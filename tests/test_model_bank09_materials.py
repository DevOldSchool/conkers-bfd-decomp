import hashlib
import struct
import unittest
from contextlib import ExitStack
from unittest.mock import patch

from scripts import model_bank09_materials as objects


class Bank09MaterialTests(unittest.TestCase):
    def fixture(self):
        code_base, data_base = 0x15000000, 0x8008B4A8
        # A table can contain more models than the reviewed constructor reaches.
        table = struct.pack('>3I', 194, 211, 412)
        data = bytearray(objects.MODEL_TABLE - data_base + len(table))
        data[-len(table):] = table
        for kind in (25, 72):
            struct.pack_into('>4I', data, kind * 52 + 8, 0x15132B80, 0x15132A88, 0, 0)
        code = struct.pack('>5I', 0x240829E8, 0xAFA80070, 0x24090001, 0xA7A90076,
                           (3 << 26) | ((0x15132A4C >> 2) & 0x3FFFFFF))
        stack = ExitStack()
        stack.enter_context(patch.object(objects, 'MODEL_COUNT', 3))
        stack.enter_context(patch.object(objects, 'MODEL_TABLE_SHA1', hashlib.sha1(table).hexdigest()))
        stack.enter_context(patch.object(objects, 'CONSUMERS', ((code_base, len(code), hashlib.sha1(code).hexdigest()),)))
        stack.enter_context(patch.object(objects, 'SETUPS', ((code_base, code_base + 16, 0x20,
            (code_base, code_base + 4), ((code_base + 8, code_base + 12),)),)))
        stack.enter_context(patch.object(objects, 'ARRAY_SETUPS', ()))
        self.addCleanup(stack.close)
        return code, code_base, data, data_base

    def test_only_constructor_referenced_models_receive_context(self):
        result = objects.material_context(*self.fixture())
        self.assertEqual([211], [model['entry'] for model in result['models']])
        proof = result['models'][0]['constructors'][0]
        self.assertEqual(0x29E8, proof['initial_flags']['value'])
        self.assertEqual(1, proof['model_selector']['value'])
        self.assertEqual([], result['capture_inputs'])

    def test_changed_consumers_lookup_and_dispatch_fail_closed(self):
        code, cb, data, db = self.fixture()
        with self.assertRaisesRegex(ValueError, 'consumer changed'):
            objects.material_context(bytes(len(code)), cb, data, db)
        with self.assertRaisesRegex(ValueError, 'exceeds ROM region'):
            objects.material_context(code[:-4], cb, data, db)
        changed = bytearray(data)
        changed[-1] ^= 1
        with self.assertRaisesRegex(ValueError, 'lookup table changed'):
            objects.material_context(code, cb, changed, db)
        changed = bytearray(data)
        struct.pack_into('>I', changed, 25 * 52 + 0x14, 0x15133E84)
        with self.assertRaisesRegex(ValueError, 'draw dispatch changed'):
            objects.material_context(code, cb, changed, db)

    def test_literal_must_be_constant_and_store_the_same_register_and_field(self):
        good = struct.pack('>II', 0x24090023, 0xA7A90076)
        result = objects.literal_store(good, 0, (0, 4), 0x76, 2)
        self.assertEqual(35, result['value'])
        for literal, store in ((0x25290023, 0xA7A90076), (0x3C090001, 0xA7A90076),
                               (0x24090023, 0xA7A80076), (0x24090023, 0xA7A90074),
                               (0x24090023, 0xAFA90076)):
            with self.subTest(literal=literal, store=store), self.assertRaises(ValueError):
                objects.literal_store(struct.pack('>II', literal, store), 0, (0, 4), 0x76, 2)

    def test_unreviewed_calls_and_out_of_range_selectors_are_rejected(self):
        code, cb, data, db = self.fixture()
        for index, value, message in ((4, 0, 'submission changed'), (2, 0x24090003, 'exceeds lookup')):
            changed = bytearray(code)
            struct.pack_into('>I', changed, index * 4, value)
            with patch.object(objects, 'CONSUMERS', ((cb, len(changed), hashlib.sha1(changed).hexdigest()),)):
                with self.assertRaisesRegex(ValueError, message):
                    objects.material_context(changed, cb, data, db)

    def test_conditional_flags_preserve_both_outcomes_and_reject_changed_flow(self):
        words = [0x10400003, 0xAFA2019C, 0x10000002, 0x24020400, 0x00001025,
                 0x344B0900, 0xAFAB0190]
        code = struct.pack('>7I', *words)
        result = objects.conditional_or_store(code, 0, (0, 20, 24), 0x190)
        self.assertEqual([0x900, 0xD00], result['values'])
        # Branch target/condition, delay-slot effects, register agreement,
        # signed literals, zero arm, OR source and destination field matter.
        changes = [(0, 0x10400004), (0, 0x14400003), (1, 0x24420001),
                   (2, 0x10000003), (3, 0x24030400), (3, 0x24028400),
                   (4, 0x00001825), (5, 0x346B0900), (6, 0xAFAB0194),
                   (6, 0xAFA20190)]
        for index, word in changes:
            changed = words.copy()
            changed[index] = word
            with self.subTest(index=index, word=word), self.assertRaises(ValueError):
                objects.conditional_or_store(struct.pack('>7I', *changed), 0, (0, 20, 24), 0x190)

    def test_high_literal_branch_retains_high_flag_bits(self):
        code = struct.pack('>7I', 0x11C00003, 0xE7A400B4, 0x10000002, 0x3C020010,
                           0x00001025, 0x344F29E8, 0xAFAF00C0)
        self.assertEqual([0x29E8, 0x1029E8],
                         objects.conditional_or_store(code, 0, (0, 20, 24), 0xC0)['values'])
        changed = bytearray(code)
        struct.pack_into('>I', changed, 12, 0x3C020001)
        self.assertEqual([0x29E8, 0x129E8],
                         objects.conditional_or_store(changed, 0, (0, 20, 24), 0xC0)['values'])

    def test_selector_array_checks_call_address_count_and_content(self):
        helper = 0x15151D6C
        raw = struct.pack('>3I', 4, 29, 30)
        words = [0x3C088001, 0x2508FFF0, 0x24070003, 0x27A500E0,
                 (3 << 26) | ((helper >> 2) & 0x3FFFFFF)]
        setup = (0, 16, helper, 8, (0, 4), 0x8000FFF0, 3, hashlib.sha1(raw).hexdigest(), 12, 0xE0)
        code = struct.pack('>5I', *words)
        result = objects.array_selectors(code, 0, raw, 0x8000FFF0, setup)
        self.assertEqual([4, 29, 30], result['selectors'])
        for index, word in [(0, 0x3C088002), (1, 0x2509FFF0), (2, 0x24070004),
                            (3, 0x27A500E4), (4, 0)]:
            changed = words.copy(); changed[index] = word
            with self.subTest(index=index), self.assertRaises(ValueError):
                objects.array_selectors(struct.pack('>5I', *changed), 0, raw, 0x8000FFF0, setup)
        with self.assertRaisesRegex(ValueError, 'selector array changed'):
            objects.array_selectors(code, 0, bytes(len(raw)), 0x8000FFF0, setup)


if __name__ == '__main__':
    unittest.main()
