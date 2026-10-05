from pathlib import Path
import struct
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import verify_main_rodata as verifier


def image(*, name=verifier.SECTION_NAME, flags=0, address=verifier.SECTION_VRAM,
          size=verifier.SECTION_SIZE, duplicate=False, include=True):
    names = b"\0.shstrtab\0" + name.encode() + b"\0"
    data_offset = 52 + len(names)
    payload = bytes(range(32))
    section_offset = data_offset + len(payload)
    sections = [(0,) * 10, (1, 3, 0, 0, 52, len(names), 0, 0, 1, 0)]
    if include:
        sections.append((11, 1, flags, address, data_offset, size, 0, 0, 4, 0))
    if duplicate:
        sections.append(sections[-1])
    header = struct.pack(">16sHHIIIIIHHHHHH", b"\x7fELF\x01\x02\x01" + bytes(9),
                         2, 8, 1, 0, 0, section_offset, 0, 52, 0, 0, 40, len(sections), 1)
    return header + names + payload + b"".join(struct.pack(">10I", *s) for s in sections)


class MainRodataTests(unittest.TestCase):
    def test_reviewed_info_payload(self):
        self.assertEqual(verifier.external_payload(image()), bytes(range(32)))

    def test_missing_and_duplicate_tables(self):
        for blob in [image(include=False), image(duplicate=True)]:
            with self.subTest(blob_size=len(blob)), self.assertRaises(ValueError):
                verifier.external_payload(blob)

    def test_unreviewed_table(self):
        with self.assertRaisesRegex(ValueError, "unreviewed"):
            verifier.external_payload(image(name=".main_rodata_other"))

    def test_allocated_or_writable_sections_rejected(self):
        for flags in [1, 2, 3, 4]:
            with self.subTest(flags=flags), self.assertRaisesRegex(ValueError, "non-allocated read-only"):
                verifier.external_payload(image(flags=flags))

    def test_wrong_address_or_extent_rejected(self):
        for blob in [image(address=verifier.SECTION_VRAM + 4), image(size=28), image(size=36)]:
            with self.subTest(blob_size=len(blob)), self.assertRaisesRegex(ValueError, "mapping"):
                verifier.external_payload(blob)

    def test_truncated_headers_and_sections(self):
        blob = image()
        for length in [0, 51, 52, len(blob) - 1]:
            with self.subTest(length=length), self.assertRaises(ValueError):
                verifier.external_payload(blob[:length])

    def test_unsupported_elf_identity(self):
        for at, value in [(0, 0), (4, 2), (5, 1), (17, 1), (19, 3)]:
            blob = bytearray(image()); blob[at] = value
            with self.subTest(at=at), self.assertRaises(ValueError):
                verifier.external_payload(bytes(blob))

    def test_full_payload_and_padding_compared(self):
        linked = bytes(range(32))
        rom = bytes(verifier.ROM_START) + linked
        verifier.verify_bytes(linked, rom)
        for at in [0, 27, 28, 31]:
            changed = bytearray(linked); changed[at] ^= 1
            with self.subTest(at=at), self.assertRaisesRegex(ValueError, "differs"):
                verifier.verify_bytes(bytes(changed), rom)

    def test_truncated_rom_and_wrong_payload_size(self):
        for linked, rom in [(bytes(32), bytes(verifier.ROM_START + 31)), (bytes(28), bytes(verifier.ROM_START + 32))]:
            with self.subTest(length=len(linked)), self.assertRaises(ValueError):
                verifier.verify_bytes(linked, rom)


if __name__ == "__main__":
    unittest.main()
