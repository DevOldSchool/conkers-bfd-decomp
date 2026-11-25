"""Native scene containers; unknown header fields have no source or credit."""
from __future__ import annotations

import struct

FORMAT = 'scene-header-native-v1'
# Offset, native scalar type. Evidence: docs/evidence/data-layout/us_scene_headers.md.
FIELDS = (
    (0x00, 'u16'),
    (0x02, 'u16'),
    (0x05, 'u8'),
    (0x06, 'u8'),
    (0x07, 'u8'),
    (0x08, 'u8'),
    (0x09, 'u8'),
    (0x0A, 'u8'),
    (0x0B, 'u8'),
    (0x0C, 'u8'),
    (0x0D, 'u8'),
    (0x0E, 'u8'),
    (0x0F, 'u8'),
    (0x10, 'u8'),
    (0x11, 's8'),
    (0x12, 'u8'),
    (0x13, 'u8'),
    (0x14, 'u8'),
    (0x16, 's16'),
    (0x18, 'u16'),
    (0x1A, 'u16'),
    (0x1C, 'u16'),
    (0x1E, 'u16'),
    (0x21, 'u8'),
    (0x29, 'u8'),
    (0x2A, 'u8'),
    (0x2B, 'u8'),
    (0x2C, 's16'),
    (0x2E, 'u16'),
    (0x30, 'u16'),
    (0x32, 's16'),
    (0x34, 'u16'),
    (0x36, 'u16'),
    (0x38, 'u8'),
    (0x39, 'u8'),
    (0x3A, 's16'),
    (0x3C, 's16'),
    (0x3E, 's16'),
    (0x40, 's16'),
    (0x42, 'u8'),
    (0x43, 'u8'),
    (0x44, 'u8'),
    (0x45, 'u8'),
    (0x46, 's8'),
    (0x49, 'u8'),
    (0x4A, 'u8'),
    (0x4B, 'u8'),
)
FORMATS = {'u8': ('B', 0, 255), 's8': ('b', -128, 127),
           'u16': ('H', 0, 65535), 's16': ('h', -32768, 32767)}


def key(offset, kind):
    return f'{kind}_{offset:02X}'


def scalar(value, kind):
    fmt, low, high = FORMATS[kind]
    if type(value) is not int or not low <= value <= high:
        raise ValueError(f'scene field requires {kind}')
    return struct.pack('>' + fmt, value)


def encode(source):
    if (type(source) is not dict or set(source) != {'format', 'fields', 'lookup_ids'}
            or source['format'] != FORMAT or type(source['fields']) is not dict
            or set(source['fields']) != {key(off, kind) for off, kind in FIELDS}
            or type(source['lookup_ids']) is not list):
        raise ValueError('invalid scene header source')
    fields = source['fields']
    count = fields['u8_12']
    if type(count) is not int or count != len(source['lookup_ids']):
        raise ValueError('scene lookup count differs from its ID list')
    ids = b''.join(scalar(value, 'u16') for value in source['lookup_ids'])
    # Two native records: 76-byte header and the counted halfword list.
    spans = [(0, struct.pack('>4I', 16, 76, 96, 0x80000000 | len(ids)))]
    spans += [(16 + off, scalar(fields[key(off, kind)], kind)) for off, kind in FIELDS]
    spans.append((92, bytes(4)))
    if ids:
        spans.append((96, ids))
    padding = bytes((-(96 + len(ids))) % 8)
    if padding:
        spans.append((96 + len(ids), padding))
    merged = []
    for offset, data in sorted(spans):
        if merged and merged[-1][0] + len(merged[-1][1]) == offset:
            previous, payload = merged[-1]
            merged[-1] = previous, payload + data
        else:
            merged.append((offset, data))
    return merged


def decode(data):
    if len(data) < 96:
        raise ValueError('truncated native scene container')
    fields = {key(off, kind): struct.unpack_from('>' + FORMATS[kind][0], data, 16 + off)[0]
              for off, kind in FIELDS}
    count = fields['u8_12']
    end = 96 + count * 2
    if len(data) != (end + 7) // 8 * 8:
        raise ValueError('scene container extent differs from its native count')
    source = {'format': FORMAT, 'fields': fields,
              'lookup_ids': list(struct.unpack_from('>' + str(count) + 'H', data, 96))}
    if any(data[offset:offset + len(fresh)] != fresh for offset, fresh in encode(source)):
        raise ValueError('scene index or alignment differs from generated native layout')
    return source
