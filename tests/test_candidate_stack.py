from __future__ import annotations
import json
from pathlib import Path
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
import automate
import diff
import permute


class CandidateStackTests(unittest.TestCase):
    def test_stack_option_invalidates_diff_and_search_cache_only_when_enabled(self):
        ordinary = automate.parse_args([])
        pilot = automate.parse_args(["--stack-shapes"])
        self.assertFalse(ordinary.stack_shapes)
        self.assertTrue(pilot.stack_shapes)
        self.assertNotEqual(automate.run_fingerprint("tool", ordinary),
                            automate.run_fingerprint("tool", pilot))
        before, after = automate.stage_fingerprint_seeds(ordinary), automate.stage_fingerprint_seeds(pilot)
        self.assertNotEqual(before["diff"], after["diff"])
        self.assertNotEqual(before["permute"], after["permute"])
        self.assertEqual(before["m2c"], after["m2c"])

    def test_stack_classification_requires_same_registers_and_only_sp_offset(self):
        for mnemonic, base, current, expected in (
            ('sw', 'sw v0,0x24(sp)', 'sw v0,0x20(sp)', True),
            ('sb', 'sb v0,37(sp)', 'sb v0,35(sp)', True),
            ('addiu', 'addiu sp,sp,-0x30', 'addiu sp,sp,-0x38', True),
            ('addiu', 'addiu a0,sp,0x24', 'addiu a0,sp,0x20', True),
            ('sw', 'sw v0,0x24(sp)', 'sw v1,0x20(sp)', False),
            ('sw', 'sw v0,0x24(a0)', 'sw v0,0x20(a0)', False),
            ('addiu', 'addiu v0,v0,4', 'addiu v0,v0,8', False),
        ):
            row = {side: {'mnemonic': mnemonic, 'text': [{'text': text, 'format': 'stack'}]}
                   for side, text in [('base', base), ('current', current)]}
            self.assertEqual(expected, diff.is_stack_difference(row), (base, current))

    def test_stack_evidence_routes_separately_without_relaxing_other_operands(self):
        counts = {'register-only': 3, 'operand-or-constant': 2,
                  'opcode-or-control-flow': 0, 'missing-or-extra': 0}
        self.assertEqual(8, automate.Diagnosis(17, counts, 2).search_budget(250, stack_shapes=True))
        self.assertEqual(2, automate.Diagnosis(17, counts, 2).search_budget(2, stack_shapes=True))
        self.assertIsNone(automate.Diagnosis(17, counts, 2).search_budget(250))
        self.assertIsNone(automate.Diagnosis(17, counts, 1).search_budget(250))
        self.assertIsNone(automate.Diagnosis(17, counts).search_budget(250))

    def test_guarded_aggregate_gets_suffix_scope(self):
        source = ('void f(int guard) {\n    Vec local;\n'
                  '    if (guard) { return; }\n'
                  '    local.x = 1;\n    consume(&local);\n}\n')
        variants = permute.stack_source_variants(source, 8)
        self.assertEqual(2, len(variants))
        self.assertIn('if (guard) { return; }\n    {\n    Vec local;', variants[1])
        self.assertIn('consume(&local);\n    }\n}', variants[1])

    def test_scalar_wrapper_preserves_width_addresses_sizeof_and_members(self):
        source = ('s32 f(s32 flag) {\n    u8 local;\n'
                  '    local = 255;\n    if (flag) { local++; }\n'
                  '    consume(&local, sizeof(local), object.local);\n'
                  '    return local;\n}\n')
        variant = permute.stack_source_variants(source, 8)[1]
        self.assertIn('struct { u8 value; } local;', variant)
        self.assertIn('consume(&(local.value), sizeof((local.value)), object.local)', variant)
        self.assertIn('(local.value)++', variant)

    def test_unsupported_control_flow_and_shadowing_are_untouched(self):
        for body in ('while (flag--) { local++; }',
                     'goto end; end: return local;',
                     'if (flag) { s32 local = 2; consume(local); }',
                     'if (flag) { s32 *local; consume(local); }',
                     '#if FLAG\nlocal = 2;\n#endif'):
            source = 's32 f(s32 flag) {\n    s32 local;\n    local = 1;\n' + body + '\nreturn local;\n}\n'
            self.assertEqual([source], permute.stack_source_variants(source, 8), body)
