from __future__ import annotations

import json
import struct
import tempfile
import unittest
from pathlib import Path

from scripts import rzip_pack, texture_assets as t, texture_rgba16 as rgba16


def commands(index: int = 42, width: int = 32, height: int = 16):
    loaded_halfwords = width * height
    return [
        (0xFD100000, index),
        (0xF5100000, 0x07000000),
        (0xF3000000, 0x07000000 | (loaded_halfwords - 1) << 12),
        (0xF5100000 | (width // 4) << 9, 0),
        (0xF2000000, ((width - 1) * 4) << 12 | (height - 1) * 4),
        (0xDF000000, 0),
    ]


def scan(words, size: int = 1024, index: int = 42):
    data = b"".join(struct.pack(">II", *word) for word in words)
    return rgba16.scan_contracts(data, "fixture", {index: size})


def sample_payload(width: int, height: int) -> bytes:
    return b"".join(
        (
            (((pixel & 31) << 11)
             | (((pixel * 3) & 31) << 6)
             | (((pixel * 7) & 31) << 1)
             | (pixel & 1))
        ).to_bytes(2, "big")
        for pixel in range(width * height)
    )


class RGBA16Tests(unittest.TestCase):
    def test_exact_full_payload_contract(self):
        for width, height in ((32, 16), (32, 32), (64, 32)):
            with self.subTest(width=width, height=height):
                record, = scan(
                    commands(width=width, height=height),
                    width * height * 2,
                )
                self.assertEqual("proven", record["status"])
                self.assertEqual((width, height), (record["width"], record["height"]))

    def test_rejects_partial_or_non_rgba16_consumers(self):
        words = commands()
        words[2] = (0xF3000000, 0x070FF000)
        self.assertEqual("partial-or-mismatched-load", scan(words)[0]["status"])

        words = commands()
        words[3] = (0xF5501000, 0)
        self.assertEqual("not-rgba16-render-tile", scan(words)[0]["status"])

    def test_rgba5551_png_round_trip(self):
        for width, height in ((32, 16), (32, 32), (64, 32)):
            with self.subTest(width=width, height=height):
                payload = sample_payload(width, height)
                png = rgba16.encode_png(payload, t.ROW_LAYOUT_TMEM, width, height)
                self.assertEqual(
                    payload,
                    rgba16.decode_png(png, t.ROW_LAYOUT_TMEM, width, height),
                )

    def test_pack_and_rzip_override_round_trip(self):
        width, height = 32, 16
        payload = sample_payload(width, height)
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            source, output = root / "source", root / "packed"
            source.mkdir()
            (source / "0042.rgba16.png").write_bytes(
                rgba16.encode_png(payload, t.ROW_LAYOUT_TMEM, width, height)
            )
            manifest = {
                "schema_version": 7,
                "family": rgba16.FAMILY,
                "profile": "us",
                "source_origin": t.SOURCE_ORIGIN,
                "png_origin": t.PNG_ORIGIN,
                "texture_count": 1,
                "textures": [{
                    "flat_index": 42,
                    "width": width,
                    "height": height,
                    "row_layout": t.ROW_LAYOUT_TMEM,
                    "file": "0042.rgba16.png",
                }],
            }
            (source / "manifest.json").write_text(json.dumps(manifest))
            self.assertEqual({42: payload}, t.pack_textures(source, output, False))
            self.assertEqual({42: payload}, rzip_pack.load_texture_overrides(output))


if __name__ == "__main__":
    unittest.main()
