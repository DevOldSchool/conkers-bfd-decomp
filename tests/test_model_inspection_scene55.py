"""Single-card scene55 Blender admission with unchanged source evidence."""
from contextlib import ExitStack, contextmanager
import copy
import json
import sys
import tempfile
import types
import unittest
from pathlib import Path
from unittest import mock
import scripts
from scripts import model_inspection as inspection
from scripts.texture_assets import encode_rgba_png


class Scene55PublicationTests(unittest.TestCase):
    def fixture(self, root):
        source = root/'geometry/scene-55.gltf';source.parent.mkdir()
        source.write_text(json.dumps({'asset': {'version':'2.0'}, 'buffers':[
            {'uri':'scene-55.bin','byteLength':4}]}))
        source.with_suffix('.bin').write_bytes(b'\0'*4)
        glb, evidence = inspection.pack_glb(source)
        image = encode_rgba_png(1,1,bytes([10,20,30,255])); raw_preview=root/'raw.png';raw_preview.write_bytes(image)
        name='scene-55-assembly-rom'
        case={'name':name,'render_case':name,'label':'Lava cavern — scene 55',
              'category':'scene-items','note':'Original assembly limits.','aliases':['old component name']}
        rom={'source':'ROM','kind':'static-scene-assembly','scene_index':55,
             'capture_inputs':[],'manifest_sha256':'fixture'}
        report={'status':'incomplete','summary':{'completed':True},
                'files':[{'path':str(source),'input_fingerprint':evidence['source_fingerprint'],
                          'checks':{k:{'status':'passed'} for k in ('gltf','blender')}}],
                'renders':[{'id':name,'source':str(source),'image':str(raw_preview),
                            'check':{'current_sha256':inspection.digest(image)}}],
                'checks':{'scene-assemblies:.':{'status':'passed','manifest_sha256':'fixture'}}}
        (root/'report.json').write_text(json.dumps(report))
        config={'rom_only':True,'models':[case],'validation_report':'report.json','previews':'previews',
                'scene55_inspection':{'output':'build/scene55-inspection'}}
        blend=b'BLENDER fixture';preview=encode_rgba_png(1,1,bytes([60,70,80,255]))
        proof={'kind':'scene55-dual-texture','scene_index':55,'output':'build/scene55-inspection',
               'source':str(source.relative_to(root)),'source_fingerprint':evidence['source_fingerprint'],
               'source_gltf_sha256':evidence['source_fingerprint']['gltf_sha256'],
               'blend_sha256':inspection.digest(blend),'preview_sha256':inspection.digest(preview)}
        artifact={'blend':blend,'preview':preview,'proof':proof,
                  'scope':'Selected zero-scroll and stored RGBA. Native lighting and filtering unresolved.'}
        return config,rom,artifact,glb

    @contextmanager
    def dependencies(self, root, rom, artifact):
        backend=types.ModuleType('scripts.model_scene55_inspection')
        backend.inspection_artifact=mock.Mock(side_effect=lambda *args:copy.deepcopy(artifact))
        backend.inspection_artifact_current=mock.Mock(return_value=True)
        with ExitStack() as stack:
            stack.enter_context(mock.patch.object(inspection,'ROOT',root))
            stack.enter_context(mock.patch.object(inspection,'rom_source_evidence',return_value=rom))
            stack.enter_context(mock.patch.dict(sys.modules,{backend.__name__:backend}))
            stack.enter_context(mock.patch.object(scripts,'model_scene55_inspection',backend,create=True))
            writes=stack.enter_context(mock.patch.object(inspection,'write_if_changed',wraps=inspection.write_if_changed))
            yield backend,writes

    def publish(self,root,config):
        path=root/'config.json';path.write_text(json.dumps(config))
        return inspection.publish_inspection(path,root/'inspect')

    def test_one_scene_download_keeps_raw_glb_counts_aliases_and_scope(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary).resolve();config,rom,artifact,glb=self.fixture(root)
            with self.dependencies(root,rom,artifact) as (backend,writes):
                events=[]
                backend.inspection_artifact_current.side_effect=lambda *args:events.append('verify') or True
                writes.side_effect=lambda *args:events.append('write')
                self.publish(root,config)
                self.assertEqual('verify',events[0]);self.assertTrue(all(e=='write' for e in events[1:]))
                writes.side_effect=None
                manifest=self.publish(root,config)
            r=manifest['models'][0]
            self.assertEqual((1,1,0),(manifest['curated_count'],manifest['gallery_count'],manifest['review_count']))
            self.assertEqual('incomplete',r['native_visual_parity'])
            self.assertEqual(config['models'][0]['aliases'],r['aliases'])
            self.assertEqual(glb,(root/'inspect'/r['file']).read_bytes())
            self.assertEqual(artifact['blend'],(root/'inspect'/r['download_file']).read_bytes())
            page=(root/'inspect/index.html').read_text();card=page.split('<article ')[1].split('</article>')[0]
            self.assertEqual(1,card.count('<a '));self.assertIn('dual-texture.blend?v=',card)
            self.assertIn('Native lighting and filtering unresolved',card)
            self.assertNotIn('href="'+r['file'],card)
            self.assertEqual(artifact['preview'],(root/r['preview']).read_bytes())

    def test_bad_identity_source_proof_or_bytes_prevents_writes(self):
        for change in ('scene','source-kind','proof-kind','proof-scene','source-hash','blend','preview','hidden'):
            with self.subTest(change=change),tempfile.TemporaryDirectory() as temporary:
                root=Path(temporary).resolve();config,rom,artifact,_=self.fixture(root)
                if change=='scene':rom['scene_index']=54
                elif change=='source-kind':rom['kind']='indexed-model'
                elif change=='proof-kind':artifact['proof']['kind']='different'
                elif change=='proof-scene':artifact['proof']['scene_index']=54
                elif change=='source-hash':artifact['proof']['source_gltf_sha256']='changed'
                elif change in ('blend','preview'):artifact[change]+=b'changed'
                else:config['models'][0]['gallery_replaced_by']=config['models'][0]['name']
                with self.dependencies(root,rom,artifact) as (_,writes):
                    with self.assertRaises(ValueError):self.publish(root,config)
                    writes.assert_not_called()

    def test_admission_and_final_recheck_failure_preserve_prior_gallery(self):
        for stage in ('admission','final-false','final-exception'):
            with self.subTest(stage=stage),tempfile.TemporaryDirectory() as temporary:
                root=Path(temporary).resolve();config,rom,artifact,_=self.fixture(root)
                old=root/'inspect/index.html';old.parent.mkdir();old.write_bytes(b'previous gallery')
                with self.dependencies(root,rom,artifact) as (backend,writes):
                    if stage=='admission':backend.inspection_artifact.side_effect=ValueError('source changed')
                    elif stage=='final-false':backend.inspection_artifact_current.return_value=False
                    else:backend.inspection_artifact_current.side_effect=ValueError('artifact changed')
                    with self.assertRaises(ValueError):self.publish(root,config)
                    writes.assert_not_called()
                self.assertEqual(b'previous gallery',old.read_bytes())

    def test_scene55_proof_cannot_be_injected_as_model_metadata(self):
        with self.assertRaisesRegex(ValueError,'verified artifacts'):
            inspection.validate_gallery_metadata([{'name':'test','category':'scene-items','scene55_inspection':{}}])


if __name__=='__main__':unittest.main()
