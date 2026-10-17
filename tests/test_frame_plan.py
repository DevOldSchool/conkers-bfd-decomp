from __future__ import annotations

import importlib.util
import io
import struct
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path
from unittest import mock

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tests"))
import frame_plan  # noqa: E402
import frame_plan_asm as asm  # noqa: E402
import probe  # noqa: E402

FIXTURES = ROOT / "tests" / "fixtures" / "frame_plan"


def fixture_plan(name: str, symbol: str = "func_15000000", size: int | None = None) -> frame_plan.FramePlan:
    return frame_plan.reference_plan(FIXTURES / name, symbol, size)


def inline_plan(body: list[str], symbol: str = "func_test") -> frame_plan.FramePlan:
    return frame_plan.analyze(symbol, asm.words(body))


class FixtureIntegrityTests(unittest.TestCase):
    def test_checked_in_fixtures_match_the_generator(self):
        for name, functions in asm.FIXTURE_FUNCTIONS.items():
            with self.subTest(fixture=name):
                self.assertEqual(asm.listing(functions), (FIXTURES / name).read_text(encoding="utf-8"))


class ReferenceWordsTests(unittest.TestCase):
    def test_function_ends_at_the_next_glabel(self):
        text = (FIXTURES / "leaf.s").read_text(encoding="utf-8")
        self.assertEqual(asm.words(asm.LEAF), frame_plan.reference_words(text, "func_15000000"))
        self.assertEqual(asm.words(asm.SAVED_REGISTERS), frame_plan.reference_words(text, "func_15000010"))

    def test_size_keeps_interior_labels_inside_the_function(self):
        body = ["addiu $sp, $sp, -0x18", "sw $ra, 0x14($sp)", "glabel func_test_entry2",
                "jal func_x", "nop", "lw $ra, 0x14($sp)", "jr $ra", "addiu $sp, $sp, 0x18"]
        text = asm.listing([("func_test", body), ("func_next", asm.LEAF)])
        self.assertEqual(2, len(frame_plan.reference_words(text, "func_test")))
        self.assertEqual(7, len(frame_plan.reference_words(text, "func_test", 7 * 4)))
        with self.assertRaisesRegex(frame_plan.FramePlanError, "shorter than"):
            frame_plan.reference_words(text, "func_test", 12 * 4)
        with self.assertRaisesRegex(frame_plan.FramePlanError, "invalid"):
            frame_plan.reference_words(text, "func_test", 6)

    def test_data_directive_ends_the_function(self):
        text = asm.listing([("func_test", asm.LEAF)]) + "    .word 0x15000000\n    /* 100 15000100 27BDFFE8 */  addiu $sp, $sp, -0x18\n"
        self.assertEqual(asm.words(asm.LEAF), frame_plan.reference_words(text, "func_test"))

    def test_missing_symbol_is_reported(self):
        with self.assertRaisesRegex(frame_plan.FramePlanError, "func_missing has no glabel"):
            frame_plan.reference_words(asm.listing([("func_test", asm.LEAF)]), "func_missing")

    def test_reference_frame_size_helper(self):
        self.assertEqual(0x30, frame_plan.reference_frame_size(FIXTURES / "spill_temps.s", "func_15000000"))
        self.assertIsNone(frame_plan.reference_frame_size(FIXTURES / "leaf.s", "func_15000000"))
        self.assertIsNone(frame_plan.reference_frame_size(FIXTURES / "leaf.s", "func_missing"))


