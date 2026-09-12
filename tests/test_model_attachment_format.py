from __future__ import annotations

import copy
import json
import struct
import tempfile
import unittest
from dataclasses import replace
from pathlib import Path

from scripts import model_assets as models
from scripts import texture_assets
from scripts.model_attachment_format import encode_attachment_model, parse_attachment_model


def payload(*, jointed=False, parts=1, inherited_texture=False):
    vertices = b"".join(
        struct.pack(">hhhHhh4B", x, y, 0, 127, 0, 0, 255, 255, 255, 255)
        for x, y in ((0, 0), (10, 0), (0, 10)))
    table = 24 + len(vertices)
    joint_data = struct.pack(">bBBB3f", -1, 0, 0, 0, 2.0, 3.0, 4.0) if jointed else b""
    joint_offset = table + parts * 4 if jointed else 0
    start = (table + parts * 4 + len(joint_data) + 7) & ~7
    commands = [(0xD7000002 if inherited_texture else 0xD7000000, 0xFFFFFFFF),
                (0xDA380003, 0x03000000), (0xDC38000E, 0),
                (0x01003006, 0x01000000), (0x05000204, 0), (0xDF000000, 0)]
    list_size = len(commands) * 8
    normals = start + parts * list_size
    commands[2] = (0xDC38000E, normals)
    result = bytearray(normals + 64)
    struct.pack_into(">6I", result, 0, table, parts * 4, joint_offset, len(joint_data), normals, 0x80000040)
    result[24:table] = vertices
    struct.pack_into(f">{parts}I", result, table, *(start + i * list_size for i in range(parts)))
    if jointed:
        result[joint_offset:joint_offset + len(joint_data)] = joint_data
    for part in range(parts):
        for index, command in enumerate(commands):
            struct.pack_into(">II", result, start + part * list_size + index * 8, *command)
    result[normals:] = bytes((1, 254)) * 32
    return bytes(result)


