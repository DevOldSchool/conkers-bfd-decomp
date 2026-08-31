from __future__ import annotations

import struct
import unittest
import zlib

from scripts import rzip_archive


def chunk(data: bytes) -> bytes:
    return struct.pack(">I", len(data)) + zlib.compress(data, wbits=-15)


class RzipArchiveTests(unittest.TestCase):
    def test_normalizes_v64_byte_order(self) -> None:
        z64 = rzip_archive.Z64_MAGIC + bytes(range(4, 16))
        v64 = bytearray(len(z64))
        v64[0::2] = z64[1::2]
        v64[1::2] = z64[0::2]
        normalized, order = rzip_archive.normalize_rom(bytes(v64))
        self.assertEqual("v64", order)
        self.assertEqual(z64, normalized)

    def test_separates_game_code_data_and_padding(self) -> None:
        key = rzip_archive.OFFSET_XOR
        first = 0x20
        second = 0x30
        code_end = 0x40
        data_start = 0x50
        payload = bytearray(0x80)
        struct.pack_into(">I", payload, 0, data_start)
        struct.pack_into(">I", payload, 4, key ^ first)
        struct.pack_into(">I", payload, 8, key ^ second)
        struct.pack_into(">I", payload, 12, key ^ code_end)
        payload[first : first + len(chunk(b"AB"))] = chunk(b"AB")
        payload[second : second + len(chunk(b"CD"))] = chunk(b"CD")
        payload[data_start : data_start + len(chunk(b"DATA"))] = chunk(b"DATA")

        archive = rzip_archive.parse_game_archive(bytes(payload))

        self.assertEqual(b"ABCD", archive.code)
        self.assertEqual(b"DATA", archive.data)
        self.assertEqual(code_end, archive.code_end)
        self.assertEqual(data_start, archive.data_start)
        self.assertEqual(0x10, len(archive.code_padding))
        self.assertGreater(len(archive.data_padding), 0)

    def test_parses_indexed_compressed_and_raw_assets(self) -> None:
        rom = bytearray(0x200)
        outer = 0x20
        bank = 0x28
        bank_size = 0x80
        struct.pack_into(">II", rom, outer, bank - outer, bank_size)

        compressed = chunk(b"zip")
        raw = b"RAW"
        struct.pack_into(">II", rom, bank, 0x20, 0x10000000 | len(compressed))
        struct.pack_into(">II", rom, bank + 8, 0x30, len(raw))
        rom[bank + 0x20 : bank + 0x20 + len(compressed)] = compressed
        rom[bank + 0x30 : bank + 0x30 + len(raw)] = raw

        banks = rzip_archive.parse_asset_banks(bytes(rom), outer)
        entries = rzip_archive.parse_asset_entries(bytes(rom), banks[0])

        self.assertEqual(1, len(banks))
        self.assertEqual(2, len(entries))
        self.assertTrue(entries[0].compressed)
        self.assertFalse(entries[1].compressed)
        self.assertEqual(
            b"zip",
            rzip_archive.decode_rzip_chunk(bytes(rom[entries[0].start : entries[0].end])).data,
        )
        self.assertEqual(raw, bytes(rom[entries[1].start : entries[1].end]))

    def test_parses_contiguous_flat_rzip_stream(self) -> None:
        first = chunk(b"first")
        second = chunk(b"second")

        entries = list(rzip_archive.iter_flat_rzip_entries(first + second))

        self.assertEqual(2, len(entries))
        self.assertEqual((0, len(first)), (entries[0].start, entries[0].end))
        self.assertEqual(b"first", entries[0].data)
        self.assertEqual((len(first), len(first) + len(second)), (entries[1].start, entries[1].end))
        self.assertEqual(b"second", entries[1].data)


if __name__ == "__main__":
    unittest.main()
