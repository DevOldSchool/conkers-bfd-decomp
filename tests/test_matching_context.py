from __future__ import annotations

import json
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / 'scripts'))
import matching_context as context


class MatchingContextTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / 'progress').mkdir()
        (self.root / 'config').mkdir()
        (self.root / 'src/game').mkdir(parents=True)
        (self.root / context.INDEX).write_text((context.ROOT / context.INDEX).read_text())
        self.source = self.root / 'src/game/example.c'
        self.source.write_text('''
void helper(void *);
#if 0
void func_target(void *p) { helper(p); }
#endif
void func_near(void *p) { helper(p); }
void func_far(void *p) { unrelated(p); }
#if 0
void func_disabled(void *p) { helper(p); }
#endif
''')
        self.entries = [self.entry('func_target', 0x1000, matched=False),
                        self.entry('func_near', 0x1040),
                        self.entry('func_far', 0x1080),
                        self.entry('func_disabled', 0x1090)]
        self.save_inventory()

    def entry(self, symbol, address, matched=True):
        return {'symbol': symbol, 'overlay': 'game', 'source': 'src/game/example.c',
                'regions': {'us': {'symbol': symbol, 'vram': hex(address), 'size_bytes': 8,
                                   'state': 'matched' if matched else 'raw_asm',
                                   'evidence': {'current_differences': 0 if matched else 100}}}}

    def save_inventory(self):
        (self.root / 'progress/functions.json').write_text(json.dumps({'functions': self.entries}))

    def test_default_is_compact_and_reads_preserved_candidate_calls(self):
        result = context.matching_context(self.root, 'func_target')
        self.assertEqual([], result['mechanisms'])
        self.assertEqual(['helper'], result['callees'])
        self.assertEqual(['func_near'], [item['symbol'] for item in result['family']])
        self.assertEqual(['func_near', 'func_far'], [item['symbol'] for item in result['siblings']])
        rendered = context.render(result)
        self.assertIn('incomplete impact sample', rendered)
        self.assertIn('hypotheses, not ABI or match proof', rendered)

    def test_source_call_lookup_excludes_comment_string_member_and_declaration(self):
        source = '''
/* void func_target(void) { fake_comment(); } */
void func_target(void);
void func_target(void) {
  char *s = "fake_string() { }";
  if (condition) helper();
  obj.callback(); obj->other();
}
void untouched(void) { irrelevant(); }
'''
        body = context.function_body(source, 'func_target')
        self.assertEqual({'helper'}, context.source_calls(body))
        self.assertNotIn('irrelevant', body)

    def test_duplicate_definition_is_not_a_lead(self):
        self.assertEqual('', context.function_body(
            'void f(void) {}\nvoid f(void) {}', 'f'))

    def test_inventory_match_without_zero_evidence_is_not_a_sibling(self):
        del self.entries[1]['regions']['us']['evidence']
        self.save_inventory()
        result = context.matching_context(self.root, 'func_target')
        self.assertEqual([], result['family'])
        self.assertEqual(['func_far'], [item['symbol'] for item in result['siblings']])

    def test_raw_direct_calls_override_stale_candidate_spellings(self):
        raw = self.root / 'asm/nonmatchings/example/func_target.s'
        raw.parent.mkdir(parents=True)
        raw.write_text('glabel func_target\n/* 0 00001000 00000000 */ jal raw_helper\n'
                       '/* 4 00001004 00000000 */ nop\n')
        result = context.matching_context(self.root, 'func_target')
        self.assertEqual(['raw_helper'], result['callees'])
        self.assertIn('raw direct calls', result['call_basis'])
        self.assertEqual([], result['family'])

    def test_incomplete_raw_reference_is_not_used(self):
        raw = self.root / 'asm/nonmatchings/example/func_target.s'
        raw.parent.mkdir(parents=True)
        raw.write_text('glabel func_target\n/* 0 00001000 00000000 */ jal raw_helper\n')
        result = context.matching_context(self.root, 'func_target')
        self.assertEqual(['helper'], result['callees'])
        self.assertIn('unvalidated', result['call_basis'])

    def test_reason_selects_bounded_relevant_mechanisms_and_marks_staleness(self):
        self.entries[0]['deferred'] = {'reason': 'Frame and lifetime mismatch; incorrect prototype.'}
        self.save_inventory()
        result = context.matching_context(self.root, 'func_target', limit=1)
        self.assertEqual(1, len(result['mechanisms']))
        self.assertIn('saved deferred reason; may be stale', result['mechanisms'][0]['selected_by'])
        self.assertEqual(1, len(result['siblings']))
        explicit = context.matching_context(self.root, 'func_target', mechanism='scope-lifetime')
        self.assertEqual(['scope-lifetime'], [item['name'] for item in explicit['mechanisms']])

    def test_unknown_symbol_ambiguous_alias_and_invalid_options_fail(self):
        for options in ({'symbol': 'missing'}, {'symbol': 'func_target', 'limit': 0},
                        {'symbol': 'func_target', 'limit': 11},
                        {'symbol': 'func_target', 'mechanism': 'magic'}):
            with self.subTest(options=options), self.assertRaises(ValueError):
                context.matching_context(self.root, **options)
        self.entries[1]['regions']['us']['symbol'] = 'func_target'
        self.save_inventory()
        with self.assertRaisesRegex(ValueError, 'found 2'):
            context.matching_context(self.root, 'func_target')

    def test_shared_callee_output_and_source_sampling_are_bounded(self):
        self.entries = [self.entries[0]] + [self.entry(f'func_sibling{i}', 0x1010 + i * 4)
                                          for i in range(70)]
        self.save_inventory()
        calls = 'helper(); second(); third();'
        self.source.write_text('void func_target(void) {' + calls + '}\n' + '\n'.join(
            f"void {entry['symbol']}(void) {{ {calls} }}" for entry in self.entries[1:]))
        result = context.matching_context(self.root, 'func_target', limit=1)
        self.assertEqual(64, result['sampled_matched_siblings'])
        self.assertEqual(70, result['total_matched_siblings'])
        self.assertEqual(1, len(result['family']))
        self.assertEqual(1, len(result['family'][0]['shared_callees']))
        self.assertEqual(3, result['family'][0]['shared_callee_count'])
        self.assertIn('(truncated)', context.render(result))

    def test_no_mutations_and_no_other_source_or_raw_scan(self):
        other = self.entry('func_other', 0x1020)
        other['source'] = 'src/game/missing.c'
        self.entries.append(other)
        self.save_inventory()
        before = {path.relative_to(self.root): path.read_bytes()
                  for path in self.root.rglob('*') if path.is_file()}
        context.matching_context(self.root, 'func_target')
        after = {path.relative_to(self.root): path.read_bytes()
                 for path in self.root.rglob('*') if path.is_file()}
        self.assertEqual(before, after)

    def test_repository_index_has_real_tracked_evidence_and_counterexamples(self):
        mechanisms = context.load_index(context.ROOT)
        self.assertEqual({'contracts', 'real-state', 'scope-lifetime'},
                         {item['name'] for item in mechanisms})
        for item in mechanisms:
            self.assertTrue(item['success'])
            self.assertTrue(item['counterexample'])
            for path in item['evidence']:
                self.assertTrue((context.ROOT / path).is_file(), path)


if __name__ == '__main__':
    unittest.main()
