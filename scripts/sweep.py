#!/usr/bin/env python3
"""Score one source transform across every deferred candidate in one warm process.

`sweep` is a read-only companion to `probe` for family-wide searches. Each
selected deferred candidate, with the transform applied, replaces its
`GLOBAL_ASM` pragma in a variant unit compiled with the pinned IDO flags, and
is scored with the same focused asm-differ comparison that `probe` uses. By
default every candidate gets its own unit, exactly as `probe <id> <variant>`
builds it, but one process serves the whole sweep: the pinned differ is loaded
once and the inventories are parsed once, which removes probe's per-function
start-up costs. `--batched` instead compiles one unit per source file.

Scores are search evidence only; `finish` remains the authoritative gate, and
nothing under `src/` or `progress/` is changed. Outputs go to `build/us/sweep/`.

Transforms:

* ``unchanged`` rescores each preserved candidate as written;
* ``literals`` replaces each ``extern f32 D_800[9A]xxxx`` game rodata symbol
  with the shortest float literal that round-trips to its ROM word;
* ``literals-inline`` additionally inlines ``f32`` locals that are assigned
  exactly once from a float literal (a named copy costs a ``-g3`` home).
"""

from __future__ import annotations

import argparse
import io
import json
import math
import os
import re
import struct
import subprocess
import sys
import tempfile
import time
from contextlib import contextmanager, nullcontext, redirect_stderr, redirect_stdout
from dataclasses import dataclass, field, replace
from decimal import Decimal
from pathlib import Path
from typing import Callable

import compile_c
import diff
import probe
import project_state

ROOT = diff.ROOT
PROFILE = "us"
OUTPUT_ROOT = ROOT / "build" / PROFILE / "sweep"
VARIANT_INDEX = 1  # probe.build_variant output name; each invocation has its own directory
TSV_HEADER = ("stored", "new", "frame", "ref_frame", "function", "source", "detail")

TAG = re.escape(project_state.DEFERRED_CANDIDATE_TAG)
CANDIDATE_START = re.compile(rf"(?m)^#if 0 /\* {TAG} (\S+)(?: CURRENT \((\d+)\))? \*/\n")
RODATA_F32_EXTERN = re.compile(r"(?m)^[ \t]*extern[ \t]+f32[ \t]+(D_800[9Aa][0-9A-Fa-f]{4})[ \t]*;[ \t]*\n?")
FLOAT_LITERAL = r"-?(?:\d+\.\d*|\.\d+)(?:[eE][-+]?\d+)?[fF]"


class SweepError(Exception):
    """The sweep could not start (bad filters or unavailable inputs)."""


class UnitError(Exception):
    """A shared variant unit did not compile."""

    def __init__(self, message: str, lines: dict[str, range]) -> None:
        super().__init__(message)
        self.message = message
        self.lines = lines


@dataclass(frozen=True)
class Block:
    """One preserved deferred candidate and the source span it occupies with its pragma."""

    identifier: str
    marker_score: int | None
    body: str
    start: int
    end: int


@dataclass
class Selected:
    block: Block
    stored: int | None
    body: str
    detail: str


@dataclass
class Row:
    stored: int | None
    new: int | None
    frame: str
    reference_frame: str
    function: str
    source: str
    detail: str

    def sort_key(self) -> tuple:
        if self.new is None:
            return (2, 0, 0, self.function)
        if self.new == 0:
            return (0, 0, 0, self.function)
        stored = self.stored if self.stored is not None else self.new
        return (1, self.new - stored, self.new, self.function)

    def cells(self) -> tuple[str, ...]:
        stored = "-" if self.stored is None else str(self.stored)
        new = "ERR" if self.new is None else str(self.new)
        detail = " ".join(self.detail.split()) or "-"
        return (stored, new, self.frame, self.reference_frame, self.function, self.source, detail)


