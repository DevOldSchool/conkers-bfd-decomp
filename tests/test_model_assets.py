from __future__ import annotations

import json
import struct
import unittest
from dataclasses import replace
from pathlib import Path

from scripts import model_assets


def bundle_payload(sizes=(8, 0, 16, 8)) -> bytes:
    header_size = len(sizes) * 8
    offset = header_size
    descriptors = bytearray()
    payload = bytearray()
    for index, size in enumerate(sizes):
        descriptors.extend(
            struct.pack(
                ">II",
                offset,
                size | (0x80000000 if index == len(sizes) - 1 else 0),
            )
        )
        payload.extend(bytes((index + 1,)) * size)
        offset += size
    return bytes(descriptors + payload)


def model_payload() -> bytes:
    vertices = b"".join(
        struct.pack(">hhhHhh4B", x, y, z, 0, s, t, red, green, blue, 255)
        for x, y, z, s, t, red, green, blue in (
            (0, 0, 0, 0, 0, 255, 0, 0),
            (10, 0, 0, 32, 0, 0, 255, 0),
            (0, 10, 0, 0, 32, 0, 0, 255),
        )
    )
    display_offset = 0x28 + len(vertices)
    commands = b"".join(
        struct.pack(">II", command, argument)
        for command, argument in (
            (0xD7000000, 0xFFFFFFFF),
            (0x01003006, 0x01000000),
            (0x05000204, 0),
            (0xDF000000, 0),
        )
    )
    header = struct.pack(
        ">10I",
        display_offset,
        len(commands),
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0x80000000,
    )
    return header + vertices + commands


def model_payload_with_segment_8_list() -> bytes:
    data = bytearray(model_payload())
    display_offset = struct.unpack_from(">I", data, 0)[0]
    commands = data[display_offset:]
    commands[-8:-8] = struct.pack(">II", 0xDE000000, 0x08000110)
    struct.pack_into(">I", data, 4, len(commands))
    return bytes(data[:display_offset] + commands)


def model_payload_with_regions_and_color_animation() -> bytes:
    data = bytearray(model_payload())
    secondary_offset = len(data)
    data.extend(b"SECOND!!")
    tertiary_offset = len(data)
    data.extend(struct.pack(">III", 0x3A000CAF, 5, 0x01000000))
    color_offset = len(data)
    data.extend(bytes((10, 20, 30, 40, 50, 60, 70, 80, 90)))
    index_offset = len(data)
    data.extend(struct.pack(">3H", 0, 2, 1))
    while len(data) % 4:
        data.append(0)
    table_offset = len(data)
    data.extend(struct.pack(">III", color_offset, index_offset, 3))
    data.extend(bytes(12))
    struct.pack_into(
        ">8I",
        data,
        8,
        secondary_offset,
        8,
        tertiary_offset,
        12,
        0,
        0,
        table_offset,
        0x80000018,
    )
    return bytes(data)


def model_payload_with_texture_references() -> bytes:
    data = bytearray(model_payload())
    display_offset = struct.unpack_from(">I", data, 0)[0]
    commands = data[display_offset:]
    commands[-8:-8] = b"".join(
        struct.pack(">II", command, argument)
        for command, argument in (
            (0xFD500000, 42),
            (0xFD100000, 0x0040002A),
            (0xFD100000, 0x08000110),
        )
    )
    struct.pack_into(">I", data, 4, len(commands))
    return bytes(data[:display_offset] + commands)


def model_payload_with_material_runs() -> bytes:
    data = bytearray(model_payload())
    display_offset = struct.unpack_from(">I", data, 0)[0]
    commands = b"".join(
        struct.pack(">II", command, argument)
        for command, argument in (
            (0xD7000000, 0xFFFFFFFF),
            (0x01003006, 0x01000000),
            (0xFC121824, 0x5531FEFF),
            (0xEF08AC3F, 0x00552230),
            (0xD7000002, 0xFFFFFFFF),
            (0xFD500000, 42),
            (0xF3000000, 0),
            (0xFD100000, 0x0080002A),
            (0xF0000000, 0),
            (0xF5400800, 0x00014050),
            (0xF2000000, 0x0007C07C),
            (0x05000204, 0),
            (0xD7000000, 0xFFFFFFFF),
            (0x05000204, 0),
            (0xDF000000, 0),
        )
    )
    struct.pack_into(">I", data, 4, len(commands))
    return bytes(data[:display_offset] + commands)


