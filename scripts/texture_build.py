"""Rebuild reviewed flat textures from PNGs, including their RZIP bytes."""
from __future__ import annotations

import hashlib
import functools
import json
import re
import struct
import subprocess
import tempfile
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
ENCODER_CONTRACT = Path('config/texture_encoders.us.json')
ENCODERS = {
    'zlib': {'format': 'rzip-raw-deflate', 'level': 9,
             'window_bits': -15, 'memory_level': 8, 'strategy': 0},
    'gzip': {'format': 'gzip-raw-deflate', 'level': 9,
             'implementation': 'GNU gzip 1.12'},
}


def reviewed_encoders(root: Path, selected: set[int], rom_sha1: str) -> dict[int, dict]:
    """Encoder choices are committed evidence, never inferred from this runtime."""
    document = json.loads((root / ENCODER_CONTRACT).read_text())
    choices = document.get('encoders')
    if (document.get('schema_version') != 1 or document.get('profile') != 'us'
            or document.get('rom_sha1') != rom_sha1 or not isinstance(choices, dict)
            or set(choices) != {f'{index:04d}' for index in selected}
            or any(not isinstance(choice, str) or choice not in ENCODERS
                   for choice in choices.values())):
        raise ValueError('committed texture encoder contract differs from selected US textures/ROM')
    return {int(index): dict(ENCODERS[choice]) for index, choice in choices.items()}


def part_name(index: int) -> str:
    return f'flat/textures/{index:04d}'


def input_directory(index: int, expected: dict | None = None) -> Path:
    if expected and expected.get('source_contract', {}).get('identity') == 'runtime-resource':
        return INPUT_DIRECTORY / 'runtime' / f'{index:04d}'
    return INPUT_DIRECTORY / f'{index:04d}'


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


def describe_texture(rom: bytes, texture: texture_assets.TextureAsset, *, encoder: dict,
                     rom_sha1: str | None = None,
                     contract: dict | None = None) -> dict:
    if encoder not in ENCODERS.values():
        raise ValueError('unsupported reviewed texture encoder')
    expected = {'schema_version': 1, 'profile': 'us', 'flat_index': texture.flat_index,
            'rom_sha1': rom_sha1 or hashlib.sha1(rom).hexdigest(),
            'rom_start': texture.rom_start, 'rom_end': texture.rom_end,
            'decoded_size': len(texture.payload),
            'original_decoded_sha256': sha256(texture.payload),
            'original_stored_sha256': sha256(rom[texture.rom_start:texture.rom_end]),
            'row_layout': ('linear' if texture.flat_index in texture_assets.LINEAR_FLAT_INDICES
                           else 'tmem-odd-row-32bit-swap'), 'file': f'{texture.flat_index:04d}.ci4.png',
            'encoder': dict(encoder)}
    if contract is not None:
        expected.update(source_contract=contract, row_layout=contract['row_layout'],
                        file=f"{texture.flat_index:04d}.{contract['format']}.png")
        if 'levels' in contract:
            expected['schema_version'] = 4 if contract.get('mixed_detail') else (3 if 'zero_alignment' in contract else 2)
            expected['files'] = [f"{texture.flat_index:04d}.level-{level['level']}.{level.get('format', contract['format'])}.png"
                                 for level in contract['levels']]
            del expected['file']
    return expected


@functools.lru_cache(maxsize=1)
def require_gnu_gzip() -> None:
    version = subprocess.check_output(['gzip', '--version'], text=True).splitlines()[0]
    if version != 'gzip 1.12':
        raise ValueError('texture reconstruction requires GNU gzip 1.12; use ./conker texture-assets build')


def encode_payload(payload: bytes, expected: dict) -> bytes:
    if expected['encoder'] == ENCODERS['zlib']:
        return rzip_pack.encode_rzip_chunk(payload)
    if expected['encoder'] != ENCODERS['gzip']:
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
        if fmt == 'rgba16':
            codec = texture_rgba16.decode_png if decode else texture_rgba16.encode_png
            return codec(data, row, width, height, source_origin=origin)
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
        for index, (texture, contract) in texture_catalog.load_extended(
                root, rom, excluded_indices=by_index).items():
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
    encoders = reviewed_encoders(root, requested, digest)
    return rom, [(describe_texture(rom, t, encoder=encoders[t.flat_index], rom_sha1=digest,
                                  contract=contracts.get(t.flat_index)), t) for t in selected]


