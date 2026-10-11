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
                     'scripts/texture_native.py', 'scripts/rzip_pack.py', 'scripts/model_assets.py',
                     'scripts/model_attachment_format.py', 'scripts/model_bundle_build.py', 'scripts/model_color_build.py', 'scripts/model_aux_build.py', 'scripts/model_effect_format.py', 'scripts/model_emission_points.py',
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
        (self.root / 'scripts/model_build.py').write_text('BANKS = (3, 4, 9)\n')
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

    def run_make(self, kind, *, jobs=4):
        prefix = 'flat/textures' if kind == 'texture' else 'font/glyphs' if kind == 'font' else 'audio/mp3/streams'
        objects = [self.root / f'build/us/assets/{prefix}/{i:04d}.o' for i in range(2)]
        result = subprocess.run([MAKE, 'ASSETS=1', f'-j{jobs}', f'LD={sys.executable} {self.ld}',
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

    def test_sequences_rebuild_from_records_and_missing_inputs_cannot_reuse_objects(self):
        shutil.copy(ROOT / 'scripts/build_files.py', self.root / 'scripts/build_files.py')
        for name in ('sequence_codec', 'audio_assets'):
            (self.root / f'scripts/{name}.py').touch()
        profile = self.root / 'config/profiles/us.yaml'
        profile.write_text(profile.read_text() + '  - name: asset_bank_17\n    type: group\n')
        (self.root / 'scripts/audio_boundaries.py').write_text("""def bank_layout(profile, *, configuration=None):
    return 0, 100, [(0, 'audio/bank17/sequences/index'),
                    (8, 'audio/bank17/sequences/0000'),
                    (40, 'audio/bank17/sequences/padding/00000028'),
                    (48, 'audio/bank17/sequences/0001')]
""")
        (self.root / 'scripts/sequence_build.py').write_text("""from pathlib import Path
from build_files import write_if_changed
for index in range(2):
    source = Path(f'build/assets/sequence-build/us/{index:04d}')
    assert (source / 'manifest.json').read_text() == '{}'
    payload = (source / 'sequence.json').read_bytes()
    write_if_changed(Path(f'build/us/sequences/parts/audio/bank17/sequences/{index:04d}.bin'), payload)
with Path('sequence.calls').open('a') as log:
    log.write('packed\\n')
""")
        for index in range(2):
            source = self.root / f'build/assets/sequence-build/us/{index:04d}'
            source.mkdir(parents=True)
            (source / 'manifest.json').write_text('{}')
            (source / 'sequence.json').write_text(f'sequence{index}')
        names = [f'build/us/assets/audio/bank17/sequences/{i:04d}.o' for i in range(2)]
        def run():
            return subprocess.run([MAKE, 'ASSETS=1', '-j4', f'LD={sys.executable} {self.ld}', *names],
                                  cwd=self.root, text=True, capture_output=True)
        result = run()
        self.assertEqual(result.returncode, 0, result.stderr)
        objects = [self.root / name for name in names]
        before = [p.stat().st_mtime_ns for p in objects]
        self.assertEqual(run().returncode, 0)
        self.assertEqual([p.stat().st_mtime_ns for p in objects], before)
        self.assertEqual((self.root / 'sequence.calls').read_text(), 'packed\n')
        time.sleep(1.05)
        source = self.root / 'build/assets/sequence-build/us/0000/sequence.json'
        source.write_text('edited sequence')
        self.assertEqual(run().returncode, 0)
        self.assertEqual(objects[0].read_text(), 'edited sequence')
        self.assertEqual(objects[1].stat().st_mtime_ns, before[1])
        part = self.root / 'build/us/sequences/parts/audio/bank17/sequences/0000.bin'
        part.unlink()
        self.assertEqual(run().returncode, 0)
        self.assertEqual(part.read_text(), 'edited sequence')
        source.unlink()
        self.assertNotEqual(run().returncode, 0)
        self.assertEqual(objects[0].read_text(), 'edited sequence')
        with (self.root / 'Makefile').open('a') as file:
            file.write('\nshow-sequences:\n\t@echo $(SEQUENCE_BINS)\n')
        listing = subprocess.run([MAKE, 'ASSETS=1', '--no-print-directory', 'show-sequences'],
                                 cwd=self.root, text=True, capture_output=True)
        self.assertEqual(listing.returncode, 0, listing.stderr)
        self.assertEqual(listing.stdout.split(), [f'assets/audio/bank17/sequences/{i:04d}.bin' for i in range(2)])

    def test_sound_bank_parts_exclude_raw_holes_and_recheck_missing_manifests(self):
        shutil.copy(ROOT / 'scripts/build_files.py', self.root / 'scripts/build_files.py')
        for name in ('sound_bank_codec', 'audio_assets'):
            (self.root / f'scripts/{name}.py').touch()
        profile = self.root / 'config/profiles/us.yaml'
        profile.write_text(profile.read_text() + '  - name: asset_bank_17\n    type: group\n')
        (self.root / 'scripts/audio_boundaries.py').write_text("""def bank_layout(profile, *, configuration=None):
    return 0, 100, [(0, 'audio/bank17/index'),
                    (8, 'audio/bank17/sound_bank_control_rzip'),
                    (40, 'audio/bank17/sound-bank/regions/00000000'),
                    (48, 'audio/bank17/sound-bank/unreconstructed/00000008')]
""")
        (self.root / 'scripts/sound_bank_build.py').write_text("""from pathlib import Path
from build_files import write_if_changed
for part, name in [('control', 'sound_bank_control_rzip'), ('00000000', 'sound-bank/regions/00000000')]:
    source = Path('build/assets/sound-bank-build/us') / part
    assert (source / 'manifest.json').read_text() == '{}'
    payload = (source / 'records.json').read_bytes()
    write_if_changed(Path('build/us/sound-bank/parts/audio/bank17') / (name + '.bin'), payload)
with Path('sound-bank.calls').open('a') as log:
    log.write('packed\\n')
""")
        for part in ('control', '00000000'):
            source = self.root / 'build/assets/sound-bank-build/us' / part
            source.mkdir(parents=True)
            (source / 'manifest.json').write_text('{}')
            (source / 'records.json').write_text(part)
        hole = self.root / 'assets/audio/bank17/sound-bank/unreconstructed/00000008.bin'
        hole.parent.mkdir(parents=True)
        hole.write_text('unexplained original bytes')
        names = ['build/us/assets/audio/bank17/' + name + '.o' for name in (
            'sound_bank_control_rzip', 'sound-bank/regions/00000000', 'sound-bank/unreconstructed/00000008')]
        def run():
            return subprocess.run([MAKE, 'ASSETS=1', '-j4', f'LD={sys.executable} {self.ld}', *names],
                                  cwd=self.root, text=True, capture_output=True)
        result = run()
        self.assertEqual(result.returncode, 0, result.stderr)
        objects = [self.root / name for name in names]
        self.assertEqual([p.read_text() for p in objects], ['control', '00000000', 'unexplained original bytes'])
        before = [p.stat().st_mtime_ns for p in objects]
        self.assertEqual(run().returncode, 0)
        self.assertEqual([p.stat().st_mtime_ns for p in objects], before)
        self.assertEqual((self.root / 'sound-bank.calls').read_text(), 'packed\n')
        time.sleep(1.05)
        source = self.root / 'build/assets/sound-bank-build/us/00000000/records.json'
        source.write_text('changed native records')
        self.assertEqual(run().returncode, 0)
        self.assertEqual(objects[1].read_text(), 'changed native records')
        self.assertEqual([objects[i].stat().st_mtime_ns for i in (0, 2)], [before[i] for i in (0, 2)])
        part = self.root / 'build/us/sound-bank/parts/audio/bank17/sound-bank/regions/00000000.bin'
        part.unlink()
        self.assertEqual(run().returncode, 0)
        self.assertEqual(part.read_text(), 'changed native records')
        (source.parent / 'manifest.json').unlink()
        self.assertNotEqual(run().returncode, 0)
        self.assertEqual(objects[1].read_text(), 'changed native records')

    def test_bank03_model_parts_recover_and_preserve_unchanged_linker_objects(self):
        self.check_model_parts('03')

    def test_bank04_model_parts_recover_and_preserve_unchanged_linker_objects(self):
        self.check_model_parts('04')

    def test_bank09_model_parts_recover_and_preserve_unchanged_linker_objects(self):
        self.check_model_parts('09')

    def setup_model_banks(self, banks):
        shutil.copy(ROOT / 'scripts/build_files.py', self.root / 'scripts/build_files.py')
        profile = self.root / 'config/profiles/us.yaml'
        profile.write_text(profile.read_text() + ''.join(
            f'  - name: asset_bank_{bank}\n    type: group\n' for bank in banks))
        (self.root / 'config/model_build.us.json').write_text('{}')
        (self.root / 'scripts/model_build.py').write_text("""from pathlib import Path
import argparse
from build_files import write_if_changed
BANKS = (3, 4, 9)
def layout_bins(profile, *, bank, configuration=None):
    assert configuration is not None
    assert any(isinstance(s, dict) and s.get('name') == f'asset_bank_{bank:02d}' for s in configuration['segments'])
    return [(0, f'models/bank{bank:02d}/0003')], 1
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('command', choices=['build-parts'])
    parser.add_argument('--bank', type=int, choices=BANKS, required=True)
    bank = parser.parse_args().bank
    if Path(f'fail-model-{bank:02d}').exists():
        raise SystemExit(f'intentional bank-{bank:02d} failure')
    source = Path(f'build/assets/model-build/us/{bank:02d}/0003/model.json')
    write_if_changed(Path(f'build/us/models/parts/models/bank{bank:02d}/0003.bin'), source.read_bytes())
    with Path(f'model_build_{bank:02d}.calls').open('a') as log:
        log.write('packed\\n')
""")

    def run_model_banks(self, banks):
        return subprocess.run([MAKE, 'ASSETS=1', '-j4', f'LD={sys.executable} {self.ld}',
                               *[f'build/us/assets/models/bank{bank}/0003.o' for bank in banks]],
                              cwd=self.root, text=True, capture_output=True)

    def test_both_model_banks_build_in_parallel_and_fail_independently(self):
        banks = ('03', '09')
        self.setup_model_banks(banks)
        for bank in banks:
            inputs = self.root / f'build/assets/model-build/us/{bank}/0003'
            inputs.mkdir(parents=True)
            (inputs / 'manifest.json').write_text('{}')
            (inputs / 'model.json').write_text('model' + bank)
        result = self.run_model_banks(banks)
        self.assertEqual(result.returncode, 0, result.stderr)
        objects = [self.root / f'build/us/assets/models/bank{bank}/0003.o' for bank in banks]
        before = [p.stat().st_mtime_ns for p in objects]
        self.assertEqual([p.read_text() for p in objects], ['model03', 'model09'])
        for bank in banks:
            self.assertTrue((self.root / f'build/us/models/bank{bank}/parts.stamp').is_file())
        self.assertEqual(self.run_model_banks(banks).returncode, 0)
        self.assertEqual([p.stat().st_mtime_ns for p in objects], before)
        for bank in banks:
            self.assertEqual((self.root / f'model_build_{bank}.calls').read_text(), 'packed\n')

        # Editing bank 09 invalidates only its packer, even with both goals.
        time.sleep(1.05)
        source09 = self.root / 'build/assets/model-build/us/09/0003/model.json'
        source09.write_text('changed09')
        self.assertEqual(self.run_model_banks(banks).returncode, 0)
        self.assertEqual(objects[1].read_text(), 'changed09')
        self.assertEqual(objects[0].stat().st_mtime_ns, before[0])
        self.assertEqual((self.root / 'model_build_03.calls').read_text(), 'packed\n')
        self.assertEqual((self.root / 'model_build_09.calls').read_text(), 'packed\npacked\n')
        part09 = self.root / 'build/us/models/parts/models/bank09/0003.bin'
        part09.unlink()
        self.assertEqual(self.run_model_banks(banks).returncode, 0)
        self.assertEqual(part09.read_text(), 'changed09')
        self.assertEqual((self.root / 'model_build_03.calls').read_text(), 'packed\n')
        self.assertEqual((self.root / 'model_build_09.calls').read_text(), 'packed\npacked\npacked\n')

        # Missing inputs and failed validation in bank 09 must not block a fresh bank-03 part.
        source09.unlink()
        (self.root / 'fail-model-09').touch()
        (self.root / 'build/us/models/parts/models/bank03/0003.bin').unlink()
        self.assertEqual(self.run_model_banks(('03',)).returncode, 0)
        self.assertEqual(objects[0].read_text(), 'model03')
        failed = self.run_model_banks(banks)
        self.assertNotEqual(failed.returncode, 0)
        self.assertIn('intentional bank-09 failure', failed.stderr)
        self.assertEqual(objects[1].read_text(), 'changed09')

        # The full asset sequence retains the storage-map positions of both banks.
        with (self.root / 'Makefile').open('a') as stream:
            stream.write('\n.PHONY: show-assets\nshow-assets:\n\t@echo $(ASSET_BINS_us)\n')
        assets = subprocess.run([MAKE, 'ASSETS=1', '--no-print-directory', 'show-assets'],
                                cwd=self.root, text=True, capture_output=True)
        self.assertEqual(assets.returncode, 0, assets.stderr)
        names = assets.stdout.split()
        for bank, previous, following in (('03', '02', '04'), ('09', '08', '0a')):
            position = names.index(f'assets/models/bank{bank}/0003.bin')
            self.assertEqual(names[position - 1], f'assets/asset_bank_{previous}.bin')
            self.assertEqual(names[position + 1], f'assets/asset_bank_{following}.bin')

    def test_raw_model_banks_keep_their_asset_slots_and_link_original_storage(self):
        self.setup_model_banks(('03', '09'))
        profile = self.root / 'config/profiles/us.yaml'
        grouped = profile.read_text()
        with (self.root / 'Makefile').open('a') as stream:
            stream.write('\n.PHONY: show-assets\nshow-assets:\n\t@echo $(ASSET_BINS_us)\n')
        for raw_banks in (('03',), ('09',), ('03', '09')):
            with self.subTest(raw_banks=raw_banks):
                contents = grouped
                for bank in raw_banks:
                    contents = contents.replace(
                        f'  - name: asset_bank_{bank}\n    type: group\n',
                        f'  - [0x{bank}00, bin, asset_bank_{bank}]\n')
                    source = self.root / f'assets/asset_bank_{bank}.bin'
                    source.parent.mkdir(parents=True, exist_ok=True)
                    source.write_text('original bank ' + bank)
                profile.write_text(contents)
                assets = subprocess.run([MAKE, 'ASSETS=1', '--no-print-directory', 'show-assets'],
                                        cwd=self.root, text=True, capture_output=True)
                self.assertEqual(assets.returncode, 0, assets.stderr)
                names = assets.stdout.split()
                for bank, previous, following in (('03', '02', '04'), ('09', '08', '0a')):
                    raw = f'assets/asset_bank_{bank}.bin'
                    model = f'assets/models/bank{bank}/0003.bin'
                    expected, excluded = (raw, model) if bank in raw_banks else (model, raw)
                    self.assertEqual(names.count(expected), 1)
                    self.assertNotIn(excluded, names)
                    position = names.index(expected)
                    self.assertEqual(names[position - 1], f'assets/asset_bank_{previous}.bin')
                    self.assertEqual(names[position + 1], f'assets/asset_bank_{following}.bin')
                targets = [f'build/us/assets/asset_bank_{bank}.o' for bank in raw_banks]
                linked = subprocess.run([MAKE, 'ASSETS=1', '-j4', f'LD={sys.executable} {self.ld}', *targets],
                                        cwd=self.root, text=True, capture_output=True)
                self.assertEqual(linked.returncode, 0, linked.stderr)
                for bank, target in zip(raw_banks, targets):
                    self.assertEqual((self.root / target).read_text(), 'original bank ' + bank)
        self.assertFalse((self.root / 'model_build_03.calls').exists())
        self.assertFalse((self.root / 'model_build_09.calls').exists())

    def test_raw_bank04_keeps_its_slot_without_reconstruction(self):
        self.setup_model_banks(('04',))
        profile = self.root / 'config/profiles/us.yaml'
        profile.write_text(profile.read_text().replace(
            '  - name: asset_bank_04\n    type: group\n',
            '  - [0x0400, bin, asset_bank_04]\n'))
        source = self.root / 'assets/asset_bank_04.bin'
        source.parent.mkdir(parents=True, exist_ok=True)
        source.write_bytes(b'original bank 04')
        with (self.root / 'Makefile').open('a') as stream:
            stream.write('\n.PHONY: show-assets\nshow-assets:\n\t@echo $(ASSET_BINS_us)\n')
        result = subprocess.run([MAKE, 'ASSETS=1', '--no-print-directory', 'show-assets'],
                                cwd=self.root, text=True, capture_output=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        names = result.stdout.split()
        position = names.index('assets/asset_bank_04.bin')
        self.assertEqual(names[position - 1:position + 2], [
            'assets/asset_bank_03.bin', 'assets/asset_bank_04.bin', 'assets/asset_bank_05.bin'])
        self.assertNotIn('assets/models/bank04/0003.bin', names)
        target = 'build/us/assets/asset_bank_04.o'
        linked = subprocess.run([MAKE, 'ASSETS=1', f'LD={sys.executable} {self.ld}', target],
                                cwd=self.root, text=True, capture_output=True)
        self.assertEqual(linked.returncode, 0, linked.stderr)
        self.assertEqual((self.root / target).read_bytes(), source.read_bytes())
        self.assertFalse((self.root / 'model_build_04.calls').exists())

    def check_model_parts(self, bank):
        self.setup_model_banks((bank,))
        inputs = self.root / f'build/assets/model-build/us/{bank}/0003'
        inputs.mkdir(parents=True)
        (inputs / 'manifest.json').write_text('{}')
        source = inputs / 'model.json'
        source.write_bytes(b'model')
        target = self.root / f'build/us/assets/models/bank{bank}/0003.o'
        part = self.root / f'build/us/models/parts/models/bank{bank}/0003.bin'
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
        pack_stamp = self.root / f'build/us/models/bank{bank}/parts.stamp'
        calls = self.root / f'model_build_{bank}.calls'
        before = calls.read_text()
        unrelated = self.root / 'scripts/model_unrelated_preview.py'
        unrelated.write_text('# unrelated preview tool')
        future = pack_stamp.stat().st_mtime_ns + 10_000_000_000
        os.utime(unrelated, ns=(future, future))
        self.assertEqual(run().returncode, 0)
        self.assertEqual(calls.read_text(), before)
        for name in ('model_build', 'model_assets', 'model_attachment_format', 'model_bundle_build', 'model_color_build', 'model_aux_build', 'model_effect_format', 'model_emission_points', 'texture_build', 'rzip_pack'):
            dependency = self.root / f'scripts/{name}.py'
            original = dependency.stat()
            newer = pack_stamp.stat().st_mtime_ns + 10_000_000_000
            os.utime(dependency, ns=(newer, newer))
            try:
                self.assertEqual(run().returncode, 0)
            finally:
                os.utime(dependency, ns=(original.st_atime_ns, original.st_mtime_ns))
            self.assertEqual(calls.read_text(), before + 'packed\n')
            before = calls.read_text()
        # Deliberately give the directory an older timestamp. Missing inputs
        # must invalidate packing even on a filesystem with a coarse clock.
        source.unlink()
        os.utime(inputs, ns=(1_000_000_000, 1_000_000_000))
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
        # Shell xtrace writes can interleave under parallel Make. This test
        # checks complete command logging; other tests retain parallel builds.
        for kind in ('font', 'mp3'):
            with self.subTest(kind=kind):
                result, objects = self.run_make(kind, jobs=1)
                self.assertEqual(result.returncode, 0, result.stderr)
                for path in objects:
                    self.assertIn(str(path), result.stderr)
                self.assertIn('fake_ld.py -r -b binary', result.stderr)
                unchanged, _ = self.run_make(kind, jobs=1)
                self.assertEqual(unchanged.returncode, 0, unchanged.stderr)
                self.assertNotIn('fake_ld.py -r -b binary', unchanged.stderr)
        self.ld.write_text('raise SystemExit(7)\n')
        for kind in ('font', 'mp3'):
            with self.subTest(failed_kind=kind):
                prefix = 'font/glyphs' if kind == 'font' else 'audio/mp3/streams'
                path = self.root / f'build/us/assets/{prefix}/0000.o'
                path.unlink()
                result, _ = self.run_make(kind, jobs=1)
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
