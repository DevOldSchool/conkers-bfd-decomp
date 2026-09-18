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
    def test_later_variadic_prototype_is_repeated_before_call(self) -> None:
        prototype = "void func_1516972C(s32 arg, ...);\n"
        body = "void f(void) { func_1516972C(1, 2, 3); }"
        declarations, _ = facts.later_function_declarations(body, prototype * 2, "")
        self.assertEqual(["void func_1516972C(s32, ...);"], declarations)
        self.assertEqual([], facts.later_function_declarations(body, prototype, prototype)[0])
        # General cross-source signature inference must still reject varargs.
        self.assertIsNone(facts.argument_types("s32, ..."))

    def test_later_prototype_ignores_comments_disabled_and_local_declarations(self) -> None:
        body = "void f(void) { callee(1); }"
        for source in ("/*\nvoid callee(s32, ...);\n*/", "#if 0\nvoid callee(s32, ...);\n#endif",
                       "void other(void) {\nvoid callee(s32, ...);\n}"):
            with self.subTest(source=source):
                self.assertEqual([], facts.later_function_declarations(body, source, "")[0])
        with self.assertRaises(facts.DeclarationError):
            facts.later_function_declarations(body, "void callee(s32, ...);\ns32 callee(s32);", "")

    def test_comment_only_prefix_does_not_supply_declarations_or_placeholders(self) -> None:
        prefix = (
            '/* Call context: func_copy: SDK binding; prototype evidence */\n'
            '/* Preserved notes:\n'
            'M2C_UNK func_unproven(M2C_UNK);\n'
            'typedef struct Fake { s32 field; } Fake;\n'
            '*/\n'
            '// M2C_UNK another_unproven(void);\n'
        )
        self.assertEqual(([], []), facts.resolve_required_declarations(prefix, ''))

    def test_skips_evidence_comments_while_preserving_declaration_abi_marker(self) -> None:
        declaration = 'void func_copy(void *, s32); /* CONKER_ABI_DISCARDED_RETURN */'
        prefix = '/* Call context: func_copy: proven argument homes */\n' + declaration
        declarations, evidence = facts.resolve_required_declarations(prefix, '')
        self.assertEqual([declaration], declarations)
        self.assertEqual(['func_copy: m2c concrete declaration'], evidence)

    def test_rejects_composite_declarations_as_a_whole(self) -> None:
        with self.assertRaisesRegex(facts.DeclarationError, 'partial fields'):
            facts.resolve_required_declarations('typedef struct State {\n s32 field;\n} State;', '')

    def test_later_global_pointer_and_array_declarations_are_visible_before_use(self) -> None:
        definition = "void func_test(void) { *D_pointer = D_array[0]; }"
        source = "extern s32 *D_pointer;\nextern s32 D_array[4];\n"
        found, _ = facts.later_object_declarations(definition, source, "")
        self.assertEqual(["extern s32 D_array[4];", "extern s32 * D_pointer;"], found)
        self.assertEqual([], facts.later_object_declarations(definition, source, source)[0])

    def test_later_global_conflict_is_rejected(self) -> None:
        with self.assertRaises(facts.DeclarationError):
            facts.later_object_declarations("void f(void) { D_value = 1; }",
                                           "extern s32 D_value;\nextern f32 D_value;\n", "")

    def test_comment_disabled_and_function_local_externs_are_not_hoisted(self) -> None:
        definition = "void f(void) { D_value = 1; }"
        for source in ("/*\nextern s32 D_value;\n*/",
                       "#if 0\nextern s32 D_value;\n#endif\n",
                       "void other(void) {\nextern s32 D_value;\n}"):
            self.assertEqual([], facts.later_object_declarations(definition, source, "")[0])

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

    def test_resolves_unknown_parameter_types_without_inventing_argument_count(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "src" / "callee.c"
            source.parent.mkdir()
            source.write_text("s32 func_target(void *arg0, s32 arg1);\n")
            declarations, _ = facts.resolve_required_declarations(
                "M2C_UNK func_target(M2C_UNK, M2C_UNK);", "", root=root)
            self.assertEqual(["s32 func_target(void *, s32);"], declarations)
            with self.assertRaises(facts.DeclarationError):
                facts.resolve_required_declarations(
                    "M2C_UNK func_target(M2C_UNK);", "", root=root)

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

    def test_known_returns_with_unknown_arguments_use_project_signatures(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "src" / "callee.c"
            source.parent.mkdir()
            source.write_text('s32 func_target(f32, f32, s32);\nvoid *func_pointer(s32);\n')
            for prefix, expected in (
                ('s32 func_target(M2C_UNK, M2C_UNK, s32);', 's32 func_target(f32, f32, s32);'),
                ('extern s32 func_target(M2C_UNK, f32, s32); /* extern */', 's32 func_target(f32, f32, s32);'),
                ('void *func_pointer(M2C_UNK);', 'void * func_pointer(s32);'),
            ):
                with self.subTest(prefix=prefix):
                    found, evidence = facts.resolve_required_declarations(prefix, '', root=root)
                    self.assertEqual([expected], found)
                    self.assertTrue(evidence)
            for prefix in ('void func_target(M2C_UNK, M2C_UNK, s32);',
                           's32 func_target(M2C_UNK, s32, s32);',
                           's32 func_target(M2C_UNK);',
                           's32 func_target(M2C_UNK, ..., s32);',
                           's32 func_absent(M2C_UNK);'):
                with self.subTest(prefix=prefix), self.assertRaises(facts.DeclarationError):
                    facts.resolve_required_declarations(prefix, '', root=root)

    def test_local_function_evidence_wins_but_known_types_must_agree(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            (root / 'src').mkdir()
            (root / 'src/other.c').write_text('void func_target(s32);\n')
            local = 's32 func_target(void *, s32);\n'
            result = facts.function_declaration('func_target', 'M2C_UNK, s32',
                                                root=root, source=local)
            self.assertEqual('s32 func_target(void *, s32);', result.text)
            self.assertEqual(('active declaration in the allowed source',), result.evidence)
            for args, ret in [('s32, s32', 'M2C_UNK'), ('M2C_UNK', 'M2C_UNK'),
                              ('M2C_UNK, s32', 'void')]:
                self.assertIsNone(facts.function_declaration('func_target', args,
                                  expected_return=ret, root=root, source=local))

    def test_local_array_object_view_is_not_replaced_by_other_source(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            (root / 'src').mkdir()
            (root / 'src/other.c').write_text('extern s32 D_value;\n')
            local = 'extern u8 D_value[];\n'
            result = facts.object_declaration('D_value', root=root, source=local)
            self.assertEqual('extern u8 D_value[];', result.text)
            self.assertEqual([], facts.resolve_required_declarations(
                'extern M2C_UNK D_value;', local, root=root)[0])
            for source in (local + 'extern s32 D_value;\n', 'static u8 D_value;\n',
                           'extern Other D_value;\n'):
                self.assertIsNone(facts.object_declaration('D_value', root=root, source=source))

    def test_resolves_local_function_pointer_array_view(self) -> None:
        source = "extern void (*D_dispatch[])(void *, void *);\n"
        result = facts.object_declaration('D_dispatch', source=source)
        self.assertIsNotNone(result)
        self.assertEqual("extern void (*D_dispatch[])(void *, void *);", result.text)
        self.assertEqual([], facts.resolve_required_declarations(
            'extern M2C_UNK D_dispatch;\n', source)[0])

    def test_resolves_zero_argument_function_pointer_array_view(self) -> None:
        source = "extern void (*D_dispatch[])(void);\n"
        result = facts.object_declaration('D_dispatch', source=source)
        self.assertIsNotNone(result)
        self.assertEqual("extern void (*D_dispatch[])(void);", result.text)
        self.assertEqual([], facts.resolve_required_declarations(
            'extern M2C_UNK D_dispatch;\n', source)[0])

    def test_function_pointer_array_conflicts_remain_ambiguous(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "src" / "objects.c"
            source.parent.mkdir(parents=True)
            source.write_text(
                "extern void (*D_dispatch[])(void *, void *);\n"
                "extern s32 D_dispatch;\n",
                encoding="utf-8",
            )
            with self.assertRaises(facts.DeclarationError):
                facts.resolve_required_declarations(
                    'extern M2C_UNK D_dispatch;\n', '', root=root
                )

    def test_extern_unknown_objects_use_unique_external_evidence(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "src" / "objects.c"
            source.parent.mkdir()
            source.write_text('extern s32 D_value;\nextern u8 *D_pointer;\n')
            found, _ = facts.resolve_required_declarations(
                'extern M2C_UNK D_value;\nextern M2C_UNK D_pointer;', '', root=root)
            self.assertEqual(['extern s32 D_value;', 'extern u8 * D_pointer;'], found)
            found, _ = facts.resolve_required_declarations(
                'extern M2C_UNK D_value;', 'extern s32 D_value;', root=root)
            self.assertEqual([], found)

    def test_unknown_objects_reject_unproven_or_conflicting_evidence(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            source = root / "src" / "objects.c"
            source.parent.mkdir()
            for evidence in (
                '/* extern s32 D_value; */',
                '#if 0\nextern s32 D_value;\n#endif',
                'void other(void) {\n s32 D_value;\n}',
                'static s32 D_value;',
                'extern s32 D_value;\nextern f32 D_value;',
                'extern s32 D_value;\nextern s32 D_value[4];',
                'extern LocalType D_value;',
                'extern M2C_UNK D_value;',
            ):
                with self.subTest(evidence=evidence):
                    source.write_text(evidence)
                    with self.assertRaises(facts.DeclarationError):
                        facts.resolve_required_declarations('extern M2C_UNK D_value;', '', root=root)

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
