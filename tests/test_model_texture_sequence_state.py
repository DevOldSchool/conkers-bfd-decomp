"""Literal US assembly examples for the texture-sequence packed state word."""
import copy
import unittest

from scripts import model_texture_sequence_state as state


WATER = {'frames': [7188, 7195, 7196, 7197, 7198, 7199, 7200, 7201,
                    7202, 7189, 7190, 7191, 7192, 7193, 7194],
         'frame_period': 1, 'ping_pong': True}
LOOP = {'frames': [255, 256, 257], 'frame_period': 6, 'ping_pong': False}


class TextureSequenceStateTests(unittest.TestCase):
    def assert_step(self, row, source, packed, counter, increment, index, flat):
        self.assertEqual({'packed_state': packed, 'counter': counter,
                          'increment': increment, 'frame_index': index,
                          'flat_index': flat}, state.step(row, source))

    def test_zero_increment_becomes_one_and_selection_follows_advance(self):
        self.assert_step(WATER, 0x00000000, 0x00010001, 1, 1, 1, 7195)
        self.assert_step(LOOP, 0x00000000, 0x00010001, 1, 1, 0, 255)
        self.assert_step(LOOP, 0x00000005, 0x00010006, 6, 1, 1, 256)

    def test_pingpong_upper_endpoint_is_repeated(self):
        self.assert_step(WATER, 0x0001000D, 0x0001000E, 14, 1, 14, 7194)
        self.assert_step(WATER, 0x0001000E, 0xFFFF000E, 14, -1, 14, 7194)
        self.assert_step(WATER, 0xFFFF000E, 0xFFFF000D, 13, -1, 13, 7193)

    def test_pingpong_lower_endpoint_returns_to_period_instead_of_zero(self):
        self.assert_step(WATER, 0xFFFF0001, 0xFFFF0000, 0, -1, 0, 7188)
        self.assert_step(WATER, 0xFFFF0000, 0x00010001, 1, 1, 1, 7195)
        slower = {**WATER, 'frame_period': 2}
        self.assert_step(slower, 0xFFFF0000, 0x00010002, 2, 1, 1, 7195)
        self.assert_step(slower, 0x0001001D, 0xFFFF001C, 28, -1, 14, 7194)

    def test_loop_subtracts_its_span_once_and_resets_increment(self):
        self.assert_step(LOOP, 0x00010010, 0x00010011, 17, 1, 2, 257)
        self.assert_step(LOOP, 0x00010011, 0x00010000, 0, 1, 0, 255)
        self.assert_step(LOOP, 0x00050011, 0x00010004, 4, 1, 0, 255)
        self.assert_step(LOOP, 0x00180000, 0x00010006, 6, 1, 1, 256)
        # A modulo implementation would silently turn this into frame zero.
        with self.assertRaises(ValueError):
            state.step(LOOP, 0x00240000)

    def test_signed_increment_magnitude_is_preserved_between_boundaries(self):
        self.assert_step(WATER, 0x00030004, 0x00030007, 7, 3, 7, 7201)
        self.assert_step(WATER, 0xFFFE000A, 0xFFFE0008, 8, -2, 8, 7202)
        self.assert_step(LOOP, 0xFFFE000A, 0xFFFE0008, 8, -2, 1, 256)
        self.assert_step(WATER, 0x7FFF0000, 0xFFFF000E, 14, -1, 14, 7194)
        self.assert_step(WATER, 0x80000000, 0x00010001, 1, 1, 1, 7195)

    def test_negative_loop_counter_is_rejected_even_if_division_would_yield_zero(self):
        with self.assertRaises(ValueError):
            state.step(LOOP, 0xFFFF0000)
        with self.assertRaises(ValueError):
            state.step(LOOP, 0x80000000)

    def test_unsigned_counter_is_not_sign_extended(self):
        wide = {'frames': list(range(255)), 'frame_period': 255,
                'ping_pong': False}
        self.assert_step(wide, 0x00008000, 0x00018001, 32769, 1, 128, 128)
        self.assert_step(wide, 0x0000FFFF, 0x000101FF, 511, 1, 2, 2)
        with self.assertRaises(ValueError):
            state.step(LOOP, 0x7FFFFFFF)

    def test_single_frame_and_duplicate_frame_arrays_keep_native_behavior(self):
        one = {'frames': [9], 'frame_period': 1, 'ping_pong': False}
        self.assert_step(one, 0, 0x00010000, 0, 1, 0, 9)
        self.assert_step({**one, 'ping_pong': True}, 0, 0xFFFF0000, 0, -1, 0, 9)
        with self.assertRaises(ValueError):
            state.step({**one, 'ping_pong': True}, 0xFFFF0000)
        duplicates = {'frames': [8, 8, 9], 'frame_period': 1, 'ping_pong': False}
        self.assert_step(duplicates, 0, 0x00010001, 1, 1, 1, 8)

    def test_malformed_rows_and_packed_words_are_rejected(self):
        bad_rows = [None, [], {}, {**WATER, 'frames': []},
                    {**WATER, 'frames': [0] * 256},
                    {**WATER, 'frames': '123'},
                    {**WATER, 'frames': [True]},
                    {**WATER, 'frames': [-1]},
                    {**WATER, 'frames': [0x100000000]},
                    {**WATER, 'frames': [1.0]}]
        bad_rows += [{**WATER, 'frame_period': x} for x in (0, 256, -1, 1.0, True, None)]
        bad_rows += [{**WATER, 'ping_pong': x} for x in (0, 1, 'true', None)]
        for row in bad_rows:
            with self.subTest(row=row), self.assertRaises(ValueError):
                state.step(row, 0)
        for packed in (-1, 0x100000000, 1.0, True, None, '0'):
            with self.subTest(packed=packed), self.assertRaises(ValueError):
                state.step(WATER, packed)

    def test_inputs_are_unchanged_and_calls_do_not_share_result_state(self):
        row = copy.deepcopy(WATER)
        saved = copy.deepcopy(row)
        first = state.step(row, 0)
        first['counter'] = 999
        self.assertEqual(saved, row)
        self.assertEqual(1, state.step(row, 0)['counter'])

    def test_description_identifies_native_consumer_and_excludes_clock_claims(self):
        description = state.description()
        self.assertEqual('func_1511A494', description['updater'])
        self.assertEqual(616, description['consumer_bytes'])
        self.assertEqual('c896da27caa019639fe040e1d5bf9034f2663673',
                         description['consumer_sha1'])
        self.assertEqual(1, description['loop']['subtractions'])
        self.assertFalse(description['loop']['negative_counter_correction'])
        self.assertIn('No FPS', description['scope'])
        self.assertIn('animation_table', description['source_validation'])
        description['input']['packed_state'] = 'changed'
        self.assertNotEqual(description, state.description())


if __name__ == '__main__':
    unittest.main()
