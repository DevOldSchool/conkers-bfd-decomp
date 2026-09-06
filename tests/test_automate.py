from __future__ import annotations

import importlib.util
import io
import json
import sys
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout
from pathlib import Path
from unittest.mock import patch


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "automate", ROOT / "scripts" / "automate.py"
)
assert SPEC is not None and SPEC.loader is not None
automation = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = automation
SPEC.loader.exec_module(automation)


class AutomateTests(unittest.TestCase):
    SOURCE = "src/game/test.c"
    PRAGMA = '#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\n'

    @staticmethod
    def raw_candidate(symbol: str = "func_test") -> object:
        return automation.automation_common.RawCandidate(
            symbol, symbol, AutomateTests.SOURCE, 32
        )

    @staticmethod
    def diagnosis(*, operands: int = 0) -> str:
        return (
            "func_test: CURRENT (35)\n"
            "register-only: 3\n"
            f"operand-or-constant: {operands}\n"
            "opcode-or-control-flow: 0\n"
            "missing-or-extra: 0\n"
        )

    def test_all_rejects_attempt_limit(self) -> None:
        with (
            redirect_stdout(io.StringIO()),
            redirect_stderr(io.StringIO()),
            self.assertRaises(SystemExit),
        ):
            automation.parse_args(["--all", "--max-attempts", "2"])

    def test_restart_requires_all(self) -> None:
        with (
            redirect_stdout(io.StringIO()),
            redirect_stderr(io.StringIO()),
            self.assertRaises(SystemExit),
        ):
            automation.parse_args(["--restart"])

    def test_exact_sanitized_raw_candidate_is_retained(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text(self.PRAGMA, encoding="utf-8")
            starter = """\
void func_test(void *arg0) {
    M2C_FIELD(arg0, s32, 0x18) = 1;
}
"""

            with (
                patch.object(automation, "ROOT", root),
                patch.object(automation.automation_common, "ROOT", root),
                patch.object(
                    automation.automation_common,
                    "generate_starter",
                    return_value=starter,
                ),
                patch.object(
                    automation.automation_common,
                    "run_command",
                    return_value=(0, "CURRENT (0)\n"),
                ),
                redirect_stdout(io.StringIO()),
            ):
                result = automation.try_raw_candidate(
                    self.raw_candidate(), budget=20, defer_best=False
                )

            self.assertEqual("matched", result.outcome)
            self.assertIn(
                "*(s32 *)((u8 *)arg0 + 0x18) = 1;",
                source.read_text(encoding="utf-8"),
            )

    def test_unproven_declaration_skips_without_changing_source(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text(self.PRAGMA, encoding="utf-8")
            starter = """\
M2C_UNK func_missing(u8); /* extern */
void func_test(void) { func_missing(1); }
"""

            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation.automation_common,
                    "generate_starter",
                    return_value=starter,
                ),
                redirect_stdout(io.StringIO()),
            ):
                result = automation.try_raw_candidate(
                    self.raw_candidate(), budget=20, defer_best=True
                )

            self.assertEqual("skipped", result.outcome)
            self.assertEqual(self.PRAGMA, source.read_text(encoding="utf-8"))

    def test_non_register_deferred_candidate_is_not_permuted(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text("preserved candidate\n", encoding="utf-8")
            candidate = automation.automation_common.DeferredCandidate(
                "func_test", self.SOURCE, 35
            )

            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation.automation_common,
                    "run_command",
                    return_value=(0, self.diagnosis(operands=1)),
                ) as run_command,
                redirect_stdout(io.StringIO()),
            ):
                result = automation.try_deferred_candidate(candidate, budget=20)

            self.assertEqual("skipped", result.outcome)
            self.assertEqual(1, run_command.call_count)

    def test_improved_deferred_candidate_updates_canonical_block(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text("preserved candidate\n", encoding="utf-8")
            best = root / "build" / "us" / "permute" / "func_test" / "best.c"
            best.parent.mkdir(parents=True)
            best.write_text("void func_test(void) {}\n", encoding="utf-8")
            candidate = automation.automation_common.DeferredCandidate(
                "func_test", self.SOURCE, 35
            )
            calls: list[list[str]] = []

            def run_command(arguments: list[str]) -> tuple[int, str]:
                calls.append(arguments)
                if "diagnose-diff" in arguments:
                    return 0, self.diagnosis()
                if "permute" in arguments:
                    return 1, "func_test: no exact match; best CURRENT (10)\n"
                if "update-deferred" in arguments:
                    return 0, "updated\n"
                raise AssertionError(arguments)

            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation.automation_common,
                    "run_command",
                    side_effect=run_command,
                ),
                patch.object(
                    automation.automation_common, "entry_is_complete", return_value=False
                ),
                redirect_stdout(io.StringIO()),
            ):
                result = automation.try_deferred_candidate(candidate, budget=20)

            self.assertEqual("deferred", result.outcome)
            self.assertEqual(10, result.score)
            self.assertIn("update-deferred", calls[-1])
            self.assertIn(str(best), calls[-1])

    def test_equal_deferred_candidate_is_reported_as_preserved(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text("preserved candidate\n", encoding="utf-8")
            candidate = automation.automation_common.DeferredCandidate(
                "func_test", self.SOURCE, 35
            )

            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation.automation_common,
                    "run_command",
                    side_effect=(
                        (0, self.diagnosis()),
                        (1, "func_test: no exact match; best CURRENT (35)\n"),
                    ),
                ),
                patch.object(
                    automation.automation_common, "entry_is_complete", return_value=False
                ),
                redirect_stdout(io.StringIO()),
            ):
                result = automation.try_deferred_candidate(candidate, budget=20)

            self.assertEqual("preserved", result.outcome)
            self.assertEqual(35, result.score)

    def test_bounded_run_uses_one_final_batch_and_writes_report(self) -> None:
        candidate = self.raw_candidate()
        calls: list[list[str]] = []
        entries = {
            "func_test": automation.AttemptResult(
                "func_test", self.SOURCE, "raw", "not_attempted", "eligible"
            )
        }

        def run_command(arguments: list[str]) -> tuple[int, str]:
            calls.append(arguments)
            return 0, "AGENT_ACTION: BATCH_COMPLETE\n"

        with tempfile.TemporaryDirectory() as temporary_directory:
            report = Path(temporary_directory) / "report.json"
            with (
                patch.object(automation, "initial_report_entries", return_value=entries),
                patch.object(
                    automation.automation_common,
                    "available_raw_candidates",
                    return_value=[candidate],
                ),
                patch.object(
                    automation.automation_common,
                    "available_deferred_candidates",
                    return_value=[],
                ),
                patch.object(
                    automation,
                    "try_raw_candidate",
                    return_value=automation.AttemptResult(
                        "func_test", self.SOURCE, "raw", "matched", "exact", 0
                    ),
                ),
                patch.object(
                    automation.automation_common,
                    "run_command",
                    side_effect=run_command,
                ),
                redirect_stdout(io.StringIO()),
            ):
                self.assertEqual(
                    0,
                    automation.main(["--limit", "1", "--report", str(report)]),
                )

            self.assertEqual(
                [[str(automation.ROOT / "conker"), "verify-batch", "func_test"]],
                calls,
            )
            payload = json.loads(report.read_text(encoding="utf-8"))
            self.assertTrue(payload["batch_verified"])
            self.assertEqual(1, payload["summary"]["matched"])

    def test_all_processes_every_scheduled_candidate_without_running_full_build(self) -> None:
        candidates = [self.raw_candidate("func_one"), self.raw_candidate("func_two")]
        entries = {
            candidate.identifier: automation.AttemptResult(
                candidate.identifier,
                candidate.source,
                "raw",
                "not_attempted",
                "eligible",
            )
            for candidate in candidates
        }
        attempted: list[str] = []

        def try_candidate(candidate: object, **_: object) -> object:
            attempted.append(candidate.identifier)
            return automation.AttemptResult(
                candidate.identifier,
                candidate.source,
                "raw",
                "restored",
                "no exact match",
                12,
            )

        with tempfile.TemporaryDirectory() as temporary_directory:
            report = Path(temporary_directory) / "all.json"
            with (
                patch.object(automation, "initial_report_entries", return_value=entries),
                patch.object(
                    automation.automation_common,
                    "available_raw_candidates",
                    return_value=candidates,
                ),
                patch.object(
                    automation.automation_common,
                    "available_deferred_candidates",
                    return_value=[],
                ),
                patch.object(automation, "try_raw_candidate", side_effect=try_candidate),
                patch.object(automation.automation_common, "run_command") as run_command,
                redirect_stdout(io.StringIO()),
            ):
                self.assertEqual(
                    0,
                    automation.main(
                        ["--all", "--skip-final-build", "--report", str(report)]
                    ),
                )

            run_command.assert_not_called()
            self.assertEqual(["func_one", "func_two"], attempted)
            payload = json.loads(report.read_text(encoding="utf-8"))
            self.assertTrue(payload["full_scan"])
            self.assertTrue(payload["scan_complete"])
            self.assertNotIn("not_attempted", payload["summary"])

    def test_all_resumes_completed_attempts_from_report(self) -> None:
        candidates = [self.raw_candidate("func_one"), self.raw_candidate("func_two")]
        entries = {
            candidate.identifier: automation.AttemptResult(
                candidate.identifier,
                candidate.source,
                "raw",
                "not_attempted",
                "eligible",
            )
            for candidate in candidates
        }
        with tempfile.TemporaryDirectory() as temporary_directory:
            report = Path(temporary_directory) / "all.json"
            automation.write_report(
                report,
                {
                    "func_one": automation.AttemptResult(
                        "func_one", self.SOURCE, "raw", "restored", "first pass", 8
                    ),
                    "func_two": entries["func_two"],
                },
                full_scan=True,
                scan_complete=False,
                attempts=1,
                batch_verified=False,
                pending_batch=[],
            )
            attempted: list[str] = []

            def try_candidate(candidate: object, **_: object) -> object:
                attempted.append(candidate.identifier)
                return automation.AttemptResult(
                    candidate.identifier,
                    candidate.source,
                    "raw",
                    "restored",
                    "second pass",
                    4,
                )

            with (
                patch.object(automation, "initial_report_entries", return_value=entries),
                patch.object(
                    automation.automation_common,
                    "available_raw_candidates",
                    return_value=candidates,
                ),
                patch.object(
                    automation.automation_common,
                    "available_deferred_candidates",
                    return_value=[],
                ),
                patch.object(automation, "try_raw_candidate", side_effect=try_candidate),
                redirect_stdout(io.StringIO()),
            ):
                self.assertEqual(
                    0, automation.main(["--all", "--report", str(report)])
                )

            self.assertEqual(["func_two"], attempted)
            payload = json.loads(report.read_text(encoding="utf-8"))
            self.assertTrue(payload["scan_complete"])
            self.assertIn("resumed:", payload["functions"][0]["detail"])

    def test_all_resumes_an_unverified_batch(self) -> None:
        entries = {
            "func_one": automation.AttemptResult(
                "func_one", self.SOURCE, "inventory", "already_matched", "exact"
            )
        }
        with tempfile.TemporaryDirectory() as temporary_directory:
            report = Path(temporary_directory) / "all.json"
            automation.write_report(
                report,
                entries,
                full_scan=True,
                scan_complete=False,
                attempts=1,
                batch_verified=False,
                pending_batch=["func_one"],
            )
            calls: list[list[str]] = []

            def run_command(arguments: list[str]) -> tuple[int, str]:
                calls.append(arguments)
                return 0, "AGENT_ACTION: BATCH_COMPLETE\n"

            with (
                patch.object(automation, "initial_report_entries", return_value=entries),
                patch.object(
                    automation.automation_common,
                    "available_raw_candidates",
                    return_value=[],
                ),
                patch.object(
                    automation.automation_common,
                    "available_deferred_candidates",
                    return_value=[],
                ),
                patch.object(
                    automation.automation_common,
                    "run_command",
                    side_effect=run_command,
                ),
                redirect_stdout(io.StringIO()),
            ):
                self.assertEqual(0, automation.main(["--all", "--report", str(report)]))

            self.assertEqual(
                [[str(automation.ROOT / "conker"), "verify-batch", "func_one"]], calls
            )
            payload = json.loads(report.read_text(encoding="utf-8"))
            self.assertTrue(payload["batch_verified"])
            self.assertEqual([], payload["pending_batch"])


if __name__ == "__main__":
    unittest.main()
