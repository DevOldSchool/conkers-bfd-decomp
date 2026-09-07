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
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "permute_helper", ROOT / "scripts" / "permute.py"
)
assert SPEC is not None and SPEC.loader is not None
permute_helper = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(permute_helper)


class PermuteTests(unittest.TestCase):
    def test_generates_declaration_order_and_lifetime_variants(self) -> None:
        function = (
            "void func_test(s32 arg0) {\n"
            "    s32 first;\n"
            "    s32 second;\n"
            "\n"
            "    first = arg0 | 1;\n"
            "    second = first & ~4;\n"
            "}\n"
        )

        variants = permute_helper.declaration_variants(function, 20)

        self.assertEqual(function, variants[0])
        self.assertTrue(
            any(
                variant.index("s32 second;") < variant.index("s32 first;")
                for variant in variants
            )
        )
        self.assertTrue(
            any("s32 first = arg0 | 1;" in variant for variant in variants)
        )
        self.assertEqual(len(variants), len(set(variants)))

    def test_budget_bounds_generated_variants(self) -> None:
        function = (
            "void func_test(void) {\n"
            "    s32 a;\n"
            "    s32 b;\n"
            "    s32 c;\n"
            "\n"
            "    a = 1;\n"
            "    b = 2;\n"
            "    c = 3;\n"
            "}\n"
        )

        self.assertEqual(3, len(permute_helper.declaration_variants(function, 3)))

    def test_source_variants_include_expression_and_assignment_forms(self) -> None:
        function = (
            "void func_test(void) {\n"
            "    value = value | mask;\n"
            "}\n"
        )

        variants = permute_helper.source_variants(function, 10)

        self.assertTrue(any("value |= mask;" in variant for variant in variants))
        self.assertTrue(any("mask | value" in variant for variant in variants))
        self.assertLessEqual(len(variants), 10)

    def test_improved_best_is_persisted_before_a_later_process_failure(self) -> None:
        function = "void func_test(void) {\n    value = value | mask;\n}\n"
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "src" / "game" / "test.c"
            source.parent.mkdir(parents=True)
            source.write_text(function, encoding="utf-8")
            with (
                patch.object(permute_helper, "ROOT", root),
                patch.object(
                    permute_helper, "work_item", return_value=({}, "func_test")
                ),
                patch.object(
                    permute_helper,
                    "active_candidate_content",
                    return_value=(source, function),
                ),
                patch.object(
                    permute_helper.diff,
                    "ensure_reference_function",
                    return_value=root / "reference.s",
                ),
                patch.object(
                    permute_helper.diff,
                    "reference_object",
                    return_value=root / "reference.o",
                ),
                patch.object(
                    permute_helper,
                    "score_candidate",
                    side_effect=(20, RuntimeError("killed")),
                ),
                patch.object(
                    sys,
                    "argv",
                    ["permute.py", "us", "func_test", "--budget", "2"],
                ),
                redirect_stdout(io.StringIO()),
                self.assertRaisesRegex(RuntimeError, "killed"),
            ):
                permute_helper.main()

            best = root / "build" / "us" / "permute" / "func_test" / "best.c"
            self.assertEqual(function, best.read_text(encoding="utf-8"))


if __name__ == "__main__":
    unittest.main()