class AnalysisTests(unittest.TestCase):
    def test_spill_temps_layout(self):
        plan = fixture_plan("spill_temps.s")
        self.assertEqual(0x30, plan.frame_size)
        self.assertEqual(4, plan.calls)
        self.assertEqual({0x14: "ra"}, plan.saved)
        self.assertEqual((0, 0x10), plan.outgoing)
        self.assertEqual((0x10, 0x18), plan.saved_area)
        self.assertEqual((0x18, 0x30), plan.local_area)
        areas = {slot.offset: slot.area for slot in plan.slots}
        self.assertEqual({0x30: "arg-in", 0x34: "arg-in", 0x38: "arg-in", 0x28: "local",
                          0x20: "local", 0x1C: "local", 0x14: "saved"}, areas)
        self.assertTrue(plan.slot_at(0x28).address_taken)
        self.assertEqual(["&-> $a2; lw x2", "sw $v0; lw [call-crossing]", "sw $v1 (delay); lw [call-crossing]"],
                         [plan.slot_at(offset).summary() for offset in (0x28, 0x20, 0x1C)])
        inference = plan.infer()
        self.assertEqual([0x2C, 0x28, 0x24], inference.named_words)
        self.assertEqual([0x20, 0x1C], inference.crossing_words)
        self.assertEqual([0x18], inference.unused_bottom_words)
        self.assertEqual([0x28], inference.anchors)

    def test_saved_registers_without_locals(self):
        plan = fixture_plan("saved_registers.s")
        self.assertEqual(0x28, plan.frame_size)
        self.assertEqual({0x24: "ra", 0x20: "s3", 0x1C: "s2", 0x18: "s1", 0x14: "s0"}, plan.saved)
        self.assertEqual((0x10, 0x28), plan.saved_area)
        self.assertEqual((0, 0x10), plan.outgoing)
        self.assertIsNone(plan.local_area)
        self.assertIsNone(plan.infer())
        self.assertTrue(all(slot.area == "saved" for slot in plan.slots))
        rendered = "\n".join(plan.render())
        self.assertIn("saved 0x10..0x27 ($ra 0x24, $s3 0x20, $s2 0x1c, $s1 0x18, $s0 0x14)", rendered)
        self.assertNotIn("inferred", rendered)

    def test_aggregate_with_sub_word_stores(self):
        plan = fixture_plan("aggregate.s")
        self.assertEqual(0x40, plan.frame_size)
        self.assertEqual((0, 0x18), plan.outgoing)
        self.assertEqual((0x20, 0x40), plan.local_area)
        byte_argument = plan.slot_at(0x47)
        self.assertEqual(("arg-in", 1), (byte_argument.area, byte_argument.size))
        self.assertIn("sub-word", plan.slot_at(0x2C).summary())
        self.assertIn("sub-word", plan.slot_at(0x2E).summary())
        self.assertEqual(["arg-out", "arg-out"], [plan.slot_at(offset).area for offset in (0x10, 0x14)])
        inference = plan.infer()
        self.assertEqual([0x3C, 0x38, 0x34, 0x30, 0x2C, 0x28], inference.named_words)
        self.assertEqual([], inference.crossing_words)
        self.assertEqual([0x24, 0x20], inference.unused_bottom_words)

    def test_leaf_without_frame_homes_arguments_in_the_caller_area(self):
        plan = fixture_plan("leaf.s")
        self.assertEqual(0, plan.frame_size)
        self.assertIsNone(plan.local_area)
        self.assertEqual([("arg-in", 0)], [(slot.area, slot.offset) for slot in plan.slots])
        self.assertIn("frame leaf", "\n".join(frame_plan.render_block(plan, None)))

    def test_delay_slot_store_crosses_its_call(self):
        plan = inline_plan([
            "addiu $sp, $sp, -0x20", "sw $ra, 0x14($sp)",
            "jal func_x", "sw $v0, 0x1C($sp)",
            "lw $t0, 0x1C($sp)",
            "jal func_y", "sw $v0, 0x18($sp)",
            "lw $ra, 0x14($sp)", "jr $ra", "addiu $sp, $sp, 0x20",
        ])
        self.assertTrue(plan.slot_at(0x1C).call_crossing)
        self.assertFalse(plan.slot_at(0x18).call_crossing, "a store never reloaded crosses nothing")

    def test_store_reloaded_before_any_call_is_not_crossing(self):
        plan = inline_plan([
            "addiu $sp, $sp, -0x20", "sw $ra, 0x14($sp)",
            "sw $t0, 0x1C($sp)", "lw $t1, 0x1C($sp)",
            "jal func_x", "nop",
            "lw $ra, 0x14($sp)", "jr $ra", "addiu $sp, $sp, 0x20",
        ])
        self.assertFalse(plan.slot_at(0x1C).call_crossing)
        inference = plan.infer()
        self.assertEqual([0x1C], inference.named_words)
        self.assertEqual([0x18], inference.unused_bottom_words)

    def test_anchor_stops_the_spill_scan(self):
        plan = inline_plan([
            "addiu $sp, $sp, -0x28", "sw $ra, 0x14($sp)",
            "addiu $a0, $sp, 0x18",
            "sw $v0, 0x20($sp)", "jal func_x", "sw $v1, 0x1C($sp)",
            "lw $a1, 0x20($sp)", "lw $a2, 0x1C($sp)", "lw $a3, 0x18($sp)",
            "lw $ra, 0x14($sp)", "jr $ra", "addiu $sp, $sp, 0x28",
        ])
        inference = plan.infer()
        self.assertEqual([0x18], inference.anchors)
        self.assertEqual([0x24, 0x20, 0x1C, 0x18], inference.named_words)
        self.assertEqual([], inference.crossing_words)

    def test_sp_moves_and_double_saves_are_recognised(self):
        plan = inline_plan([
            "addiu $sp, $sp, -0x30", "sw $ra, 0x1C($sp)", "sdc1 $f20, 0x10($sp)",
            "or $a0, $sp, $zero",
            "jal func_x", "nop",
            "ldc1 $f20, 0x10($sp)", "lw $ra, 0x1C($sp)", "jr $ra", "addiu $sp, $sp, 0x30",
        ])
        self.assertEqual({0x1C: "ra", 0x10: "f20"}, plan.saved)
        self.assertEqual((0x10, 0x20), plan.saved_area)
        self.assertEqual((0, 0x10), plan.outgoing)
        self.assertTrue(plan.slot_at(0).address_taken)
        self.assertEqual("arg-out", plan.slot_at(0).area)

    def test_render_inference_wording(self):
        lines = frame_plan.render_inference(frame_plan.Inference([0x2C, 0x28, 0x24, 0x20], [0x2C], [0x28, 0x24], [0x20], []))
        self.assertEqual("inferred: named-local homes >= 1 word (0x2c); call-crossing words below 2 (0x28..0x24);"
                         " unused bottom words 1 (0x20)", lines[0])
        self.assertIn("spill temps or named locals that live across a call", lines[1])


