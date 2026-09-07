from __future__ import annotations

import importlib.util
import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "layout_helper", ROOT / "scripts" / "layout_check.py"
)
assert SPEC is not None and SPEC.loader is not None
layout_helper = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(layout_helper)


class LayoutCheckTests(unittest.TestCase):
    def fixture(self, root: Path) -> tuple[dict, dict]:
        functions = {
            "schema_version": 1,
            "functions": [
                {
                    "symbol": "func_first",
                    "regions": {
                        "us": {"symbol": "func_15000000", "vram": "0x15000000"}
                    },
                },
                {
                    "symbol": "func_second",
                    "regions": {
                        "us": {"symbol": "func_15000014", "vram": "0x15000014"}
                    },
                },
            ],
        }
        path = root / "progress" / "functions.json"
        path.parent.mkdir(parents=True)
        path.write_text(json.dumps(functions), encoding="utf-8")
        unit = {
            "functions": ["func_first", "func_second"],
            "regions": {"us": {"start": "0x0", "end": "0x20"}},
        }
        return functions["functions"][0], unit

    def test_accepts_preserved_member_offsets_and_extent(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            function, unit = self.fixture(root)
            with patch.object(layout_helper, "ROOT", root):
                layout_helper.validate_layout(
                    function,
                    unit,
                    {"func_15000000": 0, "func_15000014": 0x14},
                    0x20,
                    0x10,
                    "us",
                )

    def test_rejects_a_successor_shift_hidden_by_focused_diff(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            function, unit = self.fixture(root)
            with (
                patch.object(layout_helper, "ROOT", root),
                self.assertRaisesRegex(
                    layout_helper.LayoutError,
                    r"func_15000014 offset 0xC, expected 0x14",
                ),
            ):
                layout_helper.validate_layout(
                    function,
                    unit,
                    {"func_15000000": 0, "func_15000014": 0xC},
                    0x18,
                    0x10,
                    "us",
                )


if __name__ == "__main__":
    unittest.main()
