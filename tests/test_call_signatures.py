from __future__ import annotations

import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / 'scripts'))
import call_signatures as calls
import m2c
import automate
import automation_common


# Synthetic instructions; these fixtures are not copied ROM bytes.
WRAPPER = '''glabel func_wrapper
addiu $sp, $sp, -0x18
sw $ra, 0x14($sp)
addiu $a1, $zero, 7
jal func_target
addiu $a2, $zero, 2
lw $ra, 0x14($sp)
addiu $sp, $sp, 0x18
jr $ra
nop
'''
CALLEE = '''glabel func_target
addiu $sp, $sp, -0x30
sw $ra, 0x14($sp)
sw $a0, 0x30($sp)
sw $a1, 0x34($sp)
sw $a2, 0x38($sp)
lw $t0, 0x30($sp)
lbu $t1, 0x27($t0)
addiu $a3, $zero, 0
jal func_other
nop
lw $ra, 0x14($sp)
addiu $sp, $sp, 0x30
jr $ra
nop
'''
STARTER = 'M2C_UNK func_target(M2C_UNK, M2C_UNK);\nvoid func_wrapper(void) { func_target(7, 2); }\n'
REPAIRED = 'void func_wrapper(void *arg0) { func_target(arg0, 7, 2); }\n'
SDK_CALL = WRAPPER.replace('func_target', 'func_10022EC0')
SDK_DECLARATION = 'void * func_10022EC0(void *, const void *, u32);'
# Minimal SDK contract fixture; no ROM instructions or SDK implementation.
SDK_HEADER = '''#ifndef _MEMORY_H
#define _MEMORY_H
#ifndef _SIZE_T_DEF
#define _SIZE_T_DEF
typedef unsigned size_t;
#endif
void *memcpy(void *,const void *,size_t);
#endif
'''


class CallSignatureTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.source = self.root / 'src/game/example.c'
        self.source.parent.mkdir(parents=True)
        self.source.write_text('#include "types.h"\n')
        (self.root/'include').mkdir()
        (self.root/'include/types.h').write_text('typedef signed int s32;\n')

    def write_raw(self, body=CALLEE):
        lines = body.splitlines()
        body = lines[0] + '\n' + '\n'.join(f'/* {i*4:X} {0x15001000+i*4:08X} 00000000 */ {line}' for i, line in enumerate(lines[1:])) + '\n'
        path = self.root/'asm/nonmatchings/example/func_target.s'
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(body)
        (self.root/'progress').mkdir(exist_ok=True)
        (self.root/'progress/functions.json').write_text(json.dumps({'functions': [{
            'symbol': 'func_target', 'overlay': 'game', 'source': 'src/game/example.c',
            'regions': {'us': {'symbol': 'func_target', 'vram': '0x15001000', 'size_bytes': 4*(len(lines)-1)}}}]}))
        return path

    def write_sdk(self):
        mapping = self.root / calls.SDK_ALIAS_MAP
        mapping.parent.mkdir(parents=True, exist_ok=True)
        mapping.write_text('''/* reviewed US bindings */
SECTIONS
{
    .sdk_test 0x80000000 : { library.a:test.o(.rodata); }
    ASSERT(SIZEOF(.sdk_test) == 0x10, "unexpected section size")
}
memcpy = 0x10022EC0;
unrelated = 0x10003000;
func_151F0000 = other_sdk_function;
''')
        header = self.root / calls.SDK_MEMORY_HEADER
        header.parent.mkdir(parents=True, exist_ok=True)
        header.write_text(SDK_HEADER)
        return mapping, header

    def write_matched(self, definition='void func_target(u8 *arg0) {}'):
        self.write_raw()
        self.source.write_text(definition + '\n')
        path = self.root / 'progress/functions.json'
        data = json.loads(path.read_text())
        data['functions'][0]['regions']['us'].update(
            state='matched', evidence={'current_differences': 0})
        path.write_text(json.dumps(data))
        (self.root / 'src/game/other.c').write_text('s32 func_target(s32, ...);\n')
        return path, data

    def test_matched_definition_overrides_speculative_external_prototypes(self):
        self.write_matched()
        recovery = calls.recover(WRAPPER, '', root=self.root)
        self.assertEqual(('void func_target(u8 *);',), recovery.declarations)
        self.assertEqual(('func_target: matched US definition in src/game/example.c',), recovery.evidence)
        declaration = calls.declaration_facts.function_declaration(
            'func_target', 'M2C_UNK', root=self.root)
        self.assertEqual(('matched US definition in src/game/example.c',), declaration.evidence)

    def test_matched_definition_does_not_replace_local_contract(self):
        self.write_matched()
        local = 'void func_target(void *);'
        self.assertEqual((local,), calls.recover(WRAPPER, local, root=self.root).declarations)
        for local in ('void func_target();', 'void func_target(Private *);',
                      'void func_target(s32); s32 func_target(s32);'):
            with self.subTest(local=local):
                self.assertEqual((), calls.recover(WRAPPER, local, root=self.root,
                                                  allow_raw=True).declarations)

    def test_only_registered_exact_us_definition_can_override_conflicts(self):
        for mutation in ('raw', 'nonzero', 'missing_evidence', 'wrong_source', 'duplicate', 'malformed'):
            with self.subTest(mutation=mutation):
                path, data = self.write_matched()
                entry = data['functions'][0]
                if mutation == 'raw':
                    entry['regions']['us']['state'] = 'raw'
                elif mutation == 'nonzero':
                    entry['regions']['us']['evidence']['current_differences'] = 1
                elif mutation == 'missing_evidence':
                    del entry['regions']['us']['evidence']
                elif mutation == 'wrong_source':
                    entry['source'] = 'src/game/other.c'
                elif mutation == 'duplicate':
                    data['functions'].append(entry.copy())
                path.write_text('not json' if mutation == 'malformed' else json.dumps(data))
                self.assertEqual((), calls.recover(WRAPPER, '', root=self.root).declarations)
        self.write_matched()
        self.assertEqual((), calls.recover(WRAPPER, '', root=self.root, profile='eu').declarations)

    def test_ambiguous_or_unusable_matched_definitions_do_not_override_conflicts(self):
        for definition in ('void func_target(u8 *);',
                           '#if 0\nvoid func_target(u8 *p) {}\n#endif',
                           'void func_target(Private *p) {}',
                           'static void func_target(u8 *p) {}',
                           'void func_target() {}',
                           'void func_target(u8 *p) {} void func_target(u8 *p) {}',
                           's32 func_target(u8 *); void func_target(u8 *p) {}'):
            with self.subTest(definition=definition):
                self.write_matched(definition)
                self.assertEqual((), calls.recover(WRAPPER, '', root=self.root).declarations)
        self.write_matched()
        (self.root / 'src/game/other.c').write_text('s32 func_target(s32 p) { return p; }')
        self.assertEqual((), calls.recover(WRAPPER, '', root=self.root).declarations)

    def test_match_state_and_definition_change_invalidate_callee_digest(self):
        path, data = self.write_matched()
        before = calls.dependency_digest(self.root, WRAPPER)
        self.assertEqual(before, calls.dependency_digest(self.root, WRAPPER, calls.signature_index(self.root)))
        self.source.write_text('void func_target(u32 *arg0) {}')
        self.assertNotEqual(before, calls.dependency_digest(self.root, WRAPPER))
        self.source.write_text('void func_target(u8 *arg0) {}')
        data['functions'][0]['regions']['us']['state'] = 'raw'
        path.write_text(json.dumps(data))
        self.assertNotEqual(before, calls.dependency_digest(self.root, WRAPPER))

    def test_sdk_alias_recovers_return_const_pointer_and_unsigned_length(self):
        self.write_sdk()
        # Conflicting views elsewhere cannot override an identified SDK callee.
        self.source.write_text('void func_10022EC0(s32, void *, s32);\n')
        (self.source.parent / 'other.c').write_text('void func_10022EC0(void *, void *, s32);\n')
        recovery = calls.recover(SDK_CALL, '', root=self.root)
        self.assertEqual((SDK_DECLARATION,), recovery.declarations)
        self.assertIn('verified SDK alias memcpy=', recovery.evidence[0])
        self.assertIn(calls.SDK_MEMORY_HEADER, recovery.evidence[0])
        self.assertNotIn(calls.ABI_MARKER, recovery.declarations[0])
        self.assertEqual({calls.Signature('void *', ('void *', 'const void *', 'u32'))},
                         calls.source_signatures(SDK_DECLARATION)['func_10022EC0'])

    def test_sdk_alias_keeps_allowed_source_precedence_and_blockers(self):
        self.write_sdk()
        local = 'void func_10022EC0(void *, void *, s32);\n'
        self.assertEqual((local.strip(),), calls.recover(SDK_CALL, local, root=self.root).declarations)
        for local in ('void func_10022EC0();',
                      'void func_10022EC0(LocalType *);',
                      'static void func_10022EC0(void);',
                      SDK_DECLARATION + '\nvoid func_10022EC0(s32);'):
            with self.subTest(local=local):
                self.assertEqual((), calls.recover(SDK_CALL, local, root=self.root,
                                                   allow_raw=True).declarations)

    def test_sdk_alias_requires_both_binding_and_matching_header(self):
        mapping, header = self.write_sdk()
        for contents in ('/* ' + SDK_HEADER + ' */',
                         '#if 0\n' + SDK_HEADER + '\n#endif',
                         SDK_HEADER.replace('typedef unsigned size_t;', 'typedef signed size_t;'),
                         SDK_HEADER.replace('typedef unsigned size_t;', ''),
                         SDK_HEADER.replace('void *memcpy', 'void memcpy'),
                         SDK_HEADER.replace('const void *', 'void *'),
                         SDK_HEADER + '\nvoid memcpy(void);\n'):
            with self.subTest(header=contents):
                header.write_text(contents)
                self.assertEqual((), calls.recover(SDK_CALL, '', root=self.root).declarations)
        header.unlink()
        self.assertEqual((), calls.recover(SDK_CALL, '', root=self.root).declarations)
        header.write_text(SDK_HEADER)
        mapping.unlink()
        self.assertEqual((), calls.recover(SDK_CALL, '', root=self.root).declarations)

    def test_sdk_alias_rejects_ambiguous_expression_and_unreviewed_bindings(self):
        mapping, _ = self.write_sdk()
        for contents in ('memcpy = 0x10022EC0; memcpy = 0x10022ED0;',
                         'memcpy = 0x10022EC0; memcpy = 0x10022EC0;',
                         'memcpy = 0x10022EC0; unrelated = 0x10022EC0;',
                         'memcpy = 0x10022EC0 + 4;',
                         'memcpy = unknown_function;',
                         'memcpy = 0x10022EC0',
                         '/* memcpy = 0x10022EC0; */',
                         'memcpy = 0x10022EC2;',
                         'memcpy = 0x0;',
                         'SECTIONS { memcpy = 0x10022EC0; }',
                         'data_pointer = 0x10022EC0;',
                         'memmove = 0x10022EC0;'):
            with self.subTest(mapping=contents):
                mapping.write_text(contents)
                self.assertEqual((), calls.recover(SDK_CALL, '', root=self.root).declarations)

    def test_sdk_alias_is_us_only_and_follows_the_map_address(self):
        mapping, _ = self.write_sdk()
        self.assertEqual((), calls.recover(SDK_CALL, '', root=self.root, profile='eu').declarations)
        mapping.write_text('memcpy = 0x10023000;\n')
        self.assertEqual((), calls.recover(SDK_CALL, '', root=self.root).declarations)
        self.assertEqual((SDK_DECLARATION.replace('10022EC0', '10023000'),), calls.recover(
            SDK_CALL.replace('10022EC0', '10023000'), '', root=self.root).declarations)

    def test_sdk_alias_is_supplied_before_m2c_and_reemitted_with_evidence(self):
        self.write_sdk()
        def decompile(command, **kwargs):
            context = self.root / command[command.index('--context') + 1]
            self.assertIn(SDK_DECLARATION, context.read_text())
            return SimpleNamespace(returncode=0, stdout='void *func_wrapper(void *p, const void *q, u32 n) { return func_10022EC0(p, q, n); }')
        with patch.object(m2c, 'ROOT', self.root), patch.object(m2c.subprocess, 'run', side_effect=decompile) as run:
            output, status = m2c.generate_with_call_context(['m2c', 'input.s'], SDK_CALL,
                                                          'func_wrapper', self.source, 'us')
        self.assertEqual(0, status)
        self.assertEqual(1, run.call_count)
        self.assertIn(SDK_DECLARATION, output)
        self.assertIn('verified SDK alias memcpy=', output)
        prepared = automate.candidate_rewrites.prepare_starter(
            output, 'func_wrapper', self.source.read_text(), root=self.root)
        self.assertEqual((SDK_DECLARATION,), prepared.declarations)
        self.assertEqual('#include "types.h"\n', self.source.read_text())
        record = json.loads((self.root / 'build/m2c/calls/func_wrapper.json').read_text())
        self.assertEqual([SDK_DECLARATION], record['declarations'])
        self.assertIn(calls.SDK_ALIAS_MAP, record['evidence'][0])

    def test_sdk_inputs_invalidate_saved_raw_and_deferred_stage_results(self):
        mapping, header = self.write_sdk()
        with patch.object(automate, 'ROOT', self.root):
            args = automate.parse_args(['--all'])
            for path in (mapping, header):
                before = automate.stage_fingerprint_seeds(args)
                path.write_text(path.read_text() + '\n/* updated SDK evidence */\n')
                after = automate.stage_fingerprint_seeds(args)
                self.assertEqual(before['inventory'], after['inventory'])
                for stage in ('m2c', 'declarations', 'prepare', 'compile', 'diff', 'permute', 'finish'):
                    self.assertNotEqual(before[stage], after[stage])
            snapshot = calls.signature_index(self.root)
            before = calls.dependency_digest(self.root, SDK_CALL)
            self.assertEqual(before, calls.dependency_digest(self.root, SDK_CALL, snapshot))
            mapping.write_text('memcpy = 0x10023000;\n')
            self.assertNotEqual(before, calls.dependency_digest(self.root, SDK_CALL))

    def test_sdk_placeholder_resolution_preserves_known_type_and_arity_checks(self):
        self.write_sdk()
        facts = calls.declaration_facts
        prefix = 'M2C_UNK func_10022EC0(M2C_UNK, M2C_UNK, M2C_UNK);'
        declarations, evidence = facts.resolve_required_declarations(prefix, '', root=self.root)
        self.assertEqual([SDK_DECLARATION], declarations)
        self.assertIn(calls.SDK_ALIAS_MAP, evidence[0])
        for prefix in ('void func_10022EC0(M2C_UNK, M2C_UNK, M2C_UNK);',
                       'M2C_UNK func_10022EC0(M2C_UNK, M2C_UNK, s32);',
                       'M2C_UNK func_10022EC0(M2C_UNK, M2C_UNK);'):
            with self.subTest(prefix=prefix), self.assertRaises(facts.DeclarationError):
                facts.resolve_required_declarations(prefix, '', root=self.root)

    def test_forwarded_a0_and_delay_slot_constants(self):
        self.assertEqual(('func_target', ('$a0', 7, 2, '$a3')), calls.wrapper_call(WRAPPER))
        self.assertEqual(('void *', 's32', 's32'), calls.callee_home_arguments(CALLEE))
        self.write_raw()
        recovery = calls.recover(WRAPPER, '', root=self.root, allow_raw=True)
        self.assertEqual(('void func_target(void *, s32, s32); /* CONKER_ABI_DISCARDED_RETURN */',), recovery.declarations)
        self.assertIn('caller discards result', recovery.evidence[0])

    def test_raw_is_not_used_without_explicit_discarded_result_gate(self):
        self.write_raw()
        self.assertEqual((), calls.recover(WRAPPER, '', root=self.root).declarations)
        self.assertTrue(calls.discarded_call(STARTER, 'func_wrapper', 'func_target'))
        self.assertFalse(calls.discarded_call('s32 func_wrapper(void) { return func_target(7, 2); }', 'func_wrapper', 'func_target'))

    def test_delay_slot_moves_track_current_register_value(self):
        asm = WRAPPER.replace('addiu $a1, $zero, 7', 'move $a1, $a0').replace('addiu $a2, $zero, 2', 'move $a2, $a1')
        self.assertEqual(('$a0', '$a0', '$a0', '$a3'), calls.wrapper_call(asm)[1])

    def test_full_reference_preamble_and_unused_parameter_home(self):
        asm = '.include "macro.inc"\n.set noat\n.set noreorder\n' + WRAPPER
        asm = asm.replace('sw $ra, 0x14($sp)', 'sw $ra, 0x14($sp)\nsw $a2, 0x20($sp)')
        self.assertEqual(('func_target', ('$a0', 7, 2, '$a3')), calls.wrapper_call(asm))

    def test_discard_only_declaration_is_never_reused_as_return_type_evidence(self):
        self.write_raw()
        self.source.write_text('void func_target(void *, s32, s32); /* CONKER_ABI_DISCARDED_RETURN */\n')
        self.assertNotIn('func_target', calls.signature_index(self.root))
        with patch.object(m2c, 'ROOT', self.root):
            self.assertNotIn('func_target', m2c.flattened_source_context(self.source))
            with patch.object(m2c.subprocess, 'run', return_value=SimpleNamespace(returncode=0, stdout='s32 func_wrapper(void) { return func_target(7, 2); }')) as run:
                output, status = m2c.generate_with_call_context(['m2c', 'input.s'], WRAPPER, 'func_wrapper', self.source, 'us')
        self.assertEqual(1, run.call_count)
        self.assertNotIn(calls.ABI_MARKER, output)
        self.assertEqual(0, status)

    def test_branch_indirect_multiple_call_stack_and_float_wrappers_are_rejected(self):
        for replacement in ['beqz $a0, .Lelse', 'jalr $t9', 'sw $a0, 0x10($sp)', 'mov.s $f12, $f0', 'jal func_other']:
            with self.subTest(replacement=replacement):
                self.assertIsNone(calls.wrapper_call(WRAPPER.replace('addiu $a1, $zero, 7', replacement)))

    def test_missing_partial_variadic_or_live_higher_homes_are_rejected(self):
        for asm in [CALLEE.replace('sw $a1, 0x34($sp)', 'nop'),
                    CALLEE.replace('sw $a1, 0x34($sp)', 'sb $a1, 0x34($sp)'),
                    CALLEE.replace('addiu $a3, $zero, 0', 'nop'),
                    CALLEE.replace('addiu $a3, $zero, 0', 'sw $a3, 0x3c($sp)'),
                    CALLEE.replace('lbu $t1, 0x27($t0)', 'mtc1 $a0, $f12')]:
            self.assertIsNone(calls.callee_home_arguments(asm))

    def test_delay_slot_live_argument_is_not_lost(self):
        self.assertIsNone(calls.callee_home_arguments(CALLEE.replace('jal func_other\nnop', 'jal func_other\nmove $t8, $a3').replace('addiu $a3, $zero, 0', 'nop')))

    def test_later_stack_argument_and_argument_area_address_are_rejected(self):
        for instruction in ['lw $t7, 0x40($sp)', 'addiu $t7, $sp, 0x30']:
            self.assertIsNone(calls.callee_home_arguments(CALLEE.replace('lw $ra, 0x14($sp)', instruction + '\nlw $ra, 0x14($sp)')))

    def test_unhomed_argument_cannot_hide_in_local_spill_or_earlier_store(self):
        for store in ['sw $a3, 0x18($sp)', 'sw $a3, 0($a0)']:
            self.assertIsNone(calls.callee_home_arguments(CALLEE.replace('addiu $a3, $zero, 0', store + '\naddiu $a3, $zero, 0')))

    def test_malformed_operands_fail_closed(self):
        self.assertIsNone(calls.wrapper_call(WRAPPER.replace('addiu $a1, $zero, 7', 'addiu $a1, $zero, nonsense')))
        self.assertIsNone(calls.callee_home_arguments(CALLEE.replace('addiu $sp, $sp, -0x30', 'addiu $sp, $sp, nonsense')))

    def test_raw_span_and_profile_are_validated(self):
        path = self.write_raw()
        self.assertEqual(path, calls.raw_callee_path(self.root, 'func_target'))
        self.assertEqual((), calls.recover(WRAPPER, '', root=self.root, profile='eu', allow_raw=True).declarations)
        path.write_text(path.read_text().replace('15001004', '15009004'))
        self.assertIsNone(calls.raw_callee_path(self.root, 'func_target'))
        self.assertEqual((), calls.recover(WRAPPER, '', root=self.root, allow_raw=True).declarations)

    def test_existing_prototype_precedes_raw_and_conflicts_block_fallback(self):
        self.write_raw()
        self.source.write_text('s32 func_target(void *arg0, s32 arg1, s32 arg2);\n')
        recovery = calls.recover(WRAPPER, '', root=self.root, allow_raw=True)
        self.assertEqual(('s32 func_target(void *, s32, s32);',), recovery.declarations)
        other = self.root/'src/game/other.c'
        other.write_text('void func_target(void *, s32, s32);\n')
        self.assertEqual((), calls.recover(WRAPPER, '', root=self.root, allow_raw=True).declarations)

    def test_allowed_source_signature_precedes_unrelated_call_views(self):
        self.source.write_text('void func_target(s32);\n')
        local = 's32 func_target(void *, s32, s32);\n'
        recovery = calls.recover(WRAPPER, local, root=self.root)
        self.assertEqual(('s32 func_target(void *, s32, s32);',), recovery.declarations)
        self.assertIn('allowed source', recovery.evidence[0])

    def test_ambiguous_or_unsupported_local_signature_blocks_fallback(self):
        self.write_raw()
        self.source.write_text('s32 func_target(void *, s32, s32);\n')
        for local in ('void func_target(s32);\ns32 func_target(s32);\n',
                      'void func_target();\n', 'static void func_target(s32);\n',
                      'void func_target(Other *);\n'):
            with self.subTest(local=local):
                self.assertEqual((), calls.recover(WRAPPER, local, root=self.root,
                                                  allow_raw=True).declarations)

    def test_disabled_and_nested_local_signatures_do_not_override_project(self):
        self.source.write_text('s32 func_target(void *, s32, s32);\n')
        local = ('/* void func_target(s32); */\n#if 0\nvoid func_target(s32);\n#endif\n'
                 'void outer(void) { extern void func_target(s32); }\n')
        self.assertEqual(('s32 func_target(void *, s32, s32);',),
                         calls.recover(WRAPPER, local, root=self.root).declarations)

    def test_comments_disabled_and_nested_declarations_are_not_evidence(self):
        self.source.write_text('/* void func_target(s32); */\n#if 0\nvoid func_target(s32);\n#endif\nvoid outer(void) { extern void func_target(s32); }\n')
        self.assertNotIn('func_target', calls.signature_index(self.root))

    def test_static_unknown_typedef_old_style_and_variadic_are_not_imported(self):
        for decl in ['static void func_target(s32);', 'void func_target(Other *p);',
                     'void func_target();', 'void func_target(s32, ...);']:
            self.source.write_text(decl)
            self.assertIsNone(calls.signature_index(self.root)['func_target'])

    def test_pointer_return_and_parameter_names_are_normalized(self):
        self.source.write_text('void *func_target(void *arg0, unsigned int arg1);')
        self.assertEqual(calls.Signature('void *', ('void *', 'unsigned int')), calls.signature_index(self.root)['func_target'])

    def test_two_pass_m2c_regenerates_and_reemits_the_prototype(self):
        self.write_raw()
        results = [SimpleNamespace(returncode=0, stdout=STARTER), SimpleNamespace(returncode=0, stdout=REPAIRED)]
        with patch.object(m2c, 'ROOT', self.root), patch.object(m2c.subprocess, 'run', side_effect=results) as run:
            output, status = m2c.generate_with_call_context(['python3', 'm2c.py', 'input.s'], WRAPPER, 'func_wrapper', self.source, 'us')
        self.assertEqual(0, status)
        self.assertEqual(2, run.call_count)
        self.assertIn('--context', run.call_args.args[0])
        self.assertIn('void func_target(void *, s32, s32);', output)
        self.assertIn('func_target(arg0, 7, 2)', output)
        self.assertEqual('#include "types.h"\n', self.source.read_text())
        self.assertTrue((self.root/'build/m2c/calls/func_wrapper.json').is_file())

    def test_failed_regeneration_is_not_silently_accepted(self):
        self.write_raw()
        results = [SimpleNamespace(returncode=0, stdout=STARTER), SimpleNamespace(returncode=1, stdout='failure')]
        with patch.object(m2c, 'ROOT', self.root), patch.object(m2c.subprocess, 'run', side_effect=results):
            output, status = m2c.generate_with_call_context(['m2c', 'input.s'], WRAPPER, 'func_wrapper', self.source, 'us')
        self.assertEqual(('failure', 1), (output, status))

    def test_resume_fingerprint_tracks_callee_and_prototype_changes(self):
        path = self.write_raw()
        wrapper = self.root/'asm/nonmatchings/example/func_wrapper.s'
        wrapper.write_text(WRAPPER)
        candidate = automate.automation_common.RawCandidate('func_wrapper', 'func_wrapper', 'src/game/example.c', 36)
        with patch.object(automate, 'ROOT', self.root):
            before = automate.candidate_fingerprint(candidate, 'seed')
            path.write_text(path.read_text().replace('0x27($t0)', '0x28($t0)'))
            self.assertNotEqual(before, automate.candidate_fingerprint(candidate, 'seed'))
            args = automate.parse_args(['--all'])
            seeds = automate.stage_fingerprint_seeds(args)
            baseline = automate.candidate_fingerprint(candidate, seeds['declarations'])
            other = self.root/'src/game/other.c'
            other.write_text('void unrelated(s32);')
            self.assertEqual(baseline, automate.candidate_fingerprint(candidate, seeds['declarations']))
            self.source.write_text('void func_target(void *, s32, s32);')
            changed = automate.stage_fingerprint_seeds(args)
            self.assertNotEqual(baseline, automate.candidate_fingerprint(candidate, changed['declarations']))
        self.assertEqual(seeds, changed)


if __name__ == '__main__':
    unittest.main()
