#!/usr/bin/env python3
"""Locate a generated function and produce an m2c C starter for it."""

from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
LABEL_PATTERN = re.compile(r"^glabel\s+([A-Za-z_][A-Za-z0-9_]*)\s*$", re.MULTILINE)
MIPS_TO_C = Path(os.environ.get("CONKER_MIPS_TO_C", "/opt/tools/mips_to_c/m2c.py"))


def reference_index_path(profile: str, *, game_reference: bool) -> Path:
    kind = "game" if game_reference else "main"
    return ROOT / "build" / "reference-index" / f"{kind}-{profile}.json"


def scan_reference_functions(assembly_root: Path) -> dict[str, list[str]]:
    symbols: dict[str, list[str]] = {}
    for path in sorted(assembly_root.rglob("*.s")):
        relative = str(path.relative_to(assembly_root))
        for match in LABEL_PATTERN.finditer(path.read_text(encoding="utf-8")):
            symbols.setdefault(match.group(1), []).append(relative)
    return symbols


def indexed_reference_candidates(
    assembly_root: Path,
    profile: str,
    symbol: str,
    *,
    game_reference: bool,
) -> list[Path] | None:
    """Return validated cached candidates, or None when the index needs rebuilding."""

    cache = reference_index_path(profile, game_reference=game_reference)
    if not cache.is_file():
        return None
    try:
        index = json.loads(cache.read_text(encoding="utf-8"))
        if index.get("schema_version") != 1:
            return None
        if index.get("assembly_root_mtime_ns") != assembly_root.stat().st_mtime_ns:
            return None
        relatives = index["symbols"].get(symbol, [])
        candidates = [assembly_root / relative for relative in relatives]
    except (OSError, ValueError, KeyError, TypeError):
        return None
    pattern = re.compile(rf"^glabel\s+{re.escape(symbol)}\s*$", re.MULTILINE)
    if any(
        not path.is_file() or not pattern.search(path.read_text(encoding="utf-8"))
        for path in candidates
    ):
        return None
    return candidates


def write_reference_index(
    assembly_root: Path,
    profile: str,
    symbols: dict[str, list[str]],
    *,
    game_reference: bool,
) -> None:
    cache = reference_index_path(profile, game_reference=game_reference)
    cache.parent.mkdir(parents=True, exist_ok=True)
    temporary = cache.with_suffix(f"{cache.suffix}.tmp.{os.getpid()}")
    temporary.write_text(
        json.dumps(
            {
                "schema_version": 1,
                "assembly_root_mtime_ns": assembly_root.stat().st_mtime_ns,
                "symbols": symbols,
            },
            indent=2,
            sort_keys=True,
        )
        + "\n",
        encoding="utf-8",
    )
    temporary.replace(cache)


def locate_function(
    profile: str,
    symbol: str,
    *,
    reference: bool = False,
    game_reference: bool = False,
) -> Path:
    if reference and game_reference:
        raise ValueError("choose either the ROM reference or the game-code reference")
    pattern = re.compile(rf"^glabel\s+{re.escape(symbol)}\s*$", re.MULTILINE)
    if game_reference:
        assembly_root = ROOT / "reference" / "game" / profile / "asm"
    else:
        assembly_root = ROOT / ("reference" if reference else "asm") / profile
    if reference:
        assembly_root /= "asm"
    if (reference or game_reference) and assembly_root.is_dir():
        candidates = indexed_reference_candidates(
            assembly_root,
            profile,
            symbol,
            game_reference=game_reference,
        )
        if candidates is None:
            symbols = scan_reference_functions(assembly_root)
            write_reference_index(
                assembly_root,
                profile,
                symbols,
                game_reference=game_reference,
            )
            candidates = [assembly_root / relative for relative in symbols.get(symbol, [])]
    elif assembly_root.is_dir():
        candidates = [
            path
            for path in sorted(assembly_root.rglob("*.s"))
            if pattern.search(path.read_text(encoding="utf-8"))
        ]
    else:
        candidates = []
    if not candidates:
        raise ValueError(
            f"{symbol} was not found in {assembly_root.relative_to(ROOT)}; generate its reference assembly first"
        )
    if len(candidates) > 1:
        names = ", ".join(str(path.relative_to(ROOT)) for path in candidates)
        raise ValueError(f"{symbol} occurs in multiple assembly files: {names}")
    return candidates[0]


