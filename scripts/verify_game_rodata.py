#!/usr/bin/env python3
"""Verify linked external game rodata against the checksum-validated US ROM."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess
import tempfile

import rzip_archive


ROOT = Path(__file__).resolve().parent.parent
SECTION = re.compile(
    r"^\s*\d+\s+(\.game_rodata_\w+)\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+"
)


def external_sections(headers: str) -> list[tuple[str, int, int]]:
    sections = []
    for line in headers.splitlines():
        match = SECTION.match(line)
        if match:
            sections.append((match[1], int(match[2], 16), int(match[3], 16)))
    if not sections:
        raise ValueError("linked image has no reviewed external game rodata")
    return sections


def payload_sizes(symbols: str) -> dict[str, int]:
    """Read explicit, absolute payload extents from the reviewed linker script."""
    result = {}
    for line in symbols.splitlines():
        fields = line.split()
        if len(fields) < 5 or "*ABS*" not in fields:
            continue
        symbol = fields[-1]
        if not re.fullmatch(r"__game_rodata_\w+_payload_size", symbol):
            continue
        section = "." + symbol[2:-len("_payload_size")]
        if section in result:
            raise ValueError(f"{section}: duplicate external rodata payload size")
        result[section] = int(fields[0], 16)
    return result


def verify_bytes(name: str, linked: bytes, size: int, vram: int,
                 data: bytes, data_vram: int, payload_size: int | None = None) -> None:
    offset = vram - data_vram
    if size <= 0 or len(linked) != size:
        raise ValueError(f"{name}: linked rodata size does not match its section")
    if offset < 0 or offset + size > len(data):
        raise ValueError(f"{name}: external rodata is outside the ROM game-data region")
    if payload_size is not None:
        # Only a reviewed, word-aligned payload followed by the object's
        # zero-filled 16-byte alignment may omit unrelated following ROM data.
        if (payload_size <= 0 or payload_size % 4 != 0
                or size != (payload_size + 15) & ~15):
            raise ValueError(f"{name}: invalid external rodata payload extent")
        if any(linked[payload_size:]):
            raise ValueError(f"{name}: external rodata alignment is not zero-filled")
        linked = linked[:payload_size]
        size = payload_size
    if linked != data[offset:offset + size]:
        raise ValueError(f"{name}: linked rodata differs from ROM at 0x{vram:X}")


def rom_game_data() -> tuple[bytes, int]:
    layout = json.loads((ROOT / "config/rzip_layouts.json").read_text())["profiles"]["us"]
    rom, _ = rzip_archive.normalize_rom((ROOT / layout["default_rom"]).read_bytes())
    if hashlib.sha1(rom).hexdigest() not in layout["normalized_sha1"]:
        raise ValueError("external game rodata verification requires a checksum-validated US ROM")
    game = rzip_archive.parse_game_archive(
        rom[int(layout["game_start"], 0):int(layout["game_end"], 0)]
    )
    return game.data, int(layout["game_data_vram"], 0)


def verify(elf: Path) -> None:
    headers = subprocess.check_output(["mips-linux-gnu-objdump", "-h", str(elf)], text=True)
    sizes = payload_sizes(subprocess.check_output(
        ["mips-linux-gnu-objdump", "-t", str(elf)], text=True
    ))
    sections = external_sections(headers)
    unknown = sizes.keys() - {name for name, _, _ in sections}
    if unknown:
        raise ValueError("payload extent has no external section: " + ", ".join(sorted(unknown)))
    data, data_vram = rom_game_data()
    with tempfile.TemporaryDirectory() as directory:
        for name, size, vram in sections:
            output = Path(directory) / "section.bin"
            subprocess.run([
                "mips-linux-gnu-objcopy", "--dump-section", f"{name}={output}",
                str(elf), str(Path(directory) / "copy.elf"),
            ], check=True)
            payload_size = sizes.get(name)
            verify_bytes(name, output.read_bytes(), size, vram, data, data_vram, payload_size)
            verified_size = size if payload_size is None else payload_size
            print(f"{name}: {verified_size} linked payload bytes at 0x{vram:X} match US ROM data")
            if verified_size != size:
                print(f"{name}: {size - verified_size} object-alignment bytes verified zero-filled")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("elf", type=Path)
    args = parser.parse_args()
    try:
        verify(args.elf)
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        parser.exit(1, f"error: {error}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
