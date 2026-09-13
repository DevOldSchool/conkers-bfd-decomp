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
        stack.enter_context(patch.object(objects, 'LOOP_SETUPS', ()))
        stack.enter_context(patch.object(objects, 'descriptor_contexts', return_value={}))
        stack.enter_context(patch.object(objects, 'fragment_array_contexts', return_value={}))
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

    def loop_fixture(self, setup):
        cb = setup.get('function', 0x1513A6E0)
        db = setup.get('mask', objects.LOOP_MASK)[0]
        code = bytearray(0x600)
        for pc, word in setup['guards']:
            struct.pack_into('>I', code, pc - cb, word)
        reg = 8
        for pc, word in zip(setup['flags'], (0x3C080010, 0x350839E9,
                                           0xAFA80000 | (setup['frame'] + 0x50))):
            struct.pack_into('>I', code, pc - cb, word)
        data = bytearray(64)
        if setup.get('count') == 2:
            data[:3] = bytes((0, 1, 2))
            selectors = (227, 229) if setup['mask_set'] else (228, 230)
        else:
            data[:6] = bytes((4, 12, 6, 7, 13, 0))
            selectors = (122, 123, 124, 125) if setup['mask_set'] else (118, 119, 120, 121)
        struct.pack_into(f'>{len(selectors)}I', data, setup['address'] - db, *selectors)
        return code, cb, data, db

    def test_mask_loops_preserve_complementary_selection_rows(self):
        expected = (([3, 4], [2, 3], [0, 1, 2, 3, 4], [1, 4]),
                    ([0, 1, 2, 5], [0, 1, 4, 5], [5], [0, 2, 3, 5]),
                    ([1], [2]), ([0, 2], [0, 1]))
        for setup, rows in zip(objects.LOOP_SETUPS, expected):
            args = self.loop_fixture(setup)
            result = objects.loop_array_contexts(*args, setup, tuple(range(233)))
            self.assertEqual(setup.get('count', 4), len(result))
            for index, proofs in enumerate(result.values()):
                self.assertEqual(rows[index], proofs[0]['selection_mask']['enabled_rows'])
                self.assertEqual(0x1039E9, proofs[0]['initial_flags']['value'])

    def test_mask_loops_reject_changed_instructions_arrays_masks_and_callback_flags(self):
        for setup in objects.LOOP_SETUPS:
            code, cb, data, db = self.loop_fixture(setup)
            for pc, word in setup['guards']:
                changed = bytearray(code)
                struct.pack_into('>I', changed, pc - cb, word ^ 1)
                with self.subTest(pc=hex(pc)), self.assertRaisesRegex(ValueError, 'instruction differs'):
                    objects.loop_array_contexts(changed, cb, data, db, setup, tuple(range(233)))
            for offset in (0, setup['address'] - db):
                changed = bytearray(data); changed[offset] ^= 1
                with self.assertRaises(ValueError):
                    objects.loop_array_contexts(code, cb, changed, db, setup, tuple(range(233)))
            changed = bytearray(code)
            struct.pack_into('>I', changed, setup['flags'][0] - cb, 0x3C080011)
            with self.assertRaisesRegex(ValueError, 'texture callback'):
                objects.loop_array_contexts(changed, cb, data, db, setup, tuple(range(233)))
            with self.assertRaisesRegex(ValueError, 'exceeds lookup'):
                objects.loop_array_contexts(code, cb, data, db, setup, tuple(range(118)))

    def test_descriptor_switch_proves_only_reachable_table_entries(self):
        cb, db = 0x15134000, 0x800A0000
        code, data = bytearray(0x5000), bytearray(128)
        struct.pack_into('>4I', code, 0, 0x03E00008, 0x24020000, 0x03E00008, 0x24020001)
        struct.pack_into('>I', code, 0x151384F4 - cb, 0x240B39E9)
        struct.pack_into('>I', code, 0x15138510 - cb, 0xAFAB0118)
        switch = struct.pack('>2I', cb, cb + 8)
        data[:8] = switch
        table = bytearray(32)
        struct.pack_into('>H', table, 12, 1)
        struct.pack_into('>H', table, 28, 2)
        data[32:64] = table
        with patch.object(objects, 'DESCRIPTOR_SWITCHES', ((db, 2, hashlib.sha1(switch).hexdigest()),)), \
             patch.object(objects, 'DESCRIPTOR_TABLE', (db + 32, 2, 16, hashlib.sha1(table).hexdigest())):
            result = objects.descriptor_contexts(code, cb, data, db, (999, 307, 230))
            self.assertEqual({307, 230}, set(result))
            for offset in (0, 32 + 12):
                changed = bytearray(data); changed[offset] ^= 1
                with self.assertRaises(ValueError):
                    objects.descriptor_contexts(code, cb, changed, db, (999, 307, 230))
            for offset in (0, 4, 0x15138510 - cb):
                changed = bytearray(code); changed[offset] ^= 1
                with self.assertRaises(ValueError):
                    objects.descriptor_contexts(changed, cb, data, db, (999, 307, 230))

    def test_word_literal_retains_high_bits_and_rejects_wrong_register_or_field(self):
        good = (0x3C080010, 0x350839E9, 0xAFA800F4)
        self.assertEqual(0x1039E9, objects.word_literal_store(struct.pack('>3I', *good), 0,
                                                           (0, 4, 8), 0xF4)['value'])
        for index, word in ((0, 0x24080010), (0, 0x3C000010), (1, 0x350939E9),
                            (1, 0x352839E9), (2, 0xAFA900F4), (2, 0xAFA800F8)):
            changed = list(good); changed[index] = word
            with self.assertRaises(ValueError):
                objects.word_literal_store(struct.pack('>3I', *changed), 0, (0, 4, 8), 0xF4)

    def fragment_fixture(self):
        cb, db = 0x150F1D00, 0x80089A20
        code = bytearray(0x15150D00 - cb)
        data = bytearray(0x800A3F64 - db)
        for pc, word in objects.FRAGMENT_GUARDS:
            struct.pack_into('>I', code, pc - cb, word)
        base = objects.FRAGMENT_TABLES[2][0]
        pointers = [base] * 20
        pointers[1] = base + 12  # Only callback-enabled type 1 reaches selector 9.
        spans = [struct.pack('>20I', *pointers), struct.pack('>20I', *([3] * 20)),
                 struct.pack('>6I', 1, 2, 3, 9, 9, 9), struct.pack('>3I', 4, 5, 6)]
        tables = []
        for (address, _, _), raw in zip(objects.FRAGMENT_TABLES, spans):
            data[address - db:address - db + len(raw)] = raw
            tables.append((address, len(raw), hashlib.sha1(raw).hexdigest()))
        return code, cb, data, db, tuple(tables)

    def test_fragment_arrays_exclude_callback_type_and_preserve_selector_alternatives(self):
        code, cb, data, db, tables = self.fragment_fixture()
        with patch.object(objects, 'FRAGMENT_TABLES', tables):
            rows = objects.fragment_array_contexts(code, cb, data, db, tuple(range(10)))
        self.assertEqual(set(range(1, 7)), set(rows))
        self.assertNotIn(9, rows)
        self.assertEqual(19, len(rows[1]))
        self.assertEqual([1, 3], rows[1][0]['selector_array']['count_variants'])
        self.assertEqual(-1, rows[4][0]['callback_index']['value'])
        self.assertEqual('func_150F1D10', rows[4][0]['selector_array']['caller'])

    def test_fragment_guards_tables_and_lookup_fail_closed(self):
        code, cb, data, db, tables = self.fragment_fixture()
        with patch.object(objects, 'FRAGMENT_TABLES', tables):
            for pc, _ in objects.FRAGMENT_GUARDS:
                changed = bytearray(code)
                changed[pc - cb] ^= 1
                with self.subTest(pc=hex(pc)), self.assertRaisesRegex(ValueError, 'callback protocol'):
                    objects.fragment_array_contexts(changed, cb, data, db, tuple(range(10)))
            for address, _, _ in tables:
                changed = bytearray(data)
                changed[address - db] ^= 1
                with self.assertRaisesRegex(ValueError, 'selector table'):
                    objects.fragment_array_contexts(code, cb, changed, db, tuple(range(10)))
            with self.assertRaisesRegex(ValueError, 'exceeds model lookup'):
                objects.fragment_array_contexts(code, cb, data, db, tuple(range(3)))

    def test_fragment_pointer_cannot_escape_its_pinned_array_span(self):
        code, cb, data, db, tables = self.fragment_fixture()
        struct.pack_into('>I', data, tables[0][0] - db, tables[2][0] - 4)
        pointer_bytes = data[tables[0][0] - db:tables[0][0] - db + 80]
        tables = ((tables[0][0], 80, hashlib.sha1(pointer_bytes).hexdigest()),) + tables[1:]
        with patch.object(objects, 'FRAGMENT_TABLES', tables), self.assertRaisesRegex(ValueError, 'pinned span'):
            objects.fragment_array_contexts(code, cb, data, db, tuple(range(10)))


if __name__ == '__main__':
    unittest.main()
