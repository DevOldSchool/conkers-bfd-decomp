from __future__ import annotations

import json
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch
import os

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import diff
import linked_aliases
import layout_check
import rom_span
import project_state
from candidate_tables import Object32


def replace_fixture_neighbor_with_asm(content: str, source: str, symbol: str) -> str:
    """Restore a real raw neighbor in the historical layout-negative fixture."""
    start, end = project_state.work_item_function_span(content, symbol, regional_symbol=symbol)
    pragma = project_state.global_asm_pragma(source, symbol)
    return content[:start] + pragma + "\n" + content[end:]


class LayoutFailureFixtureTests(unittest.TestCase):
    def test_raw_neighbor_replacement_preserves_numeric_linkage_and_surroundings(self):
        source = "src/main/init_5570.c"
        symbol = "func_800057E0"
        for definition in (symbol, "motor_pak_init"):
            with self.subTest(definition=definition):
                alias = f"#define {definition} {symbol}\n" if definition != symbol else ""
                prefix = alias + f"int {definition}(int value);\nint before(void) {{ return 1; }}\n"
                body = f"int {definition}(int value) {{\n    return value;\n}}\n"
                suffix = f"int after(void) {{ return {definition}(2); }}\n"
                replaced = replace_fixture_neighbor_with_asm(prefix + body + suffix, source, symbol)
                self.assertEqual(prefix + project_state.global_asm_pragma(source, symbol) + "\n" + suffix,
                                 replaced)


@unittest.skipUnless(shutil.which("mips-linux-gnu-as") and shutil.which("mips-linux-gnu-ld"),
                     "requires pinned MIPS binutils")
