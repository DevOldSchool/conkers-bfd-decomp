"""Proved main-runtime pointer metadata on copies of reviewed SDK objects."""
from __future__ import annotations

import hashlib
from pathlib import Path
import re
import struct
import subprocess

import objdiff_candidate as candidate
import rom_span
from prepare_main_library_object import rebase_code_pointers

OWNERS = {'xprintf.o': 52, 'n_csplayer.o': 145, 'n_reverb.o': 8, 'n_env.o': 17,
          'n_sndplayer.o': 16}
ALIAS_DELTA = -0x70000000


def plan(raw: bytes, bases: dict[str, int], count: int) -> tuple[list, dict, list]:
    """Recover bounds from candidate instructions, never reference symbols/bytes."""
    obj = candidate.Elf(raw)
    text = obj.names.index('.text')
    if not 0x80001000 <= bases.get('.text', 0) < 0x8002A000:
        raise candidate.AnnotationError('main SDK code placement is outside the reviewed mapping')
    # Analysis only: restore ordinary within-object addends so the existing
    # dispatch recognizer can check every destination against the code extent.
    analysis = rebase_code_pointers(raw, -ALIAS_DELTA, count)
    symbols = candidate.discover(analysis, bases)
    additions = [(s.name, s.offset, s.size, 0x11, 0, obj.names.index(s.section)) for s in symbols]
    words, labels = {}, set()
    restored = bytearray(raw)
    for symbol in symbols:
        if symbol.kind != 'jump_table':
            continue
        section = obj.names.index(symbol.section)
        for at in range(symbol.offset, symbol.offset + symbol.size, 4):
            kind, index = obj.relocations[(section, at)]
            target = obj.symbols[index]
            offset = (target[1] + obj.word(section, at) - ALIAS_DELTA) & 0xFFFFFFFF
            if kind != 2 or target[5] != text or offset % 4 or not 0 <= offset < obj.headers[text][5]:
                raise candidate.AnnotationError('SDK switch destination is outside its code owner')
            address = bases['.text'] + offset + ALIAS_DELTA
            if address != (bases['.text'] + target[1] + obj.word(section, at)) & 0xFFFFFFFF:
                raise candidate.AnnotationError('SDK runtime pointer alias differs')
            label = (f'.L{address:08X}', address, 0, 0x10, 0, 0xFFF1)
            words[(section, at)] = label
            labels.add(label)
            struct.pack_into('>I', restored, obj.headers[section][4] + at,
                             (obj.word(section, at) - ALIAS_DELTA) & 0xFFFFFFFF)
    if len(words) != count or bytes(restored) != analysis:
        raise candidate.AnnotationError('SDK dispatch bounds do not cover every staged code pointer')
    additions += sorted(labels)
    old_names = {s[0] for s in obj.symbols}
    if len({s[0] for s in additions}) != len(additions) or old_names & {s[0] for s in additions}:
        raise candidate.AnnotationError('SDK comparison symbol collision or already annotated object')
    return additions, words, symbols


def verify(raw: bytes, result: bytes, bases: dict[str, int], count: int) -> dict:
    """Independently check all permitted words, relocation targets and ELF metadata."""
    left, right = candidate.Elf(raw), candidate.Elf(result)
    additions, words, _ = plan(raw, bases, count)
    if (left.header != right.header or left.names != right.names
            or right.symbols != left.symbols + additions
            or right.payload(right.strtab) != left.payload(left.strtab) +
                b''.join(s[0].encode('ascii') + b'\0' for s in additions)
            or set(left.relocations) != set(right.relocations)):
        raise candidate.AnnotationError('SDK pointer copy changed object structure or original symbols')
    payloads = {i: bytearray(left.payload(i)) for i in range(len(left.headers))}
    for key, original in left.relocations.items():
        changed = right.relocations[key]
        if key not in words:
            if original != changed:
                raise candidate.AnnotationError('unrelated SDK relocation changed')
            continue
        kind, index = changed
        label = right.symbols[index]
        if kind != 2 or label != words[key] or right.word(*key):
            raise candidate.AnnotationError('SDK pointer effective destination changed')
        struct.pack_into('>I', payloads[key[0]], key[1], 0)
    for i, header in enumerate(left.headers):
        if header[1] == 9:
            for at in range(0, header[5], 8):
                offset, info = struct.unpack_from('>II', payloads[i], at)
                key = (header[7], offset)
                if key in words:
                    kind, index = right.relocations[key]
                    struct.pack_into('>I', payloads[i], at + 4, index << 8 | kind)
        other = right.headers[i]
        if i in (left.symtab, left.strtab):
            if header[:4] + header[6:] != other[:4] + other[6:]:
                raise candidate.AnnotationError('SDK symbol table semantics changed')
        elif header != other or bytes(payloads[i]) != right.payload(i):
            raise candidate.AnnotationError('unapproved SDK section or header change')
    return {'pointer_words': len(words), 'effective_destinations_identical': True,
            'original_symbols_identical': True, 'other_sections_identical': True}


