#!/usr/bin/env python3
"""Read-only, bounded evidence for the remaining retail main entry questions.

Requires owned ignored ROMs. Outputs hashes and reference coordinates, never ROM
bytes. Candidate address suffixes and cross-version resemblance are navigation
only: this command does not register boundaries or change progress.
"""
from __future__ import annotations

import hashlib
import json
import struct
from pathlib import Path

try:
    from scripts.beta_index import load_game_image
    from scripts.rzip_archive import normalize_rom, parse_game_archive
except ModuleNotFoundError:
    from beta_index import load_game_image
    from rzip_archive import normalize_rom, parse_game_archive

ROOT = Path(__file__).resolve().parent.parent
CPU_ENDS = {"us": 0x290D0, "pal": 0x29400, "debug": 0xA4E0, "ects": 0x9DB0}
BSS_STARTS = {"us": 0x2D4B0, "pal": 0x2D810, "debug": 0xD2B0, "ects": 0xCAF0}
TARGETS = {
    "us": [0x38C0, 0x38E0, 0x390C, 0x39B0, 0x50A0, 0x51C8, 0x51E8, 0x5218, 0x5298, 0x52A0],
    "pal": [0x3950, 0x3970, 0x399C, 0x3A40, 0x5380, 0x547C, 0x549C, 0x54CC, 0x554C, 0x5554],
    "debug": [0x37D0, 0x37F0, 0x381C, 0x150171A0, 0x150172E0, 0x15017300],
    "ects": [0x35D0, 0x35F0, 0x361C, 0x150152A0, 0x150153C8, 0x150153E8],
}
RANGES = {
    "us": [("main", 0x38C0, 0x38E0), ("main", 0x38E0, 0x3920), ("main", 0x39B0, 0x39C0), ("main", 0x50A0, 0x5570)],
    "pal": [("main", 0x3950, 0x3970), ("main", 0x3970, 0x39B0), ("main", 0x3A40, 0x3A50), ("main", 0x5380, 0x5860)],
    "debug": [("main", 0x37D0, 0x37F0), ("main", 0x37F0, 0x38F0), ("game", 0x171A0, 0x17330)],
    "ects": [("main", 0x35D0, 0x35F0), ("main", 0x35F0, 0x36B0), ("game", 0x152A0, 0x15420)],
}


def sha1(data: bytes) -> str:
    return hashlib.sha1(data).hexdigest()


def words(data: bytes) -> tuple[int, ...]:
    if len(data) % 4:
        raise ValueError("word scan requires a complete aligned image")
    return struct.unpack(f">{len(data) // 4}I", data)


def direct_target(word: int, pc: int) -> int | None:
    if word >> 26 not in (2, 3):
        return None
    return ((pc + 4) & 0xF0000000) | ((word & 0x03FFFFFF) << 2)


def conditional_target(word: int, pc: int) -> int | None:
    opcode = word >> 26
    if opcode == 1 and (word >> 16) & 31 not in (0, 1, 2, 3, 16, 17, 18, 19):
        return None
    if opcode not in (1, 4, 5, 6, 7, 20, 21, 22, 23) and not (
        opcode == 17 and (word >> 21) & 31 == 8
    ):
        return None
    immediate = word & 0xFFFF
    if immediate & 0x8000:
        immediate -= 0x10000
    return pc + 4 + immediate * 4


def address_aliases(target: int) -> tuple[int, ...]:
    return (target,) if target >= 0x15000000 else (0x80000000 + target, 0x10000000 + target)


def scan_target(target: int, code_scopes: list, data_scopes: list) -> dict:
    aliases = address_aliases(target)
    result = {"aliases": [f"0x{x:08X}" for x in aliases], "direct": [], "low_half_candidates": [], "literal_pointers": []}
    for label, code, base in code_scopes:
        for index, word in enumerate(words(code)):
            pc = base + index * 4
            if direct_target(word, pc) in aliases:
                result["direct"].append({"scope": label, "address": f"0x{pc:08X}"})
            if word >> 26 in (8, 9, 13) and word & 0xFFFF == target & 0xFFFF:
                result["low_half_candidates"].append({"scope": label, "address": f"0x{pc:08X}"})
    for label, data, base in data_scopes:
        for index, word in enumerate(words(data)):
            if word in aliases:
                result["literal_pointers"].append({"scope": label, "address": f"0x{base + index * 4:08X}"})
    return result



