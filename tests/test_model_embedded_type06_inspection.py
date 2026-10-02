"""Source-state, exact material delta and no-write admission guards for type06."""
import copy
import json
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

from scripts import model_embedded_type06_inspection as effect


class Type06InspectionTests(unittest.TestCase):
    def test_only_proven_positive_lifetimes_and_elapsed_zero_are_admitted(self):
        self.assertEqual([255]*8,[effect.selected_alpha(n) for n in range(8,16)])
        for lifetime in (0,-1,7,16,True,8.0,'8'):
            with self.subTest(lifetime=lifetime), self.assertRaises(ValueError):
                effect.selected_alpha(lifetime)
        for elapsed in (-1,1,True,0.0,'0'):
            with self.subTest(elapsed=elapsed), self.assertRaises(ValueError):
                effect.selected_alpha(8,elapsed)

    def fixture_contract(self):
        base = min(effect.WORDS)
        code = bytearray(max(effect.WORDS)-base+4)
        for address,word in effect.WORDS.items():
            code[address-base:address-base+4] = word.to_bytes(4,'big')
        manifest = {'render_state':{'texture_enabled':False,'geometry_mode_clear_mask':'0x00020600',
                    'combine_mode':['0xFC323864','0xFF73FFFF'],'other_mode':['0xEF082CAF','0x00504A50']},
                    'vertices':[{'rgba_u8':rgba,'st_s16':[0,0]} for rgba in [[255,255,255,16]]+[[255]*4]*3]}
        return base,code,manifest

    def test_source_proof_retains_gate_and_all_eight_initial_lifetimes(self):
        base,code,manifest = self.fixture_contract()
        with patch.object(effect,'CALLER',(base,len(code),effect.sha(code))):
            contract = effect.material_contract(code,base,manifest)
        self.assertEqual(list(range(15,7,-1)),contract['lifetime_values'])
        self.assertEqual([255]*8,contract['primitive_alphas'])
        self.assertTrue(contract['not_a_first_draw'])
        self.assertIn('nonnull',contract['caller_gate'])

    def test_consumer_words_colors_st_and_combiner_mutations_fail_closed(self):
        base,code,manifest = self.fixture_contract()
        caller = (base,len(code),effect.sha(code))
        changed = bytearray(code); changed[0] ^= 1
        with patch.object(effect,'CALLER',caller), self.assertRaisesRegex(ValueError,'caller changed'):
            effect.material_contract(changed,base,manifest)
        # Even a coherently rebound whole-span fixture cannot bypass semantic pins.
        for address in effect.WORDS:
            changed = bytearray(code); changed[address-base+3] ^= 1
            with self.subTest(address=address), patch.object(effect,'CALLER',(base,len(changed),effect.sha(changed))), \
                    self.assertRaisesRegex(ValueError,'instruction changed'):
                effect.material_contract(changed,base,manifest)
        for change in ('alpha','ST','combiner','texture'):
            altered = copy.deepcopy(manifest)
            if change == 'alpha': altered['vertices'][0]['rgba_u8'][3] = 255
            if change == 'ST': altered['vertices'][0]['st_s16'][0] = 1
            if change == 'combiner': altered['render_state']['combine_mode'][1] = '0xFFFFFFFF'
            if change == 'texture': altered['render_state']['texture_enabled'] = True
            with self.subTest(change=change), patch.object(effect,'CALLER',caller), self.assertRaises(ValueError):
                effect.material_contract(code,base,altered)

    def original_document(self):
        return {'asset':{'version':'2.0'}, 'meshes':[{'primitives':[{
                    'attributes':{'POSITION':0,'COLOR_0':1},'indices':2,'mode':4}]}],
                'accessors':[{'bufferView':0},{'bufferView':1,'componentType':5121,'normalized':True},{'bufferView':2}],
                'bufferViews':[{'buffer':0,'byteLength':48},{'buffer':0,'byteOffset':48,'byteLength':16},
                               {'buffer':0,'byteOffset':64,'byteLength':18}],
                'buffers':[{'uri':'embedded-type06-8008d538.bin','byteLength':84}],
                'extras':{'source':'preserve all raw diagnostic provenance'}}

    def test_derived_document_only_adds_selected_material_and_relabels_raw_provenance(self):
        original = self.original_document(); before = copy.deepcopy(original)
        derived = effect.derived_document(original)
        self.assertEqual(before,original)
        material = derived.pop('materials')[0]
        self.assertEqual(['KHR_materials_unlit'],derived.pop('extensionsUsed'))
        self.assertEqual(0,derived['meshes'][0]['primitives'][0].pop('material'))
        extras = derived.pop('extras')
        self.assertEqual(original['extras'],extras['sourceDiagnosticExtras'])
        self.assertEqual('selected-elapsed0-unlit-vertex-rgba',extras['materialStatus'])
        self.assertEqual(effect.STATE,extras['inspection_state'])
        self.assertIn('An unlit BLEND material',extras['materialPolicy'])
        self.assertNotIn('No glTF material',extras['materialPolicy'])
        derived['extras'] = extras['sourceDiagnosticExtras']
        self.assertEqual(original,derived)
        self.assertEqual('BLEND',material['alphaMode']); self.assertTrue(material['doubleSided'])
        self.assertEqual([1]*4,material['pbrMetallicRoughness']['baseColorFactor'])
        self.assertEqual({'KHR_materials_unlit':{}},material['extensions'])
        self.assertEqual(effect.STATE,material['extras']['inspection_state'])
        self.assertIn('inherited native shading flags',material['extras']['scope'])

    def test_existing_material_or_new_geometry_attribute_is_not_silently_replaced(self):
        for change in ('material','attribute','mesh','extension'):
            doc = self.original_document()
            if change == 'material': doc['materials'] = [{'alphaMode':'MASK'}]
            if change == 'attribute': doc['meshes'][0]['primitives'][0]['attributes']['TEXCOORD_0'] = 3
            if change == 'mesh': doc['meshes'].append(copy.deepcopy(doc['meshes'][0]))
            if change == 'extension': doc['extensionsUsed'] = ['other']
            with self.subTest(change=change), self.assertRaises(ValueError): effect.derived_document(doc)

    def artifact_fixture(self,root):
        out = root/'build/inspection'; out.mkdir(parents=True)
        files = {'source-proof.json':b'source',effect.GLB:b'derived glb'}
        proof = {'source_gltf_sha256':'raw-gltf','source_glb_sha256':'raw-glb',
                 'source_fingerprint':{'gltf_sha256':'raw-gltf','dependencies_sha256':{'raw.bin':'raw-bin'}}}
        artifact = {'glb_file':effect.GLB,'derived_glb_sha256':effect.sha(files[effect.GLB]),
                    'scope':effect.SCOPE,'inspection_state':effect.STATE,'source_proof_sha256':effect.sha(b'source'),
                    'renders':{'three-quarter.png':effect.sha(b'front'),'rear.png':effect.sha(b'rear')}}
        contents = {'artifact.json':effect.encode(artifact),'three-quarter.png':b'front','rear.png':b'rear',
                    'validation.json':effect.encode({'valid':True})}
        for name,raw in {**files,**contents}.items(): (out/name).write_bytes(raw)
        for name in effect.TOOLS + tuple(effect.VALIDATOR+'/'+n for n in ('index.js','gltf_validator.dart.js','package.json')):
            path=root/name; path.parent.mkdir(parents=True,exist_ok=True); path.write_bytes(b'code')
        return out,files,proof,artifact

    def test_snapshot_distinguishes_raw_and_download_hashes_and_binds_tools(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp).resolve(); out,files,proof,_=self.artifact_fixture(root)
            with patch.object(effect,'ROOT',root), patch.object(effect,'build_files',return_value=(files,proof)):
                snapshot,contents,scope=effect._artifact_snapshot(out)
                self.assertEqual('raw-glb',snapshot['source_glb_sha256'])
                self.assertEqual(effect.sha(b'derived glb'),snapshot['derived_glb_sha256'])
                self.assertEqual(b'derived glb',contents[effect.GLB])
                self.assertEqual(effect.STATE,snapshot['inspection_state']); self.assertEqual(effect.SCOPE,scope)
                (root/effect.TOOLS[0]).write_bytes(b'changed')
                with self.assertRaisesRegex(ValueError,'before publication'):
                    effect.inspection_artifact_current(out,snapshot)

    def test_coherently_rehashed_glb_or_source_state_cannot_bypass_fresh_source(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp).resolve(); out,files,proof,artifact=self.artifact_fixture(root)
            with patch.object(effect,'ROOT',root), patch.object(effect,'build_files',return_value=(files,proof)):
                changed=copy.deepcopy(artifact); changed['derived_glb_sha256']=effect.sha(b'other glb')
                (out/effect.GLB).write_bytes(b'other glb'); (out/'artifact.json').write_bytes(effect.encode(changed))
                with self.assertRaisesRegex(ValueError,'derived GLB changed'): effect._artifact_snapshot(out)
                (out/effect.GLB).write_bytes(files[effect.GLB])
                for key,value in [('scope','native parity'),('inspection_state',{'elapsed':1})]:
                    changed=copy.deepcopy(artifact); changed[key]=value
                    (out/'artifact.json').write_bytes(effect.encode(changed))
                    with self.subTest(key=key),self.assertRaisesRegex(ValueError,'source/state changed'):
                        effect._artifact_snapshot(out)

    def test_output_and_source_symlinks_cannot_escape_build(self):
        for path in (effect.ROOT,effect.ROOT/'build',effect.ROOT/'build/../scripts'):
            with self.assertRaisesRegex(ValueError,'child of build'): effect._checked_output(path)
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp).resolve(); out,_,_,_=self.artifact_fixture(root)
            (out/'escape').symlink_to(root/effect.TOOLS[0])
            with self.assertRaisesRegex(ValueError,'escapes output'): effect._read(out,'escape')
            (root/'build/link').symlink_to(out)
            with patch.object(effect,'ROOT',root), self.assertRaisesRegex(ValueError,'symlink'):
                effect._checked_output(root/'build/link')

    def test_admission_requires_fresh_khronos_and_blender_and_stable_all_files(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp).resolve(); out,files,proof,_=self.artifact_fixture(root)
            with patch.object(effect,'ROOT',root), patch.object(effect,'build_files',return_value=(files,proof)), \
                    patch.object(effect,'validate_gltf',return_value={'valid':True}) as validate, \
                    patch.object(effect.subprocess,'run',return_value=subprocess.CompletedProcess([],0,'','')) as run:
                result=effect.inspection_artifact(out)
                self.assertEqual(b'derived glb',result['glb']); validate.assert_called_once_with(out)
                self.assertIn('--verify',run.call_args.args[0]); self.assertIn('--disable-autoexec',run.call_args.args[0])
                before={n:p.read_bytes() for n,p in ((p.name,p) for p in out.iterdir())}
                run.return_value=subprocess.CompletedProcess([],1,'','bad material')
                with self.assertRaisesRegex(ValueError,'Blender verification failed'): effect.inspection_artifact(out)
                self.assertEqual(before,{p.name:p.read_bytes() for p in out.iterdir()})
                validate.return_value={'valid':False}
                with self.assertRaisesRegex(ValueError,'Khronos result changed'): effect.inspection_artifact(out)

    def test_create_never_overwrites_and_verify_passes_only_after_fresh_validation(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp).resolve(); out=root/'build/new'; files={'source-proof.json':b'fresh'}
            with patch.object(effect,'ROOT',root), patch.object(effect,'build_files',return_value=(files,{})), \
                    patch.object(effect,'_artifact_snapshot',return_value=({'stable':True},{},effect.SCOPE)), \
                    patch.object(effect,'validate_gltf',return_value={'valid':True}) as validate, \
                    patch.object(effect.subprocess,'run') as run:
                effect.main(['--output',str(out),'--blender','/custom/blender'])
                self.assertEqual('/custom/blender',run.call_args.args[0][0]); self.assertNotIn('--verify',run.call_args.args[0])
                calls=run.call_count
                with self.assertRaises(SystemExit): effect.main(['--output',str(out)])
                self.assertEqual(calls,run.call_count)
                effect.main(['--output',str(out),'--verify'])
                self.assertIn('--verify',run.call_args.args[0]); self.assertEqual(2,validate.call_count)
                self.assertEqual(b'fresh',(out/'source-proof.json').read_bytes())

    def test_stale_verify_fails_before_validator_or_worker_and_leaves_bytes(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp).resolve(); out,files,proof,_=self.artifact_fixture(root)
            (out/effect.GLB).write_bytes(b'tampered')
            with patch.object(effect,'ROOT',root), patch.object(effect,'build_files',return_value=(files,proof)), \
                    patch.object(effect,'validate_gltf') as validate, patch.object(effect.subprocess,'run') as run:
                with self.assertRaises(SystemExit): effect.main(['--output',str(out),'--verify'])
                validate.assert_not_called(); run.assert_not_called()
                self.assertEqual(b'tampered',(out/effect.GLB).read_bytes())


if __name__ == '__main__':
    unittest.main()
