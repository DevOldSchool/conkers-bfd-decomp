#!/usr/bin/env python3
"""Reject focused matches that disturb a reviewed source unit's object layout."""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

import compile_c


ROOT = Path(__file__).resolve().parent.parent
NM_LINE = re.compile(r"^([0-9A-Fa-f]+)\s+(?:[0-9A-Fa-f]+\s+)?[Tt]\s+(\S+)$")
TEXT_SECTION = re.compile(
    r"^\s*\d+\s+\.text\s+([0-9A-Fa-f]+)\s+.*?2\*\*(\d+)\s*$"
)


class LayoutError(ValueError):
    """Raised when a candidate changes its reviewed source-unit layout."""


def load_work_item(identifier: str, profile: str) -> tuple[dict, dict | None]:
    functions_data = json.loads(
        (ROOT / "progress" / "functions.json").read_text(encoding="utf-8")
    )
    units_data = json.loads(
        (ROOT / "progress" / "source_units.json").read_text(encoding="utf-8")
    )
    function = next(
        (entry for entry in functions_data["functions"] if entry["symbol"] == identifier),
        None,
    )
    if function is None:
        raise LayoutError(f"unknown work-item ID: {identifier}")
    if profile not in function.get("regions", {}):
        raise LayoutError(f"{identifier} is not registered for {profile}")
    unit = next(
        (
            entry
            for entry in units_data["source_units"]
            if entry.get("source") == function.get("source")
            and identifier in entry.get("functions", [])
        ),
        None,
    )
    return function, unit


def compile_mixed_object(profile: str, source: Path) -> Path:
    relative = source.relative_to(ROOT)
    output = ROOT / "build" / profile / "layout-check" / relative.with_suffix(".o")
    output.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        compile_c.compile_command(profile, source, output),
        cwd=ROOT,
        check=True,
    )
    return output


def object_symbols(path: Path) -> dict[str, int]:
    result = subprocess.run(
        ["mips-linux-gnu-nm", "-n", "-S", str(path)],
        cwd=ROOT,
        check=True,
        capture_output=True,
        text=True,
    )
    symbols: dict[str, int] = {}
    for line in result.stdout.splitlines():
        match = NM_LINE.match(line)
        if match:
            symbols[match.group(2)] = int(match.group(1), 16)
    return symbols


def text_extent(path: Path) -> tuple[int, int]:
    result = subprocess.run(
        ["mips-linux-gnu-objdump", "-h", str(path)],
        cwd=ROOT,
        check=True,
        capture_output=True,
        text=True,
    )
    for line in result.stdout.splitlines():
        match = TEXT_SECTION.match(line)
        if match:
            return int(match.group(1), 16), 1 << int(match.group(2))
    raise LayoutError(f"could not read .text layout from {path}")


def validate_layout(
    function: dict,
    unit: dict,
    symbols: dict[str, int],
    text_size: int,
    text_alignment: int,
    profile: str,
) -> None:
    functions_data = json.loads(
        (ROOT / "progress" / "functions.json").read_text(encoding="utf-8")
    )
    by_id = {entry["symbol"]: entry for entry in functions_data["functions"]}
    members = [by_id[identifier] for identifier in unit["functions"]]
    first = members[0]
    first_symbol = first["regions"][profile]["symbol"]
    if first_symbol not in symbols:
        raise LayoutError(f"mixed object is missing source-unit start symbol {first_symbol}")
    actual_start = symbols[first_symbol]
    expected_start = int(first["regions"][profile]["vram"], 16)

    errors: list[str] = []
    for member in members:
        region = member["regions"].get(profile)
        if region is None:
            continue
        symbol = region["symbol"]
        if symbol not in symbols:
            errors.append(f"{symbol} is missing from the mixed object")
            continue
        expected_offset = int(region["vram"], 16) - expected_start
        actual_offset = symbols[symbol] - actual_start
        if actual_offset != expected_offset:
            errors.append(
                f"{symbol} offset 0x{actual_offset:X}, expected 0x{expected_offset:X} "
                f"(delta {actual_offset - expected_offset:+d})"
            )

    unit_region = unit["regions"][profile]
    expected_extent = int(unit_region["end"], 16) - int(unit_region["start"], 16)
    actual_extent = text_size - actual_start
    aligned_actual = (actual_extent + text_alignment - 1) // text_alignment * text_alignment
    aligned_expected = (expected_extent + text_alignment - 1) // text_alignment * text_alignment
    if aligned_actual != aligned_expected:
        errors.append(
            f"source-unit text extent 0x{actual_extent:X} (aligned 0x{aligned_actual:X}), "
            f"expected 0x{expected_extent:X} (aligned 0x{aligned_expected:X})"
        )

    if errors:
        raise LayoutError("; ".join(errors))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("profile", choices=("us", "eu"))
    parser.add_argument("identifier")
    args = parser.parse_args()
    try:
        function, unit = load_work_item(args.identifier, args.profile)
        if unit is None:
            print(f"{args.identifier}: no reviewed source-unit layout gate required")
            return 0
        source = ROOT / function["source"]
        object_path = compile_mixed_object(args.profile, source)
        symbols = object_symbols(object_path)
        text_size, text_alignment = text_extent(object_path)
        validate_layout(
            function, unit, symbols, text_size, text_alignment, args.profile
        )
    except (LayoutError, OSError, subprocess.CalledProcessError, KeyError) as error:
        print(f"error: {args.identifier} source-unit layout mismatch: {error}", file=sys.stderr)
        return 1
    print(f"{args.identifier}: reviewed source-unit symbol layout preserved")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
