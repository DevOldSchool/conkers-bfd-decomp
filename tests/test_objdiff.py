from __future__ import annotations

import hashlib
import importlib.util
import json
import struct
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
SPEC = importlib.util.spec_from_file_location('objdiff_helper', ROOT / 'scripts/objdiff.py')
helper = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(helper)


def elf_fixture():
    """ELF32/MIPS with an unsized function and a following instruction word."""
    data = bytearray(52)
    data[:6] = b'\x7fELF\x01\x02'
    struct.pack_into('>HH', data, 16, 1, 8)
    text_offset = len(data)
    data.extend(struct.pack('>III', 0x03e00008, 0, 0x24020001))
    strings_offset = len(data)
    names = b'\0func_test\0'
    data.extend(names)
    data.extend(b'\0' * (-len(data) % 4))
    symbol_offset = len(data)
    data.extend(bytes(16))
    data.extend(struct.pack('>IIIBBH', 1, 0, 0, 0x10, 0, 1))
    sections_offset = len(data)
    sections = [bytes(40),
                struct.pack('>10I', 0, 1, 6, 0, text_offset, 12, 0, 0, 4, 0),
                struct.pack('>10I', 0, 3, 0, 0, strings_offset, len(names), 0, 0, 1, 0),
                struct.pack('>10I', 0, 2, 0, 0, symbol_offset, 32, 2, 1, 4, 16)]
    data.extend(b''.join(sections))
    struct.pack_into('>I', data, 32, sections_offset)
    struct.pack_into('>HH', data, 46, 40, 4)
    return bytes(data), symbol_offset + 16


class ReferenceBoundaryTests(unittest.TestCase):
    def test_only_symbol_size_and_type_change_not_code_or_neighbors(self):
        original, offset = elf_fixture()
        bounded = helper.bound_reference(original, 'func_test', 8)
        self.assertEqual(struct.unpack_from('>I', bounded, offset + 8)[0], 8)
        self.assertEqual(bounded[offset + 12], 0x12)
        changed = {i for i, (a, b) in enumerate(zip(original, bounded)) if a != b}
        self.assertTrue(changed <= set(range(offset + 8, offset + 13)))
        self.assertEqual(len(original), len(bounded))

    def test_registered_tail_is_preserved(self):
        original, offset = elf_fixture()
        bounded = helper.bound_reference(original, 'func_test', 12)
        self.assertEqual(struct.unpack_from('>I', bounded, offset + 8)[0], 12)
        self.assertEqual(original[52:64], bounded[52:64])

    def test_missing_reference_words_are_rejected(self):
        with self.assertRaisesRegex(ValueError, 'does not cover'):
            helper.bound_reference(elf_fixture()[0], 'func_test', 16)

    def test_missing_symbol_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'found 0'):
            helper.bound_reference(elf_fixture()[0], 'missing', 8)

    def test_invalid_object_or_span_is_rejected(self):
        for data, size in [(b'not ELF', 8), (elf_fixture()[0], 0), (elf_fixture()[0], 7)]:
            with self.subTest(size=size, data=data[:6]), self.assertRaises(ValueError):
                helper.bound_reference(data, 'func_test', size)

    def test_non_mips_object_is_rejected(self):
        data = bytearray(elf_fixture()[0])
        struct.pack_into('>H', data, 18, 3)
        with self.assertRaisesRegex(ValueError, 'MIPS'):
            helper.bound_reference(bytes(data), 'func_test', 8)


class SummaryTests(unittest.TestCase):
    def evidence(self):
        return {'left': {'symbols': [{'name': 'f', 'size': '12', 'target_symbol': 0,
                 'match_percent': 66.6, 'instructions': [
                 {'instruction': {'size': 4}},
                 {'instruction': {'address': '4', 'size': 4}},
                 {'diff_kind': 'DIFF_DELETE', 'instruction': {'address': '8', 'size': 4}}]}]},
                'right': {'symbols': [{'name': 'f', 'size': '8'}]}}

    def test_proto_defaults_and_missing_candidate_tail(self):
        result = helper.summarize(self.evidence(), 'f', 12)
        self.assertTrue(result['reference_span_covered'])
        self.assertEqual(result['candidate_size'], 8)
        self.assertEqual(result['different_rows'], 1)

    def test_truncated_reference_is_flagged_even_if_percent_is_100(self):
        evidence = self.evidence()
        evidence['left']['symbols'][0]['instructions'].pop()
        evidence['left']['symbols'][0]['match_percent'] = 100
        self.assertFalse(helper.summarize(evidence, 'f', 12)['reference_span_covered'])

    def test_unpaired_symbol_is_rejected(self):
        evidence = self.evidence()
        del evidence['left']['symbols'][0]['target_symbol']
        with self.assertRaisesRegex(ValueError, 'did not compare'):
            helper.summarize(evidence, 'f', 12)

    def test_missing_symbol_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'one left symbol'):
            helper.summarize(self.evidence(), 'other', 12)


class InstallerTests(unittest.TestCase):
    def test_cache_is_rechecked_and_bad_download_is_never_installed(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'toolchain').mkdir()
            asset = 'objdiff-cli-macos-arm64'
            lock = {'objdiff_cli': {'version': 'v-test', 'repository': 'https://github.com/encounter/objdiff',
                    'assets': {asset: hashlib.sha256(b'valid').hexdigest()}}}
            (root / 'toolchain/tools.lock.json').write_text(json.dumps(lock))
            cached = root / 'build/host-tools/objdiff-v-test' / asset
            cached.parent.mkdir(parents=True)
            cached.write_bytes(b'valid')
            with patch.object(helper, 'ROOT', root), patch.object(helper.platform, 'system', return_value='Darwin'), \
                 patch.object(helper.platform, 'machine', return_value='arm64'), patch.object(helper.subprocess, 'run') as run:
                self.assertEqual(helper.install(), cached)
                run.assert_not_called()
                cached.write_bytes(b'corrupt')
                def download(command, **kwargs):
                    Path(command[-1]).write_bytes(b'wrong digest')
                run.side_effect = download
                with self.assertRaisesRegex(ValueError, 'checksum mismatch'):
                    helper.install()
                self.assertEqual(cached.read_bytes(), b'corrupt')
                self.assertEqual(list(cached.parent.iterdir()), [cached])

    def test_release_is_pinned_for_supported_hosts(self):
        lock = json.loads((ROOT / 'toolchain/tools.lock.json').read_text())['objdiff_cli']
        self.assertRegex(lock['version'], r'^v\d+\.\d+\.\d+$')
        for asset in ('objdiff-cli-macos-arm64', 'objdiff-cli-macos-x86_64',
                      'objdiff-cli-linux-aarch64', 'objdiff-cli-linux-x86_64'):
            self.assertRegex(lock['assets'][asset], r'^[0-9a-f]{64}$')


if __name__ == '__main__':
    unittest.main()
