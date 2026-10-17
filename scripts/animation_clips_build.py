"""Rebuild only understood native clips inside otherwise unresolved animation objects."""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
try:
    from scripts import asset_inputs, model_animation_build as codec, model_assets, model_build, rzip_archive, texture_build
    from scripts.build_files import write_if_changed
    from scripts import asset_receipts
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_inputs, model_animation_build as codec, model_assets, model_build, rzip_archive, texture_build
    from build_files import write_if_changed
    import asset_receipts
    from model_character_alpha import checked_spans

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
# entry: (complete descriptor/stream pair count, unresolved pair)
SELECTION = {82: (14, 0), 83: (37, 18), 124: (43, 36), 146: (27, 21)}
PARTS = ('00D3CBA0', '00E86CF8', '00EEC120')
CODE_SPANS = (
    (0x1503D5F0, 112, '6b19502694fdcbcee75fc751b4d136adc57685df'),
    (0x1503D660, 276, '698addad07c12e755805e484a22441109dd90252'),
    (0x1505E650, 380, '7ff7faebb700286719b32f4b7390b9c9f772236b'),
    (0x1502B5C8, 244, '9c411ce6bf78e69583215fa8484bfd0f137edc72'),
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
)
DATA_SPANS = (
    (0x80098888, 5, '6fe0c9a64b1631a17cf7694da0a5ae277debf9f2'),
    (0x80084410, 20, '61f32622f7cf7a64f3053667add132e3b219fdfe'),
    (0x80098860, 20, '935c80d22bf849a3854f420dd794e764736ca2ca'),
    (0x80098874, 3, '2d34be24c766356effa07b267cd13709664a6b3d'),
    (0x80098878, 2, '4ecc87266f257c265e368df6959c08d135674000'),
    (0x8009887C, 5, '1637e728683d73b1d740a7c593bb450cfa022f6b'),
    (0x80098884, 4, '1b7c04837bff9428426dde0a70c38d7b4b026a69'),
    (0x80099420, 2, 'f3b5c98ec3292ec573fc95538ada184fbaa97bbe'),
    (0x80099422, 2, 'da9275c985a9d4abe4005c5ddb00bed00ca56761'),
    (0x80099424, 2, '9cba0a3afd8a7a9b7dc5a25f33c9e3584e2d31ac'),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def input_directory(part):
    if part not in PARTS:
        raise ValueError('unsupported partial animation object')
    return Path('build/assets/animation-clips/us') / part


def part_name(part):
    input_directory(part)
    return 'models/raw/' + part


def checked_payload(rom, entry):
    raw = rom[entry.start:entry.end]
    if not entry.compressed:
        return raw
    chunk = rzip_archive.decode_rzip_chunk(raw)
    if chunk.consumed != len(raw):
        raise ValueError('animation route has unexplained compressed trailing bytes')
    return chunk.data


def reviewed_objects(root=ROOT):
    path, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    rom, _ = rzip_archive.read_rom(path)
    if rzip_archive.rom_sha1(rom) != ROM_SHA1:
        raise ValueError('US partial animation ROM checksum mismatch')
    game = rzip_archive.game_archive(rom, layout['game_start'], layout['game_end'])
    codec.verify_consumers(game.code, int(layout['game_vram']))
    consumers = checked_spans(game.code, int(layout['game_vram']), (*codec.CONSUMER_SPANS, *CODE_SPANS))
    tables = checked_spans(game.data, int(layout['game_data_vram']), DATA_SPANS)
    banks = {b.index: b for b in rzip_archive.parse_asset_banks(rom, layout['asset_table'])}
    if any(index not in banks or banks[index].flags for index in (2, 15)):
        raise ValueError('animation or route bank flags changed')
    entries = {e.index: e for e in rzip_archive.parse_asset_entries(rom, banks[2])}
    route_entries = {e.index: e for e in rzip_archive.parse_asset_entries(rom, banks[15])}
    groups, representatives = model_assets.character_animation_group_routes(game.data, int(layout['game_data_vram']))
    route_entry = route_entries.get(representatives.get(146, 146))
    if route_entry is None:
        raise ValueError('character 146 has no native animation route')
    route_data = checked_payload(rom, route_entry)
    routes = model_assets.parse_character_animation_route_table(route_data)
    logical = {}
    for route in routes:
        if route['pair_index'] >= SELECTION[146][0]:
            raise ValueError('runtime animation route selects an absent pair')
        logical.setdefault(route['pair_index'], []).append(route['logical_animation_index'])
    rows, end = model_build.layout_bins(root / 'config/profiles/us.yaml', bank=2)
    extents = [(start, finish, name) for (start, name), (finish, _) in zip(rows, rows[1:] + [(end, '')])]
    objects = {}
    for entry_index, (pair_count, excluded) in SELECTION.items():
        entry = entries.get(entry_index)
        if entry is None or entry.compressed:
            raise ValueError('partial animation entry is missing or unexpectedly compressed')
        owners = [(start, finish, name) for start, finish, name in extents
                  if start <= entry.start < entry.end <= finish]
        if len(owners) != 1 or owners[0][2] not in [part_name(p) for p in PARTS]:
            raise ValueError('partial animation YAML object ownership changed')
        start, finish, name = owners[0]
        part = name.rsplit('/', 1)[1]
        if part not in objects:
            objects[part] = ({'schema_version': 1, 'profile': 'us', 'bank': 2, 'part': part,
                'rom_sha1': ROM_SHA1, 'rom_start': start, 'rom_end': finish,
                'original_sha256': sha256(rom[start:finish]), 'entries': [], 'rom_ranges': [],
                'consumers': consumers, 'runtime_tables': tables}, {})
        expected, records = objects[part]
        segments = codec.animation_segments(rom[entry.start:entry.end])
        if len(segments) != pair_count * 2:
            raise ValueError('partial animation pair count changed')
        evidence = {'entry': entry_index, 'rom_start': entry.start, 'rom_end': entry.end,
                    'pair_count': pair_count, 'excluded_pair': excluded, 'clips': []}
        if entry_index == 146:
            evidence['runtime_routes'] = {'entry': route_entry.index, 'rom_start': route_entry.start,
                'rom_end': route_entry.end, 'decoded_sha256': sha256(route_data), 'groups': list(groups)}
        records[str(entry_index)] = {}
        for pair, (descriptor, stream) in enumerate(zip(segments[::2], segments[1::2])):
            if pair == excluded:
                continue
            duration = 255
            logical_indices = []
            if entry_index == 146 and descriptor.data[3] == 255:
                logical_indices = logical.get(pair, [])
                duration, _ = model_assets.resolve_character_animation_runtime_duration(
                    entry_index, tuple(logical_indices), game.data, int(layout['game_data_vram']))
            record = codec.clip_records(descriptor.data, stream.data, runtime_duration=duration)
            generated = codec.encode_clip(record, runtime_duration=duration)
            if generated != (descriptor.data, stream.data):
                raise ValueError('partial animation channels differ from original bytes')
            first, last = entry.start + descriptor.offset, entry.start + stream.offset + stream.size
            evidence['clips'].append({'pair': pair, 'rom_start': first, 'rom_end': last,
                'descriptor_size': descriptor.size, 'stream_size': stream.size,
                'runtime_duration': duration, 'logical_indices': logical_indices,
                'original_sha256': sha256(descriptor.data + stream.data)})
            expected['rom_ranges'].append([first, last])
            records[str(entry_index)][str(pair)] = record
        expected['entries'].append(evidence)
    if tuple(objects) != PARTS:
        raise ValueError('partial animation object selection changed')
    return rom, list(objects.values())


def input_files(rom, expected, records):
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'backing.bin': rom[expected['rom_start']:expected['rom_end']],
            'clips.json': (json.dumps(records, indent=2) + '\n').encode()}


