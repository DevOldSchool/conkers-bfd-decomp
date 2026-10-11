"""Debugger layout derived from the reference image and canonical data ownership."""
import json
from pathlib import Path

import yaml
import data_boundaries


def load(root: Path) -> dict:
    segments = yaml.safe_load((root / 'config/reference/us.yaml').read_text())['segments']
    found = [(i, s) for i, s in enumerate(segments) if isinstance(s, dict) and s.get('name') == 'debugger']
    if len(found) != 1 or found[0][0] + 1 >= len(segments):
        raise ValueError('debugger layout requires one bounded reference image')
    index, segment = found[0]
    following = segments[index + 1]
    end = following['start'] if isinstance(following, dict) else following[0]
    parts = segment['subsegments']
    if len(parts) != 2 or parts[0][1] != 'asm' or parts[1][1] != 'data':
        raise ValueError('debugger reference needs text followed by loaded data')
    start, base, split = segment['start'], segment['vram'], parts[1][0]
    if not start == parts[0][0] < split < end:
        raise ValueError('invalid debugger reference bounds')
    origin = base - start
    mappings = data_boundaries.debugger_source_mappings(root)
    context = []
    cursor = origin + split
    for section in ('.data', '.rodata'):
        spans = sorted((m for m in mappings if m['input'] == section), key=lambda m: m['start'])
        first = cursor
        for span in spans:
            if span['start'] != cursor or span['end'] <= cursor:
                raise ValueError('debugger data mappings are not contiguous with the reference')
            cursor = span['end']
        if cursor == first:
            raise ValueError('debugger reference context section is missing')
        context.append({'name': 'context_' + section[1:], 'section': section,
                        'start': first, 'end': cursor, 'rom_start': first - origin})
    if cursor != origin + end:
        raise ValueError('debugger data mappings do not cover the reference image')
    return {'rom_start': start, 'code_end': split, 'rom_end': end, 'vram': base,
            'origin': origin, 'context': context, 'mappings': mappings}


def ui(root: Path) -> dict:
    layout = load(root)
    spans = [s for s in layout['mappings'] if s['source'] == 'src/done/debugger/debugger_0000.c'
             and s['input'] == '.rodata']
    if len(spans) != 1:
        raise ValueError('debugger UI needs one reviewed rodata placement')
    span = spans[0]
    evidence = json.loads((root / 'docs/evidence/debugger/us_debugger_data_objects.json').read_text())
    strings = [s for s in evidence['strings'] if span['start'] <= int(s['start'], 0) < span['end']]
    if not strings:
        raise ValueError('debugger UI strings have no reviewed boundaries')
    split = min(int(s['start'], 0) for s in strings)
    if split - span['start'] != 96 * 8:
        raise ValueError('debugger glyph extent differs from its reviewed format')
    return {**span, 'strings_start': split, 'strings': strings, 'origin': layout['origin']}
