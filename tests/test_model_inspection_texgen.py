"""Admission, source preservation and one-download gallery tests."""
from __future__ import annotations

import copy
from contextlib import ExitStack, contextmanager
import json
import struct
import tempfile
import sys
import types
import unittest
from pathlib import Path
from unittest import mock

from scripts import model_inspection as inspection
from scripts import model_character_texgen as texgen
from scripts.texture_assets import encode_rgba_png


class TexgenInspectionPublicationTests(unittest.TestCase):
    def fixture(self, root):
        output = root / 'inspect'
        original_png = encode_rgba_png(1, 1, bytes([25, 50, 75, 255]))
        inspection_png = encode_rgba_png(1, 1, bytes([90, 130, 170, 255]))
        records, pending = [], []
        for entry in (66, 67):
            source = root / f'model-{entry}.gltf'
            data = struct.pack('<9f3H', 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 2)
            (root / f'model-{entry}.bin').write_bytes(data)
            source.write_text(json.dumps({'asset': {'version': '2.0'},
                'buffers': [{'uri': f'model-{entry}.bin', 'byteLength': len(data)}]}))
            glb, evidence = inspection.pack_glb(source)
            name = f'review-bank01-{entry:04d}-00-rom'
            rom_source = {'bank': 1, 'entry': entry, 'segment': 0,
                          'source': 'ROM', 'capture_inputs': [], 'manifest_sha256': 'fixture'}
            record = {'name': name, 'label': f'Bank 01 / {entry:04d} / 00',
                'category': 'extracted-review', 'bank': 1, 'entry': entry, 'segment': 0,
                'review_status': 'appearance-blocked' if entry == 66 else 'review-deferred',
                'review_label': 'Appearance issues' if entry == 66 else 'Fragment or variant',
                'status': 'extracted-for-review', 'native_visual_parity': 'incomplete',
                'note': 'Original review reason.', 'face_count': 445, 'missing_material_faces': 0,
                'source': source.name, 'rom_source': rom_source, **evidence,
                'file': 'review/' + name + '.glb',
                'preview': 'previews/review/' + name + '.png',
                'preview_sha256': inspection.digest(original_png)}
            records.append(record)
            pending.extend(((output / record['file'], glb), (root / record['preview'], original_png)))
        config = {'rom_only': True, 'models': [], 'validation_report': 'report.json',
                  'previews': 'previews', 'extracted_review': {'reviews': 'reviews.json'},
                  'texgen_inspection': {'output': 'build/character66-texgen-inspection'}}
        (root / 'report.json').write_text(json.dumps({'status': 'incomplete',
            'summary': {'completed': True}, 'files': [], 'renders': []}))
        blend = b'BLENDER-v500 fixture'
        proof = {'kind': 'character66-neutral-texgen', 'model': [1, 66, 0],
                 'output': config['texgen_inspection']['output'],
                 'source': records[0]['source'], 'source_fingerprint': records[0]['source_fingerprint'],
                 'source_gltf_sha256': records[0]['source_fingerprint']['gltf_sha256'],
                 'blend_sha256': inspection.digest(blend), 'preview_sha256': inspection.digest(inspection_png)}
        artifact = {'blend': blend, 'preview': inspection_png, 'proof': proof,
                    'scope': 'Neutral pose only; joint animation unsupported. Selected inspection state, '
                             'not a native default or native appearance parity claim. Source animations retained separately.'}
        return config, records, pending, artifact

    @contextmanager
    def dependencies(self, root, records, pending, artifact):
        evidence = {r['source']: r['rom_source'] for r in records}
        with ExitStack() as stack:
            stack.enter_context(mock.patch.object(inspection, 'ROOT', root))
            stack.enter_context(mock.patch('scripts.model_inspection_review.prepare_review',
                side_effect=lambda *args: (copy.deepcopy(records), list(pending))))
            stack.enter_context(mock.patch.object(inspection, 'rom_source_evidence',
                side_effect=lambda source, **kwargs: evidence[str(source.relative_to(root))]))
            for name in ('scripts.model_review_representation.apply_representation',
                         'scripts.model_review_equivalence.bind_equivalence_decisions',
                         'scripts.model_review_equivalence.apply_equivalence'):
                stack.enter_context(mock.patch(name))
            admission = stack.enter_context(mock.patch.object(texgen, 'inspection_artifact',
                side_effect=lambda *args: copy.deepcopy(artifact)))
            current = stack.enter_context(mock.patch.object(texgen, 'inspection_artifact_current', return_value=True))
            writes = stack.enter_context(mock.patch.object(inspection, 'write_if_changed', wraps=inspection.write_if_changed))
            yield admission, current, writes

    def publish(self, root, config):
        path = root / 'config.json'
        path.write_text(json.dumps(config))
        return inspection.publish_inspection(path, root / 'inspect')

    def test_opt_in_replaces_one_visible_download_preserving_raw_records_and_every_other_artifact(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp).resolve()
            config, records, pending, artifact = self.fixture(root)
            sources = {p: p.read_bytes() for p in root.glob('model-*')}
            with self.dependencies(root, records, pending, artifact) as (admission, current, writes):
                order = []
                current.side_effect = lambda *args: order.append('preflight') or True
                writes.side_effect = lambda *args: order.append('write')
                # First check preflight order without making publication writes.
                self.publish(root, config)
                self.assertEqual('preflight', order[0])
                self.assertTrue(all(step == 'write' for step in order[1:]))
                writes.side_effect = None
                manifest = self.publish(root, config)
            target, other = manifest['review_models']
            self.assertEqual((0, 2, 2, 2), (manifest['curated_count'], manifest['review_count'],
                             manifest['gallery_review_count'], manifest['gallery_count']))
            allowed = {'label', 'note', 'preview_sha256'}
            for key, value in records[0].items():
                if key not in allowed:
                    self.assertEqual(value, target[key], key)
            self.assertEqual(records[1], other)
            self.assertEqual('appearance-blocked', target['review_status'])
            self.assertEqual('blend', target['download_format'])
            self.assertEqual(artifact['blend'], (root / 'inspect' / target['download_file']).read_bytes())
            self.assertEqual(artifact['preview'], (root / target['preview']).read_bytes())
            for path, data in pending:
                if path != root / target['preview']:
                    self.assertEqual(data, path.read_bytes())
            for path, data in sources.items():
                self.assertEqual(data, path.read_bytes())
            current.assert_called_with(root / config['texgen_inspection']['output'], artifact['proof'])
            page = (root / 'inspect/index.html').read_text()
            cards = [part.split('</article>')[0] for part in page.split('<article ')[1:]]
            selected = [card for card in cards if records[0]['name'] in card]
            self.assertEqual(2, len(cards))
            self.assertEqual(1, len(selected))
            self.assertEqual(1, selected[0].count('<a '))
            self.assertIn('href="' + target['download_file'] + '?v=' + artifact['proof']['blend_sha256'], selected[0])
            self.assertNotIn('href="' + target['file'], selected[0])
            self.assertIn('?v=' + artifact['proof']['preview_sha256'], selected[0])
            self.assertIn('joint animation unsupported', selected[0])
            self.assertIn('appearance-blocked', selected[0])
            readme = (root / 'inspect/README.md').read_text()
            self.assertIn('[' + target['download_file'] + ']', readme)
            self.assertNotIn('[' + target['file'] + ']', readme)
            self.assertIn('.blend', readme)

    def test_animated_mode_selects_verified_backend_and_keeps_one_download(self):
        import scripts
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp).resolve()
            config, records, pending, artifact = self.fixture(root)
            config['texgen_inspection']['mode'] = 'animated'
            artifact['proof']['kind'] = 'character66-animated-texgen'
            artifact['scope'] = 'Three source Actions; imported interpolation approximate. Native state unresolved.'
            backend = types.ModuleType('scripts.model_character_animated_texgen')
            backend.inspection_artifact = mock.Mock(return_value=copy.deepcopy(artifact))
            backend.inspection_artifact_current = mock.Mock(return_value=True)
            with self.dependencies(root, records, pending, artifact) as (neutral, _, _), \
                    mock.patch.dict(sys.modules, {backend.__name__: backend}), \
                    mock.patch.object(scripts, 'model_character_animated_texgen', backend, create=True):
                manifest = self.publish(root, config)
            neutral.assert_not_called()
            backend.inspection_artifact.assert_called_once()
            backend.inspection_artifact_current.assert_called_once_with(
                root / config['texgen_inspection']['output'], artifact['proof'])
            target = manifest['review_models'][0]
            self.assertTrue(target['download_file'].endswith('-animated-texgen.blend'))
            self.assertEqual('appearance-blocked', target['review_status'])
            self.assertEqual(records[0]['glb_sha256'], target['glb_sha256'])
            page = (root / 'inspect/index.html').read_text()
            card = next(c.split('</article>')[0] for c in page.split('<article ')[1:]
                        if records[0]['name'] in c)
            self.assertEqual(1, card.count('<a '))
            self.assertIn('imported interpolation approximate', card)
            self.assertIn('animated Blender inspection', card)

    def test_mode_and_proof_must_agree_before_writes(self):
        for mode in ('unknown', None, [], 'neutral'):
            with self.subTest(mode=mode), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp).resolve()
                config, records, pending, artifact = self.fixture(root)
                config['texgen_inspection']['mode'] = mode
                if mode == 'neutral':
                    artifact['proof']['kind'] = 'character66-animated-texgen'
                with self.dependencies(root, records, pending, artifact) as (_, _, writes):
                    with self.assertRaisesRegex(ValueError, 'texgen inspection'):
                        self.publish(root, config)
                    writes.assert_not_called()

    def test_without_opt_in_never_admits_artifact_or_changes_original_downloads(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp).resolve()
            config, records, pending, artifact = self.fixture(root)
            del config['texgen_inspection']
            with self.dependencies(root, records, pending, artifact) as (admission, current, _):
                manifest = self.publish(root, config)
            admission.assert_not_called()
            current.assert_not_called()
            self.assertEqual(records, manifest['review_models'])
            for path, data in pending:
                self.assertEqual(data, path.read_bytes())
            self.assertNotIn('.blend?v=', (root / 'inspect/index.html').read_text())

    def test_missing_or_changed_review_identity_fails_before_publication(self):
        for mutation in ('missing', 'duplicate', 'name', 'entry', 'status', 'hidden', 'rom', 'raw-glb'):
            with self.subTest(mutation=mutation), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp).resolve()
                config, records, pending, artifact = self.fixture(root)
                if mutation == 'missing': records.pop(0)
                elif mutation == 'duplicate': records.append(copy.deepcopy(records[0]))
                elif mutation == 'name': records[0]['name'] = 'different'
                elif mutation == 'entry': records[0]['entry'] = 68
                elif mutation == 'status': records[0]['review_status'] = 'review-deferred'
                elif mutation == 'hidden': records[0]['gallery_represented_by'] = ['scene']
                elif mutation == 'rom': records[0]['rom_source']['source'] = 'capture'
                elif mutation == 'raw-glb': records[0]['glb_sha256'] = 'changed'
                with self.dependencies(root, records, pending, artifact) as (_, _, writes):
                    with self.assertRaisesRegex(ValueError, 'texgen inspection'):
                        self.publish(root, config)
                    writes.assert_not_called()

    def test_invalid_proof_or_changed_bytes_fails_before_publication(self):
        for mutation in ('model', 'source', 'source_fingerprint', 'source_gltf_sha256', 'blend', 'preview'):
            with self.subTest(mutation=mutation), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp).resolve()
                config, records, pending, artifact = self.fixture(root)
                if mutation in ('blend', 'preview'):
                    artifact[mutation] += b'changed'
                else:
                    artifact['proof'][mutation] = 'changed'
                with self.dependencies(root, records, pending, artifact) as (_, _, writes):
                    with self.assertRaisesRegex(ValueError, 'texgen inspection'):
                        self.publish(root, config)
                    writes.assert_not_called()

    def test_admission_and_final_freshness_failures_preserve_published_files(self):
        for failure in ('admission', 'final-exception', 'final-false'):
            with self.subTest(failure=failure), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp).resolve()
                config, records, pending, artifact = self.fixture(root)
                (root / 'inspect').mkdir()
                sentinel = root / 'inspect/README.md'
                sentinel.write_bytes(b'previous publication')
                with self.dependencies(root, records, pending, artifact) as (admission, current, writes):
                    if failure == 'admission': admission.side_effect = ValueError('artifact contract changed')
                    elif failure == 'final-exception': current.side_effect = ValueError('artifact contract changed')
                    else: current.return_value = False
                    with self.assertRaises(ValueError):
                        self.publish(root, config)
                    writes.assert_not_called()
                self.assertEqual(b'previous publication', sentinel.read_bytes())

    def test_download_cannot_be_injected_through_model_metadata(self):
        for key in ('download_file', 'download_sha256', 'download_format', 'texgen_inspection'):
            with self.subTest(key=key), self.assertRaisesRegex(ValueError, 'verified artifacts'):
                inspection.validate_gallery_metadata([{'name': 'test', 'category': 'characters', key: 'unverified'}])


if __name__ == '__main__':
    unittest.main()
