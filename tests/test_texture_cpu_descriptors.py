"""Native descriptor evidence and complete texture storage must agree."""
from contextlib import ExitStack
import hashlib
from pathlib import Path
import struct
from types import SimpleNamespace
import unittest
from unittest.mock import patch

from scripts import texture_cpu_descriptors as cpu


class CpuTextureDescriptorTests(unittest.TestCase):
    def fixture(self):
        base = 0x80090000
        data = bytearray(cpu.SIZE_TABLE + 16 - base)
        frames = struct.pack('>2I', 42, 43)
        table = struct.pack('>IBBHHBB', base + 0x100, 2, 0, 16, 16, 0, 2)
        table += struct.pack('>IBBHHBB', base + 0x104, 1, 0, 16, 16, 0, 2)
        table += struct.pack('>IBBHHBB', 44, 1, 0, 16, 16, 0, 2)
        data[0x100:0x108] = frames
        data[cpu.TABLE - base:cpu.TABLE - base + len(table)] = table
        data[cpu.SIZE_TABLE - base:] = cpu.SIZE_BYTES
        code = b'complete-native-consumer'
        guards = {'COUNT': 3, 'CONSUMERS': ((0x1000, len(code), hashlib.sha1(code).hexdigest()),),
                  'TABLE_SHA1': hashlib.sha1(table).hexdigest(),
                  'FRAMES_SHA1': hashlib.sha1(frames + frames[4:]).hexdigest()}
        return base, code, data, guards

    def parse(self, code, data, base, guards):
        with patch.multiple(cpu, **guards):
            return cpu.verified_descriptors(code, 0x1000, data, base)

    def test_record_shape_frame_order_and_native_evidence(self):
        base, code, data, guards = self.fixture()
        records = self.parse(code, data, base, guards)
        self.assertEqual([r['resources'] for r in records], [[42, 43], [43], [44]])
        self.assertEqual(records[1]['address'], f'0x{cpu.TABLE + 12:08X}')
        self.assertEqual((records[0]['width'], records[0]['height'], records[0]['format'], records[0]['size']),
                         (16, 16, 0, 2))

    def test_changed_native_function_descriptor_frame_array_and_size_table_fail(self):
        base, code, data, guards = self.fixture()
        with self.assertRaisesRegex(ValueError, 'consumer changed'):
            self.parse(b'X' + code[1:], data, base, guards)
        for offset, message in ((cpu.TABLE - base + 6, 'descriptor table'),
                                (0x107, 'frame arrays'), (cpu.SIZE_TABLE - base, 'transfer-size')):
            altered = bytearray(data)
            altered[offset] ^= 1
            with self.subTest(message=message), self.assertRaisesRegex(ValueError, message):
                self.parse(code, altered, base, guards)

    def record(self, fmt=0, size=2, width=16, height=16):
        return {'format': fmt, 'size': size, 'width': width, 'height': height, 'count': 1, 'flags': 0}

    def test_all_declared_formats_roundtrip_every_pixel_and_palette_byte(self):
        for fmt, size in cpu.FORMATS:
            count = 16 * 16 * (4 << size) // 8 + ((32 if size == 0 else 512) if fmt == 2 else 0)
            payload = bytes(i % 256 for i in range(count))
            with self.subTest(fmt=fmt, size=size):
                contract = cpu.storage_contract(self.record(fmt, size), payload)
                self.assertIsNotNone(contract)
                self.assertTrue(cpu.reversible(contract, payload))

    def test_partial_trailing_overlarge_or_unaligned_storage_cannot_qualify(self):
        for record, count in ((self.record(), 511), (self.record(), 513),
                              (self.record(0, 3, 64, 64), 16384),
                              (self.record(2, 1, 64, 64), 4608),
                              (self.record(0, 3, 6, 16), 384),
                              (self.record(5, 2, 8, 16), 320),
                              (self.record(7, 1), 256),
                              ({**self.record(), 'flags': 1}, 512),
                              ({**self.record(), 'count': 0}, 512)):
            with self.subTest(record=record, count=count):
                self.assertIsNone(cpu.storage_contract(record, bytes(count)))

    def test_rgba16_i4_source_has_two_complete_same_size_image_planes(self):
        payload = bytes(i % 256 for i in range(1280))
        contract = cpu.storage_contract(self.record(5, 2, 16, 32), payload)
        self.assertEqual([(p['format'], p['offset'], p['bytes']) for p in contract['levels']],
                         [('rgba16', 0, 1024), ('i4', 1024, 256)])
        self.assertEqual(contract['palette_size'], 0)
        self.assertTrue(cpu.reversible(contract, payload))
        self.assertIsNone(cpu.storage_contract(self.record(5, 2, 16, 32), payload + b'\0'))

    def test_load_preserves_exclusions_deduplicates_and_retains_full_frame_proof(self):
        base, code, data, guards = self.fixture()
        rom = b'synthetic ROM'
        layout = {'normalized_sha1': [hashlib.sha1(rom).hexdigest()], 'game_start': 0,
                  'game_end': len(rom), 'game_vram': 0x1000, 'game_data_vram': base}
        entries = [SimpleNamespace(index=i, data=bytes(512)) for i in (42, 43, 44)]
        with ExitStack() as stack:
            stack.enter_context(patch.multiple(cpu, **guards))
            stack.enter_context(patch.object(cpu.h, 'resolve_rom', return_value=(None, layout)))
            stack.enter_context(patch.object(cpu.h, 'parse_game_archive', return_value=SimpleNamespace(code=code, data=data)))
            result = cpu.load(Path('/synthetic'), rom, entries, {42})
            self.assertEqual(list(result), [43, 44])
            self.assertEqual(result[44]['consumer']['descriptor']['pointer'], 44)
            self.assertEqual(result[43]['consumer']['selected_frame'], 1)
            self.assertEqual(result[43]['consumer']['descriptor']['resources'], [42, 43])
            with patch.object(cpu, 'reversible', return_value=False):
                self.assertEqual(cpu.load(Path('/synthetic'), rom, entries), {})
            with self.assertRaisesRegex(ValueError, 'reference ROM changed'):
                cpu.load(Path('/synthetic'), b'changed', entries)
