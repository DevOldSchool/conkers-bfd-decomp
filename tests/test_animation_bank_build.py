"""Bank 0A provenance, reconstruction, input preservation and bounded credit."""
from copy import deepcopy
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch
from scripts import model_animation_build as codec, animation_bank_build as build
from test_model_animation_build import animation_payload


class AnimationBankBuildTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(); self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.fixtures = {}
        for bank, index, record in ((10, 0, codec.animation_records(animation_payload())),):
            data = build.encode_record(bank, record); stored = data
            payload = b'rawindex' + stored + b'uncredited'
            expected = {'bank': bank, 'rom_start': 6, 'rom_end': 6 + len(payload),
                        'original_sha256': build.sha256(payload), 'rom_ranges': [[14, 14 + len(stored)]],
                        'entries': [{'entry': index, 'rom_start': 14, 'rom_end': 14 + len(stored),
                                     'decoded_sha256': build.sha256(data), 'clip_count': 2, 'frame_count': 4}]}
            decoded, rom = {str(index): record}, b'prefix' + payload + b'tail'
            directory = self.root / build.input_directory(bank)
            build.texture_build.publish_inputs(directory, build.input_files(rom, expected, decoded))
            self.fixtures[bank] = rom, expected, decoded, payload, directory, len(stored)

    def test_build_preserves_sources_and_timestamps_and_repairs_parts(self):
        for bank, (rom, expected, decoded, payload, directory, size) in self.fixtures.items():
            before = build.input_hashes(directory, expected)
            with patch.object(build, 'reviewed_bank', return_value=(rom, expected, decoded)):
                proof = build.build_parts(bank, self.root)
                part = self.root / 'build/us/animation-bank/parts' / (build.part_name(bank) + '.bin')
                timestamp = part.stat().st_mtime_ns
                self.assertEqual(build.build_parts(bank, self.root), proof)
                self.assertEqual(part.stat().st_mtime_ns, timestamp)
                part.unlink(); build.build_parts(bank, self.root)
                self.assertEqual(part.read_bytes(), payload)
                self.assertEqual(proof['rebuilt_bytes'], size)
            self.assertEqual(build.input_hashes(directory, expected), before)

    def test_missing_or_changed_sources_fail_without_overwriting_and_recover_backs_up(self):
        bank = 10; rom, expected, decoded, payload, directory, _ = self.fixtures[bank]
        originals = build.input_files(rom, expected, decoded)
        for name, value in (('animations.json', None), ('animations.json', b'{}'), ('animations.json', b'bad'),
                            ('manifest.json', b'{}'), ('backing.bin', b'changed')):
            for filename, data in originals.items(): (directory / filename).write_bytes(data)
            path = directory / name
            if value is None: path.unlink()
            else: path.write_bytes(value)
            before = {p.name: p.read_bytes() for p in directory.iterdir()}
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): build.packed_bank(directory, expected)
            self.assertEqual({p.name: p.read_bytes() for p in directory.iterdir()}, before)
        with patch.object(build, 'reviewed_bank', return_value=(rom, expected, decoded)):
            recovered = build.recover_inputs(bank, self.root)
        self.assertEqual((Path(recovered['backup_directory']) / 'backing.bin').read_bytes(), b'changed')
        self.assertEqual(build.packed_bank(directory, expected)[0], payload)

    def test_native_frame_count_and_source_race_are_checked(self):
        rom, expected, decoded, payload, directory, _ = self.fixtures[10]
        bad = deepcopy(expected); bad['entries'][0]['frame_count'] = 3
        with patch.object(build, 'input_hashes', return_value={}):
            with self.assertRaisesRegex(ValueError, 'counts differ'): build.packed_bank(directory, bad)
        encode = build.encode_record
        def changing(*args):
            data = encode(*args)
            with (directory / 'animations.json').open('a') as file: file.write(' ')
            return data
        with patch.object(build, 'encode_record', side_effect=changing):
            with self.assertRaisesRegex(ValueError, 'changed during packing'): build.packed_bank(directory, expected)

    def test_report_credits_only_rebuilt_ranges_of_actual_linked_banks(self):
        from test_objdiff_data_targets import object_file, targets
        for bank, (rom, expected, decoded, payload, directory, size) in self.fixtures.items():
            linked = self.root / 'build/us/assets' / (build.part_name(bank) + '.o')
            linked.parent.mkdir(parents=True, exist_ok=True)
            linked.write_bytes(object_file([('.data', 1, 3, payload)]))
            output = self.root / 'report'
            with patch.object(targets, 'ROOT', self.root):
                unit, item = targets.prepare_animation_bank_object(rom, expected, output=output)
                self.assertEqual(unit['rom_ranges'], expected['rom_ranges'])
                self.assertEqual(unit['report_data_bytes'], size)
                self.assertEqual(item['name'], f'assets/animations/bank{bank:02X}')
                native = targets.sections((output / f'animation-bank{bank:02X}/base.o').read_bytes(), 1)['.data'][1]
                self.assertEqual(native, rom[14:14 + size])
                linked.write_bytes(object_file([('.data', 1, 3, bytes(len(payload)))]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'): targets.prepare_animation_bank_object(rom, expected, output=output)

    def test_unknown_runtime_duration_and_other_formats_are_rejected(self):
        record = codec.animation_records(animation_payload())
        record['clips'][0]['header_bytes'][3] = 255
        with self.assertRaisesRegex(ValueError, 'runtime duration is unconfirmed'):
            build.encode_record(10, record)
        record['format'] = 'character-animation-fixed-duration'
        with self.assertRaisesRegex(ValueError, 'descriptor-duration'):
            build.encode_record(10, record)
        for bank in (True, 2, 17):
            with self.assertRaises(ValueError): build.input_directory(bank)

    def test_changed_semantic_channel_is_preserved_and_rejected(self):
        _, expected, decoded, _, directory, _ = self.fixtures[10]
        changed = deepcopy(decoded)
        changed['0']['clips'][0]['frames'][0]['root_offsets'][0] ^= 1
        source = directory / 'animations.json'
        source.write_text(json.dumps(changed))
        before = source.read_bytes()
        with self.assertRaisesRegex(ValueError, 'original decoded data'):
            build.packed_bank(directory, expected)
        self.assertEqual(source.read_bytes(), before)
