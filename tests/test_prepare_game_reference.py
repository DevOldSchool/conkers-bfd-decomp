import importlib.util
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
