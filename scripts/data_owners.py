#!/usr/bin/env python3
"""Find GAME units whose initialized .data extent the reference code pins down.

The GAME data image holds every object's .data in link order, then every
object's .rodata in the same order. Each data address the reference GAME code
references is attributed to one code unit by a longest order-preserving chain
over unit offsets (one chain per section sweep); addresses that break the order
are tables shared with other units.

A unit's .data extent is fixed when IDO's 16-byte object alignment leaves no
choice:
- start: the first 16-byte boundary after the previous unit's last referenced
  address is this unit's first referenced address;
- end: the first 16-byte boundary after this unit's last referenced address is
  the next unit's first referenced address; and
- every referenced address in the extent is referenced only by this unit.

References are %lo operands of D_<address> and jtbl_<address>_game symbols,
plus raw `lui $r, (0xHHHH0000 >> 16)` bases used by a later `offset($r)`
before any label. The .data sweep ends where the last .data placement below
the first .rodata placement ends.

A fixed extent is `placed` when existing placements cover exactly its bounds,
`misplaced` when they overlap it otherwise, and `ready` when none overlaps.

Reported extents still need review. References from data pointers or from
other overlays are not seen, so a `ready` extent can still be shared; the
objects, their types and any unreferenced bytes inside the extent come from
reading the unit's code.
"""

from __future__ import annotations

import argparse
import bisect
from dataclasses import dataclass
import json
from pathlib import Path
import re
import sys

import data_boundaries
import project_state

ROOT = Path(__file__).resolve().parent.parent
ASM_DIR = ROOT / "reference/game/us/asm"
GAME_DATA_START, GAME_DATA_END = 0x80082B20, 0x800B0DC0
PLACEMENT_SCRIPTS = ("config/game/us-rodata.ld", "config/game/us-sdk.ld")
# %lo operands of address-named symbols: D_<address> and jtbl_<address>_game.
REFERENCE = re.compile(r"%lo\((?:D_([0-9A-F]{8})|jtbl_([0-9A-F]{8})_game)(?: \+ 0x([0-9A-F]+))?\)")
# A raw upper half, used by a later load, store or addiu as `offset($reg)`.
# Delay-slot instructions carry one extra leading space.
INSTRUCTION = re.compile(r"\*/  ( ?)([a-z0-9.]+)(?:\s+(.*))?$")
RAW_BASE = re.compile(r"(\$\w+), \((0x[0-9A-F]{4}0000) >> 16\)$")
OFFSET_USE = re.compile(r"(-?0x[0-9A-F]+|\d+)\((\$\w+)\)$|^\$\w+, (\$\w+), (-?0x[0-9A-F]+|\d+)$")
STORES = {"sb", "sh", "sw", "swl", "swr", "swc1", "sdc1"}
RAW_BASE_WINDOW = 16


@dataclass
class Extent:
    unit: int
    first: int
    last: int
    start: int | None
    end: int | None
    exclusive: bool

    @property
    def fixed(self) -> bool:
        return self.start is not None and self.end is not None and self.exclusive


def align16(value: int) -> int:
    return (value + 15) & ~15


def raw_base_references(lines: list[str]) -> list[int]:
    """Addresses formed from `lui $r, (0xHHHH0000 >> 16)` and a later `offset($r)`.

    The base stays live until an instruction writes $r, except in the delay
    slot of a branch-likely, which runs only when the branch is taken.
    """
    parsed = [INSTRUCTION.search(line) for line in lines]
    addresses = []
    for index, match in enumerate(parsed):
        if match is None or match[2] != "lui":
            continue
        base = RAW_BASE.search(match[3] or "")
        if base is None:
            continue
        register, high = base[1], int(base[2], 16)
        for offset in range(index + 1, min(index + 1 + RAW_BASE_WINDOW, len(parsed))):
            current = parsed[offset]
            if current is None:
                break
            operation, operands = current[2], (current[3] or "").strip()
            use = OFFSET_USE.search(operands)
            if use and use[3] and operation != "addiu":
                use = None
            if use and (use[2] or use[3]) == register:
                addresses.append(high + int(use[1] or use[4], 0))
            previous = parsed[offset - 1]
            likely_slot = (current[1] and previous is not None and previous[2].startswith("b")
                           and previous[2].endswith("l"))
            writes = operands.split(",")[0].strip() == register and operation not in STORES \
                and not operation.startswith("b")
            if writes and not likely_slot:
                break
    return addresses


def references(asm_dir: Path = ASM_DIR) -> dict[int, set[int]]:
    """Map each referenced GAME data address to the code units that reference it."""
    result: dict[int, set[int]] = {}
    for path in asm_dir.glob("*.s"):
        unit = int(path.stem, 16)
        text = path.read_text()
        addresses = [int(match[1] or match[2], 16) + int(match[3] or "0", 16)
                     for match in REFERENCE.finditer(text)]
        addresses += raw_base_references(text.splitlines())
        for address in addresses:
            if GAME_DATA_START <= address < GAME_DATA_END:
                result.setdefault(address, set()).add(unit)
    return result


def rodata_sweep_start(root: Path = ROOT) -> int:
    """End of the .data sweep: the last .data placement below the first .rodata placement."""
    mappings = [mapping for path in PLACEMENT_SCRIPTS
                for mapping in data_boundaries.external_mappings((root / path).read_text(), path)]
    first_rodata = min(m["start"] for m in mappings if m["input"].startswith(".rodata"))
    return max(m["start"] + m["emitted_size"] for m in mappings
               if m["input"] == ".data" and m["start"] < first_rodata)