def character_model_payload() -> bytes:
    vertices = model_payload()[0x28 : 0x28 + 3 * 16]
    pointer_table_offset = 0x38 + len(vertices)
    display_offset = pointer_table_offset + 4
    commands = b"".join(
        struct.pack(">II", command, argument)
        for command, argument in (
            (0xD7000002, 0xFFFFFFFF),
            (0xDA380003, 0x03000000),
            (0x01003006, 0x01000038),
            (0xFD100000, 42),
            (0xE6000000, 0),
            (0xF3000000, 0x03FFF000),
            (0xE7000000, 0),
            (0xE6000000, 0),
            (0xFD100000, 0x0040002A),
            (0xF0000000, 0x063FC000),
            (0xE7000000, 0),
            (0xF5080800, 0x00094250),
            (0xF2002002, 0x0007E07E),
            (0x05000204, 0),
            (0xDF000000, 0),
        )
    )
    joint_offset = display_offset + len(commands)
    texture_descriptor_offset = joint_offset + 16
    auxiliary_offset = texture_descriptor_offset + 12
    header = struct.pack(
        ">14I",
        0,
        0,
        pointer_table_offset,
        4,
        joint_offset,
        16,
        texture_descriptor_offset,
        12,
        auxiliary_offset,
        8,
        0,
        0,
        0,
        0x80000000,
    )
    joint = struct.pack(">bBBB3f", -1, 0, 0, 0, 1.0, 2.0, 3.0)
    texture_descriptor = struct.pack(">IIHH", 42, 42, 32, 64)
    return (
        header
        + vertices
        + struct.pack(">I", display_offset)
        + commands
        + joint
        + texture_descriptor
        + bytes(8)
    )


