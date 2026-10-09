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
MAKE_VERSION = subprocess.check_output([MAKE, '--version'], text=True).splitlines()[0] if MAKE else ''
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
                     'scripts/build_files.py', 'scripts/font_assets.py', 'scripts/mp3_assets.py',
                     'scripts/rzip_archive.py', 'scripts/rzip_extract.py'):
            path = self.root / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.touch()
        shutil.copy(ROOT / 'scripts/profile_config.py', self.root / 'scripts/profile_config.py')
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
prefix = 'font/glyphs' if font else 'audio/mp3/streams'
def layout_bins(profile, *, configuration=None):
    assert configuration is not None
    rows = [(i, prefix + '/%04d' % i) for i in range(2)]
    return (rows, 2) if font else rows
def bank_layout(profile, *, configuration=None):
    assert configuration is not None
    return 0, 1, [(0, 'audio/bank17/index')]
if __name__ == '__main__':
    assert sys.argv[1] == 'build-parts'
    inputs = root / ('build/fonts/us' if font else 'build/assets/mp3-bank/us')
    parts = root / ('build/us/fonts/parts' if font else 'build/us/audio/parts')
    for i in range(2):
        source = inputs / ('%04d.pgm' % i if font else 'streams/%04d.mp3' % i)
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
        for name in ('font_splits', 'mp3_bank', 'audio_boundaries'):
            (self.root / f'scripts/{name}.py').write_text(script)
        self.ld = self.root / 'scripts/fake_ld.py'
        self.ld.write_text('''from pathlib import Path
import sys
output = Path(sys.argv[sys.argv.index('-o') + 1])
output.write_bytes(Path(sys.argv[-1]).read_bytes())
''')
        for directory, suffix in (('build/fonts/us', '.pgm'),
                                  ('build/assets/mp3-bank/us/streams', '.mp3')):
            parent = self.root / directory
            parent.mkdir(parents=True)
            for i in range(2):
                (parent / f'{i:04d}{suffix}').write_bytes(bytes([i]))
        for directory in ('build/fonts/us', 'build/assets/mp3-bank/us'):
            (self.root / directory / 'manifest.json').write_text('{}')

    def run_make(self, kind):
        prefix = 'font/glyphs' if kind == 'font' else 'audio/mp3/streams'
        objects = [self.root / f'build/us/assets/{prefix}/{i:04d}.o' for i in range(2)]
        result = subprocess.run([MAKE, '-j4', f'LD={sys.executable} {self.ld}',
                                 *[str(p.relative_to(self.root)) for p in objects]],
                                cwd=self.root, text=True, capture_output=True)
        return result, objects

    def test_no_change_and_single_edit_only_rebuild_affected_objects(self):
        for kind, source, packer in (
                ('font', 'build/fonts/us/0000.pgm', 'font_splits'),
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
        default = subprocess.run([MAKE], cwd=self.root, text=True, capture_output=True)
        help_result = subprocess.run([MAKE, 'help'], cwd=self.root, text=True, capture_output=True)
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
                result = subprocess.run([MAKE, f'LD={sys.executable} {self.ld}', *args],
                                        cwd=self.root, text=True, capture_output=True)
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertNotIn('profile_config.py', result.stderr)
        self.assertEqual((self.root / 'build/eu/assets/boot.o').read_bytes(), b'boot')
