#!/usr/bin/env python3
"""Merge policy for unattended matching PRs.

An auto-match PR may change matched C bodies, the function inventory and the
evidence that integration records. Anything that changes a shared contract
(headers, build inputs, tooling, linker configuration beyond additive rodata
mappings) or that smells like a forced match stops automation and waits for a
maintainer. The check reads only Git; it never builds or compares.

Usage: auto_policy.py --repo PATH --base REF --head REF --ids ID [ID ...] [--json]
Exit status 0 means the policy passed, 1 means a finding stops the merge.
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from dataclasses import dataclass, field
from pathlib import PurePosixPath

INVENTORY = "progress/functions.json"
SOURCE_UNITS = "progress/source_units.json"
SOURCE_MAP = "config/game/us.yaml"
ADDITIVE_ONLY = {"config/game/us-rodata.ld"}
ALLOWED_EXACT = {INVENTORY, SOURCE_UNITS, SOURCE_MAP} | ADDITIVE_ONLY
DONE_MOVE = re.compile(r"(?<![\w/])(?:src/)?game/")
ALLOWED_TREES = ("docs/evidence/",)
SOURCE_TREES = ("src/",)

FORCED_MATCH_PATTERNS = (
    (re.compile(r"\bif\s*\(\s*1\s*\)\s*\{\s*\}"), "empty `if (1) {}` is a fake match"),
    (re.compile(r"\^\s*0\b"), "`^ 0` is a fake match"),
    (re.compile(r"\bdo\s*\{\s*\}\s*while\s*\(\s*0\s*\)"), "empty `do {} while (0)` is a fake match"),
    (re.compile(r"\bvolatile\b"), "new `volatile` qualifier needs review"),
    (re.compile(r"#\s*pragma\s+GLOBAL_ASM"), "a GLOBAL_ASM pragma was added"),
    (re.compile(r"\b(asm|__asm__)\s*\("), "inline assembly"),
    (re.compile(r"#\s*include\b"), "a new include changes shared visibility"),
    (re.compile(r"#\s*(if|ifdef|ifndef)\b"), "a new preprocessor condition needs review"),
)


@dataclass
class Result:
    findings: list[str] = field(default_factory=list)
    notes: list[str] = field(default_factory=list)

    @property
    def passed(self) -> bool:
        return not self.findings


def git(repo: str, *args: str) -> str:
    return subprocess.check_output(["git", "-C", repo, *args], text=True)


def changed_files(repo: str, base: str, head: str) -> list[tuple[str, str, str]]:
    out = git(repo, "diff", "--name-status", "-M", "-z", f"{base}...{head}")
    parts = out.split("\0")
    rows: list[tuple[str, str, str]] = []
    i = 0
    while i < len(parts) and parts[i]:
        status = parts[i]
        if status[0] in "RC":
            rows.append((status[0], parts[i + 1], parts[i + 2]))
            i += 3
        else:
            rows.append((status[0], parts[i + 1], parts[i + 1]))
            i += 2
    return rows


def path_allowed(path: str) -> bool:
    if path in ALLOWED_EXACT or path.startswith(ALLOWED_TREES):
        return True
    p = PurePosixPath(path)
    return path.startswith(SOURCE_TREES) and p.suffix == ".c"


def check_paths(repo: str, base: str, head: str, result: Result) -> list[tuple[str, str]]:
    sources: list[tuple[str, str]] = []
    for status, old, new in changed_files(repo, base, head):
        for path in {old, new}:
            if not path_allowed(path):
                result.findings.append(f"{path}: outside the auto-merge scope ({status})")
        if status == "D":
            result.findings.append(f"{old}: deleted")
        if new.endswith(".c") and status != "D":
            sources.append((old, new))
        if status == "R":
            result.notes.append(f"{old} -> {new}")
    return sources


def file_diff(repo: str, base: str, head: str, *paths: str) -> str:
    # Pass both names of a renamed file so Git still pairs them instead of
    # reporting the whole file as added.
    return git(repo, "diff", "-U0", "-M", f"{base}...{head}", "--", *sorted(set(paths)))


def added_lines(repo: str, base: str, head: str, *paths: str) -> list[tuple[int, str]]:
    diff = file_diff(repo, base, head, *paths)
    lines: list[tuple[int, str]] = []
    line_no = 0
    for raw in diff.splitlines():
        if raw.startswith("@@"):
            match = re.search(r"\+(\d+)", raw)
            line_no = int(match.group(1)) if match else 0
        elif raw.startswith("+") and not raw.startswith("+++"):
            lines.append((line_no, raw[1:]))
            line_no += 1
    return lines


def removed_lines(repo: str, base: str, head: str, path: str) -> list[str]:
    diff = file_diff(repo, base, head, path)
    return [raw[1:] for raw in diff.splitlines() if raw.startswith("-") and not raw.startswith("---")]


def check_sources(repo: str, base: str, head: str, sources: list[tuple[str, str]], result: Result) -> None:
    for old, path in sources:
        for line_no, text in added_lines(repo, base, head, old, path):
            for pattern, reason in FORCED_MATCH_PATTERNS:
                if pattern.search(text):
                    result.findings.append(f"{path}:{line_no}: {reason}: {text.strip()}")
                    break


def check_additive(repo: str, base: str, head: str, result: Result) -> None:
    for path in ADDITIVE_ONLY:
        removed = [line for line in removed_lines(repo, base, head, path) if line.strip()]
        if removed:
            result.findings.append(f"{path}: removes {len(removed)} line(s); only additions are allowed")


def is_done_move(before: str, after: str) -> bool:
    """True when `after` is `before` with one game source path moved under done/."""
    return before != after and DONE_MOVE.sub(lambda m: m.group(0).replace("game/", "done/game/"), before, count=1) == after


def check_source_map(repo: str, base: str, head: str, result: Result) -> None:
    # Integration rewrites one segment row per completed unit; anything else is a layout change.
    removed = [line for line in removed_lines(repo, base, head, SOURCE_MAP) if line.strip()]
    added = [text for _, text in added_lines(repo, base, head, SOURCE_MAP) if text.strip()]
    if not removed and not added:
        return
    unmatched = [line for line in removed if not any(is_done_move(line, new) for new in added)]
    if len(removed) != len(added) or unmatched:
        result.findings.append(f"{SOURCE_MAP}: changes other than moving completed units under done/")


def load_inventory(repo: str, ref: str) -> dict:
    """Return the inventory keyed by work-item ID (the `functions` list keyed by `symbol`)."""
    try:
        text = git(repo, "show", f"{ref}:{INVENTORY}")
    except subprocess.CalledProcessError:
        return {}
    data = json.loads(text)
    functions = data.get("functions", []) if isinstance(data, dict) else data
    return {entry.get("symbol") or entry.get("id"): entry for entry in functions}


def us_state(entry: dict) -> tuple[str, object]:
    us = entry.get("regions", {}).get("us", {})
    return us.get("state", ""), us.get("evidence", {}).get("current_differences")


def check_inventory(repo: str, base: str, head: str, ids: list[str], result: Result) -> None:
    before = load_inventory(repo, base)
    after = load_inventory(repo, head)
    claimed = set(ids)
    for key in sorted(set(before) ^ set(after)):
        result.findings.append(f"{INVENTORY}: {key} was added or removed")
    changed = {key for key in before.keys() & after.keys() if before[key] != after[key]}
    for key in sorted(changed - claimed):
        moved = dict(before[key], source=after[key].get("source"))
        if moved == after[key] and is_done_move(before[key].get("source", ""), after[key].get("source", "")):
            result.notes.append(f"{key} moved with its completed unit")
            continue
        result.findings.append(f"{INVENTORY}: {key} changed but is not a claimed match")
    for key in sorted(claimed):
        if key not in after:
            result.findings.append(f"{INVENTORY}: claimed {key} is not in the inventory")
            continue
        if key not in changed:
            result.findings.append(f"{INVENTORY}: claimed {key} has no inventory change")
            continue
        state, differences = us_state(after[key])
        if state != "matched" or differences != 0:
            result.findings.append(f"{INVENTORY}: claimed {key} is {state!r} with {differences!r} differences")
    if not claimed:
        result.findings.append("no claimed match IDs")


def evaluate(repo: str, base: str, head: str, ids: list[str]) -> Result:
    result = Result()
    sources = check_paths(repo, base, head, result)
    check_sources(repo, base, head, sources, result)
    check_additive(repo, base, head, result)
    check_source_map(repo, base, head, result)
    check_inventory(repo, base, head, ids, result)
    return result


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--repo", required=True)
    parser.add_argument("--base", required=True)
    parser.add_argument("--head", required=True)
    parser.add_argument("--ids", nargs="+", required=True)
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args(argv)
    result = evaluate(args.repo, args.base, args.head, args.ids)
    if args.json:
        print(json.dumps({"verdict": "pass" if result.passed else "fail",
                          "findings": result.findings, "notes": result.notes}, indent=2))
    else:
        print("policy: " + ("pass" if result.passed else "fail"))
        for line in result.findings:
            print(f"- {line}")
        for line in result.notes:
            print(f"  note: {line}")
    return 0 if result.passed else 1


if __name__ == "__main__":
    sys.exit(main())
