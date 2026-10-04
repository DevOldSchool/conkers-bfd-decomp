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
