import hashlib
import math
import struct
import unittest
from unittest import mock

from scripts import texture_object_light as light


class ObjectLightTests(unittest.TestCase):
    def test_phase_edges_and_no_repeated_callback(self):
        self.assertIsNone(light.phase_callback(0, 0))
        self.assertIsNone(light.phase_callback(11.999, 0))
        self.assertEqual(light.phase_callback(12, 0), 0)
        self.assertEqual(light.phase_callback(36.999, 0), 0)
        self.assertIsNone(light.phase_callback(12, 1))
        self.assertEqual(light.phase_callback(37, 1), 1)
        self.assertIsNone(light.phase_callback(61.999, 3))
        for time in (-1, 62, math.inf, math.nan):
            with self.assertRaises(ValueError):
                light.phase_callback(time, 0)

    def test_native_guard_covers_entire_functions_and_tables(self):
        code = bytes(range(64))
        data = struct.pack('>4I', 1682, 1683, 1684, 1685)
        with mock.patch.object(light, 'CONSUMERS', ((0, 64, hashlib.sha1(code).hexdigest()),)), \
                mock.patch.object(light, 'DATA', ((0x80090204, data.hex()),)):
            self.assertEqual(light.verified_native(code, 0, data, 0x80090204), (1684, 1685))
            for at in (0, 31, 63):
                changed = bytearray(code); changed[at] ^= 1
                with self.assertRaisesRegex(ValueError, 'consumer changed'):
                    light.verified_native(changed, 0, data, 0x80090204)
            for at in range(len(data)):
                changed = bytearray(data); changed[at] ^= 1
                with self.assertRaisesRegex(ValueError, 'table changed'):
                    light.verified_native(code, 0, changed, 0x80090204)

    def test_missing_changed_and_ambiguous_object_ids_rejected(self):
        payload = bytearray(4160)
        for row, callback, _, _ in light.LIGHT_LINKS:
            payload[row * 52 + 21] = 9 << 2
            struct.pack_into('>I', payload, row * 52 + 32, callback)
        records = []; expected = {}
        for index, (ident, _) in light.PLACEMENTS.items():
            raw = bytearray(68); raw[51] = ident
            expected[index] = ident, hashlib.sha1(raw).hexdigest()
            records.append(dict(index=index, raw_hex=raw.hex(), model_source=[4, 28, 12],
                                dispatch_kind=1, word_14='0x18'))
        scene = dict(scene_index=28, bank_index=11, records=records)
        with mock.patch.object(light, 'LIGHT_SHA1', hashlib.sha1(payload).hexdigest()), \
                mock.patch.object(light, 'PLACEMENTS', expected):
            light.checked_sources(payload, {'scenes': [scene]})
            for bad in ([], records[:-1], records + records[:1]):
                with self.assertRaises(ValueError):
                    light.checked_sources(payload, {'scenes': [{**scene, 'records': bad}]})
            with self.assertRaises(ValueError):
                light.checked_sources(payload, {'scenes': [scene, {**scene, 'bank_index': 12}]})
            changed = bytearray(payload); changed[35 * 52 + 21] ^= 4
            with self.assertRaisesRegex(ValueError, 'scene source changed'):
                light.checked_sources(changed, {'scenes': [scene]})
            bad = [dict(r) for r in records]; bad[0]['model_source'] = [4, 28, 11]
            with self.assertRaises(ValueError):
                light.checked_sources(payload, {'scenes': [{**scene, 'records': bad}]})


if __name__ == '__main__':
    unittest.main()
