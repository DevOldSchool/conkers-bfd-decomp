from __future__ import annotations

import io
import json
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import project_state  # noqa: E402
import sweep  # noqa: E402

SOURCE_PATH = 'src/game/unit.c'


def pragma(identifier):
    return project_state.global_asm_pragma(SOURCE_PATH, identifier)


def deferred(identifier, score, body):
    tag = project_state.DEFERRED_CANDIDATE_TAG
    return (f'#if 0 /* {tag} {identifier} CURRENT ({score}) */\n{body}'
            f'#endif /* {tag} {identifier} */\n{pragma(identifier)}\n')


SOURCE = (
    '#include "common.h"\n'
    '\n'
    'extern f32 D_800A0000;\n'
    'extern f32 D_800A0004;\n'
    '\n'
    + deferred('func_15000000', 40, 'f32 func_15000000(f32 arg0) {\n    return arg0 * D_800A0000;\n}\n')
    + '\n'
    'void func_15000020(void) {\n}\n'
    '\n'
    + pragma('func_15000040') + '\n'
    + deferred('func_15000060', 900, 'void func_15000060(void) {\n    func_15000020();\n}\n')
)

WORDS = {0x800A0000: struct.pack('>f', 1.5), 0x800A0004: struct.pack('>f', -2.0)}


def context(content=SOURCE):
    return sweep.FileContext(content, WORDS.get)


class CandidateBlockTests(unittest.TestCase):
    def test_reads_preserved_candidates_with_scores(self):
        blocks, problems = sweep.candidate_blocks(SOURCE, SOURCE_PATH)
        self.assertEqual([], problems)
        self.assertEqual(['func_15000000', 'func_15000060'], [block.identifier for block in blocks])
        self.assertEqual([40, 900], [block.marker_score for block in blocks])
        self.assertTrue(blocks[0].body.startswith('f32 func_15000000('))
        self.assertTrue(SOURCE[:blocks[0].end].endswith(pragma('func_15000000') + '\n'))

    def test_reports_candidates_without_their_pragma_or_end_marker(self):
        tag = project_state.DEFERRED_CANDIDATE_TAG
        content = (f'#if 0 /* {tag} func_A CURRENT (1) */\nvoid func_A(void) {{}}\n'
                   f'#endif /* {tag} func_A */\n'
                   f'#if 0 /* {tag} func_B */\nvoid func_B(void) {{}}\n')
        blocks, problems = sweep.candidate_blocks(content, SOURCE_PATH)
        self.assertEqual([], blocks)
        self.assertEqual(['func_A', 'func_B'], [identifier for identifier, _ in problems])


class VariantUnitTests(unittest.TestCase):
    def test_activates_selected_bodies_and_blanks_every_global_asm_line(self):
        blocks, _ = sweep.candidate_blocks(SOURCE, SOURCE_PATH)
        unit, lines = sweep.variant_unit(SOURCE, [(blocks[1], 'void func_15000060(void) {\n}\n')])
        self.assertNotIn('#pragma GLOBAL_ASM', unit)
        self.assertIn('#if 0 /* CONKER_DEFERRED_CANDIDATE func_15000000', unit)
        self.assertNotIn('CONKER_DEFERRED_CANDIDATE func_15000060', unit)
        unit_lines = unit.splitlines()
        self.assertEqual('void func_15000060(void) {', unit_lines[lines['func_15000060'][0] - 1])
        self.assertEqual(2, len(lines['func_15000060']))

    def test_line_ranges_follow_every_activated_body(self):
        blocks, _ = sweep.candidate_blocks(SOURCE, SOURCE_PATH)
        unit, lines = sweep.variant_unit(SOURCE, [(block, block.body) for block in blocks])
        unit_lines = unit.splitlines()
        for block in blocks:
            span = lines[block.identifier]
            self.assertEqual(block.body.splitlines(), unit_lines[span[0] - 1:span[-1]])

    def test_compiler_errors_blame_the_candidate_containing_the_line(self):
        lines = {'func_A': range(10, 20), 'func_B': range(30, 35)}
        message = ("cfe: Error: unit.c, line 31: redeclaration of 'func_B'; previous declaration "
                   "at line 12 in file 'unit.c'")
        self.assertEqual({'func_A', 'func_B'}, sweep.blamed_candidates(message, lines))
        self.assertEqual(set(), sweep.blamed_candidates('cfe: Error: unit.c, line 3: syntax', lines))


