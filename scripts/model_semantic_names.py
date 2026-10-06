"""Source-bound legacy labels with separately reviewed naming confidence.

These descriptive names do not rename linked symbols, define actor types or
establish runtime activation. Source hashes and consumer roles do not confirm
semantic identity. The original registry is preserved; a pinned sidecar records
the confidence correction without inventing identities or human approval.
"""

from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
REGISTRY_PATH = ROOT / "config/model-semantic-names.json"
REGISTRY_SHA256 = "785854978bcab515c90d304caa2f22ef36a512e8d3ae233e4f483c35597fce06"
CONFIDENCE_PATH = ROOT / "config/model-name-confidence.json"
CONFIDENCE_SHA256 = "d5b8317ea18e52aa0f31c9eaf8236fa058be14953aa1e900c163a5f735517fc3"
SUPPORTED_BANKS = (0x01, 0x03, 0x04, 0x09)
NAME_KIND = "reviewed-descriptive-model-label"
CONFIDENCE_STATUSES = {
    "earlier_reviewed_character_label": "prior_character_review",
    "historical_character_label_pending_confirmation": "tentative_historical_character_label",
    "appearance_only_description": "identity_unknown_or_not_applicable",
}
SOURCE_FIELDS = ("source_bytes", "model_sha1", "model_sha256")


def registry_key(record: dict) -> str:
    return f"{record['bank']:02x}:{record['entry']:04d}:{record['segment']:02d}"


def source_record_sha256(record: dict) -> str:
    """Pin every original record field, including label, evidence and caveats."""
    return hashlib.sha256(json.dumps(record, sort_keys=True,
                                     separators=(",", ":"), ensure_ascii=False).encode()).hexdigest()


def _fields(value: object, required: set[str], context: str,
            optional: set[str] = frozenset()) -> None:
    if not isinstance(value, dict) or not required <= value.keys() <= required | optional:
        raise ValueError(f"invalid {context} fields")


def _integer(value: object, context: str, minimum: int = 0,
             maximum: int = 0xFFFFFFFF) -> None:
    if type(value) is not int or not minimum <= value <= maximum:
        raise ValueError(f"{context} requires an integer in {minimum}..{maximum}")


def _text(value: object, context: str) -> None:
    if not isinstance(value, str) or not value.strip() or value != value.strip():
        raise ValueError(f"{context} requires nonempty text without edge whitespace")


def _digest(value: object, width: int, context: str) -> None:
    if not isinstance(value, str) or re.fullmatch(r"[0-9a-f]{%d}" % width, value) is None:
        raise ValueError(f"invalid {context} digest")


def _address(value: object, context: str) -> int:
    if not isinstance(value, str) or re.fullmatch(r"0x[0-9a-fA-F]{1,8}", value) is None:
        raise ValueError(f"invalid {context} address")
    return int(value, 16)


def _unique_json_object(pairs: list[tuple[str, object]]) -> dict:
    result = {}
    for key, value in pairs:
        if key in result:
            raise ValueError("model-name registry contains duplicate JSON keys")
        result[key] = value
    return result


