from __future__ import annotations

import copy
import hashlib
import json
import struct
import tempfile
import unittest
from pathlib import Path
from unittest import mock

from scripts import model_assets, model_coverage, model_scene_consumers
from scripts.model_preview_evidence import preview_fingerprint


def triangle_payload() -> bytes:
    vertices = b"".join(struct.pack(">hhhHhh4B", x, y, 0, 0, 0, 0, 255, 255, 255, 255)
                        for x, y in ((0, 0), (10, 0), (0, 10)))
    commands = b"".join(struct.pack(">II", command, argument) for command, argument in (
        (0xD7000000, 0xFFFFFFFF), (0x01003006, 0x01000000),
        (0x05000204, 0), (0xDF000000, 0)))
    return struct.pack(">10I", 0x28 + len(vertices), len(commands), 0, 0, 0, 0, 0, 0, 0, 0x80000000) + vertices + commands


class ModelCoverageTests(unittest.TestCase):
    def test_blender_validation_requires_current_buffer_and_image_bytes(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "geometry").mkdir()
            (root / "textures").mkdir()
            path = root / "geometry/model.gltf"
            path.write_text(json.dumps({"buffers": [{"uri": "model.bin"}],
                                       "images": [{"uri": "../textures/a.png"}]}))
            buffer = path.with_suffix(".bin")
            buffer.write_bytes(b"original buffer")
            texture = root / "textures/a.png"
            texture.write_bytes(b"original texture")
            evidence = {str(path.resolve()): {"status": "validated", "fingerprint": preview_fingerprint(path)}}
            self.assertEqual("unvalidated", model_coverage.blender_status(path, {}))
            self.assertEqual("validated", model_coverage.blender_status(path, evidence))
            buffer.write_bytes(b"changed buffer")
            self.assertEqual("stale-validation", model_coverage.blender_status(path, evidence))
            buffer.write_bytes(b"original buffer")
            texture.write_bytes(b"changed texture")
            self.assertEqual("stale-validation", model_coverage.blender_status(path, evidence))
            texture.unlink()
            self.assertEqual("stale-validation", model_coverage.blender_status(path, evidence))

    def test_preview_fingerprint_rejects_external_dependencies(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "model.gltf"
            for uri in ("https://example.com/model.bin", "/tmp/model.bin", "../../model.bin"):
                with self.subTest(uri=uri):
                    path.write_text(json.dumps({"buffers": [{"uri": uri}]}))
                    with self.assertRaises(ValueError):
                        preview_fingerprint(path)

    def runtime_record(self):
        return {"model_sha1": "model", "source_first_face": 7, "source_face_count": 2,
                "variants": [{"material_state_hash": "state", "captured_texture": None,
                              "evidence": [{"trace": "task-a", "event_index": 0, "draw_run_index": 1}]}]}

    def test_runtime_material_does_not_imply_texture_or_segment_8_capture(self):
        material, texture, dynamic = model_coverage.runtime_coverage([self.runtime_record()], "model", 7, 2, 0)
        self.assertEqual("observed", material["status"])
        self.assertEqual("unobserved", texture["status"])
        self.assertEqual("missing", dynamic["status"])

    def test_overlapping_catalogs_do_not_duplicate_runtime_observations(self):
        record = self.runtime_record()
        material, _, _ = model_coverage.runtime_coverage([record, record], "model", 7, 2, None)
        self.assertEqual(1, material["draw_observation_count"])
        other = copy.deepcopy(record)
        other["variants"][0]["evidence"][0]["trace"] = "task-b"
        material, _, _ = model_coverage.runtime_coverage([record, other], "model", 7, 2, None)
        self.assertEqual(2, material["draw_observation_count"])

    def test_runtime_material_rejects_changed_model_or_face_span(self):
        for field, value in (("model_sha1", "other"), ("source_first_face", 8), ("source_face_count", 3)):
            record = self.runtime_record()
            record[field] = value
            with self.subTest(field=field), self.assertRaises(ValueError):
                model_coverage.runtime_coverage([record], "model", 7, 2, 0)

    def test_segment_8_exact_payload_is_distinct_from_effective_state(self):
        record = self.runtime_record()
        resolution = {"offset": "0x0", "status": "exact-runtime-list-state-later-overridden",
                      "payload_sha256": "payload"}
        record["variants"][0]["evidence"][0]["runtime_segment_8_resolution"] = resolution
        _, _, dynamic = model_coverage.runtime_coverage([record], "model", 7, 2, 0)
        self.assertEqual("observed", dynamic["status"])
        self.assertEqual(1, dynamic["exact_payload_count"])
        self.assertEqual(0, dynamic["effective_payload_count"])
        resolution["status"] = "segment-base-only-no-matching-call"
        _, _, dynamic = model_coverage.runtime_coverage([record], "model", 7, 2, 0)
        self.assertEqual("missing", dynamic["status"])
        with self.assertRaises(ValueError):
            model_coverage.runtime_coverage([record], "model", 7, 2, 16)

    def test_captured_texture_hash_is_checked(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "a.png").write_bytes(b"png")
            record = self.runtime_record()
            record["_source_root"] = root
            record["variants"][0]["captured_texture"] = {
                "file": "a.png", "png_sha1": hashlib.sha1(b"png").hexdigest()}
            _, texture, _ = model_coverage.runtime_coverage([record], "model", 7, 2, None)
            self.assertEqual("observed", texture["status"])
            (root / "a.png").write_bytes(b"changed")
            with self.assertRaises(ValueError):
                model_coverage.runtime_coverage([record], "model", 7, 2, None)

    def test_scene_slots_keep_collision_separate_from_rendering(self):
        payload = triangle_payload()
        segments = tuple(model_assets.ModelSegment(i, 0, len(payload), i == 3, payload) for i in range(4))
        bundle = model_assets.ModelBundle(5, 0, False, b"", segments)
        scenes, associations = model_scene_consumers.build_scene_graph([bundle], {"scenes": []})
        self.assertEqual(69, len(scenes))
        self.assertEqual(4, len(associations))
        self.assertEqual("absent", scenes[17]["bank_04_status"])
        slots = scenes[5]["initial_slots"]
        self.assertEqual("0x800B0E08", slots[2]["display_list"]["runtime_storage"])
        self.assertEqual(["conditional-display-list-submission"], [item["kind"] for item in slots[2]["consumers"]])
        self.assertEqual(["collision-input"], [item["kind"] for item in slots[3]["consumers"]])

    def test_placements_keep_bank_identity_and_missing_references(self):
        placements = {"scenes": [
            {"bank_index": 12, "scene_index": 5, "records": [{"index": 0, "model_source": [3, 5], "model_resolution_status": "resolved-bank-03-model"}]},
            {"bank_index": 11, "scene_index": 5, "records": [{"index": 1, "model_source": [4, 5, 0], "model_resolution_status": "resolved-bank-04-segment"}]},
            {"bank_index": 11, "scene_index": 17, "records": [{"index": 0, "model_source": [4, 17, 4], "model_resolution_status": "unavailable-bank-04-scene-or-segment"}]},
        ]}
        scenes, associations = model_scene_consumers.build_scene_graph([], placements)
        self.assertEqual({(3, 5, 0), (4, 5, 0)}, {(a["bank"], a["entry"], a["segment"]) for a in associations})
        self.assertEqual(1, len(scenes[17]["placement_tables"][0]["records"]))

    def test_scene_graph_rejects_sources_outside_reviewed_domain(self):
        with self.assertRaises(ValueError):
            model_scene_consumers.build_scene_graph([], {
                "scenes": [{"scene_index": 69, "bank_index": 11, "records": []}]
            })

    def test_coverage_missing_exports_cannot_claim_extraction_or_blender_success(self):
        payload = triangle_payload()
        segment = model_assets.ModelSegment(0, 0, len(payload), True, payload)
        bundle = model_assets.ModelBundle(5, 0, False, payload, (segment,))
        placements = {"scenes": [], "unresolved_bank_11_dispatch_references": []}
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            with mock.patch.object(model_assets, "BANK_INDICES", (3, 9)), \
                 mock.patch.object(model_assets, "load_model_bundles", return_value=(root / "rom", "z64", "digest", [bundle], ())), \
                 mock.patch.object(model_assets, "load_preview_texture_catalog", return_value={}), \
                 mock.patch.object(model_assets, "PREVIEW_TEXTURE_FAMILIES", ()), \
                 mock.patch.object(model_assets, "load_flat_asset_payloads", return_value={}), \
                 mock.patch.object(model_assets, "load_object_placement_manifest", return_value=(placements, {})):
                report = model_coverage.extract_coverage("us", None, root, root, root / "report.json")
                previous = (root / "report.json").read_bytes()
                activity = root / "activity.json"
                activity.write_text(json.dumps({
                    "family": "runtime-character-model-activity", "normalized_sha1": "digest",
                    "character_compositions": [{"entry": 5, "resolved_clusters": [{
                        "bank": 3, "entry": 5, "segment": 0, "material_run": 0,
                        "model_sha1": "changed", "first_face": 0, "face_count": 1,
                    }]}],
                }))
                with self.assertRaisesRegex(ValueError, "composition coverage"):
                    model_coverage.extract_coverage("us", None, root, root, root / "report.json", activity_path=activity)
                self.assertEqual(previous, (root / "report.json").read_bytes())
            self.assertEqual(2, report["summary"]["model_count"])
            self.assertEqual(2, report["summary"]["source_face_count"])
            self.assertEqual({"missing-extraction": 2}, report["summary"]["standalone_geometry"])
            self.assertEqual({"missing-preview": 2}, report["summary"]["blender_interchange"])
            self.assertEqual(["03:0005:00:0000", "09:0005:00:0000"], [r["key"] for r in report["material_runs"]])

    def test_render_to_texture_does_not_claim_body_composition(self):
        payload = triangle_payload()
        geometry = model_assets.parse_model_geometry(payload)
        segment = model_assets.ModelSegment(0, 0, len(payload), True, payload)
        bundle = model_assets.ModelBundle(5, 0, False, payload, (segment,))
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            activity = root / "activity.json"
            activity.write_text(json.dumps({
                "family": "runtime-character-model-activity", "normalized_sha1": "digest",
                "render_texture_compositions": [{"entry": 0, "resolved_clusters": [{
                    "bank": 1, "entry": 5, "segment": 0, "material_run": 0,
                    "model_sha1": hashlib.sha1(payload).hexdigest(), "first_face": 0, "face_count": 1,
                }]}],
            }))
            with mock.patch.object(model_assets, "BANK_INDICES", (1,)), \
                 mock.patch.object(model_assets, "load_model_bundles", return_value=(root / "rom", "z64", "digest", [bundle], ())), \
                 mock.patch.object(model_assets, "parse_geometry_for_bank", return_value=geometry), \
                 mock.patch.object(model_assets, "load_preview_texture_catalog", return_value={}), \
                 mock.patch.object(model_assets, "PREVIEW_TEXTURE_FAMILIES", ()), \
                 mock.patch.object(model_assets, "load_flat_asset_payloads", return_value={}), \
                 mock.patch.object(model_assets, "load_object_placement_manifest", return_value=({"scenes": [], "unresolved_bank_11_dispatch_references": []}, {})):
                report = model_coverage.extract_coverage("us", None, root, root, root / "report.json", activity_path=activity)
            row = report["material_runs"][0]
            self.assertEqual("unobserved", row["character_composition"]["status"])
            self.assertEqual("observed", row["render_to_texture"]["status"])
            self.assertEqual([0], row["render_to_texture"]["renderer_entries"])


if __name__ == "__main__":
    unittest.main()
