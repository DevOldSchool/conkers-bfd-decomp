"""Rebuild reviewed US scene spheres and trigger volumes from typed records."""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
try:
    from scripts import asset_inputs, model_assets, rzip_archive, scene_volume_codec as codec, texture_build
    from scripts.build_files import write_if_changed
    from scripts.model_character_alpha import checked_spans
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import asset_inputs, model_assets, rzip_archive, scene_volume_codec as codec, texture_build
    from build_files import write_if_changed
    from model_character_alpha import checked_spans
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
PART = 'asset_bank_0c'
INPUT_DIRECTORY = Path('build/assets/scene-volumes/us')
SELECTION = (
    (0, 3),
    (0, 5),
    (1, 3),
    (1, 5),
    (2, 3),
    (2, 5),
    (4, 3),
    (4, 5),
    (6, 3),
    (6, 5),
    (7, 3),
    (7, 5),
    (8, 5),
    (10, 3),
    (10, 5),
    (11, 5),
    (12, 3),
    (12, 5),
    (14, 3),
    (14, 5),
    (16, 3),
    (16, 5),
    (17, 5),
    (18, 5),
    (19, 3),
    (19, 5),
    (20, 3),
    (20, 5),
    (22, 5),
    (23, 5),
    (24, 3),
    (24, 5),
    (25, 5),
    (26, 5),
    (27, 3),
    (27, 5),
    (28, 5),
    (29, 5),
    (30, 3),
    (30, 5),
    (33, 5),
    (34, 5),
    (35, 3),
    (35, 5),
    (36, 5),
    (38, 3),
    (38, 5),
    (39, 5),
    (40, 5),
    (41, 5),
    (42, 5),
    (43, 5),
    (44, 3),
    (44, 5),
    (45, 5),
    (46, 5),
    (47, 5),
    (48, 5),
    (49, 3),
    (49, 5),
    (50, 3),
    (50, 5),
    (51, 5),
    (52, 5),
    (53, 3),
    (53, 5),
    (54, 5),
    (55, 3),
    (55, 5),
    (56, 5),
    (57, 5),
    (58, 5),
    (59, 3),
    (59, 5),
    (60, 3),
    (60, 5),
    (61, 5),
    (62, 5),
    (63, 5),
    (64, 5),
    (65, 3),
    (65, 5),
    (66, 5),
    (67, 5),
    (68, 5),
)
CODE_SPANS = (
    (0x15004FE0, 656, 'ec09f794ec81ec0dfce12d7ca14804343ae95fa9'),
    (0x150379DC, 1764, '4dac69fff03b3cba779c215af88e0ec8f73766b7'),
    (0x1503DDD0, 160, 'bb76ab1025b2d2d4a341fee7c8c4447f91ba5555'),
    (0x15017930, 496, '1d10415e266535b4781290cc22658bd25fe7dd65'),
    (0x15017B20, 1156, '74b6a2734f896eff5c1f715080bc802eb04de812'),
    (0x15017FA4, 1068, 'b46c72f558eb386a458c17e0e4adeaccf131da32'),
    (0x150A0D14, 120, 'f5d7eddf871570ddc3f16b948374ad37125f3726'),
    (0x150A09D0, 836, '53a9204952e2b4a669d8a9578f83e4ef36fb9187'),
    (0x150A0D8C, 692, '6ad3794dd5b27bd5a336599bb2e8372ed23a8135'),
    (0x1502B7F0, 240, '8f37332e9c2598c7a996b8d1e0c5d9ea82f44cfd'),
    (0x1502B5C8, 244, '9c411ce6bf78e69583215fa8484bfd0f137edc72'),
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def verify_consumers(game, layout):
    return {'code': checked_spans(game.code, layout['game_vram'], CODE_SPANS)}


def reviewed_bank(root=ROOT):
    path, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    rom, _ = rzip_archive.normalize_rom(path.read_bytes())
    if hashlib.sha1(rom).hexdigest() != ROM_SHA1:
        raise ValueError('US scene ROM checksum mismatch')
    game = rzip_archive.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    consumers = verify_consumers(game, layout)
    target = next(b for b in rzip_archive.parse_asset_banks(rom, layout['asset_table']) if b.index == 12)
    if target.flags:
        raise ValueError('scene bank flags differ from reviewed inventory')
    entries, decoded = [], {}
    for scene in rzip_archive.parse_asset_entries(rom, target):
        if scene.type_flags & ~0x80 or scene.compressed:
            raise ValueError('scene parent flags differ from reviewed storage')
        nested = rzip_archive.AssetBank(scene.index, scene.start, scene.end, 0)
        for child in rzip_archive.parse_asset_entries(rom, nested):
            if child.index not in (3, 5):
                continue
            if (scene.index, child.index) not in SELECTION or child.type_flags or child.compressed:
                raise ValueError('scene child selection or flags differ from reviewed storage')
            data = rom[child.start:child.end]
            record = codec.decode(data, child.index)
            if not record['records'] or codec.encode(record, child.index) != data:
                raise ValueError('scene fresh encoding differs from reviewed ROM entry')
            key = f'{scene.index}:{child.index}'
            entries.append({'scene': scene.index, 'child': child.index, 'key': key,
                'rom_start': child.start, 'rom_end': child.end, 'record_count': len(record['records']),
                'decoded_sha256': sha256(data)})
            decoded[key] = record
    if [(r['scene'], r['child']) for r in entries] != list(SELECTION):
        raise ValueError('scene selected entries differ from reviewed inventory')
    segments = load_profile(root / 'config/profiles/us.yaml')['segments']
    indices = [i for i, s in enumerate(segments) if isinstance(s, dict) and s.get('name') == PART]
    if len(indices) != 1 or indices[0] + 1 >= len(segments):
        raise ValueError('missing or duplicate scene YAML segment')
    segment, following = segments[indices[0]:indices[0] + 2]
    end = following['start'] if isinstance(following, dict) else following[0]
    if (segment.get('type') != 'bin' or segment.get('start') != target.start or end != target.end
            or segment.get('align') != 1 or segment.get('subalign') != 1):
        raise ValueError('scene YAML extent differs from reviewed ROM bank')
    expected = {'schema_version': 1, 'profile': 'us', 'bank': 12, 'rom_sha1': ROM_SHA1,
                'rom_start': target.start, 'rom_end': target.end, 'original_sha256': sha256(rom[target.start:target.end]),
                'entries': entries, 'consumers': consumers,
                'rom_ranges': [[r['rom_start'], r['rom_end']] for r in entries]}
    return rom, expected, decoded


def input_files(rom, expected, decoded):
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'backing.bin': rom[expected['rom_start']:expected['rom_end']],
            'records.json': (json.dumps(decoded, indent=2) + '\n').encode()}


