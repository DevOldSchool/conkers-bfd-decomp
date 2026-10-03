#!/usr/bin/env python3
"""Verify linked debugger switch data against the checksum-validated US ROM."""

from __future__ import annotations

import argparse
from pathlib import Path
import struct

import rom_span


ROOT = Path(__file__).resolve().parent.parent
SECTION_NAME = ".debugger_rodata_1ad0"
SECTION_VRAM = 0x1600487C
SECTION_SIZE = 0xD0


def external_payload(elf: bytes) -> bytes:
    """Read only the reviewed non-allocated ELF32 MIPS PROGBITS section."""
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
        if not name.startswith(".debugger_rodata"):
            continue
        if name != SECTION_NAME:
            raise ValueError(f"unreviewed external debugger section: {name}")
        if payload is not None:
            raise ValueError("duplicate external debugger rodata section")
        # GNU ld INFO is non-allocated PROGBITS, not a separate ELF section type.
        if section[1] != 1 or section[2] != 0:
            raise ValueError(f"{name}: expected non-allocated read-only INFO PROGBITS")
        if (section[3], section[5]) != (SECTION_VRAM, SECTION_SIZE):
            raise ValueError(f"{name}: address or size differs from reviewed mapping")
        payload = checked_slice(section[4], section[5], "debugger rodata payload")
    if payload is None:
        raise ValueError("linked image has no reviewed external debugger rodata")
    return payload


def verify_bytes(linked: bytes, data: bytes, data_vram: int) -> None:
    if len(linked) != SECTION_SIZE:
        raise ValueError("debugger rodata dump has incorrect size")
    offset = SECTION_VRAM - data_vram
    if offset < 0 or offset + SECTION_SIZE > len(data):
        raise ValueError("debugger rodata is outside the ROM loaded-data interval")
    if linked != data[offset:offset + SECTION_SIZE]:
        raise ValueError(f"debugger rodata differs from ROM at 0x{SECTION_VRAM:X}")


def verify(elf: Path) -> None:
    linked = external_payload(elf.read_bytes())
    _, data, _, data_vram, _ = rom_span.debugger_image(ROOT)
    verify_bytes(linked, data, data_vram)
    print(f"{SECTION_NAME}: {SECTION_SIZE} linked bytes at 0x{SECTION_VRAM:X} match US ROM data")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("elf", type=Path)
    args = parser.parse_args()
    try:
        verify(args.elf)
    except (ValueError, OSError) as error:
        parser.exit(1, f"error: {error}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
