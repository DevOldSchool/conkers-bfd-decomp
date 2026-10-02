"""Derived scene representation must never hide a different or blocked source."""
import copy
import unittest

from scripts.model_review_representation import apply_representation


def fixture():
    fingerprint = {'gltf_sha256': 'a' * 64, 'dependencies_sha256': {'part.bin': 'b' * 64}}
    provenance = {'manifest_sha256': 'c' * 64, 'bank': 4, 'entry': 23, 'segment': 9,
                  'source': 'ROM', 'capture_inputs': []}
    review = {'name': 'review-bank04-0023-09-rom', 'file': 'review/review-bank04-0023-09-rom.glb',
              'label': 'Bank 04 / 0023 / 09', 'category': 'extracted-review',
              'bank': 4, 'entry': 23, 'segment': 9, 'review_status': 'review-deferred',
              'face_count': 162, 'missing_material_faces': 0, 'native_visual_parity': 'incomplete',
              'source': 'build/assets/models/rom-only/us-bank-04-preview/geometry/0023-09.gltf',
              'source_fingerprint': fingerprint, 'rom_source': provenance,
              'note': 'Requires scene context.', 'glb_sha256': 'd' * 64}
    assembly = {'name': 'scene-23-assembly-rom', 'category': 'scene-items',
                'file': 'scene-23-assembly-rom.glb', 'note': 'Static scene; visibility remains unresolved.',
                'aliases': ['Old scene name'], 'native_visual_parity': 'incomplete',
                'rom_source': {'kind': 'static-scene-assembly', 'source': 'ROM', 'capture_inputs': [],
                    'manifest_sha256': 'e' * 64, 'scene_index': 23,
                    'components': [{'model': [4, 23, 9], 'path': review['source'],
                        'fingerprint': copy.deepcopy(fingerprint), 'rom_source': copy.deepcopy(provenance),
                        'face_count': 162}]}}
    return [assembly], [review]


