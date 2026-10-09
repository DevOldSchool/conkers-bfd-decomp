"""Exact PNG reconstruction and fail-closed compressed build inputs."""
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import yaml

from scripts import texture_assets, texture_build as build, rzip_pack


class TextureBuildTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.inputs = self.root / build.INPUT_DIRECTORY
        # Synthetic pixels and palette; no game bytes in tests.
        self.payload = bytes(range(256)) * 8 + bytes(range(32))
        self.packed = rzip_pack.encode_rzip_chunk(self.payload)
        self.start, self.end = 20, 20 + len(self.packed)
        self.rom = bytes(20) + self.packed + bytes(4)
        self.texture = texture_assets.TextureAsset(1063, self.start, self.end, self.payload)
        self.expected = build.describe_texture(self.rom, self.texture)
        self.layout = {'flat_assets_start': 4, 'flat_assets_end': self.end + 4}
        self.profile = self.root / 'config/profiles/us.yaml'
        self.profile.parent.mkdir(parents=True)
        self.document = {'segments': [{'name': 'assets_flat_rzip', 'type': 'group',
            'start': 4, 'align': 1, 'subalign': 1,
            'subsegments': [[4, 'bin', 'flat/raw/00000004'],
                            [self.start, 'bin', build.part_name(1063)],
                            [self.end, 'bin', f'flat/raw/{self.end:08X}']]}, [self.end + 4]]}
        self.save_profile()
        self.loader = patch.object(texture_assets, 'load_profile_textures',
            return_value=(None, self.rom, 'z64', self.layout, [self.texture]))
        self.load = self.loader.start()
        self.addCleanup(self.loader.stop)

    def save_profile(self):
        self.profile.write_text(yaml.safe_dump(self.document))

    def initialize(self):
        build.initialize_inputs(self.inputs, self.expected, self.payload)

    def add_linear_texture(self):
        payload = bytes((i * 7 + 31) % 256 for i in range(2048)) + bytes(reversed(range(32)))
        packed = rzip_pack.encode_rzip_chunk(payload)
        start = self.end + 4
        texture = texture_assets.TextureAsset(1296, start, start + len(packed), payload)
        self.rom += packed + bytes(7)
        self.layout['flat_assets_end'] = len(self.rom)
        self.document['segments'][0]['subsegments'] = [
            [offset, 'bin', name] for offset, name in build.partition(self.layout, [self.texture, texture])]
        self.document['segments'][1] = [len(self.rom)]
        self.save_profile()
        self.load.return_value = (None, self.rom, 'z64', self.layout, [self.texture, texture])
        self.expected = build.describe_texture(self.rom, self.texture)
        return texture, packed

    def test_batch_counts_only_selected_storage_and_preserves_both_row_layouts(self):
        texture, packed = self.add_linear_texture()
        proof = build.build_parts(self.root)
        self.assertEqual(proof['texture_count'], 2)
        self.assertEqual(proof['stored_bytes'], len(self.packed) + len(packed))
        self.assertEqual([e['row_layout'] for e in proof['textures']],
                         ['tmem-odd-row-32bit-swap', 'linear'])
        self.assertEqual(proof['textures'][1]['flat_index'], 1296)
        output = self.root / 'build/us/textures/parts' / (build.part_name(1296) + '.bin')
        self.assertEqual(output.read_bytes(), packed)
        _, reviewed = build.reviewed_textures(self.root)
        self.assertEqual([t.flat_index for _, t in reviewed], [1063, texture.flat_index])

    def test_later_invalid_input_does_not_replace_any_existing_parts(self):
        self.add_linear_texture()
        build.build_parts(self.root)
        output = self.root / 'build/us/textures/parts' / (build.part_name(1063) + '.bin')
        output.write_bytes(b'old part')
        other = self.root / build.input_directory(1296) / '1296.ci4.png'
        other.write_bytes(b'invalid PNG')
        with self.assertRaises(ValueError):
            build.build_parts(self.root)
        self.assertEqual(output.read_bytes(), b'old part')
        self.assertEqual(other.read_bytes(), b'invalid PNG')

    def test_earlier_input_change_during_later_pack_fails_batch(self):
        self.add_linear_texture()
        build.build_parts(self.root)
        original = build.packed_texture
        def pack(directory, expected):
            result = original(directory, expected)
            if expected['flat_index'] == 1296:
                (self.inputs / 'manifest.json').write_text(json.dumps(self.expected, indent=4))
            return result
        with patch.object(build, 'packed_texture', side_effect=pack), \
                self.assertRaisesRegex(ValueError, 'changed during batch packing'):
            build.build_parts(self.root)

    def test_reconstruction_uses_encoder_and_preserves_unchanged_part_timestamp(self):
        with patch.object(rzip_pack, 'encode_rzip_chunk', wraps=rzip_pack.encode_rzip_chunk) as encode:
            proof = build.build_parts(self.root)
        encode.assert_called_once_with(self.payload)
        self.assertTrue(proof['matches_original'])
        output = self.root / 'build/us/textures/parts' / (build.part_name(1063) + '.bin')
        self.assertEqual(output.read_bytes(), self.packed)
        timestamp = output.stat().st_mtime_ns
        build.build_parts(self.root)
        self.assertEqual(output.stat().st_mtime_ns, timestamp)

    def test_missing_output_is_recovered_from_png(self):
        build.build_parts(self.root)
        output = self.root / 'build/us/textures/parts' / (build.part_name(1063) + '.bin')
        output.unlink()
        build.build_parts(self.root)
        self.assertEqual(output.read_bytes(), self.packed)

    def test_existing_partial_input_directory_is_never_overwritten(self):
        self.inputs.mkdir(parents=True)
        source = self.inputs / self.expected['file']
        source.write_bytes(b'user input')
        with self.assertRaisesRegex(ValueError, 'refusing to overwrite'):
            build.build_parts(self.root)
        self.assertEqual(source.read_bytes(), b'user input')

    def test_changed_pixels_or_palette_fail_without_replacing_output_or_png(self):
        build.build_parts(self.root)
        output = self.root / 'build/us/textures/parts' / (build.part_name(1063) + '.bin')
        source = self.inputs / self.expected['file']
        for offset in (0, 2048):
            with self.subTest(offset=offset):
                payload = bytearray(self.payload)
                payload[offset] ^= 1
                png = texture_assets.encode_indexed_png(bytes(payload), self.expected['row_layout'])
                source.write_bytes(png)
                with self.assertRaisesRegex(ValueError, 'original payload'):
                    build.build_parts(self.root)
                self.assertEqual(source.read_bytes(), png)
                self.assertEqual(output.read_bytes(), self.packed)

    def test_changed_manifest_and_missing_png_fail(self):
        self.initialize()
        manifest = self.inputs / 'manifest.json'
        changed = dict(self.expected, rom_end=self.end + 1)
        manifest.write_text(json.dumps(changed))
        with self.assertRaisesRegex(ValueError, 'manifest differs'):
            build.packed_texture(self.inputs, self.expected)
        manifest.write_text(json.dumps(self.expected))
        (self.inputs / self.expected['file']).unlink()
        with self.assertRaises(FileNotFoundError):
            build.build_parts(self.root)

    def test_encoder_drift_is_rejected_even_at_same_size(self):
        self.initialize()
        for packed, message in ((self.packed + b'\0', 'compressed extent'),
                                (self.packed[:-1] + bytes([self.packed[-1] ^ 1]), 'original RZIP')):
            with self.subTest(message=message), \
                    patch.object(rzip_pack, 'encode_rzip_chunk', return_value=packed), \
                    self.assertRaisesRegex(ValueError, message):
                build.packed_texture(self.inputs, self.expected)

    def test_concurrent_input_change_is_rejected(self):
        self.initialize()
        def encode(payload):
            (self.inputs / 'manifest.json').write_text(json.dumps(self.expected, indent=4))
            return self.packed
        with patch.object(rzip_pack, 'encode_rzip_chunk', side_effect=encode), \
                self.assertRaisesRegex(ValueError, 'changed during packing'):
            build.packed_texture(self.inputs, self.expected)

    def test_yaml_boundary_and_name_drift_fail_before_initialization(self):
        row = self.document['segments'][0]['subsegments'][1]
        for value in (self.start - 1, self.start + 1):
            row[0] = value
            self.save_profile()
            with self.assertRaisesRegex(ValueError, 'RZIP boundaries'):
                build.build_parts(self.root)
        row[0], row[2] = self.start, 'flat/textures/wrong'
        self.save_profile()
        with self.assertRaisesRegex(ValueError, 'RZIP boundaries'):
            build.build_parts(self.root)
        self.assertFalse(self.inputs.exists())

    def test_yaml_overlap_and_wrong_alignment_fail(self):
        self.document['segments'][0]['subsegments'][1][0] = 4
        self.save_profile()
        with self.assertRaisesRegex(ValueError, 'partition'):
            build.reviewed_textures(self.root)
        self.document['segments'][0]['align'] = 16
        self.save_profile()
        with self.assertRaisesRegex(ValueError, 'byte-aligned'):
            build.reviewed_textures(self.root)
