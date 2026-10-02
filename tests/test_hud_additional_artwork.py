from __future__ import annotations

import copy
import tempfile
import unittest
from pathlib import Path

from scripts import hud_additional_artwork as extra
from scripts import hud_assets as hud


def sample_assets():
    assets = {}
    for _name, _title, ids, width, height, texture_format in extra.ARTWORK:
        for index in ids:
            size = hud.texture_native.packed_row_size(texture_format, width) * height
            value = 0xF0 if texture_format == "ia8" else index % 256
            assets[index] = hud.FlatHudAsset(index, index * 100, index * 100 + 20,
                bytes([value]) * size)
    return assets


def asymmetric_rgba(index, width=32, height=32):
    return bytes(channel for y in range(height) for x in range(width)
        for channel in ((x * 7 + index) % 256, (y * 11 + index * 3) % 256,
                        (x + y * 3 + index) % 256, (x * 17 + y * 13 + index) % 256))


def set_asymmetric_rgba(assets, index):
    pixels = asymmetric_rgba(index)
    source = assets[index]
    packed = hud.texture_native.convert_row_layout(pixels,
        hud.texture_base.ROW_LAYOUT_TMEM, "rgba32", 32, 32)
    assets[index] = hud.FlatHudAsset(index, source.rom_start, source.rom_end, packed)
    return pixels


def crop_rgba(pixels, stride, x, y, width=16, height=16):
    return b''.join(pixels[((y + row) * stride + x) * 4:
                          ((y + row) * stride + x + width) * 4]
                    for row in range(height))


