import struct
import unittest
from scripts import adpcm_headroom as wav

class FloatWavTests(unittest.TestCase):
    def test_signal_above_signed16_range_is_exact_in_normalized_float_pcm(self):
        values=[-35749,-32768,-1,0,1,32767,35987]
        raw=wav.source_float_wav(values,22050)
        self.assertEqual(wav.read_float_wav(raw,22050,len(values)),values)
        self.assertEqual(struct.unpack_from('<H',raw,20)[0],3)

    def test_wrong_format_counts_and_nonfinite_or_fractional_signal_are_rejected(self):
        raw=wav.source_float_wav([0],22050)
        cases=[raw[:-1],b'RIFF'+bytes(20)]
        for at,fmt,value in [(20,'<H',1),(22,'<H',2),(24,'<I',44100),(46,'<I',2),(58,'<f',float('nan')),(58,'<f',float('inf')),(58,'<f',1/65536)]:
            changed=bytearray(raw);struct.pack_into(fmt,changed,at,value);cases.append(bytes(changed))
        for data in cases:
            with self.subTest(data=data),self.assertRaises(ValueError):wav.read_float_wav(data,22050,1)
        with self.assertRaises(ValueError):wav.read_float_wav(raw,22050,2)

    def test_pcm16_and_headroom_inputs_do_not_accept_silent_float_quantization(self):
        for values in ([True],[1.5],[1<<23],[-(1<<23)-1]):
            with self.assertRaises(ValueError):wav.source_float_wav(values,22050)
        for rate in (True,0,-1,1<<32):
            with self.assertRaises(ValueError):wav.source_float_wav([0],rate)

if __name__=='__main__':unittest.main()
