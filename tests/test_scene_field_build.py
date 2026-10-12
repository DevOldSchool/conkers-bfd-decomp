"""Bounded semantic scene fields and cooperative ownership of the real bank."""
from copy import deepcopy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch
from scripts import scene_field_codec as codec, scene_field_build as build
from test_scene_volume_build import volume


def transform():
    return {'format': codec.FORMATS[2], 'records': [{'position': [-10, 20, 30],
        'rotation': [0, 90, 180], 'scale': [1.0, 2.0, -0.0],
        'model_source': {'kind': 0, 'index': 51}, 'update_handler': 40,
        'script_selector': 7, 'initial_state': 1, 'transform_flags': 0x21}]}


def source(child, record):
    return {'format': codec.FORMATS[child], 'records': [record]}


def put_fields(backing, fields):
    result = bytearray(backing)
    for at, data in fields: result[at:at + len(data)] = data
    return bytes(result)


class SceneFieldCodecTests(unittest.TestCase):
    def test_transform_fields_preserve_unknown_model_record_bytes(self):
        spans = codec.encode(transform(), 2)
        self.assertEqual(spans, [(0, struct.pack('>6h3I', -10, 20, 30, 0, 90, 180, 0, 51, 40)),
                                 (32, struct.pack('>3f', 1, 2, -0.0)), (51, b'\x07\x01'), (60, b'!')])
        original = bytes(range(68)); packed = put_fields(original, spans)
        for start, end in ((24, 32), (44, 51), (53, 60), (61, 68)):
            self.assertEqual(packed[start:end], original[start:end])
        self.assertEqual(codec.decode(packed, 2), transform())

    def test_group_member_labels_derive_native_count_and_packed_references(self):
        group = source(4, {'members': [{'kind': 2, 'index': 123}, {'kind': 3, 'index': 6}]})
        spans = codec.encode(group, 4)
        self.assertEqual(spans, [(2, b'\0\2'), (8, b'\x20\x7b\x30\x06')])
        backing = bytes(range(24)); packed = put_fields(backing, spans)
        self.assertEqual(codec.decode(packed, 4), group)
        self.assertEqual(packed[:2], backing[:2]); self.assertEqual(packed[4:8], backing[4:8])
        self.assertEqual(packed[12:], backing[12:])
        group['records'][0]['members'][1]['index'] = 7
        self.assertEqual(codec.encode(group, 4)[1][1][-2:], b'\x30\x07')

    def test_spawn_view_and_sprite_fields_have_native_widths_and_offsets(self):
        spawn = source(6, {'position': [-10, 20, 30], 'view_selector': 6, 'heading': 192,
                          'view_position': [1.25, -2.5, 3.0], 'spawn_option': 3,
                          'transition': -2, 'alternate_spawn': -1})
        fields = codec.encode(spawn, 6)
        self.assertEqual(fields, [(0, struct.pack('>3h2B3fBbb', -10, 20, 30, 6, 192, 1.25, -2.5, 3, 3, -2, -1))])
        self.assertEqual(codec.decode(fields[0][1] + b'\xA5', 6), spawn)
        pose = source(8, {'position': [10, -20, 30], 'view_parameters': [-30.5, 90.0, 0.0]})
        fields = codec.encode(pose, 8)
        self.assertEqual([at for at, _ in fields], [0, 12]); self.assertEqual([len(v) for _, v in fields], [6, 12])
        self.assertEqual(codec.decode(put_fields(bytes(range(24)), fields), 8), pose)
        sprites = source(10, {'sprite': 67, 'flags': 0x1234})
        self.assertEqual(codec.encode(sprites, 10), [(0, b'\0C\x12\x34')])
        self.assertEqual(codec.decode(b'\0C\x12\x34', 10), sprites)

    def test_invalid_schema_fields_and_unbounded_reference_lists_fail(self):
        for bad in ([], {}, None, dict(transform(), raw='00')):
            with self.assertRaises(ValueError): codec.encode(bad, 2)
        for field, value in [('position', [0, 0, 32768]), ('rotation', [0, True, 0]),
                             ('scale', [1, float('nan'), 1]), ('opaque', '00'),
                             ('model_source', {'kind': 3, 'index': 1}), ('model_source', {'kind': 0}),
                             ('model_source', {'kind': 0, 'index': -1}), ('update_handler', 1 << 32),
                             ('script_selector', True), ('initial_state', 256), ('transform_flags', -1)]:
            bad = transform(); bad['records'][0][field] = value
            with self.assertRaises(ValueError): codec.encode(bad, 2)
        for members in ([], [{'kind': 2, 'index': 0}] * 9, [{'kind': 16, 'index': 1}],
                        [{'kind': 2, 'index': 4096}], [{'kind': True, 'index': 0}]):
            with self.assertRaises(ValueError): codec.encode(source(4, {'members': members}), 4)
        for child, stride in codec.STRIDES.items():
            with self.assertRaises(ValueError): codec.decode(bytes(stride - 1), child)
        with self.assertRaises(ValueError): codec.encode(transform(), 3)

    def test_model_controls_use_native_widths_and_reject_a_legacy_schema(self):
        source = transform()
        for field, value, at, packed in (
                ('update_handler', 0x151150B0, 20, bytes.fromhex('151150B0')),
                ('script_selector', 255, 51, b'\xff'),
                ('initial_state', 0, 52, b'\0'),
                ('transform_flags', 255, 60, b'\xff')):
            changed = deepcopy(source); changed['records'][0][field] = value
            actual = put_fields(bytes(range(68)), codec.encode(changed, 2))
            self.assertEqual(actual[at:at + len(packed)], packed)
        for kind in (1, 2):
            changed = deepcopy(source); changed['records'][0]['model_source']['kind'] = kind
            actual = put_fields(bytes(range(68)), codec.encode(changed, 2))
            self.assertEqual(struct.unpack_from('>I', actual, 12)[0], kind)
        source['format'] = 'conker-scene-model-transforms-v1'
        with self.assertRaises(ValueError): codec.encode(source, 2)


class SceneFieldBuildTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(); self.addCleanup(temp.cleanup); self.root = Path(temp.name)
        self.records = {'0:2': transform()}; vol = build.volumes.codec.encode(volume(), 5)
        native = put_fields(bytes(range(68)), codec.encode(transform(), 2))
        self.payload = b'index123' + vol + b'rawgap!!' + native + b'endstuff'
        self.rom = b'prefix' + self.payload + b'suffix'
        common = {'bank': 12, 'rom_start': 6, 'rom_end': 6 + len(self.payload),
                  'original_sha256': build.sha256(self.payload)}
        self.expected = {**common, 'entries': [{'scene': 0, 'child': 2, 'key': '0:2', 'rom_start': 74,
            'rom_end': 142, 'record_count': 1, 'field_ranges': [[0, 24], [32, 44], [51, 53], [60, 61]],
            'field_sha256': build.sha256(native[:24] + native[32:44] + native[51:53] + native[60:61])}], 'rom_ranges': [[74, 98], [106, 118], [125, 127], [134, 135]]}
        self.volume_expected = {**common, 'entries': [{'scene': 0, 'child': 5, 'key': '0:5', 'rom_start': 14,
            'rom_end': 66, 'record_count': 1, 'decoded_sha256': build.sha256(vol)}], 'rom_ranges': [[14, 66]]}
        self.volume_records = {'0:5': volume()}
        self.directory = self.root / build.INPUT_DIRECTORY; self.volume_directory = self.root / build.volumes.INPUT_DIRECTORY
        build.texture_build.publish_inputs(self.directory, build.input_files(self.rom, self.expected, self.records))
        build.texture_build.publish_inputs(self.volume_directory, build.volumes.input_files(self.rom, self.volume_expected, self.volume_records))
        self.review = patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.records))
        self.review.start(); self.addCleanup(self.review.stop)
        self.volume_review = patch.object(build.volumes, 'reviewed_bank', return_value=(self.rom, self.volume_expected, self.volume_records))
        self.volume_review.start(); self.addCleanup(self.volume_review.stop)

    def test_both_families_compose_the_actual_bank_and_keep_all_source_hashes(self):
        hashes = build.input_hashes(self.directory, self.expected)
        volume_hashes = build.volumes.input_hashes(self.volume_directory, self.volume_expected)
        proof = build.build_parts(self.root); part = self.root / 'build/us/scene-fields/parts' / (build.PART + '.bin')
        self.assertEqual(part.read_bytes(), self.payload); self.assertEqual(proof['rebuilt_bytes'], 39)
        timestamp = part.stat().st_mtime_ns; build.build_parts(self.root); self.assertEqual(part.stat().st_mtime_ns, timestamp)
        part.unlink(); build.build_parts(self.root); self.assertEqual(part.read_bytes(), self.payload)
        self.assertEqual(build.input_hashes(self.directory, self.expected), hashes)
        self.assertEqual(build.volumes.input_hashes(self.volume_directory, self.volume_expected), volume_hashes)

    def test_either_family_failure_preserves_part_and_inputs_and_recovery_backs_up(self):
        build.build_parts(self.root); part = self.root / 'build/us/scene-fields/parts' / (build.PART + '.bin')
        for directory in (self.directory, self.volume_directory):
            for name, bad in [('records.json', None), ('records.json', b'null'), ('manifest.json', b'{}'), ('backing.bin', b'changed')]:
                path = directory / name; original = path.read_bytes()
                if bad is None: path.unlink()
                else: path.write_bytes(bad)
                before = {p.name: p.read_bytes() for p in directory.iterdir()}
                with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): build.build_parts(self.root)
                self.assertEqual({p.name: p.read_bytes() for p in directory.iterdir()}, before)
                self.assertEqual(part.read_bytes(), self.payload); path.write_bytes(original)
        (self.directory / 'records.json').write_bytes(b'edited')
        result = build.recover_inputs(self.root)
        self.assertEqual((Path(result['backup_directory']) / 'records.json').read_bytes(), b'edited')
        self.assertEqual(build.packed_bank(self.directory, self.expected)[0], self.payload)

    def test_range_count_and_source_races_cannot_publish_stale_credit(self):
        for field, value in [('record_count', 2), ('rom_end', 143), ('field_ranges', [[0, 13], [32, 44]])]:
            expected = deepcopy(self.expected); expected['entries'][0][field] = value
            with patch.object(build, 'input_hashes', return_value={}):
                with self.assertRaises(ValueError): build.packed_bank(self.directory, expected)
        encode = build.codec.encode
        def changing(*args):
            data = encode(*args)
            with (self.directory / 'records.json').open('a') as file: file.write(' ')
            return data
        with patch.object(build.codec, 'encode', side_effect=changing):
            with self.assertRaisesRegex(ValueError, 'changed during packing'): build.packed_bank(self.directory, self.expected)
        pack = build.volumes.packed_bank
        def change_volume(*args):
            result = pack(*args)
            with (self.volume_directory / 'records.json').open('a') as file: file.write(' ')
            return result
        with patch.object(build.volumes, 'packed_bank', side_effect=change_volume):
            with self.assertRaisesRegex(ValueError, 'changed during batch'): build.build_parts(self.root)
        self.assertFalse((self.root / 'build/us/scene-fields/parts' / (build.PART + '.bin')).exists())

    def test_report_uses_fresh_fields_and_shared_actual_bank_without_opaque_bytes(self):
        from test_objdiff_data_targets import object_file, targets
        linked = self.root / 'build/us/assets' / (build.PART + '.o'); linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)])); output = self.root / 'report'
        with patch.object(targets, 'ROOT', self.root):
            unit, item = targets.prepare_scene_field_bank(self.rom, self.expected, output=output)
            self.assertEqual(unit['size'], 39); self.assertEqual(unit['rom_ranges'], self.expected['rom_ranges'])
            self.assertEqual(item['name'], 'assets/scenes/fields')
            expected = b''.join(data for _, data in codec.encode(transform(), 2))
            self.assertEqual(targets.sections((output / unit['base_path']).read_bytes(), 1)['.data'][1], expected)
            changed = bytearray(self.payload); changed[1] ^= 1
            linked.write_bytes(object_file([('.data', 1, 3, bytes(changed))]))
            with self.assertRaisesRegex(ValueError, 'linked candidate'):
                targets.prepare_scene_field_bank(self.rom, self.expected, output=output)
