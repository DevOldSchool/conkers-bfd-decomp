"""Candidate-only IDO data symbols for stock objdiff; no ROM/reference access.

Recognizes one conservative switch-dispatch shape and adjacent LUI/LDC1 pairs.
The caller supplies actual linked section bases for names, never object extents.
Copied jump-table REL words may be canonicalized with an independent semantic
check; runtime inputs are never rewritten.
"""
from __future__ import annotations

from dataclasses import asdict, dataclass
import hashlib
import struct


class AnnotationError(ValueError):
    pass


class Elf:
    """Strict ELF32 big-endian MIPS reader, independent of project/reference code."""
    def __init__(self, data: bytes, elf_type: int = 1):
        self.data = data
        self.header = self.unpack('>16sHHIIIIIHHHHHH', 0)
        h = self.header
        if (h[0][:7] != b'\x7fELF\x01\x02\x01' or h[1:4] != (elf_type, 8, 1)
                or h[8] != 52 or h[11] != 40 or not 0 < h[13] < h[12]
                or (elf_type == 1 and (h[5] or h[10]))):
            raise AnnotationError('unsupported annotation ELF')
        if h[6] < 52 or h[6] + h[12] * 40 > len(data):
            raise AnnotationError('invalid section header range')
        self.headers = [self.unpack('>10I', h[6] + i * 40) for i in range(h[12])]
        # Rewriting must not alias another section, header or payload.
        occupied = [(0, 52), (h[6], h[6] + h[12] * 40)]
        for sh in self.headers[1:]:
            if sh[1] != 8 and sh[5]:
                start, end = sh[4], sh[4] + sh[5]
                if end > len(data) or (elf_type == 1 and any(start < b and a < end for a, b in occupied)):
                    raise AnnotationError('overlapping or truncated sections')
                occupied.append((start, end))
        self.names = [self.string(self.payload(h[13]), s[0]) for s in self.headers]
        if len(set(self.names)) != len(self.names):
            raise AnnotationError('duplicate section names')
        tables = [i for i, s in enumerate(self.headers) if s[1] == 2]
        if len(tables) != 1:
            raise AnnotationError('annotation needs one symbol table')
        self.symtab = tables[0]
        sh = self.headers[self.symtab]
        self.strtab = sh[6]
        if not 0 < self.strtab < len(self.headers) or self.strtab == h[13]:
            raise AnnotationError('invalid symbol string table')
        if sh[9] != 16 or sh[5] % 16 or self.headers[self.strtab][1] != 3:
            raise AnnotationError('invalid symbol table')
        self.symbols = []
        for at in range(0, sh[5], 16):
            sym = self.unpack('>IIIBBH', sh[4] + at)
            self.symbols.append((self.string(self.payload(self.strtab), sym[0]), *sym[1:]))
        self.relocations = {}
        for section in self.headers:
            if section[1] == 4:
                raise AnnotationError('RELA is unsupported')
            if section[1] != 9:
                continue
            if section[9] != 8 or section[5] % 8 or section[6] != self.symtab:
                raise AnnotationError('invalid relocation table')
            for at in range(0, section[5], 8):
                offset, info = self.unpack('>II', section[4] + at)
                if info >> 8 >= len(self.symbols):
                    raise AnnotationError('invalid relocation symbol')
                key = (section[7], offset)
                self.word(*key)
                if key in self.relocations:
                    raise AnnotationError('duplicate relocation')
                self.relocations[key] = (info & 255, info >> 8)

    def unpack(self, fmt: str, offset: int):
        size = struct.calcsize(fmt)
        if offset < 0 or offset + size > len(self.data):
            raise AnnotationError('truncated ELF')
        return struct.unpack_from(fmt, self.data, offset)

    @staticmethod
    def string(data: bytes, offset: int) -> str:
        end = data.find(b'\0', offset)
        if offset < 0 or end < offset:
            raise AnnotationError('invalid ELF string')
        return data[offset:end].decode('ascii')

    def payload(self, index: int) -> bytes:
        if not 0 <= index < len(self.headers):
            raise AnnotationError('invalid section index')
        s = self.headers[index]
        if s[1] == 8:
            return b''
        if s[4] + s[5] > len(self.data):
            raise AnnotationError('truncated section')
        return self.data[s[4]:s[4] + s[5]]

    def word(self, section: int, offset: int) -> int:
        payload = self.payload(section)
        if offset < 0 or offset % 4 or offset + 4 > len(payload):
            raise AnnotationError('relocation word outside section')
        return int.from_bytes(payload[offset:offset + 4], 'big')


