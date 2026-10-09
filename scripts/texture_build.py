"""Rebuild reviewed flat textures from PNGs, including their RZIP bytes."""
from __future__ import annotations

import hashlib
import functools
import json
import re
import struct
import subprocess
import zlib
from pathlib import Path

try:
    from scripts import texture_assets, texture_catalog, texture_rgba16, texture_native, rzip_pack
    from scripts.build_files import write_if_changed
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import texture_assets
    import texture_catalog
    import texture_rgba16
    import texture_native
    import rzip_pack
    from build_files import write_if_changed
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
INPUT_DIRECTORY = Path('build/assets/texture-build/us')


def part_name(index: int) -> str:
    return f'flat/textures/{index:04d}'


def input_directory(index: int, expected: dict | None = None) -> Path:
    if expected and expected.get('source_contract', {}).get('identity') == 'runtime-resource':
        return INPUT_DIRECTORY / 'runtime' / f'{index:04d}'
    # Preserve the pilot's existing input bundle, including any local changes.
    return INPUT_DIRECTORY if index == 1063 else INPUT_DIRECTORY / f'{index:04d}'


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def layout_bins(profile: Path, *, configuration: dict | None = None) -> tuple[list[tuple[int, str]], int]:
    segments = (load_profile(profile) if configuration is None else configuration)['segments']
    index = next((i for i, s in enumerate(segments)
                  if isinstance(s, dict) and s.get('name') == 'assets_flat_rzip'), None)
    if index is None:
        raise ValueError(f'{profile}: missing required asset group: assets_flat_rzip')
    group = segments[index]
    following = segments[index + 1]
    end = following['start'] if isinstance(following, dict) else following[0]
    if group['type'] != 'group' or group.get('align') != 1 or group.get('subalign') != 1:
        raise ValueError('flat textures must use a byte-aligned YAML group')
    rows = group['subsegments']
    if (not rows or any(len(r) != 3 or r[1] != 'bin' or not r[2].startswith('flat/')
                        or '..' in Path(r[2]).parts for r in rows)
            or rows[0][0] != group['start'] or len({r[2] for r in rows}) != len(rows)
            or any(a[0] >= b[0] for a, b in zip(rows, rows[1:] + [[end]]))):
        raise ValueError('invalid flat texture YAML partition')
    return [(r[0], r[2]) for r in rows], end


def describe_texture(rom: bytes, texture: texture_assets.TextureAsset, *, rom_sha1: str | None = None,
                     contract: dict | None = None) -> dict:
    expected = {'schema_version': 1, 'profile': 'us', 'flat_index': texture.flat_index,
            'rom_sha1': rom_sha1 or hashlib.sha1(rom).hexdigest(),
            'rom_start': texture.rom_start, 'rom_end': texture.rom_end,
            'decoded_size': len(texture.payload),
            'original_decoded_sha256': sha256(texture.payload),
            'original_stored_sha256': sha256(rom[texture.rom_start:texture.rom_end]),
            'row_layout': ('linear' if texture.flat_index in texture_assets.LINEAR_FLAT_INDICES
                           else 'tmem-odd-row-32bit-swap'), 'file': f'{texture.flat_index:04d}.ci4.png',
            'encoder': {'format': 'rzip-raw-deflate', 'level': 9,
                        'window_bits': -15, 'memory_level': 8, 'strategy': 0}}
    if contract is not None:
        expected.update(source_contract=contract, row_layout=contract['row_layout'],
                        file=f"{texture.flat_index:04d}.{contract['format']}.png")
    if rzip_pack.encode_rzip_chunk(texture.payload) != rom[texture.rom_start:texture.rom_end]:
        expected['encoder'] = {'format': 'gzip-raw-deflate', 'level': 9,
                               'implementation': 'GNU gzip 1.12'}
    return expected


@functools.lru_cache(maxsize=1)
def require_gnu_gzip() -> None:
    version = subprocess.check_output(['gzip', '--version'], text=True).splitlines()[0]
    if version != 'gzip 1.12':
        raise ValueError('texture reconstruction requires GNU gzip 1.12; use ./conker texture-assets build')


