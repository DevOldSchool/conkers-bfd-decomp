"""Rebuild the native-format animation bundles in US bank 0A."""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
import struct
try:
    from scripts import asset_inputs, model_assets, rzip_archive, model_animation_build as codec, texture_build
    from scripts.build_files import write_if_changed
    from scripts.model_character_alpha import checked_spans
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import asset_inputs, model_assets, rzip_archive, model_animation_build as codec, texture_build
    from build_files import write_if_changed
    from model_character_alpha import checked_spans
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
BANKS = (0x0A,)
# Bank-independent native layout, frame-count and channel readers. A specific
# runtime owner for bank 0A has not been established.
CODE_SPANS = codec.CONSUMER_SPANS[:4]


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def input_directory(bank):
    if type(bank) is not int or bank not in BANKS:
        raise ValueError('unsupported animation bank')
    return Path(f'build/assets/animation-bank/us/bank{bank:02X}')


def part_name(bank):
    input_directory(bank)
    return f'asset_bank_{bank:02x}'


def verify_consumers(game, layout):
    return {'code': checked_spans(game.code, layout['game_vram'], CODE_SPANS)}


def encode_record(bank, record):
    input_directory(bank)
    if not isinstance(record, dict) or record.get('format') != 'character-animation-native':
        raise ValueError('bank 0A requires descriptor-duration animation records')
    if any(clip['header_bytes'][3] == 255 for clip in record['clips']):
        raise ValueError('bank 0A runtime duration is unconfirmed')
    return codec.encode_animation_records(record)


def reviewed_bank(bank, root=ROOT):
    input_directory(bank)
    path, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    rom, _ = rzip_archive.read_rom(path)
    if rzip_archive.rom_sha1(rom) != ROM_SHA1:
        raise ValueError('US animation ROM checksum mismatch')
    game = rzip_archive.game_archive(rom, layout['game_start'], layout['game_end'])
    consumers = verify_consumers(game, layout)
    banks = {b.index: b for b in rzip_archive.parse_asset_banks(rom, layout['asset_table'])}
    target = banks[bank]
    if target.flags:
        raise ValueError('animation bank index differs from reviewed inventory')
    entries, decoded = [], {}
    all_entries = rzip_archive.parse_asset_entries(rom, target)
    if len(all_entries) != 29:
        raise ValueError('animation bank entry count differs from reviewed inventory')
    for entry in all_entries:
        if entry.type_flags != (0x80 if entry.index == 28 else 0) or entry.compressed:
            raise ValueError('animation bank entry flags differ from reviewed storage')
        data = rom[entry.start:entry.end]
        record = codec.animation_records(data)
        if encode_record(bank, record) != data:
            raise ValueError('animation fresh encoding differs from reviewed ROM entry')
        row = {'entry': entry.index, 'rom_start': entry.start, 'rom_end': entry.end,
               'decoded_sha256': sha256(data), 'clip_count': len(record['clips']),
               'frame_count': sum(len(clip['frames']) for clip in record['clips'])}
        entries.append(row); decoded[str(entry.index)] = record
    if [r['entry'] for r in entries] != list(range(29)):
        raise ValueError('animation bank entries differ from reviewed inventory')
    segments = load_profile(root / 'config/profiles/us.yaml')['segments']
    indices = [i for i, s in enumerate(segments) if isinstance(s, dict) and s.get('name') == part_name(bank)]
    if len(indices) != 1 or indices[0] + 1 >= len(segments):
        raise ValueError('missing or duplicate animation YAML segment')
    segment, following = segments[indices[0]:indices[0] + 2]
    end = following['start'] if isinstance(following, dict) else following[0]
    if (segment.get('type') != 'bin' or segment.get('start') != target.start or end != target.end
            or segment.get('align') != 1 or segment.get('subalign') != 1):
        raise ValueError('animation YAML extent differs from reviewed ROM bank')
    expected = {'schema_version': 1, 'profile': 'us', 'bank': bank, 'rom_sha1': ROM_SHA1,
                'rom_start': target.start, 'rom_end': target.end, 'original_sha256': sha256(rom[target.start:target.end]),
                'entries': entries, 'consumers': consumers,
                'rom_ranges': [[r['rom_start'], r['rom_end']] for r in entries],
                'format': 'character-animation-native', 'runtime_owner': 'unconfirmed'}
    return rom, expected, decoded


