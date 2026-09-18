from __future__ import annotations

import sys
import unittest
from pathlib import Path


sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import verify_game_rodata


class GameRodataTests(unittest.TestCase):
    def test_extracts_external_sections_without_confusing_code(self) -> None:
        headers = (
            "  0 .game 001fa130 15000000 15000000 00010000 2**4\n"
            "  1 .game_rodata_61950 00000020 80097d20 80097d20 0020a130 2**4\n"
        )
        self.assertEqual(
            verify_game_rodata.external_sections(headers),
            [(".game_rodata_61950", 0x20, 0x80097D20)],
        )
        with self.assertRaisesRegex(ValueError, "no reviewed external"):
            verify_game_rodata.external_sections("  0 .game 001fa130 15000000 ")

    def test_verifies_relocated_destinations_and_alignment_bytes(self) -> None:
        table = bytes.fromhex("150345cc") * 5 + bytes(12)
        data = bytes(0x20) + table + b"next"
        verify_game_rodata.verify_bytes("table", table, 0x20, 0x80000020, data, 0x80000000)
        for position in (3, 31):
            changed = bytearray(table)
            changed[position] ^= 1
            with self.assertRaisesRegex(ValueError, "differs from ROM"):
                verify_game_rodata.verify_bytes(
                    "table", bytes(changed), 0x20, 0x80000020, data, 0x80000000
                )

    def test_reads_only_absolute_reviewed_payload_symbols(self) -> None:
        self.assertEqual(verify_game_rodata.payload_sizes(
            "000000cc g       *ABS* 00000000 __game_rodata_70200_payload_size\n"
            "00000010 g       .text 00000000 __game_rodata_bad_payload_size\n"
        ), {".game_rodata_70200": 0xCC})

    def test_explicit_payload_preserves_rom_and_zero_padding_checks(self) -> None:
        payload = bytes.fromhex("1504302c") * 51
        linked = payload + bytes(4)
        rom = payload + bytes.fromhex("46ea6000")
        verify_game_rodata.verify_bytes("table", linked, 0xD0, 0, rom, 0, 0xCC)
        for offset in (0, 0xCB, 0xCC, 0xCF):
            changed = bytearray(linked)
            changed[offset] ^= 1
            with self.assertRaises(ValueError):
                verify_game_rodata.verify_bytes("table", bytes(changed), 0xD0, 0, rom, 0, 0xCC)
        for extent in (0, 0xBC, 0xCD, 0xD4):
            with self.assertRaises(ValueError):
                verify_game_rodata.verify_bytes("table", linked, 0xD0, 0, rom, 0, extent)
        with self.assertRaisesRegex(ValueError, "differs from ROM"):
            verify_game_rodata.verify_bytes("table", linked, 0xD0, 0, rom, 0)

    def test_rejects_unmapped_or_truncated_sections(self) -> None:
        for vram in (0x7FFFFFFF, 0x80000020):
            with self.assertRaisesRegex(ValueError, "outside"):
                verify_game_rodata.verify_bytes("table", bytes(4), 4, vram, bytes(0x20), 0x80000000)
        with self.assertRaisesRegex(ValueError, "size"):
            verify_game_rodata.verify_bytes("table", bytes(3), 4, 0x80000000, bytes(0x20), 0x80000000)


if __name__ == "__main__":
    unittest.main()