class ModelAssetTests(unittest.TestCase):
    def test_parses_bank_01_character_geometry_and_bind_hierarchy(self):
        geometry, layout = model_assets.parse_character_model_geometry(
            character_model_payload()
        )
        self.assertEqual(3, len(geometry.vertices))
        self.assertEqual(((0, 1, 2),), geometry.faces)
        self.assertEqual(0, geometry.material_runs[0].matrix_index)
        self.assertEqual(1, geometry.material_runs[0].palette.mode)
        self.assertEqual(
            2,
            model_assets.texture_coordinate_state(geometry.material_runs[0])["format"],
        )
        self.assertEqual(
            (None, "character-indexed-material-runtime-unresolved"),
            model_assets.choose_preview_texture(geometry.material_runs[0], {}),
        )
        self.assertEqual(1, layout["joint_count"])
        self.assertEqual(-1, layout["joints"][0]["parent_matrix_index"])
        self.assertEqual([1.0, 2.0, 3.0], layout["joints"][0]["local_translation_f32"])
        self.assertEqual(1, layout["texture_descriptor_count"])
        self.assertEqual(42, layout["texture_descriptors"][0]["flat_index"])
        self.assertEqual(32, layout["texture_descriptors"][0]["width"])
        self.assertEqual(64, layout["texture_descriptors"][0]["height"])
        gltf_data, _ = model_assets.encode_gltf(
            0,
            0,
            geometry,
            bank_index=1,
            character_joints=tuple(layout["joints"]),
        )
        gltf = json.loads(gltf_data)
        self.assertEqual([1.0, 2.0, 3.0], gltf["nodes"][0]["translation"])
        self.assertEqual(0, gltf["nodes"][1]["mesh"])
        self.assertEqual(0, gltf["nodes"][1]["skin"])
        self.assertEqual([0], gltf["skins"][0]["joints"])
        primitive = gltf["meshes"][0]["primitives"][0]
        self.assertIn("JOINTS_0", primitive["attributes"])
        self.assertIn("WEIGHTS_0", primitive["attributes"])

    def test_rejects_character_texture_descriptor_pointer_slot_mismatch(self):
        payload = bytearray(character_model_payload())
        descriptor_offset = struct.unpack_from(">I", payload, 24)[0]
        struct.pack_into(">I", payload, descriptor_offset, 41)
        with self.assertRaisesRegex(ValueError, "pointer slot"):
            model_assets.parse_character_model_geometry(bytes(payload))

    def test_decodes_character_half_angle_pose_and_exports_rotation(self):
        descriptor = bytearray(16)
        descriptor[1] = 2
        struct.pack_into(">3H", descriptor, 10, 0x2000, 0, 0)
        rotations = model_assets.decode_character_animation_first_pose(
            bytes(descriptor), b""
        )
        self.assertEqual(1, len(rotations))
        self.assertAlmostEqual(2 ** -0.5, rotations[0][0], places=6)
        self.assertAlmostEqual(2 ** -0.5, rotations[0][3], places=6)

        geometry, layout = model_assets.parse_character_model_geometry(
            character_model_payload()
        )
        gltf_data, _ = model_assets.encode_gltf(
            0,
            0,
            geometry,
            bank_index=1,
            character_joints=tuple(layout["joints"]),
            character_rotations=rotations,
            character_pose_source="bank-02-test-pose",
        )
        gltf = json.loads(gltf_data)
        self.assertEqual(list(rotations[0]), gltf["nodes"][0]["rotation"])
        self.assertEqual("bank-02-test-pose", gltf["extras"]["previewPose"])

    def test_extracts_nested_asset_child(self):
        table = bytearray(0x10)
        struct.pack_into(">4I", table, 0, 0x10, 0, 0x10, 0x80000004)
        table.extend(b"DATA")
        self.assertEqual(b"DATA", model_assets.nested_asset_payload(bytes(table), 1))

    def test_parses_placement_records_and_zero_alignment(self):
        record = bytearray(model_assets.PLACEMENT_RECORD_SIZE)
        struct.pack_into(">3h", record, 0x00, 10, 20, 30)
        struct.pack_into(">3h", record, 0x06, 0, 0, 0)
        struct.pack_into(">I", record, 0x0C, 0)
        struct.pack_into(">I", record, 0x10, 51)
        struct.pack_into(">3f", record, 0x20, 1.0, 2.0, 0.5)
        records, padding = model_assets.parse_placement_records(
            bytes(record) + bytes(12), allow_alignment_padding=True
        )
        self.assertEqual((bytes(record),), records)
        self.assertEqual(bytes(12), padding)
        manifest = model_assets.placement_record_manifest(records[0], 3)
        self.assertEqual(51, manifest["model_index"])
        self.assertIsNone(manifest["dispatch_index"])
        self.assertEqual([10, 20, 30], manifest["position_s16_00"])
        self.assertEqual([0, 0, 0], manifest["rotation_degrees_s16_06"])
        self.assertEqual([1.0, 2.0, 0.5], manifest["scale_f32_20"])
        self.assertEqual(
            [
                1.0, 0.0, 0.0, 0.0,
                0.0, 2.0, 0.0, 0.0,
                0.0, 0.0, 0.5, 0.0,
                10.0, 20.0, 30.0, 1.0,
            ],
            model_assets.placement_transform_matrix(manifest),
        )

        with self.assertRaisesRegex(ValueError, "trailing bytes"):
            model_assets.parse_placement_records(
                bytes(record) + b"X", allow_alignment_padding=True
            )

    def test_placement_transform_uses_runtime_yzx_rotation_order(self):
        record = {
            "position_s16_00": [0, 0, 0],
            "rotation_degrees_s16_06": [0, 90, 0],
            "scale_f32_20": [1.0, 1.0, 1.0],
        }
        expected = [
            0.0, 0.0, -1.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            1.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 1.0,
        ]
        for actual, wanted in zip(
            model_assets.placement_transform_matrix(record), expected
        ):
            self.assertAlmostEqual(wanted, actual, places=6)

    def test_parses_contiguous_segment_table(self):
        data = bundle_payload()
        segments = model_assets.parse_model_bundle(data)
        self.assertEqual([8, 0, 16, 8], [segment.size for segment in segments])
        self.assertEqual(
            [False, False, False, True],
            [segment.final_flag for segment in segments],
        )

    def test_bundle_round_trip_is_byte_identical(self):
        data = bundle_payload((8, 16, 24, 0, 8))
        self.assertEqual(
            data,
            model_assets.encode_model_bundle(model_assets.parse_model_bundle(data)),
        )

    def test_rejects_gap_and_early_final_flag(self):
        data = bytearray(bundle_payload())
        struct.pack_into(">I", data, 8, 0x30)
        with self.assertRaisesRegex(ValueError, "contiguous"):
            model_assets.parse_model_bundle(bytes(data))

        data = bytearray(bundle_payload())
        struct.pack_into(">I", data, 4, 0x80000008)
        with self.assertRaisesRegex(ValueError, "final flag"):
            model_assets.parse_model_bundle(bytes(data))

        data = bytearray(bundle_payload())
        struct.pack_into(">I", data, 4, 0x10000008)
        with self.assertRaisesRegex(ValueError, "unsupported descriptor flags"):
            model_assets.parse_model_bundle(bytes(data))

    def test_rejects_trailing_or_unaligned_data(self):
        with self.assertRaisesRegex(ValueError, "consume"):
            model_assets.parse_model_bundle(bundle_payload() + bytes(8))

        data = bytearray(bundle_payload())
        struct.pack_into(">I", data, 4, 7)
        with self.assertRaisesRegex(ValueError, "aligned"):
            model_assets.parse_model_bundle(bytes(data))

    def test_parses_vertices_and_standard_triangle(self):
        geometry = model_assets.parse_model_geometry(model_payload())
        self.assertEqual(3, len(geometry.vertices))
        self.assertEqual(((0, 1, 2),), geometry.faces)
        self.assertEqual((10, 0, 0), (
            geometry.vertices[1].x,
            geometry.vertices[1].y,
            geometry.vertices[1].z,
        ))
        self.assertEqual((0, 255, 0, 255), geometry.vertices[1].color)
        self.assertIn(b"f 1 2 3\n", model_assets.encode_obj(4, 2, geometry))

    def test_decodes_conker_four_triangle_command(self):
        self.assertEqual(
            (0, 1, 2, 0, 3, 1, 4, 3, 0, 4, 5, 3),
            model_assets.packed_four_triangle_indices(0x12141060, 0xC0110061),
        )

    def test_records_runtime_segment_8_display_list(self):
        geometry = model_assets.parse_model_geometry(
            model_payload_with_segment_8_list()
        )
        self.assertEqual((0x110,), geometry.segment_8_display_list_offsets)

    def test_rejects_unproven_display_list_branch_address(self):
        data = bytearray(model_payload_with_segment_8_list())
        display_offset = struct.unpack_from(">I", data, 0)[0]
        struct.pack_into(">I", data, display_offset + 3 * 8 + 4, 0x07000110)
        with self.assertRaisesRegex(ValueError, "unsupported display-list branch"):
            model_assets.parse_model_geometry(bytes(data))

    def test_parses_auxiliary_regions_and_vertex_color_animation(self):
        geometry = model_assets.parse_model_geometry(
            model_payload_with_regions_and_color_animation()
        )
        self.assertEqual(
            model_assets.ModelRegion(offset=120, size=8),
            geometry.secondary_region,
        )
        self.assertEqual(
            model_assets.ModelRegion(offset=128, size=12),
            geometry.tertiary_region,
        )
        self.assertEqual(156, geometry.vertex_color_animation_offset)
        self.assertEqual(24, geometry.vertex_color_animation_table_size)
        self.assertEqual(
            (
                model_assets.VertexColorAnimationDescriptor(
                    color_data_offset=140,
                    vertex_index_offset=149,
                    vertex_count=3,
                    max_vertex_index=2,
                ),
            ),
            geometry.vertex_color_animation_descriptors,
        )

    def test_rejects_invalid_vertex_color_animation_reference(self):
        data = bytearray(model_payload_with_regions_and_color_animation())
        struct.pack_into(">H", data, 149, 3)
        with self.assertRaisesRegex(ValueError, "invalid vertex"):
            model_assets.parse_model_geometry(bytes(data))

    def test_rejects_vertex_color_animation_size_mismatch(self):
        data = bytearray(model_payload_with_regions_and_color_animation())
        struct.pack_into(">I", data, 36, 0x8000000C)
        with self.assertRaisesRegex(ValueError, "not terminated"):
            model_assets.parse_model_geometry(bytes(data))

    def test_rejects_auxiliary_region_overlapping_primary_list(self):
        data = bytearray(model_payload())
        display_offset, display_size = struct.unpack_from(">II", data, 0)
        struct.pack_into(">II", data, 8, display_offset, display_size)
        with self.assertRaisesRegex(ValueError, "overlaps"):
            model_assets.parse_model_geometry(bytes(data))

    def test_records_flat_and_runtime_segment_texture_references(self):
        geometry = model_assets.parse_model_geometry(
            model_payload_with_texture_references()
        )
        self.assertEqual(
            (
                model_assets.ModelTextureReference(
                    image_command=0xFD500000,
                    encoded_argument=42,
                    flat_index=42,
                    mode=0,
                ),
                model_assets.ModelTextureReference(
                    image_command=0xFD100000,
                    encoded_argument=0x0040002A,
                    flat_index=42,
                    mode=1,
                ),
            ),
            geometry.texture_references,
        )
        self.assertEqual(((8, 0x110),), geometry.runtime_segment_texture_addresses)

    def test_rejects_texture_reference_past_flat_archive(self):
        data = bytearray(model_payload_with_texture_references())
        display_offset = struct.unpack_from(">I", data, 0)[0]
        struct.pack_into(">I", data, display_offset + 3 * 8 + 4, 0x00001E52)
        with self.assertRaisesRegex(ValueError, "exceeds the flat archive"):
            model_assets.parse_model_geometry(bytes(data))

    def test_groups_faces_by_loaded_texture_and_palette_state(self):
        geometry = model_assets.parse_model_geometry(model_payload_with_material_runs())
        self.assertEqual(2, len(geometry.material_runs))
        textured, untextured = geometry.material_runs
        self.assertEqual((0, 1, True), (
            textured.first_face,
            textured.face_count,
            textured.texture_enabled,
        ))
        self.assertEqual(42, textured.pixel.flat_index)
        self.assertEqual(42, textured.palette.flat_index)
        self.assertEqual((1, 1, False), (
            untextured.first_face,
            untextured.face_count,
            untextured.texture_enabled,
        ))
        self.assertEqual((0xFC121824, 0x5531FEFF), textured.combine_mode)
        self.assertEqual((0xEF08AC3F, 0x00552230), textured.other_mode)
        self.assertIsNone(textured.runtime_render_state_offset)
        self.assertEqual(
            {
                "formula": "(A - B) * C + D",
                "cycles": [
                    {
                        "color": ["TEXEL0", "ENVIRONMENT", "SHADE", "PRIMITIVE"],
                        "alpha": ["TEXEL0", "ZERO", "SHADE", "ZERO"],
                    },
                    {
                        "color": ["TEXEL0", "ENVIRONMENT", "SHADE", "PRIMITIVE"],
                        "alpha": ["TEXEL0", "ZERO", "SHADE", "ZERO"],
                    },
                ],
                "inputs": ["ENVIRONMENT", "PRIMITIVE", "SHADE", "TEXEL0"],
            },
            model_assets.decode_combine_mode(textured.combine_mode),
        )
        encoded = model_assets.encode_obj(4, 2, geometry)
        self.assertIn(b"mtllib 0004-02.mtl\n", encoded)
        self.assertIn(b"g material_run_0000\n", encoded)
        self.assertIn(b"usemtl flat_0042_mode_0_cmd_fd500000", encoded)
        self.assertIn(b"vt 0 1\n", encoded)
        self.assertIn(b"f 1/1 2/2 3/3\n", encoded)
        self.assertEqual(3, model_assets.texture_coordinate_count(geometry))
        material = model_assets.encode_mtl(4, 2, geometry)
        self.assertIn(b"newmtl flat_0042_mode_0_cmd_fd500000", material)
        mapped = model_assets.encode_mtl(
            4,
            2,
            geometry,
            {model_assets.material_name(textured): "../textures/0042.png"},
        )
        self.assertIn(b"map_Kd ../textures/0042.png\n", mapped)
        gltf_data, binary = model_assets.encode_gltf(
            4,
            2,
            geometry,
            {model_assets.material_name(textured): "../textures/0042.png"},
        )
        gltf = json.loads(gltf_data)
        self.assertEqual("2.0", gltf["asset"]["version"])
        self.assertEqual(len(binary), gltf["buffers"][0]["byteLength"])
        self.assertIn("COLOR_0", gltf["meshes"][0]["primitives"][0]["attributes"])
        self.assertIn(
            "TEXCOORD_0", gltf["meshes"][0]["primitives"][0]["attributes"]
        )
        self.assertEqual("../textures/0042.png", gltf["images"][0]["uri"])
        self.assertEqual(
            {"wrapS": model_assets.GLTF_REPEAT, "wrapT": model_assets.GLTF_REPEAT},
            {
                key: gltf["samplers"][0][key]
                for key in ("wrapS", "wrapT")
            },
        )
        self.assertEqual(
            {"s": "repeat", "t": "repeat"},
            gltf["materials"][0]["extras"]["textureAddressMode"]["n64"],
        )
        placement = {
            "index": 7,
            "sha1": "a" * 40,
            "position_s16_00": [10, 20, 30],
            "rotation_degrees_s16_06": [0, 0, 0],
            "scale_f32_20": [1.0, 1.0, 1.0],
            "model_index": 51,
        }
        scene_data, scene_binary = model_assets.encode_placement_scene_gltf(
            2, [placement, placement], {51: (gltf, binary)}
        )
        scene = json.loads(scene_data)
        self.assertEqual(2, len(scene["nodes"]))
        self.assertEqual(gltf["samplers"], scene["samplers"])
        self.assertEqual(1, len(scene["meshes"]))
        self.assertEqual([10.0, 20.0, 30.0], scene["nodes"][0]["matrix"][12:15])
        self.assertEqual(len(scene_binary), scene["buffers"][0]["byteLength"])
        self.assertEqual("YZX", scene["extras"]["rotationOrder"])

    def test_preview_texture_requires_matching_format_and_prefers_dimensions(self):
        geometry = model_assets.parse_model_geometry(model_payload_with_material_runs())
        run = geometry.material_runs[0]
        broad = model_assets.PreviewTexture(
            family="us",
            source=Path("broad.png"),
            flat_index=42,
            format=2,
            size=0,
            width=64,
            height=64,
            sha1="b" * 40,
        )
        exact = model_assets.PreviewTexture(
            family="us",
            source=Path("exact.png"),
            flat_index=42,
            format=2,
            size=0,
            width=32,
            height=32,
            sha1="e" * 40,
        )
        texture, status = model_assets.choose_preview_texture(
            run, {(42, 2, 0): (broad, exact)}
        )
        self.assertEqual("proven-texture", status)
        self.assertEqual(exact, texture)
        self.assertEqual(
            (None, "no-proven-texture"),
            model_assets.choose_preview_texture(run, {(42, 2, 1): (exact,)}),
        )
        native = replace(
            exact,
            family="us-native-proven",
            source=Path("native.png"),
        )
        self.assertEqual(
            (None, "native-material-combiner-unresolved"),
            model_assets.choose_preview_texture(run, {(42, 2, 0): (native,)}),
        )
        self.assertEqual(
            (exact, "proven-texture"),
            model_assets.choose_preview_texture(
                run, {(42, 2, 0): (native, exact)}
            ),
        )
        ci8_run = replace(
            run,
            palette=replace(run.palette, mode=1),
            render_tile=(0xF5480800, run.render_tile[1]),
        )
        self.assertEqual(
            (None, "mode-one-ci8-palette-runtime-unresolved"),
            model_assets.choose_preview_texture(ci8_run, {(42, 2, 1): (exact,)}),
        )

    def test_translates_n64_texture_address_modes_to_gltf(self):
        geometry = model_assets.parse_model_geometry(model_payload_with_material_runs())
        run = geometry.material_runs[0]
        command, argument = run.render_tile
        address_mode = model_assets.texture_address_mode(
            replace(
                run,
                render_tile=(command, argument | (2 << 8) | (1 << 18)),
            )
        )
        self.assertEqual(
            {"s": "clamp", "t": "mirror-repeat"}, address_mode["n64"]
        )
        self.assertEqual(
            {
                "wrapS": model_assets.GLTF_CLAMP_TO_EDGE,
                "wrapT": model_assets.GLTF_MIRRORED_REPEAT,
            },
            address_mode["gltf"],
        )

    def test_obj_name_records_selected_model_bank(self):
        geometry = model_assets.parse_model_geometry(model_payload())
        self.assertIn(
            b"o bank03_0004_02\n",
            model_assets.encode_obj(4, 2, geometry, bank_index=3),
        )

    def test_decodes_runtime_segment_8_render_state_tables(self):
        data_vram = 0x80082B20
        size = (
            model_assets.RUNTIME_RENDER_STATE_TABLE_BASES[-1]
            - data_vram
            + 0x180
        )
        data = bytearray(size)
        for table_index, base in enumerate(
            model_assets.RUNTIME_RENDER_STATE_TABLE_BASES
        ):
            for entry_index in range(24):
                struct.pack_into(
                    ">4I",
                    data,
                    base - data_vram + entry_index * 0x10,
                    0xEF000000 | table_index,
                    entry_index,
                    0xDF000000,
                    0,
                )
        tables = model_assets.parse_runtime_render_state_tables(bytes(data), data_vram)
        self.assertEqual(11, len(tables))
        self.assertEqual(24, tables[0]["entry_count"])
        self.assertEqual(
            ["0xEF000000", "0x00000004"],
            tables[0]["entries"][4]["other_mode"],
        )
        data[model_assets.RUNTIME_RENDER_STATE_TABLE_BASES[0] - data_vram] = 0
        with self.assertRaisesRegex(ValueError, "OtherMode plus EndDL"):
            model_assets.parse_runtime_render_state_tables(bytes(data), data_vram)


if __name__ == "__main__":
    unittest.main()
