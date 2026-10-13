from pathlib import Path
import sys
import tempfile
import shutil
import subprocess
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import objdiff_original_asm as original


class OriginalAssemblyCompletionTests(unittest.TestCase):
    def setUp(self):
        self.spec = {'kind': 'original_asm', 'overlay': 'debugger', 'source': 'src/debugger/tlb.c',
                     'key': 'debugger/tlb', 'original_asm_members': ['f'], 'start': 0x1A20D8, 'end': 0x1A2178}
        self.member = {'symbol': 'f', 'source': self.spec['source'], 'overlay': 'debugger',
                       'regions': {'us': {'state': 'original_asm', 'symbol': 'f',
                                         'vram': '0x16003650', 'size_bytes': 160}}}

    def test_runtime_proof_is_required(self):
        with self.assertRaisesRegex(ValueError, 'runtime image'):
            original.qualify(self.spec, {}, ROOT)

    def test_partial_span_cannot_complete_unit(self):
        self.member['regions']['us']['size_bytes'] = 152
        with patch.object(original.state, 'load_json', return_value={'functions': [self.member]}), \
             patch.object(original.original_asm, 'validate_metadata'), \
             self.assertRaisesRegex(ValueError, 'complete unit'):
            original.qualify(self.spec, {'runtime.elf': 'hash'}, ROOT)

    def test_actual_canonical_placement_is_required(self):
        with patch.object(original.state, 'load_json', return_value={'functions': [self.member]}), \
             patch.object(original.original_asm, 'validate_metadata'), \
             patch.object(original.state, 'mapped_subsegments', return_value=[(0x1A20D8, 'c', 'debugger/tlb'), (0x1A2178, 'data', 'data')]), \
             self.assertRaisesRegex(ValueError, 'canonical ASM placement'):
            original.qualify(self.spec, {'runtime.elf': 'hash'}, ROOT)

    def test_fresh_original_assembly_failure_prevents_completion(self):
        with patch.object(original.state, 'load_json', return_value={'functions': [self.member]}), \
             patch.object(original.original_asm, 'validate_metadata'), \
             patch.object(original.state, 'mapped_subsegments', return_value=[(0x1A20D8, 'asm', 'debugger/tlb'), (0x1A2178, 'data', 'data')]), \
             patch.object(original.prepare_nonmatching_asm, 'materialize'), \
             patch.object(original.objdiff_targets, 'sha256', return_value='hash'), \
             patch.object(original.original_asm, 'verify', side_effect=ValueError('changed instruction')), \
             self.assertRaisesRegex(ValueError, 'changed instruction'):
            original.qualify(self.spec, {'runtime.elf': 'hash'}, ROOT)

    def test_verified_completion_records_maintained_candidate(self):
        import json
        with patch.object(original.state, 'load_json', return_value={'functions': [self.member]}), \
             patch.object(original.original_asm, 'validate_metadata'), \
             patch.object(original.state, 'mapped_subsegments', return_value=[(0x1A20D8, 'asm', 'debugger/tlb'), (0x1A2178, 'data', 'data')]), \
             patch.object(original.prepare_nonmatching_asm, 'materialize'), \
             patch.object(original.objdiff_targets, 'sha256', return_value='hash'), \
             patch.object(original.original_asm, 'verify', return_value={'span_sha256': 'hash'}), \
             patch.object(original.original_asm, 'require_unchanged_span'), \
             patch.object(original, 'prepare_candidate', return_value={
                 'base_path': 'debugger/tlb/base.o', 'candidate_origin': 'maintained_original_assembly',
                 'maintained_source_inputs': {'src/debugger/tlb.s': 'hash'},
                 'maintained_linked_inputs': {'build/us/asm/us/debugger/tlb.o': 'hash'}}):
            result = original.qualify(self.spec, {'runtime.elf': 'hash'}, ROOT)
        self.assertTrue(result['complete'])
        self.assertTrue(result['original_asm_completion_verified'])
        self.assertEqual(result['base_path'], 'debugger/tlb/base.o')
        self.assertEqual(result['source_inputs']['src/debugger/tlb.s'], 'hash')
        self.assertTrue(result['reference_inputs'])
        self.assertTrue(all(p.startswith('asm/') for p in result['reference_inputs']))
        self.assertFalse(any(p.startswith('asm/') for p in result['source_inputs']))
        json.dumps(result)


@unittest.skipUnless(shutil.which('mips-linux-gnu-as') and shutil.which('mips-linux-gnu-ld'),
                     'requires pinned MIPS binutils')
