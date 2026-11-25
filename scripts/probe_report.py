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
# `zero` is not listed: it is never an allocation, so a line that differs in it is not register-only.
REGISTER = re.compile(r"\b(?:at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d{1,2})\b")
RELOCATION_NAMES = {"R_MIPS_HI16": "%hi", "R_MIPS_LO16": "%lo", "R_MIPS_26": "%call", "R_MIPS_32": "%word"}
DATA_SECTIONS = (".rodata", ".data", ".bss")
SYMBOL_NOTE = re.compile(r"%\w+\([^)]*\)")
ADDEND = re.compile(r"(?<=[,\t])-?(?:0x[0-9a-f]+|\d+)(?=(?:\(\w+\))? %sym)")
LOW_ADDEND = re.compile(r"(?<=[,\t])(-?\d+)(?=\(\w+\)$|$)")
RETARGETED = " -> +0x"
SHT_NOBITS, SHT_REL = 8, 9


@dataclass
class Instruction:
    offset: int  # relative to the function start
    mnemonic: str
    operands: str
    relocations: list[tuple[str, str]] = field(default_factory=list)
    target: int | None = None  # branch target relative to the function start

    @property
    def branch_target(self) -> int | None:
        """The local branch target; a relocated operand is a link-time placeholder."""

        return None if self.relocations else self.target


@dataclass(frozen=True)
class Section:
    """One data section: its bytes and the offsets of the words a relocation patches."""

    data: bytes = b""
    relocated: frozenset[int] = frozenset()

    def comparable(self) -> bytes:
        """The bytes with every relocated word zeroed.

        A relocated word (a jump-table entry) holds an offset into another
        section, which moves whenever the code before its target changes size.
        """

        data = bytearray(self.data)
        for offset in self.relocated:
            data[offset:offset + 4] = bytes(len(data[offset:offset + 4]))
        return bytes(data)


def function_listings(disassembly: str) -> dict[str, list[Instruction]]:
    """Instructions of every function in ``objdump -d -r -z --no-show-raw-insn`` text."""

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
            operands = instruction.group(3) or ""
            target = BRANCH_TARGET.search(operands)
            current.append(Instruction(int(instruction.group(1), 16) - start, instruction.group(2), operands,
                                       target=int(target.group(1), 16) - start if target else None))
        elif line.startswith("Disassembly of section"):
            current = None
    return listings


def label_lines(instructions: list[Instruction]) -> dict[int, str]:
    """Offsets inside the function that a branch targets, with their label names."""

    targets = sorted({instruction.branch_target for instruction in instructions
                      if instruction.branch_target is not None})
    return {target: f".L{number}" for number, target in enumerate(targets, start=1)}


def _section_note(instruction: Instruction, kind: str, symbol: str,
                  sections: dict[str, Section] | None) -> tuple[str, str]:
    """(operands, note) for one relocation; section-relative loads are named by content."""

    name = RELOCATION_NAMES.get(kind, kind)
    section = (sections or {}).get(symbol)
    addend = LOW_ADDEND.search(instruction.operands) if kind == "R_MIPS_LO16" else None
    if section is None or symbol == ".bss" or addend is None:
        return instruction.operands, f"{name}({symbol})"
    offset = int(addend.group(1))
    if offset in section.relocated:
        content = "relocated"
    elif 0 <= offset and offset + 4 <= len(section.data):
        content = section.data[offset:offset + 4].hex()
    else:
        return instruction.operands, f"{name}({symbol})"
    # The offset inside the section moves when an earlier literal is added; the word does not.
    operands = instruction.operands[:addend.start()] + "0" + instruction.operands[addend.end():]
    return operands, f"{name}({symbol}:{content})"


def render(instructions: list[Instruction], sections: dict[str, Section] | None = None) -> list[str]:
    """One comparable text line per instruction.

    Branch targets inside the function become ``.L<n>`` labels numbered in
    address order, each relocation replaces the link-time operand it patches,
    and a load from the object's own ``.rodata``/``.data`` is named by the
    word it reads, so equal code at different offsets renders equally.
    """

    labels = label_lines(instructions)
    lines: list[str] = []
    for instruction in instructions:
        operands = instruction.operands
        if instruction.relocations:
            notes = []
            for kind, symbol in instruction.relocations:
                operands, note = _section_note(Instruction(instruction.offset, instruction.mnemonic, operands),
                                               kind, symbol, sections)
                notes.append(note)
            if any(kind == "R_MIPS_26" for kind, _ in instruction.relocations):
                operands = notes[0]  # the printed call target is a link-time placeholder
            else:
                operands = f"{operands} {' '.join(notes)}"
        elif instruction.target is not None:
            operands = BRANCH_TARGET.sub(labels[instruction.target], operands)
        lines.append(f"{instruction.mnemonic}\t{operands}".rstrip())
    return lines


