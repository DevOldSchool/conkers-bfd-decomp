"""Scene directory ownership, native cylinders and preserved source children."""
import copy
import json
import struct
import unittest
from unittest.mock import patch

from scripts import scene_structure_codec as codec, scene_structure_inputs as inputs
from scripts import scene_field_build as scenes
import test_scene_field_build as fixtures


def cylinder():
    return {'format': codec.CYLINDER_FORMAT, 'groups': [{'id': 123, 'cylinders': [
        {'x': -32768, 'z': 32767, 'bottom': -32, 'height': 250, 'radius': 32767, 'inside': True}]}]}


class CylinderCodecTests(unittest.TestCase):
    def test_native_fields_offsets_count_and_unowned_sentinel(self):
        source = cylinder()
        raw = struct.pack('>IHH', 16, 1, 123) + bytes(4) + b'raw!' + struct.pack('>4hH', -32768, 32767, -32, 250, 65535)
        self.assertEqual(codec.decode_cylinders(raw), source)
        self.assertEqual(codec.encode_cylinders(source), [(0, raw[:12]), (16, raw[16:])])
        source['groups'].append({'id': 4, 'cylinders': []})
        spans = codec.encode_cylinders(source)
        self.assertEqual(struct.unpack('>IHHIHH', spans[0][1][:16]), (24, 1, 123, 34, 0, 4))
        for key, value in [('x', -32769), ('height', 32768), ('radius', 32768), ('inside', 1), ('bottom', True), ('opaque', 1)]:
            bad = cylinder(); bad['groups'][0]['cylinders'][0][key] = value
            with self.assertRaises(ValueError): codec.encode_cylinders(bad)
        for bad in (b'', raw[:-1], raw + b'\0', struct.pack('>I', 17) + raw[4:], raw[:4] + b'\xff\xff' + raw[6:]):
            with self.assertRaises(ValueError): codec.decode_cylinders(bad)


