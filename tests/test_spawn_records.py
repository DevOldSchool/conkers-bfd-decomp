"""Native spawn widths, constrained lanes, compression and source preservation."""
import copy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import asset_directory_build as build
from scripts import spawn_record_codec as codec, spawn_record_inputs as inputs


class SpawnRecordTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory()
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.record = {codec.key(off, kind): (-3 if kind == 's16' else -0.0 if kind == 'f32' else 7)
                       for off, kind in codec.FIELDS}
        raw = bytearray(48)
        for off, kind in codec.FIELDS:
            struct.pack_into('>' + codec.FORMATS[kind][0], raw, off, self.record[codec.key(off, kind)])
        self.raw = bytes(raw)
        backing = bytearray(552)
        self.spans = []
        self.gaps = []
        self.excluded = None
        for i in range(69):
            decoded = bytearray(raw)
            if i == 14: decoded[0x12] = 50
            compressed = inputs.compress(decoded)
            offset = len(backing)
            struct.pack_into('>II', backing, i * 8, offset, len(compressed) | (0x90000000 if i == 68 else 0x10000000))
            backing.extend(compressed)
            if i != 14: self.spans.append((offset, compressed))
            else: self.excluded = offset
            padding = (-len(backing)) % 4
            if padding: self.gaps.append(len(backing))
            backing.extend(b'\xcc' * padding)
        self.payload = bytes(backing)
        self.rom = b'prefix' + self.payload + b'tail'
        self.expected = {'key': 'bank0E', 'part': build.PARTS['bank0E'],
                         'rom_start': 6, 'rom_end': 6 + len(backing), 'rom_ranges': [[6, 558]],
                         'directory_size': 552, 'directory_sha256': build.sha256(self.payload[:552]),
                         'original_sha256': build.sha256(self.payload)}
        self.table = build.codec.decode(self.payload[:552])
        self.directory = self.root / build.input_directory('bank0E')
        self.old = build.input_files(self.rom, self.expected, self.table)
        build.texture_build.publish_inputs(self.directory, self.old)

    def run_build(self):
        with patch.object(build, 'reviewed_directories', return_value=(self.rom, [(self.expected, self.table)])):
            return build.build_parts(self.root)

    def test_native_widths_signed_zero_and_unexplained_storage(self):
        self.assertEqual(codec.encode([self.record]), self.raw)
        self.assertEqual(codec.encode(codec.decode(self.raw)), self.raw)
        self.assertEqual(self.raw[0x20:0x24], b'\x80\0\0\0')
        self.assertEqual(self.raw[6:8], b'\xff\xfd')
        self.assertEqual(codec.encode([]), b'')
        self.assertEqual(codec.decode(b''), [])
        for off in codec.ZERO_OFFSETS:
            data = bytearray(self.raw); data[off] = 1
            with self.assertRaisesRegex(ValueError, 'unexplained'): codec.decode(data)
        for data in (self.raw[:-1], self.raw + b'\0', self.raw * 256):
            with self.assertRaises(ValueError): codec.decode(data)
        for bits in (0x7f800000, 0xff800000, 0x7fc00000):
            data = bytearray(self.raw); struct.pack_into('>I', data, 0x20, bits)
            with self.assertRaises(ValueError): codec.decode(data)

    def test_strict_schema_and_scalar_domains(self):
        for off, kind in codec.FIELDS:
            _, low, high = codec.FORMATS[kind]
            invalid = (True, float('inf'), float('nan'), 10**1000, 3.5e38) if kind == 'f32' else (True, low - 1, high + 1, 1.5)
            for value in invalid:
                record = dict(self.record); record[codec.key(off, kind)] = value
                with self.assertRaises(ValueError): codec.encode([record])
        for extra in ({'raw': '00'}, {'u8_12': 0}):
            record = {**self.record, **extra}
            with self.assertRaises(ValueError): codec.encode([record])
        with self.assertRaises(ValueError): codec.encode([self.record] * 256)
        with self.assertRaises(ValueError): codec.encode((self.record,))

    def test_exact_compressed_ranges_preserve_all_backing_and_inputs(self):
        self.run_build()
        for name, value in self.old.items(): self.assertEqual((self.directory / name).read_bytes(), value)
        packed, spans, hashes = build.packed_directory(self.directory, self.expected, include_spawn_records=True)
        self.assertEqual(packed, self.payload)
        self.assertEqual(spans, [(0, self.payload[:552])])
        self.assertEqual(inputs.encoded(self.directory, self.expected, self.payload), self.spans)
        self.assertIn('spawn-records/spawns.json', hashes)
        path = self.root / 'build/us/asset-directories/parts/asset_bank_0e.bin'
        stamp = path.stat().st_mtime_ns
        self.run_build(); self.assertEqual(path.stat().st_mtime_ns, stamp)
        path.unlink(); self.run_build(); self.assertEqual(path.read_bytes(), self.payload)

    def test_edits_deletions_and_recovery_preserve_user_files(self):
        self.run_build()
        path = self.directory / inputs.DIRECTORY / 'spawns.json'
        original = json.loads(path.read_text())
        for which in ('scalar', 'selection', 'count'):
            changed = copy.deepcopy(original); row = changed['entries'][0]
            if which == 'scalar': row['records'][0]['s16_06'] += 1
            elif which == 'selection': row['index'] = True
            else: row['records'].append(dict(self.record))
            path.write_text(json.dumps(changed))
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): self.run_build()
            self.assertEqual(json.loads(path.read_text()), changed)
        path.unlink()
        with self.assertRaisesRegex(ValueError, 'Inputs were preserved'): self.run_build()
        self.assertFalse(path.exists())
        path.write_text('edited source')
        with patch.object(build, 'reviewed_directories', return_value=(self.rom, [(self.expected, self.table)])):
            recovered = build.recover_inputs('bank0E', self.root)
        self.assertEqual((Path(recovered['backup_directory']) / inputs.DIRECTORY / 'spawns.json').read_text(), 'edited source')
        self.run_build(); self.assertEqual(json.loads(path.read_text()), original)

    def test_source_race_rejected(self):
        self.run_build()
        encode = inputs.encoded
        def changed(*args):
            result = encode(*args)
            with (self.directory / inputs.DIRECTORY / 'spawns.json').open('a') as stream: stream.write(' ')
            return result
        with patch.object(inputs, 'encoded', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'): self.run_build()

    def test_report_verifies_whole_linked_object_and_claims_only_selected_streams(self):
        from test_objdiff_data_targets import object_file, targets
        self.run_build()
        linked = self.root / 'build/us/assets/asset_bank_0e.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        with patch.object(targets, 'ROOT', self.root):
            unit, _ = targets.prepare_spawn_records_object(self.rom, self.expected, output=self.root / 'report')
            self.assertEqual(unit['report_data_bytes'], sum(len(blob) for _, blob in self.spans))
            self.assertEqual(unit['rom_ranges'], [[6 + off, 6 + off + len(blob)] for off, blob in self.spans])
            for at in (0, 552, self.excluded, *self.gaps[:1], len(self.payload) - 1):
                changed = bytearray(self.payload); changed[at] ^= 1
                linked.write_bytes(object_file([('.data', 1, 3, changed)]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'):
                    targets.prepare_spawn_records_object(self.rom, self.expected, output=self.root / 'report')
