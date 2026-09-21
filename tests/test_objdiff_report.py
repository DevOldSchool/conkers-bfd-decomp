from __future__ import annotations

import sys
from pathlib import Path
import unittest

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

    def test_repository_plan_covers_both_cpu_ranges(self):
        plan = report.plan()
        ranges = report.state.validate_code_ranges(report.state.load_json(report.state.OVERLAYS_FILE))
        for overlay in ('main', 'game'):
            units = [u for u in plan if u['overlay']==overlay]
            start,end = ranges[overlay]['us']
            self.assertEqual(units[0]['start'], start)
            self.assertEqual(units[-1]['end'], end)
            self.assertTrue(all(a['end']==b['start'] for a,b in zip(units,units[1:])))
            self.assertEqual(sum(u['end']-u['start'] for u in units), end-start)


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
