"""Exact PNG reconstruction and fail-closed compressed build inputs."""
import json
import hashlib
from pathlib import Path
import tempfile
import unittest
import zlib
from types import SimpleNamespace
from unittest.mock import patch

import yaml

from scripts import texture_assets, texture_build as build, rzip_pack


class TextureBuildTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.inputs = self.root / build.input_directory(1063)
        # Synthetic pixels and palette; no game bytes in tests.
        self.payload = bytes(range(256)) * 8 + bytes(range(32))
        self.packed = rzip_pack.encode_rzip_chunk(self.payload)
        self.start, self.end = 20, 20 + len(self.packed)
        self.rom = bytes(20) + self.packed + bytes(4)
        self.texture = texture_assets.TextureAsset(1063, self.start, self.end, self.payload)
        self.expected = build.describe_texture(self.rom, self.texture, encoder=build.ENCODERS['zlib'])
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
        names = [row[2].rsplit('/', 1)[1] for row in self.document['segments'][0]['subsegments']
                 if row[2].startswith('flat/textures/')]
        (self.root / build.ENCODER_CONTRACT).write_text(json.dumps({
            'schema_version': 1, 'profile': 'us', 'rom_sha1': hashlib.sha1(self.rom).hexdigest(),
            'encoders': {name: 'zlib' for name in names}}))

    def initialize(self):
        build.initialize_inputs(self.inputs, self.expected, self.payload)

    def test_committed_encoder_selection_never_probes_the_runtime_compressor(self):
        with patch.object(rzip_pack, 'encode_rzip_chunk', side_effect=AssertionError('must not probe')):
            _, selected = build.reviewed_textures(self.root)
        self.assertEqual(selected[0][0], self.expected)
        path = self.root / build.ENCODER_CONTRACT
        document = json.loads(path.read_text())
        document['encoders']['1063'] = 'gzip'
        path.write_text(json.dumps(document))
        # Even a runtime that would reproduce this payload with zlib must retain
        # the committed gzip choice, without probing either compressor.
        with patch.object(rzip_pack, 'encode_rzip_chunk', side_effect=AssertionError('must not probe')):
            _, selected = build.reviewed_textures(self.root)
        self.assertEqual(selected[0][0]['encoder'], build.ENCODERS['gzip'])

    def test_encoder_drift_fails_build_without_changing_manifest_or_choosing_fallback(self):
        self.initialize()
        manifest = (self.inputs / 'manifest.json').read_bytes()
        changed = self.packed[:-1] + bytes([self.packed[-1] ^ 1])
        with patch.object(rzip_pack, 'encode_rzip_chunk', return_value=changed) as encode, \
                patch.object(build.rzip_gzip.subprocess, 'run', side_effect=AssertionError('no fallback')), \
                self.assertRaisesRegex(ValueError, 'reviewed encoder output differs'):
            build.build_parts(self.root)
        self.assertEqual(encode.call_count, 1)
        self.assertEqual((self.inputs / 'manifest.json').read_bytes(), manifest)

    def test_encoder_contract_rejects_missing_extra_unknown_or_wrong_rom_entries(self):
        path = self.root / build.ENCODER_CONTRACT
        original = path.read_text()
        for error in ('missing', 'extra', 'unknown', 'rom', 'version'):
            with self.subTest(error=error):
                document = json.loads(original)
                if error == 'missing':
                    del document['encoders']['1063']
                elif error == 'extra':
                    document['encoders']['0001'] = 'zlib'
                elif error == 'unknown':
                    document['encoders']['1063'] = 'automatic'
                elif error == 'rom':
                    document['rom_sha1'] = 'wrong'
                else:
                    document['schema_version'] = 2
                path.write_text(json.dumps(document))
                with self.assertRaisesRegex(ValueError, 'committed texture encoder contract'):
                    build.build_parts(self.root)
                self.assertFalse(self.inputs.exists())

    def test_repository_encoder_contract_covers_exactly_the_selected_texture_rows(self):
        root = Path(__file__).resolve().parent.parent
        rows, _ = build.layout_bins(root / 'config/profiles/us.yaml')
        selected = {int(name.rsplit('/', 1)[1]) for _, name in rows
                    if name.startswith('flat/textures/')}
        document = json.loads((root / build.ENCODER_CONTRACT).read_text())
        self.assertEqual(set(build.reviewed_encoders(root, selected, document['rom_sha1'])), selected)

    def test_interrupted_initialization_never_publishes_partial_bundle_and_retries(self):
        write = Path.write_bytes
        rename = Path.rename
        for failure in ('png', 'manifest', 'publish'):
            for parent in ('direct', 'runtime'):
                directory = self.root / parent / failure
                def interrupted_write(path, data):
                    result = write(path, data)
                    if ((failure == 'manifest' and path.name == 'manifest.json')
                            or (failure == 'png' and path.suffix == '.png')):
                        raise KeyboardInterrupt('simulated interruption')
                    return result
                def interrupted_rename(path, target):
                    if failure == 'publish':
                        raise KeyboardInterrupt('simulated interruption')
                    return rename(path, target)
                with self.subTest(failure=failure, parent=parent), \
                        patch.object(Path, 'write_bytes', interrupted_write), \
                        patch.object(Path, 'rename', interrupted_rename), \
                        self.assertRaises(KeyboardInterrupt):
                    build.initialize_inputs(directory, self.expected, self.payload)
                self.assertFalse(directory.exists())
                # A hard-killed process may leave a hidden staging directory;
                # it must not block publishing a new complete bundle.
                abandoned = directory.parent / ('.' + directory.name + '.staging-abandoned')
                abandoned.mkdir()
                (abandoned / 'partial.png').write_bytes(b'partial')
                build.initialize_inputs(directory, self.expected, self.payload)
                self.assertEqual(build.packed_texture(directory, self.expected)[0], self.packed)

    def legacy_bundle(self):
        legacy = self.root / build.INPUT_DIRECTORY
        build.initialize_inputs(legacy, self.expected, self.payload)
        # Noncanonical formatting and user-edited bytes must survive migration.
        (legacy / 'manifest.json').write_text(json.dumps(self.expected, indent=4))
        return legacy

    def test_legacy_migration_preserves_input_bytes_and_sibling_directories(self):
        legacy = self.legacy_bundle()
        (legacy / self.expected['file']).write_bytes(b'user-edited PNG')
        files = {p.name: p.read_bytes() for p in legacy.iterdir()}
        sibling = legacy / 'runtime/0053/keep.png'
        sibling.parent.mkdir(parents=True)
        sibling.write_bytes(b'unrelated input')
        build.migrate_legacy_inputs(self.root, self.expected)
        self.assertEqual({p.name: p.read_bytes() for p in self.inputs.iterdir()}, files)
        self.assertTrue(all(not (legacy / name).exists() for name in files))
        self.assertEqual(sibling.read_bytes(), b'unrelated input')

    def test_interrupted_legacy_migration_resumes_before_or_after_publication(self):
        for failure in ('publish', 'cleanup'):
            with self.subTest(failure=failure):
                # Each iteration gets an independent legacy bundle.
                directory = self.root / failure
                legacy = directory / build.INPUT_DIRECTORY
                destination = directory / build.input_directory(1063)
                build.initialize_inputs(legacy, self.expected, self.payload)
                files = {p.name: p.read_bytes() for p in legacy.iterdir()}
                unlink = Path.unlink
                def interrupted_unlink(path, *args, **kwargs):
                    result = unlink(path, *args, **kwargs)
                    if path.parent == legacy:
                        raise KeyboardInterrupt('interrupted old-file cleanup')
                    return result
                context = (patch.object(Path, 'rename', side_effect=KeyboardInterrupt('before publication'))
                           if failure == 'publish' else patch.object(Path, 'unlink', interrupted_unlink))
                with context, self.assertRaises(KeyboardInterrupt):
                    build.migrate_legacy_inputs(directory, self.expected)
                if failure == 'publish':
                    self.assertFalse(destination.exists())
                    self.assertEqual({p.name: p.read_bytes() for p in legacy.iterdir()}, files)
                else:
                    self.assertEqual({p.name: p.read_bytes() for p in destination.iterdir()}, files)
                build.migrate_legacy_inputs(directory, self.expected)
                self.assertEqual({p.name: p.read_bytes() for p in destination.iterdir()}, files)
                self.assertTrue(all(not (legacy / name).exists() for name in files))

    def test_conflicting_legacy_bundle_is_preserved_without_removing_any_files(self):
        legacy = self.legacy_bundle()
        self.initialize()
        # Keep manifest formatting identical so the PNG is the conflict.
        (self.inputs / 'manifest.json').write_bytes((legacy / 'manifest.json').read_bytes())
        (legacy / self.expected['file']).write_bytes(b'different user input')
        with self.assertRaisesRegex(ValueError, 'conflict'):
            build.migrate_legacy_inputs(self.root, self.expected)
        self.assertTrue((legacy / 'manifest.json').exists())
        self.assertEqual((legacy / self.expected['file']).read_bytes(), b'different user input')
        self.assertEqual(build.packed_texture(self.inputs, self.expected)[0], self.packed)

    def test_all_proven_pixel_formats_rebuild_storage_and_reject_changed_pixels(self):
        cases = [('ci4', 32, 8, 160), ('ci8', 32, 8, 768),
                 ('rgba16', 16, 8, 256), ('rgba32', 16, 8, 512),
                 ('i4', 16, 8, 64), ('i8', 16, 8, 128),
                 ('ia8', 16, 8, 128), ('ia16', 16, 8, 256), ('ia4', 16, 8, 64)]
        for fmt, width, height, size in cases:
            for row in ('linear', 'tmem-odd-row-32bit-swap'):
                with self.subTest(format=fmt, row=row):
                    payload = bytes(i % 256 for i in range(size))
                    packed = rzip_pack.encode_rzip_chunk(payload)
                    texture = texture_assets.TextureAsset(53, 0, len(packed), payload)
                    expected = build.describe_texture(packed, texture, encoder=build.ENCODERS['zlib'], contract={
                        'family': 'synthetic-proven', 'format': fmt, 'width': width,
                        'height': height, 'row_layout': row})
                    directory = self.root / (fmt + '-' + row)
                    build.initialize_inputs(directory, expected, payload)
                    self.assertEqual(build.packed_texture(directory, expected)[0], packed)
                    offsets = (0, width * height) if fmt == 'ci8' else (0,)
                    for offset in offsets:
                        changed = bytearray(payload)
                        changed[offset] ^= 1
                        (directory / expected['file']).write_bytes(
                            build.source_png(bytes(changed), expected))
                        with self.assertRaisesRegex(ValueError, 'original payload'):
                            build.packed_texture(directory, expected)

    def test_extended_contract_is_required_and_legacy_inputs_remain_unchanged(self):
        payload = bytes(range(256))
        packed = rzip_pack.encode_rzip_chunk(payload)
        start = len(self.rom)
        texture = texture_assets.TextureAsset(53, start, start + len(packed), payload)
        self.rom += packed + bytes(4)
        self.layout['flat_assets_end'] = len(self.rom)
        self.document['segments'][0]['subsegments'] = [
            [offset, 'bin', name] for offset, name in build.partition(self.layout, [self.texture, texture])]
        self.document['segments'][1] = [len(self.rom)]
        self.save_profile()
        self.load.return_value = (None, self.rom, 'z64', self.layout, [self.texture])
        self.expected = build.describe_texture(self.rom, self.texture, encoder=build.ENCODERS['zlib'])
        self.initialize()
        before = {p.name: p.read_bytes() for p in self.inputs.iterdir()}
        contract = {'identity': 'runtime-resource', 'runtime_resource_id': 55,
                    'family': 'rgba16-proven', 'format': 'rgba16', 'width': 16,
                    'height': 8, 'row_layout': 'tmem-odd-row-32bit-swap'}
        with patch.object(build.texture_catalog, 'load_extended', return_value={53: (texture, contract)}):
            proof = build.build_parts(self.root)
        self.assertEqual(proof['texture_count'], 2)
        self.assertEqual(proof['stored_bytes'], len(self.packed) + len(packed))
        self.assertEqual(proof['textures'][1]['source_contract'], contract)
        self.assertTrue((self.root / build.input_directory(53, proof['textures'][1]) /
                         'manifest.json').is_file())
        self.assertFalse((self.root / build.input_directory(53)).exists())
        for name, data in before.items():
            self.assertEqual((self.inputs / name).read_bytes(), data)
        with patch.object(build.texture_catalog, 'load_extended', return_value={}), \
                self.assertRaisesRegex(ValueError, 'proven RZIP boundaries/family'):
            build.reviewed_textures(self.root)

    def test_hud_source_keeps_top_row_and_roundtrips_tmem_storage(self):
        width, height = 16, 8
        linear = bytes(range(128))
        fmt, row = 'i8', texture_assets.ROW_LAYOUT_TMEM
        payload = build.texture_native.convert_row_layout(linear, row, fmt, width, height)
        expected = {'row_layout': row, 'source_contract': {
            'format': fmt, 'width': width, 'height': height, 'source_origin': 'top-left'}}
        png = build.source_png(payload, expected)
        pixels = texture_assets.decode_rgba_png_pixels(png, width, height)
        self.assertEqual(pixels, build.texture_native.payload_to_rgba(linear, fmt))
        self.assertEqual(build.source_png(png, expected, decode=True), payload)
        expected['source_contract']['source_origin'] = 'unknown'
        with self.assertRaisesRegex(ValueError, 'source origin'):
            build.source_png(payload, expected)

    def test_rgba16_top_origin_preserves_rows_and_strict_color_encoding(self):
        width, height = 16, 8
        linear = bytes(range(256))
        codec, row = build.texture_rgba16, texture_assets.ROW_LAYOUT_TMEM
        payload = codec.convert_row_layout(linear, row, width, height)
        expected = {'row_layout': row, 'source_contract': {
            'format': 'rgba16', 'width': width, 'height': height, 'source_origin': 'top-left'}}
        png = build.source_png(payload, expected)
        pixels = texture_assets.decode_rgba_png_pixels(png, width, height)
        bottom = texture_assets.decode_rgba_png_pixels(codec.encode_png(payload, row, width, height), width, height)
        self.assertEqual(pixels, codec.flip_vertical(bottom, width, height, 4))
        self.assertEqual(build.source_png(png, expected, decode=True), payload)
        for channel, value in ((0, 1), (3, 128)):
            edited = bytearray(pixels)
            edited[channel] = value
            with self.subTest(channel=channel), self.assertRaises(ValueError):
                build.source_png(texture_assets.encode_rgba_png(width, height, edited), expected, decode=True)

    def test_rgba16_top_origin_changed_pixels_fail_original_payload_gate(self):
        payload = bytes(range(256))
        packed = rzip_pack.encode_rzip_chunk(payload)
        texture = texture_assets.TextureAsset(42, 0, len(packed), payload)
        contract = {'format': 'rgba16', 'width': 16, 'height': 8,
                    'row_layout': 'linear', 'source_origin': 'top-left'}
        expected = build.describe_texture(packed, texture, contract=contract, encoder=build.ENCODERS['zlib'])
        directory = self.root / 'rgba16-top'
        build.initialize_inputs(directory, expected, payload)
        png_path = directory / expected['file']
        altered = bytearray(payload)
        altered[0] ^= 8
        png_path.write_bytes(build.source_png(altered, expected))
        with self.assertRaisesRegex(ValueError, 'original payload'):
            build.packed_texture(directory, expected)

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
        self.expected = build.describe_texture(self.rom, self.texture, encoder=build.ENCODERS['zlib'])
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
        encode.assert_called_with(self.payload)
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

    def test_gnu_gzip_wrapper_is_verified_and_only_deflate_enters_rzip(self):
        expected = dict(self.expected, encoder={'format': 'gzip-raw-deflate', 'level': 9,
                                               'implementation': 'GNU gzip 1.12'})
        compressor = zlib.compressobj(9, wbits=31)
        gz = compressor.compress(self.payload) + compressor.flush()
        with patch.object(build.rzip_gzip, 'require_gnu_gzip'), \
                patch.object(build.rzip_gzip.subprocess, 'run', return_value=SimpleNamespace(stdout=gz)) as run:
            packed = build.encode_payload(self.payload, expected)
            self.assertEqual(packed, self.packed)
            self.assertEqual(run.call_args.args[0], ['gzip', '-n', '-9', '-c'])
            self.assertEqual(run.call_args.kwargs['input'], self.payload)
            for changed in (gz[:3] + b'\x08' + gz[4:], gz[:-1] + bytes([gz[-1] ^ 1])):
                run.return_value.stdout = changed
                with self.assertRaisesRegex(ValueError, 'wrapper or checksum'):
                    build.encode_payload(self.payload, expected)

    def test_wrong_gzip_implementation_is_rejected(self):
        build.rzip_gzip.require_gnu_gzip.cache_clear()
        self.addCleanup(build.rzip_gzip.require_gnu_gzip.cache_clear)
        with patch.object(build.rzip_gzip.subprocess, 'check_output', return_value='Apple gzip\n'), \
                self.assertRaisesRegex(ValueError, 'GNU gzip 1.12'):
            build.rzip_gzip.require_gnu_gzip()

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
