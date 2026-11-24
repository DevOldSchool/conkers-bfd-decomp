#!/usr/bin/env python3
"""Readable evidence for a probe variant: where it differs and what else it changed.

`probe` scores a variant; these helpers explain the score without leaving the
read-only probe workflow:

* an instruction diff of the target function against the reference object,
  with branch targets as position-independent labels and relocations folded
  into the instruction, so an inserted instruction does not turn every later
  line into noise, plus a one-line classification of the residual;
* a comparison of every other function and of the data sections against an
  object built from the current source, which shows whether a struct,
  prototype or literal edit in a complete-source variant changed anything
  besides the target.

Everything here is search evidence only; `finish` remains the authoritative gate.
"""

from __future__ import annotations

import difflib
import re
import struct
from dataclasses import dataclass, field

FUNCTION_HEADER = re.compile(r"^([0-9a-f]+) <([^>]+)>:\s*$")
INSTRUCTION = re.compile(r"^\s*([0-9a-f]+):\t(\S+)(?:\s+(.*\S))?\s*$")
RELOCATION = re.compile(r"^\s*([0-9a-f]+):\s+(R_MIPS_\w+)\s+(\S+)\s*$")
BRANCH_TARGET = re.compile(r"\b([0-9a-f]+) <[^>]+>")
REGISTER = re.compile(
    r"\b(?:zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d{1,2})\b")
RELOCATION_NAMES = {"R_MIPS_HI16": "%hi", "R_MIPS_LO16": "%lo", "R_MIPS_26": "%call", "R_MIPS_32": "%word"}
DATA_SECTIONS = (".rodata", ".data", ".bss")


@dataclass
class Instruction:
    offset: int  # relative to the function start
    mnemonic: str
    operands: str
    relocations: list[tuple[str, str]] = field(default_factory=list)


def function_listings(disassembly: str) -> dict[str, list[Instruction]]:
    """Instructions of every function in ``objdump -d -r --no-show-raw-insn`` text."""

    listings: dict[str, list[Instruction]] = {}
    current: list[Instruction] | None = None
    start = 0
    for line in disassembly.splitlines():
        header = FUNCTION_HEADER.match(line)
        if header:
            start = int(header.group(1), 16)
            current = listings.setdefault(header.group(2), [])
            continue
        if current is None:
            continue
        relocation = RELOCATION.match(line)
        if relocation:
            if current:
                current[-1].relocations.append((relocation.group(2), relocation.group(3)))
            continue
        instruction = INSTRUCTION.match(line)
        if instruction:
            current.append(Instruction(int(instruction.group(1), 16) - start,
                                       instruction.group(2), instruction.group(3) or ""))
        elif line.startswith("Disassembly of section"):
            current = None
    return listings


def render(instructions: list[Instruction]) -> list[str]:
    """One comparable text line per instruction.

    Branch targets inside the function become ``.L<n>`` labels numbered in
    address order, and each relocation replaces the meaningless link-time
    operand it patches, so equal code at different offsets renders equally.
    """

    # objdump prints branch targets as section addresses; only their order matters here.
    targets = sorted({int(match.group(1), 16) for instruction in instructions
                      if not instruction.relocations
                      for match in BRANCH_TARGET.finditer(instruction.operands)})
    labels = {target: f".L{number}" for number, target in enumerate(targets, start=1)}
    lines: list[str] = []
    for instruction in instructions:
        operands = instruction.operands
        if instruction.relocations:
            notes = [f"{RELOCATION_NAMES.get(kind, kind)}({symbol})"
                     for kind, symbol in instruction.relocations]
            if any(kind == "R_MIPS_26" for kind, _ in instruction.relocations):
                operands = notes[0]  # the printed call target is a link-time placeholder
            else:
                operands = f"{operands} {' '.join(notes)}"
        else:
            operands = BRANCH_TARGET.sub(lambda match: labels[int(match.group(1), 16)], operands)
        lines.append(f"{instruction.mnemonic}\t{operands}".rstrip())
    return lines


