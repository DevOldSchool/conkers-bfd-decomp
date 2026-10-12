"""Rebuild bounded scene fields and compose them with the verified trigger-volume bank."""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
try:
    from scripts import asset_inputs, model_assets, rzip_archive, scene_field_codec as codec, scene_volume_build as volumes, texture_build
    from scripts.build_files import write_if_changed
    from scripts.model_character_alpha import checked_spans
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import asset_inputs, model_assets, rzip_archive, scene_field_codec as codec, scene_volume_build as volumes, texture_build
    from build_files import write_if_changed
    from model_character_alpha import checked_spans
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
PART = 'asset_bank_0c'
INPUT_DIRECTORY = Path('build/assets/scene-fields/us')
SELECTION = (
    (0, 2),
    (0, 4),
    (0, 6),
    (0, 8),
    (0, 10),
    (1, 2),
    (1, 4),
    (1, 6),
    (1, 8),
    (1, 10),
    (2, 2),
    (2, 4),
    (2, 6),
    (2, 8),
    (2, 10),
    (3, 6),
    (3, 10),
    (4, 2),
    (4, 4),
    (4, 6),
    (4, 8),
    (4, 10),
    (6, 2),
    (6, 4),
    (6, 6),
    (6, 8),
    (6, 10),
    (7, 2),
    (7, 4),
    (7, 6),
    (7, 8),
    (7, 10),
    (8, 6),
    (8, 10),
    (10, 2),
    (10, 4),
    (10, 6),
    (10, 8),
    (10, 10),
    (11, 2),
    (11, 4),
    (11, 6),
    (11, 8),
    (11, 10),
    (12, 2),
    (12, 4),
    (12, 6),
    (12, 8),
    (12, 10),
    (13, 6),
    (13, 10),
    (14, 2),
    (14, 4),
    (14, 6),
    (14, 8),
    (14, 10),
    (15, 6),
    (15, 10),
    (16, 2),
    (16, 4),
    (16, 6),
    (16, 8),
    (16, 10),
    (17, 6),
    (17, 10),
    (18, 2),
    (18, 4),
    (18, 6),
    (18, 8),
    (18, 10),
    (19, 2),
    (19, 4),
    (19, 6),
    (19, 8),
    (19, 10),
    (20, 2),
    (20, 4),
    (20, 6),
    (20, 10),
    (21, 6),
    (21, 10),
    (22, 6),
    (22, 10),
    (23, 6),
    (23, 8),
    (23, 10),
    (24, 2),
    (24, 4),
    (24, 6),
    (24, 10),
    (25, 2),
    (25, 4),
    (25, 6),
    (25, 8),
    (25, 10),
    (26, 2),
    (26, 4),
    (26, 6),
    (26, 8),
    (26, 10),
    (27, 2),
    (27, 4),
    (27, 6),
    (27, 8),
    (27, 10),
    (28, 2),
    (28, 4),
    (28, 6),
    (28, 8),
    (28, 10),
    (29, 2),
    (29, 4),
    (29, 6),
    (29, 10),
    (30, 2),
    (30, 4),
    (30, 6),
    (30, 10),
    (33, 2),
    (33, 4),
    (33, 6),
    (33, 10),
    (34, 6),
    (34, 10),
    (35, 2),
    (35, 4),
    (35, 6),
    (35, 10),
    (36, 2),
    (36, 4),
    (36, 6),
    (36, 10),
    (37, 6),
    (37, 10),
    (38, 2),
    (38, 4),
    (38, 6),
    (38, 8),
    (38, 10),
    (39, 6),
    (39, 10),
    (40, 2),
    (40, 4),
    (40, 6),
    (40, 8),
    (40, 10),
    (41, 2),
    (41, 4),
    (41, 6),
    (41, 8),
    (41, 10),
    (42, 6),
    (42, 10),
    (43, 2),
    (43, 4),
    (43, 6),
    (43, 8),
    (43, 10),
    (44, 2),
    (44, 4),
    (44, 6),
    (44, 8),
    (44, 10),
    (45, 2),
    (45, 4),
    (45, 6),
    (45, 10),
    (46, 6),
    (46, 8),
    (46, 10),
    (47, 2),
    (47, 4),
    (47, 6),
    (47, 8),
    (47, 10),
    (48, 2),
    (48, 4),
    (48, 6),
    (48, 10),
    (49, 2),
    (49, 4),
    (49, 6),
    (49, 8),
    (49, 10),
    (50, 2),
    (50, 4),
    (50, 6),
    (50, 8),
    (50, 10),
    (51, 2),
    (51, 4),
    (51, 6),
    (51, 10),
    (52, 2),
    (52, 4),
    (52, 6),
    (52, 10),
    (53, 2),
    (53, 4),
    (53, 6),
    (53, 8),
    (53, 10),
    (54, 2),
    (54, 4),
    (54, 6),
    (54, 8),
    (54, 10),
    (55, 2),
    (55, 4),
    (55, 6),
    (55, 8),
    (55, 10),
    (56, 2),
    (56, 4),
    (56, 6),
    (56, 10),
    (57, 2),
    (57, 4),
    (57, 6),
    (57, 8),
    (57, 10),
    (58, 2),
    (58, 4),
    (58, 6),
    (58, 10),
    (59, 2),
    (59, 4),
    (59, 6),
    (59, 8),
    (59, 10),
    (60, 2),
    (60, 4),
    (60, 6),
    (60, 8),
    (60, 10),
    (61, 6),
    (61, 8),
    (61, 10),
    (62, 2),
    (62, 4),
    (62, 6),
    (62, 10),
    (63, 2),
    (63, 4),
    (63, 6),
    (63, 10),
    (64, 2),
    (64, 4),
    (64, 6),
    (64, 8),
    (64, 10),
    (65, 2),
    (65, 4),
    (65, 6),
    (65, 8),
    (65, 10),
    (66, 6),
    (66, 10),
    (67, 6),
    (67, 8),
    (67, 10),
    (68, 6),
    (68, 10),
)
CODE_SPANS = (
    (0x151149AC, 112, 'a831c20eb614451ce4fc3c1acbd67b004a69cf0a'),
    (0x150039E0, 2964, 'b7b5ae00e5b5a3c5a0d28ad82582a25479a3bc66'),
    (0x150045C4, 992, '37dee925089b4581e1686a4aabefd610ad02694f'),
    (0x1511490C, 160, '629429fa4dce5a8dfb8eab6df18755a557d07775'),
    (0x151148A8, 100, '982eaba37b6c1dba097b1c79a4acafeb014eead9'),
    (0x150A7CB0, 80, '9b41e5a7ae2b80ac7139471fe9dcc4016d16937b'),
    (0x150A8050, 336, '9d826a49f8529b88a58d6e5c9455f61c87f6244c'),
    (0x150A7A48, 312, '50a10c8988bdedf7c044f28a9c22e9edbb43e1c6'),
    (0x15017578, 104, 'f6259c9efe9c590262915929790350ea2ea7672e'),
    (0x150174C0, 184, 'da6f2f90acb6ade2a374542cffb52669d233f55f'),
    (0x1508ECC0, 252, 'b89c0ae135c17fadb1e51420144b28d4453caaa9'),
    (0x1508EE0C, 372, '93d0eb954c05c52c27eaa8f8718a20f9178b6ba4'),
    (0x15113E54, 508, '0f7af2433892c364923128e69e707c3178eb2260'),
    (0x15016690, 448, '04c4bc5c7ce31f0b47fa60e4f46261a1132875bc'),
    (0x15084D70, 1696, '6719f8ecec0d801585f952735b0f11f137f7d123'),
    (0x1507DFE4, 304, 'f1e102c9478d05d3406c6804f602bf9f51bdd641'),
    (0x15005290, 564, '449541c7af21a8552d757b70604d680d9e1b988c'),
    (0x15096A68, 672, '9f22ef86dcd8c6bb0e93b949475704c6d0ec8207'),
    (0x1500ABA0, 116, 'bec39f646cc8bb13853ddb0727b9d5cbe9ac2093'),
    (0x1500AC14, 368, 'e2d376dd1513f6db8a3f2f446a357f38fc5aa7fe'),
    (0x1500BEC0, 800, '51e400a4655f8da4655a7a8a8ac5ffe2d36acd0c'),
    (0x1500AD84, 388, '11e8ef10442d2438eb832885eacc4cb7da488a81'),
    (0x1502B7F0, 240, '8f37332e9c2598c7a996b8d1e0c5d9ea82f44cfd'),
    (0x1502B5C8, 244, '9c411ce6bf78e69583215fa8484bfd0f137edc72'),
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
    (0x1502B8E0, 212, '2aea02ea13f93c5c25772d23323e71f576b8e0de'),
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
            if child.index not in codec.FORMATS:
                continue
            if (scene.index, child.index) not in SELECTION or child.type_flags or child.compressed:
                raise ValueError('scene child selection or flags differ from reviewed storage')
            data = rom[child.start:child.end]
            record = codec.decode(data, child.index)
            spans = codec.encode(record, child.index)
            if not record['records'] or any(data[at:at + len(payload)] != payload for at, payload in spans):
                raise ValueError('scene fresh encoding differs from reviewed ROM entry')
            key = f'{scene.index}:{child.index}'
            entries.append({'scene': scene.index, 'child': child.index, 'key': key,
                'rom_start': child.start, 'rom_end': child.end, 'record_count': len(record['records']),
                'field_sha256': sha256(b''.join(payload for _, payload in spans)),
                'field_ranges': [[at, at + len(payload)] for at, payload in spans]})
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
                'rom_ranges': [[r['rom_start'] + start, r['rom_start'] + end]
                               for r in entries for start, end in r['field_ranges']]}
    return rom, expected, decoded


