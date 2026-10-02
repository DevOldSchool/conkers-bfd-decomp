from __future__ import annotations

import json
import sys
import tempfile
from pathlib import Path
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import objdiff_report as report


class CoveragePlanTests(unittest.TestCase):
    def test_unassigned_gaps_remain_in_denominator(self):
        plan = report.partition(0, 40, [{'start': 8, 'end': 20, 'kind': 'source'}], [4, 24, 32])
        self.assertEqual([(u['start'],u['end']) for u in plan],
                         [(0,4),(4,8),(8,20),(20,24),(24,32),(32,40)])
        self.assertEqual(sum(u['end']-u['start'] for u in plan), 40)

    def test_overlap_cannot_double_count_source_and_sdk(self):
        with self.assertRaisesRegex(ValueError, 'overlapping'):
            report.partition(0, 40, [{'start':0,'end':24}, {'start':20,'end':40}], [])

    def test_out_of_range_unit_is_rejected(self):
        with self.assertRaises(ValueError):
            report.partition(0, 40, [{'start':8,'end':44}], [])

    def test_entire_unknown_range_is_kept(self):
        self.assertEqual(report.partition(8, 24, [], []), [{'start':8,'end':24,'kind':'unassigned'}])

    def test_repository_plan_covers_all_cpu_ranges(self):
        plan = report.plan()
        ranges = report.state.validate_code_ranges(report.state.load_json(report.state.OVERLAYS_FILE))
        for overlay in ('main', 'game', 'debugger'):
            units = [u for u in plan if u['overlay']==overlay]
            start,end = ranges[overlay]['us']
            self.assertEqual(units[0]['start'], start)
            self.assertEqual(units[-1]['end'], end)
            self.assertTrue(all(a['end']==b['start'] for a,b in zip(units,units[1:])))
            self.assertEqual(sum(u['end']-u['start'] for u in units), end-start)


    def test_debugger_scaffolds_have_no_implicit_source_ownership(self):
        load_json = report.state.load_json
        def empty_inventory(path):
            if path == report.state.FUNCTIONS_FILE:
                return {'functions': []}
            if path == report.state.SOURCE_UNITS_FILE:
                return {'source_units': []}
            return load_json(path)
        with patch.object(report.state, 'load_json', side_effect=empty_inventory):
            units = [u for u in report.plan() if u['overlay'] == 'debugger']
        self.assertEqual([(u['start'], u['end']) for u in units],
                         [(0x19EA88, 0x1A0558), (0x1A0558, 0x1A20D8), (0x1A20D8, 0x1A2178)])
        self.assertTrue(all(u['kind'] == 'unassigned' and not u.get('complete')
                            and 'source' not in u for u in units))

    def test_prepared_debugger_missing_code_keeps_denominator_without_credit(self):
        with tempfile.TemporaryDirectory() as tmp:
            output = Path(tmp) / 'report'
            specs, targets = [], {}
            for overlay in ('main', 'game', 'debugger'):
                key = overlay + '/000000'
                specs.append({'key': key, 'overlay': overlay, 'start': 0, 'end': 4,
                              'kind': 'unassigned'})
                directory = output / 'targets' / overlay
                directory.mkdir(parents=True)
                (directory / 'targets.bin').write_bytes(bytes.fromhex('03e00008'))
                targets[key] = {'path': f'targets/{overlay}/target.o', 'source': 'target.s',
                                'sha256': 'checked', 'text_bytes': 4}
            symbols = {'f': {'address': 0, 'size': 4, 'hidden': False}}
            with patch.object(report, 'ROOT', Path(tmp)), patch.object(report, 'OUTPUT', output), \
                    patch.object(report, 'plan', return_value=specs), \
                    patch.object(report.objdiff_targets, 'prepare', return_value=(targets, {})), \
                    patch.object(report, 'digest_files', return_value='inputs'), \
                    patch.object(report, 'elf_text_symbols', return_value=symbols), \
                    patch.object(report.subprocess, 'run') as run:
                report.prepare()
            run.assert_not_called()
            config = json.loads((output / 'objdiff.json').read_text())
            coverage = json.loads((output / 'coverage.json').read_text())
            debugger = next(u for u in config['units'] if u['name'].startswith('debugger/'))
            self.assertNotIn('base_path', debugger)
            self.assertFalse(debugger['metadata']['complete'])
            self.assertEqual(debugger['metadata']['progress_categories'], ['debugger', 'project'])
            self.assertIn({'id': 'debugger', 'name': 'Debugger overlay'}, config['progress_categories'])
            self.assertEqual(coverage['mapped_code_bytes'], 12)
            self.assertEqual(coverage['expected_code_bytes'], 12)
            native = {'version': 2, 'measures': {'total_code': '12'}, 'units': [
                {'name': u['name'], 'measures': {'total_code': '4'}} for u in config['units']]}
            report.validate_report(native, coverage, config)


class NativeReportValidationTests(unittest.TestCase):
    def fixtures(self):
        config = {'units': [{'name':'a'}, {'name':'b'}]}
        coverage = {'expected_code_bytes':12, 'mapped_code_bytes':16, 'excluded_zero_bytes':4,
                    'units':[{'report_code_bytes':4},{'report_code_bytes':8}]}
        native = {'version':2,'measures':{'total_code':'12'},'units':[
            {'name':'a','measures':{'total_code':'4'}}, {'name':'b','measures':{'total_code':'8'}}]}
        return native, coverage, config

    def test_native_string_encoded_counts_validate(self):
        report.validate_report(*self.fixtures())

    def test_equal_total_cannot_hide_wrong_unit_coverage(self):
        native, coverage, config = self.fixtures()
        native['units'][0]['measures']['total_code'] = '8'
        native['units'][1]['measures']['total_code'] = '4'
        with self.assertRaisesRegex(ValueError, 'unit coverage'):
            report.validate_report(native, coverage, config)

    def test_unaccounted_padding_is_rejected(self):
        native, coverage, config = self.fixtures()
        coverage['excluded_zero_bytes'] = 0
        with self.assertRaisesRegex(ValueError, 'zero gaps'):
            report.validate_report(native, coverage, config)

    def test_duplicate_unit_cannot_replace_missing_unit(self):
        native, coverage, config = self.fixtures()
        native['units'][1]['name'] = 'a'
        with self.assertRaisesRegex(ValueError, 'duplicate'):
            report.validate_report(native, coverage, config)


if __name__ == '__main__':
    unittest.main()
