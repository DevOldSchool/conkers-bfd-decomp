#!/usr/bin/env python3
"""Transactionally integrate or finalize reviewed source units."""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

import project_state


ROOT = Path(__file__).resolve().parent.parent


def replace_map_range(path: Path, start: int, end: int, mapped_name: str) -> None:
    """Replace one raw-assembly range with C and retain assembly after the unit."""

    lines = path.read_text(encoding="utf-8").splitlines()
    entry_pattern = re.compile(
        r"^(?P<indent>\s*)-\s*\[(?P<offset>0x[0-9A-Fa-f]+),\s*"
        r"(?P<kind>asm|hasm|c|lib)(?:,\s*(?P<name>[^\]]+))?\]\s*$"
    )
    matches: list[tuple[int, re.Match[str]]] = []
    offsets: set[int] = set()
    for index, line in enumerate(lines):
        match = entry_pattern.match(line)
        if match:
            offset = int(match.group("offset"), 0)
            offsets.add(offset)
            if offset == start:
                matches.append((index, match))
    if len(matches) != 1:
        raise project_state.ProjectStateError(
            f"{path.relative_to(ROOT)} must contain exactly one map entry at 0x{start:X}"
        )
    index, match = matches[0]
    if match.group("kind") not in {"asm", "hasm"}:
        raise project_state.ProjectStateError(
            f"{path.relative_to(ROOT)} entry at 0x{start:X} is not raw assembly"
        )
    if any(start < offset < end for offset in offsets):
        raise project_state.ProjectStateError(
            f"source-unit range 0x{start:X}:0x{end:X} crosses an existing map boundary"
        )
    indent = match.group("indent")
    lines[index] = f"{indent}- [0x{start:X}, c, {mapped_name}]"
    if end not in offsets:
        lines.insert(index + 1, f"{indent}- [0x{end:X}, asm]")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def replace_c_mapping(path: Path, start: int, old_name: str, new_name: str) -> None:
    """Rename an already-integrated C map entry when its unit moves to done."""

    lines = path.read_text(encoding="utf-8").splitlines()
    old_entry = re.compile(
        rf"^(?P<indent>\s*)-\s*\[0x{start:X},\s*c,\s*{re.escape(old_name)}\]\s*$",
        re.IGNORECASE,
    )
    matches = [(index, match) for index, line in enumerate(lines) if (match := old_entry.match(line))]
    if len(matches) != 1:
        raise project_state.ProjectStateError(
            f"{path.relative_to(ROOT)} must contain exactly one C entry for {old_name} at 0x{start:X}"
        )
    index, match = matches[0]
    lines[index] = f"{match.group('indent')}- [0x{start:X}, c, {new_name}]"
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def integrate(symbol: str, profile: str) -> None:
    """Integrate or finalize one reviewed active source unit transactionally."""

    functions_data = project_state.load_json(project_state.FUNCTIONS_FILE)
    units_data = project_state.load_json(project_state.SOURCE_UNITS_FILE)
    functions = project_state.validate_functions(functions_data)
    units = project_state.validate_source_units(units_data, functions)
    function = next((entry for entry in functions if entry["symbol"] == symbol), None)
    if function is None:
        raise project_state.ProjectStateError(f"unknown work-item ID: {symbol}")
    overlay = function.get("overlay", "main")
    source = function.get("source")
    unit = next((entry for entry in units if entry["source"] == source), None)
    if unit is None or symbol not in unit["functions"]:
        raise project_state.ProjectStateError(
            f"{symbol} has no reviewed source-unit record; register its boundary separately first"
        )
    boundary_evidence = unit.get("boundary_evidence", {}).get(profile)
    if not isinstance(boundary_evidence, dict) or boundary_evidence.get("reviewed") is not True:
        raise project_state.ProjectStateError(
            f"{symbol}/{profile} source unit lacks reviewed boundary evidence"
        )
    members = [entry for entry in functions if entry["symbol"] in unit["functions"]]
    unfinished = [entry["symbol"] for entry in members if not project_state.is_complete(entry)]
    integration = unit["integration"]
    if integration == "c" or source.startswith("src/game/done/"):
        raise project_state.ProjectStateError(f"source unit is already integrated: {source}")

    source_path = ROOT / source
    if not source_path.is_file():
        raise project_state.ProjectStateError(f"candidate source does not exist: {source}")
    region = unit["regions"][profile]
    start = int(region["start"], 0)
    end = int(region["end"], 0)
    if start % 0x10 or end % 0x10:
        raise project_state.ProjectStateError(
            f"{source}/{profile} must use 16-byte IDO object boundaries before integration"
        )
    map_directory = "profiles" if overlay == "main" else "game"
    map_path = ROOT / "config" / map_directory / f"{profile}.yaml"
    mapped_name = source.removeprefix("src/").removesuffix(".c")
    source_content = source_path.read_text(encoding="utf-8")

    finalizing = integration == "mixed" or (integration == "raw_asm" and not unfinished)
    if integration == "raw_asm":
        if unfinished and overlay != "game":
            raise project_state.ProjectStateError(
                "mixed C/ASM integration currently supports game-overlay source units only"
            )
        missing_placeholders = [
            identifier
            for identifier in unfinished
            if project_state.global_asm_pragma(source, identifier) not in source_content
        ]
        if missing_placeholders:
            raise project_state.ProjectStateError(
                "mixed integration requires GLOBAL_ASM placeholders for unmatched functions: "
                + ", ".join(missing_placeholders)
            )
    elif integration == "mixed":
        if unfinished:
            raise project_state.ProjectStateError(
                f"mixed source unit is not ready to finalize; unmatched active functions: {', '.join(unfinished)}"
            )
        if "GLOBAL_ASM" in source_content:
            raise project_state.ProjectStateError(
                f"mixed source unit still contains GLOBAL_ASM placeholders: {source}"
            )
    else:
        raise project_state.ProjectStateError(f"unsupported source-unit integration state: {integration}")

    done_source = f"src/game/done/{source_path.name}"
    done_path = ROOT / done_source
    if finalizing and done_path.exists():
        raise project_state.ProjectStateError(f"integration destination already exists: {done_source}")

    tracked_paths = (
        map_path,
        project_state.FUNCTIONS_FILE,
        project_state.SOURCE_UNITS_FILE,
        project_state.SUMMARY_FILE,
        project_state.DOCUMENT_FILE,
    )
    snapshots = {path: path.read_bytes() if path.exists() else None for path in tracked_paths}
    done_directory_existed = done_path.parent.exists()
    moved = False
    try:
        if finalizing:
            done_path.parent.mkdir(parents=True, exist_ok=True)
            source_path.rename(done_path)
            moved = True
            done_mapped_name = done_source.removeprefix("src/").removesuffix(".c")
            if integration == "mixed":
                replace_c_mapping(map_path, start, mapped_name, done_mapped_name)
            else:
                replace_map_range(map_path, start, end, done_mapped_name)
            for member in members:
                member["source"] = done_source
            unit["source"] = done_source
            unit["integration"] = "c"
            unit["regions"][profile]["state"] = "complete"
        else:
            replace_map_range(map_path, start, end, mapped_name)
            unit["integration"] = "mixed"
            unit["regions"][profile]["state"] = project_state.source_unit_work_state(members)

        # The build validates the on-disk project state. Publish the transactional
        # inventory changes before invoking it so finalized units point at the
        # source after it has moved into src/game/done/. The snapshots above
        # restore these files if validation or the build fails.
        validated_functions = project_state.validate_functions(functions_data)
        project_state.validate_source_units(units_data, validated_functions)
        project_state.write_json(project_state.FUNCTIONS_FILE, functions_data)
        project_state.write_json(project_state.SOURCE_UNITS_FILE, units_data)

        build_target = "build" if overlay == "main" else "game-integrated-refresh"
        command = ["make", "--silent", "--jobs", "4", build_target]
        if overlay == "main":
            command.append(f"PROFILE={profile}")
        subprocess.run(command, cwd=ROOT, check=True)

        project_state.render_progress(validated_functions)
    except BaseException:
        for path, content in snapshots.items():
            if content is None:
                path.unlink(missing_ok=True)
            else:
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(content)
        if moved and done_path.exists() and not source_path.exists():
            source_path.parent.mkdir(parents=True, exist_ok=True)
            done_path.rename(source_path)
        if not done_directory_existed and done_path.parent.exists():
            try:
                done_path.parent.rmdir()
            except OSError:
                pass
        raise

    if finalizing:
        print(
            f"Finalized {symbol}/{profile}: {done_source}; "
            f"{overlay} build is byte-identical and the source unit is complete."
        )
    else:
        print(
            f"Integrated {symbol}/{profile} as mixed C/ASM: {source}; "
            f"{overlay} build is byte-identical; unmatched functions remain GLOBAL_ASM."
        )


