from __future__ import annotations

from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import declaration_conflicts as conflicts

# Synthetic declarations; these fixtures are not copied project or ROM sources.


def conflict(sources: dict[str, str], name: str) -> dict | None:
    report = conflicts.analyze(sources)
    return next((c for c in report['conflicts'] if c['name'] == name), None)


def names(text: str) -> list[str]:
    return [d['name'] for d in conflicts.scan_source(text)]


class ScanTests(unittest.TestCase):
    def test_disabled_candidates_and_comments_are_ignored(self):
        text = '''
/* extern s32 D_1; */
#if 0 /* CONKER_DEFERRED_CANDIDATE func_A CURRENT (3) */
extern f32 D_1;
void func_A(f32 arg0) { }
#endif
extern u8 D_1;
#pragma GLOBAL_ASM("asm/nonmatchings/x/func_A.s")
'''
        decls = conflicts.scan_source(text)
        self.assertEqual([('D_1', 'u8', 7)], [(d['name'], conflicts.render(d['type']), d['line']) for d in decls])

    def test_eu_branches_are_skipped(self):
        text = '#if defined(PROFILE_US)\nextern s32 D_2;\n#elif defined(PROFILE_EU)\nextern f32 D_2;\n#endif\n'
        self.assertEqual(['s32'], [conflicts.render(d['type']) for d in conflicts.scan_source(text)])

    def test_static_symbols_and_typedefs_are_not_declarations(self):
        text = 'typedef struct Thing { s32 a; } Thing;\nstatic s32 D_3;\nstatic void func_B(void) { }\nThing D_4;\n'
        decls = conflicts.scan_source(text)
        self.assertEqual([('D_4', 'Thing', True)], [(d['name'], conflicts.render(d['type']), d['definition']) for d in decls])

    def test_declarators_render_canonically_without_parameter_names(self):
        text = '''
extern s32 (*D_5[])(Thing *);
void *func_C(u8 *arg0, f32 value, ...);
s32 func_D();
unsigned char D_6[0x10], *D_7;
void func_E(register s32 arg0, f32 *arg1) { }
'''
        rendered = {d['name']: conflicts.render(d['type']) for d in conflicts.scan_source(text)}
        self.assertEqual({
            'D_5': 's32 (*[])(Thing *)',
            'func_C': 'void *(u8 *, f32, ...)',
            'func_D': 's32 ()',
            'D_6': 'u8 [0x10]',
            'D_7': 'u8 *',
            'func_E': 'void (s32, f32 *)',
        }, rendered)

    def test_function_definition_is_recorded_as_definition(self):
        decls = conflicts.scan_source('s32 func_F(u8 arg0) {\n    return arg0;\n}\n')
        self.assertEqual([('func_F', True, 1)], [(d['name'], d['definition'], d['line']) for d in decls])


class MacroContinuationTests(unittest.TestCase):
    def test_continued_macro_bodies_do_not_hide_or_invent_declarations(self):
        text = '''#define PACKET(pkt, first)                \\
{                                                 \\
    Command *command = (pkt);                     \\
    command->word0 = (u32)(first);                \\
}
void func_A(Command *arg0) {
    PACKET(arg0, 1);
}
#define ATOI(dst, src)                \\
    for (dst = 0; *src; ++src)        \\
    {                                 \\
        dst = dst * 10 + *src - '0';  \\
    }
s32 func_B(u8 *arg0) {
    return 0;
}
'''
        self.assertEqual(['func_A', 'func_B'], names(text))

    def test_continuation_lines_keep_later_line_numbers(self):
        text = '#define VALUE \\\n    4\nextern s32 D_1[VALUE];\n'
        decls = conflicts.scan_source(text)
        self.assertEqual([('D_1', 3, 's32 [4]')], [(d['name'], d['line'], conflicts.render(d['type'])) for d in decls])

    def test_continued_directives_inside_disabled_blocks_keep_nesting(self):
        text = '#if 0\n#define HIDDEN \\\n    1\nextern f32 D_1;\n#endif\nextern s32 D_1;\n'
        self.assertEqual(['s32'], [conflicts.render(d['type']) for d in conflicts.scan_source(text)])


