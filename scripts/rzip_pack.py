#!/usr/bin/env python3
"""Rebuild the US flat RZIP stream from reviewed decoded asset overrides."""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import struct
import tempfile
import zlib
from dataclasses import dataclass
from pathlib import Path
from typing import Any

try:
    from scripts.rzip_archive import (
        decode_rzip_chunk,
        iter_flat_rzip_entries,
        normalize_rom,
    )
    from scripts.rzip_extract import ROOT, display_path, load_layout
except ModuleNotFoundError:
    from rzip_archive import (  # type: ignore[no-redef]
        decode_rzip_chunk,
        iter_flat_rzip_entries,
        normalize_rom,
    )
    from rzip_extract import ROOT, display_path, load_layout  # type: ignore[no-redef]


US_BOOTCODE_CRC32 = 0x98BC2C86
CIC_6105_SEED = 0xDF26F436
CHECKSUM_START = 0x1000
CHECKSUM_END = 0x101000
TEXTURE_FAMILY = "flat-ci4-64x64-rgba5551"
RECTANGULAR_TEXTURE_FAMILY = "flat-ci4-rectangular-proven-rgba5551"
TILED_VIEWS_TEXTURE_FAMILY = "flat-tiled-views-mixed-ci-rgba5551"
SUPPORTED_TEXTURE_PACKS = frozenset(
    (
        (3, TEXTURE_FAMILY),
        (4, RECTANGULAR_TEXTURE_FAMILY),
        (5, TILED_VIEWS_TEXTURE_FAMILY),
    )
)


@dataclass(frozen=True)
class PackResult:
    entry_count: int
    override_count: int
    changed_count: int
    original_stream_size: int
    rebuilt_stream_size: int
    capacity: int
    alignment_size: int
    crc1: int
    crc2: int
    sha1: str


def safe_input_file(input_dir: Path, filename: str) -> Path:
    relative = Path(filename)
    if relative.is_absolute() or ".." in relative.parts:
        raise ValueError(f"unsafe flat override path: {filename}")
    path = input_dir / relative
    if not path.is_file():
        raise ValueError(f"flat override file does not exist: {filename}")
    return path


def load_texture_overrides(input_dir: Path) -> dict[int, bytes]:
    manifest_path = input_dir / "manifest.json"
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    tiled_family = (
        manifest.get("schema_version"), manifest.get("family")
    ) == (5, TILED_VIEWS_TEXTURE_FAMILY)
    records = manifest.get("tiles" if tiled_family else "textures")
    if (
        (manifest.get("schema_version"), manifest.get("family"))
        not in SUPPORTED_TEXTURE_PACKS
        or manifest.get("profile") != "us"
        or manifest.get("source_origin") != "bottom-left"
        or manifest.get("png_origin") != "top-left"
        or not isinstance(records, list)
    ):
        raise ValueError("flat override manifest is not a supported texture pack")
    count_key = "tile_count" if tiled_family else "texture_count"
    if int(manifest.get(count_key, -1)) != len(records):
        raise ValueError("flat override count does not match its texture list")

    overrides: dict[int, bytes] = {}
    for record in records:
        flat_index = int(record["flat_index"])
        if flat_index < 0 or flat_index in overrides:
            raise ValueError(f"duplicate or invalid flat override index: {flat_index}")
        payload = safe_input_file(input_dir, record["file"]).read_bytes()
        if len(payload) != int(record["size"]):
            raise ValueError(f"flat override {flat_index} size does not match manifest")
        digest = hashlib.sha1(payload).hexdigest()
        if digest != record["sha1"]:
            raise ValueError(f"flat override {flat_index} SHA-1 does not match manifest")
        overrides[flat_index] = payload
    if list(overrides) != sorted(overrides):
        raise ValueError("flat override indices are not ordered")
    return overrides


def encode_rzip_chunk(payload: bytes) -> bytes:
    compressor = zlib.compressobj(level=9, wbits=-15)
    compressed = compressor.compress(payload) + compressor.flush()
    chunk = struct.pack(">I", len(payload)) + compressed
    decoded = decode_rzip_chunk(chunk)
    if decoded.data != payload or decoded.consumed != len(chunk):
        raise ValueError("new RZIP chunk did not validate after compression")
    return chunk