class MaintainedAssemblyProofTests(unittest.TestCase):
    def test_candidate_instructions_padding_and_actual_runtime_are_verified(self):
        good = '.set noreorder\n.text\n.globl f\n.type f,@function\nf:\njr $ra\nnop\n.size f,.-f\n.word 0,0\n'
        for edit, runtime_changes, error in (
            (good, True, None),
            (good.replace('jr $ra', 'jr $t0'), True, 'differs from original bytes'),
            (good.replace('.word 0,0', '.word 1,0'), True, 'differs from original bytes'),
            (good.replace('jr $ra', 'jr $t0'), False, 'actual runtime linker input'),
            (good + '.word 0,0,0,0\n', True, 'full reviewed extent'),
            (good.replace('jr $ra', 'j unreviewed'), True, 'unreviewed external symbol'),
        ):
            with self.subTest(error=error), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                shutil.copy(ROOT / 'Makefile', root / 'Makefile')
                source = root / 'src/debugger/tlb.s'
                source.parent.mkdir(parents=True)
                (root / 'config/symbols').mkdir(parents=True)
                (root / 'config/symbols/us.txt').write_text('')
                (root / 'include').mkdir()
                linked = root / 'build/us/asm/us/debugger/tlb.o'
                linked.parent.mkdir(parents=True)
                source.write_text(edit if runtime_changes else good)
                subprocess.run(['mips-linux-gnu-as', '-W', '-EB', '-march=vr4300', '-mabi=32',
                    '-I', 'include', '-o', str(linked), 'src/debugger/tlb.s'], cwd=root, check=True)
                source.write_text(edit)
                spec = {'source': 'src/debugger/tlb.c', 'key': 'debugger/tlb',
                        'start': 0x1A20D8, 'end': 0x1A20E8, 'original_asm_members': ['f']}
                expected = bytes.fromhex('03e00008000000000000000000000000')
                with patch.object(original.rom_span, 'debugger_code',
                                  return_value=(expected, 0x16003650, 'checked-rom')):
                    if error:
                        with self.assertRaisesRegex(ValueError, error):
                            original.prepare_candidate(spec, root, root / 'report')
                    else:
                        result = original.prepare_candidate(spec, root, root / 'report')
                        self.assertEqual(result['maintained_assembly_proof']['bytes'], 16)
                        self.assertTrue(result['maintained_assembly_proof']['matches_original'])
                        self.assertEqual(result['assembly_source'], 'src/debugger/tlb.s')

    def test_address_label_relocations_still_require_exact_rom_bytes(self):
        source_text = ('.set noreorder\n.text\n.globl f\n.type f,@function\nf:\n'
                       'lui $t0,%hi(D_160038AC)\naddiu $t0,$t0,%lo(D_160038AC)\n'
                       'jr $ra\nnop\n.size f,.-f\n')
        for name, matches in [('D_160038AC', True), ('D_160038B0', False)]:
            with self.subTest(name=name), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                shutil.copy(ROOT / 'Makefile', root / 'Makefile')
                source = root / 'src/debugger/tlb.s'
                source.parent.mkdir(parents=True)
                source.write_text(source_text.replace('D_160038AC', name))
                (root / 'config/symbols').mkdir(parents=True)
                (root / 'config/symbols/us.txt').write_text('')
                (root / 'include').mkdir()
                linked = root / 'build/us/asm/us/debugger/tlb.o'
                linked.parent.mkdir(parents=True)
                subprocess.run(['mips-linux-gnu-as', '-W', '-EB', '-march=vr4300', '-mabi=32',
                    '-I', 'include', '-o', str(linked), 'src/debugger/tlb.s'], cwd=root, check=True)
                spec = {'source': 'src/debugger/tlb.c', 'key': 'debugger/tlb',
                        'start': 0x1A20D8, 'end': 0x1A20E8, 'original_asm_members': ['f']}
                expected = bytes.fromhex('3c081600250838ac03e0000800000000')
                with patch.object(original.rom_span, 'debugger_code',
                                  return_value=(expected, 0x16003650, 'checked-rom')):
                    if matches:
                        self.assertTrue(original.prepare_candidate(spec, root, root / 'report')
                                        ['maintained_assembly_proof']['matches_original'])
                    else:
                        with self.assertRaisesRegex(ValueError, 'differs from original bytes'):
                            original.prepare_candidate(spec, root, root / 'report')

    def test_missing_maintained_source_cannot_use_generated_fallback(self):
        with tempfile.TemporaryDirectory() as tmp, self.assertRaisesRegex(ValueError, 'missing'):
            original.prepare_candidate({'source': 'src/debugger/tlb.c'}, Path(tmp), Path(tmp) / 'report')

class SharedAssemblerSettingsTests(unittest.TestCase):
    def test_report_target_obeys_make_assembler_and_flags(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            fake = root / 'assembler.py'
            fake.write_text('import sys\nfrom pathlib import Path\nPath("args").write_text(" ".join(sys.argv[1:]))\n')
            result = subprocess.run(['make', '-f', str(ROOT / 'Makefile'), 'assemble-maintained',
                                     'AS=' + sys.executable + ' ' + str(fake), 'ASFLAGS=--changed-flag',
                                     'MAINTAINED_SOURCE=source.s', 'MAINTAINED_OBJECT=candidate.o'],
                                    cwd=root, text=True, capture_output=True)
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertEqual((root / 'args').read_text(), '--changed-flag -o candidate.o source.s')
