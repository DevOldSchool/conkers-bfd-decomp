from __future__ import annotations

import importlib.util
import io
import sys
import subprocess
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "automation_common", ROOT / "scripts" / "automation_common.py"
)
assert SPEC is not None and SPEC.loader is not None
common = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = common
SPEC.loader.exec_module(common)


class AutomationCommonTests(unittest.TestCase):
    def test_interrupt_forwarding_reaps_the_public_command(self) -> None:
        # Use a separate harness so the deliberate SIGINT never reaches the
        # test runner. The child asks its parent to interrupt while reading it.
        harness = """
import os, sys
sys.path.insert(0, sys.argv[1])
import automation_common
child = 'import os,signal,time; print(os.getpid(),flush=True); time.sleep(0.05); os.kill(os.getppid(),signal.SIGINT); time.sleep(30)'
try:
    automation_common.run_command([sys.executable, '-c', child])
except KeyboardInterrupt:
    try:
        os.waitpid(-1, os.WNOHANG)
    except ChildProcessError:
        pass
    else:
        raise AssertionError('child was not reaped')
    print('clean interruption')
else:
    raise AssertionError('SIGINT was not propagated')
"""
        result = subprocess.run([sys.executable, '-c', harness, str(ROOT / 'scripts')], capture_output=True, text=True, timeout=10)
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertIn('clean interruption', result.stdout)

    def test_run_command_can_log_without_echoing(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            log = Path(temporary_directory) / "command.log"
            stdout = io.StringIO()
            with redirect_stdout(stdout):
                status, output = common.run_command(
                    [sys.executable, "-c", "print('detail')"],
                    echo=False,
                    log_path=log,
                )

            self.assertEqual(0, status)
            self.assertEqual("detail\n", output)
            self.assertEqual("", stdout.getvalue())
            logged = log.read_text(encoding="utf-8")
            self.assertIn("print", logged)
            self.assertIn("detail\n", logged)
            self.assertTrue(logged.endswith("[exit 0]\n\n"))

    def test_scheduler_interleaves_raw_and_deferred_pools(self) -> None:
        raw = [
            common.RawCandidate("raw_one", "raw_one", "one.c", 4),
            common.RawCandidate("raw_two", "raw_two", "two.c", 8),
        ]
        deferred = [
            common.DeferredCandidate("deferred_one", "three.c", 10),
            common.DeferredCandidate("deferred_two", "four.c", 20),
            common.DeferredCandidate("deferred_three", "five.c", 30),
        ]

        self.assertEqual(
            ["raw_one", "deferred_one", "raw_two", "deferred_two", "deferred_three"],
            [item.identifier for item in common.scheduled_candidates(raw, deferred)],
        )

    def test_replaces_only_canonical_pragma_and_preserves_crlf(self) -> None:
        original = (
            b'#include "types.h"\r\n\r\n'
            b'#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\r\n'
        )

        updated = common.replace_target_pragma(
            original,
            "src/game/test.c",
            "func_test",
            "void func_test(void) {\n    return;\n}\n",
        )

        self.assertEqual(
            b'#include "types.h"\r\n\r\nvoid func_test(void) {\r\n    return;\r\n}\r\n',
            updated,
        )

    def test_refuses_missing_or_duplicate_pragmas(self) -> None:
        pragma = b'#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\n'
        with self.assertRaisesRegex(common.AutomationError, "found 0"):
            common.replace_target_pragma(
                b"", "src/game/test.c", "func_test", "void func_test(void) {}\n"
            )
        with self.assertRaisesRegex(common.AutomationError, "found 2"):
            common.replace_target_pragma(
                pragma + pragma,
                "src/game/test.c",
                "func_test",
                "void func_test(void) {}\n",
            )


if __name__ == "__main__":
    unittest.main()