class LiteralTests(unittest.TestCase):
    def test_shortest_literal_round_trips_the_rom_word(self):
        self.assertEqual('1.0f', sweep.shortest_f32_literal(struct.pack('>f', 1.0)))
        self.assertEqual('0.1f', sweep.shortest_f32_literal(bytes.fromhex('3DCCCCCD')))
        # 3.71f rounds to 0x406D70A4; the ROM word needs the longer spelling.
        self.assertEqual('3.7099998f', sweep.shortest_f32_literal(bytes.fromhex('406D70A3')))
        self.assertEqual('0.00001f', sweep.shortest_f32_literal(struct.pack('>f', 1e-05)))
        self.assertEqual('-10000.0f', sweep.shortest_f32_literal(struct.pack('>f', -1e4)))
        self.assertEqual('1600000000.0f', sweep.shortest_f32_literal(struct.pack('>f', 1.6e9)))
        self.assertEqual('1.0e+30f', sweep.shortest_f32_literal(struct.pack('>f', 1e30)))
        self.assertEqual('-0.0f', sweep.shortest_f32_literal(bytes.fromhex('80000000')))
        self.assertIsNone(sweep.shortest_f32_literal(bytes.fromhex('7FC00000')))

    def test_short_spellings_that_overflow_are_skipped(self):
        # %.4g of FLT_MAX is 3.403e+38, which rounds above FLT_MAX and cannot pack.
        self.assertEqual('3.4028235e+38f', sweep.shortest_f32_literal(bytes.fromhex('7F7FFFFF')))
        self.assertEqual('-3.4028235e+38f', sweep.shortest_f32_literal(bytes.fromhex('FF7FFFFF')))

    def test_negated_negative_literal_is_parenthesized(self):
        self.assertEqual('x = -(-2.0f) + -2.0f;', sweep.substitute('x = -D_1 + D_1;', 'D_1', '-2.0f'))

    def test_literals_replace_file_rodata_externs(self):
        body = 'f32 func_15000000(f32 arg0) {\n    return arg0 * D_800A0000 - D_800A0004;\n}\n'
        text, detail = sweep.transform_literals(body, context())
        self.assertIn('return arg0 * 1.5f - -2.0f;', text)
        self.assertEqual('D_800A0000=1.5f D_800A0004=-2.0f', detail)

    def test_literals_drop_a_candidate_local_extern(self):
        body = 'extern f32 D_800A0004;\n\nf32 func_A(void) {\n    return D_800A0004;\n}\n'
        text, _ = sweep.transform_literals(body, context('\n'))
        self.assertNotIn('extern', text)
        self.assertIn('return -2.0f;', text)

    def test_address_taken_symbols_are_kept(self):
        body = 'void func_A(f32 *p) {\n    p = &D_800A0000;\n    *p = D_800A0004;\n}\n'
        text, detail = sweep.transform_literals(body, context())
        self.assertIn('&D_800A0000', text)
        self.assertIn('*p = -2.0f;', text)
        self.assertIn('D_800A0000:address-taken', detail)

    def test_literals_do_not_apply_without_rodata_uses(self):
        self.assertIsNone(sweep.transform_literals('void func_A(void) {\n}\n', context()))
        unreadable = sweep.FileContext(SOURCE, lambda address: None)
        self.assertIsNone(sweep.transform_literals('f32 f(void) {\n    return D_800A0000;\n}\n', unreadable))


