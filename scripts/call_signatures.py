"""Bounded call-context recovery for raw MIPS o32 wrappers.

Allowed-source C signatures take precedence, followed by reviewed SDK aliases
and unique project signatures. The raw fallback recognizes a single-call
integer-register wrapper and a callee's contiguous argument-home spills. It is
an ABI call-site view, not a claim about original typedefs or return types: a
void declaration is used only for a wrapper whose decompiler discards the call
result. All generated C still requires the independent focused and layout gates.
"""
from __future__ import annotations

import hashlib
import json
import re
from dataclasses import dataclass
from functools import lru_cache, wraps
from pathlib import Path

import candidate_syntax
import declaration_facts


WORD_TYPES = frozenset(('s32', 'u32', 'int', 'unsigned int', 'signed int'))
SCALAR_TYPES = WORD_TYPES | {'void', 's8', 'u8', 's16', 'u16', 's64', 'u64', 'f32', 'f64', 'float', 'double'}
ABI_MARKER = 'CONKER_ABI_DISCARDED_RETURN'
SDK_ALIAS_MAP = 'config/game/us-sdk.ld'
SDK_MEMORY_HEADER = 'lib/ultralib/include/compiler/ido/memory.h'
SDK_ALIAS_INPUTS = (SDK_ALIAS_MAP, SDK_MEMORY_HEADER)


def without_abi_declarations(text: str) -> str:
    """A discard-only call view must never become general signature evidence."""
    return '\n'.join(line for line in text.splitlines() if ABI_MARKER not in line)


@dataclass(frozen=True)
class Signature:
    result: str
    arguments: tuple[str, ...]

    def declaration(self, symbol: str) -> str:
        return f"{self.result} {symbol}({', '.join(self.arguments) or 'void'});"


def c_type(text: str, *, parameter: bool = False) -> str | None:
    words = text.split()
    if not words:
        return None
    # Accept only self-contained scalar types and void/scalar pointers. Importing
    # an unrelated source-local typedef or structure would invent visibility.
    for drop in (0, 1) if parameter else (0,):
        parts = words[:-drop] if drop else words
        if drop and not re.fullmatch(r'[A-Za-z_]\w*', words[-1]):
            continue
        raw = ' '.join(parts).replace(' *', '*')
        base = raw.rstrip('*').strip()
        pointers = raw[len(base):]
        supported = base in SCALAR_TYPES or (
            base.startswith('const ') and base[6:] in SCALAR_TYPES and pointers in ('*', '**'))
        if supported and pointers in ('', '*', '**'):
            return base + (' ' + raw[len(base):] if raw[len(base):] else '')
    return None


def source_signatures(text: str, wanted: set[str] | None = None) -> dict[str, set[Signature | None]]:
    """Collect supported external signatures without importing another scope."""
    found: dict[str, set[Signature | None]] = {}
    # Remove comments before interpreting preprocessor lines.
    text = without_abi_declarations(text)
    text = re.sub(r'/\*.*?\*/|//[^\n]*', '', text, flags=re.S)
    text = declaration_facts.active_text(text)
    items = candidate_syntax.tokens(text)
    start = depth = 0
    for i, token in enumerate(items):
        if depth == 0 and token.text in (';', '{'):
            words = [t.text for t in items[start:i]]
            if '(' in words:
                opening = words.index('(')
                if opening and words[-1:] == [')']:
                    symbol = words[opening-1]
                    if wanted is None or symbol in wanted:
                        prefix = words[:opening-1]
                        if 'static' in prefix:
                            found.setdefault(symbol, set()).add(None)
                        elif 'typedef' not in prefix:
                            result = c_type(' '.join(w for w in prefix if w != 'extern'))
                            arguments = declaration_facts.split_arguments(' '.join(words[opening+1:-1]))
                            types = tuple(c_type(a, parameter=True) for a in arguments)
                            if types == ('void',):
                                types = ()
                            sig = Signature(result, types) if result is not None and arguments and all(t is not None and t != 'void' for t in types) else None
                            found.setdefault(symbol, set()).add(sig)
            start = i + 1
        if token.text == '{':
            depth += 1
        elif token.text == '}':
            depth -= 1
            if depth == 0:
                start = i + 1
    return found


