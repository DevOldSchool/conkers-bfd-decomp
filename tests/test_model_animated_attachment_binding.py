import hashlib
import struct
import unittest
from unittest.mock import patch

from scripts import model_attachment_texture_bindings as bindings


class AnimatedAttachmentBindingTests(unittest.TestCase):
    code_base = 0x15000000
    data_base = 0x80082B20

    def source(self):
        code, data = bytearray(0x110000), bytearray(0x20000)
        for address, raw in ((0x80086D8C, struct.pack('>IB3x', 0x8009D2F0, 1)),
                             (0x8009D2F0, bytes.fromhex('99120f02000016000000000000000000')),
                             (0x800841FC, struct.pack('>I', 0x150337E4)),
                             (0x800902FC, struct.pack('>2I', 1545, 1546))):
            data[address-self.data_base:address-self.data_base+len(raw)] = raw
        return code, data

    def context(self, code, data, original=None):
        original = code if original is None else original
        pins = [(a, n, hashlib.sha1(original[a-self.code_base:a-self.code_base+n]).hexdigest())
                for a, n, _ in bindings.ANIMATED_CONSUMERS]
        with patch.object(bindings, 'ANIMATED_CONSUMERS', pins):
            return bindings.animated_action_binding(code, self.code_base, data, self.data_base)

    def test_kind_two_action_retains_both_direct_frames(self):
        context = self.context(*self.source())
        self.assertEqual((9, 153, 0), tuple(context[k] for k in ('bank', 'entry', 'segment')))
        state = context['texture_binding']
        self.assertEqual('direct-pixel-segments', state['kind'])
        self.assertEqual(22, state['preview_state']['descriptor_0x17'])
        self.assertEqual([1545, 1546], state['bindings']['6']['flats'])
        self.assertEqual([32, 32, 0, 3], state['bindings']['6']['image_layout'])
        self.assertNotIn('segment_8_bases', context)

    def test_changed_action_dispatch_and_frame_table_are_rejected(self):
        for address, size in ((0x80086D8C, 8), (0x8009D2F0, 16),
                              (0x800841FC, 4), (0x800902FC, 8)):
            for offset in range(size):
                code, data = self.source()
                data[address-self.data_base+offset] ^= 1
                with self.subTest(address=hex(address), offset=offset), self.assertRaises(ValueError):
                    self.context(code, data)

    def test_changed_loader_update_and_renderer_spans_are_rejected(self):
        original, data = self.source()
        for address, size, _ in bindings.ANIMATED_CONSUMERS:
            code = bytearray(original)
            code[address-self.code_base+size-1] ^= 1
            with self.subTest(address=hex(address)), self.assertRaises(ValueError):
                self.context(code, data, original)
