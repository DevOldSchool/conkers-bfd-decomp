"""Native scene scalar widths, counted IDs, sparse ownership and preservation."""
import copy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import asset_directory_build as build
from scripts import scene_header_codec as codec, scene_header_inputs as inputs


class SceneHeaderTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory()
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.source = {'format': codec.FORMAT, 'fields': {
            codec.key(off, kind): (-3 if kind.startswith('s') else 7) for off, kind in codec.FIELDS},
            'lookup_ids': [0, 65535]}
        self.source['fields']['u8_12'] = 2
        header = bytearray([0xCC] * 76)
        for off, kind in codec.FIELDS:
            struct.pack_into('>' + codec.FORMATS[kind][0], header, off, self.source['fields'][codec.key(off, kind)])
        self.container = struct.pack('>4I', 16, 76, 96, 0x80000004) + header + bytes(4) + b'\0\0\xff\xff' + bytes(4)
        backing = bytearray(552)
        for i in range(69):
            blob = b'' if i in (17, 68) else self.container
            struct.pack_into('>II', backing, i * 8, len(backing), len(blob) | (0x80000000 if i == 68 else 0))
            backing.extend(blob)
        self.payload = bytes(backing)
        self.rom = b'prefix' + self.payload + b'tail'
        self.expected = {'key': 'bank15', 'part': build.PARTS['bank15'],
                         'rom_start': 6, 'rom_end': 6 + len(backing), 'rom_ranges': [[6, 558]],
                         'directory_size': 552, 'directory_sha256': build.sha256(self.payload[:552]),
                         'original_sha256': build.sha256(self.payload)}
        self.table = build.codec.decode(self.payload[:552])
        self.directory = self.root / build.input_directory('bank15')
        self.old = build.input_files(self.rom, self.expected, self.table)
        build.texture_build.publish_inputs(self.directory, self.old)

    def run_build(self):
        with patch.object(build, 'reviewed_directories', return_value=(self.rom, [(self.expected, self.table)])):
            return build.build_parts(self.root)

    def test_native_scalar_widths_counted_ids_and_sparse_ranges(self):
        self.assertEqual(codec.decode(self.container), self.source)
        spans = codec.encode(self.source)
        covered = set()
        for offset, data in spans:
            self.assertEqual(self.container[offset:offset + len(data)], data)
            covered.update(range(offset, offset + len(data)))
        self.assertEqual(len(covered), len(self.container) - 12)
        excluded = {16 + i for i in (4, 0x15, 0x20, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x47, 0x48)}
        self.assertEqual(set(range(len(self.container))) - covered, excluded)
        for at in (0, 4, 8, 12, 92, 95, 100, 103):
            changed = bytearray(self.container); changed[at] ^= 1
            with self.assertRaises(ValueError): codec.decode(changed)
        for data in (self.container[:95], self.container[:-1], self.container + bytes(8)):
            with self.assertRaises(ValueError): codec.decode(data)
        changed = bytearray(self.container); changed[20] = 1
        self.assertEqual(codec.decode(changed), self.source)  # Unclaimed byte, never exported.

    def test_strict_source_schema_and_native_domains(self):
        for off, kind in codec.FIELDS:
            _, low, high = codec.FORMATS[kind]
            for value in (True, low - 1, high + 1, 1.5):
                changed = copy.deepcopy(self.source)
                changed['fields'][codec.key(off, kind)] = value
                with self.assertRaises(ValueError): codec.encode(changed)
        for value in (True, -1, 65536, 1.5):
            changed = copy.deepcopy(self.source); changed['lookup_ids'][0] = value
            with self.assertRaises(ValueError): codec.encode(changed)
        for extra in ({'raw': '00'}, {'u8_04': 0}):
            changed = copy.deepcopy(self.source); changed['fields'].update(extra)
            with self.assertRaises(ValueError): codec.encode(changed)
        changed = copy.deepcopy(self.source); changed['lookup_ids'].append(1)
        with self.assertRaisesRegex(ValueError, 'count'): codec.encode(changed)

    def test_inputs_and_outputs_preserved(self):
        self.run_build()
        for name, value in self.old.items(): self.assertEqual((self.directory / name).read_bytes(), value)
        packed, spans, hashes = build.packed_directory(self.directory, self.expected, include_scene_headers=True)
        self.assertEqual(packed, self.payload)
        self.assertEqual(spans, [(0, self.payload[:552])])
        self.assertIn('scene-headers/scenes.json', hashes)
        path = self.root / 'build/us/asset-directories/parts/asset_bank_15.bin'
        stamp = path.stat().st_mtime_ns
        self.run_build(); self.assertEqual(path.stat().st_mtime_ns, stamp)
        path.unlink(); self.run_build(); self.assertEqual(path.read_bytes(), self.payload)

    def test_edits_deletions_and_recovery_preserve_user_files(self):
        self.run_build()
        path = self.directory / inputs.DIRECTORY / 'scenes.json'
        original = json.loads(path.read_text())
        for which in ('header', 'lookup', 'selection'):
            changed = copy.deepcopy(original); row = changed['records'][0]
            if which == 'header': row['scene']['fields']['s16_16'] += 1
            elif which == 'lookup': row['scene']['lookup_ids'][0] += 1
            else: row['index'] = True
            path.write_text(json.dumps(changed))
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): self.run_build()
            self.assertEqual(json.loads(path.read_text()), changed)
        path.unlink()
        with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): self.run_build()
        self.assertFalse(path.exists())
        path.write_text('edited source')
        with patch.object(build, 'reviewed_directories', return_value=(self.rom, [(self.expected, self.table)])):
            recovered = build.recover_inputs('bank15', self.root)
        self.assertEqual((Path(recovered['backup_directory']) / inputs.DIRECTORY / 'scenes.json').read_text(), 'edited source')
        self.run_build(); self.assertEqual(json.loads(path.read_text()), original)

    def test_source_race_rejected(self):
        self.run_build()
        encode = inputs.encoded
        def changed(*args):
            result = encode(*args)
            with (self.directory / inputs.DIRECTORY / 'scenes.json').open('a') as stream: stream.write(' ')
            return result
        with patch.object(inputs, 'encoded', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'): self.run_build()

    def test_report_checks_complete_actual_object_but_credits_only_owned_ranges(self):
        from test_objdiff_data_targets import object_file, targets
        self.run_build()
        spans = inputs.encoded(self.directory, self.expected, self.payload)
        linked = self.root / 'build/us/assets/asset_bank_15.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        with patch.object(targets, 'ROOT', self.root):
            unit, _ = targets.prepare_scene_headers_object(self.rom, self.expected, output=self.root / 'report')
            self.assertEqual(unit['report_data_bytes'], 67 * (len(self.container) - 12))
            self.assertEqual(unit['rom_ranges'], [[6 + off, 6 + off + len(data)] for off, data in spans])
            for at in (0, 552, 552 + 20, 552 + 92, len(self.payload) - 1):
                changed = bytearray(self.payload); changed[at] ^= 1
                linked.write_bytes(object_file([('.data', 1, 3, changed)]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'):
                    targets.prepare_scene_headers_object(self.rom, self.expected, output=self.root / 'report')
