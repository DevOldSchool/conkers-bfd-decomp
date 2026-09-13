import struct
import unittest
from unittest.mock import Mock
from scripts import model_constructor_analysis as analysis


class ConstructorAnalysisTests(unittest.TestCase):
    def test_calls_are_discovery_only_and_delayed_arguments_are_not_guessed(self):
        call = 0x0C000000 | ((0x1513264C >> 2) & 0x03FFFFFF)
        code = struct.pack('>6I', 0x27BDFFE0, call, 0x2404007B, 0x03E00008, 0x27BD0020, 0)
        rows = analysis.discover_calls(code, 0x15000000)
        self.assertEqual(1, len(rows))
        self.assertEqual('0x15000004', rows[0]['call_pc'])
        self.assertEqual('requires-consumer-review', rows[0]['status'])
        self.assertNotIn('model', rows[0])
        self.assertNotIn('selectors', rows[0])

    def test_missing_prologue_never_becomes_a_function_claim(self):
        code = struct.pack('>I', 0x0D44C993)
        rows = analysis.discover_calls(code, 0x15000000)
        self.assertEqual(1, len(rows))
        self.assertNotIn('candidate_start', rows[0])
        self.assertEqual([], analysis.discover_calls(b'', 0x15000000))

    def test_successful_texture_decode_does_not_grant_renderer_evidence(self):
        models = Mock()
        models.rom_render_state_preview_texture.return_value = (object(), 'decoded', {})
        row = analysis.diagnose_run(models, object(), {}, [], None)
        self.assertEqual('renderer-evidence-missing', row['blocker'])
        self.assertTrue(row['texture_consensus'])
        models.load_object_material_context.assert_not_called()
