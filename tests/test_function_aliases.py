"""Address-preserving names must retain existing read-only matching evidence."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / 'scripts'))
import call_signatures
import declaration_facts as facts
import matching_callers
import matching_context


class FunctionAliasTests(unittest.TestCase):
    directive = '#define find_object func_151149AC\n'
    definition = 's32 find_object(u8 id) { return id; }\n'

    def test_only_code_identifiers_are_expanded(self):
        source = (self.directive + self.definition +
                  '/* find_object */\nchar *label = "find_object";\n')
        expected = source.replace('s32 find_object(', 's32 func_151149AC(')
        self.assertEqual(expected, facts.function_alias_text(source))
        self.assertEqual(expected.replace(self.directive.rstrip(), ''),
                         facts.function_alias_text(source, strip_definitions=True))

    def test_unsupported_macros_remain_unresolved(self):
        for directives in (
            '#if PROFILE_US\n' + self.directive + '#endif\n',
            '#if 0\n' + self.directive + '#endif\n',
            self.directive * 2,
            self.directive + '#undef find_object\n',
            self.directive + '#undef /* note */ find_object\n',
            '# /* note */ if FLAG\n' + self.directive + '#endif\n',
            self.directive + '#undef /*\n note */ find_object\n',
            self.directive + '#define func_151149AC other\n',
            self.directive + '#undef func_151149AC\n',
            '#define find_object(x) func_151149AC(x)\n',
            '#define find_object other\n',
            's32 find_object(u8);\n' + self.directive,
            '#if FLAG\n// continued \\\n#endif\n' + self.directive,
            '/*\n' + self.directive + '*/\n',
        ):
            source = directives + self.definition
            with self.subTest(directives=directives):
                self.assertEqual(source, facts.function_alias_text(source))
                self.assertEqual(source, facts.function_alias_text(source, strip_definitions=True))

    def test_unrelated_continuations_preserve_physical_source(self):
        for newline in ('\n', '\r\n'):
            directive = self.directive.replace('\n', newline)
            definition = self.definition.replace('\n', newline)
            macro = '#define other(v) \\\n(find_object(v) + 1) /* find_object */\n'.replace('\n', newline)
            literals = ('// find_object \\\nfind_object\n'
                        'char *label = "find_\\\nobject";\n').replace('\n', newline)
            for source in (macro + directive + definition + literals,
                           directive + definition + literals + macro):
                expected = source.replace('s32 find_object(', 's32 func_151149AC(')
                with self.subTest(newline=newline, source=source):
                    self.assertEqual(expected, facts.function_alias_text(source))
                    self.assertEqual(expected.replace(directive[:-len(newline)], ''),
                                     facts.function_alias_text(source, strip_definitions=True))

    def test_continued_aliases_and_invalidations_remain_unresolved(self):
        cases = (
            '#define find_object \\\nfunc_151149AC\n',
            '#define find_object func_151149AC\\\n\n',
            '#de\\\nfine find_object func_151149AC\n',
            '#define find_\\\nobject func_151149AC\n',
            '\\\n#define find_object func_151149AC\n',
            self.directive + '#un\\\ndef find_object\n',
            self.directive + '#undef find_\\\nobject\n',
            self.directive + '#de\\\nfine find_object other\n',
            self.directive + '#define func_151149AC \\\nother\n',
            self.directive + '#undef func_1511\\\n49AC\n',
            '#i\\\nf FLAG\n' + self.directive + '#endif\n',
            self.directive + 's32 find_\\\nobject(u8);\n',
        )
        for newline in ('\n', '\r\n'):
            for directives in cases:
                source = (directives + self.definition).replace('\n', newline)
                with self.subTest(source=source):
                    self.assertEqual(source, facts.function_alias_text(source))
                    self.assertEqual(source, facts.function_alias_text(source, strip_definitions=True))

    def test_continuations_keep_address_based_evidence(self):
        macro = '#define other \\\n+1\n'
        before = self.definition.replace('find_object', 'func_151149AC') + macro
        after = self.directive + self.definition + macro
        self.assertEqual(call_signatures.source_signatures(before),
                         call_signatures.source_signatures(after))
        self.assertIn('func_151149AC', call_signatures.source_signatures(after))
        self.assertEqual(matching_context.source_bodies(before, {'func_151149AC'}),
                         matching_context.source_bodies(after, {'func_151149AC'}))
        self.assertEqual([], matching_callers.changed_signatures(before, after))

    def test_signature_and_body_lookup_keep_registered_address(self):
        source = self.directive + self.definition
        signatures = call_signatures.source_signatures(source, definitions_only=True)
        self.assertEqual({'func_151149AC': {call_signatures.Signature('s32', ('u8',))}}, signatures)
        source += 'void caller(void) { find_object(1); }\n'
        bodies = matching_context.source_bodies(source, {'func_151149AC', 'caller'}, active_only=True)
        self.assertEqual({'func_151149AC', 'caller'}, set(bodies))
        self.assertEqual({'func_151149AC'}, matching_context.source_calls(bodies['caller']))

    def test_alias_only_edits_are_not_contract_changes(self):
        for result, argument in (('s32', 'u8'), ('LocalType *', 'LocalType *')):
            before = f'{result} func_151149AC({argument});\n'
            after = self.directive + before.replace('func_151149AC(', 'find_object(')
            self.assertEqual([], matching_callers.changed_signatures(before, after))
        changed = self.directive + 'void find_object(u8);\n'
        self.assertEqual(['func_151149AC'], matching_callers.changed_signatures(
            's32 func_151149AC(u8);\n', changed))

    def test_typed_local_prototypes_keep_raw_caller_lookup(self):
        source = self.directive + 'void find_object(LocalType *);\n'
        prototype = facts.Declaration('void func_151149AC(LocalType *);', 'func_151149AC', ())
        self.assertTrue(facts.declaration_already_present(source, prototype))
        declarations, _ = facts.later_function_declarations(
            'void caller(LocalType *p) { func_151149AC(p); }', source, '')
        self.assertEqual(['void func_151149AC(LocalType *);'], declarations)
