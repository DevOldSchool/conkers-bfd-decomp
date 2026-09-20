"""Shared local attempt history. Inventory and finish remain authoritative."""
from __future__ import annotations

import json
from pathlib import Path

REUSABLE = {"deferred", "skipped", "restored", "preserved", "ready"}


def path(root: Path) -> Path:
    return root / "build/us/automate/attempt-history.json"


def read_report(location: Path) -> dict:
    payload = json.loads(location.read_text(encoding="utf-8"))
    if (not isinstance(payload, dict) or payload.get("schema_version") not in (1, 2, 3)
            or payload.get("profile") != "us"
            or not isinstance(payload.get("functions"), list)):
        raise ValueError(f"invalid attempt report: {location}")
    if (any(not isinstance(entry, dict) or not isinstance(entry.get("symbol"), str)
            for entry in payload["functions"])
            or not isinstance(payload.get("pending_batch", []), list)
            or any(not isinstance(symbol, str) for symbol in payload.get("pending_batch", []))):
        raise ValueError(f"invalid attempt entries or pending batch: {location}")
    return payload


def merge(previous: dict, current: dict) -> dict:
    entries = {entry["symbol"]: entry for entry in previous.get("functions", [])}
    for entry in current.get("functions", []):
        if entry.get("outcome") in REUSABLE | {"matched"}:
            entries[entry["symbol"]] = entry
    pending = set(previous.get("pending_batch", []))
    pending.update(current.get("pending_batch", []))
    if current.get("batch_verified"):
        pending.difference_update(current.get("verified_batch", []))
        # Older reports did not include verified_batch.
        pending.difference_update(entry["symbol"] for entry in current.get("functions", [])
                                  if entry.get("outcome") == "matched")
    return {"schema_version": 3, "profile": "us", "mode": "execute",
            "full_scan": True, "generated_at": current.get("generated_at", ""),
            "functions": list(entries.values()), "pending_batch": sorted(pending)}


def load(root: Path) -> dict:
    location = path(root)
    if location.is_file():
        return read_report(location)
    # Import old reports once; analysis is not a failed compilation attempt.
    directory = location.parent
    reports = []
    for candidate in sorted(directory.glob("*-report.json")) + [directory / "report.json"]:
        if not candidate.is_file():
            continue
        report = read_report(candidate)
        if report.get("mode", "execute") == "execute":
            reports.append(report)
    result = {}
    for report in sorted(reports, key=lambda item: item.get("generated_at", "")):
        result = merge(result, report)
    return result


def save(root: Path, report: dict) -> None:
    if report.get("mode", "execute") != "execute":
        return
    result = merge(load(root), report)
    location = path(root)
    location.parent.mkdir(parents=True, exist_ok=True)
    temporary = location.with_suffix(".json.tmp")
    temporary.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    temporary.replace(location)
