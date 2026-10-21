#!/usr/bin/env python3
"""Score source variants and inspect stack layout without touching the work tree.

`probe` is a fast, read-only companion to `finish`. Each variant is compiled
with the pinned IDO flags into `build/<profile>/probe/<symbol>/` and scored with
the same asm-differ focused comparison that `diff` uses. Scores are search
evidence only; `finish` remains the authoritative gate.
"""

from __future__ import annotations

import argparse
import functools
import re
import struct
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

import compile_c
import diff
import frame_plan
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
# mdebug auxiliary type records (TIR basic types and type qualifiers).
BT_SIZES = {1: 4, 2: 1, 3: 1, 4: 2, 5: 2, 6: 4, 7: 4, 8: 4, 9: 4, 10: 4, 11: 8, 27: 8, 28: 8}
BT_STRUCT, BT_UNION, BT_ENUM, BT_TYPEDEF = 12, 13, 14, 15
TQ_PTR, TQ_PROC, TQ_ARRAY = 1, 2, 3
RFD_ESCAPE = 0xFFF
HEADER_DIRECTORIES = ("include", "lib/ultralib/include")
PAD_LOCAL = "conker_layout_pad"


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
    size: int | None = None  # bytes, from the .mdebug type records
    block: bool = False  # declared in a block nested inside the function body
    aggregate: bool = False  # array, struct or union


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


def _signed(value: int) -> int:
    return value - (1 << 32) if value & 0x80000000 else value


@dataclass(frozen=True)
class _MdebugFile:
    string_base: int
    symbol_base: int
    symbol_count: int
    aux_base: int
    rfd_base: int
    rfd_count: int


