from __future__ import annotations

import io
import subprocess
import sys
import unittest
from contextlib import redirect_stdout
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
import attempt_history
import project_state


class NextSelectionTests(unittest.TestCase):
    def setUp(self) -> None:
        self.functions = [
            {
                "symbol": symbol,
                "source": source,
                "overlay": "game",
                "regions": {"us": {
                    "state": "raw_asm", "symbol": symbol,
                    "vram": "0x15000000", "size_bytes": size,
                }},
            }
            for symbol, source, size in (
                ("func_a", "src/game/a.c", 4),
                ("func_a_sibling", "src/game/a.c", 8),
                ("func_b", "src/game/b.c", 12),
                ("func_similar", "src/game/a.c.extra", 16),
            )
        ]
        for target, name, value in (
            (project_state, "validate_project", ({}, self.functions)),
            (project_state, "load_json", {}),
            (project_state, "validate_source_units", []),
            (attempt_history, "load", {}),
        ):
            patcher = patch.object(target, name, return_value=value)
            patcher.start()
            self.addCleanup(patcher.stop)

    def args(self, *options: str):
        with patch.object(sys, "argv", ["project_state.py", "next", *options]):
            return project_state.parse_args()

    def select(self, *options: str) -> str:
        output = io.StringIO()
        with redirect_stdout(output):
            project_state.next_function(self.args(*options))
        return output.getvalue()

    def test_default_output_and_first_selection_are_unchanged(self) -> None:
        self.assertEqual(
            "# Start any listed work item with:\n"
            "# ./conker m2c <work-item-id> > /tmp/<work-item-id>.c\n"
            + "".join(
                f"{entry['symbol']} ({entry['source']}; us={entry['symbol']}; "
                f"size={entry['regions']['us']['size_bytes']} bytes)\n"
                for entry in self.functions
            ),
            self.select(),
        )
        self.assertEqual("func_a\n", self.select("--one", "--id-only"))

    def test_repeatable_exclusions_select_disjoint_source_families(self) -> None:
        self.assertEqual("func_a\n", self.select("--one", "--id-only"))
        self.assertEqual("func_b\n", self.select(
            "--one", "--id-only", "--exclude-source", "src/game/a.c",
        ))
        self.assertEqual("func_similar\n", self.select(
            "--one", "--id-only", "--exclude-source", "src/game/a.c",
            "--exclude-source", "src/game/b.c",
        ))

    def test_exclusions_match_only_exact_inventory_source_paths(self) -> None:
        for value in ("src/game", "src/game/", "src/game/a", "src/game/a.c*",
                      "a.c", "./src/game/a.c", "src/game/a.c.extra"):
            with self.subTest(value=value):
                self.assertEqual("func_a\n", self.select(
                    "--one", "--id-only", "--exclude-source", value,
                ))

    def test_exclusions_require_bounded_selection(self) -> None:
        with self.assertRaisesRegex(project_state.ProjectStateError, "requires --one"):
            self.select("--exclude-source", "src/game/a.c")
        project_state.validate_project.assert_not_called()

    def test_empty_filtered_selection_fails_without_context(self) -> None:
        for mode in ("--details", "--id-only"):
            with self.subTest(mode=mode), patch.object(project_state, "print_next_details") as details:
                with self.assertRaisesRegex(project_state.ProjectStateError, "after source exclusions"):
                    self.select("--one", mode,
                                "--exclude-source", "src/game/a.c",
                                "--exclude-source", "src/game/b.c",
                                "--exclude-source", "src/game/a.c.extra")
                details.assert_not_called()
        attempt_history.load.assert_not_called()

    def test_exclusions_preserve_eligibility_and_full_context(self) -> None:
        for state, extra in (
            ("matched", {}), ("candidate", {}), ("blocked", {}),
            ("raw_asm", {"deferred": {"reason": "previous attempt"}}),
            ("raw_asm", {"issue": "https://example.invalid/issues/1"}),
        ):
            entry = dict(self.functions[2], **extra)
            entry["regions"] = {"us": dict(entry["regions"]["us"], state=state)}
            self.functions.insert(0, entry)
        with patch.object(project_state, "print_next_details") as details:
            self.select("--one", "--details", "--exclude-source", "src/game/a.c")
        details.assert_called_once_with(self.functions[-2], 12, self.functions, [])

    def test_exclusions_do_not_hide_validation_or_missing_sizes(self) -> None:
        project_state.validate_project.side_effect = project_state.ProjectStateError("invalid inventory")
        with self.assertRaisesRegex(project_state.ProjectStateError, "invalid inventory"):
            self.select("--one", "--exclude-source", "src/game/a.c")
        project_state.validate_project.side_effect = None
        del self.functions[0]["regions"]["us"]["size_bytes"]
        with self.assertRaisesRegex(project_state.ProjectStateError, "cannot determine function size for: func_a"):
            self.select("--one", "--exclude-source", "src/game/a.c")

    def test_exclusions_preserve_attempt_freshness_and_fail_closed(self) -> None:
        import automate
        import call_signatures
        attempt_history.load.return_value = {"functions": [{
            "symbol": "func_b", "stage": "test", "outcome": "skipped",
            "pool": "raw", "fingerprint": "unchanged",
        }]}
        with (
            patch.object(automate, "stage_fingerprint_seeds", return_value={"test": "seed"}),
            patch.object(automate, "candidate_fingerprint", return_value="unchanged") as fingerprint,
            patch.object(call_signatures, "signature_index", return_value={}),
            patch.object(automate.declaration_facts, "object_evidence_index", return_value={}),
        ):
            self.assertEqual("func_similar\n", self.select(
                "--one", "--id-only", "--exclude-source", "src/game/a.c",
            ))
            self.assertEqual("func_b", fingerprint.call_args.args[0].c_symbol)
            with self.assertRaisesRegex(project_state.ProjectStateError, "no fresh raw candidates"):
                self.select("--one", "--details", "--exclude-source", "src/game/a.c",
                            "--exclude-source", "src/game/a.c.extra")


