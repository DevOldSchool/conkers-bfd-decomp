from __future__ import annotations

import subprocess
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent


class DeferShellTests(unittest.TestCase):
    def run_defer(self, score: str, layout_status: int = 1, proof: bool = True):
        # Run the actual dispatch branch under Bash, including macOS Bash 3.2.
        # Fake only Docker/state boundaries; no ROM or inventory edits are needed.
        script = (ROOT / "scripts/conker.sh").read_text(encoding="utf-8")
        dispatch = "    defer)" + script.split("    defer)", 1)[1].split("        ;;", 1)[0] + "        ;;\n"
        harness = r'''set -euo pipefail
repo_root="$1"
score="$2"
fake_layout_status="$3"
fake_proof="$4"
shift 4
state_tool=state-tool
die() { printf 'error: %s\n' "$*" >&2; exit 1; }
ensure_warm_container() { :; }
python3() {
    if [[ "$2" == defer ]]; then printf '%s\0' "$@"; fi
}
run_in_warm_container() {
    if [[ "$2" == scripts/diff.py ]]; then
        printf '%s\n' "$score"
    else
        if [[ "$fake_proof" == yes ]]; then
            printf '{}\n' > "$repo_root/$6/proof.json"
        fi
        return "$fake_layout_status"
    fi
}
'''
        harness += "case defer in\n" + dispatch + "esac\n"
        with tempfile.TemporaryDirectory(prefix="defer shell ") as temporary:
            result = subprocess.run(
                ["bash", "-c", harness, "test", temporary, score,
                 str(layout_status), "yes" if proof else "no",
                 "func_test", "--reason", "frame and register mismatch"],
                text=True, capture_output=True, check=False,
            )
        return result

    def state_arguments(self, result):
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertTrue(result.stdout.endswith("\0"))
        return result.stdout[:-1].split("\0")

    def test_nonzero_score_defers_without_an_empty_optional_argument(self):
        result = self.run_defer("896")
        self.assertEqual(
            ["state-tool", "defer", "func_test", "--reason",
             "frame and register mismatch", "--score", "896"],
            self.state_arguments(result),
        )

    def test_layout_failure_preserves_proof_path_as_one_argument(self):
        result = self.run_defer("0")
        arguments = self.state_arguments(result)
        self.assertEqual(
            ["state-tool", "defer", "func_test", "--reason",
             "frame and register mismatch", "--score", "0", "--layout-failure-proof"],
            arguments[:-1],
        )
        self.assertIn("defer shell ", arguments[-1])
        self.assertTrue(arguments[-1].endswith("/proof.json"))

    def test_exact_candidate_with_passing_layout_is_not_deferred(self):
        result = self.run_defer("0", layout_status=0)
        self.assertNotEqual(0, result.returncode)
        self.assertIn("run finish instead", result.stderr)
        self.assertEqual("", result.stdout)

    def test_missing_proof_or_layout_tool_failure_never_defers(self):
        for status, proof in ((1, False), (2, True)):
            with self.subTest(status=status, proof=proof):
                result = self.run_defer("0", layout_status=status, proof=proof)
                self.assertNotEqual(0, result.returncode)
                self.assertIn("verified layout failure", result.stderr)
                self.assertEqual("", result.stdout)

    def test_invalid_score_never_defers(self):
        result = self.run_defer("not-a-score")
        self.assertNotEqual(0, result.returncode)
        self.assertIn("numeric score", result.stderr)
        self.assertEqual("", result.stdout)


if __name__ == "__main__":
    unittest.main()
