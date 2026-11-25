"""Editable scene fields and lookup IDs within the preserved bank-15 object."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

try:
    from scripts import asset_inputs, asset_directory_codec as index_codec
    from scripts import scene_header_codec as codec, texture_build
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_inputs
    import asset_directory_codec as index_codec
    import scene_header_codec as codec
    import texture_build
    from model_character_alpha import checked_spans

DIRECTORY = Path('scene-headers')
CODE_SPANS = (
    (0x150000B0, 1584, 'd7d64152297212fde212ad58a6c6da4805e29e28'),
    (0x150006E0, 600, '973702b473ed10d5eda6bee701597aac42b5d530'),
    (0x15000940, 380, 'e97422686d5b2ccc1824f8942e7972936b3fc09c'),
    (0x15000AD0, 2448, 'db3541668e93174079730bedd448192d4399922e'),
    (0x15002FB4, 352, '12671f20de68fa9e1afb07632bf36734bc686177'),
    (0x150031EC, 712, 'ed48d58ffb38dab90c140a0d547dbdae13f3225a'),
    (0x15004E80, 124, '3a9708e49a6d867431e6c49ce50510c42ab7671d'),
    (0x150054C4, 852, '0c74b6d5b41ca35bd6dab6d0d4a6da1ddf591901'),
    (0x15005A60, 68, '63e8a64e5cd621133063d5d9e7ea7c7e3fa5b974'),
    (0x15007B3C, 1704, '5897d750e22cca5cfd3807a70361042faaf11c86'),
    (0x15009150, 120, 'de1fe10acad55765c5fa69f174e157dd177e2096'),
    (0x1500AF08, 748, 'c21ace33ec6fd5088b86d7aea8b7ad26fdc3b9b3'),
    (0x1500E470, 336, '65c391c6679cf7b9daab2f1ca4b59f65af00f690'),
    (0x150127B0, 1236, '9ab76db4fe57dc8da87681f84438c89e92362269'),
    (0x15015E80, 188, '8cfc674d6542596320221061abdce88b7ea607c1'),
    (0x15017868, 200, '5037eff0023a4a96e99a92d703493e9b967d90a9'),
    (0x1501CC3C, 388, 'f41a536ac40443c671b6fc8536943dff2c83ba5d'),
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
    (0x1502B4A8, 288, 'd1a82190ae64677a9404302b5a61653a5770a7dc'),
    (0x1502B6BC, 308, '91ed9cccb2168331f871d0b5b3597f9cfc8f558f'),
    (0x1502C974, 704, '166b05f7f97b828a9ebad3c9a7e51e8a6b748eea'),
    (0x150311C4, 1896, 'e276f4d4cce00c18939e50ff942094540aae5f1e'),
    (0x1504A730, 1696, 'cc2b08465267b571c76efcafa9a65573047775e6'),
    (0x1505B5F8, 972, '76ec202ad995bd2d5e8b618535a546bb06b7d0bb'),
    (0x1509B4A0, 208, 'cd7bc53cf5b4920ed87dff50e7faab869beb3b23'),
    (0x1510FEA0, 1068, '0b50922f91f99da8ecbd966a72e3545ea71551e9'),
    (0x15111AF4, 2604, 'cffa240084a658ffeee1215fd6498746e5bd0b22'),
    (0x15130230, 68, '3b0b946993cabf13efa513d963ff03fd8b0d9e76'),
    (0x151732E0, 248, 'fa16d05012863cd36cbf16d62083d12b1326b527'),
    (0x151738C4, 208, '48f23d9683b649d455247c94c48f66f4cfb5cb78'),
    (0x15173994, 24, 'd39d4d2607abb9e044800ec932560de10e2252c8'),
    (0x151749F8, 172, '8749405317b70ff18a55471aad596dcfd5a57404'),
    (0x15174AA4, 164, 'c4139e9ed546efad90c87b58c7f4cabbb77b9983'),
    (0x15174B48, 164, 'eff44f153aa5e04b09b97a1ddb21373fb80abd8c'),
    (0x15178E50, 88, 'e5a1e1a630999d6e64e3280ebf3f58121b0dcb52'),
    (0x15186794, 2844, 'cf8df41531db51e4f00144b140289ec3af632c13'),
    (0x151C2050, 588, 'f50b8215aeeb8f92410c62c766ee6044bcdd9a95'),
    (0x151EB06C, 2244, '321cdb6b0234419d3d38a4acc4151786d502aeea'),
)
MAIN_SPANS = (
    (0x80012020, 1340, 'c1d977a5ec7af0c058a49442e42e99ecfa384d8f'),
)


def verify_consumers(rom, code, base):
    return {'game': checked_spans(code, base, CODE_SPANS),
            'main': checked_spans(rom, 0x80000000, MAIN_SPANS)}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def reviewed(backing, parent):
    if (parent['key'] != 'bank15' or parent['directory_size'] != 552
            or len(backing) != parent['rom_end'] - parent['rom_start']
            or sha(backing) != parent['original_sha256']):
        raise ValueError('scene bank differs from reviewed storage')
    outer = index_codec.decode(backing[:552])
    rows, records = [], []
    for index, entry in enumerate(outer['entries']):
        if entry['flags'] != (8 if index == 68 else 0):
            raise ValueError('scene bank has unsupported flags')
        size = entry['stored_size']
        if not size:
            continue
        offset = entry['relative_offset']
        if offset + size > len(backing):
            raise ValueError('scene container exceeds native bank')
        source = codec.decode(backing[offset:offset + size])
        spans = codec.encode(source)
        rows.append({'index': index, 'offset': offset, 'size': size,
                     'ranges': [[a, a + len(data)] for a, data in spans],
                     'generated_sha256': sha(b''.join(data for _, data in spans))})
        records.append({'index': index, 'scene': source})
    if len(rows) != 67:
        raise ValueError('scene bank must contain 67 native containers')
    manifest = {'schema_version': 1, 'format': codec.FORMAT,
                'rom_start': parent['rom_start'], 'rom_end': parent['rom_end'],
                'records': rows,
                'game_consumers': [{'start': a, 'size': n, 'sha1': h} for a, n, h in CODE_SPANS],
                'main_consumers': [{'start': a, 'size': n, 'sha1': h} for a, n, h in MAIN_SPANS]}
    return manifest, {'format': codec.FORMAT, 'records': records}


def ensure_inputs(directory, expected, backing):
    manifest, source = reviewed(backing, expected)
    if not (directory / DIRECTORY).exists():
        texture_build.publish_inputs(directory / DIRECTORY, {
            'manifest.json': (json.dumps(manifest, indent=2) + '\n').encode(),
            'scenes.json': (json.dumps(source, indent=2) + '\n').encode()})


def input_hashes(directory, expected, backing):
    manifest, _ = reviewed(backing, expected)
    hashes = asset_inputs.manifest_hashes(directory / DIRECTORY, manifest,
                                          ('manifest.json', 'scenes.json'), 'scene headers')
    return {(DIRECTORY / name).as_posix(): digest for name, digest in hashes.items()}


def encoded(directory, expected, backing):
    manifest, _ = reviewed(backing, expected)
    source = json.loads((directory / DIRECTORY / 'scenes.json').read_text())
    if (type(source) is not dict or set(source) != {'format', 'records'}
            or source['format'] != codec.FORMAT or type(source['records']) is not list
            or len(source['records']) != len(manifest['records'])):
        raise ValueError('invalid scene bank source')
    spans = []
    for record, proof in zip(source['records'], manifest['records'], strict=True):
        if (type(record) is not dict or set(record) != {'index', 'scene'}
                or type(record['index']) is not int or record['index'] != proof['index']):
            raise ValueError('scene selection changed')
        fresh = codec.encode(record['scene'])
        if ([[a, a + len(data)] for a, data in fresh] != proof['ranges']
                or sha(b''.join(data for _, data in fresh)) != proof['generated_sha256']):
            raise ValueError('scene fields no longer reproduce reviewed storage')
        spans.extend((proof['offset'] + offset, data) for offset, data in fresh)
    return spans
