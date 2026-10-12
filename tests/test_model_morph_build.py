"""Independent nested-table decoding and source preservation for morph storage."""
import copy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import model_morph_build as build


def fixture():
    models = []
    for character, starts, counts, shapes in build.MODELS:
        models.append({'character_entry': character, 'vertex_starts': list(starts),
                       'part_vertex_counts': list(counts),
                       'shapes': [[[[i, -i, shape] for i in range(count)] for count in counts]
                                  for shape in range(shapes)]})
    return {'format': build.FORMAT, 'models': models}


class MorphCodecTests(unittest.TestCase):
    def test_all_nested_payloads_decode_to_typed_endpoints(self):
        records = fixture()
        with patch.object(build.rzip_pack, 'encode_rzip_chunk', wraps=build.rzip_pack.encode_rzip_chunk) as encode:
            payload = build.encode_records(records)
        self.assertEqual(encode.call_count, 69)
        entries = build.model_morphs.children(payload, 2, compressed=False)
        for source, entry in zip(records['models'], entries):
            parts = build.model_morphs.children(entry, 3, compressed=False)
            for index, part in enumerate(parts):
                leaves = build.model_morphs.children(part, len(source['shapes']), compressed=True)
                for leaf, shape in zip(leaves, source['shapes']):
                    expected = b''.join(struct.pack('>3h', *xyz) for xyz in shape[index])
                    self.assertEqual(leaf, expected + bytes(-len(expected) % 16))

    def test_positions_and_table_contract_are_strict(self):
        for change in ('schema', 'selector', 'start', 'count', 'shapes', 'parts', 'vertices', 'width', 'bounds', 'type'):
            record = fixture()
            model = record['models'][0]
            if change == 'schema': record['opaque'] = []
            elif change == 'selector': model['character_entry'] = True
            elif change == 'start': model['vertex_starts'][0] += 1
            elif change == 'count': model['part_vertex_counts'][0] += 1
            elif change == 'shapes': model['shapes'].pop()
            elif change == 'parts': model['shapes'][0].pop()
            elif change == 'vertices': model['shapes'][0][0].pop()
            elif change == 'width': model['shapes'][0][0][0].pop()
            elif change == 'bounds': model['shapes'][0][0][0][0] = 32768
            elif change == 'type': model['shapes'][0][0][0][0] = 1.0
            with self.subTest(change=change), self.assertRaises(ValueError):
                build.encode_records(record)

    def test_coordinate_change_reaches_fresh_compressed_leaf(self):
        records = fixture()
        original = build.encode_records(records)
        records['models'][1]['shapes'][-1][-1][-1][2] = -1234
        changed = build.encode_records(records)
        self.assertNotEqual(original, changed)
        entry = build.model_morphs.children(changed, 2, compressed=False)[1]
        part = build.model_morphs.children(entry, 3, compressed=False)[2]
        leaf = build.model_morphs.children(part, 7, compressed=True)[-1]
        self.assertEqual(struct.unpack_from('>h', leaf, (24 - 1) * 6 + 4)[0], -1234)


class MorphBuildTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory()
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.records = fixture()
        self.payload = build.encode_records(self.records)
        self.rom = b'prefix' + self.payload + b'tail'
        self.expected = {'rom_start': 6, 'rom_end': 6 + len(self.payload),
                         'original_sha256': build.sha256(self.payload)}
        self.inputs = self.root / build.INPUT_DIRECTORY
        build.texture_build.publish_inputs(self.inputs, build.input_files(self.expected, self.records))

    def test_build_preserves_mtimes_and_rechecks_fresh_inputs(self):
        with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.records)):
            proof = build.build_parts(self.root)
            part = self.root / 'build/us/morphs/parts/asset_bank_13.bin'
            before = [p.stat().st_mtime_ns for p in (part, self.inputs / 'morphs.json')]
            self.assertEqual(build.build_parts(self.root), proof)
            self.assertEqual([p.stat().st_mtime_ns for p in (part, self.inputs / 'morphs.json')], before)
            self.assertEqual(part.read_bytes(), self.payload)
        encode = build.encode_records
        def changed(records):
            packed = encode(records)
            with (self.inputs / 'morphs.json').open('a') as file: file.write(' ')
            return packed
        with patch.object(build, 'encode_records', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_bank(self.inputs, self.expected)

    def test_missing_changed_and_malformed_sources_preserved_until_recovery(self):
        changed = copy.deepcopy(self.records)
        changed['models'][0]['shapes'][0][0][0][0] += 1
        for name, data in [('morphs.json', json.dumps(changed).encode()), ('morphs.json', b'{'),
                           ('manifest.json', b'{}'), ('morphs.json', None)]:
            for n, content in build.input_files(self.expected, self.records).items():
                (self.inputs / n).write_bytes(content)
            if data is None: (self.inputs / name).unlink()
            else: (self.inputs / name).write_bytes(data)
            before = {p.name: p.read_bytes() for p in self.inputs.iterdir()}
            with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.records)):
                with self.subTest(name=name, data=data), self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                    build.build_parts(self.root)
                self.assertEqual({p.name: p.read_bytes() for p in self.inputs.iterdir()}, before)
                result = build.recover_inputs(self.root)
            backup = Path(result['backup_directory'])
            self.assertEqual({p.name: p.read_bytes() for p in backup.iterdir()}, before)
            self.assertEqual(build.packed_bank(self.inputs, self.expected)[0], self.payload)

    def test_original_mismatch_prevents_publication(self):
        with patch.object(build, 'reviewed_bank', return_value=(b'bad reference', self.expected, self.records)):
            with self.assertRaisesRegex(ValueError, 'independent'):
                build.build_parts(self.root)
        self.assertFalse((self.root / 'build/us/morphs/parts').exists())

    def test_native_report_requires_actual_link_object_from_current_endpoints(self):
        from test_objdiff_data_targets import object_file, targets
        linked = self.root / 'build/us/assets/asset_bank_13.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        with patch.object(targets, 'ROOT', self.root):
            unit, item = targets.prepare_morph_bank(self.rom, self.expected, output=self.root / 'report')
            self.assertTrue(unit['complete'])
            self.assertEqual(unit['report_data_bytes'], len(self.payload))
            self.assertEqual(item['name'], 'assets/asset_bank_13')
            self.assertEqual(len(unit['source_inputs']), 2)
            linked.write_bytes(object_file([('.data', 1, 3, bytes(len(self.payload)))]))
            with self.assertRaisesRegex(ValueError, 'candidate differs'):
                targets.prepare_morph_bank(self.rom, self.expected, output=self.root / 'report')
