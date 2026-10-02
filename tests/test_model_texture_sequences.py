"""Complete frame proofs and read-only verification for texture sequence exports."""
import copy
import hashlib
import tempfile
import unittest
from dataclasses import replace
from pathlib import Path
from unittest import mock

from scripts import model_assets as models
from scripts import model_texture_sequences as sequences
from scripts.texture_assets import decode_indexed_png, decode_rgba_png_pixels


def object_ci4_fixture():
    # The display list binds a segmented pixel image and a separate tail TLUT.
    run = models.ModelMaterialRun(
        first_face=0, face_count=1, texture_enabled=True,
        pixel=models.ModelTextureBinding(0xFD500000, segment=4, offset=0,
                                        load_command=(0xF3000000, 0x0715F000)),
        palette=models.ModelTextureBinding(0xFD100000, segment=5, offset=0,
                                          load_command=(0xF0000000, 0x0603C000)),
        render_tile=(0xF5400400, 0x00014050),
        render_tiles=((0, 0xF5400400, 0x00014050),
                      (1, 0xF5400240, 0x01010040),
                      (6, 0xF5600100, 0x06000000),
                      (7, 0xF5500000, 0x07000000)),
        tile_bounds=(0xF2000000, 0x0007C07C),
        texture_scale=(0xD7000002, 0xFFFFFFFF),
        combine_mode=(0xFC121824, 0x5531FEFF),
        other_mode=(0xEF19AC3F, 0x0C192230),
        runtime_render_state_offset=None,
    )
    # A blue decoy in end-512 distinguishes an incorrect CI8 palette remap.
    body = bytes(224) + bytes.fromhex('003f') * 16 + bytes(448)
    payloads = {42: body + bytes.fromhex('f801') * 16,
                43: body + bytes.fromhex('07c1') * 16}
    context = {'texture_animation': {'frames': [43, 42, 43], 'preview_frame': 0}}
    return run, context, payloads


def scene_rgba16_fixture():
    run, _, _ = object_ci4_fixture()
    run = replace(run,
        pixel=models.ModelTextureBinding(0xFD100000, segment=2, offset=0,
                                        load_command=(0xF3000000, 0x07007000)),
        palette=None,
        render_tile=(0xF5100200, 0),
        render_tiles=((0, 0xF5100200, 0), (7, 0xF5100000, 0x07000000)),
        tile_bounds=(0xF2000000, 0x0000C004),
        other_mode=(0xEF082C3F, 0x00504A50),
        combine_mode=(0xFC121824, 0xFF33FFFF))
    context = {'entry': 26, 'renderer': 'scene', 'scope': 'inspection state',
        'scene_texture_state': {'bindings': {'2': {'pixel_segment': 2,
            'frames': [42, 43], 'selected_index': 1, 'selected_flat': 43}}}}
    payloads = {42: bytes.fromhex('ffff') * 8, 43: bytes.fromhex('f801') * 8}
    return run, context, payloads


