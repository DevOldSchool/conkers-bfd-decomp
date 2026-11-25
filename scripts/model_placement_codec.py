"""Additional native model-placement parameters and complete bank-0B records."""
from __future__ import annotations

import struct

try:
    from scripts import scene_field_codec as fields
except ModuleNotFoundError:
    import scene_field_codec as fields

PROPS_FORMAT = 'model-placement-records-native-v1'
PARAMETERS_FORMAT = 'model-placement-parameters-native-v1'
# Native loads in func_150039E0. Offset labels avoid guessing callback meanings.
PARAMETERS = ((0x18, 'u32'), (0x2C, 'u8'), (0x2D, 'u8'), (0x2E, 'u16'),
              (0x30, 'u16'), (0x32, 'u8'), (0x38, 'u32'), (0x3E, 'u16'), (0x40, 'u16'))
FORMATS = {'u8': ('B', 255), 'u16': ('H', 65535), 'u32': ('I', 0xffffffff)}
ZERO_OFFSETS = (*range(0x1C, 0x20), *range(0x35, 0x38), 0x3D, 0x42, 0x43)


def key(offset, kind):
    return f'{kind}_{offset:02X}'


def encode_parameters(records):
    if type(records) is not list or len(records) > 255:
        raise ValueError('invalid model parameter record count')
    spans = []
    for index, record in enumerate(records):
        if type(record) is not dict or set(record) != {key(o, k) for o, k in PARAMETERS}:
            raise ValueError('invalid model parameter fields')
        for offset, kind in PARAMETERS:
            fmt, high = FORMATS[kind]
            value = record[key(offset, kind)]
            if type(value) is not int or not 0 <= value <= high:
                raise ValueError(f'invalid model parameter {key(offset, kind)}')
            spans.append((index * 68 + offset, struct.pack('>' + fmt, value)))
    return spans


def decode_parameters(data):
    if len(data) % 68 or len(data) > 255 * 68:
        raise ValueError('invalid model parameter extent')
    return [{key(o, k): struct.unpack_from('>' + FORMATS[k][0], data, base + o)[0]
             for o, k in PARAMETERS} for base in range(0, len(data), 68)]


def encode_props(records):
    if type(records) is not list or not 1 <= len(records) <= 255:
        raise ValueError('model placements require 1..255 records')
    models, parameters = [], []
    for record in records:
        if type(record) is not dict or set(record) != {'model', 'parameters'}:
            raise ValueError('invalid model placement schema')
        models.append(record['model'])
        parameters.append(record['parameters'])
    size = len(records) * 68
    out = bytearray((size + 15) // 16 * 16)
    spans = fields.encode({'format': fields.FORMATS[2], 'records': models}, 2)
    spans += encode_parameters(parameters)
    for offset, payload in spans:
        out[offset:offset + len(payload)] = payload
    return bytes(out)


def decode_props(data):
    count = len(data) // 68
    if not 1 <= count <= 255 or len(data) != (count * 68 + 15) // 16 * 16:
        raise ValueError('invalid padded model placement extent')
    body = data[:count * 68]
    models = fields.decode(body, 2)['records']
    parameters = decode_parameters(body)
    records = [{'model': model, 'parameters': parameter}
               for model, parameter in zip(models, parameters, strict=True)]
    if encode_props(records) != data:
        raise ValueError('model placement has unexplained nonzero storage')
    return records