def label_lines(instructions: list[Instruction], function_address: int = 0) -> dict[int, str]:
    """Offsets inside the function that a branch targets, with their label names."""

    targets: set[int] = set()
    for instruction in instructions:
        if instruction.relocations:
            continue
        for match in BRANCH_TARGET.finditer(instruction.operands):
            targets.add(int(match.group(1), 16) - function_address)
    return {target: f".L{number}" for number, target in enumerate(sorted(targets), start=1)}


def _shape(line: str) -> str:
    return REGISTER.sub("R", line)


def _without_symbols(line: str) -> str:
    return re.sub(r"%\w+\([^)]*\)", "%sym", line)


def classify(reference: list[str], candidate: list[str]) -> dict[str, int]:
    """Count differing lines by kind: register-only, relocation-only, inserted, deleted, other."""

    counts = {"register-only": 0, "relocation-only": 0, "other": 0, "inserted": 0, "deleted": 0}
    matcher = difflib.SequenceMatcher(None, reference, candidate, autojunk=False)
    for tag, i1, i2, j1, j2 in matcher.get_opcodes():
        if tag == "equal":
            continue
        paired = min(i2 - i1, j2 - j1)
        for index in range(paired):
            old, new = reference[i1 + index], candidate[j1 + index]
            if _shape(old) == _shape(new):
                counts["register-only"] += 1
            elif _without_symbols(old) == _without_symbols(new):
                counts["relocation-only"] += 1
            else:
                counts["other"] += 1
        counts["deleted"] += (i2 - i1) - paired
        counts["inserted"] += (j2 - j1) - paired
    return counts


def register_map(reference: list[str], candidate: list[str]) -> list[tuple[str, str, int]]:
    """(reference register, candidate register, uses) for register-only line pairs, most used first.

    A consistent rotation (``v0 -> v1``, ``v1 -> a0``) usually means one
    allocation decision; scattered pairs mean several.
    """

    pairs: dict[tuple[str, str], int] = {}
    matcher = difflib.SequenceMatcher(None, reference, candidate, autojunk=False)
    for tag, i1, i2, j1, j2 in matcher.get_opcodes():
        if tag != "replace":
            continue
        for index in range(min(i2 - i1, j2 - j1)):
            old, new = reference[i1 + index], candidate[j1 + index]
            if _shape(old) != _shape(new):
                continue
            for before, after in zip(REGISTER.findall(old), REGISTER.findall(new)):
                if before != after:
                    pairs[(before, after)] = pairs.get((before, after), 0) + 1
    return [(before, after, count) for (before, after), count in
            sorted(pairs.items(), key=lambda item: (-item[1], item[0]))]


def register_summary(mapping: list[tuple[str, str, int]], limit: int = 8) -> str:
    if not mapping:
        return ""
    shown = ", ".join(f"{before}->{after} x{count}" for before, after, count in mapping[:limit])
    more = f", +{len(mapping) - limit} more" if len(mapping) > limit else ""
    return f"register map (reference->candidate): {shown}{more}"


def trim_padding(instructions: list[Instruction]) -> list[Instruction]:
    """Drop the alignment nops that follow a function's final delay slot."""

    end = len(instructions)
    while end > 0 and instructions[end - 1].mnemonic == "nop" and not instructions[end - 1].relocations:
        end -= 1
    # A nop directly after the last jump or branch is its delay slot, not padding.
    if 0 < end < len(instructions) and instructions[end - 1].mnemonic[0] in "jb":
        end += 1
    return instructions[:end]


def summary(counts: dict[str, int]) -> str:
    total = sum(counts.values())
    if not total:
        return "instruction diff: identical"
    parts = [f"{value} {name}" for name, value in counts.items() if value]
    return f"instruction diff: {total} lines differ ({', '.join(parts)})"


