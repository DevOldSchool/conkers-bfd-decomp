#!/usr/bin/env python3
"""Validate local ROM setup and generate progress for the active US target."""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import subprocess
import sys
from collections import Counter
from pathlib import Path
from typing import Any, NamedTuple

ROOT = Path(__file__).resolve().parent.parent
ROMS_FILE = ROOT / "config" / "roms.json"
OVERLAYS_FILE = ROOT / "config" / "overlays.json"
FUNCTIONS_FILE = ROOT / "progress" / "functions.json"
SOURCE_UNITS_FILE = ROOT / "progress" / "source_units.json"
SUMMARY_FILE = ROOT / "progress" / "summary.json"
BADGE_FILES = {
    "us": ROOT / "progress" / "badge-us.json",
    "eu": ROOT / "progress" / "badge-eu.json",
}
DOCUMENT_FILE = ROOT / "docs" / "progress.md"
LOCAL_SETUP_FILE = ROOT / ".conker" / "roms.json"
ROM_LINKS = {
    "us": ROOT / "roms" / "baserom.us.z64",
    "eu": ROOT / "roms" / "baserom.eu.z64",
}
TARGET_REGIONS = ("us",)
FUTURE_REGIONS = ("eu",)
KNOWN_REGIONS = TARGET_REGIONS + FUTURE_REGIONS
REGION_NAMES = {"us": "US", "eu": "EU/PAL"}
OVERLAYS = {"main": "Main ROM", "game": "Game overlay"}
STATES = {"raw_asm", "in_progress", "candidate", "matched", "blocked"}
SOURCE_UNIT_STATES = {"raw_asm", "in_progress", "candidate", "complete", "blocked"}
SOURCE_UNIT_INTEGRATIONS = {"raw_asm", "mixed", "c"}
BOUNDARY_EVIDENCE_KINDS = {"linker_map", "object_symbols", "structural_analysis"}
GLABEL_PATTERN = re.compile(r"^glabel\s+([A-Za-z_][A-Za-z0-9_]*)\s*$")
INSTRUCTION_PATTERN = re.compile(
    r"^\s*/\*\s*([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s*\*/\s*([A-Za-z.][A-Za-z0-9._]*)"
)
SUBSEGMENT_PATTERN = re.compile(
    r"^\s*-\s*\[(0x[0-9A-Fa-f]+),\s*(asm|hasm|c|lib)(?:,\s*([^\]]+))?\]\s*$"
)
BATCH_FINGERPRINT_INPUTS = (
    "Makefile",
    "config",
    "include",
    "lib",
    "progress",
    "scripts",
    "src",
    "toolchain",
    "tools",
)
DEFERRED_CANDIDATE_TAG = "CONKER_DEFERRED_CANDIDATE"


class ProjectStateError(RuntimeError):
    """Raised for configuration errors that contributors can correct."""


class AssemblyFunction(NamedTuple):
    """A bounded function recovered from generated raw assembly."""

    symbol: str
    offset: int
    vram: int
    end: int
    word_count: int
    shape: str


def load_json(path: Path) -> dict[str, Any]:
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except FileNotFoundError as error:
        raise ProjectStateError(f"missing required file: {path.relative_to(ROOT)}") from error
    except json.JSONDecodeError as error:
        raise ProjectStateError(f"invalid JSON in {path.relative_to(ROOT)}: {error}") from error


