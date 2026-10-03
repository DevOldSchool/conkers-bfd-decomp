from __future__ import annotations

import io
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import verify_debugger_rodata as verifier


NAME = ".debugger_rodata_1ad0"
VRAM = 0x1600487C
SIZE = 0xD0
TABLE = bytes.fromhex("1600257c16002860") * 26


def elf_fixture(entries=None):
    # Minimal ELF32 MIPS executable; each entry is name, bytes, VMA, flags, type.
    if entries is None:
        entries = [(NAME, TABLE, VRAM, 0, 1)]
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


class DebuggerRodataTests(unittest.TestCase):
    def test_accepts_exact_nonallocated_table_alongside_allocated_text(self):
        elf = elf_fixture([(".text", b"code", 0x16000000, 6, 1),
                           (NAME, TABLE, VRAM, 0, 1)])
        self.assertEqual(TABLE, verifier.external_payload(elf))

    def test_rejects_wrong_elf_identity(self):
        for offset, value in ((0, 0), (4, 2), (5, 1), (6, 0), (17, 1), (19, 3), (41, 0)):
            elf = bytearray(elf_fixture())
            elf[offset] = value
            with self.subTest(offset=offset), self.assertRaisesRegex(ValueError, "executable"):
                verifier.external_payload(bytes(elf))

    def test_rejects_missing_duplicate_unknown_or_wrongly_placed_section(self):
        for entries in ([], [(NAME, TABLE, VRAM, 0, 1)] * 2,
                        [(".debugger_rodata_other", TABLE, VRAM, 0, 1)],
                        [(NAME, TABLE, VRAM, 0, 1), (".debugger_rodata_extra", b"", 0, 0, 1)],
                        [(NAME, TABLE, VRAM + 4, 0, 1)],
                        [(NAME, TABLE[:-4], VRAM, 0, 1)],
                        [(NAME, TABLE + bytes(4), VRAM, 0, 1)]):
            with self.subTest(entries=entries), self.assertRaises(ValueError):
                verifier.external_payload(elf_fixture(entries))

    def test_rejects_allocated_writable_executable_or_nonprogbits_table(self):
        for flags, kind in ((2, 1), (1, 1), (4, 1), (0, 8), (0, 7)):
            with self.subTest(flags=flags, kind=kind), self.assertRaisesRegex(ValueError, "INFO"):
                verifier.external_payload(elf_fixture([(NAME, TABLE, VRAM, flags, kind)]))

    def test_rejects_malformed_or_truncated_elf_metadata_and_payload(self):
        elf = elf_fixture()
        section_offset = struct.unpack_from(">I", elf, 32)[0]
        mutations = [(32, len(elf)), (section_offset + 40, 0xFFFFFFFF),
                     (section_offset + 40 + 16, len(elf) - 4),
                     (section_offset + 80 + 16, len(elf)),
                     (section_offset + 80 + 4, 1)]
        for offset, value in mutations:
            changed = bytearray(elf)
            struct.pack_into(">I", changed, offset, value)
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                verifier.external_payload(bytes(changed))
        for changed in (elf[:51], elf[:-1]):
            with self.assertRaisesRegex(ValueError, "truncated"):
                verifier.external_payload(changed)

    def test_compares_every_case_byte_without_consuming_neighboring_data(self):
        data = b"before!!" + TABLE + b"\x00" * 4 + b"nextdouble"
        verifier.verify_bytes(TABLE, data, VRAM - 8)
        for position in (0, 3, SIZE // 2, SIZE - 4, SIZE - 1):
            changed = bytearray(TABLE)
            changed[position] ^= 1
            with self.subTest(position=position), self.assertRaisesRegex(ValueError, "differs"):
                verifier.verify_bytes(bytes(changed), data, VRAM - 8)

    def test_rejects_truncated_extra_or_out_of_interval_payload(self):
        for payload in (TABLE[:-1], TABLE + b"\0"):
            with self.assertRaisesRegex(ValueError, "size"):
                verifier.verify_bytes(payload, TABLE, VRAM)
        for data, base in ((TABLE, VRAM + 4), (TABLE[:-1], VRAM), (TABLE, VRAM - 4)):
            with self.assertRaisesRegex(ValueError, "outside"):
                verifier.verify_bytes(TABLE, data, base)

    def test_verifier_uses_checked_debugger_data_and_preserves_input_elf(self):
        with tempfile.TemporaryDirectory() as directory:
            elf = Path(directory) / "input.elf"
            original = elf_fixture()
            elf.write_bytes(original)
            with patch.object(verifier.rom_span, "debugger_image",
                              return_value=(b"", TABLE, 0x16000000, VRAM, "checked")) as rom, \
                    redirect_stdout(io.StringIO()):
                verifier.verify(elf)
            rom.assert_called_once_with(verifier.ROOT)
            self.assertEqual(original, elf.read_bytes())

    def test_invalid_rom_checksum_cannot_succeed(self):
        with tempfile.TemporaryDirectory() as directory:
            elf = Path(directory) / "input.elf"
            elf.write_bytes(elf_fixture())
            with patch.object(verifier.rom_span, "debugger_image",
                              side_effect=ValueError("checksum-validated US ROM")), \
                    redirect_stdout(io.StringIO()) as output:
                with self.assertRaisesRegex(ValueError, "checksum-validated"):
                    verifier.verify(elf)
                self.assertEqual("", output.getvalue())


@unittest.skipUnless(all(shutil.which(tool) for tool in
                        ("mips-linux-gnu-as", "mips-linux-gnu-ld", "mips-linux-gnu-objdump")),
                     "requires pinned MIPS binutils")
class DebuggerRodataLinkTests(unittest.TestCase):
    def test_info_mapping_preserves_addressless_header_and_boot(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "fixture.s"
            source.write_text('.section .rodata\n.balign 16\n.space 0xD0\n'
                              '.section .fixture_header,"a"\n.space 0x40\n'
                              '.section .fixture_boot,"a"\n.space 0xFC0\n')
            obj = root / "debugger_1AD0.o"
            subprocess.run(["mips-linux-gnu-as", "-EB", "-mabi=32", "-march=vr4300",
                            "-o", str(obj), str(source)], check=True, capture_output=True)
            script = root / "generated.ld"
            script.write_text('SECTIONS { .header : { *(.fixture_header) } '
                              '.boot : { *(.fixture_boot) } '
                              '.text 0x80001000 : { *(.text) } '
                              '/DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) } }\n')
            elf = root / "fixture.elf"
            subprocess.run(["mips-linux-gnu-ld", "-m", "elf32btsmip", "-T",
                            str(verifier.ROOT / "config/debugger/us-rodata.ld"),
                            "-T", str(script), "-o", str(elf), str(obj)],
                           check=True, capture_output=True)
            self.assertEqual(bytes(SIZE), verifier.external_payload(elf.read_bytes()))
            headers = subprocess.check_output(["mips-linux-gnu-objdump", "-h", str(elf)],
                                              text=True)
            observed = {}
            for line in headers.splitlines():
                fields = line.split()
                if len(fields) >= 4 and fields[1] in (".header", ".boot"):
                    observed[fields[1]] = (int(fields[2], 16), int(fields[3], 16))
            self.assertEqual({".header": (0x40, 0), ".boot": (0xFC0, 0x40)}, observed)


if __name__ == "__main__":
    unittest.main()
