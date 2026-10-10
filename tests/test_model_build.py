from __future__ import annotations

import copy
import hashlib
import json
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import model_build as build
import objdiff_data_targets as targets
from test_objdiff_data_targets import object_file


class ModelBuildTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.records = {'header_words': [88, 24, 0, 0, 0, 0, 0, 0, 0, 0x80000000],
                        'vertices': [[-1, 2, 3, 0, -32, 64, 10, 20, 30, 255],
                                     [5, 0, 0, 0, 0, 0, 0, 0, 0, 255],
                                     [0, 5, 0, 0, 0, 0, 0, 0, 0, 255]],
                        'display_commands': [[0x01003006, 0x01000000], [0x05000204, 0], [0xDF000000, 0]]}
        self.payload = build.encode_records(self.records)
        self.packed = build.rzip_pack.encode_rzip_chunk(self.payload)
        self.rom = b'prefix' + self.packed + b'tail'
        self.expected = {'schema_version': 1, 'profile': 'us', 'bank': 3, 'entry': 3,
                         'rom_sha1': hashlib.sha1(self.rom).hexdigest(),
                         'rom_start': 6, 'rom_end': 6 + len(self.packed),
                         'decoded_size': len(self.payload),
                         'original_decoded_sha256': build.sha256(self.payload),
                         'original_stored_sha256': build.sha256(self.packed),
                         'encoder': build.texture_build.ENCODERS['zlib']}
        self.inputs = self.root / build.INPUT_DIRECTORY / '0003'
        self.initialize()

    def initialize(self):
        build.texture_build.publish_inputs(self.inputs, {
            'manifest.json': json.dumps(self.expected).encode(),
            'model.json': json.dumps(self.records).encode()})

    def test_reconstructs_native_fields_and_fresh_compressed_storage(self):
        self.assertEqual(build.model_records(self.payload), self.records)
        with patch.object(build.rzip_pack, 'encode_rzip_chunk', wraps=build.rzip_pack.encode_rzip_chunk) as encode:
            packed, hashes = build.packed_model(self.inputs, self.expected)
        self.assertEqual(packed, self.packed)
        encode.assert_called_once_with(self.payload)
        self.assertEqual(set(hashes), {'manifest.json', 'model.json'})

    def test_auxiliary_regions_and_trailing_bytes_are_not_admitted(self):
        with self.assertRaisesRegex(ValueError, 'auxiliary|trailing'):
            build.model_records(self.payload + bytes(8))
        altered = dict(self.records, header_words=[88, 24, 112, 8, 0, 0, 0, 0, 0, 0x80000000])
        data = struct.pack('>10I', *altered['header_words']) + self.payload[40:] + bytes(8)
        with self.assertRaisesRegex(ValueError, 'auxiliary|trailing'):
            build.model_records(data)

    def test_record_boundary_range_and_schema_changes_are_rejected(self):
        for field, value in [('header_words', [56, 16, 0, 0, 0, 0, 0, 0, 0, 0]),
                             ('vertices', [[32768, 0, 0, 0, 0, 0, 0, 0, 0, 0]]),
                             ('display_commands', [[0, 0]])]:
            with self.subTest(field=field), self.assertRaises(ValueError):
                build.encode_records(dict(self.records, **{field: value}))
        with self.assertRaises(ValueError):
            build.encode_records(dict(self.records, opaque='1234'))

    def test_changed_inputs_fail_without_replacing_linker_parts(self):
        selected = [(self.expected, self.records)]
        with patch.object(build, 'reviewed_models', return_value=(self.rom, selected)):
            build.build_parts(self.root)
            output = self.root / 'build/us/models/parts/models/bank03/0003.bin'
            before = output.read_bytes(), output.stat().st_mtime_ns
            altered = copy.deepcopy(self.records)
            altered['vertices'][0][0] += 1
            (self.inputs / 'model.json').write_text(json.dumps(altered))
            with self.assertRaisesRegex(ValueError, 'original payload'):
                build.build_parts(self.root)
            self.assertEqual((output.read_bytes(), output.stat().st_mtime_ns), before)
            self.assertEqual(json.loads((self.inputs / 'model.json').read_text()), altered)

    def test_missing_input_and_changed_manifest_are_preserved(self):
        (self.inputs / 'model.json').unlink()
        with self.assertRaises(FileNotFoundError):
            build.packed_model(self.inputs, self.expected)
        self.assertFalse((self.inputs / 'model.json').exists())
        (self.inputs / 'manifest.json').write_text('{}')
        with self.assertRaisesRegex(ValueError, 'manifest'):
            build.packed_model(self.inputs, self.expected)

    def test_encoder_drift_is_not_accepted_or_retried(self):
        with patch.object(build.rzip_pack, 'encode_rzip_chunk', return_value=bytes(len(self.packed))) as encode:
            with self.assertRaisesRegex(ValueError, 'encoder differs'):
                build.packed_model(self.inputs, self.expected)
        encode.assert_called_once()

    def test_input_race_is_rejected(self):
        real = build.rzip_pack.encode_rzip_chunk
        def encode(payload):
            path = self.inputs / 'model.json'
            path.write_text(path.read_text() + '\n')
            return real(payload)
        with patch.object(build.rzip_pack, 'encode_rzip_chunk', side_effect=encode):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_model(self.inputs, self.expected)

    def test_no_change_preserves_output_timestamp(self):
        with patch.object(build, 'reviewed_models', return_value=(self.rom, [(self.expected, self.records)])):
            result = build.build_parts(self.root)
            path = self.root / 'build/us/models/parts/models/bank03/0003.bin'
            stamp = path.stat().st_mtime_ns
            build.build_parts(self.root)
        self.assertEqual(stamp, path.stat().st_mtime_ns)
        self.assertEqual(result['model_count'], 1)
        self.assertTrue(result['matches_original'])

    def test_partition_preserves_index_gaps_and_unselected_storage(self):
        bank = build.rzip_archive.AssetBank(3, 0, 100, 0)
        entries = [build.rzip_archive.AssetEntry(3, 20, 30, 0x10, True),
                   build.rzip_archive.AssetEntry(8, 60, 80, 0x10, True)]
        self.assertEqual(build.partition(bank, entries), [(0, 'models/raw/00000000'),
            (20, 'models/bank03/0003'), (30, 'models/raw/0000001E'),
            (60, 'models/bank03/0008'), (80, 'models/raw/00000050')])
        with self.assertRaises(ValueError):
            build.partition(bank, entries + entries)

    def test_report_uses_actual_linker_object_and_independent_rom_target(self):
        linked = self.root / 'build/us/assets/models/bank03/0003.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.packed)]))
        output = self.root / 'report'
        def link(args, *, cwd, check):
            self.assertEqual((cwd / args[-1]).read_bytes(), self.packed)
            (cwd / 'target.o').write_bytes(object_file([('.data', 1, 3, self.packed)]))
        with patch.object(targets, 'ROOT', self.root), patch.object(targets.subprocess, 'run', side_effect=link):
            unit, item = targets.prepare_model(self.rom, self.expected, output=output)
            self.assertTrue(unit['complete'])
            self.assertEqual(unit['size'], len(self.packed))
            self.assertEqual(item['metadata']['progress_categories'], ['data'])
            self.assertEqual(len(unit['source_inputs']), 2)
            linked.write_bytes(object_file([('.data', 1, 3, bytes(len(self.packed)))]))
            with self.assertRaisesRegex(ValueError, 'current editable inputs'):
                targets.prepare_model(self.rom, self.expected, output=output)
