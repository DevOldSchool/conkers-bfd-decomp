#!/usr/bin/env python3
"""Run a bounded, semantics-preserving source-shape search for one C candidate."""

from __future__ import annotations

import argparse
import itertools
import json
import re
import subprocess
import sys
import time
from pathlib import Path

import compile_c
import candidate_rewrites
import candidate_syntax
import candidate_lifetimes
import diff
import project_state


ROOT = Path(__file__).resolve().parent.parent
DECLARATION = re.compile(
    r"^(?P<indent>[ \t]+)(?P<type>(?:(?:const|signed|unsigned)\s+)*"
    r"(?:struct\s+[A-Za-z_]\w*|[A-Za-z_]\w*)(?:[ \t]*\*)*)"
    r"(?:(?<=\*)[ \t]*|[ \t]+)(?P<name>[A-Za-z_]\w*)[ \t]*;[ \t]*$",
    re.MULTILINE,
)


class PermuteError(ValueError):
    """Raised when a candidate cannot be searched safely."""


def work_item(identifier: str, profile: str) -> tuple[dict, str]:
    inventory = json.loads(
        (ROOT / "progress" / "functions.json").read_text(encoding="utf-8")
    )
    entry = next(
        (function for function in inventory["functions"] if function["symbol"] == identifier),
        None,
    )
    if entry is None:
        raise PermuteError(f"unknown work-item ID: {identifier}")
    region = entry.get("regions", {}).get(profile)
    if region is None:
        raise PermuteError(f"{identifier} is not registered for {profile}")
    source = entry.get("source")
    if not isinstance(source, str) or not source:
        raise PermuteError(f"{identifier} has no assigned source")
    return entry, region["symbol"]


def active_candidate_content(entry: dict, identifier: str) -> tuple[Path, str]:
    source = ROOT / entry["source"]
    content = source.read_text(encoding="utf-8")
    if entry.get("deferred"):
        content = diff.activate_deferred_candidate(content, source, identifier)
    elif project_state.global_asm_pragma(entry["source"], identifier) in content:
        raise PermuteError(
            f"{identifier} has no active or preserved C candidate to permute"
        )
    return source, content


def declaration_variants(function: str, budget: int) -> list[str]:
    """Vary declaration order and first-assignment scope without changing behavior."""

    # Only the initial, top-level declaration block is eligible. Nested block
    # declarations and expression statements must never become type evidence.
    opening = function.find("{")
    declarations = []
    cursor = opening + 1
    for declaration in DECLARATION.finditer(function, cursor):
        if function[cursor:declaration.start()].strip():
            break
        if declaration.group("type") in ("return", "goto", "volatile"):
            break
        declarations.append(declaration)
        cursor = declaration.end()
    if not declarations:
        return [function]
    start = declarations[0].start()
    end = declarations[-1].end()
    between = function[start:end]
    if any(
        part.strip()
        for part in DECLARATION.sub("", between).splitlines()
    ):
        return [function]

    declaration_lines = [match.group(0) for match in declarations]
    variants: list[str] = []
    seen: set[str] = set()

    def retain(candidate: str) -> None:
        if candidate not in seen and len(variants) < budget:
            seen.add(candidate)
            variants.append(candidate)

    def lifetimes(base: str):
        if re.search(r"\bgoto\b|(?m:^[ \t]*[A-Za-z_]\w*\s*:)", base):
            return
        for declaration in declarations:
            name = declaration.group("name")
            type_name = declaration.group("type")
            indent = declaration.group("indent")
            declaration_pattern = re.compile(
                rf"^{re.escape(declaration.group(0))}\n?",
                re.MULTILINE,
            )
            without_declaration, removed = declaration_pattern.subn("", base, count=1)
            if removed != 1:
                continue
            assignment = re.compile(
                rf"^(?P<indent>[ \t]+){re.escape(name)}[ \t]*=[ \t]*(?P<expr>[^;\n]+);[ \t]*$",
                re.MULTILINE,
            )
            match = assignment.search(without_declaration)
            if match is None:
                continue
            prefix = without_declaration[: match.start()]
            prefix_tokens = candidate_syntax.tokens(prefix)
            if not prefix_tokens or prefix_tokens[-1].text not in ("{", ";", "}"):
                # An unbraced if/else/loop body must not acquire a scope that
                # swallows the rest of the function.
                continue
            preceding = candidate_syntax.tokens(prefix + match.group("expr"))
            if any(
                token.text == name and (index == 0 or preceding[index - 1].text not in (".", "->"))
                for index, token in enumerate(preceding)
            ):
                continue
            brace_depth = 0
            for token in prefix_tokens:
                brace_depth += (token.text == "{") - (token.text == "}")
            if brace_depth != 1:
                continue
            initialized = (
                f"{match.group('indent')}{{\n"
                f"{match.group('indent')}    {type_name} {name} = "
                f"{match.group('expr')};"
            )
            closing = without_declaration.rfind("}")
            if closing < match.end():
                continue
            yield (
                without_declaration[: match.start()]
                + initialized
                + without_declaration[match.end() : closing]
                + f"{match.group('indent')}}}\n"
                + without_declaration[closing:]
            )
    retain(function)
    # Interleave declaration order and first-assignment scope variants.
    orders = (
        function[:start] + "\n".join(order) + function[end:]
        for order in itertools.permutations(declaration_lines)
    )
    families = [iter(candidate_lifetimes.lifetime_variants(function, declarations)),
                iter(lifetimes(function)), iter(orders)]
    while families and len(variants) < budget:
        remaining = []
        for family in families:
            try:
                retain(next(family))
                remaining.append(family)
            except StopIteration:
                pass
        families = remaining
    return variants


