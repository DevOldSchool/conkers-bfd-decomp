"""Batch ordering and fail-closed admission for optional Blender inspections."""
from __future__ import annotations

from pathlib import Path
import tempfile
import unittest

from scripts import model_batch as batch


class ModelBatchTexgenTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        (self.root / 'scripts').mkdir()
        (self.root / 'scripts/model_assets.py').write_text('decoder = 1\n')
        (self.root / 'rom').write_bytes(b'rom')
        (self.root / 'textures').mkdir()
        self.output = self.root / 'build/assets/models/batch'
        self.destination = self.root / 'build/assets/models/character66-texgen-inspection'
        self.report = self.output / 'report.json'
        self.config = {'rom': 'rom', 'textures': 'textures', 'corpora': [],
                       'validation_config': 'config/validation.json',
                       'inspection_config': 'config/inspection.json'}
        self.inspection = {'models': [], 'validation_report': str(self.report.relative_to(self.root)),
                           'texgen_inspection': {'output': str(self.destination.relative_to(self.root))}}
        self.complete = {'status': 'passed', 'summary': {'completed': True}, 'renders': []}
        batch.write(self.root / self.config['validation_config'], {})
        self.write_inspection()
        batch.write(self.report, self.complete)
        self.gallery = self.root / 'build/assets/models/inspection/index.html'
        self.gallery.parent.mkdir(parents=True)
        self.gallery.write_bytes(b'previous gallery')
        self.calls, self.state = [], {}

    def write_inspection(self):
        batch.write(self.root / self.config['inspection_config'], self.inspection)

    def runner(self, command, *args):
        self.calls.append(command)
        if command[2] == 'validate':
            batch.write(self.report, self.complete)
        elif command[2] in ('texgen-inspection', 'texgen-animation-inspection', 'scene55-inspection', 'embedded-geometry', 'haybot-inspection'):
            if '--verify' not in command:
                self.destination.mkdir()
                (self.destination / 'artifact.json').write_bytes(b'verified artifact')
        elif command[2] == 'inspect':
            self.gallery.write_bytes(b'new gallery')
        return 0

    def run_batch(self, runner=None, blender=None):
        batch.run(self.root, self.config, self.output, self.state, [], blender,
                  runner=runner or self.runner)

    def test_fresh_create_then_existing_verify_always_runs_before_inspect(self):
        blender = Path('/custom/Blender')
        self.run_batch(blender=blender)
        self.assertEqual(['unittest', 'validate', 'texgen-inspection', 'inspect'],
                         [command[2] for command in self.calls])
        command = self.calls[-2]
        self.assertEqual(['./conker', 'model-assets', 'texgen-inspection', '--rom', 'rom',
                          '--output', str(self.destination), '--blender', str(blender)], command)
        original = (self.destination / 'artifact.json').read_bytes()
        for _ in range(2):
            self.calls.clear()
            self.run_batch(blender=blender)
            self.assertEqual(['validate', 'texgen-inspection', 'inspect'],
                             [command[2] for command in self.calls])
            self.assertIn('--verify', self.calls[-2])
            self.assertEqual(original, (self.destination / 'artifact.json').read_bytes())
        self.assertEqual('passed', self.state['stages']['texgen-inspection']['status'])

    def test_animated_mode_routes_create_and_verify_before_publication(self):
        self.inspection['texgen_inspection']['mode'] = 'animated'
        self.write_inspection()
        self.run_batch()
        self.assertEqual(['unittest', 'validate', 'texgen-animation-inspection', 'inspect'],
                         [command[2] for command in self.calls])
        self.assertNotIn('--verify', self.calls[-2])
        self.calls.clear()
        self.run_batch()
        self.assertEqual(['validate', 'texgen-animation-inspection', 'inspect'],
                         [command[2] for command in self.calls])
        self.assertIn('--verify', self.calls[-2])

    def test_scene55_creates_then_verifies_before_inspect(self):
        self.inspection['scene55_inspection'] = self.inspection.pop('texgen_inspection')
        self.write_inspection()
        self.run_batch()
        self.assertEqual(['unittest', 'validate', 'scene55-inspection', 'inspect'],
                         [command[2] for command in self.calls])
        self.assertNotIn('--verify', self.calls[-2])
        self.calls.clear()
        self.run_batch()
        self.assertEqual(['validate', 'scene55-inspection', 'inspect'],
                         [command[2] for command in self.calls])
        self.assertIn('--verify', self.calls[-2])

    def test_scene55_failed_verification_preserves_gallery(self):
        self.inspection['scene55_inspection'] = self.inspection.pop('texgen_inspection')
        self.write_inspection()
        self.destination.mkdir()
        def fail_verify(command, *args):
            if command[2] == 'scene55-inspection':
                self.calls.append(command)
                self.assertIn('--verify', command)
                return 1
            return self.runner(command, *args)
        with self.assertRaisesRegex(ValueError, 'scene55-inspection failed'):
            self.run_batch(runner=fail_verify)
        self.assertNotIn('inspect', [command[2] for command in self.calls])
        self.assertEqual(b'previous gallery', self.gallery.read_bytes())

    def test_scene55_invalid_options_fail_before_stage(self):
        del self.inspection['texgen_inspection']
        for options in (None, {}, {'output': ''}, {'output': 'build'},
                        {'output': 'build/../scripts'}, {'output': 'build/example', 'mode': 'neutral'}):
            with self.subTest(options=options):
                self.inspection['scene55_inspection'] = options
                self.write_inspection()
                self.calls.clear()
                with self.assertRaisesRegex(ValueError, 'scene55 inspection'):
                    self.run_batch()
                self.assertNotIn('scene55-inspection', [command[2] for command in self.calls])
                self.assertNotIn('inspect', [command[2] for command in self.calls])
                self.assertEqual(b'previous gallery', self.gallery.read_bytes())

    def test_embedded_type13_creates_then_verifies_before_inspect(self):
        self.inspection['embedded_type13_inspection'] = self.inspection.pop('texgen_inspection')
        self.write_inspection()
        self.run_batch()
        self.assertEqual(['unittest', 'validate', 'embedded-geometry', 'inspect'],
                         [command[2] for command in self.calls])
        self.assertEqual(['--primitive', 'type13', '--material-inspection', 'counter5'], self.calls[-2][3:7])
        self.assertNotIn('--verify', self.calls[-2])
        self.calls.clear()
        self.run_batch()
        self.assertIn('--verify', self.calls[-2])
        self.calls.clear()
        def fail(command, *args):
            if command[2] == 'embedded-geometry':
                self.calls.append(command)
                return 1
            return self.runner(command, *args)
        self.gallery.write_bytes(b'previous gallery')
        with self.assertRaisesRegex(ValueError, 'embedded-type13-inspection failed'):
            self.run_batch(runner=fail)
        self.assertNotIn('inspect', [command[2] for command in self.calls])
        self.assertEqual(b'previous gallery', self.gallery.read_bytes())

    def test_embedded_type06_creates_then_verifies_before_inspect(self):
        self.inspection['embedded_type06_inspection'] = self.inspection.pop('texgen_inspection')
        self.write_inspection()
        self.run_batch()
        self.assertEqual(['unittest', 'validate', 'embedded-geometry', 'inspect'],
                         [command[2] for command in self.calls])
        self.assertEqual(['--primitive', 'type06', '--material-inspection', 'elapsed0'], self.calls[-2][3:7])
        self.assertNotIn('--verify', self.calls[-2])
        self.calls.clear()
        self.run_batch()
        self.assertIn('--verify', self.calls[-2])
        self.calls.clear()
        def fail(command, *args):
            if command[2] == 'embedded-geometry':
                self.calls.append(command)
                return 1
            return self.runner(command, *args)
        self.gallery.write_bytes(b'previous gallery')
        with self.assertRaisesRegex(ValueError, 'embedded-type06-inspection failed'):
            self.run_batch(runner=fail)
        self.assertNotIn('inspect', [command[2] for command in self.calls])
        self.assertEqual(b'previous gallery', self.gallery.read_bytes())

    def test_haybot_creates_then_verifies_and_failure_preserves_gallery(self):
        self.inspection['haybot_inspection'] = self.inspection.pop('texgen_inspection')
        self.write_inspection()
        self.run_batch()
        self.assertEqual(['unittest', 'validate', 'haybot-inspection', 'inspect'],
                         [command[2] for command in self.calls])
        self.assertNotIn('--verify', self.calls[-2])
        self.calls.clear()
        self.run_batch()
        self.assertIn('--verify', self.calls[-2])
        self.calls.clear()
        def fail(command, *args):
            if command[2] == 'haybot-inspection':
                self.calls.append(command)
                return 1
            return self.runner(command, *args)
        self.gallery.write_bytes(b'previous gallery')
        with self.assertRaisesRegex(ValueError, 'haybot-inspection failed'):
            self.run_batch(runner=fail)
        self.assertNotIn('inspect', [command[2] for command in self.calls])
        self.assertEqual(b'previous gallery', self.gallery.read_bytes())

    def test_without_opt_in_preserves_previous_flow(self):
        del self.inspection['texgen_inspection']
        self.write_inspection()
        self.run_batch()
        self.assertEqual(['unittest', 'validate', 'inspect'], [command[2] for command in self.calls])
        self.assertFalse(self.destination.exists())

    def test_existing_incomplete_or_stale_artifact_is_verified_and_never_overwritten(self):
        for state in ('incomplete', 'stale'):
            with self.subTest(state=state):
                self.destination.mkdir(exist_ok=True)
                artifact = self.destination / 'artifact.json'
                artifact.write_bytes(state.encode())
                self.calls.clear()
                def fail_verify(command, *args):
                    if command[2] == 'texgen-inspection':
                        self.calls.append(command)
                        self.assertIn('--verify', command)
                        return 1
                    return self.runner(command, *args)
                with self.assertRaisesRegex(ValueError, 'texgen-inspection failed'):
                    self.run_batch(runner=fail_verify)
                self.assertNotIn('inspect', [command[2] for command in self.calls])
                self.assertEqual(state.encode(), artifact.read_bytes())
                self.assertEqual(b'previous gallery', self.gallery.read_bytes())
                self.assertEqual('failed', self.state['stages']['texgen-inspection']['status'])

    def test_create_failure_preserves_gallery_and_partial_output_requires_verify_on_retry(self):
        def interrupted_create(command, *args):
            if command[2] == 'texgen-inspection':
                self.calls.append(command)
                self.assertNotIn('--verify', command)
                self.destination.mkdir()
                return 1
            return self.runner(command, *args)
        with self.assertRaisesRegex(ValueError, 'texgen-inspection failed'):
            self.run_batch(runner=interrupted_create)
        self.assertEqual(b'previous gallery', self.gallery.read_bytes())
        self.calls.clear()
        def failed_retry(command, *args):
            if command[2] == 'texgen-inspection':
                self.calls.append(command)
                self.assertIn('--verify', command)
                return 1
            return self.runner(command, *args)
        with self.assertRaisesRegex(ValueError, 'texgen-inspection failed'):
            self.run_batch(runner=failed_retry)
        self.assertNotIn('inspect', [command[2] for command in self.calls])
        self.assertEqual(b'previous gallery', self.gallery.read_bytes())

    def test_validation_and_changed_render_gates_precede_texgen_and_publication(self):
        for failure in ('validation', 'render'):
            with self.subTest(failure=failure):
                self.calls.clear()
                def fail_gate(command, *args):
                    self.calls.append(command)
                    if command[2] == 'validate':
                        report = ({'status': 'failed', 'summary': {'completed': False}} if failure == 'validation'
                                  else {**self.complete, 'renders': [{'id': 'new', 'check':
                                       {'status': 'incomplete', 'current_sha256': 'new'}}]})
                        batch.write(self.report, report)
                    return 0
                with self.assertRaisesRegex(ValueError, 'gallery not refreshed'):
                    self.run_batch(runner=fail_gate)
                self.assertNotIn('texgen-inspection', [command[2] for command in self.calls])
                self.assertNotIn('inspect', [command[2] for command in self.calls])
                self.assertEqual(b'previous gallery', self.gallery.read_bytes())

    def test_invalid_artifact_configuration_fails_before_texgen_or_publication(self):
        escape = self.root / 'build/escape'
        escape.symlink_to(self.root / 'scripts', target_is_directory=True)
        for options in (None, {}, {'output': ''}, {'output': 2}, {'output': 'build', 'other': True},
                        {'output': 'build'}, {'output': 'build/../scripts'}, {'output': 'build/escape/new'},
                        {'output': 'build/example', 'mode': 'unknown'},
                        {'output': 'build/example', 'mode': None}):
            with self.subTest(options=options):
                self.inspection['texgen_inspection'] = options
                self.write_inspection()
                self.calls.clear()
                with self.assertRaisesRegex(ValueError, 'texgen inspection'):
                    self.run_batch()
                self.assertNotIn('texgen-inspection', [command[2] for command in self.calls])
                self.assertNotIn('inspect', [command[2] for command in self.calls])
                self.assertEqual(b'previous gallery', self.gallery.read_bytes())


if __name__ == '__main__':
    unittest.main()
