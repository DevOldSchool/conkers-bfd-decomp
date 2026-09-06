#!/usr/bin/env python3
"""Run the unified, evidence-backed ASM-to-C automation workflow."""

from __future__ import annotations

import argparse
import json
import re
import sys
from dataclasses import asdict, dataclass
from datetime import datetime, timezone
from pathlib import Path

import automation_common
import candidate_rewrites
import project_state


ROOT = Path(__file__).resolve().parent.parent
CURRENT_PATTERN = re.compile(r"CURRENT \((?P<score>\d+)\)")
DIAGNOSIS_SCORE_PATTERN = re.compile(
    r"(?m)^\S+: CURRENT \((?P<score>\d+)\)$"
)
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


@dataclass(frozen=True)
class AttemptResult:
    symbol: str
    source: str | None
    pool: str
    outcome: str
    detail: str
    score: int | None = None


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


def rewrite_budget(value: str) -> int:
    parsed = positive_integer(value)
    if parsed > 5000:
        raise argparse.ArgumentTypeError("must be at most 5000")
    return parsed


def parse_args(arguments: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    scope = parser.add_mutually_exclusive_group()
    scope.add_argument(
        "--limit",
        type=positive_integer,
        help="maximum exact matches to keep (default: 1)",
    )
    scope.add_argument(
        "--all",
        action="store_true",
        help="consider every active US function without attempt or match limits",
    )
    parser.add_argument(
        "--max-attempts",
        type=positive_integer,
        help="maximum raw/deferred candidates to inspect (default: 10)",
    )
    parser.add_argument(
        "--rewrite-budget",
        type=rewrite_budget,
        default=250,
        help="maximum source-shape variants per candidate (default: 250)",
    )
    parser.add_argument(
        "--defer-best",
        action="store_true",
        help="preserve a compiling nonzero best candidate and recorded score",
    )
    parser.add_argument(
        "--skip-final-build",
        action="store_true",
        help="skip the concluding clean verify-batch and print the required command",
    )
    parser.add_argument(
        "--report",
        type=Path,
        help="write the machine-readable coverage report to this path",
    )
    parser.add_argument(
        "--restart",
        action="store_true",
        help="with --all, ignore completed attempts in an existing report",
    )
    parsed = parser.parse_args(arguments)
    if parsed.all and parsed.max_attempts is not None:
        parser.error("--all cannot be combined with --max-attempts")
    if parsed.restart and not parsed.all:
        parser.error("--restart requires --all")
    if not parsed.all:
        parsed.limit = parsed.limit or 1
        parsed.max_attempts = parsed.max_attempts or 10
    return parsed


def score_from_output(output: str) -> int | None:
    matches = list(CURRENT_PATTERN.finditer(output))
    return int(matches[-1].group("score")) if matches else None


def parse_diagnosis(output: str) -> Diagnosis:
    score_match = DIAGNOSIS_SCORE_PATTERN.search(output)
    counts = {
        match.group("category"): int(match.group("count"))
        for match in COUNT_PATTERN.finditer(output)
    }
    if score_match is None or set(counts) != set(DIFF_CATEGORIES):
        raise automation_common.AutomationError(
            "diagnose-diff returned incomplete classification evidence"
        )
    return Diagnosis(int(score_match.group("score")), counts)


def candidate_block(prepared: candidate_rewrites.PreparedCandidate) -> str:
    declarations = "\n".join(prepared.declarations)
    return declarations + "\n\n" + prepared.definition if declarations else prepared.definition


def apply_best_function(source: Path, symbol: str, best: Path) -> None:
    content = source.read_text(encoding="utf-8")
    start, end = project_state.c_function_span(content, symbol)
    replacement = best.read_text(encoding="utf-8").rstrip("\n") + "\n"
    source.write_text(content[:start] + replacement + content[end:], encoding="utf-8")


def try_raw_candidate(
    candidate: automation_common.RawCandidate,
    *,
    budget: int,
    defer_best: bool,
) -> AttemptResult:
    source = ROOT / candidate.source
    if not source.is_file():
        detail = "source file is missing"
        print(f"SKIP {candidate.identifier}: {detail}")
        return AttemptResult(candidate.identifier, candidate.source, "raw", "skipped", detail)
    original = source.read_bytes()
    try:
        starter = automation_common.generate_starter(candidate.identifier)
        prepared = candidate_rewrites.prepare_starter(
            starter,
            candidate.c_symbol,
            original.decode("utf-8"),
            root=ROOT,
        )
        updated = automation_common.replace_target_pragma(
            original,
            candidate.source,
            candidate.identifier,
            candidate_block(prepared),
        )
    except (UnicodeDecodeError, automation_common.AutomationError, candidate_rewrites.CandidateError) as error:
        detail = str(error)
        print(f"SKIP {candidate.identifier}: {detail}")
        return AttemptResult(candidate.identifier, candidate.source, "raw", "skipped", detail)

    source.write_bytes(updated)
    evidence = f"; evidence: {'; '.join(prepared.evidence)}" if prepared.evidence else ""
    print(
        f"TRY {candidate.identifier}: sanitized m2c candidate in {candidate.source} "
        f"({candidate.size_bytes} bytes){evidence}"
    )
    finish_status, finish_output = automation_common.run_command(
        [str(ROOT / "conker"), "finish", candidate.identifier]
    )
    if finish_status == 0:
        return AttemptResult(
            candidate.identifier, candidate.source, "raw", "matched", "exact finish gate passed", 0
        )
    if automation_common.entry_is_complete(candidate.identifier):
        raise automation_common.AutomationError(
            f"{candidate.identifier} was recorded matched, but a later gate failed; "
            "the exact source was retained for manual recovery"
        )

    initial_score = score_from_output(finish_output)
    if initial_score == 0:
        source.write_bytes(original)
        detail = "focused CURRENT (0) failed the source-unit layout gate"
        print(f"RESTORED {candidate.identifier}: {detail}")
        return AttemptResult(candidate.identifier, candidate.source, "raw", "restored", detail, 0)
    if finish_status != 1 or initial_score is None:
        source.write_bytes(original)
        detail = "candidate did not compile or diff safely"
        print(f"RESTORED {candidate.identifier}: {detail}")
        return AttemptResult(candidate.identifier, candidate.source, "raw", "restored", detail)

    permutation_status, permutation_output = automation_common.run_command(
        [str(ROOT / "conker"), "permute", candidate.identifier, "--budget", str(budget)]
    )
    if permutation_status == 0:
        if not automation_common.entry_is_complete(candidate.identifier):
            raise automation_common.AutomationError(
                f"{candidate.identifier} permutation succeeded without recording a match"
            )
        return AttemptResult(
            candidate.identifier, candidate.source, "raw", "matched", "exact rewrite match passed finish", 0
        )
    if automation_common.entry_is_complete(candidate.identifier):
        raise automation_common.AutomationError(
            f"{candidate.identifier} was recorded matched, but permutation later failed"
        )
    if permutation_status != 1:
        source.write_bytes(original)
        raise automation_common.AutomationError(
            f"permutation failed for {candidate.identifier} with exit {permutation_status}"
        )

    best = ROOT / "build" / "us" / "permute" / candidate.identifier / "best.c"
    best_score = score_from_output(permutation_output)
    retained_score = best_score if best_score is not None else initial_score
    if not defer_best or not best.is_file() or best_score in (None, 0):
        source.write_bytes(original)
        detail = f"no exact match; best CURRENT ({retained_score})"
        print(f"RESTORED {candidate.identifier}: {detail}")
        return AttemptResult(
            candidate.identifier, candidate.source, "raw", "restored", detail, retained_score
        )

    apply_best_function(source, candidate.c_symbol, best)
    reason = (
        f"Unified automated m2c and bounded {budget}-variant source search; "
        f"best candidate remains CURRENT ({best_score})"
    )
    defer_status, _ = automation_common.run_command(
        [str(ROOT / "conker"), "defer", candidate.identifier, "--reason", reason]
    )
    if defer_status:
        source.write_bytes(original)
        raise automation_common.AutomationError(
            f"could not preserve {candidate.identifier} best candidate"
        )
    detail = f"best CURRENT ({best_score}) preserved"
    print(f"DEFERRED {candidate.identifier}: {detail}")
    return AttemptResult(
        candidate.identifier, candidate.source, "raw", "deferred", detail, best_score
    )


def try_deferred_candidate(
    candidate: automation_common.DeferredCandidate, *, budget: int
) -> AttemptResult:
    source = ROOT / candidate.source
    if not source.is_file():
        detail = "source file is missing"
        print(f"SKIP {candidate.identifier}: {detail}")
        return AttemptResult(
            candidate.identifier, candidate.source, "deferred", "skipped", detail
        )
    original = source.read_bytes()
    diagnose_status, diagnose_output = automation_common.run_command(
        [str(ROOT / "conker"), "diagnose-diff", candidate.identifier]
    )
    if diagnose_status == 2:
        detail = "preserved candidate does not compile"
        print(f"SKIP {candidate.identifier}: {detail}")
        return AttemptResult(
            candidate.identifier, candidate.source, "deferred", "skipped", detail
        )
    if diagnose_status:
        raise automation_common.AutomationError(
            f"diagnose-diff failed for {candidate.identifier} with exit {diagnose_status}"
        )
    diagnosis = parse_diagnosis(diagnose_output)
    if not diagnosis.is_register_only:
        detail = f"CURRENT ({diagnosis.current_score}) is not register-allocation-only"
        print(f"SKIP {candidate.identifier}: {detail}")
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "deferred",
            "skipped",
            detail,
            diagnosis.current_score,
        )

    print(
        f"TRY {candidate.identifier}: {diagnosis.counts['register-only']} register-only "
        f"row(s), budget {budget}"
    )
    status, output = automation_common.run_command(
        [str(ROOT / "conker"), "permute", candidate.identifier, "--budget", str(budget)]
    )
    if status == 0:
        if not automation_common.entry_is_complete(candidate.identifier):
            raise automation_common.AutomationError(
                f"{candidate.identifier} permute succeeded without recording a match"
            )
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "deferred",
            "matched",
            "exact permutation and finish gate passed",
            0,
        )
    if automation_common.entry_is_complete(candidate.identifier):
        raise automation_common.AutomationError(
            f"{candidate.identifier} was recorded matched, but a later gate failed; "
            "the exact source was retained for manual recovery"
        )
    if status == 1:
        if source.read_bytes() != original:
            source.write_bytes(original)
        best = ROOT / "build" / "us" / "permute" / candidate.identifier / "best.c"
        best_score = score_from_output(output)
        if (
            best_score is not None
            and best_score < diagnosis.current_score
            and best.is_file()
        ):
            reason = (
                f"Unified deferred permutation improved CURRENT "
                f"({diagnosis.current_score}) to CURRENT ({best_score}) with "
                f"a {budget}-variant budget"
            )
            update_status, _ = automation_common.run_command(
                [
                    sys.executable,
                    str(ROOT / "scripts" / "project_state.py"),
                    "update-deferred",
                    candidate.identifier,
                    "--candidate",
                    str(best),
                    "--reason",
                    reason,
                    "--score",
                    str(best_score),
                ]
            )
            if update_status:
                raise automation_common.AutomationError(
                    f"could not preserve improved candidate for {candidate.identifier}"
                )
            detail = (
                f"improved CURRENT ({diagnosis.current_score}) to CURRENT "
                f"({best_score}) and updated the disabled source candidate"
            )
            print(f"DEFERRED {candidate.identifier}: {detail}")
            return AttemptResult(
                candidate.identifier,
                candidate.source,
                "deferred",
                "deferred",
                detail,
                best_score,
            )
        action = next(
            (
                line.partition(":")[2].strip()
                for line in output.splitlines()
                if line.startswith("AGENT_ACTION:")
            ),
            "CONTINUE_MISMATCH",
        )
        detail = (
            f"{action}; existing CURRENT ({diagnosis.current_score}) disabled "
            "candidate remains the best"
        )
        print(f"PRESERVED {candidate.identifier}: {detail}")
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "deferred",
            "preserved",
            detail,
            diagnosis.current_score,
        )
    raise automation_common.AutomationError(
        f"permute failed for {candidate.identifier} with exit {status}"
    )


