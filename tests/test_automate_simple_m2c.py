#!/usr/bin/env python3
"""Tests for conservative unchanged-m2c automation."""

from __future__ import annotations

import importlib.util
import io
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path
from unittest.mock import patch


ROOT = Path(__file__).resolve().parent.parent
SCRIPTS = ROOT / "scripts"
sys.path.insert(0, str(SCRIPTS))
SPEC = importlib.util.spec_from_file_location(
    "automate_simple_m2c", SCRIPTS / "automate_simple_m2c.py"
)
assert SPEC is not None and SPEC.loader is not None
automation = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = automation
SPEC.loader.exec_module(automation)


class AutomateSimpleM2cTests(unittest.TestCase):
    SOURCE = "src/game/test.c"
    PRAGMA = '#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\n'

    def test_extracts_definition_without_guessed_declarations(self) -> None:
        starter = """\
extern s32 D_800DBE38;
void func_target(s32);

void func_test(s32 arg0) {
    func_target(arg0 + D_800DBE38);
}
"""

        self.assertEqual(
            "void func_test(s32 arg0) {\n    func_target(arg0 + D_800DBE38);\n}\n",
            automation.extract_simple_definition(starter, "func_test"),
        )

    def test_rejects_m2c_placeholders_in_definition(self) -> None:
        starter = """\
void func_test(void *arg0) {
    M2C_FIELD(arg0, s32, 0x18) = 1;
}
"""

        with self.assertRaisesRegex(automation.AutomationError, "M2C placeholder"):
            automation.extract_simple_definition(starter, "func_test")

    def test_replaces_only_the_canonical_pragma_and_preserves_crlf(self) -> None:
        source = "src/game/test.c"
        original = (
            b'#include "types.h"\r\n'
            b'\r\n'
            b'#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\r\n'
        )

        updated = automation.replace_target_pragma(
            original,
            source,
            "func_test",
            "void func_test(void) {\n    return;\n}\n",
        )

        self.assertEqual(
            b'#include "types.h"\r\n\r\nvoid func_test(void) {\r\n    return;\r\n}\r\n',
            updated,
        )

    def test_refuses_missing_or_duplicate_pragmas(self) -> None:
        pragma = b'#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\n'
        with self.assertRaisesRegex(automation.AutomationError, "found 0"):
            automation.replace_target_pragma(
                b"", "src/game/test.c", "func_test", "void func_test(void) {}\n"
            )
        with self.assertRaisesRegex(automation.AutomationError, "found 2"):
            automation.replace_target_pragma(
                pragma + pragma,
                "src/game/test.c",
                "func_test",
                "void func_test(void) {}\n",
            )

    def test_mismatch_restores_the_source_byte_for_byte(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            original = b'#include "types.h"\r\n\r\n' + self.PRAGMA.encode()
            source.write_bytes(original)
            candidate = automation.Candidate("func_test", "func_test", self.SOURCE, 16)

            with (
                patch.object(automation, "ROOT", root),
                patch.object(automation, "source_dirty", return_value=False),
                patch.object(
                    automation,
                    "generate_starter",
                    return_value="void func_test(void) {\n    return;\n}\n",
                ),
                patch.object(
                    automation,
                    "run_command",
                    return_value=(1, "AGENT_ACTION: CONTINUE_MISMATCH\n"),
                ),
                patch.object(automation, "entry_is_complete", return_value=False),
                redirect_stdout(io.StringIO()),
            ):
                self.assertFalse(automation.try_candidate(candidate))

            self.assertEqual(original, source.read_bytes())

    def test_exact_match_retains_only_the_function_definition(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text(self.PRAGMA, encoding="utf-8")
            candidate = automation.Candidate("func_test", "func_test", self.SOURCE, 16)
            starter = "extern s32 D_80000000;\nvoid func_test(void) {\n    return;\n}\n"

            with (
                patch.object(automation, "ROOT", root),
                patch.object(automation, "source_dirty", return_value=False),
                patch.object(automation, "generate_starter", return_value=starter),
                patch.object(automation, "run_command", return_value=(0, "")),
                redirect_stdout(io.StringIO()),
            ):
                self.assertTrue(automation.try_candidate(candidate))

            self.assertEqual(
                "void func_test(void) {\n    return;\n}\n",
                source.read_text(encoding="utf-8"),
            )


if __name__ == "__main__":
    unittest.main()
