from __future__ import annotations

import copy
import json
import struct
import tempfile
import unittest
from pathlib import Path

from scripts import model_runtime_validation as runtime
from scripts import model_submitted_pose as submitted


def rig_fixture(root):
    data = bytearray()
    views, accessors = [], []

    def add(values, code, component, kind, count):
        while len(data) % 4:
            data.append(0)
        offset = len(data)
        encoded = struct.pack('<' + code * len(values), *values)
        data.extend(encoded)
        views.append({'buffer': 0, 'byteOffset': offset, 'byteLength': len(encoded)})
        accessors.append({'bufferView': len(views) - 1, 'componentType': component,
                          'type': kind, 'count': count})
        return len(accessors) - 1

    position = add([0, 0, 0, 101, 0, 0, 100, 1, 0], 'f', 5126, 'VEC3', 3)
    joints = add([0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0], 'B', 5121, 'VEC4', 3)
    weights = add([1, 0, 0, 0] * 3, 'f', 5126, 'VEC4', 3)
    indices = add([0, 1, 2], 'H', 5123, 'SCALAR', 3)
    identity = [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1]
    translated = identity.copy()
    translated[12] = -100
    inverse = add(identity + translated, 'f', 5126, 'MAT4', 2)
    document = {'asset': {'version': '2.0'}, 'buffers': [{'uri': 'mesh.bin', 'byteLength': len(data)}],
                'bufferViews': views, 'accessors': accessors,
                'skins': [{'joints': [0, 1], 'inverseBindMatrices': inverse}],
                'nodes': [{'extras': {'matrixIndex': 0}}, {'extras': {'matrixIndex': 1}},
                          {'mesh': 0, 'skin': 0}],
                'meshes': [{'primitives': [{'attributes': {'POSITION': position, 'JOINTS_0': joints,
                                                          'WEIGHTS_0': weights}, 'indices': indices,
                                           'material': 0, 'extras': {'firstFace': 0, 'faceCount': 1}}]}]}
    (root / 'mesh.bin').write_bytes(data)
    path = root / 'mesh.gltf'
    path.write_text(json.dumps(document))
    return path, document, data


def actual_triangle():
    matrix = [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [5, 6, 7, 1]]
    return [{'xyz': xyz, 'matrix_address': 0x80010000 + 64 * joint, 'matrix': matrix}
            for xyz, joint in [((0, 0, 0), 0), ((1, 0, 0), 1), ((0, 1, 0), 1)]]


