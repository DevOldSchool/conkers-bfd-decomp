"""Generate standalone model-bank padding from typed directory boundaries."""
from __future__ import annotations

import json
from pathlib import Path

try:
    from scripts import asset_directory_build as directories, asset_receipts
    from scripts.build_files import write_if_changed
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import asset_directory_build as directories
    import asset_receipts
    from build_files import write_if_changed
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
BANK_KEYS = ('bank01', 'bank03', 'bank04', 'bank09')


def selected_parts(root=ROOT):
    """Select only complete, short raw objects; never split a preserved object."""
    segments = load_profile(root / 'config/profiles/us.yaml')['segments']
    parts = []
    for segment, following in zip(segments, segments[1:]):
        if not isinstance(segment, dict) or segment.get('type') != 'group':
            continue
        end = following['start'] if isinstance(following, dict) else following[0]
        rows = segment['subsegments']
        for row, after in zip(rows, rows[1:] + [[end]]):
            if not (isinstance(row, list) and len(row) == 3 and row[1] == 'bin'
                    and row[2].startswith('models/raw/')):
                continue
            start, stop = row[0], after[0]
            if 0 < stop - start < 8 and stop % 8 == 0:
                parts.append({'part': row[2], 'rom_start': start, 'rom_end': stop})
    return parts


def alignment_spans(source, start, end):
    return directories.bank_index_inputs.alignment_spans(source, start, end)


def reviewed(root=ROOT):
    # This authenticates the complete native directory-loader spans and US ROM.
    rom, parents = directories.reviewed_directories(root)
    outer, bank_index = next(row for row in parents if row[0]['key'] == 'outer')
    available = {}
    for parent, source in parents:
        if parent['key'] not in BANK_KEYS:
            continue
        bank = bank_index['entries'][int(parent['key'][4:], 16)]
        start = outer['rom_start'] + bank['relative_offset']
        end = start + bank['stored_size']
        if start != parent['rom_start']:
            raise ValueError('model bank and directory origins disagree')
        for extent, fresh in alignment_spans(source, start, end).items():
            if extent in available:
                raise ValueError('overlapping model-bank alignment')
            available[extent] = (parent, end, fresh)
    parts = []
    for part in selected_parts(root):
        extent = part['rom_start'], part['rom_end']
        if extent not in available:
            raise ValueError('short raw object is not a complete model directory gap')
        parent, end, fresh = available[extent]
        if fresh != rom[extent[0]:extent[1]]:
            raise ValueError('model alignment contains nonzero bytes')
        parts.append({**part, 'parent': parent, 'bank_end': end})
    return rom, parts


def input_hashes(root, part):
    parent = part['parent']
    return directories.input_hashes(root / directories.input_directory(parent['key']), parent)


def packed_part(root, part):
    parent = part['parent']
    directory = root / directories.input_directory(parent['key'])
    before = input_hashes(root, part)
    source = json.loads((directory / 'directory.json').read_text())
    table = directories.codec.encode(source)
    if directories.sha256(table) != parent['directory_sha256']:
        raise directories.input_error(directory, parent, 'model directory fields changed')
    spans = alignment_spans(source, parent['rom_start'], part['bank_end'])
    extent = part['rom_start'], part['rom_end']
    if extent not in spans:
        raise ValueError('model padding no longer follows its source directory')
    if input_hashes(root, part) != before:
        raise ValueError('model alignment sources changed during packing')
    return spans[extent], before


def build_parts(root=ROOT):
    rom, parts = reviewed(root)
    candidates = []
    for part in parts:
        packed, hashes = packed_part(root, part)
        if packed != rom[part['rom_start']:part['rom_end']]:
            raise ValueError('model alignment differs from independent ROM')
        candidates.append((part, packed, hashes))
    for part, _, hashes in candidates:
        if input_hashes(root, part) != hashes:
            raise ValueError('model alignment sources changed before publication')
    receipts = {}
    for part, packed, hashes in candidates:
        output = Path('build/us/model-alignment/parts') / (part['part'] + '.bin')
        write_if_changed(root / output, packed)
        receipts[part['part']] = asset_receipts.part_record(
            output=output, payload=packed, source_inputs=hashes,
            input_directory=directories.input_directory(part['parent']['key']), extent=part)
    asset_receipts.write(root, 'model-alignment', __file__, receipts)
    return parts


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('list-parts', 'build'))
    args = parser.parse_args(argv)
    try:
        if args.command == 'list-parts':
            print(' '.join(part['part'] for part in selected_parts()))
        else:
            parts = build_parts()
            print(f'Verified {len(parts)} standalone model alignment parts: '
                  f'{sum(p["rom_end"] - p["rom_start"] for p in parts)} bytes')
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
