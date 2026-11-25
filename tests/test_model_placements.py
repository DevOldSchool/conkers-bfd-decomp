"""Native placement fields, complete compressed records and sparse scene ownership."""
import copy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import asset_directory_build as directories, scene_field_build as scenes
from scripts import model_placement_codec as codec, model_placement_inputs as inputs
import test_scene_field_build as scene_tests


def parameter_record():
    return {codec.key(o, k): {'u8': 0xa5, 'u16': 0xabcd, 'u32': 0x12345678}[k] for o, k in codec.PARAMETERS}


class PlacementCodecTests(unittest.TestCase):
    def setUp(self):
        self.record = {'model': scene_tests.transform()['records'][0], 'parameters': parameter_record()}
        raw = bytearray(80)
        for off, data in codec.fields.encode(scene_tests.transform(), 2): raw[off:off + len(data)] = data
        for off, kind in codec.PARAMETERS:
            struct.pack_into('>' + codec.FORMATS[kind][0], raw, off, self.record['parameters'][codec.key(off, kind)])
        self.raw = bytes(raw)

    def test_independent_native_widths_and_minimum_decoded_alignment(self):
        self.assertEqual(codec.encode_props([self.record]), self.raw)
        self.assertEqual(codec.encode_props(codec.decode_props(self.raw)), self.raw)
        self.assertEqual(self.raw[40:44], b'\x80\0\0\0')
        for count in range(1, 5):
            data = codec.encode_props([self.record] * count)
            self.assertEqual(len(data), (68 * count + 15) // 16 * 16)
            self.assertEqual(codec.encode_props(codec.decode_props(data)), data)
        for at in (*codec.ZERO_OFFSETS, *range(68, 80)):
            data = bytearray(self.raw); data[at] = 1
            with self.assertRaises(ValueError): codec.decode_props(data)
        for data in (b'', self.raw[:-1], self.raw + bytes(16)):
            with self.assertRaises(ValueError): codec.decode_props(data)

    def test_strict_parameter_schema_and_single_field_mutations(self):
        record = parameter_record()
        for off, kind in codec.PARAMETERS:
            fmt, high = codec.FORMATS[kind]
            for value in (True, -1, high + 1, 1.5):
                changed = dict(record); changed[codec.key(off, kind)] = value
                with self.assertRaises(ValueError): codec.encode_parameters([changed])
            changed = dict(record); changed[codec.key(off, kind)] += 1
            before = dict(codec.encode_parameters([record])); after = dict(codec.encode_parameters([changed]))
            self.assertEqual({at for at in before if before[at] != after[at]}, {off})
        for bad in ({**record, 'raw': '00'}, {}, True):
            with self.assertRaises(ValueError): codec.encode_parameters([bad])
        with self.assertRaises(ValueError): codec.encode_props([{'model': self.record['model'], 'raw': '00'}])
        with self.assertRaises(ValueError): codec.encode_parameters([record] * 256)


class PropPlacementBuildTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(); self.addCleanup(temp.cleanup); self.root = Path(temp.name)
        self.record = {'model': scene_tests.transform()['records'][0], 'parameters': parameter_record()}
        self.compressed = inputs.compress(codec.encode_props([self.record]))
        backing = bytearray(552); self.spans = []; self.gaps = []
        for i in range(69):
            payload = self.compressed if i < 53 or i == 68 else b''
            offset = len(backing)
            struct.pack_into('>II', backing, i * 8, offset, len(payload) | ((9 if i == 68 else 1) << 28))
            backing.extend(payload)
            if payload: self.spans.append((offset, payload))
            gap = (-len(backing)) % 8
            if gap: self.gaps.append(len(backing))
            backing.extend(b'\xcc' * gap)
        self.payload = bytes(backing); self.rom = b'prefix' + self.payload
        self.expected = {'key': 'bank0B', 'part': 'asset_bank_0b', 'rom_start': 6, 'rom_end': 6 + len(backing),
                         'directory_size': 552, 'rom_ranges': [[6, 558]],
                         'directory_sha256': inputs.sha(self.payload[:552]), 'original_sha256': inputs.sha(self.payload)}
        self.index = directories.codec.decode(self.payload[:552]); self.directory = self.root / directories.input_directory('bank0B')
        self.old = directories.input_files(self.rom, self.expected, self.index)
        directories.texture_build.publish_inputs(self.directory, self.old)
        context = patch.object(directories, 'reviewed_directories', return_value=(self.rom, [(self.expected, self.index)]))
        context.start(); self.addCleanup(context.stop)

    def test_composition_old_inputs_and_regeneration(self):
        directories.build_parts(self.root)
        self.assertEqual(inputs.encoded(self.directory, self.expected, self.payload), self.spans)
        packed, _, hashes = directories.packed_directory(self.directory, self.expected, include_model_placements=True)
        self.assertEqual(packed, self.payload); self.assertIn('model-placements/placements.json', hashes)
        for name, data in self.old.items(): self.assertEqual((self.directory / name).read_bytes(), data)
        path = self.root / 'build/us/asset-directories/parts/asset_bank_0b.bin'; stamp = path.stat().st_mtime_ns
        directories.build_parts(self.root); self.assertEqual(path.stat().st_mtime_ns, stamp)
        path.unlink(); directories.build_parts(self.root); self.assertEqual(path.read_bytes(), self.payload)

    def test_edits_missing_sources_recovery_and_race(self):
        directories.build_parts(self.root); path = self.directory / inputs.DIRECTORY / 'placements.json'
        original = json.loads(path.read_text()); changed = copy.deepcopy(original)
        changed['entries'][0]['records'][0]['parameters']['u32_18'] += 1; path.write_text(json.dumps(changed))
        with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): directories.build_parts(self.root)
        self.assertEqual(json.loads(path.read_text()), changed)
        path.unlink()
        with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): directories.build_parts(self.root)
        self.assertFalse(path.exists()); path.write_text('edited')
        recovered = directories.recover_inputs('bank0B', self.root)
        self.assertEqual((Path(recovered['backup_directory']) / inputs.DIRECTORY / 'placements.json').read_text(), 'edited')
        directories.build_parts(self.root); self.assertEqual(json.loads(path.read_text()), original)
        encode = inputs.encoded
        def changing(*args):
            result = encode(*args)
            with path.open('a') as f: f.write(' ')
            return result
        with patch.object(inputs, 'encoded', side_effect=changing):
            with self.assertRaisesRegex(ValueError, 'changed during packing'): directories.build_parts(self.root)

    def test_report_requires_actual_object_including_unclaimed_gap(self):
        from test_objdiff_data_targets import object_file, targets
        directories.build_parts(self.root)
        linked = self.root / 'build/us/assets/asset_bank_0b.o'; linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        with patch.object(targets, 'ROOT', self.root):
            unit, _ = targets.prepare_model_placement_object(self.rom, self.expected, output=self.root / 'report', props=True)
            self.assertEqual(unit['report_data_bytes'], 54 * len(self.compressed))
            self.assertEqual(unit['rom_ranges'], [[6 + a, 6 + a + len(data)] for a, data in self.spans])
            for at in (0, 552, *self.gaps[:1]):
                changed = bytearray(self.payload); changed[at] ^= 1
                linked.write_bytes(object_file([('.data', 1, 3, changed)]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'):
                    targets.prepare_model_placement_object(self.rom, self.expected, output=self.root / 'report', props=True)


class SceneParameterBuildTests(unittest.TestCase):
    def setUp(self):
        scene_tests.SceneFieldBuildTests.setUp(self)

    def test_sparse_addition_preserves_old_inputs_and_report_measures(self):
        from test_objdiff_data_targets import object_file, targets
        old = scenes.input_hashes(self.directory, self.expected)
        scenes.build_parts(self.root)
        self.assertEqual(scenes.input_hashes(self.directory, self.expected), old)
        spans = inputs.encoded(self.directory, self.expected, self.payload)
        self.assertEqual(sum(len(data) for _, data in spans), 19)
        linked = self.root / 'build/us/assets/asset_bank_0c.o'; linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        with patch.object(targets, 'ROOT', self.root):
            unit, _ = targets.prepare_model_placement_object(self.rom, self.expected, output=self.root / 'report', props=False)
            self.assertEqual(unit['report_data_bytes'], 19)
            original, _ = targets.prepare_scene_field_bank(self.rom, self.expected, output=self.root / 'report')
            self.assertEqual(original['report_data_bytes'], 39)
            ranges = unit['rom_ranges'] + original['rom_ranges']
            ranges.sort(); self.assertTrue(all(a[1] <= b[0] for a, b in zip(ranges, ranges[1:])))
            changed = bytearray(self.payload); changed[self.model_offset + 28] ^= 1
            linked.write_bytes(object_file([('.data', 1, 3, changed)]))
            with self.assertRaisesRegex(ValueError, 'candidate differs'):
                targets.prepare_model_placement_object(self.rom, self.expected, output=self.root / 'report', props=False)

    def test_parameter_edits_deletion_recovery_and_race(self):
        scenes.build_parts(self.root); path = self.directory / inputs.DIRECTORY / 'placements.json'
        original = json.loads(path.read_text()); changed = copy.deepcopy(original)
        changed['entries'][0]['records'][0]['u16_40'] += 1; path.write_text(json.dumps(changed))
        with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): scenes.build_parts(self.root)
        self.assertEqual(json.loads(path.read_text()), changed)
        path.unlink()
        with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): scenes.build_parts(self.root)
        self.assertFalse(path.exists()); path.write_text('edited')
        recovered = scenes.recover_inputs(self.root)
        self.assertEqual((Path(recovered['backup_directory']) / inputs.DIRECTORY / 'placements.json').read_text(), 'edited')
        scenes.build_parts(self.root); self.assertEqual(json.loads(path.read_text()), original)
        encode = inputs.encoded
        def changing(*args):
            result = encode(*args)
            with path.open('a') as f: f.write(' ')
            return result
        with patch.object(inputs, 'encoded', side_effect=changing):
            with self.assertRaisesRegex(ValueError, 'changed during packing'): scenes.build_parts(self.root)
