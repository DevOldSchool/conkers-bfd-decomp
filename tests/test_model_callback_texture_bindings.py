import hashlib
import struct
import unittest
from unittest.mock import patch

from scripts import model_callback_texture_bindings as bindings


class CallbackTextureBindingTests(unittest.TestCase):
    code_base = 0x15000000
    data_base = 0x80082B20

    def source(self):
        code, data = bytearray(0x1D0000), bytearray(0x22000)

        def put(address, raw):
            target, base = (code, self.code_base) if address < 0x80000000 else (data, self.data_base)
            target[address - base:address - base + len(raw)] = raw

        for pc, word in bindings.GUARDS:
            put(pc, struct.pack('>I', word))
        for _, pairs in bindings.SIGHT_SELECTORS:
            for pcs, selectors in zip(pairs, ((135, 139), (136, 140)) if _ == 55 else ((137, 141), (138, 142))):
                for pc, selector in zip(pcs, selectors):
                    put(pc, struct.pack('>I', 0x24080000 | selector))
        put(0x800899A8, struct.pack('>2I', 0x15133EB8, 0x15133FD8))
        put(0x80089A24, struct.pack('>I', 0x800A3C94))
        put(0x800A3F18, struct.pack('>I', 8))
        put(0x800A3C94, struct.pack('>8I', 2, 3, 48, 146, 146, 145, 49, 49))
        put(0x800A4258, struct.pack('>4H', 131, 129, 130, 132))
        for selector, entry in ((145, 269), (146, 270), (55, 304), (56, 305)):
            put(bindings.objects.MODEL_TABLE + selector * 4, struct.pack('>I', entry))
        for selector in (*range(129, 133), *range(135, 143)):
            pointer = 0x80090A3C + (selector - 129) * 4
            put(0x80090B60 + selector * 12,
                struct.pack('>IBBHHBB', pointer, 1, 0, 32, 32 if selector < 135 else 64, 2, 1))
            put(pointer, struct.pack('>I', 1000 + selector))
        return code, data

    def pins(self, raw, base, spans):
        return tuple((a, n, hashlib.sha1(raw[a-base:a-base+n]).hexdigest()) for a, n, _ in spans)

    def contexts(self, code, data, source=None):
        original_code, original_data = source or (code, data)
        with patch.object(bindings, 'CONSUMERS', self.pins(original_code, self.code_base, bindings.CONSUMERS)), \
             patch.object(bindings, 'DATA_SPANS', self.pins(original_data, self.data_base, bindings.DATA_SPANS)):
            return bindings.material_context(code, self.code_base, data, self.data_base)

    def test_only_reviewed_models_and_correlated_alternatives(self):
        result = self.contexts(*self.source())
        self.assertEqual([269, 270, 304, 305], [r['entry'] for r in result['models']])
        fragment, _, sight, sight2 = [r['texture_binding'] for r in result['models']]
        self.assertEqual([1131, 1129, 1130, 1132], fragment['bindings']['6']['flats'])
        self.assertEqual([1135, 1139], sight['bindings']['4']['flats'])
        self.assertEqual([1136, 1140], sight['bindings']['6']['flats'])
        self.assertEqual([1138, 1142], sight2['bindings']['6']['flats'])
        self.assertEqual(0, sight['selected_variant'])
        self.assertEqual([True, False], [v['caller_arg_0x14_nonzero'] for v in sight['selector_variants']])
        self.assertEqual([], result['capture_inputs'])
        for row in result['models']:
            self.assertNotIn('8', row['texture_binding']['bindings'])
            self.assertIn('not a sampled gameplay state', row['texture_binding']['preview_policy'])

    def test_changed_consumer_and_data_spans_rejected(self):
        code, data = self.source()
        for spans, raw, base in ((bindings.CONSUMERS, code, self.code_base),
                                 (bindings.DATA_SPANS, data, self.data_base)):
            for address, size, _ in spans:
                changed = bytearray(raw)
                changed[address-base+size-1] ^= 1
                with self.subTest(address=hex(address)), self.assertRaises(ValueError):
                    self.contexts(changed if base == self.code_base else code,
                                  changed if base == self.data_base else data, (code, data))

    def test_dispatch_array_and_copy_guard_rejected_even_with_rehashed_fixture(self):
        for address in (0x800899AB, 0x80089A27, 0x800A3F1B, 0x151C9423):
            code, data = self.source()
            target, base = (code, self.code_base) if address < 0x80000000 else (data, self.data_base)
            target[address-base] ^= 1
            with self.subTest(address=hex(address)), self.assertRaises(ValueError):
                self.contexts(code, data)

    def test_descriptor_pointer_cannot_escape_checked_flat_words(self):
        code, data = self.source()
        struct.pack_into('>I', data, 0x80091184-self.data_base, 0x80090A4C)
        with self.assertRaisesRegex(ValueError, 'flat pointer'):
            self.contexts(code, data)

    def test_descriptor_layout_and_selector_bounds_rejected(self):
        for field in (4, 5, 6, 8, 10, 11):
            code, data = self.source()
            data[0x80091184-self.data_base+field] ^= 1
            with self.subTest(field=field), self.assertRaises(ValueError):
                self.contexts(code, data)
        code, data = self.source()
        struct.pack_into('>H', data, 0x800A4258-self.data_base, 134)
        with self.assertRaisesRegex(ValueError, 'descriptor outside'):
            self.contexts(code, data)

    def test_missing_regions_rejected(self):
        with self.assertRaises(ValueError):
            bindings.material_context(b'', self.code_base, b'', self.data_base)
