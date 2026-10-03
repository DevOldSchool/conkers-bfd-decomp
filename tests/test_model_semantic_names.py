"""Naming evidence never substitutes for model identity or runtime evidence."""

from __future__ import annotations

import copy
import hashlib
import json
import tempfile
from types import SimpleNamespace
import unittest
from pathlib import Path
from unittest.mock import patch

from scripts import model_assets as models, model_coverage, model_semantic_names as names
from scripts import model_haybot_rom_variants
from test_model_coverage import triangle_payload


REVIEWED_CHARACTER_NAMES = {
    5: "Wasp", 10: "Mrs. Catfish", 14: "Corn Bag", 15: "Lady Cog — red",
    24: "Jack — metal box", 26: "Catfish — skeletal remains", 52: "TNT Imp",
    68: "Dung Beetle", 70: "Lady Cog — blue", 75: "Haybot", 76: "Lady Cog — green",
    107: "Electric Eel", 125: "Franky the Pitchfork — broken upper part",
    165: "Red Dinosaur", 173: "Wayne — cigar", 174: "Wanka — fat wasp",
    175: "Wanka — skinny wasp",
}
REVIEWED_OBJECT_NAMES = {
    (3, 1, 0): "Square-base hanging bell", (3, 60, 0): "Three throwing knives",
    (3, 61, 0): "Crossbow", (3, 62, 0): "Chainsaw",
    (3, 77, 0): "Cock and Plucker sign", (3, 82, 0): "Curved sword",
    (3, 83, 0): "Revolver", (3, 87, 0): "Grenade crate",
    (3, 91, 0): "Vitamin bottle", (3, 95, 0): "Tracked vehicle",
    (3, 98, 0): "Closed / Back at 10 sign", (3, 110, 0): "Bombs crate",
    (9, 29, 0): "Cigar", (9, 133, 0): "Military helmet",
    (9, 162, 0): "Wall-mounted flame (UI model)", (9, 164, 0): "Upright cash bundle",
    (9, 165, 0): "Upright cash bundle — attachment variant", (9, 185, 0): "Conker HUD head",
    (9, 186, 0): "Digital timer", (9, 345, 0): "Hanging bell",
}
REVIEWED_NAMES = {(1, entry, 0): name for entry, name in REVIEWED_CHARACTER_NAMES.items()}
REVIEWED_NAMES.update(REVIEWED_OBJECT_NAMES)


def synthetic_registry(data=b"model"):
    registry = names.load_registry()
    record = next(r for r in registry["models"] if (r["bank"], r["entry"], r["segment"]) == (1, 75, 0))
    registry["models"] = [record]
    record.update(source_bytes=len(data), model_sha1=hashlib.sha1(data).hexdigest(),
                  model_sha256=hashlib.sha256(data).hexdigest())
    return registry


def synthetic_consumers():
    code = bytes(range(32))
    registry = synthetic_registry()
    record = registry["models"][0]
    record["consumers"] = [{"symbol": "func_test", "vram": "0x1004", "size_bytes": 16,
                            "sha1": hashlib.sha1(code[4:20]).hexdigest(), "role": "shared test span"}]
    record["model_specific_branch"].update(symbol="func_test", start="0x1008", end="0x100C",
                                          sha1=hashlib.sha1(code[8:12]).hexdigest())
    return code, registry


