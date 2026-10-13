from __future__ import annotations
from copy import deepcopy
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch
from scripts import animation_clips_build as build
from test_model_animation_build import animation_payload


class AnimationClipsBuildTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(); self.addCleanup(temp.cleanup)
        self.root = Path(temp.name); self.part = build.PARTS[0]
        clip = build.codec.animation_records(animation_payload())['clips'][0]
        desc, stream = build.codec.encode_clip(clip); self.fresh = desc + stream
        self.payload = b'unproved' + self.fresh + b'unknown!' + self.fresh + b'raw tail'
        self.rom = b'prefix' + self.payload + b'suffix'
        self.records = {'82': {'1': deepcopy(clip)}, '83': {'0': deepcopy(clip)}}
        self.expected = {'part': self.part, 'rom_start': 6, 'rom_end': 6 + len(self.payload),
                         'original_sha256': build.sha256(self.payload), 'entries': [], 'rom_ranges': []}
        for entry, pair, offset in ((82, 1, 14), (83, 0, 22 + len(self.fresh))):
            row = {'pair': pair, 'rom_start': offset, 'rom_end': offset + len(self.fresh),
                   'descriptor_size': len(desc), 'stream_size': len(stream), 'runtime_duration': 255,
                   'original_sha256': build.sha256(self.fresh)}
            self.expected['entries'].append({'entry': entry, 'clips': [row]})
            self.expected['rom_ranges'].append([row['rom_start'], row['rom_end']])
        self.directory = self.root / build.input_directory(self.part)
        build.texture_build.publish_inputs(self.directory, build.input_files(self.rom, self.expected, self.records))

    def test_rebuilds_only_selected_clips_and_preserves_uncredited_bytes(self):
        packed, spans, before = build.packed_object(self.directory, self.expected)
        self.assertEqual(packed, self.payload)
        self.assertEqual([data for _, data in spans], [self.fresh] * 2)
        self.assertEqual(sum(len(data) for _, data in spans), len(self.payload) - 24)
        with patch.object(build, 'reviewed_objects', return_value=(self.rom, [(self.expected, self.records)])):
            proofs = build.build_parts(self.root)
            part = self.root / 'build/us/animation-clips/parts' / (build.part_name(self.part) + '.bin')
            timestamp = part.stat().st_mtime_ns
            self.assertEqual(build.build_parts(self.root), proofs)
            self.assertEqual(part.stat().st_mtime_ns, timestamp)
            part.unlink(); build.build_parts(self.root)
            self.assertEqual(part.read_bytes(), self.payload)
            self.assertEqual(proofs[0]['rebuilt_bytes'], len(self.fresh) * 2)
        self.assertEqual(build.input_hashes(self.directory, self.expected), before)

    def test_changed_missing_or_invalid_inputs_are_preserved_and_recover_backs_up(self):
        original = build.input_files(self.rom, self.expected, self.records)
        for name, data in [('clips.json', None), ('clips.json', b'null'), ('clips.json', b'{}'),
                           ('clips.json', b'bad'), ('backing.bin', b'changed'), ('manifest.json', b'{}')]:
            for key, value in original.items(): (self.directory / key).write_bytes(value)
            file = self.directory / name
            if data is None: file.unlink()
            else: file.write_bytes(data)
            before = {p.name: p.read_bytes() for p in self.directory.iterdir()}
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                build.packed_object(self.directory, self.expected)
            self.assertEqual({p.name: p.read_bytes() for p in self.directory.iterdir()}, before)
        with patch.object(build, 'reviewed_objects', return_value=(self.rom, [(self.expected, self.records)])):
            result = build.recover_inputs(self.part, self.root)
        self.assertEqual((Path(result['backup_directory']) / 'manifest.json').read_bytes(), b'{}')
        self.assertEqual(build.packed_object(self.directory, self.expected)[0], self.payload)

    def test_clip_set_edits_and_semantic_changes_do_not_get_opaque_credit(self):
        mutations = [lambda r: r['82'].update({'0': r['82']['1']}),
                     lambda r: r['82'].pop('1'), lambda r: r.update({'84': {}}),
                     lambda r: r['82']['1']['frames'][0]['root_offsets'].__setitem__(0, 0),
                     lambda r: r['82']['1'].update(opaque='raw bytes')]
        for mutate in mutations:
            changed = deepcopy(self.records); mutate(changed)
            source = self.directory / 'clips.json'; source.write_text(json.dumps(changed))
            with self.assertRaises(ValueError): build.packed_object(self.directory, self.expected)
            self.assertEqual(json.loads(source.read_text()), changed)

    def test_extent_range_and_source_race_checks(self):
        for field, value in [('descriptor_size', 8), ('stream_size', 8), ('rom_start', 0)]:
            expected = deepcopy(self.expected); expected['entries'][0]['clips'][0][field] = value
            with patch.object(build, 'input_hashes', return_value={}):
                with self.assertRaises(ValueError): build.packed_object(self.directory, expected)
        expected = deepcopy(self.expected); expected['rom_ranges'][0][0] -= 8
        with patch.object(build, 'input_hashes', return_value={}):
            with self.assertRaisesRegex(ValueError, 'ranges changed'):
                build.packed_object(self.directory, expected)
        encode = build.codec.encode_clip
        def changing(*args, **kwargs):
            result = encode(*args, **kwargs)
            with (self.directory / 'clips.json').open('a') as file: file.write(' ')
            return result
        with patch.object(build.codec, 'encode_clip', side_effect=changing):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_object(self.directory, self.expected)

    def test_report_uses_actual_linker_objects_and_only_typed_ranges(self):
        from test_objdiff_data_targets import object_file, targets
        linked = self.root / 'build/us/assets' / (build.part_name(self.part) + '.o')
        linked.parent.mkdir(parents=True); linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        output = self.root / 'report'
        with patch.object(targets, 'ROOT', self.root):
            unit, item = targets.prepare_animation_clips_object(self.rom, self.expected, output=output)
            self.assertEqual(unit['rom_ranges'], self.expected['rom_ranges'])
            self.assertEqual(unit['size'], len(self.fresh) * 2)
            self.assertEqual(item['name'], 'assets/animations/partial/' + self.part)
            candidate = targets.sections((output / unit['base_path']).read_bytes(), 1)['.data'][1]
            self.assertEqual(candidate, self.fresh * 2)
            changed = bytearray(self.payload); changed[0] ^= 1
            linked.write_bytes(object_file([('.data', 1, 3, bytes(changed))]))
            with self.assertRaisesRegex(ValueError, 'linked candidate'):
                targets.prepare_animation_clips_object(self.rom, self.expected, output=output)
            linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
            changed_rom = bytearray(self.rom); changed_rom[14] ^= 1
            with self.assertRaisesRegex(ValueError, 'original ROM'):
                targets.prepare_animation_clips_object(bytes(changed_rom), self.expected, output=output)
