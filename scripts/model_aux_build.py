"""Typed bank-09 effect meshes and skeletal particle-emission point arrays."""
from __future__ import annotations

import math
import struct

try:
    from scripts import model_effect_format, model_emission_points
except ModuleNotFoundError:
    import model_effect_format, model_emission_points


def effect_records(payload: bytes) -> dict:
    header = list(model_effect_format.effect_header(payload))
    cursor = 32
    sections = []
    for pair in range(4):
        offset, size = header[2 * pair:2 * pair + 2]
        size &= 0x0FFFFFFF
        if size and offset != cursor:
            raise ValueError('effect sections leave an unsupported gap')
        fmt = '>hhhHhh4B' if pair < 2 else '>II'
        sections.append([list(row) for row in struct.iter_unpack(fmt, payload[offset:offset + size])])
        if size:
            cursor += size
    suffix = payload[cursor:]
    if suffix not in (b'', bytes(8)):
        raise ValueError('effect model has an unsupported zero suffix')
    return {'format': 'effect-four-pair', 'header_words': header,
            'vertex_buffers': sections[:2], 'material_commands': sections[2],
            'geometry_commands': sections[3], 'zero_suffix_bytes': len(suffix)}


def encode_effect_records(records: dict) -> bytes:
    fields = {'format', 'header_words', 'vertex_buffers', 'material_commands',
              'geometry_commands', 'zero_suffix_bytes'}
    if (not isinstance(records, dict) or set(records) != fields
            or records['format'] != 'effect-four-pair'
            or not isinstance(records['vertex_buffers'], list)
            or len(records['vertex_buffers']) != 2
            or type(records['zero_suffix_bytes']) is not int
            or records['zero_suffix_bytes'] not in (0, 8)):
        raise ValueError('invalid effect-model record schema')
    try:
        payload = (struct.pack('>8I', *records['header_words'])
                   + b''.join(struct.pack('>hhhHhh4B', *v)
                              for buffer in records['vertex_buffers'] for v in buffer)
                   + b''.join(struct.pack('>II', *row) for row in records['material_commands'])
                   + b''.join(struct.pack('>II', *row) for row in records['geometry_commands'])
                   + bytes(records['zero_suffix_bytes']))
    except (struct.error, TypeError, OverflowError) as error:
        raise ValueError('invalid native effect-model record') from error
    if effect_records(payload) != records:
        raise ValueError('effect records disagree with declared boundaries')
    return payload


def point_records(payload: bytes) -> dict:
    parsed = model_emission_points.parse_points(payload)
    points = []
    for point in parsed['points']:
        if point['reserved_bytes'] != '000000':
            raise ValueError('emission point has unknown reserved bytes')
        points.append({'matrix_slot': point['matrix_slot'], 'reserved_bytes': [0, 0, 0],
                       'local_xyz': point['local_xyz']})
    return {'format': 'emission-points', 'points': points}


def encode_point_records(records: dict) -> bytes:
    if (not isinstance(records, dict) or set(records) != {'format', 'points'}
            or records['format'] != 'emission-points'
            or not isinstance(records['points'], list) or not records['points']):
        raise ValueError('invalid emission-point record schema')
    parts = []
    try:
        for point in records['points']:
            if (not isinstance(point, dict)
                    or set(point) != {'matrix_slot', 'reserved_bytes', 'local_xyz'}
                    or point['reserved_bytes'] != [0, 0, 0]
                    or len(point['local_xyz']) != 3
                    or not all(math.isfinite(v) for v in point['local_xyz'])):
                raise ValueError('invalid native emission-point fields')
            parts.append(struct.pack('>B3x3f', point['matrix_slot'], *point['local_xyz']))
    except (struct.error, TypeError, OverflowError) as error:
        raise ValueError('invalid native emission-point record') from error
    payload = b''.join(parts)
    if point_records(payload) != records:
        raise ValueError('emission-point fields cannot be represented exactly')
    return payload
