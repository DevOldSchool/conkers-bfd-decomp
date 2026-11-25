"""Reviewed 40-byte collision responses with a constrained zero lane at +33.

The two original records with nonzero +33 are deliberately unsupported. Its
meaning is unresolved; it is not described as alignment or exposed as raw data.
"""
from __future__ import annotations

import math
import struct

FORMAT = 'animation-control-collisions-native-v1'
# Names describe native accesses without guessing gameplay labels.
FIELDS = (('response', 0, 'B'), ('sound', 4, 'I'),
          ('callback', 8, 'B'), ('angle', 9, 'B'), ('distance', 10, 'B'),
          ('height', 12, 'h'), ('extent', 14, 'B'), ('damage_flags', 15, 'B'),
          ('response_angle', 16, 'B'), ('state_3c', 20, 'f'),
          ('state_20', 24, 'f'), ('state_24', 28, 'f'),
          ('state_109', 32, 'B'), ('invulnerability', 34, 'B'), ('flags', 36, 'H'))


def encode(records):
    if type(records) is not list or not records or len(records) > 256:
        raise ValueError('collision controls require 1..256 records')
    out = bytearray(40 * len(records))
    for index, record in enumerate(records):
        if type(record) is not dict or set(record) != {name for name, _, _ in FIELDS}:
            raise ValueError('collision response has unknown or missing fields')
        for name, offset, kind in FIELDS:
            value = record[name]
            if kind == 'f':
                try:
                    valid = type(value) in (float, int) and math.isfinite(value)
                except OverflowError:
                    valid = False
            else:
                lo, hi = {'B': (0, 255), 'H': (0, 65535),
                          'I': (0, 0xffffffff), 'h': (-32768, 32767)}[kind]
                valid = type(value) is int and lo <= value <= hi
            if not valid:
                raise ValueError(f'invalid collision field {name}')
            try:
                struct.pack_into('>' + kind, out, index * 40 + offset, value)
            except (OverflowError, struct.error) as error:
                raise ValueError(f'invalid collision field {name}') from error
    return bytes(out)


def decode(data):
    if not data or len(data) % 40 or len(data) > 256 * 40:
        raise ValueError('invalid collision response extent')
    if any(data[start + 33] for start in range(0, len(data), 40)):
        raise ValueError('collision byte +33 has no established consumer')
    records = [{name: struct.unpack_from('>' + kind, data, start + offset)[0]
                for name, offset, kind in FIELDS} for start in range(0, len(data), 40)]
    if encode(records) != data:
        raise ValueError('collision response has unexplained storage')
    return records
