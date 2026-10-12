"""Native route semantics, shared paths, reconstruction provenance and credit."""
from copy import deepcopy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch
from scripts import route_codec as codec, route_build as build


def paths():
    return {'format': codec.PATH_FORMAT, 'actor_paths': [0, None, 0, 1], 'paths': [
        [{'position': [-100, 200, 300], 'control': 9}, {'position': [4, -5, 6], 'control': 65535}],
        [{'position': [7, 8, -9], 'control': 0}]]}


def graph():
    return {'format': codec.GRAPH_FORMAT, 'nodes': [
        {'position': [-10, 20, 30], 'height_band': 2, 'identifier': 42, 'radius': 20,
         'neighbors': [1, None, None, None, None], 'group': 4, 'trigger': 5},
        {'position': [1, -2, 3], 'height_band': 3, 'identifier': 7, 'radius': 11,
         'neighbors': [0, 1, None, None, None], 'group': 1, 'trigger': 9}]}


class RouteCodecTests(unittest.TestCase):
    def test_paths_derive_native_directory_and_preserve_aliases(self):
        record = paths(); data = codec.encode_paths(record)
        self.assertEqual(list(struct.iter_unpack('>II', data[:32])), [(32, 2), (0, 0), (32, 2), (48, 1)])
        self.assertEqual(len(data), 64)
        self.assertEqual(codec.decode_paths(data, 4), record)
        self.assertEqual(data[56:], bytes(8))
        # A shared path edit reaches both native actor pointers.
        record['paths'][0][0]['position'][0] = -123
        record['paths'][0][0]['control'] = 77
        fresh = codec.encode_paths(record)
        for actor in (0, 2):
            offset, count = struct.unpack_from('>II', fresh, actor * 8)
            self.assertEqual(count, 2)
            self.assertEqual(struct.unpack_from('>hhhH', fresh, offset), (-123, 200, 300, 77))
        empty = {'format': codec.PATH_FORMAT, 'actor_paths': [], 'paths': []}
        self.assertEqual(codec.encode_paths(empty), b'')
        self.assertEqual(codec.decode_paths(b'', 0), empty)

    def test_paths_reject_gaps_alias_conflicts_and_unexplained_padding(self):
        original = codec.encode_paths(paths())
        for at, value in ((0, 40), (4, 256), (8, 8), (12, 1), (20, 1)):
            bad = bytearray(original); struct.pack_into('>I', bad, at, value)
            with self.assertRaises(ValueError): codec.decode_paths(bytes(bad), 4)
        for data in (original[:-1], original + bytes(16), original[:-1] + b'\x01'):
            with self.assertRaises(ValueError): codec.decode_paths(data, 4)
        for count in (True, -1, 240):
            with self.assertRaises(ValueError): codec.decode_paths(original, count)

    def test_paths_reject_nonsemantic_sources_and_out_of_width_values(self):
        for actor_refs in ([True], [-1], [2], [0] * 240):
            bad = paths(); bad['actor_paths'] = actor_refs
            with self.assertRaises(ValueError): codec.encode_paths(bad)
        for value in ([], [0, 1], [0, 0, 32768], [0, False, 0]):
            bad = paths(); bad['paths'][0][0]['position'] = value
            with self.assertRaises(ValueError): codec.encode_paths(bad)
        for value in (-1, 65536, True):
            bad = paths(); bad['paths'][0][0]['control'] = value
            with self.assertRaises(ValueError): codec.encode_paths(bad)
        for mutate in (lambda r: r.update(raw='00'), lambda r: r['paths'].append(r['paths'][0]),
                       lambda r: r['paths'].__setitem__(0, [])):
            bad = paths(); mutate(bad)
            with self.assertRaises(ValueError): codec.encode_paths(bad)

    def test_graph_native_coordinates_links_groups_and_triggers(self):
        record = graph(); data = codec.encode_graph(record)
        self.assertEqual(codec.decode_graph(data), record)
        self.assertEqual(struct.unpack_from('>HH', data), (2, 0))
        self.assertEqual(struct.unpack_from('>hhh10B', data, 4), (-10, 20, 30, 2, 42, 20, 1, 255, 255, 255, 255, 4, 5))
        record['nodes'][0]['neighbors'][0] = 0
        record['nodes'][0]['trigger'] = 9
        fresh = codec.encode_graph(record)
        self.assertNotEqual(fresh, data)
        self.assertEqual(fresh[13], 0)
        self.assertEqual(fresh[19], 9)
        self.assertEqual(fresh[-4:], bytes(4))

    def test_graph_rejects_unreviewed_header_links_and_padding(self):
        original = codec.encode_graph(graph())
        for at, value in ((3, 61), (10, 6), (13, 253), (39, 1)):
            bad = bytearray(original); bad[at] = value
            with self.assertRaises(ValueError): codec.decode_graph(bytes(bad))
        for data in (original[:2], original[:-1], original + bytes(8)):
            with self.assertRaises(ValueError): codec.decode_graph(data)
        for field, value in (('identifier', 256), ('radius', -1), ('group', True), ('trigger', 256),
                             ('neighbors', []), ('neighbors', [0, 0, 0, 0, 2])):
            bad = graph(); bad['nodes'][0][field] = value
            with self.assertRaises(ValueError): codec.encode_graph(bad)
        with self.assertRaises(ValueError): codec.encode_graph(dict(graph(), secondary_header=61))


class RouteBuildTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(); self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.fixtures = {}
        for bank, index, record in ((0x10, 0, paths()), (0x19, 2, graph())):
            data = build.encode_record(bank, record); stored = build.encode_payload(data)
            payload = b'rawindex' + stored + b'uncredited'
            expected = {'bank': bank, 'rom_start': 6, 'rom_end': 6 + len(payload),
                        'original_sha256': build.sha256(payload), 'rom_ranges': [[14, 14 + len(stored)]],
                        'entries': [{'entry': index, 'rom_start': 14, 'rom_end': 14 + len(stored),
                                     'decoded_sha256': build.sha256(data), 'encoder': {'level': 6, 'window_bits': -15}}]}
            if bank == 0x10: expected['entries'][0]['actors'] = {'count': 4}
            decoded, rom = {str(index): record}, b'prefix' + payload + b'tail'
            directory = self.root / build.input_directory(bank)
            build.texture_build.publish_inputs(directory, build.input_files(rom, expected, decoded))
            self.fixtures[bank] = rom, expected, decoded, payload, directory, len(stored)

    def test_build_preserves_sources_and_timestamps_and_repairs_parts(self):
        for bank, (rom, expected, decoded, payload, directory, size) in self.fixtures.items():
            before = build.input_hashes(directory, expected)
            with patch.object(build, 'reviewed_bank', return_value=(rom, expected, decoded)):
                proof = build.build_parts(bank, self.root)
                part = self.root / 'build/us/routes/parts' / (build.part_name(bank) + '.bin')
                timestamp = part.stat().st_mtime_ns
                self.assertEqual(build.build_parts(bank, self.root), proof)
                self.assertEqual(part.stat().st_mtime_ns, timestamp)
                part.unlink(); build.build_parts(bank, self.root)
                self.assertEqual(part.read_bytes(), payload)
                self.assertEqual(proof['rebuilt_bytes'], size)
            self.assertEqual(build.input_hashes(directory, expected), before)

    def test_missing_or_changed_sources_fail_without_overwriting_and_recover_backs_up(self):
        bank = 0x10; rom, expected, decoded, payload, directory, _ = self.fixtures[bank]
        originals = build.input_files(rom, expected, decoded)
        for name, value in (('routes.json', None), ('routes.json', b'{}'), ('routes.json', b'bad'),
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

    def test_native_actor_count_and_source_race_are_checked(self):
        rom, expected, decoded, payload, directory, _ = self.fixtures[0x10]
        bad = deepcopy(expected); bad['entries'][0]['actors']['count'] = 3
        with patch.object(build, 'input_hashes', return_value={}):
            with self.assertRaisesRegex(ValueError, 'native placements'): build.packed_bank(directory, bad)
        encode = build.encode_record
        def changing(*args):
            data = encode(*args)
            with (directory / 'routes.json').open('a') as file: file.write(' ')
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
                unit, item = targets.prepare_route_bank(rom, expected, output=output)
                self.assertEqual(unit['rom_ranges'], expected['rom_ranges'])
                self.assertEqual(unit['report_data_bytes'], size)
                self.assertEqual(item['name'], f'assets/routes/bank{bank:02X}')
                native = targets.sections((output / f'route-bank{bank:02X}/base.o').read_bytes(), 1)['.data'][1]
                self.assertEqual(native, rom[14:14 + size])
                linked.write_bytes(object_file([('.data', 1, 3, bytes(len(payload)))]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'): targets.prepare_route_bank(rom, expected, output=output)
