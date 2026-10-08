from __future__ import annotations

from contextlib import ExitStack, redirect_stdout
import io
from pathlib import Path
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import project_state as state
import prepare_nonmatching_asm


class DebuggerWorkflowTests(unittest.TestCase):
    def setUp(self):
        self.stack = ExitStack()
        self.addCleanup(self.stack.close)
        self.root = Path(self.stack.enter_context(tempfile.TemporaryDirectory()))
        self.stack.enter_context(patch.object(state, "ROOT", self.root))
        for name, path in {
            "FUNCTIONS_FILE": "progress/functions.json",
            "SOURCE_UNITS_FILE": "progress/source_units.json",
            "SUMMARY_FILE": "build/progress/summary.json",
            "DOCUMENT_FILE": "build/progress/progress.md",
            "OVERLAYS_FILE": "config/overlays.json",
        }.items():
            self.stack.enter_context(patch.object(state, name, self.root / path))
        state.write_json(state.FUNCTIONS_FILE, {"schema_version": 1, "functions": []})
        state.write_json(state.SOURCE_UNITS_FILE, {"schema_version": 1, "source_units": []})
        self.config = {"schema_version": 1, "overlays": {
            overlay: {"code_ranges": {region: {"start": "0x0", "end": "0x100"}
                                      for region in state.KNOWN_REGIONS}}
            for overlay in ("main", "game")
        }}
        self.config["overlays"]["debugger"] = {
            "code_ranges": {"us": {"start": "0x1008", "end": "0x1028"}}}
        state.write_json(state.OVERLAYS_FILE, self.config)
        self.source = "src/debugger/transport/test.c"
        self.profile = self.root / "config/profiles/us.yaml"
        self.profile.parent.mkdir(parents=True)
        self.profile.write_text("    subsegments:\n      - [0x0, asm]\n"
                                "      - [0x1008, c, debugger/transport/test]\n"
                                "      - [0x1028, data, debugger/data]\n")
        assembly = self.root / "reference/us/asm/debugger.s"
        assembly.parent.mkdir(parents=True)
        assembly.write_text("glabel func_80000000\n/* 0 80000000 00000000 */ nop\n" + "".join(
            f"glabel func_{0x16000000 + index * 16:X}\n" + "".join(
                f"/* {0x1008 + index * 16 + word * 4:X} {0x16000000 + index * 16 + word * 4:X} 00000000 */ nop\n"
                for word in range(4)) for index in range(3)))
        path = self.root / self.source
        path.parent.mkdir(parents=True)
        path.write_text('#include "types.h"\n\n' + "\n".join(
            state.global_asm_pragma(self.source, symbol)
            for symbol in ("func_16000000", "func_16000010")) + "\n")

    def register_args(self, **overrides):
        return SimpleNamespace(**{
            "overlay": "debugger", "source": self.source,
            "us_start": "0x1008", "us_end": "0x1028", "register_members": True,
            "evidence_kind": "structural_analysis", "evidence_reference": "review/debugger-unit",
            **overrides,
        })

    def test_discovery_uses_only_debugger_code_and_full_rom_reference(self):
        functions = state.parse_assembly_functions("us", "debugger")
        self.assertEqual(["func_16000000", "func_16000010"], [f.symbol for f in functions])
        self.assertEqual([(0x1008, 0x1018), (0x1018, 0x1028)], [(f.offset, f.end) for f in functions])
        self.assertEqual(self.root / "reference/us/asm", state.assembly_root("us", "debugger"))
        self.assertEqual(["func_80000000"], [f.symbol for f in state.parse_main_functions("us")])

    def test_us_only_progress_does_not_invent_pal_code(self):
        ranges = state.validate_code_ranges(self.config)
        result = state.code_progress([], [], ranges)
        self.assertEqual(32, result["overlays"]["debugger"]["total_bytes"])
        self.assertEqual({"us"}, set(result["overlays"]["debugger"]["regions"]))
        self.assertEqual(512, result["regions"]["eu"]["total_bytes"])
        self.assertEqual(544, result["regions"]["us"]["total_bytes"])

    def test_individual_registration_leaves_unit_unassigned(self):
        with redirect_stdout(io.StringIO()):
            state.register_debugger(SimpleNamespace(identifier="debugger_test", source=self.source, us="func_16000000"))
        record = state.load_json(state.FUNCTIONS_FILE)["functions"][0]
        self.assertEqual("debugger", record["overlay"])
        self.assertEqual({"us"}, set(record["regions"]))
        self.assertEqual(16, record["regions"]["us"]["size_bytes"])
        self.assertEqual([], state.load_json(state.SOURCE_UNITS_FILE)["source_units"])

    def test_explicit_review_can_adopt_exact_existing_scaffold_without_match_credit(self):
        original = (self.root / self.source).read_bytes()
        with redirect_stdout(io.StringIO()):
            state.register_source_unit(self.register_args())
        functions = state.validate_functions(state.load_json(state.FUNCTIONS_FILE))
        units = state.validate_source_units(state.load_json(state.SOURCE_UNITS_FILE), functions)
        self.assertEqual("mixed", units[0]["integration"])
        self.assertEqual(["func_16000000", "func_16000010"], units[0]["functions"])
        self.assertEqual(original, (self.root / self.source).read_bytes())
        self.assertEqual(0, state.summary(functions)["code_bytes"]["overlays"]["debugger"]["matched_bytes"])
        self.assertEqual("src/done/debugger/transport/test.c", state.completed_source_path(self.source, "debugger"))
        self.assertEqual("asm/us/nonmatchings/debugger/transport/test/func_16000000.s",
                         state.nonmatching_asm_path("src/done/debugger/transport/test.c", "func_16000000").as_posix())

    def test_scaffold_adoption_rejects_different_source_or_extent_without_writes(self):
        original = state.FUNCTIONS_FILE.read_bytes(), state.SOURCE_UNITS_FILE.read_bytes()
        for overrides in ({"source": "src/debugger/other.c"}, {"us_end": "0x1018"}):
            with self.subTest(overrides=overrides), self.assertRaises(state.ProjectStateError):
                state.register_source_unit(self.register_args(**overrides))
            self.assertEqual(original, (state.FUNCTIONS_FILE.read_bytes(), state.SOURCE_UNITS_FILE.read_bytes()))
        with self.assertRaisesRegex(state.ProjectStateError, "8-byte-aligned"):
            state.register_source_unit(self.register_args(us_start="0x100C"))

    def test_new_raw_unit_materializes_untouched_members_from_full_reference(self):
        (self.root / self.source).unlink()
        self.profile.write_text("    subsegments:\n      - [0x1008, asm]\n      - [0x1028, data]\n")
        with redirect_stdout(io.StringIO()):
            state.register_source_unit(self.register_args())
        with patch.object(prepare_nonmatching_asm, "ROOT", self.root):
            written = prepare_nonmatching_asm.materialize("us", self.source)
        self.assertEqual(2, len(written))
        for index, path in enumerate(written):
            self.assertIn(f"glabel func_{0x16000000 + index * 16:X}", path.read_text())
            self.assertNotIn("glabel func_80000000", path.read_text())
            self.assertEqual(4, path.read_text().count("/*"))

    def test_debugger_batch_and_integration_plans_select_full_rom_overlay(self):
        with redirect_stdout(io.StringIO()):
            state.register_debugger(SimpleNamespace(identifier="debugger_test", source=self.source, us="func_16000000"))
        functions = state.load_json(state.FUNCTIONS_FILE)["functions"]
        functions[0]["regions"]["us"]["state"] = "matched"
        output = io.StringIO()
        with patch.object(state, "validate_project", return_value=({}, functions)), redirect_stdout(output):
            state.batch_plan(["debugger_test"])
        self.assertEqual("debugger\n", output.getvalue())
        output = io.StringIO()
        with redirect_stdout(output):
            state.integration_plan(SimpleNamespace(symbol="debugger_test", all_reviewed=False))
        self.assertEqual("debugger\n", output.getvalue())


if __name__ == "__main__":
    unittest.main()
