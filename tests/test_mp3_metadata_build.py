"""Metadata text credit excludes terminated-field residue and all stream tails."""
import copy
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch
from scripts import mp3_metadata_codec as codec, mp3_metadata_build as metadata, mp3_spectral_build as build
from test_mp3_spectral_build import fixture


def tag():
    return (b'TAG' + b'title\0' + b'UNEXPLAINED'.ljust(24, b'!')
            + b'artist'.ljust(30, b' ') + b'album'.ljust(30, b' ')
            + b'2000' + b'comment'.ljust(30, b' ') + bytes([101]))


class MetadataCodecTests(unittest.TestCase):
    def test_field_prefix_boundaries_and_exact_mutations(self):
        original = tag(); record = codec.decode(original)
        spans = codec.encode(record)
        self.assertEqual(spans, [(0, original[:9]), (33, original[33:])])
        for name, at, width in codec.FIELDS:
            changed = copy.deepcopy(record)
            changed['fields'][name]['text'] = 'X' + changed['fields'][name]['text'][1:]
            fresh = bytearray(original)
            for start, data in codec.encode(changed): fresh[start:start + len(data)] = data
            expected = bytearray(original); expected[at] = ord('X')
            self.assertEqual(fresh, expected)
        changed = copy.deepcopy(record); changed['genre'] = 2
        self.assertEqual(codec.encode(changed)[-1][1][-1], 2)

    def test_opaque_overrides_invalid_text_and_extents_rejected(self):
        mutations = [lambda r: r.update(raw='00'), lambda r: r.update(genre=True),
            lambda r: r.update(genre=256), lambda r: r['fields']['title'].update(text='a\0b'),
            lambda r: r['fields']['title'].update(text='é'),
            lambda r: r['fields']['title'].update(text='x'*30),
            lambda r: r['fields']['title'].update(terminated=False),
            lambda r: r['fields']['album'].update(text='short')]
        for mutate in mutations:
            record = codec.decode(tag()); mutate(record)
            with self.assertRaises(ValueError): codec.encode(record)
        for raw in (tag()[:-1], b'BAD'+tag()[3:]):
            with self.assertRaises(ValueError): codec.decode(raw)


class MetadataBuildTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(); self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.records, original = fixture()
        self.offset = metadata.mp3_assets.parse_mp3_cue_stream(original).trailing_offset
        self.original = original[:self.offset] + tag() + b'unknown tail'
        ranges, count, selected = build.codec.reviewed_ranges(self.original)
        self.expected = {'entry': 7, 'rom_start': 6, 'rom_end': 6+len(self.original),
            'frame_count': count, 'selected_frames': selected,
            'original_sha256': build.sha256(self.original), 'rom_ranges': [[6+a,6+z] for a,z in ranges]}
        self.directory = self.root / build.input_directory(7)
        build.texture_build.publish_inputs(self.directory, build.input_files(self.expected, self.records))
        raw = self.directory / build.raw_relative_name(7); raw.parent.mkdir(parents=True)
        raw.write_bytes(self.original)
        metadata.initialize(self.root, self.original, self.expected)
        build.cues.initialize(self.root, self.original, self.expected)
        self.meta = self.root / metadata.input_directory(7)
        self.contract, self.record = metadata.reviewed_tag(self.original, self.expected)

    def test_composition_and_report_exclude_unknown_bits_fields_cues_and_tail(self):
        packed, spans, hashes = build.packed_stream(self.directory, self.expected,
            include_partial=True, include_metadata=True)
        self.assertEqual(packed, self.original)
        self.assertEqual(sum(len(data) for _, data in spans), 233+104)
        self.assertEqual(len(hashes), 5)
        legacy = build.packed_stream(self.directory, self.expected, include_partial=True)
        self.assertEqual(sum(len(data) for _, data in legacy[1]), 233)
        from test_objdiff_data_targets import object_file, targets
        linked = self.root / 'build/us/assets/audio/mp3/streams/0007.o'
        linked.parent.mkdir(parents=True); linked.write_bytes(object_file([('.data',1,3,packed)]))
        with patch.object(targets, 'ROOT', self.root):
            unit, _ = targets.prepare_mp3_spectral_stream(self.original, self.expected, output=self.root/'report')
            self.assertEqual(unit['report_data_bytes'], 344)
            self.assertEqual(len(unit['source_inputs']), 7)
            for at in (self.offset+10, len(packed)-1):
                changed = bytearray(packed); changed[at] ^= 1
                linked.write_bytes(object_file([('.data',1,3,changed)]))
                with self.assertRaisesRegex(ValueError, 'linked candidate differs'):
                    targets.prepare_mp3_spectral_stream(self.original, self.expected, output=self.root/'report')

    def test_missing_and_changed_inputs_preserved_and_explicit_recovery(self):
        files = metadata.input_files(self.contract, self.record)
        for name, value in (('tag.json',None), ('tag.json',b'bad'), ('manifest.json',b'{}')):
            for filename, data in files.items(): (self.meta/filename).write_bytes(data)
            path = self.meta/name
            if value is None: path.unlink()
            else: path.write_bytes(value)
            before = {p.name:p.read_bytes() for p in self.meta.iterdir()}
            with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                build.prepare_candidate((self.root,self.expected,self.original))
            self.assertEqual({p.name:p.read_bytes() for p in self.meta.iterdir()}, before)
        with patch.object(build,'reviewed_streams',return_value=(self.original,[(self.expected,self.original)])):
            result = metadata.recover_inputs(7,self.root)
        self.assertEqual((Path(result['backup_directory'])/'manifest.json').read_bytes(),b'{}')
        self.assertEqual(metadata.packed_tag(self.meta,self.contract)[0][0][1],tag()[:9])

    def test_all_field_edits_fail_and_source_race_is_detected(self):
        for name, _, _ in codec.FIELDS:
            changed=copy.deepcopy(self.record)
            changed['fields'][name]['text']='X'+changed['fields'][name]['text'][1:]
            (self.meta/'tag.json').write_text(json.dumps(changed))
            with self.assertRaisesRegex(ValueError,'no longer reproduces'):
                build.packed_stream(self.directory,self.expected,include_partial=True,include_metadata=True)
        (self.meta/'tag.json').write_text(json.dumps(self.record))
        encode=codec.encode
        def racing(record):
            result=encode(record)
            with (self.meta/'tag.json').open('a') as stream:stream.write(' ')
            return result
        with patch.object(codec,'encode',side_effect=racing):
            with self.assertRaisesRegex(ValueError,'changed during packing'):
                metadata.packed_tag(self.meta,self.contract)