class InlineTests(unittest.TestCase):
    def test_initialized_local_is_inlined(self):
        body = 'void f(f32 *p) {\n    f32 scale = 2.0f;\n\n    p[0] = scale;\n    p[1] = p->scale * scale;\n}\n'
        text, inlined = sweep.inline_literal_locals(body)
        self.assertEqual(['scale=2.0f'], inlined)
        self.assertNotIn('f32 scale', text)
        self.assertIn('p[0] = 2.0f;', text)
        self.assertIn('p[1] = p->scale * 2.0f;', text)

    def test_single_assignment_at_declaration_level_is_inlined(self):
        body = 'void f(f32 *p) {\n    f32 temp;\n\n    temp = -1.0f;\n    *p = -temp;\n}\n'
        text, inlined = sweep.inline_literal_locals(body)
        self.assertEqual(['temp=-1.0f'], inlined)
        self.assertNotIn('temp', text)
        self.assertIn('*p = -(-1.0f);', text)

    def test_locals_with_other_writes_are_kept(self):
        for body in (
            'void f(f32 *p) {\n    f32 t;\n\n    t = 1.0f;\n    t = 2.0f;\n    *p = t;\n}\n',
            'void f(f32 *p) {\n    f32 t = 1.0f;\n\n    t += *p;\n    *p = t;\n}\n',
            'void f(f32 *p) {\n    f32 t = 1.0f;\n\n    g(&t);\n    *p = t;\n}\n',
            'void f(f32 *p) {\n    f32 t;\n\n    *p = t;\n    t = 1.0f;\n}\n',
            'void f(f32 *p, s32 c) {\n    f32 t;\n\n    if (c) {\n        t = 1.0f;\n    }\n    *p = t;\n}\n',
            'void f(f32 *p) {\n    f32 t = 1.0f;\n}\n',
        ):
            with self.subTest(body=body):
                self.assertEqual((body, []), sweep.inline_literal_locals(body))

    def test_substitution_stays_inside_the_declaring_block(self):
        body = ('f32 f(void) {\n    {\n        f32 scale;\n        scale = 1.0f;\n'
                '        consume(scale);\n    }\n    return scale;\n}\n')
        text, inlined = sweep.inline_literal_locals(body)
        self.assertEqual(['scale=1.0f'], inlined)
        self.assertIn('consume(1.0f);', text)
        self.assertIn('return scale;', text)
        self.assertNotIn('f32 scale', text)

    def test_shadowed_names_are_kept(self):
        body = ('void f(f32 *p) {\n    f32 t = 1.0f;\n\n    {\n        s32 t;\n\n'
                '        t = 2;\n        g(t);\n    }\n    *p = t;\n}\n')
        self.assertEqual((body, []), sweep.inline_literal_locals(body))

    def test_braces_in_comments_and_strings_do_not_form_blocks(self):
        text = '{ /* { */ "}" \'{\' // }\n}'
        self.assertEqual([(0, len(text) - 1)], sweep.brace_pairs(text))

    def test_literals_inline_applies_only_when_a_local_is_inlined(self):
        body = 'f32 func_A(void) {\n    f32 t;\n\n    t = D_800A0000;\n    return t * t;\n}\n'
        text, detail = sweep.transform_literals_inline(body, context())
        self.assertIn('return 1.5f * 1.5f;', text)
        self.assertEqual('D_800A0000=1.5f inline t=1.5f', detail)
        self.assertIsNone(sweep.transform_literals_inline(
            'f32 func_A(void) {\n    return D_800A0000;\n}\n', context()))


