import hashlib
import unittest
from unittest.mock import patch
from scripts import model_attachment_texture_bindings as bindings


class IndexedAnimatedBindingsTests(unittest.TestCase):
    code_base = 0x15000000
    data_base = 0x80082B20

    def source(self):
        code, data = bytearray(0x90000), bytearray(0x20000)
        for address, text in bindings.INDEXED_ANIMATED_DATA:
            raw = bytes.fromhex(text)
            data[address-self.data_base:address-self.data_base+len(raw)] = raw
        return code, data

    def context(self, code, data, original=None):
        original = code if original is None else original
        pins = [(a, n, hashlib.sha1(original[a-self.code_base:a-self.code_base+n]).hexdigest())
                for a, n, _ in bindings.INDEXED_ANIMATED_CONSUMERS]
        with patch.object(bindings, 'INDEXED_ANIMATED_CONSUMERS', pins):
            return bindings.indexed_animated_action_bindings(code, self.code_base, data, self.data_base)

    def test_explicit_states_retain_both_inline_palette_alternatives(self):
        contexts = self.context(*self.source())
        self.assertEqual([141, 147], [row['entry'] for row in contexts])
        states = [row['texture_binding'] for row in contexts]
        self.assertEqual([[7181, 7182], [3791, 3792]], [s['bindings']['6']['flats'] for s in states])
        self.assertEqual(0, states[0]['selector']['progress_0x800D2148'])
        self.assertEqual(90, states[1]['selector']['parent_0x04'])
        for context, state in zip(contexts, states):
            self.assertEqual('attachment-payload', state['kind'])
            self.assertEqual(0, state['selector']['parent_0x2D0'])
            self.assertEqual(0, state['bindings']['6']['selected_index'])
            self.assertNotIn('segment_8_bases', context)

    def test_each_action_and_indirect_target_byte_is_guarded(self):
        for address, raw in bindings.INDEXED_ANIMATED_DATA:
            for offset in range(len(bytes.fromhex(raw))):
                code, data = self.source()
                data[address-self.data_base+offset] ^= 1
                with self.subTest(address=hex(address), offset=offset), self.assertRaises(ValueError):
                    self.context(code, data)

    def test_changed_initializer_helper_and_updater_are_rejected(self):
        original, data = self.source()
        for address, size, _ in bindings.INDEXED_ANIMATED_CONSUMERS:
            code = bytearray(original)
            code[address-self.code_base+size-1] ^= 1
            with self.subTest(address=hex(address)), self.assertRaises(ValueError):
                self.context(code, data, original)
