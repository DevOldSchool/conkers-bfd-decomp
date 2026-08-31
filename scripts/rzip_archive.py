#!/usr/bin/env python3
"""Parse Conker game archives and indexed asset banks without guessing by signature."""

from __future__ import annotations

import struct
import zlib
from dataclasses import dataclass
from typing import Iterator


OFFSET_XOR = 0x8039CCCA
Z64_MAGIC = b"\x80\x37\x12\x40"
V64_MAGIC = b"\x37\x80\x40\x12"
N64_MAGIC = b"\x40\x12\x37\x80"


@dataclass(frozen=True)
class DecodedChunk:
    data: bytes
    consumed: int
    declared_size: int


@dataclass(frozen=True)
class GameArchive:
    code: bytes
    data: bytes
    code_offsets: tuple[int, ...]
    decoded_code_offsets: tuple[int, ...]
    code_end: int
    data_start: int
    data_end: int
    code_padding: bytes
    data_padding: bytes


@dataclass(frozen=True)
class AssetBank:
    index: int
    start: int
    end: int
    flags: int


@dataclass(frozen=True)
class AssetEntry:
    index: int
    start: int
    end: int
    type_flags: int
    compressed: bool


@dataclass(frozen=True)
class FlatRzipEntry:
    index: int
    start: int
    end: int
    data: bytes


def normalize_rom(data: bytes) -> tuple[bytes, str]:
    """Return big-endian ROM bytes and the detected source byte order."""

    magic = data[:4]
    if magic == Z64_MAGIC:
        return data, "z64"
    if magic == V64_MAGIC:
        if len(data) % 2:
            raise ValueError("byte-swapped V64 ROM has an odd byte length")
        swapped = bytearray(len(data))
        swapped[0::2] = data[1::2]
        swapped[1::2] = data[0::2]
        return bytes(swapped), "v64"
    if magic == N64_MAGIC:
        if len(data) % 4:
            raise ValueError("word-swapped N64 ROM length is not divisible by four")
        swapped = bytearray(len(data))
        for offset in range(0, len(data), 4):
            swapped[offset : offset + 4] = data[offset : offset + 4][::-1]
        return bytes(swapped), "n64"
    raise ValueError(f"unsupported N64 ROM byte order (magic {magic.hex()})")


def decode_rzip_chunk(blob: bytes) -> DecodedChunk:
    """Decode one length-prefixed raw-deflate stream and report its exact extent."""

    if len(blob) < 5:
        raise ValueError("RZIP chunk is shorter than its header and deflate stream")
    declared_size = struct.unpack_from(">I", blob, 0)[0]
    decoder = zlib.decompressobj(wbits=-15)
    data = decoder.decompress(blob[4:])
    data += decoder.flush()
    if not decoder.eof:
        raise ValueError("RZIP deflate stream is truncated")
    if len(data) != declared_size:
        raise ValueError(
            f"RZIP length mismatch: header declares {declared_size}, decoded {len(data)}"
        )
    consumed = len(blob) - len(decoder.unused_data)
    return DecodedChunk(data=data, consumed=consumed, declared_size=declared_size)


def iter_flat_rzip_entries(blob: bytes) -> Iterator[FlatRzipEntry]:
    """Decode a contiguous stream of length-prefixed RZIP chunks."""

    offset = 0
    index = 0
    while offset < len(blob):
        decoded = decode_rzip_chunk(blob[offset:])
        if decoded.consumed <= 4:
            raise ValueError(f"flat RZIP entry {index} did not consume a deflate stream")
        end = offset + decoded.consumed
        yield FlatRzipEntry(index=index, start=offset, end=end, data=decoded.data)
        offset = end
        index += 1


