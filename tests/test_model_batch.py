from __future__ import annotations

import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from scripts import model_batch as batch


class ModelBatchTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        (self.root / 'scripts').mkdir()
        (self.root / 'scripts/model_assets.py').write_text('decoder-v1')
        self.output = self.root / 'build/assets/models/batch'
        self.output.mkdir(parents=True)
        self.config = {'rom_root': 'build/assets/models/rom-only',
                       'validation_config': 'config/validation.json',
                       'inspection_config': 'config/inspection.json'}
        batch.write(self.root / self.config['validation_config'], {'render_cases': []})
        batch.write(self.root / self.config['inspection_config'], {'models': []})
        for bank in batch.BANKS:
            directory = self.root / self.config['rom_root'] / f'us-bank-{bank:02}-preview'
            batch.write(directory/'manifest.json', {'bank_index': bank, 'normalized_sha1': 'same-rom',
                         'runtime_material_manifest': None, 'models': []})

    def add_model(self, entry=1, *, status='untextured', formula=None, texture=None):
        directory = self.root / self.config['rom_root'] / 'us-bank-04-preview'
        source = directory / f'geometry/{entry:04}-00.gltf'
        source.parent.mkdir(exist_ok=True)
        batch.write(source, {'buffers': [{'uri': f'{entry:04}.bin'}], 'images': []})
        (source.parent / f'{entry:04}.bin').write_bytes(b'geometry')
        run = {'face_count': 2, 'status': status, 'combine_formula': formula, 'texture': texture}
        model = {'bank_entry': entry, 'segment': 0, 'gltf_file': str(source.relative_to(directory)),
                 'face_count': 2, 'material_runs': [run]}
        manifest = batch.read(directory/'manifest.json');manifest['models'].append(model)
        batch.write(directory/'manifest.json', manifest)
        return model, source

    def test_unknown_combiner_is_not_treated_as_untextured(self):
        self.add_model(status='native-material-combiner-unresolved')
        report = batch.scan(self.root, self.config, {}, {})
        self.assertEqual({'material-blocked': 1}, report['counts'])
        self.assertEqual('04:0001:00', report['groups'][0]['representative'])

    def test_known_nontexture_formula_does_not_create_false_material_blocker(self):
        self.add_model(status='rom-default-combiner-does-not-use-texture', formula={'inputs': ['SHADE']})
        self.assertEqual({'review-needed': 1}, batch.scan(self.root, self.config, {}, {})['counts'])

    def test_saved_visual_review_reopens_after_geometry_changes(self):
        model, source = self.add_model()
        reviews = {'04:0001:00': {'fingerprint': batch.model_fingerprint(model, source),
                   'decision': 'review-deferred', 'reason': 'Disconnected fragment'}}
        self.assertEqual({'review-deferred': 1}, batch.scan(self.root, self.config, reviews, {})['counts'])
        (source.parent/'0001.bin').write_bytes(b'changed geometry')
        report = batch.scan(self.root, self.config, reviews, {})
        self.assertEqual({'review-needed': 1}, report['counts'])
        self.assertTrue(report['models'][0]['review_stale'])

    def test_group_deferral_reopens_when_decoder_or_material_changes(self):
        self.add_model(status='runtime-segment')
        group = batch.scan(self.root, self.config, {}, {})['groups'][0]
        holds = {'runtime-segment': {'fingerprint': group['fingerprint'], 'reason': 'Caller unknown'}}
        self.assertEqual('deferred', batch.scan(self.root, self.config, {}, holds)['groups'][0]['status'])
        (self.root/'scripts/model_assets.py').write_text('decoder-v2')
        self.assertEqual('investigate', batch.scan(self.root, self.config, {}, holds)['groups'][0]['status'])

    def test_rejects_mixed_rom_and_captured_corpora(self):
        path = self.root/self.config['rom_root']/'us-bank-04-preview/manifest.json'
        original = batch.read(path)
        for field, value in [('normalized_sha1', 'other-rom'), ('runtime_material_manifest', 'capture.json')]:
            batch.write(path, {**original, field: value})
            with self.assertRaises(ValueError):batch.scan(self.root, self.config, {}, {})

    def test_changed_approved_model_is_not_automatically_removed_or_duplicated(self):
        _, source = self.add_model(status='runtime-segment')
        batch.write(self.root/self.config['validation_config'], {'render_cases': [{'id': 'one', 'source': str(source.relative_to(self.root))}]})
        batch.write(self.root/self.config['inspection_config'], {'models': [{'render_case': 'one'}]})
        report = batch.scan(self.root, self.config, {}, {})
        self.assertEqual({'published': 1}, report['counts'])
        self.assertEqual([], report['groups'])
        self.assertEqual({'runtime-segment': 1}, report['models'][0]['blockers'])

    def test_resume_skips_only_matching_success_with_intact_output(self):
        state = {};calls = []; artifact = self.output/'preview'
        def runner(*args):
            calls.append(args[0]);artifact.mkdir(exist_ok=True);(artifact/'model.bin').write_bytes(b'valid');return 0
        def invoke(key=1):batch.stage(self.root,self.output,state,'preview',['preview'],key,artifact,runner=runner)
        invoke();invoke();self.assertEqual(1,len(calls))
        (artifact/'model.bin').write_bytes(b'tampered');invoke();self.assertEqual(2,len(calls))
        invoke(2);self.assertEqual(3,len(calls))

    def test_failed_and_interrupted_steps_are_never_cached(self):
        state = {}
        with self.assertRaises(ValueError):
            batch.stage(self.root,self.output,state,'preview',['preview'],{},runner=lambda *args: 2)
        self.assertEqual('failed',batch.read(self.output/'state.json')['stages']['preview']['status'])
        def interrupt(*args):raise KeyboardInterrupt()
        with self.assertRaises(KeyboardInterrupt):
            batch.stage(self.root,self.output,state,'preview',['preview'],{},runner=interrupt)
        self.assertEqual('interrupted',batch.read(self.output/'state.json')['stages']['preview']['status'])
        batch.stage(self.root,self.output,state,'preview',['preview'],{},runner=lambda *args: 0)
        self.assertEqual('passed',state['stages']['preview']['status'])

    def test_final_validation_is_called_even_after_previous_success(self):
        state = {}; calls = []
        def runner(*args):calls.append(1);return 0
        for _ in range(2):batch.stage(self.root,self.output,state,'validate',['validate'],{},reusable=False,runner=runner)
        self.assertEqual(2,len(calls))

    def test_lock_rejects_simultaneous_runner(self):
        with batch.lock(self.output):
            with self.assertRaises(ValueError):
                with batch.lock(self.output):pass

    def test_output_paths_cannot_escape_build(self):
        for value in ['config', 'build/assets/models', 'build/assets/models/../../../scripts']:
            with self.assertRaises(ValueError):batch.build_path(self.root, value)
        (self.output/'escape').symlink_to(self.root/'scripts', target_is_directory=True)
        with self.assertRaises(ValueError):batch.build_path(self.root,self.output/'escape')

    def test_new_render_exception_stops_publication_and_stays_blocked_on_resume(self):
        (self.root/'rom').write_bytes(b'rom')
        (self.root/'textures').mkdir()
        config = {**self.config, 'rom': 'rom', 'textures': 'textures', 'corpora': []}
        path = self.output/'report.json'
        batch.write(self.root/self.config['inspection_config'], {'models': [], 'validation_report': str(path.relative_to(self.root))})
        previous = {'status':'incomplete','summary':{'completed':True},'renders':[{'id':'old','check':{'status':'incomplete','current_sha256':'old'}}]}
        batch.write(path, previous);state={};calls=[]
        def runner(command,*args):
            calls.append(command[2])
            if command[2]=='validate':batch.write(path,{**previous,'renders':[{'id':'old','check':{'status':'incomplete','current_sha256':'changed'}}]})
            return 0
        for _ in range(2):
            with self.assertRaisesRegex(ValueError,'changed render'):
                batch.run(self.root,config,self.output,state,[],runner=runner)
        self.assertNotIn('inspect',calls)
        self.assertEqual({'old':'old'},state['baseline_render_exceptions'])
        def approved(command,*args):
            calls.append(command[2])
            if command[2]=='validate':batch.write(path,{**previous,'renders':[]})
            return 0
        batch.run(self.root,config,self.output,state,[],runner=approved)
        self.assertIn('inspect',calls)
        self.assertEqual({}, state['baseline_render_exceptions'])
        def returns(command,*args):
            if command[2]=='validate':batch.write(path, previous)
            return 0
        with self.assertRaisesRegex(ValueError,'changed render'):
            batch.run(self.root,config,self.output,state,[],runner=returns)

    def test_bank_run_refreshes_all_corpora_and_resumes_before_authoritative_gates(self):
        (self.root/'rom').write_bytes(b'rom');(self.root/'textures').mkdir()
        config = {**self.config, 'rom':'rom', 'textures':'textures', 'corpora':[
            {'name':'rom-only','root':self.config['rom_root'],'rom_defaults':True},
            {'name':'main','root':'build/assets/models','runtime_materials':'captures/main/manifest.json'},
            {'name':'colours','root':'build/assets/models/colours','runtime_materials':'captures/colours/manifest.json'}]}
        path = self.output/'report.json'
        batch.write(self.root/self.config['inspection_config'], {'models':[],'validation_report':str(path.relative_to(self.root))})
        complete = {'status':'incomplete','summary':{'completed':True},'renders':[]}
        batch.write(path,complete);state={};calls=[]
        def runner(command,*args):
            calls.append(command)
            if command[2]=='preview':
                destination=Path(command[command.index('--output')+1]);destination.mkdir(parents=True,exist_ok=True)
                (destination/'made.bin').write_bytes(b'output')
            if command[2]=='validate':batch.write(path,complete)
            return 0
        batch.run(self.root,config,self.output,state,[1],runner=runner)
        previews=[c for c in calls if c[2]=='preview'];self.assertEqual(3,len(previews))
        self.assertIn('--rom-defaults',previews[0]);self.assertNotIn('--runtime-materials',previews[0])
        for c in previews[1:]:
            self.assertIn('--runtime-materials',c);self.assertNotIn('--rom-defaults',c)
        calls.clear();batch.run(self.root,config,self.output,state,[1],runner=runner)
        self.assertEqual(['validate','inspect'],[c[2]for c in calls])
        # Gallery naming changes need current tests/validation, not new exports.
        inspection = batch.read(self.root/self.config['inspection_config'])
        batch.write(self.root/self.config['inspection_config'], {**inspection, 'title': 'new label'})
        calls.clear();batch.run(self.root,config,self.output,state,[1],runner=runner)
        self.assertEqual(['unittest','validate','inspect'],[c[2]for c in calls])

    def test_scene_assemblies_refresh_after_exports_before_validation(self):
        (self.root / 'rom').write_bytes(b'rom')
        (self.root / 'textures').mkdir()
        config = {**self.config, 'rom': 'rom', 'textures': 'textures',
                  'corpora': [{'name': 'rom-only', 'root': self.config['rom_root']}]}
        destination = 'build/assets/models/rom-scene-assemblies'
        batch.write(self.root / self.config['validation_config'], {'scene_assemblies': [destination]})
        path = self.output / 'report.json'
        batch.write(self.root / self.config['inspection_config'],
                    {'models': [], 'validation_report': str(path.relative_to(self.root))})
        complete = {'status': 'incomplete', 'summary': {'completed': True}, 'renders': []}
        batch.write(path, complete)
        calls, state = [], {}
        def runner(command, *args):
            calls.append(command[2])
            if command[2] in ('preview', 'scene-assemblies'):
                target = Path(command[command.index('--output') + 1])
                target.mkdir(parents=True, exist_ok=True)
                (target / 'manifest.json').write_text('{}')
            if command[2] == 'validate':
                batch.write(path, complete)
            return 0
        batch.run(self.root, config, self.output, state, [4], runner=runner)
        self.assertEqual(['unittest', 'verify', 'preview', 'scene-assemblies', 'validate', 'inspect'], calls)
        calls.clear()
        batch.run(self.root, config, self.output, state, [4], runner=runner)
        self.assertEqual(['scene-assemblies', 'validate', 'inspect'], calls)

    def test_constructor_journal_reuses_only_intact_current_evidence(self):
        (self.root/'rom').write_bytes(b'rom')
        (self.root/'scripts/model_assets.py').write_text('from scripts import model_constructor_analysis\n')
        (self.root/'scripts/model_constructor_analysis.py').write_text('version = 1\n')
        config = {**self.config, 'rom': 'rom'}
        calls = []; state = {}
        def runner(command, *args):
            calls.append(command)
            batch.write(Path(command[-1]), {'counts': {}, 'argument_analysis': {'counts': {}}, 'target_queue': []})
            return 0
        def invoke():return batch.constructor_stage(self.root,config,self.output,state,[9],runner=runner)
        self.assertIn('9', invoke());invoke();self.assertEqual(1,len(calls))
        (self.root/'scripts/unrelated.py').write_text('x = 1\n')
        invoke();self.assertEqual(1,len(calls))
        (self.output/'constructors-bank09.json').write_text('{}')
        invoke();self.assertEqual(2,len(calls))
        (self.root/'scripts/model_constructor_analysis.py').write_text('version = 2\n')
        invoke();self.assertEqual(3,len(calls))

    def test_failed_validation_report_blocks_inspection_even_with_zero_process_exit(self):
        (self.root/'rom').write_bytes(b'rom');(self.root/'textures').mkdir()
        config={**self.config,'rom':'rom','textures':'textures','corpora':[]}
        path=self.output/'report.json'
        batch.write(self.root/self.config['inspection_config'],{'models':[],'validation_report':str(path.relative_to(self.root))})
        batch.write(path,{'status':'passed','summary':{'completed':True},'renders':[]})
        calls=[]
        def runner(command,*args):
            calls.append(command[2])
            if command[2]=='validate':batch.write(path,{'status':'failed','summary':{'completed':False}})
            return 0
        with self.assertRaisesRegex(ValueError,'validation did not complete'):
            batch.run(self.root,config,self.output,{},[],runner=runner)
        self.assertNotIn('inspect',calls)


if __name__ == '__main__':
    unittest.main()
