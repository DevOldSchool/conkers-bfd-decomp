from __future__ import annotations

import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from scripts import font_assets, font_preview, texture_assets


class FontPreviewTests(unittest.TestCase):
    def artifacts(self):
        glyphs = [font_assets.FontGlyph(0x30 + i, 2, 2, bytes((1, 2)),
                  bytes((0, 16, 128, 240)), bytes((0, 16, 128, 240))) for i in range(3)]
        return font_preview.build_artifacts(glyphs, b'A&&', {"font_start": "0x20"})

    def test_source_pixels_and_atlas_coordinates_preserve_every_intensity(self):
        manifest, files = self.artifacts()
        atlas = manifest['atlas']
        decoded = texture_assets.decode_rgba_png_pixels(files['atlas.png'], atlas['width'], atlas['height'])
        for record in manifest['glyphs']:
            pixels = texture_assets.decode_rgba_png_pixels(files[record['png_file']], 2, 2)
            self.assertEqual(pixels[3::4], bytes((0, 16, 128, 240)))
            r = record['atlas_rect']
            recovered = b''.join(decoded[((r['y']+row)*atlas['width']+r['x'])*4:
                                      ((r['y']+row)*atlas['width']+r['x']+2)*4] for row in range(2))
            self.assertEqual(recovered, pixels)

    def test_mapping_retains_noncontiguous_bytes_duplicate_glyphs_and_metrics(self):
        manifest, _ = self.artifacts()
        a, first, shadowed = manifest['glyphs']
        self.assertEqual((a['input_byte'], a['legacy_pgm_file']), (65, '0030.pgm'))
        self.assertEqual((a['advance'], a['line_extent']), (3, 5))
        self.assertEqual((a['runtime_width'], a['runtime_height']), (3, 3))
        self.assertEqual((first['lookup_status'], shadowed['lookup_status']), ('first-match', 'shadowed'))
        self.assertEqual(shadowed['lookup_first_index'], 1)
        self.assertEqual(manifest['distinct_input_byte_count'], 2)

    def test_rejects_mismatched_map(self):
        with self.assertRaisesRegex(ValueError, 'counts differ'):
            font_preview.build_artifacts([], b'A', {})

    def test_verify_detects_changed_png_mapping_and_html(self):
        artifacts = self.artifacts()
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory) / 'preview'
            with patch.object(font_preview, 'load_artifacts', return_value=artifacts):
                font_preview.preview_fonts('us', None, root)
                self.assertEqual(font_preview.verify_preview('us', None, root)[0], 3)
                for name in ('atlas.png', 'preview-manifest.json', 'index.html'):
                    original = (root / name).read_bytes()
                    (root / name).write_bytes(original + b'changed')
                    with self.assertRaisesRegex(ValueError, 'stale or corrupted'):
                        font_preview.verify_preview('us', None, root)
                    (root / name).write_bytes(original)

    def test_signature_and_range_evidence_fail_closed(self):
        with patch.object(font_preview, 'FONT_SIGNATURES', {0x1000: 0x12345678}):
            data = b''.join(value.to_bytes(4, 'big') for value in font_preview.FONT_ROM_RANGE)
            font_preview.validate_font_consumer(bytes.fromhex('12345678'), data, 0x1000, font_preview.FONT_ROM_RANGE_VRAM)
            with self.assertRaisesRegex(ValueError, 'instruction mismatch'):
                font_preview.validate_font_consumer(bytes(4), data, 0x1000, font_preview.FONT_ROM_RANGE_VRAM)
            with self.assertRaisesRegex(ValueError, 'ROM range'):
                font_preview.validate_font_consumer(bytes.fromhex('12345678'), bytes(8), 0x1000, font_preview.FONT_ROM_RANGE_VRAM)


if __name__ == '__main__':
    unittest.main()
