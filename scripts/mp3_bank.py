"""Build the reviewed US bank-16 container from encoded MP3 files and its index."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct

try:
    from scripts import mp3_assets
except ModuleNotFoundError:
    import mp3_assets


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def describe_bank(rom: bytes, family: mp3_assets.Mp3AssetFamily) -> dict:
    """Keep every original index slot and account separately for alignment padding."""
    start, end = family.stream_bank_start, family.stream_bank_end
    table_size = struct.unpack_from('>I', rom, start)[0]
    if not 0 <= start < start + table_size <= end <= len(rom) or table_size % 8:
        raise ValueError('invalid MP3 bank index extent')
    records = [list(struct.unpack_from('>II', rom, start + offset)) for offset in range(0, table_size, 8)]
    streams, padding = [], []
    cursor = table_size
    for stream in family.streams:
        offset, size = stream.rom_start - start, len(stream.data)
        if (stream.entry_index >= len(records) or records[stream.entry_index][0] != offset
                or (records[stream.entry_index][1] & 0x0FFFFFFF) != size
                or records[stream.entry_index][1] >> 24 != stream.type_flags
                or stream.compressed or stream.rom_end != start + offset + size
                or offset < cursor or offset + size > end - start
                or rom[stream.rom_start:stream.rom_end] != stream.data):
            raise ValueError('MP3 stream disagrees with its raw bank index')
        if offset > cursor:
            padding.append({'offset': cursor, 'size': offset - cursor,
                         'file': f'padding/{cursor:08X}.bin',
                         'sha256': sha256(rom[start + cursor:start + offset])})
        streams.append({'index': stream.entry_index, 'offset': offset, 'size': size,
                        'file': f'streams/{stream.entry_index:04d}.mp3',
                        'original_sha256': sha256(stream.data)})
        cursor = offset + size
    if cursor < end - start:
        padding.append({'offset': cursor, 'size': end - start - cursor,
                     'file': f'padding/{cursor:08X}.bin', 'sha256': sha256(rom[start + cursor:end])})
    if {i for i, (_, size) in enumerate(records) if size & 0x0FFFFFFF} != {s['index'] for s in streams}:
        raise ValueError('MP3 bank has unaccounted index records')
    for entry in padding:
        begin = start + entry['offset']
        if entry['size'] != (-begin) % 8 or any(rom[begin:begin + entry['size']]):
            raise ValueError('MP3 bank padding must be zero-filled to the next 8-byte boundary')
    return {'schema_version': 1, 'profile': 'us', 'bank_index': 0x16,
            'rom_sha1': hashlib.sha1(rom).hexdigest(), 'rom_start': start, 'rom_end': end,
            'records': records, 'streams': streams, 'padding': padding}


def initialize_inputs(directory: Path, manifest: dict, rom: bytes) -> None:
    """Initialize once; never replace an existing input tree or user's edits."""
    if directory.exists():
        raise ValueError('MP3 bank inputs exist without a manifest; refusing to overwrite them')
    directory.mkdir(parents=True)
    start = manifest['rom_start']
    for entry in manifest['streams'] + manifest['padding']:
        path = directory / entry['file']
        path.parent.mkdir(exist_ok=True)
        offset = start + entry['offset']
        path.write_bytes(rom[offset:offset + entry['size']])
    (directory / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')


def input_hashes(directory: Path, expected: dict) -> dict[str, str]:
    manifest = json.loads((directory / 'manifest.json').read_text())
    if manifest != expected:
        raise ValueError('MP3 bank manifest differs from the reviewed ROM layout')
    names = ['manifest.json'] + [entry['file'] for entry in expected['streams'] + expected['padding']]
    return {name: sha256((directory / name).read_bytes()) for name in names}


def packed_bank(directory: Path, expected: dict) -> tuple[bytes, dict[str, str]]:
    """Keep fixed storage coordinates; edits must retain stream lengths and framing.

    Index metadata and alignment padding retain their original values. Streams may
    change without changing their recorded original digest; comparison and the
    complete ROM build independently decide whether the result still matches.
    """
    before = input_hashes(directory, expected)
    size = expected['rom_end'] - expected['rom_start']
    output = bytearray(size)
    table = b''.join(struct.pack('>II', *record) for record in expected['records'])
    output[:len(table)] = table
    cursor = len(table)
    pieces = sorted([(entry, True) for entry in expected['streams']]
                    + [(entry, False) for entry in expected['padding']], key=lambda item: item[0]['offset'])
    for entry, stream in pieces:
        data = (directory / entry['file']).read_bytes()
        end = cursor + entry['size']
        if entry['offset'] != cursor or len(data) != entry['size'] or end > size:
            raise ValueError('MP3 bank inputs do not cover their exact fixed storage ranges')
        if stream:
            parsed = mp3_assets.parse_mp3_cue_stream(data)
            if not parsed.frame_count:
                raise ValueError('MP3 bank stream has no complete MPEG frames')
        elif sha256(data) != entry['sha256']:
            raise ValueError('MP3 bank alignment padding changed')
        output[cursor:end] = data
        cursor = end
    if cursor != size or before != input_hashes(directory, expected):
        raise ValueError('MP3 bank is incomplete or inputs changed during packing')
    return bytes(output), before


def build_bank(input_dir: Path, output: Path) -> tuple[bytes, dict]:
    rom_path, rom, _, family = mp3_assets.load_profile_mp3_assets('us', None)
    expected = describe_bank(rom, family)
    if output.resolve() == rom_path.resolve() or output.resolve().is_relative_to(input_dir.resolve()):
        raise ValueError('MP3 bank output would overwrite source inputs')
    if not (input_dir / 'manifest.json').is_file():
        initialize_inputs(input_dir, expected, rom)
    packed, hashes = packed_bank(input_dir, expected)
    output.parent.mkdir(parents=True, exist_ok=True)
    temporary = output.with_suffix(output.suffix + '.tmp')
    temporary.write_bytes(packed)
    temporary.replace(output)
    evidence = {'rom_start': expected['rom_start'], 'rom_end': expected['rom_end'],
                'rom_sha1': expected['rom_sha1'], 'stream_count': len(expected['streams']),
                'index_bytes': len(expected['records']) * 8,
                'stream_bytes': sum(s['size'] for s in expected['streams']),
                'padding_bytes': sum(s['size'] for s in expected['padding']),
                'source_inputs': hashes, 'sha256': sha256(packed),
                'matches_original': packed == rom[expected['rom_start']:expected['rom_end']]}
    output.with_suffix('.json').write_text(json.dumps(evidence, indent=2) + '\n')
    return packed, evidence


def layout_bins(profile: Path) -> list[tuple[int, str]]:
    """Read the canonical splat input names and boundaries without opening a ROM."""
    import yaml
    config = yaml.safe_load(profile.read_text())
    bank = next(segment for segment in config['segments']
                if isinstance(segment, dict) and segment.get('name') == 'asset_bank_16')
    if bank['type'] != 'group' or bank['align'] != 1 or bank['subalign'] != 1:
        raise ValueError('MP3 bank must retain byte-aligned group placement')
    result = []
    for entry in bank['subsegments']:
        if (len(entry) != 3 or entry[1] != 'bin' or not entry[2].startswith('audio/mp3/')
                or '..' in Path(entry[2]).parts):
            raise ValueError('invalid MP3 bank split entry')
        result.append((entry[0], entry[2]))
    if not result or bank['start'] != result[0][0]:
        raise ValueError('MP3 bank group start disagrees with its first split')
    return result


def write_parts(packed: bytes, manifest: dict, profile: Path, directory: Path) -> None:
    """Require checked-in splat ranges to match the loader-proven partition."""
    start = manifest['rom_start']
    expected = [(start, 'audio/mp3/index')] + sorted(
        (start + entry['offset'], 'audio/mp3/' + str(Path(entry['file']).with_suffix('')))
        for entry in manifest['streams'] + manifest['padding'])
    splits = layout_bins(profile)
    if splits != expected or len(packed) != manifest['rom_end'] - start:
        raise ValueError('US YAML MP3 splits disagree with the reviewed bank boundaries')
    for (begin, name), end in zip(splits, [p[0] for p in splits[1:]] + [manifest['rom_end']]):
        path = directory / (name + '.bin')
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(packed[begin - start:end - start])


if __name__ == '__main__':
    import sys
    profile = mp3_assets.ROOT / 'config/profiles/us.yaml'
    if sys.argv[1:] == ['list-bins']:
        print(' '.join('assets/' + name + '.bin' for _, name in layout_bins(profile)))
    elif sys.argv[1:] == ['build-parts']:
        root = mp3_assets.ROOT
        inputs = root / 'build/assets/mp3-bank/us'
        packed, _ = build_bank(inputs, root / 'build/us/audio/asset_bank_16.bin')
        manifest = json.loads((inputs / 'manifest.json').read_text())
        write_parts(packed, manifest, profile, root / 'build/us/audio/parts')
        print(f'Built {len(layout_bins(profile))} MP3 bank split inputs from US YAML')
    else:
        raise SystemExit('Use list-bins or build-parts')
