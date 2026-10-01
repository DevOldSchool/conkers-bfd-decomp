"""ROM-consumer export tests with synthetic images and guarded source-document fixtures."""
import copy
import hashlib
import json
from pathlib import Path
import unittest
from unittest.mock import patch
from scripts import model_assets as models, model_haybot_rom_variants as variants


class HaybotVariantExportTests(unittest.TestCase):
    def fixture(self):
        evidence=copy.deepcopy(variants.contract())
        payloads={};pngs={};descriptors=[None]*18
        for selector in (15,16,17):
            info=evidence['variants'][str(selector)]
            payload=bytes([selector])*2048+bytes([selector,255])*16
            rows=bytes(payload[y*32+(x^(4 if y&1 else 0))] for y in range(64) for x in range(32))
            png=models.encode_indexed_png(rows+payload[2048:],'linear',64,64)
            info.update(sha256=hashlib.sha256(payload).hexdigest(),pixel_sha256=hashlib.sha256(payload[:2048]).hexdigest(),
                        palette_sha256=hashlib.sha256(payload[2048:]).hexdigest(),png_sha256=hashlib.sha256(png).hexdigest(),png_sha1=hashlib.sha1(png).hexdigest())
            payloads[info['flat']]=payload;pngs[selector]=png
            descriptors[selector]={'record_index':selector,'runtime_pointer_slot_initial_value':info['flat'],'flat_index':info['flat'],'width':64,'height':64}
        texture={'flat_index':3823,'file':variants.OLD_IMAGE,'png_sha1':evidence['variants']['15']['png_sha1'],
                 'source_family':'captured-haybot-ROM-decoded','width':64,'height':64,'format':2,'size':0,
                 'pixel_byte_offset':0,'palette_byte_offset':2048}
        runs=[{'status':'baseline','texture':None} for _ in range(17)]
        runs[16]={'status':'captured-haybot-selector15-inspection','captured_texture_preset':{'scope':'captured phase5'},'texture':texture}
        record={'bank_entry':75,'segment':0,'source_face_count':1226,'face_count':1226,'vertex_count':1625,
                'texture_coordinate_count':1625,'joint_count':45,'omitted_zero_area_face_count':0,
                'animation_clip_count':15,'animation_frame_count':291,'incompatible_animation_clip_count':0,
                'gltf_file':'geometry/0075-00.gltf','gltf_binary_file':'geometry/0075-00.bin',
                'bind_gltf_file':'geometry/0075-00-bind.gltf','bind_gltf_binary_file':'geometry/0075-00-bind.bin',
                'material_runs':runs}
        manifest={'selected_entries':[75],'model_count':1,'source_zero_area_faces_preserved':True,
                  'capture_evidence':variants.haybot.contract(),'capture_replayed_locally':False,
                  'capture_provenance':{'matrix_evidence':'captured task matrix conversion'},
                  'models':[record],'textures':[texture],
                  'status_run_counts':{'baseline':16,'captured-haybot-selector15-inspection':1},
                  'status_face_counts':{'baseline':1202,'captured-haybot-selector15-inspection':24}}
        document={'meshes':[{'primitives':[{'indices':0}]}], 'nodes':[{'name':f'joint{i}'} for i in range(45)],
                  'skins':[{'joints':list(range(45))}],'accessors':[{'count':1226*3,'source':'geometry-and-rig'}],
                  'bufferViews':[{'byteOffset':0,'byteLength':42}],'buffers':[{'uri':'0075-00.bin','byteLength':42}],
                  'extras':{'capturedTexturePreset':{'scope':'captured phase5'},'source':'ROM'},
                  'images':[{'uri':'../'+variants.OLD_IMAGE}], 'textures':[{'source':0,'sampler':0}],
                  'samplers':[{'magFilter':9729,'minFilter':9729}],
                  'materials':[{'extras':{'materialRun':16,'capturedTexturePreset':{'effective_material':'captured'}},
                                'pbrMetallicRoughness':{'baseColorTexture':{'index':0}}}],
                  'animations':[{'extras':{'sourceBank':2,'sourceEntry':75,'sourcePair':i,'sourceFrameCount':frames}}
                                for i,frames in enumerate(variants.haybot.FRAMES)]}
        bind=copy.deepcopy(document);bind.pop('animations');bind['buffers'][0]['uri']='0075-00-bind.bin'
        base={variants.OLD_IMAGE:pngs[15],record['gltf_file']:json.dumps(document).encode(),
              record['bind_gltf_file']:json.dumps(bind).encode(),record['gltf_binary_file']:b'source geometry uv rig and animation bytes',
              record['bind_gltf_binary_file']:b'source neutral geometry uv rig bytes',
              'manifest.json':json.dumps(manifest).encode(),'README.txt':b'capture matrix phase5 provenance'}
        return evidence,base,manifest,pngs,payloads,{'texture_descriptors':descriptors}

    def test_pinned_ROM_contract_and_canonical_preset(self):
        self.assertEqual('343edae4fab6b7b994c7f52fee124c7f1209ba8adaf75ce8ff425d900b9c2131', variants.CONTRACT_SHA256)
        self.assertEqual('haybot-rom-selector-variants', variants.PRESET)
        self.assertEqual(variants.CONTRACT_SHA256, hashlib.sha256(variants.CONTRACT_PATH.read_bytes()).hexdigest())
        self.assertEqual([15,16,17,17,16,15], [variants.selector_for_phase(i) for i in range(6)])

    def test_three_images_keep_exact_source_documents_and_binary_bytes(self):
        evidence,base,manifest,pngs,_,_=self.fixture()
        untouched=copy.deepcopy((base,manifest))
        with patch.object(variants,'contract',return_value=evidence):
            for selector,flat in ((15,3823),(16,3822),(17,3824)):
                files,output=variants.variant_files(base,manifest,selector,pngs[selector],evidence)
                model=output['models'][0];image=f'textures/haybot-rom-selector{selector}-flat{flat}.png'
                self.assertEqual(pngs[selector],files[image]);self.assertNotIn(variants.OLD_IMAGE,files)
                self.assertEqual((1226,45,15,291),(model['face_count'],model['joint_count'],model['animation_clip_count'],model['animation_frame_count']))
                for field,binary_field in (('gltf_file','gltf_binary_file'),('bind_gltf_file','bind_gltf_binary_file')):
                    before=json.loads(base[model[field]]);after=json.loads(files[model[field]])
                    for key in variants.common.PRESERVED_DOCUMENT_FIELDS:
                        self.assertEqual(before.get(key),after.get(key))
                    self.assertEqual(base[model[binary_field]],files[model[binary_field]])
                    self.assertEqual('../'+image,after['images'][0]['uri'])
                    self.assertEqual(flat,after['extras']['romConsumerTextureVariant']['flat'])
                    self.assertIsNone(after['extras']['romConsumerTextureVariant']['observed_phase'])
                    self.assertIsNone(after['extras']['romConsumerTextureVariant']['playback_timing'])
                self.assertEqual(image,model['material_runs'][16]['texture']['file'])
                self.assertEqual('rom-consumer-selector-inspection',model['material_runs'][16]['status'])
                self.assertTrue(output['rom_only'])
                self.assertEqual(24,output['status_face_counts']['rom-consumer-selector-inspection'])
                self.assertFalse(any(marker in data for name,data in files.items() if name.endswith(('.json','.gltf')) for marker in variants.CAPTURE_MARKERS))
                self.assertNotIn(b'captured phase5',files['README.txt'])
        self.assertEqual(untouched,(base,manifest))

    def test_build_uses_guarded_baseline_and_all_three_decoder_bindings(self):
        evidence,base,manifest,pngs,payloads,layout=self.fixture()
        geometry=object();draw=object()
        with patch.object(variants,'contract',return_value=evidence),\
             patch.object(variants.haybot,'build_files',return_value=(base,geometry,layout,draw,manifest)) as baseline,\
             patch.object(variants.models,'load_flat_asset_payloads',return_value=payloads):
            files,actual_geometry,actual_layout,actual_draw,records=variants.build_files(None,None)
        baseline.assert_called_once_with(None,None)
        self.assertIs(geometry,actual_geometry);self.assertIs(layout,actual_layout);self.assertIs(draw,actual_draw)
        self.assertEqual({15,16,17},set(records))
        for selector,flat in ((15,3823),(16,3822),(17,3824)):
            self.assertEqual(pngs[selector],files[f'selector{selector}/textures/haybot-rom-selector{selector}-flat{flat}.png'])

    def test_wrong_source_inventory_and_identity_cannot_be_relabelled(self):
        evidence,base,manifest,pngs,_,_=self.fixture()
        with patch.object(variants,'contract',return_value=evidence):
            for field,value in (('face_count',1225),('source_face_count',1225),('joint_count',44),('animation_clip_count',14),
                                ('animation_frame_count',290),('omitted_zero_area_face_count',1)):
                changed=copy.deepcopy(manifest);changed['models'][0][field]=value
                with self.subTest(field=field),self.assertRaises(ValueError):variants.variant_files(base,changed,15,pngs[15],evidence)
            for field in ('rom_sha1','model_sha256','updater_sha1'):
                changed=copy.deepcopy(evidence);changed[field]='0'*len(changed[field])
                with patch.object(variants,'contract',return_value=changed),self.subTest(identity=field),self.assertRaisesRegex(ValueError,'identities disagree'):
                    variants.guard_baseline(manifest,changed)

    def test_image_selector_clip_and_binding_mutations_fail_closed(self):
        evidence,base,manifest,pngs,_,_=self.fixture()
        with patch.object(variants,'contract',return_value=evidence):
            for selector in (True,15.0,14,18):
                with self.subTest(selector=selector),self.assertRaises(ValueError):variants.variant_files(base,manifest,selector,pngs[15],evidence)
            with self.assertRaises(ValueError):variants.variant_files(base,manifest,15,pngs[16],evidence)
            for mutation in ('missing_image','missing_primitive','wrong_texture_binding','wrong_frames','bind_animation'):
                changed=dict(base);field='bind_gltf_file' if mutation=='bind_animation' else 'gltf_file';name=manifest['models'][0][field]
                document=json.loads(changed[name])
                if mutation=='missing_image':document['images']=[]
                elif mutation=='missing_primitive':document['materials']=[]
                elif mutation=='wrong_texture_binding':
                    document['images'].append({'uri':'../textures/other.png'})
                    document['textures'][0]['source']=1
                elif mutation=='wrong_frames':document['animations'][0]['extras']['sourceFrameCount']=12
                else:document['animations']=[{}]
                changed[name]=json.dumps(document).encode()
                with self.subTest(mutation=mutation),self.assertRaises(ValueError):variants.variant_files(changed,manifest,15,pngs[15],evidence)

    def test_extra_capture_metadata_is_rejected(self):
        evidence,base,manifest,pngs,_,_=self.fixture()
        changed=dict(base);changed['unaccounted.json']=b'{"capture_evidence": {}}'
        with patch.object(variants,'contract',return_value=evidence),self.assertRaisesRegex(ValueError,'capture-specific'):
            variants.variant_files(changed,manifest,15,pngs[15],evidence)