def encode_payload(payload: bytes, expected: dict) -> bytes:
    if expected['encoder']['format'] == 'rzip-raw-deflate':
        return rzip_pack.encode_rzip_chunk(payload)
    if expected['encoder'] != {'format': 'gzip-raw-deflate', 'level': 9,
                               'implementation': 'GNU gzip 1.12'}:
        raise ValueError('unsupported texture encoder contract')
    require_gnu_gzip()
    gz = subprocess.run(['gzip', '-n', '-9', '-c'], input=payload,
                        stdout=subprocess.PIPE, check=True).stdout
    # GNU -n emits a fixed ten-byte header with no optional fields. Retain only
    # freshly encoded DEFLATE, not the gzip wrapper or any original ROM bytes.
    if (len(gz) < 18 or gz[:8] != bytes.fromhex('1f8b080000000000')
            or struct.unpack('<II', gz[-8:]) != (zlib.crc32(payload), len(payload) & 0xffffffff)):
        raise ValueError('unexpected GNU gzip wrapper or checksum')
    packed = struct.pack('>I', len(payload)) + gz[10:-8]
    decoded = rzip_pack.decode_rzip_chunk(packed)
    if decoded.data != payload or decoded.consumed != len(packed):
        raise ValueError('GNU gzip texture output did not round-trip')
    return packed


def source_png(data: bytes, expected: dict, *, decode: bool = False) -> bytes:
    contract = expected.get('source_contract', {'format': 'ci4', 'width': 64, 'height': 64})
    fmt, width, height = contract['format'], contract['width'], contract['height']
    row = expected['row_layout']
    origin = contract.get('source_origin', 'bottom-left')
    if origin == 'top-left':
        if decode:
            pixels = texture_assets.decode_rgba_png_pixels(data, width, height)
            linear = texture_native.rgba_to_payload(pixels, fmt)
            return texture_native.convert_row_layout(linear, row, fmt, width, height)
        linear = texture_native.convert_row_layout(data, row, fmt, width, height)
        return texture_assets.encode_rgba_png(
            width, height, texture_native.payload_to_rgba(linear, fmt))
    if origin != 'bottom-left':
        raise ValueError('unsupported texture source origin')
    if fmt == 'ci4':
        codec = texture_assets.decode_indexed_png if decode else texture_assets.encode_indexed_png
    elif fmt == 'ci8':
        codec = texture_assets.decode_ci8_png if decode else texture_assets.encode_ci8_png
    elif fmt == 'rgba16':
        codec = texture_rgba16.decode_png if decode else texture_rgba16.encode_png
    else:
        codec = texture_native.decode_png if decode else texture_native.encode_png
        return codec(data, fmt, row, width, height)
    return codec(data, row, width, height)


def partition(layout: dict, textures: list[texture_assets.TextureAsset]) -> list[tuple[int, str]]:
    """Count each stored byte once; unselected intervals remain raw backing."""
    rows = []
    cursor = layout['flat_assets_start']
    for texture in sorted(textures, key=lambda t: t.rom_start):
        if not cursor <= texture.rom_start < texture.rom_end <= layout['flat_assets_end']:
            raise ValueError('overlapping or out-of-range texture storage')
        if cursor < texture.rom_start:
            rows.append((cursor, f'flat/raw/{cursor:08X}'))
        rows.append((texture.rom_start, part_name(texture.flat_index)))
        cursor = texture.rom_end
    if cursor < layout['flat_assets_end']:
        rows.append((cursor, f'flat/raw/{cursor:08X}'))
    return rows


def reviewed_textures(root: Path = ROOT) -> tuple[bytes, list[tuple[dict, texture_assets.TextureAsset]]]:
    _, rom, _, layout, textures = texture_assets.load_profile_textures(
        'us', root / 'roms/baserom.us.z64')
    rows, end = layout_bins(root / 'config/profiles/us.yaml')
    by_index = {t.flat_index: t for t in textures}
    contracts = {}
    names = [name for _, name in rows if name.startswith('flat/textures/')]
    if any(re.fullmatch(r'flat/textures/([0-9]{4})', name) is None for name in names):
        raise ValueError('texture selection differs from proven RZIP boundaries/family')
    requested = {int(name.rsplit('/', 1)[1]) for name in names}
    if requested - by_index.keys():
        for index, (texture, contract) in texture_catalog.load_extended(root, rom).items():
            if index in by_index:
                if by_index[index] != texture:
                    raise ValueError('extended texture conflicts with the square family')
                continue
            by_index[index] = texture
            contracts[index] = contract
    selected = []
    for _, name in rows:
        if name.startswith('flat/textures/'):
            match = re.fullmatch(r'flat/textures/([0-9]{4})', name)
            if not match or int(match[1]) not in by_index:
                raise ValueError('texture selection differs from proven RZIP boundaries/family')
            selected.append(by_index[int(match[1])])
    if (not selected or len({t.flat_index for t in selected}) != len(selected)
            or rows != partition(layout, selected) or end != layout['flat_assets_end']):
        raise ValueError('flat texture YAML splits differ from the verified RZIP boundaries')
    digest = hashlib.sha1(rom).hexdigest()
    return rom, [(describe_texture(rom, t, rom_sha1=digest,
                                  contract=contracts.get(t.flat_index)), t) for t in selected]


