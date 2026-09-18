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


def fixture():
    names = b'\0.text\0.rodata\0.symtab\0.strtab\0.rel.text\0.rel.rodata\0.shstrtab\0'
    symbols = bytes(16) + struct.pack('>IIIBBH', 0, 0, 16, 3, 0, 1) + struct.pack('>IIIBBH', 0, 0, 32, 3, 0, 2)
    # Two tables, separated in ROM, contiguous in this compiler object.
    payloads = [b'', struct.pack('>4I', 0x3C010000, 0x8C220000, 0x3C010000, 0x8C220008),
                struct.pack('>4I', 0, 4, 8, 12) + bytes(16), symbols, b'\0',
                b''.join(struct.pack('>II', offset, 2 << 8 | kind) for offset, kind in ((0, 5), (4, 6), (8, 5), (12, 6))),
                b''.join(struct.pack('>II', offset, 1 << 8 | 2) for offset in range(0, 16, 4)), names]
    specs = [('', 0, 0, 0, 0, 0), ('.text', 1, 6, 0, 0, 0), ('.rodata', 1, 2, 0, 0, 0),
             ('.symtab', 2, 0, 4, 3, 16), ('.strtab', 3, 0, 0, 0, 0),
             ('.rel.text', 9, 0, 3, 1, 8), ('.rel.rodata', 9, 0, 3, 2, 8), ('.shstrtab', 3, 0, 0, 0, 0)]
    result = bytearray(52)
    sections = []
    for (name, kind, flags, link, info, entsize), payload in zip(specs, payloads):
        result.extend(bytes(-len(result) % 4))
        sections.append((names.index(name.encode() + b'\0'), kind, flags, 0, len(result), len(payload), link, info, 4, entsize))
        result.extend(payload)
    result.extend(bytes(-len(result) % 4))
    table = len(result)
    result.extend(b''.join(struct.pack('>10I', *s) for s in sections))
    struct.pack_into('>16sHHIIIIIHHHHHH', result, 0, b'\x7fELF\x01\x02\x01' + bytes(9), 1, 8, 1, 0, 0, table, 0, 52, 0, 0, 40, len(sections), 7)
    return bytes(result)


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