def validate_registry(registry: dict) -> None:
    """Check structure, not provenance; only load_registry authenticates the file."""
    _fields(registry, {"schema_version", "profile", "rom_sha1", "rom_sha256",
                       "rom_size_bytes", "name_kind", "models"}, "registry")
    _integer(registry["schema_version"], "schema version", 2, 2)
    if registry["profile"] != "us" or registry["name_kind"] != NAME_KIND:
        raise ValueError("unsupported model-name profile or kind")
    _integer(registry["rom_size_bytes"], "ROM size", 1)
    _digest(registry["rom_sha1"], 40, "ROM SHA-1")
    _digest(registry["rom_sha256"], 64, "ROM SHA-256")
    if not isinstance(registry["models"], list) or not registry["models"]:
        raise ValueError("model-name registry requires a nonempty model list")
    keys = set()
    shared_consumers = {}
    consumer_addresses = {}
    for record in registry["models"]:
        _fields(record, {"bank", "entry", "segment", "name", "model_sha1",
                         "model_sha256", "source_bytes", "evidence", "consumers",
                         "limitations"}, "model", {"model_specific_branch"})
        for field in ("bank", "entry", "segment"):
            _integer(record[field], "model " + field)
        if record["bank"] not in SUPPORTED_BANKS:
            raise ValueError("unsupported model-name bank")
        key = tuple(record[field] for field in ("bank", "entry", "segment"))
        if key in keys:
            raise ValueError("model-name registry contains ambiguous numeric identities")
        keys.add(key)
        _text(record["name"], "model name")
        _integer(record["source_bytes"], "model source size", 1)
        _digest(record["model_sha1"], 40, "model SHA-1")
        _digest(record["model_sha256"], 64, "model SHA-256")
        if not isinstance(record["evidence"], list) or not record["evidence"]:
            raise ValueError("model evidence requires nonempty relative paths")
        for path in record["evidence"]:
            _text(path, "model evidence path")
            if (any(part in ("", ".", "..") for part in path.split("/"))
                    or any(char in path for char in ("\\", ":", "\0"))):
                raise ValueError("model evidence requires nonempty relative paths")
        if len(set(record["evidence"])) != len(record["evidence"]):
            raise ValueError("duplicate model evidence path")
        if not isinstance(record["limitations"], list) or not record["limitations"]:
            raise ValueError("model requires nonempty limitations")
        for limitation in record["limitations"]:
            _text(limitation, "model limitation")
        if not isinstance(record["consumers"], list) or not record["consumers"]:
            raise ValueError("model requires nonempty consumer spans")
        local_consumers = {}
        for consumer in record["consumers"]:
            _fields(consumer, {"symbol", "vram", "size_bytes", "sha1", "role"}, "consumer")
            symbol = consumer["symbol"]
            if not isinstance(symbol, str) or re.fullmatch(r"[A-Za-z_][A-Za-z_0-9]*", symbol) is None:
                raise ValueError("invalid consumer symbol")
            start = _address(consumer["vram"], "consumer")
            _integer(consumer["size_bytes"], "consumer size", 1)
            if not start or start + consumer["size_bytes"] > 0x100000000:
                raise ValueError("invalid consumer address range")
            _digest(consumer["sha1"], 40, "consumer SHA-1")
            _text(consumer["role"], "consumer role")
            if symbol in local_consumers:
                raise ValueError("duplicate model consumer")
            local_consumers[symbol] = consumer
            # Different descriptions may cite the same full span, but its identity
            # and digest must agree everywhere. Audit that span only once.
            identity = (start, consumer["size_bytes"], consumer["sha1"])
            if symbol in shared_consumers and shared_consumers[symbol] != identity:
                raise ValueError("conflicting shared consumer identity")
            if start in consumer_addresses and consumer_addresses[start] != symbol:
                raise ValueError("ambiguous shared consumer address")
            shared_consumers[symbol] = identity
            consumer_addresses[start] = symbol
        if "model_specific_branch" not in record:
            continue
        branch = record["model_specific_branch"]
        _fields(branch, {"symbol", "start", "end", "sha1", "model_index",
                         "texture_selector_offset", "phase_offset", "descriptor_cycle"},
                "model-specific branch")
        _text(branch["symbol"], "branch symbol")
        if branch["symbol"] not in local_consumers:
            raise ValueError("model-specific branch has no containing consumer")
        _integer(branch["model_index"], "branch model index")
        if branch["model_index"] != record["entry"]:
            raise ValueError("model-specific branch identity disagrees with model")
        start = _address(branch["start"], "branch start")
        end = _address(branch["end"], "branch end")
        consumer = local_consumers[branch["symbol"]]
        outer = int(consumer["vram"], 16)
        if not outer <= start < end <= outer + consumer["size_bytes"]:
            raise ValueError("model-specific branch escapes its containing consumer")
        _digest(branch["sha1"], 40, "branch SHA-1")
        for field in ("texture_selector_offset", "phase_offset"):
            _address(branch[field], "branch " + field)
        cycle = branch["descriptor_cycle"]
        if not isinstance(cycle, list) or not cycle:
            raise ValueError("branch descriptor cycle requires a nonempty list")
        for selector in cycle:
            _integer(selector, "branch descriptor selector", 0, 255)


def load_registry() -> dict:
    raw = REGISTRY_PATH.read_bytes()
    if hashlib.sha256(raw).hexdigest() != REGISTRY_SHA256:
        raise ValueError("reviewed model-name registry changed")
    registry = json.loads(raw, object_pairs_hook=_unique_json_object)
    validate_registry(registry)
    return registry


