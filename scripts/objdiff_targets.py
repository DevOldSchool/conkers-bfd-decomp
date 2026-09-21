#!/usr/bin/env python3
"""Generate splat full-disassembly targets and prove their linked CPU-code bytes."""
from __future__ import annotations

from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
import os
from pathlib import Path
import re
import struct
import subprocess

import extract_game_code
import normalize_asm

ROOT = Path(__file__).resolve().parent.parent
ORIGINS = {'main': 0x80000000, 'game': 0x15000000}


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def config_document(specs: list[dict], directory: Path, binary: Path, sha1: str) -> dict:
    """Use reviewed range ownership; all outputs stay in the report directory."""
    overlay = specs[0]['overlay']
    relative = directory.relative_to(ROOT).as_posix()
    options = {
        'basename': overlay, 'base_path': os.path.relpath(ROOT, directory.parent),
        'target_path': binary.relative_to(ROOT).as_posix(),
        'platform': 'n64', 'compiler': 'IDO',
        'asm_path': relative + '/asm', 'src_path': relative + '/unused-src',
        'asset_path': relative + '/assets', 'build_path': relative + '/objects',
        'ld_script_path': relative + '/splat.ld', 'cache_path': relative + '/splache',
        'undefined_funcs_auto_path': relative + '/undefined_funcs.txt',
        'undefined_syms_auto_path': relative + '/undefined_syms.txt',
        'create_c_files': False, 'make_full_disasm_for_code': True,
        'disassemble_all': True, 'asm_emit_size_directive': True,
        'asm_function_macro': 'glabel', 'asm_data_macro': 'glabel',
        'asm_jtbl_label_macro': 'jlabel', 'mips_abi_float_regs': 'o32',
        'symbol_addrs_path': ['config/symbols/' + ('us' if overlay == 'main' else 'game-us') + '.txt'],
    }
    segments = []
    if specs[0]['start']:
        segments.append([0, 'bin', 'prefix'])
    segments.append({
        'name': overlay, 'type': 'code', 'start': specs[0]['start'],
        'vram': ORIGINS[overlay] + specs[0]['start'],
        'subsegments': [[s['start'], 'c' if s['kind'] == 'source' else 'asm', f"{s['start']:06X}"]
                        for s in specs],
    })
    if specs[-1]['end'] < binary.stat().st_size:
        segments.append([specs[-1]['end'], 'bin', 'suffix'])
    segments.append([binary.stat().st_size])
    return {'name': overlay + ' objdiff targets', 'sha1': sha1, 'options': options, 'segments': segments}


def text_extent(data: bytes) -> int:
    """Reject unexpected allocated target sections instead of dropping their bytes."""
    if len(data) < 52 or data[:7] != b'\x7fELF\x01\x02\x01':
        raise ValueError('expected big-endian ELF32 target')
    if struct.unpack_from('>HH', data, 16) != (1, 8):
        raise ValueError('expected relocatable MIPS target')
    shoff = struct.unpack_from('>I', data, 32)[0]
    size, count, names_index = struct.unpack_from('>HHH', data, 46)
    if size != 40 or shoff + size * count > len(data) or names_index >= count:
        raise ValueError('invalid target section table')
    sections = [struct.unpack_from('>10I', data, shoff + i * size) for i in range(count)]
    names_section = sections[names_index]
    names = data[names_section[4]:names_section[4] + names_section[5]]
    extent = None
    for section in sections:
        name = names[section[0]:].split(b'\0', 1)[0]
        if name == b'.text':
            if extent is not None or section[1] != 1 or section[2] & 6 != 6:
                raise ValueError('invalid target text section')
            extent = section[5]
        elif section[2] & 2 and section[5] and name not in (b'.reginfo', b'.MIPS.abiflags'):
            raise ValueError(f'unmapped allocated target section: {name.decode()}')
        if section[1] != 8 and section[4] + section[5] > len(data):
            raise ValueError('truncated target section')
    if extent is None:
        raise ValueError('missing target text section')
    return extent


def linker_script(specs: list[dict], objects: list[Path], externals: str) -> str:
    lines = ['SECTIONS {']
    for i, (spec, path) in enumerate(zip(specs, objects, strict=True)):
        address = ORIGINS[spec['overlay']] + spec['start']
        lines += [f'.unit{i} 0x{address:X} : SUBALIGN(4) {{ "{path}"(.text) }}',
                  f'ASSERT(SIZEOF(.unit{i}) == {spec["end"] - spec["start"]}, "target extent {spec["key"]}")']
    lines += ['/DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.gnu.attributes) *(.comment) }', '}']
    # These are splat's ROM-derived unresolved-address definitions. PROVIDE
    # preserves actual definitions in targets for cross-object relocations.
    for name, address in re.findall(r'(\w+)\s*=\s*(0x[0-9A-Fa-f]+);', externals):
        lines.append(f'PROVIDE({name} = {address});')
    return '\n'.join(lines) + '\n'


def verify_linked_bytes(actual: bytes, expected: bytes, overlay: str) -> dict:
    if actual != expected:
        offset = next((i for i, (a, b) in enumerate(zip(actual, expected)) if a != b),
                      min(len(actual), len(expected)))
        raise ValueError(f'{overlay} linked target differs from original bytes at +0x{offset:X} '
                         f'(actual {len(actual)}, expected {len(expected)} bytes)')
    return {'bytes': len(actual), 'sha256': hashlib.sha256(actual).hexdigest(), 'matches_original': True}


