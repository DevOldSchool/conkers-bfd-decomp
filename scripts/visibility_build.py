"""Rebuild reviewed US visibility ranges from editable Huffman codes and visible-node sets."""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
import struct
import zlib

try:
    from scripts import asset_inputs, model_assets, rzip_archive, visibility_codec as codec, texture_build, visibility_geometry, rzip_bounded
    from scripts.build_files import write_if_changed
    from scripts.model_character_alpha import checked_spans
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import asset_inputs, model_assets, rzip_archive, visibility_codec as codec, texture_build, visibility_geometry, rzip_bounded
    from build_files import write_if_changed
    from model_character_alpha import checked_spans
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
INPUT_DIRECTORY = Path('build/assets/visibility/us')
PART_NAME = 'asset_bank_05'
CODE_SPANS = (
    (0x150025FC, 200, 'f0c6709831a249d31ec728521c808de4320272a5'),
    (0x150183D0, 304, 'd81697ea28726ad4979ab992e6a85ff54e4a98b0'),
    (0x15018500, 464, 'b21668751b16dee2de164e058895ce0935b01d3a'),
    (0x1502B5C8, 244, '9c411ce6bf78e69583215fa8484bfd0f137edc72'),
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
    (0x150A6760, 256, '8962df8ba492ec8ddb19a9460ec1e8961284374e'),
)
CODEBOOK_ENCODERS = dict.fromkeys((5, 13, 15, 23, 25, 39, 47, 53, 55, 57, 59, 61, 73, 87, 89, 91, 97, 105, 111, 121), 6)

BITMAP_ENTRIES = (4, 12, 14, 22, 38, 52, 54, 60, 72, 86, 88, 90, 96, 104, 110, 120)
ENCODERS = dict(sorted({**CODEBOOK_ENCODERS, **dict.fromkeys(BITMAP_ENTRIES, 'bounded6')}.items()))


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def verify_consumers(game, layout):
    return {'code': checked_spans(game.code, layout['game_vram'], CODE_SPANS),
            'geometry': checked_spans(game.code, layout['game_vram'], visibility_geometry.CODE_SPANS)}


def encode_payload(data, encoder):
    if encoder == 'bounded6':
        return rzip_bounded.encode_payload(data)
    if type(encoder) is not int or encoder != 6:
        raise ValueError('unsupported visibility encoder')
    compressor = zlib.compressobj(level=encoder, wbits=-15)
    return struct.pack('>I', len(data)) + compressor.compress(data) + compressor.flush()


