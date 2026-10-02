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


def debugger_image(root: Path) -> tuple[bytes, bytes, int, int, str]:
    """Return the loader-proven US debugger text and loaded data intervals.

    The independent reference map describes the complete raw image, including
    privileged TLB text and its padding. These intervals are image boundaries,
    not evidence for original C source ownership or a data/rodata split.
    """
    metadata = json.loads((root / "config/roms.json").read_text())["profiles"]["us"]
    rom, _ = rzip_archive.normalize_rom((root / "roms/baserom.us.z64").read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    if digest != metadata["sha1"] or len(rom) != metadata["size_bytes"]:
        raise ValueError("span verification requires a checksum-validated US ROM")
    segments = yaml.safe_load((root / "config/reference/us.yaml").read_text())["segments"]
    matches = [(index, segment) for index, segment in enumerate(segments)
               if isinstance(segment, dict) and segment.get("name") == "debugger"]
    if len(matches) != 1 or matches[0][0] + 1 >= len(segments):
        raise ValueError("debugger reference requires one bounded raw image")
    index, segment = matches[0]
    following = segments[index + 1]
    end = following.get("start") if isinstance(following, dict) else following[0]
    parts = segment.get("subsegments", [])
    if (segment.get("type") != "code" or segment.get("align") != 8
            or len(parts) != 2 or any(not isinstance(part, list) or len(part) < 2 for part in parts)
            or parts[0][:2] != [0x19EA88, "asm"] or parts[1][:2] != [0x1A2178, "data"]
            or (segment.get("start"), segment.get("vram"), end)
            != (0x19EA88, 0x16000000, 0x1A33E8) or end > len(rom)):
        raise ValueError("debugger reference differs from the reviewed loader image")
    start, split, base = segment["start"], parts[1][0], segment["vram"]
    return rom[start:split], rom[split:end], base, base + split - start, digest


def debugger_code(root: Path) -> tuple[bytes, int, str]:
    code, _, base, _, digest = debugger_image(root)
    return code, base, digest


def code_image(root: Path, overlay: str) -> tuple[bytes, int, str]:
    """Select independent ROM bytes without treating other overlays as main."""
    readers = {"main": main_code, "game": game_code, "debugger": debugger_code}
    if overlay not in readers:
        raise ValueError(f"unsupported US code overlay: {overlay}")
    return readers[overlay](root)


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