class TypedefResolutionTests(unittest.TestCase):
    def test_same_typedef_name_with_different_definitions_conflicts(self):
        found = conflict({
            'a.c': 'typedef s16 Value;\nextern Value D_1;',
            'b.c': 'typedef s32 Value;\nextern Value D_1;',
        }, 'D_1')
        self.assertEqual('incompatible', found['severity'])
        self.assertIn('access size differs', found['reasons'])
        self.assertEqual({('Value', 's16'), ('Value', 's32')},
                         {(v['type'], v['resolved']) for v in found['variants']})

    def test_typedef_alias_of_same_type_is_not_a_conflict(self):
        self.assertIsNone(conflict({
            'a.c': 'typedef s32 Value;\nextern Value D_1;\nvoid func_A(Value);',
            'b.c': 'extern s32 D_1;\nvoid func_A(s32);',
        }, 'D_1'))
        self.assertIsNone(conflict({
            'a.c': 'typedef s32 Value;\nvoid func_A(Value);',
            'b.c': 'void func_A(s32);',
        }, 'func_A'))

    def test_spellings_of_one_resolved_type_are_grouped(self):
        found = conflict({
            'a.c': 'typedef s32 Value;\nextern Value D_1;',
            'b.c': 'extern s32 D_1;',
            'c.c': 'extern f32 D_1;',
        }, 'D_1')
        self.assertEqual(2, found['variant_count'])
        grouped = next(v for v in found['variants'] if v['count'] == 2)
        self.assertEqual({'Value': 1, 's32': 1}, grouped['spellings'])


class AggregateLayoutTests(unittest.TestCase):
    def layout(self, body: str):
        return conflicts.strip(conflicts.scan_source(f'typedef struct {{ {body} }} T;\nextern T D_1;')[0]['type'])[2]

    def test_layout_uses_mips_alignment(self):
        self.assertEqual((12, 4), self.layout('u8 a; s32 b; s16 c;')[:2])
        self.assertEqual((16, 8), self.layout('u8 a; f64 b;')[:2])
        self.assertEqual((0x88, 4), self.layout('u8 pad0[0x84]; u32 flags;')[:2])
        self.assertEqual((8, 4), self.layout('struct { f32 x, z; } position;')[:2])

    def test_union_layout_is_widest_member(self):
        decls = conflicts.scan_source('typedef union { u32 w[2]; u64 d; } U;\nextern U D_1;')
        self.assertEqual((8, 8), conflicts.strip(decls[0]['type'])[2][:2])

    def test_bitfields_and_unknown_members_make_layout_unknown(self):
        self.assertIsNone(self.layout('u32 a : 3;'))
        self.assertIsNone(self.layout('Opaque inner;'))
        self.assertIsNone(self.layout('u8 data[COUNT];'))

    def test_identical_layouts_with_different_names_are_aggregate_name(self):
        found = conflict({
            'a.c': 'typedef struct { u8 pad0[4]; s32 x; } ThingA;\nextern ThingA D_1;',
            'b.c': 'typedef struct { u8 unk0[4]; s32 y; } ThingB;\nextern ThingB D_1;',
        }, 'D_1')
        self.assertEqual('aggregate-name', found['severity'])
        self.assertEqual([], found['reasons'])

    def test_different_layouts_are_not_called_the_same_shape(self):
        found = conflict({
            'a.c': 'typedef struct { s32 a; s32 b; } ThingA;\nextern ThingA D_1;',
            'b.c': 'typedef struct { s32 a; f32 b; } ThingB;\nextern ThingB D_1;',
        }, 'D_1')
        self.assertEqual('aggregate-unverified', found['severity'])
        self.assertEqual(['struct layout differs'], found['reasons'])
        sized = conflict({
            'a.c': 'typedef struct { s32 a; } ThingA;\nvoid func_A(ThingA *);',
            'b.c': 'typedef struct { s32 a; s32 b; } ThingB;\nvoid func_A(ThingB *);',
        }, 'func_A')
        self.assertEqual(['struct size differs'], sized['reasons'])

    def test_unknown_layout_is_reported_as_unknown(self):
        found = conflict({'a.c': 'extern ThingA *D_1;', 'b.c': 'extern ThingB *D_1;'}, 'D_1')
        self.assertEqual('aggregate-unverified', found['severity'])
        self.assertEqual(['struct layout unknown'], found['reasons'])

    def test_same_struct_name_with_different_layouts_conflicts(self):
        found = conflict({
            'a.c': 'typedef struct Thing { s32 a; } Thing;\nextern Thing D_1;',
            'b.c': 'typedef struct Thing { f32 a; } Thing;\nextern Thing D_1;',
        }, 'D_1')
        self.assertEqual('aggregate-unverified', found['severity'])
        self.assertEqual(['struct layout differs'], found['reasons'])

    def test_forward_struct_reference_resolves_later_definition(self):
        text = 'extern struct Node *D_1;\nstruct Node { struct Node *next; s16 value; };\nextern struct Node D_2;'
        decls = {d['name']: d['type'] for d in conflicts.scan_source(text)}
        self.assertEqual((8, 4), decls['D_1'][1][2][:2])
        self.assertEqual((8, 4), decls['D_2'][2][:2])