def input_files(rom, expected, decoded):
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'backing.bin': rom[expected['rom_start']:expected['rom_end']],
            'animations.json': (json.dumps(decoded, indent=2) + '\n').encode()}


def input_error(directory, expected, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      f'./conker animation-bank recover --bank {expected["bank"]:02X} to back up this folder and restore reviewed animations.')


def input_hashes(directory, expected):
    try:
        hashes = asset_inputs.manifest_hashes(directory, expected,
            ('manifest.json', 'backing.bin', 'animations.json'), 'animation bank')
        if hashes['backing.bin'] != expected['original_sha256']:
            raise ValueError('animation backing changed; restore it before reconstruction')
        return hashes
    except (OSError, ValueError, KeyError, TypeError, IndexError, struct.error) as error:
        raise input_error(directory, expected, str(error)) from error


def packed_bank(directory, expected):
    before = input_hashes(directory, expected)
    try:
        packed = bytearray((directory / 'backing.bin').read_bytes())
        records = json.loads((directory / 'animations.json').read_text())
        if not isinstance(records, dict) or set(records) != {str(row['entry']) for row in expected['entries']}:
            raise ValueError('animation source entry set changed')
        spans = []
        for row in expected['entries']:
            record = records[str(row['entry'])]
            data = encode_record(expected['bank'], record)
            if (len(record['clips']) != row['clip_count']
                    or sum(len(clip['frames']) for clip in record['clips']) != row['frame_count']):
                raise ValueError('animation source counts differ from reviewed inventory')
            if sha256(data) != row['decoded_sha256']:
                raise ValueError('animations no longer reconstruct original decoded data')
            fresh = data
            if len(fresh) != row['rom_end'] - row['rom_start']:
                raise ValueError('animation extent differs from reviewed ROM')
            at = row['rom_start'] - expected['rom_start']
            packed[at:at + len(fresh)] = fresh
            spans.append((at, fresh))
        if sha256(packed) != expected['original_sha256']:
            raise ValueError('animations no longer reconstruct original storage')
    except (OSError, ValueError, KeyError, TypeError, IndexError, struct.error) as error:
        raise input_error(directory, expected, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('animation inputs changed during packing')
    return bytes(packed), spans, before


def recover_inputs(bank, root=ROOT):
    rom, expected, decoded = reviewed_bank(bank, root)
    backup = asset_inputs.recover_directory(root / input_directory(bank), root / 'build/assets/animation-bank/recovery',
                                           f'us-bank{bank:02X}-', input_files(rom, expected, decoded))
    return {'input_directory': str(root / input_directory(bank)), 'backup_directory': backup}


def build_parts(bank, root=ROOT):
    rom, expected, decoded = reviewed_bank(bank, root)
    directory = root / input_directory(bank)
    if not directory.exists():
        texture_build.publish_inputs(directory, input_files(rom, expected, decoded))
    packed, spans, hashes = packed_bank(directory, expected)
    if packed != rom[expected['rom_start']:expected['rom_end']]:
        raise ValueError('animation candidate differs from independent original ROM')
    if input_hashes(directory, expected) != hashes:
        raise ValueError('animation inputs changed during batch packing')
    write_if_changed(root / 'build/us/animation-bank/parts' / (part_name(bank) + '.bin'), packed)
    proof = {**expected, 'source_inputs': hashes, 'rebuilt_bytes': sum(len(data) for _, data in spans),
             'verification': 'native_animation_records_actual_rom_ranges', 'matches_original': True}
    write_if_changed(root / f'build/us/animation-bank/bank{bank:02X}.json', (json.dumps(proof, indent=2) + '\n').encode())
    return proof


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('build', 'recover'))
    parser.add_argument('--bank', choices=('0A',))
    args = parser.parse_args(argv)
    if args.command == 'recover' and args.bank is None:
        parser.error('recover requires --bank to choose one input directory')
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(int(args.bank, 16)), indent=2))
        else:
            for bank in (int(args.bank, 16),) if args.bank else BANKS:
                proof = build_parts(bank)
                print(f"Verified animation bank {bank:02X}: {proof['rebuilt_bytes']} ROM bytes")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
