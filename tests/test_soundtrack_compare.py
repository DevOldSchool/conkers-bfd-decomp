from __future__ import annotations

import unittest

try:
    import numpy as np
    from scripts import soundtrack_compare as comparison
except ImportError:
    np = comparison = None


@unittest.skipIf(np is None, "optional audio comparison dependencies unavailable")
class SoundtrackComparisonTests(unittest.TestCase):
    def test_shifted_pattern_has_correct_alignment_and_bounded_score(self) -> None:
        source = np.random.default_rng(7).normal(size=(61, 80))
        reference = np.pad(source, ((0, 0), (17, 12)))
        windows = comparison.compare(source, reference)
        self.assertTrue(windows)
        for window in windows:
            self.assertAlmostEqual(window["score"], 1)
            self.assertAlmostEqual(window["reference_seconds"] - window["source_seconds"],
                                   17 * comparison.HOP, places=3)

    def test_silent_short_and_nonfinite_inputs_do_not_generate_identity_evidence(self) -> None:
        self.assertEqual(comparison.compare(np.zeros((61, 80)), np.zeros((61, 100))), [])
        self.assertEqual(comparison.compare(np.zeros((61, 2)), np.zeros((61, 100))), [])
        with self.assertRaisesRegex(ValueError, "finite"):
            comparison.compare(np.full((61, 80), np.nan), np.zeros((61, 100)))

class WaveformClockTests(unittest.TestCase):
    def test_observed_clock_restores_alignment_and_gain(self):
        import tempfile
        from pathlib import Path
        import soundfile as sf
        from scripts.soundtrack_compare import waveform_alignment
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            rng = np.random.default_rng(17)
            source = rng.normal(0, 0.15, 24000)
            sf.write(root / 'source.wav', source, 12000, subtype='FLOAT')
            # The same samples played at the reference hardware clock, delayed
            # by exactly one second and scaled, should recover both values.
            reference = np.pad(source * 0.4, (11000, 11000))
            sf.write(root / 'reference.wav', reference, 11000, subtype='FLOAT')
            corrected = waveform_alignment(root / 'source.wav', root / 'reference.wav', 1, 11000)
            wrong = waveform_alignment(root / 'source.wav', root / 'reference.wav', 1)
            self.assertGreater(corrected['correlation'], 0.99)
            self.assertAlmostEqual(corrected['reference_seconds'], 1.0, places=3)
            self.assertAlmostEqual(corrected['least_squares_gain'], 0.4, places=3)
            self.assertLess(wrong['correlation'], 0.1)
