from __future__ import annotations

import json
import io
import sys
import tempfile
from pathlib import Path
import unittest
from unittest.mock import patch
from contextlib import ExitStack, redirect_stdout

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import objdiff_report as report


class CoveragePlanTests(unittest.TestCase):
    def test_original_assembly_reuses_fresh_data_runtime_proof(self):
        path = 'build/us/original-assets/conker.us.elf'
        unit = {'kind': 'source_placement', 'overlay': 'debugger',
                'data_completion_verified': True, 'linked_inputs': {path: 'checked'}}
        self.assertEqual(report.debugger_runtime_from_data([unit]), {path: 'checked'})
        for units in ([], [{**unit, 'data_completion_verified': False}],
                      [{**unit, 'linked_inputs': {}}],
                      [unit, {**unit, 'linked_inputs': {path: 'different'}}]):
            with self.subTest(units=units), self.assertRaisesRegex(ValueError, 'fresh debugger'):
                report.debugger_runtime_from_data(units)

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
            with ExitStack() as stack:
                data_prepared = stack.enter_context(patch.object(report, 'prepare_data', return_value=([], [], {})))
                for context in (
                    patch.object(report, 'ROOT', Path(tmp)), patch.object(report, 'OUTPUT', output),
                    patch.object(report, 'plan', return_value=specs),
                    patch.object(report.objdiff_targets, 'prepare', return_value=(targets, {})),
                    patch.object(report, 'digest_files', return_value='inputs'),
                    patch.object(report.objdiff_ownership, 'verify_grouped_images'),

                    patch.object(report, 'prepare_font', return_value=(
                        {'size': 8, 'report_code_bytes': 0, 'report_data_bytes': 8},
                        {'name': 'assets/font', 'metadata': {'complete': False}})),
                    patch.object(report, 'prepare_textures', return_value=(
                        [{'size': 4, 'report_code_bytes': 0, 'report_data_bytes': 4},
                         {'size': 6, 'report_code_bytes': 0, 'report_data_bytes': 6}],
                        [{'name': 'assets/flat/textures/1063', 'metadata': {'complete': False}},
                         {'name': 'assets/flat/textures/1064', 'metadata': {'complete': False}}])),
                    patch.object(report, 'prepare_models', return_value=(
                        [{'size': 5, 'report_code_bytes': 0, 'report_data_bytes': 5}],
                        [{'name': 'assets/models/bank03/0003', 'metadata': {'complete': False}}])),
                    patch.object(report, 'prepare_adpcm', return_value=([], [])),
                    patch.object(report, 'prepare_sound_bank', return_value=([], [])),
                    patch.object(report, 'prepare_animation_controls', return_value=([], [])),
                    patch.object(report, 'prepare_scripts', return_value=([], [])),
                    patch.object(report, 'prepare_events', return_value=([], [])),
                    patch.object(report, 'prepare_sprites', return_value=([], [])),
                    patch.object(report, 'prepare_visibility', return_value=([], [])),
                    patch.object(report, 'prepare_animation_clips', return_value=([], [])),
                    patch.object(report, 'prepare_scene_fields', return_value=([], [])),
                    patch.object(report, 'prepare_scene_volumes', return_value=([], [])),
                    patch.object(report, 'prepare_animation_bank', return_value=([], [])),
                    patch.object(report, 'prepare_routes', return_value=([], [])),
                    patch.object(report, 'prepare_morphs', return_value=([], [])),
                    patch.object(report, 'prepare_mp3_spectral', return_value=([], [])),
                    patch.object(report, 'prepare_mp3_tables', return_value=([], [])),
                    patch.object(report, 'prepare_sequences', return_value=([], [])),
                    patch.object(report.objdiff_data_targets, 'prebuild_asset_objects'),
                    patch.object(report, 'prepare_storage', return_value=(
                        [{'kind': 'unreconstructed_asset', 'size': 7, 'report_code_bytes': 0,
                          'report_data_bytes': 7, 'complete': False}],
                        [{'name': 'assets/storage/flat/unreconstructed', 'metadata': {'complete': False}}],
                        {'stored_asset_bytes': 30})),
                    patch.object(report, 'elf_text_symbols', side_effect=lambda _: (
                        self.assertTrue(data_prepared.called), symbols)[1]),
                ):
                    stack.enter_context(context)
                run = stack.enter_context(patch.object(report.subprocess, 'run'))
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
                {'id': 'original_assembly', 'name': 'Original assembly'},
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
            (root / 'toolchain').mkdir()
            (root / 'toolchain/tools.lock.json').write_text(json.dumps({'objdiff_cli': {
                'version': 'test', 'assets': {'official': 'test'}}}))
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
            printed = io.StringIO()
            with patch.object(report, 'ROOT', root), patch.object(report, 'OUTPUT', output), \
                    patch.object(report, 'input_fingerprint', return_value='stable-inputs'), \
                    patch.object(report.subprocess, 'check_output', return_value='a' * 40), \
                    patch.object(report.subprocess, 'run', side_effect=run) as commands, redirect_stdout(printed):
                self.assertEqual(0, report.generate(Path('/synthetic/objdiff')))
                prepare = commands.call_args_list[0].args[0]
                self.assertEqual(prepare[1:], ['objdiff-report-prepare'])
                self.assertEqual(0, report.generate(Path('/synthetic/objdiff'), fresh=True))
                self.assertEqual(commands.call_args_list[3].args[0][1:], ['objdiff-report-prepare', '--fresh'])
            # The log gets a short summary; the full validation document goes to disk only.
            lines = printed.getvalue().splitlines()
            self.assertLess(len(lines), 30)
            self.assertTrue(lines[0].startswith('objdiff report: profile us, revision aaaaaaaaaaaa'))
            self.assertIn('  compile errors: 0', lines)
            self.assertNotIn('"snapshot_schema"', printed.getvalue())
            self.assertIn('validation.json', printed.getvalue())
            self.assertFalse((root / 'progress/summary.json').exists())
            self.assertFalse((root / 'build/progress/summary.json').exists())
            validation = json.loads((output / 'validation.json').read_text())
            self.assertEqual(expected, validation['existing_progress'])
            self.assertEqual('test', validation['native_toolchain']['version'])
            self.assertEqual(1, validation['snapshot_schema'])
            self.assertEqual('us', validation['profile'])
            self.assertEqual('a' * 40, validation['git_revision'])
            self.assertIn('source_dirty', validation)

    def test_original_assembly_credit_requires_maintained_source_and_native_match(self):
        import copy
        config = {'units': [{'name': 'tlb', 'base_path': 'base.o', 'metadata': {
            'complete': True, 'source_path': 'src/debugger/tlb.s',
            'progress_categories': ['debugger', 'original_assembly']}}]}
        spec = {'kind': 'original_asm', 'report_code_bytes': 152, 'report_data_bytes': 0,
                'start': 0, 'end': 160, 'base_path': 'base.o', 'assembly_source': 'src/debugger/tlb.s',
                'candidate_origin': 'maintained_original_assembly',
                'complete': True, 'original_asm_completion_verified': True,
                'maintained_assembly_proof': {'bytes': 160, 'matches_original': True},
                'original_asm_proofs': {'tlb': {'span_sha256': 'checked'}},
                'source_inputs': {'src/debugger/tlb.s': 'checked'}, 'linked_inputs': {'runtime.elf': 'checked'}}
        coverage = {'units': [spec], 'expected_code_bytes': 152, 'mapped_code_bytes': 160,
                    'excluded_zero_bytes': 8}
        measures = {'total_code': '152', 'matched_code': '152', 'complete_code': '152'}
        native = {'version': 2, 'measures': measures,
                  'units': [{'name': 'tlb', 'measures': dict(measures)}]}
        report.validate_report(native, coverage, config)
        for field in ('matched_code', 'complete_code'):
            changed = copy.deepcopy(native)
            changed['units'][0]['measures'][field] = '0'
            with self.subTest(field=field), self.assertRaisesRegex(ValueError, 'original assembly'):
                report.validate_report(changed, coverage, config)
        for field in ('base_path', 'candidate_origin', 'maintained_assembly_proof', 'assembly_source',
                      'original_asm_completion_verified', 'original_asm_proofs', 'linked_inputs'):
            changed = copy.deepcopy(coverage)
            del changed['units'][0][field]
            with self.subTest(field=field), self.assertRaisesRegex(ValueError, 'original assembly'):
                report.validate_report(native, changed, config)
        changed = copy.deepcopy(config)
        changed['units'][0]['metadata']['progress_categories'] = ['debugger']
        with self.assertRaisesRegex(ValueError, 'original assembly'):
            report.validate_report(native, coverage, changed)

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
            'target_verification': {'matches_original': True}, 'candidate_source': 'fresh_encode'})
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
        coverage['units'][-1]['literal_payload_matches_rom'] = False
        native['units'][-1]['measures']['matched_data'] = '0'
        native['measures']['matched_data'] = '8'
        with self.assertRaisesRegex(ValueError, 'fully linked'):
            report.validate_report(native, coverage, config)

    def reused_fixtures(self):
        native, coverage, config = self.fixtures()
        coverage['units'][-1].update(
            candidate_source='reused_receipt', payload_sha256='out',
            receipt={'family': 'font', 'path': 'build/us/asset-receipts/font.json',
                     'encoder_module': 'scripts/font_splits.py', 'encoder_extra': [], 'encoder_sha256': 'enc',
                     'part': 'font_rle', 'output': 'build/us/fonts/parts/font_rle.bin', 'output_sha256': 'out',
                     'input_directory': '', 'source_inputs': {'glyph.pgm': 'hash'}})
        return native, coverage, config

    def test_rebuilt_assets_record_their_candidate_origin(self):
        native, coverage, config = self.fixtures()
        del coverage['units'][-1]['candidate_source']
        with self.assertRaisesRegex(ValueError, 'origin is not recorded'):
            report.validate_report(native, coverage, config)
        coverage['units'][-1]['candidate_source'] = 'cached'
        with self.assertRaisesRegex(ValueError, 'origin is not recorded'):
            report.validate_report(native, coverage, config)

    def test_reused_receipt_must_match_compared_inputs_and_bytes(self):
        report.validate_report(*self.reused_fixtures())
        for change in ({'source_inputs': {'glyph.pgm': 'other'}}, {'output_sha256': 'other'},
                       {'encoder_sha256': ''}, {'encoder_module': ''}, {'output': ''}):
            native, coverage, config = self.reused_fixtures()
            coverage['units'][-1]['receipt'].update(change)
            with self.subTest(change=change), self.assertRaisesRegex(ValueError, 'reused receipt'):
                report.validate_report(native, coverage, config)
        native, coverage, config = self.reused_fixtures()
        del coverage['units'][-1]['receipt']
        with self.assertRaisesRegex(ValueError, 'reused receipt'):
            report.validate_report(native, coverage, config)
        native, coverage, config = self.reused_fixtures()
        coverage['units'][-1]['payload_sha256'] = 'other'
        with self.assertRaisesRegex(ValueError, 'reused receipt'):
            report.validate_report(native, coverage, config)

    def test_reused_receipt_is_rederived_from_the_checkout(self):
        import hashlib
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'build/us/fonts/parts').mkdir(parents=True)
            (root / 'build/us/fonts/parts/font_rle.bin').write_bytes(b'font bytes')
            (root / 'glyph.pgm').write_bytes(b'glyph')
            native, coverage, config = self.reused_fixtures()
            unit = coverage['units'][-1]
            unit['source_inputs'] = {'glyph.pgm': hashlib.sha256(b'glyph').hexdigest()}
            unit['receipt']['source_inputs'] = dict(unit['source_inputs'])
            unit['payload_sha256'] = unit['receipt']['output_sha256'] = hashlib.sha256(b'font bytes').hexdigest()
            with patch.object(report.asset_receipts, 'encoder_fingerprint', return_value='enc') as fingerprint:
                report.validate_report(native, coverage, config, root=root)
                fingerprint.assert_called_once()
                self.assertEqual(fingerprint.call_args.args[1], 'scripts/font_splits.py')
                (root / 'build/us/fonts/parts/font_rle.bin').write_bytes(b'rebuilt differently')
                with self.assertRaisesRegex(ValueError, 'differs from the built file'):
                    report.validate_report(native, coverage, config, root=root)
                (root / 'build/us/fonts/parts/font_rle.bin').write_bytes(b'font bytes')
                (root / 'glyph.pgm').write_bytes(b'edited')
                with self.assertRaisesRegex(ValueError, 'receipt input changed'):
                    report.validate_report(native, coverage, config, root=root)
                (root / 'glyph.pgm').write_bytes(b'glyph')
                report.validate_report(native, coverage, config, root=root)
            with patch.object(report.asset_receipts, 'encoder_fingerprint', return_value='other encoder'), \
                    self.assertRaisesRegex(ValueError, 'encoder differs'):
                report.validate_report(native, coverage, config, root=root)
            # Without a root the structural checks still run and pass.
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


