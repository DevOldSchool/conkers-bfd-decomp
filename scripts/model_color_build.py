"""Native primary-surface model with vertex-color animation descriptors."""
from __future__ import annotations

import hashlib
import struct

try:
    from scripts import model_assets
except ModuleNotFoundError:
    import model_assets


def color_records(payload: bytes) -> dict:
    geometry = model_assets.parse_model_geometry(payload)
    header = list(geometry.header_words)
    table_size = geometry.vertex_color_animation_table_size
    if (any(header[2:4] + header[6:8]) or not header[8]
            or header[9] != (0x80000000 | table_size)
            or table_size != 12 * (len(geometry.vertex_color_animation_descriptors) + 1)
            or header[8] + table_size != header[4]
            or header[4] + header[5] != len(payload)):
        raise ValueError('unsupported color-animation model regions')
    display_end = header[0] + header[1]
    commands = [list(row) for row in struct.iter_unpack('>II', payload[header[0]:display_end])]
    if any(command == 0xDC38000E for command, _ in commands):
        raise ValueError('color-animation model has an unsupported normal region')
    segment = model_assets.ModelSegment(0, 0, len(payload), True, payload)
    words = model_assets.bank_04_collision_surface_words(segment, geometry)
    ranges = [(0, display_end), (header[8], header[4]), (header[4], len(payload))]
    descriptors = []
    for item in geometry.vertex_color_animation_descriptors:
        rgb_start, index_start, count = item.color_data_offset, item.vertex_index_offset, item.vertex_count
        descriptors.append({'color_offset': rgb_start, 'vertex_index_offset': index_start,
                            'vertex_count': count,
                            'colors': [list(row) for row in struct.iter_unpack(
                                '>3B', payload[rgb_start:rgb_start + 3 * count])],
                            'vertex_indices': list(struct.unpack_from(f'>{count}H', payload, index_start))})
        ranges.extend([(rgb_start, rgb_start + 3 * count), (index_start, index_start + 2 * count)])
    sentinel = list(struct.unpack_from('>3I', payload, header[4] - 12))
    if sentinel != [0, 0, 0]:
        raise ValueError('color-animation sentinel has unknown fields')
    cursor, zero_regions = 0, []
    for start, end in sorted(ranges):
        if start < cursor or any(payload[cursor:start]):
            raise ValueError('color-animation ranges overlap or leave opaque data')
        if start > cursor:
            if start - cursor not in (1, 2):
                raise ValueError('unsupported color-animation zero region')
            zero_regions.append([cursor, start - cursor])
        cursor = end
    return {'format': 'primary-color-surface-direct', 'header_words': header,
            'vertices': [[v.x, v.y, v.z, v.flag, v.s, v.t, *v.color] for v in geometry.vertices],
            'display_commands': commands, 'color_descriptors': descriptors,
            'sentinel_words': sentinel, 'zero_regions': zero_regions,
            'surface_header': list(struct.unpack_from('>II', payload, header[4])),
            'surface_words': list(words)}


def encode_color_records(records: dict) -> bytes:
    fields = {'format', 'header_words', 'vertices', 'display_commands', 'color_descriptors',
              'sentinel_words', 'zero_regions', 'surface_header', 'surface_words'}
    if (not isinstance(records, dict) or set(records) != fields
            or records['format'] != 'primary-color-surface-direct'):
        raise ValueError('invalid color-animation model schema')
    try:
        header = records['header_words']
        chunks = [(0, struct.pack('>10I', *header)
                   + b''.join(struct.pack('>hhhHhh4B', *v) for v in records['vertices'])
                   + b''.join(struct.pack('>II', *row) for row in records['display_commands'])),
                  (header[4], struct.pack('>II', *records['surface_header'])
                   + b''.join(struct.pack('>I', word) for word in records['surface_words']))]
        table = []
        for item in records['color_descriptors']:
            if (set(item) != {'color_offset', 'vertex_index_offset', 'vertex_count', 'colors', 'vertex_indices'}
                    or item['vertex_count'] != len(item['colors'])
                    or item['vertex_count'] != len(item['vertex_indices'])):
                raise ValueError('color-animation descriptor count or fields changed')
            table.append(struct.pack('>III', item['color_offset'], item['vertex_index_offset'], item['vertex_count']))
            chunks.extend([(item['color_offset'], b''.join(struct.pack('>3B', *rgb) for rgb in item['colors'])),
                           (item['vertex_index_offset'], b''.join(struct.pack('>H', i) for i in item['vertex_indices']))])
        table.append(struct.pack('>3I', *records['sentinel_words']))
        chunks.append((header[8], b''.join(table)))
        for offset, size in records['zero_regions']:
            if type(offset) is not int or type(size) is not int or size not in (1, 2):
                raise ValueError('invalid color-animation zero region')
            chunks.append((offset, bytes(size)))
    except (struct.error, TypeError, IndexError, OverflowError) as error:
        raise ValueError('invalid native color-animation record') from error
    cursor, parts = 0, []
    for offset, data in sorted(chunks):
        if offset != cursor:
            raise ValueError('color-animation records overlap or leave an uncovered gap')
        parts.append(data)
        cursor += len(data)
    payload = b''.join(parts)
    if color_records(payload) != records:
        raise ValueError('color-animation records disagree with native boundaries')
    return payload


def verify_consumers(code: bytes, base: int) -> None:
    for address, size, digest in (
        (0x15003120, 204, '3d917f11eef25bd8cf376178f84c6b2fed203180'),
        (0x151739B0, 688, '9b41bacec4b3981885419cc7d5185700cae3a273'),
    ):
        offset = address - base
        if offset < 0 or hashlib.sha1(code[offset:offset + size]).hexdigest() != digest:
            raise ValueError(f'ROM vertex-color consumer changed at 0x{address:08X}')