def sdk_alias_signatures(root: Path, wanted: set[str] | None = None, *,
                         profile: str = 'us') -> dict[str, Signature]:
    """Recover the reviewed memcpy alias from its US binding and SDK header.

    This deliberately supports only memcpy. Other SDK names, data addresses,
    expressions, ambiguous bindings and unavailable/changed header contracts
    need separate review. No SDK typedef is imported into a game source file.
    """
    if profile != 'us':
        return {}
    try:
        bindings = re.sub(r'/\*.*?\*/|//[^\n]*', '',
                          (root / SDK_ALIAS_MAP).read_text(encoding='utf-8'), flags=re.S)
        header = re.sub(r'/\*.*?\*/|//[^\n]*', '',
                        (root / SDK_MEMORY_HEADER).read_text(encoding='utf-8'), flags=re.S)
    except (OSError, UnicodeDecodeError):
        return {}
    addresses: dict[str, list[int | None]] = {}
    # The map also contains SECTIONS, ASSERT and symbolic aliases. Only take
    # literal top-level assignments; never evaluate those other linker forms.
    items = candidate_syntax.tokens(bindings)
    depth = 0
    for i, token in enumerate(items):
        if (depth == 0 and candidate_syntax.IDENTIFIER.fullmatch(token.text)
                and i + 1 < len(items) and items[i + 1].text == '='):
            end = i + 2
            while end < len(items) and items[end].text not in (';', '{', '}'):
                end += 1
            value = None
            if (end == i + 3 and end < len(items) and items[end].text == ';'
                    and re.fullmatch(r'0x[0-9A-Fa-f]{1,8}', items[i + 2].text)):
                value = int(items[i + 2].text, 16)
            addresses.setdefault(token.text, []).append(value)
        depth += (token.text == '{') - (token.text == '}')
    targets = addresses.get('memcpy', [])
    if len(targets) != 1 or targets[0] is None:
        return {}
    address = targets[0]
    if address == 0 or address % 4 or sum(values.count(address) for values in addresses.values()) != 1:
        return {}
    symbol = f'func_{address:08X}'
    if wanted is not None and symbol not in wanted:
        return {}
    header = declaration_facts.active_text(header)
    # IDO's SDK header defines size_t as unsigned int. Keep the canonical
    # project's u32 spelling, and preserve const on memcpy's source pointer.
    typedefs = re.findall(r'\btypedef\s+([^;{}]+?)\s+size_t\s*;', header)
    if [t.strip() for t in typedefs] not in (['unsigned'], ['unsigned int']):
        return {}
    header = re.sub(r'\bsize_t\b', 'u32', header)
    signature = Signature('void *', ('void *', 'const void *', 'u32'))
    if source_signatures(header, {'memcpy'}).get('memcpy') != {signature}:
        return {}
    return {symbol: signature}


def sdk_alias_evidence(symbol: str) -> str:
    return (f'verified SDK alias memcpy=0x{symbol.removeprefix("func_")} in {SDK_ALIAS_MAP}; '
            f'prototype and unsigned size_t in {SDK_MEMORY_HEADER}')


def signature_index(root: Path, wanted: set[str] | None = None, *,
                    source: str = "", profile: str = 'us') -> dict[str, Signature | None]:
    """Prefer the allowed source's unique signature over unrelated call views.

    A conflicting or unsupported local declaration blocks global/raw fallback.
    Without local evidence, a reviewed SDK alias precedes unrelated call views;
    otherwise the complete project must still agree.
    """
    local = source_signatures(source, wanted) if source else {}
    if wanted is not None and wanted <= local.keys():
        return {name: next(iter(values)) if len(values) == 1 else None
                for name, values in local.items()}
    sdk = sdk_alias_signatures(root, wanted, profile=profile)
    remaining = wanted - local.keys() - sdk.keys() if wanted is not None else None
    found: dict[str, set[Signature | None]] = {}
    paths = declaration_facts.evidence_files(root) if remaining is None or remaining else ()
    for path in paths:
        text = path.read_text(encoding='utf-8')
        if remaining is not None and not any(re.search(rf'\b{re.escape(s)}\b', text) for s in remaining):
            continue
        for name, values in source_signatures(text, remaining).items():
            found.setdefault(name, set()).update(values)
    found.update({name: {signature} for name, signature in sdk.items()})
    found.update(local)
    return {name: next(iter(values)) if len(values) == 1 else None for name, values in found.items()}


@dataclass(frozen=True)
class Instruction:
    op: str
    args: tuple[str, ...]


