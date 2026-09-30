"""Additional candidate-time gate for ROM-backed IDO game switch tables.

Run only after a full-span instruction CURRENT (0): instruction offsets then
identify the candidate's dispatch relocations. This does not prove final linker
placement, replace finish, or replace linked-ROM verification.
"""
from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import re
import struct

import hashlib
import json
import rzip_archive

ROOT = Path(__file__).resolve().parents[1]


class TableEvidenceError(ValueError):
    """A switch cannot be verified, or its emitted case targets differ."""


@dataclass(frozen=True)
class Table:
    upper: int
    load: int
    targets: tuple[int, ...]

def direct_target(word: int, address: int) -> int | None:
    """Decode only architectural direct control transfers, not a full CFG."""
    op, rs, rt = word >> 26, (word >> 21) & 31, (word >> 16) & 31
    if op in (2, 3):
        return ((address + 4) & 0xF0000000) | ((word & 0x03FFFFFF) << 2)
    conditional = (op in (4, 5, 6, 7, 20, 21, 22, 23)
                   or (op == 1 and rt in (0, 1, 2, 3, 16, 17, 18, 19))
                   or (op in (16, 17, 18) and rs == 8))
    if conditional:
        displacement = word & 0xFFFF
        if displacement & 0x8000:
            displacement -= 0x10000
        return address + 4 + displacement * 4
    return None


def is_transfer(word: int, address: int) -> bool:
    return (direct_target(word, address) is not None
            or (word >> 26 == 0 and (word & 63) in (8, 9)))


