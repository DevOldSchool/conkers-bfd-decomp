"""Synthetic native containers, real parser/CI8 decoder; no private ROM fixture."""
import copy
import hashlib
import json
import struct
import unittest
from contextlib import ExitStack
from dataclasses import replace
from unittest.mock import patch
from scripts import model_assets as models
try:
    from scripts import model_special_attachment_materials as special
except ImportError:
    import model_special_attachment_materials as special


def fixture():
    vertices=b''.join(struct.pack('>hhhHhh4B',x,y,0,127,s,t,255,255,255,255)
                      for x,y,s,t in ((0,0,0,0),(10,0,1024,0),(0,10,0,1024)))
    table=24+len(vertices);joint=table+4;start=(joint+16+7)&~7
    commands=[(0xDA380003,0x03000000),(0x01003006,0x01000000),
              (0xD7000000,0xFFFFFFFF),(0x05000204,0)]
    for segment in (6,7,10,11):
        commands.extend(((0xD7000002,0xFFFFFFFF),(0xFCFF9880,0xF514FEFF),
            (0xFD100000,segment<<24),(0xF5100000,0x07000000),(0xF3000000,0x071FF000),
            (0xFD100000,(segment<<24)|1024),(0xF5000100,0x06000000),(0xF0000000,0x063FC000),
            (0xF5080800,0x00014050),(0xF2002002,0x0007E07E),(0x05000204,0)))
    commands.append((0xDF000000,0))
    raw=bytearray(start+len(commands)*8)
    struct.pack_into('>6I',raw,0,table,4,joint,16,0,0x80000000)
    raw[24:table]=vertices;struct.pack_into('>I',raw,table,start)
    struct.pack_into('>bBBB3f',raw,joint,-1,0,0,0,2,3,4)
    for i,pair in enumerate(commands):struct.pack_into('>II',raw,start+i*8,*pair)
    geometry,native=models.parse_attachment_model(bytes(raw),models.parse_model_geometry)
    payloads={flat:bytes(range(256))*4+struct.pack('>H',colour)*256
              for flat,colour in ((1937,0xF801),(1942,0x07C1),(1946,0x003F),(3649,0xFFFF),(3657,0x8421))}
    spec={'bytes':len(raw),'sha1':hashlib.sha1(raw).hexdigest(),'faces':5,'vertices':3,'joints':1,'runs':5}
    runs=tuple((i,i,1,seg,1024,(32,32,2,1)) for i,seg in enumerate((6,7,10,11),1))
    return bytes(raw),geometry,native,payloads,spec,runs


