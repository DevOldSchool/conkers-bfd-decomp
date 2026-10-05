#!/usr/bin/env python3
"""Manifest-driven proof and integration of reviewed initialized main data.

Mappings require explicit ownership evidence. Never infer placement from a
candidate's symbol spelling, zero initializer, or improved diff score.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re

from candidate_tables import Object32
from elf_sections import sections
import layout_check
import rom_span
import rzip_archive

ROOT = Path(__file__).resolve().parent.parent
MANIFEST = "config/main/private-data.json"


def mappings(root: Path = ROOT) -> list[dict]:
    path = root / MANIFEST
    if not path.exists():
        return []  # Small fixtures and unregistered sources keep symbolic proof.
    value = json.loads(path.read_text())
    if not isinstance(value, dict) or value.get("schema_version") != 1 or not isinstance(value.get("units"), list):
        raise ValueError("unsupported main private-data manifest")
    sources, outputs, intervals = set(), set(), []
    for unit in value["units"]:
        if not isinstance(unit, dict):
            raise ValueError("invalid private-data unit")
        aliases = unit.get("sources")
        evidence = unit.get("evidence_reference", "")
        if (not isinstance(aliases, list) or not aliases
                or not all(isinstance(s, str) and re.fullmatch(r"src/(?:done/)?main/[A-Za-z0-9_/]+\.c", s)
                           and ".." not in s for s in aliases)
                or len(set(aliases)) != len(aliases) or sources.intersection(aliases)):
            raise ValueError("ambiguous or unsafe private-data source aliases")
        if (not isinstance(evidence, str) or not evidence.startswith("docs/evidence/")
                or ".." in Path(evidence).parts or not (root / evidence).is_file()
                or not (root / evidence).resolve().is_relative_to(root.resolve())):
            raise ValueError("private-data mapping requires recorded ownership evidence")
        sources.update(aliases)
        if not isinstance(unit.get("sections"), list) or not unit["sections"]:
            raise ValueError("private-data unit needs initialized section mappings")
        inputs = set()
        for section in unit["sections"]:
            if not isinstance(section, dict):
                raise ValueError("invalid private-data section")
            input_, output = section.get("input"), section.get("output")
            if (input_ not in (".data", ".rodata", ".sdata") or input_ in inputs
                    or not isinstance(output, str) or not re.fullmatch(r"\.main_private_[a-z0-9_]+", output)
                    or output in outputs or output in (".main", ".main_bss",)):
                raise ValueError("duplicate or unsupported private-data section")
            inputs.add(input_); outputs.add(output)
            try:
                address, offset = int(section["vram"], 0), int(section["rom_offset"], 0)
                size, alignment, flags = section["size"], section["alignment"], section["flags"]
                digest = section["sha256"]
            except (KeyError, TypeError, ValueError) as error:
                raise ValueError("invalid private-data mapping") from error
            if (type(size) is not int or size <= 0 or type(alignment) is not int
                    or alignment <= 0 or alignment & (alignment - 1)
                    or address % alignment or offset < 0 or address != 0x80000000 + offset
                    or type(flags) is not int
                    or flags not in ((3, 0x10000003) if input_ == ".sdata" else (2, 3)) or not isinstance(digest, str)
                    or not re.fullmatch(r"[0-9a-f]{64}", digest)):
                raise ValueError("invalid private-data address, extent, alignment or digest")
            if any(address < end and address + size > start for start, end in intervals):
                raise ValueError("overlapping private-data mappings")
            intervals.append((address, address + size))
    return value["units"]


def mapping(root: Path, source: str) -> dict | None:
    return next((unit for unit in mappings(root) if source in unit["sources"]), None)


def validated_rom(root: Path) -> bytes:
    metadata = json.loads((root / "config/roms.json").read_text())["profiles"]["us"]
    rom, _ = rzip_archive.normalize_rom((root / "roms/baserom.us.z64").read_bytes())
    if len(rom) != metadata["size_bytes"] or hashlib.sha1(rom).hexdigest() != metadata["sha1"]:
        raise ValueError("private data requires a checksum-validated US ROM")
    return rom


def expected_data(section: dict, rom: bytes) -> bytes:
    offset = int(section["rom_offset"], 0)
    payload = rom[offset:offset + section["size"]]
    if len(payload) != section["size"] or hashlib.sha256(payload).hexdigest() != section["sha256"]:
        raise ValueError("reviewed private-data digest differs from US ROM")
    return payload


def candidate_sections(obj: Object32, unit: dict, rom: bytes) -> frozenset[int] | None:
    parsed = sections(obj.data, 1)
    indices = set()
    for record in unit["sections"]:
        if record["input"] not in parsed:
            return None
        section, payload = parsed[record["input"]]
        if (section[1:4] != (1, record["flags"], 0) or section[5] != record["size"]
                or section[8] != record["alignment"] or payload != expected_data(record, rom)):
            return None
        indices.add(obj.sections.index(section))
    # Initialized sections with pointer relocations and private BSS need their
    # own reviewed proof. Do not silently place additional emitted storage.
    for name, (section, _) in parsed.items():
        if name != ".text" and section[5] and section[2] & 2 and section[1] in (1, 8):
            if obj.sections.index(section) not in indices:
                return None
    if any(section in indices for section, _ in obj.relocations):
        return None
    return frozenset(indices)


def prepare(root: Path, source: str, candidate: Path, reference: Path, assembly: Path,
            symbol: str, start: int, size: int, addresses: dict[str, int]) -> tuple[Path, Path] | None:
    import linked_aliases

    unit = mapping(root, source)
    if unit is None:
        return None
    current, raw = Object32(candidate.read_bytes()), Object32(reference.read_bytes())
    rom = validated_rom(root)
    private = candidate_sections(current, unit, rom)
    if private is None:
        return None
    origin, text = linked_aliases.function(current, symbol, size, padding=True)
    definitions = linked_aliases.definitions(current, text_addresses=addresses,
                                             text_section=text, text_base=start - origin,
                                             private_sections=private)
    raw_definitions = linked_aliases.definitions(raw)
    if definitions is None or raw_definitions is None:
        return None
    code, base, _ = rom_span.main_code(root)
    expected = rom_span.raw_span(assembly.read_text(), start, size, code, base)
    directory = root / "build/us/linked-aliases" / symbol
    directory.mkdir(parents=True, exist_ok=True)
    raw_bytes = linked_aliases.linked_span(reference, raw, symbol, start, size,
                                          raw_definitions, directory / "reference", reference=True)
    if raw_bytes != expected:
        raise ValueError("private-data raw reference differs from the US ROM")
    placements = {s["input"]: (int(s["vram"], 0), s["alignment"]) for s in unit["sections"]}
    current_bytes = linked_aliases.linked_span(candidate, current, symbol, start, size,
                                              definitions, directory / "candidate", reference=False,
                                              padding=True, section_placements=placements)
    linked = sections((directory / "candidate.elf").read_bytes(), 2)
    for record in unit["sections"]:
        section, payload = linked[record["input"]]
        if (section[1:4] != (1, record["flags"], int(record["vram"], 0))
                or section[5] != record["size"] or section[8] != record["alignment"]
                or payload != expected_data(record, rom)):
            raise ValueError("linked private-data section differs from reviewed mapping")
    if current_bytes != expected:
        return None
    if current.data != candidate.read_bytes() or raw.data != reference.read_bytes():
        raise ValueError("private-data objects changed during proof")
    paths = directory / "candidate.o", directory / "reference.o"
    for path, payload in zip(paths, (current_bytes, raw_bytes)):
        path.write_bytes(linked_aliases.comparison_object(payload, symbol))
    return paths


def active_units(root: Path, sources: list[str]) -> list[tuple[dict, str]]:
    result = []
    for unit in mappings(root):
        active = set(unit["sources"]).intersection(sources)
        if len(active) > 1:
            raise ValueError("both raw and completed aliases are active")
        if active:
            result.append((unit, active.pop()))
    return result


def linker(root: Path, output: Path, sources: list[str]) -> None:
    lines = ["/* Generated from reviewed private-data mappings. */", "SECTIONS", "{",
             "    __main_private_saved_dot = ABSOLUTE(.);"]
    assertions = []
    for unit, source in active_units(root, sources):
        object_path = "build/us/" + source.removesuffix(".c") + ".o"
        for record in unit["sections"]:
            lines.extend([f"    {record['output']} {record['vram']} (INFO) : SUBALIGN({record['alignment']})",
                          "    {", f"        {object_path}({record['input']})", "    }"])
            assertions.append(f"ASSERT(SIZEOF({record['output']}) == {record['size']}, \"private data extent changed\")")
    lines.extend(["    . = __main_private_saved_dot;", "}"] + assertions)
    payload = "\n".join(lines) + "\n"
    output.parent.mkdir(parents=True, exist_ok=True)
    if not output.exists() or output.read_text() != payload:
        output.write_text(payload)


def verify(root: Path, elf: Path, sources: list[str]) -> None:
    linked = sections(elf.read_bytes(), 2)
    active = active_units(root, sources)
    outputs = {s["output"] for unit, _ in active for s in unit["sections"]}
    all_outputs = {s["output"] for unit in mappings(root) for s in unit["sections"]}
    if ({name for name in linked if name.startswith(".main_private_")} != outputs
            or all_outputs.intersection(linked) != outputs):
        raise ValueError("missing or inactive private-data output section")
    if not active:
        return
    main, backing = linked[".main"]
    if main[1] != 1 or not main[2] & 2:
        raise ValueError("private-data backing must be allocated main PROGBITS")
    rom = validated_rom(root)
    units = json.loads((root / "progress/source_units.json").read_text())["source_units"]
    functions = json.loads((root / "progress/functions.json").read_text())["functions"]
    for unit, source in active:
        owners = [u for u in units if u["source"] == source and u.get("boundary_evidence", {}).get("us", {}).get("reviewed") is True]
        if len(owners) != 1:
            raise ValueError("private data needs one reviewed source-unit owner")
        owner = owners[0]
        addresses = [int(f["regions"]["us"]["vram"], 0) for f in functions
                     if f["symbol"] in owner["functions"] and f.get("overlay", "main") == "main"]
        if len(addresses) != len(owner["functions"]):
            raise ValueError("private-data unit has incomplete main membership")
        text_start = min(addresses)
        text_size = int(owner["regions"]["us"]["end"], 0) - int(owner["regions"]["us"]["start"], 0)
        offset = text_start - main[3]
        rom_offset = int(owner["regions"]["us"]["start"], 0)
        if offset < 0 or offset + text_size > len(backing) or backing[offset:offset + text_size] != rom[rom_offset:rom_offset + text_size]:
            raise ValueError("entire linked private-data source unit differs from US ROM")
        for record in unit["sections"]:
            s, payload = linked[record["output"]]
            address = int(record["vram"], 0)
            if (s[1:4] != (1, record["flags"] & ~2, address) or s[5] != record["size"]
                    or s[8] != record["alignment"] or payload != expected_data(record, rom)):
                raise ValueError("private-data INFO mapping differs from reviewed contract")
            offset = address - main[3]
            if offset < 0 or offset + len(payload) > len(backing) or backing[offset:offset + len(payload)] != payload:
                raise ValueError("original allocated backing differs from private data")
        print(f"{source}: private data and entire {text_size}-byte linked unit match US ROM")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("linker", "verify"))
    parser.add_argument("--output", type=Path)
    parser.add_argument("--elf", type=Path)
    parser.add_argument("--source", action="append", default=[])
    args = parser.parse_args()
    try:
        if args.action == "linker":
            if args.output is None: parser.error("linker needs --output")
            linker(ROOT, args.output, args.source)
        else:
            if args.elf is None: parser.error("verify needs --elf")
            verify(ROOT, args.elf, args.source)
    except (ValueError, OSError, KeyError) as error:
        parser.exit(1, f"error: {error}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
