from __future__ import annotations

import copy
import struct
import unittest

from scripts import model_color_build as color


def color_payload():
    vertices = b''.join(struct.pack('>hhhHhh4B', *v) for v in (
        (0, 0, 0, 0, 0, 0, 255, 255, 255, 255),
        (10, 0, 0, 0, 0, 0, 255, 255, 255, 255),
        (0, 10, 0, 0, 0, 0, 255, 255, 255, 255)))
    display = struct.pack('>6I', 0x01003006, 0x01000000, 0x05000204, 0, 0xDF000000, 0)
    return (struct.pack('>10I', 88, 24, 0, 0, 148, 12, 0, 0, 124, 0x80000018)
            + vertices + display + bytes([10, 20, 30, 40, 50, 60]) + bytes(2)
            + struct.pack('>2H', 0, 2) + struct.pack('>6I', 112, 120, 2, 0, 0, 0)
            + struct.pack('>3I', 0, 5, 0x1234))


class ModelColorBuildTests(unittest.TestCase):
    def test_native_color_descriptor_arrays_surface_and_padding_roundtrip(self):
        raw = color_payload()
        records = color.color_records(raw)
        self.assertEqual(records['color_descriptors'][0]['colors'], [[10, 20, 30], [40, 50, 60]])
        self.assertEqual(records['color_descriptors'][0]['vertex_indices'], [0, 2])
        self.assertEqual(records['zero_regions'], [[118, 2]])
        self.assertEqual(color.encode_color_records(records), raw)
        records['color_descriptors'][0]['colors'][0][1] = 99
        records['color_descriptors'][0]['vertex_indices'][0] = 1
        self.assertNotEqual(color.encode_color_records(records), raw)
        self.assertEqual(color.color_records(color.encode_color_records(records)), records)

    def test_descriptor_counts_indices_sentinel_and_unknown_fields_are_rejected(self):
        records = color.color_records(color_payload())
        invalid = [dict(records, opaque='00'), dict(records, sentinel_words=[0, 1, 0]),
                   dict(records, zero_regions=[]), dict(records, zero_regions=[[118, 3]])]
        for key, value in (('vertex_count', 3), ('vertex_indices', [0, 3]),
                           ('color_offset', 113), ('vertex_index_offset', 112),
                           ('colors', [[10, 20, 300], [40, 50, 60]])):
            changed = copy.deepcopy(records)
            changed['color_descriptors'][0][key] = value
            invalid.append(changed)
        for changed in invalid:
            with self.subTest(changed=changed), self.assertRaises(ValueError):
                color.encode_color_records(changed)
        poisoned = bytearray(color_payload())
        poisoned[118] = 1
        with self.assertRaisesRegex(ValueError, 'opaque'):
            color.color_records(bytes(poisoned))

    def test_bank04_bundle_dispatch_preserves_native_empty_slots(self):
        from scripts import model_build
        primary = color_payload()
        end = 32 + len(primary)
        raw = struct.pack('>8I', 32, len(primary), end, 0, end, 0, end, 0x80000000) + primary
        records = model_build.model_records(raw, bank=4)
        self.assertEqual(records['segments'][0]['format'], 'primary-color-surface-direct')
        self.assertEqual(records['segments'][1:], [None, None, None])
        self.assertEqual(model_build.encode_records(records, bank=4), raw)

    def test_consumer_pin_requires_complete_registered_spans(self):
        with self.assertRaisesRegex(ValueError, 'consumer changed'):
            color.verify_consumers(bytes(204), 0x15003120)