class TsvTests(unittest.TestCase):
    def test_zeros_first_then_largest_improvement_and_errors_last(self):
        rows = [
            sweep.Row(50, 50, '0x20', '0x20', 'func_same', 'src/a.c', ''),
            sweep.Row(None, None, '-', '-', 'func_err', 'src/a.c', '[compile: cfe: Error]'),
            sweep.Row(300, 100, 'leaf', 'leaf', 'func_better', 'src/b.c', 'D_800A0000=1.5f'),
            sweep.Row(20, 0, '0x18', '0x18', 'func_zero', 'src/b.c', ''),
            sweep.Row(10, 40, '0x18', '0x20', 'func_worse', 'src/b.c', 'two\twords'),
        ]
        stream = io.StringIO()
        sweep.write_tsv(rows, stream)
        lines = stream.getvalue().splitlines()
        self.assertEqual('\t'.join(sweep.TSV_HEADER), lines[0])
        self.assertEqual(['func_zero', 'func_better', 'func_same', 'func_worse', 'func_err'],
                         [line.split('\t')[4] for line in lines[1:]])
        self.assertEqual(['20', '0', '0x18', '0x18', 'func_zero', 'src/b.c', '-'], lines[1].split('\t'))
        self.assertEqual(['-', 'ERR'], lines[-1].split('\t')[:2])
        self.assertEqual('two words', lines[4].split('\t')[6])
        self.assertTrue(all(len(line.split('\t')) == 7 for line in lines))


class SelectionTests(unittest.TestCase):
    def setUp(self):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        root = Path(directory.name)
        (root / 'progress').mkdir()
        (root / 'src/game').mkdir(parents=True)
        (root / SOURCE_PATH).write_text(SOURCE, encoding='utf-8')
        functions = [
            {'symbol': 'func_15000000', 'source': SOURCE_PATH, 'overlay': 'game',
             'deferred': {'current_score': 40, 'reason': 'register swap'},
             'regions': {'us': {'symbol': 'func_15000000', 'state': 'raw_asm', 'vram': '0x15000000'}}},
            {'symbol': 'func_15000060', 'source': SOURCE_PATH, 'overlay': 'game',
             'deferred': {'current_score': 900, 'reason': 'frame differs'},
             'regions': {'us': {'symbol': 'func_15000060', 'state': 'raw_asm', 'vram': '0x15000060'}}},
            {'symbol': 'func_15000020', 'source': SOURCE_PATH, 'overlay': 'game',
             'regions': {'us': {'symbol': 'func_15000020', 'state': 'matched', 'vram': '0x15000020'}}},
        ]
        (root / 'progress/functions.json').write_text(json.dumps({'functions': functions}), encoding='utf-8')
        patcher = mock.patch.object(sweep, 'ROOT', root)
        patcher.start()
        self.addCleanup(patcher.stop)

    def select(self, transform='unchanged', **options):
        values = {'max_score': None, 'sources': [], 'functions': [], 'reason': None, 'rom_word': WORDS.get}
        values.update(options)
        grouped, problems = sweep.select_candidates(transform, **values)
        self.assertEqual([], problems)
        return [item.block.identifier for _, selected in grouped.values() for item in selected]

    def test_filters_by_score_source_function_and_reason(self):
        self.assertEqual(['func_15000000', 'func_15000060'], self.select())
        self.assertEqual(['func_15000000'], self.select(max_score=300))
        self.assertEqual([], self.select(sources=['src/main']))
        self.assertEqual(['func_15000000', 'func_15000060'], self.select(sources=['src/game']))
        self.assertEqual(['func_15000060'], self.select(functions=['func_15000060']))
        self.assertEqual(['func_15000060'], self.select(reason='FRAME'))

    def test_transforms_select_only_candidates_they_change(self):
        self.assertEqual(['func_15000000'], self.select('literals'))
        self.assertEqual([], self.select('literals-inline'))

    def test_unknown_function_is_rejected(self):
        with self.assertRaisesRegex(sweep.SweepError, 'func_15000020'):
            self.select(functions=['func_15000020'])


class TemporaryOutputMixin:
    def setUp(self):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        patcher = mock.patch.object(sweep, 'OUTPUT_ROOT', Path(directory.name))
        patcher.start()
        self.addCleanup(patcher.stop)

    def runner(self, mode='batched'):
        with mock.patch.object(sweep, 'InProcessScorer'):
            runner = sweep.Sweep('unchanged', mode=mode, log=io.StringIO())
        self.addCleanup(runner.close)
        return runner