def initialize_inputs(directory: Path, expected: dict, payload: bytes) -> None:
    if directory.exists():
        raise ValueError('texture inputs exist without a manifest; refusing to overwrite them')
    directory.mkdir(parents=True)
    (directory / expected['file']).write_bytes(
        source_png(payload, expected))
    (directory / 'manifest.json').write_text(json.dumps(expected, indent=2) + '\n')


def input_hashes(directory: Path, expected: dict) -> dict[str, str]:
    if json.loads((directory / 'manifest.json').read_text()) != expected:
        raise ValueError('texture manifest differs from the reviewed ROM contract')
    return {name: sha256((directory / name).read_bytes())
            for name in ('manifest.json', expected['file'])}


def packed_texture(directory: Path, expected: dict) -> tuple[bytes, dict[str, str]]:
    """Encode current PNG pixels, never copy original compressed bytes."""
    before = input_hashes(directory, expected)
    payload = source_png((directory / expected['file']).read_bytes(), expected, decode=True)
    if (len(payload) != expected['decoded_size']
            or sha256(payload) != expected['original_decoded_sha256']):
        raise ValueError('texture PNG no longer reconstructs the original payload')
    packed = encode_payload(payload, expected)
    if len(packed) != expected['rom_end'] - expected['rom_start']:
        raise ValueError('texture encoder changes the fixed compressed extent')
    if sha256(packed) != expected['original_stored_sha256']:
        raise ValueError('texture encoder does not reproduce the original RZIP bytes')
    if before != input_hashes(directory, expected):
        raise ValueError('texture inputs changed during packing')
    return packed, before


def build_parts(root: Path = ROOT) -> dict:
    rom, selected = reviewed_textures(root)
    # Initialize the legacy parent bundle first even if future selections include
    # earlier indices whose new child directories would create that parent.
    for expected, texture in selected:
        if texture.flat_index == 1063 and not (root / INPUT_DIRECTORY / 'manifest.json').is_file():
            initialize_inputs(root / INPUT_DIRECTORY, expected, texture.payload)
    candidates = []
    for expected, texture in selected:
        directory = root / input_directory(texture.flat_index, expected)
        if not (directory / 'manifest.json').is_file():
            initialize_inputs(directory, expected, texture.payload)
        packed, hashes = packed_texture(directory, expected)
        evidence = {**expected, 'source_inputs': hashes, 'sha256': sha256(packed),
                    'matches_original': packed == rom[texture.rom_start:texture.rom_end],
                    'zlib_version': rzip_pack.zlib.ZLIB_RUNTIME_VERSION}
        candidates.append((expected, directory, packed, evidence))
    # Validate the entire batch before replacing any existing linker part.
    for expected, directory, _, evidence in candidates:
        if evidence['source_inputs'] != input_hashes(directory, expected):
            raise ValueError('texture inputs changed during batch packing')
    for expected, _, packed, evidence in candidates:
        index = expected['flat_index']
        write_if_changed(root / 'build/us/textures/parts' / (part_name(index) + '.bin'), packed)
        write_if_changed(root / f'build/us/textures/{index:04d}.json',
                         (json.dumps(evidence, indent=2) + '\n').encode())
    result = {'texture_count': len(candidates), 'stored_bytes': sum(len(p) for _, _, p, _ in candidates),
              'matches_original': all(e['matches_original'] for _, _, _, e in candidates),
              'textures': [e for _, _, _, e in candidates]}
    write_if_changed(root / 'build/us/textures/batch.json', (json.dumps(result, indent=2) + '\n').encode())
    return result


if __name__ == '__main__':
    import sys
    if sys.argv[1:] != ['build-parts']:
        raise SystemExit('Use build-parts')
    proof = build_parts()
    print(f"Built {proof['texture_count']} textures: {proof['stored_bytes']} RZIP bytes; "
          f"matches original: {proof['matches_original']}")
