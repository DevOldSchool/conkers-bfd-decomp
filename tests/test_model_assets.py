from __future__ import annotations

import argparse
import base64
import hashlib
import json
import math
import struct
import tempfile
import unittest
from dataclasses import replace
from pathlib import Path
from unittest import mock

from scripts import model_assets
from scripts import texture_assets
from scripts import validate_model_previews_blender


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


def model_payload_with_culling() -> bytes:
    data = bytearray(model_payload())
    display_offset = struct.unpack_from(">I", data)[0]
    pairs = (
        (0xD7000000, 0xFFFFFFFF), (0x01003006, 0x01000000),
        (0x05000204, 0),  # Both bits inherited.
        (0xD9FFFDFF, 0), (0x05000402, 0),  # Only front is known clear.
        (0xD9FFFFFF, 0x400), (0x05000204, 0),
        (0xEF082C3F, 0x00552230), (0x05000402, 0),  # RDP state preserves RSP culling.
        (0xD9FFFBFF, 0), (0x05000204, 0),
        (0xDE000000, 0x08000040), (0x05000402, 0),  # Unresolved call invalidates knowledge.
        (0xD9FFF9FF, 0x400), (0x05000204, 0),
        (0xDF000000, 0),
        (0xD7000000, 0xFFFFFFFF), (0x01003006, 0x01000000),
        (0x05000402, 0), (0xDF000000, 0),  # Independent callable list.
    )
    commands = b"".join(struct.pack(">II", *pair) for pair in pairs)
    struct.pack_into(">I", data, 4, len(commands))
    return bytes(data[:display_offset]) + commands


