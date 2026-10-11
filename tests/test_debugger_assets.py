import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import debugger_assets as assets


class DebuggerAssetTests(unittest.TestCase):
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
            entries = [{'address': assets.STRINGS, 'text': 'x' * (assets.END - assets.STRINGS - 1)}]
            path = directory / 'strings.json'
            path.write_text(json.dumps(entries))
            with patch.object(assets.main_private_data, 'validated_rom', side_effect=AssertionError('ROM read during pack')):
                data, strings = assets.pack(root)
                self.assertEqual(len(data), assets.END - assets.START)
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
        self.assertEqual(packed, rom[assets.START - assets.ORIGIN:assets.END - assets.ORIGIN])
