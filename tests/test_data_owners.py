import sys
import tempfile
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))

import data_owners


class DataOwnersTests(unittest.TestCase):
    def test_references_read_lo_operands_with_offsets(self):
        with tempfile.TemporaryDirectory() as directory:
            Path(directory, "1580B0.s").write_text(
                "lw $t9, %lo(D_8008AE00)($t9)\n"
                "lw $t0, %lo(D_8008AFB8 + 0x4)($t0)\n"
                "lui $t1, %hi(D_8008AE18)\n"
                "lw $t2, %lo(D_80000400)($t2)\n")
            refs = data_owners.references(Path(directory))
        self.assertEqual(refs, {0x8008AE00: {0x1580B0}, 0x8008AFBC: {0x1580B0}})

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
        extents = {e.unit: e for e in data_owners.data_extents(refs)}
        self.assertTrue(extents[0x200].fixed)
        self.assertEqual((extents[0x200].start, extents[0x200].end), (0x80083010, 0x80083020))
        # 0x80083040 is a second boundary before the next unit's first reference.
        self.assertIsNone(extents[0x300].end)
        self.assertFalse(extents[0x300].fixed)

    def test_shared_reference_blocks_an_extent(self):
        refs = {0x80083000: {0x100}, 0x80083010: {0x200}, 0x80083014: {0x200, 0x500},
                0x80083020: {0x300}}
        extents = {e.unit: e for e in data_owners.data_extents(refs)}
        self.assertFalse(extents[0x200].exclusive)
        self.assertFalse(extents[0x200].fixed)


if __name__ == "__main__":
    unittest.main()