def instructions(assembly: str) -> list[Instruction] | None:
    label = re.search(r'^\s*glabel\s+\w+\s*$', assembly, re.M)
    if label is not None:
        # Full raw-reference extracts have assembler setup before the label;
        # that preamble is not part of the function's instruction stream.
        assembly = assembly[label.end():]
    result = []
    for line in assembly.splitlines():
        line = re.sub(r'/\*.*?\*/', '', line).split('#', 1)[0].strip()
        if not line or line.startswith(('glabel ', '.section ')) or line.endswith(':'):
            continue
        match = re.fullmatch(r'([a-z][a-z0-9]*)\s*(.*)', line)
        if match is None:
            return None
        result.append(Instruction(match[1], tuple(a.strip() for a in match[2].split(',') if a.strip())))
    return result


def direct_callees(assembly: str) -> set[str]:
    return set(re.findall(r'\bjal\s+([A-Za-z_]\w*)', re.sub(r'/\*.*?\*/', '', assembly)))


@lru_cache(maxsize=4)
def _inventory(path: str, stamp: int, size: int) -> list[dict]:
    return json.loads(Path(path).read_text())['functions']


def raw_callee_path(root: Path, symbol: str, profile: str = 'us') -> Path | None:
    inventory = root / 'progress/functions.json'
    if not inventory.is_file():
        return None
    stat = inventory.stat()
    entries = [e for e in _inventory(str(inventory), stat.st_mtime_ns, stat.st_size)
               if e.get('regions', {}).get(profile, {}).get('symbol') == symbol]
    if len(entries) != 1 or entries[0].get('overlay', 'main') != 'game':
        return None
    entry = entries[0]
    try:
        relative = Path(entry['source']).relative_to('src/game').with_suffix('')
    except (KeyError, ValueError):
        return None
    path = root / 'asm/nonmatchings' / relative / (entry['symbol'] + '.s')
    if not path.is_file():
        return None
    text = path.read_text()
    if re.findall(r'^\s*glabel\s+(\w+)', text, re.M) != [symbol]:
        return None
    # The raw bytes must cover this registered regional span, with consecutive
    # addresses. Labels alone are insufficient provenance for ABI inference.
    rows = re.findall(r'/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/', text)
    region = entry['regions'][profile]
    if not rows or len(rows) * 4 != region.get('size_bytes'):
        return None
    start = int(region['vram'], 0)
    if [int(row, 16) for row in rows] != list(range(start, start + len(rows)*4, 4)):
        return None
    return path


def memory(operand: str) -> tuple[int, str] | None:
    match = re.fullmatch(r'(-?(?:0x[0-9a-fA-F]+|\d+))\((\$\w+)\)', operand)
    return (int(match[1], 0), match[2]) if match else None


def reject_malformed_assembly(function):
    @wraps(function)
    def guarded(*args, **kwargs):
        try:
            return function(*args, **kwargs)
        except (ValueError, IndexError):
            return None
    return guarded


