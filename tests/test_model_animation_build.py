from __future__ import annotations

import copy
import struct
import unittest

from scripts import model_animation_build as animation, model_assets


def animation_payload():
    descriptor = struct.pack('>bBbBbBBBBB', -1, 2, 2, 2, -3, 7, 0x11, 0xE1, 0, 0)
    descriptor += struct.pack('>7H', 123, 456, 0x8000, 0x31, 0x102, 1, 1)
    stream = struct.pack('>3hB3hB', -12, 34, 56, 0xBA, 78, -90, 123, 0) + bytes(2)
    parts = [descriptor, stream, descriptor, stream]
    offset = 32
    segments = []
    for index, data in enumerate(parts):
        segments.append(model_assets.ModelSegment(index, offset, len(data), index == 3, data))
        offset += len(data)
    return model_assets.encode_model_bundle(tuple(segments))


class AnimationBuildTests(unittest.TestCase):
    def test_channels_agree_with_independent_pose_decoder(self):
        payload = animation_payload()
        records = animation.animation_records(payload)
        self.assertEqual(animation.encode_animation_records(records), payload)
        clip = records['clips'][0]
        frame = clip['frames'][0]
        self.assertEqual(frame['joint_translations'], [[-12, 34, 56]])
        self.assertEqual(frame['root_offsets'], [1, 0, 1])
        self.assertEqual(frame['rotation_offsets'], [1, 1, 0])
        self.assertEqual(frame['scale_offsets'], [2, None, None])
        segments = model_assets.parse_model_bundle(payload)
        pose = model_assets.decode_character_animation_frame(segments[0].data, segments[1].data[:7])
        self.assertEqual(pose.root_translation, (-4064, 8192, -12256))
        self.assertEqual(pose.encoded_rotations, ((64, 32, 0),))
        self.assertEqual(pose.scale_channels, (320, None, None))

    def test_channel_edits_change_native_bytes(self):
        payload = animation_payload()
        records = animation.animation_records(payload)
        for name, value in [('joint_translations', [[1, 2, 3]]), ('root_offsets', [0, 1, 0]),
                             ('rotation_offsets', [0, 0, 1]), ('scale_offsets', [3, None, None])]:
            changed = copy.deepcopy(records)
            changed['clips'][0]['frames'][0][name] = value
            with self.subTest(channel=name):
                data = animation.encode_animation_records(changed)
                self.assertNotEqual(data, payload)
                self.assertEqual(animation.animation_records(data), changed)

    def test_overflow_counts_and_unknown_storage_are_rejected(self):
        records = animation.animation_records(animation_payload())
        changes = [('root_offsets', [2, 0, 0]), ('root_offsets', [-1, 0, 0]),
                   ('rotation_offsets', [0]), ('scale_offsets', [1, 0, None]),
                   ('joint_translations', [[32768, 0, 0]]), ('opaque', [0])]
        for field, value in changes:
            changed = copy.deepcopy(records)
            changed['clips'][0]['frames'][0][field] = value
            with self.subTest(field=field, value=value), self.assertRaises(ValueError):
                animation.encode_animation_records(changed)
        for field, value in [('frames', []), ('stream_padding', 8), ('descriptor_padding', 8),
                             ('optional_words', []), ('translation_mask_words', []), ('opaque', [])]:
            changed = copy.deepcopy(records)
            changed['clips'][0][field] = value
            with self.subTest(field=field), self.assertRaises(ValueError):
                animation.encode_animation_records(changed)

    def test_native_padding_and_frame_tails_are_not_opaque(self):
        descriptor = bytearray(16)
        descriptor[1], descriptor[3], descriptor[5] = 2, 2, 1
        struct.pack_into('>3H', descriptor, 10, 1, 1, 1)
        records = animation.clip_records(bytes(descriptor), b'\xE0\x00' + bytes(6))
        self.assertEqual(animation.encode_clip(records), (bytes(descriptor), b'\xE0\x00' + bytes(6)))
        for stream in (b'\xE1\x00' + bytes(6), b'\xE0\x00' + bytes(5) + b'\x01', bytes(16)):
            with self.assertRaises(ValueError):
                animation.clip_records(bytes(descriptor), stream)
        descriptor[5] = 2
        with self.assertRaisesRegex(ValueError, 'per-frame'):
            animation.clip_records(bytes(descriptor), bytes(8))
        descriptor[5], descriptor[3] = 1, 255
        with self.assertRaisesRegex(ValueError, 'truncated'):
            animation.clip_records(bytes(descriptor), bytes(8))

    def test_special_duration_entries_and_missing_consumers_fail(self):
        for entry in animation.SPECIAL_DURATION_ENTRIES:
            with self.subTest(entry=entry), self.assertRaisesRegex(ValueError, 'duration'):
                animation.animation_records(animation_payload(), entry=entry)
        with self.assertRaisesRegex(ValueError, 'consumer changed'):
            animation.verify_consumers(b'', 0x15000000)

    def test_single_pair_table_preserves_scene_bundle_contract(self):
        records = animation.animation_records(animation_payload())
        records['clips'] = records['clips'][:1]
        payload = animation.encode_animation_records(records)
        self.assertEqual(animation.animation_records(payload), records)
        self.assertEqual(struct.unpack_from('>I', payload)[0], 16)
        self.assertEqual(len(animation.animation_segments(payload)), 2)
        with self.assertRaises(ValueError):
            model_assets.parse_model_bundle(payload)
        for offset, value in ((0, 8), (0, 24), (0, 32), (4, 0x80000018),
                              (8, 16), (12, 16), (12, 0x90000010), (12, 0x80000018)):
            changed = bytearray(payload)
            struct.pack_into('>I', changed, offset, value)
            with self.subTest(offset=offset, value=value), self.assertRaises(ValueError):
                animation.animation_segments(bytes(changed))
        with self.assertRaises(ValueError):
            animation.animation_segments(payload + bytes(8))
        records['clips'] = []
        with self.assertRaises(ValueError):
            animation.encode_animation_records(records)

    def test_fixed_runtime_duration_controls_native_frame_count(self):
        descriptor = bytearray(16)
        descriptor[1], descriptor[3], descriptor[5], descriptor[8] = 2, 255, 1, 3
        struct.pack_into('>3H', descriptor, 10, 1, 1, 1)
        stream = bytes([0xE0] * 161) + bytes(7)
        clip = animation.clip_records(bytes(descriptor), stream, runtime_duration=641)
        self.assertEqual(len(clip['frames']), 161)
        records = {'format': 'character-animation-fixed-duration', 'character_entry': 183,
                   'runtime_duration': 641, 'clips': [clip]}
        payload = animation.encode_animation_records(records)
        self.assertEqual(animation.animation_records(payload, entry=183, runtime_duration=641), records)
        with self.assertRaises(ValueError):
            animation.clip_records(bytes(descriptor), stream)
        for field, value in [('runtime_duration', 0), ('runtime_duration', True),
                             ('runtime_duration', 65536), ('character_entry', 146),
                             ('character_entry', 7), ('opaque', [])]:
            changed = copy.deepcopy(records)
            changed[field] = value
            with self.subTest(field=field, value=value), self.assertRaises(ValueError):
                animation.encode_animation_records(changed)
        for entry in (146, 7, None):
            with self.subTest(entry=entry), self.assertRaises(ValueError):
                animation.animation_records(payload, entry=entry, runtime_duration=641)
        for field, value in [('frames', clip['frames'][:-1]), ('stream_padding', 8)]:
            changed = copy.deepcopy(records)
            changed['clips'][0][field] = value
            with self.subTest(field=field), self.assertRaises(ValueError):
                animation.encode_animation_records(changed)

    def test_fixed_duration_scalar_is_pinned_at_its_native_address(self):
        address = model_assets.CHARACTER_ANIMATION_SPECIAL_DURATION_ADDRESS
        scalar = struct.pack('>f', 641.0)
        self.assertEqual(animation.verify_fixed_duration(scalar, address), 641)
        for data, base in ((scalar[:3], address), (scalar, address + 1),
                           (struct.pack('>f', 640.0), address), (scalar, address - 1)):
            with self.subTest(data=data, base=base), self.assertRaises(ValueError):
                animation.verify_fixed_duration(data, base)
