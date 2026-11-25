"""ROM-free checks for ABI-proved SDK symbol metadata repairs."""
import copy
import hashlib
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import objdiff_sdk_metadata as metadata
from objdiff_candidate import Elf


@unittest.skipUnless(shutil.which('mips-linux-gnu-as'), 'requires pinned MIPS binutils')
class ViMetadataTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        source, output = self.root / 'mode.s', self.root / 'mode.o'
        source.write_text('.data\n.globl osViModeNtscLan1\n.type osViModeNtscLan1, @object\n'
                          'osViModeNtscLan1:\n.space 76\n.word 2\n.size osViModeNtscLan1,78\n')
        subprocess.run(['mips-linux-gnu-as', '-EB', '-march=vr4300', '-mabi=32',
                        '-no-pad-sections', '-o', str(output), str(source)], check=True)
        self.raw = output.read_bytes()
        self.obj = Elf(self.raw)

    def test_repairs_size_only_and_keeps_the_nonzero_last_word(self):
        result, proof = metadata.repair_vi_symbol(self.raw, 'osViModeNtscLan1', metadata.VI_LAYOUT)
        after = Elf(result)
        self.assertEqual(after.payload(after.names.index('.data')), bytes(76) + b'\0\0\0\2')
        self.assertEqual(proof['old_size'], 78)
        self.assertEqual(proof['new_size'], 80)
        self.assertTrue(proof['storage_and_relocations_unchanged'])
        self.assertEqual(sum(a != b for a, b in zip(self.raw, result, strict=True)), 1)
        self.assertEqual(metadata.repair_vi_symbol(result, 'osViModeNtscLan1', metadata.VI_LAYOUT)[0], result)

    def test_unknown_symbols_layouts_and_unexpected_extents_fail_closed(self):
        for name, layout in [('other', metadata.VI_LAYOUT), ('osViModeNtscLan1', (78, 40, 20, 76, 2))]:
            with self.subTest(name=name, layout=layout), self.assertRaises(ValueError):
                metadata.repair_vi_symbol(self.raw, name, layout)
        index = next(i for i, s in enumerate(self.obj.symbols) if s[0] == 'osViModeNtscLan1')
        start = self.obj.headers[self.obj.symtab][4] + index * 16
        for offset, value in [(4, 4), (8, 77), (8, 82)]:
            raw = bytearray(self.raw)
            struct.pack_into('>I', raw, start + offset, value)
            with self.subTest(offset=offset, value=value), self.assertRaises(ValueError):
                metadata.repair_vi_symbol(bytes(raw), 'osViModeNtscLan1', metadata.VI_LAYOUT)

    def test_report_hook_requires_archive_and_whole_section_proof(self):
        output = self.root / 'report'
        output.mkdir()
        (output / 'base.o').write_bytes(self.raw)
        archive = self.root / 'build/us/lib/libultra_2_0G.a'
        archive.parent.mkdir(parents=True)
        archive.write_bytes(b'fixture archive')
        payload = self.obj.payload(self.obj.names.index('.data'))
        span = {'section': '.data', 'size': 80, 'kind': 'sdk_placement',
                'owner': {'archive': 'libultra_2_0G', 'member': 'vimodentsclan1.o'},
                'evidence_reference': 'config/profiles/us.yaml', 'candidate_data_relocations': 0,
                'literal_payload_matches_rom': True, 'sha256': hashlib.sha256(payload).hexdigest()}
        unit = {'kind': 'sdk_placement', 'overlay': 'main', 'archive': 'libultra_2_0G',
                'member': 'vimodentsclan1.o', 'key': 'data/fixture', 'base_path': 'base.o',
                'data_ranges': [span], 'complete': True}
        config = {'base_path': 'base.o', 'metadata': {'complete': True}}
        with patch.object(metadata.subprocess, 'check_output', return_value=self.raw), \
                patch.object(metadata, 'compile_vi_layout', return_value={'layout': list(metadata.VI_LAYOUT)}):
            for key, value in [('size', 78), ('literal_payload_matches_rom', False),
                               ('candidate_data_relocations', 1), ('sha256', '0' * 64)]:
                bad = copy.deepcopy(unit)
                bad['data_ranges'][0][key] = value
                with self.subTest(key=key), self.assertRaises(ValueError):
                    metadata.repair_vi_candidates([bad], [copy.deepcopy(config)], self.root, output)
            (output / 'base.o').write_bytes(b'stale')
            with self.assertRaisesRegex(ValueError, 'actual SDK archive'):
                metadata.repair_vi_candidates([unit], [config], self.root, output)
            (output / 'base.o').write_bytes(self.raw)
            metadata.repair_vi_candidates([unit], [config], self.root, output)
        self.assertEqual((output / 'base.o').read_bytes(), self.raw)
        self.assertEqual(unit['comparison_copy']['new_size'], 80)
        self.assertTrue(unit['complete'])
        self.assertTrue(config['metadata']['complete'])

    @unittest.skipUnless(Path('/opt/ido/cc').is_file(), 'requires pinned IDO compiler')
    @unittest.skipUnless((ROOT / 'lib/ultralib/include/PR/os_vi.h').is_file(), 'requires the libultra submodule')
    def test_pinned_sdk_header_compiles_to_the_reviewed_layout(self):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build', prefix='vi-abi-test-') as tmp:
            proof = metadata.compile_vi_layout(ROOT, Path(tmp))
        self.assertEqual(proof['layout'], [80, 40, 20, 76, 4])


if __name__ == '__main__':
    unittest.main()
