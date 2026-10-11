from dataclasses import replace
from pathlib import Path
import struct
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch
import yaml

from scripts import audio_boundaries as boundaries, audio_assets
from test_audio_assets import compact_sequence_bank


def fixture():
    sequence_data = compact_sequence_bank()
    data = [b'zip!!', b'bankdata', bytes(8), sequence_data, bytes(8), bytes(8), bytes(8)]
    bank = bytearray(56)
    assets = []
    for i, payload in enumerate(data):
        bank.extend(bytes((-len(bank)) % 8))
        begin = len(bank)
        bank.extend(payload)
        flags = (0x10000000 if i == 0 else 0) | (0x80000000 if i == 6 else 0) | len(payload)
        struct.pack_into('>II', bank, 8 * i, begin, flags)
        assets.append(audio_assets.AudioAsset(i, 'fixture', payload, 16 + begin,
                                             16 + len(bank), flags >> 24, i == 0))
    family = SimpleNamespace(bank_start=16, bank_end=16 + len(bank), assets=tuple(assets[:4]),
                             sequences=audio_assets.parse_compact_sequence_bank(sequence_data))
    mp3 = SimpleNamespace(offsets=assets[4], lookup=assets[5], huffman=assets[6])
    return bytes(16) + bank, family, mp3


class AudioBoundariesTests(unittest.TestCase):
    def test_partitions_bank_and_retains_nonzero_sequence_padding(self):
        rom, family, mp3 = fixture()
        ranges = boundaries.proven_ranges(rom, family, mp3)
        self.assertEqual(b''.join(rom[start:end] for start, end, _ in ranges), rom[16:])
        padding = [rom[start:end] for start, end, name in ranges if '/sequences/padding/' in name]
        self.assertEqual(padding, [b'\xAA\xBB', b'\xCC'])
        self.assertEqual(len([name for _, _, name in ranges if name.endswith('_rzip')]), 1)
        self.assertEqual(len([name for _, _, name in ranges if '/padding/' in name and '/sequences/' not in name]), 2)

    def test_rejects_index_disagreement_and_unproven_padding(self):
        rom, family, mp3 = fixture()
        with self.assertRaisesRegex(ValueError, 'bank index'):
            boundaries.proven_ranges(rom, family, SimpleNamespace(
                offsets=replace(mp3.offsets, rom_end=mp3.offsets.rom_end - 1),
                lookup=mp3.lookup, huffman=mp3.huffman))
        changed = bytearray(rom)
        changed[family.assets[0].rom_end] = 1
        with self.assertRaisesRegex(ValueError, 'alignment padding is not proven'):
            boundaries.proven_ranges(bytes(changed), family, mp3)

    def test_nonzero_sequence_padding_must_follow_four_byte_alignment(self):
        rom, family, mp3 = fixture()
        sequence = family.sequences[0]
        family.sequences = (replace(sequence, padding_after=sequence.padding_after + bytes(4)),) + family.sequences[1:]
        # Isolate the alignment guard from the independent container reconstruction check.
        with patch.object(boundaries.audio_assets, 'rebuild_compact_sequence_bank', return_value=family.assets[3].data):
            with self.assertRaisesRegex(ValueError, 'next four-byte boundary'):
                boundaries.proven_ranges(rom, family, mp3)

    def test_yaml_is_checked_against_rom_ranges(self):
        rom, family, mp3 = fixture()
        ranges = boundaries.proven_ranges(rom, family, mp3)
        config = {'segments': [{'name': 'asset_bank_17', 'type': 'group', 'start': 16,
                               'align': 1, 'subalign': 1,
                               'subsegments': [[start, 'bin', name] for start, _, name in ranges]},
                              {'name': 'next', 'start': family.bank_end}]}
        with tempfile.TemporaryDirectory() as directory:
            profile = Path(directory) / 'us.yaml'
            profile.write_text(yaml.safe_dump(config))
            with patch.object(boundaries.audio_assets, 'load_profile_audio_assets',
                              return_value=(None, rom, 'big', family)), \
                    patch.object(boundaries.mp3_assets, 'load_profile_mp3_assets',
                                 return_value=(None, rom, 'big', mp3)):
                self.assertEqual(boundaries.verify(profile), (rom, ranges))
                config['segments'][0]['subsegments'][1][0] += 1
                profile.write_text(yaml.safe_dump(config))
                with self.assertRaisesRegex(ValueError, 'YAML audio splits differ'):
                    boundaries.verify(profile)

    def test_typed_sound_regions_keep_unknown_bytes_raw_and_require_matching_yaml(self):
        rom, family, mp3 = fixture()
        regions = {'external': [{'start': 0, 'end': 2}, {'start': 4, 'end': 8}],
                   'external_unknown_ranges': [(2, 4)]}
        ranges = boundaries.proven_ranges(rom, family, mp3, sound_regions=regions)
        self.assertEqual(b''.join(rom[a:b] for a, b, _ in ranges), rom[16:])
        graph = [(a, b, n) for a, b, n in ranges if '/sound-bank/' in n]
        self.assertEqual(len(graph), 3)
        self.assertIn('/unreconstructed/', graph[1][2])
        self.assertEqual(rom[graph[1][0]:graph[1][1]], b'nk')
        config = {'segments': [{'name': 'asset_bank_17', 'type': 'group', 'start': 16,
                               'align': 1, 'subalign': 1,
                               'subsegments': [[a, 'bin', n] for a, _, n in ranges]},
                              {'name': 'next', 'start': family.bank_end}]}
        with tempfile.TemporaryDirectory() as directory:
            profile = Path(directory) / 'us.yaml'
            profile.write_text(yaml.safe_dump(config))
            with patch.object(boundaries.audio_assets, 'load_profile_audio_assets', return_value=(None, rom, 'big', family)), \
                    patch.object(boundaries.mp3_assets, 'load_profile_mp3_assets', return_value=(None, rom, 'big', mp3)), \
                    patch.object(boundaries.sound_bank_codec, 'verify_consumers') as consumers, \
                    patch.object(boundaries.sound_bank_codec, 'typed_regions', return_value=regions):
                self.assertEqual(boundaries.verify(profile), (rom, ranges))
                consumers.assert_called_once_with(rom)
                target = next(row for row in config['segments'][0]['subsegments'] if '/unreconstructed/' in row[2])
                target[0] += 1
                profile.write_text(yaml.safe_dump(config))
                with self.assertRaisesRegex(ValueError, 'YAML audio splits differ'):
                    boundaries.verify(profile)
