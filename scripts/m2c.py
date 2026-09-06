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
INTERNAL_GLABEL_PATTERN = re.compile(
    r"^(?P<indent>[ \t]+)glabel\s+(?P<symbol>[A-Za-z_][A-Za-z0-9_]*)\s*$",
    re.MULTILINE,
)
MIPS_TO_C = Path(os.environ.get("CONKER_MIPS_TO_C", "/opt/tools/mips_to_c/m2c.py"))
TYPES_HEADER = Path("include/types.h")
JAL_PATTERN = re.compile(r"\bjal\s+([A-Za-z_][A-Za-z0-9_]*)\b")
ARGUMENT_REGISTER_PATTERN = re.compile(r"\$a([0-3])\b")
PREPROCESSOR_PATTERN = re.compile(r"^\s*#")
TYPES_INCLUDE_PATTERN = re.compile(r'^\s*#include\s+"types\.h"\s*$')
GLOBAL_ASM_PATTERN = re.compile(r"^\s*#pragma\s+GLOBAL_ASM\b")
DISABLED_BLOCK_START_PATTERN = re.compile(r"^\s*#if\s+0(?:\s|$)")
DISABLED_BLOCK_END_PATTERN = re.compile(r"^\s*#endif\b")


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


def registered_symbols(profile: str) -> set[str]:
    """Return regional symbols that delimit registered work items."""

    inventory = json.loads(
        (ROOT / "progress" / "functions.json").read_text(encoding="utf-8")
    )
    return {
        region["symbol"]
        for entry in inventory["functions"]
        if (region := entry["regions"].get(profile)) is not None
    }


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


def extract_function(
    source: Path, symbol: str, *, boundary_symbols: set[str] | None = None
) -> Path:
    """Write one registered function and its assembler preamble for m2c.

    Raw game functions can contain globally named secondary entries. When the
    registered inventory is available, only another registered work item ends
    the extraction; internal ``glabel`` targets must remain visible to m2c.
    """
    text = source.read_text(encoding="utf-8")
    labels = list(LABEL_PATTERN.finditer(text))
    target_index = next(index for index, label in enumerate(labels) if label.group(1) == symbol)
    target = labels[target_index]
    following = labels[target_index + 1 :]
    if boundary_symbols is not None:
        following = [label for label in following if label.group(1) in boundary_symbols]
    end = following[0].start() if following else len(text)
    preamble = text[: labels[0].start()]

    extracted = preamble + text[target.start() : end]
    if boundary_symbols is not None:
        internal_symbols = [
            match.group("symbol")
            for match in INTERNAL_GLABEL_PATTERN.finditer(extracted)
        ]
        for internal_symbol in internal_symbols:
            extracted = re.sub(
                rf"\b{re.escape(internal_symbol)}\b",
                f".L{internal_symbol}",
                extracted,
            )
        extracted = INTERNAL_GLABEL_PATTERN.sub(
            lambda match: f"{match.group('indent')}.L{match.group('symbol')}:",
            extracted,
        )
        extracted = re.sub(
            r"^(?P<indent>[ \t]+)glabel\s+(?P<label>\.L[A-Za-z_][A-Za-z0-9_]*)\s*$",
            r"\g<indent>\g<label>:",
            extracted,
            flags=re.MULTILINE,
        )

    output = ROOT / "build" / "m2c" / source.parent.name / f"{symbol}.s"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(extracted, encoding="utf-8")
    return output


def callees_with_preserved_a0(assembly: str) -> set[str]:
    """Find calls whose delay slot derives a1 from an unchanged incoming a0."""

    lines = assembly.splitlines()
    callees: set[str] = set()
    for index, line in enumerate(lines[:-1]):
        call = JAL_PATTERN.search(line)
        if call is None:
            continue
        delay_slot = lines[index + 1].split("*/", 1)[-1]
        registers = ARGUMENT_REGISTER_PATTERN.findall(delay_slot)
        if registers and registers[0] == "1" and "0" in registers[1:]:
            callees.add(call.group(1))
    return callees


def split_arguments(arguments: str) -> list[str]:
    """Split a C argument list while respecting nested expressions."""

    parts: list[str] = []
    start = 0
    depth = 0
    for index, character in enumerate(arguments):
        if character in "([{":
            depth += 1
        elif character in ")]}":
            depth -= 1
        elif character == "," and depth == 0:
            parts.append(arguments[start:index].strip())
            start = index + 1
    tail = arguments[start:].strip()
    if tail:
        parts.append(tail)
    return parts