def reference_tables(assembly: str, code: bytes, data: bytes,
                     code_vram: int, data_vram: int) -> tuple[int, list[Table]]:
    rows = list(re.finditer(
        r"(?m)^[ \t]*/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})\s*\*/[^\n]*", assembly))
    if not rows:
        raise TableEvidenceError("switch reference has no raw instruction addresses")
    start = int(rows[0][1], 16)
    addresses = {int(row[1], 16) for row in rows}
    words = [int(row[2], 16) for row in rows]
    for index, row in enumerate(rows):
        address = int(row[1], 16)
        if (address != start + index * 4 or address < code_vram
                or code[address - code_vram:address - code_vram + 4] != bytes.fromhex(row[2])):
            raise TableEvidenceError("switch raw instruction bytes differ from US ROM")
    rs = lambda word: (word >> 21) & 31
    rt = lambda word: (word >> 16) & 31
    rd = lambda word: (word >> 11) & 31
    direct_edges = [direct_target(word, start + i * 4) for i, word in enumerate(words)]
    tables = []
    for index, row in enumerate(rows):
        name = re.search(r"%lo\(jtbl_([0-9A-Fa-f]{8})(?:_\w+)?\)", row[0])
        if name is None:
            continue
        if index < 5 or index + 2 >= len(rows):
            raise TableEvidenceError("truncated switch dispatch")
        if is_transfer(words[index + 2], start + (index + 2) * 4):
            raise TableEvidenceError("control transfer in switch jump delay slot")
        shift, upper, add, load, jump = words[index - 3:index + 2]
        if not (shift >> 26 == 0 and shift & 0x7FF == 0x80 and rs(shift) == 0 and rd(shift) != 0
                and upper >> 26 == 0x0F and rs(upper) == 0 and rt(upper) not in (0, rd(shift))
                and add >> 26 == 0 and add & 0x7FF == 0x21 and rd(add) != 0
                and {rs(add), rt(add)} == {rt(upper), rd(shift)}
                and load >> 26 == 0x23 and rs(load) == rd(add) and rt(load) != 0
                and jump == ((rt(load) << 21) | 8)):
            raise TableEvidenceError("unsupported switch dispatch shape")
        counts = []
        # Permit up to three independent instructions before the branch and
        # one delay slot before the shift. The boolean xori/sltiu scheduling
        # in func_1511DD98 cannot overwrite the index or guard result. swc1
        # names an FPR in rt, not a protected GPR. Direct-edge vetoes below
        # reject bypasses for the new schedule, without inferring a full CFG.
        for guard_index in range(max(0, index - 9), index - 4):
            guard = words[guard_index]
            if not (guard >> 26 == 0x0B and rs(guard) == rt(shift) and rt(guard) != 0
                    and rt(guard) != rs(guard) and 0 < (guard & 0xFFFF) <= 1024):
                continue
            for branch_index in (index - 4, index - 5):
                if not guard_index < branch_index <= guard_index + 4:
                    continue
                branch = words[branch_index]
                if not (branch >> 26 == 4 and rs(branch) == rt(guard) and rt(branch) == 0
                        and 0 < (branch & 0xFFFF) < 0x8000
                        and start + branch_index * 4 + 4 + (branch & 0xFFFF) * 4 in addresses):
                    continue
                independent = words[guard_index + 1:branch_index] + words[branch_index + 1:index - 3]
                extended = (branch_index - guard_index > 3
                            or any(word >> 26 in (0x0E, 0x0B) for word in independent))
                # New boolean schedules require a single direct entry at the
                # guard. Legacy forms include reviewed guard-in-delay and
                # loop-entry shapes; do not reinterpret those with this local
                # check. Resolving arbitrary indirect entries is not a CFG
                # proof supplied by this recognizer.
                if extended:
                    guard_address = start + guard_index * 4
                    dispatch_end = start + (index + 2) * 4  # jr delay slot
                    if (guard_index and is_transfer(words[guard_index - 1], guard_address - 4)
                            or any(target is not None and guard_address < target <= dispatch_end
                                   for target in direct_edges)):
                        continue
                protected = {rs(guard), rt(guard)}
                if any(not (word == 0 or word >> 26 in (0x28, 0x29, 0x2B, 0x39)
                            or (word >> 26 in (0x23, 0x0E, 0x0B) and rt(word) not in protected))
                       for word in independent):
                    continue
                counts.append(guard & 0xFFFF)
        if len(counts) != 1:
            raise TableEvidenceError("switch bound is missing or ambiguous")
        lower = load & 0xFFFF
        address = (((upper & 0xFFFF) << 16) + (lower if lower < 0x8000 else lower - 0x10000)) & 0xFFFFFFFF
        offset = address - data_vram
        if address != int(name[1], 16) or offset < 0 or offset % 4 or offset + counts[0] * 4 > len(data):
            raise TableEvidenceError("switch table outside ROM game data")
        targets = tuple(int.from_bytes(data[pos:pos + 4], "big")
                        for pos in range(offset, offset + counts[0] * 4, 4))
        if any(target not in addresses for target in targets):
            raise TableEvidenceError("ROM case target outside registered function")
        tables.append(Table((index - 2) * 4, index * 4, targets))
    if not tables:
        raise TableEvidenceError("switch reference has no supported dispatch")
    return start, tables


