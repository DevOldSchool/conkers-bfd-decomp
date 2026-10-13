"""Native visibility codebooks, source provenance and bounded report credit."""
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch
from scripts import visibility_codec as codec, visibility_build as build


def sample():
    return {'format': codec.FORMAT, 'codes': ['0', '10', '110', '111'] + [None] * 252}


def native_tree(data):
    # Independent forward model of native insertion: MSB first, six-byte nodes.
    allocation = int.from_bytes(data[:4], 'big')
    nodes = [[-1, 0, 0]]
    for symbol in range(256):
        code, length = struct.unpack_from('>II', data, 4 + symbol * 8)
        if not length: continue
        node = 0
        for bit in range(length - 1, -1, -1):
            branch = 1 + ((code >> bit) & 1)
            if not nodes[node][branch]:
                nodes[node][branch] = len(nodes) * 6
                nodes.append([-1, 0, 0])
            node = nodes[node][branch] // 6
        nodes[node][0] = symbol
    if len(nodes) * 6 != allocation:
        raise ValueError('native allocation does not equal generated nodes')
    return nodes


class VisibilityCodecTests(unittest.TestCase):
    def test_roundtrip_and_native_tree_walk(self):
        record = sample(); data = codec.encode_codebook(record)
        self.assertEqual(codec.decode_codebook(data), record)
        tree = native_tree(data)
        self.assertEqual(len(tree), 7)
        for symbol, bits in enumerate(record['codes']):
            if bits is None: continue
            node = 0
            for bit in bits: node = tree[node][1 + int(bit)] // 6
            self.assertEqual(tree[node], [symbol, 0, 0])

    def test_reassigning_symbols_changes_storage_and_native_decoding(self):
        record = sample(); before = codec.encode_codebook(record)
        record['codes'][0], record['codes'][1] = record['codes'][1], record['codes'][0]
        after = codec.encode_codebook(record)
        self.assertNotEqual(before, after)
        tree = native_tree(after)
        self.assertEqual(tree[tree[0][1] // 6][0], 1)
        self.assertEqual(before[:4], after[:4])

    def test_bad_source_and_encoded_contracts_fail(self):
        for codes in [[], [None] * 256, ['0', '0'], ['0', '01'], ['2'], [''], ['1' * 33], [True]]:
            bad = {'format': codec.FORMAT, 'codes': codes + [None] * (256 - len(codes)) if codes else codes}
            with self.assertRaises(ValueError): codec.encode_codebook(bad)
        for record in [None, {}, dict(sample(), extra=0)]:
            with self.assertRaises(ValueError): codec.encode_codebook(record)
        original = codec.encode_codebook(sample())
        for at, value in [(0, 0), (4, 2), (8, 33), (36, 1), (2052, 1)]:
            bad = bytearray(original); struct.pack_into('>I', bad, at, value)
            with self.assertRaises(ValueError): codec.decode_codebook(bytes(bad))
        with self.assertRaises(ValueError): codec.decode_codebook(original[:-1])


class VisibilityBuildTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(); self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.record = sample()
        self.data = codec.encode_codebook(self.record)
        self.stored = build.encode_payload(self.data, 6)
        self.payload = b'indexgap' + self.stored + b'raw-uncredited'
        self.rom = b'prefix' + self.payload + b'tail'
        end = 14 + len(self.stored)
        self.expected = {'rom_start': 6, 'rom_end': 6 + len(self.payload), 'original_sha256': build.sha256(self.payload),
            'rom_ranges': [[14, end]], 'entries': [{'entry': 5,
            'decoded_sha256': build.sha256(self.data), 'encoder': 6, 'rom_start': 14, 'rom_end': end}]}
        self.decoded = {'5': self.record}
        self.directory = self.root / build.INPUT_DIRECTORY
        build.texture_build.publish_inputs(self.directory, build.input_files(self.rom, self.expected, self.decoded))

    def test_build_preserves_sources_and_mtime_and_repairs_missing_part(self):
        with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.decoded)):
            proof = build.build_parts(self.root)
            part = self.root / 'build/us/visibility/parts/asset_bank_05.bin'
            before = part.stat().st_mtime_ns
            self.assertEqual(build.build_parts(self.root), proof)
            self.assertEqual(part.stat().st_mtime_ns, before)
            self.assertEqual(proof['rebuilt_bytes'], len(self.stored))
            part.unlink(); build.build_parts(self.root)
            self.assertEqual(part.read_bytes(), self.payload)

    def test_bad_or_missing_codebooks_manifest_and_backing_are_preserved(self):
        original = build.input_files(self.rom, self.expected, self.decoded)
        for name, data in [('codebooks.json', b'bad'), ('codebooks.json', None), ('manifest.json', b'{}'), ('backing.bin', b'bad')]:
            for filename, content in original.items(): (self.directory / filename).write_bytes(content)
            path = self.directory / name
            if data is None: path.unlink()
            else: path.write_bytes(data)
            before = {p.name: p.read_bytes() for p in self.directory.iterdir()}
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                build.packed_bank(self.directory, self.expected)
            self.assertEqual({p.name: p.read_bytes() for p in self.directory.iterdir()}, before)
        with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.decoded)):
            result = build.recover_inputs(self.root)
        self.assertEqual((Path(result['backup_directory']) / 'backing.bin').read_bytes(), b'bad')
        self.assertEqual(build.packed_bank(self.directory, self.expected)[0], self.payload)

    def test_source_race_fails_after_encoding(self):
        encode = codec.encode_codebook
        def changing(*args):
            value = encode(*args)
            with (self.directory / 'manifest.json').open('a') as file: file.write(' ')
            return value
        with patch.object(codec, 'encode_codebook', side_effect=changing):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_bank(self.directory, self.expected)

    def test_report_credits_only_codebook_ranges_and_rejects_stale_actual_object(self):
        from test_objdiff_data_targets import object_file, targets
        linked = self.root / 'build/us/assets/asset_bank_05.o'; linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        with patch.object(targets, 'ROOT', self.root):
            unit, item = targets.prepare_visibility_bank(self.rom, self.expected, output=self.root / 'report')
            self.assertEqual(unit['report_data_bytes'], len(self.stored))
            self.assertEqual(unit['rom_ranges'], self.expected['rom_ranges'])
            self.assertEqual(item['name'], 'assets/visibility/bank05')
            candidate = targets.sections((self.root / 'report/visibility-bank/base.o').read_bytes(), 1)['.data'][1]
            self.assertEqual(candidate, self.stored)
            linked.write_bytes(object_file([('.data', 1, 3, bytes(len(self.payload)))]))
            with self.assertRaisesRegex(ValueError, 'candidate differs'):
                targets.prepare_visibility_bank(self.rom, self.expected, output=self.root / 'report')
