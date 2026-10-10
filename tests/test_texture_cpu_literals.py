import unittest
from unittest import mock

from scripts import texture_cpu_literals as literals, texture_cpu_descriptors as cpu


class LiteralStorageTests(unittest.TestCase):
    def test_reviewed_full_payloads_round_trip(self):
        cases = ((4096, 'rgba32', 32, 32), (2048, 'rgba16', 32, 32),
                 (4096, 'ia8', 64, 64), (1024, 'ia8', 32, 32),
                 (4096, 'ia8', 64, 64), (3072, 'rgba16', 48, 32),
                 (4096, 'rgba32', 32, 32), (4096, 'rgba32', 32, 32),
                 (2048, 'rgba32', 16, 32))
        self.assertEqual(len(cases), len(literals.RECORDS))
        for record, (size, fmt, width, height) in zip(literals.RECORDS, cases):
            with self.subTest(resources=record[0]):
                payload = bytes((i * 37 + i // 13) % 256 for i in range(size))
                contract = literals.storage_contract(record, payload)
                self.assertEqual((contract['format'], contract['width'], contract['height']),
                                 (fmt, width, height))
                self.assertTrue(cpu.reversible(contract, payload))
                self.assertIsNone(literals.storage_contract(record, payload[:-1]))
                self.assertIsNone(literals.storage_contract(record, payload + b'\0'))

    def test_inconsistent_transfers_and_tiles_rejected(self):
        original = literals.RECORDS[0]
        # Nonzero image width, load origin, wrong tile, DXT, transfer extent,
        # render origin/stride, fractional bounds and palette-dependent format.
        changes = ((4, None, 1), (5, 0, 1), (5, 1, 0x01000000),
                   (6, 1, 1), (6, 1, 0x1000), (7, 0, 1),
                   (7, 0, 0x200), (8, 1, 1), (8, 0, 0x1000),
                   (7, 0, 0x00400000))
        for field, word, mask in changes:
            with self.subTest(change=(field, word, mask)):
                record = list(original)
                if word is None:
                    record[field] ^= mask
                else:
                    pair = list(record[field]); pair[word] ^= mask
                    record[field] = tuple(pair)
                self.assertIsNone(literals.storage_contract(record, bytes(4096)))

    def test_whole_native_span_is_guarded(self):
        import hashlib
        code = bytes(range(64))
        with mock.patch.object(literals, 'CONSUMERS',
                               ((0x15000000, 64, hashlib.sha1(code).hexdigest()),)):
            self.assertEqual(literals.verified_records(code, 0x15000000), literals.RECORDS)
            for offset in (0, 32, 63):
                changed = bytearray(code); changed[offset] ^= 1
                with self.assertRaisesRegex(ValueError, 'consumer changed'):
                    literals.verified_records(changed, 0x15000000)


if __name__ == '__main__':
    unittest.main()