class AdditionalArtworkTests(unittest.TestCase):
    def test_nintendo_tile_order_and_ia8_transparency(self):
        assets = sample_assets()
        records, files = extra.render_artwork(assets)
        logo = next(r for r in records if r["name"] == "nintendo-wordmark")
        self.assertEqual(logo["resource_ids"], [2141, 2142, 2143])
        self.assertEqual((logo["width"], logo["height"]), (192, 64))
        pixels = hud.texture_base.decode_rgba_png_pixels(files[logo["preview_file"]], 192, 64)
        for column, index in enumerate(logo["resource_ids"]):
            self.assertEqual(pixels[column * 64 * 4:column * 64 * 4 + 4], bytes([index % 256]) * 4)
        label = next(r for r in records if r["name"] == "poops-label")
        pixels = hud.texture_base.decode_rgba_png_pixels(files[label["preview_file"]], 64, 32)
        self.assertEqual(pixels, bytes((255, 255, 255, 0)) * 64 * 32)
        self.assertEqual(files['additional/resources/2200.bin'], bytes([0xF0]) * 2048)

    def test_stale_provenance_or_changed_source_or_png_is_rejected(self):
        assets = sample_assets()
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory)
            records = extra.write_preview(assets, output)
            extra.verify_preview(assets, output, records)
            stale = copy.deepcopy(records)
            stale[0]['sources'][0]['rom_start'] = '0xBAD'
            with self.assertRaisesRegex(ValueError, 'provenance'):
                extra.verify_preview(assets, output, stale)
            for relative in (records[0]['preview_file'], records[0]['sources'][0]['raw_file']):
                original = (output / relative).read_bytes()
                (output / relative).write_bytes(b'corrupted')
                with self.assertRaisesRegex(ValueError, 'stale'):
                    extra.verify_preview(assets, output, records)
                (output / relative).write_bytes(original)
            assets[2204] = hud.FlatHudAsset(2204, 0, 1, b'wrong length')
            with self.assertRaisesRegex(ValueError, 'exactly'):
                extra.render_artwork(assets)

    def test_skull_uses_column_major_two_by_two_composition(self):
        assets = sample_assets()
        sources = {index: set_asymmetric_rgba(assets, index)
                   for index in (1980, 1981, 1982, 1983)}
        records, files = extra.render_artwork(assets)
        skull = next(r for r in records if r['name'] == 'skull-icon')
        self.assertEqual(skull['resource_ids'], [1980, 1981, 1982, 1983])
        self.assertEqual((skull['width'], skull['height']), (64, 64))
        pixels = hud.texture_base.decode_rgba_png_pixels(
            files[skull['preview_file']], 64, 64)
        for index, x, y in ((1980, 0, 0), (1981, 0, 32),
                            (1982, 32, 0), (1983, 32, 32)):
            with self.subTest(resource=index):
                self.assertEqual(crop_rgba(pixels, 64, x, y, 32, 32), sources[index])
                self.assertEqual(files[f'additional/resources/{index:04d}.bin'],
                                 assets[index].data)

    def test_packed_icon_crops_preserve_coordinates_rgba_and_raw_sources(self):
        assets = sample_assets()
        sources = {index: set_asymmetric_rgba(assets, index)
                   for index in (2115, 2183, 2184)}
        records, files = extra.render_artwork(assets)
        groups = {r['name']: r for r in records}
        expected = {
            'small-player-badges': [
                ('small-p1-badge', 2115, 0, 0),
                ('small-p2-badge', 2115, 16, 0),
                ('small-p3-badge', 2115, 0, 16),
                ('small-p4-badge', 2115, 16, 16),
            ],
            'small-statistics-icons': [
                ('small-stopwatch', 2183, 0, 0),
                ('small-money-bag', 2183, 16, 0),
                ('small-rip-gravestone', 2183, 0, 16),
                ('small-green-roll', 2183, 16, 16),
                ('small-skull', 2184, 32, 0),
                ('small-green-crosshair', 2184, 48, 0),
                ('small-gray-projectile', 2184, 32, 16),
                ('small-purple-head-impact', 2184, 48, 16),
            ],
        }
        region_files = set()
        for group, specifications in expected.items():
            regions = groups[group]['regions']
            self.assertEqual(len(regions), len(specifications))
            by_name = {r['name']: r for r in regions}
            self.assertEqual(set(by_name), {item[0] for item in specifications})
            for name, index, x, y in specifications:
                with self.subTest(region=name):
                    region = by_name[name]
                    self.assertEqual(region['source_resource_id'], index)
                    self.assertEqual((region['x'], region['y'], region['width'],
                                      region['height']), (x, y, 16, 16))
                    self.assertTrue(region['display_name'])
                    self.assertEqual(region['preview_file'],
                                     f'additional/regions/{index:04d}-{name}.png')
                    pixels = hud.texture_base.decode_rgba_png_pixels(
                        files[region['preview_file']], 16, 16)
                    self.assertEqual(pixels, crop_rgba(sources[index], 32, x % 32, y))
                    region_files.add(region['preview_file'])
        self.assertEqual(len(region_files), 12)
        for index, pixels in sources.items():
            self.assertEqual(files[f'additional/resources/{index:04d}.bin'],
                             assets[index].data)
            self.assertNotEqual(assets[index].data, pixels)
            self.assertIn(0, pixels[3::4])
            self.assertIn(255, pixels[3::4])

    def test_changed_crop_pixels_and_stale_crop_metadata_are_rejected(self):
        assets = sample_assets()
        set_asymmetric_rgba(assets, 2184)
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory)
            records = extra.write_preview(assets, output)
            extra.verify_preview(assets, output, records)
            group_index = next(i for i, record in enumerate(records)
                               if record['name'] == 'small-statistics-icons')
            region = records[group_index]['regions'][-1]
            crop_file = output / region['preview_file']
            original = crop_file.read_bytes()
            pixels = bytearray(hud.texture_base.decode_rgba_png_pixels(original, 16, 16))
            pixels[3] ^= 1
            crop_file.write_bytes(hud.texture_base.encode_rgba_png(16, 16, bytes(pixels)))
            with self.assertRaisesRegex(ValueError, 'stale'):
                extra.verify_preview(assets, output, records)
            crop_file.write_bytes(original)
            for key, value in (('x', region['x'] + 1), ('source_resource_id', 2183)):
                stale = copy.deepcopy(records)
                stale[group_index]['regions'][-1][key] = value
                with self.subTest(field=key):
                    with self.assertRaisesRegex(ValueError, 'metadata|provenance'):
                        extra.verify_preview(assets, output, stale)
            extra.verify_preview(assets, output, records)

    def test_additional_artwork_preserves_selector_inventory(self):
        assets = sample_assets()
        assets[2196] = hud.FlatHudAsset(2196, 123, 234, bytes(4096))
        family = hud.HudAssetFamily(b'A', b'', (hud.SpriteMetadata(1, 1, 1, 128, 0, 2196),))
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / 'preview'
            manifest = hud.build_preview(family, assets, output, False, include_additional=True)
            self.assertEqual(hud.verify_preview(family, assets, output, include_additional=True), (1, 1))
            self.assertEqual(manifest['selector_count'], 1)
            self.assertEqual(manifest['resource_count'], 1)
            self.assertEqual(manifest['additional_artwork_count'], 40)
            self.assertEqual(manifest['additional_resource_count'], 74)
            self.assertEqual(manifest['additional_region_count'], 12)
            self.assertEqual(manifest['additional_png_count'], 52)
            self.assertEqual(len(manifest['additional_artwork']), 40)
            rendered = (output / 'index.html').read_text()
            self.assertEqual(rendered.count('data-kind="additional"'), 40)
            self.assertIn('Additional artwork · resource 2141, 2142, 2143', rendered)
            self.assertIn('additional/2141-nintendo-wordmark.png', rendered)


if __name__ == '__main__':
    unittest.main()