def rebuild_flat_region(
    rom: bytes, layout: dict[str, Any], overrides: dict[int, bytes]
) -> tuple[bytes, int, int, int]:
    flat_start = layout["flat_assets_start"]
    flat_end = layout["flat_assets_end"]
    table_start = layout["asset_table"]
    if not 0 <= flat_start < flat_end <= table_start <= len(rom):
        raise ValueError("configured flat RZIP range is outside the ROM")

    original_stream = rom[flat_start:flat_end]
    alignment_size = table_start - flat_end
    if alignment_size < 15:
        raise ValueError("flat RZIP region does not preserve the 15-byte loader gap")
    entries = list(iter_flat_rzip_entries(original_stream))
    if entries and entries[-1].end != len(original_stream):
        raise ValueError("flat RZIP entries do not consume the configured stream")
    if any(index >= len(entries) for index in overrides):
        raise ValueError("flat override index is outside the source stream")

    changed_count = 0
    chunks: list[bytes] = []
    for entry in entries:
        raw = original_stream[entry.start : entry.end]
        replacement = overrides.get(entry.index)
        if replacement is None or replacement == entry.data:
            chunks.append(raw)
            continue
        chunks.append(encode_rzip_chunk(replacement))
        changed_count += 1

    rebuilt_stream = b"".join(chunks)
    capacity = flat_end - flat_start
    if len(rebuilt_stream) > capacity:
        raise ValueError(
            f"rebuilt flat RZIP stream is {len(rebuilt_stream) - capacity} bytes too large"
        )

    if changed_count == 0:
        region = rom[flat_start:table_start]
    else:
        fixed_region_size = table_start - flat_start
        region = rebuilt_stream + bytes(fixed_region_size - len(rebuilt_stream))
    if len(region) != table_start - flat_start:
        raise ValueError("rebuilt flat RZIP region changed its fixed ROM span")

    rebuilt_entries = list(iter_flat_rzip_entries(region[: len(rebuilt_stream)]))
    if len(rebuilt_entries) != len(entries):
        raise ValueError("rebuilt flat RZIP stream changed its entry count")
    for original, rebuilt in zip(entries, rebuilt_entries):
        expected = overrides.get(original.index, original.data)
        if rebuilt.data != expected:
            raise ValueError(f"rebuilt flat entry {original.index} failed validation")
    return region, len(entries), changed_count, len(rebuilt_stream)


def rotate_left(value: int, amount: int) -> int:
    if amount == 0:
        return value
    return ((value << amount) | (value >> (32 - amount))) & 0xFFFFFFFF


def calculate_6105_checksum(rom: bytes) -> tuple[int, int]:
    if len(rom) < CHECKSUM_END:
        raise ValueError("ROM is too small for the N64 header checksum range")
    bootcode_crc = zlib.crc32(rom[0x40:0x1000]) & 0xFFFFFFFF
    if bootcode_crc != US_BOOTCODE_CRC32:
        raise ValueError(f"unsupported N64 bootcode CRC32: 0x{bootcode_crc:08X}")

    t1 = t2 = t3 = t4 = t5 = t6 = CIC_6105_SEED
    for offset in range(CHECKSUM_START, CHECKSUM_END, 4):
        value = struct.unpack_from(">I", rom, offset)[0]
        if t6 + value > 0xFFFFFFFF:
            t4 = (t4 + 1) & 0xFFFFFFFF
        t6 = (t6 + value) & 0xFFFFFFFF
        t3 ^= value
        rotated = rotate_left(value, value & 0x1F)
        t5 = (t5 + rotated) & 0xFFFFFFFF
        if t2 > value:
            t2 ^= rotated
        else:
            t2 ^= t6 ^ value
        boot_value = struct.unpack_from(">I", rom, 0x750 + (offset & 0xFF))[0]
        t1 = (t1 + (boot_value ^ value)) & 0xFFFFFFFF
    return t6 ^ t4 ^ t3, t5 ^ t2 ^ t1


