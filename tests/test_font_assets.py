from __future__ import annotations

import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from scripts import font_assets


class FontAssetsTests(unittest.TestCase):
    def test_rle_round_trip_preserves_row_boundaries(self) -> None:
        pixels = bytes([0x10, 0x10, 0x10, 0x10, 0x10, 0x10])

        encoded = font_assets.encode_pixels(3, 2, pixels)

        self.assertEqual(bytes([0x12, 0x12]), encoded)
        self.assertEqual(pixels, font_assets.decode_pixels(3, 2, encoded))

    def test_extract_and_pack_rebuilds_the_font_storage(self) -> None:
        glyphs = [
            font_assets.FontGlyph(
                codepoint=0x30,
                width=2,
                height=2,
                metadata=b"\x01\x02",
                pixels=bytes([0x10, 0x10, 0x20, 0x20]),
                encoded=b"",
            ),
            font_assets.FontGlyph(
                codepoint=0x31,
                width=1,
                height=2,
                metadata=b"\x03\x04",
                pixels=bytes([0x30, 0x40]),
                encoded=b"",
            ),
        ]
        table = font_assets.encode_font_table(glyphs, padding_size=3)
        rom = bytes.fromhex("80371240") + bytes(0x1C) + table

        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            rom_path = root / "test.z64"
            rom_path.write_bytes(rom)
            output = root / "fonts"
            layout = {
                "default_rom": "test.z64",
                "font_count": 2,
                "font_start": 0x20,
                "font_storage_end": len(rom),
                "normalized_sha1": [font_assets.hashlib.sha1(rom).hexdigest()],
            }

            with (
                patch.object(font_assets, "ROOT", root),
                patch.object(font_assets, "load_layout", return_value=layout),
            ):
                manifest = font_assets.extract_fonts("test", None, output, force=False)

            self.assertEqual(2, manifest["record_count"])
            self.assertEqual(3, manifest["padding_size"])
            self.assertNotIn(temporary_directory, manifest["source_rom"])

            packed_path = root / "packed.bin"
            packed = font_assets.pack_fonts(output, packed_path)
            self.assertEqual(table, packed)
            self.assertEqual(table, packed_path.read_bytes())

            parsed_manifest = json.loads((output / "manifest.json").read_text())
            self.assertEqual("0030.pgm", parsed_manifest["glyphs"][0]["file"])

    def test_rejects_non_nibble_grayscale_pixels(self) -> None:
        with self.assertRaisesRegex(ValueError, "four-bit grayscale"):
            font_assets.encode_pixels(1, 1, b"\x11")


if __name__ == "__main__":
    unittest.main()
