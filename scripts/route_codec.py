"""Native actor path points and navigation graphs from semantic records."""
from __future__ import annotations
import struct

PATH_FORMAT = 'conker-actor-paths-v1'
GRAPH_FORMAT = 'conker-navigation-graph-v1'


def integer(value, low, high, role):
    if type(value) is not int or not low <= value <= high:
        raise ValueError(f'{role} is outside its native range')
    return value


def position(value):
    if not isinstance(value, list) or len(value) != 3:
        raise ValueError('route position requires three signed coordinates')
    return [integer(v, -32768, 32767, 'route coordinate') for v in value]


def encode_paths(record):
    if (not isinstance(record, dict) or set(record) != {'format', 'actor_paths', 'paths'}
            or record['format'] != PATH_FORMAT):
        raise ValueError('unsupported actor path schema')
    actors, paths = record['actor_paths'], record['paths']
    if not isinstance(actors, list) or len(actors) > 239 or not isinstance(paths, list):
        raise ValueError('actor path directory exceeds native actor bounds')
    references = [integer(ref, 0, len(paths) - 1, 'actor path reference') for ref in actors if ref is not None]
    if set(references) != set(range(len(paths))):
        raise ValueError('actor paths contain unreferenced storage')
    output, offsets = bytearray(len(actors) * 8), []
    for points in paths:
        if not isinstance(points, list) or not 1 <= len(points) <= 255:
            raise ValueError('actor path point count is outside the native byte range')
        offsets.append(len(output))
        for point in points:
            if not isinstance(point, dict) or set(point) != {'position', 'control'}:
                raise ValueError('unsupported actor path point schema')
            output.extend(struct.pack('>hhhH', *position(point['position']),
                                      integer(point['control'], 0, 65535, 'path control')))
    for index, ref in enumerate(actors):
        if ref is not None:
            struct.pack_into('>II', output, index * 8, offsets[ref], len(paths[ref]))
    output.extend(bytes((-len(output)) % 16))
    return bytes(output)


def decode_paths(data, actor_count):
    integer(actor_count, 0, 239, 'actor count')
    if len(data) < actor_count * 8:
        raise ValueError('actor path directory is truncated')
    table = list(struct.iter_unpack('>II', data[:actor_count * 8]))
    counts = {}
    for offset, count in table:
        if offset == 0:
            if count:
                raise ValueError('absent actor path has a nonzero count')
            continue
        if (offset % 8 or offset < actor_count * 8 or not 1 <= count <= 255
                or offset + count * 8 > len(data)):
            raise ValueError('actor path has invalid offset or count')
        if offset in counts and counts[offset] != count:
            raise ValueError('shared actor path has conflicting counts')
        counts[offset] = count
    cursor, paths, references = actor_count * 8, [], {}
    for offset, count in sorted(counts.items()):
        if offset != cursor:
            raise ValueError('actor paths contain unexplained gaps or overlaps')
        references[offset] = len(paths)
        paths.append([{'position': [x, y, z], 'control': control}
                      for x, y, z, control in struct.iter_unpack('>hhhH', data[offset:offset + count * 8])])
        cursor += count * 8
    record = {'format': PATH_FORMAT, 'actor_paths': [references[offset] if offset else None for offset, _ in table],
              'paths': paths}
    if encode_paths(record) != data:
        raise ValueError('actor path alignment or trailing storage is unexplained')
    return record


def encode_graph(record):
    if (not isinstance(record, dict) or set(record) != {'format', 'nodes'}
            or record['format'] != GRAPH_FORMAT):
        raise ValueError('unsupported navigation graph schema')
    nodes = record['nodes']
    if not isinstance(nodes, list) or len(nodes) >= 256:
        raise ValueError('navigation node count exceeds native byte references')
    output = bytearray(struct.pack('>HH', len(nodes), 0))
    for node in nodes:
        if (not isinstance(node, dict)
                or set(node) != {'position', 'height_band', 'identifier', 'radius', 'neighbors', 'group', 'trigger'}):
            raise ValueError('unsupported navigation node schema')
        neighbors = node['neighbors']
        if not isinstance(neighbors, list) or len(neighbors) != 5:
            raise ValueError('navigation node requires five neighbor slots')
        links = [255 if n is None else integer(n, 0, len(nodes) - 1, 'navigation neighbor') for n in neighbors]
        output.extend(struct.pack('>hhh10B', *position(node['position']),
                                  integer(node['height_band'], 0, 5, 'navigation height band'),
                                  integer(node['identifier'], 0, 255, 'navigation identifier'),
                                  integer(node['radius'], 0, 255, 'navigation radius'), *links,
                                  integer(node['group'], 0, 255, 'navigation group'),
                                  integer(node['trigger'], 0, 255, 'navigation trigger')))
    output.extend(bytes((-len(output)) % 8))
    return bytes(output)


def decode_graph(data):
    if len(data) < 4:
        raise ValueError('navigation graph header is truncated')
    count, secondary = struct.unpack_from('>HH', data)
    if count >= 256 or secondary or len(data) < 4 + count * 16:
        raise ValueError('navigation graph has an unreviewed header or extent')
    nodes = []
    for at in range(count):
        values = struct.unpack_from('>hhh10B', data, 4 + at * 16)
        nodes.append({'position': list(values[:3]), 'height_band': values[3], 'identifier': values[4],
                      'radius': values[5], 'neighbors': [None if v == 255 else v for v in values[6:11]],
                      'group': values[11], 'trigger': values[12]})
    record = {'format': GRAPH_FORMAT, 'nodes': nodes}
    if encode_graph(record) != data:
        raise ValueError('navigation graph alignment or trailing storage is unexplained')
    return record
