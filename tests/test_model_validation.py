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
    def test_attachment_update_requires_matching_provenance_and_actual_uvs(self):
        run = models.ModelMaterialRun(0, 1, True,
            models.ModelTextureBinding(0xFD180000, segment=6, offset=0,
                                      load_command=(0xF3000000, 0x071FF000)),
            None, (0xF5180400, 0x00018030), (), (0xF2002002, 0x0001E0FE),
            (0xD7000002, 0xFFFFFFFF), (0xFCFF9880, 0xF514FEFF), (0xEF182C3F, 0x04D049D8), None)
        source = replace(geometry(), material_runs=(run,))
        adjusted = replace(source, material_runs=(replace(run,
            tile_bounds=(0xF200203E, 0x0001E0FE), texture_dimensions=(8, 64)),))
        evidence = {'updater': 'func_150D83D8', 'preview_command': [0xF200203E, 0x0001E0FE]}
        records = [{'face_count': 1, 'runtime_material': None}]
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            document, binary = models.encode_gltf(80, 0, adjusted, {}, output_stem='model')
            parsed = json.loads(document)
            parsed.setdefault('extras', {})['romAttachmentUpdate'] = evidence
            path = root / 'model.gltf'; validation.write(path, parsed)
            path.with_suffix('.bin').write_bytes(binary)
            result = validation.compare_geometry(path, adjusted, None, records, attachment_update=evidence)
            self.assertEqual(3, result['uv_corners'])
            with self.assertRaisesRegex(ValueError, 'UV differs'):
                validation.compare_geometry(path, source, None, records, attachment_update=evidence)
            with self.assertRaisesRegex(ValueError, 'attachment texture/UV update differs'):
                validation.compare_geometry(path, adjusted, None, records)
            parsed['extras']['romAttachmentUpdate'] = {'preview_command': [0xF2002002, 0x0001E0FE]}
            validation.write(path, parsed)
            with self.assertRaisesRegex(ValueError, 'attachment texture/UV update differs'):
                validation.compare_geometry(path, adjusted, None, records, attachment_update=evidence)

    def detail_fixture(self, root):
        def bounds(i, origin, w, h):
            return (i, 0xF2000000 | (origin << 12) | origin,
                    (i << 24) | ((origin+4*(w-1)) << 12) | (origin+4*(h-1)))
        sizes = (bounds(0, 64, 4, 8), bounds(1, 32, 8, 8), bounds(2, 16, 4, 4))
        tiles = ((0, 0xF560020C, 0x0000FC2F), (1, 0xF5480200, 0x0100C030),
                 (2, 0xF5480208, 0x02008421), (6, 0xF5600100, 0x06000000),
                 (7, 0xF5500000, 0x07000000))
        run = models.ModelMaterialRun(0, 1, True,
            models.ModelTextureBinding(0xFD500000, 42, 0, load_command=(0xF3000000, 0x0704F000)),
            models.ModelTextureBinding(0xFD100000, 42, 1, load_command=(0xF0000000, 0x063FC000)),
            tiles[0][1:], tiles, sizes[0][1:], (0xD7000802, 0xFFFFFFFF),
            (0xFC26A004, 0x151092FF), (0xEF1DAC3F, 0x0C192230), None,
            detail_tile_bounds=sizes)
        flat = {42: bytes(range(160)) + bytes.fromhex('0001') * 256}
        texture, status = models.choose_preview_texture(run, {}, flat)
        selected = replace(run, preview_coordinate_state=texture.preview_coordinate_state)
        source = replace(geometry(), material_runs=(run,))
        output = replace(source, material_runs=(selected,))
        record = {'face_count': 1, 'runtime_material': None, 'status': status,
                  'rom_detail_texture_preview': models.detail_texture_preview_record(selected),
                  'texture': {'file': 'base.png', 'source_family': texture.family, 'width': 8, 'height': 8}}
        (root/'base.png').write_bytes(texture.png_data)
        document, binary = models.encode_gltf(0, 0, output, {0: 'base.png'}, output_stem='model')
        path = root/'model.gltf';path.write_bytes(document);path.with_suffix('.bin').write_bytes(binary)
        return path, source, [record], flat

    def test_detail_validation_recomputes_pixels_and_uv_selection_from_rom(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory);path, source, runs, flat = self.detail_fixture(root)
            result = validation.compare_geometry(path, source, None, runs, flat_payloads=flat)
            self.assertEqual(3, result['uv_corners'])
            runs[0]['rom_detail_texture_preview']['preview_tile'] = 0
            with self.assertRaisesRegex(ValueError, 'ROM detail preview selection differs'):
                validation.compare_geometry(path, source, None, runs, flat_payloads=flat)
            runs[0]['rom_detail_texture_preview']['preview_tile'] = 1
            (root/'base.png').write_bytes(b'changed')
            with self.assertRaisesRegex(ValueError, 'ROM detail texture differs'):
                validation.compare_geometry(path, source, None, runs, flat_payloads=flat)

    def test_detail_validation_rejects_forged_gltf_binding_metadata_and_coordinates(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory);path, source, runs, flat = self.detail_fixture(root)
            document = validation.read(path)
            saved = json.loads(json.dumps(document))
            document['materials'][0]['extras']['romDetailTexturePreview']['preview_tile'] = 0
            validation.write(path, document)
            with self.assertRaisesRegex(ValueError, 'exported ROM detail preview evidence differs'):
                validation.compare_geometry(path, source, None, runs, flat_payloads=flat)
            document = json.loads(json.dumps(saved));(root/'wrong.png').write_bytes((root/'base.png').read_bytes())
            document['images'][0]['uri'] = 'wrong.png';validation.write(path, document)
            with self.assertRaisesRegex(ValueError, 'exported ROM detail image binding differs'):
                validation.compare_geometry(path, source, None, runs, flat_payloads=flat)
            validation.write(path, saved)
            accessor = saved['accessors'][saved['meshes'][0]['primitives'][0]['attributes']['TEXCOORD_0']]
            offset = saved['bufferViews'][accessor['bufferView']]['byteOffset']
            binary = bytearray(path.with_suffix('.bin').read_bytes());struct.pack_into('<f',binary,offset,123.0);path.with_suffix('.bin').write_bytes(binary)
            with self.assertRaisesRegex(ValueError, 'UV differs from selected coordinate state'):
                validation.compare_geometry(path, source, None, runs, flat_payloads=flat)

    def test_rom_direct_defaults_reject_forged_selection_and_changed_pixels(self):
        pixel = models.ModelTextureBinding(0xFD180000, segment=6, offset=0,
                                           load_command=(0xF3000000, 0x07007000))
        run = models.ModelMaterialRun(0, 1, True, pixel, None, (0xF5180200, 0),
            ((0, 0xF5180200, 0), (7, 0xF5180000, 0x07000000)),
            (0xF2000000, 0x0000C004), (0xD7000002, 0xFFFFFFFF),
            (0xFCFF9880, 0xF514FEFF), (0xEF182C3F, 0x04D04DD8), None)
        source = replace(geometry(), material_runs=(run,))
        defaults = {'entries': {23: {'preset': 'fixture', 'header_sha1': 'header',
                                     'descriptor_indices': {'6': 0}}}}
        descriptors = [{'record_index': 0, 'flat_index': 42, 'width': 4, 'height': 2}]
        payloads = {42: bytes(range(32))}
        texture, status, evidence = models.rom_default_preview_texture(
            run, defaults['entries'][23], descriptors, payloads, [])
        record = {'status': status, 'rom_default_texture': evidence,
                  'texture': {'file': 'face.png'}}
        manifest = {'rom_character_defaults': defaults,
                    'models': [{'bank_entry': 23, 'character_draw_pass': {}, 'material_runs': [record]}]}
        bundle = SimpleNamespace(index=23, data=b'model')
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path = root / 'manifest.json'
            (root / 'face.png').write_bytes(texture.png_data)
            validation.write(path, manifest)
            with mock.patch.object(models, 'load_model_bundles', return_value=(None, None, 'rom', [bundle], [])), \
                 mock.patch.object(models, 'load_character_defaults', return_value=defaults), \
                 mock.patch.object(models, 'parse_character_model_geometry', return_value=(source, {'texture_descriptors': descriptors})), \
                 mock.patch.object(models.model_character_parts, 'primary_preview', return_value=(source, {})):
                result = validation.compare_rom_defaults(path, [], payloads, {})
                self.assertEqual((1, 1), (result['resolved_runs'], result['resolved_faces']))
                (root / 'face.png').write_bytes(b'changed')
                with self.assertRaisesRegex(ValueError, 'ROM default PNG differs'):
                    validation.compare_rom_defaults(path, [], payloads, {})
                (root / 'face.png').write_bytes(texture.png_data)
                record['rom_default_texture'] = {**evidence, 'segment': 7}
                validation.write(path, manifest)
                with self.assertRaisesRegex(ValueError, 'ROM default resolution changed'):
                    validation.compare_rom_defaults(path, [], payloads, {})

    def test_object_material_validation_rejects_forged_provenance_pixels_and_capture_mix(self):
        for bank in (3, 4, 9):
            with self.subTest(bank=bank):
                self.check_object_material_validation(bank)

    def check_object_material_validation(self, bank):
        source = geometry()
        segment = SimpleNamespace(index=0, data=b'model')
        bundle = SimpleNamespace(index=58, segments=[segment])
        context = {'models': [{'bank': bank, 'entry': 58, 'segment': 0}]}
        evidence = {'object_renderer_context': {'bank': bank, 'entry': 58, 'segment': 0}}
        png = texture_assets.encode_rgba_png(1, 1, bytes((10, 20, 30, 255)))
        record = {'status': 'rom-state-consensus-ci4', 'rom_texture_state_consensus': evidence,
                  'texture': {'file': 'texture.png'}}
        manifest = {'bank_index': bank, 'rom_object_material_context': context,
                    'models': [{'bank_entry': 58, 'segment': 0, 'material_runs': [record]}]}
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path = root / 'manifest.json'
            (root / 'texture.png').write_bytes(png)
            validation.write(path, manifest)
            with mock.patch.object(models, 'load_model_bundles', return_value=(None, None, 'rom', [bundle], [])), \
                 mock.patch.object(models, 'load_object_material_context', return_value=context), \
                 mock.patch.object(models, 'parse_segment_geometry', return_value=source), \
                 mock.patch.object(models, 'choose_preview_texture', return_value=(None, 'no-proven-texture')), \
                 mock.patch.object(models, 'rom_object_preview_texture', return_value=(SimpleNamespace(png_data=png), record['status'], evidence)):
                result = validation.compare_rom_object_materials(path, {}, {}, {})
                self.assertEqual((1, 1), (result['consensus_texture_runs'], result['consensus_texture_faces']))
                with self.assertRaisesRegex(ValueError, 'captured material was replaced'):
                    validation.compare_rom_object_materials(path, {}, {}, {(bank, 58, 0, 0): {}})
                (root / 'texture.png').write_bytes(b'changed')
                with self.assertRaisesRegex(ValueError, 'texture differs'):
                    validation.compare_rom_object_materials(path, {}, {}, {})
                manifest['rom_object_material_context'] = {'models': []}
                validation.write(path, manifest)
                with self.assertRaisesRegex(ValueError, 'provenance differs'):
                    validation.compare_rom_object_materials(path, {}, {}, {})

    def test_scene_material_validation_rejects_forged_provenance_pixels_and_capture_mix(self):
        for bank in (4,):
            with self.subTest(bank=bank):
                self.check_scene_material_validation(bank)

    def check_scene_material_validation(self, bank):
        source = geometry()
        segment = SimpleNamespace(index=0, data=b'model')
        bundle = SimpleNamespace(index=58, segments=[segment])
        context = {'models': [{'bank': bank, 'entry': 58, 'segment': 0}]}
        evidence = {'object_renderer_context': {'bank': bank, 'entry': 58, 'segment': 0}}
        png = texture_assets.encode_rgba_png(1, 1, bytes((10, 20, 30, 255)))
        record = {'status': 'rom-scene-texture-state', 'rom_scene_texture_state': evidence,
                  'texture': {'file': 'texture.png'}}
        manifest = {'bank_index': bank, 'rom_object_material_context': context,
                    'models': [{'bank_entry': 58, 'segment': 0, 'material_runs': [record]}]}
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path = root / 'manifest.json'
            (root / 'texture.png').write_bytes(png)
            validation.write(path, manifest)
            with mock.patch.object(models, 'load_model_bundles', return_value=(None, None, 'rom', [bundle], [])), \
                 mock.patch.object(models, 'load_object_material_context', return_value=context), \
                 mock.patch.object(models, 'parse_segment_geometry', return_value=source), \
                 mock.patch.object(models, 'choose_preview_texture', return_value=(None, 'runtime-segment')), \
                 mock.patch.object(models, 'rom_scene_preview_texture', return_value=(SimpleNamespace(png_data=png), record['status'], evidence)):
                result = validation.compare_rom_object_materials(path, {}, {}, {})
                self.assertEqual((1, 1), (result['consensus_texture_runs'], result['consensus_texture_faces']))
                with self.assertRaisesRegex(ValueError, 'captured material was replaced'):
                    validation.compare_rom_object_materials(path, {}, {}, {(bank, 58, 0, 0): {}})
                (root / 'texture.png').write_bytes(b'changed')
                with self.assertRaisesRegex(ValueError, 'texture state differs'):
                    validation.compare_rom_object_materials(path, {}, {}, {})
                manifest['rom_object_material_context'] = {'models': []}
                validation.write(path, manifest)
                with self.assertRaisesRegex(ValueError, 'provenance differs'):
                    validation.compare_rom_object_materials(path, {}, {}, {})

    def test_binding_material_validation_rejects_forged_provenance_pixels_and_capture_mix(self):
        for bank in (4, 9):
            with self.subTest(bank=bank):
                self.check_binding_material_validation(bank)

    def check_binding_material_validation(self, bank):
        source = geometry()
        segment = SimpleNamespace(index=0, data=b'model')
        bundle = SimpleNamespace(index=58, segments=[segment])
        context = {'models': [{'bank': bank, 'entry': 58, 'segment': 0}]}
        evidence = {'object_renderer_context': {'bank': bank, 'entry': 58, 'segment': 0}}
        png = texture_assets.encode_rgba_png(1, 1, bytes((10, 20, 30, 255)))
        record = {'status': 'rom-object-binding-texture', 'rom_object_texture_binding': evidence,
                  'texture': {'file': 'texture.png'}}
        manifest = {'bank_index': bank, 'rom_object_material_context': context,
                    'models': [{'bank_entry': 58, 'segment': 0, 'material_runs': [record]}]}
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path = root / 'manifest.json'
            (root / 'texture.png').write_bytes(png)
            validation.write(path, manifest)
            with mock.patch.object(models, 'load_model_bundles', return_value=(None, None, 'rom', [bundle], [])), \
                 mock.patch.object(models, 'load_object_material_context', return_value=context), \
                 mock.patch.object(models, 'parse_segment_geometry', return_value=source), \
                 mock.patch.object(models, 'choose_preview_texture', return_value=(None, 'runtime-segment')), \
                 mock.patch.object(models, 'rom_object_binding_preview_texture', return_value=(SimpleNamespace(png_data=png), record['status'], evidence)):
                result = validation.compare_rom_object_materials(path, {}, {}, {})
                self.assertEqual((1, 1), (result['consensus_texture_runs'], result['consensus_texture_faces']))
                with self.assertRaisesRegex(ValueError, 'captured material was replaced'):
                    validation.compare_rom_object_materials(path, {}, {}, {(bank, 58, 0, 0): {}})
                (root / 'texture.png').write_bytes(b'changed')
                with self.assertRaisesRegex(ValueError, 'texture binding differs'):
                    validation.compare_rom_object_materials(path, {}, {}, {})
                manifest['rom_object_material_context'] = {'models': []}
                validation.write(path, manifest)
                with self.assertRaisesRegex(ValueError, 'provenance differs'):
                    validation.compare_rom_object_materials(path, {}, {}, {})

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

    def test_regression_cache_reuses_content_and_rechecks_changes_or_missing_differences(self):
        from scripts.model_evidence_cache import ContentSnapshot
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            reference, current, difference = (root / name for name in ('before.png', 'after.png', 'diff.png'))
            original = texture_assets.encode_rgba_png(1, 1, bytes((0, 0, 0, 255)))
            reference.write_bytes(original); current.write_bytes(original)
            def compare(code='v1'):
                return validation.cached_image_comparison(reference, current, difference,
                    root / 'cache', ContentSnapshot(), code)
            self.assertFalse(compare()['cached'])
            with mock.patch.object(validation, 'compare_images', side_effect=AssertionError('unchanged images redecoded')):
                self.assertTrue(compare()['cached'])
            current.write_bytes(texture_assets.encode_rgba_png(1, 1, bytes((15, 0, 0, 255))))
            result = compare()
            self.assertEqual(('incomplete', False, 1), (result['status'], result['cached'], result['changed_pixels']))
            self.assertTrue(compare()['cached'])
            difference.unlink();self.assertFalse(compare()['cached']);self.assertTrue(difference.is_file())
            difference.write_bytes(b'corrupt');self.assertFalse(compare()['cached'])
            self.assertFalse(compare('changed decoder')['cached'])
            reference.write_bytes(current.read_bytes())
            self.assertEqual('passed', compare()['status'])

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
