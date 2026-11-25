from copy import deepcopy
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from scripts import duplicate_model_build as build
from scripts import asset_directory_codec as index
from test_model_duplicate_normals import duplicate_payload
import binary_object
import objdiff_data_targets as report


class DuplicateModelBuildTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(); self.addCleanup(temp.cleanup); self.root = Path(temp.name)
        decoded = duplicate_payload(); self.source = build.codec.decode(decoded)
        stored = build.rzip_bounded.encode_payload(decoded); end = 8 + len(stored)
        self.index = {'format': index.FORMAT, 'entries': [{'relative_offset': 8, 'stored_size': len(stored), 'flags': 1}]}
        table = index.encode(self.index); self.packed = stored + bytes((-end) % 8); self.rom = table + self.packed
        parent = {'key': 'bank04', 'rom_start': 0, 'rom_end': 8,
                  'original_sha256': build.sha(table), 'directory_sha256': build.sha(table)}
        gaps = build.bank_index_inputs.alignment_spans(self.index, 0, len(self.rom))
        self.expected = {'rom_start': 8, 'rom_end': len(self.rom), 'part': build.PART,
                         'original_sha256': build.sha(self.packed), 'entry_start': 8, 'entry_end': end,
                         'decoded_sha256': build.sha(decoded), 'stored_sha256': build.sha(stored),
                         'parent': parent, 'bank_end': len(self.rom), 'alignment_ranges': [[a, b] for a, b in gaps]}
        self.directory = self.root / build.DIRECTORY
        build.texture_build.publish_inputs(self.directory, build.input_files(self.expected, self.source))
        self.shared = self.root / build.directories.input_directory('bank04'); self.shared.mkdir(parents=True)
        (self.shared / 'manifest.json').write_text(json.dumps(parent))
        (self.shared / 'directory.json').write_text(json.dumps(self.index))
        (self.shared / 'backing.bin').write_bytes(table)
        self.review = patch.object(build, 'reviewed', return_value=(self.rom, self.expected, self.source))
        self.review.start(); self.addCleanup(self.review.stop)

    def test_exact_full_object_noop_and_deleted_output_are_reproducible(self):
        hashes = build.input_hashes(self.root, self.expected)
        self.assertEqual(build.packed_part(self.root, self.expected), (self.packed, hashes))
        proof = build.build_parts(self.root)
        path = self.root / 'build/us/duplicate-models/parts' / (build.PART + '.bin'); stamp = path.stat().st_mtime_ns
        self.assertEqual(build.build_parts(self.root), proof); self.assertEqual(path.stat().st_mtime_ns, stamp)
        path.unlink(); build.build_parts(self.root); self.assertEqual(path.read_bytes(), self.packed)
        self.assertEqual(build.input_hashes(self.root, self.expected), hashes)

    def test_changed_or_missing_sources_fail_without_overwrite_and_recovery_backs_up(self):
        build.build_parts(self.root)
        output = self.root / 'build/us/duplicate-models/parts' / (build.PART + '.bin')
        for folder, names in ((self.directory, ('manifest.json', 'model.json')),
                              (self.shared, ('manifest.json', 'directory.json', 'backing.bin'))):
            for name in names:
                path = folder / name; original = path.read_bytes()
                for value in (None, b'{}', b'broken'):
                    if value is None: path.unlink()
                    else: path.write_bytes(value)
                    with self.assertRaises(ValueError): build.build_parts(self.root)
                    self.assertEqual(path.read_bytes() if path.exists() else None, value)
                    self.assertEqual(output.read_bytes(), self.packed); path.write_bytes(original)
        changed = deepcopy(self.source); changed['segments'][0]['normal_xy_s8'][0][0][0] ^= 1
        path = self.directory / 'model.json'; path.write_text(json.dumps(changed))
        with self.assertRaisesRegex(ValueError, 'fields differ'): build.build_parts(self.root)
        result = build.recover_inputs(self.root)
        self.assertEqual(json.loads((Path(result['backup_directory']) / 'model.json').read_text()), changed)
        self.assertEqual(build.packed_part(self.root, self.expected)[0], self.packed)

    def test_source_races_and_false_extents_cannot_publish(self):
        old = build.codec.encode
        def race(source):
            data = old(source); path = self.shared / 'directory.json'; path.write_text(path.read_text() + '\n'); return data
        with patch.object(build.codec, 'encode', side_effect=race):
            with self.assertRaisesRegex(ValueError, 'changed during'): build.build_parts(self.root)
        for field in ('entry_start', 'entry_end', 'rom_start', 'rom_end'):
            changed = dict(self.expected); changed[field] += 1
            with patch.object(build, 'input_hashes', return_value={}):
                with self.assertRaises(ValueError): build.packed_part(self.root, changed)
        self.assertFalse((self.root / 'build/us/duplicate-models/parts' / (build.PART + '.bin')).exists())

    def test_native_report_uses_actual_linked_object_and_independent_rom(self):
        build.build_parts(self.root)
        linked = self.root / 'build/us/assets' / (build.PART + '.o'); linked.parent.mkdir(parents=True)
        linked.write_bytes(binary_object.binary_object(self.packed, build.PART + '.bin'))
        with patch.object(report, 'ROOT', self.root), patch.object(report, 'duplicate_model_build', build):
            unit, _ = report.prepare_duplicate_model_object(self.rom, self.expected, output=self.root / 'report')
            self.assertTrue(unit['complete']); self.assertEqual(unit['report_data_bytes'], len(self.packed))
            for at in (0, len(self.packed) - 1):
                changed = bytearray(self.packed); changed[at] ^= 1
                linked.write_bytes(binary_object.binary_object(changed, build.PART + '.bin'))
                with self.assertRaisesRegex(ValueError, 'candidate differs'):
                    report.prepare_duplicate_model_object(self.rom, self.expected, output=self.root / 'report')
            linked.write_bytes(binary_object.binary_object(self.packed, build.PART + '.bin'))
            changed = bytearray(self.rom); changed[8] ^= 1
            unit, _ = report.prepare_duplicate_model_object(changed, self.expected, output=self.root / 'report')
            self.assertFalse(unit['complete']); self.assertFalse(unit['literal_payload_matches_rom'])