def elf_object(functions: list[tuple[str, list[int], int | None]]) -> bytes:
    """Minimal big-endian ELF32 object with .text, .symtab and .strtab.

    ``functions`` holds (name, words, st_size); None records a zero size so the
    reader must bound the function by the next symbol or the section end.
    """

    text = b""
    symbols = b"\0" * 16
    strings = b"\0"
    for name, words, size in functions:
        value = len(text)
        body = b"".join(word.to_bytes(4, "big") for word in words)
        text += body
        symbols += struct.pack(">IIIBBH", len(strings), value, len(body) if size is None else size, 0x12, 0, 1)
        strings += name.encode() + b"\0"
    shstrtab = b"\0.text\0.symtab\0.strtab\0.shstrtab\0"
    header_size = 52
    text_offset = header_size
    symtab_offset = text_offset + len(text)
    strtab_offset = symtab_offset + len(symbols)
    shstrtab_offset = strtab_offset + len(strings)
    section_offset = shstrtab_offset + len(shstrtab)
    header = bytearray(header_size)
    header[:6] = b"\x7fELF\x01\x02"
    struct.pack_into(">I", header, 0x20, section_offset)
    struct.pack_into(">HHH", header, 0x2E, 40, 5, 4)
    sections = struct.pack(">10I", *([0] * 10))
    sections += struct.pack(">10I", 1, 1, 6, 0, text_offset, len(text), 0, 0, 16, 0)
    sections += struct.pack(">10I", 7, 2, 0, 0, symtab_offset, len(symbols), 3, 0, 4, 16)
    sections += struct.pack(">10I", 15, 3, 0, 0, strtab_offset, len(strings), 0, 0, 1, 0)
    sections += struct.pack(">10I", 23, 3, 0, 0, shstrtab_offset, len(shstrtab), 0, 0, 1, 0)
    return bytes(header) + text + symbols + strings + shstrtab + sections


