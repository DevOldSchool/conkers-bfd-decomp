"""Typed nested indexes for the bounded partial-animation reconstruction."""
from __future__ import annotations

import hashlib
import json

try:
    from scripts import asset_directory_codec as codec, asset_inputs, model_animation_build
except ModuleNotFoundError:
    import asset_directory_codec as codec, asset_inputs, model_animation_build


def sha(data):
    return hashlib.sha256(data).hexdigest()


def index_ranges(expected):
    ranges = []
    for entry in expected['entries']:
        count = entry['pair_count']
        if type(count) is not int or not 0 < count <= 0x10000:
            raise ValueError('animation index pair count is invalid')
        start, end = entry['rom_start'], entry['rom_start'] + count * 16
        if not expected['rom_start'] <= start < end <= entry['rom_end'] <= expected['rom_end']:
            raise ValueError('animation index lies outside its reviewed entry or object')
        ranges.append([start, end])
    if len(ranges) != len({e['entry'] for e in expected['entries']}):
        raise ValueError('duplicate animation index entry')
    return sorted(ranges)


def owned_ranges(expected):
    ranges = sorted(expected['rom_ranges'] + index_ranges(expected))
    if any(a[1] > b[0] for a, b in zip(ranges, ranges[1:])):
        raise ValueError('animation index and clip ranges overlap')
    return ranges


def reviewed(backing, expected):
    """Derive a separate child contract without rewriting accepted parent inputs."""
    if len(backing) != expected['rom_end'] - expected['rom_start'] or sha(backing) != expected['original_sha256']:
        raise ValueError('animation index backing changed')
    owned_ranges(expected)
    entries, records = [], {}
    for entry in expected['entries']:
        start = entry['rom_start']; count = entry['pair_count'] * 2; size = count * 8
        offset = start - expected['rom_start']
        raw = backing[offset:entry['rom_end'] - expected['rom_start']]
        segments = model_animation_build.animation_segments(raw)
        if len(segments) != count:
            raise ValueError('animation index descriptor count changed')
        record = codec.decode(raw[:size])
        for i, (row, segment) in enumerate(zip(record['entries'], segments)):
            if row != {'relative_offset':segment.offset, 'stored_size':segment.size,
                       'flags':8 if i == count - 1 else 0}:
                raise ValueError('animation index flags or native segment extents changed')
        if codec.encode(record) != raw[:size]:
            raise ValueError('animation index fields do not reproduce original directory')
        records[str(entry['entry'])] = record
        entries.append({'entry':entry['entry'], 'rom_start':start, 'rom_end':start + size,
                        'descriptor_count':count, 'original_sha256':sha(raw[:size])})
    manifest = {'schema_version':1, 'profile':'us', 'part':expected['part'],
                'parent_sha256':expected['original_sha256'], 'entries':entries}
    return manifest, records


def input_files(backing, expected):
    manifest, records = reviewed(backing, expected)
    return {name:(json.dumps(value, indent=2)+'\n').encode()
            for name, value in [('manifest.json',manifest), ('indexes.json',records)]}


def input_hashes(directory, expected):
    manifest, _ = reviewed((directory/'backing.bin').read_bytes(), expected)
    return asset_inputs.manifest_hashes(directory/'indexes', manifest,
        ('manifest.json','indexes.json'), 'animation indexes')


def packed_spans(directory, expected):
    before = input_hashes(directory, expected)
    manifest, _ = reviewed((directory/'backing.bin').read_bytes(), expected)
    records = json.loads((directory/'indexes/indexes.json').read_text())
    if type(records) is not dict or set(records) != {str(e['entry']) for e in manifest['entries']}:
        raise ValueError('animation index source entry set changed')
    spans = []
    for entry in manifest['entries']:
        fresh = codec.encode(records[str(entry['entry'])])
        if len(fresh) != entry['rom_end'] - entry['rom_start'] or sha(fresh) != entry['original_sha256']:
            raise ValueError('animation index fields no longer reproduce reviewed storage')
        spans.append((entry['rom_start'] - expected['rom_start'], fresh))
    if input_hashes(directory, expected) != before:
        raise ValueError('animation index inputs changed during packing')
    return spans
