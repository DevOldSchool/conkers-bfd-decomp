"""Separately editable collision entries composed into bank 0F."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct
import zlib

try:
    from scripts import asset_inputs, animation_control_codec as codec, texture_build, rzip_archive
    from scripts.collision_control_codec import FORMAT
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_inputs, animation_control_codec as codec, texture_build, rzip_archive
    from collision_control_codec import FORMAT
    from model_character_alpha import checked_spans

DIRECTORY = Path('collision-controls')
ENTRIES = (12, 27, 46, 51, 62, 69, 77, 84, 102, 107, 120, 126, 127, 158, 166, 172)
CODE_SPANS = ((0x1505B9C4, 1916, '2f1e6ec26658042e24f9235e4fe108b9d32eda77'),
              (0x1505C1A4, 64, '2917af6483e72651d562e20f057fbf0aeb1d2364'),
              (0x1505C7D8, 2124, '0fd78a95b2be0c345f10fabeceea6a50773c90e3'))


def verify_consumers(code, base):
    return checked_spans(code, base, CODE_SPANS)


def compress(data):
    encoder = zlib.compressobj(level=6, wbits=-15)
    return struct.pack('>I', len(data)) + encoder.compress(data) + encoder.flush()


def reviewed(backing, parent):
    if (parent['bank'] != 15 or len(backing) < 8
            or hashlib.sha256(backing).hexdigest() != parent['original_sha256']):
        raise ValueError('collision controls differ from the reviewed bank')
    table_size = struct.unpack_from('>I', backing)[0]
    if table_size % 8 or table_size > len(backing) or table_size < (max(ENTRIES) + 1) * 8:
        raise ValueError('invalid collision control directory')
    rows, records, previous_end = [], {}, table_size
    for index in ENTRIES:
        offset, word = struct.unpack_from('>II', backing, index * 8)
        size, flags = word & 0xfffffff, word >> 28
        if flags not in (1, 9) or offset < previous_end or size < 5 or offset + size > len(backing):
            raise ValueError('invalid collision control extent')
        previous_end = offset + size
        # Existing credited entries must remain disjoint from the new family.
        start, end = parent['rom_start'] + offset, parent['rom_start'] + previous_end
        if any(start < b and a < end for a, b in parent['rom_ranges']):
            raise ValueError('collision control overlaps an existing reconstructed entry')
        original = backing[offset:previous_end]
        chunk = rzip_archive.decode_rzip_chunk(original)
        record = codec.decode(chunk.data, allow_collisions=True)
        if (chunk.consumed != size or record['format'] != FORMAT
                or compress(codec.encode(record)) != original):
            raise ValueError('collision control does not reproduce original compression')
        records[str(index)] = record
        rows.append({'entry': index, 'offset': offset, 'stored_size': size,
                     'decoded_size': len(chunk.data), 'sha256': hashlib.sha256(original).hexdigest()})
    manifest = {'schema_version': 1, 'format': FORMAT,
                'rom_start': parent['rom_start'], 'rom_end': parent['rom_end'],
                'entries': rows, 'consumers': [{'start': a, 'size': n, 'sha1': h} for a, n, h in CODE_SPANS]}
    return manifest, records


def input_files(backing, expected):
    manifest, records = reviewed(backing, expected)
    return {'manifest.json': (json.dumps(manifest, indent=2) + '\n').encode(),
            'controls.json': (json.dumps(records, indent=2, allow_nan=False) + '\n').encode()}


def ensure_inputs(directory, expected, backing):
    target = directory / DIRECTORY
    if not target.exists():
        texture_build.publish_inputs(target, input_files(backing, expected))


def input_hashes(directory, expected, backing):
    manifest, _ = reviewed(backing, expected)
    hashes = asset_inputs.manifest_hashes(directory / DIRECTORY, manifest,
                                          ('manifest.json', 'controls.json'), 'collision controls')
    return {(DIRECTORY / name).as_posix(): value for name, value in hashes.items()}


def encoded(directory, expected, backing):
    manifest, _ = reviewed(backing, expected)
    records = json.loads((directory / DIRECTORY / 'controls.json').read_text())
    if type(records) is not dict or set(records) != {str(i) for i in ENTRIES}:
        raise ValueError('collision control entry set changed')
    spans = []
    for row in manifest['entries']:
        record = records[str(row['entry'])]
        if type(record) is not dict or record.get('format') != FORMAT:
            raise ValueError('collision control format changed')
        decoded = codec.encode(record)
        fresh = compress(decoded)
        if (len(decoded) != row['decoded_size'] or len(fresh) != row['stored_size']
                or hashlib.sha256(fresh).hexdigest() != row['sha256']):
            raise ValueError('collision controls no longer reconstruct original storage')
        spans.append((row['offset'], fresh))
    return spans
