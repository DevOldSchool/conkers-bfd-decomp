import copy
import hashlib
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import sequence_build as build


class SequenceBuildTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.payload = struct.pack('>17I', 68, *([0] * 15), 480) + bytes.fromhex('00c00100ff2f')
        self.records = build.sequence_codec.parse_records(self.payload)
        self.rom = b'prefix' + self.payload + b'tail'
        self.expected = {'schema_version': 1, 'profile': 'us', 'entry': 0,
                         'rom_sha1': hashlib.sha1(self.rom).hexdigest(), 'rom_start': 6,
                         'rom_end': 6 + len(self.payload), 'original_sha256': build.sha256(self.payload),
                         'encoder': 'conker-compact-sequence-v1'}
        self.inputs = self.root / build.input_directory(0)
        build.texture_build.publish_inputs(self.inputs, build.input_files(self.expected, self.records))

    def test_fresh_event_encoding_and_source_hashes(self):
        with patch.object(build.sequence_codec, 'encode_records', wraps=build.sequence_codec.encode_records) as encode:
            payload, hashes = build.packed_sequence(self.inputs, self.expected)
        self.assertEqual(payload, self.payload)
        encode.assert_called_once_with(self.records)
        self.assertEqual(set(hashes), {'manifest.json', 'sequence.json'})

    def test_changed_event_manifest_and_missing_source_fail_without_replacement(self):
        records = copy.deepcopy(self.records)
        records['tracks'][0]['events'][0]['data'][0] = 2
        for files in ({'sequence.json': json.dumps(records).encode()}, {'manifest.json': b'{}'},
                      {'sequence.json': b'{'}, {'sequence.json': None}):
            for name, content in build.input_files(self.expected, self.records).items():
                (self.inputs / name).write_bytes(content)
            for name, data in files.items():
                if data is None:
                    (self.inputs / name).unlink()
                else:
                    (self.inputs / name).write_bytes(data)
            before = {p.name: p.read_bytes() for p in self.inputs.iterdir()}
            with self.subTest(files=files), self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                build.packed_sequence(self.inputs, self.expected)
            self.assertEqual({p.name: p.read_bytes() for p in self.inputs.iterdir()}, before)

    def test_build_initializes_and_preserves_parts_and_source_mtimes(self):
        for p in self.inputs.iterdir():
            p.unlink()
        self.inputs.rmdir()
        with patch.object(build, 'reviewed_sequences', return_value=(self.rom, [(self.expected, self.records)])):
            first = build.build_parts(self.root)
            parts = self.root / 'build/us/sequences/parts' / (build.part_name(0) + '.bin')
            before = [p.stat().st_mtime_ns for p in [parts, self.inputs / 'sequence.json']]
            second = build.build_parts(self.root)
        self.assertEqual(first, second)
        self.assertEqual(first['stored_bytes'], len(self.payload))
        self.assertEqual(parts.read_bytes(), self.payload)
        self.assertEqual([p.stat().st_mtime_ns for p in [parts, self.inputs / 'sequence.json']], before)

    def test_independent_rom_mismatch_cannot_publish_candidate(self):
        with patch.object(build, 'reviewed_sequences', return_value=(b'bad reference', [(self.expected, self.records)])):
            with self.assertRaisesRegex(ValueError, 'independent'):
                build.build_parts(self.root)
        self.assertFalse((self.root / 'build/us/sequences/parts').exists())

    def test_partial_folder_is_preserved_until_explicit_recovery(self):
        (self.inputs / 'sequence.json').unlink()
        (self.inputs / 'notes.txt').write_text('keep me')
        with patch.object(build, 'reviewed_sequences', return_value=(self.rom, [(self.expected, self.records)])):
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                build.build_parts(self.root)
            result = build.recover_inputs(0, self.root)
        backup = Path(result['backup_directory'])
        self.assertEqual((backup / 'notes.txt').read_text(), 'keep me')
        self.assertFalse((backup / 'sequence.json').exists())
        self.assertEqual(build.packed_sequence(self.inputs, self.expected)[0], self.payload)

    def test_input_change_during_encoding_is_rejected(self):
        encode = build.sequence_codec.encode_records
        def changed(records):
            result = encode(records)
            with (self.inputs / 'sequence.json').open('a') as file:
                file.write(' ')
            return result
        with patch.object(build.sequence_codec, 'encode_records', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_sequence(self.inputs, self.expected)

    def test_recovery_rolls_back_backup_if_publication_fails(self):
        before = {p.name: p.read_bytes() for p in self.inputs.iterdir()}
        with patch.object(build, 'reviewed_sequences', return_value=(self.rom, [(self.expected, self.records)])), \
                patch.object(build.texture_build, 'publish_inputs', side_effect=OSError('failed publication')):
            with self.assertRaises(OSError):
                build.recover_inputs(0, self.root)
        self.assertEqual({p.name: p.read_bytes() for p in self.inputs.iterdir()}, before)

    def test_native_report_requires_actual_link_object_and_independent_target(self):
        from test_objdiff_data_targets import object_file, targets
        linked = self.root / 'build/us/assets/audio/bank17/sequences/0000.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        def link(args, *, cwd, check):
            self.assertEqual(args[-1], build.part_name(0) + '.bin')
            original = (cwd / args[-1]).read_bytes()
            self.assertEqual(original, self.payload)
            (cwd / 'target.o').write_bytes(object_file([('.data', 1, 3, original)]))
        with patch.object(targets, 'ROOT', self.root), patch.object(targets.subprocess, 'run', side_effect=link):
            unit, item = targets.prepare_sequence(self.rom, self.expected, output=self.root / 'report')
            self.assertTrue(unit['complete'])
            self.assertEqual(unit['report_data_bytes'], len(self.payload))
            self.assertEqual(item['name'], 'assets/audio/bank17/sequences/0000')
            self.assertEqual(item['metadata']['progress_categories'], ['data'])
            self.assertEqual(len(unit['source_inputs']), 2)
            self.assertEqual(set(unit['linked_inputs']), {str(linked.relative_to(self.root))})
            linked.write_bytes(object_file([('.data', 1, 3, bytes(len(self.payload)))]))
            with self.assertRaisesRegex(ValueError, 'candidate differs'):
                targets.prepare_sequence(self.rom, self.expected, output=self.root / 'report')

    def test_reviewed_sequences_pin_consumers_and_exact_yaml_payload_extents(self):
        from types import SimpleNamespace
        sequence = SimpleNamespace(index=0, offset=0, data=self.payload)
        family = SimpleNamespace(bank_start=0, bank_end=len(self.rom),
                                 assets=[None, None, None, SimpleNamespace(rom_start=6)],
                                 sequences=[sequence])
        rows = [(0, 'audio/bank17/index'), (6, build.part_name(0)),
                (self.expected['rom_end'], 'audio/bank17/sequences/padding/0000')]
        with patch.object(build, 'ROM_SHA1', self.expected['rom_sha1']), \
                patch.object(build.audio_assets, 'load_profile_audio_assets', return_value=(None, self.rom, None, family)), \
                patch.object(build.sequence_codec, 'verify_consumers') as consumers, \
                patch.object(build.audio_boundaries, 'bank_layout', return_value=(0, len(self.rom), rows)) as layout:
            rom, selected = build.reviewed_sequences(self.root)
            self.assertEqual(rom, self.rom)
            self.assertEqual(selected, [(self.expected, self.records)])
            consumers.assert_called_once_with(self.rom)
            consumers.side_effect = ValueError('consumer changed')
            with self.assertRaisesRegex(ValueError, 'consumer changed'):
                build.reviewed_sequences(self.root)
            consumers.side_effect = None
            for changed in ([*rows[:2], (self.expected['rom_end'] + 1, rows[2][1])],
                            [*rows, (len(self.rom), build.part_name(1))],
                            [*rows, (len(self.rom), build.part_name(0))]):
                layout.return_value = (0, len(self.rom), changed)
                with self.subTest(rows=changed), self.assertRaises(ValueError):
                    build.reviewed_sequences(self.root)
