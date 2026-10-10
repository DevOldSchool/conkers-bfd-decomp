"""Exercise the actual Makefile's asset scheduling without a ROM or MIPS linker."""
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile
import time
import unittest

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
from build_files import write_if_changed

MAKE = shutil.which('make')
MAKE_VERSION = subprocess.check_output([MAKE, 'ASSETS=1', '--version'], text=True).splitlines()[0] if MAKE else ''
MATCH = re.search(r'GNU Make (\d+)\.(\d+)', MAKE_VERSION)
GNU_MAKE = MATCH is not None


class GeneratedFileTests(unittest.TestCase):
    def test_unchanged_contents_preserve_timestamp_and_changes_replace_atomically(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / 'nested/part.bin'
            self.assertTrue(write_if_changed(path, b'original'))
            os.utime(path, ns=(1000000000, 1000000000))
            self.assertFalse(write_if_changed(path, b'original'))
            self.assertEqual(path.stat().st_mtime_ns, 1000000000)
            self.assertTrue(write_if_changed(path, b'changed'))
            self.assertEqual(path.read_bytes(), b'changed')
            self.assertFalse(path.with_name('part.bin.tmp').exists())


@unittest.skipUnless(GNU_MAKE, 'requires GNU make')
class AssetMakeTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        shutil.copy(ROOT / 'Makefile', self.root / 'Makefile')
        for name in ('config/profiles/us.yaml', 'config/rzip_layouts.json',
                     'toolchain/python-requirements.txt', 'roms/baserom.us.z64',
                     'config/texture_encoders.us.json',
                     'scripts/build_files.py', 'scripts/font_assets.py', 'scripts/mp3_assets.py',
                     'scripts/rzip_archive.py', 'scripts/rzip_extract.py',
                     'scripts/texture_assets.py', 'scripts/texture_catalog.py',
                     'scripts/texture_ci8.py', 'scripts/texture_rgba16.py',
                     'scripts/texture_native.py', 'scripts/rzip_pack.py',
                     'scripts/hud_assets.py', 'scripts/hud_additional_artwork.py',
                     'scripts/texture_model_catalog.py', 'scripts/texture_model_storage.py'):
            path = self.root / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.touch()
        shutil.copy(ROOT / 'scripts/profile_config.py', self.root / 'scripts/profile_config.py')
        shutil.copy(ROOT / 'scripts/build_timing.py', self.root / 'scripts/build_timing.py')
        (self.root / 'config/profiles/us.yaml').write_text(
            'segments:\n  - name: font\n    type: group\n'
            '    subsegments:\n      include: us/assets/font.yaml\n')
        self.fragment = self.root / 'config/profiles/us/assets/font.yaml'
        self.fragment.parent.mkdir(parents=True)
        self.fragment.write_text('- [0x100, bin, font/glyphs/0000]\n')
        script = '''from pathlib import Path
import sys
root = Path.cwd()
name = Path(__file__).stem
if (root / ('fail-' + name)).exists():
    raise SystemExit('intentional ' + name + ' failure')
font = name == 'font_splits'
texture = name == 'texture_build'
prefix = 'flat/textures' if texture else 'font/glyphs' if font else 'audio/mp3/streams'
def layout_bins(profile, *, configuration=None):
    assert configuration is not None
    rows = [(i, prefix + '/%04d' % i) for i in range(2)]
    return (rows, 2) if font or texture else rows
def bank_layout(profile, *, configuration=None):
    assert configuration is not None
    return 0, 1, [(0, 'audio/bank17/index')]
if __name__ == '__main__':
    assert sys.argv[1] == 'build-parts'
    inputs = root / ('build/assets/texture-build/us' if texture else 'build/fonts/us' if font else 'build/assets/mp3-bank/us')
    parts = root / ('build/us/textures/parts' if texture else 'build/us/fonts/parts' if font else 'build/us/audio/parts')
    for i in range(2):
        source = inputs / ('%04d.png' % i if texture else '%04d.pgm' % i if font else 'streams/%04d.mp3' % i)
        payload = source.read_bytes()
        path = parts / prefix / ('%04d.bin' % i)
        path.parent.mkdir(parents=True, exist_ok=True)
        if not path.exists() or path.read_bytes() != payload:
            path.write_bytes(payload)
    with (root / (name + '.calls')).open('a') as stream:
        stream.write('packed\\n')
'''
        (self.root / 'scripts/list_integrated_sources.py').write_text(
            'def profile_sources(profile, segment):\n    return []\n')
        for name in ('font_splits', 'mp3_bank', 'audio_boundaries', 'texture_build'):
            (self.root / f'scripts/{name}.py').write_text(script)
        self.ld = self.root / 'scripts/fake_ld.py'
        self.ld.write_text('''from pathlib import Path
import sys
output = Path(sys.argv[sys.argv.index('-o') + 1])
output.write_bytes(Path(sys.argv[-1]).read_bytes())
''')
        for directory, suffix in (('build/fonts/us', '.pgm'),
                                  ('build/assets/texture-build/us', '.png'),
                                  ('build/assets/mp3-bank/us/streams', '.mp3')):
            parent = self.root / directory
            parent.mkdir(parents=True)
            for i in range(2):
                (parent / f'{i:04d}{suffix}').write_bytes(bytes([i]))
        for directory in ('build/fonts/us', 'build/assets/mp3-bank/us', 'build/assets/texture-build/us/1063'):
            (self.root / directory).mkdir(parents=True, exist_ok=True)
            (self.root / directory / 'manifest.json').write_text('{}')

    def run_make(self, kind):
        prefix = 'flat/textures' if kind == 'texture' else 'font/glyphs' if kind == 'font' else 'audio/mp3/streams'
        objects = [self.root / f'build/us/assets/{prefix}/{i:04d}.o' for i in range(2)]
        result = subprocess.run([MAKE, 'ASSETS=1', '-j4', f'LD={sys.executable} {self.ld}',
                                 *[str(p.relative_to(self.root)) for p in objects]],
                                cwd=self.root, text=True, capture_output=True)
        return result, objects

    def test_no_change_and_single_edit_only_rebuild_affected_objects(self):
        for kind, source, packer in (
                ('font', 'build/fonts/us/0000.pgm', 'font_splits'),
                ('texture', 'build/assets/texture-build/us/0000.png', 'texture_build'),
                ('mp3', 'build/assets/mp3-bank/us/streams/0000.mp3', 'mp3_bank')):
            with self.subTest(kind=kind):
                result, objects = self.run_make(kind)
                self.assertEqual(result.returncode, 0, result.stderr)
                before = [p.stat().st_mtime_ns for p in objects]
                result, _ = self.run_make(kind)
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertEqual([p.stat().st_mtime_ns for p in objects], before)
                self.assertEqual((self.root / (packer + '.calls')).read_text(), 'packed\n')
                time.sleep(1.05)
                (self.root / source).write_bytes(b'changed')
                result, _ = self.run_make(kind)
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertEqual(objects[0].read_bytes(), b'changed')
                self.assertGreater(objects[0].stat().st_mtime_ns, before[0])
                self.assertEqual(objects[1].stat().st_mtime_ns, before[1])

    def test_model_parts_recover_and_preserve_unchanged_linker_objects(self):
        shutil.copy(ROOT / 'scripts/build_files.py', self.root / 'scripts/build_files.py')
        profile = self.root / 'config/profiles/us.yaml'
        profile.write_text(profile.read_text() +
            '  - name: asset_bank_03\n    type: group\n')
        (self.root / 'config/model_build.us.json').write_text('{}')
        (self.root / 'scripts/model_build.py').write_text("""from pathlib import Path
from build_files import write_if_changed
def layout_bins(profile, *, configuration=None):
    return [(0, 'models/bank03/0003')], 1
if __name__ == '__main__':
    source = Path('build/assets/model-build/us/03/0003/model.json')
    write_if_changed(Path('build/us/models/parts/models/bank03/0003.bin'), source.read_bytes())
""")
        inputs = self.root / 'build/assets/model-build/us/03/0003'
        inputs.mkdir(parents=True)
        (inputs / 'manifest.json').write_text('{}')
        source = inputs / 'model.json'
        source.write_bytes(b'model')
        target = self.root / 'build/us/assets/models/bank03/0003.o'
        part = self.root / 'build/us/models/parts/models/bank03/0003.bin'
        def run():
            return subprocess.run([MAKE, 'ASSETS=1', f'LD={sys.executable} {self.ld}',
                                   str(target.relative_to(self.root))],
                                  cwd=self.root, text=True, capture_output=True)
        result = run()
        self.assertEqual(result.returncode, 0, result.stderr)
        stamp = target.stat().st_mtime_ns
        self.assertEqual(run().returncode, 0)
        self.assertEqual(target.stat().st_mtime_ns, stamp)
        part.unlink()
        self.assertEqual(run().returncode, 0)
        self.assertEqual(target.read_bytes(), b'model')
        time.sleep(1.05)
        source.unlink()
        self.assertNotEqual(run().returncode, 0)
        self.assertEqual(target.read_bytes(), b'model')

    def test_every_texture_module_and_encoder_contract_invalidates_packing(self):
        dependencies = sorted(path.relative_to(ROOT) for path in (ROOT / 'scripts').glob('texture_*.py'))
        dependencies += [Path('scripts/texture_future_selector.py'),
                         Path('config/texture_encoders.us.json')]
        result, objects = self.run_make('texture')
        self.assertEqual(result.returncode, 0, result.stderr)
        before = [path.stat().st_mtime_ns for path in objects]
        stamp = self.root / 'build/us/textures/parts.stamp'
        calls = self.root / 'texture_build.calls'
        for number, relative in enumerate(dependencies, 2):
            with self.subTest(dependency=relative):
                dependency = self.root / relative
                dependency.touch()
                original = dependency.stat()
                # Exercise the actual Make graph, including newly added modules,
                # without sleeping for Make 3.81's second-resolution clock.
                newer = stamp.stat().st_mtime_ns + 2_000_000_000
                os.utime(dependency, ns=(newer, newer))
                try:
                    result, _ = self.run_make('texture')
                finally:
                    os.utime(dependency, ns=(original.st_atime_ns, original.st_mtime_ns))
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertEqual(calls.read_text().count('packed'), number)
                self.assertEqual([path.stat().st_mtime_ns for path in objects], before)

    def test_asset_link_commands_are_logged_on_success_and_failure(self):
        for kind in ('font', 'mp3'):
            with self.subTest(kind=kind):
                result, objects = self.run_make(kind)
                self.assertEqual(result.returncode, 0, result.stderr)
                for path in objects:
                    self.assertIn(str(path), result.stderr)
                self.assertIn('fake_ld.py -r -b binary', result.stderr)
                unchanged, _ = self.run_make(kind)
                self.assertEqual(unchanged.returncode, 0, unchanged.stderr)
                self.assertNotIn('fake_ld.py -r -b binary', unchanged.stderr)
        self.ld.write_text('raise SystemExit(7)\n')
        for kind in ('font', 'mp3'):
            with self.subTest(failed_kind=kind):
                prefix = 'font/glyphs' if kind == 'font' else 'audio/mp3/streams'
                path = self.root / f'build/us/assets/{prefix}/0000.o'
                path.unlink()
                result, _ = self.run_make(kind)
                self.assertNotEqual(result.returncode, 0)
                self.assertIn('fake_ld.py -r -b binary', result.stderr)
                self.assertIn(str(path), result.stderr)

    def test_missing_part_is_recovered_and_missing_editable_input_fails(self):
        result, objects = self.run_make('font')
        self.assertEqual(result.returncode, 0, result.stderr)
        (self.root / 'build/us/fonts/parts/font/glyphs/0000.bin').unlink()
        result, _ = self.run_make('font')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(objects[0].read_bytes(), b'\0')
        before = [p.stat().st_mtime_ns for p in objects]
        time.sleep(1.05)  # GNU make 3.81 compares timestamps at second resolution.
        (self.root / 'build/fonts/us/0000.pgm').unlink()
        result, _ = self.run_make('font')
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual([p.stat().st_mtime_ns for p in objects], before)

    def test_default_goal_is_help_without_packing_assets(self):
        default = subprocess.run([MAKE, 'ASSETS=1'], cwd=self.root, text=True, capture_output=True)
        help_result = subprocess.run([MAKE, 'ASSETS=1', 'help'], cwd=self.root, text=True, capture_output=True)
        self.assertEqual(default.returncode, 0, default.stderr)
        self.assertEqual(help_result.returncode, 0, help_result.stderr)
        self.assertEqual(default.stdout, help_result.stdout)
        self.assertFalse((self.root / 'font_splits.calls').exists())
        self.assertFalse((self.root / 'mp3_bank.calls').exists())
        self.assertFalse((self.root / 'build/us').exists())

    def test_fragment_change_invalidates_packing_and_missing_fragment_stops_make(self):
        result, objects = self.run_make('font')
        self.assertEqual(result.returncode, 0, result.stderr)
        before = [p.stat().st_mtime_ns for p in objects]
        time.sleep(1.05)  # macOS make 3.81 has second-resolution timestamps.
        self.fragment.write_text('- [0x108, bin, font/glyphs/0000]\n')
        result, _ = self.run_make('font')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual((self.root / 'font_splits.calls').read_text(), 'packed\npacked\n')
        self.assertEqual([p.stat().st_mtime_ns for p in objects], before)
        self.fragment.unlink()
        result, _ = self.run_make('font')
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('profile_config.py make-assets failed', result.stderr)
        self.assertEqual([p.stat().st_mtime_ns for p in objects], before)

    def test_all_bin_list_errors_stop_make_at_the_generator(self):
        for name in ('font_splits', 'mp3_bank', 'audio_boundaries'):
            with self.subTest(name=name):
                flag = self.root / ('fail-' + name)
                flag.touch()
                result, objects = self.run_make('font')
                self.assertNotEqual(result.returncode, 0)
                self.assertIn(f'intentional {name} failure', result.stderr)
                self.assertIn('profile_config.py make-assets failed', result.stderr)
                self.assertFalse(any(p.exists() for p in objects))
                flag.unlink()

    def test_broken_us_fragment_does_not_block_housekeeping_reference_or_eu(self):
        self.fragment.unlink()
        for args in (['help'], ['clean'], ['-n', 'prepare-reference'],
                     ['PROFILE=eu', 'build/eu/assets/boot.o']):
            with self.subTest(args=args):
                assets = self.root / 'assets'
                assets.mkdir(exist_ok=True)
                (assets / 'boot.bin').write_bytes(b'boot')
                result = subprocess.run([MAKE, 'ASSETS=1', f'LD={sys.executable} {self.ld}', *args],
                                        cwd=self.root, text=True, capture_output=True)
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertNotIn('profile_config.py', result.stderr)
        self.assertEqual((self.root / 'build/eu/assets/boot.o').read_bytes(), b'boot')

    def test_code_object_does_not_require_rom_or_run_packers(self):
        (self.root / 'roms/baserom.us.z64').unlink()
        (self.root / 'src').mkdir()
        (self.root / 'src/foo.c').write_text('code')
        (self.root / 'scripts/compile_c.py').write_text(
            "from pathlib import Path\nimport sys\n"
            "Path(sys.argv[sys.argv.index('--output') + 1]).write_text('object')\n")
        for goal in ('build/us/src/foo.o', './build/us/src/foo.o'):
            result = subprocess.run([MAKE, 'ASSETS=1', goal], cwd=self.root, text=True, capture_output=True)
            self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual((self.root / 'build/us/src/foo.o').read_text(), 'object')
        self.assertFalse((self.root / 'font_splits.calls').exists())
        self.assertFalse((self.root / 'mp3_bank.calls').exists())

    def test_default_code_object_bypasses_fragments_and_asset_modules(self):
        self.fragment.unlink()
        (self.root / 'scripts/texture_build.py').write_text('raise ImportError("unavailable codec")')
        (self.root / 'src').mkdir()
        (self.root / 'src/foo.c').write_text('code')
        (self.root / 'scripts/compile_c.py').write_text(
            "from pathlib import Path\nimport sys\n"
            "Path(sys.argv[sys.argv.index('--output') + 1]).write_text('object')\n")
        result = subprocess.run([MAKE, 'build/us/src/foo.o'], cwd=self.root,
                                text=True, capture_output=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual((self.root / 'build/us/src/foo.o').read_text(), 'object')
        for codec in ('texture_build', 'font_splits', 'mp3_bank'):
            self.assertFalse((self.root / (codec + '.calls')).exists())

    def test_default_mode_rejects_reconstructed_targets_even_if_already_present(self):
        for name in ('flat/textures/0000', 'font/glyphs/0000', 'audio/mp3/streams/0000'):
            target = self.root / ('build/us/assets/' + name + '.o')
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_text('existing object')
            result = subprocess.run([MAKE, str(target.relative_to(self.root))], cwd=self.root,
                                    text=True, capture_output=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn('require ASSETS=1', result.stderr)

    def test_game_and_diff_goals_skip_broken_fragments_and_packing(self):
        self.fragment.unlink()
        # Dry-run the real goal graph. Missing game/toolchain prerequisites in
        # this asset-only fixture may stop it, but asset planning must not.
        for goal in ('game-asm', 'game-asm-prepare', 'game-integrated',
                     'game-integrated-refresh', 'game-integrated-prepare',
                     'game-integrated-raw', 'diff',
                     './build/game-integrated/us/conker.game.us.integrated.bin'):
            with self.subTest(goal=goal):
                result = subprocess.run([MAKE, 'ASSETS=1', '-n', goal], cwd=self.root,
                                        text=True, capture_output=True)
                output = result.stdout + result.stderr
                self.assertNotIn('profile_config.py make-assets failed', output)
                self.assertNotIn('font_splits.py build-parts', output)
                self.assertNotIn('mp3_bank.py build-parts', output)
                self.assertNotIn('roms/baserom.us.z64', result.stderr)
        self.assertFalse((self.root / 'font_splits.calls').exists())
        self.assertFalse((self.root / 'mp3_bank.calls').exists())

    def test_mixed_game_and_asset_goals_still_validate_fragments(self):
        self.fragment.unlink()
        result = subprocess.run([MAKE, 'ASSETS=1', '-n', 'game-asm', 'build/us/conker.us.z64'],
                                cwd=self.root, text=True, capture_output=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('profile_config.py make-assets failed', result.stderr)
        self.assertNotIn('Traceback', result.stderr)

    def test_new_aggregate_goal_packs_and_links_asset_inputs(self):
        with (self.root / 'Makefile').open('a') as stream:
            stream.write('\n.PHONY: all\nall: build/combined.bin\n'
                         'build/combined.bin: $(FONT_OBJS) $(MP3_BANK_OBJS)\n'
                         '\tcat $^ > $@\n')
        result = subprocess.run([MAKE, 'ASSETS=1', '-j4', f'LD={sys.executable} {self.ld}', 'all'],
                                cwd=self.root, text=True, capture_output=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        for prefix in ('font/glyphs', 'audio/mp3/streams'):
            for index in range(2):
                path = self.root / f'build/us/assets/{prefix}/{index:04d}.o'
                self.assertEqual(path.read_bytes(), bytes([index]))
        combined = self.root / 'build/combined.bin'
        self.assertEqual(combined.read_bytes(), bytes([0, 1, 0, 1]))
        before = combined.stat().st_mtime_ns
        unchanged = subprocess.run([MAKE, 'ASSETS=1', '-j4', f'LD={sys.executable} {self.ld}', 'all'],
                                   cwd=self.root, text=True, capture_output=True)
        self.assertEqual(unchanged.returncode, 0, unchanged.stderr)
        self.assertEqual(combined.stat().st_mtime_ns, before)
        time.sleep(1.05)
        (self.root / 'build/fonts/us/0000.pgm').write_bytes(b'changed')
        changed = subprocess.run([MAKE, 'ASSETS=1', '-j4', f'LD={sys.executable} {self.ld}', 'all'],
                                 cwd=self.root, text=True, capture_output=True)
        self.assertEqual(changed.returncode, 0, changed.stderr)
        self.assertEqual(combined.read_bytes(), b'changed' + bytes([1, 0, 1]))
        self.fragment.unlink()
        failed = subprocess.run([MAKE, 'ASSETS=1', 'all'], cwd=self.root, text=True, capture_output=True)
        self.assertIn('profile_config.py make-assets failed', failed.stderr)
        self.assertNotEqual(failed.returncode, 0)

    def test_dot_prefixed_rom_goal_retains_all_asset_prerequisites(self):
        # This fixture lacks the rest of the ROM. Inspect Make's actual target
        # database rather than claiming a ROM link from these synthetic assets.
        result = subprocess.run([MAKE, 'ASSETS=1', '-np', './build/us/conker.us.z64'],
                                cwd=self.root, text=True, capture_output=True)
        objects = next(line for line in result.stdout.splitlines() if line.startswith('ASSET_OBJS := '))
        for name in ('font/glyphs/0000', 'audio/mp3/streams/0000', 'audio/bank17/index'):
            self.assertIn('build/us/assets/' + name + '.o', objects)
        self.assertNotIn('profile_config.py make-assets failed', result.stderr)
