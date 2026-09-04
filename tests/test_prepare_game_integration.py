from __future__ import annotations

import importlib.util
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
SPEC = importlib.util.spec_from_file_location(
    "prepare_game_integration", ROOT / "scripts" / "prepare_game_integration.py"
)
assert SPEC is not None and SPEC.loader is not None
prepare_game_integration = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(prepare_game_integration)


class PrepareGameIntegrationTests(unittest.TestCase):
    def test_preserves_adjacent_archives_and_the_following_raw_boundary(self) -> None:
        source = (
            "      - [0x0, asm]\n"
            "      - [0x10, asm]\n"
            "      - [0x20, lib, sdk, first, .text]\n"
            "      - [0x30, lib, sdk, second, .text]\n"
            "      - [0x40, asm]\n"
            "      - [0x50, asm]\n"
            "      - [0x60, c, game/test]\n"
        )
        self.assertEqual(
            prepare_game_integration.collapse_raw_assembly_boundaries(source),
            source.replace("      - [0x10, asm]\n", "").replace("      - [0x50, asm]\n", ""),
        )

    def test_keeps_only_boundaries_needed_by_c_units(self) -> None:
        source = (
            "    subsegments:\n"
            "      - [0x0, asm]\n"
            "      - [0x10, asm]\n"
            "      - [0x20, c, game/done/first]\n"
            "      - [0x30, asm]\n"
            "      - [0x40, asm]\n"
            "      - [0x50, c, game/done/second]\n"
            "      - [0x60, asm]\n"
            "      - [0x70, asm]\n"
        )

        result = prepare_game_integration.collapse_raw_assembly_boundaries(source)

        self.assertIn("- [0x0, asm]", result)
        self.assertNotIn("- [0x10, asm]", result)
        self.assertIn("- [0x20, c, game/done/first]", result)
        self.assertIn("- [0x30, asm]", result)
        self.assertNotIn("- [0x40, asm]", result)
        self.assertIn("- [0x50, c, game/done/second]", result)
        self.assertIn("- [0x60, asm]", result)
        self.assertNotIn("- [0x70, asm]", result)


if __name__ == "__main__":
    unittest.main()
