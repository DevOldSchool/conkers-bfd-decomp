#!/usr/bin/env python3
"""Run the unified, evidence-backed ASM-to-C automation workflow."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import sys
import time
import attempt_history
from functools import partial, wraps
from dataclasses import asdict, dataclass, replace
from datetime import datetime, timezone
from pathlib import Path

import automation_common
import candidate_rewrites
import project_state
import call_signatures
import declaration_facts


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
RESOURCE_KILL_STATUSES = frozenset((-9, 137))
COMPACT_PROGRESS_INTERVAL = 50
MAX_COMPILE_REPAIRS = 3
REPORT_SCHEMA_VERSION = 3
FINGERPRINT_VERSION = 2
FINGERPRINT_INPUTS = (
    "scripts/automate.py",
    "scripts/attempt_history.py",
    "scripts/automation_common.py",
    "scripts/candidate_rewrites.py",
    "scripts/candidate_syntax.py",
    "scripts/candidate_lifetimes.py",
    "scripts/candidate_tables.py",
    "scripts/declaration_facts.py",
    "scripts/m2c.py",
    "scripts/rzip_archive.py",
    "config/rzip_layouts.json",
    "scripts/call_signatures.py",
    "toolchain/tools.lock.json",
) + call_signatures.SDK_ALIAS_INPUTS
STAGE_INPUTS = {
    "inventory": ("scripts/automation_common.py", "scripts/project_state.py"),
    "m2c": ("scripts/m2c.py", "toolchain/tools.lock.json"),
    "declarations": ("scripts/declaration_facts.py",),
    "prepare": ("scripts/candidate_rewrites.py", "scripts/candidate_syntax.py"),
    "compile": (
        "scripts/candidate_rewrites.py",
        "scripts/candidate_syntax.py",
        "scripts/compile_c.py",
        "scripts/compile_diff_candidate.py",
        "scripts/diff.py",
        "toolchain/tools.lock.json",
    ),
    "diff": ("scripts/diff.py", "scripts/candidate_tables.py"),
    "permute": (
        "scripts/permute.py",
        "scripts/candidate_tables.py",
        "scripts/candidate_lifetimes.py",
        "scripts/candidate_rewrites.py",
        "scripts/candidate_syntax.py",
        "scripts/project_state.py",
        "toolchain/tools.lock.json",
    ),
    "finish": (
        "scripts/layout_check.py",
        "scripts/project_state.py",
        "scripts/conker.sh",
        "toolchain/tools.lock.json",
    ),
}
STAGE_VERSIONS = {stage: 1 for stage in STAGE_INPUTS}
# Raw and deferred candidates share diagnostic preflight/search eligibility.
STAGE_VERSIONS["diff"] = 3
# A changed starter can fix any later raw-stage failure, including declaration
# blockers saved before compilation. Keep the upstream recovery inputs in each
# relevant stage instead of requiring users to restart a saved scan.
CALL_CONTEXT_INPUTS = ("scripts/m2c.py", "scripts/call_signatures.py", "scripts/declaration_facts.py",
                       "scripts/rzip_archive.py", "config/rzip_layouts.json") + call_signatures.SDK_ALIAS_INPUTS
for _stage in STAGE_INPUTS:
    if _stage != "inventory":
        STAGE_INPUTS[_stage] = tuple(dict.fromkeys(STAGE_INPUTS[_stage] + CALL_CONTEXT_INPUTS))
CFE_DIAGNOSTIC = re.compile(
    r"(?m)^cfe: (?P<severity>Warning|Error)(?: (?P<code>\d+))?: "
    r"(?:(?P<path>.+), line (?P<line>\d+): )?(?P<message>.+)$"
)


@dataclass(frozen=True)
class CompilerDiagnostic:
    category: str
    severity: str
    code: int | None
    path: str | None
    line: int | None
    message: str


@dataclass(frozen=True)
class AttemptResult:
    symbol: str
    source: str | None
    pool: str
    outcome: str
    detail: str
    score: int | None = None
    fingerprint: str | None = None
    diagnostics: tuple[CompilerDiagnostic, ...] = ()
    candidate_artifact: str | None = None
    diagnostic_log: str | None = None
    command_log: str | None = None
    stage: str | None = None
    blocker_code: str | None = None
    stage_fingerprint: str | None = None
    previous_score: int | None = None
    repair_actions: tuple[str, ...] = ()


@dataclass(frozen=True)
class Diagnosis:
    current_score: int
    counts: dict[str, int]
    stack_rows: int = 0

    @property
    def is_stack_mismatch(self) -> bool:
        return (self.current_score > 0 and self.stack_rows > 0
                and self.counts["operand-or-constant"] == self.stack_rows
                and self.counts["opcode-or-control-flow"] == 0
                and self.counts["missing-or-extra"] == 0)

    @property
    def is_register_only(self) -> bool:
        return self.current_score > 0 and self.counts["register-only"] > 0 and all(
            self.counts[category] == 0
            for category in DIFF_CATEGORIES
            if category != "register-only"
        )

    @property
    def is_small_register_mismatch(self) -> bool:
        return (
            self.current_score > 0
            and self.counts["register-only"] > 0
            and self.counts["operand-or-constant"] == 0
            and self.counts["opcode-or-control-flow"] == 0
            and 1 <= self.counts["missing-or-extra"] <= 3
        )

    def search_budget(self, budget: int, *, stack_shapes: bool = False) -> int | None:
        if self.current_score == 0:
            return 1
        if stack_shapes and self.is_stack_mismatch:
            return min(budget, 8)
        if self.is_register_only:
            return budget
        if self.is_small_register_mismatch:
            return min(budget, 32)
        return None


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
        "--function",
        dest="target",
        metavar="WORK_ITEM_ID",
        help="attempt one specific eligible raw or deferred function",
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
        default=32,
        help="maximum source-shape variants per candidate (default: 32)",
    )
    parser.add_argument("--stack-shapes", action="store_true",
                        help="pilot evidence-checked stack-only candidate probes")
    parser.add_argument("--exhaustive", action="store_true",
                        help="use the full rewrite budget instead of stopping searches on a plateau")
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
        help="retry cached outcomes; pending verification is always preserved",
    )
    parser.add_argument(
        "--analyze",
        action="store_true",
        help="with --all, classify candidates without editing tracked project state",
    )
    parser.add_argument(
        "--verbose",
        action="store_true",
        help="echo detailed per-command output instead of compact progress",
    )
    parser.add_argument("--model-tokens", type=positive_integer,
                        help="externally measured model tokens attributable to this run")
    parsed = parser.parse_args(arguments)
    if parsed.all and parsed.max_attempts is not None:
        parser.error("--all cannot be combined with --max-attempts")
    if parsed.analyze and not parsed.all:
        parser.error("--analyze requires --all")
    if parsed.analyze and (
        parsed.defer_best or parsed.skip_final_build
    ):
        parser.error("--analyze cannot be combined with --defer-best or --skip-final-build")
    if parsed.target and parsed.max_attempts is not None:
        parser.error("--function cannot be combined with --max-attempts")
    if not parsed.all:
        parsed.limit = parsed.limit or 1
        parsed.max_attempts = 1 if parsed.target else (parsed.max_attempts or 10)
    return parsed


def automation_fingerprint() -> str:
    """Hash the versioned preparation and orchestration inputs."""

    digest = hashlib.sha256()
    digest.update(f"automation-fingerprint-v{FINGERPRINT_VERSION}\0".encode())
    for relative in FINGERPRINT_INPUTS:
        path = ROOT / relative
        digest.update(relative.encode())
        digest.update(b"\0")
        digest.update(path.read_bytes() if path.is_file() else b"<missing>")
        digest.update(b"\0")
    return digest.hexdigest()


def run_fingerprint(tool_fingerprint: str, args: argparse.Namespace) -> str:
    """Hash candidate-affecting invocation settings with the tooling inputs."""

    payload = {
        "defer_best": bool(args.defer_best),
        "mode": "analyze" if args.analyze else "execute",
        "rewrite_budget": args.rewrite_budget,
        "exhaustive": args.exhaustive,
        "stack_shapes": getattr(args, "stack_shapes", False),
    }
    digest = hashlib.sha256()
    digest.update(f"run-fingerprint-v{FINGERPRINT_VERSION}\0".encode())
    digest.update(tool_fingerprint.encode())
    digest.update(b"\0")
    digest.update(json.dumps(payload, sort_keys=True, separators=(",", ":")).encode())
    return digest.hexdigest()


def candidate_fingerprint(
    candidate: automation_common.RawCandidate | automation_common.DeferredCandidate,
    tool_fingerprint: str,
    *,
    prototypes: dict[str, call_signatures.Signature | None] | None = None,
    objects: dict[str, tuple[str, ...]] | None = None,
) -> str:
    """Hash candidate-local inputs used to decide whether a result is reusable."""

    digest = hashlib.sha256()
    digest.update(f"candidate-fingerprint-v{FINGERPRINT_VERSION}\0".encode())
    digest.update(tool_fingerprint.encode())
    digest.update(b"\0")
    for value in (candidate.identifier, candidate.source):
        digest.update(value.encode())
        digest.update(b"\0")
    for path in (
        ROOT / candidate.source,
        ROOT / project_state.nonmatching_asm_path(
            candidate.source, candidate.identifier
        ),
    ):
        digest.update(str(path.relative_to(ROOT)).encode())
        digest.update(b"\0")
        digest.update(path.read_bytes() if path.is_file() else b"<missing>")
        digest.update(b"\0")
    raw = ROOT / project_state.nonmatching_asm_path(candidate.source, candidate.identifier)
    if raw.is_file():
        assembly = raw.read_text()
        digest.update(call_signatures.dependency_digest(ROOT, assembly, prototypes).encode())
        if objects is None:
            objects = declaration_facts.object_evidence_index(ROOT)
        for symbol in sorted(set(re.findall(r"\b[A-Za-z_]\w*\b", assembly)) & objects.keys()):
            digest.update(symbol.encode())
            digest.update(json.dumps(objects[symbol]).encode())
    return digest.hexdigest()


def stage_fingerprint_seeds(args: argparse.Namespace) -> dict[str, str]:
    """Hash only the tools and options capable of changing each pipeline stage."""

    seeds: dict[str, str] = {}
    headers = hashlib.sha256()
    for path in sorted((ROOT / "include").rglob("*")):
        if path.is_file():
            headers.update(str(path.relative_to(ROOT)).encode())
            headers.update(path.read_bytes())
    for stage, relatives in STAGE_INPUTS.items():
        digest = hashlib.sha256()
        digest.update(
            f"automation-stage-{stage}-v{STAGE_VERSIONS[stage]}\0".encode()
        )
        for relative in relatives:
            path = ROOT / relative
            digest.update(relative.encode())
            digest.update(b"\0")
            digest.update(path.read_bytes() if path.is_file() else b"<missing>")
            digest.update(b"\0")
        digest.update(headers.digest())
        settings: dict[str, object] = {
            "mode": "analyze" if args.analyze else "execute"
        }
        if stage in {"diff", "permute"}:
            settings["stack_shapes"] = getattr(args, "stack_shapes", False)
        if stage == "permute":
            settings.update(
                rewrite_budget=args.rewrite_budget,
                exhaustive=args.exhaustive,
                defer_best=bool(args.defer_best),
            )
        digest.update(
            json.dumps(settings, sort_keys=True, separators=(",", ":")).encode()
        )
        seeds[stage] = digest.hexdigest()
    return seeds


def classify_attempt(result: AttemptResult) -> AttemptResult:
    """Attach a stable pipeline stage and blocker code to an attempt result."""

    detail = result.detail.lower()
    if result.outcome == "matched":
        return replace(result, stage="finish", blocker_code=None)
    if result.outcome == "ready":
        return replace(result, stage="prepare", blocker_code=None)
    if result.diagnostics:
        return replace(
            result,
            stage="compile",
            blocker_code=result.diagnostics[0].category,
        )
    if "source file is missing" in detail or "no source mapping" in detail:
        return replace(result, stage="inventory", blocker_code="missing_source")
    if "no unique project declaration evidence" in detail:
        return replace(
            result, stage="declarations", blocker_code="declaration_evidence"
        )
    if "unresolved placeholder" in detail:
        return replace(result, stage="prepare", blocker_code="unresolved_placeholder")
    if "composite declaration" in detail or "inferred member" in detail:
        return replace(result, stage="prepare", blocker_code="composite_layout")
    if "jump table" in detail:
        return replace(result, stage="m2c", blocker_code="missing_jump_table")
    if "decompilation failure" in detail or "m2c" in detail:
        return replace(result, stage="m2c", blocker_code="m2c_failure")
    if "layout gate" in detail or "source-unit layout mismatch" in detail:
        return replace(result, stage="finish", blocker_code="layout_gate")
    if "not register-allocation-only" in detail or "no supported targeted search" in detail:
        return replace(result, stage="diff", blocker_code="structural_mismatch")
    if "diagnostic preflight failed" in detail:
        return replace(result, stage="diff", blocker_code="diagnostic_failure")
    if "killed with exit" in detail:
        return replace(result, stage="permute", blocker_code="resource_killed")
    if result.outcome in {"preserved", "deferred", "restored"}:
        return replace(result, stage="permute", blocker_code="search_exhausted")
    return replace(result, stage="prepare", blocker_code="preparation_failure")


def compiler_diagnostics(output: str) -> tuple[CompilerDiagnostic, ...]:
    diagnostics: list[CompilerDiagnostic] = []
    for match in CFE_DIAGNOSTIC.finditer(output):
        severity = match.group("severity").lower()
        code_text = match.group("code")
        code = int(code_text) if code_text is not None else None
        category = (
            "pointer_integer"
            if code == 712
            else f"compiler_{severity}"
        )
        line_text = match.group("line")
        diagnostics.append(
            CompilerDiagnostic(
                category,
                severity,
                code,
                match.group("path"),
                int(line_text) if line_text is not None else None,
                match.group("message"),
            )
        )
    return tuple(diagnostics)


def save_failure_artifacts(
    symbol: str,
    candidate_source: bytes,
    output: str,
    diagnostics: tuple[CompilerDiagnostic, ...],
) -> tuple[str, str]:
    """Persist an unsuccessful compiling candidate and its complete diagnostic log."""

    directory = ROOT / "build" / "us" / "automate" / "artifacts" / symbol
    directory.mkdir(parents=True, exist_ok=True)
    candidate = directory / "candidate.c"
    log = directory / "compiler.log"
    structured = directory / "diagnostics.json"
    candidate.write_bytes(candidate_source)
    log.write_text(output, encoding="utf-8")
    structured.write_text(
        json.dumps([asdict(diagnostic) for diagnostic in diagnostics], indent=2)
        + "\n",
        encoding="utf-8",
    )
    return (
        str(candidate.relative_to(ROOT)),
        str(log.relative_to(ROOT)),
    )


def diagnostic_detail(
    diagnostics: tuple[CompilerDiagnostic, ...], fallback: str
) -> str:
    if not diagnostics:
        return fallback
    first = diagnostics[0]
    code = f" {first.code}" if first.code is not None else ""
    location = ""
    if first.path is not None:
        location = first.path
        if first.line is not None:
            location += f":{first.line}"
        location += ": "
    return f"{first.category}: {first.severity}{code}: {location}{first.message}"


def candidate_log_path(symbol: str) -> Path:
    return ROOT / "build" / "us" / "automate" / "logs" / f"{symbol}.log"


def prepare_candidate_log(symbol: str, *, verbose: bool) -> None:
    candidate_log_path(symbol).unlink(missing_ok=True)


def run_candidate_command(
    symbol: str, arguments: list[str], *, verbose: bool
) -> tuple[int, str]:
    return automation_common.run_command(
        arguments,
        echo=verbose,
        log_path=candidate_log_path(symbol),
    )


def emit_compact_progress(
    result: AttemptResult,
    *,
    attempts: int,
    total: int,
    pending_matches: int,
    new_matches: int = 0,
    score_improvements: int = 0,
) -> None:
    if result.outcome == "matched":
        print(f"MATCH {result.symbol}: exact candidate retained")
    elif result.outcome == "deferred":
        print(f"DEFERRED {result.symbol}: {result.detail}")
    elif result.diagnostics:
        print(f"DIAGNOSTIC {result.symbol}: {result.detail}")
    elif "killed with exit" in result.detail:
        print(f"INTERRUPTED {result.symbol}: {result.detail}")

    if attempts % COMPACT_PROGRESS_INTERVAL == 0:
        print(
            f"PROGRESS {attempts}/{total} candidate(s) inspected this run; "
            f"{total - attempts} remaining; {new_matches} new exact, "
            f"{max(0, pending_matches - new_matches)} carried exact, "
            f"{score_improvements} deferred improvement(s); "
            f"{pending_matches} awaiting the final batch gate"
        )


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
    stack = re.search(r"(?m)^stack-rows: (\d+)$", output)
    return Diagnosis(int(score_match.group("score")), counts, int(stack[1]) if stack else 0)


def candidate_block(prepared: candidate_rewrites.PreparedCandidate) -> str:
    declarations = "\n".join(prepared.declarations)
    return declarations + "\n\n" + prepared.definition if declarations else prepared.definition


def apply_best_function(source: Path, symbol: str, best: Path) -> None:
    content = source.read_text(encoding="utf-8")
    start, end = project_state.c_function_span(content, symbol)
    replacement = best.read_text(encoding="utf-8").rstrip("\n") + "\n"
    source.write_text(content[:start] + replacement + content[end:], encoding="utf-8")


def repair_candidate_source(
    candidate_source: bytes,
    symbol: str,
    diagnostics: tuple[CompilerDiagnostic, ...],
) -> tuple[bytes, tuple[str, ...]]:
    """Repair only the target function using the current compiler evidence."""

    content = candidate_source.decode("utf-8")
    start, end = project_state.c_function_span(content, symbol)
    repaired, actions = candidate_rewrites.repair_compile_diagnostics(
        content[start:end], tuple(diagnostic.message for diagnostic in diagnostics),
        visible_source=content[:start],
    )
    if repaired == content[start:end]:
        return candidate_source, ()
    return (content[:start] + repaired + content[end:]).encode(), actions


def add_deferred_intrinsic_declarations(
    candidate_source: bytes, symbol: str
) -> tuple[bytes, tuple[str, ...]]:
    """Add missing source-local IDO intrinsics used by a deferred function."""

    content = candidate_source.decode("utf-8")
    if not any(
        re.search(rf"\b{re.escape(intrinsic)}\s*\(", content)
        for intrinsic in candidate_rewrites.KNOWN_INTRINSICS
    ):
        return candidate_source, ()
    function_start, function_end = project_state.c_function_span(content, symbol)
    declarations, evidence = candidate_rewrites.required_intrinsic_declarations(
        content[function_start:function_end], content
    )
    if not declarations:
        return candidate_source, ()
    marker_pattern = re.compile(
        rf"#if 0 /\* {re.escape(project_state.DEFERRED_CANDIDATE_TAG)} "
        rf"{re.escape(symbol)}(?: CURRENT \(\d+\))? \*/"
    )
    marker = marker_pattern.search(content, 0, function_start)
    if marker is None:
        raise automation_common.AutomationError(
            f"{symbol} lacks its deferred candidate marker"
        )
    newline = "\r\n" if "\r\n" in content else "\n"
    insertion = newline.join(declarations) + newline
    updated = content[: marker.start()] + insertion + content[marker.start() :]
    actions = tuple(
        f"added source-local IDO intrinsic support for {item.partition(':')[0]}"
        for item in evidence
    )
    return updated.encode(), actions


def deferred_function_artifact(source: Path, symbol: str) -> Path:
    """Persist exactly one deferred function for transactional metadata updates."""

    content = source.read_text(encoding="utf-8")
    start, end = project_state.c_function_span(content, symbol)
    directory = ROOT / "build" / "us" / "automate" / "artifacts" / symbol
    directory.mkdir(parents=True, exist_ok=True)
    artifact = directory / "prepared-candidate.c"
    artifact.write_text(content[start:end].strip() + "\n", encoding="utf-8")
    return artifact


@dataclass
class SourceCheckpoint:
    content: bytes | None = None


def guard_interrupted_candidate(function):
    """Restore the latest retained source checkpoint after command cancellation."""

    @wraps(function)
    def guarded(candidate, **options):
        checkpoint = SourceCheckpoint()
        try:
            return function(candidate, checkpoint=checkpoint, **options)
        except KeyboardInterrupt:
            source = ROOT / candidate.source
            transaction = ROOT / "build/us/permute" / candidate.identifier / "apply-transaction.json"
            if transaction.is_file():
                status, _ = automation_common.run_command([
                    sys.executable, str(ROOT / "scripts/project_state.py"),
                    "rollback-permutation", candidate.identifier,
                ])
                if status:
                    raise automation_common.AutomationError(f"interrupted permutation rollback failed for {candidate.identifier}")
            inventory = ROOT / "progress/functions.json"
            if inventory.is_file():
                entries = project_state.load_json(inventory)["functions"]
                entry = next(e for e in entries if e["symbol"] == candidate.identifier)
                if project_state.is_complete(entry):
                    raise
                score = entry.get("deferred", {}).get("current_score")
                if score is not None and checkpoint.content is not None:
                    marker = re.compile(rf"CONKER_DEFERRED_CANDIDATE {re.escape(candidate.identifier)} CURRENT \({score}\)")
                    if not marker.search(checkpoint.content.decode()):
                        if marker.search(source.read_text()):
                            # A completed defer/update transaction supersedes
                            # the pre-command checkpoint and must be retained.
                            raise
                        raise automation_common.AutomationError(f"interrupted deferred state needs recovery for {candidate.identifier}")
            if checkpoint.content is not None:
                source.write_bytes(checkpoint.content)
            raise
    return guarded


def save_starter_artifact(symbol: str, starter: str) -> str:
    path = ROOT / "build/us/automate/artifacts" / symbol / "starter.c"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(starter, encoding="utf-8")
    return str(path.relative_to(ROOT))


def analyze_raw_candidate(
    candidate: automation_common.RawCandidate,
    *,
    verbose: bool = True,
) -> AttemptResult:
    """Classify one raw starter without changing tracked project files."""

    source = ROOT / candidate.source
    if not source.is_file():
        if verbose:
            print(f"ANALYZE {candidate.identifier}: SKIPPED source file is missing")
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "raw",
            "skipped",
            "source file is missing",
        )
    try:
        original = source.read_bytes()
        starter = automation_common.generate_starter(candidate.identifier)
        save_starter_artifact(candidate.identifier, starter)
        prepared = candidate_rewrites.prepare_starter(
            starter,
            candidate.c_symbol,
            original.decode("utf-8"),
            root=ROOT,
        )
        automation_common.replace_target_pragma(
            original,
            candidate.source,
            candidate.identifier,
            candidate_block(prepared),
        )
    except (
        UnicodeDecodeError,
        automation_common.AutomationError,
        candidate_rewrites.CandidateError,
        OSError,
    ) as error:
        if verbose:
            print(f"ANALYZE {candidate.identifier}: SKIPPED {error}")
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "raw",
            "skipped",
            str(error),
        )
    detail = "sanitized starter is ready for a focused compile"
    if prepared.evidence:
        detail += "; evidence: " + "; ".join(prepared.evidence)
    if verbose:
        print(f"ANALYZE {candidate.identifier}: READY")
    return AttemptResult(
        candidate.identifier,
        candidate.source,
        "raw",
        "ready",
        detail,
    )


def analyze_deferred_candidate(
    candidate: automation_common.DeferredCandidate,
    *,
    verbose: bool = True,
) -> AttemptResult:
    """Record a deferred candidate as compile-analysis work without resuming it."""

    source = ROOT / candidate.source
    if not source.is_file():
        if verbose:
            print(f"ANALYZE {candidate.identifier}: SKIPPED source file is missing")
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "deferred",
            "skipped",
            "source file is missing",
        )
    score = candidate.current_score
    detail = "preserved candidate is ready for non-mutating diagnose-diff"
    if score is not None:
        detail += f" from CURRENT ({score})"
    if verbose:
        print(f"ANALYZE {candidate.identifier}: READY deferred candidate")
    return AttemptResult(
        candidate.identifier,
        candidate.source,
        "deferred",
        "ready",
        detail,
        score,
    )


@guard_interrupted_candidate
def try_raw_candidate(
    candidate: automation_common.RawCandidate,
    *,
    budget: int,
    defer_best: bool,
    verbose: bool = True,
    exhaustive: bool = False,
    stack_shapes: bool = False,
    checkpoint: SourceCheckpoint,
) -> AttemptResult:
    prepare_candidate_log(candidate.identifier, verbose=verbose)
    source = ROOT / candidate.source
    if not source.is_file():
        detail = "source file is missing"
        if verbose:
            print(f"SKIP {candidate.identifier}: {detail}")
        return AttemptResult(candidate.identifier, candidate.source, "raw", "skipped", detail)
    original = source.read_bytes()
    checkpoint.content = original
    try:
        starter = automation_common.generate_starter(candidate.identifier)
        save_starter_artifact(candidate.identifier, starter)
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
        if verbose:
            print(f"SKIP {candidate.identifier}: {detail}")
        return AttemptResult(candidate.identifier, candidate.source, "raw", "skipped", detail)

    source.write_bytes(updated)
    evidence = f"; evidence: {'; '.join(prepared.evidence)}" if prepared.evidence else ""
    if verbose:
        print(
            f"TRY {candidate.identifier}: sanitized m2c candidate in "
            f"{candidate.source} ({candidate.size_bytes} bytes){evidence}"
        )
    diff_status, diff_output = run_candidate_command(
        candidate.identifier,
        [str(ROOT / "conker"), "diagnose-diff", candidate.identifier],
        verbose=verbose,
    )
    parsed_diagnostics = compiler_diagnostics(diff_output)
    initial_score = score_from_output(diff_output)
    repair_actions: list[str] = []
    diagnostic_output = diff_output
    for _ in range(MAX_COMPILE_REPAIRS):
        if not parsed_diagnostics:
            break
        repaired, actions = repair_candidate_source(
            updated, candidate.c_symbol, parsed_diagnostics
        )
        if not actions or repaired == updated:
            break
        updated = repaired
        source.write_bytes(updated)
        repair_actions.extend(actions)
        if verbose:
            print(
                f"REPAIR {candidate.identifier}: "
                + "; ".join(actions)
            )
        diff_status, diff_output = run_candidate_command(
            candidate.identifier,
            [str(ROOT / "conker"), "diagnose-diff", candidate.identifier],
            verbose=verbose,
        )
        diagnostic_output += "\n" + diff_output
        parsed_diagnostics = compiler_diagnostics(diff_output)
        initial_score = score_from_output(diff_output)
    if parsed_diagnostics:
        candidate_artifact, diagnostic_log = save_failure_artifacts(
            candidate.identifier, updated, diagnostic_output, parsed_diagnostics
        )
        source.write_bytes(original)
        detail = diagnostic_detail(
            parsed_diagnostics, "candidate emitted compiler diagnostics"
        )
        if verbose:
            print(f"RESTORED {candidate.identifier}: {detail}")
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "raw",
            "restored",
            detail,
            initial_score,
            diagnostics=parsed_diagnostics,
            candidate_artifact=candidate_artifact,
            diagnostic_log=diagnostic_log,
            repair_actions=tuple(dict.fromkeys(repair_actions)),
        )
    diagnosis = None
    diagnosis_error = f"exit {diff_status}"
    if diff_status == 0:
        try:
            diagnosis = parse_diagnosis(diff_output)
        except automation_common.AutomationError as error:
            diagnosis_error = str(error)
    if diagnosis is None:
        candidate_artifact, diagnostic_log = save_failure_artifacts(
            candidate.identifier, updated, diagnostic_output, parsed_diagnostics
        )
        source.write_bytes(original)
        detail = diagnostic_detail(
            parsed_diagnostics,
            f"diagnostic preflight failed: {diagnosis_error}",
        )
        if verbose:
            print(f"RESTORED {candidate.identifier}: {detail}")
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "raw",
            "restored",
            detail,
            initial_score,
            diagnostics=parsed_diagnostics,
            candidate_artifact=candidate_artifact,
            diagnostic_log=diagnostic_log,
            repair_actions=tuple(dict.fromkeys(repair_actions)),
        )
    initial_score = diagnosis.current_score
    if initial_score == 0:
        finish_status, finish_output = run_candidate_command(
            candidate.identifier,
            [str(ROOT / "conker"), "finish", candidate.identifier],
            verbose=verbose,
        )
        if finish_status == 0:
            return AttemptResult(
                candidate.identifier,
                candidate.source,
                "raw",
                "matched",
                "exact preflight and finish gates passed",
                0,
                repair_actions=tuple(dict.fromkeys(repair_actions)),
            )
        if automation_common.entry_is_complete(candidate.identifier):
            raise automation_common.AutomationError(
                f"{candidate.identifier} was recorded matched, but a later gate "
                "failed; the exact source was retained for manual recovery"
            )
        finish_diagnostics = compiler_diagnostics(finish_output)
        candidate_artifact, diagnostic_log = save_failure_artifacts(
            candidate.identifier, updated, finish_output, finish_diagnostics
        )
        source.write_bytes(original)
        detail = diagnostic_detail(
            finish_diagnostics,
            "focused CURRENT (0) failed the source-unit layout gate",
        )
        if verbose:
            print(f"RESTORED {candidate.identifier}: {detail}")
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "raw",
            "restored",
            detail,
            0,
            diagnostics=finish_diagnostics,
            candidate_artifact=candidate_artifact,
            diagnostic_log=diagnostic_log,
            repair_actions=tuple(dict.fromkeys(repair_actions)),
        )

    search_budget = diagnosis.search_budget(budget, stack_shapes=stack_shapes)
    if search_budget is None:
        try:
            candidate_artifact, diagnostic_log = save_failure_artifacts(
                candidate.identifier, updated, diagnostic_output, ()
            )
        finally:
            source.write_bytes(original)
        detail = f"CURRENT ({initial_score}) has no supported targeted search"
        if verbose:
            print(f"SKIP {candidate.identifier}: {detail}; candidate saved")
        return AttemptResult(
            candidate.identifier, candidate.source, "raw", "skipped", detail,
            initial_score, candidate_artifact=candidate_artifact,
            diagnostic_log=diagnostic_log,
            repair_actions=tuple(dict.fromkeys(repair_actions)),
        )

    permutation_status, permutation_output = run_candidate_command(
        candidate.identifier,
        [
            str(ROOT / "conker"),
            "permute",
            candidate.identifier,
            "--budget",
            str(search_budget),
            *(["--stack-shapes"] if diagnosis.is_stack_mismatch else []),
            *(["--exhaustive"] if exhaustive else []),
        ],
        verbose=verbose,
    )
    if permutation_status == 0:
        if not automation_common.entry_is_complete(candidate.identifier):
            raise automation_common.AutomationError(
                f"{candidate.identifier} permutation succeeded without recording a match"
            )
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "raw",
            "matched",
            "exact rewrite match passed finish",
            0,
            repair_actions=tuple(dict.fromkeys(repair_actions)),
        )
    if automation_common.entry_is_complete(candidate.identifier):
        raise automation_common.AutomationError(
            f"{candidate.identifier} was recorded matched, but permutation later failed"
        )
    resource_killed = permutation_status in RESOURCE_KILL_STATUSES
    if permutation_status != 1 and not resource_killed:
        source.write_bytes(original)
        raise automation_common.AutomationError(
            f"permutation failed for {candidate.identifier} with exit {permutation_status}"
        )

    best = ROOT / "build" / "us" / "permute" / candidate.identifier / "best.c"
    best_score = score_from_output(permutation_output)
    retained_score = best_score if best_score is not None else initial_score
    saved_positive_best = best.is_file() and best_score not in (None, 0)
    killed_with_scored_source = resource_killed and initial_score > 0
    if not defer_best or (not saved_positive_best and not killed_with_scored_source):
        source.write_bytes(original)
        if resource_killed:
            detail = (
                f"permutation process was killed with exit {permutation_status}; "
                "source restored"
            )
            if verbose:
                print(f"SKIP {candidate.identifier}: {detail}")
            return AttemptResult(
                candidate.identifier,
                candidate.source,
                "raw",
                "skipped",
                detail,
                retained_score,
                repair_actions=tuple(dict.fromkeys(repair_actions)),
            )
        detail = f"no exact match; best CURRENT ({retained_score})"
        if verbose:
            print(f"RESTORED {candidate.identifier}: {detail}")
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "raw",
            "restored",
            detail,
            retained_score,
            repair_actions=tuple(dict.fromkeys(repair_actions)),
        )

    if saved_positive_best:
        apply_best_function(source, candidate.c_symbol, best)
        deferred_score = best_score
    else:
        deferred_score = initial_score
    reason = (
        f"Unified automated m2c and bounded {budget}-variant source search; "
        f"best candidate remains CURRENT ({deferred_score})"
    )
    if resource_killed:
        reason += f" after permutation was killed with exit {permutation_status}"
    defer_status, _ = run_candidate_command(
        candidate.identifier,
        [str(ROOT / "conker"), "defer", candidate.identifier, "--reason", reason],
        verbose=verbose,
    )
    if defer_status:
        source.write_bytes(original)
        raise automation_common.AutomationError(
            f"could not preserve {candidate.identifier} best candidate"
        )
    detail = f"best CURRENT ({deferred_score}) preserved"
    if verbose:
        print(f"DEFERRED {candidate.identifier}: {detail}")
    return AttemptResult(
        candidate.identifier,
        candidate.source,
        "raw",
        "deferred",
        detail,
        deferred_score,
        repair_actions=tuple(dict.fromkeys(repair_actions)),
    )


@guard_interrupted_candidate
def try_deferred_candidate(
    candidate: automation_common.DeferredCandidate,
    *,
    budget: int,
    verbose: bool = True,
    exhaustive: bool = False,
    stack_shapes: bool = False,
    checkpoint: SourceCheckpoint,
) -> AttemptResult:
    prepare_candidate_log(candidate.identifier, verbose=verbose)
    source = ROOT / candidate.source
    if not source.is_file():
        detail = "source file is missing"
        if verbose:
            print(f"SKIP {candidate.identifier}: {detail}")
        return AttemptResult(
            candidate.identifier, candidate.source, "deferred", "skipped", detail
        )
    original = source.read_bytes()
    checkpoint.content = original
    augmented, intrinsic_actions = add_deferred_intrinsic_declarations(
        original, candidate.identifier
    )
    if augmented != original:
        source.write_bytes(augmented)
        if verbose:
            print(
                f"REPAIR {candidate.identifier}: "
                + "; ".join(intrinsic_actions)
            )
    diagnose_status, diagnose_output = run_candidate_command(
        candidate.identifier,
        [str(ROOT / "conker"), "diagnose-diff", candidate.identifier],
        verbose=verbose,
    )
    parsed_diagnostics = compiler_diagnostics(diagnose_output)
    repair_actions = list(intrinsic_actions)
    diagnostic_output = diagnose_output
    for _ in range(MAX_COMPILE_REPAIRS):
        if not parsed_diagnostics:
            break
        repaired, actions = repair_candidate_source(
            augmented, candidate.identifier, parsed_diagnostics
        )
        if not actions or repaired == augmented:
            break
        augmented = repaired
        source.write_bytes(augmented)
        repair_actions.extend(actions)
        if verbose:
            print(f"REPAIR {candidate.identifier}: " + "; ".join(actions))
        try:
            diagnose_status, diagnose_output = run_candidate_command(
                candidate.identifier,
                [str(ROOT / "conker"), "diagnose-diff", candidate.identifier],
                verbose=verbose,
            )
        except BaseException:
            source.write_bytes(original)
            raise
        diagnostic_output += "\n" + diagnose_output
        parsed_diagnostics = compiler_diagnostics(diagnose_output)
    preparation_actions = tuple(dict.fromkeys(repair_actions))
    if parsed_diagnostics:
        candidate_artifact, diagnostic_log = save_failure_artifacts(
            candidate.identifier, augmented, diagnostic_output, parsed_diagnostics
        )
        detail = diagnostic_detail(
            parsed_diagnostics, "preserved candidate emitted compiler diagnostics"
        )
        if verbose:
            print(f"SKIP {candidate.identifier}: {detail}")
        if source.read_bytes() != original:
            source.write_bytes(original)
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "deferred",
            "skipped",
            detail,
            candidate.current_score,
            diagnostics=parsed_diagnostics,
            candidate_artifact=candidate_artifact,
            diagnostic_log=diagnostic_log,
            repair_actions=preparation_actions,
        )
    if diagnose_status == 2:
        candidate_artifact, diagnostic_log = save_failure_artifacts(
            candidate.identifier, augmented, diagnostic_output, parsed_diagnostics
        )
        detail = f"preserved candidate compile failed with exit {diagnose_status}"
        if verbose:
            print(f"SKIP {candidate.identifier}: {detail}")
        if source.read_bytes() != original:
            source.write_bytes(original)
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "deferred",
            "skipped",
            detail,
            candidate.current_score,
            diagnostics=parsed_diagnostics,
            candidate_artifact=candidate_artifact,
            diagnostic_log=diagnostic_log,
            repair_actions=preparation_actions,
        )
    if diagnose_status:
        if source.read_bytes() != original:
            source.write_bytes(original)
        raise automation_common.AutomationError(
            f"diagnose-diff failed for {candidate.identifier} with exit {diagnose_status}"
        )
    try:
        diagnosis = parse_diagnosis(diagnose_output)
    except automation_common.AutomationError:
        if source.read_bytes() != original:
            source.write_bytes(original)
        raise
    preparation_improved = False
    retention_score = candidate.current_score
    if preparation_actions:
        old_score = candidate.current_score
        if (
            diagnosis.current_score > 0
            and old_score is not None
            and diagnosis.current_score < old_score
        ):
            artifact = deferred_function_artifact(source, candidate.identifier)
            reason = (
                f"Unified deferred preparation improved CURRENT ({old_score}) to "
                f"CURRENT ({diagnosis.current_score}) with diagnostic-guided "
                "source preparation"
            )
            update_status, _ = run_candidate_command(
                candidate.identifier,
                [
                    sys.executable,
                    str(ROOT / "scripts" / "project_state.py"),
                    "update-deferred",
                    candidate.identifier,
                    "--candidate",
                    str(artifact),
                    "--reason",
                    reason,
                    "--score",
                    str(diagnosis.current_score),
                ],
                verbose=verbose,
            )
            if update_status:
                source.write_bytes(original)
                raise automation_common.AutomationError(
                    f"could not preserve preparation repair for {candidate.identifier}"
                )
            original = source.read_bytes()
            checkpoint.content = original
            preparation_improved = True
            retention_score = diagnosis.current_score
    preserved_score = (
        retention_score
        if preparation_actions and retention_score is not None
        else diagnosis.current_score
    )
    search_budget = diagnosis.search_budget(budget, stack_shapes=stack_shapes)
    if search_budget is None:
        detail = f"CURRENT ({diagnosis.current_score}) has no supported targeted search"
        outcome = "skipped"
        if preparation_improved:
            detail += "; improved deferred candidate retained"
            outcome = "deferred"
        if source.read_bytes() != original:
            source.write_bytes(original)
        if verbose:
            print(f"SKIP {candidate.identifier}: {detail}")
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "deferred",
            outcome,
            detail,
            diagnosis.current_score,
            repair_actions=preparation_actions,
        )

    if verbose:
        if diagnosis.current_score == 0:
            print(
                f"TRY {candidate.identifier}: exact deferred candidate; "
                "running authoritative finish recovery"
            )
        else:
            print(
                f"TRY {candidate.identifier}: "
                f"{diagnosis.counts['register-only']} register-only row(s), "
                f"{diagnosis.counts['missing-or-extra']} missing/extra row(s), "
                f"budget {search_budget}"
            )
    try:
        status, output = run_candidate_command(
            candidate.identifier,
            [
                str(ROOT / "conker"),
                "permute",
                candidate.identifier,
                "--budget",
                str(search_budget),
                *(["--stack-shapes"] if diagnosis.is_stack_mismatch else []),
                *(["--exhaustive"] if exhaustive else []),
            ],
            verbose=verbose,
        )
    except BaseException:
        if not automation_common.entry_is_complete(candidate.identifier):
            source.write_bytes(original)
        raise
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
            repair_actions=preparation_actions,
        )
    if automation_common.entry_is_complete(candidate.identifier):
        raise automation_common.AutomationError(
            f"{candidate.identifier} was recorded matched, but a later gate failed; "
            "the exact source was retained for manual recovery"
        )
    if status == 1 or status in RESOURCE_KILL_STATUSES:
        if source.read_bytes() != original:
            source.write_bytes(original)
        if status in RESOURCE_KILL_STATUSES:
            detail = (
                f"permutation process was killed with exit {status}; existing "
                f"CURRENT ({preserved_score}) disabled candidate preserved"
            )
            if verbose:
                print(f"PRESERVED {candidate.identifier}: {detail}")
            return AttemptResult(
                candidate.identifier,
                candidate.source,
                "deferred",
                "preserved",
                detail,
                preserved_score,
                repair_actions=preparation_actions,
            )
        layout_failure = next(
            (
                line.partition("error:")[2].strip()
                for line in output.splitlines()
                if "source-unit layout mismatch" in line
            ),
            None,
        )
        if layout_failure is not None:
            detail = (
                f"{layout_failure}; existing CURRENT "
                f"({preserved_score}) disabled candidate preserved"
            )
            if verbose:
                print(f"PRESERVED {candidate.identifier}: {detail}")
            return AttemptResult(
                candidate.identifier,
                candidate.source,
                "deferred",
                "preserved",
                detail,
                preserved_score,
                repair_actions=preparation_actions,
            )
        best = ROOT / "build" / "us" / "permute" / candidate.identifier / "best.c"
        best_score = score_from_output(output)
        if (
            best_score is not None
            and best_score > 0
            and best_score < preserved_score
            and best.is_file()
        ):
            reason = (
                f"Unified deferred permutation improved CURRENT "
                f"({preserved_score}) to CURRENT ({best_score}) with "
                f"a {budget}-variant budget"
            )
            if preparation_actions and not preparation_improved:
                # Keep source-local declarations used to measure this best
                # candidate. Roll back the augmentation if persistence fails.
                source.write_bytes(augmented)
            update_status, _ = run_candidate_command(
                candidate.identifier,
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
                ],
                verbose=verbose,
            )
            if update_status:
                source.write_bytes(original)
                raise automation_common.AutomationError(
                    f"could not preserve improved candidate for {candidate.identifier}"
                )
            detail = (
                f"improved CURRENT ({preserved_score}) to CURRENT "
                f"({best_score}) and updated the disabled source candidate"
            )
            if verbose:
                print(f"DEFERRED {candidate.identifier}: {detail}")
            return AttemptResult(
                candidate.identifier,
                candidate.source,
                "deferred",
                "deferred",
                detail,
                best_score,
                repair_actions=preparation_actions,
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
        if verbose:
            print(f"PRESERVED {candidate.identifier}: {detail}")
        return AttemptResult(
            candidate.identifier,
            candidate.source,
            "deferred",
            "preserved",
            detail,
            preserved_score,
            repair_actions=preparation_actions,
        )
    if source.read_bytes() != original:
        source.write_bytes(original)
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
    if args.analyze:
        name = "analysis-report.json"
    elif args.target:
        name = f"{args.target}-report.json"
    else:
        name = "all-report.json" if args.all else "report.json"
    return ROOT / "build" / "us" / "automate" / name


def run_progress(entries: dict[str, AttemptResult], pending_batch: list[str]) -> dict[str, int]:
    fresh = [result for result in entries.values() if not result.detail.startswith("resumed: ")]
    return {
        "new_exact_matches": sum(result.outcome == "matched" for result in fresh),
        "carried_pending_matches": sum(entries[symbol].outcome != "matched" for symbol in pending_batch if symbol in entries),
        "deferred_improvements": sum(
            result.previous_score is not None and result.score is not None
            and 0 < result.score < result.previous_score and result.outcome in ("deferred", "preserved")
            for result in fresh
        ),
    }


def write_report(
    path: Path,
    entries: dict[str, AttemptResult],
    *,
    full_scan: bool,
    scan_complete: bool,
    attempts: int,
    batch_verified: bool,
    pending_batch: list[str] | None = None,
    mode: str = "execute",
    tool_fingerprint: str | None = None,
    stage_fingerprints: dict[str, str] | None = None,
    metrics: dict | None = None,
    verified_batch: list[str] | None = None,
    save_history: bool = False,
) -> None:
    counts: dict[str, int] = {}
    for result in entries.values():
        counts[result.outcome] = counts.get(result.outcome, 0) + 1
    payload = {
        "schema_version": REPORT_SCHEMA_VERSION,
        "profile": "us",
        "mode": mode,
        "generated_at": datetime.now(timezone.utc).isoformat(),
        "fingerprint_version": FINGERPRINT_VERSION,
        "automation_fingerprint": tool_fingerprint or automation_fingerprint(),
        "stage_fingerprints": stage_fingerprints or {},
        "full_scan": full_scan,
        "scan_complete": scan_complete,
        "attempts": sum(
            counts.get(outcome, 0)
        for outcome in (
            "matched",
            "deferred",
            "skipped",
            "restored",
            "preserved",
            "ready",
        )
        ),
        "invocation_attempts": attempts,
        "invocation_progress": run_progress(entries, pending_batch or []),
        "batch_verified": batch_verified,
        "pending_batch": pending_batch or [],
        "verified_batch": verified_batch or [],
        "metrics": metrics or {},
        "summary": dict(sorted(counts.items())),
        "functions": [asdict(entries[symbol]) for symbol in sorted(entries)],
    }
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_text(json.dumps(payload, indent=2) + "\n", encoding="utf-8")
    temporary.replace(path)
    if save_history:
        attempt_history.save(ROOT, payload)


def reconcile_pending_batch(
    pending: list[str], authoritative_entries: dict[str, AttemptResult]
) -> tuple[list[str], list[str]]:
    """Keep only unique pending IDs that remain matched in current inventory."""

    currently_matched = {
        symbol
        for symbol, result in authoritative_entries.items()
        if result.outcome == "already_matched"
    }
    unique = list(dict.fromkeys(pending))
    return (
        [symbol for symbol in unique if symbol in currently_matched],
        [symbol for symbol in unique if symbol not in currently_matched],
    )


def resume_report(
    path: Path,
    entries: dict[str, AttemptResult],
    current_fingerprints: dict[str, str | dict[str, str]] | None = None,
    *,
    mode: str = "execute",
    payload: dict | None = None,
) -> tuple[dict[str, AttemptResult], list[str]]:
    """Reuse fresh outcomes and retain pending gates for any execution scope."""

    if payload is None and not path.is_file():
        return entries, []
    try:
        if payload is None:
            payload = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as error:
        raise automation_common.AutomationError(
            f"cannot resume coverage report {path}: {error}"
        ) from error
    if (
        payload.get("schema_version") not in (1, 2, REPORT_SCHEMA_VERSION)
        or payload.get("profile") != "us"
        or payload.get("mode", "execute") != mode
        or not isinstance(payload.get("functions"), list)
    ):
        raise automation_common.AutomationError(
            f"cannot resume incompatible coverage report {path}; use --restart"
        )
    authoritative_entries = dict(entries)
    resumable = {"deferred", "skipped", "restored", "preserved", "ready"}
    for saved in payload["functions"]:
        if not isinstance(saved, dict) or saved.get("outcome") not in resumable:
            continue
        symbol = saved.get("symbol")
        current = entries.get(symbol)
        if current is None or current.outcome != "not_attempted":
            continue
        if saved.get("source") != current.source:
            continue
        saved_fingerprint = saved.get("fingerprint")
        if current_fingerprints is not None:
            expected = current_fingerprints.get(symbol)
            saved_stage = saved.get("stage")
            if isinstance(expected, dict):
                if not isinstance(saved_stage, str):
                    continue
                expected = expected.get(saved_stage)
            if (
                not isinstance(saved_fingerprint, str)
                or not isinstance(expected, str)
                or saved_fingerprint != expected
            ):
                continue
        saved_pool = str(saved.get("pool", current.pool))
        if saved_pool != current.pool and not (
            saved.get("outcome") == "deferred" and current.pool == "deferred"
        ):
            continue
        try:
            saved_diagnostics = tuple(
                CompilerDiagnostic(
                    category=str(diagnostic["category"]),
                    severity=str(diagnostic["severity"]),
                    code=(
                        diagnostic.get("code")
                        if isinstance(diagnostic.get("code"), int)
                        else None
                    ),
                    path=(
                        diagnostic.get("path")
                        if isinstance(diagnostic.get("path"), str)
                        else None
                    ),
                    line=(
                        diagnostic.get("line")
                        if isinstance(diagnostic.get("line"), int)
                        else None
                    ),
                    message=str(diagnostic["message"]),
                )
                for diagnostic in saved.get("diagnostics", [])
                if isinstance(diagnostic, dict)
            )
            detail = str(saved.get("detail", "completed attempt"))
            if not detail.startswith("resumed: "):
                detail = "resumed: " + detail
            entries[symbol] = AttemptResult(
                symbol=symbol,
                source=current.source,
                pool=current.pool,
                outcome=str(saved["outcome"]),
                detail=detail,
                score=saved.get("score") if isinstance(saved.get("score"), int) else None,
                fingerprint=saved_fingerprint if isinstance(saved_fingerprint, str) else None,
                diagnostics=saved_diagnostics,
                candidate_artifact=(
                    saved.get("candidate_artifact")
                    if isinstance(saved.get("candidate_artifact"), str)
                    else None
                ),
                diagnostic_log=(
                    saved.get("diagnostic_log")
                    if isinstance(saved.get("diagnostic_log"), str)
                    else None
                ),
                command_log=(
                    saved.get("command_log")
                    if isinstance(saved.get("command_log"), str)
                    else None
                ),
                stage=(
                    saved.get("stage")
                    if isinstance(saved.get("stage"), str)
                    else None
                ),
                blocker_code=(
                    saved.get("blocker_code")
                    if isinstance(saved.get("blocker_code"), str)
                    else None
                ),
                stage_fingerprint=(
                    saved.get("stage_fingerprint")
                    if isinstance(saved.get("stage_fingerprint"), str)
                    else None
                ),
                repair_actions=tuple(
                    str(action)
                    for action in saved.get("repair_actions", [])
                    if isinstance(action, str)
                ),
            )
        except (KeyError, TypeError, ValueError):
            continue
    pending = payload.get("pending_batch", [])
    if not isinstance(pending, list) or not all(
        isinstance(symbol, str) for symbol in pending
    ):
        raise automation_common.AutomationError(
            f"cannot resume invalid pending batch in {path}; use --restart"
        )
    reconciled, dropped = reconcile_pending_batch(pending, authoritative_entries)
    if dropped:
        print(
            "Ignored stale pending batch ID(s) that are no longer matched: "
            + " ".join(dropped)
        )
    return entries, reconciled


def main(arguments: list[str] | None = None) -> int:
    args = parse_args(arguments)
    write_run_report = partial(write_report, save_history=True)
    entries: dict[str, AttemptResult] = {}
    attempts = 0
    matched: list[str] = []
    deferred: list[str] = []
    destination = report_path(args)
    scan_complete = False
    batch_verified = False
    mode = "analyze" if args.analyze else "execute"
    compact = not args.verbose
    started = time.monotonic()
    attempted_symbols: list[str] = []
    tool_fingerprint: str | None = None
    stage_seeds: dict[str, str] = {}
    active_candidate = None
    try:
        tool_fingerprint = automation_fingerprint()
        stage_seeds = stage_fingerprint_seeds(args)
        entries = initial_report_entries()
        candidates = automation_common.scheduled_candidates(
            automation_common.available_raw_candidates(),
            automation_common.available_deferred_candidates(),
        )
        # Share a read-only signature snapshot across resume fingerprints; a
        # candidate hashes only its callees, not unrelated newly matched C.
        prototypes = call_signatures.signature_index(ROOT)
        objects = declaration_facts.object_evidence_index(ROOT)
        if args.target:
            selected = next(
                (
                    candidate
                    for candidate in candidates
                    if candidate.identifier == args.target
                ),
                None,
            )
            if selected is None:
                inventory_result = entries.get(args.target)
                if inventory_result is None:
                    raise automation_common.AutomationError(
                        f"unknown work item {args.target}"
                    )
                raise automation_common.AutomationError(
                    f"{args.target} is not eligible for automation: "
                    f"{inventory_result.detail}"
                )
            candidates = [selected]
        history = (None if args.analyze else attempt_history.load(ROOT))
        if destination.is_file() and (args.analyze or not history):
            history = attempt_history.read_report(destination)
        saved_results = {item["symbol"]: item for item in (history or {}).get("functions", [])}
        current_fingerprints = {}
        for candidate in candidates:
            stage = saved_results.get(candidate.identifier, {}).get("stage")
            if stage in stage_seeds:
                current_fingerprints[candidate.identifier] = {
                    stage: candidate_fingerprint(candidate, stage_seeds[stage],
                                                 prototypes=prototypes, objects=objects)
                }
        if history:
            if args.restart:
                history = dict(history, functions=[])
            entries, matched = resume_report(
                destination, entries, current_fingerprints, mode=mode, payload=history,
            )
        before_cache = len(candidates)
        candidates = [candidate for candidate in candidates
                      if entries[candidate.identifier].outcome == "not_attempted"]
        cache_hits = before_cache - len(candidates)
        if cache_hits:
            print(f"CACHE: {cache_hits} unchanged outcome(s) skipped; --restart explicitly retries them")
        carried_matches = set(matched)
        for candidate in candidates:
            if not args.all and (
                len(set(matched) - carried_matches) >= args.limit or attempts >= args.max_attempts
            ):
                break
            active_candidate = candidate
            source_path = ROOT / candidate.source
            source_before = source_path.read_bytes() if source_path.is_file() else None
            prepare_candidate_log(candidate.identifier, verbose=not compact)
            attempted_symbols.append(candidate.identifier)
            (ROOT / f"build/us/automate/artifacts/{candidate.identifier}/starter.c").unlink(missing_ok=True)
            attempts += 1
            if args.analyze and isinstance(
                candidate, automation_common.RawCandidate
            ):
                result = analyze_raw_candidate(candidate, verbose=not compact)
            elif args.analyze:
                result = analyze_deferred_candidate(candidate, verbose=not compact)
            elif isinstance(candidate, automation_common.RawCandidate):
                result = try_raw_candidate(
                    candidate,
                    budget=args.rewrite_budget,
                    defer_best=args.defer_best,
                    verbose=not compact,
                    exhaustive=args.exhaustive,
                    stack_shapes=args.stack_shapes,
                )
            else:
                result = try_deferred_candidate(
                    candidate,
                    budget=args.rewrite_budget,
                    verbose=not compact,
                    exhaustive=args.exhaustive,
                    stack_shapes=args.stack_shapes,
                )
            log = candidate_log_path(candidate.identifier)
            result = classify_attempt(result)
            source_after = source_path.read_bytes() if source_path.is_file() else None
            if source_after != source_before:
                prototypes = call_signatures.signature_index(ROOT)
                objects = declaration_facts.object_evidence_index(ROOT)
            result_stage = result.stage or "prepare"
            result = replace(
                result,
                fingerprint=candidate_fingerprint(candidate, stage_seeds[result_stage],
                                                  prototypes=prototypes, objects=objects),
                stage_fingerprint=stage_seeds[result_stage],
                candidate_artifact=(result.candidate_artifact or (
                    f"build/us/automate/artifacts/{candidate.identifier}/starter.c"
                    if (ROOT / f"build/us/automate/artifacts/{candidate.identifier}/starter.c").is_file() else None)),
                previous_score=(candidate.current_score if isinstance(candidate, automation_common.DeferredCandidate) else None),
                command_log=(
                    str(log.relative_to(ROOT))
                    if not args.analyze and log.is_file()
                    else None
                ),
            )
            entries[result.symbol] = result
            if not args.analyze:
                matched = [symbol for symbol in matched if symbol != result.symbol]
                if result.outcome == "matched":
                    matched.append(result.symbol)
                elif result.outcome in {"deferred", "preserved"}:
                    deferred.append(result.symbol)
            write_run_report(
                destination,
                entries,
                full_scan=args.all,
                scan_complete=False,
                attempts=attempts,
                batch_verified=False,
                pending_batch=matched,
                mode=mode,
                tool_fingerprint=tool_fingerprint,
                stage_fingerprints=stage_seeds,
            )
            if compact:
                if not args.all:
                    print(f"RESULT {result.symbol}: {result.outcome}; {result.blocker_code or result.stage}; "
                          f"{result.detail[:240]}")
                    if result.command_log:
                        print(f"  log: {result.command_log}")
                    if result.candidate_artifact:
                        print(f"  candidate: {result.candidate_artifact}")
                progress = run_progress(entries, matched)
                emit_compact_progress(
                    result,
                    attempts=attempts,
                    total=len(candidates),
                    pending_matches=len(matched),
                    new_matches=progress["new_exact_matches"],
                    score_improvements=progress["deferred_improvements"],
                )
            active_candidate = None
        scan_complete = args.all or attempts == len(candidates)

        if args.analyze:
            write_run_report(
                destination,
                entries,
                full_scan=True,
                scan_complete=scan_complete,
                attempts=attempts,
                batch_verified=False,
                mode=mode,
                tool_fingerprint=tool_fingerprint,
                stage_fingerprints=stage_seeds,
            )
            print(
                f"Analysis complete: {attempts} candidate(s) inspected without "
                "editing tracked project state."
            )
            print(
                "Analysis report: "
                + str(
                    destination.relative_to(ROOT)
                    if destination.is_relative_to(ROOT)
                    else destination
                )
            )
            return 0

        if matched:
            matched, dropped = reconcile_pending_batch(
                matched, initial_report_entries()
            )
            if dropped:
                print(
                    "Dropped stale pending batch ID(s) that changed state during "
                    "the scan: " + " ".join(dropped)
                )

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
                write_run_report(
                    destination,
                    entries,
                    full_scan=args.all,
                    scan_complete=scan_complete,
                    attempts=attempts,
                    batch_verified=False,
                    pending_batch=matched,
                    mode=mode,
                    tool_fingerprint=tool_fingerprint,
                    stage_fingerprints=stage_seeds,
                )
                return status
            batch_verified = True
        else:
            batch_verified = True
        write_run_report(
            destination,
            entries,
            full_scan=args.all,
            scan_complete=scan_complete,
            attempts=attempts,
            batch_verified=batch_verified,
            pending_batch=[] if batch_verified else matched,
            verified_batch=matched if batch_verified else [],
            metrics={
                "elapsed_seconds": round(time.monotonic() - started, 3),
                "cache_hits": cache_hits,
                "attempted_symbols": attempted_symbols,
                "new_batch_verified_matches": len(set(matched) - carried_matches) if batch_verified else 0,
                "carried_batch_verified_matches": len(set(matched) & carried_matches) if batch_verified else 0,
                "model_tokens": args.model_tokens,
                "new_verified_matches_per_1000_tokens": (
                    1000 * len(set(matched) - carried_matches) / args.model_tokens
                    if batch_verified and args.model_tokens else None
                ),
                "command_log_bytes": sum(candidate_log_path(symbol).stat().st_size
                    for symbol in attempted_symbols if candidate_log_path(symbol).is_file()),
            },
            mode=mode,
            tool_fingerprint=tool_fingerprint,
            stage_fingerprints=stage_seeds,
        )
    except KeyboardInterrupt:
        if active_candidate is not None:
            inventory = ROOT / "progress/functions.json"
            if inventory.is_file() and automation_common.entry_is_complete(active_candidate.identifier):
                if active_candidate.identifier not in matched:
                    matched.append(active_candidate.identifier)
                entries[active_candidate.identifier] = AttemptResult(
                    active_candidate.identifier, active_candidate.source, "inventory", "matched",
                    "exact match recorded before interruption; final batch gate remains required", 0,
                    stage="finish",
                )
        if entries:
            write_run_report(
                destination, entries, full_scan=args.all, scan_complete=False,
                attempts=attempts, batch_verified=False, pending_batch=matched,
                mode=mode, tool_fingerprint=tool_fingerprint, stage_fingerprints=stage_seeds,
            )
        print("Interrupted: candidate state preserved and coverage saved; rerun the same command to resume.")
        if matched:
            print("Required batch gate: ./conker verify-batch " + " ".join(matched))
        return 130
    except (
        automation_common.AutomationError,
        candidate_rewrites.CandidateError,
        project_state.ProjectStateError,
        OSError,
        ValueError,
    ) as error:
        if entries:
            write_run_report(
                destination,
                entries,
                save_history=False,
                full_scan=args.all,
                scan_complete=False,
                attempts=attempts,
                batch_verified=False,
                pending_batch=matched,
                mode=mode,
                tool_fingerprint=tool_fingerprint,
                stage_fingerprints=stage_seeds,
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
