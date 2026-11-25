"""Direct models whose explicit normal table covers fewer than 32 cache slots."""
from __future__ import annotations

import struct

try:
    from scripts import model_assets
except ModuleNotFoundError:
    import model_assets


FORMAT = 'short-normal-model'


def decode(payload):
    geometry = model_assets.parse_model_geometry(payload)
    header = list(geometry.header_words)
    display_end = header[0] + header[1]
    normal_start, normal_size, face_start, face_size = header[2:6]
    if (header[0] != 40 + 16 * len(geometry.vertices)
            or normal_start != display_end or not 0 < normal_size < 64 or normal_size % 2
            or face_start != normal_start + normal_size or face_size != 4 * len(geometry.faces)
            or not face_size or header[6:] != [0, 0, 0, 0x80000000]):
        raise ValueError('short normal model has unsupported region boundaries')
    commands = [list(row) for row in struct.iter_unpack('>II', payload[header[0]:display_end])]
    base, used = None, set()
    for command, argument in commands:
        if command == model_assets.CHARACTER_CUSTOM_MOVEMEM_COMMAND:
            if argument != normal_start:
                raise ValueError('short normal command does not select the explicit table')
            base = argument
        elif command >> 24 == 1:
            count, stop = command >> 12 & 255, command >> 1 & 127
            start = stop - count
            if base is None or not 0 <= start < stop <= normal_size // 2:
                raise ValueError('vertex load reads outside the short normal table')
            used.update(range(start, stop))
    if used != set(range(normal_size // 2)):
        raise ValueError('short normal table contains unreferenced pairs')
    tail = len(payload) - face_start - face_size
    if not 0 <= tail <= 12 or any(payload[face_start + face_size:]):
        raise ValueError('short normal model has unsupported trailing storage')
    return {'format': FORMAT, 'header_words': header,
            'vertices': [[v.x, v.y, v.z, v.flag, v.s, v.t, *v.color] for v in geometry.vertices],
            'display_commands': commands,
            'normal_xy_s8': [list(row) for row in struct.iter_unpack('>bb', payload[normal_start:face_start])],
            'face_words': list(struct.unpack_from(f'>{len(geometry.faces)}I', payload, face_start)),
            'zero_tail_bytes': tail}


def encode(records):
    fields = {'format', 'header_words', 'vertices', 'display_commands', 'normal_xy_s8',
              'face_words', 'zero_tail_bytes'}
    if (type(records) is not dict or set(records) != fields or records['format'] != FORMAT
            or type(records['zero_tail_bytes']) is not int or not 0 <= records['zero_tail_bytes'] <= 12):
        raise ValueError('invalid short normal model schema')
    try:
        payload = (struct.pack('>10I', *records['header_words'])
                   + b''.join(struct.pack('>hhhHhh4B', *row) for row in records['vertices'])
                   + b''.join(struct.pack('>II', *row) for row in records['display_commands'])
                   + b''.join(struct.pack('>bb', *row) for row in records['normal_xy_s8'])
                   + b''.join(struct.pack('>I', word) for word in records['face_words'])
                   + bytes(records['zero_tail_bytes']))
        checked = decode(payload)
    except (struct.error, TypeError, IndexError, OverflowError) as error:
        raise ValueError('invalid short normal model fields') from error
    if checked != records:
        raise ValueError('short normal fields disagree with native layout')
    return payload
