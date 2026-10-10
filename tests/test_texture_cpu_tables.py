import hashlib
import struct
import unittest
from unittest import mock

from scripts import texture_cpu_tables as tables, texture_cpu_descriptors as cpu


class NativeTableTests(unittest.TestCase):
    def test_full_storage_is_independent_of_sampler_bounds(self):
        cases = ((4096, 'i8', 64, 64), (4096, 'ia8', 64, 64), (2048, 'rgba16', 32, 32))
        for record, (extent, fmt, width, height) in zip(tables.LOADS, cases):
            with self.subTest(resources=record[0]):
                payload = bytes((i * 19 + i // 31) % 256 for i in range(extent))
                contract = tables.storage_contract(record, payload)
                self.assertEqual((contract['format'], contract['width'], contract['height']),
                                 (fmt, width, height))
                self.assertTrue(cpu.reversible(contract, payload))
                self.assertIsNone(tables.storage_contract(record, payload[:-1]))
                self.assertIsNone(tables.storage_contract(record, payload + b'\0'))

    def test_unsupported_loads_rejected(self):
        original = tables.LOADS[0]
        for field, word, mask in ((2, None, 1), (3, 0, 1), (3, 1, 0x1000000),
                                  (4, 0, 0x1000), (4, 1, 1), (4, 1, 0x1000),
                                  (5, 0, 1), (5, 0, 0x1000), (5, 1, 0x1000000)):
            record = list(original)
            if word is None:
                record[field] ^= mask
            else:
                pair = list(record[field]); pair[word] ^= mask; record[field] = tuple(pair)
            with self.subTest(change=(field, word, mask)):
                self.assertIsNone(tables.storage_contract(record, bytes(4096)))

    def test_native_and_table_guards(self):
        code = bytes(range(64))
        data = struct.pack('>6I', 3929, 1968, 4417, 4414, 4415, 4416)
        with mock.patch.object(tables, 'CONSUMERS',
                               ((0x15000000, len(code), hashlib.sha1(code).hexdigest()),)):
            self.assertEqual(tables.verified_resources(code, 0x15000000, data, tables.TABLE),
                             (3929, 1968, 4417, 4414, 4415, 4416))
            for offset in (0, 32, 63):
                changed = bytearray(code); changed[offset] ^= 1
                with self.assertRaisesRegex(ValueError, 'consumer changed'):
                    tables.verified_resources(changed, 0x15000000, data, tables.TABLE)
            for offset in range(len(data)):
                changed = bytearray(data); changed[offset] ^= 1
                with self.assertRaisesRegex(ValueError, 'resource table changed'):
                    tables.verified_resources(code, 0x15000000, changed, tables.TABLE)


if __name__ == '__main__':
    unittest.main()