def _pairs(reference: list[str], candidate: list[str]) -> dict[int, int]:
    """reference index -> candidate index for equal lines and position-paired replacements."""

    mapping: dict[int, int] = {}
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, reference, candidate, autojunk=False).get_opcodes():
        if tag in ("equal", "replace"):
            for index in range(min(i2 - i1, j2 - j1)):
                mapping[i1 + index] = j1 + index
    return mapping


def aligned(reference: list[Instruction], candidate: list[Instruction],
            reference_sections: dict[str, Section] | None = None,
            candidate_sections: dict[str, Section] | None = None) -> tuple[list[str], list[str]]:
    """Rendered lines of both listings, with retargeted branches made visible.

    Labels are numbered by rank, so a branch whose target moved to a different
    instruction can still render as the same ``.L<n>``. Each pair of equal
    branch lines is therefore checked against the alignment of the two
    listings: when the targets do not correspond, both lines get their real
    target offset appended and no longer compare equal.
    """

    old, new = render(reference, reference_sections), render(candidate, candidate_sections)
    mapping = _pairs(old, new)
    mapped = set(mapping.values())
    old_index = {instruction.offset: index for index, instruction in enumerate(reference)}
    new_index = {instruction.offset: index for index, instruction in enumerate(candidate)}
    for i, j in mapping.items():
        before, after = reference[i].branch_target, candidate[j].branch_target
        if old[i] != new[j] or before is None or after is None:
            continue
        ti, tj = old_index.get(before), new_index.get(after)
        if (ti in mapping and mapping[ti] != tj) or (ti not in mapping and tj in mapped):
            old[i] += f"{RETARGETED}{before:x}"
            new[j] += f"{RETARGETED}{after:x}"
    return old, new


def _shape(line: str) -> str:
    return REGISTER.sub("R", line)


def _without_symbols(line: str) -> str:
    """``line`` without the symbol a relocation names or the addend it carries."""

    return ADDEND.sub("N", SYMBOL_NOTE.sub("%sym", line))


def _without_target(line: str) -> str:
    return line.split(RETARGETED)[0]


KINDS = ("register-only", "relocation-only", "branch-target", "other", "inserted", "deleted")


def classify(reference: list[str], candidate: list[str]) -> dict[str, int]:
    """Count differing lines by kind (see ``KINDS``)."""

    counts = dict.fromkeys(KINDS, 0)
    matcher = difflib.SequenceMatcher(None, reference, candidate, autojunk=False)
    for tag, i1, i2, j1, j2 in matcher.get_opcodes():
        if tag == "equal":
            continue
        paired = min(i2 - i1, j2 - j1)
        for index in range(paired):
            old, new = reference[i1 + index], candidate[j1 + index]
            if _without_target(old) == _without_target(new):
                counts["branch-target"] += 1
            elif _shape(old) == _shape(new):
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


def _transfers_control(mnemonic: str) -> bool:
    return mnemonic != "break" and mnemonic[:1] in ("j", "b")


def trim_padding(instructions: list[Instruction]) -> list[Instruction]:
    """Drop the alignment nops that follow a function's final delay slot."""

    end = len(instructions)
    while end > 0 and instructions[end - 1].mnemonic == "nop" and not instructions[end - 1].relocations:
        end -= 1
    # A nop directly after the last jump or branch is its delay slot, not padding.
    if 0 < end < len(instructions) and _transfers_control(instructions[end - 1].mnemonic):
        end += 1
    return instructions[:end]


def summary(counts: dict[str, int]) -> str:
    total = sum(counts.values())
    if not total:
        return "instruction diff: identical"
    parts = [f"{value} {name}" for name, value in counts.items() if value]
    return f"instruction diff: {total} lines differ ({', '.join(parts)})"


def _offset_at(instructions: list[Instruction], index: int) -> int:
    if index < len(instructions):
        return instructions[index].offset
    return instructions[-1].offset + 4 if instructions else 0


def diff_lines(reference: list[Instruction], candidate: list[Instruction], *, context: int = 2,
               lines: tuple[list[str], list[str]] | None = None) -> list[str]:
    """Unified diff of two listings: ``-`` reference, ``+`` candidate, with function offsets.

    ``lines`` are the rendered lines from ``aligned`` when the caller already has them.
    """

    old, new = lines if lines is not None else aligned(reference, candidate)
    old_labels, new_labels = label_lines(reference), label_lines(candidate)

    def shown(prefix: str, instructions: list[Instruction], rendered: list[str], labels: dict[int, str],
              index: int) -> str:
        offset = instructions[index].offset
        label = labels.get(offset, "")
        return f"{prefix} {offset:4x}: {label + ':' if label else '':6}{rendered[index]}"

    output: list[str] = []
    matcher = difflib.SequenceMatcher(None, old, new, autojunk=False)
    for group in matcher.get_grouped_opcodes(context):
        first = group[0]
        output.append(f"@@ reference +0x{_offset_at(reference, first[1]):x}, "
                      f"candidate +0x{_offset_at(candidate, first[3]):x} @@")
        for tag, i1, i2, j1, j2 in group:
            if tag == "equal":
                output += [shown(" ", candidate, new, new_labels, index) for index in range(j1, j2)]
                continue
            output += [shown("-", reference, old, old_labels, index) for index in range(i1, i2)]
            output += [shown("+", candidate, new, new_labels, index) for index in range(j1, j2)]
    return output