class ArrayElementTests(unittest.TestCase):
    def test_element_width_difference_is_shortlisted(self):
        found = conflict({'a.c': 'extern s16 D_1[];', 'b.c': 'extern s32 D_1[];'}, 'D_1')
        self.assertEqual('incompatible', found['severity'])
        self.assertEqual(['array element width differs'], found['reasons'])
        self.assertTrue(found['abi_risk'])

    def test_byte_array_against_wider_array_reports_element_width(self):
        found = conflict({
            'a.c': 'extern s32 D_1[];', 'b.c': 'extern u8 D_1[];', 'c.c': 'extern void *D_1[];',
        }, 'D_1')
        self.assertEqual('incompatible', found['severity'])
        self.assertIn('array element width differs', found['reasons'])
        self.assertIn('pointer vs integer or other same-size difference', found['reasons'])
        self.assertTrue(found['abi_risk'])

    def test_scalar_against_array_of_different_width_is_shortlisted(self):
        found = conflict({'a.c': 'extern s32 D_1;', 'b.c': 'extern s16 D_1[2];'}, 'D_1')
        self.assertEqual(['array element width differs', 'array vs scalar object'], found['reasons'])
        self.assertTrue(found['abi_risk'])
        placeholder = conflict({'a.c': 'extern u8 D_1;', 'b.c': 'extern s32 D_1[2];'}, 'D_1')
        self.assertEqual(['array vs scalar object'], placeholder['reasons'])
        self.assertFalse(placeholder['abi_risk'])

    def test_element_float_vs_integer(self):
        found = conflict({'a.c': 'extern f32 D_1[4];', 'b.c': 'extern s32 D_1[4];'}, 'D_1')
        self.assertEqual(['array element float vs integer'], found['reasons'])
        self.assertTrue(found['abi_risk'])

    def test_scalar_byte_placeholder_is_not_shortlisted(self):
        found = conflict({'a.c': 'extern u8 D_1;', 'b.c': 'typedef struct { s32 a; } T;\nextern T D_1;'}, 'D_1')
        self.assertEqual('byte-placeholder', found['severity'])
        self.assertFalse(found['abi_risk'])

    def test_array_bounds_evaluate_constant_arithmetic_only(self):
        self.assertEqual(16, conflicts.eval_bound('0x10'))
        self.assertEqual(0x74, conflicts.eval_bound('0x84 - 0x10'))
        self.assertEqual(16, conflicts.eval_bound('1 << 4'))
        self.assertEqual(4, conflicts.eval_bound('8U / 2'))
        for text in ('', 'COUNT', 'sizeof ( x )', '2 ** 8', '1 << 99', '-1'):
            with self.subTest(text=text):
                self.assertIsNone(conflicts.eval_bound(text))


