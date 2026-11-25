"""Standalone padding generation, source preservation and actual-object proof."""
import copy
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from scripts import model_alignment_build as build


class ModelAlignmentTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory()
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.source = {'format': build.directories.codec.FORMAT, 'entries': [
            {'relative_offset': 16, 'stored_size': 3, 'flags': 0},
            {'relative_offset': 24, 'stored_size': 2, 'flags': 8}]}
        table = build.directories.codec.encode(self.source)
        self.rom = bytes(0x100) + table + b'ABC' + bytes(5) + b'DE' + bytes(6)
        self.parent = {'key': 'bank01', 'rom_start': 0x100, 'rom_end': 0x110,
                       'directory_size': 16, 'directory_sha256': build.directories.sha256(table),
                       'original_sha256': build.directories.sha256(table)}
        self.directory = self.root / build.directories.input_directory('bank01')
        build.directories.texture_build.publish_inputs(
            self.directory, build.directories.input_files(self.rom, self.parent, self.source))
        self.outer = ({'key': 'outer', 'rom_start': 0x80}, {'entries': [
            {}, {'relative_offset': 0x80, 'stored_size': 0x20}]})
        profile = self.root / 'config/profiles/us.yaml'
        profile.parent.mkdir(parents=True)
        profile.write_text('''segments:
  - start: 0x100
    type: group
    subsegments:
      - [0x100, bin, models/raw/00000100]
      - [0x110, bin, models/bank01/0000]
      - [0x113, bin, models/raw/00000113]
      - [0x118, bin, models/bank01/0001]
      - [0x11A, bin, models/raw/0000011A]
  - [0x120]
''')
        self.review = patch.object(build.directories, 'reviewed_directories',
            return_value=(self.rom, [self.outer, (self.parent, self.source)]))
        self.review.start()
        self.addCleanup(self.review.stop)

    def test_minimal_absolute_alignment_empty_entries_and_bounds(self):
        spans = build.alignment_spans(self.source, 0x100, 0x120)
        self.assertEqual(spans, {(0x113, 0x118): bytes(5), (0x11A, 0x120): bytes(6)})
        for end in (0x10F, 0x119, 0x121, 0x128):
            with self.assertRaises(ValueError):
                build.alignment_spans(self.source, 0x100, end)
        extra = copy.deepcopy(self.source)
        extra['entries'][1]['relative_offset'] = 32
        with self.assertRaisesRegex(ValueError, 'minimal eight-byte'):
            build.alignment_spans(extra, 0x100, 0x128)
        empty = {'format': self.source['format'], 'entries': [
            {'relative_offset': 24, 'stored_size': 0, 'flags': 0},
            {'relative_offset': 26, 'stored_size': 1, 'flags': 0},
            {'relative_offset': 34, 'stored_size': 1, 'flags': 8}]}
        self.assertEqual(build.alignment_spans(empty, 6, 48),
                         {(30, 32): bytes(2), (33, 40): bytes(7), (41, 48): bytes(7)})

    def test_profile_selection_and_independent_zero_reference(self):
        rom, parts = build.reviewed(self.root)
        self.assertEqual(rom, self.rom)
        self.assertEqual([p['rom_start'] for p in parts], [0x113, 0x11A])
        changed = bytearray(self.rom)
        changed[0x113] = 1
        with patch.object(build.directories, 'reviewed_directories',
                          return_value=(bytes(changed), [self.outer, (self.parent, self.source)])):
            with self.assertRaisesRegex(ValueError, 'nonzero'):
                build.reviewed(self.root)
        with patch.object(build, 'selected_parts', return_value=[{'part': 'models/raw/bad', 'rom_start': 0x111, 'rom_end': 0x118}]):
            with self.assertRaisesRegex(ValueError, 'complete model directory gap'):
                build.reviewed(self.root)

    def test_build_preserves_sources_and_unchanged_outputs(self):
        before = {p.name: p.read_bytes() for p in self.directory.iterdir()}
        parts = build.build_parts(self.root)
        path = self.root / 'build/us/model-alignment/parts/models/raw/00000113.bin'
        self.assertEqual(path.read_bytes(), bytes(5))
        stamp = path.stat().st_mtime_ns
        build.build_parts(self.root)
        self.assertEqual(path.stat().st_mtime_ns, stamp)
        self.assertEqual({p.name: p.read_bytes() for p in self.directory.iterdir()}, before)
        path.unlink()
        build.build_parts(self.root)
        self.assertEqual(path.read_bytes(), bytes(5))
        self.assertEqual(len(parts), 2)

    def test_edited_and_missing_sources_fail_without_replacement(self):
        path = self.directory / 'directory.json'
        original = path.read_bytes()
        for index in range(2):
            for field in ('relative_offset', 'stored_size', 'flags'):
                changed = copy.deepcopy(self.source)
                changed['entries'][index][field] += 1
                path.write_text(json.dumps(changed))
                with self.assertRaises(ValueError):
                    build.build_parts(self.root)
                self.assertEqual(json.loads(path.read_text()), changed)
        path.unlink()
        with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
            build.build_parts(self.root)
        self.assertFalse(path.exists())
        path.write_bytes(original)
        backing = self.directory / 'backing.bin'
        backing.write_bytes(b'wrong')
        with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
            build.build_parts(self.root)
        self.assertEqual(backing.read_bytes(), b'wrong')

    def test_source_race_fails_before_output(self):
        original = build.alignment_spans
        def changed(*args):
            result = original(*args)
            with (self.directory / 'directory.json').open('a') as stream:
                stream.write(' ')
            return result
        _, parts = build.reviewed(self.root)
        with patch.object(build, 'alignment_spans', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_part(self.root, parts[0])

    def test_report_reads_actual_linker_object_and_checks_every_byte(self):
        from test_objdiff_data_targets import targets
        from scripts.binary_object import binary_object
        _, parts = build.reviewed(self.root)
        part = parts[0]
        path = self.root / ('build/us/assets/' + part['part'] + '.o')
        path.parent.mkdir(parents=True)
        path.write_bytes(binary_object(bytes(5), part['part'] + '.bin'))
        with patch.object(targets, 'ROOT', self.root):
            unit, _ = targets.prepare_model_alignment_part(self.rom, part, output=self.root / 'report')
            self.assertEqual(unit['report_data_bytes'], 5)
            self.assertTrue(unit['complete'])
            self.assertEqual((unit['rom_start'], unit['rom_end']), (0x113, 0x118))
            for offset in range(5):
                changed = bytearray(5)
                changed[offset] = 1
                path.write_bytes(binary_object(changed, part['part'] + '.bin'))
                with self.assertRaisesRegex(ValueError, 'candidate differs'):
                    targets.prepare_model_alignment_part(self.rom, part, output=self.root / 'report')