def candidate_blocks(content: str, source_relative: str) -> tuple[list[Block], list[tuple[str, str]]]:
    """Preserved candidates in ``content`` and (identifier, problem) for malformed blocks."""

    blocks: list[Block] = []
    problems: list[tuple[str, str]] = []
    for start in CANDIDATE_START.finditer(content):
        identifier = start.group(1)
        end_marker = f"#endif /* {project_state.DEFERRED_CANDIDATE_TAG} {identifier} */"
        end = content.find(end_marker, start.end())
        if end < 0:
            problems.append((identifier, "unterminated deferred candidate"))
            continue
        block_end = end + len(end_marker)
        if content[block_end:block_end + 1] == "\n":
            block_end += 1
        pragma = project_state.global_asm_pragma(source_relative, identifier)
        if content[block_end:block_end + len(pragma)] != pragma:
            problems.append((identifier, "deferred candidate is not followed by its GLOBAL_ASM pragma"))
            continue
        block_end += len(pragma)
        if content[block_end:block_end + 1] == "\n":
            block_end += 1
        score = int(start.group(2)) if start.group(2) is not None else None
        body = content[start.end():end].rstrip("\n") + "\n"
        blocks.append(Block(identifier, score, body, start.start(), block_end))
    return blocks, problems


def variant_unit(content: str, replacements: list[tuple[Block, str]]) -> tuple[str, dict[str, range]]:
    """Activate each block with its replacement body; blank every remaining GLOBAL_ASM line.

    Also returns the 1-based line range each activated body occupies, so a
    compiler error can be attributed to the candidate that contains it.
    """

    pieces: list[str] = []
    lines: dict[str, range] = {}
    position, line = 0, 1
    for block, body in sorted(replacements, key=lambda item: item[0].start):
        text = body if body.endswith("\n") else body + "\n"
        before = content[position:block.start]
        line += before.count("\n")
        lines[block.identifier] = range(line, line + text.count("\n"))
        line += text.count("\n")
        pieces += [before, text]
        position = block.end
    pieces.append(content[position:])
    # The pattern stops before the newline, so line numbers are unchanged.
    return diff.GLOBAL_ASM_LINE.sub("", "".join(pieces)), lines


ERROR_LINE = re.compile(r"\bline (\d+)\b")


def blamed_candidates(message: str, lines: dict[str, range]) -> set[str]:
    """Candidates whose activated bodies contain a line the compiler reported."""

    reported = {int(number) for number in ERROR_LINE.findall(message)}
    return {identifier for identifier, span in lines.items() if any(line in span for line in reported)}


# --- transforms -------------------------------------------------------------


@dataclass
class FileContext:
    """Per-source facts a transform may use."""

    content: str
    rom_word: Callable[[int], bytes | None] = lambda address: None
    rodata_f32: set[str] = field(default_factory=set)

    def __post_init__(self) -> None:
        self.rodata_f32 = set(RODATA_F32_EXTERN.findall(self.content))


def shortest_f32_literal(word: bytes) -> str | None:
    """The shortest C float literal whose f32 rounding is exactly ``word``."""

    value = struct.unpack(">f", word)[0]
    if not math.isfinite(value):
        return None
    for precision in range(1, 10):
        text = "%.*g" % (precision, value)
        try:
            if struct.pack(">f", float(text)) == word:
                break
        except OverflowError:  # a short spelling of FLT_MAX rounds above it
            continue
    else:  # nine significant digits always round-trip an f32
        return None
    if -7 <= Decimal(text).adjusted() < 16:
        text = format(Decimal(text), "f")  # 1e+04 -> 10000, 1e-05 -> 0.00001
    mantissa, _, exponent = text.partition("e")
    if "." not in mantissa:
        mantissa += ".0"
    return mantissa + (f"e{exponent}" if exponent else "") + "f"


def substitute(text: str, name: str, literal: str) -> str:
    """Replace whole-identifier uses of ``name`` (not member names) with ``literal``."""

    pattern = re.compile(rf"(?<!\.)(?<!->)\b{re.escape(name)}\b")

    def replace(match: re.Match[str]) -> str:
        before = text[match.start() - 1] if match.start() else ""
        # `-D_x` must not become the decrement token `--1.0f`.
        return f"({literal})" if literal.startswith("-") and before == "-" else literal

    return pattern.sub(replace, text)


def transform_unchanged(body: str, context: FileContext) -> tuple[str, str] | None:
    return body, ""


def transform_literals(body: str, context: FileContext) -> tuple[str, str] | None:
    names = set(context.rodata_f32)
    names.update(RODATA_F32_EXTERN.findall(body))
    used = sorted(name for name in names if re.search(rf"\b{name}\b", _without_externs(body, name)))
    if not used:
        return None
    result = body
    replaced: list[str] = []
    skipped: list[str] = []
    for name in used:
        if re.search(rf"&\s*{name}\b", result):
            skipped.append(f"{name}:address-taken")
            continue
        word = context.rom_word(int(name[2:], 16))
        literal = shortest_f32_literal(word) if word is not None else None
        if literal is None:
            skipped.append(f"{name}:no-literal")
            continue
        result = _without_externs(result, name)
        result = substitute(result, name, literal)
        replaced.append(f"{name}={literal}")
    if not replaced:
        return None
    return result, " ".join(replaced + skipped)


