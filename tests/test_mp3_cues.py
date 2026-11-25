"""Native command fields, explicit holes and conservative source recovery."""
import copy
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch
from scripts import mp3_cue_codec as codec, mp3_cue_build as cues, mp3_spectral_build as build
from test_mp3_spectral_build import fixture


class CueCodecTests(unittest.TestCase):
    def test_native_fields_and_unconsumed_bytes(self):
        raw = b'L:\x01\x05\x80\x80\x87\xe8\0'
        record = codec.decode(raw)
        self.assertEqual(record, {'format': codec.FORMAT, 'action': 4, 'duration_numerator': 1000})
        self.assertEqual(codec.encode(record), [(0, b'L'), (3, raw[3:])])
        self.assertEqual(codec.decode(b'L!?'+raw[3:]), record)
        for bit in range(28):
            changed = dict(record, duration_numerator=1000 ^ (1 << bit))
            encoded = codec.encode(changed)[1][1]
            self.assertEqual(int.from_bytes(encoded[1:5], 'big') ^ int.from_bytes(raw[4:8], 'big'),
                             1 << ((bit // 7) * 8 + bit % 7))
        for action in (0, 1, 254):
            self.assertEqual(codec.encode(dict(record, action=action))[1][1][0], action + 1)
        self.assertEqual(codec.encode(dict(record, duration_numerator=0))[1][1][1:5], b'\x80'*4)

    def test_domains_terminators_and_opaque_overrides_rejected(self):
        raw = b'L:\x01\x05\x80\x80\x87\xe8\0'; record = codec.decode(raw)
        for field, value in [('action', -1), ('action', 255), ('action', True),
                             ('duration_numerator', -1), ('duration_numerator', 1 << 28),
                             ('duration_numerator', 1.0), ('raw', '00'), ('format', 'other')]:
            with self.subTest(field=field, value=value), self.assertRaises(ValueError):
                codec.encode(dict(record, **{field: value}))
        for offset in range(9):
            changed = bytearray(raw); changed[offset] = 1 if offset in (0, 8) else 0
            with self.subTest(offset=offset), self.assertRaises(ValueError): codec.decode(changed)
        for offset in range(4, 8):
            changed = bytearray(raw); changed[offset] &= 127
            with self.assertRaises(ValueError): codec.decode(changed)
        for changed in (raw[:-1], raw+b'\0'):
            with self.assertRaises(ValueError): codec.decode(changed)


class CueBuildTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(); self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.records, self.original = fixture()
        self.stream = {'entry': 0, 'original_sha256': build.sha256(self.original)}
        self.expected, self.commands = cues.reviewed_stream(self.original, self.stream)
        cues.initialize(self.root, self.original, self.stream)
        self.directory = self.root / cues.input_directory(0)

    def test_exact_seven_byte_ranges_and_original_extent_checks(self):
        spans, hashes = cues.packed_fields(self.directory, self.expected)
        self.assertEqual(spans, [(78, b'L'), (81, self.original[81:87])])
        self.assertEqual(len(hashes), 2)
        with self.assertRaisesRegex(ValueError, 'backing differs'):
            cues.reviewed_stream(self.original+b'X', self.stream)
        self.assertIsNone(cues.reviewed_stream(self.original, dict(self.stream, entry=1)))

    def test_field_placement_count_and_override_edits_are_rejected(self):
        changes = [lambda r: r['commands'][0]['fields'].update(action=5),
                   lambda r: r['commands'][0]['fields'].update(duration_numerator=1001),
                   lambda r: r['commands'][0].update(frame=1),
                   lambda r: r['commands'][0].update(frame=False),
                   lambda r: r.update(raw='00'), lambda r: r['commands'].clear(),
                   lambda r: r['commands'].append(copy.deepcopy(r['commands'][0]))]
        for change in changes:
            source = copy.deepcopy(self.commands); change(source)
            path = self.directory/'commands.json'; path.write_text(json.dumps(source))
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                cues.packed_fields(self.directory, self.expected)
            self.assertEqual(json.loads(path.read_text()), source)

    def test_missing_sources_are_preserved_and_recovery_is_explicit(self):
        for name, data in [('commands.json', None), ('commands.json', b'bad'), ('manifest.json', b'{}')]:
            for filename, content in cues.input_files(self.expected, self.commands).items():
                (self.directory/filename).write_bytes(content)
            path = self.directory/name
            if data is None: path.unlink()
            else: path.write_bytes(data)
            before = {p.name:p.read_bytes() for p in self.directory.iterdir()}
            cues.initialize(self.root, self.original, self.stream)
            with self.assertRaisesRegex(ValueError, 'recover-cues'):
                cues.packed_fields(self.directory, self.expected)
            self.assertEqual({p.name:p.read_bytes() for p in self.directory.iterdir()}, before)
        with patch.object(build, 'reviewed_streams', return_value=(self.original, [(self.stream, self.original)])):
            result = cues.recover_inputs(0, self.root)
        self.assertEqual((Path(result['backup_directory'])/'manifest.json').read_bytes(), b'{}')
        self.assertEqual(sum(len(b) for _,b in cues.packed_fields(self.directory, self.expected)[0]), 7)

    def test_source_race_is_rejected(self):
        encode = codec.encode
        def racing(record):
            result = encode(record)
            with (self.directory/'commands.json').open('a') as f: f.write(' ')
            return result
        with patch.object(codec, 'encode', side_effect=racing):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                cues.packed_fields(self.directory, self.expected)
