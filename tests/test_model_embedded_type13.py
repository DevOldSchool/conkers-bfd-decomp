"""Independent geometry decoding and fail-closed type13 source admission."""
import hashlib
import json
import struct
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from scripts import model_assets as models, model_embedded_geometry as embedded
from scripts.model_inspection import pack_glb, read_glb


class EmbeddedType13Tests(unittest.TestCase):
    code_base = 0x15160000
    data_base = 0x8008B000

    def source(self):
        code = bytearray(0x15167A68 - self.code_base)
        # Literal instruction words transcribed independently from raw US ASM.
        words = {0x15166D9C: 0x3C0D8009, 0x15166DD0: 0x25ADB3E0,
                 0x15166DB0: 0x3C120100, 0x15166DBC: 0x3652600C,
                 0x15166DFC: 0xAC720000, 0x15166E00: 0xAC6D0004,
                 0x15166ECC: 0x3C19050A, 0x15166ED0: 0x37390600,
                 0x15166EE4: 0x3C0E0504, 0x15166EE8: 0x35CE0A00,
                 0x15166EFC: 0x3C0F0502, 0x15166F00: 0x35EF080A,
                 0x15166F14: 0x3C180502, 0x15166F18: 0x37180A04}
        for a, w in words.items():
            struct.pack_into('>I', code, a-self.code_base, w)
        data = bytearray(0x6000)
        for a, b in embedded.TYPE13_DATA:
            data[a-self.data_base:a-self.data_base+len(b)] = b
        return code, data

    def describe(self, code, data, original=None):
        original = code if original is None else original
        pins = [(a, n, hashlib.sha1(original[a-self.code_base:a-self.code_base+n]).hexdigest())
                for a, n, _ in embedded.TYPE13_CONSUMERS]
        with patch.object(embedded, 'TYPE13_CONSUMERS', pins):
            return embedded.describe_type13_geometry(code, self.code_base, data, self.data_base)

    def test_whole_consumer_spans_and_every_data_byte_reject_mutation(self):
        code, data = self.source()
        for a, n, _ in embedded.TYPE13_CONSUMERS:
            for offset in (0, n//2, n-1):
                changed = bytearray(code)
                changed[a-self.code_base+offset] ^= 1
                with self.subTest(code=hex(a+offset)), self.assertRaisesRegex(ValueError, 'consumer changed'):
                    self.describe(changed, data, code)
        for a, b in embedded.TYPE13_DATA:
            for offset in range(len(b)):
                changed = bytearray(data)
                changed[a-self.data_base+offset] ^= 1
                with self.subTest(data=hex(a+offset)), self.assertRaisesRegex(ValueError, 'data changed'):
                    self.describe(code, changed)

    def test_bounds_and_vertex_submission_fail_closed(self):
        code, data = self.source()
        with self.assertRaises(ValueError):
            self.describe(code[:-4], data, code)
        with self.assertRaises(ValueError):
            self.describe(code, data[:0x100])
        for a, w in ((0x15166DD0, 0x25ADB3F0), (0x15166DBC, 0x3652600E),
                     (0x15166DFC, 0xAC730000), (0x15166E00, 0xAC6E0004),
                     (0x15166ED0, 0x37390601)):
            changed = bytearray(code)
            struct.pack_into('>I', changed, a-self.code_base, w)
            # Repinning synthetic code tests the explicit load/triangle guards.
            with self.subTest(address=hex(a)), self.assertRaises(ValueError):
                self.describe(changed, data)

    def test_existing_model_decoder_agrees_with_all_source_fields_and_order(self):
        code, data = self.source()
        m = self.describe(code, data)
        dl = bytes.fromhex('0100600c01000000050a06000000000005040a00000000000502080a0000000005020a0400000000df00000000000000')
        decoded = models.parse_model_geometry(struct.pack('>10I', 136, 48, 0, 0, 0, 0, 0, 0, 0, 0x80000000)
                                              + embedded.TYPE13_VERTICES + dl)
        self.assertEqual([[5,3,0], [2,5,0], [1,4,5], [1,5,2]], m['triangles'])
        self.assertEqual(m['triangles'], [list(f) for f in decoded.faces])
        self.assertEqual([(-400,-34,-40), (-400,-34,40), (-400,34,0),
                          (0,-34,-40), (0,-34,40), (0,34,0)],
                         [(v.x,v.y,v.z) for v in decoded.vertices])
        self.assertEqual([(0,0,0,0,0,0,0)]*6, [(v.flag,v.s,v.t,*v.color) for v in decoded.vertices])
        self.assertEqual(3, m['runtime_instancing']['draw_loop_count'])
        self.assertIn('not synthesized', m['render_state']['dynamic_st']['policy'])

    def test_packed_geometry_preserves_zero_attributes_without_assigning_material(self):
        code, data = self.source()
        files = embedded.type13_geometry_files(self.describe(code, data))
        name = 'geometry/' + embedded.TYPE13_NAME
        doc = json.loads(files[name+'.gltf']); binary = files[name+'.bin']
        self.assertEqual(embedded.TYPE13_VERTICES, files['source/vertices-8008b3e0.bin'])
        self.assertEqual(bytes(24), binary[72:96])
        self.assertEqual((5,3,0,2,5,0,1,4,5,1,5,2), struct.unpack('<12H', binary[96:120]))
        self.assertEqual({'mesh','name'}, set(doc['nodes'][0]))
        self.assertNotIn('material', doc['meshes'][0]['primitives'][0])
        self.assertEqual({'POSITION','COLOR_0'}, set(doc['meshes'][0]['primitives'][0]['attributes']))
        for key in ('materials','textures','images','animations','skins'):
            self.assertNotIn(key, doc)
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for path, content in files.items():
                (root/path).parent.mkdir(parents=True, exist_ok=True)
                (root/path).write_bytes(content)
            packed, _ = pack_glb(root/(name+'.gltf')); wrapped, wrapped_binary = read_glb(packed)
            self.assertEqual(binary, wrapped_binary)
            self.assertEqual(doc['meshes'], wrapped['meshes'])
            self.assertEqual(doc['accessors'], wrapped['accessors'])

    def test_overwrite_and_tamper_rejection_do_not_rewrite_outputs(self):
        code, data = self.source(); m = self.describe(code, data)
        files = embedded.type13_geometry_files(m); files['manifest.json'] = json.dumps(m).encode()
        with tempfile.TemporaryDirectory() as temporary, patch.object(embedded, 'build_export', return_value=(m,files)):
            root = Path(temporary)/'type13'
            embedded.export(root, primitive='type13')
            embedded.export(root, primitive='type13', verify=True)
            with self.assertRaises(FileExistsError):
                embedded.export(root, primitive='type13')
            for name, original in files.items():
                changed = original+b'X'; (root/name).write_bytes(changed)
                with self.subTest(file=name), self.assertRaisesRegex(ValueError, 'differs from ROM'):
                    embedded.export(root, primitive='type13', verify=True)
                self.assertEqual(changed, (root/name).read_bytes())
                (root/name).write_bytes(original)

    def test_cli_type13_uses_separate_output(self):
        with patch.object(embedded, 'export', return_value={'vertex_count':6,'triangle_count':4}) as export:
            embedded.main(['--primitive','type13','--verify'])
            export.assert_called_once_with((models.ROOT/'build/assets/models/embedded-geometry-type13').resolve(),
                                           None, verify=True, primitive='type13')


if __name__ == '__main__':
    unittest.main()
