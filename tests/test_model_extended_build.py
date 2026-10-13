from __future__ import annotations

import copy
import struct
import unittest

from scripts import model_build, model_extended_build as extended, model_assets
from test_model_bundle_build import surface_payload
from test_model_color_build import color_payload


def normal_surface_payload(*, primary=True):
    raw = surface_payload()
    header = list(struct.unpack_from('>10I', raw))
    display = raw[header[0]:header[0] + header[1]]
    header[1] += 8
    header[2:4] = [header[0] + header[1], 64]
    header[4] = header[2] + 64
    surface = raw[-16:-4]
    if not primary:
        header[5] -= 8
        surface = surface[8:]
    normals = b''.join(struct.pack('>bb', i - 16, 16 - i) for i in range(32))
    return (struct.pack('>10I', *header) + raw[40:88]
            + struct.pack('>2I', model_assets.CHARACTER_CUSTOM_MOVEMEM_COMMAND, header[2])
            + display + normals + surface + bytes(4))


class ExtendedModelBuildTests(unittest.TestCase):
    def test_referenced_normal_tables_and_face_words_roundtrip(self):
        for primary in (True, False):
            raw = normal_surface_payload(primary=primary)
            records = extended.extended_records(raw, primary=primary)
            self.assertEqual(extended.encode_extended_records(records), raw)
            self.assertEqual(len(records['normal_xy_s8']), 1)
            self.assertEqual(records['face_words'], [0x10002])
            self.assertEqual(len(records['surface_header']), 2 if primary else 0)
            for slot in (0, 31):
                changed = copy.deepcopy(records)
                changed['normal_xy_s8'][0][slot][0] ^= 1
                rebuilt = extended.encode_extended_records(changed)
                self.assertNotEqual(rebuilt, raw)
                self.assertEqual(extended.extended_records(rebuilt, primary=primary), changed)

    def test_primary_and_child_color_fields_with_zero_suffix(self):
        for primary in (True, False):
            raw = color_payload()
            if not primary:
                header = list(struct.unpack_from('>10I', raw))
                header[5] -= 8
                raw = struct.pack('>10I', *header) + raw[40:header[4]] + raw[header[4] + 8:]
            raw += bytes(8)
            records = extended.extended_records(raw, primary=primary)
            self.assertEqual(extended.encode_extended_records(records), raw)
            self.assertEqual(records['zero_regions'][-1], [len(raw) - 8, 8])
            records['color_descriptors'][0]['colors'][-1][2] ^= 1
            changed = extended.encode_extended_records(records)
            self.assertNotEqual(changed, raw)
            self.assertEqual(extended.extended_records(changed, primary=primary), records)

    def test_bundle_fallback_and_primary_role_remain_exact(self):
        parts = [normal_surface_payload(), normal_surface_payload(primary=False), b'', b'']
        offset = 32
        descriptors = []
        for i, data in enumerate(parts):
            descriptors.extend([offset, len(data) | (0x80000000 if i == 3 else 0)])
            offset += len(data)
        raw = struct.pack('>8I', *descriptors) + b''.join(parts)
        records = model_build.model_records(raw, bank=4)
        self.assertEqual([p['format'] for p in records['segments'][:2]], ['extended-model'] * 2)
        self.assertEqual(model_build.encode_records(records, bank=4), raw)
        records['segments'][0]['primary'] = False
        with self.assertRaisesRegex(ValueError, 'role'):
            model_build.encode_records(records, bank=4)

    def test_unreferenced_secondary_bytes_and_nonzero_gaps_fail(self):
        raw = normal_surface_payload()
        changed = bytearray(raw)
        struct.pack_into('>2I', changed, 88, 0xE7000000, 0)
        with self.assertRaisesRegex(ValueError, 'secondary'):
            extended.extended_records(bytes(changed), primary=True)
        changed = bytearray(raw)
        changed[-1] = 1
        with self.assertRaisesRegex(ValueError, 'unsupported storage'):
            extended.extended_records(bytes(changed), primary=True)
        changed = bytearray(raw)
        struct.pack_into('>I', changed, 92, 121)
        with self.assertRaisesRegex(ValueError, 'contiguous'):
            extended.extended_records(bytes(changed), primary=True)

    def test_bad_counts_offsets_and_unowned_fields_are_rejected(self):
        records = extended.extended_records(normal_surface_payload(), primary=True)
        for field, value in [('normal_xy_s8', [[[0, 0]]]), ('surface_header', []),
                             ('face_words', []), ('zero_regions', [[196, 13]]),
                             ('opaque', []), ('color_descriptors', [{'bad': 1}])]:
            with self.subTest(field=field), self.assertRaises(ValueError):
                extended.encode_extended_records(dict(records, **{field: value}))
        changed = copy.deepcopy(records)
        changed['vertices'][0].pop()
        with self.assertRaises(ValueError):
            extended.encode_extended_records(changed)
        with self.assertRaisesRegex(ValueError, 'consumer changed'):
            extended.verify_normal_consumers(b'', 0x15000000)
