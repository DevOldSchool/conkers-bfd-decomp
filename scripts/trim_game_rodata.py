#!/usr/bin/env python3
"""Trim a GAME object's .rodata to its reviewed size, as the original link packed it.

IDO's as1 (5.3 and 7.1, as built by decompals ido-static-recomp) aligns .rodata to
16 bytes and pads its size to 16. Conker's GAME data image instead packs each
object's .rodata on a 4-byte boundary directly after the previous object's:
game_1C02A0's constants start at 0x800A8194, where game_1BFDD0's end. The
packing came from a step after assembly, so the build reproduces it here.

A whole-object `.rodata` placement in config/game/us-rodata.ld asserts the
section's exact size. This tool sets the object's .rodata size to that value
and its alignment to 4. It refuses unless the removed tail is zero and holds
no symbol or relocation, so only assembler padding is dropped.

Usage:
  trim_game_rodata.py OBJECT      trim OBJECT in place if a placement names it
  trim_game_rodata.py --list      print the object names that have a placement
"""

from __future__ import annotations

import argparse
from pathlib import Path
import re
import struct
import sys

ROOT = Path(__file__).resolve().parent.parent
SCRIPT = ROOT / "config/game/us-rodata.ld"


def reviewed_sizes(text: str) -> dict[str, int]:
    """Map object file name to the asserted size of its whole-.rodata placement."""
    sections = dict(re.findall(
        r"(\.game_rodata_\w+)\s+0x[0-9A-Fa-f]+\s+\((?:INFO|NOLOAD)\)\s*:\s*"
        r"(?:SUBALIGN\(\d+\)\s*)?\{\s*\*(\w+\.o)\(\.rodata\);?\s*\}", text))
    sizes: dict[str, int] = {}
    for name, value in re.findall(r"ASSERT\(SIZEOF\((\.game_rodata_\w+)\)\s*==\s*(0x[0-9A-Fa-f]+|\d+)", text):
        if name in sections:
            sizes[sections[name]] = int(value, 0)
    return sizes


def trim_rodata(data: bytes, size: int) -> bytes | None:
    """Return the object with .rodata set to `size` bytes, or None if already that size."""
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
    if rodata[5] == size and rodata[8] == 4:
        return None
    if size > rodata[5] or size % 4 or size <= 0:
        raise ValueError(f".rodata is 0x{rodata[5]:X} bytes; cannot trim to 0x{size:X}")
    if any(data[rodata[4] + size:rodata[4] + rodata[5]]):
        raise ValueError(f".rodata tail beyond 0x{size:X} is not zero")
    for header in headers:
        if header[1] == 2:  # SHT_SYMTAB
            for offset in range(header[4], header[4] + header[5], 16):
                _, value, _, _, _, shndx = struct.unpack_from(">IIIBBH", data, offset)
                if shndx == index and value > size:
                    raise ValueError(f".rodata symbol at 0x{value:X} beyond 0x{size:X}")
        if header[1] in (9, 4) and header[7] == index:  # REL/RELA applied to .rodata
            step = 8 if header[1] == 9 else 12
            for offset in range(header[4], header[4] + header[5], step):
                if struct.unpack_from(">I", data, offset)[0] >= size:
                    raise ValueError(f".rodata relocation beyond 0x{size:X}")
    result = bytearray(data)
    rodata[5], rodata[8] = size, 4
    struct.pack_into(">10I", result, shoff + index * shentsize, *rodata)
    return bytes(result)


def trim_object(path: Path, name: str | None = None) -> None:
    """Trim the object at path in place if a placement names it (default: its file name)."""
    size = reviewed_sizes(SCRIPT.read_text()).get(name or path.name)
    if size is None:
        return
    trimmed = trim_rodata(path.read_bytes(), size)
    if trimmed is not None:
        path.write_bytes(trimmed)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("object", nargs="?", type=Path)
    parser.add_argument("--list", action="store_true")
    arguments = parser.parse_args()
    sizes = reviewed_sizes(SCRIPT.read_text())
    if arguments.list:
        print(" ".join(sorted(sizes)))
        return 0
    if arguments.object is None:
        parser.error("an object or --list is required")
    try:
        trim_object(arguments.object)
    except ValueError as error:
        print(f"error: {arguments.object}: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