class DataCompletionNotesTests(unittest.TestCase):
    def fixture(self, matched):
        native, coverage, config = PublishedDataTests().fixtures()
        spec = coverage['units'][-2]
        spec.update(complete=True, data_completion_verified=True,
                    linked_inputs={'actual-sdk.a': 'hash'})
        config['units'][-2]['metadata']['complete'] = True
        native['units'][-2]['measures'].update(matched_data=str(matched), complete_data='8')
        native['measures'].update(matched_data=str(matched), complete_data='8')
        return native, coverage, config

    def test_verified_completion_does_not_require_or_modify_native_matching(self):
        for matched in (0, 4, 8):
            with self.subTest(matched=matched):
                inputs = self.fixture(matched)
                original = json.dumps(inputs)
                notes = report.data_completion_notes(*inputs)
                self.assertEqual(json.dumps(inputs), original)
                self.assertEqual(len(notes), int(matched != 8))
                if notes:
                    self.assertEqual(notes[0]['data_bytes'], 8)
                    self.assertEqual(notes[0]['matched_data_bytes'], matched)
                    self.assertIn('verified independently', notes[0]['reason'])
                report.validate_report(*inputs)

    def test_match_without_build_proof_never_promotes_completion(self):
        native, coverage, config = PublishedDataTests().fixtures()
        original = json.dumps((native, coverage, config))
        self.assertEqual(report.data_completion_notes(native, coverage, config), [])
        self.assertEqual(json.dumps((native, coverage, config)), original)
        self.assertFalse(config['units'][-2]['metadata']['complete'])

    def test_completion_always_needs_independent_proof_and_linked_inputs(self):
        for matched in (0, 4, 8):
            for field in ('data_completion_verified', 'linked_inputs'):
                with self.subTest(matched=matched, field=field):
                    native, coverage, config = self.fixture(matched)
                    coverage['units'][-2].pop(field)
                    with self.assertRaisesRegex(ValueError, 'fully linked'):
                        report.data_completion_notes(native, coverage, config)

    def test_matching_other_units_cannot_replace_missing_completion_proof(self):
        native, coverage, config = self.fixture(0)
        config['units'][-1]['base_path'] = 'other.o'
        native['units'][-1]['measures']['matched_data'] = '24'
        native['measures']['matched_data'] = '24'
        coverage['units'][-2].pop('data_completion_verified')
        with self.assertRaisesRegex(ValueError, 'fully linked'):
            report.validate_report(native, coverage, config)

    def test_completed_data_requires_candidate_even_with_zero_native_match(self):
        native, coverage, config = self.fixture(0)
        config['units'][-2].pop('base_path')
        with self.assertRaisesRegex(ValueError, 'requires a candidate'):
            report.validate_report(native, coverage, config)

    def test_legacy_completion_cannot_override_native_matching(self):
        native, coverage, config = self.fixture(0)
        config['units'][-2]['complete'] = True
        with self.assertRaisesRegex(ValueError, 'legacy completion'):
            report.validate_report(native, coverage, config)