def initial_report_entries() -> dict[str, AttemptResult]:
    functions, source_units = automation_common.candidate_inventory()
    entries: dict[str, AttemptResult] = {}
    for entry in functions:
        symbol = entry["symbol"]
        source = entry.get("source") if isinstance(entry.get("source"), str) else None
        if project_state.is_complete(entry):
            result = AttemptResult(symbol, source, "inventory", "already_matched", "already exact")
        elif entry.get("issue"):
            result = AttemptResult(symbol, source, "inventory", "excluded", "recorded issue")
        elif source is None:
            result = AttemptResult(symbol, source, "inventory", "excluded", "no source mapping")
        elif not all(
            entry["regions"][region]["state"] == "raw_asm"
            for region in project_state.TARGET_REGIONS
        ):
            result = AttemptResult(symbol, source, "inventory", "excluded", "unsupported regional state")
        else:
            _, post_match_action = project_state.next_source_unit_guidance(
                entry, functions, source_units
            )
            if post_match_action != "stop":
                result = AttemptResult(
                    symbol, source, "inventory", "excluded", "source-unit integration transition"
                )
            elif isinstance(entry.get("deferred"), dict):
                result = AttemptResult(symbol, source, "deferred", "not_attempted", "eligible deferred candidate")
            else:
                result = AttemptResult(symbol, source, "raw", "not_attempted", "eligible raw candidate")
        entries[symbol] = result
    return entries


