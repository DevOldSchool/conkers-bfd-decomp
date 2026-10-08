#!/usr/bin/env python3
"""Score source variants and inspect stack layout without touching the work tree.

`probe` is a fast, read-only companion to `finish`. Each variant is compiled
with the pinned IDO flags into `build/<profile>/probe/<symbol>/` and scored with
the same asm-differ focused comparison that `diff` uses. Scores are search
evidence only; `finish` remains the authoritative gate.
"""

from __future__ import annotations

import argparse
import re
import struct
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

import compile_c
import diff
import project_state

ROOT = diff.ROOT

# mdebug symbol types and storage classes used by IDO's -g3 symbol table.
ST_PROC = 6
ST_STATIC_PROC = 14
ST_LOCAL = 4
ST_PARAM = 3
ST_BLOCK = 7
ST_END = 8
SC_ABS = 5


class ProbeError(Exception):
    """A probe could not be completed."""


class VariantError(ProbeError):
    """One variant was rejected (splice or compiler error); other variants may run."""


class ToolingError(ProbeError):
    """The scorer or object inspection failed; the batch result is unreliable."""


@dataclass(frozen=True)
class Local:
    kind: str
    name: str
    frame_offset: int  # relative to the frame top (negative for locals)


def definition_names(content: str, regional_symbol: str) -> list[str]:
    """Names whose definition emits ``regional_symbol``: itself or a profile macro alias.

    A work-item ID that differs from the regional symbol (for example
    ``func_bootstrap_clear_region`` for ``func_80001420``) names only the pragma;
    a function defined under that ID would not emit the symbol being scored.
    """

    alias = re.compile(
        rf"(?m)^\s*#\s*define\s+([A-Za-z_]\w*)\s+{re.escape(regional_symbol)}\s*$"
    )
    names = [regional_symbol, *(match.group(1) for match in alias.finditer(content))]
    return list(dict.fromkeys(names))


def defines_any(content: str, names: list[str]) -> bool:
    for name in names:
        try:
            project_state.c_function_span(content, name)
        except project_state.ProjectStateError:
            continue
        return True
    return False


def splice_variant(content: str, identifier: str, regional_symbol: str,
                   source_relative: str, variant: str) -> str:
    """Replace the work item's definition (or GLOBAL_ASM pragma) with ``variant``.

    A variant containing ``#include`` is treated as a complete source file.
    Otherwise it may carry helper declarations before the function definition,
    which must emit the regional symbol directly or through a profile macro alias.
    """

    if re.search(r"^[ \t]*#include\b", variant, re.MULTILINE):
        return variant
    names = definition_names(content, regional_symbol)
    if not defines_any(variant, names):
        raise VariantError(
            f"variant does not define {regional_symbol} for {identifier} "
            f"(define it as: {', '.join(names)})"
        )
    replacement = variant if variant.endswith("\n") else variant + "\n"
    pragma = project_state.global_asm_pragma(source_relative, identifier)
    pragma_line = re.compile(r"(?m)^[ \t]*" + re.escape(pragma) + r"[ \t]*\n?")
    match = pragma_line.search(content)
    if match is not None:
        start, end = match.span()
    else:
        try:
            start, end = project_state.work_item_function_span(content, identifier, regional_symbol)
        except project_state.ProjectStateError as error:
            raise VariantError(f"source has neither a C definition nor a GLOBAL_ASM pragma: {error}") from error
    return content[:start] + replacement + content[end:]


def _section(data: bytes, name: str) -> tuple[int, int]:
    if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 2:
        raise ProbeError("expected a 32-bit big-endian ELF object")
    shoff = struct.unpack(">I", data[0x20:0x24])[0]
    shentsize, shnum, shstrndx = struct.unpack(">HHH", data[0x2E:0x34])
    headers = [
        struct.unpack(">IIIIIIIIII", data[shoff + i * shentsize : shoff + i * shentsize + 40])
        for i in range(shnum)
    ]
    strtab = headers[shstrndx][4]
    for header in headers:
        start = strtab + header[0]
        if data[start : data.index(b"\0", start)].decode() == name:
            return header[4], header[5]
    raise ProbeError(f"object has no {name} section; compile with -g3")