if __name__ == '__main__':
    unittest.main()

class ReportInputFreshnessTests(unittest.TestCase):
    def test_every_proof_input_is_checked_during_generation(self):
        import hashlib
        for field in ('reference_inputs', 'source_inputs', 'linked_inputs'):
            with self.subTest(field=field), tempfile.TemporaryDirectory() as tmp, \
                    patch.object(report, 'ROOT', Path(tmp)):
                root = Path(tmp)
                input_file = root / 'input'
                input_file.write_bytes(b'original')
                unit = {field: {'input': hashlib.sha256(input_file.read_bytes()).hexdigest()}}
                report.verify_input_files(unit)
                input_file.write_bytes(b'changed')
                with self.assertRaisesRegex(ValueError, 'input changed'):
                    report.verify_input_files(unit)


class DebuggerComparisonCopyTests(unittest.TestCase):
    RUNTIME = 'build/us/original-assets/conker.us.elf'

    def run_hook(self, unit, canonical=b'canonical'):
        import hashlib
        with tempfile.TemporaryDirectory() as tmp, patch.object(report, 'ROOT', Path(tmp)), \
                patch.object(report, 'OUTPUT', Path(tmp) / 'out'), \
                patch.object(report.objdiff_candidate, 'linked_section_bases', return_value={'.text': 0}), \
                patch.object(report.objdiff_candidate, 'canonicalize',
                             side_effect=lambda raw, _: (canonical or raw, {'symbols': []})), \
                patch.object(report.objdiff_candidate, 'verify_linked_copies',
                             return_value={'.text': {'raw_and_canonical_match_runtime': True}}) as link:
            root = Path(tmp)
            (root / self.RUNTIME).parent.mkdir(parents=True)
            (root / self.RUNTIME).write_bytes(b'runtime')
            (root / 'out/code').mkdir(parents=True)
            (root / 'out/code/base.o').write_bytes(b'raw')
            unit.setdefault('linked_inputs', {self.RUNTIME: hashlib.sha256(b'runtime').hexdigest()})
            config = {'base_path': unit.get('base_path')}
            report.canonical_debugger_candidates([unit], [config])
            written = (root / 'out' / unit['base_path']).read_bytes() if unit.get('base_path') else None
            return unit, config, written, link.call_count

    def owner(self, **fields):
        return {'key': 'formatter', 'overlay': 'debugger', 'source': 'src/formatter.c',
                'data_ranges': [{}], 'complete': True, 'data_completion_verified': True,
                'base_path': 'code/base.o', **fields}

    def test_verified_debugger_owner_uses_linked_comparison_copy(self):
        unit, config, written, links = self.run_hook(self.owner())
        self.assertEqual(unit['base_path'], 'owned/formatter/base.o')
        self.assertEqual(config['base_path'], unit['base_path'])
        self.assertEqual(written, b'canonical')
        self.assertEqual(unit['comparison_copy']['raw_base_path'], 'code/base.o')
        self.assertEqual(links, 1)

    def test_owner_without_anonymous_data_keeps_actual_base(self):
        unit, config, written, links = self.run_hook(self.owner(), canonical=None)
        self.assertEqual((unit['base_path'], config['base_path'], written, links),
                         ('code/base.o', 'code/base.o', b'raw', 0))
        self.assertNotIn('comparison_copy', unit)

    def test_other_or_unverified_units_are_not_rewritten(self):
        for change in ({'overlay': 'main'}, {'complete': False}, {'data_completion_verified': False},
                       {'data_ranges': []}, {'source': None}):
            with self.subTest(change=change):
                unit, _, written, links = self.run_hook(self.owner(**change))
                self.assertEqual((unit['base_path'], written, links), ('code/base.o', b'raw', 0))

    def test_stale_runtime_proof_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'fresh runtime ELF'):
            self.run_hook(self.owner(linked_inputs={self.RUNTIME: 'stale'}))


