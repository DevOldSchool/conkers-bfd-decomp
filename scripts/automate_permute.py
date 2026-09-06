#!/usr/bin/env python3
"""Try bounded source-shape permutations for deferred register-only candidates."""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

import project_state


ROOT = Path(__file__).resolve().parent.parent
CURRENT_PATTERN = re.compile(r"(?m)^\S+: CURRENT \((?P<score>\d+)\)$")
COUNT_PATTERN = re.compile(
    r"(?m)^(?P<category>register-only|operand-or-constant|"
    r"opcode-or-control-flow|missing-or-extra): (?P<count>\d+)$"
)
DIFF_CATEGORIES = (
    "register-only",
    "operand-or-constant",
    "opcode-or-control-flow",
    "missing-or-extra",
)


class AutomationError(RuntimeError):
    """An unsafe or inconsistent automation state."""


@dataclass(frozen=True)
class Candidate:
    identifier: str
    source: str
    current_score: int | None


@dataclass(frozen=True)
class Diagnosis:
    current_score: int
    counts: dict[str, int]

    @property
    def is_register_only(self) -> bool:
        return self.current_score > 0 and self.counts["register-only"] > 0 and all(
            self.counts[category] == 0
            for category in DIFF_CATEGORIES
            if category != "register-only"
        )


def positive_integer(value: str) -> int:
    parsed = int(value)
    if parsed < 1:
        raise argparse.ArgumentTypeError("must be at least 1")
    return parsed


def permutation_budget(value: str) -> int:
    parsed = positive_integer(value)
    if parsed > 5000:
        raise argparse.ArgumentTypeError("must be at most 5000")
    return parsed


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
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
        help="maximum deferred candidates to diagnose (default: 10)",
    )
    parser.add_argument(
        "--budget",
        type=permutation_budget,
        default=250,
        help="maximum variants per eligible candidate (default: 250; maximum: 5000)",
    )
    return parser.parse_args()


def available_candidates() -> list[Candidate]:
    """Return deferred source-local candidates ordered by their recorded score."""

    _, functions = project_state.validate_project()
    source_units = project_state.validate_source_units(
        project_state.load_json(project_state.SOURCE_UNITS_FILE), functions
    )
    candidates: list[Candidate] = []
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
        current_score = deferred.get("current_score")
        candidates.append(
            Candidate(
                identifier=entry["symbol"],
                source=source,
                current_score=current_score if isinstance(current_score, int) else None,
            )
        )
    return sorted(
        candidates,
        key=lambda candidate: (
            candidate.current_score is None,
            candidate.current_score or 0,
            candidate.identifier,
        ),
    )


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


def parse_diagnosis(output: str) -> Diagnosis:
    score_match = CURRENT_PATTERN.search(output)
    counts = {
        match.group("category"): int(match.group("count"))
        for match in COUNT_PATTERN.finditer(output)
    }
    if score_match is None or set(counts) != set(DIFF_CATEGORIES):
        raise AutomationError("diagnose-diff returned incomplete classification evidence")
    return Diagnosis(int(score_match.group("score")), counts)


def entry_is_complete(identifier: str) -> bool:
    inventory = project_state.load_json(project_state.FUNCTIONS_FILE)
    entry = next(
        (item for item in inventory["functions"] if item["symbol"] == identifier),
        None,
    )
    return bool(entry and project_state.is_complete(entry))


def try_candidate(candidate: Candidate, budget: int) -> bool:
    source_path = ROOT / candidate.source
    if not source_path.is_file():
        print(f"SKIP {candidate.identifier}: source file is missing")
        return False
    original = source_path.read_bytes()

    diagnose_status, diagnose_output = run_command(
        [str(ROOT / "conker"), "diagnose-diff", candidate.identifier]
    )
    if diagnose_status == 2:
        print(f"SKIP {candidate.identifier}: preserved candidate does not compile")
        return False
    if diagnose_status:
        raise AutomationError(
            f"diagnose-diff failed for {candidate.identifier} with exit {diagnose_status}"
        )
    diagnosis = parse_diagnosis(diagnose_output)
    if not diagnosis.is_register_only:
        print(
            f"SKIP {candidate.identifier}: CURRENT ({diagnosis.current_score}) is not "
            "register-allocation-only"
        )
        return False

    print(
        f"TRY {candidate.identifier}: {diagnosis.counts['register-only']} register-only "
        f"row(s), budget {budget}"
    )
    status, output = run_command(
        [
            str(ROOT / "conker"),
            "permute",
            candidate.identifier,
            "--budget",
            str(budget),
        ]
    )
    if status == 0:
        if not entry_is_complete(candidate.identifier):
            raise AutomationError(
                f"{candidate.identifier} permute succeeded without recording a match"
            )
        print(f"MATCHED {candidate.identifier}: exact permutation and finish gate passed")
        return True

    if entry_is_complete(candidate.identifier):
        raise AutomationError(
            f"{candidate.identifier} was recorded matched, but a later gate failed; "
            "the exact source was retained for manual recovery"
        )
    if source_path.read_bytes() != original:
        source_path.write_bytes(original)
    if status == 1:
        action = next(
            (
                line.partition(":")[2].strip()
                for line in output.splitlines()
                if line.startswith("AGENT_ACTION:")
            ),
            "CONTINUE_MISMATCH",
        )
        print(f"RESTORED {candidate.identifier}: {action}")
        return False
    raise AutomationError(f"permute failed for {candidate.identifier} with exit {status}")


def main() -> int:
    args = parse_args()
    matched: list[str] = []
    attempts = 0
    try:
        candidates = available_candidates()
        if not candidates:
            print("No deferred source-local candidates are available for permutation.")
            return 0
        for candidate in candidates:
            if len(matched) >= args.limit or attempts >= args.max_attempts:
                break
            attempts += 1
            if try_candidate(candidate, args.budget):
                matched.append(candidate.identifier)
    except (AutomationError, OSError, project_state.ProjectStateError) as error:
        print(f"error: {error}", file=sys.stderr)
        print("AGENT_ACTION: BLOCKED_TOOLING")
        return 1

    if not matched:
        print(
            f"No exact matches found in {attempts} diagnosed candidate(s); "
            "all project-source edits were restored."
        )
        return 0

    print(f"Running one clean batch gate for: {' '.join(matched)}")
    status, _ = run_command([str(ROOT / "conker"), "verify-batch", *matched])
    if status:
        return status
    print(f"Automated {len(matched)} exact permutation match(es): {' '.join(matched)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
