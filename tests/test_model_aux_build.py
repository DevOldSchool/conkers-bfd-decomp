from __future__ import annotations

import copy
import struct
import unittest

from scripts import model_aux_build as auxiliary


def effect_payload(*, secondary=True, lists=True, suffix=8):
    vertex = struct.pack('>hhhHhh4B', -3, 4, 5, 0, 32, -64, 10, 20, 30, 255)
    cursor = 32
    header = []
    parts = []
    for data in (vertex, vertex if secondary else b'',
                 struct.pack('>II', 0xDF000000, 0) if lists else b'',
                 struct.pack('>II', 0xDF000000, 0) if lists else b''):
        header.extend([cursor if data else 0, len(data)])
        parts.append(data)
        cursor += len(data)
    header[-1] |= 0x80000000
    return struct.pack('>8I', *header) + b''.join(parts) + bytes(suffix)


class ModelAuxBuildTests(unittest.TestCase):
    def test_reviewed_entry_dispatch_and_wrong_bank_rejection(self):
        from scripts import model_build
        for entry, payload in ((173, effect_payload()), (432, struct.pack('>B3x3f', 7, 0, 1, 2))):
            with self.subTest(entry=entry):
                records = model_build.model_records(payload, bank=9, entry=entry)
                self.assertEqual(model_build.encode_records(records, bank=9), payload)
                with self.assertRaises(ValueError):
                    model_build.encode_records(records, bank=3)
                with self.assertRaises(ValueError):
                    model_build.model_records(payload, bank=9)

    def test_effect_sections_and_explicit_empty_lists_roundtrip(self):
        for secondary, lists, suffix in ((True, True, 8), (True, False, 0), (False, True, 0)):
            data = effect_payload(secondary=secondary, lists=lists, suffix=suffix)
            with self.subTest(secondary=secondary, lists=lists, suffix=suffix):
                records = auxiliary.effect_records(data)
                self.assertEqual(auxiliary.encode_effect_records(records), data)
                self.assertEqual(bool(records['vertex_buffers'][1]), secondary)
                self.assertEqual(bool(records['geometry_commands']), lists)
                edited = copy.deepcopy(records)
                edited['vertex_buffers'][0][0][0] -= 1
                self.assertNotEqual(auxiliary.encode_effect_records(edited), data)

    def test_effect_schema_boundaries_and_command_termination_are_checked(self):
        records = auxiliary.effect_records(effect_payload())
        invalid = [dict(records, opaque='00'), dict(records, zero_suffix_bytes=16),
                   dict(records, vertex_buffers=records['vertex_buffers'][:1])]
        for index, value in ((0, 40), (1, 32), (2, 32), (4, 0), (7, 8)):
            changed = copy.deepcopy(records)
            changed['header_words'][index] = value
            invalid.append(changed)
        changed = copy.deepcopy(records)
        changed['geometry_commands'][0][0] = 0
        invalid.append(changed)
        for changed in invalid:
            with self.subTest(changed=changed), self.assertRaises(ValueError):
                auxiliary.encode_effect_records(changed)
        for bad in (effect_payload() + bytes(8), effect_payload()[:-1] + b'\1'):
            with self.assertRaises(ValueError):
                auxiliary.effect_records(bad)

    def test_points_preserve_native_floats_signed_zero_and_matrix_slots(self):
        data = struct.pack('>B3x3fB3x3f', 7, -0.0, 1.25, -8.5, 255, 8.0, -3.0, 6.5)
        records = auxiliary.point_records(data)
        self.assertEqual(auxiliary.encode_point_records(records), data)
        records['points'][1]['matrix_slot'] = 4
        self.assertNotEqual(auxiliary.encode_point_records(records), data)
        records['points'][0]['local_xyz'][0] = 2.0
        self.assertEqual(auxiliary.point_records(auxiliary.encode_point_records(records)), records)

    def test_points_reject_unknown_padding_nonfinite_or_unrepresentable_fields(self):
        data = struct.pack('>B3x3f', 7, 0.0, 1.0, 2.0)
        records = auxiliary.point_records(data)
        invalid = [dict(records, opaque='00'), dict(records, points=[])]
        for key, value in (('matrix_slot', 256), ('reserved_bytes', [0, 1, 0]),
                           ('local_xyz', [float('nan'), 0, 0]), ('local_xyz', [0, 0]),
                           ('local_xyz', [1e100, 0, 0]), ('opaque', '00')):
            changed = copy.deepcopy(records)
            changed['points'][0][key] = value
            invalid.append(changed)
        for changed in invalid:
            with self.subTest(changed=changed), self.assertRaises(ValueError):
                auxiliary.encode_point_records(changed)
        for bad in (b'', data[:-1], data[:1] + b'\1' + data[2:], struct.pack('>B3x3f', 7, float('inf'), 0, 0)):
            with self.assertRaises(ValueError):
                auxiliary.point_records(bad)