def compare_functions(base: dict[str, list[Instruction]], candidate: dict[str, list[Instruction]],
                      skip: set[str], base_sections: dict[str, Section] | None = None,
                      candidate_sections: dict[str, Section] | None = None) -> tuple[int, list[str]]:
    """(identical count, problems) for every function other than ``skip``.

    Listings are compared after rendering and without their trailing alignment
    nops, so a function that only moved, whose literals only moved inside
    ``.rodata``, or whose padding changed because a neighbour changed size
    counts as identical.
    """

    identical = 0
    problems: list[str] = []
    for name in base:
        if name in skip:
            continue
        if name not in candidate:
            problems.append(f"{name}: missing from the variant object")
            continue
        old, new = aligned(trim_padding(base[name]), trim_padding(candidate[name]),
                           base_sections, candidate_sections)
        if old == new:
            identical += 1
        else:
            counts = classify(old, new)
            problems.append(f"{name}: CHANGED ({summary(counts).removeprefix('instruction diff: ')})")
    problems += [f"{name}: only in the variant object" for name in candidate
                 if name not in base and name not in skip]
    return identical, problems


def words(data: bytes, limit: int = 16) -> str:
    shown = " ".join(data[index:index + 4].hex() for index in range(0, min(len(data), limit * 4), 4))
    return shown + (" ..." if len(data) > limit * 4 else "")


def data_sections(data: bytes) -> dict[str, Section]:
    """The data sections of a 32-bit big-endian ELF object (``.bss`` as zeros)."""

    if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 2:
        raise ValueError("expected a 32-bit big-endian ELF object")
    offset = struct.unpack_from(">I", data, 0x20)[0]
    entry_size, count, names_index = struct.unpack_from(">HHH", data, 0x2E)
    headers = [struct.unpack_from(">10I", data, offset + index * entry_size) for index in range(count)]
    names = headers[names_index][4]

    def name_of(header: tuple[int, ...]) -> str:
        start = names + header[0]
        return data[start:data.index(b"\0", start)].decode()

    contents: dict[str, bytes] = {}
    relocated: dict[str, set[int]] = {}
    for header in headers:
        name = name_of(header)
        if name in DATA_SECTIONS:
            contents[name] = bytes(header[5]) if header[1] == SHT_NOBITS else data[header[4]:header[4] + header[5]]
        elif header[1] == SHT_REL and name.removeprefix(".rel") in DATA_SECTIONS:
            entries = data[header[4]:header[4] + header[5]]
            relocated[name.removeprefix(".rel")] = {struct.unpack_from(">I", entries, index)[0]
                                                    for index in range(0, len(entries) - 7, 8)}
    return {name: Section(content, frozenset(relocated.get(name, ()))) for name, content in contents.items()}


def payload(data: bytes) -> bytes:
    """``data`` without its trailing zero words (object alignment padding)."""

    end = len(data.rstrip(b"\0"))
    return data[:(end + 3) & ~3]


def compare_sections(base: dict[str, Section], candidate: dict[str, Section]) -> list[str]:
    """One line per data section whose size or bytes differ from the current-source object.

    Relocated words (jump-table entries) are compared as zero: their values
    are offsets into the text, which a changed function size moves.
    """

    lines: list[str] = []
    for name in DATA_SECTIONS:
        before, after = base.get(name, Section()), candidate.get(name, Section())
        old, new = before.comparable(), after.comparable()
        if old == new:
            continue
        detail = f"{name}: size 0x{len(old):x} -> 0x{len(new):x}"
        if name == ".bss":
            lines.append(detail)
            continue
        # Padding is judged on the real bytes: a zeroed jump-table word is not padding.
        kept = len(payload(before.data))
        if new[:kept] == old[:kept] and len(new) >= kept:
            added = payload(after.data)[kept:]
            detail += f"; appended words: {words(added) or '(zero padding only)'}"
        else:
            first = next((index for index in range(0, min(len(old), len(new)), 4)
                          if old[index:index + 4] != new[index:index + 4]), min(len(old), len(new)))
            detail += f"; differs from +0x{first:x}, variant words there: {words(after.data[first:]) or '(none)'}"
        lines.append(detail)
    return lines