def symbol_coverage(original: bytes, symbols: dict) -> dict:
    """Account for native function bytes and independently verified zero gaps."""
    spans = sorted((s['address'], s['address'] + s['size']) for s in symbols.values()
                   if s['size'] and not s['hidden'])
    cursor, total, gaps = 0, 0, []
    for start, end in spans + [(len(original), len(original))]:
        if start < cursor or end < start or end > len(original) or start % 4 or end % 4:
            raise ValueError('overlapping, unaligned or out-of-range target symbols')
        if start > cursor:
            if any(original[cursor:start]):
                raise ValueError(f'nonzero original bytes outside target symbols at +0x{cursor:X}')
            gaps.append({'start': cursor, 'end': start})
        total += end - start
        cursor = end
    return {'report_code_bytes': total, 'excluded_zero_bytes': len(original) - total,
            'excluded_zero_ranges': gaps}


def prepare(specs: list[dict], output: Path) -> tuple[dict, dict]:
    """Fresh split, independent assembly, and whole-overlay link validation."""
    directory = output / 'targets'
    directory.mkdir(parents=True, exist_ok=True)
    rom = ROOT / 'roms/baserom.us.z64'
    rom_bytes = rom.read_bytes()
    profile = json.loads((ROOT / 'config/roms.json').read_text())['profiles']['us']
    if len(rom_bytes) != profile['size_bytes'] or hashlib.sha1(rom_bytes).hexdigest() != profile['sha1']:
        raise ValueError('US ROM checksum/size mismatch')
    game_bytes = extract_game_code.extract_code(rom_bytes, 'us')
    game_sha1 = json.loads((ROOT / 'config/overlays.json').read_text())['overlays']['game']['profiles']['us']['sha1']
    if hashlib.sha1(game_bytes).hexdigest() != game_sha1:
        raise ValueError('decompressed game code checksum mismatch')
    game = directory / 'game.code.bin'
    game.write_bytes(game_bytes)
    targets, verification = {}, {}
    for overlay, binary, original, digest in (
        ('main', rom, rom_bytes, profile['sha1']), ('game', game, game_bytes, game_sha1)
    ):
        units = [s for s in specs if s['overlay'] == overlay]
        dest = directory / overlay
        dest.mkdir(parents=True, exist_ok=True)
        config = directory / f'{overlay}.yaml'
        config.write_text(json.dumps(config_document(units, dest, binary, digest), indent=2) + '\n')
        print(f'objdiff targets: splat full disassembly for {overlay}', flush=True)
        with (dest / 'splat.log').open('w') as log:
            subprocess.run(['splat', 'split', str(config)], cwd=ROOT, stdout=log, stderr=log, check=True)

        def assemble(spec):
            name = f"{spec['start']:06X}"
            source = dest / 'asm' / f'{name}.s'
            normalized = dest / f'{name}.s'
            obj = dest / f'{name}.o'
            # Only the existing GNU-as syntax normalization. Preserve splat's
            # full translation unit, symbols, sizes, padding and relocations.
            normalized.write_text(normalize_asm.normalize(source.read_text()))
            with (dest / f'{name}.log').open('w') as log:
                subprocess.run(['mips-linux-gnu-as', '-W', '-EB', '-march=vr4300', '-mabi=32',
                                '-I', 'include', '-o', str(obj), str(normalized)],
                               cwd=ROOT, stdout=log, stderr=log, check=True)
            extent = text_extent(obj.read_bytes())
            if extent != spec['end'] - spec['start']:
                raise ValueError(f'{spec["key"]}: splat target extent differs from mapped range')
            return spec['key'], {'path': obj.relative_to(output).as_posix(),
                                  'source': source.relative_to(output).as_posix(),
                                  'sha256': sha256(obj), 'text_bytes': extent}

        with ThreadPoolExecutor(max_workers=4) as pool:
            prepared = dict(pool.map(assemble, units))
        objects = [(output / prepared[s['key']]['path']).relative_to(ROOT) for s in units]
        externals = '\n'.join((dest / name).read_text() for name in ('undefined_funcs.txt', 'undefined_syms.txt'))
        script = dest / 'targets.ld'
        script.write_text(linker_script(units, objects, externals))
        elf, linked = dest / 'targets.elf', dest / 'targets.bin'
        with (dest / 'link.log').open('w') as log:
            subprocess.run(['mips-linux-gnu-ld', '-m', 'elf32btsmip', '-T', str(script), '-o', str(elf),
                            *map(str, objects)], cwd=ROOT, stdout=log, stderr=log, check=True)
            subprocess.run(['mips-linux-gnu-objcopy', '-O', 'binary', str(elf), str(linked)],
                           cwd=ROOT, stdout=log, stderr=log, check=True)
        verification[overlay] = verify_linked_bytes(linked.read_bytes(),
            original[units[0]['start']:units[-1]['end']], overlay)
        verification[overlay].update({'unit_count': len(units), 'input_sha1': digest,
                                      'config_sha256': sha256(config)})
        targets.update(prepared)
        print(f'objdiff targets: {overlay} linked bytes match ({verification[overlay]["bytes"]} bytes)', flush=True)
    return targets, verification