class InvocationIsolationTests(TemporaryOutputMixin, unittest.TestCase):
    def test_each_invocation_builds_in_its_own_directory(self):
        first, second = self.runner('exact'), self.runner('exact')
        target = sweep.probe.Target('func_A', 'us', Path('src/unit.c'), 'func_A', Path('ref.s'),
                                    Path('ref.o'), 8, Path('build/us/probe/func_A'))
        with mock.patch.object(sweep.probe, 'resolve', return_value=target):
            directories = [first.target('func_A').directory, second.target('func_A').directory]
        self.assertNotEqual(*directories)
        self.assertTrue(all(directory.is_dir() for directory in directories))
        self.assertNotIn(Path('build/us/probe/func_A'), directories)
        first.close()
        self.assertFalse(directories[0].exists())
        self.assertTrue(directories[1].exists())

    def test_tables_are_replaced_atomically(self):
        path = sweep.OUTPUT_ROOT / 'unchanged.tsv'
        sweep.write_atomically(path, 'old\n')
        sweep.write_atomically(path, 'new\n')
        self.assertEqual('new\n', path.read_text())
        self.assertEqual(['unchanged.tsv'], [entry.name for entry in path.parent.iterdir()])


class BatchedConfirmationTests(TemporaryOutputMixin, unittest.TestCase):

    def test_batched_zeros_and_improvements_are_rescored_on_their_own(self):
        blocks, _ = sweep.candidate_blocks(SOURCE, SOURCE_PATH)
        selected = [sweep.Selected(blocks[0], 40, blocks[0].body, ''),
                    sweep.Selected(blocks[1], 900, blocks[1].body, '')]
        runner = self.runner()
        shared = {'func_15000000': 0, 'func_15000060': 950}

        def score_shared(item, source, _candidate, _disassembly):
            return runner.row(item, source, shared[item.block.identifier], '0x18', '0x18')

        def score_isolated(item, source):
            return runner.row(item, source, 12, '0x18', '0x18')

        with mock.patch.object(runner, 'compile_unit', return_value=(Path('unit.o'), {})), \
                mock.patch.object(sweep.probe, 'object_disassembly', return_value=''), \
                mock.patch.object(runner, 'score_shared', side_effect=score_shared), \
                mock.patch.object(runner, 'score_isolated', side_effect=score_isolated) as isolated:
            rows = runner.score_file(SOURCE_PATH, SOURCE, selected)
        self.assertEqual(1, isolated.call_count)
        self.assertEqual([(12, '[batched 0]'), (950, '[batched]')], [(row.new, row.detail) for row in rows])

    def test_unattributed_unit_error_builds_every_candidate_alone(self):
        blocks, _ = sweep.candidate_blocks(SOURCE, SOURCE_PATH)
        selected = [sweep.Selected(block, 1, block.body, '') for block in blocks]
        runner = self.runner()
        error = sweep.UnitError('uopt: Error: internal', {})
        with mock.patch.object(runner, 'compile_unit', side_effect=error), \
                mock.patch.object(runner, 'score_isolated',
                                  side_effect=lambda item, source: runner.row(item, source, 5, '-', '-')):
            rows = runner.score_file(SOURCE_PATH, SOURCE, selected)
        self.assertEqual([5, 5], [row.new for row in rows])


class InventoryParseTests(unittest.TestCase):
    def test_large_identical_text_shares_one_parse_inside_the_context(self):
        text = json.dumps({'functions': ['x' * 70000]})
        with sweep.parse_inventories_once():
            self.assertIs(json.loads(text), json.loads(text))
            self.assertIsNot(json.loads('{"a": 1}'), json.loads('{"a": 1}'))
        self.assertIsNot(json.loads(text), json.loads(text))


if __name__ == '__main__':
    unittest.main()