def linked_section_bases(candidate: bytes, linked: bytes) -> dict[str, int]:
    """Derive placement from candidate-owned named anchors in the runtime ELF.

    This adapter reads no reference names, ROM bytes, splat output or layout file.
    Every available candidate anchor in the section must agree on its base.
    """
    obj, runtime = Elf(candidate), Elf(linked, 2)
    addresses = {}
    for name, value, _, _, _, section in runtime.symbols:
        if name and 0 < section < len(runtime.headers):
            addresses.setdefault(name, set()).add(value)
    bases = {}
    for index, section in enumerate(obj.names):
        if section not in ('.text', '.rodata', '.data') or not obj.headers[index][5]:
            continue
        values = []
        for name, value, size, info, _, shndx in obj.symbols:
            if shndx != index or info & 15 == 3 or not name:
                continue
            linked_values = addresses.get(name, set())
            if len(linked_values) != 1:
                raise AnnotationError('missing or ambiguous runtime anchor: ' + name)
            values.append(next(iter(linked_values)) - value)
        if not values or len(set(values)) != 1:
            raise AnnotationError('runtime anchors do not establish one section base')
        if values[0] < 0 or values[0] + obj.headers[index][5] > 0x100000000:
            raise AnnotationError('linked section address outside MIPS32')
        bases[section] = values[0]
    return bases


@dataclass(frozen=True)
class Symbol:
    section: str
    offset: int
    size: int
    name: str
    kind: str


def rs(w): return (w >> 21) & 31

def rt(w): return (w >> 16) & 31

def rd(w): return (w >> 11) & 31


def signed16(w):
    return (w & 0xFFFF) - (0x10000 if w & 0x8000 else 0)


def references(obj: Elf) -> list[tuple[int, int, int, int, int]]:
    """Return (source section, high offset, low offset, target section, addend)."""
    pending, result = {}, []
    for (section, offset), (kind, symbol) in sorted(obj.relocations.items()):
        target = obj.symbols[symbol]
        # Only references to the read-only section itself can be anonymous here.
        if target[3] & 15 != 3 or target[5] >= len(obj.names) or obj.names[target[5]] != '.rodata':
            continue
        key = (section, symbol)
        if kind == 5:
            pending.setdefault(key, []).append(offset)
        elif kind == 6:
            highs = pending.pop(key, [])
            if not highs:
                raise AnnotationError('unpaired read-only LO16 relocation')
            for high in highs:
                upper, lower = obj.word(section, high), obj.word(section, offset)
                if upper >> 26 != 15 or rs(upper) != 0 or rt(upper) == 0:
                    raise AnnotationError('HI16 relocation is not a LUI')
                addend = target[1] + (((upper & 0xFFFF) << 16) + signed16(lower))
                if not 0 <= addend < obj.headers[target[5]][5]:
                    raise AnnotationError('read-only relocation addend outside section')
                result.append((section, high, offset, target[5], addend))
        elif kind == 2:
            addend = target[1] + obj.word(section, offset)
            if not 0 <= addend < obj.headers[target[5]][5]:
                raise AnnotationError('read-only pointer outside section')
            result.append((section, offset, offset, target[5], addend))
        else:
            raise AnnotationError('unsupported read-only relocation')
    if pending:
        raise AnnotationError('unpaired read-only HI16 relocation')
    return result


