"""ROM modes cannot confuse reconstructed assets with the original-byte fast path."""
from contextlib import chdir
import json
import shutil
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

import yaml

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import prepare_rom
import profile_config


class RomPreparationTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.context = chdir(self.root)
        self.context.__enter__()
        self.addCleanup(self.context.__exit__, None, None, None)
        self.profile = Path('config/profiles/us.yaml')
        self.fragment = Path('config/profiles/us/assets/font.yaml')
        self.document = dict(options=dict(target_path='__ROM_PATH__',
            elf_path='build/us/conker.us.elf', ld_script_path='build/us/conker.us.ld',
            symbol_addrs_path=['config/symbols/us.txt']), segments=[
            dict(name='main', type='code', start=0, subsegments=[[0, 'c', 'main/test']]),
            dict(name='font', type='group', start=16, align=1, subalign=1, follows_vram='main',
                 subsegments=dict(include='us/assets/font.yaml')), [32]])
        files = {'config/profiles/us.yaml': yaml.safe_dump(self.document),
                 str(self.fragment): '- [16, bin, font/glyphs/0000]\n',
                 'roms/baserom.us.z64': 'ROM', 'config/symbols/us.txt': 'symbol',
                 'src/main/test.c': 'source', 'scripts/prepare_rom.py': 'script',
                 'scripts/profile_config.py': 'script', 'scripts/build_files.py': 'script',
                 'toolchain/tools.lock.json': '{}', 'toolchain/python-requirements.txt': 'splat'}
        for name, contents in files.items():
            path = Path(name)
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(contents)
        self.version = patch.object(prepare_rom.importlib.metadata, 'version', return_value='test')
        self.version.start()
        self.addCleanup(self.version.stop)
        split = patch.object(prepare_rom.subprocess, 'run', side_effect=self.fake_split)
        self.split = split.start()
        self.addCleanup(split.stop)

    def fake_split(self, command, **kwargs):
        configuration = yaml.safe_load(Path(command[-1]).read_text())
        asm = Path('asm/us/0.s')
        asm.parent.mkdir(parents=True, exist_ok=True)
        asm.write_text('assembly')
        paths = prepare_rom.generated_paths(configuration, Path(command[-1]), 'us')
        for path in paths:
            if str(path).endswith('.yaml'):
                continue
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text('generated ' + str(path))

    def test_original_mode_ignores_unused_fragments_and_preserves_code_and_layout(self):
        self.fragment.unlink()
        original = profile_config.original_asset_profile(self.profile)
        self.assertEqual(original['segments'][0], self.document['segments'][0])
        self.assertEqual(original['segments'][1], dict(name='font', type='bin', start=16,
            align=1, subalign=1, follows_vram='main'))
        plan = profile_config.make_original_assets(self.profile)
        self.assertIn('original=assets/font.bin', plan)
        self.assertIn('source=src/main/test.c', plan)
        prepare_rom.prepare('us')
        with self.assertRaises(FileNotFoundError):
            prepare_rom.prepare('us', assets=True)

    def test_cached_split_keeps_mtimes_and_c_edits_do_not_resplit(self):
        prepare_rom.prepare('us')
        before = Path('asm/us/0.s').stat().st_mtime_ns
        Path('src/main/test.c').write_text('changed C')
        prepare_rom.prepare('us')
        self.assertEqual(self.split.call_count, 1)
        self.assertEqual(Path('asm/us/0.s').stat().st_mtime_ns, before)

    def test_missing_changed_or_extra_generated_files_invalidate_cache(self):
        prepare_rom.prepare('us')
        for name, action in [('assets/font.bin', 'delete'), ('asm/us/0.s', 'change'),
                             ('asm/us/stale.s', 'change'), ('build/us/original-assets/conker.us.ld', 'change')]:
            with self.subTest(name=name):
                previous = self.split.call_count
                if action == 'delete':
                    Path(name).unlink()
                else:
                    Path(name).write_text('wrong')
                prepare_rom.prepare('us')
                self.assertEqual(self.split.call_count, previous + 1)
        self.assertFalse(Path('asm/us/stale.s').exists())

    def test_rom_symbols_tools_profile_and_refresh_invalidate_cache(self):
        prepare_rom.prepare('us')
        for name in ('roms/baserom.us.z64', 'config/symbols/us.txt', 'scripts/prepare_rom.py',
                     'toolchain/tools.lock.json'):
            previous = self.split.call_count
            Path(name).write_text('changed')
            prepare_rom.prepare('us')
            self.assertEqual(self.split.call_count, previous + 1)
        self.document['segments'][0]['subsegments'][0][2] = 'main/other'
        self.profile.write_text(yaml.safe_dump(self.document))
        previous = self.split.call_count
        prepare_rom.prepare('us')
        prepare_rom.prepare('us', refresh=True)
        self.assertEqual(self.split.call_count, previous + 2)

    def test_switching_modes_preserves_separate_outputs_and_reuses_identical_assembly(self):
        prepare_rom.prepare('us')
        prepare_rom.prepare('us', assets=True)
        prepare_rom.prepare('us')
        prepare_rom.prepare('us', assets=True)
        self.assertEqual(self.split.call_count, 2)
        for name in ('build/us/.prepared-original.json', 'build/us/.prepared-rebuilt.json',
                     'assets/font.bin', 'assets/font/glyphs/0000.bin',
                     'build/us/conker.us.ld', 'build/us/original-assets/conker.us.ld'):
            self.assertTrue(Path(name).is_file(), name)
        self.fragment.write_text('- [16, bin, font/glyphs/0001]\n')
        prepare_rom.prepare('us')
        self.assertEqual(self.split.call_count, 2)
        prepare_rom.prepare('us', assets=True)
        self.assertEqual(self.split.call_count, 3)

    def test_unnamed_original_binary_uses_splat_hexadecimal_name(self):
        self.document['segments'].insert(-1, dict(type='bin', start=30))
        self.profile.write_text(yaml.safe_dump(self.document))
        prepare_rom.prepare('us')
        self.assertTrue(Path('assets/1E.bin').is_file())
        self.assertIn('original=assets/1E.bin', profile_config.make_original_assets(self.profile))

    def test_invalid_cache_record_is_rebuilt(self):
        prepare_rom.prepare('us')
        stamp = Path('build/us/.prepared-original.json')
        record = json.loads(stamp.read_text())
        record['outputs'] = ['invalid']
        stamp.write_text(json.dumps(record))
        prepare_rom.prepare('us')
        self.assertEqual(self.split.call_count, 2)

    def test_failed_split_invalidates_stamp_and_next_attempt_recovers(self):
        prepare_rom.prepare('us')
        self.split.side_effect = subprocess.CalledProcessError(1, 'splat')
        with self.assertRaises(subprocess.CalledProcessError):
            prepare_rom.prepare('us', refresh=True)
        self.assertFalse(Path('build/us/.prepared-original.json').exists())
        self.split.side_effect = self.fake_split
        prepare_rom.prepare('us')
        self.assertEqual(self.split.call_count, 3)