def mdebug_locals(path: Path, symbol: str) -> list[Local]:
    """Read parameters and locals of ``symbol`` from IDO's .mdebug table."""

    data = path.read_bytes()
    offset, _size = _section(data, ".mdebug")
    header = struct.unpack(">hh" + "i" * 23, data[offset : offset + 0x60])
    symbol_count, symbol_offset = header[9], header[10]
    string_offset = header[16]
    found: list[Local] = []
    inside = False
    for index in range(symbol_count):
        entry = symbol_offset + index * 12
        iss, value, bits = struct.unpack(">iiI", data[entry : entry + 12])
        st, sc = bits >> 26, (bits >> 21) & 0x1F
        name = ""
        if iss >= 0:
            start = string_offset + iss
            name = data[start : data.index(b"\0", start)].decode(errors="replace")
        if st in (ST_PROC, ST_STATIC_PROC):
            if inside:
                break
            inside = name == symbol
            continue
        if inside and st in (ST_LOCAL, ST_PARAM) and sc == SC_ABS:
            found.append(Local("param" if st == ST_PARAM else "local", name, value))
    if not inside and not found:
        raise ProbeError(f"{symbol} not found in .mdebug")
    return found


FRAME = re.compile(r"addiu\s+\$?sp,\s*\$?sp,\s*-(0x[0-9A-Fa-f]+|\d+)")


def object_frame_size(path: Path, symbol: str) -> int | None:
    try:
        output = subprocess.run(
            ["mips-linux-gnu-objdump", "-d", "--no-show-raw-insn", str(path)],
            cwd=ROOT, check=True, capture_output=True, text=True,
        ).stdout
    except (OSError, subprocess.CalledProcessError) as error:
        raise ToolingError(f"objdump failed for {path}: {error}") from error
    start = output.find(f"<{symbol}>:")
    if start < 0:
        raise ToolingError(f"{symbol} not found in {path}")
    for line in output[start:].split("\n")[1:12]:
        if re.match(r"^[0-9a-f]+ <", line):
            break
        match = FRAME.search(line)
        if match:
            return int(match.group(1), 0)
    return None


def reference_frame_size(assembly: Path, symbol: str) -> int | None:
    text = assembly.read_text(encoding="utf-8")
    start = text.find(f"glabel {symbol}")
    if start < 0:
        return None
    for line in text[start:].split("\n")[1:12]:
        if line.startswith("glabel "):
            break
        match = FRAME.search(re.sub(r"/\*.*?\*/", "", line))
        if match:
            return int(match.group(1), 0)
    return None


@dataclass
class Target:
    identifier: str
    profile: str
    source: Path
    symbol: str
    assembly: Path
    reference: Path
    expected_size: int
    directory: Path


def resolve(identifier: str, profile: str) -> Target:
    source, symbol, game_reference = diff.find_work_item_by_id(identifier, profile)
    assembly = diff.ensure_reference_function(profile, symbol, game_reference=game_reference)
    reference = diff.reference_object(profile, symbol, game_reference=game_reference, assembly=assembly)
    directory = ROOT / "build" / profile / "probe" / symbol
    directory.mkdir(parents=True, exist_ok=True)
    return Target(identifier, profile, source, symbol, assembly, reference,
                  diff.expected_function_size(profile, symbol), directory)


def probe_source(target: Target, variant: Path | None) -> str:
    """Return the focused source for one probe without editing the work tree."""

    content = target.source.read_text(encoding="utf-8")
    source_relative = target.source.relative_to(ROOT).as_posix()
    if variant is not None:
        return splice_variant(content, target.identifier, target.symbol, source_relative,
                              variant.read_text(encoding="utf-8"))
    if diff.work_item_is_deferred(target.identifier):
        return diff.activate_deferred_candidate(content, target.source, target.identifier)
    pragma = project_state.global_asm_pragma(source_relative, target.identifier)
    if pragma in content:
        raise VariantError(f"{target.identifier} has no C definition to probe; pass a variant file")
    return content


def build_variant(target: Target, variant: Path | None, index: int) -> Path:
    content = diff.GLOBAL_ASM_LINE.sub("", probe_source(target, variant))
    stem = f"variant{index:03d}" if variant is not None else "current"
    source = target.directory / f"{stem}.c"
    output = target.directory / f"{stem}.o"
    source.write_text(content, encoding="utf-8")
    output.unlink(missing_ok=True)
    try:
        result = subprocess.run(
            compile_c.compile_command(target.profile, source, output),
            cwd=ROOT, capture_output=True, text=True,
        )
    except OSError as error:
        raise ToolingError(f"could not run the compiler: {error}") from error
    if result.returncode:
        message = "\n".join(line for line in result.stdout.splitlines() + result.stderr.splitlines()
                            if "Error" in line or "error" in line)
        raise VariantError(message.strip() or "compile failed")
    return output


