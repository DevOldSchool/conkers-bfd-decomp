import struct
import unittest
from dataclasses import replace
from pathlib import Path
from unittest import mock

from scripts import model_assets as m
from scripts import model_character_defaults as defaults
from scripts import texture_assets


class CharacterDefaultsTests(unittest.TestCase):
    def test_renderer_presets_preserve_other_bindings_and_initializer(self):
        initial = {'preset': 'initializer', 'descriptor_indices': {'6': 0, '7': 0, '10': 3, '11': 4}}
        manifest = {'entries': {40: initial, 41: initial}, 'renderer_texture_presets': {
            40: {'preset': 'stationary', 'descriptor_indices': {'6': 15, '7': 9},
                 'runtime_state': {'actor_0x3C_f32': 0.0, 'actor_0x44_f32': 0.0}}}}
        selected = defaults.preview_defaults(manifest, 40)
        self.assertEqual({'6': 15, '7': 9, '10': 3, '11': 4}, selected['descriptor_indices'])
        self.assertEqual(0, initial['descriptor_indices']['6'])
        self.assertIs(initial, defaults.preview_defaults(manifest, 41))
        for selectors in ({}, {'8': 3}, {'6': -1}, {'7': 256}):
            manifest['renderer_texture_presets'][40]['descriptor_indices'] = selectors
            with self.assertRaisesRegex(ValueError, 'selectors are invalid'):
                defaults.preview_defaults(manifest, 40)
        manifest['expression_preview_presets'] = {40: {'index': 0}}
        with self.assertRaisesRegex(ValueError, 'overlap'):
            defaults.preview_defaults(manifest, 40)
        with self.assertRaisesRegex(ValueError, 'renderer texture consumer changed'):
            defaults.renderer_texture_presets(bytes(256), 0x150EE00C)

    def test_stored_expression_selects_descriptors_without_mutating_initializer(self):
        # A direct blink code is descriptor+10, not an index into header+8.
        payload = struct.pack('>6BH2B', 5, 4, 0, 5, 0, 0, 0, 0, 7)
        initial = defaults.parse_defaults(self.bundle(payload))
        initial['expression_presets'] = defaults.parse_expression_presets(self.bundle(payload))
        manifest = {'entries': {82: initial, 83: initial}, 'expression_preview_presets': {
            82: {'index': 0, 'consumer_sha1': {'test': 'guard'}}}}
        selected = defaults.preview_defaults(manifest, 82)
        self.assertEqual({'6': 5, '7': 4, '10': 3, '11': 7}, selected['descriptor_indices'])
        self.assertEqual({'6': 1, '7': 2, '10': 3, '11': 4}, initial['descriptor_indices'])
        self.assertIs(initial, defaults.preview_defaults(manifest, 83))
        self.assertEqual('explicit-inspection-preset-not-initializer-default',
                         selected['expression_texture_selection']['selection_policy'])
        for field, value in [('morph_shape', 1), ('animation_selector', 1),
                             ('reserved_byte', 1), ('actor_blink_codes', [0, 14]),
                             ('blink_selector_bytes', [246, 4])]:
            with self.subTest(field=field):
                preset = {**initial['expression_presets'][0], field: value}
                changed = {**initial, 'expression_presets': [preset]}
                with self.assertRaises(ValueError):
                    defaults.expression_preview_defaults(changed, {'index': 0, 'consumer_sha1': {}})
        for index in (-1, 1):
            with self.assertRaisesRegex(ValueError, 'outside its stored range'):
                defaults.expression_preview_defaults(initial, {'index': index, 'consumer_sha1': {}})
        manifest['instance_texture_presets'] = {82: {}}
        with self.assertRaisesRegex(ValueError, 'overlap'):
            defaults.preview_defaults(manifest, 82)
        with self.assertRaisesRegex(ValueError, 'expression texture consumer changed'):
            defaults.expression_texture_consumers(bytes(256), 0x1507E5C8)

    def test_instance_preset_preserves_initializer_and_unrelated_models(self):
        initial = {'preset': 'initializer-default', 'header_sha1': 'header',
                   'descriptor_indices': {'6': 0, '7': 0, '10': 0, '11': 0}}
        manifest = {'entries': {59: initial, 60: initial}, 'instance_texture_presets': {
            59: {'preset': 'team-zero', 'segment': 10, 'descriptor_indices': [1, 2, 3, 4],
                 'selected_variant': 0}}}
        selected = defaults.preview_defaults(manifest, 59)
        self.assertEqual(1, selected['descriptor_indices']['10'])
        self.assertEqual(0, selected['descriptor_indices']['11'])
        self.assertEqual(0, initial['descriptor_indices']['10'])
        self.assertEqual(0, selected['instance_texture_selection']['initializer_descriptor_index'])
        self.assertIs(initial, defaults.preview_defaults(manifest, 60))
        self.assertIsNone(defaults.preview_defaults(manifest, 61))
        for bad in (-1, 4):
            manifest['instance_texture_presets'][59]['selected_variant'] = bad
            with self.assertRaisesRegex(ValueError, 'outside its verified range'):
                defaults.preview_defaults(manifest, 59)

    def test_instance_consumer_guard_rejects_missing_or_changed_instructions(self):
        for data, base in ((b'', 0x150830A8), (bytes(96), 0x150830A8), (bytes(96), 0x150830AC)):
            with self.assertRaisesRegex(ValueError, 'instance texture consumer changed'):
                defaults.instance_texture_presets(data, base)

    def bundle(self, expression=b''):
        header = bytearray(64)
        header[8], header[11], header[59], header[60] = 1, 2, 3, 4
        data = struct.pack('>4I', 16, 64, 80 if expression else 0, 0x80000000 | len(expression)) + header + expression
        return data + bytes(-len(data) % 16)

    def test_initializer_selectors_and_optional_expression_are_distinct(self):
        for expression in (b'', b'\xFF' * 300):
            parsed = defaults.parse_defaults(self.bundle(expression))
            self.assertEqual({'6': 1, '7': 2, '10': 3, '11': 4}, parsed['descriptor_indices'])
            self.assertEqual(len(expression), parsed['expression_size'])

    def test_descriptor_ranges_and_padding_fail_closed(self):
        valid = self.bundle(b'\x01' * 300)
        for offset, value in ((0, 24), (4, 48), (8, 96), (12, 0x9000012C), (12, 0x80001000)):
            changed = bytearray(valid)
            struct.pack_into('>I', changed, offset, value)
            with self.assertRaises(ValueError):
                defaults.parse_defaults(bytes(changed))
        with self.assertRaises(ValueError):
            defaults.parse_defaults(valid[:-1] + b'\x01')

    def test_missing_or_null_descriptor_is_not_guessed(self):
        parsed = defaults.parse_defaults(self.bundle())
        self.assertIsNone(defaults.select_descriptor(parsed, [], 6))
        self.assertIsNone(defaults.select_descriptor(parsed, [], 8))
        descriptors = [{'record_index': i, 'flat_index': 0} for i in range(5)]
        self.assertIsNone(defaults.select_descriptor(parsed, descriptors, 6))

    def run_and_payload(self):
        pixel = m.ModelTextureBinding(0xFD100000, segment=6, offset=8,
                                      load_command=(0xF3000000, 0x0700F000))
        palette = m.ModelTextureBinding(0xFD100000, segment=6, offset=64,
                                        load_command=(0xF0000000, 0x063FC000))
        run = m.ModelMaterialRun(0, 1, True, pixel, palette,
            (0xF5080200, 0x00008030),
            ((0, 0xF5080200, 0x00008030), (6, 0xF5100100, 0x06000000),
             (7, 0xF5100000, 0x07000000)),
            (0xF2000000, 0x0001C00C), (0xD7000002, 0xFFFFFFFF),
            (0xFCFFFFFF, 0xFFFCF279), (0xEF18AC3F, 0x04D04DD8), None)
        rows = bytes(range(32))
        # Explicit TLUT at +64; a different palette at the end catches the
        # tempting but incorrect shortcut of always using a trailing palette.
        palette_bytes = b''.join(struct.pack('>H', i * 2 + 1) for i in range(256))
        payload = bytes(8) + rows + bytes(24) + palette_bytes + bytes.fromhex('F801') * 256
        return run, payload, palette_bytes

    def decode(self, run, payload, tables=(), dimensions=(8, 4)):
        preset = {'preset': 'test', 'header_sha1': 'test', 'descriptor_indices': {'6': 0}}
        descriptors = [{'record_index': 0, 'flat_index': 42, 'width': dimensions[0], 'height': dimensions[1]}]
        return m.rom_default_preview_texture(run, preset, descriptors, {42: payload}, tables)

    def test_uses_explicit_offsets_and_odd_row_swizzle(self):
        run, payload, palette = self.run_and_payload()
        texture, status, evidence = self.decode(run, payload)
        self.assertEqual('rom-default-indexed', status)
        expected = b''.join(bytes(payload[8 + y * 8 + (x ^ 4 if y & 1 else x)] for x in range(8)) for y in range(4))
        decoded = texture_assets.decode_ci8_png(texture.png_data, 'linear', 8, 4)
        self.assertEqual(expected + palette, decoded)
        self.assertEqual(64, evidence['palette_byte_offset'])

    def test_unknown_lookup_mismatched_palette_and_short_load_are_unresolved(self):
        run, payload, _ = self.run_and_payload()
        changes = [replace(run, other_mode=None), replace(run, palette=None),
                   replace(run, palette=replace(run.palette, segment=7)),
                   replace(run, palette=replace(run.palette, offset=len(payload))),
                   replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x07000000)))]
        for changed in changes:
            self.assertIsNone(self.decode(changed, payload)[0])

    def wrapped_ci8_run(self):
        run, _, palette = self.run_and_payload()
        tile = (0xF5080C00, 0x00098260)
        run = replace(run, pixel=replace(run.pixel, offset=0,
            load_command=(0xF3000000, 0x0741F000)),
            palette=replace(run.palette, offset=2112), render_tile=tile,
            render_tiles=((0, *tile), (6, 0xF5000100, 0x06000000),
                          (7, 0xF5100000, 0x07000000)),
            tile_bounds=(0xF2002002, 0x000AE0AE))
        # Different rows and upper-TMEM bytes expose a missing address wrap.
        pixels = bytes((i * 37 + i // 48 * 11) & 255 for i in range(2112))
        return run, pixels + palette, palette

    def test_rom_ci8_wraps_indices_below_tlut_and_preserves_the_palette(self):
        run, payload, palette = self.wrapped_ci8_run()
        texture, status, evidence = self.decode(run, payload, dimensions=(44, 44))
        self.assertEqual('rom-default-indexed', status)
        decoded = texture_assets.decode_ci8_png(texture.png_data, 'linear', 44, 44)
        # Rows zero through 41 fit. Row 42 wraps after column 31 and row 43
        # starts at lower-TMEM byte 16, then applies the odd-row word swap.
        expected = b''.join(bytes(payload[((y * 48 + x) ^ (4 if y & 1 else 0)) % 2048]
                                  for x in range(44)) for y in range(44))
        self.assertEqual(expected + palette, decoded)
        self.assertEqual('0x7FF', evidence['tmem_addressing']['index_address_mask'])
        self.assertEqual(2112, evidence['tmem_addressing']['loaded_bytes'])
        changed_upper_tmem = payload[:2048] + bytes(64) + payload[2112:]
        self.assertEqual(texture.png_data,
            self.decode(run, changed_upper_tmem, dimensions=(44, 44))[0].png_data)

    def test_rom_ci8_wrap_rejects_unknown_origin_partial_mode_and_short_transfer(self):
        run, payload, _ = self.wrapped_ci8_run()
        changes = (
            replace(run, other_mode_partial=(0, 0, 0, 0)),
            replace(run, other_mode=None),
            replace(run, render_tiles=run.render_tiles[:-1] + ((7, 0xF5100001, 0x07000000),)),
            replace(run, render_tile=(run.render_tile[0] + 1, run.render_tile[1])),
            replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x073FF000))),
            replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x07800000))),
            replace(run, palette=replace(run.palette, offset=2048)),
        )
        for candidate in changes:
            with self.subTest(candidate=candidate):
                self.assertIsNone(self.decode(candidate, payload, dimensions=(44, 44))[0])
        self.assertIsNone(self.decode(run, payload[:-1], dimensions=(44, 44))[0])

    def test_descriptor_dimensions_require_explicit_bounds_and_valid_payload(self):
        run, payload, _ = self.run_and_payload()
        texture, _, evidence = self.decode(run, payload, dimensions=(32, 32))
        self.assertEqual((8, 4), (texture.width, texture.height))
        self.assertEqual([8, 4], evidence['render_dimensions'])
        self.assertIsNone(self.decode(replace(run, tile_bounds=None), payload, dimensions=(32, 32))[0])
        self.assertIsNone(self.decode(run, payload[:64], dimensions=(32, 32))[0])

    def direct_run(self, rgba=False):
        run, _, _ = self.run_and_payload()
        tile = 0xF5180200 if rgba else 0xF5680200
        return replace(run, palette=None,
            pixel=m.ModelTextureBinding(0xFD180000 if rgba else 0xFD700000,
                segment=6, offset=0, load_command=(0xF3000000, 0x07007000)),
            render_tile=(tile, 0),
            render_tiles=((0, tile, 0), (7, 0xF5180000 if rgba else 0xF5700000, 0x07000000)),
            tile_bounds=(0xF2000000, 0x0000C004 if rgba else 0x0001C004),
            combine_mode=(0xFCFF9880, 0xF514FEFF),
            other_mode=(0xEF182C3F, 0x04D04DD8))

    def test_direct_defaults_decode_rows_and_alpha_from_the_selected_rom_payload(self):
        for rgba in (False, True):
            run = self.direct_run(rgba)
            payload = bytes(range(32 if rgba else 16))
            width = 4 if rgba else 8
            texture, status, evidence = self.decode(run, payload, dimensions=(width, 2))
            self.assertEqual('rom-default-direct-' + ('rgba32' if rgba else 'ia8'), status)
            linear = (payload[24:32] + payload[16:24] + payload[:16] if rgba
                      else payload[12:16] + payload[8:12] + payload[:8])
            expected = linear if rgba else b''.join(bytes((v >> 4,) * 3 + (v & 15,)) for v in linear)
            if not rgba:
                expected = bytes(v * 17 for v in expected)
            self.assertEqual(expected, texture_assets.decode_rgba_png_pixels(texture.png_data, width, 2))
            self.assertEqual(42, evidence['descriptor']['flat_index'])
            self.assertEqual(6, evidence['segment'])
            self.assertIsNone(evidence['palette_byte_offset'])
            self.assertEqual('explicit-other-mode', evidence['lookup_evidence'])
            self.assertIsNone(run.pixel.flat_index)  # Resolving a selector must not mutate the source binding.
            changed = bytes([payload[0] ^ 0xFF]) + payload[1:]
            self.assertNotEqual(texture.png_data, self.decode(run, changed, dimensions=(width, 2))[0].png_data)

    def test_direct_defaults_reject_unsupported_bindings_states_and_spans(self):
        for rgba in (False, True):
            run = self.direct_run(rgba)
            width, payload = (4, bytes(32)) if rgba else (8, bytes(16))
            for changed in (
                    replace(run, pixel=None),
                    replace(run, palette=run.pixel),
                    replace(run, pixel=replace(run.pixel, offset=4)),
                    replace(run, pixel=replace(run.pixel, offset=None)),
                    replace(run, pixel=replace(run.pixel, segment=11)),
                    replace(run, pixel=replace(run.pixel, image_command=0xFD100000)),
                    replace(run, other_mode=None),
                    replace(run, other_mode=(0xEF18AC3F, 0x04D04DD8)),
                    replace(run, other_mode_partial=(0, 0, 0, 0)),
                    replace(run, combine_mode=(0xFCFFFFFF, 0xFFFCF279)),
                    replace(run, texture_coordinates_proven=False),
                    replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x07003000))),
                    replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x07007001)))):
                with self.subTest(rgba=rgba, changed=changed):
                    self.assertIsNone(self.decode(changed, payload, dimensions=(width, 2))[0])
            self.assertIsNone(self.decode(run, payload, dimensions=(width, 4))[0])
            self.assertIsNone(self.decode(run, payload[:-1], dimensions=(width, 2))[0])
            preset = {'preset': 'test', 'header_sha1': 'test', 'descriptor_indices': {'6': 0}}
            self.assertIsNone(m.rom_default_preview_texture(run, preset, [], {}, ())[0])

    def test_trilinear_base_requires_complete_nonoverlapping_mip_layout(self):
        run, payload, _ = self.run_and_payload()
        run = replace(run, combine_mode=(0xFC26A080, 0x151492FF),
                      other_mode=(0xEF19AC3F, 0x04D04DD8),
                      texture_scale=(0xD7000802, 0xFFFFFFFF),
                      pixel=replace(run.pixel, load_command=(0xF3000000, 0x07017000)),
                      render_tiles=run.render_tiles + ((1, 0xF5080204, 0x01004421),))
        texture, status, evidence = self.decode(run, payload)
        self.assertIsNotNone(texture)
        self.assertEqual('rom-default-indexed-trilinear-base', status)
        self.assertEqual([8, 40], [v['pixel_byte_offset'] for v in evidence['mip_levels']])
        self.assertEqual('trilinear-base-at-LOD-fraction-zero', evidence['preview_scope'])
        for tile in ((), ((1, 0xF5080200, 0x01004421),),
                     ((1, 0xF5080204, 0x01004422),), ((1, 0xF5080206, 0x01004421),)):
            self.assertIsNone(self.decode(replace(run, render_tiles=run.render_tiles[:-1] + tile), payload)[0])
        self.assertIsNone(self.decode(replace(run, palette=replace(run.palette, offset=40)), payload)[0])

    def test_every_render_variant_must_agree_on_lookup(self):
        run, payload, _ = self.run_and_payload()
        run = replace(run, other_mode=None, runtime_render_state_offset=0)
        yes = {'entries': [{'offset': '0x0', 'other_mode': ['0xEF18AC3F', '0x04D04DD8']}]}
        no = {'entries': [{'offset': '0x0', 'other_mode': ['0xEF182C3F', '0x04D04DD8']}]}
        self.assertIsNotNone(self.decode(run, payload, (yes, yes))[0])
        self.assertIsNone(self.decode(run, payload, (yes, no))[0])

    def test_zero_alpha_defaults_require_a_proven_invisible_blender_path(self):
        run, payload, _ = self.run_and_payload()
        run = replace(run, combine_mode=(0xFCFF9880, 0xF514FEFF))
        payload = payload[:64] + bytes(512)
        texture, status, evidence = self.decode(run, payload)
        self.assertEqual('rom-default-indexed', status)
        decoded = texture_assets.decode_ci8_png(texture.png_data, 'linear', 8, 4)
        self.assertEqual(bytes(512), decoded[-512:])
        self.assertEqual('unchanged-ROM-palette-alpha', evidence['zero_alpha_preview']['source'])
        low = run.other_mode[1]
        for changed_low in (low | 0x2000, low | 0x1000, low | 0x20, low | 1,
                            low & ~0x4000, low & ~0x40, low ^ 0x01000000):
            changed = replace(run, other_mode=(run.other_mode[0], changed_low))
            self.assertIsNone(self.decode(changed, payload)[0])
        self.assertIsNone(self.decode(replace(run, combine_mode=(0xFCFFFFFF, 0xFFFCF279)), payload)[0])
        self.assertIsNone(self.decode(replace(run, other_mode=None), payload)[0])

    def test_rom_mode_rejects_capture_inputs_before_loading(self):
        with mock.patch.object(m, 'load_model_bundles', side_effect=AssertionError('must not read inputs')):
            with self.assertRaises(ValueError):
                m.extract_model_preview('us', None, Path('textures'), Path('output'), False,
                                        bank_index=1, runtime_material_path=Path('capture.json'), rom_defaults=True)
            with self.assertRaises(ValueError):
                m.extract_model_preview('us', None, Path('textures'), Path('output'), False,
                                        bank_index=4, rom_defaults=True)

    def test_consumer_guard_rejects_changed_rom_instruction(self):
        base = min(defaults.US_CONSUMER_WORDS)
        data = bytearray(max(defaults.US_CONSUMER_WORDS) - base + 4)
        for address, word in defaults.US_CONSUMER_WORDS.items():
            struct.pack_into('>I', data, address - base, word)
        defaults.verify_consumers(bytes(data), base)
        data[0] ^= 1
        with self.assertRaises(ValueError):
            defaults.verify_consumers(bytes(data), base)

    def test_expression_fields_endianness_and_reserved_byte_round_trip(self):
        payload = bytes.fromhex('FF030916078012340005')
        preset = defaults.parse_expression_presets(self.bundle(payload))[0]
        self.assertEqual([255, 3], preset['blink_selector_bytes'])
        self.assertEqual([9, 13], preset['actor_blink_codes'])
        self.assertEqual(9, preset['morph_shape'])
        self.assertEqual(22, preset['morph_transition_duration'])
        self.assertEqual(7, preset['animation_selector'])
        self.assertEqual(128, preset['reserved_byte'])
        self.assertEqual(0x1234, preset['animation_duration_raw'])
        self.assertEqual([0, 5], preset['texture_descriptor_overrides'])
        self.assertEqual(payload, defaults.encode_expression_presets([preset]))
        self.assertEqual([], defaults.parse_expression_presets(self.bundle()))

    def test_expression_stride_index_and_consumer_guards(self):
        with self.assertRaisesRegex(ValueError, 'ten-byte'):
            defaults.parse_expression_presets(self.bundle(bytes(11)))
        with self.assertRaises(ValueError):
            defaults.parse_expression_presets(self.bundle(bytes(10))[:-16])
        presets = defaults.parse_expression_presets(self.bundle(bytes(20)))
        presets.reverse()
        with self.assertRaisesRegex(ValueError, 'index'):
            defaults.encode_expression_presets(presets)
        with self.assertRaisesRegex(ValueError, 'consumer changed'):
            defaults.verify_expression_consumers(bytes(100), 0x1507E908)

    def expression_program_data(self):
        base = 0x80086CC4
        data = bytearray(0x8009D915 - base)
        data[0x8009D910 - base:] = bytes((5, 6, 7, 10, 11))
        for index, action in enumerate((5, 6, 7, 10, 11)):
            pointer = base + 0x100 + index * 32
            count = 2 if action == 11 else 1
            struct.pack_into('>IB3s', data, (action - 1) * 8, pointer, count, b'ABC')
            for part in range(count):
                data[pointer - base + part * 16:pointer - base + (part + 1) * 16] = bytes((1, 2, 3, part, 4, 5, 6, 7)) * 2
        return data, base

    def test_expression_action_programs_preserve_order_and_all_bytes(self):
        data, base = self.expression_program_data()
        programs = defaults.parse_expression_animation_programs(bytes(data), base)
        self.assertEqual([5, 6, 7, 10, 11], [p['native_action'] for p in programs])
        self.assertEqual([1, 1, 1, 1, 2], [p['record_count'] for p in programs])
        self.assertEqual([0, 1], [r['dispatch_kind'] for r in programs[-1]['records']])
        for program in programs:
            pointer = int(program['program_address'], 0) - base
            raw = b''.join(bytes.fromhex(record['raw_bytes']) for record in program['records'])
            self.assertEqual(bytes(data[pointer:pointer + program['decoded_size']]), raw)
            self.assertTrue(program['table_bytes'].endswith(b'ABC'.hex()))

    def test_expression_action_program_bounds_and_selector_guard(self):
        original, base = self.expression_program_data()
        for target, replacement in ((0x8009D910 - base, 255), (4 * 8 + 4, 0),
                                    (0x100 + 3, 3)):
            data = original.copy()
            data[target] = replacement
            with self.assertRaises(ValueError):
                defaults.parse_expression_animation_programs(bytes(data), base)
        data = original.copy()
        struct.pack_into('>I', data, 4 * 8, base + (len(data) & ~3) - 4)
        with self.assertRaisesRegex(ValueError, 'exceeds ROM data'):
            defaults.parse_expression_animation_programs(bytes(data), base)
