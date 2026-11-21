from __future__ import annotations

from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
TOOLS = ROOT / "tools/rules"
FIXTURES = ROOT / "tests/fixtures/hoist"
CC = shutil.which("cc") or shutil.which("gcc")


@unittest.skipUnless(CC, "requires a host C compiler")
class HoistExternsTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tempdir = tempfile.TemporaryDirectory()
        cls.bin = Path(cls.tempdir.name) / "bin"
        cls.bin.mkdir()
        for tool in ("rules_check", "hoist_externs"):
            subprocess.run(
                [CC, "-std=c99", "-D_POSIX_C_SOURCE=200809L", "-O2", "-Wall", "-Werror",
                 "-o", str(cls.bin / tool), str(TOOLS / f"{tool}.c")],
                check=True,
            )

    @classmethod
    def tearDownClass(cls):
        cls.tempdir.cleanup()

    def setUp(self):
        self.work = Path(tempfile.mkdtemp(dir=self.tempdir.name))
        shutil.copytree(FIXTURES / "include", self.work / "include")
        shutil.copytree(FIXTURES / "src", self.work / "src")

    def hoist(self, *args: str) -> str:
        listing = subprocess.run(
            [str(self.bin / "rules_check"), "--list-globals"],
            cwd=self.work, capture_output=True, text=True, check=True,
        ).stdout
        (self.work / "globals.tsv").write_text(listing)
        return subprocess.run(
            [str(self.bin / "hoist_externs"), *args, "globals.tsv"],
            cwd=self.work, capture_output=True, text=True, check=True,
        ).stdout

    def read(self, path: str) -> str:
        return (self.work / path).read_text()

    def test_dry_run_changes_nothing(self):
        report = self.hoist()
        self.assertIn("dry run: 5 globals declared in include/globals.h", report)
        self.assertFalse((self.work / "include/globals.h").exists())
        self.assertEqual(self.read("src/first.c"), (FIXTURES / "src/first.c").read_text())

    def test_apply_moves_agreeing_globals(self):
        report = self.hoist("--apply")
        self.assertIn("applied: 5 globals declared in include/globals.h", report)
        header = self.read("include/globals.h")
        for line in ("extern s32 D_80000010;", "extern f32 D_80000020[];",
                     "extern s32 (*D_80000070)(s32);", "extern s32 D_80000080;"):
            self.assertIn(line, header)
        # a unit-private type, type conflicts and a macro alias stay local
        for name in ("D_80000040", "D_80000050", "D_80000090", "D_800000A0", "gAlias"):
            self.assertNotIn(name, header)

    def test_bounds_agree_and_header_takes_the_bound(self):
        self.hoist("--apply")
        self.assertIn("extern Shared D_80000060[4];", self.read("include/globals.h"))
        self.assertNotIn("D_80000060", self.read("src/second.c").split("f32 Second_Read")[0])

    def test_units_are_rewritten(self):
        self.hoist("--apply")
        first = self.read("src/first.c")
        self.assertIn('#include "types.h"\n#include "globals.h"\n', first)
        self.assertNotIn("extern s32 D_80000010;", first)
        self.assertNotIn("extern s32 D_80000080;", first)            # block scope
        self.assertIn("s32 First_Read(void) {\n    return", first)      # no blank line left behind
        # the multi-name line keeps only the global that stays
        self.assertIn("extern f32 D_80000090;", first)
        self.assertNotIn("D_80000020", first)
        for kept in ("extern Local D_80000040;", "extern u8 D_80000050;", "extern u8 gAlias;"):
            self.assertIn(kept, first)
        second = self.read("src/second.c")
        self.assertIn("extern s8 D_80000050;", second)
        self.assertIn("extern s32 D_80000090;", second)
        self.assertNotIn("extern s32 D_80000080;", second)

    def test_storage_units_are_left_alone(self):
        report = self.hoist("--apply")
        self.assertIn("left alone: 1 units that define their own storage", report)
        self.assertEqual(self.read("src/storage.c"), (FIXTURES / "src/storage.c").read_text())

    def test_second_run_is_a_no_op(self):
        self.hoist("--apply")
        first = self.read("src/first.c")
        header = self.read("include/globals.h")
        report = self.hoist("--apply")
        self.assertIn("0 declarations removed from 0 units", report)
        self.assertEqual(self.read("src/first.c"), first)
        self.assertEqual(self.read("include/globals.h"), header)

    def test_checker_sees_fewer_r2_findings(self):
        def r2_findings() -> list[str]:
            out = subprocess.run(
                [str(self.bin / "rules_check"), "--findings"],
                cwd=self.work, capture_output=True, text=True, check=True,
            ).stdout
            return [line for line in out.splitlines() if " R2 [match] " in line]

        before = r2_findings()
        self.hoist("--apply")
        after = r2_findings()
        self.assertLess(len(after), len(before))
        moved = [line for line in after if "D_80000010" in line]
        self.assertEqual([line.split(":")[0] for line in moved], ["src/storage.c"])

    def unify(self, *args: str) -> list[list[str]]:
        self.hoist()                                    # writes globals.tsv only
        out = subprocess.run(
            [str(self.bin / "hoist_externs"), "--unify", *args, "globals.tsv"],
            cwd=self.work, capture_output=True, text=True, check=True,
        ).stdout
        return [line.split("\t") for line in out.splitlines()]

    def test_unify_plans_one_declaration_per_conflict(self):
        rows = self.unify()
        retyped = {(row[1], row[2]): row[4] for row in rows if row[0] == "U"}
        # equal rank and equal use: the first variant seen wins
        self.assertEqual(retyped[("src/second.c", "D_80000050")], "u8 D_80000050")
        self.assertEqual(retyped[("src/second.c", "D_80000090")], "f32 D_80000090")
        self.assertEqual(self.read("src/second.c"), (FIXTURES / "src/second.c").read_text())   # dry run

    def test_unify_choice_picks_the_next_candidate(self):
        rows = self.unify("--choice", "1")
        retyped = {(row[1], row[2]): row[4] for row in rows if row[0] == "U"}
        self.assertEqual(retyped[("src/first.c", "D_80000050")], "s8 D_80000050")

    def test_unify_never_drops_information(self):
        second = self.work / "src/second.c"
        second.write_text(second.read_text().replace("extern s8 D_80000050;", "extern Shared D_80000050;"))
        # the named type is the only candidate that keeps every declaration's information
        rows = self.unify()
        retyped = {(row[1], row[2]): row[4] for row in rows if row[0] == "U"}
        self.assertEqual(retyped[("src/first.c", "D_80000050")], "Shared D_80000050")
        self.assertNotIn(("src/second.c", "D_80000050"), retyped)
        rows = self.unify("--choice", "1")
        self.assertIn(["S", "D_80000050", "no candidate left"], rows)

    def test_unify_apply_rewrites_minority_units(self):
        (self.work / "only.txt").write_text("D_80000050\t1\n")
        self.unify("--apply", "--only", "only.txt")
        self.assertIn("extern s8 D_80000050;", self.read("src/first.c"))
        self.assertIn("extern f32 D_80000020[], D_80000090;", self.read("src/first.c"))   # untouched line
        report = self.hoist("--apply")
        self.assertIn("applied: 6 globals declared", report)
        self.assertIn("extern s8 D_80000050;", self.read("include/globals.h"))


if __name__ == "__main__":
    unittest.main()
