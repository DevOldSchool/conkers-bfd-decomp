"""Bounded attachment-80 controller behavior independently read from US ASM."""
import copy
import hashlib
import math
import struct
import unittest
from unittest.mock import patch

from scripts import model_attachment_controller as controller
from scripts import model_attachment_updates as updates


class AttachmentControllerTests(unittest.TestCase):
    def assert_state(self, result, phase, accumulator, texture, origin):
        self.assertEqual(phase, result['phase'])
        self.assertEqual(accumulator, result['accumulator'])
        self.assertEqual(texture, result['texture_flat'])
        self.assertEqual(0xF2002000 | origin, result['tile_word'])

    def test_native_float32_rounding_and_mask_origins(self):
        # Literal outcomes checked against the native CVT/MUL/MUL/ADD/TRUNC
        # instruction sequence. A host-double accumulator * 1.2 disagrees.
        origins = {0: 2, 1: 3, 5: 7, 10: 13, 15: 19, 20: 25,
                   30: 37, 40: 49, 49: 60, 50: 62, 51: 63,
                   60: 73, 80: 97, 85: 103, 99: 120, 100: 122}
        for accumulator, origin in origins.items():
            with self.subTest(accumulator=accumulator):
                self.assertEqual(0xF2002000 | origin,
                                 controller.tile_word(accumulator))

    def test_initial_arm_resets_counter_and_texture_before_parent_gate(self):
        for parent in (0, 396, 398, 65535):
            with self.subTest(parent=parent):
                result = controller.step(0, 99, 65535, delta=100,
                                         parent_action=parent)
                self.assert_state(result, 0, 50, 7203, 62)
        self.assert_state(controller.step(0, 0, 3249, parent_action=397,
                                          parent_frame=45.5), 0, 50, 7203, 62)

    def test_initial_threshold_changes_texture_without_running_next_arm(self):
        for frame in (46, 46.5, 45.99999999):
            with self.subTest(frame=frame):
                # The last value rounds to exactly 46 in source float32.
                result = controller.step(0, 0, 7203, delta=100,
                                         parent_action=397, parent_frame=frame)
                self.assert_state(result, 1, 50, 3249, 62)

    def test_rising_arm_clamps_and_preserves_incoming_texture(self):
        self.assert_state(controller.step(1, 50, 1234, delta=0),
                          1, 50, 1234, 62)
        self.assert_state(controller.step(1, 50, 1234, delta=1),
                          1, 51, 1234, 63)
        self.assert_state(controller.step(1, 99, 7203, delta=1),
                          2, 100, 7203, 122)
        self.assert_state(controller.step(1, 99, 3249, delta=100),
                          2, 100, 3249, 122)
        # Reaching phase2 must not execute its parent/frame gate in this call.
        self.assert_state(controller.step(1, 100, 3249, delta=0,
                                          parent_action=398),
                          2, 100, 3249, 122)

    def test_waiting_arm_requires_its_own_gate_and_delays_decrement(self):
        self.assert_state(controller.step(2, 100, 3249, delta=100,
                                          parent_action=397),
                          2, 100, 3249, 122)
        self.assert_state(controller.step(2, 100, 1234, delta=100,
                                          parent_action=398, parent_frame=33.5),
                          2, 100, 1234, 122)
        for frame in (34, 34.5, 33.99999999):
            with self.subTest(frame=frame):
                self.assert_state(controller.step(2, 100, 1234, delta=100,
                                                  parent_action=398,
                                                  parent_frame=frame),
                                  3, 100, 1234, 122)

    def test_falling_arm_clamps_at_zero_and_changes_only_its_fields(self):
        self.assert_state(controller.step(3, 50, 1234, delta=0),
                          3, 50, 1234, 62)
        self.assert_state(controller.step(3, 5, 1234, delta=1),
                          3, 1, 1234, 3)
        self.assert_state(controller.step(3, 4, 1234, delta=1),
                          4, 0, 1234, 2)
        self.assert_state(controller.step(3, 3, 1234, delta=100),
                          4, 0, 1234, 2)
        self.assert_state(controller.step(3, 0, 7203, delta=0),
                          4, 0, 7203, 2)

    def test_default_arm_includes_all_other_unsigned_word_phases(self):
        for phase in (4, 5, 0x7fffffff, 0x80000000, 0xffffffff):
            with self.subTest(phase=phase):
                self.assert_state(controller.step(phase, 50, 65535, delta=100,
                                                  parent_action=397),
                                  phase, 50, 65535, 62)

    def test_nan_does_not_pass_native_ordered_float_comparison(self):
        self.assert_state(controller.step(0, 0, 0, parent_action=397,
                                          parent_frame=math.nan),
                          0, 50, 7203, 62)
        self.assert_state(controller.step(2, 100, 3249, parent_action=398,
                                          parent_frame=math.nan),
                          2, 100, 3249, 122)

    def test_frame_is_required_only_for_the_arm_that_dereferences_parent(self):
        for phase, action in ((0, 397), (2, 398)):
            with self.subTest(phase=phase), self.assertRaises(ValueError):
                controller.step(phase, 50, 7203, parent_action=action)
        for phase, action in ((0, 398), (1, 397), (1, 398), (2, 397),
                              (3, 398), (4, 397)):
            with self.subTest(phase=phase, action=action):
                controller.step(phase, 50, 7203, parent_action=action)

    def test_bounded_inputs_reject_overflow_and_noninteger_field_values(self):
        for value in (-1, 101, 0x7fffffff, 50.0, True):
            with self.subTest(accumulator=value), self.assertRaises(ValueError):
                controller.tile_word(value)
        base = {'phase': 0, 'accumulator': 50, 'texture_flat': 7203,
                'delta': 0, 'parent_action': 0}
        invalid = {'phase': (-1, 0x100000000, 0.0, True),
                   'accumulator': (-1, 101, 50.0, True),
                   'texture_flat': (-1, 65536, 7203.0, True),
                   'delta': (-1, 101, 1.0, True),
                   'parent_action': (-1, 65536, 397.0, True)}
        for field, values in invalid.items():
            for value in values:
                with self.subTest(field=field, value=value), self.assertRaises(ValueError):
                    controller.step(**{**base, field: value})


