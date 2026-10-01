from __future__ import annotations

import copy
from dataclasses import replace
import hashlib
import json
from pathlib import Path
import struct
import tempfile
import unittest
from unittest import mock

from scripts import model_assets as models, model_shc_boat_appearance as boat
from scripts import texture_assets, model_validation


def source_run(record):
    """Rehydrate non-payload handoff metadata without copying source model bytes."""
    def binding(value):
        if value is None:
            return None
        value = dict(value)
        if value["load_command"] is not None:
            value["load_command"] = tuple(value["load_command"])
        return models.ModelTextureBinding(**value)

    def tuples(value):
        return tuple(map(tuples, value)) if isinstance(value, list) else value

    value = {key: tuples(item) for key, item in record.items()}
    value["pixel"], value["palette"] = binding(record["pixel"]), binding(record["palette"])
    value["texture_loads"] = tuple((binding(image), tuples(tile))
                                    for image, tile in record["texture_loads"])
    return models.ModelMaterialRun(**value)


def synthetic_geometry(evidence):
    runs = tuple(source_run(material["source_contract"]) for material in evidence["materials"])
    vertices = tuple(models.ModelVertex(i, i * i % 17, i % 3, 127,
                                        i * 37 - 600, i * 19 - 400,
                                        (i * 3, i * 5, 255 - i, 255)) for i in range(50))
    faces, start = [], 0
    for run, count in zip(runs, (12, 22, 8, 8)):
        faces.extend(tuple(start + (3 * face + corner) % count for corner in range(3))
                     for face in range(run.face_count))
        start += count
    return models.ModelGeometry(
        vertices=vertices, faces=tuple(faces), material_runs=runs,
        display_list_offset=0, display_list_size=0, vertex_load_count=1,
        segment_8_display_list_offsets=(), secondary_region=None, tertiary_region=None,
        vertex_color_animation_offset=None, vertex_color_animation_table_size=0,
        vertex_color_animation_descriptors=(), texture_references=(),
        runtime_segment_texture_addresses=(), header_words=(),
        face_normal_bytes=(((0, 0, 127),) * 3,) * 36,
        face_matrix_indices=((0, 0, 0),) * 36,
    )