class SubmittedRigTests(unittest.TestCase):
    def test_inverse_bind_and_mixed_vertex_load_matrices_match_captured_inputs(self):
        with tempfile.TemporaryDirectory() as directory:
            path, _, _ = rig_fixture(Path(directory))
            _, faces = runtime.load_rig(path)
            self.assertEqual([(0, 0, 0), (1, 0, 0), (0, 1, 0)],
                             [c['xyz'] for c in faces[0]['corners']])
            matches = runtime.match_cluster(faces, [(12, actual_triangle())], 0, 1)
            self.assertEqual(0x80010000, matches[0]['root'])
            self.assertEqual(0, matches[0]['world_error'])
            # Rotation is allowed; reversing winding is not.
            actual = actual_triangle()
            rotated = runtime.match_cluster(faces, [(12, actual[1:] + actual[:1])], 0, 1)
            self.assertEqual(1, rotated[0]['rotation'])
            self.assertIsNone(runtime.match_cluster(faces, [(12, actual[::-1])], 0, 1))

    def test_changed_vertex_or_wrong_load_matrix_cannot_match(self):
        with tempfile.TemporaryDirectory() as directory:
            path, _, _ = rig_fixture(Path(directory))
            _, faces = runtime.load_rig(path)
            wrong = actual_triangle()
            wrong[1]['xyz'] = (2, 0, 0)
            self.assertIsNone(runtime.match_cluster(faces, [(12, wrong)], 0, 1))
            wrong = actual_triangle()
            wrong[1]['matrix_address'] -= 64
            self.assertIsNone(runtime.match_cluster(faces, [(12, wrong)], 0, 1))

    def test_duplicate_faces_preserve_multiplicity_and_ambiguous_roots_fail(self):
        with tempfile.TemporaryDirectory() as directory:
            path, _, _ = rig_fixture(Path(directory))
            _, faces = runtime.load_rig(path)
            faces[1] = copy.deepcopy(faces[0])
            triangles = [(12, actual_triangle()), (13, actual_triangle())]
            self.assertEqual([0, 1], [r['face'] for r in runtime.match_cluster(faces, triangles, 0, 2)])
            self.assertIsNone(runtime.match_cluster(faces, triangles[:1], 0, 2))
            for corner in faces[1]['corners']:
                corner['joint'] += 1
            self.assertIsNone(runtime.match_cluster(faces, triangles, 0, 2))

    def test_complete_instances_require_each_face_once(self):
        matches = [{'root': root, 'face': face} for root in (100, 200) for face in (0, 1)]
        self.assertEqual(2, len(runtime.instance_coverage(matches, 2, 2)))
        self.assertEqual(2, len(runtime.instance_coverage(matches, 2, 2, {100, 200})))
        shifted = [{**row, 'root': row['root'] - 64} for row in matches]
        with self.assertRaisesRegex(ValueError, 'captured reference roots'):
            runtime.instance_coverage(shifted, 2, 2, {100, 200})
        for bad in (matches[:-1], matches + [matches[0]], matches[:2]):
            with self.subTest(matches=bad), self.assertRaises(ValueError):
                runtime.instance_coverage(bad, 2, 2)

    def test_selected_parts_require_exact_explicit_face_coverage(self):
        matches = [{'root': 100, 'face': face} for face in (1, 3)]
        self.assertEqual(1, len(runtime.instance_coverage(matches, 4, 1, {100}, {1, 3})))
        for selected in ({1}, {1, 2, 3}, {1, 5}, set()):
            with self.assertRaises(ValueError):
                runtime.instance_coverage(matches, 4, 1, {100}, selected)

    def test_rig_reader_rejects_unproven_weights_and_extra_transforms(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path, document, data = rig_fixture(root)
            weight = document['meshes'][0]['primitives'][0]['attributes']['WEIGHTS_0']
            offset = document['bufferViews'][document['accessors'][weight]['bufferView']]['byteOffset']
            struct.pack_into('<f', data, offset, 0.5)
            (root / 'mesh.bin').write_bytes(data)
            with self.assertRaisesRegex(ValueError, 'unit rigid weights'):
                runtime.load_rig(path)
            path, document, _ = rig_fixture(root)
            document['nodes'][-1]['translation'] = [5, 0, 0]
            path.write_text(json.dumps(document))
            with self.assertRaisesRegex(ValueError, 'unsupported transform'):
                runtime.load_rig(path)

    def test_wrong_rom_trace_is_rejected_before_reference_replay(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path, _, _ = rig_fixture(root)
            trace = root / 'trace.jsonl'
            trace.write_text(json.dumps({'record_type': 'session', 'normalized_sha1': 'wrong'}) + '\n')
            with self.assertRaisesRegex(ValueError, 'active ROM'):
                runtime.compare_submitted_rig({'source': str(path), 'trace': str(trace)}, 'expected', {})


def call_fixture(entry=1, source_entry=1, return_event=12, kind='caller-managed-target'):
    source = {'bank': 1, 'entry': source_entry, 'segment': 0, 'model_sha1': 'model-sha1'}
    cluster = {'static_cluster_index': 2, 'first_face': 0, 'face_count': 1,
               'material_run': 0, 'matrix_index': 0}
    candidate = {**source, 'static_cluster_index': 2, 'static_first_face': 0,
                 'triangle_count': 1, 'material_run': {'index': 0}}
    call = {'entry': entry, 'slot': 0, 'task_submission_index': 1,
            'return_event_index': return_event, 'render_pass': {'kind': kind},
            'root_matrix_address': 0x80010000, 'command_sha256': 'command-sha256',
            'part_selections': [{'model_correlation_count': 1,
                'model_sequence_resolution': {'status': 'resolved', 'source_model': source,
                                              'resolved_clusters': [cluster]}}],
            'model_correlations': [{'candidates': [candidate]}],
            'submitted_graphics': {'event_index': 13,
                'status': 'captured-range-executed-once-in-next-graphics-task'}}
    context = {'trace': {'draw_calls': [call]}, 'parts': {13: {
        7: {'candidate': candidate, 'evidence': {'return_event_index': return_event}}}}}
    case = {'target': [1, source_entry, 0], 'event_index': 13,
            'draw_call': runtime.draw_call_selector(call)}
    return case, context


class SubmittedCallTests(unittest.TestCase):
    def test_json_selector_uses_source_model_separately_from_active_entry(self):
        case, context = call_fixture(source_entry=4, kind='render-to-texture')
        case = json.loads(json.dumps(case))
        selection = runtime.select_submitted_call(case, 'model-sha1', context)
        self.assertEqual({0}, selection['source_faces'])
        self.assertEqual(4, selection['evidence']['source_model']['entry'])
        self.assertEqual(1, selection['evidence']['selector']['entry'])
        self.assertEqual({7}, set(selection['clusters']))
        self.assertEqual(0x80010000, selection['root'])

    def test_missing_duplicate_or_changed_selector_fails_closed(self):
        for key, value in [('entry', 4), ('slot', 3), ('return_event_index', 9),
                           ('task_submission_index', 0), ('render_pass', 'render-to-texture')]:
            case, context = call_fixture()
            case['draw_call'][key] = value
            with self.subTest(key=key), self.assertRaisesRegex(ValueError, 'exactly one'):
                runtime.select_submitted_call(case, 'model-sha1', context)
        for calls in ([], [call_fixture()[1]['trace']['draw_calls'][0]] * 2):
            case, context = call_fixture()
            context['trace']['draw_calls'] = calls
            with self.assertRaisesRegex(ValueError, 'exactly one'):
                runtime.select_submitted_call(case, 'model-sha1', context)

    def test_submission_source_and_instance_identity_are_pinned(self):
        changes = [lambda case, ctx: case.update(event_index=6),
                   lambda case, ctx: ctx['trace']['draw_calls'][0].pop('submitted_graphics'),
                   lambda case, ctx: ctx['trace']['draw_calls'][0]['submitted_graphics'].update(status='unproven'),
                   lambda case, ctx: case.update(target=[1, 4, 0]),
                   lambda case, ctx: case.update(expected_instances=2),
                   lambda case, ctx: case.update(palette_roots=['0x80010040']),
                   lambda case, ctx: case.update(palette_roots=[])]
        for change in changes:
            case, context = call_fixture()
            change(case, context)
            with self.assertRaises(ValueError):
                runtime.select_submitted_call(case, 'model-sha1', context)
        case, context = call_fixture()
        with self.assertRaisesRegex(ValueError, 'another source model'):
            runtime.select_submitted_call(case, 'changed-model-sha1', context)

    def test_missing_extra_and_changed_selected_cluster_evidence_fails(self):
        changes = [lambda ctx: ctx['parts'].clear(),
                   lambda ctx: ctx['parts'][13].update({8: copy.deepcopy(ctx['parts'][13][7])}),
                   lambda ctx: ctx['parts'][13][7]['candidate'].update(entry=4),
                   lambda ctx: ctx['parts'][13][7]['candidate'].update(static_first_face=1),
                   lambda ctx: ctx['parts'][13][7]['evidence'].update(return_event_index=9)]
        for change in changes:
            case, context = call_fixture()
            change(context)
            with self.assertRaisesRegex(ValueError, 'submitted clusters exactly'):
                runtime.select_submitted_call(case, 'model-sha1', context)

    def test_partial_call_is_not_accepted_by_complete_rig_consumer(self):
        with tempfile.TemporaryDirectory() as directory:
            path, _, _ = rig_fixture(Path(directory))
            case, context = call_fixture()
            case['source'] = str(path)
            # This is a valid selected source span, but not this complete rig.
            context['trace']['draw_calls'][0]['part_selections'][0][
                'model_sequence_resolution']['resolved_clusters'][0]['first_face'] = 1
            context['parts'][13][7]['candidate']['static_first_face'] = 1
            with self.assertRaisesRegex(ValueError, 'partial composition'):
                runtime.submitted_rig_reference(case, 'rom-sha1', {'model_sha1': 'model-sha1'},
                                                call_context=context)
            with self.assertRaisesRegex(ValueError, 'cannot combine'):
                runtime.submitted_rig_reference(case, 'rom-sha1', {}, {'clusters': {}}, call_context=context)

    def test_discovery_separates_calls_and_preserves_unattributed_effects(self):
        _, context = call_fixture()
        _, offscreen = call_fixture(source_entry=4, return_event=9, kind='render-to-texture')
        context['trace']['draw_calls'].extend(offscreen['trace']['draw_calls'])
        plans = submitted.discovery_plans(context, 13, 6, {(1, 1, 0), (1, 4, 0), (1, 115, 0)})
        self.assertEqual([[1, 1, 0], [1, 4, 0], [1, 115, 0]], [p['target'] for p in plans])
        self.assertEqual(['caller-managed-target', 'render-to-texture'],
                         [p['draw_call']['render_pass'] for p in plans[:2]])
        self.assertNotIn('draw_call', plans[2])
        # Calls from later in the trace do not suppress an earlier unpaired task.
        self.assertEqual([{'target': [1, 1, 0]}],
                         submitted.discovery_plans(context, 0, -1, {(1, 1, 0)}))

    def test_export_checker_requires_matching_selected_call_provenance(self):
        with tempfile.TemporaryDirectory() as directory:
            path, document, _ = rig_fixture(Path(directory))
            case, context = call_fixture()
            evidence = runtime.select_submitted_call(case, 'model-sha1', context)['evidence']
            for extra in ({}, {'submittedPose': {'selectedCall': {**evidence, 'submitted_event_index': 6}}}):
                document['extras'] = extra
                path.write_text(json.dumps(document))
                with self.assertRaisesRegex(ValueError, 'selected-call evidence'):
                    submitted.compare_pose(path, {'selected_call': evidence}, 0x80010000, None, {})

    def test_missing_pair_or_unresolved_parts_never_fall_back_for_same_source(self):
        for unresolved in (False, True):
            _, context = call_fixture()
            call = context['trace']['draw_calls'][0]
            if unresolved:
                call['part_selections'] = []
            else:
                call.pop('submitted_graphics')
            plans = submitted.discovery_plans(context, 13, 6, {(1, 1, 0), (1, 115, 0)})
            self.assertEqual(2, len(plans))
            self.assertIn('reason', plans[0])
            self.assertEqual({'target': [1, 115, 0]}, plans[1])


if __name__ == '__main__':
    unittest.main()
