#!/usr/bin/env python3
"""Find matched twins of a raw or deferred work item in the US reference assembly.

Every per-function block under the independently generated reference assembly
is normalised into an instruction stream at three levels:

* level 0 strips ``%hi``/``%lo`` relocations, ``.L`` branch labels and
  ``func_``/``D_``/``jtbl_`` symbol names;
* level 1 additionally strips registers;
* level 2 additionally strips immediates.

Functions with identical streams at a level are twins at that level. A twin that
is already ``matched`` in ``progress/functions.json`` supplies a proven C body
for the same code shape. The result is a lead, never match evidence: the copied
C still needs the ordinary ``finish`` gates against the item's own assembly.

The normalised index is cached under ``build/reference-index/siblings-<level>.json``
and keyed by the reference directory mtimes, like ``matching_history.reference_files``.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import project_state


ROOT = Path(__file__).resolve().parent.parent
LEVELS = (0, 1, 2)
SCHEMA_VERSION = 1
# Reference roots searched, with the inventory overlays they cover.
REFERENCE_ROOTS = (
    ("game", "reference/game/us/asm"),
    ("main", "reference/us/asm"),
)

GLABEL_PATTERN = re.compile(r"^\s*glabel\s+([A-Za-z_][A-Za-z0-9_]*)\s*$")
FUNCTION_END_PATTERN = re.compile(r"^\s*(?:endlabel\b|dlabel\b|\.size\b|\.section\b)")
INSTRUCTION_PATTERN = re.compile(
    r"^\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s*\*/\s+(\S+)\s*(.*?)\s*$"
)
RELOCATION_PATTERN = re.compile(r"%(?:hi|lo)\([^)]*\)")
LOCAL_LABEL_PATTERN = re.compile(r"\.L[0-9A-Fa-f]+\b")
SYMBOL_PATTERN = re.compile(r"\b(?:func|D|jtbl)_\w+")
REGISTER_PATTERN = re.compile(r"\$\w+")
IMMEDIATE_PATTERN = re.compile(r"-?0x[0-9A-Fa-f]+|-?\b\d+\b")


class SiblingsError(RuntimeError):
    """Raised for user-correctable input problems."""


def normalize_arguments(arguments: str, level: int) -> str:
    """Normalise one instruction's operands to the requested level."""

    if level not in LEVELS:
        raise SiblingsError(f"unsupported sibling level: {level}")
    text = RELOCATION_PATTERN.sub("REL", arguments)
    text = LOCAL_LABEL_PATTERN.sub("L", text)
    text = SYMBOL_PATTERN.sub("SYM", text)
    if level >= 1:
        text = REGISTER_PATTERN.sub("R", text)
    if level >= 2:
        text = IMMEDIATE_PATTERN.sub("N", text)
    return " ".join(text.split())


def normalize_instruction(opcode: str, arguments: str, level: int) -> str:
    normalized = normalize_arguments(arguments, level)
    return f"{opcode} {normalized}".rstrip()


def parse_reference_text(text: str) -> dict[str, list[tuple[str, str]]]:
    """Return ``{symbol: [(opcode, arguments), ...]}`` for each glabel block.

    Data directives (``.word`` and friends), ``dlabel`` blocks and anything
    outside a function label are ignored.
    """

    functions: dict[str, list[tuple[str, str]]] = {}
    current: list[tuple[str, str]] | None = None
    for line in text.splitlines():
        label = GLABEL_PATTERN.match(line)
        if label:
            current = functions.setdefault(label.group(1), [])
            continue
        if FUNCTION_END_PATTERN.match(line):
            current = None
            continue
        if current is None:
            continue
        instruction = INSTRUCTION_PATTERN.match(line)
        if instruction is None or instruction.group(1).startswith("."):
            continue
        current.append((instruction.group(1), instruction.group(2)))
    return functions


def stream(instructions: list[tuple[str, str]], level: int) -> list[str]:
    return [normalize_instruction(opcode, arguments, level) for opcode, arguments in instructions]


