from __future__ import annotations

import importlib.util
import json
import os
import subprocess
import sys
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout
from io import StringIO
from pathlib import Path
from unittest.mock import patch


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location("diff_helper", ROOT / "scripts" / "diff.py")
assert SPEC is not None and SPEC.loader is not None
diff_helper = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(diff_helper)


class DiffReferenceTests(unittest.TestCase):
    def test_table_gate_blocks_zero_in_diagnosis_and_authoritative_diff(self):
        from unittest.mock import Mock
        evidence = subprocess.CompletedProcess([], 0, json.dumps({"current_score": 0, "rows": []}), "")
        for runner in (diff_helper.run_required_asm_diff, diff_helper.run_diagnose_diff):
            gate = Mock(side_effect=ValueError("case table differs from ROM"))
            output = StringIO()
            with patch.object(diff_helper.subprocess, "run", return_value=evidence), redirect_stdout(output), redirect_stderr(output):
                status = runner(Path("candidate.o"), Path("reference.o"), "func_test", Path("unused"), 4, table_check=gate)
            self.assertEqual(diff_helper.EXIT_BLOCKED_TOOLING, status)
            gate.assert_called_once()
            self.assertNotIn("CURRENT (0)", output.getvalue())
            self.assertIn("case table differs", output.getvalue())

    def test_reuses_existing_game_reference(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            assembly = temporary_root / "reference" / "game" / "us" / "asm" / "game.s"
            assembly.parent.mkdir(parents=True)
            assembly.write_text("glabel func_test\n", encoding="utf-8")

            with (
                patch.object(diff_helper, "ROOT", temporary_root),
                patch.object(diff_helper, "prepare_reference") as prepare_reference,
            ):
                diff_helper.ensure_reference("us", game_reference=True)

            prepare_reference.assert_not_called()

    def test_prepares_missing_game_reference(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            with (
                patch.object(diff_helper, "ROOT", Path(temporary_directory)),
                patch.object(diff_helper, "prepare_reference") as prepare_reference,
            ):
                diff_helper.ensure_reference("us", game_reference=True)

            prepare_reference.assert_called_once_with("us", game_reference=True)

    def test_prepares_empty_main_reference(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            (temporary_root / "reference" / "us" / "asm").mkdir(parents=True)

            with (
                patch.object(diff_helper, "ROOT", temporary_root),
                patch.object(diff_helper, "prepare_reference") as prepare_reference,
            ):
                diff_helper.ensure_reference("us")

            prepare_reference.assert_called_once_with("us", game_reference=False)

    def test_reference_function_returns_the_located_assembly(self) -> None:
        assembly = Path("reference/game/us/asm/game.s")
        extracted = Path("build/m2c/asm/func_test.s")
        with (
            patch.object(diff_helper, "ensure_reference") as ensure_reference,
            patch.object(diff_helper, "locate_function", return_value=assembly),
            patch.object(diff_helper, "registered_symbols", return_value={"func_test"}),
            patch.object(diff_helper, "extract_function", return_value=extracted) as extract,
        ):
            result = diff_helper.ensure_reference_function(
                "us", "func_test", game_reference=True
            )

        self.assertEqual(extracted, result)
        ensure_reference.assert_called_once_with("us", game_reference=True)
        extract.assert_called_once_with(
            assembly, "func_test", boundary_symbols={"func_test"}
        )

    def test_expected_size_stops_at_an_overlapping_registered_symbol(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            inventory = temporary_root / "progress" / "functions.json"
            inventory.parent.mkdir(parents=True)
            inventory.write_text(
                '{"functions":['
                '{"symbol":"func_parent","overlay":"game","regions":{"us":'
                '{"symbol":"func_15000000","vram":"0x15000000","size_bytes":20}}},'
                '{"symbol":"func_tail","overlay":"game","regions":{"us":'
                '{"symbol":"func_1500000C","vram":"0x1500000C","size_bytes":8}}},'
                '{"symbol":"func_main","overlay":"main","regions":{"us":'
                '{"symbol":"func_80000008","vram":"0x15000008","size_bytes":4}}}'
                "]}",
                encoding="utf-8",
            )

            with patch.object(diff_helper, "ROOT", temporary_root):
                size = diff_helper.expected_function_size("us", "func_15000000")

            self.assertEqual(12, size)

    def test_expected_size_uses_reviewed_source_unit_when_record_is_legacy(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            progress = temporary_root / "progress"
            progress.mkdir(parents=True)
            (progress / "functions.json").write_text(
                '{"functions":['
                '{"symbol":"func_target","overlay":"game","regions":{"us":'
                '{"symbol":"func_15000000","vram":"0x15000000"}}},'
                '{"symbol":"func_tail","overlay":"game","regions":{"us":'
                '{"symbol":"func_15000060","vram":"0x15000060","size_bytes":4}}}'
                "]}",
                encoding="utf-8",
            )
            (progress / "source_units.json").write_text(
                '{"source_units":[{"source":"src/game/test.c",'
                '"functions":["func_target","func_tail"],'
                '"regions":{"us":{"start":"0x100","end":"0x164"}}}]}',
                encoding="utf-8",
            )

            with patch.object(diff_helper, "ROOT", temporary_root):
                size = diff_helper.expected_function_size("us", "func_15000000")

            self.assertEqual(96, size)

    def test_resolves_game_overlay_from_work_item_id(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            inventory = temporary_root / "progress" / "functions.json"
            inventory.parent.mkdir(parents=True)
            inventory.write_text(
                '{"functions":[{"symbol":"func_test","overlay":"game",'
                '"source":"src/game/test.c","regions":{"us":{"symbol":"func_15000000"}}}]}',
                encoding="utf-8",
            )

            with patch.object(diff_helper, "ROOT", temporary_root):
                source, symbol, is_game = diff_helper.find_work_item_by_id("func_test", "us")

            self.assertEqual(temporary_root / "src" / "game" / "test.c", source)
            self.assertEqual("func_15000000", symbol)
            self.assertTrue(is_game)

    def test_reads_zero_difference_json_evidence(self) -> None:
        self.assertEqual(0, diff_helper.current_difference_count('{"current_score": 0}'))

    def test_activates_a_deferred_candidate_without_editing_source(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            source = temporary_root / "src" / "game" / "test.c"
            content = (
                "#if 0 /* CONKER_DEFERRED_CANDIDATE func_test CURRENT (35) */\n"
                "void func_test(void) {}\n"
                "#endif /* CONKER_DEFERRED_CANDIDATE func_test */\n"
                '#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\n'
            )
            with patch.object(diff_helper, "ROOT", temporary_root):
                activated = diff_helper.activate_deferred_candidate(
                    content, source, "func_test"
                )

            self.assertEqual("void func_test(void) {}\n", activated)

    def test_classifies_register_only_diff_rows(self) -> None:
        rows = [
            {
                "key": None,
                "base": {"mnemonic": "or", "text": [{"text": "or t8,t7,at"}]},
                "current": {"mnemonic": "or", "text": [{"text": "or t7,t6,at"}]},
            },
            {
                "key": None,
                "base": {"mnemonic": "beq", "text": [{"text": "beq t0,zero,10"}]},
                "current": {"mnemonic": "bne", "text": [{"text": "bne t0,zero,10"}]},
            },
        ]

        counts = diff_helper.classify_diff_rows(rows)

        self.assertEqual(1, counts["register_only"])
        self.assertEqual(1, counts["opcode_or_control_flow"])

    def test_diagnose_uses_the_full_registered_span(self) -> None:
        evidence = subprocess.CompletedProcess(
            args=["asm-differ"],
            returncode=0,
            stdout='{"current_score": 0, "rows": []}',
            stderr="",
        )
        with (
            patch.object(diff_helper.subprocess, "run", return_value=evidence) as run,
            redirect_stdout(StringIO()),
        ):
            result = diff_helper.run_diagnose_diff(
                Path("candidate.o"),
                Path("reference.o"),
                "func_test",
                Path("build/us/diff"),
                20,
            )

        self.assertEqual(0, result)
        command = run.call_args.args[0]
        self.assertEqual("5", command[command.index("--max-lines") + 1])
        self.assertNotIn("--stop-at-ret", command)

    def test_diagnose_mismatch_saves_compact_evidence_in_one_pass(self) -> None:
        row = {
            "base": {"mnemonic": "nop", "text": [{"text": "0: nop"}]},
        }
        raw = json.dumps({"current_score": 100, "rows": [row] * 10})
        output = StringIO()
        with tempfile.TemporaryDirectory() as temporary_directory:
            directory = Path(temporary_directory)
            with (
                patch.object(diff_helper.subprocess, "run", return_value=subprocess.CompletedProcess([], 0, raw, "")) as run,
                redirect_stdout(output),
            ):
                result = diff_helper.run_diagnose_diff(Path("candidate.o"), Path("reference.o"), "func_test", directory, 40)
            self.assertEqual(0, result)
            run.assert_called_once()
            self.assertEqual(raw, (directory / "func_test/mismatch.json").read_text())
            self.assertEqual(10, (directory / "func_test/mismatch.txt").read_text().count("0: nop"))
        self.assertIn("missing-or-extra: 10", output.getvalue())
        self.assertIn("first 5 of 10", output.getvalue())
        self.assertEqual(5, output.getvalue().count("0: nop"))

    def test_diagnose_artifact_failure_blocks_preflight(self) -> None:
        evidence = subprocess.CompletedProcess([], 0, '{"current_score": 100, "rows": []}', "")
        with (
            patch.object(diff_helper.subprocess, "run", return_value=evidence),
            patch.object(diff_helper, "print_compact_mismatch", side_effect=OSError("disk full")),
            redirect_stderr(StringIO()),
        ):
            result = diff_helper.run_diagnose_diff(Path("candidate.o"), Path("reference.o"), "func_test", Path("unused"), 4)
        self.assertEqual(diff_helper.EXIT_BLOCKED_TOOLING, result)

    def test_register_annotations_do_not_hide_other_differences(self) -> None:
        for mnemonic, text, format_name, category in (
            ("addiu", "4:    addiu t1,t1,2", "immediate", "operand_or_constant"),
            ("addiu", "4:    addiu t1,t1,2", "rotation", "operand_or_constant"),
            ("lw", "4:    lw t1,8(sp)", "stack", "opcode_or_control_flow"),
            ("ori", "4:    ori t1,t1,1", "register", "opcode_or_control_flow"),
        ):
            with self.subTest(text=text, format=format_name):
                row = {
                    "key": "candidate",
                    "base": {"mnemonic": "addiu", "text": [
                        {"text": "0:    addiu t0,t0,1", "format": "register"},
                    ]},
                    "current": {"mnemonic": mnemonic, "text": [
                        {"text": text, "format": format_name},
                    ]},
                }
                self.assertEqual(category, diff_helper.diff_row_category(row))

    def test_classifier_ignores_offsets_and_decorative_branch_rotation(self) -> None:
        row = {
            "key": "nop",
            "base": {"mnemonic": "nop", "text": [
                {"text": "0:    nop"},
            ]},
            "current": {"mnemonic": "nop", "text": [
                {"text": "4: "}, {"text": "~>", "format": "rotation"}, {"text": " nop"},
            ]},
        }
        self.assertIsNone(diff_helper.diff_row_category(row))
        row["base"] = {"mnemonic": "or", "text": [{"text": "0:    or t0,t1,zero"}]}
        row["current"] = {"mnemonic": "or", "text": [{"text": "4:    or t2,t3,zero"}]}
        self.assertEqual("register_only", diff_helper.diff_row_category(row))

    def test_relocated_relative_branch_uses_encoded_displacement(self) -> None:
        # func_15053894: object location changes, branch encoding does not.
        row = {
            "base": {"mnemonic": "bnez", "line": 0x18, "branch": 0x28,
                     "text": [{"text": "18: bnez at,28 "}, {"text": "~>", "format": "rotation"}]},
            "current": {"mnemonic": "bnez", "line": 0x98, "branch": 0xA8,
                        "text": [{"text": " 56 98: bnez at,a8 "}, {"text": "~>", "format": "rotation"}]},
        }
        self.assertIsNone(diff_helper.diff_row_category(row))
        row["current"]["text"][0]["text"] = "98: bnez t0,a8 "
        self.assertEqual("register_only", diff_helper.diff_row_category(row))
        row["current"]["branch"] = 0xAC
        row["current"]["text"][0]["text"] = "98: bnez t0,ac "
        self.assertEqual("operand_or_constant", diff_helper.diff_row_category(row))

    def test_branch_normalization_requires_consistent_metadata_and_relative_opcode(self) -> None:
        for mnemonic, metadata in (("bnez", {}), ("bnez", {"line": 0x98, "branch": 0xAC}),
                                   ("j", {"line": 0x98, "branch": 0xA8})):
            row = {
                "base": {"mnemonic": mnemonic, "line": 0x18, "branch": 0x28,
                         "text": [{"text": f"18: {mnemonic} 28"}]},
                "current": {"mnemonic": mnemonic, **metadata,
                            "text": [{"text": f"98: {mnemonic} a8"}]},
            }
            with self.subTest(mnemonic=mnemonic, metadata=metadata):
                self.assertEqual("operand_or_constant", diff_helper.diff_row_category(row))

    def test_classifier_counts_stack_and_missing_rows(self) -> None:
        base = {"mnemonic": "lw", "text": [{"text": "0: lw t0,4(sp)"}]}
        current = {"mnemonic": "lw", "text": [{"text": "0: lw t1,8(sp)", "format": "rotation"}]}
        counts = diff_helper.classify_diff_rows([
            {"base": base, "current": current}, {"base": base}, {"current": current},
            {"is_data_ref": True, "base": base},
        ])
        self.assertEqual(1, counts["operand_or_constant"])
        self.assertEqual(2, counts["missing_or_extra"])
        self.assertEqual(0, counts["register_only"])

    def test_classifier_counts_marker_only_cell_as_missing_instruction(self) -> None:
        # Row shape captured from the func_1507E73C pilot's pinned-differ JSON.
        row = {
            "key": None, "is_data_ref": False,
            "base": {"text": [
                {"text": "2c:", "format": "diff_remove"}, {"text": "    "},
                {"text": "move    v0,v1", "format": "diff_remove"},
            ], "mnemonic": "move", "line": 44},
            "current": {"text": [
                {"text": "<", "format": "diff_remove"}, {"text": "      "},
            ]},
        }
        added = {
            "key": "move", "base": {"text": [{"text": ">", "format": "diff_add"}]},
            "current": row["base"],
        }
        for evidence in (row, added):
            with self.subTest(evidence=evidence):
                counts = diff_helper.classify_diff_rows([evidence])
                self.assertEqual({
                    "register_only": 0, "operand_or_constant": 0,
                    "opcode_or_control_flow": 0, "missing_or_extra": 1,
                }, counts)

    def test_classifier_ignores_pinned_differ_source_line_prefixes(self) -> None:
        row = {
            "key": "addiu\tsp,sp,-0x18", "is_data_ref": False,
            "base": {"text": [{"text": "0:    addiu   sp,sp,-0x18"}],
                     "mnemonic": "addiu", "line": 0},
            "current": {"text": [
                {"text": " "}, {"text": "   48", "format": "source_line_num"},
                {"text": " 88:    addiu   sp,sp,-0x18"},
            ], "mnemonic": "addiu", "line": 136, "src_line": 48},
        }
        self.assertIsNone(diff_helper.diff_row_category(row))
        row["current"]["text"] = [
            {"text": "r   48", "format": "register"},
            {"text": " 88:    addiu   sp,t0,-0x18", "format": "rotation"},
        ]
        self.assertEqual("register_only", diff_helper.diff_row_category(row))

    def test_diagnosis_does_not_recommend_permutation_with_changed_operands(self) -> None:
        output = StringIO()
        with redirect_stdout(output):
            diff_helper.print_diagnosis("func_test", 10, {
                "register_only": 2, "operand_or_constant": 1,
                "opcode_or_control_flow": 0, "missing_or_extra": 0,
            })
        self.assertNotIn("bounded declaration/lifetime permutation", output.getvalue())

    def test_compact_mismatch_reuses_evidence_and_saves_full_details(self) -> None:
        row = {
            "key": "or",
            "base": {"mnemonic": "or", "text": [{"text": "0:    or t0,t1,zero"}]},
            "current": {"mnemonic": "or", "text": [{"text": "0:    or t2,t3,zero"}]},
        }
        raw = json.dumps({"current_score": 80, "rows": [row] * 20})
        evidence = subprocess.CompletedProcess([], 0, raw, "")
        output = StringIO()
        with tempfile.TemporaryDirectory() as temporary_directory:
            directory = Path(temporary_directory)
            with (
                patch.object(diff_helper.subprocess, "run", return_value=evidence) as run,
                patch.object(diff_helper, "run_asm_diff") as display,
                redirect_stdout(output), redirect_stderr(StringIO()),
            ):
                result = diff_helper.run_required_asm_diff(
                    Path("candidate.o"), Path("reference.o"), "func_test", directory, 80,
                    compact_mismatch=True,
                )
            self.assertEqual(diff_helper.EXIT_MISMATCH, result)
            run.assert_called_once()
            display.assert_not_called()
            command = run.call_args.args[0]
            self.assertEqual("20", command[command.index("--max-lines") + 1])
            self.assertNotIn("--stop-at-ret", command)
            self.assertEqual(raw, (directory / "func_test/mismatch.json").read_text())
            self.assertEqual(20, (directory / "func_test/mismatch.txt").read_text().count("or t0,t1,zero"))
        text = output.getvalue()
        self.assertIn("CURRENT (80)", text)
        self.assertIn("register-only: 20", text)
        self.assertIn("bounded declaration/lifetime permutation", text)
        self.assertIn("first 5 of 20", text)
        self.assertEqual(5, text.count("or t0,t1,zero"))
        self.assertIn("full-diff:", text)
        self.assertIn("diff-evidence:", text)

    def test_compact_mismatch_rejects_malformed_diagnostics_without_rerunning(self) -> None:
        for rows in (None, [None], [{"base": None}], [{"base": {"text": [1]}}]):
            with self.subTest(rows=rows), tempfile.TemporaryDirectory() as temporary_directory:
                evidence = subprocess.CompletedProcess([], 0, json.dumps({"current_score": 10, "rows": rows}), "")
                with (
                    patch.object(diff_helper.subprocess, "run", return_value=evidence) as run,
                    patch.object(diff_helper, "run_asm_diff") as display,
                    redirect_stderr(StringIO()),
                ):
                    result = diff_helper.run_required_asm_diff(
                        Path("candidate.o"), Path("reference.o"), "func_test",
                        Path(temporary_directory), 4, compact_mismatch=True,
                    )
                self.assertEqual(diff_helper.EXIT_BLOCKED_TOOLING, result)
                run.assert_called_once()
                display.assert_not_called()

    def test_compact_artifact_failure_blocks_match(self) -> None:
        evidence = subprocess.CompletedProcess([], 0, '{"current_score": 10, "rows": []}', "")
        with (
            patch.object(diff_helper.subprocess, "run", return_value=evidence),
            patch.object(Path, "mkdir", side_effect=OSError("read-only")),
            redirect_stderr(StringIO()),
        ):
            result = diff_helper.run_required_asm_diff(
                Path("candidate.o"), Path("reference.o"), "func_test", Path("unused"), 4,
                compact_mismatch=True,
            )
        self.assertEqual(diff_helper.EXIT_BLOCKED_TOOLING, result)

    def test_compact_exact_match_does_not_write_mismatch_artifacts(self) -> None:
        evidence = subprocess.CompletedProcess([], 0, '{"current_score": 0}', "")
        with (
            patch.object(diff_helper.subprocess, "run", return_value=evidence) as run,
            patch.object(diff_helper, "print_compact_mismatch") as summarize,
            redirect_stdout(StringIO()),
        ):
            result = diff_helper.run_required_asm_diff(
                Path("candidate.o"), Path("reference.o"), "func_test", Path("unused"), 4,
                compact_mismatch=True,
            )
        self.assertEqual(0, result)
        run.assert_called_once()
        summarize.assert_not_called()

    def test_rejects_invalid_json_evidence(self) -> None:
        with self.assertRaises(ValueError):
            diff_helper.current_difference_count('{"current_score": "0"}')

    def test_rejects_nonzero_difference_evidence(self) -> None:
        with self.assertRaisesRegex(ValueError, r"CURRENT \(10\)"):
            diff_helper.require_zero_difference('{"current_score": 10}', "func_test")

    def test_score_only_diff_prints_current_score(self) -> None:
        evidence = subprocess.CompletedProcess(
            args=["asm-differ"],
            returncode=0,
            stdout='{"current_score": 45}',
            stderr="",
        )
        output = StringIO()
        with (
            patch.object(diff_helper.subprocess, "run", return_value=evidence) as run,
            redirect_stdout(output),
        ):
            result = diff_helper.run_score_only_diff(
                Path("candidate.o"),
                Path("reference.o"),
                "func_test",
                Path("build/us/diff"),
                4,
            )

        self.assertEqual(0, result)
        self.assertEqual("45\n", output.getvalue())
        command = run.call_args.args[0]
        self.assertEqual("1", command[command.index("--max-lines") + 1])
        self.assertNotIn("--stop-at-ret", command)

    def test_required_diff_displays_normal_diff_on_mismatch(self) -> None:
        evidence = subprocess.CompletedProcess(
            args=["asm-differ"],
            returncode=0,
            stdout='{"current_score": 10}',
            stderr="",
        )
        with (
            patch.object(diff_helper.subprocess, "run", return_value=evidence),
            patch.object(diff_helper, "run_asm_diff", return_value=0) as display,
        ):
            result = diff_helper.run_required_asm_diff(
                Path("candidate.o"),
                Path("reference.o"),
                "func_test",
                Path("build/us/diff"),
                4,
            )

        self.assertEqual(1, result)
        display_command, display_directory = display.call_args.args
        self.assertIn("color", display_command)
        self.assertEqual(Path("build/us/diff"), display_directory)

    def test_required_diff_does_not_render_twice_on_exact_match(self) -> None:
        evidence = subprocess.CompletedProcess(
            args=["asm-differ"],
            returncode=0,
            stdout='{"current_score": 0}',
            stderr="",
        )
        with (
            patch.object(diff_helper.subprocess, "run", return_value=evidence),
            patch.object(diff_helper, "run_asm_diff") as display,
        ):
            result = diff_helper.run_required_asm_diff(
                Path("candidate.o"),
                Path("reference.o"),
                "func_test",
                Path("build/us/diff"),
                4,
            )

        self.assertEqual(0, result)
        display.assert_not_called()

    def test_required_diff_classifies_invalid_evidence_as_tooling_failure(self) -> None:
        evidence = subprocess.CompletedProcess(
            args=["asm-differ"],
            returncode=0,
            stdout="not-json",
            stderr="",
        )
        with patch.object(diff_helper.subprocess, "run", return_value=evidence):
            result = diff_helper.run_required_asm_diff(
                Path("candidate.o"),
                Path("reference.o"),
                "func_test",
                Path("build/us/diff"),
                4,
            )

        self.assertEqual(diff_helper.EXIT_BLOCKED_TOOLING, result)

    def test_required_diff_uses_the_full_registered_span(self) -> None:
        evidence = subprocess.CompletedProcess(
            args=["asm-differ"],
            returncode=0,
            stdout='{"current_score": 10}',
            stderr="",
        )
        with (
            patch.object(diff_helper.subprocess, "run", return_value=evidence) as run,
            patch.object(diff_helper, "run_asm_diff", return_value=0) as display,
        ):
            result = diff_helper.run_required_asm_diff(
                Path("candidate.o"),
                Path("reference.o"),
                "func_test",
                Path("build/us/diff"),
                20,
            )

        self.assertEqual(diff_helper.EXIT_MISMATCH, result)
        display.assert_called_once()
        evidence_command = run.call_args.args[0]
        display_command = display.call_args.args[0]
        for command in (evidence_command, display_command):
            self.assertEqual("5", command[command.index("--max-lines") + 1])
            self.assertNotIn("--stop-at-ret", command)

    def test_required_diff_classifies_asm_differ_launch_failure_as_tooling(self) -> None:
        with patch.object(diff_helper.subprocess, "run", side_effect=OSError("missing")):
            result = diff_helper.run_required_asm_diff(
                Path("candidate.o"),
                Path("reference.o"),
                "func_test",
                Path("build/us/diff"),
                4,
            )

        self.assertEqual(diff_helper.EXIT_BLOCKED_TOOLING, result)

    def test_main_classifies_candidate_compile_failure(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            source = Path(temporary_directory) / "test.c"
            source.write_text("void func_test(void) {}\n", encoding="utf-8")
            with (
                patch.object(
                    sys,
                    "argv",
                    ["diff.py", "us", "func_test", "--auto-overlay"],
                ),
                patch.object(
                    diff_helper,
                    "find_work_item_by_id",
                    return_value=(source, "func_test", True),
                ),
                patch.object(
                    diff_helper,
                    "ensure_reference_function",
                    return_value=Path("reference.s"),
                ),
                patch.object(diff_helper, "expected_function_size", return_value=4),
                patch.object(diff_helper, "require_c_implementation"),
                patch.object(
                    diff_helper,
                    "compile_candidate",
                    side_effect=subprocess.CalledProcessError(1, ["cc"]),
                ),
            ):
                result = diff_helper.main()

        self.assertEqual(diff_helper.EXIT_FIX_COMPILE, result)

    def test_main_classifies_resolution_failure_as_tooling(self) -> None:
        with (
            patch.object(
                sys,
                "argv",
                ["diff.py", "us", "func_test", "--auto-overlay"],
            ),
            patch.object(
                diff_helper,
                "find_work_item_by_id",
                side_effect=ValueError("unknown work item"),
            ),
        ):
            result = diff_helper.main()

        self.assertEqual(diff_helper.EXIT_BLOCKED_TOOLING, result)

    def test_candidate_object_uses_the_makefile_output_path(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            source = temporary_root / "src" / "game" / "test.c"

            with patch.object(diff_helper, "ROOT", temporary_root):
                output = diff_helper.candidate_object("us", source)

            self.assertEqual(temporary_root / "build" / "us" / "src" / "game" / "test.o", output)

    def test_focused_candidate_source_removes_only_global_asm_pragmas(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            source = temporary_root / "src" / "game" / "test.c"
            source.parent.mkdir(parents=True)
            source.write_text(
                '#include "types.h"\n'
                '#pragma GLOBAL_ASM("asm/nonmatchings/test/func_old.s")\n'
                'void func_test(s32 arg0) {\n'
                '    (void)arg0;\n'
                '}\n',
                encoding="utf-8",
            )

            with patch.object(diff_helper, "ROOT", temporary_root):
                focused = diff_helper.focused_candidate_source("us", source)

            self.assertEqual(
                temporary_root / "build" / "us" / "diff-source" / "src" / "game" / "test.c",
                focused,
            )
            self.assertEqual(
                '#include "types.h"\n\n'
                'void func_test(s32 arg0) {\n'
                '    (void)arg0;\n'
                '}\n',
                focused.read_text(encoding="utf-8"),
            )

    def test_compile_candidate_uses_absolute_paths_from_any_working_directory(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            source = temporary_root / "src" / "game" / "test.c"
            focused = temporary_root / "build" / "us" / "diff-source" / "test.c"
            output = temporary_root / "build" / "us" / "src" / "game" / "test.o"
            source.parent.mkdir(parents=True)
            source.write_text("void func_test(void) {}\n", encoding="utf-8")
            with (
                patch.object(diff_helper, "ROOT", temporary_root),
                patch.object(diff_helper, "candidate_object", return_value=output),
                patch.object(diff_helper, "focused_candidate_source", return_value=focused),
                patch.object(diff_helper.compile_c, "compile_command", return_value=["true"]) as command,
                patch.object(diff_helper.subprocess, "run") as run,
            ):
                self.assertEqual(output, diff_helper.compile_candidate("us", source))

            command.assert_called_once_with("us", focused, output)
            run.assert_called_once_with(["true"], cwd=temporary_root, check=True)

    def test_rejects_a_target_still_supplied_by_global_asm(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            source = temporary_root / "src" / "game" / "test.c"
            source.parent.mkdir(parents=True)
            source.write_text(
                '#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\n',
                encoding="utf-8",
            )
            with (
                patch.object(diff_helper, "ROOT", temporary_root),
                self.assertRaisesRegex(ValueError, "still supplied by GLOBAL_ASM"),
            ):
                diff_helper.require_c_implementation(source, "func_test")

    def test_reuses_current_reference_object(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            assembly = temporary_root / "reference" / "game" / "us" / "asm" / "game.s"
            normalizer = temporary_root / "scripts" / "normalize_asm.py"
            macros = temporary_root / "include" / "macro.inc"
            toolchain = temporary_root / "Dockerfile"
            output = temporary_root / "build" / "us" / "reference-objects" / "game" / "us" / "asm" / "game.o"
            for path in (assembly, normalizer, macros, toolchain, output):
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text("\n", encoding="utf-8")
            for path in (assembly, normalizer, macros, toolchain):
                os.utime(path, ns=(1_000_000_000, 1_000_000_000))
            os.utime(output, ns=(2_000_000_000, 2_000_000_000))

            with (
                patch.object(diff_helper, "ROOT", temporary_root),
                patch.object(diff_helper, "NORMALIZE_ASM", normalizer),
                patch.object(diff_helper, "ASSEMBLY_MACROS", macros),
                patch.object(diff_helper, "TOOLCHAIN_DEFINITION", toolchain),
                patch.object(diff_helper, "locate_function", return_value=assembly),
                patch.object(diff_helper.subprocess, "run") as run,
            ):
                result = diff_helper.reference_object("us", "func_test", game_reference=True)

            self.assertEqual(output, result)
            run.assert_not_called()

    def test_compiles_an_extracted_reference_span_outside_reference_tree(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            assembly = temporary_root / "build" / "m2c" / "asm" / "func_test.s"
            assembly.parent.mkdir(parents=True)
            assembly.write_text("glabel func_test\n", encoding="utf-8")
            normalizer = temporary_root / "scripts" / "normalize_asm.py"
            normalizer.parent.mkdir(parents=True)
            normalizer.write_text("", encoding="utf-8")
            macros = temporary_root / "include" / "macro.inc"
            macros.parent.mkdir(parents=True)
            macros.write_text("", encoding="utf-8")
            toolchain = temporary_root / "Dockerfile"
            toolchain.write_text("", encoding="utf-8")

            with (
                patch.object(diff_helper, "ROOT", temporary_root),
                patch.object(diff_helper, "NORMALIZE_ASM", normalizer),
                patch.object(diff_helper, "ASSEMBLY_MACROS", macros),
                patch.object(diff_helper, "TOOLCHAIN_DEFINITION", toolchain),
                patch.object(diff_helper.subprocess, "run") as run,
            ):
                result = diff_helper.reference_object(
                    "us", "func_test", assembly=assembly
                )

            self.assertEqual(
                temporary_root
                / "build"
                / "us"
                / "reference-objects"
                / "build"
                / "m2c"
                / "asm"
                / "func_test.o",
                result,
            )
            self.assertEqual(2, run.call_count)

    def test_watch_settings_use_the_focused_candidate_compiler(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            source = temporary_root / "src" / "game" / "test.c"

            with patch.object(diff_helper, "ROOT", temporary_root):
                directory = diff_helper.write_settings("us", source)

            content = (directory / "diff_settings.py").read_text(encoding="utf-8")
            self.assertIn("scripts/compile_diff_candidate.py", content)
            self.assertIn("'--profile', 'us', '--source', SOURCE", content)
            self.assertIn("def map_build_target", content)
            self.assertIn("return [SOURCE, os.path.join(ROOT, 'include')]", content)

    def test_watch_command_keeps_asm_differ_alive(self) -> None:
        command = diff_helper.asm_diff_command(
            Path("candidate.o"),
            Path("reference.o"),
            "func_test",
            4,
            watch=True,
        )

        self.assertIn("-m", command)
        self.assertIn("-w", command)
        self.assertIn("-3", command)
        self.assertNotIn("--no-pager", command)

    def test_focused_command_uses_the_full_registered_instruction_span(self) -> None:
        command = diff_helper.asm_diff_command(
            Path("candidate.o"),
            Path("reference.o"),
            "func_test",
            20,
            require_match=True,
        )

        self.assertEqual("5", command[command.index("--max-lines") + 1])
        self.assertNotIn("--stop-at-ret", command)

    def test_keyboard_interrupt_exits_watch_without_a_traceback(self) -> None:
        with patch.object(diff_helper.subprocess, "run", side_effect=KeyboardInterrupt):
            self.assertEqual(
                130,
                diff_helper.run_asm_diff(["asm-differ"], Path("build/us/diff")),
            )