class AttachmentFormatTests(unittest.TestCase):
    def decode(self, data):
        return parse_attachment_model(data, models.parse_model_geometry)

    def regions(self, data, layout):
        return {section["name"]: data[section["offset"]:section["offset"] + section["size"]]
                for section in layout["sections"]}

    def test_rigid_and_jointed_native_reconstruction(self):
        for jointed in (False, True):
            for parts in (1, 2):
                with self.subTest(jointed=jointed, parts=parts):
                    data = payload(jointed=jointed, parts=parts)
                    geometry, layout = self.decode(data)
                    self.assertEqual(len(geometry.faces), parts)
                    self.assertEqual(geometry.header_words, struct.unpack_from(">6I", data))
                    self.assertEqual(geometry.face_normal_bytes[0], ((1, -2, 127),) * 3)
                    self.assertEqual(geometry.face_command_offsets[0], layout["display_list_pointers"][0] + 32)
                    self.assertEqual(encode_attachment_model(geometry, layout, self.regions(data, layout)), data)
                    self.assertEqual(models.parse_geometry_for_bank(data, 9), geometry)
                    if jointed:
                        faces = models.validation_face_records(geometry, tuple(layout["joints"]))
                        self.assertEqual(faces[0]["positions"][0], (2.0, 3.0, 4.0))
                        gltf, _ = models.encode_gltf(0, 0, geometry, bank_index=9,
                                                    character_joints=tuple(layout["joints"]))
                        extras = json.loads(gltf)["extras"]
                        self.assertEqual(extras["attachmentMatrixState"]["renderer"], "func_150311C4")
                        self.assertNotIn("characterMatrixState", extras)
                        self.assertEqual(extras["animationStatus"], "attachment-animation-not-recovered")

    def test_encoder_uses_decoded_vertices_and_joints(self):
        data = payload(jointed=True)
        geometry, layout = self.decode(data)
        changed = replace(geometry, vertices=(replace(geometry.vertices[0], x=7), *geometry.vertices[1:]))
        encoded = encode_attachment_model(changed, layout, self.regions(data, layout))
        self.assertEqual(struct.unpack_from(">h", encoded, 24)[0], 7)
        layout = copy.deepcopy(layout)
        layout["joints"][0]["bind_pivot_f32"][1] = 9.0
        encoded = encode_attachment_model(geometry, layout, self.regions(data, layout))
        self.assertEqual(struct.unpack_from(">f", encoded, layout["joint_offset"] + 8)[0], 9.0)

    def test_reconstruction_rejects_changed_opaque_region(self):
        data = payload()
        geometry, layout = self.decode(data)
        regions = self.regions(data, layout)
        regions["normals"] = bytes(64)
        with self.assertRaisesRegex(ValueError, "region identity"):
            encode_attachment_model(geometry, layout, regions)

    def test_inherited_texture_coordinates_are_not_invented(self):
        geometry, _ = self.decode(payload(inherited_texture=True))
        self.assertTrue(geometry.material_runs[0].texture_enabled)
        self.assertFalse(geometry.material_runs[0].texture_coordinates_proven)
        self.assertNotIn(b"\nvt ", models.encode_obj(0, 0, geometry, bank_index=9))

    def test_independent_parts_cannot_borrow_vertex_cache(self):
        data = bytearray(payload(parts=2))
        _, layout = self.decode(bytes(data))
        second = layout["display_list_pointers"][1]
        # Replace the second part's VTX with a harmless matrix command.
        struct.pack_into(">II", data, second + 24, 0xDA380003, 0x03000000)
        with self.assertRaisesRegex(ValueError, "unloaded vertex"):
            self.decode(bytes(data))

    def test_malformed_ranges_and_joint_hierarchies_rejected(self):
        original = payload(jointed=True, parts=2)
        _, layout = self.decode(original)
        table, joint = layout["pointer_table_offset"], layout["joint_offset"]
        mutations = {
            "header range": (4, struct.pack(">I", 0x10000)),
            "duplicate list": (table + 4, original[table:table + 4]),
            "cyclic joint": (joint, bytes((0,))),
            "absent parent": (joint, bytes((3,))),
            "missing matrix": (joint + 1, bytes((1,))),
            "nonfinite pivot": (joint + 4, struct.pack(">f", float("nan"))),
            "normal range": (layout["display_list_pointers"][0] + 20, struct.pack(">I", len(original))),
        }
        for name, (offset, raw) in mutations.items():
            with self.subTest(name=name):
                data = bytearray(original)
                data[offset:offset + len(raw)] = raw
                with self.assertRaises(ValueError):
                    self.decode(bytes(data))

    def test_unknown_gap_and_tail_rejected(self):
        original = payload()
        _, layout = self.decode(original)
        gap = layout["pointer_table_offset"] + layout["pointer_table_size"]
        data = bytearray(original)
        data[gap] = 1
        with self.assertRaisesRegex(ValueError, "nonzero gaps"):
            self.decode(bytes(data))
        with self.assertRaisesRegex(ValueError, "nonzero tail"):
            self.decode(original + bytes((1,)))

    def test_captured_rgba32_decodes_rows_and_preserves_alpha(self):
        run = models.ModelMaterialRun(
            first_face=0, face_count=1, texture_enabled=True,
            pixel=models.ModelTextureBinding(image_command=0xFD180000,
                                            load_command=(0xF3000000, 0x07007000)),
            palette=None, render_tile=(0xF5180200, 0), render_tiles=(),
            tile_bounds=(0xF2000000, 0x0000C004), texture_scale=(0xD7000002, 0xFFFFFFFF),
            combine_mode=None, other_mode=None, runtime_render_state_offset=None)
        state = {"other_mode": [0xEF182C3F, 0], "texture": {"enabled": True,
                 "pixel_image": {"command": 0xFD180000, "captured_texture_image_index": 3}}}
        pixels = bytes(range(32))
        captured = models.runtime_captured_preview_texture(run, state, {3: pixels})
        self.assertEqual(captured["format"], "rgba32")
        rgba = texture_assets.decode_rgba_png_pixels(captured["png_data"], 4, 2)
        # Exported PNGs are vertically flipped for OBJ/glTF's V convention.
        self.assertEqual(rgba, pixels[24:32] + pixels[16:24] + pixels[:16])
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            png = root / captured["file"]
            png.parent.mkdir()
            png.write_bytes(captured["png_data"])
            texture = models.runtime_captured_texture_choice({
                "_source_root": root, "variants": [{"captured_texture": captured}]})
            self.assertEqual((texture.format, texture.size, texture.width, texture.height), (0, 3, 4, 2))
        for mutation in (replace(run, render_tile=(0xF5180201, 0)),
                         replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x07007001))),
                         replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x07006000)))):
            with self.subTest(mutation=mutation):
                self.assertIsNone(models.runtime_captured_preview_texture(mutation, state, {3: pixels}))
        self.assertIsNone(models.runtime_captured_preview_texture(run, state, {3: pixels[:-1]}))
        state["other_mode"] = [0xEF18AC3F, 0]
        self.assertIsNone(models.runtime_captured_preview_texture(run, state, {3: pixels}))


if __name__ == "__main__":
    unittest.main()