@dataclass
class _Mdebug:
    files: list[_MdebugFile]
    symbols: list[tuple[str, int, int, int, int]]  # name, value, st, sc, aux index
    aux: list[int]
    rfds: list[int]

    def file_of(self, file: int, rfd: int) -> int | None:
        """File index a relative file descriptor of ``file`` names."""

        entry = self.files[file]
        if not entry.rfd_count:
            return rfd if 0 <= rfd < len(self.files) else None
        position = entry.rfd_base + rfd
        return self.rfds[position] if 0 <= rfd < entry.rfd_count and position < len(self.rfds) else None

    def type_size(self, file: int, index: int, depth: int = 0) -> tuple[int, bool] | None:
        """(bytes, aggregate) of ``file``'s type record ``index``, or None when unreadable.

        The record is a TIR word, an optional bitfield width, a symbol reference
        for struct, union, enum and typedef types, then bounds and element width
        for each array qualifier. The last qualifier is the outermost declarator.
        """

        if depth > 8:
            return None
        aux = self.aux
        try:
            position = self.files[file].aux_base + index
            tir = aux[position]
            basic = (tir >> 24) & 0x3F
            qualifiers = [(tir >> shift) & 0xF for shift in (12, 8, 4, 0, 20, 16)]
            qualifiers = qualifiers[: qualifiers.index(0)] if 0 in qualifiers else qualifiers
            position += 1 + (tir >> 31)
            referenced = None
            if basic in (BT_STRUCT, BT_UNION, BT_ENUM, BT_TYPEDEF):
                word = aux[position]
                rfd = word >> 20
                position += 1
                if rfd == RFD_ESCAPE:
                    rfd = aux[position]
                    position += 1
                target = self.file_of(file, rfd)
                if target is None:
                    return None
                referenced = (target, self.files[target].symbol_base + (word & 0xFFFFF))
            arrays = []
            for qualifier in qualifiers:
                if qualifier != TQ_ARRAY:
                    continue
                position += 2 if aux[position] >> 20 == RFD_ESCAPE else 1
                low, high, width = _signed(aux[position]), _signed(aux[position + 1]), aux[position + 2]
                position += 3
                arrays.append((high - low + 1) * width // 8)
            if qualifiers:
                if qualifiers[-1] in (TQ_PTR, TQ_PROC):
                    return 4, False
                if qualifiers[-1] == TQ_ARRAY:
                    return arrays[-1], True
                return None
            if basic in BT_SIZES:
                return BT_SIZES[basic], False
            if basic == BT_ENUM:
                return 4, False
            if referenced is None:
                return None
            target, symbol = referenced
            if basic in (BT_STRUCT, BT_UNION):
                return self.symbols[symbol][1], True
            return self.type_size(target, self.symbols[symbol][4], depth + 1)
        except (IndexError, TypeError, ValueError):
            return None


def _read_mdebug(data: bytes) -> _Mdebug:
    offset, _size = _section(data, ".mdebug")
    header = struct.unpack(">hh" + "i" * 23, data[offset : offset + 0x60])
    symbol_count, symbol_offset = header[9], header[10]
    aux_count, aux_offset = header[13], header[14]
    string_offset = header[16]
    file_count, file_offset, rfd_count, rfd_offset = header[19], header[20], header[21], header[22]

    def words(count: int, start: int) -> list[int]:
        if count <= 0 or start + 4 * count > len(data):
            return []
        return list(struct.unpack(f">{count}I", data[start : start + 4 * count]))

    files = []
    for index in range(max(file_count, 0)):
        fields = struct.unpack(">IIIIIIIIIIhhIIIIIII", data[file_offset + 72 * index : file_offset + 72 * index + 72])
        files.append(_MdebugFile(fields[2], fields[4], fields[5], fields[12], fields[14], fields[15]))
    if not files:
        files = [_MdebugFile(0, 0, symbol_count, 0, 0, 0)]
    symbols: list[tuple[str, int, int, int, int]] = [("", 0, 0, 0, 0)] * symbol_count
    for file in files:
        for index in range(file.symbol_base, min(file.symbol_base + file.symbol_count, symbol_count)):
            entry = symbol_offset + index * 12
            iss, value, bits = struct.unpack(">iiI", data[entry : entry + 12])
            name = ""
            if iss >= 0:
                start = string_offset + file.string_base + iss
                name = data[start : data.index(b"\0", start)].decode(errors="replace")
            symbols[index] = (name, value, bits >> 26, (bits >> 21) & 0x1F, bits & 0xFFFFF)
    return _Mdebug(files, symbols, words(aux_count, aux_offset), words(rfd_count, rfd_offset))


def mdebug_locals(path: Path, symbol: str) -> list[Local]:
    """Read parameters and locals of ``symbol`` from IDO's .mdebug table.

    Locals keep declaration order, their sizes from the type records and
    whether they sit in a block nested inside the function body block.
    """

    table = _read_mdebug(path.read_bytes())
    found: list[Local] = []
    inside = False
    for file_index, file in enumerate(table.files):
        depth = 0
        for name, value, st, sc, aux_index in table.symbols[file.symbol_base : file.symbol_base + file.symbol_count]:
            if st in (ST_PROC, ST_STATIC_PROC):
                if inside:
                    break
                inside, depth = name == symbol, 0
                continue
            if not inside:
                continue
            if st == ST_BLOCK:
                depth += 1
            elif st == ST_END:
                if depth == 0:
                    break
                depth -= 1
            elif st in (ST_LOCAL, ST_PARAM) and sc == SC_ABS:
                typed = table.type_size(file_index, aux_index)
                size, aggregate = typed if typed is not None else (None, False)
                found.append(Local("param" if st == ST_PARAM else "local", name, value, size,
                                   st == ST_LOCAL and depth >= 2, aggregate))
        if inside:
            break
    if not inside and not found:
        raise ProbeError(f"{symbol} not found in .mdebug")
    return found


FRAME = re.compile(r"addiu\s+\$?sp,\s*\$?sp,\s*-(0x[0-9A-Fa-f]+|\d+)")


def object_disassembly(path: Path) -> str:
    try:
        return subprocess.run(
            ["mips-linux-gnu-objdump", "-d", "--no-show-raw-insn", str(path)],
            cwd=ROOT, check=True, capture_output=True, text=True,
        ).stdout
    except (OSError, subprocess.CalledProcessError) as error:
        raise ToolingError(f"objdump failed for {path}: {error}") from error


def object_frame_size(path: Path, symbol: str) -> int | None:
    return disassembly_frame_size(object_disassembly(path), symbol, path)


def disassembly_frame_size(output: str, symbol: str, path: Path) -> int | None:
    """Frame size from the prologue of ``symbol`` in ``objdump -d`` text, or None for a leaf."""

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
        result = compile_c.run_compile(target.profile, source, output,
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


def layout_lines(frame: int | None, reference_frame: int | None, locals_: list[Local],
                 reference: frame_plan.FramePlan | None, reference_error: str | None = None) -> list[str]:
    """Candidate .mdebug homes beside the reference frame plan, aligned by frame-top offset.

    Named locals are allocated from the frame top on both sides, so rows are keyed
    by the offset from each side's own frame top; each side's sp offset is shown too.
    """

    lines = [f"frame: candidate {hex(frame) if frame is not None else 'leaf'}"
             f", reference {hex(reference_frame) if reference_frame is not None else 'leaf'}"]
    candidate_frame = frame or 0
    candidate_rows: dict[int, list[str]] = {}
    for entry in locals_:
        candidate_rows.setdefault(entry.frame_offset, []).append(f"{entry.kind} {entry.name}")
    reference_rows: dict[int, str] = {}
    if reference is not None:
        for slot in reference.slots:
            reference_rows[slot.offset - reference.frame_size] = f"{slot.area} {slot.summary()}"
        if reference.local_area is not None:
            low, high = reference.local_area
            for word in range(low, high, 4):
                reference_rows.setdefault(word - reference.frame_size, "local unused")
    keys = sorted(set(candidate_rows) | set(reference_rows), reverse=True)
    if keys:
        lines.append(f"{'top-rel':>8} {'cand sp':>8}  {'candidate (.mdebug)':28} {'ref sp':>7}  reference")
    for key in keys:
        relative = f"{'+' if key >= 0 else '-'}{abs(key):#x}"
        candidate_sp = hex(candidate_frame + key) if key in candidate_rows else ""
        candidate_text = ", ".join(candidate_rows.get(key, [])) or "-"
        reference_sp = hex((reference.frame_size if reference else 0) + key) if key in reference_rows else ""
        reference_text = reference_rows.get(key, "-")
        lines.append(f"{relative:>8} {candidate_sp:>8}  {candidate_text:28} {reference_sp:>7}  {reference_text}")
    named = [entry for entry in locals_ if entry.kind == "local"]
    if named and candidate_frame:
        floor = min(candidate_frame + entry.frame_offset for entry in named)
        lines.append(f"lowest candidate local: {hex(floor)} ({len(named)} named homes;"
                     " outgoing args, saved registers and reserved spill words lie below)")
    if reference is not None:
        areas = reference.render(label="reference", indent="")[1:2]
        lines.extend(f"reference {line}" for line in areas)
        inference = reference.infer()
        if inference is not None:
            lines.extend(f"reference {line}" for line in frame_plan.render_inference(inference))
    elif reference_error:
        lines.append(f"reference frame-plan: unavailable ({reference_error})")
    return lines


@functools.lru_cache(maxsize=1)
def header_macros() -> frozenset[str]:
    """Function-like macros of the project and libultra headers."""

    names: set[str] = set()
    for directory in HEADER_DIRECTORIES:
        for header in sorted((ROOT / directory).rglob("*.h")):
            try:
                names |= frame_plan.function_like_macros(header.read_text(encoding="utf-8", errors="replace"))
            except OSError:
                continue
    return frozenset(names)


def function_body(content: str, target: Target) -> tuple[int, int] | None:
    """Offsets of the scored definition's ``{`` and matching ``}`` in ``content``."""

    for name in definition_names(content, target.symbol):
        try:
            start, end = project_state.c_function_span(content, name)
        except project_state.ProjectStateError:
            continue
        opening = content.index("{", content.index(name, start))
        return opening, project_state.matching_delimiter(content, opening, "{", "}")
    return None


def pad_alignment(target: Target, candidate: Path, content: str, body: tuple[int, int]) -> int | None:
    """Alignment words in the candidate's frame: 1 when one more named word still fits.

    Recompiles the probe source with an unused block-scoped ``int`` at the end of
    the body, which takes one word below every other named home. None when the
    probe compile or its frame cannot be read.
    """

    closing = body[1]
    source = candidate.with_name(f"{candidate.stem}-pad.c")
    output = source.with_suffix(".o")
    source.write_text(content[:closing] + f"    {{ int {PAD_LOCAL}; }}\n" + content[closing:], encoding="utf-8")
    output.unlink(missing_ok=True)
    try:
        result = compile_c.run_compile(target.profile, source, output, cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            return None
        before = frame_plan.object_frame_size(candidate, target.symbol) or 0
        after = frame_plan.object_frame_size(output, target.symbol) or 0
    except (OSError, frame_plan.FramePlanError):
        return None
    return {0: 1, 8: 0}.get(after - before)


def account_lines(target: Target, candidate: Path, locals_: list[Local],
                  reference: frame_plan.FramePlan) -> list[str]:
    """Word account of the candidate's local area against the reference's."""

    plan = frame_plan.object_plan(candidate, target.symbol)
    homes = [frame_plan.NamedHome(entry.name, plan.frame_size + entry.frame_offset, entry.size,
                                  entry.block, entry.aggregate)
             for entry in locals_ if entry.kind == "local"]
    source = candidate.with_suffix(".c")
    content = source.read_text(encoding="utf-8") if source.exists() else ""
    body = function_body(content, target) if content else None
    statements = []
    if body is not None:
        macros = header_macros() | frame_plan.function_like_macros(content)
        statements = frame_plan.call_argument_statements(content[body[0] + 1: body[1]], macros)
    account = frame_plan.account_local_area(plan, homes, statements, None)
    if account.materialized and body is not None:
        account.alignment = pad_alignment(target, candidate, content, body)
    lines = frame_plan.render_account(account, plan, reference, indent="  ")
    if body is None:
        lines.insert(1, "  (candidate source unavailable: call-arg temps not counted)")
    return lines


def print_layout(target: Target, candidate: Path) -> None:
    frame = object_frame_size(candidate, target.symbol)
    reference_frame = reference_frame_size(target.assembly, target.symbol)
    locals_ = mdebug_locals(candidate, target.symbol)
    reference = None
    reference_error = None
    try:
        reference = frame_plan.reference_plan(target.assembly, target.symbol, target.expected_size)
    except (frame_plan.FramePlanError, OSError, ValueError) as error:
        reference_error = str(error)
    for line in layout_lines(frame, reference_frame, locals_, reference, reference_error):
        print(line)
    if reference is not None and frame != reference_frame:
        try:
            lines = account_lines(target, candidate, locals_, reference)
        except (frame_plan.FramePlanError, OSError, ValueError) as error:
            lines = [f"local-area account: unavailable ({error})"]
        for line in lines:
            print(line)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("profile", choices=("us", "eu"))
    parser.add_argument("identifier")
    parser.add_argument("variants", nargs="*", type=Path,
                        help="function-definition or complete-source variant files")
    parser.add_argument("--layout", action="store_true",
                        help="print frame size and named-local stack offsets, plus a local-area "
                             "word account against the reference when the frames differ")
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
