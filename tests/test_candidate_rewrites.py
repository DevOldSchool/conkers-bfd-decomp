from __future__ import annotations

import importlib.util
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
SPEC = importlib.util.spec_from_file_location(
    "candidate_rewrites", ROOT / "scripts" / "candidate_rewrites.py"
)
assert SPEC is not None and SPEC.loader is not None
rewrites = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = rewrites
SPEC.loader.exec_module(rewrites)


class CandidateRewriteTests(unittest.TestCase):
    def test_store_only_narrow_argument_stays_in_32_bit_abi_register(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            function = "void func_test(void *arg0, s8 arg1) {\n    *(s8 *)((u8 *)arg0 + 4) = arg1;\n}"
            prepared, evidence = rewrites.widen_store_only_parameters(function, "func_test", root=root)
            self.assertIn("s32 arg1", prepared)
            self.assertTrue(evidence)
            for extra in ("    return arg1;\n", "    arg1++;\n", "    consume(arg1);\n"):
                other = function.replace("}", extra + "}")
                self.assertEqual(other, rewrites.widen_store_only_parameters(other, "func_test", root=root)[0])
            source = root / "src/test.c"; source.parent.mkdir()
            source.write_text("void func_test(void *, s8);\n")
            self.assertEqual(function, rewrites.widen_store_only_parameters(function, "func_test", root=root)[0])

    def test_halfword_and_byte_store_widths_must_agree(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            function = "void func_test(void *arg0, s16 arg1) {\n    *(s8 *)arg0 = arg1;\n}"
            self.assertEqual(function, rewrites.widen_store_only_parameters(function, "func_test", root=Path(directory))[0])

    def test_repeats_later_global_omitted_by_m2c_context(self) -> None:
        source = '#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\nextern s32 D_value;\n'
        candidate = rewrites.prepare_starter('void func_test(void) { D_value = 1; }', 'func_test', source)
        self.assertEqual(('extern s32 D_value;',), candidate.declarations)

    def test_repeats_a_later_prototype_before_the_target_call(self) -> None:
        source = '#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\ns32 callee(u8);\n'
        candidate = rewrites.prepare_starter('void func_test(void) { callee(0U); }', 'func_test', source)
        self.assertEqual(('s32 callee(u8);',), candidate.declarations)

    def test_repeats_existing_variadic_prototype_without_inferring_new_abi(self) -> None:
        source = '#pragma GLOBAL_ASM("asm/nonmatchings/test/func_test.s")\nvoid callee(s32, ...);\n'
        candidate = rewrites.prepare_starter('void func_test(void) { callee(0, 1, 2); }', 'func_test', source)
        self.assertEqual(('void callee(s32, ...);',), candidate.declarations)

    def test_lowers_inferred_members_without_redefining_the_project_structure(self) -> None:
        source = 'typedef struct State { s32 known; } State;\nextern State *state;\n'
        starter = (
            'typedef struct State {\n/* 0x000 */ s32 known;\n'
            '/* 0x005 */ u8 unk5; /* inferred */\n} State;\n'
            'void func_test(void) { state->unk5 = 1; }\n'
        )
        candidate = rewrites.prepare_starter(starter, 'func_test', source)
        self.assertIn('*(u8 *)((u8 *)state + 0x005) = 1;', candidate.definition)
        self.assertEqual((), candidate.declarations)
        self.assertTrue(candidate.evidence)

    def test_rejects_unproven_composite_type_instead_of_copying_loose_fields(self) -> None:
        starter = 'typedef struct Unknown {\n s32 field;\n} Unknown;\nvoid func_test(void) {}'
        with self.assertRaisesRegex(rewrites.CandidateError, 'canonical project type'):
            rewrites.prepare_starter(starter, 'func_test', '')

    def test_repairs_typed_end_pointer_without_changing_element_arithmetic(self) -> None:
        function = 'void func_test(s64 *base) {\n    s32 end;\n    end = base + 0x40;\n    do { base += 8; } while (base != end);\n}'
        repaired, actions = rewrites.repair_compile_diagnostics(function, ('illegal combination of pointer and integer', 'Unacceptable operand of == or !='))
        self.assertIn('s64 *end;', repaired)
        self.assertIn('base + 0x40', repaired)
        self.assertIn('base += 8', repaired)
        self.assertTrue(actions)

    def test_sanitizes_aligned_scalar_m2c_field(self) -> None:
        starter = """\
void func_test(void *arg0) {
    M2C_FIELD(arg0, s32, 0x18) = 1;
}
"""

        prepared = rewrites.prepare_starter(starter, "func_test", "")

        self.assertIn("*(s32 *)((u8 *)arg0 + 0x18) = 1;", prepared.definition)
        self.assertNotIn("M2C_", prepared.definition)

    def test_sanitizes_pointer_fields_expression_bases_and_negative_offsets(self) -> None:
        starter = """\
void func_test(void *arg0, s32 index) {
    void *value;

    value = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD((arg0 + index), s16 *, -2) = 1;
}
"""

        prepared = rewrites.prepare_starter(starter, "func_test", "")

        self.assertIn("value = *(void **)((u8 *)arg0 + 0);", prepared.definition)
        self.assertIn(
            "*(s16 *)((u8 *)(arg0 + index) + -2) = 1;", prepared.definition
        )
        self.assertNotIn("M2C_FIELD", prepared.definition)

    def test_resolves_placeholder_declaration_before_preparing_candidate(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            target = root / "src" / "game" / "target.c"
            target.parent.mkdir(parents=True)
            target.write_text("void func_target(u8 arg0) {}\n", encoding="utf-8")
            starter = """\
M2C_UNK func_target(u8); /* extern */

void func_test(void) {
    func_target(1);
}
"""

            prepared = rewrites.prepare_starter(
                starter, "func_test", "", root=root
            )

            self.assertEqual(("void func_target(u8);",), prepared.declarations)
            self.assertEqual(("func_target: src/game/target.c",), prepared.evidence)

    def test_rejects_unproven_placeholder_declaration(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            starter = """\
M2C_UNK func_target(u8); /* extern */
void func_test(void) { func_target(1); }
"""
            with self.assertRaisesRegex(rewrites.CandidateError, "no unique"):
                rewrites.prepare_starter(
                    starter,
                    "func_test",
                    "",
                    root=Path(temporary_directory),
                )

    def test_replaces_only_unused_unknown_register_parameters(self) -> None:
        starter = """\
s32 func_test(s32 arg0, M2C_UNK arg1) {
    if (arg0 != 0) {
        return 1;
    }
    return 0;
}
"""

        prepared = rewrites.prepare_starter(starter, "func_test", "")

        self.assertIn("s32 func_test(s32 arg0, s32 arg1)", prepared.definition)

        used = "void func_test(M2C_UNK arg0) { use(arg0); }\n"
        with self.assertRaisesRegex(rewrites.CandidateError, "M2C_UNK"):
            rewrites.prepare_starter(used, "func_test", "")

    def test_casts_integer_backed_address_assigned_to_void_pointer(self) -> None:
        starter = """\
void func_test(void *arg0) {
    void *temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x1D4) + 0x40;
    *(s32 *)((u8 *)temp_v0 + 4) = 0;
}
"""

        prepared = rewrites.prepare_starter(starter, "func_test", "")

        self.assertIn(
            "temp_v0 = (void *)(*(s32 *)((u8 *)arg0 + 0x1D4) + 0x40);",
            prepared.definition,
        )

    def test_casts_shifted_integer_offset_assigned_to_void_pointer(self) -> None:
        starter = """\
void func_test(s32 arg1, s32 arg2) {
    s32 temp_v1;
    void *temp_a2;
    void *temp_v0;

    temp_a2 = (arg1 << 6) + temp_v1;
    temp_v0 = temp_v1 + (arg2 << 6);
}
"""

        prepared = rewrites.prepare_starter(starter, "func_test", "")

        self.assertIn(
            "temp_a2 = (void *)((arg1 << 6) + temp_v1);", prepared.definition
        )
        self.assertIn(
            "temp_v0 = (void *)(temp_v1 + (arg2 << 6));", prepared.definition
        )

    def test_does_not_cast_integer_assignment_to_scalar(self) -> None:
        starter = """\
void func_test(void *arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x28) + 0x58;
}
"""

        prepared = rewrites.prepare_starter(starter, "func_test", "")

        self.assertNotIn("(void *)", prepared.definition.split("{", 1)[1])

    def test_casts_visible_global_operand_before_void_pointer_arithmetic(self) -> None:
        function = "void f(s32 index) {\n    void *p;\n    p = D_base + (index * 0x9A0);\n}\n"
        repaired, actions = rewrites.repair_compile_diagnostics(
            function, ("Unacceptable operand of '+'.",), visible_source="extern void *D_base;\n"
        )
        self.assertIn("((u8 *)D_base) + (index * 0x9A0)", repaired)
        self.assertTrue(any("before byte arithmetic" in action for action in actions))
        self.assertEqual(repaired, rewrites.repair_compile_diagnostics(
            repaired, ("Unacceptable operand of '+'.",), visible_source="extern void *D_base;\n"
        )[0])

    def test_does_not_guess_global_pointer_type_or_override_shadow(self) -> None:
        function = "void f(s32 index) {\n    void *p;\n    p = D_base + index;\n}\n"
        for context in ("", "extern s32 *D_base;", "/*\nextern void *D_base;\n*/",
                        "#if 0\nextern void *D_base;\n#endif", "extern void *D_base;\nextern s32 D_base;"):
            repaired, _ = rewrites.repair_compile_diagnostics(function, ("Unacceptable operand of '+'.",), visible_source=context)
            self.assertNotIn("((u8 *)D_base)", repaired)
        shadow = function.replace("s32 index", "s32 index, s32 *D_base")
        repaired, _ = rewrites.repair_compile_diagnostics(shadow, ("Unacceptable operand of '+'.",), visible_source="extern void *D_base;")
        self.assertNotIn("((u8 *)D_base)", repaired)

    def test_casts_integer_address_call_argument_from_visible_prototype(self) -> None:
        function = "void f(void) {\n    s32 temp;\n    void *packet;\n    copy(temp + 0x28, &packet, 0xC);\n}\n"
        prototype = "void copy(void *, void *, s32);\n"
        repaired, actions = rewrites.repair_compile_diagnostics(
            function, ("illegal combination of pointer and integer",), visible_source=prototype
        )
        self.assertIn("copy((void *)(temp + 0x28), &packet, 0xC)", repaired)
        self.assertIn("s32 temp;", repaired)
        self.assertTrue(any("visible prototype" in action for action in actions))
        self.assertEqual(repaired, rewrites.repair_compile_diagnostics(repaired,
            ("illegal combination of pointer and integer",), visible_source=prototype)[0])
        for context in ("", "#if 0\n" + prototype + "#endif", prototype + "void copy(s32, void *, s32);\n"):
            self.assertEqual(function, rewrites.repair_compile_diagnostics(function,
                ("illegal combination of pointer and integer",), visible_source=context)[0])
        self.assertEqual(function, rewrites.repair_compile_diagnostics(function, (), visible_source=prototype)[0])

    def test_repairs_undefined_null_from_compiler_evidence(self) -> None:
        function = "void func_test(void *arg0) { if (arg0 == NULL) return; }\n"

        repaired, actions = rewrites.repair_compile_diagnostics(
            function, ("'NULL' undefined",)
        )

        self.assertIn("arg0 == 0", repaired)
        self.assertNotIn("NULL", repaired)
        self.assertIn("undefined NULL", actions[0])

    def test_repairs_void_pointer_arithmetic_from_compiler_evidence(self) -> None:
        function = """\
void func_test(void *arg0, s32 arg1) {
    void *temp_v0;
    void *temp_a2;

    temp_v0 = arg0 + 4;
    temp_a2 = (arg1 << 6) + 0x1000;
    temp_v0 += 0x10;
}
"""

        repaired, actions = rewrites.repair_compile_diagnostics(
            function, ("illegal combination of pointer and integer",)
        )

        self.assertIn("u8 *arg0", repaired)
        self.assertIn("u8 *temp_v0", repaired)
        self.assertIn("temp_a2 = (void *)((arg1 << 6) + 0x1000);", repaired)
        self.assertTrue(any("byte-address" in action for action in actions))
        self.assertTrue(any("temp_a2" in action for action in actions))

    def test_repairs_integer_address_parameter_and_byte_buffer_dereference(self) -> None:
        function = """\
void func_test(s32 arg0, s32 arg1) {
    u8 *var_v1;

    var_v1 = arg0 + (arg1 * 0x10);
    *(D_800BE510 + (D_800BE528 * 3)) = *(u8 *)(var_v1 + 0xC);
    if (var_v1 != ((arg1 * 0x10) + arg0)) {
        return;
    }
}
"""

        repaired, actions = rewrites.repair_compile_diagnostics(
            function,
            (
                "illegal combination of pointer and integer",
                "Dereferenced a non-pointer.",
                "Unacceptable operand of == or !=",
            ),
        )

        self.assertIn("void func_test(u8 *arg0, s32 arg1)", repaired)
        self.assertIn(
            "*(u8 *)(D_800BE510 + (D_800BE528 * 3))", repaired
        )
        self.assertIn("(arg1 * 0x10) + arg0", repaired)
        self.assertTrue(any("address parameter" in action for action in actions))
        self.assertTrue(any("byte buffer" in action for action in actions))

    def test_adds_ido_sqrtf_intrinsic_declarations(self) -> None:
        starter = """\
f32 func_test(f32 arg0) {
    return sqrtf(arg0);
}
"""

        prepared = rewrites.prepare_starter(starter, "func_test", "")

        self.assertIn("f32 sqrtf(f32);", prepared.declarations)
        self.assertIn("#pragma intrinsic(sqrtf)", prepared.declarations)
        self.assertIn("sqrtf: m2c intrinsic expression", prepared.evidence)

    def test_reuses_existing_ido_sqrtf_intrinsic_declarations(self) -> None:
        starter = """\
f32 func_test(f32 arg0) {
    return sqrtf(arg0);
}
"""
        source = "f32 sqrtf(f32 value);\n#pragma intrinsic(sqrtf)\n"

        prepared = rewrites.prepare_starter(starter, "func_test", source)

        self.assertNotIn("f32 sqrtf(f32);", prepared.declarations)
        self.assertNotIn("#pragma intrinsic(sqrtf)", prepared.declarations)
        self.assertIn("sqrtf: m2c intrinsic expression", prepared.evidence)

    def test_generates_compound_and_commutative_forms(self) -> None:
        function = "void func_test(void) {\n    value = value | mask;\n}\n"

        variants = rewrites.rewrite_variants([function], 10)

        self.assertTrue(any("value |= mask;" in variant for variant in variants))
        self.assertTrue(any("mask | value" in variant for variant in variants))
        self.assertEqual(len(variants), len(set(variants)))

    def test_rewrite_budget_is_strict(self) -> None:
        function = "void func_test(void) { value = value | mask; }\n"
        self.assertEqual(2, len(rewrites.rewrite_variants([function], 2)))

    def test_preserves_declarations_casts_and_operator_precedence(self) -> None:
        function = """\
s32 func_test(s32 *arg0, s32 a, s32 b, s32 c) {
    GameState *state;
    s32 value;
    value = a + b * c;
    return *(s32 *)((u8 *)arg0 + 4) + value;
}
"""
        variants = rewrites.swap_commutative_expressions(function)
        self.assertTrue(any("a + c * b" in v for v in variants))
        self.assertTrue(any("4 + (u8 *)arg0" in v for v in variants))
        for variant in variants:
            self.assertIn("s32 *arg0", variant)
            self.assertIn("GameState *state;", variant)
            self.assertNotIn("b + a * c", variant)
            self.assertNotIn("(u8 *)4", variant)

    def test_does_not_rewrite_literals_comments_or_side_effecting_operands(self) -> None:
        function = """\
s32 func_test(s32 a, s32 b) {
    /* a + b and s32 *arg0 */
    text = "a + b";
    return next() + b++;
}
"""
        self.assertEqual([], rewrites.swap_commutative_expressions(function))

    def test_assignment_rewrites_ignore_comment_lines(self) -> None:
        function = "void func_test(void) {\n/*\n    value = value | mask;\n*/\n}\n"
        self.assertEqual([], rewrites.assignment_form_variants(function))

    def test_unknown_syntax_is_left_untouched(self) -> None:
        for expression in ("a ? b + c : d", "(UnknownType)a + b"):
            function = f"s32 func_test(void) {{ return {expression}; }}"
            self.assertEqual([], rewrites.swap_commutative_expressions(function))

    def test_integer_rewrites_preserve_values_across_precedence_boundaries(self) -> None:
        for expression in ("a + b * c", "a * b + c", "a - b + c", "a + b | c", "a & b ^ c", "(a + b) * c"):
            function = f"s32 func_test(s32 a, s32 b, s32 c) {{ return {expression}; }}"
            for variant in rewrites.swap_commutative_expressions(function):
                rewritten = variant.split("return ", 1)[1].split(";", 1)[0]
                for values in ({"a": 2, "b": 3, "c": 5}, {"a": -5, "b": 7, "c": -2}):
                    self.assertEqual(eval(expression, {"__builtins__": {}}, values), eval(rewritten, {"__builtins__": {}}, values))

    def test_rewrites_saturate_without_growing_parentheses(self) -> None:
        function = "s32 func_test(s32 a, s32 b) { return a + b; }"
        variants = rewrites.rewrite_variants([function], 250)
        self.assertEqual(2, len(variants))
        self.assertTrue(all(v.count("(") == function.count("(") for v in variants))


if __name__ == "__main__":
    unittest.main()