from scripts import model_haybot_rom_variants as v, model_assets as m


class HaybotROMVariantTests(unittest.TestCase):
    def fixture(self,selector):
        e=v.contract();info=e['variants'][str(selector)];data=bytes(2080)
        info.update(sha256=hashlib.sha256(data).hexdigest(),pixel_sha256=hashlib.sha256(data[:2048]).hexdigest(),palette_sha256=hashlib.sha256(data[2048:]).hexdigest(),png_sha256=hashlib.sha256(m.encode_indexed_png(data,'linear',64,64)).hexdigest())
        descriptors=[None]*18;descriptors[selector]=dict(record_index=selector,runtime_pointer_slot_initial_value=info['flat'],flat_index=info['flat'],width=64,height=64)
        return e,data,{'texture_descriptors':descriptors}

    def test_guarded_phase_to_descriptor_cycle(self):
        self.assertEqual([15,16,17,17,16,15],[v.selector_for_phase(i) for i in range(6)])
        for phase in (-1,6,True,1.0,'1'):
            with self.assertRaises(ValueError):v.selector_for_phase(phase)

    def test_contract_and_three_distinct_bindings(self):
        e=v.contract();self.assertEqual([3823,3822,3824],[e['variants'][str(i)]['flat'] for i in (15,16,17)])
        with patch.object(Path,'read_bytes',return_value=b'{}'),self.assertRaises(ValueError):v.contract()

    def test_source_images_preserve_payload_alpha(self):
        for selector in (15,16,17):
            e,data,layout=self.fixture(selector)
            with patch.object(v,'contract',return_value=e):self.assertEqual(m.encode_indexed_png(data,'linear',64,64),v.decode_variant(selector,data,layout,e))

    def test_wrong_selector_descriptor_and_size_rejected(self):
        e,data,layout=self.fixture(16)
        with patch.object(v,'contract',return_value=e):
            for selector in (0,14,18,True,16.0):
                with self.assertRaises(ValueError):v.decode_variant(selector,data,layout,e)
            for field,value in [('flat_index',3839),('record_index',15),('width',32),('runtime_pointer_slot_initial_value',3823)]:
                changed=copy.deepcopy(layout);changed['texture_descriptors'][16][field]=value
                with self.assertRaises(ValueError):v.decode_variant(16,data,changed,e)
            for changed in (data[:-1],bytes([1])+data[1:],data[:-1]+b'\1'):
                with self.assertRaises(ValueError):v.decode_variant(16,changed,layout,e)

    def test_evidence_and_timeline_cannot_be_relabelled(self):
        e=v.contract();e['descriptor_cycle']=[15]*6
        with self.assertRaises(ValueError):v.decode_variant(15,bytes(2080),{},e)


if __name__ == '__main__':
    unittest.main()
