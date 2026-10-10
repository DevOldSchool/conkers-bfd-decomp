"""Caller evidence, descriptor layouts and frame identity are acceptance gates."""
from contextlib import ExitStack
import hashlib
from pathlib import Path
import struct
from types import SimpleNamespace
import unittest
from unittest.mock import patch

from scripts import texture_cpu_effects as effects


def sha(raw):
    return hashlib.sha1(raw).hexdigest()


class CpuEffectTextureTests(unittest.TestCase):
    def fixture(self):
        base = 0x80000000
        data = bytearray(0x800)
        pointer = struct.pack('>IBBHHBB', 44, 1, 0, 16, 16, 0, 2)
        literal = struct.pack('>IBBHHBB', base + 0x700, 2, 0, 16, 16, 0, 2)
        frames = struct.pack('>2I', 42, 43)
        table = struct.pack('>3I', base + 0x200, 0, base + 0x200)
        compact = struct.pack('>IHHBBBB', 45, 16, 16, 0, 2, 0, 0)
        compact_array = struct.pack('>IHHBBBB', 0, 16, 16, 0, 2, 1, 0)
        array = struct.pack('>2I', 46, 44)
        for offset, raw in ((0x100, table), (0x10C, struct.pack('>3I', *effects.CALLBACKS)),
                            (0x200, pointer), (0x300, literal), (0x400, compact),
                            (0x40C, compact_array), (0x500, array),
                            (0x600, effects.cpu.SIZE_BYTES), (0x700, frames)):
            data[offset:offset + len(raw)] = raw
        code = b'whole registered native consumer span'
        guards = dict(POINTER_TABLE=base + 0x100, POINTER_COUNT=3, POINTER_SHA1=sha(table),
                      POINTER_DESCRIPTORS_SHA1=sha(pointer * 2), POINTER_FRAMES_SHA1=sha(b''),
                      LITERALS=(base + 0x300,), LITERAL_SHA1=sha(literal), LITERAL_FRAMES_SHA1=sha(frames),
                      COMPACT=((base + 0x400, sha(compact)), (base + 0x40C, sha(compact_array))),
                      COMPACT_ARRAY=base + 0x500, COMPACT_ARRAY_COUNT=2, COMPACT_ARRAY_SHA1=sha(array),
                      CONSUMERS=((0x1000, len(code), sha(code)),))
        return base, code, data, guards

    def parse(self, code, data, base, guards):
        with patch.multiple(effects, **guards), patch.object(effects.cpu, 'SIZE_TABLE', base + 0x600):
            return effects.verified_descriptors(code, 0x1000, data, base)

    def test_pointer_holes_duplicates_literal_frame_order_and_compact_layouts(self):
        base, code, data, guards = self.fixture()
        records = self.parse(code, data, base, guards)
        self.assertEqual([r['resources'] for r in records], [[44], [44], [42, 43], [45], [46, 44]])
        self.assertEqual([r['selector'] for r in records[:2]], [0, 2])
        self.assertEqual(records[2]['pointer'], base + 0x700)
        self.assertEqual(records[2]['frame_sha1'], guards['LITERAL_FRAMES_SHA1'])
        self.assertEqual((records[4]['flags'], records[4]['explicit_pixel_frame_offset']), (1, 0))
        self.assertEqual((records[4]['width'], records[4]['height'], records[4]['format'], records[4]['size']),
                         (16, 16, 0, 2))

    def test_native_and_every_data_evidence_boundary_fail_closed(self):
        base, code, data, guards = self.fixture()
        with self.assertRaisesRegex(ValueError, 'consumer'):
            self.parse(code[:-1] + b'!', data, base, guards)
        for offset, label in ((0x100, 'pointer table'), (0x10C, 'boundary'),
                              (0x206, 'pointer descriptors'), (0x306, 'literal descriptors'),
                              (0x707, 'literal frame arrays'), (0x404, 'compact descriptor'),
                              (0x410, 'compact descriptor'), (0x500, 'compact resource array'),
                              (0x600, 'transfer-size')):
            altered = bytearray(data)
            altered[offset] ^= 1
            with self.subTest(offset=offset), self.assertRaisesRegex(ValueError, label):
                self.parse(code, altered, base, guards)

    def test_unknown_compact_flags_and_padding_rejected_even_with_updated_digest(self):
        base, code, data, guards = self.fixture()
        for offset in (0x40A, 0x40B):
            altered = bytearray(data)
            altered[offset] = 2
            changed = {**guards, 'COMPACT': ((base + 0x400, sha(altered[0x400:0x40C])), guards['COMPACT'][1])}
            with self.subTest(offset=offset), self.assertRaisesRegex(ValueError, 'compact descriptor flags'):
                self.parse(code, altered, base, changed)

    def test_load_preserves_old_sources_deduplicates_and_retains_selected_frame(self):
        base, code, data, guards = self.fixture()
        rom = b'synthetic reference'
        layout = dict(normalized_sha1=[sha(rom)], game_start=0, game_end=len(rom),
                      game_vram=0x1000, game_data_vram=base)
        entries = [SimpleNamespace(index=i, data=bytes(512)) for i in range(42, 47)]
        with ExitStack() as stack:
            stack.enter_context(patch.multiple(effects, **guards))
            stack.enter_context(patch.object(effects.cpu, 'SIZE_TABLE', base + 0x600))
            stack.enter_context(patch.object(effects.h, 'resolve_rom', return_value=(None, layout)))
            stack.enter_context(patch.object(effects.h, 'parse_game_archive', return_value=SimpleNamespace(code=code, data=data)))
            result = effects.load(Path('/synthetic'), rom, entries, {42})
            self.assertEqual(list(result), [44, 43, 45, 46])
            self.assertEqual(result[43]['consumer']['selected_frame'], 1)
            self.assertEqual(result[44]['consumer']['descriptor']['kind'], 'pointer')
            self.assertEqual(result[46]['consumer']['descriptor']['flags'], 1)
            self.assertEqual(result[46]['consumer']['descriptor']['resources'], [46, 44])
            self.assertEqual(result[43]['consumer']['descriptor']['resources'], [42, 43])
            with patch.object(effects.cpu, 'reversible', return_value=False):
                self.assertEqual(effects.load(Path('/synthetic'), rom, entries), {})
            with self.assertRaisesRegex(ValueError, 'reference ROM changed'):
                effects.load(Path('/synthetic'), b'changed', entries)

    def test_load_rejects_payload_tails_and_flagged_input_descriptors(self):
        base, code, data, guards = self.fixture()
        rom = b'synthetic reference'
        records = self.parse(code, data, base, guards)
        records[0]['flags'] = 1
        records[1]['flags'] = 1
        layout = dict(normalized_sha1=[sha(rom)], game_start=0, game_end=len(rom),
                      game_vram=0x1000, game_data_vram=base)
        entries = [SimpleNamespace(index=44, data=bytes(512)), SimpleNamespace(index=43, data=bytes(513))]
        with patch.object(effects.h, 'resolve_rom', return_value=(None, layout)), \
                patch.object(effects.h, 'parse_game_archive', return_value=SimpleNamespace(code=code, data=data)), \
                patch.object(effects, 'verified_descriptors', return_value=records[:3]):
            self.assertEqual(effects.load(Path('/synthetic'), rom, entries), {})