class Object32:
    """Minimal ELF32 big-endian MIPS REL reader; unsupported formats fail closed."""
    def __init__(self, data: bytes):
        self.data = data
        header = self.unpack(">16sHHIIIIIHHHHHH", 0)
        if (header[0][:7] != b"\x7fELF\x01\x02\x01" or header[1:4] != (1, 8, 1)
                or header[11] != 40 or header[12] == 0):
            raise TableEvidenceError("candidate is not a supported ELF32 MIPS REL object")
        self.sections = [self.unpack(">10I", header[6] + 40 * i) for i in range(header[12])]
        self.symbols = {}
        self.relocations = {}
        for section in self.sections:
            if section[1] != 2:
                continue
            if section[9] != 16 or section[5] % 16:
                raise TableEvidenceError("invalid symbol table extent")
            strings = self.section(section[6])
            symbols = []
            for offset in range(0, section[5], 16):
                name, value, size, info, other, shndx = self.unpack(">IIIBBH", section[4] + offset)
                end = strings.find(b"\0", name)
                if end < name:
                    raise TableEvidenceError("invalid symbol name")
                symbols.append((strings[name:end].decode("ascii"), value, size, shndx))
            self.symbols[self.sections.index(section)] = symbols
        for section in self.sections:
            if section[1] == 4:
                raise TableEvidenceError("RELA relocations are unsupported")
            if section[1] != 9:
                continue
            if section[9] != 8 or section[5] % 8 or section[6] not in self.symbols:
                raise TableEvidenceError("invalid relocation table")
            symbols = self.symbols[section[6]]
            for offset in range(0, section[5], 8):
                location, info = self.unpack(">II", section[4] + offset)
                if info >> 8 >= len(symbols):
                    raise TableEvidenceError("invalid relocation symbol")
                key = (section[7], location)
                if key in self.relocations:
                    raise TableEvidenceError("ambiguous candidate relocation")
                self.relocations[key] = (info & 255, symbols[info >> 8])

    def unpack(self, format: str, offset: int):
        if offset < 0 or offset + struct.calcsize(format) > len(self.data):
            raise TableEvidenceError("truncated candidate object")
        return struct.unpack_from(format, self.data, offset)

    def section(self, index: int) -> bytes:
        if not 0 < index < len(self.sections):
            raise TableEvidenceError("invalid candidate section")
        section = self.sections[index]
        if section[1] == 8 or section[4] + section[5] > len(self.data):
            raise TableEvidenceError("candidate section has no complete payload")
        return self.data[section[4]:section[4] + section[5]]

    def word(self, section: int, offset: int) -> int:
        data = self.section(section)
        if offset < 0 or offset % 4 or offset + 4 > len(data):
            raise TableEvidenceError("candidate word outside section")
        return int.from_bytes(data[offset:offset + 4], "big")

    def relocation(self, section: int, offset: int, kind: int):
        relocation = self.relocations.get((section, offset))
        if relocation is None or relocation[0] != kind:
            raise TableEvidenceError(f"missing R_MIPS relocation {kind} at 0x{offset:X}")
        return relocation[1]


def verify_object(data: bytes, symbol: str, raw_start: int, tables: list[Table], expected_size: int) -> None:
    obj = Object32(data)
    functions = [s for syms in obj.symbols.values() for s in syms if s[0] == symbol]
    if len(functions) != 1:
        raise TableEvidenceError("candidate function symbol is missing or ambiguous")
    _, origin, size, text = functions[0]
    if size != expected_size:
        raise TableEvidenceError("candidate function extent differs from registered span")
    for table in tables:
        high = obj.relocation(text, origin + table.upper, 5)
        low = obj.relocation(text, origin + table.load, 6)
        if high != low:
            raise TableEvidenceError("switch HI16/LO16 symbols disagree")
        upper = obj.word(text, origin + table.upper) & 0xFFFF
        lower = obj.word(text, origin + table.load) & 0xFFFF
        offset = high[1] + (upper << 16) + (lower if lower < 0x8000 else lower - 0x10000)
        for index, target in enumerate(table.targets):
            position = offset + index * 4
            case = obj.relocation(high[3], position, 2)
            relative = case[1] + obj.word(high[3], position) - origin
            if case[3] != text or not 0 <= relative < expected_size or relative % 4:
                raise TableEvidenceError("candidate case target is outside the function")
            if raw_start + relative != target:
                raise TableEvidenceError(f"switch table case {index} differs from US ROM")


def verify_candidate(candidate: Path, symbol: str, assembly: Path, expected_size: int) -> None:
    raw = assembly.read_text()
    if not re.search(r"%lo\(jtbl_", raw):
        return
    layout = json.loads((ROOT / "config/rzip_layouts.json").read_text())["profiles"]["us"]
    rom, _ = rzip_archive.normalize_rom((ROOT / layout["default_rom"]).read_bytes())
    if hashlib.sha1(rom).hexdigest() not in layout["normalized_sha1"]:
        raise TableEvidenceError("switch verification requires a checksum-validated US ROM")
    game = rzip_archive.parse_game_archive(rom[int(layout["game_start"], 0):int(layout["game_end"], 0)])
    start, tables = reference_tables(raw, game.code, game.data,
                                    int(layout["game_vram"], 0), int(layout["game_data_vram"], 0))
    verify_object(candidate.read_bytes(), symbol, start, tables, expected_size)
