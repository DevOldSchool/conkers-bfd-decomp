"""Typed bank indexes and minimum alignment, independent of payload codecs."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct

try:
    from scripts import asset_directory_codec as codec, asset_inputs, texture_build
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_directory_codec as codec, asset_inputs, texture_build
    from model_character_alpha import checked_spans

DIRECTORY = Path('bank-index')
NEW_BANKS = (0, 5, 15, 16, 25)
ALIGNMENT_KEYS = ('bank07', 'bank0B', 'bank0D', 'bank0E', 'bank11', 'bank18', 'bank1A', 'bank1B', 'bank1C')
CODE_SPANS = ((0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
              (0x1502B5C8, 244, '9c411ce6bf78e69583215fa8484bfd0f137edc72'))


def verify_consumers(code, base):
    return checked_spans(code, base, CODE_SPANS)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def alignment_spans(source, start, end):
    """Derive minimal absolute eight-byte alignment from native index fields."""
    cursor = start + len(codec.encode(source))
    if cursor > end:
        raise ValueError('directory exceeds bank extent')
    spans = {}
    for entry in source['entries']:
        if not entry['stored_size']:
            continue
        offset = start + entry['relative_offset']
        padding = bytes((-cursor) % 8)
        if offset != cursor + len(padding) or offset + entry['stored_size'] > end:
            raise ValueError('entry does not follow minimal eight-byte alignment')
        if padding:
            spans[(cursor, offset)] = padding
        cursor = offset + entry['stored_size']
    padding = bytes((-cursor) % 8)
    if cursor + len(padding) != end:
        raise ValueError('bank has unexplained trailing storage')
    if padding:
        spans[(cursor, end)] = padding
    return spans


def index_spans(source, parent):
    start = parent['rom_start']
    spans = {(start, start + len(codec.encode(source))): codec.encode(source)}
    spans.update(alignment_spans(source, start, parent['rom_end']))
    return [(a - start, data) for (a, _), data in sorted(spans.items())]


def reviewed(backing, parent):
    if (parent.get('bank') not in NEW_BANKS or len(backing) != parent['rom_end'] - parent['rom_start']
            or sha(backing) != parent['original_sha256'] or len(backing) < 8):
        raise ValueError('bank index backing differs from reviewed bank')
    size = struct.unpack_from('>I', backing)[0]
    if not 8 <= size <= len(backing) or size % 8:
        raise ValueError('invalid bank index extent')
    source = codec.decode(backing[:size])
    spans = index_spans(source, parent)
    if any(backing[a:a + len(data)] != data for a, data in spans):
        raise ValueError('bank index alignment contains unexplained data')
    manifest = {'schema_version': 1, 'format': codec.FORMAT, 'bank': parent['bank'],
                'rom_start': parent['rom_start'], 'rom_end': parent['rom_end'],
                'ranges': [[a, a + len(data)] for a, data in spans],
                'sha256': sha(b''.join(data for _, data in spans)),
                'consumers': [{'start': a, 'size': n, 'sha1': h} for a, n, h in CODE_SPANS]}
    return manifest, source


def ensure_inputs(directory, parent, backing):
    manifest, source = reviewed(backing, parent)
    if not (directory / DIRECTORY).exists():
        texture_build.publish_inputs(directory / DIRECTORY, {
            'manifest.json': (json.dumps(manifest, indent=2) + '\n').encode(),
            'index.json': (json.dumps(source, indent=2) + '\n').encode()})


def input_hashes(directory, parent, backing):
    manifest, _ = reviewed(backing, parent)
    hashes = asset_inputs.manifest_hashes(directory / DIRECTORY, manifest,
        ('manifest.json', 'index.json'), 'bank index')
    return {(DIRECTORY / name).as_posix(): digest for name, digest in hashes.items()}


def encoded(directory, parent, backing):
    manifest, _ = reviewed(backing, parent)
    source = json.loads((directory / DIRECTORY / 'index.json').read_text())
    spans = index_spans(source, parent)
    if ([[a, a + len(data)] for a, data in spans] != manifest['ranges']
            or sha(b''.join(data for _, data in spans)) != manifest['sha256']):
        raise ValueError('bank index no longer reproduces reviewed storage')
    return spans


def existing_alignment(directory, parent):
    """Use existing authored outer and menu/dialogue indexes; no new source dump."""
    if parent['key'] not in ALIGNMENT_KEYS:
        return []
    source = json.loads((directory / 'directory.json').read_text())
    start = parent['rom_start']
    spans = alignment_spans(source, start, parent['rom_end'])
    nested = []
    if parent['key'] == 'bank1A':
        child = json.loads((directory / 'dialogue/dialogue.json').read_text())
        nested = [row['directory'] for row in child['languages']]
    elif parent['key'] == 'bank1C':
        nested = [json.loads((directory / 'menu-text/text.json').read_text())['directory']]
    for number, inner in enumerate(nested):
        entry = source['entries'][number]
        at = start + entry['relative_offset']
        additional = alignment_spans(inner, at, at + entry['stored_size'])
        if spans.keys() & additional.keys():
            raise ValueError('directory alignment ranges overlap')
        spans.update(additional)
    result = [(a - start, data) for (a, _), data in sorted(spans.items())]
    if any(a + len(data) > b for (a, data), (b, _) in zip(result, result[1:])):
        raise ValueError('directory alignment ranges overlap')
    return result