def canonicalize(raw: bytes, bases: dict[str, int], count: int) -> tuple[bytes, dict]:
    additions, words, symbols = plan(raw, bases, count)
    labeled = candidate.add_labels(raw, additions)
    obj = candidate.Elf(labeled)
    data = bytearray(labeled)
    indices = {s: i for i, s in enumerate(obj.symbols)}
    for header in obj.headers:
        if header[1] != 9:
            continue
        for at in range(header[4], header[4] + header[5], 8):
            offset, info = struct.unpack_from('>II', labeled, at)
            key = (header[7], offset)
            if key not in words:
                continue
            struct.pack_into('>I', data, obj.headers[key[0]][4] + offset, 0)
            struct.pack_into('>I', data, at + 4, indices[words[key]] << 8 | 2)
    result = bytes(data)
    return result, {'method': 'candidate-dispatch-and-main-runtime-alias',
                    'symbols': [candidate.asdict(s) for s in symbols],
                    'section_bases': bases, 'alias_delta': ALIAS_DELTA,
                    'semantic_verification': verify(raw, result, bases, count)}


def verify_linked(raw_path: Path, canonical_path: Path, runtime_bytes: bytes,
                  bases: dict[str, int], directory: Path) -> dict:
    """Link both complete objects at real placements, including owned BSS."""
    obj, runtime = candidate.Elf(raw_path.read_bytes()), candidate.Elf(runtime_bytes, 2)
    addresses = {}
    for name, value, _, _, _, section in runtime.symbols:
        if name and (0 < section < len(runtime.headers) or section == 0xFFF1):
            addresses.setdefault(name, set()).add(value)
    placements = dict(bases)
    for i, header in enumerate(obj.headers):
        if header[1] != 8 or not header[2] & 2 or not header[5]:
            continue
        values = set()
        for name, value, _, info, _, section in obj.symbols:
            if section == i and info & 15 != 3 and name:
                if len(addresses.get(name, [])) != 1:
                    raise candidate.AnnotationError('missing or ambiguous SDK BSS anchor')
                values.add(next(iter(addresses[name])) - value)
        if len(values) != 1:
            raise candidate.AnnotationError('SDK BSS has no unique actual placement')
        placements[obj.names[i]] = values.pop()
    used = {index for _, index in obj.relocations.values()}
    definitions = []
    for index, (name, value, _, _, _, section) in enumerate(obj.symbols):
        if section or not name or index not in used:
            continue
        if value or not re.fullmatch(r'[A-Za-z_.$][\w.$]*', name) or len(addresses.get(name, [])) != 1:
            raise candidate.AnnotationError('unresolved SDK comparison external: ' + name)
        definitions.append(f'{name} = 0x{next(iter(addresses[name])):X};')
    expected = {}
    for name, base in bases.items():
        size = obj.headers[obj.names.index(name)][5]
        containing = [(i, h) for i, h in enumerate(runtime.headers)
                      if h[1] == 1 and h[2] & 2 and h[3] <= base and base + size <= h[3] + h[5]]
        if len(containing) != 1:
            raise candidate.AnnotationError('SDK placement is not one allocated runtime section')
        i, h = containing[0]
        expected[name] = runtime.payload(i)[base - h[3]:base - h[3] + size]
    directory.mkdir(parents=True, exist_ok=True)
    for label, path in [('raw', raw_path), ('canonical', canonical_path)]:
        script, elf = directory / (label + '.ld'), directory / (label + '.elf')
        script.write_text('SECTIONS {\n' + '\n'.join(
            f'{name} 0x{base:X} : {{ *({name}) }}' for name, base in placements.items()) +
            '\n/DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.mdebug) '
            '*(.gnu.attributes) *(.comment) }\n}\n' + '\n'.join(definitions) + '\n')
        with (directory / (label + '.log')).open('w') as log:
            subprocess.run(['mips-linux-gnu-ld', '-m', 'elf32btsmip', '-T', str(script),
                            '-o', str(elf), str(path)], check=True, stdout=log, stderr=log)
        linked = candidate.Elf(elf.read_bytes(), 2)
        for name, payload in expected.items():
            i = linked.names.index(name)
            if linked.headers[i][3] != bases[name] or linked.payload(i) != payload:
                raise candidate.AnnotationError('SDK comparison copy differs from runtime: ' + label + ' ' + name)
        for name in placements.keys() - bases.keys():
            h = linked.headers[linked.names.index(name)]
            if h[1] != 8 or h[3] != placements[name] or h[5] != obj.headers[obj.names.index(name)][5]:
                raise candidate.AnnotationError('SDK BSS placement changed')
    return {'sections': {name: {'bytes': len(payload), 'sha256': hashlib.sha256(payload).hexdigest()}
                         for name, payload in expected.items()},
            'nobits_placements': {n: placements[n] for n in placements.keys() - bases.keys()},
            'raw_and_canonical_match_runtime': True}


