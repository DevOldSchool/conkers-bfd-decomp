import copy
import json
import tempfile
import unittest
from pathlib import Path
from unittest import mock

from scripts import model_scene_assemblies as scenes


class SceneAssemblyTests(unittest.TestCase):
    def fixture(self):
        record = {'index': 7, 'sha1': 'placement', 'model_source': [4, 54, 6],
                  'position_s16_00': [120, -30, 90], 'rotation_degrees_s16_06': [0, 90, 0],
                  'scale_f32_20': [2, 3, 4]}
        scene = {'scene_index': 54, 'initial_slots': [
            {'segment': 0, 'model_sha1': 'terrain', 'consumers': [{'kind': 'conditional-display-list-submission'}]},
            {'segment': 3, 'model_sha1': 'collision', 'consumers': [{'kind': 'collision-input'}]}],
            'placement_tables': [{'bank_index': 11, 'records': [record]}]}
        return scene, {'scene_index': 54, 'exclude_models': []}

    def source(self, root, key, sha1):
        # Small independent triangle: the placement must transform its node,
        # leaving these original mesh bytes untouched in the merged buffer.
        document = {'asset': {'version': '2.0'}, 'buffers': [{'byteLength': 12}],
            'bufferViews': [{'buffer': 0, 'byteLength': 12}],
            'accessors': [{'bufferView': 0, 'componentType': 5126, 'count': 1, 'type': 'VEC3'}],
            'materials': [{'pbrMetallicRoughness': {'baseColorFactor': [1, 0, 0, 1]}}],
            'meshes': [{'primitives': [{'indices': 0, 'attributes': {'POSITION': 0}, 'material': 0}]}]}
        return (document, bytes(range(12))), {'model': list(key), 'face_count': 1}

    def test_placement_translation_scale_rotation_and_collision_exclusion(self):
        scene, selection = self.fixture()
        selected, omitted = scenes.select_instances(scene, selection)
        self.assertEqual([[4, 54, 0], [4, 54, 6]], [r['model'] for r in selected])
        self.assertEqual([4, 54, 3], omitted[0]['model'])
        matrix = selected[1]['matrix']
        self.assertEqual([120, -30, 90], matrix[12:15])
        self.assertAlmostEqual(-2, matrix[2])
        self.assertAlmostEqual(3, matrix[5])
        self.assertAlmostEqual(4, matrix[8])

    def test_static_state_omits_only_explicitly_selected_variants(self):
        scene, selection = self.fixture()
        alternative = copy.deepcopy(scene['placement_tables'][0]['records'][0])
        alternative.update(index=8, model_source=[4, 54, 7])
        scene['placement_tables'][0]['records'].append(alternative)
        selection['exclude_models'] = [{'model': [4, 54, 7], 'reason': 'damage variant'}]
        selected, omitted = scenes.select_instances(scene, selection)
        self.assertEqual(2, len(selected))
        self.assertEqual(alternative, omitted[-1]['record'])
        selection['exclude_models'][0]['model'] = [4, 54, 99]
        with self.assertRaisesRegex(ValueError, 'absent exclusion'):
            scenes.select_instances(scene, selection)

    def test_missing_renderer_or_unresolved_placement_is_rejected(self):
        scene, selection = self.fixture()
        scene['initial_slots'][0]['consumers'] = []
        with self.assertRaisesRegex(ValueError, 'rendering consumer'):
            scenes.select_instances(scene, selection)
        scene, selection = self.fixture()
        scene['placement_tables'][0]['records'][0]['model_source'] = None
        with self.assertRaisesRegex(ValueError, 'unresolved placement'):
            scenes.select_instances(scene, selection)

    def test_composition_preserves_bytes_instances_and_detects_tampering(self):
        scene, selection = self.fixture()
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            config = root / 'selection.json'
            config.write_text(json.dumps({'schema_version': 1, 'scenes': [selection]}))
            output = root / 'assemblies'
            with mock.patch.object(scenes, 'ROOT', root), \
                    mock.patch.object(scenes, 'rom_scenes', return_value=('rom', {54: scene})), \
                    mock.patch.object(scenes, 'source_model', side_effect=self.source):
                scenes.export_assemblies(config, root / 'models', output)
                self.assertEqual(2, scenes.verify_assemblies(output, fresh_rom=True)['instance_count'])
                path = output / 'geometry/scene-54.gltf'
                doc = json.loads(path.read_text())
                self.assertEqual(bytes(range(12)) * 2, path.with_suffix('.bin').read_bytes())
                self.assertEqual(12, doc['bufferViews'][1]['byteOffset'])
                self.assertEqual(1, doc['meshes'][1]['primitives'][0]['attributes']['POSITION'])
                self.assertEqual(7, doc['nodes'][1]['extras']['record']['index'])
                doc['nodes'][1]['matrix'][12] += 1
                path.write_text(json.dumps(doc))
                with self.assertRaisesRegex(ValueError, 'differs from its ROM'):
                    scenes.verify_assemblies(output)

    def test_changed_rom_placements_do_not_validate_from_manifest_alone(self):
        scene, selection = self.fixture()
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            config = root / 'selection.json'
            config.write_text(json.dumps({'schema_version': 1, 'scenes': [selection]}))
            with mock.patch.object(scenes, 'ROOT', root), \
                    mock.patch.object(scenes, 'rom_scenes', return_value=('rom', {54: scene})), \
                    mock.patch.object(scenes, 'source_model', side_effect=self.source):
                scenes.export_assemblies(config, root / 'models', root / 'assemblies')
                scene['placement_tables'][0]['records'][0]['position_s16_00'][0] += 10
                with self.assertRaisesRegex(ValueError, 'inputs differ from ROM'):
                    scenes.verify_assemblies(root / 'assemblies', fresh_rom=True)

    def test_inspection_phase_reuses_recomposition_but_fresh_phase_detects_tampering(self):
        scene, selection = self.fixture()
        other = copy.deepcopy(scene)
        other['scene_index'] = 55
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            config = root / 'selection.json'
            config.write_text(json.dumps({'schema_version': 1, 'scenes': [
                selection, {'scene_index': 55, 'exclude_models': []}]}))
            output = root / 'assemblies'
            with mock.patch.object(scenes, 'ROOT', root), \
                    mock.patch.object(scenes, 'rom_scenes', return_value=('rom', {54: scene, 55: other})), \
                    mock.patch.object(scenes, 'source_model', side_effect=self.source):
                scenes.export_assemblies(config, root / 'models', output)
                first = output / 'geometry/scene-54.gltf'
                second = output / 'geometry/scene-55.gltf'
                with mock.patch.object(scenes, 'verify_assemblies', wraps=scenes.verify_assemblies) as verify:
                    phase = {}
                    one = scenes.inspection_evidence(first, verification_cache=phase)
                    two = scenes.inspection_evidence(second, verification_cache=phase)
                    self.assertEqual((54, 55), (one['scene_index'], two['scene_index']))
                    self.assertEqual(1, verify.call_count)
                    # The independent final phase must recompose the actual bytes.
                    second.with_suffix('.bin').write_bytes(b'changed after preparation')
                    with self.assertRaisesRegex(ValueError, 'differs from its ROM'):
                        scenes.inspection_evidence(first, verification_cache={})
                    self.assertEqual(2, verify.call_count)
                    manifest = output / 'manifest.json'
                    manifest.write_text(manifest.read_text() + ' ')
                    with self.assertRaisesRegex(ValueError, 'manifest changed'):
                        scenes.inspection_evidence(first, verification_cache=phase)