def stream_digest(lines: list[str]) -> str:
    return hashlib.sha1("\n".join(lines).encode("utf-8")).hexdigest()


def reference_roots() -> list[tuple[str, Path]]:
    """Return the present reference roots as ``(overlay, absolute path)``."""

    return [(overlay, ROOT / relative) for overlay, relative in REFERENCE_ROOTS
            if (ROOT / relative).is_dir()]


def reference_fingerprint(roots: list[tuple[str, Path]]) -> dict[str, int]:
    return {path.relative_to(ROOT).as_posix(): path.stat().st_mtime_ns for _, path in roots}


def index_path(level: int) -> Path:
    return ROOT / "build" / "reference-index" / f"siblings-{level}.json"


def scan_reference(roots: list[tuple[str, Path]]) -> dict[int, dict[str, dict]]:
    """Normalise every reference function once and return one index per level."""

    indexes: dict[int, dict[str, dict]] = {level: {} for level in LEVELS}
    for overlay, root in roots:
        for path in sorted(root.rglob("*.s")):
            relative = path.relative_to(ROOT).as_posix()
            for symbol, instructions in parse_reference_text(
                    path.read_text(encoding="utf-8")).items():
                if not instructions:
                    continue
                for level in LEVELS:
                    entry = {"file": relative, "overlay": overlay,
                             "count": len(instructions),
                             "digest": stream_digest(stream(instructions, level))}
                    if symbol in indexes[level]:
                        # Ambiguous labels can never establish a twin; keep the first
                        # file and mark the duplicate so lookups refuse it.
                        indexes[level][symbol]["ambiguous"] = True
                    else:
                        indexes[level][symbol] = entry
    return indexes


def write_index(level: int, fingerprint: dict[str, int], functions: dict[str, dict]) -> None:
    path = index_path(level)
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_suffix(f"{path.suffix}.tmp.{os.getpid()}")
    temporary.write_text(json.dumps({
        "schema_version": SCHEMA_VERSION, "level": level,
        "assembly_roots_mtime_ns": fingerprint, "functions": functions,
    }, indent=1, sort_keys=True) + "\n", encoding="utf-8")
    temporary.replace(path)


def cached_index(level: int, fingerprint: dict[str, int]) -> dict[str, dict] | None:
    path = index_path(level)
    if not path.is_file():
        return None
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
        if (data.get("schema_version") != SCHEMA_VERSION or data.get("level") != level
                or data.get("assembly_roots_mtime_ns") != fingerprint
                or not isinstance(data.get("functions"), dict)):
            return None
        return data["functions"]
    except (OSError, ValueError, TypeError):
        return None


def load_index(level: int, *, refresh: bool = False) -> dict[str, dict]:
    """Return ``{symbol: {file, overlay, count, digest[, ambiguous]}}`` for one level."""

    roots = reference_roots()
    if not roots:
        raise SiblingsError(
            "no reference assembly is present; run ./conker game-asm and "
            "./conker _prepare-reference --profile us first")
    fingerprint = reference_fingerprint(roots)
    if not refresh:
        cached = cached_index(level, fingerprint)
        if cached is not None:
            return cached
    indexes = scan_reference(roots)
    for other_level, functions in indexes.items():
        write_index(other_level, fingerprint, functions)
    return indexes[level]


def groups(index: dict[str, dict]) -> dict[str, list[str]]:
    """Group unambiguous symbols by normalised stream digest."""

    result: dict[str, list[str]] = {}
    for symbol, entry in index.items():
        if entry.get("ambiguous"):
            continue
        result.setdefault(entry["digest"], []).append(symbol)
    for members in result.values():
        members.sort()
    return result


