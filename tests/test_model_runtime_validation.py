from __future__ import annotations

import copy
import json
import struct
import tempfile
import unittest
from pathlib import Path

from scripts import model_runtime_validation as runtime


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


if __name__ == '__main__':
    unittest.main()
