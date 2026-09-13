import copy
import unittest
from scripts import model_object_texture_bindings as bindings


class ObjectTextureBindingTests(unittest.TestCase):
    def placements(self, update=37, model=15):
        return {'scenes': [{'bank_index': 11, 'scene_index': 7, 'records': [{
            'dispatch_kind': 1, 'dispatch_index': model, 'model_source': [4, 7, model],
            'model_resolution_status': 'resolved-bank-04-segment',
            'bytes_3c_3f': '00000000', 'word_14': hex(update), 'index': 9, 'sha1': 'source'}]}]}

    def test_stationary_variants_and_loader_selector_are_distinct(self):
        proof = bindings.placement_bindings(self.placements(), (1682, 1683))[(4, 7, 15)]
        self.assertEqual([705, 448], proof['bindings']['4']['flats'])
        self.assertEqual([0, 3], proof['selector']['stationary_values'])
        self.assertEqual((4, 0), (proof['selector']['loader_value'], proof['selector']['selected_value']))
        self.assertIn('not a sampled gameplay state', proof['preview_policy'])

    def test_pair_table_is_scoped_to_model_twelve(self):
        proof = bindings.placement_bindings(self.placements(24, 12), (1682, 1683))[(4, 7, 12)]
        self.assertEqual([1682], proof['bindings']['4']['flats'])
        self.assertEqual([1683], proof['bindings']['6']['flats'])
        self.assertEqual(7, proof['bindings']['6']['palette_segment'])
        self.assertEqual({}, bindings.placement_bindings(self.placements(24, 13), (1682, 1683)))

    def test_unproven_paths_do_not_get_a_binding(self):
        for field, value in [('dispatch_kind', 0), ('word_14', '0x4e'),
                             ('bytes_3c_3f', '02000000'), ('model_resolution_status', 'unresolved'),
                             ('model_source', [4, 8, 15])]:
            placements = self.placements()
            placements['scenes'][0]['records'][0][field] = value
            with self.subTest(field=field):
                self.assertEqual({}, bindings.placement_bindings(placements, (1682, 1683)))
        placements = self.placements()
        placements['scenes'][0]['bank_index'] = 12
        self.assertEqual({}, bindings.placement_bindings(placements, (1682, 1683)))

    def test_all_supporting_placements_are_retained(self):
        placements = self.placements()
        second = copy.deepcopy(placements['scenes'][0]['records'][0])
        second.update(index=10, sha1='second')
        placements['scenes'][0]['records'].append(second)
        proof = bindings.placement_bindings(placements, (1682, 1683))[(4, 7, 15)]
        self.assertEqual(['source', 'second'], [p['sha1'] for p in proof['placements']])

    def test_rom_consumer_bytes_are_required(self):
        with self.assertRaisesRegex(ValueError, 'consumer'):
            bindings.binding_table(bytes(0x200000), 0x15000000, b'', 0x80082B20)
