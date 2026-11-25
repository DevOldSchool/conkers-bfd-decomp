from pathlib import Path
import json
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / 'scripts'))
import objdiff_data_targets as targets


class ReferenceExpressionTests(unittest.TestCase):
    row = '/* 0000 80000000 15000004 */ .word func_15000000 + 0x4'
    original = bytes.fromhex('15000004')
    symbols = {'func_15000000': (0x15000000, 8)}

    def test_checked_interior_destination_defines_function_start(self):
        self.assertEqual(targets.reference_definitions(
            self.row, self.original, code_symbols=self.symbols),
            {'func_15000000': 0x15000000})

    def test_original_bytes_and_loaded_coordinate_are_required(self):
        for text, raw in ((self.row, bytes(4)),
                          (self.row.replace('80000000', '80000004'), self.original)):
            with self.subTest(text=text, raw=raw), self.assertRaisesRegex(ValueError, 'original ROM'):
                targets.reference_definitions(text, raw, code_symbols=self.symbols)

    def test_function_extent_and_alignment_are_required(self):
        for span in ((0x15000004, 8), (0x15000000, 4), (0x15000001, 8),
                     (0x15000000, 0), (0x15000000, 6)):
            with self.subTest(span=span), self.assertRaisesRegex(ValueError, 'function extent'):
                targets.reference_definitions(self.row, self.original,
                                              code_symbols={'func_15000000': span})
        with self.assertRaisesRegex(ValueError, 'function extent'):
            targets.reference_definitions(
                self.row.replace('15000004', '15000002').replace('+ 0x4', '+ 0x2'),
                bytes.fromhex('15000002'), code_symbols=self.symbols)

    def test_unknown_and_unsupported_expressions_stay_unresolved(self):
        self.assertEqual(targets.reference_definitions(self.row, self.original), {})
        for expression in (' - 0x4', ' + 4', ' + 0x4 + 0x0', ' * 0x4'):
            with self.subTest(expression=expression):
                self.assertEqual(targets.reference_definitions(
                    self.row.replace(' + 0x4', expression), self.original,
                    code_symbols=self.symbols), {})

    def test_known_bare_function_must_also_match_its_registered_start(self):
        with self.assertRaisesRegex(ValueError, 'function extent'):
            targets.reference_definitions(self.row.replace(' + 0x4', ''), self.original,
                                          code_symbols=self.symbols)
        self.assertEqual(targets.reference_definitions(
            self.row.replace('15000004', '15000000').replace(' + 0x4', ''),
            bytes.fromhex('15000000'), code_symbols=self.symbols),
            {'func_15000000': 0x15000000})

    def test_repeated_interior_offsets_share_one_checked_anchor(self):
        text = (self.row + '\n/* 0004 80000004 15000000 */ .word func_15000000 + 0x0')
        self.assertEqual(targets.reference_definitions(
            text, self.original + bytes.fromhex('15000000'), code_symbols=self.symbols),
            {'func_15000000': 0x15000000})

    def registry(self, root, entries):
        (root / 'progress').mkdir(exist_ok=True)
        (root / 'progress/functions.json').write_text(json.dumps({'functions': entries}))
        (root / 'progress/source_units.json').write_text(json.dumps({'source_units': []}))

    def entry(self, *, address='0x15000000', size=8, overlay='game', region='us'):
        return {'symbol': 'func_15000000', 'overlay': overlay,
                'regions': {region: {'vram': address, 'size_bytes': size}}}

    def test_registered_spans_use_us_game_and_full_recorded_size(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            entries = [self.entry(), {**self.entry(overlay='main'), 'symbol': 'main_only'},
                       {**self.entry(region='eu'), 'symbol': 'eu_only'}]
            self.registry(root, entries)
            self.assertEqual(targets.registered_game_function_symbols(
                root, code_start=0x15000000, code_size=8), self.symbols)

    def test_registered_spans_cannot_escape_original_code(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for address, size in (('0x14FFFFFC', 8), ('0x15000004', 8),
                                  ('0x15000002', 4), ('0x15000000', 0),
                                  ('0x15000000', 6)):
                self.registry(root, [self.entry(address=address, size=size)])
                with self.subTest(address=address, size=size), self.assertRaisesRegex(ValueError, 'code context'):
                    targets.registered_game_function_symbols(root, code_start=0x15000000, code_size=8)


if __name__ == '__main__':
    unittest.main()
