"""Captured appearance contract identity/mutation tests; ROM execution is separate."""
import copy
import hashlib
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch
from scripts import model_scene60_appearance as scene


class Scene60AppearanceTests(unittest.TestCase):
    def test_canonical_contract_is_pinned_and_scope_is_exact(self):
        evidence = scene.contract()
        scene.guard(evidence)
        self.assertEqual('scene60-captured-primary-opacity255', scene.PRESET)
        self.assertEqual('model-scene60-captured-appearance.json', scene.CONTRACT_PATH.name)
        self.assertEqual(scene.CONTRACT_SHA256, hashlib.sha256(scene.CONTRACT_PATH.read_bytes()).hexdigest())
        self.assertEqual({'154', '162'}, set(evidence['models']))
        self.assertEqual(20, sum(len(model['runs']) for model in evidence['models'].values()))
        self.assertEqual(384, sum(model['blocked_faces'] for model in evidence['models'].values()))
        self.assertEqual([403, 508], [evidence['models'][entry]['selected_primary_faces'] for entry in ('154', '162')])

    def test_packet_and_backing_evidence_hashes_are_pinned(self):
        evidence = scene.contract()
        self.assertEqual('0bebc53e7ac41acd51c849b891b869d3b784f4d402a8ac27909ff5551a6a887f', evidence['provenance']['packet_sha256'])
        common = evidence['captured_state_common']
        for state in evidence['captured_states'].values():
            numeric = {'other_mode': [int(word, 16) for word in state['other_mode']],
                       'combine_mode': [int(word, 16) for word in state['combine_mode']],
                       'convert_mode': [int(word, 16) for word in common['convert_mode']],
                       'colours': common['colours']}
            self.assertEqual(state['state_subset_sha256'], hashlib.sha256(json.dumps(numeric, sort_keys=True).encode()).hexdigest())
        for entry, model in evidence['models'].items():
            self.assertEqual(model['blocked_faces'], sum(row[2] for row in model['runs']))
            self.assertEqual({str(row[0]) for row in model['runs']}, set(evidence['local_source_guards']['material_run_sha256'][entry]))

    def test_contract_bytes_cannot_be_replaced_by_self_consistent_metadata(self):
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / 'mutated.json'
            data = json.loads(scene.CONTRACT_PATH.read_bytes())
            data['models']['154']['caller_arguments'][0] = 254
            path.write_text(json.dumps(data, indent=2) + '\n')
            with patch.object(scene, 'CONTRACT_PATH', path), self.assertRaisesRegex(ValueError, 'contract changed'):
                scene.contract()

    def test_guard_rejects_context_state_source_and_scope_mutations(self):
        mutations = {
            'entry155': lambda e: e['models'].update({'155': e['models'].pop('154')}),
            'opacity': lambda e: e['models']['154']['caller_arguments'].__setitem__(0, 254),
            'mode': lambda e: e['models']['162']['selected_part'].update(draw_mode=2),
            'secondary': lambda e: e['models']['162']['selected_part'].update(secondary_model=154),
            'coverage': lambda e: e['captured_state_common'].update(alpha_cvg_select=False),
            'conversion': lambda e: e['captured_state_common'].update(K5=0),
            'flat_payload': lambda e: e['textures']['903'].update(flat_sha256='0' * 64),
            'run_guard': lambda e: e['local_source_guards']['material_run_sha256']['154'].update({'0': '0' * 64}),
            'task': lambda e: e['task'].update(event=9),
            'scope': lambda e: e.update(inspection_scope='universal default'),
        }
        evidence = scene.contract()
        for name, mutate in mutations.items():
            changed = copy.deepcopy(evidence)
            mutate(changed)
            with self.subTest(mutation=name), self.assertRaisesRegex(ValueError, 'evidence changed'):
                scene.guard(changed)

    def test_shared_export_rejects_changed_contract_before_ROM_access(self):
        evidence = scene.contract()
        evidence['inspection_scope'] = 'universal default'
        with patch.object(scene.models, 'resolve_rom') as resolve:
            with self.assertRaisesRegex(ValueError, 'evidence changed'):
                scene.build_files(None, None, evidence)
            resolve.assert_not_called()

    def test_shared_export_accepts_independently_pinned_library_contract(self):
        from scripts import model_library_bat155_appearance as library
        scene.guard_evidence(library.contract())
        changed = library.contract()
        changed['models']['155']['caller_arguments'][0] = 254
        with self.assertRaisesRegex(ValueError, 'evidence changed'):
            scene.guard_evidence(changed)

    def test_preservation_guard_rejects_geometry_and_buffer_changes(self):
        before = {key: [] for key in scene.PRESERVED_DOCUMENT_FIELDS}
        for key in scene.PRESERVED_DOCUMENT_FIELDS:
            changed = copy.deepcopy(before)
            changed[key] = [{'changed': True}]
            with self.subTest(field=key), self.assertRaises(ValueError):
                scene.guard_document_preservation(before, changed)
        with self.assertRaises(ValueError):
            scene.guard_document_preservation(before, before, b'old', b'new')


if __name__ == '__main__':
    unittest.main()
