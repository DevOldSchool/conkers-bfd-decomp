import copy
from types import SimpleNamespace
import unittest
from scripts import adpcm_layout as layout

class AdpcmLayoutTests(unittest.TestCase):
    def setUp(self):
        self.asset = SimpleNamespace(compressed=False, rom_start=100, rom_end=150, data=bytes(50))
        self.samples = [{'index':0,'kind':'adpcm','base':'0x2','stored_length':29,'runtime_payload_length':27},
                        {'index':1,'kind':'adpcm','base':'0x20','stored_length':18,'runtime_payload_length':18}]
        self.contract = {'format':'conker-adpcm-frames-v1','rom_sha1':layout.ROM_SHA1,
                         'sample_count':2,'ambiguous_frames':[{'sample':0,'frames':[1]}]}

    def test_complete_frames_preserve_ambiguous_frames_tails_and_gaps(self):
        rows = layout.partition(self.asset,self.samples,self.contract)
        self.assertEqual([(a,b) for a,b,_ in rows],[(100,102),(102,111),(111,120),(120,129),(129,132),(132,150)])
        self.assertEqual(sum(b-a for a,b,n in rows if '/raw/' not in n),36)
        self.assertEqual([n for _,_,n in rows if '/raw/' not in n], [layout.part_name(0,0),layout.part_name(0,2),layout.part_name(1,0)])

    def test_invalid_contract_duplicate_out_of_order_or_partial_frame_fails(self):
        for frames in ([1,1],[2,1],[-1],[3],[True],[]):
            changed=copy.deepcopy(self.contract);changed['ambiguous_frames'][0]['frames']=frames
            with self.subTest(frames=frames),self.assertRaises(ValueError):layout.partition(self.asset,self.samples,changed)
        for extra in ({'sample_count':True},{'rom_sha1':'wrong'},{'format':'raw-byte-copy'}):
            with self.assertRaises(ValueError):layout.partition(self.asset,self.samples,dict(self.contract,**extra))
        for length in (26,28,0):
            samples=copy.deepcopy(self.samples);samples[0]['runtime_payload_length']=length
            with self.assertRaises(ValueError):layout.partition(self.asset,samples,self.contract)

    def test_overlapping_samples_and_bad_selectors_fail(self):
        samples=copy.deepcopy(self.samples);samples[1]['base']='0x1E'
        with self.assertRaises(ValueError):layout.partition(self.asset,samples,self.contract)
        for sample,frame in ((True,0),(-1,0),(10000,0),(0,-1),(0,True)):
            with self.assertRaises(ValueError):layout.part_name(sample,frame)