def report_path(args: argparse.Namespace) -> Path:
    if args.report is not None:
        return args.report if args.report.is_absolute() else ROOT / args.report
    name = "all-report.json" if args.all else "report.json"
    return ROOT / "build" / "us" / "automate" / name


def write_report(
    path: Path,
    entries: dict[str, AttemptResult],
    *,
    full_scan: bool,
    scan_complete: bool,
    attempts: int,
    batch_verified: bool,
    pending_batch: list[str] | None = None,
) -> None:
    counts: dict[str, int] = {}
    for result in entries.values():
        counts[result.outcome] = counts.get(result.outcome, 0) + 1
    payload = {
        "schema_version": 1,
        "profile": "us",
        "generated_at": datetime.now(timezone.utc).isoformat(),
        "full_scan": full_scan,
        "scan_complete": scan_complete,
        "attempts": sum(
            counts.get(outcome, 0)
        for outcome in ("matched", "deferred", "skipped", "restored", "preserved")
        ),
        "invocation_attempts": attempts,
        "batch_verified": batch_verified,
        "pending_batch": pending_batch or [],
        "summary": dict(sorted(counts.items())),
        "functions": [asdict(entries[symbol]) for symbol in sorted(entries)],
    }
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_text(json.dumps(payload, indent=2) + "\n", encoding="utf-8")
    temporary.replace(path)