@reject_malformed_assembly
def wrapper_call(assembly: str) -> tuple[str, tuple[int | str, ...]] | None:
    """Recognize constants/moves and forwarded a0-a3 around one ordinary call."""
    code = instructions(assembly)
    if code is None or not 6 <= len(code) <= 24:
        return None
    calls = [i for i, ins in enumerate(code) if ins.op == 'jal']
    if len(calls) != 1:
        return None
    call = calls[0]
    if call + 1 >= len(code) or len(code[call].args) != 1:
        return None
    registers: dict[str, int | str] = {f'$a{i}': f'$a{i}' for i in range(4)}
    frame = 0
    saved_ra = None
    for ins in code[:call] + code[call+1:call+2]:
        op, args = ins.op, ins.args
        if op == 'nop':
            continue
        if op == 'addiu' and len(args) == 3 and args[:2] == ('$sp', '$sp') and not frame:
            frame = -int(args[2], 0)
            if frame < 24 or frame % 8:
                return None
        elif op == 'sw' and len(args) == 2 and args[0] == '$ra':
            saved_ra = memory(args[1])
            if not saved_ra or saved_ra[1] != '$sp' or not 16 <= saved_ra[0] < frame:
                return None
        elif op == 'sw' and len(args) == 2 and args[0] in registers:
            # IDO can preserve an otherwise unused incoming parameter in its
            # own argument home before replacing that register for the call.
            index = int(args[0][-1])
            if not frame or memory(args[1]) != (frame + index*4, '$sp') or registers[args[0]] != args[0]:
                return None
        elif op in ('addiu', 'ori') and len(args) == 3 and args[0] in registers and args[1] == '$zero':
            value = int(args[2], 0)
            if not -32768 <= value <= (65535 if op == 'ori' else 32767):
                return None
            registers[args[0]] = value
        elif op == 'move' and len(args) == 2 and args[0] in registers and args[1] in registers:
            registers[args[0]] = registers[args[1]]
        elif op in ('addu', 'or') and len(args) == 3 and args[0] in registers and args[1] in registers and args[2] == '$zero':
            registers[args[0]] = registers[args[1]]
        elif op in ('addu', 'or') and len(args) == 3 and args[0] in registers and args[1:] == ('$zero', '$zero'):
            registers[args[0]] = 0
        else:
            return None
    if not frame or saved_ra is None:
        return None
    suffix = code[call+2:]
    # Compare parsed operands because raw assembly can spell immediates in hex.
    if not suffix or suffix[0].op != 'lw' or len(suffix[0].args) != 2 or suffix[0].args[:1] != ('$ra',) or memory(suffix[0].args[1]) != saved_ra:
        return None
    suffix = suffix[1:]
    if len(suffix) == 3 and suffix[-1] == Instruction('nop', ()):
        adjust, ret = suffix[:2]
    elif len(suffix) == 2:
        ret, adjust = suffix
    else:
        return None
    if ret != Instruction('jr', ('$ra',)) or adjust.op != 'addiu' or len(adjust.args) != 3 or adjust.args[:2] != ('$sp', '$sp') or int(adjust.args[2], 0) != frame:
        return None
    return code[call].args[0], tuple(registers[f'$a{i}'] for i in range(4))


@reject_malformed_assembly
def callee_home_arguments(assembly: str) -> tuple[str, ...] | None:
    """Recover contiguous o32 word homes and pointer use in the entry block.

    Stop at the first branch/call. Only a small whitelist propagates aliases;
    floating-point, partial-width homes, unknown operations, or missing homes
    reject inference. A word saved to its ABI home is not narrowed to u8/u16.
    """
    code = instructions(assembly)
    if code is None:
        return None
    origins = {f'$a{i}': i for i in range(4)}
    stack: dict[int, int] = {}
    homes: set[int] = set()
    pointers: set[int] = set()
    used: set[int] = set()
    frame = 0
    transfers = {'jal', 'jr', 'j', 'b', 'beq', 'bne', 'beqz', 'bnez', 'bgez', 'bltz', 'blez', 'bgtz'}
    boundary = next((i for i, ins in enumerate(code[:63]) if ins.op in transfers), None)
    if boundary is None or boundary + 1 >= len(code):
        return None
    for index, ins in enumerate(code[:boundary+2]):
        op, args = ins.op, ins.args
        operands = args if op in transfers | {'sw', 'sb', 'sh'} else args[1:]
        for operand in operands:
            mem = memory(operand)
            register = mem[1] if mem else operand
            if register in origins:
                used.add(origins[register])
        if index == boundary:
            continue
        if op == 'nop':
            continue
        if op == 'addiu' and args[:2] == ('$sp', '$sp') and len(args) == 3 and not frame:
            frame = -int(args[2], 0)
            if frame <= 0 or frame % 8:
                return None
        elif op in ('sw', 'sb', 'sh', 'lw', 'lbu', 'lb', 'lhu', 'lh') and len(args) == 2:
            mem = memory(args[1])
            if mem is None:
                return None
            offset, base = mem
            if base in origins:
                pointers.add(origins[base])
            if base == '$sp':
                offset -= frame
                if op in ('sw', 'sb', 'sh'):
                    value = origins.get(args[0])
                    if value is not None and offset >= 0:
                        if op != 'sw' or offset != value*4:
                            return None
                        homes.add(value)
                    width = {'sw': 4, 'sh': 2, 'sb': 1}[op]
                    for slot in list(stack):
                        if offset < slot + 4 and slot < offset + width:
                            del stack[slot]
                    if value is not None and op == 'sw':
                        stack[offset] = value
                    else:
                        stack.pop(offset, None)
                else:
                    origins.pop(args[0], None)
                    if op == 'lw' and offset in stack:
                        origins[args[0]] = stack[offset]
            elif op in ('lw', 'lbu', 'lb', 'lhu', 'lh'):
                origins.pop(args[0], None)
        elif op in ('move', 'addiu', 'addu', 'or', 'ori', 'lui'):
            if not args:
                return None
            origin = origins.get(args[1]) if len(args) > 1 else None
            # Nonzero arithmetic destroys pointer/argument provenance.
            copy = op == 'move' or (op in ('addu', 'or') and len(args) == 3 and args[2] == '$zero')
            origins.pop(args[0], None)
            if copy and origin is not None:
                origins[args[0]] = origin
        else:
            return None
    if not homes or homes != set(range(max(homes)+1)):
        return None
    # Four homes can be a variadic register-save area. Higher live arguments at
    # a branch/call could be consumed on a later path, so do not truncate them.
    if len(homes) == 4 or used - homes or set(stack.values()) - homes:
        return None
    if code[boundary].op != 'jr' and set(origins.values()) - homes:
        return None
    for ins in code:
        for operand in ins.args:
            mem = memory(operand)
            if mem and mem[1] == '$sp' and mem[0] >= frame + 4*len(homes):
                return None
        if ins.op == 'addiu' and len(ins.args) == 3 and ins.args[1] == '$sp':
            amount = int(ins.args[2], 0)
            if ins.args[0] == '$sp':
                if amount not in (-frame, frame):
                    return None
            elif amount >= frame:
                # Taking the address of the incoming argument area could hide
                # variadic or stack-passed arguments behind another register.
                return None
    return tuple('void *' if i in pointers else 's32' for i in range(len(homes)))


