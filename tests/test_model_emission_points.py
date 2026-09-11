import copy
import struct
import unittest

from scripts import model_emission_points as points


class EmissionPointTests(unittest.TestCase):
    def test_floats_and_unknown_bytes_reconstruct_exactly(self):
        raw = struct.pack('>B3s3f', 7, b'\x12\x34\x56', -0.0, 12.25, -8192.5)
        result = points.parse_points(raw)
        self.assertEqual(result['points'][0]['matrix_slot'], 7)
        self.assertEqual(result['points'][0]['reserved_bytes'], '123456')
        self.assertEqual(points.encode_points(result), raw)
        changed = copy.deepcopy(result)
        changed['points'][0]['local_xyz'][1] = 4.5
        self.assertEqual(struct.unpack_from('>f', points.encode_points(changed), 8)[0], 4.5)

    def test_record_boundaries_and_nonfinite_positions_rejected(self):
        for raw in (b'', bytes(15), bytes(17),
                    struct.pack('>B3s3f', 0, bytes(3), float('inf'), 0, 0),
                    struct.pack('>B3s3f', 0, bytes(3), float('nan'), 0, 0)):
            with self.subTest(raw=raw):
                with self.assertRaises(ValueError):
                    points.parse_points(raw)

    def test_encoder_checks_count_and_reserved_extent(self):
        result = points.parse_points(bytes(16))
        result['point_count'] = 2
        with self.assertRaisesRegex(ValueError, 'count'):
            points.encode_points(result)
        result['point_count'] = 1
        result['points'][0]['reserved_bytes'] = '00'
        with self.assertRaisesRegex(ValueError, 'reserved'):
            points.encode_points(result)

    def test_unproven_entry_and_changed_consumers_are_not_accepted(self):
        self.assertNotIn(447, points.ENTRIES)
        self.assertEqual(20, len(set(points.ENTRIES)))
        with self.assertRaisesRegex(ValueError, 'consumer changed'):
            points.make_manifest({}, b'', 0x15000000, b'', 0x80082B20, 'unverified')
