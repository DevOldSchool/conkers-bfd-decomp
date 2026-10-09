"""Every mip level and shared palette is a required PNG build input."""
import copy
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from scripts import texture_assets as t, texture_build as build, rzip_pack


class MipmapBuildTests(unittest.TestCase):
    def fixture(self, root, fmt='ci8'):
        palette_size = 512 if fmt == 'ci8' else 0
        payload = bytes(i % 256 for i in range(112 + palette_size))
        packed = rzip_pack.encode_rzip_chunk(payload)
        texture = t.TextureAsset(53, 0, len(packed), payload)
        contract = {'identity': 'runtime-resource', 'format': fmt, 'width': 8, 'height': 8,
                    'row_layout': t.ROW_LAYOUT_TMEM, 'source_origin': 'bottom-left',
                    'palette_size': palette_size, 'levels': [
                        {'level': 0, 'offset': 0, 'width': 8, 'height': 8, 'bytes': 64},
                        {'level': 1, 'offset': 64, 'width': 8, 'height': 4, 'bytes': 32},
                        {'level': 2, 'offset': 96, 'width': 8, 'height': 2, 'bytes': 16}]}
        expected = build.describe_texture(packed, texture, contract=contract)
        directory = root / fmt
        build.initialize_inputs(directory, expected, payload)
        return directory, expected, payload, packed

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
