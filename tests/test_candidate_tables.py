from __future__ import annotations

import struct
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
from candidate_tables import Table, TableEvidenceError, Object32, verify_object, reference_tables, direct_target


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

    def test_float_store_delay_slot_cannot_clobber_guard_gprs(self):
        # The same bounded dispatch as func_150415E0, with a swc1 in the
        # branch delay slot. FPR indices matching at/t6 must not be treated
        # as writes to those GPRs; a GPR-writing instruction still fails.
        def reference(delay, branch=0x10200007):
            words = [0x2DC10002, 0x8FA30020, 0x8FA5001C, branch, delay,
                     0x000E7080, 0x3C018009, 0x002E0821, 0x8C2E0000,
                     0x01C00008, 0, 0]
            raw = ''.join(f'/* {i*4:06X} {0x15000000+i*4:08X} {word:08X} */ '
                          + ('lw $t6,%lo(jtbl_80090000)($at)' if i == 8 else 'instruction')
                          + '\n' for i, word in enumerate(words))
            code = b''.join(word.to_bytes(4, 'big') for word in words)
            return raw, code

        data = struct.pack('>II', 0x15000028, 0x1500002C)
        expected = (0x15000000, [Table(24, 32, (0x15000028, 0x1500002C))])
        for delay in (0xE4440000, 0xE4410000, 0xE5CE0000):
            with self.subTest(delay=hex(delay)):
                raw, code = reference(delay)
                self.assertEqual(expected, reference_tables(raw, code, data,
                                                            0x15000000, 0x80090000))
        for delay in (0x440E0000, 0x44010000, 0x8C4E0000, 0x25CE0001):
            with self.subTest(gpr_clobber=hex(delay)):
                raw, code = reference(delay)
                with self.assertRaisesRegex(TableEvidenceError, 'bound is missing'):
                    reference_tables(raw, code, data, 0x15000000, 0x80090000)
        raw, code = reference(0xE4440000, branch=0x14200007)
        with self.assertRaisesRegex(TableEvidenceError, 'bound is missing'):
            reference_tables(raw, code, data, 0x15000000, 0x80090000)

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


