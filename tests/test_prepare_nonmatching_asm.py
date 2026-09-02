from __future__ import annotations

import importlib.util
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock


ROOT = Path(__file__).resolve().parent.parent
SCRIPTS = ROOT / "scripts"
sys.path.insert(0, str(SCRIPTS))
SPEC = importlib.util.spec_from_file_location(
    "prepare_nonmatching_asm", SCRIPTS / "prepare_nonmatching_asm.py"
)
assert SPEC is not None and SPEC.loader is not None
prepare_nonmatching_asm = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(prepare_nonmatching_asm)


class PrepareNonmatchingAssemblyTests(unittest.TestCase):
    def test_identical_generated_file_keeps_its_timestamp(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "func_test.s"
            output.write_text("glabel func_test\n", encoding="utf-8")

            with mock.patch.object(Path, "write_text") as write_text:
                changed = prepare_nonmatching_asm.write_if_changed(
                    output, "glabel func_test\n"
                )

            self.assertFalse(changed)
            write_text.assert_not_called()

    def test_changed_generated_file_is_rewritten(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "func_test.s"
            output.write_text("old\n", encoding="utf-8")

            changed = prepare_nonmatching_asm.write_if_changed(output, "new\n")

            self.assertTrue(changed)
            self.assertEqual(output.read_text(encoding="utf-8"), "new\n")


if __name__ == "__main__":
    unittest.main()
