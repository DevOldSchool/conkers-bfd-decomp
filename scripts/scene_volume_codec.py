"""Typed US scene trigger volumes and spherical collision records."""
from __future__ import annotations
import math
import struct

VOLUME_FORMAT = 'conker-scene-trigger-volumes-v1'
SPHERE_FORMAT = 'conker-scene-collision-spheres-v1'
VOLUME_FIELDS = {'position', 'dimensions', 'angles', 'disabled', 'shape', 'kind',
                 'flags', 'mode', 'action_value', 'packed_parameter', 'initial_state'}
SPHERE_FIELDS = {'position', 'radius', 'response_parameter', 'activation_index'}


def integer(value, low, high):
    if type(value) is not int or not low <= value <= high:
        raise ValueError('scene field exceeds its native integer width')
    return value


def floats(values, count):
    if not isinstance(values, list) or len(values) != count:
        raise ValueError('scene float vector has an invalid dimension')
    try:
        if any(type(value) not in (float, int) or not math.isfinite(value) for value in values):
            raise ValueError('scene float field must be finite')
        return struct.pack(f'>{count}f', *values)
    except (struct.error, OverflowError) as error:
        raise ValueError('scene float field exceeds native storage') from error


def vector16(values):
    if not isinstance(values, list) or len(values) != 3:
        raise ValueError('scene signed coordinate vector has an invalid dimension')
    return struct.pack('>3h', *(integer(value, -32768, 32767) for value in values))


def records(source, format):
    if (not isinstance(source, dict) or set(source) != {'format', 'records'}
            or source['format'] != format or not isinstance(source['records'], list)):
        raise ValueError('invalid scene record source schema')
    return source['records']


def encode_volumes(source):
    output = bytearray()
    for record in records(source, VOLUME_FORMAT):
        if not isinstance(record, dict) or set(record) != VOLUME_FIELDS:
            raise ValueError('invalid trigger-volume fields')
        if type(record['disabled']) is not bool:
            raise ValueError('trigger disabled state must be boolean')
        output.extend(vector16(record['position']))
        output.extend(vector16(record['dimensions']))
        output.extend(floats(record['angles'], 2))
        output.extend(struct.pack('>4B', int(record['disabled']),
            integer(record['shape'], 0, 3) | integer(record['kind'], 0, 63) << 2,
            integer(record['flags'], 0, 15), integer(record['mode'], 0, 255)))
        output.extend(struct.pack('>iIi', integer(record['action_value'], -(1 << 31), (1 << 31) - 1),
            integer(record['packed_parameter'], 0, (1 << 32) - 1),
            integer(record['initial_state'], -(1 << 31), (1 << 31) - 1)))
        # func_150A0D14 overwrites the four reserved trigonometric cache slots.
        # The bounded stored format initializes all four to positive float zero.
        output.extend(bytes(16))
    return bytes(output)


def decode_volumes(data):
    if len(data) % 52:
        raise ValueError('trigger-volume storage has a partial 52-byte record')
    output = {'format': VOLUME_FORMAT, 'records': []}
    for offset in range(0, len(data), 52):
        position = list(struct.unpack_from('>3h', data, offset))
        dimensions = list(struct.unpack_from('>3h', data, offset + 6))
        angles = list(struct.unpack_from('>2f', data, offset + 12))
        disabled, kind_shape, flags, mode = struct.unpack_from('>4B', data, offset + 20)
        value, parameter, state = struct.unpack_from('>iIi', data, offset + 24)
        if disabled not in (0, 1) or data[offset + 36:offset + 52] != bytes(16):
            raise ValueError('trigger record has unsupported initial state or nonzero runtime cache')
        output['records'].append({'position': position, 'dimensions': dimensions, 'angles': angles,
            'disabled': bool(disabled), 'shape': kind_shape & 3, 'kind': kind_shape >> 2,
            'flags': flags, 'mode': mode, 'action_value': value,
            'packed_parameter': parameter, 'initial_state': state})
    if encode_volumes(output) != data:
        raise ValueError('trigger-volume source does not reproduce native storage')
    return output


def encode_spheres(source):
    output = bytearray()
    for record in records(source, SPHERE_FORMAT):
        if not isinstance(record, dict) or set(record) != SPHERE_FIELDS:
            raise ValueError('invalid collision-sphere fields')
        output.extend(floats(record['position'], 3))
        output.extend(floats([record['radius'], record['response_parameter'], record['activation_index']], 3))
    return bytes(output)


def decode_spheres(data):
    if len(data) % 24:
        raise ValueError('sphere storage has a partial 24-byte record')
    output = {'format': SPHERE_FORMAT, 'records': []}
    for values in struct.iter_unpack('>6f', data):
        output['records'].append({'position': list(values[:3]), 'radius': values[3],
            'response_parameter': values[4], 'activation_index': values[5]})
    if encode_spheres(output) != data:
        raise ValueError('sphere source does not reproduce native storage')
    return output


def encode(source, child):
    if child == 3:
        return encode_spheres(source)
    if child == 5:
        return encode_volumes(source)
    raise ValueError('unsupported scene volume child')


def decode(data, child):
    if child == 3:
        return decode_spheres(data)
    if child == 5:
        return decode_volumes(data)
    raise ValueError('unsupported scene volume child')
