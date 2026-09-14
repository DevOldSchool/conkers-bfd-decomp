import struct
import unittest
from unittest.mock import patch
from scripts import model_attachment_texture_bindings as bindings


class AttachmentTextureBindingTests(unittest.TestCase):
    base = 0x80082B20

    def source(self):
        data = bytearray(0x20000)
        def put(address, raw):
            data[address - self.base:address - self.base + len(raw)] = raw
        for action, address, raw in bindings.ACTIONS + bindings.DIRECT_ACTIONS:
            put(0x80086CC4 + (action - 1) * 8, struct.pack('>IB3x', address, 1))
            put(address, bytes.fromhex(raw))
        for index, function in bindings.UPDATERS.items():
            put(0x800841C0 + index * 4, struct.pack('>I', function))
        for address, flats in bindings.TEXTURES.values():
            put(address, struct.pack(f'>{len(flats)}I', *flats))
        put(0x80086D8C, struct.pack('>IB3x', 0x8009D2F0, 1))
        put(0x8009D2F0, bytes.fromhex('99120f02000016000000000000000000'))
        put(0x800841FC, struct.pack('>I', 0x150337E4))
        put(0x800902FC, struct.pack('>2I', 1545, 1546))
        for address, raw in bindings.INDEXED_ANIMATED_DATA:
            put(address, bytes.fromhex(raw))
        return data

    def test_only_reviewed_kind_one_records_get_contexts(self):
        contexts = bindings.action_bindings(self.source(), self.base)
        self.assertEqual([19, 25, 49], [row['entry'] for row in contexts])
        self.assertTrue(all(row['renderer'] == 'func_150311C4' for row in contexts))
        loop = contexts[1]['texture_binding']
        self.assertEqual([2644, 2645, 2646], loop['bindings']['6']['flats'])
        self.assertEqual([0, 1, 2, 2, 1, 0], loop['selector']['frame_indices'])
        self.assertEqual(174, contexts[2]['texture_binding']['selector']['excluded_parent_0x84'])
        self.assertIn('not a sampled gameplay state', contexts[2]['texture_binding']['preview_policy'])

    def test_mutated_model_kind_header_pointer_dispatch_and_flat_rejected(self):
        addresses = [0x8009CE90, 0x8009CE93, 0x80086D04, 0x80086D08,
                     0x800841C4, 0x800902B0, 0x800902C7, 0x8009028F]
        for address in addresses:
            data = self.source()
            data[address - self.base] ^= 1
            with self.subTest(address=hex(address)), self.assertRaises(ValueError):
                bindings.action_bindings(data, self.base)

    def test_missing_rom_regions_and_changed_consumers_rejected(self):
        with self.assertRaises(ValueError):
            bindings.action_bindings(b'', self.base)
        with self.assertRaisesRegex(ValueError, 'consumer'):
            bindings.material_context(bytes(0x200000), 0x15000000, self.source(), self.base)

    def test_direct_actions_require_no_updater_and_no_initializer(self):
        with patch.object(bindings, 'CONSUMERS', ()), patch.object(bindings, 'ANIMATED_CONSUMERS', ()), \
                patch.object(bindings, 'INDEXED_ANIMATED_CONSUMERS', ()):
            data = self.source()
            result = bindings.material_context(b'', 0, data, self.base)
            self.assertEqual([19, 25, 49, 121, 128, 153, 141, 147], [r['entry'] for r in result['models']])
            for row in result['models'][3:5]:
                self.assertIsNone(row['updater'])
                self.assertNotIn('texture_binding', row)
            for address in (0x800841C0, 0x8009D8C0, 0x8009D8F2, 0x80086CC4 + 47 * 8):
                changed = bytearray(data); changed[address - self.base] ^= 1
                with self.subTest(address=hex(address)), self.assertRaises(ValueError):
                    bindings.material_context(b'', 0, changed, self.base)
