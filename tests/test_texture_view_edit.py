from __future__ import annotations

import hashlib
import json
import struct
import tempfile
import unittest
import zlib
from pathlib import Path

from scripts import texture_assets as t
from scripts.texture_view_edit import apply_view_edits, decode_view_png


class TextureViewEditTests(unittest.TestCase):
    def fixture(self, root: Path):
        (root / "tiles").mkdir()
        originals, records = {}, []
        for index in range(72):
            depth = 4 if index % 2 == 0 else 8
            # Slots 0 and 2 have identical colors: no-op packing must retain 2.
            palette = [1] * (16 if depth == 4 else 256)
            palette[1] = 0xFFFF
            palette[3] = 0xF801
            payload = bytes([0x22 if depth == 4 else 2]) * (256 * depth)
            payload += struct.pack(f">{len(palette)}H", *palette)
            originals[index] = payload
            filename = f"tiles/{index}.png"
            encoded = (t.encode_indexed_png(payload, width=64, height=32)
                       if depth == 4 else t.encode_ci8_png(payload))
            (root / filename).write_bytes(encoded)
            records.append({
                "flat_index": index, "file": filename,
                "decoded_sha1": hashlib.sha1(payload).hexdigest(),
                "format": "ci4" if depth == 4 else "ci8",
                "storage_width": 64, "storage_height": 32,
                "row_layout": t.ROW_LAYOUT_TMEM,
            })
        manifest = {
            "schema_version": 5, "profile": "us", "family": t.TILED_VIEWS_FAMILY,
            "source_origin": t.SOURCE_ORIGIN, "png_origin": t.PNG_ORIGIN,
            "tile_count": 72, "tiles": records, "view_count": 1,
            "views": [{"group_index": 0, "view_index": 0,
                       "first_flat_index": 2, "continuous_stream_phase": 2,
                       "source_flat_index_start": 0, "source_flat_index_end": 71,
                       "flat_index_order": "column-major", "file": "view.png"}],
        }
        rgba, _ = t.compose_tiled_view(2, {
            i: t.TextureAsset(i, 0, 0, p) for i, p in originals.items()
        })
        (root / "view.png").write_bytes(t.encode_rgba_png(360, 360, rgba))
        (root / "manifest.json").write_text(json.dumps(manifest))
        return manifest, originals, bytearray(rgba)

    def test_noop_preserves_duplicate_indices_and_every_payload_byte(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            _, originals, _ = self.fixture(root)
            packed = t.pack_textures(root, root / "packed", False, views=True)
            self.assertEqual(originals, packed)

    def test_edits_cross_columns_and_formats_preserving_palettes_and_padding(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            _, originals, rgba = self.fixture(root)
            # Tile 0 CI4, tile 1 CI8, and tile 12 at the next column boundary.
            coordinates = [(0, 0), (59, 29), (0, 30), (60, 0)]
            for x, y in coordinates:
                offset = (y * 360 + x) * 4
                rgba[offset:offset + 4] = b"\xff" * 4
            (root / "view.png").write_bytes(t.encode_rgba_png(360, 360, rgba))
            packed = t.pack_textures(root, root / "packed", False, views=True)
            self.assertEqual([0, 1, 12], [i for i in packed if packed[i] != originals[i]])
            assembled, _ = t.compose_tiled_view(2, {
                i: t.TextureAsset(i, 0, 0, p) for i, p in packed.items()
            })
            self.assertEqual(rgba, assembled)
            for i in (0, 1, 12):
                depth = 4 if i % 2 == 0 else 8
                size = 256 * depth
                self.assertEqual(originals[i][size:], packed[i][size:])
                before = t.indexed_payload_rgba(originals[i], depth)
                after = t.indexed_payload_rgba(packed[i], depth)
                for y in range(32):
                    for x in range(64):
                        if x >= 60 or y >= 30:
                            offset = (y * 64 + x) * 4
                            self.assertEqual(before[offset:offset + 4], after[offset:offset + 4])

    def test_invalid_color_fails_before_replacing_output(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            _, _, rgba = self.fixture(root)
            rgba[:4] = bytes((0, 255, 0, 255))
            (root / "view.png").write_bytes(t.encode_rgba_png(360, 360, rgba))
            output = root / "packed"
            output.mkdir()
            (output / "sentinel").write_text("keep")
            with self.assertRaisesRegex(ValueError, "outside tile 0's palette"):
                t.pack_textures(root, output, True, views=True)
            self.assertEqual("keep", (output / "sentinel").read_text())

    def test_stale_mapping_and_changed_tiles_are_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            manifest, originals, _ = self.fixture(root)
            manifest["views"][0]["source_flat_index_start"] = 2
            with self.assertRaisesRegex(ValueError, "stale"):
                apply_view_edits(root, manifest, originals)
            manifest["tiles"][0]["decoded_sha1"] = "wrong"
            with self.assertRaisesRegex(ValueError, "tile 0 was edited"):
                apply_view_edits(root, manifest, originals)

    def test_pack_cannot_replace_input_directory(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self.fixture(root)
            with self.assertRaisesRegex(ValueError, "must not replace"):
                t.pack_textures(root, root, True, views=True)
            self.assertTrue((root / "manifest.json").exists())

    def test_conflicting_edits_in_views_sharing_a_tile_are_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            manifest, originals, rgba = self.fixture(root)
            rgba[:4] = b"\xff" * 4
            (root / "view.png").write_bytes(t.encode_rgba_png(360, 360, rgba))
            rgba[:4] = bytes((255, 0, 0, 255))
            (root / "other.png").write_bytes(t.encode_rgba_png(360, 360, rgba))
            manifest["views"].append({**manifest["views"][0], "view_index": 1, "file": "other.png"})
            manifest["view_count"] = 2
            with self.assertRaisesRegex(ValueError, "conflicting view edits"):
                apply_view_edits(root, manifest, originals)

    def test_png_rgb_and_rgba_all_filters_and_crc(self):
        for channels in (3, 4):
            for filter_type in range(5):
                with self.subTest(channels=channels, filter_type=filter_type):
                    pixel = bytes((40, 80, 120, 255))[:channels]
                    row = pixel * 360
                    filtered = bytearray()
                    previous = bytes(len(row))
                    for y in range(360):
                        filtered.append(filter_type)
                        for x, value in enumerate(row):
                            left = row[x - channels] if x >= channels else 0
                            above = previous[x]
                            # Constant rows make the Paeth predictor left on row 0,
                            # above thereafter (including the first pixel).
                            predictors = (0, left, above, (left + above) // 2,
                                          left if y == 0 else above)
                            filtered.append((value - predictors[filter_type]) & 255)
                        previous = row
                    png = (t.PNG_SIGNATURE
                           + t.png_chunk(b"IHDR", struct.pack(">IIBBBBB", 360, 360, 8,
                                                              6 if channels == 4 else 2, 0, 0, 0))
                           + t.png_chunk(b"IDAT", zlib.compress(filtered))
                           + t.png_chunk(b"IEND", b""))
                    self.assertEqual(bytes((40, 80, 120, 255)) * (360 * 360), decode_view_png(png))
        corrupt = bytearray(png)
        corrupt[-5] ^= 1
        with self.assertRaisesRegex(ValueError, "CRC"):
            decode_view_png(bytes(corrupt))


if __name__ == "__main__":
    unittest.main()
