"""Bounded combinations of model normals, vertex colors and native face words."""
from __future__ import annotations

import hashlib
import struct

try:
    from scripts import model_assets
except ModuleNotFoundError:
    import model_assets


def extended_records(payload: bytes, *, primary: bool) -> dict:
    geometry = model_assets.parse_model_geometry(payload)
    header = list(geometry.header_words)
    display_end = header[0] + header[1]
    commands = [list(row) for row in struct.iter_unpack('>II', payload[header[0]:display_end])]
    normal_offsets = sorted({argument for command, argument in commands
                             if command == model_assets.CHARACTER_CUSTOM_MOVEMEM_COMMAND})
    normal_end = display_end + 64 * len(normal_offsets)
    if normal_offsets != list(range(display_end, normal_end, 64)):
        raise ValueError('extended normals are not contiguous and completely referenced')
    if (header[2:4] not in ([0, 0], [display_end, normal_end - display_end])
            or header[6:8] != [0, 0]):
        raise ValueError('extended secondary region lacks normal references')
    ranges = [(0, display_end)]
    if normal_offsets:
        ranges.append((display_end, normal_end))
    colors, sentinel = [], []
    if header[8]:
        table_size = geometry.vertex_color_animation_table_size
        if table_size != 12 * (len(geometry.vertex_color_animation_descriptors) + 1):
            raise ValueError('extended color table has invalid extent')
        for item in geometry.vertex_color_animation_descriptors:
            color, indices, count = item.color_data_offset, item.vertex_index_offset, item.vertex_count
            colors.append({'color_offset': color, 'vertex_index_offset': indices, 'vertex_count': count,
                           'colors': [list(row) for row in struct.iter_unpack(
                               '>3B', payload[color:color + 3 * count])],
                           'vertex_indices': list(struct.unpack_from(f'>{count}H', payload, indices))})
            ranges.extend([(color, color + 3 * count), (indices, indices + 2 * count)])
        sentinel = list(struct.unpack_from('>3I', payload, header[8] + table_size - 12))
        if sentinel != [0, 0, 0]:
            raise ValueError('extended color sentinel fields are unknown')
        ranges.append((header[8], header[8] + table_size))
    elif header[9] != 0x80000000:
        raise ValueError('extended model marker is invalid')
    surface_header, words = [], []
    if header[4]:
        if primary:
            segment = model_assets.ModelSegment(0, 0, len(payload), True, payload)
            words = list(model_assets.bank_04_collision_surface_words(segment, geometry))
            surface_header = list(struct.unpack_from('>2I', payload, header[4]))
        else:
            if header[5] != 4 * len(geometry.faces):
                raise ValueError('extended child table does not cover every face')
            words = list(struct.unpack_from(f'>{len(geometry.faces)}I', payload, header[4]))
        ranges.append((header[4], header[4] + header[5]))
    elif header[5]:
        raise ValueError('extended face table size lacks its pointer')
    cursor, zero_regions = 0, []
    for start, end in sorted(ranges) + [(len(payload), len(payload))]:
        if start < cursor or start - cursor > 12 or any(payload[cursor:start]):
            raise ValueError('extended typed regions overlap or leave unsupported storage')
        if start > cursor:
            zero_regions.append([cursor, start - cursor])
        cursor = end
    return {'format': 'extended-model', 'primary': primary, 'header_words': header,
            'vertices': [[v.x, v.y, v.z, v.flag, v.s, v.t, *v.color] for v in geometry.vertices],
            'display_commands': commands,
            'normal_xy_s8': [[list(row) for row in struct.iter_unpack('>bb', payload[offset:offset + 64])]
                             for offset in normal_offsets],
            'color_descriptors': colors, 'sentinel_words': sentinel,
            'surface_header': surface_header, 'face_words': words, 'zero_regions': zero_regions}


def encode_extended_records(records: dict) -> bytes:
    fields = {'format', 'primary', 'header_words', 'vertices', 'display_commands', 'normal_xy_s8',
              'color_descriptors', 'sentinel_words', 'surface_header', 'face_words', 'zero_regions'}
    if (not isinstance(records, dict) or set(records) != fields
            or records['format'] != 'extended-model' or type(records['primary']) is not bool):
        raise ValueError('invalid extended model schema')
    try:
        header = records['header_words']
        display_end = header[0] + header[1]
        chunks = [(0, struct.pack('>10I', *header)
                   + b''.join(struct.pack('>hhhHhh4B', *v) for v in records['vertices'])
                   + b''.join(struct.pack('>2I', *row) for row in records['display_commands']))]
        for index, table in enumerate(records['normal_xy_s8']):
            if len(table) != 32:
                raise ValueError('extended normals require 32 XY pairs')
            chunks.append((display_end + 64 * index, b''.join(struct.pack('>bb', *xy) for xy in table)))
        if header[4]:
            chunks.append((header[4], b''.join(struct.pack('>I', word)
                                             for word in records['surface_header'] + records['face_words'])))
        descriptors = []
        for item in records['color_descriptors']:
            if (set(item) != {'color_offset', 'vertex_index_offset', 'vertex_count', 'colors', 'vertex_indices'}
                    or item['vertex_count'] != len(item['colors'])
                    or len(item['colors']) != len(item['vertex_indices'])):
                raise ValueError('extended color count or schema is invalid')
            descriptors.append(struct.pack('>3I', item['color_offset'], item['vertex_index_offset'], item['vertex_count']))
            chunks.extend([(item['color_offset'], b''.join(struct.pack('>3B', *rgb) for rgb in item['colors'])),
                           (item['vertex_index_offset'], b''.join(struct.pack('>H', i) for i in item['vertex_indices']))])
        if header[8]:
            chunks.append((header[8], b''.join(descriptors) + struct.pack('>3I', *records['sentinel_words'])))
        for offset, size in records['zero_regions']:
            if type(offset) is not int or type(size) is not int or not 1 <= size <= 12:
                raise ValueError('invalid extended model zero interval')
            chunks.append((offset, bytes(size)))
    except (struct.error, TypeError, IndexError, OverflowError) as error:
        raise ValueError('invalid extended model fields') from error
    cursor, parts = 0, []
    for offset, data in sorted(chunks):
        if offset != cursor:
            raise ValueError('extended model fields overlap or leave a gap')
        parts.append(data)
        cursor += len(data)
    payload = b''.join(parts)
    try:
        checked = extended_records(payload, primary=records['primary'])
    except (struct.error, TypeError, IndexError, OverflowError) as error:
        raise ValueError('invalid extended model boundaries') from error
    if checked != records:
        raise ValueError('extended model records disagree with native layout')
    return payload


CONSUMER_SPANS = (
    (0x1503D368, 208, 'abef1711e0dda14ca8b45eb3689aa144f101bb5f'),
    (0x1503D438, 36, 'add9aec5cb5ff6df58ba80704156c1463b4a2071'),
)


def verify_normal_consumers(code: bytes, base: int) -> None:
    for address, size, digest in CONSUMER_SPANS:
        offset = address - base
        if offset < 0 or hashlib.sha1(code[offset:offset + size]).hexdigest() != digest:
            raise ValueError(f'ROM normal consumer changed at 0x{address:08X}')
