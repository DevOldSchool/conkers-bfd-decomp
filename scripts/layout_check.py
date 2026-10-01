#!/usr/bin/env python3
"""Reject focused matches that disturb a reviewed source unit's object layout."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path

import compile_c
from candidate_tables import Object32


ROOT = Path(__file__).resolve().parent.parent
NM_LINE = re.compile(r"^([0-9A-Fa-f]+)\s+(?:[0-9A-Fa-f]+\s+)?[Tt]\s+(\S+)$")
TEXT_SECTION = re.compile(
    r"^\s*\d+\s+\.text\s+([0-9A-Fa-f]+)\s+.*?2\*\*(\d+)\s*$"
)


class LayoutError(ValueError):
    """Raised when a candidate changes its reviewed source-unit layout."""


class LayoutMismatch(LayoutError):
    """A compiled object's measured member offsets or extent differ."""


def archived_object_layout(data: bytes) -> tuple[dict[str, int], int, int]:
    """Re-extract proof measurements using the existing strict MIPS ELF reader."""
    obj = Object32(data)
    header = obj.unpack(">16sHHIIIIIHHHHHH", 0)
    names = obj.section(header[13])
    text = []
    for index, section in enumerate(obj.sections):
        end = names.find(b"\0", section[0])
        if end < section[0]:
            raise LayoutError("invalid archived section name")
        if names[section[0]:end] == b".text":
            text.append(index)
    if len(text) != 1:
        raise LayoutError("archived object needs exactly one .text section")
    index = text[0]
    section = obj.sections[index]
    alignment = section[8]
    if section[1] != 1 or not section[2] & 4 or alignment < 1 or alignment & (alignment - 1):
        raise LayoutError("unsupported archived text section")
    obj.section(index)  # Verify the complete text payload exists.
    symbols = {}
    for table in obj.symbols.values():
        for name, value, _, section_index in table:
            if name and section_index == index:
                if name in symbols:
                    raise LayoutError("ambiguous archived text symbol")
                symbols[name] = value
    return symbols, section[5], alignment


def failure_inputs(root: Path, source: str) -> dict[str, str]:
    paths = {source, "progress/functions.json", "progress/source_units.json",
             "toolchain/tools.lock.json"}
    paths.update(path.relative_to(root).as_posix()
                 for path in (root / "include").rglob("*") if path.is_file())
    paths.update(re.findall(r'#pragma\s+GLOBAL_ASM\("([^\"]+)"\)',
                            (root / source).read_text(encoding="utf-8")))
    return {name: hashlib.sha256((root / name).read_bytes()).hexdigest()
            for name in sorted(paths)}


def archive_layout_failure(
    root: Path, directory: Path, profile: str, identifier: str, function: dict,
    unit: dict, object_path: Path, symbols: dict[str, int], size: int,
    alignment: int, error: LayoutMismatch, inputs: dict[str, str], focused_output: str,
) -> None:
    """Write evidence first; a missing final receipt never authorizes deferral."""
    directory = directory.resolve()
    if not directory.is_relative_to((root / "build" / profile / "deferred-layout").resolve()):
        raise LayoutError("layout failure archive must be inside the profile build directory")
    if unit.get("boundary_evidence", {}).get(profile, {}).get("reviewed") is not True:
        raise LayoutError("exact deferral requires a reviewed source-unit boundary")
    if failure_inputs(root, function["source"]) != inputs:
        raise LayoutError("layout inputs changed during compilation")
    source_data = (root / function["source"]).read_bytes()
    object_data = object_path.read_bytes()
    if f"{identifier}: CURRENT (0)" not in focused_output:
        raise LayoutError("exact deferral requires a successful focused comparison")
    focused_data = focused_output.encode("utf-8")
    receipt = {
        "schema_version": 1, "kind": "reviewed_layout_mismatch", "profile": profile,
        "identifier": identifier, "source": function["source"], "inputs": inputs,
        "object": object_path.relative_to(root).as_posix(),
        "source_sha256": hashlib.sha256(source_data).hexdigest(),
        "object_sha256": hashlib.sha256(object_data).hexdigest(),
        "focused_current_differences": 0,
        "focused_log_sha256": hashlib.sha256(focused_data).hexdigest(),
        "symbols": symbols, "text_size": size, "text_alignment": alignment,
        "error": str(error),
    }
    if receipt["source_sha256"] != inputs[function["source"]]:
        raise LayoutError("candidate source changed before archival")
    directory.mkdir(parents=True, exist_ok=True)
    for name, data in (("candidate.c", source_data), ("candidate.o", object_data),
                       ("focused.log", focused_data)):
        with (directory / name).open("xb") as stream:
            stream.write(data)
    if (failure_inputs(root, function["source"]) != inputs
            or object_path.read_bytes() != object_data):
        raise LayoutError("layout inputs or object changed during archival")
    with (directory / "proof.json").open("x", encoding="utf-8") as stream:
        json.dump(receipt, stream, indent=2, sort_keys=True)
        stream.write("\n")


