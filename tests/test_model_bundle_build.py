from __future__ import annotations

import copy
import struct
import unittest

from scripts import model_assets, model_build, model_bundle_build as bundle


def surface_payload(suffix=4):
    vertices = b''.join(struct.pack('>hhhHhh4B', *v) for v in (
        (0, 0, 0, 0, 0, 0, 255, 255, 255, 255),
        (10, 0, 0, 0, 0, 0, 255, 255, 255, 255),
        (0, 10, 0, 0, 0, 0, 255, 255, 255, 255)))
    faces = 2 if suffix in (0, 8) else 1
    commands = [(0x01003006, 0x01000000)] + [(0x05000204, 0)] * faces + [(0xDF000000, 0)]
    display = b''.join(struct.pack('>II', *c) for c in commands)
    header = [88, len(display), 0, 0, 88 + len(display), 8 + 4 * faces, 0, 0, 0, 0x80000000]
    return (struct.pack('>10I', *header) + vertices + display
            + struct.pack('>II', 0x11223344, 5) + struct.pack('>I', 0x00010002) * faces
            + bytes(suffix))


def bundle_payload(suffix=4):
    primary = surface_payload(suffix)
    geometry = model_assets.parse_model_geometry(primary)
    direct = (struct.pack('>10I', geometry.display_list_offset, geometry.display_list_size,
                          0, 0, 0, 0, 0, 0, 0, 0x80000000)
              + primary[40:geometry.display_list_offset + geometry.display_list_size])
    end_primary = 32 + len(primary)
    end = end_primary + len(direct)
    return struct.pack('>8I', 32, len(primary), end_primary, len(direct), end, 0, end, 0x80000000) + primary + direct