def resume_report(
    path: Path, entries: dict[str, AttemptResult]
) -> tuple[dict[str, AttemptResult], list[str]]:
    """Carry completed outcomes from an interrupted compatible full scan."""

    if not path.is_file():
        return entries, []
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as error:
        raise automation_common.AutomationError(
            f"cannot resume coverage report {path}: {error}"
        ) from error
    if (
        payload.get("schema_version") != 1
        or payload.get("profile") != "us"
        or payload.get("full_scan") is not True
        or not isinstance(payload.get("functions"), list)
    ):
        raise automation_common.AutomationError(
            f"cannot resume incompatible coverage report {path}; use --restart"
        )
    resumable = {"matched", "deferred", "skipped", "restored", "preserved"}
    for saved in payload["functions"]:
        if not isinstance(saved, dict) or saved.get("outcome") not in resumable:
            continue
        symbol = saved.get("symbol")
        current = entries.get(symbol)
        if current is None or current.outcome != "not_attempted":
            continue
        if saved.get("source") != current.source:
            continue
        try:
            entries[symbol] = AttemptResult(
                symbol=symbol,
                source=current.source,
                pool=str(saved.get("pool", current.pool)),
                outcome=str(saved["outcome"]),
                detail="resumed: " + str(saved.get("detail", "completed attempt")),
                score=saved.get("score") if isinstance(saved.get("score"), int) else None,
            )
        except (KeyError, TypeError, ValueError):
            continue
    pending = payload.get("pending_batch", [])
    if not isinstance(pending, list) or not all(
        isinstance(symbol, str) and symbol in entries for symbol in pending
    ):
        raise automation_common.AutomationError(
            f"cannot resume invalid pending batch in {path}; use --restart"
        )
    return entries, list(dict.fromkeys(pending))


