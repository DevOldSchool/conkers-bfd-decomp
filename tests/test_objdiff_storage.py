from __future__ import annotations

import hashlib
from pathlib import Path
import shutil
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch
import zlib

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import objdiff_storage as storage
from elf_sections import sections


def fixture():
    flat = struct.pack('>I', 8) + zlib.compress(b'flatdata', wbits=-15)
    rom = bytearray(b'0123456789abcdef' + flat + b'\0\0')
    table = len(rom)
    rom += bytes(30 * 8)
    for index in range(30):
        start = len(rom)
        raw = index == 29
        rom += b'RAW!' if raw else struct.pack('>II', 8, 4) + b'DATA'
        struct.pack_into('>II', rom, table + index * 8, start - table,
                         (0x80000000 if raw else 0) | (len(rom) - start))
    return bytes(rom), {'font_start': 4, 'font_storage_end': 8,
                        'flat_assets_start': 16, 'flat_assets_end': 16 + len(flat),
                        'asset_table': table,
                        'asset_bank_categories': {f'{i:02X}': ('assets-models' if i in (1,3,4,9)
                            else 'assets-animations' if i == 2 else 'assets-audio' if i in (22,23)
                            else 'assets-other') for i in range(30)},
                        'normalized_sha1': [hashlib.sha1(rom).hexdigest()]}


def rebuilt(start, end):
    return {'rom_start': start, 'rom_end': end, 'size': end - start}