def prepare_candidates(units: list[dict], configs: list[dict], root: Path, output: Path) -> None:
    runtime_path = root / 'build/us/conker.us.elf'
    runtime = None
    original_code = None
    for unit, config in zip(units, configs, strict=True):
        if (unit.get('kind') != 'sdk' or unit.get('overlay') != 'main'
                or unit.get('archive') != 'libultrare' or unit.get('member') not in OWNERS):
            continue
        archive = root / 'build/us/lib/libultrare.a'
        raw = subprocess.check_output(['mips-linux-gnu-ar', 'p', str(archive), unit['member']])
        raw_path = output / unit['base_path']
        if raw_path.read_bytes() != raw:
            raise candidate.AnnotationError('SDK pointer candidate differs from actual archive')
        obj = candidate.Elf(raw)
        if obj.headers[obj.names.index('.text')][5] != unit['end'] - unit['start']:
            raise candidate.AnnotationError('SDK code extent differs from its reviewed owner')
        bases = {'.text': 0x80000000 + unit['start']}
        for span in unit.get('data_ranges', []):
            if (span.get('kind') != 'sdk_placement'
                    or span.get('owner') != {'archive': 'libultrare', 'member': unit['member']}
                    or span.get('evidence_reference') != 'config/profiles/us.yaml'
                    or span['section'] not in ('.data', '.rodata') or span['section'] in bases
                    or obj.headers[obj.names.index(span['section'])][5] != span['size']):
                raise candidate.AnnotationError('SDK pointer copy requires complete reviewed placements')
            bases[span['section']] = span['start']
        required = {n for n, h in zip(obj.names, obj.headers) if h[1] == 1 and h[2] & 2 and h[5]
                    and n not in ('.reginfo', '.MIPS.abiflags')}
        if bases.keys() != required:
            raise candidate.AnnotationError('SDK pointer copy omits an allocated section')
        corrected, proof = canonicalize(raw, bases, OWNERS[unit['member']])
        path = output / 'owned' / unit['key'] / 'base.o'
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(corrected)
        if runtime is None:
            runtime = runtime_path.read_bytes()
        linked = verify_linked(raw_path, path, runtime, bases, path.parent / 'sdk-pointer-proof')
        for span in unit['data_ranges']:
            if linked['sections'][span['section']]['sha256'] != span['sha256']:
                raise candidate.AnnotationError('SDK linked data differs from independent ROM span')
        if original_code is None:
            original_code, original_base, _ = rom_span.main_code(root)
        begin = bases['.text'] - original_base
        expected = original_code[begin:begin + unit['end'] - unit['start']]
        if (begin < 0 or len(expected) != unit['end'] - unit['start']
                or hashlib.sha256(expected).hexdigest() != linked['sections']['.text']['sha256']):
            raise candidate.AnnotationError('SDK linked code differs from independent full ROM span')
        unit['comparison_copy'] = {'raw_base_path': unit['base_path'],
                                   'raw_base_sha256': hashlib.sha256(raw).hexdigest(),
                                   'linked_verification': linked, **proof}
        for input_path in (archive, runtime_path):
            unit.setdefault('linked_inputs', {})[input_path.relative_to(root).as_posix()] = hashlib.sha256(input_path.read_bytes()).hexdigest()
        unit['base_path'] = config['base_path'] = path.relative_to(output).as_posix()
        unit['base_sha256'] = hashlib.sha256(corrected).hexdigest()