class DebuggerReferencePreparationTests(unittest.TestCase):
    SPLIT = 'reference/us/asm/debugger/debugger.s'

    def run_ensure(self, present_before, produced):
        with tempfile.TemporaryDirectory() as tmp, patch.object(report, 'ROOT', Path(tmp)), \
                patch.object(report, 'OUTPUT', Path(tmp) / 'out'), \
                patch.object(report.subprocess, 'run') as run:
            split = Path(tmp) / self.SPLIT
            if present_before:
                split.parent.mkdir(parents=True)
                split.write_text('glabel x\n')

            def prepare(*args, **kwargs):
                if produced:
                    split.parent.mkdir(parents=True, exist_ok=True)
                    split.write_text('glabel x\n')
            run.side_effect = prepare
            report.ensure_debugger_reference()
            return run.call_args_list

    def test_existing_reference_is_reused(self):
        self.assertEqual(self.run_ensure(True, False), [])

    def test_missing_reference_is_prepared_once(self):
        calls = self.run_ensure(False, True)
        self.assertEqual([c.args[0] for c in calls], [['make', 'prepare-reference', 'PROFILE=us']])

    def test_failed_preparation_is_reported(self):
        with self.assertRaisesRegex(ValueError, 'debugger split'):
            self.run_ensure(False, False)
