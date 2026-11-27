#!/usr/bin/env python3
"""Generate a linker layout that emits the GAME data image as link output.

The integrated build places reviewed GAME data as INFO output sections and
`link_game_data.py` overlays their payloads on preserved ROM bytes. This
prototype instead links the whole image: every reviewed placement inside the
image becomes an allocated output section at its address, and every range no
object owns yet becomes a gap section of LONG/BYTE data statements holding the
preserved ROM bytes (the equivalent of a splat `bin` subsegment). The image is
then `objcopy -O binary` of exactly those sections, in address order.

A placement whose emitted (compiler-padded) extent runs into the next
placement, or whose padding is not zero in the ROM, cannot be laid out
contiguously; it stays INFO and its bytes are covered by the surrounding gap.
The generator reports each one.

Outputs, under --output-dir:
  rodata.ld, sdk.ld  copies of the placement scripts with linked placements
                     changed from INFO to allocated sections
  gaps.ld            gap sections with the preserved bytes
  sections.args      objcopy `-j` arguments in address order
  layout.json        the resulting ranges and their provenance

Whole-object .rodata placements are already trimmed to their asserted size by
scripts/trim_game_rodata.py in the compile step, so they link back to back.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import sys

import link_game_data
import rom_span

ROOT = Path(__file__).resolve().parent.parent
SCRIPTS = {"rodata.ld": "config/game/us-rodata.ld", "sdk.ld": "config/game/us-sdk.ld"}


def layout(mappings: list[dict], original: bytes, base: int) -> tuple[list[dict], list[dict]]:
    """Choose the placements that can be linked back to back and the gaps between them.

    A linked section emits its compiler padding too, so the ROM must hold zeros
    there. Where it does not, the original link packed the next object inside
    what our object pads, and the placement stays INFO.
    """
    size = len(original)
    linked, kept_info = [], []
    for index, mapping in enumerate(mappings):
        emitted_end = mapping["start"] + mapping["emitted_size"]
        following = mappings[index + 1]["start"] if index + 1 < len(mappings) else base + size
        previous_end = linked[-1]["start"] + linked[-1]["emitted_size"] if linked else base
        padding = original[mapping["end"] - base:emitted_end - base]
        if emitted_end > following or mapping["start"] < previous_end or any(padding) \
                or emitted_end > base + size:
            kept_info.append(mapping)
        else:
            linked.append(mapping)
    ranges, cursor = [], base
    for mapping in linked:
        if cursor < mapping["start"]:
            ranges.append({"kind": "gap", "start": cursor, "end": mapping["start"]})
        end = mapping["start"] + mapping["emitted_size"]
        ranges.append({"kind": "linked", "start": mapping["start"], "end": end,
                       "output": mapping["output"], "input_selector": mapping["input_selector"]})
        cursor = end
    if cursor < base + size:
        ranges.append({"kind": "gap", "start": cursor, "end": base + size})
    return ranges, kept_info


def gap_section(name: str, start: int, payload: bytes) -> str:
    lines = [f"    {name} 0x{start:08X} : {{"]
    offset = 0
    # Word statements only from a word-aligned address; bytes elsewhere.
    while offset < len(payload) and (start + offset) % 4:
        lines.append(f"        BYTE(0x{payload[offset]:02X})")
        offset += 1
    while offset + 4 <= len(payload):
        lines.append(f"        LONG(0x{int.from_bytes(payload[offset:offset + 4], 'big'):08X})")
        offset += 4
    while offset < len(payload):
        lines.append(f"        BYTE(0x{payload[offset]:02X})")
        offset += 1
    lines.append("    }")
    return "\n".join(lines)


def allocate(text: str, outputs: set[str]) -> tuple[str, int]:
    """Drop the INFO type from the linked placements' output section headers."""
    count = 0

    def replace(match: re.Match) -> str:
        nonlocal count
        if match[1] not in outputs:
            return match[0]
        count += 1
        return f"{match[1]} {match[2]} :"

    pattern = re.compile(r"(\.(?:game_rodata|sdk)_\w+)\s+(0x[0-9A-Fa-f]+)\s+\(INFO\)\s*:")
    return pattern.sub(replace, text), count


def generate(output_dir: Path, root: Path = ROOT) -> dict:
    original, base, digest = rom_span.game_data(root)
    mappings = link_game_data.placements(root, base, len(original))
    output_dir.mkdir(parents=True, exist_ok=True)
    ranges, kept_info = layout(mappings, original, base)
    outputs = {r["output"] for r in ranges if r["kind"] == "linked"}

    converted = 0
    for name, source in SCRIPTS.items():
        text, count = allocate((root / source).read_text(), outputs)
        converted += count
        (output_dir / name).write_text(text)
    if converted != len(outputs):
        raise ValueError(f"converted {converted} placement headers, expected {len(outputs)}")

    sections, gaps = [], ["/* Generated by scripts/game_data_link.py; do not edit. */", "SECTIONS", "{"]
    for item in ranges:
        if item["kind"] == "gap":
            item["output"] = f".game_data_gap_{item['start']:08X}"
            payload = original[item["start"] - base:item["end"] - base]
            gaps.append(gap_section(item["output"], item["start"], payload))
        sections.append(item["output"])
    gaps.append("}")
    (output_dir / "gaps.ld").write_text("\n".join(gaps) + "\n")
    (output_dir / "sections.args").write_text("".join(f"-j {name}\n" for name in sections))

    linked_bytes = sum(r["end"] - r["start"] for r in ranges if r["kind"] == "linked")
    summary = {
        "rom_sha1": digest, "vram_start": base, "size": len(original),
        "linked_sections": len(outputs), "linked_bytes": linked_bytes,
        "gap_sections": sum(r["kind"] == "gap" for r in ranges),
        "gap_bytes": len(original) - linked_bytes,
        "kept_info": [m["output"] for m in kept_info],
        "ranges": ranges,
    }
    (output_dir / "layout.json").write_text(json.dumps(summary, indent=2) + "\n")
    return summary


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--output-dir", type=Path, required=True)
    arguments = parser.parse_args()
    try:
        summary = generate(arguments.output_dir)
    except (ValueError, OSError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    print(f"{arguments.output_dir}: {summary['linked_sections']} linked sections "
          f"({summary['linked_bytes']} bytes, padding included), {summary['gap_sections']} gap sections "
          f"({summary['gap_bytes']} bytes); {len(summary['kept_info'])} placements kept INFO")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
