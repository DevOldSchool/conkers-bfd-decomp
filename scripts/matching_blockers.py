#!/usr/bin/env python3
"""Rank recorded blockers without compiling, changing source, or claiming matches."""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import json
import re
from pathlib import Path

import attempt_history
import project_state

ROOT = Path(__file__).resolve().parent.parent


def summarize(history: dict, functions: list[dict], limit: int) -> dict:
    inventory = {entry["symbol"]: entry for entry in functions}
    declarations: dict[str, set[str]] = defaultdict(set)
    placeholders: dict[str, set[str]] = defaultdict(set)
    counts: Counter = Counter()
    for result in history.get("functions", []):
        symbol = result["symbol"]
        current = inventory.get(symbol)
        if current is None or project_state.is_complete(current):
            continue
        code = result.get("blocker_code")
        if not code:
            continue
        counts[code] += 1
        detail = result.get("detail", "")
        if code == "declaration_evidence":
            names = detail.partition("no unique project declaration evidence for:")[2]
            for name in set(re.findall(r"\b[A-Za-z_]\w*\b", names)):
                declarations[name].add(symbol)
        elif code == "unresolved_placeholder":
            for name in set(re.findall(r"\bM2C_[A-Za-z0-9_]+\b", detail)):
                placeholders[name].add(symbol)

    def ranked(groups: dict[str, set[str]]) -> list[dict]:
        return [{"symbol": name, "dependent_count": len(dependents),
                 "examples": sorted(dependents)[:3],
                 "currently_matched": bool(name in inventory and project_state.is_complete(inventory[name]))}
                for name, dependents in sorted(groups.items(), key=lambda pair: (-len(pair[1]), pair[0]))[:limit]]

    return {"basis": "saved outcomes, excluding currently matched functions; freshness not revalidated",
            "note": "Counts overlap and are potential unblocks, not promised matches.",
            "blockers": dict(counts.most_common()),
            "declarations": ranked(declarations), "placeholders": ranked(placeholders)}


def main(arguments: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--limit", type=int, default=20)
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args(arguments)
    if args.limit < 1:
        parser.error("--limit must be positive")
    try:
        history = attempt_history.load(ROOT)
        functions = project_state.load_json(ROOT / "progress/functions.json")["functions"]
        result = summarize(history, functions, args.limit)
    except (OSError, ValueError, project_state.ProjectStateError) as error:
        parser.exit(1, f"error: {error}\n")
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        print(result["basis"])
        print(result["note"])
        for code, count in result["blockers"].items():
            print(f"{code}: {count}")
        for group in ("declarations", "placeholders"):
            print(f"{group}:")
            for item in result[group]:
                state = "; already matched: check declaration compatibility/visibility" if item["currently_matched"] else ""
                print(f"  {item['symbol']}: {item['dependent_count']} dependent(s){state}; examples: {', '.join(item['examples'])}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
