"""Canonical glyph-record linker inputs rebuilt from editable font sources."""
from pathlib import Path
import json
import sys
import yaml

from build_files import write_if_changed
import font_assets

ROOT = Path(__file__).resolve().parent.parent


def layout_bins(profile: Path) -> tuple[list[tuple[int, str]], int]:
    segments = yaml.safe_load(profile.read_text())['segments']
    index = next(i for i, s in enumerate(segments) if isinstance(s, dict) and s.get('name') == 'font_rle')
    group, following = segments[index:index + 2]
    end = following['start'] if isinstance(following, dict) else following[0]
    if group['type'] != 'group' or group.get('align') != 1 or group.get('subalign') != 1:
        raise ValueError('font must use a byte-aligned YAML group')
    result = []
    for row in group['subsegments']:
        if (len(row) != 3 or row[1] != 'bin' or not row[2].startswith('font/')
                or '..' in Path(row[2]).parts):
            raise ValueError('invalid font YAML split')
        result.append((row[0], row[2]))
    if not result or result[0][0] != group['start'] or len({n for _, n in result}) != len(result):
        raise ValueError('invalid font YAML extent or duplicate input')
    return result, end


def verify_splits(profile: Path, rom: bytes, layout: dict) -> list[tuple[int, int, str]]:
    glyphs, padding = font_assets.parse_font_table(rom, layout['font_start'], layout['font_count'],
                                                  layout['font_storage_end'])
    cursor = layout['font_start']
    expected = []
    for index, glyph in enumerate(glyphs):
        expected.append((cursor, f'font/glyphs/{index:04d}'))
        cursor += 8 + len(glyph.encoded)
    if padding:
        expected.append((cursor, 'font/padding'))
    actual, end = layout_bins(profile)
    if actual != expected or end != layout['font_storage_end']:
        raise ValueError('font YAML splits differ from original record boundaries')
    return [(start, stop, name) for (start, name), stop in
            zip(actual, [s for s, _ in actual[1:]] + [end], strict=True)]


def build_parts(root: Path = ROOT) -> list[tuple[int, int, str]]:
    _, rom, _, layout, _, _ = font_assets.load_profile_fonts('us', None)
    ranges = verify_splits(root / 'config/profiles/us.yaml', rom, layout)
    packed = font_assets.build_fonts('us', root / 'build/fonts/us', root / 'build/us/fonts/font_rle.bin')
    # Fixed YAML records must stay individually bounded even when two edits
    # would cancel out in the total encoded length.
    glyphs, padding = font_assets.parse_font_table(packed, 0, layout['font_count'], len(packed))
    sizes = [8 + len(g.encoded) for g in glyphs] + ([padding] if padding else [])
    if sizes != [end - start for start, end, _ in ranges]:
        raise ValueError('edited glyph changes a fixed YAML record extent')
    for start, end, name in ranges:
        path = root / 'build/us/fonts/parts' / (name + '.bin')
        path.parent.mkdir(parents=True, exist_ok=True)
        write_if_changed(path, packed[start - layout['font_start']:end - layout['font_start']])
    return ranges


if __name__ == '__main__':
    if sys.argv[1:] == ['list-bins']:
        rows, _ = layout_bins(ROOT / 'config/profiles/us.yaml')
        print(' '.join('assets/' + name + '.bin' for _, name in rows))
    elif sys.argv[1:] == ['build-parts']:
        print(f'Built {len(build_parts())} font inputs from US YAML')
    else:
        raise SystemExit('Use list-bins or build-parts')
