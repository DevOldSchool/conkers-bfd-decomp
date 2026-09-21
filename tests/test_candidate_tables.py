from __future__ import annotations

import struct
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
from candidate_tables import Table, TableEvidenceError, Object32, verify_object, reference_tables


def object_fixture(*, wrong_case=False, missing_relocation=False, origin=32, table_offset=4):
    text = bytearray(origin + 32)
    struct.pack_into('>I', text, origin, 0x3C010000 + (1 if table_offset >= 0x8000 else 0))
    struct.pack_into('>I', text, origin + 8, 0x8C220000 + table_offset)
    rodata = bytearray(table_offset + 8)
    struct.pack_into('>II', rodata, table_offset, origin + 16, origin + (16 if wrong_case else 20))
    strings = b'\0func_test\0'
    symbol = lambda name, value, size, info, section: struct.pack('>IIIBBH', name, value, size, info, 0, section)
    symbols = (bytes(16) + symbol(1, origin, 32, 0x12, 1)
               + symbol(0, 0, 0, 3, 1) + symbol(0, 0, 0, 3, 2))
    reltext = struct.pack('>IIII', origin, 3 << 8 | 5, origin + 8, 3 << 8 | 6)
    reltable = struct.pack('>II', table_offset, 2 << 8 | 2)
    if not missing_relocation:
        reltable += struct.pack('>II', table_offset + 4, 2 << 8 | 2)
    sections = [(0, b'', 0, 0, 0), (1, text, 0, 0, 0), (1, rodata, 0, 0, 0),
                (2, symbols, 4, 0, 16), (3, strings, 0, 0, 0),
                (9, reltext, 3, 1, 8), (9, reltable, 3, 2, 8)]
    body = bytearray(52)
    headers = []
    for kind, data, link, info, entsize in sections:
        headers.append(struct.pack('>10I', 0, kind, 0, 0, len(body), len(data), link, info, 4, entsize))
        body.extend(data)
    offset = len(body)
    body.extend(b''.join(headers))
    body[:52] = struct.pack('>16sHHIIIIIHHHHHH', b'\x7fELF\x01\x02\x01' + bytes(9),
                            1, 8, 1, 0, 0, offset, 0, 52, 0, 0, 40, len(sections), 0)
    return bytes(body)


class CandidateTableTests(unittest.TestCase):
    tables = [Table(0, 8, (0x15000010, 0x15000014))]

    def test_relocates_case_targets_relative_to_candidate_function(self):
        for origin in (0, 32, 128):
            for offset in (4, 0x8000):
                verify_object(object_fixture(origin=origin, table_offset=offset), 'func_test',
                              0x15000000, self.tables, 32)

    def test_same_instructions_with_wrong_table_are_rejected(self):
        with self.assertRaisesRegex(TableEvidenceError, 'case 1 differs'):
            verify_object(object_fixture(wrong_case=True), 'func_test', 0x15000000, self.tables, 32)

    def test_missing_relocation_and_wrong_function_extent_fail_closed(self):
        with self.assertRaisesRegex(TableEvidenceError, 'missing R_MIPS'):
            verify_object(object_fixture(missing_relocation=True), 'func_test', 0x15000000, self.tables, 32)
        with self.assertRaisesRegex(TableEvidenceError, 'extent'):
            verify_object(object_fixture(), 'func_test', 0x15000000, self.tables, 28)

    def test_truncated_or_foreign_objects_fail_closed(self):
        for data in (b'', object_fixture()[:80], b'not ELF' + object_fixture()[7:]):
            with self.assertRaises(TableEvidenceError):
                Object32(data)

    def test_reference_validates_scheduled_dispatch_bounds_and_rom_bytes(self):
        # sltiu at,t6,2; two independent loads; beqz at,default; sh delay;
        # sll t6,t6,2; lui at,8009; addu at,at,t6; lw t6,0(at); jr t6.
        words = [0x2DC10002, 0x8FA30020, 0x8FA5001C, 0x10200007, 0xA4400000,
                 0x000E7080, 0x3C018009, 0x002E0821, 0x8C2E0000, 0x01C00008, 0, 0]
        raw = ''.join(f'/* {i*4:06X} {0x15000000+i*4:08X} {word:08X} */ '
                      + ('lw $t6,%lo(jtbl_80090000)($at)' if i == 8 else 'instruction') + '\n'
                      for i, word in enumerate(words))
        code = b''.join(word.to_bytes(4, 'big') for word in words)
        data = struct.pack('>II', 0x15000028, 0x1500002C)
        self.assertEqual((0x15000000, [Table(24, 32, (0x15000028, 0x1500002C))]),
                         reference_tables(raw, code, data, 0x15000000, 0x80090000))
        for bad_raw, bad_code, bad_data in ((raw, bytes(len(code)), data),
                                          (raw, code, data[:4]),
                                          (raw, code, struct.pack('>II', 0x15010000, 0x1500002C))):
            with self.assertRaises(TableEvidenceError):
                reference_tables(bad_raw, bad_code, bad_data, 0x15000000, 0x80090000)
        clobbered = raw.replace('8FA30020', '8FAE0020')
        with self.assertRaises(TableEvidenceError):
            reference_tables(clobbered, code[:4] + bytes.fromhex('8FAE0020') + code[8:],
                             data, 0x15000000, 0x80090000)