def integrate_all_reviewed(profile: str) -> None:
    """Integrate every incomplete reviewed game unit in one transactional build."""

    functions_data = project_state.load_json(project_state.FUNCTIONS_FILE)
    units_data = project_state.load_json(project_state.SOURCE_UNITS_FILE)
    functions = project_state.validate_functions(functions_data)
    units = project_state.validate_source_units(units_data, functions)
    functions_by_id = {entry["symbol"]: entry for entry in functions}
    candidates: list[tuple[dict, list[dict], Path, int, int, str]] = []
    map_path = ROOT / "config" / "game" / f"{profile}.yaml"

    for unit in units:
        if unit["integration"] != "raw_asm":
            continue
        members = [functions_by_id[identifier] for identifier in unit["functions"]]
        if any(member.get("overlay", "main") != "game" for member in members):
            continue
        unfinished = [member["symbol"] for member in members if not project_state.is_complete(member)]
        if not unfinished:
            continue
        source = unit["source"]
        evidence = unit.get("boundary_evidence", {}).get(profile)
        if not isinstance(evidence, dict) or evidence.get("reviewed") is not True:
            raise project_state.ProjectStateError(
                f"{source}/{profile} source unit lacks reviewed boundary evidence"
            )
        source_path = ROOT / source
        if not source_path.is_file():
            raise project_state.ProjectStateError(f"candidate source does not exist: {source}")
        content = source_path.read_text(encoding="utf-8")
        missing = [
            identifier
            for identifier in unfinished
            if project_state.global_asm_pragma(source, identifier) not in content
        ]
        if missing:
            raise project_state.ProjectStateError(
                f"{source} lacks GLOBAL_ASM placeholders for: {', '.join(missing)}"
            )
        region = unit["regions"][profile]
        start = int(region["start"], 0)
        end = int(region["end"], 0)
        mapped_name = source.removeprefix("src/").removesuffix(".c")
        candidates.append((unit, members, source_path, start, end, mapped_name))

    if not candidates:
        print("No incomplete reviewed game source units are awaiting mixed integration.")
        return

    tracked_paths = (
        map_path,
        project_state.FUNCTIONS_FILE,
        project_state.SOURCE_UNITS_FILE,
        project_state.SUMMARY_FILE,
        project_state.DOCUMENT_FILE,
    )
    snapshots = {path: path.read_bytes() if path.exists() else None for path in tracked_paths}
    try:
        for unit, members, _, start, end, mapped_name in candidates:
            replace_map_range(map_path, start, end, mapped_name)
            unit["integration"] = "mixed"
            unit["regions"][profile]["state"] = project_state.source_unit_work_state(members)
        subprocess.run(
            ["make", "--silent", "--jobs", "4", "game-integrated-refresh"],
            cwd=ROOT,
            check=True,
        )
        validated_functions = project_state.validate_functions(functions_data)
        project_state.validate_source_units(units_data, validated_functions)
        project_state.write_json(project_state.SOURCE_UNITS_FILE, units_data)
        project_state.render_progress(validated_functions)
    except BaseException:
        for path, content in snapshots.items():
            if content is None:
                path.unlink(missing_ok=True)
            else:
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(content)
        raise

    print(
        f"Integrated {len(candidates)} reviewed game source units as mixed C/ASM; "
        "the US game build is byte-identical."
    )


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--profile", choices=project_state.TARGET_REGIONS, required=True)
    parser.add_argument("symbol", nargs="?")
    parser.add_argument("--all-reviewed", action="store_true")
    arguments = parser.parse_args()
    try:
        if arguments.all_reviewed:
            if arguments.symbol is not None:
                parser.error("a symbol cannot be combined with --all-reviewed")
            integrate_all_reviewed(arguments.profile)
        elif arguments.symbol is None:
            parser.error("provide a symbol or --all-reviewed")
        else:
            integrate(arguments.symbol, arguments.profile)
    except (project_state.ProjectStateError, subprocess.CalledProcessError, OSError) as error:
        print(f"error: integration failed and project files were restored: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
