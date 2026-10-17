"""Randomized `permute --randomized` mode driven through a fake decomp-permuter."""

from __future__ import annotations

import importlib.util
import io
import json
import os
import subprocess
import sys
import tempfile
import textwrap
import unittest
from contextlib import redirect_stderr, redirect_stdout
from pathlib import Path
from unittest.mock import patch


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location("permute_randomized_helper", ROOT / "scripts" / "permute.py")
assert SPEC is not None and SPEC.loader is not None
permute_helper = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(permute_helper)

FUNCTION = (
    "void func_test(s32 *arg0) {\n"
    "    s32 value;\n"
    "    value = *arg0 | 1;\n"
    "    *arg0 = value;\n"
    "}\n"
)
SOURCE = (
    "#include \"types.h\"\n"
    "extern s32 D_80000000;\n"
    "#pragma GLOBAL_ASM(\"asm/nonmatchings/test/func_other.s\")\n"
    + FUNCTION
    + "void func_after(void) {\n    D_80000000 = 2;\n}\n"
)
# What pycparser's generator would hand back for the base (two-space indentation).
REGENERATED_CONTEXT_BEFORE = "typedef int s32;\nextern s32 D_80000000;\nvoid func_other(void);\n"
REGENERATED_CONTEXT_AFTER = "void func_after(void);\n"
REGENERATED_BASE = (
    "void func_test(s32 *arg0)\n{\n  s32 value;\n  value = (*arg0) | 1;\n  *arg0 = value;\n}\n"
)
IMPROVED = "void func_test(s32 *arg0)\n{\n  s32 value = (*arg0) | 1;\n  *arg0 = value;\n}\n"
EXACT = "void func_test(s32 *arg0)\n{\n  *arg0 = (*arg0) | 1;\n}\n"
OTHER_TEXT = "void func_test(s32 *arg0)\n{\n  *arg0 |= 1;\n}\n"

# The fake permuter reads a JSON plan from its directory: outputs to write, how
# long to run, and the exit status of the --debug base run.
FAKE_PERMUTER = textwrap.dedent(
    '''
    import json, os, random, sys, time
    directory = next(arg for arg in sys.argv[1:] if not arg.startswith("-") and arg != "1")
    plan = json.load(open(os.path.join(directory, "plan.json")))
    with open(os.path.join(directory, "invocations.log"), "a") as log:
        log.write(json.dumps({"argv": sys.argv[1:], "random": random.random(), "cwd": os.getcwd()}) + "\\n")
    if "--debug" in sys.argv:
        if plan.get("debug_status"):
            print("Unable to compile base candidate", file=sys.stderr)
            sys.exit(plan["debug_status"])
        with open(os.path.join(directory, "debug_source.c"), "w") as handle:
            handle.write(plan["regenerated_base"])
        print("[func_test] base score = %d" % plan["base_score"])
        sys.exit(0)
    for index, output in enumerate(plan["outputs"], 1):
        path = os.path.join(directory, "output-%d-%d" % (output["score"], index))
        os.mkdir(path)
        with open(os.path.join(path, "source.c"), "w") as handle:
            handle.write(output["source"])
        print("wrote to " + path)
    print("iteration %d" % plan.get("iterations", 5), end="\\r")
    try:
        time.sleep(plan.get("sleep", 0))
    except KeyboardInterrupt:
        print("\\nExiting.")
        sys.exit(0)
    '''
)


def regenerated(function: str) -> str:
    return REGENERATED_CONTEXT_BEFORE + "\n" + function + "\n" + REGENERATED_CONTEXT_AFTER


