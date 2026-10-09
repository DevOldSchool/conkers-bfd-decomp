"""Complete TMEM coverage and native selector semantics must be explicit."""
import copy
import hashlib
import struct
from dataclasses import replace
from types import SimpleNamespace as NS
import unittest

from scripts import texture_model_storage as storage


class ModelStorageTests(unittest.TestCase):
    def authored_fixture(self):
        pixel = storage.models.ModelTextureBinding(0xFD100000, 42, 0,
                                                   load_command=(0xF3000000, 0x070FF000))
        palette = storage.models.ModelTextureBinding(0xFD100000, 42, 1,
                                                     load_command=(0xF0000000, 0x063FC000))
        tile, bounds = (0xF5080400, 0x14040), (0xF2002002, 0x3E07E)
        draw = (0xF5081000, 0x01014060)
        run = storage.models.ModelMaterialRun(
            0, 1, True, pixel, palette, draw, ((0, *tile), (1, *draw)),
            (0xF2002002, 0x010FE07E), (0xD7000902, 0xFFFFFFFF), None, None, None,
            texture_loads=((pixel, (0xF5100000, 0x07000000)),
                           (palette, (0xF5000100, 0x06000000))))
        commands = [(0xFD100000, 42), (0xE6000000, 0), pixel.load_command,
                    (0xE7000000, 0), (0xE6000000, 0), (0xFD100000, 0x40002A),
                    palette.load_command, (0xE7000000, 0), tile, bounds]
        return run, commands

    def authored(self, run, commands, payload=bytes(1024)):
        data = b''.join(struct.pack('>II', *pair) for pair in commands)
        geometry = NS(display_list_offset=0, face_command_offsets=(len(data),))
        return storage.authored_contract(data, geometry, run, payload)

    def test_authored_storage_retains_draw_tile_and_complete_source_provenance(self):
        run, commands = self.authored_fixture()
        for tail in ([], [(0xD9FFFFFF, 0x400)]):
            contract, evidence = self.authored(run, commands + tail)
            self.assertEqual((contract['format'], contract['width'], contract['height']), ('ci8', 16, 32))
            self.assertEqual(contract['levels'][0]['bytes'], 512)
            self.assertEqual(contract['palette_size'], 512)
            self.assertEqual(evidence['commands'], [list(pair) for pair in commands + tail])
            self.assertEqual((evidence['storage_tile'], evidence['draw_tile']), (0, 1))
            self.assertEqual(run.texture_scale[0], 0xD7000902)
            self.assertEqual(run.render_tile[1] >> 24, 1)

    def test_inherited_tiles_intervening_commands_and_wrong_pointer_do_not_qualify(self):
        run, commands = self.authored_fixture()
        for changed in (commands[:8], commands[:8] + [(0xE7000000, 0), commands[9]],
                        commands + [(0xDE000000, 0x08000040)],
                        [(0xFD100000, 43)] + commands[1:],
                        commands[:5] + [(0xFD100000, 0x40002B)] + commands[6:]):
            self.assertIsNone(self.authored(run, changed))
        self.assertIsNone(self.authored(replace(run, render_tiles=run.render_tiles[1:]), commands))

    def test_authored_storage_requires_full_payload_and_captured_load(self):
        run, commands = self.authored_fixture()
        self.assertIsNone(self.authored(run, commands, bytes(1025)))
        self.assertIsNone(self.authored(replace(run, texture_loads=()), commands))
        bad_bounds = commands[:-1] + [(0xF2002002, 0x3E03E)]
        self.assertIsNone(self.authored(run, bad_bounds))

    def test_complete_detail_source_requires_every_plane_and_zero_tail(self):
        try:
            from tests.test_model_assets import ModelAssetTests
        except ModuleNotFoundError:
            from test_model_assets import ModelAssetTests
        for size in (0, 1):
            run = ModelAssetTests().detail_indexed_run(size)
            palette_size = 32 if size == 0 else 512
            payload = bytes(range(160)) + bytes(palette_size)
            preview, _ = storage.models.choose_preview_texture(run, {}, {42: payload})
            contract = storage.detail_contract(run, preview, payload)
            self.assertEqual([r['format'] for r in contract['levels']],
                             ['ci4' if size == 0 else 'ci8'] * 2 + ['ia4'])
            self.assertEqual([r['offset'] for r in contract['levels']], [0, 64, 96])
            self.assertEqual(sum(r['bytes'] for r in contract['levels']), 160)
            aligned = payload[:160] + bytes(32) + payload[160:]
            self.assertEqual(storage.detail_contract(run, preview, aligned)['zero_alignment']['size'], 32)
            for tail in (bytes(33), b'x' + bytes(31), bytes(96)):
                self.assertIsNone(storage.detail_contract(run, preview, payload[:160] + tail + payload[160:]))
            self.assertIsNone(storage.detail_contract(run, None, payload))
            gap = replace(run, render_tiles=tuple(
                (i, cmd + 1 if i == 0 else cmd, arg) for i, cmd, arg in run.render_tiles))
            self.assertIsNone(storage.detail_contract(gap, preview, payload))

    def test_bound_storage_only_relocates_authenticated_zero_origin_and_palette_tail(self):
        try:
            from tests.test_model_assets import ModelAssetTests
        except ModuleNotFoundError:
            from test_model_assets import ModelAssetTests
        from unittest.mock import patch
        run = ModelAssetTests().direct_ci4_run()
        pixel = replace(run.pixel, flat_index=None, mode=None, segment=6, offset=0)
        palette = replace(run.palette, flat_index=None, mode=None, segment=6, offset=128)
        bound = replace(run, pixel=pixel, palette=palette,
                        texture_loads=((pixel, (0xF5100000, 0)), (palette, (0xF5100100, 0))))
        preview = NS(flat_index=42, format=2, size=0)
        with patch.object(storage, 'layered_contract', return_value={'verified': True}) as check:
            self.assertEqual(storage.bound_contract(bound, preview, bytes(160)), {'verified': True})
            mapped = check.call_args.args[0]
            self.assertEqual((mapped.pixel.flat_index, mapped.pixel.mode, mapped.pixel.segment), (42, 0, None))
            self.assertEqual((mapped.palette.flat_index, mapped.palette.mode), (42, 2))
            self.assertEqual(mapped.texture_loads[0][0], mapped.pixel)
            self.assertEqual(mapped.texture_loads[1][0], mapped.palette)
            check.reset_mock()
            for candidate in (replace(bound, pixel=replace(pixel, offset=4)),
                              replace(bound, palette=replace(palette, offset=127)),
                              replace(bound, palette=replace(palette, segment=7))):
                self.assertIsNone(storage.bound_contract(candidate, preview, bytes(160)))
            check.assert_not_called()

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
        aligned = storage.layered_contract(run, bytes(384), storage_extensions=True)
        self.assertEqual(aligned['zero_alignment'], {'offset': 352, 'size': 32, 'alignment': 128})
        self.assertIsNone(storage.layered_contract(run, bytes(512), storage_extensions=True))
        self.assertIsNone(storage.layered_contract(run, bytes(352) + b'x' + bytes(31), storage_extensions=True))

    def indexed_fixture(self):
        run = self.run_fixture()
        run.pixel.image_command = 0xFD500000
        run.palette = NS(flat_index=42, mode=1, image_command=0xFD100000,
                         load_command=(0xF0000000, 255 << 14))
        run.texture_loads += ((run.palette, (0xF5100100, 0)),)
        run.render_tiles = tuple((i, cmd ^ 0xC00000, arg) for i, cmd, arg in run.render_tiles)
        run.render_tile = run.render_tiles[0][1:]
        return run

    def test_storage_extension_accepts_only_zero_padding_to_64_bytes(self):
        run = self.indexed_fixture()
        self.assertIsNone(storage.layered_contract(run, bytes(640)))
        contract = storage.layered_contract(run, bytes(640), storage_extensions=True)
        self.assertEqual(contract['zero_alignment'], {'offset': 112, 'size': 16, 'alignment': 64})
        self.assertEqual(sum(level['bytes'] for level in contract['levels']), 112)
        for payload in (bytes(641), bytes(704), bytes(112) + b'x' + bytes(527)):
            self.assertIsNone(storage.layered_contract(run, payload, storage_extensions=True))
        native = storage.layered_contract(self.run_fixture(), bytes(128), storage_extensions=True)
        self.assertEqual(native['zero_alignment'], contract['zero_alignment'])

    def test_npot_mips_require_clamping_and_exact_rounded_mask_periods(self):
        run = self.indexed_fixture()
        run.texture_dimensions = (32, 44)
        run.texture_scale = (0xD7001802, 0xFFFFFFFF)
        run.pixel.load_command = (0xF3000000, 943 << 12)
        run.render_tiles = ((0, 0xF5480800, 0x98250), (1, 0xF54804B0, 0x1094641),
                            (2, 0xF54802DC, 0x2090A32), (3, 0xF54802E7, 0x308CE23))
        run.render_tile = run.render_tiles[0][1:]
        self.assertIsNone(storage.layered_contract(run, bytes(2400)))
        contract = storage.layered_contract(run, bytes(2400), storage_extensions=True)
        self.assertTrue(contract['clamped_npot_dimensions'])
        self.assertEqual([level['height'] for level in contract['levels']], [44, 22, 11, 5])
        self.assertEqual(sum(level['bytes'] for level in contract['levels']), 1888)
        for changed in (0x1094641 ^ 0x80000, 0x1094641 + 0x4000, 0x1094641 ^ 1):
            candidate = copy.deepcopy(run)
            candidate.render_tiles = (run.render_tiles[0], (1, 0xF54804B0, changed), *run.render_tiles[2:])
            self.assertIsNone(storage.layered_contract(candidate, bytes(2400), storage_extensions=True))

    def test_storage_overlap_retains_complete_transfer_and_later_palette(self):
        run = self.indexed_fixture()
        run.pixel.load_command = (0xF3000000, 1055 << 12)
        run.texture_dimensions = (44, 44)
        run.texture_scale = (0xD7000002, 0xFFFFFFFF)
        run.render_tile = (0xF5480C00, 0)
        run.render_tiles = ((0, *run.render_tile),)
        self.assertIsNone(storage.layered_contract(run, bytes(2624)))
        contract = storage.layered_contract(run, bytes(2624), storage_extensions=True)
        self.assertEqual(contract['pixel_tlut_overlap_bytes'], 64)
        self.assertEqual((contract['width'], contract['height']), (48, 44))
        self.assertEqual(contract['levels'][0]['bytes'], 2112)
        run.texture_loads = tuple(reversed(run.texture_loads))
        self.assertIsNone(storage.layered_contract(run, bytes(2624), storage_extensions=True))

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

    def test_action_selectors_require_verified_attachment_only_program_and_identity(self):
        initial = {'descriptor_indices': {'6': 1, '7': 2, '10': 3, '11': 4}}
        preset = {'index': 22, 'animation_selector': 2, 'native_action': 6, 'reserved_byte': 0,
                  'morph_shape': 10, 'blink_selector_bytes': [25, 25], 'actor_blink_codes': [35, 35],
                  'texture_descriptor_overrides': [37, 37]}
        program = {'selector': 2, 'native_action': 6, 'record_count': 1, 'operations': [
            {'dispatch_kind': 1, 'operation': 'attachment-constructor', 'bank': 9}]}
        initial['expression_presets'] = [preset]
        manifest = {'entries': {0: initial}, 'expression_constructors': {
            'family': 'ROM-expression-attachment-constructors', 'programs': [program],
            'consumer_sha1': {'whole-native-functions': 'verified'}}}
        choices = storage.action_selector_choices(manifest, 0)
        self.assertEqual(choices[0][0], 'action-expression-22')
        self.assertEqual(choices[0][1]['descriptor_indices'], {'6': 25, '7': 25, '10': 37, '11': 37})
        proof = choices[0][1]['expression_texture_selection']
        self.assertEqual(proof['stored_preset']['animation_selector'], 2)
        self.assertEqual(proof['action_program'], program)
        self.assertEqual(storage.action_selector_choices(manifest, 1), [])
        self.assertIsNone(storage.expression_selectors(initial, preset, {}))
        for changed in ({**program, 'selector': 3}, {**program, 'native_action': 7},
                        {**program, 'record_count': 2}, {**program, 'operations': []},
                        {**program, 'operations': [{'dispatch_kind': 0, 'operation': 'parent-modification', 'bank': 1}]}):
            self.assertIsNone(storage.expression_selectors(initial, preset, {}, action_program=changed))

    def renderer_fixture(self):
        return {'entries': {123: {'descriptor_indices': {'6': 7, '10': 2, '11': 3}}},
                'renderer_texture_presets': {123: {
                    'consumer_sha1': {
                        '0x150F1CB0': '4ceb60c5b35d31cc6e2df4d6a5b06b979ffb86e3',
                        '0x150622F8': 'acb3c86862962cf9c98de7e18d177209c2c0bcb0'},
                    'model_id_load': {'address': '0x15061BD8', 'word': '0x92700004'},
                    'descriptor_indices': {'10': 12, '11': 19}}}}

    def test_renderer_damage_precedence_and_animation_preserve_other_selectors(self):
        manifest = self.renderer_fixture()
        before = copy.deepcopy(manifest)
        choices = storage.renderer_selector_choices(manifest, 123)
        self.assertEqual(len(choices), 8)
        outcomes = {}
        for _, choice in choices:
            state = choice['renderer_texture_selection']['runtime_state']
            outcomes[state['actor_0x84_u16'], state['actor_0x2E4_u32']] = choice['descriptor_indices']
        for animation, segment10 in ((0, 12), (20, 27)):
            for damage, segment11 in ((0, 19), (3, 20), (12, 23), (15, 23)):
                self.assertEqual(outcomes[animation, damage], {'6': 7, '10': segment10, '11': segment11})
        self.assertEqual(manifest, before)
        self.assertEqual(storage.renderer_selector_choices(manifest, 40), [])
        self.assertEqual(storage.renderer_selector_choices({'entries': {}}, 123), [])

    def test_renderer_variants_require_native_and_model_binding_evidence(self):
        for field in ('consumer_sha1', 'model_id_load', 'descriptor_indices'):
            manifest = self.renderer_fixture()
            manifest['renderer_texture_presets'][123][field] = {}
            with self.subTest(field=field), self.assertRaisesRegex(ValueError, 'evidence changed'):
                storage.renderer_selector_choices(manifest, 123)
        with self.assertRaisesRegex(ValueError, 'evidence changed'):
            storage.renderer_selector_choices({'entries': {123: {}}}, 123)

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
