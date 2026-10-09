"""Profile composition preserves Splat inputs and keeps code mappings local."""
from pathlib import Path
import subprocess
import shutil
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
        for name in ('missing.yaml', '../outside.yaml', str(self.fragment), '', 'us/assets/font.txt'):
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

    def test_paths_are_yaml_scalars_in_inline_and_reference_profiles(self):
        for spelling in ('__ROM_PATH__', '"__ROM_PATH__"', "'__ROM_PATH__'"):
            self.profile.write_text('options:\n  target_path: ' + spelling + '\nsegments: []\n')
            for name in ('roms/a: b # c.z64', 'roms/quotes"and\\slashes.z64',
                         'roms/new\nline.z64', 'roms/été.z64'):
                for reference in (False, True):
                    with self.subTest(spelling=spelling, name=name, reference=reference):
                        result = profile_config.render_profile(self.profile, name, reference=reference)
                        self.assertEqual(yaml.safe_load(result)['options']['target_path'], name)

    def test_render_preserves_comments_hexadecimal_offsets_and_row_style(self):
        for marker in ('\n      # include note\n      include: us/assets/font.yaml # inline note\n',
                       ' {include: us/assets/font.yaml} # inline note\n'):
            self.profile.write_text(
                '# profile comment\noptions:\n  target_path: __ROM_PATH__ # ROM comment\n'
                'segments:\n  - name: font\n    type: group\n    start: 0x100\n'
                '    subsegments:' + marker + '  - [0x110] # end comment\n')
            self.fragment.write_text('# fragment comment\n- [0x100, bin, font/a] # row comment\n')
            rendered = profile_config.render_profile(self.profile, 'roms/test.z64')
            for text in ('# profile comment', '# ROM comment', '# inline note',
                         '# fragment comment', '# row comment', '# end comment',
                         'start: 0x100', '[0x100, bin, font/a]', '[0x110]'):
                self.assertIn(text, rendered)
            self.assertNotIn('include:', rendered)

    def test_nested_yaml_fragments_are_trackable_but_payloads_remain_ignored(self):
        repository = Path(__file__).resolve().parent.parent
        shutil.copy(repository / '.gitignore', self.root / '.gitignore')
        subprocess.run(['git', 'init', '-q', str(self.root)], check=True)
        for name, ignored in (
                ('config/profiles/us/assets/font.yaml', False),
                ('config/profiles/us/assets/audio/samples/bank17.yaml', False),
                ('config/profiles/us/assets/audio/samples/data.bin', True),
                ('assets/audio/data.bin', True)):
            result = subprocess.run(['git', 'check-ignore', '-q', name], cwd=self.root)
            self.assertEqual(result.returncode, 0 if ignored else 1, name)
        nested = self.fragment.parent / 'audio/samples/font.yaml'
        nested.parent.mkdir(parents=True)
        self.fragment.rename(nested)
        self.document['segments'][1]['subsegments']['include'] = 'us/assets/audio/samples/font.yaml'
        self.save()
        self.assertEqual(profile_config.load_profile(self.profile)['segments'][1]['subsegments'], self.rows)

    def test_make_plan_parses_each_input_once(self):
        repository = Path(__file__).resolve().parent.parent
        profile = repository / 'config/profiles/us.yaml'
        dependencies = profile_config.profile_dependencies(profile)
        with patch.object(sys, 'path', [str(repository / 'scripts'), *sys.path]), \
             patch.object(profile_config.yaml, 'safe_load', wraps=yaml.safe_load) as parse:
            tokens = profile_config.make_assets(profile)
        self.assertEqual(parse.call_count, len(dependencies))
        self.assertEqual(len([t for t in tokens if t.startswith('dep=')]), len(dependencies))
        self.assertEqual(len([t for t in tokens if t.startswith('font=')]), 96)
        self.assertTrue(any(t.startswith('source=src/') for t in tokens))
