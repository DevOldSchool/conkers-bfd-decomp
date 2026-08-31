#!/usr/bin/env python3
"""Correlate owned beta game overlays with retail US without changing progress."""

from __future__ import annotations

import argparse
import bisect
import csv
import hashlib
import json
import re
import shutil
import struct
import subprocess
import tempfile
from collections import Counter
from dataclasses import dataclass
from pathlib import Path
from typing import Any

try:
    from scripts.rzip_archive import normalize_rom, parse_game_archive
    from scripts.rzip_extract import load_layout
except ModuleNotFoundError:
    from rzip_archive import normalize_rom, parse_game_archive  # type: ignore[no-redef]
    from rzip_extract import load_layout  # type: ignore[no-redef]


ROOT = Path(__file__).resolve().parent.parent
OUTPUT = ROOT / "build" / "beta-index"
ACTIVE_PROFILE = "us"
EVIDENCE_PROFILES = ("debug", "ects")
INDEX_VERSION = 2
SOURCE_PATH_PATTERN = re.compile(rb"\.\./[A-Za-z0-9_./-]+\.c")
FUNCTION_INDEX_OPTIONS = (
    "--compiler",
    "IDO",
    "--no-libultra-syms",
    "--no-hardware-regs",
    "--no-ique-syms",
    "--quiet",
)


@dataclass(frozen=True)
class FunctionRecord:
    offset: int
    address: int
    symbol: str
    length: int
    fingerprint: str


@dataclass(frozen=True)
class GameImage:
    profile: str
    rom_path: Path
    normalized_rom: bytes
    normalized_sha1: str
    code: bytes
    data: bytes
    code_vram: int
    data_vram: int


def display_path(path: Path) -> str:
    try:
        return str(path.relative_to(ROOT))
    except ValueError:
        return str(path)


def load_game_image(profile: str) -> GameImage:
    layout = load_layout(profile)
    raw_path = Path(layout["default_rom"])
    rom_path = raw_path if raw_path.is_absolute() else ROOT / raw_path
    if not rom_path.is_file():
        raise ValueError(f"{profile} evidence ROM does not exist: {display_path(rom_path)}")
    normalized, _ = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(
            f"{profile} normalized ROM SHA-1 mismatch: got {digest}; expected one of "
            + ", ".join(layout["normalized_sha1"])
        )

    start = layout["game_start"]
    end = layout["game_end"]
    if not 0 <= start < end <= len(normalized):
        raise ValueError(f"{profile} game range is outside the ROM")
    if layout["game_format"] == "rzip":
        archive = parse_game_archive(normalized[start:end])
        code = archive.code
        data = archive.data
    elif layout["game_format"] == "raw":
        code_end = layout["game_code_end"]
        if not start < code_end <= end:
            raise ValueError(f"{profile} raw game code boundary is outside the game range")
        code = normalized[start:code_end]
        data = normalized[code_end:end]
    else:
        raise ValueError(f"{profile} uses unsupported game format {layout['game_format']}")

    return GameImage(
        profile=profile,
        rom_path=rom_path,
        normalized_rom=normalized,
        normalized_sha1=digest,
        code=code,
        data=data,
        code_vram=layout["game_vram"],
        data_vram=layout["game_data_vram"],
    )


def parse_function_csv(path: Path) -> list[FunctionRecord]:
    records: list[FunctionRecord] = []
    with path.open(newline="", encoding="utf-8") as source:
        for row in csv.DictReader(source):
            records.append(
                FunctionRecord(
                    offset=int(row["vrom"], 0),
                    address=int(row["address"], 0),
                    symbol=row["name"],
                    length=int(row["length"], 0),
                    fingerprint=row["hash of top bits of words"],
                )
            )
    if not records:
        raise ValueError(f"spimdisasm did not recover functions from {display_path(path)}")
    return records


def function_index_identity(image: GameImage, code_sha1: str) -> dict[str, Any]:
    lock = json.loads((ROOT / "toolchain" / "tools.lock.json").read_text(encoding="utf-8"))
    return {
        "index_version": INDEX_VERSION,
        "code_sha1": code_sha1,
        "code_vram": f"0x{image.code_vram:X}",
        "container_image": lock["container_image"],
        "spimdisasm": lock["tools"]["spimdisasm"],
        "options": list(FUNCTION_INDEX_OPTIONS),
    }


