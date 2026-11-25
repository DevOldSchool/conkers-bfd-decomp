"""Editable save widths composed into the existing bank-07 directory object.

The directory retains its own manifest and source unchanged. Only the 69 bytes
read by both native loops are generated here; trailing storage stays excluded.
"""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct

try:
    from scripts import asset_inputs, save_layout_codec as codec, texture_build
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_inputs
    import save_layout_codec as codec
    import texture_build
    from model_character_alpha import checked_spans

DIRECTORY = Path('save-layout')
CODE_SPANS = ((0x15006590, 1628, '324013365c23946b311c63491cf8df35864a68b9'),
              (0x15006BEC, 1168, '8a66e901d3c6cab285c357fd08ad121dbe6ca7b1'))


def verify_consumers(code, base):
    return checked_spans(code, base, CODE_SPANS)


def reviewed(backing: bytes, directory: dict) -> tuple[dict, dict]:
    if (directory['key'] != 'bank07' or directory['directory_size'] != 8
            or len(backing) != 80 or struct.unpack_from('>2I', backing) != (8, 0x80000045)
            or hashlib.sha256(backing).hexdigest() != directory['original_sha256']):
        raise ValueError('save layout differs from the reviewed native bank')
    payload = backing[8:8 + codec.FIELD_COUNT]
    source = codec.decode(payload)
    expected = {'schema_version': 1, 'format': codec.FORMAT,
                'rom_start': directory['rom_start'] + 8,
                'rom_end': directory['rom_start'] + 8 + codec.FIELD_COUNT,
                'sha256': hashlib.sha256(payload).hexdigest(),
                'consumers': [{'start': start, 'size': size, 'sha1': digest}
                              for start, size, digest in CODE_SPANS]}
    return expected, source


def ensure_inputs(directory: Path, expected: dict, backing: bytes) -> None:
    manifest, source = reviewed(backing, expected)
    target = directory / DIRECTORY
    if not target.exists():
        texture_build.publish_inputs(target, {
            'manifest.json': (json.dumps(manifest, indent=2) + '\n').encode(),
            'widths.json': (json.dumps(source, indent=2) + '\n').encode()})


def input_hashes(directory: Path, expected: dict, backing: bytes) -> dict:
    manifest, _ = reviewed(backing, expected)
    hashes = asset_inputs.manifest_hashes(directory / DIRECTORY, manifest,
                                          ('manifest.json', 'widths.json'), 'save layout')
    return {(DIRECTORY / name).as_posix(): digest for name, digest in hashes.items()}


def encoded(directory: Path, expected: dict, backing: bytes) -> bytes:
    manifest, _ = reviewed(backing, expected)
    fresh = codec.encode(json.loads((directory / DIRECTORY / 'widths.json').read_text()))
    if hashlib.sha256(fresh).hexdigest() != manifest['sha256']:
        raise ValueError('save field widths no longer reproduce the reviewed ROM table')
    return fresh
