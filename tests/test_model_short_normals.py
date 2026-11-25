from copy import deepcopy
import struct
import unittest

from scripts import model_short_normals as codec
from test_model_extended_build import normal_surface_payload


def short_payload():
    raw = normal_surface_payload(primary=False)
    header = list(struct.unpack_from('>10I', raw))
    old_face = header[4]
    header[3] = 6
    header[4] = header[2] + 6
    return struct.pack('>10I', *header) + raw[40:header[2] + 6] + raw[old_face:]


class ShortNormalTests(unittest.TestCase):
    def test_short_table_and_face_fields_are_independent(self):
        raw = short_payload(); source = codec.decode(raw)
        self.assertEqual(codec.encode(source), raw)
        self.assertEqual(len(source['normal_xy_s8']), 3)
        for slot in range(3):
            for component in (0, 1):
                changed = deepcopy(source); changed['normal_xy_s8'][slot][component] ^= 1
                packed = codec.encode(changed)
                self.assertEqual([i for i, (a, b) in enumerate(zip(raw, packed)) if a != b],
                                 [source['header_words'][2] + 2 * slot + component])
        changed = deepcopy(source); changed['face_words'][0] ^= 1
        self.assertEqual(codec.decode(codec.encode(changed)), changed)

    def test_loads_cannot_read_adjacent_face_words_or_uninitialized_normals(self):
        source = codec.decode(short_payload())
        load = next(i for i, (word, _) in enumerate(source['display_commands']) if word >> 24 == 1)
        for word in (0x01004008, 0x01003008, 0x01002004):
            changed = deepcopy(source); changed['display_commands'][load][0] = word
            with self.assertRaises(ValueError): codec.encode(changed)
        changed = deepcopy(source); changed['display_commands'][0] = [0xE7000000, 0]
        with self.assertRaisesRegex(ValueError, 'outside'): codec.encode(changed)
        changed = deepcopy(source); changed['display_commands'][0][1] += 2
        with self.assertRaisesRegex(ValueError, 'explicit table'): codec.encode(changed)

    def test_unknown_layouts_counts_and_trailing_storage_fail(self):
        source = codec.decode(short_payload())
        for field, value in [('normal_xy_s8', []), ('face_words', []), ('opaque', []),
                             ('zero_tail_bytes', -1), ('zero_tail_bytes', 13), ('vertices', [[]])]:
            changed = dict(source, **{field: value})
            with self.assertRaises(ValueError): codec.encode(changed)
        for field in (2, 3, 4, 5, 6, 7, 8, 9):
            changed = deepcopy(source); changed['header_words'][field] ^= 1
            with self.assertRaises(ValueError): codec.encode(changed)
        raw = bytearray(short_payload()); raw[-1] = 1
        with self.assertRaisesRegex(ValueError, 'trailing'): codec.decode(bytes(raw))
        with self.assertRaises(ValueError): codec.decode(normal_surface_payload(primary=False))
