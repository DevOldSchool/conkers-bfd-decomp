"""Editable camera tracks composed into the original bank-1B linker object."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct

try:
    from scripts import asset_inputs, camera_tracks_codec as codec, texture_build
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_inputs
    import camera_tracks_codec as codec
    import texture_build
    from model_character_alpha import checked_spans

DIRECTORY = Path('camera-tracks')
CODE_SPANS = ((0x1512D238, 172, 'c8377042a8ea9554438110cd544b3504e6e5f58d'),
              (0x1512C490, 3040, '6e3de8106f6ac5997e9db8d4da9acde1a106f965'),
              (0x1512D2F8, 112, '2cae95492810b9f2236178b577ecc53922d77624'))


def verify_consumers(code, base):
    return checked_spans(code, base, CODE_SPANS)


def reviewed(backing: bytes, directory: dict) -> tuple[dict, dict]:
    if (directory['key'] != 'bank1B' or directory['directory_size'] != 32
            or len(backing) < 32 or struct.unpack_from('>I', backing)[0] != 32
            or hashlib.sha256(backing).hexdigest() != directory['original_sha256']):
        raise ValueError('camera tracks differ from the reviewed native bank')
    tracks, entries = [], []
    previous_end = 32
    for index in range(4):
        offset, word = struct.unpack_from('>2I', backing, index * 8)
        size, flags = word & 0x0fffffff, word >> 28
        if (flags != (9 if index == 3 else 1) or offset < previous_end
                or size < 5 or offset + size > len(backing)):
            raise ValueError('invalid native camera track extent')
        previous_end = offset + size
        original = backing[offset:previous_end]
        decoded = codec.unpack(original)
        source = codec.decode(decoded)
        if codec.compress(codec.encode(source)) != original:
            raise ValueError('camera track does not reproduce original compression')
        tracks.append(source)
        entries.append({'offset': offset, 'stored_size': size,
                        'decoded_size': len(decoded),
                        'sha256': hashlib.sha256(original).hexdigest()})
    expected = {'schema_version': 1, 'format': codec.FORMAT,
                'rom_start': directory['rom_start'], 'rom_end': directory['rom_end'],
                'entries': entries,
                'consumers': [{'start': start, 'size': size, 'sha1': digest}
                              for start, size, digest in CODE_SPANS]}
    return expected, {'format': codec.FORMAT, 'tracks': tracks}


def ensure_inputs(directory: Path, expected: dict, backing: bytes) -> None:
    manifest, source = reviewed(backing, expected)
    target = directory / DIRECTORY
    if not target.exists():
        texture_build.publish_inputs(target, {
            'manifest.json': (json.dumps(manifest, indent=2) + '\n').encode(),
            'tracks.json': (json.dumps(source, indent=2, allow_nan=False) + '\n').encode()})


def input_hashes(directory: Path, expected: dict, backing: bytes) -> dict:
    manifest, _ = reviewed(backing, expected)
    hashes = asset_inputs.manifest_hashes(directory / DIRECTORY, manifest,
                                          ('manifest.json', 'tracks.json'), 'camera tracks')
    return {(DIRECTORY / name).as_posix(): digest for name, digest in hashes.items()}


def encoded(directory: Path, expected: dict, backing: bytes) -> list[tuple[int, bytes]]:
    manifest, _ = reviewed(backing, expected)
    source = json.loads((directory / DIRECTORY / 'tracks.json').read_text())
    if (type(source) is not dict or set(source) != {'format', 'tracks'}
            or source['format'] != codec.FORMAT or type(source['tracks']) is not list
            or len(source['tracks']) != 4):
        raise ValueError('camera bank requires exactly four tracks')
    spans = []
    for track, entry in zip(source['tracks'], manifest['entries']):
        decoded = codec.encode(track)
        fresh = codec.compress(decoded)
        if (len(decoded) != entry['decoded_size'] or len(fresh) != entry['stored_size']
                or hashlib.sha256(fresh).hexdigest() != entry['sha256']):
            raise ValueError('camera deltas no longer reproduce the reviewed ROM track')
        spans.append((entry['offset'], fresh))
    return spans