class ModelBundleBuildTests(unittest.TestCase):
    def decode(self, payload):
        return bundle.bundle_records(payload, lambda raw: model_build.model_records(raw, bank=3))

    def encode(self, records):
        return bundle.encode_bundle_records(records,
            lambda rows: model_build.encode_records(rows, bank=3),
            lambda raw: model_build.model_records(raw, bank=3))

    def test_full_bundle_fields_empty_slots_and_observed_zero_suffixes(self):
        for suffix in (0, 4, 8, 12):
            raw = bundle_payload(suffix)
            with self.subTest(suffix=suffix):
                records = self.decode(raw)
                self.assertEqual(records['segments'][2:], [None, None])
                self.assertEqual(records['segments'][0]['zero_suffix_bytes'], suffix)
                self.assertEqual(records['segments'][0]['surface_words'][0], 0x00010002)
                self.assertEqual(self.encode(records), raw)

    def test_scoped_bank04_build_requires_its_consumers_and_preserves_other_inputs(self):
        import hashlib
        import json
        import tempfile
        from pathlib import Path
        from types import SimpleNamespace
        from unittest.mock import patch
        m = model_build
        raw = bundle_payload()
        packed = m.encode_model_payload(raw, m.LEVEL6_ENCODER)
        rom = b'prefix' + packed + b'tail'
        digest = hashlib.sha1(rom).hexdigest()
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            rom_path = root / 'rom.bin'
            rom_path.write_bytes(rom)
            contract = root / m.CONTRACT
            contract.parent.mkdir(parents=True)
            contract.write_text(json.dumps({'schema_version': 2, 'profile': 'us',
                'rom_sha1': digest, 'encoder': m.texture_build.ENCODERS['zlib'],
                'banks': {'03': [3], '04': [3], '09': [3]},
                'level6_entries': {'03': [], '04': [3], '09': []}}))
            layout = {'normalized_sha1': [digest], 'asset_table': 0,
                'game_format': 'rzip', 'game_start': 0, 'game_end': 6, 'game_vram': 0x15000000}
            bank = m.rzip_archive.AssetBank(4, 6, 6 + len(packed), 0)
            entry = m.rzip_archive.AssetEntry(3, 6, bank.end, 0x10, True)
            with patch.object(m.model_assets, 'resolve_rom', return_value=(rom_path, layout)), \
                    patch.object(m.rzip_archive, 'normalize_rom', return_value=(rom, 'z64')), \
                    patch.object(m.rzip_archive, 'parse_asset_banks', return_value=[bank]), \
                    patch.object(m.rzip_archive, 'parse_asset_entries', return_value=[entry]), \
                    patch.object(m.rzip_archive, 'parse_game_archive', return_value=SimpleNamespace(code=b'code')), \
                    patch.object(m, 'layout_bins', return_value=(m.partition(bank, [entry]), bank.end)), \
                    patch.object(m.model_bundle_build, 'verify_consumers') as consumers, \
                    patch.object(m.model_assets, 'verify_direct_model_consumers') as other:
                proof = m.build_parts(root, bank=4)
                self.assertEqual(proof['model_count'], 1)
                consumers.assert_called_once_with(b'code', 0x15000000)
                other.assert_not_called()
                target = root / 'build/us/models/parts/models/bank04/0003.bin'
                self.assertEqual(target.read_bytes(), packed)
                self.assertFalse((root / m.input_directory(3, 3)).exists())
                self.assertFalse((root / m.input_directory(3, 9)).exists())
                consumers.side_effect = ValueError('bundle consumer changed')
                with self.assertRaisesRegex(ValueError, 'consumer changed'):
                    m.build_parts(root, bank=4)
                self.assertEqual(target.read_bytes(), packed)

    def test_surface_words_are_editable_native_integers(self):
        records = self.decode(bundle_payload())
        records['segments'][0]['surface_words'][0] ^= 1
        rebuilt = self.encode(records)
        self.assertNotEqual(rebuilt, bundle_payload())
        self.assertEqual(self.decode(rebuilt), records)
        records['segments'][1]['vertices'][0][0] = -42
        self.assertEqual(self.decode(self.encode(records)), records)

    def test_unknown_regions_bad_counts_headers_and_suffixes_fail(self):
        records = self.decode(bundle_payload())['segments'][0]
        invalid = []
        for field, value in (('surface_words', []), ('surface_header', [0, 6]),
                             ('zero_suffix_bytes', True), ('zero_suffix_bytes', 16)):
            invalid.append(dict(records, **{field: value}))
        invalid.append(dict(records, opaque_tail='0000'))
        for offset, value in ((2, 120), (3, 8), (4, 120), (5, 16), (8, 120)):
            changed = copy.deepcopy(records)
            changed['header_words'][offset] = value
            invalid.append(changed)
        for value in invalid:
            with self.subTest(value=value), self.assertRaises(ValueError):
                bundle.encode_surface_records(value)
        poisoned = bytearray(surface_payload())
        poisoned[-1] = 1
        with self.assertRaisesRegex(ValueError, 'suffix'):
            bundle.surface_records(bytes(poisoned))

    def test_bundle_descriptors_cannot_hide_gaps_overlap_or_opaque_parts(self):
        records = self.decode(bundle_payload())
        invalid = []
        for index, field, value in ((0, 0, 40), (0, 1, 120), (1, 0, 32),
                                    (1, 1, 0x80000070), (3, 1, 0)):
            changed = copy.deepcopy(records)
            changed['descriptors'][index][field] = value
            invalid.append(changed)
        for value in (None, {'opaque': '00'}):
            changed = copy.deepcopy(records)
            changed['segments'][0] = value
            invalid.append(changed)
        changed = copy.deepcopy(records)
        changed['segments'].pop()
        invalid.append(changed)
        for value in invalid:
            with self.subTest(value=value), self.assertRaises(ValueError):
                self.encode(value)

    def test_missing_consumer_bytes_are_rejected(self):
        with self.assertRaisesRegex(ValueError, 'consumer changed'):
            bundle.verify_consumers(b'', 0x15000000)
