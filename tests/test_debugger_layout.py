import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / 'scripts'))
import debugger_layout


class DebuggerLayoutTests(unittest.TestCase):
    def test_context_is_derived_and_layout_drift_is_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'config/reference').mkdir(parents=True)
            profile = {'segments': [{'name': 'debugger', 'start': 100, 'vram': 4096,
                                    'subsegments': [[100, 'asm'], [120, 'data']]}, [140]]}
            (root / 'config/reference/us.yaml').write_text(json.dumps(profile))
            spans = [{'input': '.data', 'start': 4116, 'end': 4124},
                     {'input': '.rodata', 'start': 4124, 'end': 4136}]
            with patch.object(debugger_layout.data_boundaries, 'debugger_source_mappings', return_value=spans):
                result = debugger_layout.load(root)
                self.assertEqual(result['origin'], 3996)
                self.assertEqual([(p['rom_start'], p['end'] - p['start']) for p in result['context']],
                                 [(120, 8), (128, 12)])
                for broken in [[spans[0]], [{**spans[0], 'end': 4123}, spans[1]],
                               [spans[0], {**spans[1], 'end': 4137}]]:
                    with self.subTest(broken=broken), patch.object(debugger_layout.data_boundaries,
                            'debugger_source_mappings', return_value=broken):
                        with self.assertRaises(ValueError):
                            debugger_layout.load(root)
