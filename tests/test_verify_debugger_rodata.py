from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import verify_debugger_rodata as verifier

NAME = '.debugger'
VRAM = 0x16000000
SIZE = 0x4960
TABLE = bytes(SIZE)

def elf_fixture(entries=None):
    # Minimal ELF32 MIPS executable; each entry is name, bytes, VMA, flags, type.
    if entries is None:
        entries = [(NAME, TABLE, VRAM, 7, 1)]
    names = bytearray(b"\0.shstrtab\0")
    body = bytearray(52)
    sections = [bytes(40)]
    for name, payload, vram, flags, kind in entries:
        name_offset = len(names)
        names.extend(name.encode("ascii") + b"\0")
        sections.append(struct.pack(">10I", name_offset, kind, flags, vram,
                                    len(body), len(payload), 0, 0, 4, 0))
        body.extend(payload)
    sections.append(struct.pack(">10I", 1, 3, 0, 0, len(body), len(names), 0, 0, 1, 0))
    body.extend(names)
    body.extend(bytes(-len(body) % 4))
    section_offset = len(body)
    body.extend(b"".join(sections))
    body[:52] = struct.pack(">16sHHIIIIIHHHHHH", b"\x7fELF\x01\x02\x01" + bytes(9),
                           2, 8, 1, 0, 0, section_offset, 0, 52, 0, 0, 40,
                           len(sections), len(sections) - 1)
    return bytes(body)


class DebuggerAllocatedDataTests(unittest.TestCase):
    def test_accepts_only_actual_allocated_loader_image(self):
        self.assertEqual(TABLE, verifier.allocated_image(elf_fixture()))
        for flags, kind in ((0, 1), (3, 1), (6, 1), (7, 8)):
            with self.subTest(flags=flags, kind=kind), self.assertRaises(ValueError):
                verifier.allocated_image(elf_fixture([(NAME, TABLE, VRAM, flags, kind)]))

    def test_rejects_missing_duplicate_wrong_extent_and_info_copy(self):
        for entries in ([], [(NAME, TABLE, VRAM, 7, 1)] * 2,
                        [(NAME, TABLE, VRAM + 4, 7, 1)],
                        [(NAME, TABLE[:-4], VRAM, 7, 1)],
                        [(NAME, TABLE + bytes(4), VRAM, 7, 1)],
                        [(NAME, TABLE, VRAM, 7, 1),
                         ('.debugger_rodata_1ad0', bytes(208), 0x1600487C, 0, 1)]):
            with self.subTest(count=len(entries)), self.assertRaises(ValueError):
                verifier.allocated_image(elf_fixture(entries))

    def test_rejects_wrong_identity_and_truncation(self):
        for offset, value in ((0, 0), (4, 2), (5, 1), (6, 0), (17, 1), (19, 3), (41, 0)):
            elf = bytearray(elf_fixture()); elf[offset] = value
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                verifier.allocated_image(bytes(elf))
        for elf in (elf_fixture()[:51], elf_fixture()[:-1]):
            with self.assertRaises(ValueError):
                verifier.allocated_image(elf)

    def test_verifies_every_code_and_data_byte_against_checked_rom(self):
        checked = (bytes(0x36F0), bytes(0x1270), VRAM, VRAM + 0x36F0, 'checked')
        with tempfile.TemporaryDirectory() as directory:
            elf = Path(directory) / 'image.elf'
            elf.write_bytes(elf_fixture())
            with patch.object(verifier.rom_span, 'debugger_image', return_value=checked) as rom:
                verifier.verify(elf)
                rom.assert_called_once_with(verifier.ROOT)
                for offset in (0, 0x3650, 0x36F0, 0x3C70, 0x4800, 0x487C, 0x494B, 0x4950, SIZE - 1):
                    image = bytearray(TABLE); image[offset] = 1
                    elf.write_bytes(elf_fixture([(NAME, image, VRAM, 7, 1)]))
                    with self.subTest(offset=offset), self.assertRaisesRegex(ValueError, 'differs'):
                        verifier.verify(elf)

    def test_invalid_rom_or_changed_loader_boundary_cannot_succeed(self):
        with tempfile.TemporaryDirectory() as directory:
            elf = Path(directory) / 'image.elf'; elf.write_bytes(elf_fixture())
            with patch.object(verifier.rom_span, 'debugger_image', side_effect=ValueError('checksum')):
                with self.assertRaisesRegex(ValueError, 'checksum'):
                    verifier.verify(elf)
            with patch.object(verifier.rom_span, 'debugger_image',
                              return_value=(bytes(0x36F0), bytes(0x1270), VRAM, VRAM, 'checked')):
                with self.assertRaisesRegex(ValueError, 'boundaries'):
                    verifier.verify(elf)


if __name__ == '__main__':
    unittest.main()