def initialize_inputs(directory: Path, expected: dict, payload: bytes) -> None:
    if directory.exists():
        raise ValueError('texture inputs exist without a manifest; refusing to overwrite them')
    images, palette_size = source_images(expected)
    padding = alignment_padding(expected, sum(image[3] for image in images))
    if padding and payload[len(payload) - palette_size - len(padding):len(payload) - palette_size] != padding:
        raise ValueError('texture alignment bytes are not zero')
    palette = payload[-palette_size:] if palette_size else b''
    encoded = [(name, source_png(payload[offset:offset + size] +
                                (palette if palette_size and plane['source_contract']['format'] in ('ci4', 'ci8') else b''), plane))
               for name, plane, offset, size in images]
    files = dict(encoded)
    files['manifest.json'] = (json.dumps(expected, indent=2) + '\n').encode()
    publish_inputs(directory, files)


def publish_inputs(directory: Path, files: dict[str, bytes]) -> None:
    """Publish a complete bundle; interruption cannot create a partial destination."""
    if directory.exists():
        raise ValueError('texture input directory already exists; refusing to overwrite it')
    directory.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix=f'.{directory.name}.staging-',
                                     dir=directory.parent) as temporary:
        staged = Path(temporary) / 'bundle'
        staged.mkdir()
        for name, data in files.items():
            (staged / name).write_bytes(data)
        if directory.exists():
            raise ValueError('texture input directory appeared during initialization')
        staged.rename(directory)


def migrate_legacy_inputs(root: Path, expected: dict) -> None:
    """Move the pilot out of the shared parent without losing editable bytes.

    Publish the full copy first. Interrupted removal of the old files resumes
    only when each remaining file is identical to its canonical counterpart.
    """
    legacy = root / INPUT_DIRECTORY
    destination = root / input_directory(1063, expected)
    names = ['manifest.json'] + [image[0] for image in source_images(expected)[0]]
    remaining = [name for name in names if (legacy / name).exists()]
    if not remaining:
        return
    if not destination.exists():
        # Refuse partial old bundles and preserve all their bytes for recovery.
        before = input_hashes(legacy, expected)
        files = {name: (legacy / name).read_bytes() for name in names}
        if {name: sha256(data) for name, data in files.items()} != before:
            raise ValueError('legacy texture inputs changed during migration')
        publish_inputs(destination, files)
    input_hashes(destination, expected)
    # Check every remaining file before removing any, including conflicting PNGs.
    for name in remaining:
        if (legacy / name).read_bytes() != (destination / name).read_bytes():
            raise ValueError('legacy texture inputs conflict with migrated 1063 bundle')
    for name in remaining:
        (legacy / name).unlink()