def load_inventory() -> dict[str, dict]:
    """Return the US inventory keyed by US symbol, with work-item metadata attached."""

    data = json.loads((ROOT / "progress" / "functions.json").read_text(encoding="utf-8"))
    inventory: dict[str, dict] = {}
    for entry in data["functions"]:
        region = entry.get("regions", {}).get("us")
        if not region:
            continue
        inventory[region["symbol"]] = entry
    return inventory


def resolve_item(inventory: dict[str, dict], identifier: str) -> dict:
    """Resolve a work-item ID or US symbol to its inventory entry."""

    by_id = [entry for entry in inventory.values() if entry["symbol"] == identifier]
    if len(by_id) == 1:
        return by_id[0]
    if identifier in inventory:
        return inventory[identifier]
    raise SiblingsError(f"unknown US work-item ID or symbol: {identifier}")


def item_state(entry: dict) -> str:
    state = entry["regions"]["us"].get("state", "unknown")
    if state == "raw_asm" and entry.get("deferred"):
        return "deferred"
    return state


def is_raw(entry: dict) -> bool:
    return entry["regions"]["us"].get("state") == "raw_asm"


def is_matched(entry: dict) -> bool:
    return entry["regions"]["us"].get("state") == "matched" and bool(entry.get("source"))


def matched_twins(symbol: str, index: dict[str, dict], grouped: dict[str, list[str]],
                  inventory: dict[str, dict]) -> list[str]:
    """Return matched US symbols sharing ``symbol``'s normalised stream."""

    entry = index.get(symbol)
    if entry is None or entry.get("ambiguous"):
        return []
    return [other for other in grouped.get(entry["digest"], [])
            if other != symbol and other in inventory and is_matched(inventory[other])]


def unmatched_twins(symbol: str, index: dict[str, dict], grouped: dict[str, list[str]],
                    inventory: dict[str, dict]) -> list[str]:
    """Return registered raw/deferred US symbols sharing ``symbol``'s stream.

    These twins supply no C body, but one match among them serves the whole group.
    """

    entry = index.get(symbol)
    if entry is None or entry.get("ambiguous"):
        return []
    return [other for other in grouped.get(entry["digest"], [])
            if other != symbol and other in inventory and is_raw(inventory[other])]


def lowest_level_twins(symbol: str, indexes: dict[int, dict[str, dict]],
                       grouped: dict[int, dict[str, list[str]]],
                       inventory: dict[str, dict],
                       max_level: int, *, matched: bool = True) -> tuple[int, list[str]] | None:
    finder = matched_twins if matched else unmatched_twins
    for level in LEVELS:
        if level > max_level:
            break
        twins = finder(symbol, indexes[level], grouped[level], inventory)
        if twins:
            return level, twins
    return None


def load_levels(max_level: int, *, refresh: bool = False
                ) -> tuple[dict[int, dict[str, dict]], dict[int, dict[str, list[str]]]]:
    indexes = {level: load_index(level, refresh=refresh) for level in LEVELS if level <= max_level}
    return indexes, {level: groups(index) for level, index in indexes.items()}


def function_instructions(index: dict[str, dict], symbol: str) -> list[tuple[str, str]]:
    entry = index[symbol]
    functions = parse_reference_text((ROOT / entry["file"]).read_text(encoding="utf-8"))
    return functions.get(symbol, [])


def level0_differences(target: list[tuple[str, str]], twin: list[tuple[str, str]]
                       ) -> list[tuple[int, str, str]]:
    """Return ``(index, target line, twin line)`` where level-0 streams differ."""

    left = stream(target, 0)
    right = stream(twin, 0)
    differences = [(position, a, b) for position, (a, b) in enumerate(zip(left, right)) if a != b]
    for position in range(min(len(left), len(right)), max(len(left), len(right))):
        differences.append((position,
                            left[position] if position < len(left) else "",
                            right[position] if position < len(right) else ""))
    return differences


