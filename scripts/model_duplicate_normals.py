"""Typed bank-04 bundles containing a duplicate of the primary normal table."""
from __future__ import annotations

import struct

try:
    from scripts import model_assets, model_build, model_bundle_build, model_extended_build as extended
except ModuleNotFoundError:
    import model_assets, model_build, model_bundle_build
    import model_extended_build as extended

FORMAT = 'model-bundle-duplicate-normals'
CHILD_FORMAT = 'duplicate-primary-normal-prefix'


def normal_bytes(primary):
    if primary.get('format') != 'extended-model' or primary.get('primary') is not True:
        raise ValueError('duplicate normals require a typed primary model')
    tables = primary['normal_xy_s8']
    if not tables or any(len(t) != 32 for t in tables):
        raise ValueError('duplicate primary normal tables are missing or incomplete')
    return b''.join(struct.pack('>bb', *pair) for table in tables for pair in table)


def regular_decode(payload, index):
    try:
        if index == 0:
            return model_bundle_build.surface_records(payload)
        if struct.unpack_from('>I', payload, 16)[0]:
            return model_bundle_build.surface_records(payload, primary=False)
        return model_build.model_records(payload, bank=3)
    except ValueError:
        return extended.extended_records(payload, primary=index == 0)


def regular_encode(source, index):
    if source.get('format') == 'extended-model':
        if source.get('primary') != (index == 0):
            raise ValueError('duplicate bundle model role changed')
        return extended.encode_extended_records(source)
    if index == 0 or source.get('format') == 'part-tertiary-direct':
        return model_bundle_build.encode_surface_records(source)
    return model_build.encode_records(source, bank=3)


def child_decode(payload, primary):
    geometry = model_assets.parse_model_geometry(payload)
    header = list(geometry.header_words)
    end = header[0] + header[1]
    prefix = normal_bytes(primary)
    if header[2:] != [0, 0, 0, 0, 0, 0, 0, 0x80000000]:
        raise ValueError('duplicate-normal child has unsupported header regions')
    if payload[end:end + len(prefix)] != prefix:
        raise ValueError('child prefix differs from the independently typed primary normals')
    commands = [list(c) for c in struct.iter_unpack('>II', payload[header[0]:end])]
    offsets = sorted({a for w, a in commands if w == model_assets.CHARACTER_CUSTOM_MOVEMEM_COMMAND})
    if (not offsets or offsets != list(range(end + len(prefix), len(payload), 64))
            or offsets[-1] + 64 != len(payload)):
        raise ValueError('child normal tables are incomplete or not completely referenced')
    return {'format': CHILD_FORMAT, 'header_words': header,
            'vertices': [[v.x, v.y, v.z, v.flag, v.s, v.t, *v.color] for v in geometry.vertices],
            'display_commands': commands,
            'duplicated_normal_source': {'segment': 0, 'first_table': 0, 'table_count': len(primary['normal_xy_s8'])},
            'normal_xy_s8': [[list(p) for p in struct.iter_unpack('>bb', payload[a:a + 64])] for a in offsets]}


def child_encode(source, primary):
    fields = {'format', 'header_words', 'vertices', 'display_commands', 'duplicated_normal_source', 'normal_xy_s8'}
    if (type(source) is not dict or set(source) != fields or source['format'] != CHILD_FORMAT
            or source['duplicated_normal_source'] != {'segment': 0, 'first_table': 0,
                                                     'table_count': len(primary['normal_xy_s8'])}
            or any(len(table) != 32 for table in source['normal_xy_s8'])):
        raise ValueError('invalid duplicate-normal child source')
    payload = (struct.pack('>10I', *source['header_words'])
               + b''.join(struct.pack('>hhhHhh4B', *row) for row in source['vertices'])
               + b''.join(struct.pack('>II', *row) for row in source['display_commands'])
               + normal_bytes(primary)
               + b''.join(struct.pack('>bb', *p) for table in source['normal_xy_s8'] for p in table))
    if child_decode(payload, primary) != source:
        raise ValueError('duplicate child fields disagree with native layout')
    return payload


def decode(payload):
    segments = model_assets.parse_model_bundle(payload)
    if not segments[0].data or not segments[1].data:
        raise ValueError('duplicate-normal bundle requires primary and child models')
    primary = regular_decode(segments[0].data, 0)
    rows = [primary, child_decode(segments[1].data, primary)]
    rows.extend(regular_decode(s.data, s.index) if s.data else None for s in segments[2:])
    return {'format': FORMAT, 'descriptors': [[s.offset, s.size | (0x80000000 if s.final_flag else 0)]
                                             for s in segments], 'segments': rows}


def encode(source):
    if (type(source) is not dict or set(source) != {'format', 'descriptors', 'segments'}
            or source['format'] != FORMAT or type(source['segments']) is not list
            or len(source['segments']) < 4 or len(source['segments']) != len(source['descriptors'])
            or any(row is not None and type(row) is not dict for row in source['segments'])
            or source['segments'][0] is None or source['segments'][1] is None):
        raise ValueError('invalid duplicate-normal bundle schema')
    try:
        primary = source['segments'][0]
        parts = [regular_encode(primary, 0), child_encode(source['segments'][1], primary)]
        parts.extend(regular_encode(row, i) if row is not None else b''
                     for i, row in enumerate(source['segments'][2:], 2))
        payload = b''.join(struct.pack('>II', *row) for row in source['descriptors']) + b''.join(parts)
        checked = decode(payload)
    except (struct.error, TypeError, IndexError, KeyError, OverflowError) as error:
        raise ValueError('invalid duplicate-normal bundle fields') from error
    if checked != source:
        raise ValueError('duplicate-normal bundle fields disagree with native descriptors')
    return payload