class SpecialAttachmentMaterialsTests(unittest.TestCase):
    def setUp(self):
        self.raw,self.geometry,self.native,self.payloads,spec,runs=fixture()
        self.context=special.model_context(185)
        self.patches=ExitStack();self.addCleanup(self.patches.close)
        self.patches.enter_context(patch.object(special,'MODELS',{185:spec}))
        self.patches.enter_context(patch.object(special,'RUNS',{185:runs}))
        self.patches.enter_context(patch.object(special,'PAYLOADS',
            {k:(len(v),hashlib.sha1(v).hexdigest()) for k,v in self.payloads.items()}))

    def apply(self,**changes):
        args={'geometry':self.geometry,'model_bytes':self.raw,'context':self.context,'payloads':self.payloads}
        args.update(changes);return special.apply_preview_geometry(**args)

    def code_fixture(self):
        base=min(a for a,_,_ in special.CONSUMERS)
        code=bytearray(max(a+n for a,n,_ in special.CONSUMERS)-base)
        db=min(a for a,_ in special.DATA)
        data=bytearray(max(a+len(bytes.fromhex(h)) for a,h in special.DATA)-db)
        for a,h in special.DATA:data[a-db:a-db+len(bytes.fromhex(h))]=bytes.fromhex(h)
        pins=tuple((a,n,hashlib.sha1(code[a-base:a-base+n]).hexdigest()) for a,n,_ in special.CONSUMERS)
        return code,base,data,db,pins

    def test_every_consumer_body_is_pinned(self):
        code,base,data,db,pins=self.code_fixture()
        with patch.object(special,'CONSUMERS',pins):
            special.material_context(code,base,data,db)
            for address,size,_ in pins:
                bad=bytearray(code);bad[address-base+size-1]^=1
                with self.subTest(address=hex(address)),self.assertRaisesRegex(ValueError,'consumer changed'):
                    special.material_context(bad,base,data,db)

    def test_dispatch_descriptor_pointer_and_phase_table_are_pinned(self):
        code,base,data,db,pins=self.code_fixture()
        with patch.object(special,'CONSUMERS',pins):
            for address,text in special.DATA:
                for offset in (0,len(bytes.fromhex(text))-1):
                    bad=bytearray(data);bad[address-db+offset]^=1
                    with self.subTest(address=hex(address),offset=offset),self.assertRaisesRegex(ValueError,'table changed'):
                        special.material_context(code,base,bad,db)

    def test_model_identity_and_phase_mutations_fail(self):
        for key,value in (('bank',1),('entry',165),('segment',1),('renderer','func_unknown'),
                          ('selected_phase',1),('selected_phase',False),('scope','overclaim')):
            bad={**self.context,key:value}
            # bool compares equal to zero: reject it explicitly at the interface.
            with self.subTest(key=key,value=value),self.assertRaises(ValueError):self.apply(context=bad)

    def test_raw_source_and_same_count_geometry_mutations_fail(self):
        bad=bytearray(self.raw);bad[24]^=1
        with self.assertRaisesRegex(ValueError,'source model'):self.apply(model_bytes=bytes(bad))
        for geometry in (replace(self.geometry,vertices=(replace(self.geometry.vertices[0],x=1),*self.geometry.vertices[1:])),
                         replace(self.geometry,faces=(tuple(reversed(self.geometry.faces[0])),*self.geometry.faces[1:])),
                         replace(self.geometry,material_runs=(replace(self.geometry.material_runs[0],face_count=9),*self.geometry.material_runs[1:]))):
            if geometry==self.geometry:continue
            with self.assertRaisesRegex(ValueError,'geometry changed'):self.apply(geometry=geometry)

    def test_each_selected_and_later_payload_must_be_present_and_exact(self):
        for flat in self.payloads:
            for missing in (True,False):
                bad=dict(self.payloads)
                if missing:bad.pop(flat)
                else:bad[flat]=bytes([bad[flat][0]^1])+bad[flat][1:]
                with self.subTest(flat=flat,missing=missing),self.assertRaisesRegex(ValueError,'payload changed'):
                    self.apply(payloads=bad)

    def test_all_four_phases_decode_and_remain_correlated(self):
        result,proof=self.apply()
        expected=((1937,3649),(1937,3657),(1942,3657),(1946,3657))
        self.assertEqual([(v['bindings'][6],v['bindings'][10]) for v in proof['correlated_variants']],list(expected))
        self.assertEqual([len(v['runs']) for v in proof['correlated_variants']],[4]*4)
        self.assertTrue(all(len(r['png_sha1'])==40 for v in proof['correlated_variants'] for r in v['runs']))
        self.assertEqual([r.pixel.flat_index for r in result.material_runs[1:]],[1937,1937,3649,3649])
        self.assertEqual([r.pixel.segment for r in self.geometry.material_runs[1:]],[6,7,10,11])
        self.assertEqual(proof['affected_faces'],4)

    def test_only_material_bindings_change_and_native_geometry_encodes(self):
        result,proof=self.apply()
        self.assertIs(result.vertices,self.geometry.vertices)
        self.assertIs(result.faces,self.geometry.faces)
        self.assertIs(result.face_matrix_indices,self.geometry.face_matrix_indices)
        self.assertIs(result.material_runs[0],self.geometry.material_runs[0])
        for a,b in zip(self.geometry.material_runs[1:],result.material_runs[1:]):
            self.assertEqual(a,replace(b,pixel=a.pixel,palette=a.palette,texture_loads=a.texture_loads))
            for vertex in result.vertices:self.assertEqual(models.texture_coordinates(vertex,a),models.texture_coordinates(vertex,b))
        joints=tuple(self.native['joints'])
        self.assertEqual(models.validation_face_records(self.geometry,joints),models.validation_face_records(result,joints))
        gltf,binary=models.encode_gltf(185,0,result,bank_index=9,character_joints=joints)
        document=json.loads(gltf)
        self.assertTrue(binary);self.assertEqual(len(document['skins'][0]['joints']),1)
        self.assertIn(b'\nv ',models.encode_obj(185,0,result,bank_index=9))

    def test_equivalent_cli_dataclass_and_gltf_consumer_provenance(self):
        from dataclasses import fields, make_dataclass
        OtherGeometry = make_dataclass('OtherGeometry', [(f.name, object) for f in fields(self.geometry)])
        other = OtherGeometry(*(getattr(self.geometry, f.name) for f in fields(self.geometry)))
        mapped, proof = self.apply(geometry=other)
        self.assertEqual(self.geometry.faces, mapped.faces)
        gltf, _ = models.encode_gltf(185, 0, mapped, bank_index=9,
                                     character_joints=tuple(self.native['joints']))
        rows = [{'rom_special_attachment_material_state': proof} for _ in mapped.material_runs]
        document = json.loads(models.add_rom_texture_state_evidence(gltf, rows))
        serialized_proof = json.loads(json.dumps(proof))
        self.assertEqual(serialized_proof, document['extras']['romSpecialAttachmentMaterialState'])
        self.assertEqual('func_150911F4', document['extras']['attachmentColorState']['renderer'])
        self.assertEqual('stored-geometry-neutral-joints', document['extras']['attachmentMatrixState']['status'])
        self.assertNotIn('selector', document['extras']['attachmentMatrixState'])
        self.assertTrue(all(m['extras']['romSpecialAttachmentMaterialState'] == serialized_proof
                            for m in document['materials']))

    def test_skinned_specialized_materials_do_not_claim_character_renderer(self):
        context = special.model_context(165)
        proof = {'renderer': context['renderer'], 'scope': context['scope']}
        encoded, binary = models.encode_gltf(165, 0, self.geometry, bank_index=9,
            character_joints=tuple(self.native['joints']))
        before = json.loads(encoded)
        self.assertTrue(binary)
        self.assertGreater(len(before['materials']), 1)
        self.assertTrue(all('characterColorState' in m['extras'] for m in before['materials']))
        rows = [{} for _ in self.geometry.material_runs]
        rows[1]['rom_special_attachment_material_state'] = proof
        out = json.loads(models.add_rom_texture_state_evidence(encoded, rows))
        self.assertEqual('func_15157420', out['extras']['attachmentColorState']['renderer'])
        self.assertEqual('dynamic-colour-opacity-unresolved', out['extras']['attachmentColorState']['status'])
        self.assertEqual('stored-geometry-neutral-joints', out['extras']['attachmentMatrixState']['status'])
        self.assertNotIn('selector', out['extras']['attachmentMatrixState'])
        self.assertTrue(all('characterColorState' not in m['extras'] for m in out['materials']))
        self.assertEqual(proof, out['materials'][1]['extras']['romSpecialAttachmentMaterialState'])
        self.assertEqual(before['skins'], out['skins'])
        self.assertEqual(before['meshes'], out['meshes'])
        self.assertEqual(before['accessors'], out['accessors'])
        for old, new in zip(before['materials'], out['materials']):
            expected = {**old, 'extras': dict(old['extras'])}
            expected['extras'].pop('characterColorState')
            actual = {**new, 'extras': dict(new['extras'])}
            actual['extras'].pop('romSpecialAttachmentMaterialState', None)
            self.assertEqual(expected, actual)

    def test_ordinary_character_material_claims_are_unchanged(self):
        encoded, _ = models.encode_gltf(0, 0, self.geometry, bank_index=1,
            character_joints=tuple(self.native['joints']))
        rows = [{} for _ in self.geometry.material_runs]
        self.assertEqual(encoded, models.add_rom_texture_state_evidence(encoded, rows))
        rows[0]['rom_texture_state_consensus'] = {'scope': 'ordinary texture evidence'}
        out = json.loads(models.add_rom_texture_state_evidence(encoded, rows))
        self.assertTrue(all(m['extras']['characterColorState'] == models.CHARACTER_RUNTIME_COLOR_STATE
                            for m in out['materials']))

    def test_source_run_contract_still_rejects_mismatch_after_source_repin(self):
        # Change source segment bytes, re-pin only the synthetic source, and
        # prove the separately reviewed run contract still rejects the binding.
        bad=bytearray(self.raw);start=self.native['display_list_pointers'][0]
        for offset in range(start,len(bad),8):
            command,arg=struct.unpack_from('>II',bad,offset)
            if command==0xFD100000 and arg==0x06000000:
                struct.pack_into('>I',bad,offset+4,0x05000000);break
        geometry,_=models.parse_attachment_model(bytes(bad),models.parse_model_geometry)
        spec={**special.MODELS[185],'sha1':hashlib.sha1(bad).hexdigest()}
        with patch.object(special,'MODELS',{185:spec}),self.assertRaisesRegex(ValueError,'run source binding'):
            self.apply(geometry=geometry,model_bytes=bytes(bad))

    def test_counter_thresholds_and_input_types(self):
        self.assertEqual([special.phase_for_counter(x) for x in (0,91,479,480,959,960,1199,1200,65535)],[0,0,0,1,1,2,2,3,3])
        for bad in (-1,65536,True,1.0,None):
            with self.assertRaises(ValueError):special.phase_for_counter(bad)

    def test_capture_and_unrelated_context_preserve_source(self):
        self.assertEqual(self.apply(context=None),(self.geometry,None))
        self.assertEqual(self.apply(context={'entry':185}),(self.geometry,None))
        self.assertEqual(self.apply(runtime_materials={0:{'capture':True}}),(self.geometry,None))

if __name__=='__main__':unittest.main()
