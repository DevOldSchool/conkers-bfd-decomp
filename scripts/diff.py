#!/usr/bin/env python3
"""Compile one registered C candidate and show its focused assembly diff."""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

import compile_c
from m2c import locate_function
import project_state


ROOT = Path(__file__).resolve().parent.parent
ASM_DIFFER = Path("/opt/tools/asm-differ/diff.py")
NORMALIZE_ASM = ROOT / "scripts" / "normalize_asm.py"
ASSEMBLY_MACROS = ROOT / "include" / "macro.inc"
TOOLCHAIN_DEFINITION = ROOT / "Dockerfile"
GLOBAL_ASM_LINE = re.compile(
    r"^[ \t]*#pragma[ \t]+GLOBAL_ASM\([^\r\n]*\)[ \t]*\r?$", re.MULTILINE
)
EXIT_MISMATCH = 1
EXIT_FIX_COMPILE = 2
EXIT_BLOCKED_TOOLING = 3


class NonzeroDifferenceError(ValueError):
    """Raised when valid asm-differ evidence reports a nonzero score."""


def find_work_item(symbol: str, profile: str, *, overlay: str | None = None) -> tuple[Path, str]:
    inventory = json.loads((ROOT / "progress" / "functions.json").read_text(encoding="utf-8"))
    for function in inventory["functions"]:
        region = function["regions"].get(profile)
        if region and region["symbol"] == symbol and function.get("overlay", "main") == (overlay or "main"):
            return ROOT / function["source"], region["symbol"]
    raise ValueError(f"{symbol} is not registered for the {profile} profile")


def find_work_item_by_id(identifier: str, profile: str) -> tuple[Path, str, bool]:
    """Resolve a shared work-item ID and whether it uses the game overlay."""

    inventory = json.loads((ROOT / "progress" / "functions.json").read_text(encoding="utf-8"))
    for function in inventory["functions"]:
        if function["symbol"] != identifier:
            continue
        region = function["regions"].get(profile)
        if not region:
            raise ValueError(f"{identifier} is not registered for the {profile} profile")
        return ROOT / function["source"], region["symbol"], function.get("overlay", "main") == "game"
    raise ValueError(f"unknown work-item ID: {identifier}")


def candidate_object(profile: str, source: Path) -> Path:
    try:
        source_relative = source.relative_to(ROOT)
    except ValueError as error:
        raise ValueError(f"candidate source must be inside the repository: {source}") from error

    output = ROOT / "build" / profile / source_relative.with_suffix(".o")
    output.parent.mkdir(parents=True, exist_ok=True)
    return output


def focused_candidate_source(profile: str, source: Path) -> Path:
    """Create a focused source without unrelated mixed-unit assembly members."""

    content = source.read_text(encoding="utf-8")
    focused_content = GLOBAL_ASM_LINE.sub("", content)
    if focused_content == content:
        return source
    source_relative = source.relative_to(ROOT)
    output = ROOT / "build" / profile / "diff-source" / source_relative
    output.parent.mkdir(parents=True, exist_ok=True)
    if not output.is_file() or output.read_text(encoding="utf-8") != focused_content:
        output.write_text(focused_content, encoding="utf-8")
    return output


def compile_candidate(profile: str, source: Path) -> Path:
    output = candidate_object(profile, source)
    compile_source = focused_candidate_source(profile, source)
    subprocess.run(
        compile_c.compile_command(
            profile,
            compile_source,
            output,
        ),
        cwd=ROOT,
        check=True,
    )
    return output


def require_c_implementation(source: Path, identifier: str) -> None:
    source_relative = str(source.relative_to(ROOT))
    target_pragma = project_state.global_asm_pragma(source_relative, identifier)
    if target_pragma in source.read_text(encoding="utf-8"):
        raise ValueError(
            f"{identifier} is still supplied by GLOBAL_ASM; remove its pragma and add C before diffing"
        )


