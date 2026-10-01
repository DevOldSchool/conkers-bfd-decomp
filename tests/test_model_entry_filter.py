"""Newly derived entry-filter extraction tests with synthetic source loaders."""
import copy
import json
import struct
import tempfile
import unittest
from contextlib import ExitStack, contextmanager
from dataclasses import replace
from pathlib import Path
from unittest.mock import patch

from scripts import model_assets as models, model_validation
from test_model_assets import character_model_payload


def make_bundle(entry, data):
    return models.ModelBundle(
        index=entry, type_flags=0, compressed=False, data=data,
        segments=(models.ModelSegment(0, 0, len(data), True, data),),
    )


def synthetic_animation_inputs():
    descriptor = bytearray(18)
    descriptor[1], descriptor[3], descriptor[5] = 2, 2, 7
    descriptor[6], descriptor[7] = 0x10, 0x80
    struct.pack_into(">H", descriptor, 10, 0x8000)
    struct.pack_into(">3H", descriptor, 12, 0, 0, 0)
    bitstream = struct.pack(">3hB3hB", 16, -32, 48, 0, 32, 0, -16, 0x80)
    manifest = {"entries": [{"bank_entry": 75, "clips": [{
        "timeline_status": "runtime-frame-layout-proven",
        "joint_count": 1,
        "descriptor_segment_index": 8,
        "bitstream_segment_index": 9,
        "pair_index": 4,
        "frame_byte_size": 7,
        "frame_count": 2,
        "bitstream_padding_size": 0,
        "descriptor_runtime_zero_fill_size": 0,
        "duration_ticks": 4,
        "keyframe_step": 4,
    }]}]}
    return manifest, {
        "animations/bank-02/segments/0075-0008.bin": bytes(descriptor),
        "animations/bank-02/segments/0075-0009.bin": bitstream,
    }


class SyntheticPreviewSources:
    """Mock source-loading boundaries; parse, encode and verify real outputs."""
    def __init__(self, root, data=None):
        self.root = root
        self.data = character_model_payload() if data is None else data
        self.bundles = [make_bundle(entry, self.data) for entry in (75, 76)]
        self.animation_manifest, self.animation_files = synthetic_animation_inputs()

    @contextmanager
    def patches(self):
        with ExitStack() as stack:
            self.bundle_loader = stack.enter_context(patch.object(
                models, "load_model_bundles",
                return_value=(self.root / "synthetic.us.z64", "z64", "synthetic", self.bundles, ()),
            ))
            stack.enter_context(patch.object(models, "load_flat_asset_payloads", return_value={}))
            stack.enter_context(patch.object(models, "load_preview_texture_catalog", return_value={}))
            stack.enter_context(patch.object(
                models, "load_character_animation_manifest",
                return_value=(self.animation_manifest, self.animation_files),
            ))
            stack.enter_context(patch.object(models, "load_character_defaults", return_value={"entries": {}}))
            self.morph_loader = stack.enter_context(patch.object(
                models, "load_character_morph_manifest", return_value={"models": []},
            ))
            yield self


class ModelEntryFilterTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.sources = SyntheticPreviewSources(self.root)
        self.output = self.root / "preview"

    def extract(self, selection=frozenset({75}), *, output=None, force=False, bank=1, **kwargs):
        return models.extract_model_preview(
            "us", None, self.root / "textures", self.output if output is None else output,
            force, bank, entry_filter=selection, **kwargs,
        )

    def test_selected_export_has_only_requested_normal_bind_and_animation(self):
        with self.sources.patches():
            manifest = self.extract()
        self.assertEqual([75], manifest["selected_entries"])
        self.assertEqual([(75, 0)], [(m["bank_entry"], m["segment"]) for m in manifest["models"]])
        self.assertEqual((1, 2, 0), tuple(manifest[k] for k in (
            "animation_clip_count", "animation_frame_count", "incompatible_animation_clip_count")))
        self.assertEqual({
            "0075-00.obj", "0075-00.mtl", "0075-00.gltf", "0075-00.bin",
            "0075-00-bind.gltf", "0075-00-bind.bin",
        }, {p.name for p in (self.output / "geometry").iterdir()})
        normal = json.loads((self.output / "geometry/0075-00.gltf").read_text())
        bind = json.loads((self.output / "geometry/0075-00-bind.gltf").read_text())
        self.assertEqual(1, len(normal["animations"]))
        self.assertEqual(2, normal["animations"][0]["extras"]["sourceFrameCount"])
        self.assertFalse(bind.get("animations"))
        self.assertEqual(manifest, json.loads((self.output / "manifest.json").read_text()))
        readme = (self.output / "README.txt").read_text()
        self.assertIn("geometry/0075-00-bind.gltf", readme)
        self.assertIn("geometry/0075-00.gltf", readme)
        self.assertNotIn("geometry/0000-00", readme)

    def test_normal_and_bind_geometry_rig_and_sources_are_preserved(self):
        original_bundles = copy.deepcopy(self.sources.bundles)
        original_animation = copy.deepcopy((self.sources.animation_manifest, self.sources.animation_files))
        geometry, layout = models.parse_character_model_geometry(self.sources.data)
        with self.sources.patches():
            manifest = self.extract()
        record = manifest["models"][0]
        self.assertEqual((3, 1, 1, 0), tuple(record[k] for k in (
            "vertex_count", "face_count", "joint_count", "omitted_zero_area_face_count")))
        for key in ("gltf_file", "bind_gltf_file"):
            report = model_validation.compare_geometry(
                self.output / record[key], geometry, tuple(layout["joints"]), record["material_runs"],
            )
            self.assertEqual((1, 3), (report["faces"], report["joint_corners"]))
        self.assertEqual(original_bundles, self.sources.bundles)
        self.assertEqual(original_animation, (self.sources.animation_manifest, self.sources.animation_files))

    def test_multiple_selected_entries_preserve_identical_per_model_files(self):
        with self.sources.patches():
            one = self.extract()
            pair_output = self.root / "pair"
            pair = self.extract(frozenset({76, 75}), output=pair_output)
        self.assertEqual([75, 76], pair["selected_entries"])
        self.assertEqual(2, pair["model_count"])
        self.assertEqual([1, 0], [m["animation_clip_count"] for m in pair["models"]])
        self.assertEqual([2, 0], [m["animation_frame_count"] for m in pair["models"]])
        for key in ("object_file", "material_file", "gltf_file", "gltf_binary_file", "bind_gltf_file", "bind_gltf_binary_file"):
            name = one["models"][0][key]
            self.assertEqual((self.output / name).read_bytes(), (pair_output / name).read_bytes())

    def test_zero_clip_selected_entry_is_not_treated_as_empty_selection(self):
        with self.sources.patches():
            manifest = self.extract(frozenset({76}))
        self.assertEqual([76], manifest["selected_entries"])
        self.assertEqual((1, 0, 0), tuple(manifest[k] for k in (
            "model_count", "animation_clip_count", "animation_frame_count")))

    def test_full_bank_default_still_exports_all_and_uses_legacy_guard(self):
        for explicit_none in (False, True):
            with self.subTest(explicit_none=explicit_none), self.sources.patches():
                output = self.root / ("none" if explicit_none else "default")
                kwargs = {"entry_filter": None} if explicit_none else {}
                with self.assertRaisesRegex(ValueError, "bank-01 preview animation inventory changed"):
                    models.extract_model_preview("us", None, self.root / "textures", output, False, 1, **kwargs)
                manifest = json.loads((output / "manifest.json").read_text())
                self.assertNotIn("selected_entries", manifest)
                self.assertEqual([75, 76], [m["bank_entry"] for m in manifest["models"]])

    def test_invalid_filter_is_rejected_before_source_loading_or_output_mutation(self):
        self.output.mkdir()
        sentinel = self.output / "keep.txt"
        sentinel.write_text("preserve")
        invalid = (frozenset(), {75}, [75], (75,), frozenset({True}), frozenset({False}),
                   frozenset({-1}), frozenset({75.0}), frozenset({"75"}))
        for selection in invalid:
            with self.subTest(selection=selection), self.sources.patches():
                with self.assertRaises(ValueError):
                    self.extract(selection, force=True)
                self.sources.bundle_loader.assert_not_called()
                self.assertEqual("preserve", sentinel.read_text())

    def test_selection_rejects_other_banks_before_source_loading(self):
        for bank in (3, 4, 9, True, 1.0):
            with self.subTest(bank=bank), self.sources.patches():
                with self.assertRaises(ValueError):
                    self.extract(bank=bank)
                self.sources.bundle_loader.assert_not_called()
                self.assertFalse(self.output.exists())

    def test_missing_selection_cannot_delete_forced_output(self):
        self.output.mkdir()
        sentinel = self.output / "keep.txt"
        sentinel.write_text("preserve")
        for selection in (frozenset({999}), frozenset({75, 999})):
            with self.subTest(selection=selection), self.sources.patches():
                with self.assertRaises(ValueError):
                    self.extract(selection, force=True)
                self.assertEqual({"keep.txt"}, {p.name for p in self.output.iterdir()})
                self.assertEqual("preserve", sentinel.read_text())

    def test_duplicate_empty_or_nonzero_selected_source_segments_are_rejected(self):
        original = self.sources.bundles
        first = original[0]
        variants = (
            [first, first, original[1]],
            [replace(first, segments=()), original[1]],
            [replace(first, segments=(replace(first.segments[0], data=b""),)), original[1]],
            [replace(first, segments=(replace(first.segments[0], index=1),)), original[1]],
            [replace(first, segments=(first.segments[0], first.segments[0])), original[1]],
        )
        for index, bundles in enumerate(variants):
            with self.subTest(variant=index):
                self.sources.bundles = bundles
                with self.sources.patches(), self.assertRaises(ValueError):
                    self.extract()
                self.assertFalse(self.output.exists())
        self.sources.bundles = original

    def test_rom_default_source_validation_receives_complete_bundle_corpus(self):
        with self.sources.patches():
            manifest = self.extract(rom_defaults=True)
            self.assertEqual(self.sources.bundles, self.sources.morph_loader.call_args.args[2])
        self.assertEqual([75], manifest["selected_entries"])
        self.assertEqual([75], [m["bank_entry"] for m in manifest["models"]])

    def test_real_verifier_rejects_mutated_selected_export(self):
        with self.sources.patches():
            manifest = self.extract()
        (self.output / manifest["models"][0]["gltf_binary_file"]).unlink()
        with self.assertRaisesRegex(ValueError, "missing an exported file"):
            models.verify_preview_output(self.output, manifest, expected_entries=frozenset({75}))


if __name__ == "__main__":
    unittest.main()
