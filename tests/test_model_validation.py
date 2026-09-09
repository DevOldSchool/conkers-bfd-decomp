from __future__ import annotations

import json
import hashlib
import shutil
import struct
import subprocess
import tempfile
import unittest
from dataclasses import replace
from pathlib import Path
from types import SimpleNamespace
from unittest import mock

from scripts import model_assets as models, model_validation as validation, texture_assets


def geometry():
    vertices = b''.join(struct.pack('>hhhHhh4B', x, y, 0, 0, x * 32, y * 32, 255, 255, 255, 255)
                        for x, y in ((0, 0), (10, 0), (0, 10)))
    commands = b''.join(struct.pack('>II', a, b) for a, b in
        ((0xD7000000, 0xFFFFFFFF), (0x01003006, 0x01000000), (0x05000204, 0), (0xDF000000, 0)))
    return models.parse_model_geometry(struct.pack('>10I', 0x28 + len(vertices), len(commands),
        0, 0, 0, 0, 0, 0, 0, 0x80000000) + vertices + commands)


class ModelValidationTests(unittest.TestCase):
    def export(self, root, source):
        document, binary = models.encode_gltf(0, 0, source, output_stem='model')
        path = root / 'model.gltf'
        path.write_bytes(document)
        path.with_suffix('.bin').write_bytes(binary)
        runs = [{'face_count': run.face_count, 'runtime_material': None} for run in source.material_runs]
        return path, json.loads(document), runs

    def test_numeric_comparison_detects_changed_positions_and_triangle_order(self):
        with tempfile.TemporaryDirectory() as directory:
            source = geometry()
            path, document, runs = self.export(Path(directory), source)
            self.assertEqual(1, validation.compare_geometry(path, source, None, runs)['faces'])
            original = path.with_suffix('.bin').read_bytes()
            changed = bytearray(original)
            struct.pack_into('<f', changed, 0, 100)
            path.with_suffix('.bin').write_bytes(changed)
            with self.assertRaisesRegex(ValueError, 'position differs'):
                validation.compare_geometry(path, source, None, runs)
            primitive = document['meshes'][0]['primitives'][0]
            accessor = document['accessors'][primitive['indices']]
            offset = document['bufferViews'][accessor['bufferView']]['byteOffset']
            changed = bytearray(original)
            struct.pack_into('<3H', changed, offset, 0, 2, 1)
            path.with_suffix('.bin').write_bytes(changed)
            with self.assertRaisesRegex(ValueError, 'position differs'):
                validation.compare_geometry(path, source, None, runs)

    def test_accessor_rejects_overrun_nonfinite_and_invalid_stride(self):
        with tempfile.TemporaryDirectory() as directory:
            _, document, _ = self.export(Path(directory), geometry())
            data = (Path(directory) / 'model.bin').read_bytes()
            bad = json.loads(json.dumps(document))
            bad['accessors'][0]['count'] += 1
            with self.assertRaisesRegex(ValueError, 'buffer view'):
                validation.accessor(bad, 0, [data])
            bad = json.loads(json.dumps(document))
            bad['bufferViews'][0]['byteStride'] = 1
            with self.assertRaisesRegex(ValueError, 'stride'):
                validation.accessor(bad, 0, [data])
            changed = bytearray(data)
            struct.pack_into('<f', changed, 0, float('nan'))
            with self.assertRaisesRegex(ValueError, 'non-finite'):
                validation.accessor(document, 0, [changed])

    def test_empty_model_keeps_record_without_invalid_empty_mesh(self):
        source = replace(geometry(), faces=(), material_runs=(), face_command_offsets=(),
                         face_matrix_indices=(), face_cull_modes=())
        with tempfile.TemporaryDirectory() as directory:
            path, document, runs = self.export(Path(directory), source)
            self.assertNotIn('meshes', document)
            self.assertNotIn('materials', document)
            self.assertTrue(document['nodes'])
            self.assertEqual(0, document['extras']['drawableFaceCount'])
            self.assertEqual(0, validation.compare_geometry(path, source, None, runs)['faces'])

    def test_image_difference_is_generated_without_replacing_reference(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            reference, current, difference = (root / name for name in ('before.png', 'after.png', 'diff.png'))
            original = texture_assets.encode_rgba_png(2, 1, bytes((0, 0, 0, 255, 20, 20, 20, 255)))
            reference.write_bytes(original)
            current.write_bytes(original)
            self.assertEqual('passed', validation.compare_images(reference, current, difference)['status'])
            current.write_bytes(texture_assets.encode_rgba_png(2, 1, bytes((0, 0, 0, 255, 30, 20, 20, 255))))
            result = validation.compare_images(reference, current, difference)
            self.assertEqual(('incomplete', 1, 10), (result['status'], result['changed_pixels'], result['max_channel_delta']))
            self.assertTrue(difference.is_file())
            self.assertEqual(original, reference.read_bytes())

    def test_missing_evidence_never_becomes_a_success_or_cache_hit_for_new_key(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'cache.json'
            validation.write(path, {'key': 'old-code-and-input', 'result': {'status': 'incomplete'}})
            self.assertEqual('incomplete', validation.cached(path, 'old-code-and-input')['status'])
            self.assertIsNone(validation.cached(path, 'new-code-and-input'))
            self.assertEqual('incomplete', validation.summarize_status({}))
            self.assertEqual('failed', validation.summarize_status({'a': {'status': 'incomplete'}, 'b': {'status': 'failed'}}))

    def test_evidence_dimensions_stay_independent(self):
        model = {'scene_association': {'status': 'resolved'}, 'semantic_name': {'status': 'unknown'}}
        run = {name: {'status': state} for name, state in
               (('static_texture', 'resolved'), ('runtime_material', 'observed'),
                ('dynamic_segment_8', 'missing'), ('character_composition', 'partial'),
                ('attachment_composition', 'not-applicable'))}
        result = validation.evidence_checks(model, [run])
        self.assertEqual('passed', result['static_texture']['status'])
        self.assertEqual('passed', result['runtime_material']['status'])
        self.assertEqual('incomplete', result['dynamic_segment_8']['status'])
        self.assertEqual('incomplete', result['character_composition']['status'])
        self.assertEqual('incomplete', result['semantic_name']['status'])

    def test_captured_pixel_extent_excludes_palette_and_must_cover_complete_image(self):
        payload = bytes(range(96))
        run = SimpleNamespace(render_tile=(0xF5080200, 0))  # Eight-byte stride.
        texture = SimpleNamespace(width=8, height=8, size=1, format=2, pixel_byte_offset=0)
        digest = hashlib.sha256(payload[:64]).hexdigest()
        state = {'texture': {'pixel_image': {'byte_length': 64, 'sha256': digest}}}
        capture = {'pixel_sha256': digest}
        self.assertTrue(validation.captured_pixel_prefix_matches(run, texture, capture, state, payload))
        self.assertFalse(validation.captured_pixel_prefix_matches(run, texture, capture, state, b'X' + payload[1:]))
        state['texture']['pixel_image']['byte_length'] = 56
        digest = hashlib.sha256(payload[:56]).hexdigest()
        state['texture']['pixel_image']['sha256'] = capture['pixel_sha256'] = digest
        self.assertFalse(validation.captured_pixel_prefix_matches(run, texture, capture, state, payload))

    def test_fatal_input_error_replaces_stale_success_report(self):
        for error in (ValueError('missing preview'), validation.TraceError('captured bytes changed')):
            with self.subTest(error=type(error).__name__), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                validation.write(root / 'report.json', {'status': 'passed'})
                with mock.patch.object(validation, '_validate_batch', side_effect=error):
                    result = validation.validate_batch(root / 'config.json', root)
                self.assertEqual('failed', result['status'])
                self.assertEqual('failed', validation.read(root / 'report.json')['status'])
                self.assertIn(str(error), (root / 'review.html').read_text())
                def fail():
                    raise error
                self.assertEqual('failed', validation.checked(fail)['status'])

    def test_interruption_leaves_current_run_incomplete(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            config = root / 'config.json'
            validation.write(config, {'schema_version': 1})
            validation.write(root / 'report.json', {'status': 'passed'})
            with mock.patch.object(models, 'resolve_rom', side_effect=KeyboardInterrupt), self.assertRaises(KeyboardInterrupt):
                validation.validate_batch(config, root)
            report = validation.read(root / 'report.json')
            self.assertEqual('incomplete', report['status'])
            self.assertFalse(report['summary']['completed'])

    def test_invalid_configuration_produces_failed_report(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            validation.write(root / 'config.json', [])
            result = validation.validate_batch(root / 'config.json', root)
            self.assertEqual('failed', result['status'])
            self.assertIn('configuration', result['checks']['batch-input']['error'])

    def test_khronos_adapter_rejects_invalid_empty_mesh(self):
        package = validation.ROOT / 'build/tools/model-validation/node_modules/gltf-validator'
        node = shutil.which('node')
        if not node or not package.is_dir():
            self.skipTest('optional pinned Khronos validator is not installed')
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path = root / 'broken.gltf'
            validation.write(path, {'asset': {'version': '2.0'}, 'meshes': [{'primitives': []}]})
            output, request = root / 'result.json', root / 'request.json'
            validation.write(request, [{'path': str(path), 'key': 'test', 'output': str(output),
                                       'fingerprint': validation.preview_fingerprint(path)}])
            subprocess.run([node, str(validation.ROOT / 'scripts/gltf_validate_models.cjs'), str(package), str(request)], check=True)
            result = validation.read(output)['result']
            self.assertEqual('failed', result['status'])
            self.assertIn('EMPTY_ENTITY', [m['code'] for m in result['issues']['messages']])


if __name__ == '__main__':
    unittest.main()
