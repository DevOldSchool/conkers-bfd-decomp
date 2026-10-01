import copy
from dataclasses import replace
import hashlib
import json
from pathlib import Path
import tempfile
from types import SimpleNamespace
import unittest
from unittest import mock

from scripts import model_assets as models, model_coverage as coverage
from test_model_coverage import triangle_payload


class CoverageRomPolicyTests(unittest.TestCase):
    def geometry(self):
        return models.parse_model_geometry(triangle_payload())

    def primary_fixture(self):
        source = self.geometry()
        run = source.material_runs[0]
        source = replace(source, faces=source.faces * 4,
                         material_runs=(replace(run, first_face=0, face_count=2),
                                        replace(run, first_face=2, face_count=2)),
                         face_command_offsets=(80, 88, 96, 104))
        selected = replace(source, faces=source.faces[:2], face_source_indices=(0, 2),
                           material_runs=(replace(run, first_face=0, face_count=1),
                                          replace(run, first_face=1, face_count=1)),
                           face_command_offsets=(80, 96))
        proof = {'model_sha1': hashlib.sha1(b'model').hexdigest(),
                 'source_face_indices': [0, 2], 'primary_face_count': 2,
                 'all_tables_face_count': 4}
        return source, selected, proof

    def test_character_preset_cli_flag_is_explicit_and_coverage_only(self):
        import contextlib
        import io
        import sys
        with mock.patch.object(sys, 'argv', ['model_assets', 'coverage']):
            self.assertFalse(models.parse_args().rom_character_presets)
        with mock.patch.object(sys, 'argv', ['model_assets', 'coverage', '--rom-character-presets']):
            self.assertTrue(models.parse_args().rom_character_presets)
        for action in ('preview', 'extract', 'verify'):
            with mock.patch.object(sys, 'argv', ['model_assets', action, '--rom-character-presets']), \
                 contextlib.redirect_stderr(io.StringIO()), self.assertRaises(SystemExit):
                models.parse_args()

    def test_rom_object_fallback_resolves_without_manifest_status(self):
        run = self.geometry().material_runs[0]
        run = replace(run, texture_enabled=True, texture_coordinates_proven=True)
        texture = SimpleNamespace(sha1='proved')
        with mock.patch.object(models, 'choose_preview_texture', return_value=(None, 'no-proven-texture')), \
             mock.patch.object(models, 'rom_object_preview_texture', return_value=(texture, 'rom-object-proved', {'proof': True})) as fallback:
            actual, reason, evidence = coverage.rom_static_texture(run, {}, {}, (), {'entry': 5}, b'model', (9, 5, 0))
        self.assertIs(texture, actual)
        self.assertEqual('rom-object-proved', reason)
        self.assertEqual({'rom_texture_state_consensus': {'proof': True}}, evidence)
        self.assertEqual({'entry': 5}, fallback.call_args.args[-1])

    def test_coordinate_state_vetoes_a_fallback_texture(self):
        run = replace(self.geometry().material_runs[0], texture_enabled=True,
                      texture_coordinates_proven=False)
        with mock.patch.object(models, 'choose_preview_texture', return_value=(None, 'runtime-segment')), \
             mock.patch.object(models, 'rom_object_animation_preview_texture', return_value=(SimpleNamespace(sha1='image'), 'proved', {})):
            texture, reason, evidence = coverage.rom_static_texture(run, {}, {}, (), {}, b'model', (9, 5, 0))
        self.assertIsNone(texture)
        self.assertIsNone(evidence)
        self.assertEqual('runtime-texture-observed-coordinate-state-unresolved', reason)

    def test_runtime_segment_fallback_order_and_stop_on_success(self):
        run = replace(self.geometry().material_runs[0], texture_enabled=True)
        texture = SimpleNamespace(sha1='binding-image')
        with mock.patch.object(models, 'choose_preview_texture', return_value=(None, 'runtime-segment')), \
             mock.patch.object(models, 'rom_object_animation_preview_texture', return_value=(None, 'unresolved', None)) as animation, \
             mock.patch.object(models, 'rom_object_binding_preview_texture', return_value=(texture, 'binding', {'source': 'ROM'})) as binding, \
             mock.patch.object(models, 'rom_scene_preview_texture') as scene:
            actual, reason, proof = coverage.rom_static_texture(run, {}, {}, (), {}, b'model', (9, 5, 0))
        self.assertIs(actual, texture)
        self.assertEqual('binding', reason)
        animation.assert_called_once()
        binding.assert_called_once()
        scene.assert_not_called()
        self.assertEqual({'rom_object_texture_binding': {'source': 'ROM'}}, proof)

    def test_material_updates_keep_full_source_domain_and_allow_proven_uv_changes(self):
        source = self.geometry()
        vertex = replace(source.vertices[0], s=123, t=-456)
        mapped = replace(source, vertices=(vertex, *source.vertices[1:]))
        coverage._same_face_domain(source, mapped)
        for changed in (
            replace(source, faces=()),
            replace(source, face_source_indices=(9,)),
            replace(source, material_runs=(replace(source.material_runs[0], first_face=2),)),
            replace(source, vertices=(replace(source.vertices[0], x=99), *source.vertices[1:])),
        ):
            with self.assertRaisesRegex(ValueError, 'coverage ROM'):
                coverage._same_face_domain(source, changed)

    def test_preview_primary_hash_mapping_and_count_come_from_rom(self):
        source, selected, proof = self.primary_fixture()
        preview = {'source_face_count': 2, 'character_draw_pass': proof}
        with mock.patch.object(models, 'parse_character_model_geometry', return_value=(source, {})), \
             mock.patch.object(models.model_character_parts, 'primary_preview', return_value=(selected, proof)):
            self.assertEqual(2, coverage.validate_preview_source(preview, 1, b'model', source))
            for field, value in (('model_sha1', 'forged'), ('source_face_indices', [0, 1]),
                                 ('all_tables_face_count', 2)):
                changed = copy.deepcopy(preview)
                changed['character_draw_pass'][field] = value
                with self.assertRaisesRegex(ValueError, 'source hash or primary face mapping'):
                    coverage.validate_preview_source(changed, 1, b'model', source)
            for value in (4, True):
                with self.assertRaisesRegex(ValueError, 'source span'):
                    coverage.validate_preview_source({**preview, 'source_face_count': value}, 1, b'model', source)
            with self.assertRaisesRegex(ValueError, 'requires bank01'):
                coverage.validate_preview_source(preview, 9, b'model', source)

    def test_primary_selection_rejects_duplicate_out_of_range_and_cross_run_indices(self):
        source, selected, proof = self.primary_fixture()
        for indices in ((0, 0), (0, 4), (2, 0)):
            with mock.patch.object(models.model_character_parts, 'primary_preview',
                                   return_value=(replace(selected, face_source_indices=indices), proof)):
                with self.assertRaisesRegex(ValueError, 'coverage primary selection'):
                    coverage.checked_primary_geometry(b'model', source, {})

    def test_preset_rows_retain_full_source_face_indices(self):
        source, selected, proof = self.primary_fixture()
        with mock.patch.object(models, 'parse_character_model_geometry', return_value=(source, {})), \
             mock.patch.object(models.model_character_parts, 'primary_preview', return_value=(selected, proof)), \
             mock.patch.object(models.model_character_defaults, 'preview_defaults', return_value=None):
            rows = coverage.rom_character_preset_rows(b'model', source, 5, {}, {}, {}, ())
        self.assertEqual([[0], [2]], [r['source_face_indices'] for r in rows])
        self.assertEqual([1, 1], [r['source_face_count'] for r in rows])
        self.assertEqual(['not-required', 'not-required'], [r['status'] for r in rows])
        self.assertEqual(4, len(source.faces))

    def test_spoofed_preview_status_cannot_promote_texture_or_enable_presets(self):
        payload = triangle_payload()
        segment = models.ModelSegment(0, 0, len(payload), True, payload)
        bundle = models.ModelBundle(5, 0, False, payload, (segment,))
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path = root / 'us-bank-09-preview/manifest.json'
            path.parent.mkdir()
            path.write_text(json.dumps({'normalized_sha1': 'digest', 'models': [{
                'bank_entry': 5, 'segment': 0, 'source_face_count': 1,
                'material_runs': [{'status': 'resolved', 'texture': {'png_sha1': 'forged'}}],
            }], 'rom_character_defaults': {'status': 'resolved'}}))
            with mock.patch.object(models, 'BANK_INDICES', (9,)), \
                 mock.patch.object(models, 'load_model_bundles', return_value=(root/'rom', 'z64', 'digest', [bundle], ())), \
                 mock.patch.object(models, 'load_preview_texture_catalog', return_value={}), \
                 mock.patch.object(models, 'PREVIEW_TEXTURE_FAMILIES', ()), \
                 mock.patch.object(models, 'load_flat_asset_payloads', return_value={}), \
                 mock.patch.object(models, 'load_object_placement_manifest', return_value=({'scenes': [], 'unresolved_bank_11_dispatch_references': []}, {})), \
                 mock.patch.object(models, 'load_object_material_context', return_value={'normalized_sha1': 'digest', 'models': []}), \
                 mock.patch.object(models, 'load_character_defaults') as defaults:
                report = coverage.extract_coverage('us', None, root, root, root/'report.json')
            defaults.assert_not_called()
            row = report['material_runs'][0]
            self.assertEqual('not-required', row['static_texture']['status'])
            self.assertIsNone(row['static_texture']['png_sha1'])
            self.assertNotIn('rom_preset_texture', row)
            self.assertEqual({'not-required': 1}, report['summary']['static_texture_face_counts'])


if __name__ == '__main__':
    unittest.main()
