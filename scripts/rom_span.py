"""Independent, checksum-validated US game-code span evidence."""
from __future__ import annotations

import hashlib
import json
import re
from pathlib import Path

import rzip_archive


def game_code(root: Path) -> tuple[bytes, int, str]:
    layout = json.loads((root / "config/rzip_layouts.json").read_text())["profiles"]["us"]
    rom, _ = rzip_archive.normalize_rom((root / layout["default_rom"]).read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError("span verification requires a checksum-validated US ROM")
    game = rzip_archive.parse_game_archive(
        rom[int(layout["game_start"], 0):int(layout["game_end"], 0)])
    return game.code, int(layout["game_vram"], 0), digest


def raw_span(assembly: str, start: int, size: int, code: bytes, base: int) -> bytes:
    rows = re.findall(r"/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})\s*\*/", assembly)
    if size <= 0 or size % 4 or len(rows) * 4 != size:
        raise ValueError("raw assembly does not cover the full registered span")
    if any(int(address, 16) != start + index * 4 for index, (address, _) in enumerate(rows)):
        raise ValueError("raw assembly addresses are not contiguous")
    payload = bytes.fromhex("".join(word for _, word in rows))
    offset = start - base
    if offset < 0 or code[offset:offset + size] != payload:
        raise ValueError("raw assembly bytes differ from the US ROM")
    return payload
