import copy
import io
import unittest
import wave
from scripts import adpcm_codec as codec
from scripts import audio_assets

class AdpcmCodecTests(unittest.TestCase):
    def plan(self, frames=1, scale=0):
        return {'format':'conker-adpcm-pcm16-plan-v1','order':2,'predictor_count':1,
                'coefficients':[0]*16,'frames':[[scale,0] for _ in range(frames)]}

    def test_pcm_fields_encode_fresh_signed_nibbles_and_wav_edits_change_bytes(self):
        samples=list(range(-8,8));plan=self.plan()
        self.assertEqual(codec.encode_pcm(samples,plan),bytes.fromhex('0089abcdef01234567'))
        source=codec.source_wav(samples,22050)
        self.assertEqual(codec.read_wav(source,22050,16),samples)
        changed=samples.copy();changed[0]=-7
        self.assertNotEqual(codec.encode_pcm(codec.read_wav(codec.source_wav(changed,22050),22050,16),plan),codec.encode_pcm(samples,plan))

    def test_history_and_predictor_parameters_roundtrip_across_frames(self):
        coefficients=[-10]*8+[100]*8+[30]*8+[-20]*8+[0]*32
        raw=bytes.fromhex('20 89abcdef01234567 31 0102030405060700')
        pcm=audio_assets.decode_n64_vadpcm(raw,coefficients,2,4)
        plan=codec.frame_plan(raw,coefficients,2,4)
        self.assertEqual(plan['frames'],[[2,0],[3,1]])
        self.assertEqual(codec.encode_pcm(pcm,plan),raw)

    def test_clipped_vectors_choose_first_solution_without_enumerating_every_solution(self):
        result=codec.encode_vector([32767]*8,[32767,32767],[32767]*16,0,2,1)
        self.assertEqual(result,[-8]*8)
        with self.assertRaisesRegex(ValueError,'no residual solution'):
            codec.encode_vector([0]*8,[32767,32767],[32767]*16,0,2,1)

    def test_pcm_that_cannot_fit_selected_scale_fails(self):
        samples=[0]*16;samples[0]=1
        with self.assertRaisesRegex(ValueError,'no residual solution'):
            codec.encode_pcm(samples,self.plan(scale=1))

    def test_schema_and_native_ranges_reject_opaque_streams_and_bad_parameters(self):
        plan=self.plan();invalid=[dict(plan,original_residual_bytes='00'),dict(plan,order=True),
                                dict(plan,order=1),dict(plan,predictor_count=2),dict(plan,frames=[])]
        for frames in ([[16,0]],[[-1,0]],[[0,1]],[[True,0]],[[0,'0']]):invalid.append(dict(plan,frames=frames))
        for coefficients in ([0]*15,[32768]*16,[False]*16):invalid.append(dict(plan,coefficients=coefficients))
        for changed in invalid:
            with self.subTest(plan=changed),self.assertRaises(ValueError):codec.encode_pcm([0]*16,changed)
        for samples in ([0]*15,[32768]*16,[True]*16):
            with self.assertRaises(ValueError):codec.encode_pcm(samples,plan)
        for raw in (b'',bytes(8),bytes(10)):
            with self.assertRaises(ValueError):codec.frame_plan(raw,[0]*16,2,1)

    def test_source_wav_requires_mono_pcm16_rate_and_frame_count(self):
        data=codec.source_wav([0]*16,22050)
        for rate,frames in ((22051,16),(22050,15)):
            with self.assertRaises(ValueError):codec.read_wav(data,rate,frames)
        for invalid in (data[:-1],b'bad wav'):
            with self.assertRaises(ValueError):codec.read_wav(invalid,22050,16)
        for channels,width in ((2,2),(1,1)):
            out=io.BytesIO()
            with wave.open(out,'wb') as file:
                file.setnchannels(channels);file.setsampwidth(width);file.setframerate(22050);file.writeframes(bytes(16*channels*width))
            with self.assertRaises(ValueError):codec.read_wav(out.getvalue(),22050,16)
