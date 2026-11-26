import struct
import sys
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))

import trim_game_rodata


def elf_with_rodata(payload: bytes, align: int = 16) -> bytes:
    """Build a minimal big-endian ELF32 object holding one .rodata section."""
    names = b"\0.rodata\0.shstrtab\0"
    rodata_offset = 0x34
    names_offset = rodata_offset + len(payload)
    shoff = (names_offset + len(names) + 3) & ~3
    header = bytearray(0x34)
    header[:6] = b"\x7fELF\x01\x02"
    struct.pack_into(">I", header, 0x20, shoff)
    struct.pack_into(">HHH", header, 0x2E, 40, 3, 2)
    sections = [
        (0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
        (1, 1, 2, 0, rodata_offset, len(payload), 0, 0, align, 0),
        (9, 3, 0, 0, names_offset, len(names), 0, 0, 1, 0),
    ]
    body = bytes(header) + payload + names
    body += b"\0" * (shoff - len(body))
    return body + b"".join(struct.pack(">10I", *section) for section in sections)


def rodata_header(data: bytes) -> tuple[int, int]:
    shoff, = struct.unpack_from(">I", data, 0x20)
    fields = struct.unpack_from(">10I", data, shoff + 40)
    return fields[5], fields[8]


class TrimGameRodataTests(unittest.TestCase):
    def test_reviewed_sizes_reads_whole_rodata_placements_only(self):
        script = """
            .game_rodata_1bfdd0 0x800A8180 (INFO) : SUBALIGN(4) { *game_1BFDD0.o(.rodata) }
            .game_rodata_b4080_0 0x8009D000 (INFO) : SUBALIGN(4) { *game_B4080.o(.rodata.b4080_0) }
            .game_rodata_185560_data 0x8008ADD0 (INFO) : SUBALIGN(4) { *game_185560.o(.data) }
            ASSERT(SIZEOF(.game_rodata_1bfdd0) == 0x14, "x")
            ASSERT(SIZEOF(.game_rodata_b4080_0) == 0x8, "x")
            ASSERT(SIZEOF(.game_rodata_185560_data) == 0x200, "x")
        """
        self.assertEqual(trim_game_rodata.reviewed_sizes(script), {"game_1BFDD0.o": 0x14})

    def test_trims_zero_padding_and_sets_word_alignment(self):
        data = elf_with_rodata(bytes(range(1, 21)) + bytes(12))
        trimmed = trim_game_rodata.trim_rodata(data, 0x14)
        self.assertEqual(rodata_header(trimmed), (0x14, 4))
        self.assertIsNone(trim_game_rodata.trim_rodata(trimmed, 0x14))

    def test_refuses_to_drop_nonzero_bytes(self):
        data = elf_with_rodata(bytes(range(1, 33)))
        with self.assertRaisesRegex(ValueError, "not zero"):
            trim_game_rodata.trim_rodata(data, 0x14)

    def test_refuses_to_grow_or_misalign(self):
        data = elf_with_rodata(bytes(16))
        with self.assertRaises(ValueError):
            trim_game_rodata.trim_rodata(data, 0x20)
        with self.assertRaises(ValueError):
            trim_game_rodata.trim_rodata(data, 0x6)


if __name__ == "__main__":
    unittest.main()