def twin_body(entry: dict) -> tuple[str | None, str | None]:
    """Return the matched twin's C definition text, or a reason it is unavailable."""

    source = ROOT / entry["source"]
    if not source.is_file():
        return None, f"source {entry['source']} is not present"
    text = source.read_text(encoding="utf-8")
    try:
        begin, end = project_state.work_item_function_span(
            text, entry["symbol"], entry["regions"]["us"]["symbol"])
    except project_state.ProjectStateError as error:
        return None, str(error)
    return text[begin:end].rstrip("\n") + "\n", None


def hint(identifier: str) -> str:
    """One-line ``sibling-twin:`` value for ``next --ready``; never raises."""

    if not reference_roots():
        return "none (reference assembly absent)"
    try:
        inventory = load_inventory()
        entry = resolve_item(inventory, identifier)
        indexes, grouped = load_levels(max(LEVELS))
        found = lowest_level_twins(entry["regions"]["us"]["symbol"], indexes, grouped,
                                   inventory, max(LEVELS))
    except (SiblingsError, OSError, ValueError, KeyError) as error:
        return f"unavailable ({error})"
    if found is None:
        return "none"
    level, twins = found
    return f"level {level} {' '.join(inventory[symbol]['symbol'] for symbol in twins[:3])}"


def print_item(identifier: str, *, max_level: int, limit: int, refresh: bool,
               show_diff: int = 20) -> int:
    inventory = load_inventory()
    entry = resolve_item(inventory, identifier)
    symbol = entry["regions"]["us"]["symbol"]
    indexes, grouped = load_levels(max_level, refresh=refresh)
    print(f"work-item: {entry['symbol']}")
    print(f"us-symbol: {symbol}")
    print(f"overlay: {entry.get('overlay', 'main')}")
    print(f"source: {entry.get('source') or 'not assigned'}")
    state = item_state(entry)
    score = (entry.get("deferred") or {}).get("current_score")
    print(f"state: {state}" + (f" (CURRENT {score})" if score is not None else ""))
    reference = indexes[0].get(symbol)
    if reference is None:
        print("instructions: not found in reference assembly")
        print("sibling-twin: none")
        return 1
    if reference.get("ambiguous"):
        print("instructions: ambiguous reference label")
        print("sibling-twin: none")
        return 1
    print(f"instructions: {reference['count']} ({reference['file']})")
    found = lowest_level_twins(symbol, indexes, grouped, inventory, max_level)
    unmatched = lowest_level_twins(symbol, indexes, grouped, inventory, max_level, matched=False)
    if unmatched is None:
        print("unmatched-twins: none")
    else:
        print(f"unmatched-twins: level {unmatched[0]} "
              + " ".join(f"{inventory[t]['symbol']}({item_state(inventory[t])})"
                         for t in unmatched[1]))
    if found is None:
        print(f"sibling-twin: none (levels 0-{max_level})")
        return 1
    level, twins = found
    print(f"sibling-twin: level {level} {' '.join(inventory[t]['symbol'] for t in twins)}")
    target_instructions = function_instructions(indexes[0], symbol)
    for twin in twins[:limit]:
        twin_entry = inventory[twin]
        twin_reference = indexes[0][twin]
        print()
        print(f"twin: {twin_entry['symbol']}")
        print(f"twin-us-symbol: {twin}")
        print(f"twin-overlay: {twin_entry.get('overlay', 'main')}")
        print(f"twin-source: {twin_entry['source']}")
        print(f"twin-instructions: {twin_reference['count']} ({twin_reference['file']})")
        print(f"instruction-count-diff: {reference['count'] - twin_reference['count']}")
        differences = level0_differences(target_instructions,
                                         function_instructions(indexes[0], twin))
        print(f"level-0-differences: {len(differences)}")
        for position, left, right in differences[:show_diff]:
            print(f"  {position:>4}: {left or '<none>'} | {right or '<none>'}")
        if len(differences) > show_diff:
            print(f"  ... ({len(differences) - show_diff} more)")
        body, reason = twin_body(twin_entry)
        if body is None:
            print(f"twin-body: unavailable ({reason})")
        else:
            print("twin-body:")
            print(body, end="")
    if len(twins) > limit:
        print()
        print(f"... ({len(twins) - limit} more twins; raise --limit)")
    return 0


