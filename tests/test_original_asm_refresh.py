from __future__ import annotations

import copy
import hashlib
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest
from contextlib import ExitStack, redirect_stdout
from types import SimpleNamespace
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
import diff
import original_asm
import prepare_nonmatching_asm
import project_state as state


class OriginalAssemblyRefreshTests(unittest.TestCase):
    def setUp(self):
        self.stack = ExitStack()
        self.addCleanup(self.stack.close)
        self.root = Path(self.stack.enter_context(tempfile.TemporaryDirectory()))
        for name, relative in {'FUNCTIONS_FILE': 'progress/functions.json',
                               'SOURCE_UNITS_FILE': 'progress/source_units.json',
                               'ROMS_FILE': 'config/roms.json', 'OVERLAYS_FILE': 'config/overlays.json',
                               'SUMMARY_FILE': 'build/progress/summary.json', 'DOCUMENT_FILE': 'build/progress/progress.md'}.items():
            self.stack.enter_context(patch.object(state, name, self.root / relative))
        self.stack.enter_context(patch.object(state, 'ROOT', self.root))
        self.stack.enter_context(patch.object(state, 'validate_rom_config'))
        state.write_json(state.ROMS_FILE, {})
        state.write_json(state.OVERLAYS_FILE, {'schema_version': 1, 'overlays': {
            overlay: {'code_ranges': {region: {'start': '0x0', 'end': '0x100'}
                      for region in state.KNOWN_REGIONS}} for overlay in ('main', 'game')}})
        state.write_json(state.SOURCE_UNITS_FILE, {'schema_version': 1, 'source_units': []})
        self.payload = bytes.fromhex('03E00008')
        self.text = 'glabel func_test\n/* 8120 80008120 03E00008 */ jr $ra\n'
        self.source = self.root / 'src/main/test.c'
        self.source.parent.mkdir(parents=True)
        self.source.write_text(state.global_asm_pragma('src/main/test.c', 'func_test') + '\n')
        (self.root / 'evidence.md').write_text('Reviewed original ABI\n')
        self.assembly = self.root / state.nonmatching_asm_path('src/main/test.c', 'func_test')
        self.assembly.parent.mkdir(parents=True)
        self.assembly.write_text(self.text)
        self.entry = {'symbol': 'func_test', 'source': 'src/main/test.c', 'overlay': 'main',
                      'original_asm': {'reason': 'privileged ABI', 'reference': 'evidence.md',
                                       'recorded_revision': 'historical-revision'},
                      'regions': {'us': {'state': 'original_asm', 'symbol': 'func_test',
                         'vram': '0x80008120', 'size_bytes': 4, 'evidence': {
                            'rom_sha1': 'a' * 40, 'span_sha256': hashlib.sha256(self.payload).hexdigest(),
                            'assembly_sha256': 'b' * 64, 'verified_revision': 'working-tree'}}}}
        self.save()

    def save(self, *others):
        state.write_json(state.FUNCTIONS_FILE, {'schema_version': 1, 'functions': [self.entry, *others]})

    def proof_tools(self):
        raw = self.root / 'raw.s'
        raw.write_text(self.text)
        self.stack.enter_context(patch.object(original_asm, 'reference_image',
                                             return_value=(self.payload, 0x80008120, 'a' * 40)))
        self.stack.enter_context(patch.object(diff, 'expected_function_size', return_value=4))
        self.stack.enter_context(patch.object(diff, 'ensure_reference_function', return_value=raw))
        obj = self.root / 'object.o'
        obj.write_bytes(b'object')
        self.stack.enter_context(patch.object(diff, 'reference_object', return_value=obj))
        self.stack.enter_context(patch.object(original_asm, 'Object32', return_value=SimpleNamespace(symbols={})))
        return self.stack.enter_context(patch.object(original_asm.linked_aliases, 'linked_span', return_value=self.payload))

    def args(self, **overrides):
        return SimpleNamespace(**{'symbol': 'func_test', 'refresh': True, 'check': False,
            'reason': None, 'evidence_reference': None, 'proof_output': None,
            'proof': str(self.root / 'proof.json'), **overrides})

    def test_only_selected_stale_text_hash_is_relaxed_and_normal_check_stays_strict(self):
        with self.assertRaisesRegex(state.ProjectStateError, 'changed since verification'):
            state.validate_project()
        state.validate_project(original_asm_refresh='func_test')
        other = copy.deepcopy(self.entry)
        other['symbol'] = other['regions']['us']['symbol'] = 'func_other'
        self.source.write_text(self.source.read_text() + state.global_asm_pragma('src/main/test.c', 'func_other'))
        other_path = self.assembly.with_name('func_other.s')
        other_path.write_text(self.text.replace('func_test', 'func_other'))
        self.save(other)
        with self.assertRaisesRegex(state.ProjectStateError, 'func_other.*changed'):
            state.validate_project(original_asm_refresh='func_test')
        # A multi-item refresh relaxes exactly the named items.
        state.validate_project(original_asm_refresh=['func_test', 'func_other'])
        with self.assertRaisesRegex(state.ProjectStateError, 'func_other.*changed'):
            state.verify_original_asm(self.args())
        with self.assertRaisesRegex(state.ProjectStateError, 'already classified'):
            state.validate_project(original_asm_refresh=['func_test', 'missing'])
        with self.assertRaisesRegex(state.ProjectStateError, '--refresh-with requires'):
            state.verify_original_asm(self.args(refresh=False, check=True, refresh_with=['func_other']))
        self.save()
        with self.assertRaisesRegex(state.ProjectStateError, 'already classified'):
            state.validate_project(original_asm_refresh='missing')
        with self.assertRaisesRegex(state.ProjectStateError, 'cannot combine'):
            state.verify_original_asm(self.args(check=True))
        with self.assertRaisesRegex(state.ProjectStateError, 'changed since verification'):
            state.verify_original_asm(self.args(refresh=False, check=True))
        self.source.write_text('void func_test(void) {}\n')
        with self.assertRaisesRegex(state.ProjectStateError, 'GLOBAL_ASM'):
            state.validate_project(original_asm_refresh='func_test')

    def test_fresh_assembled_proof_rejects_changed_directives_bytes_and_recorded_hashes(self):
        linked = self.proof_tools()
        result = original_asm.verify(self.root, self.entry, refresh=True)
        self.assertEqual(hashlib.sha256(self.text.encode()).hexdigest(), result['assembly_sha256'])
        with self.assertRaisesRegex(ValueError, 'changed since verification'):
            original_asm.verify(self.root, self.entry)
        linked.return_value = bytes(4)
        with self.assertRaisesRegex(ValueError, 'assembled original span differs'):
            original_asm.verify(self.root, self.entry, refresh=True)
        linked.return_value = self.payload
        for key in ('rom_sha1', 'span_sha256'):
            altered = copy.deepcopy(self.entry)
            altered['regions']['us']['evidence'][key] = 'c' * len(altered['regions']['us']['evidence'][key])
            with self.assertRaisesRegex(ValueError, 'recorded ROM or span hash'):
                original_asm.verify(self.root, altered, refresh=True)
        self.assembly.write_text(self.text.replace('03E00008', '00000000'))
        with self.assertRaisesRegex(ValueError, 'US ROM'):
            original_asm.verify(self.root, self.entry, refresh=True)

    def test_proof_hashes_exact_assembled_snapshot_and_host_rejects_intervening_edit(self):
        linked = self.proof_tools()
        def mutate_after_assembly(*args, **kwargs):
            self.assembly.write_text(self.text.replace('jr $ra', 'nop'))
            return self.payload
        linked.side_effect = mutate_after_assembly
        evidence = original_asm.verify(self.root, self.entry, refresh=True)
        self.assertEqual(hashlib.sha256(self.text.encode()).hexdigest(), evidence['assembly_sha256'])
        original = self.root / 'build/us/original-asm/func_test/original.s'
        self.assertEqual(b'.set noat\n.set noreorder\n.set gp=64\n' + self.text.encode(), original.read_bytes())
        proof = self.root / 'proof.json'
        proof.write_text(json.dumps({'symbol': 'func_test', 'evidence': evidence}))
        with self.assertRaisesRegex(ValueError, 'current inputs'):
            original_asm.read_proof(self.root, self.entry, proof)

    def test_record_refresh_preserves_classification_and_rolls_back_on_failure(self):
        self.proof_tools()
        evidence = original_asm.verify(self.root, self.entry, refresh=True)
        (self.root / 'proof.json').write_text(json.dumps({'symbol': 'func_test', 'evidence': evidence}))
        before = state.FUNCTIONS_FILE.read_bytes()
        state.SUMMARY_FILE.parent.mkdir(parents=True, exist_ok=True)
        state.SUMMARY_FILE.write_text('old summary')
        def broken_render(_):
            state.SUMMARY_FILE.write_text('changed summary')
            raise RuntimeError('render failed')
        with patch.object(state, 'render_progress', side_effect=broken_render):
            with self.assertRaisesRegex(RuntimeError, 'render failed'):
                state.verify_original_asm(self.args())
        self.assertEqual(before, state.FUNCTIONS_FILE.read_bytes())
        self.assertEqual('old summary', state.SUMMARY_FILE.read_text())
        with patch.object(state, 'render_progress'), redirect_stdout(io.StringIO()):
            state.verify_original_asm(self.args())
        recorded = state.load_json(state.FUNCTIONS_FILE)['functions'][0]
        self.assertEqual(self.entry['original_asm'], recorded['original_asm'])
        self.assertEqual('original_asm', recorded['regions']['us']['state'])
        self.assertFalse(state.is_complete(recorded))
        self.assertEqual(evidence, recorded['regions']['us']['evidence'])
        state.validate_project()

    def test_materializer_preserves_verified_text_without_reference_and_pruning_keeps_it(self):
        self.entry['regions']['us']['evidence']['assembly_sha256'] = hashlib.sha256(self.assembly.read_bytes()).hexdigest()
        unit = {'source': self.entry['source'], 'functions': ['func_test']}
        with patch.object(prepare_nonmatching_asm, 'ROOT', self.root), \
                patch.object(state, 'validate_functions', return_value=[self.entry]), \
                patch.object(state, 'validate_source_units', return_value=[unit]), \
                patch.object(prepare_nonmatching_asm, 'reference_function_blocks', side_effect=AssertionError('must not regenerate')):
            stale = self.assembly.with_name('stale.s')
            stale.write_text('old unused cache')
            self.assertEqual([], prepare_nonmatching_asm.materialize('us', prune_stale=True))
            self.assertEqual(self.text, self.assembly.read_text())
            self.assertFalse(stale.exists())
            self.assembly.write_text(self.text + '# regenerated spelling\n')
            with self.assertRaisesRegex(state.ProjectStateError, '--refresh'):
                prepare_nonmatching_asm.materialize('us', prune_stale=True)
            self.assertTrue(self.assembly.read_text().endswith('# regenerated spelling\n'))


if __name__ == '__main__':
    unittest.main()
