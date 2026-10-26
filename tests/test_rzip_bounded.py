"""Exact compression vectors, boundary cases and independent decode rejection."""
import hashlib
from pathlib import Path
import random
import struct
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

    def test_exact_dynamic_blocks_heuristic_boundaries_and_long_history(self):
        rng = random.Random(715)
        cases = [
            (bytes(rng.randrange(16) for _ in range(70000)),
             '04f9f2d0870f6be87e48ddb2f94992b613c9dcaf15b0d478d00bc2669143448f'),
            (bytes(rng.randrange(256) for _ in range(10000)) + b'a' * 50000
             + bytes(rng.randrange(256) for _ in range(10000)),
             '8a06924f917a45f6454dbfe21881fb736f3a7bb2a1ecbd54f9469a3242d024fd'),
            ((bytes(range(251)) + b'end') * 600,
             'd139ea59f98f7175c3d9d9e2156ad9aad4cfc9750709ec0aeefa041e93f64f70'),
        ]
        for data, digest in cases:
            encoded = codec.encode_payload(data)[4:]
            self.assertEqual(hashlib.sha256(encoded).hexdigest(), digest)
            self.assertEqual(zlib.decompress(encoded, -15), data)

    def test_match_at_early_block_checkpoint(self):
        # Synthetic regression: the 4,096-token estimate must use the position
        # before consuming a match, while the emitted block includes its bytes.
        rng = random.Random(215)
        gap = rng.randrange(200, 280)
        data = bytearray(rng.randrange(256) for _ in range(600))
        while len(data) < 30000:
            data += bytes(rng.randrange(256) for _ in range(gap + rng.randrange(-3, 4)))
            source = rng.randrange(0, 300)
            data += data[source:source + 258]
        data = bytes(data)
        self.assertEqual(len(data), 30232)
        self.assertEqual(hashlib.sha256(data).hexdigest(),
                         'e6e6e7cd9960dcf5df430448886befcdd289d5901d0b1db5ebc4377713e6a303')
        encoded = codec.encode_payload(data)[4:]
        self.assertEqual(len(encoded), 14343)
        self.assertEqual(hashlib.sha256(encoded).hexdigest(),
                         'a914382a565ab3c562059709b2c27f9bdf14d1e94ad93b4ff7e1b89785d45b75')
        self.assertEqual(zlib.decompress(encoded, -15), data)

    def test_window_and_block_boundaries_with_varied_inputs(self):
        rng = random.Random(715)
        for size in (4095, 4096, 16382, 16383, 16384, 32506, 32768, 65273, 65274, 65536):
            for alphabet in (2, 256):
                data = bytes(rng.randrange(alphabet) for _ in range(size))
                with self.subTest(size=size, alphabet=alphabet):
                    encoded = codec.encode_payload(data)
                    self.assertEqual(zlib.decompress(encoded[4:], -15), data)

    def test_length_limited_huffman_tree_remains_complete(self):
        # A Fibonacci distribution needs more than 15 levels without limiting.
        from scripts.deflate_encoder import tree_lengths
        for limit, count in ((7, 19), (15, 30)):
            weights = [1, 1]
            while len(weights) < count:
                weights.append(sum(weights[-2:]))
            widths = tree_lengths(weights, limit)
            self.assertEqual(len(widths), count)
            self.assertTrue(all(0 < width <= limit for width in widths))
            self.assertEqual(sum(1 << (limit - width) for width in widths), 1 << limit)

    def test_dynamic_block_with_limited_tree_round_trips(self):
        from scripts.deflate_encoder import Bits, emit_block
        frequencies = [1, 1]
        while len(frequencies) < 20:
            frequencies.append(sum(frequencies[-2:]))
        data = bytes(symbol for symbol, count in enumerate(frequencies) for _ in range(count))
        writer = Bits()
        emit_block(writer, data, list(data), 0, len(data), False, True)
        writer.align()
        self.assertEqual((writer.output[0] >> 1) & 3, 2)
        self.assertEqual(zlib.decompress(bytes(writer.output), -15), data)


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
        for payload in (bytearray(b'data'), 'data', None):
            with self.assertRaises(ValueError): codec.encode_payload(payload)
        valid = zlib.compress(b'data', wbits=-15)
        for packed in (b'bad', valid[:-1], valid + b'trailer', zlib.compress(b'other', wbits=-15)):
            with self.subTest(packed=packed), patch.object(codec.deflate_encoder, 'encode', return_value=packed):
                with self.assertRaises(ValueError): codec.encode_payload(b'data')



class HashReuseTests(unittest.TestCase):
    def test_unchanged_tool_files_are_not_read_again_and_edits_invalidate(self):
        from scripts import build_files
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / 'source.c'; path.write_bytes(b'first')
            self.assertEqual(build_files.cached_sha256(path), hashlib.sha256(b'first').hexdigest())
            with patch.object(Path, 'read_bytes', side_effect=AssertionError('redundant read')):
                self.assertEqual(build_files.cached_sha256(path), hashlib.sha256(b'first').hexdigest())
            # A different size: Linux file timestamps are tick-coarse, so a
            # same-size rewrite can keep the whole file signature.
            path.write_bytes(b'edited')
            self.assertEqual(build_files.cached_sha256(path), hashlib.sha256(b'edited').hexdigest())
