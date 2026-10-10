"""Particle admission requires the complete callback, frame and storage chain."""
from contextlib import ExitStack
import hashlib
from pathlib import Path
import struct
from types import SimpleNamespace
import unittest
from unittest.mock import patch

from scripts import texture_cpu_particles as particles


def sha(raw):
    return hashlib.sha1(raw).hexdigest()


class CpuParticleTests(unittest.TestCase):
    def fixture(self):
        base = 0x80000000
        code = b'whole native particle constructor and consumer'
        data = bytearray(0x100)
        descriptor = struct.pack('>IBBHHBB', base + 0x40, 3, 0, 16, 16, 0, 3)
        frames = struct.pack('>3I', 42, 43, 42)
        data[0:12] = descriptor
        data[0x40:0x4C] = frames
        data[0x60:0x64] = b'call'
        data[0x80:0x90] = particles.cpu.SIZE_BYTES
        guards = dict(DESCRIPTOR=base, DESCRIPTOR_SHA1=sha(descriptor), FRAMES_SHA1=sha(frames),
                      DATA_GUARDS=((base + 0x60, 4, sha(b'call')),),
                      CONSUMERS=((0x1000, len(code), sha(code)),))
        return base, code, data, guards

    def parse(self, base, code, data, guards):
        with patch.multiple(particles, **guards), patch.object(particles.cpu, 'SIZE_TABLE', base + 0x80):
            return particles.verified_descriptor(code, 0x1000, data, base)

    def test_frame_order_duplicates_and_descriptor_fields_are_preserved(self):
        base, code, data, guards = self.fixture()
        record = self.parse(base, code, data, guards)
        self.assertEqual(record['resources'], [42, 43, 42])
        self.assertEqual((record['count'], record['width'], record['height']), (3, 16, 16))
        self.assertEqual(record['frame_sha1'], guards['FRAMES_SHA1'])

    def test_native_callbacks_descriptor_and_every_frame_are_guarded(self):
        base, code, data, guards = self.fixture()
        with self.assertRaisesRegex(ValueError, 'consumer'):
            self.parse(base, code[:-1] + b'!', data, guards)
        for offset, label in ((6, 'descriptor'), (0x43, 'frame array'), (0x47, 'frame array'),
                              (0x4B, 'frame array'), (0x60, 'callback data'), (0x80, 'transfer-size')):
            altered = bytearray(data)
            altered[offset] ^= 1
            with self.subTest(offset=offset), self.assertRaisesRegex(ValueError, label):
                self.parse(base, code, altered, guards)

    def test_invalid_frame_descriptor_is_rejected_even_with_replaced_digest(self):
        base, code, data, guards = self.fixture()
        for pointer, count, flags in ((base + 0x41, 3, 0), (42, 3, 0),
                                       (base + 0x40, 0, 0), (base + 0x40, 3, 1)):
            altered = bytearray(data)
            altered[:12] = struct.pack('>IBBHHBB', pointer, count, flags, 16, 16, 0, 3)
            changed = dict(guards, DESCRIPTOR_SHA1=sha(altered[:12]))
            with self.subTest(pointer=pointer, count=count, flags=flags), self.assertRaisesRegex(ValueError, 'frame-array'):
                self.parse(base, code, altered, changed)

    def test_frame_array_bounds_and_resource_range_are_checked(self):
        base, code, data, guards = self.fixture()
        with self.assertRaises(ValueError):
            self.parse(base, code, data[:0x48], guards)
        altered = bytearray(data)
        altered[0x44:0x48] = struct.pack('>I', particles.h.RUNTIME_FLAT_ASSET_COUNT)
        with self.assertRaisesRegex(ValueError, 'out of range'):
            self.parse(base, code, altered, dict(guards, FRAMES_SHA1=sha(altered[0x40:0x4C])))

    def test_load_preserves_exclusions_frame_identity_and_full_payload_gate(self):
        base, code, data, guards = self.fixture()
        rom = b'reference ROM'
        layout = dict(normalized_sha1=[sha(rom)], game_start=0, game_end=len(rom),
                      game_vram=0x1000, game_data_vram=base)
        entries = [SimpleNamespace(index=i, data=bytes(1024)) for i in (42, 43)]
        with ExitStack() as stack:
            stack.enter_context(patch.multiple(particles, **guards))
            stack.enter_context(patch.object(particles.cpu, 'SIZE_TABLE', base + 0x80))
            stack.enter_context(patch.object(particles.h, 'resolve_rom', return_value=(None, layout)))
            stack.enter_context(patch.object(particles.h, 'parse_game_archive', return_value=SimpleNamespace(code=code, data=data)))
            result = particles.load(Path('/synthetic'), rom, entries, {42})
            self.assertEqual(list(result), [43])
            self.assertEqual(result[43]['consumer']['selected_frame'], 1)
            self.assertEqual(list(particles.load(Path('/synthetic'), rom, entries)), [42, 43])
            entries[0].data += b'opaque tail'
            self.assertEqual(list(particles.load(Path('/synthetic'), rom, entries)), [43])
            with self.assertRaisesRegex(ValueError, 'reference ROM'):
                particles.load(Path('/synthetic'), rom + b'!', entries)
