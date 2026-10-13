"""Native semantic round trips and strict exclusion of cue/tail storage."""
import copy
import json
import struct
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from scripts import mp3_spectral_codec as codec, mp3_spectral_build as build


def fixture():
    header = dict(sync=0x7ff, version=2, layer=1, protection=1, bitrate=3, sample_rate=0,
                  padding=0, private=0, mode=3, mode_extension=0, copyright=0, original=1, emphasis=0)
    side = dict(main_data_begin=0, private_bit=0, part2_3_length=520, big_values=0,
                global_gain=200, scalefac_compress=0, window_switching=0, block_type=0,
                mixed_block_flag=0, table_select=[0, 0, 0], region0_count=0, region1_count=0,
                scalefac_scale=0, count1table_select=1)
    frame = {'header': header, 'side_info': side, 'scalefactors': [0] * 21, 'big_pairs': [],
             'count1_quads': [[-1, 0, 0, 0] if i < 8 else [0, 0, 0, 0] for i in range(128)]}
    frames = [copy.deepcopy(frame) for _ in range(3)]
    frames[0]['header']['copyright'] = 1
    frames[-1]['count1_quads'].pop()
    frames[-1]['side_info']['part2_3_length'] -= 4
    records = {'format': codec.FORMAT, 'frames': frames}
    data = bytearray()
    for item in frames:
        bits = codec.encode_granule(item)
        bits += '1010'[:(-len(bits)) % 8]  # Explicitly unproven terminal bits.
        data.extend(codec.encode_header(item['header']) + codec.encode_side(item['side_info'])
                    + int(bits, 2).to_bytes(len(bits) // 8, 'big'))
        if item['header']['copyright']:
            data.extend(b'L:opaque\0')
    data.extend(b'unexplained tail')
    return records, bytes(data)


class SpectralCodecTests(unittest.TestCase):
    def test_full_semantic_round_trip_excludes_cues_and_terminal_frame(self):
        records, original = fixture()
        self.assertEqual(codec.decode_stream(original), records)
        spans = codec.encode_stream(records)
        self.assertEqual([[a, a + len(b)] for a, b in spans], [[0, 78], [87, 165]])
        self.assertEqual(codec.reviewed_ranges(original), ([[0, 78], [87, 165]], 3, 2))
        self.assertEqual([payload for start, payload in spans], [original[:78], original[87:165]])
        self.assertEqual(sum(len(payload) for _, payload in spans), 156)
        self.assertGreater(len(original), 156 + 9)

    def test_partial_frames_stop_before_an_incomplete_reservoir_byte(self):
        records, original = fixture()
        spans = codec.encode_stream(records, include_partial=True)
        self.assertEqual([[a, a + len(b)] for a, b in spans], [[0, 78], [87, 242]])
        self.assertEqual(codec.reviewed_ranges(original, include_partial=True),
                         ([[0, 78], [87, 242]], 3, 3))
        self.assertEqual(spans[1][1], original[87:242])
        # The final byte has four unknown bits. It must be wholly excluded,
        # together with the cue and the arbitrary stream tail.
        self.assertEqual(original[242] & 15, 10)
        self.assertEqual(sum(len(b) for _, b in spans), 233)
        records['frames'][-1]['count1_quads'][0][0] = 1
        self.assertNotEqual(codec.encode_stream(records, include_partial=True)[1][1], original[87:242])

    def test_headers_remain_typed_after_last_reservoir_bit_and_cues_stay_excluded(self):
        records, _ = fixture()
        for frame in records['frames'][1:]:
            frame['side_info']['part2_3_length'] = 0
            frame['count1_quads'] = []
        records['frames'][-1]['side_info']['main_data_begin'] = 65
        records['frames'][1]['header']['copyright'] = 1
        spans = codec.encode_stream(records, include_partial=True)
        self.assertEqual([[a, a + len(b)] for a, b in spans], [[0, 78], [87, 100], [174, 187]])
        records['frames'][-1]['side_info']['global_gain'] += 1
        changed = codec.encode_stream(records, include_partial=True)
        self.assertEqual(spans[:2], changed[:2])
        self.assertNotEqual(spans[-1], changed[-1])

    def test_signed_coefficient_and_header_edits_reach_output(self):
        records, original = fixture()
        records['frames'][0]['count1_quads'][0][0] = 1
        changed = codec.encode_stream(records)
        self.assertNotEqual(changed[0][1], original[:78])
        records, _ = fixture()
        records['frames'][0]['side_info']['global_gain'] += 1
        self.assertNotEqual(codec.encode_stream(records)[0][1], original[:78])

    def test_extended_pair_linbits_signs_and_bounds(self):
        records, _ = fixture()
        frame = records['frames'][0]
        frame['big_pairs'], frame['count1_quads'] = [[-16, 16]], []
        side = frame['side_info']
        side['big_values'], side['table_select'] = 1, [16, 0, 0]
        side['part2_3_length'] = len(codec.huffman_tables()[1][16][15, 15]) + 4
        bits = codec.encode_granule(frame)
        raw = int(bits + '0' * (-len(bits) % 8), 2).to_bytes((len(bits) + 7) // 8, 'big')
        self.assertEqual(codec.decode_granule(raw, 0, side)['big_pairs'], [[-16, 16]])
        frame['big_pairs'][0][0] = -17
        with self.assertRaisesRegex(ValueError, 'field width'):
            codec.encode_granule(frame)

    def test_rejects_opaque_fields_wrong_counts_invalid_domains_and_overlap(self):
        for change in ('opaque', 'channels', 'rate', 'crc', 'big', 'tables', 'scales', 'quad',
                       'float', 'overlap', 'granule_length', 'pair', 'negative_offset'):
            records, _ = fixture()
            frame = records['frames'][0]
            side = frame['side_info']
            if change == 'opaque': frame['compressed_hex'] = '00'
            elif change == 'channels': frame['header']['mode'] = 0
            elif change == 'rate': frame['header']['sample_rate'] = 1
            elif change == 'crc': frame['header']['protection'] = 0
            elif change == 'big': side['big_values'] = 289
            elif change == 'tables': side['table_select'] = [0, 0]
            elif change == 'scales': frame['scalefactors'].pop()
            elif change == 'quad': frame['count1_quads'][0][0] = 2
            elif change == 'float': frame['count1_quads'][0][0] = 1.0
            elif change == 'overlap': records['frames'][1]['side_info']['main_data_begin'] = 1
            elif change == 'granule_length': side['part2_3_length'] -= 1
            elif change == 'pair': frame['big_pairs'] = [[0, 0]]
            elif change == 'negative_offset': side['main_data_begin'] = 1
            with self.subTest(change=change), self.assertRaises(ValueError):
                codec.encode_stream(records)


class SpectralBuildTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.records, self.original = fixture()
        self.rom = b'prefix' + self.original + b'tail'
        ranges, count, selected = codec.reviewed_ranges(self.original)
        self.expected = {'entry': 0, 'rom_start': 6, 'rom_end': 6 + len(self.original),
                         'frame_count': count, 'selected_frames': selected,
                         'original_sha256': build.sha256(self.original),
                         'rom_ranges': [[6 + a, 6 + b] for a, b in ranges]}
        self.directory = self.root / build.input_directory(0)
        build.texture_build.publish_inputs(self.directory, build.input_files(self.expected, self.records))
        self.raw = self.directory / build.raw_relative_name(0)
        self.raw.parent.mkdir(parents=True)
        self.raw.write_bytes(self.original)

    def test_fresh_coefficient_encoding_preserves_uncredited_bytes(self):
        with patch.object(codec, 'encode_stream', wraps=codec.encode_stream) as encode:
            packed, spans, hashes = build.packed_stream(self.directory, self.expected)
        encode.assert_called_once_with(self.records)
        self.assertEqual(packed, self.original)
        self.assertEqual(packed[78:87], b'L:opaque\0')
        self.assertTrue(packed.endswith(b'unexplained tail'))
        self.assertEqual(sum(len(payload) for _, payload in spans), 156)
        self.assertEqual(set(hashes), {'manifest.json', 'stream.json', build.raw_relative_name(0)})

    def test_partial_builder_uses_last_frame_sources_and_preserves_opaque_byte(self):
        packed, spans, _ = build.packed_stream(self.directory, self.expected, include_partial=True)
        self.assertEqual(packed, self.original)
        self.assertEqual(sum(len(b) for _, b in spans), 233)
        self.assertEqual(packed[242:], self.original[242:])
        changed = copy.deepcopy(self.records)
        changed['frames'][-1]['side_info']['global_gain'] += 1
        (self.directory / 'stream.json').write_text(json.dumps(changed))
        with self.assertRaisesRegex(ValueError, 'no longer reconstruct'):
            build.packed_stream(self.directory, self.expected, include_partial=True)
        self.assertEqual(json.loads((self.directory / 'stream.json').read_text()), changed)
        self.assertEqual(self.raw.read_bytes(), self.original)

    def test_partial_source_race_and_legacy_manifest_disagreement_fail(self):
        expected = dict(self.expected, selected_frames=1)
        # Bypass only the fixture manifest equality to reach the independent
        # original framing contract, which still must reject this stale count.
        with patch.object(build, 'input_hashes', return_value={}):
            with self.assertRaisesRegex(ValueError, 'full-frame contract changed'):
                build.packed_stream(self.directory, expected, include_partial=True)
        encode = codec.encode_stream
        def changed(records, **kwargs):
            spans = encode(records, **kwargs)
            with (self.directory / 'stream.json').open('a') as file: file.write(' ')
            return spans
        with patch.object(codec, 'encode_stream', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_stream(self.directory, self.expected, include_partial=True)

    def test_mutations_missing_sources_and_raw_edits_are_preserved(self):
        changed = copy.deepcopy(self.records)
        changed['frames'][0]['count1_quads'][0][0] = 1
        for name, data in [('stream.json', json.dumps(changed).encode()), ('stream.json', b'{'),
                           ('manifest.json', b'{}'), ('stream.json', None),
                           (build.raw_relative_name(0), self.original[:80] + b'X' + self.original[81:])]:
            for file, content in build.input_files(self.expected, self.records).items():
                (self.directory / file).write_bytes(content)
            self.raw.write_bytes(self.original)
            file = self.directory / name
            if data is None: file.unlink()
            else: file.write_bytes(data)
            before = {p.name: p.read_bytes() for p in self.directory.iterdir()}
            raw_before = self.raw.read_bytes()
            with self.subTest(name=name), self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                build.packed_stream(self.directory, self.expected)
            self.assertEqual({p.name: p.read_bytes() for p in self.directory.iterdir()}, before)
            self.assertEqual(self.raw.read_bytes(), raw_before)

    def test_recovery_backs_up_typed_sources_and_never_changes_raw_backing(self):
        (self.directory / 'stream.json').unlink()
        (self.directory / 'notes.txt').write_text('preserve')
        with patch.object(build, 'reviewed_streams', return_value=(self.rom, [(self.expected, self.original)])):
            proof = build.recover_inputs(0, self.root)
        backup = Path(proof['backup_directory'])
        self.assertEqual((backup / 'notes.txt').read_text(), 'preserve')
        self.assertFalse((backup / 'stream.json').exists())
        self.assertEqual(self.raw.read_bytes(), self.original)
        self.assertEqual(build.packed_stream(self.directory, self.expected)[0], self.original)

    def test_source_change_during_encoding_fails(self):
        encode = codec.encode_stream
        def changed(records):
            spans = encode(records)
            with (self.directory / 'stream.json').open('a') as file: file.write(' ')
            return spans
        with patch.object(codec, 'encode_stream', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_stream(self.directory, self.expected)

    def test_report_proves_real_object_slices_and_never_counts_raw_holes(self):
        from test_objdiff_data_targets import object_file, targets
        from scripts.elf_sections import sections
        linked = self.root / 'build/us/assets/audio/mp3/streams/0000.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.original)]))
        output = self.root / 'report'
        with patch.object(targets, 'ROOT', self.root):
            unit, item = targets.prepare_mp3_spectral_stream(self.original, self.expected, output=output)
            self.assertEqual(unit['rom_ranges'], [[6, 84], [93, 248]])
            self.assertEqual(unit['report_data_bytes'], 233)
            self.assertTrue(unit['complete'])
            self.assertNotIn('rom_start', unit)
            wanted = self.original[:78] + self.original[87:242]
            for key in ('base_path', 'target_path'):
                self.assertEqual(sections((output / unit[key]).read_bytes(), 1)['.data'][1], wanted)
            self.assertEqual(len(unit['source_inputs']), 3)
            self.assertTrue(all('..' not in name for name in unit['source_inputs']))
            self.assertEqual(item['name'], 'assets/audio/mp3/spectral/0000')
            # Even a changed excluded byte must fail agreement with current ROM
            # build inputs; it can never leak into the credited target.
            altered = self.original[:80] + b'X' + self.original[81:]
            linked.write_bytes(object_file([('.data', 1, 3, altered)]))
            with self.assertRaisesRegex(ValueError, 'linked candidate differs'):
                targets.prepare_mp3_spectral_stream(self.original, self.expected, output=output)


class SpectralReviewTests(unittest.TestCase):
    def test_invalid_huffman_selection_and_code_have_useful_errors(self):
        for book in (4, 14, -1, 100, True):
            with self.subTest(book=book), self.assertRaisesRegex(ValueError, 'codebook'):
                codec.Reader(b'\x00').symbol(book)
        with patch.object(codec, 'huffman_tables', return_value=([{0: {'leaf': (1, 1)}}], [])):
            with self.assertRaisesRegex(ValueError, 'invalid MPEG Huffman code'):
                codec.Reader(b'\x80').symbol(0)
        with self.assertRaisesRegex(ValueError, 'reservoir'):
            codec.Reader(b'').symbol(1)

    def test_encoding_cache_reuses_build_and_rejects_stale_or_corrupt_entries(self):
        records, _ = fixture()
        with tempfile.TemporaryDirectory() as temporary:
            cache = Path(temporary)
            with patch.object(build.codec, 'encode_stream', wraps=build.codec.encode_stream) as encoder:
                expected = build.encoded_spans(records, {'entry': 0}, {'source': 'a'}, True, cache)
                self.assertEqual(build.encoded_spans(records, {'entry': 0}, {'source': 'a'}, True, cache), expected)
                self.assertEqual(encoder.call_count, 1)
                receipt = next(cache.glob('*.cache')); receipt.write_bytes(b'corrupt')
                self.assertEqual(build.encoded_spans(records, {'entry': 0}, {'source': 'a'}, True, cache), expected)
                self.assertEqual(encoder.call_count, 2)
                build.encoded_spans(records, {'entry': 0}, {'source': 'b'}, True, cache)
                self.assertEqual(encoder.call_count, 3)
                with patch.object(build, 'cached_sha256', return_value='changed codec'):
                    build.encoded_spans(records, {'entry': 0}, {'source': 'b'}, True, cache)
                self.assertEqual(encoder.call_count, 4)

    def test_cache_replaces_revisions_and_stores_binary_payload(self):
        records, _ = fixture()
        with tempfile.TemporaryDirectory() as temporary:
            cache = Path(temporary)
            for revision in range(3):
                spans = build.encoded_spans(records, {'entry': 0}, {'source': str(revision)}, True, cache)
                self.assertEqual([p.name for p in cache.iterdir()], ['0000-partial.cache'])
            raw = (cache / '0000-partial.cache').read_bytes()
            start = len(build.CACHE_MAGIC) + 4
            length = struct.unpack('>I', raw[len(build.CACHE_MAGIC):start])[0]
            self.assertNotIn('payload', json.loads(raw[start:start + length]))
            self.assertEqual(raw[start + length:], b''.join(data for _, data in spans))
            build.encoded_spans(records, {'entry': 1}, {}, False, cache)
            self.assertEqual(len(list(cache.iterdir())), 2)

    def test_failed_write_or_replace_preserves_previous_entry_and_removes_temp(self):
        records, _ = fixture()
        with tempfile.TemporaryDirectory() as temporary:
            cache = Path(temporary)
            build.encoded_spans(records, {'entry': 0}, {'source': 'old'}, True, cache)
            path = cache / '0000-partial.cache'; before = path.read_bytes()
            original = build.tempfile.NamedTemporaryFile
            def failing_writer(*args, **kwargs):
                handle = original(*args, **kwargs)
                handle.write = lambda data: (_ for _ in ()).throw(OSError('disk full'))
                return handle
            for context in (patch.object(build.tempfile, 'NamedTemporaryFile', side_effect=failing_writer),
                            patch.object(Path, 'replace', side_effect=OSError('replace failed'))):
                with context, self.assertRaises(OSError):
                    build.encoded_spans(records, {'entry': 0}, {'source': 'new'}, True, cache)
                self.assertEqual(path.read_bytes(), before)
                self.assertEqual(list(cache.iterdir()), [path])

    def test_legacy_cache_cleanup_leaves_current_and_in_flight_files_alone(self):
        with tempfile.TemporaryDirectory() as temporary:
            cache = Path(temporary)
            old = ('a' * 64 + '.json', 'tmpabcd1234')
            keep = ('0000-partial.cache', '.spectral-active.tmp', 'notes.json')
            for name in old + keep: (cache / name).write_bytes(b'fixture')
            build.prune_legacy_cache(cache)
            self.assertEqual({p.name for p in cache.iterdir()}, set(keep))