def _without_externs(body: str, name: str) -> str:
    return re.sub(rf"(?m)^[ \t]*extern[ \t]+f32[ \t]+{name}[ \t]*;[ \t]*\n?", "", body)


F32_DECLARATION = re.compile(
    rf"(?m)^([ \t]*)(?:register[ \t]+)?f32[ \t]+(\w+)(?:[ \t]*=[ \t]*({FLOAT_LITERAL}))?[ \t]*;[ \t]*\n"
)


def brace_pairs(text: str) -> list[tuple[int, int]]:
    """Matching ``{``/``}`` offsets in C text, ignoring comments and literals."""

    pairs: list[tuple[int, int]] = []
    stack: list[int] = []
    index, state = 0, "code"
    while index < len(text):
        char, following = text[index], text[index + 1:index + 2]
        if state == "code":
            if char == "/" and following in ("*", "/"):
                state = "block_comment" if following == "*" else "line_comment"
                index += 2
                continue
            if char in "\"'":
                state = char
            elif char == "{":
                stack.append(index)
            elif char == "}" and stack:
                pairs.append((stack.pop(), index))
        elif state == "block_comment" and char == "*" and following == "/":
            state = "code"
            index += 2
            continue
        elif state == "line_comment" and char == "\n":
            state = "code"
        elif state in "\"'":
            if char == "\\":
                index += 2
                continue
            if char == state:
                state = "code"
        index += 1
    return pairs


def redeclares(scope: str, name: str) -> bool:
    """Whether ``scope`` declares ``name`` again (a nested block would shadow the local)."""

    return re.search(
        rf"(?m)^[ \t]*(?!(?:return|else|case|goto)\b)(?:(?:register|static|const|volatile)[ \t]+)*"
        rf"[A-Za-z_]\w*[ \t*]+{name}[ \t]*[;=,\[]", scope) is not None


def inline_literal_locals(body: str) -> tuple[str, list[str]]:
    """Inline f32 locals whose only write is one float-literal initialization or assignment.

    Every check and substitution stays inside the block that declares the local,
    so a same-named outer variable is untouched; a block that redeclares the
    name is skipped. A plain declaration's single assignment must sit at the
    declaration's block level and precede every other use.
    """

    inlined: list[str] = []
    for name in dict.fromkeys(match.group(2) for match in F32_DECLARATION.finditer(body)):
        declaration = next((match for match in F32_DECLARATION.finditer(body) if match.group(2) == name), None)
        if declaration is None:
            continue
        blocks = [pair for pair in brace_pairs(body)
                  if pair[0] < declaration.start() and declaration.end() <= pair[1]]
        if not blocks:
            continue
        opening, closing = max(blocks)  # the innermost enclosing block
        indent, literal = declaration.group(1), declaration.group(3)
        trial = body[opening + 1:declaration.start()] + body[declaration.end():closing]
        if redeclares(trial, name):
            continue
        if literal is None:
            assignment = re.compile(rf"(?m)^([ \t]*){name}[ \t]*=[ \t]*({FLOAT_LITERAL})[ \t]*;[ \t]*\n")
            assignments = list(assignment.finditer(trial))
            if len(assignments) != 1 or assignments[0].group(1) != indent:
                continue
            first_use = re.search(rf"(?<!\.)(?<!->)\b{name}\b", trial)
            if first_use is None or first_use.start() < assignments[0].start():
                continue
            literal = assignments[0].group(2)
            trial = trial[:assignments[0].start()] + trial[assignments[0].end():]
        writes = rf"(?<!\.)(?<!->)\b{name}\s*(?:[-+*/%&|^]?=(?!=)|<<=|>>=|\+\+|--)|(?:\+\+|--)\s*{name}\b|&\s*{name}\b"
        if re.search(writes, trial):
            continue
        if not re.search(rf"(?<!\.)(?<!->)\b{name}\b", trial):
            continue
        body = body[:opening + 1] + substitute(trial, name, literal) + body[closing:]
        inlined.append(f"{name}={literal}")
    return body, inlined