def validate_confidence(confidence: dict, registry: dict) -> None:
    """Check exact bindings, not file provenance; load_confidence pins the file.

    Explicit in-memory registry/confidence pairs also support synthetic unit
    fixtures. They receive the same structural and cross-record checks, but do
    not replace either production file loader or its immutable byte digest.
    """
    validate_registry(registry)
    _fields(confidence, {"schema_version", "registry_sha256", "profile", "rom_sha1",
                         "rom_sha256", "rom_size_bytes", "models"}, "confidence")
    _integer(confidence["schema_version"], "confidence schema version", 1, 1)
    if confidence["registry_sha256"] != REGISTRY_SHA256:
        raise ValueError("model-name confidence registry digest mismatch")
    for field in ("profile", "rom_sha1", "rom_sha256", "rom_size_bytes"):
        if type(confidence[field]) is not type(registry[field]) or confidence[field] != registry[field]:
            raise ValueError("model-name confidence ROM/profile mismatch")
    if not isinstance(confidence["models"], list) or not confidence["models"]:
        raise ValueError("model-name confidence requires a nonempty classification list")
    records = {registry_key(record): record for record in registry["models"]}
    seen = set()
    for classification in confidence["models"]:
        _fields(classification, {"registry_key", "bank", "entry", "segment",
                                 "source_record_sha256", *SOURCE_FIELDS, "classification"},
                "model confidence")
        for field in ("bank", "entry", "segment"):
            _integer(classification[field], "confidence " + field)
        key = registry_key(classification)
        if classification["registry_key"] != key:
            raise ValueError("model-name confidence numeric key mismatch")
        if key in seen:
            raise ValueError("duplicate model-name confidence classification")
        seen.add(key)
        if key not in records:
            raise ValueError("model-name confidence contains an unlisted registry key")
        if (not isinstance(classification["classification"], str)
                or classification["classification"] not in CONFIDENCE_STATUSES):
            raise ValueError("unsupported model-name confidence classification")
        record = records[key]
        for field in SOURCE_FIELDS:
            if (type(classification[field]) is not type(record[field])
                    or classification[field] != record[field]):
                raise ValueError("model-name confidence source identity mismatch")
        if classification["source_record_sha256"] != source_record_sha256(record):
            raise ValueError("model-name confidence source record mismatch")
    if seen != records.keys():
        raise ValueError("model-name confidence is missing registry classifications")


def load_confidence(registry: dict) -> dict:
    raw = CONFIDENCE_PATH.read_bytes()
    if hashlib.sha256(raw).hexdigest() != CONFIDENCE_SHA256:
        raise ValueError("reviewed model-name confidence sidecar changed")
    confidence = json.loads(raw, object_pairs_hook=_unique_json_object)
    validate_confidence(confidence, registry)
    return confidence


def resolve_name(registry: dict, profile: str, rom_sha1: str,
                 key: tuple[int, int, int], data: bytes, *,
                 confidence: dict | None = None) -> dict:
    """Resolve a source-bound description, never inferred human confirmation.

    `name` remains a legacy descriptive-label alias of `descriptor`; it is not a
    confirmed semantic identity. Unknown-model responses remain unchanged.
    """
    unknown = {"status": "unknown", "name": None}
    if len(key) != 3 or any(type(value) is not int for value in key):
        raise ValueError("model-name key requires integer bank, entry and segment")
    if (profile, rom_sha1) != (registry["profile"], registry["rom_sha1"]):
        return unknown
    matches = [record for record in registry["models"]
               if tuple(record[field] for field in ("bank", "entry", "segment")) == key]
    if not matches:
        return unknown
    if len(matches) != 1:
        raise ValueError("model-name registry contains ambiguous numeric identities")
    record = matches[0]
    if (len(data) != record["source_bytes"]
            or hashlib.sha1(data).hexdigest() != record["model_sha1"]
            or hashlib.sha256(data).hexdigest() != record["model_sha256"]):
        raise ValueError("named model source identity changed")
    if confidence is None:
        confidence = load_confidence(registry)
    else:
        validate_confidence(confidence, registry)
    classification = next(item["classification"] for item in confidence["models"]
                          if item["registry_key"] == registry_key(record))
    return {"status": classification, "name": record["name"],
            "descriptor": record["name"], "kind": "legacy-descriptive-model-label",
            "semantic_identity_status": CONFIDENCE_STATUSES[classification],
            "semantic_identity_confirmed": False,
            "human_confirmation_status": "not_individually_audited",
            "qualifier_confirmation_status": "not_individually_audited",
            "registry_key": registry_key(record),
            "evidence": list(record["evidence"])}


