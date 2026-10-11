"""Native bank-04 bundle descriptors and primary collision-surface records."""
from __future__ import annotations

import hashlib
import struct

try:
    from scripts import model_assets, model_color_build
except ModuleNotFoundError:
    import model_assets, model_color_build


def surface_records(payload: bytes) -> dict:
    geometry = model_assets.parse_model_geometry(payload)
    header = list(geometry.header_words)
    if header[8]:
        return model_color_build.color_records(payload)
    if (any(header[2:4] + header[6:9]) or header[9] != 0x80000000
            or header[4] != header[0] + header[1]):
        raise ValueError('unsupported primary surface-model regions')
    segment = model_assets.ModelSegment(0, 0, len(payload), True, payload)
    words = model_assets.bank_04_collision_surface_words(segment, geometry)
    commands = [list(row) for row in struct.iter_unpack(
        '>II', payload[header[0]:header[0] + header[1]])]
    if any(command[0] == 0xDC38000E for command in commands):
        raise ValueError('primary surface model has an unsupported normal region')
    end = header[4] + header[5]
    suffix = len(payload) - end
    if suffix not in (0, 4, 8, 12) or any(payload[end:]):
        raise ValueError('unsupported primary surface-model suffix')
    return {'format': 'primary-surface-direct', 'header_words': header,
            'vertices': [[v.x, v.y, v.z, v.flag, v.s, v.t, *v.color] for v in geometry.vertices],
            'display_commands': commands,
            'surface_header': list(struct.unpack_from('>II', payload, header[4])),
            'surface_words': list(words), 'zero_suffix_bytes': suffix}


def encode_surface_records(records: dict) -> bytes:
    if isinstance(records, dict) and records.get('format') == 'primary-color-surface-direct':
        return model_color_build.encode_color_records(records)
    fields = {'format', 'header_words', 'vertices', 'display_commands',
              'surface_header', 'surface_words', 'zero_suffix_bytes'}
    if (not isinstance(records, dict) or set(records) != fields
            or records['format'] != 'primary-surface-direct'
            or type(records['zero_suffix_bytes']) is not int
            or records['zero_suffix_bytes'] not in (0, 4, 8, 12)):
        raise ValueError('invalid primary surface-model record schema')
    try:
        payload = (struct.pack('>10I', *records['header_words'])
                   + b''.join(struct.pack('>hhhHhh4B', *row) for row in records['vertices'])
                   + b''.join(struct.pack('>II', *row) for row in records['display_commands'])
                   + struct.pack('>II', *records['surface_header'])
                   + b''.join(struct.pack('>I', word) for word in records['surface_words'])
                   + bytes(records['zero_suffix_bytes']))
    except (struct.error, TypeError, OverflowError) as error:
        raise ValueError('invalid native surface-model record') from error
    if surface_records(payload) != records:
        raise ValueError('surface-model records disagree with declared boundaries')
    return payload


def bundle_records(payload: bytes, decode_direct) -> dict:
    segments = model_assets.parse_model_bundle(payload)
    if not segments[0].data:
        raise ValueError('reviewed bundle lacks its primary surface model')
    records = []
    for segment in segments:
        if not segment.data:
            records.append(None)
        elif segment.index == 0:
            records.append(surface_records(segment.data))
        else:
            records.append(decode_direct(segment.data))
    return {'format': 'model-bundle',
            'descriptors': [[s.offset, s.size | (0x80000000 if s.final_flag else 0)] for s in segments],
            'segments': records}


def encode_bundle_records(records: dict, encode_direct, decode_direct) -> bytes:
    if (not isinstance(records, dict) or set(records) != {'format', 'descriptors', 'segments'}
            or records['format'] != 'model-bundle'
            or not isinstance(records['descriptors'], list)
            or not isinstance(records['segments'], list)
            or len(records['segments']) < 4
            or len(records['segments']) != len(records['descriptors'])
            or records['segments'][0] is None):
        raise ValueError('invalid native model-bundle schema')
    try:
        header = b''.join(struct.pack('>II', *row) for row in records['descriptors'])
        parts = [encode_surface_records(records['segments'][0])]
        parts.extend(b'' if row is None else encode_direct(row) for row in records['segments'][1:])
    except (struct.error, TypeError, OverflowError) as error:
        raise ValueError('invalid native model-bundle record') from error
    payload = header + b''.join(parts)
    if bundle_records(payload, decode_direct) != records:
        raise ValueError('model-bundle records disagree with declared boundaries')
    return payload


def verify_consumers(code: bytes, base: int) -> None:
    """Pin full loader, surface-pointer setup and indexed 32-bit consumer spans."""
    for address, size, digest in (
        (0x150031EC, 712, 'ed48d58ffb38dab90c140a0d547dbdae13f3225a'),
        (0x150039BC, 36, '3158e418c38cbfc95446c9535ecc73bed4bc28ea'),
        (0x150450CC, 576, 'e6792bb72b55c4d4ff70be77513bc6dd9fc789be'),
    ):
        offset = address - base
        if offset < 0 or hashlib.sha1(code[offset:offset + size]).hexdigest() != digest:
            raise ValueError(f'ROM model-bundle consumer changed at 0x{address:08X}')
