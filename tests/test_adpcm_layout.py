from types import SimpleNamespace
import unittest
from scripts import adpcm_layout as layout


class AdpcmLayoutTests(unittest.TestCase):
    def test_retired_frame_contract_is_rejected(self):
        asset = SimpleNamespace(compressed=False, rom_start=0, rom_end=16, data=bytes(16))
        contract = {'format': 'conker-adpcm-frames-v1', 'rom_sha1': layout.ROM_SHA1,
                    'sample_count': 0, 'ambiguous_frames': []}
        with self.assertRaisesRegex(ValueError, 'complete ADPCM sample contract'):
            layout.partition(asset, [], contract)

    def test_only_complete_sample_names_are_valid(self):
        self.assertEqual(layout.part_name(123, 0), 'audio/bank17/samples/0123/00000000')
        for sample, frame in ((True, 0), (-1, 0), (10000, 0), (0, -1), (0, True), (0, 2)):
            with self.subTest(sample=sample, frame=frame), self.assertRaises(ValueError):
                layout.part_name(sample, frame)
