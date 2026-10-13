import json
import subprocess
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import debugger_assets as assets


class DebuggerAssetTests(unittest.TestCase):
    def setUp(self):
        self.layout = assets.debugger_layout.ui(ROOT)
        mocked = patch.object(assets.debugger_layout, 'ui', return_value=self.layout)
        mocked.start()
        self.addCleanup(mocked.stop)

    def test_atlas_bit_order_and_tile_boundaries(self):
        data = bytearray(768)
        data[0] = 0x80
        data[8] = 0x01
        data[16 * 8] = 0x40
        data[-1] = 0x01
        pixels = assets.decode_atlas(bytes(data))
        self.assertEqual([i for i, p in enumerate(pixels) if p], [0, 15, 8 * 128 + 1, 48 * 128 - 1])
        self.assertEqual(assets.encode_atlas(pixels), data)

    def test_bad_dimensions_and_nonbinary_pixels_rejected(self):
        for data in (bytes(1), bytes(128 * 48 - 1), b'\1' + bytes(128 * 48 - 1)):
            with self.assertRaises(ValueError):
                assets.encode_atlas(data)
        with self.assertRaises(ValueError):
            assets.decode_atlas(bytes(767))

    def test_repack_is_rom_independent_and_retains_string_addresses(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            directory = root / assets.DIRECTORY
            directory.mkdir(parents=True)
            (directory / 'glyphs.pgm').write_bytes(b'P5\n128 48\n255\n' + bytes(128 * 48))
            # Synthetic editable storage with the same total bounded extent.
            entries = [{'address': self.layout['strings_start'], 'text': 'x' * (self.layout['end'] - self.layout['strings_start'] - 1)}]
            path = directory / 'strings.json'
            path.write_text(json.dumps(entries))
            with patch.object(assets.main_private_data, 'validated_rom', side_effect=AssertionError('ROM read during pack')):
                data, strings = assets.pack(root)
                self.assertEqual(len(data), self.layout['end'] - self.layout['start'])
                self.assertEqual(data[:768], bytes(768))
                self.assertEqual(strings[0][1][-1:], b'\0')
                generated = assets.prepare(root)
                self.assertIn('const u8 D_16003CE0[768]', generated.read_text())
                entries[0]['address'] += 4
                path.write_text(json.dumps(entries))
                with self.assertRaisesRegex(ValueError, 'reviewed addresses'):
                    assets.pack(root)

    def test_actual_editable_inputs_rebuild_checked_rom(self):
        if not (ROOT / assets.DIRECTORY / 'strings.json').is_file():
            self.skipTest('local editable debugger assets unavailable')
        rom = assets.main_private_data.validated_rom(ROOT)
        packed, _ = assets.pack(ROOT)
        self.assertEqual(packed, rom[self.layout['start'] - self.layout['origin']:self.layout['end'] - self.layout['origin']])

    def test_edits_survive_actual_make_clean_and_repack_without_rom(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            directory = root / assets.DIRECTORY
            directory.mkdir(parents=True)
            pixels = bytearray(128 * 48)
            pixels[0] = 255
            (directory / 'glyphs.pgm').write_bytes(b'P5\n128 48\n255\n' + pixels)
            entries = [{'address': self.layout['strings_start'],
                        'text': 'x' * (self.layout['end'] - self.layout['strings_start'] - 1)}]
            (directory / 'strings.json').write_text(json.dumps(entries))
            with patch.object(assets.main_private_data, 'validated_rom', side_effect=AssertionError('ROM accessed')):
                before = assets.prepare(root).read_bytes()
                subprocess.run(['make', '-f', str(ROOT / 'Makefile'), 'clean'], cwd=root,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
                self.assertFalse((root / 'build').exists())
                self.assertEqual(assets.prepare(root).read_bytes(), before)
                self.assertEqual(assets.pack(root)[0][0], 0x80)

    def test_legacy_inputs_migrate_without_overwrite_or_rom_access(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            old = root / assets.LEGACY_DIRECTORY
            old.mkdir(parents=True)
            for name in assets.INPUTS:
                (old / name).write_bytes(b'user edit ' + name.encode())
            with patch.object(assets, 'extract', side_effect=AssertionError('re-extracted')):
                assets.ensure_inputs(root)
                for name in assets.INPUTS:
                    self.assertEqual((root / assets.DIRECTORY / name).read_bytes(), (old / name).read_bytes())
                current = root / assets.DIRECTORY / assets.INPUTS[0]
                current.write_bytes(b'new edit')
                assets.ensure_inputs(root)
                self.assertEqual(current.read_bytes(), b'new edit')

    def test_partial_inputs_never_trigger_silent_reextraction(self):
        for location in (assets.DIRECTORY, assets.LEGACY_DIRECTORY):
            with self.subTest(location=location), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                directory = root / location
                directory.mkdir(parents=True)
                path = directory / 'strings.json'
                path.write_bytes(b'edited')
                with patch.object(assets, 'extract', side_effect=AssertionError('re-extracted')):
                    with self.assertRaisesRegex(ValueError, 'partial'):
                        assets.ensure_inputs(root)
                self.assertEqual(path.read_bytes(), b'edited')

    def test_first_clean_migrates_legacy_edits_before_deleting_build(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            legacy = root / assets.LEGACY_DIRECTORY
            legacy.mkdir(parents=True)
            for name in assets.INPUTS:
                (legacy / name).write_bytes(b'user edits ' + name.encode())
            subprocess.run(['make', '-f', str(ROOT / 'Makefile'), 'clean'], cwd=root,
                           stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
            self.assertFalse((root / 'build').exists())
            for name in assets.INPUTS:
                self.assertEqual((root / assets.DIRECTORY / name).read_bytes(), b'user edits ' + name.encode())

    def test_clean_stops_before_deleting_partial_legacy_inputs(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            legacy = root / assets.LEGACY_DIRECTORY
            legacy.mkdir(parents=True)
            (legacy / 'strings.json').write_bytes(b'user edits')
            result = subprocess.run(['make', '-f', str(ROOT / 'Makefile'), 'clean'], cwd=root,
                                    stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            self.assertNotEqual(result.returncode, 0)
            self.assertEqual((legacy / 'strings.json').read_bytes(), b'user edits')

class PreparationCacheTests(unittest.TestCase):
    def test_cache_detects_content_edits_output_loss_and_metadata_changes(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            inputs = root / assets.DIRECTORY
            inputs.mkdir(parents=True)
            for name in assets.INPUTS:
                (inputs / name).write_bytes(b'original')
            output = root / assets.GENERATED
            def generate(root, *, output):
                output.parent.mkdir(parents=True, exist_ok=True)
                output.write_bytes((inputs / 'strings.json').read_bytes())
                return output
            with patch.object(assets, '_generate', side_effect=generate) as rebuild:
                assets.prepare(root)
                assets.prepare(root)
                self.assertEqual(rebuild.call_count, 1)
                # Same size and unchanged mtime must not conceal an edit.
                import os
                source = inputs / 'strings.json'
                st = source.stat()
                source.write_bytes(b'modified')
                os.utime(source, ns=(st.st_atime_ns, st.st_mtime_ns))
                assets.prepare(root)
                self.assertEqual(rebuild.call_count, 2)
                output.unlink()
                assets.prepare(root)
                self.assertEqual(rebuild.call_count, 3)
                config = root / 'config/profiles/us.yaml'
                config.parent.mkdir(parents=True)
                config.write_text('changed metadata')
                assets.prepare(root)
                self.assertEqual(rebuild.call_count, 4)
                (inputs / 'glyphs.pgm').unlink()
                with self.assertRaisesRegex(ValueError, 'partial'):
                    assets.prepare(root)