def switch_size(obj: Elf, text: int, high: int, low: int, rodata: int, start: int) -> int:
    if low < 20 or high != low - 8:
        raise AnnotationError('unsupported switch dispatch')
    guard, branch, shift, upper, add, load, jump, delay = [
        obj.word(text, at) for at in range(low - 20, low + 12, 4)]
    if not (guard >> 26 == 11 and rt(guard) != 0 and rs(guard) != rt(guard)
            and branch >> 26 == 4 and rs(branch) == rt(guard) and rt(branch) == 0
            and 0 < signed16(branch) and low + 8 < low - 12 + signed16(branch) * 4 < obj.headers[text][5]
            and shift >> 26 == 0 and shift & 0x7FF == 0x80 and rs(shift) == 0
            and rt(shift) == rs(guard) and rd(shift) != 0
            and rt(upper) != rd(shift)
            and add >> 26 == 0 and add & 0x7FF == 0x21
            and {rs(add), rt(add)} == {rt(upper), rd(shift)} and rd(add) != 0
            and load >> 26 == 35 and rs(load) == rd(add) and rt(load) != 0
            and jump == (rt(load) << 21 | 8) and delay == 0):
        raise AnnotationError('unsupported switch dispatch/bound')
    # Count the relocation run, independently of the instruction's switch bound.
    end = start
    while (rodata, end) in obj.relocations:
        kind, symbol = obj.relocations[(rodata, end)]
        target = obj.symbols[symbol]
        if kind != 2 or target[5] != text:
            raise AnnotationError('switch entry is not an R_MIPS_32 text pointer')
        destination = target[1] + obj.word(rodata, end)
        if destination % 4 or not 0 <= destination < obj.headers[text][5]:
            raise AnnotationError('switch destination outside candidate text')
        end += 4
    if ((rodata, start - 4) in obj.relocations or not end > start
            or end - start != (guard & 0xFFFF) * 4):
        raise AnnotationError('switch relocation count differs from dispatch bound')
    return end - start


def discover(candidate: bytes, bases: dict[str, int]) -> list[Symbol]:
    obj = Elf(candidate)
    refs = references(obj)
    found = {}
    for text, high, low, section, offset in refs:
        if obj.names[text] != '.text' or high == low:
            continue
        overlaps = [s for s in obj.symbols if s[5] == section and s[3] & 15 != 3
                    and s[1] <= offset < s[1] + s[2]]
        upper, lower = obj.word(text, high), obj.word(text, low)
        if lower >> 26 == 53:
            if low != high + 4 or rs(lower) != rt(upper):
                raise AnnotationError('unsupported anonymous double load')
            size, kind, prefix, alignment = 8, 'double', 'D', 8
        elif lower >> 26 == 35:
            size = switch_size(obj, text, high, low, section, offset)
            kind, prefix, alignment = 'jump_table', 'jtbl', 4
        else:
            if overlaps:
                continue
            raise AnnotationError('unsupported anonymous read-only reference')
        section_name = obj.names[section]
        if section_name not in bases or not 0 <= bases[section_name] <= 0xFFFFFFFF:
            raise AnnotationError('missing actual linked section base')
        if (offset % alignment or (bases[section_name] + offset) % alignment
                or offset + size > obj.headers[section][5]
                or bases[section_name] + offset + size > 0x100000000):
            raise AnnotationError('anonymous object extent/alignment invalid')
        symbol = Symbol(section_name, offset, size, f'{prefix}_{bases[section_name] + offset:08X}', kind)
        key = (section, offset)
        if key in found and found[key] != symbol:
            raise AnnotationError('ambiguous anonymous extent')
        found[key] = symbol
    ordered = sorted(found.items())
    for (section, offset), symbol in ordered:
        for name, value, size, info, other, shndx in obj.symbols:
            if name == symbol.name and (shndx, value, size, info, other) != (section, offset, symbol.size, 0x11, 0):
                raise AnnotationError('annotation name collision')
            if (shndx == section and info & 15 != 3
                    and value < offset + symbol.size and offset < value + max(1, size)):
                if (name, value, size, info, other) != (symbol.name, offset, symbol.size, 0x11, 0):
                    raise AnnotationError('anonymous extent overlaps a named symbol')
        for (other_section, other_offset), other in ordered:
            if section == other_section and offset < other_offset < offset + symbol.size:
                raise AnnotationError('anonymous extents overlap')
        if any(target == section and offset < addend < offset + symbol.size
               for _, _, _, target, addend in refs):
            raise AnnotationError('relocation points inside anonymous object')
        if symbol.kind == 'double' and any(s == section and offset <= at < offset + symbol.size
                                          for s, at in obj.relocations):
            raise AnnotationError('double contains relocations')
    return [symbol for _, symbol in ordered]


def verify_invariance(before: bytes, after: bytes, additions: list[Symbol]) -> None:
    left, right = Elf(before), Elf(after)
    if left.header != right.header or left.names != right.names:
        raise AnnotationError('annotation changed ELF header or sections')
    allowed = {left.symtab, left.strtab}
    for i, (a, b) in enumerate(zip(left.headers, right.headers, strict=True)):
        if i in allowed:
            if a[:4] + a[6:] != b[:4] + b[6:]:
                raise AnnotationError('annotation changed symbol table semantics')
        elif a != b or left.payload(i) != right.payload(i):
            raise AnnotationError('annotation changed section bytes or headers')
    if (right.symbols[:len(left.symbols)] != left.symbols
            or right.relocations != left.relocations
            or not right.payload(right.strtab).startswith(left.payload(left.strtab))):
        raise AnnotationError('annotation changed existing symbols or relocations')
    expected = [(s.name, s.offset, s.size, 0x11, 0, left.names.index(s.section)) for s in additions]
    if right.symbols[len(left.symbols):] != expected:
        raise AnnotationError('annotation added unexpected symbols')