def input_error(directory, expected, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      f'./conker animation-clips recover --part {expected["part"]} to back up and restore this object.')


def input_hashes(directory, expected):
    try:
        hashes = asset_inputs.manifest_hashes(directory, expected,
            ('manifest.json', 'backing.bin', 'clips.json'), 'partial animation')
        if hashes['backing.bin'] != expected['original_sha256']:
            raise ValueError('animation backing changed')
        return hashes
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error


def packed_object(directory, expected):
    before = input_hashes(directory, expected)
    try:
        packed = bytearray((directory / 'backing.bin').read_bytes())
        records = json.loads((directory / 'clips.json').read_text())
        if not isinstance(records, dict) or set(records) != {str(e['entry']) for e in expected['entries']}:
            raise ValueError('partial animation source entry set changed')
        spans = []
        for entry in expected['entries']:
            clips = records[str(entry['entry'])]
            if not isinstance(clips, dict) or set(clips) != {str(c['pair']) for c in entry['clips']}:
                raise ValueError('partial animation source clip selection changed')
            for clip in entry['clips']:
                descriptor, stream = codec.encode_clip(clips[str(clip['pair'])], runtime_duration=clip['runtime_duration'])
                if (len(descriptor) != clip['descriptor_size'] or len(stream) != clip['stream_size']
                        or len(descriptor) + len(stream) != clip['rom_end'] - clip['rom_start']):
                    raise ValueError('partial animation generated clip extent changed')
                fresh = descriptor + stream
                if sha256(fresh) != clip['original_sha256']:
                    raise ValueError('animation channels no longer reconstruct the original clip')
                offset = clip['rom_start'] - expected['rom_start']
                if offset < 0 or offset + len(fresh) > len(packed):
                    raise ValueError('partial animation clip lies outside the linked object')
                packed[offset:offset + len(fresh)] = fresh
                spans.append((offset, fresh))
        ranges = [[expected['rom_start'] + offset, expected['rom_start'] + offset + len(data)] for offset, data in spans]
        if ranges != expected['rom_ranges'] or any(a[1] > b[0] for a, b in zip(ranges, ranges[1:])):
            raise ValueError('partial animation generated ranges changed or overlap')
        if sha256(packed) != expected['original_sha256']:
            raise ValueError('partial animation output differs from original storage')
    except (OSError, ValueError, TypeError, KeyError, IndexError) as error:
        raise input_error(directory, expected, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('partial animation inputs changed during packing')
    return bytes(packed), spans, before


def recover_inputs(part, root=ROOT):
    input_directory(part)
    rom, selected = reviewed_objects(root)
    expected, records = next(pair for pair in selected if pair[0]['part'] == part)
    backup = asset_inputs.recover_directory(root / input_directory(part), root / 'build/assets/animation-clips/recovery',
                                           f'us-{part}-', input_files(rom, expected, records))
    return {'input_directory': str(root / input_directory(part)), 'backup_directory': backup}


def build_parts(root=ROOT):
    rom, selected = reviewed_objects(root)
    candidates = []
    for expected, records in selected:
        directory = root / input_directory(expected['part'])
        if not directory.exists():
            texture_build.publish_inputs(directory, input_files(rom, expected, records))
        packed, spans, hashes = packed_object(directory, expected)
        if packed != rom[expected['rom_start']:expected['rom_end']]:
            raise ValueError('partial animation differs from independent original ROM')
        candidates.append((expected, directory, (packed, spans), hashes))
    asset_inputs.check_batch_sources(candidates, input_hashes, 'partial animation')
    proofs, receipts = [], {}
    for expected, directory, (packed, spans), hashes in candidates:
        name = part_name(expected['part'])
        write_if_changed(root / 'build/us/animation-clips/parts' / (name + '.bin'), packed)
        proofs.append({**expected, 'source_inputs': hashes, 'rebuilt_bytes': sum(len(data) for _, data in spans),
                       'matches_original': True})
        receipts[name] = asset_receipts.part_record(
            output=f'build/us/animation-clips/parts/{name}.bin', payload=packed, source_inputs=hashes,
            input_directory=input_directory(expected['part']), extent=expected, spans=spans)
    asset_receipts.write(root, 'animation-clips', __file__, receipts)
    write_if_changed(root / 'build/us/animation-clips/batch.json', (json.dumps(proofs, indent=2) + '\n').encode())
    return proofs


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('build', 'recover'))
    parser.add_argument('--part', choices=PARTS)
    args = parser.parse_args(argv)
    if args.command == 'recover' and args.part is None:
        parser.error('recover requires --part')
    if args.command == 'build' and args.part is not None:
        parser.error('build reconstructs the three linked objects together')
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(args.part), indent=2))
        else:
            proof = build_parts()
            print(f"Verified animation clip ranges: {sum(x['rebuilt_bytes'] for x in proof)} ROM bytes")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
