"""Selected-state, ROM span and no-overwrite gates for the Haybot artifact."""
import copy
from pathlib import Path
import subprocess
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

from scripts import model_haybot_inspection as haybot


class HaybotInspectionTests(unittest.TestCase):
    def test_phase_zero_is_post_update_wrap_and_preserves_segment_eleven(self):
        state = haybot.selected_state()
        self.assertEqual((5, 0, 15, 0), (state['previous_phase'], state['phase'], state['actor68'], state['actor69']))
        self.assertEqual([15, 16, 17, 17, 16, 15], state['cycle_by_updated_phase'])
        self.assertEqual((0, 0), (state['initializer_actor68'], state['initializer_actor69']))
        for value in (False, 0., '0', -1, 1, 5):
            with self.subTest(value=value), self.assertRaisesRegex(ValueError, 'post-update'):
                haybot.selected_state(value)

    def test_manual_ci4_oracle_applies_nibbles_palette_and_odd_word_swap(self):
        payload = bytearray(2080)
        payload[2048:2052] = bytes.fromhex('0000F801')  # transparent black, opaque red
        payload[0] = 0x10
        payload[32+4] = 0x01  # odd source row: logical first two pixels 0,1
        pixels = haybot.raw_rgba(payload)
        self.assertEqual(bytes((255, 0, 0, 255, 0, 0, 0, 0)), pixels[:8])
        self.assertEqual(bytes((0, 0, 0, 0, 255, 0, 0, 255)), pixels[256:264])
        self.assertEqual(64*64*4, len(pixels))
        for changed in (payload[:-1], payload+b'\0'):
            with self.assertRaisesRegex(ValueError, 'span'): haybot.raw_rgba(changed)

    def fixture(self):
        run = SimpleNamespace(face_count=24, first_face=367, texture_enabled=True, texture_coordinates_proven=True,
            pixel=SimpleNamespace(segment=10, offset=0, load_command=(0xF3000000, 0x073FF000)),
            palette=SimpleNamespace(segment=10, offset=2048, load_command=(0xF0000000, 0x0603C000)),
            render_tile=(0xF5000800, 0x00098260), tile_bounds=(0xF2002002, 0x000FE0FE),
            combine_mode=(0xFCFF9880, 0xF514FEFF), runtime_render_state_offset=64)
        geometry = SimpleNamespace(faces=[(0, 1, 2)]*1225,
                                   vertices=[SimpleNamespace(color=(255, 255, 255, 255)) for _ in range(3)])
        return run, geometry

    def test_complete_target_contract_and_alpha_formula(self):
        run, geometry = self.fixture(); formula = haybot.material_contract(run, geometry)
        self.assertEqual(['TEXEL0', 'ZERO', 'SHADE', 'ZERO'], formula['cycles'][0]['alpha'])
        self.assertEqual(['COMBINED', 'ZERO', 'ENVIRONMENT', 'ZERO'], formula['cycles'][1]['alpha'])
        self.assertEqual(['SHADE', 'ENVIRONMENT', 'COMBINED', 'PRIMITIVE'], formula['cycles'][1]['color'])

    def test_material_guard_rejects_bounds_modes_selectors_and_raw_color_changes(self):
        run, geometry = self.fixture()
        changes = {'face_count': 23, 'first_face': 368, 'texture_enabled': False,
                   'texture_coordinates_proven': False, 'render_tile': (0xF5000800, 0x00094260),
                   'tile_bounds': (0xF2000000, 0x000FE0FE), 'combine_mode': (0xFCFF9880, 0),
                   'runtime_render_state_offset': 0}
        for key, value in changes.items():
            changed = copy.deepcopy(run); setattr(changed, key, value)
            with self.subTest(key=key), self.assertRaises(ValueError): haybot.material_contract(changed, geometry)
        for field, key, value in [('pixel', 'segment', 11), ('palette', 'offset', 0),
                                  ('pixel', 'load_command', (0xF3000000, 0x073FE000))]:
            changed = copy.deepcopy(run); setattr(getattr(changed, field), key, value)
            with self.subTest(field=field, key=key), self.assertRaises(ValueError):
                haybot.material_contract(changed, geometry)
        geometry.vertices[1].color = (255, 255, 255, 0)
        with self.assertRaisesRegex(ValueError, 'SHADE'): haybot.material_contract(run, geometry)

    def test_spawn_evidence_requires_whole_payload_and_exact_record(self):
        scene, offset, _, record_hex = haybot.SPAWNS[1]
        record = bytes.fromhex(record_hex); payload = bytes(offset)+record+bytes(10)
        args = (scene, offset, haybot.sha(payload), record_hex)
        result = haybot.spawn_contract(payload, *args)
        self.assertTrue(result['script_gated']); self.assertFalse(result['constructor_fade_override'])
        for index in (0, offset, offset+2, len(payload)-1):
            changed = bytearray(payload); changed[index] ^= 1
            with self.subTest(index=index), self.assertRaisesRegex(ValueError, 'spawn'):
                haybot.spawn_contract(changed, *args)
        # Coherently changing the source record to flags26 is still rejected.
        changed = bytearray(record); changed[1] = 0x26; payload2 = bytes(offset)+changed+bytes(10)
        with self.assertRaises(ValueError):
            haybot.spawn_contract(payload2, scene, offset, haybot.sha(payload2), changed.hex())

    def test_opacity_and_mode_are_explicit_and_native_parity_remains_incomplete(self):
        self.assertEqual([0, 0, 0, 255], haybot.STATE['environment_rgba'])
        self.assertEqual(['0xEF18AC3F', '0x04D12078'], haybot.STATE['other_mode'])
        self.assertFalse(haybot.STATE['native_parity'])
        self.assertIn('not a captured concurrent state', haybot.SCOPE)
        self.assertIn('15 Actions', haybot.SCOPE)

    def test_existing_or_partial_outputs_are_never_overwritten(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp); output = root/'build/inspection'
            with patch.object(haybot, 'ROOT', root), patch.object(haybot, 'build_files', return_value=({'source-proof.json': b'fresh'}, {})), \
                    patch.object(haybot.subprocess, 'run') as run:
                self.assertEqual(0, haybot.main(['--output', str(output), '--blender', '/custom/blender']))
                self.assertEqual('/custom/blender', run.call_args.args[0][0])
                self.assertIn('--disable-autoexec', run.call_args.args[0]); self.assertNotIn('--verify', run.call_args.args[0])
                calls = run.call_count
                with self.assertRaises(SystemExit): haybot.main(['--output', str(output)])
                self.assertEqual(calls, run.call_count)
                self.assertEqual(0, haybot.main(['--output', str(output), '--verify']))
                self.assertIn('--verify', run.call_args.args[0])
                (output/'source-proof.json').write_bytes(b'stale'); calls = run.call_count
                with self.assertRaises(SystemExit): haybot.main(['--output', str(output), '--verify'])
                self.assertEqual(calls, run.call_count); self.assertEqual(b'stale', (output/'source-proof.json').read_bytes())

    def test_worker_failure_and_midoperation_source_change_fail_closed(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp); output = root/'build/inspection'; output.mkdir(parents=True)
            (output/'source-proof.json').write_bytes(b'fresh')
            with patch.object(haybot, 'ROOT', root), patch.object(haybot, 'build_files', return_value=({'source-proof.json': b'fresh'}, {})), \
                    patch.object(haybot.subprocess, 'run', side_effect=subprocess.CalledProcessError(1, ['blender'])):
                with self.assertRaises(SystemExit): haybot.main(['--output', str(output), '--verify'])
                self.assertEqual(b'fresh', (output/'source-proof.json').read_bytes())
            with patch.object(haybot, 'ROOT', root), patch.object(haybot, 'build_files', side_effect=[
                    ({'source-proof.json': b'fresh'}, {}), ({'source-proof.json': b'changed'}, {})]), \
                    patch.object(haybot.subprocess, 'run'):
                with self.assertRaises(SystemExit): haybot.main(['--output', str(output), '--verify'])

    def test_build_children_only_and_no_symlink(self):
        for path in (haybot.ROOT, haybot.ROOT/'build', haybot.ROOT/'build/../scripts'):
            with self.assertRaisesRegex(ValueError, 'child of build'): haybot._checked_output(path)
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp); (root/'build/real').mkdir(parents=True); (root/'build/link').symlink_to(root/'build/real')
            with patch.object(haybot, 'ROOT', root), self.assertRaisesRegex(ValueError, 'symlink'):
                haybot._checked_output(root/'build/link')

    def test_admission_requires_fresh_worker_and_stable_snapshot(self):
        fixture = {'blend': b'x'}
        with patch.object(haybot, '_checked_output', return_value=Path('/fake')), \
                patch.object(haybot, '_artifact_snapshot', side_effect=[({'identity': 1}, fixture), ({'identity': 2}, fixture)]), \
                patch.object(haybot.subprocess, 'run', return_value=SimpleNamespace(returncode=0, stdout='', stderr='')) as run:
            with self.assertRaisesRegex(ValueError, 'changed during'): haybot.inspection_artifact('/fake')
            self.assertIn('--verify', run.call_args.args[0])
        with patch.object(haybot, '_checked_output', return_value=Path('/fake')), \
                patch.object(haybot, '_artifact_snapshot', return_value=({'identity': 1}, fixture)), \
                patch.object(haybot.subprocess, 'run', return_value=SimpleNamespace(returncode=1, stdout='bad', stderr='')):
            with self.assertRaisesRegex(ValueError, 'fresh Blender verification failed'): haybot.inspection_artifact('/fake')

    def test_final_preflight_rejects_any_changed_proof(self):
        with patch.object(haybot, '_checked_output', return_value=Path('/fake')), \
                patch.object(haybot, '_artifact_snapshot', return_value=({'identity': 1}, {})):
            self.assertTrue(haybot.inspection_artifact_current('/fake', {'identity': 1}))
            with self.assertRaisesRegex(ValueError, 'before publication'):
                haybot.inspection_artifact_current('/fake', {'identity': 2})


if __name__ == '__main__':
    unittest.main()