def model_payload_with_mixed_vertex_matrices() -> bytes:
    data = bytearray(model_payload())
    display_offset = struct.unpack_from(">I", data, 0)[0]
    commands = b"".join(
        struct.pack(">II", command, argument)
        for command, argument in (
            (0xDA380003, 0x03000040),
            (0x01002004, 0x01000000),  # Cache 0/1 under matrix 1.
            (0xDA380003, 0x03000080),
            (0x01001006, 0x01000020),  # Cache 2 under matrix 2.
            (0xDA380003, 0x03000000),  # Draw matrix must not change the cache.
            (0x05000204, 0),
            (0xDA380003, 0x030000C0),
            (0x01001002, 0x01000000),  # Reload source vertex 0 under matrix 3.
            (0xDA380003, 0x03000000),
            (0x05000204, 0),
            (0xDF000000, 0),
        )
    )
    struct.pack_into(">I", data, 4, len(commands))
    return bytes(data[:display_offset]) + commands


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
    def test_vertex_load_matrices_survive_cache_reuse_and_gltf_skinning(self):
        geometry = model_assets.parse_model_geometry(
            model_payload_with_mixed_vertex_matrices()
        )
        self.assertEqual(((0, 1, 2),) * 2, geometry.faces)
        self.assertEqual(((1, 1, 2), (3, 1, 2)), geometry.face_matrix_indices)
        self.assertEqual(1, len(geometry.material_runs))
        self.assertEqual(0, geometry.material_runs[0].matrix_index)
        pivots = ((0, 0, 0), (100, 0, 0), (0, 200, 0), (0, 0, 300))
        joints = tuple(
            {"record_index": i, "parent_matrix_index": -1 if i == 0 else 0,
             "matrix_index": i, "animation_index": i, "flags": 0,
             "bind_pivot_f32": list(pivot)}
            for i, pivot in enumerate(pivots)
        )
        data, binary = model_assets.encode_gltf(
            0, 0, geometry, bank_index=1, character_joints=joints
        )
        gltf = json.loads(data)
        attributes = gltf["meshes"][0]["primitives"][0]["attributes"]

        def values(attribute, fmt):
            accessor = gltf["accessors"][attributes[attribute]]
            view = gltf["bufferViews"][accessor["bufferView"]]
            start = view.get("byteOffset", 0)
            return tuple(struct.iter_unpack(fmt, binary[start:start + view["byteLength"]]))

        self.assertEqual(
            ((1, 0, 0, 0), (1, 0, 0, 0), (2, 0, 0, 0), (3, 0, 0, 0)),
            values("JOINTS_0", "<4H"),
        )
        self.assertEqual(
            ((100, 0, 0), (110, 0, 0), (0, 210, 0), (0, 0, 300)),
            values("POSITION", "<3f"),
        )
        records = model_assets.validation_face_records(geometry, joints)
        self.assertEqual(((100, 0, 0), (110, 0, 0), (0, 210, 0)), records[0]["positions"])

    def test_pose_and_composition_preserve_each_cached_vertex_matrix(self):
        geometry = model_assets.parse_model_geometry(model_payload_with_mixed_vertex_matrices())
        geometry = replace(geometry, face_cull_modes=(0x400, 0))
        merged = model_assets.merge_character_composition_geometry(
            {(1, 0, 0, "model"): geometry},
            [{"bank": 1, "entry": 0, "segment": 0, "model_sha1": "model",
              "static_cluster_index": 0, "material_run": 0,
              "first_face": 0, "face_count": 2}],
        )
        self.assertEqual(geometry.face_matrix_indices, merged.face_matrix_indices)
        self.assertEqual((0x400, 0), merged.face_cull_modes)
        matrices = {
            i: [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [*translation, 1]]
            for i, translation in ((1, (100, 0, 0)), (2, (0, 200, 0)), (3, (0, 0, 300)))
        }
        posed = model_assets.bake_character_runtime_pose(merged, matrices, [0, 0, 0])
        self.assertEqual(((0, 1, 2), (3, 1, 2)), posed.faces)
        self.assertEqual(
            ((100, 0, 0), (110, 0, 0), (0, 210, 0), (0, 0, 300)),
            tuple((v.x, v.y, v.z) for v in posed.vertices),
        )
        self.assertEqual((), posed.face_matrix_indices)
        self.assertEqual((0x400, 0), posed.face_cull_modes)
        del matrices[2]
        with self.assertRaisesRegex(ValueError, "runtime matrix 2 is absent"):
            model_assets.bake_character_runtime_pose(merged, matrices, [0, 0, 0])

    def test_joint_local_zero_area_face_can_be_drawable_after_transforms(self):
        geometry = model_assets.parse_model_geometry(model_payload())
        geometry = replace(geometry, faces=((0, 1, 1),), face_matrix_indices=((0, 0, 1),))
        preview, omitted, _ = model_assets.omit_zero_area_preview_faces(geometry)
        self.assertEqual((), omitted)
        self.assertEqual(geometry.face_matrix_indices, preview.face_matrix_indices)
        posed = model_assets.bake_character_runtime_pose(
            preview,
            {0: [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]],
             1: [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 10, 0, 1]]},
            [0, 0, 0],
        )
        self.assertEqual((), model_assets.omit_zero_area_preview_faces(posed)[1])

    def test_pose_preserves_per_corner_normals_in_gltf(self):
        geometry = model_assets.parse_model_geometry(model_payload())
        geometry = replace(geometry, face_matrix_indices=((0, 1, 2),),
                           face_normal_bytes=(((127, 127, 0),) * 3,))
        matrices = {
            0: [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [10, 20, 30, 1]],
            1: [[2, 0, 0, 0], [0, 3, 0, 0], [0, 0, 4, 0], [10, 20, 30, 1]],
            2: [[1, 0, 0, 0], [0, 0, 1, 0], [0, -1, 0, 0], [10, 20, 30, 1]],
        }
        posed = model_assets.bake_character_runtime_pose(geometry, matrices, [10, 20, 30])
        expected = ((2 ** -0.5, 2 ** -0.5, 0),
                    (3 / 13 ** 0.5, 2 / 13 ** 0.5, 0),
                    (2 ** -0.5, 0, 2 ** -0.5))
        self.assertEqual((), posed.face_normal_bytes)
        self.assertEqual(geometry.face_normal_bytes, (((127, 127, 0),) * 3,))
        gltf, binary = model_assets.encode_gltf(0, 0, posed)
        document = json.loads(gltf)
        primitive = document["meshes"][0]["primitives"][0]
        accessor = document["accessors"][primitive["attributes"]["NORMAL"]]
        view = document["bufferViews"][accessor["bufferView"]]
        normals = list(struct.iter_unpack("<3f", binary[view["byteOffset"]:view["byteOffset"] + view["byteLength"]]))
        self.assertEqual(3, len(normals))
        for observed, wanted in zip(normals, expected):
            for x, y in zip(observed, wanted):
                self.assertAlmostEqual(y, x, places=6)
        # A non-uniformly scaled surface tangent remains perpendicular.
        self.assertAlmostEqual(0, 2 * normals[1][0] - 3 * normals[1][1], places=6)
        self.assertIn("inverse-transpose", document["extras"]["characterNormalStatus"])

    def test_pose_normal_fallbacks_and_face_filter_stay_aligned(self):
        identity = [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]]
        self.assertIsNone(model_assets.transform_preview_normal(None, identity))
        self.assertIsNone(model_assets.transform_preview_normal((0, 0, 0), identity))
        singular = [row[:] for row in identity]
        singular[0] = [0, 0, 0, 0]
        self.assertIsNone(model_assets.transform_preview_normal((127, 0, 0), singular))
        reflected = [row[:] for row in identity]
        reflected[0][0] = -1
        self.assertEqual((-1, 0, 0), model_assets.transform_preview_normal((127, 0, 0), reflected))
        geometry = model_assets.parse_model_geometry(model_payload())
        geometry = replace(geometry, faces=((0, 0, 0), *geometry.faces),
                           material_runs=(replace(geometry.material_runs[0], face_count=2),),
                           face_preview_normals=(((1, 0, 0),) * 3, ((0, 0, 1), None, (0, 0, 1))),
                           face_command_offsets=(), face_command_opcodes=(),
                           face_cache_indices=(), face_matrix_indices=(), face_cull_modes=())
        filtered, omitted, _ = model_assets.omit_zero_area_preview_faces(geometry)
        self.assertEqual((0,), omitted)
        self.assertEqual((geometry.face_preview_normals[1],), filtered.face_preview_normals)
        gltf, _ = model_assets.encode_gltf(0, 0, filtered)
        self.assertIn("NORMAL", json.loads(gltf)["meshes"][0]["primitives"][0]["attributes"])

    def test_culling_tracks_known_bits_calls_and_independent_lists(self):
        geometry = model_assets.parse_model_geometry(model_payload_with_culling(), independent_display_lists=True)
        self.assertEqual((None, None, 0x400, 0x400, 0, None, 0x400, None), geometry.face_cull_modes)
        self.assertEqual(4, len(geometry.material_runs))
        self.assertEqual([(0, 2, None), (2, 1, 0x400)],
                         model_assets.face_culling_spans(geometry, geometry.material_runs[0]))
        with self.assertRaisesRegex(ValueError, "culling state does not cover"):
            model_assets.face_culling_spans(replace(geometry, face_cull_modes=(0,)), geometry.material_runs[0])

    def test_runtime_culling_requires_consensus_for_each_bounded_face(self):
        def observation(first, count, mode):
            return {"source_first_face": first, "source_face_count": count,
                    "face_culling": {"mode": mode, "known_bits": 0x600 if mode is not None else 0}}
        record = {"source_first_face": 10, "source_face_count": 4,
                  "variants": [{"evidence": [observation(10, 2, 0x400)]},
                               {"evidence": [observation(11, 2, 0), observation(12, 1, None)]}]}
        self.assertEqual({10: 0x400, 11: None, 12: None}, model_assets.runtime_face_culling_map(record))
        self.assertEqual({}, model_assets.runtime_face_culling_map(None))
        record["variants"][1]["evidence"].append({"source_first_face": 13, "source_face_count": 1})
        self.assertEqual({}, model_assets.runtime_face_culling_map(record))
        record["variants"][1]["evidence"][-1] = observation(14, 1, 0)
        with self.assertRaisesRegex(ValueError, "exceeds source material"):
            model_assets.runtime_face_culling_map(record)
        record["variants"][1]["evidence"][-1] = observation(13, 1, 0x800)
        with self.assertRaisesRegex(ValueError, "invalid known bits"):
            model_assets.runtime_face_culling_map(record)
        record["variants"][1]["evidence"][-1] = observation(13, 1, 0)
        record["variants"][1]["evidence"][-1]["material_correlation_status"] = "equivalent-material-aliases"
        self.assertEqual({}, model_assets.runtime_face_culling_map(record))

    def test_runtime_culling_remaps_filtered_source_faces_without_extending_coverage(self):
        geometry = model_assets.parse_model_geometry(model_payload_with_culling(), independent_display_lists=True)
        # The first local run represents three surviving faces from a larger
        # source range. One captured face was omitted by a prior pose filter.
        geometry = replace(geometry, face_source_indices=(10, 12, 14, 15, 16, 17, 18, 19))
        state = {"texture": {}, "tiles": [], "colours": {}, "geometry_mode": 0}
        record = {"model_sha1": "test", "source_first_face": 10, "source_face_count": 5,
                  "variant_count": 1, "observation_count": 2,
                  "variants": [{"state": state,
                                "gltf_translation": model_assets.translate_runtime_material_state(state),
                                "evidence": [{"source_first_face": 10, "source_face_count": 2,
                                              "face_culling": {"mode": 0x400, "known_bits": 0x600}},
                                             {"source_first_face": 14, "source_face_count": 1,
                                              "face_culling": {"mode": None, "known_bits": 0}}]}]}
        data, _ = model_assets.encode_gltf(0, 0, geometry, runtime_materials={0: record})
        materials = [m for m in json.loads(data)["materials"] if m["extras"]["materialRun"] == 0]
        self.assertEqual([False, True, False], [m["doubleSided"] for m in materials])
        self.assertEqual([(0, 1), (1, 1), (2, 1)], [(m["extras"]["firstFace"], m["extras"]["faceCount"]) for m in materials])
        culling = [m["extras"]["faceCulling"] for m in materials]
        self.assertEqual(["captured-command-replay", "ROM-display-list-analysis", "ROM-display-list-analysis"], [c["source"] for c in culling])
        self.assertEqual([1, 0, 0], [c.get("runtimeObservedFaceCount", 0) for c in culling])
        self.assertEqual([0, 0, 1], [c.get("runtimeConflictFaceCount", 0) for c in culling])
        self.assertEqual(["back", "inherited-unresolved", "back"], [c["mode"] for c in culling])
        record["variants"][0]["evidence"][1]["face_culling"] = {"mode": 0, "known_bits": 0x600}
        data, _ = model_assets.encode_gltf(0, 0, geometry, runtime_materials={0: record})
        last = json.loads(data)["materials"][2]
        self.assertFalse(last["doubleSided"])
        self.assertEqual(1, last["extras"]["faceCulling"]["runtimeConflictFaceCount"])

    def test_gltf_partitions_culling_without_changing_faces_or_source_runs(self):
        geometry = model_assets.parse_model_geometry(model_payload_with_culling(), independent_display_lists=True)
        encoded, binary = model_assets.encode_gltf(0, 0, geometry)
        gltf = json.loads(encoded)
        primitives = gltf["meshes"][0]["primitives"]
        self.assertEqual(7, len(primitives))
        recovered_faces = []
        for primitive in primitives:
            material = gltf["materials"][primitive["material"]]
            extra = material["extras"]
            first, count = extra["firstFace"], extra["faceCount"]
            run = geometry.material_runs[extra["materialRun"]]
            self.assertTrue(run.first_face <= first < first + count <= run.first_face + run.face_count)
            self.assertEqual(geometry.face_cull_modes[first] != 0x400, material["doubleSided"])
            def values(accessor_index, fmt):
                accessor = gltf["accessors"][accessor_index]
                view = gltf["bufferViews"][accessor["bufferView"]]
                return list(struct.iter_unpack(fmt, binary[view["byteOffset"]:view["byteOffset"] + view["byteLength"]]))
            positions = values(primitive["attributes"]["POSITION"], "<3f")
            indices = [index for (index,) in values(primitive["indices"], "<H")]
            recovered_faces.extend(tuple(positions[index] for index in indices[i:i + 3]) for i in range(0, len(indices), 3))
        expected = [tuple((geometry.vertices[i].x, geometry.vertices[i].y, geometry.vertices[i].z) for i in face) for face in geometry.faces]
        self.assertEqual(expected, recovered_faces)
        records = [{"face_count": run.face_count, "runtime_material": None} for run in geometry.material_runs]
        model_assets.verify_gltf_material_spans(gltf, records)
        gltf["materials"][1]["extras"]["firstFace"] -= 1
        with self.assertRaisesRegex(ValueError, "do not partition"):
            model_assets.verify_gltf_material_spans(gltf, records)
        gltf["materials"][1]["extras"]["firstFace"] += 1
        gltf["materials"][1]["doubleSided"] = True
        with self.assertRaisesRegex(ValueError, "culling flag"):
            model_assets.verify_gltf_material_spans(gltf, records)

    def test_independent_display_list_does_not_inherit_a_stored_neighbor_texture(self):
        data = bytearray(model_payload_with_material_runs())
        display_offset, display_size = struct.unpack_from(">II", data)
        # First list loads image 42. The next list reloads vertices and enables texturing;
        # its caller supplies the image and tile state.
        data.extend(struct.pack(">II", 0xD7000002, 0xFFFFFFFF))
        data.extend(struct.pack(">II", 0x01003006, 0x01000000))
        data.extend(struct.pack(">II", 0x05000204, 0))
        data.extend(struct.pack(">II", 0xDF000000, 0))
        struct.pack_into(">I", data, 4, display_size + 32)
        geometry = model_assets.parse_model_geometry(
            bytes(data), allow_external_texture=True, independent_display_lists=True
        )
        last = geometry.material_runs[-1]
        self.assertTrue(last.pixel.external)
        self.assertIsNone(last.pixel.flat_index)
        self.assertIsNone(last.render_tile)
        self.assertEqual((None, "external-runtime-texture"), model_assets.choose_preview_texture(last, {}))
        # Without a local Texture command, even texture enable is unknown.
        struct.pack_into(">II", data, display_offset + display_size, 0xE7000000, 0)
        unknown = model_assets.parse_model_geometry(
            bytes(data), allow_external_texture=True, independent_display_lists=True
        ).material_runs[-1]
        self.assertIsNone(unknown.texture_enabled)
        self.assertEqual(
            (None, "runtime-texture-enable-state-unresolved"),
            model_assets.choose_preview_texture(unknown, {}),
        )

    def test_blender_validator_collects_cross_bank_models_and_scenes(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for bank in (1, 3, 4, 9):
                preview = root / f"us-bank-{bank:02x}-preview"
                preview.mkdir()
                model = {"gltf_file": "geometry/model.gltf"}
                if bank == 1:
                    model["bind_gltf_file"] = "geometry/model-bind.gltf"
                scenes = (
                    [{"gltf_file": "scenes/scene.gltf"}]
                    if bank in (3, 4)
                    else []
                )
                (preview / "geometry").mkdir()
                (preview / "geometry/model.gltf").write_text("{}", encoding="utf-8")
                if bank == 1:
                    (preview / "geometry/model-bind.gltf").write_text(
                        "{}", encoding="utf-8"
                    )
                if scenes:
                    (preview / "scenes").mkdir()
                    (preview / "scenes/scene.gltf").write_text("{}", encoding="utf-8")
                (preview / "manifest.json").write_text(
                    json.dumps(
                        {
                            "bank_index": bank,
                            "model_count": 1,
                            "models": [model],
                            "assembled_scene_count": len(scenes),
                            "assembled_scenes": scenes,
                        }
                    ),
                    encoding="utf-8",
                )
            records = validate_model_previews_blender.collect_preview_records(root)

            self.assertEqual(7, len(records))
            self.assertEqual(
                2,
                sum(record["kind"] == "assembled-scene" for record in records),
            )
            self.assertEqual(
                1,
                sum(record["kind"] == "animated-model" for record in records),
            )

    def test_texture_command_selects_tile_and_its_own_bounds(self):
        data = bytearray(model_payload())
        display_offset = struct.unpack_from(">I", data)[0]
        commands = [
            (0x01003006, 0x01000000),
            (0xF5080800, 0x04014050),  # Tile 4: 8-bit, 32x32 masks.
            (0xF2004008, 0x04080084),  # Its own nonzero S/T origin.
            (0xF5000800, 0x00054160),  # Tile 0: 4-bit, 64x32 masks.
            (0xF2002002, 0x000FE07E),
            (0xD7002402, 0xFFFFFFFF),  # Select 4, after defining 0.
            (0x05000204, 0),
            (0xD7000002, 0xFFFFFFFF),
            (0x05000204, 0),
            (0xD7002502, 0xFFFFFFFF),  # Missing tile 5 must not use 0.
            (0x05000204, 0),
            (0xDF000000, 0),
        ]
        payload = b"".join(struct.pack(">II", *pair) for pair in commands)
        struct.pack_into(">I", data, 4, len(payload))
        geometry = model_assets.parse_model_geometry(
            bytes(data[:display_offset]) + payload, allow_external_texture=True
        )
        selected, zero, missing = geometry.material_runs
        state = model_assets.texture_coordinate_state(selected)
        self.assertEqual((32, 32, 4, 8, 1), tuple(
            state[key] for key in ("width", "height", "uls", "ult", "size")
        ))
        self.assertEqual((-1 / 32, 1 + 2 / 32),
                         model_assets.texture_coordinates(geometry.vertices[0], selected))
        self.assertEqual(64, model_assets.texture_coordinate_state(zero)["width"])
        self.assertIsNone(missing.render_tile)
        self.assertIsNone(missing.tile_bounds)
        with self.assertRaisesRegex(ValueError, "lacks tile"):
            model_assets.texture_coordinate_state(missing)

    def test_selected_facial_tile_decodes_ci8_without_tile_zero_bounds(self):
        data = bytearray(character_model_payload())
        table = struct.unpack_from(">I", data, 8)[0]
        start = struct.unpack_from(">I", data, table)[0]
        # Reuse the fixture's local load contract, defining its render tile as
        # tile 4 with masks, then selecting it explicitly before drawing.
        for offset in range(start, len(data) - 7, 8):
            command, argument = struct.unpack_from(">II", data, offset)
            if command >> 24 == 0xF5 and (argument >> 24) & 7 == 0:
                struct.pack_into(">II", data, offset, 0xF5080800, 0x04014050)
            elif command >> 24 == 0xD7:
                struct.pack_into(">I", data, offset, 0xD7000402)
        geometry, _ = model_assets.parse_character_model_geometry(bytes(data))
        run = geometry.material_runs[0]
        self.assertIsNone(run.tile_bounds)
        captured = model_assets.runtime_captured_preview_texture(run, {
            "other_mode": [0xEF18AC3F, 0x0C184DD8],
            "tile_bounds": {"4": [0xF2002002, 0x0407E07E]},
            "texture": {"enabled": True, "scale": list(run.texture_scale),
                        "pixel_image": {"captured_texture_image_index": 0},
                        "palette_image": {"captured_texture_image_index": 1}},
            "tiles": [{"index": 4, "command": 0xF5080800, "argument": 0x04014050}],
        }, {0: bytes(range(256)) * 4, 1: bytes.fromhex("FFFF") * 256})
        self.assertIsNotNone(captured)
        self.assertEqual(("ci8", 32, 32),
                         tuple(captured[key] for key in ("format", "width", "height")))
        replayed = model_assets.apply_runtime_texture_coordinates(
            geometry, {0: {"variants": [{"captured_texture": captured}]}}
        )
        self.assertEqual("captured-command-replay", captured["coordinate_state"]["bounds_evidence"])
        self.assertIsNone(geometry.material_runs[0].tile_bounds)
        self.assertEqual((0xF2002002, 0x0407E07E), replayed.material_runs[0].tile_bounds)
        before = model_assets.texture_coordinates(geometry.vertices[0], run)
        after = model_assets.texture_coordinates(replayed.vertices[0], replayed.material_runs[0])
        self.assertEqual((before[0] - 0.5 / 32, before[1] + 0.5 / 32), after)
        captured["width"] = 64
        with self.assertRaisesRegex(ValueError, "dimensions disagree"):
            model_assets.apply_runtime_texture_coordinates(
                geometry, {0: {"variants": [{"captured_texture": captured}]}}
            )
        wrapped = model_assets.runtime_captured_preview_texture(run, {
            "other_mode": [0xEF18AC3F, 0x0C184DD8],
            "tile_bounds": {"4": [0xF2FFB00B, 0x0407E0FE]},
            "texture": {"enabled": True, "scale": list(run.texture_scale),
                        "pixel_image": {"captured_texture_image_index": 0},
                        "palette_image": {"captured_texture_image_index": 1}},
            "tiles": [{"index": 4, "command": 0xF5080800, "argument": 0x04014050}],
        }, {0: bytes(range(256)) * 4, 1: bytes.fromhex("FFFF") * 256})
        self.assertIsNotNone(wrapped)
        self.assertEqual([32, 32], wrapped["coordinate_state"]["texture_dimensions"])
        replayed = model_assets.apply_runtime_texture_coordinates(
            geometry, {0: {"variants": [{"captured_texture": wrapped}]}}
        )
        after = model_assets.texture_coordinates(replayed.vertices[0], replayed.material_runs[0])
        self.assertEqual((before[0] - 4091 / 128, before[1] + 11 / 128), after)

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
            face_matrix_indices=((None, None, None),) * 2,
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
            face_matrix_indices=((None, None, None),) * 2,
            material_runs=(replace(geometry.material_runs[0], face_count=2),),
            face_command_offsets=(0x68, 0x70),
            face_command_opcodes=(0x05, 0x06),
            face_cull_modes=(0x400, 0),
        )
        preview, omitted, omitted_by_run = (
            model_assets.omit_zero_area_preview_faces(geometry)
        )
        self.assertEqual((0,), omitted)
        self.assertEqual((1,), omitted_by_run)
        self.assertEqual(((0, 1, 2),), preview.faces)
        self.assertEqual((0x70,), preview.face_command_offsets)
        self.assertEqual((0x06,), preview.face_command_opcodes)
        self.assertEqual((0,), preview.face_cull_modes)
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
            face_matrix_indices=((7, 7, 7),),
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
        self.assertEqual(
            {
                "coefficients": [175, -33, 7, 222, 114, 42],
                "raw": ["0xEC15FDF0", "0x3B78E42A"],
            },
            model_assets.decode_convert_mode((0xEC15FDF0, 0x3B78E42A)),
        )
        two_cycle_lit = model_assets.translate_runtime_material_state(
            {
                "combine_mode": [0xFCFF9880, 0xF514FEFF],
                "other_mode": [0xEF18AC3F, 0x04D12078],
                "convert_mode": [0xEC15FDF0, 0x3B78E42A],
                "colours": {
                    "primitive": {"rgba": [0, 0, 0, 0]},
                    "environment": {"rgba": [0, 0, 0, 255]},
                },
                "lighting_enabled": True,
                "lights": {"slots": [{"decoded": {"colour": [255, 255, 255]}}]},
            }
        )
        self.assertEqual(
            "requires-runtime-lighting-replay", two_cycle_lit["status"]
        )
        self.assertEqual(
            [1.0, 1.0, 1.0, 1.0], two_cycle_lit["baseColorFactor"]
        )
        self.assertEqual(42, two_cycle_lit["convertMode"]["coefficients"][5])
        k5_lit = model_assets.translate_runtime_material_state(
            {
                "combine_mode": [0xFCFFFE8F, 0xF517F8FF],
                "convert_mode": [0xEC000000, 0x000000FF],
                "other_mode": [0xEF182C3F, 0x04D12078],
                "colours": {
                    "primitive": {"rgba": [0, 0, 0, 0]},
                    "environment": {"rgba": [0, 0, 0, 255]},
                },
                "lighting_enabled": True,
                "lights": {"slots": [{"decoded": {"colour": [255, 255, 255]}}]},
            }
        )
        self.assertEqual("requires-runtime-lighting-replay", k5_lit["status"])
        self.assertEqual([255 / 256.0] * 3 + [1.0], k5_lit["baseColorFactor"])
        k5_unlit = model_assets.translate_runtime_material_state(
            {
                "combine_mode": [0xFCFFFE8F, 0xF517F8FF],
                "convert_mode": [0xEC000000, 0x000000FF],
                "other_mode": [0xEF182C3F, 0x04D12078],
                "colours": {
                    "primitive": {"rgba": [0, 0, 0, 0]},
                    "environment": {"rgba": [0, 0, 0, 255]},
                },
                "lighting_enabled": False,
            }
        )
        self.assertEqual("exact-vertex-color-times-factor", k5_unlit["status"])
        primitive_alpha = model_assets.translate_runtime_material_state(
            {
                "combine_mode": [0xFCFF97FF, 0xFF2DFEFF],
                "other_mode": [0xEF082C3F, 0x00504DD8],
                "colours": {
                    "primitive": {"rgba": [0, 0, 0, 160]},
                    "environment": {"rgba": [0, 0, 0, 0]},
                },
                "lighting_enabled": False,
            }
        )
        self.assertEqual(
            "exact-runtime-color-times-texture-alpha",
            primitive_alpha["status"],
        )
        self.assertEqual([0.0, 0.0, 0.0, 160 / 255.0], primitive_alpha["baseColorFactor"])
        self.assertFalse(primitive_alpha["usesVertexColor"])
        separate_vertex_alpha = model_assets.translate_runtime_material_state(
            {
                "combine_mode": [0xFC127FFF, 0xFF17F23F],
                "other_mode": [0xEF18ACAF, 0x0C1849D8],
                "colours": {
                    "primitive": {"rgba": [0, 0, 0, 72]},
                    "environment": {"rgba": [0, 0, 0, 220]},
                },
                "lighting_enabled": False,
            }
        )
        self.assertEqual(
            "exact-texture-times-vertex-color", separate_vertex_alpha["status"]
        )
        self.assertEqual(
            [1.0, 1.0, 1.0, 220 / 255.0],
            separate_vertex_alpha["baseColorFactor"],
        )
        self.assertEqual("one", separate_vertex_alpha["vertexAlphaMode"])
        one_cycle_environment_alpha = model_assets.translate_runtime_material_state(
            {
                "combine_mode": [0xFC121A24, 0xFF37FFFF],
                "other_mode": [0xEF18ACAF, 0x0C1849D8],
                "colours": {
                    "primitive": {"rgba": [0, 0, 0, 0]},
                    "environment": {"rgba": [0, 0, 0, 174]},
                },
                "lighting_enabled": True,
                "lights": {"slots": [{"decoded": {"colour": [255, 255, 255]}}]},
            }
        )
        self.assertEqual(
            "requires-runtime-lighting-replay",
            one_cycle_environment_alpha["status"],
        )
        self.assertEqual(
            [1.0, 1.0, 1.0, 174 / 255.0],
            one_cycle_environment_alpha["baseColorFactor"],
        )
        self.assertEqual("one", one_cycle_environment_alpha["vertexAlphaMode"])
        one_cycle_texture_alpha = model_assets.translate_runtime_material_state(
            {
                "combine_mode": [0xFC127E24, 0x55FDF2F9],
                "other_mode": [0xEF08AC3E, 0x0F0A3238],
                "colours": {
                    "primitive": {"rgba": [0, 0, 0, 255]},
                    "environment": {"rgba": [0, 0, 0, 255]},
                },
                "lighting_enabled": False,
            }
        )
        self.assertEqual(
            "exact-texture-times-vertex-color",
            one_cycle_texture_alpha["status"],
        )
        self.assertEqual("one", one_cycle_texture_alpha["vertexAlphaMode"])
        two_cycle_translucent_environment = (
            model_assets.translate_runtime_material_state(
                {
                    "combine_mode": [0xFCFF9880, 0xF514FEFF],
                    "other_mode": [0xEF18AC3F, 0x04D12078],
                    "colours": {
                        "primitive": {"rgba": [0, 0, 0, 0]},
                        "environment": {"rgba": [0, 0, 0, 128]},
                    },
                    "lighting_enabled": False,
                }
            )
        )
        self.assertEqual(
            "exact-texture-times-vertex-color",
            two_cycle_translucent_environment["status"],
        )
        self.assertEqual(
            [1.0, 1.0, 1.0, 128 / 255.0],
            two_cycle_translucent_environment["baseColorFactor"],
        )
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
        multitexture = model_assets.translate_runtime_material_state(
            {
                "combine_mode": [0xFC111404, 0xFF13FFFF],
                "other_mode": [0xEF18AC3F, 0x0C184A50],
                "colours": {
                    "primitive": {"rgba": [0, 0, 0, 255]},
                    "environment": {"rgba": [0, 0, 0, 255]},
                },
                "lighting_enabled": False,
            }
        )
        self.assertEqual("unsupported-rdp-multitexture", multitexture["status"])
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
        task_gltf_data, _ = model_assets.encode_gltf(
            4,
            2,
            geometry,
            {
                model_assets.material_name(textured): "../textures/static.png",
                0: "../textures/runtime.png",
            },
        )
        task_gltf = json.loads(task_gltf_data)
        self.assertEqual("../textures/runtime.png", task_gltf["images"][0]["uri"])
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

    def test_captured_image_is_not_bound_when_combiner_has_no_texel_input(self):
        geometry = model_assets.parse_model_geometry(model_payload_with_material_runs())
        state = {
            "texture": {"enabled": True},
            "combine_mode": [0xFCFFFE8F, 0xF517F8FF],
            "other_mode": [0xEF18AC3F, 0x04D12078],
            "colours": {"primitive": {"rgba": [0, 0, 0, 0]},
                        "environment": {"rgba": [0, 0, 0, 255]}},
            "lighting_enabled": True,
        }
        translation = model_assets.translate_runtime_material_state(state)
        # K5 and lighting are missing, but neither cycle references a texel.
        self.assertEqual("unsupported-rdp-combiner", translation["status"])
        record = {
            "model_sha1": "source", "source_first_face": 0, "source_face_count": 1,
            "variant_count": 1, "observation_count": 1,
            "variants": [{"state": state, "gltf_translation": translation,
                          "captured_texture": {"file": "unused.png"}}],
        }
        self.assertFalse(model_assets.runtime_material_references_texels(record))
        self.assertIsNone(model_assets.runtime_captured_texture_choice(record))
        gltf, _ = model_assets.encode_gltf(
            0, 0, geometry, texture_files={0: "unused.png"}, runtime_materials={0: record}
        )
        document = json.loads(gltf)
        material = document["materials"][0]
        self.assertNotIn("baseColorTexture", material["pbrMetallicRoughness"])
        self.assertFalse(material["extras"]["runtimeMaterial"]["consensus"]["referencesTexels"])
        self.assertIn("COLOR_0", document["meshes"][0]["primitives"][0]["attributes"])
        self.assertNotIn("images", document)

        state["other_mode"] = [0xEF200000, 0]  # Copy mode bypasses the combiner.
        self.assertTrue(model_assets.runtime_material_references_texels(record))
        state["other_mode"] = None
        self.assertIsNone(model_assets.runtime_material_references_texels(record))
        state["other_mode"] = [0xEF18AC3F, 0x04D12078]
        # Alpha-only texturing and unresolved TEXEL1 expressions remain eligible.
        for pair in ([0xFCFF97FF, 0xFF2DFEFF], [0xFC111404, 0xFF13FFFF]):
            state["combine_mode"] = pair
            self.assertTrue(model_assets.runtime_material_references_texels(record))

    def test_exact_primitive_texture_alpha_omits_vertex_color(self):
        geometry = model_assets.parse_model_geometry(model_payload_with_material_runs())
        state = {
            "texture": {"enabled": True},
            "tiles": [],
            "combine_mode": [0xFCFF97FF, 0xFF2DFEFF],
            "other_mode": [0xEF082C3F, 0x00504DD8],
            "colours": {
                "primitive": {"rgba": [0, 0, 0, 160]},
                "environment": {"rgba": [0, 0, 0, 0]},
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
            "observation_count": 1,
            "variants": [
                {
                    "material_state_hash": "state-sha256",
                    "observation_count": 1,
                    "state": state,
                    "gltf_translation": translation,
                    "evidence": [],
                }
            ],
        }

        gltf_data, _ = model_assets.encode_gltf(
            0,
            0,
            geometry,
            texture_files={0: "../textures/alpha.png"},
            runtime_materials={0: runtime_material},
        )
        gltf = json.loads(gltf_data)

        self.assertNotIn("COLOR_0", gltf["meshes"][0]["primitives"][0]["attributes"])
        self.assertEqual(
            [0.0, 0.0, 0.0, 160 / 255.0],
            gltf["materials"][0]["pbrMetallicRoughness"]["baseColorFactor"],
        )

    def test_character_activity_trace_validates_live_pool_identity(self):
        session = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "session",
            "spec_name": "character-model-activity",
            "normalized_sha1": "rom-sha1",
            "tool_revisions": {},
        }
        active_record = {
            "slot": 2,
            "record_offset": 2 * model_assets.CHARACTER_POOL_RECORD_SIZE,
            "record_address": (
                model_assets.CHARACTER_POOL_ADDRESS
                + 2 * model_assets.CHARACTER_POOL_RECORD_SIZE
            ),
            "owner_address": 0x80100000,
            "entry": 73,
            "flags": 1,
            "animation_state_address": 0x80200000,
        }
        event = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "draw_state",
            "hit_index": 0,
            "render_state_hash": "state-hash",
            "state": {
                "model": {
                    "character_pool_address": model_assets.CHARACTER_POOL_ADDRESS,
                    "record_size": model_assets.CHARACTER_POOL_RECORD_SIZE,
                    "record_count": model_assets.CHARACTER_POOL_RECORD_COUNT,
                    "active_record_count": 1,
                    "active_entries": [73],
                    "active_records": [active_record],
                }
            },
        }
        with tempfile.TemporaryDirectory() as temporary:
            trace = Path(temporary) / "save-game-test.jsonl"
            trace.write_text(
                json.dumps(session) + "\n" + json.dumps(event) + "\n",
                encoding="utf-8",
            )

            decoded = model_assets.load_character_activity_trace(
                trace, "rom-sha1", {73}
            )

        self.assertEqual(1, decoded["snapshot_count"])
        self.assertEqual([73], decoded["snapshots"][0]["active_entries"])
        self.assertEqual(active_record, decoded["snapshots"][0]["active_records"][0])

    def test_activity_and_matrix_refine_one_ambiguous_character_material(self):
        session = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "session",
            "spec_name": "test",
            "normalized_sha1": "rom-sha1",
            "tool_revisions": {},
        }
        draw_state = {
            "texture": {"enabled": False},
            "tiles": [],
            "combine_mode": [0xFC121824, 0xFF33FFFF],
            "convert_mode": [0xEC000000, 0x000000FF],
            "other_mode": [0xEF000000, 0x00004000],
            "colours": {},
            "geometry_mode": 0,
            "lighting_enabled": False,
            "lights": [],
            "matrix": {"matrix_slot": 7},
        }
        candidates = [
            {
                "bank": 1,
                "entry": 115,
                "segment": 0,
                "model_sha1": "character-sha1",
                "material_run": {
                    "index": 2,
                    "first_face": 10,
                    "face_count": 3,
                    "matrix_index": 7,
                },
            },
            {
                "bank": 4,
                "entry": 8,
                "segment": 0,
                "model_sha1": "level-sha1",
                "material_run": {
                    "index": 1,
                    "first_face": 4,
                    "face_count": 3,
                    "matrix_index": None,
                },
            },
        ]
        event = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "draw_state",
            "state": {
                "joint_matrices": [],
                "rdp": {
                    "nested_display_lists": [],
                    "unresolved_display_list_targets": [],
                    "draw_runs": [
                        {
                            "material_state_hash": "draw-state",
                            "state": draw_state,
                        }
                    ],
                    "material_run_correlations": [
                        {
                            "status": "ambiguous",
                            "draw_run_indices": [0],
                            "candidates": candidates,
                        }
                    ],
                },
            },
        }
        inventory = {
            (1, 115, 0, 2): {
                "model_sha1": "character-sha1",
                "first_face": 10,
                "face_count": 3,
                "matrix_index": 7,
            },
            (4, 8, 0, 1): {
                "model_sha1": "level-sha1",
                "first_face": 4,
                "face_count": 3,
                "matrix_index": None,
            },
        }
        activity = {
            "schema_version": 1,
            "family": "runtime-character-model-activity",
            "normalized_sha1": "rom-sha1",
            "active_entries": [115],
            "source_traces": [
                {
                    "state": "save-game-18",
                    "snapshots": [{"active_entries": [115]}],
                }
            ],
        }
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            trace = root / "save-game-18.jsonl"
            trace.write_text(
                json.dumps(session) + "\n" + json.dumps(event) + "\n",
                encoding="utf-8",
            )
            activity_path = root / "activity.json"
            activity_path.write_text(json.dumps(activity), encoding="utf-8")
            with mock.patch.object(
                model_assets,
                "runtime_material_inventory",
                return_value=("rom-sha1", inventory),
            ):
                manifest = model_assets.extract_runtime_materials(
                    "us",
                    None,
                    (trace,),
                    root / "output",
                    False,
                    activity_path,
                )

        self.assertEqual(1, manifest["activity_refined_correlation_count"])
        self.assertEqual(1, manifest["activity_refined_draw_observation_count"])
        self.assertEqual(1, manifest["material_record_count"])
        self.assertEqual(115, manifest["materials"][0]["entry"])
        self.assertEqual(
            "runtime-active-character-matrix",
            manifest["materials"][0]["variants"][0]["evidence"][0][
                "material_correlation_status"
            ],
        )

    def test_activity_does_not_disprove_cross_bank_candidate_without_matrix(self):
        inventory = {
            (1, 115, 0, 2): {
                "model_sha1": "character-sha1",
                "first_face": 10,
                "face_count": 3,
                "matrix_index": 7,
            },
            (4, 8, 0, 1): {
                "model_sha1": "level-sha1",
                "first_face": 4,
                "face_count": 3,
                "matrix_index": None,
            },
        }
        candidates = [
            {
                "bank": key[0],
                "entry": key[1],
                "segment": key[2],
                "model_sha1": record["model_sha1"],
                "material_run": {
                    "index": key[3],
                    "first_face": record["first_face"],
                    "face_count": record["face_count"],
                    "matrix_index": record["matrix_index"],
                },
            }
            for key, record in inventory.items()
        ]

        resolved = model_assets.refine_character_material_candidates(
            candidates,
            {"state": {"matrix": {"matrix_slot": None}}},
            {115},
            inventory,
        )

        self.assertEqual(set(), resolved)

    def test_character_render_pass_requires_proven_callsite_and_mode(self):
        result = model_assets.character_render_pass(0x15185154, 3)
        self.assertEqual("render-to-texture", result["kind"])
        self.assertEqual((64, 8), (result["width"], result["storage_bits_per_pixel"]))
        for caller in (None, 0x1502CBD0, 0x15185150):
            self.assertEqual("caller-managed-target", model_assets.character_render_pass(caller, 3)["kind"])
        with self.assertRaisesRegex(ValueError, "no longer passes draw mode 3"):
            model_assets.character_render_pass(0x15185154, 1)

    def test_composition_keeps_render_texture_geometry_in_separate_files(self):
        data = character_model_payload()
        digest = hashlib.sha1(data).hexdigest()
        bundles = [model_assets.ModelBundle(
            index=entry, type_flags=16, compressed=True, data=data,
            segments=(model_assets.ModelSegment(0, 0, len(data), True, data),),
        ) for entry in (0, 4)]
        def composition(entry, render_pass):
            source = {"bank": 1, "entry": entry, "segment": 0, "model_sha1": digest}
            return {
                "entry": 0, "render_pass": render_pass,
                "sequence_source_models": [source],
                "resolved_clusters": [{**source, "static_cluster_index": 0,
                    "material_run": 0, "first_face": 0, "face_count": 1}],
                "model_sequence_status_counts": {"resolved": 1},
            }
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            activity = root / "activity.json"
            activity.write_text(json.dumps({
                "family": "runtime-character-model-activity", "normalized_sha1": "rom-sha1",
                "character_compositions": [composition(0, model_assets.character_render_pass(None, 1))],
                "render_texture_compositions": [composition(4, model_assets.character_render_pass(0x15185154, 3))],
            }))
            with mock.patch.object(model_assets, "load_model_bundles", return_value=(None, None, "rom-sha1", bundles, ())):
                manifest = model_assets.extract_character_composition_previews(
                    "us", None, activity, root / "output", False
                )
            self.assertEqual((1, 1), (manifest["model_count"], manifest["render_texture_model_count"]))
            normal, offscreen = manifest["models"][0], manifest["render_texture_models"][0]
            self.assertEqual(0, normal["source_models"][0]["entry"])
            self.assertEqual(4, offscreen["source_models"][0]["entry"])
            self.assertNotEqual(normal["gltf_file"], offscreen["gltf_file"])
            records = validate_model_previews_blender.collect_composition_records(root / "output")
            self.assertEqual({"composed-character", "render-to-texture-character"}, {r["kind"] for r in records})
            document = json.loads((root / "output" / offscreen["gltf_file"]).read_text())
            self.assertEqual("render-to-texture", document["extras"]["renderPass"]["kind"])

    def test_character_draw_trace_pairs_renderer_command_range(self):
        session = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "session",
            "spec_name": "character-model-draw-ranges",
            "normalized_sha1": "rom-sha1",
            "tool_revisions": {},
        }
        selected = {"slot": 3, "entry": 115}
        enter = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "draw_state",
            "breakpoint": "character-model-draw-enter",
            "hit_index": 0,
            "state": {
                "model": {
                    "draw_character_slot": 3,
                    "command_buffer_start": 0x80100000,
                    "root_matrix_address": 0x80200000,
                    "draw_argument_4": 0xFF,
                    "draw_argument_5": 0x80001000,
                    "draw_argument_6": 1,
                    "draw_argument_7": 0,
                    "active_records": [selected],
                }
            },
            "evidence": {"registers": {"sp": "0xFFFFFFFF80002000"}},
        }
        part_selection = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "draw_state",
            "breakpoint": "character-normal-part-selected",
            "hit_index": 1,
            "state": {
                "model": {
                    "display_model_index": 115,
                    "secondary_model_index": 115,
                    "draw_mode": 1,
                    "character_record_address": (
                        model_assets.CHARACTER_POOL_ADDRESS
                        + 3 * model_assets.CHARACTER_POOL_RECORD_SIZE
                    ),
                    "part_index": 2,
                    "part_table_slot_address": 0x800C4654,
                    "selected_display_list": 0x80123400,
                }
            },
            "evidence": {"registers": {"sp": "0xFFFFFFFF80001EB0"}},
        }
        leave = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "draw_state",
            "breakpoint": "character-model-draw-return",
            "hit_index": 2,
            "state": {
                "model": {"command_buffer_end": 0x801000C0},
                "joint_matrices": [
                    {
                        "address": 0x80200300,
                        "sha256": "matrix-sha256",
                        "layout": "cbfd-character-row-major-f32",
                        "status": "decoded-affine-components",
                        "rows": [[1.0, 0.0, 0.0, 0.0]] * 4,
                        "translation": [1.0, 2.0, 3.0],
                        "references": [
                            {
                                "segment": 3,
                                "segment_base_address": 0x80200000,
                                "segment_relative_matrix_slot": 12,
                                "matrix_slot": 12,
                            },
                            {
                                "segment": 3,
                                "segment_base_address": 0x80200300,
                                "segment_relative_matrix_slot": 0,
                                "matrix_slot": 0,
                            },
                        ],
                    }
                ],
                "rdp": {
                    "walked_display_lists": [
                        {
                            "address": 0x80123400,
                            "length": 0x88,
                            "sha256": "part-list-sha256",
                            "rdp": {"model_correlations": []},
                        }
                    ]
                },
            },
            "evidence": {
                "registers": {"sp": "0xFFFFFFFF80001EB0"},
                "memory": [
                    {
                        "name": "character-command-buffer",
                        "resolved_address": "0x80100000",
                        "length": 0xC0,
                        "sha256": "command-sha256",
                    }
                ],
            },
        }
        boundary = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "draw_state",
            "breakpoint": "character-draws-at-graphics-submit",
            "hit_index": 3,
            "state": {"model": {}},
            "evidence": {"registers": {"sp": "0xFFFFFFFF80003000"}},
        }
        raw_task = struct.pack(">I", 2) + bytes(60)
        second_boundary = {
            **boundary,
            "hit_index": 4,
            "evidence": {**boundary["evidence"], "memory": [{
                "name": "task", "length": 64,
                "data_base64": base64.b64encode(raw_task).decode(),
                "sha256": hashlib.sha256(raw_task).hexdigest(),
            }]},
        }
        with tempfile.TemporaryDirectory() as temporary:
            trace = Path(temporary) / "save-game-test.jsonl"
            trace.write_text(
                "\n".join(
                    json.dumps(item)
                    for item in (
                        session,
                        enter,
                        part_selection,
                        leave,
                        boundary,
                        second_boundary,
                    )
                )
                + "\n",
                encoding="utf-8",
            )
            decoded = model_assets.load_character_draw_trace(
                trace, "rom-sha1", {115}
            )

        self.assertEqual(1, decoded["draw_call_count"])
        self.assertEqual(2, decoded["task_submission_count"])
        self.assertEqual(0, decoded["graphics_task_submission_count"])
        self.assertEqual(1, decoded["non_graphics_task_submission_count"])
        self.assertEqual(1, decoded["untyped_task_submission_count"])
        self.assertEqual(115, decoded["draw_calls"][0]["entry"])
        self.assertEqual(0, decoded["draw_calls"][0]["task_submission_index"])
        self.assertEqual(2, decoded["draw_calls"][0]["return_event_index"])
        self.assertEqual(0xC0, decoded["draw_calls"][0]["command_byte_count"])
        self.assertEqual(1, decoded["draw_calls"][0]["part_selection_count"])
        self.assertEqual(1, decoded["draw_calls"][0]["runtime_matrix_count"])
        self.assertEqual(
            12, decoded["draw_calls"][0]["runtime_matrices"][0]["matrix_slot"]
        )
        self.assertEqual(
            {
                "event_index": 1,
                "hit_index": 1,
                "table": "normal",
                "display_model_index": 115,
                "secondary_model_index": 115,
                "draw_mode": 1,
                "part_index": 2,
                "part_table_slot_address": 0x800C4654,
                "selected_display_list": 0x80123400,
                "display_list_sha256": "part-list-sha256",
                "display_list_byte_count": 0x88,
                "model_correlation_count": 0,
                "model_sequence_resolution": {
                    "status": "no-model-correlations",
                    "resolved_clusters": [],
                },
            },
            decoded["draw_calls"][0]["part_selections"][0],
        )

    def test_character_part_table_trace_redecodes_exact_payloads(self):
        pointers = bytearray(model_assets.CHARACTER_PART_POINTER_TABLE_SIZE)
        counts = bytearray(model_assets.CHARACTER_PART_COUNT_TABLE_SIZE)
        extra = bytearray(model_assets.CHARACTER_PART_POINTER_TABLE_SIZE)
        struct.pack_into(">I", pointers, 4 * 90, 0x8022E818)
        struct.pack_into(">H", counts, 2 * 90, 4)
        decoded_tables = model_assets.decode_cbfd_character_part_table_headers(
            bytes(pointers), bytes(counts), bytes(extra)
        )

        def probe(name, address, payload):
            return {
                "name": name,
                "resolved_address": f"0x{address:08X}",
                "length": len(payload),
                "sha256": hashlib.sha256(payload).hexdigest(),
                "data_base64": base64.b64encode(payload).decode("ascii"),
            }

        session = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "session",
            "spec_name": "character-model-part-tables",
            "normalized_sha1": "rom-sha1",
            "tool_revisions": {},
        }
        event = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "draw_state",
            "breakpoint": "character-part-tables-at-graphics-submit",
            "state": {"model": {"part_tables": decoded_tables}},
            "evidence": {
                "memory": [
                    probe("character-part-pointer-table", 0x800C4488, pointers),
                    probe("character-part-count-table", 0x800C4778, counts),
                    probe("character-extra-part-pointer-table", 0x800C48F0, extra),
                ]
            },
        }
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / "part-tables.jsonl"
            path.write_text(
                json.dumps(session) + "\n" + json.dumps(event) + "\n",
                encoding="utf-8",
            )
            decoded = model_assets.load_character_part_table_trace(
                path, "rom-sha1"
            )

        self.assertEqual(1, decoded["table_record_count"])
        self.assertEqual(90, decoded["part_tables"][0]["model_index"])
        self.assertEqual(4, decoded["part_tables"][0]["part_count"])

    def test_runtime_material_appearance_lookup_uses_trace_content_identity(self):
        manifest = {
            "schema_version": 1,
            "family": "runtime-correlated-model-materials",
            "normalized_sha1": "rom-sha1",
            "source_traces": [
                {
                    "trace_index": 7,
                    "sha256": "draw-trace-sha256",
                }
            ],
            "appearances": [
                {
                    "trace_index": 7,
                    "event_index": 3,
                }
            ],
        }
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / "manifest.json"
            path.write_text(json.dumps(manifest), encoding="utf-8")

            lookup = model_assets.load_runtime_material_appearance_lookup(
                path, "rom-sha1"
            )

        self.assertEqual(
            {("draw-trace-sha256", 3): (7, 3)},
            lookup,
        )

    def test_character_model_sequence_resolves_aliases_by_static_order(self):
        def candidate(entry, cluster):
            return {
                "bank": 1,
                "entry": entry,
                "segment": 0,
                "model_sha1": f"model-{entry}",
                "static_cluster_index": cluster,
                "static_first_face": cluster * 3,
                "triangle_count": 3,
                "material_run": {"index": 2, "matrix_index": 4},
            }

        resolved = model_assets.resolve_character_model_sequence(
            [
                {"candidates": [candidate(4, 5), candidate(4, 8)]},
                {"candidates": [candidate(4, 6), candidate(4, 9)]},
                {"candidates": [candidate(4, 7)]},
            ]
        )

        self.assertEqual("resolved", resolved["status"])
        self.assertEqual(4, resolved["source_model"]["entry"])
        self.assertEqual(
            [5, 6, 7],
            [item["static_cluster_index"] for item in resolved["resolved_clusters"]],
        )
        self.assertEqual(9, resolved["resolved_face_count"])

    def test_character_model_sequence_uses_exact_renderer_model_index(self):
        def candidate(bank, entry, cluster):
            return {
                "bank": bank,
                "entry": entry,
                "segment": 0,
                "model_sha1": f"model-{bank}-{entry}",
                "static_cluster_index": cluster,
                "static_first_face": cluster * 3,
                "triangle_count": 3,
                "material_run": {"index": cluster, "matrix_index": 4},
            }

        resolved = model_assets.resolve_character_model_sequence(
            [
                {"candidates": [candidate(1, 90, 5), candidate(4, 8, 2)]},
                {"candidates": [candidate(1, 90, 6), candidate(4, 8, 3)]},
            ],
            expected_bank_entry=(1, 90),
        )

        self.assertEqual("resolved", resolved["status"])
        self.assertEqual(90, resolved["source_model"]["entry"])
        self.assertEqual(
            [5, 6],
            [item["static_cluster_index"] for item in resolved["resolved_clusters"]],
        )

    def test_character_model_sequence_uses_exact_rom_part_list(self):
        def candidate(cluster):
            return {
                "bank": 1,
                "entry": 130,
                "segment": 0,
                "model_sha1": "model-130",
                "static_cluster_index": cluster,
                "static_first_face": cluster * 3,
                "triangle_count": 3,
                "material_run": {"index": cluster, "matrix_index": 4},
            }

        resolved = model_assets.resolve_character_model_sequence(
            [
                {"candidates": [candidate(29), candidate(67)]},
                {"candidates": [candidate(30), candidate(68)]},
            ],
            expected_bank_entry=(1, 130),
            expected_static_cluster_indices={29, 30},
        )

        self.assertEqual("resolved", resolved["status"])
        self.assertEqual(
            [29, 30],
            [item["static_cluster_index"] for item in resolved["resolved_clusters"]],
        )

    def test_selected_part_materials_disambiguate_sibling_lists_with_the_same_matrix(self):
        source = {"bank": 1, "entry": 130, "segment": 0, "model_sha1": "source"}
        candidates = [{**source, "static_cluster_index": index, "static_first_face": first,
                       "triangle_count": 4,
                       "material_run": {"index": index, "first_face": first, "face_count": 4,
                                        "matrix_index": 12}}
                      for index, first in ((3, 10), (7, 90))]
        inventory = {(1, 130, 0, c["material_run"]["index"]):
                     {"model_sha1": "source", **c["material_run"]} for c in candidates}
        correlation = {"runtime_cluster_index": 5, "candidates": candidates}
        sequence = model_assets.resolve_character_model_sequence(
            [correlation], expected_bank_entry=(1, 130), expected_static_cluster_indices={3})
        call = {"return_event_index": 8, "command_sha256": "commands",
                "model_correlations": [correlation], "part_selections": [
                    {"event_index": 7, "model_correlation_count": 1,
                     "model_sequence_resolution": sequence}]}
        trace = {"draw_calls": [call]}
        # An active entry and a matching matrix alone cannot choose the list.
        self.assertEqual(set(), model_assets.refine_character_material_candidates(
            candidates, {"state": {"matrix": {"matrix_slot": 12}}}, {130}, inventory))
        selected = model_assets.selected_part_material_candidates(trace, inventory)
        self.assertEqual(candidates[0], selected[8][5]["candidate"])
        self.assertEqual([7], selected[8][5]["evidence"]["part_selection_event_indices"])
        self.assertEqual(3, selected[8][5]["evidence"]["static_cluster_index"])
        schema = "conker.model-draw-state-trace/v1"
        session = {"schema": schema, "record_type": "session", "normalized_sha1": "rom",
                   "spec_name": "character-model-draw-ranges"}
        event = {"schema": schema, "record_type": "draw_state", "state": {"rdp": {
            "model_correlations": [correlation],
            "material_run_correlations": [{**correlation, "status": "ambiguous", "draw_run_indices": [0]}],
            "draw_runs": [{"triangle_count": 4, "state": {"texture": {}, "tiles": [],
                "colours": {}, "geometry_mode": 0, "lighting_enabled": False,
                "matrix": {"matrix_slot": 12}}}],
        }}}
        validated = {"draw_calls": [{**call, "return_event_index": 0}]}
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            path = root / "trace.jsonl"
            path.write_text(json.dumps(session) + "\n" + json.dumps(event) + "\n")
            with (mock.patch.object(model_assets, "runtime_material_inventory", return_value=("rom", inventory)),
                  mock.patch.object(model_assets, "load_model_bundles", return_value=(None, None, "rom", (), None)),
                  mock.patch.object(model_assets, "character_display_list_topology", return_value={}),
                  mock.patch.object(model_assets, "load_character_draw_trace", return_value=validated)):
                manifest = model_assets.extract_runtime_materials("us", None, (path,), root / "output", False)
        self.assertEqual(1, manifest["material_record_count"])
        self.assertEqual(3, manifest["materials"][0]["material_run"])
        evidence = manifest["materials"][0]["variants"][0]["evidence"][0]
        self.assertEqual((10, 4), (evidence["source_first_face"], evidence["source_face_count"]))
        self.assertEqual("renderer-selected-part-sequence", evidence["material_correlation_status"])
        self.assertEqual(3, evidence["renderer_part_sequence"]["static_cluster_index"])
        call["model_correlations"] = []
        with self.assertRaisesRegex(ValueError, "does not cover"):
            model_assets.selected_part_material_candidates(trace, inventory)
        call["model_correlations"] = [correlation]
        candidates[0]["static_first_face"] += 1
        with self.assertRaisesRegex(ValueError, "no exact renderer correlation"):
            model_assets.selected_part_material_candidates(trace, inventory)
        candidates[0]["static_first_face"] -= 1
        inventory[(1, 130, 0, 3)]["model_sha1"] = "changed"
        with self.assertRaisesRegex(ValueError, "model hash changed"):
            model_assets.selected_part_material_candidates(trace, inventory)

    def test_character_call_sequence_combines_exact_part_lists(self):
        def sequence(*clusters):
            return {
                "status": "resolved",
                "source_model": {
                    "bank": 1,
                    "entry": 130,
                    "segment": 0,
                    "model_sha1": "model-130",
                },
                "resolved_clusters": [
                    {
                        "static_cluster_index": cluster,
                        "first_face": cluster * 3,
                        "face_count": 3,
                        "material_run": cluster,
                        "matrix_index": 4,
                    }
                    for cluster in clusters
                ],
            }

        resolved = model_assets.resolve_character_call_from_part_selections(
            [
                {
                    "model_correlation_count": 2,
                    "model_sequence_resolution": sequence(29, 30),
                },
                {
                    "model_correlation_count": 1,
                    "model_sequence_resolution": sequence(31),
                },
            ]
        )

        self.assertIsNotNone(resolved)
        self.assertEqual(
            "renderer-model-header-pointer-table", resolved["resolution_basis"]
        )
        self.assertEqual(
            [29, 30, 31],
            [
                item["static_cluster_index"]
                for item in resolved["resolved_clusters"]
            ],
        )
        self.assertEqual(9, resolved["resolved_face_count"])

    def test_character_part_order_resolves_single_cluster_alias(self):
        def candidate(cluster):
            return {
                "bank": 1,
                "entry": 90,
                "segment": 0,
                "model_sha1": "model-90",
                "static_cluster_index": cluster,
                "static_first_face": cluster * 3,
                "triangle_count": 3,
                "material_run": {"index": cluster, "matrix_index": 4},
            }

        selections = [
            {
                "display_model_index": 90,
                "model_correlation_count": 1,
                "_model_correlations": [{"candidates": [candidate(0)]}],
            },
            {
                "display_model_index": 90,
                "model_correlation_count": 1,
                "_model_correlations": [
                    {"candidates": [candidate(1), candidate(5)]}
                ],
            },
            {
                "display_model_index": 90,
                "model_correlation_count": 1,
                "_model_correlations": [{"candidates": [candidate(2)]}],
            },
        ]

        model_assets.resolve_character_part_selection_sequence(selections)

        self.assertTrue(
            all(
                item["model_sequence_resolution"]["status"] == "resolved"
                for item in selections
            )
        )
        self.assertEqual(
            1,
            selections[1]["model_sequence_resolution"]["resolved_clusters"][0][
                "static_cluster_index"
            ],
        )
        self.assertNotIn("_model_correlations", selections[1])

    def test_bakes_character_runtime_pose_and_centers_root_translation(self):
        geometry = model_assets.parse_model_geometry(model_payload())
        geometry = replace(
            geometry,
            material_runs=(
                replace(geometry.material_runs[0], matrix_index=1),
            ),
            face_matrix_indices=((1, 1, 1),),
        )
        rows = [
            [2.0, 0.0, 0.0, 0.0],
            [0.0, 2.0, 0.0, 0.0],
            [0.0, 0.0, 2.0, 0.0],
            [110.0, 220.0, 330.0, 1.0],
        ]

        posed = model_assets.bake_character_runtime_pose(
            geometry,
            {1: rows},
            [100.0, 200.0, 300.0],
        )

        self.assertEqual((10.0, 20.0, 30.0), (posed.vertices[0].x, posed.vertices[0].y, posed.vertices[0].z))
        self.assertEqual((30.0, 20.0, 30.0), (posed.vertices[1].x, posed.vertices[1].y, posed.vertices[1].z))
        self.assertEqual(geometry.faces, posed.faces)
        self.assertEqual((), posed.face_normal_bytes)

    def test_blender_validator_collects_neutral_and_posed_compositions(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / "neutral.gltf").write_text("{}", encoding="utf-8")
            (root / "posed.gltf").write_text("{}", encoding="utf-8")
            (root / "manifest.json").write_text(
                json.dumps(
                    {
                        "family": "runtime-character-model-composition-preview",
                        "model_count": 1,
                        "models": [{"gltf_file": "neutral.gltf"}],
                        "posed_model_count": 1,
                        "posed_models": [{"gltf_file": "posed.gltf"}],
                    }
                ),
                encoding="utf-8",
            )

            records = validate_model_previews_blender.collect_composition_records(
                root
            )

        self.assertEqual(
            ["composed-character", "posed-composed-character"],
            [record["kind"] for record in records],
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
        self.assertEqual(0, manifest["appearance_count"])
        self.assertEqual(0, manifest["source_traces"][0]["trace_index"])
        self.assertEqual(3, manifest["segment_8_display_list_call_count"])
        self.assertEqual(3, manifest["resolved_segment_8_display_list_call_count"])
        self.assertEqual(2, manifest["resolved_segment_8_display_list_count"])
        self.assertEqual(
            ["0x80083140", "0x80083180"],
            manifest["resolved_segment_8_display_list_addresses"],
        )

    def test_backfills_convert_mode_from_retained_command_buffer(self):
        commands = b"".join(
            struct.pack(">II", command, argument)
            for command, argument in (
                (0xEC15FDF0, 0x3B78E42A),
                (0x05000204, 0),
                (0xDF000000, 0),
            )
        )
        run = model_assets.decode_f3dex2_cbfd(commands)["rdp"]["draw_runs"][0]
        del run["state"]["convert_mode"]
        event = {
            "state": {"rdp": {"draw_runs": [run]}},
            "evidence": {
                "memory": [
                    {
                        "name": "command-buffer",
                        "data_base64": base64.b64encode(commands).decode("ascii"),
                    }
                ]
            },
        }

        model_assets.backfill_runtime_convert_modes(event)

        self.assertEqual(
            [0xEC15FDF0, 0x3B78E42A],
            event["state"]["rdp"]["draw_runs"][0]["state"]["convert_mode"],
        )

    def test_submission_link_requires_executed_bytes_and_uses_final_matrices(self):
        def probe(name, address, raw):
            return {"name": name, "resolved_address": hex(address), "length": len(raw),
                    "data_base64": base64.b64encode(raw).decode(),
                    "sha256": hashlib.sha256(raw).hexdigest()}
        start, matrix_address = 0x80100008, 0x80102000
        raw = struct.pack(">4I", 0xDA380003, matrix_address, 0xDE000000, 0x80104000)
        root = bytes(8) + raw + struct.pack(">2I", 0xDF000000, 0)
        task = bytearray(64)
        struct.pack_into(">I", task, 0, 1)
        struct.pack_into(">2I", task, 48, start - 8, len(root))
        identity = [[float(i == j) for j in range(4)] for i in range(4)]
        fixed = struct.pack(">16h16H", *(int(v) for row in identity for v in row), *([0] * 16))
        original = [row[:] for row in identity]; original[0][0] = 2.0
        returned = {"state": {"rdp": {"draw_runs": [{"triangle_count": 1}]}},
                    "evidence": {"memory": [probe("character-command-buffer", start, raw)]}}
        submitted = {"state": {"rdp": {
            "replayed_command_origins": [[start-8], [start], [start+8], [start+8, 0x80104000], [start+16]],
            "draw_runs": [{"command_offset": 24, "triangle_count": 1}]}},
            "evidence": {"memory": [probe("task", 0x80001000, task),
                probe("command-buffer", start-8, root), probe("runtime-matrix-0", matrix_address, fixed)]}}
        audio = {"evidence": {"memory": [probe("task", 0x80001000, struct.pack(">I", 2) + bytes(60))]}}
        call = {"return_event_index": 0, "command_buffer_start": start, "command_buffer_end": start+16,
                "runtime_matrices": [{"matrix_slot": 0, "address": matrix_address, "rows": original}]}
        result = model_assets.link_character_graphics_submission([returned, audio, submitted], call)
        self.assertEqual(2, result["event_index"])
        self.assertEqual([0], result["matrices_changed_after_return"])
        self.assertEqual(identity, result["runtime_matrices"][0]["rows"])
        # A repeated physical range is not a unique submitted instance.
        submitted["state"]["rdp"]["replayed_command_origins"].append([start])
        self.assertIsNone(model_assets.link_character_graphics_submission([returned, submitted], call))
        submitted["state"]["rdp"]["replayed_command_origins"].pop()
        # A nearby buffer with changed commands is insufficient even if rehashed.
        submitted["evidence"]["memory"][1] = probe("command-buffer", start-8, bytes(len(root)))
        self.assertIsNone(model_assets.link_character_graphics_submission([returned, submitted], call))
        submitted["evidence"]["memory"][1] = probe("command-buffer", start-8, root)
        struct.pack_into(">I", task, 48, 0x80120000)
        submitted["evidence"]["memory"][0] = probe("task", 0x80001000, task)
        self.assertIsNone(model_assets.link_character_graphics_submission([returned, submitted], call))

    def test_material_command_range_separates_instances_in_the_same_task(self):
        variants = [{"material_state_hash": str(i), "evidence": [{
            "trace_index": 0, "event_index": 7, "command_path": [address, 0x80200000]}]}
            for i, address in enumerate((0x80100000, 0x80100100))]
        manifest = {"schema_version": 1, "family": "runtime-correlated-model-materials",
            "normalized_sha1": "rom", "material_record_count": 1,
            "appearances": [{"trace_index": 0, "event_index": 7}],
            "materials": [{"bank": 1, "entry": 90, "segment": 0, "material_run": 0, "variants": variants}]}
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / "manifest.json"; path.write_text(json.dumps(manifest))
            selected = model_assets.load_runtime_material_catalog(
                path, "rom", (0, 7), command_range=(0x80100000, 0x80100008))
            self.assertEqual("0", selected[(1, 90, 0, 0)]["variants"][0]["material_state_hash"])
            self.assertEqual(1, selected[(1, 90, 0, 0)]["variant_count"])
            with self.assertRaises(ValueError):
                model_assets.load_runtime_material_catalog(path, "rom", command_range=(0x80100000, 0x80100008))

    def test_runtime_appearance_filters_variants_and_lighting_contexts(self):
        context_a = {
            "lighting_context_hash": "context-a",
            "observation_count": 1,
        }
        context_b = {
            "lighting_context_hash": "context-b",
            "observation_count": 1,
        }
        manifest = {
            "schema_version": 1,
            "family": "runtime-correlated-model-materials",
            "normalized_sha1": "rom-sha1",
            "material_record_count": 1,
            "appearances": [
                {"trace_index": 2, "event_index": 4},
                {"trace_index": 3, "event_index": 0},
            ],
            "materials": [
                {
                    "bank": 1,
                    "entry": 0,
                    "segment": 0,
                    "material_run": 0,
                    "variant_count": 2,
                    "observation_count": 2,
                    "variants": [
                        {
                            "material_state_hash": "state-a",
                            "observation_count": 1,
                            "lighting_context_count": 2,
                            "lighting_contexts": [context_a, context_b],
                            "evidence": [
                                {
                                    "trace_index": 2,
                                    "event_index": 4,
                                    "lighting_context_hash": "context-a",
                                }
                            ],
                        },
                        {
                            "material_state_hash": "state-b",
                            "observation_count": 1,
                            "lighting_context_count": 0,
                            "lighting_contexts": [],
                            "evidence": [
                                {
                                    "trace_index": 3,
                                    "event_index": 0,
                                    "lighting_context_hash": None,
                                }
                            ],
                        },
                    ],
                }
            ],
        }
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / "manifest.json"
            path.write_text(json.dumps(manifest), encoding="utf-8")
            catalog = model_assets.load_runtime_material_catalog(
                path, "rom-sha1", (2, 4)
            )
        record = catalog[(1, 0, 0, 0)]
        self.assertEqual(1, record["variant_count"])
        self.assertEqual("state-a", record["variants"][0]["material_state_hash"])
        self.assertEqual([context_a], record["variants"][0]["lighting_contexts"])

    def test_runtime_material_manifest_indexes_captured_appearances(self):
        session = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "session",
            "spec_name": "appearance-test",
            "normalized_sha1": "rom-sha1",
            "tool_revisions": {},
        }
        event = {
            "schema": "conker.model-draw-state-trace/v1",
            "record_type": "draw_state",
            "hit_index": 7,
            "render_state_hash": "render-state",
            "state": {
                "joint_matrices": [],
                "rdp": {
                    "nested_display_lists": [],
                    "unresolved_display_list_targets": [],
                    "draw_runs": [
                        {
                            "material_state_hash": "draw-state",
                            "state": {
                                "texture": {"enabled": False},
                                "tiles": [],
                                "combine_mode": [0xFC121824, 0xFF33FFFF],
                                "convert_mode": [0xEC000000, 0x000000FF],
                                "other_mode": [0xEF000000, 0x00004000],
                                "colours": {},
                                "geometry_mode": 0,
                                "lighting_enabled": False,
                                "lights": [],
                            },
                        }
                    ],
                    "material_run_correlations": [
                        {
                            "status": "unique",
                            "draw_run_indices": [0],
                            "candidates": [
                                {
                                    "bank": 1,
                                    "entry": 2,
                                    "segment": 0,
                                    "model_sha1": "model-sha1",
                                    "material_run": {
                                        "index": 0,
                                        "first_face": 3,
                                        "face_count": 4,
                                        "matrix_index": 5,
                                    },
                                }
                            ],
                        }
                    ],
                },
            },
        }
        inventory = {
            (1, 2, 0, 0): {
                "model_sha1": "model-sha1",
                "first_face": 3,
                "face_count": 4,
                "matrix_index": 5,
            }
        }
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            trace = root / "trace.jsonl"
            raw_task = struct.pack(">I", 2) + bytes(60)
            audio_event = {**event, "evidence": {"memory": [{"name": "task", "length": 64,
                "data_base64": base64.b64encode(raw_task).decode(),
                "sha256": hashlib.sha256(raw_task).hexdigest()}]}}
            trace.write_text(
                "\n".join(json.dumps(item) for item in (session, event, audio_event)) + "\n",
                encoding="utf-8",
            )
            with mock.patch.object(
                model_assets,
                "runtime_material_inventory",
                return_value=("rom-sha1", inventory),
            ):
                manifest = model_assets.extract_runtime_materials(
                    "us", None, (trace,), root / "output", False
                )
        self.assertEqual(1, manifest["appearance_count"])
        self.assertEqual(1, manifest["source_traces"][0]["ignored_non_graphics_task_count"])
        self.assertEqual(1, manifest["convert_mode_variant_count"])
        self.assertEqual(0, manifest["missing_convert_mode_variant_count"])
        self.assertEqual(1, manifest["convert_mode_count"])
        appearance = manifest["appearances"][0]
        self.assertEqual("trace-000-event-000", appearance["id"])
        self.assertEqual(1, appearance["material_record_count"])
        self.assertEqual(1, appearance["variant_count"])
        self.assertEqual([{"bank": 1, "entries": [2]}], appearance["bank_entries"])
        evidence = manifest["materials"][0]["variants"][0]["evidence"][0]
        self.assertEqual(0, evidence["trace_index"])
        self.assertEqual(0, evidence["event_index"])

    def test_runtime_appearance_parser_rejects_malformed_selector(self):
        self.assertEqual((12, 3), model_assets.parse_runtime_appearance("12:3"))
        with self.assertRaises(argparse.ArgumentTypeError):
            model_assets.parse_runtime_appearance("12")

    def test_invalid_runtime_trace_does_not_delete_existing_forced_output(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            trace = root / "invalid.jsonl"
            trace.write_text('{}\n', encoding="utf-8")
            output = root / "output"
            output.mkdir()
            sentinel = output / "sentinel.txt"
            sentinel.write_text("preserve", encoding="utf-8")
            with mock.patch.object(
                model_assets,
                "runtime_material_inventory",
                return_value=("rom-sha1", {}),
            ):
                with self.assertRaisesRegex(ValueError, "no session record"):
                    model_assets.extract_runtime_materials(
                        "us", None, (trace,), output, True
                    )
            self.assertEqual("preserve", sentinel.read_text(encoding="utf-8"))

    def test_composes_task_local_ci4_texture_from_captured_rdram(self):
        run = model_assets.ModelMaterialRun(
            first_face=0,
            face_count=1,
            texture_enabled=True,
            pixel=None,
            palette=None,
            render_tile=(0xF5000800, 0x00054160),
            render_tiles=(),
            tile_bounds=(0xF2002002, 0x000FE07E),
            texture_scale=(0xD7000002, 0xFFFFFFFF),
            combine_mode=None,
            other_mode=None,
            runtime_render_state_offset=None,
        )
        pixels = bytes(index & 0xFF for index in range(1024))
        palette = b"".join(
            struct.pack(">H", (index << 11) | 1) for index in range(16)
        ) + bytes(0x200 - 0x20)
        captured = model_assets.runtime_captured_preview_texture(
            run,
            {
                "other_mode": [0xEF18AC3F, 0x0C184DD8],
                "texture": {
                    "pixel_image": {
                        "captured_texture_image_index": 3,
                        "sha256": "pixel-sha256",
                    },
                    "palette_image": {
                        "captured_texture_image_index": 4,
                        "sha256": "palette-sha256",
                    },
                }
            },
            {3: pixels, 4: palette},
        )

        self.assertIsNotNone(captured)
        self.assertEqual("ci4", captured["format"])
        decoded = texture_assets.decode_indexed_png(
            captured["png_data"], "linear", 64, 32
        )
        self.assertEqual(1024 + 0x20, len(decoded))
        self.assertEqual(palette[:0x20], decoded[-0x20:])
        self.assertEqual(1, captured["mip_level_count"])

    def test_captured_palette_disabled_formats_ignore_retained_tlut(self):
        for command, expected_format, first_pixel in (
            (0xF5080200, "i8", bytes((0xA3,) * 4)),
            (0xF5880200, "i8", bytes((0xA3,) * 4)),
            (0xF5680200, "ia8", bytes((0xAA, 0xAA, 0xAA, 0x33))),
            (0xF5000200, "i4", bytes((0xAA,) * 4)),
        ):
            with self.subTest(format=expected_format, command=command):
                run = model_assets.ModelMaterialRun(
                    first_face=0, face_count=1, texture_enabled=True,
                    pixel=None, palette=None, render_tile=(command, 0),
                    render_tiles=(), tile_bounds=(0xF2000000, 0x0001C000),
                    texture_scale=(0xD7000002, 0xFFFFFFFF), combine_mode=None,
                    other_mode=None, runtime_render_state_offset=None,
                )
                state = {
                    "other_mode": [0xEF182C3F, 0x07C24000],
                    "texture": {
                        "enabled": True,
                        "pixel_image": {"captured_texture_image_index": 3},
                    },
                }
                captured = model_assets.runtime_captured_preview_texture(
                    run, state, {3: bytes((0xA3,)) * 8}
                )
                self.assertIsNotNone(captured)
                self.assertEqual(expected_format, captured["format"])
                self.assertEqual("runtime-captured-native-texture", captured["status"])
                self.assertIsNone(captured["palette_sha256"])
                rgba = texture_assets.decode_rgba_png_pixels(captured["png_data"], 8, 1)
                self.assertEqual(first_pixel, rgba[:4])
                state["texture"]["palette_image"] = {
                    "captured_texture_image_index": 4, "sha256": "irrelevant",
                }
                with_palette = model_assets.runtime_captured_preview_texture(
                    run, state, {3: bytes((0xA3,)) * 8, 4: bytes(512)}
                )
                self.assertEqual(captured["png_data"], with_palette["png_data"])

    def test_captured_format_requires_mode_and_compatible_runtime_coordinates(self):
        run = model_assets.ModelMaterialRun(
            first_face=0, face_count=1, texture_enabled=True,
            pixel=None, palette=None, render_tile=(0xF5080200, 0),
            render_tiles=(), tile_bounds=(0xF2000000, 0x0001C000),
            texture_scale=(0xD7000002, 0xFFFFFFFF), combine_mode=None,
            other_mode=None, runtime_render_state_offset=None,
        )
        state = {"texture": {
            "pixel_image": {"captured_texture_image_index": 3},
            "palette_image": {"captured_texture_image_index": 4},
        }}
        payloads = {3: bytes(64), 4: bytes(512)}
        self.assertIsNone(model_assets.runtime_captured_preview_texture(run, state, payloads))
        state["other_mode"] = [0xEF18EC3F, 0]  # IA16 TLUT is not RGBA5551.
        self.assertIsNone(model_assets.runtime_captured_preview_texture(run, state, payloads))
        state["other_mode"] = [0xEF182C3F, 0]
        for command, argument in ((0xF5180200, 0), (0xF5080200, 0x10)):
            state["tiles"] = [{"index": 0, "command": command, "argument": argument}]
            self.assertIsNone(model_assets.runtime_captured_preview_texture(run, state, payloads))
        state["tiles"] = []
        state["texture"]["enabled"] = False
        self.assertIsNone(model_assets.runtime_captured_preview_texture(run, state, payloads))

    def test_captured_runtime_tile_selects_native_format(self):
        run = model_assets.ModelMaterialRun(
            first_face=0, face_count=1, texture_enabled=True,
            pixel=None, palette=None, render_tile=(0xF5080200, 0),
            render_tiles=(), tile_bounds=(0xF2000000, 0x0001C000),
            texture_scale=(0xD7000002, 0xFFFFFFFF), combine_mode=None,
            other_mode=None, runtime_render_state_offset=None,
        )
        captured = model_assets.runtime_captured_preview_texture(run, {
            "other_mode": [0xEF182C3F, 0],
            "texture": {"pixel_image": {"captured_texture_image_index": 3}},
            "tiles": [{"index": 0, "command": 0xF5680200, "argument": 0}],
        }, {3: bytes((0xA3,)) * 8})
        self.assertEqual("ia8", captured["format"])
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            output = root / captured["file"]
            output.parent.mkdir(parents=True)
            output.write_bytes(captured["png_data"])
            selected = model_assets.runtime_captured_texture_choice({
                "_source_root": root, "variants": [{"captured_texture": captured}],
            })
            self.assertEqual((3, 1), (selected.format, selected.size))

    def test_composes_task_local_ci8_mip_levels_from_captured_rdram(self):
        run = model_assets.ModelMaterialRun(
            first_face=0,
            face_count=1,
            texture_enabled=True,
            pixel=None,
            palette=None,
            render_tile=(0xF5080200, 0x00008030),
            render_tiles=(),
            tile_bounds=(0xF2000000, 0x0001C004),
            texture_scale=(0xD7000802, 0xFFFFFFFF),
            combine_mode=None,
            other_mode=None,
            runtime_render_state_offset=None,
        )
        pixels = bytes(range(36))
        palette = b"".join(
            struct.pack(">H", (index << 8) | 1) for index in range(256)
        )
        captured = model_assets.runtime_captured_preview_texture(
            run,
            {
                "other_mode": [0xEF18AC3F, 0x0C184DD8],
                "texture": {
                    "scale": [0xD7000802, 0xFFFFFFFF],
                    "pixel_image": {
                        "captured_texture_image_index": 3,
                        "sha256": "pixel-sha256",
                    },
                    "palette_image": {
                        "captured_texture_image_index": 4,
                        "sha256": "palette-sha256",
                    },
                },
                "tiles": [
                    {"index": 0, "command": 0xF5080200, "argument": 0x00008030},
                    {"index": 1, "command": 0xF5080204, "argument": 0x01004020},
                ],
            },
            {3: pixels, 4: palette},
        )

        self.assertIsNotNone(captured)
        self.assertEqual(2, captured["mip_level_count"])
        self.assertEqual(1, len(captured["mip_levels"]))
        mip = captured["mip_levels"][0]
        self.assertEqual((1, 4, 1, 32), (
            mip["level"], mip["width"], mip["height"], mip["tmem_byte_offset"]
        ))
        decoded = texture_assets.decode_ci8_png(mip["png_data"], "linear", 4, 1)
        self.assertEqual(pixels[32:36], decoded[:4])

    def test_composes_detail_texture_and_texel1_mip_chain(self):
        run = model_assets.ModelMaterialRun(
            first_face=0,
            face_count=1,
            texture_enabled=True,
            pixel=model_assets.ModelTextureBinding(
                image_command=0xFD500000,
                load_command=(0xF3000000, 0x07000000),
            ),
            palette=None,
            render_tile=(0xF5400206, 0x00008020),
            render_tiles=(
                (0, 0xF5400206, 0x00008020),
                (1, 0xF5480200, 0x01008030),
                (2, 0xF5480204, 0x02004020),
                (7, 0xF5480000, 0x07000000),
            ),
            tile_bounds=(0xF2000000, 0x0000C004),
            texture_scale=(0xD7000802, 0xFFFFFFFF),
            combine_mode=None,
            other_mode=None,
            runtime_render_state_offset=None,
        )
        pixels = bytes(range(64))
        palette = b"".join(
            struct.pack(">H", (index << 8) | 1) for index in range(256)
        )
        captured = model_assets.runtime_captured_preview_texture(
            run,
            {
                "texture": {
                    "scale": [0xD7000802, 0xFFFFFFFF],
                    "pixel_image": {
                        "captured_texture_image_index": 3,
                        "sha256": "pixel-sha256",
                    },
                    "palette_image": {
                        "captured_texture_image_index": 4,
                        "sha256": "palette-sha256",
                    },
                },
                "tiles": [
                    {"index": 0, "command": 0xF5400206, "argument": 0x00008020},
                    {"index": 1, "command": 0xF5480200, "argument": 0x01008030},
                    {"index": 2, "command": 0xF5480204, "argument": 0x02004020},
                    {"index": 7, "command": 0xF5480000, "argument": 0x07000000},
                ],
                "other_mode": [0xEF1DAC3F, 0x0C184DD8],
            },
            {3: pixels, 4: palette},
        )

        self.assertIsNotNone(captured)
        self.assertEqual(48, captured["source_byte_offset"])
        self.assertEqual(0, len(captured["mip_levels"]))
        self.assertEqual(2, captured["texture1_mip_level_count"])
        self.assertEqual(
            [(0, 8, 4, 0), (1, 4, 2, 32)],
            [
                (
                    level["level"],
                    level["width"],
                    level["height"],
                    level["source_byte_offset"],
                )
                for level in captured["texture1_mip_levels"]
            ],
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
        context["combined_rows"] = context["model_view_rows"]

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
        invalid = {
            "sha256": "c" * 64,
            "layout": "cbfd-character-row-major-f32",
            "status": "invalid-or-uninitialized-at-capture",
            "rows": None,
            "translation": None,
        }
        self.assertIsNone(
            model_assets.runtime_lighting_context(
                {"captured_matrix_index": 0, "matrix_sha256": "c" * 64},
                [invalid],
            )
        )

    def test_runtime_segment_8_resolution_proves_effective_other_mode(self):
        geometry = model_assets.parse_model_geometry(model_payload())
        run = replace(
            geometry.material_runs[0], runtime_render_state_offset=0x40
        )
        other_mode = [0xEF18AC3F, 0x04D13078]
        payload = struct.pack(">IIII", *other_mode, 0xDF000000, 0)
        resolved = model_assets.runtime_segment_8_resolution(
            run,
            {"segments": {"8": 0x80083140}, "other_mode": other_mode},
            [
                {
                    "address": 0x08000040,
                    "resolved_address": 0x80083180,
                }
            ],
            {
                0x80083180: {
                    "data_base64": base64.b64encode(payload).decode("ascii"),
                    "sha256": hashlib.sha256(payload).hexdigest(),
                }
            },
        )

        self.assertEqual("exact-runtime-list-effective-state", resolved["status"])
        self.assertEqual("0x80083180", resolved["resolved_address"])
        self.assertTrue(resolved["matches_effective_other_mode"])

    def test_gltf_does_not_bake_legacy_draw_time_lighting_context(self):
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

        self.assertEqual(5121, color["componentType"])
        self.assertNotIn("NORMAL", primitive["attributes"])
        self.assertEqual(
            "not-baked-ambiguous-or-incomplete",
            gltf["materials"][0]["extras"]["runtimeMaterial"]["lightingReplay"][
                "status"
            ],
        )

    def vertex_colour_fixture(self):
        geometry = model_assets.parse_model_geometry(model_payload())
        identity = [[float(i == j) for j in range(4)] for i in range(4)]
        modifiers = [0.0] * 16
        modifiers[12:15] = [1.0] * 3
        state = {"lighting_enabled": True, "lighting_enabled_known": True,
                 "geometry_mode": 0x20000,
                 "lights": {"num_lights": 2, "advanced_lighting": False,
                            "coordinate_modifiers": modifiers,
                            "slots": [{"light_slot": slot, "decoded": {
                                "colour": colour, "position_s16": [0, 0, 0, 0],
                                "attenuation": 1.0, "direction_normalized": [0, 0, 1],
                            }} for slot, colour in ((0, [255, 0, 0]), (2, [0, 0, 0]))]}}
        raw = b"".join(struct.pack(">hhhHhh4B", v.x, v.y, v.z, 0, v.s, v.t, 255, 255, 255, 255)
                       for v in geometry.vertices)
        loads = []
        for translation in (256, 512):
            combined = [row[:] for row in identity]
            combined[3][0] = translation
            loads.append({"resolved_address": 0x80100000, "first_cache_index": 0,
                          "vertex_count": 3, "state": state,
                          "processing_matrices": {"combined_rows": combined, "model_view_rows": identity}})
        draw = {"triangle_count": 1, "replayed_vertex_load_indices": [[0, 0, 1]],
                "replayed_vertex_cache_indices": [[0, 1, 2]]}
        sources = [(0x80100000, raw, hashlib.sha256(raw).hexdigest())]
        return geometry, draw, loads, sources

    def test_unique_command_pattern_cannot_override_captured_vertex_mismatch(self):
        geometry, draw, loads, sources = self.vertex_colour_fixture()
        wrong = replace(geometry, vertices=tuple(replace(v, x=v.x + 1) for v in geometry.vertices))
        fields = {"first_face": 0, "face_count": 1, "matrix_index": 0}
        candidate = {"bank": 1, "entry": 0, "segment": 0, "static_first_face": 0,
                     "material_run": {"index": 0, **fields}}
        correlation = {"status": "unique", "runtime_cluster_index": 0,
                       "draw_run_indices": [0], "candidates": [candidate]}
        event = {"schema": "conker.model-draw-state-trace/v1", "record_type": "draw_state",
                 "state": {"rdp": {"draw_runs": [{**draw, "state": loads[0]["state"]}],
                           "replayed_vertex_loads": loads, "model_correlations": [correlation],
                           "material_run_correlations": [correlation]}}}
        session = {"schema": event["schema"], "record_type": "session", "normalized_sha1": "rom"}
        inventory = {(1, 0, 0, 0): {**fields, "model_sha1": "model", "_geometry": wrong}}
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary); trace = root / "trace.jsonl"
            trace.write_text(json.dumps(session) + "\n" + json.dumps(event) + "\n")
            with mock.patch.object(model_assets, "runtime_material_inventory", return_value=("rom", inventory)), \
                 mock.patch.object(model_assets, "captured_vertex_sources", return_value=sources):
                manifest = model_assets.extract_runtime_materials("us", None, (trace,), root / "output", False)
        self.assertEqual(0, manifest["material_record_count"])
        self.assertEqual(1, manifest["vertex_unproven_assignment_count"])

    def test_vertex_bytes_resolve_whole_cluster_and_preserve_true_aliases(self):
        geometry, draw, loads, sources = self.vertex_colour_fixture()
        # Both candidates share the first triangle; only the second differs.
        vertices = (*geometry.vertices, *(replace(v, x=v.x + 20) for v in geometry.vertices))
        correct = replace(geometry, vertices=vertices, faces=((0, 1, 2), (3, 4, 5)),
                          face_cache_indices=((0, 1, 2), (0, 1, 2)))
        wrong = replace(correct, vertices=(*vertices[:3], *(replace(v, x=v.x+1) for v in vertices[3:])))
        raw = b"".join(struct.pack(">hhhHhh4B", v.x, v.y, v.z, v.flag, v.s, v.t, 1, 2, 3, 4)
                       for v in vertices)
        sources = [(0x80100000, raw, hashlib.sha256(raw).hexdigest())]
        loads = [loads[0], {**loads[0], "resolved_address": 0x80100030}]
        draws = [{**draw, "replayed_vertex_load_indices": [[i, i, i]]} for i in (0, 1)]
        fields = {"first_face": 0, "face_count": 2, "matrix_index": 0}
        inventory = {(1, i, 0, 0): {**fields, "_geometry": g} for i, g in ((0, correct), (1, wrong))}
        candidates = [{"bank": 1, "entry": i, "segment": 0, "static_first_face": 0,
                       "material_run": {"index": 0, **fields}} for i in (0, 1)]
        def resolve(selected):
            return model_assets.refine_captured_material_candidate(
                {"draw_run_indices": [0, 1]}, {"candidates": selected}, draws, loads, sources, inventory)
        # Runtime RGB differs from source RGB, without changing model identity.
        self.assertEqual(((1, 0, 0, 0), 0), resolve(candidates))
        self.assertIsNone(resolve([candidates[1]]))
        inventory[(1, 1, 0, 0)]["_geometry"] = correct
        self.assertIsNone(resolve(candidates))
        duplicate = replace(correct, faces=correct.faces * 2, face_cache_indices=correct.face_cache_indices * 2)
        inventory[(1, 0, 0, 0)]["_geometry"] = duplicate
        self.assertIsNone(resolve([candidates[0], {**candidates[0], "static_first_face": 2}]))

    def test_captured_vertex_colours_use_per_corner_projection_and_runtime_bytes(self):
        geometry, draw, loads, sources = self.vertex_colour_fixture()
        sample = model_assets.replay_draw_vertex_colours(draw, loads, sources, geometry, 0)
        self.assertIsNotNone(sample)
        colours = sample["face_colours"][0]
        self.assertAlmostEqual(0.5, colours[0][0])
        self.assertAlmostEqual(65536 / (2 * (512 ** 2 + 10 ** 2)), colours[2][0])
        # The captured second vertex is white; its ROM colour has zero red.
        self.assertGreater(colours[1][0], 0)
        self.assertEqual(0, geometry.vertices[1].color[0])
        model_assets.validate_vertex_lighting_sample(sample, 0, 1)
        incomplete = [{**loads[0], "processing_matrices": {"model_view_rows": loads[0]["processing_matrices"]["model_view_rows"]}}, loads[1]]
        self.assertIsNone(model_assets.replay_draw_vertex_colours(draw, incomplete, sources, geometry, 0))
        mutated = bytearray(sources[0][1]); mutated[1] = 1
        self.assertIsNone(model_assets.replay_draw_vertex_colours(
            draw, loads, [(sources[0][0], bytes(mutated), "b" * 64)], geometry, 0))

    def test_gltf_bakes_only_consistent_captured_corner_colours_without_relighting(self):
        geometry, draw, loads, sources = self.vertex_colour_fixture()
        sample = model_assets.replay_draw_vertex_colours(draw, loads, sources, geometry, 0)
        state = {**loads[0]["state"], "combine_mode": [0xFC121824, 0x5531FEFF],
                 "other_mode": [0xEF08AC3F, 0x00552230], "colours": {}}
        evidence = {"source_first_face": 0, "source_face_count": 1, "vertex_lighting": sample}
        record = {"model_sha1": "test", "source_first_face": 0, "source_face_count": 1,
                  "variant_count": 1, "observation_count": 1,
                  "variants": [{"state": state, "evidence": [evidence],
                                "gltf_translation": model_assets.translate_runtime_material_state(state)}]}
        data, binary = model_assets.encode_gltf(0, 0, geometry, runtime_materials={0: record})
        gltf = json.loads(data)
        accessor = gltf["accessors"][gltf["meshes"][0]["primitives"][0]["attributes"]["COLOR_0"]]
        view = gltf["bufferViews"][accessor["bufferView"]]
        colours = list(struct.iter_unpack("<4f", binary[view["byteOffset"]:view["byteOffset"]+view["byteLength"]]))
        self.assertAlmostEqual(0.5, colours[0][0])
        self.assertEqual(["KHR_materials_unlit"], gltf["extensionsUsed"])
        self.assertIn("KHR_materials_unlit", gltf["materials"][0]["extensions"])
        # An observation with missing inputs prevents an aggregate consensus.
        record["variants"][0]["evidence"].append({"source_first_face": 0, "source_face_count": 1})
        self.assertEqual({}, model_assets.runtime_vertex_colour_map(record))
        record["variants"][0]["evidence"].pop()
        sample["face_colours"][0][0][0] = 0.75
        with self.assertRaisesRegex(ValueError, "sample hash changed"):
            model_assets.runtime_vertex_colour_map(record)

    def test_captured_tri4_colours_join_cache_slots_in_source_face_order(self):
        geometry, draw, loads, sources = self.vertex_colour_fixture()
        emitted = [(0, 1, 2), (1, 2, 0), (2, 0, 1), (2, 1, 0)]
        stored = tuple(emitted[i] for i in (2, 3, 1, 0))
        geometry = replace(geometry, faces=stored, face_cache_indices=stored,
                           material_runs=(replace(geometry.material_runs[0], face_count=4),))
        draw = {"triangle_count": 4, "replayed_vertex_cache_indices": emitted,
                "replayed_vertex_load_indices": [[0, 0, 0]] * 4}
        sample = model_assets.replay_draw_vertex_colours(draw, loads, sources, geometry, 0)
        self.assertIsNotNone(sample)
        self.assertAlmostEqual(65536 / (2 * (256 ** 2 + 10 ** 2)), sample["face_colours"][0][0][0])
        self.assertAlmostEqual(0.5, sample["face_colours"][3][0][0])

    def test_source_face_identity_survives_filtering_and_runtime_pose(self):
        geometry, _, _, _ = self.vertex_colour_fixture()
        geometry = replace(geometry, faces=((0, 0, 0), geometry.faces[0]),
                           material_runs=(replace(geometry.material_runs[0], first_face=0, face_count=2, matrix_index=0),),
                           face_cache_indices=((0, 0, 0), (0, 1, 2)), face_matrix_indices=(),
                           face_command_offsets=(), face_command_opcodes=(), face_cull_modes=())
        filtered, omitted, _ = model_assets.omit_zero_area_preview_faces(geometry)
        self.assertEqual((0,), omitted)
        self.assertEqual((1,), filtered.face_source_indices)
        identity = [[float(i == j) for j in range(4)] for i in range(4)]
        posed = model_assets.bake_character_runtime_pose(filtered, {0: identity}, [0, 0, 0])
        self.assertEqual((1,), posed.face_source_indices)

    def test_vertex_sources_require_a_verified_complete_graphics_task(self):
        geometry, draw, loads, sources = self.vertex_colour_fixture()
        raw = sources[0][1]
        task = bytearray(64)
        struct.pack_into(">I", task, 0, 1)
        struct.pack_into(">II", task, 48, 0x80120000, 8)
        probes = [{"name": name, "resolved_address": address, "length": len(data),
                   "sha256": hashlib.sha256(data).hexdigest(),
                   "data_base64": base64.b64encode(data).decode("ascii")}
                  for name, address, data in (
                      ("task", "0x80130000", task), ("command-buffer", "0x80120000", bytes(8)),
                      ("runtime-vertex-block-0000", "0x80100000", raw))]
        event = {"state": {"rdp": {"replayed_vertex_loads": loads}}, "evidence": {"memory": probes}}
        self.assertEqual(sources, model_assets.captured_vertex_sources(event))
        probes[1]["name"] = "character-command-buffer"
        self.assertEqual([], model_assets.captured_vertex_sources(event))
        probes[1]["name"] = "command-buffer"
        probes[0]["data_base64"] = base64.b64encode(bytes(64)).decode("ascii")
        with self.assertRaisesRegex(ValueError, "graphics task bytes changed"):
            model_assets.captured_vertex_sources(event)

    def test_gltf_splits_shared_source_vertices_with_different_captured_colours(self):
        geometry, draw, loads, sources = self.vertex_colour_fixture()
        geometry = replace(geometry, faces=geometry.faces * 2, face_cache_indices=geometry.face_cache_indices * 2,
                           face_matrix_indices=geometry.face_matrix_indices * 2,
                           face_cull_modes=geometry.face_cull_modes * 2,
                           material_runs=(replace(geometry.material_runs[0], face_count=2),))
        evidence = []
        for first, load_index in ((0, 0), (1, 1)):
            draw = {**draw, "replayed_vertex_load_indices": [[load_index] * 3]}
            sample = model_assets.replay_draw_vertex_colours(draw, loads, sources, geometry, first)
            evidence.append({"source_first_face": first, "source_face_count": 1, "vertex_lighting": sample})
        state = {"lighting_enabled": True}
        record = {"model_sha1": "test", "source_first_face": 0, "source_face_count": 2,
                  "variant_count": 1, "observation_count": 2,
                  "variants": [{"state": state, "evidence": evidence,
                                "gltf_translation": model_assets.translate_runtime_material_state(state)}]}
        data, _ = model_assets.encode_gltf(0, 0, geometry, runtime_materials={0: record})
        gltf = json.loads(data)
        primitive = gltf["meshes"][0]["primitives"][0]
        self.assertEqual(6, gltf["accessors"][primitive["attributes"]["COLOR_0"]]["count"])
        self.assertEqual(6, gltf["accessors"][primitive["indices"]]["count"])

    def test_preview_catalog_translates_physical_stream_ordinals_to_runtime_ids(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for family in model_assets.PREVIEW_TEXTURE_FAMILIES:
                folder = root / family
                folder.mkdir()
                records = []
                if family == "us":
                    (folder / "physical-1.png").write_bytes(b"captured-png")
                    records = [{"flat_index": 1, "width": 32, "height": 64,
                                "file": "physical-1.png"}]
                (folder / "manifest.json").write_text(json.dumps({
                    "profile": "us", "normalized_sha1": "rom",
                    "tiles" if family == "us-tiled-views" else "textures": records,
                }))
            catalog = model_assets.load_preview_texture_catalog(root, "rom", (0, 3))
            self.assertEqual({(3, 2, 0)}, set(catalog))
            self.assertEqual("physical-1.png", catalog[(3, 2, 0)][0].source.name)

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
            (None, "direct-ci8-flat-payload-missing"),
            model_assets.choose_preview_texture(ci8_run, {(42, 2, 1): (exact,)}),
        )

    def test_composes_direct_ci8_without_caller_specific_palette_policy(self):
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
        # The old decoder read end-512; put a distinct red palette there
        # and require the actual green mode-two TLUT at end-32.
        payload = (
            bytes(1024) + bytes.fromhex("F801") * 16
            + bytes(448) + bytes.fromhex("07C1") * 16
        )
        texture, status = model_assets.character_runtime_preview_texture(
            ci4_run, payload
        )
        self.assertEqual("runtime-composed-character-texture", status)
        self.assertEqual(0, texture.size)
        self.assertEqual(1504, texture.palette_byte_offset)
        from scripts.texture_assets import decode_indexed_png
        self.assertEqual(bytes(512) + bytes.fromhex("07C1") * 16,
                         decode_indexed_png(texture.png_data, "linear", 32, 32))

    def direct_ci4_run(self):
        geometry = model_assets.parse_model_geometry(model_payload_with_material_runs())
        run = geometry.material_runs[0]
        return replace(
            run,
            pixel=replace(run.pixel, image_command=0xFD500000, mode=0,
                          load_command=(0xF3000000, 0x0715F000)),
            palette=replace(run.palette, image_command=0xFD100000, mode=2,
                            load_command=(0xF0000000, 0x0603C000)),
            render_tile=(0xF5400400, 0x00014050),
            render_tiles=((0, 0xF5400400, 0x00014050),
                          (1, 0xF5400240, 0x01010040),
                          (6, 0xF5600100, 0x06000000),
                          (7, 0xF5500000, 0x07000000)),
            tile_bounds=(0xF2000000, 0x0007C07C),
            other_mode=(0xEF19AC3F, 0x0C192230),
        )

    def test_direct_ci4_uses_base_image_and_tail_palette_from_mip_payload(self):
        run = self.direct_ci4_run()
        base = bytes(range(256)) * 2
        lower_levels = bytes.fromhex("1234") * 96
        palette = b"".join(struct.pack(">H", (i << 11) | 1) for i in range(16))
        texture, status = model_assets.choose_preview_texture(
            run, {}, {42: base + lower_levels + palette}
        )
        self.assertEqual("runtime-composed-direct-ci4-texture", status)
        self.assertEqual((32, 32, 704),
                         (texture.width, texture.height, texture.palette_byte_offset))
        self.assertEqual(texture_assets.encode_indexed_png(base + palette,
                         "tmem-odd-row-32bit-swap", 32, 32), texture.png_data)

    def test_direct_ci4_rejects_unproven_load_and_palette_state(self):
        run = self.direct_ci4_run()
        payload = bytes(704) + bytes.fromhex("0001") * 16
        cases = (
            (replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x0715F001))),
             "direct-ci4-load-row-conversion-unresolved"),
            (replace(run, render_tiles=run.render_tiles[:-1]),
             "direct-ci4-load-tmem-origin-unresolved"),
            (replace(run, render_tile=(run.render_tile[0], run.render_tile[1] | 0x100000)),
             "direct-ci4-tlut-bank-unresolved"),
            (replace(run, other_mode=None), "direct-ci4-lookup-mode-unresolved"),
            (replace(run, palette=replace(run.palette, load_command=(0xF0000000, 0x063FC000))),
             "direct-ci4-tlut-size-unresolved"),
            (replace(run, texture_dimensions=(33, 32)), "direct-ci4-odd-width-unresolved"),
            (replace(run, texture_dimensions=(4, 2), render_tile=(0xF5400000, run.render_tile[1])),
             "direct-ci4-row-stride-unresolved"),
        )
        for candidate, reason in cases:
            with self.subTest(reason=reason):
                self.assertEqual((None, reason), model_assets.choose_preview_texture(candidate, {}, {42: payload}))
        self.assertEqual((None, "direct-ci4-payload-span-unresolved"),
                         model_assets.choose_preview_texture(run, {}, {42: bytes(511)}))

    def test_direct_ci4_prefers_command_geometry_to_storage_preview(self):
        run = self.direct_ci4_run()
        storage = model_assets.PreviewTexture(family="us", source=Path("storage.png"),
            flat_index=42, format=2, size=0, width=16, height=64, sha1="a" * 40)
        texture, status = model_assets.choose_preview_texture(
            run, {(42, 2, 0): (storage,)}, {42: bytes(704) + bytes.fromhex("0001") * 16}
        )
        self.assertEqual("runtime-composed-direct-ci4-texture", status)
        self.assertIsNone(texture.source)
        self.assertEqual((32, 32), (texture.width, texture.height))
        self.assertEqual(
            (None, "direct-ci4-lookup-mode-unresolved"),
            model_assets.choose_preview_texture(replace(run, other_mode=None),
                {(42, 2, 0): (storage,)}, {42: bytes(704) + bytes.fromhex("0001") * 16}),
        )

    def test_direct_ci4_wrap_period_controls_image_and_uv_dimensions(self):
        run = replace(self.direct_ci4_run(),
                      tile_bounds=(0xF2040040, 0x000B40BC))  # 30 by 32, origin 16.
        state = model_assets.texture_coordinate_state(run)
        self.assertEqual((32, 32), (state["width"], state["height"]))
        self.assertEqual("direct-load-block-tile-masks", state["dimension_evidence"])
        geometry = model_assets.parse_model_geometry(model_payload_with_material_runs())
        vertex = replace(geometry.vertices[0], s=0, t=0)
        half_scale = replace(run, texture_scale=(0xD7000002, 0x80008000))
        uv = model_assets.texture_coordinates(vertex, half_scale)
        self.assertEqual((-0.5, 1.5), uv)
        shifted_uv = model_assets.texture_coordinates(replace(vertex, s=2048, t=2048), half_scale)
        self.assertEqual((0.5, 0.5), shifted_uv)
        texture, _ = model_assets.choose_preview_texture(run, {},
            {42: bytes(704) + bytes.fromhex("0001") * 16})
        self.assertEqual((32, 32), (texture.width, texture.height))
        cases = (
            replace(run, render_tile=(run.render_tile[0], run.render_tile[1] | (2 << 8))),
            replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x070EF000))),
        )
        for candidate in cases:
            with self.subTest(candidate=candidate):
                state = model_assets.texture_coordinate_state(candidate)
                self.assertEqual((30, 32), (state["width"], state["height"]))
                self.assertEqual("tile-bounds", state["dimension_evidence"])
        state = model_assets.texture_coordinate_state(replace(run, texture_dimensions=(16, 16)))
        self.assertEqual((16, 16), (state["width"], state["height"]))

    def direct_rgba32_run(self):
        run = self.direct_ci4_run()
        return replace(run, palette=None,
            pixel=replace(run.pixel, image_command=0xFD180000,
                          load_command=(0xF3000000, 0x0700B000)),
            render_tile=(0xF5180200, 0),
            render_tiles=((0, 0xF5180200, 0), (7, 0xF5180000, 0x07000000)),
            tile_bounds=(0xF2000000, 0x0000C004),
            other_mode=(0xEF082C3F, 0x00504A50),
            combine_mode=(0xFC121824, 0xFF33FFFF))

    def test_direct_rgba32_decodes_paired_tmem_rows_and_preserves_alpha(self):
        run = self.direct_rgba32_run()
        payload = bytes(range(48))  # Base 4x2 image, then a lower level.
        texture, status = model_assets.choose_preview_texture(run, {}, {42: payload})
        self.assertEqual("runtime-composed-direct-rgba32-texture", status)
        self.assertEqual((4, 2), (texture.width, texture.height))
        self.assertEqual(0, texture.pixel_byte_offset)
        self.assertIsNone(texture.palette_byte_offset)
        # PNG rows are vertically flipped; RGBA32's odd row swaps eight-byte
        # halves rather than the four-byte halves used by narrower formats.
        expected = payload[24:32] + payload[16:24] + payload[:16]
        self.assertEqual(expected, texture_assets.decode_rgba_png_pixels(texture.png_data, 4, 2))
        full = replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x07007000)))
        self.assertEqual(texture.png_data,
                         model_assets.choose_preview_texture(full, {}, {42: payload[:32]})[0].png_data)

    def test_direct_rgba32_rejects_unknown_lookup_and_incomplete_transfers(self):
        run = self.direct_rgba32_run()
        cases = (
            (replace(run, other_mode=None), "direct-rgba32-lookup-mode-unresolved"),
            (replace(run, other_mode=(0xEF08AC3F, 0x00504A50)), "direct-rgba32-lookup-mode-unresolved"),
            (replace(run, combine_mode=None), "direct-rgba32-combiner-inputs-unresolved"),
            (replace(run, render_tiles=run.render_tiles[:-1]), "direct-rgba32-load-tmem-origin-unresolved"),
            (replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x0700B001))), "direct-rgba32-load-row-conversion-unresolved"),
            (replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x07003000))), "direct-rgba32-tmem-span-unresolved"),
            (replace(run, render_tile=(0xF5180400, 0)), "direct-rgba32-row-stride-unresolved"),
        )
        for candidate, reason in cases:
            with self.subTest(reason=reason):
                self.assertEqual((None, reason), model_assets.choose_preview_texture(candidate, {}, {42: bytes(48)}))
        self.assertEqual((None, "direct-rgba32-payload-span-unresolved"),
                         model_assets.choose_preview_texture(run, {}, {42: bytes(47)}))

    def test_static_rgba32_preview_retains_source_blend_state(self):
        run = self.direct_rgba32_run()
        geometry = model_assets.parse_model_geometry(model_payload_with_material_runs())
        geometry = replace(geometry, material_runs=(run,) + geometry.material_runs[1:])
        encoded, _ = model_assets.encode_gltf(0, 0, geometry, {0: "rgba32.png"})
        material = json.loads(encoded)["materials"][0]
        self.assertEqual("BLEND", material["alphaMode"])
        self.assertNotIn("alphaCutoff", material)
        self.assertEqual("exact-texture-times-vertex-color",
                         material["extras"]["staticMaterialPreview"]["colourStatus"])
        self.assertEqual("unverified", material["extras"]["staticMaterialPreview"]["nativeRasterParity"])

    def direct_intensity_run(self, fmt=3, size=1):
        run = self.direct_rgba32_run()
        # Each fixture has eight bytes per row and a 16-bit transfer tile.
        width = {(3, 1): 8, (3, 2): 4, (4, 0): 16, (4, 1): 8}[(fmt, size)]
        tile = 0xF5000200 | (fmt << 21) | (size << 19)
        return replace(run,
            pixel=replace(run.pixel, image_command=0xFD100000 | (fmt << 21)),
            render_tile=(tile, 0),
            render_tiles=((0, tile, 0), (7, 0xF5100000 | (fmt << 21), 0x07000000)),
            tile_bounds=(0xF2000000, ((width - 1) * 4 << 12) | 4))

    def test_direct_intensity_decodes_pixels_alpha_rows_and_base_prefix(self):
        payload = bytes.fromhex("0123456789abcdef1032547698badcfe") + b"padding!"
        linear = payload[12:16] + payload[8:12] + payload[:8]
        for fmt, size, name, width in ((3, 1, "ia8", 8), (3, 2, "ia16", 4),
                                      (4, 0, "i4", 16), (4, 1, "i8", 8)):
            with self.subTest(format=name):
                run = self.direct_intensity_run(fmt, size)
                texture, status = model_assets.choose_preview_texture(run, {}, {42: payload})
                self.assertEqual(f"runtime-composed-direct-{name}-texture", status)
                self.assertEqual((width, 2, 0, None),
                                 (texture.width, texture.height, texture.pixel_byte_offset,
                                  texture.palette_byte_offset))
                if name == "ia8":
                    expected = b"".join(bytes((v >> 4,) * 3 + (v & 15,))
                                        for v in linear)
                    expected = bytes(v * 17 for v in expected)
                elif name == "ia16":
                    expected = b"".join(bytes((linear[i],) * 3 + (linear[i + 1],))
                                        for i in range(0, 16, 2))
                elif name == "i4":
                    expected = b"".join(bytes((v * 17,) * 4)
                                        for byte in linear for v in (byte >> 4, byte & 15))
                else:
                    expected = b"".join(bytes((v,) * 4) for v in linear)
                self.assertEqual(expected,
                                 texture_assets.decode_rgba_png_pixels(texture.png_data, width, 2))
                full = replace(run, pixel=replace(run.pixel,
                               load_command=(0xF3000000, 0x07007000)))
                self.assertEqual(texture.png_data, model_assets.choose_preview_texture(
                    full, {}, {42: payload[:16]})[0].png_data)

    def test_direct_intensity_rejects_unproven_source_and_material_state(self):
        run = self.direct_intensity_run()
        alpha_changed = (run.combine_mode[0], run.combine_mode[1] & ~7)
        cases = (
            (replace(run, pixel=replace(run.pixel, mode=1)), "source"),
            (replace(run, pixel=replace(run.pixel, image_command=0xFD100000)), "source"),
            (replace(run, other_mode=None), "lookup-mode"),
            (replace(run, other_mode=(0xEF08AC3F, run.other_mode[1])), "lookup-mode"),
            (replace(run, combine_mode=None), "combiner-inputs"),
            (replace(run, combine_mode=(0xFC26A080, 0x151492FF)), "combiner-inputs"),
            (replace(run, other_mode=(0xEF282C3F, 0)), "cycle-mode"),
            (replace(run, other_mode=(0xEF382C3F, 0)), "cycle-mode"),
            (replace(run, other_mode=(0xEF182C3F, run.other_mode[1])), "alpha-expression"),
            (replace(run, combine_mode=alpha_changed), "alpha-expression"),
        )
        # Even a same-sized storage PNG cannot override missing draw evidence.
        native = model_assets.PreviewTexture(family="us-native-proven", source=Path("native.png"),
            flat_index=42, format=3, size=1, width=8, height=2, sha1="e" * 40)
        for candidate, reason in cases:
            with self.subTest(reason=reason, candidate=candidate):
                self.assertEqual((None, f"direct-ia8-{reason}-unresolved"),
                    model_assets.choose_preview_texture(candidate, {(42, 3, 1): (native,)},
                                                        {42: bytes(24)}))
        self.assertEqual((None, "direct-intensity-flat-payload-missing"),
                         model_assets.choose_preview_texture(run, {}, {}))

    def test_direct_intensity_rejects_incomplete_or_ambiguous_transfers(self):
        run = self.direct_intensity_run()
        cases = (
            (replace(run, pixel=replace(run.pixel, load_command=None)), "load-row-conversion"),
            (replace(run, pixel=replace(run.pixel, load_command=(0xF3000001, 0x0700B000))), "load-row-conversion"),
            (replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x0700B001))), "load-row-conversion"),
            (replace(run, render_tiles=run.render_tiles[:-1]), "load-tmem-origin"),
            (replace(run, render_tiles=((7, 0xF5700001, 0x07000000),)), "load-tmem-origin"),
            (replace(run, render_tiles=((7, 0xF5680000, 0x07000000),)), "load-format"),
            (replace(run, render_tile=(0xF5680201, 0)), "row-stride"),
            (replace(run, render_tile=(0xF5680400, 0)), "row-stride"),
            (replace(run, tile_bounds=(0xF2000000, 0x00018004)), "row-stride"),
            (replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x07003000))), "tmem-span"),
            (replace(run, pixel=replace(run.pixel, load_command=(0xF3000000, 0x07800000))), "tmem-span"),
        )
        for candidate, reason in cases:
            with self.subTest(reason=reason, candidate=candidate):
                self.assertEqual((None, f"direct-ia8-{reason}-unresolved"),
                    model_assets.choose_preview_texture(candidate, {}, {42: bytes(24)}))
        self.assertEqual((None, "direct-ia8-payload-span-unresolved"),
                         model_assets.choose_preview_texture(run, {}, {42: bytes(23)}))
        odd = replace(self.direct_intensity_run(4, 0), tile_bounds=(0xF2000000, 0x00038004))
        self.assertEqual((None, "direct-i4-row-stride-unresolved"),
                         model_assets.choose_preview_texture(odd, {}, {42: bytes(24)}))

    def test_direct_intensity_export_preserves_blend_and_opaque_source_modes(self):
        geometry = model_assets.parse_model_geometry(model_payload_with_material_runs())
        for fmt, size in ((3, 1), (3, 2), (4, 0), (4, 1)):
            for mode, expected in ((0x00504A50, "BLEND"), (0, "OPAQUE")):
                with self.subTest(format=fmt, size=size, mode=expected):
                    run = self.direct_intensity_run(fmt, size)
                    run = replace(run, other_mode=(run.other_mode[0], mode))
                    self.assertIsNotNone(model_assets.choose_preview_texture(run, {}, {42: bytes(24)})[0])
                    candidate = replace(geometry, material_runs=(run,) + geometry.material_runs[1:])
                    data, _ = model_assets.encode_gltf(0, 0, candidate, {0: "intensity.png"})
                    material = json.loads(data)["materials"][0]
                    self.assertEqual(expected, material["alphaMode"])
                    self.assertNotIn("alphaCutoff", material)
                    self.assertEqual("unverified", material["extras"]["staticMaterialPreview"]["nativeRasterParity"])

    def test_static_raster_state_applies_to_every_linked_texture_format(self):
        geometry = model_assets.parse_model_geometry(model_payload_with_material_runs())
        for fmt, size in ((0, 2), (0, 3), (2, 0), (2, 1), (3, 1), (4, 1)):
            with self.subTest(format=fmt, size=size):
                run = self.direct_rgba32_run()
                tile = (run.render_tile[0] & ~(31 << 19)) | (fmt << 21) | (size << 19)
                run = replace(run, render_tile=(tile, run.render_tile[1]),
                              pixel=replace(run.pixel, image_command=0xFD000000 | (fmt << 21) | (size << 19)),
                              other_mode=(run.other_mode[0] & ~0x3000, run.other_mode[1]))
                candidate = replace(geometry, material_runs=(run,) + geometry.material_runs[1:])
                encoded, _ = model_assets.encode_gltf(0, 0, candidate, {0: "source.png"})
                gltf = json.loads(encoded)
                material = gltf["materials"][0]
                self.assertEqual("BLEND", material["alphaMode"])
                self.assertNotIn("alphaCutoff", material)
                texture = gltf["textures"][material["pbrMetallicRoughness"]["baseColorTexture"]["index"]]
                sampler = gltf["samplers"][texture["sampler"]]
                self.assertEqual((9728, 9984), (sampler["magFilter"], sampler["minFilter"]))

    def test_static_raster_state_preserves_unknown_and_runtime_precedence(self):
        geometry = model_assets.parse_model_geometry(model_payload_with_material_runs())
        run = replace(self.direct_rgba32_run(), other_mode=None)
        candidate = replace(geometry, material_runs=(run,) + geometry.material_runs[1:])
        data, _ = model_assets.encode_gltf(0, 0, candidate, {0: "source.png"})
        material = json.loads(data)["materials"][0]
        self.assertEqual("MASK", material["alphaMode"])
        self.assertNotIn("staticMaterialPreview", material["extras"])
        run = replace(run, other_mode=(0xEF000000, 0))
        candidate = replace(candidate, material_runs=(run,) + geometry.material_runs[1:])
        data, _ = model_assets.encode_gltf(0, 0, candidate, {0: "source.png"})
        self.assertEqual("OPAQUE", json.loads(data)["materials"][0]["alphaMode"])
        state = {"texture": {}, "tiles": [], "colours": {}, "geometry_mode": 0,
                 "combine_mode": run.combine_mode, "other_mode": [0xEF082C3F, 0x00504A50]}
        record = {"model_sha1": "test", "source_first_face": 0, "source_face_count": 1,
                  "variant_count": 1, "observation_count": 1,
                  "variants": [{"state": state, "evidence": [],
                                "gltf_translation": model_assets.translate_runtime_material_state(state)}]}
        data, _ = model_assets.encode_gltf(0, 0, candidate, {0: "source.png"}, runtime_materials={0: record})
        material = json.loads(data)["materials"][0]
        self.assertEqual("BLEND", material["alphaMode"])
        self.assertNotIn("staticMaterialPreview", material["extras"])

    def test_character_trilinear_base_requires_the_exact_colour_formula(self):
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
        payload = bytes(range(256)) * 8 + bytes.fromhex("0001") * 256
        texture, status = model_assets.choose_preview_texture(
            mipmapped, {}, {42: payload}
        )
        self.assertEqual(
            "runtime-composed-character-trilinear-base", status
        )
        self.assertIsNotNone(texture)
        # Changing the interpolation factor to primitive LOD is a different
        # colour operation and must not silently become a base diffuse image.
        unsupported = replace(mipmapped, combine_mode=(0xFC26A280, 0x151492FF))
        self.assertEqual((None, "character-indexed-mipmap-combiner-unresolved"),
                         model_assets.choose_preview_texture(unsupported, {}, {42: payload}))
        preview_geometry = replace(
            geometry, material_runs=(mipmapped,),
            vertices=tuple(replace(v, color=(*v.color[:3], 0)) for v in geometry.vertices),
        )
        encoded, binary = model_assets.encode_gltf(0, 0, preview_geometry, {0: "base.png"})
        document = json.loads(encoded)
        material = document["materials"][0]
        self.assertEqual("unverified", material["extras"]["textureLodPreview"]["nativeDistanceDependentLodParity"])
        colors = document["accessors"][document["meshes"][0]["primitives"][0]["attributes"]["COLOR_0"]]
        view = document["bufferViews"][colors["bufferView"]]
        self.assertEqual([255] * colors["count"], list(binary[view["byteOffset"] + 3: view["byteOffset"] + view["byteLength"]:4]))

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
