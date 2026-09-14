import json
import tempfile
import unittest
from pathlib import Path
from unittest import mock

from scripts import model_inspection as inspection, model_inspection_review as review
from scripts.model_batch import model_fingerprint


class ExtractedReviewTests(unittest.TestCase):
    def test_collects_remaining_records_without_accepting_them_and_rejects_stale_files(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp).resolve()
            config = {'model_root': 'models', 'reviews': 'reviews.json'}
            files, decisions = {}, {}
            for bank in (1, 3, 4, 9):
                directory = root / 'models' / f'us-bank-{bank:02x}-preview'
                (directory / 'geometry').mkdir(parents=True)
                models = []
                if bank == 9:
                    for entry, faces, status in [(0, 2, 'untextured'), (1, 2, 'runtime-segment'), (2, 0, 'untextured'), (3, 4, 'untextured')]:
                        path = directory / f'geometry/{entry:04}-00.gltf'
                        path.write_text(json.dumps({'asset': {'version': '2.0'}, 'buffers': [], 'images': [], 'materials': []}))
                        row = {'bank_entry': entry, 'segment': 0, 'gltf_file': f'geometry/{path.name}',
                               'face_count': faces, 'material_runs': [{'face_count': faces, 'status': status, 'runtime_material': None}]}
                        models.append(row)
                        files[str(path)] = {'input_fingerprint': review.preview_fingerprint(path),
                                           'checks': {'gltf': {'status': 'passed'}, 'blender': {'status': 'passed'}}}
                        if entry == 3:
                            decisions['09:0003:00'] = {'fingerprint': model_fingerprint(row, path),
                                                       'decision': 'review-deferred', 'reason': 'Variant'}
                (directory / 'manifest.json').write_text(json.dumps({'family': f'indexed-bank-{bank:02x}-model-preview',
                    'profile': 'us', 'bank_index': bank, 'models': models}))
            (root / 'reviews.json').write_text(json.dumps({'models': decisions}))
            curated = [{'rom_source': {'bank': 9, 'entry': 0, 'segment': 0}},
                       {'rom_source': {'kind': 'static-scene-assembly'}}]
            with mock.patch.object(review, 'ROOT', root):
                rows = review.collect_review(config, curated, files)
                self.assertEqual([1, 3, 2], [r['entry'] for r in rows])
                self.assertEqual(['material-blocked', 'review-deferred', 'no-drawable-geometry'], [r['review_status'] for r in rows])
                self.assertTrue(all(r['status'] == 'extracted-for-review' for r in rows))
                self.assertEqual(2, rows[0]['missing_material_faces'])
                source = root / rows[0]['source']
                source.write_text(source.read_text() + '\n')
                with self.assertRaisesRegex(ValueError, 'current file validation'):
                    review.collect_review(config, curated, files)

    def test_review_cards_show_status_and_empty_records_without_broken_images(self):
        records = [{'label': 'Bank 01 / 0011 / 00', 'name': 'empty', 'file': 'review/empty.glb',
                    'glb_sha256': 'hash', 'category': 'extracted-review', 'bank': 1,
                    'review_status': 'no-drawable-geometry', 'review_label': 'No drawable faces',
                    'note': 'No geometry <test>'}]
        page = inspection.gallery_page(records, inspection.ROOT / 'inspect')
        self.assertIn('Extracted review', page)
        self.assertIn('preview-placeholder', page)
        self.assertIn('data-bank="01"', page)
        self.assertIn('data-review-status="no-drawable-geometry"', page)
        self.assertNotIn('<img ', page)
        self.assertIn('No geometry &lt;test&gt;', page)
