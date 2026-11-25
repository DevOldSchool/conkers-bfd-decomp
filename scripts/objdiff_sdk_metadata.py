"""Narrow, ABI-verified metadata repairs on SDK comparison copies only."""
from __future__ import annotations

import hashlib
from pathlib import Path
import struct
import subprocess

import compile_c
from elf_sections import sections
from objdiff_candidate import Elf


VI_MEMBERS = {
    'vimodentsclan1.o': 'osViModeNtscLan1',
    'vimodepallan1.o': 'osViModePalLan1',
    'vimodempallan1.o': 'osViModeMpalLan1',
}
VI_LAYOUT = (80, 40, 20, 76, 4)
VI_PROBE = '''#include <PR/os.h>
#define OFFSET(type, member) ((u32)&(((type *)0)->member))
const u32 vi_layout[] = {
    sizeof(OSViMode), OFFSET(OSViMode, fldRegs),
    sizeof(((OSViMode *)0)->fldRegs[0]),
    OFFSET(OSViMode, fldRegs[1].vIntr),
    sizeof(((OSViMode *)0)->fldRegs[1].vIntr)
};
'''


def compile_vi_layout(root: Path, directory: Path) -> dict:
    directory.mkdir(parents=True, exist_ok=True)
    source, output = directory / 'vi-layout.c', directory / 'vi-layout.o'
    source.write_text(VI_PROBE)
    with (directory / 'vi-layout.log').open('w') as log:
        result = compile_c.run_compile('us', source, output, cwd=root, stdout=log, stderr=log)
    if result.returncode:
        raise ValueError('SDK VI layout probe failed to compile')
    raw = output.read_bytes()
    obj = Elf(raw)
    payload = sections(raw, 1)['.rodata'][1]
    if obj.relocations or len(payload) < 20 or any(payload[20:]):
        raise ValueError('SDK VI layout probe has unexpected storage or relocations')
    layout = struct.unpack('>5I', payload[:20])
    if layout != VI_LAYOUT:
        raise ValueError('SDK VI layout differs from the reviewed 80-byte structure')
    return {'layout': list(layout), 'probe_source': source.relative_to(root).as_posix(),
            'probe_object_sha256': hashlib.sha256(raw).hexdigest(),
            'header_sha256': hashlib.sha256((root / 'lib/ultralib/include/PR/os_vi.h').read_bytes()).hexdigest()}


def repair_vi_symbol(raw: bytes, symbol: str, layout: tuple[int, ...]) -> tuple[bytes, dict]:
    """Correct the known 78-byte ELF extent, preserving all storage and relocations."""
    if symbol not in VI_MEMBERS.values() or tuple(layout) != VI_LAYOUT:
        raise ValueError('unreviewed VI symbol or ABI layout')
    obj = Elf(raw)
    if '.data' not in obj.names:
        raise ValueError('VI object has no data section')
    section = obj.names.index('.data')
    if obj.headers[section][5] != 80 or obj.relocations:
        raise ValueError('VI object extent or relocations differ')
    if any(h[2] & 2 and h[5] for i, h in enumerate(obj.headers)
           if i != section and obj.names[i] not in ('.reginfo', '.MIPS.abiflags')):
        raise ValueError('VI object has additional allocated storage')
    matches = [i for i, s in enumerate(obj.symbols) if s[0] == symbol]
    if len(matches) != 1:
        raise ValueError('VI object symbol is missing or ambiguous')
    index = matches[0]
    old = obj.symbols[index]
    if old[1:] not in ((0, 78, 0x11, 0, section), (0, 80, 0x11, 0, section)):
        raise ValueError('VI symbol does not have the reviewed shape')
    if any(s[5] == section and s[3] & 15 != 3 and i != index for i, s in enumerate(obj.symbols)):
        raise ValueError('VI object has another data variable')
    offset = obj.headers[obj.symtab][4] + index * 16 + 8
    result = bytearray(raw)
    struct.pack_into('>I', result, offset, 80)
    result = bytes(result)
    after = Elf(result)
    expected = list(obj.symbols)
    expected[index] = (symbol, 0, 80, 0x11, 0, section)
    if (raw[:offset] != result[:offset] or raw[offset + 4:] != result[offset + 4:]
            or after.symbols != expected or after.relocations != obj.relocations
            or after.headers != obj.headers):
        raise ValueError('VI repair changed more than the declared symbol size')
    return result, {'method': 'compiled-SDK-ABI-symbol-size', 'symbol': symbol,
                    'old_size': old[2], 'new_size': 80,
                    'storage_and_relocations_unchanged': True}


def repair_vi_candidates(units: list[dict], configs: list[dict], root: Path, output: Path) -> None:
    layout_proof = None
    for unit, config in zip(units, configs, strict=True):
        if (unit.get('kind') != 'sdk_placement' or unit.get('overlay') != 'main'
                or unit.get('archive') != 'libultra_2_0G' or unit.get('member') not in VI_MEMBERS):
            continue
        spans = unit.get('data_ranges', [])
        if len(spans) != 1 or not unit.get('base_path'):
            raise ValueError('VI metadata repair requires one mapped SDK data section')
        span = spans[0]
        if (span.get('section') != '.data' or span.get('size') != 80
                or span.get('kind') != 'sdk_placement'
                or span.get('owner') != {'archive': 'libultra_2_0G', 'member': unit['member']}
                or span.get('evidence_reference') != 'config/profiles/us.yaml'
                or span.get('candidate_data_relocations') != 0
                or span.get('literal_payload_matches_rom') is not True):
            raise ValueError('VI metadata repair requires a whole-section ROM proof')
        archive = root / 'build/us/lib/libultra_2_0G.a'
        raw = subprocess.check_output(['mips-linux-gnu-ar', 'p', str(archive), unit['member']])
        if (output / unit['base_path']).read_bytes() != raw:
            raise ValueError('VI candidate differs from the actual SDK archive')
        payload = sections(raw, 1)['.data'][1]
        if len(payload) != 80 or hashlib.sha256(payload).hexdigest() != span['sha256']:
            raise ValueError('VI payload differs from the independent ROM proof')
        if layout_proof is None:
            layout_proof = compile_vi_layout(root, output / 'sdk-abi')
        corrected, proof = repair_vi_symbol(raw, VI_MEMBERS[unit['member']], tuple(layout_proof['layout']))
        path = output / 'owned' / unit['key'] / 'base.o'
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(corrected)
        unit['comparison_copy'] = {'raw_base_path': unit['base_path'],
                                   'raw_base_sha256': hashlib.sha256(raw).hexdigest(),
                                   'abi_proof': layout_proof, **proof}
        unit.setdefault('linked_inputs', {})[archive.relative_to(root).as_posix()] = hashlib.sha256(archive.read_bytes()).hexdigest()
        unit['base_path'] = config['base_path'] = path.relative_to(output).as_posix()
        unit['base_sha256'] = hashlib.sha256(corrected).hexdigest()
