from __future__ import annotations

import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent


class MatchingShellTests(unittest.TestCase):
    def test_finish_wrapper_and_existing_gate_actions(self):
        script = (ROOT / "scripts/conker.sh").read_text()
        dispatch = "    finish)" + script.split("    finish)", 1)[1].split("        ;;", 1)[0] + "        ;;\n"
        with tempfile.TemporaryDirectory() as directory:
            shim = Path(directory) / "python3"
            shim.write_text('#!/bin/sh\nif [ "$2" = record ]; then printf "%s\\n" "$@"; fi\n')
            shim.chmod(0o755)
            harness = '''set -euo pipefail
repo_root=/fixture
state_tool=state-tool
parse_profile_and_value() { selected_profile=us; selected_value=func_test; }
verify_and_record_match() { return "$gate_status"; }
git() { return 0; }
'''
            for active, status, expected in (
                (False, 0, "scripts/matching_history.py\nrecord\nfunc_test\n"),
                (True, 1, "AGENT_ACTION: CONTINUE_MISMATCH\n"),
                (True, 2, "AGENT_ACTION: FIX_COMPILE\n"),
                (True, 3, "AGENT_ACTION: BLOCKED_TOOLING\n"),
                (True, 0, "AGENT_ACTION: STOP_MATCHED\n"),
            ):
                with self.subTest(active=active, status=status):
                    env = dict(os.environ, PATH=directory + os.pathsep + os.environ["PATH"])
                    env.pop("CONKER_MATCHING_RECORD_ACTIVE", None)
                    if active:
                        env["CONKER_MATCHING_RECORD_ACTIVE"] = "1"
                    result = subprocess.run(["bash", "-c", harness + f"gate_status={status}\n"
                                             + "case finish in\n" + dispatch + "esac\n"],
                                            env=env, capture_output=True, text=True)
                    self.assertEqual(status if active else 0, result.returncode, result.stderr)
                    self.assertTrue(result.stdout.endswith(expected), result.stdout)

    def test_batch_test_tmpdir_is_resolved_and_preserves_spaces(self):
        script = (ROOT / "scripts/conker.sh").read_text()
        assignment = next(line.strip() for line in script.splitlines() if line.strip().startswith("host_test_tmpdir="))
        command = next(line.strip()[:-len(" || status=$?")]
                       for line in script.splitlines() if line.strip().startswith("TMPDIR=\"$host_test_tmpdir\" "))
        with tempfile.TemporaryDirectory() as directory:
            actual = Path(directory) / "actual path"
            actual.mkdir()
            alias = Path(directory) / "alias path"
            alias.symlink_to(actual, target_is_directory=True)
            # Execute the real -c normalization; replace only the test-suite boundary.
            harness = '''set -euo pipefail
python3() {
  if [[ "$1" == -c ]]; then "$actual_python" "$@";
  else printf '%s\\n' "$TMPDIR"; fi
}
'''
            result = subprocess.run(["bash", "-c", harness + assignment + "\n" + command],
                                    env=dict(os.environ, TMPDIR=str(alias), actual_python=sys.executable),
                                    capture_output=True, text=True)
            self.assertEqual(0, result.returncode, result.stderr)
            self.assertEqual(str(actual.resolve()) + "\n", result.stdout)


if __name__ == "__main__":
    unittest.main()
