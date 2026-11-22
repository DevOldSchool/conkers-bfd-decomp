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
        # fix_disabled sits in #if 0, fix_counted_once is defined in both #ifdef branches,
        # and the *_missing functions sit in branches the conditions rule out
        self.assertIn("functions with C bodies (bytes matched): 21", result.stdout)
        self.assertIn("matched under the rules:                 7", result.stdout)
        self.assertIn("MATCH-PENDING:                           14", result.stdout)

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
        self.assertNotIn("clean_sum", pending)
        self.assertNotIn("parked_offset", pending)

    def test_fake_code_forms(self):
        result = self.run_checker("--findings")
        messages = [line.split("[match] ", 1)[1] for line in result.stdout.splitlines() if " R17 [match] " in line]
        for expected in ("volatile without", "empty if block", "self-assignment", "'* 1'", "'+ 0'",
                         "do { } while ( 0 )", "bare ';' statement", "uses volatile member 'Local.state'"):
            with self.subTest(expected=expected):
                self.assertTrue(any(expected in message for message in messages), messages)

    def test_padding_is_advisory_unless_strict(self):
        self.assertIn(("pending.c", "func_80001080", "R27"), self.findings())
        strict = [row for row in self.findings("--strict-padding") if row[1] == "func_80001080"]
        self.assertNotIn("R27", {row[2] for row in strict})
        result = self.run_checker("--findings", "--strict-padding")
        self.assertIn("func_80001080: R17 [match] uses padding member 'pad1'", result.stdout)
        self.assertNotIn("func_80001080: R17 [match] uses padding member", self.run_checker("--findings").stdout)

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

    def pending(self) -> dict[str, set[str]]:
        result = self.run_checker("--pending")
        return {
            line.split()[1]: set(line.split(":", 1)[1].split())
            for line in result.stdout.splitlines() if line.startswith("MATCH-PENDING ")
        }

    def match_findings(self, function: str) -> list[str]:
        result = self.run_checker("--findings")
        return [line.split("[match] ", 1)[1] for line in result.stdout.splitlines()
                if f": {function}: " in line and " [match] " in line]

    def test_volatile_parameters_are_checked(self):
        self.assertEqual(self.pending()["fix_volatile_param"], {"R17"})

    def test_volatile_initializer_cast_is_not_hardware(self):
        self.assertEqual(self.pending()["fix_volatile_initializer"], {"R17"})

    def test_volatile_members_follow_their_struct(self):
        findings = self.match_findings("fix_volatile_member")
        self.assertEqual(len(findings), 1, findings)
        self.assertIn("'VolatileOwner.flags'", findings[0])

    def test_block_scope_externs_stay_in_their_function(self):
        pending = self.pending()
        self.assertEqual(pending["fix_block_extern"], {"R2"})
        self.assertNotIn("fix_after_block_extern", pending)

    def test_conditional_branches_are_read_once(self):
        result = self.run_checker("--advisory")
        self.assertNotIn("fix_disabled", result.stdout)
        self.assertIn("fixes.c:42: (unit): R37", result.stdout)     # the #if 0 itself, not the #else
        self.assertNotIn("fix_live_branch", self.pending())
        self.assertNotIn("fix_counted_once", self.pending())

    def test_offset_forms(self):
        findings = self.match_findings("fix_offset_forms")
        r4 = [finding for finding in findings if "offset" in finding]
        self.assertEqual(len(r4), 2, findings)     # the indexed cast and &D_x + 4, not ((u8 *)&word)[3]
        self.assertTrue(any("indexed by a constant" in finding for finding in r4), r4)
        self.assertEqual(self.pending()["fix_offset_forms"], {"R2", "R4"})

    def test_unresolved_bases_fall_back_to_the_member_name(self):
        for function in ("fix_volatile_deref", "fix_volatile_chain"):
            with self.subTest(function=function):
                findings = self.match_findings(function)
                self.assertEqual(len(findings), 1, findings)
                self.assertIn("'VolatileOwner.flags'", findings[0])
                self.assertIn("matched by member name", findings[0])

    def test_statements_are_not_declarations(self):
        # `else p = b;` and `return a;` must not hide the real declarations
        for function in ("fix_declared_after_else", "fix_declared_after_return"):
            with self.subTest(function=function):
                findings = self.match_findings(function)
                self.assertEqual(len(findings), 1, findings)
                self.assertIn("'VolatileOwner.flags'", findings[0])
                self.assertNotIn("matched by member name", findings[0])

    def test_scalar_byte_views_stay_inside_the_scalar(self):
        findings = [finding for finding in self.match_findings("fix_scalar_offsets") if "offset" in finding]
        # word + 0x20 is past an int, and gWordPtr is a pointer; ((u8 *)&word)[3] stays exempt
        self.assertEqual(len(findings), 2, findings)
        self.assertEqual(self.pending()["fix_scalar_offsets"], {"R4"})

    def test_header_macros_and_undef(self):
        result = self.run_checker("--advisory")
        self.assertNotIn("fix_header_macro_missing", result.stdout)
        self.assertNotIn("fix_after_undef_missing", result.stdout)
        pending = self.pending()
        self.assertNotIn("fix_header_macro", pending)
        self.assertNotIn("fix_after_undef", pending)

    def test_fail_on_pending(self):
        self.assertEqual(self.run_checker("--fail-on-pending").returncode, 1)


if __name__ == "__main__":
    unittest.main()
