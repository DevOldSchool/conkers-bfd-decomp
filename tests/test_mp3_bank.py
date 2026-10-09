from dataclasses import replace
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import mp3_assets, mp3_bank
from test_mp3_assets import sample_family


def bank_fixture():
    frame = bytes.fromhex('FFF330C0') + bytes(74)
    bank = struct.pack('>IIIIII', 24, 78, 104, 0, 104, 0x8000004E)
    bank += frame + bytes(2) + frame + bytes(2)
    rom = bytes(16) + bank
    family = replace(sample_family(), stream_bank_start=16, stream_bank_end=len(rom), streams=(
        mp3_assets.Mp3Asset(0, 'stream', frame, 40, 118, 0, False),
        mp3_assets.Mp3Asset(2, 'stream', frame, 120, 198, 0x80, False)))
    return rom, family


class Mp3BankTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.inputs = self.root / 'inputs'
        self.rom, self.family = bank_fixture()
        self.manifest = mp3_bank.describe_bank(self.rom, self.family)
        mp3_bank.initialize_inputs(self.inputs, self.manifest, self.rom)

    def test_round_trip_preserves_sparse_index_flags_and_zero_padding(self):
        packed, hashes = mp3_bank.packed_bank(self.inputs, self.manifest)
        self.assertEqual(packed, self.rom[16:])
        self.assertEqual(self.manifest['records'][1], [104, 0])
        self.assertEqual(self.manifest['records'][2], [104, 0x8000004E])
        self.assertEqual(len(hashes), 5)
        self.assertFalse((self.inputs / 'streams/0001.mp3').exists())

    def test_build_preserves_edited_stream_and_records_mismatch(self):
        stream = self.inputs / 'streams/0000.mp3'
        changed = bytearray(stream.read_bytes())
        changed[20] = 1
        stream.write_bytes(changed)
        source = self.root / 'owned.z64'
        source.write_bytes(self.rom)
        with patch.object(mp3_assets, 'load_profile_mp3_assets', return_value=(source, self.rom, 'big', self.family)):
            packed, evidence = mp3_bank.build_bank(self.inputs, self.root / 'output/bank.bin')
        self.assertFalse(evidence['matches_original'])
        self.assertEqual(packed[24:102], changed)
        self.assertEqual(stream.read_bytes(), changed)
        self.assertEqual(json.loads((self.inputs / 'manifest.json').read_text()), self.manifest)
        self.assertEqual(evidence['index_bytes'] + evidence['stream_bytes'] + evidence['padding_bytes'], len(packed))

    def test_rejects_changed_padding(self):
        path = self.inputs / self.manifest['padding'][0]['file']
        path.write_bytes(b'\x01\x00')
        with self.assertRaisesRegex(ValueError, 'alignment padding changed'):
            mp3_bank.packed_bank(self.inputs, self.manifest)

    def test_rejects_missing_resized_and_invalid_streams(self):
        path = self.inputs / 'streams/0000.mp3'
        for data in (b'', bytes(78), bytes.fromhex('FFF330C0')):
            with self.subTest(data=data):
                path.write_bytes(data)
                with self.assertRaises(ValueError):
                    mp3_bank.packed_bank(self.inputs, self.manifest)
        path.unlink()
        with self.assertRaises(FileNotFoundError):
            mp3_bank.packed_bank(self.inputs, self.manifest)

    def test_rejects_changed_layout_or_provenance(self):
        path = self.inputs / 'manifest.json'
        for key, value in (('rom_start', 0), ('rom_sha1', 'wrong'), ('profile', 'eu'), ('records', [])):
            with self.subTest(key=key):
                edited = dict(self.manifest, **{key: value})
                path.write_text(json.dumps(edited))
                with self.assertRaisesRegex(ValueError, 'reviewed ROM layout'):
                    mp3_bank.packed_bank(self.inputs, self.manifest)

    def test_refuses_existing_partial_inputs(self):
        (self.inputs / 'manifest.json').unlink()
        stream = self.inputs / 'streams/0000.mp3'
        stream.write_bytes(b'keep my edit')
        with self.assertRaisesRegex(ValueError, 'refusing to overwrite'):
            mp3_bank.initialize_inputs(self.inputs, self.manifest, self.rom)
        self.assertEqual(stream.read_bytes(), b'keep my edit')

    def test_build_initializes_once_and_protects_sources(self):
        source = self.root / 'owned.z64'
        source.write_bytes(self.rom)
        with patch.object(mp3_assets, 'load_profile_mp3_assets', return_value=(source, self.rom, 'big', self.family)):
            packed, evidence = mp3_bank.build_bank(self.root / 'fresh', self.root / 'bank.bin')
            self.assertEqual(packed, self.rom[16:])
            self.assertTrue(evidence['matches_original'])
            for output in (source, self.inputs / 'streams/0000.mp3'):
                with self.assertRaisesRegex(ValueError, 'overwrite source inputs'):
                    mp3_bank.build_bank(self.inputs, output)
        self.assertEqual(source.read_bytes(), self.rom)

    def test_rejects_inputs_changed_during_pack(self):
        hashes = mp3_bank.input_hashes(self.inputs, self.manifest)
        with patch.object(mp3_bank, 'input_hashes', side_effect=[hashes, {}]):
            with self.assertRaisesRegex(ValueError, 'inputs changed'):
                mp3_bank.packed_bank(self.inputs, self.manifest)

    def test_rejects_unaccounted_or_disagreeing_records(self):
        for family in (replace(self.family, streams=self.family.streams[:1]),
                       replace(self.family, streams=(replace(self.family.streams[0], type_flags=0x80),))):
            with self.subTest(family=family), self.assertRaises(ValueError):
                mp3_bank.describe_bank(self.rom, family)

    def test_nonzero_gap_is_not_classified_as_padding(self):
        changed = bytearray(self.rom)
        changed[118] = 1
        with self.assertRaisesRegex(ValueError, 'zero-filled to the next 8-byte boundary'):
            mp3_bank.describe_bank(bytes(changed), self.family)

    def test_yaml_splits_are_exact_build_inputs_and_reject_drift(self):
        import yaml
        profile = self.root / 'us.yaml'
        segments = [[16, 'bin', 'audio/mp3/index'],
                    [40, 'bin', 'audio/mp3/streams/0000'],
                    [118, 'bin', 'audio/mp3/padding/00000066'],
                    [120, 'bin', 'audio/mp3/streams/0002'],
                    [198, 'bin', 'audio/mp3/padding/000000B6']]
        config = {'segments': [{'name': 'asset_bank_16', 'type': 'group',
                              'start': 16, 'align': 1, 'subalign': 1, 'subsegments': segments}]}
        profile.write_text(yaml.safe_dump(config))
        packed, _ = mp3_bank.packed_bank(self.inputs, self.manifest)
        parts = self.root / 'parts'
        mp3_bank.write_parts(packed, self.manifest, profile, parts)
        rebuilt = b''.join((parts / (name + '.bin')).read_bytes()
                           for _, name in mp3_bank.layout_bins(profile))
        self.assertEqual(rebuilt, packed)
        for offset, name in mp3_bank.layout_bins(profile):
            payload = (parts / (name + '.bin')).read_bytes()
            self.assertEqual(payload, self.rom[offset:offset + len(payload)])
        segments[1][0] += 1
        profile.write_text(yaml.safe_dump(config))
        with self.assertRaisesRegex(ValueError, 'YAML MP3 splits disagree'):
            mp3_bank.write_parts(packed, self.manifest, profile, parts)

    def test_yaml_rejects_unsafe_paths_and_changed_alignment(self):
        import yaml
        profile = self.root / 'us.yaml'
        for path, alignment in (('audio/mp3/../../outside', 1), ('audio/mp3/index', 16)):
            profile.write_text(yaml.safe_dump({'segments': [{'name': 'asset_bank_16',
                'type': 'group', 'start': 16, 'align': alignment, 'subalign': 1,
                'subsegments': [[16, 'bin', path]]}]}))
            with self.assertRaises(ValueError):
                mp3_bank.layout_bins(profile)