def write_json(path: Path, data: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    content = json.dumps(data, indent=2, sort_keys=True) + "\n"
    path.write_text(content, encoding="utf-8")


def assembly_root(region: str, overlay: str) -> Path:
    """Return the independently generated raw-assembly root for one overlay."""

    if overlay == "main":
        return ROOT / "reference" / region / "asm"
    if overlay == "game":
        return ROOT / "reference" / "game" / region / "asm"
    raise ProjectStateError(f"unknown overlay: {overlay}")


def game_assembly_root(region: str) -> Path:
    return assembly_root(region, "game")


def parse_assembly_functions(region: str, overlay: str) -> list[AssemblyFunction]:
    """Return functions in file-offset order from generated raw assembly."""

    root = assembly_root(region, overlay)
    if not root.is_dir():
        preparation = (
            f"./conker _prepare-reference --profile {region}"
            if overlay == "main"
            else f"./conker game-asm --profile {region}"
        )
        raise ProjectStateError(
            f"missing {root.relative_to(ROOT)}; run {preparation} first"
        )

    discovered: list[tuple[str, int, int, list[str]]] = []
    for path in sorted(root.rglob("*.s")):
        current_symbol: str | None = None
        current_offset: int | None = None
        current_vram: int | None = None
        mnemonics: list[str] = []
        for line in path.read_text(encoding="utf-8").splitlines():
            label = GLABEL_PATTERN.match(line)
            if label:
                if current_symbol is not None and current_offset is not None and current_vram is not None:
                    discovered.append((current_symbol, current_offset, current_vram, mnemonics))
                current_symbol = label.group(1)
                current_offset = None
                current_vram = None
                mnemonics = []
                continue
            instruction = INSTRUCTION_PATTERN.match(line)
            if current_symbol is not None and instruction:
                if current_offset is None:
                    current_offset = int(instruction.group(1), 16)
                    current_vram = int(instruction.group(2), 16)
                mnemonics.append(instruction.group(4))
        if current_symbol is not None and current_offset is not None and current_vram is not None:
            discovered.append((current_symbol, current_offset, current_vram, mnemonics))

    if not discovered:
        raise ProjectStateError(f"no functions found in {root.relative_to(ROOT)}")

    discovered.sort(key=lambda item: item[1])
    functions: list[AssemblyFunction] = []
    for index, (symbol, offset, vram, mnemonics) in enumerate(discovered):
        if index + 1 < len(discovered):
            end = discovered[index + 1][1]
        else:
            end = offset + max(len(mnemonics), 1) * 4
        shape = hashlib.sha1(" ".join(mnemonics).encode("utf-8")).hexdigest()[:10]
        functions.append(
            AssemblyFunction(
                symbol=symbol,
                offset=offset,
                vram=vram,
                end=end,
                word_count=len(mnemonics),
                shape=shape,
            )
        )
    return functions


def parse_game_functions(region: str) -> list[AssemblyFunction]:
    """Return game-overlay functions in file-offset order."""

    return parse_assembly_functions(region, "game")


def parse_main_functions(region: str) -> list[AssemblyFunction]:
    """Return main-executable functions in file-offset order."""

    return parse_assembly_functions(region, "main")


def format_range(start: int, end: int) -> str:
    return f"0x{start:X}:0x{end:X}"


def nonmatching_asm_directory(source: str) -> Path:
    source_path = Path(source)
    try:
        relative = source_path.relative_to("src/game").with_suffix("")
    except ValueError:
        relative = source_path.relative_to("src").with_suffix("")
    return Path("asm/nonmatchings") / relative


def nonmatching_asm_path(source: str, symbol: str) -> Path:
    return nonmatching_asm_directory(source) / f"{symbol}.s"


def global_asm_pragma(source: str, symbol: str) -> str:
    return f'#pragma GLOBAL_ASM("{nonmatching_asm_path(source, symbol)}")'


def matching_delimiter(content: str, start: int, opening: str, closing: str) -> int:
    """Find a balanced C delimiter while ignoring comments and literals."""

    depth = 0
    index = start
    state = "code"
    while index < len(content):
        char = content[index]
        following = content[index + 1] if index + 1 < len(content) else ""
        if state == "code":
            if char == "/" and following == "*":
                state = "block_comment"
                index += 2
                continue
            if char == "/" and following == "/":
                state = "line_comment"
                index += 2
                continue
            if char == '"':
                state = "string"
            elif char == "'":
                state = "character"
            elif char == opening:
                depth += 1
            elif char == closing:
                depth -= 1
                if depth == 0:
                    return index
        elif state == "block_comment" and char == "*" and following == "/":
            state = "code"
            index += 2
            continue
        elif state == "line_comment" and char == "\n":
            state = "code"
        elif state in {"string", "character"}:
            if char == "\\":
                index += 2
                continue
            if (state == "string" and char == '"') or (
                state == "character" and char == "'"
            ):
                state = "code"
        index += 1
    raise ProjectStateError("unterminated C delimiter while preserving deferred candidate")


def c_function_span(content: str, symbol: str) -> tuple[int, int]:
    """Locate one ordinary source-level C definition by symbol."""

    matches: list[tuple[int, int]] = []
    for match in re.finditer(rf"\b{re.escape(symbol)}\s*\(", content):
        opening_parenthesis = content.find("(", match.start())
        closing_parenthesis = matching_delimiter(
            content, opening_parenthesis, "(", ")"
        )
        body_start = closing_parenthesis + 1
        while body_start < len(content) and content[body_start].isspace():
            body_start += 1
        if body_start >= len(content) or content[body_start] != "{":
            continue
        body_end = matching_delimiter(content, body_start, "{", "}") + 1
        line_start = content.rfind("\n", 0, match.start()) + 1
        if not content[line_start:match.start()].strip():
            raise ProjectStateError(
                f"cannot preserve multiline return declaration for {symbol}"
            )
        if body_end < len(content) and content[body_end] == "\n":
            body_end += 1
        matches.append((line_start, body_end))
    if len(matches) != 1:
        raise ProjectStateError(
            f"expected exactly one C definition for {symbol}; found {len(matches)}"
        )
    return matches[0]


def deferred_candidate_markers(
    symbol: str, current_score: int | None = None
) -> tuple[str, str]:
    score = f" CURRENT ({current_score})" if current_score is not None else ""
    return (
        f"#if 0 /* {DEFERRED_CANDIDATE_TAG} {symbol}{score} */",
        f"#endif /* {DEFERRED_CANDIDATE_TAG} {symbol} */",
    )


def preserve_deferred_candidate(
    source: str, symbol: str, current_score: int
) -> tuple[Path, str, str]:
    """Disable the best C candidate in place and restore its raw-ASM pragma."""

    path = ROOT / source
    content = path.read_text(encoding="utf-8")
    pragma = global_asm_pragma(source, symbol)
    start_marker, end_marker = deferred_candidate_markers(symbol, current_score)
    marker_prefix = f"#if 0 /* {DEFERRED_CANDIDATE_TAG} {symbol}"
    if marker_prefix in content or end_marker in content:
        raise ProjectStateError(f"{symbol} already has a preserved deferred candidate")
    if pragma in content:
        raise ProjectStateError(
            f"{symbol} still uses GLOBAL_ASM; add the best C candidate before deferring it"
        )
    start, end = c_function_span(content, symbol)
    candidate = content[start:end].rstrip("\n")
    replacement = (
        f"{start_marker}\n{candidate}\n{end_marker}\n{pragma}\n"
    )
    return path, content, content[:start] + replacement + content[end:]


def restore_deferred_candidate(source: str, symbol: str) -> tuple[Path, str, str]:
    """Restore a preserved C candidate and remove its raw-ASM pragma."""

    path = ROOT / source
    content = path.read_text(encoding="utf-8")
    pragma = global_asm_pragma(source, symbol)
    _, end_marker = deferred_candidate_markers(symbol)
    marker_pattern = re.compile(
        rf"#if 0 /\* {re.escape(DEFERRED_CANDIDATE_TAG)} "
        rf"{re.escape(symbol)}(?: CURRENT \(\d+\))? \*/"
    )
    marker_match = marker_pattern.search(content)
    if marker_match is None:
        raise ProjectStateError(f"{symbol} lacks a preserved deferred candidate")
    start = marker_match.start()
    candidate_start = marker_match.end()
    if content[candidate_start:candidate_start + 1] == "\n":
        candidate_start += 1
    marker_start = content.find(end_marker, candidate_start)
    if marker_start < 0:
        raise ProjectStateError(f"{symbol} has an unterminated deferred candidate")
    candidate = content[candidate_start:marker_start].rstrip("\n")
    block_end = marker_start + len(end_marker)
    if content[block_end:block_end + 1] == "\n":
        block_end += 1
    if content[block_end:block_end + len(pragma)] != pragma:
        raise ProjectStateError(
            f"{symbol} deferred candidate is not followed by its GLOBAL_ASM pragma"
        )
    block_end += len(pragma)
    if content[block_end:block_end + 1] == "\n":
        block_end += 1
    return path, content, content[:start] + candidate + "\n" + content[block_end:]


def source_unit_header_span(content: str) -> tuple[int, int] | None:
    """Locate the reviewed-source-unit block comment, if present."""

    marker = content.find("Reviewed source unit:")
    if marker < 0:
        return None
    start = content.rfind("/*", 0, marker)
    end = content.find("*/", marker)
    if start < 0 or end < 0:
        raise ProjectStateError("reviewed source-unit header is not a complete block comment")
    return start, end + 2


def source_unit_header_follows_includes(content: str) -> bool:
    """Return whether the reviewed-source-unit block immediately follows includes."""

    span = source_unit_header_span(content)
    if span is None:
        return True
    lines = content.splitlines(keepends=True)
    header_line = content.count("\n", 0, span[0])
    include_lines = [
        index for index, line in enumerate(lines) if line.startswith("#include ")
    ]
    if not include_lines:
        return header_line == 0
    last_include = include_lines[-1]
    return (
        header_line == last_include + 2
        and lines[last_include + 1].strip() == ""
    )


def normalize_source_unit_header(content: str) -> str:
    """Move a reviewed-source-unit block directly below the include block."""

    span = source_unit_header_span(content)
    if span is None or source_unit_header_follows_includes(content):
        return content
    lines = content.splitlines(keepends=True)
    start_line = content.count("\n", 0, span[0])
    end_line = content.count("\n", 0, span[1] - 1) + 1
    header = lines[start_line:end_line]
    del lines[start_line:end_line]
    while start_line < len(lines) and not lines[start_line].strip():
        del lines[start_line]

    include_lines = [
        index for index, line in enumerate(lines) if line.startswith("#include ")
    ]
    insertion = include_lines[-1] + 1 if include_lines else 0
    while insertion < len(lines) and not lines[insertion].strip():
        del lines[insertion]
    lines[insertion:insertion] = ["\n", *header, "\n"] if include_lines else [*header, "\n"]
    return "".join(lines)


def normalize_source_unit_headers() -> None:
    """Normalize every reviewed C source header without changing its contents."""

    changed: list[Path] = []
    for path in sorted((ROOT / "src").rglob("*.c")):
        content = path.read_text(encoding="utf-8")
        normalized = normalize_source_unit_header(content)
        if normalized == content:
            continue
        path.write_text(normalized, encoding="utf-8")
        changed.append(path)
    print(f"Normalized reviewed source-unit headers in {len(changed)} file(s).")


def file_sha1(path: Path) -> str:
    digest = hashlib.sha1()
    with path.open("rb") as source:
        for chunk in iter(lambda: source.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def validate_rom_config(config: dict[str, Any]) -> None:
    profiles = config.get("profiles")
    if config.get("schema_version") != 1 or not isinstance(profiles, dict):
        raise ProjectStateError("config/roms.json must use schema_version 1 and a profiles object")
    if set(profiles) != set(KNOWN_REGIONS):
        raise ProjectStateError("config/roms.json must define exactly the us and eu profiles")
    for region in KNOWN_REGIONS:
        profile = profiles[region]
        if not isinstance(profile, dict):
            raise ProjectStateError(f"ROM profile '{region}' must be an object")
        sha1 = profile.get("sha1")
        if sha1 is not None and (not isinstance(sha1, str) or len(sha1) != 40):
            raise ProjectStateError(f"ROM profile '{region}' has an invalid sha1")
        size = profile.get("size_bytes")
        if not isinstance(size, int) or size <= 0:
            raise ProjectStateError(f"ROM profile '{region}' requires a positive size_bytes")
        expected_status = "active" if region in TARGET_REGIONS else "future"
        if profile.get("status") != expected_status:
            raise ProjectStateError(
                f"ROM profile '{region}' must have status '{expected_status}'"
            )


def validate_code_ranges(config: dict[str, Any]) -> dict[str, dict[str, tuple[int, int]]]:
    """Validate and normalize the byte ranges used by progress reporting."""

    configured = config.get("overlays")
    if config.get("schema_version") != 1 or not isinstance(configured, dict):
        raise ProjectStateError("config/overlays.json must use schema_version 1 and an overlays object")
    if not set(OVERLAYS).issubset(configured):
        raise ProjectStateError("config/overlays.json must define progress ranges for main and game")

    ranges: dict[str, dict[str, tuple[int, int]]] = {}
    for overlay in OVERLAYS:
        raw_ranges = configured[overlay].get("code_ranges")
        if not isinstance(raw_ranges, dict) or set(raw_ranges) != set(KNOWN_REGIONS):
            raise ProjectStateError(f"{overlay} must define exactly the us and eu code ranges")
        ranges[overlay] = {}
        for region in KNOWN_REGIONS:
            raw_range = raw_ranges[region]
            if not isinstance(raw_range, dict):
                raise ProjectStateError(f"{overlay}/{region} code range must be an object")
            try:
                start = int(raw_range["start"], 0)
                end = int(raw_range["end"], 0)
            except (KeyError, TypeError, ValueError) as error:
                raise ProjectStateError(
                    f"{overlay}/{region} code range needs hexadecimal start and end"
                ) from error
            if start < 0 or end <= start:
                raise ProjectStateError(f"{overlay}/{region} code range must be non-empty")
            ranges[overlay][region] = (start, end)
    return ranges


def is_complete(entry: dict[str, Any]) -> bool:
    """Return whether a function matches every currently active target."""

    return all(entry["regions"][region]["state"] == "matched" for region in TARGET_REGIONS)


def validate_region_keys(regions: Any, owner: str) -> dict[str, Any]:
    """Require active targets while allowing preserved future-region metadata."""

    if not isinstance(regions, dict):
        raise ProjectStateError(f"{owner} must have a regions object")
    missing = set(TARGET_REGIONS) - set(regions)
    unknown = set(regions) - set(KNOWN_REGIONS)
    if missing:
        raise ProjectStateError(f"{owner} is missing active region entries: {', '.join(sorted(missing))}")
    if unknown:
        raise ProjectStateError(f"{owner} has unknown region entries: {', '.join(sorted(unknown))}")
    return regions


def mapped_subsegments(region: str, overlay: str) -> list[tuple[int, str, str | None]]:
    """Read the checked-in map entries that determine object boundaries."""

    directory = "profiles" if overlay == "main" else "game"
    path = ROOT / "config" / directory / f"{region}.yaml"
    entries: list[tuple[int, str, str | None]] = []
    for line in path.read_text(encoding="utf-8").splitlines():
        match = SUBSEGMENT_PATTERN.match(line)
        if match:
            name = match.group(3).strip() if match.group(3) else None
            entries.append((int(match.group(1), 0), match.group(2), name))
    return entries


def mapped_library_text_ranges(
    code_ranges: dict[str, dict[str, tuple[int, int]]],
) -> dict[str, dict[str, list[tuple[int, int]]]]:
    """Return executable ranges supplied by archives in the canonical build map."""

    ranges: dict[str, dict[str, list[tuple[int, int]]]] = {
        overlay: {region: [] for region in KNOWN_REGIONS} for overlay in OVERLAYS
    }
    for overlay in OVERLAYS:
        for region in KNOWN_REGIONS:
            code_start, code_end = code_ranges[overlay][region]
            directory = "profiles" if overlay == "main" else "game"
            map_path = ROOT / "config" / directory / f"{region}.yaml"
            if not map_path.is_file():
                continue
            entries = mapped_subsegments(region, overlay)
            for index, (start, kind, name) in enumerate(entries):
                if kind != "lib" or name is None:
                    continue
                fields = [field.strip() for field in name.split(",")]
                # RSP has a separate ISA and payload ledger; preserve CPU progress.
                if fields[0] == "librsp":
                    continue
                if len(fields) < 3 or fields[-1] != ".text":
                    continue
                if start < code_start or start >= code_end:
                    raise ProjectStateError(
                        f"{overlay}/{region} library .text start 0x{start:X} falls outside "
                        f"the tracked code range {format_range(code_start, code_end)}"
                    )
                end = code_end
                for next_start, _, _ in entries[index + 1 :]:
                    if next_start > start:
                        end = min(next_start, code_end)
                        break
                if end <= start:
                    raise ProjectStateError(
                        f"{overlay}/{region} library .text at 0x{start:X} has no positive range"
                    )
                ranges[overlay][region].append((start, end))
    return ranges


def reference_subsegments(region: str, overlay: str) -> list[tuple[int, str, str | None]]:
    """Read the independent raw map, materializing game C/archive ranges as ASM."""

    if overlay == "game":
        return [
            (offset, "asm", None) if kind in {"c", "lib"} else (offset, kind, name)
            for offset, kind, name in mapped_subsegments(region, overlay)
        ]
    elif overlay == "main":
        content = (ROOT / "config" / "reference" / f"{region}.yaml").read_text(encoding="utf-8")
    else:
        raise ProjectStateError(f"unknown overlay: {overlay}")
    entries: list[tuple[int, str, str | None]] = []
    for line in content.splitlines():
        match = SUBSEGMENT_PATTERN.match(line)
        if match:
            name = match.group(3).strip() if match.group(3) else None
            entries.append((int(match.group(1), 0), match.group(2), name))
    return entries


def validate_integrated_source_mapping(
    source: str,
    unit_regions: dict[str, Any],
    members: list[dict[str, Any]],
) -> None:
    """Require a completed unit to exist and own its exact active C-map range."""

    source_path = ROOT / source
    if not source_path.is_file():
        raise ProjectStateError(f"completed source unit does not exist: {source}")
    overlays = {member.get("overlay", "main") for member in members}
    if len(overlays) != 1:
        raise ProjectStateError(f"{source} cannot span multiple overlays")
    overlay = overlays.pop()
    mapped_name = source.removeprefix("src/").removesuffix(".c")
    for region in TARGET_REGIONS:
        start = int(unit_regions[region]["start"], 0)
        end = int(unit_regions[region]["end"], 0)
        if start % 0x10 or end % 0x10:
            raise ProjectStateError(f"{source}/{region} C range must use 16-byte IDO object boundaries")
        entries = mapped_subsegments(region, overlay)
        if (start, "c", mapped_name) not in entries:
            raise ProjectStateError(
                f"{source}/{region} is integrated but is not mapped as C at 0x{start:X}"
            )
        _, code_end = validate_code_ranges(load_json(OVERLAYS_FILE))[overlay][region]
        offsets = {offset for offset, _, _ in entries}
        if end != code_end and end not in offsets:
            raise ProjectStateError(
                f"{source}/{region} is integrated but has no map boundary at 0x{end:X}"
            )


def source_unit_work_state(members: list[dict[str, Any]]) -> str:
    if all(is_complete(member) for member in members):
        return "candidate"
    if any(
        member["regions"][region]["state"] in {"in_progress", "candidate", "matched"}
        for member in members
        for region in TARGET_REGIONS
    ):
        return "in_progress"
    return "raw_asm"


def validate_functions(data: dict[str, Any]) -> list[dict[str, Any]]:
    if data.get("schema_version") != 1 or not isinstance(data.get("functions"), list):
        raise ProjectStateError("progress/functions.json must use schema_version 1 and a functions array")
    identifiers: set[str] = set()
    functions: list[dict[str, Any]] = data["functions"]
    for entry in functions:
        identifier = entry.get("symbol")
        if not isinstance(identifier, str) or not identifier:
            raise ProjectStateError("each function needs a non-empty symbol")
        if identifier in identifiers:
            raise ProjectStateError(f"duplicate function symbol: {identifier}")
        identifiers.add(identifier)
        if entry.get("overlay", "main") not in OVERLAYS:
            raise ProjectStateError(f"{identifier} has an invalid overlay")
        regions = validate_region_keys(entry.get("regions"), identifier)
        for region in regions:
            result = regions[region]
            if not isinstance(result, dict) or result.get("state") not in STATES:
                raise ProjectStateError(f"{identifier}/{region} has an invalid state")
            region_symbol = result.get("symbol")
            if not isinstance(region_symbol, str) or not region_symbol:
                raise ProjectStateError(f"{identifier}/{region} needs a non-empty region symbol")
            vram = result.get("vram")
            if not isinstance(vram, str) or not vram.startswith("0x"):
                raise ProjectStateError(f"{identifier}/{region} needs a hexadecimal vram address")
            size_bytes = result.get("size_bytes")
            if size_bytes is not None and (
                not isinstance(size_bytes, int) or isinstance(size_bytes, bool) or size_bytes <= 0
            ):
                raise ProjectStateError(f"{identifier}/{region} size_bytes must be a positive integer")
            if result["state"] == "matched":
                evidence = result.get("evidence")
                if not isinstance(evidence, dict) or evidence.get("current_differences") != 0:
                    raise ProjectStateError(
                        f"{identifier}/{region} is matched but lacks zero-difference evidence"
                    )
                for key in ("rom_sha1", "verified_revision"):
                    if not isinstance(evidence.get(key), str) or not evidence[key]:
                        raise ProjectStateError(f"{identifier}/{region} evidence needs {key}")
        deferred = entry.get("deferred")
        if deferred is not None:
            if not isinstance(deferred, dict):
                raise ProjectStateError(f"{identifier} deferred metadata must be an object")
            reason = deferred.get("reason")
            if not isinstance(reason, str) or not reason.strip():
                raise ProjectStateError(f"{identifier} deferred metadata needs a reason")
            revision = deferred.get("recorded_revision")
            if not isinstance(revision, str) or not revision:
                raise ProjectStateError(
                    f"{identifier} deferred metadata needs recorded_revision"
                )
            if deferred.get("candidate_preserved") is not True:
                raise ProjectStateError(
                    f"{identifier} deferred metadata must confirm candidate_preserved"
                )
            current_score = deferred.get("current_score")
            if current_score is not None and (
                not isinstance(current_score, int)
                or isinstance(current_score, bool)
                or current_score <= 0
            ):
                raise ProjectStateError(
                    f"{identifier} deferred metadata current_score must be a positive integer"
                )
            if is_complete(entry):
                raise ProjectStateError(f"matched function {identifier} cannot be deferred")
    return functions


def validate_source_units(
    data: dict[str, Any],
    functions: list[dict[str, Any]],
    *,
    archive_replacements: frozenset[str] = frozenset(),
) -> list[dict[str, Any]]:
    if data.get("schema_version") != 1 or not isinstance(data.get("source_units"), list):
        raise ProjectStateError("progress/source_units.json must use schema_version 1 and a source_units array")
    functions_by_symbol = {entry["symbol"]: entry for entry in functions}
    seen_sources: set[str] = set()
    units: list[dict[str, Any]] = data["source_units"]
    for unit in units:
        source = unit.get("source")
        if not isinstance(source, str) or not source.startswith("src/") or source in seen_sources:
            raise ProjectStateError("each source unit needs a unique source path under src/")
        seen_sources.add(source)
        names = unit.get("functions")
        if not isinstance(names, list) or not names or any(name not in functions_by_symbol for name in names):
            raise ProjectStateError(f"{source} must list one or more registered functions")
        if any(functions_by_symbol[name].get("source") != source for name in names):
            raise ProjectStateError(f"{source} must own every function it lists")
        integration = unit.get("integration")
        if integration not in SOURCE_UNIT_INTEGRATIONS:
            raise ProjectStateError(f"{source} integration must be raw_asm, mixed, or c")
        regions = validate_region_keys(unit.get("regions"), source)
        member_regions = [set(functions_by_symbol[name]["regions"]) for name in names]
        if any(not set(regions).issubset(available) for available in member_regions):
            raise ProjectStateError(f"{source} region entries must be available for every function it owns")
        for region in regions:
            result = regions[region]
            if not isinstance(result, dict) or result.get("state") not in SOURCE_UNIT_STATES:
                raise ProjectStateError(f"{source}/{region} has an invalid source-unit state")
            for key in ("start", "end"):
                if not isinstance(result.get(key), str) or not result[key].startswith("0x"):
                    raise ProjectStateError(f"{source}/{region} needs hexadecimal {key}")
        complete = all(regions[region]["state"] == "complete" for region in TARGET_REGIONS)
        boundary_evidence = unit.get("boundary_evidence")
        if boundary_evidence is not None:
            if not isinstance(boundary_evidence, dict):
                raise ProjectStateError(f"{source} boundary_evidence must be an object")
            unknown_evidence = set(boundary_evidence) - set(KNOWN_REGIONS)
            if unknown_evidence:
                raise ProjectStateError(
                    f"{source} has boundary evidence for unknown regions: "
                    f"{', '.join(sorted(unknown_evidence))}"
                )
            for region, evidence in boundary_evidence.items():
                if not isinstance(evidence, dict) or evidence.get("kind") not in BOUNDARY_EVIDENCE_KINDS:
                    raise ProjectStateError(f"{source}/{region} has invalid boundary evidence kind")
                if evidence.get("reviewed") is not True:
                    raise ProjectStateError(f"{source}/{region} boundary evidence is not reviewed")
                reference = evidence.get("reference")
                if not isinstance(reference, str) or not reference.strip():
                    raise ProjectStateError(f"{source}/{region} boundary evidence needs a reference")
        if complete and (integration != "c" or not source.startswith("src/game/done/")):
            raise ProjectStateError(f"{source} is complete only after C integration under src/game/done/")
        members = [functions_by_symbol[name] for name in names]
        if complete and not all(is_complete(member) for member in members):
            raise ProjectStateError(f"{source} is complete but has an unfinished function")
        if integration == "c" and not complete:
            raise ProjectStateError(f"{source} uses C integration but is not complete")
        if integration == "mixed" and (complete or source.startswith("src/game/done/")):
            raise ProjectStateError(f"{source} mixed integration must remain outside src/game/done/")
        if integration in {"mixed", "c"}:
            missing_evidence = [
                region
                for region in TARGET_REGIONS
                if not isinstance(boundary_evidence, dict) or region not in boundary_evidence
            ]
            if missing_evidence:
                raise ProjectStateError(
                    f"{source} is integrated but lacks reviewed boundary evidence for "
                    f"{', '.join(missing_evidence)}"
                )
            # Retirement validates the exact archive extent and untouched source
            # below; its map has already transitioned from C to a library entry.
            if source not in archive_replacements:
                validate_integrated_source_mapping(source, regions, members)
        source_path = ROOT / source
        if source_path.is_file():
            source_content = source_path.read_text(encoding="utf-8")
            if not source_unit_header_follows_includes(source_content):
                raise ProjectStateError(
                    f"{source} reviewed source-unit header must immediately follow its includes"
                )
            stale_placeholders = [
                member["symbol"]
                for member in members
                if is_complete(member)
                and global_asm_pragma(source, member["symbol"]) in source_content
            ]
            if stale_placeholders:
                raise ProjectStateError(
                    f"{source} still uses GLOBAL_ASM for matched functions: "
                    + ", ".join(stale_placeholders)
                )
    return units


def validate_deferred_candidate_sources(functions: list[dict[str, Any]]) -> None:
    """Require every deferred inventory record to retain a resumable source block."""

    for function in functions:
        if not function.get("deferred"):
            continue
        source = function.get("source")
        if not isinstance(source, str) or not source:
            raise ProjectStateError(
                f"deferred function {function['symbol']} needs an assigned source"
            )
        try:
            restore_deferred_candidate(source, function["symbol"])
        except FileNotFoundError as error:
            raise ProjectStateError(
                f"deferred function {function['symbol']} source does not exist: {source}"
            ) from error


def validate_project() -> tuple[dict[str, Any], list[dict[str, Any]]]:
    roms = load_json(ROMS_FILE)
    functions = load_json(FUNCTIONS_FILE)
    validate_rom_config(roms)
    validate_code_ranges(load_json(OVERLAYS_FILE))
    validated_functions = validate_functions(functions)
    validate_deferred_candidate_sources(validated_functions)
    validate_source_units(load_json(SOURCE_UNITS_FILE), validated_functions)
    return roms, validated_functions


def merged_size(ranges: list[tuple[int, int]]) -> int:
    """Return the union size so accidental overlapping inventory cannot inflate progress."""

    total = 0
    current_start: int | None = None
    current_end: int | None = None
    for start, end in sorted(ranges):
        if current_start is None:
            current_start, current_end = start, end
        elif start > current_end:
            total += current_end - current_start
            current_start, current_end = start, end
        else:
            current_end = max(current_end, end)
    if current_start is not None and current_end is not None:
        total += current_end - current_start
    return total


def percentage(matched: int, total: int) -> float:
    return round((matched / total) * 100, 6) if total else 0.0


def code_progress(
    functions: list[dict[str, Any]],
    source_units: list[dict[str, Any]],
    code_ranges: dict[str, dict[str, tuple[int, int]]],
    library_ranges: dict[str, dict[str, list[tuple[int, int]]]] | None = None,
) -> dict[str, Any]:
    """Count matched functions, source units, and archive text against executable bytes."""

    functions_by_symbol = {entry["symbol"]: entry for entry in functions}
    library_ranges = library_ranges or {}
    source_unit_ranges: dict[str, dict[str, list[tuple[int, int]]]] = {
        overlay: {region: [] for region in KNOWN_REGIONS} for overlay in OVERLAYS
    }
    complete_unit_ranges: dict[str, dict[str, list[tuple[int, int]]]] = {
        overlay: {region: [] for region in KNOWN_REGIONS} for overlay in OVERLAYS
    }

    for unit in source_units:
        members = [functions_by_symbol[name] for name in unit["functions"]]
        overlay = members[0].get("overlay", "main")
        if any(member.get("overlay", "main") != overlay for member in members):
            raise ProjectStateError(f"{unit['source']} cannot span multiple overlays")
        for region in KNOWN_REGIONS:
            if region not in unit["regions"]:
                continue
            start = int(unit["regions"][region]["start"], 0)
            end = int(unit["regions"][region]["end"], 0)
            range_start, range_end = code_ranges[overlay][region]
            if start < range_start or end > range_end or end <= start:
                raise ProjectStateError(
                    f"{unit['source']}/{region} range {format_range(start, end)} falls outside "
                    f"the {overlay} code range {format_range(range_start, range_end)}"
                )
            source_unit_ranges[overlay][region].append((start, end))
            region_matched = all(
                member.get("regions", {}).get(region, {}).get("state") == "matched"
                for member in members
            )
            if region_matched:
                complete_unit_ranges[overlay][region].append((start, end))

    library_text_bytes: dict[str, dict[str, int]] = {
        overlay: {region: 0 for region in KNOWN_REGIONS} for overlay in OVERLAYS
    }
    for overlay in OVERLAYS:
        for region in KNOWN_REGIONS:
            range_start, range_end = code_ranges[overlay][region]
            archive_ranges = library_ranges.get(overlay, {}).get(region, [])
            for start, end in archive_ranges:
                if start < range_start or end > range_end or end <= start:
                    raise ProjectStateError(
                        f"{overlay}/{region} library range {format_range(start, end)} falls "
                        f"outside the tracked code range {format_range(range_start, range_end)}"
                    )
                if any(
                    start < unit_end and unit_start < end
                    for unit_start, unit_end in source_unit_ranges[overlay][region]
                ):
                    raise ProjectStateError(
                        f"{overlay}/{region} library range {format_range(start, end)} overlaps "
                        "a tracked source unit"
                    )
            library_text_bytes[overlay][region] = merged_size(archive_ranges)

    matched_function_bytes: dict[str, dict[str, int]] = {
        overlay: {region: 0 for region in KNOWN_REGIONS} for overlay in OVERLAYS
    }
    for region in KNOWN_REGIONS:
        sizes = active_function_sizes(functions, source_units, region)
        for entry in functions:
            region_record = entry.get("regions", {}).get(region)
            if region_record is None or region_record["state"] != "matched":
                continue
            symbol = entry["symbol"]
            if symbol not in sizes:
                raise ProjectStateError(
                    f"cannot determine matched byte count for {symbol}/{region}"
                )
            overlay = entry.get("overlay", "main")
            matched_function_bytes[overlay][region] += sizes[symbol]

    overlay_results: dict[str, dict[str, Any]] = {}
    region_results = {
        region: {
            "matched_bytes": 0,
            "fully_matched_source_unit_bytes": 0,
            "library_text_bytes": 0,
            "total_bytes": 0,
        }
        for region in KNOWN_REGIONS
    }
    matched_total = 0
    complete_unit_total = 0
    byte_total = 0
    for overlay in OVERLAYS:
        overlay_matched = 0
        overlay_complete_units = 0
        overlay_total = 0
        overlay_regions: dict[str, dict[str, Any]] = {}
        for region in KNOWN_REGIONS:
            start, end = code_ranges[overlay][region]
            total = end - start
            archive_bytes = library_text_bytes[overlay][region]
            matched = matched_function_bytes[overlay][region] + archive_bytes
            complete_units = merged_size(complete_unit_ranges[overlay][region]) + archive_bytes
            if matched > total or complete_units > total:
                raise ProjectStateError(
                    f"matched {overlay}/{region} bytes exceed the tracked code range"
                )
            if region in TARGET_REGIONS:
                overlay_matched += matched
                overlay_complete_units += complete_units
                overlay_total += total
            region_results[region]["matched_bytes"] += matched
            region_results[region]["fully_matched_source_unit_bytes"] += complete_units
            region_results[region]["library_text_bytes"] += archive_bytes
            region_results[region]["total_bytes"] += total
            overlay_regions[region] = {
                "matched_bytes": matched,
                "fully_matched_source_unit_bytes": complete_units,
                "library_text_bytes": archive_bytes,
                "total_bytes": total,
                "percentage": percentage(matched, total),
                "fully_matched_source_unit_percentage": percentage(complete_units, total),
            }
        overlay_results[overlay] = {
            "matched_bytes": overlay_matched,
            "fully_matched_source_unit_bytes": overlay_complete_units,
            "library_text_bytes": sum(
                library_text_bytes[overlay][region] for region in TARGET_REGIONS
            ),
            "total_bytes": overlay_total,
            "percentage": percentage(overlay_matched, overlay_total),
            "fully_matched_source_unit_percentage": percentage(
                overlay_complete_units, overlay_total
            ),
            "regions": overlay_regions,
        }
        matched_total += overlay_matched
        complete_unit_total += overlay_complete_units
        byte_total += overlay_total

    for values in region_results.values():
        values["percentage"] = percentage(values["matched_bytes"], values["total_bytes"])
        values["fully_matched_source_unit_percentage"] = percentage(
            values["fully_matched_source_unit_bytes"], values["total_bytes"]
        )
    return {
        "matched_bytes": matched_total,
        "fully_matched_source_unit_bytes": complete_unit_total,
        "library_text_bytes": sum(
            library_text_bytes[overlay][region]
            for overlay in OVERLAYS
            for region in TARGET_REGIONS
        ),
        "total_bytes": byte_total,
        "percentage": percentage(matched_total, byte_total),
        "fully_matched_source_unit_percentage": percentage(
            complete_unit_total, byte_total
        ),
        "overlays": overlay_results,
        "regions": region_results,
    }


def summary(functions: list[dict[str, Any]]) -> dict[str, Any]:
    per_region: dict[str, dict[str, int]] = {}
    for region in TARGET_REGIONS:
        counts = Counter(entry["regions"][region]["state"] for entry in functions)
        per_region[region] = {state: counts.get(state, 0) for state in sorted(STATES)}
    target_matched = sum(is_complete(entry) for entry in functions)
    source_units = validate_source_units(load_json(SOURCE_UNITS_FILE), functions)
    assigned_functions = {
        identifier for unit in source_units for identifier in unit["functions"]
    }
    code_ranges = validate_code_ranges(load_json(OVERLAYS_FILE))
    bytes_result = code_progress(
        functions,
        source_units,
        code_ranges,
        mapped_library_text_ranges(code_ranges),
    )
    complete_units = sum(
        all(unit["regions"][region]["state"] == "complete" for region in TARGET_REGIONS)
        for unit in source_units
    )
    overlays: dict[str, dict[str, int]] = {}
    for overlay in OVERLAYS:
        members = [entry for entry in functions if entry.get("overlay", "main") == overlay]
        if members:
            overlays[overlay] = {
                "known_functions": len(members),
                "target_matched": sum(is_complete(entry) for entry in members),
            }
    return {
        "schema_version": 1,
        "active_regions": list(TARGET_REGIONS),
        "future_regions": list(FUTURE_REGIONS),
        "known_functions": len(functions),
        "target_matched": target_matched,
        "target_remaining": len(functions) - target_matched,
        "source_units": len(source_units),
        "mixed_source_units": sum(unit["integration"] == "mixed" for unit in source_units),
        "unassigned_functions": sum(
            entry["symbol"] not in assigned_functions for entry in functions
        ),
        "complete_source_units": complete_units,
        "code_bytes": bytes_result,
        "overlays": overlays,
        "regions": per_region,
    }


def render_markdown(result: dict[str, Any]) -> str:
    lines = [
        "# Decompilation progress",
        "",
        "This file is generated by `./conker progress render`; do not edit it manually.",
        "",
        f"- Known functions: **{result['known_functions']}**",
        "- Active target: **North America (US)**",
        "- Future target: **Europe/PAL (not counted)**",
        f"- Matched for active target: **{result['target_matched']}**",
        f"- Remaining: **{result['target_remaining']}**",
        f"- Completed source units: **{result['complete_source_units']} / {result['source_units']}**",
        f"- Mixed C/ASM source units in the canonical build: **{result['mixed_source_units']}**",
        f"- Functions awaiting reviewed source-unit boundaries: **{result['unassigned_functions']}**",
        "- Matched function bytes for active target: "
        f"**{result['code_bytes']['matched_bytes']:,} / {result['code_bytes']['total_bytes']:,} "
        f"({result['code_bytes']['percentage']:.4f}%)**",
        "- Fully matched source-unit bytes: "
        f"**{result['code_bytes']['fully_matched_source_unit_bytes']:,} / "
        f"{result['code_bytes']['total_bytes']:,} "
        f"({result['code_bytes']['fully_matched_source_unit_percentage']:.4f}%)**",
        "- Archive-backed library text bytes included above: "
        f"**{result['code_bytes']['library_text_bytes']:,}**",
        "",
        "| Region | Raw ASM | In progress | Candidate | Matched | Blocked |",
        "| --- | ---: | ---: | ---: | ---: | ---: |",
    ]
    for region in TARGET_REGIONS:
        counts = result["regions"][region]
        lines.append(
            "| {name} | {raw} | {progress} | {candidate} | {matched} | {blocked} |".format(
                name=REGION_NAMES[region],
                raw=counts["raw_asm"],
                progress=counts["in_progress"],
                candidate=counts["candidate"],
                matched=counts["matched"],
                blocked=counts["blocked"],
            )
        )
    lines.extend(
        [
            "",
            "| Region | Matched function bytes | Fully matched source-unit bytes | Total code bytes | Function byte match |",
            "| --- | ---: | ---: | ---: | ---: |",
        ]
    )
    for region in KNOWN_REGIONS:
        values = result["code_bytes"]["regions"][region]
        lines.append(
            f"| {REGION_NAMES[region]} | {values['matched_bytes']:,} | "
            f"{values['fully_matched_source_unit_bytes']:,} | "
            f"{values['total_bytes']:,} | {values['percentage']:.4f}% |"
        )
    lines.extend(
        [
            "",
            "| Area | Known functions | Matched for active target | Matched function bytes | Fully matched source-unit bytes | Total bytes | Function byte match |",
            "| --- | ---: | ---: | ---: | ---: | ---: | ---: |",
        ]
    )
    for overlay, counts in result["overlays"].items():
        byte_counts = result["code_bytes"]["overlays"][overlay]
        lines.append(
            f"| {OVERLAYS[overlay]} | {counts['known_functions']} | {counts['target_matched']} | "
            f"{byte_counts['matched_bytes']:,} | "
            f"{byte_counts['fully_matched_source_unit_bytes']:,} | "
            f"{byte_counts['total_bytes']:,} | "
            f"{byte_counts['percentage']:.4f}% |"
        )
    lines.extend(
        [
            "",
            "A function inventory entry is matched when its US record has zero-difference evidence.",
            "Each regional byte total credits functions with independent zero-difference evidence for that region, including C functions in mixed C/`GLOBAL_ASM` source units, plus executable `.text` ranges supplied by verified archives in the canonical build map.",
            "Fully matched source-unit bytes credit a reviewed regional range only after every function in that unit matches, and also include those archive-backed `.text` ranges as complete source objects.",
            "EU/PAL configuration, badge, and regional byte total are informational for the future target and do not affect current completion.",
            "A source unit is complete only after reviewed boundary evidence, every listed US function is matched, and the unit is integrated as C under `src/game/done/`.",
            "",
        ]
    )
    return "\n".join(lines)


def render_badge(result: dict[str, Any], region: str) -> dict[str, Any]:
    """Return one region's Shields badge for the matched-byte metric."""

    region_progress = result["code_bytes"]["regions"][region]
    value = f"{region_progress['percentage']:.4f}".rstrip("0").rstrip(".")
    return {
        "schemaVersion": 1,
        "label": REGION_NAMES[region],
        "message": f"{value}%",
        "color": "blue",
    }


def progress(args: argparse.Namespace) -> None:
    _, functions = validate_project()
    result = summary(functions)
    markdown = render_markdown(result)
    badges = {region: render_badge(result, region) for region in KNOWN_REGIONS}
    summary_content = json.dumps(result, indent=2, sort_keys=True) + "\n"
    badge_contents = {
        region: json.dumps(badge, indent=2, sort_keys=True) + "\n"
        for region, badge in badges.items()
    }
    if args.render:
        write_json(SUMMARY_FILE, result)
        for region, badge in badges.items():
            write_json(BADGE_FILES[region], badge)
        DOCUMENT_FILE.write_text(markdown, encoding="utf-8")
        print(
            "Updated "
            + ", ".join(
                str(path.relative_to(ROOT))
                for path in (SUMMARY_FILE, *BADGE_FILES.values(), DOCUMENT_FILE)
            )
        )
    elif args.check:
        expected_summary = SUMMARY_FILE.read_text(encoding="utf-8") if SUMMARY_FILE.exists() else ""
        expected_badges = {
            region: path.read_text(encoding="utf-8") if path.exists() else ""
            for region, path in BADGE_FILES.items()
        }
        expected_document = DOCUMENT_FILE.read_text(encoding="utf-8") if DOCUMENT_FILE.exists() else ""
        if (
            expected_summary != summary_content
            or expected_badges != badge_contents
            or expected_document != markdown
        ):
            raise ProjectStateError("progress output is stale; run ./conker progress render and commit the result")
        print("Progress output is current.")
    else:
        print(markdown, end="")


def render_progress(functions: list[dict[str, Any]]) -> None:
    """Refresh the checked-in progress views after an inventory change."""

    result = summary(functions)
    write_json(SUMMARY_FILE, result)
    for region in KNOWN_REGIONS:
        write_json(BADGE_FILES[region], render_badge(result, region))
    DOCUMENT_FILE.parent.mkdir(parents=True, exist_ok=True)
    DOCUMENT_FILE.write_text(render_markdown(result), encoding="utf-8")


def remove_source_todo(source: str, symbol: str) -> bool:
    """Remove one exact matched symbol from a reviewed source-unit TODO header."""

    path = ROOT / source
    if not path.is_file():
        return False
    lines = path.read_text(encoding="utf-8").splitlines(keepends=True)
    todo_start = next(
        (
            index
            for index, line in enumerate(lines)
            if "TODO: Implement these source-unit functions:" in line
        ),
        None,
    )
    if todo_start is None:
        return False
    todo_end = next(
        (
            index
            for index in range(todo_start + 1, len(lines))
            if "Unmatched members use generated GLOBAL_ASM placeholders below."
            in lines[index]
        ),
        None,
    )
    if todo_end is None:
        return False
    expected = f" * - {symbol}"
    matches = [
        index
        for index in range(todo_start + 1, todo_end)
        if lines[index].rstrip("\r\n") == expected
    ]
    if len(matches) != 1:
        return False
    del lines[matches[0]]
    todo_end = next(
        index
        for index in range(todo_start + 1, len(lines))
        if "Unmatched members use generated GLOBAL_ASM placeholders below."
        in lines[index]
    )
    if not any(
        lines[index].startswith(" * - ")
        for index in range(todo_start + 1, todo_end)
    ):
        block_start = todo_start
        if todo_start > 0 and lines[todo_start - 1].rstrip("\r\n") == " *":
            block_start -= 1
        del lines[block_start : todo_end + 1]
    path.write_text("".join(lines), encoding="utf-8")
    return True


def mark_matched(args: argparse.Namespace) -> None:
    """Record independently verified zero-difference evidence for one work item."""

    roms = load_json(ROMS_FILE)
    validate_rom_config(roms)
    functions_data = load_json(FUNCTIONS_FILE)
    source_units_data = load_json(SOURCE_UNITS_FILE)
    functions = validate_functions(functions_data)
    units = validate_source_units(source_units_data, functions)

    function = next((entry for entry in functions if entry["symbol"] == args.symbol), None)
    if function is None:
        raise ProjectStateError(f"unknown work-item ID: {args.symbol}")
    region = function["regions"].get(args.profile)
    if region is None:
        raise ProjectStateError(f"{args.symbol} is not registered for the {args.profile} profile")
    source_unit = next(
        (
            unit
            for unit in units
            if unit["source"] == function.get("source") and args.symbol in unit["functions"]
        ),
        None,
    )
    region["state"] = "matched"
    region["evidence"] = {
        "current_differences": 0,
        "rom_sha1": roms["profiles"][args.profile]["sha1"],
        "verified_revision": "working-tree",
    }
    function.pop("deferred", None)
    if source_unit is not None:
        unit_region = source_unit["regions"][args.profile]
        unit_members = [
            entry for entry in functions if entry["symbol"] in source_unit["functions"]
        ]
        unit_region["state"] = source_unit_work_state(unit_members)

    validated_functions = validate_functions(functions_data)
    validate_source_units(source_units_data, validated_functions)
    source_todo_updated = bool(function.get("source")) and remove_source_todo(
        function["source"], args.symbol
    )
    write_json(FUNCTIONS_FILE, functions_data)
    if source_unit is not None:
        write_json(SOURCE_UNITS_FILE, source_units_data)
    render_progress(validated_functions)
    print(
        f"Marked {args.symbol}/{args.profile} as matched; updated "
        f"{FUNCTIONS_FILE.relative_to(ROOT)}, "
        + (f"{SOURCE_UNITS_FILE.relative_to(ROOT)}, " if source_unit is not None else "")
        + (f"{function['source']}, " if source_todo_updated else "")
        + f"{SUMMARY_FILE.relative_to(ROOT)}, "
        + ", ".join(str(BADGE_FILES[region].relative_to(ROOT)) for region in KNOWN_REGIONS)
        + ", "
        + f"and {DOCUMENT_FILE.relative_to(ROOT)}."
    )


def defer_function(args: argparse.Namespace) -> None:
    """Temporarily remove a stubborn raw-ASM item from automatic selection."""

    functions_data = load_json(FUNCTIONS_FILE)
    functions = validate_functions(functions_data)
    function = next((entry for entry in functions if entry["symbol"] == args.symbol), None)
    if function is None:
        raise ProjectStateError(f"unknown work-item ID: {args.symbol}")
    if is_complete(function):
        raise ProjectStateError(f"matched function {args.symbol} cannot be deferred")
    if not all(
        function["regions"][region]["state"] == "raw_asm" for region in TARGET_REGIONS
    ):
        raise ProjectStateError(
            f"{args.symbol} must be raw_asm in every active region before it can be deferred"
        )
    reason = args.reason.strip()
    if not reason:
        raise ProjectStateError("defer requires a non-empty reason")
    if args.score <= 0:
        raise ProjectStateError("defer requires a positive nonzero focused-diff score")
    source = function.get("source")
    if not isinstance(source, str) or not source:
        raise ProjectStateError(f"{args.symbol} needs an assigned source before deferral")
    source_path, old_source, deferred_source = preserve_deferred_candidate(
        source, args.symbol, args.score
    )
    function["deferred"] = {
        "reason": reason,
        "current_score": args.score,
        "recorded_revision": "working-tree",
        "candidate_preserved": True,
    }
    validate_functions(functions_data)
    source_path.write_text(deferred_source, encoding="utf-8")
    try:
        write_json(FUNCTIONS_FILE, functions_data)
    except Exception:
        source_path.write_text(old_source, encoding="utf-8")
        raise
    print(f"Deferred {args.symbol}; preserved its C candidate in {source}: {reason}")


def resume_function(args: argparse.Namespace) -> None:
    """Return a deferred item to automatic selection."""

    functions_data = load_json(FUNCTIONS_FILE)
    functions = validate_functions(functions_data)
    function = next((entry for entry in functions if entry["symbol"] == args.symbol), None)
    if function is None:
        raise ProjectStateError(f"unknown work-item ID: {args.symbol}")
    if "deferred" not in function:
        raise ProjectStateError(f"{args.symbol} is not deferred")
    source = function.get("source")
    if not isinstance(source, str) or not source:
        raise ProjectStateError(f"{args.symbol} needs an assigned source before resume")
    source_path, old_source, resumed_source = restore_deferred_candidate(
        source, args.symbol
    )
    function.pop("deferred")
    validate_functions(functions_data)
    source_path.write_text(resumed_source, encoding="utf-8")
    try:
        write_json(FUNCTIONS_FILE, functions_data)
    except Exception:
        source_path.write_text(old_source, encoding="utf-8")
        raise
    print(
        f"Resumed {args.symbol}; restored its C candidate and made it eligible "
        "for next --ready again."
    )


def game_index() -> None:
    """Print US game functions as review candidates."""

    print("# Proposed US game-overlay work items (review before registering)")
    print("# ID | US symbol [range] words/shape")
    for index, function in enumerate(parse_game_functions("us"), start=1):
        detail = (
            f"{function.symbol} [{format_range(function.offset, function.end)}] "
            f"{function.word_count}/{function.shape}"
        )
        print(f"{index:03d} | {detail}")


def find_assembly_function(region: str, overlay: str, symbol: str) -> AssemblyFunction:
    for function in parse_assembly_functions(region, overlay):
        if function.symbol == symbol:
            return function
    preparation = (
        f"./conker _prepare-reference --profile {region}"
        if overlay == "main"
        else f"./conker game-asm --profile {region}"
    )
    raise ProjectStateError(
        f"{symbol} is not present in generated {region} {overlay} assembly; "
        f"run {preparation} and choose a listed symbol"
    )


def find_game_function(region: str, symbol: str) -> AssemblyFunction:
    return find_assembly_function(region, "game", symbol)


def validate_registration_source(source: str, overlay: str) -> None:
    """Require a safe C source path appropriate for the selected overlay."""

    parts = Path(source).parts
    if not source.startswith("src/") or not source.endswith(".c") or ".." in parts:
        raise ProjectStateError("--source must be a C path below src/")
    if overlay == "game" and not source.startswith("src/game/"):
        raise ProjectStateError("game --source must be a C path below src/game/")
    if overlay == "main" and source.startswith("src/game/"):
        raise ProjectStateError("main --source must not be below src/game/")


def register_function(args: argparse.Namespace, overlay: str) -> None:
    """Register one explicitly reviewed US function for an executable overlay."""

    source = args.source
    validate_registration_source(source, overlay)

    selected = {"us": find_assembly_function("us", overlay, args.us)}
    functions_data = load_json(FUNCTIONS_FILE)
    source_units_data = load_json(SOURCE_UNITS_FILE)
    functions = validate_functions(functions_data)
    units = validate_source_units(source_units_data, functions)

    if any(entry["symbol"] == args.identifier for entry in functions):
        raise ProjectStateError(f"function ID already registered: {args.identifier}")
    if any(unit["source"] == source for unit in units):
        raise ProjectStateError(f"source unit already registered: {source}")
    for region in TARGET_REGIONS:
        if any(entry["regions"][region]["symbol"] == selected[region].symbol for entry in functions):
            raise ProjectStateError(f"{region} function already registered: {selected[region].symbol}")

    function = {
        "overlay": overlay,
        "source": source,
        "symbol": args.identifier,
        "regions": {
            region: {
                "state": "raw_asm",
                "symbol": selected[region].symbol,
                "vram": f"0x{selected[region].vram:X}",
                "size_bytes": selected[region].end - selected[region].offset,
            }
            for region in TARGET_REGIONS
        },
    }
    updated_functions = {**functions_data, "functions": [*functions, function]}
    validated_functions = validate_functions(updated_functions)
    validate_source_units(source_units_data, validated_functions)

    write_json(FUNCTIONS_FILE, updated_functions)
    render_progress(validated_functions)
    print(
        f"Registered {overlay} function work {args.identifier}: "
        f"us={selected['us'].symbol}; source={source}; "
        "source-unit boundary remains unassigned"
    )


def register_game(args: argparse.Namespace) -> None:
    """Register one explicitly reviewed US game-overlay function."""

    register_function(args, "game")


def register_main(args: argparse.Namespace) -> None:
    """Register one explicitly reviewed US main-executable function."""

    register_function(args, "main")


def source_unit_skeleton_content(
    source: str,
    evidence_reference: str,
    pending_functions: list[str],
) -> str:
    """Return the canonical unmodified raw-ASM source-unit skeleton."""

    safe_reference = evidence_reference.replace("*/", "* /")
    pending_lines = "".join(f" * - {identifier}\n" for identifier in pending_functions)
    pragma_lines = "".join(
        f"{global_asm_pragma(source, identifier)}\n" for identifier in pending_functions
    )
    return (
        '#include "types.h"\n\n'
        "/*\n"
        f" * Reviewed source unit: {source}\n"
        f" * Boundary evidence: {safe_reference}\n"
        " *\n"
        " * TODO: Implement these source-unit functions:\n"
        f"{pending_lines}"
        " *\n"
        " * Unmatched members use generated GLOBAL_ASM placeholders below.\n"
        " */\n\n"
        f"{pragma_lines}"
    )


def create_source_unit_skeleton(
    source: str,
    evidence_reference: str,
    pending_functions: list[str],
) -> bool:
    """Create a reviewed unit's C workspace without replacing existing work."""

    source_path = ROOT / source
    if source_path.exists():
        if not source_path.is_file():
            raise ProjectStateError(f"source-unit path exists but is not a file: {source}")
        return False
    source_path.parent.mkdir(parents=True, exist_ok=True)
    content = source_unit_skeleton_content(source, evidence_reference, pending_functions)
    try:
        with source_path.open("x", encoding="utf-8") as output:
            output.write(content)
    except FileExistsError:
        if not source_path.is_file():
            raise ProjectStateError(f"source-unit path exists but is not a file: {source}")
        return False
    return True


def retire_library_units(args: argparse.Namespace) -> None:
    """Retire archive-backed work, preserving completed source in the library."""

    validate_rom_config(load_json(ROMS_FILE))
    validate_code_ranges(load_json(OVERLAYS_FILE))
    evidence_reference = args.evidence_reference
    functions_data = load_json(FUNCTIONS_FILE)
    source_units_data = load_json(SOURCE_UNITS_FILE)
    functions = validate_functions(functions_data)
    validate_deferred_candidate_sources(functions)
    requested_sources = set(getattr(args, "sources", None) or [])
    preserved_source = getattr(args, "preserved_source", None)
    if preserved_source and len(requested_sources) != 1:
        raise ProjectStateError("--preserved-source requires exactly one --source")
    replacements = frozenset(
        unit["source"]
        for unit in source_units_data.get("source_units", [])
        if unit.get("boundary_evidence", {}).get("us", {}).get("reference")
        == evidence_reference
        and (not requested_sources or unit["source"] in requested_sources)
    )
    if requested_sources - replacements:
        raise ProjectStateError(
            "requested sources do not use this boundary evidence: "
            + ", ".join(sorted(requested_sources - replacements))
        )
    units = validate_source_units(
        source_units_data, functions, archive_replacements=replacements
    )
    selected = [
        unit
        for unit in units
        if unit["source"] in replacements
    ]
    if not selected:
        raise ProjectStateError(
            f"no source units use boundary evidence {evidence_reference}"
        )

    functions_by_id = {entry["symbol"]: entry for entry in functions}
    source_contents: dict[Path, bytes] = {}
    retired_ids: set[str] = set()

    for unit in selected:
        source = unit["source"]
        members = [functions_by_id[identifier] for identifier in unit["functions"]]
        overlays = {member.get("overlay", "main") for member in members}
        if len(overlays) != 1:
            raise ProjectStateError(f"{source} cannot span multiple overlays")
        overlay = overlays.pop()
        working = mapped_subsegments("us", overlay)
        reference = reference_subsegments("us", overlay)
        working_by_offset = {offset: (kind, name) for offset, kind, name in working}
        reference_by_offset = {offset: (kind, name) for offset, kind, name in reference}
        working_offsets = sorted(working_by_offset)
        if preserved_source:
            if unit.get("integration") not in {"raw_asm", "mixed"} or not all(
                is_complete(member) and member.get("deferred") is None
                for member in members
            ):
                raise ProjectStateError(f"{source} must have every active function matched before source preservation")
        else:
            if unit.get("integration") not in {"raw_asm", "mixed"} or any(
                unit["regions"][region]["state"] != "raw_asm"
                for region in TARGET_REGIONS
            ):
                raise ProjectStateError(f"{source} is not an untouched raw-ASM source unit")
            if any(
                member.get("deferred") is not None
                or any(
                    member["regions"][region]["state"] != "raw_asm"
                    for region in TARGET_REGIONS
                )
                for member in members
            ):
                raise ProjectStateError(f"{source} has active or completed function work")

        start = int(unit["regions"]["us"]["start"], 0)
        end = int(unit["regions"]["us"]["end"], 0)
        mapped_kind, mapped_name = working_by_offset.get(start, (None, None))
        if mapped_kind != "lib" or not mapped_name or mapped_name.split(",")[-1].strip() != ".text":
            raise ProjectStateError(
                f"{source} is not library-backed at working-map offset 0x{start:X}"
            )
        following = next((offset for offset in working_offsets if offset > start), None)
        if following != end:
            raise ProjectStateError(
                f"{source} library map does not own exact range 0x{start:X}:0x{end:X}"
            )
        if reference_by_offset.get(start, (None, None))[0] != "asm":
            raise ProjectStateError(
                f"{source} raw reference is not ASM at offset 0x{start:X}"
            )

        source_path = ROOT / source
        if not source_path.is_file():
            raise ProjectStateError(f"raw-ASM source-unit skeleton is missing: {source}")
        content = source_path.read_bytes()
        if preserved_source:
            archive_path = ROOT / preserved_source
            archive, member, _ = [part.strip() for part in mapped_name.split(",")]
            if (
                not source.startswith("src/libultrare/")
                or preserved_source != f"lib/libultrare/{source}"
                or archive != "libultrare"
                or member != source_path.stem
                or source_path.is_symlink()
                or archive_path.is_symlink()
                or not source_path.resolve().is_relative_to(ROOT.resolve() / "src/libultrare")
                or not archive_path.resolve().is_relative_to(ROOT.resolve() / "lib/libultrare")
            ):
                raise ProjectStateError("preserved source must use the matching Rare archive source path and member")
            if not archive_path.is_file() or archive_path.read_bytes() != content:
                raise ProjectStateError("preserved library source must be a byte-identical copy")
            if b"GLOBAL_ASM" in content:
                raise ProjectStateError("preserved matched library source must not contain GLOBAL_ASM")
        else:
            expected = source_unit_skeleton_content(
                source,
                evidence_reference,
                unit["functions"],
            )
            if content != expected.encode("utf-8"):
                raise ProjectStateError(
                    f"refusing to remove modified source-unit skeleton: {source}"
                )
        source_contents[source_path] = content
        retired_ids.update(unit["functions"])

    updated_functions = {
        **functions_data,
        "functions": [
            entry for entry in functions if entry["symbol"] not in retired_ids
        ],
    }
    selected_sources = {unit["source"] for unit in selected}
    updated_units = {
        **source_units_data,
        "source_units": [
            unit for unit in units if unit["source"] not in selected_sources
        ],
    }
    validated_functions = validate_functions(updated_functions)
    validate_source_units(updated_units, validated_functions)

    original_files = {
        path: path.read_bytes() if path.is_file() else None
        for path in (FUNCTIONS_FILE, SOURCE_UNITS_FILE, SUMMARY_FILE, *BADGE_FILES.values(), DOCUMENT_FILE)
    }
    try:
        write_json(FUNCTIONS_FILE, updated_functions)
        write_json(SOURCE_UNITS_FILE, updated_units)
        render_progress(validated_functions)
        for source_path in source_contents:
            source_path.unlink()
    except Exception:
        # The map already names an archive. Rendering the restored old inventory
        # would reject its overlap with that map, masking the original failure.
        for path, original in original_files.items():
            if original is None:
                path.unlink(missing_ok=True)
            else:
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(original)
        for source_path, content in source_contents.items():
            if not source_path.exists():
                source_path.parent.mkdir(parents=True, exist_ok=True)
                source_path.write_bytes(content)
        raise

    print(
        f"Retired {len(selected)} library-backed source units and "
        f"{len(retired_ids)} function work items; "
        f"evidence={evidence_reference}"
    )


def withdraw_source_unit(args: argparse.Namespace) -> None:
    """Withdraw a game boundary while preserving its untouched function work."""
    functions = validate_functions(load_json(FUNCTIONS_FILE))
    data = load_json(SOURCE_UNITS_FILE)
    units = validate_source_units(data, functions)
    unit = next((unit for unit in units if unit["source"] == args.source), None)
    if unit is None:
        raise ProjectStateError(f"source unit not registered: {args.source}")
    members = [entry for entry in functions if entry["symbol"] in unit["functions"]]
    if unit.get("integration") not in {"raw_asm", "mixed"} or any(
        entry.get("overlay", "main") != "game"
        or entry.get("deferred") is not None
        or any(record["state"] != "raw_asm" for record in entry["regions"].values())
        for entry in members
    ):
        raise ProjectStateError("withdrawal requires untouched raw-ASM game functions")
    source_path = ROOT / args.source
    expected = source_unit_skeleton_content(
        args.source, unit["boundary_evidence"]["us"]["reference"], unit["functions"]
    )
    if source_path.is_symlink() or source_path.read_text() != expected:
        raise ProjectStateError("refusing to withdraw a modified source skeleton")
    map_path = ROOT / "config/game/us.yaml"
    map_text = map_path.read_text()
    start = int(unit["regions"]["us"]["start"], 0)
    end = int(unit["regions"]["us"]["end"], 0)
    entries = mapped_subsegments("us", "game")
    position = next(i for i, entry in enumerate(entries) if entry[0] == start)
    if position + 1 >= len(entries) or entries[position + 1][0] != end:
        raise ProjectStateError("withdrawal requires the exact mapped source interval")
    kind, name = entries[position][1:]
    mapped_source = args.source.removeprefix("src/").removesuffix(".c")
    if (kind, name) not in {("c", mapped_source), ("asm", None)}:
        raise ProjectStateError("working map does not name the source being withdrawn")
    if kind == "c":
        pattern = rf"(?m)^(\s*- \[0x{start:X}, )c, {re.escape(mapped_source)}(\]\s*)$"
        map_text, count = re.subn(pattern, r"\1asm\2", map_text)
        if count != 1:
            raise ProjectStateError("could not identify one exact source mapping")
    updated = {**data, "source_units": [item for item in units if item is not unit]}
    paths = (SOURCE_UNITS_FILE, map_path, source_path, SUMMARY_FILE, DOCUMENT_FILE, *BADGE_FILES.values())
    originals = {path: path.read_bytes() if path.exists() else None for path in paths}
    try:
        write_json(SOURCE_UNITS_FILE, updated)
        map_path.write_text(map_text)
        source_path.write_text(expected.replace("Reviewed source unit:", "Raw function collection (boundary withdrawn):"))
        validate_source_units(updated, functions)
        render_progress(functions)
    except Exception:
        for path, original in originals.items():
            if original is None:
                path.unlink(missing_ok=True)
            else:
                path.write_bytes(original)
        raise
    print(f"Withdrew boundary {args.source}; retained {len(members)} raw function work items.")


def register_source_unit(args: argparse.Namespace) -> None:
    """Register one separately reviewed US source/object boundary."""

    overlay = getattr(args, "overlay", "game")
    source = args.source
    validate_registration_source(source, overlay)
    try:
        start = int(args.us_start, 0)
        end = int(args.us_end, 0)
    except ValueError as error:
        raise ProjectStateError("--us-start and --us-end must be hexadecimal offsets") from error
    if start < 0 or end <= start or start % 0x10 or end % 0x10:
        raise ProjectStateError("reviewed source-unit boundaries must be a non-empty 16-byte-aligned range")

    functions_data = load_json(FUNCTIONS_FILE)
    source_units_data = load_json(SOURCE_UNITS_FILE)
    functions = validate_functions(functions_data)
    units = validate_source_units(source_units_data, functions)
    if any(unit["source"] == source for unit in units):
        raise ProjectStateError(f"source unit already registered: {source}")

    entries = mapped_subsegments("us", overlay)
    offsets = {offset for offset, _, _ in entries}
    _, code_end = validate_code_ranges(load_json(OVERLAYS_FILE))[overlay]["us"]
    if start not in offsets or (end != code_end and end not in offsets):
        map_directory = "profiles" if overlay == "main" else "game"
        raise ProjectStateError(
            f"reviewed range 0x{start:X}:0x{end:X} must already exist in "
            f"config/{map_directory}/us.yaml"
        )

    functions_in_range = [
        function
        for function in parse_assembly_functions("us", overlay)
        if start <= function.offset < end
    ]
    explicit_ids = list(getattr(args, "functions", None) or [])
    register_members = bool(getattr(args, "register_members", False))
    if register_members == bool(explicit_ids):
        raise ProjectStateError(
            "use exactly one of repeated --function values or --register-members"
        )

    assigned_to_unit = {
        identifier: unit["source"]
        for unit in units
        for identifier in unit["functions"]
    }
    updated_function_entries = list(functions)
    newly_registered: list[str] = []
    reassigned: list[str] = []

    if register_members:
        by_us_symbol = {
            entry["regions"]["us"]["symbol"]: entry
            for entry in updated_function_entries
            if "us" in entry["regions"]
        }
        identifiers = {entry["symbol"] for entry in updated_function_entries}
        replacements: dict[str, dict[str, Any]] = {}
        for function in functions_in_range:
            member = by_us_symbol.get(function.symbol)
            if member is None:
                if function.symbol in identifiers:
                    raise ProjectStateError(
                        f"cannot use {function.symbol} as a work-item ID because it is already registered"
                    )
                member = {
                    "overlay": overlay,
                    "source": source,
                    "symbol": function.symbol,
                    "regions": {
                        "us": {
                            "state": "raw_asm",
                            "symbol": function.symbol,
                            "vram": f"0x{function.vram:X}",
                            "size_bytes": function.end - function.offset,
                        }
                    },
                }
                updated_function_entries.append(member)
                identifiers.add(function.symbol)
                newly_registered.append(function.symbol)
                continue

            identifier = member["symbol"]
            if member.get("overlay", "main") != overlay:
                raise ProjectStateError(f"{identifier} is not a {overlay} function")
            owner = assigned_to_unit.get(identifier)
            if owner is not None:
                raise ProjectStateError(f"{identifier} is already assigned to source unit {owner}")
            if member.get("source") != source:
                replacements[identifier] = {**member, "source": source}
                reassigned.append(identifier)

        if replacements:
            updated_function_entries = [
                replacements.get(entry["symbol"], entry) for entry in updated_function_entries
            ]
        requested_ids = [
            next(
                entry["symbol"]
                for entry in updated_function_entries
                if entry["regions"]["us"]["symbol"] == function.symbol
            )
            for function in functions_in_range
        ]
    else:
        requested_ids = explicit_ids

    if len(set(requested_ids)) != len(requested_ids):
        raise ProjectStateError("--function values must be unique")
    functions_by_id = {entry["symbol"]: entry for entry in updated_function_entries}
    unknown = [identifier for identifier in requested_ids if identifier not in functions_by_id]
    if unknown:
        raise ProjectStateError(f"unknown work-item IDs: {', '.join(unknown)}")
    members = [functions_by_id[identifier] for identifier in requested_ids]
    if any(member.get("overlay", "main") != overlay for member in members):
        raise ProjectStateError(
            f"every source-unit member must use the {overlay} overlay"
        )
    if any(member.get("source") != source for member in members):
        raise ProjectStateError("every source-unit member must use the same --source path")
    already_assigned = {
        identifier for identifier in requested_ids if identifier in assigned_to_unit
    }
    if already_assigned:
        raise ProjectStateError(
            f"functions already assigned to a source unit: {', '.join(sorted(already_assigned))}"
        )

    regional_to_id = {
        entry["regions"]["us"]["symbol"]: entry["symbol"]
        for entry in updated_function_entries
        if "us" in entry["regions"]
    }
    missing_registration = [
        function.symbol for function in functions_in_range if function.symbol not in regional_to_id
    ]
    if missing_registration:
        raise ProjectStateError(
            "reviewed source unit still contains unregistered functions: "
            + ", ".join(missing_registration)
        )
    expected_ids = [regional_to_id[function.symbol] for function in functions_in_range]
    if set(expected_ids) != set(requested_ids):
        omitted = [identifier for identifier in expected_ids if identifier not in requested_ids]
        outside = [identifier for identifier in requested_ids if identifier not in expected_ids]
        details = []
        if omitted:
            details.append("omitted: " + ", ".join(omitted))
        if outside:
            details.append("outside range: " + ", ".join(outside))
        raise ProjectStateError("source-unit membership does not match reviewed range (" + "; ".join(details) + ")")

    state = source_unit_work_state(members)
    source_unit = {
        "source": source,
        "functions": expected_ids,
        "integration": "raw_asm",
        "boundary_evidence": {
            "us": {
                "kind": args.evidence_kind,
                "reference": args.evidence_reference,
                "reviewed": True,
            }
        },
        "regions": {
            "us": {
                "state": state,
                "start": f"0x{start:X}",
                "end": f"0x{end:X}",
            }
        },
    }
    updated_units = {**source_units_data, "source_units": [*units, source_unit]}
    updated_functions = {**functions_data, "functions": updated_function_entries}
    validated_functions = validate_functions(updated_functions)
    validate_source_units(updated_units, validated_functions)
    pending_functions = [member["symbol"] for member in members if not is_complete(member)]
    created_skeleton = create_source_unit_skeleton(
        source,
        args.evidence_reference,
        pending_functions,
    )
    try:
        if register_members:
            write_json(FUNCTIONS_FILE, updated_functions)
        write_json(SOURCE_UNITS_FILE, updated_units)
        render_progress(validated_functions)
    except Exception:
        if created_skeleton:
            (ROOT / source).unlink(missing_ok=True)
        raise
    registration_detail = ""
    if register_members:
        registration_detail = (
            f"; registered={len(newly_registered)}; reassigned={len(reassigned)}"
        )
    skeleton_detail = "created" if created_skeleton else "preserved"
    print(
        f"Registered reviewed source unit {source}: us=0x{start:X}:0x{end:X}; "
        f"functions={len(expected_ids)}; evidence={args.evidence_kind}; "
        f"skeleton={skeleton_detail}{registration_detail}"
    )


def rom_info(path_argument: str) -> None:
    path = Path(path_argument).expanduser().resolve()
    if not path.is_file():
        raise ProjectStateError(f"ROM does not exist or is not a file: {path}")
    print(json.dumps({"path": str(path), "size_bytes": path.stat().st_size, "sha1": file_sha1(path)}, indent=2))


def setup(args: argparse.Namespace) -> None:
    roms, _ = validate_project()
    supplied = {"us": Path(args.us).expanduser().resolve()}
    if args.eu:
        supplied["eu"] = Path(args.eu).expanduser().resolve()
    local: dict[str, Any] = {"schema_version": 1, "profiles": {}}
    for region, path in supplied.items():
        if not path.is_file():
            raise ProjectStateError(f"{REGION_NAMES[region]} ROM does not exist: {path}")
        profile = roms["profiles"][region]
        expected = profile["sha1"]
        if expected is None:
            raise ProjectStateError(
                f"{REGION_NAMES[region]} is not pinned yet. Run ./conker rom-info on the maintainer ROM, "
                "record the reviewed SHA-1 in config/roms.json, then retry setup."
            )
        actual = file_sha1(path)
        if actual != expected:
            raise ProjectStateError(
                f"{REGION_NAMES[region]} SHA-1 mismatch: expected {expected}, got {actual}"
            )
        if path.stat().st_size != profile["size_bytes"]:
            raise ProjectStateError(
                f"{REGION_NAMES[region]} size mismatch: expected {profile['size_bytes']}, got {path.stat().st_size}"
            )
        link_path = ROM_LINKS[region]
        link_target = Path(os.path.relpath(path, start=link_path.parent))
        if link_path.exists() or link_path.is_symlink():
            if link_path.resolve() != path:
                raise ProjectStateError(
                    f"{link_path.relative_to(ROOT)} already points to a different ROM; "
                    "remove it or rerun setup with that ROM"
                )
            if link_path.is_symlink() and link_path.readlink() != link_target:
                link_path.unlink()
                link_path.symlink_to(link_target)
        else:
            link_path.parent.mkdir(parents=True, exist_ok=True)
            link_path.symlink_to(link_target)
        local["profiles"][region] = {
            "path": str(link_path.relative_to(ROOT)),
            "sha1": actual,
        }
    write_json(LOCAL_SETUP_FILE, local)
    if "eu" in supplied:
        print("US ROM and optional future EU/PAL ROM were validated and saved in .conker/roms.json.")
    else:
        print("US ROM was validated and saved in .conker/roms.json.")
    print("Ignored project-local ROM paths are available under roms/ for Docker builds.")


def setup_check(args: argparse.Namespace) -> None:
    roms, _ = validate_project()
    local = load_json(LOCAL_SETUP_FILE)
    profiles = local.get("profiles", {})
    regions = TARGET_REGIONS if args.all else (args.profile,)
    for region in regions:
        local_profile = profiles.get(region, {})
        path = Path(local_profile.get("path", ""))
        if not path.is_absolute():
            path = ROOT / path
        if not path.is_file():
            raise ProjectStateError("US ROM path is not configured; run ./conker setup --us <path>")
        if local_profile.get("sha1") != roms["profiles"][region]["sha1"]:
            raise ProjectStateError(f"{REGION_NAMES[region]} local setup is stale; rerun ./conker setup")


def active_function_sizes(
    functions: list[dict[str, Any]], source_units: list[dict[str, Any]], region: str = "us"
) -> dict[str, int]:
    """Return exact function byte spans for one active region."""

    functions_by_symbol = {entry["symbol"]: entry for entry in functions}
    sizes: dict[str, int] = {}
    for unit in source_units:
        if region not in unit["regions"]:
            continue
        members = sorted(
            (functions_by_symbol[symbol] for symbol in unit["functions"]),
            key=lambda entry: int(entry["regions"][region]["vram"], 0),
        )
        unit_region = unit["regions"][region]
        unit_size = int(unit_region["end"], 0) - int(unit_region["start"], 0)
        first_vram = int(members[0]["regions"][region]["vram"], 0)
        unit_end_vram = first_vram + unit_size
        for index, entry in enumerate(members):
            start_vram = int(entry["regions"][region]["vram"], 0)
            end_vram = (
                int(members[index + 1]["regions"][region]["vram"], 0)
                if index + 1 < len(members)
                else unit_end_vram
            )
            size_bytes = end_vram - start_vram
            if size_bytes <= 0:
                raise ProjectStateError(
                    f"cannot derive a positive size for {entry['symbol']}/{region}"
                )
            recorded_size = entry["regions"][region].get("size_bytes")
            sizes[entry["symbol"]] = recorded_size or size_bytes

    for entry in functions:
        region_record = entry["regions"].get(region)
        if region_record is None:
            continue
        recorded_size = region_record.get("size_bytes")
        if recorded_size is not None:
            sizes.setdefault(entry["symbol"], recorded_size)
    return sizes


def git_path_dirty(source: str) -> str:
    """Return yes/no for a repository path, or unknown outside a Git checkout."""

    try:
        result = subprocess.run(
            ["git", "status", "--porcelain", "--", source],
            cwd=ROOT,
            check=False,
            capture_output=True,
            text=True,
        )
    except OSError:
        return "unknown"
    if result.returncode:
        return "unknown"
    return "yes" if result.stdout.strip() else "no"


def next_source_unit_guidance(
    entry: dict[str, Any],
    functions: list[dict[str, Any]],
    source_units: list[dict[str, Any]],
) -> tuple[str, str]:
    """Return the integration state and required action after this item matches."""

    source = entry.get("source")
    unit = next(
        (
            candidate
            for candidate in source_units
            if candidate["source"] == source and entry["symbol"] in candidate["functions"]
        ),
        None,
    )
    if unit is None:
        return "not-reviewed", "stop"

    integration = unit["integration"]
    functions_by_symbol = {function["symbol"]: function for function in functions}
    unfinished_after_match = [
        symbol
        for symbol in unit["functions"]
        if symbol != entry["symbol"] and not is_complete(functions_by_symbol[symbol])
    ]
    if integration == "raw_asm" and (
        entry.get("overlay", "main") == "game" or not unfinished_after_match
    ):
        return integration, "integrate"
    if integration == "mixed" and not unfinished_after_match:
        return integration, "integrate"
    return integration, "stop"


def raw_us_call_sites(
    entry: dict[str, Any], limit: int = 8
) -> list[tuple[Path, int, list[str]]]:
    """Return bounded direct-call snippets from the separately generated US assembly."""

    root = (
        ROOT / "reference" / "game" / "us" / "asm"
        if entry.get("overlay", "main") == "game"
        else ROOT / "reference" / "us" / "asm"
    )
    if not root.is_dir():
        return []
    symbol = entry["regions"]["us"]["symbol"]
    direct_call = re.compile(rf"\bjal\s+{re.escape(symbol)}(?:\s|$)")
    results: list[tuple[Path, int, list[str]]] = []
    for path in sorted(root.rglob("*.s")):
        try:
            lines = path.read_text(encoding="utf-8").splitlines()
        except OSError:
            continue
        for index, line in enumerate(lines):
            if not direct_call.search(line):
                continue
            snippet = lines[max(0, index - 3) : min(len(lines), index + 2)]
            results.append((path.relative_to(ROOT), index + 1, snippet))
            if len(results) == limit:
                return results
    return results


def print_next_details(
    entry: dict[str, Any],
    size_bytes: int,
    functions: list[dict[str, Any]],
    source_units: list[dict[str, Any]],
) -> None:
    """Print bounded local context for one work item without network lookups."""

    identifier = entry["symbol"]
    source = entry.get("source")
    region = entry["regions"]["us"]
    print(f"work-item: {identifier}")
    print(f"overlay: {entry.get('overlay', 'main')}")
    print(f"source: {source or 'not assigned'}")
    print(f"allowed-edit: {source or 'none'}")
    print(f"target-file-dirty: {git_path_dirty(source) if source else 'unknown'}")
    source_unit_state, post_match_action = next_source_unit_guidance(
        entry, functions, source_units
    )
    print(f"source-unit-state: {source_unit_state}")
    print(f"post-match-action: {post_match_action}")
    print(f"us-symbol: {region['symbol']}")
    print(f"us-vram: {region['vram']}")
    print(f"size: {size_bytes} bytes")
    issue = entry.get("issue")
    print(f"issue: {issue or 'none recorded; do not query GitHub'}")
    print(f"standalone-starter: ./conker m2c {identifier} > /tmp/{identifier}.c")
    print(f"finish: ./conker finish {identifier}")

    call_sites = raw_us_call_sites(entry)
    if call_sites:
        print("raw-us-call-sites:")
        for path, line_number, snippet in call_sites:
            print(f"  {path}:{line_number}")
            for line in snippet:
                print(f"    {line}")
    else:
        print("raw-us-call-sites: none found")

    if not source:
        return
    source_path = ROOT / source
    assembly_relative = nonmatching_asm_path(source, region["symbol"])
    assembly_path = ROOT / assembly_relative
    print(f"assembly: {assembly_relative}")
    if assembly_path.is_file():
        assembly_lines = assembly_path.read_text(encoding="utf-8").splitlines()
        print("assembly-body:")
        for line in assembly_lines[:80]:
            print(f"  {line}")
        if len(assembly_lines) > 80:
            print(f"  ... ({len(assembly_lines) - 80} more lines)")
    else:
        print("assembly-body: not generated; run the starter command")

    if not source_path.is_file():
        print("source-context: source file is not present")
        return
    source_lines = source_path.read_text(encoding="utf-8").splitlines()
    pragma = global_asm_pragma(source, identifier)
    target_index = next(
        (index for index, line in enumerate(source_lines) if line.strip() == pragma),
        None,
    )
    declaration_end = next(
        (
            index
            for index, line in enumerate(source_lines)
            if "Reviewed source unit:" in line
        ),
        min(len(source_lines), 40),
    )
    selected = set(range(min(declaration_end, 40)))
    if target_index is not None:
        selected.update(
            range(max(0, target_index - 2), min(len(source_lines), target_index + 3))
        )
        print(f"source-line: {target_index + 1}")
    else:
        print("source-line: target pragma not found")
    print("source-context:")
    previous = -2
    for index in sorted(selected):
        if index > previous + 1:
            print("  ...")
        print(f"  {index + 1:>5}  {source_lines[index]}")
        previous = index


def next_function(args: argparse.Namespace | None = None) -> None:
    one = bool(args and args.one)
    details = bool(args and args.details)
    id_only = bool(args and getattr(args, "id_only", False))
    if details and not one:
        raise ProjectStateError("--details requires --one to keep output bounded")
    if id_only and not one:
        raise ProjectStateError("--id-only requires --one")
    if id_only and details:
        raise ProjectStateError("--id-only and --details cannot be combined")
    _, functions = validate_project()
    source_units = validate_source_units(load_json(SOURCE_UNITS_FILE), functions)
    sizes = active_function_sizes(functions, source_units)
    available = [
        entry
        for entry in functions
        if not is_complete(entry)
        and all(entry["regions"][region]["state"] == "raw_asm" for region in TARGET_REGIONS)
        and not entry.get("issue")
        and not entry.get("deferred")
    ]
    if not available:
        if id_only:
            raise ProjectStateError("no unclaimed raw-ASM functions are registered yet")
        print("No unclaimed raw-ASM functions are registered yet.")
        return
    missing_sizes = [entry["symbol"] for entry in available if entry["symbol"] not in sizes]
    if missing_sizes:
        raise ProjectStateError(
            "cannot determine function size for: "
            + ", ".join(sorted(missing_sizes))
            + "; register a reviewed source unit or record size_bytes during function registration"
        )
    available.sort(key=lambda entry: (sizes[entry["symbol"]], entry["symbol"]))
    if one:
        available = available[:1]
    if id_only:
        print(available[0]["symbol"])
        return
    if details:
        print_next_details(
            available[0], sizes[available[0]["symbol"]], functions, source_units
        )
        return
    print("# Start any listed work item with:")
    print("# ./conker m2c <work-item-id> > /tmp/<work-item-id>.c")
    for entry in available:
        print(
            f"{entry['symbol']} ({entry.get('source', 'source not assigned')}; "
            f"us={entry['regions']['us']['symbol']}; size={sizes[entry['symbol']]} bytes)"
        )


def batch_plan(symbols: list[str]) -> None:
    """Validate a matched work-item batch and print the required build overlays."""

    _, functions = validate_project()
    functions_by_symbol = {entry["symbol"]: entry for entry in functions}
    unknown = [symbol for symbol in symbols if symbol not in functions_by_symbol]
    if unknown:
        raise ProjectStateError(f"unknown work-item ID(s): {', '.join(unknown)}")
    unfinished = [
        symbol for symbol in symbols if not is_complete(functions_by_symbol[symbol])
    ]
    if unfinished:
        raise ProjectStateError(
            "verify-batch requires matched active work items: " + ", ".join(unfinished)
        )
    overlays = {
        functions_by_symbol[symbol].get("overlay", "main") for symbol in symbols
    }
    print(" ".join(overlay for overlay in ("main", "game") if overlay in overlays))


def batch_fingerprint() -> str:
    """Hash current build inputs so an unchanged integration failure is not rerun."""

    paths: list[Path] = []
    for relative in BATCH_FINGERPRINT_INPUTS:
        candidate = ROOT / relative
        if candidate.is_file():
            paths.append(candidate)
        elif candidate.is_dir():
            paths.extend(
                path
                for path in candidate.rglob("*")
                if path.is_file()
                and "__pycache__" not in path.parts
                and path.suffix != ".pyc"
            )
    digest = hashlib.sha256()
    for path in sorted(paths):
        digest.update(str(path.relative_to(ROOT)).encode("utf-8"))
        digest.update(b"\0")
        digest.update(path.read_bytes())
        digest.update(b"\0")
    return digest.hexdigest()


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(add_help=False)
    subparsers = parser.add_subparsers(dest="command", required=True)
    subparsers.add_parser("validate")
    subparsers.add_parser("normalize-source-headers")
    rom_info_parser = subparsers.add_parser("rom-info")
    rom_info_parser.add_argument("path")
    setup_parser = subparsers.add_parser("setup")
    setup_parser.add_argument("--us", required=True)
    setup_parser.add_argument("--eu", help="optional future EU/PAL ROM; not required by active work")
    setup_check_parser = subparsers.add_parser("setup-check")
    setup_check_parser.add_argument("--profile", choices=TARGET_REGIONS)
    setup_check_parser.add_argument("--all", action="store_true")
    progress_parser = subparsers.add_parser("progress")
    progress_parser.add_argument("--show", action="store_true")
    progress_parser.add_argument("--render", action="store_true")
    progress_parser.add_argument("--check", action="store_true")
    mark_matched_parser = subparsers.add_parser("mark-matched")
    mark_matched_parser.add_argument("--profile", choices=TARGET_REGIONS, required=True)
    mark_matched_parser.add_argument("symbol")
    defer_parser = subparsers.add_parser("defer")
    defer_parser.add_argument("symbol")
    defer_parser.add_argument("--reason", required=True)
    defer_parser.add_argument("--score", required=True, type=int)
    resume_parser = subparsers.add_parser("resume")
    resume_parser.add_argument("symbol")
    next_parser = subparsers.add_parser("next")
    next_parser.add_argument(
        "--one",
        action="store_true",
        help="print only the first available work item",
    )
    next_parser.add_argument(
        "--details",
        action="store_true",
        help="with --one, print bounded local source and assembly context",
    )
    next_parser.add_argument(
        "--id-only",
        action="store_true",
        help=argparse.SUPPRESS,
    )
    batch_plan_parser = subparsers.add_parser("batch-plan")
    batch_plan_parser.add_argument("symbols", nargs="+")
    subparsers.add_parser("batch-fingerprint")
    subparsers.add_parser("game-index")
    register_game_parser = subparsers.add_parser("register-game")
    register_game_parser.add_argument("--id", dest="identifier", required=True)
    register_game_parser.add_argument("--us", required=True)
    register_game_parser.add_argument("--source", required=True)
    register_main_parser = subparsers.add_parser("register-main")
    register_main_parser.add_argument("--id", dest="identifier", required=True)
    register_main_parser.add_argument("--us", required=True)
    register_main_parser.add_argument("--source", required=True)
    register_unit_parser = subparsers.add_parser("register-source-unit")
    register_unit_parser.add_argument(
        "--overlay", choices=sorted(OVERLAYS), default="game"
    )
    register_unit_parser.add_argument("--source", required=True)
    membership = register_unit_parser.add_mutually_exclusive_group(required=True)
    membership.add_argument("--function", dest="functions", action="append")
    membership.add_argument(
        "--register-members",
        action="store_true",
        help="register every recovered US function in the reviewed range",
    )
    register_unit_parser.add_argument("--us-start", required=True)
    register_unit_parser.add_argument("--us-end", required=True)
    register_unit_parser.add_argument(
        "--evidence-kind", choices=sorted(BOUNDARY_EVIDENCE_KINDS), required=True
    )
    register_unit_parser.add_argument("--evidence-reference", required=True)
    withdraw_unit_parser = subparsers.add_parser("withdraw-source-unit")
    withdraw_unit_parser.add_argument("--source", required=True)
    retire_library_parser = subparsers.add_parser("retire-library-units")
    retire_library_parser.add_argument("--evidence-reference", required=True)
    retire_library_parser.add_argument("--source", dest="sources", action="append")
    retire_library_parser.add_argument(
        "--preserved-source",
        help="retire one fully matched Rare unit only when an identical source copy exists in its archive path",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        if args.command == "validate":
            validate_project()
            print("Project metadata is valid.")
        elif args.command == "normalize-source-headers":
            normalize_source_unit_headers()
        elif args.command == "rom-info":
            rom_info(args.path)
        elif args.command == "setup":
            setup(args)
        elif args.command == "setup-check":
            if args.all == bool(args.profile):
                raise ProjectStateError("use exactly one of --profile or --all")
            setup_check(args)
        elif args.command == "progress":
            progress(args)
        elif args.command == "mark-matched":
            mark_matched(args)
        elif args.command == "defer":
            defer_function(args)
        elif args.command == "resume":
            resume_function(args)
        elif args.command == "next":
            next_function(args)
        elif args.command == "batch-plan":
            batch_plan(args.symbols)
        elif args.command == "batch-fingerprint":
            print(batch_fingerprint())
        elif args.command == "game-index":
            game_index()
        elif args.command == "register-game":
            register_game(args)
        elif args.command == "register-main":
            register_main(args)
        elif args.command == "register-source-unit":
            register_source_unit(args)
        elif args.command == "withdraw-source-unit":
            withdraw_source_unit(args)
        elif args.command == "retire-library-units":
            retire_library_units(args)
    except ProjectStateError as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