def locations(prototype: str) -> list:
    decl = conflicts.scan_source(prototype)[0]
    return [loc and loc[0] for loc in conflicts.o32_argument_locations(conflicts.strip(decl['type']))]


class O32CallingConventionTests(unittest.TestCase):
    def test_only_leading_floats_use_float_registers(self):
        cases = {
            'void f(f32, f32);': ['$f12', '$f14'],
            'void f(f64, f32);': ['$f12', '$f14'],
            'void f(f32, s32, f32);': ['$f12', '$a1', '$a2'],
            'void f(s32, f32);': ['$a0', '$a1'],
            'void f(s16, f32, f32 *, f32 *);': ['$a0', '$a1', '$a2', '$a3'],
            'void f(f32, f32, f32);': ['$f12', '$f14', '$a2'],
        }
        for prototype, expected in cases.items():
            with self.subTest(prototype=prototype):
                self.assertEqual(expected, locations(prototype))

    def test_eight_byte_values_align_to_even_slots_and_spill_to_stack(self):
        self.assertEqual(['$a0', '$a2:$a3'], locations('void f(s32, f64);'))
        self.assertEqual(['$a0', '$a2:$a3', 'sp+0x10'], locations('void f(s32, s64, s32);'))
        self.assertEqual(['$a0', '$a1', '$a2', '$a3', 'sp+0x10'], locations('void f(s32, s32, s32, s32, s32);'))

    def test_struct_return_passes_hidden_pointer_and_closes_float_registers(self):
        text = 'typedef struct { s32 a; s32 b; } Pair;\nPair f(f32, s32);'
        decl = conflicts.scan_source(text)[0]
        fn = conflicts.strip(decl['type'])
        self.assertEqual('memory via hidden $a0', conflicts.o32_return_location(fn[1]))
        self.assertEqual(['$a1', '$a2'], [loc[0] for loc in conflicts.o32_argument_locations(fn)])

    def test_trailing_float_spelled_as_integer_is_a_value_disagreement(self):
        found = conflict({
            'def.c': 'void func_A(s16 a, f32 b, f32 *c, f32 *d) { }',
            'caller.c': 'void func_A(s16, s32, f32 *, f32 *);',
        }, 'func_A')
        self.assertEqual(['float vs integer argument in the same register'], found['reasons'])
        self.assertTrue(found['abi_risk'])

    def test_shifted_arguments_are_location_differences(self):
        found = conflict({'a.c': 'void func_A(s32, s64, s32);', 'b.c': 'void func_A(s32, s32, s32);'}, 'func_A')
        self.assertEqual(['argument location differs'], found['reasons'])
        struct_return = conflict({
            'a.c': 'typedef struct { s32 a; s32 b; } Pair;\nPair func_A(s32);',
            'b.c': 's32 func_A(s32);',
        }, 'func_A')
        self.assertEqual(['argument location differs', 'return location differs'], struct_return['reasons'])

    def test_same_register_width_difference_is_not_shortlisted(self):
        found = conflict({'a.c': 'void func_A(u8, f32 *);', 'b.c': 'void func_A(s32, f32 *);'}, 'func_A')
        self.assertEqual(['argument type differs (same register)'], found['reasons'])
        self.assertFalse(found['abi_risk'])

    def test_unknown_struct_by_value_stops_location_comparison(self):
        found = conflict({'a.c': 'void func_A(Opaque, s32);', 'b.c': 'void func_A(s32, s32);'}, 'func_A')
        self.assertIn('argument location unknown (struct passed by value)', found['reasons'])