class ReadySelectionShellTests(unittest.TestCase):
    def run_ready(self, *options: str, selection_status: int = 0):
        # Execute the real dispatcher and preparation function with fake toolchain
        # boundaries; no ROM, Docker, or compiler is needed for argument/gate tests.
        script = (ROOT / "scripts/conker.sh").read_text(encoding="utf-8")
        prepare = "prepare_next_work() {" + script.split("prepare_next_work() {", 1)[1].split("\n}", 1)[0] + "\n}\n"
        dispatch = "    next)" + script.split("    next)", 1)[1].split("        ;;", 1)[0] + "        ;;\n"
        harness = '''set -euo pipefail
state_tool=state-tool
warm_container_name=test
die() { printf 'error: %s\\n' "$*" >&2; exit 1; }
python3() {
    printf 'state:' >&2
    printf ' <%s>' "$@" >&2
    printf '\\n' >&2
    if [[ "$2" == next ]]; then
        if [[ "$selection_status" != 0 ]]; then return "$selection_status"; fi
        printf 'work-item: func_b\\nallowed-edit: src/game/b.c\\n'
    fi
}
ensure_warm_container() { printf 'prewarm\\n' >&2; }
run_host_mips_to_c() { printf 'starter:' >&2; printf ' <%s>' "$@" >&2; printf '\\n' >&2; }
'''
        harness += f"selection_status={selection_status}\n" + prepare + 'case next in\n' + dispatch + 'esac\n'
        return subprocess.run(["bash", "-c", harness, "test", "--ready", *options],
                              text=True, capture_output=True, check=False)

    def test_ready_default_and_repeatable_paths_keep_context_and_toolchain_order(self) -> None:
        for options, suffix in (
            ((), ""),
            (("--exclude-source", "src/game/a.c", "--exclude-source", "src/game/with space.c"),
             " <--exclude-source> <src/game/a.c> <--exclude-source> <src/game/with space.c>"),
        ):
            with self.subTest(options=options):
                result = self.run_ready(*options)
                self.assertEqual(0, result.returncode, result.stderr)
                self.assertEqual([
                    "state: <state-tool> <next> <--one> <--details>" + suffix,
                    "state: <state-tool> <setup-check> <--profile> <us>",
                    "prewarm",
                    "starter: <us> <func_b> <--auto-overlay> <--ready-output>",
                ], result.stderr.splitlines())
                self.assertEqual("work-item: func_b\nallowed-edit: src/game/b.c\ntoolchain: warm (test)\n", result.stdout)

    def test_ready_rejects_missing_paths_or_output_mode_changes(self) -> None:
        for options in (("--exclude-source",), ("--id-only",), ("--one",),
                        ("--exclude-source", "src/game/a.c", "--details")):
            with self.subTest(options=options):
                result = self.run_ready(*options)
                self.assertNotEqual(0, result.returncode)
                self.assertIn("usage:", result.stderr)
                self.assertNotIn("state:", result.stderr)
                self.assertEqual("", result.stdout)

    def test_ready_selection_failure_never_prewarms_or_generates_starter(self) -> None:
        result = self.run_ready("--exclude-source", "src/game/a.c", selection_status=1)
        self.assertEqual(1, result.returncode)
        self.assertEqual("", result.stdout)
        self.assertNotIn("setup-check", result.stderr)
        self.assertNotIn("prewarm", result.stderr)
        self.assertNotIn("starter:", result.stderr)


if __name__ == "__main__":
    unittest.main()
