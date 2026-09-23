import importlib.util
import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
SPEC = importlib.util.spec_from_file_location(
    "prepare_game_reference", ROOT / "scripts" / "prepare_game_reference.py"
)
prepare_game_reference = importlib.util.module_from_spec(SPEC)
assert SPEC.loader is not None
SPEC.loader.exec_module(prepare_game_reference)


class PrepareGameReferenceTests(unittest.TestCase):
    def test_archive_ranges_remain_independent_raw_references(self) -> None:
        source = "      - [0x100, lib, sdk, random, .text]\n      - [0x130, asm]\n"
        self.assertEqual(
            prepare_game_reference.raw_reference_map(source),
            "      - [0x100, asm]\n      - [0x130, asm]\n",
        )

    def test_integrated_empty_stub_boundaries_survive_fresh_reference_generation(self) -> None:
        # These reviewed stubs used to rely on internal raw-map split points.
        # Whole-unit C integration removes those points, so Splat must receive
        # explicit symbols or duplicate each stub in its preceding fallback.
        names = {'func_15086C68', 'func_15094E98', 'func_1515BE48',
                 'func_1516D2D8', 'func_151B5E8C', 'func_151DE6CC'}
        inventory = {entry['symbol']: entry for entry in
                     json.loads((ROOT / 'progress/functions.json').read_text())['functions']}
        symbols = (ROOT / 'config/symbols/game-us.txt').read_text()
        for name in names:
            region = inventory[name]['regions']['us']
            self.assertEqual(region['size_bytes'], 8)
            pattern = rf'(?m)^{name}\s*=\s*{region["vram"]};\s*//\s*type:func\s+size:0x8$'
            self.assertRegex(symbols, pattern)
        generated = prepare_game_reference.raw_reference_map((ROOT / 'config/game/us.yaml').read_text())
        self.assertIn('- config/symbols/game-us.txt', generated)

    def test_raw_reference_map_replaces_named_c_ranges_only(self) -> None:
        source = (
            "      - [0x0, asm]\n"
            "      - [0xAC0, c, game/game_2DF70]\n"
            "      - [0x3120, asm]\n"
        )

        self.assertEqual(
            prepare_game_reference.raw_reference_map(source),
            "      - [0x0, asm]\n"
            "      - [0xAC0, asm]\n"
            "      - [0x3120, asm]\n",
        )


if __name__ == "__main__":
    unittest.main()