def resolve_work_item(profile: str, identifier: str) -> tuple[str, Path, str, bool]:
    """Resolve a work-item ID or regional symbol and whether it uses the game overlay."""

    inventory = json.loads(
        (ROOT / "progress" / "functions.json").read_text(encoding="utf-8")
    )
    exact_identifier = [
        entry for entry in inventory["functions"] if entry["symbol"] == identifier
    ]
    candidates = exact_identifier or [
        entry
        for entry in inventory["functions"]
        if (region := entry["regions"].get(profile)) is not None
        and region["symbol"] == identifier
    ]
    if not candidates:
        raise ValueError(f"unknown work-item ID or {profile} symbol: {identifier}")
    if len(candidates) > 1:
        raise ValueError(f"{identifier} resolves to multiple {profile} work items")
    entry = candidates[0]
    region = entry["regions"].get(profile)
    if region is None:
        raise ValueError(f"{entry['symbol']} is not registered for the {profile} profile")
    return (
        entry["symbol"],
        ROOT / entry["source"],
        region["symbol"],
        entry.get("overlay", "main") == "game",
    )


def nonmatching_function_source(source: Path, identifier: str, symbol: str) -> Path | None:
    """Return the existing raw per-function assembly for a reviewed game unit."""

    try:
        relative = source.relative_to(ROOT / "src" / "game").with_suffix("")
    except ValueError:
        return None
    path = ROOT / "asm" / "nonmatchings" / relative / f"{identifier}.s"
    if not path.is_file():
        return None
    labels = [match.group(1) for match in LABEL_PATTERN.finditer(path.read_text(encoding="utf-8"))]
    return path if labels == [symbol] else None


def prepare_reference(profile: str, *, game_reference: bool) -> None:
    if os.environ.get("CONKER_HOST_M2C") == "1":
        command = [
            str(ROOT / "conker"),
            "game-asm" if game_reference else "_prepare-reference",
            "--profile",
            profile,
        ]
    elif game_reference:
        command = ["make", "game-asm", f"GAME_REFERENCE_PROFILE={profile}"]
    else:
        command = ["make", "prepare-reference", f"PROFILE={profile}"]
    subprocess.run(command, cwd=ROOT, check=True, stdout=sys.stderr)


def ensure_reference_function(profile: str, symbol: str, *, game_reference: bool) -> Path:
    """Locate a raw reference function, generating the split only when needed."""

    try:
        return locate_function(
            profile,
            symbol,
            reference=not game_reference,
            game_reference=game_reference,
        )
    except ValueError:
        prepare_reference(profile, game_reference=game_reference)
        return locate_function(
            profile,
            symbol,
            reference=not game_reference,
            game_reference=game_reference,
        )


def existing_reference_function(
    profile: str, symbol: str, *, game_reference: bool
) -> Path | None:
    """Return an already-generated raw reference without regenerating its split."""

    try:
        return locate_function(
            profile,
            symbol,
            reference=not game_reference,
            game_reference=game_reference,
        )
    except ValueError as error:
        if "was not found" not in str(error):
            raise
        return None


def locate_registered_function(profile: str, identifier: str) -> tuple[Path, str]:
    work_item, source, symbol, game_reference = resolve_work_item(profile, identifier)
    if game_reference:
        reference = existing_reference_function(
            profile, symbol, game_reference=True
        )
        if reference is not None:
            return reference, symbol
        nonmatching = nonmatching_function_source(source, work_item, symbol)
        if nonmatching is not None:
            return nonmatching, symbol
    return ensure_reference_function(profile, symbol, game_reference=game_reference), symbol


def extract_function(source: Path, symbol: str) -> Path:
    """Write only one function and its assembler preamble for m2c."""
    text = source.read_text(encoding="utf-8")
    labels = list(LABEL_PATTERN.finditer(text))
    target_index = next(index for index, label in enumerate(labels) if label.group(1) == symbol)
    target = labels[target_index]
    end = labels[target_index + 1].start() if target_index + 1 < len(labels) else len(text)
    preamble = text[: labels[0].start()]

    output = ROOT / "build" / "m2c" / source.parent.name / f"{symbol}.s"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(preamble + text[target.start() : end], encoding="utf-8")
    return output


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("profile", choices=("us", "eu"))
    parser.add_argument("symbol")
    source_kind = parser.add_mutually_exclusive_group()
    source_kind.add_argument("--reference", action="store_true")
    source_kind.add_argument("--game-reference", action="store_true")
    source_kind.add_argument(
        "--auto-overlay",
        action="store_true",
        help="resolve the registered work item and prefer existing per-function assembly",
    )
    args = parser.parse_args()
    try:
        if args.auto_overlay:
            source, symbol = locate_registered_function(args.profile, args.symbol)
        else:
            symbol = args.symbol
            source = locate_function(
                args.profile,
                symbol,
                reference=args.reference,
                game_reference=args.game_reference,
            )
    except (ValueError, subprocess.CalledProcessError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    extracted_source = extract_function(source, symbol)

    command = [
        "python3",
        str(MIPS_TO_C),
        "--target",
        "mips-ido-c",
        "--valid-syntax",
        "--function",
        symbol,
        str(extracted_source.relative_to(ROOT)),
    ]
    return subprocess.run(command, cwd=ROOT, check=False).returncode


if __name__ == "__main__":
    raise SystemExit(main())
