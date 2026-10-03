"""Synthetic inputs shared by the naming contract tests; never production data."""

import copy
import hashlib

from scripts import model_semantic_names as names

RESULT_FIELDS = {"status", "name", "descriptor", "kind", "registry_key", "evidence",
                 "semantic_identity_status", "semantic_identity_confirmed",
                 "human_confirmation_status", "qualifier_confirmation_status"}
EXPECTED_COUNTS = {"earlier_reviewed_character_label": 17,
                   "historical_character_label_pending_confirmation": 74,
                   "appearance_only_description": 176}


def synthetic_confidence(registry, *, classifications=None):
    """Rebind only test fixtures; production loaders never call this helper.

    Source bytes are deliberately synthetic in existing resolver tests. Copy
    the pinned classification at the same numeric key, unless a test explicitly
    supplies a classification for an invented fixture key. Recompute every
    binding so tests exercise the real cross-record checks, not a bypass flag.
    """
    original = names.load_confidence(names.load_registry())
    by_key = {r["registry_key"]: r["classification"] for r in original["models"]}
    by_key.update(classifications or {})
    original.update({field: registry[field] for field in
                     ("profile", "rom_sha1", "rom_sha256", "rom_size_bytes")})
    original["models"] = [{
        "registry_key": names.registry_key(record),
        **{field: record[field] for field in ("bank", "entry", "segment", *names.SOURCE_FIELDS)},
        "source_record_sha256": names.source_record_sha256(record),
        "classification": by_key[names.registry_key(record)],
    } for record in registry["models"]]
    return original


def resolve_synthetic_name(registry, profile, rom_sha1, key, data):
    return names.resolve_name(registry, profile, rom_sha1, key, data,
                              confidence=synthetic_confidence(registry))


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
