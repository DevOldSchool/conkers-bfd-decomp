#!/usr/bin/env python3
"""Verify the integrated main queue-thread table against the validated US ROM."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parent.parent
SECTION_NAME = ".main_rodata_init_2e50"
SECTION_VRAM = 0x8002C080
SECTION_SIZE = 0x20
ROM_START = 0x2C080


def external_payload(elf: bytes) -> bytes:
    def checked_slice(offset: int, size: int, description: str) -> bytes:
        if offset < 0 or size < 0 or offset + size > len(elf):
            raise ValueError(f"truncated {description}")
        return elf[offset:offset + size]

    header = struct.unpack(">16sHHIIIIIHHHHHH", checked_slice(0, 52, "ELF header"))
    if (header[0][:7] != b"\x7fELF\x01\x02\x01" or header[1:4] != (2, 8, 1)
            or header[8] != 52):
        raise ValueError("expected ELF32 big-endian MIPS executable")
    offset, entry_size, count, string_index = header[6], header[11], header[12], header[13]
    if offset < 52 or entry_size != 40 or count == 0 or not 0 < string_index < count:
        raise ValueError("unsupported ELF section table")
    checked_slice(offset, count * entry_size, "ELF section table")
    sections = [struct.unpack_from(">10I", elf, offset + index * entry_size)
                for index in range(count)]
    strings = sections[string_index]
    if strings[1] != 3:
        raise ValueError("invalid ELF section-name string table")
    names = checked_slice(strings[4], strings[5], "ELF section names")
    payload = None
    for section in sections:
        name_start = section[0]
        name_end = names.find(b"\0", name_start)
        if name_start >= len(names) or name_end < name_start:
            raise ValueError("invalid ELF section name")
        try:
            name = names[name_start:name_end].decode("ascii")
        except UnicodeDecodeError as error:
            raise ValueError("invalid ELF section name") from error
        if not name.startswith(".main_rodata"):
            continue
        if name != SECTION_NAME:
            raise ValueError(f"unreviewed external main section: {name}")
        if payload is not None:
            raise ValueError("duplicate external main table")
        if section[1] != 1 or section[2] != 0:
            raise ValueError(f"{name}: expected non-allocated read-only INFO PROGBITS")
        if (section[3], section[5]) != (SECTION_VRAM, SECTION_SIZE):
            raise ValueError(f"{name}: address or size differs from reviewed mapping")
        payload = checked_slice(section[4], section[5], "main table payload")
    if payload is None:
        raise ValueError("linked image has no reviewed external main table")
    return payload


def verify_bytes(linked: bytes, rom: bytes) -> None:
    if len(linked) != SECTION_SIZE:
        raise ValueError("main table dump has incorrect size")
    if ROM_START + SECTION_SIZE > len(rom):
        raise ValueError("main table is outside the US ROM")
    if linked != rom[ROM_START:ROM_START + SECTION_SIZE]:
        raise ValueError(f"main table differs from ROM at 0x{ROM_START:X}")


def verify(elf: Path, root: Path = ROOT) -> None:
    import rzip_archive

    linked = external_payload(elf.read_bytes())
    metadata = json.loads((root / "config/roms.json").read_text())["profiles"]["us"]
    rom, _ = rzip_archive.normalize_rom((root / "roms/baserom.us.z64").read_bytes())
    if hashlib.sha1(rom).hexdigest() != metadata["sha1"] or len(rom) != metadata["size_bytes"]:
        raise ValueError("main table verification requires a checksum-validated US ROM")
    verify_bytes(linked, rom)
    print(f"{SECTION_NAME}: {SECTION_SIZE} linked bytes at 0x{SECTION_VRAM:X} match US ROM data")


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