def prepare_output_file(output: Path, source_rom: Path, force: bool) -> None:
    if output.resolve() == source_rom.resolve():
        raise ValueError("refusing to overwrite the source ROM")
    if output.exists():
        if not force:
            raise ValueError(
                f"output already exists: {display_path(output)}; pass --force to replace it"
            )
        if not output.is_file():
            raise ValueError(f"refusing to replace non-file output: {display_path(output)}")
    output.parent.mkdir(parents=True, exist_ok=True)


def write_output_atomic(output: Path, data: bytes) -> None:
    temporary_path: Path | None = None
    try:
        with tempfile.NamedTemporaryFile(
            dir=output.parent, prefix=f".{output.name}.", delete=False
        ) as temporary:
            temporary_path = Path(temporary.name)
            temporary.write(data)
            temporary.flush()
            os.fsync(temporary.fileno())
        os.replace(temporary_path, output)
    finally:
        if temporary_path is not None and temporary_path.exists():
            temporary_path.unlink()


def pack_rom(
    profile: str,
    rom_path: Path,
    input_dir: Path,
    output: Path,
    force: bool,
) -> PackResult:
    if profile != "us":
        raise ValueError("flat RZIP packing is currently supported only for US")
    prepare_output_file(output, rom_path, force)
    layout = load_layout(profile)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    if source_order != "z64":
        raise ValueError("US flat RZIP packing currently requires a big-endian Z64 ROM")
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(f"US normalized ROM SHA-1 mismatch: got {digest}")

    overrides = load_texture_overrides(input_dir)
    region, entry_count, changed_count, rebuilt_size = rebuild_flat_region(
        normalized, layout, overrides
    )
    flat_start = layout["flat_assets_start"]
    table_start = layout["asset_table"]
    rebuilt_rom = bytearray(normalized)
    rebuilt_rom[flat_start:table_start] = region

    if changed_count:
        crc1, crc2 = calculate_6105_checksum(rebuilt_rom)
        struct.pack_into(">II", rebuilt_rom, 0x10, crc1, crc2)
    else:
        crc1, crc2 = struct.unpack_from(">II", rebuilt_rom, 0x10)
        if bytes(rebuilt_rom) != normalized:
            raise ValueError("unchanged flat RZIP rebuild was not byte-identical")

    write_output_atomic(output, rebuilt_rom)
    return PackResult(
        entry_count=entry_count,
        override_count=len(overrides),
        changed_count=changed_count,
        original_stream_size=layout["flat_assets_end"] - flat_start,
        rebuilt_stream_size=rebuilt_size,
        capacity=layout["flat_assets_end"] - flat_start,
        alignment_size=table_start - layout["flat_assets_end"],
        crc1=crc1,
        crc2=crc2,
        sha1=hashlib.sha1(rebuilt_rom).hexdigest(),
    )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--profile", choices=("us",), default="us")
    parser.add_argument("--rom", type=Path)
    parser.add_argument("--input", type=Path, required=True)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--force", action="store_true")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        layout = load_layout(args.profile)
        default_rom = layout.get("default_rom")
        rom_path = args.rom or (ROOT / default_rom if default_rom else None)
        if rom_path is None:
            raise ValueError("--rom is required for the US profile")
        if not rom_path.is_absolute():
            rom_path = ROOT / rom_path
        if not rom_path.is_file():
            raise ValueError(f"ROM does not exist: {display_path(rom_path)}")
        input_dir = args.input if args.input.is_absolute() else ROOT / args.input
        output = args.output or ROOT / "build" / "rzip" / "us-packed.z64"
        if not output.is_absolute():
            output = ROOT / output
        result = pack_rom(args.profile, rom_path, input_dir, output, args.force)
    except (KeyError, OSError, TypeError, ValueError, json.JSONDecodeError) as error:
        print(f"error: {error}")
        return 1

    print(
        f"Packed US flat RZIP stream: {result.entry_count} entries, "
        f"{result.override_count} overrides, {result.changed_count} changed, "
        f"{result.rebuilt_stream_size}/{result.capacity} bytes, "
        f"loader gap={result.alignment_size} bytes"
    )
    print(
        f"ROM: {display_path(output)} "
        f"(CRC1={result.crc1:08X}, CRC2={result.crc2:08X}, SHA-1={result.sha1})"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
