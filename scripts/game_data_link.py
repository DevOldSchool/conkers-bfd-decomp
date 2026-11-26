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
  objects.args       the link's object list, with trimmed copies substituted
  integrated.ld      the integrated script, selecting the trimmed copies
  objects/           .rodata-trimmed copies of reviewed source objects
  layout.json        the resulting ranges and their provenance

IDO objects here align .rodata to 16 bytes and pad its size to 16, but the
original link packed each object's .rodata on a 4-byte boundary directly after
the previous one (for example game_1C02A0's constants start at 0x800A8194,
where game_1BFDD0's end). For the data link, each reviewed whole-object
.rodata placement uses a copy of its object whose .rodata is trimmed to the
reviewed payload with 4-byte alignment. Trimming is refused unless the
removed tail is zero and holds no symbol or relocation.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import struct
import sys

import link_game_data
import rom_span

ROOT = Path(__file__).resolve().parent.parent
INTEGRATED_SCRIPT = "build/game-integrated/us/conker.game.us.integrated.ld"
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


def trim_rodata(data: bytes, size: int) -> bytes:
    """Return a big-endian ELF32 object whose .rodata is `size` bytes, 4-byte aligned."""
    if data[:6] != b"\x7fELF\x01\x02":
        raise ValueError("not a big-endian ELF32 object")
    shoff, = struct.unpack_from(">I", data, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from(">HHH", data, 0x2E)
    headers = [list(struct.unpack_from(">10I", data, shoff + i * shentsize)) for i in range(shnum)]
    strtab = headers[shstrndx]

    def name(header: list[int]) -> str:
        start = strtab[4] + header[0]
        return data[start:data.index(b"\0", start)].decode()

    index = next((i for i, h in enumerate(headers) if name(h) == ".rodata"), None)
    if index is None:
        raise ValueError("object has no .rodata")
    rodata = headers[index]
    if size > rodata[5] or size % 4:
        raise ValueError(f".rodata payload 0x{size:X} does not fit 0x{rodata[5]:X} on a word boundary")
    if any(data[rodata[4] + size:rodata[4] + rodata[5]]):
        raise ValueError(".rodata tail beyond the payload is not zero")
    for header in headers:
        if header[1] == 2:  # SHT_SYMTAB
            for offset in range(header[4], header[4] + header[5], 16):
                _, value, _, _, _, shndx = struct.unpack_from(">IIIBBH", data, offset)
                if shndx == index and value > size:
                    raise ValueError(".rodata symbol beyond the payload")
        if header[1] in (9, 4) and header[7] == index:  # REL/RELA targeting .rodata
            step = 8 if header[1] == 9 else 12
            for offset in range(header[4], header[4] + header[5], step):
                if struct.unpack_from(">I", data, offset)[0] >= size:
                    raise ValueError(".rodata relocation beyond the payload")
    result = bytearray(data)
    rodata[5], rodata[8] = size, 4
    struct.pack_into(">10I", result, shoff + index * shentsize, *rodata)
    return bytes(result)


def trim_objects(mappings: list[dict], objects: list[str], output_dir: Path, root: Path) -> list[str]:
    """Trim each reviewed whole-object .rodata placement; return the trimmed outputs."""
    by_name = {Path(path).name: path for path in objects}
    substitutes, trimmed = {}, []
    for mapping in mappings:
        match = re.fullmatch(r"\*(\w+\.o)\(\.rodata\)", mapping["input_selector"])
        size = mapping["end"] - mapping["start"]
        if not match or size == mapping["emitted_size"] or match[1] not in by_name:
            continue
        source = by_name[match[1]]
        target = (output_dir / "objects" / match[1]).resolve()
        target.parent.mkdir(parents=True, exist_ok=True)
        try:
            target.write_bytes(trim_rodata((root / source).read_bytes(), size))
        except ValueError as error:
            raise ValueError(f"{mapping['output']}: {error}") from None
        substitutes[source] = target.relative_to(root.resolve()).as_posix()
        mapping["emitted_size"] = size
        trimmed.append(mapping["output"])
    (output_dir / "objects.args").write_text("".join(substitutes.get(p, p) + "\n" for p in objects))
    # The integrated script selects objects by path; point it at the copies.
    text = (root / INTEGRATED_SCRIPT).read_text()
    for source, target in substitutes.items():
        text, count = re.subn(re.escape(source) + r"(?=\()", target, text)
        if not count:
            raise ValueError(f"{source}: not selected by {INTEGRATED_SCRIPT}")
    (output_dir / "integrated.ld").write_text(text)
    return trimmed


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


def allocate(text: str, outputs: set[str], trimmed: dict[str, int]) -> tuple[str, int]:
    """Drop the INFO type from the linked placements' output section headers."""
    count = 0
    for output, size in trimmed.items():
        text, found = re.subn(r"(ASSERT\(SIZEOF\(" + re.escape(output) + r"\)\s*==\s*)0x[0-9A-Fa-f]+",
                              lambda match: f"{match[1]}0x{size:X}", text)
        if found > 1:
            raise ValueError(f"{output}: more than one extent assertion")

    def replace(match: re.Match) -> str:
        nonlocal count
        if match[1] not in outputs:
            return match[0]
        count += 1
        return f"{match[1]} {match[2]} :"

    pattern = re.compile(r"(\.(?:game_rodata|sdk)_\w+)\s+(0x[0-9A-Fa-f]+)\s+\(INFO\)\s*:")
    return pattern.sub(replace, text), count


def generate(output_dir: Path, objects: list[str], root: Path = ROOT) -> dict:
    original, base, digest = rom_span.game_data(root)
    mappings = link_game_data.placements(root, base, len(original))
    output_dir.mkdir(parents=True, exist_ok=True)
    trimmed = trim_objects(mappings, objects, output_dir, root)
    ranges, kept_info = layout(mappings, original, base)
    outputs = {r["output"] for r in ranges if r["kind"] == "linked"}
    sizes = {m["output"]: m["emitted_size"] for m in mappings if m["output"] in trimmed}

    converted = 0
    for name, source in SCRIPTS.items():
        text, count = allocate((root / source).read_text(), outputs, sizes)
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
        "trimmed_rodata": trimmed,
        "kept_info": [m["output"] for m in kept_info],
        "ranges": ranges,
    }
    (output_dir / "layout.json").write_text(json.dumps(summary, indent=2) + "\n")
    return summary


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--output-dir", type=Path, required=True)
    parser.add_argument("--objects", type=Path, required=True,
                        help="file listing the integrated link's objects, one per line")
    arguments = parser.parse_args()
    try:
        objects = arguments.objects.read_text().split()
        summary = generate(arguments.output_dir, objects)
    except (ValueError, OSError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    print(f"{arguments.output_dir}: {summary['linked_sections']} linked sections "
          f"({summary['linked_bytes']} bytes, padding included), {summary['gap_sections']} gap sections "
          f"({summary['gap_bytes']} bytes); {len(summary['trimmed_rodata'])} .rodata objects trimmed; "
          f"{len(summary['kept_info'])} placements kept INFO")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
