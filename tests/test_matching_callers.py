from __future__ import annotations

from contextlib import redirect_stdout
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import matching_callers as callers


class ChangedSignatureTests(unittest.TestCase):
    def test_byte_parameter_and_return_changes_are_reported(self):
        self.assertEqual(['glyph'], callers.changed_signatures('void glyph(s32);', 'void glyph(u8);'))
        self.assertEqual(['glyph'], callers.changed_signatures('void glyph(u8);', 's32 glyph(u8);'))

    def test_supported_parameter_names_comments_and_body_changes_are_not_abi_changes(self):
        before = 'void glyph(u8 ch); void draw(s32 x) { glyph(x); }'
        after = '/* annotation */ void glyph( u8 character ); void draw(s32 y) { glyph(y + 1); }'
        self.assertEqual([], callers.changed_signatures(before, after))

    def test_added_or_removed_declarations_are_reported(self):
        self.assertEqual(['glyph'], callers.changed_signatures('', 'void glyph(u8);'))
        self.assertEqual(['glyph'], callers.changed_signatures('void glyph(u8);', ''))

    def test_unsupported_to_unsupported_changes_are_not_lost(self):
        for before, after in [('void effect(OldType *);', 'void effect(NewType *);'),
                              ('void effect();', 's32 effect();'),
                              ('void effect(void (*callback)(u8));', 'void effect(void (*callback)(s32));')]:
            with self.subTest(before=before):
                self.assertEqual(['effect'], callers.changed_signatures(before, after))

    def test_unsupported_body_only_change_does_not_warn(self):
        self.assertEqual([], callers.changed_signatures(
            'Thing *effect(Thing *x) { return x; }',
            'Thing *effect(Thing *x) { return x + 1; }'))

    def test_changed_ambiguous_headers_remain_review_leads(self):
        before = 'void effect(OldType *); void effect(OtherType *);'
        after = 'void effect(NewType *); void effect(OtherType *);'
        self.assertEqual(['effect'], callers.changed_signatures(before, after))

    def test_disabled_candidates_do_not_change_active_signatures(self):
        before = 'void glyph(u8);\n#if 0\nvoid glyph(s32);\n#endif\n'
        self.assertEqual([], callers.changed_signatures(before, before.replace('glyph(s32)', 'glyph(f64)')))


class SignatureClassificationTests(unittest.TestCase):
    def test_new_target_and_its_prototypes_are_additions_without_existing_call_review(self):
        before = 'void existing(void) {}\n#pragma GLOBAL_ASM("raw.s")\n'
        after = 'void existing(void) {}\nvoid callee(u8);\nvoid target(void) { callee(1); }\n'
        self.assertEqual({'changed': [], 'removed': [], 'added': ['callee', 'target'],
                          'added_with_existing_calls': [], 'added_with_uncertain_callers': []},
                         callers.classify_signature_changes(before, after))

    def test_added_prototype_or_definition_used_by_existing_body_requires_review(self):
        before = 'void existing(void) { callee(1); }\n'
        for declaration in ('void callee(u8);\n', 'void callee(u8 x) { }\n'):
            with self.subTest(declaration=declaration):
                result = callers.classify_signature_changes(before, declaration + before)
                self.assertEqual(['callee'], result['added'])
                self.assertEqual(['callee'], result['added_with_existing_calls'])
                self.assertEqual([], result['changed'])

    def test_changed_removed_and_unsupported_signatures_stay_distinct(self):
        before = 'void target(s32); void removed(void); void effect(OldType *);'
        after = 'void target(u8); void effect(NewType *); void added(void);'
        self.assertEqual({'changed': ['effect', 'target'], 'removed': ['removed'],
                          'added': ['added'], 'added_with_existing_calls': [],
                          'added_with_uncertain_callers': []},
                         callers.classify_signature_changes(before, after))

    def test_unknown_conditional_definitions_keep_conservative_addition_review(self):
        before = ('#ifdef FLAG\nvoid existing(void) { callee(1); }\n'
                  '#else\nvoid existing(void) { callee(2); }\n#endif\n')
        result = callers.classify_signature_changes(before, 'void callee(u8);\n' + before)
        self.assertEqual(['callee'], result['added'])
        self.assertEqual([], result['added_with_existing_calls'])
        self.assertEqual(['callee'], result['added_with_uncertain_callers'])

    def test_alternatives_after_if_zero_retain_uncertain_caller_review(self):
        for alternative in ('#else', '#elif 1', '#elif FLAG'):
            with self.subTest(alternative=alternative):
                before = ('#if 0\nvoid disabled(void) {}\n' + alternative +
                          '\nvoid existing(void) { callee(1); }\n#endif\n')
                result = callers.classify_signature_changes(before, 'void callee(u8);\n' + before)
                self.assertEqual(['callee'], result['added_with_uncertain_callers'])

    def test_if_zero_without_alternative_remains_inactive(self):
        before = '#if 0\nvoid disabled(void) { callee(1); }\n#endif\n'
        result = callers.classify_signature_changes(before, 'void callee(u8);\n' + before)
        self.assertEqual([], result['added_with_uncertain_callers'])

    def test_commented_alternative_does_not_create_uncertainty(self):
        before = '/* #if 0\n#else\n*/\nvoid existing(void) {}\n'
        result = callers.classify_signature_changes(before, 'void callee(u8);\n' + before)
        self.assertEqual([], result['added_with_uncertain_callers'])

    def test_inactive_comments_strings_and_member_spellings_do_not_promote_additions(self):
        before = ('void existing(void) { /* callee(1); */ text("callee(2)"); '
                  'ptr->callee(3); obj.callee(4); }\n'
                  '#if 0\nvoid inactive(void) { callee(5); }\n#endif\n')
        result = callers.classify_signature_changes(before, 'void callee(u8);\n' + before)
        self.assertEqual(['callee'], result['added'])
        self.assertEqual([], result['added_with_existing_calls'])

    def test_parameter_names_and_body_edits_do_not_become_contract_changes(self):
        before = 'void callee(u8 x); void existing(s32 x) { callee(x); }'
        after = 'void callee(u8 y); void existing(s32 y) { callee(y + 1); }'
        self.assertTrue(all(not values for values in
                            callers.classify_signature_changes(before, after).values()))


class CallerLookupTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / 'progress').mkdir()
        (self.root / 'src').mkdir()
        self.source = self.root / 'src/a.c'
        self.source.write_text('void glyph(u8);\nvoid matched(void) { glyph(1); other(); glyph(2); }\nvoid comment_only(void) { /* glyph(1); */ text("glyph(1)"); }\nvoid indirect(void) { callback(1); ptr->glyph(2); obj.glyph(3); }\n#if 0\nvoid preserved(void) { glyph(1); }\n#endif\n#pragma GLOBAL_ASM("raw.s")\nvoid duplicate(void) { glyph(1); }\nvoid duplicate(void) { other(); }\nvoid raw_state(void) { glyph(1); }\nvoid unproved(void) { glyph(1); }\nvoid unregistered(void) { glyph(1); }\n')
        entries = []
        for symbol in ('matched', 'comment_only', 'indirect', 'preserved', 'raw', 'duplicate', 'raw_state', 'unproved'):
            entries.append({'symbol': symbol, 'source': 'src/a.c', 'regions': {'us': {
                'symbol': symbol, 'state': 'raw_asm' if symbol == 'raw_state' else 'matched',
                'evidence': {'current_differences': 1 if symbol == 'unproved' else 0}}}})
        self.inventory = self.root / 'progress/functions.json'
        self.inventory.write_text(json.dumps({'functions': entries}))

    def test_only_active_unique_proven_registered_direct_spellings_are_returned(self):
        before = self.source.read_bytes(), self.inventory.read_bytes()
        self.assertEqual([{'symbol': 'matched', 'source': 'src/a.c', 'callees': ['glyph', 'other'],
                           'basis': 'direct C call spelling', 'coverage': 'incomplete'}],
                         callers.affected_callers(self.root, ['other', 'glyph', 'glyph']))
        self.assertEqual(before, (self.source.read_bytes(), self.inventory.read_bytes()))

    def test_duplicate_inventory_ownership_is_not_selected(self):
        data = json.loads(self.inventory.read_text())
        data['functions'].append(data['functions'][0])
        self.inventory.write_text(json.dumps(data))
        self.assertEqual([], callers.affected_callers(self.root, ['glyph']))

    def test_cli_empty_results_still_warn_of_incomplete_coverage(self):
        output = io.StringIO()
        with redirect_stdout(output):
            self.assertEqual(0, callers.main(['unknown', '--root', str(self.root)]))
        result = json.loads(output.getvalue())
        self.assertEqual([], result['callers'])
        self.assertEqual('incomplete', result['coverage'])
        for limitation in ('indirect', 'macro', 'raw ASM'):
            self.assertIn(limitation, result['limitations'])

    def test_invalid_symbol_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'C identifiers'):
            callers.affected_callers(self.root, ['not-a-symbol'])


if __name__ == '__main__':
    unittest.main()
