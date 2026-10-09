"""Every mip level and shared palette is a required PNG build input."""
import copy
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from scripts import texture_assets as t, texture_build as build, rzip_pack


class MipmapBuildTests(unittest.TestCase):
    def mixed_fixture(self, root, fmt):
        bits, palette_size = (4, 32) if fmt == 'ci4' else (8, 512)
        levels, cursor = [], 0
        for index, (form, height) in enumerate(((fmt, 8), (fmt, 4), ('ia4', 2))):
            size = 8 * height
            levels.append({'level': index, 'format': form, 'role': 'detail' if index == 2 else 'mip',
                           'offset': cursor, 'width': 16 if form == 'ia4' else 64 // bits,
                           'height': height, 'bytes': size})
            cursor += size
        payload = bytes(range(cursor)) + bytes(16) + bytes(i % 256 for i in range(palette_size))
        packed = rzip_pack.encode_rzip_chunk(payload)
        texture = t.TextureAsset(54, 0, len(packed), payload)
        contract = {'format': fmt, 'width': 64 // bits, 'height': 8, 'row_layout': t.ROW_LAYOUT_TMEM,
                    'mixed_detail': True, 'palette_size': palette_size, 'levels': levels,
                    'zero_alignment': {'offset': cursor, 'size': 16, 'alignment': 64}}
        expected = build.describe_texture(packed, texture, contract=contract)
        directory = root / fmt
        build.initialize_inputs(directory, expected, payload)
        return directory, expected, packed

    def test_mixed_detail_sources_roundtrip_with_full_indexed_palette(self):
        with tempfile.TemporaryDirectory() as tmp:
            for fmt in ('ci4', 'ci8'):
                directory, expected, packed = self.mixed_fixture(Path(tmp), fmt)
                self.assertEqual(expected['schema_version'], 4)
                self.assertTrue(expected['files'][-1].endswith('.ia4.png'))
                result, hashes = build.packed_texture(directory, expected)
                self.assertEqual(result, packed)
                self.assertEqual(set(hashes), {'manifest.json', *expected['files']})
                name, plane, _, size = build.source_images(expected)[0][-1]
                raw = build.source_png((directory / name).read_bytes(), plane, decode=True)
                self.assertEqual(len(raw), size)  # IA4 has no indexed palette.

    def test_mixed_detail_changes_missing_input_and_race_fail(self):
        for failure in ('change', 'missing', 'race', 'palette'):
            with self.subTest(failure=failure), tempfile.TemporaryDirectory() as tmp:
                directory, expected, packed = self.mixed_fixture(Path(tmp), 'ci8')
                images = build.source_images(expected)[0]
                name, plane, _, _ = images[1 if failure == 'palette' else -1]
                path = directory / name
                if failure == 'race':
                    def encode(*_):
                        path.write_bytes(path.read_bytes() + b'changed')
                        return packed
                    with patch.object(build, 'encode_payload', side_effect=encode), \
                            self.assertRaisesRegex(ValueError, 'changed during packing'):
                        build.packed_texture(directory, expected)
                    continue
                if failure == 'missing':
                    path.unlink()
                    error, message = FileNotFoundError, ''
                else:
                    raw = bytearray(build.source_png(path.read_bytes(), plane, decode=True))
                    raw[-1 if failure == 'palette' else 0] ^= 1
                    path.write_bytes(build.source_png(bytes(raw), plane))
                    error, message = ValueError, 'shared palette' if failure == 'palette' else 'original payload'
                with self.assertRaisesRegex(error, message):
                    build.packed_texture(directory, expected)

    def test_mixed_detail_wrong_format_role_gap_and_unrepresented_tail_fail(self):
        with tempfile.TemporaryDirectory() as tmp:
            _, expected, _ = self.mixed_fixture(Path(tmp), 'ci4')
            for change in ('format', 'role', 'gap', 'tail'):
                altered = copy.deepcopy(expected)
                last = altered['source_contract']['levels'][-1]
                if change == 'format':
                    last['format'] = 'ci4'
                elif change == 'role':
                    last['role'] = 'mip'
                elif change == 'gap':
                    last['offset'] += 1
                else:
                    altered['decoded_size'] += 1
                with self.assertRaises(ValueError):
                    build.source_images(altered)

    def fixture(self, root, fmt='ci8', padding=0):
        palette_size = 512 if fmt == 'ci8' else 0
        payload = bytes(i % 256 for i in range(112 + palette_size))
        payload = payload[:112] + bytes(padding) + payload[112:]
        packed = rzip_pack.encode_rzip_chunk(payload)
        texture = t.TextureAsset(53, 0, len(packed), payload)
        contract = {'identity': 'runtime-resource', 'format': fmt, 'width': 8, 'height': 8,
                    'row_layout': t.ROW_LAYOUT_TMEM, 'source_origin': 'bottom-left',
                    'palette_size': palette_size, 'levels': [
                        {'level': 0, 'offset': 0, 'width': 8, 'height': 8, 'bytes': 64},
                        {'level': 1, 'offset': 64, 'width': 8, 'height': 4, 'bytes': 32},
                        {'level': 2, 'offset': 96, 'width': 8, 'height': 2, 'bytes': 16}]}
        if padding:
            contract['zero_alignment'] = {'offset': 112, 'size': padding, 'alignment': 64}
        expected = build.describe_texture(packed, texture, contract=contract)
        directory = root / fmt
        build.initialize_inputs(directory, expected, payload)
        return directory, expected, payload, packed

    def test_unloaded_alignment_is_generated_zero_without_an_opaque_input(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            directory, expected, payload, packed = self.fixture(root, padding=16)
            self.assertEqual(expected['schema_version'], 3)
            self.assertEqual(build.packed_texture(directory, expected)[0], packed)
            self.assertEqual(set(p.name for p in directory.iterdir()), {'manifest.json', *expected['files']})
            changed = bytearray(payload)
            changed[112] = 1
            with self.assertRaisesRegex(ValueError, 'alignment bytes are not zero'):
                build.initialize_inputs(root / 'nonzero', expected, bytes(changed))
            self.assertFalse((root / 'nonzero').exists())
            for change in ({'size': 15}, {'size': 80}, {'offset': 111}, {'alignment': 32}):
                altered = copy.deepcopy(expected)
                altered['source_contract']['zero_alignment'].update(change)
                with self.assertRaisesRegex(ValueError, 'zero alignment'):
                    build.source_images(altered)
            altered = copy.deepcopy(expected)
            del altered['source_contract']['zero_alignment']
            with self.assertRaisesRegex(ValueError, 'lacks zero alignment'):
                build.source_images(altered)
            native_dir, native_expected, _, native_packed = self.fixture(root, 'i8', padding=16)
            self.assertEqual(build.packed_texture(native_dir, native_expected)[0], native_packed)

    def test_all_levels_rebuild_exactly_with_or_without_palette(self):
        with tempfile.TemporaryDirectory() as tmp:
            for fmt in ('ci8', 'i8'):
                directory, expected, payload, packed = self.fixture(Path(tmp), fmt)
                result, hashes = build.packed_texture(directory, expected)
                self.assertEqual(result, packed)
                self.assertEqual(set(hashes), {'manifest.json', *expected['files']})
                self.assertNotIn('file', expected)
                with self.assertRaisesRegex(ValueError, 'refusing to overwrite'):
                    build.initialize_inputs(directory, expected, payload)

    def test_lower_mip_change_missing_file_and_palette_disagreement_fail(self):
        for failure in ('pixels', 'missing', 'palette'):
            with self.subTest(failure=failure), tempfile.TemporaryDirectory() as tmp:
                directory, expected, payload, _ = self.fixture(Path(tmp))
                name, plane, offset, size = build.source_images(expected)[0][-1]
                if failure == 'missing':
                    (directory / name).unlink()
                    error, message = FileNotFoundError, ''
                else:
                    raw = bytearray(payload[offset:offset + size] + payload[-512:])
                    raw[0 if failure == 'pixels' else -1] ^= 1
                    (directory / name).write_bytes(build.source_png(bytes(raw), plane))
                    error, message = ValueError, 'original payload' if failure == 'pixels' else 'shared palette'
                with self.assertRaisesRegex(error, message):
                    build.packed_texture(directory, expected)

    def test_gap_overlap_and_unrepresented_tail_fail_before_initialization(self):
        with tempfile.TemporaryDirectory() as tmp:
            _, expected, payload, _ = self.fixture(Path(tmp))
            for update in ('gap', 'overlap', 'tail'):
                changed = copy.deepcopy(expected)
                if update == 'tail':
                    changed['decoded_size'] += 1
                else:
                    changed['source_contract']['levels'][1]['offset'] += 1 if update == 'gap' else -1
                target = Path(tmp) / update
                with self.assertRaisesRegex(ValueError, 'cover'):
                    build.initialize_inputs(target, changed, payload)
                self.assertFalse(target.exists())

    def test_lower_mip_race_is_detected(self):
        with tempfile.TemporaryDirectory() as tmp:
            directory, expected, _, packed = self.fixture(Path(tmp))
            def encode(*_):
                path = directory / expected['files'][-1]
                path.write_bytes(path.read_bytes() + b'changed')
                return packed
            with patch.object(build, 'encode_payload', side_effect=encode), \
                    self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_texture(directory, expected)
