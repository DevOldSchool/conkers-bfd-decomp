#!/usr/bin/env python3
"""Verify VI private storage mapping, original BSS extent and linked US code."""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parent.parent
VI_VRAM = 0x80036DD0
VI_SIZE = 0x1070
BSS_VRAM = 0x8002D4B0
BSS_SIZE = 0x16690
TEXT_VRAM = 0x800034E0
TEXT_ROM = 0x34E0
TEXT_SIZE = 0x310


def linked_text(elf: bytes) -> bytes:
    def checked(offset: int, size: int, what: str) -> bytes:
        if offset < 0 or size < 0 or offset + size > len(elf):
            raise ValueError(f"truncated {what}")
        return elf[offset:offset + size]

    h = struct.unpack(">16sHHIIIIIHHHHHH", checked(0, 52, "ELF header"))
    if h[0][:7] != b"\x7fELF\x01\x02\x01" or h[1:4] != (2, 8, 1) or h[8] != 52:
        raise ValueError("expected ELF32 big-endian MIPS executable")
    offset, width, count, strings_index = h[6], h[11], h[12], h[13]
    if offset < 52 or width != 40 or count == 0 or not 0 < strings_index < count:
        raise ValueError("unsupported ELF section table")
    checked(offset, count * width, "ELF section table")
    sections = [struct.unpack_from(">10I", elf, offset + i * width) for i in range(count)]
    st = sections[strings_index]
    if st[1] != 3:
        raise ValueError("invalid section-name string table")
    names = checked(st[4], st[5], "ELF section names")
    selected = {}
    for section in sections:
        start = section[0]
        end = names.find(b"\0", start)
        if start >= len(names) or end < start:
            raise ValueError("invalid ELF section name")
        try:
            name = names[start:end].decode("ascii")
        except UnicodeDecodeError as error:
            raise ValueError("invalid ELF section name") from error
        if name.startswith(".main_vi") and name != ".main_vi_bss":
            raise ValueError(f"unreviewed VI storage section: {name}")
        if name in (".main_vi_bss", ".main_bss", ".main"):
            if name in selected:
                raise ValueError(f"duplicate {name}")
            selected[name] = section
    if set(selected) != {".main_vi_bss", ".main_bss", ".main"}:
        raise ValueError("missing VI mapping, main BSS or code section")
    vi, bss, text = (selected[n] for n in (".main_vi_bss", ".main_bss", ".main"))
    if vi[1:4] != (1, 1, VI_VRAM) or vi[5] != VI_SIZE or vi[8] != 16:
        raise ValueError("VI mapping must be non-allocated writable zero-filled INFO PROGBITS at the reviewed address/extent")
    if any(checked(vi[4], vi[5], "VI zero-initialization payload")):
        raise ValueError("VI private storage must be zero-initialized")
    if bss[1:4] != (8, 3, BSS_VRAM) or bss[5] != BSS_SIZE:
        raise ValueError("original main BSS allocation changed")
    if not bss[3] <= vi[3] < vi[3] + vi[5] <= bss[3] + bss[5]:
        raise ValueError("VI storage is outside the original main BSS")
    relative = TEXT_VRAM - text[3]
    if text[1] != 1 or not text[2] & 2 or relative < 0 or relative + TEXT_SIZE > text[5]:
        raise ValueError("VI code is outside the allocated main code section")
    return checked(text[4] + relative, TEXT_SIZE, "linked VI code")


def verify_bytes(code: bytes, rom: bytes) -> None:
    if len(code) != TEXT_SIZE or TEXT_ROM + TEXT_SIZE > len(rom):
        raise ValueError("invalid VI code or ROM extent")
    if code != rom[TEXT_ROM:TEXT_ROM + TEXT_SIZE]:
        raise ValueError("linked VI code and storage addresses differ from the US ROM")


def verify(elf: Path, root: Path = ROOT) -> None:
    import rzip_archive

    code = linked_text(elf.read_bytes())
    metadata = json.loads((root / "config/roms.json").read_text())["profiles"]["us"]
    rom, _ = rzip_archive.normalize_rom((root / "roms/baserom.us.z64").read_bytes())
    if len(rom) != metadata["size_bytes"] or hashlib.sha1(rom).hexdigest() != metadata["sha1"]:
        raise ValueError("VI verification requires a checksum-validated US ROM")
    verify_bytes(code, rom)
    print(f"VI storage: 0x{VI_SIZE:X} INFO bytes at 0x{VI_VRAM:X}; original BSS preserved; {TEXT_SIZE} linked code bytes match US ROM")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("elf", type=Path)
    args = parser.parse_args()
    try:
        verify(args.elf)
    except (ValueError, OSError, KeyError, struct.error) as error:
        parser.exit(1, f"error: {error}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
