"""Exact whole-unit proof for debugger aliases after initialized-data integration."""
import json
from pathlib import Path
import re

import data_boundaries
import debugger_layout
from elf_sections import sections
import layout_check
import rom_span


class CandidateMismatch(ValueError):
    """Candidate cannot use linked alias normalization; use the symbolic differ."""


def relocation_addends_fit(obj, private: set[int]) -> bool:
    """Validate encoded REL addends as well as symbol metadata before linking."""
    highs = {}
    used = set()
    for (location, offset), (kind, target) in sorted(obj.relocations.items()):
        name, value, _, section = target
        if offset % 4 or offset < 0 or offset + 4 > obj.sections[location][5]:
            return False
        word = obj.word(location, offset)
        if kind == 5:
            highs.setdefault((location, target), []).append((offset, word & 0xFFFF))
            continue
        if kind == 6:
            pairs = highs.get((location, target))
            if not pairs:
                return False
            low = (word & 0xFFFF) - (0x10000 if word & 0x8000 else 0)
            addends = [((high << 16) + low) & 0xFFFFFFFF for _, high in pairs]
            used.update((location, high_offset) for high_offset, _ in pairs)
        elif kind == 2:
            addends = [word]
        elif kind == 4:
            addends = [(word & 0x03FFFFFF) << 2]
        else:
            return False
        for addend in addends:
            if section in private:
                signed = addend - (0x100000000 if addend & 0x80000000 else 0)
                if not 0 <= value + signed < obj.sections[section][5]:
                    return False
            elif addend and name.startswith('func_'):
                return False
            # External data aliases can legitimately encode an offset, such as
            # D_80042A10 + 0x40. Their effective address is checked by the full
            # linked-ROM comparison; private section bounds are known above.
    return all((location, offset) in used for (location, _), pairs in highs.items()
               for offset, _ in pairs)


def context(root: Path, obj, symbol: str, start: int) -> dict | None:
    if not (root / 'config/profiles/us.yaml').is_file():
        return None
    functions = json.loads((root / 'progress/functions.json').read_text())['functions']
    members = [f for f in functions if f.get('overlay') == 'debugger' and f['regions']['us']['symbol'] == symbol]
    if len(members) != 1:
        raise ValueError('debugger data alias requires one registered function')
    entry = members[0]
    units = json.loads((root / 'progress/source_units.json').read_text())['source_units']
    units = [u for u in units if u['source'] == entry['source'] and entry['symbol'] in u['functions']]
    mappings = [m for m in data_boundaries.debugger_source_mappings(root) if m['source'] == entry['source']]
    if not mappings:
        return None
    if len(units) != 1 or not units[0].get('boundary_evidence', {}).get('us', {}).get('reviewed'):
        raise ValueError('debugger data alias needs reviewed unit boundaries')
    unit = units[0]
    try:
        measured, extent, alignment = layout_check.archived_object_layout(obj.data)
        layout_check.validate_layout(entry, unit, measured, extent, alignment, 'us', root=root)
    except layout_check.LayoutError as error:
        raise CandidateMismatch(str(error)) from error
    origin = debugger_layout.load(root)['origin']
    text_start = origin + int(unit['regions']['us']['start'], 0)
    if int(entry['regions']['us']['vram'], 0) != start:
        raise ValueError('debugger alias address differs from registration')
    parsed = sections(obj.data, 1)
    placements = {}
    private = set()
    for mapping in mappings:
        name = mapping['input']
        if name not in parsed:
            raise CandidateMismatch('debugger candidate is missing ' + name)
        header, _ = parsed[name]
        if header[1] != 1 or header[5] != mapping['end'] - mapping['start'] or not header[2] & 2:
            raise CandidateMismatch('debugger candidate data differs from allocated placement')
        placements[name] = (mapping['start'], 1)
        private.add(obj.sections.index(header))
    allocated = {name for name, (header, _) in parsed.items()
                 if header[2] & 2 and header[5] and name not in ('.text', '.reginfo', '.MIPS.abiflags')}
    if allocated != set(placements):
        raise CandidateMismatch('unmapped debugger candidate storage')
    text = obj.sections.index(parsed['.text'][0])
    definitions = {}
    for _, (kind, target) in obj.relocations.items():
        name, value, size, section = target
        if section in private:
            if kind not in (2, 5, 6) or not 0 <= value < obj.sections[section][5] or value + size > obj.sections[section][5]:
                raise CandidateMismatch('invalid debugger data relocation')
        elif section == text:
            if kind not in (2, 4) or not re.fullmatch(r'func_[0-9A-Fa-f]{8}', name) or text_start + value != int(name[5:], 16):
                raise CandidateMismatch('debugger defined text relocation changed its original address')
        elif section == 0:
            match = re.fullmatch(r'(?:D|func|jtbl)_([0-9A-Fa-f]{8})', name)
            if kind not in (2, 4, 5, 6) or match is None or value:
                raise CandidateMismatch('unsupported debugger external relocation')
            definitions[name] = int(match[1], 16)
        else:
            raise CandidateMismatch('unsupported debugger defined relocation')
    if not relocation_addends_fit(obj, private):
        raise CandidateMismatch('debugger candidate relocation addend exceeds reviewed bounds')
    return {'placements': placements, 'definitions': definitions, 'text_start': text_start,
            'text_end': text_start + extent, 'mappings': mappings}


def verify(root: Path, elf: Path, layout: dict) -> bool:
    code, data, code_start, data_start, _ = rom_span.debugger_image(root)
    actual = sections(elf.read_bytes(), 2)
    a, b = layout['text_start'] - code_start, layout['text_end'] - code_start
    if a < 0 or b > len(code) or actual.get('.text', (None, None))[1] != code[a:b]:
        return False
    for mapping in layout['mappings']:
        a, b = mapping['start'] - data_start, mapping['end'] - data_start
        if a < 0 or b > len(data) or actual.get(mapping['input'], (None, None))[1] != data[a:b]:
            return False
    return True
