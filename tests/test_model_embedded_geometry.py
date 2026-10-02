"""ROM-free rejection and independently decoded geometry checks."""
import hashlib
import json
import struct
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from scripts import model_assets as models, model_embedded_geometry as embedded
from scripts.model_inspection import pack_glb, read_glb


class EmbeddedGeometryTests(unittest.TestCase):
    code_base = 0x15160000
    data_base = 0x8008B000

    def source(self):
        code = bytearray(0x15187EC0 - self.code_base)
        # Literal instruction words independently transcribed from the raw ASM.
        instructions = {0x15187B18: 0x3C178009, 0x15187B28: 0x26F7D538,
                        0x15187CC8: 0x3C0E0100, 0x15187CCC: 0x35CE4008,
                        0x15187CE0: 0x3C0F0500, 0x15187CE4: 0x35EF0204,
                        0x15187CF8: 0x3C180500, 0x15187CFC: 0x37180206,
                        0x15187D10: 0x3C080500, 0x15187D14: 0x35080406}
        for address, word in instructions.items():
            struct.pack_into('>I', code, address - self.code_base, word)
        data = bytearray(0x3000)
        for address, raw in embedded.DATA_SPANS:
            data[address - self.data_base:address - self.data_base + len(raw)] = raw
        return code, data

    def describe(self, code, data, original=None):
        original = code if original is None else original
        pins = [(a, n, hashlib.sha1(original[a-self.code_base:a-self.code_base+n]).hexdigest())
                for a, n, _ in embedded.CONSUMERS]
        with patch.object(embedded, 'CONSUMERS', pins):
            return embedded.describe_geometry(code, self.code_base, data, self.data_base)

    def test_entire_consumer_spans_reject_mutation(self):
        original, data = self.source()
        for address, size, _ in embedded.CONSUMERS:
            for delta in (0, size // 2, size - 1):
                changed = bytearray(original)
                changed[address - self.code_base + delta] ^= 1
                with self.subTest(address=hex(address), delta=delta), self.assertRaisesRegex(ValueError, 'consumer changed'):
                    self.describe(changed, data, original)

    def test_every_descriptor_setup_teardown_and_vertex_byte_is_guarded(self):
        code, original = self.source()
        for address, raw in embedded.DATA_SPANS:
            for delta in range(len(raw)):
                data = bytearray(original)
                data[address - self.data_base + delta] ^= 1
                with self.subTest(address=hex(address), delta=delta), self.assertRaisesRegex(ValueError, 'data changed'):
                    self.describe(code, data)

    def test_out_of_image_sources_and_changed_instruction_construction_fail(self):
        code, data = self.source()
        with self.assertRaises(ValueError):
            self.describe(code[:-0x200], data, code)
        with self.assertRaises(ValueError):
            self.describe(code, data[:0x100])
        changed = bytearray(code)
        struct.pack_into('>I', changed, 0x15187CCC-self.code_base, 0x35EF4008)  # Wrong ORI register.
        with self.assertRaisesRegex(ValueError, 'immediate construction'):
            self.describe(changed, data)

    def test_native_decoder_independently_agrees_with_vertex_and_triangle_order(self):
        code, data = self.source()
        manifest = self.describe(code, data)
        saved_code, saved_data = bytes(code), bytes(data)
        # Feed the exact source vertices and independently specified F3DEX2
        # command bytes through the existing ordinary-model decoder.
        dl = bytes.fromhex('0100400801000000050002040000000005000206000000000500040600000000df00000000000000')
        vertices = data[0x8008D538-self.data_base:0x8008D578-self.data_base]
        header = struct.pack('>10I', 0x68, len(dl), 0, 0, 0, 0, 0, 0, 0, 0x80000000)
        decoded = models.parse_model_geometry(header + vertices + dl)
        self.assertEqual([list(f) for f in decoded.faces], manifest['triangles'])
        self.assertEqual([(v.x, v.y, v.z) for v in decoded.vertices],
                         [tuple(v['position']) for v in manifest['vertices']])
        self.assertEqual([v.color for v in decoded.vertices],
                         [tuple(v['rgba_u8']) for v in manifest['vertices']])
        self.assertEqual([(v.flag, v.s, v.t) for v in decoded.vertices],
                         [(v['flag'], *v['st_s16']) for v in manifest['vertices']])
        self.assertEqual(saved_code, code)
        self.assertEqual(saved_data, data)

    def test_gltf_and_packed_glb_preserve_source_bytes_and_do_not_assign_native_material(self):
        code, data = self.source()
        manifest = self.describe(code, data)
        files = embedded.geometry_files(manifest)
        self.assertEqual(data[0x8008D538-self.data_base:0x8008D578-self.data_base],
                         files['source/vertices-8008d538.bin'])
        gltf_name = 'geometry/' + embedded.NAME + '.gltf'
        document = json.loads(files[gltf_name])
        binary = files['geometry/' + embedded.NAME + '.bin']
        self.assertEqual([(-625.0, 0.0, 0.0), (625.0, 31.0, 0.0),
                          (625.0, -31.0, 31.0), (625.0, -31.0, -31.0)],
                         list(struct.iter_unpack('<3f', binary[:48])))
        self.assertEqual(bytes.fromhex('ffffff10ffffffffffffffffffffffff'), binary[48:64])
        self.assertEqual((0, 1, 2, 0, 1, 3, 0, 2, 3), struct.unpack('<9H', binary[64:82]))
        self.assertEqual({'bufferView': 1, 'componentType': 5121, 'count': 4,
                          'type': 'VEC4', 'normalized': True}, document['accessors'][1])
        primitive = document['meshes'][0]['primitives'][0]
        self.assertNotIn('material', primitive)
        self.assertEqual({'POSITION', 'COLOR_0'}, set(primitive['attributes']))
        for key in ('materials', 'textures', 'images', 'animations', 'skins'):
            self.assertNotIn(key, document)
        self.assertEqual({'mesh', 'name'}, set(document['nodes'][0]))
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            for name, content in files.items():
                (root / name).parent.mkdir(parents=True, exist_ok=True)
                (root / name).write_bytes(content)
            packed, _ = pack_glb(root / gltf_name)
            wrapped, wrapped_binary = read_glb(packed)
            self.assertEqual(binary, wrapped_binary)
            self.assertEqual(document['meshes'], wrapped['meshes'])
            self.assertEqual(document['accessors'], wrapped['accessors'])

    def test_export_refuses_overwrite_and_verify_detects_tampering_without_rewriting(self):
        code, data = self.source()
        manifest = self.describe(code, data)
        files = embedded.geometry_files(manifest)
        files['manifest.json'] = (json.dumps(manifest) + '\n').encode()
        with tempfile.TemporaryDirectory() as tmp, patch.object(embedded, 'build_export', return_value=(manifest, files)):
            root = Path(tmp) / 'embedded'
            self.assertEqual(manifest, embedded.export(root))
            self.assertEqual(manifest, embedded.export(root, verify=True))
            with self.assertRaises(FileExistsError):
                embedded.export(root)
            for name, raw in files.items():
                changed = raw + b'X'
                (root / name).write_bytes(changed)
                with self.subTest(file=name), self.assertRaisesRegex(ValueError, 'differs from ROM'):
                    embedded.export(root, verify=True)
                self.assertEqual(changed, (root / name).read_bytes())
                (root / name).write_bytes(raw)
            (root / 'manifest.json').unlink()
            with self.assertRaises(FileNotFoundError):
                embedded.export(root, verify=True)
            self.assertFalse((root / 'manifest.json').exists())


class EmbeddedType08Tests(unittest.TestCase):
    code_base = 0x15160000
    data_base = 0x80087000

    def source(self):
        code = bytearray(0x1517ABB0 - self.code_base)
        for address, word in {0x1517A618: 0x3C098009, 0x1517A61C: 0x2529CDF0,
                              0x1517A620: 0x3C0ADE00, 0x1517A624: 0xAC4A0000,
                              0x1517A628: 0xAC490004}.items():
            struct.pack_into('>I', code, address - self.code_base, word)
        data = bytearray(0x9700)
        for address, raw in embedded.TYPE08_DATA:
            data[address - self.data_base:address - self.data_base + len(raw)] = raw
        return code, data

    def describe(self, code, data, original=None):
        original = code if original is None else original
        pins = [(a, n, hashlib.sha1(original[a-self.code_base:a-self.code_base+n]).hexdigest())
                for a, n, _ in embedded.TYPE08_CONSUMERS]
        with patch.object(embedded, 'TYPE08_CONSUMERS', pins):
            return embedded.describe_type08_geometry(code, self.code_base, data, self.data_base)

    def test_complete_dispatch_and_source_family_spans_reject_mutation(self):
        original, data = self.source()
        for address, size, _ in embedded.TYPE08_CONSUMERS:
            for delta in (0, size // 2, size - 1):
                changed = bytearray(original)
                changed[address - self.code_base + delta] ^= 1
                with self.subTest(address=hex(address), delta=delta), self.assertRaisesRegex(ValueError, 'consumer changed'):
                    self.describe(changed, data, original)

    def test_every_source_dispatch_setup_selector_and_list_byte_is_guarded(self):
        code, original = self.source()
        for address, raw in embedded.TYPE08_DATA:
            for delta in range(len(raw)):
                data = bytearray(original)
                data[address - self.data_base + delta] ^= 1
                with self.subTest(address=hex(address + delta)), self.assertRaisesRegex(ValueError, 'data changed'):
                    self.describe(code, data)

    def test_bounds_and_actual_list_submission_fail_closed(self):
        code, data = self.source()
        with self.assertRaises(ValueError):
            self.describe(code[:-4], data, code)
        with self.assertRaises(ValueError):
            self.describe(code, data[:0x100])
        for address, word in ((0x1517A61C, 0x2528CDF0), (0x1517A624, 0xAC4B0000),
                              (0x1517A628, 0xAC4A0004)):
            changed = bytearray(code)
            struct.pack_into('>I', changed, address - self.code_base, word)
            # Repin the synthetic fixture so explicit instruction-flow guards
            # are checked independently of complete-span mutation detection.
            with self.subTest(address=hex(address)), self.assertRaises(ValueError):
                self.describe(changed, data)

    def test_native_decoder_independently_agrees_with_all_vertex_fields(self):
        code, data = self.source()
        manifest = self.describe(code, data)
        commands = bytes.fromhex('0100600c01000000050002040000000005000602000000000508020600000000050a080600000000df00000000000000')
        header = struct.pack('>10I', 136, 48, 0, 0, 0, 0, 0, 0, 0, 0x80000000)
        decoded = models.parse_model_geometry(header + embedded.TYPE08_VERTICES + commands)
        expected = [[0, 1, 2], [0, 3, 1], [4, 1, 3], [5, 4, 3]]
        self.assertEqual(expected, manifest['triangles'])
        self.assertEqual(expected, [list(face) for face in decoded.faces])
        self.assertEqual([(7, 4, 0), (-7, 4, 0), (0, 1, 3), (7, 14, 0), (-7, 14, 0), (0, 21, 4)],
                         [(v.x, v.y, v.z) for v in decoded.vertices])
        self.assertEqual([(254, 254, 254, 255)] * 6, [v.color for v in decoded.vertices])
        self.assertEqual([(9234, 8351), (8200, 8334), (8720, 8107), (9202, 9040), (8213, 9024), (8698, 9694)],
                         [(v.s, v.t) for v in decoded.vertices])
        self.assertEqual([(v.flag, v.s, v.t) for v in decoded.vertices],
                         [(v['flag'], *v['st_s16']) for v in manifest['vertices']])

    def test_packed_geometry_keeps_native_bytes_without_material_or_transforms(self):
        code, data = self.source()
        files = embedded.type08_geometry_files(self.describe(code, data))
        name = 'geometry/' + embedded.TYPE08_NAME
        doc = json.loads(files[name + '.gltf'])
        binary = files[name + '.bin']
        self.assertEqual(embedded.TYPE08_VERTICES, files['source/vertices-8008cd90.bin'])
        self.assertEqual(embedded.TYPE08_LIST, files['source/list-8008cdf0.bin'])
        self.assertEqual(bytes.fromhex('fefefeff') * 6, binary[72:96])
        self.assertEqual((0, 1, 2, 0, 3, 1, 4, 1, 3, 5, 4, 3), struct.unpack('<12H', binary[96:120]))
        self.assertEqual({'mesh', 'name'}, set(doc['nodes'][0]))
        self.assertEqual({'POSITION', 'COLOR_0'}, set(doc['meshes'][0]['primitives'][0]['attributes']))
        self.assertNotIn('material', doc['meshes'][0]['primitives'][0])
        for key in ('materials', 'textures', 'images', 'animations', 'skins'):
            self.assertNotIn(key, doc)
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            for path, content in files.items():
                (root / path).parent.mkdir(parents=True, exist_ok=True)
                (root / path).write_bytes(content)
            packed, _ = pack_glb(root / (name + '.gltf'))
            wrapped, wrapped_binary = read_glb(packed)
            self.assertEqual(binary, wrapped_binary)
            self.assertEqual(doc['meshes'], wrapped['meshes'])
            self.assertEqual(doc['accessors'], wrapped['accessors'])

    def test_type08_overwrite_and_tamper_guards(self):
        code, data = self.source()
        manifest = self.describe(code, data)
        files = embedded.type08_geometry_files(manifest)
        files['manifest.json'] = json.dumps(manifest).encode()
        with tempfile.TemporaryDirectory() as tmp, patch.object(embedded, 'build_export', return_value=(manifest, files)) as build:
            root = Path(tmp) / 'type08'
            embedded.export(root, primitive='type08')
            build.assert_called_with(None, primitive='type08')
            embedded.export(root, primitive='type08', verify=True)
            with self.assertRaises(FileExistsError):
                embedded.export(root, primitive='type08')
            source = root / 'source/list-8008cdf0.bin'
            source.write_bytes(source.read_bytes() + b'X')
            with self.assertRaisesRegex(ValueError, 'differs from ROM'):
                embedded.export(root, primitive='type08', verify=True)
            self.assertEqual(embedded.TYPE08_LIST + b'X', source.read_bytes())

    def test_cli_defaults_preserve_type06_and_select_separate_type08_output(self):
        result = {'vertex_count': 6, 'triangle_count': 4}
        with patch.object(embedded, 'export', return_value=result) as export:
            embedded.main(['--verify'])
            export.assert_called_once_with((models.ROOT / 'build/assets/models/embedded-geometry').resolve(),
                                           None, verify=True, primitive='type06')
        with patch.object(embedded, 'export', return_value=result) as export:
            embedded.main(['--primitive', 'type08', '--verify'])
            export.assert_called_once_with((models.ROOT / 'build/assets/models/embedded-geometry-type08').resolve(),
                                           None, verify=True, primitive='type08')
        with self.assertRaisesRegex(ValueError, 'unsupported embedded primitive'):
            embedded.build_export(primitive='type09')


if __name__ == '__main__':
    unittest.main()
