"""Visibility node sets, native CPU geometry and independently decoded flags."""
from copy import deepcopy
import json
from pathlib import Path
import struct
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch
from scripts import visibility_codec as codec, visibility_geometry as geometry, visibility_build as build
from test_visibility_build import native_tree


def codebook():
    return {'format': codec.FORMAT, 'codes': [f'{n:08b}' for n in range(256)]}


def record():
    return {'format': codec.BITMAP_FORMAT, 'node_count': 5, 'visible_nodes': [[0, 4], [], [1, 2, 3], [4]]}


def forward_flags(data, book, count):
    tree, result, node = native_tree(codec.encode_codebook(book)), [], 0
    for byte in data:
        for shift in range(7, -1, -1):
            node = tree[node][1 + ((byte >> shift) & 1)] // 6
            if tree[node][0] >= 0:
                result.append(tree[node][0]); node = 0
                if len(result) == count: return bytes(result)
    raise ValueError('incomplete native symbols')


class BitmapTests(unittest.TestCase):
    def test_native_lsb_node_order_and_row_mutation(self):
        source, book = record(), codebook()
        data = codec.encode_bitmap(source, book)
        self.assertEqual(codec.decode_bitmap(data, 5, book), source)
        self.assertEqual(forward_flags(data, book, 64), b'\x11' + bytes(15) + bytes(16) + b'\x0e' + bytes(15) + b'\x10' + bytes(15))
        source['visible_nodes'][0].append(3)
        source['visible_nodes'][0].sort()
        fresh = codec.encode_bitmap(source, book)
        self.assertNotEqual(data, fresh)
        self.assertEqual(forward_flags(fresh, book, 64)[0], 0x19)

    def test_rejects_invalid_node_sets_and_dimensions(self):
        for value in (True, 0, 2, 21849, 1.0):
            with self.assertRaises(ValueError): codec.bitmap_dimensions(value)
        for value in (None, {}, [], [[0]]):
            bad = record(); bad['visible_nodes'] = value
            with self.assertRaises(ValueError): codec.encode_bitmap(bad, codebook())
        for values in ([1, 0], [0, 0], [5], [-1], [True], ['1']):
            bad = record(); bad['visible_nodes'][0] = values
            with self.assertRaises(ValueError): codec.encode_bitmap(bad, codebook())
        bad = dict(record(), raw_padding='00')
        with self.assertRaises(ValueError): codec.encode_bitmap(bad, codebook())
        book = codebook(); book['codes'][17] = None
        with self.assertRaisesRegex(ValueError, 'no Huffman symbol'): codec.encode_bitmap(record(), book)

    def test_rejects_unused_bits_trailing_data_and_huffman_holes(self):
        data = codec.encode_bitmap(record(), codebook())
        for offset, value in ((0, 32), (1, 1), (63, 1)):
            bad = bytearray(data); bad[offset] = value
            with self.assertRaisesRegex(ValueError, 'unused node bits'): codec.decode_bitmap(bytes(bad), 5, codebook())
        for bad in (data[:-1], data + bytes(8)):
            with self.assertRaises(ValueError): codec.decode_bitmap(bad, 5, codebook())
        book = {'format': codec.FORMAT, 'codes': ['0', '10'] + [None] * 254}
        single = {'format': codec.BITMAP_FORMAT, 'node_count': 1, 'visible_nodes': [[0]]}
        encoded = codec.encode_bitmap(single, book)
        self.assertEqual(len(encoded), 8)
        self.assertEqual(codec.decode_bitmap(encoded, 1, book), single)
        with self.assertRaisesRegex(ValueError, 'alignment'): codec.decode_bitmap(encoded[:-1] + b'\x01', 1, book)
        with self.assertRaisesRegex(ValueError, 'absent branch'): codec.decode_bitmap(b'\xff' * 8, 1, book)