def alignment_padding(expected: dict, pixel_size: int) -> bytes:
    """Regenerate only explicitly verified zero alignment, never an opaque tail."""
    padding = expected.get('source_contract', {}).get('zero_alignment')
    if padding is None:
        if expected['schema_version'] == 3:
            raise ValueError('aligned texture source lacks zero alignment')
        return b''
    boundary = 128 if expected['source_contract']['format'] == 'rgba32' else 64
    if (expected['schema_version'] not in (3, 4) or padding['alignment'] != boundary
            or padding['offset'] != pixel_size or not 0 < padding['size'] < boundary
            or pixel_size + padding['size'] != (pixel_size + boundary - 1) // boundary * boundary):
        raise ValueError('invalid texture zero alignment contract')
    return bytes(padding['size'])


def source_images(expected: dict) -> tuple[list[tuple[str, dict, int, int]], int]:
    """Return complete image planes; all shared palette bytes are PNG sources."""
    if expected['schema_version'] == 1:
        return [(expected['file'], expected, 0, expected['decoded_size'])], 0
    if expected['schema_version'] not in (2, 3, 4):
        raise ValueError('unsupported texture source schema')
    contract = expected['source_contract']
    levels, names, palette_size = contract['levels'], expected['files'], contract['palette_size']
    fmt = contract['format']
    depths = {'ci4': 4, 'ci8': 8, 'rgba16': 16, 'rgba32': 32,
              'ia4': 4, 'ia8': 8, 'ia16': 16, 'i4': 4, 'i8': 8}
    mixed = expected['schema_version'] == 4
    if (not 1 <= len(levels) <= 6 or len(names) != len(levels) or len(set(names)) != len(names)
            or any(Path(name).name != name for name in names)
            or palette_size != {'ci4': 32, 'ci8': 512}.get(fmt, 0)):
        raise ValueError('invalid layered texture source contract')
    detail_format = {'ci4': 'ia4', 'ci8': 'ia4', 'rgba16': 'i4'}.get(fmt)
    if mixed and (not contract.get('mixed_detail') or detail_format is None or len(levels) < 2
                  or (fmt == 'rgba16' and (len(levels) != 2
                      or any((level['width'], level['height']) != (contract['width'], contract['height'])
                             for level in levels)))):
        raise ValueError('invalid mixed detail source contract')
    images, cursor = [], 0
    for index, (name, level) in enumerate(zip(names, levels)):
        width, height, size = level['width'], level['height'], level['bytes']
        plane_format = level.get('format', fmt)
        if (plane_format not in depths or (not mixed and plane_format != fmt)
                or (mixed and (plane_format != (detail_format if index == len(levels) - 1 else fmt)
                               or level.get('role') != ('detail' if index == len(levels) - 1 else 'mip')))):
            raise ValueError('invalid texture plane format or role')
        bits = depths[plane_format]
        if (level['level'] != index or level['offset'] != cursor or width <= 0 or height <= 0
                or width * bits % 8 or size != width * bits // 8 * height):
            raise ValueError('layered texture images do not cover contiguous storage')
        plane = {**expected, 'source_contract': {**contract, 'format': plane_format,
                                                'width': width, 'height': height}}
        images.append((name, plane, cursor, size))
        cursor += size
    if cursor + len(alignment_padding(expected, cursor)) + palette_size != expected['decoded_size']:
        raise ValueError('layered texture images do not cover the entire payload')
    return images, palette_size


def input_hashes(directory: Path, expected: dict) -> dict[str, str]:
    if json.loads((directory / 'manifest.json').read_text()) != expected:
        raise ValueError('texture manifest differs from the reviewed ROM contract')
    images, _ = source_images(expected)
    return {name: sha256((directory / name).read_bytes())
            for name in ['manifest.json'] + [image[0] for image in images]}


def packed_texture(directory: Path, expected: dict) -> tuple[bytes, dict[str, str]]:
    """Encode current PNG pixels, never copy original compressed bytes."""
    before = input_hashes(directory, expected)
    images, palette_size = source_images(expected)
    planes, palette = [], None
    for name, plane, _, size in images:
        decoded = source_png((directory / name).read_bytes(), plane, decode=True)
        plane_palette = palette_size if palette_size and plane['source_contract']['format'] in ('ci4', 'ci8') else 0
        if len(decoded) != size + plane_palette:
            raise ValueError('texture image has an unexpected decoded size')
        if plane_palette:
            current = decoded[-plane_palette:]
            if palette is not None and current != palette:
                raise ValueError('texture levels disagree on the shared palette')
            palette = current
        planes.append(decoded[:size])
    pixels = b''.join(planes)
    payload = pixels + alignment_padding(expected, len(pixels)) + (palette or b'')
    if (len(payload) != expected['decoded_size']
            or sha256(payload) != expected['original_decoded_sha256']):
        raise ValueError('texture PNG no longer reconstructs the original payload')
    packed = encode_payload(payload, expected)
    if len(packed) != expected['rom_end'] - expected['rom_start']:
        raise ValueError(f"texture {expected['flat_index']}: reviewed encoder output differs "
                         'from the fixed compressed extent; use the pinned toolchain')
    if sha256(packed) != expected['original_stored_sha256']:
        raise ValueError(f"texture {expected['flat_index']}: reviewed encoder output differs "
                         'from the original RZIP bytes; use the pinned toolchain')
    if before != input_hashes(directory, expected):
        raise ValueError('texture inputs changed during packing')
    return packed, before


def build_parts(root: Path = ROOT) -> dict:
    rom, selected = reviewed_textures(root)
    candidates = []
    for expected, texture in selected:
        if texture.flat_index == 1063:
            migrate_legacy_inputs(root, expected)
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
