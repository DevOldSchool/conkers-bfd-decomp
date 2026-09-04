#!/usr/bin/env python3
"""Extract and byte-identically rebuild loader-proven US CI4 texture families."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
import zlib
from dataclasses import dataclass
from pathlib import Path
from typing import Any

try:
    from scripts.rzip_archive import (
        decode_rzip_chunk,
        iter_flat_rzip_entries,
        normalize_rom,
        parse_asset_banks,
        parse_asset_entries,
        parse_game_archive,
    )
    from scripts.rzip_extract import (
        ROOT,
        display_path,
        load_layout,
        manifest_source,
        prepare_output,
    )
except ModuleNotFoundError:
    from rzip_archive import (  # type: ignore[no-redef]
        decode_rzip_chunk,
        iter_flat_rzip_entries,
        normalize_rom,
        parse_asset_banks,
        parse_asset_entries,
        parse_game_archive,
    )
    from rzip_extract import (  # type: ignore[no-redef]
        ROOT,
        display_path,
        load_layout,
        manifest_source,
        prepare_output,
    )


WIDTH = 64
HEIGHT = 64
PIXEL_SIZE = WIDTH * HEIGHT // 2
PALETTE_COLORS = 16
PALETTE_SIZE = PALETTE_COLORS * 2
PAYLOAD_SIZE = PIXEL_SIZE + PALETTE_SIZE
EXPECTED_US_COUNT = 704
PNG_SIGNATURE = b"\x89PNG\r\n\x1a\n"
ROW_LAYOUT_TMEM = "tmem-odd-row-32bit-swap"
ROW_LAYOUT_LINEAR = "linear"
ROW_LAYOUTS = frozenset((ROW_LAYOUT_TMEM, ROW_LAYOUT_LINEAR))
SOURCE_ORIGIN = "bottom-left"
PNG_ORIGIN = "top-left"
SQUARE_FAMILY = "flat-ci4-64x64-rgba5551"
RECTANGULAR_FAMILY = "flat-ci4-rectangular-proven-rgba5551"
TILED_VIEWS_FAMILY = "flat-tiled-views-mixed-ci-rgba5551"
SQUARE_FAMILY_NAME = "64x64"
RECTANGULAR_FAMILY_NAME = "1056-proven"
TILED_VIEWS_FAMILY_NAME = "tiled-views"

# These two particle textures are passed to the 64-pixel sprite path in their
# linear source order. The other 2,080-byte entries use the TMEM-ready ordering
# where the two 32-bit halves of each 64-bit word are exchanged on odd rows.
LINEAR_FLAT_INDICES = frozenset((1296, 1297))

RECTANGULAR_PAYLOAD_SIZE = 1056
RECTANGULAR_PIXEL_SIZE = 1024
DIRECT_TEXTURE_IMAGE = 0xFD500000
DIRECT_PALETTE_IMAGE = 0xFD100000
CI_FORMAT = 2
CI4_SIZE = 0
END_DISPLAY_LIST = 0xDF
BRANCH_DISPLAY_LIST = 0xDE

# func_15000AD0 selects one of seven flat-archive base indices through this
# pointer table, then preloads 0x168 consecutive entries with func_1510D0EC.
# These addresses are verified against the US game code before the table is
# used; the evidence classifies indirect resource references, not image shape.
PRELOAD_POINTER_TABLE_VRAM = 0x800891BC
PRELOAD_GROUP_COUNT = 7
PRELOAD_GROUP_LENGTH = 0x168
PRELOAD_CODE_SIGNATURES = {
    0x15000BF4: 0x3C118009,  # lui s1, 0x8009
    0x15000BF8: 0x263191BC,  # addiu s1, s1, 0x91BC
    0x15000C2C: 0x0D44343B,  # jal func_1510D0EC
    0x15000C30: 0x03102021,  # addu a0, t8, s0
    0x15000C38: 0x24010168,  # addiu at, zero, 0x168
}

# func_15111AF4 selects five view bases from each record referenced by the same
# pointer table. func_15110CFC then walks a 360x360 image in 60x30 visible
# tiles: six columns by twelve rows, with flat indices stored column-major.
# Its two render configurations distinguish 2,560-byte CI8 tiles from
# 1,056-byte CI4 tiles. The latter use 64x32 storage, a palette at +0x400,
# and a 16-entry TLUT. These signatures keep that interpretation tied to the
# verified US renderer rather than payload size alone.
TILED_VIEW_BASE_COUNT = 5
TILED_VIEW_WIDTH = 360
TILED_VIEW_HEIGHT = 360
TILED_VISIBLE_WIDTH = 60
TILED_VISIBLE_HEIGHT = 30
TILED_STORAGE_WIDTH = 64
TILED_STORAGE_HEIGHT = 32
TILED_EDGE_STORAGE_WIDTH = 32
TILED_EDGE_VISIBLE_WIDTH = 30
TILED_EDGE_CI8_SIZE = TILED_EDGE_STORAGE_WIDTH * TILED_STORAGE_HEIGHT + 256 * 2
TILED_COLUMNS = TILED_VIEW_WIDTH // TILED_VISIBLE_WIDTH
TILED_ROWS = TILED_VIEW_HEIGHT // TILED_VISIBLE_HEIGHT
TILED_ENTRIES_PER_VIEW = TILED_COLUMNS * TILED_ROWS
TILED_STREAM_PHASE = 2
TILED_RENDER_CODE_SIGNATURES = {
    0x15111F90: 0x3C188009,  # lui t8, 0x8009
    0x15111FAC: 0x8F1891BC,  # lw t8, 0x91BC(t8)
    0x1511221C: 0x00037880,  # sll t7, v1, 2
    0x15112224: 0x8DC60000,  # lw a2, 0(t6): selected view base
    0x15112244: 0x240E003C,  # addiu t6, zero, 60
    0x1511226C: 0x2418001E,  # addiu t8, zero, 30
    0x151122E8: 0x0D44433F,  # jal func_15110CFC
    0x15111164: 0x8FB90178,  # load selected view base
    0x15111168: 0x01F8001B,  # divide height by tile height
    0x1511118C: 0x01197821,  # add column-major tile offset to base
    0x15111198: 0x01F82021,  # add row offset to flat index
    0x15111204: 0x0D44343B,  # jal func_1510D0EC
    0x15111540: 0x8FAE01C4,  # load palette-offset table
    0x15111550: 0x87380000,  # selected palette offset
    0x15111578: 0x3C18F000,  # load TLUT command
    0x1511158C: 0x01C57821,  # index TLUT-size table
    0x15111590: 0x91F80000,  # selected TLUT size
    # A conditional renderer path substitutes a 3x2 block beginning at flat
    # index 0x1673.  This is a runtime reference independent of the five
    # ordinary view bases and accounts for the gap immediately before group 1.
    0x151111C4: 0x2B010004,  # outer tile coordinate >= 4
    0x151111CC: 0x2B010007,  # outer tile coordinate < 7
    0x151111D4: 0x29C10002,  # inner tile coordinate >= 2
    0x151111DC: 0x29C10004,  # inner tile coordinate < 4
    0x151111E4: 0x000EC880,  # inner * 4
    0x151111E8: 0x032EC823,  # inner * 3
    0x151111EC: 0x03387821,  # inner * 3 + outer
    0x151111F0: 0x3C190000,  # high half of flat index 0x1673
    0x151111F4: 0x27391673,  # low half of flat index 0x1673
    0x151111F8: 0x25EEFFF6,  # normalize the 3x2 coordinates
    0x151111FC: 0x01D92021,  # select the replacement flat index
}
TILED_OVERRIDE_FIRST_INDEX = 0x1673
TILED_OVERRIDE_ENTRY_COUNT = 6
TILED_RENDER_DATA_WORDS = {
    0x800891EC: 0x01040000,
    0x800891F0: 0x01020000,
    0x800891F4: 0x08000400,  # CI8 +0x800; CI4 +0x400
    0x800891F8: 0xFF0F0000,  # 256-entry and 16-entry TLUT selectors
    0x800891FC: 0x00010000,
}


@dataclass(frozen=True)
class TextureAsset:
    flat_index: int
    rom_start: int
    rom_end: int
    payload: bytes


@dataclass(frozen=True)
class TextureReference:
    flat_index: int
    source: str
    offset: int
    width: int | None
    height: int | None
    palette_at_payload_end: bool
    tile_command: int | None
    tile_format: int | None
    tile_size: int | None
    load_block_texels: int | None
    palette_reference_mode: int | None
    palette_entries: int | None


def validate_payload(
    payload: bytes, width: int = WIDTH, height: int = HEIGHT
) -> None:
    expected_size = width * height // 2 + PALETTE_SIZE
    if len(payload) != expected_size:
        raise ValueError(
            f"CI4 texture payload is {len(payload)} bytes; expected {expected_size}"
        )


def expand_5bit(value: int) -> int:
    return value * 255 // 31


def reduce_5bit(value: int) -> int:
    reduced = (value * 31 + 127) // 255
    if expand_5bit(reduced) != value:
        raise ValueError("PNG palette color is not exactly representable as RGBA5551")
    return reduced


def png_chunk(kind: bytes, data: bytes) -> bytes:
    checksum = zlib.crc32(kind + data) & 0xFFFFFFFF
    return struct.pack(">I", len(data)) + kind + data + struct.pack(">I", checksum)


def row_layout_for_flat_index(flat_index: int) -> str:
    if flat_index in LINEAR_FLAT_INDICES:
        return ROW_LAYOUT_LINEAR
    return ROW_LAYOUT_TMEM


def convert_row_layout(
    pixels: bytes,
    row_layout: str,
    width: int = WIDTH,
    height: int = HEIGHT,
) -> bytes:
    if row_layout not in ROW_LAYOUTS:
        raise ValueError(f"unsupported CI4 row layout: {row_layout}")
    pixel_size = width * height // 2
    if len(pixels) != pixel_size:
        raise ValueError(
            f"CI4 pixel data is {len(pixels)} bytes; expected {pixel_size}"
        )
    if row_layout == ROW_LAYOUT_LINEAR:
        return pixels

    row_size = width // 2
    converted = bytearray(pixels)
    for row_index in range(1, height, 2):
        row_start = row_index * row_size
        source = pixels[row_start : row_start + row_size]
        converted[row_start : row_start + row_size] = bytes(
            source[column ^ 4] for column in range(row_size)
        )
    return bytes(converted)


def flip_vertical(
    pixels: bytes, width: int = WIDTH, height: int = HEIGHT
) -> bytes:
    pixel_size = width * height // 2
    if len(pixels) != pixel_size:
        raise ValueError(
            f"CI4 pixel data is {len(pixels)} bytes; expected {pixel_size}"
        )
    row_size = width // 2
    return b"".join(
        pixels[offset : offset + row_size]
        for offset in range(pixel_size - row_size, -1, -row_size)
    )


def encode_indexed_png(
    payload: bytes,
    row_layout: str = ROW_LAYOUT_TMEM,
    width: int = WIDTH,
    height: int = HEIGHT,
) -> bytes:
    validate_payload(payload, width, height)
    pixel_size = width * height // 2
    pixels = flip_vertical(
        convert_row_layout(payload[:pixel_size], row_layout, width, height),
        width,
        height,
    )
    palette_words = struct.unpack(f">{PALETTE_COLORS}H", payload[pixel_size:])
    palette = bytearray()
    alpha = bytearray()
    for value in palette_words:
        palette.extend(
            (
                expand_5bit((value >> 11) & 0x1F),
                expand_5bit((value >> 6) & 0x1F),
                expand_5bit((value >> 1) & 0x1F),
            )
        )
        alpha.append(255 if value & 1 else 0)
    rows = b"".join(
        b"\0" + pixels[offset : offset + width // 2]
        for offset in range(0, pixel_size, width // 2)
    )
    header = struct.pack(">IIBBBBB", width, height, 4, 3, 0, 0, 0)
    return (
        PNG_SIGNATURE
        + png_chunk(b"IHDR", header)
        + png_chunk(b"PLTE", bytes(palette))
        + png_chunk(b"tRNS", bytes(alpha))
        + png_chunk(b"IDAT", zlib.compress(rows, level=9))
        + png_chunk(b"IEND", b"")
    )


def validate_ci8_payload(
    payload: bytes, width: int = TILED_STORAGE_WIDTH, height: int = TILED_STORAGE_HEIGHT
) -> None:
    expected_size = width * height + 256 * 2
    if len(payload) != expected_size:
        raise ValueError(
            f"CI8 texture payload is {len(payload)} bytes; expected {expected_size}"
        )


def convert_ci8_row_layout(
    pixels: bytes,
    row_layout: str,
    width: int = TILED_STORAGE_WIDTH,
    height: int = TILED_STORAGE_HEIGHT,
) -> bytes:
    if row_layout not in ROW_LAYOUTS:
        raise ValueError(f"unsupported CI8 row layout: {row_layout}")
    if len(pixels) != width * height:
        raise ValueError(f"CI8 pixel data is {len(pixels)} bytes; expected {width * height}")
    if row_layout == ROW_LAYOUT_LINEAR:
        return pixels
    converted = bytearray(pixels)
    for row_index in range(1, height, 2):
        row_start = row_index * width
        source = pixels[row_start : row_start + width]
        converted[row_start : row_start + width] = bytes(
            source[column ^ 4] for column in range(width)
        )
    return bytes(converted)


def flip_vertical_ci8(
    pixels: bytes,
    width: int = TILED_STORAGE_WIDTH,
    height: int = TILED_STORAGE_HEIGHT,
) -> bytes:
    if len(pixels) != width * height:
        raise ValueError(f"CI8 pixel data is {len(pixels)} bytes; expected {width * height}")
    return b"".join(
        pixels[offset : offset + width]
        for offset in range(width * (height - 1), -1, -width)
    )


def encode_ci8_png(
    payload: bytes,
    row_layout: str = ROW_LAYOUT_TMEM,
    width: int = TILED_STORAGE_WIDTH,
    height: int = TILED_STORAGE_HEIGHT,
) -> bytes:
    validate_ci8_payload(payload, width, height)
    pixel_size = width * height
    pixels = flip_vertical_ci8(
        convert_ci8_row_layout(payload[:pixel_size], row_layout, width, height),
        width,
        height,
    )
    palette_words = struct.unpack(">256H", payload[pixel_size:])
    palette = bytearray()
    alpha = bytearray()
    for value in palette_words:
        palette.extend(
            (
                expand_5bit((value >> 11) & 0x1F),
                expand_5bit((value >> 6) & 0x1F),
                expand_5bit((value >> 1) & 0x1F),
            )
        )
        alpha.append(255 if value & 1 else 0)
    rows = b"".join(
        b"\0" + pixels[offset : offset + width]
        for offset in range(0, pixel_size, width)
    )
    header = struct.pack(">IIBBBBB", width, height, 8, 3, 0, 0, 0)
    return (
        PNG_SIGNATURE
        + png_chunk(b"IHDR", header)
        + png_chunk(b"PLTE", bytes(palette))
        + png_chunk(b"tRNS", bytes(alpha))
        + png_chunk(b"IDAT", zlib.compress(rows, level=9))
        + png_chunk(b"IEND", b"")
    )


def encode_rgba_png(width: int, height: int, pixels: bytes) -> bytes:
    if len(pixels) != width * height * 4:
        raise ValueError("RGBA PNG pixel data has an invalid size")
    rows = b"".join(
        b"\0" + pixels[offset : offset + width * 4]
        for offset in range(0, len(pixels), width * 4)
    )
    header = struct.pack(">IIBBBBB", width, height, 8, 6, 0, 0, 0)
    return (
        PNG_SIGNATURE
        + png_chunk(b"IHDR", header)
        + png_chunk(b"IDAT", zlib.compress(rows, level=9))
        + png_chunk(b"IEND", b"")
    )


def paeth(left: int, above: int, upper_left: int) -> int:
    estimate = left + above - upper_left
    left_distance = abs(estimate - left)
    above_distance = abs(estimate - above)
    upper_left_distance = abs(estimate - upper_left)
    if left_distance <= above_distance and left_distance <= upper_left_distance:
        return left
    if above_distance <= upper_left_distance:
        return above
    return upper_left


def unfilter_rows(
    data: bytes,
    width: int = WIDTH,
    height: int = HEIGHT,
    bytes_per_row: int | None = None,
) -> bytes:
    row_size = bytes_per_row if bytes_per_row is not None else width // 2
    if len(data) != height * (row_size + 1):
        raise ValueError("indexed PNG has an invalid decompressed size")
    output = bytearray()
    previous = bytes(row_size)
    offset = 0
    for _ in range(height):
        filter_type = data[offset]
        encoded = data[offset + 1 : offset + 1 + row_size]
        offset += row_size + 1
        row = bytearray(row_size)
        for column, value in enumerate(encoded):
            left = row[column - 1] if column else 0
            above = previous[column]
            upper_left = previous[column - 1] if column else 0
            if filter_type == 0:
                predictor = 0
            elif filter_type == 1:
                predictor = left
            elif filter_type == 2:
                predictor = above
            elif filter_type == 3:
                predictor = (left + above) // 2
            elif filter_type == 4:
                predictor = paeth(left, above, upper_left)
            else:
                raise ValueError(f"indexed PNG uses unsupported filter {filter_type}")
            row[column] = (value + predictor) & 0xFF
        output.extend(row)
        previous = bytes(row)
    return bytes(output)


def decode_indexed_png(
    data: bytes,
    row_layout: str = ROW_LAYOUT_TMEM,
    width: int = WIDTH,
    height: int = HEIGHT,
) -> bytes:
    expected_width = width
    expected_height = height
    if not data.startswith(PNG_SIGNATURE):
        raise ValueError("texture file is not a PNG")
    chunks: dict[bytes, list[bytes]] = {}
    offset = len(PNG_SIGNATURE)
    while offset < len(data):
        if offset + 12 > len(data):
            raise ValueError("PNG chunk is truncated")
        length = struct.unpack_from(">I", data, offset)[0]
        kind = data[offset + 4 : offset + 8]
        end = offset + 12 + length
        if end > len(data):
            raise ValueError("PNG chunk payload is truncated")
        payload = data[offset + 8 : offset + 8 + length]
        expected_crc = struct.unpack_from(">I", data, offset + 8 + length)[0]
        if zlib.crc32(kind + payload) & 0xFFFFFFFF != expected_crc:
            raise ValueError("PNG chunk CRC is invalid")
        chunks.setdefault(kind, []).append(payload)
        offset = end
        if kind == b"IEND":
            break
    if offset != len(data):
        raise ValueError("PNG has trailing data")
    if len(chunks.get(b"IHDR", [])) != 1:
        raise ValueError("PNG must contain exactly one IHDR")
    header = chunks[b"IHDR"][0]
    if len(header) != 13:
        raise ValueError("PNG IHDR has an invalid size")
    png_width, png_height, depth, color_type, compression, filtering, interlace = struct.unpack(
        ">IIBBBBB", header
    )
    if (png_width, png_height, depth, color_type) != (
        expected_width,
        expected_height,
        4,
        3,
    ):
        raise ValueError(
            f"texture PNG must be {expected_width}x{expected_height} indexed "
            "color at four bits"
        )
    if compression or filtering or interlace:
        raise ValueError("texture PNG uses unsupported encoding options")
    palette = b"".join(chunks.get(b"PLTE", []))
    alpha = b"".join(chunks.get(b"tRNS", []))
    if len(palette) != PALETTE_COLORS * 3 or len(alpha) != PALETTE_COLORS:
        raise ValueError("texture PNG must contain a 16-color RGBA palette")
    palette_words = []
    for index in range(PALETTE_COLORS):
        red, green, blue = palette[index * 3 : index * 3 + 3]
        if alpha[index] not in (0, 255):
            raise ValueError("PNG palette alpha is not representable as RGBA5551")
        palette_words.append(
            (reduce_5bit(red) << 11)
            | (reduce_5bit(green) << 6)
            | (reduce_5bit(blue) << 1)
            | (1 if alpha[index] else 0)
        )
    try:
        filtered = zlib.decompress(b"".join(chunks[b"IDAT"]))
    except (KeyError, zlib.error) as error:
        raise ValueError("PNG IDAT data is missing or invalid") from error
    pixels = convert_row_layout(
        flip_vertical(
            unfilter_rows(filtered, expected_width, expected_height),
            expected_width,
            expected_height,
        ),
        row_layout,
        expected_width,
        expected_height,
    )
    result = pixels + struct.pack(f">{PALETTE_COLORS}H", *palette_words)
    validate_payload(result, expected_width, expected_height)
    return result


def decode_ci8_png(
    data: bytes,
    row_layout: str = ROW_LAYOUT_TMEM,
    width: int = TILED_STORAGE_WIDTH,
    height: int = TILED_STORAGE_HEIGHT,
) -> bytes:
    if not data.startswith(PNG_SIGNATURE):
        raise ValueError("texture file is not a PNG")
    chunks: dict[bytes, list[bytes]] = {}
    offset = len(PNG_SIGNATURE)
    while offset < len(data):
        if offset + 12 > len(data):
            raise ValueError("PNG chunk is truncated")
        length = struct.unpack_from(">I", data, offset)[0]
        kind = data[offset + 4 : offset + 8]
        end = offset + 12 + length
        if end > len(data):
            raise ValueError("PNG chunk payload is truncated")
        payload = data[offset + 8 : offset + 8 + length]
        expected_crc = struct.unpack_from(">I", data, offset + 8 + length)[0]
        if zlib.crc32(kind + payload) & 0xFFFFFFFF != expected_crc:
            raise ValueError("PNG chunk CRC is invalid")
        chunks.setdefault(kind, []).append(payload)
        offset = end
        if kind == b"IEND":
            break
    if offset != len(data):
        raise ValueError("PNG has trailing data")
    if len(chunks.get(b"IHDR", [])) != 1:
        raise ValueError("PNG must contain exactly one IHDR")
    header = chunks[b"IHDR"][0]
    if len(header) != 13:
        raise ValueError("PNG IHDR has an invalid size")
    png_width, png_height, depth, color_type, compression, filtering, interlace = (
        struct.unpack(">IIBBBBB", header)
    )
    if (png_width, png_height, depth, color_type) != (width, height, 8, 3):
        raise ValueError(
            f"texture PNG must be {width}x{height} indexed color at eight bits"
        )
    if compression or filtering or interlace:
        raise ValueError("texture PNG uses unsupported encoding options")
    palette = b"".join(chunks.get(b"PLTE", []))
    alpha = b"".join(chunks.get(b"tRNS", []))
    if len(palette) != 256 * 3 or len(alpha) != 256:
        raise ValueError("texture PNG must contain a 256-color RGBA palette")
    palette_words = []
    for index in range(256):
        red, green, blue = palette[index * 3 : index * 3 + 3]
        if alpha[index] not in (0, 255):
            raise ValueError("PNG palette alpha is not representable as RGBA5551")
        palette_words.append(
            (reduce_5bit(red) << 11)
            | (reduce_5bit(green) << 6)
            | (reduce_5bit(blue) << 1)
            | (1 if alpha[index] else 0)
        )
    try:
        filtered = zlib.decompress(b"".join(chunks[b"IDAT"]))
    except (KeyError, zlib.error) as error:
        raise ValueError("PNG IDAT data is missing or invalid") from error
    pixels = convert_ci8_row_layout(
        flip_vertical_ci8(
            unfilter_rows(filtered, width, height, bytes_per_row=width),
            width,
            height,
        ),
        row_layout,
        width,
        height,
    )
    result = pixels + struct.pack(">256H", *palette_words)
    validate_ci8_payload(result, width, height)
    return result


def indexed_payload_rgba(
    payload: bytes,
    bit_depth: int,
    row_layout: str = ROW_LAYOUT_TMEM,
    width: int = TILED_STORAGE_WIDTH,
    height: int = TILED_STORAGE_HEIGHT,
) -> bytes:
    if bit_depth == 4:
        validate_payload(payload, width, height)
        pixel_size = width * height // 2
        packed = flip_vertical(
            convert_row_layout(payload[:pixel_size], row_layout, width, height),
            width,
            height,
        )
        indices = bytes(
            value
            for byte in packed
            for value in ((byte >> 4) & 0xF, byte & 0xF)
        )
        palette_count = PALETTE_COLORS
    elif bit_depth == 8:
        validate_ci8_payload(payload, width, height)
        pixel_size = width * height
        indices = flip_vertical_ci8(
            convert_ci8_row_layout(payload[:pixel_size], row_layout, width, height),
            width,
            height,
        )
        palette_count = 256
    else:
        raise ValueError(f"unsupported indexed texture depth: {bit_depth}")
    palette_words = struct.unpack(f">{palette_count}H", payload[pixel_size:])
    colors = [
        bytes(
            (
                expand_5bit((value >> 11) & 0x1F),
                expand_5bit((value >> 6) & 0x1F),
                expand_5bit((value >> 1) & 0x1F),
                255 if value & 1 else 0,
            )
        )
        for value in palette_words
    ]
    return b"".join(colors[index] for index in indices)


def resolve_rom(profile: str, rom_argument: Path | None) -> tuple[Path, dict[str, Any]]:
    if profile != "us":
        raise ValueError("the CI4 texture family is currently proven only for US")
    layout = load_layout(profile)
    default_rom = layout.get("default_rom")
    rom_path = rom_argument or (ROOT / default_rom if default_rom else None)
    if rom_path is None:
        raise ValueError("--rom is required for the US profile")
    if not rom_path.is_absolute():
        rom_path = ROOT / rom_path
    if not rom_path.is_file():
        raise ValueError(f"ROM does not exist: {display_path(rom_path)}")
    return rom_path, layout


def load_profile_textures(
    profile: str, rom_argument: Path | None
) -> tuple[Path, bytes, str, dict[str, Any], list[TextureAsset]]:
    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(f"US normalized ROM SHA-1 mismatch: got {digest}")
    start = layout["flat_assets_start"]
    end = layout["flat_assets_end"]
    textures = [
        TextureAsset(entry.index, start + entry.start, start + entry.end, entry.data)
        for entry in iter_flat_rzip_entries(normalized[start:end])
        if len(entry.data) == PAYLOAD_SIZE
    ]
    if len(textures) != EXPECTED_US_COUNT:
        raise ValueError(
            f"US 64x64 CI4 family has {len(textures)} entries; expected {EXPECTED_US_COUNT}"
        )
    return rom_path, normalized, source_order, layout, textures


def command_words(data: bytes, offset: int) -> tuple[int, int]:
    return struct.unpack_from(">II", data, offset)


def ci4_dimensions_from_tile(command: int) -> tuple[int, int] | None:
    if command >> 24 != 0xF5:
        return None
    image_format = (command >> 21) & 0x7
    image_size = (command >> 19) & 0x3
    line_words = (command >> 9) & 0x1FF
    if image_format != CI_FORMAT or image_size != CI4_SIZE or line_words == 0:
        return None
    width = line_words * 16
    if width == 0 or RECTANGULAR_PIXEL_SIZE * 2 % width:
        return None
    height = RECTANGULAR_PIXEL_SIZE * 2 // width
    if (width, height) not in ((32, 64), (64, 32)):
        return None
    return width, height


def tile_format_and_size(command: int) -> tuple[int, int] | None:
    if command >> 24 != 0xF5:
        return None
    return (command >> 21) & 0x7, (command >> 19) & 0x3


def is_render_tile(command: int, argument: int) -> bool:
    return command >> 24 == 0xF5 and ((argument >> 24) & 0x7) != 7


def tlut_entry_count(command: int, argument: int) -> int | None:
    if command >> 24 != 0xF0:
        return None
    return ((argument >> 14) & 0x3FF) + 1


def word_at_vram(data: bytes, base_vram: int, address: int) -> int:
    offset = address - base_vram
    if offset < 0 or offset + 4 > len(data):
        raise ValueError(f"address 0x{address:X} is outside the decoded game range")
    return struct.unpack_from(">I", data, offset)[0]


def scan_indirect_preload_groups(
    game_code: bytes,
    game_data: bytes,
    layout: dict[str, Any],
    candidate_indices: frozenset[int],
    flat_entry_count: int,
) -> tuple[list[dict[str, Any]], frozenset[int]]:
    """Recover the bounded flat-resource ranges preloaded by func_15000AD0.

    This path establishes that an entry is selected by the runtime flat loader,
    but it does not establish a texture format or dimensions.  The exact US
    call, pointer-table address, and loop bound are checked before any range is
    reported so data that merely resembles an asset index cannot count.
    """

    code_vram = int(layout["game_vram"])
    data_vram = int(layout["game_data_vram"])
    for address, expected in PRELOAD_CODE_SIGNATURES.items():
        actual = word_at_vram(game_code, code_vram, address)
        if actual != expected:
            raise ValueError(
                f"US preload signature at 0x{address:X} is 0x{actual:08X}; "
                f"expected 0x{expected:08X}"
            )

    pointers = [
        word_at_vram(game_data, data_vram, PRELOAD_POINTER_TABLE_VRAM + index * 4)
        for index in range(PRELOAD_GROUP_COUNT)
    ]
    next_word = word_at_vram(
        game_data,
        data_vram,
        PRELOAD_POINTER_TABLE_VRAM + PRELOAD_GROUP_COUNT * 4,
    )
    if not code_vram <= next_word < code_vram + len(game_code):
        raise ValueError("US preload pointer-table boundary is not followed by game code")

    groups = []
    indirect_candidates: set[int] = set()
    for group_index, pointer in enumerate(pointers):
        if not data_vram <= pointer <= data_vram + len(game_data) - 4:
            raise ValueError(
                f"US preload group {group_index} pointer 0x{pointer:X} is outside game data"
            )
        first = word_at_vram(game_data, data_vram, pointer)
        end = first + PRELOAD_GROUP_LENGTH
        if first < 0 or end > flat_entry_count:
            raise ValueError(
                f"US preload group {group_index} range {first}:{end} is outside flat assets"
            )
        candidates = candidate_indices.intersection(range(first, end))
        indirect_candidates.update(candidates)
        groups.append(
            {
                "group_index": group_index,
                "base_pointer": f"0x{pointer:X}",
                "first_flat_index": first,
                "last_flat_index": end - 1,
                "entry_count": PRELOAD_GROUP_LENGTH,
                "candidate_count": len(candidates),
            }
        )
    return groups, frozenset(indirect_candidates)


def scan_tiled_render_groups(
    game_code: bytes,
    game_data: bytes,
    layout: dict[str, Any],
    candidate_indices: frozenset[int],
    flat_entry_count: int,
) -> tuple[list[dict[str, Any]], frozenset[int]]:
    """Recover the 64x32 CI4 tiles consumed by the 360x360 view renderer."""

    code_vram = int(layout["game_vram"])
    data_vram = int(layout["game_data_vram"])
    for address, expected in TILED_RENDER_CODE_SIGNATURES.items():
        actual = word_at_vram(game_code, code_vram, address)
        if actual != expected:
            raise ValueError(
                f"US tiled-render signature at 0x{address:X} is 0x{actual:08X}; "
                f"expected 0x{expected:08X}"
            )
    for address, expected in TILED_RENDER_DATA_WORDS.items():
        actual = word_at_vram(game_data, data_vram, address)
        if actual != expected:
            raise ValueError(
                f"US tiled-render data at 0x{address:X} is 0x{actual:08X}; "
                f"expected 0x{expected:08X}"
            )

    pointers = [
        word_at_vram(game_data, data_vram, PRELOAD_POINTER_TABLE_VRAM + index * 4)
        for index in range(PRELOAD_GROUP_COUNT)
    ]
    groups = []
    rendered_candidates: set[int] = set()
    for group_index, pointer in enumerate(pointers):
        last_record_start = data_vram + len(game_data) - 4 * TILED_VIEW_BASE_COUNT
        if not data_vram <= pointer <= last_record_start:
            raise ValueError(
                f"US tiled-render group {group_index} pointer 0x{pointer:X} "
                "is outside game data"
            )
        bases = [
            word_at_vram(game_data, data_vram, pointer + view_index * 4)
            for view_index in range(TILED_VIEW_BASE_COUNT)
        ]
        views = []
        for view_index, base in enumerate(bases):
            end = base + TILED_ENTRIES_PER_VIEW
            if base < 0 or end > flat_entry_count:
                raise ValueError(
                    f"US tiled-render group {group_index} view {view_index} range "
                    f"{base}:{end} is outside flat assets"
                )
            candidates = candidate_indices.intersection(range(base, end))
            rendered_candidates.update(candidates)
            views.append(
                {
                    "view_index": view_index,
                    "first_flat_index": base,
                    "last_flat_index": end - 1,
                    "entry_count": TILED_ENTRIES_PER_VIEW,
                    "ci4_candidate_count": len(candidates),
                }
            )
        groups.append(
            {
                "group_index": group_index,
                "record_pointer": f"0x{pointer:X}",
                "views": views,
                "ci4_candidate_count": sum(
                    view["ci4_candidate_count"] for view in views
                ),
            }
        )
    override_end = TILED_OVERRIDE_FIRST_INDEX + TILED_OVERRIDE_ENTRY_COUNT
    if override_end > flat_entry_count:
        raise ValueError("US tiled-render override range is outside flat assets")
    rendered_candidates.update(
        candidate_indices.intersection(
            range(TILED_OVERRIDE_FIRST_INDEX, override_end)
        )
    )
    return groups, frozenset(rendered_candidates)


def scan_direct_texture_references(
    data: bytes, source: str, target_indices: frozenset[int]
) -> list[TextureReference]:
    """Find loader-rewritten CI4 references in an aligned display-list blob.

    Conker stores a flat-archive index in the second word of an FD texture-image
    command.  ``func_1510CE60`` replaces that index with the decompressed
    pointer.  A second reference with flag 0x00800000 is rewritten to
    ``payload_end - 0x20``, which proves the location of the 16-entry palette.
    """

    references = []
    for offset in range(0, len(data) - 7, 8):
        image_command, image_reference = command_words(data, offset)
        if image_command != DIRECT_TEXTURE_IMAGE or image_reference not in target_indices:
            continue

        tile_command: int | None = None
        load_block_texels: int | None = None
        palette_at_payload_end = False
        palette_reference_mode: int | None = None
        palette_entries: int | None = None
        scan_end = min(len(data) - 7, offset + 0x100)
        for cursor in range(offset + 8, scan_end, 8):
            command, argument = command_words(data, cursor)
            opcode = command >> 24
            if command == DIRECT_TEXTURE_IMAGE or opcode in (
                END_DISPLAY_LIST,
                BRANCH_DISPLAY_LIST,
            ):
                break
            if opcode == 0xF3 and load_block_texels is None:
                load_block_texels = ((argument >> 12) & 0xFFF) + 1
            if is_render_tile(command, argument) and tile_command is None:
                tile_command = command
            if (
                command == DIRECT_PALETTE_IMAGE
                and (argument & 0x003FFFFF) == image_reference
            ):
                palette_reference_mode = argument >> 22
                palette_at_payload_end = palette_reference_mode == 2
            entries = tlut_entry_count(command, argument)
            if entries is not None and palette_entries is None:
                palette_entries = entries

        # Consecutive textures can reuse the preceding render-tile state.
        if tile_command is None:
            scan_start = max(0, offset - 0x100)
            for cursor in range(offset - 8, scan_start - 1, -8):
                command, argument = command_words(data, cursor)
                opcode = command >> 24
                if opcode in (END_DISPLAY_LIST, BRANCH_DISPLAY_LIST):
                    break
                if is_render_tile(command, argument):
                    tile_command = command
                    break

        dimensions = (
            ci4_dimensions_from_tile(tile_command) if tile_command is not None else None
        )
        tile_state = (
            tile_format_and_size(tile_command) if tile_command is not None else None
        )
        references.append(
            TextureReference(
                flat_index=image_reference,
                source=source,
                offset=offset,
                width=dimensions[0] if dimensions else None,
                height=dimensions[1] if dimensions else None,
                palette_at_payload_end=palette_at_payload_end,
                tile_command=tile_command,
                tile_format=tile_state[0] if tile_state else None,
                tile_size=tile_state[1] if tile_state else None,
                load_block_texels=load_block_texels,
                palette_reference_mode=palette_reference_mode,
                palette_entries=palette_entries,
            )
        )
    return references


def survey_rectangular_textures(
    profile: str, rom_argument: Path | None
) -> dict[str, Any]:
    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(f"US normalized ROM SHA-1 mismatch: got {digest}")

    flat_start = layout["flat_assets_start"]
    flat_end = layout["flat_assets_end"]
    flat_entries = list(iter_flat_rzip_entries(normalized[flat_start:flat_end]))
    rectangular = {
        entry.index: entry
        for entry in flat_entries
        if len(entry.data) == RECTANGULAR_PAYLOAD_SIZE
    }
    target_indices = frozenset(rectangular)
    references: list[TextureReference] = []
    for bank in parse_asset_banks(normalized, layout["asset_table"]):
        if bank.flags:
            continue
        for entry in parse_asset_entries(normalized, bank):
            raw = normalized[entry.start : entry.end]
            decoded = decode_rzip_chunk(raw).data if entry.compressed else raw
            references.extend(
                scan_direct_texture_references(
                    decoded,
                    f"bank-{bank.index:02X}/{entry.index:04d}",
                    target_indices,
                )
            )

    by_index: dict[int, list[TextureReference]] = {}
    for reference in references:
        by_index.setdefault(reference.flat_index, []).append(reference)

    proven = []
    incompatible = []
    conflicts = []
    for flat_index, texture_references in sorted(by_index.items()):
        dimensions = {
            (reference.width, reference.height)
            for reference in texture_references
            if reference.width is not None and reference.palette_at_payload_end
        }
        if len(dimensions) > 1:
            conflicts.append(
                {
                    "flat_index": flat_index,
                    "dimensions": [list(value) for value in sorted(dimensions)],
                }
            )
            continue
        if len(dimensions) != 1:
            incompatible_references = [
                reference
                for reference in texture_references
                if reference.palette_reference_mode == 1
                and reference.palette_entries == 256
            ]
            if incompatible_references:
                incompatible.append(
                    {
                        "flat_index": flat_index,
                        "reason": "256-entry-tlut",
                        "references": [
                            {
                                "source": reference.source,
                                "offset": f"0x{reference.offset:X}",
                                "tile_command": (
                                    f"0x{reference.tile_command:08X}"
                                    if reference.tile_command is not None
                                    else None
                                ),
                                "tile_format": reference.tile_format,
                                "tile_size": reference.tile_size,
                                "palette_reference_mode": (
                                    reference.palette_reference_mode
                                ),
                                "palette_entries": reference.palette_entries,
                                "load_block_texels": reference.load_block_texels,
                            }
                            for reference in incompatible_references
                        ],
                    }
                )
            continue
        width, height = next(iter(dimensions))
        entry = rectangular[flat_index]
        proven.append(
            {
                "flat_index": flat_index,
                "width": width,
                "height": height,
                "pixel_encoding": "ci4-high-nibble-first",
                "pixel_size": RECTANGULAR_PIXEL_SIZE,
                "palette_encoding": "rgba5551-big-endian",
                "palette_offset": RECTANGULAR_PIXEL_SIZE,
                "palette_size": PALETTE_SIZE,
                "decoded_sha1": hashlib.sha1(entry.data).hexdigest(),
                "references": [
                    {
                        "source": reference.source,
                        "offset": f"0x{reference.offset:X}",
                        "tile_command": (
                            f"0x{reference.tile_command:08X}"
                            if reference.tile_command is not None
                            else None
                        ),
                        "load_block_texels": reference.load_block_texels,
                    }
                    for reference in texture_references
                    if (reference.width, reference.height) == (width, height)
                    and reference.palette_at_payload_end
                ],
            }
        )

    proven_indices = {record["flat_index"] for record in proven}
    incompatible_indices = {record["flat_index"] for record in incompatible}
    direct_indices = frozenset(by_index)
    game_start = layout["game_start"]
    game_end = layout["game_end"]
    if layout.get("game_format") != "rzip":
        raise ValueError("rectangular texture survey requires the US RZIP game archive")
    game = parse_game_archive(normalized[game_start:game_end])
    preload_groups, preloaded_candidates = scan_indirect_preload_groups(
        game.code,
        game.data,
        layout,
        target_indices,
        len(flat_entries),
    )
    tiled_groups, tiled_candidates = scan_tiled_render_groups(
        game.code,
        game.data,
        layout,
        target_indices,
        len(flat_entries),
    )
    tiled_only_indices = tiled_candidates - direct_indices
    preload_only_indices = preloaded_candidates - direct_indices - tiled_candidates
    unreferenced_indices = (
        target_indices - direct_indices - preloaded_candidates - tiled_candidates
    )
    return {
        "schema_version": 4,
        "profile": profile,
        "source_rom": manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": digest,
        "target_decoded_size": RECTANGULAR_PAYLOAD_SIZE,
        "candidate_count": len(rectangular),
        "direct_reference_count": len(references),
        "directly_referenced_texture_count": len(by_index),
        "proven_ci4_texture_count": len(proven),
        "directly_incompatible_texture_count": len(incompatible),
        "direct_incompatible_runtime_tiled_overlap_count": len(
            tiled_candidates.intersection(incompatible_indices)
        ),
        "indirect_preload_candidate_count": len(preloaded_candidates),
        "runtime_tiled_ci4_candidate_count": len(tiled_candidates),
        "runtime_tiled_only_candidate_count": len(tiled_only_indices),
        "preload_only_candidate_count": len(preload_only_indices),
        "unreferenced_candidate_count": len(unreferenced_indices),
        "runtime_referenced_candidate_count": len(
            target_indices - unreferenced_indices
        ),
        "not_standalone_extracted_texture_count": (
            len(rectangular) - len(proven_indices)
        ),
        "unresolved_texture_count": len(unreferenced_indices),
        "unreferenced_candidates": [
            {
                "flat_index": flat_index,
                "decoded_sha1": hashlib.sha1(rectangular[flat_index].data).hexdigest(),
                "structural_format": "ci4-64x32-with-trailing-rgba5551-palette",
                "classification": "no-recovered-runtime-reference",
            }
            for flat_index in sorted(unreferenced_indices)
        ],
        "indirect_preload_contract": {
            "function": "func_15000AD0",
            "loader": "func_1510D0EC",
            "pointer_table_vram": f"0x{PRELOAD_POINTER_TABLE_VRAM:X}",
            "group_count": PRELOAD_GROUP_COUNT,
            "entries_per_group": PRELOAD_GROUP_LENGTH,
            "classification": "runtime-flat-resource-reference-only",
            "groups": preload_groups,
        },
        "runtime_tiled_ci4_contract": {
            "selector": "func_15111AF4",
            "renderer": "func_15110CFC",
            "loader": "func_1510D0EC",
            "pointer_table_vram": f"0x{PRELOAD_POINTER_TABLE_VRAM:X}",
            "group_count": PRELOAD_GROUP_COUNT,
            "views_per_group": TILED_VIEW_BASE_COUNT,
            "view_width": TILED_VIEW_WIDTH,
            "view_height": TILED_VIEW_HEIGHT,
            "visible_tile_width": TILED_VISIBLE_WIDTH,
            "visible_tile_height": TILED_VISIBLE_HEIGHT,
            "storage_width": TILED_STORAGE_WIDTH,
            "storage_height": TILED_STORAGE_HEIGHT,
            "columns": TILED_COLUMNS,
            "rows": TILED_ROWS,
            "entries_per_view": TILED_ENTRIES_PER_VIEW,
            "flat_index_order": "column-major",
            "pixel_encoding": "ci4-high-nibble-first",
            "palette_offset": RECTANGULAR_PIXEL_SIZE,
            "palette_entries": PALETTE_COLORS,
            "classification": "runtime-rendered-tile-not-yet-extracted",
            "conditional_override": {
                "function": "func_15110CFC",
                "first_flat_index": TILED_OVERRIDE_FIRST_INDEX,
                "last_flat_index": (
                    TILED_OVERRIDE_FIRST_INDEX + TILED_OVERRIDE_ENTRY_COUNT - 1
                ),
                "entry_count": TILED_OVERRIDE_ENTRY_COUNT,
                "ci4_candidate_indices": sorted(
                    target_indices.intersection(
                        range(
                            TILED_OVERRIDE_FIRST_INDEX,
                            TILED_OVERRIDE_FIRST_INDEX
                            + TILED_OVERRIDE_ENTRY_COUNT,
                        )
                    )
                ),
            },
            "groups": tiled_groups,
        },
        "conflicts": conflicts,
        "proven_textures": proven,
        "incompatible_textures": incompatible,
    }


def load_rectangular_textures(
    profile: str, rom_argument: Path | None
) -> tuple[
    Path,
    bytes,
    str,
    dict[str, Any],
    list[TextureAsset],
    dict[int, dict[str, Any]],
    dict[str, Any],
]:
    survey = survey_rectangular_textures(profile, rom_argument)
    if survey["conflicts"]:
        raise ValueError("rectangular CI4 survey contains conflicting dimensions")
    contracts = {
        int(record["flat_index"]): record for record in survey["proven_textures"]
    }
    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    start = layout["flat_assets_start"]
    end = layout["flat_assets_end"]
    textures = [
        TextureAsset(entry.index, start + entry.start, start + entry.end, entry.data)
        for entry in iter_flat_rzip_entries(normalized[start:end])
        if entry.index in contracts
    ]
    if len(textures) != len(contracts):
        raise ValueError("not every proven rectangular CI4 contract has a flat payload")
    return (
        rom_path,
        normalized,
        source_order,
        layout,
        textures,
        contracts,
        survey,
    )


def load_tiled_view_textures(
    profile: str, rom_argument: Path | None
) -> tuple[
    Path,
    bytes,
    str,
    dict[str, Any],
    dict[int, TextureAsset],
    list[dict[str, Any]],
]:
    survey = survey_rectangular_textures(profile, rom_argument)
    contract = survey["runtime_tiled_ci4_contract"]
    groups = contract["groups"]
    runtime_indices = {
        index
        for group in groups
        for view in group["views"]
        for index in range(
            int(view["first_flat_index"]), int(view["last_flat_index"]) + 1
        )
    }
    runtime_indices.update(
        range(
            TILED_OVERRIDE_FIRST_INDEX,
            TILED_OVERRIDE_FIRST_INDEX + TILED_OVERRIDE_ENTRY_COUNT,
        )
    )
    preview_indices = {
        index
        for group in groups
        for view in group["views"]
        for index in range(
            int(view["first_flat_index"]) - TILED_STREAM_PHASE,
            int(view["first_flat_index"])
            + TILED_ENTRIES_PER_VIEW
            - TILED_STREAM_PHASE,
        )
    }
    selected_indices = runtime_indices | preview_indices
    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    start = layout["flat_assets_start"]
    end = layout["flat_assets_end"]
    textures = {
        entry.index: TextureAsset(
            entry.index, start + entry.start, start + entry.end, entry.data
        )
        for entry in iter_flat_rzip_entries(normalized[start:end])
        if entry.index in selected_indices
    }
    if set(textures) != selected_indices:
        raise ValueError("not every tiled-view flat payload is present")
    return rom_path, normalized, source_order, layout, textures, groups


def compose_tiled_view(
    base: int, textures: dict[int, TextureAsset]
) -> tuple[bytes, list[int]]:
    edge_indices = [
        index
        for index in range(
            base - TILED_STREAM_PHASE,
            base + TILED_ENTRIES_PER_VIEW - TILED_STREAM_PHASE,
        )
        if len(textures[index].payload) == TILED_EDGE_CI8_SIZE
    ]
    composite = bytearray(TILED_VIEW_WIDTH * TILED_VIEW_HEIGHT * 4)
    for column in range(TILED_COLUMNS):
        for row in range(TILED_ROWS):
            destination_position = column * TILED_ROWS + row
            flat_index = base + destination_position - TILED_STREAM_PHASE
            texture = textures[flat_index]
            if len(texture.payload) == RECTANGULAR_PAYLOAD_SIZE:
                tile = indexed_payload_rgba(texture.payload, 4)
                tile_width = TILED_STORAGE_WIDTH
                visible_width = TILED_VISIBLE_WIDTH
            elif len(texture.payload) == TILED_STORAGE_WIDTH * TILED_STORAGE_HEIGHT + 512:
                tile = indexed_payload_rgba(texture.payload, 8)
                tile_width = TILED_STORAGE_WIDTH
                visible_width = TILED_VISIBLE_WIDTH
            elif len(texture.payload) == TILED_EDGE_CI8_SIZE:
                tile = indexed_payload_rgba(
                    texture.payload,
                    8,
                    width=TILED_EDGE_STORAGE_WIDTH,
                    height=TILED_STORAGE_HEIGHT,
                )
                tile_width = TILED_EDGE_STORAGE_WIDTH
                visible_width = TILED_EDGE_VISIBLE_WIDTH
            else:
                raise ValueError(
                    f"tiled-view texture {flat_index} has unsupported decoded size "
                    f"{len(texture.payload)}"
                )
            destination_x = column * TILED_VISIBLE_WIDTH
            destination_y = row * TILED_VISIBLE_HEIGHT
            for tile_y in range(TILED_VISIBLE_HEIGHT):
                source = tile_y * tile_width * 4
                destination = (
                    (destination_y + tile_y) * TILED_VIEW_WIDTH + destination_x
                ) * 4
                composite[destination : destination + visible_width * 4] = tile[
                    source : source + visible_width * 4
                ]
    return bytes(composite), edge_indices


def safe_manifest_file(input_dir: Path, filename: str) -> Path:
    relative = Path(filename)
    if relative.is_absolute() or ".." in relative.parts:
        raise ValueError(f"unsafe texture manifest path: {filename}")
    return input_dir / relative


def extract_textures(
    profile: str, rom_argument: Path | None, output: Path, force: bool
) -> dict[str, Any]:
    rom_path, normalized, source_order, layout, textures = load_profile_textures(
        profile, rom_argument
    )
    prepare_output(output, force)
    texture_dir = output / "textures"
    texture_dir.mkdir()
    records = []
    for texture in textures:
        filename = f"textures/{texture.flat_index:04d}.ci4.png"
        row_layout = row_layout_for_flat_index(texture.flat_index)
        (output / filename).write_bytes(
            encode_indexed_png(texture.payload, row_layout)
        )
        records.append(
            {
                "flat_index": texture.flat_index,
                "rom_start": f"0x{texture.rom_start:X}",
                "rom_end": f"0x{texture.rom_end:X}",
                "decoded_size": len(texture.payload),
                "decoded_sha1": hashlib.sha1(texture.payload).hexdigest(),
                "row_layout": row_layout,
                "file": filename,
            }
        )
    manifest = {
        "schema_version": 3,
        "profile": profile,
        "family": SQUARE_FAMILY,
        "source_rom": manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": hashlib.sha1(normalized).hexdigest(),
        "flat_rom_start": f"0x{layout['flat_assets_start']:X}",
        "flat_rom_end": f"0x{layout['flat_assets_end']:X}",
        "width": WIDTH,
        "height": HEIGHT,
        "source_origin": SOURCE_ORIGIN,
        "png_origin": PNG_ORIGIN,
        "texture_count": len(records),
        "textures": records,
    }
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    return manifest


def extract_rectangular_textures(
    profile: str, rom_argument: Path | None, output: Path, force: bool
) -> dict[str, Any]:
    (
        rom_path,
        normalized,
        source_order,
        layout,
        textures,
        contracts,
        survey,
    ) = load_rectangular_textures(profile, rom_argument)
    prepare_output(output, force)
    texture_dir = output / "textures"
    texture_dir.mkdir()
    records = []
    for texture in textures:
        contract = contracts[texture.flat_index]
        width = int(contract["width"])
        height = int(contract["height"])
        filename = f"textures/{texture.flat_index:04d}.ci4.png"
        (output / filename).write_bytes(
            encode_indexed_png(
                texture.payload, ROW_LAYOUT_TMEM, width=width, height=height
            )
        )
        records.append(
            {
                "flat_index": texture.flat_index,
                "rom_start": f"0x{texture.rom_start:X}",
                "rom_end": f"0x{texture.rom_end:X}",
                "decoded_size": len(texture.payload),
                "decoded_sha1": hashlib.sha1(texture.payload).hexdigest(),
                "width": width,
                "height": height,
                "row_layout": ROW_LAYOUT_TMEM,
                "contract_references": contract["references"],
                "file": filename,
            }
        )
    manifest = {
        "schema_version": 4,
        "profile": profile,
        "family": RECTANGULAR_FAMILY,
        "source_rom": manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": hashlib.sha1(normalized).hexdigest(),
        "flat_rom_start": f"0x{layout['flat_assets_start']:X}",
        "flat_rom_end": f"0x{layout['flat_assets_end']:X}",
        "source_origin": SOURCE_ORIGIN,
        "png_origin": PNG_ORIGIN,
        "candidate_count": survey["candidate_count"],
        "directly_incompatible_texture_count": survey[
            "directly_incompatible_texture_count"
        ],
        "direct_incompatible_runtime_tiled_overlap_count": survey[
            "direct_incompatible_runtime_tiled_overlap_count"
        ],
        "indirect_preload_candidate_count": survey[
            "indirect_preload_candidate_count"
        ],
        "runtime_tiled_ci4_candidate_count": survey[
            "runtime_tiled_ci4_candidate_count"
        ],
        "runtime_tiled_only_candidate_count": survey[
            "runtime_tiled_only_candidate_count"
        ],
        "preload_only_candidate_count": survey["preload_only_candidate_count"],
        "unreferenced_candidate_count": survey["unreferenced_candidate_count"],
        "runtime_referenced_candidate_count": survey[
            "runtime_referenced_candidate_count"
        ],
        "not_standalone_extracted_texture_count": survey[
            "not_standalone_extracted_texture_count"
        ],
        "unresolved_texture_count": survey["unresolved_texture_count"],
        "texture_count": len(records),
        "textures": records,
    }
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    return manifest


def extract_tiled_views(
    profile: str, rom_argument: Path | None, output: Path, force: bool
) -> dict[str, Any]:
    rom_path, normalized, source_order, layout, textures, groups = (
        load_tiled_view_textures(profile, rom_argument)
    )
    prepare_output(output, force)
    tile_dir = output / "tiles"
    view_dir = output / "views"
    tile_dir.mkdir()
    view_dir.mkdir()

    runtime_indices = {
        index
        for group in groups
        for view in group["views"]
        for index in range(
            int(view["first_flat_index"]), int(view["last_flat_index"]) + 1
        )
    }
    ordinary_runtime_tile_count = len(runtime_indices)
    runtime_indices.update(
        range(
            TILED_OVERRIDE_FIRST_INDEX,
            TILED_OVERRIDE_FIRST_INDEX + TILED_OVERRIDE_ENTRY_COUNT,
        )
    )
    preview_indices = {
        index
        for group in groups
        for view in group["views"]
        for index in range(
            int(view["first_flat_index"]) - TILED_STREAM_PHASE,
            int(view["first_flat_index"])
            + TILED_ENTRIES_PER_VIEW
            - TILED_STREAM_PHASE,
        )
    }
    tile_records = []
    format_counts = {"ci4": 0, "ci8": 0, "ci8-edge": 0}
    for flat_index, texture in sorted(textures.items()):
        if len(texture.payload) == RECTANGULAR_PAYLOAD_SIZE:
            tile_format = "ci4"
            filename = f"tiles/{flat_index:04d}.ci4.png"
            encoded = encode_indexed_png(
                texture.payload,
                ROW_LAYOUT_TMEM,
                TILED_STORAGE_WIDTH,
                TILED_STORAGE_HEIGHT,
            )
        elif len(texture.payload) == TILED_STORAGE_WIDTH * TILED_STORAGE_HEIGHT + 512:
            tile_format = "ci8"
            filename = f"tiles/{flat_index:04d}.ci8.png"
            encoded = encode_ci8_png(texture.payload)
            storage_width = TILED_STORAGE_WIDTH
            visible_width = TILED_VISIBLE_WIDTH
        elif len(texture.payload) == TILED_EDGE_CI8_SIZE:
            tile_format = "ci8-edge"
            filename = f"tiles/{flat_index:04d}.ci8-edge.png"
            encoded = encode_ci8_png(
                texture.payload,
                ROW_LAYOUT_TMEM,
                TILED_EDGE_STORAGE_WIDTH,
                TILED_STORAGE_HEIGHT,
            )
            storage_width = TILED_EDGE_STORAGE_WIDTH
            visible_width = TILED_EDGE_VISIBLE_WIDTH
        else:
            raise ValueError(
                f"tiled-view texture {flat_index} has unsupported decoded size "
                f"{len(texture.payload)}"
            )
        if tile_format in ("ci4", "ci8"):
            storage_width = TILED_STORAGE_WIDTH
            visible_width = TILED_VISIBLE_WIDTH
        (output / filename).write_bytes(encoded)
        format_counts[tile_format] += 1
        tile_records.append(
            {
                "flat_index": flat_index,
                "rom_start": f"0x{texture.rom_start:X}",
                "rom_end": f"0x{texture.rom_end:X}",
                "decoded_size": len(texture.payload),
                "decoded_sha1": hashlib.sha1(texture.payload).hexdigest(),
                "format": tile_format,
                "storage_width": storage_width,
                "storage_height": TILED_STORAGE_HEIGHT,
                "visible_width": visible_width,
                "visible_height": TILED_VISIBLE_HEIGHT,
                "row_layout": ROW_LAYOUT_TMEM,
                "runtime_selected": flat_index in runtime_indices,
                "preview_used": flat_index in preview_indices,
                "file": filename,
            }
        )

    view_records = []
    edge_view_count = 0
    for group in groups:
        group_index = int(group["group_index"])
        for view in group["views"]:
            view_index = int(view["view_index"])
            base = int(view["first_flat_index"])
            rgba, edge_indices = compose_tiled_view(base, textures)
            if edge_indices:
                edge_view_count += 1
            filename = f"views/group-{group_index:02d}-view-{view_index}.rgba.png"
            (output / filename).write_bytes(
                encode_rgba_png(TILED_VIEW_WIDTH, TILED_VIEW_HEIGHT, rgba)
            )
            view_records.append(
                {
                    "group_index": group_index,
                    "view_index": view_index,
                    "first_flat_index": base,
                    "last_flat_index": base + TILED_ENTRIES_PER_VIEW - 1,
                    "flat_index_order": "column-major",
                    "source_row_order_top_to_bottom": [
                        (row - TILED_STREAM_PHASE) % TILED_ROWS
                        for row in range(TILED_ROWS)
                    ],
                    "source_flat_index_start": base - TILED_STREAM_PHASE,
                    "source_flat_index_end": (
                        base + TILED_ENTRIES_PER_VIEW - TILED_STREAM_PHASE - 1
                    ),
                    "continuous_stream_phase": TILED_STREAM_PHASE,
                    "columns": TILED_COLUMNS,
                    "rows": TILED_ROWS,
                    "width": TILED_VIEW_WIDTH,
                    "height": TILED_VIEW_HEIGHT,
                    "edge_flat_indices": edge_indices,
                    "preview_only": True,
                    "file": filename,
                }
            )

    manifest = {
        "schema_version": 5,
        "profile": profile,
        "family": TILED_VIEWS_FAMILY,
        "source_rom": manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": hashlib.sha1(normalized).hexdigest(),
        "flat_rom_start": f"0x{layout['flat_assets_start']:X}",
        "flat_rom_end": f"0x{layout['flat_assets_end']:X}",
        "source_origin": SOURCE_ORIGIN,
        "png_origin": PNG_ORIGIN,
        "view_width": TILED_VIEW_WIDTH,
        "view_height": TILED_VIEW_HEIGHT,
        "visible_tile_width": TILED_VISIBLE_WIDTH,
        "visible_tile_height": TILED_VISIBLE_HEIGHT,
        "storage_tile_width": TILED_STORAGE_WIDTH,
        "storage_tile_height": TILED_STORAGE_HEIGHT,
        "view_count": len(view_records),
        "edge_view_count": edge_view_count,
        "tile_count": len(tile_records),
        "ordinary_runtime_tile_count": ordinary_runtime_tile_count,
        "runtime_tile_count": len(runtime_indices),
        "preview_tile_count": len(preview_indices),
        "context_only_tile_count": len(preview_indices - runtime_indices),
        "runtime_tail_tile_count": len(runtime_indices - preview_indices),
        "format_counts": format_counts,
        "editing_contract": (
            "Edit indexed files under tiles/. The assembled RGBA views are "
            "preview-only because each logical view uses per-tile palettes. "
            "The assembled previews apply the renderer stream's two-entry "
            "phase continuously across column and view boundaries. Runtime "
            "tail records that spill into unselected faces remain reversible "
            "but are not used by these previews."
        ),
        "tiles": tile_records,
        "views": view_records,
    }
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    return manifest


def pack_textures(input_dir: Path, output: Path, force: bool) -> dict[int, bytes]:
    manifest = json.loads((input_dir / "manifest.json").read_text(encoding="utf-8"))
    schema_family = (manifest.get("schema_version"), manifest.get("family"))
    tiled_family = schema_family == (5, TILED_VIEWS_FAMILY)
    records = manifest.get("tiles" if tiled_family else "textures")
    if (
        schema_family
        not in (
            (3, SQUARE_FAMILY),
            (4, RECTANGULAR_FAMILY),
            (5, TILED_VIEWS_FAMILY),
        )
        or manifest.get("profile") != "us"
        or manifest.get("source_origin") != SOURCE_ORIGIN
        or manifest.get("png_origin") != PNG_ORIGIN
        or not isinstance(records, list)
    ):
        raise ValueError("texture manifest has an unsupported schema or family")
    count_key = "tile_count" if tiled_family else "texture_count"
    if int(manifest.get(count_key, -1)) != len(records):
        raise ValueError("texture manifest count does not match its texture list")
    packed: dict[int, bytes] = {}
    packed_layouts: dict[int, str] = {}
    packed_formats: dict[int, str] = {}
    for record in records:
        flat_index = int(record["flat_index"])
        if flat_index in packed:
            raise ValueError("texture manifest contains a duplicate flat index")
        row_layout = record.get("row_layout")
        tile_format = record.get("format") if tiled_family else None
        if row_layout not in ROW_LAYOUTS:
            raise ValueError(
                f"texture {flat_index} has an unsupported row layout: {row_layout}"
            )
        if tiled_family:
            width = int(record["storage_width"])
            height = int(record["storage_height"])
            data = safe_manifest_file(input_dir, record["file"]).read_bytes()
            if tile_format == "ci4":
                packed[flat_index] = decode_indexed_png(
                    data, row_layout, width, height
                )
            elif tile_format in ("ci8", "ci8-edge"):
                packed[flat_index] = decode_ci8_png(data, row_layout, width, height)
            else:
                raise ValueError(
                    f"tiled-view texture {flat_index} has unsupported format: "
                    f"{tile_format}"
                )
            packed_formats[flat_index] = str(tile_format)
        elif schema_family == (3, SQUARE_FAMILY):
            width, height = WIDTH, HEIGHT
            packed[flat_index] = decode_indexed_png(
                safe_manifest_file(input_dir, record["file"]).read_bytes(),
                row_layout,
                width,
                height,
            )
        else:
            width, height = int(record["width"]), int(record["height"])
            if (width, height) not in ((32, 64), (64, 32)):
                raise ValueError(
                    f"texture {flat_index} has unsupported dimensions: "
                    f"{width}x{height}"
                )
            packed[flat_index] = decode_indexed_png(
                safe_manifest_file(input_dir, record["file"]).read_bytes(),
                row_layout,
                width,
                height,
            )
        packed_layouts[flat_index] = row_layout
    if list(packed) != sorted(packed):
        raise ValueError("texture manifest flat indices are not ordered")
    prepare_output(output, force)
    payload_dir = output / "flat"
    payload_dir.mkdir()
    for flat_index, payload in packed.items():
        (payload_dir / f"{flat_index:04d}.bin").write_bytes(payload)
    packed_records = [
        {
            "flat_index": index,
            "size": len(payload),
            "sha1": hashlib.sha1(payload).hexdigest(),
            "row_layout": packed_layouts[index],
            **({"format": packed_formats[index]} if tiled_family else {}),
            **(
                {
                    "width": int(records[position]["width"]),
                    "height": int(records[position]["height"]),
                }
                if schema_family == (4, RECTANGULAR_FAMILY)
                else {}
            ),
            "file": f"flat/{index:04d}.bin",
        }
        for position, (index, payload) in enumerate(packed.items())
    ]
    packed_manifest = {
        "schema_version": manifest["schema_version"],
        "profile": "us",
        "family": manifest["family"],
        "source_origin": SOURCE_ORIGIN,
        "png_origin": PNG_ORIGIN,
        ("tile_count" if tiled_family else "texture_count"): len(packed),
        ("tiles" if tiled_family else "textures"): packed_records,
    }
    (output / "manifest.json").write_text(
        json.dumps(packed_manifest, indent=2) + "\n", encoding="utf-8"
    )
    return packed


def verify_textures(profile: str, rom_argument: Path | None) -> tuple[int, int]:
    _, _, _, _, textures = load_profile_textures(profile, rom_argument)
    for texture in textures:
        row_layout = row_layout_for_flat_index(texture.flat_index)
        if (
            decode_indexed_png(
                encode_indexed_png(texture.payload, row_layout), row_layout
            )
            != texture.payload
        ):
            raise ValueError(
                f"texture {texture.flat_index} did not rebuild byte-identically"
            )
    return len(textures), sum(len(texture.payload) for texture in textures)


def verify_rectangular_textures(
    profile: str, rom_argument: Path | None
) -> tuple[int, int]:
    _, _, _, _, textures, contracts, _ = load_rectangular_textures(
        profile, rom_argument
    )
    for texture in textures:
        contract = contracts[texture.flat_index]
        width = int(contract["width"])
        height = int(contract["height"])
        if (
            decode_indexed_png(
                encode_indexed_png(
                    texture.payload, ROW_LAYOUT_TMEM, width=width, height=height
                ),
                ROW_LAYOUT_TMEM,
                width,
                height,
            )
            != texture.payload
        ):
            raise ValueError(
                f"texture {texture.flat_index} did not rebuild byte-identically"
            )
    return len(textures), sum(len(texture.payload) for texture in textures)


def verify_tiled_views(
    profile: str, rom_argument: Path | None
) -> tuple[int, int, int]:
    _, _, _, _, textures, groups = load_tiled_view_textures(profile, rom_argument)
    edge_count = 0
    for texture in textures.values():
        if len(texture.payload) == RECTANGULAR_PAYLOAD_SIZE:
            rebuilt = decode_indexed_png(
                encode_indexed_png(
                    texture.payload,
                    ROW_LAYOUT_TMEM,
                    TILED_STORAGE_WIDTH,
                    TILED_STORAGE_HEIGHT,
                ),
                ROW_LAYOUT_TMEM,
                TILED_STORAGE_WIDTH,
                TILED_STORAGE_HEIGHT,
            )
        elif len(texture.payload) == TILED_STORAGE_WIDTH * TILED_STORAGE_HEIGHT + 512:
            rebuilt = decode_ci8_png(encode_ci8_png(texture.payload))
        elif len(texture.payload) == TILED_EDGE_CI8_SIZE:
            edge_count += 1
            rebuilt = decode_ci8_png(
                encode_ci8_png(
                    texture.payload,
                    ROW_LAYOUT_TMEM,
                    TILED_EDGE_STORAGE_WIDTH,
                    TILED_STORAGE_HEIGHT,
                ),
                ROW_LAYOUT_TMEM,
                TILED_EDGE_STORAGE_WIDTH,
                TILED_STORAGE_HEIGHT,
            )
        else:
            raise ValueError(
                f"tiled-view texture {texture.flat_index} has unsupported decoded "
                f"size {len(texture.payload)}"
            )
        if rebuilt != texture.payload:
            raise ValueError(
                f"tiled-view texture {texture.flat_index} did not rebuild "
                "byte-identically"
            )
    view_count = sum(len(group["views"]) for group in groups)
    return len(textures), view_count, edge_count


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    subparsers = parser.add_subparsers(dest="command", required=True)
    extract_parser = subparsers.add_parser("extract")
    extract_parser.add_argument("--profile", choices=("us",), default="us")
    extract_parser.add_argument(
        "--family",
        choices=(
            SQUARE_FAMILY_NAME,
            RECTANGULAR_FAMILY_NAME,
            TILED_VIEWS_FAMILY_NAME,
        ),
        default=SQUARE_FAMILY_NAME,
    )
    extract_parser.add_argument("--rom", type=Path)
    extract_parser.add_argument("--output", type=Path)
    extract_parser.add_argument("--force", action="store_true")
    pack_parser = subparsers.add_parser("pack")
    pack_parser.add_argument("--input", type=Path, required=True)
    pack_parser.add_argument("--output", type=Path, required=True)
    pack_parser.add_argument("--force", action="store_true")
    verify_parser = subparsers.add_parser("verify")
    verify_parser.add_argument("--profile", choices=("us",), default="us")
    verify_parser.add_argument(
        "--family",
        choices=(
            SQUARE_FAMILY_NAME,
            RECTANGULAR_FAMILY_NAME,
            TILED_VIEWS_FAMILY_NAME,
        ),
        default=SQUARE_FAMILY_NAME,
    )
    verify_parser.add_argument("--rom", type=Path)
    survey_parser = subparsers.add_parser("survey")
    survey_parser.add_argument("--profile", choices=("us",), default="us")
    survey_parser.add_argument("--rom", type=Path)
    survey_parser.add_argument("--output", type=Path)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        if args.command == "extract":
            default_name = args.profile
            if args.family != SQUARE_FAMILY_NAME:
                default_name = f"{args.profile}-{args.family}"
            output = args.output or ROOT / "build" / "assets" / "textures" / default_name
            if not output.is_absolute():
                output = ROOT / output
            if args.family == SQUARE_FAMILY_NAME:
                manifest = extract_textures(args.profile, args.rom, output, args.force)
            elif args.family == RECTANGULAR_FAMILY_NAME:
                manifest = extract_rectangular_textures(
                    args.profile, args.rom, output, args.force
                )
            else:
                manifest = extract_tiled_views(
                    args.profile, args.rom, output, args.force
                )
            if args.family == TILED_VIEWS_FAMILY_NAME:
                print(
                    f"Extracted {manifest['view_count']} US tiled views and "
                    f"{manifest['tile_count']} reversible tile payloads to "
                    f"{display_path(output)}"
                )
            else:
                print(
                    f"Extracted {manifest['texture_count']} US {args.family} CI4 "
                    f"textures to {display_path(output)}"
                )
        elif args.command == "pack":
            input_dir = args.input if args.input.is_absolute() else ROOT / args.input
            output = args.output if args.output.is_absolute() else ROOT / args.output
            packed = pack_textures(input_dir, output, args.force)
            print(
                f"Packed {len(packed)} US texture payloads "
                f"({sum(map(len, packed.values()))} bytes) to {display_path(output)}"
            )
        elif args.command == "verify":
            if args.family == SQUARE_FAMILY_NAME:
                count, size = verify_textures(args.profile, args.rom)
                description = f"{count} entries, {size} bytes"
            elif args.family == RECTANGULAR_FAMILY_NAME:
                count, size = verify_rectangular_textures(args.profile, args.rom)
                description = f"{count} entries, {size} bytes"
            else:
                count, view_count, edge_count = verify_tiled_views(
                    args.profile, args.rom
                )
                description = (
                    f"{view_count} views, {count} tiles, "
                    f"{edge_count} compact CI8 edge tiles"
                )
            print(
                f"Verified US {args.family} textures: {description}, byte-identical"
            )
        else:
            output = (
                args.output
                or ROOT
                / "build"
                / "assets"
                / "textures"
                / args.profile
                / "1056-contracts.json"
            )
            if not output.is_absolute():
                output = ROOT / output
            manifest = survey_rectangular_textures(args.profile, args.rom)
            output.parent.mkdir(parents=True, exist_ok=True)
            output.write_text(
                json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
            )
            print(
                f"Surveyed {manifest['candidate_count']} US 1,056-byte payloads: "
                f"{manifest['proven_ci4_texture_count']} have direct CI4 dimension "
                "contracts; "
                f"{manifest['directly_incompatible_texture_count']} use incompatible "
                "256-entry TLUT paths; "
                f"{manifest['runtime_tiled_ci4_candidate_count']} are consumed as "
                "64x32 CI4 tiles by the 360x360 runtime renderer; "
                f"{manifest['preload_only_candidate_count']} remain preload-only; "
                f"{manifest['unreferenced_candidate_count']} have no recovered runtime "
                "reference; "
                f"wrote {display_path(output)}"
            )
    except (KeyError, OSError, TypeError, ValueError, json.JSONDecodeError) as error:
        print(f"error: {error}")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