def annotate(candidate: bytes, bases: dict[str, int]) -> tuple[bytes, dict]:
    """Pure bytes-to-bytes annotation. No filesystem, subprocess or network I/O."""
    obj = Elf(candidate)
    symbols = discover(candidate, bases)
    existing = {s[0] for s in obj.symbols}
    additions = [s for s in symbols if s.name not in existing]
    result = candidate
    if additions:
        strings = bytearray(obj.payload(obj.strtab))
        entries = bytearray(obj.payload(obj.symtab))
        for symbol in additions:
            entries.extend(struct.pack('>IIIBBH', len(strings), symbol.offset, symbol.size,
                                       0x11, 0, obj.names.index(symbol.section)))
            strings.extend(symbol.name.encode('ascii') + b'\0')
        data = bytearray(candidate)
        for index, payload in ((obj.symtab, entries), (obj.strtab, strings)):
            data.extend(bytes((-len(data)) % max(1, obj.headers[index][8])))
            offset = len(data)
            data.extend(payload)
            struct.pack_into('>II', data, obj.header[6] + index * 40 + 16, offset, len(payload))
        result = bytes(data)
    verify_invariance(candidate, result, additions)
    return result, {'method': 'candidate-relocations-and-instructions',
                    'symbols': [asdict(s) for s in symbols],
                    'added_symbols': len(additions), 'invariance_verified': True,
                    'input_sha256': hashlib.sha256(candidate).hexdigest(),
                    'output_sha256': hashlib.sha256(result).hexdigest()}


def destination_labels(obj: Elf, symbols: list[Symbol], bases: dict[str, int]) -> list[tuple]:
    """Name only instruction destinations of independently discovered tables."""
    labels = set()
    for table in symbols:
        if table.kind != 'jump_table':
            continue
        section = obj.names.index(table.section)
        for offset in range(table.offset, table.offset + table.size, 4):
            kind, index = obj.relocations[(section, offset)]
            target = obj.symbols[index]
            if kind != 2 or obj.names[target[5]] != '.text':
                raise AnnotationError('non-code switch destination')
            destination = target[1] + obj.word(section, offset)
            if '.text' not in bases or not 0 <= bases['.text'] + destination < 0x100000000:
                raise AnnotationError('missing or invalid actual code base')
            name = f'.L{bases[".text"] + destination:08X}'
            label = (name, destination, 0, 0x10, 0, target[5])
            existing = [s for s in obj.symbols if s[0] == name]
            if existing and existing != [label]:
                raise AnnotationError('code label collision')
            labels.add(label)
    return sorted(labels, key=lambda s: (s[5], s[1], s[0]))


def add_labels(candidate: bytes, labels: list[tuple]) -> bytes:
    obj = Elf(candidate)
    additions = [s for s in labels if s not in obj.symbols]
    if not additions:
        return candidate
    strings, symbols = bytearray(obj.payload(obj.strtab)), bytearray(obj.payload(obj.symtab))
    for name, value, size, info, other, section in additions:
        symbols.extend(struct.pack('>IIIBBH', len(strings), value, size, info, other, section))
        strings.extend(name.encode('ascii') + b'\0')
    output = bytearray(candidate)
    for index, payload in ((obj.symtab, symbols), (obj.strtab, strings)):
        output.extend(bytes((-len(output)) % max(1, obj.headers[index][8])))
        start = len(output)
        output.extend(payload)
        struct.pack_into('>II', output, obj.header[6] + index * 40 + 16, start, len(payload))
    return bytes(output)


