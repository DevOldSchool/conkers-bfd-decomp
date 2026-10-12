"""Scene records: native field layout, source ownership and bounded report credit."""
from copy import deepcopy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch
from scripts import scene_volume_codec as codec, scene_volume_build as build


def volume():
    return {'format': codec.VOLUME_FORMAT, 'records': [{'position': [-4, 5, -6],
        'dimensions': [100, 200, 300], 'angles': [-0.0, 90.0], 'disabled': True,
        'shape': 2, 'kind': 7, 'flags': 10, 'mode': 12, 'action_value': -42,
        'packed_parameter': 0x12345678, 'initial_state': 2}]}


def sphere():
    return {'format': codec.SPHERE_FORMAT, 'records': [{'position': [-1.25, 2.5, -0.0],
        'radius': 300.0, 'response_parameter': 3.0, 'activation_index': 7.0}]}


class SceneVolumeCodecTests(unittest.TestCase):
    def test_native_fields_and_derived_rotation_cache(self):
        raw = codec.encode(volume(), 5)
        expected = struct.pack('>6h2f4BiIi', -4, 5, -6, 100, 200, 300, -0.0, 90.0,
                               1, 7 << 2 | 2, 10, 12, -42, 0x12345678, 2) + bytes(16)
        self.assertEqual(raw, expected)
        self.assertEqual(codec.decode(raw, 5), volume())
        self.assertEqual(codec.encode(codec.decode(raw, 5), 5), expected)
        self.assertEqual(codec.encode(sphere(), 3), struct.pack('>6f', -1.25, 2.5, -0.0, 300, 3, 7))
        self.assertEqual(codec.decode(codec.encode(sphere(), 3), 3), sphere())

    def test_changed_fields_reach_native_offsets_without_touching_other_fields(self):
        original = codec.encode(volume(), 5)
        for field, value, start, end in [('position', [1, 2, 3], 0, 6), ('dimensions', [4, 5, 6], 6, 12),
                ('angles', [30.0, 40.0], 12, 20), ('disabled', False, 20, 21),
                ('kind', 25, 21, 22), ('shape', 1, 21, 22), ('flags', 3, 22, 23),
                ('mode', 1, 23, 24), ('action_value', 123, 24, 28),
                ('packed_parameter', 0xFFFF0001, 28, 32), ('initial_state', -1, 32, 36)]:
            source = volume(); source['records'][0][field] = value
            result = codec.encode(source, 5)
            self.assertNotEqual(result[start:end], original[start:end])
            self.assertEqual(result[:start], original[:start]); self.assertEqual(result[end:], original[end:])
            self.assertEqual(codec.decode(result, 5)['records'][0][field], value)

    def test_strict_widths_schema_finite_floats_and_initialized_cache(self):
        invalid = [('position', [0, 0, 32768]), ('dimensions', [0, True, 0]), ('angles', [0, float('nan')]),
                   ('angles', [0, float('inf')]), ('angles', [0, 1e100]), ('angles', [0, 10 ** 400]), ('disabled', 1), ('shape', 4),
                   ('kind', 64), ('flags', 16), ('mode', -1), ('action_value', 1 << 31),
                   ('packed_parameter', -1), ('initial_state', -(1 << 31) - 1)]
        for field, value in invalid:
            source = volume(); source['records'][0][field] = value
            with self.assertRaises(ValueError): codec.encode(source, 5)
        for source in ([], None, {}, dict(volume(), raw='00')):
            with self.assertRaises(ValueError): codec.encode(source, 5)
        for child, record in ((3, sphere()), (5, volume())):
            raw = codec.encode(record, child)
            for data in (raw[:-1], raw + b'\0'):
                with self.assertRaises(ValueError): codec.decode(data, child)
            record['records'][0]['opaque'] = '00'
            with self.assertRaises(ValueError): codec.encode(record, child)
        raw = codec.encode(volume(), 5)
        for at in (20, 36, 40, 44, 48, 51):
            changed = bytearray(raw); changed[at] = 2
            with self.assertRaises(ValueError): codec.decode(bytes(changed), 5)
        with self.assertRaises(ValueError): codec.decode(raw, 6)


class SceneVolumeBuildTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(); self.addCleanup(temp.cleanup); self.root = Path(temp.name)
        self.decoded = {'0:3': sphere(), '0:5': volume()}
        a, b = codec.encode(sphere(), 3), codec.encode(volume(), 5)
        self.payload = b'rawindex' + a + b'unknown!' + b + b'raw tail'
        self.rom = b'prefix' + self.payload + b'suffix'
        self.expected = {'bank': 12, 'rom_start': 6, 'rom_end': 6 + len(self.payload),
                         'original_sha256': build.sha256(self.payload), 'entries': [], 'rom_ranges': []}
        for child, start, data in ((3, 14, a), (5, 22 + len(a), b)):
            row = {'scene': 0, 'child': child, 'key': f'0:{child}', 'rom_start': start,
                   'rom_end': start + len(data), 'record_count': 1, 'decoded_sha256': build.sha256(data)}
            self.expected['entries'].append(row); self.expected['rom_ranges'].append([start, start + len(data)])
        self.directory = self.root / build.INPUT_DIRECTORY
        build.texture_build.publish_inputs(self.directory, build.input_files(self.rom, self.expected, self.decoded))

    def test_exact_build_preserves_sources_mtime_and_repairs_missing_part(self):
        hashes = build.input_hashes(self.directory, self.expected)
        with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.decoded)):
            proof = build.build_parts(self.root)
            part = self.root / 'build/us/scene-volumes/parts' / (build.PART + '.bin')
            self.assertEqual(part.read_bytes(), self.payload); self.assertEqual(proof['rebuilt_bytes'], 76)
            timestamp = part.stat().st_mtime_ns; build.build_parts(self.root)
            self.assertEqual(part.stat().st_mtime_ns, timestamp)
            part.unlink(); build.build_parts(self.root); self.assertEqual(part.read_bytes(), self.payload)
        self.assertEqual(build.input_hashes(self.directory, self.expected), hashes)

    def test_changed_missing_and_invalid_inputs_preserved_and_recovery_backed_up(self):
        files = build.input_files(self.rom, self.expected, self.decoded)
        for name, value in [('records.json', None), ('records.json', b'bad'), ('records.json', b'null'),
                ('records.json', b'{}'), ('backing.bin', b'changed'), ('manifest.json', b'{}')]:
            for key, content in files.items(): (self.directory / key).write_bytes(content)
            path = self.directory / name
            if value is None: path.unlink()
            else: path.write_bytes(value)
            before = {p.name: p.read_bytes() for p in self.directory.iterdir()}
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                build.packed_bank(self.directory, self.expected)
            self.assertEqual({p.name: p.read_bytes() for p in self.directory.iterdir()}, before)
        with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.decoded)):
            result = build.recover_inputs(self.root)
        self.assertEqual((Path(result['backup_directory']) / 'manifest.json').read_bytes(), b'{}')
        self.assertEqual(build.packed_bank(self.directory, self.expected)[0], self.payload)

    def test_semantic_edits_extents_count_and_races_fail(self):
        records = deepcopy(self.decoded); records['0:5']['records'][0]['initial_state'] = 0
        source = self.directory / 'records.json'; source.write_text(json.dumps(records))
        with self.assertRaisesRegex(ValueError, 'original decoded'): build.packed_bank(self.directory, self.expected)
        source.write_text(json.dumps(self.decoded))
        for field, value in [('record_count', 2), ('rom_start', 0), ('rom_end', 20)]:
            expected = deepcopy(self.expected); expected['entries'][0][field] = value
            with patch.object(build, 'input_hashes', return_value={}):
                with self.assertRaises(ValueError): build.packed_bank(self.directory, expected)
        encode = build.codec.encode
        def changing(*args):
            data = encode(*args)
            with source.open('a') as file: file.write(' ')
            return data
        with patch.object(build.codec, 'encode', side_effect=changing):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_bank(self.directory, self.expected)

    def test_report_uses_actual_object_and_only_fresh_semantic_ranges(self):
        from test_objdiff_data_targets import object_file, targets
        linked = self.root / 'build/us/assets' / (build.PART + '.o'); linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)])); output = self.root / 'report'
        with patch.object(targets, 'ROOT', self.root):
            unit, item = targets.prepare_scene_volume_bank(self.rom, self.expected, output=output)
            self.assertEqual(unit['rom_ranges'], self.expected['rom_ranges']); self.assertEqual(unit['size'], 76)
            self.assertEqual(item['name'], 'assets/scenes/volumes')
            candidate = targets.sections((output / unit['base_path']).read_bytes(), 1)['.data'][1]
            self.assertEqual(candidate, codec.encode(sphere(), 3) + codec.encode(volume(), 5))
            changed = bytearray(self.payload); changed[0] ^= 1
            linked.write_bytes(object_file([('.data', 1, 3, bytes(changed))]))
            with self.assertRaisesRegex(ValueError, 'linked candidate'):
                targets.prepare_scene_volume_bank(self.rom, self.expected, output=output)
            linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
            wrong = bytearray(self.rom); wrong[14] ^= 1
            with self.assertRaisesRegex(ValueError, 'original ROM'):
                targets.prepare_scene_volume_bank(bytes(wrong), self.expected, output=output)
            expected = deepcopy(self.expected); expected['rom_ranges'][0][0] -= 1
            with patch.object(targets.scene_volume_build, 'input_hashes', return_value={}):
                with self.assertRaisesRegex(ValueError, 'report ranges'):
                    targets.prepare_scene_volume_bank(self.rom, expected, output=output)
