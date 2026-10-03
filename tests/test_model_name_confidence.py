"""Confidence is source-bound metadata, never a gallery-derived identity claim."""

from __future__ import annotations

import copy
from collections import Counter
import hashlib
import io
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from scripts import model_semantic_names as names
from model_name_fixtures import (EXPECTED_COUNTS, RESULT_FIELDS,
                                 resolve_synthetic_name, synthetic_confidence)


class ModelNameConfidenceTests(unittest.TestCase):
    def setUp(self):
        self.registry = names.load_registry()
        self.confidence = names.load_confidence(self.registry)

    def test_exact_registry_bytes_and_all_267_record_bindings(self):
        self.assertEqual(names.REGISTRY_SHA256,
                         hashlib.sha256(names.REGISTRY_PATH.read_bytes()).hexdigest())
        self.assertEqual(names.CONFIDENCE_SHA256,
                         hashlib.sha256(names.CONFIDENCE_PATH.read_bytes()).hexdigest())
        self.assertEqual(EXPECTED_COUNTS, Counter(r["classification"] for r in self.confidence["models"]))
        self.assertEqual(267, len(self.confidence["models"]))
        self.assertEqual([names.registry_key(r) for r in self.registry["models"]],
                         [r["registry_key"] for r in self.confidence["models"]])
        # Only hashes, numeric identities and bounded classes are published.
        raw = names.CONFIDENCE_PATH.read_text()
        for forbidden in ("/workspace/", "build/", "canonical_provenance", "evidence_rows",
                          "starting_main_gallery_provenance", "existing_label"):
            self.assertNotIn(forbidden, raw)

    def test_all_classes_resolve_as_descriptions_without_human_or_qualifier_confirmation(self):
        payload = b"synthetic source bytes for confidence tests"
        registry = copy.deepcopy(self.registry)
        for record in registry["models"]:
            record.update(source_bytes=len(payload), model_sha1=hashlib.sha1(payload).hexdigest(),
                          model_sha256=hashlib.sha256(payload).hexdigest())
        confidence = synthetic_confidence(registry)
        classifications = {r["registry_key"]: r["classification"] for r in confidence["models"]}
        for record in registry["models"]:
            key = tuple(record[field] for field in ("bank", "entry", "segment"))
            result = names.resolve_name(registry, "us", registry["rom_sha1"], key, payload,
                                        confidence=confidence)
            self.assertEqual(RESULT_FIELDS, set(result))
            self.assertEqual(record["name"], result["descriptor"])
            self.assertEqual(result["descriptor"], result["name"])
            self.assertEqual(classifications[names.registry_key(record)], result["status"])
            self.assertIs(False, result["semantic_identity_confirmed"])
            self.assertEqual("not_individually_audited", result["human_confirmation_status"])
            self.assertEqual("not_individually_audited", result["qualifier_confirmation_status"])
            if result["status"] == "appearance_only_description":
                self.assertEqual("identity_unknown_or_not_applicable", result["semantic_identity_status"])
            self.assertNotIn(result["status"], ("reviewed", "known", "resolved", "confirmed"))

    def test_appearance_labels_include_three_bat_records_and_ambiguous_character_words(self):
        records = {r["registry_key"]: r for r in self.confidence["models"]}
        for entry in (121, 152, 154, 155, 156, 157, 159, 160, 162):
            self.assertEqual("appearance_only_description", records[f"01:{entry:04d}:00"]["classification"])

    def test_missing_stale_duplicate_and_malformed_confidence_fail_closed(self):
        mutations = [
            lambda c: c.update(schema_version=True), lambda c: c.update(schema_version=2),
            lambda c: c.update(registry_sha256="0" * 64), lambda c: c.update(profile="eu"),
            lambda c: c.update(rom_sha1="0" * 40), lambda c: c.update(rom_sha256="0" * 64),
            lambda c: c.update(rom_size_bytes=True), lambda c: c.update(extra="unreviewed"),
            lambda c: c.update(models=[]), lambda c: c.update(models={}),
            lambda c: c["models"].pop(), lambda c: c["models"].append(copy.deepcopy(c["models"][0])),
            lambda c: c["models"][0].update(registry_key="01:9999:00"),
            lambda c: c["models"][0].update(bank=True),
            lambda c: c["models"][0].update(entry=9999, registry_key="01:9999:00"),
            lambda c: c["models"][0].update(classification="confirmed"),
            lambda c: c["models"][0].update(classification=[]),
            lambda c: c["models"][0].pop("classification"),
            lambda c: c["models"][0].update(semantic_identity_confirmed=True),
            lambda c: c["models"][0].update(source_bytes=True),
            lambda c: c["models"][0].update(model_sha1="0" * 40),
            lambda c: c["models"][0].update(model_sha256="0" * 64),
            lambda c: c["models"][0].update(source_record_sha256="0" * 64),
        ]
        for mutate in mutations:
            changed = copy.deepcopy(self.confidence)
            mutate(changed)
            with self.subTest(mutation=mutate), self.assertRaises(ValueError):
                names.validate_confidence(changed, self.registry)
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "missing.json"
            with patch.object(names, "CONFIDENCE_PATH", path), self.assertRaises(FileNotFoundError):
                names.load_confidence(self.registry)
            path.write_text(json.dumps(self.confidence) + "\n")
            with patch.object(names, "CONFIDENCE_PATH", path), self.assertRaisesRegex(ValueError, "sidecar changed"):
                names.load_confidence(self.registry)

    def test_duplicate_json_fields_are_rejected_even_if_pin_is_updated(self):
        raw = names.CONFIDENCE_PATH.read_bytes().replace(b'"schema_version": 1,',
                                                       b'"schema_version": 1, "schema_version": 1,')
        with patch.object(names, "CONFIDENCE_SHA256", hashlib.sha256(raw).hexdigest()), \
             patch.object(Path, "read_bytes", return_value=raw), \
             self.assertRaisesRegex(ValueError, "duplicate JSON keys"):
            names.load_confidence(self.registry)

    def test_resolver_rejects_missing_or_invalid_classification_before_returning_label(self):
        registry = copy.deepcopy(self.registry)
        registry["models"] = [next(r for r in registry["models"] if names.registry_key(r) == "01:0013:00")]
        payload = b"synthetic appearance-only source"
        registry["models"][0].update(source_bytes=len(payload), model_sha1=hashlib.sha1(payload).hexdigest(),
                                      model_sha256=hashlib.sha256(payload).hexdigest())
        confidence = synthetic_confidence(registry)
        for mutate in (lambda c: c.update(models=[]),
                       lambda c: c["models"].append(copy.deepcopy(c["models"][0])),
                       lambda c: c["models"][0].update(classification="confirmed"),
                       lambda c: c["models"][0].update(model_sha256="0" * 64),
                       lambda c: c["models"][0].pop("classification")):
            changed = copy.deepcopy(confidence)
            mutate(changed)
            with self.assertRaises(ValueError):
                names.resolve_name(registry, "us", registry["rom_sha1"], (1, 13, 0), payload,
                                   confidence=changed)
        with tempfile.TemporaryDirectory() as directory:
            with patch.object(names, "CONFIDENCE_PATH", Path(directory) / "absent.json"), \
                 self.assertRaises(FileNotFoundError):
                names.resolve_name(registry, "us", registry["rom_sha1"], (1, 13, 0), payload)

    def test_every_registry_field_is_bound_independently_of_source_hashes(self):
        mutations = [lambda r: r.update(name="Different descriptor"),
                     lambda r: r["evidence"].append("docs/other.md"),
                     lambda r: r["limitations"].append("Different caveat"),
                     lambda r: r["consumers"][0].update(role="Different role")]
        for mutate in mutations:
            changed = copy.deepcopy(self.registry)
            mutate(changed["models"][0])
            with self.assertRaisesRegex(ValueError, "source record mismatch"):
                names.validate_confidence(self.confidence, changed)

    def test_synthetic_sources_require_explicit_matching_confidence(self):
        registry = copy.deepcopy(self.registry)
        registry["models"] = [registry["models"][0]]
        payload = b"synthetic source"
        registry["models"][0].update(source_bytes=len(payload), model_sha1=hashlib.sha1(payload).hexdigest(),
                                      model_sha256=hashlib.sha256(payload).hexdigest())
        with self.assertRaisesRegex(ValueError, "confidence source identity mismatch"):
            names.resolve_name(registry, "us", registry["rom_sha1"], (1, 0, 0), payload)
        result = resolve_synthetic_name(registry, "us", registry["rom_sha1"], (1, 0, 0), payload)
        self.assertFalse(result["semantic_identity_confirmed"])
        with self.assertRaisesRegex(ValueError, "confidence source identity mismatch"):
            names.load_confidence(registry)

    def test_cli_reports_source_records_and_confidence_not_verified_names(self):
        report = {"models": [None] * 267, "confidence_counts": EXPECTED_COUNTS,
                  "consumer_count": 47, "model_specific_branch_count": 1}
        stream = io.StringIO()
        with patch.object(names, "audit_registry", return_value=report), \
             patch("sys.argv", ["model_semantic_names.py"]), patch("sys.stdout", stream):
            names.main()
        output = stream.getvalue()
        self.assertIn("Source-verified US model descriptions: 267 records", output)
        self.assertNotIn("Verified US model names", output)
        for classification, count in EXPECTED_COUNTS.items():
            self.assertIn(f"{classification}: {count}", output)
        self.assertIn("qualifiers remain unconfirmed", output)


if __name__ == "__main__":
    unittest.main()