class ModelSemanticNameTests(unittest.TestCase):
    def test_registry_is_pinned_and_agrees_with_rom_variant_evidence(self):
        registry = names.load_registry()
        self.assertEqual(2, registry["schema_version"])
        self.assertEqual(models.BANK_INDICES, names.SUPPORTED_BANKS)
        self.assertEqual(REVIEWED_NAMES,
                         {tuple(r[k] for k in ("bank", "entry", "segment")): r["name"]
                          for r in registry["models"]})
        self.assertEqual(37, len(registry["models"]))
        record = next(r for r in registry["models"] if (r["bank"], r["entry"], r["segment"]) == (1, 75, 0))
        variant = model_haybot_rom_variants.contract()
        self.assertEqual(variant["rom_sha1"], registry["rom_sha1"])
        self.assertEqual(variant["model_sha256"], record["model_sha256"])
        self.assertEqual(variant["updater_sha1"], record["model_specific_branch"]["sha1"])
        self.assertEqual(variant["descriptor_cycle"], record["model_specific_branch"]["descriptor_cycle"])
        self.assertEqual(8, len(record["consumers"]))
        for record in registry["models"]:
            for evidence in record["evidence"]:
                self.assertTrue((names.ROOT / evidence).is_file(), evidence)
            if (record["bank"], record["entry"], record["segment"]) != (1, 75, 0):
                self.assertNotIn("model_specific_branch", record)
                if record["bank"] == 1:
                    self.assertEqual(8 if record["entry"] in (15, 70, 76) else 7,
                                     len(record["consumers"]))
                self.assertNotIn("func_15061B4C", {c["symbol"] for c in record["consumers"]})

    def test_lady_cog_eye_part_consumer_is_full_span_and_exactly_scoped(self):
        registry = names.load_registry()
        consumer = {
            "symbol": "func_1507E3C0", "vram": "0x1507E3C0", "size_bytes": 320,
            "sha1": "eb9bcf2cd630cf7c6dde5111e846ebb8934d575d",
            "role": "actor_update_lady_cog_eye_parts; exact model gate 15/70/76, raw-ROM semantics only",
        }
        selected = {(1, entry, 0) for entry in (15, 70, 76)}
        for record in registry["models"]:
            key = tuple(record[field] for field in ("bank", "entry", "segment"))
            matches = [c for c in record["consumers"] if c["symbol"] == consumer["symbol"]]
            with self.subTest(key=key):
                self.assertEqual([consumer] if key in selected else [], matches)
                if key in selected:
                    self.assertIn("docs/evidence/lady_cog_eye_part_semantics.md", record["evidence"])
                    self.assertNotIn("model_specific_branch", record)

    def test_object_models_keep_their_reviewed_consumer_domains(self):
        registry = names.load_registry()
        records = {tuple(r[k] for k in ("bank", "entry", "segment")): r for r in registry["models"]}
        placed = {"func_150039E0", "func_151135C4", "func_151137D4"}
        action = {"func_1514DCAC", "func_15083568", "func_15030AF4", "func_1502FFD8", "func_1502FE10"}
        ui = {"func_151EB06C", "func_151ED90C", "func_151EDBDC", "func_1503F62C",
              "func_1502FE10", "func_1510CE60"}
        expected = {key: placed for key in REVIEWED_OBJECT_NAMES if key[0] == 3}
        expected.update({
            (9, 29, 0): action,
            (9, 133, 0): action | {"func_1503F62C"},
            (9, 162, 0): ui,
            (9, 164, 0): ui | {"func_1510D0EC"},
            (9, 165, 0): {"func_150FAE18", "func_151D6BFC", "func_15157010", "func_150FB1E8",
                          "func_151D710C", "func_15157420", "func_15133EEC", "func_1503F62C", "func_1502FE10"},
            (9, 185, 0): {"func_1509093C", "func_150911F4", "func_1502FE10", "func_1510D0EC"},
            (9, 186, 0): {"func_15093878", "func_1518C900", "func_150938BC", "func_15168E54",
                          "func_15168E34", "func_1510D0EC", "func_150A7D00"},
            (9, 345, 0): {"func_15010A60", "func_1513264C", "func_151336A8", "func_15132B80"},
        })
        character_consumers = {c["symbol"] for r in registry["models"] if r["bank"] == 1
                               for c in r["consumers"]}
        for key, consumers in expected.items():
            with self.subTest(key=key):
                self.assertEqual(consumers, {c["symbol"] for c in records[key]["consumers"]})
                self.assertTrue(consumers.isdisjoint(character_consumers))
                self.assertNotIn("model_specific_branch", records[key])
        self.assertEqual(33, len(set().union(*expected.values())))
        self.assertEqual(84, sum(len(consumers) for consumers in expected.values()))

    def test_object_names_resolve_only_the_exact_bank_entry_and_segment(self):
        registry = names.load_registry()
        # Equal synthetic bytes cannot merge names across identity namespaces.
        payload = b"same source bytes"
        for record in registry["models"]:
            record.update(source_bytes=len(payload), model_sha1=hashlib.sha1(payload).hexdigest(),
                          model_sha256=hashlib.sha256(payload).hexdigest())
        for key, expected in REVIEWED_NAMES.items():
            with self.subTest(key=key):
                result = names.resolve_name(registry, "us", registry["rom_sha1"], key, payload)
                self.assertEqual(expected, result["name"])
                self.assertEqual("reviewed-descriptive-model-label", result["kind"])
                self.assertEqual({"status", "name", "kind", "registry_key", "evidence"}, set(result))
        # Action IDs 35/68, lookup selector 86, nearby variants, and Conker's
        # bank-01 body gain no name from the newly reviewed bank-09 models.
        unknown = [(9, 35, 0), (9, 68, 0), (9, 86, 0), (1, 0, 0), (1, 164, 0),
                   (1, 185, 0), (3, 345, 0), (9, 1, 0), (9, 186, 1),
                   (3, 0, 0), (3, 39, 0), (3, 109, 0), (9, 42, 0)]
        for key in unknown:
            with self.subTest(key=key):
                self.assertEqual({"status": "unknown", "name": None},
                                 names.resolve_name(registry, "us", registry["rom_sha1"], key, payload))

    def test_cash_variants_have_distinct_source_pins_and_bounded_labels(self):
        records = {tuple(r[k] for k in ("bank", "entry", "segment")): r
                   for r in names.load_registry()["models"]}
        for field in ("model_sha1", "model_sha256", "source_bytes"):
            self.assertNotEqual(records[(9, 164, 0)][field], records[(9, 165, 0)][field])
        self.assertEqual("Digital timer", records[(9, 186, 0)]["name"])
        self.assertEqual("Conker HUD head", records[(9, 185, 0)]["name"])

    def test_replaced_registry_is_not_accepted_as_its_own_evidence(self):
        registry = names.load_registry()
        mutations = [lambda r: r["models"][0].update(name="Other character"),
                     lambda r: r["models"][0].update(entry=66),
                     lambda r: r["models"].append(copy.deepcopy(r["models"][0])),
                     lambda r: r["models"][0]["consumers"][0].update(sha1="0" * 40),
                     lambda r: r.update(registry_sha256=names.REGISTRY_SHA256)]
        for mutate in mutations:
            changed = copy.deepcopy(registry)
            mutate(changed)
            with patch.object(Path, "read_bytes", return_value=json.dumps(changed).encode()):
                with self.assertRaisesRegex(ValueError, "registry changed"):
                    names.load_registry()

    def test_duplicate_json_keys_rejected_even_after_review_pin_update(self):
        raw = names.REGISTRY_PATH.read_bytes().replace(b'"schema_version": 2,',
                                                      b'"schema_version": 1, "schema_version": 2,')
        # A hypothetical reviewer-updated pin cannot hide ambiguous JSON syntax.
        with patch.object(names, "REGISTRY_SHA256", hashlib.sha256(raw).hexdigest()), \
             patch.object(Path, "read_bytes", return_value=raw):
            with self.assertRaisesRegex(ValueError, "duplicate JSON keys"):
                names.load_registry()

    def test_exact_name_is_descriptive_and_does_not_claim_actor_or_visibility(self):
        registry = synthetic_registry()
        result = names.resolve_name(registry, "us", registry["rom_sha1"], (1, 75, 0), b"model")
        self.assertEqual("Haybot", result["name"])
        self.assertEqual("reviewed-descriptive-model-label", result["kind"])
        self.assertEqual("01:0075:00", result["registry_key"])
        self.assertEqual({"status", "name", "kind", "registry_key", "evidence"}, set(result))

    def test_other_identity_domains_remain_unknown(self):
        registry = names.load_registry()
        cases = [("eu", registry["rom_sha1"], (1, 75, 0)),
                 ("us", "0" * 40, (1, 75, 0)),
                 ("us", registry["rom_sha1"], (9, 75, 0)),
                 ("us", registry["rom_sha1"], (1, 69, 0)),
                 ("us", registry["rom_sha1"], (1, 75, 1)),
                 ("us", registry["rom_sha1"], (1, 0, 0)),
                 ("us", registry["rom_sha1"], (1, 12, 0)),
                 ("us", registry["rom_sha1"], (1, 54, 0)),
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
        with self.assertRaisesRegex(ValueError, "ambiguous"):
            names.validate_registry(registry)

    def test_exact_schema_and_malformed_expanded_records_are_rejected(self):
        mutations = [
            lambda r: r.update(extra="unreviewed"),
            lambda r: r.pop("rom_sha256"),
            lambda r: r.update(schema_version=True),
            lambda r: r.update(schema_version=1),
            lambda r: r.update(profile="eu"),
            lambda r: r.update(name_kind="original-symbol"),
            lambda r: r.update(models=[]),
            lambda r: r.update(models={}),
            lambda r: r.update(rom_size_bytes=0),
            lambda r: r.update(rom_size_bytes=True),
            lambda r: r.update(rom_sha1="G" * 40),
            lambda r: r.update(rom_sha256="0" * 63),
        ]
        model_mutations = [
            lambda r: r.update(extra="unreviewed"), lambda r: r.pop("model_sha256"),
            lambda r: r.update(name=""), lambda r: r.update(name=" Wasp"),
            lambda r: r.update(bank=True), lambda r: r.update(entry=False),
            lambda r: r.update(segment=True), lambda r: r.update(entry=5.0),
            lambda r: r.update(entry=-1), lambda r: r.update(segment=-1),
            lambda r: r.update(bank=17), lambda r: r.update(source_bytes=0),
            lambda r: r.update(source_bytes=-1), lambda r: r.update(source_bytes=True),
            lambda r: r.update(model_sha1="x" * 40), lambda r: r.update(model_sha256="0" * 63),
            lambda r: r.update(evidence=[]), lambda r: r.update(evidence="docs/proof.md"),
            lambda r: r.update(evidence=[""]), lambda r: r.update(evidence=["/absolute.md"]),
            lambda r: r.update(evidence=["../outside.md"]), lambda r: r.update(evidence=["docs/../outside.md"]),
            lambda r: r.update(evidence=["./proof.md"]), lambda r: r.update(evidence=["docs//proof.md"]),
            lambda r: r.update(evidence=["C:\\proof.md"]), lambda r: r.update(evidence=["https://example.com"]),
            lambda r: r.update(evidence=["docs/\0proof.md"]), lambda r: r.update(evidence=[True]),
            lambda r: r.update(evidence=["docs/proof.md", "docs/proof.md"]),
            lambda r: r.update(limitations=[]), lambda r: r.update(limitations=[""]),
            lambda r: r.update(consumers=[]), lambda r: r.update(consumers={}),
            lambda r: r.update(model_specific_branch=None),
        ]
        for mutate in mutations:
            registry = names.load_registry()
            mutate(registry)
            with self.subTest(mutation=mutate):
                with self.assertRaises(ValueError):
                    names.validate_registry(registry)
        # Put each malformed record after a valid one to exercise expansion parsing.
        for mutate in model_mutations:
            registry = names.load_registry()
            mutate(registry["models"][-1])
            with self.subTest(mutation=mutate):
                with self.assertRaises(ValueError):
                    names.validate_registry(registry)

    def test_malformed_consumer_ranges_and_conflicting_shared_pins_are_rejected(self):
        for field, value in (("symbol", ""), ("symbol", "invalid-symbol"),
                             ("vram", "-1"), ("vram", True), ("vram", "0x0"),
                             ("vram", "0xFFFFFFFF"), ("size_bytes", 0),
                             ("size_bytes", -1), ("size_bytes", True), ("size_bytes", 4.0),
                             ("sha1", "z" * 40), ("role", ""), ("extra", "unknown")):
            _, registry = synthetic_consumers()
            registry["models"][0]["consumers"][0][field] = value
            with self.subTest(field=field, value=value), self.assertRaises(ValueError):
                names.validate_registry(registry)
        _, registry = synthetic_consumers()
        record = registry["models"][0]
        record["consumers"].append(copy.deepcopy(record["consumers"][0]))
        with self.assertRaisesRegex(ValueError, "duplicate model consumer"):
            names.validate_registry(registry)
        for field, value in (("sha1", "0" * 40), ("vram", "0x1000"),
                             ("size_bytes", 15), ("symbol", "func_alias")):
            _, registry = synthetic_consumers()
            extra = copy.deepcopy(registry["models"][0])
            extra.update(entry=76)
            extra.pop("model_specific_branch")
            extra["consumers"][0][field] = value
            registry["models"].append(extra)
            with self.subTest(field=field), self.assertRaisesRegex(ValueError, "shared consumer"):
                names.validate_registry(registry)

    def test_branch_must_identify_and_fit_its_own_consumer(self):
        for field, value in (("symbol", "func_absent"), ("model_index", 76),
                             ("model_index", True), ("start", "0x1000"),
                             ("end", "0x1008"), ("end", "0x1015"),
                             ("sha1", "0" * 39), ("phase_offset", -1),
                             ("descriptor_cycle", []), ("descriptor_cycle", [True]),
                             ("descriptor_cycle", [256]), ("extra", "unknown")):
            _, registry = synthetic_consumers()
            registry["models"][0]["model_specific_branch"][field] = value
            with self.subTest(field=field, value=value), self.assertRaises(ValueError):
                names.validate_registry(registry)

    def test_consumer_guards_check_full_extents_and_optional_branch(self):
        code, registry = synthetic_consumers()
        self.assertEqual(1, names.verify_consumers(code, 0x1000, registry))
        for offset in (4, 19):
            changed = bytearray(code)
            changed[offset] ^= 1
            with self.assertRaisesRegex(ValueError, "consumer changed"):
                names.verify_consumers(bytes(changed), 0x1000, registry)
        for base, data in ((0x1008, code), (0x1000, code[:19])):
            with self.assertRaisesRegex(ValueError, "consumer changed"):
                names.verify_consumers(data, base, registry)
        changed = copy.deepcopy(registry)
        changed["models"][0]["model_specific_branch"]["sha1"] = "0" * 40
        with self.assertRaisesRegex(ValueError, "branch changed"):
            names.verify_consumers(code, 0x1000, changed)
        extra = copy.deepcopy(registry["models"][0])
        extra.update(entry=76)
        extra.pop("model_specific_branch")
        registry["models"].append(extra)
        self.assertEqual(1, names.verify_consumers(code, 0x1000, registry))
        registry["models"][0].pop("model_specific_branch")
        self.assertEqual(1, names.verify_consumers(code, 0x1000, registry))

    def test_coverage_named_and_unlisted_identities_keep_independent_evidence(self):
        payload = triangle_payload()
        registry = synthetic_registry(payload)
        registry["models"][0].update(bank=3, entry=5)
        registry["models"][0].pop("model_specific_branch")
        extra = copy.deepcopy(registry["models"][0])
        extra.update(entry=6, name="Synthetic second label")
        registry["models"].append(extra)
        names.validate_registry(registry)
        digest = registry["rom_sha1"]
        segment = models.ModelSegment(0, 0, len(payload), True, payload)
        bundles = [models.ModelBundle(index, 0, False, payload, (segment,)) for index in (5, 6, 7)]
        placements = {"scenes": [], "unresolved_bank_11_dispatch_references": []}
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            with patch.object(names, "load_registry", return_value=registry), \
                 patch.object(models, "BANK_INDICES", (3,)), \
                 patch.object(models, "load_model_bundles", return_value=(root / "rom", "z64", digest, bundles, ())), \
                 patch.object(models, "load_preview_texture_catalog", return_value={}), \
                 patch.object(models, "PREVIEW_TEXTURE_FAMILIES", ()), \
                 patch.object(models, "load_object_material_context", return_value={"normalized_sha1": digest, "models": []}), \
                 patch.object(models, "load_flat_asset_payloads", return_value={}), \
                 patch.object(models, "load_object_placement_manifest", return_value=(placements, {})):
                report = model_coverage.extract_coverage("us", None, root, root, root / "report.json")
        self.assertEqual(["Haybot", "Synthetic second label", None],
                         [r["semantic_name"]["name"] for r in report["models"]])
        self.assertEqual(["03:0005:00", "03:0006:00", None],
                         [r["semantic_name"].get("registry_key") for r in report["models"]])
        for record in report["models"]:
            self.assertEqual("missing-extraction", record["standalone_geometry"]["status"])
            self.assertEqual("missing", record["scene_association"]["status"])
            self.assertEqual("unverified", record["visual_parity"]["status"])
        self.assertTrue(all(r["runtime_material"]["status"] == "unobserved" for r in report["material_runs"]))
        self.assertEqual({"reviewed": 2, "unknown": 1}, report["summary"]["semantic_name"])
        self.assertEqual("reviewed-registry", report["evidence_availability"]["semantic_name_registry"])

    def test_audit_loads_each_listed_bank_and_counts_unique_consumers(self):
        code, registry = synthetic_consumers()
        record = registry["models"][0]
        record.pop("model_specific_branch")
        record.update(bank=3, entry=5)
        extra = copy.deepcopy(record)
        extra.update(bank=4, entry=6, name="Synthetic second label")
        registry["models"].append(extra)
        normalized = b"synthetic normalized ROM"
        registry.update(rom_sha1=hashlib.sha1(normalized).hexdigest(),
                        rom_sha256=hashlib.sha256(normalized).hexdigest(), rom_size_bytes=len(normalized))
        digest = registry["rom_sha1"]
        segment = models.ModelSegment(0, 0, 5, True, b"model")
        banks = {3: [models.ModelBundle(5, 0, False, b"model", (segment,))],
                 4: [models.ModelBundle(6, 0, False, b"model", (segment,))]}
        rom_path = Path("synthetic.rom")

        def bundles(profile, path, bank):
            self.assertEqual(("us", rom_path), (profile, path))
            return rom_path, "z64", digest, banks[bank], ()

        with patch.object(names, "load_registry", return_value=registry), \
             patch.object(models, "resolve_rom", return_value=(rom_path, {"game_start": 0, "game_end": 1, "game_vram": 0x1000})), \
             patch.object(Path, "read_bytes", return_value=b"source order ROM"), \
             patch.object(models, "normalize_rom", return_value=(normalized, "v64")), \
             patch.object(models, "parse_game_archive", return_value=SimpleNamespace(code=code)), \
             patch.object(models, "load_model_bundles", side_effect=bundles) as loader:
            report = names.audit_registry(rom_path)
            self.assertEqual([3, 4], [call.args[2] for call in loader.call_args_list])
            self.assertEqual([3, 4], report["banks"])
            self.assertEqual(1, report["consumer_count"])
            self.assertEqual(2, report["consumer_reference_count"])
            self.assertEqual(0, report["model_specific_branch_count"])
            self.assertEqual(["03:0005:00", "04:0006:00"], [r["registry_key"] for r in report["models"]])
            banks[4] = []
            with self.assertRaisesRegex(ValueError, "absent"):
                names.audit_registry(rom_path)
            banks[4] = [models.ModelBundle(6, 0, False, b"model", (segment, segment))]
            with self.assertRaisesRegex(ValueError, "ambiguous extracted"):
                names.audit_registry(rom_path)

    def test_audit_rejects_changed_normalized_rom_and_reread_digest(self):
        normalized = b"synthetic normalized ROM"
        code, registry = synthetic_consumers()
        registry.update(rom_sha1=hashlib.sha1(normalized).hexdigest(),
                        rom_sha256=hashlib.sha256(normalized).hexdigest(), rom_size_bytes=len(normalized))
        rom_path = Path("synthetic.rom")
        with patch.object(names, "load_registry", return_value=registry), \
             patch.object(models, "resolve_rom", return_value=(rom_path, {"game_start": 0, "game_end": 1, "game_vram": 0x1000})), \
             patch.object(Path, "read_bytes", return_value=normalized), \
             patch.object(models, "normalize_rom", return_value=(normalized, "z64")), \
             patch.object(models, "parse_game_archive", return_value=SimpleNamespace(code=code)), \
             patch.object(models, "load_model_bundles", return_value=(rom_path, "z64", "0" * 40, [], ())):
            with self.assertRaisesRegex(ValueError, "ROM changed"):
                names.audit_registry(rom_path)
            for field, value in (("rom_sha1", "0" * 40), ("rom_sha256", "0" * 64), ("rom_size_bytes", 1)):
                previous = registry[field]
                registry[field] = value
                with self.subTest(field=field), self.assertRaisesRegex(ValueError, "different ROM"):
                    names.audit_registry(rom_path)
                registry[field] = previous

    @unittest.skipUnless((names.ROOT / "roms/baserom.us.z64").is_file(), "reviewed US ROM not available")
    def test_owned_rom_confirms_all_models_and_complete_consumer_spans(self):
        report = names.audit_registry(names.ROOT / "roms/baserom.us.z64")
        self.assertEqual(42, report["consumer_count"])
        self.assertEqual(207, report["consumer_reference_count"])
        self.assertEqual(1, report["model_specific_branch_count"])
        self.assertEqual([1, 3, 9], report["banks"])
        self.assertEqual([REVIEWED_NAMES[key] for key in sorted(REVIEWED_NAMES)],
                         [record["name"] for record in report["models"]])


if __name__ == "__main__":
    unittest.main()
