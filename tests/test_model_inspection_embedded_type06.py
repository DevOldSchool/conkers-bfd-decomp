"""Admission and zero-write failure paths for the embedded primitive gallery card."""
from contextlib import ExitStack, contextmanager
import copy
import json
from pathlib import Path
import tempfile
import unittest
from unittest import mock

from scripts import model_inspection as gallery, model_inspection_embedded_type06 as embedded, model_embedded_type06_inspection as backend, model_inspection_embedded as shared
from scripts.texture_assets import encode_rgba_png


class EmbeddedGalleryTests(unittest.TestCase):
    def fixture(self, root):
        source = root / backend.SOURCE
        source.parent.mkdir(parents=True)
        source.write_text(json.dumps({'asset': {'version': '2.0'},
            'buffers': [{'uri': 'fixture.bin', 'byteLength': 4}]}))
        (source.parent / 'fixture.bin').write_bytes(b'\0' * 4)
        manifest = {'family': 'rom-embedded-effect-geometry', 'object_type': 6,
            'indexed_model_bank': None, 'source_vertex_address': '0x8008D538',
            'vertex_count': 4, 'triangle_count': 3, 'normalized_sha1': 'rom'}
        (source.parent.parent / 'manifest.json').write_text(json.dumps(manifest))
        raw, evidence = gallery.pack_glb(source)
        derived = root / 'build/inspection' / backend.DERIVED_GLTF
        derived.parent.mkdir(parents=True)
        derived.write_text(source.read_text())
        (derived.parent / 'fixture.bin').write_bytes(b'\0' * 4)
        glb, _ = gallery.pack_glb(derived)
        preview = encode_rgba_png(1, 1, bytes([200, 200, 200, 255]))
        artifact = {'glb': glb, 'preview': preview, 'scope': backend.SCOPE,
            'proof': {'kind': 'embedded-type06-elapsed0', 'primitive': 'type06', 'elapsed': 0,
                'source': backend.SOURCE, 'source_fingerprint': evidence['source_fingerprint'],
                'source_gltf_sha256': evidence['source_fingerprint']['gltf_sha256'],
                'source_glb_sha256': evidence['glb_sha256'], 'output': 'build/inspection',
                'inspection_state': copy.deepcopy(backend.STATE),
                'derived_glb_sha256': gallery.digest(glb), 'preview_sha256': gallery.digest(preview)}}
        config = {'rom_only': True, 'models': [], 'validation_report': 'report.json',
            'previews': 'previews', 'embedded_type06_inspection': {'output': 'build/inspection'}}
        (root / 'report.json').write_text(json.dumps({'status': 'incomplete',
            'summary': {'completed': True}, 'files': [], 'renders': []}))
        return config, artifact, raw

    @contextmanager
    def dependencies(self, root, artifact):
        with ExitStack() as stack:
            stack.enter_context(mock.patch.object(gallery, 'ROOT', root))
            admit = stack.enter_context(mock.patch.object(backend, 'inspection_artifact',
                side_effect=lambda *args: copy.deepcopy(artifact)))
            current = stack.enter_context(mock.patch.object(backend, 'inspection_artifact_current', return_value=True))
            validate = stack.enter_context(mock.patch.object(shared, 'validate_source',
                return_value={'gltf': {'status': 'passed'}, 'tools': {'fixture': 'hash'}}))
            stack.enter_context(mock.patch.object(shared, 'validator_identity', return_value=(None, None, None, {'fixture': 'hash'})))
            writes = stack.enter_context(mock.patch.object(gallery, 'write_if_changed', wraps=gallery.write_if_changed))
            yield admit, current, validate, writes

    def publish(self, root, config):
        path = root / 'config.json'; path.write_text(json.dumps(config))
        return gallery.publish_inspection(path, root / 'inspect')

    def test_one_embedded_card_one_download_with_separate_source_evidence(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary).resolve(); config, artifact, raw = self.fixture(root)
            with self.dependencies(root, artifact) as (_, current, validate, writes):
                events = []
                current.side_effect = lambda *args: events.append('verify') or True
                writes.side_effect = lambda *args: events.append('write')
                self.publish(root, config)
                self.assertEqual('verify', events[0])
                writes.side_effect = None
                result = self.publish(root, config)
            self.assertEqual((1, 1, 0), (result['curated_count'], result['gallery_count'], result['review_count']))
            record = result['models'][0]
            self.assertNotIn('bank', record)
            self.assertEqual('embedded-effect-primitive', record['rom_source']['kind'])
            self.assertEqual('incomplete', record['native_visual_parity'])
            self.assertEqual(raw, (root / 'inspect' / record['file']).read_bytes())
            self.assertEqual(artifact['glb'], (root / 'inspect' / record['download_file']).read_bytes())
            page = (root / 'inspect/index.html').read_text()
            self.assertEqual(1, page.count('<article '))
            card = page.split('<article ')[1].split('</article>')[0]
            self.assertEqual(1, card.count('<a '))
            self.assertIn('-elapsed0.glb?v=', card)
            self.assertIn('elapsed 0', card)
            self.assertNotIn('href="' + record['file'], card)
            self.assertEqual(4, validate.call_count)

    def test_changed_proof_scope_or_payload_never_publishes(self):
        for change in ('kind', 'elapsed', 'primitive', 'source', 'source_gltf_sha256', 'source_glb_sha256',
                       'source_fingerprint', 'output', 'inspection_state', 'derived_glb_sha256', 'scope', 'glb', 'preview'):
            with self.subTest(change=change), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary).resolve(); config, artifact, _ = self.fixture(root)
                if change in ('scope', 'glb', 'preview'):
                    artifact[change] += ' changed' if change == 'scope' else b'changed'
                else:
                    artifact['proof'][change] = 'changed'
                with self.dependencies(root, artifact) as (_, _, _, writes):
                    with self.assertRaises(ValueError): self.publish(root, config)
                    writes.assert_not_called()

    def test_failures_preserve_previous_gallery(self):
        for fail in ('artifact', 'gltf', 'final', 'manifest', 'derived'):
            with self.subTest(fail=fail), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary).resolve(); config, artifact, _ = self.fixture(root)
                old = root / 'inspect/index.html'; old.parent.mkdir(); old.write_bytes(b'old gallery')
                with self.dependencies(root, artifact) as (admit, current, validate, writes):
                    if fail == 'artifact': admit.side_effect = ValueError('stale artifact')
                    elif fail == 'gltf': validate.side_effect = ValueError('invalid glTF')
                    elif fail == 'final': current.return_value = False
                    else:
                        def mutate(*args):
                            if fail == 'derived':
                                path = root / 'build/inspection' / backend.DERIVED_GLTF
                                (path.parent / 'fixture.bin').write_bytes(b'changed')
                            else:
                                path = root / backend.SOURCE
                                (path.parent.parent / 'manifest.json').write_bytes(b'changed')
                            return True
                        current.side_effect = mutate
                        # A changed input after preparation is rejected by the
                        # separate current callback before artifact verification.
                        original = embedded.prepare_type06
                        def changed(*args):
                            result = original(*args)
                            mutate()
                            return result
                        with mock.patch.object(embedded, 'prepare_type06', side_effect=changed):
                            with self.assertRaises(ValueError): self.publish(root, config)
                        writes.assert_not_called()
                        continue
                    with self.assertRaises(ValueError): self.publish(root, config)
                    writes.assert_not_called()
                self.assertEqual(b'old gallery', old.read_bytes())

    def test_requires_rom_only_and_derived_metadata(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary).resolve(); config, artifact, _ = self.fixture(root)
            config['rom_only'] = False
            with self.dependencies(root, artifact) as (admit, _, _, writes):
                with self.assertRaisesRegex(ValueError, 'ROM-only'): self.publish(root, config)
                admit.assert_not_called(); writes.assert_not_called()
        with self.assertRaisesRegex(ValueError, 'verified artifacts'):
            gallery.validate_gallery_metadata([{'name': 'x', 'category': 'parts-effects',
                                                 'embedded_type06_inspection': {}}])


if __name__ == '__main__': unittest.main()
