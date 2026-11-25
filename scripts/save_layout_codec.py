"""Native bank-07 widths for 69 unsigned 64-bit save fields."""
from __future__ import annotations

FORMAT = 'save-field-widths-native-v1'
FIELD_COUNT = 69


def encode(record: dict) -> bytes:
    if (type(record) is not dict or set(record) != {'format', 'bit_widths'}
            or record['format'] != FORMAT or type(record['bit_widths']) is not list
            or len(record['bit_widths']) != FIELD_COUNT):
        raise ValueError('save layout requires exactly 69 bit widths')
    widths = record['bit_widths']
    if any(type(width) is not int or not 0 <= width <= 64 for width in widths):
        raise ValueError('save field width must be an integer from 0 through 64')
    return bytes(widths)


def decode(data: bytes) -> dict:
    record = {'format': FORMAT, 'bit_widths': list(data)}
    if encode(record) != data:
        raise ValueError('save layout does not round trip')
    return record
