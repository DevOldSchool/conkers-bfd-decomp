#!/usr/bin/env python3
"""Shared selection and source-transaction helpers for ASM-to-C automation."""

from __future__ import annotations

import re
import subprocess
from dataclasses import dataclass
from pathlib import Path

import project_state


ROOT = Path(__file__).resolve().parent.parent


class AutomationError(RuntimeError):
    """An unsafe or inconsistent automation state."""


@dataclass(frozen=True)
class RawCandidate:
    identifier: str
    c_symbol: str
    source: str
    size_bytes: int


@dataclass(frozen=True)
class DeferredCandidate:
    identifier: str
    source: str
    current_score: int | None


def candidate_inventory() -> tuple[list[dict], list[dict]]:
    _, functions = project_state.validate_project()
    source_units = project_state.validate_source_units(
        project_state.load_json(project_state.SOURCE_UNITS_FILE), functions
    )
    return functions, source_units


def available_raw_candidates() -> list[RawCandidate]:
    """Return size-ordered unclaimed source-local candidates."""

    functions, source_units = candidate_inventory()
    sizes = project_state.active_function_sizes(functions, source_units)
    available = [
        entry
        for entry in functions
        if not project_state.is_complete(entry)
        and not entry.get("issue")
        and not entry.get("deferred")
        and all(
            entry["regions"][region]["state"] == "raw_asm"
            for region in project_state.TARGET_REGIONS
        )
    ]
    missing_sizes = [entry["symbol"] for entry in available if entry["symbol"] not in sizes]
    if missing_sizes:
        raise AutomationError(
            "cannot determine function size for: " + ", ".join(sorted(missing_sizes))
        )
    candidates: list[RawCandidate] = []
    for entry in available:
        source = entry.get("source")
        if not isinstance(source, str) or not source:
            continue
        _, post_match_action = project_state.next_source_unit_guidance(
            entry, functions, source_units
        )
        if post_match_action != "stop":
            continue
        candidates.append(
            RawCandidate(
                entry["symbol"],
                entry["regions"]["us"]["symbol"],
                source,
                sizes[entry["symbol"]],
            )
        )
    return sorted(candidates, key=lambda item: (item.size_bytes, item.identifier))


def available_deferred_candidates() -> list[DeferredCandidate]:
    """Return deferred source-local candidates ordered by recorded score."""

    functions, source_units = candidate_inventory()
    candidates: list[DeferredCandidate] = []
    for entry in functions:
        deferred = entry.get("deferred")
        source = entry.get("source")
        if (
            project_state.is_complete(entry)
            or not isinstance(deferred, dict)
            or not isinstance(source, str)
            or not source
            or entry.get("issue")
            or not all(
                entry["regions"][region]["state"] == "raw_asm"
                for region in project_state.TARGET_REGIONS
            )
        ):
            continue
        _, post_match_action = project_state.next_source_unit_guidance(
            entry, functions, source_units
        )
        if post_match_action != "stop":
            continue
        score = deferred.get("current_score")
        candidates.append(
            DeferredCandidate(
                entry["symbol"],
                source,
                score if isinstance(score, int) else None,
            )
        )
    return sorted(
        candidates,
        key=lambda item: (
            item.current_score is None,
            item.current_score or 0,
            item.identifier,
        ),
    )


def scheduled_candidates(
    raw: list[RawCandidate], deferred: list[DeferredCandidate]
) -> list[RawCandidate | DeferredCandidate]:
    """Interleave new and preserved work so neither pool starves."""

    scheduled: list[RawCandidate | DeferredCandidate] = []
    count = max(len(raw), len(deferred))
    for index in range(count):
        if index < len(raw):
            scheduled.append(raw[index])
        if index < len(deferred):
            scheduled.append(deferred[index])
    return scheduled


def replace_target_pragma(
    original: bytes, source: str, identifier: str, definition: str
) -> bytes:
    """Replace exactly one canonical pragma while preserving newline style."""

    pragma = project_state.global_asm_pragma(source, identifier).encode("utf-8")
    pattern = re.compile(rb"(?m)^[ \t]*" + re.escape(pragma) + rb"(?P<newline>\r?\n|$)")
    matches = list(pattern.finditer(original))
    if len(matches) != 1:
        raise AutomationError(
            f"expected exactly one canonical GLOBAL_ASM pragma, found {len(matches)}"
        )
    newline = b"\r\n" if matches[0].group("newline") == b"\r\n" else b"\n"
    replacement = definition.rstrip("\n").replace("\n", newline.decode()).encode("utf-8")
    replacement += matches[0].group("newline")
    return original[: matches[0].start()] + replacement + original[matches[0].end() :]


def run_command(arguments: list[str]) -> tuple[int, str]:
    """Run a public conker command, echoing and retaining combined output."""

    process = subprocess.Popen(
        arguments,
        cwd=ROOT,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1,
    )
    assert process.stdout is not None
    lines: list[str] = []
    for line in process.stdout:
        print(line, end="")
        lines.append(line)
    return process.wait(), "".join(lines)


def generate_starter(identifier: str) -> str:
    result = subprocess.run(
        [str(ROOT / "conker"), "m2c", identifier],
        cwd=ROOT,
        check=False,
        capture_output=True,
        text=True,
    )
    if result.returncode:
        detail = result.stderr.strip() or result.stdout.strip() or "m2c failed"
        raise AutomationError(detail)
    return result.stdout


def entry_is_complete(identifier: str) -> bool:
    inventory = project_state.load_json(project_state.FUNCTIONS_FILE)
    entry = next(
        (item for item in inventory["functions"] if item["symbol"] == identifier),
        None,
    )
    return bool(entry and project_state.is_complete(entry))
