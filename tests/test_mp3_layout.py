"""Typed MP3 index, derived alignment and actual linker-object coverage."""
from copy import deepcopy
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from scripts import mp3_bank as bank, mp3_layout as layout
from test_mp3_bank import bank_fixture


class Mp3LayoutTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(); self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.rom, self.family = bank_fixture()
        self.expected = bank.describe_bank(self.rom, self.family)
        self.directory = self.root / layout.INPUT_DIRECTORY
        bank.initialize_inputs(self.directory, self.expected, self.rom)
        self.prior = bank.input_hashes(self.directory, self.expected)
        layout.ensure_inputs(self.directory, self.expected)

    def test_index_empty_slots_flags_and_generated_alignment(self):
        manifest, source = layout.reviewed(self.expected)
        self.assertEqual(source['entries'][1], {'relative_offset': 104, 'stored_size': 0, 'flags': 0})
        self.assertEqual(source['entries'][2]['flags'], 8)
        parts = layout.encoded(self.directory, self.expected)
        self.assertEqual([p['name'] for p, _ in parts], ['index', 'padding/00000066', 'padding/000000B6'])
        for part, data in parts:
            start = 16 + part['offset']
            self.assertEqual(data, self.rom[start:start + part['size']])
        packed, hashes = bank.packed_bank(self.directory, self.expected, include_layout=True)
        self.assertEqual(packed, self.rom[16:])
        self.assertEqual({key: hashes[key] for key in self.prior}, self.prior)
        self.assertEqual(set(hashes) - set(self.prior), {'layout/index.json', 'layout/manifest.json'})
        for mutate in (lambda x: x['records'][2].__setitem__(0, 112),
                       lambda x: x['padding'][0].update(size=10),
                       lambda x: x['padding'][0].update(sha256='0'*64),
                       lambda x: x['records'][2].__setitem__(1, 0x1000004e)):
            expected = deepcopy(self.expected); mutate(expected)
            with self.assertRaises(ValueError): layout.reviewed(expected)

    def test_changed_index_fields_fail_without_overwrite(self):
        path = self.directory / 'layout/index.json'; original = json.loads(path.read_text())
        for i, key, value in ((0, 'relative_offset', 32), (0, 'stored_size', 79),
                              (1, 'relative_offset', 0), (2, 'flags', 0), (1, 'stored_size', True)):
            record = deepcopy(original); record['entries'][i][key] = value
            path.write_text(json.dumps(record)); before = path.read_bytes()
            with self.assertRaises(ValueError): bank.packed_bank(self.directory, self.expected, include_layout=True)
            self.assertEqual(path.read_bytes(), before)

    def test_missing_invalid_child_and_recovery_preserve_parent(self):
        child = self.directory / 'layout'; originals = {p.name: p.read_bytes() for p in child.iterdir()}
        for name, value in (('index.json', None), ('index.json', b'bad'), ('manifest.json', None), ('manifest.json', b'{}')):
            for filename, data in originals.items(): (child / filename).write_bytes(data)
            path = child / name
            if value is None: path.unlink()
            else: path.write_bytes(value)
            before = {p.name: p.read_bytes() for p in child.iterdir()}
            layout.ensure_inputs(self.directory, self.expected)
            with self.assertRaises((ValueError, OSError)):
                bank.packed_bank(self.directory, self.expected, include_layout=True)
            self.assertEqual(before, {p.name: p.read_bytes() for p in child.iterdir()})
        result = layout.recover(self.directory, self.expected, self.root / 'recovery')
        self.assertEqual((Path(result['backup_directory']) / 'manifest.json').read_bytes(), b'{}')
        self.assertEqual(bank.input_hashes(self.directory, self.expected), self.prior)
        self.assertEqual(bank.packed_bank(self.directory, self.expected, include_layout=True)[0], self.rom[16:])

    def test_stream_edits_remain_edits_and_bad_padding_is_rejected(self):
        path = self.directory / 'streams/0000.mp3'
        changed = bytearray(path.read_bytes()); changed[20] ^= 1; path.write_bytes(changed)
        packed, _ = bank.packed_bank(self.directory, self.expected, include_layout=True)
        self.assertEqual(packed[24:102], changed)
        self.assertEqual(path.read_bytes(), changed)
        padding = self.directory / self.expected['padding'][0]['file']
        padding.write_bytes(b'xx')
        with self.assertRaisesRegex(ValueError, 'alignment padding changed'):
            bank.packed_bank(self.directory, self.expected, include_layout=True)

    def test_source_race_rejected(self):
        original = bank.mp3_assets.parse_mp3_cue_stream
        def changing(data):
            with (self.directory / 'layout/index.json').open('a') as file: file.write(' ')
            return original(data)
        with patch.object(bank.mp3_assets, 'parse_mp3_cue_stream', side_effect=changing):
            with self.assertRaisesRegex(ValueError, 'inputs changed'):
                bank.packed_bank(self.directory, self.expected, include_layout=True)

    def test_each_actual_link_object_compared_and_no_stream_credit(self):
        from test_objdiff_data_targets import object_file, targets
        parts = layout.encoded(self.directory, self.expected)
        output = self.root / 'report'
        with patch.object(targets, 'ROOT', self.root):
            units = []
            for part, payload in parts:
                linked = self.root / ('build/us/assets/audio/mp3/' + part['name'] + '.o')
                linked.parent.mkdir(parents=True, exist_ok=True)
                linked.write_bytes(object_file([('.data', 1, 3, payload)]))
                unit, item = targets.prepare_mp3_layout_part(self.rom, self.expected, part, payload, output=output)
                units.append(unit)
                self.assertEqual(item['name'], 'assets/audio/mp3/' + part['name'])
                self.assertEqual(unit['rom_start'], 16 + part['offset'])
                self.assertEqual(unit['report_data_bytes'], len(payload))
                changed = bytearray(payload); changed[0] ^= 1
                linked.write_bytes(object_file([('.data', 1, 3, changed)]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'):
                    targets.prepare_mp3_layout_part(self.rom, self.expected, part, payload, output=output)
            self.assertEqual(sum(u['report_data_bytes'] for u in units), 28)
            for unit in units:
                for stream in self.expected['streams']:
                    start = 16 + stream['offset']
                    self.assertFalse(unit['rom_start'] < start + stream['size'] and start < unit['rom_end'])
