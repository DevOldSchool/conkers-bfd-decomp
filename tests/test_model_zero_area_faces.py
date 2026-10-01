"""Newly derived ROM-free tests for the retained source-face preservation edit."""

import copy
import json
import math
import struct
import tempfile
import unittest
from pathlib import Path
from unittest import mock

from scripts import model_assets as models
from test_model_assets import character_model_payload
from test_model_entry_filter import SyntheticPreviewSources, make_bundle


SOURCE_FACES = ((0, 1, 2), (0, 1, 1), (0, 1, 4), (0, 1, 3), (2, 1, 0))
SOURCE_POSITIONS = ((0, 0, 0), (10, 0, 0), (0, 10, 0), (20, 0, 0), (10, 0, 0))


def mixed_face_payload():
    """One valid run and a second run with coincident/collinear source triangles."""
    original = character_model_payload()
    words = list(struct.unpack_from(">14I", original))
    old_display = struct.unpack_from(">I", original, words[2])[0]
    commands = list(struct.iter_unpack(">II", original[old_display:words[4]]))
    commands[3] = (0x0100500A, 0x01000038)
    # Keep different UVs and colours for equal-position vertices 1 and 4.
    vertices = original[0x38:0x38 + 3 * 16] + b"".join(
        struct.pack(">hhhHhh4B", *position, 0, s, t, *colour)
        for position, s, t, colour in (
            ((20, 0, 0), 64, 64, (90, 80, 70, 255)),
            ((10, 0, 0), 96, 32, (40, 50, 60, 255)),
        )
    )
    triangles = [(0x05000000 | a * 2 << 16 | b * 2 << 8 | c * 2, 0)
                 for a, b, c in SOURCE_FACES]
    commands = commands[:-2] + triangles[:2] + [(0xD7000002, 0x7FFF7FFF)] + triangles[2:] + [(0xDF000000, 0)]
    pointer_offset = 0x38 + len(vertices)
    display_offset = pointer_offset + 4
    joint_offset = display_offset + len(commands) * 8
    descriptor_offset = joint_offset + 16
    normal_offset = descriptor_offset + 12
    normals = bytes((127, 0, 0, 127, 129, 0, 0, 0, 0, 0, 0, 0))
    procedural_offset = normal_offset + len(normals)
    commands[0] = (commands[0][0], normal_offset)
    words[2:10] = [pointer_offset, 4, joint_offset, 16, descriptor_offset, 12, normal_offset, len(normals)]
    words[12] = procedural_offset
    return (struct.pack(">14I", *words) + vertices + struct.pack(">I", display_offset)
            + b"".join(struct.pack(">II", *command) for command in commands)
            + original[struct.unpack_from(">I", original, 16)[0]:][:16]
            + struct.pack(">IIHH", 42, 42, 32, 64) + normals + bytes((0, 0xFF)))


def accessor_rows(document, binary, index):
    """Decode glTF independently, respecting view/accessor offset and stride."""
    accessor = document["accessors"][index]
    view = document["bufferViews"][accessor["bufferView"]]
    components = {"SCALAR": 1, "VEC2": 2, "VEC3": 3, "VEC4": 4, "MAT4": 16}[accessor["type"]]
    code = {5121: "B", 5123: "H", 5125: "I", 5126: "f"}[accessor["componentType"]]
    layout = struct.Struct("<" + code * components)
    start = view.get("byteOffset", 0) + accessor.get("byteOffset", 0)
    stride = view.get("byteStride", layout.size)
    return [layout.unpack_from(binary, start + stride * i) for i in range(accessor["count"])]


def decoded_corners(document, binary, attribute):
    result = []
    for mesh in document["meshes"]:
        for primitive in mesh["primitives"]:
            values = accessor_rows(document, binary, primitive["attributes"][attribute])
            indices = accessor_rows(document, binary, primitive["indices"])
            result.extend(values[index[0]] for index in indices)
    return result


class ZeroAreaPreviewTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.payload = mixed_face_payload()
        self.geometry, self.layout = models.parse_character_model_geometry(self.payload)
        self.assertEqual(SOURCE_FACES, self.geometry.faces)
        self.assertEqual(2, len(self.geometry.material_runs))

    def extract(self, name, preserve=None):
        source = SyntheticPreviewSources(self.root, data=self.payload)
        source.bundles = (make_bundle(75, self.payload),)
        arguments = {} if preserve is None else {"preserve_zero_area_faces": preserve}
        output = self.root / name
        with source.patches():
            manifest = models.extract_model_preview(
                "us", None, self.root / "textures", output, False,
                bank_index=1, entry_filter=frozenset({75}), **arguments)
        return output, manifest

    def test_default_output_and_explicit_false_are_byte_identical(self):
        default_root, default = self.extract("default")
        false_root, explicit_false = self.extract("false", False)
        self.assertEqual(default, explicit_false)
        self.assertNotIn("source_zero_area_faces_preserved", default)
        self.assertIn("omitted from OBJ/glTF previews", (default_root / "README.txt").read_text())
        self.assertEqual(2, default["face_count"])
        self.assertEqual(3, default["omitted_zero_area_face_count"])
        self.assertEqual(["repeated-vertex-index", "duplicate-position", "collinear-positions"],
                         [record["kind"] for record in default["models"][0]["omitted_zero_area_faces"]])
        self.assertEqual([1, 2], [run["omitted_zero_area_face_count"]
                                 for run in default["models"][0]["material_runs"]])
        for path in default_root.rglob("*"):
            if path.is_file():
                self.assertEqual(path.read_bytes(), (false_root / path.relative_to(default_root)).read_bytes())

    def test_preserves_source_triangles_obj_normal_bind_uv_normals_and_rig(self):
        output, manifest = self.extract("preserve", True)
        self.assertIs(manifest["source_zero_area_faces_preserved"], True)
        instructions = (output / "README.txt").read_text()
        self.assertIn("preserved in OBJ/glTF previews", instructions)
        self.assertNotIn("omitted from OBJ/glTF previews", instructions)
        self.assertEqual(5, manifest["source_face_count"])
        self.assertEqual(5, manifest["face_count"])
        self.assertEqual(0, manifest["omitted_zero_area_face_count"])
        model = manifest["models"][0]
        self.assertEqual([], model["omitted_zero_area_faces"])
        self.assertEqual([0, 0], [run["omitted_zero_area_face_count"] for run in model["material_runs"]])
        obj_faces = [tuple(int(field.split("/")[0]) - 1 for field in line.split()[1:])
                     for line in (output / model["object_file"]).read_text().splitlines() if line.startswith("f ")]
        self.assertEqual(list(SOURCE_FACES), obj_faces)
        expected_positions = [tuple(float(value) + pivot for value, pivot in zip(SOURCE_POSITIONS[index], (1, 2, 3)))
                              for face in SOURCE_FACES for index in face]
        source_normals = ((1, 0, 0), (0, 1, 0), (-1, 0, 0), (0, 0, 1), (0, 0, 1))
        source_st = ((0, 0), (32, 0), (0, 32), (64, 64), (96, 32))
        # Fixture tile bounds are (2,2)..(126,126), giving 32x32 texels;
        # s/t are 5-bit fractional coordinates, scales are unsigned 16-bit.
        expected_uv = [((source_st[index][0] / 32 * scale / 65536 - 0.5) / 32,
                        1 - (source_st[index][1] / 32 * scale / 65536 - 0.5) / 32)
                       for face_index, face in enumerate(SOURCE_FACES)
                       for scale in (65535 if face_index < 2 else 32767,)
                       for index in face]
        documents = []
        for gltf_key, binary_key in (("gltf_file", "gltf_binary_file"), ("bind_gltf_file", "bind_gltf_binary_file")):
            document = json.loads((output / model[gltf_key]).read_bytes())
            binary = (output / model[binary_key]).read_bytes()
            documents.append((document, binary))
            self.assertEqual(expected_positions, decoded_corners(document, binary, "POSITION"))
            self.assertEqual([(0, 0, 0, 0)] * 15, decoded_corners(document, binary, "JOINTS_0"))
            self.assertEqual([(1, 0, 0, 0)] * 15, decoded_corners(document, binary, "WEIGHTS_0"))
            self.assertEqual([self.geometry.vertices[index].color for face in SOURCE_FACES for index in face],
                             decoded_corners(document, binary, "COLOR_0"))
            normals = decoded_corners(document, binary, "NORMAL")
            self.assertEqual([source_normals[index] for face in SOURCE_FACES for index in face], normals)
            self.assertTrue(all(all(math.isfinite(value) for value in normal) for normal in normals))
            for normal in normals:
                self.assertAlmostEqual(1, sum(value * value for value in normal))
            # Vertex 3/4 have zero normal bytes on zero-area source faces.
            self.assertEqual((0, 0, 1), normals[8])
            self.assertEqual((0, 0, 1), normals[11])
            uv = decoded_corners(document, binary, "TEXCOORD_0")
            self.assertEqual(15, len(uv))
            for observed, expected in zip(uv, expected_uv):
                for actual, wanted in zip(observed, expected):
                    self.assertAlmostEqual(wanted, actual, places=6)
            self.assertNotEqual(uv[7], uv[8])  # Equal-position source vertices 1 and 4.
            skin = document["skins"][0]
            self.assertEqual([0], skin["joints"])
            self.assertEqual([(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -1, -2, -3, 1)],
                             accessor_rows(document, binary, skin["inverseBindMatrices"]))
        for attribute in ("POSITION", "NORMAL", "TEXCOORD_0", "COLOR_0", "JOINTS_0", "WEIGHTS_0"):
            self.assertEqual(decoded_corners(*documents[0], attribute), decoded_corners(*documents[1], attribute))
        self.assertEqual(1, len(documents[0][0]["animations"]))
        self.assertFalse(documents[1][0].get("animations"))
        self.assertTrue(any("preserved in" in item for item in manifest["limitations"]))
        models.verify_preview_output(output, manifest, expected_entries=frozenset({75}))

    def test_source_geometry_validation_remains_independent(self):
        before = models.validate_model_geometry(self.geometry, tuple(self.layout["joints"]))
        self.assertEqual("review", before["status"])
        self.assertEqual(3, before["zero_area_face_count"])
        self.extract("preserved", True)
        self.assertEqual(before, models.validate_model_geometry(self.geometry, tuple(self.layout["joints"])))

    def test_preserved_exports_still_reject_geometry_rig_and_animation_damage(self):
        output, manifest = self.extract("preserved", True)
        path = output / manifest["models"][0]["gltf_file"]
        original = json.loads(path.read_text())
        mutations = {
            "triangle_count": lambda document: document["accessors"][document["meshes"][0]["primitives"][0]["indices"]].update(count=0),
            "missing_normals": lambda document: document["meshes"][0]["primitives"][0]["attributes"].pop("NORMAL"),
            "missing_weights": lambda document: document["meshes"][0]["primitives"][0]["attributes"].pop("WEIGHTS_0"),
            "bad_animation_target": lambda document: document["animations"][0]["channels"][0]["target"].update(node=999),
        }
        for name, mutate in mutations.items():
            document = copy.deepcopy(original)
            mutate(document)
            path.write_text(json.dumps(document))
            with self.subTest(mutation=name), self.assertRaises(ValueError):
                models.verify_preview_output(output, manifest, expected_entries=frozenset({75}))

    def test_preservation_retains_animation_samples(self):
        default_output, default = self.extract("default")
        preserved_output, preserved = self.extract("preserved", True)
        samples = []
        for output, manifest in ((default_output, default), (preserved_output, preserved)):
            model = manifest["models"][0]
            document = json.loads((output / model["gltf_file"]).read_bytes())
            binary = (output / model["gltf_binary_file"]).read_bytes()
            samples.append([(channel["target"], sampler["interpolation"],
                             accessor_rows(document, binary, sampler["input"]),
                             accessor_rows(document, binary, sampler["output"]))
                            for animation in document["animations"] for channel in animation["channels"]
                            for sampler in (animation["samplers"][channel["sampler"]],)])
        self.assertTrue(samples[0])
        self.assertEqual(samples[0], samples[1])

    def test_preservation_needs_explicit_bank_one_selection_before_io(self):
        with mock.patch.object(models, "load_model_bundles") as load:
            for bank, selection in ((1, None), (3, frozenset({75}))):
                with self.subTest(bank=bank, selection=selection), self.assertRaises(ValueError):
                    models.extract_model_preview("us", None, self.root, self.root / "never", False,
                                                 bank_index=bank, entry_filter=selection,
                                                 preserve_zero_area_faces=True)
            load.assert_not_called()

    def test_preservation_option_rejects_non_booleans_before_io(self):
        with mock.patch.object(models, "load_model_bundles") as load:
            for value in (0, 1, "false", "true", None):
                with self.subTest(value=value), self.assertRaisesRegex(ValueError, "must be boolean"):
                    models.extract_model_preview("us", None, self.root, self.root / "never", False,
                                                 bank_index=1, entry_filter=frozenset({75}),
                                                 preserve_zero_area_faces=value)
            load.assert_not_called()

    def test_preservation_marker_requires_explicit_bank_one_verification(self):
        output, manifest = self.extract("preserved", True)
        with self.assertRaisesRegex(ValueError, "requires explicit bank-01 verification"):
            models.verify_preview_output(output, manifest)
        manifest["bank_index"] = 3
        with self.assertRaisesRegex(ValueError, "requires explicit bank-01 verification"):
            models.verify_preview_output(output, manifest, expected_entries=frozenset({75}))

    def test_verifier_rejects_false_preservation_claim_on_filtered_export(self):
        output, manifest = self.extract("default")
        manifest["source_zero_area_faces_preserved"] = True
        with self.assertRaisesRegex(ValueError, "preservation conflicts"):
            models.verify_preview_output(output, manifest, expected_entries=frozenset({75}))

    def test_verifier_rejects_marker_and_omission_mutations_independently(self):
        output, manifest = self.extract("preserved", True)
        mutations = {
            "marker_false": lambda item: item.update(source_zero_area_faces_preserved=False),
            "marker_integer": lambda item: item.update(source_zero_area_faces_preserved=1),
            "marker_string": lambda item: item.update(source_zero_area_faces_preserved="true"),
            "aggregate_omission": lambda item: item.update(omitted_zero_area_face_count=1),
            "model_omission": lambda item: item["models"][0].update(omitted_zero_area_face_count=1),
            "omission_records": lambda item: item["models"][0].update(omitted_zero_area_faces=[{}]),
            "run_omission": lambda item: item["models"][0]["material_runs"][0].update(omitted_zero_area_face_count=1),
        }
        for name, mutate in mutations.items():
            changed = copy.deepcopy(manifest)
            mutate(changed)
            with self.subTest(mutation=name), self.assertRaisesRegex(ValueError, "preservation"):
                models.verify_preview_output(output, changed, expected_entries=frozenset({75}))


if __name__ == "__main__":
    unittest.main()
