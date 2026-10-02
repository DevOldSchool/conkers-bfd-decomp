"""Resolve address-label aliases only after full linked-byte and ROM proof.

The normal symbolic differ remains authoritative for all other candidates.
This narrow path supports undefined address-bearing bootstrap labels and no
local data relocations. Original objects and assembly are never rewritten.
"""
from __future__ import annotations

import re
import struct
import subprocess
import json
from pathlib import Path

from candidate_tables import Object32
import layout_check
import rom_span

ADDRESS = re.compile(r"(?:D|func)_([0-9A-Fa-f]{8})")
DATA_ADDRESS = re.compile(r"D_([0-9A-Fa-f]{8})")


def function(obj: Object32, symbol: str, size: int, *, reference: bool = False,
             padding: bool = False):
    matches = [s for symbols in obj.symbols.values() for s in symbols if s[0] == symbol]
    if len(matches) != 1:
        raise ValueError("alias proof requires one function symbol")
    _, origin, extent, section = matches[0]
    if (not padding and extent not in ((0, size) if reference else (size,))
            or padding and not 0 < extent <= size):
        raise ValueError("alias proof function extent differs from registered span")
    if (size <= 0 or size % 4 or origin % 4 or extent % 4
            or origin + size > len(obj.section(section))
            or obj.sections[section][1] != 1 or not obj.sections[section][2] & 4):
        raise ValueError("alias proof function exceeds its text section")
    if padding and any(name and name != symbol and index == section
                       and origin + extent <= value < origin + size
                       for symbols in obj.symbols.values()
                       for name, value, _, index in symbols):
        raise ValueError("alias proof padding overlaps the next text symbol")
    return origin, section


def address_alias_present(candidate: Object32, reference: Object32, symbol: str, size: int,
                          *, literals: bool = False) -> bool:
    origin, section = function(candidate, symbol, size)
    raw_origin, raw_section = function(reference, symbol, size, reference=True)
    for offset in range(0, size, 4):
        left = candidate.relocations.get((section, origin + offset))
        right = reference.relocations.get((raw_section, raw_origin + offset))
        if (left and right and left[0] == right[0] and left[0] in (5, 6)
                and DATA_ADDRESS.fullmatch(left[1][0]) and DATA_ADDRESS.fullmatch(right[1][0])
                and left[1][0] != right[1][0]):
            return True
        # A literal address has no relocation at all. Eligibility is only a
        # reason to attempt the independent linked-byte proof, never equality.
        if literals and ((left is None) != (right is None)):
            relocation = left or right
            if relocation[0] in (5, 6) and DATA_ADDRESS.fullmatch(relocation[1][0]):
                return True
    return False


def definitions(obj: Object32, *, text_addresses: dict[str, int] | None = None,
                text_section: int | None = None, text_base: int = 0) -> dict[str, int] | None:
    result = {}
    for kind, (name, value, _, section) in obj.relocations.values():
        match = ADDRESS.fullmatch(name)
        if kind not in (2, 4, 5, 6) or match is None:
            return None
        if section:
            # Only real, uniquely defined, reviewed same-unit callees. Leave
            # them to the linker: assigning their address in the script would
            # conceal a compressed or stale candidate's incorrect offsets.
            matches = [s for syms in obj.symbols.values() for s in syms if s[0] == name]
            if (kind != 4 or section != text_section or text_addresses is None
                    or not name.startswith("func_") or len(matches) != 1
                    or text_addresses.get(name) != text_base + value
                    or int(match[1], 16) != text_base + value):
                return None
            continue
        if value != 0:
            return None
        result[name] = int(match[1], 16)
    return result


