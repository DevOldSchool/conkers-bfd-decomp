#!/usr/bin/env python3
"""Stack-frame plan of a reference function (and optionally a candidate object).

The plan reads a function's raw MIPS words, either from the `/* off vram WORD */`
comments of a spimdisasm reference listing under ``reference/`` or from the
``.text`` bytes of a compiled candidate object, and reports:

- the frame size from the prologue ``addiu $sp, $sp, -N``;
- saved registers and their slots;
- every distinct sp-relative slot the body reads, writes or takes the address
  of, classified as incoming-argument home, local/spill area, saved-register
  area or outgoing-argument area;
- an inferred split of the local area into named-local homes and spill words
  using the IDO -O2 -g3 convention: named locals get homes in declaration order
  from the frame top (unused and register-allocated ones included) and
  call-crossing compiler temporaries are spilled below the lowest named local.

The inference is a heuristic: a named local that lives across a call is stored
to its home exactly like a spilled temporary, so the summary gives lower bounds
and lists the ambiguous words. Decoding words rather than mnemonics keeps the
analysis independent of register spellings and of binutils.
"""

from __future__ import annotations

import argparse
import re
import struct
import sys
from dataclasses import dataclass, field
from itertools import combinations
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

GPR = (
    "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra",
)
SP = 29
CALLEE_SAVED = {"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "fp", "gp", "ra",
                "f20", "f22", "f24", "f26", "f28", "f30"}

# opcode -> (mnemonic, access size, kind, coprocessor register)
MEMORY_OPS = {
    0x20: ("lb", 1, "load", False), 0x21: ("lh", 2, "load", False),
    0x22: ("lwl", 4, "load", False), 0x23: ("lw", 4, "load", False),
    0x24: ("lbu", 1, "load", False), 0x25: ("lhu", 2, "load", False),
    0x26: ("lwr", 4, "load", False), 0x27: ("lwu", 4, "load", False),
    0x28: ("sb", 1, "store", False), 0x29: ("sh", 2, "store", False),
    0x2A: ("swl", 4, "store", False), 0x2B: ("sw", 4, "store", False),
    0x2E: ("swr", 4, "store", False),
    0x31: ("lwc1", 4, "load", True), 0x35: ("ldc1", 8, "load", True),
    0x37: ("ld", 8, "load", False),
    0x39: ("swc1", 4, "store", True), 0x3D: ("sdc1", 8, "store", True),
    0x3F: ("sd", 8, "store", False),
}
ADD_IMMEDIATE_OPS = {0x08: "addi", 0x09: "addiu", 0x19: "daddiu"}
MOVE_FUNCTS = {0x21: "addu", 0x25: "or", 0x2D: "daddu"}

INSTRUCTION_ROW = re.compile(
    r"^[ \t]*/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+([0-9A-Fa-f]{8})\s*\*/", re.MULTILINE
)
LABEL = re.compile(r"(?m)^[ \t]*glabel\s+(\S+)[ \t]*$")
DATA_DIRECTIVE = re.compile(r"^[ \t]*\.(word|byte|half|short|float|double|ascii|asciz|incbin)\b")


class FramePlanError(Exception):
    """The function or its words could not be located."""


@dataclass(frozen=True)
class Instruction:
    index: int
    word: int
    mnemonic: str
    call: bool = False
    frame_delta: int | None = None  # addiu $sp, $sp, N
    access: tuple[str, int, int, str] | None = None  # (kind, offset, size, register)


@dataclass(frozen=True)
class Access:
    index: int
    mnemonic: str
    kind: str  # load | store | address
    offset: int
    size: int
    register: str
    delay_slot: bool  # executes in a call's delay slot
    call_crossing: bool  # a store whose value is next reloaded only after a call


@dataclass
class Slot:
    offset: int
    size: int
    area: str  # arg-in | local | saved | arg-out
    accesses: list[Access] = field(default_factory=list)
    saved_register: str | None = None

    @property
    def end(self) -> int:
        return self.offset + self.size

    @property
    def address_taken(self) -> bool:
        return any(access.kind == "address" for access in self.accesses)

    @property
    def stores(self) -> list[Access]:
        return [access for access in self.accesses if access.kind == "store"]

    @property
    def loads(self) -> list[Access]:
        return [access for access in self.accesses if access.kind == "load"]

    @property
    def call_crossing(self) -> bool:
        return any(access.call_crossing for access in self.stores)

    def summary(self) -> str:
        """Compact access summary in instruction order, e.g. ``sw $a0; lw x2``."""

        if self.saved_register is not None:
            return f"${self.saved_register}"
        parts: list[str] = []
        for access in self.accesses:
            if access.kind == "address":
                text = f"&-> ${access.register}"
            elif access.kind == "store":
                text = f"{access.mnemonic} ${access.register}"
                if access.delay_slot:
                    text += " (delay)"
            else:
                text = access.mnemonic
            parts.append(text)
        compressed: list[str] = []
        counts: list[int] = []
        for text in parts:
            if compressed and compressed[-1] == text:
                counts[-1] += 1
            else:
                compressed.append(text)
                counts.append(1)
        rendered = "; ".join(
            text if count == 1 else f"{text} x{count}" for text, count in zip(compressed, counts)
        )
        notes = []
        if self.call_crossing:
            notes.append("call-crossing")
        if any(access.size < 4 for access in self.accesses if access.kind != "address"):
            notes.append("sub-word")
        if notes:
            rendered += f" [{', '.join(notes)}]"
        return rendered or "unused"


@dataclass
class Inference:
    local_words: list[int]  # descending sp offsets of every word in the local area
    named_words: list[int]
    crossing_words: list[int]
    unused_bottom_words: list[int]
    anchors: list[int]


