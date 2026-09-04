from __future__ import annotations

import hashlib
import json
import struct
import tempfile
import unittest
import zlib
from pathlib import Path

from scripts import rzip_pack
from scripts.rzip_archive import iter_flat_rzip_entries


def chunk(data: bytes) -> bytes:
    return struct.pack(">I", len(data)) + zlib.compress(data, level=9, wbits=-15)


class RzipPackTests(unittest.TestCase):
    def test_unchanged_flat_region_is_preserved_byte_identically(self) -> None:
        stream = chunk(b"first") + chunk(b"second")
        alignment = bytes(range(15))
        rom = bytes(0x20) + stream + alignment
        layout = {
            "flat_assets_start": 0x20,
            "flat_assets_end": 0x20 + len(stream),
            "asset_table": 0x20 + len(stream) + len(alignment),
        }

        region, count, changed, rebuilt_size = rzip_pack.rebuild_flat_region(
            rom, layout, {0: b"first", 1: b"second"}
        )

        self.assertEqual(2, count)
        self.assertEqual(0, changed)
        self.assertEqual(len(stream), rebuilt_size)
        self.assertEqual(rom[0x20:], region)

    def test_changed_entry_is_recompressed_and_fixed_span_is_preserved(self) -> None:
        stream = chunk(b"first") + chunk(b"second")
        alignment = 15
        rom = bytes(0x20) + stream + bytes(alignment)
        layout = {
            "flat_assets_start": 0x20,
            "flat_assets_end": 0x20 + len(stream),
            "asset_table": 0x20 + len(stream) + alignment,
        }

        region, count, changed, rebuilt_size = rzip_pack.rebuild_flat_region(
            rom, layout, {1: b"SECOND"}
        )
        rebuilt = list(iter_flat_rzip_entries(region[:rebuilt_size]))

        self.assertEqual(2, count)
        self.assertEqual(1, changed)
        self.assertEqual(len(stream) + alignment, len(region))
        self.assertEqual(b"first", rebuilt[0].data)
        self.assertEqual(b"SECOND", rebuilt[1].data)
        self.assertEqual(chunk(b"first"), region[: len(chunk(b"first"))])

    def test_changed_stream_must_fit_before_fixed_asset_table(self) -> None:
        stream = chunk(b"a")
        rom = bytes(0x20) + stream + bytes(15)
        layout = {
            "flat_assets_start": 0x20,
            "flat_assets_end": 0x20 + len(stream),
            "asset_table": 0x20 + len(stream) + 15,
        }

        with self.assertRaisesRegex(ValueError, "too large"):
            rzip_pack.rebuild_flat_region(rom, layout, {0: bytes(range(128))})

    def test_texture_override_manifest_is_hash_checked(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            payload_dir = root / "flat"
            payload_dir.mkdir()
            payload = b"payload"
            (payload_dir / "0035.bin").write_bytes(payload)
            manifest = {
                "schema_version": 3,
                "profile": "us",
                "family": rzip_pack.TEXTURE_FAMILY,
                "source_origin": "bottom-left",
                "png_origin": "top-left",
                "texture_count": 1,
                "textures": [
                    {
                        "flat_index": 35,
                        "size": len(payload),
                        "sha1": hashlib.sha1(payload).hexdigest(),
                        "file": "flat/0035.bin",
                    }
                ],
            }
            (root / "manifest.json").write_text(
                json.dumps(manifest), encoding="utf-8"
            )

            self.assertEqual({35: payload}, rzip_pack.load_texture_overrides(root))
            (payload_dir / "0035.bin").write_bytes(b"changed")
            with self.assertRaisesRegex(ValueError, "SHA-1"):
                rzip_pack.load_texture_overrides(root)

    def test_rectangular_texture_override_manifest_is_supported(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            payload_dir = root / "flat"
            payload_dir.mkdir()
            payload = bytes(1056)
            (payload_dir / "1282.bin").write_bytes(payload)
            (root / "manifest.json").write_text(
                json.dumps(
                    {
                        "schema_version": 4,
                        "profile": "us",
                        "family": rzip_pack.RECTANGULAR_TEXTURE_FAMILY,
                        "source_origin": "bottom-left",
                        "png_origin": "top-left",
                        "texture_count": 1,
                        "textures": [
                            {
                                "flat_index": 1282,
                                "size": len(payload),
                                "sha1": hashlib.sha1(payload).hexdigest(),
                                "file": "flat/1282.bin",
                            }
                        ],
                    }
                ),
                encoding="utf-8",
            )

            self.assertEqual(
                {1282: payload}, rzip_pack.load_texture_overrides(root)
            )

    def test_tiled_view_override_manifest_is_supported(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            payload_dir = root / "flat"
            payload_dir.mkdir()
            payload = bytes(2560)
            (payload_dir / "4811.bin").write_bytes(payload)
            (root / "manifest.json").write_text(
                json.dumps(
                    {
                        "schema_version": 5,
                        "profile": "us",
                        "family": rzip_pack.TILED_VIEWS_TEXTURE_FAMILY,
                        "source_origin": "bottom-left",
                        "png_origin": "top-left",
                        "tile_count": 1,
                        "tiles": [
                            {
                                "flat_index": 4811,
                                "size": len(payload),
                                "sha1": hashlib.sha1(payload).hexdigest(),
                                "file": "flat/4811.bin",
                            }
                        ],
                    }
                ),
                encoding="utf-8",
            )

            self.assertEqual(
                {4811: payload}, rzip_pack.load_texture_overrides(root)
            )

    def test_real_us_checksum_algorithm_matches_header_when_rom_is_available(self) -> None:
        rom_path = rzip_pack.ROOT / "roms" / "baserom.us.z64"
        if not rom_path.is_file():
            self.skipTest("private US ROM is unavailable")
        rom = rom_path.read_bytes()

        self.assertEqual(
            struct.unpack_from(">II", rom, 0x10),
            rzip_pack.calculate_6105_checksum(rom),
        )


if __name__ == "__main__":
    unittest.main()
