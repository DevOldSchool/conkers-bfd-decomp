"""Editable bank-1A language directories and dialogue; external gaps stay backing."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

try:
    from scripts import asset_inputs, asset_directory_codec as index_codec
    from scripts import dialogue_codec as codec, texture_build
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_inputs
    import asset_directory_codec as index_codec
    import dialogue_codec as codec
    import texture_build
    from model_character_alpha import checked_spans

DIRECTORY = Path('dialogue')
FORMAT = 'dialogue-bank-native-v1'
CODE_SPANS = (
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
    (0x1502B350, 344, 'd789fbbc29db59a4ea107ebe753587f3774b8d51'),
    (0x1502B4A8, 288, 'd1a82190ae64677a9404302b5a61653a5770a7dc'),
    (0x1502B6BC, 308, '91ed9cccb2168331f871d0b5b3597f9cfc8f558f'),
    (0x15080784, 112, 'cb41f8fe55d9f909549c8581061cb0d989826f46'),
    (0x150807F4, 52, '5fb4dfc14d7d96b2c23dbc04de314090f48cb27e'),
    (0x15080828, 960, '8636fda707da13836dba8b0178a7e177bdaadae9'),
    (0x1516A770, 64, '18df06617601ad6875a4e884a29200301024ef5a'),
    (0x1516A7B0, 704, '9aa9e16a434ff6083f8bcdb92689e0bfa464e554'),
    (0x1516C878, 188, '3a580a51a07d1ea387c917cb3a9c76d047e1b6c2'),
    (0x1516C934, 804, '20936c05b95eb29379e17a68a56d2f9d51bc6689'),
    (0x150415E0, 460, '824a58833934924d26413602b5ce5c6041ad5b1b'),
    (0x150417AC, 4392, 'a778546ac55048b14f49c93aa0016b5771218e39'),
    (0x150428D4, 876, '2c2fc01dc865c503a3ecc421e796caf3b6783558'),
    (0x15042C40, 260, '1cbcc484f919723ecfaa366957051beedf919817'),
)
DATA_SPANS = ((0x80085930, 95, '638383dd651377aeb3e254fe60797e07d2d0a68b'),
              (0x80098B14, 108, 'bb82701baa65290c194dbfd69518d35c414cecca'))


def verify_consumers(code, code_base, data, data_base):
    return {'code': checked_spans(code, code_base, CODE_SPANS),
            'data': checked_spans(data, data_base, DATA_SPANS)}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def reviewed(backing: bytes, directory: dict) -> tuple[dict, dict]:
    if (directory['key'] != 'bank1A' or directory['directory_size'] != 40
            or len(backing) < 40 or sha(backing) != directory['original_sha256']):
        raise ValueError('dialogue differs from the reviewed native bank')
    outer = index_codec.decode(backing[:40])
    languages, manifest_rows = [], []
    previous = 40
    for language, entry in enumerate(outer['entries']):
        offset, size = entry['relative_offset'], entry['stored_size']
        if (entry['flags'] != (8 if language == 4 else 0) or offset < previous
                or size < 544 or offset + size > len(backing)):
            raise ValueError('invalid dialogue language extent')
        previous = offset + size
        raw_index = backing[offset:offset + 544]
        index = index_codec.decode(raw_index)
        content, records = [], []
        for number, child in enumerate(index['entries']):
            flags = child['flags']
            if flags not in ((8, 9) if number == 67 else (0, 1)):
                raise ValueError('invalid dialogue entry flags')
            stored_size = child['stored_size']
            if not stored_size:
                continue
            start = offset + child['relative_offset']
            if start + stored_size > offset + size:
                raise ValueError('dialogue child exceeds language extent')
            original = backing[start:start + stored_size]
            compressed = bool(flags & 1)
            decoded = codec.unpack(original) if compressed else original
            source = codec.decode(decoded)
            fresh = codec.encode(source)
            fresh = codec.compress(fresh) if compressed else fresh
            if fresh != original:
                raise ValueError('dialogue does not reproduce original compression')
            content.append({'index': number, 'dialogue': source})
            records.append({'index': number, 'offset': start, 'stored_size': stored_size,
                            'decoded_size': len(decoded), 'compressed': compressed,
                            'sha256': sha(original)})
        languages.append({'directory': index, 'records': content})
        manifest_rows.append({'offset': offset, 'directory_size': 544,
                              'directory_sha256': sha(raw_index), 'records': records})
    manifest = {'schema_version': 1, 'format': FORMAT,
                'rom_start': directory['rom_start'], 'rom_end': directory['rom_end'],
                'languages': manifest_rows,
                'code_consumers': [{'start': a, 'size': s, 'sha1': h} for a, s, h in CODE_SPANS],
                'data_consumers': [{'start': a, 'size': s, 'sha1': h} for a, s, h in DATA_SPANS]}
    return manifest, {'format': FORMAT, 'languages': languages}


def ensure_inputs(directory: Path, expected: dict, backing: bytes) -> None:
    manifest, source = reviewed(backing, expected)
    target = directory / DIRECTORY
    if not target.exists():
        texture_build.publish_inputs(target, {
            'manifest.json': (json.dumps(manifest, indent=2) + '\n').encode(),
            'dialogue.json': (json.dumps(source, indent=2) + '\n').encode()})


def input_hashes(directory: Path, expected: dict, backing: bytes) -> dict:
    manifest, _ = reviewed(backing, expected)
    hashes = asset_inputs.manifest_hashes(directory / DIRECTORY, manifest,
                                          ('manifest.json', 'dialogue.json'), 'dialogue')
    return {(DIRECTORY / name).as_posix(): digest for name, digest in hashes.items()}


def encoded(directory: Path, expected: dict, backing: bytes) -> list[tuple[int, bytes]]:
    manifest, _ = reviewed(backing, expected)
    source = json.loads((directory / DIRECTORY / 'dialogue.json').read_text())
    if (type(source) is not dict or set(source) != {'format', 'languages'}
            or source['format'] != FORMAT or type(source['languages']) is not list
            or len(source['languages']) != 5):
        raise ValueError('dialogue bank requires five language directories')
    spans = []
    for language, proof in zip(source['languages'], manifest['languages'], strict=True):
        if (type(language) is not dict or set(language) != {'directory', 'records'}
                or type(language['records']) is not list or len(language['records']) != len(proof['records'])):
            raise ValueError('invalid dialogue language schema')
        index = index_codec.encode(language['directory'])
        if len(index) != proof['directory_size'] or sha(index) != proof['directory_sha256']:
            raise ValueError('dialogue directory no longer reproduces reviewed storage')
        spans.append((proof['offset'], index))
        for record, entry in zip(language['records'], proof['records'], strict=True):
            if (type(record) is not dict or set(record) != {'index', 'dialogue'}
                    or type(record['index']) is not int or record['index'] != entry['index']):
                raise ValueError('dialogue record selection changed')
            decoded = codec.encode(record['dialogue'])
            fresh = codec.compress(decoded) if entry['compressed'] else decoded
            if (len(decoded) != entry['decoded_size'] or len(fresh) != entry['stored_size']
                    or sha(fresh) != entry['sha256']):
                raise ValueError('dialogue no longer reproduces reviewed storage')
            spans.append((entry['offset'], fresh))
    return spans
