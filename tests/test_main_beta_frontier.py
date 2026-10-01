"""ROM-free checks for the bounded main/beta evidence scanner."""
import struct
import unittest

from scripts.audit_main_beta_frontier import (
    address_aliases,
    conditional_target,
    direct_target,
    scan_target,
    scan_main_range,
    words,
)


class MainBetaFrontierTests(unittest.TestCase):
    def test_direct_jump_uses_pc_region(self):
        word = (3 << 26) | (0x381C >> 2)
        self.assertEqual(direct_target(word, 0x15007A44), 0x1000381C)
        self.assertEqual(direct_target(word, 0x80001070), 0x8000381C)

    def test_non_jump_is_not_selector(self):
        self.assertIsNone(direct_target(0x03E00008, 0x8000381C))

    def test_direct_jump_uses_delay_boundary_region(self):
        self.assertEqual(direct_target(2 << 26, 0x0FFFFFFC), 0x10000000)

    def test_main_aliases_do_not_rewrite_game_targets(self):
        self.assertEqual(address_aliases(0x381C), (0x8000381C, 0x1000381C))
        self.assertEqual(address_aliases(0x150171A0), (0x150171A0,))

    def test_negative_conditional_displacement(self):
        self.assertEqual(conditional_target((5 << 26) | 0xFFFE, 0x80002000), 0x80001FFC)
        self.assertIsNone(conditional_target(3 << 26, 0x80002000))

    def test_cop1_branch_and_likely_branch(self):
        self.assertEqual(conditional_target((17 << 26) | (8 << 21) | 2, 0x1000), 0x100C)
        self.assertEqual(conditional_target((20 << 26) | 2, 0x1000), 0x100C)
        self.assertIsNone(conditional_target((17 << 26) | (9 << 21) | 2, 0x1000))

    def test_regimm_trap_is_not_a_branch(self):
        self.assertIsNone(conditional_target((1 << 26) | (8 << 16) | 2, 0x1000))

    def test_whole_range_includes_unlisted_interior_entry(self):
        code = struct.pack(">II", (3 << 26) | (0x1238 >> 2), 0)
        data = struct.pack(">I", 0x8000123C)
        result = scan_main_range(0x1230, 0x1240, [("game", code, 0x15000000)], [("data_offset", data, 0)])
        self.assertEqual(result["direct_entries"][0]["target"], "0x10001238")
        self.assertEqual(result["literal_pointers"][0]["target"], "0x8000123C")
        self.assertEqual(result["relative_crossings"], [])

    def test_unaligned_image_fails_closed(self):
        with self.assertRaises(ValueError):
            words(b"\0")

    def test_scan_distinguishes_candidates_from_selections(self):
        target = 0x1234
        code = struct.pack(">III", (3 << 26) | (target >> 2), (9 << 26) | target, 0)
        data = struct.pack(">II", 0x10001234, 0x80005678)
        result = scan_target(target, [("game", code, 0x15000000)], [("data_offset", data, 0)])
        self.assertEqual(result["direct"], [{"scope": "game", "address": "0x15000000"}])
        self.assertEqual(result["low_half_candidates"], [{"scope": "game", "address": "0x15000004"}])
        self.assertEqual(result["literal_pointers"], [{"scope": "data_offset", "address": "0x00000000"}])


if __name__ == "__main__":
    unittest.main()