@dataclass
class FramePlan:
    symbol: str
    frame_size: int
    instruction_count: int
    calls: int
    saved: dict[int, str]
    slots: list[Slot]
    outgoing: tuple[int, int] | None
    saved_area: tuple[int, int] | None
    local_area: tuple[int, int] | None

    def slot_at(self, offset: int) -> Slot | None:
        """The slot starting at ``offset``, else the first slot containing it."""

        for slot in self.slots:
            if slot.offset == offset:
                return slot
        for slot in self.slots:
            if slot.offset <= offset < slot.end:
                return slot
        return None

    def word_slots(self, word: int) -> list[Slot]:
        return [slot for slot in self.slots if slot.offset < word + 4 and slot.end > word]

    def infer(self) -> Inference | None:
        if self.local_area is None:
            return None
        low, high = self.local_area
        words = list(range(high - 4, low - 1, -4))
        anchors = sorted({slot.offset & ~3 for slot in self.slots if slot.address_taken
                          and low <= slot.offset < high})
        unused_bottom: list[int] = []
        crossing: list[int] = []
        remaining = list(words)
        while remaining and not self.word_slots(remaining[-1]):
            unused_bottom.insert(0, remaining.pop())
        while remaining and self._spill_like(remaining[-1], anchors):
            crossing.insert(0, remaining.pop())
        return Inference(words, remaining, crossing, unused_bottom, anchors)

    def _spill_like(self, word: int, anchors: list[int]) -> bool:
        if anchors and word >= min(anchors):
            return False
        slots = self.word_slots(word)
        if not slots:
            return False
        for slot in slots:
            if slot.address_taken or slot.size != 4 or not slot.stores:
                return False
            if not all(access.call_crossing for access in slot.stores):
                return False
        return True

    def render(self, *, label: str = "reference", indent: str = "  ", with_frame: bool = True) -> list[str]:
        lines = []
        frame = f"{self.frame_size:#x}" if self.frame_size else "leaf (no frame)"
        header = f"{indent}{label}: {self.instruction_count} instructions; {self.calls} calls"
        if with_frame:
            header = f"{indent}{label} frame {frame}; {self.instruction_count} instructions; {self.calls} calls"
        lines.append(header)
        areas = []
        if self.outgoing is not None:
            low, high = self.outgoing
            areas.append(f"arg-out {low:#x}..{high - 1:#x} ({(high - low) // 4} words)")
        if self.saved_area is not None:
            low, high = self.saved_area
            saved = ", ".join(f"${name} {offset:#x}" for offset, name in sorted(self.saved.items(), reverse=True))
            areas.append(f"saved {low:#x}..{high - 1:#x} ({saved})")
        if self.local_area is not None:
            low, high = self.local_area
            areas.append(f"local {low:#x}..{high - 1:#x} ({(high - low) // 4} words)")
        if areas:
            lines.append(f"{indent}areas: " + "; ".join(areas))
        lines.append(f"{indent}{'sp off':>7} {'size':>4}  {'area':7} access")
        for slot in sorted(self.slots, key=lambda item: -item.offset):
            lines.append(f"{indent}{hex(slot.offset):>7} {slot.size:>4}  {slot.area:7} {slot.summary()}")
        inference = self.infer()
        if inference is not None:
            lines.extend(f"{indent}{line}" for line in render_inference(inference))
        return lines


def render_inference(inference: Inference) -> list[str]:
    def span(words: list[int]) -> str:
        if not words:
            return ""
        if len(words) == 1:
            return f" ({words[0]:#x})"
        return f" ({words[0]:#x}..{words[-1]:#x})"

    named = inference.named_words
    parts = [f"named-local homes >= {len(named)} word{'s' if len(named) != 1 else ''}{span(named)}"]
    if inference.crossing_words:
        parts.append(
            f"call-crossing words below {len(inference.crossing_words)}{span(inference.crossing_words)}"
        )
    if inference.unused_bottom_words:
        parts.append(
            f"unused bottom words {len(inference.unused_bottom_words)}{span(inference.unused_bottom_words)}"
        )
    lines = ["inferred: " + "; ".join(parts)]
    if inference.anchors:
        lines.append("address-taken anchors: " + ", ".join(f"{word:#x}" for word in inference.anchors)
                     + " (aggregate or &local; every word above is a named home)")
    if inference.crossing_words:
        lines.append("call-crossing words are spill temps or named locals that live across a call;"
                     " compare with the candidate's named homes")
    return lines


def sign16(value: int) -> int:
    return value - 0x10000 if value & 0x8000 else value