def input_error(directory, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      './conker scene-volumes recover to back up this folder and restore reviewed records.')


def input_hashes(directory, expected):
    try:
        hashes = asset_inputs.manifest_hashes(directory, expected,
            ('manifest.json', 'backing.bin', 'records.json'), 'scene bank')
        if hashes['backing.bin'] != expected['original_sha256']:
            raise ValueError('scene backing changed; restore it before reconstruction')
        return hashes
    except (OSError, ValueError) as error:
        raise input_error(directory, str(error)) from error


def packed_bank(directory, expected):
    before = input_hashes(directory, expected)
    try:
        packed = bytearray((directory / 'backing.bin').read_bytes())
        records = json.loads((directory / 'records.json').read_text())
        if not isinstance(records, dict) or set(records) != {row['key'] for row in expected['entries']}:
            raise ValueError('scene source entry set changed')
        spans = []
        for row in expected['entries']:
            record = records[row['key']]
            data = codec.encode(record, row['child'])
            if len(record['records']) != row['record_count']:
                raise ValueError('scene source record count differs from native storage')
            if sha256(data) != row['decoded_sha256']:
                raise ValueError('scene records no longer reconstruct original decoded data')
            if len(data) != row['rom_end'] - row['rom_start']:
                raise ValueError('scene extent differs from reviewed ROM')
            at = row['rom_start'] - expected['rom_start']
            if at < 0 or at + len(data) > len(packed) or (spans and at < spans[-1][0] + len(spans[-1][1])):
                raise ValueError('scene ranges are unordered, overlapping or out of bounds')
            packed[at:at + len(data)] = data
            spans.append((at, data))
        if sha256(packed) != expected['original_sha256']:
            raise ValueError('scene records no longer reconstruct original storage')
    except (OSError, ValueError) as error:
        raise input_error(directory, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('scene inputs changed during packing')
    return bytes(packed), spans, before


def recover_inputs(root=ROOT):
    rom, expected, decoded = reviewed_bank(root)
    backup = asset_inputs.recover_directory(root / INPUT_DIRECTORY, root / 'build/assets/scene-volumes/recovery',
                                           'us-', input_files(rom, expected, decoded))
    return {'input_directory': str(root / INPUT_DIRECTORY), 'backup_directory': backup}


def build_parts(root=ROOT):
    rom, expected, decoded = reviewed_bank(root)
    directory = root / INPUT_DIRECTORY
    if not directory.exists():
        texture_build.publish_inputs(directory, input_files(rom, expected, decoded))
    packed, spans, hashes = packed_bank(directory, expected)
    if packed != rom[expected['rom_start']:expected['rom_end']]:
        raise ValueError('scene candidate differs from independent original ROM')
    if input_hashes(directory, expected) != hashes:
        raise ValueError('scene inputs changed during batch packing')
    write_if_changed(root / 'build/us/scene-volumes/parts' / (PART + '.bin'), packed)
    proof = {**expected, 'source_inputs': hashes, 'rebuilt_bytes': sum(len(data) for _, data in spans),
             'verification': 'native_scene_records_actual_rom_ranges', 'matches_original': True}
    write_if_changed(root / 'build/us/scene-volumes/batch.json', (json.dumps(proof, indent=2) + '\n').encode())
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
            print(f"Verified scene volumes: {proof['rebuilt_bytes']} ROM bytes")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
