"""A rendered preview earns reconstruction credit only for its entire payload."""
from contextlib import ExitStack
import hashlib
from pathlib import Path
from types import SimpleNamespace
import unittest
from unittest.mock import patch

from scripts import texture_assets as t, texture_native as native, texture_model_catalog as catalog
from scripts import model_shc_boat_appearance as boat


class ModelTextureCatalogTests(unittest.TestCase):
    def test_captured_binding_preserves_scope_and_requires_both_full_inverses(self):
        payload = bytes(range(256)) * 6
        png = t.encode_ci8_png(payload, t.ROW_LAYOUT_TMEM, 32, 32)
        preview = SimpleNamespace(flat_index=4195, format=2, size=1, width=32,
                                  height=32, png_data=png, sha1=hashlib.sha1(png).hexdigest())
        evidence = boat.contract()
        # Existing boat tests cover the ROM/model/metadata guards. Isolate the
        # catalog adapter to test that a valid-looking partial view earns no credit.
        with patch.object(boat, 'checked_model', return_value=('geometry', {})), \
                patch.object(boat, 'map_geometry', return_value='mapped'), \
                patch.object(boat, 'decode_textures', return_value=[None, None, preview, preview]) as decoder:
            result = catalog.captured_boat_contract(b'native source', 'rom digest', {4195: payload})
            self.assertEqual(result['family'], 'model-captured-storage')
            self.assertEqual(result['consumer']['context'], evidence['context'])
            self.assertEqual(result['consumer']['provenance'], evidence['provenance'])
            self.assertFalse(result['consumer']['capture_replayed_locally'])
            with self.assertRaisesRegex(ValueError, 'complete source inverse'):
                catalog.captured_boat_contract(b'native source', 'rom digest', {4195: payload + b'tail'})
            other = SimpleNamespace(**{**vars(preview), 'flat_index': 4196})
            decoder.return_value = [None, None, preview, other]
            with self.assertRaisesRegex(ValueError, 'complete source inverse'):
                catalog.captured_boat_contract(b'native source', 'rom digest', {4195: payload})

    def test_binding_variant_retains_the_proven_native_palette_and_source_identity(self):
        for fmt, size in ((2, 0), (2, 1), (0, 3)):
            pixel = catalog.models.ModelTextureBinding(0xFD100000, segment=4, offset=0)
            palette = catalog.models.ModelTextureBinding(0xFD100000, segment=5, offset=0) if fmt == 2 else None
            run = catalog.models.ModelMaterialRun(0, 1, True, pixel, palette, None, (),
                                                  None, None, None, None, None)
            first = SimpleNamespace(flat_index=9, format=fmt, size=size, width=32, height=32)
            preview = SimpleNamespace(flat_index=10, format=fmt, size=size, width=32, height=32, sha1='checked-png')
            variant = {'flat_index': 10, 'png_sha1': 'checked-png'}
            with patch.object(catalog.models, 'choose_preview_texture', return_value=(preview, 'verified')) as decoder:
                self.assertEqual(catalog.binding_variant(run, first, variant, {10: b'payload'}, [], {}), (preview, 'verified'))
                mapped = decoder.call_args.args[0]
                self.assertEqual(mapped.pixel.flat_index, 10)
                self.assertIsNone(mapped.pixel.segment)
                if palette:
                    self.assertEqual((mapped.palette.flat_index, mapped.palette.mode), (10, 2 if size == 0 else 1))
                else:
                    self.assertIsNone(mapped.palette)
                self.assertEqual(run.pixel.segment, 4)
                for changes in ({'png_sha1': 'changed'}, {'flat_index': 11}):
                    with self.assertRaisesRegex(ValueError, 'complete ROM binding proof'):
                        catalog.binding_variant(run, first, {**variant, **changes}, {}, [], {})
                first.width = 64
                with self.assertRaisesRegex(ValueError, 'complete ROM binding proof'):
                    catalog.binding_variant(run, first, variant, {}, [], {})

    def test_binding_variant_requires_a_resolved_image_before_any_credit(self):
        pixel = catalog.models.ModelTextureBinding(0xFD100000, segment=4, offset=0)
        run = catalog.models.ModelMaterialRun(0, 1, True, pixel, None, None, (), None, None, None, None, None)
        first = SimpleNamespace(format=0, size=3, width=32, height=32)
        with patch.object(catalog.models, 'choose_preview_texture', return_value=(None, 'unresolved')), \
                patch.object(catalog.models, 'rom_object_preview_texture', return_value=(None, 'unresolved', None)), \
                self.assertRaisesRegex(ValueError, 'complete ROM binding proof'):
            catalog.binding_variant(run, first, {'flat_index': 10, 'png_sha1': 'expected'}, {}, [], {})

    def preview(self):
        payload = bytes(range(256)) + bytes(range(256)) * 2
        png = t.encode_ci8_png(payload, t.ROW_LAYOUT_TMEM, 32, 8)
        return payload, SimpleNamespace(flat_index=9, format=2, size=1,
                                        width=32, height=8, png_data=png)

    def test_full_payload_required_including_every_palette_byte(self):
        payload, preview = self.preview()
        contract = catalog.full_payload_contract(preview, payload)
        self.assertEqual((contract['format'], contract['width'], contract['height']),
                         ('ci8', 32, 8))
        self.assertIsNone(catalog.full_payload_contract(preview, payload + b'trailing'))
        changed = bytearray(payload)
        changed[-1] ^= 1
        self.assertIsNone(catalog.full_payload_contract(preview, bytes(changed)))

    def test_visual_alpha_transform_is_not_a_reconstructible_source(self):
        payload = bytes(range(128))
        png = native.encode_png(payload, 'i8', t.ROW_LAYOUT_TMEM, 16, 8)
        rgba = bytearray(t.decode_rgba_png_pixels(png, 16, 8))
        rgba[3::4] = bytes([255]) * 128
        preview = SimpleNamespace(format=4, size=1, width=16, height=8,
                                  png_data=t.encode_rgba_png(16, 8, bytes(rgba)))
        self.assertIsNone(catalog.full_payload_contract(preview, payload))

    def sequence_load(self, *, excluded=(), bound=True, wrong_rom=False):
        payload, preview = self.preview()
        rom = b'synthetic reference'
        record = {'flat_index': 9, 'format': 2, 'size': 1, 'width': 32, 'height': 8,
                  'file': 'image.png', 'png_sha1': hashlib.sha1(preview.png_data).hexdigest(),
                  'texture_status': 'verified-sequence-frame'}
        manifest = {'normalized_sha1': 'wrong' if wrong_rom else hashlib.sha1(rom).hexdigest(),
                    'images': [record, record], 'bindings': [{
                        'model': [4, 7, 0], 'material_run': 3, 'kind': 'scene-texture-state',
                        'frames': [{'flat_index': 9, 'png_sha1': record['png_sha1']}]}] if bound else []}
        with ExitStack() as stack:
            stack.enter_context(patch.object(catalog.models, 'BANK_INDICES', ()))
            stack.enter_context(patch.object(catalog.sequences, 'build_export',
                                            return_value=(manifest, {'image.png': preview.png_data})))
            stack.enter_context(patch.object(catalog.models, 'load_object_material_context',
                                            return_value={'models': []}))
            stack.enter_context(patch.object(catalog.models, 'load_character_defaults', return_value=None))
            return catalog.load(Path('/synthetic'), rom,
                                [SimpleNamespace(index=9, data=payload)], excluded)

    def test_sequence_identity_provenance_deduplication_and_exclusion(self):
        result = self.sequence_load()
        self.assertEqual(list(result), [9])
        self.assertEqual(result[9]['family'], 'model-sequence')
        self.assertEqual(result[9]['consumer']['bindings'][0]['model'], [4, 7, 0])
        self.assertEqual(self.sequence_load(excluded={9}), {})

    def test_missing_consumer_and_changed_rom_fail_closed(self):
        with self.assertRaisesRegex(ValueError, 'lacks a verified consumer'):
            self.sequence_load(bound=False)
        with self.assertRaisesRegex(ValueError, 'reference ROM changed'):
            self.sequence_load(wrong_rom=True)
