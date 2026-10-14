"""Native animation controls, generated boundaries and actual linked credit."""
from copy import deepcopy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch
from scripts import animation_control_codec as codec, animation_control_build as build


def controls():
    return {'format': codec.FORMAT, 'routes': [
        {'descriptor': 2, 'duration_index': 3, 'event': 0},
        {'descriptor': 4, 'duration_index': 0, 'event': 0}],
        'events': [[{'frame': 1.5, 'opcode': 9, 'argument': 0xFF010203}]],
        'actions': [{'selector': 7, 'sound': 0xFF020304, 'response': 35, 'phases': [
            {'animation': 3, 'speed_percent': 100, 'flags': 1},
            {'animation': 4, 'speed_percent': 120, 'flags': 200},
            {'animation': 0, 'speed_percent': 0, 'flags': 0}]}],
        'programs': [[{'marker': 247}, {'opcode': 8, 'parameters': [0, 1, 0, 1]}],
                     [{'opcode': 0, 'parameters': [0, 0, 0, 0]}]],
        'behaviors': [{'selector': 1, 'program': 0}, {'selector': 2, 'program': 0},
                      {'selector': 3, 'program': 1}]}


class AnimationControlCodecTests(unittest.TestCase):
    def test_native_offsets_widths_aliases_and_nop(self):
        record = controls(); data = codec.encode(record)
        self.assertEqual(codec.decode(data), record)
        behavior, collision, action, size = struct.unpack_from('>4I', data)
        self.assertEqual((collision, action, size), (0, 64, 24))
        self.assertEqual(struct.unpack_from('>HHI', data, 16), (2, 3, 24))
        self.assertEqual(struct.unpack_from('>HHI', data, 24), (4, 0, 24))
        self.assertEqual(struct.unpack_from('>fII', data, 40), (1.5, 9, 0xFF010203))
        self.assertEqual(struct.unpack_from('>fII', data, 52), (999.0, 0, 0))
        self.assertEqual(struct.unpack_from('>B3xIBxHBB', data, 64), (7, 0xFF020304, 35, 3, 100, 1))
        self.assertEqual(data[88:94], bytes([247, 8, 0, 1, 0, 1]))
        self.assertEqual(struct.unpack_from('>I', data, behavior)[0], 72)
        self.assertEqual(struct.unpack_from('>I', data, behavior + 8)[0], 72)
        record['events'][0][0]['argument'] = 42
        changed = codec.encode(record)
        self.assertEqual(changed[:48], data[:48]); self.assertEqual(changed[52:], data[52:])
        self.assertEqual(struct.unpack_from('>I', changed, 48)[0], 42)

    def test_unexplained_spans_and_collision_fields_rejected(self):
        data = codec.encode(controls())
        for at in (4, 39, 44, 63, 65, 73, 86, 94, 109, len(data) - 1):
            bad = bytearray(data); bad[at] ^= 1
            with self.subTest(at=at), self.assertRaises(ValueError): codec.decode(bytes(bad))
        for bad in (data[:16], data[:-1], data + bytes(16)):
            with self.assertRaises(ValueError): codec.decode(bad)
        # A four-byte zero tail cannot be minimal four-byte alignment.
        record = controls(); record['programs'][0] = [{'opcode': 8, 'parameters': [0]*4}]*4
        native = bytearray(codec.encode(record)); at = struct.unpack_from('>I', native)[0]
        start = struct.unpack_from('>I', native, at+16)[0]+16
        native[start:start] = bytes(4)
        struct.pack_into('>I', native, 0, at+4)
        struct.pack_into('>I', native, at+4+16, start-16+4)
        native.extend(bytes((-len(native))%16))
        with self.assertRaises(ValueError): codec.decode(bytes(native))

    def test_invalid_semantic_sources_and_widths_rejected(self):
        mutations = [lambda r: r.update(raw_bytes='00'),
            lambda r: r['routes'][0].update(descriptor=3),
            lambda r: r['routes'][0].update(event=5),
            lambda r: r['events'][0][0].update(frame=float('nan')),
            lambda r: r['events'][0][0].update(opcode=256),
            lambda r: r['actions'][0].update(selector=True),
            lambda r: r['actions'][0]['phases'][0].update(animation=65536),
            lambda r: r['programs'][0][0].update(marker=246),
            lambda r: r['programs'][0][1].update(parameters=[1,2]),
            lambda r: r['behaviors'][0].update(program=-1),
            lambda r: r['programs'].append([{'marker': 247}])]
        for mutate in mutations:
            record = controls(); mutate(record)
            with self.assertRaises(ValueError): codec.encode(record)


class AnimationControlBuildTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(); self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.fixtures = {}
        for bank, index, record in ((0x0F, 6, controls()),):
            data = build.encode_record(bank, record); stored = build.encode_payload(data)
            payload = b'rawindex' + stored + b'uncredited'
            expected = {'bank': bank, 'rom_start': 6, 'rom_end': 6 + len(payload),
                        'original_sha256': build.sha256(payload), 'rom_ranges': [[14, 14 + len(stored)]],
                        'entries': [{'entry': index, 'rom_start': 14, 'rom_end': 14 + len(stored),
                                     'decoded_sha256': build.sha256(data), 'encoder': {'level': 6, 'window_bits': -15}}]}
            decoded, rom = {str(index): record}, b'prefix' + payload + b'tail'
            directory = self.root / build.input_directory(bank)
            build.texture_build.publish_inputs(directory, build.input_files(rom, expected, decoded))
            self.fixtures[bank] = rom, expected, decoded, payload, directory, len(stored)

    def test_build_preserves_sources_and_timestamps_and_repairs_parts(self):
        for bank, (rom, expected, decoded, payload, directory, size) in self.fixtures.items():
            before = build.input_hashes(directory, expected)
            with patch.object(build, 'reviewed_bank', return_value=(rom, expected, decoded)):
                proof = build.build_parts(bank, self.root)
                part = self.root / 'build/us/animation-control/parts' / (build.part_name(bank) + '.bin')
                timestamp = part.stat().st_mtime_ns
                self.assertEqual(build.build_parts(bank, self.root), proof)
                self.assertEqual(part.stat().st_mtime_ns, timestamp)
                part.unlink(); build.build_parts(bank, self.root)
                self.assertEqual(part.read_bytes(), payload)
                self.assertEqual(proof['rebuilt_bytes'], size)
            self.assertEqual(build.input_hashes(directory, expected), before)

    def test_missing_or_changed_sources_fail_without_overwriting_and_recover_backs_up(self):
        bank = 0x0F; rom, expected, decoded, payload, directory, _ = self.fixtures[bank]
        originals = build.input_files(rom, expected, decoded)
        for name, value in (('controls.json', None), ('controls.json', b'{}'), ('controls.json', b'bad'),
                            ('manifest.json', b'{}'), ('backing.bin', b'changed')):
            for filename, data in originals.items(): (directory / filename).write_bytes(data)
            path = directory / name
            if value is None: path.unlink()
            else: path.write_bytes(value)
            before = {p.name: p.read_bytes() for p in directory.iterdir()}
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): build.packed_bank(directory, expected)
            self.assertEqual({p.name: p.read_bytes() for p in directory.iterdir()}, before)
        with patch.object(build, 'reviewed_bank', return_value=(rom, expected, decoded)):
            recovered = build.recover_inputs(bank, self.root)
        self.assertEqual((Path(recovered['backup_directory']) / 'backing.bin').read_bytes(), b'changed')
        self.assertEqual(build.packed_bank(directory, expected)[0], payload)

    def test_source_race_is_checked(self):
        rom, expected, decoded, payload, directory, _ = self.fixtures[0x0F]
        encode = build.encode_record
        def changing(*args):
            data = encode(*args)
            with (directory / 'controls.json').open('a') as file: file.write(' ')
            return data
        with patch.object(build, 'encode_record', side_effect=changing):
            with self.assertRaisesRegex(ValueError, 'changed during packing'): build.packed_bank(directory, expected)

    def test_report_credits_only_rebuilt_ranges_of_actual_linked_banks(self):
        from test_objdiff_data_targets import object_file, targets
        for bank, (rom, expected, decoded, payload, directory, size) in self.fixtures.items():
            linked = self.root / 'build/us/assets' / (build.part_name(bank) + '.o')
            linked.parent.mkdir(parents=True, exist_ok=True)
            linked.write_bytes(object_file([('.data', 1, 3, payload)]))
            output = self.root / 'report'
            with patch.object(targets, 'ROOT', self.root):
                unit, item = targets.prepare_animation_control_bank(rom, expected, output=output)
                self.assertEqual(unit['rom_ranges'], expected['rom_ranges'])
                self.assertEqual(unit['report_data_bytes'], size)
                self.assertEqual(item['name'], f'assets/animation-controls/bank{bank:02X}')
                native = targets.sections((output / f'animation-control-bank{bank:02X}/base.o').read_bytes(), 1)['.data'][1]
                self.assertEqual(native, rom[14:14 + size])
                linked.write_bytes(object_file([('.data', 1, 3, bytes(len(payload)))]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'): targets.prepare_animation_control_bank(rom, expected, output=output)