class ReviewRepresentationTests(unittest.TestCase):
    def test_exact_component_gets_one_assembly_link_and_searchable_identity(self):
        curated, reviews = fixture()
        source = copy.deepcopy(reviews[0])
        result = apply_representation(curated, reviews)
        self.assertEqual({'represented_review_count': 1, 'representing_assembly_count': 1}, result)
        self.assertEqual(['scene-23-assembly-rom'], reviews[0]['gallery_represented_by'])
        self.assertEqual(source, {k: v for k, v in reviews[0].items() if k != 'gallery_represented_by'})
        for term in ('Bank 04 / 0023 / 09', 'review-bank04-0023-09-rom',
                     'review/review-bank04-0023-09-rom.glb', 'review-bank04-0023-09-rom.glb', '04:0023:09'):
            self.assertIn(term, curated[0]['aliases'])
        self.assertIn('unresolved native appearance', curated[0]['note'])
        self.assertEqual('incomplete', curated[0]['native_visual_parity'])
        self.assertEqual([4, 23, 9], curated[0]['represented_review_components'][0]['model'])
        once = copy.deepcopy((curated, reviews))
        self.assertEqual(result, apply_representation(curated, reviews))
        self.assertEqual(once, (curated, reviews))

    def test_component_provenance_mutations_fail_before_any_changes(self):
        mutations = (
            lambda c: c.update(path='build/other/part.gltf'),
            lambda c: c['fingerprint'].update(gltf_sha256='f' * 64),
            lambda c: c['fingerprint']['dependencies_sha256'].update({'part.bin': 'f' * 64}),
            lambda c: c['rom_source'].update(manifest_sha256='f' * 64),
            lambda c: c['rom_source'].update(capture_inputs=['capture.json']),
            lambda c: c['rom_source'].update(entry=24),
            lambda c: c.update(face_count=161),
        )
        for mutate in mutations:
            curated, reviews = fixture()
            mutate(curated[0]['rom_source']['components'][0])
            before = copy.deepcopy((curated, reviews))
            with self.subTest(mutation=mutate), self.assertRaisesRegex(ValueError, 'conflicts'):
                apply_representation(curated, reviews)
            self.assertEqual(before, (curated, reviews))

    def test_identity_mismatch_and_duplicate_candidates_fail(self):
        for change in ('provenance', 'review-duplicate', 'component-duplicate', 'component-type'):
            curated, reviews = fixture()
            if change == 'provenance': reviews[0]['rom_source']['bank'] = 3
            elif change == 'review-duplicate': reviews.append(copy.deepcopy(reviews[0]))
            elif change == 'component-duplicate': curated[0]['rom_source']['components'] *= 2
            else: curated[0]['rom_source']['components'][0]['model'][0] = 4.0
            with self.subTest(change=change), self.assertRaises(ValueError):
                apply_representation(curated, reviews)

    def test_blocked_stale_and_empty_records_stay_visible(self):
        for status, faces, missing in (('material-blocked', 162, 3), ('appearance-blocked', 162, 0),
                                      ('review-needed', 162, 0), ('review-deferred', 162, 1),
                                      ('no-drawable-geometry', 0, 0), ('review-deferred', 0, 0)):
            curated, reviews = fixture()
            reviews[0].update(review_status=status, face_count=faces, missing_material_faces=missing)
            with self.subTest(status=status, faces=faces, missing=missing):
                self.assertEqual(0, apply_representation(curated, reviews)['represented_review_count'])
                self.assertNotIn('gallery_represented_by', reviews[0])
                self.assertEqual(status, reviews[0]['review_status'])

    def test_excluded_component_and_hidden_assembly_do_not_resolve_review(self):
        for mode in ('excluded', 'replaced', 'represented'):
            curated, reviews = fixture()
            if mode == 'excluded': curated[0]['rom_source']['components'] = []
            elif mode == 'replaced': curated[0]['gallery_replaced_by'] = 'another-scene'
            else: curated[0]['gallery_represented_by'] = ['another-scene']
            with self.subTest(mode=mode):
                self.assertEqual(0, apply_representation(curated, reviews)['represented_review_count'])
                self.assertNotIn('gallery_represented_by', reviews[0])

    def test_multiple_containing_assemblies_retain_all_memberships(self):
        curated, reviews = fixture()
        second = copy.deepcopy(curated[0])
        second.update(name='scene-02-assembly-rom', file='scene-02-assembly-rom.glb')
        second['rom_source']['scene_index'] = 2
        curated.append(second)
        self.assertEqual({'represented_review_count': 1, 'representing_assembly_count': 2},
                         apply_representation(curated, reviews))
        self.assertEqual(['scene-02-assembly-rom', 'scene-23-assembly-rom'], reviews[0]['gallery_represented_by'])
        for target in curated:
            self.assertIn('04:0023:09', target['aliases'])
        bad = copy.deepcopy(curated)
        bad[1]['rom_source']['components'][0]['fingerprint']['gltf_sha256'] = 'f' * 64
        with self.assertRaisesRegex(ValueError, 'conflicts'):
            apply_representation(bad, reviews)

    def test_matching_empty_or_captured_evidence_does_not_count_as_proof(self):
        for mode in ('empty-fingerprint', 'invalid-provenance', 'assembly-hash', 'assembly-capture'):
            curated, reviews = fixture()
            component = curated[0]['rom_source']['components'][0]
            if mode == 'empty-fingerprint':
                reviews[0]['source_fingerprint'] = component['fingerprint'] = {}
            elif mode == 'invalid-provenance':
                reviews[0]['rom_source']['manifest_sha256'] = 'unknown'
                component['rom_source']['manifest_sha256'] = 'unknown'
            elif mode == 'assembly-hash':
                curated[0]['rom_source']['manifest_sha256'] = 'unknown'
            else:
                curated[0]['rom_source']['capture_inputs'] = ['capture.json']
            with self.subTest(mode=mode), self.assertRaises(ValueError):
                apply_representation(curated, reviews)
            self.assertNotIn('gallery_represented_by', reviews[0])

    def test_current_ineligible_state_clears_prior_derived_hiding(self):
        curated, reviews = fixture()
        apply_representation(curated, reviews)
        reviews[0]['review_status'] = 'review-needed'
        result = apply_representation(curated, reviews)
        self.assertEqual(0, result['represented_review_count'])
        self.assertNotIn('gallery_represented_by', reviews[0])
        self.assertNotIn('represented_review_components', curated[0])
        self.assertNotIn('review_representation_note', curated[0])
        self.assertEqual('Static scene; visibility remains unresolved.', curated[0]['note'])

    def test_invalid_target_metadata_cannot_leave_partial_hiding(self):
        for field, value in (('aliases', [123]), ('note', None), ('name', None)):
            curated, reviews = fixture()
            curated[0][field] = value
            before = copy.deepcopy((curated, reviews))
            with self.subTest(field=field), self.assertRaises(ValueError):
                apply_representation(curated, reviews)
            self.assertEqual(before, (curated, reviews))


if __name__ == '__main__':
    unittest.main()
