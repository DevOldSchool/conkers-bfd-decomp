"""Bank index composition, source preservation and actual linker ownership."""
from copy import deepcopy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import bank_index_inputs as index, asset_directory_codec as codec
from scripts import sprite_build, visibility_build, route_build, animation_control_build, asset_directory_build
import test_sprite_build, test_visibility_build, test_route_build, test_animation_control_build
import objdiff_data_targets as report
import binary_object


class BankIndexTests(unittest.TestCase):
    def test_alignment_is_minimal_absolute_and_ignores_empty_entries(self):
        source = codec.decode(struct.pack('>IIII', 16, 3, 999, 0x80000000))
        self.assertEqual(index.alignment_spans(source, 8, 32), {(27, 32): bytes(5)})
        for end in (31, 33, 40):
            with self.assertRaises(ValueError): index.alignment_spans(source, 8, end)
        bad = deepcopy(source); bad['entries'][0]['relative_offset'] = 24
        with self.assertRaises(ValueError): index.alignment_spans(bad, 8, 40)

    def test_all_five_builders_generate_index_and_preserve_payload_ownership(self):
        cases = ((sprite_build, test_sprite_build.SpriteBuildTests, 0),
                 (visibility_build, test_visibility_build.VisibilityBuildTests, 5),
                 (animation_control_build, test_animation_control_build.AnimationControlBuildTests, 15),
                 (route_build, test_route_build.RouteBuildTests, 16),
                 (route_build, test_route_build.RouteBuildTests, 25))
        for module, fixture, bank in cases:
            with self.subTest(bank=bank):
                fixture.setUp(self)
                if bank in (0, 5):
                    old, expected, decoded, directory = self.payload, self.expected, self.decoded, self.directory
                    source, part, family = module.INPUT_DIRECTORY, module.PART_NAME, 'sprites' if bank == 0 else 'visibility'
                else:
                    _, expected, decoded, old, directory, _ = self.fixtures[bank]
                    source, part = module.input_directory(bank), module.part_name(bank)
                    family = 'animation-control' if bank == 15 else 'routes'
                expected = deepcopy(expected); row = expected['entries'][0]
                stored = old[row['rom_start'] - expected['rom_start']:row['rom_end'] - expected['rom_start']]
                n = row['entry'] + 2; table_size = n * 8
                entries = [{'relative_offset': table_size if i == 0 else 0, 'stored_size': 0, 'flags': 0} for i in range(n)]
                entries[row['entry']] = {'relative_offset': table_size, 'stored_size': len(stored), 'flags': 0}
                at = table_size + len(stored); gap = bytes((-at) % 8)
                entries[-1] = {'relative_offset': at + len(gap), 'stored_size': 3, 'flags': 8}
                native = {'format': codec.FORMAT, 'entries': entries}
                payload = codec.encode(native) + stored + gap + b'raw' + bytes(5)
                expected.update(bank=bank, rom_start=8, rom_end=8 + len(payload), original_sha256=module.sha256(payload))
                row.update(rom_start=8 + table_size, rom_end=8 + table_size + len(stored))
                expected['rom_ranges'] = [[row['rom_start'], row['rom_end']]]
                rom = bytes(8) + payload
                for name, data in module.input_files(rom, expected, decoded).items(): (directory / name).write_bytes(data)
                old_hashes = module.input_hashes(directory, expected)
                args = (self.root,) if bank in (0, 5) else (bank, self.root)
                with patch.object(module, 'reviewed_bank', return_value=(rom, expected, decoded)):
                    module.build_parts(*args, include_directory=True)
                    packed, spans, hashes = module.packed_bank(directory, expected, include_directory=True)
                    self.assertEqual(packed, payload)
                    self.assertEqual(spans, [(table_size, stored)])
                    self.assertEqual(module.input_hashes(directory, expected), old_hashes)
                    self.assertEqual(hashes.keys() - old_hashes.keys(), {'bank-index/manifest.json', 'bank-index/index.json'})
                    fresh = index.encoded(directory, expected, payload)
                    self.assertEqual(fresh[0], (0, codec.encode(native)))
                    self.assertEqual(sum(len(data) for _, data in fresh), table_size + len(gap) + 5)
                    linked = self.root / ('build/us/assets/' + part + '.o'); linked.parent.mkdir(parents=True, exist_ok=True)
                    linked.write_bytes(binary_object.binary_object(packed, part + '.bin'))
                    output = self.root / 'report'
                    with patch.object(report, 'ROOT', self.root):
                        unit, _ = report.prepare_bank_index_object(rom, expected, module=module, source=source,
                            part=part, options={'include_directory': True}, output=output)
                        self.assertEqual(unit['report_data_bytes'], sum(len(data) for _, data in fresh))
                        bad = bytearray(payload); bad[0] ^= 1
                        linked.write_bytes(binary_object.binary_object(bad, part + '.bin'))
                        with self.assertRaisesRegex(ValueError, 'linked candidate'):
                            report.prepare_bank_index_object(rom, expected, module=module, source=source,
                                part=part, options={'include_directory': True}, output=output)
                    output_part = self.root / f'build/us/{family}/parts/{part}.bin'
                    stamp = output_part.stat().st_mtime_ns
                    module.build_parts(*args, include_directory=True)
                    self.assertEqual(output_part.stat().st_mtime_ns, stamp)
                    output_part.unlink(); module.build_parts(*args, include_directory=True)
                    for name in ('manifest.json', 'index.json'):
                        path = directory / 'bank-index' / name; saved = path.read_bytes()
                        path.write_text('{}'); edited = path.read_bytes()
                        with self.assertRaises(ValueError): module.build_parts(*args, include_directory=True)
                        self.assertEqual(path.read_bytes(), edited)
                        self.assertEqual(output_part.read_bytes(), payload)
                        path.unlink()
                        with self.assertRaises(ValueError): module.build_parts(*args, include_directory=True)
                        self.assertFalse(path.exists()); path.write_bytes(saved)
                    path = directory / 'bank-index/index.json'; saved = path.read_bytes()
                    bad = json.loads(saved); bad['entries'][-1]['flags'] ^= 1; path.write_text(json.dumps(bad))
                    with self.assertRaises(ValueError): module.build_parts(*args, include_directory=True)
                    recovery = module.recover_inputs(*args)
                    self.assertEqual((Path(recovery['backup_directory']) / 'bank-index/index.json').read_text(), json.dumps(bad))
                    module.build_parts(*args, include_directory=True)
                    self.assertEqual(path.read_bytes(), saved)

    def test_nested_alignment_uses_authored_indexes_and_does_not_credit_payload(self):
        with tempfile.TemporaryDirectory() as tmp:
            directory = Path(tmp)
            outer = codec.decode(struct.pack('>II', 8, 16 | 0x80000000))
            inner = codec.decode(struct.pack('>II', 8, 3 | 0x80000000))
            (directory / 'directory.json').write_text(json.dumps(outer))
            for key, child, source in [('bank1A', 'dialogue/dialogue.json', {'languages': [{'directory': inner}]}),
                                       ('bank1C', 'menu-text/text.json', {'directory': inner})]:
                path = directory / child; path.parent.mkdir(); path.write_text(json.dumps(source))
                self.assertEqual(index.existing_alignment(directory, {'key': key, 'rom_start': 8, 'rom_end': 32}), [(19, bytes(5))])

    def test_existing_directory_builder_composes_alignment_and_tracks_source(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp); directory = root / asset_directory_build.input_directory('bank0D')
            directory.mkdir(parents=True)
            source = codec.decode(struct.pack('>II', 8, 3 | 0x80000000))
            payload = codec.encode(source) + b'raw' + bytes(5)
            expected = {'key': 'bank0D', 'rom_start': 8, 'rom_end': 24, 'part': 'asset_bank_0d',
                        'original_sha256': index.sha(payload), 'directory_size': 8,
                        'directory_sha256': index.sha(payload[:8]), 'rom_ranges': [[8, 16]]}
            rom = bytes(8) + payload
            for name, data in asset_directory_build.input_files(rom, expected, source).items():
                (directory / name).write_bytes(data)
            with patch.object(asset_directory_build, 'reviewed_directories', return_value=(rom, [(expected, source)])):
                asset_directory_build.build_parts(root, include_alignment=True)
            linked = root / 'build/us/assets/asset_bank_0d.o'; linked.parent.mkdir(parents=True)
            linked.write_bytes(binary_object.binary_object(payload, 'asset_bank_0d.bin'))
            with patch.object(report, 'ROOT', root):
                unit, _ = report.prepare_bank_index_object(rom, expected, module=asset_directory_build,
                    source=directory.relative_to(root), part='asset_bank_0d', options={'include_alignment': True},
                    alignment=True, output=root / 'report')
                self.assertEqual(unit['rom_ranges'], [[19, 24]])
                self.assertEqual(unit['report_data_bytes'], 5)
            bad = deepcopy(source); bad['entries'][0]['stored_size'] += 1
            (directory / 'directory.json').write_text(json.dumps(bad))
            with self.assertRaises(ValueError): asset_directory_build.packed_directory(directory, expected, include_alignment=True)
