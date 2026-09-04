#!/usr/bin/env python3
"""Try unchanged m2c function bodies and keep only exact US matches."""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

import project_state


ROOT = Path(__file__).resolve().parent.parent
DEFINITION_PATTERN = re.compile(
    r"^.*\b(?P<symbol>[A-Za-z_][A-Za-z0-9_]*)\([^;\n]*\)\s*\{",
    re.MULTILINE,
)
PLACEHOLDER_PATTERN = re.compile(r"\bM2C_[A-Za-z0-9_]+\b")


class AutomationError(RuntimeError):
    """An unsafe or inconsistent automation state."""


@dataclass(frozen=True)
class Candidate:
    identifier: str
    c_symbol: str
    source: str
    size_bytes: int


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Try m2c output verbatim for clean, source-local work items. "
            "Only exact CURRENT (0) matches are retained."
        )
    )
    parser.add_argument(
        "--limit",
        type=positive_integer,
        default=1,
        help="maximum exact matches to keep (default: 1)",
    )
    parser.add_argument(
        "--max-attempts",
        type=positive_integer,
        default=10,
        help="maximum clean candidates to inspect before stopping (default: 10)",
    )
    return parser.parse_args()


def positive_integer(value: str) -> int:
    parsed = int(value)
    if parsed < 1:
        raise argparse.ArgumentTypeError("must be at least 1")
    return parsed


def available_candidates() -> list[Candidate]:
    """Return the same size-ordered, unclaimed pool used by ``next``."""

    _, functions = project_state.validate_project()
    source_units = project_state.validate_source_units(
        project_state.load_json(project_state.SOURCE_UNITS_FILE), functions
    )
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
    missing_sizes = [
        entry["symbol"] for entry in available if entry["symbol"] not in sizes
    ]
    if missing_sizes:
        raise AutomationError(
            "cannot determine function size for: " + ", ".join(sorted(missing_sizes))
        )
    candidates: list[Candidate] = []
    for entry in available:
        source = entry.get("source")
        if not source:
            continue
        _, post_match_action = project_state.next_source_unit_guidance(
            entry, functions, source_units
        )
        if post_match_action != "stop":
            continue
        candidates.append(
            Candidate(
                entry["symbol"],
                entry["regions"]["us"]["symbol"],
                source,
                sizes[entry["symbol"]],
            )
        )
    return sorted(
        candidates, key=lambda candidate: (candidate.size_bytes, candidate.identifier)
    )


def source_dirty(source: str) -> bool:
    result = subprocess.run(
        ["git", "status", "--porcelain", "--", source],
        cwd=ROOT,
        check=False,
        capture_output=True,
        text=True,
    )
    if result.returncode:
        raise AutomationError(f"could not inspect Git state for {source}")
    return bool(result.stdout.strip())


def extract_simple_definition(starter: str, identifier: str) -> str:
    """Strip m2c's guessed declarations and return one placeholder-free definition."""

    definitions = list(DEFINITION_PATTERN.finditer(starter))
    if len(definitions) != 1 or definitions[0].group("symbol") != identifier:
        raise AutomationError(f"m2c did not emit exactly one {identifier} definition")
    definition = starter[definitions[0].start() :].strip()
    if PLACEHOLDER_PATTERN.search(definition):
        raise AutomationError("m2c body contains an M2C placeholder")
    if not definition.endswith("}"):
        raise AutomationError("m2c emitted content after the function definition")
    return definition + "\n"


def replace_target_pragma(
    original: bytes, source: str, identifier: str, definition: str
) -> bytes:
    """Replace exactly one canonical pragma while preserving the file's newline style."""

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
    """Run a public conker command, echoing and retaining its combined output."""

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


def try_candidate(candidate: Candidate) -> bool:
    source_path = ROOT / candidate.source
    if source_dirty(candidate.source):
        print(f"SKIP {candidate.identifier}: {candidate.source} already has Git changes")
        return False
    if not source_path.is_file():
        print(f"SKIP {candidate.identifier}: source file is missing")
        return False

    original = source_path.read_bytes()
    try:
        starter = generate_starter(candidate.identifier)
        definition = extract_simple_definition(starter, candidate.c_symbol)
        updated = replace_target_pragma(
            original, candidate.source, candidate.identifier, definition
        )
    except AutomationError as error:
        print(f"SKIP {candidate.identifier}: {error}")
        return False

    source_path.write_bytes(updated)
    print(
        f"TRY {candidate.identifier}: unchanged m2c body in {candidate.source} "
        f"({candidate.size_bytes} bytes)"
    )
    status, output = run_command([str(ROOT / "conker"), "finish", candidate.identifier])
    if status == 0:
        print(f"MATCHED {candidate.identifier}: exact US diff and per-function gate passed")
        return True

    if entry_is_complete(candidate.identifier):
        raise AutomationError(
            f"{candidate.identifier} was recorded matched, but a later finish gate failed; "
            "the source was retained for manual recovery"
        )
    source_path.write_bytes(original)
    action = next(
        (
            line.partition(":")[2].strip()
            for line in output.splitlines()
            if line.startswith("AGENT_ACTION:")
        ),
        f"exit {status}",
    )
    print(f"RESTORED {candidate.identifier}: {action}")
    return False


def main() -> int:
    args = parse_args()
    matched: list[str] = []
    attempts = 0
    try:
        candidates = available_candidates()
        if not candidates:
            print("No conservative source-local m2c candidates are available.")
            return 0
        for candidate in candidates:
            if len(matched) >= args.limit or attempts >= args.max_attempts:
                break
            if source_dirty(candidate.source):
                print(f"SKIP {candidate.identifier}: {candidate.source} already has Git changes")
                continue
            attempts += 1
            if try_candidate(candidate):
                matched.append(candidate.identifier)
    except (AutomationError, project_state.ProjectStateError) as error:
        print(f"error: {error}", file=sys.stderr)
        print("AGENT_ACTION: BLOCKED_TOOLING")
        return 1

    if not matched:
        print(
            f"No exact matches found in {attempts} attempted candidate(s); "
            "all edits were restored."
        )
        return 0

    print(f"Running one clean batch gate for: {' '.join(matched)}")
    status, _ = run_command([str(ROOT / "conker"), "verify-batch", *matched])
    if status:
        return status
    print(f"Automated {len(matched)} exact m2c match(es): {' '.join(matched)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
