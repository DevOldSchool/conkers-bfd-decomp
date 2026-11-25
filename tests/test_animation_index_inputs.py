"""Index ownership and edited-input guards independent of animation decoding."""
from copy import deepcopy
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest.mock import patch

from scripts import animation_index_inputs as indexes


class AnimationIndexInputsTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(); self.addCleanup(temp.cleanup)
        self.directory = Path(temp.name)
        # Two structurally valid segments with deliberately uninterpreted contents.
        self.table = struct.pack('>4I',16,8,24,0x80000008)
        self.payload = self.table + b'unknown!' + b'raw clip'
        self.expected = {'part':'00D3CBA0','rom_start':100,'rom_end':140,
                         'original_sha256':indexes.sha(self.payload+b'raw tail'),
                         'entries':[{'entry':82,'pair_count':1,'rom_start':100,'rom_end':132}],
                         'rom_ranges':[]}
        self.backing = self.payload+b'raw tail'
        (self.directory/'backing.bin').write_bytes(self.backing)
        child = self.directory/'indexes'; child.mkdir()
        for name,data in indexes.input_files(self.backing,self.expected).items():
            (child/name).write_bytes(data)

    def test_only_directory_is_owned_and_unknown_payload_is_not_interpreted(self):
        self.assertEqual(indexes.owned_ranges(self.expected), [[100,116]])
        self.assertEqual(indexes.packed_spans(self.directory,self.expected), [(0,self.table)])
        self.assertEqual((self.directory/'backing.bin').read_bytes(), self.backing)
        self.assertEqual(set(indexes.input_hashes(self.directory,self.expected)), {'manifest.json','indexes.json'})

    def test_wrong_flags_offsets_lengths_and_entry_sets_are_rejected_without_replacing_source(self):
        path = self.directory/'indexes/indexes.json'; original = json.loads(path.read_text())
        edits = [lambda r:r['82']['entries'][-1].__setitem__('flags',0),
                 lambda r:r['82']['entries'][1].__setitem__('stored_size',0),
                 lambda r:r['82']['entries'][1].__setitem__('relative_offset',32),
                 lambda r:r.__setitem__('83',r['82']), lambda r:r.pop('82'),
                 lambda r:r['82'].__setitem__('opaque','raw')]
        for edit in edits:
            changed = deepcopy(original); edit(changed); path.write_text(json.dumps(changed))
            with self.assertRaises(ValueError): indexes.packed_spans(self.directory,self.expected)
            self.assertEqual(json.loads(path.read_text()),changed)

    def test_parent_changes_overlapping_credit_and_outside_entry_are_rejected(self):
        for edit in [lambda e:e['entries'][0].__setitem__('rom_start',99),
                     lambda e:e['entries'][0].__setitem__('rom_end',115),
                     lambda e:e['entries'][0].__setitem__('pair_count',2),
                     lambda e:e['rom_ranges'].append([108,124]),
                     lambda e:e['entries'].append(deepcopy(e['entries'][0]))]:
            expected = deepcopy(self.expected); edit(expected)
            with self.assertRaises(ValueError): indexes.reviewed(self.backing,expected)
        with self.assertRaises(ValueError): indexes.reviewed(b'x'+self.backing[1:],self.expected)

    def test_missing_child_and_concurrent_edits_fail(self):
        path = self.directory/'indexes/indexes.json'; original = path.read_bytes()
        path.unlink()
        with self.assertRaises(OSError): indexes.packed_spans(self.directory,self.expected)
        self.assertFalse(path.exists()); path.write_bytes(original)
        encode = indexes.codec.encode
        def race(record):
            result = encode(record)
            path.write_bytes(path.read_bytes()+b' ')
            return result
        with patch.object(indexes.codec,'encode',side_effect=race):
            with self.assertRaisesRegex(ValueError,'changed during packing'):
                indexes.packed_spans(self.directory,self.expected)


if __name__ == '__main__':
    unittest.main()