class MainComparisonTests(unittest.TestCase):
    source = "src/main/unit.c"
    symbol = "func_80001010"
    start = 0x80001010

    def assemble(self, root, name, text):
        source = root / (name + ".s")
        source.write_text(".text\n.set noreorder\n" + text)
        output = source.with_suffix(".o")
        subprocess.run(["mips-linux-gnu-as", "-EB", "-mabi=32", "-march=vr4300",
                        "-o", str(output), str(source)], check=True, capture_output=True)
        return output

    def metadata(self, root, *, target=None, start=None, size=16, prefix=16, extent=32):
        target, start = target or self.symbol, start or self.start
        members = [{"symbol": "func_80001000", "source": self.source,
                    "regions": {"us": {"symbol": "func_80001000", "vram": "0x80001000", "size_bytes": prefix}}},
                   {"symbol": target, "source": self.source,
                    "regions": {"us": {"symbol": target, "vram": hex(start), "size_bytes": size}}}]
        unit = {"source": self.source, "functions": [member["symbol"] for member in members],
                "boundary_evidence": {"us": {"reviewed": True}},
                "regions": {"us": {"start": "0x1000", "end": hex(0x1000 + extent)}}}
        (root / "progress").mkdir(exist_ok=True)
        (root / "progress/functions.json").write_text(json.dumps({"functions": members}))
        (root / "progress/source_units.json").write_text(json.dumps({"source_units": [unit]}))

    def function(self, body, *, symbol=None, size=None):
        symbol = symbol or self.symbol
        return f".globl {symbol}\n{symbol}:\n{body}\n.size {symbol},{size if size is not None else '.-'+symbol}\n"

    def mixed(self, root, body, *, symbol=None, prefix=16, tail="", size=None):
        return self.assemble(root, "candidate", self.function("nop\n" * (prefix // 4), symbol="func_80001000")
                             + self.function(body, symbol=symbol, size=size) + tail)

    def prove(self, root, candidate, reference, words, *, symbol=None, start=None, raw=None):
        symbol, start = symbol or self.symbol, start or self.start
        payload = struct.pack(">" + "I" * len(words), *words)
        assembly = root / "raw.s"
        assembly.write_text(raw or "".join(f"/* {i*4:X} {start+i*4:08X} {word:08X} */ instruction\n"
                                          for i, word in enumerate(words)))
        with patch.object(rom_span, "main_code", return_value=(payload, start, "validated")):
            return linked_aliases.prepare_main(root, self.source, candidate, reference, assembly,
                                               symbol, start, len(payload))

    def test_alias_literal_and_signed_carry_full_span_proofs(self):
        for candidate_expression, reference_expression, address in (
                ("0xA0000000", "D_A0000000", 0xA0000000),
                ("D_800E7FFC+4", "D_800E8000", 0x800E8000),
                ("D_800E0A30+0x40", "D_800E0A70", 0x800E0A70)):
            with self.subTest(expression=candidate_expression), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                self.metadata(root)
                body = lambda expression: f"lui $v0,%hi({expression})\naddiu $v0,$v0,%lo({expression})\njr $ra\nnop"
                candidate = self.mixed(root, body(candidate_expression))
                reference = self.assemble(root, "reference", self.function(body(reference_expression)))
                words = [0x3C020000 | (((address + 0x8000) >> 16) & 0xFFFF),
                         0x24420000 | (address & 0xFFFF), 0x03E00008, 0]
                self.assertTrue(linked_aliases.main_eligible(candidate, reference, self.symbol, 16))
                pair = self.prove(root, candidate, reference, words)
                self.assertIsNotNone(pair)
                self.assertEqual(pair[0].read_bytes(), pair[1].read_bytes())

    def test_actual_same_unit_callee_is_linked_without_override(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            self.metadata(root)
            body = "jal func_80001000\nnop\njr $ra\nnop"
            candidate = self.mixed(root, body)
            reference = self.assemble(root, "reference", self.function(body))
            pair = self.prove(root, candidate, reference, [0x0C000400, 0, 0x03E00008, 0])
            self.assertIsNotNone(pair)
            script = (root / "build/us/linked-aliases" / self.symbol / "candidate.ld").read_text()
            self.assertNotIn("func_80001000 =", script)
            wrong_callee = self.mixed(root, "jal func_80001000+4\nnop\njr $ra\nnop")
            self.assertIsNone(self.prove(root, wrong_callee, reference, [0x0C000400, 0, 0x03E00008, 0]))
            parsed = Object32(candidate.read_bytes())
            self.assertIsNone(linked_aliases.definitions(parsed))
            self.assertIsNone(linked_aliases.definitions(parsed, text_addresses={"func_80001000": 0x80001004},
                                                        text_section=1, text_base=0x80001000))

    def test_real_mixed_alignment_tail_preserves_short_symbol_extent(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            symbol, start = "func_8000100C", 0x8000100C
            self.metadata(root, target=symbol, start=start, size=20, prefix=12)
            body = "jr $ra\nmove $v0,$zero\nnop"
            candidate = self.mixed(root, body, symbol=symbol, prefix=12, tail=".p2align 4\n")
            reference = self.assemble(root, "reference", self.function(body + "\nnop\nnop", symbol=symbol))
            self.assertTrue(linked_aliases.main_eligible(candidate, reference, symbol, 20))
            original = candidate.read_bytes()
            self.assertIsNotNone(self.prove(root, candidate, reference, [0x03E00008, 0x00001025, 0, 0, 0],
                                            symbol=symbol, start=start))
            self.assertEqual(original, candidate.read_bytes())
            self.assertEqual(12, next(s[2] for ss in Object32(original).symbols.values() for s in ss if s[0] == symbol))

    def test_wrong_literal_addend_carry_register_opcode_and_terminal_word_fail(self):
        bodies = ["lui $v0,0x800e\naddiu $v0,$v0,0x7ffc\njr $ra\nnop",
                  "lui $v0,%hi(D_800E7FFC+8)\naddiu $v0,$v0,%lo(D_800E7FFC+8)\njr $ra\nnop",
                  "lui $v0,0x800e\naddiu $v0,$v0,0x8000\njr $ra\nnop",
                  "lui $v1,%hi(D_800E7FFC+4)\naddiu $v1,$v1,%lo(D_800E7FFC+4)\njr $ra\nnop",
                  "lui $v0,%hi(D_800E7FFC+4)\nori $v0,$v0,%lo(D_800E7FFC+4)\njr $ra\nnop",
                  "lui $v0,%hi(D_800E7FFC+4)\naddiu $v0,$v0,%lo(D_800E7FFC+4)\njr $ra\naddiu $v1,$zero,1"]
        for body in bodies:
            with self.subTest(body=body), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                self.metadata(root)
                reference = self.assemble(root, "reference", self.function(
                    "lui $v0,%hi(D_800E8000)\naddiu $v0,$v0,%lo(D_800E8000)\njr $ra\nnop"))
                self.assertIsNone(self.prove(root, self.mixed(root, body), reference,
                                            [0x3C02800F, 0x24428000, 0x03E00008, 0]))

    def test_unknown_unsupported_and_local_data_relocations_fail_closed(self):
        for body, tail in (("jal unresolved\nnop\njr $ra\nnop", ""),
                           ("lw $v0,%gp_rel(D_800E8000)($gp)\nnop\njr $ra\nnop", ""),
                           ("lui $v0,%hi(D_800E8000)\naddiu $v0,$v0,%lo(D_800E8000)\njr $ra\nnop",
                            ".data\n.globl D_800E8000\nD_800E8000: .word 0\n")):
            with self.subTest(body=body), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                self.metadata(root)
                candidate = self.mixed(root, body, tail=tail)
                reference = self.assemble(root, "reference", self.function("nop\nnop\njr $ra\nnop"))
                self.assertIsNone(self.prove(root, candidate, reference, [0, 0, 0x03E00008, 0]))

    def test_shifted_member_or_padding_overlapping_next_symbol_is_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            self.metadata(root)
            candidate = self.mixed(root, "jr $ra\nnop\nnop", prefix=12)
            reference = self.assemble(root, "reference", self.function("jr $ra\nnop\nnop\nnop"))
            with self.assertRaisesRegex(layout_check.LayoutMismatch, "delta -4"):
                self.prove(root, candidate, reference, [0x03E00008, 0, 0, 0])
            candidate = self.mixed(root, "jr $ra\nnop", tail="next_function:\nnop\nnop\n")
            with self.assertRaisesRegex(ValueError, "padding overlaps"):
                self.prove(root, candidate, reference, [0x03E00008, 0, 0, 0])

    def test_raw_word_mismatch_truncation_and_noncontiguous_span_are_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            self.metadata(root)
            candidate = self.mixed(root, "nop\nnop\njr $ra\nnop")
            reference = self.assemble(root, "reference", self.function("nop\nnop\njr $ra\nnop"))
            valid = "".join(f"/* {i*4:X} {self.start+i*4:08X} {word:08X} */ instruction\n"
                            for i, word in enumerate([0, 0, 0x03E00008, 0]))
            for raw in (valid.replace("03E00008", "03E00009"), valid.rsplit("/*", 1)[0],
                        valid.replace("8000101C", "80001020")):
                with self.assertRaises(ValueError):
                    self.prove(root, candidate, reference, [0, 0, 0x03E00008, 0], raw=raw)
            with self.assertRaisesRegex(ValueError, "raw-reference span differs"):
                self.prove(root, candidate, reference, [0, 0, 0x03E00008, 1])

    def test_shorter_supplied_assembly_and_rom_cannot_shrink_registered_span(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            self.metadata(root, size=16)
            candidate = self.mixed(root, "jr $ra\nnop")
            reference = self.assemble(root, "reference", self.function("jr $ra\nnop"))
            with self.assertRaisesRegex(ValueError, "full registered span"):
                self.prove(root, candidate, reference, [0x03E00008, 0])


class MainComparisonFreshnessTests(unittest.TestCase):
    def test_main_rom_checksum_is_checked_before_payload_use(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / "config").mkdir()
            (root / "roms").mkdir()
            (root / "roms/baserom.us.z64").write_bytes(b"wrong ROM")
            (root / "config/roms.json").write_text(json.dumps({"profiles": {"us": {
                "sha1": "a" * 40, "size_bytes": 9}}}))
            with patch.object(rom_span.rzip_archive, "normalize_rom", return_value=(b"wrong ROM", None)):
                with self.assertRaisesRegex(ValueError, "checksum-validated"):
                    rom_span.main_code(root)

    def test_missing_and_duplicate_candidate_symbols_are_rejected(self):
        obj = Object32(linked_aliases.comparison_object(bytes(16), "func_test"))
        with self.assertRaisesRegex(ValueError, "one function"):
            linked_aliases.function(obj, "missing", 16)
        table = next(iter(obj.symbols.values()))
        table.append(table[-1])
        with self.assertRaisesRegex(ValueError, "one function"):
            linked_aliases.function(obj, "func_test", 16)

    def test_fresh_mixed_compile_and_stale_source_fail_closed(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            source = root / "src/main/unit.c"
            source.parent.mkdir(parents=True)
            source.write_text("void func_test(void) {}\n")
            with patch.object(diff, "ROOT", root), \
                    patch.object(linked_aliases, "main_eligible", return_value=True), \
                    patch.object(diff.prepare_nonmatching_asm, "materialize"), \
                    patch.object(layout_check, "failure_inputs", side_effect=[{"source": "old"}, {"source": "new"}]), \
                    patch.object(diff.compile_c, "compile_command", return_value=["compiler"]) as command, \
                    patch.object(diff.subprocess, "run") as run, \
                    patch.object(linked_aliases, "prepare_main", return_value=(Path("candidate"), Path("reference"))):
                with self.assertRaisesRegex(ValueError, "inputs changed"):
                    diff.prepare_main_comparison(source, Path("focused"), Path("reference"), Path("raw"),
                                                 "func_test", 0x80001000, 16)
                self.assertIn("linked-aliases/func_test/source.c", str(command.call_args.args[1]))
                run.assert_called_once_with(["compiler"], cwd=root, check=True)

    def test_global_asm_target_cannot_use_a_mixed_assembly_match(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            source = root / "src/main/unit.c"
            source.parent.mkdir(parents=True)
            source.write_text('#pragma GLOBAL_ASM("asm/nonmatchings/main/unit/func_test.s")\n')
            with patch.object(diff, "ROOT", root), \
                    patch.object(linked_aliases, "main_eligible", return_value=True), \
                    patch.object(diff.prepare_nonmatching_asm, "materialize"), \
                    patch.object(layout_check, "failure_inputs", return_value={}), \
                    patch.object(diff.subprocess, "run") as run:
                with self.assertRaisesRegex(ValueError, "still supplied by GLOBAL_ASM"):
                    diff.prepare_main_comparison(source, Path("focused"), Path("reference"), Path("raw"),
                                                 "func_test", 0x80001000, 16)
                run.assert_not_called()

    def test_watch_never_uses_a_linked_main_snapshot(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            source, reference = root / "source.c", root / "reference.o"
            source.write_text("void func_test(void) {}\n")
            reference.write_bytes(b"reference")
            with patch.object(sys, "argv", ["diff.py", "us", "func_test", "--watch"]), \
                    patch.object(diff, "find_work_item", return_value=(source, "func_test")), \
                    patch.object(diff, "ensure_reference_function", return_value=Path("raw.s")), \
                    patch.object(diff, "expected_function_size", return_value=16), \
                    patch.object(diff, "require_c_implementation"), \
                    patch.object(diff, "compile_candidate", return_value=Path("live.o")), \
                    patch.object(diff, "reference_object", return_value=reference), \
                    patch.object(diff, "work_item_overlay", return_value="main"), \
                    patch.object(diff, "prepare_main_comparison") as prepare, \
                    patch.object(diff, "write_settings", return_value=root), \
                    patch.object(diff, "asm_diff_command", return_value=["differ"]) as command, \
                    patch.object(diff, "run_asm_diff", return_value=0):
                self.assertEqual(0, diff.main())
                prepare.assert_not_called()
                self.assertEqual(Path("live.o"), command.call_args.args[0])
                self.assertTrue(command.call_args.kwargs["watch"])


@unittest.skipUnless(os.environ.get("CONKER_ROM_TESTS") == "1" and diff.compile_c.IDO_CC.is_file(),
                     "opt-in integration tests require the pinned toolchain and reviewed US ROM")
class RegisteredMainComparisonTests(unittest.TestCase):
    def test_registered_candidates_with_live_source_and_rom(self):
        for suffix in ("3330", "57E0", "F248", "390C", "5948", "440C", "56A0"):
            symbol = "func_8000" + suffix
            with self.subTest(symbol=symbol):
                source, _ = diff.find_work_item(symbol, "us")
                assembly = diff.ensure_reference_function("us", symbol)
                reference = diff.reference_object("us", symbol, assembly=assembly)
                size = diff.expected_function_size("us", symbol)
                deferred = symbol if diff.work_item_is_deferred(symbol) else None
                if suffix == "56A0" and deferred is None:
                    continue  # The historical negative applies only to its preserved candidate.
                candidate = diff.compile_candidate("us", source, deferred_symbol=deferred)
                pair = diff.prepare_main_comparison(source, candidate, reference, assembly, symbol,
                                                    int(symbol[-8:], 16), size, deferred_symbol=deferred)
                if suffix == "56A0":
                    self.assertIsNone(pair)
                    directory = diff.write_settings("us", source)
                    # Live C neighbors can change the focused diagnostic. The
                    # invariant is rejection of the real mixed layout/span.
                    mixed = diff.ROOT / "build/us/linked-aliases" / symbol / "mixed.o"
                    function, unit = layout_check.load_work_item(symbol, "us")
                    with self.assertRaisesRegex(layout_check.LayoutMismatch, "delta -12"):
                        layout_check.validate_layout(function, unit, *layout_check.archived_object_layout(mixed.read_bytes()), "us")
                    result = subprocess.run(diff.asm_diff_command(mixed, reference, symbol, size, require_match=True),
                                            cwd=directory, capture_output=True, text=True, check=True)
                    self.assertEqual(600, diff.current_difference_count(result.stdout))
                else:
                    self.assertIsNotNone(pair)
                    self.assertEqual(pair[0].read_bytes(), pair[1].read_bytes())
                    code, base, _ = rom_span.main_code(diff.ROOT)
                    expected = rom_span.raw_span(assembly.read_text(), int(symbol[-8:], 16), size, code, base)
                    obj = Object32(pair[0].read_bytes())
                    _, section = linked_aliases.function(obj, symbol, size)
                    self.assertEqual(expected, obj.section(section))

    def test_real_layout_failure_can_still_be_archived_deferred_and_resumed(self):
        root = diff.ROOT
        symbol = "func_800056A0"
        if not diff.work_item_is_deferred(symbol):
            self.skipTest("historical layout-negative candidate is no longer deferred")
        source = Path("src/main/init_5570.c")
        original = (root / source).read_bytes()
        (root / "build").mkdir(exist_ok=True)
        with tempfile.TemporaryDirectory(dir=root / "build") as temporary:
            fixture = Path(temporary)
            for directory in ("scripts", "progress", "src"):
                shutil.copytree(root / directory, fixture / directory)
            for directory in ("config", "include", "reference", "roms", "toolchain"):
                (fixture / directory).symlink_to(root / directory, target_is_directory=True)
            shutil.copy2(root / "Dockerfile", fixture / "Dockerfile")
            # Recreate the historical focused-zero case independently of the
            # live tree's progress: these two real raw neighbors are removed
            # by the focused compiler and retained by the mixed compiler.
            inventory_path = fixture / "progress/functions.json"
            inventory = json.loads(inventory_path.read_text())
            content = (fixture / source).read_text()
            for neighbor in ("func_800057E0", "func_80005948"):
                pragma = project_state.global_asm_pragma(source.as_posix(), neighbor)
                if pragma not in content:
                    content = replace_fixture_neighbor_with_asm(content, source.as_posix(), neighbor)
                    entry = next(entry for entry in inventory["functions"] if entry["symbol"] == neighbor)
                    entry["regions"]["us"]["state"] = "raw_asm"
                    entry.pop("deferred", None)
            (fixture / source).write_text(content)
            inventory_path.write_text(json.dumps(inventory))
            def command(*arguments):
                return subprocess.run([sys.executable, *arguments], cwd=fixture,
                                      capture_output=True, text=True)
            self.assertEqual(0, command("scripts/project_state.py", "resume", symbol).returncode)
            restored = (fixture / source).read_bytes()
            focused = command("scripts/diff.py", "us", symbol, "--auto-overlay", "--require-match")
            self.assertEqual(0, focused.returncode, focused.stdout + focused.stderr)
            self.assertIn("CURRENT (0)", focused.stdout)
            proof = "build/us/deferred-layout/attempt/proof.json"
            layout = command("scripts/layout_check.py", "us", symbol,
                             "--failure-archive", "build/us/deferred-layout/attempt")
            self.assertEqual(1, layout.returncode, layout.stdout + layout.stderr)
            self.assertIn("delta -12", layout.stderr)
            self.assertTrue((fixture / proof).is_file())
            deferred = command("scripts/project_state.py", "defer", symbol, "--score", "0",
                               "--reason", "Exact focused body, shifted mixed neighbors",
                               "--layout-failure-proof", proof)
            self.assertEqual(0, deferred.returncode, deferred.stdout + deferred.stderr)
            inventory = json.loads((fixture / "progress/functions.json").read_text())["functions"]
            entry = next(entry for entry in inventory if entry["symbol"] == symbol)
            self.assertEqual("raw_asm", entry["regions"]["us"]["state"])
            self.assertEqual(0, entry["deferred"]["layout_failure"]["focused_current_differences"])
            self.assertEqual(0, command("scripts/project_state.py", "resume", symbol).returncode)
            self.assertEqual(restored, (fixture / source).read_bytes())
        self.assertEqual(original, (root / source).read_bytes())