class RandomizedPermuteTests(unittest.TestCase):
    def setUp(self) -> None:
        self.temporary = tempfile.TemporaryDirectory()
        self.root = Path(self.temporary.name)
        self.permuter_root = self.root / "fake-permuter"
        self.permuter_root.mkdir()
        (self.permuter_root / "permuter.py").write_text(FAKE_PERMUTER, encoding="utf-8")
        (self.permuter_root / "strip_other_fns.py").write_text(
            "import sys\nopen(sys.argv[1] + '.stripped', 'w').write(sys.argv[2])\n", encoding="utf-8"
        )
        self.source = self.root / "src" / "game" / "test.c"
        self.source.parent.mkdir(parents=True)
        self.source.write_text(SOURCE, encoding="utf-8")
        self.reference = self.root / "reference.o"
        self.reference.write_bytes(b"independent raw reference")
        (self.root / "toolchain").mkdir()
        (self.root / "toolchain" / "tools.lock.json").write_text(
            json.dumps({"tools": {"decomp-permuter": {"revision": "abc123"}}}), encoding="utf-8"
        )
        self.directory = self.root / "build" / "us" / "permute" / "func_test"
        self.work = self.directory / "randomized"
        self.scores: dict[str, int] = {}
        self.scored: list[str] = []

    def tearDown(self) -> None:
        self.temporary.cleanup()

    def write_plan(self, outputs, *, base_score=35, debug_status=0, sleep=0, iterations=5) -> None:
        self.work.mkdir(parents=True, exist_ok=True)
        (self.work / "plan.json").write_text(json.dumps({
            "outputs": outputs, "base_score": base_score, "debug_status": debug_status,
            "sleep": sleep, "iterations": iterations, "regenerated_base": regenerated(REGENERATED_BASE),
        }), encoding="utf-8")

    def fake_score(self, profile, symbol, content, directory, reference, expected_size) -> int:
        start, end = permute_helper.candidate_function_span(content, "func_test", "func_test")
        function = content[start:end]
        self.scored.append(function)
        self.assertEqual(SOURCE[: SOURCE.index("void func_test")], content[:start])
        self.assertEqual("void func_after(void) {\n    D_80000000 = 2;\n}\n", content[end:])
        for key, score in self.scores.items():
            if key.strip() in function:
                return score
        return 35

    def run_main(self, argv, *, overlay="game", table_error=None):
        stdout, stderr = io.StringIO(), io.StringIO()
        entry = {"overlay": overlay, "regions": {"us": {"vram": "0x15000000"}}, "source": "src/game/test.c"}
        with (patch.object(permute_helper, "ROOT", self.root),
              patch.object(permute_helper, "PERMUTER_ROOT", self.permuter_root),
              patch.object(permute_helper, "work_item", return_value=(entry, "func_test")),
              patch.object(permute_helper, "active_candidate_content", return_value=(self.source, SOURCE)),
              patch.object(permute_helper, "ido_preprocess",
                           side_effect=lambda profile, focused: "# 1 \"x\"\n" + focused.read_text()),
              patch.object(permute_helper.candidate_tables, "verify_candidate", side_effect=table_error),
              patch.object(permute_helper.diff, "ensure_reference_function", return_value=self.root / "reference.s"),
              patch.object(permute_helper.diff, "reference_object", return_value=self.reference),
              patch.object(permute_helper.diff, "expected_function_size", return_value=16),
              patch.object(permute_helper, "score_candidate", side_effect=self.fake_score),
              patch.object(sys, "argv", ["permute.py", "us", "func_test", *argv]),
              redirect_stdout(stdout), redirect_stderr(stderr)):
            status = permute_helper.main()
        self.output = stdout.getvalue() + stderr.getvalue()
        self.assertEqual(SOURCE, self.source.read_text(encoding="utf-8"))
        report = json.loads((self.directory / "search-report.json").read_text(encoding="utf-8"))
        return status, report

    def invocations(self) -> list[dict]:
        return [json.loads(line) for line in (self.work / "invocations.log").read_text().splitlines()]

    def test_exact_output_is_restyled_and_saved_after_rejecting_other_text(self) -> None:
        # Outputs are rescored in the permuter's own score order (12, 15, 20, 30),
        # not in the order the permuter wrote them.
        self.write_plan([
            {"score": 20, "source": regenerated(IMPROVED)},
            {"score": 15, "source": REGENERATED_CONTEXT_BEFORE + "extern s32 D_80000004;\n" + OTHER_TEXT
                                    + REGENERATED_CONTEXT_AFTER},
            {"score": 30, "source": regenerated(EXACT)},
            {"score": 12, "source": regenerated(IMPROVED)},
        ])
        self.scores = {"s32 value = (*arg0) | 1;": 10, "*arg0 = (*arg0) | 1;": 0}

        status, report = self.run_main(["--randomized", "--seconds", "30", "--seed", "7"])

        self.assertEqual(0, status, self.output)
        self.assertEqual("exact", report["stop_reason"])
        self.assertEqual("randomized", report["strategy"])
        self.assertEqual((7, True, 30), (report["seed"], report["seed_given"], report["seconds"]))
        self.assertEqual((35, 0, 35), (report["baseline_score"], report["best_score"], report["permuter_base_score"]))
        self.assertEqual((4, 1, 2), (report["permuter_outputs"], report["rejected_context"], report["improvements"]))
        self.assertEqual(4, report["compiled"])
        self.assertEqual("abc123", report["permuter_revision"])
        self.assertEqual(5, report["permuter_iterations"])
        self.assertEqual(
            "void func_test(s32 *arg0)\n{\n    *arg0 = (*arg0) | 1;\n}\n",
            (self.directory / "best.c").read_text(encoding="utf-8"),
        )
        # Baseline, then the three accepted outputs; the other-text output is never compiled.
        self.assertEqual(4, len(self.scored))
        self.assertIn("rejected output-15-2; it changes text outside func_test", self.output)
        self.assertIn("exact randomized permutation saved to build/us/permute/func_test/best.c", self.output)

        # The permuter directory holds the documented inputs and the scoring work.
        self.assertEqual("func_test\n", (self.work / "function.txt").read_text())
        self.assertIn('compiler_type = "ido"', (self.work / "settings.toml").read_text())
        self.assertEqual(b"independent raw reference", (self.work / "target.o").read_bytes())
        self.assertNotIn("GLOBAL_ASM", (self.work / "base.c").read_text())
        self.assertNotIn("# 1 \"x\"", (self.work / "base.c").read_text())
        self.assertEqual("func_test", (self.work / "base.c.stripped").read_text())
        compile_script = (self.work / "compile.sh").read_text()
        self.assertTrue(os.access(self.work / "compile.sh", os.X_OK))
        self.assertIn("/opt/ido/cc -c -32 -G 0", compile_script)
        self.assertIn("-O2 -g3 -mips2 \"$@\"", compile_script)
        debug, search = self.invocations()
        self.assertEqual([str(self.work), "--debug", "--stack-diffs"], debug["argv"])
        self.assertEqual([str(self.work), "--stop-on-zero", "--better-only", "--stack-diffs", "-j", "1"],
                         search["argv"])
        self.assertEqual(self.work.resolve(), Path(debug["cwd"]).resolve())

    def test_seeded_runs_are_reproducible_and_reused_until_the_seed_changes(self) -> None:
        self.write_plan([{"score": 20, "source": regenerated(IMPROVED)}])
        self.scores = {"s32 value = (*arg0) | 1;": 10}

        status, report = self.run_main(["--randomized", "--seconds", "5", "--seed", "3"])
        self.assertEqual((1, "permuter_exit", 10), (status, report["stop_reason"], report["best_score"]))
        self.assertIn("no exact match in 1 permuter output(s) (permuter_exit, seed 3)", self.output)
        first = self.invocations()
        self.assertEqual(2, len(first))
        self.assertEqual(first[0]["random"], first[1]["random"])

        status, report = self.run_main(["--randomized", "--seconds", "5", "--seed", "3"])
        self.assertEqual(1, status)
        self.assertIn("unchanged search skipped", self.output)
        self.assertEqual(2, len(self.invocations()))

        status, report = self.run_main(["--randomized", "--seconds", "5", "--seed", "4"])
        self.assertEqual(1, status)
        self.assertNotIn("unchanged search skipped", self.output)
        self.assertEqual(4, len(self.invocations()))
        self.assertNotEqual(first[0]["random"], self.invocations()[2]["random"])

    def test_unseeded_runs_draw_and_record_a_seed_and_never_reuse(self) -> None:
        self.write_plan([])
        seeds = []
        for _ in range(2):
            status, report = self.run_main(["--randomized", "--seconds", "5"])
            self.assertEqual((1, "permuter_exit", 35, 0), (status, report["stop_reason"], report["best_score"],
                                                            report["improvements"]))
            self.assertFalse(report["seed_given"])
            seeds.append(report["seed"])
        self.assertNotIn("unchanged search skipped", self.output)
        self.assertEqual(4, len(self.invocations()))
        self.assertTrue(all(isinstance(seed, int) for seed in seeds))
        self.assertEqual(FUNCTION, (self.directory / "best.c").read_text(encoding="utf-8"))

    def test_time_limit_interrupts_the_permuter_and_keeps_its_outputs(self) -> None:
        self.write_plan([{"score": 20, "source": regenerated(IMPROVED)}], sleep=60)
        self.scores = {"s32 value = (*arg0) | 1;": 10}

        status, report = self.run_main(["--randomized", "--seconds", "1", "--seed", "1"])

        self.assertEqual((1, "time_limit", 10, 1), (status, report["stop_reason"], report["best_score"],
                                                    report["improvements"]))
        self.assertEqual(0, report["permuter_exit"])
        self.assertLess(report["permuter_elapsed_seconds"], 20)
        self.assertIn("Exiting.", (self.work / "permuter.log").read_text())

    def test_permuter_base_failure_is_a_tooling_failure_with_evidence(self) -> None:
        self.write_plan([], debug_status=1)

        status, report = self.run_main(["--randomized", "--seconds", "5", "--seed", "1"])

        self.assertEqual((2, "tooling_failure", 35), (status, report["stop_reason"], report["best_score"]))
        self.assertIn("could not score the base candidate", report["error"])
        self.assertIn("permuter-base.log", report["error"])
        self.assertIn("Unable to compile base candidate", (self.work / "permuter-base.log").read_text())
        self.assertEqual(1, len(self.invocations()))
        self.assertEqual(FUNCTION, (self.directory / "best.c").read_text(encoding="utf-8"))

    def test_invalid_outputs_are_skipped_and_table_failures_stop(self) -> None:
        self.write_plan([{"score": 20, "source": regenerated(IMPROVED)},
                         {"score": 30, "source": regenerated(EXACT)}])
        self.scores = {"s32 value = (*arg0) | 1;": subprocess.CalledProcessError(1, "cc"),
                       "*arg0 = (*arg0) | 1;": 0}
        original = self.fake_score

        def scoring(*arguments):
            result = original(*arguments)
            if isinstance(result, Exception):
                raise result
            return result

        with patch.object(self, "fake_score", scoring):
            status, report = self.run_main(["--randomized", "--seconds", "5", "--seed", "1"],
                                           table_error=ValueError("case target differs"))
        self.assertEqual((2, "table_gate_failure", 1, 35), (status, report["stop_reason"], report["invalid"],
                                                          report["best_score"]))
        self.assertIn("candidate table gate: case target differs", report["error"])

    def test_randomized_flags_are_validated(self) -> None:
        for argv in (["--randomized", "--stack-shapes"], ["--randomized", "--exhaustive"],
                     ["--seconds", "5"], ["--seed", "1"], ["--randomized", "--seconds", "0"],
                     ["--randomized", "--seed", "-1"]):
            with self.subTest(argv=argv), patch.object(sys, "argv", ["permute.py", "us", "func_test", *argv]), \
                    redirect_stderr(io.StringIO()), self.assertRaises(SystemExit) as raised:
                permute_helper.main()
            self.assertEqual(2, raised.exception.code)

    def test_regenerated_base_without_the_function_is_a_tooling_failure(self) -> None:
        self.write_plan([])
        (self.work / "plan.json").write_text(json.dumps({
            "outputs": [], "base_score": 1, "debug_status": 0, "sleep": 0,
            "regenerated_base": "void func_other(void);\n",
        }), encoding="utf-8")
        status, report = self.run_main(["--randomized", "--seconds", "5", "--seed", "1"])
        self.assertEqual((2, "tooling_failure"), (status, report["stop_reason"]))
        self.assertIn("func_test", report["error"])