class TimingTests(unittest.TestCase):
    @unittest.skipUnless(shutil.which('make'), 'requires Make')
    def test_timed_recursive_make_preserves_parallel_jobserver(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'worker.py').write_text(
                "from pathlib import Path\nimport sys, time\n"
                "name = sys.argv[1]\nPath(name).touch()\n"
                "other = Path('b' if name == 'a' else 'a')\n"
                "deadline = time.monotonic() + 5\n"
                "while not other.exists() and time.monotonic() < deadline: time.sleep(.01)\n"
                "assert other.exists(), 'recursive Make lost parallelism'\n")
            (root / 'Makefile').write_text(
                '.PHONY: all children a b\nall:\n'
                f'\t+{sys.executable} {ROOT / "scripts/build_timing.py"} --profile us --mode original --stage child -- $(MAKE) children\n'
                'children: a b\na b:\n'
                f'\t{sys.executable} worker.py $@\n')
            result = subprocess.run(['make', '-j2'], cwd=root, capture_output=True, text=True, timeout=15)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertNotIn('jobserver unavailable', result.stderr)

    def test_records_success_and_failure_without_hiding_exit_status(self):
        with tempfile.TemporaryDirectory() as directory:
            for status in (0, 7):
                result = subprocess.run([sys.executable, str(ROOT / 'scripts/build_timing.py'),
                    '--profile', 'us', '--mode', 'original', '--stage', 'test', '--',
                    sys.executable, '-c', f'raise SystemExit({status})'], cwd=directory,
                    text=True, capture_output=True)
                self.assertEqual(result.returncode, status, result.stderr)
                self.assertIn('TIMING us/original test:', result.stdout)
            records = [json.loads(line) for line in
                (Path(directory) / 'build/timings/us-original.jsonl').read_text().splitlines()]
            self.assertEqual([r['exit_code'] for r in records], [0, 7])
            self.assertTrue(all(r['elapsed_seconds'] >= 0 for r in records))


if __name__ == '__main__':
    unittest.main()
