from __future__ import annotations

import struct
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / 'scripts'))
import split_game_rodata as splitter


def unpack(data):
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    sections = [struct.unpack_from('>10I', data, header[6] + i * 40) for i in range(header[12])]
    strings = sections[header[13]]
    names = data[strings[4]:strings[4] + strings[5]]
    return {names[s[0]:].split(b'\0')[0].decode(): (s, data[s[4]:s[4] + s[5]]) for s in sections}


# Two tables, separated in ROM, contiguous in this compiler object.
TABLE_TEXT = (0x3C010000, 0x8C220000, 0x3C010000, 0x8C220008)
TABLE_RELOCATIONS = ((0, 5), (4, 6), (8, 5), (12, 6))
# One table, then a literal pool: a lui shared by two lwc1 loads, and a second
# lui/lwc1 pair reloading the pool's second literal.
POOL_TEXT = (0x3C010000, 0x8C220000, 0x3C010000, 0xC4240008, 0xC426000C, 0x3C010000, 0xC428000C)
POOL_RELOCATIONS = ((0, 5), (4, 6), (8, 5), (12, 6), (16, 6), (20, 5), (24, 6))
POOL_RODATA = struct.pack('>4I', 0, 4, 0x3F800000, 0x40000000) + bytes(16)


def fixture(text=TABLE_TEXT, relocations=TABLE_RELOCATIONS,
            rodata=struct.pack('>4I', 0, 4, 8, 12) + bytes(16), table_words=range(0, 16, 4)):
    names = b'\0.text\0.rodata\0.symtab\0.strtab\0.rel.text\0.rel.rodata\0.shstrtab\0'
    symbols = bytes(16) + struct.pack('>IIIBBH', 0, 0, 16, 3, 0, 1) + struct.pack('>IIIBBH', 0, 0, 32, 3, 0, 2)
    payloads = [b'', struct.pack(f'>{len(text)}I', *text), rodata, symbols, b'\0',
                b''.join(struct.pack('>II', offset, 2 << 8 | kind) for offset, kind in relocations),
                b''.join(struct.pack('>II', offset, 1 << 8 | 2) for offset in table_words or ()), names]
    specs = [('', 0, 0, 0, 0, 0), ('.text', 1, 6, 0, 0, 0), ('.rodata', 1, 2, 0, 0, 0),
             ('.symtab', 2, 0, 4, 3, 16), ('.strtab', 3, 0, 0, 0, 0),
             ('.rel.text', 9, 0, 3, 1, 8), ('.rel.rodata', 9, 0, 3, 2, 8), ('.shstrtab', 3, 0, 0, 0, 0)]
    if table_words is None:
        # A literal-only unit has no data relocation section.
        del payloads[6], specs[6]
    result = bytearray(52)
    sections = []
    for (name, kind, flags, link, info, entsize), payload in zip(specs, payloads):
        result.extend(bytes(-len(result) % 4))
        sections.append((names.index(name.encode() + b'\0'), kind, flags, 0, len(result), len(payload), link, info, 4, entsize))
        result.extend(payload)
    result.extend(bytes(-len(result) % 4))
    table = len(result)
    result.extend(b''.join(struct.pack('>10I', *s) for s in sections))
    struct.pack_into('>16sHHIIIIIHHHHHH', result, 0, b'\x7fELF\x01\x02\x01' + bytes(9), 1, 8, 1, 0, 0, table, 0, 52, 0, 0, 40,
                     len(sections), len(sections) - 1)
    return bytes(result)


def resolve(after, bases):
    """Return each HI16/LO16 site's (base symbol, linked address) for linker bases."""
    relocations = list(struct.iter_unpack('>II', after['.rel.text'][1]))
    return [(info >> 8, bases[info >> 8] + (struct.unpack_from('>I', after['.text'][1], pos)[0] & 0xFFFF))
            for pos, info in relocations if info & 255 == 6]


class SplitRodataTests(unittest.TestCase):
    def run_split(self, data):
        with patch.dict(splitter.LAYOUTS, {'game_test': (32, [(0, 8, 0, 4), (8, 8, 8, 12)])}):
            return splitter.split(data, 'game_test')

    def test_split_preserves_instructions_and_relocated_table_contents(self):
        original = fixture()
        before, after = unpack(original), unpack(self.run_split(original))
        self.assertEqual(before['.text'][1], after['.text'][1])
        self.assertEqual(before['.text'][0][4], after['.text'][0][4])
        self.assertEqual(b'', after['.rodata'][1])
        self.assertEqual(before['.rodata'][1][:8], after['.rodata.test_0'][1])
        self.assertEqual(before['.rodata'][1][8:16], after['.rodata.test_8'][1])
        self.assertEqual(before['.rel.rodata'][1][:16], after['.rel.rodata.test_0'][1])
        self.assertEqual(before['.rel.rodata'][1][:16], after['.rel.rodata.test_8'][1])
        # Instruction addends remain 0 / 8. Linker base bindings recover two
        # deliberately discontiguous runtime addresses without rewriting code.
        relocs = list(struct.iter_unpack('>II', after['.rel.text'][1]))
        self.assertEqual([3, 3, 4, 4], [info >> 8 for _, info in relocs])
        bases = {3: 0x80001000, 4: 0x80003000 - 8}
        for pos, info in (relocs[1], relocs[3]):
            addend = struct.unpack_from('>I', after['.text'][1], pos)[0] & 0xFFFF
            self.assertEqual(0x80001000 if pos == 4 else 0x80003000, bases[info >> 8] + addend)

    def test_rejects_nonzero_padding_changed_addends_and_nontext_table_relocations(self):
        original = fixture()
        sections = unpack(original)
        for offset in (sections['.rodata'][0][4] + 16, sections['.text'][0][4] + 15,
                       sections['.rel.rodata'][0][4] + 7):
            with self.subTest(offset=offset):
                changed = bytearray(original)
                changed[offset] ^= 1
                with self.assertRaises(ValueError):
                    self.run_split(bytes(changed))

    def test_rejects_truncated_or_wrong_format_object(self):
        for data in (b'', fixture()[:80], b'not ELF' + fixture()[7:]):
            with self.assertRaises(ValueError):
                self.run_split(data)


