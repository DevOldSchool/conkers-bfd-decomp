"""Collision record fields, unchanged legacy inputs and linked range evidence."""
from copy import deepcopy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import animation_control_build as build, animation_control_codec as codec
from scripts import collision_control_codec as fields, collision_control_inputs as inputs
from test_animation_control_build import controls


def source():
    record = controls()
    record.update(format=fields.FORMAT, collisions=[{
        'response': 0x81, 'sound': 0xff010203, 'callback': 9, 'angle': 128,
        'distance': 42, 'height': -120, 'extent': 250, 'damage_flags': 0x41,
        'response_angle': 64, 'state_3c': -0.0, 'state_20': 12.5,
        'state_24': -2.25, 'state_109': 3, 'invulnerability': 0x9e, 'flags': 0x810}])
    return record


class CollisionControlTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(); self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.entries = patch.object(inputs, 'ENTRIES', (1,))
        self.entries.start(); self.addCleanup(self.entries.stop)
        old, new = controls(), source()
        old_bytes, new_bytes = [build.encode_payload(codec.encode(r)) for r in (old, new)]
        at = 16 + len(old_bytes) + 3
        self.payload = (struct.pack('>4I', 16, 0x10000000 | len(old_bytes),
                                   at, 0x90000000 | len(new_bytes))
                        + old_bytes + b'gap' + new_bytes + b'end')
        self.rom = b'prefix' + self.payload
        self.expected = {'bank': 15, 'rom_start': 6, 'rom_end': 6 + len(self.payload),
                         'original_sha256': build.sha256(self.payload),
                         'rom_ranges': [[22, 22 + len(old_bytes)]],
                         'entries': [{'entry': 0, 'rom_start': 22, 'rom_end': 22 + len(old_bytes),
                                      'decoded_sha256': build.sha256(codec.encode(old)),
                                      'encoder': {'level': 6, 'window_bits': -15}}]}
        self.old, self.source = {'0': old}, new
        self.directory = self.root / build.input_directory(15)
        self.originals = build.input_files(self.rom, self.expected, self.old)
        build.texture_build.publish_inputs(self.directory, self.originals)
        self.new_range = [6 + at, 6 + at + len(new_bytes)]

    def run_build(self):
        with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.old)):
            return build.build_parts(15, self.root, include_collisions=True)

    def test_native_field_offsets_and_mutations(self):
        original = fields.encode(self.source['collisions'])
        self.assertEqual(original[20:24], bytes.fromhex('80000000'))
        self.assertEqual(struct.unpack_from('>h', original, 12)[0], -120)
        self.assertEqual(fields.encode(fields.decode(original)), original)
        for name, offset, kind in fields.FIELDS:
            record = deepcopy(self.source['collisions'])
            record[0][name] += 1
            changed = fields.encode(record)
            width = struct.calcsize(kind)
            self.assertEqual(changed[:offset], original[:offset])
            self.assertEqual(changed[offset + width:], original[offset + width:])
            self.assertNotEqual(changed[offset:offset + width], original[offset:offset + width])
        data = codec.encode(self.source)
        self.assertEqual(codec.encode(codec.decode(data, allow_collisions=True)), data)
        with self.assertRaisesRegex(ValueError, 'not fully established'): codec.decode(data)
        # Every generated lane rejects nonzero storage, including unresolved +33.
        for offset in (1, 2, 3, 11, 17, 18, 19, 33, 35, 38, 39):
            changed = bytearray(original); changed[offset] = 1
            with self.subTest(offset=offset), self.assertRaises(ValueError): fields.decode(changed)
        start = struct.unpack_from('>I', data, 4)[0]
        for offset in (start - 4, start + 4, len(data)):
            changed = bytearray(data); struct.pack_into('>I', changed, 4, offset)
            with self.assertRaises(ValueError): codec.decode(changed, allow_collisions=True)

    def test_invalid_semantic_values_and_opaque_fields_rejected(self):
        for name, _, kind in fields.FIELDS:
            values = [True, '1', None]
            values += [float('nan'), float('inf'), 1e100, 10**400] if kind == 'f' else [-32769, 2**32]
            for value in values:
                record = deepcopy(self.source['collisions']); record[0][name] = value
                with self.subTest(name=name, value=str(value)), self.assertRaises(ValueError): fields.encode(record)
        for records in ([], {}, self.source['collisions'] * 257, [dict(self.source['collisions'][0], raw='00')]):
            with self.assertRaises(ValueError): fields.encode(records)

    def test_composition_preserves_old_sources_and_missing_output_rebuilt(self):
        self.run_build()
        for name, data in self.originals.items(): self.assertEqual((self.directory / name).read_bytes(), data)
        packed, spans, hashes = build.packed_bank(self.directory, self.expected, include_collisions=True)
        self.assertEqual(packed, self.payload)
        self.assertEqual(len(spans), 1)  # Existing family retains its own range only.
        self.assertEqual(set(hashes), set(self.originals) | {'collision-controls/manifest.json', 'collision-controls/controls.json'})
        output = self.root / 'build/us/animation-control/parts/asset_bank_0f.bin'
        stamp = output.stat().st_mtime_ns
        self.run_build(); self.assertEqual(output.stat().st_mtime_ns, stamp)
        output.unlink(); self.run_build(); self.assertEqual(output.read_bytes(), self.payload)

    def test_missing_or_invalid_child_sources_preserved_and_recovery_backs_up(self):
        self.run_build()
        child = self.directory / inputs.DIRECTORY
        originals = {p.name: p.read_bytes() for p in child.iterdir()}
        for name, data in (('manifest.json', None), ('manifest.json', b'{}'),
                           ('controls.json', None), ('controls.json', b'invalid'), ('controls.json', b'{}')):
            for filename, value in originals.items(): (child / filename).write_bytes(value)
            path = child / name
            if data is None: path.unlink()
            else: path.write_bytes(data)
            before = {p.name: p.read_bytes() for p in child.iterdir()}
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): self.run_build()
            self.assertEqual(before, {p.name: p.read_bytes() for p in child.iterdir()})
        with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.old)):
            result = build.recover_inputs(15, self.root)
        self.assertEqual((Path(result['backup_directory']) / inputs.DIRECTORY / 'controls.json').read_bytes(), b'{}')
        self.run_build()

    def test_edited_fields_fail_exact_build_without_overwrite(self):
        self.run_build(); path = self.directory / inputs.DIRECTORY / 'controls.json'
        for name, _, _ in fields.FIELDS:
            record = deepcopy(self.source); record['collisions'][0][name] += 1
            path.write_text(json.dumps({'1': record}))
            before = path.read_bytes()
            with self.assertRaisesRegex(ValueError, 'no longer reconstruct'): self.run_build()
            self.assertEqual(path.read_bytes(), before)

    def test_source_race_rejected(self):
        self.run_build(); original = inputs.encoded
        def changing(*args):
            result = original(*args)
            with (self.directory / inputs.DIRECTORY / 'controls.json').open('a') as file: file.write(' ')
            return result
        with patch.object(inputs, 'encoded', side_effect=changing):
            with self.assertRaisesRegex(ValueError, 'changed during packing'): self.run_build()

    def test_actual_linked_object_and_disjoint_credit(self):
        from test_objdiff_data_targets import object_file, targets
        self.run_build()
        linked = self.root / 'build/us/assets/asset_bank_0f.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        with patch.object(targets, 'ROOT', self.root), patch.object(targets.collision_control_inputs, 'ENTRIES', (1,)):
            unit, _ = targets.prepare_collision_control_bank(self.rom, self.expected, output=self.root / 'report')
            old, _ = targets.prepare_animation_control_bank(self.rom, self.expected, output=self.root / 'report', include_collisions=True)
            self.assertEqual(unit['rom_ranges'], [self.new_range])
            self.assertEqual(unit['report_data_bytes'], self.new_range[1] - self.new_range[0])
            self.assertEqual(old['rom_ranges'], self.expected['rom_ranges'])
            for offset in (0, self.new_range[0] - 6, len(self.payload) - 1):
                changed = bytearray(self.payload); changed[offset] ^= 1
                linked.write_bytes(object_file([('.data', 1, 3, changed)]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'):
                    targets.prepare_collision_control_bank(self.rom, self.expected, output=self.root / 'report')
