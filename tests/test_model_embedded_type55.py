"""Independent type55/85 source, display-list and packed-geometry boundaries."""
import copy
from contextlib import contextmanager
import hashlib
import json
import struct
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from scripts import model_assets as models, model_embedded_type55 as embedded
from scripts.model_inspection import pack_glb, read_glb


# Source values transcribed from the five distinct native Vtx records.
POSITIONS = (
    [(0,-127,-255),(0,25,0),(-22,-12,0),(22,-12,0),(0,51,255)],
    [(0,25,-255),(-22,-12,-255),(22,-12,-255),(0,0,255)],
    [(0,-127,-255),(0,25,0),(-22,-12,0),(22,-12,0),(0,51,255)],
    [(0,25,-255),(-22,-12,-255),(22,-12,-255),(0,0,255)],
    [(0,255,0),(255,0,0),(0,-255,0),(-255,0,0),(0,0,255),(0,0,-255)],
)
COLORS = (
    [(255,255,0,255),(200,200,0,255),(160,80,20,255),(100,130,18,255),(128,64,0,255)],
    [(200,170,20,255),(128,32,8,255),(100,100,0,255),(128,64,0,255)],
    [(252,82,5,255),(254,141,48,255),(240,98,28,255),(249,91,20,255),(133,41,0,255)],
    [(248,88,20,255),(198,62,3,255),(254,143,61,255),(252,82,5,255)],
    [(255,0,0,64)] * 6,
)
FACES = (
    [(0,1,2),(0,2,3),(0,3,1),(1,4,2),(2,4,3),(3,4,1)],
    [(0,1,2),(0,3,1),(1,3,2),(2,3,0)],
    [(0,1,2),(0,2,3),(0,3,1),(1,4,2),(2,4,3),(3,4,1)],
    [(0,1,2),(0,3,1),(1,3,2),(2,3,0)],
    [(0,1,5),(0,5,3),(0,3,4),(0,4,1),(5,1,2),(3,5,2),(4,3,2),(1,4,2)],
)