def verify_consumers(code: bytes, base: int, registry: dict) -> int:
    """Audit unique full spans and optional branches, not exclusive ownership."""
    validate_registry(registry)
    verified = set()
    for record in registry["models"]:
        for consumer in record["consumers"]:
            if consumer["symbol"] in verified:
                continue
            start = int(consumer["vram"], 16) - base
            size = consumer["size_bytes"]
            if (start < 0 or start + size > len(code)
                    or hashlib.sha1(code[start:start + size]).hexdigest() != consumer["sha1"]):
                raise ValueError("model-name consumer changed: " + consumer["symbol"])
            verified.add(consumer["symbol"])
        branch = record.get("model_specific_branch")
        if branch is None:
            continue
        start, end = (int(branch[field], 16) - base for field in ("start", "end"))
        if (start < 0 or end <= start or end > len(code)
                or hashlib.sha1(code[start:end]).hexdigest() != branch["sha1"]):
            raise ValueError("model-name branch changed: " + record["name"])
    return len(verified)


def audit_registry(rom: Path | None = None) -> dict:
    """Read the owned ROM only; no captures, exports or generated names are inputs."""
    try:
        from scripts import model_assets as models
    except ModuleNotFoundError:
        import model_assets as models
    registry = load_registry()
    rom_path, layout = models.resolve_rom("us", rom)
    normalized, _ = models.normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if (digest != registry["rom_sha1"] or len(normalized) != registry["rom_size_bytes"]
            or hashlib.sha256(normalized).hexdigest() != registry["rom_sha256"]):
        raise ValueError("model-name registry belongs to a different ROM")
    confidence = load_confidence(registry)
    game = models.parse_game_archive(normalized[layout["game_start"]:layout["game_end"]])
    consumer_count = verify_consumers(game.code, layout["game_vram"], registry)
    sources = {}
    banks = sorted({record["bank"] for record in registry["models"]})
    for bank in banks:
        _, _, bank_digest, bundles, _ = models.load_model_bundles("us", rom_path, bank)
        if bank_digest != digest:
            raise ValueError("ROM changed during model-name audit")
        for bundle in bundles:
            for segment in bundle.segments:
                key = (bank, bundle.index, segment.index)
                if key in sources:
                    raise ValueError("ambiguous extracted model identity")
                sources[key] = segment.data
    names = []
    for record in registry["models"]:
        key = tuple(record[field] for field in ("bank", "entry", "segment"))
        if key not in sources:
            raise ValueError("named model is absent from the ROM")
        names.append(resolve_name(registry, "us", digest, key, sources[key], confidence=confidence))
    return {"profile": "us", "rom_sha1": digest, "rom_sha256": registry["rom_sha256"],
            "rom_size_bytes": len(normalized), "banks": banks, "models": names,
            "registry_sha256": REGISTRY_SHA256, "confidence_sha256": CONFIDENCE_SHA256,
            "confidence_counts": dict(sorted(Counter(item["status"] for item in names).items())),
            "confirmed_semantic_identity_model_count": 0,
            "consumer_count": consumer_count,
            "consumer_reference_count": sum(len(record["consumers"]) for record in registry["models"]),
            "model_specific_branch_count": sum("model_specific_branch" in record for record in registry["models"])}


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path)
    args = parser.parse_args()
    report = audit_registry(args.rom)
    print(f"Source-verified US model descriptions: {len(report['models'])} records")
    for status, count in report["confidence_counts"].items():
        print(f"  {status}: {count}")
    print("Human confirmation was not individually audited; qualifiers remain unconfirmed.")
    print(f"{report['consumer_count']} unique full consumer spans and "
          f"{report['model_specific_branch_count']} model-specific branches verified")


if __name__ == "__main__":
    main()
