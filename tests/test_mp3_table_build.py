"""Independent Huffman traversal, editable-input safety and report linkage checks."""
import copy
import hashlib
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import mp3_table_build as build
from scripts import mp3_table_codec as codec


def records():
    names = [f'var{i}' for i in range(17)]
    return {'format': codec.FORMAT,
            'codebooks': {name: [[0, 0, 1, 0], [1, 0, 1, 1]] for name in names},
            'table_codebooks': [None, *names, *names[:16]]}


class Mp3TableCodecTests(unittest.TestCase):
    def test_canonical_c_seeds_reproduce_rom_hashes_and_every_leaf(self):
        source = (build.ROOT / build.SEED_SOURCE).read_text()
        seeds = codec.seed_records(source)
        packed = codec.encode_tables(seeds)
        self.assertEqual({k: build.sha256(v) for k, v in packed.items()}, {
            'mp3_huffman_offsets': 'a8201bbc8ba01bb3008aa89f73914ee676ae01134d45fdf26ce454b2563f8d12',
            'mp3_lookup': '809d401abc1d09c4a82c2f95608449d36a2d3bd21abfa5bf2b911d08c8f99e37',
            'mp3_huffman': '966e0ffb6945fce6348d127af40683b279dcc67664da89473371a32422574582'})
        offsets = struct.unpack('>36I', packed['mp3_huffman_offsets'])
        nodes, lookup = packed['mp3_huffman'], packed['mp3_lookup']
        self.assertEqual(nodes[-4:], bytes((0, 0, 255, 255)))
        self.assertEqual(offsets[-2:], (0, 0))
        for table, name in enumerate(seeds['table_codebooks'][1:], 1):
            for x, y, width, code in seeds['codebooks'][name]:
                cursor = offsets[table]
                for bit in range(width):
                    self.assertEqual(nodes[cursor + 2:cursor + 4], b'\xff\xff')
                    edge = nodes[cursor + ((code >> bit) & 1)]
                    self.assertGreater(edge, 0)
                    cursor += 4 * edge
                self.assertEqual(nodes[cursor:cursor + 4], bytes((0, 0, x, y)))
            # Independently walk all 256 input bytes to validate fast-path fallback.
            for byte in range(256):
                cursor, consumed = offsets[table], 0
                while nodes[cursor + 2:cursor + 4] == b'\xff\xff' and consumed < 8:
                    cursor += 4 * nodes[cursor + ((byte >> (7 - consumed)) & 1)]
                    consumed += 1
                leaf = nodes[cursor + 2:cursor + 4] != b'\xff\xff'
                at = table * 256 + byte
                self.assertEqual(lookup[at + 0x2200], consumed if leaf else 0)
                self.assertEqual(lookup[at], (nodes[cursor + 3] << 4) | nodes[cursor + 2] if leaf else 0)

    def test_parser_rejects_malformed_rows_terminators_and_pointer_expressions(self):
        source = (build.ROOT / build.SEED_SOURCE).read_text()
        for old, new in [('100, 100, 100, 0, 0', '100, 100, 99, 0, 0'),
                         ('(struct mp3decthing *)var70054b40', '(struct mp3decthing *)(var70054b40+1)'),
                         ('var70054b40[] = {', 'var70054b40[] = { unexpected,')]:
            self.assertIn(old, source)
            with self.subTest(old=old), self.assertRaises(ValueError):
                codec.seed_records(source.replace(old, new, 1))

    def test_seed_semantics_change_generated_nodes_and_lookup(self):
        original = records()
        altered = copy.deepcopy(original)
        altered['codebooks']['var0'][0][0] = 2
        a, b = codec.encode_tables(original), codec.encode_tables(altered)
        self.assertEqual(a['mp3_huffman_offsets'], b['mp3_huffman_offsets'])
        self.assertNotEqual(a['mp3_huffman'], b['mp3_huffman'])
        self.assertNotEqual(a['mp3_lookup'], b['mp3_lookup'])

    def test_rejects_ambiguous_and_unrepresentable_trees(self):
        for rows in ([[0, 0, 1, 0], [1, 0, 2, 0]], [[0, 0, 1, 0], [1, 0, 1, 0]],
                     [[0, 0, 2, 0], [1, 0, 2, 1]], [[0, 0, 1, 0], [0, 0, 1, 1]],
                     [[0, 0, 1, 0], [16, 0, 1, 1]], [[0, 0, 1, 0], [1, 0, 1, 2]],
                     [[0, 0, 1, 0], [1, 0, True, 1]], [[0, 0, 1, 0], [1, 0, 33, 1]]):
            with self.subTest(rows=rows), self.assertRaises(ValueError):
                codec.encode_tree(rows)
        malformed = records()
        malformed['table_codebooks'][1] = []
        with self.assertRaises(ValueError):
            codec.encode_tables(malformed)

    def test_consumer_gate_checks_both_endpoints(self):
        code = b'prefixconsumer tail'
        pin = (6, 8, hashlib.sha1(code[6:14]).hexdigest(), 'test')
        with patch.object(codec, 'CONSUMERS', (pin,)):
            codec.verify_consumers(code)
            for offset in (6, 13):
                changed = bytearray(code)
                changed[offset] ^= 1
                with self.assertRaisesRegex(ValueError, 'consumer differs'):
                    codec.verify_consumers(changed)


