import hashlib
import struct
import unittest
from unittest import mock

from scripts import texture_cpu_strips as strips, texture_cpu_descriptors as cpu


class NativeSourceStripTests(unittest.TestCase):
    def test_entire_source_inverts_without_inventing_transfer_tail(self):
        payload = bytes((i * 31 + i // 7) % 256 for i in range(1024))
        contract = strips.storage_contract(payload)
        self.assertEqual((contract['format'], contract['width'], contract['height']), ('i4', 128, 16))
        self.assertTrue(cpu.reversible(contract, payload))
        # Sixteen rows come from the rectangle and T step, not the payload size
        # or the larger sampler rectangle. A full-TMEM payload cannot qualify.
        self.assertLess(30 * 0x222, 16 * 1024)
        self.assertGreater(30 * 0x222, 15 * 1024)
        for size in (512, 1023, 1025, 2048, 4096):
            self.assertIsNone(strips.storage_contract(bytes(size)))

    def test_inconsistent_stride_format_bounds_and_strip_extent_rejected(self):
        for name, value in (
                ('RENDER_TILE', (0xF5881000, 0x0009C270)),
                ('RENDER_TILE', (0xF5800800, 0x0009C270)),
                ('BOUNDS', (0xF2002002, 0x000FE0FE)),
                ('RECTANGLE_HEIGHT', 60), ('T_STEP', 1024),
                ('LOAD_BLOCK', (0xF3000000, 0x077FF100)),
                ('LOAD_BLOCK', (0xF3000000, 0x071FF000))):
            with self.subTest(field=name), mock.patch.object(strips, name, value):
                self.assertIsNone(strips.storage_contract(bytes(1024)))

    def test_native_and_resource_identity_guards(self):
        code = bytes(range(64)); data = struct.pack('>2I', 1956, 1957)
        with mock.patch.object(strips, 'CONSUMERS',
                               ((0x15000000, len(code), hashlib.sha1(code).hexdigest()),)):
            self.assertEqual(strips.verified_resources(code, 0x15000000, data, strips.TABLE),
                             (1956, 1957))
            for offset in (0, 31, 63):
                changed = bytearray(code); changed[offset] ^= 1
                with self.assertRaisesRegex(ValueError, 'consumer changed'):
                    strips.verified_resources(changed, 0x15000000, data, strips.TABLE)
            for offset in range(len(data)):
                changed = bytearray(data); changed[offset] ^= 1
                with self.assertRaisesRegex(ValueError, 'resource table changed'):
                    strips.verified_resources(code, 0x15000000, changed, strips.TABLE)


if __name__ == '__main__':
    unittest.main()
