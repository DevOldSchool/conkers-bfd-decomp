from __future__ import annotations

import importlib.util
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
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


if __name__ == "__main__":
    unittest.main()
