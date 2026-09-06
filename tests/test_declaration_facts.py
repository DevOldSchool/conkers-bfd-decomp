from __future__ import annotations

import importlib.util
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "declaration_facts", ROOT / "scripts" / "declaration_facts.py"
)
assert SPEC is not None and SPEC.loader is not None
facts = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = facts
SPEC.loader.exec_module(facts)


class DeclarationFactsTests(unittest.TestCase):
    def test_resolves_placeholder_return_type_from_matching_project_definition(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            target = root / "src" / "game" / "target.c"
            target.parent.mkdir(parents=True)
            target.write_text(
                "s32 func_target(u8 arg0) { return arg0; }\n", encoding="utf-8"
            )

            declarations, evidence = facts.resolve_required_declarations(
                "M2C_UNK func_target(u8); /* extern */\n",
                '#include "types.h"\n',
                root=root,
            )

            self.assertEqual(["s32 func_target(u8);"], declarations)
            self.assertEqual(["func_target: src/game/target.c"], evidence)

    def test_conflicting_return_types_remain_ambiguous(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "src" / "game"
            source.mkdir(parents=True)
            (source / "one.c").write_text("s32 func_target(u8);\n", encoding="utf-8")
            (source / "two.c").write_text("void func_target(u8);\n", encoding="utf-8")

            with self.assertRaisesRegex(
                facts.DeclarationError, "no unique project declaration evidence"
            ):
                facts.resolve_required_declarations(
                    "M2C_UNK func_target(u8); /* extern */\n", "", root=root
                )

    def test_ignores_preserved_disabled_candidate_as_declaration_evidence(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "src" / "game" / "candidate.c"
            source.parent.mkdir(parents=True)
            source.write_text(
                "#if 0 /* preserved */\n"
                "s32 func_target(u8 arg0) { return arg0; }\n"
                "#endif\n",
                encoding="utf-8",
            )

            with self.assertRaises(facts.DeclarationError):
                facts.resolve_required_declarations(
                    "M2C_UNK func_target(u8); /* extern */\n", "", root=root
                )

    def test_does_not_insert_an_existing_compatible_declaration(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = "extern s32 D_80000000;\n"

            declarations, _ = facts.resolve_required_declarations(
                "extern s32 D_80000000;\n", source, root=root
            )

            self.assertEqual([], declarations)


if __name__ == "__main__":
    unittest.main()