def main(arguments: list[str] | None = None) -> int:
    args = parse_args(arguments)
    entries: dict[str, AttemptResult] = {}
    attempts = 0
    matched: list[str] = []
    deferred: list[str] = []
    destination = report_path(args)
    scan_complete = False
    batch_verified = False
    try:
        entries = initial_report_entries()
        if args.all and not args.restart:
            entries, matched = resume_report(destination, entries)
        candidates = automation_common.scheduled_candidates(
            automation_common.available_raw_candidates(),
            automation_common.available_deferred_candidates(),
        )
        if args.all:
            candidates = [
                candidate
                for candidate in candidates
                if entries[candidate.identifier].outcome == "not_attempted"
            ]
        for candidate in candidates:
            if not args.all and (
                len(matched) >= args.limit or attempts >= args.max_attempts
            ):
                break
            attempts += 1
            if isinstance(candidate, automation_common.RawCandidate):
                result = try_raw_candidate(
                    candidate, budget=args.rewrite_budget, defer_best=args.defer_best
                )
            else:
                result = try_deferred_candidate(candidate, budget=args.rewrite_budget)
            entries[result.symbol] = result
            if result.outcome == "matched":
                matched.append(result.symbol)
            elif result.outcome == "deferred":
                deferred.append(result.symbol)
            write_report(
                destination,
                entries,
                full_scan=args.all,
                scan_complete=False,
                attempts=attempts,
                batch_verified=False,
                pending_batch=matched,
            )
        scan_complete = args.all or attempts == len(candidates)

        if matched and args.skip_final_build:
            command = "./conker verify-batch " + " ".join(matched)
            print(
                "Skipped the final clean build check. The retained matches are not "
                "batch-verified."
            )
            print(f"Required before commit or handoff: {command}")
        elif matched:
            print(f"Running one clean batch gate for: {' '.join(matched)}")
            status, _ = automation_common.run_command(
                [str(ROOT / "conker"), "verify-batch", *matched]
            )
            if status:
                write_report(
                    destination,
                    entries,
                    full_scan=args.all,
                    scan_complete=scan_complete,
                    attempts=attempts,
                    batch_verified=False,
                    pending_batch=matched,
                )
                return status
            batch_verified = True
        else:
            batch_verified = True
        write_report(
            destination,
            entries,
            full_scan=args.all,
            scan_complete=scan_complete,
            attempts=attempts,
            batch_verified=batch_verified,
            pending_batch=[] if batch_verified else matched,
        )
    except (
        automation_common.AutomationError,
        candidate_rewrites.CandidateError,
        project_state.ProjectStateError,
        OSError,
    ) as error:
        if entries:
            write_report(
                destination,
                entries,
                full_scan=args.all,
                scan_complete=False,
                attempts=attempts,
                batch_verified=False,
                pending_batch=matched,
            )
        print(f"error: {error}", file=sys.stderr)
        print("AGENT_ACTION: BLOCKED_TOOLING")
        return 1

    print(
        f"Automation complete: {len(matched)} exact match(es), "
        f"{len(deferred)} preserved nonmatch(es), {attempts} attempt(s)."
    )
    print(f"Coverage report: {destination.relative_to(ROOT) if destination.is_relative_to(ROOT) else destination}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
