from __future__ import annotations

import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import build_rsp
from build_rsp import verify_ownership, verify_payload
import project_state


class RspTests(unittest.TestCase):
    def test_comparison_uses_independent_reference_and_rejects_length_changes(self):
        reference = b'\x01\x02\x03\x04'
        digest = hashlib.md5(reference).hexdigest()
        verify_payload(reference, reference, digest, 'test')
        for wrong in (reference[:-1], reference + b'\x00', b'\x01\x02\x00\x04'):
            with self.subTest(wrong=wrong), self.assertRaisesRegex(ValueError, 'payload mismatch'):
                verify_payload(wrong, reference, digest, 'test')
        with self.assertRaisesRegex(ValueError, 'independent ROM range checksum'):
            verify_payload(reference, reference, '0' * 32, 'test')

    def test_ownership_rejects_gaps_overlap_empty_ranges_and_extra_output(self):
        verify_ownership(12, [(8, 12), (0, 8)], 'test')
        for spans in ([(0, 8)], [(0, 8), (9, 12)], [(0, 9), (8, 12)],
                      [(0, 12), (12, 12)], [(0, 13)]):
            with self.subTest(spans=spans), self.assertRaises(ValueError):
                verify_ownership(12, spans, 'test')

    def test_extra_assembler_tail_is_rejected_before_same_named_member_is_sliced(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            for directory in ('config/rsp', 'toolchain', 'roms', 'build/us/lib'):
                (root / directory).mkdir(parents=True)
            reference = b'ABCD'
            (root / 'roms/baserom.us.z64').write_bytes(reference)
            (root / 'toolchain/tools.lock.json').write_text(json.dumps(
                {'tools': {'armips': {'revision': 'pinned-test-revision'}}}))
            revision = root / 'revision'
            revision.write_text('pinned-test-revision')
            config = {'rom_sha1': hashlib.sha1(reference).hexdigest(),
                      'sources': [{'path': 'boot.s', 'code': 'boot.bin'}],
                      'payloads': [{'name': 'boot', 'file': 'boot.bin', 'offset': 0,
                                    'start': 0, 'end': 4, 'kind': 'code', 'section': '.text',
                                    'md5': hashlib.md5(reference).hexdigest()}]}
            (root / 'config/rsp/us.json').write_text(json.dumps(config))
            archive = root / 'build/us/lib/librsp.a'
            archive.write_bytes(b'previous verified archive')

            def assemble(command, **kwargs):
                self.assertEqual(command[0], '/opt/armips/armips')
                Path(command[3]).write_bytes(reference + b'EXTRA')

            with patch.object(build_rsp, 'ROOT', root), \
                 patch.object(build_rsp, 'ARMIPS_REVISION_FILE', revision), \
                 patch.object(build_rsp.subprocess, 'run', side_effect=assemble):
                with self.assertRaisesRegex(ValueError, 'unowned bytes'):
                    build_rsp.main()
            self.assertEqual(archive.read_bytes(), b'previous verified archive')

    def test_rsp_text_does_not_inflate_cpu_progress(self):
        code_ranges = {overlay: {region: (0x1000, 0x3000)
                                for region in project_state.KNOWN_REGIONS}
                       for overlay in project_state.OVERLAYS}
        entries = [(0x1000, 'lib', 'libultra, sdk, .text'),
                   (0x1100, 'lib', 'librsp, rspboot, .text'),
                   (0x1200, 'asm', None),
                   (0x3100, 'lib', 'librsp, asp_overlay1, .text')]
        with patch.object(project_state, 'mapped_subsegments', return_value=entries):
            result = project_state.mapped_library_text_ranges(code_ranges)
        self.assertEqual(result['main']['us'], [(0x1000, 0x1100)])

    def test_source_is_rsp_assembly_and_does_not_embed_rom_instruction_words(self):
        for name in ('rspboot.s', 'asp.s'):
            source = (ROOT / 'src/rsp' / name).read_text()
            self.assertIn('.rsp', source)
            self.assertNotIn('incbin', source.lower())
            code = source.split('.create CODE_FILE,', 1)[1]
            self.assertNotRegex(code, r'\.(?:dw|dh|word|halfword|incbin|fill)\b')

    def test_pinned_tool_and_payload_source_paths_exist(self):
        lock = json.loads((ROOT / 'toolchain/tools.lock.json').read_text())
        self.assertRegex(lock['tools']['armips']['revision'], r'^[0-9a-f]{40}$')
        config = json.loads((ROOT / 'config/rsp/us.json').read_text())
        for source in config['sources']:
            self.assertTrue((ROOT / source['path']).is_file())
        for payload in config['payloads']:
            self.assertGreater(payload['end'], payload['start'])
            self.assertRegex(payload['md5'], r'^[0-9a-f]{32}$')


if __name__ == '__main__':
    unittest.main()
