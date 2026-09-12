from __future__ import annotations

import importlib.util
import io
import json
import subprocess
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
                if "s32 second;" in variant and "s32 first;" in variant
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

    def test_lifetimes_are_not_starved_by_six_local_permutations(self) -> None:
        function = (
            "s32 func_test(void) {\n"
            + "".join(f"    s32 {name};\n" for name in "abcdef")
            + "\n"
            + "".join(f"    {name} = 1;\n" for name in "abcdef")
            + "    return a + b + c + d + e + f;\n}\n"
        )
        variants = permute_helper.source_variants(function, 250)
        self.assertTrue(any("s32 a = 1;" in v for v in variants[:5]))
        self.assertTrue(any("s32 f = 1;" in v for v in variants))
        self.assertLessEqual(len(variants), 250)
        self.assertEqual(len(variants), len(set(variants)))

    def test_pointer_and_project_typedef_declarations_participate(self) -> None:
        function = (
            "void func_test(GameState *arg0) {\n"
            "    GameCallback callback;\n"
            "    s32 *pointer;\n"
            "    s32 index;\n\n"
            "    callback = arg0->callback;\n"
            "    pointer = arg0->pointer;\n"
            "    index = 1;\n"
            "    callback(pointer, index);\n}\n"
        )
        variants = permute_helper.declaration_variants(function, 30)
        self.assertTrue(any("GameCallback callback = arg0->callback;" in v for v in variants))
        self.assertTrue(any("s32 * pointer = arg0->pointer;" in v or "s32 *pointer = arg0->pointer;" in v for v in variants))

    def test_lifetime_does_not_move_into_branch_or_self_initialization(self) -> None:
        for statement in (
            "    if (flag) {\n        value = 1;\n    }",
            "    if (flag)\n        value = 1;",
            "    value = value + 1;",
        ):
            function = "s32 func_test(s32 flag) {\n    s32 value;\n" + statement + "\n    return value;\n}\n"
            self.assertEqual([function], permute_helper.declaration_variants(function, 20))

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

    def test_tight_scopes_split_writes_and_disjoint_reuse(self) -> None:
        function = ("s32 func_test(s32 input) {\n"
                    "    s32 first;\n    s32 second;\n    s32 result;\n"
                    "    first = input + 1;\n    result = first * 2;\n"
                    "    second = input - 1;\n    second = second + 3;\n"
                    "    return result + second;\n}\n")
        variants = permute_helper.declaration_variants(function, 40)
        self.assertTrue(any("first_split" not in v and "second_split0 = second + 3" in v for v in variants))
        self.assertTrue(any("s32 second;" not in v and "first = input - 1" in v for v in variants))
        self.assertTrue(any("result = first * 2;\n    }" in v for v in variants))

    def test_new_lifetime_rules_reject_escaped_addresses_and_control_flow(self) -> None:
        from candidate_lifetimes import lifetime_variants
        for body in ("value = input; consume(&value); return value;",
                     "value = input; consume(&((value))); return value;",
                     "value = input; if (input) { value = 3; } return value;",
                     "value = input; goto end; end: return value;",
                     "value = input; while (input--) value++; return value;"):
            function = "s32 func_test(s32 input) {\n    s32 value;\n    " + body + "\n}\n"
            declarations = list(permute_helper.DECLARATION.finditer(function))
            self.assertEqual([], list(lifetime_variants(function, declarations)))

    def run_search(self, scores, *, exhaustive=False):
        function = "s32 func_test(void) { return 1; }\n"
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            variants = [function.replace("1", str(i + 1)) for i in range(len(scores))]
            argv = ["permute.py", "us", "func_test", "--budget", str(len(scores))]
            if exhaustive:
                argv.append("--exhaustive")
            with (patch.object(permute_helper, "ROOT", root),
                  patch.object(permute_helper, "work_item", return_value=({}, "func_test")),
                  patch.object(permute_helper, "active_candidate_content", return_value=(root / "test.c", function)),
                  patch.object(permute_helper, "source_variants", return_value=variants),
                  patch.object(permute_helper.diff, "ensure_reference_function", return_value=root / "reference.s"),
                  patch.object(permute_helper.diff, "reference_object", return_value=root / "reference.o"),
                  patch.object(permute_helper, "score_candidate", side_effect=scores) as scorer,
                  patch.object(sys, "argv", argv), redirect_stdout(io.StringIO())):
                status = permute_helper.main()
            output = root / "build/us/permute/func_test"
            return status, scorer.call_count, json.loads((output / "search-report.json").read_text())

    def test_plateau_stops_at_32_and_exhaustive_preserves_full_budget(self) -> None:
        status, calls, report = self.run_search([10] * 80)
        self.assertEqual((1, 32, "plateau"), (status, calls, report["stop_reason"]))
        status, calls, report = self.run_search([10] * 80, exhaustive=True)
        self.assertEqual((1, 80, "variants_exhausted"), (status, calls, report["stop_reason"]))

    def test_improvement_extends_search_until_later_exact_variant(self) -> None:
        status, calls, report = self.run_search([10] * 23 + [5] * 16 + [0] + [3] * 40)
        self.assertEqual((0, 40, 0), (status, calls, report["best_score"]))
        self.assertEqual("exact", report["stop_reason"])

    def test_invalid_variants_also_consume_the_plateau_budget(self) -> None:
        status, calls, report = self.run_search([subprocess.CalledProcessError(1, "compiler")] * 80)
        self.assertEqual((1, 32, 32), (status, calls, report["invalid"]))
        self.assertIsNone(report["best_score"])

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
