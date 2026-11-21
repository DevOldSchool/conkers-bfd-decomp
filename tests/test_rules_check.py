from __future__ import annotations

from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "tools/rules/rules_check.c"
FIXTURES = ROOT / "tests/fixtures/rules"
CC = shutil.which("cc") or shutil.which("gcc")


@unittest.skipUnless(CC, "requires a host C compiler")
class RulesCheckTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tempdir = tempfile.TemporaryDirectory()
        cls.binary = Path(cls.tempdir.name) / "rules_check"
        subprocess.run(
            [CC, "-std=c99", "-D_POSIX_C_SOURCE=200809L", "-O2", "-Wall", "-Werror",
             "-o", str(cls.binary), str(SOURCE)],
            check=True,
        )

    @classmethod
    def tearDownClass(cls):
        cls.tempdir.cleanup()

    def run_checker(self, *args: str) -> subprocess.CompletedProcess[str]:
        return subprocess.run(
            [str(self.binary), *args, "include", "src"],
            cwd=FIXTURES, capture_output=True, text=True, check=False,
        )

    def findings(self, *args: str) -> list[tuple[str, str, str]]:
        result = self.run_checker("--advisory", *args)
        self.assertEqual(result.returncode, 0, result.stderr)
        rows = []
        for line in result.stdout.splitlines():
            if " [match] " not in line and " [advisory] " not in line:
                continue
            location, function, rest = line.split(": ", 2)
            rows.append((Path(location.split(":")[0]).name, function, rest.split(" ", 1)[0]))
        return rows

    def test_summary_counts(self):
        result = self.run_checker()
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("functions with C bodies (bytes matched): 6", result.stdout)
        self.assertIn("matched under the rules:                 2", result.stdout)
        self.assertIn("MATCH-PENDING:                           4", result.stdout)

    def test_clean_unit_has_no_match_findings(self):
        rows = [row for row in self.findings() if row[0] == "clean.c"]
        self.assertFalse([row for row in rows if row[2] in {"R1", "R2", "R4", "R17", "R18"}], rows)
        # placeholder-free, commented functions: no R7 or R33 either
        self.assertFalse(rows, rows)

    def test_pending_rules_per_function(self):
        result = self.run_checker("--pending")
        pending = {
            line.split()[1]: set(line.split(":", 1)[1].split())
            for line in result.stdout.splitlines() if line.startswith("MATCH-PENDING ")
        }
        self.assertEqual(pending["func_80001000"], {"R2", "R4"})
        self.assertEqual(pending["func_80001040"], {"R4", "R17"})
        self.assertEqual(pending["func_80001080"], {"R1", "R17"})
        self.assertEqual(pending["func_800010C0"], {"R2", "R17"})
        self.assertNotIn("Clean_Sum", pending)
        self.assertNotIn("Parked", pending)

    def test_fake_code_forms(self):
        result = self.run_checker("--findings")
        messages = [line.split("[match] ", 1)[1] for line in result.stdout.splitlines() if " R17 [match] " in line]
        for expected in ("volatile without", "empty if block", "self-assignment", "'* 1'", "'+ 0'",
                         "do { } while ( 0 )", "bare ';' statement", "uses volatile member 'state'"):
            with self.subTest(expected=expected):
                self.assertTrue(any(expected in message for message in messages), messages)

    def test_padding_is_advisory_unless_strict(self):
        self.assertIn(("pending.c", "func_80001080", "R27"), self.findings())
        strict = [row for row in self.findings("--strict-padding") if row[1] == "func_80001080"]
        self.assertNotIn("R27", {row[2] for row in strict})

    def test_advisory_rules(self):
        rows = self.findings()
        self.assertIn(("pending.c", "func_80001000", "R7"), rows)
        self.assertIn(("pending.c", "func_80001000", "R33"), rows)
        self.assertIn(("pending.c", "func_80001080", "R35"), rows)
        self.assertIn(("pending.c", "(unit)", "R37"), rows)
        self.assertNotIn(("pending.c", "func_800010C0", "R33"), rows)

    def test_single_file_still_reads_include(self):
        result = subprocess.run(
            [str(self.binary), "--pending", "src/pending.c"],
            cwd=FIXTURES, capture_output=True, text=True, check=False,
        )
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("MATCH-PENDING func_80001080 src/pending.c: R1 R17", result.stdout)
        self.assertIn("functions with C bodies (bytes matched): 4", result.stdout)

    def test_fail_on_pending(self):
        self.assertEqual(self.run_checker("--fail-on-pending").returncode, 1)


if __name__ == "__main__":
    unittest.main()
