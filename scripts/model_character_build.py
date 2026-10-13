"""Typed native bank-01 character storage; no opaque regions or compressed inputs."""
from __future__ import annotations

import hashlib
import struct

try:
    from scripts import model_assets
except ModuleNotFoundError:
    import model_assets


def character_records(payload: bytes) -> dict:
    geometry, _ = model_assets.parse_character_model_geometry(payload)
    header = list(geometry.header_words)
    display = geometry.display_list_offset
    display_end = display + geometry.display_list_size
    ranges = [(0, 56), (56, 56 + 16 * len(geometry.vertices)), (display, display_end)]
    formats = ('>I', '>I', '>bBBB3f', '>IIHH', '>bb', '>I', '>B')
    names = ('vertex_boundaries', 'primary_pointers', 'joints', 'texture_descriptors',
             'normal_xy_s8', 'secondary_pointers', 'procedural_joint_indices')
    result = {'format': 'character-native', 'header_words': header,
              'vertices': [[v.x, v.y, v.z, v.flag, v.s, v.t, *v.color] for v in geometry.vertices],
              'display_commands': [list(row) for row in struct.iter_unpack('>II', payload[display:display_end])]}
    for pair, (name, fmt) in enumerate(zip(names, formats)):
        offset, size = header[2 * pair:2 * pair + 2]
        if pair == 6:
            size &= 0x7fffffff
        if size % struct.calcsize(fmt):
            raise ValueError(f'character {name} has a partial native record')
        result[name] = [list(row) for row in struct.iter_unpack(fmt, payload[offset:offset + size])]
        if size:
            ranges.append((offset, offset + size))
    # Preserve only small, observed all-zero alignment intervals. Everything
    # else must belong to a typed native region, including both display passes.
    cursor, zero_regions = 0, []
    for start, end in sorted(ranges) + [(len(payload), len(payload))]:
        if start < cursor or start - cursor > 15 or any(payload[cursor:start]):
            raise ValueError('character regions overlap or leave unsupported storage')
        if start > cursor:
            zero_regions.append([cursor, start - cursor])
        cursor = end
    result['zero_regions'] = zero_regions
    return result


def encode_character_records(records: dict) -> bytes:
    names = ('vertex_boundaries', 'primary_pointers', 'joints', 'texture_descriptors',
             'normal_xy_s8', 'secondary_pointers', 'procedural_joint_indices')
    fields = {'format', 'header_words', 'vertices', 'display_commands', 'zero_regions', *names}
    if (not isinstance(records, dict) or set(records) != fields
            or records['format'] != 'character-native'):
        raise ValueError('invalid character record schema')
    try:
        header = records['header_words']
        if len(header) != 14:
            raise ValueError('character header requires seven native pairs')
        pointers = records['primary_pointers'] + records['secondary_pointers']
        display = min(row[0] for row in pointers)
        chunks = [(0, struct.pack('>14I', *header)),
                  (56, b''.join(struct.pack('>hhhHhh4B', *v) for v in records['vertices'])),
                  (display, b''.join(struct.pack('>II', *row) for row in records['display_commands']))]
        for pair, (name, fmt) in enumerate(zip(names, ('>I', '>I', '>bBBB3f', '>IIHH', '>bb', '>I', '>B'))):
            data = b''.join(struct.pack(fmt, *row) for row in records[name])
            size = header[2 * pair + 1] & (0x7fffffff if pair == 6 else 0xffffffff)
            if len(data) != size:
                raise ValueError(f'character {name} count disagrees with header')
            if data:
                chunks.append((header[2 * pair], data))
        for offset, size in records['zero_regions']:
            if type(offset) is not int or type(size) is not int or not 1 <= size <= 15:
                raise ValueError('invalid character zero region')
            chunks.append((offset, bytes(size)))
    except (struct.error, TypeError, IndexError, OverflowError) as error:
        raise ValueError('invalid native character record') from error
    cursor, parts = 0, []
    for offset, data in sorted(chunks):
        if offset != cursor:
            raise ValueError('character records overlap or leave an uncovered gap')
        parts.append(data)
        cursor += len(data)
    payload = b''.join(parts)
    if character_records(payload) != records:
        raise ValueError('character records disagree with their native boundaries')
    return payload


CONSUMER_SPANS = (
    (0x1503CF20, 1096, '2335fa3855313510f1f46512cfa704ab301814d1'),
    (0x1503DC3C, 224, '4d0a13f114d5f3ecad9c56068bdde74a052935af'),
    (0x150A81D0, 4876, '56cae2497377b0bc66714a4175a2a27a0d78de0a'),
    (0x1503D368, 208, 'abef1711e0dda14ca8b45eb3689aa144f101bb5f'),
    (0x1503D438, 36, 'add9aec5cb5ff6df58ba80704156c1463b4a2071'),
    (0x1503DA3C, 96, '809ec0d6fed4c0983c19fc045f2433761c16cd46'),
    (0x15034860, 1620, 'a02ca6ff2ab888c064e26fb70c42b3cc32f5e08c'),
)


def verify_consumers(code: bytes, base: int) -> None:
    """Pin complete loader, descriptor, joint, normal and procedural consumers."""
    for address, size, digest in CONSUMER_SPANS:
        offset = address - base
        if offset < 0 or hashlib.sha1(code[offset:offset + size]).hexdigest() != digest:
            raise ValueError(f'ROM character consumer changed at 0x{address:08X}')
