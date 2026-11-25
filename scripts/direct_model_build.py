"""Rebuild bounded bank-03 auxiliary models within their existing raw objects."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

try:
    from scripts import (asset_directory_build as directories, asset_inputs, asset_receipts,
                         bank_index_inputs, model_assets, model_build, model_extended_build as codec,
                         rzip_archive, rzip_bounded, texture_build, model_short_normals)
    from scripts.build_files import write_if_changed
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_directory_build as directories, asset_inputs, asset_receipts
    import bank_index_inputs, model_assets, model_build, model_extended_build as codec
    import rzip_archive, rzip_bounded, texture_build, model_short_normals
    from build_files import write_if_changed
    from model_character_alpha import checked_spans

ROOT = Path(__file__).resolve().parent.parent
SOURCE_ROOT = Path('build/assets')
PARTS = ('00F90626', '00F954D8', '00F969E2', '00F97590', '00F9BB68', '00F9C0B2')
ENTRIES = (44, 45, 46, 47, 48, 49, 50, 63, 64, 65, 67, 68, 69, 73, 74, 75, 77, 78, 79, 96, 99)
SHORT_PART = '00F954D8'
SHORT_RANGE = (16341152, 16341495)
CODE_SPANS = (
    (0x150039E0, 2964, 'b7b5ae00e5b5a3c5a0d28ad82582a25479a3bc66'),
    (0x1502B6BC, 308, '91ed9cccb2168331f871d0b5b3597f9cfc8f558f'),
    (0x1502B4A8, 288, 'd1a82190ae64677a9404302b5a61653a5770a7dc'),
    *codec.CONSUMER_SPANS,
)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def input_directory(part):
    if part not in PARTS:
        raise ValueError('unsupported direct-model raw object')
    return SOURCE_ROOT / 'direct-models/us' / part


def part_name(part):
    input_directory(part)
    return 'models/raw/' + part


def encode_record(record):
    if (type(record) is not dict or record.get('primary') is not False
            or record.get('color_descriptors') or record.get('sentinel_words')):
        raise ValueError('direct auxiliary model requires non-primary normals/face words without colors')
    return codec.encode_extended_records(record)


def owned_ranges(expected):
    return sorted(expected['rom_ranges'] + ([list(SHORT_RANGE)] if expected['part'] == SHORT_PART else []))


def short_inputs(backing, expected):
    """Keep the accepted parent manifest/source unchanged when adding model 66."""
    if expected['part'] != SHORT_PART:
        return None
    start, end = SHORT_RANGE
    if (sha(backing) != expected['original_sha256']
            or not expected['rom_start'] <= start < end <= expected['rom_end']):
        raise ValueError('short normal model backing or extent changed')
    stored = backing[start - expected['rom_start']:end - expected['rom_start']]
    chunk = rzip_archive.decode_rzip_chunk(stored)
    source = model_short_normals.decode(chunk.data)
    if (chunk.consumed != len(stored) or model_short_normals.encode(source) != chunk.data
            or rzip_bounded.encode_payload(chunk.data) != stored):
        raise ValueError('short normal model is not an exact fresh reconstruction')
    manifest = {'schema_version': 1, 'entry': 66, 'rom_start': start, 'rom_end': end,
                'decoded_sha256': sha(chunk.data), 'stored_sha256': sha(stored),
                'parent_sha256': expected['original_sha256']}
    return manifest, source


def short_files(backing, expected):
    manifest, source = short_inputs(backing, expected)
    return {'manifest.json': (json.dumps(manifest, indent=2) + '\n').encode(),
            'model.json': (json.dumps(source, indent=2) + '\n').encode()}


def reviewed_objects(root=ROOT):
    rom, parents = directories.reviewed_directories(root)
    parent, index = next(row for row in parents if row[0]['key'] == 'bank03')
    _, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    game = rzip_archive.game_archive(rom, layout['game_start'], layout['game_end'])
    consumers = checked_spans(game.code, layout['game_vram'], CODE_SPANS)
    bank = rzip_archive.parse_asset_banks(rom, layout['asset_table'])[3]
    if bank.flags or bank.start != parent['rom_start']:
        raise ValueError('direct-model bank differs from its native index')
    short_entry = next(e for e in rzip_archive.parse_asset_entries(rom, bank) if e.index == 66)
    if not short_entry.compressed or (short_entry.start, short_entry.end) != SHORT_RANGE:
        raise ValueError('short normal model differs from its native directory entry')
    gaps = bank_index_inputs.alignment_spans(index, bank.start, bank.end)
    rows, end = model_build.layout_bins(root / 'config/profiles/us.yaml', bank=3)
    extents = {name: (a, b) for (a, name), (b, _) in zip(rows, rows[1:] + [(end, '')])}
    selected = [e for e in rzip_archive.parse_asset_entries(rom, bank) if e.index in ENTRIES]
    if tuple(e.index for e in selected) != ENTRIES:
        raise ValueError('direct-model selection is missing native entries')
    objects = {}
    for part in PARTS:
        start, stop = extents[part_name(part)]
        alignment = [[a, b] for a, b in gaps if start <= a < b <= stop]
        if any(a < stop and start < b and not start <= a < b <= stop for a, b in gaps):
            raise ValueError('direct-model object cuts an alignment gap')
        expected = {'schema_version': 1, 'profile': 'us', 'bank': 3, 'part': part,
                    'rom_sha1': directories.ROM_SHA1, 'rom_start': start, 'rom_end': stop,
                    'original_sha256': sha(rom[start:stop]), 'parent': parent,
                    'bank_end': bank.end, 'alignment_ranges': alignment,
                    'entries': [], 'rom_ranges': list(alignment), 'consumers': consumers}
        records = {}
        for entry in selected:
            if not start <= entry.start < entry.end <= stop:
                continue
            if not entry.compressed:
                raise ValueError('direct auxiliary model is unexpectedly uncompressed')
            original = rom[entry.start:entry.end]
            chunk = rzip_archive.decode_rzip_chunk(original)
            record = codec.extended_records(chunk.data, primary=False)
            if (chunk.consumed != len(original) or encode_record(record) != chunk.data
                    or rzip_bounded.encode_payload(chunk.data) != original):
                raise ValueError('direct auxiliary model is not an exact fresh reconstruction')
            expected['entries'].append({'entry': entry.index, 'rom_start': entry.start, 'rom_end': entry.end,
                'decoded_sha256': sha(chunk.data), 'stored_sha256': sha(original)})
            expected['rom_ranges'].append([entry.start, entry.end])
            records[str(entry.index)] = record
        if not records:
            raise ValueError('direct-model selected raw object contains no reviewed models')
        expected['rom_ranges'].sort()
        objects[part] = expected, records
    if sorted(e['entry'] for expected, _ in objects.values() for e in expected['entries']) != list(ENTRIES):
        raise ValueError('direct-model raw objects do not partition the selection')
    return rom, list(objects.values())


def input_files(rom, expected, records):
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'backing.bin': rom[expected['rom_start']:expected['rom_end']],
            'models.json': (json.dumps(records, indent=2) + '\n').encode()}


def input_error(directory, expected, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      f'./conker direct-models recover --part {expected["part"]} to back up and restore this object. '
                      'Shared bank03 index inputs use ./conker asset-directories recover --part bank03.')


def input_hashes(root, expected):
    directory = root / input_directory(expected['part'])
    try:
        own = asset_inputs.manifest_hashes(directory, expected,
            ('manifest.json', 'backing.bin', 'models.json'), 'direct auxiliary model')
        if own['backing.bin'] != expected['original_sha256']:
            raise ValueError('direct-model backing changed')
        prefix = input_directory(expected['part']).relative_to(SOURCE_ROOT)
        hashes = {(prefix / p).as_posix(): h for p, h in own.items()}
        if expected['part'] == SHORT_PART:
            manifest, _ = short_inputs((directory / 'backing.bin').read_bytes(), expected)
            child = asset_inputs.manifest_hashes(directory / 'short-normals', manifest,
                ('manifest.json', 'model.json'), 'short normal model')
            hashes.update({(prefix / 'short-normals' / p).as_posix(): h for p, h in child.items()})
        parent = expected['parent']; source = directories.input_directory(parent['key'])
        shared = directories.input_hashes(root / source, parent)
        hashes.update({(source.relative_to(SOURCE_ROOT) / p).as_posix(): h for p, h in shared.items()})
        return hashes
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error


def packed_object(root, expected):
    before = input_hashes(root, expected)
    directory = root / input_directory(expected['part'])
    try:
        packed = bytearray((directory / 'backing.bin').read_bytes())
        records = json.loads((directory / 'models.json').read_text())
        if type(records) is not dict or set(records) != {str(e['entry']) for e in expected['entries']}:
            raise ValueError('direct-model source entry set changed')
        spans = []
        for entry in expected['entries']:
            decoded = encode_record(records[str(entry['entry'])])
            if sha(decoded) != entry['decoded_sha256']:
                raise ValueError('direct-model fields no longer reproduce reviewed decoded storage')
            fresh = rzip_bounded.encode_payload(decoded)
            if len(fresh) != entry['rom_end'] - entry['rom_start'] or sha(fresh) != entry['stored_sha256']:
                raise ValueError('direct-model fresh compression differs from reviewed storage')
            spans.append((entry['rom_start'] - expected['rom_start'], fresh))
        if expected['part'] == SHORT_PART:
            manifest, _ = short_inputs(packed, expected)
            source = json.loads((directory / 'short-normals/model.json').read_text())
            decoded = model_short_normals.encode(source)
            fresh = rzip_bounded.encode_payload(decoded)
            if (sha(decoded) != manifest['decoded_sha256'] or sha(fresh) != manifest['stored_sha256']
                    or len(fresh) != manifest['rom_end'] - manifest['rom_start']):
                raise ValueError('short normal model fields differ from reviewed storage')
            spans.append((manifest['rom_start'] - expected['rom_start'], fresh))
        parent = expected['parent']
        index = json.loads((root / directories.input_directory(parent['key']) / 'directory.json').read_text())
        if sha(directories.codec.encode(index)) != parent['directory_sha256']:
            raise ValueError('direct-model source index changed')
        gaps = bank_index_inputs.alignment_spans(index, parent['rom_start'], expected['bank_end'])
        alignment = [[a, b] for a, b in gaps if expected['rom_start'] <= a < b <= expected['rom_end']]
        if alignment != expected['alignment_ranges']:
            raise ValueError('direct-model generated alignment ranges changed')
        spans.extend((a - expected['rom_start'], gaps[a, b]) for a, b in alignment)
        spans.sort()
        ranges = [[expected['rom_start'] + a, expected['rom_start'] + a + len(data)] for a, data in spans]
        if (ranges != owned_ranges(expected) or any(a[1] > b[0] for a, b in zip(ranges, ranges[1:]))
                or any(not expected['rom_start'] <= a < b <= expected['rom_end'] for a, b in ranges)):
            raise ValueError('direct-model generated ownership differs or overlaps')
        for at, fresh in spans:
            packed[at:at + len(fresh)] = fresh
        if sha(packed) != expected['original_sha256']:
            raise ValueError('direct-model output differs from reviewed whole object')
    except (OSError, ValueError, TypeError, KeyError, IndexError) as error:
        raise input_error(directory, expected, str(error)) from error
    if input_hashes(root, expected) != before:
        raise ValueError('direct-model sources changed during packing')
    return bytes(packed), spans, before


def recover_inputs(part, root=ROOT):
    input_directory(part)
    rom, selected = reviewed_objects(root)
    expected, records = next(pair for pair in selected if pair[0]['part'] == part)
    files = input_files(rom, expected, records)
    if part == SHORT_PART:
        files.update({'short-normals/' + p: data for p, data in short_files(files['backing.bin'], expected).items()})
    backup = asset_inputs.recover_directory(root / input_directory(part), root / 'build/assets/direct-models/recovery',
                                           f'us-{part}-', files)
    return {'input_directory': str(root / input_directory(part)), 'backup_directory': backup}


def build_parts(root=ROOT):
    rom, selected = reviewed_objects(root)
    candidates = []
    for expected, records in selected:
        directory = root / input_directory(expected['part'])
        if not directory.exists():
            texture_build.publish_inputs(directory, input_files(rom, expected, records))
        if expected['part'] == SHORT_PART and not (directory / 'short-normals').exists():
            texture_build.publish_inputs(directory / 'short-normals',
                short_files(rom[expected['rom_start']:expected['rom_end']], expected))
        packed, spans, hashes = packed_object(root, expected)
        if packed != rom[expected['rom_start']:expected['rom_end']]:
            raise ValueError('direct-model candidate differs from independent ROM')
        candidates.append((expected, packed, spans, hashes))
    for expected, _, _, hashes in candidates:
        if input_hashes(root, expected) != hashes:
            raise ValueError('direct-model sources changed before publication')
    proofs, receipts = [], {}
    for expected, packed, spans, hashes in candidates:
        name = part_name(expected['part']); output = Path('build/us/direct-models/parts') / (name + '.bin')
        write_if_changed(root / output, packed)
        receipts[name] = asset_receipts.part_record(output=output, payload=packed, source_inputs=hashes,
            input_directory=SOURCE_ROOT, extent=expected, spans=spans)
        proofs.append({**expected, 'rom_ranges': owned_ranges(expected),
                       'source_inputs': hashes, 'rebuilt_bytes': sum(len(data) for _, data in spans),
                       'matches_original': True})
    asset_receipts.write(root, 'direct-models', __file__, receipts)
    write_if_changed(root / 'build/us/direct-models/batch.json', (json.dumps(proofs, indent=2) + '\n').encode())
    return proofs


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('build', 'recover'))
    parser.add_argument('--part', choices=PARTS)
    args = parser.parse_args(argv)
    if (args.command == 'recover') != (args.part is not None):
        parser.error('recover requires --part; build reconstructs all six objects')
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(args.part), indent=2))
        else:
            proof = build_parts()
            print(f"Verified direct auxiliary models: {sum(p['rebuilt_bytes'] for p in proof)} ROM bytes")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
