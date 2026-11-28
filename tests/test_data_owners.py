import sys
import tempfile
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))

import data_owners

RODATA = 0x80090000


class DataOwnersTests(unittest.TestCase):
    def test_references_read_lo_operands_with_offsets(self):
        with tempfile.TemporaryDirectory() as directory:
            Path(directory, "1580B0.s").write_text(
                "lw $t9, %lo(D_8008AE00)($t9)\n"
                "lw $t0, %lo(D_8008AFB8 + 0x4)($t0)\n"
                "lui $t1, %hi(D_8008AE18)\n"
                "lw $t2, %lo(D_80000400)($t2)\n"
                "addiu $at, $at, %lo(jtbl_8008857C_game)\n")
            refs = data_owners.references(Path(directory))
        self.assertEqual(refs, {0x8008AE00: {0x1580B0}, 0x8008AFBC: {0x1580B0},
                                0x8008857C: {0x1580B0}})

    def test_raw_base_follows_register_until_redefined_or_label(self):
        def line(text, slot=False):
            return "    /* 0 0 0 */  " + (" " if slot else "") + text
        lines = [
            line("lui        $t5, (0x80090000 >> 16)"),
            line("beql       $t7, $t8, .L1"),
            line("lb        $t5, 0x0($t3)", slot=True),  # branch-likely slot: taken path only
            line("andi       $t6, $t5, 0x200"),  # not an address use
            line("nop"),
            line("lhu        $t5, -0x244($t5)"),  # use, then redefinition
            line("lw         $t0, 0x10($t5)"),
            line("lui        $at, (0x800A0000 >> 16)"),
            line("addiu      $a0, $at, 0x20"),
            "  .L2:",
            line("lwc1       $f0, 0x30($at)"),  # another path may reach the label
        ]
        self.assertEqual(data_owners.raw_base_references(lines), [0x8008FDBC, 0x800A0020])

    def test_owner_chain_drops_out_of_order_references(self):
        refs = {0x80083000: {0x100}, 0x80083010: {0x300}, 0x80083020: {0x200}, 0x80083030: {0x200}}
        owners = data_owners.owner_chain(refs, sorted(refs))
        self.assertEqual(owners, {0x80083000: 0x100, 0x80083020: 0x200, 0x80083030: 0x200})

    def test_extent_is_fixed_only_by_unique_16_byte_boundaries(self):
        refs = {
            0x80083004: {0x100},
            0x80083010: {0x200}, 0x80083018: {0x200},
            0x80083020: {0x300}, 0x80083034: {0x300},
            0x80083050: {0x400},
        }
        extents = {e.unit: e for e in data_owners.data_extents(refs, RODATA)}
        self.assertTrue(extents[0x200].fixed)
        self.assertEqual((extents[0x200].start, extents[0x200].end), (0x80083010, 0x80083020))
        # 0x80083040 is a second boundary before the next unit's first reference.
        self.assertIsNone(extents[0x300].end)
        self.assertFalse(extents[0x300].fixed)

    def test_shared_reference_blocks_an_extent(self):
        refs = {0x80083000: {0x100}, 0x80083010: {0x200}, 0x80083014: {0x200, 0x500},
                0x80083020: {0x300}}
        extents = {e.unit: e for e in data_owners.data_extents(refs, RODATA)}
        self.assertFalse(extents[0x200].exclusive)
        self.assertFalse(extents[0x200].fixed)

    def test_multi_unit_address_does_not_extend_its_own_chain(self):
        # Counting 0x80083000 once for each of its units would make
        # 0x100 -> 0x200 -> 0x250 a chain of three; it is really two long,
        # so the later two-long chain 0x60 -> 0x70 is kept.
        refs = {0x80083000: {0x100, 0x200}, 0x80083010: {0x250},
                0x80083020: {0x60}, 0x80083030: {0x70}}
        owners = data_owners.owner_chain(refs, sorted(refs))
        self.assertEqual(owners, {0x80083020: 0x60, 0x80083030: 0x70})

    def test_start_rule_needs_an_aligned_first_reference(self):
        refs = {0x80083000: {0x100}, 0x80083014: {0x200}, 0x80083020: {0x300}}
        extents = {e.unit: e for e in data_owners.data_extents(refs, RODATA)}
        self.assertIsNone(extents[0x200].start)

    def test_dropped_address_inside_an_extent_makes_it_shared(self):
        # 0x80083018 is referenced only by unit 0x050, which breaks the order.
        refs = {0x80083000: {0x100}, 0x80083010: {0x200}, 0x80083018: {0x050},
                0x8008301C: {0x200}, 0x80083020: {0x300}}
        extents = {e.unit: e for e in data_owners.data_extents(refs, RODATA)}
        self.assertFalse(extents[0x200].exclusive)

    def test_addresses_at_or_above_the_rodata_sweep_are_ignored(self):
        refs = {0x80083000: {0x100}, 0x80090000: {0x050}}
        self.assertEqual([e.unit for e in data_owners.data_extents(refs, RODATA)], [0x100])

    def test_status_precedence_and_exact_placement(self):
        def extent(**fields):
            base = dict(unit=0x200, first=0x80083010, last=0x80083018, start=0x80083010,
                        end=0x80083020, exclusive=True)
            return data_owners.Extent(**{**base, **fields})
        whole = [(0x80083010, 0x80083020, ".a")]
        halves = [(0x80083010, 0x80083018, ".a"), (0x80083018, 0x80083020, ".b")]
        cases = [
            (extent(exclusive=False, start=None), whole, "shared"),
            (extent(start=None, end=None), whole, "start-ambiguous"),
            (extent(end=None), whole, "end-ambiguous"),
            (extent(), [], "ready"),
            (extent(), whole, "placed"),
            (extent(), halves, "placed"),
            (extent(), [(0x80083010, 0x80083030, ".a")], "misplaced"),
            (extent(), [(0x80083000, 0x80083014, ".a")], "misplaced"),
        ]
        for value, placed, expected in cases:
            with self.subTest(expected=expected, placed=placed):
                self.assertEqual(data_owners.status(value, placed)[0], expected)


if __name__ == "__main__":
    unittest.main()
