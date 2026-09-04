from __future__ import annotations

import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from scripts import mp3_assets


def sample_family() -> mp3_assets.Mp3AssetFamily:
    offsets = [0, 0] + [index * 4 for index in range(1, 33)] + [0, 0]
    return mp3_assets.Mp3AssetFamily(
        stream_bank_start=0x1000,
        stream_bank_end=0x1800,
        streams=(
            mp3_assets.Mp3Asset(
                entry_index=0,
                role="stream",
                data=bytes.fromhex("FFF330C0") + bytes(12),
                rom_start=0x1010,
                rom_end=0x1020,
                type_flags=0,
                compressed=False,
            ),
            mp3_assets.Mp3Asset(
                entry_index=2,
                role="stream",
                data=bytes.fromhex("FFF350C0") + bytes(20),
                rom_start=0x1030,
                rom_end=0x1048,
                type_flags=0,
                compressed=False,
            ),
        ),
        decoder_bank_start=0x1800,
        decoder_bank_end=0x8000,
        offsets=mp3_assets.Mp3Asset(
            entry_index=4,
            role="huffman-offsets",
            data=mp3_assets.encode_huffman_offsets(offsets, mp3_assets.HUFFMAN_TABLE_SIZE),
            rom_start=0x1100,
            rom_end=0x1190,
            type_flags=0,
            compressed=False,
        ),
        lookup=mp3_assets.Mp3Asset(
            entry_index=5,
            role="lookup",
            data=bytes(index & 0xFF for index in range(mp3_assets.LOOKUP_TABLE_SIZE)),
            rom_start=0x1200,
            rom_end=0x1200 + mp3_assets.LOOKUP_TABLE_SIZE,
            type_flags=0,
            compressed=False,
        ),
        huffman=mp3_assets.Mp3Asset(
            entry_index=6,
            role="huffman",
            data=bytes((index * 3) & 0xFF for index in range(mp3_assets.HUFFMAN_TABLE_SIZE)),
            rom_start=0x6000,
            rom_end=0x6000 + mp3_assets.HUFFMAN_TABLE_SIZE,
            type_flags=0x80,
            compressed=False,
        ),
    )


class Mp3AssetsTests(unittest.TestCase):
    def test_huffman_offsets_round_trip(self) -> None:
        family = sample_family()
        offsets = mp3_assets.decode_huffman_offsets(
            family.offsets.data, len(family.huffman.data)
        )

        self.assertEqual(
            family.offsets.data,
            mp3_assets.encode_huffman_offsets(offsets, len(family.huffman.data)),
        )

    def test_extract_and_pack_rebuilds_sparse_streams_and_decoder_entries(self) -> None:
        family = sample_family()
        normalized = bytes.fromhex("80371240") + bytes(28)

        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            output = root / "mp3"
            source = root / "owned.z64"
            source.write_bytes(normalized)
            with (
                patch.object(mp3_assets, "ROOT", root),
                patch.object(
                    mp3_assets,
                    "load_profile_mp3_assets",
                    return_value=(source, normalized, "big", family),
                ),
            ):
                manifest = mp3_assets.extract_mp3_assets("us", None, output, False)

            self.assertEqual(5, manifest["asset_count"])
            self.assertEqual(2, manifest["stream_bank"]["stream_count"])
            self.assertNotIn(temporary_directory, manifest["source_rom"])
            self.assertEqual(
                "huffman-offsets.json",
                manifest["decoder_bank"]["assets"][0]["file"],
            )
            self.assertEqual(
                family.streams[0].data, (output / "streams" / "0000.mp3").read_bytes()
            )
            self.assertFalse((output / "streams" / "0001.mp3").exists())
            self.assertEqual(
                family.streams[1].data, (output / "streams" / "0002.mp3").read_bytes()
            )

            packed_output = root / "packed"
            packed = mp3_assets.pack_mp3_assets(output, packed_output, False)
            self.assertEqual(family.streams[0].data, packed[0x16][0])
            self.assertEqual(family.streams[1].data, packed[0x16][2])
            self.assertEqual(family.offsets.data, packed[0x17][4])
            self.assertEqual(family.lookup.data, packed[0x17][5])
            self.assertEqual(family.huffman.data, packed[0x17][6])
            self.assertEqual(
                family.huffman.data,
                (packed_output / "bank-17" / "0006.bin").read_bytes(),
            )

    def test_pack_rejects_unsafe_manifest_file(self) -> None:
        family = sample_family()
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "owned.z64"
            source.write_bytes(bytes.fromhex("80371240"))
            output = root / "mp3"
            with patch.object(
                mp3_assets,
                "load_profile_mp3_assets",
                return_value=(source, source.read_bytes(), "big", family),
            ):
                mp3_assets.extract_mp3_assets("us", None, output, False)

            manifest_path = output / "manifest.json"
            manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
            manifest["decoder_bank"]["assets"][1]["file"] = "../lookup.bin"
            manifest_path.write_text(json.dumps(manifest), encoding="utf-8")

            with self.assertRaisesRegex(ValueError, "unsafe MP3 asset manifest path"):
                mp3_assets.pack_mp3_assets(output, root / "packed", False)

    def test_rejects_misaligned_huffman_offset(self) -> None:
        family = sample_family()
        offsets = mp3_assets.decode_huffman_offsets(
            family.offsets.data, len(family.huffman.data)
        )
        offsets[2] = 3

        with self.assertRaisesRegex(ValueError, "four-byte aligned"):
            mp3_assets.encode_huffman_offsets(offsets, len(family.huffman.data))


if __name__ == "__main__":
    unittest.main()
