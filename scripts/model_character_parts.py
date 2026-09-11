"""Separate the primary and mode-3 character display-list tables from ROM."""

from __future__ import annotations

import hashlib
import struct
from dataclasses import replace
from typing import Any


def verify_consumers(code: bytes, base: int) -> dict:
    spans = ((0x1503CF20, 1096, '2335fa3855313510f1f46512cfa704ab301814d1'),
             (0x1502CCFC, 2128, '2176c655198fed8b1867b28f059cb4765bced897'))
    for address, size, expected in spans:
        offset = address - base
        if offset < 0 or hashlib.sha1(code[offset:offset + size]).hexdigest() != expected:
            raise ValueError(f'ROM character draw-table consumer changed at 0x{address:08X}')
    return {'loader': 'func_1503CF20', 'renderer': 'func_1502CCFC',
            'primary_pointer_table': '0x800C4488', 'secondary_pointer_table': '0x800C48F0',
            'secondary_render_mode': 3,
            'consumer_sha1': {f'0x{address:08X}': sha1 for address, _, sha1 in spans}}


def primary_preview(data: bytes, geometry: Any, layout: dict) -> tuple[Any, dict | None]:
    """Keep all primary parts; actor visibility masks remain a separate concern.

    The native renderer selects one table according to its mode argument. It
    does not concatenate both tables into an ordinary textured character.
    """
    tables = {table['name']: [int(p, 0) for p in table['pointers']]
              for table in layout['display_list_pointer_tables']}
    if not tables.get('secondary'):
        return geometry, None
    pointers = tables.get('primary', []) + tables['secondary']
    if not tables.get('primary') or len(set(pointers)) != len(pointers):
        raise ValueError('character draw-table pointers are absent or aliased')
    ranges = []
    for table, values in tables.items():
        if table not in ('primary', 'secondary'):
            raise ValueError('unknown character draw table')
        for pointer in values:
            if pointer < 0 or pointer % 8 or pointer + 8 > len(data):
                raise ValueError('character draw-table pointer is out of bounds')
            for end in range(pointer, len(data) - 7, 8):
                if struct.unpack_from('>II', data, end) == (0xDF000000, 0):
                    ranges.append((pointer, end + 8, table))
                    break
            else:
                raise ValueError('character draw-table list is unterminated')
    ordered = sorted(ranges)
    if any(left[1] > right[0] for left, right in zip(ordered, ordered[1:])):
        raise ValueError('character draw-table lists overlap')
    if len(geometry.face_command_offsets) != len(geometry.faces):
        raise ValueError('character faces lack complete command provenance')
    keep = []
    for index, offset in enumerate(geometry.face_command_offsets):
        owners = [table for start, end, table in ranges if start <= offset < end]
        if len(owners) != 1:
            raise ValueError('character face is outside its draw-table lists')
        if owners[0] == 'primary':
            keep.append(index)
    selected = set(keep)
    runs, cursor = [], 0
    for run in geometry.material_runs:
        count = sum(index in selected for index in range(run.first_face, run.first_face + run.face_count))
        runs.append(replace(run, first_face=cursor, face_count=count))
        cursor += count
    fields = {}
    for name in ('faces', 'face_normal_bytes', 'face_preview_normals', 'face_command_offsets',
                 'face_command_opcodes', 'face_cache_indices', 'face_matrix_indices', 'face_cull_modes',
                 'face_source_indices'):
        values = getattr(geometry, name)
        if values and len(values) != len(geometry.faces):
            raise ValueError(f'character face field {name} has an incomplete extent')
        fields[name] = tuple(values[index] for index in keep) if values else ()
    fields['face_source_indices'] = tuple(
        geometry.face_source_indices[index] if geometry.face_source_indices else index for index in keep)
    fields['material_runs'] = tuple(runs)
    evidence = {'selection': 'primary-table-all-parts', 'secondary_render_mode': 3,
                'model_sha1': hashlib.sha1(data).hexdigest(),
                'primary_pointers': tables['primary'], 'secondary_pointers': tables['secondary'],
                'all_tables_face_count': len(geometry.faces), 'primary_face_count': len(keep),
                'excluded_secondary_face_count': len(geometry.faces) - len(keep),
                'source_face_indices': fields['face_source_indices'],
                'scope': 'Primary draw table only. Actor part visibility and other renderer modes remain unresolved; raw extraction retains both tables.'}
    # Keep JSON identity stable between generation and independent validation.
    evidence['source_face_indices'] = list(evidence['source_face_indices'])
    return replace(geometry, **fields), evidence