def owner_chain(refs: dict[int, set[int]], addresses: list[int]) -> dict[int, int]:
    """Longest non-decreasing chain of unit offsets, choosing one unit per address."""
    tails: list[int] = []
    tail_nodes: list[int] = []
    nodes: list[tuple[int, int]] = []
    previous: list[int | None] = []
    for address in addresses:
        # Descending candidates stop one address from extending its own chain.
        for unit in sorted(refs[address], reverse=True):
            index = bisect.bisect_right(tails, unit)
            node = len(nodes)
            nodes.append((address, unit))
            previous.append(tail_nodes[index - 1] if index else None)
            if index == len(tails):
                tails.append(unit)
                tail_nodes.append(node)
            else:
                tails[index] = unit
                tail_nodes[index] = node
    owners: dict[int, int] = {}
    node = tail_nodes[-1] if tail_nodes else None
    while node is not None:
        address, unit = nodes[node]
        owners.setdefault(address, unit)
        node = previous[node]
    return owners


def data_extents(refs: dict[int, set[int]], rodata_start: int) -> list[Extent]:
    """Group the .data sweep (below rodata_start) by owning unit and decide which extents are fixed.

    The chain is non-decreasing in address order, so each unit's chained
    addresses form one contiguous group.
    """
    addresses = sorted(a for a in refs if a < rodata_start)
    owners = owner_chain(refs, addresses)
    ordered = sorted(owners)
    groups: list[list[int]] = []  # [unit, first, last]
    for address in ordered:
        unit = owners[address]
        if groups and groups[-1][0] == unit:
            groups[-1][2] = address
        else:
            groups.append([unit, address, address])
    extents = []
    for index, (unit, first, last) in enumerate(groups):
        previous_last = groups[index - 1][2] if index else None
        following = groups[index + 1][1] if index + 1 < len(groups) else None
        start = first if previous_last is not None and align16(previous_last + 1) == first else None
        end = following if following is not None and align16(last + 1) == following else None
        bound = following if following is not None else last + 1
        exclusive = all(refs[a] == {unit} for a in addresses if first <= a < bound)
        extents.append(Extent(unit, first, last, start, end, exclusive))
    return extents


def placed_ranges(root: Path = ROOT) -> list[tuple[int, int, str]]:
    ranges = []
    for path in PLACEMENT_SCRIPTS:
        for mapping in data_boundaries.external_mappings((root / path).read_text(), path):
            ranges.append((mapping["start"], mapping["start"] + mapping["emitted_size"], mapping["output"]))
    return sorted(ranges)


def status(extent: Extent, placed: list[tuple[int, int, str]]) -> tuple[str, list[str]]:
    """Classify an extent; `placed` only when placements tile exactly its fixed bounds."""
    low = extent.start if extent.start is not None else extent.first
    high = extent.end if extent.end is not None else extent.last + 1
    overlapping = [(start, end, output) for start, end, output in placed if start < high and end > low]
    names = [output for _, _, output in overlapping]
    if not extent.exclusive:
        return "shared", names
    if extent.start is None:
        return "start-ambiguous", names
    if extent.end is None:
        return "end-ambiguous", names
    if not overlapping:
        return "ready", names
    cursor = low
    for start, end, _ in overlapping:
        if start != cursor:
            return "misplaced", names
        cursor = end
    return ("placed" if cursor == high else "misplaced"), names


def report(root: Path = ROOT) -> list[dict]:
    units = {offset: name for offset, kind, name in project_state.mapped_subsegments("us", "game")
             if kind == "c" and name}
    placed = placed_ranges(root)
    rows = []
    extents = data_extents(references(root / "reference/game/us/asm"), rodata_sweep_start(root))
    for extent in extents:
        name = units.get(extent.unit)
        if name is None:
            continue
        state, placements = status(extent, placed)
        rows.append({
            "unit": name.rsplit("/", 1)[-1], "source": f"src/{name}.c",
            "matched": name.startswith("done/"), "status": state,
            # Bounds are null unless the alignment rule fixes them.
            "start": None if extent.start is None else f"0x{extent.start:08X}",
            "end": None if extent.end is None else f"0x{extent.end:08X}",
            "first_reference": f"0x{extent.first:08X}", "last_reference": f"0x{extent.last:08X}",
            "placements": placements,
        })
    return rows


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--status", action="append",
                        help="only rows with this status (ready, placed, misplaced, "
                             "start-ambiguous, end-ambiguous, shared); repeatable")
    parser.add_argument("--matched", action="store_true", help="only fully matched units")
    parser.add_argument("--json", action="store_true")
    arguments = parser.parse_args()
    if not (ROOT / "reference/game/us/asm").is_dir():
        print("error: missing reference/game/us/asm; run ./conker _prepare-reference --profile us",
              file=sys.stderr)
        return 1
    rows = report()
    if arguments.status:
        rows = [row for row in rows if row["status"] in arguments.status]
    if arguments.matched:
        rows = [row for row in rows if row["matched"]]
    if arguments.json:
        print(json.dumps(rows, indent=2))
        return 0
    print("status           start      end        references             unit")
    for row in rows:
        print(f"{row['status']:16s} {row['start'] or '?':10s} {row['end'] or '?':10s} "
              f"{row['first_reference']}-{row['last_reference']} "
              f"{'matched' if row['matched'] else 'partial':8s} {row['source']}")
    counts: dict[str, int] = {}
    for row in rows:
        counts[row["status"]] = counts.get(row["status"], 0) + 1
    print("; ".join(f"{count} {status}" for status, count in sorted(counts.items())))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
