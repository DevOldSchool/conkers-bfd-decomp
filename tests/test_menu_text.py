"""Native string semantics, input preservation and actual linked bank coverage."""
import copy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import asset_directory_build as build
from scripts import menu_text_codec as codec, menu_text_inputs as inputs


class MenuTextTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.tables = [{'format': codec.FORMAT, 'strings': [
            ['Menu ' + str(i)], ['P', {'icon': name}], ['*'], ['=']]}
            for i, name in enumerate(codec.ICONS)]
        backing = bytearray(72)
        for i, source in enumerate(self.tables):
            packed = codec.compress(codec.encode(source))
            struct.pack_into('>II', backing, 40 + i * 8, len(backing) - 40,
                             len(packed) | (9 if i == 3 else 1) << 28)
            backing.extend(packed)
            backing.extend(b'GAP')  # These bytes must never earn credit.
        struct.pack_into('>II', backing, 0, 40, len(backing) - 40)
        for i in range(1, 5):
            struct.pack_into('>II', backing, i * 8, len(backing), 0x80000000 if i == 4 else 0)
        self.payload = bytes(backing)
        self.rom = b'prefix' + self.payload + b'after'
        self.expected = {'key': 'bank1C', 'part': build.PARTS['bank1C'],
                         'rom_start': 6, 'rom_end': 6 + len(backing), 'rom_ranges': [[6, 46]],
                         'directory_size': 40, 'directory_sha256': build.sha256(self.payload[:40]),
                         'original_sha256': build.sha256(self.payload)}
        self.table = build.codec.decode(self.payload[:40])
        self.directory = self.root / build.input_directory('bank1C')
        self.old = build.input_files(self.rom, self.expected, self.table)
        build.texture_build.publish_inputs(self.directory, self.old)

    def run_build(self):
        with patch.object(build, 'reviewed_directories', return_value=(self.rom, [(self.expected, self.table)])):
            return build.build_parts(self.root)

    def test_native_text_icons_and_derived_alignment(self):
        source = {'format': codec.FORMAT, 'strings': [['OFF'], ['ON'],
                  ['1', {'icon': 'descriptor_80091710'}], ['*'], ['=']]}
        raw = b'OFF\0ON\0\0' + b'1\xb6\0\0*\0=\0'
        self.assertEqual(codec.encode(source), raw)
        self.assertEqual(codec.decode(raw), source)
        self.assertEqual(codec.unpack(codec.compress(raw)), raw)
        for raw in (b'', b'A', b'\0\0', b'A\0\0\0', b'AB\0X', b'\xff\0'):
            with self.subTest(raw=raw), self.assertRaises(ValueError):
                codec.decode(raw)
        for segments in ([], [''], ['A\0B'], ['\u00b6'], [{'icon': 'unknown'}], [182],
                         [{'raw': 'B6'}], ['A' * (codec.MAX_SIZE + 1)]):
            with self.assertRaises(ValueError):
                codec.encode({'format': codec.FORMAT, 'strings': [segments]})
        blob = codec.compress(codec.encode(source))
        for bad in (blob[:-1], blob + b'extra', bytes(5), bytes.fromhex('ffffffff') + blob[4:]):
            with self.assertRaises(ValueError):
                codec.unpack(bad)

    def test_sources_preserved_and_complete_object_rebuilt(self):
        self.run_build()
        for name, data in self.old.items():
            self.assertEqual((self.directory / name).read_bytes(), data)
        packed, spans, hashes = build.packed_directory(self.directory, self.expected, include_menu_text=True)
        self.assertEqual(packed, self.payload)
        self.assertEqual(spans, [(0, self.payload[:40])])
        self.assertIn('menu-text/text.json', hashes)
        output = self.root / 'build/us/asset-directories/parts/asset_bank_1c.bin'
        stamp = output.stat().st_mtime_ns
        self.run_build()
        self.assertEqual(output.stat().st_mtime_ns, stamp)
        output.unlink()
        self.run_build()
        self.assertEqual(output.read_bytes(), self.payload)

    def test_text_icons_and_directory_edits_fail_without_overwrite(self):
        self.run_build()
        path = self.directory / inputs.DIRECTORY / 'text.json'
        original = json.loads(path.read_text())
        for i in range(4):
            changed = copy.deepcopy(original)
            changed['tables'][i]['strings'][0][0] += 'x'
            self.assertNotEqual(codec.encode(changed['tables'][i]), codec.encode(original['tables'][i]))
            path.write_text(json.dumps(changed))
            with self.assertRaisesRegex(ValueError, 'no longer reproduces'):
                self.run_build()
            self.assertEqual(json.loads(path.read_text()), changed)
        for field in ('relative_offset', 'stored_size', 'flags'):
            changed = copy.deepcopy(original)
            changed['directory']['entries'][1][field] += 1
            path.write_text(json.dumps(changed))
            with self.assertRaises(ValueError):
                self.run_build()
            self.assertEqual(json.loads(path.read_text()), changed)
        changed = copy.deepcopy(original)
        changed['tables'][0]['strings'][1][1]['icon'] = 'descriptor_80091720'
        path.write_text(json.dumps(changed))
        with self.assertRaisesRegex(ValueError, 'no longer reproduces'):
            self.run_build()
        self.assertEqual(json.loads(path.read_text()), changed)

    def test_invalid_or_missing_source_preserved_and_recovery_backs_up(self):
        self.run_build()
        directory = self.directory / inputs.DIRECTORY
        original = {p.name: p.read_bytes() for p in directory.iterdir()}
        for name, value in (('text.json', None), ('text.json', b'bad'),
                            ('text.json', b'{}'), ('manifest.json', b'{}')):
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
            recovered = build.recover_inputs('bank1C', self.root)
        self.assertEqual((Path(recovered['backup_directory']) / inputs.DIRECTORY / 'manifest.json').read_bytes(), b'{}')
        self.run_build()
        self.assertEqual((directory / 'text.json').read_bytes(), original['text.json'])

    def test_source_race_rejected(self):
        self.run_build()
        encode = inputs.encoded
        def changed(*args):
            result = encode(*args)
            with (self.directory / inputs.DIRECTORY / 'text.json').open('a') as stream:
                stream.write(' ')
            return result
        with patch.object(build.menu_text_inputs, 'encoded', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                self.run_build()

    def test_report_excludes_outer_directory_and_gaps_checks_whole_object(self):
        from test_objdiff_data_targets import object_file, targets
        self.run_build()
        spans = inputs.encoded(self.directory, self.expected, self.payload)
        linked = self.root / 'build/us/assets/asset_bank_1c.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        output = self.root / 'report'
        with patch.object(targets, 'ROOT', self.root):
            unit, _ = targets.prepare_menu_text_object(self.rom, self.expected, output=output)
            header, _ = targets.prepare_asset_directory(self.rom, self.expected, output=output)
            self.assertEqual(unit['report_data_bytes'], sum(len(data) for _, data in spans))
            self.assertEqual(unit['rom_ranges'], [[6 + off, 6 + off + len(data)] for off, data in spans])
            self.assertEqual(header['rom_ranges'], [[6, 46]])
            self.assertEqual(targets.sections((output / unit['base_path']).read_bytes(), 1)['.data'][1],
                             b''.join(data for _, data in spans))
            for at in (0, 40, 72, len(self.payload) - 1):
                changed = bytearray(self.payload)
                changed[at] ^= 1
                linked.write_bytes(object_file([('.data', 1, 3, bytes(changed))]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'):
                    targets.prepare_menu_text_object(self.rom, self.expected, output=output)
