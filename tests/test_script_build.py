"""Native script fields, nested archives and source/report provenance."""
import copy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch
from scripts import script_codec as codec, script_build as build


def script():
    return {'format': codec.FORMAT,
            'position_tracks': [[{'position': [-12, 34, -56], 'control': 0x8042}], []],
            'bindings': [{'kind': 1, 'selector': 2, 'target': -1, 'height_offset': 300},
                         {'kind': 2, 'selector': 5, 'target': 0, 'height_offset': 0}],
            'value_tracks': [[{'value': -1.25, 'interpolation': 0, 'channel': 3, 'time': 200}]],
            'command_tracks': [[{'opcode': -2, 'time_delta': 0, 'selector': -9999,
                                'argument_a': -1, 'argument_b': 127, 'argument_c': -32768},
                               {'opcode': 5, 'time_delta': 12, 'selector': 95,
                                'argument_a': 14, 'argument_b': 13, 'argument_c': 6}]],
            'texts': ['Hello', '\xbeLine\nTwo', '', None]}


def fixture():
    return {'format': codec.FORMAT, 'scenes': [
        {'scripts': [script(), None, script()]}, None, {'scripts': [None, script()]}]}


class ScriptCodecTests(unittest.TestCase):
    def test_native_fields_and_alignment_are_independent_of_raw_backing(self):
        record = script(); data = codec.encode(record)
        self.assertEqual(codec.decode(data), record)
        segments = [struct.unpack_from('>II', data, i * 8) for i in range(11)]
        self.assertEqual(segments[0], (88, 8))
        self.assertEqual(struct.unpack_from('>4H', data, 88), (2, 1, 1, 4))
        self.assertEqual(struct.unpack_from('>3hH', data, segments[1][0]), (-12, 34, -56, 0x8042))
        self.assertEqual(data[segments[3][0]:segments[3][0]+8], struct.pack('>HBbh2x', 1, 2, -1, 300))
        self.assertEqual(struct.unpack_from('>fBBh', data, segments[5][0]), (-1.25, 0, 3, 200))
        self.assertEqual(struct.unpack_from('>bBhbbh', data, segments[6][0]), (-2, 0, -9999, -1, 127, -32768))
        self.assertEqual(segments[10][1], 0x80000000)
        self.assertTrue(all(offset % 8 == 0 for offset, _ in segments))

    def test_text_edits_relocate_later_segments_and_preserve_empty_distinction(self):
        before = codec.encode(script()); changed = script()
        changed['texts'][0] = 'A longer text string'
        after = codec.encode(changed)
        self.assertEqual(codec.decode(after), changed)
        self.assertGreater(struct.unpack_from('>I', after, 8 * 8)[0], struct.unpack_from('>I', before, 8 * 8)[0])
        self.assertEqual(struct.unpack_from('>I', after, 9 * 8 + 4)[0], 2)
        self.assertEqual(struct.unpack_from('>I', after, 10 * 8 + 4)[0], 0x80000000)

    def test_unknown_padding_flags_offsets_and_truncation_fail_closed(self):
        original = codec.encode(script())
        binding = struct.unpack_from('>I', original, 3 * 8)[0]
        text = struct.unpack_from('>I', original, 7 * 8)[0]
        for at in (4, binding + 6, binding + 7, text + 6):
            data = bytearray(original); data[at] ^= 1
            with self.subTest(at=at), self.assertRaises(ValueError): codec.decode(bytes(data))
        for data in (original[:-1], original + bytes(8)):
            with self.assertRaises(ValueError): codec.decode(data)

    def test_source_widths_extra_fields_and_nonfinite_values_are_rejected(self):
        changes = [lambda x: x.update(raw='00'),
                   lambda x: x['bindings'][0].update(padding=0),
                   lambda x: x['bindings'][0].update(kind=8),
                   lambda x: x['bindings'][0].update(target=128),
                   lambda x: x['bindings'][0].update(height_offset=True),
                   lambda x: x['position_tracks'][0][0].update(position=[0, 1, 32768]),
                   lambda x: x['value_tracks'][0][0].update(value=float('nan')),
                   lambda x: x['value_tracks'][0][0].update(channel=15),
                   lambda x: x['command_tracks'][0][0].update(opcode=18),
                   lambda x: x['command_tracks'][0][0].update(time_delta=256),
                   lambda x: x['texts'].__setitem__(0, 'A\0B'),
                   lambda x: x['texts'].__setitem__(0, '\u1000')]
        for change in changes:
            record = script(); change(record)
            with self.assertRaises(ValueError): codec.encode(record)

    def test_bank_nested_slots_flags_and_fresh_compression(self):
        records = fixture(); bank = codec.encode_bank(records)
        scenes = list(struct.iter_unpack('>II', bank[:24]))
        self.assertEqual(scenes[1][1], 0)
        self.assertEqual(scenes[2][1] >> 28, 8)
        for index in (0, 2):
            offset, flags = scenes[index]; scene = bank[offset:offset+(flags & 0x0fffffff)]
            for j, record in enumerate(records['scenes'][index]['scripts']):
                at, flag = struct.unpack_from('>II', scene, j * 8)
                if record is None:
                    self.assertEqual(flag & 0x1fffffff, 0)
                    continue
                self.assertTrue(flag & 0x10000000)
                payload = scene[at:at+(flag & 0x0fffffff)]
                decoded = build.rzip_archive.decode_rzip_chunk(payload)
                self.assertEqual(decoded.consumed, len(payload))
                self.assertEqual(codec.decode(decoded.data), record)


class ScriptBuildTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory()
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.records = fixture()
        self.payload = codec.encode_bank(self.records)
        self.rom = b'prefix' + self.payload + b'tail'
        self.expected = {'rom_start': 6, 'rom_end': 6 + len(self.payload),
                         'original_sha256': build.sha256(self.payload)}
        self.inputs = self.root / build.INPUT_DIRECTORY
        build.texture_build.publish_inputs(self.inputs, build.input_files(self.expected, self.records))

    def test_fresh_source_build_preserves_mtime_and_missing_part_is_repaired(self):
        with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.records)):
            proof = build.build_parts(self.root)
            part = self.root / 'build/us/scripts/parts/asset_bank_06.bin'
            before = [p.stat().st_mtime_ns for p in (part, self.inputs / 'scripts.json')]
            self.assertEqual(build.build_parts(self.root), proof)
            self.assertEqual([p.stat().st_mtime_ns for p in (part, self.inputs / 'scripts.json')], before)
            part.unlink()
            build.build_parts(self.root)
            self.assertEqual(part.read_bytes(), self.payload)

    def test_missing_changed_and_malformed_sources_preserved_until_recovery(self):
        changed = copy.deepcopy(self.records)
        changed['scenes'][0]['scripts'][0]['position_tracks'][0][0]['position'][0] ^= 1
        for name, data in [('scripts.json', json.dumps(changed).encode()), ('scripts.json', b'{'),
                           ('manifest.json', b'{}'), ('scripts.json', None)]:
            for file, content in build.input_files(self.expected, self.records).items():
                (self.inputs / file).write_bytes(content)
            path = self.inputs / name
            if data is None: path.unlink()
            else: path.write_bytes(data)
            before = {p.name: p.read_bytes() for p in self.inputs.iterdir()}
            with self.subTest(name=name), self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                build.packed_bank(self.inputs, self.expected)
            self.assertEqual({p.name: p.read_bytes() for p in self.inputs.iterdir()}, before)
        with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.records)):
            result = build.recover_inputs(self.root)
        backup = Path(result['backup_directory'])
        self.assertFalse((backup / 'scripts.json').exists())
        self.assertEqual(build.packed_bank(self.inputs, self.expected)[0], self.payload)

    def test_source_change_during_encoding_fails(self):
        encode = codec.encode_bank
        def changed(records):
            packed = encode(records)
            with (self.inputs / 'scripts.json').open('a') as file: file.write(' ')
            return packed
        with patch.object(codec, 'encode_bank', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_bank(self.inputs, self.expected)

    def test_report_requires_actual_link_object_from_current_sources(self):
        from test_objdiff_data_targets import object_file, targets
        linked = self.root / 'build/us/assets/asset_bank_06.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        with patch.object(targets, 'ROOT', self.root):
            unit, item = targets.prepare_script_bank(self.rom, self.expected, output=self.root / 'report')
            self.assertTrue(unit['complete'])
            self.assertEqual(unit['report_data_bytes'], len(self.payload))
            self.assertEqual(item['name'], 'assets/asset_bank_06')
            self.assertEqual(len(unit['source_inputs']), 2)
            linked.write_bytes(object_file([('.data', 1, 3, bytes(len(self.payload)))]))
            with self.assertRaisesRegex(ValueError, 'candidate differs'):
                targets.prepare_script_bank(self.rom, self.expected, output=self.root / 'report')
