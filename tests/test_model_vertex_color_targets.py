"""ROM-free source contracts and native integer color interpolation checks."""
import copy
import hashlib
import json
import struct
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from scripts import model_vertex_color_targets as colors


def fixture_model():
    raw = bytearray(160)
    struct.pack_into('>10I', raw, 0, 88, 32, 0, 0, 0, 0, 0, 0, 136, 0x80000018)
    for index, rgba in enumerate(((0, 255, 128, 7), (50, 60, 70, 0), (255, 0, 10, 255))):
        struct.pack_into('>hhhHhh4B', raw, 40 + index * 16, index, 0, 0, 0, 0, 0, *rgba)
    struct.pack_into('>8I', raw, 88, 0xD7000000, 0xFFFFFFFF, 0x01003006, 0x01000000, 0x05000204, 0, 0xDF000000, 0)
    raw[120:129] = bytes((10, 90, 240, 20, 30, 40, 50, 60, 70))
    struct.pack_into('>3H', raw, 129, 2, 0, 2)
    struct.pack_into('>6I', raw, 136, 120, 129, 3, 0, 0x00FACADE, 0x1234)
    return bytes(raw)


class VertexColorInterpolationTests(unittest.TestCase):
    def test_native_signed_shift_and_alpha_preservation(self):
        base, target = (10, 250, 128, 37), (11, 249, 255)
        self.assertEqual((10, 250, 128, 37), colors.interpolate_rgba(base, target, 0))
        self.assertEqual((10, 249, 128, 37), colors.interpolate_rgba(base, target, 1))
        self.assertEqual((10, 249, 191, 37), colors.interpolate_rgba(base, target, 128))
        self.assertEqual((10, 249, 254, 37), colors.interpolate_rgba(base, target, 255))
        self.assertEqual((254, 0, 128, 0), colors.interpolate_rgba((0, 255, 128, 0), (255, 0, 128), 255))

    def test_explicit_byte_domain_prevents_native_product_overflow(self):
        for factor in (-1, 256, True, 1.0):
            with self.subTest(factor=factor), self.assertRaises(ValueError):
                colors.interpolate_rgba((0, 0, 0, 0), (255, 255, 255), factor)
        for channel in (-1, 256, True, 1.0):
            with self.subTest(channel=channel), self.assertRaises(ValueError):
                colors.interpolate_rgba((channel, 0, 0, 0), (1, 2, 3), 128)
        for base, target in (((0, 0, 0), (0, 0, 0)), ((0, 0, 0, 0), (0, 0)),
                             ((0, 0, 0, 0), 'rgb')):
            with self.subTest(base=base, target=target), self.assertRaises(ValueError):
                colors.interpolate_rgba(base, target, 0)


class VertexColorArrayTests(unittest.TestCase):
    def decode(self, raw):
        return colors.decode_model(raw, hashlib.sha1(raw).hexdigest())

    def test_order_duplicates_alpha_and_unknown_terminator_words_survive_json(self):
        raw = fixture_model()
        result = json.loads(json.dumps(self.decode(raw)))
        target = result['targets'][0]
        self.assertEqual([2, 0, 2], [v['vertex_index'] for v in target['vertices']])
        self.assertEqual([[255, 0, 10, 255], [0, 255, 128, 7], [255, 0, 10, 255]],
                         [v['stored_source_rgba'] for v in target['vertices']])
        self.assertEqual([0, 0x00FACADE, 0x1234], result['descriptor_table']['terminator_words'])
        indices, rgb, rgba = colors.encode_descriptor_arrays(target)
        self.assertEqual(raw[129:135], indices)
        self.assertEqual(raw[120:129], rgb)
        self.assertEqual(raw[84:88] + raw[52:56] + raw[84:88], rgba)
        self.assertEqual(3, target['changed_rgb_reference_count'])
        self.assertEqual(3, result['source_vertex_count'])
        self.assertEqual(1, result['source_face_count'])
        self.assertEqual(fixture_model(), raw)

    def test_all_model_bytes_are_guarded(self):
        raw = fixture_model()
        digest = hashlib.sha1(raw).hexdigest()
        for offset in (0, 52, 55, 120, 129, 136, 159):
            altered = bytearray(raw)
            altered[offset] ^= 1
            with self.subTest(offset=offset), self.assertRaisesRegex(ValueError, 'source model changed'):
                colors.decode_model(bytes(altered), digest)

    def test_truncation_invalid_indices_and_missing_table_are_rejected(self):
        raw = bytearray(fixture_model())
        struct.pack_into('>H', raw, 129, 3)
        with self.assertRaisesRegex(ValueError, 'invalid vertex'):
            self.decode(bytes(raw))
        with self.assertRaises(ValueError):
            self.decode(fixture_model()[:-1])
        raw = bytearray(fixture_model())
        struct.pack_into('>II', raw, 32, 0, 0x80000000)
        with self.assertRaisesRegex(ValueError, 'no target descriptors'):
            self.decode(bytes(raw))

    def test_encoder_rejects_changed_counts_and_field_widths(self):
        record = self.decode(fixture_model())['targets'][0]
        bad = copy.deepcopy(record)
        bad['vertex_count'] = 4
        with self.assertRaisesRegex(ValueError, 'count'):
            colors.encode_descriptor_arrays(bad)
        for field, value in (('vertex_index', 65536), ('vertex_index', True),
                             ('target_rgb', [1, 2, 256]), ('stored_source_rgba', [0, 0, 0])):
            bad = copy.deepcopy(record)
            bad['vertices'][0][field] = value
            with self.subTest(field=field), self.assertRaises(ValueError):
                colors.encode_descriptor_arrays(bad)


