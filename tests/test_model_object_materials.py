import hashlib
import struct
import unittest
from unittest.mock import patch

from scripts import model_object_materials as objects


class ObjectMaterialTests(unittest.TestCase):
    def placement(self, bank=3, entry=0, flags=0):
        source = [3, entry] if bank == 3 else [4, 12, entry]
        record = {'model_source': source, 'dispatch_kind': 0 if bank == 3 else 1,
                  'model_resolution_status': 'resolved-bank-03-model' if bank == 3 else 'resolved-bank-04-segment',
                  'bytes_3c_3f': bytes((flags, 0, 0, 0)).hex(),
                  'index': 2, 'sha1': 'a' * 40}
        return {'scenes': [{'bank_index': 12 if bank == 3 else 11,
                            'scene_index': 12, 'records': [record]}]}

    def test_bank03_uses_rom_defaults_instead_of_placement_flags(self):
        placement = self.placement(flags=2)
        result = objects.placement_contexts(placement, bytes(12), objects.OBJECT_TABLE)
        self.assertEqual((3, 0, 0), tuple(result[0][key] for key in ('bank', 'entry', 'segment')))
        self.assertEqual(0, result[0]['placements'][0]['initial_flags_70'])
        data = bytearray(12)
        data[9] = 2
        self.assertEqual([], objects.placement_contexts(self.placement(), data, objects.OBJECT_TABLE))
        with self.assertRaisesRegex(ValueError, 'exceed ROM data'):
            objects.placement_contexts(placement, bytes(11), objects.OBJECT_TABLE)

    def test_bank04_requires_resolved_direct_dispatch(self):
        placement = self.placement(4, 29, 8)
        result = objects.placement_contexts(placement, b'', 0)
        self.assertEqual((4, 12, 29), tuple(result[0][key] for key in ('bank', 'entry', 'segment')))
        self.assertEqual(0, result[0]['placements'][0]['initial_flags_70'])
        self.assertEqual([], objects.placement_contexts(self.placement(4, 29, 2), b'', 0))
        record = placement['scenes'][0]['records'][0]
        record['dispatch_kind'] = 3
        self.assertEqual([], objects.placement_contexts(placement, b'', 0))
        record['dispatch_kind'] = 1
        record['model_resolution_status'] = 'unavailable-bank-04-scene-or-segment'
        self.assertEqual([], objects.placement_contexts(placement, b'', 0))

    def test_consumer_guard_rejects_changes_new_callers_and_function_pointers(self):
        base = 0x15000000
        code = struct.pack('>II', 0x03E00008, 0)
        pin = (base, len(code), hashlib.sha1(code).hexdigest())
        with patch.object(objects, 'CONSUMERS', (pin,)), patch.object(objects, 'OVERRIDE_CALLS', ()):
            self.assertEqual(1, len(objects.verify_consumers(code, base, b'')))
            with self.assertRaisesRegex(ValueError, 'consumer changed'):
                objects.verify_consumers(bytes(8), base, b'')
            with self.assertRaisesRegex(ValueError, 'outside ROM code'):
                objects.verify_consumers(code[:4], base, b'')
            call = (3 << 26) | ((0x1510D874 >> 2) & 0x3FFFFFF)
            with self.assertRaisesRegex(ValueError, 'callers changed'):
                objects.verify_consumers(code + struct.pack('>I', call), base, b'')
            with self.assertRaisesRegex(ValueError, 'unreviewed data pointer'):
                objects.verify_consumers(code, base, struct.pack('>I', 0x1510D874))


if __name__ == '__main__':
    unittest.main()