def reference_object(
    profile: str,
    symbol: str,
    *,
    game_reference: bool = False,
    assembly: Path | None = None,
) -> Path:
    if assembly is None:
        assembly = locate_function(
            profile,
            symbol,
            reference=not game_reference,
            game_reference=game_reference,
        )
    relative = assembly.relative_to(ROOT / "reference").with_suffix(".s")
    normalized = ROOT / "build" / profile / "reference-normalized" / relative
    output = ROOT / "build" / profile / "reference-objects" / relative.with_suffix(".o")
    normalized.parent.mkdir(parents=True, exist_ok=True)
    output.parent.mkdir(parents=True, exist_ok=True)
    dependencies = (assembly, NORMALIZE_ASM, ASSEMBLY_MACROS, TOOLCHAIN_DEFINITION)
    if output.is_file() and all(
        dependency.is_file() and output.stat().st_mtime_ns >= dependency.stat().st_mtime_ns
        for dependency in dependencies
    ):
        return output
    subprocess.run(
        ["python3", "scripts/normalize_asm.py", str(assembly.relative_to(ROOT)), str(normalized.relative_to(ROOT))],
        cwd=ROOT,
        check=True,
    )
    subprocess.run(
        ["mips-linux-gnu-as", "-W", "-EB", "-march=vr4300", "-mabi=32", "-I", "include", "-o", str(output.relative_to(ROOT)), str(normalized.relative_to(ROOT))],
        cwd=ROOT,
        check=True,
    )
    return output


def prepare_reference(profile: str, *, game_reference: bool = False) -> None:
    """Generate the profile's raw, unmodified reference assembly."""

    if game_reference:
        subprocess.run(["make", "game-asm", f"GAME_REFERENCE_PROFILE={profile}"], cwd=ROOT, check=True)
    else:
        subprocess.run(["make", "prepare-reference", f"PROFILE={profile}"], cwd=ROOT, check=True)


def ensure_reference(profile: str, *, game_reference: bool = False) -> None:
    """Prepare reference assembly only when no generated assembly is available."""

    if game_reference:
        assembly_root = ROOT / "reference" / "game" / profile / "asm"
    else:
        assembly_root = ROOT / "reference" / profile / "asm"
    if assembly_root.is_dir() and next(assembly_root.rglob("*.s"), None) is not None:
        return
    prepare_reference(profile, game_reference=game_reference)


def ensure_reference_function(
    profile: str, symbol: str, *, game_reference: bool = False
) -> Path:
    """Refresh a stale split only when it does not contain the requested function."""

    ensure_reference(profile, game_reference=game_reference)
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


def current_difference_count(output: str) -> int:
    """Read asm-differ's machine-readable current score."""

    try:
        current_differences = json.loads(output)["current_score"]
    except (json.JSONDecodeError, KeyError, TypeError) as error:
        raise ValueError(f"asm-differ returned invalid JSON match evidence: {error}") from error
    if not isinstance(current_differences, int):
        raise ValueError("asm-differ returned a non-integer difference score")
    return current_differences


def require_zero_difference(output: str, symbol: str) -> None:
    """Reject asm-differ evidence that is not an exact instruction match."""

    current_differences = current_difference_count(output)
    if current_differences != 0:
        raise NonzeroDifferenceError(
            f"{symbol} is not matched: CURRENT ({current_differences}); inventory was not changed"
        )


def write_settings(profile: str, source: Path) -> Path:
    directory = ROOT / "build" / profile / "diff"
    directory.mkdir(parents=True, exist_ok=True)
    settings = directory / "diff_settings.py"
    focused_compiler = ROOT / "scripts" / "compile_diff_candidate.py"
    settings.write_text(
        "import os\n"
        f"ROOT = {str(ROOT)!r}\n"
        f"SOURCE = {str(source)!r}\n"
        f"FOCUSED_COMPILER = {str(focused_compiler)!r}\n"
        "def apply(config, args):\n"
        "    config['arch'] = 'mips'\n"
        "    config['objdump_executable'] = 'mips-linux-gnu-objdump'\n"
        "    config['source_directories'] = [os.path.join(ROOT, 'src')]\n"
        f"    config['make_command'] = ['python3', FOCUSED_COMPILER, '--profile', '{profile}', '--source', SOURCE]\n"
        "def map_build_target(make_target):\n"
        "    return os.path.relpath(make_target, ROOT)\n"
        "def watch_sources_for_target(make_target):\n"
        "    return [SOURCE, os.path.join(ROOT, 'include')]\n",
        encoding="utf-8",
    )
    return directory