def queue(inventory: dict[str, dict], indexes: dict[int, dict[str, dict]],
          grouped: dict[int, dict[str, list[str]]], max_level: int,
          *, matched: bool = True) -> list[dict]:
    """Rank raw/deferred items by twin level, then instruction count.

    With ``matched`` false, rank items whose twins are themselves raw/deferred;
    matching any one of them hands the others a proven body.
    """

    rows = []
    for symbol, entry in inventory.items():
        if not is_raw(entry) or symbol not in indexes[0]:
            continue
        found = lowest_level_twins(symbol, indexes, grouped, inventory, max_level,
                                   matched=matched)
        if found is None:
            continue
        level, twins = found
        rows.append({
            "level": level, "count": indexes[0][symbol]["count"],
            "id": entry["symbol"], "us_symbol": symbol, "state": item_state(entry),
            "score": (entry.get("deferred") or {}).get("current_score"),
            "source": entry.get("source") or "not assigned",
            "twins": [inventory[twin]["symbol"] for twin in twins],
        })
    rows.sort(key=lambda row: (row["level"], row["count"], row["id"]))
    return rows


def print_queue(*, max_level: int, limit: int | None, refresh: bool,
                unmatched: bool = False) -> int:
    inventory = load_inventory()
    indexes, grouped = load_levels(max_level, refresh=refresh)
    rows = queue(inventory, indexes, grouped, max_level, matched=not unmatched)
    kind = "a raw/deferred twin and no matched one" if unmatched else "a matched twin"
    print(f"# raw/deferred US items with {kind}; lowest level first, then size")
    print("# level instructions state score work-item source <= twins")
    for row in rows[:limit]:
        score = "-" if row["score"] is None else str(row["score"])
        print(f"{row['level']} {row['count']:>4} {row['state']:<8} {score:>5} {row['id']} "
              f"{row['source']} <= {' '.join(row['twins'][:3])}")
    if limit is not None and len(rows) > limit:
        print(f"# ... ({len(rows) - limit} more; raise --limit)")
    print(f"# total: {len(rows)}")
    return 0


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("identifier", nargs="?", help="work-item ID or US symbol")
    parser.add_argument("--all-deferred", action="store_true",
                        help="list every raw/deferred item with a matched twin as a queue")
    parser.add_argument("--hint", action="store_true",
                        help="print only a one-line sibling-twin: hint for next --ready")
    parser.add_argument("--level", type=int, choices=LEVELS, default=max(LEVELS),
                        help="loosest normalisation level to search (default 2)")
    parser.add_argument("--limit", type=int, default=None,
                        help="twins to print per item (default 3) or queue rows (default all)")
    parser.add_argument("--unmatched", action="store_true",
                        help="with --all-deferred, list items whose only twins are raw/deferred")
    parser.add_argument("--refresh", action="store_true", help="rebuild the cached index")
    args = parser.parse_args(argv)
    if args.all_deferred == (args.identifier is not None):
        parser.error("give exactly one of <work-item-id> or --all-deferred")
    if args.hint and args.all_deferred:
        parser.error("--hint needs a work-item ID")
    if args.unmatched and not args.all_deferred:
        parser.error("--unmatched needs --all-deferred")
    if args.limit is not None and args.limit < 1:
        parser.error("--limit must be positive")
    return args


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    try:
        if args.hint:
            print(f"sibling-twin: {hint(args.identifier)}")
            return 0
        if args.all_deferred:
            return print_queue(max_level=args.level, limit=args.limit, refresh=args.refresh,
                               unmatched=args.unmatched)
        return print_item(args.identifier, max_level=args.level,
                          limit=args.limit or 3, refresh=args.refresh)
    except SiblingsError as error:
        print(f"error: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
