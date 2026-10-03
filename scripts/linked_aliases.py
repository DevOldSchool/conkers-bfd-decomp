"""Resolve address-label aliases only after full linked-byte and ROM proof.

The normal symbolic differ remains authoritative for all other candidates.
The existing path supports undefined address-bearing bootstrap labels. A separate
debugger SI path also proves literal MMIO operands, retaining natural same-object
call resolution. The debugger also permits one explicitly reviewed empty-return
companion within its unchanged registered span. Neither path accepts local data relocations or rewrites originals.
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


def reviewed_empty_companion(obj: Object32, symbol: str, size: int) -> bool:
    """Recognize only 019A8's reviewed 0xBC body plus 1A64's empty return.

    This establishes symbol coverage, not a match. Both linked objects still
    have to equal the independently ROM-validated complete 0xC4-byte raw span.
    """
    if (symbol, size) != ("func_160019A8", 0xC4):
        return False
    records = []
    for table, entries in obj.symbols.items():
        for index, entry in enumerate(entries):
            # Object32 deliberately omits st_info/st_other from its public tuple.
            info, other = obj.unpack(">BB", obj.sections[table][4] + index * 16 + 12)
            records.append((entry, info, other))
    primary = [record for record in records if record[0][0] == symbol]
    companion = [record for record in records if record[0][0] == "func_16001A64"]
    if len(primary) != 1 or len(companion) != 1:
        return False
    main, info, other = primary[0]
    tail, tail_info, tail_other = companion[0]
    _, origin, extent, text = main
    if (info != 0x12 or other != 0 or tail_info != 0x12 or tail_other != 0
            or extent != 0xBC or tail != ("func_16001A64", origin + 0xBC, 8, text)
            or not 0 < text < len(obj.sections)
            or obj.sections[text][1:3] != (1, 6)
            or origin % 4 or origin + size > len(obj.section(text))):
        return False
    # Any additional function entry or sized symbol intersecting the reviewed
    # span would make this two-member coverage ambiguous. IDO emits a local
    # STT_SECTION symbol covering all of .text; that is section metadata, not
    # another function. Accept only its canonical zero/full-section extent.
    for entry, kind, visibility in records:
        if entry in (main, tail):
            continue
        name, value, length, section = entry
        if section == text and kind & 15 == 3:
            if (kind != 3 or visibility != 0 or name not in ("", ".text")
                    or value != 0 or length not in (0, len(obj.section(text)))):
                return False
            continue
        if section == text and ((length > 0 and value < origin + size and value + length > origin)
                                or (kind & 15 == 2 and origin <= value < origin + size)):
            return False
    if any(section == text and origin + 0xBC <= offset < origin + size
           for section, offset in obj.relocations):
        return False
    return (obj.word(text, origin + 0xB4), obj.word(text, origin + 0xB8),
            obj.word(text, origin + 0xBC), obj.word(text, origin + 0xC0)) == (0x03E00008, 0, 0x03E00008, 0)


def function(obj: Object32, symbol: str, size: int, *, reference: bool = False,
             padding: bool = False, empty_companion: bool = False):
    matches = [s for symbols in obj.symbols.values() for s in symbols if s[0] == symbol]
    if len(matches) != 1:
        raise ValueError("alias proof requires one function symbol")
    _, origin, extent, section = matches[0]
    if padding:
        valid_extent = 0 < extent <= size
    else:
        valid_extent = (extent in ((0, size) if reference else (size,))
                        or (empty_companion and not reference
                            and reviewed_empty_companion(obj, symbol, size)))
    if not valid_extent:
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
                          *, literals: bool = False, empty_companion: bool = False) -> bool:
    origin, section = function(candidate, symbol, size, empty_companion=empty_companion)
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


SI_REGISTERS = frozenset({"D_A4800000", "D_A4800004", "D_A4800010", "D_A4800018"})


def si_literal_equivalent(candidate: Object32, reference: Object32,
                          symbol: str, size: int, *, empty_companion: bool = False) -> bool:
    """Recognize only the reviewed SI LUI plus word-load/store literal forms.

    This is eligibility for full linked-byte proof, never acceptance by itself.
    Repeated or ambiguous HI/LO uses and symbol addends deliberately fall back.
    """
    origin, section = function(candidate, symbol, size, empty_companion=empty_companion)
    raw_origin, raw_section = function(reference, symbol, size, reference=True)
    pairs = {}
    for (rel_section, offset), (kind, target) in reference.relocations.items():
        if rel_section != raw_section or not raw_origin <= offset < raw_origin + size:
            continue
        name, value, _, target_section = target
        if name not in SI_REGISTERS:
            continue
        if kind not in (5, 6) or target_section != 0 or value != 0:
            return False
        pairs.setdefault(name, []).append((kind, offset))
    if not pairs:
        return False
    for name, entries in pairs.items():
        if len(entries) != 2 or sorted(kind for kind, _ in entries) != [5, 6]:
            return False
        locations = dict(entries)
        upper_offset, lower_offset = locations[5], locations[6]
        if upper_offset >= lower_offset:
            return False
        upper = reference.word(raw_section, upper_offset)
        lower = reference.word(raw_section, lower_offset)
        base = (upper >> 16) & 31
        if (upper >> 26 != 15 or (upper >> 21) & 31 or base == 0
                or lower >> 26 not in (35, 43) or (lower >> 21) & 31 != base):
            return False
        # Original SI references have no symbol addend. Do not generalize this
        # path to arbitrary aliases or signed-low carry schedules.
        if upper & 0xFFFF or lower & 0xFFFF:
            return False
        current_upper = origin + upper_offset - raw_origin
        current_lower = origin + lower_offset - raw_origin
        if ((section, current_upper) in candidate.relocations
                or (section, current_lower) in candidate.relocations):
            return False
        literal_upper = candidate.word(section, current_upper)
        literal_lower = candidate.word(section, current_lower)
        if ((upper & 0xFFFF0000) != (literal_upper & 0xFFFF0000)
                or (lower & 0xFFFF0000) != (literal_lower & 0xFFFF0000)):
            return False
        low = literal_lower & 0xFFFF
        address = ((literal_upper & 0xFFFF) << 16) + (low if low < 0x8000 else low - 0x10000)
        if (address & 0xFFFFFFFF) != int(name[2:], 16):
            return False
    return True


def si_definitions(obj: Object32, symbol: str, start: int, size: int,
                   *, reference: bool = False, empty_companion: bool = False) -> dict[str, int] | None:
    """Resolve undefined labels only; never rebind compacted C definitions."""
    origin, text = function(obj, symbol, size, reference=reference, empty_companion=empty_companion)
    text_start = start - origin
    if text_start < 0:
        return None
    names = {}
    for table in obj.symbols.values():
        for entry in table:
            if entry[0]:
                names.setdefault(entry[0], set()).add(entry)
    result = {}
    for (rel_section, offset), (kind, target) in obj.relocations.items():
        name, value, _, section = target
        match = ADDRESS.fullmatch(name)
        if match is None or len(names.get(name, ())) != 1:
            return None
        if section == 0:
            if kind not in (2, 4, 5, 6) or value != 0:
                return None
            result[name] = int(match[1], 16)
            continue
        if (kind != 4 or rel_section != text or section != text
                or not name.startswith("func_") or value % 4
                or not 0 <= value < len(obj.section(text))):
            return None
        word = obj.word(text, offset)
        if word >> 26 != 3:
            return None
        # Calls in unrelated compacted C can retain their natural resolution.
        # Calls in this span must already land at the canonical address. Do not
        # override a definition to hide omitted GLOBAL_ASM bytes in its prefix.
        if origin <= offset < origin + size:
            if (word & 0x03FFFFFF
                    or text_start + value != int(match[1], 16)):
                return None
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
                padding: bool = False, empty_companion: bool = False) -> bytes:
    origin, _ = function(obj, symbol, size, reference=reference, padding=padding,
                         empty_companion=empty_companion)
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
    # This is an explicit reviewed debugger composition, never a generic smaller
    # function extent exception. The canonical start and full size cannot change.
    empty_companion = (overlay, symbol, start, size) == (
        "debugger", "func_160019A8", 0x160019A8, 0xC4)
    # Ordinary size mismatches remain useful symbolic diagnostics, not tooling failures.
    try:
        eligible = address_alias_present(current, raw, symbol, size, empty_companion=empty_companion)
        if eligible and overlay != "debugger":
            # Preserve the existing game path and its restrictions unchanged.
            current_symbols, raw_symbols = definitions(current), definitions(raw)
        elif overlay == "debugger" and (eligible or si_literal_equivalent(
                current, raw, symbol, size, empty_companion=empty_companion)):
            current_symbols = si_definitions(current, symbol, start, size, empty_companion=empty_companion)
            raw_symbols = si_definitions(raw, symbol, start, size, reference=True)
        else:
            return None
    except ValueError:
        return None
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
                                output / "candidate", reference=False, empty_companion=empty_companion)
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


def game_eligible(candidate: Path, reference: Path, symbol: str, size: int) -> bool:
    """GAME only admits exact-extent, symbolic data-address aliases."""
    try:
        return address_alias_present(Object32(candidate.read_bytes()),
                                     Object32(reference.read_bytes()), symbol, size)
    except ValueError:
        return False


def game_unit_registered(root: Path, source: str, symbol: str) -> bool:
    """Registered units cannot fall back to a focused-only alias proof."""
    path = root / "progress/source_units.json"
    if not path.is_file():
        return False
    units = json.loads(path.read_text())["source_units"]
    return any(unit["source"] == source or symbol in unit["functions"] for unit in units)


def game_context(root: Path, source: str, symbol: str, start: int, size: int):
    """Resolve one complete, contiguous, reviewed US GAME source unit."""
    inventory = json.loads((root / "progress/functions.json").read_text())["functions"]
    matches = [entry for entry in inventory
               if entry.get("regions", {}).get("us", {}).get("symbol") == symbol]
    if len(matches) != 1:
        raise ValueError("game comparison requires one registered function")
    entry = matches[0]
    if (entry.get("overlay") != "game" or entry["source"] != source
            or Path(source).as_posix() != source or Path(source).is_absolute()
            or ".." in Path(source).parts
            or int(entry["regions"]["us"]["vram"], 16) != start):
        raise ValueError("game comparison source, address or full span differs from registration")
    units = json.loads((root / "progress/source_units.json").read_text())["source_units"]
    owners = [unit for unit in units
              if unit["source"] == source or entry["symbol"] in unit["functions"]]
    if (len(owners) != 1 or owners[0]["source"] != source
            or entry["symbol"] not in owners[0]["functions"]
            or owners[0].get("boundary_evidence", {}).get("us", {}).get("reviewed") is not True):
        raise ValueError("game comparison requires one reviewed source-unit owner")
    unit = owners[0]
    identifiers = unit["functions"]
    if len(set(identifiers)) != len(identifiers) or not identifiers:
        raise ValueError("game comparison has ambiguous source-unit membership")
    members = []
    for identifier in identifiers:
        found = [member for member in inventory if member["symbol"] == identifier]
        if (len(found) != 1 or found[0]["source"] != source
                or found[0].get("overlay") != "game" or "us" not in found[0]["regions"]
                or any(other is not unit and identifier in other["functions"] for other in units)):
            raise ValueError("game comparison has an ambiguous or foreign source-unit member")
        members.append(found[0])
    if {member["symbol"] for member in inventory if member.get("source") == source} != set(identifiers):
        raise ValueError("game comparison omits a registered source-unit member")
    bounds = unit["regions"]["us"]
    boundary_start, boundary_end = int(bounds["start"], 16), int(bounds["end"], 16)
    extent = boundary_end - boundary_start
    game_identifiers = {member["symbol"] for member in inventory
                        if member.get("overlay") == "game" and "us" in member.get("regions", {})}
    for other in units:
        region = other.get("regions", {}).get("us")
        if other is unit or region is None or not game_identifiers.intersection(other["functions"]):
            continue
        other_start, other_end = int(region["start"], 16), int(region["end"], 16)
        if other_start < 0 or other_end <= other_start:
            raise ValueError("game comparison has invalid foreign source-unit bounds")
        # Ownership comes from registered unit intervals even when a foreign
        # final member has no size_bytes. Touching half-open boundaries are safe.
        if boundary_start < other_end and other_start < boundary_end:
            raise ValueError("game comparison overlaps another registered GAME source unit")
    unit_start = int(members[0]["regions"]["us"]["vram"], 16)
    cursor = unit_start
    addresses = {}
    spans = {}
    for index, member in enumerate(members):
        region = member["regions"]["us"]
        address = int(region["vram"], 16)
        end = (int(members[index + 1]["regions"]["us"]["vram"], 16)
               if index + 1 < len(members) else unit_start + extent)
        span = region.get("size_bytes", end - address)
        if (address != cursor or not isinstance(span, int) or span <= 0 or span % 4
                or region["symbol"] != f"func_{address:08X}" or region["symbol"] in addresses):
            raise ValueError("game comparison member spans are not contiguous and unambiguous")
        addresses[region["symbol"]] = address
        spans[region["symbol"]] = span
        cursor += span
    if spans[symbol] != size:
        raise ValueError("game comparison does not cover the full registered span")
    if unit_start % 16 or extent <= 0 or extent % 16 or cursor != unit_start + extent:
        raise ValueError("game comparison has an invalid complete unit extent or alignment")
    for member in inventory:
        region = member.get("regions", {}).get("us")
        if member.get("overlay") != "game" or region is None or member in members:
            continue
        address = int(region["vram"], 16)
        if (region["symbol"] in addresses or unit_start <= address < cursor
                or address < unit_start < address + int(region.get("size_bytes", 0))):
            raise ValueError("game comparison unit overlaps another registered function")
    return entry, unit, members, addresses, unit_start, extent, spans


def game_definitions(obj: Object32, addresses: dict[str, int], section: int,
                     base: int) -> dict[str, int] | None:
    """Inspect the entire object, including dependencies outside the target."""
    names = [name for symbols in obj.symbols.values() for name, _, _, _ in symbols if name]
    if len(names) != len(set(names)):
        return None
    for (location_section, offset), (kind, (_, _, _, defined_section)) in obj.relocations.items():
        # This capability has no data/jump-table ownership or non-text fixups.
        if location_section != section:
            return None
        word = obj.word(location_section, offset)
        if defined_section and (kind != 4 or word >> 26 != 3 or word & 0x03FFFFFF):
            return None
    if any(index != section and header[1] in (1, 8) and header[2] & 6 and header[5]
           for index, header in enumerate(obj.sections)):
        return None
    return definitions(obj, text_addresses=addresses, text_section=section, text_base=base)


def prepare_game(root: Path, source: str, candidate: Path, reference: Path, assembly: Path,
                 symbol: str, start: int, size: int) -> tuple[Path, Path] | None:
    """Prove the target and every physical byte of its freshly built GAME unit."""
    entry, unit, members, addresses, unit_start, extent, spans = game_context(root, source, symbol, start, size)
    current, raw = Object32(candidate.read_bytes()), Object32(reference.read_bytes())
    if not address_alias_present(current, raw, symbol, size):
        return None
    measured, text_size, alignment = layout_check.archived_object_layout(current.data)
    layout_check.validate_layout(entry, unit, measured, text_size, alignment, "us", root=root)
    origin, section = function(current, symbol, size)
    if alignment != 16 or text_size != extent or start - origin != unit_start:
        raise layout_check.LayoutMismatch("game comparison needs the exact unit extent, origin and alignment")
    current_symbols = game_definitions(current, addresses, section, unit_start)
    raw_origin, raw_section = function(raw, symbol, size, reference=True)
    raw_symbols = game_definitions(raw, {}, raw_section, start - raw_origin)
    if current_symbols is None or raw_symbols is None:
        return None
    for member in members:
        region = member["regions"]["us"]
        position, member_section = function(current, region["symbol"], spans[region["symbol"]], padding=True)
        if member_section != section or position != addresses[region["symbol"]] - unit_start:
            raise layout_check.LayoutMismatch("game comparison member has an incorrect text position")
    code, base, _ = rom_span.game_code(root)
    if unit_start != base + int(unit["regions"]["us"]["start"], 16):
        raise ValueError("game comparison unit base differs from the US ROM")
    expected = rom_span.raw_span(assembly.read_text(), start, size, code, base)
    unit_offset = unit_start - base
    expected_unit = code[unit_offset:unit_offset + extent]
    if unit_offset < 0 or len(expected_unit) != extent:
        raise ValueError("game comparison unit exceeds the US ROM")
    output = root / "build/us/linked-aliases" / symbol
    output.mkdir(parents=True, exist_ok=True)
    raw_bytes = linked_span(reference, raw, symbol, start, size, raw_symbols,
                            output / "reference", reference=True)
    if raw_bytes != expected:
        raise ValueError("linked raw-reference span differs from the US ROM")
    current_bytes = linked_span(candidate, current, symbol, start, size, current_symbols,
                                output / "candidate", reference=False)
    # linked_span writes the whole real .text section before extracting the
    # bounded display span. No fabricated alignment or cropped unit is accepted.
    complete = (output / "candidate.bin").read_bytes()
    if candidate.read_bytes() != current.data or reference.read_bytes() != raw.data:
        raise ValueError("game comparison objects changed during proof")
    if current_bytes != expected or complete != expected_unit:
        return None
    paths = output / "candidate.o", output / "reference.o"
    for path, payload in zip(paths, (current_bytes, raw_bytes)):
        path.write_bytes(comparison_object(payload, symbol))
    return paths


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
