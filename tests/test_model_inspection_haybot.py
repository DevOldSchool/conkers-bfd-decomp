"""Keep the selected Haybot phase on one source-bound curated card."""
from contextlib import ExitStack, contextmanager
import copy
import json
from pathlib import Path
import sys
import tempfile
import types
import unittest
from unittest import mock
import scripts
from scripts import model_inspection as gallery, model_assets
from scripts.texture_assets import encode_rgba_png


class HaybotGalleryTests(unittest.TestCase):
    def fixture(self, root):
        source = root / 'geometry/0075-00.gltf'; source.parent.mkdir()
        source.write_text(json.dumps({'asset': {'version': '2.0'},
            'buffers': [{'uri': '0075-00.bin', 'byteLength': 4}]}))
        source.with_suffix('.bin').write_bytes(b'\0' * 4)
        glb, evidence = gallery.pack_glb(source)
        preview = encode_rgba_png(1, 1, bytes([20, 30, 40, 255])); (root/'preview.png').write_bytes(preview)
        name = 'haybot-rom-defaults'
        case = {'name': name, 'render_case': name, 'label': 'Haybot — ROM defaults and animations',
                'category': 'characters', 'note': 'Original unresolved run16 source.', 'aliases': ['Haybot']}
        rom = {'source': 'ROM', 'bank': 1, 'entry': 75, 'segment': 0, 'capture_inputs': [], 'manifest_sha256': 'fixture'}
        report = {'status': 'incomplete', 'summary': {'completed': True}, 'files': [
            {'path': str(source), 'input_fingerprint': evidence['source_fingerprint'],
             'checks': {k: {'status': 'passed'} for k in ('gltf', 'blender')}}], 'renders': [
            {'id': name, 'source': str(source), 'image': str(root/'preview.png'), 'check': {'current_sha256': gallery.digest(preview)}}]}
        (root/'report.json').write_text(json.dumps(report))
        config = {'rom_only': True, 'models': [case], 'validation_report': 'report.json', 'previews': 'previews',
                  'haybot_inspection': {'output': 'build/haybot-inspection'}}
        state = {'phase': 0, 'descriptor': 15, 'native_parity': False}
        scope = 'Selected post-update phase0. Original15 Actions. Native first draw remains unproven.'
        blend = b'BLENDER fixture'; image = encode_rgba_png(1, 1, bytes([40, 50, 60, 255]))
        artifact = {'blend': blend, 'preview': image, 'scope': scope, 'proof': {
            'kind': 'haybot-selected-phase0', 'entry': 75, 'phase': 0, 'descriptor': 15,
            'output': 'build/haybot-inspection', 'source': str(source.relative_to(root)),
            'source_fingerprint': evidence['source_fingerprint'], 'source_gltf_sha256': evidence['source_fingerprint']['gltf_sha256'],
            'source_glb_sha256': evidence['glb_sha256'], 'blend_sha256': gallery.digest(blend),
            'preview_sha256': gallery.digest(image), 'inspection_state': state}}
        return config, rom, artifact, glb, state, scope

    @contextmanager
    def dependencies(self, root, rom, artifact, state, scope):
        backend = types.ModuleType('scripts.model_haybot_inspection')
        backend.SOURCE = 'geometry/0075-00.gltf'; backend.STATE = state; backend.SCOPE = scope
        backend.inspection_artifact = mock.Mock(side_effect=lambda *args: copy.deepcopy(artifact))
        backend.inspection_artifact_current = mock.Mock(return_value=True)
        with ExitStack() as stack:
            stack.enter_context(mock.patch.dict(sys.modules, {backend.__name__: backend}))
            stack.enter_context(mock.patch.object(scripts, 'model_haybot_inspection', backend, create=True))
            stack.enter_context(mock.patch.object(gallery, 'ROOT', root))
            stack.enter_context(mock.patch.object(gallery, 'rom_source_evidence', return_value=rom))
            writes = stack.enter_context(mock.patch.object(gallery, 'write_if_changed', wraps=gallery.write_if_changed))
            yield backend, writes

    def publish(self, root, config):
        path = root/'config.json'; path.write_text(json.dumps(config))
        return gallery.publish_inspection(path, root/'inspect')

    def test_same_card_preserves_raw_source_and_alias_with_one_scoped_download(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary).resolve(); config, rom, artifact, glb, state, scope = self.fixture(root)
            with self.dependencies(root, rom, artifact, state, scope) as (backend, writes):
                calls = []; backend.inspection_artifact_current.side_effect = lambda *args: calls.append('verify') or True
                writes.side_effect = lambda *args: calls.append('write')
                self.publish(root, config); self.assertEqual('verify', calls[0]); writes.side_effect = None
                result = self.publish(root, config)
            self.assertEqual((1, 1, 0), (result['curated_count'], result['gallery_count'], result['review_count']))
            row = result['models'][0]; self.assertEqual('incomplete', row['native_visual_parity'])
            self.assertEqual(['Haybot'], row['aliases'])
            self.assertEqual(glb, (root/'inspect'/row['file']).read_bytes())
            self.assertEqual(artifact['blend'], (root/'inspect'/row['download_file']).read_bytes())
            card = (root/'inspect/index.html').read_text().split('<article ')[1].split('</article>')[0]
            self.assertEqual(1, card.count('<a ')); self.assertIn('-phase0.blend?v=', card)
            self.assertIn('Native first draw remains unproven', card)
            self.assertNotIn('href="' + row['file'], card)

    def test_wrong_identity_state_or_bytes_never_replaces_gallery(self):
        for change in ('entry', 'capture', 'kind', 'phase', 'descriptor', 'inspection_state', 'source_glb_sha256', 'source_fingerprint', 'scope', 'blend', 'preview'):
            with self.subTest(change=change), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary).resolve(); config, rom, artifact, _, state, scope = self.fixture(root)
                state = copy.deepcopy(state)
                if change == 'entry': rom['entry'] = 76
                elif change == 'capture': rom['capture_inputs'] = ['runtime']
                elif change in ('scope', 'blend', 'preview'): artifact[change] += ' changed' if change == 'scope' else b'changed'
                else: artifact['proof'][change] = 'changed'
                with self.dependencies(root, rom, artifact, state, scope) as (_, writes):
                    with self.assertRaises(ValueError): self.publish(root, config)
                    writes.assert_not_called()

    def test_final_failure_and_invalid_options_preserve_previous_gallery(self):
        for options in ({'output': 'build'}, {'output': '../escape'}, {'output': 'build/x', 'phase': 0}, {'output': 'build/haybot-inspection'}):
            with self.subTest(options=options), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary).resolve(); config, rom, artifact, _, state, scope = self.fixture(root)
                old = root/'inspect/index.html'; old.parent.mkdir(); old.write_bytes(b'old gallery')
                config['haybot_inspection'] = options
                with self.dependencies(root, rom, artifact, state, scope) as (backend, writes):
                    backend.inspection_artifact_current.return_value = False
                    with self.assertRaises(ValueError): self.publish(root, config)
                    writes.assert_not_called()
                self.assertEqual(b'old gallery', old.read_bytes())
        with self.assertRaisesRegex(ValueError, 'verified artifacts'):
            gallery.validate_gallery_metadata([{'name': 'x', 'category': 'characters', 'haybot_inspection': {}}])

    def test_cli_delegates_without_entering_generic_decoder(self):
        backend = types.ModuleType('scripts.model_haybot_inspection'); backend.main = mock.Mock(return_value=0)
        args = ['model_assets.py', 'haybot-inspection', '--verify', '--output', 'build/example']
        with mock.patch.dict(sys.modules, {backend.__name__: backend}), mock.patch.object(sys, 'argv', args), \
             mock.patch.object(model_assets, 'parse_args', side_effect=AssertionError('generic parser reached')):
            self.assertEqual(0, model_assets.main())
        backend.main.assert_called_once_with(args[2:])


if __name__ == '__main__': unittest.main()
