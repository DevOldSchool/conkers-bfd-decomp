#!/usr/bin/env python3
"""Compile one registered C candidate and show its focused assembly diff."""

from __future__ import annotations

import argparse
import importlib.util
import json
import re
import subprocess
import sys
from pathlib import Path
from typing import Callable

import candidate_tables
import compile_c
from m2c import extract_function, locate_function, registered_symbols
import project_state


ROOT = Path(__file__).resolve().parent.parent
ASM_DIFFER = Path("/opt/tools/asm-differ/diff.py")
NORMALIZE_ASM = ROOT / "scripts" / "normalize_asm.py"
ASSEMBLY_MACROS = ROOT / "include" / "macro.inc"
TOOLCHAIN_DEFINITION = ROOT / "Dockerfile"
GLOBAL_ASM_LINE = re.compile(
    r"^[ \t]*#pragma[ \t]+GLOBAL_ASM\([^\r\n]*\)[ \t]*\r?$", re.MULTILINE
)
MIPS_REGISTER = re.compile(
    r"\b(?:zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f(?:[0-9]|[12][0-9]|3[01])|f[vt][0-9])\b"
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


def expected_function_size(profile: str, symbol: str) -> int:
    """Return the non-overlapping registered byte span for one regional symbol."""

    inventory = json.loads((ROOT / "progress" / "functions.json").read_text(encoding="utf-8"))
    matches = [
        (function, region)
        for function in inventory["functions"]
        if (region := function["regions"].get(profile)) is not None
        and region["symbol"] == symbol
    ]
    if not matches:
        raise ValueError(f"{symbol} is not registered for the {profile} profile")
    if len(matches) != 1:
        raise ValueError(f"{symbol} resolves to multiple {profile} work items")

    function, region = matches[0]
    recorded_size = region.get("size_bytes")
    if recorded_size is None:
        source_units_path = ROOT / "progress" / "source_units.json"
        if not source_units_path.is_file():
            raise ValueError(
                f"{symbol} lacks size_bytes and has no reviewed source-unit span"
            )
        source_units_data = json.loads(source_units_path.read_text(encoding="utf-8"))
        sizes = project_state.active_function_sizes(
            inventory["functions"], source_units_data.get("source_units", []), profile
        )
        size = sizes.get(function["symbol"])
        if size is None:
            raise ValueError(
                f"{symbol} lacks size_bytes and has no reviewed source-unit span"
            )
    else:
        size = int(recorded_size)
    start = int(region["vram"], 16)
    overlay = function.get("overlay", "main")
    following = [
        int(other_region["vram"], 16)
        for other in inventory["functions"]
        if other is not function
        and other.get("overlay", "main") == overlay
        and (other_region := other["regions"].get(profile)) is not None
        and int(other_region["vram"], 16) > start
    ]
    if following:
        size = min(size, min(following) - start)
    if size <= 0 or size % 4:
        raise ValueError(f"{symbol} has an invalid {size}-byte instruction span")
    return size


def work_item_is_deferred(identifier: str) -> bool:
    inventory = json.loads((ROOT / "progress" / "functions.json").read_text(encoding="utf-8"))
    entry = next(
        (function for function in inventory["functions"] if function["symbol"] == identifier),
        None,
    )
    if entry is None:
        raise ValueError(f"unknown work-item ID: {identifier}")
    return "deferred" in entry


def candidate_object(profile: str, source: Path) -> Path:
    try:
        source_relative = source.relative_to(ROOT)
    except ValueError as error:
        raise ValueError(f"candidate source must be inside the repository: {source}") from error

    output = ROOT / "build" / profile / source_relative.with_suffix(".o")
    output.parent.mkdir(parents=True, exist_ok=True)
    return output


def activate_deferred_candidate(content: str, source: Path, symbol: str) -> str:
    """Restore one preserved candidate in memory without changing the worktree."""

    start_pattern = re.compile(
        rf"#if 0 /\* {re.escape(project_state.DEFERRED_CANDIDATE_TAG)} "
        rf"{re.escape(symbol)}(?: CURRENT \(\d+\))? \*/\n"
    )
    start = start_pattern.search(content)
    end_marker = f"#endif /* {project_state.DEFERRED_CANDIDATE_TAG} {symbol} */"
    if start is None:
        raise ValueError(f"{symbol} lacks a preserved deferred candidate")
    end = content.find(end_marker, start.end())
    if end < 0:
        raise ValueError(f"{symbol} has an unterminated deferred candidate")
    candidate = content[start.end() : end].rstrip("\n")
    block_end = end + len(end_marker)
    if content[block_end : block_end + 1] == "\n":
        block_end += 1
    source_relative = source.relative_to(ROOT).as_posix()
    pragma = project_state.global_asm_pragma(source_relative, symbol)
    if content[block_end : block_end + len(pragma)] != pragma:
        raise ValueError(f"{symbol} deferred candidate is not followed by its GLOBAL_ASM pragma")
    block_end += len(pragma)
    if content[block_end : block_end + 1] == "\n":
        block_end += 1
    return content[: start.start()] + candidate + "\n" + content[block_end:]


def focused_candidate_source(
    profile: str, source: Path, *, deferred_symbol: str | None = None
) -> Path:
    """Create a focused source without unrelated mixed-unit assembly members."""

    content = source.read_text(encoding="utf-8")
    if deferred_symbol is not None:
        content = activate_deferred_candidate(content, source, deferred_symbol)
    focused_content = GLOBAL_ASM_LINE.sub("", content)
    if focused_content == content and deferred_symbol is None:
        return source
    source_relative = source.relative_to(ROOT)
    output = ROOT / "build" / profile / "diff-source" / source_relative
    output.parent.mkdir(parents=True, exist_ok=True)
    if not output.is_file() or output.read_text(encoding="utf-8") != focused_content:
        output.write_text(focused_content, encoding="utf-8")
    return output


def compile_candidate(
    profile: str, source: Path, *, deferred_symbol: str | None = None
) -> Path:
    output = candidate_object(profile, source)
    compile_source = focused_candidate_source(
        profile, source, deferred_symbol=deferred_symbol
    )
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
    try:
        relative = assembly.relative_to(ROOT / "reference").with_suffix(".s")
    except ValueError:
        relative = assembly.relative_to(ROOT).with_suffix(".s")
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
    profile: str,
    symbol: str,
    *,
    game_reference: bool = False,
) -> Path:
    """Return an exact registered raw span, refreshing a stale split when needed."""

    ensure_reference(profile, game_reference=game_reference)
    try:
        assembly = locate_function(
            profile,
            symbol,
            reference=not game_reference,
            game_reference=game_reference,
        )
    except ValueError:
        prepare_reference(profile, game_reference=game_reference)
        assembly = locate_function(
            profile,
            symbol,
            reference=not game_reference,
            game_reference=game_reference,
        )
    return extract_function(
        assembly, symbol, boundary_symbols=registered_symbols(profile)
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


def write_settings(profile: str, source: Path, *, directory: Path | None = None) -> Path:
    if directory is None:
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
    expected_size: int,
    *,
    require_match: bool = False,
    watch: bool = False,
) -> list[str]:
    if expected_size <= 0 or expected_size % 4:
        raise ValueError(f"{symbol} has an invalid {expected_size}-byte instruction span")
    command = [
        "python3",
        str(ROOT / "scripts" / "diff.py"),
        "--asm-differ",
        "-o",
        "-f",
        str(candidate),
        "-F",
        str(reference),
        "--max-lines",
        str(expected_size // 4),
    ]
    if watch:
        command.extend(["-m", "-w", "-3"])
    else:
        command.append("--no-pager")
    command.extend(["--format", "json" if require_match else "color", symbol])
    return command


def registered_span_lines(lines: list, instruction_count: int, *, reference: bool) -> list:
    """Remove display metadata, retaining every registered instruction word."""

    result = []
    for line in lines:
        # These describe incoming data relocations (for example jump-table
        # entries), not instructions. The raw text-only reference may lack
        # them, so exclude them from both span validation and match scoring.
        # Relocations attached to real instructions remain intact.
        if line.mnemonic == "<data-ref>" and line.diff_row == "<data-ref>":
            if line.line_num is not None:
                raise ValueError("asm-differ data-reference annotation has an instruction address")
            continue
        result.append(line)
    if result and result[-1].mnemonic == "..." and result[-1].original == "...":
        if result[-1].line_num is not None:
            raise ValueError("asm-differ truncation marker has an instruction address")
        result.pop()
    addresses = [line.line_num for line in result]
    if any(address is None for address in addresses):
        raise ValueError("asm-differ returned a non-instruction inside the registered span")
    if any(right != left + 4 for left, right in zip(addresses, addresses[1:])):
        raise ValueError("asm-differ returned a discontinuous registered instruction span")
    if len(result) > instruction_count or (reference and len(result) != instruction_count):
        raise ValueError("asm-differ reference does not cover the registered instruction span")
    return result


def configure_registered_span_differ(differ) -> None:
    """Adapt the pinned viewer's truncation heuristics for exact bounded matching.

    Upstream inserts a synthetic ellipsis when more object text follows the
    requested span. Its scorer can then ignore real differences after a long
    matching prefix. Exclude that display marker before alignment/scoring, and
    retain trailing nops because they are part of our reviewed byte span.
    """

    original_do_diff = differ.do_diff

    def do_registered_diff(base, current, config):
        if not config.diff_obj or config.stop_at_ret or config.arch.name != "mips":
            raise ValueError("registered-span comparison requires bounded MIPS object mode")
        count = config.max_function_size_lines
        if count <= 0:
            raise ValueError("registered-span comparison requires a positive instruction count")
        base = registered_span_lines(base, count, reference=True)
        current = registered_span_lines(current, count, reference=False)
        return original_do_diff(base, current, config)

    differ.do_diff = do_registered_diff
    differ.trim_nops = lambda lines, arch: lines


def run_pinned_asm_differ() -> None:
    spec = importlib.util.spec_from_file_location("conker_asm_differ", ASM_DIFFER)
    if spec is None or spec.loader is None:
        raise ValueError(f"cannot load pinned asm-differ: {ASM_DIFFER}")
    differ = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = differ
    spec.loader.exec_module(differ)
    configure_registered_span_differ(differ)
    differ.main()


def run_asm_diff(command: list[str], directory: Path) -> int:
    try:
        return subprocess.run(command, cwd=directory, check=False).returncode
    except KeyboardInterrupt:
        return 130
    except OSError as error:
        print(f"error: could not run asm-differ: {error}", file=sys.stderr)
        return EXIT_BLOCKED_TOOLING


def run_required_asm_diff(
    candidate: Path,
    reference: Path,
    symbol: str,
    directory: Path,
    expected_size: int,
    *,
    compact_mismatch: bool = False,
    table_check: Callable[[], None] | None = None,
) -> int:
    """Verify an exact match; optionally summarize the same mismatch evidence."""

    evidence_command = asm_diff_command(
        candidate,
        reference,
        symbol,
        expected_size,
        require_match=True,
    )
    try:
        result = subprocess.run(
            evidence_command,
            cwd=directory,
            check=False,
            capture_output=True,
            text=True,
        )
    except OSError as error:
        print(f"error: could not run asm-differ: {error}", file=sys.stderr)
        return EXIT_BLOCKED_TOOLING
    if result.returncode:
        sys.stdout.write(result.stdout)
        sys.stderr.write(result.stderr)
        return EXIT_BLOCKED_TOOLING
    try:
        require_zero_difference(result.stdout, symbol)
        if table_check is not None:
            table_check()
    except NonzeroDifferenceError as error:
        if compact_mismatch:
            try:
                print_compact_mismatch(result.stdout, symbol, directory)
            except (ValueError, OSError) as diagnostic_error:
                print(f"error: could not summarize mismatch: {diagnostic_error}", file=sys.stderr)
                return EXIT_BLOCKED_TOOLING
        else:
            display_command = asm_diff_command(
                candidate, reference, symbol, expected_size
            )
            run_asm_diff(display_command, directory)
        print(f"error: {error}", file=sys.stderr)
        return EXIT_MISMATCH
    except (ValueError, OSError) as error:
        print(f"error: {error}", file=sys.stderr)
        return EXIT_BLOCKED_TOOLING
    print(f"{symbol}: CURRENT (0)")
    return 0


def run_score_only_diff(
    candidate: Path,
    reference: Path,
    symbol: str,
    directory: Path,
    expected_size: int,
) -> int:
    """Print only the machine-readable focused-diff score for shell callers."""

    try:
        result = subprocess.run(
            asm_diff_command(
                candidate, reference, symbol, expected_size, require_match=True
            ),
            cwd=directory,
            check=False,
            capture_output=True,
            text=True,
        )
    except OSError as error:
        print(f"error: could not run asm-differ: {error}", file=sys.stderr)
        return EXIT_BLOCKED_TOOLING
    if result.returncode:
        sys.stdout.write(result.stdout)
        sys.stderr.write(result.stderr)
        return EXIT_BLOCKED_TOOLING
    try:
        score = current_difference_count(result.stdout)
        print(score)
    except ValueError as error:
        print(f"error: {error}", file=sys.stderr)
        return EXIT_BLOCKED_TOOLING
    return 0


def instruction_text(row: dict, side: str) -> str | None:
    entry = row.get(side)
    if not isinstance(entry, dict):
        return None
    fragments = entry.get("text")
    if not isinstance(fragments, list):
        return None
    return "".join(
        fragment.get("text", "") if isinstance(fragment, dict) else str(fragment)
        for fragment in fragments
    ).strip()


def diagnostic_rows(output: str) -> list[dict]:
    evidence = json.loads(output)
    if not isinstance(evidence, dict) or not isinstance(evidence.get("rows"), list):
        raise ValueError("asm-differ JSON lacks rows")
    rows = evidence["rows"]
    for row in rows:
        if not isinstance(row, dict):
            raise ValueError("asm-differ JSON contains an invalid row")
        for side in ("base", "current"):
            entry = row.get(side, {})
            if not isinstance(entry, dict) or not isinstance(entry.get("text", []), list):
                raise ValueError("asm-differ JSON contains an invalid instruction")
            for fragment in entry.get("text", []):
                if not isinstance(fragment, dict) or not isinstance(fragment.get("text"), str):
                    raise ValueError("asm-differ JSON contains an invalid text fragment")
    return rows


def diff_row_category(row: dict) -> str | None:
    """Classify visible differences conservatively, not semantic equivalence."""

    if row.get("is_data_ref"):
        return None
    # Empty cells may still contain a formatted '<' or '>' display marker.
    # The pinned formatter supplies a mnemonic only for actual instructions.
    base_mnemonic = row.get("base", {}).get("mnemonic")
    current_mnemonic = row.get("current", {}).get("mnemonic")
    if bool(base_mnemonic) != bool(current_mnemonic):
        return "missing_or_extra"
    base = instruction_text(row, "base")
    current = instruction_text(row, "current")
    if not base or not current:
        return "missing_or_extra" if base or current else None
    if row.get("base", {}).get("mnemonic") != row.get("current", {}).get("mnemonic"):
        return "opcode_or_control_flow"
    formats = {
        fragment.get("format")
        for side in ("base", "current")
        for fragment in row.get(side, {}).get("text", [])
        if isinstance(fragment, dict) and fragment.get("format")
    }
    # Register coloring can coexist with changed immediates, stack offsets or
    # branch targets. These must not be advertised as register-only differences.
    if formats & {"immediate", "stack", "diff_change"}:
        return "operand_or_constant"
    # The formatter includes diff markers, C line numbers, offsets and branch
    # arrows. Use the structured mnemonic to find the actual instruction.
    def operands(text: str, side: str) -> str:
        mnemonic = row.get(side, {}).get("mnemonic")
        if isinstance(mnemonic, str):
            match = re.search(rf"(?<!\S){re.escape(mnemonic)}(?=\s|$)", text)
            if match:
                text = text[match.start():]
        return " ".join(text.replace("~>", "").split())

    base, current = operands(base, "base"), operands(current, "current")
    # Object-relative branch addresses move when a candidate has preceding C.
    # Compare the encoded PC-relative displacement, using structured evidence
    # and checking the displayed operand before replacing it. Never normalize
    # absolute jumps, symbolic relocations, or missing address evidence.
    relative_branches = {
        "b", "bal", "beq", "beql", "beqz", "beqzl", "bne", "bnel",
        "bnez", "bnezl", "bgez", "bgezl", "bgezal", "bgezall", "bgtz",
        "bgtzl", "blez", "blezl", "bltz", "bltzl", "bltzal", "bltzall",
        "bc1f", "bc1fl", "bc1t", "bc1tl",
    }
    if base_mnemonic in relative_branches:
        def relative_operand(text: str, side: str) -> str:
            entry = row[side]
            address, target = entry.get("line"), entry.get("branch")
            match = re.search(r"(?<=[,\s])(?:0x)?[0-9a-fA-F]+$", text)
            if (type(address) is int and type(target) is int and match
                    and int(match.group(), 16) == target):
                return text[:match.start()] + f"<branch:{target - address}>"
            return text
        base, current = relative_operand(base, "base"), relative_operand(current, "current")
    if base == current:
        return None
    if MIPS_REGISTER.sub("REG", base) == MIPS_REGISTER.sub("REG", current):
        return "register_only"
    return "operand_or_constant"


def is_stack_difference(row: dict) -> bool:
    """Accept only identical opcodes/registers with one changed SP immediate."""
    if diff_row_category(row) != "operand_or_constant":
        return False
    mnemonic = row.get("base", {}).get("mnemonic")
    if mnemonic not in {"addiu", "addi", "lw", "sw", "lh", "lhu", "sh", "lb", "lbu", "sb", "lwc1", "swc1", "ldc1", "sdc1"}:
        return False
    normalized = []
    for side in ("base", "current"):
        text = instruction_text(row, side) or ""
        match = re.search(rf"(?<!\S){mnemonic}\s+(.+)$", text)
        if not match:
            return False
        operands = re.sub(r"\s+", "", match[1]).replace("$", "")
        immediate = r"-?(?:0x[0-9a-fA-F]+|[0-9]+)"
        pattern = (rf"(?<=,sp,){immediate}$" if mnemonic in {"addi", "addiu"}
                   else rf"{immediate}(?=\(sp\)$)")
        operands, count = re.subn(pattern, "<slot>", operands)
        if count != 1:
            return False
        normalized.append(operands)
    return normalized[0] == normalized[1]


def classify_diff_rows(rows: list[dict]) -> dict[str, int]:
    """Summarize asm-differ rows into actionable source-shaping categories."""

    counts = {
        "register_only": 0,
        "operand_or_constant": 0,
        "opcode_or_control_flow": 0,
        "missing_or_extra": 0,
    }
    for row in rows:
        category = diff_row_category(row)
        if category is not None:
            counts[category] += 1
    return counts


def print_diagnosis(symbol: str, score: int, counts: dict[str, int], stack_rows: int = 0) -> None:
    print(f"{symbol}: CURRENT ({score})")
    for category, count in counts.items():
        print(f"{category.replace('_', '-')}: {count}")
    print(f"stack-rows: {stack_rows}")
    if score and stack_rows and stack_rows == counts["operand_or_constant"] and not (counts["opcode_or_control_flow"] or counts["missing_or_extra"]):
        print("recommendation: bounded stack-shape probe")
    elif score and counts["register_only"] and not any(
        count for category, count in counts.items() if category != "register_only"
    ):
        print("recommendation: bounded declaration/lifetime permutation")
    elif score:
        print("recommendation: inspect full diff for expression, operand or control-flow differences")
    else:
        print("recommendation: run finish")


def print_compact_mismatch(output: str, symbol: str, directory: Path) -> None:
    rows = diagnostic_rows(output)
    score = current_difference_count(output)
    counts = classify_diff_rows(rows)
    details = directory / symbol
    details.mkdir(parents=True, exist_ok=True)
    evidence_path = details / "mismatch.json"
    text_path = details / "mismatch.txt"
    lines = [
        f"{instruction_text(row, 'base') or '-'} | {instruction_text(row, 'current') or '-'}"
        for row in rows
    ]
    for path, content in (
        (evidence_path, output),
        (text_path, f"{symbol}: CURRENT ({score})\nreference | candidate\n" + "\n".join(lines) + "\n"),
    ):
        temporary = path.with_suffix(path.suffix + ".tmp")
        temporary.write_text(content, encoding="utf-8")
        temporary.replace(path)
    print_diagnosis(symbol, score, counts, sum(is_stack_difference(row) for row in rows))
    differing = [line for row, line in zip(rows, lines) if diff_row_category(row) is not None]
    print(f"diff-excerpt: first {min(5, len(differing))} of {len(differing)} differing rows (reference | candidate)")
    for line in differing[:5]:
        print("  " + (line[:157] + "..." if len(line) > 160 else line))
    for label, path in (("full-diff", text_path), ("diff-evidence", evidence_path)):
        print(f"{label}: {path.relative_to(ROOT) if path.is_relative_to(ROOT) else path}")


def run_diagnose_diff(
    candidate: Path,
    reference: Path,
    symbol: str,
    directory: Path,
    expected_size: int,
    *, table_check: Callable[[], None] | None = None,
) -> int:
    try:
        result = subprocess.run(
            asm_diff_command(
                candidate, reference, symbol, expected_size, require_match=True
            ),
            cwd=directory,
            check=False,
            capture_output=True,
            text=True,
        )
    except OSError as error:
        print(f"error: could not run asm-differ: {error}", file=sys.stderr)
        return EXIT_BLOCKED_TOOLING
    if result.returncode:
        sys.stdout.write(result.stdout)
        sys.stderr.write(result.stderr)
        return EXIT_BLOCKED_TOOLING
    try:
        score = current_difference_count(result.stdout)
        rows = diagnostic_rows(result.stdout)
        counts = classify_diff_rows(rows)
        if score:
            print_compact_mismatch(result.stdout, symbol, directory)
        else:
            if table_check is not None:
                table_check()
            print_diagnosis(symbol, score, counts, sum(is_stack_difference(row) for row in rows))
    except (json.JSONDecodeError, ValueError, OSError) as error:
        print(f"error: asm-differ returned invalid diagnostic evidence: {error}", file=sys.stderr)
        return EXIT_BLOCKED_TOOLING
    return 0


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("profile", choices=("us", "eu"))
    parser.add_argument("symbol")
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument("--game", action="store_true", help="compare a registered game-overlay candidate")
    mode.add_argument("--auto-overlay", action="store_true", help="resolve the overlay from the work-item ID")
    parser.add_argument("--require-match", action="store_true", help="fail unless asm-differ reports CURRENT (0)")
    parser.add_argument("--compact-mismatch", action="store_true", help="summarize failed --require-match evidence without rerunning the differ")
    parser.add_argument("--score-only", action="store_true", help="print only the focused-diff score")
    parser.add_argument("--diagnose", action="store_true", help="classify focused differences, including a preserved deferred candidate")
    parser.add_argument("--watch", action="store_true", help="watch the candidate source and rebuild inside this container")
    arguments = parser.parse_args()
    if arguments.compact_mismatch and not arguments.require_match:
        parser.error("--compact-mismatch requires --require-match")
    if arguments.watch and (arguments.require_match or arguments.score_only or arguments.diagnose):
        parser.error("--watch cannot be combined with --require-match or --score-only")
    if arguments.require_match and arguments.score_only:
        parser.error("--require-match and --score-only cannot be combined")
    if arguments.diagnose and (arguments.require_match or arguments.score_only):
        parser.error("--diagnose cannot be combined with --require-match or --score-only")

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
            arguments.profile,
            symbol,
            game_reference=game_reference,
        )
        expected_size = expected_function_size(arguments.profile, symbol)
        if not source.is_file():
            raise ValueError(f"candidate source does not exist: {source.relative_to(ROOT)}")
    except (ValueError, subprocess.CalledProcessError, OSError) as error:
        print(f"error: {error}", file=sys.stderr)
        return EXIT_BLOCKED_TOOLING

    try:
        deferred_symbol = (
            arguments.symbol
            if arguments.diagnose and work_item_is_deferred(arguments.symbol)
            else None
        )
        if deferred_symbol is None:
            require_c_implementation(source, arguments.symbol)
        candidate = compile_candidate(
            arguments.profile, source, deferred_symbol=deferred_symbol
        )
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

    table_options = {}
    if arguments.profile == "us" and game_reference:
        table_options["table_check"] = lambda: candidate_tables.verify_candidate(
            candidate, symbol, reference_assembly, expected_size)
    directory = write_settings(arguments.profile, source)
    if arguments.score_only:
        return run_score_only_diff(candidate, reference, symbol, directory, expected_size)
    if arguments.diagnose:
        return run_diagnose_diff(
            candidate, reference, symbol, directory, expected_size, **table_options
        )
    if arguments.require_match:
        return run_required_asm_diff(
            candidate, reference, symbol, directory, expected_size,
            compact_mismatch=arguments.compact_mismatch, **table_options,
        )
    command = asm_diff_command(
        candidate,
        reference,
        symbol,
        expected_size,
        watch=arguments.watch,
    )
    return run_asm_diff(command, directory)


if __name__ == "__main__":
    if sys.argv[1:2] == ["--asm-differ"]:
        del sys.argv[1]
        try:
            run_pinned_asm_differ()
        except (ValueError, OSError) as error:
            print(f"error: {error}", file=sys.stderr)
            raise SystemExit(EXIT_BLOCKED_TOOLING)
    else:
        raise SystemExit(main())
