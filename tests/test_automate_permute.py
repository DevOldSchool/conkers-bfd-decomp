#!/usr/bin/env python3
"""Tests for bounded deferred-candidate permutation automation."""

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
    "automate_permute", SCRIPTS / "automate_permute.py"
)
assert SPEC is not None and SPEC.loader is not None
automation = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = automation
SPEC.loader.exec_module(automation)


class AutomatePermuteTests(unittest.TestCase):
    SOURCE = "src/game/test.c"

    @staticmethod
    def diagnosis(
        *, registers: int = 3, operands: int = 0, opcodes: int = 0, missing: int = 0
    ) -> str:
        return (
            "func_test: CURRENT (35)\n"
            f"register-only: {registers}\n"
            f"operand-or-constant: {operands}\n"
            f"opcode-or-control-flow: {opcodes}\n"
            f"missing-or-extra: {missing}\n"
        )

    def test_accepts_only_pure_register_allocation_diagnosis(self) -> None:
        diagnosis = automation.parse_diagnosis(self.diagnosis())
        mixed = automation.parse_diagnosis(self.diagnosis(operands=1))

        self.assertTrue(diagnosis.is_register_only)
        self.assertFalse(mixed.is_register_only)

    def test_rejects_incomplete_diagnostic_evidence(self) -> None:
        with self.assertRaisesRegex(automation.AutomationError, "incomplete"):
            automation.parse_diagnosis("func_test: CURRENT (35)\nregister-only: 3\n")

    def test_non_register_candidate_is_skipped_without_permutation(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text("preserved candidate\n", encoding="utf-8")
            candidate = automation.Candidate("func_test", self.SOURCE, 35)

            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation,
                    "run_command",
                    return_value=(0, self.diagnosis(opcodes=1)),
                ) as run_command,
                redirect_stdout(io.StringIO()),
            ):
                self.assertFalse(automation.try_candidate(candidate, 20))

            self.assertEqual(1, run_command.call_count)

    def test_failed_permutation_restores_source_byte_for_byte(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            original = b"preserved candidate\r\n"
            source.write_bytes(original)
            candidate = automation.Candidate("func_test", self.SOURCE, 35)

            def run_command(arguments: list[str]) -> tuple[int, str]:
                if "diagnose-diff" in arguments:
                    return 0, self.diagnosis()
                source.write_text("unexpected active candidate\n", encoding="utf-8")
                return 1, "AGENT_ACTION: CONTINUE_MISMATCH\n"

            with (
                patch.object(automation, "ROOT", root),
                patch.object(automation, "run_command", side_effect=run_command),
                patch.object(automation, "entry_is_complete", return_value=False),
                redirect_stdout(io.StringIO()),
            ):
                self.assertFalse(automation.try_candidate(candidate, 20))

            self.assertEqual(original, source.read_bytes())

    def test_success_requires_recorded_exact_match(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text("preserved candidate\n", encoding="utf-8")
            candidate = automation.Candidate("func_test", self.SOURCE, 35)

            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation,
                    "run_command",
                    side_effect=((0, self.diagnosis()), (0, "AGENT_ACTION: STOP_MATCHED\n")),
                ),
                patch.object(automation, "entry_is_complete", return_value=True),
                redirect_stdout(io.StringIO()),
            ):
                self.assertTrue(automation.try_candidate(candidate, 20))

    def test_main_runs_one_final_batch_for_all_matches(self) -> None:
        candidates = [
            automation.Candidate("func_one", self.SOURCE, 10),
            automation.Candidate("func_two", self.SOURCE, 20),
        ]
        calls: list[list[str]] = []

        def run_command(arguments: list[str]) -> tuple[int, str]:
            calls.append(arguments)
            return 0, "AGENT_ACTION: BATCH_COMPLETE\n"

        with (
            patch.object(sys, "argv", ["automate_permute.py", "--limit", "2"]),
            patch.object(automation, "available_candidates", return_value=candidates),
            patch.object(automation, "try_candidate", return_value=True),
            patch.object(automation, "run_command", side_effect=run_command),
            redirect_stdout(io.StringIO()),
        ):
            self.assertEqual(0, automation.main())

        self.assertEqual(1, len(calls))
        self.assertEqual(
            [str(automation.ROOT / "conker"), "verify-batch", "func_one", "func_two"],
            calls[0],
        )


if __name__ == "__main__":
    unittest.main()
