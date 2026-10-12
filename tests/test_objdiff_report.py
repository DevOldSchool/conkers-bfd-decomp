from __future__ import annotations

import json
import io
import sys
import tempfile
from pathlib import Path
import unittest
from unittest.mock import patch
from contextlib import redirect_stdout

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
                    patch.object(report.objdiff_ownership, 'verify_grouped_images'), \
                    patch.object(report, 'prepare_data', return_value=([], [], {})), \
                    patch.object(report, 'prepare_font', return_value=(
                        {'size': 8, 'report_code_bytes': 0, 'report_data_bytes': 8},
                        {'name': 'assets/font', 'metadata': {'complete': False}})), \
                    patch.object(report, 'prepare_textures', return_value=(
                        [{'size': 4, 'report_code_bytes': 0, 'report_data_bytes': 4},
                         {'size': 6, 'report_code_bytes': 0, 'report_data_bytes': 6}],
                        [{'name': 'assets/flat/textures/1063', 'metadata': {'complete': False}},
                         {'name': 'assets/flat/textures/1064', 'metadata': {'complete': False}}])), \
                    patch.object(report, 'prepare_models', return_value=(
                        [{'size': 5, 'report_code_bytes': 0, 'report_data_bytes': 5}],
                        [{'name': 'assets/models/bank03/0003', 'metadata': {'complete': False}}])), \
                    patch.object(report, 'prepare_adpcm', return_value=([], [])), \
                    patch.object(report, 'prepare_sound_bank', return_value=([], [])), \
                    patch.object(report, 'prepare_sequences', return_value=([], [])), \
                    patch.object(report, 'prepare_storage', return_value=(
                        [{'kind': 'unreconstructed_asset', 'size': 7, 'report_code_bytes': 0,
                          'report_data_bytes': 7, 'complete': False}],
                        [{'name': 'assets/storage/flat/unreconstructed', 'metadata': {'complete': False}}],
                        {'stored_asset_bytes': 30})), \
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
            self.assertEqual(config['progress_categories'], [
                {'id': 'main', 'name': 'Main executable'},
                {'id': 'game', 'name': 'Game overlay'},
                {'id': 'debugger', 'name': 'Debugger overlay'},
                {'id': 'project', 'name': 'Project code'},
                {'id': 'sdk', 'name': 'SDK libraries'},
                {'id': 'data', 'name': 'Data'},
            ])
            self.assertEqual(coverage['mapped_code_bytes'], 12)
            self.assertEqual(coverage['expected_code_bytes'], 12)
            self.assertEqual(coverage['stored_asset_bytes'], 30)
            native = {'version': 2, 'measures': {'total_code': '12', 'total_data': '30'}, 'units': [
                {'name': u['name'], 'measures': {'total_code': '0', 'total_data': '8'}
                 if u['name'] == 'assets/font' else {'total_code': '0', 'total_data': '4'}
                 if u['name'] == 'assets/flat/textures/1063' else {'total_code': '0', 'total_data': '6'}
                 if u['name'] == 'assets/flat/textures/1064' else {'total_code': '0', 'total_data': '5'}
                 if u['name'] == 'assets/models/bank03/0003' else {'total_code': '0', 'total_data': '7'}
                 if u['name'] == 'assets/storage/flat/unreconstructed' else {'total_code': '4'}} for u in config['units']]}
            report.validate_report(native, coverage, config)
            stored = next(u for u in native['units'] if u['name'].endswith('/unreconstructed'))
            stored['measures']['matched_data'] = '7'
            with self.assertRaisesRegex(ValueError, 'without a matching candidate'):
                report.validate_report(native, coverage, config)
            stored['measures']['matched_data'] = '0'
            remainder = next(u for u in config['units'] if u['name'].endswith('/unreconstructed'))
            remainder['base_path'] = 'raw-copy.o'
            with self.assertRaisesRegex(ValueError, 'unreconstructed storage'):
                report.validate_report(native, coverage, config)