def transform_literals_inline(body: str, context: FileContext) -> tuple[str, str] | None:
    literal_result = transform_literals(body, context)
    text, detail = literal_result if literal_result is not None else (body, "")
    text, inlined = inline_literal_locals(text)
    if not inlined:
        return None
    return text, " ".join(filter(None, [detail, "inline " + ",".join(inlined)]))


TRANSFORMS: dict[str, Callable[[str, FileContext], tuple[str, str] | None]] = {
    "unchanged": transform_unchanged,
    "literals": transform_literals,
    "literals-inline": transform_literals_inline,
}
NEEDS_ROM = {"literals", "literals-inline"}


def rom_word_reader() -> Callable[[int], bytes | None]:
    import verify_game_rodata

    try:
        data, base = verify_game_rodata.rom_game_data()
    except (OSError, ValueError, KeyError) as error:
        raise SweepError(f"the literal transforms need the checksum-validated US ROM: {error}") from error

    def word(address: int) -> bytes | None:
        offset = address - base
        if offset < 0 or offset + 4 > len(data) or address % 4:
            return None
        return data[offset:offset + 4]

    return word


# --- selection --------------------------------------------------------------


def deferred_inventory() -> dict[str, dict]:
    inventory = json.loads((ROOT / "progress" / "functions.json").read_text(encoding="utf-8"))
    return {entry["symbol"]: entry for entry in inventory["functions"]
            if isinstance(entry.get("deferred"), dict) and PROFILE in entry.get("regions", {})
            and isinstance(entry.get("source"), str)}


def source_selected(source: str, filters: list[str]) -> bool:
    if not filters:
        return True
    for selected in filters:
        selected = selected.rstrip("/")
        if source == selected or source.startswith(selected + "/"):
            return True
    return False


def normalize_source_filter(value: str) -> str:
    path = Path(value)
    if path.is_absolute():
        try:
            path = path.resolve().relative_to(ROOT)
        except ValueError as error:
            raise SweepError(f"--source must be inside the repository: {value}") from error
    return path.as_posix().removeprefix("./")


# --- scoring ----------------------------------------------------------------


@contextmanager
def parse_inventories_once():
    """Reuse each large JSON parse (the inventories) for the rest of the sweep.

    `probe.resolve` reparses progress/functions.json about five times per
    function. The sweep never writes inventories and its helpers only read
    the parsed data, so identical text can share one parse.
    """

    original = json.loads
    parsed: dict[str, object] = {}

    def loads(text, *args, **kwargs):
        if args or kwargs or not isinstance(text, str) or len(text) < 1 << 16:
            return original(text, *args, **kwargs)
        if text not in parsed:
            parsed[text] = original(text)
        return parsed[text]

    json.loads = loads
    try:
        yield
    finally:
        json.loads = original


def frame_text(value: int | None) -> str:
    return hex(value) if value is not None else "leaf"


def first_line(error: BaseException) -> str:
    text = str(error).strip().replace(f"{ROOT}/", "")
    return text.splitlines()[0] if text else type(error).__name__


class InProcessScorer:
    """One pinned asm-differ instance serving every score in this process.

    `probe.score` starts a Python process per score; this runs the same
    registered-span differ with the same arguments and reads the same JSON.
    """

    def __init__(self, directory: Path) -> None:
        settings = diff.write_settings(PROFILE, ROOT / "src", directory=directory)
        self.differ = diff.load_pinned_asm_differ()
        previous = os.getcwd()
        os.chdir(settings)
        try:
            self.differ.main_early()
        finally:
            os.chdir(previous)

    def __call__(self, target: probe.Target, candidate: Path) -> int:
        command = diff.asm_diff_command(candidate, target.reference, target.symbol,
                                        target.expected_size, require_match=True)
        arguments = command[command.index("--asm-differ") + 1:]
        output, errors = io.StringIO(), io.StringIO()
        saved = sys.argv
        sys.argv = [str(diff.ASM_DIFFER), *arguments]
        try:
            with redirect_stdout(output), redirect_stderr(errors):
                self.differ.main_late()
        except SystemExit as error:
            if error.code not in (None, 0):
                raise probe.ToolingError(errors.getvalue().strip() or output.getvalue().strip()
                                         or "asm-differ failed") from error
        except (OSError, ValueError, subprocess.CalledProcessError) as error:
            raise probe.ToolingError(f"asm-differ failed: {error}") from error
        finally:
            sys.argv = saved
        try:
            return diff.current_difference_count(output.getvalue())
        except ValueError as error:
            raise probe.ToolingError(f"asm-differ returned an invalid score: {error}") from error


