"""ROM-free source preservation and exact-range tests for native save widths."""
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import asset_directory_build as build
from scripts import save_layout_codec as codec, save_layout_inputs as inputs


class SaveLayoutTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.source = {'format': codec.FORMAT, 'bit_widths': [i % 41 for i in range(69)]}
        self.widths = codec.encode(self.source)
        self.payload = struct.pack('>2I', 8, 0x80000045) + self.widths + b'xyz'
        self.rom = b'prefix' + self.payload + b'after'
        self.expected = {'key': 'bank07', 'part': build.PARTS['bank07'],
                         'rom_start': 6, 'rom_end': 86, 'rom_ranges': [[6, 14]],
                         'directory_size': 8, 'directory_sha256': build.sha256(self.payload[:8]),
                         'original_sha256': build.sha256(self.payload)}
        self.table = build.codec.decode(self.payload[:8])
        self.directory = self.root / build.input_directory('bank07')
        self.old = build.input_files(self.rom, self.expected, self.table)
        build.texture_build.publish_inputs(self.directory, self.old)

    def run_build(self):
        with patch.object(build, 'reviewed_directories', return_value=(self.rom, [(self.expected, self.table)])):
            return build.build_parts(self.root)

    def test_source_width_types_bounds_and_count(self):
        self.assertEqual(codec.decode(self.widths), self.source)
        for value in (True, -1, 65, 2.5, '3'):
            source = dict(self.source, bit_widths=[value] + self.source['bit_widths'][1:])
            with self.subTest(value=value), self.assertRaises(ValueError):
                codec.encode(source)
        for data in (bytes(68), bytes(70), bytes([65]) * 69):
            with self.assertRaises(ValueError):
                codec.decode(data)
        for source in ({}, dict(self.source, raw='00'), dict(self.source, format='unknown')):
            with self.assertRaises(ValueError):
                codec.encode(source)
        self.assertEqual(codec.encode(dict(self.source, bit_widths=[64] * 69)), bytes([64]) * 69)

    def test_existing_directory_sources_preserved_and_sources_used(self):
        self.run_build()
        for name, original in self.old.items():
            self.assertEqual((self.directory / name).read_bytes(), original)
        packed, spans, hashes = build.packed_directory(self.directory, self.expected, include_save_layout=True)
        self.assertEqual(packed, self.payload)
        self.assertEqual(spans, [(0, self.payload[:8])])
        self.assertIn('save-layout/widths.json', hashes)
        path = self.root / 'build/us/asset-directories/parts/asset_bank_07.bin'
        stamp = path.stat().st_mtime_ns
        self.run_build()
        self.assertEqual(path.stat().st_mtime_ns, stamp)
        path.unlink()
        self.run_build()
        self.assertEqual(path.read_bytes(), self.payload)

    def test_every_width_mutation_changes_output_and_is_rejected(self):
        self.run_build()
        file = self.directory / inputs.DIRECTORY / 'widths.json'
        for index in range(69):
            source = codec.decode(self.widths)
            source['bit_widths'][index] += 1
            fresh = codec.encode(source)
            self.assertEqual([i for i, (a, b) in enumerate(zip(fresh, self.widths)) if a != b], [index])
            file.write_text(json.dumps(source))
            before = file.read_bytes()
            with self.subTest(index=index), self.assertRaisesRegex(ValueError, 'no longer reproduce'):
                self.run_build()
            self.assertEqual(file.read_bytes(), before)

    def test_missing_invalid_sources_preserved_and_explicit_recovery_backs_up(self):
        self.run_build()
        directory = self.directory / inputs.DIRECTORY
        original = {p.name: p.read_bytes() for p in directory.iterdir()}
        for name, value in (('widths.json', None), ('widths.json', b'bad'), ('manifest.json', b'{}')):
            for filename, data in original.items():
                (directory / filename).write_bytes(data)
            file = directory / name
            if value is None:
                file.unlink()
            else:
                file.write_bytes(value)
            before = {p.name: p.read_bytes() for p in directory.iterdir()}
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                self.run_build()
            self.assertEqual({p.name: p.read_bytes() for p in directory.iterdir()}, before)
        with patch.object(build, 'reviewed_directories', return_value=(self.rom, [(self.expected, self.table)])):
            recovered = build.recover_inputs('bank07', self.root)
        self.assertEqual((Path(recovered['backup_directory']) / inputs.DIRECTORY / 'manifest.json').read_bytes(), b'{}')
        self.run_build()
        self.assertEqual((self.directory / inputs.DIRECTORY / 'widths.json').read_bytes(), original['widths.json'])

    def test_source_race_rejected(self):
        self.run_build()
        encode = inputs.encoded
        def changed(*args):
            result = encode(*args)
            with (self.directory / inputs.DIRECTORY / 'widths.json').open('a') as stream:
                stream.write(' ')
            return result
        with patch.object(build.save_layout_inputs, 'encoded', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                self.run_build()

    def test_report_disjoint_widths_excludes_directory_and_trailing_bytes(self):
        from test_objdiff_data_targets import object_file, targets
        self.run_build()
        linked = self.root / 'build/us/assets/asset_bank_07.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        output = self.root / 'report'
        with patch.object(targets, 'ROOT', self.root):
            unit, _ = targets.prepare_save_layout_object(self.rom, self.expected, output=output)
            header, _ = targets.prepare_asset_directory(self.rom, self.expected, output=output)
            self.assertEqual(unit['report_data_bytes'], 69)
            self.assertEqual(unit['rom_ranges'], [[14, 83]])
            self.assertEqual(header['rom_ranges'], [[6, 14]])
            self.assertEqual(targets.sections((output / unit['base_path']).read_bytes(), 1)['.data'][1], self.widths)
            for at in (0, 8, 79):
                changed = bytearray(self.payload)
                changed[at] ^= 1
                linked.write_bytes(object_file([('.data', 1, 3, bytes(changed))]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'):
                    targets.prepare_save_layout_object(self.rom, self.expected, output=output)