def reviewed_bank(root=ROOT):
    path, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    rom, _ = rzip_archive.normalize_rom(path.read_bytes())
    if hashlib.sha1(rom).hexdigest() != ROM_SHA1:
        raise ValueError('US visibility ROM checksum mismatch')
    game = rzip_archive.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    consumers = verify_consumers(game, layout)
    bank = next(b for b in rzip_archive.parse_asset_banks(rom, layout['asset_table']) if b.index == 5)
    if bank.flags:
        raise ValueError('visibility bank index differs from reviewed inventory')
    entries, decoded, payloads, stored_entries = [], {}, {}, {}
    for entry in rzip_archive.parse_asset_entries(rom, bank):
        if entry.index not in ENCODERS:
            continue
        if entry.type_flags & ~0x90 or not entry.compressed:
            raise ValueError('visibility entry flags differ from reviewed storage')
        original = rom[entry.start:entry.end]
        chunk = rzip_archive.decode_rzip_chunk(original)
        if chunk.consumed != len(original):
            raise ValueError('visibility compressed entry has unexplained trailing bytes')
        payloads[entry.index], stored_entries[entry.index] = chunk.data, entry
    if sorted(payloads) != list(ENCODERS):
        raise ValueError('visibility bank selected entries differ from reviewed inventory')
    for index in CODEBOOK_ENCODERS:
        decoded[str(index)] = codec.decode_codebook(payloads[index])
    scene_bank = next(b for b in rzip_archive.parse_asset_banks(rom, layout['asset_table']) if b.index == 4)
    scenes = {entry.index: entry for entry in rzip_archive.parse_asset_entries(rom, scene_bank)}
    for index, encoder in ENCODERS.items():
        entry, data = stored_entries[index], payloads[index]
        row = {'entry': index, 'rom_start': entry.start, 'rom_end': entry.end,
               'decoded_sha256': sha256(data), 'encoder': encoder}
        if index in BITMAP_ENTRIES:
            scene_entry = scenes[index // 2]
            source = rom[scene_entry.start:scene_entry.end]
            scene = rzip_archive.decode_rzip_chunk(source).data if scene_entry.compressed else source
            geometry = visibility_geometry.scene_dimensions(scene)
            decoded[str(index)] = codec.decode_bitmap(data, geometry['node_count'], decoded[str(index + 1)])
            row['geometry'] = {'scene': index // 2, **geometry}
        else:
            row['symbol_count'] = sum(bits is not None for bits in decoded[str(index)]['codes'])
        if encode_payload(data, encoder) != rom[entry.start:entry.end]:
            raise ValueError('visibility fresh compressor differs from reviewed ROM entry')
        entries.append(row)
    segments = load_profile(root / 'config/profiles/us.yaml')['segments']
    indices = [i for i, s in enumerate(segments) if isinstance(s, dict) and s.get('name') == PART_NAME]
    if len(indices) != 1 or indices[0] + 1 >= len(segments):
        raise ValueError('missing or duplicate visibility YAML segment')
    segment, following = segments[indices[0]:indices[0] + 2]
    end = following['start'] if isinstance(following, dict) else following[0]
    if (segment.get('type') != 'bin' or segment.get('start') != bank.start or end != bank.end
            or segment.get('align') != 1 or segment.get('subalign') != 1):
        raise ValueError('visibility YAML extent differs from reviewed ROM bank')
    expected = {'schema_version': 2, 'profile': 'us', 'bank': 5, 'rom_sha1': ROM_SHA1,
                'rom_start': bank.start, 'rom_end': bank.end, 'original_sha256': sha256(rom[bank.start:bank.end]),
                'entries': entries, 'consumers': consumers,
                'rom_ranges': [[r['rom_start'], r['rom_end']] for r in entries],
                'format': codec.FORMAT, 'bitmap_format': codec.BITMAP_FORMAT}
    return rom, expected, decoded


def input_files(rom, expected, decoded):
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'backing.bin': rom[expected['rom_start']:expected['rom_end']],
            'codebooks.json': (json.dumps({k: v for k, v in decoded.items() if int(k) % 2}, indent=2) + '\n').encode(),
            'bitmaps.json': (json.dumps({k: v for k, v in decoded.items() if not int(k) % 2}, indent=2) + '\n').encode()}


def input_error(directory, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      './conker visibility-assets recover to back up this folder and restore reviewed visibility sources.')


def input_hashes(directory, expected):
    try:
        hashes = asset_inputs.manifest_hashes(directory, expected,
            ('manifest.json', 'backing.bin', 'codebooks.json', 'bitmaps.json'), 'visibility bank')
        if hashes['backing.bin'] != expected['original_sha256']:
            raise ValueError('visibility backing changed; restore it before reconstruction')
        return hashes
    except (OSError, ValueError) as error:
        raise input_error(directory, str(error)) from error


def packed_bank(directory, expected):
    before = input_hashes(directory, expected)
    try:
        packed = bytearray((directory / 'backing.bin').read_bytes())
        codebooks = json.loads((directory / 'codebooks.json').read_text())
        bitmaps = json.loads((directory / 'bitmaps.json').read_text())
        for records, parity in ((codebooks, 1), (bitmaps, 0)):
            if (not isinstance(records, dict)
                    or set(records) != {str(row['entry']) for row in expected['entries'] if row['entry'] % 2 == parity}):
                raise ValueError('visibility source entry set changed')
        spans = []
        for row in expected['entries']:
            index = row['entry']
            if index % 2:
                data = codec.encode_codebook(codebooks[str(index)])
            else:
                record = bitmaps[str(index)]
                data = codec.encode_bitmap(record, codebooks[str(index + 1)])
                if record['node_count'] != row['geometry']['node_count']:
                    raise ValueError('visibility source dimensions differ from native geometry')
            if sha256(data) != row['decoded_sha256']:
                raise ValueError('visibility sources no longer reconstruct original decoded data')
            fresh = encode_payload(data, row['encoder'])
            if len(fresh) != row['rom_end'] - row['rom_start']:
                raise ValueError('visibility compression extent differs from reviewed ROM')
            at = row['rom_start'] - expected['rom_start']
            packed[at:at + len(fresh)] = fresh
            spans.append((at, fresh))
        if sha256(packed) != expected['original_sha256']:
            raise ValueError('visibility sources no longer reconstruct original storage')
    except (OSError, ValueError) as error:
        raise input_error(directory, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('visibility inputs changed during packing')
    return bytes(packed), spans, before


def recover_inputs(root=ROOT):
    rom, expected, decoded = reviewed_bank(root)
    backup = asset_inputs.recover_directory(root / INPUT_DIRECTORY, root / 'build/assets/visibility/recovery',
                                           'us-', input_files(rom, expected, decoded))
    return {'input_directory': str(root / INPUT_DIRECTORY), 'backup_directory': backup}


def build_parts(root=ROOT):
    rom, expected, decoded = reviewed_bank(root)
    directory = root / INPUT_DIRECTORY
    if not directory.exists():
        texture_build.publish_inputs(directory, input_files(rom, expected, decoded))
    packed, spans, hashes = packed_bank(directory, expected)
    if packed != rom[expected['rom_start']:expected['rom_end']]:
        raise ValueError('visibility candidate differs from independent original ROM')
    if input_hashes(directory, expected) != hashes:
        raise ValueError('visibility inputs changed during batch packing')
    write_if_changed(root / 'build/us/visibility/parts' / (PART_NAME + '.bin'), packed)
    proof = {**expected, 'source_inputs': hashes, 'rebuilt_bytes': sum(len(data) for _, data in spans),
             'verification': 'huffman_codes_and_node_sets_fresh_compression_actual_rom_ranges', 'matches_original': True}
    write_if_changed(root / 'build/us/visibility/batch.json', (json.dumps(proof, indent=2) + '\n').encode())
    return proof


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('build', 'recover'))
    args = parser.parse_args(argv)
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(), indent=2))
        else:
            proof = build_parts()
            print(f"Verified visibility ranges: {proof['rebuilt_bytes']} ROM bytes")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
