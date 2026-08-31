#!/usr/bin/env python3
"""Extract the decompressed executable game payload from an owned ROM."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
import zlib
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
OVERLAYS_FILE = ROOT / "config" / "overlays.json"
OFFSET_XOR = 0x8039CCCA


def load_game_layouts() -> dict[str, dict[str, int]]:
    config = json.loads(OVERLAYS_FILE.read_text(encoding="utf-8"))
    profiles = config["overlays"]["game"]["profiles"]
    return {
        profile: {key: int(value, 0) for key, value in layout.items() if key != "sha1"}
        for profile, layout in profiles.items()
    }


RZIP_LAYOUTS = load_game_layouts()


def decompress_chunk(data: bytes) -> bytes:
    if len(data) < 5:
        raise ValueError("RZIP chunk is too short")
    return zlib.decompress(data[4:], wbits=-15)


def code_chunk_offsets(payload: bytes) -> list[int]:
    offsets: list[int] = []
    for index in range(1, len(payload) // 4):
        encoded = struct.unpack_from(">I", payload, index * 4)[0]
        if encoded == 0:
            break
        offsets.append(encoded ^ OFFSET_XOR)
    if len(offsets) < 2:
        raise ValueError("RZIP code offset table has fewer than two entries")
    return offsets


def extract_code(rom: bytes, profile: str) -> bytes:
    layout = RZIP_LAYOUTS[profile]
    payload = rom[layout["start"] : layout["end"]]
    if len(payload) != layout["end"] - layout["start"]:
        raise ValueError("ROM does not contain the complete RZIP game payload")
    offsets = code_chunk_offsets(payload)
    if offsets[-1] != layout["code_end"]:
        raise ValueError("RZIP code offset table does not end at the configured code boundary")
    return b"".join(
        decompress_chunk(payload[start:end]) for start, end in zip(offsets, offsets[1:])
    )


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("profile", choices=tuple(RZIP_LAYOUTS))
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()

    rom_path = ROOT / "roms" / f"baserom.{args.profile}.z64"
    if not rom_path.is_file():
        parser.error(f"ROM does not exist: {rom_path}; run ./conker setup first")
    code = extract_code(rom_path.read_bytes(), args.profile)
    output = args.output if args.output.is_absolute() else ROOT / args.output
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(code)
    try:
        display_path = output.relative_to(ROOT)
    except ValueError:
        display_path = output
    print(f"Extracted {len(code)} bytes to {display_path}")
    print(f"SHA-1: {hashlib.sha1(code).hexdigest()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
