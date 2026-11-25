"""Explicit glyph selectors must retain evidence and full-payload checks."""
from contextlib import ExitStack
import hashlib
from pathlib import Path
import struct
from types import SimpleNamespace
import unittest
from unittest.mock import patch

from scripts import texture_cpu_glyphs as glyphs


def sha(raw):
    return hashlib.sha1(raw).hexdigest()


class GlyphTextureTests(unittest.TestCase):
    def fixture(self):
        base = 0x80000000
        data = bytearray(0x800)
        code = b'whole native function including its final instruction'
        routes = ((0xA8, 0x1004, base + 0x200, (0,)),
                  (0xB2, 0x1008, base + 0x20C, (0, 1, 2, 3)))
        jump = [0] * 27
        jump[0xA8 - 0xA1], jump[0xB2 - 0xA1] = 0x1004, 0x1008
        jump_bytes = struct.pack('>27I', *jump)
        descriptors = (struct.pack('>IBBHHBB', base + 0x300, 0, 0, 16, 16, 0, 2)
                       + struct.pack('>IBBHHBB', base + 0x304, 3, 0, 16, 16, 0, 2))
        frames = struct.pack('>5I', 42, 43, 44, 45, 46)
        for offset, raw in ((0x100, jump_bytes), (0x200, descriptors),
                            (0x300, frames), (0x600, glyphs.cpu.SIZE_BYTES)):
            data[offset:offset + len(raw)] = raw
        guards = dict(CONSUMERS=((0x1000, len(code), sha(code)),),
                      JUMP_TABLE=base + 0x100, JUMP_COUNT=27, JUMP_SHA1=sha(jump_bytes),
                      ROUTES=routes, DESCRIPTORS_SHA1=sha(descriptors), FRAMES_SHA1=sha(frames))
        return base, code, data, guards

    def parse(self, code, data, base, guards):
        with patch.multiple(glyphs, **guards), patch.object(glyphs.cpu, 'SIZE_TABLE', base + 0x600):
            return glyphs.verified_records(code, 0x1000, data, base)

    def test_explicit_zero_count_and_fourth_frame_keep_original_counts(self):
        base, code, data, guards = self.fixture()
        records = self.parse(code, data, base, guards)
        self.assertEqual([r['stored_count'] for r in records], [0, 3])
        self.assertEqual([r['resources'] for r in records], [[42], [43, 44, 45, 46]])
        self.assertEqual(records[1]['frames'], [0, 1, 2, 3])
        self.assertIsNotNone(glyphs.storage_contract(records[0], bytes(512)))
        self.assertIsNotNone(glyphs.storage_contract(records[1], bytes(512)))
        # The new consumer does not relax the original generic count requirement.
        self.assertIsNone(glyphs.cpu.storage_contract(dict(
            count=0, flags=0, width=16, height=16, format=0, size=2), bytes(512)))

    def test_native_tail_jump_descriptor_and_fourth_word_mutations_fail_closed(self):
        base, code, data, guards = self.fixture()
        with self.assertRaisesRegex(ValueError, 'consumer'):
            self.parse(code[:-1] + b'!', data, base, guards)
        for offset, label in ((0x100 + 7 * 4, 'jump table'), (0x204, 'descriptors'),
                              (0x212, 'descriptors'), (0x313, 'selected frame words'),
                              (0x600, 'transfer-size')):
            changed = bytearray(data)
            changed[offset] ^= 1
            with self.subTest(offset=offset), self.assertRaisesRegex(ValueError, label):
                self.parse(code, changed, base, guards)

    def test_padding_scalar_pointer_and_selector_domains_are_rejected(self):
        base, code, data, guards = self.fixture()
        for offset, value in ((0x205, 1), (0x200, 0)):
            changed = bytearray(data)
            changed[offset] = value
            updated = {**guards, 'DESCRIPTORS_SHA1': sha(changed[0x200:0x218])}
            with self.subTest(offset=offset), self.assertRaisesRegex(ValueError, 'pointer or padding'):
                self.parse(code, changed, base, updated)
        for route in ((0xA7, 0x1004, base + 0x200, (0,)),
                      (0xA8, 0x1008, base + 0x200, (0,)),
                      (0xA8, 0x1004, base + 0x200, (0, 2))):
            updated = {**guards, 'ROUTES': (route, guards['ROUTES'][1])}
            with self.subTest(route=route), self.assertRaisesRegex(ValueError, 'selector contract'):
                self.parse(code, data, base, updated)

    def test_storage_rejects_tails_truncation_invalid_dimensions_and_padding(self):
        base, code, data, guards = self.fixture()
        row = self.parse(code, data, base, guards)[1]
        for payload in (bytes(511), bytes(513)):
            self.assertIsNone(glyphs.storage_contract(row, payload))
        for change in ({'width': 15}, {'format': 7}, {'padding': 1}, {'frames': []}, {'frames': [0, 2]}):
            self.assertIsNone(glyphs.storage_contract({**row, **change}, bytes(512)))

    def test_load_preserves_exclusions_frame_identity_and_inverse_requirement(self):
        base, code, data, guards = self.fixture()
        rom = b'synthetic reference'
        layout = dict(normalized_sha1=[sha(rom)], game_start=0, game_end=len(rom),
                      game_vram=0x1000, game_data_vram=base)
        entries = [SimpleNamespace(index=i, data=bytes(512)) for i in range(42, 47)]
        with ExitStack() as stack:
            stack.enter_context(patch.multiple(glyphs, **guards))
            stack.enter_context(patch.object(glyphs.cpu, 'SIZE_TABLE', base + 0x600))
            stack.enter_context(patch.object(glyphs.h, 'resolve_rom', return_value=(None, layout)))
            stack.enter_context(patch.object(glyphs.h, 'parse_game_archive', return_value=SimpleNamespace(code=code, data=data)))
            result = glyphs.load(Path('/synthetic'), rom, entries, {43})
            self.assertEqual(list(result), [42, 44, 45, 46])
            self.assertEqual(result[42]['consumer']['glyph']['stored_count'], 0)
            self.assertEqual(result[46]['consumer']['selected_frame'], 3)
            self.assertEqual(result[46]['consumer']['glyph']['stored_count'], 3)
            self.assertEqual(result[46]['family'], 'cpu-glyph-selector')
            with patch.object(glyphs.cpu, 'reversible', return_value=False):
                self.assertEqual(glyphs.load(Path('/synthetic'), rom, entries), {})
            with self.assertRaisesRegex(ValueError, 'reference ROM'):
                glyphs.load(Path('/synthetic'), b'changed', entries)
            self.assertEqual(glyphs.load(Path('/synthetic'), rom,
                                        [SimpleNamespace(index=42, data=bytes(513))]), {})
