"""Native delta semantics, source preservation and physical camera-track ranges."""
import copy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import asset_directory_build as build
from scripts import camera_tracks_codec as codec, camera_tracks_inputs as inputs


class CameraTrackTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.tracks = [{'format': codec.FORMAT, 'frames': [
            {codec.FIELDS[0]: [i + 0.25, -0.0, -j * 0.5],
             codec.FIELDS[1]: [j + 0.125, -i, 0.0]}
            for j in range(i + 1)]} for i in range(4)]
        backing = bytearray(32)
        self.spans = []
        for i, source in enumerate(self.tracks):
            packed = codec.compress(codec.encode(source))
            offset = len(backing)
            struct.pack_into('>2I', backing, i * 8, offset,
                             len(packed) | (9 if i == 3 else 1) << 28)
            self.spans.append((offset, packed))
            backing.extend(packed)
            backing.extend(b'gap')
        self.payload = bytes(backing)
        self.rom = b'prefix' + self.payload + b'after'
        self.expected = {'key': 'bank1B', 'part': build.PARTS['bank1B'],
                         'rom_start': 6, 'rom_end': 6 + len(backing), 'rom_ranges': [[6, 38]],
                         'directory_size': 32, 'directory_sha256': build.sha256(self.payload[:32]),
                         'original_sha256': build.sha256(self.payload)}
        self.table = build.codec.decode(self.payload[:32])
        self.directory = self.root / build.input_directory('bank1B')
        self.old = build.input_files(self.rom, self.expected, self.table)
        build.texture_build.publish_inputs(self.directory, self.old)

    def run_build(self):
        with patch.object(build, 'reviewed_directories', return_value=(self.rom, [(self.expected, self.table)])):
            return build.build_parts(self.root)

    def test_float_roundtrip_signed_zero_and_invalid_records(self):
        for source in self.tracks:
            raw = codec.encode(source)
            self.assertEqual(codec.encode(json.loads(json.dumps(codec.decode(raw)))), raw)
            self.assertEqual(codec.unpack(codec.compress(raw)), raw)
        for value in (True, float('nan'), float('inf'), 1e100, '1', 10 ** 400):
            changed = copy.deepcopy(self.tracks[0])
            changed['frames'][0][codec.FIELDS[0]][0] = value
            with self.subTest(value=str(value)), self.assertRaises(ValueError):
                codec.encode(changed)
        for frames in ([], self.tracks[0]['frames'] * 257, [{}], [{codec.FIELDS[0]: [0, 0]}]):
            with self.assertRaises(ValueError):
                codec.encode({'format': codec.FORMAT, 'frames': frames})
        with self.assertRaises(ValueError):
            codec.encode(dict(self.tracks[0], raw='opaque'))
        for raw in (b'', bytes(23), bytes(257 * 24), struct.pack('>6f', float('nan'), 0, 0, 0, 0, 0)):
            with self.assertRaises(ValueError):
                codec.decode(raw)
        blob = codec.compress(codec.encode(self.tracks[0]))
        for bad in (blob[:-1], blob + b'junk', bytes(5), bytes.fromhex('ffffffff') + blob[4:]):
            with self.assertRaises(ValueError):
                codec.unpack(bad)

    def test_sources_preserved_and_complete_object_rebuilt(self):
        self.run_build()
        for name, data in self.old.items():
            self.assertEqual((self.directory / name).read_bytes(), data)
        packed, spans, hashes = build.packed_directory(self.directory, self.expected, include_camera_tracks=True)
        self.assertEqual(packed, self.payload)
        self.assertEqual(spans, [(0, self.payload[:32])])
        self.assertIn('camera-tracks/tracks.json', hashes)
        output = self.root / 'build/us/asset-directories/parts/asset_bank_1b.bin'
        stamp = output.stat().st_mtime_ns
        self.run_build()
        self.assertEqual(output.stat().st_mtime_ns, stamp)
        output.unlink()
        self.run_build()
        self.assertEqual(output.read_bytes(), self.payload)

    def test_all_field_mutations_change_source_output_and_fail_exact_build(self):
        self.run_build()
        path = self.directory / inputs.DIRECTORY / 'tracks.json'
        original = json.loads(path.read_text())
        for track_index, track in enumerate(original['tracks']):
            for frame_index, _ in enumerate(track['frames']):
                for field in codec.FIELDS:
                    for axis in range(3):
                        source = copy.deepcopy(original)
                        edited = source['tracks'][track_index]
                        edited['frames'][frame_index][field][axis] += 1.0
                        self.assertNotEqual(codec.encode(edited), codec.encode(track))
                        path.write_text(json.dumps(source))
                        before = path.read_bytes()
                        with self.assertRaisesRegex(ValueError, 'no longer reproduce'):
                            self.run_build()
                        self.assertEqual(path.read_bytes(), before)

    def test_invalid_or_missing_source_preserved_and_recovery_backs_up(self):
        self.run_build()
        directory = self.directory / inputs.DIRECTORY
        original = {p.name: p.read_bytes() for p in directory.iterdir()}
        for name, value in (('tracks.json', None), ('tracks.json', b'bad'),
                            ('tracks.json', b'{"format":"wrong","tracks":[]}'),
                            ('manifest.json', b'{}')):
            for filename, data in original.items():
                (directory / filename).write_bytes(data)
            file = directory / name
            if value is None:
                file.unlink()
            else:
                file.write_bytes(value)
            before = {p.name: p.read_bytes() for p in directory.iterdir()}
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                self.run_build()
            self.assertEqual({p.name: p.read_bytes() for p in directory.iterdir()}, before)
        with patch.object(build, 'reviewed_directories', return_value=(self.rom, [(self.expected, self.table)])):
            recovered = build.recover_inputs('bank1B', self.root)
        self.assertEqual((Path(recovered['backup_directory']) / inputs.DIRECTORY / 'manifest.json').read_bytes(), b'{}')
        self.run_build()
        self.assertEqual((directory / 'tracks.json').read_bytes(), original['tracks.json'])

    def test_source_race_rejected(self):
        self.run_build()
        encode = inputs.encoded
        def changed(*args):
            result = encode(*args)
            with (self.directory / inputs.DIRECTORY / 'tracks.json').open('a') as stream:
                stream.write(' ')
            return result
        with patch.object(build.camera_tracks_inputs, 'encoded', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                self.run_build()

    def test_report_excludes_directory_and_nonzero_gaps_checks_whole_linker_object(self):
        from test_objdiff_data_targets import object_file, targets
        self.run_build()
        linked = self.root / 'build/us/assets/asset_bank_1b.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        output = self.root / 'report'
        with patch.object(targets, 'ROOT', self.root):
            unit, _ = targets.prepare_camera_tracks_object(self.rom, self.expected, output=output)
            header, _ = targets.prepare_asset_directory(self.rom, self.expected, output=output)
            self.assertEqual(unit['report_data_bytes'], sum(len(data) for _, data in self.spans))
            self.assertEqual(unit['rom_ranges'], [[6 + off, 6 + off + len(data)] for off, data in self.spans])
            self.assertEqual(header['rom_ranges'], [[6, 38]])
            self.assertEqual(targets.sections((output / unit['base_path']).read_bytes(), 1)['.data'][1],
                             b''.join(data for _, data in self.spans))
            for at in (0, 32, len(self.payload) - 1):
                changed = bytearray(self.payload)
                changed[at] ^= 1
                linked.write_bytes(object_file([('.data', 1, 3, bytes(changed))]))
                with self.assertRaisesRegex(ValueError, 'candidate differs'):
                    targets.prepare_camera_tracks_object(self.rom, self.expected, output=output)
