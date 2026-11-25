"""Editable US bank-1C text and its nested directory; storage gaps stay excluded."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct

try:
    from scripts import asset_inputs, asset_directory_codec as index_codec
    from scripts import menu_text_codec as codec, texture_build
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_inputs
    import asset_directory_codec as index_codec
    import menu_text_codec as codec
    import texture_build
    from model_character_alpha import checked_spans

DIRECTORY = Path('menu-text')
CODE_SPANS = ((0x151E6964, 664, '98c7ad9d7d85e4d61c1b884976d9cd69a8b6d21c'),
              (0x150417AC, 4392, 'a778546ac55048b14f49c93aa0016b5771218e39'),
              (0x150415E0, 460, '824a58833934924d26413602b5ce5c6041ad5b1b'),
              (0x15042C40, 260, '1cbcc484f919723ecfaa366957051beedf919817'))
DATA_SPANS = ((0x80085930, 95, '638383dd651377aeb3e254fe60797e07d2d0a68b'),
              (0x80098B14, 108, 'bb82701baa65290c194dbfd69518d35c414cecca'))


def verify_consumers(code, code_base, data, data_base):
    return {'code': checked_spans(code, code_base, CODE_SPANS),
            'data': checked_spans(data, data_base, DATA_SPANS)}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def reviewed(backing: bytes, directory: dict) -> tuple[dict, dict]:
    if (directory['key'] != 'bank1C' or directory['directory_size'] != 40
            or len(backing) < 72 or sha(backing) != directory['original_sha256']):
        raise ValueError('menu text differs from the reviewed native bank')
    if struct.unpack_from('>II', backing) != (40, len(backing) - 40):
        raise ValueError('menu language directory must contain one uncompressed child')
    for i in range(1, 5):
        if struct.unpack_from('>II', backing, 8 * i) != (len(backing), 0x80000000 if i == 4 else 0):
            raise ValueError('unexpected additional menu language storage')
    raw_index = backing[40:72]
    index = index_codec.decode(raw_index)
    tables, entries = [], []
    previous_end = 72
    for i in range(4):
        relative, word = struct.unpack_from('>II', raw_index, 8 * i)
        offset, size, flags = 40 + relative, word & 0xfffffff, word >> 28
        if (flags != (9 if i == 3 else 1) or offset < previous_end
                or size < 5 or offset + size > len(backing)):
            raise ValueError('invalid nested menu text extent')
        previous_end = offset + size
        original = backing[offset:previous_end]
        decoded = codec.unpack(original)
        source = codec.decode(decoded)
        if codec.compress(codec.encode(source)) != original:
            raise ValueError('menu text does not reproduce original compression')
        tables.append(source)
        entries.append({'offset': offset, 'stored_size': size, 'decoded_size': len(decoded),
                        'string_count': len(source['strings']), 'sha256': sha(original)})
    manifest = {'schema_version': 1, 'format': codec.FORMAT,
                'rom_start': directory['rom_start'], 'rom_end': directory['rom_end'],
                'nested_directory_sha256': sha(raw_index), 'entries': entries,
                'code_consumers': [{'start': a, 'size': s, 'sha1': h} for a, s, h in CODE_SPANS],
                'data_consumers': [{'start': a, 'size': s, 'sha1': h} for a, s, h in DATA_SPANS]}
    return manifest, {'format': codec.FORMAT, 'directory': index, 'tables': tables}


def ensure_inputs(directory: Path, expected: dict, backing: bytes) -> None:
    manifest, source = reviewed(backing, expected)
    target = directory / DIRECTORY
    if not target.exists():
        texture_build.publish_inputs(target, {
            'manifest.json': (json.dumps(manifest, indent=2) + '\n').encode(),
            'text.json': (json.dumps(source, indent=2) + '\n').encode()})


def input_hashes(directory: Path, expected: dict, backing: bytes) -> dict:
    manifest, _ = reviewed(backing, expected)
    hashes = asset_inputs.manifest_hashes(directory / DIRECTORY, manifest,
                                          ('manifest.json', 'text.json'), 'menu text')
    return {(DIRECTORY / name).as_posix(): digest for name, digest in hashes.items()}


def encoded(directory: Path, expected: dict, backing: bytes) -> list[tuple[int, bytes]]:
    manifest, _ = reviewed(backing, expected)
    source = json.loads((directory / DIRECTORY / 'text.json').read_text())
    if (type(source) is not dict or set(source) != {'format', 'directory', 'tables'}
            or source['format'] != codec.FORMAT or type(source['tables']) is not list
            or len(source['tables']) != 4):
        raise ValueError('menu bank requires a nested directory and four text tables')
    index = index_codec.encode(source['directory'])
    if len(index) != 32 or sha(index) != manifest['nested_directory_sha256']:
        raise ValueError('menu directory no longer reproduces reviewed storage')
    spans = [(40, index)]
    for table, entry in zip(source['tables'], manifest['entries']):
        decoded = codec.encode(table)
        fresh = codec.compress(decoded)
        if (len(table['strings']) != entry['string_count'] or len(decoded) != entry['decoded_size']
                or len(fresh) != entry['stored_size'] or sha(fresh) != entry['sha256']):
            raise ValueError('menu text no longer reproduces reviewed storage')
        spans.append((entry['offset'], fresh))
    return spans
