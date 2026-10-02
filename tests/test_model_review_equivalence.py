"""Current file and review boundaries for derived presentation equivalence."""
import copy
import json
import struct
import tempfile
import unittest
import zlib
from pathlib import Path
from unittest import mock

from scripts import model_review_equivalence as equivalence
from scripts.model_batch import model_fingerprint
from scripts.model_inspection import rom_source_evidence
from scripts.model_preview_evidence import preview_fingerprint


def png(color):
    def chunk(kind, data):
        return struct.pack('>I', len(data)) + kind + data + struct.pack('>I', zlib.crc32(kind + data))
    return (b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', 1, 1, 8, 6, 0, 0, 0))
            + chunk(b'IDAT', zlib.compress(b'\0' + bytes(color))) + chunk(b'IEND', b''))


class EquivalenceTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.directory = self.root / 'models/bank04'
        (self.directory / 'geometry').mkdir(parents=True)
        (self.directory / 'textures').mkdir()
        # Three vertices, their UVs and indices, then aligned animation times.
        binary = (struct.pack('<9f', 0, 0, 0, 1, 0, 0, 0, 1, 0)
                  + struct.pack('<6f', 0, 0, 1, 0, 0, 1)
                  + struct.pack('<3H', 0, 1, 2) + b'\0\0' + struct.pack('<3f', 0, 1, 2))
        self.models = []
        for entry in (6, 59):
            stem = f'{entry:04d}-05'
            path = self.directory / f'geometry/{stem}.gltf'
            document = {'asset': {'version': '2.0', 'generator': f'fixture {entry}'},
                'scene': 0, 'scenes': [{'nodes': [0]}],
                'nodes': [{'mesh': 0, 'name': stem}],
                'meshes': [{'name': stem, 'primitives': [{'attributes': {'POSITION': 0, 'TEXCOORD_0': 1},
                    'indices': 2, 'material': 0, 'mode': 4, 'extras': {'ROMEntry': entry}}]}],
                'buffers': [{'uri': stem + '.bin', 'byteLength': len(binary)}],
                'bufferViews': [{'buffer': 0, 'byteOffset': 0, 'byteLength': 36},
                    {'buffer': 0, 'byteOffset': 36, 'byteLength': 24},
                    {'buffer': 0, 'byteOffset': 60, 'byteLength': 6},
                    {'buffer': 0, 'byteOffset': 68, 'byteLength': 12}],
                'accessors': [{'bufferView': 0, 'componentType': 5126, 'count': 3, 'type': 'VEC3',
                    'min': [0, 0, 0], 'max': [1, 1, 0]},
                    {'bufferView': 1, 'componentType': 5126, 'count': 3, 'type': 'VEC2'},
                    {'bufferView': 2, 'componentType': 5123, 'count': 3, 'type': 'SCALAR'},
                    {'bufferView': 3, 'componentType': 5126, 'count': 3, 'type': 'SCALAR', 'min': [0], 'max': [2]}],
                'images': [{'uri': f'../textures/{stem}.png'}],
                'textures': [{'source': 0, 'sampler': 0}], 'samplers': [{'wrapS': 10497, 'wrapT': 10497}],
                'materials': [{'name': stem, 'pbrMetallicRoughness': {'baseColorTexture': {'index': 0}},
                    'extensions': {'KHR_materials_unlit': {}}}],
                'extensionsUsed': ['KHR_materials_unlit'],
                'animations': [{'name': stem, 'samplers': [{'input': 3, 'output': 0, 'interpolation': 'LINEAR'}],
                    'channels': [{'sampler': 0, 'target': {'node': 0, 'path': 'translation'}}]}]}
            path.write_text(json.dumps(document))
            path.with_suffix('.bin').write_bytes(binary)
            (self.directory / f'textures/{stem}.png').write_bytes(png((255, 0, 0, 255)))
            self.models.append({'bank_entry': entry, 'segment': 5, 'gltf_file': f'geometry/{stem}.gltf',
                'face_count': 1, 'source_face_count': 1, 'material_runs': [{'face_count': 1,
                    'status': 'runtime-composed-direct-ci8-texture', 'texture': {'flat_index': 42}}]})
        self.manifest = {'family': 'indexed-bank-04-model-preview', 'profile': 'us', 'bank_index': 4,
                         'normalized_sha1': '1' * 40, 'models': self.models}
        self.write_manifest()
        self.target = {'name': 'object-bank04-0006-05-rom', 'label': 'Current prop',
            'source': 'models/bank04/geometry/0006-05.gltf', 'file': 'object-bank04-0006-05-rom.glb',
            'status': 'ready-for-inspection', 'native_visual_parity': 'incomplete',
            'note': 'Native state is unresolved.', 'aliases': ['Original name', '04:0059:05']}
        self.source = {'name': 'review-bank04-0059-05-rom', 'label': 'Bank 04 / 0059 / 05',
            'source': 'models/bank04/geometry/0059-05.gltf', 'file': 'review/review-bank04-0059-05-rom.glb',
            'bank': 4, 'entry': 59, 'segment': 5, 'face_count': 1, 'missing_material_faces': 0,
            'review_status': 'review-deferred', 'native_visual_parity': 'incomplete',
            'note': 'Distinct source; consumer unverified.', 'presentation_equivalent_to': self.target['name']}
        self.curated, self.reviews = [self.target], [self.source]
        self.refresh()
        self.decisions_path = self.root / 'reviews.json'
        self.write_decisions()

    def write_manifest(self):
        (self.directory / 'manifest.json').write_text(json.dumps(self.manifest))

    def refresh(self):
        for record in (self.source, self.target):
            path = self.root / record['source']
            record['source_fingerprint'] = preview_fingerprint(path)
            record['rom_source'] = rom_source_evidence(path)

    def write_decisions(self, fingerprint=None, target=None):
        decision = {'decision': 'review-deferred',
            'fingerprint': fingerprint or model_fingerprint(self.models[1], self.root / self.source['source']),
            'presentation_equivalent_to': self.target['name'] if target is None else target}
        self.decisions_path.write_text(json.dumps({'models': {'04:0059:05': decision}}))

    def document(self, record=None):
        path = self.root / (record or self.source)['source']
        return path, json.loads(path.read_text())

    def apply(self):
        return equivalence.apply_equivalence(self.curated, self.reviews, self.root)

    def assert_atomic_error(self, message=None):
        before = copy.deepcopy((self.curated, self.reviews))
        with self.assertRaisesRegex(ValueError, message or '.*'):
            self.apply()
        self.assertEqual(before, (self.curated, self.reviews))

    def test_exact_standard_presentation_retains_both_rom_identities_and_aliases(self):
        before = copy.deepcopy(self.source)
        self.assertEqual({'equivalent_review_count': 1, 'equivalent_target_count': 1}, self.apply())
        self.assertEqual(self.target['name'], self.source['gallery_equivalent_to'])
        self.assertEqual(before, {k: v for k, v in self.source.items() if k != 'gallery_equivalent_to'})
        evidence, = self.target['equivalent_review_sources']
        self.assertEqual([4, 59, 5], evidence['model'])
        self.assertEqual(6, self.target['rom_source']['entry'])
        self.assertEqual(59, evidence['rom_source']['entry'])
        self.assertEqual(before['source_fingerprint'], evidence['source_fingerprint'])
        for alias in (self.source['label'], self.source['name'], self.source['file'],
                      'review-bank04-0059-05-rom.glb', '04:0059:05', 'Original name'):
            self.assertIn(alias, self.target['aliases'])
        self.assertIn('native appearance are not equated', self.target['note'])
        self.assertEqual('incomplete', self.target['native_visual_parity'])
        once = copy.deepcopy((self.curated, self.reviews))
        self.apply()
        self.assertEqual(once, (self.curated, self.reviews))

    def test_freshly_fingerprinted_sampler_geometry_animation_and_image_changes_fail(self):
        for kind in ('sampler', 'geometry', 'animation', 'image'):
            with self.subTest(kind=kind):
                self.setUp()
                path, doc = self.document()
                if kind == 'sampler': doc['samplers'][0]['wrapS'] = 33071
                elif kind == 'geometry': doc['nodes'][0]['translation'] = [0, 0, 1]
                elif kind == 'animation': doc['animations'][0]['samplers'][0]['interpolation'] = 'STEP'
                else: (self.directory / 'textures/0059-05.png').write_bytes(png((0, 0, 255, 255)))
                path.write_text(json.dumps(doc))
                self.refresh()
                self.assert_atomic_error('presentations differ')

    def test_freshly_fingerprinted_buffer_byte_changes_fail(self):
        path, doc = self.document()
        binary = bytearray(path.with_suffix('.bin').read_bytes())
        struct.pack_into('<f', binary, 12, 2.0)
        path.with_suffix('.bin').write_bytes(binary)
        doc['accessors'][0]['max'][0] = 2
        path.write_text(json.dumps(doc))
        self.refresh()
        self.assert_atomic_error('presentations differ')

    def test_hidden_blocked_missing_assembly_and_stale_targets_fail_atomically(self):
        for kind in ('replaced', 'represented', 'equivalent', 'blocked', 'missing', 'assembly', 'stale'):
            with self.subTest(kind=kind):
                self.setUp()
                if kind == 'replaced': self.target['gallery_replaced_by'] = 'other'
                elif kind == 'represented': self.target['gallery_represented_by'] = ['other']
                elif kind == 'equivalent': self.target['gallery_equivalent_to'] = 'other'
                elif kind == 'blocked': self.target['review_status'] = 'appearance-blocked'
                elif kind == 'missing': self.source['presentation_equivalent_to'] = 'absent'
                elif kind == 'assembly': self.target['rom_source']['kind'] = 'static-scene-assembly'
                else: (self.root / self.target['source']).with_suffix('.bin').write_bytes(b'changed')
                self.assert_atomic_error()

    def test_target_current_manifest_material_blocker_cannot_be_hidden_by_record_metadata(self):
        self.models[0]['material_runs'][0].update(texture=None, status='external-runtime-texture')
        self.write_manifest()
        self.refresh()
        self.assert_atomic_error('incomplete materials')

    def test_ineligible_sources_clear_only_derived_links_aliases_and_notes(self):
        for update in ({'review_status': 'material-blocked'}, {'review_status': 'review-needed'},
                       {'missing_material_faces': 1}, {'face_count': 0},
                       {'gallery_represented_by': ['scene-59-assembly-rom']}):
            with self.subTest(update=update):
                self.setUp()
                self.apply()
                self.source.update(update)
                self.assertEqual({'equivalent_review_count': 0, 'equivalent_target_count': 0}, self.apply())
                self.assertNotIn('gallery_equivalent_to', self.source)
                self.assertNotIn('equivalent_review_sources', self.target)
                self.assertEqual(['Original name', '04:0059:05'], self.target['aliases'])
                self.assertEqual('Native state is unresolved.', self.target['note'])
                self.assertEqual('incomplete', self.source['native_visual_parity'])

    def test_unsupported_extensions_leave_card_visible_and_clear_prior_derivation(self):
        for location in ('declared', 'required', 'embedded'):
            with self.subTest(location=location):
                self.setUp()
                self.apply()
                path, doc = self.document()
                if location == 'declared': doc['extensionsUsed'].append('EXT_mesh_gpu_instancing')
                elif location == 'required': doc['extensionsRequired'] = ['EXT_mesh_gpu_instancing']
                else: doc['nodes'][0]['extensions'] = {'EXT_mesh_gpu_instancing': {'attributes': {}}}
                path.write_text(json.dumps(doc))
                self.refresh()
                self.assertEqual(0, self.apply()['equivalent_review_count'])
                self.assertNotIn('gallery_equivalent_to', self.source)
                self.assertNotIn('equivalent_review_sources', self.target)

    def test_wrong_identity_captured_provenance_or_stale_source_is_rejected(self):
        for kind in ('identity', 'bool-identity', 'capture', 'manifest', 'dependency'):
            with self.subTest(kind=kind):
                self.setUp()
                if kind == 'identity': self.source['entry'] = 58
                elif kind == 'bool-identity': self.source['bank'] = True
                elif kind == 'capture': self.source['rom_source']['capture_inputs'] = ['capture.json']
                elif kind == 'manifest': self.source['rom_source']['manifest_sha256'] = '0' * 64
                else: (self.directory / 'textures/0059-05.png').write_bytes(png((0, 255, 0, 255)))
                self.assert_atomic_error()

    def test_bad_note_after_successful_comparison_cannot_partially_hide_sources(self):
        self.target['note'] = None
        self.assert_atomic_error('note')

    def test_dependency_change_during_comparison_is_caught_by_final_recheck(self):
        original = equivalence._canonical
        calls = []
        def mutate_after_comparison(path):
            result = original(path)
            calls.append(path)
            if len(calls) == 2:
                (self.directory / 'textures/0059-05.png').write_bytes(png((0, 255, 0, 255)))
            return result
        with mock.patch.object(equivalence, '_canonical', side_effect=mutate_after_comparison):
            self.assert_atomic_error('changed during comparison')

    def test_binder_attaches_only_explicit_current_decisions_and_is_idempotent(self):
        self.source.pop('presentation_equivalent_to')
        bind = equivalence.bind_equivalence_decisions
        self.assertEqual({'bound_equivalence_count': 1}, bind(self.reviews, self.root, self.decisions_path))
        self.assertEqual(self.target['name'], self.source['presentation_equivalent_to'])
        before = copy.deepcopy(self.reviews)
        bind(self.reviews, self.root, self.decisions_path)
        self.assertEqual(before, self.reviews)
        self.write_decisions(fingerprint='0' * 64)
        self.assertEqual({'bound_equivalence_count': 0}, bind(self.reviews, self.root, self.decisions_path))
        self.assertNotIn('presentation_equivalent_to', self.source)

    def test_binder_uses_full_model_record_and_requires_explicit_intent(self):
        bind = equivalence.bind_equivalence_decisions
        self.models[1]['source_face_count'] = 2
        self.write_manifest()
        self.refresh()
        self.assertEqual(0, bind(self.reviews, self.root, self.decisions_path)['bound_equivalence_count'])
        self.assertNotIn('presentation_equivalent_to', self.source)
        self.write_decisions()
        decisions = json.loads(self.decisions_path.read_text())
        row = decisions['models']['04:0059:05']
        row.pop('presentation_equivalent_to')
        row['reason'] = 'Same exported geometry as object-bank04-0006-05-rom'
        self.decisions_path.write_text(json.dumps(decisions))
        self.assertEqual(0, bind(self.reviews, self.root, self.decisions_path)['bound_equivalence_count'])
        self.assertNotIn('presentation_equivalent_to', self.source)

    def test_binder_bad_current_target_name_or_mismatched_source_is_atomic(self):
        for kind in ('syntax', 'source', 'identity', 'stale-source'):
            with self.subTest(kind=kind):
                self.setUp()
                if kind == 'syntax': self.write_decisions(target='../not-a-target')
                elif kind == 'source': self.source['source'] = self.target['source']
                elif kind == 'identity': self.source['entry'] = 58
                else: (self.directory / 'textures/0059-05.png').write_bytes(png((0, 0, 255, 255)))
                before = copy.deepcopy(self.reviews)
                if kind == 'identity':
                    # No decision for a different identity can carry old intent.
                    equivalence.bind_equivalence_decisions(self.reviews, self.root, self.decisions_path)
                    self.assertNotIn('presentation_equivalent_to', self.source)
                else:
                    with self.assertRaises(ValueError):
                        equivalence.bind_equivalence_decisions(self.reviews, self.root, self.decisions_path)
                    self.assertEqual(before, self.reviews)

    def test_binder_clears_old_intent_when_review_becomes_ineligible(self):
        self.source['review_status'] = 'review-needed'
        self.assertEqual(0, equivalence.bind_equivalence_decisions(
            self.reviews, self.root, self.decisions_path)['bound_equivalence_count'])
        self.assertNotIn('presentation_equivalent_to', self.source)


if __name__ == '__main__':
    unittest.main()
