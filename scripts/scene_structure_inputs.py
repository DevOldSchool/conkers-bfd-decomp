"""Preserved source children for scene directories and cylinder groups."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

try:
    from scripts import asset_inputs, texture_build, scene_structure_codec as codec
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_inputs, texture_build, scene_structure_codec as codec
    from model_character_alpha import checked_spans

FAMILIES = ('directories', 'cylinders')
CODE_SPANS = (
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
    (0x1502B5C8, 244, '9c411ce6bf78e69583215fa8484bfd0f137edc72'),
    (0x1502B7F0, 240, '8f37332e9c2598c7a996b8d1e0c5d9ea82f44cfd'),
    (0x150163D0, 304, '5d42be01ef96501de4cbd04700429767b3cc0aa9'),
    (0x15055E50, 768, 'f534477307c96c3a7024254c3b6b6a410972d6ae'),
)


def verify_consumers(code, base):
    return checked_spans(code, base, CODE_SPANS)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def child(family):
    if family not in FAMILIES:
        raise ValueError('unsupported scene structure family')
    return Path('scene-' + family)


def encode(source, parent, family):
    if family == 'directories':
        return codec.encode_tree(source, parent['rom_start'], parent['rom_end'])
    if (family != 'cylinders' or type(source) is not dict
            or set(source) != {'format', 'entries'} or source['format'] != codec.CYLINDER_FORMAT
            or type(source['entries']) is not list):
        raise ValueError('invalid scene cylinder source')
    spans, previous = [], -1
    for entry in source['entries']:
        if (type(entry) is not dict or set(entry) != {'scene', 'offset', 'groups'}
                or type(entry['scene']) is not int or entry['scene'] <= previous
                or type(entry['offset']) is not int or entry['offset'] < 0):
            raise ValueError('invalid scene cylinder selection')
        previous = entry['scene']
        spans.extend((entry['offset'] + a, data) for a, data in codec.encode_cylinders(
            {'format': codec.CYLINDER_FORMAT, 'groups': entry['groups']}))
    if any(a + len(data) > parent['rom_end'] - parent['rom_start'] for a, data in spans):
        raise ValueError('scene cylinders exceed bank extent')
    return spans


def reviewed(backing, parent, family):
    child(family)
    if (parent.get('bank') != 12 or len(backing) != parent['rom_end'] - parent['rom_start']
            or sha(backing) != parent['original_sha256']):
        raise ValueError('scene structure backing differs from reviewed bank')
    tree = codec.decode_tree(backing, parent['rom_start'])
    source = tree
    if family == 'cylinders':
        source = {'format': codec.CYLINDER_FORMAT, 'entries': []}
        for scene in tree['scenes']:
            if len(scene['directory']['entries']) <= 9:
                continue
            entry = scene['directory']['entries'][9]
            if not entry['stored_size']:
                continue
            offset = tree['outer']['entries'][scene['index']]['relative_offset'] + entry['relative_offset']
            decoded = codec.decode_cylinders(backing[offset:offset + entry['stored_size']])
            source['entries'].append({'scene': scene['index'], 'offset': offset, 'groups': decoded['groups']})
    spans = encode(source, parent, family)
    if any(backing[a:a + len(data)] != data for a, data in spans):
        raise ValueError('scene structure does not reproduce original storage')
    manifest = {'schema_version': 1, 'format': source['format'], 'family': family,
                'rom_start': parent['rom_start'], 'rom_end': parent['rom_end'],
                'ranges': [[a, a + len(data)] for a, data in spans],
                'sha256': sha(b''.join(data for _, data in spans)),
                'consumers': [{'start': a, 'size': n, 'sha1': h} for a, n, h in CODE_SPANS]}
    return manifest, source


def ensure_inputs(directory, parent, backing, family):
    manifest, source = reviewed(backing, parent, family)
    target = directory / child(family)
    if not target.exists():
        texture_build.publish_inputs(target, {
            'manifest.json': (json.dumps(manifest, indent=2) + '\n').encode(),
            family + '.json': (json.dumps(source, indent=2) + '\n').encode()})


def input_hashes(directory, parent, backing, family):
    manifest, _ = reviewed(backing, parent, family)
    hashes = asset_inputs.manifest_hashes(directory / child(family), manifest,
        ('manifest.json', family + '.json'), 'scene ' + family)
    return {(child(family) / name).as_posix(): digest for name, digest in hashes.items()}


def encoded(directory, parent, backing, family):
    manifest, reviewed_source = reviewed(backing, parent, family)
    source = json.loads((directory / child(family) / (family + '.json')).read_text())
    if family == 'cylinders':
        if (type(source) is not dict or type(source.get('entries')) is not list
                or [(e.get('scene'), e.get('offset')) for e in source['entries'] if type(e) is dict]
                != [(e['scene'], e['offset']) for e in reviewed_source['entries']]):
            raise ValueError('scene cylinder owners changed')
    spans = encode(source, parent, family)
    if ([[a, a + len(data)] for a, data in spans] != manifest['ranges']
            or sha(b''.join(data for _, data in spans)) != manifest['sha256']):
        raise ValueError('scene structures no longer reproduce reviewed storage')
    return spans