def score(target: Target, candidate: Path) -> int:
    settings = diff.write_settings(target.profile, target.source, directory=target.directory)
    try:
        result = subprocess.run(
            diff.asm_diff_command(candidate, target.reference, target.symbol,
                                  target.expected_size, require_match=True),
            cwd=settings, capture_output=True, text=True,
        )
    except (OSError, ValueError) as error:
        raise ToolingError(f"could not run asm-differ: {error}") from error
    if result.returncode:
        raise ToolingError((result.stderr or result.stdout).strip() or "asm-differ failed")
    try:
        return diff.current_difference_count(result.stdout)
    except ValueError as error:
        raise ToolingError(f"asm-differ returned an invalid score: {error}") from error


def print_layout(target: Target, candidate: Path) -> None:
    frame = object_frame_size(candidate, target.symbol)
    reference_frame = reference_frame_size(target.assembly, target.symbol)
    print(f"frame: candidate {hex(frame) if frame is not None else 'leaf'}"
          f", reference {hex(reference_frame) if reference_frame is not None else 'leaf'}")
    locals_ = mdebug_locals(candidate, target.symbol)
    if frame is None:
        frame = 0
    print(f"{'kind':6} {'sp offset':>9}  name")
    for entry in sorted(locals_, key=lambda item: -item.frame_offset):
        print(f"{entry.kind:6} {hex(frame + entry.frame_offset):>9}  {entry.name}")
    named = [entry for entry in locals_ if entry.kind == "local"]
    if named and frame:
        floor = min(frame + entry.frame_offset for entry in named)
        print(f"lowest local: {hex(floor)} (outgoing args, saved registers and reserved spill words lie below)")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("profile", choices=("us", "eu"))
    parser.add_argument("identifier")
    parser.add_argument("variants", nargs="*", type=Path,
                        help="function-definition or complete-source variant files")
    parser.add_argument("--layout", action="store_true",
                        help="print frame size and named-local stack offsets")
    arguments = parser.parse_intermixed_args()
    try:
        target = resolve(arguments.identifier, arguments.profile)
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        print(f"error: {error}", file=sys.stderr)
        return diff.EXIT_BLOCKED_TOOLING

    if arguments.layout:
        if len(arguments.variants) > 1:
            parser.error("--layout accepts at most one variant")
        variant = arguments.variants[0] if arguments.variants else None
        try:
            candidate = build_variant(target, variant, 0)
            print(f"{target.symbol}: CURRENT ({score(target, candidate)}) [probe]")
            print_layout(target, candidate)
        except VariantError as error:
            print(f"error: {error}", file=sys.stderr)
            return diff.EXIT_FIX_COMPILE
        except (ProbeError, OSError) as error:
            print(f"error: {error}", file=sys.stderr)
            return diff.EXIT_BLOCKED_TOOLING
        return 0

    variants: list[Path | None] = list(arguments.variants) or [None]
    results: list[tuple[int, str, str]] = []
    for index, variant in enumerate(variants, start=1):
        label = "current source" if variant is None else str(variant)
        try:
            candidate = build_variant(target, variant, index)
        except VariantError as error:
            first = str(error).splitlines()[0] if str(error) else "variant rejected"
            print(f"skip {label}: {first}", file=sys.stderr)
            continue
        except (ProbeError, OSError) as error:
            print(f"error: {label}: {error}", file=sys.stderr)
            return diff.EXIT_BLOCKED_TOOLING
        try:
            value = score(target, candidate)
            frame = object_frame_size(candidate, target.symbol)
        except (ProbeError, OSError) as error:
            # A scorer failure makes any ranking unreliable; stop without a partial result.
            print(f"error: scoring {label} failed: {error}", file=sys.stderr)
            return diff.EXIT_BLOCKED_TOOLING
        results.append((value, label, hex(frame) if frame is not None else "leaf"))
    if not results:
        print("error: no variant compiled", file=sys.stderr)
        return diff.EXIT_FIX_COMPILE
    reference_frame = reference_frame_size(target.assembly, target.symbol)
    print(f"{target.symbol}: reference frame {hex(reference_frame) if reference_frame else 'leaf'}")
    for value, label, frame in sorted(results, key=lambda item: item[0]):
        print(f"CURRENT ({value})\tframe {frame}\t{label}")
    if min(result[0] for result in results) == 0:
        print("note: a probe zero is not a match; apply the variant and run ./conker finish")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
