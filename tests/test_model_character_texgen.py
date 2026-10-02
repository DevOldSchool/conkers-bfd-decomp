"""Source guards and vertex-load cache semantics for texgen inspection."""
import copy
import hashlib
import json
import struct
import subprocess
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

from scripts import model_character_texgen as texgen


class TexgenSourceTests(unittest.TestCase):
    def synthetic_source(self):
        raw = bytearray(0x3080)
        raw[0x100:0x10C] = bytes([20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 127])
        commands = [(0xDC38000E, 0x100), (0xD9F3FFFF, 0),
                    (0x01003006, 0x01000038),  # Load ordinary vertices in slots0..2.
                    (0xD9FFFFFF, 0x40000),
                    (0x0100300C, 0x01000068),  # Load generated vertices in slots3..5.
                    (0xD9FBFFFF, 0)]           # Clear before drawing cached generated vertices.
        commands += [(0x0506080A, 0)] * 103 + [(0x05000204, 0)] * 342
        for index, command in enumerate(commands):
            struct.pack_into('>II', raw, 0x1D60 + index * 8, *command)
        vertices = [SimpleNamespace(x=i, y=i+1, z=i+2, flag=30+i, s=0, t=0) for i in range(6)]
        faces = ((3, 4, 5),) * 103 + ((0, 1, 2),) * 342
        normals = [tuple((raw[0x100+i*2], raw[0x101+i*2], 30+i) for i in face) for face in faces]
        geometry = SimpleNamespace(vertices=vertices, faces=faces, face_normal_bytes=normals,
                                   material_runs=[SimpleNamespace(first_face=0, face_count=103),
                                                  SimpleNamespace(first_face=103, face_count=342)])
        expected = {'model_sha256': hashlib.sha256(raw).hexdigest(), 'affected_runs': {'0': 103}}
        return bytes(raw), geometry, expected

    def test_texgen_is_latched_at_load_and_retained_when_mode_clears(self):
        raw, geometry, expected = self.synthetic_source()
        with patch.object(texgen.models, 'parse_character_model_geometry', return_value=(geometry, None)), \
                patch.object(texgen.models, 'texture_coordinate_state', return_value={'width': 32}):
            proof = texgen.replay(raw, expected)
        self.assertEqual(103, len(proof['faces']))
        self.assertEqual(445, proof['source_face_count'])
        self.assertEqual(list(range(103)), [row['face'] for row in proof['faces']])
        self.assertEqual([80, 90, 33], proof['faces'][0]['corners'][0]['normal_bytes'])
        self.assertTrue(all(c['texgen'] for r in proof['faces'] for c in r['corners']))
        self.assertEqual([3, 4, 5], proof['faces'][0]['corners'][0]['source_position'])

    def test_model_mutation_fails_before_parser(self):
        raw, _, expected = self.synthetic_source()
        for position in (0, 0x100, 0x1D60, len(raw)-1):
            changed = bytearray(raw)
            changed[position] ^= 1
            with self.subTest(position=position), patch.object(texgen.models, 'parse_character_model_geometry') as parser:
                with self.assertRaisesRegex(ValueError, 'model source changed'):
                    texgen.replay(changed, expected)
                parser.assert_not_called()

    def test_source_normal_disagreement_is_rejected(self):
        raw, geometry, expected = self.synthetic_source()
        geometry.face_normal_bytes[0] = ((0, 0, 0),) * 3
        with patch.object(texgen.models, 'parse_character_model_geometry', return_value=(geometry, None)):
            with self.assertRaisesRegex(ValueError, 'normal replay differs'):
                texgen.replay(raw, expected)

    def test_neutral_joint_world_translation_and_changed_rotation_guard(self):
        doc = {'nodes': [{'translation': [1, 2, 3], 'children': [1]},
                         {'translation': [4, 5, 6], 'extras': {'matrixIndex': 6}}]}
        self.assertEqual({'6': [5, 7, 9]}, texgen.neutral_translations(doc))
        for transform in ('rotation', 'scale', 'matrix'):
            changed = copy.deepcopy(doc)
            changed['nodes'][0][transform] = []
            with self.assertRaisesRegex(ValueError, 'translation-only'):
                texgen.neutral_translations(changed)
        doc['nodes'][1]['children'] = [0]
        with self.assertRaisesRegex(ValueError, 'cyclic'):
            texgen.neutral_translations(doc)

    def attribute_fixture(self):
        binary = struct.pack('<6f', 0, 0, 0.5, 0.5, 1, 1) + struct.pack('<309H', *([0, 1, 2]*103))
        doc = {'buffers': [{'uri': 'original.bin', 'byteLength': len(binary)}],
               'bufferViews': [{'buffer': 0, 'byteOffset': 0, 'byteLength': 24},
                               {'buffer': 0, 'byteOffset': 24, 'byteLength': 618}],
               'accessors': [{'bufferView': 0, 'componentType': 5126, 'count': 3, 'type': 'VEC2'},
                             {'bufferView': 1, 'componentType': 5123, 'count': 309, 'type': 'SCALAR'}],
               'meshes': [{'primitives': [{'attributes': {'TEXCOORD_0': 0}, 'indices': 1,
                                          'material': 20, 'extras': {'firstFace': 0, 'faceCount': 103}}]}],
               'animations': [{'name': 'source clip preserved separately'}]}
        proof = {'material_runs': {'20': 20},
                 'faces': [{'face': i, 'material_run': 20,
                            'corners': [{'normal_bytes': n} for n in [(1, 2, 3), (64, 64, 0), (-128, 0, 0)]]}
                           for i in range(103)]}
        return doc, binary, proof

    def test_raw_nonunit_normals_append_without_changing_st_or_original_document(self):
        doc, binary, proof = self.attribute_fixture()
        original = copy.deepcopy(doc)
        updated, output, spans = texgen.add_attribute(doc, binary, proof)
        self.assertEqual(doc, original)
        self.assertEqual(binary, output[:len(binary)])
        self.assertEqual(doc['accessors'], updated['accessors'][:2])
        self.assertNotIn('animations', updated)
        self.assertIn('animations', doc)
        attribute = updated['meshes'][0]['primitives'][0]['attributes'][texgen.ATTRIBUTE]
        self.assertEqual(0, updated['bufferViews'][updated['accessors'][attribute]['bufferView']]['byteOffset'] % 4)
        normals = texgen.accessor(updated, output, attribute)
        self.assertAlmostEqual(-128/127, normals[2][0])
        self.assertLess(sum(x*x for x in normals[0]), 0.001)
        self.assertEqual([{'material_index': 20, 'source_material_run': 20,
                           'first_face': 0, 'face_count': 103}], spans)

    def test_conflicting_corner_normal_and_changed_material_span_fail(self):
        doc, binary, proof = self.attribute_fixture()
        proof['faces'][1]['corners'][0]['normal_bytes'] = [5, 6, 7]
        with self.assertRaisesRegex(ValueError, 'conflicting texgen normal'):
            texgen.add_attribute(doc, binary, proof)
        doc, binary, proof = self.attribute_fixture()
        doc['meshes'][0]['primitives'][0]['material'] = 21
        with self.assertRaisesRegex(ValueError, 'material span changed'):
            texgen.add_attribute(doc, binary, proof)

    def test_supported_command_help_works_without_rom_or_blender(self):
        result = subprocess.run(['./conker', 'model-assets', 'texgen-inspection', '--help'],
                                cwd=texgen.ROOT, capture_output=True, text=True)
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertIn('--verify', result.stdout)
        self.assertIn('neutral-pose', result.stdout)

    def test_publication_admission_rejects_changes_during_fresh_verify(self):
        output = texgen.ROOT / 'build/texgen-test-output'
        contents = {'character66-neutral-texgen.blend': b'BLENDER', 'three-quarter.png': b'PNG'}
        snapshots = [({'files': {'x': 'before'}}, contents, 'neutral'),
                     ({'files': {'x': 'after'}}, contents, 'neutral')]
        with patch.object(texgen, '_artifact_snapshot', side_effect=snapshots), \
                patch.object(texgen.subprocess, 'run', return_value=SimpleNamespace(returncode=0, stdout='', stderr='')) as run:
            with self.assertRaisesRegex(ValueError, 'changed during verification'):
                texgen.inspection_artifact(output)
            command = run.call_args.args[0]
            self.assertIn('--disable-autoexec', command)
            self.assertIn('--python-exit-code', command)
            self.assertIn('--verify', command)

    def test_publication_preflight_rejects_changed_admitted_bytes(self):
        with patch.object(texgen, '_artifact_snapshot', return_value=({'files': {'x': 'changed'}}, {}, 'neutral')):
            with self.assertRaisesRegex(ValueError, 'before publication'):
                texgen.inspection_artifact_current(texgen.ROOT / 'build/texgen-test-output', {'files': {'x': 'original'}})

    def test_contract_guard_rejects_mutation(self):
        raw = texgen.CONTRACT.read_bytes()
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / 'contract.json'
            path.write_bytes(raw + b' ')
            with patch.object(texgen, 'CONTRACT', path):
                with self.assertRaisesRegex(ValueError, 'contract changed'):
                    texgen.contract()


if __name__ == '__main__':
    unittest.main()
