from __future__ import annotations

import struct
import unittest

from scripts.prepare_main_library_object import PreparationError, rebase_code_pointers


def fixture() -> tuple[bytes, int, int]:
    data = bytearray(52)
    data[:7] = b"\x7fELF\x01\x02\x01"
    struct.pack_into(">HHI", data, 16, 1, 8, 1)
    sections = [(0,) * 10]

    def section(kind: int, flags: int, payload: bytes, link=0, info=0, size=0) -> int:
        offset = len(data)
        data.extend(payload)
        sections.append((0, kind, flags, 0, offset, len(payload), link, info, 4, size))
        return offset

    section(1, 6, struct.pack(">II", 0x0C000000, 0x03E00008))
    rodata = section(1, 2, struct.pack(">III", 0x10, 0x20, 0x60))
    section(1, 3, b"\0" * 4)
    symbols = b"\0" * 16
    symbols += struct.pack(">IIIBBH", 0, 0, 8, 3, 0, 1)
    symbols += struct.pack(">IIIBBH", 0, 0, 4, 3, 0, 3)
    section(2, 0, symbols, info=3, size=16)
    relocations = section(
        9, 0, struct.pack(">IIIIII", 0, 0x102, 4, 0x102, 8, 0x202),
        link=4, info=2, size=8,
    )
    section(9, 0, struct.pack(">II", 0, 0x104), link=4, info=1, size=8)
    table = len(data)
    for entry in sections:
        data.extend(struct.pack(">10I", *entry))
    struct.pack_into(">I", data, 32, table)
    struct.pack_into(">HHHHHH", data, 40, 52, 0, 0, 40, len(sections), 0)
    return bytes(data), rodata, relocations


class MainLibraryObjectTests(unittest.TestCase):
    def test_rebases_only_data_code_pointers_and_preserves_compiled_instructions(self):
        original, rodata, _ = fixture()
        staged = rebase_code_pointers(original, -0x70000000, 2)
        expected = bytearray(original)
        struct.pack_into(">II", expected, rodata, 0x90000010, 0x90000020)
        self.assertEqual(staged, bytes(expected))
        # Applying the normal link address now produces the runtime alias.
        for offset, runtime in ((0, 0x10010010), (4, 0x10010020)):
            addend = struct.unpack_from(">I", staged, rodata + offset)[0]
            self.assertEqual((0x80010000 + addend) & 0xFFFFFFFF, runtime)
        self.assertEqual(struct.unpack_from(">I", original, rodata)[0], 0x10)

    def test_rejects_unreviewed_relocation_count(self):
        original, _, _ = fixture()
        with self.assertRaisesRegex(PreparationError, "expected 1.*found 2"):
            rebase_code_pointers(original, -0x70000000, 1)

    def test_rejects_other_data_code_relocation_types(self):
        original, _, relocations = fixture()
        changed = bytearray(original)
        struct.pack_into(">I", changed, relocations + 4, 0x104)
        with self.assertRaisesRegex(PreparationError, "R_MIPS_32"):
            rebase_code_pointers(bytes(changed), -0x70000000, 2)

    def test_rejects_invalid_pointer_offsets(self):
        original, _, relocations = fixture()
        for location in (2, 12):
            with self.subTest(location=location):
                changed = bytearray(original)
                struct.pack_into(">I", changed, relocations, location)
                with self.assertRaisesRegex(PreparationError, "out-of-bounds"):
                    rebase_code_pointers(bytes(changed), -0x70000000, 2)

    def test_rejects_nonobject_and_truncated_inputs(self):
        original, _, _ = fixture()
        executable = bytearray(original)
        struct.pack_into(">H", executable, 16, 2)
        for invalid in (b"not ELF", original[:-1], bytes(executable)):
            with self.assertRaises(PreparationError):
                rebase_code_pointers(invalid, -0x70000000, 2)
