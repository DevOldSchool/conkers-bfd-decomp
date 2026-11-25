"""Dialogue semantics, preserved inputs and whole linked-object coverage."""
import copy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import asset_directory_build as build
from scripts import dialogue_codec as codec, dialogue_inputs as inputs


class DialogueTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.source = {'format': codec.FORMAT, 'pages': [
            ['Hello\n', {'control': 'pulse'}, 'Conker'],
            [{'control': 'descriptor_80091690_animated'}, 'Go!']], 'audio_ids': [1, 0, 65535]}
        backing = bytearray(40)
        for language in range(5):
            child = bytearray(544)
            for index in range(68):
                payload = codec.encode(self.source) if index in (0, 67) else b''
                compressed = index == 0
                if compressed:
                    payload = codec.compress(payload)
                flags = (8 if index == 67 else 0) | int(compressed)
                struct.pack_into('>II', child, index * 8, len(child), len(payload) | flags << 28)
                if payload:
                    child.extend(payload)
                    child.extend(b'GAP')  # Never credited or derived as padding.
            struct.pack_into('>II', backing, language * 8, len(backing), len(child) | (8 if language == 4 else 0) << 28)
            backing.extend(child)
        self.payload = bytes(backing)
        self.rom = b'prefix' + self.payload + b'after'
        self.expected = {'key': 'bank1A', 'part': build.PARTS['bank1A'],
                         'rom_start': 6, 'rom_end': 6 + len(backing), 'rom_ranges': [[6, 46]],
                         'directory_size': 40, 'directory_sha256': build.sha256(self.payload[:40]),
                         'original_sha256': build.sha256(self.payload)}
        self.table = build.codec.decode(self.payload[:40])
        self.directory = self.root / build.input_directory('bank1A')
        self.old = build.input_files(self.rom, self.expected, self.table)
        build.texture_build.publish_inputs(self.directory, self.old)

    def run_build(self):
        with patch.object(build, 'reviewed_directories', return_value=(self.rom, [(self.expected, self.table)])):
            return build.build_parts(self.root)

    def test_text_pages_controls_audio_widths_and_derived_alignment(self):
        source = {'format': codec.FORMAT, 'pages': [['A'], ['B', {'control': 'pulse'}]], 'audio_ids': [0x1234]}
        expected = struct.pack('>4I', 16, 6, 24, 0x80000002) + b'A\xBDB\xA6\0\0\0\0\x12\x34' + bytes(6)
        self.assertEqual(codec.encode(source), expected)
        self.assertEqual(codec.decode(expected), source)
        self.assertEqual(codec.unpack(codec.compress(expected)), expected)
        for offset in (20, 22, 31):
            changed = bytearray(expected)
            changed[offset] = 1
            with self.assertRaises(ValueError):
                codec.decode(bytes(changed))
        for bad in (True, -1, 65536, 1.5):
            with self.assertRaises(ValueError):
                codec.encode({**source, 'audio_ids': [bad]})
        for pages in ([], [[]], [['']], [['A\0B']], [['\u00BD']], [[{'raw': 'BD'}]], [[{'control': 'unknown'}]]):
            with self.assertRaises(ValueError):
                codec.encode({**source, 'pages': pages})
        blob = codec.compress(expected)
        for bad in (blob[:-1], blob + b'junk', bytes(5), bytes.fromhex('ffffffff') + blob[4:]):
            with self.assertRaises(ValueError):
                codec.unpack(bad)

    def test_sources_preserved_and_rebuild_is_idempotent(self):
        self.run_build()
        for name, data in self.old.items():
            self.assertEqual((self.directory / name).read_bytes(), data)
        packed, spans, hashes = build.packed_directory(self.directory, self.expected, include_dialogue=True)
        self.assertEqual(packed, self.payload)
        self.assertEqual(spans, [(0, self.payload[:40])])
        self.assertIn('dialogue/dialogue.json', hashes)
        path = self.root / 'build/us/asset-directories/parts/asset_bank_1a.bin'
        stamp = path.stat().st_mtime_ns
        self.run_build()
        self.assertEqual(path.stat().st_mtime_ns, stamp)
        path.unlink()
        self.run_build()
        self.assertEqual(path.read_bytes(), self.payload)

    def test_edits_and_missing_inputs_preserved_recovery_backs_up(self):
        self.run_build()
        path = self.directory / inputs.DIRECTORY / 'dialogue.json'
        original = json.loads(path.read_text())
        variants = []
        for kind in ('text', 'audio', 'directory', 'selection'):
            changed = copy.deepcopy(original)
            row = changed['languages'][0]['records'][0]
            if kind == 'text':
                row['dialogue']['pages'][0][0] += 'x'
            elif kind == 'audio':
                row['dialogue']['audio_ids'][0] += 1
            elif kind == 'directory':
                changed['languages'][0]['directory']['entries'][0]['flags'] ^= 1
            else:
                row['index'] = True
            variants.append(changed)
        for changed in variants:
            path.write_text(json.dumps(changed))
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                self.run_build()
            self.assertEqual(json.loads(path.read_text()), changed)
        path.unlink()
        with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
            self.run_build()
        self.assertFalse(path.exists())
        path.write_text('bad input')
        with patch.object(build, 'reviewed_directories', return_value=(self.rom, [(self.expected, self.table)])):
            recovered = build.recover_inputs('bank1A', self.root)
        self.assertEqual((Path(recovered['backup_directory']) / inputs.DIRECTORY / 'dialogue.json').read_text(), 'bad input')
        self.run_build()
        self.assertEqual(json.loads(path.read_text()), original)

    def test_source_race_is_rejected(self):
        self.run_build()
        encode = inputs.encoded
        def changed(*args):
            result = encode(*args)
            with (self.directory / inputs.DIRECTORY / 'dialogue.json').open('a') as stream:
                stream.write(' ')
            return result
        with patch.object(inputs, 'encoded', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                self.run_build()

    def test_report_checks_whole_object_and_excludes_outer_directory_and_gaps(self):
        from test_objdiff_data_targets import object_file, targets
        self.run_build()
        spans = inputs.encoded(self.directory, self.expected, self.payload)
        linked = self.root / 'build/us/assets/asset_bank_1a.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        output = self.root / 'report'
        with patch.object(targets, 'ROOT', self.root):
            unit, _ = targets.prepare_dialogue_object(self.rom, self.expected, output=output)
            self.assertEqual(unit['report_data_bytes'], sum(len(data) for _, data in spans))
            self.assertEqual(unit['rom_ranges'], [[6 + off, 6 + off + len(data)] for off, data in spans])
            self.assertEqual(targets.sections((output / unit['base_path']).read_bytes(), 1)['.data'][1],
                             b''.join(data for _, data in spans))
            for at in (0, 40, 584, len(self.payload) - 1):
                changed = bytearray(self.payload)
                changed[at] ^= 1
                linked.write_bytes(object_file([('.data', 1, 3, bytes(changed))]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'):
                    targets.prepare_dialogue_object(self.rom, self.expected, output=output)
