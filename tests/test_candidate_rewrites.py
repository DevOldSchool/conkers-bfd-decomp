from __future__ import annotations

import importlib.util
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "candidate_rewrites", ROOT / "scripts" / "candidate_rewrites.py"
)
assert SPEC is not None and SPEC.loader is not None
rewrites = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = rewrites
SPEC.loader.exec_module(rewrites)


class CandidateRewriteTests(unittest.TestCase):
    def test_sanitizes_aligned_scalar_m2c_field(self) -> None:
        starter = """\
void func_test(void *arg0) {
    M2C_FIELD(arg0, s32, 0x18) = 1;
}
"""

        prepared = rewrites.prepare_starter(starter, "func_test", "")

        self.assertIn("*(s32 *)((u8 *)arg0 + 0x18) = 1;", prepared.definition)
        self.assertNotIn("M2C_", prepared.definition)

    def test_resolves_placeholder_declaration_before_preparing_candidate(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            target = root / "src" / "game" / "target.c"
            target.parent.mkdir(parents=True)
            target.write_text("void func_target(u8 arg0) {}\n", encoding="utf-8")
            starter = """\
M2C_UNK func_target(u8); /* extern */

void func_test(void) {
    func_target(1);
}
"""

            prepared = rewrites.prepare_starter(
                starter, "func_test", "", root=root
            )

            self.assertEqual(("void func_target(u8);",), prepared.declarations)
            self.assertEqual(("func_target: src/game/target.c",), prepared.evidence)

    def test_rejects_unproven_placeholder_declaration(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            starter = """\
M2C_UNK func_target(u8); /* extern */
void func_test(void) { func_target(1); }
"""
            with self.assertRaisesRegex(rewrites.CandidateError, "no unique"):
                rewrites.prepare_starter(
                    starter,
                    "func_test",
                    "",
                    root=Path(temporary_directory),
                )

    def test_replaces_only_unused_unknown_register_parameters(self) -> None:
        starter = """\
s32 func_test(s32 arg0, M2C_UNK arg1) {
    if (arg0 != 0) {
        return 1;
    }
    return 0;
}
"""

        prepared = rewrites.prepare_starter(starter, "func_test", "")

        self.assertIn("s32 func_test(s32 arg0, s32 arg1)", prepared.definition)

        used = "void func_test(M2C_UNK arg0) { use(arg0); }\n"
        with self.assertRaisesRegex(rewrites.CandidateError, "M2C_UNK"):
            rewrites.prepare_starter(used, "func_test", "")

    def test_generates_compound_and_commutative_forms(self) -> None:
        function = "void func_test(void) {\n    value = value | mask;\n}\n"

        variants = rewrites.rewrite_variants([function], 10)

        self.assertTrue(any("value |= mask;" in variant for variant in variants))
        self.assertTrue(any("mask | value" in variant for variant in variants))
        self.assertEqual(len(variants), len(set(variants)))

    def test_rewrite_budget_is_strict(self) -> None:
        function = "void func_test(void) { value = value | mask; }\n"
        self.assertEqual(2, len(rewrites.rewrite_variants([function], 2)))


if __name__ == "__main__":
    unittest.main()
