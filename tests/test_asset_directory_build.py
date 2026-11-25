"""Typed directory fields and credit bounded to actual linked directory bytes."""
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch
from scripts import asset_directory_build as build, asset_directory_codec as codec


def source():
    return {'format': codec.FORMAT, 'entries': [
        {'relative_offset': 24, 'stored_size': 4, 'flags': 2},
        {'relative_offset': 0, 'stored_size': 0, 'flags': 0},
        {'relative_offset': 32, 'stored_size': 3, 'flags': 1}]}


class DirectoryCodecTests(unittest.TestCase):
    def test_native_words_and_empty_slots(self):
        native = struct.pack('>6I', 24, 0x20000004, 0, 0, 32, 0x10000003)
        self.assertEqual(codec.encode(source()), native)
        self.assertEqual(codec.decode(native), source())
        for field, value, word in (('relative_offset', 40, 4), ('stored_size', 5, 5), ('flags', 7, 5)):
            changed = source(); changed['entries'][2][field] = value
            words = struct.unpack('>6I', codec.encode(changed))
            original = struct.unpack('>6I', native)
            self.assertNotEqual(words[word], original[word])
            self.assertEqual(words[:word] + words[word+1:], original[:word] + original[word+1:])

    def test_invalid_fields_and_extents(self):
        for field, value in (('relative_offset', -1), ('relative_offset', 1 << 32),
                             ('relative_offset', 25), ('relative_offset', 0xffffffff),
                             ('stored_size', 1 << 28), ('flags', 16), ('flags', True),
                             ('raw_bytes', '00')):
            record = source(); record['entries'][2][field] = value
            with self.subTest(field=field, value=value), self.assertRaises(ValueError): codec.encode(record)
        record = source(); record['entries'][0]['relative_offset'] = 32
        with self.assertRaises(ValueError): codec.encode(record)
        for data in (b'', bytes(7), bytes(8)):
            with self.assertRaises(ValueError): codec.decode(data)


class DirectoryBuildTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(); self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.native = codec.encode(source())
        self.payload = self.native + b'abcdGAP!end'
        self.rom = b'prefix' + self.payload + b'tail'
        self.expected = {'key': 'bank08', 'part': build.PARTS['bank08'],
            'rom_start': 6, 'rom_end': 6 + len(self.payload), 'rom_ranges': [[6, 30]],
            'directory_size': 24, 'directory_sha256': build.sha256(self.native),
            'original_sha256': build.sha256(self.payload)}
        self.directory = self.root / build.input_directory('bank08')
        self.files = build.input_files(self.rom, self.expected, source())
        build.texture_build.publish_inputs(self.directory, self.files)

    def reviewed(self):
        return patch.object(build, 'reviewed_directories', return_value=(self.rom, [(self.expected, source())]))

    def test_sources_stable_and_missing_output_repaired(self):
        hashes = build.input_hashes(self.directory, self.expected)
        with self.reviewed():
            proof = build.build_parts(self.root)
            path = self.root / ('build/us/asset-directories/parts/' + self.expected['part'] + '.bin')
            stamp = path.stat().st_mtime_ns
            self.assertEqual(build.build_parts(self.root), proof)
            self.assertEqual(path.stat().st_mtime_ns, stamp)
            path.unlink(); build.build_parts(self.root)
            self.assertEqual(path.read_bytes(), self.payload)
        self.assertEqual(proof[0]['rebuilt_bytes'], 24)
        self.assertEqual(build.input_hashes(self.directory, self.expected), hashes)

    def test_invalid_sources_preserved_and_recovery_backed_up(self):
        for name, value in (('directory.json', None), ('directory.json', b'bad'),
                            ('directory.json', b'{}'), ('manifest.json', b'{}'), ('backing.bin', b'edited')):
            for filename, data in self.files.items(): (self.directory / filename).write_bytes(data)
            path = self.directory / name
            if value is None: path.unlink()
            else: path.write_bytes(value)
            before = {p.name: p.read_bytes() for p in self.directory.iterdir()}
            with self.reviewed(), self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                build.build_parts(self.root)
            self.assertEqual({p.name: p.read_bytes() for p in self.directory.iterdir()}, before)
            self.assertFalse((self.root / 'build/us/asset-directories/parts').exists())
        with self.reviewed(): restored = build.recover_inputs('bank08', self.root)
        self.assertEqual((Path(restored['backup_directory']) / 'backing.bin').read_bytes(), b'edited')
        self.assertEqual(build.packed_directory(self.directory, self.expected)[0], self.payload)

    def test_all_typed_field_changes_rejected_against_reference(self):
        for field in ('relative_offset', 'stored_size', 'flags'):
            record = source(); record['entries'][2][field] += 1
            (self.directory / 'directory.json').write_text(json.dumps(record))
            with self.assertRaisesRegex(ValueError, 'no longer reproduce'):
                build.packed_directory(self.directory, self.expected)

    def test_source_race_rejected(self):
        encode = codec.encode
        def changed(record):
            data = encode(record)
            with (self.directory / 'directory.json').open('a') as stream: stream.write(' ')
            return data
        with patch.object(codec, 'encode', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_directory(self.directory, self.expected)

    def test_report_only_credits_directory_and_checks_entire_linked_object(self):
        from test_objdiff_data_targets import object_file, targets
        linked = self.root / ('build/us/assets/' + self.expected['part'] + '.o')
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        output = self.root / 'report'
        with patch.object(targets, 'ROOT', self.root):
            unit, item = targets.prepare_asset_directory(self.rom, self.expected, output=output)
            self.assertEqual(unit['report_data_bytes'], 24)
            self.assertEqual(unit['rom_ranges'], [[6, 30]])
            self.assertEqual(item['name'], 'assets/directories/bank08')
            native = targets.sections((output / 'asset-directory-bank08/base.o').read_bytes(), 1)['.data'][1]
            self.assertEqual(native, self.native)
            for at in (0, len(self.payload)-1):
                changed = bytearray(self.payload); changed[at] ^= 1
                linked.write_bytes(object_file([('.data', 1, 3, changed)]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'):
                    targets.prepare_asset_directory(self.rom, self.expected, output=output)