class ObjectTests(unittest.TestCase):
    def test_reads_words_by_symbol_with_and_without_sizes(self):
        data = elf_object([("func_a", asm.words(asm.SPILL_TEMPS), None), ("func_b", asm.words(asm.LEAF), 0)])
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "unit.o"
            path.write_bytes(data)
            self.assertEqual(asm.words(asm.SPILL_TEMPS), frame_plan.object_words(path, "func_a"))
            self.assertEqual(asm.words(asm.LEAF), frame_plan.object_words(path, "func_b"))
            self.assertEqual(0x30, frame_plan.object_frame_size(path, "func_a"))
            self.assertIsNone(frame_plan.object_frame_size(path, "func_b"))
            self.assertEqual(0x30, frame_plan.object_plan(path, "func_a").frame_size)
            with self.assertRaisesRegex(frame_plan.FramePlanError, "func_c not found"):
                frame_plan.object_words(path, "func_c")

    def test_zero_size_symbol_is_bounded_by_the_next_symbol(self):
        data = elf_object([("func_a", asm.words(asm.LEAF), 0), ("func_b", asm.words(asm.SAVED_REGISTERS), 0)])
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "unit.o"
            path.write_bytes(data)
            self.assertEqual(4, len(frame_plan.object_words(path, "func_a")))
            self.assertEqual(len(asm.SAVED_REGISTERS) - 1, len(frame_plan.object_words(path, "func_b")))

    def test_non_elf_input_is_rejected(self):
        with self.assertRaisesRegex(frame_plan.FramePlanError, "big-endian ELF"):
            frame_plan.elf_sections(b"not an object")


class RenderBlockTests(unittest.TestCase):
    def test_block_reports_frame_mismatch_and_candidate_slots(self):
        reference = fixture_plan("spill_temps.s")
        candidate = inline_plan(["addiu $sp, $sp, -0x28", "sw $ra, 0x14($sp)", "sw $v0, 0x20($sp)",
                                 "jal func_x", "nop", "lw $a0, 0x20($sp)",
                                 "lw $ra, 0x14($sp)", "jr $ra", "addiu $sp, $sp, 0x28"], "func_15000000")
        lines = frame_plan.render_block(reference, candidate)
        self.assertEqual("frame-plan:", lines[0])
        self.assertEqual("  reference frame 0x30; candidate frame 0x28 (MISMATCH)", lines[1])
        self.assertIn("  candidate slots (sp offsets of the candidate's own frame):", lines)
        self.assertTrue(any("0x20    4  local   sw $v0; lw [call-crossing]" in line for line in lines))

    def test_block_without_candidate_and_with_matching_frame(self):
        reference = fixture_plan("spill_temps.s")
        self.assertIn("candidate frame unavailable", frame_plan.render_block(reference, None)[1])
        same = frame_plan.render_block(reference, reference)
        self.assertIn("(match)", same[1])
        self.assertFalse(any("candidate slots" in line for line in same))


class CommandLineTests(unittest.TestCase):
    def test_assembly_mode_prints_the_block(self):
        output = io.StringIO()
        argv = ["frame_plan.py", "--assembly", str(FIXTURES / "spill_temps.s"), "func_15000000"]
        with mock.patch.object(sys, "argv", argv), redirect_stdout(output):
            self.assertEqual(0, frame_plan.main())
        self.assertIn("frame-plan:", output.getvalue())
        self.assertIn("named-local homes >= 3 words", output.getvalue())

    def test_missing_symbol_is_an_error_exit(self):
        argv = ["frame_plan.py", "--assembly", str(FIXTURES / "spill_temps.s"), "func_missing"]
        with mock.patch.object(sys, "argv", argv), redirect_stdout(io.StringIO()), \
                mock.patch.object(sys, "stderr", io.StringIO()):
            self.assertEqual(1, frame_plan.main())


