from __future__ import annotations

import copy
import struct
import unittest
from dataclasses import replace

from scripts import model_assets as models
from scripts.model_effect_format import (
    EffectModelSource, effect_header, encode_effect_model, is_effect_model,
    parse_effect_model, resolve_effect_sources, verify_effect_consumers,
)


TYPES = (10, 10, 21, 22, 23, 24, 20, 19, 68, 69, 19)


def payload(*, draw=True, material=True, second=True, x=0, texture=10):
    vertices = b"".join(struct.pack(">hhhHhh4B", a + x, b, 0, 0, s, t, 255, 255, 255, 255)
                        for a, b, s, t in ((0, 0, 0, 0), (16, 0, 512, 0), (0, 16, 0, 512)))
    material_commands = (
        (0xD7000002, 0xFFFFFFFF), (0xFD100000, texture),
        (0xF5100000, 0x07000000), (0xF3000000, 0x077FF000),
        (0xF5102000, 0x00094260), (0xF2000000, 0x000FC07C), (0xDF000000, 0),
    ) if material else ()
    draw_commands = ((0x01003006, 0x01000000), (0x05000204, 0), (0xDF000000, 0)) if draw else ()
    sections = (vertices, vertices if second else b"",
                b"".join(struct.pack(">II", *command) for command in material_commands),
                b"".join(struct.pack(">II", *command) for command in draw_commands))
    words, offset = [], 32
    for index, section in enumerate(sections):
        words.extend((offset if section else 0, len(section) | (0x80000000 if index == 3 else 0)))
        offset += len(section)
    return struct.pack(">8I", *words) + b"".join(sections)


class EffectModelTests(unittest.TestCase):
    def decode(self, data, source=None):
        return parse_effect_model(data, models.parse_model_geometry, source)

    def regions(self, data, layout):
        return {s["name"]: data[s["offset"]:s["offset"] + s["size"]] for s in layout["sections"]}

    def test_native_geometry_material_order_and_roundtrip(self):
        for second in (True, False):
            data = payload(second=second)
            geometry, layout = self.decode(data)
            self.assertEqual(geometry.faces, ((0, 1, 2),))
            self.assertEqual(geometry.face_command_offsets, (effect_header(data)[6] + 8,))
            run = geometry.material_runs[0]
            self.assertTrue(run.texture_enabled)
            self.assertTrue(run.texture_coordinates_proven)
            self.assertEqual(run.pixel.flat_index, 10)
            self.assertIsNone(run.other_mode)  # Inherited bits have no invented defaults.
            self.assertEqual(encode_effect_model(geometry, layout, self.regions(data, layout)), data)
            self.assertEqual(models.parse_geometry_for_bank(data, 9), geometry)

    def test_shared_rom_triangle_and_material_dependencies(self):
        entries = {i: payload(x=i, texture=i) for i in range(173, 184)}
        entries[174] = payload(draw=False, material=False, x=174)
        entries[182] = payload(draw=False, x=182, texture=182)
        entries[183] = payload(material=False, second=False, x=183)
        sources = resolve_effect_sources(entries, TYPES)
        for entry, geometry_entry, material_entry in ((174, 173, 173), (182, 181, 182), (183, 183, 180)):
            with self.subTest(entry=entry):
                data = entries[entry]
                geometry, layout = self.decode(data, sources[entry])
                self.assertEqual(geometry.vertices[0].x, entry)
                self.assertEqual(geometry.material_runs[0].pixel.flat_index, material_entry)
                self.assertEqual(layout["geometry_source_entry"], geometry_entry)
                self.assertEqual(layout["material_source_entry"], material_entry)
                self.assertEqual([0xD9FDFFFF, 0], layout["draw_setup_commands"][0])
                self.assertEqual(None if entry == 183 else (0xEF082CAF, 0x00504A50),
                                 geometry.material_runs[0].other_mode)
                self.assertEqual(geometry.face_command_offsets, (effect_header(entries[geometry_entry])[6] + 8,))
                self.assertEqual(encode_effect_model(geometry, layout, self.regions(data, layout)), data)
                segment = models.ModelSegment(0, 0, len(data), True, data, sources[entry])
                self.assertEqual(models.parse_segment_geometry(segment, 9), geometry)
                with self.assertRaisesRegex(ValueError, "bank 09"):
                    models.parse_segment_geometry(segment, 3)

    def test_missing_dependencies_fail_closed(self):
        with self.assertRaisesRegex(ValueError, "shared ROM"):
            self.decode(payload(draw=False, material=False))
        with self.assertRaisesRegex(ValueError, "missing a ROM dependency"):
            resolve_effect_sources({}, TYPES)
        with self.assertRaisesRegex(ValueError, "verified eleven-entry"):
            resolve_effect_sources({}, ())
        with self.assertRaisesRegex(ValueError, "consumer changed"):
            verify_effect_consumers(bytes(0x190000), 0x15000000, b"", 0x80082B20)

    def test_header_bounds_and_terminators(self):
        original = payload()
        for offset, value in ((0, 16), (4, 49), (8, 32), (12, 32),
                              (16, len(original)), (20, 0), (24, 0), (28, 24)):
            with self.subTest(offset=offset, value=value):
                data = bytearray(original)
                struct.pack_into(">I", data, offset, value)
                with self.assertRaises(ValueError):
                    self.decode(bytes(data))
        self.assertFalse(is_effect_model(original[:31]))
        with self.assertRaisesRegex(ValueError, "nonzero tail"):
            self.decode(original + b"x")
        data = bytearray(original)
        data[-8] = 0
        with self.assertRaisesRegex(ValueError, "unterminated"):
            self.decode(bytes(data))
        data = bytearray(original)
        struct.pack_into(">II", data, effect_header(data)[4], 0xDF000000, 0)
        with self.assertRaisesRegex(ValueError, "early terminator"):
            self.decode(bytes(data))

    def test_primary_and_secondary_vertices_are_checked(self):
        data = payload()
        geometry, layout = self.decode(data)
        changed = replace(geometry, vertices=(replace(geometry.vertices[0], x=7), *geometry.vertices[1:]))
        with self.assertRaisesRegex(ValueError, "primary vertices"):
            encode_effect_model(changed, layout, self.regions(data, layout))
        other_layout = copy.deepcopy(layout)
        other_layout["vertex_buffers"][1][0][0] = 9
        encoded = encode_effect_model(geometry, other_layout, self.regions(data, layout))
        self.assertEqual(struct.unpack_from(">h", encoded, layout["vertex_offsets"][1])[0], 9)
        regions = self.regions(data, layout)
        regions["material"] = bytes(len(regions["material"]))
        with self.assertRaisesRegex(ValueError, "section identity"):
            encode_effect_model(geometry, layout, regions)

    def test_shared_geometry_cannot_address_past_variant_vertices(self):
        data = payload()
        shared = bytearray(data)
        struct.pack_into(">I", shared, effect_header(shared)[6] + 4, 0x01000010)
        source = EffectModelSource(174, 173, bytes(shared), 173, data, 10)
        with self.assertRaises(ValueError):
            self.decode(payload(draw=False, material=False), source)


if __name__ == "__main__":
    unittest.main()
