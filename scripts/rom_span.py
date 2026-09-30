"""Independent, checksum-validated US CPU-code span evidence."""
from __future__ import annotations

import hashlib
import json
import re
from pathlib import Path

import rzip_archive
import yaml


def main_code(root: Path) -> tuple[bytes, int, str]:
    """Return only the main CPU interval, excluding the boot blob and RSP text."""
    metadata = json.loads((root / "config/roms.json").read_text())["profiles"]["us"]
    rom, _ = rzip_archive.normalize_rom((root / "roms/baserom.us.z64").read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    if digest != metadata["sha1"] or len(rom) != metadata["size_bytes"]:
        raise ValueError("span verification requires a checksum-validated US ROM")
    profile = yaml.safe_load((root / "config/reference/us.yaml").read_text())
    entry = next(segment for segment in profile["segments"]
                 if isinstance(segment, dict) and segment.get("name") == "entry")
    start, base = entry["start"], entry["vram"]
    rsp = json.loads((root / "config/rsp/us.json").read_text())
    if rsp["rom_sha1"] != digest:
        raise ValueError("main CPU endpoint requires the same checksum-validated RSP layout")
    end = min(payload["start"] for payload in rsp["payloads"] if payload["kind"] == "code")
    if not 0 <= start < end <= len(rom):
        raise ValueError("invalid main CPU interval")
    return rom[start:end], base, digest


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