def diff_lines(reference: list[Instruction], candidate: list[Instruction], *, context: int = 2,
               reference_address: int = 0, candidate_address: int = 0) -> list[str]:
    """Unified diff of two listings: ``-`` reference, ``+`` candidate, with function offsets."""

    old, new = render(reference), render(candidate)
    old_labels = label_lines(reference, reference_address)
    new_labels = label_lines(candidate, candidate_address)

    def shown(prefix: str, instructions: list[Instruction], lines: list[str], labels: dict[int, str],
              index: int) -> str:
        offset = instructions[index].offset
        label = labels.get(offset, "")
        return f"{prefix} {offset:4x}: {label + ':' if label else '':6}{lines[index]}"

    output: list[str] = []
    matcher = difflib.SequenceMatcher(None, old, new, autojunk=False)
    for group in matcher.get_grouped_opcodes(context):
        first = group[0]
        output.append(f"@@ reference +0x{reference[first[1]].offset:x}, candidate "
                      f"+0x{candidate[first[3]].offset if first[3] < len(candidate) else 0:x} @@")
        for tag, i1, i2, j1, j2 in group:
            if tag == "equal":
                output += [shown(" ", candidate, new, new_labels, index) for index in range(j1, j2)]
                continue
            output += [shown("-", reference, old, old_labels, index) for index in range(i1, i2)]
            output += [shown("+", candidate, new, new_labels, index) for index in range(j1, j2)]
    return output


def function_addresses(disassembly: str) -> dict[str, int]:
    return {match.group(2): int(match.group(1), 16)
            for match in map(FUNCTION_HEADER.match, disassembly.splitlines()) if match}


def compare_functions(base: dict[str, list[Instruction]], candidate: dict[str, list[Instruction]],
                      skip: set[str]) -> tuple[int, list[str]]:
    """(identical count, problems) for every function other than ``skip``.

    Listings are compared after rendering, so a function that only moved to a
    different address counts as identical.
    """

    identical = 0
    problems: list[str] = []
    for name in base:
        if name in skip:
            continue
        if name not in candidate:
            problems.append(f"{name}: missing from the variant object")
        elif render(base[name]) == render(candidate[name]):
            identical += 1
        else:
            counts = classify(render(base[name]), render(candidate[name]))
            problems.append(f"{name}: CHANGED ({summary(counts).removeprefix('instruction diff: ')})")
    problems += [f"{name}: only in the variant object" for name in candidate
                 if name not in base and name not in skip]
    return identical, problems


def words(data: bytes, limit: int = 16) -> str:
    shown = " ".join(data[index:index + 4].hex() for index in range(0, min(len(data), limit * 4), 4))
    return shown + (" ..." if len(data) > limit * 4 else "")


def data_sections(data: bytes) -> dict[str, bytes]:
    """Bytes of the data sections of a 32-bit big-endian ELF object (``.bss`` as zeros)."""

    if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 2:
        raise ValueError("expected a 32-bit big-endian ELF object")
    offset = struct.unpack_from(">I", data, 0x20)[0]
    entry_size, count, names_index = struct.unpack_from(">HHH", data, 0x2E)
    headers = [struct.unpack_from(">10I", data, offset + index * entry_size) for index in range(count)]
    names = headers[names_index][4]
    sections: dict[str, bytes] = {}
    for header in headers:
        start = names + header[0]
        name = data[start:data.index(b"\0", start)].decode()
        if name in DATA_SECTIONS:
            sections[name] = bytes(header[5]) if header[1] == 8 else data[header[4]:header[4] + header[5]]
    return sections


def payload(data: bytes) -> bytes:
    """``data`` without its trailing zero words (object alignment padding)."""

    end = len(data.rstrip(b"\0"))
    return data[:(end + 3) & ~3]


def compare_sections(base: dict[str, bytes], candidate: dict[str, bytes]) -> list[str]:
    """One line per data section whose size or bytes differ from the current-source object."""

    lines: list[str] = []
    for name in DATA_SECTIONS:
        old, new = base.get(name, b""), candidate.get(name, b"")
        if old == new:
            continue
        if name == ".bss":
            lines.append(f"{name}: size 0x{len(old):x} -> 0x{len(new):x}")
            continue
        detail = f"{name}: size 0x{len(old):x} -> 0x{len(new):x}"
        old_payload, new_payload = payload(old), payload(new)
        if new_payload[:len(old_payload)] == old_payload:
            added = new_payload[len(old_payload):]
            detail += f"; appended words: {words(added) or '(zero padding only)'}"
        else:
            detail += f"; variant words: {words(new)}"
        lines.append(detail)
    return lines
