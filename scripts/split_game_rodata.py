#!/usr/bin/env python3
"""Split reviewed discontiguous US jump tables without changing instructions.

REL instruction addends retain their original offsets. Each table's HI16/LO16
references use a linker-defined base (runtime address minus original offset).
Table R_MIPS_32 relocations still refer to the original .text symbol.
"""
from __future__ import annotations

import argparse
from pathlib import Path
import struct

# (object extent, [(offset, payload size, HI16 site, LO16 site), ...])
# ROM provenance and dispatch bounds: docs/evidence/automation_jump_tables.md.
LAYOUTS = {
    'game_16EE20': (0x80, [(0, 0x40, 0x3B4, 0x3BC), (0x40, 0x38, 0x29A0, 0x29A8)]),
    'game_1C1150': (0x40, [(0, 0x14, 0x6A4, 0x6AC), (0x14, 0x14, 0x718, 0x720), (0x28, 0x14, 0xB40, 0xB48)]),
}


def split(data: bytes, unit: str) -> bytes:
    if len(data) < 52 or data[:7] != b'\x7fELF\x01\x02\x01':
        raise ValueError('expected big-endian ELF32')
    header = list(struct.unpack_from('>16sHHIIIIIHHHHHH', data))
    if header[1:3] != [1, 8] or header[10] or header[11] != 40:
        raise ValueError('expected relocatable MIPS object without program headers')
    if header[6] + header[12] * 40 > len(data):
        raise ValueError('truncated section table')
    sections = [list(struct.unpack_from('>10I', data, header[6] + i * 40)) for i in range(header[12])]

    def payload(index):
        section = sections[index]
        if section[1] == 8:
            return b''
        start, size = section[4:6]
        if start + size > len(data):
            raise ValueError('truncated section')
        return data[start:start + size]

    contents = [payload(i) for i in range(len(sections))]
    original_contents = contents.copy()
    names = contents[header[13]]
    decoded = [names[s[0]:].split(b'\0', 1)[0].decode() for s in sections]
    ro = decoded.index('.rodata')
    text = decoded.index('.text')
    sym = decoded.index('.symtab')
    relro = decoded.index('.rel.rodata')
    extent, tables = LAYOUTS[unit]
    if sections[ro][5] != extent or sections[ro][1] != 1:
        raise ValueError('reviewed rodata extent changed')
    end = tables[-1][0] + tables[-1][1]
    if any(contents[ro][end:]):
        raise ValueError('nonzero object alignment bytes')
    if sections[sym][9] != 16 or len(contents[sym]) % 16:
        raise ValueError('invalid symbol table')
    symbols = [list(struct.unpack_from('>IIIBBH', contents[sym], i)) for i in range(0, len(contents[sym]), 16)]
    ro_symbols = [i for i, s in enumerate(symbols) if s[5] == ro]
    if len(ro_symbols) != 1 or symbols[ro_symbols[0]][1] != 0 or symbols[ro_symbols[0]][3] != 3:
        raise ValueError('expected only the rodata section symbol')
    ro_symbol = ro_symbols[0]
    strings = bytearray(contents[sections[sym][6]])
    names = bytearray(names)
    base_symbols = []
    prefix = unit.removeprefix('game_').lower()
    for start, size, hi, lo in tables:
        name = f'__game_rodata_{prefix}_{start:x}_base'.encode() + b'\0'
        base_symbols.append(len(symbols))
        symbols.append([len(strings), 0, 0, 0x10, 0, 0])  # undefined global
        strings.extend(name)
    expected = {site: (kind, base_symbols[i], start) for i, (start, size, hi, lo) in enumerate(tables)
                for site, kind in ((hi, 5), (lo, 6))}
    seen = set()
    for i, section in enumerate(sections):
        if section[1] == 4:
            raise ValueError('RELA relocations are unsupported')
        if section[1] != 9:
            continue
        if section[6] != sym or section[9] != 8 or len(contents[i]) % 8:
            raise ValueError('invalid REL section')
        rel = bytearray(contents[i])
        for pos in range(0, len(rel), 8):
            location, info = struct.unpack_from('>II', rel, pos)
            if info >> 8 != ro_symbol:
                continue
            if section[7] != text or location not in expected or location in seen:
                raise ValueError('unreviewed reference to rodata')
            kind, symbol, start = expected[location]
            if info & 255 != kind or location + 4 > len(contents[text]):
                raise ValueError('unexpected table relocation')
            instruction = struct.unpack_from('>I', contents[text], location)[0]
            if instruction & 0xFFFF != (0 if kind == 5 else start):
                raise ValueError('table instruction addend changed')
            struct.pack_into('>I', rel, pos + 4, symbol << 8 | kind)
            seen.add(location)
        contents[i] = bytes(rel)
    if seen != expected.keys():
        raise ValueError('missing reviewed table references')
    table_relocations = [struct.unpack_from('>II', contents[relro], i) for i in range(0, len(contents[relro]), 8)]
    if [off for off, _ in table_relocations] != list(range(0, end, 4)):
        raise ValueError('table relocation coverage changed')
    for _, info in table_relocations:
        if info & 255 != 2 or info >> 8 >= len(symbols) or symbols[info >> 8][5] != text:
            raise ValueError('jump table must contain only relocated text pointers')
    for start, size, _, _ in tables:
        section_name = f'.rodata.{prefix}_{start:x}'
        name_offset = len(names)
        names.extend(section_name.encode() + b'\0')
        index = len(sections)
        sections.append([name_offset, 1, sections[ro][2], 0, 0, size, 0, 0, 4, 0])
        contents.append(contents[ro][start:start + size])
        name_offset = len(names)
        names.extend(('.rel' + section_name).encode() + b'\0')
        relocations = b''.join(struct.pack('>II', off - start, info) for off, info in table_relocations if start <= off < start + size)
        sections.append([name_offset, 9, sections[relro][2], 0, 0, len(relocations), sym, index, 4, 8])
        contents.append(relocations)
    contents[ro] = contents[relro] = b''
    symbols[ro_symbol][2] = 0
    contents[sym] = b''.join(struct.pack('>IIIBBH', *s) for s in symbols)
    contents[sections[sym][6]] = bytes(strings)
    contents[header[13]] = bytes(names)
    # Keep untouched sections at their original file offsets: MIPS .mdebug
    # contains file-relative ECOFF offsets that must not move with ELF metadata.
    result = bytearray(data)
    for i, (section, content) in enumerate(zip(sections, contents)):
        if section[1] == 8:
            continue
        if i < len(original_contents) and content == original_contents[i]:
            continue
        alignment = max(1, section[8])
        result.extend(bytes((-len(result)) % alignment))
        section[4], section[5] = len(result), len(content)
        result.extend(content)
    result.extend(bytes((-len(result)) % 4))
    header[6], header[12] = len(result), len(sections)
    result.extend(b''.join(struct.pack('>10I', *s) for s in sections))
    struct.pack_into('>16sHHIIIIIHHHHHH', result, 0, *header)
    return bytes(result)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    args = parser.parse_args()
    try:
        output = split(args.object.read_bytes(), args.object.stem)
        temporary = args.object.with_suffix('.rodata.tmp')
        temporary.write_bytes(output)
        temporary.replace(args.object)
    except (ValueError, KeyError, OSError, struct.error) as error:
        parser.exit(1, f'error: {error}\n')


if __name__ == '__main__':
    main()