class ClassificationTests(unittest.TestCase):
    def test_identical_declarations_are_not_conflicts(self):
        self.assertIsNone(conflict({'a.c': 'extern s32 D_1;', 'b.c': 'extern s32 D_1;'}, 'D_1'))

    def test_severity_ladder(self):
        cases = [
            ('extern volatile s32 D_1;', 'extern s32 D_1;', 'qualifier'),
            ('extern u8 D_1[4];', 'extern u8 D_1[];', 'qualifier'),
            ('extern ThingA *D_1;', 'extern ThingB *D_1;', 'aggregate-unverified'),
            ('extern void *D_1;', 'extern u8 *D_1;', 'pointee'),
            ('extern u16 D_1;', 'extern s16 D_1;', 'signedness'),
            ('extern u8 D_1;', 'extern Thing D_1;', 'byte-placeholder'),
            ('extern s32 D_1;', 'extern void *D_1;', 'incompatible'),
            ('extern f32 D_1;', 'extern s32 D_1;', 'incompatible'),
        ]
        for a, b, severity in cases:
            with self.subTest(a=a, b=b):
                self.assertEqual(severity, conflict({'a.c': a, 'b.c': b}, 'D_1')['severity'])

    def test_unprototyped_function_compares_return_type_only(self):
        self.assertEqual('qualifier', conflict({'a.c': 's32 func_A();', 'b.c': 's32 func_A(s32, f32);'}, 'func_A')['severity'])
        self.assertEqual('signedness', conflict({'a.c': 'u32 func_A();', 'b.c': 's32 func_A(s32);'}, 'func_A')['severity'])
        self.assertEqual('incompatible', conflict({'a.c': 'f32 func_A();', 'b.c': 's32 func_A(s32);'}, 'func_A')['severity'])

    def test_risk_reasons(self):
        cases = [
            ('void func_A(f32);', 'void func_A(s32);', 'argument location differs', True),
            ('void func_A(s16, f32);', 'void func_A(s16, s32);', 'float vs integer argument in the same register', True),
            ('void func_A(s32);', 'void func_A(s32, s32);', 'argument count differs', True),
            ('void func_A(s32, ...);', 'void func_A(s32, s32);', 'variadic vs fixed', True),
            ('f32 func_A(void);', 's32 func_A(void);', 'return location differs', True),
            ('void func_A(void *);', 'void func_A(s32);', 'argument type differs (same register)', False),
            ('void func_A(void);', 's32 func_A(void);', 'void vs value return', False),
            ('extern u8 *D_A;', 'extern s32 D_A[];', 'array vs pointer', True),
            ('extern u8 D_A;', 'extern u8 D_A[];', 'array vs scalar object', False),
            ('extern s32 D_A;', 'extern s32 D_A[2];', 'array vs scalar object', False),
        ]
        for a, b, reason, risk in cases:
            with self.subTest(a=a, b=b):
                name = 'D_A' if 'D_A' in a else 'func_A'
                found = conflict({'a.c': a, 'b.c': b}, name)
                self.assertIn(reason, found['reasons'])
                self.assertEqual(risk, found['abi_risk'])

    def test_disagreement_with_c_definition(self):
        found = conflict({
            'def.c': 'void func_A(Thing *arg0) { }',
            'same.c': 'void func_A(Thing *);',
            'loose.c': 'void func_A(void *);',
            'wrong.c': 'void func_A(s32, s32);',
        }, 'func_A')
        self.assertEqual('def.c:1', found['definition'])
        self.assertEqual({'void (void *)': 'pointee', 'void (s32, s32)': 'incompatible'},
                         {d['type']: d['severity'] for d in found['disagree_with_definition']})
        self.assertEqual(4, found['file_count'])

    def test_report_orders_shortlisted_conflicts_first_and_renders_markdown(self):
        report = conflicts.analyze({
            'a.c': 'extern s32 D_1; void func_A(f32); extern u16 D_2; typedef s16 V; extern V D_3;',
            'b.c': 'extern void *D_1; void func_A(s32); extern s16 D_2; typedef s32 V; extern V D_3;',
        }, {'func_A': 'raw_asm'})
        self.assertEqual(['D_3', 'func_A', 'D_1', 'D_2'], [c['name'] for c in report['conflicts']])
        self.assertEqual(2, report['summary']['risk_shortlist_symbols'])
        markdown = conflicts.render_markdown(report, limit=5)
        self.assertIn('### `func_A`: incompatible, 2 variants in 2 files', markdown)
        self.assertIn('US state `raw_asm`', markdown)
        self.assertIn('`V` → `s16`', markdown)
        self.assertIn('not a verified or exhaustive count', markdown)


if __name__ == '__main__':
    unittest.main()
