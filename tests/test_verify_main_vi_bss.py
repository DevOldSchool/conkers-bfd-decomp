from pathlib import Path
import struct
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import verify_main_vi_bss as verifier

CODE = bytes(range(256)) * 3 + bytes(range(16))


def image(*, vi_name=".main_vi_bss", vi_type=1, vi_flags=1,
          vi_address=verifier.VI_VRAM, vi_size=verifier.VI_SIZE,
          vi_alignment=16, bss_address=verifier.BSS_VRAM,
          bss_size=verifier.BSS_SIZE, bss_flags=3,
          main_address=verifier.TEXT_VRAM, main_size=verifier.TEXT_SIZE,
          duplicate=False, include=True):
    names = b"\0.shstrtab\0" + vi_name.encode() + b"\0.main_bss\0.main\0"
    vi_offset = 52 + len(names)
    payload_offset = vi_offset + verifier.VI_SIZE
    section_offset = payload_offset + len(CODE)
    def index(name):
        return names.index(name.encode() + b"\0")
    sections = [(0,) * 10, (1, 3, 0, 0, 52, len(names), 0, 0, 1, 0)]
    if include:
        sections.append((index(vi_name), vi_type, vi_flags, vi_address, vi_offset,
                         vi_size, 0, 0, vi_alignment, 0))
    if duplicate:
        sections.append(sections[-1])
    sections.extend([
        (index(".main_bss"), 8, bss_flags, bss_address, 0, bss_size, 0, 0, 16, 0),
        (index(".main"), 1, 7, main_address, payload_offset, main_size, 0, 0, 16, 0),
    ])
    header = struct.pack(">16sHHIIIIIHHHHHH", b"\x7fELF\x01\x02\x01" + bytes(9),
                         2, 8, 1, 0, 0, section_offset, 0, 52, 0, 0, 40, len(sections), 1)
    return header + names + bytes(verifier.VI_SIZE) + CODE + b"".join(struct.pack(">10I", *s) for s in sections)


class ViBssTests(unittest.TestCase):
    def test_original_backing_and_info_mapping(self):
        self.assertEqual(verifier.linked_text(image()), CODE)

    def test_allocated_or_nobits_vi_storage_rejected(self):
        for kwargs in [{"vi_flags": f} for f in [0, 2, 3, 5]] + [{"vi_type": 8}]:
            with self.subTest(kwargs=kwargs), self.assertRaisesRegex(ValueError, "INFO PROGBITS"):
                verifier.linked_text(image(**kwargs))

    def test_nonzero_private_initializers_rejected(self):
        for at in [0, 0x1000, verifier.VI_SIZE - 1]:
            blob = bytearray(image())
            h = struct.unpack_from(">16sHHIIIIIHHHHHH", blob)
            section = struct.unpack_from(">10I", blob, h[6] + 2 * 40)
            blob[section[4] + at] = 1
            with self.subTest(at=at), self.assertRaisesRegex(ValueError, "zero-initialized"):
                verifier.linked_text(bytes(blob))

    def test_wrong_private_extent_alignment_or_address(self):
        for kwargs in [{"vi_size": 0x1010}, {"vi_size": 0x1080},
                       {"vi_address": verifier.VI_VRAM + 16}, {"vi_alignment": 8}]:
            with self.subTest(kwargs=kwargs), self.assertRaises(ValueError):
                verifier.linked_text(image(**kwargs))

    def test_shifted_or_grown_original_bss_rejected(self):
        for kwargs in [{"bss_size": verifier.BSS_SIZE + 0x1070},
                       {"bss_address": verifier.BSS_VRAM + 16}, {"bss_flags": 1}]:
            with self.subTest(kwargs=kwargs), self.assertRaisesRegex(ValueError, "allocation changed"):
                verifier.linked_text(image(**kwargs))

    def test_missing_duplicate_and_unreviewed_sections(self):
        for kwargs in [{"include": False}, {"duplicate": True}, {"vi_name": ".main_vi_other"}]:
            with self.subTest(kwargs=kwargs), self.assertRaises(ValueError):
                verifier.linked_text(image(**kwargs))

    def test_code_must_be_inside_main_section(self):
        for kwargs in [{"main_size": verifier.TEXT_SIZE - 4},
                       {"main_address": verifier.TEXT_VRAM + 4}]:
            with self.subTest(kwargs=kwargs), self.assertRaisesRegex(ValueError, "code is outside"):
                verifier.linked_text(image(**kwargs))

    def test_truncated_headers_and_sections(self):
        blob = image()
        for length in [0, 51, 52, len(blob) - 1]:
            with self.subTest(length=length), self.assertRaises(ValueError):
                verifier.linked_text(blob[:length])

    def test_unsupported_elf_identity(self):
        for at, value in [(0, 0), (4, 2), (5, 1), (17, 1), (19, 3)]:
            changed = bytearray(image()); changed[at] = value
            with self.subTest(at=at), self.assertRaises(ValueError):
                verifier.linked_text(bytes(changed))

    def test_all_linked_code_bytes_and_storage_relocations_compared(self):
        rom = bytes(verifier.TEXT_ROM) + CODE
        verifier.verify_bytes(CODE, rom)
        for at in [0, 0x35CE - verifier.TEXT_ROM, 0x369E - verifier.TEXT_ROM, len(CODE) - 1]:
            changed = bytearray(CODE); changed[at] ^= 1
            with self.subTest(at=at), self.assertRaisesRegex(ValueError, "differ"):
                verifier.verify_bytes(bytes(changed), rom)

    def test_truncated_rom_or_wrong_code_length(self):
        for code, rom in [(CODE[:-4], bytes(verifier.TEXT_ROM) + CODE),
                          (CODE, bytes(verifier.TEXT_ROM) + CODE[:-1])]:
            with self.subTest(length=len(code)), self.assertRaises(ValueError):
                verifier.verify_bytes(code, rom)


if __name__ == "__main__":
    unittest.main()
