from __future__ import annotations

import importlib.util
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
SPEC = importlib.util.spec_from_file_location(
    "bootstrap_symbols", ROOT / "scripts" / "create_bootstrap_symbols.py"
)
assert SPEC is not None and SPEC.loader is not None
bootstrap_symbols = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(bootstrap_symbols)


class BootstrapSymbolsTests(unittest.TestCase):
    def test_collects_explicit_completed_sources_alongside_assembly_directory(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            assembly = root / "asm"
            assembly.mkdir()
            (assembly / "main.s").write_text("jal func_80001050\n")
            source = root / "src/done/platform/system.c"
            source.parent.mkdir(parents=True)
            source.write_text("extern int D_8002D4B0;\n")
            (source.parent / "unmapped.c").write_text("extern int D_8002FFFF;\n")

            symbols = bootstrap_symbols.collect_symbols([assembly, source])

        self.assertEqual({"func_80001050": 0x80001050, "D_8002D4B0": 0x8002D4B0}, symbols)

    def test_collects_only_address_bearing_reference_labels(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            source = Path(temporary_directory) / "main.s"
            source.write_text("jal func_80001050\nlui $a0, %hi(D_8002D4B0)\n", encoding="utf-8")
            symbols = bootstrap_symbols.collect_symbols(Path(temporary_directory))

        self.assertEqual(symbols, {"D_8002D4B0": 0x8002D4B0, "func_80001050": 0x80001050})
        self.assertIn("PROVIDE(D_8002D4B0 = 0x8002D4B0);", bootstrap_symbols.render(symbols))

    def test_collects_suffixed_jump_table_label(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            source = Path(temporary_directory) / "main.s"
            source.write_text(".word jtbl_800A811C_game\n", encoding="utf-8")
            symbols = bootstrap_symbols.collect_symbols(Path(temporary_directory))

        self.assertEqual(symbols, {"jtbl_800A811C_game": 0x800A811C})
