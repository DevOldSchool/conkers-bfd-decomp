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
    """A variant or object could not be processed."""


@dataclass(frozen=True)
class Local:
    kind: str
    name: str
    frame_offset: int  # relative to the frame top (negative for locals)


def _matching_brace(content: str, open_index: int) -> int:
    depth = 0
    index = open_index
    length = len(content)
    while index < length:
        char = content[index]
        if content.startswith("/*", index):
            end = content.find("*/", index + 2)
            if end < 0:
                break
            index = end + 2
            continue
        if content.startswith("//", index):
            end = content.find("\n", index)
            index = length if end < 0 else end
            continue
        if char in "\"'":
            index += 1
            while index < length and content[index] != char:
                index += 2 if content[index] == "\\" else 1
        elif char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
            if depth == 0:
                return index
        index += 1
    raise ProbeError("unbalanced braces in function definition")


def definition_span(content: str, symbol: str) -> tuple[int, int] | None:
    """Return the [start, end) span of a top-level C definition of ``symbol``."""

    pattern = re.compile(
        r"^(?![ \t#])[^;{}\n]*\b" + re.escape(symbol) + r"[ \t]*\(([^;{}]*)\)[ \t\n]*\{",
        re.MULTILINE,
    )
    for match in pattern.finditer(content):
        if _inside_disabled_block(content, match.start()):
            continue
        close = _matching_brace(content, match.end() - 1)
        end = close + 1
        if content[end : end + 1] == "\n":
            end += 1
        return match.start(), end
    return None


def _inside_disabled_block(content: str, index: int) -> bool:
    before = content[:index]
    tag = "CONKER_DEFERRED_CANDIDATE"
    return before.count(f"#if 0 /* {tag} ") > before.count(f"#endif /* {tag} ")


def splice_variant(content: str, symbol: str, variant: str) -> str:
    """Replace ``symbol``'s definition (or GLOBAL_ASM pragma) with ``variant``.

    A variant containing ``#include`` is treated as a complete source file.
    Otherwise it may carry helper declarations before the function definition.
    """

    if re.search(r"^[ \t]*#include\b", variant, re.MULTILINE):
        return variant
    if definition_span(variant, symbol) is None:
        raise ProbeError(f"variant does not define {symbol}")
    replacement = variant if variant.endswith("\n") else variant + "\n"
    span = definition_span(content, symbol)
    if span is None:
        pragma = re.compile(
            r'^[ \t]*#pragma[ \t]+GLOBAL_ASM\("[^"\n]*/' + re.escape(symbol) + r'\.s"\)[ \t]*\n',
            re.MULTILINE,
        )
        match = pragma.search(content)
        if match is None:
            raise ProbeError(f"source has neither a C definition nor a GLOBAL_ASM pragma for {symbol}")
        span = (match.start(), match.end())
    start, end = span
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
    output = subprocess.run(
        ["mips-linux-gnu-objdump", "-d", "--no-show-raw-insn", str(path)],
        cwd=ROOT, check=True, capture_output=True, text=True,
    ).stdout
    start = output.find(f"<{symbol}>:")
    if start < 0:
        raise ProbeError(f"{symbol} not found in {path}")
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


def build_variant(target: Target, variant: Path | None, index: int) -> Path:
    content = target.source.read_text(encoding="utf-8")
    if variant is not None:
        content = splice_variant(content, target.symbol, variant.read_text(encoding="utf-8"))
    content = diff.GLOBAL_ASM_LINE.sub("", content)
    if definition_span(content, target.symbol) is None:
        raise ProbeError(f"{target.symbol} has no C definition to probe")
    stem = f"variant{index:03d}" if variant is not None else "current"
    source = target.directory / f"{stem}.c"
    output = target.directory / f"{stem}.o"
    source.write_text(content, encoding="utf-8")
    output.unlink(missing_ok=True)
    result = subprocess.run(
        compile_c.compile_command(target.profile, source, output),
        cwd=ROOT, capture_output=True, text=True,
    )
    if result.returncode:
        message = "\n".join(line for line in result.stdout.splitlines() + result.stderr.splitlines()
                            if "Error" in line or "error" in line)
        raise ProbeError(message.strip() or "compile failed")
    return output


def score(target: Target, candidate: Path) -> int:
    settings = diff.write_settings(target.profile, target.source, directory=target.directory)
    result = subprocess.run(
        diff.asm_diff_command(candidate, target.reference, target.symbol,
                              target.expected_size, require_match=True),
        cwd=settings, capture_output=True, text=True,
    )
    if result.returncode:
        raise ProbeError((result.stderr or result.stdout).strip() or "asm-differ failed")
    return diff.current_difference_count(result.stdout)


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
        except (ProbeError, ValueError, OSError, subprocess.CalledProcessError) as error:
            print(f"error: {error}", file=sys.stderr)
            return diff.EXIT_BLOCKED_TOOLING
        return 0

    variants: list[Path | None] = list(arguments.variants) or [None]
    results: list[tuple[int, str, str]] = []
    for index, variant in enumerate(variants, start=1):
        label = "current source" if variant is None else str(variant)
        try:
            candidate = build_variant(target, variant, index)
            value = score(target, candidate)
            frame = object_frame_size(candidate, target.symbol)
            results.append((value, label, hex(frame) if frame is not None else "leaf"))
        except (ProbeError, ValueError, OSError, subprocess.CalledProcessError) as error:
            first = str(error).splitlines()[0] if str(error) else type(error).__name__
            print(f"skip {label}: {first}", file=sys.stderr)
    if not results:
        print("error: no variant compiled and scored", file=sys.stderr)
        return diff.EXIT_FIX_COMPILE
    reference_frame = reference_frame_size(target.assembly, target.symbol)
    print(f"{target.symbol}: reference frame {hex(reference_frame) if reference_frame else 'leaf'}")
    for value, label, frame in sorted(results, key=lambda item: item[0]):
        print(f"CURRENT ({value})\tframe {frame}\t{label}")
    best = min(result[0] for result in results)
    if best == 0:
        print("note: a probe zero is not a match; apply the variant and run ./conker finish")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