class GeometryTests(unittest.TestCase):
    def primary(self, commands):
        payload = b''.join(struct.pack('>II', *pair) for pair in commands)
        return struct.pack('>II', 8, len(payload)) + payload

    def test_cpu_triangle_opcodes_and_vertex_cache(self):
        data = self.primary([(0x01003006, 0x01000000), (0x05000204, 0),
                             (0x06000204, 0x00000402), (0x10000000, 0), (0xDF000000, 0)])
        faces, loads = geometry.cpu_faces(data, 3)
        self.assertEqual(faces, ((0, 1, 2), (0, 1, 2), (0, 2, 1)) + ((0, 0, 0),) * 4)
        self.assertEqual(loads, 1)
        for load in ((0x01003008, 0x01000000), (0x01003006, 0x02000000),
                     (0x01003006, 0x01000001), (0x01003006, 0x01000010)):
            with self.assertRaises(ValueError): geometry.cpu_faces(self.primary([load, (0xDF000000, 0)]), 3)
        for commands in ([(0x05000204, 0), (0xDF000000, 0)], [(0x01003006, 0x01000000)]):
            with self.assertRaises(ValueError): geometry.cpu_faces(self.primary(commands), 3)

    def test_inclusive_overlap_and_exact_subdivision_thresholds(self):
        self.assertTrue(geometry.intersects(((2, 0), (0, 2), (2, 2)), 0, 0, 1))
        self.assertFalse(geometry.intersects(((3, 0), (0, 3), (3, 3)), 0, 0, 1))
        point = ((-30000, -30000),) * 3
        self.assertEqual(geometry.quadtree_dimensions([point] * 9), (1, 1))
        self.assertEqual(geometry.quadtree_dimensions([point] * 10), (29, 22))
        point = ((100, 100),) * 3
        self.assertEqual(geometry.quadtree_dimensions([point] * 10, half=512), (5, 4))
        self.assertEqual(geometry.quadtree_dimensions([point] * 10, half=256), (1, 1))

    def test_scene_rejects_vertical_slab_and_disagreement(self):
        primary = self.primary([(0x01003006, 0x01000000), (0x05000204, 0), (0xDF000000, 0)])
        vertices = [SimpleNamespace(x=0, y=0, z=0), SimpleNamespace(x=1, y=0, z=0), SimpleNamespace(x=0, y=0, z=1)]
        parsed = SimpleNamespace(vertices=vertices, faces=((0, 1, 2),))
        with patch.object(geometry.model_assets, 'parse_model_bundle', return_value=[SimpleNamespace(index=0, data=primary)]), patch.object(geometry.model_assets, 'parse_model_geometry', return_value=parsed):
            self.assertEqual(geometry.scene_dimensions(b'fixture')['node_count'], 1)
            vertices[0].y = 16000
            with self.assertRaisesRegex(ValueError, 'vertical slab'): geometry.scene_dimensions(b'fixture')
            vertices[0].y = 0; parsed.faces = ((1, 0, 2),)
            with self.assertRaisesRegex(ValueError, 'differs'): geometry.scene_dimensions(b'fixture')


class BitmapPackingTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(); self.addCleanup(temp.cleanup)
        self.root, self.sources = Path(temp.name), {'4': record(), '5': codebook()}
        self.expected = {'rom_start': 0, 'entries': []}
        payload = bytearray(b'raw-index')
        for index in (4, 5):
            data = codec.encode_bitmap(self.sources['4'], self.sources['5']) if index == 4 else codec.encode_codebook(self.sources['5'])
            stored = build.encode_payload(data, 6)
            row = {'entry': index, 'rom_start': len(payload), 'rom_end': len(payload) + len(stored),
                   'encoder': 6, 'decoded_sha256': build.sha256(data)}
            if index == 4: row['geometry'] = {'node_count': 5}
            self.expected['entries'].append(row); payload.extend(stored)
        payload.extend(b'raw-uncredited')
        self.rom = bytes(payload)
        self.expected.update(rom_end=len(payload), original_sha256=build.sha256(payload))
        self.directory = self.root / build.INPUT_DIRECTORY
        build.texture_build.publish_inputs(self.directory, build.input_files(self.rom, self.expected, self.sources))

    def test_bitmap_sources_drive_ranges_and_invalid_sources_are_preserved(self):
        packed, spans, _ = build.packed_bank(self.directory, self.expected)
        self.assertEqual(packed, self.rom)
        self.assertEqual(len(spans), 2)
        path = self.directory / 'bitmaps.json'; original = path.read_bytes()
        bad = deepcopy(self.sources['4']); bad['visible_nodes'][0] = []
        for data in (None, b'[]', b'{}', b'bad', json.dumps({'4': bad}).encode()):
            if data is None: path.unlink()
            else: path.write_bytes(data)
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): build.packed_bank(self.directory, self.expected)
            self.assertEqual(path.read_bytes() if path.exists() else None, data)
            path.write_bytes(original)
        wrong = deepcopy(self.expected); wrong['entries'][0]['geometry']['node_count'] = 9
        with patch.object(build, 'input_hashes', return_value={}):
            with self.assertRaisesRegex(ValueError, 'native geometry'): build.packed_bank(self.directory, wrong)

    def test_bitmap_source_race_is_detected(self):
        encode = codec.encode_bitmap
        def changing(*args):
            data = encode(*args)
            with (self.directory / 'bitmaps.json').open('a') as file: file.write(' ')
            return data
        with patch.object(codec, 'encode_bitmap', side_effect=changing):
            with self.assertRaisesRegex(ValueError, 'changed during packing'): build.packed_bank(self.directory, self.expected)
