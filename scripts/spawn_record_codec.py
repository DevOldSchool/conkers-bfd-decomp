"""Native 48-byte spawn records with six constrained, unexposed zero lanes.

Byte 0x12 has an unresolved nonzero instance. This subset rejects it instead
of exposing an opaque field or inferring that it is padding.
"""
from __future__ import annotations

import math
import struct

FORMAT = 'spawn-record-native-v1'
FIELDS = ((0x00, 'u16'), (0x02, 'u8'), (0x03, 'u8'), (0x04, 'u8'),
          (0x06, 's16'), (0x08, 's16'), (0x0A, 's16'), (0x0C, 'u8'),
          (0x0D, 'u8'), (0x0E, 'u8'), (0x0F, 'u8'), (0x10, 'u8'),
          (0x11, 'u8'), (0x13, 'u8'), (0x14, 's16'), (0x18, 'u32'),
          (0x1C, 'u8'), (0x1D, 'u8'), (0x20, 'f32'), (0x24, 'f32'),
          (0x28, 'u8'), (0x29, 'u8'), (0x2A, 'u16'), (0x2C, 'u16'),
          (0x2E, 'u8'), (0x2F, 'u8'))
FORMATS = {'u8': ('B', 0, 255), 'u16': ('H', 0, 65535),
           's16': ('h', -32768, 32767), 'u32': ('I', 0, 0xffffffff),
           'f32': ('f', None, None)}
ZERO_OFFSETS = (0x05, 0x12, 0x16, 0x17, 0x1E, 0x1F)


def key(offset, kind):
    return f'{kind}_{offset:02X}'


def encode(records):
    if type(records) is not list or len(records) > 255:
        raise ValueError('spawn records require a list of at most 255 records')
    out = bytearray(48 * len(records))
    for index, record in enumerate(records):
        if type(record) is not dict or set(record) != {key(o, k) for o, k in FIELDS}:
            raise ValueError('spawn record has unknown or missing fields')
        for offset, kind in FIELDS:
            value = record[key(offset, kind)]
            fmt, low, high = FORMATS[kind]
            if kind == 'f32':
                try:
                    valid = type(value) in (float, int) and math.isfinite(value)
                except OverflowError:
                    valid = False
            else:
                valid = type(value) is int and low <= value <= high
            if not valid:
                raise ValueError(f'invalid spawn field {key(offset, kind)}')
            try:
                struct.pack_into('>' + fmt, out, index * 48 + offset, value)
            except (OverflowError, struct.error) as error:
                raise ValueError(f'invalid spawn field {key(offset, kind)}') from error
    return bytes(out)


def decode(data):
    if len(data) % 48 or len(data) > 255 * 48:
        raise ValueError('invalid native spawn record extent')
    records = [{key(off, kind): struct.unpack_from('>' + FORMATS[kind][0], data, start + off)[0]
                for off, kind in FIELDS} for start in range(0, len(data), 48)]
    if encode(records) != data:
        raise ValueError('spawn record has unexplained storage')
    return records
