from __future__ import annotations

import json
import math
import struct
import tempfile
import unittest
from dataclasses import replace
from pathlib import Path
from unittest import mock

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


def model_payload_with_custom_normals() -> bytes:
    data = bytearray(model_payload())
    display_offset = struct.unpack_from(">I", data, 0)[0]
    commands = data[display_offset:]
    commands[8:8] = struct.pack(">II", 0xDC38000E, 0)
    normal_offset = display_offset + len(commands) + 8
    struct.pack_into(">I", commands, 12, normal_offset)
    struct.pack_into(">I", data, 4, len(commands))
    data = data[:display_offset] + commands
    data.extend(bytes(8))
    data.extend(struct.pack(">6b", 127, 0, 0, 127, -127, 0))
    return bytes(data)


def character_model_payload() -> bytes:
    vertices = model_payload()[0x28 : 0x28 + 3 * 16]
    pointer_table_offset = 0x38 + len(vertices)
    display_offset = pointer_table_offset + 4
    commands = b"".join(
        struct.pack(">II", command, argument)
        for command, argument in (
            (model_assets.CHARACTER_CUSTOM_MOVEMEM_COMMAND, 0),
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
    procedural_joint_offset = auxiliary_offset + 8
    commands = bytearray(commands)
    struct.pack_into(">I", commands, 4, auxiliary_offset)
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
        procedural_joint_offset,
        0x80000002,
    )
    joint = struct.pack(">bBBB3f", -1, 0, 0, 0, 1.0, 2.0, 3.0)
    texture_descriptor = struct.pack(">IIHH", 42, 42, 32, 64)
    return (
        header
        + vertices
        + struct.pack(">I", display_offset)
        + bytes(commands)
        + joint
        + texture_descriptor
        + bytes((127, 0, 0, 127, 129, 0, 0, 0))
        + bytes((0, 0xFF))
    )


class ModelAssetTests(unittest.TestCase):
    def test_parses_generic_cbfd_custom_normal_stream(self):
        geometry = model_assets.parse_model_geometry(
            model_payload_with_custom_normals()
        )

        self.assertEqual(
            (((127, 0, 0), (0, 127, 0), (-127, 0, 0)),),
            geometry.face_normal_bytes,
        )
        gltf_data, _ = model_assets.encode_gltf(0, 0, geometry, bank_index=4)
        primitive = json.loads(gltf_data)["meshes"][0]["primitives"][0]
        self.assertIn("NORMAL", primitive["attributes"])

    def test_parses_bank_01_character_geometry_and_bind_hierarchy(self):
        payload = character_model_payload()
        geometry, layout = model_assets.parse_character_model_geometry(payload)
        self.assertEqual(3, len(geometry.vertices))
        self.assertEqual(((0, 1, 2),), geometry.faces)
        pointer_table_offset = struct.unpack_from(">I", payload, 8)[0]
        display_offset = struct.unpack_from(">I", payload, pointer_table_offset)[0]
        self.assertEqual((display_offset + 14 * 8,), geometry.face_command_offsets)
        self.assertEqual((0x05,), geometry.face_command_opcodes)
        self.assertEqual(0, geometry.material_runs[0].matrix_index)
        self.assertEqual(
            [0, None], layout["procedural_animation_joint_indices"]
        )
        self.assertEqual(
            "func_1503DA3C", layout["runtime_evidence"]["procedural_joint_lookup"]
        )
        self.assertEqual(1, geometry.material_runs[0].palette.mode)
        self.assertEqual(
            2,
            model_assets.texture_coordinate_state(geometry.material_runs[0])["format"],
        )
        self.assertEqual(
            (None, "character-indexed-material-runtime-unresolved"),
            model_assets.choose_preview_texture(geometry.material_runs[0], {}),
        )
        character_payload = bytes(range(256)) * 6 + bytes.fromhex("0001") * 256
        runtime_texture, runtime_status = model_assets.choose_preview_texture(
            geometry.material_runs[0], {}, {42: character_payload}
        )
        self.assertEqual("runtime-composed-character-texture", runtime_status)
        self.assertEqual("us-character-runtime-composed", runtime_texture.family)
        self.assertEqual((32, 32), (runtime_texture.width, runtime_texture.height))
        self.assertEqual(0, runtime_texture.pixel_byte_offset)
        self.assertEqual(0x600, runtime_texture.palette_byte_offset)
        self.assertTrue(runtime_texture.png_data.startswith(b"\x89PNG\r\n\x1a\n"))
        self.assertEqual(
            (None, "character-indexed-mipmap-state-unresolved"),
            model_assets.choose_preview_texture(
                replace(
                    geometry.material_runs[0],
                    combine_mode=(0xFC26A080, 0x151492FF),
                ),
                {},
                {42: character_payload},
            ),
        )
        self.assertEqual(
            (None, "character-indexed-payload-span-unresolved"),
            model_assets.choose_preview_texture(
                geometry.material_runs[0], {}, {42: bytes(0x3FF)}
            ),
        )
        overlapping_payload = bytes(768) + bytes.fromhex("0001") * 256
        self.assertEqual(
            (None, "character-indexed-pixel-palette-overlap-unresolved"),
            model_assets.choose_preview_texture(
                geometry.material_runs[0], {}, {42: overlapping_payload}
            ),
        )
        self.assertEqual(1, layout["joint_count"])
        self.assertEqual(-1, layout["joints"][0]["parent_matrix_index"])
        self.assertEqual([1.0, 2.0, 3.0], layout["joints"][0]["bind_pivot_f32"])
        self.assertEqual(1, layout["texture_descriptor_count"])
        self.assertEqual(42, layout["texture_descriptors"][0]["flat_index"])
        self.assertEqual(32, layout["texture_descriptors"][0]["width"])
        self.assertEqual(64, layout["texture_descriptors"][0]["height"])
        self.assertEqual(1, layout["custom_movemem_command_count"])
        self.assertEqual(
            (((127, 0, 0), (0, 127, 0), (-127, 0, 0)),),
            geometry.face_normal_bytes,
        )
        auxiliary = layout["sections"][4]
        self.assertEqual(
            {
                "display_list_offset": layout["display_list_offset"],
                "command": "0xDC38000E",
                "source_offset": auxiliary["offset"],
                "relative_to_auxiliary": 0,
                "source_location": "auxiliary-region",
            },
            layout["custom_movemem_commands"][0],
        )
        gltf_data, gltf_binary = model_assets.encode_gltf(
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
        self.assertIn("inverseBindMatrices", gltf["skins"][0])
        primitive = gltf["meshes"][0]["primitives"][0]
        self.assertIn("JOINTS_0", primitive["attributes"])
        self.assertIn("WEIGHTS_0", primitive["attributes"])
        self.assertIn("NORMAL", primitive["attributes"])
        position_accessor = gltf["accessors"][primitive["attributes"]["POSITION"]]
        position_view = gltf["bufferViews"][position_accessor["bufferView"]]
        self.assertEqual(
            (1.0, 2.0, 3.0),
            struct.unpack_from("<3f", gltf_binary, position_view.get("byteOffset", 0)),
        )
        normal_accessor = gltf["accessors"][primitive["attributes"]["NORMAL"]]
        normal_view = gltf["bufferViews"][normal_accessor["bufferView"]]
        self.assertEqual(
            (1.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0, 0.0),
            struct.unpack_from(
                "<9f", gltf_binary, normal_view.get("byteOffset", 0)
            ),
        )
        bind_data, _ = model_assets.encode_gltf(
            0,
            0,
            geometry,
            bank_index=1,
            character_joints=tuple(layout["joints"]),
            output_stem="0000-00-bind",
        )
        bind_gltf = json.loads(bind_data)
        self.assertEqual("0000-00-bind.bin", bind_gltf["buffers"][0]["uri"])
        self.assertNotIn("animations", bind_gltf)
        self.assertEqual(
            "joint-local-source-positions-baked-through-accumulated-global-pivots",
            bind_gltf["extras"]["characterVertexSpace"],
        )
        self.assertEqual(
            "emulator-validated-signed-xy-normal-stream-vertex-flag-signed-z",
            bind_gltf["extras"]["characterAuxiliaryData"],
        )
        self.assertEqual(
            "runtime-dynamic-not-baked",
            bind_gltf["extras"]["characterColorState"]["status"],
        )
        self.assertEqual(
            "D_800D9B68",
            bind_gltf["materials"][0]["extras"]["characterColorState"][
                "primitive_rgb_storage"
            ],
        )

    def test_accumulates_parent_relative_character_bind_translations(self):
        geometry, layout = model_assets.parse_character_model_geometry(
            character_model_payload()
        )
        root = layout["joints"][0]
        child = {
            "record_index": 1,
            "parent_matrix_index": 0,
            "matrix_index": 1,
            "animation_index": 1,
            "flags": 0,
            "bind_pivot_f32": [4.0, 8.0, 12.0],
        }
        gltf_data, binary = model_assets.encode_gltf(
            0,
            0,
            geometry,
            bank_index=1,
            character_joints=(root, child),
        )
        gltf = json.loads(gltf_data)
        self.assertEqual([1.0, 2.0, 3.0], gltf["nodes"][0]["translation"])
        self.assertEqual([4.0, 8.0, 12.0], gltf["nodes"][1]["translation"])
        accessor = gltf["accessors"][gltf["skins"][0]["inverseBindMatrices"]]
        view = gltf["bufferViews"][accessor["bufferView"]]
        matrices = struct.unpack_from("<32f", binary, view.get("byteOffset", 0))
        self.assertEqual((-1.0, -2.0, -3.0), matrices[12:15])
        self.assertEqual((-5.0, -10.0, -15.0), matrices[28:31])

    def test_converts_absolute_pivot_animation_to_parent_relative_translation(self):
        root = {
            "parent_matrix_index": -1,
            "matrix_index": 0,
            "animation_index": 0,
        }
        child = {
            "parent_matrix_index": 0,
            "matrix_index": 1,
            "animation_index": 1,
        }
        frame = model_assets.CharacterAnimationFrame(
            root_translation=(1024, 0, -2048),
            joint_translation_deltas=((16, 32, 48), None),
            encoded_rotations=((0, 0, 0), (0, 0, 0)),
            rotations=((0.0, 0.0, 0.0, 1.0),) * 2,
            scale_channels=(None,) * 6,
            trailing_data=b"",
        )
        self.assertEqual(
            (2.0, 4.0, 4.0),
            model_assets.character_local_animation_translation(
                frame, root, [0.0, 2.0, 3.0]
            ),
        )
        self.assertEqual(
            (4.0, 6.0, 8.0),
            model_assets.character_local_animation_translation(
                frame, child, [4.0, 6.0, 8.0]
            ),
        )

    def test_rejects_character_texture_descriptor_pointer_slot_mismatch(self):
        payload = bytearray(character_model_payload())
        descriptor_offset = struct.unpack_from(">I", payload, 24)[0]
        struct.pack_into(">I", payload, descriptor_offset, 41)
        with self.assertRaisesRegex(ValueError, "pointer slot"):
            model_assets.parse_character_model_geometry(bytes(payload))

    def test_rejects_character_movemem_outside_auxiliary_region(self):
        payload = bytearray(character_model_payload())
        pointer_table_offset = struct.unpack_from(">I", payload, 8)[0]
        display_offset = struct.unpack_from(">I", payload, pointer_table_offset)[0]
        struct.pack_into(">I", payload, display_offset + 4, len(payload) + 32)
        with self.assertRaisesRegex(ValueError, "does not reference its auxiliary"):
            model_assets.parse_character_model_geometry(bytes(payload))

    def test_decodes_runtime_character_euler_pose_and_exports_rotation(self):
        descriptor = bytearray(16)
        descriptor[1] = 2
        struct.pack_into(">3H", descriptor, 10, 0x2000, 0, 0)
        rotations = model_assets.decode_character_animation_first_pose(
            bytes(descriptor), b""
        )
        self.assertEqual(1, len(rotations))
        self.assertAlmostEqual(math.sin(math.pi / 8), rotations[0][0], places=6)
        self.assertAlmostEqual(math.cos(math.pi / 8), rotations[0][3], places=6)

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

    def test_ignores_animation_descriptor_flag_bit_in_quaternion_angle(self):
        quaternion = model_assets.character_rotation_quaternion((0x10, 0, 0))
        self.assertEqual((0.0, 0.0, 0.0, 1.0), quaternion)

    def test_conker_runtime_trace_rotation_matches_pair_25_frame_0(self):
        quaternion = model_assets.character_rotation_quaternion((0xF6E0, 0, 0))
        x, _, _, w = quaternion
        self.assertAlmostEqual(0.97502535, 1.0 - 2.0 * x * x, places=6)
        self.assertAlmostEqual(0.22209363, -2.0 * x * w, places=6)
        self.assertAlmostEqual(-0.22209363, 2.0 * x * w, places=6)

    def test_decodes_complete_fixed_stride_character_timeline(self):
        descriptor = bytearray(16)
        descriptor[1] = 2
        descriptor[3] = 2
        descriptor[5] = 1
        struct.pack_into(">3H", descriptor, 10, 1, 1, 1)
        layout = model_assets.parse_character_animation_descriptor(bytes(descriptor))
        self.assertEqual(1, layout.joint_count)
        self.assertEqual(3, layout.frame_bit_size)
        self.assertEqual(1, layout.decoded_frame_byte_size)
        self.assertEqual(1, layout.frame_byte_size)

        frames = model_assets.decode_character_animation_timeline(
            bytes(descriptor), bytes((0, 0xE0))
        )
        self.assertEqual(2, len(frames))
        self.assertEqual((0, 0, 0), frames[0].root_translation)
        self.assertEqual(((0, 0, 0),), frames[0].encoded_rotations)
        self.assertEqual(((32, 32, 32),), frames[1].encoded_rotations)

    def test_uses_duration_and_keyframe_spacing_for_character_frame_count(self):
        descriptor = bytearray(16)
        descriptor[1] = 2
        descriptor[3] = 4
        descriptor[5] = 1
        descriptor[8] = 3
        struct.pack_into(">3H", descriptor, 10, 1, 1, 1)
        layout = model_assets.parse_character_animation_descriptor(bytes(descriptor))
        frame_count, trailing, duration_status = (
            model_assets.character_animation_frame_span(
                bytes(descriptor), layout, bytes(4)
            )
        )
        self.assertEqual(2, frame_count)
        self.assertEqual(bytes(2), trailing)
        self.assertEqual(
            "descriptor-duration-and-keyframe-spacing", duration_status
        )
        self.assertEqual(
            2,
            len(
                model_assets.decode_character_animation_timeline(
                    bytes(descriptor), bytes(4)
                )
            ),
        )

    def test_resolves_runtime_duration_before_counting_source_frames(self):
        descriptor = bytearray(16)
        descriptor[1] = 2
        descriptor[3] = 0xFF
        descriptor[5] = 1
        descriptor[8] = 3
        struct.pack_into(">3H", descriptor, 10, 1, 1, 1)
        layout = model_assets.parse_character_animation_descriptor(bytes(descriptor))
        frame_count, trailing, duration_status = (
            model_assets.character_animation_frame_span(
                bytes(descriptor),
                layout,
                bytes(80),
                runtime_duration=0xFF,
                runtime_duration_status="runtime-default-u8-duration",
            )
        )
        self.assertEqual(65, frame_count)
        self.assertEqual(bytes(15), trailing)
        self.assertEqual("runtime-default-u8-duration", duration_status)

    def test_decodes_logical_animation_routes_to_even_segment_pairs(self):
        data = bytearray(0x40)
        struct.pack_into(">HHI", data, 0x10, 0x32, 7, 0x30)
        struct.pack_into(">HHI", data, 0x18, 0x04, 0, 0)
        struct.pack_into(">HHI", data, 0x20, 0x03E7, 0, 0)
        routes = model_assets.parse_character_animation_route_table(bytes(data))
        self.assertEqual(2, len(routes))
        self.assertEqual(0, routes[0]["logical_animation_index"])
        self.assertEqual(25, routes[0]["pair_index"])
        self.assertEqual(7, routes[0]["runtime_table_index"])
        self.assertEqual(0x30, routes[0]["auxiliary_offset"])

    def test_resolves_character_0x92_duration_from_logical_animation_id(self):
        game_data_vram = model_assets.CHARACTER_ANIMATION_DURATION_TABLE_ADDRESS
        game_data = bytearray(64)
        struct.pack_into(">H", game_data, 20 * 2, 533)
        self.assertEqual(
            (533, "runtime-character-0x92-duration-table"),
            model_assets.resolve_character_animation_runtime_duration(
                0x92, (20,), bytes(game_data), game_data_vram
            ),
        )

    def test_decodes_masked_joint_translation_before_packed_channels(self):
        descriptor = bytearray(18)
        descriptor[1] = 2
        descriptor[5] = 6
        descriptor[7] = 0x80
        struct.pack_into(">H", descriptor, 10, 0x8000)
        struct.pack_into(">3H", descriptor, 12, 0, 0, 0)
        frame = model_assets.decode_character_animation_frame(
            bytes(descriptor), struct.pack(">3h", -10, 20, -30)
        )
        self.assertEqual(((-10, 20, -30),), frame.joint_translation_deltas)
        self.assertEqual(((0, 0, 0),), frame.encoded_rotations)
        self.assertEqual(b"", frame.trailing_data)

    def test_decodes_and_exports_runtime_joint_scale_channels(self):
        descriptor = bytearray(18)
        descriptor[1] = 2
        descriptor[3] = 1
        descriptor[5] = 1
        struct.pack_into(">4H", descriptor, 10, 0x0010, 0x4001, 0, 0)
        frame = model_assets.decode_character_animation_frame(
            bytes(descriptor), b"\x80"
        )
        self.assertEqual(((0, 0, 0),), frame.encoded_rotations)
        self.assertEqual((0x4020, None, None), frame.scale_channels)

        geometry, character_layout = model_assets.parse_character_model_geometry(
            character_model_payload()
        )
        clip = model_assets.CharacterAnimationClip(
            pair_index=0,
            frames=(frame,),
            frame_byte_size=1,
            bitstream_padding_size=0,
            descriptor_runtime_zero_fill_size=0,
            duration_ticks=1,
        )
        gltf_data, binary = model_assets.encode_gltf(
            0,
            0,
            geometry,
            bank_index=1,
            character_joints=tuple(character_layout["joints"]),
            character_animation_clips=(clip,),
        )
        gltf = json.loads(gltf_data)
        scale_channel = next(
            channel
            for channel in gltf["animations"][0]["channels"]
            if channel["target"]["path"] == "scale"
        )
        sampler = gltf["animations"][0]["samplers"][scale_channel["sampler"]]
        accessor = gltf["accessors"][sampler["output"]]
        view = gltf["bufferViews"][accessor["bufferView"]]
        self.assertEqual(
            (float(0x4020) / 16384.0, 1.0, 1.0),
            struct.unpack_from("<3f", binary, view.get("byteOffset", 0)),
        )

    def test_uses_declared_character_frame_stride_and_preserves_tail(self):
        descriptor = bytearray(16)
        descriptor[1] = 2
        descriptor[3] = 2
        descriptor[5] = 3
        struct.pack_into(">3H", descriptor, 10, 1, 1, 1)
        layout = model_assets.parse_character_animation_descriptor(bytes(descriptor))
        self.assertEqual(1, layout.decoded_frame_byte_size)
        self.assertEqual(3, layout.frame_byte_size)
        self.assertEqual(2, layout.frame_trailing_size)

        frames = model_assets.decode_character_animation_timeline(
            bytes(descriptor), bytes((0xE0, 0x12, 0x34, 0, 0x56, 0x78))
        )
        self.assertEqual(2, len(frames))
        self.assertEqual(((32, 32, 32),), frames[0].encoded_rotations)
        self.assertEqual(b"\x12\x34", frames[0].trailing_data)
        self.assertEqual(((0, 0, 0),), frames[1].encoded_rotations)
        self.assertEqual(b"\x56\x78", frames[1].trailing_data)

    def test_runtime_descriptor_zero_fill_is_explicit_and_bounded(self):
        descriptor = bytearray(16)
        descriptor[1] = 2
        descriptor[5] = 1
        with self.assertRaisesRegex(ValueError, "rotation table is truncated"):
            model_assets.parse_character_animation_descriptor(bytes(descriptor[:15]))
        layout = model_assets.parse_character_animation_descriptor(
            bytes(descriptor[:15]), runtime_zero_fill_limit=1
        )
        self.assertEqual(1, layout.descriptor_runtime_zero_fill_size)

    def test_exports_character_rotation_and_masked_translation_animation(self):
        descriptor = bytearray(18)
        descriptor[1] = 2
        descriptor[3] = 2
        descriptor[5] = 7
        descriptor[6] = 0x10
        descriptor[7] = 0x80
        struct.pack_into(">H", descriptor, 10, 0x8000)
        struct.pack_into(">3H", descriptor, 12, 0, 0, 0)
        bitstream = struct.pack(">3hB3hB", 16, -32, 48, 0, 32, 0, -16, 0x80)
        frames = model_assets.decode_character_animation_timeline(
            bytes(descriptor), bitstream
        )
        clip = model_assets.CharacterAnimationClip(
            pair_index=4,
            frames=frames,
            frame_byte_size=7,
            bitstream_padding_size=0,
            descriptor_runtime_zero_fill_size=0,
            duration_ticks=4,
            keyframe_step=4,
        )
        self.assertEqual(
            (0.0, 0.1), model_assets.character_animation_preview_times(clip)
        )
        geometry, character_layout = model_assets.parse_character_model_geometry(
            character_model_payload()
        )
        gltf_data, _ = model_assets.encode_gltf(
            0,
            0,
            geometry,
            bank_index=1,
            character_joints=tuple(character_layout["joints"]),
            character_animation_clips=(clip,),
        )
        gltf = json.loads(gltf_data)
        self.assertEqual(1, len(gltf["animations"]))
        animation = gltf["animations"][0]
        self.assertEqual("bank02_entry_0000_pair_0004", animation["name"])
        self.assertEqual(2, len(animation["channels"]))
        self.assertEqual(
            {"rotation", "translation"},
            {channel["target"]["path"] for channel in animation["channels"]},
        )
        self.assertEqual(
            "runtime-animation-clock-proven-30-hz",
            animation["extras"]["timingStatus"],
        )
        self.assertEqual(30.0, animation["extras"]["runtimeFramesPerSecond"])
        self.assertEqual(
            "applied-to-root-node-runtime-scale-one-over-1024",
            animation["extras"]["rootTranslationStatus"],
        )

    def test_accepts_animation_descriptors_with_unused_trailing_channels(self):
        descriptor = bytearray(22)
        descriptor[1] = 3
        descriptor[3] = 1
        descriptor[5] = 1
        descriptor[6] = 0x10
        manifest = {
            "entries": [
                {
                    "bank_entry": 0,
                    "clips": [
                        {
                            "pair_index": 0,
                            "descriptor_segment_index": 0,
                            "bitstream_segment_index": 1,
                            "timeline_status": "runtime-frame-layout-proven",
                            "joint_count": 2,
                            "frame_count": 1,
                            "frame_byte_size": 1,
                            "bitstream_padding_size": 0,
                            "descriptor_runtime_zero_fill_size": 0,
                        }
                    ],
                }
            ]
        }
        files = {
            "animations/bank-02/segments/0000-0000.bin": bytes(descriptor),
            "animations/bank-02/segments/0000-0001.bin": b"\0",
        }
        clips, incompatible = model_assets.character_animation_clips_for_model(
            0, 1, manifest, files
        )
        self.assertEqual(1, len(clips))
        self.assertEqual(0, incompatible)
        self.assertEqual(2, len(clips[0].frames[0].rotations))

    def test_rejects_nonpadding_character_timeline_remainder(self):
        descriptor = bytearray(16)
        descriptor[1] = 2
        descriptor[3] = 1
        descriptor[5] = 2
        struct.pack_into(">3H", descriptor, 10, 3, 3, 3)
        with self.assertRaisesRegex(ValueError, "unresolved trailing data"):
            model_assets.decode_character_animation_timeline(
                bytes(descriptor), bytes((0, 0, 0x80))
            )

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
        self.assertTrue(manifest["collision_included"])
        record[0x32] = 0x20
        self.assertFalse(
            model_assets.placement_record_manifest(bytes(record), 3)[
                "collision_included"
            ]
        )
        record[0x32] = 0
        self.assertEqual(
            [
                1.0, 0.0, 0.0, 0.0,
                0.0, 2.0, 0.0, 0.0,
                0.0, 0.0, 0.5, 0.0,
                10.0, 20.0, 30.0, 1.0,
            ],
            model_assets.placement_transform_matrix(manifest),
        )

        struct.pack_into(">I", record, 0x0C, 2)
        dispatched = model_assets.placement_record_manifest(bytes(record), 4)
        self.assertIsNone(dispatched["model_index"])
        self.assertEqual(51, dispatched["dispatch_index"])

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
        self.assertEqual((0x68,), geometry.face_command_offsets)
        self.assertEqual((0x05,), geometry.face_command_opcodes)
        self.assertEqual((10, 0, 0), (
            geometry.vertices[1].x,
            geometry.vertices[1].y,
            geometry.vertices[1].z,
        ))
        self.assertEqual((0, 255, 0, 255), geometry.vertices[1].color)
        self.assertIn(b"f 1 2 3\n", model_assets.encode_obj(4, 2, geometry))

    def test_validates_and_renders_texture_independent_model_strip(self):
        geometry = model_assets.parse_model_geometry(model_payload())
        validation = model_assets.validate_model_geometry(geometry)
        self.assertEqual("accepted", validation["status"])
        self.assertEqual([10.0, 10.0, 0.0], validation["bounds"]["extent"])
        self.assertEqual(1, validation["connected_component_count"])
        self.assertEqual(0, validation["zero_area_face_count"])
        png = model_assets.render_validation_strip(geometry, view_size=32)
        self.assertTrue(png.startswith(b"\x89PNG\r\n\x1a\n"))
        self.assertEqual((96, 32), struct.unpack_from(">II", png, 16))
        self.assertEqual(png, model_assets.render_validation_strip(geometry, view_size=32))

    def test_validation_records_zero_area_and_duplicate_triangles_for_review(self):
        geometry = model_assets.parse_model_geometry(model_payload())
        repeated = replace(
            geometry,
            faces=((0, 1, 1), (0, 1, 1)),
            material_runs=(replace(geometry.material_runs[0], face_count=2),),
            face_command_offsets=(0x68, 0x68),
            face_command_opcodes=(0x05, 0x05),
        )
        validation = model_assets.validate_model_geometry(repeated)
        self.assertEqual("review", validation["status"])
        self.assertEqual(2, validation["zero_area_face_count"])
        self.assertEqual(
            {"repeated-vertex-index": 2}, validation["zero_area_kind_counts"]
        )
        self.assertEqual({"0x05": 2}, validation["zero_area_opcode_counts"])
        self.assertEqual(1, validation["duplicate_face_count"])

    def test_omits_zero_area_faces_from_preview_and_preserves_provenance(self):
        geometry = model_assets.parse_model_geometry(model_payload())
        geometry = replace(
            geometry,
            faces=((0, 1, 1), (0, 1, 2)),
            material_runs=(replace(geometry.material_runs[0], face_count=2),),
            face_command_offsets=(0x68, 0x70),
            face_command_opcodes=(0x05, 0x06),
        )
        preview, omitted, omitted_by_run = (
            model_assets.omit_zero_area_preview_faces(geometry)
        )
        self.assertEqual((0,), omitted)
        self.assertEqual((1,), omitted_by_run)
        self.assertEqual(((0, 1, 2),), preview.faces)
        self.assertEqual((0x70,), preview.face_command_offsets)
        self.assertEqual((0x06,), preview.face_command_opcodes)
        self.assertEqual(0, preview.material_runs[0].first_face)
        self.assertEqual(1, preview.material_runs[0].face_count)
        self.assertEqual(
            {
                "face_index": 0,
                "source_indices": [0, 1, 1],
                "kind": "repeated-vertex-index",
                "display_list_offset": "0x68",
                "triangle_opcode": "0x05",
            },
            model_assets.zero_area_face_record(geometry, 0),
        )

    def test_validation_rejects_absent_character_joint_assignment(self):
        geometry, layout = model_assets.parse_character_model_geometry(
            character_model_payload()
        )
        invalid = replace(
            geometry,
            material_runs=(replace(geometry.material_runs[0], matrix_index=7),),
        )
        validation = model_assets.validate_model_geometry(
            invalid, tuple(layout["joints"])
        )
        self.assertEqual("rejected", validation["status"])
        self.assertEqual([7], validation["invalid_joint_assignments"])

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

    def test_exports_primary_collision_records_and_surface_grouped_gltf(self):
        data = model_payload_with_regions_and_color_animation()
        segment = model_assets.ModelSegment(
            index=0,
            offset=0,
            size=len(data),
            final_flag=True,
            data=data,
        )
        geometry = model_assets.parse_model_geometry(data)
        surface_words = model_assets.bank_04_collision_surface_words(
            segment, geometry
        )
        self.assertEqual((0x01000000,), surface_words)
        self.assertEqual(
            struct.pack(">III", 0x28, 0x38, 0x48),
            model_assets.encode_collision_triangle_offsets(geometry),
        )
        gltf_data, binary_data, omitted_faces = model_assets.encode_collision_gltf(
            7, geometry, surface_words
        )
        document = json.loads(gltf_data)
        self.assertEqual((), omitted_faces)
        self.assertEqual(len(binary_data), document["buffers"][0]["byteLength"])
        self.assertEqual("0007-00-collision.bin", document["buffers"][0]["uri"])
        self.assertEqual(
            "0x01000000",
            document["materials"][0]["extras"]["surfaceWord"],
        )
        self.assertEqual(
            [0],
            document["meshes"][0]["primitives"][0]["extras"][
                "sourceFaceIndices"
            ],
        )
        secondary_gltf, _, _ = model_assets.encode_collision_gltf(
            7, geometry, None, segment_index=3
        )
        secondary_document = json.loads(secondary_gltf)
        self.assertEqual(
            "no-associated-primary-table",
            secondary_document["materials"][0]["extras"]["surfaceWordStatus"],
        )
        self.assertEqual(
            "0007-03-collision.bin",
            secondary_document["buffers"][0]["uri"],
        )

    def test_rejects_collision_surface_table_with_wrong_header(self):
        data = bytearray(model_payload_with_regions_and_color_animation())
        struct.pack_into(">I", data, 132, 4)
        segment = model_assets.ModelSegment(
            index=0,
            offset=0,
            size=len(data),
            final_flag=True,
            data=bytes(data),
        )
        geometry = model_assets.parse_model_geometry(bytes(data))
        with self.assertRaisesRegex(ValueError, "unknown table header"):
            model_assets.bank_04_collision_surface_words(segment, geometry)

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
        other = model_assets.decode_other_mode(textured.other_mode)
        self.assertEqual("one-cycle", other["cycle_type"])
        self.assertEqual("bilinear", other["texture_filter"])
        self.assertEqual("rgba16", other["texture_lut"])
        self.assertEqual("OPAQUE", other["gltf_alpha_mode"])
        translated = model_assets.translate_runtime_material_state(
            {
                "combine_mode": [0xFC121824, 0x5531FEFF],
                "other_mode": [0xEF08AC3F, 0x00552230],
                "colours": {
                    "primitive": {"rgba": [0, 0, 0, 0]},
                    "environment": {"rgba": [0, 0, 0, 255]},
                },
                "lighting_enabled": False,
            }
        )
        self.assertEqual(
            "exact-texture-times-vertex-color", translated["status"]
        )
        self.assertEqual([1.0, 1.0, 1.0, 1.0], translated["baseColorFactor"])
        lit = model_assets.translate_runtime_material_state(
            {
                "combine_mode": [0xFC121824, 0x5531FEFF],
                "other_mode": [0xEF08AC3F, 0x00552230],
                "colours": {
                    "primitive": {"rgba": [0, 0, 0, 0]},
                    "environment": {"rgba": [0, 0, 0, 255]},
                },
                "lighting_enabled": True,
            }
        )
        self.assertEqual("requires-runtime-lighting", lit["status"])
        mipmapped = model_assets.translate_runtime_material_state(
            {
                "combine_mode": [0xFC26A004, 0x151092FF],
                "other_mode": [0xEF19AC3F, 0x0F0A3238],
                "colours": {
                    "primitive": {"rgba": [0, 0, 0, 0]},
                    "environment": {"rgba": [0, 0, 0, 255]},
                },
                "lighting_enabled": False,
            }
        )
        self.assertEqual("unsupported-explicit-rdp-mipmap", mipmapped["status"])
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

        dispatched = dict(placement)
        dispatched["dispatch_kind"] = 2
        dispatched["dispatch_index"] = dispatched.pop("model_index")
        dispatched_scene_data, _ = model_assets.encode_placement_scene_gltf(
            4,
            [dispatched],
            {51: (gltf, binary)},
            placement_bank=0x0B,
            model_bank=0x04,
            model_index_field="dispatch_index",
        )
        dispatched_scene = json.loads(dispatched_scene_data)
        self.assertEqual(0x0B, dispatched_scene["extras"]["placementBank"])
        self.assertEqual(0x04, dispatched_scene["extras"]["modelBank"])
        self.assertEqual(2, dispatched_scene["nodes"][0]["extras"]["dispatchKind"])
        self.assertEqual(51, dispatched_scene["nodes"][0]["extras"]["modelIndex"])

    def test_embeds_runtime_material_variant_and_translates_alpha_mode(self):
        geometry = model_assets.parse_model_geometry(model_payload())
        state = {
            "texture": {"enabled": True},
            "tiles": [],
            "combine_mode": [0xFC121824, 0xFF33FFFF],
            "other_mode": [0xEF000000, 0x00004000],
            "colours": {
                "primitive": {"rgba": [0, 0, 0, 255]},
                "environment": {"rgba": [0, 0, 0, 255]},
            },
            "geometry_mode": 0,
            "lighting_enabled": False,
        }
        translation = model_assets.translate_runtime_material_state(state)
        runtime_material = {
            "model_sha1": "model-sha1",
            "source_first_face": 0,
            "source_face_count": 1,
            "variant_count": 1,
            "observation_count": 2,
            "variants": [
                {
                    "material_state_hash": "state-sha256",
                    "observation_count": 2,
                    "state": state,
                    "gltf_translation": translation,
                    "evidence": [{"trace": "ignored-in-gltf"}],
                }
            ],
        }
        gltf_data, _ = model_assets.encode_gltf(
            0,
            0,
            geometry,
            runtime_materials={0: runtime_material},
        )
        material = json.loads(gltf_data)["materials"][0]
        self.assertEqual("BLEND", material["alphaMode"])
        self.assertEqual(
            "exact-texture-times-vertex-color",
            material["extras"]["runtimeMaterial"]["consensus"]["statuses"][0],
        )
        self.assertNotIn(
            "evidence", material["extras"]["runtimeMaterial"]["variants"][0]
        )

    def test_runtime_material_manifest_summarizes_resolved_segment_8_calls(self):
        session = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "session",
            "spec_name": "test",
            "normalized_sha1": "rom-sha1",
            "tool_revisions": {},
        }
        event = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "draw_state",
            "state": {
                "joint_matrices": [],
                "rdp": {
                    "draw_runs": [],
                    "material_run_correlations": [],
                    "nested_display_lists": [
                        {
                            "address": 0x08000000,
                            "resolved_address": 0x80083140,
                        },
                        {
                            "address": 0x08000040,
                            "resolved_address": 0x80083180,
                        },
                        {
                            "address": 0x08000000,
                            "resolved_address": 0x80083140,
                        },
                        {
                            "address": 0x80100000,
                            "resolved_address": 0x80100000,
                        },
                    ],
                    "unresolved_display_list_targets": [],
                },
            },
        }
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            trace = root / "trace.jsonl"
            trace.write_text(
                json.dumps(session) + "\n" + json.dumps(event) + "\n",
                encoding="utf-8",
            )
            with mock.patch.object(
                model_assets,
                "runtime_material_inventory",
                return_value=("rom-sha1", {}),
            ):
                manifest = model_assets.extract_runtime_materials(
                    "us", None, (trace,), root / "output", False
                )

        self.assertEqual(4, manifest["nested_display_list_call_count"])
        self.assertEqual(4, manifest["resolved_address_display_list_call_count"])
        self.assertEqual(0, manifest["decoder_unresolved_display_list_call_count"])
        self.assertEqual(3, manifest["segment_8_display_list_call_count"])
        self.assertEqual(3, manifest["resolved_segment_8_display_list_call_count"])
        self.assertEqual(2, manifest["resolved_segment_8_display_list_count"])
        self.assertEqual(
            ["0x80083140", "0x80083180"],
            manifest["resolved_segment_8_display_list_addresses"],
        )

    def test_replays_captured_cbfd_basic_and_advanced_lighting(self):
        vertex = model_assets.ModelVertex(0, 0, 0, 0, 0, 0, (255, 128, 64, 32))
        context = {
            "model_view_rows": [
                [1.0, 0.0, 0.0, 0.0],
                [0.0, 1.0, 0.0, 0.0],
                [0.0, 0.0, 1.0, 0.0],
                [0.0, 0.0, 0.0, 1.0],
            ]
        }

        def slot(index, colour, direction=(0.0, 0.0, 1.0)):
            return {
                "light_slot": index,
                "decoded": {
                    "colour": list(colour),
                    "direction_normalized": list(direction),
                    "attenuation": 0.0,
                    "position_s16": [0, 0, 0, 0],
                },
            }

        lights = {
            "num_lights": 2,
            "advanced_lighting": False,
            "coordinate_modifiers": [0.0] * 15,
            "slots": [
                slot(0, (255, 255, 255)),
                slot(2, (64, 128, 255)),
            ],
        }
        basic = model_assets.replay_cbfd_vertex_lighting(
            vertex,
            None,
            {"lighting_enabled": True, "geometry_mode": 0, "lights": lights},
            context,
        )
        self.assertEqual(
            (64 / 255, 128 / 255 * 128 / 255, 64 / 255, 32 / 255),
            basic,
        )
        lights["advanced_lighting"] = True
        lights["slots"].insert(1, slot(1, (255, 255, 255)))
        advanced = model_assets.replay_cbfd_vertex_lighting(
            vertex,
            (0, 0, 127),
            {"lighting_enabled": True, "geometry_mode": 0, "lights": lights},
            context,
        )
        self.assertEqual((1.0, 128 / 255, 64 / 255, 32 / 255), advanced)

    def test_runtime_lighting_context_requires_matching_captured_matrix(self):
        matrix = {
            "sha256": "a" * 64,
            "layout": "n64-mtx-row-major-4x4-s16.16-split",
            "rows": [[1.0, 0.0, 0.0, 0.0]] * 4,
            "translation": [0.0, 0.0, 0.0],
        }
        context = model_assets.runtime_lighting_context(
            {"captured_matrix_index": 0, "matrix_sha256": "a" * 64},
            [matrix],
        )
        self.assertEqual("a" * 64, context["matrix_sha256"])
        self.assertEqual(64, len(context["lighting_context_hash"]))
        with self.assertRaisesRegex(ValueError, "matrix hash changed"):
            model_assets.runtime_lighting_context(
                {"captured_matrix_index": 0, "matrix_sha256": "b" * 64},
                [matrix],
            )

    def test_gltf_bakes_unambiguous_runtime_normal_stream_lighting(self):
        geometry = model_assets.parse_model_geometry(model_payload())
        light_slots = []
        for index, colour in ((0, [0, 0, 0]), (1, [255, 255, 255]), (2, [64, 64, 64])):
            light_slots.append(
                {
                    "light_slot": index,
                    "decoded": {
                        "colour": colour,
                        "direction_normalized": [0.0, 0.0, 1.0],
                        "attenuation": 0.0,
                        "position_s16": [0, 0, 0, 0],
                    },
                }
            )
        state = {
            "combine_mode": [0xFC121824, 0x5531FEFF],
            "other_mode": [0xEF08AC3F, 0x00552230],
            "colours": {
                "primitive": {"rgba": [0, 0, 0, 0]},
                "environment": {"rgba": [0, 0, 0, 255]},
            },
            "lighting_enabled": True,
            "geometry_mode": 0,
            "lights": {
                "num_lights": 2,
                "advanced_lighting": True,
                "coordinate_modifiers": [0.0] * 15,
                "slots": light_slots,
            },
        }
        runtime_material = {
            "model_sha1": "model-sha1",
            "source_first_face": 0,
            "source_face_count": 1,
            "variant_count": 1,
            "observation_count": 1,
            "variants": [
                {
                    "material_state_hash": "state-sha256",
                    "observation_count": 1,
                    "state": state,
                    "gltf_translation": model_assets.translate_runtime_material_state(
                        state
                    ),
                    "lighting_context_count": 1,
                    "lighting_contexts": [
                        {
                            "lighting_context_hash": "context-sha256",
                            "model_view_rows": [
                                [1.0, 0.0, 0.0, 0.0],
                                [0.0, 1.0, 0.0, 0.0],
                                [0.0, 0.0, 1.0, 0.0],
                                [0.0, 0.0, 0.0, 1.0],
                            ],
                            "normal_stream": {
                                "normal_xy_s8": [[0, 0] for _ in range(32)]
                            },
                        }
                    ],
                    "evidence": [],
                }
            ],
        }

        gltf_data, _ = model_assets.encode_gltf(
            0, 0, geometry, runtime_materials={0: runtime_material}
        )
        gltf = json.loads(gltf_data)
        primitive = gltf["meshes"][0]["primitives"][0]
        color = gltf["accessors"][primitive["attributes"]["COLOR_0"]]

        self.assertEqual(5126, color["componentType"])
        self.assertIn("NORMAL", primitive["attributes"])
        self.assertEqual(
            "gliden64-equivalent-observed-draw",
            gltf["materials"][0]["extras"]["runtimeMaterial"]["lightingReplay"][
                "status"
            ],
        )

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
        self.assertEqual(
            (None, "mode-one-ci8-palette-overlaps-pixels"),
            model_assets.choose_preview_texture(
                ci8_run,
                {(42, 2, 1): (exact,)},
                mode_one_ci8_palette_policy="payload-base",
            ),
        )

    def test_composes_direct_ci8_for_non_null_parser_consumer(self):
        geometry = model_assets.parse_model_geometry(
            model_payload_with_material_runs()
        )
        run = geometry.material_runs[0]
        ci8_run = replace(
            run,
            pixel=replace(
                run.pixel,
                image_command=0xFD500000,
                mode=0,
                load_command=(0xF3000000, 0x073FF000),
            ),
            palette=replace(
                run.palette,
                image_command=0xFD100000,
                mode=1,
                load_command=(0xF0000000, 0x063FC000),
            ),
            render_tile=(0xF5480800, run.render_tile[1]),
        )
        payload = bytes(range(256)) * 4 + bytes.fromhex("0001") * 256
        texture, status = model_assets.choose_preview_texture(
            ci8_run,
            {},
            {42: payload},
            mode_one_ci8_palette_policy="payload-end-minus-0x200",
        )
        self.assertEqual("runtime-composed-direct-ci8-texture", status)
        self.assertEqual("us-direct-runtime-composed", texture.family)
        self.assertEqual((32, 32), (texture.width, texture.height))
        self.assertEqual(0, texture.pixel_byte_offset)
        self.assertEqual(0x400, texture.palette_byte_offset)
        self.assertTrue(texture.png_data.startswith(b"\x89PNG\r\n\x1a\n"))

    def test_composes_character_ci4_from_tmem_span_and_trailing_tlut(self):
        geometry, _ = model_assets.parse_character_model_geometry(
            character_model_payload()
        )
        run = geometry.material_runs[0]
        ci4_run = replace(
            run,
            palette=replace(
                run.palette,
                mode=2,
                load_command=(0xF0000000, 0x0603C000),
            ),
            render_tile=(0xF5000400, run.render_tile[1]),
        )
        payload = bytes(1024) + bytes.fromhex("0001") * 16 + bytes(480)
        texture, status = model_assets.character_runtime_preview_texture(
            ci4_run, payload
        )
        self.assertEqual("runtime-composed-character-texture", status)
        self.assertEqual(0, texture.size)
        self.assertEqual(1024, texture.palette_byte_offset)
        self.assertTrue(texture.png_data.startswith(b"\x89PNG\r\n\x1a\n"))

    def test_keeps_character_mipmap_combiner_unbound_when_tile_one_is_proven(self):
        geometry, _ = model_assets.parse_character_model_geometry(
            character_model_payload()
        )
        run = geometry.material_runs[0]
        mipmapped = replace(
            run,
            combine_mode=(0xFC26A080, 0x151492FF),
            render_tiles=run.render_tiles
            + ((1, 0xF5480480, 0x01010441),),
        )
        payload = bytes(range(256)) * 6 + bytes.fromhex("0001") * 256
        texture, status = model_assets.choose_preview_texture(
            mipmapped, {}, {42: payload}
        )
        self.assertEqual(
            "character-indexed-mipmap-combiner-unresolved", status
        )
        self.assertIsNone(texture)

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