def asm_diff_command(
    candidate: Path,
    reference: Path,
    symbol: str,
    *,
    require_match: bool = False,
    watch: bool = False,
) -> list[str]:
    command = [
        "python3",
        str(ASM_DIFFER),
        "-o",
        "-f",
        str(candidate),
        "-F",
        str(reference),
        "--stop-at-ret",
    ]
    if watch:
        command.extend(["-m", "-w", "-3"])
    else:
        command.append("--no-pager")
    command.extend(["--format", "json" if require_match else "color", symbol])
    return command


def run_asm_diff(command: list[str], directory: Path) -> int:
    try:
        return subprocess.run(command, cwd=directory, check=False).returncode
    except KeyboardInterrupt:
        return 130


def run_required_asm_diff(
    candidate: Path,
    reference: Path,
    symbol: str,
    directory: Path,
) -> int:
    """Verify an exact match, showing the normal diff when verification fails."""

    evidence_command = asm_diff_command(
        candidate,
        reference,
        symbol,
        require_match=True,
    )
    result = subprocess.run(
        evidence_command,
        cwd=directory,
        check=False,
        capture_output=True,
        text=True,
    )
    if result.returncode:
        sys.stdout.write(result.stdout)
        sys.stderr.write(result.stderr)
        return EXIT_BLOCKED_TOOLING
    try:
        require_zero_difference(result.stdout, symbol)
    except NonzeroDifferenceError as error:
        display_command = asm_diff_command(candidate, reference, symbol)
        run_asm_diff(display_command, directory)
        print(f"error: {error}", file=sys.stderr)
        return EXIT_MISMATCH
    except ValueError as error:
        print(f"error: {error}", file=sys.stderr)
        return EXIT_BLOCKED_TOOLING
    print(f"{symbol}: CURRENT (0)")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("profile", choices=("us", "eu"))
    parser.add_argument("symbol")
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument("--game", action="store_true", help="compare a registered game-overlay candidate")
    mode.add_argument("--auto-overlay", action="store_true", help="resolve the overlay from the work-item ID")
    parser.add_argument("--require-match", action="store_true", help="fail unless asm-differ reports CURRENT (0)")
    parser.add_argument("--watch", action="store_true", help="watch the candidate source and rebuild inside this container")
    arguments = parser.parse_args()
    if arguments.watch and arguments.require_match:
        parser.error("--watch and --require-match cannot be combined")

    try:
        if arguments.auto_overlay:
            source, symbol, game_reference = find_work_item_by_id(arguments.symbol, arguments.profile)
        else:
            game_reference = arguments.game
            source, symbol = find_work_item(
                arguments.symbol,
                arguments.profile,
                overlay="game" if game_reference else None,
            )
        reference_assembly = ensure_reference_function(
            arguments.profile, symbol, game_reference=game_reference
        )
        if not source.is_file():
            raise ValueError(f"candidate source does not exist: {source.relative_to(ROOT)}")
    except (ValueError, subprocess.CalledProcessError, OSError) as error:
        print(f"error: {error}", file=sys.stderr)
        return EXIT_BLOCKED_TOOLING

    try:
        require_c_implementation(source, arguments.symbol)
        candidate = compile_candidate(arguments.profile, source)
    except (ValueError, subprocess.CalledProcessError, OSError) as error:
        print(f"error: {error}", file=sys.stderr)
        return EXIT_FIX_COMPILE

    try:
        reference = reference_object(
            arguments.profile,
            symbol,
            game_reference=game_reference,
            assembly=reference_assembly,
        )
        if not reference.is_file():
            raise ValueError(
                f"reference object does not exist: {reference.relative_to(ROOT)}; run ./conker build --profile {arguments.profile} first"
            )
    except (ValueError, subprocess.CalledProcessError, OSError) as error:
        print(f"error: {error}", file=sys.stderr)
        return EXIT_BLOCKED_TOOLING

    directory = write_settings(arguments.profile, source)
    if arguments.require_match:
        return run_required_asm_diff(candidate, reference, symbol, directory)
    command = asm_diff_command(
        candidate,
        reference,
        symbol,
        watch=arguments.watch,
    )
    return run_asm_diff(command, directory)


if __name__ == "__main__":
    raise SystemExit(main())
