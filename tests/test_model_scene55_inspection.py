"""Bounded two-plane decoder, source mapping and publication admission guards."""
import copy
from dataclasses import replace
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch
import zlib

from scripts import model_scene55_inspection as scene


class Scene55Tests(unittest.TestCase):
    def texture_fixture(self):
        m=scene.models
        pixel=m.ModelTextureBinding(0xFD500000,737,0,load_command=(0xF3000000,0x073FF000))
        palette=m.ModelTextureBinding(0xFD100000,737,2,load_command=(0xF0000000,0x0603C000))
        tiles=((0,0xF5400800,0x00014060),(1,0xF5400880,0x01014060),
               (6,0xF5600100,0x06000000),(7,0xF5500000,0x07000000))
        run=m.ModelMaterialRun(0,38,True,pixel,palette,tiles[0][1:],tiles,None,
                              (0xD7000002,0xFFFFFFFF),(0xFC111404,0xFF13FFFF),
                              (0xEF18AC3F,0x0C184A50),None,
                              texture_loads=((pixel,tiles[3][1:]),(palette,tiles[2][1:])))
        payload=bytes((i*17+i//32)%256 for i in range(2048))+struct.pack('>16H',*[i*0x842+1 for i in range(16)])
        return run,payload

    def decode(self,run,payload):
        # Only the content-address gate is substituted for this synthetic layout.
        with patch.object(scene.hashlib,'sha1',return_value=SimpleNamespace(hexdigest=lambda:'6efffd09da18f157c1f2f77daf5f3f7f51873008')):
            return scene.decode_planes(run,payload)

    def test_second_plane_and_odd_row_swizzle_are_independent(self):
        run,payload=self.texture_fixture(); images=self.decode(run,payload)
        for tile,png in enumerate(images):
            at=8; chunks={}
            while at<len(png):
                length=int.from_bytes(png[at:at+4],'big'); key=png[at+4:at+8]
                chunks.setdefault(key,[]).append(png[at+8:at+8+length]); at+=length+12
            rows=zlib.decompress(b''.join(chunks[b'IDAT']))
            self.assertEqual(1056,len(rows))
            for output_y in range(32):
                y=31-output_y
                self.assertEqual(0,rows[output_y*33])
                expected=bytes(payload[tile*1024+y*32+(x^(4 if y&1 else 0))] for x in range(32))
                self.assertEqual(expected,rows[output_y*33+1:(output_y+1)*33])

    def test_full_transfer_and_combiner_mutations_fail_closed(self):
        run,payload=self.texture_fixture()
        changes=[replace(run,pixel=replace(run.pixel,load_command=(0xF3000000,0x073FF001))),
                 replace(run,palette=replace(run.palette,mode=1)),replace(run,texture_loads=run.texture_loads[:-1]),
                 replace(run,render_tiles=tuple((i,w+1 if i==1 else w,a) for i,w,a in run.render_tiles)),
                 replace(run,combine_mode=(0xFC111404,0xFF13FFFE)),replace(run,tile_bounds=(0,0)),
                 replace(run,texture_scale=(0xD7000002,0xFFFF0000))]
        for changed in changes:
            with self.subTest(changed=changed),self.assertRaises(ValueError): self.decode(changed,payload)
        with self.assertRaises(ValueError): self.decode(run,payload[:-1])
        with self.assertRaisesRegex(ValueError,'payload changed'): scene.decode_planes(run,payload)

    def corner_fixture(self):
        target={'mesh':0,'material':0,'faces':1}
        vertices=[SimpleNamespace(x=i,y=i+1,z=i+2,color=(254,143,93,126),s=0,t=0) for i in range(3)]
        arrays={'POSITION':[(v.x,v.y,v.z) for v in vertices], 'COLOR_0':[v.color for v in vertices],
                'TEXCOORD_0':[(.5,.25)]*3,'indices':[(i,) for i in range(3)]}
        doc={'meshes':[{'primitives':[{'material':0,'extras':{'firstFace':0,'faceCount':1},
              'attributes':{k:k for k in ('POSITION','COLOR_0','TEXCOORD_0')},'indices':'indices'}]}]}
        geometry=SimpleNamespace(material_runs=[SimpleNamespace(face_count=1)],faces=[(0,1,2)],vertices=vertices)
        return doc,geometry,target,arrays

    def test_corners_keep_raw_rgba_and_source_uv(self):
        doc,geometry,target,arrays=self.corner_fixture()
        with patch.object(scene,'accessor',side_effect=lambda d,b,k:arrays[k]), \
                patch.object(scene.models,'texture_coordinates',return_value=(.5,.25)):
            result=scene.affected_corners(doc,b'',geometry,target)
            self.assertEqual([254,143,93,126],result[0][0]['rgba'])
            self.assertEqual([.5,.25],result[0][0]['uv'])
            arrays['COLOR_0'][0]=(255,143,93,126)
            with self.assertRaisesRegex(ValueError,'RGBA changed'): scene.affected_corners(doc,b'',geometry,target)

    def test_corner_uv_or_material_span_change_rejected(self):
        doc,geometry,target,arrays=self.corner_fixture()
        with patch.object(scene,'accessor',side_effect=lambda d,b,k:arrays[k]), \
                patch.object(scene.models,'texture_coordinates',return_value=(.5,.25)):
            arrays['TEXCOORD_0'][0]=(.6,.25)
            with self.assertRaisesRegex(ValueError,'UV changed'): scene.affected_corners(doc,b'',geometry,target)
            target['material']=1
            with self.assertRaisesRegex(ValueError,'material span changed'): scene.affected_corners(doc,b'',geometry,target)

    def test_contract_and_output_path_are_guarded(self):
        self.assertEqual(55,scene.contract()['scene_index'])
        with tempfile.TemporaryDirectory() as temp:
            path=Path(temp)/'config.json'; path.write_bytes(scene.CONTRACT.read_bytes()+b' ')
            with patch.object(scene,'CONTRACT',path),self.assertRaisesRegex(ValueError,'contract changed'): scene.contract()
        for path in (scene.ROOT,scene.ROOT/'build',scene.ROOT/'build/../scripts'):
            with self.assertRaisesRegex(ValueError,'child of build'): scene._checked_output(path)

    def test_create_refuses_existing_directory_and_verify_rejects_stale_source(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp); output=root/'build/inspection'; output.mkdir(parents=True)
            (output/'source-proof.json').write_bytes(b'stale')
            with patch.object(scene,'ROOT',root),patch.object(scene,'build_files',return_value=({'source-proof.json':b'fresh'},{})), \
                    patch.object(scene.subprocess,'run') as run:
                with self.assertRaises(SystemExit): scene.main(['--output',str(output)])
                with self.assertRaises(SystemExit): scene.main(['--output',str(output),'--verify'])
                run.assert_not_called(); self.assertEqual(b'stale',(output/'source-proof.json').read_bytes())

    def test_fresh_create_and_existing_verify_route_worker(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp); output=root/'build/inspection'
            with patch.object(scene,'ROOT',root),patch.object(scene,'build_files',return_value=({'source-proof.json':b'fresh'},{})), \
                    patch.object(scene.subprocess,'run') as run:
                self.assertEqual(0,scene.main(['--output',str(output),'--blender','/custom/blender']))
                first=run.call_args.args[0]; self.assertNotIn('--verify',first); self.assertEqual('/custom/blender',first[0])
                self.assertEqual(0,scene.main(['--output',str(output),'--verify']))
                self.assertIn('--verify',run.call_args.args[0]); self.assertIn('--disable-autoexec',first)

    def test_admission_fresh_verify_and_before_after_stability(self):
        contents={scene.BLEND:b'BLENDER','three-quarter.png':b'PNG'}; output=scene.ROOT/'build/test'
        snapshot=({'files':{'x':'same'}},contents,'selected state')
        with patch.object(scene,'_artifact_snapshot',return_value=snapshot),patch.object(scene.subprocess,'run',
                return_value=SimpleNamespace(returncode=0,stdout='',stderr='')) as run:
            artifact=scene.inspection_artifact(output)
            self.assertEqual(b'BLENDER',artifact['blend']); self.assertIn('--verify',run.call_args.args[0])
        with patch.object(scene,'_artifact_snapshot',side_effect=[snapshot,({'files':{'x':'changed'}},contents,'state')]), \
                patch.object(scene.subprocess,'run',return_value=SimpleNamespace(returncode=0,stdout='',stderr='')):
            with self.assertRaisesRegex(ValueError,'changed during verification'): scene.inspection_artifact(output)

    def test_cli_detects_source_change_during_blender(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp); output=root/'build/inspection'
            snapshots=[({'source-proof.json':b'before'},{}),({'source-proof.json':b'after'}, {})]
            with patch.object(scene,'ROOT',root),patch.object(scene,'build_files',side_effect=snapshots), \
                    patch.object(scene.subprocess,'run'):
                with self.assertRaises(SystemExit): scene.main(['--output',str(output)])
                self.assertEqual(b'before',(output/'source-proof.json').read_bytes())

    def test_admission_worker_failure_and_final_preflight_fail_closed(self):
        output=scene.ROOT/'build/test'; snapshot=({'files':{'x':'same'}},{},'state')
        with patch.object(scene,'_artifact_snapshot',return_value=snapshot),patch.object(scene.subprocess,'run',
                return_value=SimpleNamespace(returncode=1,stdout='',stderr='invalid shader')):
            with self.assertRaisesRegex(ValueError,'fresh Blender verification failed'): scene.inspection_artifact(output)
            with self.assertRaisesRegex(ValueError,'before publication'): scene.inspection_artifact_current(output,{'x':'old'})

    def test_supported_help_does_not_load_rom_or_blender(self):
        result=subprocess.run(['./conker','model-assets','scene55-inspection','--help'],cwd=scene.ROOT,capture_output=True,text=True)
        self.assertEqual(0,result.returncode,result.stderr); self.assertIn('--verify',result.stdout)


if __name__=='__main__':
    unittest.main()
