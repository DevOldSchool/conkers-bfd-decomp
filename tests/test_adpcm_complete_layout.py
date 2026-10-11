import copy
from types import SimpleNamespace
import unittest
from scripts import adpcm_layout as layout

class CompleteLayoutTests(unittest.TestCase):
    def setUp(self):
        self.asset=SimpleNamespace(compressed=False,rom_start=100,rom_end=124,data=b'x'*9+bytes(7)+b'y'*0+bytes(8))
        self.asset.data=b'x'*9+bytes(7)+b'y'*18+bytes(6);self.asset.rom_end=140
        self.rows=[{'index':0,'kind':'adpcm','base':'0x0','runtime_payload_length':9,'stored_length':10},
                   {'index':1,'kind':'adpcm','base':'0x10','runtime_payload_length':18,'stored_length':18}]
        self.contract={'format':'conker-adpcm-complete-samples-v2','rom_sha1':layout.ROM_SHA1,'sample_count':2,'float32_headroom_samples':[1]}

    def test_runtime_extents_determine_complete_two_and_eight_byte_alignment(self):
        rows=layout.complete_samples(self.asset,self.rows,self.contract)
        self.assertEqual([(r['rom_start'],r['rom_end'],r['zero_padding_bytes']) for r in rows],[(100,116,7),(116,140,6)])
        self.assertEqual([r['pcm_format'] for r in rows],['pcm16','float32-headroom'])

    def test_unknown_gaps_nonzero_padding_or_unreviewed_signal_selection_fail(self):
        for at in (9,15,34,39):
            asset=copy.deepcopy(self.asset);data=bytearray(asset.data);data[at]=1;asset.data=bytes(data)
            with self.assertRaises(ValueError):layout.complete_samples(asset,self.rows,self.contract)
        for field,value in [('base','0x18'),('stored_length',19),('runtime_payload_length',17)]:
            rows=copy.deepcopy(self.rows);rows[1][field]=value
            with self.assertRaises(ValueError):layout.complete_samples(self.asset,rows,self.contract)
        for values in ([1,1],[True],[2],[1,0]):
            contract=dict(self.contract,float32_headroom_samples=values)
            with self.assertRaises(ValueError):layout.complete_samples(self.asset,self.rows,contract)

if __name__=='__main__':unittest.main()
