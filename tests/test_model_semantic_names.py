"""Naming evidence never substitutes for model identity or runtime evidence."""

from __future__ import annotations

import copy
import hashlib
import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from scripts import model_assets as models, model_coverage, model_semantic_names as names
from scripts import model_haybot_rom_variants
from test_model_coverage import triangle_payload


def synthetic_registry(data=b"model"):
    registry = names.load_registry()
    record = registry["models"][0]
    record.update(source_bytes=len(data), model_sha1=hashlib.sha1(data).hexdigest(),
                  model_sha256=hashlib.sha256(data).hexdigest())
    return registry


class ModelSemanticNameTests(unittest.TestCase):
    def test_registry_is_pinned_and_agrees_with_rom_variant_evidence(self):
        registry = names.load_registry()
        record, = registry["models"]
        variant = model_haybot_rom_variants.contract()
        self.assertEqual((1, 75, 0, "Haybot"), tuple(record[k] for k in ("bank", "entry", "segment", "name")))
        self.assertEqual(variant["rom_sha1"], registry["rom_sha1"])
        self.assertEqual(variant["model_sha256"], record["model_sha256"])
        self.assertEqual(variant["updater_sha1"], record["model_specific_branch"]["sha1"])
        self.assertEqual(variant["descriptor_cycle"], record["model_specific_branch"]["descriptor_cycle"])
        self.assertEqual(8, len(record["consumers"]))
        for evidence in record["evidence"]:
            self.assertTrue((names.ROOT / evidence).is_file(), evidence)

    def test_replaced_registry_is_not_accepted_as_its_own_evidence(self):
        registry = names.load_registry()
        mutations = [lambda r: r["models"][0].update(name="Other character"),
                     lambda r: r["models"][0].update(entry=66),
                     lambda r: r["models"].append(copy.deepcopy(r["models"][0])),
                     lambda r: r["models"][0]["consumers"][0].update(sha1="0" * 40)]
        for mutate in mutations:
            changed = copy.deepcopy(registry)
            mutate(changed)
            with patch.object(Path, "read_bytes", return_value=json.dumps(changed).encode()):
                with self.assertRaisesRegex(ValueError, "registry changed"):
                    names.load_registry()

    def test_exact_name_is_descriptive_and_does_not_claim_actor_or_visibility(self):
        registry = synthetic_registry()
        result = names.resolve_name(registry, "us", registry["rom_sha1"], (1, 75, 0), b"model")
        self.assertEqual("Haybot", result["name"])
        self.assertEqual("reviewed-descriptive-model-label", result["kind"])
        self.assertEqual("01:0075:00", result["registry_key"])
        self.assertEqual({"status", "name", "kind", "registry_key", "evidence"}, set(result))

    def test_other_identity_domains_remain_unknown(self):
        registry = synthetic_registry()
        cases = [("eu", registry["rom_sha1"], (1, 75, 0)),
                 ("us", "0" * 40, (1, 75, 0)),
                 ("us", registry["rom_sha1"], (9, 75, 0)),
                 ("us", registry["rom_sha1"], (1, 69, 0)),
                 ("us", registry["rom_sha1"], (1, 75, 1)),
                 ("us", registry["rom_sha1"], (1, 66, 0))]
        for profile, digest, key in cases:
            with self.subTest(profile=profile, digest=digest, key=key):
                self.assertEqual({"status": "unknown", "name": None},
                                 names.resolve_name(registry, profile, digest, key, b"model"))

    def test_model_bytes_and_both_hashes_must_agree(self):
        registry = synthetic_registry()
        for data in (b"other", b"model\0"):
            with self.assertRaisesRegex(ValueError, "source identity"):
                names.resolve_name(registry, "us", registry["rom_sha1"], (1, 75, 0), data)
        for field in ("model_sha1", "model_sha256", "source_bytes"):
            changed = copy.deepcopy(registry)
            changed["models"][0][field] = 0 if field == "source_bytes" else "0" * len(changed["models"][0][field])
            with self.assertRaisesRegex(ValueError, "source identity"):
                names.resolve_name(changed, "us", registry["rom_sha1"], (1, 75, 0), b"model")

    def test_ambiguous_and_noninteger_keys_are_rejected(self):
        registry = synthetic_registry()
        for key in ((True, 75, 0), (1, 75.0, 0), (1, 75), (1, 75, False)):
            with self.assertRaisesRegex(ValueError, "integer"):
                names.resolve_name(registry, "us", registry["rom_sha1"], key, b"model")
        registry["models"].append(copy.deepcopy(registry["models"][0]))
        with self.assertRaisesRegex(ValueError, "ambiguous"):
            names.resolve_name(registry, "us", registry["rom_sha1"], (1, 75, 0), b"model")

    def test_consumer_guards_check_full_extents_and_branch(self):
        code = bytes(range(32))
        registry = synthetic_registry()
        record = registry["models"][0]
        record["consumers"] = [{"symbol": "func_test", "vram": "0x1004", "size_bytes": 16,
                                "sha1": hashlib.sha1(code[4:20]).hexdigest()}]
        record["model_specific_branch"] = {"start": "0x1008", "end": "0x100C",
                                           "sha1": hashlib.sha1(code[8:12]).hexdigest()}
        names.verify_consumers(code, 0x1000, registry)
        for offset in (4, 19):
            changed = bytearray(code)
            changed[offset] ^= 1
            with self.assertRaisesRegex(ValueError, "consumer changed"):
                names.verify_consumers(bytes(changed), 0x1000, registry)
        for base, data in ((0x1008, code), (0x1000, code[:19])):
            with self.assertRaisesRegex(ValueError, "consumer changed"):
                names.verify_consumers(data, base, registry)
        for field, value in (("start", "0x0"), ("end", "0x1008"), ("end", "0x1030"), ("sha1", "0" * 40)):
            changed = copy.deepcopy(registry)
            changed["models"][0]["model_specific_branch"][field] = value
            with self.assertRaisesRegex(ValueError, "shared branch changed"):
                names.verify_consumers(code, 0x1000, changed)

    def test_coverage_name_does_not_promote_other_evidence(self):
        payload = triangle_payload()
        registry = synthetic_registry(payload)
        registry["models"][0].update(bank=3, entry=5)
        digest = registry["rom_sha1"]
        segment = models.ModelSegment(0, 0, len(payload), True, payload)
        bundle = models.ModelBundle(5, 0, False, payload, (segment,))
        placements = {"scenes": [], "unresolved_bank_11_dispatch_references": []}
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            with patch.object(names, "load_registry", return_value=registry), \
                 patch.object(models, "BANK_INDICES", (3,)), \
                 patch.object(models, "load_model_bundles", return_value=(root / "rom", "z64", digest, [bundle], ())), \
                 patch.object(models, "load_preview_texture_catalog", return_value={}), \
                 patch.object(models, "PREVIEW_TEXTURE_FAMILIES", ()), \
                 patch.object(models, "load_object_material_context", return_value={"normalized_sha1": digest, "models": []}), \
                 patch.object(models, "load_flat_asset_payloads", return_value={}), \
                 patch.object(models, "load_object_placement_manifest", return_value=(placements, {})):
                report = model_coverage.extract_coverage("us", None, root, root, root / "report.json")
            record, = report["models"]
            self.assertEqual("Haybot", record["semantic_name"]["name"])
            self.assertEqual("missing-extraction", record["standalone_geometry"]["status"])
            self.assertEqual("missing", record["scene_association"]["status"])
            self.assertEqual("unverified", record["visual_parity"]["status"])
            self.assertEqual("unobserved", report["material_runs"][0]["runtime_material"]["status"])
            self.assertEqual({"reviewed": 1}, report["summary"]["semantic_name"])

    @unittest.skipUnless((names.ROOT / "roms/baserom.us.z64").is_file(), "reviewed US ROM not available")
    def test_owned_rom_confirms_model_and_complete_consumer_spans(self):
        report = names.audit_registry(names.ROOT / "roms/baserom.us.z64")
        self.assertEqual(8, report["consumer_count"])
        self.assertEqual(["Haybot"], [record["name"] for record in report["models"]])


if __name__ == "__main__":
    unittest.main()
