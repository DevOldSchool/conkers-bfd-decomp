"""Native eight-byte asset directory records, separate from their payloads."""
from __future__ import annotations
import struct

FORMAT = 'asset-directory-native-v1'


def integer(value, bits):
    if type(value) is not int or not 0 <= value < 1 << bits:
        raise ValueError(f'asset directory requires an unsigned {bits}-bit integer')
    return value


def encode(record):
    if (type(record) is not dict or set(record) != {'format', 'entries'}
            or record['format'] != FORMAT or type(record['entries']) is not list
            or not record['entries']):
        raise ValueError('invalid asset directory source')
    out = bytearray()
    previous_end = len(record['entries']) * 8
    for entry in record['entries']:
        if type(entry) is not dict or set(entry) != {'relative_offset', 'stored_size', 'flags'}:
            raise ValueError('invalid asset directory entry')
        offset = integer(entry['relative_offset'], 32)
        size = integer(entry['stored_size'], 28)
        flags = integer(entry['flags'], 4)
        if size:
            if offset < previous_end or offset + size > 0xffffffff:
                raise ValueError('overlapping or overflowing asset directory extent')
            previous_end = offset + size
        out.extend(struct.pack('>II', offset, size | flags << 28))
    if record['entries'][0]['relative_offset'] != len(out):
        raise ValueError('first offset does not describe the directory extent')
    return bytes(out)


def decode(data):
    if not data or len(data) % 8:
        raise ValueError('asset directory is not a nonempty eight-byte table')
    record = {'format': FORMAT, 'entries': [
        {'relative_offset': offset, 'stored_size': word & 0x0fffffff, 'flags': word >> 28}
        for offset, word in struct.iter_unpack('>II', data)]}
    if encode(record) != data:
        raise ValueError('asset directory does not round trip')
    return record
