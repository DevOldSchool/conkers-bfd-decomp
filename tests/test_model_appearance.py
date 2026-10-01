"""Shared appearance-preset command checks; no ROM or renderer invocation."""
from contextlib import redirect_stderr, redirect_stdout
import io
from pathlib import Path
from types import SimpleNamespace
import unittest
from unittest.mock import Mock, patch

from scripts import model_appearance as cli


class AppearanceCliTests(unittest.TestCase):
    def test_every_registered_preset_is_real_and_unique(self):
        self.assertEqual(5, len(cli.PRESETS))
        self.assertEqual(5, len(set(cli.PRESETS.values())))
        for preset, module in cli.PRESETS.items():
            self.assertEqual(preset, cli.importlib.import_module(module).PRESET)

    def test_all_contracts_are_available_and_pinned(self):
        import hashlib
        for module_name in cli.PRESETS.values():
            module = cli.importlib.import_module(module_name)
            with self.subTest(module=module_name):
                self.assertEqual(module.CONTRACT_SHA256, hashlib.sha256(module.CONTRACT_PATH.read_bytes()).hexdigest())
                self.assertTrue(module.contract())

    def test_exports_reject_paths_outside_build_before_loading_ROM(self):
        for preset, module_name in cli.PRESETS.items():
            module = cli.importlib.import_module(module_name)
            for output in (module.CONTRACT_PATH.parent.parent, module.CONTRACT_PATH.parent.parent / 'build'):
                with self.subTest(preset=preset, output=str(output)), patch.object(module, 'build_files') as build:
                    with self.assertRaisesRegex(ValueError, 'child of build/'):
                        module.main(['--preset', preset, '--output', str(output)])
                    build.assert_not_called()

    def test_routes_all_arguments_unchanged_to_exact_preset(self):
        for preset, module in cli.PRESETS.items():
            argv = ['--preset', preset, '--output', 'build/new export', '--rom', 'private.us.z64',
                    '--textures', 'build/textures', '--verify']
            target = SimpleNamespace(main=Mock(return_value=0))
            with self.subTest(preset=preset), patch.object(cli.importlib, 'import_module', return_value=target) as load:
                self.assertEqual(0, cli.main(argv))
                load.assert_called_once_with(module)
                target.main.assert_called_once_with(argv)

    def test_invalid_commands_cannot_start_export(self):
        preset = next(iter(cli.PRESETS))
        for argv in ([], ['--preset', 'unknown', '--output', 'build/x'],
                     ['--preset', preset], ['--preset', preset, '--output', 'build/x', '--force']):
            with self.subTest(argv=argv), patch.object(cli.importlib, 'import_module') as load, redirect_stderr(io.StringIO()):
                with self.assertRaises(SystemExit) as result:
                    cli.main(argv)
                self.assertEqual(2, result.exception.code)
                load.assert_not_called()

    def test_help_does_not_import_or_export(self):
        output = io.StringIO()
        with patch.object(cli.importlib, 'import_module') as load, redirect_stdout(output):
            with self.assertRaises(SystemExit) as result:
                cli.main(['--help'])
            self.assertEqual(0, result.exception.code)
            load.assert_not_called()
        for preset in cli.PRESETS:
            self.assertIn(preset, output.getvalue())

    def test_export_guard_failure_is_reported_without_retry(self):
        target = SimpleNamespace(main=Mock(side_effect=ValueError('source identity changed')))
        error = io.StringIO()
        with patch.object(cli.importlib, 'import_module', return_value=target), redirect_stderr(error):
            with self.assertRaises(SystemExit) as result:
                cli.main(['--preset', next(iter(cli.PRESETS)), '--output', 'build/x'])
            self.assertEqual(1, result.exception.code)
            target.main.assert_called_once()
        self.assertIn('source identity changed', error.getvalue())


if __name__ == '__main__':
    unittest.main()
