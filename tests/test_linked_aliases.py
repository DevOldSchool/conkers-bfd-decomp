from __future__ import annotations

import shutil
import json
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
from candidate_tables import Object32
import linked_aliases
import rom_span


class SpanProofTests(unittest.TestCase):
    def test_unapproved_rom_checksum_is_rejected_before_decompression(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / "config").mkdir()
            (root / "rom.z64").write_bytes(b"not the reviewed ROM")
            (root / "config/rzip_layouts.json").write_text(json.dumps({"profiles": {"us": {
                "default_rom": "rom.z64", "normalized_sha1": ["a" * 40]}}}))
            with patch.object(rom_span.rzip_archive, "normalize_rom", return_value=(b"wrong ROM", None)), \
                    patch.object(rom_span.rzip_archive, "parse_game_archive") as parse:
                with self.assertRaisesRegex(ValueError, "checksum-validated"):
                    rom_span.game_code(root)
                parse.assert_not_called()

    def test_full_span_requires_contiguous_rom_bytes_including_final_word(self):
        raw = "/* 0 15000000 03E00008 */ jr $ra\n/* 4 15000004 00000000 */ nop\n"
        code = bytes.fromhex("03e0000800000000")
        self.assertEqual(code, rom_span.raw_span(raw, 0x15000000, 8, code, 0x15000000))
        for assembly, size, payload in ((raw, 4, code), (raw, 12, code),
                                        (raw.replace("15000004", "15000008"), 8, code),
                                        (raw, 8, code[:-1] + b"\x01")):
            with self.assertRaises(ValueError):
                rom_span.raw_span(assembly, 0x15000000, size, payload, 0x15000000)

    def test_comparison_object_preserves_every_byte_and_exact_extent(self):
        payload = bytes.fromhex("03e000082402000100000000")
        obj = Object32(linked_aliases.comparison_object(payload, "func_test"))
        origin, section = linked_aliases.function(obj, "func_test", len(payload))
        self.assertEqual(0, origin)
        self.assertEqual(payload, obj.section(section))
        self.assertFalse(obj.relocations)
        with self.assertRaisesRegex(ValueError, "extent"):
            linked_aliases.function(obj, "func_test", len(payload) - 4)


@unittest.skipUnless(shutil.which("mips-linux-gnu-as") and shutil.which("mips-linux-gnu-ld"),
                     "requires pinned MIPS binutils")
class LinkedAliasToolchainTests(unittest.TestCase):
    def assemble(self, root, name, expression, *, tail="nop", extent=16):
        path = root / (name + ".s")
        path.write_text(".text\n.set noreorder\n.globl func_15000000\nfunc_15000000:\n"
                        f"lui $v0,%hi({expression})\naddiu $v0,$v0,%lo({expression})\n"
                        f"jr $ra\n{tail}\n.size func_15000000,{extent}\n")
        output = path.with_suffix(".o")
        subprocess.run(["mips-linux-gnu-as", "-EB", "-mabi=32", "-march=vr4300",
                        "-o", str(output), str(path)], check=True, capture_output=True)
        return output

    def prepare(self, root, candidate, reference, address, *, raw_override=None, start=0x15000000):
        high = ((address + 0x8000) >> 16) & 0xFFFF
        words = [0x3C020000 | high, 0x24420000 | (address & 0xFFFF), 0x03E00008, 0]
        code = struct.pack(">4I", *words)
        raw = root / "raw.s"
        raw.write_text(raw_override or "".join(
            f"/* {i*4:X} {start+i*4:08X} {word:08X} */ instruction\n"
            for i, word in enumerate(words)))
        with patch.object(rom_span, "game_code", return_value=(code, start, "rom")):
            return linked_aliases.prepare(root, candidate, reference, raw, "func_15000000", start, 16)

    def test_registered_address_need_only_be_word_aligned(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            candidate = self.assemble(root, "candidate", "D_800E0A30+0x40")
            reference = self.assemble(root, "reference", "D_800E0A70")
            self.assertIsNotNone(self.prepare(root, candidate, reference, 0x800E0A70, start=0x15000004))

    def test_equivalent_aliases_and_signed_low_carry_match(self):
        for base, offset in ((0x800E0A30, 0x40), (0x800E7FFC, 4)):
            with self.subTest(base=base), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                candidate = self.assemble(root, "candidate", f"D_{base:08X}+{offset}")
                reference = self.assemble(root, "reference", f"D_{base+offset:08X}")
                pair = self.prepare(root, candidate, reference, base + offset)
                self.assertIsNotNone(pair)
                self.assertEqual(pair[0].read_bytes(), pair[1].read_bytes())

    def test_wrong_address_or_final_instruction_or_extent_never_becomes_zero(self):
        for expression, tail, extent in (("D_800E0A30+0x44", "nop", 16),
                                          ("D_800E0A30+0x40", "addiu $v1,$zero,1", 16),
                                          ("D_800E0A30+0x40", "nop", 12)):
            with self.subTest(expression=expression, tail=tail, extent=extent), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                candidate = self.assemble(root, "candidate", expression, tail=tail, extent=extent)
                reference = self.assemble(root, "reference", "D_800E0A70")
                self.assertIsNone(self.prepare(root, candidate, reference, 0x800E0A70))

    def test_reference_must_link_to_actual_rom_not_just_agree_with_candidate(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            candidate = self.assemble(root, "candidate", "D_800E0A30+0x40")
            reference = self.assemble(root, "reference", "D_800E0A70")
            with self.assertRaisesRegex(ValueError, "raw-reference span differs"):
                self.prepare(root, candidate, reference, 0x800E0A74)

    def test_unknown_symbol_fails_closed_to_original_symbolic_diff(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            candidate = self.assemble(root, "candidate", "D_800E0A30+0x40", tail="jal unknown_function")
            reference = self.assemble(root, "reference", "D_800E0A70")
            self.assertIsNone(self.prepare(root, candidate, reference, 0x800E0A70))