def source_variants(function: str, budget: int) -> list[str]:
    """Combine lifetime permutations with bounded expression-form rewrites."""

    declaration_budget = max(1, (budget + 1) // 2)
    seeds = declaration_variants(function, declaration_budget)
    return candidate_rewrites.rewrite_variants(seeds, budget)


def score_candidate(
    profile: str,
    symbol: str,
    source_content: str,
    directory: Path,
    reference: Path,
    expected_size: int,
) -> int:
    candidate_source = directory / "candidate.c"
    candidate_object = directory / "candidate.o"
    candidate_source.write_text(
        diff.GLOBAL_ASM_LINE.sub("", source_content), encoding="utf-8"
    )
    subprocess.run(
        compile_c.compile_command(profile, candidate_source, candidate_object),
        cwd=ROOT,
        check=True,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )
    result = subprocess.run(
        diff.asm_diff_command(
            candidate_object,
            reference,
            symbol,
            expected_size,
            require_match=True,
        ),
        cwd=directory,
        check=True,
        capture_output=True,
        text=True,
    )
    return diff.current_difference_count(result.stdout)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("profile", choices=("us", "eu"))
    parser.add_argument("identifier")
    parser.add_argument("--budget", type=int, default=250)
    parser.add_argument("--exhaustive", action="store_true",
                        help="use the full variant budget instead of stopping after 32 attempts without improvement")
    args = parser.parse_args()
    if args.budget < 1 or args.budget > 5000:
        parser.error("--budget must be between 1 and 5000")

    try:
        entry, symbol = work_item(args.identifier, args.profile)
        source, active_content = active_candidate_content(entry, args.identifier)
        function_start, function_end = project_state.c_function_span(
            active_content, symbol
        )
        original_function = active_content[function_start:function_end].rstrip("\n")
        variants = source_variants(original_function, args.budget)
        reference_assembly = diff.ensure_reference_function(
            args.profile,
            symbol,
            game_reference=entry.get("overlay", "main") == "game",
        )
        reference = diff.reference_object(
            args.profile,
            symbol,
            game_reference=entry.get("overlay", "main") == "game",
            assembly=reference_assembly,
        )
        expected_size = diff.expected_function_size(args.profile, symbol)
        directory = ROOT / "build" / args.profile / "permute" / args.identifier
        directory.mkdir(parents=True, exist_ok=True)
        best_path = directory / "best.c"
        best_path.unlink(missing_ok=True)

        best_score: int | None = None
        best_function = original_function
        exact_function: str | None = None
        started = time.monotonic()
        attempted = 0
        skipped = 0
        last_improvement = 0
        improvements = 0
        stop_reason = "variants_exhausted"
        for variant in variants:
            if not args.exhaustive and attempted + skipped >= max(32, last_improvement + 32):
                stop_reason = "plateau"
                break
            candidate_content = (
                active_content[:function_start]
                + variant
                + "\n"
                + active_content[function_end:]
            )
            try:
                score = score_candidate(
                    args.profile,
                    symbol,
                    candidate_content,
                    directory,
                    reference,
                    expected_size,
                )
            except subprocess.CalledProcessError:
                skipped += 1
                continue
            attempted += 1
            if best_score is None:
                best_score = score
                best_function = variant
                best_path.write_text(best_function + "\n", encoding="utf-8")
                print(f"{args.identifier}: baseline CURRENT ({score}) at variant {attempted}")
            elif score < best_score:
                best_score = score
                best_function = variant
                best_path.write_text(best_function + "\n", encoding="utf-8")
                last_improvement = attempted + skipped
                improvements += 1
                print(f"{args.identifier}: improved CURRENT ({score}) at variant {attempted}")
            if score == 0:
                exact_function = variant
                stop_reason = "exact"
                break

        summary = {
            "budget": args.budget, "exhaustive": args.exhaustive,
            "generated": len(variants), "compiled": attempted, "invalid": skipped,
            "improvements": improvements, "best_score": best_score,
            "stop_reason": stop_reason, "elapsed_seconds": time.monotonic() - started,
        }
        report = directory / "search-report.json"
        temporary = report.with_suffix(".json.tmp")
        temporary.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
        temporary.replace(report)
        if exact_function is None:
            print(
                f"{args.identifier}: no exact match in {attempted} variant(s); "
                f"best CURRENT ({best_score}) saved to {best_path.relative_to(ROOT)}"
                + (f"; {skipped} invalid variant(s) skipped" if skipped else "")
                + ("; plateau reached (use --exhaustive for the full budget)" if stop_reason == "plateau" else "")
            )
            return 1

        print(
            f"{args.identifier}: exact variant {attempted} saved to "
            f"{best_path.relative_to(ROOT)}; host application and "
            "authoritative finish required"
        )
        return 0
    except (
        PermuteError,
        ValueError,
        OSError,
        subprocess.CalledProcessError,
        project_state.ProjectStateError,
    ) as error:
        print(f"error: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
