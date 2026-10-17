from __future__ import annotations

from contextlib import redirect_stdout
import io
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import siblings


ROOT = Path(__file__).resolve().parent.parent


def block(symbol: str, lines: list[str]) -> str:
    body = "".join(f"    /* 0 15000000 00000000 */  {line}\n" for line in lines)
    return f"glabel {symbol}\n{body}endlabel {symbol}\n"


TARGET = ["addiu $sp, $sp, -0x18", "sw $ra, 0x14($sp)", "lui $t6, %hi(D_80041E58)",
          "lw $v0, %lo(D_80041E58)($t6)", "jal func_10023790", "nop",
          "beqz $v0, .L15000030", "nop", "lw $ra, 0x14($sp)", "jr $ra",
          "addiu $sp, $sp, 0x18"]
# Same symbols/labels renamed: a level-0 twin.
EXACT = [line.replace("D_80041E58", "D_80041EA0").replace("func_10023790", "func_10008570")
         .replace(".L15000030", ".L15000130") for line in TARGET]
# Registers renamed: a level-1 twin only.
REGISTERS = [line.replace("$t6", "$t7").replace("$v0", "$v1") for line in TARGET]
# Immediates changed: a level-2 twin only.
IMMEDIATES = [line.replace("0x14", "0x1C").replace("0x18", "0x20") for line in TARGET]
OTHER = ["jr $ra", "nop"]