def validate_failure_proof(root: Path, proof: Path, function: dict, profile: str) -> dict:
    proof = proof.resolve()
    if not proof.is_relative_to((root / "build" / profile / "deferred-layout").resolve()):
        raise LayoutError("layout failure proof must be inside the profile build directory")
    receipt = json.loads(proof.read_text(encoding="utf-8"))
    if not isinstance(receipt, dict):
        raise LayoutError("layout failure proof must be an object")
    if any(receipt.get(key) != value for key, value in {
        "schema_version": 1, "kind": "reviewed_layout_mismatch", "profile": profile,
        "identifier": function["symbol"], "source": function["source"],
        "focused_current_differences": 0,
    }.items()):
        raise LayoutError("layout failure proof does not identify this candidate")
    if receipt.get("inputs") != failure_inputs(root, function["source"]):
        raise LayoutError("layout failure proof has stale source or inputs")
    object_path = (root / receipt["object"]).resolve()
    if not object_path.is_relative_to((root / "build" / profile / "layout-check").resolve()):
        raise LayoutError("layout failure object must be a mixed layout-check object")
    for path, expected in (
        (root / function["source"], receipt["source_sha256"]),
        (proof.parent / "candidate.c", receipt["source_sha256"]),
        (object_path, receipt["object_sha256"]),
        (proof.parent / "candidate.o", receipt["object_sha256"]),
        (proof.parent / "focused.log", receipt["focused_log_sha256"]),
    ):
        if path.is_symlink() or hashlib.sha256(path.read_bytes()).hexdigest() != expected:
            raise LayoutError("layout failure candidate or object evidence changed")
    focused = (proof.parent / "focused.log").read_text(encoding="utf-8")
    scores = re.findall(rf"^{re.escape(function['symbol'])}: CURRENT \((\d+)\)$", focused, re.MULTILINE)
    if scores != ["0"]:
        raise LayoutError("layout failure proof lacks one exact-target CURRENT (0) result")
    units = json.loads((root / "progress/source_units.json").read_text())["source_units"]
    owners = [unit for unit in units if unit.get("source") == function["source"]
              and function["symbol"] in unit.get("functions", [])]
    if (len(owners) != 1
            or owners[0].get("boundary_evidence", {}).get(profile, {}).get("reviewed") is not True):
        raise LayoutError("exact deferral requires one reviewed source unit")
    symbols, size, alignment = archived_object_layout((proof.parent / "candidate.o").read_bytes())
    members = {entry["regions"][profile]["symbol"] for entry in
               json.loads((root / "progress/functions.json").read_text())["functions"]
               if entry["symbol"] in owners[0]["functions"] and profile in entry["regions"]}
    if ({name: symbols.get(name) for name in members}
            != {name: receipt["symbols"].get(name) for name in members}
            or (size, alignment) != (receipt["text_size"], receipt["text_alignment"])):
        raise LayoutError("layout failure measurements do not match the archived object")
    try:
        validate_layout(function, owners[0], symbols, size, alignment, profile, root=root)
    except LayoutMismatch as error:
        if str(error) != receipt.get("error"):
            raise LayoutError("layout failure receipt no longer describes the measured mismatch")
    else:
        raise LayoutError("cannot defer an exact candidate with preserved layout")
    return receipt


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
    *,
    root: Path | None = None,
) -> None:
    functions_data = json.loads(
        ((root or ROOT) / "progress" / "functions.json").read_text(encoding="utf-8")
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
        raise LayoutMismatch("; ".join(errors))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("profile", choices=("us", "eu"))
    parser.add_argument("identifier")
    parser.add_argument("--failure-archive", type=Path)
    args = parser.parse_args()
    try:
        function, unit = load_work_item(args.identifier, args.profile)
        if unit is None:
            print(f"{args.identifier}: no reviewed source-unit layout gate required")
            return 0
        source = ROOT / function["source"]
        inputs = failure_inputs(ROOT, function["source"]) if args.failure_archive else None
        focused_output = ""
        if args.failure_archive:
            focused_output = subprocess.run(
                [sys.executable, "scripts/diff.py", args.profile, args.identifier,
                 "--auto-overlay", "--require-match"], cwd=ROOT, check=True,
                capture_output=True, text=True,
            ).stdout
        object_path = compile_mixed_object(args.profile, source)
        symbols = object_symbols(object_path)
        text_size, text_alignment = text_extent(object_path)
        try:
            validate_layout(function, unit, symbols, text_size, text_alignment, args.profile)
        except LayoutMismatch as error:
            if args.failure_archive:
                archive_layout_failure(ROOT, args.failure_archive, args.profile, args.identifier,
                                       function, unit, object_path, symbols, text_size,
                                       text_alignment, error, inputs, focused_output)
            raise
    except (LayoutError, OSError, subprocess.CalledProcessError, KeyError) as error:
        print(f"error: {args.identifier} source-unit layout mismatch: {error}", file=sys.stderr)
        return 1
    print(f"{args.identifier}: reviewed source-unit symbol layout preserved")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