class BoatAppearanceContractTests(unittest.TestCase):
    def setUp(self):
        self.evidence = boat.contract()
        self.geometry = synthetic_geometry(self.evidence)

    def test_contract_keeps_scope_and_both_valid_draws(self):
        context = self.evidence["context"]
        self.assertEqual((9, 47, 0, 88, 42), tuple(context[key] for key in
                         ("bank", "entry", "part", "parent_entry", "parent_id")))
        self.assertEqual("unobserved", context["animation24_action74_activation"])
        self.assertEqual([(0, 2), (2, 7)], [(item["draw"], item["event"])
                         for item in self.evidence["provenance"]["verified_instances"]])
        self.assertEqual([1], [item["draw"] for item in self.evidence["provenance"]["excluded_draws"]])
        self.assertEqual("665265eab6e085e668a0ac96b32d7d4307d648bda20f1affe7b962a1e42a08a9",
                         self.evidence["provenance"]["draw_proof_sha256"])

    def test_binding_only_mapping_preserves_first_28_faces_and_source_state(self):
        mapped = boat.map_geometry(self.geometry, self.evidence)
        self.assertEqual(self.geometry, replace(mapped, material_runs=self.geometry.material_runs))
        self.assertEqual(self.geometry.material_runs[:2], mapped.material_runs[:2])
        for index in (2, 3):
            original, run = self.geometry.material_runs[index], mapped.material_runs[index]
            self.assertEqual(original, replace(run, pixel=original.pixel, palette=original.palette))
            self.assertEqual((4195, 0, None, None),
                             (run.pixel.flat_index, run.pixel.mode, run.pixel.segment, run.pixel.offset))
            self.assertEqual((4195, 1, None, None),
                             (run.palette.flat_index, run.palette.mode, run.palette.segment, run.palette.offset))
            self.assertIsNone(run.other_mode)
            state = models.texture_coordinate_state(run)
            self.assertEqual((32, 32, 2, 1), tuple(state[k] for k in ("width", "height", "format", "size")))
            for vertex in self.geometry.vertices:
                self.assertEqual(models.texture_coordinates(vertex, original),
                                 models.texture_coordinates(vertex, run))

    def test_context_and_capture_mutations_fail_closed(self):
        for field, value in (("preset", "default"), ("bank", 1), ("entry", 48),
                             ("part", 1), ("part", False)):
            with self.subTest(field=field, value=value), self.assertRaisesRegex(ValueError, "context"):
                boat.map_geometry(self.geometry, self.evidence, **{field: value})
        for mutate in (
            lambda e: e["context"].update(parent_id=41),
            lambda e: e["context"].update(animation24_action74_activation="observed"),
            lambda e: e["provenance"]["verified_instances"].pop(),
            lambda e: e["provenance"].update(excluded_draws=[]),
            lambda e: e["materials"][2].update(other_mode_words=["0", "0"]),
        ):
            changed = copy.deepcopy(self.evidence)
            mutate(changed)
            with self.assertRaisesRegex(ValueError, "evidence"):
                boat.map_geometry(self.geometry, changed)

    def test_source_material_mutations_reject_defaults_and_coordinate_changes(self):
        original = self.geometry.material_runs[2]
        mutations = {
            "segment": replace(original, pixel=replace(original.pixel, segment=6)),
            "parent40x40": replace(original, pixel=replace(original.pixel, flat_index=4200)),
            "palette_offset": replace(original, palette=replace(original.palette, offset=0x640)),
            "combiner": replace(original, combine_mode=None),
            "tile": replace(original, render_tile=None),
            "UV_scale": replace(original, texture_scale=None),
            "dimensions": replace(original, texture_dimensions=(40, 40)),
            "loads": replace(original, texture_loads=()),
            "matrix": replace(original, matrix_index=1),
            "face_extent": replace(original, face_count=3),
        }
        for name, changed in mutations.items():
            runs = list(self.geometry.material_runs)
            runs[2] = changed
            with self.subTest(name=name), self.assertRaisesRegex(ValueError, "source material 2"):
                boat.map_geometry(replace(self.geometry, material_runs=tuple(runs)), self.evidence)
        runs = list(self.geometry.material_runs)
        runs[0] = replace(runs[0], texture_scale=None)
        with self.assertRaisesRegex(ValueError, "source material 0"):
            boat.map_geometry(replace(self.geometry, material_runs=tuple(runs)), self.evidence)

    def test_invalid_source_and_flat_bytes_rejected_before_parsing(self):
        with self.assertRaisesRegex(ValueError, "ROM identity"):
            boat.checked_model(bytes(1464), "0" * 40, self.evidence)
        for raw in (b"", bytes(1464)):
            with self.assertRaisesRegex(ValueError, "model identity"):
                boat.checked_model(raw, self.evidence["identity"]["rom_sha1"], self.evidence)
        for payload in (b"", bytes(1535), bytes(1536), bytes(2112)):
            with self.assertRaisesRegex(ValueError, "flat4195 identity"):
                boat.checked_flat(payload, self.evidence)

    def test_changed_contract_file_rejected(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "contract.json"
            path.write_text(json.dumps(self.evidence))
            with mock.patch.object(boat, "CONTRACT_PATH", path), self.assertRaisesRegex(ValueError, "contract"):
                boat.contract()


class BoatAppearanceEncodingTests(unittest.TestCase):
    def setUp(self):
        self.evidence = boat.contract()
        self.geometry = synthetic_geometry(self.evidence)
        self.textures = []
        for index, material in enumerate(self.evidence["materials"]):
            width, height = material["captured_texture"]["width"], material["captured_texture"]["height"]
            png = texture_assets.encode_rgba_png(width, height, bytes((index, 64, 128, 255)) * width * height)
            digest = hashlib.sha1(png).hexdigest()
            material["decoded_png_sha1"] = digest
            self.textures.append(models.PreviewTexture("synthetic", None, material["flat"],
                                                       2, 1, width, height, digest, png))
        self.contract_patch = mock.patch.object(boat, "contract", return_value=self.evidence)
        self.contract_patch.start()
        self.addCleanup(self.contract_patch.stop)
        # Synthetic geometry enters only at the native source-loading boundary.
        # ROM-free contract tests above exercise the real source identity rejection.
        self.model_patch = mock.patch.object(boat, "checked_model", return_value=(self.geometry, {"joints": []}))
        self.model_patch.start()
        self.addCleanup(self.model_patch.stop)
        self.mapped = boat.map_geometry(self.geometry, self.evidence)
        self.files, self.manifest = boat.encode_files(self.geometry, self.mapped,
                                                     {"joints": []}, self.textures, self.evidence,
                                                     raw=b"synthetic", digest="synthetic")

    def write(self, output):
        for name, data in self.files.items():
            path = output / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)

    def test_real_writers_preserve_geometry_UVs_normals_colours_and_empty_rig(self):
        self.assertEqual(50, models.texture_coordinate_count(self.geometry))
        with tempfile.TemporaryDirectory() as temp:
            output = Path(temp)
            self.write(output)
            report = boat.verify_files(output, self.files, self.geometry, {"joints": []}, self.manifest)
            self.assertEqual((36, 108, 0), tuple(report[k] for k in ("faces", "uv_corners", "joint_corners")))
            document = json.loads(self.files["geometry/0047-00.gltf"])
            binary = [self.files["geometry/0047-00.bin"]]
            self.assertNotIn("skins", document)
            self.assertNotIn("animations", document)
            self.assertFalse(document["extras"]["capturedBoatAppearance"]["parent_transform_baked"])
            for primitive in document["meshes"][0]["primitives"]:
                attrs = primitive["attributes"]
                self.assertNotIn("JOINTS_0", attrs)
                self.assertNotIn("WEIGHTS_0", attrs)
                normals = model_validation.accessor(document, attrs["NORMAL"], binary)
                self.assertTrue(all(value == (0.0, 0.0, 1.0) for value in normals))
                colours = model_validation.accessor(document, attrs["COLOR_0"], binary)
                positions = model_validation.accessor(document, attrs["POSITION"], binary)
                for position, colour in zip(positions, colours):
                    vertex = self.geometry.vertices[int(position[0])]
                    self.assertEqual(vertex.color, colour)
            self.assertTrue(all(m["alphaMode"] == "OPAQUE" and "alphaCutoff" not in m
                                for m in document["materials"]))
            obj = self.files["geometry/0047-00.obj"].decode().splitlines()
            self.assertEqual((50, 50, 36), tuple(sum(line.startswith(prefix) for line in obj)
                                               for prefix in ("v ", "vt ", "f ")))

    def test_binary_mutation_is_detected_independently(self):
        with tempfile.TemporaryDirectory() as temp:
            output = Path(temp)
            self.write(output)
            path = output / "geometry/0047-00.bin"
            data = bytearray(path.read_bytes())
            struct.pack_into("<f", data, 0, 999.0)
            path.write_bytes(data)
            with self.assertRaisesRegex(ValueError, "output changed"):
                boat.verify_files(output, self.files, self.geometry, {"joints": []}, self.manifest)
            with self.assertRaisesRegex(ValueError, "position differs"):
                model_validation.compare_geometry(output / "geometry/0047-00.gltf", self.geometry, (),
                                                  self.manifest["models"][0]["material_runs"])

    def test_source_geometry_and_rig_mutations_rejected(self):
        for mapped, layout, textures in (
            (replace(self.mapped, vertices=self.mapped.vertices[:-1]), {"joints": []}, self.textures),
            (self.mapped, {"joints": [{"matrix_index": 0}]}, self.textures),
            (self.mapped, {"joints": []}, self.textures[:-1]),
            (self.mapped, {"joints": []}, self.textures + [self.textures[0]]),
        ):
            with self.assertRaises(ValueError):
                boat.encode_files(self.geometry, mapped, layout, textures, self.evidence,
                                  raw=b"synthetic", digest="synthetic")

    def test_same_count_fabricated_source_cannot_borrow_verified_identity(self):
        vertex = replace(self.geometry.vertices[0], x=1234)
        geometry = replace(self.geometry, vertices=(vertex,) + self.geometry.vertices[1:])
        mapped = boat.map_geometry(geometry, self.evidence)
        with self.assertRaisesRegex(ValueError, "differs from verified source"):
            boat.encode_files(geometry, mapped, {"joints": []}, self.textures, self.evidence,
                              raw=b"synthetic", digest="synthetic")

    def test_changed_image_and_capture_metadata_are_detected(self):
        for name in (next(name for name in self.files if name.endswith(".png")), "manifest.json",
                     "geometry/0047-00.gltf"):
            with tempfile.TemporaryDirectory() as temp:
                output = Path(temp)
                self.write(output)
                path = output / name
                path.write_bytes(path.read_bytes() + b" ")
                with self.subTest(name=name), self.assertRaisesRegex(ValueError, "output changed"):
                    boat.verify_files(output, self.files, self.geometry, {"joints": []}, self.manifest)


if __name__ == "__main__":
    unittest.main()
