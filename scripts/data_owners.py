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

Reported extents still need review: the objects, their types and any
unreferenced bytes inside the extent come from reading the unit's code.
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
# .data occupies the image below this address and .rodata above it.
RODATA_SWEEP_START = 0x80092000
PLACEMENT_SCRIPTS = ("config/game/us-rodata.ld", "config/game/us-sdk.ld")
REFERENCE = re.compile(r"%lo\(D_([0-9A-F]{8})(?: \+ 0x([0-9A-F]+))?\)")


@dataclass
class Extent:
    unit: int
    first: int
    last: int
    start: int | None
    end: int | None
    exclusive: bool
    split: bool

    @property
    def fixed(self) -> bool:
        return self.start is not None and self.end is not None and self.exclusive and not self.split


def align16(value: int) -> int:
    return (value + 15) & ~15


def references(asm_dir: Path = ASM_DIR) -> dict[int, set[int]]:
    """Map each referenced GAME data address to the code units that reference it."""
    result: dict[int, set[int]] = {}
    for path in asm_dir.glob("*.s"):
        unit = int(path.stem, 16)
        for match in REFERENCE.finditer(path.read_text()):
            address = int(match[1], 16) + int(match[2] or "0", 16)
            if GAME_DATA_START <= address < GAME_DATA_END:
                result.setdefault(address, set()).add(unit)
    return result


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


def data_extents(refs: dict[int, set[int]]) -> list[Extent]:
    """Group the .data sweep by owning unit and decide which extents are fixed."""
    addresses = sorted(a for a in refs if a < RODATA_SWEEP_START)
    owners = owner_chain(refs, addresses)
    ordered = sorted(owners)
    groups: list[list[int]] = []  # [unit, first, last]
    for address in ordered:
        unit = owners[address]
        if groups and groups[-1][0] == unit:
            groups[-1][2] = address
        else:
            groups.append([unit, address, address])
    seen: dict[int, int] = {}
    for unit, _, _ in groups:
        seen[unit] = seen.get(unit, 0) + 1
    extents = []
    for index, (unit, first, last) in enumerate(groups):
        previous_last = groups[index - 1][2] if index else None
        following = groups[index + 1][1] if index + 1 < len(groups) else None
        start = first if previous_last is not None and align16(previous_last + 1) == first else None
        end = following if following is not None and align16(last + 1) == following else None
        bound = following if following is not None else last + 1
        exclusive = all(refs[a] == {unit} for a in addresses if first <= a < bound)
        extents.append(Extent(unit, first, last, start, end, exclusive, seen[unit] > 1))
    return extents


def placed_ranges(root: Path = ROOT) -> list[tuple[int, int, str]]:
    ranges = []
    for path in PLACEMENT_SCRIPTS:
        for mapping in data_boundaries.external_mappings((root / path).read_text(), path):
            ranges.append((mapping["start"], mapping["start"] + mapping["emitted_size"], mapping["output"]))
    return sorted(ranges)


def report(root: Path = ROOT) -> list[dict]:
    units = {offset: name for offset, kind, name in project_state.mapped_subsegments("us", "game")
             if kind == "c" and name}
    placed = placed_ranges(root)
    rows = []
    for extent in data_extents(references(root / "reference/game/us/asm")):
        name = units.get(extent.unit)
        if name is None:
            continue
        low = extent.start if extent.start is not None else extent.first
        high = extent.end if extent.end is not None else extent.last + 1
        overlapping = [output for start, end, output in placed if start < high and end > low]
        if extent.split:
            status = "split"
        elif not extent.exclusive:
            status = "shared"
        elif extent.start is None:
            status = "start-ambiguous"
        elif extent.end is None:
            status = "end-ambiguous"
        elif overlapping:
            status = "placed"
        else:
            status = "ready"
        rows.append({
            "unit": name.rsplit("/", 1)[-1], "source": f"src/{name}.c",
            "matched": name.startswith("done/"), "status": status,
            "start": f"0x{low:08X}", "end": f"0x{high:08X}", "size": high - low,
            "placements": overlapping,
        })
    return rows


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--status", action="append",
                        help="only rows with this status (ready, placed, start-ambiguous, "
                             "end-ambiguous, shared, split); repeatable")
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
    for row in rows:
        print(f"{row['status']:16s} {row['start']}-{row['end']} {row['size']:#7x} "
              f"{'matched' if row['matched'] else 'partial':8s} {row['source']}")
    counts: dict[str, int] = {}
    for row in rows:
        counts[row["status"]] = counts.get(row["status"], 0) + 1
    print("; ".join(f"{count} {status}" for status, count in sorted(counts.items())))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
