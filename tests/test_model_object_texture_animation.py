import copy
import unittest
from scripts import model_object_texture_animation as animation


class ObjectTextureAnimationTests(unittest.TestCase):
    def placements(self):
        return {'scenes': [{'bank_index': 11, 'scene_index': 23, 'records': [{
            'dispatch_kind': 1, 'dispatch_index': 9, 'model_source': [4, 23, 9],
            'model_resolution_status': 'resolved-bank-04-segment',
            'bytes_3c_3f': '00000000', 'word_14': '0x00000019', 'index': 2, 'sha1': 'source'}]}]}

    def rows(self):
        return [{'scene': 23, 'model': model, 'address': str(model), 'frames': [model + 1],
                 'frame_period': 3, 'ping_pong': False} for model in (9, 255)]

    def test_ordered_specific_and_wildcard_selection(self):
        placements = self.placements()
        proof = animation.placement_animations(placements, self.rows())[(4, 23, 9)]
        self.assertEqual([10], proof['frames'])
        self.assertEqual(0, proof['preview_frame'])
        self.assertIn('not a sampled gameplay time', proof['preview_policy'])
        placements['scenes'][0]['records'][0]['dispatch_index'] = 10
        self.assertEqual([256], animation.placement_animations(placements, self.rows())[(4, 23, 9)]['frames'])

    def test_unproven_placement_paths_do_not_inherit_animation(self):
        for field, value in [('dispatch_kind', 0), ('word_14', '0x4e'),
                             ('bytes_3c_3f', '02000000'), ('model_resolution_status', 'unresolved')]:
            placements = self.placements()
            placements['scenes'][0]['records'][0][field] = value
            with self.subTest(field=field):
                self.assertEqual({}, animation.placement_animations(placements, self.rows()))
        placements = self.placements()
        placements['scenes'][0]['scene_index'] = 22
        self.assertEqual({}, animation.placement_animations(placements, self.rows()))

    def test_regions_fail_closed(self):
        for address, size in ((9, 1), (12, 2)):
            with self.assertRaises(ValueError):
                animation.checked(b'abc', 10, address, size)

    def test_consumer_bytes_are_required(self):
        with self.assertRaisesRegex(ValueError, 'consumer changed'):
            animation.animation_table(bytes(0x200000), 0x15000000, b'', 0x80082B20)