MODES = ("exact", "batched", "probe")


class Sweep:
    """Score selected candidates in one process.

    ``exact`` builds each candidate in its own unit, exactly as probe does
    (other candidates stay inactive), and scores it with the in-process differ.
    ``batched`` compiles one unit per source with every selected candidate
    active. IDO's allocation can differ in such a unit (other active functions
    shift its tie-breaks), so every batched zero or improvement is re-scored
    exactly before it is reported. ``probe`` repeats probe's own per-function
    costs (a differ process per score) as a timing and agreement baseline.
    """

    def __init__(self, transform: str, *, mode: str = "exact", log=sys.stderr) -> None:
        if mode not in MODES:
            raise ValueError(f"unknown sweep mode: {mode}")
        self.transform = transform
        self.mode = mode
        self.log = log
        self.directory = OUTPUT_ROOT / transform
        self.compiles = 0
        self.confirmations = 0
        # Builds, objects and differ settings stay private to this invocation, so
        # overlapping sweeps (or probes) never overwrite each other's objects.
        runs = OUTPUT_ROOT / "runs"
        runs.mkdir(parents=True, exist_ok=True)
        self.run = tempfile.TemporaryDirectory(prefix=f"{transform}-", dir=runs)
        self.work = Path(self.run.name)
        try:
            self.scorer = probe.score if mode == "probe" else InProcessScorer(self.work / "differ")
        except BaseException:
            self.close()
            raise

    def close(self) -> None:
        self.run.cleanup()

    def target(self, identifier: str) -> probe.Target:
        target = probe.resolve(identifier, PROFILE)
        directory = self.work / "probe" / target.symbol
        directory.mkdir(parents=True, exist_ok=True)
        return replace(target, directory=directory)

    def score_object(self, target: probe.Target, candidate: Path, disassembly: str) -> tuple[int, str]:
        value = self.scorer(target, candidate)
        frame = probe.disassembly_frame_size(disassembly, target.symbol, candidate)
        return value, frame_text(frame)

    def reference_frame(self, target: probe.Target) -> str:
        return frame_text(probe.reference_frame_size(target.assembly, target.symbol))

    def compile_unit(self, source_relative: str, content: str,
                     selected: list[Selected]) -> tuple[Path, dict[str, range]]:
        unit, lines = variant_unit(content, [(item.block, item.body) for item in selected])
        source = self.work / "units" / source_relative
        output = source.with_suffix(".o")
        source.parent.mkdir(parents=True, exist_ok=True)
        source.write_text(unit, encoding="utf-8")
        output.unlink(missing_ok=True)
        self.compiles += 1
        try:
            result = compile_c.run_compile(PROFILE, source, output, cwd=ROOT, capture_output=True, text=True)
        except OSError as error:
            raise probe.ToolingError(f"could not run the compiler: {error}") from error
        if result.returncode:
            raise UnitError("\n".join(result.stdout.splitlines() + result.stderr.splitlines()), lines)
        return output, lines

    def score_file(self, source_relative: str, content: str, selected: list[Selected]) -> list[Row]:
        if self.mode != "batched":
            return [self.score_isolated(item, source_relative) for item in selected]
        return self.score_batched(source_relative, content, selected)

    def score_batched(self, source_relative: str, content: str, selected: list[Selected]) -> list[Row]:
        """One shared unit for every candidate the compiler accepts.

        A failing unit is retried without the candidates whose bodies contain a
        reported error line; those, or every candidate when an error cannot be
        attributed, are built on their own.
        """

        rows: list[Row] = []
        isolated: list[Selected] = []
        batch = list(selected)
        while batch:
            try:
                candidate, _ = self.compile_unit(source_relative, content, batch)
                disassembly = probe.object_disassembly(candidate)
            except UnitError as error:
                blamed = blamed_candidates(error.message, error.lines)
                summary = next((line.strip() for line in error.message.splitlines() if "rror" in line),
                               "compile failed")
                if not blamed:
                    print(f"  {source_relative}: unit does not compile ({summary}); "
                          "building its candidates one at a time", file=self.log)
                    isolated += batch
                    break
                print(f"  {source_relative}: isolating {', '.join(sorted(blamed))} ({summary})",
                      file=self.log)
                isolated += [item for item in batch if item.block.identifier in blamed]
                batch = [item for item in batch if item.block.identifier not in blamed]
                continue
            for item in batch:
                row = self.score_shared(item, source_relative, candidate, disassembly)
                if row.new is not None and (row.new == 0 or (item.stored is not None and row.new < item.stored)):
                    self.confirmations += 1
                    exact = self.score_isolated(item, source_relative)
                    note = "[confirmed]" if exact.new == row.new else f"[batched {row.new}]"
                    row = replace(exact, detail=" ".join(filter(None, [exact.detail, note])))
                else:
                    row.detail = " ".join(filter(None, [row.detail, "[batched]"]))
                rows.append(row)
            break
        rows += [self.score_isolated(item, source_relative) for item in isolated]
        return rows

    def row(self, item: Selected, source_relative: str, new: int | None, frame: str,
            reference_frame: str, detail: str = "") -> Row:
        return Row(item.stored, new, frame, reference_frame, item.block.identifier, source_relative,
                   " ".join(filter(None, [item.detail, detail])))

    def score_shared(self, item: Selected, source_relative: str, candidate: Path, disassembly: str) -> Row:
        try:
            target = self.target(item.block.identifier)
            value, frame = self.score_object(target, candidate, disassembly)
            return self.row(item, source_relative, value, frame, self.reference_frame(target))
        except (probe.ProbeError, ValueError, OSError, subprocess.CalledProcessError) as error:
            return self.row(item, source_relative, None, "-", "-", f"[error: {first_line(error)}]")

    def score_isolated(self, item: Selected, source_relative: str) -> Row:
        """Build and score one candidate exactly as `probe <id> <variant>` would."""

        try:
            target = self.target(item.block.identifier)
            variant = self.work / "variants" / f"{item.block.identifier}.c"
            variant.parent.mkdir(parents=True, exist_ok=True)
            variant.write_text(item.body, encoding="utf-8")
            # Keep the transformed body for copying into source after the run.
            write_atomically(self.directory / "variants" / variant.name, item.body)
            self.compiles += 1
            candidate = probe.build_variant(target, variant, VARIANT_INDEX)
            value, frame = self.score_object(target, candidate, probe.object_disassembly(candidate))
            return self.row(item, source_relative, value, frame, self.reference_frame(target))
        except probe.VariantError as error:
            return self.row(item, source_relative, None, "-", "-", f"[compile: {first_line(error)}]")
        except (probe.ProbeError, ValueError, OSError, subprocess.CalledProcessError) as error:
            return self.row(item, source_relative, None, "-", "-", f"[error: {first_line(error)}]")


