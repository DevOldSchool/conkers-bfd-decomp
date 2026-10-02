import copy
import json
import math
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import model_character_animated_texgen as animated


def fixture():
    doc = {'nodes': [{'translation': [0, 0, 0], 'extras': {'matrixIndex': i}} for i in range(28)],
           'skins': [{'joints': list(range(28))}], 'meshes': [{'primitives': []}],
           'accessors': [], 'bufferViews': [], 'animations': []}
    data = bytearray()
    def add(rows, kind, component=5126):
        width = {'SCALAR': 1, 'VEC3': 3, 'VEC4': 4, 'MAT4': 16}[kind]
        payload = b''.join(struct.pack('<'+{5123: 'H', 5126: 'f'}[component]*width, *r) for r in rows)
        vi = len(doc['bufferViews']); doc['bufferViews'].append({'buffer': 0, 'byteOffset': len(data), 'byteLength': len(payload)})
        data.extend(payload); ai = len(doc['accessors']); doc['accessors'].append({'bufferView': vi, 'count': len(rows), 'type': kind, 'componentType': component})
        return ai
    identity = tuple(float(i % 5 == 0) for i in range(16))
    doc['skins'][0]['inverseBindMatrices'] = add([identity]*28, 'MAT4')
    proof = {'joint_world_translations': {str(i): [0, 0, 0] for i in range(28)},
             'affected_materials': {str(k): k for k in (20, 21, 31, 32, 33, 34)}, 'faces': []}
    for material, first, count, default in [(20, 279, 21, 19), (21, 300, 2, 6), (31, 365, 41, 19),
                                           (32, 406, 14, 19), (33, 420, 19, 6), (34, 439, 6, 13)]:
        joints = []
        for fi in range(first, first+count):
            corners = []
            for k in range(3):
                j = 13 if 285 <= fi <= 290 and k == 2 else default
                joints.append((j, 0, 0, 0)); corners.append({'matrix_index': j, 'source_position': [0, 0, 0]})
            proof['faces'].append({'face': fi, 'corners': corners})
        attrs = {'JOINTS_0': add(joints, 'VEC4', 5123), 'WEIGHTS_0': add([(1, 0, 0, 0)]*len(joints), 'VEC4'),
                 'POSITION': add([(0, 0, 0)]*len(joints), 'VEC3')}
        doc['meshes'][0]['primitives'].append({'material': material, 'attributes': attrs,
            'indices': add([(i,) for i in range(len(joints))], 'SCALAR', 5123), 'extras': {'firstFace': first}})
    doc['meshes'][0]['primitives'].append({'material': 0, 'attributes': {
        'JOINTS_0': add([(0, 0, 0, 0)]*220, 'VEC4', 5123), 'WEIGHTS_0': add([(1, 0, 0, 0)]*220, 'VEC4')}})
    for ci, keys in enumerate((11, 10, 30)):
        times = add([(i/30,) for i in range(keys)], 'SCALAR')
        rotations = add([(0, 0, math.sin(i*.025), math.cos(i*.025)) for i in range(keys)], 'VEC4')
        positions = add([(i, 0, 0) for i in range(keys)], 'VEC3')
        channels = [{'sampler': 0, 'target': {'node': i, 'path': 'rotation'}} for i in range(28)]
        channels += [{'sampler': 1, 'target': {'node': i, 'path': 'translation'}} for i in range((2, 3, 2)[ci])]
        doc['animations'].append({'name': f'original-{ci}', 'channels': channels,
            'samplers': [{'input': times, 'output': rotations, 'interpolation': 'LINEAR'},
                         {'input': times, 'output': positions, 'interpolation': 'LINEAR'}]})
    return doc, bytes(data), proof