class SplitLiteralPoolTests(unittest.TestCase):
    def run_split(self, data, ranges=((0, 8, 0, 4), (8, 8)), extent=32):
        with patch.dict(splitter.LAYOUTS, {'game_test': (extent, list(ranges))}):
            return splitter.split(data, 'game_test')

    def test_pool_sites_use_pool_base_and_keep_instructions(self):
        original = fixture(POOL_TEXT, POOL_RELOCATIONS, POOL_RODATA, range(0, 8, 4))
        before, after = unpack(original), unpack(self.run_split(original))
        self.assertEqual(before['.text'][1], after['.text'][1])
        self.assertEqual(before['.rodata'][1][8:16], after['.rodata.test_8'][1])
        self.assertNotIn('.rel.rodata.test_8', after)
        self.assertEqual(before['.rel.rodata'][1], after['.rel.rodata.test_0'][1])
        relocs = list(struct.iter_unpack('>II', after['.rel.text'][1]))
        self.assertEqual([3, 3, 4, 4, 4, 4, 4], [info >> 8 for _, info in relocs])
        self.assertEqual([kind for _, kind in POOL_RELOCATIONS], [info & 255 for _, info in relocs])
        # The pool links at 0x80003000 although it followed the table in the object.
        bases = {3: 0x80001000, 4: 0x80003000 - 8}
        self.assertEqual([(3, 0x80001000), (4, 0x80003000), (4, 0x80003004), (4, 0x80003004)],
                         resolve(after, bases))

    def test_literal_only_unit_without_data_relocations(self):
        text = (0x3C010000, 0xC4240000, 0x3C010000, 0xC4260004)
        relocations = ((0, 5), (4, 6), (8, 5), (12, 6))
        original = fixture(text, relocations, struct.pack('>2I', 0x3F800000, 0x40000000) + bytes(8), None)
        after = unpack(self.run_split(original, ((0, 4), (4, 4)), 16))
        self.assertEqual(struct.pack('>I', 0x40000000), after['.rodata.test_4'][1])
        self.assertNotIn('.rel.rodata', after)
        bases = {3: 0x80001000, 4: 0x80002000 - 4}
        self.assertEqual([(3, 0x80001000), (4, 0x80002000)], resolve(after, bases))

    def test_rejects_unowned_unpaired_or_cross_pool_literal_references(self):
        cases = {
            # LO16 addend in the table range at a site not reviewed for it.
            'table addend': (POOL_TEXT[:3] + (0xC4240004,) + POOL_TEXT[4:], POOL_RELOCATIONS),
            # A final HI16 without a following LO16.
            'unpaired HI16': (POOL_TEXT + (0x3C010000,), POOL_RELOCATIONS + ((28, 5),)),
            # A nonzero HI16 addend.
            'HI16 addend': (POOL_TEXT[:2] + (0x3C010001,) + POOL_TEXT[3:], POOL_RELOCATIONS),
            # Data relocation inside the literal pool.
            'pool data relocation': (POOL_TEXT, POOL_RELOCATIONS, range(0, 12, 4)),
        }
        for name, (text, relocations, *words) in cases.items():
            with self.subTest(name):
                data = fixture(text, relocations, POOL_RODATA, words[0] if words else range(0, 8, 4))
                with self.assertRaises(ValueError):
                    self.run_split(data)
        # A LO16 reusing an earlier HI16 must stay inside that HI16's pool.
        text = (0x3C010000, 0xC4240000, 0xC4260004)
        data = fixture(text, ((0, 5), (4, 6), (8, 6)), struct.pack('>2I', 1, 2) + bytes(8), None)
        with self.assertRaises(ValueError):
            self.run_split(data, ((0, 4), (4, 4)), 16)
        self.run_split(data, ((0, 8),), 16)

    def test_rejects_ranges_that_do_not_tile_the_object_rodata(self):
        data = fixture(POOL_TEXT, POOL_RELOCATIONS, POOL_RODATA, range(0, 8, 4))
        for ranges in (((0, 8, 0, 4), (12, 4)), ((0, 8, 0, 4), (8, 6)), ((0, 8, 0, 4), (8, 32))):
            with self.subTest(ranges=ranges), self.assertRaises(ValueError):
                self.run_split(data, ranges)
