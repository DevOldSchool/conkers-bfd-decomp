"""Newly derived selected-preview verifier tests; no ROM inputs or mocks."""

import copy
import json
import struct
import tempfile
import unittest
from pathlib import Path

from scripts import model_assets as models
from test_model_assets import character_model_payload


ANIMATION_COUNTS = (
    "animation_clip_count",
    "animation_frame_count",
    "incompatible_animation_clip_count",
)


def two_frame_clip():
    descriptor = bytearray(18)
    descriptor[1] = 2
    descriptor[3] = 2
    descriptor[5] = 7
    descriptor[6] = 0x10
    descriptor[7] = 0x80
    struct.pack_into(">H", descriptor, 10, 0x8000)
    struct.pack_into(">3H", descriptor, 12, 0, 0, 0)
    bitstream = struct.pack(">3hB3hB", 16, -32, 48, 0, 32, 0, -16, 0x80)
    return models.CharacterAnimationClip(
        pair_index=4,
        frames=models.decode_character_animation_timeline(bytes(descriptor), bitstream),
        frame_byte_size=7,
        bitstream_padding_size=0,
        descriptor_runtime_zero_fill_size=0,
        duration_ticks=4,
        keyframe_step=4,
    )


def write_preview(output, entries=(75,)):
    """Write real one-triangle, one-joint previews; only entry75 has a clip."""
    geometry, layout = models.parse_character_model_geometry(character_model_payload())
    joints = tuple(layout["joints"])
    clip = two_frame_clip()
    output.mkdir()
    (output / "geometry").mkdir()
    (output / "README.txt").write_text("Synthetic selected-preview verifier fixture.\n")
    records = []
    for entry in entries:
        stem = f"{entry:04d}-00"
        clips = (clip,) if entry == 75 else ()
        normal, binary = models.encode_gltf(
            entry, 0, geometry, bank_index=1,
            character_joints=joints, character_animation_clips=clips,
        )
        bind, bind_binary = models.encode_gltf(
            entry, 0, geometry, bank_index=1,
            character_joints=joints, output_stem=stem + "-bind",
        )
        payloads = {
            stem + ".obj": models.encode_obj(entry, 0, geometry, bank_index=1),
            stem + ".mtl": models.encode_mtl(entry, 0, geometry, bank_index=1),
            stem + ".gltf": normal,
            stem + ".bin": binary,
            stem + "-bind.gltf": bind,
            stem + "-bind.bin": bind_binary,
        }
        for name, payload in payloads.items():
            (output / "geometry" / name).write_bytes(payload)
        records.append({
            "bank_entry": entry,
            "segment": 0,
            "object_file": f"geometry/{stem}.obj",
            "material_file": f"geometry/{stem}.mtl",
            "gltf_file": f"geometry/{stem}.gltf",
            "gltf_binary_file": f"geometry/{stem}.bin",
            "bind_gltf_file": f"geometry/{stem}-bind.gltf",
            "bind_gltf_binary_file": f"geometry/{stem}-bind.bin",
            "vertex_count": len(geometry.vertices),
            "source_face_count": len(geometry.faces),
            "face_count": len(geometry.faces),
            "omitted_zero_area_face_count": 0,
            "omitted_zero_area_faces": [],
            "texture_coordinate_count": models.texture_coordinate_count(geometry),
            "joint_count": len(joints),
            "animation_clip_count": len(clips),
            "animation_frame_count": sum(len(item.frames) for item in clips),
            "incompatible_animation_clip_count": 0,
            "material_runs": [
                {
                    "source_face_count": run.face_count,
                    "face_count": run.face_count,
                    "omitted_zero_area_face_count": 0,
                    "runtime_material": None,
                    "texture": None,
                }
                for run in geometry.material_runs
            ],
        })
    return {
        "bank_index": 1,
        "instructions_file": "README.txt",
        "textures": [],
        "models": records,
        "model_count": len(records),
        "selected_entries": sorted(entries),
        **{key: sum(record[key] for record in records) for key in ANIMATION_COUNTS},
        "runtime_lighting_replay_run_count": 0,
        "copied_runtime_mip_texture_count": 0,
        "copied_runtime_multitexture_count": 0,
    }


class PreviewSelectionVerificationTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.output = Path(self.temporary.name) / "preview"
        self.manifest = write_preview(self.output)
        self.selection = frozenset({75})

    def verify(self, manifest=None, *, selection=None, output=None):
        models.verify_preview_output(
            self.output if output is None else output,
            self.manifest if manifest is None else manifest,
            expected_entries=self.selection if selection is None else selection,
        )

    def test_selected_preview_and_optional_selection_metadata(self):
        self.assertEqual((1, 2, 0), tuple(self.manifest[key] for key in ANIMATION_COUNTS))
        for include_metadata in (True, False):
            with self.subTest(include_metadata=include_metadata):
                manifest = copy.deepcopy(self.manifest)
                if not include_metadata:
                    manifest.pop("selected_entries")
                self.verify(manifest)

    def test_multiple_entries_keep_distinct_animation_inventories(self):
        output = Path(self.temporary.name) / "pair"
        manifest = write_preview(output, entries=(75, 76))
        self.assertEqual([1, 0], [record["animation_clip_count"] for record in manifest["models"]])
        self.assertEqual([2, 0], [record["animation_frame_count"] for record in manifest["models"]])
        self.verify(manifest, selection=frozenset({75, 76}), output=output)

    def test_default_does_not_trust_manifest_selection(self):
        for kwargs in ({}, {"expected_entries": None}):
            with self.subTest(kwargs=kwargs), self.assertRaisesRegex(
                ValueError, "bank-01 preview animation inventory changed"
            ):
                models.verify_preview_output(self.output, self.manifest, **kwargs)

    def test_each_legacy_full_bank_inventory_total_stays_pinned(self):
        # Exercise the summary guard, not a purported complete-bank export.
        for key, value in zip(ANIMATION_COUNTS, (2620, 57731, 1)):
            with self.subTest(key=key):
                manifest = copy.deepcopy(self.manifest)
                manifest.update(zip(ANIMATION_COUNTS, (2621, 57732, 0)))
                manifest[key] = value
                with self.assertRaisesRegex(ValueError, "bank-01 preview animation inventory changed"):
                    models.verify_preview_output(self.output, manifest)

    def test_selection_requires_nonempty_frozenset_of_nonnegative_exact_integers(self):
        invalid = (
            set(), {75}, (75,), [75], frozenset(), frozenset({True}),
            frozenset({False}), frozenset({-1}), frozenset({75.0}),
            frozenset({"75"}),
        )
        for selection in invalid:
            with self.subTest(selection=selection), self.assertRaises(ValueError):
                self.verify(selection=selection)

    def test_explicit_selection_is_bounded_to_bank01(self):
        for bank in (3, 4, 9):
            with self.subTest(bank=bank):
                manifest = copy.deepcopy(self.manifest)
                manifest["bank_index"] = bank
                with self.assertRaises(ValueError):
                    self.verify(manifest)

    def test_missing_unexpected_and_duplicate_records_are_rejected(self):
        changes = (
            ("missing", lambda m: m["models"].clear()),
            ("unexpected", lambda m: m["models"][0].update(bank_entry=76)),
            ("duplicate", lambda m: m["models"].append(copy.deepcopy(m["models"][0]))),
        )
        for name, change in changes:
            with self.subTest(case=name):
                manifest = copy.deepcopy(self.manifest)
                change(manifest)
                manifest["model_count"] = len(manifest["models"])
                for key in ANIMATION_COUNTS:
                    manifest[key] = sum(record[key] for record in manifest["models"])
                manifest.pop("selected_entries")
                with self.assertRaises(ValueError):
                    self.verify(manifest)
        with self.assertRaises(ValueError):
            self.verify(selection=frozenset({75, 76}))

    def test_record_identity_segment_and_model_count_are_strict(self):
        cases = (
            ("bank_entry", True), ("bank_entry", 75.0), ("bank_entry", "75"),
            ("segment", 1), ("segment", False), ("segment", 0.0),
            ("segment", "0"), ("model_count", 0), ("model_count", 2),
            ("model_count", True), ("model_count", 1.0),
        )
        for key, value in cases:
            with self.subTest(key=key, value=value):
                manifest = copy.deepcopy(self.manifest)
                target = manifest if key == "model_count" else manifest["models"][0]
                target[key] = value
                with self.assertRaises(ValueError):
                    self.verify(manifest)

    def test_selection_metadata_must_be_canonical_and_match_caller(self):
        for entries in ([], [76], [75, 75], [75.0], [True], ["75"], (75,)):
            with self.subTest(entries=entries):
                manifest = copy.deepcopy(self.manifest)
                manifest["selected_entries"] = entries
                with self.assertRaises(ValueError):
                    self.verify(manifest)
        output = Path(self.temporary.name) / "pair"
        manifest = write_preview(output, entries=(75, 76))
        manifest["selected_entries"] = [76, 75]
        with self.assertRaises(ValueError):
            self.verify(manifest, selection=frozenset({75, 76}), output=output)

    def test_all_animation_counts_are_nonnegative_exact_integers(self):
        for scope in ("summary", "model"):
            for key in ANIMATION_COUNTS:
                for value in (-1, True, False, 1.0, "1", None):
                    with self.subTest(scope=scope, key=key, value=value):
                        manifest = copy.deepcopy(self.manifest)
                        target = manifest if scope == "summary" else manifest["models"][0]
                        target[key] = value
                        with self.assertRaises(ValueError):
                            self.verify(manifest)

    def test_all_animation_summaries_must_equal_model_sums(self):
        for scope in ("summary", "model"):
            for key in ANIMATION_COUNTS:
                with self.subTest(scope=scope, key=key):
                    manifest = copy.deepcopy(self.manifest)
                    target = manifest if scope == "summary" else manifest["models"][0]
                    target[key] += 1
                    with self.assertRaises(ValueError):
                        self.verify(manifest)

    def test_consistently_reported_incompatible_clips_are_rejected(self):
        manifest = copy.deepcopy(self.manifest)
        manifest["incompatible_animation_clip_count"] = 1
        manifest["models"][0]["incompatible_animation_clip_count"] = 1
        with self.assertRaises(ValueError):
            self.verify(manifest)

    def test_selected_verification_still_requires_normal_and_bind_binaries(self):
        for key in ("gltf_binary_file", "bind_gltf_binary_file"):
            with self.subTest(key=key):
                path = self.output / self.manifest["models"][0][key]
                original = path.read_bytes()
                path.unlink()
                try:
                    with self.assertRaisesRegex(ValueError, "missing an exported file"):
                        self.verify()
                finally:
                    path.write_bytes(original)

    def test_selected_verification_still_checks_normal_and_bind_buffer_sizes(self):
        for key in ("gltf_file", "bind_gltf_file"):
            with self.subTest(key=key):
                path = self.output / self.manifest["models"][0][key]
                original = path.read_bytes()
                document = json.loads(original)
                document["buffers"][0]["byteLength"] += 4
                path.write_text(json.dumps(document))
                try:
                    with self.assertRaisesRegex(ValueError, "buffer (size )?mismatch"):
                        self.verify()
                finally:
                    path.write_bytes(original)

    def test_selected_verification_still_checks_normal_and_bind_animations(self):
        record = self.manifest["models"][0]
        normal_path = self.output / record["gltf_file"]
        normal_bytes = normal_path.read_bytes()
        normal = json.loads(normal_bytes)
        self.assertEqual(1, len(normal["animations"]))
        removed = copy.deepcopy(normal)
        removed["animations"] = []
        normal_path.write_text(json.dumps(removed))
        with self.assertRaisesRegex(ValueError, "animation count mismatch"):
            self.verify()
        normal_path.write_bytes(normal_bytes)
        bind_path = self.output / record["bind_gltf_file"]
        bind = json.loads(bind_path.read_bytes())
        bind["animations"] = normal["animations"]
        bind_path.write_text(json.dumps(bind))
        with self.assertRaisesRegex(ValueError, "bind preview contains animations"):
            self.verify()


if __name__ == "__main__":
    unittest.main()