def prepare_function_index(image: GameImage, refresh: bool) -> tuple[list[FunctionRecord], str]:
    profile_dir = OUTPUT / image.profile
    profile_dir.mkdir(parents=True, exist_ok=True)
    code_path = profile_dir / "game.code.bin"
    csv_path = profile_dir / "functions.csv"
    metadata_path = profile_dir / "metadata.json"
    code_sha1 = hashlib.sha1(image.code).hexdigest()
    identity = function_index_identity(image, code_sha1)

    reusable = False
    if not refresh and csv_path.is_file() and metadata_path.is_file():
        metadata = json.loads(metadata_path.read_text(encoding="utf-8"))
        reusable = all(metadata.get(key) == value for key, value in identity.items())
    if reusable:
        return parse_function_csv(csv_path), code_sha1

    code_path.write_bytes(image.code)
    if shutil.which("spimdisasm") is None:
        raise ValueError("spimdisasm is required; run ./conker beta-index through the toolchain")
    with tempfile.TemporaryDirectory(prefix="assembly-", dir=profile_dir) as temporary:
        subprocess.run(
            [
                "spimdisasm",
                "singleFileDisasm",
                str(code_path),
                str(Path(temporary) / "game.s"),
                "--vram",
                f"0x{image.code_vram:X}",
                "--function-info",
                str(csv_path),
                *FUNCTION_INDEX_OPTIONS,
            ],
            check=True,
        )
    metadata_path.write_text(
        json.dumps(
            {
                **identity,
                "profile": image.profile,
                "normalized_rom_sha1": image.normalized_sha1,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    return parse_function_csv(csv_path), code_sha1


def align_functions(
    active: list[FunctionRecord], evidence: list[FunctionRecord]
) -> tuple[list[dict[str, Any]], dict[str, int]]:
    active_hashes = [record.fingerprint for record in active]
    evidence_hashes = [record.fingerprint for record in evidence]
    active_counts = Counter(active_hashes)
    evidence_counts = Counter(evidence_hashes)
    evidence_positions = {
        value: index for index, value in enumerate(evidence_hashes) if evidence_counts[value] == 1
    }
    unique_pairs = [
        (index, evidence_positions[value])
        for index, value in enumerate(active_hashes)
        if active_counts[value] == 1 and value in evidence_positions
    ]
    ordered_anchors = longest_increasing_pairs(unique_pairs)

    mapped_pairs: dict[tuple[int, int], tuple[str, int]] = {}
    covered_anchors: set[tuple[int, int]] = set()
    anchor_set = set(ordered_anchors)
    for active_index, evidence_index in ordered_anchors:
        if (active_index, evidence_index) in covered_anchors:
            continue
        left = 0
        while (
            active_index - left - 1 >= 0
            and evidence_index - left - 1 >= 0
            and active_hashes[active_index - left - 1]
            == evidence_hashes[evidence_index - left - 1]
        ):
            left += 1
        right = 0
        while (
            active_index + right + 1 < len(active)
            and evidence_index + right + 1 < len(evidence)
            and active_hashes[active_index + right + 1]
            == evidence_hashes[evidence_index + right + 1]
        ):
            right += 1
        sequence_length = left + right + 1
        for relative in range(-left, right + 1):
            pair = (active_index + relative, evidence_index + relative)
            fingerprint = active_hashes[pair[0]]
            unique = active_counts[fingerprint] == 1 and evidence_counts[fingerprint] == 1
            confidence = "strong" if unique and sequence_length >= 2 else "candidate"
            previous = mapped_pairs.get(pair)
            if previous is None or (previous[0] == "candidate" and confidence == "strong"):
                mapped_pairs[pair] = (confidence, sequence_length)
            if pair in anchor_set:
                covered_anchors.add(pair)

    selected_pairs: dict[tuple[int, int], tuple[str, int]] = {}
    used_active: set[int] = set()
    used_evidence: set[int] = set()
    ranked_pairs = sorted(
        mapped_pairs.items(),
        key=lambda item: (
            item[1][0] != "strong",
            -item[1][1],
            item[0][0],
            item[0][1],
        ),
    )
    for (active_index, evidence_index), mapping_evidence in ranked_pairs:
        if active_index in used_active or evidence_index in used_evidence:
            continue
        selected_pairs[(active_index, evidence_index)] = mapping_evidence
        used_active.add(active_index)
        used_evidence.add(evidence_index)

    mappings: list[dict[str, Any]] = []
    for (active_index, evidence_index), (confidence, sequence_length) in sorted(selected_pairs.items()):
        active_record = active[active_index]
        evidence_record = evidence[evidence_index]
        mappings.append(
            {
                "us_symbol": active_record.symbol,
                "us_offset": f"0x{active_record.offset:X}",
                "evidence_symbol": evidence_record.symbol,
                "evidence_offset": f"0x{evidence_record.offset:X}",
                "length": active_record.length,
                "fingerprint": active_record.fingerprint,
                "confidence": confidence,
                "matching_sequence_length": sequence_length,
            }
        )
    common_hashes = set(active_counts) & set(evidence_counts)
    summary = {
        "strong": sum(mapping["confidence"] == "strong" for mapping in mappings),
        "candidate": sum(mapping["confidence"] == "candidate" for mapping in mappings),
        "ordered_exact": len(mappings),
        "common_fingerprints": len(common_hashes),
        "ambiguous_fingerprints": sum(
            active_counts[value] != 1 or evidence_counts[value] != 1 for value in common_hashes
        ),
    }
    return mappings, summary


def longest_increasing_pairs(pairs: list[tuple[int, int]]) -> list[tuple[int, int]]:
    """Return the order-preserving unique anchors using patience sorting."""

    if not pairs:
        return []
    tails: list[int] = []
    tail_pair_indexes: list[int] = []
    previous = [-1] * len(pairs)
    for pair_index, (_, evidence_index) in enumerate(pairs):
        position = bisect.bisect_left(tails, evidence_index)
        if position == len(tails):
            tails.append(evidence_index)
            tail_pair_indexes.append(pair_index)
        else:
            tails[position] = evidence_index
            tail_pair_indexes[position] = pair_index
        if position:
            previous[pair_index] = tail_pair_indexes[position - 1]

    result: list[tuple[int, int]] = []
    pair_index = tail_pair_indexes[-1]
    while pair_index >= 0:
        result.append(pairs[pair_index])
        pair_index = previous[pair_index]
    return list(reversed(result))


def code_references(code: bytes, address: int) -> list[int]:
    """Find conventional LUI plus ADDIU/ORI constructions of one address."""

    if len(code) % 4:
        code = code[: len(code) - len(code) % 4]
    words = struct.unpack(f">{len(code) // 4}I", code)
    addiu_high = ((address + 0x8000) >> 16) & 0xFFFF
    ori_high = (address >> 16) & 0xFFFF
    low = address & 0xFFFF
    references: list[int] = []
    for index, word in enumerate(words):
        if word >> 26 != 0x0F or word & 0xFFFF not in (addiu_high, ori_high):
            continue
        register = word >> 16 & 0x1F
        for following in range(index + 1, min(index + 25, len(words))):
            candidate = words[following]
            opcode = candidate >> 26
            source_register = candidate >> 21 & 0x1F
            expected_high = addiu_high if opcode == 0x09 else ori_high
            if (
                opcode in (0x09, 0x0D)
                and word & 0xFFFF == expected_high
                and source_register == register
                and candidate & 0xFFFF == low
            ):
                references.append(index * 4)
                break
    return references


def containing_function(
    functions: list[FunctionRecord], starts: list[int], offset: int
) -> FunctionRecord | None:
    index = bisect.bisect_right(starts, offset) - 1
    if index < 0:
        return None
    function = functions[index]
    return function if offset < function.offset + function.length else None


def find_source_paths(image: GameImage, functions: list[FunctionRecord]) -> list[dict[str, Any]]:
    grouped: dict[str, dict[str, Any]] = {}
    starts = [function.offset for function in functions]

    def record(path: str, scope: str, offset: int, runtime_address: int | None) -> None:
        item = grouped.setdefault(path, {"path": path, "occurrences": [], "function_anchors": []})
        occurrence: dict[str, Any] = {"scope": scope, "offset": f"0x{offset:X}"}
        if runtime_address is not None:
            occurrence["runtime_address"] = f"0x{runtime_address:X}"
        item["occurrences"].append(occurrence)
        if runtime_address is None:
            return
        for reference in code_references(image.code, runtime_address):
            function = containing_function(functions, starts, reference)
            if function is not None:
                anchor = {
                    "symbol": function.symbol,
                    "function_offset": f"0x{function.offset:X}",
                    "reference_offset": f"0x{reference:X}",
                }
                if anchor not in item["function_anchors"]:
                    item["function_anchors"].append(anchor)

    data_spans: list[tuple[int, int]] = []
    for match in SOURCE_PATH_PATTERN.finditer(image.data):
        path = match.group().decode("ascii")
        record(path, "game_data", match.start(), image.data_vram + match.start())
        data_spans.append((match.start(), match.end()))

    for match in SOURCE_PATH_PATTERN.finditer(image.normalized_rom):
        path = match.group().decode("ascii")
        if any(image.data[start:end] == match.group() for start, end in data_spans):
            continue
        record(path, "rom", match.start(), None)
    return sorted(grouped.values(), key=lambda item: item["path"].lower())


def source_leads(
    paths: list[dict[str, Any]], mappings: list[dict[str, Any]]
) -> list[dict[str, Any]]:
    by_evidence = {
        mapping["evidence_symbol"]: mapping
        for mapping in mappings
        if mapping["confidence"] == "strong"
    }
    leads: list[dict[str, Any]] = []
    for item in paths:
        anchors = []
        seen: set[tuple[str, str]] = set()
        for anchor in item["function_anchors"]:
            mapping = by_evidence.get(anchor["symbol"])
            key = (anchor["symbol"], mapping["us_symbol"]) if mapping is not None else None
            if mapping is not None and key not in seen:
                anchors.append(
                    {
                        "evidence_symbol": anchor["symbol"],
                        "us_symbol": mapping["us_symbol"],
                        "confidence": mapping["confidence"],
                    }
                )
                seen.add(key)
        leads.append(
            {
                "path": item["path"],
                "us_function_candidates": anchors,
                "boundary_status": "unreviewed",
            }
        )
    return leads


def direct_source_leads(paths: list[dict[str, Any]]) -> list[dict[str, Any]]:
    leads: list[dict[str, Any]] = []
    for item in paths:
        symbols = sorted({anchor["symbol"] for anchor in item["function_anchors"]})
        leads.append(
            {
                "path": item["path"],
                "us_function_candidates": [
                    {"us_symbol": symbol, "confidence": "direct"} for symbol in symbols
                ],
                "boundary_status": "unreviewed",
            }
        )
    return leads


def build_report(refresh: bool) -> dict[str, Any]:
    images = {profile: load_game_image(profile) for profile in (ACTIVE_PROFILE, *EVIDENCE_PROFILES)}
    functions: dict[str, list[FunctionRecord]] = {}
    code_hashes: dict[str, str] = {}
    for profile, image in images.items():
        functions[profile], code_hashes[profile] = prepare_function_index(image, refresh)

    comparisons: dict[str, Any] = {}
    active_paths = find_source_paths(images[ACTIVE_PROFILE], functions[ACTIVE_PROFILE])
    paths: dict[str, Any] = {ACTIVE_PROFILE: active_paths}
    leads: dict[str, Any] = {ACTIVE_PROFILE: direct_source_leads(active_paths)}
    for profile in EVIDENCE_PROFILES:
        mappings, summary = align_functions(functions[ACTIVE_PROFILE], functions[profile])
        profile_paths = find_source_paths(images[profile], functions[profile])
        comparisons[profile] = {"summary": summary, "mappings": mappings}
        paths[profile] = profile_paths
        leads[profile] = source_leads(profile_paths, mappings)

    return {
        "schema_version": 1,
        "purpose": "non-gating cross-version evidence",
        "active_profile": ACTIVE_PROFILE,
        "profiles": {
            profile: {
                "rom": display_path(image.rom_path),
                "normalized_sha1": image.normalized_sha1,
                "game_code_sha1": code_hashes[profile],
                "function_count": len(functions[profile]),
            }
            for profile, image in images.items()
        },
        "comparisons": comparisons,
        "source_paths": paths,
        "source_leads": leads,
        "safety": {
            "updates_progress": False,
            "proves_function_match": False,
            "proves_source_unit_boundary": False,
        },
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--refresh", action="store_true", help="rebuild cached function indexes")
    args = parser.parse_args()
    try:
        OUTPUT.mkdir(parents=True, exist_ok=True)
        report = build_report(args.refresh)
        report_path = OUTPUT / "report.json"
        report_path.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    except (OSError, ValueError, json.JSONDecodeError, subprocess.CalledProcessError) as error:
        print(f"error: {error}")
        return 1

    print("Beta evidence index (non-gating; progress files were not changed)")
    for profile in EVIDENCE_PROFILES:
        comparison = report["comparisons"][profile]["summary"]
        profile_paths = report["source_paths"][profile]
        print(
            f"{profile}: strong={comparison['strong']}, candidate={comparison['candidate']}, "
            f"source paths={len(profile_paths)}"
        )
    print(f"Report: {display_path(report_path)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
