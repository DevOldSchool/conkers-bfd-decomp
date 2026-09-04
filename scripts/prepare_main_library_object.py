#!/usr/bin/env python3
"""Rebase data relocations for code executed through the main runtime alias."""

from __future__ import annotations

import argparse
import os
from pathlib import Path
import struct
import tempfile


class PreparationError(ValueError):
    pass


def rebase_code_pointers(data: bytes, delta: int, expected_relocations: int) -> bytes:
    """Adjust R_MIPS_32 addends pointing from allocated data to executable code.

    Conker links main code at 0x80000000 and executes it at 0x10000000.
    JAL instructions encode only low address bits, but compiler jump tables
    contain full code pointers. Their REL addends need the runtime alias delta.
    Neither instructions nor relocation records are rewritten.
    """
    if len(data) < 52 or data[:7] != b"\x7fELF\x01\x02\x01":
        raise PreparationError("expected a big-endian ELF32 object")
    kind, machine = struct.unpack_from(">HH", data, 16)
    if (kind, machine) != (1, 8):
        raise PreparationError("expected a relocatable MIPS object")
    if expected_relocations <= 0:
        raise PreparationError("expected relocation count must be positive")
    table = struct.unpack_from(">I", data, 32)[0]
    entry_size, count = struct.unpack_from(">HH", data, 46)
    if entry_size != 40 or not count or table + count * entry_size > len(data):
        raise PreparationError("invalid ELF section table")
    sections = [struct.unpack_from(">10I", data, table + i * 40) for i in range(count)]

    def contents(section: tuple[int, ...]) -> tuple[int, int]:
        start, size = section[4:6]
        if start + size > len(data):
            raise PreparationError("section extends beyond object")
        return start, size

    replacements: dict[int, int] = {}
    for relocations in sections:
        if relocations[1] not in (4, 9):  # SHT_RELA / SHT_REL
            continue
        symbol_index, target_index = relocations[6:8]
        if not (symbol_index < count and target_index < count):
            raise PreparationError("invalid relocation section links")
        target = sections[target_index]
        # Only allocated non-executable data. Debug, PDR and text remain intact.
        if not target[2] & 2 or target[2] & 4:
            continue
        if target[1] != 1 or relocations[1] != 9 or relocations[9] != 8:
            raise PreparationError("unsupported allocated-data relocation format")
        symbols = sections[symbol_index]
        if symbols[1] != 2 or symbols[9] != 16:
            raise PreparationError("invalid relocation symbol table")
        sym_start, sym_size = contents(symbols)
        target_start, target_size = contents(target)
        rel_start, rel_size = contents(relocations)
        if sym_size % 16 or rel_size % 8:
            raise PreparationError("truncated relocation or symbol entry")
        for offset in range(rel_start, rel_start + rel_size, 8):
            location, info = struct.unpack_from(">II", data, offset)
            symbol = info >> 8
            if symbol >= sym_size // 16:
                raise PreparationError("relocation symbol is out of bounds")
            defining_section = struct.unpack_from(">H", data, sym_start + symbol * 16 + 14)[0]
            if defining_section >= count or not sections[defining_section][2] & 4:
                continue
            if info & 0xFF != 2:
                raise PreparationError("code pointer must use R_MIPS_32")
            if location % 4 or location + 4 > target_size:
                raise PreparationError("unaligned or out-of-bounds code pointer")
            position = target_start + location
            if position in replacements:
                raise PreparationError("duplicate code-pointer relocation")
            value = struct.unpack_from(">I", data, position)[0]
            replacements[position] = (value + delta) & 0xFFFFFFFF
    if len(replacements) != expected_relocations:
        raise PreparationError(
            f"expected {expected_relocations} code-pointer relocations, found {len(replacements)}"
        )
    result = bytearray(data)
    for position, value in replacements.items():
        struct.pack_into(">I", result, position, value)
    return bytes(result)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--delta", type=lambda value: int(value, 0), required=True)
    parser.add_argument("--expected-relocations", type=int, required=True)
    args = parser.parse_args()
    if args.source.resolve() == args.output.resolve():
        parser.error("source and staged output must be different files")
    try:
        result = rebase_code_pointers(args.source.read_bytes(), args.delta, args.expected_relocations)
    except PreparationError as error:
        parser.error(str(error))
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile(dir=args.output.parent, delete=False) as temporary:
        temporary.write(result)
        temporary_name = temporary.name
    try:
        os.replace(temporary_name, args.output)
    finally:
        if os.path.exists(temporary_name):
            os.unlink(temporary_name)


if __name__ == "__main__":
    main()