def scan_main_range(start: int, end: int, code_scopes: list, data_scopes: list) -> dict:
    """Check a whole main range, including unlisted instruction-aligned entries."""
    def inside(address: int | None) -> bool:
        return address is not None and (address & 0xF0000000) in (0x10000000, 0x80000000) and start <= (address & 0x0FFFFFFF) < end

    result = {"direct_entries": [], "relative_crossings": [], "literal_pointers": []}
    for label, code, base in code_scopes:
        for index, word in enumerate(words(code)):
            pc = base + index * 4
            target = direct_target(word, pc)
            if inside(target):
                result["direct_entries"].append({"scope": label, "address": f"0x{pc:08X}", "target": f"0x{target:08X}"})
            target = conditional_target(word, pc)
            if target is not None and inside(pc) != inside(target):
                result["relative_crossings"].append({"scope": label, "address": f"0x{pc:08X}", "target": f"0x{target:08X}"})
    for label, data, base in data_scopes:
        for index, word in enumerate(words(data)):
            if inside(word):
                result["literal_pointers"].append({"scope": label, "address": f"0x{base + index * 4:08X}", "target": f"0x{word:08X}"})
    return result

def load_inputs() -> dict:
    result = {}
    for profile in ("us", "debug", "ects"):
        image = load_game_image(profile)
        raw = image.rom_path.read_bytes()
        result[profile] = (image.normalized_rom, image.code, image.data, raw, image.data_vram)
    raw = (ROOT / "roms/baserom.eu.z64").read_bytes()
    rom, _ = normalize_rom(raw)
    if sha1(rom) != "ee7bc6656fd1e1d9ffb3d19add759f28b88df710":
        raise ValueError("PAL ROM checksum mismatch")
    archive = parse_game_archive(rom[0x427B0:0x19EDE8])
    if sha1(archive.code) != "e79369f8c0cad22892728a3db723092bc6856f07":
        raise ValueError("PAL decoded game checksum mismatch")
    result["pal"] = (rom, archive.code, archive.data, raw, None)
    return result


def build_report() -> dict:
    images = load_inputs()
    boot = images["us"][0][0x290D0:0x291A0]
    profiles = {}
    for profile in ("us", "pal", "debug", "ects"):
        rom, code, data, raw, data_vram = images[profile]
        cpu_end, bss_start = CPU_ENDS[profile], BSS_STARTS[profile]
        if len(rom) != 0x4000000 or rom.find(boot) != cpu_end or rom.find(boot, cpu_end + 1) != -1:
            raise ValueError(f"{profile}: unique complete RSP-boot boundary check failed")
        high = struct.unpack_from(">I", rom, 0x1000)[0]
        low = struct.unpack_from(">I", rom, 0x1008 if profile in ("us", "pal") else 0x1004)[0]
        if high >> 16 != 0x3C08 or low >> 16 != 0x2508:
            raise ValueError(f"{profile}: unexpected boot BSS address construction")
        signed_low = (low & 0x7FFF) - (low & 0x8000)
        if ((high & 0xFFFF) << 16) + signed_low != 0x80000000 + bss_start:
            raise ValueError(f"{profile}: boot BSS address check failed")
        code_scopes = [("main", rom[0x1050:cpu_end], 0x80001050), ("game", code, 0x15000000)]
        data_scopes = [("post_cpu_initialized_main", rom[cpu_end:bss_start], 0x80000000 + cpu_end), ("game_data_offset", data, 0)]
        profiles[profile] = {
            "rom_bytes": len(raw), "raw_rom_sha1": sha1(raw), "normalized_rom_sha1": sha1(rom),
            "game_code_bytes": len(code), "game_code_sha1": sha1(code),
            "game_data_bytes": len(data), "game_data_sha1": sha1(data),
            "main_cpu_end": f"0x{cpu_end:X}", "main_bss_start": f"0x{bss_start:X}",
            "hardware_base_constructions": [{"scope": label, "address": f"0x{base + index * 4:08X}"} for label, image, base in code_scopes for index, word in enumerate(words(image)) if word >> 26 == 15 and word & 0xFFFF == 0xBC00],
            "hardware_pair_entries": scan_main_range(*RANGES[profile][1][1:], code_scopes, data_scopes),
            "ranges": [{"scope": scope, "start": f"0x{start:X}", "end": f"0x{end:X}", "sha1": sha1((rom if scope == "main" else code)[start:end])} for scope, start, end in RANGES[profile]],
            "targets": {f"0x{target:X}": scan_target(target, code_scopes, data_scopes) for target in TARGETS[profile]},
        }
    us = images["us"][0]
    crossings = []
    for index, word in enumerate(words(us[0x1050:CPU_ENDS["us"]])):
        source = 0x1050 + index * 4
        target = conditional_target(word, source)
        if target is not None and (0x38E0 <= source < 0x3920) != (0x38E0 <= target < 0x3920):
            crossings.append({"source": f"0x{source:X}", "target": f"0x{target:X}"})
    return {
        "purpose": "bounded read-only entry evidence; no ownership or matching transaction",
        "limitations": ["Low-half candidates require manual reaching-definition review.", "Negative scans do not exclude computed or encoded selections.", "Post-CPU main pointer scope includes RSP payloads and initialized data.", "No beta counterpart is asserted for US 0x39B0, 0x5218, 0x5298 or 0x52A0."],
        "profiles": profiles, "us_hardware_pair_conditional_crossings": crossings,
    }


if __name__ == "__main__":
    print(json.dumps(build_report(), indent=2))
