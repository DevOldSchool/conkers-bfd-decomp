from __future__ import annotations

import importlib.util
import tempfile
import sys
import unittest
from unittest.mock import patch
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
SPEC = importlib.util.spec_from_file_location("compile_c", ROOT / "scripts" / "compile_c.py")
assert SPEC is not None and SPEC.loader is not None
compile_c = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(compile_c)


class CompileCTests(unittest.TestCase):
    def test_plain_source_uses_ido_directly(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "plain.c"
            source.write_text("void func_test(void) {}\n", encoding="utf-8")
            command = compile_c.compile_command("us", source, Path("build/plain.o"))

        self.assertEqual("/opt/ido/cc", command[0])
        self.assertNotIn("asm-processor", " ".join(command))

    def test_global_asm_source_uses_pinned_asm_processor(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "mixed.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/nonmatchings/unit/func_test.s")\n',
                encoding="utf-8",
            )
            command = compile_c.compile_command("us", source, Path("build/mixed.o"))

        rendered = " ".join(command)
        self.assertIn("/opt/tools/asm-processor/build.py", rendered)
        self.assertIn("/opt/tools/asm-processor/prelude.inc", rendered)
        self.assertIn("mips-linux-gnu-as", command)
        self.assertIn("-DPROFILE_US=1", command)

    def test_global_asm_text_in_a_comment_still_uses_ido_directly(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "focused.c"
            source.write_text(
                "/* Unmatched members use generated GLOBAL_ASM placeholders. */\n"
                "void func_test(void) {}\n",
                encoding="utf-8",
            )
            command = compile_c.compile_command(
                "us", source, Path("build/focused.o")
            )

        self.assertEqual("/opt/ido/cc", command[0])
        self.assertNotIn("asm-processor", " ".join(command))

    def test_command_construction_does_not_extract_or_write_assets(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            source = root / 'unit.c'
            source.write_text('#include "debugger-assets/ui.inc.c"\n')
            with patch.object(compile_c.subprocess, 'run', side_effect=AssertionError('executed')):
                command = compile_c.compile_command('us', source, root / 'unit.o', generated_dir=root / 'generated')
            self.assertIn(str(root / 'generated'), command)
            self.assertEqual(list(root.iterdir()), [source])

    def test_execution_prepares_once_unless_make_already_prepared_inputs(self):
        import debugger_assets
        with tempfile.TemporaryDirectory() as tmp:
            source = Path(tmp) / 'unit.c'
            source.write_text('#include "debugger-assets/ui.inc.c"\n')
            with patch.object(debugger_assets, 'prepare') as prepare, patch.object(compile_c.subprocess, 'run') as run:
                compile_c.run_compile('us', source, Path(tmp) / 'unit.o', check=True)
                prepare.assert_called_once()
                run.assert_called_once()
                prepare.reset_mock()
                compile_c.run_compile('us', source, Path(tmp) / 'unit.o', inputs_prepared=True, check=True)
                prepare.assert_not_called()

    def test_compile_without_directive_drops_only_named_pinned_flags(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "unit.c"
            source.write_text(
                "/* Reviewed source unit: src/main/unit.c */\n"
                "/* CONKER_COMPILE_WITHOUT: -g3 */\n"
                "void func_test(void) {}\n",
                encoding="utf-8",
            )
            command = compile_c.compile_command("us", source, Path("build/unit.o"))

        self.assertNotIn("-g3", command)
        self.assertIn("-O2", command)
        self.assertIn("-g3", compile_c.compiler_flags("us"))
        self.assertEqual(compile_c.compiler_flags("us", "void f(void) {}\n"), compile_c.compiler_flags("us"))

    def test_compile_without_directive_rejects_other_flags_and_repeats(self) -> None:
        for text in (
            "/* CONKER_COMPILE_WITHOUT: -O2 */\n",
            "/* CONKER_COMPILE_WITHOUT: -g3 -O2 */\n",
            "/* CONKER_COMPILE_WITHOUT: */\n",
            "/* CONKER_COMPILE_WITHOUT: -g3 */\n/* CONKER_COMPILE_WITHOUT: -g3 */\n",
        ):
            with self.subTest(text=text), self.assertRaises(ValueError):
                compile_c.compiler_flags("us", text)
        self.assertEqual(compile_c.dropped_flags("/* mentions CONKER_COMPILE_WITHOUT: -g3 in prose */\n"), ())


if __name__ == "__main__":
    unittest.main()

class SourceReadTests(unittest.TestCase):
    def test_execution_reads_source_once_and_shares_it_with_command_builder(self):
        with patch.object(Path, 'read_text', return_value='void f(void) {}') as read, \
             patch.object(compile_c.subprocess, 'run'):
            compile_c.run_compile('us', Path('candidate.c'), Path('candidate.o'))
        read.assert_called_once_with(encoding='utf-8')