class AnimationDomainTests(unittest.TestCase):
    def setUp(self):
        self.doc, self.binary, self.proof = fixture()

    def test_exact_one_hot_corners_and_mixed_joint_triangles(self):
        result = animated.animation_contract(self.doc, self.binary, self.proof)
        self.assertEqual(result['weighted_vertices'], 529)
        self.assertEqual(result['source_corners'], 309)
        self.assertEqual(result['mixed_joint_faces'], [285, 286, 287, 288, 289, 290])
        self.assertEqual([len(c['sample_times']) for c in result['clips']], [31, 28, 88])

    def test_reject_blended_weight_in_affected_vertex(self):
        a = self.doc['accessors'][self.doc['meshes'][0]['primitives'][0]['attributes']['WEIGHTS_0']]
        offset = self.doc['bufferViews'][a['bufferView']]['byteOffset']
        changed = bytearray(self.binary); struct.pack_into('<4f', changed, offset, .5, .5, 0, 0)
        with self.assertRaisesRegex(ValueError, 'one-hot'):
            animated.animation_contract(self.doc, changed, self.proof)

    def test_reject_wrong_source_corner_joint(self):
        self.proof['faces'][0]['corners'][0]['matrix_index'] = 6
        with self.assertRaisesRegex(ValueError, 'corner joint'):
            animated.animation_contract(self.doc, self.binary, self.proof)

    def test_reject_scale_and_nonunit_quaternion(self):
        changed = copy.deepcopy(self.doc); changed['animations'][0]['channels'][0]['target']['path'] = 'scale'
        with self.assertRaisesRegex(ValueError, 'scale channel'):
            animated.animation_domain(changed, self.binary)
        a = self.doc['accessors'][self.doc['animations'][0]['samplers'][0]['output']]
        changed = bytearray(self.binary); offset = self.doc['bufferViews'][a['bufferView']]['byteOffset']
        struct.pack_into('<4f', changed, offset, 0, 0, 0, 2)
        with self.assertRaisesRegex(ValueError, 'unit length'):
            animated.animation_domain(self.doc, changed)

    def test_reject_duplicate_channel_and_unordered_keys(self):
        changed = copy.deepcopy(self.doc); changed['animations'][0]['channels'][1]['target']['node'] = 0
        with self.assertRaisesRegex(ValueError, 'duplicate'):
            animated.animation_domain(changed, self.binary)
        sampler = self.doc['animations'][0]['samplers'][0]
        a = self.doc['accessors'][sampler['input']]; offset = self.doc['bufferViews'][a['bufferView']]['byteOffset']
        changed = bytearray(self.binary); struct.pack_into('<f', changed, offset+4, 0)
        with self.assertRaisesRegex(ValueError, 'animation times'):
            animated.animation_domain(self.doc, changed)

    def test_spherical_oracle_has_literal_halfway_rotation(self):
        q = animated.slerp([0, 0, 0, 1], [0, 0, 1, 0], .5)
        self.assertAlmostEqual(q[2], math.sqrt(.5)); self.assertAlmostEqual(q[3], math.sqrt(.5))
        point = animated.transform(animated.local_matrix([3, 4, 5], q), [1, 0, 0, 1])
        for actual, expected in zip(point, [3, 5, 5, 1]): self.assertAlmostEqual(actual, expected)
        self.assertEqual(animated.slerp([0, 0, 0, 1], [0, 0, 0, -1], .37), [0, 0, 0, 1])

    def test_source_preparation_preserves_every_neutral_byte_and_clip(self):
        base = {'source/geometry/0066-00.gltf': animated.encode(self.doc), 'source/geometry/0066-00.bin': self.binary,
                'geometry/character66-texgen.gltf': animated.encode({k:v for k,v in self.doc.items() if k!='animations'}),
                'source-proof.json': b'proof', 'source/texture.png': b'original pixels'}
        with patch.object(animated.neutral, 'build_files', return_value=(base, self.proof)):
            files, audit = animated.build_files()
        self.assertEqual({k:files[k] for k in base}, base)
        self.assertEqual(json.loads(files[animated.ANIMATED_SOURCE])['animations'], self.doc['animations'])
        self.assertEqual(audit['neutral_source_proof_sha256'], animated.sha(b'proof'))
        self.assertEqual(set(files)-set(base), {animated.ANIMATED_SOURCE, 'animation-proof.json'})


class IOTests(unittest.TestCase):
    def test_existing_output_refuses_without_worker_or_writes(self):
        with tempfile.TemporaryDirectory() as tmp:
            output = Path(tmp); marker = output/'untouched'; marker.write_bytes(b'user data')
            with patch.object(animated, 'build_files', return_value=({'source': b'new'}, {})), \
                 patch.object(animated, '_checked_output', return_value=output), \
                 patch.object(animated.subprocess, 'run') as run:
                with self.assertRaises(SystemExit): animated.main(['--output', str(output)])
                run.assert_not_called()
            self.assertEqual({p.name:p.read_bytes() for p in output.iterdir()}, {'untouched': b'user data'})

    def test_stale_source_verify_fails_without_worker_or_writes(self):
        with tempfile.TemporaryDirectory() as tmp:
            output = Path(tmp); (output/'source').write_bytes(b'stale')
            with patch.object(animated, 'build_files', return_value=({'source': b'fresh'}, {})), \
                 patch.object(animated, '_checked_output', return_value=output), \
                 patch.object(animated.subprocess, 'run') as run:
                with self.assertRaises(SystemExit): animated.main(['--verify', '--output', str(output)])
                run.assert_not_called()
            self.assertEqual((output/'source').read_bytes(), b'stale')

    def test_direct_output_symlink_is_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp)/'alias'; path.symlink_to(Path(tmp)/'missing')
            with self.assertRaisesRegex(ValueError, 'symlink'): animated._checked_output(path)

    def test_worker_command_disables_autoexec_and_propagates_failure(self):
        cmd = animated._worker_command(Path('/output'), Path('/blender'), verify=True)
        self.assertIn('--disable-autoexec', cmd); self.assertIn('--verify', cmd)
        self.assertEqual(cmd[cmd.index('--python-exit-code')+1], '1')
        self.assertEqual(cmd[cmd.index('--source')+1], '/output/'+animated.ANIMATED_SOURCE)

    def test_publication_rejects_change_during_verification(self):
        result = type('Result', (), {'returncode': 0, 'stdout': '', 'stderr': ''})()
        contents = {animated.BLEND: b'blend', 'three-quarter.png': b'image'}
        with patch.object(animated, '_checked_output', return_value=Path('/output')), \
             patch.object(animated, '_artifact_snapshot', side_effect=[({'hash':1}, contents, 'scope'), ({'hash':2}, contents, 'scope')]), \
             patch.object(animated.subprocess, 'run', return_value=result):
            with self.assertRaisesRegex(ValueError, 'during verification'): animated.inspection_artifact('/output')

    def test_current_rejects_stale_publication_snapshot(self):
        with patch.object(animated, '_checked_output', return_value=Path('/output')), \
             patch.object(animated, '_artifact_snapshot', return_value=({'hash':'new'}, {}, 'scope')):
            with self.assertRaisesRegex(ValueError, 'before publication'):
                animated.inspection_artifact_current('/output', {'hash':'old'})


if __name__ == '__main__':
    unittest.main()