class Mp3TableBuildTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.records = records()
        self.packed = codec.encode_tables(self.records)
        self.rom = b'prefix'
        parts = []
        for name, payload in self.packed.items():
            parts.append({'name': name, 'rom_start': len(self.rom), 'rom_end': len(self.rom) + len(payload),
                          'original_sha256': build.sha256(payload)})
            self.rom += payload
        self.expected = {'parts': parts}
        self.inputs = self.root / build.INPUT_DIRECTORY
        build.texture_build.publish_inputs(self.inputs, build.input_files(self.expected, self.records))

    def test_fresh_encoding_and_input_mutation_during_pack(self):
        encode = codec.encode_tables
        with patch.object(build.mp3_table_codec, 'encode_tables', wraps=encode) as fresh:
            packed, hashes = build.packed_tables(self.inputs, self.expected)
            fresh.assert_called_once_with(self.records)
        self.assertEqual(packed, self.packed)
        self.assertEqual(set(hashes), {'manifest.json', 'tables.json'})
        def changed(records):
            result = encode(records)
            with (self.inputs / 'tables.json').open('a') as file:
                file.write(' ')
            return result
        with patch.object(codec, 'encode_tables', side_effect=changed):
            with self.assertRaisesRegex(ValueError, 'changed during packing'):
                build.packed_tables(self.inputs, self.expected)

    def test_changed_and_missing_inputs_preserved_until_recovery(self):
        changed = copy.deepcopy(self.records)
        changed['codebooks']['var0'][0][0] = 2
        for name, data in [('tables.json', json.dumps(changed).encode()), ('manifest.json', b'{}'),
                           ('tables.json', b'{'), ('tables.json', None)]:
            for file, content in build.input_files(self.expected, self.records).items():
                (self.inputs / file).write_bytes(content)
            if data is None:
                (self.inputs / name).unlink()
            else:
                (self.inputs / name).write_bytes(data)
            before = {p.name: p.read_bytes() for p in self.inputs.iterdir()}
            with self.subTest(name=name, data=data), patch.object(build, 'reviewed_tables',
                    return_value=(self.rom, self.expected, self.records)):
                with self.assertRaisesRegex(ValueError, 'Inputs were preserved'):
                    build.build_parts(self.root)
                self.assertEqual({p.name: p.read_bytes() for p in self.inputs.iterdir()}, before)
                proof = build.recover_inputs(self.root)
                backup = Path(proof['backup_directory'])
                self.assertEqual({p.name: p.read_bytes() for p in backup.iterdir()}, before)
                self.assertEqual(build.packed_tables(self.inputs, self.expected)[0], self.packed)

    def test_build_initializes_sources_and_preserves_unchanged_timestamps(self):
        for p in self.inputs.iterdir():
            p.unlink()
        self.inputs.rmdir()
        with patch.object(build, 'reviewed_tables', return_value=(self.rom, self.expected, self.records)):
            first = build.build_parts(self.root)
            paths = [self.root / 'build/us/mp3-tables/parts' / (build.part_name(n) + '.bin') for n in self.packed]
            before = [p.stat().st_mtime_ns for p in [*paths, self.inputs / 'tables.json']]
            self.assertEqual(build.build_parts(self.root), first)
            self.assertEqual([p.stat().st_mtime_ns for p in [*paths, self.inputs / 'tables.json']], before)
        self.assertEqual([p.read_bytes() for p in paths], list(self.packed.values()))

    def test_rom_mismatch_cannot_publish_candidate(self):
        with patch.object(build, 'reviewed_tables', return_value=(b'bad reference', self.expected, self.records)):
            with self.assertRaisesRegex(ValueError, 'independent'):
                build.build_parts(self.root)
        self.assertFalse((self.root / 'build/us/mp3-tables/parts').exists())

    def test_report_requires_actual_link_object_matching_current_seeds(self):
        from test_objdiff_data_targets import object_file, targets
        part = self.expected['parts'][1]
        payload = self.packed[part['name']]
        linked = self.root / ('build/us/assets/' + build.part_name(part['name']) + '.o')
        linked.parent.mkdir(parents=True)
        linked.write_bytes(object_file([('.data', 1, 3, payload)]))
        def link(args, *, cwd, check):
            original = (cwd / args[-1]).read_bytes()
            self.assertEqual(original, payload)
            (cwd / 'target.o').write_bytes(object_file([('.data', 1, 3, original)]))
        with patch.object(targets, 'ROOT', self.root), patch.object(targets.subprocess, 'run', side_effect=link):
            unit, item = targets.prepare_mp3_table(self.rom, self.expected, part, output=self.root / 'report')
            self.assertTrue(unit['complete'])
            self.assertEqual(unit['report_data_bytes'], len(payload))
            self.assertEqual(len(unit['source_inputs']), 2)
            self.assertEqual(item['name'], 'assets/' + build.part_name(part['name']))
            linked.write_bytes(object_file([('.data', 1, 3, bytes(len(payload)))]))
            with self.assertRaisesRegex(ValueError, 'candidate differs'):
                targets.prepare_mp3_table(self.rom, self.expected, part, output=self.root / 'report')
