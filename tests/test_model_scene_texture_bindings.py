import unittest
from scripts import model_scene_texture_bindings as scene


class SceneTextureBindingsTests(unittest.TestCase):
    def words(self, address, count):
        dispatch = {19: 0x1510BB6C, 20: 0x1510BB4C, 26: 0x1510BB5C, 51: 0x1510BB8C}
        if 0x800A2C2C <= address < 0x800A2CB8:
            return [dispatch[19 + (address - 0x800A2C2C) // 4]]
        if address in (0x80088810, 0x80088900):
            return [0x80090230, 0x80090244]
        return list(range(address, address + 4 * count, 4))

    def test_scene_selectors_preserve_phase_offsets_and_type_groups(self):
        contexts = {r['entry']: r for r in scene.decoded_contexts(self.words)}
        self.assertEqual({19, 20, 26, 51}, set(contexts))
        self.assertTrue(all(r['bank'] == 4 and r['segment'] == 0 for r in contexts.values()))
        bindings = lambda entry: contexts[entry]['scene_texture_state']['bindings']
        self.assertEqual([0, 3, 1, 4, 2, 0], [r['selected_index'] for r in bindings(51).values()])
        self.assertEqual(1, bindings(26)['3']['selected_index'])
        self.assertEqual('0x80090230', bindings(20)['5']['frame_array'])
        self.assertEqual('0x80090244', bindings(20)['6']['frame_array'])
        self.assertEqual(5, len(bindings(19)['2']['frames']))
        self.assertIn('not a sampled or initial', contexts[19]['scene_texture_state']['preview_policy'])

    def test_wrong_dispatch_and_truncated_rom_fail_closed(self):
        with self.assertRaisesRegex(ValueError, 'dispatch changed'):
            scene.decoded_contexts(lambda address, count: [0] * count)
        with self.assertRaisesRegex(ValueError, 'exceeds ROM region'):
            scene.scene_contexts(b'', 0x15000000, b'', 0x80000000)
        with self.assertRaisesRegex(ValueError, 'consumer changed'):
            scene.scene_contexts(bytes(0x200000), 0x15000000, bytes(0x100000), 0x80000000)
        with self.assertRaises(ValueError):
            scene.checked(b'0123', 100, 99, 1)


if __name__ == '__main__':
    unittest.main()
