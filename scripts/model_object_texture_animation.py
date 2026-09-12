"""ROM scene/object texture-animation bindings for the stored-frame preview."""
from __future__ import annotations

import hashlib
import struct

# Whole reviewed consumers supplement model_object_materials' loader/renderer
# and segment-register pins. They are guards, not inferred MIPS semantics.
CONSUMERS = (
    (0x1511A410, 132, '058498eb31b8ec9894eb891adbed369a2fbd0a7a'),
    (0x1511A494, 616, 'c896da27caa019639fe040e1d5bf9034f2663673'),
    (0x1511A6FC, 60, 'c0e6f956212d1cfa0906c53c8cc468c1fbda25c5'),
    (0x1511A738, 136, '9761ec47e5c256a049beda6560c76b7cf8038bed'),
    (0x1511D7BC, 552, 'd9402123ffac1b160d855d2af419ec0f321ff681'),
    (0x15113E54, 508, '0f7af2433892c364923128e69e707c3178eb2260'),
)
TABLE = 0x80089324
TABLE_SIZE = 0x120
TABLE_SHA1 = '46e61ea1c668a41dd1e7a0726ebaa35cf272376d'
ARRAYS = {
    0x8009177C: (15, '59c9a7fdc64a4b02c8888111283828c1c14c5ff8'),
    0x800917D8: (3, 'd806d28013d3b380bdf44fe9a10db7ecfd1ab94a'),
    0x80090338: (3, '60b71efc573d85e5fc2e149e50d65800d92a0233'),
}
UPDATE_FUNCTIONS = {21: 0x1511D7BC, 25: 0x1511A6FC, 41: 0x1511A738}


def checked(raw, base, address, size):
    offset = address - base
    if offset < 0 or offset + size > len(raw):
        raise ValueError('object texture animation exceeds ROM region')
    return raw[offset:offset + size]


def animation_table(code, code_base, data, data_base):
    for address, size, expected in CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError('object texture animation consumer changed')
    raw = checked(data, data_base, TABLE, TABLE_SIZE)
    if hashlib.sha1(raw).hexdigest() != TABLE_SHA1:
        raise ValueError('object texture animation table changed')
    for index, function in UPDATE_FUNCTIONS.items():
        if checked(data, data_base, 0x80088C90 + index * 12, 4) != struct.pack('>I', function):
            raise ValueError('object texture animation update dispatch changed')
    rows = []
    for offset in range(0, len(raw), 12):
        pointer, count, model, scene, period, pingpong = struct.unpack_from('>IBBbBB', raw, offset)
        if pointer not in ARRAYS or count != ARRAYS[pointer][0] or not period or pingpong not in (0, 1):
            raise ValueError('object texture animation array descriptor changed')
        frames = checked(data, data_base, pointer, count * 4)
        if hashlib.sha1(frames).hexdigest() != ARRAYS[pointer][1]:
            raise ValueError('object texture animation frame array changed')
        rows.append({'address': f'0x{TABLE + offset:08X}', 'scene': scene, 'model': model,
                     'frame_array': f'0x{pointer:08X}', 'frame_array_sha1': ARRAYS[pointer][1],
                     'frames': list(struct.unpack(f'>{count}I', frames)),
                     'frame_period': period, 'ping_pong': bool(pingpong)})
    return rows


def placement_animations(placements, rows):
    """Mirror first matching table row, scoped to a reviewed placement updater."""
    result = {}
    for scene in placements['scenes']:
        if scene['bank_index'] != 11:
            continue
        for record in scene['records']:
            if (record['dispatch_kind'] not in (1, 2)
                    or record['model_resolution_status'] != 'resolved-bank-04-segment'
                    or bytes.fromhex(record['bytes_3c_3f'])[0] & 2):
                continue
            update = int(record['word_14'], 16)
            if update not in UPDATE_FUNCTIONS:
                continue
            # Loader stores dispatch_index | 0x8000 at object +0x54. A
            # scene-specific table row applies that same bit before comparing.
            row = next((row for row in rows if row['scene'] == scene['scene_index']
                        and row['model'] in (255, record['dispatch_index'])), None)
            if row is None:
                continue
            key = tuple(record['model_source'])
            proof = {**row, 'preview_frame': 0,
                     'preview_policy': 'first stored ROM frame; not a sampled gameplay time',
                     'pixel_segment': 4, 'palette_segment': 5, 'palette_tail_bytes': 32,
                     'update_function': f'func_{UPDATE_FUNCTIONS[update]:08X}',
                     'placement_record': record['index'], 'placement_sha1': record['sha1']}
            if key in result and result[key]['address'] != proof['address']:
                raise ValueError('object texture animation has conflicting placements')
            result.setdefault(key, proof)
    return result