class EmbeddedType55Tests(unittest.TestCase):
    code_base = 0x151580B0
    data_base = 0x8008ADD0

    def source(self):
        code = bytearray(0x15167A68 - self.code_base)
        # Raw US constructor and table-submission words, independent test fixture.
        words = {0x151580F0:0x24040055,0x151580F4:0x24040037,
                 0x15158128:0x26840010,0x1515812C:0x02002825,
                 0x15158130:0x0C008BB0,0x15158134:0x24060044,
                 0x15158550:0x3C0FDE00,0x15158554:0xAC8F0000,
                 0x15158558:0x92180016,0x1515855C:0x3C088009,
                 0x15158564:0x0018C880,0x15158568:0x01194021,
                 0x1515856C:0x8D08AFB8,0x15158574:0xAC880004}
        for address, word in words.items():
            struct.pack_into('>I',code,address-self.code_base,word)
        data = bytearray(0x800A6200-self.data_base)
        for address, raw in embedded.DATA_SPANS:
            data[address-self.data_base:address-self.data_base+len(raw)] = raw
        return code,data

    @contextmanager
    def admitted(self, code):
        pins = [(a,n,hashlib.sha1(code[a-self.code_base:a-self.code_base+n]).hexdigest())
                for a,n,_ in embedded.CONSUMERS]
        with patch.object(embedded,'CONSUMERS',pins):
            yield

    def describe(self, code, data, selector):
        return embedded.describe_geometry(code,self.code_base,data,self.data_base,selector)

    def test_pointer_table_order_and_distinct_color_variants(self):
        code,data = self.source()
        with self.admitted(code):
            manifests = [self.describe(code,data,i) for i in range(5)]
        self.assertEqual(['0x8008AE60','0x8008AEA8','0x8008AF38','0x8008AF80','0x8008AEE0'],
                         [m['source_list_address'] for m in manifests])
        self.assertEqual([6,4,6,4,8],[m['triangle_count'] for m in manifests])
        self.assertEqual(5,len({embedded.name(i) for i in range(5)}))
        for selector,manifest in enumerate(manifests):
            self.assertEqual(POSITIONS[selector],[tuple(v['position']) for v in manifest['vertices']])
            self.assertEqual(COLORS[selector],[tuple(v['rgba_u8']) for v in manifest['vertices']])
            self.assertEqual(FACES[selector],[tuple(f) for f in manifest['triangles']])
        for a,b in ((0,2),(1,3)):
            self.assertEqual(POSITIONS[a],POSITIONS[b])
            self.assertEqual(FACES[a],FACES[b])
            self.assertNotEqual(manifests[a]['vertex_bytes_sha1'],manifests[b]['vertex_bytes_sha1'])

    def test_independent_f3dex2_parser_matches_every_native_field_and_face(self):
        code,data = self.source()
        with self.admitted(code):
            for selector in range(5):
                manifest = self.describe(code,data,selector)
                files = embedded.geometry_files(manifest)
                source = next(value for key,value in files.items() if key.startswith('source/vertices-'))
                display = bytearray(next(value for key,value in files.items() if key.startswith('source/display-list-')))
                struct.pack_into('>I',display,12,0x01000000)
                model = models.parse_model_geometry(struct.pack('>10I',40+len(source),len(display),0,0,0,0,0,0,0,0x80000000)+source+display)
                with self.subTest(selector=selector):
                    self.assertEqual(POSITIONS[selector],[(v.x,v.y,v.z) for v in model.vertices])
                    self.assertEqual(COLORS[selector],[tuple(v.color) for v in model.vertices])
                    self.assertEqual([(0,0,0)]*len(POSITIONS[selector]),[(v.flag,v.s,v.t) for v in model.vertices])
                    self.assertEqual(FACES[selector],[tuple(f) for f in model.faces])
                    expected_raw = b''.join(struct.pack('>hhhHhhBBBB',*xyz,0,0,0,*rgba)
                                            for xyz,rgba in zip(POSITIONS[selector],COLORS[selector]))
                    self.assertEqual(expected_raw,source)

    def test_all_consumer_spans_and_each_data_byte_are_guarded(self):
        code,data = self.source()
        with self.admitted(code):
            for address,size,_ in embedded.CONSUMERS:
                for offset in (0,size//2,size-1):
                    changed = bytearray(code); changed[address-self.code_base+offset] ^= 1
                    with self.subTest(code=hex(address+offset)), self.assertRaisesRegex(ValueError,'consumer changed'):
                        self.describe(changed,data,0)
            for address,source in embedded.DATA_SPANS:
                for offset in range(len(source)):
                    changed = bytearray(data); changed[address-self.data_base+offset] ^= 1
                    with self.subTest(data=hex(address+offset)), self.assertRaisesRegex(ValueError,'data changed'):
                        self.describe(code,changed,0)

    def test_bounds_and_constructor_submission_guards(self):
        code,data = self.source()
        with self.admitted(code):
            for changed_code,changed_data in ((code[:-4],data),(code,data[:32])):
                with self.assertRaises(ValueError):
                    self.describe(changed_code,changed_data,0)
        for address,word in ((0x15158134,0x24060040),(0x15158558,0x92180017),
                             (0x1515856C,0x8D08AFBC),(0x15158574,0xAC890004)):
            changed = bytearray(code);struct.pack_into('>I',changed,address-self.code_base,word)
            with self.admitted(changed), self.subTest(address=hex(address)), self.assertRaisesRegex(ValueError,'submission changed'):
                self.describe(changed,data,0)

    def test_selector_rejects_bool_coercions_and_unproven_indices(self):
        code,data = self.source()
        for selector in (-1,5,255,True,False,'0',0.0,None):
            with self.subTest(selector=selector):
                with self.assertRaisesRegex(ValueError,'selector'):
                    embedded.name(selector)
                with self.assertRaisesRegex(ValueError,'selector'):
                    self.describe(code,data,selector)
                with self.assertRaisesRegex(ValueError,'selector'):
                    embedded.geometry_files({'selector':selector})

    def test_manifest_edits_cannot_change_source_or_claimed_contract(self):
        code,data = self.source()
        with self.admitted(code):
            original = self.describe(code,data,4)
            changes = [('triangle',lambda m:m['triangles'][0].__setitem__(0,2)),
                       ('RGBA',lambda m:m['vertices'][0]['rgba_u8'].__setitem__(3,255)),
                       ('ST',lambda m:m['vertices'][0]['st_s16'].__setitem__(0,1)),
                       ('source',lambda m:m.__setitem__('source_list_address','0x8008AE60')),
                       ('policy',lambda m:m['render_state'].__setitem__('material_status','native')),
                       ('scope',lambda m:m.__setitem__('scope','All selectors are active'))]
            for label,change in changes:
                altered = copy.deepcopy(original);change(altered)
                with self.subTest(field=label), self.assertRaisesRegex(ValueError,'manifest differs'):
                    embedded.geometry_files(altered)

    def test_packed_glb_bytes_preserve_source_without_invented_material_or_transform(self):
        code,data = self.source()
        with self.admitted(code), tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for selector in range(5):
                manifest = self.describe(code,data,selector)
                files = embedded.geometry_files(manifest)
                stem = 'geometry/'+embedded.name(selector)
                expected = b''.join(struct.pack('<3f',*xyz) for xyz in POSITIONS[selector])
                expected += bytes(channel for rgba in COLORS[selector] for channel in rgba)
                expected += struct.pack('<'+'H'*3*len(FACES[selector]),*(i for face in FACES[selector] for i in face))
                expected += b'\0'*(-len(expected)%4)
                self.assertEqual(expected,files[stem+'.bin'])
                document = json.loads(files[stem+'.gltf'])
                self.assertEqual({'mesh','name'},set(document['nodes'][0]))
                primitive = document['meshes'][0]['primitives'][0]
                self.assertEqual({'POSITION':0,'COLOR_0':1},primitive['attributes'])
                self.assertNotIn('material',primitive)
                for key in ('materials','textures','images','animations','skins','extensionsUsed'):
                    self.assertNotIn(key,document)
                self.assertEqual({'bufferView':1,'componentType':5121,'count':len(POSITIONS[selector]),'type':'VEC4','normalized':True},document['accessors'][1])
                for path,content in files.items():
                    (root/path).parent.mkdir(parents=True,exist_ok=True);(root/path).write_bytes(content)
                packed,_ = pack_glb(root/(stem+'.gltf'));wrapped,binary = read_glb(packed)
                self.assertEqual(expected,binary)
                self.assertEqual(document['meshes'],wrapped['meshes'])
                self.assertEqual(document['accessors'],wrapped['accessors'])


if __name__ == '__main__':
    unittest.main()