def decode(words: list[int]) -> list[Instruction]:
    """Decode the sp-relative, call and frame instructions of one function."""

    decoded: list[Instruction] = []
    for index, word in enumerate(words):
        opcode = word >> 26
        rs, rt, rd = (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
        funct = word & 63
        immediate = sign16(word & 0xFFFF)
        instruction = Instruction(index, word, "")
        if opcode == 0x03:
            instruction = Instruction(index, word, "jal", call=True)
        elif opcode == 0 and funct == 0x09:
            instruction = Instruction(index, word, "jalr", call=True)
        elif opcode == 0 and funct in MOVE_FUNCTS and {rs, rt} == {SP, 0} and rd != SP:
            instruction = Instruction(index, word, MOVE_FUNCTS[funct],
                                      access=("address", 0, 0, GPR[rd]))
        elif opcode in ADD_IMMEDIATE_OPS and rs == SP:
            mnemonic = ADD_IMMEDIATE_OPS[opcode]
            if rt == SP:
                instruction = Instruction(index, word, mnemonic, frame_delta=immediate)
            else:
                instruction = Instruction(index, word, mnemonic,
                                          access=("address", immediate, 0, GPR[rt]))
        elif opcode in MEMORY_OPS and rs == SP:
            mnemonic, size, kind, coprocessor = MEMORY_OPS[opcode]
            register = f"f{rt}" if coprocessor else GPR[rt]
            instruction = Instruction(index, word, mnemonic, access=(kind, immediate, size, register))
        decoded.append(instruction)
    return decoded


def analyze(symbol: str, words: list[int]) -> FramePlan:
    instructions = decode(words)
    frame_size = 0
    for instruction in instructions[:12]:
        if instruction.frame_delta is not None and instruction.frame_delta < 0:
            frame_size = -instruction.frame_delta
            break
    calls = [instruction.index for instruction in instructions if instruction.call]

    raw: dict[tuple[int, int], list[Access]] = {}
    for instruction in instructions:
        if instruction.access is None:
            continue
        kind, offset, size, register = instruction.access
        delay_slot = instruction.index > 0 and instructions[instruction.index - 1].call
        crossing = False
        if kind == "store":
            crossing = _store_crosses_call(instructions, instruction.index, offset, size, calls)
        key = (offset, size) if kind != "address" else (offset, 0)
        raw.setdefault(key, []).append(
            Access(instruction.index, instruction.mnemonic, kind, offset, size, register, delay_slot, crossing)
        )

    slots = _merge_slots(raw)
    saved: dict[int, str] = {}
    for slot in slots:
        first = slot.accesses[0]
        if (first.kind == "store" and first.register in CALLEE_SAVED and slot.size >= 4
                and 0 <= slot.offset < frame_size
                and any(access.kind == "load" and access.register == first.register
                        for access in slot.accesses)):
            saved[slot.offset] = first.register
            slot.saved_register = first.register
        elif (first.kind == "store" and first.register == "ra" and 0 <= slot.offset < frame_size):
            saved[slot.offset] = "ra"
            slot.saved_register = "ra"

    outgoing = saved_area = local_area = None
    if frame_size:
        if saved:
            low = min(saved) & ~7
            high = (max(offset + (8 if name.startswith("f") else 4) for offset, name in saved.items()) + 7) & ~7
            saved_area = (low, min(high, frame_size))
            if calls:
                outgoing = (0, low)
            local_low = saved_area[1]
        else:
            local_low = 0
            if calls:
                outgoing = (0, min(0x10, frame_size))
                local_low = outgoing[1]
        if local_low < frame_size:
            local_area = (local_low, frame_size)

    for slot in slots:
        if slot.saved_register is not None:
            slot.area = "saved"
        elif slot.offset >= frame_size:
            slot.area = "arg-in"
        elif outgoing is not None and slot.offset < outgoing[1]:
            slot.area = "arg-out"
        elif saved_area is not None and saved_area[0] <= slot.offset < saved_area[1]:
            slot.area = "saved"
        else:
            slot.area = "local"
    return FramePlan(symbol, frame_size, len(instructions), len(calls), saved, slots,
                     outgoing, saved_area, local_area)


def _store_crosses_call(instructions: list[Instruction], index: int, offset: int, size: int,
                        calls: list[int]) -> bool:
    """True when the next reload of this slot happens only after a call.

    A store in a call's delay slot executes before that call, so the call
    counts as crossed. Control flow is ignored: this is linear evidence.
    """

    first_crossed = index - 1 if index > 0 and instructions[index - 1].call else index + 1
    for later in instructions[index + 1:]:
        if later.access is None or later.access[0] != "load":
            continue
        _kind, other, other_size, _register = later.access
        if other < offset + size and other + other_size > offset:
            return any(first_crossed <= call < later.index for call in calls)
    return False


def _merge_slots(raw: dict[tuple[int, int], list[Access]]) -> list[Slot]:
    """Fold address-taken markers into the slot that starts at their offset."""

    slots: list[Slot] = []
    for (offset, size), accesses in sorted(raw.items(), key=lambda item: (item[0][0], -item[0][1])):
        if size == 0:
            continue
        slots.append(Slot(offset, size, "local", list(accesses)))
    for (offset, size), accesses in raw.items():
        if size:
            continue
        target = next((slot for slot in slots if slot.offset == offset), None)
        if target is None:
            target = next((slot for slot in slots if slot.offset <= offset < slot.end), None)
        if target is None:
            target = Slot(offset, 4, "local")
            slots.append(target)
        target.accesses.extend(accesses)
    for slot in slots:
        slot.accesses.sort(key=lambda access: access.index)
    slots.sort(key=lambda slot: slot.offset)
    return slots


# --- reference listings -----------------------------------------------------


def reference_words(text: str, symbol: str, size_bytes: int | None = None) -> list[int]:
    """Instruction words of ``symbol`` in a spimdisasm listing.

    With ``size_bytes`` exactly that many instruction rows are taken (interior
    secondary ``glabel`` entries stay inside the function). Otherwise the
    function ends at the next ``glabel`` or data directive.
    """

    labels = list(LABEL.finditer(text))
    try:
        position = next(index for index, label in enumerate(labels) if label.group(1) == symbol)
    except StopIteration as error:
        raise FramePlanError(f"{symbol} has no glabel in the reference listing") from error
    start = labels[position].end()
    if size_bytes is not None:
        if size_bytes <= 0 or size_bytes % 4:
            raise FramePlanError(f"{symbol} has an invalid {size_bytes}-byte span")
        rows = INSTRUCTION_ROW.findall(text[start:])
        count = size_bytes // 4
        if len(rows) < count:
            raise FramePlanError(f"{symbol} reference listing is shorter than its {size_bytes}-byte span")
        return [int(row, 16) for row in rows[:count]]
    end = labels[position + 1].start() if position + 1 < len(labels) else len(text)
    words = []
    for line in text[start:end].splitlines():
        if DATA_DIRECTIVE.match(line):
            break
        match = INSTRUCTION_ROW.match(line)
        if match:
            words.append(int(match.group(1), 16))
    return words


def reference_plan(assembly: Path, symbol: str, size_bytes: int | None = None) -> FramePlan:
    text = assembly.read_text(encoding="utf-8")
    return analyze(symbol, reference_words(text, symbol, size_bytes))


def reference_frame_size(assembly: Path, symbol: str) -> int | None:
    """Prologue frame size, or None for a leaf without a frame or an unknown symbol."""

    text = assembly.read_text(encoding="utf-8")
    try:
        words = reference_words(text, symbol)
    except FramePlanError:
        return None
    plan = analyze(symbol, words[:12])
    return plan.frame_size or None


# --- candidate objects --------------------------------------------------------


def elf_sections(data: bytes) -> dict[str, tuple[int, int, int]]:
    """Map section name -> (file offset, size, index) of a 32-bit big-endian ELF."""

    if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 2:
        raise FramePlanError("expected a 32-bit big-endian ELF object")
    shoff = struct.unpack(">I", data[0x20:0x24])[0]
    shentsize, shnum, shstrndx = struct.unpack(">HHH", data[0x2E:0x34])
    headers = [
        struct.unpack(">IIIIIIIIII", data[shoff + i * shentsize: shoff + i * shentsize + 40])
        for i in range(shnum)
    ]
    strtab = headers[shstrndx][4]
    sections = {}
    for index, header in enumerate(headers):
        start = strtab + header[0]
        name = data[start: data.index(b"\0", start)].decode()
        sections[name] = (header[4], header[5], index)
    return sections


def object_words(path: Path, symbol: str) -> list[int]:
    """Instruction words of ``symbol`` from an object's ``.text`` via ``.symtab``."""

    data = path.read_bytes()
    sections = elf_sections(data)
    for name in (".symtab", ".strtab", ".text"):
        if name not in sections:
            raise FramePlanError(f"{path.name} has no {name} section")
    sym_offset, sym_size, _ = sections[".symtab"]
    str_offset = sections[".strtab"][0]
    text_offset, text_size, text_index = sections[".text"]
    functions: list[tuple[str, int, int]] = []
    for entry in range(sym_offset, sym_offset + sym_size, 16):
        st_name, st_value, st_size, _info, _other, st_shndx = struct.unpack(">IIIBBH", data[entry: entry + 16])
        if st_shndx != text_index:
            continue
        name = data[str_offset + st_name: data.index(b"\0", str_offset + st_name)].decode(errors="replace")
        functions.append((name, st_value, st_size))
    match = next((entry for entry in functions if entry[0] == symbol), None)
    if match is None:
        raise FramePlanError(f"{symbol} not found in {path.name} .text symbols")
    _name, value, size = match
    if not size:
        following = [other_value for _other, other_value, _size in functions if other_value > value]
        size = (min(following) if following else text_size) - value
    size -= size % 4
    raw = data[text_offset + value: text_offset + value + size]
    return [int.from_bytes(raw[index: index + 4], "big") for index in range(0, len(raw), 4)]


def object_plan(path: Path, symbol: str) -> FramePlan:
    return analyze(symbol, object_words(path, symbol))


def object_frame_size(path: Path, symbol: str) -> int | None:
    """Prologue frame size of a compiled function, or None without a frame."""

    return analyze(symbol, object_words(path, symbol)[:12]).frame_size or None


# --- side-by-side rendering -----------------------------------------------------


def render_block(reference: FramePlan, candidate: FramePlan | None, *, indent: str = "  ") -> list[str]:
    """``frame-plan:`` block: both frames, the reference table and the inference."""

    lines = ["frame-plan:"]
    reference_frame = f"{reference.frame_size:#x}" if reference.frame_size else "leaf"
    if candidate is None:
        candidate_frame = "unavailable"
    else:
        candidate_frame = f"{candidate.frame_size:#x}" if candidate.frame_size else "leaf"
    verdict = ""
    if candidate is not None:
        verdict = " (match)" if candidate.frame_size == reference.frame_size else " (MISMATCH)"
    lines.append(f"{indent}reference frame {reference_frame}; candidate frame {candidate_frame}{verdict}")
    lines.extend(reference.render(label="reference", indent=indent, with_frame=False))
    if candidate is not None and candidate.frame_size != reference.frame_size:
        lines.append(f"{indent}candidate slots (sp offsets of the candidate's own frame):")
        for slot in sorted(candidate.slots, key=lambda item: -item.offset):
            lines.append(f"{indent}{hex(slot.offset):>7} {slot.size:>4}  {slot.area:7} {slot.summary()}")
    return lines


# --- local-area word account -----------------------------------------------------
#
# Under IDO -O2 -g3 the candidate's local area (between the saved registers and
# the frame top) holds, from the top down:
#
# - a home for every named local in declaration order, block-scoped ones
#   included (sibling blocks do not share space) and register-only or
#   `register` ones too. Homes pack by natural alignment (aggregates at least
#   word-aligned). They exist only once some named local needs memory; until
#   then their .mdebug offsets fall below the local area and cost nothing;
# - one reserved word per call-containing argument (`f(g(x))`, RNG calls passed
#   inline), counted per statement and shared across statements, so the area
#   holds the largest statement's count. A spilled argument value reuses it;
# - further spill words and other uopt temporaries;
# - at most one alignment word keeping the frame 8-byte aligned.

C_KEYWORDS = frozenset({
    "if", "else", "while", "for", "do", "switch", "case", "default", "return", "sizeof",
    "goto", "break", "continue",
})
CONDITION_KEYWORDS = frozenset({"if", "while", "for", "switch"})
C_NOISE = re.compile(
    r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'|^[ \t]*#[^\n]*(?:\\\n[^\n]*)*",
    re.DOTALL | re.MULTILINE,
)
C_TOKEN = re.compile(r"[A-Za-z_]\w*|\d[\w.]*|->|\+\+|--|&&|\|\||<<|>>|\S")
FUNCTION_MACRO = re.compile(r"(?m)^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)\(")
MAX_SEARCH_WORDS = 6  # largest local-area surplus the attribution search explains
MAX_REMOVED_HOMES = 4
MAX_SEARCH_HOMES = 24  # beyond this only homes the code never touches are tried


def function_like_macros(text: str) -> set[str]:
    """Names of function-like macros defined in ``text``; their invocations are not calls."""

    return set(FUNCTION_MACRO.findall(text))


@dataclass(frozen=True)
class CallArgumentStatement:
    count: int  # call-containing argument expressions in the statement
    text: str  # the statement, whitespace-normalised


def call_argument_statements(body: str, macros: set[str] | frozenset[str] = frozenset()) -> list[CallArgumentStatement]:
    """Statements of a C function body that pass call-containing arguments, largest first.

    Statements end at ``;``, braces, ``else``/``do`` and after the condition of
    ``if``/``while``/``for``/``switch``; each ``for`` clause is its own statement.
    Every argument, at any nesting level, whose expression contains a call counts
    once. Invocations of ``macros`` are not calls, though calls inside their
    arguments still count their own arguments.
    """

    text = C_NOISE.sub(lambda match: re.sub(r"[^\n]", " ", match.group(0)), body)
    statements: list[list[re.Match[str]]] = [[]]
    depth = 0
    condition_depth: int | None = None
    pending_condition = False

    def close() -> None:
        if statements[-1]:
            statements.append([])

    for match in C_TOKEN.finditer(text):
        token = match.group(0)
        if token in (";", "{", "}", "else", "do"):
            close()
            continue
        statements[-1].append(match)
        if token in CONDITION_KEYWORDS:
            pending_condition = True
        elif token == "(":
            depth += 1
            if pending_condition:
                condition_depth, pending_condition = depth, False
        elif token == ")":
            if condition_depth == depth:
                condition_depth = None
                close()
            depth -= 1
    found = []
    for matches in statements:
        tokens = [match.group(0) for match in matches]
        count = _call_argument_count(tokens, macros)
        if count:
            snippet = " ".join(text[matches[0].start(): matches[-1].end()].split())
            found.append(CallArgumentStatement(count, snippet))
    found.sort(key=lambda statement: -statement.count)
    return found


def _matching(tokens: list[str], index: int, step: int) -> int | None:
    opening, closing = ("(", ")") if step > 0 else (")", "(")
    depth = 0
    position = index
    while 0 <= position < len(tokens):
        if tokens[position] == opening:
            depth += 1
        elif tokens[position] == closing:
            depth -= 1
            if depth == 0:
                return position
        position += step
    return None


def _is_call(tokens: list[str], index: int, macros: set[str] | frozenset[str]) -> bool:
    """True when the ``(`` at ``index`` opens a call's argument list."""

    if index == 0:
        return False
    previous = tokens[index - 1]
    if previous == "]":
        return True
    if previous == ")":
        # `(*pointer)(x)` calls through a pointer; `(type)(x)` is a cast.
        opening = _matching(tokens, index - 1, -1)
        return opening is not None and tokens[opening + 1: opening + 2] == ["*"]
    return (previous[0].isalpha() or previous[0] == "_") and previous not in C_KEYWORDS \
        and previous not in macros


def _call_argument_count(tokens: list[str], macros: set[str] | frozenset[str]) -> int:
    count = 0
    for index, token in enumerate(tokens):
        if token != "(" or not _is_call(tokens, index, macros):
            continue
        closing = _matching(tokens, index, 1)
        end = len(tokens) if closing is None else closing
        start = index + 1
        depth = 0
        for position in range(index + 1, end + 1):
            if position < end:
                if tokens[position] in ("(", "["):
                    depth += 1
                elif tokens[position] in (")", "]"):
                    depth -= 1
                if depth or tokens[position] != ",":
                    continue
            if any(tokens[inner] == "(" and _is_call(tokens, inner, macros) for inner in range(start, position)):
                count += 1
            start = position + 1
    return count


@dataclass(frozen=True)
class NamedHome:
    name: str
    offset: int  # sp offset in the candidate frame
    size: int | None = None  # bytes from .mdebug type information
    block: bool = False  # declared in a nested block
    aggregate: bool = False  # array, struct or union


@dataclass
class LocalAccount:
    frame_size: int
    local_area: tuple[int, int] | None
    homes: list[NamedHome]
    materialized: bool  # the homes occupy frame words
    named_words: int
    call_arg_words: int
    call_arg_statements: list[CallArgumentStatement]
    spill_words: list[int]  # used words below the named homes
    alignment: int | None  # 0 or 1 from the pad probe; None when unknown
    accessed: set[str]  # homes the candidate's code reads, writes or takes the address of
    layout: list[tuple[int, int]] | None  # (size, alignment) per home reproducing the offsets

    @property
    def words(self) -> int:
        if self.local_area is None:
            return 0
        low, high = self.local_area
        return (high - low) // 4

    @property
    def extra_spill_words(self) -> int:
        """Spill words beyond those a spilled argument value takes in a call-arg word."""

        return max(0, len(self.spill_words) - self.call_arg_words)

    @property
    def other_words(self) -> int | None:
        """Words left for other uopt temporaries; None while the alignment is unknown."""

        if self.alignment is None:
            return None
        return (self.words - self.named_words - self.call_arg_words - self.extra_spill_words
                - self.alignment)


def _natural_alignment(home: NamedHome) -> int:
    if home.size is None:
        return 1
    if home.aggregate:
        return 4
    return home.size if home.size in (1, 2, 4, 8) else 1


def home_layout(homes: list[NamedHome], frame_size: int) -> list[tuple[int, int]] | None:
    """(size, alignment) per home that reproduces the .mdebug offsets when packed.

    Homes are packed downward from the frame top in declaration order. A home
    without a usable size takes its span down from the previous home.
    """

    cursor = 0
    layout: list[tuple[int, int]] = []
    for home in homes:
        relative = home.offset - frame_size
        if relative > cursor:
            return None
        choices: list[tuple[int, int]] = []
        if home.size:
            natural = _natural_alignment(home)
            choices.extend((home.size, alignment) for alignment in (1, 2, 4, 8) if alignment >= natural)
        choices.append((cursor - relative, 1))
        for size, alignment in choices:
            if (cursor - size) // alignment * alignment == relative:
                layout.append((size, alignment))
                break
        cursor = relative
    return layout


def pack_homes(layout: list[tuple[int, int]]) -> list[int]:
    """Frame-top-relative offsets of homes packed in order."""

    cursor = 0
    offsets = []
    for size, alignment in layout:
        cursor = (cursor - size) // alignment * alignment
        offsets.append(cursor)
    return offsets


def _words_from_top(offsets: list[int]) -> int:
    return (-min(offsets) + 3) // 4 if offsets else 0


def account_local_area(plan: FramePlan, homes: list[NamedHome],
                       statements: list[CallArgumentStatement], alignment: int | None) -> LocalAccount:
    """Split the candidate's local area into named homes, call-arg temps, spills and alignment."""

    local_area = plan.local_area
    low, high = local_area if local_area is not None else (plan.frame_size, plan.frame_size)
    materialized = bool(homes) and local_area is not None and all(low <= home.offset < high for home in homes)
    named_words = (high - (min(home.offset for home in homes) & ~3)) // 4 if materialized else 0
    floor = high - named_words * 4
    spill_words = [word for word in range(floor - 4, low - 1, -4) if plan.word_slots(word)]
    accessed = set()
    if materialized:
        for home in homes:
            end = home.offset + (home.size or 4)
            if any(slot.offset < end and slot.end > home.offset for slot in plan.slots if slot.area == "local"):
                accessed.add(home.name)
    return LocalAccount(
        plan.frame_size, local_area, list(homes), materialized, named_words,
        statements[0].count if statements else 0, list(statements), spill_words, alignment,
        accessed, home_layout(homes, plan.frame_size) if materialized else None,
    )


@dataclass(frozen=True)
class Explanation:
    named: tuple[str, ...]  # homes the reference lacks
    call_arg_words: int
    call_arg_statements: int  # statements whose call-containing arguments must be split out
    spill_words: int
    alignment: int  # candidate alignment words minus the hypothesis' alignment words

    @property
    def units(self) -> int:
        return len(self.named) + self.call_arg_statements + self.spill_words

    def signature(self) -> tuple[int, int, int, int]:
        return (len(self.named), self.call_arg_words, self.spill_words, self.alignment)


def _area_words(area: tuple[int, int] | None) -> int:
    return (area[1] - area[0]) // 4 if area is not None else 0


def _reference_words(reference: FramePlan) -> set[int]:
    """Frame-top-relative words the reference code touches in its local area.

    A load or store covers every word it overlaps, so an eight-byte ``sdc1``
    covers two; taking an address marks only the word it points at.
    """

    words = set()
    for slot in reference.slots:
        if slot.area != "local":
            continue
        for access in slot.accesses:
            end = access.offset + (access.size if access.kind != "address" else 1)
            words.update(range(access.offset & ~3, end, 4))
    return {word - reference.frame_size for word in words}


def explain_surplus(account: LocalAccount, reference: FramePlan) -> list[Explanation]:
    """Fewest-unit ways to remove the candidate's surplus local words, best first.

    A unit is one named home, one statement whose call-containing arguments are
    split into separate statements, or one spill word the reference lacks.
    Removing a home must not move a used candidate home off a word the
    reference also uses. Alignment follows from the remaining word parity.
    Ties prefer no alignment change, then call-arg temps over named homes; ways
    needing one more unit than the best are kept as alternatives.
    """

    target = _area_words(reference.local_area)
    surplus = account.words - target
    if surplus <= 0 or surplus > MAX_SEARCH_WORDS:
        return []
    reference_words = _reference_words(reference)
    order = [home.name for home in account.homes]
    used = {index for index, home in enumerate(account.homes) if home.name in account.accessed}

    def aligned(offsets: list[int], kept: list[int]) -> set[int]:
        return {index for position, index in enumerate(kept)
                if index in used and (offsets[position] & ~3) in reference_words}

    named_options: list[tuple[tuple[int, ...], int]] = [((), 0)]
    if account.materialized and account.layout is not None:
        everything = list(range(len(account.homes)))
        baseline = aligned(pack_homes(account.layout), everything)
        pool = everything if len(everything) <= MAX_SEARCH_HOMES else \
            [index for index in everything if index not in used]
        for count in range(1, min(surplus + 1, MAX_REMOVED_HOMES, len(pool)) + 1):
            for removed in combinations(pool, count):
                kept = [index for index in everything if index not in removed]
                offsets = pack_homes([account.layout[index] for index in kept])
                freed = account.named_words - _words_from_top(offsets)
                # Each home already on a reference word must stay on one; a newly
                # aligned home does not make up for losing another.
                if freed <= 0 or not baseline <= aligned(offsets, kept):
                    continue
                named_options.append((removed, freed))
    counts = [statement.count for statement in account.call_arg_statements]
    call_options = [(0, 0)]
    if counts:
        for level in sorted(set(counts[1:]) | {0}):
            if level < counts[0]:
                call_options.append((counts[0] - level, sum(1 for count in counts if count > level)))
    reference_inference = reference.infer()
    reference_spills = len(reference_inference.crossing_words) if reference_inference else 0
    spill_limit = min(account.extra_spill_words, max(0, len(account.spill_words) - reference_spills))
    alignments = [account.alignment] if account.alignment is not None else [0, 1]

    found: dict[tuple, Explanation] = {}
    for removed, freed in named_options:
        for call_words, call_statements in call_options:
            for spills in range(spill_limit + 1):
                for alignment in alignments:
                    content = account.words - alignment - freed - call_words - spills
                    if content < 0 or content + content % 2 != target:
                        continue
                    explanation = Explanation(tuple(order[index] for index in removed), call_words,
                                              call_statements, spills, alignment - content % 2)
                    found.setdefault((explanation.named, explanation.signature()), explanation)
    ranked = sorted(found.values(), key=lambda item: (item.units, abs(item.alignment), len(item.named),
                                                     [order.index(name) for name in item.named]))
    return [item for item in ranked if item.units <= ranked[0].units + 1] if ranked else []


def pinned_above(account: LocalAccount, reference: FramePlan,
                 choices: list[tuple[str, ...]]) -> tuple[str, list[str]] | None:
    """The lowest used home already on a reference word, and the unused homes above it.

    The search keeps such homes in place, so a surplus home declared above one
    is only removable together with moving a later local up.
    """

    if account.layout is None:
        return None
    reference_words = _reference_words(reference)
    offsets = pack_homes(account.layout)
    pinned = [index for index, home in enumerate(account.homes)
              if home.name in account.accessed and (offsets[index] & ~3) in reference_words]
    if not pinned:
        return None
    lowest = max(pinned)
    chosen = {name for names in choices for name in names}
    names = [home.name for home in account.homes[:lowest]
             if home.name not in account.accessed and home.name not in chosen]
    return (account.homes[lowest].name, names) if names else None


def _plural(count: int, singular: str, plural: str | None = None) -> str:
    return f"{count} {singular if abs(count) == 1 else (plural or singular + 's')}"


def _explanation_parts(explanation: Explanation) -> list[str]:
    parts = []
    if explanation.named:
        parts.append(f"{len(explanation.named)} named")
    if explanation.call_arg_words:
        parts.append(_plural(explanation.call_arg_words, "call-arg temp"))
    if explanation.spill_words:
        parts.append(_plural(explanation.spill_words, "spill word"))
    if explanation.alignment:
        parts.append(f"{explanation.alignment} alignment")
    return parts


def _grouped(explanations: list[Explanation]) -> list[tuple[Explanation, list[tuple[str, ...]]]]:
    """Explanations with the same category counts, keeping each one's named homes."""

    groups: dict[tuple[int, int, int, int], tuple[Explanation, list[tuple[str, ...]]]] = {}
    for explanation in explanations:
        entry = groups.setdefault(explanation.signature(), (explanation, []))
        if explanation.named:
            entry[1].append(explanation.named)
    return list(groups.values())


def _named_choices(choices: list[tuple[str, ...]]) -> str:
    return " or ".join(", ".join(names) for names in choices[:6]) + (" or ..." if len(choices) > 6 else "")


def render_account(account: LocalAccount, candidate: FramePlan, reference: FramePlan,
                   *, indent: str = "  ") -> list[str]:
    """``local-area account:`` block ending in a one-line word delta against the reference."""

    lines = [f"local-area account (candidate frame {candidate.frame_size:#x}, reference {reference.frame_size:#x}):"]
    if account.local_area is not None:
        low, high = account.local_area
        lines.append(f"{indent}candidate local {low:#x}..{high - 1:#x}: {_plural(account.words, 'word')}")
    else:
        lines.append(f"{indent}candidate local area: none")
    sub = indent * 2
    if account.homes:
        blocks = sum(1 for home in account.homes if home.block)
        state = "" if account.materialized else "; no named local needs memory, so the homes cost no words"
        lines.append(f"{sub}named homes {_plural(account.named_words, 'word')} ({_plural(len(account.homes), 'local')},"
                     f" {blocks} block-scoped; * = home used by the code{state}):")
        entries = []
        for home in account.homes:
            size = home.size if home.size is not None else "?"
            text = f"{home.name} {size}{'*' if home.name in account.accessed else ''}"
            entries.append(text + (" [block]" if home.block else ""))
        lines.append(f"{sub}{indent}" + ", ".join(entries))
    else:
        lines.append(f"{sub}named homes 0 words (no named locals)")
    if account.call_arg_statements:
        largest = account.call_arg_statements[0]
        snippet = largest.text if len(largest.text) <= 72 else largest.text[:69] + "..."
        lines.append(f"{sub}call-arg temps {_plural(account.call_arg_words, 'word')} (largest statement: {snippet})")
    else:
        lines.append(f"{sub}call-arg temps 0 words (no call-containing arguments)")
    spill = ", ".join(f"{word:#x}" for word in account.spill_words)
    lines.append(f"{sub}spill words {len(account.spill_words)}{f' ({spill})' if spill else ''}; "
                 f"{account.extra_spill_words} beyond the call-arg temps")
    if account.alignment is None:
        rest = account.words - account.named_words - account.call_arg_words - account.extra_spill_words
        lines.append(f"{sub}alignment and other temps {_plural(rest, 'word')} (pad probe unavailable)")
    else:
        lines.append(f"{sub}alignment {account.alignment} (pad probe: one more named word "
                     f"{'fits in the frame' if account.alignment else 'grows the frame'})")
        other = account.other_words
        if other is not None and other < 0:
            lines.append(f"{sub}model overcount {_plural(-other, 'word')} (a call-arg or spill estimate is too high)")
        else:
            lines.append(f"{sub}other uopt temps {_plural(other, 'word')}")
    inference = reference.infer()
    if reference.local_area is not None:
        low, high = reference.local_area
        summary = f"{indent}reference local {low:#x}..{high - 1:#x}: {_plural(_area_words(reference.local_area), 'word')}"
        if inference is not None:
            summary += f" (named homes >= {len(inference.named_words)} words"
            if inference.crossing_words:
                summary += f"; {_plural(len(inference.crossing_words), 'call-crossing bottom word')}"
            if inference.unused_bottom_words:
                summary += f"; {_plural(len(inference.unused_bottom_words), 'unused bottom word')}"
            summary += ")"
        lines.append(summary)
    else:
        lines.append(f"{indent}reference local area: none")
    lines.extend(f"{indent}{line}" for line in delta_lines(account, candidate, reference))
    return lines


def delta_lines(account: LocalAccount, candidate: FramePlan, reference: FramePlan) -> list[str]:
    """The one-line word delta plus the homes or statements it names."""

    frame_words = (candidate.frame_size - reference.frame_size) // 4
    parts: list[str] = []
    for label, mine, theirs in (("saved-register word", candidate.saved_area, reference.saved_area),
                                ("outgoing-arg word", candidate.outgoing, reference.outgoing)):
        difference = _area_words(mine) - _area_words(theirs)
        if difference:
            parts.append(_plural(difference, label))
    local = account.words - _area_words(reference.local_area)
    details: list[str] = []
    if local > 0:
        groups = _grouped(explain_surplus(account, reference))
        if groups:
            best, choices = groups[0]
            parts.extend(_explanation_parts(best))
            if best.named:
                details.append(f"named: drop or merge {_named_choices(choices)}")
                above = pinned_above(account, reference, choices)
                if above:
                    pinned, names = above
                    which = names[0] if len(names) == 1 else f"one of {', '.join(names)}"
                    details.append(f"  or drop {which} and declare a later local before {pinned}"
                                   f" ({pinned}'s home lines up with a reference word)")
            if best.call_arg_words:
                details.append(f"call-arg temps: give {_plural(best.call_arg_statements, 'statement')} one call each"
                               f" (largest: {account.call_arg_statements[0].count} call-containing arguments)")
            for other, other_choices in groups[1:]:
                text = ", ".join(_explanation_parts(other))
                if other.named:
                    text += f" ({_named_choices(other_choices)})"
                details.append(f"or: {text}")
            if account.alignment is None:
                details.append("alignment assumed: the pad probe was unavailable")
        elif local > MAX_SEARCH_WORDS:
            parts.append(f"{_plural(local, 'local word')} (too many to attribute; compare the named homes first)")
        else:
            parts.append(f"{_plural(local, 'local word')} unexplained")
    elif local < 0:
        missing = -local
        if account.alignment is None:
            parts.append(f"local area {_plural(missing, 'word')} short")
        else:
            content = account.words - account.alignment
            target = _area_words(reference.local_area)
            options = []
            for needed in sorted(needed for needed in (target - content, target - 1 - content) if needed > 0):
                padded = (content + needed) % 2
                options.append(f"{needed}{' (+1 alignment)' if padded else ''}")
            parts.append(f"local area short: add {' or '.join(options)} words of named locals,"
                         " call-containing arguments or spills")
    sign = "+" if frame_words > 0 else ""
    summary = f"candidate {sign}{_plural(frame_words, 'word')}"
    lines = [summary + (": " + ", ".join(parts) if parts else "")]
    lines.extend(details)
    return lines


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("target", help="work-item ID (default) or a reference .s listing with --assembly")
    parser.add_argument("symbol", nargs="?", help="symbol inside the listing given with --assembly")
    parser.add_argument("--profile", default="us", choices=("us", "eu"))
    parser.add_argument("--assembly", action="store_true", help="treat TARGET as a listing path")
    parser.add_argument("--size", type=lambda value: int(value, 0), help="registered byte span of the function")
    parser.add_argument("--candidate", type=Path, help="compiled object holding the candidate symbol")
    arguments = parser.parse_args()
    try:
        if arguments.assembly:
            if not arguments.symbol:
                parser.error("--assembly needs the symbol")
            assembly, symbol = Path(arguments.target), arguments.symbol
        else:
            import m2c  # located the way diff.py and m2c.py locate reference functions

            assembly, symbol = m2c.locate_registered_function(arguments.profile, arguments.target)
        reference = reference_plan(assembly, symbol, arguments.size)
        candidate = object_plan(arguments.candidate, symbol) if arguments.candidate else None
    except (FramePlanError, OSError, ValueError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    print(f"{symbol}: {assembly.relative_to(ROOT) if assembly.is_relative_to(ROOT) else assembly}")
    print("\n".join(render_block(reference, candidate)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
