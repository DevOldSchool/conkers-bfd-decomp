"""Rebuild US actor paths and reviewed navigation graphs from editable records."""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
import struct
import zlib
try:
    from scripts import asset_inputs, model_assets, rzip_archive, route_codec as codec, texture_build
    from scripts.build_files import write_if_changed
    from scripts import asset_receipts
    from scripts.model_character_alpha import checked_spans
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import asset_inputs, model_assets, rzip_archive, route_codec as codec, texture_build
    from build_files import write_if_changed
    import asset_receipts
    from model_character_alpha import checked_spans
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
BANKS = {0x10: tuple(range(69)),
         0x19: (2, 11, 17, 23, 28, 29, 36, 39, 40, 42, 43, 44, 45, 48, 50, 51, 52, 55,
                56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68)}
CODE_SPANS = (
    (0x15016850, 2736, '63f239818f87b8a1dec1ea0e9fbb7a743c34b0c4'),
    (0x15077DBC, 224, 'a208f2d466ef764b84e212ee7cec490172eee669'),
    (0x1507B974, 212, 'f4e49c5ea97773c24d5c5cc2d96876a6e402da64'),
    (0x150611E8, 1012, '939f23fb852ce69ee5654609675d77395e8fc2c8'),
    (0x1502B7F0, 240, '8f37332e9c2598c7a996b8d1e0c5d9ea82f44cfd'),
    (0x1502B8E0, 212, '2aea02ea13f93c5c25772d23323e71f576b8e0de'),
    (0x1502B9B4, 284, 'accc93aa31acfbf75c5e1115f51de09fd9a22b48'),
    (0x15085B70, 120, '83c1be07442824609b2ec549d16fec9431e551e9'),
    (0x15085BE8, 448, '058c1c93e9c9dfb151f404bb64f05b174f444574'),
    (0x15085DF8, 672, '1063907ca86203a445bbc8d76f0880ee885d16f4'),
    (0x15086098, 716, 'f646bbf58e968acdf86cad35cfa983d84c05b4ba'),
    (0x15086364, 2156, '402c0aaef5970cea35f9bc0124eac4d475be88b6'),
    (0x15086D48, 76, 'c67431410646c4fb8cd54ecec6d39f46dfbf56e9'),
    (0x15088A08, 848, 'd84d374ddda6e8dfc76ca2f4835b9e90c04e4dae'),
    (0x1508B2A8, 336, 'd526c4c8169fa772f02d4b39b563dc5f90ad18cf'),
    (0x1502B5C8, 244, '9c411ce6bf78e69583215fa8484bfd0f137edc72'),
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def input_directory(bank):
    if type(bank) is not int or bank not in BANKS:
        raise ValueError('unsupported route bank')
    return Path(f'build/assets/routes/us/bank{bank:02X}')


def part_name(bank):
    input_directory(bank)
    return f'asset_bank_{bank:02X}'


def verify_consumers(game, layout):
    return {'code': checked_spans(game.code, layout['game_vram'], CODE_SPANS)}


def encode_payload(data):
    compressor = zlib.compressobj(level=6, wbits=-15)
    return struct.pack('>I', len(data)) + compressor.compress(data) + compressor.flush()


def encode_record(bank, record):
    input_directory(bank)
    return codec.encode_paths(record) if bank == 0x10 else codec.encode_graph(record)


def reviewed_bank(bank, root=ROOT):
    input_directory(bank)
    path, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    rom, _ = rzip_archive.read_rom(path)
    if rzip_archive.rom_sha1(rom) != ROM_SHA1:
        raise ValueError('US route ROM checksum mismatch')
    game = rzip_archive.game_archive(rom, layout['game_start'], layout['game_end'])
    consumers = verify_consumers(game, layout)
    banks = {b.index: b for b in rzip_archive.parse_asset_banks(rom, layout['asset_table'])}
    target = banks[bank]
    if target.flags:
        raise ValueError('route bank index differs from reviewed inventory')
    actors = {e.index: e for e in rzip_archive.parse_asset_entries(rom, banks[0x0E])} if bank == 0x10 else {}
    entries, decoded = [], {}
    for entry in rzip_archive.parse_asset_entries(rom, target):
        if entry.index not in BANKS[bank]:
            continue
        if entry.type_flags & ~0x90 or not entry.compressed:
            raise ValueError('route entry flags differ from reviewed storage')
        original = rom[entry.start:entry.end]
        chunk = rzip_archive.decode_rzip_chunk(original)
        if chunk.consumed != len(original):
            raise ValueError('route compressed entry has unexplained trailing bytes')
        data = chunk.data
        row = {'entry': entry.index, 'rom_start': entry.start, 'rom_end': entry.end,
               'decoded_sha256': sha256(data), 'encoder': {'level': 6, 'window_bits': -15}}
        if bank == 0x10:
            if entry.index not in actors:
                raise ValueError(f'route inventory mismatch: missing bank 0E actor entry {entry.index}')
            actor = actors[entry.index]
            source = rom[actor.start:actor.end]
            actor_chunk = rzip_archive.decode_rzip_chunk(source) if actor.compressed else None
            if actor_chunk and actor_chunk.consumed != len(source):
                raise ValueError('actor count source has unexplained trailing bytes')
            actor_data = actor_chunk.data if actor_chunk else source
            if len(actor_data) % 48:
                raise ValueError('actor placement size differs from the native 48-byte stride')
            count = len(actor_data) // 48
            record = codec.decode_paths(data, count)
            row['actors'] = {'bank': 14, 'entry': entry.index, 'count': count, 'decoded_sha256': sha256(actor_data)}
        else:
            record = codec.decode_graph(data)
            row['node_count'] = len(record['nodes'])
        if encode_record(bank, record) != data or encode_payload(data) != original:
            raise ValueError('route fresh encoding differs from reviewed ROM entry')
        entries.append(row); decoded[str(entry.index)] = record
    if [r['entry'] for r in entries] != list(BANKS[bank]):
        raise ValueError('route bank selected entries differ from reviewed inventory')
    segments = load_profile(root / 'config/profiles/us.yaml')['segments']
    indices = [i for i, s in enumerate(segments) if isinstance(s, dict) and s.get('name') == part_name(bank)]
    if len(indices) != 1 or indices[0] + 1 >= len(segments):
        raise ValueError('missing or duplicate route YAML segment')
    segment, following = segments[indices[0]:indices[0] + 2]
    end = following['start'] if isinstance(following, dict) else following[0]
    if (segment.get('type') != 'bin' or segment.get('start') != target.start or end != target.end
            or segment.get('align') != 1 or segment.get('subalign') != 1):
        raise ValueError('route YAML extent differs from reviewed ROM bank')
    expected = {'schema_version': 1, 'profile': 'us', 'bank': bank, 'rom_sha1': ROM_SHA1,
                'rom_start': target.start, 'rom_end': target.end, 'original_sha256': sha256(rom[target.start:target.end]),
                'entries': entries, 'consumers': consumers,
                'rom_ranges': [[r['rom_start'], r['rom_end']] for r in entries],
                'format': codec.PATH_FORMAT if bank == 0x10 else codec.GRAPH_FORMAT}
    return rom, expected, decoded


def input_files(rom, expected, decoded):
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'backing.bin': rom[expected['rom_start']:expected['rom_end']],
            'routes.json': (json.dumps(decoded, indent=2) + '\n').encode()}


