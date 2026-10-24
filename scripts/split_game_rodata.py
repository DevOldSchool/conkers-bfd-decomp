#!/usr/bin/env python3
"""Split reviewed discontiguous US rodata ranges without changing instructions.

A range is a jump table or a float literal pool. REL instruction addends retain
their original offsets. Each range's HI16/LO16 references use a linker-defined
base (runtime address minus original offset). Table R_MIPS_32 relocations still
refer to the original .text symbol; literal pools have no data relocations.
"""
from __future__ import annotations

import argparse
from pathlib import Path
import struct

# (object extent, [range, ...]) with ranges tiling the object rodata in order.
# A table range is (offset, payload size, HI16 site, LO16 site) for its one
# reviewed dispatch. A literal pool is (offset, payload size): its HI16/LO16
# sites are every .text reference whose LO16 addend lies inside the pool, each
# HI16 joining the next LO16 as in the REL pairing convention.
# ROM provenance and dispatch bounds: docs/evidence/data-layout/automation_jump_tables.md;
# literal pools and the blood and game_1C1150 additions:
# docs/evidence/data-layout/game_rodata_literal_sub_pools.md.
LAYOUTS = {
    'game_B4080': (0x200, [(0, 0x20, 0x3028, 0x3030), (0x20, 0xFC, 0x7B10, 0x7B18),
                              (0x11C, 0xE4, 0x7BD4, 0x7BDC)]),
    'game_16EE20': (0x2B0, [(0, 0xB4, 0x2B8, 0x2C0), (0xB4, 0x164, 0x2D8, 0x2E0),
                              (0x218, 0x40, 0x3B4, 0x3BC), (0x258, 0x14, 0x284C, 0x2854),
                              (0x26C, 0x38, 0x29A0, 0x29A8)]),
    'game_1C1150': (0x60, [(0, 0x14, 0x6A4, 0x6AC), (0x14, 0x14, 0x718, 0x720), (0x28, 0x14, 0x78C, 0x794),
                              (0x3C, 0xC), (0x48, 0x14, 0xB40, 0xB48)]),
    'game_83300': (0x20, [(0, 0xC), (0xC, 0x8)]),
    'blood': (0x280, [(0, 0x204, 0x1C, 0x24), (0x204, 0x5C, 0x3C, 0x44), (0x260, 0x20)]),
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
    relro = decoded.index('.rel.rodata') if '.rel.rodata' in decoded else None
    extent, ranges = LAYOUTS[unit]
    if sections[ro][5] != extent or sections[ro][1] != 1:
        raise ValueError('reviewed rodata extent changed')
    end = 0
    for item in ranges:
        if len(item) not in (2, 4) or item[0] != end or item[1] <= 0 or item[1] % 4:
            raise ValueError('reviewed rodata ranges must tile the object rodata')
        end += item[1]
    if end > extent:
        raise ValueError('reviewed rodata ranges exceed the object extent')
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
    for start, *_ in ranges:
        name = f'__game_rodata_{prefix}_{start:x}_base'.encode() + b'\0'
        base_symbols.append(len(symbols))
        symbols.append([len(strings), 0, 0, 0x10, 0, 0])  # undefined global
        strings.extend(name)
    expected = {site: (kind, base_symbols[i], item[0]) for i, item in enumerate(ranges) if len(item) == 4
                for site, kind in ((item[2], 5), (item[3], 6))}
    pools = [(item[0], item[0] + item[1], base_symbols[i]) for i, item in enumerate(ranges) if len(item) == 2]
    seen = set()
    for i, section in enumerate(sections):
        if section[1] == 4:
            raise ValueError('RELA relocations are unsupported')
        if section[1] != 9:
            continue
        if section[6] != sym or section[9] != 8 or len(contents[i]) % 8:
            raise ValueError('invalid REL section')
        rel = bytearray(contents[i])
        pending, group = [], None
        for pos in range(0, len(rel), 8):
            location, info = struct.unpack_from('>II', rel, pos)
            if info >> 8 != ro_symbol:
                continue
            if section[7] != text or location in seen or location + 4 > len(contents[text]):
                raise ValueError('unreviewed reference to rodata')
            if location not in expected:
                # Literal pool load: lui %hi(.rodata) ... lwc1 %lo(.rodata+offset).
                kind = info & 255
                immediate = struct.unpack_from('>I', contents[text], location)[0] & 0xFFFF
                if kind == 5 and immediate == 0:
                    pending.append(pos)
                elif kind == 6:
                    pool = [p for p in pools if p[0] <= immediate < p[1] and not immediate % 4]
                    if not pool or not pending and group != pool[0]:
                        raise ValueError('unreviewed reference to rodata')
                    group = pool[0]
                    for site in pending + [pos]:
                        struct.pack_into('>I', rel, site + 4, group[2] << 8 | struct.unpack_from('>I', rel, site + 4)[0] & 255)
                    pending = []
                else:
                    raise ValueError('unreviewed reference to rodata')
                seen.add(location)
                continue
            if pending:
                raise ValueError('unpaired literal HI16 relocation')
            kind, symbol, start = expected[location]
            if info & 255 != kind or location + 4 > len(contents[text]):
                raise ValueError('unexpected table relocation')
            instruction = struct.unpack_from('>I', contents[text], location)[0]
            if instruction & 0xFFFF != (0 if kind == 5 else start):
                raise ValueError('table instruction addend changed')
            struct.pack_into('>I', rel, pos + 4, symbol << 8 | kind)
            seen.add(location)
        if pending:
            raise ValueError('unpaired literal HI16 relocation')
        contents[i] = bytes(rel)
    if not expected.keys() <= seen:
        raise ValueError('missing reviewed table references')
    relocated = b'' if relro is None else contents[relro]
    table_relocations = [struct.unpack_from('>II', relocated, i) for i in range(0, len(relocated), 8)]
    table_words = [off for item in ranges if len(item) == 4 for off in range(item[0], item[0] + item[1], 4)]
    if [off for off, _ in table_relocations] != table_words:
        raise ValueError('table relocation coverage changed')
    for _, info in table_relocations:
        if info & 255 != 2 or info >> 8 >= len(symbols) or symbols[info >> 8][5] != text:
            raise ValueError('jump table must contain only relocated text pointers')
    for start, size, *table in ranges:
        section_name = f'.rodata.{prefix}_{start:x}'
        name_offset = len(names)
        names.extend(section_name.encode() + b'\0')
        index = len(sections)
        sections.append([name_offset, 1, sections[ro][2], 0, 0, size, 0, 0, 4, 0])
        contents.append(contents[ro][start:start + size])
        if not table:
            continue
        name_offset = len(names)
        names.extend(('.rel' + section_name).encode() + b'\0')
        relocations = b''.join(struct.pack('>II', off - start, info) for off, info in table_relocations if start <= off < start + size)
        sections.append([name_offset, 9, sections[relro][2], 0, 0, len(relocations), sym, index, 4, 8])
        contents.append(relocations)
    contents[ro] = b''
    if relro is not None:
        contents[relro] = b''
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
