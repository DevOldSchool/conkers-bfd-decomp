"""A rendered preview earns reconstruction credit only for its entire payload."""
from contextlib import ExitStack
import hashlib
from pathlib import Path
from types import SimpleNamespace
import unittest
from unittest.mock import patch

from scripts import texture_assets as t, texture_native as native, texture_model_catalog as catalog


class ModelTextureCatalogTests(unittest.TestCase):
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
