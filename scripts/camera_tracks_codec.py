"""Bank-1B frame deltas consumed by the native camera state update."""
from __future__ import annotations

import math
import struct
import zlib

FORMAT = 'camera-state-deltas-native-v1'
FIELDS = ('delta_860_868', 'delta_854_85c')


def encode(record: dict) -> bytes:
    if (type(record) is not dict or set(record) != {'format', 'frames'}
            or record['format'] != FORMAT or type(record['frames']) is not list
            or not 1 <= len(record['frames']) <= 256):
        raise ValueError('camera track requires 1 through 256 frames')
    out = bytearray()
    for frame in record['frames']:
        if type(frame) is not dict or set(frame) != set(FIELDS):
            raise ValueError('camera frame requires both native delta vectors')
        values = []
        for field in FIELDS:
            vector = frame[field]
            if type(vector) is not list or len(vector) != 3:
                raise ValueError('camera delta vector requires three floats')
            for value in vector:
                if type(value) not in (int, float):
                    raise ValueError('camera delta must be a finite f32')
                try:
                    packed = struct.pack('>f', value)
                    if not math.isfinite(struct.unpack('>f', packed)[0]):
                        raise ValueError('camera delta must be a finite f32')
                except (OverflowError, struct.error) as error:
                    raise ValueError('camera delta must be a finite f32') from error
                values.append(packed)
        out.extend(b''.join(values))
    return bytes(out)


def decode(data: bytes) -> dict:
    if not data or len(data) % 24 or len(data) > 256 * 24:
        raise ValueError('camera track is not a bounded array of 24-byte frames')
    record = {'format': FORMAT, 'frames': [
        {FIELDS[0]: list(row[:3]), FIELDS[1]: list(row[3:])}
        for row in struct.iter_unpack('>6f', data)]}
    if encode(record) != data:
        raise ValueError('camera track does not round trip')
    return record


def compress(data: bytes) -> bytes:
    compressor = zlib.compressobj(level=6, wbits=-15)
    return struct.pack('>I', len(data)) + compressor.compress(data) + compressor.flush()


def unpack(blob: bytes) -> bytes:
    if len(blob) < 5:
        raise ValueError('truncated camera track')
    size = struct.unpack_from('>I', blob)[0]
    if not 24 <= size <= 256 * 24 or size % 24:
        raise ValueError('invalid camera track decoded size')
    decoder = zlib.decompressobj(wbits=-15)
    try:
        data = decoder.decompress(blob[4:], size + 1)
    except zlib.error as error:
        raise ValueError('invalid camera track compressed stream') from error
    if (len(data) != size or not decoder.eof or decoder.unused_data
            or decoder.unconsumed_tail):
        raise ValueError('camera track stream has an invalid extent')
    decode(data)
    return data
