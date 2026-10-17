"""Build receipts let the report skip re-encoding only when every field re-derives."""
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
import asset_receipts as receipts


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


class ReceiptTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        scripts = self.root / 'scripts'
        scripts.mkdir()
        (scripts / 'enc_build.py').write_text(
            'import json\ntry:\n    from scripts import enc_codec\n    from scripts.enc_tables import rows\n'
            'except ModuleNotFoundError:\n    import enc_codec\n    from enc_tables import rows\n')
        (scripts / 'enc_codec.py').write_text('import struct\nVALUE = 1\n')
        (scripts / 'enc_tables.py').write_text('rows = []\n')
        (scripts / 'unrelated.py').write_text('OTHER = 1\n')
        (self.root / 'lib').mkdir()
        (self.root / 'lib/seed.c').write_text('int seed = 1;\n')
        self.inputs = self.root / 'build/assets/enc/us/0001'
        self.inputs.mkdir(parents=True)
        (self.inputs / 'manifest.json').write_text('{}')
        (self.inputs / 'source.json').write_text('[1, 2, 3]')
        self.hashes = {name: sha256((self.inputs / name).read_bytes()) for name in ('manifest.json', 'source.json')}
        self.payload = bytes(range(32))
        self.output = self.root / 'build/us/enc/parts/part0001.bin'
        self.output.parent.mkdir(parents=True)
        self.output.write_bytes(self.payload)
        self.extent = {'rom_start': 0x100, 'rom_end': 0x120}
        self.spans = [(4, self.payload[4:12]), (20, self.payload[20:30])]
        receipts._local_imports.cache_clear()
        receipts._encoder_modules.cache_clear()
        receipts._file_sha256.cache_clear()
        self.addCleanup(receipts._local_imports.cache_clear)
        self.addCleanup(receipts._encoder_modules.cache_clear)
        self.addCleanup(receipts._file_sha256.cache_clear)

    def write(self, **overrides):
        part = receipts.part_record(output='build/us/enc/parts/part0001.bin', payload=self.payload,
                                    source_inputs=self.hashes, input_directory='build/assets/enc/us/0001',
                                    extent=self.extent, spans=self.spans)
        part.update(overrides)
        return receipts.write(self.root, 'enc', self.root / 'scripts/enc_build.py', {'part0001': part},
                              extra=('lib/seed.c',))

    def load(self):
        receipts._file_sha256.cache_clear()
        receipts._local_imports.cache_clear()
        receipts._encoder_modules.cache_clear()
        return receipts.load(self.root, 'enc', 'scripts/enc_build.py', extra=('lib/seed.c',))

    def test_fingerprint_covers_transitive_local_imports_and_extra_files_only(self):
        self.assertEqual(receipts.encoder_modules(self.root, 'scripts/enc_build.py'),
                         ['scripts/enc_build.py', 'scripts/enc_codec.py', 'scripts/enc_tables.py'])
        before = receipts.encoder_fingerprint(self.root, 'scripts/enc_build.py', ('lib/seed.c',))
        self.assertEqual(before, receipts.encoder_fingerprint(self.root, 'scripts/enc_build.py', ('lib/seed.c',)))
        (self.root / 'scripts/unrelated.py').write_text('OTHER = 2\n')
        receipts._file_sha256.cache_clear()
        self.assertEqual(before, receipts.encoder_fingerprint(self.root, 'scripts/enc_build.py', ('lib/seed.c',)))
        for path, text in (('scripts/enc_codec.py', 'VALUE = 2\n'), ('lib/seed.c', 'int seed = 2;\n'),
                           ('scripts/enc_build.py', '# changed\nimport enc_codec\n')):
            (self.root / path).write_text(text)
            receipts._file_sha256.cache_clear()
            receipts._local_imports.cache_clear()
            receipts._encoder_modules.cache_clear()
            after = receipts.encoder_fingerprint(self.root, 'scripts/enc_build.py', ('lib/seed.c',))
            self.assertNotEqual(before, after, path)
            before = after
        self.assertNotEqual(before, receipts.encoder_fingerprint(self.root, 'scripts/enc_build.py'))

    def test_receipts_round_trip_and_are_ignored_when_encoder_schema_or_family_differ(self):
        path = self.write()
        self.assertEqual(path, self.root / 'build/us/asset-receipts/enc.json')
        loaded = self.load()
        self.assertEqual(set(loaded.parts), {'part0001'})
        self.assertEqual(loaded.parts['part0001']['output_sha256'], sha256(self.payload))
        self.assertEqual(loaded.parts['part0001']['spans'], [[4, 8], [20, 10]])
        self.assertEqual(loaded.header['encoder_module'], 'scripts/enc_build.py')
        self.assertEqual(loaded.header['encoder_extra'], ['lib/seed.c'])
        document = json.loads(path.read_text())
        for key, value in (('schema', 99), ('family', 'other'), ('encoder_module', 'scripts/enc_codec.py'),
                           ('encoder_sha256', 'x' * 64), ('encoder_extra', []), ('parts', [])):
            changed = dict(document, **{key: value})
            path.write_text(json.dumps(changed))
            with self.subTest(key=key):
                self.assertEqual(self.load().parts, {})
        path.write_text('{')
        self.assertEqual(self.load().parts, {})
        path.unlink()
        self.assertEqual(self.load().parts, {})
        self.write()
        (self.root / 'scripts/enc_tables.py').write_text('rows = [1]\n')
        self.assertEqual(self.load().parts, {}, 'a changed import invalidates the family')
        self.assertEqual(receipts.load(self.root, 'enc', 'scripts/enc_build.py').parts, {},
                         'extra inputs must be declared identically')

    def test_merge_keeps_other_parts_of_the_same_encoder_only(self):
        self.write()
        other = receipts.part_record(output='build/us/enc/parts/part0002.bin', payload=b'two',
                                     source_inputs={'manifest.json': 'h'}, input_directory='x',
                                     extent={'rom_start': 0x200, 'rom_end': 0x203})
        receipts.write(self.root, 'enc', self.root / 'scripts/enc_build.py', {'part0002': other},
                       extra=('lib/seed.c',), merge=True)
        self.assertEqual(set(self.load().parts), {'part0001', 'part0002'})
        (self.root / 'scripts/enc_codec.py').write_text('VALUE = 3\n')
        receipts._file_sha256.cache_clear()
        receipts.write(self.root, 'enc', self.root / 'scripts/enc_build.py', {'part0002': other},
                       extra=('lib/seed.c',), merge=True)
        self.assertEqual(set(self.load().parts), {'part0002'}, 'stale parts of an old encoder are dropped')

    def test_reuse_requires_matching_inputs_extent_and_output_bytes(self):
        self.write()
        loaded = self.load()
        reused = receipts.reusable(self.root, loaded, 'part0001', hashes=self.hashes, extent=self.extent)
        self.assertEqual(reused.packed, self.payload)
        self.assertIsNone(reused.spans)
        self.assertEqual(reused.provenance['candidate_source'], 'reused_receipt')
        receipt = reused.provenance['receipt']
        self.assertEqual(receipt['source_inputs'],
                         {f'build/assets/enc/us/0001/{name}': digest for name, digest in self.hashes.items()})
        outside = {**self.hashes, '../../../raw/0001.mp3': 'raw'}
        self.write(source_inputs=outside)
        reused = receipts.reusable(self.root, self.load(), 'part0001', hashes=outside, extent=self.extent)
        self.assertEqual(reused.provenance['receipt']['source_inputs']['build/assets/raw/0001.mp3'], 'raw')
        self.write()
        loaded = self.load()
        self.assertEqual(receipt['output_sha256'], sha256(self.payload))
        self.assertEqual(receipt['encoder_sha256'], loaded.encoder_sha256)
        ranged = receipts.reusable(self.root, loaded, 'part0001', hashes=self.hashes, extent=self.extent, ranged=True)
        self.assertEqual(ranged.spans, self.spans)
        self.assertIsNone(receipts.reusable(self.root, loaded, 'part0001', hashes=self.hashes,
                                            extent=self.extent, fresh=True), 'fresh mode never reuses')
        self.assertIsNone(receipts.reusable(self.root, loaded, 'part0002', hashes=self.hashes, extent=self.extent))
        self.assertIsNone(receipts.reusable(self.root, loaded, 'part0001', hashes={**self.hashes, 'source.json': 'edited'},
                                            extent=self.extent))
        self.assertIsNone(receipts.reusable(self.root, loaded, 'part0001', hashes=self.hashes,
                                            extent={'rom_start': 0x100, 'rom_end': 0x124}))
        self.assertIsNone(receipts.reusable(self.root, loaded, 'part0001', hashes=self.hashes,
                                            extent={**self.extent, 'rom_ranges': [[0x104, 0x10C]]}))
        self.output.write_bytes(self.payload[:-1] + b'X')
        self.assertIsNone(receipts.reusable(self.root, loaded, 'part0001', hashes=self.hashes, extent=self.extent))
        self.output.unlink()
        self.assertIsNone(receipts.reusable(self.root, loaded, 'part0001', hashes=self.hashes, extent=self.extent))
        self.output.write_bytes(self.payload)
        self.write(spans=[[4, 40]])
        self.assertIsNone(receipts.reusable(self.root, self.load(), 'part0001', hashes=self.hashes,
                                            extent=self.extent, ranged=True), 'spans must lie inside the output')
        self.assertIsNotNone(receipts.reusable(self.root, self.load(), 'part0001', hashes=self.hashes,
                                               extent=self.extent))

    def test_candidate_falls_back_to_a_fresh_encode(self):
        calls = []
        def encode():
            calls.append(1)
            return b'fresh', {'manifest.json': 'h'}
        empty = receipts.empty('enc')
        packed, hashes, provenance = receipts.candidate(self.root, empty, 'part0001', hashes=self.hashes,
                                                        extent=self.extent, encode=encode)
        self.assertEqual((packed, hashes, provenance), (b'fresh', {'manifest.json': 'h'}, {'candidate_source': 'fresh_encode'}))
        self.assertEqual(len(calls), 1)
        self.write()
        packed, hashes, provenance = receipts.candidate(self.root, self.load(), 'part0001', hashes=self.hashes,
                                                        extent=self.extent, encode=encode)
        self.assertEqual(len(calls), 1, 'a valid receipt skips the encoder')
        self.assertEqual((packed, hashes, provenance['candidate_source']), (self.payload, self.hashes, 'reused_receipt'))
        packed, spans, hashes, provenance = receipts.candidate(
            self.root, self.load(), 'part0001', hashes=self.hashes, extent=self.extent, encode=encode, ranged=True)
        self.assertEqual(spans, self.spans)
        packed, hashes, provenance = receipts.candidate(self.root, self.load(), 'part0001', hashes=self.hashes,
                                                        extent=self.extent, encode=encode, fresh=True)
        self.assertEqual((len(calls), provenance), (2, {'candidate_source': 'fresh_encode'}))

    def test_verify_reused_rederives_encoder_inputs_and_output_from_the_checkout(self):
        self.write()
        reused = receipts.reusable(self.root, self.load(), 'part0001', hashes=self.hashes, extent=self.extent)
        unit = {'key': 'enc-0001', 'payload_sha256': sha256(self.payload),
                'source_inputs': reused.provenance['receipt']['source_inputs'], **reused.provenance}
        receipts.verify_reused(self.root, unit)
        receipts.verify_reused(self.root, {'key': 'fresh', 'candidate_source': 'fresh_encode'})
        with self.assertRaisesRegex(ValueError, 'lacks its receipt'):
            receipts.verify_reused(self.root, {'key': 'x', 'candidate_source': 'reused_receipt'})
        with self.assertRaisesRegex(ValueError, 'compared candidate'):
            receipts.verify_reused(self.root, {**unit, 'payload_sha256': sha256(b'other')})
        (self.inputs / 'source.json').write_text('[1, 2, 3, 4]')
        with self.assertRaisesRegex(ValueError, 'receipt input changed'):
            receipts.verify_reused(self.root, unit)
        (self.inputs / 'source.json').write_text('[1, 2, 3]')
        receipts.verify_reused(self.root, unit)
        self.output.write_bytes(b'tampered')
        with self.assertRaisesRegex(ValueError, 'differs from the built file'):
            receipts.verify_reused(self.root, unit)
        self.output.write_bytes(self.payload)
        (self.root / 'scripts/enc_codec.py').write_text('VALUE = 9\n')
        receipts._file_sha256.cache_clear()
        with self.assertRaisesRegex(ValueError, 'encoder differs'):
            receipts.verify_reused(self.root, unit)

    def test_receipt_families_cannot_escape_their_directory(self):
        for family in ('', '../x', '/abs', 'a/../../b'):
            with self.subTest(family=family), self.assertRaisesRegex(ValueError, 'invalid asset receipt family'):
                receipts.receipt_path(self.root, family)
        self.assertEqual(receipts.receipt_path(self.root, 'models/bank01'),
                         self.root / 'build/us/asset-receipts/models/bank01.json')


if __name__ == '__main__':
    unittest.main()
