"""Typed MP3 bank index and freshly generated minimal alignment spans."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct

try:
    from scripts import asset_directory_codec as codec, asset_inputs, texture_build, rzip_archive
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_directory_codec as codec, asset_inputs, texture_build, rzip_archive
    from model_character_alpha import checked_spans

DIRECTORY = Path('layout')
INPUT_DIRECTORY = Path('build/assets/mp3-bank/us')
CODE_SPANS = ((0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
              (0x1502B5C8, 244, '9c411ce6bf78e69583215fa8484bfd0f137edc72'))


def verify_consumers(rom, layout):
    game = rzip_archive.game_archive(rom, layout['game_start'], layout['game_end'])
    return checked_spans(game.code, layout['game_vram'], CODE_SPANS)


def reviewed(expected):
    if expected['profile'] != 'us' or expected['bank_index'] != 0x16:
        raise ValueError('unsupported MP3 bank layout')
    table = b''.join(struct.pack('>II', *record) for record in expected['records'])
    source = codec.decode(table)
    parts = [{'name': 'index', 'offset': 0, 'size': len(table),
              'sha256': hashlib.sha256(table).hexdigest()}]
    cursor = len(table)
    streams = {row['index']: row for row in expected['streams']}
    gaps = []
    for index, entry in enumerate(source['entries']):
        if entry['flags'] not in (0, 8):
            raise ValueError('MP3 layout contains compressed or unknown flags')
        if not entry['stored_size']:
            if index in streams:
                raise ValueError('empty MP3 index slot has a stream')
            continue
        stream = streams.pop(index, None)
        if stream is None or (entry['relative_offset'], entry['stored_size']) != (stream['offset'], stream['size']):
            raise ValueError('MP3 index does not describe the reviewed streams')
        gap = (-(expected['rom_start'] + cursor)) % 8
        if entry['relative_offset'] != cursor + gap:
            raise ValueError('MP3 stream does not follow minimal eight-byte alignment')
        if gap:
            gaps.append((cursor, gap))
        cursor = entry['relative_offset'] + entry['stored_size']
    if streams:
        raise ValueError('MP3 layout has unaccounted streams')
    remaining = expected['rom_end'] - expected['rom_start'] - cursor
    if remaining:
        if remaining != (-(expected['rom_start'] + cursor)) % 8:
            raise ValueError('MP3 layout has unexplained trailing storage')
        gaps.append((cursor, remaining))
    if gaps != [(row['offset'], row['size']) for row in expected['padding']]:
        raise ValueError('MP3 alignment inventory differs from derived gaps')
    for (offset, size), row in zip(gaps, expected['padding']):
        digest = hashlib.sha256(bytes(size)).hexdigest()
        name = f'padding/{offset:08X}'
        if row['file'] != name + '.bin' or row['sha256'] != digest:
            raise ValueError('MP3 alignment is not the reviewed generated zero fill')
        parts.append({'name': name, 'offset': offset, 'size': size, 'sha256': digest})
    manifest = {'schema_version': 1, 'format': 'mp3-bank-layout-native-v1',
                'rom_start': expected['rom_start'], 'rom_end': expected['rom_end'],
                'parts': parts, 'consumers': [{'start': a, 'size': n, 'sha1': h} for a, n, h in CODE_SPANS]}
    return manifest, source


def input_files(expected):
    manifest, source = reviewed(expected)
    return {'manifest.json': (json.dumps(manifest, indent=2) + '\n').encode(),
            'index.json': (json.dumps(source, indent=2) + '\n').encode()}


def ensure_inputs(directory, expected):
    if not (directory / DIRECTORY).exists():
        texture_build.publish_inputs(directory / DIRECTORY, input_files(expected))


def input_hashes(directory, expected):
    manifest, _ = reviewed(expected)
    hashes = asset_inputs.manifest_hashes(directory / DIRECTORY, manifest,
                                          ('manifest.json', 'index.json'), 'MP3 bank layout')
    return {(DIRECTORY / name).as_posix(): value for name, value in hashes.items()}


def encoded(directory, expected):
    manifest, _ = reviewed(expected)
    table = codec.encode(json.loads((directory / DIRECTORY / 'index.json').read_text()))
    if hashlib.sha256(table).hexdigest() != manifest['parts'][0]['sha256']:
        raise ValueError('MP3 index no longer reconstructs the reviewed layout')
    return [(part, table if part['name'] == 'index' else bytes(part['size'])) for part in manifest['parts']]


def part_hashes(directory, expected, part):
    if json.loads((directory / 'manifest.json').read_text()) != expected:
        raise ValueError('MP3 parent manifest differs from the reviewed layout')
    hashes = {'manifest.json': hashlib.sha256((directory / 'manifest.json').read_bytes()).hexdigest(),
              **input_hashes(directory, expected)}
    if part['name'] != 'index':
        name = part['name'] + '.bin'
        digest = hashlib.sha256((directory / name).read_bytes()).hexdigest()
        if digest != part['sha256']:
            raise ValueError('MP3 bank alignment padding changed')
        hashes[name] = digest
    return hashes


def recover(directory, expected, recovery_root):
    backup = asset_inputs.recover_directory(directory / DIRECTORY, recovery_root,
                                           'us-layout-', input_files(expected))
    return {'input_directory': str(directory / DIRECTORY), 'backup_directory': backup}


def main(argv=None):
    import argparse
    try:
        from scripts import mp3_assets, mp3_bank
    except ModuleNotFoundError:
        import mp3_assets, mp3_bank
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('recover',))
    args = parser.parse_args(argv)
    try:
        rom_path, rom, _, family = mp3_assets.load_profile_mp3_assets('us', None)
        _, layout = mp3_assets.resolve_rom('us', rom_path)
        verify_consumers(rom, layout)
        expected = mp3_bank.describe_bank(rom, family)
        root = mp3_assets.ROOT
        directory = root / INPUT_DIRECTORY
        mp3_bank.input_hashes(directory, expected)
        print(json.dumps(recover(directory, expected, root / 'build/assets/mp3-bank/recovery'), indent=2))
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