class EncodeSequenceFramesTests(unittest.TestCase):
    def object_proof(self, run, context, payloads, tables=()):
        texture, _, proof = models.rom_object_animation_preview_texture(
            run, {}, payloads, tables, context)
        self.assertIsNotNone(texture)
        return proof

    def scene_proof(self, run, context, payloads):
        texture, _, proof = models.rom_scene_preview_texture(run, {}, payloads, context)
        self.assertIsNotNone(texture)
        return proof

    def test_ci4_frames_preserve_order_duplicates_and_each_tail_palette(self):
        run, context, payloads = object_ci4_fixture()
        proof = self.object_proof(run, context, payloads)
        before = copy.deepcopy((run, context, payloads, proof))
        decoded = sequences.encode_frames(run, context, proof, payloads, [])
        self.assertEqual([43, 42, 43], [texture.flat_index for texture, _ in decoded])
        green, red = bytes.fromhex('07c1'), bytes.fromhex('f801')
        for (texture, _), frame, color in zip(decoded, proof['frames'], (green, red, green)):
            self.assertEqual((32, 32, 2, 0),
                             (texture.width, texture.height, texture.format, texture.size))
            self.assertEqual(704, texture.palette_byte_offset)
            # Every possible four-bit index maps to the same known color.
            # Read the PNG palette itself, independently of the binding proof.
            indexed = decode_indexed_png(texture.png_data, 'linear', 32, 32)
            self.assertEqual(544, len(indexed))
            self.assertEqual(color * 16, indexed[-32:])
            self.assertEqual(frame['png_sha1'], hashlib.sha1(texture.png_data).hexdigest())
        self.assertEqual(before, (run, context, payloads, proof))

    def test_scene_decodes_all_frames_in_array_order_not_selected_order(self):
        run, context, payloads = scene_rgba16_fixture()
        selected, _, _ = models.rom_scene_preview_texture(run, {}, payloads, context)
        self.assertEqual(43, selected.flat_index)
        proof = self.scene_proof(run, context, payloads)
        before = copy.deepcopy((run, context, payloads, proof))
        decoded = sequences.encode_frames(run, context, proof, payloads, [])
        self.assertEqual([42, 43], [texture.flat_index for texture, _ in decoded])
        for (texture, _), frame, color in zip(decoded, proof['decoded_frames'],
                (bytes((255, 255, 255, 255)), bytes((255, 0, 0, 255)))):
            self.assertIsNone(texture.palette_byte_offset)
            self.assertEqual(color * 8, decode_rgba_png_pixels(texture.png_data, 4, 2))
            self.assertEqual(frame['png_sha1'], hashlib.sha1(texture.png_data).hexdigest())
        self.assertEqual(before, (run, context, payloads, proof))

    def test_noninitial_png_proof_mismatch_is_rejected(self):
        for fixture, proof_method, key in (
                (object_ci4_fixture, self.object_proof, 'frames'),
                (scene_rgba16_fixture, self.scene_proof, 'decoded_frames')):
            with self.subTest(kind=key):
                run, context, payloads = fixture()
                proof = proof_method(run, context, payloads)
                proof[key][1]['png_sha1'] = '0' * 40
                with self.assertRaisesRegex(ValueError, 'complete ROM binding proof'):
                    sequences.encode_frames(run, context, proof, payloads, [])

    def test_changed_missing_and_truncated_noninitial_payloads_fail_closed(self):
        for fixture, proof_method, changed_flat, replacement in (
                (object_ci4_fixture, self.object_proof, 42,
                 bytes(704) + bytes.fromhex('003f') * 16),
                (scene_rgba16_fixture, self.scene_proof, 43,
                 bytes.fromhex('003f') * 8)):
            run, context, original = fixture()
            proof = proof_method(run, context, original)
            for label, value in (('changed', replacement), ('missing', None), ('short', b'\x00')):
                payloads = dict(original)
                if value is None:
                    del payloads[changed_flat]
                else:
                    payloads[changed_flat] = value
                with self.subTest(kind=fixture.__name__, mutation=label):
                    with self.assertRaisesRegex(ValueError, 'complete ROM binding proof'):
                        sequences.encode_frames(run, context, proof, payloads, [])

    def test_object_inherited_state_requires_every_verified_render_table(self):
        scene_run, _, payloads = scene_rgba16_fixture()
        run = replace(scene_run, pixel=replace(scene_run.pixel, segment=4),
                      other_mode=None, runtime_render_state_offset=0x30)
        context = {'bank': 4, 'entry': 7, 'segment': 9, 'renderer': 'func_151137D4',
                   'segment_8_bases': [], 'scope': 'ordinary placement draw',
                   'texture_animation': {'frames': [42, 43], 'preview_frame': 0}}
        tables = [{'base_address': hex(base), 'entries': [
            {'offset': '0x30', 'other_mode': ['0xEF082C3F', '0x00504A50']}]} for base in
            models.RUNTIME_RENDER_STATE_TABLE_BASES]
        proof = self.object_proof(run, context, payloads, tables)
        decoded = sequences.encode_frames(run, context, proof, payloads, tables)
        self.assertEqual([42, 43], [texture.flat_index for texture, _ in decoded])
        self.assertTrue(all(status.startswith('rom-state-consensus-') for _, status in decoded))
        with self.assertRaisesRegex(ValueError, 'every verified table'):
            sequences.encode_frames(run, context, proof, payloads, tables[:-1])
        bad_tables = copy.deepcopy(tables)
        bad_tables[-1]['entries'][0]['other_mode'][0] = '0xEF08AC3F'
        with self.assertRaisesRegex(ValueError, 'complete ROM binding proof'):
            sequences.encode_frames(run, context, proof, payloads, bad_tables)


class TextureSequenceOutputTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.output = Path(self.temp.name) / 'sequences'
        self.manifest = {'summary': {'image_count': 2}, 'test_fixture': True}
        self.files = {'manifest.json': b'{"test_fixture": true}\n',
                      'textures/first.png': b'first texture',
                      'textures/second.png': b'second texture'}
        self.builder = mock.patch.object(sequences, 'build_export',
                                         return_value=(self.manifest, self.files)).start()
        self.addCleanup(mock.patch.stopall)

    def snapshot(self):
        return {str(path.relative_to(self.output)): path.read_bytes()
                for path in self.output.rglob('*') if path.is_file()}

    def assert_verify_read_only(self, expected_error=None):
        before = self.snapshot()
        with mock.patch.object(Path, 'mkdir', side_effect=AssertionError('verification created a directory')), \
             mock.patch.object(Path, 'write_bytes', side_effect=AssertionError('verification wrote a file')):
            if expected_error is None:
                self.assertEqual(self.manifest, sequences.export(self.output, verify=True))
            else:
                with self.assertRaises(expected_error):
                    sequences.export(self.output, verify=True)
        self.assertEqual(before, self.snapshot())

    def test_new_export_writes_every_file_and_verifies_without_writes(self):
        self.assertEqual(self.manifest, sequences.export(self.output, 'test-rom.z64'))
        self.builder.assert_called_once_with('test-rom.z64')
        self.assertEqual(self.files, self.snapshot())
        self.assert_verify_read_only()

    def test_existing_output_is_not_overwritten_even_when_empty(self):
        self.output.mkdir()
        with self.assertRaises(FileExistsError):
            sequences.export(self.output)
        self.assertEqual({}, self.snapshot())
        sentinel = self.output / 'manifest.json'
        sentinel.write_bytes(b'keep existing output')
        before = self.snapshot()
        with self.assertRaises(FileExistsError):
            sequences.export(self.output)
        self.assertEqual(before, self.snapshot())

    def test_verification_rejects_tampered_manifest_and_later_texture_without_writes(self):
        sequences.export(self.output)
        for name in ('manifest.json', 'textures/second.png'):
            with self.subTest(file=name):
                path = self.output / name
                path.write_bytes(b'tampered')
                self.assert_verify_read_only(ValueError)
                path.write_bytes(self.files[name])

    def test_verification_rejects_missing_texture_without_recreating_it(self):
        sequences.export(self.output)
        (self.output / 'textures/second.png').unlink()
        self.assert_verify_read_only(FileNotFoundError)
        self.assertFalse((self.output / 'textures/second.png').exists())

    def test_missing_output_and_failed_rom_proof_do_not_create_directories(self):
        self.assert_verify_read_only(FileNotFoundError)
        self.assertFalse(self.output.exists())
        self.builder.side_effect = ValueError('ROM proof failed')
        with self.assertRaisesRegex(ValueError, 'ROM proof failed'):
            sequences.export(self.output)
        self.assertFalse(self.output.exists())


if __name__ == '__main__':
    unittest.main()
