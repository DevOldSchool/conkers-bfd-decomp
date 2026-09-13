import struct
import unittest
from scripts import model_attachment_events as events


class AttachmentEventTests(unittest.TestCase):
    def payload(self, records):
        return bytes(32) + b''.join(struct.pack('>fII', *row) for row in records)

    def test_relocated_events_stop_before_other_arrays(self):
        payload = self.payload([(1, 105, 74), (2, 106, 74), (999, 0, 0), (1, 105, 99)])
        rows = events.parse_events(payload, 16)
        self.assertEqual([32, 44], [row['event_offset'] for row in rows])
        self.assertEqual(['create', 'remove'], [row['operation'] for row in rows])
        self.assertEqual([74, 74], [row['action'] for row in rows])
        self.assertEqual([], events.parse_events(payload, 0))

    def test_bad_pointer_time_and_missing_sentinel_rejected(self):
        payload = self.payload([(1, 105, 74), (999, 0, 0)])
        for pointer in (-32, 17, 1000, 0x01000010):
            with self.subTest(pointer=pointer), self.assertRaises(ValueError):
                events.parse_events(payload, pointer)
        for time in (float('nan'), float('inf'), -1):
            with self.subTest(time=time), self.assertRaises(ValueError):
                events.parse_events(self.payload([(time, 105, 74)]), 16)
        with self.assertRaises(ValueError):
            events.parse_events(self.payload([(1, 105, 74)]), 16)
        with self.assertRaisesRegex(ValueError, 'wrap'):
            events.parse_events(self.payload([(1, 105, 74)] * 256), 16)

    def test_parent_action_is_not_misidentified_as_an_attachment(self):
        base = 0x80086CC4
        data = bytearray(48)
        struct.pack_into('>IB3x', data, 0, base + 16, 2)
        data[16:32] = bytes.fromhex('2f170001000000000000000000000000')
        data[32:48] = bytes.fromhex('ff170000000000000000000000000000')
        records = events.action_records(data, base, 1)['records']
        self.assertEqual(47, records[0]['entry'])
        self.assertNotIn('entry', records[1])
        for action in (0, -1, 999999):
            with self.subTest(action=action), self.assertRaises(ValueError):
                events.action_records(data, base, action)
        data[19] = 3
        with self.assertRaises(ValueError):
            events.action_records(data, base, 1)

    def test_changed_or_missing_consumer_evidence_rejected(self):
        with self.assertRaises(ValueError):
            events.verify_consumers(b'', 0, b'', 0)


if __name__ == '__main__':
    unittest.main()
