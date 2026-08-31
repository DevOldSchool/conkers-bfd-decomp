from __future__ import annotations

import importlib.util
import os
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location("diff_helper", ROOT / "scripts" / "diff.py")
assert SPEC is not None and SPEC.loader is not None
diff_helper = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(diff_helper)


class DiffReferenceTests(unittest.TestCase):
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
        with (
            patch.object(diff_helper, "ensure_reference") as ensure_reference,
            patch.object(diff_helper, "locate_function", return_value=assembly),
        ):
            result = diff_helper.ensure_reference_function(
                "us", "func_test", game_reference=True
            )

        self.assertEqual(assembly, result)
        ensure_reference.assert_called_once_with("us", game_reference=True)

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

    def test_rejects_invalid_json_evidence(self) -> None:
        with self.assertRaises(ValueError):
            diff_helper.current_difference_count('{"current_score": "0"}')

    def test_rejects_nonzero_difference_evidence(self) -> None:
        with self.assertRaisesRegex(ValueError, r"CURRENT \(10\)"):
            diff_helper.require_zero_difference('{"current_score": 10}', "func_test")

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
            watch=True,
        )

        self.assertIn("-m", command)
        self.assertIn("-w", command)
        self.assertIn("-3", command)
        self.assertNotIn("--no-pager", command)

    def test_keyboard_interrupt_exits_watch_without_a_traceback(self) -> None:
        with patch.object(diff_helper.subprocess, "run", side_effect=KeyboardInterrupt):
            self.assertEqual(
                130,
                diff_helper.run_asm_diff(["asm-differ"], Path("build/us/diff")),
            )