class SiblingsTests(unittest.TestCase):
    def setUp(self) -> None:
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        patcher = patch.object(siblings, "ROOT", self.root)
        patcher.start()
        self.addCleanup(patcher.stop)
        self.write("reference/game/us/asm/a.s",
                   ".section .text\n\n" + block("func_15000000", TARGET)
                   + block("func_15000100", EXACT) + block("func_15000200", REGISTERS))
        self.write("reference/game/us/asm/b.s",
                   block("func_15000300", IMMEDIATES) + block("func_15000400", OTHER)
                   + block("func_15000500", TARGET)
                   + "dlabel D_15000600\n    /* 0 15000600 3C013F80 */ .word 0x3C013F80\n")
        self.write("reference/us/asm/c.s", block("func_80000000", TARGET))
        self.functions = {
            "func_15000000": ("raw_asm", "src/game/a.c", {"current_score": 12}),
            "func_15000100": ("matched", "src/game/a.c", None),
            "func_15000200": ("matched", "src/game/b.c", None),
            "func_15000300": ("matched", "src/game/b.c", None),
            "func_15000400": ("raw_asm", "src/game/b.c", None),
            "func_15000500": ("raw_asm", "src/game/b.c", None),
            "func_80000000": ("matched", "src/done/main/c.c", None),
        }
        self.write_inventory()
        self.write("src/game/a.c",
                   "#pragma GLOBAL_ASM(\"asm/nonmatchings/a/func_15000000.s\")\n\n"
                   "void func_15000100(void *arg0) {\n    helper(arg0);\n}\n")
        self.write("src/game/b.c",
                   "void func_15000200(void *arg0) {\n    other(arg0);\n}\n"
                   "void func_15000300(void *arg0) {\n    third(arg0);\n}\n")
        self.write("src/done/main/c.c",
                   "#define main_alias func_80000000\n"
                   "void main_alias(void *arg0) {\n    main_body(arg0);\n}\n")

    def write(self, name: str, text: str) -> Path:
        path = self.root / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")
        return path

    def write_inventory(self) -> None:
        entries = []
        for symbol, (state, source, deferred) in self.functions.items():
            entry = {"symbol": symbol, "source": source,
                     "overlay": "main" if symbol.startswith("func_8") else "game",
                     "regions": {"us": {"symbol": symbol, "state": state,
                                        "vram": "0x" + symbol[5:]}}}
            if deferred:
                entry["deferred"] = deferred
            entries.append(entry)
        self.write("progress/functions.json",
                   json.dumps({"schema_version": 1, "functions": entries}))

    def run_main(self, *argv: str) -> tuple[int, str]:
        output = io.StringIO()
        with redirect_stdout(output):
            status = siblings.main(list(argv))
        return status, output.getvalue()

    def test_normalisation_levels_strip_progressively(self) -> None:
        arguments = "$t6, %lo(D_80041E58)($t6)"
        self.assertEqual("$t6, REL($t6)", siblings.normalize_arguments(arguments, 0))
        self.assertEqual("R, REL(R)", siblings.normalize_arguments(arguments, 1))
        self.assertEqual("R, REL(R)", siblings.normalize_arguments(arguments, 2))
        self.assertEqual("SYM", siblings.normalize_arguments("func_10023790", 0))
        self.assertEqual("L", siblings.normalize_arguments(".L15000030", 0))
        self.assertEqual("SYM", siblings.normalize_arguments("jtbl_15001234_game", 0))
        self.assertEqual("$a0, $zero, -0x28", siblings.normalize_arguments("$a0, $zero, -0x28", 0))
        self.assertEqual("R, R, N", siblings.normalize_arguments("$a0, $zero, -0x28", 2))
        self.assertEqual("R, N(R)", siblings.normalize_arguments("$t6, 12($sp)", 2))
        # Named symbols other than func_/D_/jtbl_ stay meaningful at every level.
        self.assertEqual("osInvalDCache", siblings.normalize_arguments("osInvalDCache", 2))
        with self.assertRaises(siblings.SiblingsError):
            siblings.normalize_arguments("", 3)

    def test_parser_keeps_only_instructions_inside_function_labels(self) -> None:
        text = (self.root / "reference/game/us/asm/b.s").read_text(encoding="utf-8")
        functions = siblings.parse_reference_text(text)
        self.assertEqual({"func_15000300", "func_15000400", "func_15000500"}, set(functions))
        self.assertEqual([("jr", "$ra"), ("nop", "")], functions["func_15000400"])
        self.assertEqual(len(TARGET), len(functions["func_15000500"]))

    def test_index_is_cached_by_reference_mtime_and_rebuilt_when_stale(self) -> None:
        index = siblings.load_index(0)
        self.assertEqual({"func_15000000", "func_15000100", "func_15000200", "func_15000300",
                          "func_15000400", "func_15000500", "func_80000000"}, set(index))
        self.assertEqual(index["func_15000000"]["digest"], index["func_15000100"]["digest"])
        self.assertEqual(index["func_15000000"]["digest"], index["func_80000000"]["digest"])
        self.assertNotEqual(index["func_15000000"]["digest"], index["func_15000200"]["digest"])
        self.assertEqual("reference/us/asm/c.s", index["func_80000000"]["file"])
        self.assertEqual("main", index["func_80000000"]["overlay"])
        for level in siblings.LEVELS:
            self.assertTrue((self.root / "build/reference-index" / f"siblings-{level}.json").is_file())
        with patch.object(siblings, "scan_reference",
                          side_effect=AssertionError("index was not reused")):
            self.assertEqual(index, siblings.load_index(0))
        level1 = siblings.load_index(1)
        self.assertEqual(level1["func_15000000"]["digest"], level1["func_15000200"]["digest"])
        self.assertNotEqual(level1["func_15000000"]["digest"], level1["func_15000300"]["digest"])
        level2 = siblings.load_index(2)
        self.assertEqual(level2["func_15000000"]["digest"], level2["func_15000300"]["digest"])
        self.assertNotEqual(level2["func_15000000"]["digest"], level2["func_15000400"]["digest"])

        cache = self.root / "build/reference-index/siblings-0.json"
        data = json.loads(cache.read_text(encoding="utf-8"))
        data["assembly_roots_mtime_ns"]["reference/game/us/asm"] -= 1
        cache.write_text(json.dumps(data), encoding="utf-8")
        with patch.object(siblings, "scan_reference", wraps=siblings.scan_reference) as scan:
            siblings.load_index(0)
        self.assertEqual(1, scan.call_count)

    def test_duplicate_labels_never_establish_a_twin(self) -> None:
        self.write("reference/game/us/asm/dup.s", block("func_15000100", OTHER))
        index = siblings.load_index(0, refresh=True)
        self.assertTrue(index["func_15000100"]["ambiguous"])
        inventory = siblings.load_inventory()
        grouped = siblings.groups(index)
        self.assertEqual(["func_80000000"],
                         siblings.matched_twins("func_15000000", index, grouped, inventory))

    def test_lowest_level_matched_twin_is_reported_with_body_and_differences(self) -> None:
        status, output = self.run_main("func_15000000")
        self.assertEqual(0, status, output)
        self.assertIn("state: deferred (CURRENT 12)\n", output)
        self.assertIn(f"instructions: {len(TARGET)} (reference/game/us/asm/a.s)\n", output)
        self.assertIn("sibling-twin: level 0 func_15000100 func_80000000\n", output)
        self.assertIn("unmatched-twins: level 0 func_15000500(raw_asm)\n", output)
        self.assertIn("twin: func_15000100\ntwin-us-symbol: func_15000100\ntwin-overlay: game\n"
                      "twin-source: src/game/a.c\n", output)
        self.assertIn("instruction-count-diff: 0\nlevel-0-differences: 0\n", output)
        self.assertIn("twin-body:\nvoid func_15000100(void *arg0) {\n    helper(arg0);\n}\n", output)
        # The main twin's definition hides behind a profile alias macro.
        self.assertIn("twin-source: src/done/main/c.c\n", output)
        self.assertIn("twin-body:\nvoid main_alias(void *arg0) {\n    main_body(arg0);\n}\n", output)

    def test_level_limit_and_twin_limit_bound_the_report(self) -> None:
        self.functions["func_15000100"] = ("raw_asm", "src/game/a.c", None)
        self.functions["func_80000000"] = ("raw_asm", "src/done/main/c.c", None)
        self.write_inventory()
        status, output = self.run_main("func_15000000", "--level", "0")
        self.assertEqual(1, status)
        self.assertIn("sibling-twin: none (levels 0-0)\n", output)
        self.assertNotIn("twin-body", output)

        status, output = self.run_main("func_15000000", "--level", "1")
        self.assertEqual(0, status)
        self.assertIn("sibling-twin: level 1 func_15000200\n", output)
        self.assertIn("level-0-differences: 3\n", output)
        self.assertIn("     2: lui $t6, REL | lui $t7, REL\n", output)
        self.assertIn("twin-body:\nvoid func_15000200(void *arg0) {\n    other(arg0);\n}\n", output)

        self.functions["func_15000100"] = ("matched", "src/game/a.c", None)
        self.functions["func_80000000"] = ("matched", "src/done/main/c.c", None)
        self.write_inventory()
        status, output = self.run_main("func_15000000", "--level", "0", "--limit", "1")
        self.assertEqual(0, status)
        self.assertIn("sibling-twin: level 0 func_15000100 func_80000000\n", output)
        self.assertEqual(1, output.count("twin-body:"))
        self.assertIn("... (1 more twins; raise --limit)\n", output)

    def test_missing_twin_body_is_reported_without_failing(self) -> None:
        self.write("src/game/a.c", "/* definition moved */\n")
        status, output = self.run_main("func_15000000", "--level", "0", "--limit", "1")
        self.assertEqual(0, status)
        self.assertIn("twin-body: unavailable (expected exactly one C definition for func_15000100; found 0)\n",
                      output)

    def test_queue_ranks_raw_items_by_level_then_size(self) -> None:
        self.functions["func_15000100"] = ("raw_asm", "src/game/a.c", None)
        self.write_inventory()
        status, output = self.run_main("--all-deferred")
        self.assertEqual(0, status)
        rows = [line for line in output.splitlines() if not line.startswith("#")]
        self.assertEqual([
            f"0 {len(TARGET):>4} deferred    12 func_15000000 src/game/a.c <= func_80000000",
            f"0 {len(TARGET):>4} raw_asm      - func_15000100 src/game/a.c <= func_80000000",
            f"0 {len(TARGET):>4} raw_asm      - func_15000500 src/game/b.c <= func_80000000",
        ], rows)
        self.assertIn("# total: 3\n", output)

        status, output = self.run_main("--all-deferred", "--limit", "1")
        self.assertIn("# ... (2 more; raise --limit)\n", output)

        self.functions["func_80000000"] = ("raw_asm", "src/done/main/c.c", None)
        self.functions["func_15000200"] = ("raw_asm", "src/game/b.c", None)
        self.functions["func_15000300"] = ("raw_asm", "src/game/b.c", None)
        self.write_inventory()
        status, output = self.run_main("--all-deferred")
        self.assertIn("# total: 0\n", output)
        status, output = self.run_main("--all-deferred", "--unmatched")
        rows = [line for line in output.splitlines() if not line.startswith("#")]
        # Every raw item now has raw twins: four level-0 copies and the two renamed ones.
        self.assertEqual(6, len(rows))
        self.assertTrue(rows[0].endswith("func_15000000 src/game/a.c <= func_15000100 func_15000500 func_80000000"))
        self.assertTrue(rows[4].startswith("1 ") and "func_15000200" in rows[4])
        self.assertTrue(rows[5].startswith("2 ") and "func_15000300" in rows[5])

    def test_matched_twins_are_matched_state_only(self) -> None:
        for state in ("blocked", "original_asm", "raw_asm"):
            self.functions["func_15000100"] = (state, "src/game/a.c", None)
            self.functions["func_80000000"] = (state, "src/done/main/c.c", None)
            self.write_inventory()
            with self.subTest(state=state):
                status, output = self.run_main("func_15000000", "--level", "0")
                self.assertEqual(1, status)
                self.assertIn("sibling-twin: none", output)

    def test_hint_is_quiet_without_reference_assembly_and_never_raises(self) -> None:
        self.assertEqual("level 0 func_15000100 func_80000000", siblings.hint("func_15000000"))
        self.assertEqual("none", siblings.hint("func_15000400"))
        self.assertTrue(siblings.hint("func_unknown").startswith("unavailable ("))
        status, output = self.run_main("func_15000000", "--hint")
        self.assertEqual((0, "sibling-twin: level 0 func_15000100 func_80000000\n"), (status, output))
        with patch.object(siblings, "REFERENCE_ROOTS", (("game", "reference/missing/asm"),)):
            with patch.object(siblings, "load_inventory",
                              side_effect=AssertionError("inventory read without reference")):
                self.assertEqual("none (reference assembly absent)", siblings.hint("func_15000000"))

    def test_unknown_items_and_missing_reference_fail_clearly(self) -> None:
        status, output = self.run_main("func_15000400")
        self.assertEqual(1, status)
        self.assertIn("sibling-twin: none (levels 0-2)\n", output)
        with patch("sys.stderr", io.StringIO()) as stderr:
            self.assertEqual(2, self.run_main("func_unknown")[0])
            self.assertIn("unknown US work-item ID or symbol: func_unknown", stderr.getvalue())
        with patch.object(siblings, "REFERENCE_ROOTS", (("game", "reference/missing/asm"),)):
            with patch("sys.stderr", io.StringIO()) as stderr:
                self.assertEqual(2, self.run_main("func_15000000")[0])
                self.assertIn("no reference assembly is present", stderr.getvalue())
        with self.assertRaises(SystemExit), patch("sys.stderr", io.StringIO()):
            siblings.parse_args([])
        with self.assertRaises(SystemExit), patch("sys.stderr", io.StringIO()):
            siblings.parse_args(["func_15000000", "--all-deferred"])
        with self.assertRaises(SystemExit), patch("sys.stderr", io.StringIO()):
            siblings.parse_args(["func_15000000", "--unmatched"])

    def test_wrapper_exposes_the_command_and_the_ready_hint(self) -> None:
        script = (ROOT / "scripts/conker.sh").read_text(encoding="utf-8")
        self.assertIn("siblings <work-item-id> [--level 0|1|2] [--limit N]", script)
        self.assertIn('python3 scripts/siblings.py "$@"', script)
        prepare_body = script.split("prepare_next_work() {", 1)[1].split("\n}", 1)[0]
        self.assertIn('python3 scripts/siblings.py "$identifier" --hint', prepare_body)
        # The hint is printed with the selection details, before toolchain preparation.
        self.assertLess(prepare_body.index('scripts/siblings.py "$identifier" --hint'),
                        prepare_body.index("ensure_warm_container"))
        # The dispatch branch forwards arguments unchanged under Bash 3.2.
        dispatch = ("    siblings)" + script.split("    siblings)", 1)[1].split("        ;;", 1)[0]
                    + "        ;;\n")
        harness = ("set -euo pipefail\n"
                   "die() { printf 'error: %s\\n' \"$*\" >&2; exit 1; }\n"
                   "python3() { printf '%s\\0' \"$@\"; }\n"
                   "case siblings in\n" + dispatch + "esac\n")
        result = subprocess.run(["bash", "-c", harness, "test", "func_a", "--level", "1"],
                                text=True, capture_output=True, check=False)
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertEqual(["scripts/siblings.py", "func_a", "--level", "1"],
                         result.stdout[:-1].split("\0"))
        result = subprocess.run(["bash", "-c", harness, "test"],
                                text=True, capture_output=True, check=False)
        self.assertEqual(1, result.returncode)
        self.assertIn("usage: ./conker siblings", result.stderr)


if __name__ == "__main__":
    unittest.main()
