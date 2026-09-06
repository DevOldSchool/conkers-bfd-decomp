from __future__ import annotations

import json
import struct
import tempfile
import unittest
from pathlib import Path

from scripts import rzip_pack, texture_assets as t, texture_native as native


FORMAT_FIXTURES = {
    "rgba32": (0xFD180000, 0xF5180000, 4),
    "ia8": (0xFD700000, 0xF5680000, 1),
    "ia16": (0xFD700000, 0xF5700000, 2),
    "i4": (0xFD900000, 0xF5800000, 0.5),
    "i8": (0xFD900000, 0xF5880000, 1),
}


def commands(texture_format: str, index: int, width: int, height: int):
    image, tile, bytes_per_pixel = FORMAT_FIXTURES[texture_format]
    payload_size = int(width * height * bytes_per_pixel)
    image_bytes_per_unit = 4 if texture_format == "rgba32" else 2
    loaded_count = payload_size // image_bytes_per_unit
    line_bytes = width * 2 if texture_format == "rgba32" else int(
        width * bytes_per_pixel
    )
    return [
        (image, index),
        (tile, 0x07000000),
        (0xF3000000, 0x07000000 | (loaded_count - 1) << 12),
        (tile | (line_bytes // 8) << 9, 0),
        (0xF2000000, ((width - 1) * 4) << 12 | (height - 1) * 4),
        (0xDF000000, 0),
    ]


def sample_payload(texture_format: str, width: int, height: int) -> bytes:
    pixels = width * height
    if texture_format == "rgba32":
        return bytes((index * 7) & 0xFF for index in range(pixels * 4))
    if texture_format == "ia16":
        return b"".join(bytes((index & 0xFF, (index * 3) & 0xFF)) for index in range(pixels))
    if texture_format in ("ia8", "i8"):
        return bytes((index * 5) & 0xFF for index in range(pixels))
    return bytes((index * 11) & 0xFF for index in range(pixels // 2))


class NativeTextureTests(unittest.TestCase):
    def test_rgba32_tmem_rows_swap_eight_byte_halves(self):
        even = bytes(range(16))
        odd = bytes(range(16, 32))
        converted = native.convert_row_layout(
            even + odd, t.ROW_LAYOUT_TMEM, "rgba32", 4, 2
        )
        self.assertEqual(even, converted[:16])
        self.assertEqual(odd[8:16] + odd[0:8], converted[16:32])

    def test_exact_contract_for_each_supported_format(self):
        dimensions = {
            "rgba32": (16, 16),
            "ia8": (32, 16),
            "ia16": (32, 16),
            "i4": (32, 16),
            "i8": (32, 16),
        }
        for index, (texture_format, (width, height)) in enumerate(dimensions.items()):
            with self.subTest(texture_format=texture_format):
                payload = sample_payload(texture_format, width, height)
                words = commands(texture_format, index, width, height)
                data = b"".join(struct.pack(">II", *word) for word in words)
                record, = native.scan_contracts(data, "fixture", {index: len(payload)})
                self.assertEqual("proven", record["status"])
                self.assertEqual(texture_format, record["format"])
                self.assertEqual((width, height), (record["width"], record["height"]))

    def test_png_round_trip_for_each_supported_format(self):
        for texture_format in native.FORMATS.values():
            width, height = (16, 16) if texture_format == "rgba32" else (32, 16)
            with self.subTest(texture_format=texture_format):
                payload = sample_payload(texture_format, width, height)
                png = native.encode_png(
                    payload, texture_format, t.ROW_LAYOUT_TMEM, width, height
                )
                self.assertEqual(
                    payload,
                    native.decode_png(
                        png, texture_format, t.ROW_LAYOUT_TMEM, width, height
                    ),
                )

    def test_rejects_partial_load(self):
        words = commands("ia8", 42, 32, 16)
        words[2] = (0xF3000000, 0x0707F000)
        data = b"".join(struct.pack(">II", *word) for word in words)
        record, = native.scan_contracts(data, "fixture", {42: 512})
        self.assertEqual("partial-or-mismatched-load", record["status"])

    def test_mixed_native_pack_and_rzip_override_round_trip(self):
        records = []
        payloads = {}
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            source, output = root / "source", root / "packed"
            source.mkdir()
            for index, texture_format in enumerate(native.FORMATS.values()):
                width, height = (16, 16) if texture_format == "rgba32" else (32, 16)
                payload = sample_payload(texture_format, width, height)
                filename = f"{index:04d}.{texture_format}.png"
                (source / filename).write_bytes(
                    native.encode_png(
                        payload, texture_format, t.ROW_LAYOUT_TMEM, width, height
                    )
                )
                payloads[index] = payload
                records.append({
                    "flat_index": index,
                    "format": texture_format,
                    "width": width,
                    "height": height,
                    "row_layout": t.ROW_LAYOUT_TMEM,
                    "file": filename,
                })
            manifest = {
                "schema_version": 8,
                "family": native.FAMILY,
                "profile": "us",
                "source_origin": t.SOURCE_ORIGIN,
                "png_origin": t.PNG_ORIGIN,
                "texture_count": len(records),
                "textures": records,
            }
            (source / "manifest.json").write_text(json.dumps(manifest))
            self.assertEqual(payloads, t.pack_textures(source, output, False))
            self.assertEqual(payloads, rzip_pack.load_texture_overrides(output))


if __name__ == "__main__":
    unittest.main()
