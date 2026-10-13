"""Native event label relocation, exact bank storage and source provenance."""
import copy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import event_codec as codec, event_build as build


def instruction(opcode, *operands, wide=False):
    return {'opcode': opcode, 'wide': wide, 'operands': list(operands)}


def fixture():
    literal = lambda value: {'mode': 'literal', 'value': value}
    program = {'flags': 0x1800, 'state_bytes': 12, 'entrypoints': [0, 1, 4, 6, 8],
               'strings': ['First\n', 'Second'], 'instructions': [
                   instruction(27, literal(0)),
                   instruction(24, {'mode': 'data-address', 'string': 0}),
                   instruction(24, {'mode': 'data-address', 'string': 1}),
                   instruction(25, {'mode': 'native-index', 'value': 2}),
                   instruction(25, {'mode': 'program-offset', 'target': 6}, wide=True),
                   instruction(15, {'mode': 'program-offset', 'target': 8}),
                   instruction(24, literal(-2147483648), wide=True),
                   instruction(28), instruction(28)]}
    return {'format': codec.FORMAT, 'programs': [program, None, copy.deepcopy(program)]}


class EventCodecTests(unittest.TestCase):
    def test_labels_strings_and_signed_wide_operands_round_trip(self):
        program = fixture()['programs'][0]
        data = codec.encode_program(program)
        self.assertEqual(codec.decode_program(data), program)
        header = struct.unpack_from('>16H', data)
        self.assertEqual(header[:4], (0x1800, 0, len(data), 12))
        self.assertEqual(data[header[4]:], b'First\n\0Second\0\0\0')
        self.assertIn(struct.pack('>i', -2147483648), data)

    def test_width_and_string_edits_relocate_references(self):
        program = fixture()['programs'][0]
        original = codec.encode_program(program)
        program['instructions'][0]['wide'] = True
        program['strings'][0] = 'Longer first\n'
        changed = codec.encode_program(program)
        self.assertEqual(codec.decode_program(changed), program)
        before, after = struct.unpack_from('>16H', original), struct.unpack_from('>16H', changed)
        self.assertEqual(after[4], before[4] + 2)
        self.assertEqual(after[7:11], tuple(value + 2 for value in before[7:11]))
        offsets, _, _ = codec.instruction_layout(program['instructions'])
        self.assertEqual(struct.unpack_from('>i', changed, offsets[4] + 2)[0], offsets[6])
        self.assertEqual(struct.unpack_from('>h', changed, offsets[2] + 2)[0], len('Longer first\n') + 1)

    def test_bank_offsets_empty_slot_flags_and_fresh_rzip(self):
        records = fixture()
        bank = codec.encode_bank(records)
        table = list(struct.iter_unpack('>II', bank[:24]))
        self.assertEqual(table[0][0], 24)
        self.assertEqual(table[1][1], 0)
        self.assertEqual(table[1][0], table[2][0])
        self.assertEqual(table[-1][1] >> 28, 9)
        for index in (0, 2):
            at, flags = table[index]
            packed = bank[at:at + (flags & 0x0fffffff)]
            decoded = build.rzip_archive.decode_rzip_chunk(packed)
            self.assertEqual(decoded.consumed, len(packed))
            self.assertEqual(codec.decode_program(decoded.data), records['programs'][index])
            end = at + len(packed)
            following = table[2][0] if index == 0 else len(bank)
            self.assertEqual(bank[end:following], bytes((-end) % 8))
        records['programs'][0]['flags'] ^= 0x800
        self.assertNotEqual(codec.encode_bank(records), bank)

    def test_schema_bounds_labels_and_unused_fields_are_rejected(self):
        for change in ('opaque', 'flags', 'state', 'entry', 'opcode', 'wide', 'arity', 'mode',
                       'value', 'native', 'target', 'string', 'unreferenced', 'nul', 'nonascii', 'bool'):
            program = fixture()['programs'][0]
            if change == 'opaque': program['raw_hex'] = '00'
            elif change == 'flags': program['flags'] |= 1
            elif change == 'state': program['state_bytes'] = 3
            elif change == 'entry': program['entrypoints'][0] = 1
            elif change == 'opcode': program['instructions'][0]['opcode'] = 0
            elif change == 'wide': program['instructions'][-1]['wide'] = True
            elif change == 'arity': program['instructions'][0]['operands'] = []
            elif change == 'mode': program['instructions'][0]['operands'][0]['mode'] = 'raw'
            elif change == 'value': program['instructions'][0]['operands'][0]['value'] = 32768
            elif change == 'native': program['instructions'][3]['operands'][0]['value'] = 14
            elif change == 'target': program['instructions'][4]['operands'][0]['target'] = 9
            elif change == 'string': program['instructions'][1]['operands'][0]['string'] = -1
            elif change == 'unreferenced': program['strings'].append('unused')
            elif change == 'nul': program['strings'][0] = 'A\0B'
            elif change == 'nonascii': program['strings'][0] = '\xff'
            elif change == 'bool': program['flags'] = True
            with self.subTest(change=change), self.assertRaises(ValueError):
                codec.encode_program(program)
        data = bytearray(codec.encode_program(fixture()['programs'][0]))
        for offset in (2, 10, 22, len(data) - 1):
            changed = data[:]
            changed[offset] ^= 1
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                codec.decode_program(changed)
        changed = data[:]
        changed[32] ^= 1  # Unused operand-selector bits cannot hide in a raw word.
        with self.assertRaises(ValueError):
            codec.decode_program(changed)


class EventBuildTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory()
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.records = fixture()
        self.payload = codec.encode_bank(self.records)
        self.rom = b'prefix' + self.payload + b'tail'
        self.expected = {'rom_start': 6, 'rom_end': 6 + len(self.payload),
                         'original_sha256': build.sha256(self.payload)}
        self.inputs = self.root / build.INPUT_DIRECTORY
        build.texture_build.publish_inputs(self.inputs, build.input_files(self.expected, self.records))

    def test_fresh_source_build_preserves_mtime_and_missing_part_is_repaired(self):
        with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.records)):
            proof = build.build_parts(self.root)
            part = self.root / 'build/us/events/parts/asset_bank_14.bin'
            before = [p.stat().st_mtime_ns for p in (part, self.inputs / 'programs.json')]
            self.assertEqual(build.build_parts(self.root), proof)
            self.assertEqual([p.stat().st_mtime_ns for p in (part, self.inputs / 'programs.json')], before)
            part.unlink()
            build.build_parts(self.root)
            self.assertEqual(part.read_bytes(), self.payload)

    def test_missing_changed_and_malformed_sources_preserved_until_recovery(self):
        changed = copy.deepcopy(self.records)
        changed['programs'][0]['flags'] ^= 0x800
        for name, data in [('programs.json', json.dumps(changed).encode()), ('programs.json', b'{'),
                           ('manifest.json', b'{}'), ('programs.json', None)]:
            for file, content in build.input_files(self.expected, self.records).items():
                (self.inputs / file).write_bytes(content)
            path = self.inputs / name
            if data is None: path.unlink()
            else: path.write_bytes(data)
            before = {p.name: p.read_bytes() for p in self.inputs.iterdir()}
            with self.subTest(name=name), self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                build.packed_bank(self.inputs, self.expected)
            self.assertEqual({p.name: p.read_bytes() for p in self.inputs.iterdir()}, before)
        with patch.object(build, 'reviewed_bank', return_value=(self.rom, self.expected, self.records)):
            result = build.recover_inputs(self.root)
        backup = Path(result['backup_directory'])
        self.assertFalse((backup / 'programs.json').exists())
        self.assertEqual(build.packed_bank(self.inputs, self.expected)[0], self.payload)

    def test_source_change_during_encoding_fails(self):
        encode = codec.encode_bank
        def changed(records):
            packed = encode(records)
            with (self.inputs / 'programs.json').open('a') as file: file.write(' ')
            return packed
        with patch.object(codec, 'encode_bank', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_bank(self.inputs, self.expected)

    def test_report_requires_actual_link_object_from_current_sources(self):
        from test_objdiff_data_targets import object_file, targets
        linked = self.root / 'build/us/assets/asset_bank_14.o'
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, self.payload)]))
        with patch.object(targets, 'ROOT', self.root):
            unit, item = targets.prepare_event_bank(self.rom, self.expected, output=self.root / 'report')
            self.assertTrue(unit['complete'])
            self.assertEqual(unit['report_data_bytes'], len(self.payload))
            self.assertEqual(item['name'], 'assets/asset_bank_14')
            self.assertEqual(len(unit['source_inputs']), 2)
            linked.write_bytes(object_file([('.data', 1, 3, bytes(len(self.payload)))]))
            with self.assertRaisesRegex(ValueError, 'candidate differs'):
                targets.prepare_event_bank(self.rom, self.expected, output=self.root / 'report')