def repair_preserved_call_arguments(starter: str, assembly: str, symbol: str) -> str:
    """Restore a proven live a0 argument that mips_to_c omitted from a call."""

    signature = re.search(
        rf"^.*\b{re.escape(symbol)}\(([^)]*)\)\s*\{{",
        starter,
        re.MULTILINE,
    )
    if signature is None:
        return starter
    arg0 = re.search(r"(.+?)\s+arg0\b", signature.group(1))
    if arg0 is None:
        return starter
    arg0_type = arg0.group(1).strip()

    repaired = starter
    for callee in callees_with_preserved_a0(assembly):
        call_pattern = re.compile(
            rf"^(\s*){re.escape(callee)}\((.+)\);\s*$", re.MULTILINE
        )

        def repair_call(match: re.Match[str]) -> str:
            arguments = split_arguments(match.group(2))
            if len(arguments) != 1 or arguments[0] == "arg0":
                return match.group(0)
            return f"{match.group(1)}{callee}(arg0, {arguments[0]});"

        previous = repaired
        repaired = call_pattern.sub(repair_call, repaired)
        if repaired == previous:
            continue
        declaration_pattern = re.compile(
            rf"^(.*\b{re.escape(callee)}\()([^()\n]*)(\);.*)$", re.MULTILINE
        )

        def repair_declaration(match: re.Match[str]) -> str:
            arguments = split_arguments(match.group(2))
            if len(arguments) != 1:
                return match.group(0)
            return f"{match.group(1)}{arg0_type}, {arguments[0]}{match.group(3)}"

        repaired = declaration_pattern.sub(repair_declaration, repaired, count=1)
    return repaired


def ready_output(starter: str, symbol: str) -> str:
    """Label declarations that must accompany the bounded C starter."""

    definition = re.search(
        rf"^.*\b{re.escape(symbol)}\([^;\n]*\)\s*\{{", starter, re.MULTILINE
    )
    prefix = starter[: definition.start()] if definition is not None else ""
    declarations = [
        line.strip()
        for line in prefix.splitlines()
        if ";" in line and line.strip().endswith((";", "*/"))
    ]
    declaration_block = "\n".join(f"  {line}" for line in declarations) or "  none"
    return f"required-declarations:\n{declaration_block}\nc-starter:\n{starter}"


def flattened_types_header() -> str:
    """Return scalar aliases without include guards or other directives."""

    source = ROOT / TYPES_HEADER
    if not source.is_file():
        return ""
    return "".join(
        line
        for line in source.read_text(encoding="utf-8").splitlines(keepends=True)
        if not PREPROCESSOR_PATTERN.match(line)
    ).strip()


def flattened_source_context(source: Path) -> str | None:
    """Flatten one canonical source file into parser-ready m2c context."""

    lines: list[str] = []
    disabled_depth = 0
    for line in source.read_text(encoding="utf-8").splitlines(keepends=True):
        if TYPES_INCLUDE_PATTERN.match(line) or GLOBAL_ASM_PATTERN.match(line):
            continue
        if DISABLED_BLOCK_START_PATTERN.match(line):
            disabled_depth += 1
            continue
        if disabled_depth and DISABLED_BLOCK_END_PATTERN.match(line):
            disabled_depth -= 1
            continue
        if PREPROCESSOR_PATTERN.match(line):
            return None
        lines.append(line)
    if disabled_depth:
        return None
    types = flattened_types_header()
    body = "".join(lines).lstrip()
    return (
        "/* Generated m2c context; canonical declarations remain in project source. */\n\n"
        + (types + "\n\n" if types else "")
        + body
    )


def prepare_m2c_context(source: Path | None) -> Path | None:
    """Generate source-local context under ignored build output for caching."""

    if source is None or not source.is_file():
        return None
    try:
        relative = source.relative_to(ROOT / "src")
    except ValueError:
        return None
    context = flattened_source_context(source)
    if context is None:
        return None
    output = ROOT / "build" / "m2c" / "context" / relative
    output.parent.mkdir(parents=True, exist_ok=True)
    content = context.encode("utf-8")
    if not output.is_file() or output.read_bytes() != content:
        output.write_bytes(content)
    return output


def mips_to_c_command(
    extracted_source: Path, symbol: str, context_source: Path | None = None
) -> list[str]:
    """Build the pinned mips_to_c invocation, including curated types."""

    command = [
        "python3",
        str(MIPS_TO_C),
        "--target",
        "mips-ido-c",
        "--valid-syntax",
        "--function",
        symbol,
    ]
    context = prepare_m2c_context(context_source)
    if context is not None:
        command.extend(["--context", str(context.relative_to(ROOT))])
    command.append(str(extracted_source.relative_to(ROOT)))
    return command


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
    parser.add_argument(
        "--ready-output",
        action="store_true",
        help="label required declarations before printing the complete C starter",
    )
    args = parser.parse_args()
    context_source = None
    try:
        if args.auto_overlay:
            _, context_source, _, _ = resolve_work_item(args.profile, args.symbol)
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
    boundaries = registered_symbols(args.profile) if args.auto_overlay else None
    extracted_source = extract_function(
        source, symbol, boundary_symbols=boundaries
    )

    command = mips_to_c_command(extracted_source, symbol, context_source)
    result = subprocess.run(
        command,
        cwd=ROOT,
        check=False,
        stdout=subprocess.PIPE,
        text=True,
    )
    starter = repair_preserved_call_arguments(
        result.stdout,
        extracted_source.read_text(encoding="utf-8"),
        symbol,
    )
    if args.ready_output and result.returncode == 0:
        starter = ready_output(starter, symbol)
    print(starter, end="" if starter.endswith("\n") else "\n")
    return result.returncode


if __name__ == "__main__":
    raise SystemExit(main())
