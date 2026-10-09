"""Complete TMEM coverage and native selector semantics must be explicit."""
import copy
import hashlib
from types import SimpleNamespace as NS
import unittest

from scripts import texture_model_storage as storage


class ModelStorageTests(unittest.TestCase):
    def run_fixture(self):
        pixel = NS(mode=0, external=False, flat_index=42, image_command=0xFD900000,
                   load_command=(0xF3000000, 0x07037000))  # 56 RGBA16 transfers, 112 bytes
        command = 0xF5880200  # I8, one TMEM word per row
        return NS(pixel=pixel, palette=None, texture_enabled=True,
                  texture_dimensions=(8, 8), tile_bounds=None,
                  texture_scale=(0xD7001002, 0xFFFFFFFF),
                  render_tile=(command, 0xC030),
                  render_tiles=((0, command, 0xC030), (1, command | 8, 0x01008421),
                                (2, command | 12, 0x02004812)),
                  texture_loads=((pixel, (0xF5100000, 0x07000000)),))

    def test_all_levels_include_stride_texels_outside_visible_bounds(self):
        contract = storage.layered_contract(self.run_fixture(), bytes(112))
        self.assertEqual(contract['format'], 'i8')
        self.assertEqual([(r['width'], r['visible_width'], r['height'], r['offset'], r['bytes'])
                          for r in contract['levels']],
                         [(8, 8, 8, 0, 64), (8, 4, 4, 64, 32), (8, 2, 2, 96, 16)])

    def test_missing_overlap_gap_tail_and_wrong_level_state_reject(self):
        run = self.run_fixture()
        for tiles in (run.render_tiles[:2],
                      run.render_tiles[:2] + ((2, 0xF588020B, 0x02004812),),
                      run.render_tiles[:2] + ((2, 0xF588020D, 0x02004812),),
                      run.render_tiles[:2] + ((2, 0xF588020C, 0x02004811),),
                      run.render_tiles[:2] + ((2, 0xF568020C, 0x02004812),)):
            with self.subTest(tiles=tiles):
                candidate = copy.deepcopy(run)
                candidate.render_tiles = tiles
                self.assertIsNone(storage.layered_contract(candidate, bytes(112)))
        self.assertIsNone(storage.layered_contract(run, bytes(113)))
        run.texture_scale = (0xD7000802, 0xFFFFFFFF)
        self.assertIsNone(storage.layered_contract(run, bytes(112)))

    def test_captured_load_state_is_required_and_dxt_or_later_unknown_load_rejects(self):
        for change in ('missing', 'origin', 'size', 'dxt', 'later'):
            with self.subTest(change=change):
                run = self.run_fixture()
                if change == 'missing':
                    run.texture_loads = ()
                elif change in ('origin', 'size'):
                    run.texture_loads = ((run.pixel, (0xF5100001 if change == 'origin' else 0xF5180000, 0)),)
                elif change == 'dxt':
                    run.pixel.load_command = (0xF3000000, 0x07037001)
                else:
                    run.texture_loads += ((None, None),)
                self.assertIsNone(storage.layered_contract(run, bytes(112)))

    def test_indexed_palette_requires_exact_source_count_and_load_bank(self):
        run = self.run_fixture()
        run.pixel.image_command = 0xFD500000
        run.palette = NS(flat_index=42, mode=1, image_command=0xFD100000,
                         load_command=(0xF0000000, 255 << 14))
        run.texture_loads += ((run.palette, (0xF5100100, 0)),)
        run.render_tiles = tuple((i, cmd ^ 0xC00000, arg) for i, cmd, arg in run.render_tiles)
        run.render_tile = run.render_tiles[0][1:]
        self.assertEqual(storage.layered_contract(run, bytes(624))['palette_size'], 512)
        for change in ('source', 'count', 'bank'):
            candidate = copy.deepcopy(run)
            if change == 'source':
                candidate.palette.flat_index = 43
            elif change == 'count':
                candidate.palette.load_command = (0xF0000000, 15 << 14)
            else:
                candidate.texture_loads = candidate.texture_loads[:-1] + ((candidate.palette, (0xF5100101, 0)),)
            self.assertIsNone(storage.layered_contract(candidate, bytes(624)))

    def test_rgba32_uses_both_tmem_banks_for_stride_and_offset(self):
        run = self.run_fixture()
        run.pixel.image_command = 0xFD180000
        run.pixel.load_command = (0xF3000000, 87 << 12)
        run.texture_loads = ((run.pixel, (0xF5180000, 0)),)
        run.render_tiles = ((0, 0xF5180400, 0xC030), (1, 0xF5180210, 0x01008421),
                            (2, 0xF5180214, 0x02004812))
        run.render_tile = run.render_tiles[0][1:]
        levels = storage.layered_contract(run, bytes(352))['levels']
        self.assertEqual([(level['offset'], level['width'], level['bytes']) for level in levels],
                         [(0, 8, 256), (256, 4, 64), (320, 4, 32)])

    def test_expression_morph_does_not_change_selector_writes(self):
        initial = {'descriptor_indices': {'6': 1, '7': 2, '10': 3, '11': 4}}
        preset = {'index': 2, 'animation_selector': 0, 'reserved_byte': 0, 'morph_shape': 9,
                  'blink_selector_bytes': [5, 6], 'actor_blink_codes': [15, 16],
                  'texture_descriptor_overrides': [0, 7]}
        result = storage.expression_selectors(initial, preset, {'verified': 'hash'})
        self.assertEqual(result['descriptor_indices'], {'6': 5, '7': 6, '10': 3, '11': 7})
        self.assertEqual(result['expression_texture_selection']['stored_preset']['morph_shape'], 9)
        for update in ({'animation_selector': 1}, {'reserved_byte': 1},
                       {'blink_selector_bytes': [246, 6], 'actor_blink_codes': [0, 16]},
                       {'actor_blink_codes': [15, 17]}):
            self.assertIsNone(storage.expression_selectors(initial, {**preset, **update}, {}))

    def test_blink_tables_are_read_from_verified_initializer(self):
        raw = bytes(range(80))
        initial = {'rom_start': '0x0', 'rom_end': '0x50', 'compressed': False,
                   'sha1': hashlib.sha1(raw).hexdigest(), 'expression_presets': [],
                   'descriptor_indices': {'6': 24, '7': 27, '10': 75, '11': 76}}
        manifest = {'entries': {9: initial}, 'expression_consumers': {}}
        choices = storage.selector_choices(manifest, 9, raw)
        self.assertEqual(choices[1][1]['descriptor_indices'], {'6': 25, '7': 28, '10': 75, '11': 76})
        self.assertEqual(choices[2][1]['descriptor_indices']['7'], 29)
        with self.assertRaisesRegex(ValueError, 'source changed'):
            storage.selector_choices(manifest, 9, bytes(80))
