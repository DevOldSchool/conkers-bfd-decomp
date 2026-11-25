"""Native scene directories and bounded vertical-cylinder groups."""
from __future__ import annotations

import struct

try:
    from scripts import asset_directory_codec as index
except ModuleNotFoundError:
    import asset_directory_codec as index

TREE_FORMAT = 'scene-directory-tree-native-v1'
CYLINDER_FORMAT = 'scene-cylinder-groups-native-v1'


def directory_spans(source, start, end, *, inner=False):
    table = index.encode(source)
    cursor = start + len(table)
    if cursor > end:
        raise ValueError('scene directory exceeds container')
    spans = [(start, table)]
    for number, entry in enumerate(source['entries']):
        if entry['flags'] not in (0, 8) or (entry['flags'] == 8 and number != len(source['entries']) - 1):
            raise ValueError('unsupported scene directory flags')
        if not entry['stored_size']:
            continue
        at = start + entry['relative_offset']
        padding = bytes((-cursor) % (16 if inner else 8))
        if at != cursor + len(padding) or at + entry['stored_size'] > end:
            raise ValueError('scene entry does not follow minimal alignment')
        if padding:
            spans.append((cursor, padding))
        cursor = at + entry['stored_size']
    padding = b'' if inner else bytes((-cursor) % 8)
    if cursor + len(padding) != end:
        raise ValueError('unexplained scene container tail')
    if padding:
        spans.append((cursor, padding))
    return spans


def encode_tree(source, start, end):
    if (type(source) is not dict or set(source) != {'format', 'outer', 'scenes'}
            or source['format'] != TREE_FORMAT or type(source['scenes']) is not list):
        raise ValueError('invalid scene directory tree')
    spans = directory_spans(source['outer'], start, end)
    parents = [(i, e) for i, e in enumerate(source['outer']['entries']) if e['stored_size']]
    if len(source['scenes']) != len(parents):
        raise ValueError('scene directory count differs from outer index')
    for row, (number, entry) in zip(source['scenes'], parents, strict=True):
        if (type(row) is not dict or set(row) != {'index', 'directory'}
                or type(row['index']) is not int or row['index'] != number):
            raise ValueError('scene directory selection differs from outer index')
        at = start + entry['relative_offset']
        spans.extend(directory_spans(row['directory'], at, at + entry['stored_size'], inner=True))
    spans.sort()
    if any(a + len(data) > b for (a, data), (b, _) in zip(spans, spans[1:])):
        raise ValueError('scene directory ownership overlaps')
    return [(a - start, data) for a, data in spans]


def decode_tree(data, start):
    def read(at, end):
        if not 0 <= at <= end - 8 or end > len(data):
            raise ValueError('scene directory exceeds available data')
        size = struct.unpack_from('>I', data, at)[0]
        if not 8 <= size <= end - at or size % 8:
            raise ValueError('invalid scene directory extent')
        return index.decode(data[at:at + size])
    outer = read(0, len(data))
    source = {'format': TREE_FORMAT, 'outer': outer, 'scenes': []}
    for number, entry in enumerate(outer['entries']):
        if entry['stored_size']:
            at = entry['relative_offset']
            source['scenes'].append({'index': number, 'directory': read(at, at + entry['stored_size'])})
    if any(data[a:a + len(b)] != b for a, b in encode_tree(source, start, start + len(data))):
        raise ValueError('scene directory or alignment differs from original')
    return source


def integer(value, low, high):
    if type(value) is not int or not low <= value <= high:
        raise ValueError('invalid cylinder scalar')
    return value


def encode_cylinders(source):
    if (type(source) is not dict or set(source) != {'format', 'groups'}
            or source['format'] != CYLINDER_FORMAT or type(source['groups']) is not list
            or len(source['groups']) > 65535):
        raise ValueError('invalid cylinder group schema')
    groups = source['groups']
    cursor = (len(groups) + 1) * 8
    table, body = bytearray(), bytearray()
    for group in groups:
        if (type(group) is not dict or set(group) != {'id', 'cylinders'}
                or type(group['cylinders']) is not list or len(group['cylinders']) > 65535):
            raise ValueError('invalid cylinder group')
        table.extend(struct.pack('>IHH', cursor, len(group['cylinders']), integer(group['id'], 0, 65535)))
        for record in group['cylinders']:
            if (type(record) is not dict
                    or set(record) != {'x', 'z', 'bottom', 'height', 'radius', 'inside'}
                    or type(record['inside']) is not bool):
                raise ValueError('invalid cylinder fields')
            coords = [integer(record[k], -32768, 32767) for k in ('x', 'z', 'bottom', 'height')]
            flags = integer(record['radius'], 0, 32767) | (int(record['inside']) << 15)
            body.extend(struct.pack('>4hH', *coords, flags))
        cursor = (len(groups) + 1) * 8 + len(body)
    # Native code reads only the terminal zero offset. The following four
    # sentinel bytes are deliberately absent from the owned spans.
    spans = [(0, bytes(table) + bytes(4))]
    if body:
        spans.append(((len(groups) + 1) * 8, bytes(body)))
    return spans


def decode_cylinders(data):
    at, groups = 0, []
    while True:
        if at + 8 > len(data):
            raise ValueError('missing cylinder group sentinel')
        offset, count, ident = struct.unpack_from('>IHH', data, at)
        if not offset:
            break
        if offset + count * 10 > len(data):
            raise ValueError('cylinder records exceed child extent')
        records = [{'x': x, 'z': z, 'bottom': bottom, 'height': height,
                    'radius': flags & 32767, 'inside': bool(flags & 32768)}
                   for x, z, bottom, height, flags in struct.iter_unpack('>4hH', data[offset:offset + count * 10])]
        groups.append({'id': ident, 'cylinders': records})
        at += 8
    source = {'format': CYLINDER_FORMAT, 'groups': groups}
    spans = encode_cylinders(source)
    size = (len(groups) + 1) * 8 + sum(len(g['cylinders']) * 10 for g in groups)
    if size != len(data) or any(data[a:a + len(b)] != b for a, b in spans):
        raise ValueError('cylinder groups are not contiguous native records')
    return source