class SceneStructureBuildTests(unittest.TestCase):
    def setUp(self):
        fixtures.SceneFieldBuildTests.setUp(self)

    def test_directory_tree_generates_exact_tables_and_minimal_alignment(self):
        source = codec.decode_tree(self.payload, self.expected['rom_start'])
        spans = codec.encode_tree(source, self.expected['rom_start'], self.expected['rom_end'])
        self.assertEqual(len(spans[0][1]), 552)
        self.assertTrue(all(self.payload[a:a + len(b)] == b for a, b in spans))
        self.assertTrue(any(b and not any(b) for _, b in spans))
        changed = copy.deepcopy(source); changed['scenes'][0]['directory']['entries'][5]['relative_offset'] += 16
        with self.assertRaises(ValueError): codec.encode_tree(changed, 8, self.expected['rom_end'])
        for value in ([], True, [{'index': True, 'directory': source['scenes'][0]['directory']}]):
            changed = copy.deepcopy(source); changed['scenes'] = value
            with self.assertRaises(ValueError): codec.encode_tree(changed, 8, self.expected['rom_end'])
        at = next(a for a, b in spans if b and not any(b))
        changed = bytearray(self.payload); changed[at] = 1
        with self.assertRaises(ValueError): codec.decode_tree(changed, 8)
        with self.assertRaises(ValueError): codec.decode_tree(b'\xff' * 8, 8)

    def test_all_sources_compose_without_changing_prior_input_hashes(self):
        # Publish the preceding placement child, then record every old input.
        scenes.model_placement_inputs.ensure_inputs(self.directory, self.expected, self.payload)
        old = scenes.input_hashes(self.directory, self.expected, include_model_placements=True)
        scenes.build_parts(self.root)
        self.assertEqual(scenes.input_hashes(self.directory, self.expected, include_model_placements=True), old)
        packed, fields, hashes = scenes.packed_bank(self.directory, self.expected,
            include_model_placements=True, include_scene_structures=True)
        self.assertEqual(packed, self.payload)
        self.assertEqual(len(hashes) - len(old), 4)
        ranges = fields + [(a - 8, self.rom[a:b]) for a, b in self.volume_expected['rom_ranges']]
        ranges += scenes.model_placement_inputs.encoded(self.directory, self.expected, self.payload)
        for family in inputs.FAMILIES:
            ranges += inputs.encoded(self.directory, self.expected, self.payload, family)
        ranges.sort(); self.assertTrue(all(a + len(b) <= c for (a, b), (c, _) in zip(ranges, ranges[1:])))
        cylinders = inputs.encoded(self.directory, self.expected, self.payload, 'cylinders')
        self.assertEqual(sum(len(b) for _, b in cylinders), 22)
        unknown = self.cylinder_offset + 12
        self.assertFalse(any(a <= unknown < a + len(b) for a, b in cylinders))
        part = self.root / 'build/us/scene-fields/parts/asset_bank_0c.bin'
        stamp = part.stat().st_mtime_ns; scenes.build_parts(self.root)
        self.assertEqual(part.stat().st_mtime_ns, stamp)
        part.unlink(); scenes.build_parts(self.root); self.assertEqual(part.read_bytes(), self.payload)

    def test_each_child_preserves_edits_deletions_and_recovery(self):
        scenes.build_parts(self.root)
        part = self.root / 'build/us/scene-fields/parts/asset_bank_0c.bin'
        for family in inputs.FAMILIES:
            path = self.directory / inputs.child(family) / (family + '.json')
            original = path.read_bytes(); source = json.loads(original)
            if family == 'directories': source['outer']['entries'][0]['flags'] = 1
            else: source['entries'][0]['groups'][0]['cylinders'][0]['radius'] += 1
            path.write_text(json.dumps(source)); edited = path.read_bytes()
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): scenes.build_parts(self.root)
            self.assertEqual(path.read_bytes(), edited); self.assertEqual(part.read_bytes(), self.payload)
            path.unlink()
            with self.assertRaises(ValueError): scenes.build_parts(self.root)
            self.assertFalse(path.exists()); path.write_bytes(edited)
            recovery = scenes.recover_inputs(self.root)
            from pathlib import Path
            self.assertEqual((Path(recovery['backup_directory']) / inputs.child(family) / path.name).read_bytes(), edited)
            scenes.build_parts(self.root); self.assertEqual(path.read_bytes(), original)

    def test_source_race_fails_before_publishing(self):
        scenes.build_parts(self.root)
        encode = inputs.encoded
        path = self.directory / inputs.child('directories') / 'directories.json'
        def changing(*args):
            result = encode(*args)
            with path.open('a') as f: f.write(' ')
            return result
        with patch.object(inputs, 'encoded', side_effect=changing):
            with self.assertRaisesRegex(ValueError, 'changed during packing'): scenes.build_parts(self.root)

    def test_report_checks_whole_linked_bank_and_separate_owned_ranges(self):
        from test_objdiff_data_targets import object_file, targets
        scenes.build_parts(self.root)
        linked = self.root / 'build/us/assets/asset_bank_0c.o'; linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        with patch.object(targets, 'ROOT', self.root):
            ranges = []
            for family in inputs.FAMILIES:
                unit, _ = targets.prepare_scene_structure_object(self.rom, self.expected, output=self.root / 'report', family=family)
                ranges += unit['rom_ranges']
                self.assertEqual(unit['report_data_bytes'], sum(len(b) for _, b in inputs.encoded(self.directory, self.expected, self.payload, family)))
            ranges.sort(); self.assertTrue(all(a[1] <= b[0] for a, b in zip(ranges, ranges[1:])))
            for at in (0, self.model_offset + 28, self.cylinder_offset + 12):
                changed = bytearray(self.payload); changed[at] ^= 1
                linked.write_bytes(object_file([('.data', 1, 3, changed)]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'):
                    targets.prepare_scene_structure_object(self.rom, self.expected, output=self.root / 'report', family='cylinders')
