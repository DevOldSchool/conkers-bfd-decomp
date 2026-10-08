from __future__ import annotations

import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
import host_environment
import matching_prerequisites as readiness


class MatchingPrerequisiteTests(unittest.TestCase):
    def git(self, directory, *args):
        result = subprocess.run(
            ["git", "-c", "core.fsmonitor=false", "-c", "core.hooksPath=/dev/null",
             "-c", "user.name=Test", "-c", "user.email=test@example.invalid",
             "-C", str(directory), *args], capture_output=True, text=True, check=True,
        )
        return result.stdout.strip()

    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="ready inputs ")
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.git(self.root, "init", "-q")
        self.reference = self.root / "reference/us/asm/debugger/debugger.s"
        self.reference.parent.mkdir(parents=True)
        self.reference.write_text("glabel func_test\n")
        self.sdk = self.root / "lib/ultralib"
        self.sdk.mkdir(parents=True)
        self.git(self.sdk, "init", "-q")
        (self.sdk / "Makefile").write_text("all:\n\t@true\n")
        self.git(self.sdk, "add", "Makefile")
        self.git(self.sdk, "commit", "-qm", "fixture")
        self.pin = self.git(self.sdk, "rev-parse", "HEAD")
        self.git(self.root, "update-index", "--add", "--cacheinfo", f"160000,{self.pin},lib/ultralib")

    def test_ready_checkout_is_read_only_and_preserves_dirty_submodule(self):
        (self.sdk / "Makefile").write_text("# existing approved work\n")
        before = (self.root / ".git/index").read_bytes(), (self.sdk / "Makefile").read_bytes()
        self.assertEqual([], readiness.check(self.root))
        self.assertEqual(before, ((self.root / ".git/index").read_bytes(),
                                 (self.sdk / "Makefile").read_bytes()))

    def test_missing_and_empty_main_reference_require_supported_preparation(self):
        self.reference.unlink()
        for present in (True, False):
            if not present:
                self.reference.parent.rmdir()
                self.reference.parent.parent.rmdir()
            with self.subTest(reference_directory_exists=present):
                errors = readiness.check(self.root)
                self.assertEqual(1, len(errors))
                self.assertIn("./conker _prepare-reference --profile us", errors[0])

    def test_reference_assembly_directory_is_not_a_reference_file(self):
        self.reference.unlink()
        self.reference.mkdir()
        self.assertIn("missing or empty reference/us/asm", readiness.check(self.root)[0])

    def test_uninitialized_or_partial_sdk_is_detected_without_parent_head_fallback(self):
        metadata = self.sdk / ".git"
        metadata.rename(self.sdk / ".git.saved")
        self.assertIn("git submodule update --init --recursive lib/ultralib",
                      readiness.check(self.root)[0])
        (self.sdk / ".git.saved").rename(metadata)
        (self.sdk / "Makefile").unlink()
        self.assertIn("not initialized", readiness.check(self.root)[0])

    def test_mismatched_sdk_is_reported_without_switching_it(self):
        self.git(self.sdk, "commit", "--allow-empty", "-qm", "another SDK revision")
        actual = self.git(self.sdk, "rev-parse", "HEAD")
        errors = readiness.check(self.root)
        self.assertEqual(1, len(errors))
        self.assertIn(actual, errors[0])
        self.assertIn(self.pin, errors[0])
        self.assertEqual(actual, self.git(self.sdk, "rev-parse", "HEAD"))
        # Staging a deliberate parent pin update makes this checkout ready.
        self.git(self.root, "update-index", "--cacheinfo", f"160000,{actual},lib/ultralib")
        self.assertEqual([], readiness.check(self.root))

    def test_missing_gitlink_fails_closed(self):
        self.git(self.root, "update-index", "--force-remove", "lib/ultralib")
        self.assertIn("no single resolved gitlink", readiness.check(self.root)[0])

    def test_multiple_missing_inputs_are_reported_together(self):
        self.reference.unlink()
        (self.sdk / "Makefile").unlink()
        self.assertEqual(2, len(readiness.check(self.root)))

    def test_host_test_dependencies_do_not_gate_matching(self):
        with patch.object(host_environment, "check", return_value=["missing numpy"]) as host:
            self.assertEqual([], readiness.check(self.root))
        host.assert_not_called()

    def test_cli_reports_blocked_tooling(self):
        with patch.object(readiness, "check", return_value=["missing fixture"]), \
                patch("sys.stdout") as stdout, patch("sys.stderr") as stderr:
            self.assertEqual(2, readiness.main())
        self.assertIn("AGENT_ACTION: BLOCKED_TOOLING", "".join(call.args[0] for call in stdout.write.call_args_list))
        self.assertIn("error: missing fixture", "".join(call.args[0] for call in stderr.write.call_args_list))


if __name__ == "__main__":
    unittest.main()