class AttachmentControllerSourceTests(unittest.TestCase):
    code_base = 0x15000000
    data_base = 0x80082B20

    def source(self):
        code = bytearray(max(a + n for a, n, _ in updates.CONSUMERS) - self.code_base)
        data = bytearray(0x20000)
        for address, text in updates.DATA_SPANS:
            raw = bytes.fromhex(text)
            offset = address - self.data_base
            data[offset:offset + len(raw)] = raw
        struct.pack_into('>II', data, 0x80090304 - self.data_base, 7203, 3249)
        return code, data

    def describe(self, code, data, original_code=None):
        original_code = code if original_code is None else original_code
        pins = [(a, n, hashlib.sha1(original_code[a-self.code_base:a-self.code_base+n]).hexdigest())
                for a, n, _ in updates.CONSUMERS]
        with patch.object(updates, 'CONSUMERS', pins):
            return controller.describe_controller(code, self.code_base,
                                                   data, self.data_base)

    def test_description_is_repeatable_and_does_not_change_source_inputs(self):
        code, data = self.source()
        saved_code, saved_data = bytes(code), bytes(data)
        first = self.describe(code, data)
        self.assertIsInstance(first, dict)
        expected = copy.deepcopy(first)
        second = self.describe(code, data)
        self.assertEqual(expected, second)
        self.assertIsNot(first, second)
        self.assertEqual(saved_code, code)
        self.assertEqual(saved_data, data)

    def test_every_consumer_and_every_pinned_data_byte_is_guarded(self):
        original, data = self.source()
        for address, size, _ in updates.CONSUMERS:
            for delta in (0, size // 2, size - 1):
                changed = bytearray(original)
                changed[address - self.code_base + delta] ^= 1
                with self.subTest(consumer=hex(address), delta=delta), self.assertRaises(ValueError):
                    self.describe(changed, data, original)
        spans = list(updates.DATA_SPANS) + [(0x80090304, '00001c2300000cb1')]
        for address, text in spans:
            for delta in range(len(bytes.fromhex(text))):
                changed = bytearray(data)
                changed[address - self.data_base + delta] ^= 1
                with self.subTest(data=hex(address), delta=delta), self.assertRaises(ValueError):
                    self.describe(original, changed)

    def test_truncated_or_rebased_evidence_is_rejected(self):
        code, data = self.source()
        with self.assertRaises(ValueError):
            self.describe(code, data[:0x80090308 - self.data_base])
        with self.assertRaises(ValueError):
            self.describe(code[:-1], data, code)
        with self.assertRaises(ValueError):
            controller.describe_controller(code, self.code_base + 4,
                                           data, self.data_base)


if __name__ == '__main__':
    unittest.main()
