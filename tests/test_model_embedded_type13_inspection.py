"""Source, selected cached-ST and publication guards for type13 inspection."""
import copy
import ast
import json
from pathlib import Path
import subprocess
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

from scripts import model_embedded_type13_inspection as effect


class Type13InspectionTests(unittest.TestCase):
    def test_saved_orthographic_camera_shifts_aspect_and_crop_are_guarded(self):
        # Import the pure signature function without importing Blender or
        # executing the worker. Exercise the original missed shift_x case and
        # every other ORTHO field used to determine the visible frame.
        worker=effect.ROOT/'scripts/model_embedded_type13_inspection_blender.py'
        parsed=ast.parse(worker.read_text())
        function=next(n for n in parsed.body if isinstance(n,ast.FunctionDef)and n.name=='framing_signature')
        namespace={};exec(compile(ast.Module(body=[function],type_ignores=[]),str(worker),'exec'),namespace)
        camera=SimpleNamespace(type='ORTHO',ortho_scale=470.,shift_x=0.,shift_y=0.,sensor_fit='AUTO',
                               clip_start=.1,clip_end=3000.,dof=SimpleNamespace(use_dof=False))
        render=SimpleNamespace(resolution_x=768,resolution_y=768,resolution_percentage=100,
             pixel_aspect_x=1.,pixel_aspect_y=1.,use_border=False,use_crop_to_border=False,
             border_min_x=0.,border_max_x=1.,border_min_y=0.,border_max_y=1.)
        scene=SimpleNamespace(camera=SimpleNamespace(data=camera),render=render)
        signature=namespace['framing_signature'];baseline=signature(scene)
        for block,changes in [(camera,{'shift_x':3.,'shift_y':3.,'ortho_scale':100.,'sensor_fit':'VERTICAL',
                                     'clip_start':100.,'clip_end':100.,'type':'PERSP'}),
                              (render,{'resolution_x':384,'resolution_y':384,'resolution_percentage':50,
                                       'pixel_aspect_x':2.,'pixel_aspect_y':2.,'use_border':True,
                                       'use_crop_to_border':True,'border_min_x':.25,'border_max_x':.75,
                                       'border_min_y':.25,'border_max_y':.75}),
                              (camera.dof,{'use_dof':True})]:
            for key,value in changes.items():
                with self.subTest(key=key):
                    original=getattr(block,key);setattr(block,key,value)
                    self.assertNotEqual(baseline,signature(scene));setattr(block,key,original)

    def test_counter_is_explicit_and_cached_st_is_not_scaled_twice(self):
        state=effect.selected_state()
        self.assertEqual([[8192,8192],[8192,8192],[8192,9216],[10240,8192],[10240,8192],[10240,9216]],
                         state['raw_modified_ST'])
        self.assertEqual([[0,1],[0,1],[0,0],[1,1],[1,1],[1,0]],state['cached_ST_uv'])
        for value in (0,4,6,10,True,5.0,'5'):
            with self.subTest(value=value),self.assertRaisesRegex(ValueError,'counter5'):effect.selected_state(value)

    def contract_fixture(self):
        base=0x80090548;data=bytearray(0x8009DEC0-base)
        data[:16]=bytes.fromhex('000010b3800905480100004000200401')
        data[0x8009DEB0-base:]=bytes.fromhex('03010000020100000101020202020203')
        code=b'full consumer span';payload=bytes(2048)
        return code,base,data,payload

    def call_contract(self,code,base,data,payload):
        original=effect.sha
        # Substitute only the synthetic pixel identity, retaining all layout/byte guards.
        digest=lambda value:('bb14d7224693e5aa0312bc85e0a86115894c3cf70d76d03f87c3a85a52237f22'
                             if value is payload else original(value))
        with patch.object(effect,'CONSUMERS',((0,len(code),original(code)),)),patch.object(effect,'sha',side_effect=digest):
            return effect.material_contract(code,0,data,base,payload)

    def test_loader_reconstruction_owns_i8_tile_and_has_no_tlut(self):
        code,base,data,payload=self.contract_fixture();commands=self.call_contract(code,base,data,payload)
        self.assertEqual(['E7000000','FD900000','F5900000','F3000000','F5881000','F2400400'],[c['command']for c in commands])
        self.assertEqual('073FF000',commands[3]['argument'])
        self.assertEqual('00094260',commands[4]['argument']);self.assertEqual('004FC47C',commands[5]['argument'])

    def test_descriptor_table_payload_and_consumer_mutations_are_rejected(self):
        code,base,data,payload=self.contract_fixture()
        for offset in (0,7,15,0x8009DEB1-base):
            changed=bytearray(data);changed[offset]^=1
            with self.subTest(offset=offset),self.assertRaises(ValueError):self.call_contract(code,base,changed,payload)
        with self.assertRaisesRegex(ValueError,'payload changed'):self.call_contract(code,base,data,payload[:-1])
        with patch.object(effect,'CONSUMERS',((0,len(code),effect.sha(code)),)),self.assertRaisesRegex(ValueError,'consumer changed'):
            effect.material_contract(b'X'+code[1:],0,data,base,payload)
        with patch.object(effect,'CONSUMERS',()),self.assertRaisesRegex(ValueError,'payload changed'):
            effect.material_contract(code,0,data,base,payload)

    def test_output_must_be_build_child_and_not_symlink(self):
        for path in (effect.ROOT,effect.ROOT/'build',effect.ROOT/'build/../scripts'):
            with self.assertRaisesRegex(ValueError,'child of build'):effect._checked_output(path)
        with tempfile.TemporaryDirectory()as temp:
            root=Path(temp);(root/'build').mkdir();(root/'build/real').mkdir();(root/'build/link').symlink_to(root/'build/real')
            with patch.object(effect,'ROOT',root),self.assertRaisesRegex(ValueError,'symlink'):effect._checked_output(root/'build/link')

    def test_create_and_fresh_verify_are_distinct_and_existing_is_not_overwritten(self):
        with tempfile.TemporaryDirectory()as temp:
            root=Path(temp);out=root/'build/inspection';fixture=({'source-proof.json':b'fresh'}, {})
            with patch.object(effect,'ROOT',root),patch.object(effect,'build_files',return_value=fixture),patch.object(effect.subprocess,'run')as run:
                self.assertEqual(0,effect.main(['--output',str(out),'--blender','/custom/blender']))
                command=run.call_args.args[0];self.assertEqual('/custom/blender',command[0]);self.assertNotIn('--verify',command)
                self.assertIn('--disable-autoexec',command)
                calls=run.call_count
                with self.assertRaises(SystemExit):effect.main(['--output',str(out)])
                self.assertEqual(calls,run.call_count)
                self.assertEqual(0,effect.main(['--output',str(out),'--verify']))
                self.assertIn('--verify',run.call_args.args[0])
                self.assertEqual(b'fresh',(out/'source-proof.json').read_bytes())

    def test_stale_existing_or_worker_failure_preserves_files(self):
        with tempfile.TemporaryDirectory()as temp:
            root=Path(temp);out=root/'build/inspection';out.mkdir(parents=True);path=out/'source-proof.json';path.write_bytes(b'stale')
            with patch.object(effect,'ROOT',root),patch.object(effect,'build_files',return_value=({'source-proof.json':b'fresh'},{})), \
                    patch.object(effect.subprocess,'run')as run:
                with self.assertRaises(SystemExit):effect.main(['--output',str(out),'--verify'])
                run.assert_not_called();self.assertEqual(b'stale',path.read_bytes())
                path.write_bytes(b'fresh');run.side_effect=subprocess.CalledProcessError(1,['blender'])
                with self.assertRaises(SystemExit):effect.main(['--output',str(out),'--verify'])
                self.assertEqual(b'fresh',path.read_bytes())

    def test_cli_rechecks_source_after_blender(self):
        with tempfile.TemporaryDirectory()as temp:
            root=Path(temp);out=root/'build/inspection'
            with patch.object(effect,'ROOT',root),patch.object(effect,'build_files',side_effect=[({'source-proof.json':b'before'},{}),({'source-proof.json':b'after'}, {})]), \
                    patch.object(effect.subprocess,'run'):
                with self.assertRaises(SystemExit):effect.main(['--output',str(out)])
                self.assertEqual(b'before',(out/'source-proof.json').read_bytes())

    def artifact_fixture(self,root):
        out=root/'build/inspection';out.mkdir(parents=True)
        files={'source-proof.json':b'source'}
        proof={'source_gltf_sha256':'source-hash','source_glb_sha256':'packed-source-hash','source_fingerprint':{'gltf_sha256':'source-hash'}}
        artifact={'blend_file':effect.BLEND,'blend_sha256':effect.sha(b'BLENDER'),
                  'scope':effect.SCOPE,'inspection_state':effect.STATE,'source_proof_sha256':effect.sha(b'source'),
                  'source_gltf_sha256':'source-hash','renders':{'three-quarter.png':effect.sha(b'front'),'rear.png':effect.sha(b'rear')}}
        contents={effect.BLEND:b'BLENDER','three-quarter.png':b'front','rear.png':b'rear','artifact.json':effect.encode(artifact)}
        for name,data in {**files,**contents}.items():(out/name).write_bytes(data)
        for name in ('model_embedded_type13_inspection','model_embedded_type13_inspection_blender','model_embedded_geometry',
                     'model_assets','model_preview_evidence','texture_native','texture_assets'):
            path=root/'scripts'/(name+'.py');path.parent.mkdir(exist_ok=True);path.write_text('# source\n')
        return out,files,proof,artifact

    def test_snapshot_proof_binds_original_source_and_raw_tool_and_artifact_bytes(self):
        with tempfile.TemporaryDirectory()as temp:
            root=Path(temp).resolve();out,files,proof,_=self.artifact_fixture(root)
            with patch.object(effect,'ROOT',root),patch.object(effect,'build_files',return_value=(files,proof)):
                snapshot,contents,scope=effect._artifact_snapshot(out)
                self.assertEqual('embedded-type13-counter5',snapshot['kind']);self.assertEqual(5,snapshot['counter'])
                self.assertEqual(effect.SOURCE,snapshot['source']);self.assertEqual(proof['source_fingerprint'],snapshot['source_fingerprint'])
                self.assertIn('scripts/model_embedded_geometry.py',snapshot['tools']);self.assertEqual(effect.SCOPE,scope)
                self.assertEqual(b'BLENDER',contents[effect.BLEND])
                (root/'scripts/model_embedded_geometry.py').write_text('# changed\n')
                with self.assertRaisesRegex(ValueError,'before publication'):effect.inspection_artifact_current(out,snapshot)

    def test_coherent_scope_or_selected_state_audit_cannot_change_admission(self):
        with tempfile.TemporaryDirectory()as temp:
            root=Path(temp);out,files,proof,artifact=self.artifact_fixture(root)
            with patch.object(effect,'ROOT',root),patch.object(effect,'build_files',return_value=(files,proof)):
                for key,value in [('scope','native parity proven'),('inspection_state',{'counter':10}),('source_gltf_sha256','other-source')]:
                    changed=copy.deepcopy(artifact);changed[key]=value;(out/'artifact.json').write_bytes(effect.encode(changed))
                    with self.subTest(key=key),self.assertRaisesRegex(ValueError,'source/state changed'):effect._artifact_snapshot(out)

    def test_admission_requires_fresh_worker_and_stable_before_after(self):
        out=effect.ROOT/'build/test';contents={effect.BLEND:b'BLENDER','three-quarter.png':b'front'}
        snapshot=({'files':{'x':'before'}},contents,'selected state')
        with patch.object(effect,'_artifact_snapshot',return_value=snapshot),patch.object(effect.subprocess,'run',
                return_value=SimpleNamespace(returncode=0,stdout='',stderr=''))as run:
            artifact=effect.inspection_artifact(out);self.assertEqual(b'BLENDER',artifact['blend'])
            self.assertIn('--verify',run.call_args.args[0]);self.assertIn('--disable-autoexec',run.call_args.args[0])
        with patch.object(effect,'_artifact_snapshot',side_effect=[snapshot,({'files':{'x':'after'}},contents,'state')]), \
                patch.object(effect.subprocess,'run',return_value=SimpleNamespace(returncode=0,stdout='',stderr='')):
            with self.assertRaisesRegex(ValueError,'changed during verification'):effect.inspection_artifact(out)
        with patch.object(effect,'_artifact_snapshot',return_value=snapshot),patch.object(effect.subprocess,'run',
                return_value=SimpleNamespace(returncode=1,stdout='',stderr='changed shader')):
            with self.assertRaisesRegex(ValueError,'fresh Blender verification failed'):effect.inspection_artifact(out)


if __name__=='__main__':
    unittest.main()
