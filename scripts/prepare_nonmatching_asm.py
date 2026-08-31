#!/usr/bin/env python3
"""Materialize per-function assembly used by reviewed mixed source units."""

from __future__ import annotations

import argparse
import re
from pathlib import Path

import project_state


ROOT = Path(__file__).resolve().parent.parent
FUNCTION_LABEL = re.compile(r"^glabel\s+([A-Za-z_][A-Za-z0-9_]*)\s*$")


def reference_function_blocks(profile: str) -> dict[str, str]:
    root = project_state.game_assembly_root(profile)
    if not root.is_dir():
        raise project_state.ProjectStateError(
            f"missing {root.relative_to(ROOT)}; run ./conker game-asm --profile {profile} first"
        )
    blocks: dict[str, str] = {}
    for path in sorted(root.rglob("*.s")):
        lines = path.read_text(encoding="utf-8").splitlines()
        starts = [
            (index, match.group(1))
            for index, line in enumerate(lines)
            if (match := FUNCTION_LABEL.match(line))
        ]
        for position, (start, symbol) in enumerate(starts):
            end = starts[position + 1][0] if position + 1 < len(starts) else len(lines)
            body = "\n".join(lines[start:end]).rstrip() + "\n"
            blocks[symbol] = '.section .text, "ax"\n\n' + body
    return blocks


def write_if_changed(path: Path, content: str) -> bool:
    """Write generated assembly only when its bytes changed."""

    if path.is_file() and path.read_text(encoding="utf-8") == content:
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8")
    return True


def materialize(
    profile: str,
    source_filter: str | None = None,
    *,
    prune_stale: bool = False,
) -> list[Path]:
    functions = project_state.validate_functions(project_state.load_json(project_state.FUNCTIONS_FILE))
    units = project_state.validate_source_units(
        project_state.load_json(project_state.SOURCE_UNITS_FILE),
        functions,
    )
    by_identifier = {entry["symbol"]: entry for entry in functions}
    blocks = reference_function_blocks(profile)
    written: list[Path] = []
    for unit in units:
        source = unit["source"]
        members = [by_identifier[identifier] for identifier in unit["functions"]]
        if source_filter is not None and source != source_filter:
            continue
        if any(member.get("overlay", "main") != "game" for member in members):
            continue
        source_path = ROOT / source
        if not source_path.is_file():
            continue
        expected: set[Path] = set()
        for member in members:
            region = member["regions"].get(profile)
            if region is None or region["state"] == "matched":
                continue
            regional_symbol = region["symbol"]
            body = blocks.get(regional_symbol)
            if body is None:
                raise project_state.ProjectStateError(
                    f"missing {regional_symbol} in generated {profile} game reference"
                )
            output = ROOT / project_state.nonmatching_asm_path(source, member["symbol"])
            write_if_changed(output, body)
            expected.add(output)
            written.append(output)
        output_directory = ROOT / project_state.nonmatching_asm_directory(source)
        if prune_stale and output_directory.is_dir():
            for stale in output_directory.glob("*.s"):
                if stale not in expected:
                    stale.unlink()
    return written


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--profile", choices=project_state.TARGET_REGIONS, required=True)
    parser.add_argument("--source")
    parser.add_argument(
        "--prune-stale",
        action="store_true",
        help="remove obsolete generated functions after a clean object-cache refresh",
    )
    arguments = parser.parse_args()
    written = materialize(
        arguments.profile,
        arguments.source,
        prune_stale=arguments.prune_stale,
    )
    print(f"Prepared {len(written)} nonmatching assembly function(s) for {arguments.profile}.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except project_state.ProjectStateError as error:
        print(f"error: {error}")
        raise SystemExit(1)
