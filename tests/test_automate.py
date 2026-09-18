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

    def test_interrupted_raw_attempt_restores_source(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text(self.PRAGMA)
            with (
                patch.object(automation, 'ROOT', root),
                patch.object(automation.automation_common, 'generate_starter', return_value='void func_test(void) {}'),
                patch.object(automation.automation_common, 'run_command', side_effect=KeyboardInterrupt),
                redirect_stdout(io.StringIO()),
                self.assertRaises(KeyboardInterrupt),
            ):
                automation.try_raw_candidate(self.raw_candidate(), budget=20, defer_best=False)
            self.assertEqual(self.PRAGMA, source.read_text())

    def test_interrupted_first_deferred_diagnosis_restores_intrinsic_augmentation(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            original = (
                '#if 0 /* CONKER_DEFERRED_CANDIDATE func_test CURRENT (40) */\n'
                'f32 func_test(f32 value) { return sqrtf(value); }\n'
                '#endif /* CONKER_DEFERRED_CANDIDATE func_test */\n' + self.PRAGMA
            )
            source.write_text(original)
            with (
                patch.object(automation, 'ROOT', root),
                patch.object(automation.automation_common, 'run_command', side_effect=KeyboardInterrupt),
                redirect_stdout(io.StringIO()),
                self.assertRaises(KeyboardInterrupt),
            ):
                automation.try_deferred_candidate(automation.automation_common.DeferredCandidate('func_test', self.SOURCE, 40), budget=20)
            self.assertEqual(original, source.read_text())

    def test_main_interrupt_saves_retryable_coverage_and_returns_130(self) -> None:
        candidate = self.raw_candidate()
        entries = {'func_test': automation.AttemptResult('func_test', self.SOURCE, 'raw', 'not_attempted', 'eligible')}
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            report = root / 'report.json'
            output = io.StringIO()
            with (
                patch.object(automation, 'ROOT', root),
                patch.object(automation, 'initial_report_entries', return_value=entries),
                patch.object(automation.automation_common, 'available_raw_candidates', return_value=[candidate]),
                patch.object(automation.automation_common, 'available_deferred_candidates', return_value=[]),
                patch.object(automation, 'try_raw_candidate', side_effect=KeyboardInterrupt),
                redirect_stdout(output),
            ):
                status = automation.main(['--all', '--report', str(report)])
            self.assertEqual(130, status)
            payload = json.loads(report.read_text())
            self.assertFalse(payload['scan_complete'])
            self.assertFalse(payload['batch_verified'])
            self.assertEqual('not_attempted', payload['functions'][0]['outcome'])
            self.assertIn('Interrupted:', output.getvalue())

    def test_unproven_composite_is_a_preparation_blocker(self) -> None:
        result = automation.classify_attempt(automation.AttemptResult(
            'func_test', self.SOURCE, 'raw', 'skipped',
            'unresolved composite declaration in m2c context; refusing partial fields',
        ))
        self.assertEqual(('prepare', 'composite_layout'), (result.stage, result.blocker_code))

    @staticmethod
    def raw_candidate(symbol: str = "func_test") -> object:
        return automation.automation_common.RawCandidate(
            symbol, symbol, AutomateTests.SOURCE, 32
        )

    @staticmethod
    def diagnosis(*, current: int = 35, operands: int = 0) -> str:
        return (
            f"func_test: CURRENT ({current})\n"
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

    def test_analyze_requires_all_and_rejects_mutating_options(self) -> None:
        for arguments in (
            ["--analyze"],
            ["--all", "--analyze", "--defer-best"],
            ["--all", "--analyze", "--skip-final-build"],
        ):
            with (
                self.subTest(arguments=arguments),
                redirect_stdout(io.StringIO()),
                redirect_stderr(io.StringIO()),
                self.assertRaises(SystemExit),
            ):
                automation.parse_args(arguments)

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
                    return_value=(0, self.diagnosis(current=0)),
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

    def test_repairs_address_argument_with_visible_context_only_in_target(self) -> None:
        prefix = "void copy(void *, void *, s32);\n/* unrelated work */\n"
        body = "void func_test(void) {\n    s32 address;\n    s32 packet;\n    copy(address + 0x28, &packet, 12);\n}\n"
        suffix = "void other(void) { untouched(); }\n"
        source = (prefix + body + suffix).encode()
        diagnostics = automation.compiler_diagnostics(
            "cfe: Warning 712: file.c, line 6: illegal combination of pointer and integer\n"
        )
        updated, actions = automation.repair_candidate_source(source, "func_test", diagnostics)
        self.assertEqual(
            (prefix + body.replace("copy(address + 0x28", "copy((void *)(address + 0x28)") + suffix).encode(),
            updated,
        )
        self.assertTrue(actions)

    def test_raw_preflight_routes_only_eligible_differences_to_search(self) -> None:
        cases = (
            (self.diagnosis(), 250, None),
            (self.diagnosis().replace("missing-or-extra: 0", "missing-or-extra: 3"), 32, None),
            (self.diagnosis(operands=1), None, "structural_mismatch"),
            (self.diagnosis().replace("opcode-or-control-flow: 0", "opcode-or-control-flow: 1"), None, "structural_mismatch"),
            (self.diagnosis().replace("missing-or-extra: 0", "missing-or-extra: 4"), None, "structural_mismatch"),
            ("func_test: CURRENT (0)\n", None, "diagnostic_failure"),
        )
        for evidence, expected_budget, blocker in cases:
            with self.subTest(evidence=evidence), tempfile.TemporaryDirectory() as temporary_directory:
                root = Path(temporary_directory)
                source = root / self.SOURCE
                source.parent.mkdir(parents=True)
                original = "/* existing unrelated work */\n" + self.PRAGMA
                source.write_text(original)
                starter = "void func_test(void) { value += 1; }\n"
                calls = []

                def run_command(arguments):
                    calls.append(arguments)
                    if arguments[1] == "diagnose-diff":
                        return 0, evidence
                    if arguments[1] == "permute":
                        return 1, "CURRENT (35)\n"
                    raise AssertionError(arguments)

                with (
                    patch.object(automation, "ROOT", root),
                    patch.object(automation.automation_common, "generate_starter", return_value=starter),
                    patch.object(automation.automation_common, "run_command", side_effect=run_command),
                    patch.object(automation.automation_common, "entry_is_complete", return_value=False),
                    redirect_stdout(io.StringIO()),
                ):
                    result = automation.try_raw_candidate(self.raw_candidate(), budget=250, defer_best=True)
                self.assertEqual(original, source.read_text())
                self.assertEqual("diagnose-diff", calls[0][1])
                searches = [call for call in calls if call[1] == "permute"]
                if expected_budget is not None:
                    self.assertEqual(1, len(searches))
                    self.assertEqual(str(expected_budget), searches[0][searches[0].index("--budget") + 1])
                else:
                    self.assertEqual([], searches)
                    self.assertEqual(1, len(calls))
                    self.assertEqual(blocker, automation.classify_attempt(result).blocker_code)
                    self.assertIn("value += 1", (root / result.candidate_artifact).read_text())
                    self.assertEqual(evidence, (root / result.diagnostic_log).read_text())

    def test_raw_structural_candidate_restores_source_if_artifact_write_fails(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text(self.PRAGMA)
            with (
                patch.object(automation, "ROOT", root),
                patch.object(automation.automation_common, "generate_starter", return_value="void func_test(void) { value += 1; }\n"),
                patch.object(automation.automation_common, "run_command", return_value=(0, self.diagnosis(operands=1))) as run,
                patch.object(automation, "save_failure_artifacts", side_effect=OSError("disk full")),
                redirect_stdout(io.StringIO()),
                self.assertRaisesRegex(OSError, "disk full"),
            ):
                automation.try_raw_candidate(self.raw_candidate(), budget=32, defer_best=True)
            self.assertEqual(self.PRAGMA, source.read_text())
            run.assert_called_once()

    def test_unresolved_warning_is_restored_after_bounded_repairs(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text(self.PRAGMA, encoding="utf-8")
            starter = """\
void func_test(void *arg0) {
    void *temp_v0;
    temp_v0 = arg0 + 4;
}
"""
            compiler_output = (
                "cfe: Warning 712: /workspace/src/game/test.c, line 3: "
                "illegal combination of pointer and integer\n"
                "func_test: CURRENT (0)\n"
            )

            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation.automation_common,
                    "generate_starter",
                    return_value=starter,
                ),
                patch.object(
                    automation.automation_common,
                    "run_command",
                    return_value=(0, compiler_output),
                ) as run_command,
                redirect_stdout(io.StringIO()),
            ):
                result = automation.try_raw_candidate(
                    self.raw_candidate(), budget=20, defer_best=False
                )

            self.assertEqual("restored", result.outcome)
            self.assertEqual(self.PRAGMA, source.read_text(encoding="utf-8"))
            self.assertEqual(2, run_command.call_count)
            self.assertEqual("pointer_integer", result.diagnostics[0].category)
            self.assertEqual(712, result.diagnostics[0].code)
            self.assertEqual(3, result.diagnostics[0].line)
            artifact = (root / str(result.candidate_artifact)).read_text(
                encoding="utf-8"
            )
            self.assertIn("u8 *arg0", artifact)
            self.assertTrue(result.repair_actions)
            self.assertEqual(
                compiler_output + "\n" + compiler_output,
                (root / str(result.diagnostic_log)).read_text(encoding="utf-8"),
            )

    def test_warning_repair_retries_and_retains_exact_candidate(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text(self.PRAGMA, encoding="utf-8")
            starter = """\
void func_test(void *arg0) {
    void *temp_v0;
    temp_v0 = arg0 + 4;
}
"""
            compiler_output = (
                "cfe: Warning 712: /workspace/src/game/test.c, line 3: "
                "illegal combination of pointer and integer\n"
            )

            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation.automation_common,
                    "generate_starter",
                    return_value=starter,
                ),
                patch.object(
                    automation.automation_common,
                    "run_command",
                    side_effect=((1, compiler_output), (0, self.diagnosis(current=0)), (0, "done\n")),
                ) as run_command,
                redirect_stdout(io.StringIO()),
            ):
                result = automation.try_raw_candidate(
                    self.raw_candidate(), budget=20, defer_best=False
                )

            self.assertEqual("matched", result.outcome)
            self.assertEqual(3, run_command.call_count)
            self.assertEqual(
                ["diagnose-diff", "diagnose-diff", "finish"],
                [call.args[0][1] for call in run_command.call_args_list],
            )
            self.assertTrue(result.repair_actions)
            self.assertIn("u8 *arg0", source.read_text(encoding="utf-8"))

    def test_candidate_fingerprint_changes_with_source_or_assembly(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            assembly = root / "asm" / "nonmatchings" / "test" / "func_test.s"
            source.parent.mkdir(parents=True)
            assembly.parent.mkdir(parents=True)
            source.write_text(self.PRAGMA, encoding="utf-8")
            assembly.write_text("glabel func_test\n", encoding="utf-8")
            candidate = self.raw_candidate()

            with patch.object(automation, "ROOT", root):
                original = automation.candidate_fingerprint(candidate, "tool")
                source.write_text(self.PRAGMA + "\n", encoding="utf-8")
                source_changed = automation.candidate_fingerprint(candidate, "tool")
                source.write_text(self.PRAGMA, encoding="utf-8")
                assembly.write_text("glabel func_test\nnop\n", encoding="utf-8")
                assembly_changed = automation.candidate_fingerprint(candidate, "tool")

            self.assertNotEqual(original, source_changed)
            self.assertNotEqual(original, assembly_changed)

    def test_run_fingerprint_changes_with_candidate_affecting_options(self) -> None:
        baseline = automation.parse_args(["--all"])
        deeper = automation.parse_args(["--all", "--rewrite-budget", "500"])
        preserving = automation.parse_args(["--all", "--defer-best"])

        original = automation.run_fingerprint("tool", baseline)
        self.assertNotEqual(original, automation.run_fingerprint("tool", deeper))
        self.assertNotEqual(original, automation.run_fingerprint("tool", preserving))

    def test_compact_candidate_command_logs_without_echoing(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation.automation_common,
                    "run_command",
                    return_value=(0, "detail\n"),
                ) as run_command,
            ):
                self.assertEqual(
                    (0, "detail\n"),
                    automation.run_candidate_command(
                        "func_test", ["tool", "arg"], verbose=False
                    ),
                )

            run_command.assert_called_once_with(
                ["tool", "arg"],
                echo=False,
                log_path=root
                / "build"
                / "us"
                / "automate"
                / "logs"
                / "func_test.log",
            )

    def test_compact_progress_is_periodic_and_keeps_important_events(self) -> None:
        stdout = io.StringIO()
        with redirect_stdout(stdout):
            automation.emit_compact_progress(
                automation.AttemptResult(
                    "func_match", self.SOURCE, "raw", "matched", "exact", 0
                ),
                attempts=49,
                total=100,
                pending_matches=1,
            )
            automation.emit_compact_progress(
                automation.AttemptResult(
                    "func_skip", self.SOURCE, "raw", "skipped", "unsupported"
                ),
                attempts=50,
                total=100,
                pending_matches=1,
            )

        output = stdout.getvalue()
        self.assertIn("MATCH func_match", output)
        self.assertIn("PROGRESS 50/100", output)
        self.assertNotIn("func_skip", output)

    def test_progress_separates_new_matches_from_carried_pending_matches(self) -> None:
        entries = {
            "carried": automation.AttemptResult("carried", self.SOURCE, "inventory", "already_matched", "existing"),
            "fresh": automation.AttemptResult("fresh", self.SOURCE, "raw", "matched", "exact", 0),
            "better": automation.AttemptResult("better", self.SOURCE, "deferred", "deferred", "improved", 5, previous_score=20),
            "old_better": automation.AttemptResult("old_better", self.SOURCE, "deferred", "deferred", "resumed: improved", 5, previous_score=20),
        }
        counts = automation.run_progress(entries, ["carried", "fresh"])
        self.assertEqual({"new_exact_matches": 1, "carried_pending_matches": 1, "deferred_improvements": 1}, counts)
        stdout = io.StringIO()
        with redirect_stdout(stdout):
            automation.emit_compact_progress(entries["better"], attempts=50, total=100,
                                             pending_matches=2, new_matches=1, score_improvements=1)
        self.assertIn("1 new exact, 1 carried exact, 1 deferred improvement", stdout.getvalue())

    def test_exhaustive_changes_only_permutation_stage_settings(self) -> None:
        baseline = automation.stage_fingerprint_seeds(automation.parse_args(["--all"]))
        exhaustive = automation.stage_fingerprint_seeds(automation.parse_args(["--all", "--exhaustive"]))
        self.assertNotEqual(baseline.pop("permute"), exhaustive.pop("permute"))
        self.assertEqual(baseline, exhaustive)

    def test_small_register_and_missing_instruction_probe_is_bounded(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory); source = root / self.SOURCE
            source.parent.mkdir(parents=True); source.write_text("preserved candidate\n")
            candidate = automation.automation_common.DeferredCandidate("func_test", self.SOURCE, 35)
            calls = []
            def run_command(arguments, **kwargs):
                calls.append(arguments)
                if "diagnose-diff" in arguments:
                    return 0, self.diagnosis().replace("missing-or-extra: 0", "missing-or-extra: 3")
                return 1, "CURRENT (35)"
            with (patch.object(automation, "ROOT", root),
                  patch.object(automation.automation_common, "run_command", side_effect=run_command),
                  patch.object(automation.automation_common, "entry_is_complete", return_value=False),
                  redirect_stdout(io.StringIO())):
                result = automation.try_deferred_candidate(candidate, budget=250)
            search = next(call for call in calls if "permute" in call)
            self.assertEqual("32", search[search.index("--budget") + 1])
            self.assertEqual("preserved", result.outcome)

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

    def test_killed_raw_permutation_restores_source_and_does_not_block(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text(self.PRAGMA, encoding="utf-8")
            starter = "void func_test(void) {\n    value += 1;\n}\n"

            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation.automation_common,
                    "generate_starter",
                    return_value=starter,
                ),
                patch.object(
                    automation.automation_common,
                    "run_command",
                    side_effect=(
                        (0, self.diagnosis(current=40)),
                        (137, "AGENT_ACTION: BLOCKED_TOOLING\n"),
                    ),
                ),
                patch.object(
                    automation.automation_common, "entry_is_complete", return_value=False
                ),
                redirect_stdout(io.StringIO()),
            ):
                result = automation.try_raw_candidate(
                    self.raw_candidate(), budget=20, defer_best=False
                )

            self.assertEqual("skipped", result.outcome)
            self.assertIn("exit 137", result.detail)
            self.assertEqual(self.PRAGMA, source.read_text(encoding="utf-8"))

    def test_killed_raw_permutation_defers_the_measured_initial_candidate(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text(self.PRAGMA, encoding="utf-8")
            starter = "void func_test(void) {\n    value += 1;\n}\n"
            active_at_defer: list[str] = []

            def run_command(arguments: list[str]) -> tuple[int, str]:
                if "diagnose-diff" in arguments:
                    return 0, self.diagnosis(current=40)
                if "permute" in arguments:
                    return 137, "AGENT_ACTION: BLOCKED_TOOLING\n"
                if "defer" in arguments:
                    active_at_defer.append(source.read_text(encoding="utf-8"))
                    return 0, "deferred\n"
                raise AssertionError(arguments)

            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation.automation_common,
                    "generate_starter",
                    return_value=starter,
                ),
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
                result = automation.try_raw_candidate(
                    self.raw_candidate(), budget=20, defer_best=True
                )

            self.assertEqual("deferred", result.outcome)
            self.assertEqual(40, result.score)
            self.assertEqual([starter], active_at_defer)

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

    def test_missing_deferred_source_is_skipped_without_mutation(self) -> None:
        with tempfile.TemporaryDirectory() as directory, patch.object(automation, "ROOT", Path(directory)), redirect_stdout(io.StringIO()):
            result = automation.try_deferred_candidate(
                automation.automation_common.DeferredCandidate("func_test", self.SOURCE, 40), budget=20,
            )
            self.assertEqual("skipped", result.outcome)
            self.assertEqual("source file is missing", result.detail)

    def test_deferred_intrinsic_repair_is_retained_on_strict_improvement(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text(
                """\
#if 0 /* CONKER_DEFERRED_CANDIDATE func_test CURRENT (500) */
f32 func_test(f32 arg0) {
    return sqrtf(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_test */
#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")
""",
                encoding="utf-8",
            )
            candidate = automation.automation_common.DeferredCandidate(
                "func_test", self.SOURCE, 500
            )
            calls: list[list[str]] = []

            def run_command(arguments: list[str]) -> tuple[int, str]:
                calls.append(arguments)
                if "diagnose-diff" in arguments:
                    return 0, self.diagnosis(current=100, operands=1)
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
                redirect_stdout(io.StringIO()),
            ):
                result = automation.try_deferred_candidate(candidate, budget=20)

            self.assertEqual("deferred", result.outcome)
            self.assertEqual(100, result.score)
            self.assertIn("f32 sqrtf(f32);", source.read_text(encoding="utf-8"))
            self.assertIn(
                "#pragma intrinsic(sqrtf)", source.read_text(encoding="utf-8")
            )
            self.assertTrue(any("update-deferred" in call for call in calls))
            self.assertTrue(result.repair_actions)

    def exercise_deferred_compile_repair(
        self, *, repaired_score: int, permutation_score: int | None = None,
        persistent_warning: bool = False, layout_failure: bool = False,
    ) -> tuple[object, bytes, bytes, list[list[str]]]:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            original = (
                'extern s32 base;\nextern s32 index;\n'
                '#if 0 /* CONKER_DEFERRED_CANDIDATE func_test CURRENT (40) */\n'
                'void func_test(void) {\n    void *pointer;\n'
                '    pointer = base + (index * 0xA0);\n    use(pointer);\n}\n'
                '#endif /* CONKER_DEFERRED_CANDIDATE func_test */\n'
                + self.PRAGMA
            ).encode()
            source.write_bytes(original)
            calls: list[list[str]] = []
            diagnoses = 0
            completed = False

            def run_command(arguments: list[str]) -> tuple[int, str]:
                nonlocal diagnoses, completed
                calls.append(arguments)
                if 'diagnose-diff' in arguments:
                    diagnoses += 1
                    if diagnoses == 1 or persistent_warning:
                        return 0, (
                            'cfe: Warning 712: /workspace/src/game/test.c, line 5: '
                            'illegal combination of pointer and integer\n'
                            + self.diagnosis(current=40)
                        )
                    self.assertIn(b'pointer = (void *)', source.read_bytes())
                    return 0, self.diagnosis(current=repaired_score)
                if 'update-deferred' in arguments:
                    artifact = Path(arguments[arguments.index('--candidate') + 1])
                    self.assertIn('pointer = (void *)', artifact.read_text())
                    score = arguments[arguments.index('--score') + 1]
                    source.write_bytes(source.read_bytes().replace(b'CURRENT (40)', f'CURRENT ({score})'.encode()))
                    return 0, 'updated\n'
                if 'permute' in arguments:
                    self.assertIn(b'pointer = (void *)', source.read_bytes())
                    if repaired_score == 0:
                        if layout_failure:
                            return 1, 'error: source-unit layout mismatch\n'
                        completed = True
                        return 0, 'matched\n'
                    best = root / 'build/us/permute/func_test/best.c'
                    best.parent.mkdir(parents=True)
                    start, end = automation.project_state.c_function_span(source.read_text(), 'func_test')
                    best.write_text(source.read_text()[start:end])
                    score = permutation_score if permutation_score is not None else repaired_score
                    return 1, f'best CURRENT ({score})\n'
                raise AssertionError(arguments)

            with (
                patch.object(automation, 'ROOT', root),
                patch.object(automation.automation_common, 'run_command', side_effect=run_command),
                patch.object(automation.automation_common, 'entry_is_complete', side_effect=lambda _: completed),
                redirect_stdout(io.StringIO()),
            ):
                result = automation.try_deferred_candidate(
                    automation.automation_common.DeferredCandidate('func_test', self.SOURCE, 40), budget=20,
                )
            if persistent_warning:
                artifact = (root / result.candidate_artifact).read_bytes()
                self.assertIn(b'pointer = (void *)', artifact)
                self.assertLessEqual(diagnoses, automation.MAX_COMPILE_REPAIRS + 1)
            return result, original, source.read_bytes(), calls

    def test_equal_deferred_repair_can_search_but_restores_original(self) -> None:
        result, original, current, calls = self.exercise_deferred_compile_repair(repaired_score=40)
        self.assertEqual('preserved', result.outcome)
        self.assertEqual(original, current)
        self.assertTrue(any('permute' in call for call in calls))
        self.assertFalse(any('update-deferred' in call for call in calls))

    def test_deferred_repair_retains_only_a_strict_score_improvement(self) -> None:
        result, original, current, calls = self.exercise_deferred_compile_repair(repaired_score=30)
        self.assertNotEqual(original, current)
        self.assertIn(b'CURRENT (30)', current)
        self.assertTrue(any('update-deferred' in call for call in calls))
        self.assertTrue(result.repair_actions)

    def test_worse_repair_does_not_replace_a_better_canonical_candidate(self) -> None:
        result, original, current, calls = self.exercise_deferred_compile_repair(repaired_score=60, permutation_score=50)
        self.assertEqual(original, current)
        self.assertEqual(40, result.score)
        self.assertFalse(any('update-deferred' in call for call in calls))

    def test_equal_repair_can_retain_a_later_better_permutation(self) -> None:
        result, original, current, calls = self.exercise_deferred_compile_repair(repaired_score=40, permutation_score=20)
        self.assertNotEqual(original, current)
        self.assertIn(b'CURRENT (20)', current)
        self.assertEqual('deferred', result.outcome)
        self.assertEqual(20, result.score)
        self.assertTrue(any('update-deferred' in call for call in calls))

    def test_deferred_compile_repair_uses_exact_gate_and_layout_rollback(self) -> None:
        result, _, current, calls = self.exercise_deferred_compile_repair(repaired_score=0)
        self.assertEqual('matched', result.outcome)
        self.assertIn(b'pointer = (void *)', current)
        self.assertEqual('1', calls[-1][-1])
        result, original, current, _ = self.exercise_deferred_compile_repair(repaired_score=0, layout_failure=True)
        self.assertEqual(original, current)
        self.assertEqual('layout_gate', automation.classify_attempt(result).blocker_code)

    def test_persistent_deferred_warning_retains_diagnostics_and_restores_source(self) -> None:
        result, original, current, calls = self.exercise_deferred_compile_repair(repaired_score=40, persistent_warning=True)
        self.assertEqual('skipped', result.outcome)
        self.assertEqual(original, current)
        self.assertTrue(result.diagnostics)
        self.assertFalse(any('permute' in call for call in calls))

    def test_exact_deferred_candidate_runs_authoritative_recovery(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text("preserved candidate\n", encoding="utf-8")
            candidate = automation.automation_common.DeferredCandidate(
                "func_test", self.SOURCE, 0
            )

            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation.automation_common,
                    "run_command",
                    side_effect=((0, self.diagnosis(current=0)), (0, "matched\n")),
                ) as run_command,
                patch.object(
                    automation.automation_common, "entry_is_complete", return_value=True
                ),
                redirect_stdout(io.StringIO()),
            ):
                result = automation.try_deferred_candidate(candidate, budget=250)

            self.assertEqual("matched", result.outcome)
            self.assertEqual("1", run_command.call_args_list[1].args[0][-1])

    def test_exact_deferred_layout_failure_is_classified_at_finish_stage(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text("preserved candidate\n", encoding="utf-8")
            candidate = automation.automation_common.DeferredCandidate(
                "func_test", self.SOURCE, 0
            )
            layout_output = (
                "error: func_test source-unit layout mismatch: "
                "func_next offset 0xC, expected 0x14 (delta -8)\n"
                "AGENT_ACTION: CONTINUE_MISMATCH\n"
            )

            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation.automation_common,
                    "run_command",
                    side_effect=((0, self.diagnosis(current=0)), (1, layout_output)),
                ),
                patch.object(
                    automation.automation_common, "entry_is_complete", return_value=False
                ),
                redirect_stdout(io.StringIO()),
            ):
                result = automation.try_deferred_candidate(candidate, budget=250)

            classified = automation.classify_attempt(result)
            self.assertEqual("preserved", classified.outcome)
            self.assertIn("delta -8", classified.detail)
            self.assertEqual("finish", classified.stage)
            self.assertEqual("layout_gate", classified.blocker_code)

    def test_function_scope_selects_one_named_candidate(self) -> None:
        parsed = automation.parse_args(["--function", "func_test"])
        self.assertEqual("func_test", parsed.target)
        self.assertEqual(1, parsed.max_attempts)

    def test_function_scope_attempts_only_the_named_candidate(self) -> None:
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
            report = Path(temporary_directory) / "target.json"
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
                    0,
                    automation.main(
                        ["--function", "func_two", "--report", str(report)]
                    ),
                )

            self.assertEqual(["func_two"], attempted)
            payload = json.loads(report.read_text(encoding="utf-8"))
            result = next(
                item for item in payload["functions"] if item["symbol"] == "func_two"
            )
            self.assertEqual("permute", result["stage"])
            self.assertEqual("search_exhausted", result["blocker_code"])

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

    def test_killed_deferred_permutation_preserves_existing_candidate(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            original = b"preserved candidate\n"
            source.write_bytes(original)
            candidate = automation.automation_common.DeferredCandidate(
                "func_test", self.SOURCE, 35
            )

            with (
                patch.object(automation, "ROOT", root),
                patch.object(
                    automation.automation_common,
                    "run_command",
                    side_effect=((0, self.diagnosis()), (137, "killed\n")),
                ),
                patch.object(
                    automation.automation_common, "entry_is_complete", return_value=False
                ),
                redirect_stdout(io.StringIO()),
            ):
                result = automation.try_deferred_candidate(candidate, budget=20)

            self.assertEqual("preserved", result.outcome)
            self.assertIn("exit 137", result.detail)
            self.assertEqual(original, source.read_bytes())

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

    def test_analyze_all_prepares_candidates_without_source_or_compile_changes(self) -> None:
        candidate = self.raw_candidate()
        entries = {
            "func_test": automation.AttemptResult(
                "func_test", self.SOURCE, "raw", "not_attempted", "eligible"
            )
        }
        starter = "void func_test(void) {}\n"
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / self.SOURCE
            source.parent.mkdir(parents=True)
            source.write_text(self.PRAGMA, encoding="utf-8")
            report = root / "analysis.json"
            with (
                patch.object(automation, "ROOT", root),
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
                    automation.automation_common,
                    "generate_starter",
                    return_value=starter,
                ),
                patch.object(automation.automation_common, "run_command") as run_command,
                redirect_stdout(io.StringIO()),
            ):
                self.assertEqual(
                    0,
                    automation.main(
                        ["--all", "--analyze", "--report", str(report)]
                    ),
                )

            run_command.assert_not_called()
            self.assertEqual(self.PRAGMA, source.read_text(encoding="utf-8"))
            payload = json.loads(report.read_text(encoding="utf-8"))
            self.assertEqual(3, payload["schema_version"])
            self.assertEqual("analyze", payload["mode"])
            self.assertTrue(payload["scan_complete"])
            self.assertEqual(1, payload["summary"]["ready"])
            self.assertRegex(
                payload["functions"][0]["fingerprint"], r"^[0-9a-f]{64}$"
            )

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
                        "func_one",
                        self.SOURCE,
                        "raw",
                        "restored",
                        "first pass",
                        8,
                        fingerprint="stable",
                        stage="permute",
                        stage_fingerprint="stage",
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
            verbose_values: list[object] = []

            def try_candidate(candidate: object, **options: object) -> object:
                attempted.append(candidate.identifier)
                verbose_values.append(options.get("verbose"))
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
                patch.object(
                    automation, "candidate_fingerprint", return_value="stable"
                ),
                redirect_stdout(io.StringIO()),
            ):
                self.assertEqual(
                    0, automation.main(["--all", "--report", str(report)])
                )

            self.assertEqual(["func_two"], attempted)
            self.assertEqual([False], verbose_values)
            payload = json.loads(report.read_text(encoding="utf-8"))
            self.assertTrue(payload["scan_complete"])
            self.assertIn("resumed:", payload["functions"][0]["detail"])

    def test_resume_retries_an_outcome_when_its_fingerprint_changes(self) -> None:
        current = {
            "func_one": automation.AttemptResult(
                "func_one", self.SOURCE, "raw", "not_attempted", "eligible"
            )
        }
        with tempfile.TemporaryDirectory() as temporary_directory:
            report = Path(temporary_directory) / "all.json"
            automation.write_report(
                report,
                {
                    "func_one": automation.AttemptResult(
                        "func_one",
                        self.SOURCE,
                        "raw",
                        "skipped",
                        "old blocker",
                        fingerprint="old",
                    )
                },
                full_scan=True,
                scan_complete=True,
                attempts=1,
                batch_verified=True,
            )

            resumed, pending = automation.resume_report(
                report, current, {"func_one": "new"}
            )

            self.assertEqual([], pending)
            self.assertEqual("not_attempted", resumed["func_one"].outcome)

    def test_resume_reuses_only_matching_stage_fingerprint(self) -> None:
        current = {
            symbol: automation.AttemptResult(
                symbol, self.SOURCE, "raw", "not_attempted", "eligible"
            )
            for symbol in ("func_compile", "func_permute")
        }
        with tempfile.TemporaryDirectory() as temporary_directory:
            report = Path(temporary_directory) / "all.json"
            automation.write_report(
                report,
                {
                    "func_compile": automation.AttemptResult(
                        "func_compile",
                        self.SOURCE,
                        "raw",
                        "restored",
                        "warning",
                        fingerprint="compile-current",
                        stage="compile",
                    ),
                    "func_permute": automation.AttemptResult(
                        "func_permute",
                        self.SOURCE,
                        "raw",
                        "restored",
                        "mismatch",
                        fingerprint="permute-old",
                        stage="permute",
                    ),
                },
                full_scan=True,
                scan_complete=True,
                attempts=2,
                batch_verified=True,
            )

            resumed, _ = automation.resume_report(
                report,
                current,
                {
                    "func_compile": {"compile": "compile-current"},
                    "func_permute": {"permute": "permute-new"},
                },
            )

            self.assertEqual("restored", resumed["func_compile"].outcome)
            self.assertEqual("not_attempted", resumed["func_permute"].outcome)

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

    def test_resume_drops_a_pending_match_reopened_as_deferred(self) -> None:
        current = {
            "func_stale": automation.AttemptResult(
                "func_stale",
                self.SOURCE,
                "deferred",
                "not_attempted",
                "eligible deferred candidate",
            )
        }
        with tempfile.TemporaryDirectory() as temporary_directory:
            report = Path(temporary_directory) / "all.json"
            automation.write_report(
                report,
                {
                    "func_stale": automation.AttemptResult(
                        "func_stale",
                        self.SOURCE,
                        "raw",
                        "matched",
                        "exact finish gate passed",
                        0,
                    )
                },
                full_scan=True,
                scan_complete=True,
                attempts=1,
                batch_verified=False,
                pending_batch=["func_stale"],
            )

            output = io.StringIO()
            with redirect_stdout(output):
                resumed, pending = automation.resume_report(report, current)

            self.assertEqual([], pending)
            self.assertEqual("not_attempted", resumed["func_stale"].outcome)
            self.assertIn("no longer matched: func_stale", output.getvalue())

    def test_full_scan_rechecks_pending_matches_before_batch(self) -> None:
        candidate = self.raw_candidate("func_stale")
        initial = {
            "func_stale": automation.AttemptResult(
                "func_stale", self.SOURCE, "raw", "not_attempted", "eligible"
            )
        }
        reopened = {
            "func_stale": automation.AttemptResult(
                "func_stale",
                self.SOURCE,
                "deferred",
                "not_attempted",
                "reopened after integration",
            )
        }
        with tempfile.TemporaryDirectory() as temporary_directory:
            report = Path(temporary_directory) / "all.json"
            with (
                patch.object(
                    automation,
                    "initial_report_entries",
                    side_effect=(initial, reopened),
                ),
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
                        "func_stale", self.SOURCE, "raw", "matched", "exact", 0
                    ),
                ),
                patch.object(automation.automation_common, "run_command") as run_command,
                redirect_stdout(io.StringIO()),
            ):
                self.assertEqual(
                    0,
                    automation.main(["--all", "--report", str(report)]),
                )

            run_command.assert_not_called()
            payload = json.loads(report.read_text(encoding="utf-8"))
            self.assertTrue(payload["batch_verified"])
            self.assertEqual([], payload["pending_batch"])


if __name__ == "__main__":
    unittest.main()
