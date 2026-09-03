from __future__ import annotations

import runpy
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
audit = runpy.run_path(str(ROOT / "scripts/audit_library_boundaries.py"))
TextTemplate = audit["TextTemplate"]
find_occurrences = audit["find_occurrences"]


class LibraryBoundaryAuditTests(unittest.TestCase):
    def test_dictionary_rodata_mapping_excludes_owned_bytes_from_raw_scan(self) -> None:
        subsegments = [
            [0, "asm"],
            [0x10, "lib", "libultrare", "formatter", ".text"],
            [0x20, "data"],
            {"start": 0x30, "type": "lib", "name": "libultrare", "object": "formatter",
             "section": ".rodata", "linker_section_order": ".data"},
            [0x40, "data"],
            {"start": 0x50, "type": "lib", "name": "libultrare", "object": "state",
             "section": ".bss", "vram": 0x80010000},
        ]
        ranges = audit["mapped_section_ranges"](subsegments, 0x50)
        self.assertEqual({".text": [(0x10, 0x20)], ".rodata": [(0x30, 0x40)]}, ranges)
        self.assertTrue(audit["overlaps"](ranges[".rodata"], 0x30, 0x40))
        self.assertFalse(audit["overlaps"](ranges[".rodata"], 0x20, 0x30))

    def test_hi16_relocation_masks_the_immediate_but_preserves_the_opcode(self) -> None:
        template = TextTemplate(
            text=bytes.fromhex("3c01800403e00008"),
            relocations=((0, 5),),
        )

        self.assertEqual(bytes.fromhex("ffff0000ffffffff"), template.compare_mask)
        self.assertEqual([0], find_occurrences(template, bytes.fromhex("3c01123403e00008"), 0, 8))
        self.assertEqual([], find_occurrences(template, bytes.fromhex("3401123403e00008"), 0, 8))

    def test_mips26_relocation_masks_the_target_but_preserves_jal(self) -> None:
        template = TextTemplate(
            text=bytes.fromhex("0c123456000000000000000000000000"),
            relocations=((0, 4),),
        )

        self.assertEqual(bytes.fromhex("fc000000ffffffffffffffffffffffff"), template.compare_mask)
        self.assertEqual(
            [0],
            find_occurrences(
                template,
                bytes.fromhex("0fffffff000000000000000000000000"),
                0,
                16,
            ),
        )
        self.assertEqual(
            [],
            find_occurrences(
                template,
                bytes.fromhex("0bffffff000000000000000000000000"),
                0,
                16,
            ),
        )

    def test_section_alignment_is_respected(self) -> None:
        template = TextTemplate(
            text=bytes.fromhex("0102030405060708090a0b0c0d0e0f10"),
            relocations=(),
            section=".rodata",
            alignment=8,
        )
        rom = b"\0" * 4 + template.text + b"\0" * 4 + template.text

        self.assertEqual([24], find_occurrences(template, rom, 0, len(rom)))


if __name__ == "__main__":
    unittest.main()
