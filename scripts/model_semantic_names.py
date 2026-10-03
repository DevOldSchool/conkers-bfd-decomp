"""Reviewed model labels keyed by ROM, bank, entry, segment and source bytes.

These descriptive names do not rename linked symbols, define actor types or
establish runtime activation. The fixed registry is reviewed source evidence.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REGISTRY_PATH = ROOT / "config/model-semantic-names.json"
REGISTRY_SHA256 = "6b7140c4854480c1525c6549a5bed853b438e969728e452f76f2470d304f412a"


def load_registry() -> dict:
    raw = REGISTRY_PATH.read_bytes()
    if hashlib.sha256(raw).hexdigest() != REGISTRY_SHA256:
        raise ValueError("reviewed model-name registry changed")
    registry = json.loads(raw)
    keys = [tuple(record[field] for field in ("bank", "entry", "segment"))
            for record in registry["models"]]
    if len(set(keys)) != len(keys):
        raise ValueError("model-name registry contains ambiguous numeric identities")
    return registry


def resolve_name(registry: dict, profile: str, rom_sha1: str,
                 key: tuple[int, int, int], data: bytes) -> dict:
    """Resolve only exact reviewed identities; unrelated models remain unknown."""
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
    return {"status": "reviewed", "name": record["name"],
            "kind": registry["name_kind"],
            "registry_key": f"{key[0]:02x}:{key[1]:04d}:{key[2]:02d}",
            "evidence": list(record["evidence"])}


def verify_consumers(code: bytes, base: int, registry: dict) -> None:
    """Audit full function spans and the separately identified shared branch."""
    for record in registry["models"]:
        for consumer in record["consumers"]:
            start = int(consumer["vram"], 16) - base
            size = consumer["size_bytes"]
            if (start < 0 or start + size > len(code)
                    or hashlib.sha1(code[start:start + size]).hexdigest() != consumer["sha1"]):
                raise ValueError("model-name consumer changed: " + consumer["symbol"])
        branch = record["model_specific_branch"]
        start, end = (int(branch[field], 16) - base for field in ("start", "end"))
        if (start < 0 or end <= start or end > len(code)
                or hashlib.sha1(code[start:end]).hexdigest() != branch["sha1"]):
            raise ValueError("model-name shared branch changed")


def audit_registry(rom: Path | None = None) -> dict:
    """Read the owned ROM only; no captures, exports or generated names are inputs."""
    try:
        from scripts import model_assets as models
    except ModuleNotFoundError:
        import model_assets as models
    registry = load_registry()
    rom_path, _, digest, bundles, _ = models.load_model_bundles("us", rom, 1)
    if digest != registry["rom_sha1"]:
        raise ValueError("model-name registry belongs to a different ROM")
    _, layout = models.resolve_rom("us", rom_path)
    normalized, _ = models.normalize_rom(rom_path.read_bytes())
    if hashlib.sha1(normalized).hexdigest() != digest:
        raise ValueError("ROM changed during model-name audit")
    game = models.parse_game_archive(normalized[layout["game_start"]:layout["game_end"]])
    verify_consumers(game.code, layout["game_vram"], registry)
    sources = {(1, bundle.index, segment.index): segment.data
               for bundle in bundles for segment in bundle.segments}
    names = []
    for record in registry["models"]:
        key = tuple(record[field] for field in ("bank", "entry", "segment"))
        if key not in sources:
            raise ValueError("named model is absent from the ROM")
        names.append(resolve_name(registry, "us", digest, key, sources[key]))
    return {"profile": "us", "rom_sha1": digest, "models": names,
            "consumer_count": sum(len(record["consumers"]) for record in registry["models"])}


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path)
    args = parser.parse_args()
    report = audit_registry(args.rom)
    print("Verified US model names: " + ", ".join(
        f"{record['name']} [{record['registry_key']}]" for record in report["models"]))
    print(f"{report['consumer_count']} full consumer spans and the shared Haybot branch verified")


if __name__ == "__main__":
    main()