def comparison_object(payload: bytes, symbol: str) -> bytes:
    """Package already verified linked bytes for bounded object-mode display."""
    strings = b"\0" + symbol.encode("ascii") + b"\0"
    names = b"\0.text\0.symtab\0.strtab\0.shstrtab\0"
    symbols = bytes(16) + struct.pack(">IIIBBH", 1, 0, len(payload), 0x12, 0, 1)
    sections = [(0, 0, 0, b"", 0, 0, 0), (1, 1, 6, payload, 0, 0, 0),
                (7, 2, 0, symbols, 3, 1, 16), (15, 3, 0, strings, 0, 0, 0),
                (23, 3, 0, names, 0, 0, 0)]
    body = bytearray(52)
    headers = []
    for name, kind, flags, data, link, info, entsize in sections:
        body.extend(bytes(-len(body) % 4))
        headers.append(struct.pack(">10I", name, kind, flags, 0, len(body), len(data), link, info, 4, entsize))
        body.extend(data)
    body.extend(bytes(-len(body) % 4))
    offset = len(body)
    body.extend(b"".join(headers))
    body[:52] = struct.pack(">16sHHIIIIIHHHHHH", b"\x7fELF\x01\x02\x01" + bytes(9),
                            1, 8, 1, 0, 0, offset, 0x10001000, 52, 0, 0, 40, len(sections), 4)
    return bytes(body)


def linked_span(path: Path, obj: Object32, symbol: str, start: int, size: int,
                symbols: dict[str, int], output: Path, *, reference: bool,
                padding: bool = False) -> bytes:
    origin, _ = function(obj, symbol, size, reference=reference, padding=padding)
    if start < origin:
        raise ValueError("alias proof has an invalid text address")
    script = output.with_suffix(".ld")
    script.write_text(f"SECTIONS {{ .text 0x{start - origin:X} : SUBALIGN(4) {{ *(.text) }} }}\n"
                      + "".join(f"{name} = 0x{value:X};\n" for name, value in sorted(symbols.items())))
    subprocess.run(["mips-linux-gnu-ld", "-T", str(script), "-o", str(output.with_suffix(".elf")),
                    str(path)], check=True, capture_output=True, text=True)
    subprocess.run(["mips-linux-gnu-objcopy", "-O", "binary", "--only-section=.text",
                    str(output.with_suffix(".elf")), str(output.with_suffix(".bin"))],
                   check=True, capture_output=True, text=True)
    payload = output.with_suffix(".bin").read_bytes()[origin:origin + size]
    if len(payload) != size:
        raise ValueError("linked alias proof is truncated")
    return payload


def prepare(root: Path, candidate: Path, reference: Path, assembly: Path,
            symbol: str, start: int, size: int, *, overlay: str = "game") -> tuple[Path, Path] | None:
    current = Object32(candidate.read_bytes())
    raw = Object32(reference.read_bytes())
    # Ordinary size mismatches remain useful symbolic diagnostics, not tooling failures.
    try:
        eligible = address_alias_present(current, raw, symbol, size)
    except ValueError:
        return None
    if not eligible:
        return None
    current_symbols, raw_symbols = definitions(current), definitions(raw)
    if current_symbols is None or raw_symbols is None:
        return None
    code, base, _ = rom_span.code_image(root, overlay)
    expected = rom_span.raw_span(assembly.read_text(), start, size, code, base)
    output = root / "build/us/linked-aliases" / symbol
    output.mkdir(parents=True, exist_ok=True)
    raw_bytes = linked_span(reference, raw, symbol, start, size, raw_symbols,
                            output / "reference", reference=True)
    if raw_bytes != expected:
        raise ValueError("linked raw-reference span differs from the US ROM")
    current_bytes = linked_span(candidate, current, symbol, start, size, current_symbols,
                                output / "candidate", reference=False)
    if current_bytes != raw_bytes:
        return None
    paths = output / "candidate.o", output / "reference.o"
    for path, payload in zip(paths, (current_bytes, raw_bytes)):
        path.write_bytes(comparison_object(payload, symbol))
    return paths


def main_eligible(candidate: Path, reference: Path, symbol: str, size: int) -> bool:
    """Keep the mixed-context path restricted to aliases and short extents."""
    current, raw = Object32(candidate.read_bytes()), Object32(reference.read_bytes())
    matches = [s for syms in current.symbols.values() for s in syms if s[0] == symbol]
    if len(matches) != 1:
        raise ValueError("main comparison requires one candidate function symbol")
    if 0 < matches[0][2] < size:
        return True
    try:
        return address_alias_present(current, raw, symbol, size, literals=True)
    except ValueError:
        return False


