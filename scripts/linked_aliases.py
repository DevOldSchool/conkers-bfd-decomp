"""Resolve address-label aliases only after full linked-byte and ROM proof.

The normal symbolic differ remains authoritative for all other candidates.
This narrow path supports undefined address-bearing bootstrap labels and no
local data relocations. Original objects and assembly are never rewritten.
"""
from __future__ import annotations

import re
import struct
import subprocess
from pathlib import Path

from candidate_tables import Object32
import rom_span

ADDRESS = re.compile(r"(?:D|func)_([0-9A-Fa-f]{8})")
DATA_ADDRESS = re.compile(r"D_([0-9A-Fa-f]{8})")


def function(obj: Object32, symbol: str, size: int, *, reference: bool = False):
    matches = [s for symbols in obj.symbols.values() for s in symbols if s[0] == symbol]
    if len(matches) != 1:
        raise ValueError("alias proof requires one function symbol")
    _, origin, extent, section = matches[0]
    if extent not in ((0, size) if reference else (size,)):
        raise ValueError("alias proof function extent differs from registered span")
    if origin % 4 or origin + size > len(obj.section(section)):
        raise ValueError("alias proof function exceeds its text section")
    return origin, section


def address_alias_present(candidate: Object32, reference: Object32, symbol: str, size: int) -> bool:
    origin, section = function(candidate, symbol, size)
    raw_origin, raw_section = function(reference, symbol, size, reference=True)
    for offset in range(0, size, 4):
        left = candidate.relocations.get((section, origin + offset))
        right = reference.relocations.get((raw_section, raw_origin + offset))
        if (left and right and left[0] == right[0] and left[0] in (5, 6)
                and DATA_ADDRESS.fullmatch(left[1][0]) and DATA_ADDRESS.fullmatch(right[1][0])
                and left[1][0] != right[1][0]):
            return True
    return False


def definitions(obj: Object32) -> dict[str, int] | None:
    result = {}
    for kind, (name, value, _, section) in obj.relocations.values():
        match = ADDRESS.fullmatch(name)
        if kind not in (2, 4, 5, 6) or section != 0 or value != 0 or match is None:
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
                symbols: dict[str, int], output: Path, *, reference: bool) -> bytes:
    origin, _ = function(obj, symbol, size, reference=reference)
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
            symbol: str, start: int, size: int) -> tuple[Path, Path] | None:
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
    code, base, _ = rom_span.game_code(root)
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
