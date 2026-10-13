"""Reconstruct the complete US morph bank from signed XYZ endpoints."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct

try:
    from scripts import asset_inputs, model_assets, model_morphs, rzip_archive, rzip_pack, texture_build
    from scripts.build_files import write_if_changed
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import asset_inputs, model_assets, model_morphs, rzip_archive, rzip_pack, texture_build
    from build_files import write_if_changed
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
FORMAT = 'conker-character-morph-endpoints-v1'
INPUT_DIRECTORY = Path('build/assets/morph-build/us')
PART_NAME = 'asset_bank_13'
# The original selector table and corresponding model vertex boundaries.
MODELS = ((0, (496, 833, 901), (337, 12, 12), 16),
          (58, (199, 308, 333), (109, 25, 24), 7))


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def pair_table(parts, *, compressed):
    """Generate all native offsets, length flags and eight-byte zero alignment."""
    if not parts or len(parts) > 255:
        raise ValueError('invalid morph pair-table count')
    cursor = 8 * len(parts)
    headers, body = [], bytearray()
    for index, payload in enumerate(parts):
        if not payload or len(payload) >= 0x10000000:
            raise ValueError('invalid morph child extent')
        pad = -cursor % 8
        body.extend(bytes(pad))
        cursor += pad
        flags = len(payload) | (0x10000000 if compressed else 0)
        if index == len(parts) - 1:
            flags |= 0x80000000
        headers.append((cursor, flags))
        body.extend(payload)
        cursor += len(payload)
    body.extend(bytes(-cursor % 8))
    return b''.join(struct.pack('>II', *row) for row in headers) + body


def morph_records(manifest):
    result = {'format': FORMAT, 'models': []}
    for model in manifest['models']:
        result['models'].append({
            'character_entry': model['character_entry'],
            'vertex_starts': model['vertex_starts'],
            'part_vertex_counts': model['part_vertex_counts'],
            'shapes': [[part['positions'] for part in target['parts']] for target in model['targets']]})
    return result


def encode_records(records):
    if (not isinstance(records, dict) or set(records) != {'format', 'models'}
            or records['format'] != FORMAT or not isinstance(records['models'], list)
            or len(records['models']) != len(MODELS)):
        raise ValueError('invalid morph endpoint schema')
    entries = []
    for model, (character, starts, counts, shapes) in zip(records['models'], MODELS):
        if (not isinstance(model, dict)
                or set(model) != {'character_entry', 'vertex_starts', 'part_vertex_counts', 'shapes'}
                or type(model['character_entry']) is not int or model['character_entry'] != character
                or model['vertex_starts'] != list(starts) or model['part_vertex_counts'] != list(counts)
                or not isinstance(model['shapes'], list) or len(model['shapes']) != shapes
                or any(not isinstance(shape, list) or len(shape) != 3 for shape in model['shapes'])):
            raise ValueError('morph selector, vertex boundaries or shape count changed')
        parts = []
        for part, count in enumerate(counts):
            leaves = []
            for shape in model['shapes']:
                positions = shape[part]
                if (not isinstance(positions, list) or len(positions) != count
                        or any(not isinstance(xyz, list) or len(xyz) != 3
                               or any(type(v) is not int or not -32768 <= v <= 32767 for v in xyz)
                               for xyz in positions)):
                    raise ValueError('morph positions must be complete signed XYZ halfwords')
                payload = b''.join(struct.pack('>3h', *xyz) for xyz in positions)
                payload += bytes(-len(payload) % 16)
                leaves.append(rzip_pack.encode_rzip_chunk(payload))
            parts.append(pair_table(leaves, compressed=True))
        entries.append(pair_table(parts, compressed=False))
    return pair_table(entries, compressed=False)


def reviewed_bank(root=ROOT):
    path, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    rom, _ = rzip_archive.read_rom(path)
    if rzip_archive.rom_sha1(rom) != ROM_SHA1:
        raise ValueError('US morph ROM checksum mismatch')
    banks = {b.index: b for b in rzip_archive.parse_asset_banks(rom, layout['asset_table'])}
    if any(index not in banks or banks[index].flags for index in (1, 0x13)):
        raise ValueError('morph or character bank changed')
    models = {}
    for entry in rzip_archive.parse_asset_entries(rom, banks[1]):
        if entry.index in {row[0] for row in MODELS}:
            raw = rom[entry.start:entry.end]
            payload = rzip_archive.decode_rzip_chunk(raw).data if entry.compressed else raw
            models[entry.index] = (payload, model_assets.parse_character_model_geometry(payload)[0])
    if set(models) != {row[0] for row in MODELS}:
        raise ValueError('morph character model is missing')
    manifest = model_morphs.load_manifest(rom, layout, models)
    records = morph_records(manifest)
    packed = encode_records(records)
    bank = banks[0x13]
    segments = load_profile(root / 'config/profiles/us.yaml')['segments']
    indices = [i for i, s in enumerate(segments) if isinstance(s, dict) and s.get('name') == PART_NAME]
    if len(indices) != 1 or indices[0] + 1 >= len(segments):
        raise ValueError('missing or duplicate morph YAML segment')
    segment, following = segments[indices[0]:indices[0] + 2]
    end = following['start'] if isinstance(following, dict) else following[0]
    if (segment.get('type') != 'bin' or segment.get('start') != bank.start or end != bank.end
            or segment.get('align') != 1 or segment.get('subalign') != 1):
        raise ValueError('morph YAML extent differs from the reviewed ROM bank')
    if packed != rom[bank.start:bank.end]:
        raise ValueError('morph endpoints fail fresh whole-bank ROM reconstruction')
    expected = {'schema_version': 1, 'profile': 'us', 'bank': 0x13, 'rom_sha1': ROM_SHA1,
                'rom_start': bank.start, 'rom_end': bank.end, 'original_sha256': sha256(packed),
                'format': FORMAT, 'encoder': dict(texture_build.ENCODERS['zlib']),
                'model_sha1': {str(index): hashlib.sha1(data).hexdigest() for index, (data, _) in models.items()}}
    return rom, expected, records


def input_files(expected, records):
    return {name: (json.dumps(value, indent=2) + '\n').encode()
            for name, value in [('manifest.json', expected), ('morphs.json', records)]}


def input_error(directory, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      './conker model-assets recover-morphs to back up this folder and restore reviewed endpoints.')


def input_hashes(directory, expected):
    try:
        return asset_inputs.manifest_hashes(directory, expected, ('manifest.json', 'morphs.json'), 'morph bank')
    except (OSError, ValueError) as error:
        raise input_error(directory, str(error)) from error


def packed_bank(directory, expected):
    before = input_hashes(directory, expected)
    try:
        packed = encode_records(json.loads((directory / 'morphs.json').read_text()))
        if len(packed) != expected['rom_end'] - expected['rom_start'] or sha256(packed) != expected['original_sha256']:
            raise ValueError('morph endpoints no longer reconstruct original bank')
    except (OSError, ValueError) as error:
        raise input_error(directory, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('morph inputs changed during packing')
    return packed, before


def recover_inputs(root=ROOT):
    _, expected, records = reviewed_bank(root)
    backup = asset_inputs.recover_directory(root / INPUT_DIRECTORY, root / 'build/assets/morph-build/recovery',
                                           'us-', input_files(expected, records))
    return {'input_directory': str(root / INPUT_DIRECTORY), 'backup_directory': backup}


def build_parts(root=ROOT):
    rom, expected, records = reviewed_bank(root)
    directory = root / INPUT_DIRECTORY
    if not directory.exists():
        texture_build.publish_inputs(directory, input_files(expected, records))
    packed, hashes = packed_bank(directory, expected)
    if packed != rom[expected['rom_start']:expected['rom_end']]:
        raise ValueError('morph bank differs from independent original ROM bytes')
    if input_hashes(directory, expected) != hashes:
        raise ValueError('morph inputs changed during batch packing')
    write_if_changed(root / 'build/us/morphs/parts' / (PART_NAME + '.bin'), packed)
    proof = {**expected, 'source_inputs': hashes, 'stored_bytes': len(packed),
             'verification': 'typed_endpoints_fresh_compression_and_independent_rom', 'matches_original': True}
    write_if_changed(root / 'build/us/morphs/batch.json', (json.dumps(proof, indent=2) + '\n').encode())
    return proof


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('build-parts', 'recover'))
    args = parser.parse_args(argv)
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(), indent=2))
        else:
            proof = build_parts()
            print(f"Verified whole morph bank: {proof['stored_bytes']} ROM bytes")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
