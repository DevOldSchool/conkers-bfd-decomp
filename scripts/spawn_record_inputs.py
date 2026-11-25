"""Editable typed bank-0E spawn streams within the preserved directory object."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct
import zlib

try:
    from scripts import asset_inputs, asset_directory_codec as index_codec
    from scripts import spawn_record_codec as codec, texture_build, rzip_archive
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_inputs
    import asset_directory_codec as index_codec
    import spawn_record_codec as codec
    import texture_build, rzip_archive
    from model_character_alpha import checked_spans

DIRECTORY = Path('spawn-records')
SELECTED = tuple(i for i in range(69) if i != 14)
CODE_SPANS = (
    (0x150169A0, 1908, '774d2e2e6e020e45f99980cef4342f92be94e5bb'),
    (0x1502B8E0, 212, '2aea02ea13f93c5c25772d23323e71f576b8e0de'),
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
    (0x150825C0, 924, 'e626c88906c1344002292db83074802975dc059a'),
    (0x15082A44, 2152, 'df94e52b3063e063c091fac537096563d3e47620'),
    (0x150623F4, 760, '4bd9cbeabff8940b64276fef674e0241b5e54c4a'),
    (0x150839B8, 272, '83514e60fb88c39b8e225ba6b68a54a5094c2dff'),
    (0x150832AC, 216, '0ec77fd56141002265c6011b88dd598a91710fc1'),
)


def verify_consumers(code, base):
    return checked_spans(code, base, CODE_SPANS)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def compress(data):
    compressor = zlib.compressobj(level=6, wbits=-15)
    return struct.pack('>I', len(data)) + compressor.compress(data) + compressor.flush()


def reviewed(backing, parent):
    if (parent['key'] != 'bank0E' or parent['directory_size'] != 552
            or len(backing) != parent['rom_end'] - parent['rom_start']
            or sha(backing) != parent['original_sha256']):
        raise ValueError('spawn bank differs from reviewed storage')
    outer = index_codec.decode(backing[:552])
    rows, entries = [], []
    previous = 552
    for index, entry in enumerate(outer['entries']):
        offset, size = entry['relative_offset'], entry['stored_size']
        if (entry['flags'] != (9 if index == 68 else 1) or offset < previous
                or offset % 4 or not size or offset + size > len(backing)):
            raise ValueError('invalid native spawn stream extent or flags')
        previous = offset + size
        if index not in SELECTED:
            continue
        original = backing[offset:offset + size]
        chunk = rzip_archive.decode_rzip_chunk(original)
        if chunk.consumed != len(original):
            raise ValueError('spawn stream has unexplained trailing bytes')
        records = codec.decode(chunk.data)
        fresh = compress(codec.encode(records))
        if fresh != original:
            raise ValueError('spawn fields do not reproduce original compression')
        rows.append({'index': index, 'offset': offset, 'stored_size': size,
                     'record_count': len(records), 'sha256': sha(original)})
        entries.append({'index': index, 'records': records})
    if tuple(r['index'] for r in rows) != SELECTED:
        raise ValueError('spawn bank selection differs from reviewed inventory')
    manifest = {'schema_version': 1, 'format': codec.FORMAT,
                'rom_start': parent['rom_start'], 'rom_end': parent['rom_end'],
                'entries': rows,
                'consumers': [{'start': a, 'size': n, 'sha1': h} for a, n, h in CODE_SPANS]}
    return manifest, {'format': codec.FORMAT, 'entries': entries}


def ensure_inputs(directory, expected, backing):
    manifest, source = reviewed(backing, expected)
    if not (directory / DIRECTORY).exists():
        texture_build.publish_inputs(directory / DIRECTORY, {
            'manifest.json': (json.dumps(manifest, indent=2) + '\n').encode(),
            'spawns.json': (json.dumps(source, indent=2, allow_nan=False) + '\n').encode()})


def input_hashes(directory, expected, backing):
    manifest, _ = reviewed(backing, expected)
    hashes = asset_inputs.manifest_hashes(directory / DIRECTORY, manifest,
                                         ('manifest.json', 'spawns.json'), 'spawn records')
    return {(DIRECTORY / name).as_posix(): digest for name, digest in hashes.items()}


def encoded(directory, expected, backing):
    manifest, _ = reviewed(backing, expected)
    source = json.loads((directory / DIRECTORY / 'spawns.json').read_text())
    if (type(source) is not dict or set(source) != {'format', 'entries'}
            or source['format'] != codec.FORMAT or type(source['entries']) is not list
            or len(source['entries']) != len(manifest['entries'])):
        raise ValueError('invalid spawn bank source')
    spans = []
    for entry, proof in zip(source['entries'], manifest['entries'], strict=True):
        if (type(entry) is not dict or set(entry) != {'index', 'records'}
                or type(entry['index']) is not int or entry['index'] != proof['index']):
            raise ValueError('spawn selection changed')
        decoded = codec.encode(entry['records'])
        fresh = compress(decoded)
        if (len(decoded) != proof['record_count'] * 48
                or len(fresh) != proof['stored_size'] or sha(fresh) != proof['sha256']):
            raise ValueError('spawn fields no longer reproduce reviewed storage')
        spans.append((proof['offset'], fresh))
    return spans
