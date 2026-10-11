import copy
import struct
import unittest

from scripts import sequence_codec as codec
from scripts import audio_assets


def sequence(stream, track=0):
    offsets = [0] * 16
    offsets[track] = 68
    return struct.pack('>17I', *offsets, 480) + stream


class SequenceCodecTests(unittest.TestCase):
    def test_notes_durations_running_status_and_back_references_rebuild(self):
        raw = sequence(bytes.fromhex('00903c640afe00050500ff2f'))
        records = codec.parse_records(raw)
        track = records['tracks'][0]
        self.assertEqual(track['back_references'], [[5, 5, 5]])
        self.assertEqual([event.get('duration') for event in track['events']], [10, 10, None])
        self.assertEqual(codec.encode_records(records), raw)
        changed = copy.deepcopy(records)
        for event in changed['tracks'][0]['events'][:2]:
            event['data'][0] = 65
        encoded = codec.encode_records(changed)
        self.assertNotEqual(encoded, raw)
        self.assertEqual(audio_assets.compact_sequence_to_midi(encoded).notes, 2)
        changed['tracks'][0]['events'][1]['data'][0] = 66
        with self.assertRaisesRegex(ValueError, 'disagree'):
            codec.encode_records(changed)
        raw = sequence(bytes.fromhex('00913c640a05405a0500ff2f'), track=3)
        records = codec.parse_records(raw)
        self.assertIsNone(records['tracks'][3]['events'][1]['status'])
        self.assertEqual(records['tracks'][3]['events'][0]['status'], 0x91)
        self.assertEqual(codec.encode_records(records), raw)

    def test_escaped_bytes_tempo_markers_and_physical_loop_fields(self):
        # A varint containing FE and a tempo containing FE use escaped reads;
        # loop-end count bytes are physical and are never escaped.
        raw = sequence(bytes.fromhex('fefe00ff51fefe123400ff2e123400ff2dfefe0000000c00ff2f'))
        records = codec.parse_records(raw)
        events = records['tracks'][0]['events']
        self.assertEqual(events[0]['delta'], 16128)
        self.assertEqual(events[0]['tempo_us'], 0xFE1234)
        self.assertEqual(events[1]['marker_value'], 0x1234)
        self.assertEqual(events[2]['current_count'], 0xFE)
        self.assertEqual(codec.encode_records(records), raw)

    def test_nonminimal_variable_width_is_explicit(self):
        raw = sequence(bytes.fromhex('8000c00100ff2f'))
        records = codec.parse_records(raw)
        self.assertEqual(records['tracks'][0]['events'][0]['delta_width'], 2)
        self.assertEqual(codec.encode_records(records), raw)
        records['tracks'][0]['events'][0]['delta_width'] = 1
        self.assertEqual(codec.encode_records(records), sequence(bytes.fromhex('00c00100ff2f')))

    def test_opaque_fields_gaps_invalid_running_status_and_unconsumed_bytes_fail(self):
        records = codec.parse_records(sequence(bytes.fromhex('00c00100ff2f')))
        invalid = [dict(records, original_bytes='00')]
        changed = copy.deepcopy(records)
        changed['track_offsets'][0] += 1
        invalid.append(changed)
        changed = copy.deepcopy(records)
        changed['tracks'][0]['events'][0]['status'] = None
        invalid.append(changed)
        changed = copy.deepcopy(records)
        changed['tracks'][0]['events'].pop()
        invalid.append(changed)
        changed = copy.deepcopy(records)
        changed['tracks'][0]['events'][0]['data'] = [200]
        invalid.append(changed)
        for changed in invalid:
            with self.subTest(changed=changed), self.assertRaises(ValueError):
                codec.encode_records(changed)
        for stream in (bytes.fromhex('000100ff2f'), bytes.fromhex('00ff2f00'), bytes.fromhex('00ff5500')):
            with self.assertRaises(ValueError):
                codec.parse_records(sequence(stream))

    def test_bad_back_references_and_physical_overlap_fail(self):
        records = codec.parse_records(sequence(bytes.fromhex('00903c640afe00050500ff2f')))
        for refs in ([[5, 5, 0]], [[5, 0xFE00, 5]], [[5, 65536, 5]], [[5, 5, 200]],
                     [[5, 5, 5], [6, 5, 1]], [[-1, 0, 1]], [[5, 65535, 5]]):
            changed = copy.deepcopy(records)
            changed['tracks'][0]['back_references'] = refs
            with self.subTest(refs=refs), self.assertRaises(ValueError):
                codec.encode_records(changed)
        records = codec.parse_records(sequence(bytes.fromhex('00ff2d01010000000800ff2f')))
        records['tracks'][0]['back_references'] = [[3, 1, 1]]
        with self.assertRaisesRegex(ValueError, 'range'):
            codec.encode_records(records)

    def test_consumer_proof_rejects_missing_full_spans(self):
        with self.assertRaisesRegex(ValueError, 'consumer changed'):
            codec.verify_consumers(b'')

    def test_unsigned_fields_reject_wrong_types_and_overflow(self):
        raw = sequence(bytes.fromhex('00ff5101234500ff2e123400ff2d01010000000800ff2f'))
        records = codec.parse_records(raw)
        for event_index, field, values in [(0, 'tempo_us', [True, -1, 0x1000000, 1.5]),
                                            (1, 'marker_value', [False, 0x10000, '1']),
                                            (2, 'repeat_count', [True, 256]),
                                            (2, 'back_offset', [True, 0x100000000])]:
            for value in values:
                changed = copy.deepcopy(records)
                changed['tracks'][0]['events'][event_index][field] = value
                with self.subTest(field=field, value=value), self.assertRaises(ValueError):
                    codec.encode_records(changed)
        for value in (True, 0, 32768, -1):
            with self.subTest(division=value), self.assertRaises(ValueError):
                codec.encode_records(dict(records, division=value))
