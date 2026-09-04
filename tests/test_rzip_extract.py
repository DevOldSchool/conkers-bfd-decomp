from __future__ import annotations

import hashlib
import json
import struct
import tempfile
import unittest
import zlib
from pathlib import Path
from unittest.mock import patch

from scripts import rzip_extract


def chunk(data: bytes) -> bytes:
    return struct.pack(">I", len(data)) + zlib.compress(data, wbits=-15)


class RzipExtractTests(unittest.TestCase):
    def test_retail_profiles_include_reviewed_flat_asset_streams(self) -> None:
        expected = {
            "debug": (0x199BA0, 0xABBCFD, 0xABBD00),
            "us": (0x1A37E0, 0xAB1941, 0xAB1950),
        }

        for profile, (start, end, table) in expected.items():
            with self.subTest(profile=profile):
                layout = rzip_extract.load_layout(profile)
                self.assertEqual(start, layout["flat_assets_start"])
                self.assertEqual(end, layout["flat_assets_end"])
                self.assertEqual(table, layout["asset_table"])
                self.assertLess(layout["game_end"], start)
                self.assertLess(end, table)

    def test_extracts_raw_game_and_flat_assets(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            rom = bytearray(0x200)
            rom[:4] = bytes.fromhex("80371240")
            rom[0x20:0x30] = bytes(range(0x10))
            rom[0x30:0x40] = bytes(range(0x10, 0x20))

            flat = chunk(b"flat-one") + chunk(b"flat-two")
            rom[0x40 : 0x40 + len(flat)] = flat
            table = 0x100
            bank = table + 8
            asset = chunk(b"indexed")
            struct.pack_into(">II", rom, table, bank - table, 0x40)
            struct.pack_into(">II", rom, bank, 8, 0x10000000 | len(asset))
            rom[bank + 8 : bank + 8 + len(asset)] = asset

            rom_path = root / "roms" / "test.z64"
            rom_path.parent.mkdir()
            rom_path.write_bytes(rom)
            layouts = root / "config" / "rzip_layouts.json"
            layouts.parent.mkdir()
            layouts.write_text(
                json.dumps(
                    {
                        "schema_version": 1,
                        "profiles": {
                            "test": {
                                "asset_table": "0x100",
                                "default_rom": "roms/test.z64",
                                "flat_assets_start": "0x40",
                                "flat_assets_end": f"0x{0x40 + len(flat):X}",
                                "game_code_end": "0x30",
                                "game_data_vram": "0x80001000",
                                "game_end": "0x40",
                                "game_format": "raw",
                                "game_start": "0x20",
                                "game_vram": "0x15000000",
                                "normalized_sha1": [hashlib.sha1(rom).hexdigest()],
                            }
                        },
                    }
                ),
                encoding="utf-8",
            )
            output = root / "output"
            output.mkdir()

            with (
                patch.object(rzip_extract, "ROOT", root),
                patch.object(rzip_extract, "LAYOUTS_FILE", layouts),
            ):
                manifest = rzip_extract.extract(
                    "test", rom_path, output, keep_rzip=True, manifest_only=False
                )

            self.assertEqual("raw", manifest["game"]["format"])
            self.assertEqual("roms/test.z64", manifest["source_rom"])
            self.assertEqual(16, manifest["game"]["code_size"])
            self.assertEqual(2, manifest["assets"]["flat"]["file_count"])
            self.assertEqual(1, manifest["assets"]["file_count"])
            self.assertEqual(3, manifest["assets"]["total_file_count"])
            self.assertEqual(3, manifest["assets"]["total_compressed_file_count"])
            self.assertEqual(
                hashlib.sha1(b"flat-one").hexdigest(),
                manifest["assets"]["flat"]["files"][0]["decoded_sha1"],
            )
            self.assertEqual(
                hashlib.sha1(b"indexed").hexdigest(),
                manifest["assets"]["banks"][0]["entries"][0]["decoded_sha1"],
            )
            self.assertEqual(b"flat-one", (output / "assets" / "flat" / "0000.bin").read_bytes())
            self.assertEqual(b"indexed", (output / "assets" / "bank-00" / "0000.bin").read_bytes())

    def test_external_manifest_source_omits_the_host_directory(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory) / "repository"
            external_rom = Path(temporary_directory) / "owned-roms" / "private.v64"
            with patch.object(rzip_extract, "ROOT", root):
                source = rzip_extract.manifest_source(external_rom)

            self.assertEqual("private.v64", source)
            self.assertNotIn(temporary_directory, source)


if __name__ == "__main__":
    unittest.main()
