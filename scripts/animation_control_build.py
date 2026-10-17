"""Rebuild reviewed US animation-control entries from native semantic records."""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
import struct
import zlib
try:
    from scripts import asset_inputs, model_assets, rzip_archive, animation_control_codec as codec, texture_build
    from scripts.build_files import write_if_changed
    from scripts import asset_receipts
    from scripts.model_character_alpha import checked_spans
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import asset_inputs, model_assets, rzip_archive, animation_control_codec as codec, texture_build
    from build_files import write_if_changed
    import asset_receipts
    from model_character_alpha import checked_spans
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
BANKS = {15: (6, 7, 9, 13, 14, 17, 19, 20, 23, 25, 26, 28, 29, 31, 34, 35, 38, 39, 44, 45, 47, 49, 50,
      53, 55, 57, 63, 64, 65, 66, 67, 73, 78, 82, 86, 89, 92, 93, 97, 99, 100, 101, 103, 106,
      108, 110, 111, 112, 114, 115, 118, 124, 125, 129, 132, 133, 134, 135, 137, 138, 139, 143,
      145, 148, 151, 153, 161, 162, 163, 164, 167, 168, 169, 170, 171, 179, 181, 182, 183, 184,
      185, 186)}
CODE_SPANS = (
    (0x1503D438, 36, 'add9aec5cb5ff6df58ba80704156c1463b4a2071'),
    (0x1503D45C, 40, 'f5577970b0c26c8f77e61e87793a6743762fef19'),
    (0x1503D484, 140, '40f757370bbf19e10e675591d24421010455453d'),
    (0x1503D660, 276, '698addad07c12e755805e484a22441109dd90252'),
    (0x1505E0C4, 1420, '3e17bb649f54edb53a448676e71fbea0adce0e10'),
    (0x1505E650, 380, '7ff7faebb700286719b32f4b7390b9c9f772236b'),
    (0x1506AD30, 580, 'd812ac16d841c33e1022eb9989b506c2529fc62f'),
    (0x1507BB28, 236, '6cee60a0ca9a16387aec59870d545689e54bf66f'),
    (0x1507BC14, 412, 'e04f71fcd2150534ad374b1be8b77050eb1be2bd'),
    (0x15075400, 152, '2bb1b91ab6bcc907c54bb2ddb6dece4248bc79fe'),
    (0x15075DE8, 132, 'c8b170b755ac831f4c65ef01d979c93df9040e91'),
    (0x1507735C, 8, 'fcaee431e1f242adb7285049ca72a9c79bfa3f0e'),
    (0x1505E7CC, 168, '0a9f64f88204888e084714906bf7cd8dc4ae17ca'),
    (0x1505E874, 1216, '13d48182eca8587b0cc26a2d7ce35930aef570f4'),
    (0x1505959C, 608, 'ee1e6907462d2bc608ada1e670b960f59c2edcf2'),
    (0x1502B5C8, 244, '9c411ce6bf78e69583215fa8484bfd0f137edc72'),
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def input_directory(bank):
    if type(bank) is not int or bank not in BANKS:
        raise ValueError('unsupported animation control bank')
    return Path(f'build/assets/animation-control/us/bank{bank:02X}')


def part_name(bank):
    input_directory(bank)
    return f'asset_bank_{bank:02x}'


def verify_consumers(game, layout):
    return {'code': checked_spans(game.code, layout['game_vram'], CODE_SPANS)}


def encode_payload(data):
    compressor = zlib.compressobj(level=6, wbits=-15)
    return struct.pack('>I', len(data)) + compressor.compress(data) + compressor.flush()


def encode_record(bank, record):
    input_directory(bank)
    return codec.encode(record)


def reviewed_bank(bank, root=ROOT):
    input_directory(bank)
    path, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    rom, _ = rzip_archive.read_rom(path)
    if rzip_archive.rom_sha1(rom) != ROM_SHA1:
        raise ValueError('US animation control ROM checksum mismatch')
    game = rzip_archive.game_archive(rom, layout['game_start'], layout['game_end'])
    consumers = verify_consumers(game, layout)
    banks = {b.index: b for b in rzip_archive.parse_asset_banks(rom, layout['asset_table'])}
    target = banks[bank]
    if target.flags:
        raise ValueError('animation control bank index differs from reviewed inventory')
    entries, decoded = [], {}
    for entry in rzip_archive.parse_asset_entries(rom, target):
        if entry.index not in BANKS[bank]:
            continue
        if entry.type_flags & ~0x90 or not entry.compressed:
            raise ValueError('animation control entry flags differ from reviewed storage')
        original = rom[entry.start:entry.end]
        chunk = rzip_archive.decode_rzip_chunk(original)
        if chunk.consumed != len(original):
            raise ValueError('animation control compressed entry has unexplained trailing bytes')
        data = chunk.data
        row = {'entry': entry.index, 'rom_start': entry.start, 'rom_end': entry.end,
               'decoded_sha256': sha256(data), 'encoder': {'level': 6, 'window_bits': -15}}
        record = codec.decode(data)
        row['record_counts'] = {key: len(value) for key, value in record.items() if isinstance(value, list)}
        if encode_record(bank, record) != data or encode_payload(data) != original:
            raise ValueError('animation control fresh encoding differs from reviewed ROM entry')
        entries.append(row); decoded[str(entry.index)] = record
    if [r['entry'] for r in entries] != list(BANKS[bank]):
        raise ValueError('animation control bank selected entries differ from reviewed inventory')
    segments = load_profile(root / 'config/profiles/us.yaml')['segments']
    indices = [i for i, s in enumerate(segments) if isinstance(s, dict) and s.get('name') == part_name(bank)]
    if len(indices) != 1 or indices[0] + 1 >= len(segments):
        raise ValueError('missing or duplicate animation control YAML segment')
    segment, following = segments[indices[0]:indices[0] + 2]
    end = following['start'] if isinstance(following, dict) else following[0]
    if (segment.get('type') != 'bin' or segment.get('start') != target.start or end != target.end
            or segment.get('align') != 1 or segment.get('subalign') != 1):
        raise ValueError('animation control YAML extent differs from reviewed ROM bank')
    expected = {'schema_version': 1, 'profile': 'us', 'bank': bank, 'rom_sha1': ROM_SHA1,
                'rom_start': target.start, 'rom_end': target.end, 'original_sha256': sha256(rom[target.start:target.end]),
                'entries': entries, 'consumers': consumers,
                'rom_ranges': [[r['rom_start'], r['rom_end']] for r in entries],
                'format': codec.FORMAT}
    return rom, expected, decoded


def input_files(rom, expected, decoded):
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'backing.bin': rom[expected['rom_start']:expected['rom_end']],
            'controls.json': (json.dumps(decoded, indent=2) + '\n').encode()}


