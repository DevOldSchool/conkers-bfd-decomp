import copy
import hashlib
import struct
import unittest
from dataclasses import replace
from unittest.mock import patch

from scripts import model_assets as models
from scripts import model_timer_texture_bindings as timer


class TimerTextureBindingTests(unittest.TestCase):
    base = 0x15000000

    def source(self):
        code = bytearray(0x190000)
        for address, word in timer.GUARDS:
            struct.pack_into('>I', code, address - self.base, word)
        return code

    def context(self, code=None, original=None, ticks=0):
        code = self.source() if code is None else code
        original = code if original is None else original
        pins = [(a, n, hashlib.sha1(original[a-self.base:a-self.base+n]).hexdigest())
                for a, n, _ in timer.CONSUMERS]
        with patch.object(timer, 'CONSUMERS', pins):
            return timer.material_context(code, self.base, preview_ticks=ticks)['models'][0]

    def texture_run(self):
        return models.ModelMaterialRun(
            first_face=0, face_count=2, texture_enabled=True,
            pixel=models.ModelTextureBinding(0xFD700000, segment=1, offset=0,
                                            load_command=(0xF3000000, 0x0707F000)),
            palette=None, render_tile=(0xF5600200, 0x00014040),
            render_tiles=((0, 0xF5600200, 0x00014040), (7, 0xF5700000, 0x07000000)),
            tile_bounds=(0xF2000000, 0x0003C07C), texture_scale=(65535, 65535),
            combine_mode=(0xFC121824, 0xFF33FFFF), other_mode=(0xEF082C3F, 0x00504240),
            runtime_render_state_offset=None)

    def test_decimal_boundaries_and_correlated_presets(self):
        for ticks, digits in ((0, [0, 0, 0, 0]), (29, [0, 0, 0, 0]),
                              (30, [0, 0, 0, 1]), (1799, [0, 0, 5, 9]),
                              (1800, [0, 1, 0, 0]), (179999, [9, 9, 5, 9]),
                              (180000, [0, 0, 0, 0])):
            with self.subTest(ticks=ticks):
                self.assertEqual(digits, list(timer.digit_selectors(ticks).values()))
        context = self.context(ticks=(12 * 60 + 34) * 30)
        self.assertEqual((9, 186, 0), tuple(context[k] for k in ('bank', 'entry', 'segment')))
        state = context['texture_binding']
        self.assertEqual('12:34', state['preview_state']['display'])
        self.assertEqual([4526, 4527, 4528, 4529],
                         [b['selected_flat'] for b in state['bindings'].values()])
        self.assertTrue(all(len(b['flats']) == 10 for b in state['bindings'].values()))

    def test_invalid_timer_values_are_rejected(self):
        for value in (-1, 0x80000000, True, 0.0, '0', None):
            with self.subTest(value=value), self.assertRaises(ValueError):
                timer.digit_selectors(value)

    def test_changed_consumers_and_instruction_guards_are_rejected(self):
        original = self.source()
        for address, size, _ in timer.CONSUMERS:
            code = bytearray(original)
            code[address-self.base+size-1] ^= 1
            with self.subTest(address=hex(address)), self.assertRaises(ValueError):
                self.context(code, original)
        for address, _ in timer.GUARDS:
            code = bytearray(original)
            code[address-self.base+3] ^= 1
            with self.subTest(guard=hex(address)), self.assertRaises(ValueError):
                self.context(code)
        with self.assertRaises(ValueError):
            self.context(bytearray(4), original)

    def test_every_retained_glyph_must_decode_and_selection_is_preserved(self):
        context = self.context(ticks=12 * 60 * 30)
        payloads = {4525 + i: bytes([i * 17]) * 256 for i in range(10)}
        texture, status, proof = models.rom_object_binding_preview_texture(
            self.texture_run(), {}, payloads, [], context)
        self.assertEqual('rom-direct-binding-texture', status)
        expected = models.choose_preview_texture(replace(self.texture_run(), pixel=replace(
            self.texture_run().pixel, flat_index=4526, mode=0, segment=None, offset=None)), {}, payloads)[0]
        self.assertEqual(expected.png_data, texture.png_data)
        self.assertEqual(10, len(proof['decoded_variants']))
        for value in (None, bytes(255), bytes(257)):
            broken = {**payloads, 4534: value}
            self.assertIsNone(models.rom_object_binding_preview_texture(
                self.texture_run(), {}, broken, [], context)[0])

    def test_binding_cannot_escape_proven_source_or_render_state(self):
        context = self.context()
        payloads = {4525+i: bytes(256) for i in range(10)}
        run = self.texture_run()
        candidates = (replace(run, pixel=replace(run.pixel, segment=8)),
                      replace(run, pixel=replace(run.pixel, offset=1)),
                      replace(run, pixel=replace(run.pixel, external=True)),
                      replace(run, pixel=replace(run.pixel, flat_index=4525)),
                      replace(run, palette=run.pixel),
                      replace(run, texture_coordinates_proven=False),
                      replace(run, other_mode=None),
                      replace(run, other_mode=(0xEF08AC3F, 0x00504240)))
        for candidate in candidates:
            with self.subTest(candidate=candidate):
                self.assertIsNone(models.rom_object_binding_preview_texture(
                    candidate, {}, payloads, [], context)[0])
        for field, value in (('selected_index', -1), ('selected_index', True),
                             ('selected_index', 10), ('selected_flat', 4530),
                             ('image_layout', [16, 32, 4, 0])):
            bad = copy.deepcopy(context)
            bad['texture_binding']['bindings']['1'][field] = value
            self.assertIsNone(models.rom_object_binding_preview_texture(run, {}, payloads, [], bad)[0])
        self.assertEqual((None, 'rom-object-renderer-unresolved', None),
                         models.rom_object_preview_texture(run, {}, payloads, [], context))