def select_candidates(transform: str, *, max_score: int | None, sources: list[str],
                      functions: list[str], reason: str | None,
                      rom_word: Callable[[int], bytes | None] | None = None,
                      ) -> tuple[dict[str, tuple[str, list[Selected]]], list[Row]]:
    """Group selected candidates by source: {source: (content, [Selected])}, plus malformed rows."""

    inventory = deferred_inventory()
    apply = TRANSFORMS[transform]
    reason_pattern = re.compile(reason, re.IGNORECASE) if reason else None
    wanted = set(functions)
    unknown = wanted - inventory.keys()
    if unknown:
        raise SweepError("not deferred work items: " + ", ".join(sorted(unknown)))
    grouped: dict[str, tuple[str, list[Selected]]] = {}
    problems: list[Row] = []
    by_source: dict[str, list[dict]] = {}
    for entry in inventory.values():
        by_source.setdefault(entry["source"], []).append(entry)
    for source_relative in sorted(by_source):
        if not source_selected(source_relative, sources):
            continue
        path = ROOT / source_relative
        if not path.is_file():
            continue
        content = path.read_text(encoding="utf-8")
        blocks, malformed = candidate_blocks(content, source_relative)
        context = FileContext(content, rom_word or (lambda address: None))
        for identifier, problem in malformed:
            if identifier in inventory and (not wanted or identifier in wanted):
                problems.append(Row(None, None, "-", "-", identifier, source_relative, f"[error: {problem}]"))
        selected: list[Selected] = []
        for block in blocks:
            entry = inventory.get(block.identifier)
            if entry is None or entry["source"] != source_relative:
                continue
            if wanted and block.identifier not in wanted:
                continue
            recorded = entry["deferred"].get("current_score")
            stored = recorded if isinstance(recorded, int) else block.marker_score
            if max_score is not None and (stored is None or stored > max_score):
                continue
            if reason_pattern and not reason_pattern.search(str(entry["deferred"].get("reason", ""))):
                continue
            result = apply(block.body, context)
            if result is None:
                continue
            body, detail = result
            selected.append(Selected(block, stored, body, detail))
        if selected:
            grouped[source_relative] = (content, selected)
    return grouped, problems