def input_files(rom, expected, decoded):
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'backing.bin': rom[expected['rom_start']:expected['rom_end']],
            'records.json': (json.dumps(decoded, indent=2) + '\n').encode()}


def input_error(directory, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      './conker scene-fields recover to back up this folder and restore reviewed records.')


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
            fields = codec.encode(record, row['child'])
            if len(record['records']) != row['record_count']:
                raise ValueError('scene source record count differs from native storage')
            if len(record['records']) * codec.STRIDES[row['child']] != row['rom_end'] - row['rom_start']:
                raise ValueError('scene child extent differs from native record count')
            if [[at, at + len(data)] for at, data in fields] != row['field_ranges']:
                raise ValueError('scene semantic field extents changed')
            if sha256(b''.join(data for _, data in fields)) != row['field_sha256']:
                raise ValueError('scene fields no longer reconstruct original decoded values')
            for start, data in fields:
                if start < 0 or start + len(data) > row['rom_end'] - row['rom_start']:
                    raise ValueError('scene field exceeds native child extent')
                at = row['rom_start'] + start - expected['rom_start']
                if at < 0 or at + len(data) > len(packed) or (spans and at < spans[-1][0] + len(spans[-1][1])):
                    raise ValueError('scene ranges are unordered, overlapping or out of bounds')
                packed[at:at + len(data)] = data
                spans.append((at, data))
        if [[expected['rom_start'] + at, expected['rom_start'] + at + len(data)] for at, data in spans] != expected['rom_ranges']:
            raise ValueError('scene physical ranges changed')
        if sha256(packed) != expected['original_sha256']:
            raise ValueError('scene records no longer reconstruct original storage')
    except (OSError, ValueError) as error:
        raise input_error(directory, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('scene inputs changed during packing')
    return bytes(packed), spans, before


def recover_inputs(root=ROOT):
    rom, expected, decoded = reviewed_bank(root)
    backup = asset_inputs.recover_directory(root / INPUT_DIRECTORY, root / 'build/assets/scene-fields/recovery',
                                           'us-', input_files(rom, expected, decoded))
    return {'input_directory': str(root / INPUT_DIRECTORY), 'backup_directory': backup}


def build_parts(root=ROOT):
    # Validate both families before publishing the bank shared by their report units.
    rom, expected, decoded = reviewed_bank(root)
    volume_rom, volume_expected, volume_decoded = volumes.reviewed_bank(root)
    if (volume_rom != rom or volume_expected['rom_start'] != expected['rom_start']
            or volume_expected['rom_end'] != expected['rom_end']):
        raise ValueError('scene family reference ROM or bank extent differs')
    directory, volume_directory = root / INPUT_DIRECTORY, root / volumes.INPUT_DIRECTORY
    for path, producer, contract, source in ((directory, input_files, expected, decoded),
            (volume_directory, volumes.input_files, volume_expected, volume_decoded)):
        if not path.exists():
            texture_build.publish_inputs(path, producer(rom, contract, source))
    packed, spans, hashes = packed_bank(directory, expected)
    volume_packed, volume_spans, volume_hashes = volumes.packed_bank(volume_directory, volume_expected)
    all_spans = sorted([*spans, *volume_spans])
    for (at, data), (following, _) in zip(all_spans, all_spans[1:]):
        if at + len(data) > following:
            raise ValueError('scene field and volume ownership overlaps')
    composed = bytearray(volume_packed)
    for at, data in spans:
        composed[at:at + len(data)] = data
    if composed != packed or packed != rom[expected['rom_start']:expected['rom_end']]:
        raise ValueError('scene candidate differs from independent original ROM')
    if (input_hashes(directory, expected) != hashes
            or volumes.input_hashes(volume_directory, volume_expected) != volume_hashes):
        raise ValueError('scene inputs changed during batch packing')
    write_if_changed(root / 'build/us/scene-fields/parts' / (PART + '.bin'), bytes(composed))
    proof = {**expected, 'source_inputs': hashes, 'volume_source_inputs': volume_hashes,
             'rebuilt_bytes': sum(len(data) for _, data in spans),
             'verification': 'native_scene_fields_actual_rom_ranges', 'matches_original': True}
    write_if_changed(root / 'build/us/scene-fields/batch.json', (json.dumps(proof, indent=2) + '\n').encode())
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
            print(f"Verified additional scene fields: {proof['rebuilt_bytes']} ROM bytes")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
