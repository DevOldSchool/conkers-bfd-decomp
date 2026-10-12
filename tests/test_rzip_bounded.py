"""EOF decisions, 16K block boundaries and reproducible native encoder builds."""
import hashlib
from pathlib import Path
import random
import shutil
import struct
import subprocess
import tempfile
import unittest
from unittest.mock import patch
import zlib
from scripts import rzip_bounded as codec, model_build

# Synthetic random bytes from Random(17), never extracted ROM contents.
EOF_VECTOR = bytes.fromhex(
    '0105000401060501040403010307030402060306000102020106030306040406010704'
    '0100000101070105060602020200020102030701010706050207060605000700060603'
    '000706030301020603040006030707020303010202050000000007040302030507000000')


@unittest.skipUnless(shutil.which('cc'), 'requires a host C compiler')
class BoundedEncoderTests(unittest.TestCase):
    def test_eof_and_16k_block_vectors_and_independent_decode(self):
        rng = random.Random(531)
        vectors = [(EOF_VECTOR, 'bc812a5449373406715afd1fd38b7a9c2e21921d917c09b0e768c8f8b2dcdf18'),
                   (bytes(rng.randrange(256) for _ in range(40000)),
                    '7c7df51f44a8f1695688cf59724b28e2156aa2857c6816a401f1a806ba1e33b1')]
        for data, expected in vectors:
            encoded = codec.encode_payload(data)
            self.assertEqual(hashlib.sha256(encoded).hexdigest(), expected)
            self.assertEqual(struct.unpack('>I', encoded[:4])[0], len(data))
            self.assertEqual(zlib.decompress(encoded[4:], -15), data)
        for size in (0, 1, 2, 3, 257, 258, 259, 32768, 65536, 100000):
            data = (bytes(range(251)) * ((size + 250) // 251))[:size]
            self.assertEqual(zlib.decompress(codec.encode_payload(data)[4:], -15), data)

    def test_cache_repairs_corruption_and_changes_with_sources(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            shutil.copytree(codec.ROOT / codec.SOURCE, root / codec.SOURCE)
            binary = codec.executable(root)
            before = binary.read_bytes(), binary.stat().st_mtime_ns
            self.assertEqual(codec.executable(root), binary)
            self.assertEqual((binary.read_bytes(), binary.stat().st_mtime_ns), before)
            binary.write_bytes(b'corrupt')
            self.assertEqual(codec.executable(root).read_bytes(), before[0])
            source = root / codec.SOURCE / 'main.c'
            source.write_text(source.read_text() + '\n/* distinct source revision */\n')
            other = codec.executable(root)
            self.assertNotEqual(other, binary)
            output = subprocess.check_output([str(other), '6'], input=EOF_VECTOR)
            self.assertEqual(zlib.decompress(output, -15), EOF_VECTOR)

    def test_missing_compiler_and_source_race_fail_without_cached_success(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            shutil.copytree(codec.ROOT / codec.SOURCE, root / codec.SOURCE)
            with patch.object(codec.shutil, 'which', return_value=None):
                with self.assertRaisesRegex(ValueError, 'requires a C compiler'):
                    codec.executable(root)
            before = codec.source_hashes(root)
            with patch.object(codec, 'source_hashes', side_effect=[before, dict(before, changed='yes')]):
                with self.assertRaisesRegex(ValueError, 'changed during compilation'):
                    codec.executable(root)
            self.assertEqual(list((root / 'build/tools/bounded-deflate').glob('*/encoder')), [])


class BoundedContractTests(unittest.TestCase):
    def test_explicit_model_selection_is_reviewed_and_disjoint(self):
        contract = {'banks': {'03': [1, 2, 3], '09': [4]},
                    'level6_entries': {'03': [1], '09': []},
                    'gzip6_entries': {'03': [2], '09': []}}
        self.assertEqual(model_build.bounded_selections(contract), {'03': [], '09': []})
        choices = {'03': [3], '09': [4]}
        self.assertEqual(model_build.bounded_selections(dict(contract, bounded_entries=choices)), choices)
        for choices in ({'03': [1], '09': []}, {'03': [2], '09': []}, {'03': [5], '09': []},
                        {'03': [3, 3], '09': []}, {'03': [True], '09': []}, {'03': []}):
            with self.assertRaises(ValueError):
                model_build.bounded_selections(dict(contract, bounded_entries=choices))
        with patch.object(codec, 'encode_payload', return_value=b'exact') as encoder:
            self.assertEqual(model_build.encode_model_payload(b'source', dict(codec.ENCODER)), b'exact')
            encoder.assert_called_once_with(b'source')
        with self.assertRaises(ValueError):
            model_build.encode_model_payload(b'source', dict(codec.ENCODER, token_buffer=32768))

    def test_unsupported_levels_and_failed_independent_decode_rejected(self):
        for level in (True, 0, 9, '6'):
            with self.assertRaises(ValueError): codec.encode_payload(b'data', level)
        with patch.object(codec, 'executable', return_value=Path('fake')):
            result = subprocess.CompletedProcess([], 0, b'bad', b'')
            with patch.object(codec.subprocess, 'run', return_value=result):
                with self.assertRaises(ValueError): codec.encode_payload(b'data')
