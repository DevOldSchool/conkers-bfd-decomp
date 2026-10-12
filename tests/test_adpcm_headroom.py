import unittest
from scripts import adpcm_codec, audio_assets, adpcm_headroom as codec

class HeadroomTests(unittest.TestCase):
    def test_preclamp_signal_reconstructs_clipped_frame_bits_from_float_wav(self):
        raw=bytes.fromhex('f0 7788887777888877 f0 8877778888777788')
        coefficients=[0]*16;plan=adpcm_codec.frame_plan(raw,coefficients,2,1)
        signal=codec.decode_headroom(raw,coefficients,2,1)
        self.assertTrue(any(abs(v)>32768 for v in signal))
        wav=codec.source_float_wav(signal,22050)
        self.assertEqual(codec.encode_headroom(codec.read_float_wav(wav,22050,32),plan),raw)
        self.assertEqual(tuple(max(-32768,min(32767,v)) for v in signal),audio_assets.decode_n64_vadpcm(raw,coefficients,2,1))
        canonical=adpcm_codec.encode_pcm(list(audio_assets.decode_n64_vadpcm(raw,coefficients,2,1)),plan)
        self.assertNotEqual(canonical,raw)

    def test_history_is_saturated_between_vectors_with_multiple_predictors(self):
        coefficients=[-10]*8+[1700]*8+[30]*8+[2000]*8+[0]*32
        raw=bytes.fromhex('d0 7788778877887788 d1 8877887788778877')
        plan=adpcm_codec.frame_plan(raw,coefficients,2,4)
        signal=codec.decode_headroom(raw,coefficients,2,4)
        self.assertEqual(codec.encode_headroom(signal,plan),raw)
        self.assertEqual(tuple(max(-32768,min(32767,v)) for v in signal),audio_assets.decode_n64_vadpcm(raw,coefficients,2,4))

    def test_signal_edits_change_bytes_or_fail_without_original_residual_input(self):
        raw=bytes.fromhex('10 0123456789abcdef');plan=adpcm_codec.frame_plan(raw,[0]*16,2,1)
        signal=codec.decode_headroom(raw,[0]*16,2,1);signal[0]=2
        self.assertNotEqual(codec.encode_headroom(signal,plan),raw)
        signal[0]=1
        with self.assertRaises(ValueError):codec.encode_headroom(signal,plan)
        for invalid in ([0]*15,[True]*16,[1.5]*16,[1<<23]*16):
            with self.assertRaises(ValueError):codec.encode_headroom(invalid,plan)
        with self.assertRaises(ValueError):codec.decode_headroom(bytes(8),[0]*16,2,1)

if __name__=='__main__':unittest.main()