@dataclass(frozen=True)
class Recovery:
    declarations: tuple[str, ...] = ()
    evidence: tuple[str, ...] = ()


def recover(assembly: str, source: str, *, root: Path, profile: str = 'us', allow_raw: bool = False) -> Recovery:
    callees = direct_callees(assembly)
    signatures = signature_index(root, callees, source=source, profile=profile) if callees else {}
    local = source_signatures(source, callees) if source and callees else {}
    sdk = sdk_alias_signatures(root, callees, profile=profile) if callees else {}
    declarations = []
    evidence = []
    for symbol, sig in sorted(signatures.items()):
        if sig is not None:
            declarations.append(sig.declaration(symbol))
            origin = ('unique active declaration in the allowed source' if symbol in local else
                      sdk_alias_evidence(symbol) if symbol in sdk else 'unique active project prototype')
            evidence.append(f'{symbol}: {origin}')
    if allow_raw and profile == 'us':
        wrapper = wrapper_call(assembly)
        if wrapper and wrapper[0] not in signatures:
            symbol, values = wrapper
            path = raw_callee_path(root, symbol, profile)
            args = callee_home_arguments(path.read_text()) if path else None
            if args and all(values[i] == f'$a{i}' for i in range(len(args), 4)):
                # A raw pointer parameter may only receive a forwarded register
                # or NULL; nonzero integer constants are not pointer evidence.
                if all(t != 'void *' or isinstance(v, str) or v == 0 for t, v in zip(args, values)):
                    declarations.append(Signature('void', args).declaration(symbol) + f' /* {ABI_MARKER} */')
                    evidence.append(f'{symbol}: raw o32 argument homes in {path.relative_to(root)}; types from entry-block use; caller discards result')
    return Recovery(tuple(declarations), tuple(evidence))


def discarded_call(starter: str, symbol: str, callee: str) -> bool:
    # Raw fallback only when the existing decompiler represents this as a
    # void wrapper containing one discarded call and no other C statements.
    return re.search(rf'\bvoid\s+{re.escape(symbol)}\([^{{;]*\)\s*\{{\s*{re.escape(callee)}\([^;{{}}]*\);\s*\}}\s*$', starter) is not None


def dependency_digest(root: Path, assembly: str,
                      prototypes: dict[str, Signature | None] | None = None, *,
                      profile: str = 'us') -> str:
    digest = hashlib.sha256()
    callees = direct_callees(assembly)
    if prototypes is None:
        prototypes = signature_index(root, callees, profile=profile) if callees else {}
    for symbol in sorted(callees):
        digest.update(symbol.encode())
        signature = prototypes.get(symbol)
        digest.update((signature.declaration(symbol) if signature else
                       '<ambiguous>' if symbol in prototypes else '<undeclared>').encode())
        path = raw_callee_path(root, symbol, profile)
        digest.update(path.read_bytes() if path else b'<no-validated-callee>')
    return digest.hexdigest()