class NativeReportValidationTests(unittest.TestCase):
    def test_generation_uses_canonical_progress_without_any_saved_summary(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            output = root / 'build/us/objdiff-report'
            coverage = {'scope': 'synthetic', 'expected_code_bytes': 0,
                        'mapped_code_bytes': 0, 'excluded_zero_bytes': 0,
                        'target_method': 'synthetic', 'target_verification': {},
                        'compile_errors': [], 'units': []}
            native = {'version': 2, 'measures': {'total_code': '0'}, 'units': []}
            def run(command, **kwargs):
                if 'objdiff-report-prepare' in command:
                    (output / 'coverage.json').write_text(json.dumps(coverage))
                    (output / 'objdiff.json').write_text('{"units": []}')
                elif 'generate' in command:
                    (output / 'report.json').write_text(json.dumps(native))
            expected = report.state.summary(report.state.validate_project()[1])['code_bytes']['regions']['us']
            with patch.object(report, 'ROOT', root), patch.object(report, 'OUTPUT', output), \
                    patch.object(report, 'input_fingerprint', return_value='stable-inputs'), \
                    patch.object(report.subprocess, 'check_output', return_value='a' * 40), \
                    patch.object(report.subprocess, 'run', side_effect=run), redirect_stdout(io.StringIO()):
                self.assertEqual(0, report.generate(Path('/synthetic/objdiff')))
            self.assertFalse((root / 'progress/summary.json').exists())
            self.assertFalse((root / 'build/progress/summary.json').exists())
            validation = json.loads((output / 'validation.json').read_text())
            self.assertEqual(expected, validation['existing_progress'])
            self.assertEqual(1, validation['snapshot_schema'])
            self.assertEqual('us', validation['profile'])
            self.assertEqual('a' * 40, validation['git_revision'])
            self.assertIn('source_dirty', validation)

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


class PublishedDataTests(unittest.TestCase):
    def fixtures(self):
        native, coverage, config = NativeReportValidationTests().fixtures()
        config['units'] += [{'name': 'main/data/owned', 'base_path': 'data/base.o',
                             'metadata': {'complete': False}},
                            {'name': 'main/data/unknown', 'metadata': {'complete': False}}]
        coverage['units'] += [{'report_code_bytes': 0, 'report_data_bytes': 8},
                              {'report_code_bytes': 0, 'report_data_bytes': 24}]
        coverage.update(expected_data_bytes=32, mapped_data_bytes=8, unassigned_data_bytes=24)
        native['units'] += [{'name': 'main/data/owned', 'measures': {'total_data': '8', 'matched_data': '8'}},
                            {'name': 'main/data/unknown', 'measures': {'total_data': '24'}}]
        native['measures'].update(total_data='32', matched_data='8')
        return native, coverage, config

    def test_initialized_data_preserves_code_and_unknown_denominators(self):
        report.validate_report(*self.fixtures())

    def test_equal_data_total_cannot_hide_missing_unknown_bytes(self):
        native, coverage, config = self.fixtures()
        native['units'][-2]['measures']['total_data'] = '16'
        native['units'][-1]['measures']['total_data'] = '16'
        with self.assertRaisesRegex(ValueError, 'unit coverage'):
            report.validate_report(native, coverage, config)

    def test_target_only_data_cannot_earn_credit(self):
        native, coverage, config = self.fixtures()
        native['units'][-1]['measures']['matched_data'] = '24'
        native['measures']['matched_data'] = '32'
        with self.assertRaisesRegex(ValueError, 'without a matching candidate'):
            report.validate_report(native, coverage, config)

    def test_placement_cannot_earn_fully_linked_credit(self):
        native, coverage, config = self.fixtures()
        native['units'][-2]['measures']['complete_data'] = '8'
        native['measures']['complete_data'] = '8'
        with self.assertRaisesRegex(ValueError, 'fully linked'):
            report.validate_report(native, coverage, config)

    def test_data_total_must_include_all_audited_ranges(self):
        native, coverage, config = self.fixtures()
        coverage['unassigned_data_bytes'] = 0
        with self.assertRaisesRegex(ValueError, 'audited data and storage ranges'):
            report.validate_report(native, coverage, config)

    def test_published_preparation_uses_fresh_loaded_ranges_without_assets(self):
        with tempfile.TemporaryDirectory() as tmp:
            output = Path(tmp)
            audit = {'rom_sha1': 'checked', 'images': {o: {
                'loaded_bytes': 16, 'mapped_bytes': 0, 'unassigned_bytes': 16}
                for o in report.state.OVERLAYS}}
            def targets(image, rom, *, overlay, output):
                return ([{'key': overlay, 'overlay': overlay, 'size': 16,
                          'target_path': overlay + '.o'}], {'verified': True})
            def candidates(units, *, output):
                return [{'name': u['overlay'] + '/data/test', 'target_path': u['target_path'],
                         'metadata': {'complete': False}} for u in units]
            with patch.object(report, 'OUTPUT', output), \
                    patch.object(report.data_boundaries, 'audit', return_value=audit), \
                    patch.object(report.main_private_data, 'validated_rom', return_value=b'rom'), \
                    patch.object(report.objdiff_data_targets, 'prepare_targets', side_effect=targets), \
                    patch.object(report.objdiff_data_targets, 'prepare_candidates', side_effect=candidates), \
                    patch.object(report.objdiff_data_targets, 'prepare_font') as font:
                units, config, proof = report.prepare_data()
            font.assert_not_called()
            self.assertEqual(proof['expected_data_bytes'], 48)
            self.assertEqual(len(config), 3)
            for unit, item in zip(units, config):
                self.assertEqual(unit['report_code_bytes'], 0)
                self.assertEqual(unit['report_data_bytes'], 16)
                self.assertEqual(item['target_path'], 'data/' + unit['overlay'] + '.o')
                self.assertEqual(item['metadata']['progress_categories'], [unit['overlay'], 'data'])
                self.assertFalse(item['metadata']['complete'])


class FontCompletionTests(unittest.TestCase):
    def fixtures(self):
        native, coverage, config = PublishedDataTests().fixtures()
        config['units'].append({'name': 'assets/font', 'base_path': 'font/base.o',
                                'metadata': {'complete': True}})
        coverage['units'].append({'report_code_bytes': 0, 'report_data_bytes': 8,
            'kind': 'rebuilt_asset', 'complete': True, 'literal_payload_matches_rom': True,
            'source_inputs': {'glyph.pgm': 'hash'}, 'linked_inputs': {'font.o': 'hash'},
            'target_verification': {'matches_original': True}})
        coverage.update(expected_data_bytes=40, mapped_data_bytes=16)
        native['units'].append({'name': 'assets/font', 'measures': {
            'total_data': '8', 'matched_data': '8', 'complete_data': '8'}})
        native['measures'].update(total_data='40', matched_data='16', complete_data='8')
        return native, coverage, config

    def test_font_rebuilt_from_current_inputs_can_earn_completion(self):
        report.validate_report(*self.fixtures())

    def test_font_needs_all_rebuild_proofs(self):
        for field in ('literal_payload_matches_rom', 'source_inputs', 'linked_inputs', 'target_verification'):
            with self.subTest(field=field):
                native, coverage, config = self.fixtures()
                coverage['units'][-1].pop(field)
                with self.assertRaisesRegex(ValueError, 'fully linked'):
                    report.validate_report(native, coverage, config)

    def test_edited_font_cannot_retain_completion(self):
        native, coverage, config = self.fixtures()
        native['units'][-1]['measures']['matched_data'] = '0'
        native['measures']['matched_data'] = '8'
        with self.assertRaisesRegex(ValueError, 'fully linked'):
            report.validate_report(native, coverage, config)

    def test_unmatched_font_stays_in_denominator_without_completion(self):
        native, coverage, config = self.fixtures()
        coverage['units'][-1].update(complete=False, literal_payload_matches_rom=False)
        config['units'][-1]['metadata']['complete'] = False
        native['units'][-1]['measures'].update(matched_data='0', complete_data='0')
        native['measures'].update(matched_data='8', complete_data='0')
        report.validate_report(native, coverage, config)

    def test_font_preparation_checks_yaml_range_and_controls_completion(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'config/profiles').mkdir(parents=True)
            profile = root / 'config/profiles/us.yaml'
            profile.write_text('segments: [{name: font_rle, type: group, start: 16}, [24]]')
            def font(rom, *, output):
                return ({'rom_start': 16, 'rom_end': 24, 'size': 8,
                         'literal_payload_matches_rom': True}, {'metadata': {}})
            with patch.object(report, 'ROOT', root), \
                    patch.object(report.main_private_data, 'validated_rom', return_value=b'rom'), \
                    patch.object(report.objdiff_data_targets, 'prepare_font', side_effect=font):
                unit, item = report.prepare_font()
                self.assertTrue(unit['complete'])
                self.assertTrue(item['metadata']['complete'])
                self.assertEqual(item['metadata']['progress_categories'], ['data'])
                profile.write_text('segments: [{name: font_rle, type: group, start: 16}, [28]]')
                with self.assertRaisesRegex(ValueError, 'canonical YAML'):
                    report.prepare_font()


class DataCompletionQualificationTests(unittest.TestCase):
    def fixture(self, matched):
        native, coverage, config = PublishedDataTests().fixtures()
        spec = coverage['units'][-2]
        spec.update(complete=True, data_completion_verified=True,
                    linked_inputs={'actual-sdk.a': 'hash'})
        config['units'][-2]['metadata']['complete'] = True
        native['units'][-2]['measures'].update(matched_data=str(matched), complete_data='8')
        native['measures'].update(matched_data=str(matched), complete_data='8')
        return native, coverage, config

    def test_linked_byte_equality_cannot_replace_native_matching(self):
        for matched in (0, 4):
            with self.subTest(matched=matched):
                native, coverage, config = self.fixture(matched)
                with self.assertRaisesRegex(ValueError, 'natively matched'):
                    report.validate_report(native, coverage, config)
                original = json.dumps(native)
                changes = report.qualify_data_completion(native, coverage, config)
                self.assertEqual(json.dumps(native), original)
                self.assertEqual(len(changes), 1)
                self.assertFalse(coverage['units'][-2]['complete'])
                self.assertFalse(config['units'][-2]['metadata']['complete'])
                # A stale first-pass report must fail until native regeneration.
                with self.assertRaisesRegex(ValueError, 'fully linked'):
                    report.validate_report(native, coverage, config)
                native['units'][-2]['measures']['complete_data'] = '0'
                native['measures']['complete_data'] = '0'
                report.validate_report(native, coverage, config)

    def test_native_match_preserves_proven_completion(self):
        native, coverage, config = self.fixture(8)
        self.assertEqual(report.qualify_data_completion(native, coverage, config), [])
        report.validate_report(native, coverage, config)

    def test_match_without_build_proof_never_promotes_completion(self):
        native, coverage, config = PublishedDataTests().fixtures()
        self.assertEqual(report.qualify_data_completion(native, coverage, config), [])
        self.assertFalse(config['units'][-2]['metadata']['complete'])

    def test_matching_total_cannot_hide_an_unmatched_completed_unit(self):
        native, coverage, config = self.fixture(0)
        config['units'][-1]['base_path'] = 'other.o'
        native['units'][-1]['measures']['matched_data'] = '24'
        native['measures']['matched_data'] = '24'
        with self.assertRaisesRegex(ValueError, 'natively matched'):
            report.validate_report(native, coverage, config)


if __name__ == '__main__':
    unittest.main()