class StorageTests(unittest.TestCase):
    def test_all_bank_storage_indices_gaps_and_raw_block_are_counted_once(self):
        rom, layout = fixture()
        regions = storage.regions(rom, layout)
        self.assertEqual(sum(r['rom_end'] - r['rom_start'] for r in regions), 4 + len(rom) - 16)
        self.assertEqual(len(regions), 34)
        self.assertEqual(regions[-1]['key'], 'bank1D')
        self.assertEqual(regions[-1]['rom_end'] - regions[-1]['rom_start'], 4)
        categories = {}
        for r in regions:
            categories[r['category']] = categories.get(r['category'], 0) + r['rom_end'] - r['rom_start']
        self.assertEqual(categories['assets-models'], 4 * 12)
        self.assertEqual(categories['assets-audio'], 2 * 12)
        self.assertEqual(categories['assets-animations'], 12)
        self.assertEqual(regions[2]['rom_end'] - regions[2]['rom_start'], 2)
        self.assertEqual(regions[3]['rom_end'] - regions[3]['rom_start'], 240)

    def test_layout_categories_are_applied_and_must_cover_every_bank(self):
        rom, layout = fixture()
        categories = layout['asset_bank_categories']
        categories['03'] = 'assets-audio'
        region = next(r for r in storage.regions(rom, layout) if r['key'] == 'bank03')
        self.assertEqual(region['category'], 'assets-audio')
        for invalid in (None, {}, {**categories, '03': 'typo'},
                        {**categories, '1E': 'assets-other'},
                        {k: v for k, v in categories.items() if k != '03'}):
            with self.subTest(categories=invalid), self.assertRaisesRegex(ValueError, 'classify every ROM bank'):
                storage.regions(rom, {**layout, 'asset_bank_categories': invalid})

    def test_changed_rom_or_unconsumed_flat_tail_is_rejected(self):
        rom, layout = fixture()
        with self.assertRaisesRegex(ValueError, 'checksum'):
            storage.regions(rom[:-1] + b'?', layout)
        with self.assertRaises(ValueError):
            storage.regions(rom, {**layout, 'flat_assets_end': layout['flat_assets_end'] + 1})
        with self.assertRaisesRegex(ValueError, 'overlapping'):
            storage.regions(rom, {**layout, 'font_storage_end': 17})

    def test_partial_full_and_empty_regions_keep_exact_complement(self):
        regions = [{'key': 'a', 'rom_start': 0, 'rom_end': 20},
                   {'key': 'b', 'rom_start': 30, 'rom_end': 40},
                   {'key': 'c', 'rom_start': 40, 'rom_end': 48}]
        selected = [rebuilt(4, 8), rebuilt(8, 10), rebuilt(16, 20), rebuilt(30, 40)]
        plan = storage.partition(regions, list(reversed(selected)))
        self.assertEqual([r['unreconstructed_ranges'] for r in plan],
                         [[[0, 4], [10, 16]], [], [[40, 48]]])
        self.assertEqual(sum(r['rebuilt_bytes'] for r in plan), 20)
        self.assertEqual(sum(r['unreconstructed_bytes'] for r in plan), 18)

    def test_overlap_cross_region_outside_and_incorrect_extent_are_rejected(self):
        regions = [{'key': 'a', 'rom_start': 0, 'rom_end': 20},
                   {'key': 'b', 'rom_start': 20, 'rom_end': 30}]
        for selected in ([rebuilt(4, 12), rebuilt(8, 16)], [rebuilt(4, 12)] * 2,
                         [rebuilt(16, 24)], [rebuilt(32, 36)], [rebuilt(-1, 2)],
                         [rebuilt(4, 4)], [{**rebuilt(4, 8), 'size': 8}]):
            with self.subTest(selected=selected), self.assertRaises(ValueError):
                storage.partition(regions, selected)
        for bad in ([regions[0], regions[0]],
                    [regions[0], {**regions[1], 'rom_start': 19}],
                    [{**regions[0], 'rom_end': 0}]):
            with self.subTest(regions=bad), self.assertRaises(ValueError):
                storage.partition(bad, [])

    @unittest.skipUnless(shutil.which('mips-linux-gnu-ld'), 'requires MIPS binutils')
    def test_independent_targets_retain_every_uncredited_byte_without_candidates(self):
        rom, layout = fixture()
        flat_end = layout['flat_assets_end']
        selected = [rebuilt(4, 8), rebuilt(18, flat_end - 2)]
        configs = [{'metadata': {'complete': True}} for _ in selected]
        with tempfile.TemporaryDirectory() as tmp:
            output = Path(tmp)
            units, items, proof = storage.prepare(rom, layout, selected, configs, output=output)
            self.assertEqual(proof['stored_asset_bytes'], len(rom) - 16 + 4)
            self.assertEqual(proof['rebuilt_asset_bytes'], sum(u['size'] for u in selected))
            self.assertEqual(sum(u['report_data_bytes'] for u in units), proof['unreconstructed_asset_bytes'])
            for config in configs:
                self.assertEqual(config['metadata']['progress_categories'], ['data'])
            self.assertTrue(configs[1]['metadata']['complete'])
            observed = []
            for unit, item in zip(units, items, strict=True):
                self.assertNotIn('base_path', unit)
                self.assertNotIn('base_path', item)
                self.assertFalse(item['metadata']['complete'])
                self.assertEqual(item['metadata']['progress_categories'], ['data'])
                self.assertEqual(unit['report_code_bytes'], 0)
                expected = b''.join(rom[a:b] for a, b in unit['rom_ranges'])
                self.assertEqual(sections((output / unit['target_path']).read_bytes(), 1)['.data'][1], expected)
                observed.extend(i for a, b in unit['rom_ranges'] for i in range(a, b))
            observed.extend(i for u in selected for i in range(u['rom_start'], u['rom_end']))
            self.assertEqual(sorted(observed), list(range(4, 8)) + list(range(16, len(rom))))
            # A wrapper that changes even one target byte cannot pass the proof.
            region = storage.partition(storage.regions(rom, layout), selected)[1]
            with patch.object(storage, 'sections', return_value={'.data': ((0, 1, 2, 0, 0, 1), b'?')}), \
                    self.assertRaisesRegex(ValueError, 'differs from original'):
                storage.prepare_remainder(rom, region, output)