def input_error(directory, expected, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      f'./conker animation-control recover --bank {expected["bank"]:02X} to back up this folder and restore reviewed animation controls.')


def input_hashes(directory, expected):
    try:
        hashes = asset_inputs.manifest_hashes(directory, expected,
            ('manifest.json', 'backing.bin', 'controls.json'), 'animation control bank')
        if hashes['backing.bin'] != expected['original_sha256']:
            raise ValueError('animation control backing changed; restore it before reconstruction')
        return hashes
    except (OSError, ValueError, KeyError, TypeError, IndexError, struct.error) as error:
        raise input_error(directory, expected, str(error)) from error


def packed_bank(directory, expected):
    before = input_hashes(directory, expected)
    try:
        packed = bytearray((directory / 'backing.bin').read_bytes())
        records = json.loads((directory / 'controls.json').read_text())
        if not isinstance(records, dict) or set(records) != {str(row['entry']) for row in expected['entries']}:
            raise ValueError('animation control source entry set changed')
        spans = []
        for row in expected['entries']:
            record = records[str(row['entry'])]
            data = encode_record(expected['bank'], record)
            if row['encoder'] != {'level': 6, 'window_bits': -15}:
                raise ValueError('unsupported animation control encoder')
            if sha256(data) != row['decoded_sha256']:
                raise ValueError('animation controls no longer reconstruct original decoded data')
            fresh = encode_payload(data)
            if len(fresh) != row['rom_end'] - row['rom_start']:
                raise ValueError('animation control compression extent differs from reviewed ROM')
            at = row['rom_start'] - expected['rom_start']
            packed[at:at + len(fresh)] = fresh
            spans.append((at, fresh))
        if sha256(packed) != expected['original_sha256']:
            raise ValueError('animation controls no longer reconstruct original storage')
    except (OSError, ValueError, KeyError, TypeError, IndexError, struct.error) as error:
        raise input_error(directory, expected, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('animation control inputs changed during packing')
    return bytes(packed), spans, before


def recover_inputs(bank, root=ROOT):
    rom, expected, decoded = reviewed_bank(bank, root)
    backup = asset_inputs.recover_directory(root / input_directory(bank), root / 'build/assets/animation-control/recovery',
                                           f'us-bank{bank:02X}-', input_files(rom, expected, decoded))
    return {'input_directory': str(root / input_directory(bank)), 'backup_directory': backup}


def build_parts(bank, root=ROOT):
    rom, expected, decoded = reviewed_bank(bank, root)
    directory = root / input_directory(bank)
    if not directory.exists():
        texture_build.publish_inputs(directory, input_files(rom, expected, decoded))
    packed, spans, hashes = packed_bank(directory, expected)
    if packed != rom[expected['rom_start']:expected['rom_end']]:
        raise ValueError('animation control candidate differs from independent original ROM')
    if input_hashes(directory, expected) != hashes:
        raise ValueError('animation control inputs changed during batch packing')
    write_if_changed(root / 'build/us/animation-control/parts' / (part_name(bank) + '.bin'), packed)
    asset_receipts.write(root, 'animation-control', __file__, {part_name(bank): asset_receipts.part_record(
        output=f'build/us/animation-control/parts/{part_name(bank)}.bin', payload=packed, source_inputs=hashes,
        input_directory=input_directory(bank), extent=expected, spans=spans)}, merge=True)
    proof = {**expected, 'source_inputs': hashes, 'rebuilt_bytes': sum(len(data) for _, data in spans),
             'verification': 'native_animation_control_records_fresh_compression_actual_rom_ranges', 'matches_original': True}
    write_if_changed(root / f'build/us/animation-control/bank{bank:02X}.json', (json.dumps(proof, indent=2) + '\n').encode())
    return proof


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('build', 'recover'))
    parser.add_argument('--bank', choices=('0F',))
    args = parser.parse_args(argv)
    if args.command == 'recover' and args.bank is None:
        parser.error('recover requires --bank to choose one input directory')
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(int(args.bank, 16)), indent=2))
        else:
            for bank in (int(args.bank, 16),) if args.bank else BANKS:
                proof = build_parts(bank)
                print(f"Verified animation control bank {bank:02X}: {proof['rebuilt_bytes']} ROM bytes")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
