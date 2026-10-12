"""Native sprite TMEM layout, editable PNG provenance and bounded data credit."""
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch
from scripts import sprite_codec as codec, sprite_build as build


def sampled_planes(payload, width, height):
    # Independent forward upload into 4 KiB of TMEM, followed by tile reads.
    tmem = bytearray(4096)
    accumulator = 0
    dxt = (2048 + width // 4 - 1) // (width // 4)
    for address in range(0, len(payload), 8):
        word = payload[address:address + 8]
        if accumulator & 2048:
            word = word[4:] + word[:4]
        tmem[address:address + 8] = word
        accumulator += dxt
    result = {}
    for fmt, offset, stride in [('rgba16', 0, width * 2), ('i4', width * height * 2, width // 2)]:
        data = bytearray()
        for y in range(height):
            row = tmem[offset + y * stride:offset + (y + 1) * stride]
            if y % 2:
                row = b''.join(row[x + 4:x + 8] + row[x:x + 4] for x in range(0, stride, 8))
            data.extend(row)
        result[fmt] = bytes(data)
    return result


class SpriteCodecTests(unittest.TestCase):
    def test_every_plane_matches_independent_forward_tmem_simulation(self):
        for width, height in [(32, 44), (32, 32), (16, 64), (64, 22), (48, 32)]:
            data = bytes((i * 71 + i // 257) % 256 for i in range(width * height * 5 // 2))
            images = codec.decode_frame(data, width, height)
            expected = sampled_planes(data, width, height)
            for fmt in codec.FORMATS:
                linear = build.texture_build.source_png(images[fmt], codec.png_contract(width, height, fmt), decode=True)
                self.assertEqual(linear, expected[fmt])
            self.assertEqual(codec.encode_frame(images, width, height), data)

    def test_pixels_in_each_plane_change_only_their_own_storage(self):
        data = bytes(32 * 32 * 5 // 2)
        images = codec.decode_frame(data, 32, 32)
        for fmt, value in [('rgba16', b'\xff\xff'), ('i4', b'\xff')]:
            size = 2048 if fmt == 'rgba16' else 512
            plane = value + bytes(size - len(value))
            changed = dict(images)
            changed[fmt] = build.texture_build.source_png(plane, codec.png_contract(32, 32, fmt))
            rebuilt = codec.encode_frame(changed, 32, 32)
            self.assertNotEqual(rebuilt, data)
            other = slice(2048, None) if fmt == 'rgba16' else slice(0, 2048)
            self.assertEqual(rebuilt[other], data[other])

    def test_bad_dimensions_extent_and_pngs_fail(self):
        for width, height in [(True, 32), (24, 32), (32, 0), (64, 64), (32, 65)]:
            with self.assertRaises(ValueError): codec.dimensions(width, height)
        with self.assertRaises(ValueError): codec.decode_frame(b'', 32, 32)
        with self.assertRaises(ValueError): codec.encode_frame({'rgba16': b''}, 32, 32)
        with self.assertRaises(ValueError): codec.encode_frame({'rgba16': b'bad', 'i4': b'bad'}, 32, 32)


class SpriteBuildTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(); self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.data = bytes((i * 31) % 256 for i in range(2560))
        self.payload = b'indexgap' + self.data + b'raw-uncredited'
        self.rom = b'prefix' + self.payload + b'tail'
        self.expected = {'rom_start': 6, 'rom_end': 6 + len(self.payload), 'original_sha256': build.sha256(self.payload),
            'rom_ranges': [[14, 2574]], 'entries': [{'entry': 40, 'frames': 1, 'width': 32, 'height': 32,
            'frame_bytes': 2560, 'decoded_sha256': build.sha256(self.data), 'encoder': 'raw', 'rom_start': 14, 'rom_end': 2574}]}
        self.decoded = {40: self.data}
        self.directory = self.root / build.INPUT_DIRECTORY
        build.texture_build.publish_inputs(self.directory, build.input_files(self.rom, self.expected, self.decoded))

    def test_build_preserves_sources_and_mtime_and_repairs_missing_part(self):
        with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.decoded)):
            proof = build.build_parts(self.root)
            part = self.root / 'build/us/sprites/parts/asset_bank_00.bin'
            before = part.stat().st_mtime_ns
            self.assertEqual(build.build_parts(self.root), proof)
            self.assertEqual(part.stat().st_mtime_ns, before)
            self.assertEqual(proof['rebuilt_bytes'], len(self.data))
            part.unlink(); build.build_parts(self.root)
            self.assertEqual(part.read_bytes(), self.payload)

    def test_bad_or_missing_png_manifest_and_backing_are_preserved(self):
        original = build.input_files(self.rom, self.expected, self.decoded)
        for name, data in [('40-00.rgba16.png', b'bad'), ('40-00.i4.png', None), ('manifest.json', b'{}'), ('backing.bin', b'bad')]:
            for filename, content in original.items(): (self.directory / filename).write_bytes(content)
            path = self.directory / name
            if data is None: path.unlink()
            else: path.write_bytes(data)
            before = {p.name: p.read_bytes() for p in self.directory.iterdir()}
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                build.packed_bank(self.directory, self.expected)
            self.assertEqual({p.name: p.read_bytes() for p in self.directory.iterdir()}, before)
        with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.decoded)):
            result = build.recover_inputs(self.root)
        self.assertEqual((Path(result['backup_directory']) / 'backing.bin').read_bytes(), b'bad')
        self.assertEqual(build.packed_bank(self.directory, self.expected)[0], self.payload)

    def test_source_race_fails_after_encoding(self):
        encode = codec.encode_frame
        def changing(*args):
            value = encode(*args)
            with (self.directory / 'manifest.json').open('a') as file: file.write(' ')
            return value
        with patch.object(codec, 'encode_frame', side_effect=changing):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_bank(self.directory, self.expected)

    def test_report_credits_only_png_ranges_and_rejects_stale_actual_object(self):
        from test_objdiff_data_targets import object_file, targets
        linked = self.root / 'build/us/assets/asset_bank_00.o'; linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        with patch.object(targets, 'ROOT', self.root):
            unit, item = targets.prepare_sprite_bank(self.rom, self.expected, output=self.root / 'report')
            self.assertEqual(unit['report_data_bytes'], 2560)
            self.assertEqual(unit['rom_ranges'], [[14, 2574]])
            self.assertEqual(item['name'], 'assets/sprites/bank00')
            candidate = targets.sections((self.root / 'report/sprite-bank/base.o').read_bytes(), 1)['.data'][1]
            self.assertEqual(candidate, self.data)
            linked.write_bytes(object_file([('.data', 1, 3, bytes(len(self.payload)))]))
            with self.assertRaisesRegex(ValueError, 'candidate differs'):
                targets.prepare_sprite_bank(self.rom, self.expected, output=self.root / 'report')
