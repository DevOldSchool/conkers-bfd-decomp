from copy import deepcopy
import struct
import unittest

from scripts import model_duplicate_normals as codec
from test_model_extended_build import normal_surface_payload


def duplicate_payload():
    primary = normal_surface_payload()
    header = list(struct.unpack_from('>10I', primary))
    end = header[0] + header[1]
    prefix = primary[header[2]:header[2] + header[3]]
    commands = bytearray(primary[header[0]:end])
    struct.pack_into('>I', commands, 4, end + len(prefix))
    header[2:] = [0, 0, 0, 0, 0, 0, 0, 0x80000000]
    child = struct.pack('>10I', *header) + primary[40:header[0]] + commands + prefix + bytes(64)
    stop = 32 + len(primary) + len(child)
    return (struct.pack('>8I', 32, len(primary), 32 + len(primary), len(child), stop, 0, stop, 0x80000000)
            + primary + child)


class DuplicateNormalCodecTests(unittest.TestCase):
    def test_typed_parent_mutations_update_exactly_both_stored_copies(self):
        raw = duplicate_payload(); source = codec.decode(raw)
        self.assertEqual(codec.encode(source), raw)
        primary, child = source['segments'][:2]
        first = source['descriptors'][0][0] + primary['header_words'][2]
        second = source['descriptors'][1][0] + sum(child['header_words'][:2])
        for slot in range(32):
            for component in (0, 1):
                changed = deepcopy(source); changed['segments'][0]['normal_xy_s8'][0][slot][component] ^= 1
                packed = codec.encode(changed)
                self.assertEqual([i for i, (a, b) in enumerate(zip(raw, packed)) if a != b],
                                 [first + 2 * slot + component, second + 2 * slot + component])
        changed = deepcopy(source); changed['segments'][1]['normal_xy_s8'][0][31][1] = 17
        self.assertEqual(codec.decode(codec.encode(changed)), changed)

    def test_copy_mismatch_missing_reference_and_unexplained_storage_are_rejected(self):
        raw = duplicate_payload(); source = codec.decode(raw); child = source['segments'][1]
        child_at = source['descriptors'][1][0]; prefix_at = child_at + sum(child['header_words'][:2])
        changed = bytearray(raw); changed[prefix_at + 3] ^= 1
        with self.assertRaisesRegex(ValueError, 'differs'): codec.decode(bytes(changed))
        for value in ({'segment': 1, 'first_table': 0, 'table_count': 1},
                      {'segment': 0, 'first_table': 1, 'table_count': 1},
                      {'segment': 0, 'first_table': 0, 'table_count': 2}):
            changed = deepcopy(source); changed['segments'][1]['duplicated_normal_source'] = value
            with self.assertRaises(ValueError): codec.encode(changed)
        for value in (0, sum(child['header_words'][:2]), sum(child['header_words'][:2]) + 65):
            changed = deepcopy(source); changed['segments'][1]['display_commands'][0][1] = value
            with self.assertRaises(ValueError): codec.encode(changed)

    def test_roles_descriptors_counts_and_unknown_fields_are_rejected(self):
        source = codec.decode(duplicate_payload())
        cases = []
        for field, value in [('format', 'raw'), ('segments', [None] * 4), ('opaque', [])]:
            cases.append(dict(source, **{field: value}))
        for field, value in [('normal_xy_s8', []), ('vertices', []), ('header_words', [0] * 10), ('opaque', [])]:
            changed = deepcopy(source); changed['segments'][1][field] = value; cases.append(changed)
        changed = deepcopy(source); changed['segments'][0]['primary'] = False; cases.append(changed)
        changed = deepcopy(source); changed['descriptors'][1][0] += 8; cases.append(changed)
        for changed in cases:
            with self.assertRaises(ValueError): codec.encode(changed)
