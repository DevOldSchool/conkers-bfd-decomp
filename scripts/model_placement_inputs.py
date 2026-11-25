"""Preserved-source children for bank-0B placements and bank-0C parameters."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct
import zlib

try:
    from scripts import asset_inputs, asset_directory_codec as index_codec
    from scripts import model_placement_codec as codec, texture_build, rzip_archive
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_inputs, asset_directory_codec as index_codec
    import model_placement_codec as codec, texture_build, rzip_archive
    from model_character_alpha import checked_spans

DIRECTORY = Path('model-placements')
CODE_SPANS = (
    (0x150039E0, 2964, 'b7b5ae00e5b5a3c5a0d28ad82582a25479a3bc66'),
    (0x1502B7F0, 240, '8f37332e9c2598c7a996b8d1e0c5d9ea82f44cfd'),
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
)


def verify_consumers(code, base):
    return checked_spans(code, base, CODE_SPANS)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def compress(data):
    compressor = zlib.compressobj(level=6, wbits=-15)
    return struct.pack('>I', len(data)) + compressor.compress(data) + compressor.flush()


def reviewed(backing, parent):
    if (len(backing) != parent['rom_end'] - parent['rom_start']
            or sha(backing) != parent['original_sha256']):
        raise ValueError('model placement bank differs from reviewed storage')
    props = parent.get('key') == 'bank0B'
    if not props and parent.get('bank') != 12:
        raise ValueError('unsupported model placement owner')
    format_name = codec.PROPS_FORMAT if props else codec.PARAMETERS_FORMAT
    rows, sources = [], []
    if props:
        if parent['directory_size'] != 552:
            raise ValueError('invalid model placement directory extent')
        index = index_codec.decode(backing[:552])
        previous = 552
        for number, entry in enumerate(index['entries']):
            offset, size = entry['relative_offset'], entry['stored_size']
            if not size:
                continue
            if (entry['flags'] != (9 if number == 68 else 1) or offset < previous
                    or offset + size > len(backing)):
                raise ValueError('invalid model placement stream bounds or flags')
            previous = offset + size
            original = backing[offset:offset + size]
            chunk = rzip_archive.decode_rzip_chunk(original)
            if chunk.consumed != size:
                raise ValueError('model placement stream has trailing storage')
            records = codec.decode_props(chunk.data)
            payload = compress(codec.encode_props(records))
            if payload != original:
                raise ValueError('model placement compression differs from original')
            rows.append({'key': str(number), 'offset': offset, 'record_count': len(records),
                         'ranges': [[0, size]], 'sha256': sha(payload)})
            sources.append({'key': str(number), 'records': records})
        if len(rows) != 54:
            raise ValueError('model placement stream selection differs from reviewed bank')
    else:
        for entry in parent['entries']:
            if entry['child'] != 2:
                continue
            offset = entry['rom_start'] - parent['rom_start']
            size = entry['rom_end'] - entry['rom_start']
            if offset < 0 or size != entry['record_count'] * 68 or offset + size > len(backing):
                raise ValueError('model parameter child exceeds reviewed extent')
            original = backing[offset:offset + size]
            records = codec.decode_parameters(original)
            spans = codec.encode_parameters(records)
            if any(original[a:a + len(data)] != data for a, data in spans):
                raise ValueError('model parameters differ from original storage')
            rows.append({'key': entry['key'], 'offset': offset, 'record_count': len(records),
                         'ranges': [[a, a + len(data)] for a, data in spans],
                         'sha256': sha(b''.join(data for _, data in spans))})
            sources.append({'key': entry['key'], 'records': records})
    manifest = {'schema_version': 1, 'format': format_name,
                'rom_start': parent['rom_start'], 'rom_end': parent['rom_end'], 'entries': rows,
                'consumers': [{'start': a, 'size': n, 'sha1': h} for a, n, h in CODE_SPANS]}
    return manifest, {'format': format_name, 'entries': sources}


def ensure_inputs(directory, expected, backing):
    manifest, source = reviewed(backing, expected)
    if not (directory / DIRECTORY).exists():
        texture_build.publish_inputs(directory / DIRECTORY, {
            'manifest.json': (json.dumps(manifest, indent=2) + '\n').encode(),
            'placements.json': (json.dumps(source, indent=2, allow_nan=False) + '\n').encode()})


def input_hashes(directory, expected, backing):
    manifest, _ = reviewed(backing, expected)
    hashes = asset_inputs.manifest_hashes(directory / DIRECTORY, manifest,
                                         ('manifest.json', 'placements.json'), 'model placements')
    return {(DIRECTORY / name).as_posix(): digest for name, digest in hashes.items()}


def encoded(directory, expected, backing):
    manifest, _ = reviewed(backing, expected)
    source = json.loads((directory / DIRECTORY / 'placements.json').read_text())
    if (type(source) is not dict or set(source) != {'format', 'entries'}
            or source['format'] != manifest['format'] or type(source['entries']) is not list
            or len(source['entries']) != len(manifest['entries'])):
        raise ValueError('invalid model placement source')
    spans = []
    for entry, proof in zip(source['entries'], manifest['entries'], strict=True):
        if (type(entry) is not dict or set(entry) != {'key', 'records'} or entry['key'] != proof['key']
                or type(entry['records']) is not list or len(entry['records']) != proof['record_count']):
            raise ValueError('model placement selection or count changed')
        if manifest['format'] == codec.PROPS_FORMAT:
            fresh = [(0, compress(codec.encode_props(entry['records'])))]
        else:
            fresh = codec.encode_parameters(entry['records'])
        if ([[a, a + len(data)] for a, data in fresh] != proof['ranges']
                or sha(b''.join(data for _, data in fresh)) != proof['sha256']):
            raise ValueError('model placements no longer reproduce reviewed storage')
        spans.extend((proof['offset'] + a, data) for a, data in fresh)
    return spans