def load(name: str):
    spec = importlib.util.spec_from_file_location(name + "_helper", ROOT / "scripts" / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class DiffIntegrationTests(unittest.TestCase):
    def setUp(self):
        self.diff = load("diff")
        self.reference = FIXTURES / "spill_temps.s"
        self.size = len(asm.SPILL_TEMPS) * 4

    def write_candidate(self, directory: Path, body: list[str]) -> Path:
        path = directory / "candidate.o"
        path.write_bytes(elf_object([("func_15000000", asm.words(body), None)]))
        return path

    def test_no_block_without_stack_rows_when_frames_agree(self):
        with tempfile.TemporaryDirectory() as directory:
            candidate = self.write_candidate(Path(directory), asm.SPILL_TEMPS)
            self.assertEqual([], self.diff.frame_plan_lines(self.reference, candidate, "func_15000000", self.size, 0))

    def test_block_on_frame_mismatch_even_without_stack_rows(self):
        smaller = ["addiu $sp, $sp, -0x28", "sw $ra, 0x14($sp)", "jal func_x", "nop",
                   "lw $ra, 0x14($sp)", "jr $ra", "addiu $sp, $sp, 0x28"]
        with tempfile.TemporaryDirectory() as directory:
            candidate = self.write_candidate(Path(directory), smaller)
            lines = self.diff.frame_plan_lines(self.reference, candidate, "func_15000000", self.size, 0)
        self.assertEqual("frame-plan:", lines[0])
        self.assertIn("reference frame 0x30; candidate frame 0x28 (MISMATCH)", lines[1])

    def test_block_on_stack_rows_reports_a_missing_candidate_symbol(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "candidate.o"
            path.write_bytes(elf_object([("func_other", asm.words(asm.LEAF), None)]))
            lines = self.diff.frame_plan_lines(self.reference, path, "func_15000000", self.size, 2)
        self.assertEqual("frame-plan:", lines[0])
        self.assertIn("candidate plan unavailable (func_15000000 not found", lines[1])
        self.assertTrue(any("named-local homes >= 3 words" in line for line in lines))

    def test_reference_failure_is_reported_only_with_stack_rows(self):
        with tempfile.TemporaryDirectory() as directory:
            candidate = self.write_candidate(Path(directory), asm.SPILL_TEMPS)
            missing = self.diff.frame_plan_lines(self.reference, candidate, "func_missing", self.size, 1)
            self.assertEqual(1, len(missing))
            self.assertIn("frame-plan: unavailable", missing[0])
            self.assertEqual([], self.diff.frame_plan_lines(self.reference, candidate, "func_missing", self.size, 0))

    def test_compact_mismatch_prints_the_block_with_stack_rows(self):
        row = {
            "key": "sw", "is_data_ref": False,
            "base": {"mnemonic": "sw", "text": [{"text": "8:    sw v0,0x20(sp)"}]},
            "current": {"mnemonic": "sw", "text": [{"text": "8:    sw v0,0x18(sp)", "format": "stack"}]},
        }
        import json
        output = json.dumps({"current_score": 10, "rows": [row]})
        with tempfile.TemporaryDirectory() as directory:
            candidate = self.write_candidate(Path(directory), asm.SPILL_TEMPS)
            printed = io.StringIO()
            with redirect_stdout(printed):
                self.diff.print_compact_mismatch(output, "func_15000000", Path(directory),
                                                 frame_plan_inputs=(self.reference, candidate, self.size))
        text = printed.getvalue()
        self.assertIn("stack-rows: 1", text)
        self.assertLess(text.index("stack-rows: 1"), text.index("frame-plan:"))
        self.assertLess(text.index("frame-plan:"), text.index("diff-excerpt:"))
        self.assertIn("(match)", text)


class ProbeLayoutTests(unittest.TestCase):
    def test_layout_aligns_candidate_homes_with_the_reference_plan(self):
        reference = fixture_plan("spill_temps.s")
        locals_ = [probe.Local("param", "arg0", 0), probe.Local("param", "arg1", 4), probe.Local("param", "arg2", 8),
                   probe.Local("local", "result", -4), probe.Local("local", "output", -8), probe.Local("local", "found", -12)]
        lines = probe.layout_lines(0x28, 0x30, locals_, reference)
        self.assertEqual("frame: candidate 0x28, reference 0x30", lines[0])
        text = "\n".join(lines)
        self.assertRegex(text, r"\+0x0\s+0x28\s+param arg0\s+0x30\s+arg-in swc1 \$f12; lwc1 \[call-crossing\]")
        self.assertRegex(text, r"\+0x8\s+0x30\s+param arg2\s+0x38\s+arg-in sw \$a2; lwc1 \[call-crossing\]")
        self.assertRegex(text, r"-0x8\s+0x20\s+local output\s+0x28\s+local &-> \$a2; lw x2")
        self.assertRegex(text, r"-0x14\s+-\s+0x1c\s+local sw \$v1 \(delay\); lw \[call-crossing\]")
        self.assertRegex(text, r"-0x18\s+-\s+0x18\s+local unused")
        self.assertIn("lowest candidate local: 0x1c (3 named homes;", text)
        self.assertIn("reference areas: arg-out 0x0..0xf", text)
        self.assertIn("reference inferred: named-local homes >= 3 words", text)

    def test_layout_reports_an_unavailable_reference_plan(self):
        lines = probe.layout_lines(None, None, [probe.Local("param", "arg0", 0)], None, "no glabel")
        self.assertEqual("frame: candidate leaf, reference leaf", lines[0])
        self.assertIn("reference frame-plan: unavailable (no glabel)", lines)


if __name__ == "__main__":
    unittest.main()