class ScheduledBooleanGuardTests(unittest.TestCase):
    # The scheduling of func_1511DD98, including two unrelated boolean
    # sltiu instructions. Case bodies start strictly after the jr delay.
    words = [0x2F210036, 0x3847003B, 0x38460080, 0x2CE70001,
             0x10200007, 0x2CC60001, 0x0019C880, 0x3C018009,
             0x00390821, 0x8C390000, 0x03200008, 0,
             0x03E00008, 0]

    def verify(self, words=None, count=54, load=9):
        words = self.words.copy() if words is None else words
        start = 0x15000000
        raw = ''.join(f'/* {i*4:06X} {start+i*4:08X} {word:08X} */ '
                      + ('lw $t9,%lo(jtbl_80090000)($at)' if i == load else 'instruction')
                      + '\n' for i, word in enumerate(words))
        code = b''.join(word.to_bytes(4, 'big') for word in words)
        data = struct.pack('>' + 'I' * count, *([start + 48] * count))
        return reference_tables(raw, code, data, start, 0x80090000)

    def reject(self, words):
        with self.assertRaises(TableEvidenceError):
            self.verify(words)

    def test_three_boolean_instructions_and_delay_preserve_true_bound(self):
        start, tables = self.verify()
        self.assertEqual(start, 0x15000000)
        self.assertEqual(tables, [Table(28, 36, (0x15000030,) * 54)])
        for count in (1, 1024):
            words = self.words.copy()
            words[0] = 0x2F210000 | count
            self.assertEqual(len(self.verify(words, count)[1][0].targets), count)
        # Reading either protected GPR while writing an independent GPR is safe.
        for source in (1, 25):
            words = self.words.copy()
            words[1] = (0x0E << 26) | (source << 21) | (7 << 16) | 1
            self.verify(words)

    def test_protected_destination_in_each_scheduled_position_is_rejected(self):
        for position in (1, 2, 3, 5):
            for opcode in (0x23, 0x0E, 0x0B):
                for destination in (1, 25):
                    with self.subTest(position=position, opcode=opcode, destination=destination):
                        words = self.words.copy()
                        words[position] = (opcode << 26) | (2 << 21) | (destination << 16) | 1
                        self.reject(words)

    def test_unrelated_wrong_register_and_invalid_limit_guards_are_rejected(self):
        for guard in (0x2C410036, 0x2F230036, 0x2F390036, 0x2F210000, 0x2F210401, 0):
            with self.subTest(guard=hex(guard)):
                words = self.words.copy()
                words[0] = guard
                self.reject(words)
        for branch in (0x14200007, 0x10E00007, 0x10200000, 0x1020FFFF, 0x10207FFF):
            with self.subTest(branch=hex(branch)):
                words = self.words.copy()
                words[4] = branch
                self.reject(words)

    def test_only_narrow_independent_opcodes_are_accepted(self):
        for position in (1, 2, 3, 5):
            for word in (0x24470001, 0x34470001, 0x44070000, 0x08000000,
                         0x0C000000, 0x03E00008, 0x0320F809, 0x10000001,
                         0x50000001, 0x45010001):
                with self.subTest(position=position, word=hex(word)):
                    words = self.words.copy()
                    words[position] = word
                    self.reject(words)
        # Four intervening instructions remain unsupported.
        words = self.words[:4] + [0] + self.words[4:]
        with self.assertRaises(TableEvidenceError):
            self.verify(words, load=10)

    def test_direct_entries_and_default_inside_dispatch_are_rejected(self):
        start = 0x15000000
        for target_index in range(1, 12):
            for opcode in (2, 3):
                with self.subTest(target=target_index, opcode=opcode):
                    word = (opcode << 26) | (((start + target_index * 4) >> 2) & 0x03FFFFFF)
                    self.reject(self.words + [word, 0])
            # Backward ordinary/likely/REGIMM/COP branches from after the cases.
            displacement = (target_index - 15) & 0xFFFF
            for branch in (0x10000000, 0x50000000, 0x04010000, 0x45010000):
                self.reject(self.words + [branch | displacement, 0])
        for target_index in range(5, 12):
            words = self.words.copy()
            words[4] = 0x10200000 | (target_index - 5)
            self.reject(words)
        # A direct entry from before the guard is rejected as well. The
        # preceding nop avoids conflating this with the guard-delay check.
        for target_index in range(3, 14):
            target = start + target_index * 4
            for opcode in (2, 3):
                with self.assertRaises(TableEvidenceError):
                    self.verify([(opcode << 26) | ((target >> 2) & 0x03FFFFFF), 0]
                                + self.words, load=11)
        # Entry at the guard itself or just after the dispatch is allowed.
        for target_index in (0, 12):
            target = start + target_index * 4
            self.verify(self.words + [(2 << 26) | ((target >> 2) & 0x03FFFFFF), 0])

    def test_guard_and_jump_delay_slots_are_checked(self):
        # A guard in the delay slot of a preceding transfer is not independent.
        with self.assertRaises(TableEvidenceError):
            self.verify([0x08000000] + self.words, load=10)
        with self.assertRaises(TableEvidenceError):
            self.verify(self.words[:11])
        for transfer in (0x03E00008, 0x08000000, 0x10000001, 0x45010001):
            words = self.words.copy()
            words[11] = transfer
            self.reject(words)

    def test_direct_target_decoding_uses_signed_offsets_and_pc_high_bits(self):
        address = 0x8FFFFFFC
        for op in (2, 3):
            self.assertEqual(direct_target((op << 26) | 3, address), 0x9000000C)
        for branch in (0x10000000, 0x50000000, 0x04010000, 0x45010000):
            self.assertEqual(direct_target(branch | 0xFFFF, 0x15000040), 0x15000040)
            self.assertEqual(direct_target(branch | 2, 0x15000040), 0x1500004C)
        self.assertIsNone(direct_target(0x2F210036, 0x15000000))