class RandomizedShellDispatchTests(unittest.TestCase):
    def run_permute(self, status: int):
        script = (ROOT / "scripts/conker.sh").read_text(encoding="utf-8")
        dispatch = "    permute)" + script.split("    permute)", 1)[1].split("        ;;", 1)[0] + "        ;;\n"
        harness = r'''set -euo pipefail
repo_root=/repo
state_tool=state-tool
search_status="$1"
shift
die() { printf 'error: %s\n' "$*" >&2; exit 1; }
ensure_warm_container() { :; }
python3() { printf 'host:%s\n' "$*"; }
run_in_warm_container() { printf 'container:%s\n' "$*"; return "$search_status"; }
'''
        harness += "case permute in\n" + dispatch + "esac\n"
        return subprocess.run(["bash", "-c", harness, "test", str(status), "func_test",
                               "--randomized", "--seconds", "120", "--seed", "9"],
                              text=True, capture_output=True, check=False)

    def test_randomized_flags_pass_through_to_the_container_search(self) -> None:
        result = self.run_permute(1)
        self.assertEqual(1, result.returncode, result.stderr)
        self.assertEqual(
            ["host:state-tool setup-check --profile us",
             "container:python3 scripts/permute.py us func_test --randomized --seconds 120 --seed 9",
             "AGENT_ACTION: CONTINUE_MISMATCH"],
            result.stdout.splitlines(),
        )

    def test_exact_randomized_result_uses_the_transactional_apply_path(self) -> None:
        result = self.run_permute(0)
        lines = result.stdout.splitlines()
        self.assertIn("host:state-tool apply-permutation func_test --candidate build/us/permute/func_test/best.c",
                      lines)


if __name__ == "__main__":
    unittest.main()
