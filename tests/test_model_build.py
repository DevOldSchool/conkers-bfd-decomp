from __future__ import annotations

import copy
import hashlib
import json
import io
from pathlib import Path
import struct
import sys
import tempfile
import subprocess
import unittest
from unittest.mock import patch
from contextlib import redirect_stderr, redirect_stdout
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import model_build as build
import objdiff_data_targets as targets
from test_objdiff_data_targets import object_file


class ModelBuildTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.records = {'header_words': [88, 24, 0, 0, 0, 0, 0, 0, 0, 0x80000000],
                        'vertices': [[-1, 2, 3, 0, -32, 64, 10, 20, 30, 255],
                                     [5, 0, 0, 0, 0, 0, 0, 0, 0, 255],
                                     [0, 5, 0, 0, 0, 0, 0, 0, 0, 255]],
                        'display_commands': [[0x01003006, 0x01000000], [0x05000204, 0], [0xDF000000, 0]]}
        self.payload = build.encode_records(self.records, bank=3)
        self.packed = build.rzip_pack.encode_rzip_chunk(self.payload)
        self.rom = b'prefix' + self.packed + b'tail'
        self.expected = {'schema_version': 1, 'profile': 'us', 'bank': 3, 'entry': 3,
                         'rom_sha1': hashlib.sha1(self.rom).hexdigest(),
                         'rom_start': 6, 'rom_end': 6 + len(self.packed),
                         'decoded_size': len(self.payload),
                         'original_decoded_sha256': build.sha256(self.payload),
                         'original_stored_sha256': build.sha256(self.packed),
                         'encoder': build.texture_build.ENCODERS['zlib']}
        self.inputs = self.root / build.input_directory(3, 3)
        self.initialize()

    def initialize(self):
        build.texture_build.publish_inputs(self.inputs, {
            'manifest.json': json.dumps(self.expected).encode(),
            'model.json': json.dumps(self.records).encode()})

    def test_reconstructs_native_fields_and_fresh_compressed_storage(self):
        self.assertEqual(build.model_records(self.payload, bank=3), self.records)
        with patch.object(build.rzip_pack, 'encode_rzip_chunk', wraps=build.rzip_pack.encode_rzip_chunk) as encode:
            packed, hashes = build.packed_model(self.inputs, self.expected)
        self.assertEqual(packed, self.packed)
        encode.assert_called_once_with(self.payload)
        self.assertEqual(set(hashes), {'manifest.json', 'model.json'})

    def test_bank_specific_helpers_require_an_explicit_bank(self):
        for function, arguments in (
                (build.part_name, (3,)), (build.input_directory, (3,)),
                (build.layout_bins, (self.root,)), (build.model_records, (self.payload,)),
                (build.encode_records, (self.records,)), (build.recover_inputs, (3, self.root))):
            with self.subTest(function=function.__name__), self.assertRaises(TypeError):
                function(*arguments)

    def test_cli_requires_recovery_bank_and_routes_scoped_builds(self):
        with patch.object(build, 'recover_inputs') as recover, redirect_stderr(io.StringIO()) as stderr:
            with self.assertRaises(SystemExit) as error:
                build.main(['recover', '--entry', '3'])
        self.assertEqual(error.exception.code, 2)
        self.assertIn('--bank', stderr.getvalue())
        recover.assert_not_called()
        for bank in (3, 9):
            with patch.object(build, 'build_parts', return_value={'model_count': 1, 'stored_bytes': 2}) as pack, \
                    redirect_stdout(io.StringIO()):
                build.main(['build-parts', '--bank', str(bank)])
            pack.assert_called_once_with(bank=bank)

    def test_bank09_relative_addresses_are_bank_scoped_and_preserve_command_words(self):
        records = copy.deepcopy(self.records)
        records['display_commands'][0][1] = 0x28
        payload = build.encode_records(records, bank=9)
        self.assertEqual(build.model_records(payload, bank=9), records)
        self.assertEqual(struct.unpack_from('>II', payload, 88), (0x01003006, 0x28))
        with self.assertRaisesRegex(ValueError, 'invalid vertex load'):
            build.encode_records(records, bank=3)
        for address in (0x18, 0x29, 0x58):
            with self.subTest(address=address), self.assertRaises(ValueError):
                records['display_commands'][0][1] = address
                build.encode_records(records, bank=9)
        with self.assertRaisesRegex(ValueError, 'unsupported direct-model bank'):
            build.model_records(self.payload, bank=4)

    def test_same_entry_id_in_two_banks_has_separate_inputs_outputs_and_recovery(self):
        expected09 = dict(self.expected, bank=9)
        inputs09 = self.root / build.input_directory(3, 9)
        build.texture_build.publish_inputs(inputs09, build.input_files(expected09, self.records))
        selected = [(self.expected, self.records), (expected09, self.records)]
        with patch.object(build, 'reviewed_models', return_value=(self.rom, selected)):
            proof = build.build_parts(self.root)
            (inputs09 / 'notes.txt').write_text('bank09 edit')
            recovered = build.recover_inputs(3, self.root, bank=9)
        self.assertEqual(proof['model_count'], 2)
        for bank in (3, 9):
            self.assertEqual((self.root / 'build/us/models/parts' /
                              (build.part_name(3, bank) + '.bin')).read_bytes(), self.packed)
        self.assertEqual(recovered['bank'], 9)
        self.assertEqual((Path(recovered['backup_directory']) / 'notes.txt').read_text(), 'bank09 edit')
        self.assertEqual(json.loads((self.inputs / 'manifest.json').read_text()), self.expected)

    def test_bank09_rejects_auxiliary_or_uncovered_storage(self):
        for payload in (self.payload + bytes(16),
                        struct.pack('>10I', 88, 24, 112, 8, 0, 0, 0, 0, 0, 0x80000000)
                        + self.payload[40:] + bytes(8)):
            with self.assertRaisesRegex(ValueError, 'auxiliary|trailing'):
                build.model_records(payload, bank=9)

    def test_normal_tables_and_observed_zero_suffix_rebuild_exactly(self):
        for bank in (3, 9):
            for suffix in (b'', bytes(8)):
                header = [88, 32, 0, 0, 0, 0, 0, 0, 0, 0x80000000]
                normals = b''.join(struct.pack('>bb', i - 16, 127 - i) for i in range(32))
                payload = (struct.pack('>10I', *header) + self.payload[40:88]
                           + struct.pack('>II', 0xDC38000E, 120) + self.payload[88:]
                           + normals + suffix)
                with self.subTest(bank=bank, suffix=len(suffix)):
                    records = build.model_records(payload, bank=bank)
                    self.assertEqual(records['normal_xy_s8'][0][0], [-16, 127])
                    self.assertEqual(records.get('zero_suffix_bytes', 0), len(suffix))
                    self.assertEqual(build.encode_records(records, bank=bank), payload)
                    altered = copy.deepcopy(records)
                    altered['normal_xy_s8'][0][0][0] = -17
                    self.assertNotEqual(build.encode_records(altered, bank=bank), payload)
                    altered['normal_xy_s8'][0].pop()
                    with self.assertRaisesRegex(ValueError, 'normal table'):
                        build.encode_records(altered, bank=bank)

    def test_normal_pointer_ranges_do_not_admit_gaps_overlap_or_truncation(self):
        for pointer in (88, 112, 121, 128, 184):
            payload = (struct.pack('>10I', 88, 32, 0, 0, 0, 0, 0, 0, 0, 0x80000000)
                       + self.payload[40:88] + struct.pack('>II', 0xDC38000E, pointer)
                       + self.payload[88:] + bytes(64))
            with self.subTest(pointer=pointer), self.assertRaises(ValueError):
                build.model_records(payload, bank=9)
        payload = (struct.pack('>10I', 88, 32, 0, 0, 0, 0, 0, 0, 0, 0x80000000)
                   + self.payload[40:88] + struct.pack('>II', 0xDC38000E, 120)
                   + self.payload[88:] + bytes(63))
        with self.assertRaisesRegex(ValueError, 'incomplete'):
            build.model_records(payload, bank=9)

    def test_zero_suffix_is_explicit_and_cannot_encode_opaque_bytes(self):
        records = dict(self.records, zero_suffix_bytes=8)
        self.assertEqual(build.encode_records(records, bank=3), self.payload + bytes(8))
        for suffix in (bytes(7), bytes(16), bytes(7) + b'X'):
            with self.subTest(suffix=suffix), self.assertRaisesRegex(ValueError, 'trailing'):
                build.model_records(self.payload + suffix, bank=3)
        for size in (True, -1, 1, 16, 8.0):
            with self.subTest(size=size), self.assertRaises(ValueError):
                build.encode_records(dict(self.records, zero_suffix_bytes=size), bank=3)

    def test_attachment_records_rebuild_rigid_jointed_and_multiple_parts(self):
        from test_model_attachment_format import payload
        for jointed in (False, True):
            for parts in (1, 2):
                for suffix in (b'', bytes(8)):
                    raw = payload(jointed=jointed, parts=parts) + suffix
                    with self.subTest(jointed=jointed, parts=parts, suffix=len(suffix)):
                        records = build.model_records(raw, bank=9)
                        self.assertEqual(records['format'], 'attachment-three-pair')
                        self.assertEqual(len(records['part_pointers']), parts)
                        self.assertEqual(len(records['joints']), int(jointed))
                        self.assertEqual(records['normal_xy_s8'][0], [1, -2])
                        self.assertEqual(build.encode_records(records, bank=9), raw)
                        with self.assertRaisesRegex(ValueError, 'require bank 09'):
                            build.encode_records(records, bank=3)

    def test_attachment_boundaries_and_joint_fields_are_not_opaque(self):
        from test_model_attachment_format import payload
        raw = payload(jointed=True, parts=2)
        records = build.model_records(raw, bank=9)
        for field in ('vertices', 'normal_xy_s8', 'joints'):
            changed = copy.deepcopy(records)
            changed[field][0][0 if field == 'vertices' else -1] += 1
            with self.subTest(field=field):
                self.assertNotEqual(build.encode_records(changed, bank=9), raw)
        invalid = []
        changed = copy.deepcopy(records)
        changed['part_pointers'][1] = changed['part_pointers'][0]
        invalid.append(changed)
        changed = copy.deepcopy(records)
        changed['normal_xy_s8'].pop()
        invalid.append(changed)
        changed = copy.deepcopy(records)
        changed['joints'][0][0] = 0  # A cycle is invalid even if byte encoding succeeds.
        invalid.append(changed)
        changed = copy.deepcopy(records)
        changed['joints'][0][-1] = float('nan')
        invalid.append(changed)
        changed = copy.deepcopy(records)
        changed['header_words'][4] += 8
        invalid.append(changed)
        for changed in invalid:
            with self.subTest(records=changed), self.assertRaises(ValueError):
                build.encode_records(changed, bank=9)

    def test_attachment_zero_regions_cannot_hide_gaps_or_nonzero_source(self):
        from test_model_attachment_format import payload
        raw = payload(jointed=True) + bytes(8)
        records = build.model_records(raw, bank=9)
        offset, size = records['zero_regions'][0]
        poisoned = bytearray(raw)
        poisoned[offset] = 1
        with self.assertRaisesRegex(ValueError, 'nonzero'):
            build.model_records(bytes(poisoned), bank=9)
        for zero_regions in ([], [[offset, size + 4]], [[offset + 1, size]],
                             [[offset, True]], [[offset, 0x10000000]]):
            with self.subTest(zero_regions=zero_regions), self.assertRaises(ValueError):
                build.encode_records(dict(records, zero_regions=zero_regions), bank=9)
        with self.assertRaisesRegex(ValueError, 'schema'):
            build.encode_records(dict(records, opaque_tail='00'), bank=9)

    def test_bank09_source_changes_preserve_existing_linker_parts(self):
        expected = dict(self.expected, bank=9)
        directory = self.root / build.input_directory(3, 9)
        with patch.object(build, 'reviewed_models', return_value=(self.rom, [(expected, self.records)])):
            build.build_parts(self.root)
            part = self.root / 'build/us/models/parts/models/bank09/0003.bin'
            before = part.read_bytes(), part.stat().st_mtime_ns
            records = copy.deepcopy(self.records)
            records['vertices'][0][0] += 1
            (directory / 'model.json').write_text(json.dumps(records))
            with self.assertRaisesRegex(ValueError, 'original payload'):
                build.build_parts(self.root)
            self.assertEqual((part.read_bytes(), part.stat().st_mtime_ns), before)
            self.assertEqual(json.loads((directory / 'model.json').read_text()), records)

    def test_auxiliary_regions_and_trailing_bytes_are_not_admitted(self):
        with self.assertRaisesRegex(ValueError, 'auxiliary|trailing'):
            build.model_records(self.payload + bytes(16), bank=3)
        altered = dict(self.records, header_words=[88, 24, 112, 8, 0, 0, 0, 0, 0, 0x80000000])
        data = struct.pack('>10I', *altered['header_words']) + self.payload[40:] + bytes(8)
        with self.assertRaisesRegex(ValueError, 'auxiliary|trailing'):
            build.model_records(data, bank=3)

    def test_record_boundary_range_and_schema_changes_are_rejected(self):
        for field, value in [('header_words', [56, 16, 0, 0, 0, 0, 0, 0, 0, 0]),
                             ('vertices', [[32768, 0, 0, 0, 0, 0, 0, 0, 0, 0]]),
                             ('display_commands', [[0, 0]])]:
            with self.subTest(field=field), self.assertRaises(ValueError):
                build.encode_records(dict(self.records, **{field: value}), bank=3)
        with self.assertRaises(ValueError):
            build.encode_records(dict(self.records, opaque='1234'), bank=3)

    def test_changed_inputs_fail_without_replacing_linker_parts(self):
        selected = [(self.expected, self.records)]
        with patch.object(build, 'reviewed_models', return_value=(self.rom, selected)):
            build.build_parts(self.root)
            output = self.root / 'build/us/models/parts/models/bank03/0003.bin'
            before = output.read_bytes(), output.stat().st_mtime_ns
            altered = copy.deepcopy(self.records)
            altered['vertices'][0][0] += 1
            (self.inputs / 'model.json').write_text(json.dumps(altered))
            with self.assertRaisesRegex(ValueError, 'original payload'):
                build.build_parts(self.root)
            self.assertEqual((output.read_bytes(), output.stat().st_mtime_ns), before)
            self.assertEqual(json.loads((self.inputs / 'model.json').read_text()), altered)

    def test_missing_input_and_changed_manifest_are_preserved(self):
        (self.inputs / 'model.json').unlink()
        with self.assertRaisesRegex(ValueError, r'model.json.*Inputs were preserved;.*recover --bank 3 --entry 3'):
            build.packed_model(self.inputs, self.expected)
        self.assertFalse((self.inputs / 'model.json').exists())
        (self.inputs / 'manifest.json').write_text('{}')
        with self.assertRaisesRegex(ValueError, 'manifest'):
            build.packed_model(self.inputs, self.expected)

    def test_explicit_recovery_preserves_the_entire_old_bundle(self):
        (self.inputs / 'model.json').unlink()
        (self.inputs / 'manifest.json').write_text('stale manifest')
        (self.inputs / 'notes.txt').write_text('user work')
        with patch.object(build, 'reviewed_models', return_value=(self.rom, [(self.expected, self.records)])):
            with self.assertRaisesRegex(ValueError, 'recover --bank 3 --entry 3'):
                build.build_parts(self.root)
            result = build.recover_inputs(3, self.root, bank=3)
            packed, _ = build.packed_model(self.inputs, self.expected)
            with self.assertRaisesRegex(ValueError, 'not in the reviewed'):
                build.recover_inputs(999, self.root, bank=3)
        backup = Path(result['backup_directory'])
        self.assertEqual((backup / 'manifest.json').read_text(), 'stale manifest')
        self.assertEqual((backup / 'notes.txt').read_text(), 'user work')
        self.assertFalse((backup / 'model.json').exists())
        self.assertEqual(packed, self.packed)
        self.assertFalse(backup.is_relative_to(self.root / build.INPUT_DIRECTORY))

    def test_failed_recovery_restores_original_folder(self):
        (self.inputs / 'notes.txt').write_text('keep this')
        before = {p.name: p.read_bytes() for p in self.inputs.iterdir()}
        with patch.object(build, 'reviewed_models', return_value=(self.rom, [(self.expected, self.records)])), \
                patch.object(build.texture_build, 'publish_inputs', side_effect=ValueError('publish failed')):
            with self.assertRaisesRegex(ValueError, 'publish failed'):
                build.recover_inputs(3, self.root, bank=3)
        self.assertEqual({p.name: p.read_bytes() for p in self.inputs.iterdir()}, before)

    def test_missing_manifest_does_not_reinitialize_orphaned_records(self):
        (self.inputs / 'manifest.json').unlink()
        before = (self.inputs / 'model.json').read_bytes()
        with patch.object(build, 'reviewed_models', return_value=(self.rom, [(self.expected, self.records)])):
            with self.assertRaisesRegex(ValueError, 'manifest.json.*recover --bank 3 --entry 3'):
                build.build_parts(self.root)
        self.assertEqual((self.inputs / 'model.json').read_bytes(), before)
        self.assertFalse((self.inputs / 'manifest.json').exists())

    def test_cli_routes_recovery_and_reports_expected_errors_without_tracebacks(self):
        with patch.object(build, 'recover_inputs', return_value={'backup_directory': 'kept'}) as recover, \
                redirect_stdout(io.StringIO()) as stdout:
            build.main(['recover', '--bank', '3', '--entry', '3'])
        recover.assert_called_once_with(3, bank=3)
        self.assertEqual(json.loads(stdout.getvalue())['backup_directory'], 'kept')
        with patch.object(build, 'build_parts', side_effect=ValueError('broken input; recover --bank 3 --entry 3')), \
                redirect_stderr(io.StringIO()) as stderr:
            with self.assertRaises(SystemExit) as error:
                build.main(['build-parts'])
        self.assertEqual(error.exception.code, 2)
        self.assertIn('error: broken input; recover --bank 3 --entry 3', stderr.getvalue())
        self.assertNotIn('Traceback', stderr.getvalue())

    def test_absent_bank_raises_domain_error(self):
        rom = self.root / 'rom.bin'
        rom.write_bytes(self.rom)
        contract = self.root / build.CONTRACT
        contract.parent.mkdir(parents=True)
        contract.write_text(json.dumps({'schema_version': 2, 'profile': 'us',
            'rom_sha1': self.expected['rom_sha1'], 'encoder': self.expected['encoder'], 'banks': {'03': [3], '09': [3]}}))
        with patch.object(build.model_assets, 'resolve_rom', return_value=(rom, {
                'normalized_sha1': [self.expected['rom_sha1']], 'asset_table': 0})), \
                patch.object(build.rzip_archive, 'normalize_rom', return_value=(self.rom, 'z64')), \
                patch.object(build.rzip_archive, 'parse_asset_banks', return_value=[]):
            with self.assertRaisesRegex(ValueError, 'bank 03 is missing'):
                build.reviewed_models(self.root)

    def test_independent_rom_mismatch_fails_before_any_output_is_written(self):
        with patch.object(build, 'reviewed_models', return_value=(self.rom, [(self.expected, self.records)])), \
                patch.object(build, 'packed_model', return_value=(b'wrong', {})):
            with self.assertRaisesRegex(ValueError, 'independent original ROM'):
                build.build_parts(self.root)
        self.assertFalse((self.root / 'build/us/models').exists())

    def test_model_make_error_names_the_log(self):
        output = self.root / 'report'
        output.mkdir()
        def fail(args, **kwargs):
            kwargs['stderr'].write('model compiler details')
            raise subprocess.CalledProcessError(2, args)
        with patch.object(targets.model_build, 'reviewed_models', return_value=(self.rom, [(self.expected, self.records)])), \
                patch.object(targets.subprocess, 'run', side_effect=fail):
            with self.assertRaisesRegex(ValueError, r'exit 2.*model-build.log'):
                targets.prepare_models(self.rom, output=output)
        self.assertEqual((output / 'model-build.log').read_text(), 'model compiler details')

    def test_encoder_drift_is_not_accepted_or_retried(self):
        with patch.object(build.rzip_pack, 'encode_rzip_chunk', return_value=bytes(len(self.packed))) as encode:
            with self.assertRaisesRegex(ValueError, 'encoder differs'):
                build.packed_model(self.inputs, self.expected)
        encode.assert_called_once()

    def test_input_race_is_rejected(self):
        real = build.rzip_pack.encode_rzip_chunk
        def encode(payload):
            path = self.inputs / 'model.json'
            path.write_text(path.read_text() + '\n')
            return real(payload)
        with patch.object(build.rzip_pack, 'encode_rzip_chunk', side_effect=encode):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_model(self.inputs, self.expected)

    def test_no_change_preserves_output_timestamp(self):
        with patch.object(build, 'reviewed_models', return_value=(self.rom, [(self.expected, self.records)])):
            result = build.build_parts(self.root)
            path = self.root / 'build/us/models/parts/models/bank03/0003.bin'
            stamp = path.stat().st_mtime_ns
            build.build_parts(self.root)
        self.assertEqual(stamp, path.stat().st_mtime_ns)
        self.assertEqual(result['model_count'], 1)
        self.assertTrue(result['matches_original'])

    def test_partition_preserves_index_gaps_and_unselected_storage(self):
        bank = build.rzip_archive.AssetBank(3, 0, 100, 0)
        entries = [build.rzip_archive.AssetEntry(3, 20, 30, 0x10, True),
                   build.rzip_archive.AssetEntry(8, 60, 80, 0x10, True)]
        self.assertEqual(build.partition(bank, entries), [(0, 'models/raw/00000000'),
            (20, 'models/bank03/0003'), (30, 'models/raw/0000001E'),
            (60, 'models/bank03/0008'), (80, 'models/raw/00000050')])
        with self.assertRaises(ValueError):
            build.partition(bank, entries + entries)

    def test_report_uses_actual_linker_object_and_independent_rom_target(self):
        linked = self.root / 'build/us/assets/models/bank03/0003.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.packed)]))
        output = self.root / 'report'
        def link(args, *, cwd, check):
            self.assertEqual((cwd / args[-1]).read_bytes(), self.packed)
            (cwd / 'target.o').write_bytes(object_file([('.data', 1, 3, self.packed)]))
        with patch.object(targets, 'ROOT', self.root), patch.object(targets.subprocess, 'run', side_effect=link):
            unit, item = targets.prepare_model(self.rom, self.expected, output=output)
            self.assertTrue(unit['complete'])
            self.assertEqual(unit['size'], len(self.packed))
            self.assertEqual(item['metadata']['progress_categories'], ['data'])
            self.assertEqual(len(unit['source_inputs']), 2)
            linked.write_bytes(object_file([('.data', 1, 3, bytes(len(self.packed)))]))
            with self.assertRaisesRegex(ValueError, 'model 03:0003 candidate differs from current editable inputs'):
                targets.prepare_model(self.rom, self.expected, output=output)

    def test_bank09_report_key_and_source_proof_do_not_collide_with_bank03(self):
        expected = dict(self.expected, bank=9)
        inputs = self.root / build.input_directory(3, 9)
        build.texture_build.publish_inputs(inputs, build.input_files(expected, self.records))
        linked = self.root / 'build/us/assets/models/bank09/0003.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.packed)]))
        def link(args, *, cwd, check):
            self.assertEqual(args[-1], 'models/bank09/0003.bin')
            (cwd / 'target.o').write_bytes(object_file([('.data', 1, 3, self.packed)]))
        with patch.object(targets, 'ROOT', self.root), patch.object(targets.subprocess, 'run', side_effect=link):
            unit, item = targets.prepare_model(self.rom, expected, output=self.root / 'report')
        self.assertEqual(unit['key'], 'model-09-0003')
        self.assertEqual(item['name'], 'assets/models/bank09/0003')
        self.assertTrue(unit['complete'])
        self.assertEqual(set(unit['source_inputs']), {
            'build/assets/model-build/us/09/0003/manifest.json',
            'build/assets/model-build/us/09/0003/model.json'})

    def test_reviewed_selection_checks_both_bank_partitions_and_consumer_proof(self):
        rom = self.root / 'rom.bin'
        rom.write_bytes(self.rom)
        contract = self.root / build.CONTRACT
        contract.parent.mkdir(parents=True)
        contract.write_text(json.dumps({'schema_version': 2, 'profile': 'us',
            'rom_sha1': self.expected['rom_sha1'], 'encoder': self.expected['encoder'],
            'banks': {'03': [3], '09': [3]}}))
        layout = {'normalized_sha1': [self.expected['rom_sha1']], 'asset_table': 0,
                  'game_format': 'rzip', 'game_start': 0, 'game_end': 6, 'game_vram': 0x15000000}
        banks = [build.rzip_archive.AssetBank(bank, 6, self.expected['rom_end'], 0) for bank in (3, 9)]
        entry = build.rzip_archive.AssetEntry(3, 6, self.expected['rom_end'], 0x10, True)
        def rows(profile, *, bank):
            return build.partition(banks[(3, 9).index(bank)], [entry]), self.expected['rom_end']
        with patch.object(build.model_assets, 'resolve_rom', return_value=(rom, layout)), \
                patch.object(build.rzip_archive, 'normalize_rom', return_value=(self.rom, 'z64')), \
                patch.object(build.rzip_archive, 'parse_asset_banks', return_value=banks), \
                patch.object(build.rzip_archive, 'parse_asset_entries', return_value=[entry]), \
                patch.object(build.rzip_archive, 'parse_game_archive', return_value=SimpleNamespace(code=b'code')) as archive, \
                patch.object(build, 'layout_bins', side_effect=rows) as partitions, \
                patch.object(build.model_assets, 'verify_direct_model_consumers') as consumers:
            _, selected = build.reviewed_models(self.root)
            self.assertEqual([e['bank'] for e, _ in selected], [3, 9])
            self.assertEqual(selected[0][0], self.expected)
            self.assertEqual([call.kwargs['bank'] for call in partitions.call_args_list], [3, 9])
            consumers.assert_called_once_with(b'code', 0x15000000)
            consumers.side_effect = ValueError('ROM direct-model consumer changed')
            for bank in (None, 9):
                with self.subTest(bank=bank), self.assertRaisesRegex(ValueError, 'consumer changed'):
                    build.reviewed_models(self.root, bank=bank)
            consumers.reset_mock()
            archive.reset_mock()
            _, scoped = build.reviewed_models(self.root, bank=3)
            self.assertEqual([e['bank'] for e, _ in scoped], [3])
            proof = build.build_parts(self.root, bank=3)
            self.assertEqual(proof['model_count'], 1)
            (self.inputs / 'notes.txt').write_text('bank03 work')
            recovered = build.recover_inputs(3, self.root, bank=3)
            self.assertEqual((Path(recovered['backup_directory']) / 'notes.txt').read_text(), 'bank03 work')
            consumers.assert_not_called()
            archive.assert_not_called()
            receipt03 = self.root / 'build/us/models/bank03/batch.json'
            before = receipt03.read_bytes(), receipt03.stat().st_mtime_ns
            self.assertFalse((self.root / 'build/us/models/batch.json').exists())
            self.assertFalse((self.root / build.input_directory(3, 9)).exists())
            with self.assertRaisesRegex(ValueError, 'consumer changed'):
                build.build_parts(self.root, bank=9)
            consumers.side_effect = None
            build.build_parts(self.root, bank=9)
            self.assertEqual((receipt03.read_bytes(), receipt03.stat().st_mtime_ns), before)
            receipt09 = json.loads((self.root / 'build/us/models/bank09/batch.json').read_text())
            self.assertEqual([e['bank'] for e in receipt09['models']], [9])
            partitions.side_effect = lambda profile, *, bank: ([(6, 'models/bank03/0003')], self.expected['rom_end'])
            with self.assertRaisesRegex(ValueError, 'bank-09 boundaries'):
                build.reviewed_models(self.root)

    def test_model_contract_rejects_unsupported_banks_and_malformed_selections(self):
        rom = self.root / 'rom.bin'
        rom.write_bytes(self.rom)
        contract = self.root / build.CONTRACT
        contract.parent.mkdir(parents=True)
        base = {'schema_version': 2, 'profile': 'us', 'rom_sha1': self.expected['rom_sha1'],
                'encoder': self.expected['encoder'], 'banks': {'03': [3], '09': [3]}}
        with patch.object(build.model_assets, 'resolve_rom', return_value=(rom, {
                'normalized_sha1': [self.expected['rom_sha1']], 'asset_table': 0})), \
                patch.object(build.rzip_archive, 'normalize_rom', return_value=(self.rom, 'z64')):
            for banks in ({'03': [3]}, {'03': [3], '04': [3]}, {'03': [3], '09': []},
                          {'03': [3], '09': [True]}, {'03': [3], '09': [3, 3]},
                          {'03': [3], '09': [3, 2]}, {'03': [3], '09': [-1]}):
                with self.subTest(banks=banks):
                    contract.write_text(json.dumps(dict(base, banks=banks)))
                    with self.assertRaisesRegex(ValueError, 'reconstruction contract|reconstruction selection'):
                        build.reviewed_models(self.root)
