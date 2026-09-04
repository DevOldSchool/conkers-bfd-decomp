#!/usr/bin/env python3
"""Correlate Conker asset manifests by decoded content without retaining payloads."""

from __future__ import annotations

import argparse
import json
import tempfile
from collections import defaultdict
from pathlib import Path
from typing import Any, Iterable

try:
    from scripts.rzip_extract import ROOT, display_path, extract, load_layout
except ModuleNotFoundError:
    from rzip_extract import (  # type: ignore[no-redef]
        ROOT,
        display_path,
        extract,
        load_layout,
    )


PROFILE_CHOICES = ("us", "debug", "ects")


def asset_entries(manifest: dict[str, Any]) -> list[dict[str, Any]]:
    assets = manifest["assets"]
    entries: list[dict[str, Any]] = []

    flat = assets.get("flat")
    if flat is not None:
        for record in flat["files"]:
            entries.append(
                {
                    "locator": f"flat:{int(record['index']):04d}",
                    "collection": "flat",
                    "decoded_size": int(record["decoded_size"]),
                    "decoded_sha1": record["decoded_sha1"],
                }
            )

    for bank in assets["banks"]:
        bank_index = int(bank["index"])
        for record in bank["entries"]:
            entries.append(
                {
                    "locator": f"bank-{bank_index:02X}:{int(record['index']):04d}",
                    "collection": "indexed",
                    "decoded_size": int(record["decoded_size"]),
                    "decoded_sha1": record["decoded_sha1"],
                }
            )
    return entries


def grouped_locations(
    entries: Iterable[dict[str, Any]],
) -> dict[str, list[dict[str, Any]]]:
    grouped: dict[str, list[dict[str, Any]]] = defaultdict(list)
    for entry in entries:
        grouped[entry["decoded_sha1"]].append(
            {
                "locator": entry["locator"],
                "collection": entry["collection"],
                "decoded_size": entry["decoded_size"],
            }
        )
    return {
        digest: sorted(locations, key=lambda location: location["locator"])
        for digest, locations in grouped.items()
    }


def correlate_manifests(
    base_manifest: dict[str, Any], comparison_manifest: dict[str, Any]
) -> dict[str, Any]:
    base_profile = base_manifest["profile"]
    comparison_profile = comparison_manifest["profile"]
    base_entries = asset_entries(base_manifest)
    comparison_entries = asset_entries(comparison_manifest)
    base_groups = grouped_locations(base_entries)
    comparison_groups = grouped_locations(comparison_entries)
    shared_hashes = sorted(set(base_groups) & set(comparison_groups))

    base_by_locator = {
        entry["locator"]: entry["decoded_sha1"] for entry in base_entries
    }
    comparison_by_locator = {
        entry["locator"]: entry["decoded_sha1"] for entry in comparison_entries
    }
    exact_locators = sorted(
        locator
        for locator in set(base_by_locator) & set(comparison_by_locator)
        if base_by_locator[locator] == comparison_by_locator[locator]
    )

    shared_records: list[dict[str, Any]] = []
    relocated_hash_count = 0
    duplicate_hash_count = 0
    for digest in shared_hashes:
        base_locations = base_groups[digest]
        comparison_locations = comparison_groups[digest]
        base_locator_set = {location["locator"] for location in base_locations}
        comparison_locator_set = {
            location["locator"] for location in comparison_locations
        }
        shared_locators = sorted(base_locator_set & comparison_locator_set)
        if not shared_locators:
            relocated_hash_count += 1
        if len(base_locations) > 1 or len(comparison_locations) > 1:
            duplicate_hash_count += 1
        shared_records.append(
            {
                "decoded_sha1": digest,
                base_profile: base_locations,
                comparison_profile: comparison_locations,
                "same_locators": shared_locators,
            }
        )

    return {
        "base_profile": base_profile,
        "comparison_profile": comparison_profile,
        "base_file_count": len(base_entries),
        "comparison_file_count": len(comparison_entries),
        "base_unique_hash_count": len(base_groups),
        "comparison_unique_hash_count": len(comparison_groups),
        "shared_unique_hash_count": len(shared_hashes),
        "base_occurrences_with_shared_hash": sum(
            len(base_groups[digest]) for digest in shared_hashes
        ),
        "comparison_occurrences_with_shared_hash": sum(
            len(comparison_groups[digest]) for digest in shared_hashes
        ),
        "exact_locator_match_count": len(exact_locators),
        "relocated_hash_count": relocated_hash_count,
        "duplicate_shared_hash_count": duplicate_hash_count,
        "exact_locators": exact_locators,
        "shared_assets": shared_records,
    }


def scan_profile(profile: str, temporary_root: Path) -> dict[str, Any]:
    layout = load_layout(profile)
    rom_path = ROOT / layout["default_rom"]
    if not rom_path.is_file():
        raise ValueError(f"ROM does not exist: {rom_path.relative_to(ROOT)}")
    output = temporary_root / profile
    output.mkdir()
    return extract(
        profile,
        rom_path,
        output,
        keep_rzip=False,
        manifest_only=True,
    )


def build_report(base: str, comparisons: list[str]) -> dict[str, Any]:
    profiles = [base, *comparisons]
    if len(set(profiles)) != len(profiles):
        raise ValueError("asset correlation profiles must be unique")

    with tempfile.TemporaryDirectory(prefix="conker-asset-correlation-") as temporary:
        temporary_root = Path(temporary)
        manifests = {
            profile: scan_profile(profile, temporary_root) for profile in profiles
        }

    return {
        "schema_version": 1,
        "base_profile": base,
        "profiles": {
            profile: {
                "source_rom": manifest["source_rom"],
                "normalized_sha1": manifest["normalized_sha1"],
                "file_count": len(asset_entries(manifest)),
            }
            for profile, manifest in manifests.items()
        },
        "comparisons": [
            correlate_manifests(manifests[base], manifests[profile])
            for profile in comparisons
        ],
    }


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--base", choices=PROFILE_CHOICES, default="us")
    parser.add_argument(
        "--compare",
        action="append",
        choices=PROFILE_CHOICES,
        help="comparison profile; repeat to compare more than one",
    )
    parser.add_argument("--output", type=Path)
    parser.add_argument("--force", action="store_true")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    comparisons = args.compare or [
        profile for profile in PROFILE_CHOICES if profile != args.base
    ]
    output = args.output or (ROOT / "build" / "assets" / "correlation.json")
    if not output.is_absolute():
        output = ROOT / output

    try:
        if output.exists() and not args.force:
            raise ValueError(
                f"output already exists: {display_path(output)}; pass --force to replace it"
            )
        report = build_report(args.base, comparisons)
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    except (KeyError, OSError, TypeError, ValueError, json.JSONDecodeError) as error:
        print(f"error: {error}")
        return 1

    print(f"Asset correlation report: {display_path(output)}")
    for comparison in report["comparisons"]:
        print(
            f"{comparison['base_profile']} vs {comparison['comparison_profile']}: "
            f"shared unique={comparison['shared_unique_hash_count']}, "
            f"same locator={comparison['exact_locator_match_count']}, "
            f"relocated={comparison['relocated_hash_count']}"
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
