"""Profile composition preserves Splat inputs and keeps code mappings local."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

import yaml

from scripts import prepare_profile, profile_config


class ProfileConfigTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        self.profile = self.root / 'config/profiles/us.yaml'
        self.profile.parent.mkdir(parents=True)
        self.fragment = self.profile.parent / 'us/assets/font.yaml'
        self.fragment.parent.mkdir(parents=True)
        self.rows = [[0x100, 'bin', 'font/glyphs/0000'], [0x108, 'bin', 'font/padding']]
        self.fragment.write_text(yaml.safe_dump(self.rows))
        self.document = {'options': {'target_path': '__ROM_PATH__', 'base_path': '../..'},
                         'segments': [{'name': 'main', 'type': 'code', 'start': 0,
                                       'subsegments': [[0, 'c', 'main/init']]},
                                      {'name': 'font', 'type': 'group', 'start': 0x100,
                                       'align': 1, 'subalign': 1,
                                       'subsegments': {'include': 'us/assets/font.yaml'}},
                                      [0x110]]}
        self.save()

    def save(self):
        self.profile.write_text(yaml.safe_dump(self.document, sort_keys=False))

    def test_expansion_preserves_structure_and_order_without_mutating_sources(self):
        before = [p.read_bytes() for p in (self.profile, self.fragment)]
        expected = yaml.safe_load(self.profile.read_text())
        expected['segments'][1]['subsegments'] = self.rows
        self.assertEqual(profile_config.load_profile(self.profile), expected)
        self.assertEqual(profile_config.profile_dependencies(self.profile),
                         [self.profile, self.fragment])
        self.assertEqual([p.read_bytes() for p in (self.profile, self.fragment)], before)
        self.profile.write_text(yaml.safe_dump(expected))
        self.assertEqual(profile_config.load_profile(self.profile), expected)
        self.assertEqual(profile_config.profile_dependencies(self.profile), [self.profile])

    def test_materialized_profile_is_plain_yaml_and_reference_stays_independent(self):
        rom = self.root / 'roms/baserom.us.z64'
        rom.parent.mkdir()
        rom.touch()
        reference = self.root / 'config/reference/us.yaml'
        reference.parent.mkdir()
        reference.write_text('options:\n  target_path: "__ROM_PATH__"\nsegments:\n  - [0, bin, original]\n')
        with patch.object(prepare_profile, 'ROOT', self.root), \
             patch.object(prepare_profile, 'OUTPUT_DIR', self.root / 'build/config'), \
             patch.object(prepare_profile, 'ROM_PATHS', {'us': rom}), \
             patch.object(sys, 'argv', ['prepare_profile', 'us']):
            prepare_profile.main()
            expected = profile_config.load_profile(self.profile)
            expected['options']['target_path'] = 'roms/baserom.us.z64'
            self.assertEqual(yaml.safe_load((self.root / 'build/config/us.yaml').read_text()), expected)
            # A broken asset fragment must not affect the immutable raw reference.
            self.fragment.unlink()
            with patch.object(sys, 'argv', ['prepare_profile', 'us', '--reference']):
                prepare_profile.main()
            self.assertEqual((self.root / 'build/config/reference/us.yaml').read_text(),
                             reference.read_text().replace('__ROM_PATH__', 'roms/baserom.us.z64'))

    def test_include_rejects_missing_escaping_or_non_asset_inputs(self):
        for name in ('missing.yaml', '../outside.yaml', str(self.fragment), ''):
            with self.subTest(name=name):
                self.document['segments'][1]['subsegments'] = {'include': name}
                self.save()
                with self.assertRaises((ValueError, FileNotFoundError)):
                    profile_config.load_profile(self.profile)
        self.document['segments'][1]['subsegments'] = {'include': 'us/assets/font.yaml'}
        self.document['segments'][1]['type'] = 'code'
        self.save()
        with self.assertRaisesRegex(ValueError, 'only asset groups'):
            profile_config.load_profile(self.profile)

    def test_fragments_are_nonempty_binary_lists_without_nested_includes(self):
        for value in (None, {}, [], {'include': 'font.yaml'},
                      [[0, 'c', 'main/init']], [[True, 'bin', 'font']],
                      [[0, 'bin']], [[0, 'bin', '']]):
            with self.subTest(value=value):
                self.fragment.write_text(yaml.safe_dump(value))
                with self.assertRaises(ValueError):
                    profile_config.load_profile(self.profile)

    def test_symlinks_cannot_escape_and_fragments_cannot_be_repeated(self):
        outside = self.root / 'outside.yaml'
        outside.write_text(yaml.safe_dump(self.rows))
        self.fragment.unlink()
        self.fragment.symlink_to(outside)
        with self.assertRaisesRegex(ValueError, 'escapes'):
            profile_config.load_profile(self.profile)
        self.fragment.unlink()
        self.fragment.write_text(yaml.safe_dump(self.rows))
        self.document['segments'].insert(2, self.document['segments'][1].copy())
        self.save()
        with self.assertRaisesRegex(ValueError, 'repeated'):
            profile_config.load_profile(self.profile)

    def test_dependency_cli_lists_all_inputs_and_fails_on_invalid_fragment(self):
        command = [sys.executable, str(Path(profile_config.__file__).resolve()),
                   'dependencies', 'config/profiles/us.yaml']
        result = subprocess.run(command, cwd=self.root, text=True, capture_output=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.split(), ['config/profiles/us.yaml',
                                                'config/profiles/us/assets/font.yaml'])
        self.fragment.unlink()
        result = subprocess.run(command, cwd=self.root, text=True, capture_output=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(result.stdout, '')