def prepare_main(root: Path, source: str, candidate: Path, reference: Path, assembly: Path,
                 symbol: str, start: int, size: int) -> tuple[Path, Path] | None:
    """Prove a freshly compiled mixed main object, without altering its layout."""
    inventory = json.loads((root / "progress/functions.json").read_text())["functions"]
    matches = [entry for entry in inventory
               if entry.get("regions", {}).get("us", {}).get("symbol") == symbol]
    if len(matches) != 1:
        raise ValueError("main comparison requires one registered function")
    entry = matches[0]
    if (entry.get("overlay", "main") != "main" or entry["source"] != source
            or int(entry["regions"]["us"]["vram"], 16) != start):
        raise ValueError("main comparison source or address differs from registration")
    units = json.loads((root / "progress/source_units.json").read_text())["source_units"]
    units = [unit for unit in units if unit["source"] == source
             and entry["symbol"] in unit["functions"]]
    if (len(units) != 1
            or units[0].get("boundary_evidence", {}).get("us", {}).get("reviewed") is not True):
        return None
    unit = units[0]
    current, raw = Object32(candidate.read_bytes()), Object32(reference.read_bytes())
    measured, extent, alignment = layout_check.archived_object_layout(current.data)
    layout_check.validate_layout(entry, unit, measured, extent, alignment, "us", root=root)
    origin, section = function(current, symbol, size, padding=True)
    addresses = {}
    for identifier in unit["functions"]:
        members = [member for member in inventory if member["symbol"] == identifier]
        if len(members) != 1 or members[0]["source"] != source:
            raise ValueError("main comparison has an ambiguous source-unit member")
        region = members[0]["regions"].get("us")
        if region:
            addresses[region["symbol"]] = int(region["vram"], 16)
    registered_size = entry["regions"]["us"].get("size_bytes")
    if registered_size is None:
        bounds = unit["regions"]["us"]
        unit_end = min(addresses.values()) + int(bounds["end"], 16) - int(bounds["start"], 16)
        registered_size = min([address for address in addresses.values() if address > start]
                              + [unit_end]) - start
    following = [int(member["regions"]["us"]["vram"], 16) for member in inventory
                 if member.get("overlay", "main") == "main" and "us" in member["regions"]
                 and int(member["regions"]["us"]["vram"], 16) > start]
    registered_size = min([int(registered_size)] + [address - start for address in following])
    if size != registered_size:
        raise ValueError("main comparison does not cover the full registered span")
    # A registered span cannot consume any neighbor, even if its bytes happen
    # to agree. The full tail must already exist in the real mixed object.
    if any(start < address < start + size for address in addresses.values()):
        raise ValueError("main comparison span overlaps the next function")
    current_symbols = definitions(current, text_addresses=addresses,
                                  text_section=section, text_base=start - origin)
    raw_symbols = definitions(raw)
    if current_symbols is None or raw_symbols is None:
        return None
    code, base, _ = rom_span.main_code(root)
    expected = rom_span.raw_span(assembly.read_text(), start, size, code, base)
    output = root / "build/us/linked-aliases" / symbol
    output.mkdir(parents=True, exist_ok=True)
    raw_bytes = linked_span(reference, raw, symbol, start, size, raw_symbols,
                            output / "reference", reference=True)
    if raw_bytes != expected:
        raise ValueError("linked raw-reference span differs from the US ROM")
    current_bytes = linked_span(candidate, current, symbol, start, size, current_symbols,
                                output / "candidate", reference=False, padding=True)
    if current_bytes != expected:
        return None
    paths = output / "candidate.o", output / "reference.o"
    for path, payload in zip(paths, (current_bytes, raw_bytes)):
        path.write_bytes(comparison_object(payload, symbol))
    return paths