def game_code_offsets(payload: bytes, key: int = OFFSET_XOR) -> tuple[int, ...]:
    offsets: list[int] = []
    for index in range(1, len(payload) // 4):
        encoded = struct.unpack_from(">I", payload, index * 4)[0]
        if encoded == 0:
            break
        offsets.append(encoded ^ key)
    if len(offsets) < 2:
        raise ValueError("game RZIP code table has fewer than two offsets")
    table_end = (len(offsets) + 2) * 4
    if offsets[0] < table_end:
        raise ValueError("game RZIP code data overlaps its offset table")
    if offsets != sorted(offsets):
        raise ValueError("game RZIP code offsets are not monotonic")
    return tuple(offsets)


def parse_game_archive(payload: bytes, key: int = OFFSET_XOR) -> GameArchive:
    if len(payload) < 4:
        raise ValueError("game archive is too short")
    data_start = struct.unpack_from(">I", payload, 0)[0]
    offsets = game_code_offsets(payload, key)
    code_end = offsets[-1]
    if not (code_end <= data_start < len(payload)):
        raise ValueError("game RZIP data offset is outside the archive or before code end")

    code_parts: list[bytes] = []
    decoded_offsets = [0]
    for start, end in zip(offsets, offsets[1:]):
        decoded = decode_rzip_chunk(payload[start:end])
        code_parts.append(decoded.data)
        decoded_offsets.append(decoded_offsets[-1] + len(decoded.data))

    decoded_data = decode_rzip_chunk(payload[data_start:])
    data_end = data_start + decoded_data.consumed
    return GameArchive(
        code=b"".join(code_parts),
        data=decoded_data.data,
        code_offsets=offsets,
        decoded_code_offsets=tuple(decoded_offsets),
        code_end=code_end,
        data_start=data_start,
        data_end=data_end,
        code_padding=payload[code_end:data_start],
        data_padding=payload[data_end:],
    )


def parse_asset_banks(rom: bytes, table_start: int) -> list[AssetBank]:
    """Parse the outer offset/size table that separates asset banks."""

    if table_start < 0 or table_start + 8 > len(rom):
        raise ValueError("asset table is outside the ROM")
    table_size = struct.unpack_from(">I", rom, table_start)[0]
    if table_size == 0 or table_size % 8 or table_start + table_size > len(rom):
        raise ValueError("asset table does not have a valid eight-byte entry span")

    banks: list[AssetBank] = []
    previous_end = table_start + table_size
    for index in range(table_size // 8):
        relative_start, size_flags = struct.unpack_from(">II", rom, table_start + index * 8)
        start = table_start + relative_start
        size = size_flags & 0x0FFFFFFF
        flags = size_flags >> 28
        end = start + size
        if size == 0 or start < previous_end or end > len(rom):
            raise ValueError(f"asset bank {index:02X} has an invalid range")
        banks.append(AssetBank(index=index, start=start, end=end, flags=flags))
        previous_end = end
    return banks


def parse_asset_entries(rom: bytes, bank: AssetBank) -> list[AssetEntry]:
    """Parse one bank's indexed compressed and uncompressed asset files."""

    if bank.flags:
        return []
    first_relative = struct.unpack_from(">I", rom, bank.start)[0]
    if first_relative == 0 or first_relative % 8 or bank.start + first_relative > bank.end:
        raise ValueError(f"asset bank {bank.index:02X} has an invalid inner table")

    entries: list[AssetEntry] = []
    previous_end = bank.start + first_relative
    for index in range(first_relative // 8):
        relative_start, length_flags = struct.unpack_from(">II", rom, bank.start + index * 8)
        length = length_flags & 0x0FFFFFFF
        type_flags = length_flags >> 24
        if length == 0:
            continue
        start = bank.start + relative_start
        end = start + length
        if start < previous_end or end > bank.end:
            raise ValueError(f"asset bank {bank.index:02X} entry {index} has an invalid range")
        entries.append(
            AssetEntry(
                index=index,
                start=start,
                end=end,
                type_flags=type_flags,
                compressed=bool(type_flags & 0x10),
            )
        )
        previous_end = end
    return entries
