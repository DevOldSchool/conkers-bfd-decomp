import hashlib
import struct
import unittest
from dataclasses import dataclass, replace
from types import SimpleNamespace
from unittest.mock import patch

from scripts import model_assets as models, model_attachment_updates as updates


@dataclass(frozen=True)
class Geometry:
    material_runs: tuple
    vertices: tuple = ('unchanged vertices',)
    faces: tuple = ('unchanged faces',)


class AttachmentUpdatesTests(unittest.TestCase):
    code_base = 0x15000000
    data_base = 0x80082B20

    def source(self):
        code, data = bytearray(0x120000), bytearray(0x20000)
        for address, text in updates.DATA_SPANS:
            raw = bytes.fromhex(text)
            data[address-self.data_base:address-self.data_base+len(raw)] = raw
        return code, data

    def context(self, code, data, original=None):
        original = code if original is None else original
        pins = [(a, n, hashlib.sha1(original[a-self.code_base:a-self.code_base+n]).hexdigest())
                for a, n, _ in updates.CONSUMERS]
        with patch.object(updates, 'CONSUMERS', pins):
            return updates.material_context(code, self.code_base, data, self.data_base)['models'][0]

    def geometry_fixture(self):
        raw = bytearray(0x5B8)
        struct.pack_into('>II', raw, 0x340, 0xF2002002, 0x0001E0FE)
        digest = hashlib.sha1(raw).hexdigest()
        with patch.object(updates, 'MODEL_SHA1', digest):
            context = self.context(*self.source())
        pixel = models.ModelTextureBinding(0xFD180000, segment=6, offset=0,
                                           load_command=(0xF3000000, 0x071FF000))
        run = models.ModelMaterialRun(0, 16, True, pixel, None, (0xF5180400, 0x00018030),
            ((0, 0xF5180400, 0x00018030), (7, 0xF5180000, 0x07000000)),
            (0xF2002002, 0x0001E0FE), (0xD7000002, 0xFFFFFFFF),
            (0xFCFF9880, 0xF514FEFF), (0xEF182C3F, 0x04D049D8), None)
        return raw, Geometry((run, replace(run, first_face=16, face_count=44))), context, digest

    def test_initial_texture_and_float32_tile_origin_are_paired(self):
        context = self.context(*self.source())
        self.assertEqual(80, context['entry'])
        self.assertEqual(397, context['texture_binding']['selector']['excluded_parent_0x84'])
        self.assertEqual([7203], context['texture_binding']['bindings']['6']['flats'])
        scale = struct.unpack('>f', bytes.fromhex('3c23d70a'))[0]
        self.assertEqual(0xF200203E, updates.initial_tile_word(scale))
        self.assertEqual([8, 64], context['geometry_update']['texture_dimensions'])

    def test_every_consumer_and_data_byte_is_guarded(self):
        original, data = self.source()
        for address, size, _ in updates.CONSUMERS:
            code = bytearray(original);code[address-self.code_base+size-1] ^= 1
            with self.subTest(consumer=hex(address)), self.assertRaises(ValueError):
                self.context(code, data, original)
        for address, text in updates.DATA_SPANS:
            for i in range(len(bytes.fromhex(text))):
                code, data = self.source();data[address-self.data_base+i] ^= 1
                with self.subTest(data=hex(address), offset=i), self.assertRaises(ValueError):
                    self.context(code, data)

    def test_only_first_run_uvs_move_and_storage_is_unchanged(self):
        raw, source, context, digest = self.geometry_fixture();saved = bytes(raw)
        with patch.object(updates, 'MODEL_SHA1', digest):
            result, evidence = updates.preview_geometry(raw, source, context)
        self.assertEqual(saved, raw)
        self.assertIs(result.vertices, source.vertices)
        self.assertIs(result.faces, source.faces)
        self.assertIs(result.material_runs[1], source.material_runs[1])
        self.assertEqual(context['geometry_update'], evidence)
        for s, t in ((0, 0), (2000, -80), (-120, 9000)):
            v = SimpleNamespace(s=s, t=t)
            before = models.texture_coordinates(v, source.material_runs[0])
            after = models.texture_coordinates(v, result.material_runs[0])
            self.assertEqual(before[0], after[0])
            self.assertAlmostEqual(15 / 64, after[1] - before[1])

    def test_changed_model_command_and_preset_are_rejected(self):
        raw, source, context, digest = self.geometry_fixture()
        with patch.object(updates, 'MODEL_SHA1', digest):
            changed = bytearray(raw);changed[0x340] ^= 1
            with self.assertRaises(ValueError):updates.preview_geometry(changed, source, context)
            for field, value in [('command_offset', 0x348), ('texture_dimensions', [8, 49]),
                                 ('preview_command', [0xF2002002, 0x0001E0FE]),
                                 ('affected_material_runs', [1])]:
                bad = {**context, 'geometry_update': {**context['geometry_update'], field: value}}
                with self.subTest(field=field), self.assertRaises(ValueError):
                    updates.preview_geometry(raw, source, bad)

    def test_mask_load_and_source_span_changes_fail_closed(self):
        raw, source, context, digest = self.geometry_fixture();run = source.material_runs[0]
        with patch.object(updates, 'MODEL_SHA1', digest):
            for bad in (replace(run, render_tile=(0xF5180400, 0)),
                        replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x070FF000))),
                        replace(run, texture_dimensions=(8, 49)), replace(run, face_count=15)):
                with self.assertRaises(ValueError):
                    updates.preview_geometry(raw, replace(source, material_runs=(bad, source.material_runs[1])), context)

    def test_capture_state_and_unrelated_models_do_not_get_rom_update(self):
        raw, source, context, digest = self.geometry_fixture()
        self.assertEqual((source, None), updates.preview_geometry(raw, source, context, {0: {'captured': True}}))
        self.assertEqual((source, None), updates.preview_geometry(raw, source, None))
        self.assertEqual((source, None), models.apply_rom_attachment_preview_update(raw, source, {}))