def input_error(directory, expected, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      f'./conker route-assets recover --bank {expected["bank"]:02X} to back up this folder and restore reviewed routes.')


def input_hashes(directory, expected):
    try:
        hashes = asset_inputs.manifest_hashes(directory, expected,
            ('manifest.json', 'backing.bin', 'routes.json'), 'route bank')
        if hashes['backing.bin'] != expected['original_sha256']:
            raise ValueError('route backing changed; restore it before reconstruction')
        return hashes
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error


def packed_bank(directory, expected):
    before = input_hashes(directory, expected)
    try:
        packed = bytearray((directory / 'backing.bin').read_bytes())
        records = json.loads((directory / 'routes.json').read_text())
        if not isinstance(records, dict) or set(records) != {str(row['entry']) for row in expected['entries']}:
            raise ValueError('route source entry set changed')
        spans = []
        for row in expected['entries']:
            record = records[str(row['entry'])]
            data = encode_record(expected['bank'], record)
            if expected['bank'] == 0x10 and len(record['actor_paths']) != row['actors']['count']:
                raise ValueError('route source actor count differs from native placements')
            if row['encoder'] != {'level': 6, 'window_bits': -15}:
                raise ValueError('unsupported route encoder')
            if sha256(data) != row['decoded_sha256']:
                raise ValueError('routes no longer reconstruct original decoded data')
            fresh = encode_payload(data)
            if len(fresh) != row['rom_end'] - row['rom_start']:
                raise ValueError('route compression extent differs from reviewed ROM')
            at = row['rom_start'] - expected['rom_start']
            packed[at:at + len(fresh)] = fresh
            spans.append((at, fresh))
        if sha256(packed) != expected['original_sha256']:
            raise ValueError('routes no longer reconstruct original storage')
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('route inputs changed during packing')
    return bytes(packed), spans, before


def recover_inputs(bank, root=ROOT):
    rom, expected, decoded = reviewed_bank(bank, root)
    backup = asset_inputs.recover_directory(root / input_directory(bank), root / 'build/assets/routes/recovery',
                                           f'us-bank{bank:02X}-', input_files(rom, expected, decoded))
    return {'input_directory': str(root / input_directory(bank)), 'backup_directory': backup}


def build_parts(bank, root=ROOT):
    rom, expected, decoded = reviewed_bank(bank, root)
    directory = root / input_directory(bank)
    if not directory.exists():
        texture_build.publish_inputs(directory, input_files(rom, expected, decoded))
    packed, spans, hashes = packed_bank(directory, expected)
    if packed != rom[expected['rom_start']:expected['rom_end']]:
        raise ValueError('route candidate differs from independent original ROM')
    if input_hashes(directory, expected) != hashes:
        raise ValueError('route inputs changed during batch packing')
    write_if_changed(root / 'build/us/routes/parts' / (part_name(bank) + '.bin'), packed)
    asset_receipts.write(root, 'routes', __file__, {part_name(bank): asset_receipts.part_record(
        output=f'build/us/routes/parts/{part_name(bank)}.bin', payload=packed, source_inputs=hashes,
        input_directory=input_directory(bank), extent=expected, spans=spans)}, merge=True)
    proof = {**expected, 'source_inputs': hashes, 'rebuilt_bytes': sum(len(data) for _, data in spans),
             'verification': 'native_route_records_fresh_compression_actual_rom_ranges', 'matches_original': True}
    write_if_changed(root / f'build/us/routes/bank{bank:02X}.json', (json.dumps(proof, indent=2) + '\n').encode())
    return proof


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('build', 'recover'))
    parser.add_argument('--bank', choices=('10', '19'))
    args = parser.parse_args(argv)
    if args.command == 'recover' and args.bank is None:
        parser.error('recover requires --bank to choose one input directory')
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(int(args.bank, 16)), indent=2))
        else:
            for bank in (int(args.bank, 16),) if args.bank else BANKS:
                proof = build_parts(bank)
                print(f"Verified route bank {bank:02X}: {proof['rebuilt_bytes']} ROM bytes")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