class VertexColorConsumerTests(unittest.TestCase):
    code_base, data_base = 0x15000000, 0x80082B20

    def source(self):
        size = max(a + n for a, n, _ in colors.CONSUMERS) - self.code_base
        code = (bytes(range(256)) * (size // 256 + 1))[:size]
        data = bytearray(colors.DISPATCH_ADDRESS + len(colors.DISPATCH_BYTES) - self.data_base)
        data[-len(colors.DISPATCH_BYTES):] = colors.DISPATCH_BYTES
        pins = [(a, n, hashlib.sha1(code[a-self.code_base:a-self.code_base+n]).hexdigest())
                for a, n, _ in colors.CONSUMERS]
        return code, bytes(data), pins

    def test_complete_consumers_and_dispatch_bytes_reject_mutations(self):
        code, data, pins = self.source()
        with patch.object(colors, 'CONSUMERS', pins):
            self.assertEqual(len(pins), len(colors.verify_consumers(code, self.code_base, data, self.data_base)))
            for address, size, _ in pins:
                for delta in (0, size // 2, size - 1):
                    mutated = bytearray(code)
                    mutated[address-self.code_base+delta] ^= 1
                    with self.subTest(address=address, delta=delta), self.assertRaises(ValueError):
                        colors.verify_consumers(mutated, self.code_base, data, self.data_base)
            for delta in range(len(colors.DISPATCH_BYTES)):
                mutated = bytearray(data)
                mutated[-len(colors.DISPATCH_BYTES)+delta] ^= 1
                with self.subTest(dispatch_byte=delta), self.assertRaises(ValueError):
                    colors.verify_consumers(code, self.code_base, mutated, self.data_base)
            for c, cb, d, db in ((code[:-1], self.code_base, data, self.data_base),
                                  (code, self.code_base, data[:-1], self.data_base),
                                  (code, self.code_base+4, data, self.data_base)):
                with self.assertRaises(ValueError):
                    colors.verify_consumers(c, cb, d, db)

    def test_controller_links_are_pinned_source_requests_not_activation(self):
        raw = bytearray(68)
        struct.pack_into('>II', raw, 0x14, 17, 2)
        raw[0x34] = 1
        record = {'index': 9, 'raw_hex': raw.hex(), 'model_source': [4, 4, 17],
                  'word_14': '0x00000011', 'word_18': '0x00000002'}
        placements = {'scenes': [{'bank_index': 11, 'scene_index': 4, 'records': [record]}]}
        pins = ((4, 9, 17, 2, hashlib.sha1(raw).hexdigest()),)
        with patch.object(colors, 'PLACEMENTS', pins):
            result = colors.controller_links(placements)
            self.assertEqual([4, 4, 0], result[0]['target_model'])
            self.assertEqual(2, result[0]['target_index'])
            self.assertEqual(1, result[0]['initial_inactive_byte_34'])
            for field, value in (('raw_hex', bytes(68).hex()), ('model_source', [4, 4, 18]),
                                 ('word_14', '0x12'), ('word_18', '0x03')):
                bad = copy.deepcopy(placements)
                bad['scenes'][0]['records'][0][field] = value
                with self.subTest(field=field), self.assertRaises(ValueError):
                    colors.controller_links(bad)
            with self.assertRaises(ValueError):
                colors.controller_links({'scenes': []})

    def test_output_verification_detects_edits_and_existing_export_is_preserved(self):
        manifest = {'targets': [1, 2, 3]}
        expected = b'{"targets":[1,2,3]}\n'
        with tempfile.TemporaryDirectory() as tmp, patch.object(colors, 'build_export', return_value=(manifest, {'manifest.json': expected})):
            output = Path(tmp) / 'targets'
            self.assertEqual(manifest, colors.export(output))
            self.assertEqual(manifest, colors.export(output, verify=True))
            with self.assertRaises(FileExistsError):
                colors.export(output)
            self.assertEqual(expected, (output / 'manifest.json').read_bytes())
            (output / 'manifest.json').write_bytes(expected + b' ')
            with self.assertRaisesRegex(ValueError, 'differs from ROM'):
                colors.export(output, verify=True)
            self.assertEqual(expected + b' ', (output / 'manifest.json').read_bytes())


if __name__ == '__main__':
    unittest.main()