def verify_canonicalization(before: bytes, after: bytes, bases: dict[str, int]) -> dict:
    """Independently audit the only permitted changes and every S + A value.

    No transform-generated change list is trusted. All allowed words and symbol
    additions are re-derived from the original candidate and its dispatch bounds.
    Unchanged relocations must be byte-identical; rewritten R_MIPS_32 entries must
    keep type, source location, target section and effective destination. Section
    base cancels, so the proof holds for any legal placement of the target section.
    """
    left, right = Elf(before), Elf(after)
    symbols = discover(before, bases)
    labels = destination_labels(left, symbols, bases)
    additions = [(s.name, s.offset, s.size, 0x11, 0, left.names.index(s.section))
                 for s in symbols if s.name not in {v[0] for v in left.symbols}]
    additions += [s for s in labels if s not in left.symbols]
    if (left.header != right.header or left.names != right.names
            or right.symbols != left.symbols + additions
            or right.payload(right.strtab) != left.payload(left.strtab) +
                b''.join(s[0].encode('ascii') + b'\0' for s in additions)
            or set(left.relocations) != set(right.relocations)):
        raise AnnotationError('canonicalization changed object structure or symbols')
    words = {(left.names.index(s.section), at) for s in symbols if s.kind == 'jump_table'
             for at in range(s.offset, s.offset + s.size, 4)}
    # Build permitted replacement bytes independently from actual output values.
    payloads = {i: bytearray(left.payload(i)) for i in range(len(left.headers))}
    for key, (kind, index) in left.relocations.items():
        new_kind, new_index = right.relocations[key]
        if key not in words:
            if (kind, index) != (new_kind, new_index):
                raise AnnotationError('unrelated relocation changed')
            continue
        section, offset = key
        old_target, new_target = left.symbols[index], right.symbols[new_index]
        old_destination = old_target[1] + left.word(section, offset)
        new_destination = new_target[1] + right.word(section, offset)
        if (kind != 2 or new_kind != kind or old_target[5] != new_target[5]
                or old_destination != new_destination or right.word(section, offset) != 0
                or new_target not in labels):
            raise AnnotationError('R_MIPS_32 destination changed')
        struct.pack_into('>I', payloads[section], offset, 0)
    for i, header in enumerate(left.headers):
        if header[1] == 9:
            for offset in range(0, header[5], 8):
                location, info = struct.unpack_from('>II', payloads[i], offset)
                key = (header[7], location)
                if key in words:
                    kind, index = right.relocations[key]
                    struct.pack_into('>I', payloads[i], offset + 4, index << 8 | kind)
        other = right.headers[i]
        if i in (left.symtab, left.strtab):
            if header[:4] + header[6:] != other[:4] + other[6:]:
                raise AnnotationError('symbol table header semantics changed')
        elif header != other or bytes(payloads[i]) != right.payload(i):
            raise AnnotationError('unapproved section/header byte change')
    return {'relocations_verified': len(left.relocations),
            'canonical_table_words': len(words), 'effective_destinations_identical': True,
            'other_sections_identical': True, 'existing_symbols_identical': True}


def canonicalize(candidate: bytes, bases: dict[str, int]) -> tuple[bytes, dict]:
    """Annotate a comparison copy, then move each table REL addend into a label."""
    annotated, proof = annotate(candidate, bases)
    obj = Elf(annotated)
    symbols = discover(annotated, bases)
    labels = destination_labels(obj, symbols, bases)
    labeled = add_labels(annotated, labels)
    obj = Elf(labeled)
    data = bytearray(labeled)
    words = {(obj.names.index(s.section), at) for s in symbols if s.kind == 'jump_table'
             for at in range(s.offset, s.offset + s.size, 4)}
    for header in obj.headers:
        if header[1] != 9:
            continue
        for at in range(header[4], header[4] + header[5], 8):
            offset, info = struct.unpack_from('>II', labeled, at)
            key = (header[7], offset)
            if key not in words:
                continue
            target = obj.symbols[info >> 8]
            destination = target[1] + obj.word(*key)
            label = next(s for s in labels if s[5] == target[5] and s[1] == destination)
            index = obj.symbols.index(label)
            struct.pack_into('>I', data, obj.headers[key[0]][4] + offset, 0)
            struct.pack_into('>I', data, at + 4, index << 8 | 2)
    result = bytes(data)
    semantic_proof = verify_canonicalization(candidate, result, bases)
    proof['annotation_invariance_verified'] = proof.pop('invariance_verified')
    return result, {**proof, 'method': 'candidate-only-ido-symbols-and-R_MIPS_32',
                    'output_sha256': hashlib.sha256(result).hexdigest(),
                    'section_bases': bases, 'destination_labels': [s[0] for s in labels],
                    'semantic_verification': semantic_proof}
