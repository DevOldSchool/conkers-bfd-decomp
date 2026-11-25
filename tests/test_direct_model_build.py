"""Direct auxiliary models, bounded raw-object ownership and preserved inputs."""
from copy import deepcopy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import direct_model_build as build
from scripts import asset_directory_codec as index
from test_model_extended_build import normal_surface_payload
from test_model_short_normals import short_payload
import binary_object
import objdiff_data_targets as report


class DirectModelBuildTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(); self.addCleanup(temp.cleanup)
        self.root = Path(temp.name); self.part = build.PARTS[0]
        decoded = normal_surface_payload(primary=False)
        self.record = build.codec.extended_records(decoded, primary=False)
        self.stored = build.rzip_bounded.encode_payload(decoded)
        after = 16 + len(self.stored); pad = bytes((-after) % 8)
        unknown = b'unknown!raw'
        end = after + len(pad) + len(unknown); tail = bytes((-end) % 8)
        self.index = {'format': index.FORMAT, 'entries': [
            {'relative_offset': 16, 'stored_size': len(self.stored), 'flags': 1},
            {'relative_offset': after + len(pad), 'stored_size': len(unknown), 'flags': 9}]}
        table = index.encode(self.index)
        self.payload = self.stored + pad + unknown + tail
        self.rom = table + self.payload
        self.parent = {'key': 'bank03', 'rom_start': 0, 'rom_end': 16,
                       'original_sha256': build.sha(table), 'directory_sha256': build.sha(table)}
        self.parent_directory = self.root / build.directories.input_directory('bank03')
        self.parent_directory.mkdir(parents=True)
        (self.parent_directory / 'manifest.json').write_text(json.dumps(self.parent))
        (self.parent_directory / 'directory.json').write_text(json.dumps(self.index))
        (self.parent_directory / 'backing.bin').write_bytes(table)
        alignment = [[a, b] for a, b in build.bank_index_inputs.alignment_spans(self.index, 0, len(self.rom))]
        self.expected = {'part': self.part, 'rom_start': 16, 'rom_end': len(self.rom),
                         'original_sha256': build.sha(self.payload), 'parent': self.parent,
                         'bank_end': len(self.rom), 'alignment_ranges': alignment,
                         'entries': [{'entry': 44, 'rom_start': 16, 'rom_end': after,
                                      'decoded_sha256': build.sha(decoded), 'stored_sha256': build.sha(self.stored)}],
                         'rom_ranges': sorted([[16, after], *alignment])}
        self.records = {'44': self.record}
        self.directory = self.root / build.input_directory(self.part)
        build.texture_build.publish_inputs(self.directory, build.input_files(self.rom, self.expected, self.records))
        self.review = patch.object(build, 'reviewed_objects', return_value=(self.rom, [(self.expected, self.records)]))
        self.review.start(); self.addCleanup(self.review.stop)

    def test_rebuild_owns_models_and_minimum_alignment_but_preserves_unknown_payload(self):
        before = build.input_hashes(self.root, self.expected)
        packed, spans, hashes = build.packed_object(self.root, self.expected)
        self.assertEqual(packed, self.payload); self.assertEqual(hashes, before)
        self.assertEqual(sum(len(b) for _, b in spans), len(packed) - 11)
        self.assertTrue(any('asset-directories/us/bank03/directory.json' == p for p in hashes))
        unknown_at = self.index['entries'][1]['relative_offset'] - 16
        self.assertFalse(any(a <= unknown_at < a + len(b) for a, b in spans))
        proof = build.build_parts(self.root)
        part = self.root / 'build/us/direct-models/parts' / (build.part_name(self.part) + '.bin')
        stamp = part.stat().st_mtime_ns
        self.assertEqual(build.build_parts(self.root), proof)
        self.assertEqual(part.stat().st_mtime_ns, stamp)
        part.unlink(); build.build_parts(self.root)
        self.assertEqual(part.read_bytes(), self.payload)
        self.assertEqual(build.input_hashes(self.root, self.expected), before)

    def test_each_missing_or_changed_input_is_preserved_and_recovery_backs_up(self):
        build.build_parts(self.root)
        part = self.root / 'build/us/direct-models/parts' / (build.part_name(self.part) + '.bin')
        for directory, names in ((self.directory, ('manifest.json', 'models.json', 'backing.bin')),
                                 (self.parent_directory, ('manifest.json', 'directory.json', 'backing.bin'))):
            for name in names:
                path = directory / name; old = path.read_bytes()
                for content in (b'{}', b'invalid', None):
                    if content is None: path.unlink()
                    else: path.write_bytes(content)
                    with self.assertRaises(ValueError): build.build_parts(self.root)
                    self.assertEqual(path.read_bytes() if path.exists() else None, content)
                    self.assertEqual(part.read_bytes(), self.payload)
                    path.write_bytes(old)
        path = self.directory / 'models.json'; path.write_text('changed')
        result = build.recover_inputs(self.part, self.root)
        self.assertEqual((Path(result['backup_directory']) / 'models.json').read_text(), 'changed')
        self.assertEqual(build.packed_object(self.root, self.expected)[0], self.payload)

    def test_native_fields_roles_and_unknown_schemas_are_not_silently_accepted(self):
        mutations = (lambda r: r['44'].update(primary=True),
                     lambda r: r['44'].update(opaque='raw'),
                     lambda r: r['44']['normal_xy_s8'][0][0].__setitem__(0, 42),
                     lambda r: r['44']['face_words'].__setitem__(0, 9),
                     lambda r: r.update({'66': r['44']}), lambda r: r.pop('44'))
        for mutate in mutations:
            source = deepcopy(self.records); mutate(source)
            path = self.directory / 'models.json'; path.write_text(json.dumps(source))
            with self.assertRaises(ValueError): build.packed_object(self.root, self.expected)
            self.assertEqual(json.loads(path.read_text()), source)
        for bad in (None, {}, dict(self.record, color_descriptors=[{}])):
            with self.assertRaises(ValueError): build.encode_record(bad)

    def test_source_races_and_false_ranges_are_rejected_before_publication(self):
        old = build.encode_record
        def race(record):
            data = old(record)
            path = self.parent_directory / 'directory.json'; path.write_text(path.read_text() + '\n')
            return data
        with patch.object(build, 'encode_record', side_effect=race):
            with self.assertRaisesRegex(ValueError, 'changed during packing'): build.build_parts(self.root)
        for field in ('rom_ranges', 'alignment_ranges'):
            changed = deepcopy(self.expected); changed[field][0][0] += 1
            with patch.object(build, 'input_hashes', return_value={}):
                with self.assertRaises(ValueError): build.packed_object(self.root, changed)
        part = self.root / 'build/us/direct-models/parts' / (build.part_name(self.part) + '.bin')
        self.assertFalse(part.exists())

    def test_actual_linker_candidate_and_independent_report_reference_are_required(self):
        build.build_parts(self.root)
        linked = self.root / 'build/us/assets' / (build.part_name(self.part) + '.o')
        linked.parent.mkdir(parents=True)
        linked.write_bytes(binary_object.binary_object(self.payload, build.part_name(self.part) + '.bin'))
        with patch.object(report, 'ROOT', self.root):
            unit, _ = report.prepare_direct_model_object(self.rom, self.expected, output=self.root / 'report')
            self.assertEqual(unit['rom_ranges'], self.expected['rom_ranges'])
            self.assertEqual(unit['report_data_bytes'], len(self.payload) - 11)
            self.assertTrue(all((self.root / p).is_file() for p in unit['source_inputs']))
            for at in (0, self.index['entries'][1]['relative_offset'] - 16, len(self.payload) - 1):
                changed = bytearray(self.payload); changed[at] ^= 1
                linked.write_bytes(binary_object.binary_object(changed, build.part_name(self.part) + '.bin'))
                with self.assertRaisesRegex(ValueError, 'linked candidate'):
                    report.prepare_direct_model_object(self.rom, self.expected, output=self.root / 'report')
            linked.write_bytes(binary_object.binary_object(self.payload, build.part_name(self.part) + '.bin'))
            changed_rom = bytearray(self.rom); changed_rom[16] ^= 1
            with self.assertRaisesRegex(ValueError, 'original ROM'):
                report.prepare_direct_model_object(changed_rom, self.expected, output=self.root / 'report')

    def test_short_normal_child_preserves_parent_and_rejects_changes_and_missing_sources(self):
        decoded = short_payload(); short_stored = build.rzip_bounded.encode_payload(decoded)
        short_start = self.index['entries'][1]['relative_offset']
        short_end = short_start + len(short_stored)
        self.index['entries'][1].update(stored_size=len(short_stored), flags=1)
        table = index.encode(self.index)
        self.payload = self.payload[:short_start - 16] + short_stored + bytes((-short_end) % 8)
        self.rom = table + self.payload
        self.parent.update(original_sha256=build.sha(table), directory_sha256=build.sha(table))
        (self.parent_directory / 'manifest.json').write_text(json.dumps(self.parent))
        (self.parent_directory / 'directory.json').write_text(json.dumps(self.index))
        (self.parent_directory / 'backing.bin').write_bytes(table)
        alignment = [[a, b] for a, b in build.bank_index_inputs.alignment_spans(self.index, 0, len(self.rom))]
        self.expected.update(part=build.SHORT_PART, rom_end=len(self.rom), bank_end=len(self.rom),
                             original_sha256=build.sha(self.payload), alignment_ranges=alignment,
                             rom_ranges=sorted([[16, 16 + len(self.stored)], *alignment]))
        self.directory = self.root / build.input_directory(build.SHORT_PART)
        parent_files = build.input_files(self.rom, self.expected, self.records)
        build.texture_build.publish_inputs(self.directory, parent_files)
        with patch.object(build, 'SHORT_RANGE', (short_start, short_end)), \
                patch.object(build, 'reviewed_objects', return_value=(self.rom, [(self.expected, self.records)])):
            proof = build.build_parts(self.root)
            self.assertEqual(proof[0]['rebuilt_bytes'], len(self.payload))
            self.assertEqual(build.packed_object(self.root, self.expected)[0], self.payload)
            self.assertEqual({p: (self.directory / p).read_bytes() for p in parent_files}, parent_files)
            linked = self.root / 'build/us/assets' / (build.part_name(build.SHORT_PART) + '.o')
            linked.parent.mkdir(parents=True)
            linked.write_bytes(binary_object.binary_object(self.payload, build.part_name(build.SHORT_PART) + '.bin'))
            with patch.object(report, 'ROOT', self.root), patch.object(report, 'direct_model_build', build):
                unit, _ = report.prepare_direct_model_object(self.rom, self.expected, output=self.root / 'report')
                self.assertEqual(unit['report_data_bytes'], len(self.payload))
                self.assertEqual(unit['rom_ranges'], build.owned_ranges(self.expected))
            child = self.directory / 'short-normals'
            for name in ('manifest.json', 'model.json'):
                path = child / name; saved = path.read_bytes()
                for value in (None, b'{}', b'broken'):
                    if value is None: path.unlink()
                    else: path.write_bytes(value)
                    with self.assertRaises(ValueError): build.build_parts(self.root)
                    self.assertEqual(path.read_bytes() if path.exists() else None, value)
                    path.write_bytes(saved)
            path = child / 'model.json'; source = json.loads(path.read_text())
            source['normal_xy_s8'][0][0] ^= 1; path.write_text(json.dumps(source))
            with self.assertRaisesRegex(ValueError, 'short normal model fields'): build.build_parts(self.root)
            result = build.recover_inputs(build.SHORT_PART, self.root)
            self.assertEqual(json.loads((Path(result['backup_directory']) / 'short-normals/model.json').read_text()), source)
            self.assertEqual(build.packed_object(self.root, self.expected)[0], self.payload)
            self.assertEqual({p: (self.directory / p).read_bytes() for p in parent_files}, parent_files)