def write_atomically(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    handle, temporary = tempfile.mkstemp(prefix=f".{path.name}.", dir=path.parent)
    try:
        with os.fdopen(handle, "w", encoding="utf-8") as stream:
            stream.write(text)
        os.replace(temporary, path)
    except BaseException:
        Path(temporary).unlink(missing_ok=True)
        raise


def write_tsv(rows: list[Row], stream) -> None:
    stream.write("\t".join(TSV_HEADER) + "\n")
    for row in sorted(rows, key=Row.sort_key):
        stream.write("\t".join(row.cells()) + "\n")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("transform", choices=sorted(TRANSFORMS))
    parser.add_argument("--max-score", type=int, help="only candidates whose stored score is at most N")
    parser.add_argument("--source", action="append", default=[], metavar="PATH",
                        help="only this source file or directory (repeatable)")
    parser.add_argument("--function", action="append", default=[], metavar="ID",
                        help="only this deferred work item (repeatable)")
    parser.add_argument("--reason", metavar="REGEX", help="only candidates whose deferral reason matches")
    parser.add_argument("--batched", dest="mode", action="store_const", const="batched", default="exact",
                        help="one compile per source; zeros and improvements are re-scored exactly")
    parser.add_argument("--probe-baseline", dest="mode", action="store_const", const="probe",
                        help="spend probe's per-function costs (a differ process per score) for comparison")
    parser.add_argument("--output", type=Path, help="TSV path (default build/us/sweep/<transform>.tsv)")
    arguments = parser.parse_args(argv)
    started = time.monotonic()
    try:
        sources = [normalize_source_filter(value) for value in arguments.source]
        rom_word = rom_word_reader() if arguments.transform in NEEDS_ROM else None
        grouped, rows = select_candidates(
            arguments.transform, max_score=arguments.max_score, sources=sources,
            functions=arguments.function, reason=arguments.reason, rom_word=rom_word,
        )
    except (SweepError, re.error, OSError, ValueError) as error:
        print(f"error: {error}", file=sys.stderr)
        return diff.EXIT_BLOCKED_TOOLING
    total = sum(len(selected) for _, selected in grouped.values())
    print(f"sweep {arguments.transform}: {total} candidates in {len(grouped)} sources ({arguments.mode})",
          file=sys.stderr)
    try:
        sweep = Sweep(arguments.transform, mode=arguments.mode)
    except (ValueError, OSError, probe.ProbeError) as error:
        print(f"error: could not start the scorer: {error}", file=sys.stderr)
        return diff.EXIT_BLOCKED_TOOLING
    # The probe baseline keeps probe's own per-function inventory parsing.
    try:
        with nullcontext() if arguments.mode == "probe" else parse_inventories_once():
            for index, (source_relative, (content, selected)) in enumerate(grouped.items(), start=1):
                file_started = time.monotonic()
                file_rows = sweep.score_file(source_relative, content, selected)
                rows.extend(file_rows)
                zeros = sum(row.new == 0 for row in file_rows)
                print(f"[{index}/{len(grouped)}] {source_relative}: {len(selected)} scored, {zeros} zero, "
                      f"{time.monotonic() - file_started:.1f}s", file=sys.stderr, flush=True)
    finally:
        sweep.close()
    output = arguments.output or OUTPUT_ROOT / f"{arguments.transform}.tsv"
    table = io.StringIO()
    write_tsv(rows, table)
    write_atomically(output, table.getvalue())
    sys.stdout.write(table.getvalue())
    errors = sum(row.new is None for row in rows)
    zeros = sum(row.new == 0 for row in rows)
    elapsed = time.monotonic() - started
    print(f"sweep {arguments.transform}: {len(rows)} rows, {zeros} zero, {errors} errors, "
          f"{sweep.compiles} compiles, {sweep.confirmations} batched confirmations, {elapsed:.1f}s; "
          f"wrote {output.relative_to(ROOT) if output.is_relative_to(ROOT) else output}", file=sys.stderr)
    if zeros:
        print("note: a sweep zero is not a match; apply the body and run ./conker finish", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
