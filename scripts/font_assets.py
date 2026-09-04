#!/usr/bin/env python3
"""Extract and byte-identically rebuild Conker's grayscale RLE font table."""

from __future__ import annotations

import argparse
import hashlib
import json
from dataclasses import dataclass
from pathlib import Path
from typing import Any

try:
    from scripts.rzip_archive import normalize_rom
    from scripts.rzip_extract import ROOT, display_path, load_layout, manifest_source, prepare_output
except ModuleNotFoundError:
    from rzip_archive import normalize_rom  # type: ignore[no-redef]
    from rzip_extract import (  # type: ignore[no-redef]
        ROOT,
        display_path,
        load_layout,
        manifest_source,
        prepare_output,
    )


@dataclass(frozen=True)
class FontGlyph:
    codepoint: int
    width: int
    height: int
    metadata: bytes
    pixels: bytes
    encoded: bytes


def decode_pixels(width: int, height: int, encoded: bytes) -> bytes:
    if width <= 0 or height <= 0:
        raise ValueError("font dimensions must be positive")
    expected = width * height
    pixels = bytearray()
    for value in encoded:
        intensity = value & 0xF0
        run_length = (value & 0x0F) + 1
        pixels.extend([intensity] * run_length)
        if len(pixels) > expected:
            raise ValueError("font RLE expands beyond the declared dimensions")
    if len(pixels) != expected:
        raise ValueError(
            f"font RLE expands to {len(pixels)} pixels; expected {expected}"
        )
    return bytes(pixels)


def encode_pixels(width: int, height: int, pixels: bytes) -> bytes:
    if width <= 0 or height <= 0 or len(pixels) != width * height:
        raise ValueError("font pixels do not match the declared dimensions")
    if any(value & 0x0F for value in pixels):
        raise ValueError("font pixels must use four-bit grayscale intensities")

    encoded = bytearray()
    offset = 0
    while offset < len(pixels):
        run_length = 1
        while (
            run_length < 16
            and offset + run_length < len(pixels)
            and (offset + run_length) % width != 0
            and pixels[offset + run_length] == pixels[offset]
        ):
            run_length += 1
        encoded.append(pixels[offset] | (run_length - 1))
        offset += run_length
    return bytes(encoded)


def parse_font_table(
    rom: bytes, start: int, count: int, storage_end: int
) -> tuple[list[FontGlyph], int]:
    if not (0 <= start < storage_end <= len(rom)):
        raise ValueError("font table range is outside the ROM")

    glyphs: list[FontGlyph] = []
    offset = start
    for record_index in range(count):
        if offset + 8 > storage_end:
            raise ValueError(f"font record {record_index} header exceeds the table")
        width, height = rom[offset], rom[offset + 1]
        metadata = rom[offset + 2 : offset + 4]
        record_size = int.from_bytes(rom[offset + 4 : offset + 8], "big")
        if record_size < 8 or offset + record_size > storage_end:
            raise ValueError(f"font record {record_index} has an invalid size")
        encoded = rom[offset + 8 : offset + record_size]
        glyphs.append(
            FontGlyph(
                codepoint=0x30 + record_index,
                width=width,
                height=height,
                metadata=metadata,
                pixels=decode_pixels(width, height, encoded),
                encoded=encoded,
            )
        )
        offset += record_size

    padding = rom[offset:storage_end]
    if any(padding):
        raise ValueError("font table alignment padding is not zero-filled")
    return glyphs, len(padding)


def encode_glyph(glyph: FontGlyph) -> bytes:
    encoded = encode_pixels(glyph.width, glyph.height, glyph.pixels)
    return (
        bytes((glyph.width, glyph.height))
        + glyph.metadata
        + (8 + len(encoded)).to_bytes(4, "big")
        + encoded
    )


def encode_font_table(glyphs: list[FontGlyph], padding_size: int) -> bytes:
    if padding_size < 0:
        raise ValueError("font padding size cannot be negative")
    return b"".join(encode_glyph(glyph) for glyph in glyphs) + bytes(padding_size)


def write_pgm(path: Path, glyph: FontGlyph) -> None:
    path.write_bytes(
        f"P5\n{glyph.width} {glyph.height}\n255\n".encode("ascii") + glyph.pixels
    )


def read_pgm(path: Path, expected_width: int, expected_height: int) -> bytes:
    data = path.read_bytes()
    parts = data.split(b"\n", 3)
    if len(parts) != 4 or parts[0] != b"P5" or parts[2] != b"255":
        raise ValueError(f"unsupported PGM header: {display_path(path)}")
    try:
        width_text, height_text = parts[1].split()
        width = int(width_text)
        height = int(height_text)
    except (TypeError, ValueError) as error:
        raise ValueError(f"invalid PGM dimensions: {display_path(path)}") from error
    if (width, height) != (expected_width, expected_height):
        raise ValueError(
            f"PGM dimensions for {display_path(path)} are {width}x{height}; "
            f"expected {expected_width}x{expected_height}"
        )
    pixels = parts[3]
    if len(pixels) != width * height:
        raise ValueError(f"PGM pixel length is invalid: {display_path(path)}")
    return pixels


def resolve_rom(profile: str, rom_argument: Path | None) -> tuple[Path, dict[str, Any]]:
    layout = load_layout(profile)
    if rom_argument is None:
        default_rom = layout.get("default_rom")
        if not default_rom:
            raise ValueError(f"--rom is required for the {profile} profile")
        rom_path = ROOT / default_rom
    else:
        rom_path = rom_argument if rom_argument.is_absolute() else ROOT / rom_argument
    if not rom_path.is_file():
        raise ValueError(f"ROM does not exist: {display_path(rom_path)}")
    return rom_path, layout


def load_profile_fonts(
    profile: str, rom_argument: Path | None
) -> tuple[Path, bytes, str, dict[str, Any], list[FontGlyph], int]:
    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(
            f"{profile} normalized ROM SHA-1 mismatch: got {digest}; expected one of "
            + ", ".join(layout["normalized_sha1"])
        )
    glyphs, padding_size = parse_font_table(
        normalized,
        layout["font_start"],
        layout["font_count"],
        layout["font_storage_end"],
    )
    return rom_path, normalized, source_order, layout, glyphs, padding_size


def extract_fonts(
    profile: str, rom_argument: Path | None, output: Path, force: bool
) -> dict[str, Any]:
    rom_path, normalized, source_order, layout, glyphs, padding_size = load_profile_fonts(
        profile, rom_argument
    )
    prepare_output(output, force)

    records: list[dict[str, Any]] = []
    offset = layout["font_start"]
    for glyph in glyphs:
        filename = f"{glyph.codepoint:04X}.pgm"
        write_pgm(output / filename, glyph)
        record_size = 8 + len(glyph.encoded)
        records.append(
            {
                "codepoint": glyph.codepoint,
                "width": glyph.width,
                "height": glyph.height,
                "metadata": glyph.metadata.hex(),
                "rom_start": f"0x{offset:X}",
                "rom_end": f"0x{offset + record_size:X}",
                "record_size": record_size,
                "decoded_sha1": hashlib.sha1(glyph.pixels).hexdigest(),
                "file": filename,
            }
        )
        offset += record_size

    manifest = {
        "schema_version": 1,
        "profile": profile,
        "source_rom": manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": hashlib.sha1(normalized).hexdigest(),
        "font_start": f"0x{layout['font_start']:X}",
        "font_records_end": f"0x{offset:X}",
        "font_storage_end": f"0x{layout['font_storage_end']:X}",
        "record_count": len(records),
        "padding_size": padding_size,
        "glyphs": records,
    }
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    return manifest


def safe_manifest_file(input_dir: Path, filename: str) -> Path:
    relative = Path(filename)
    if relative.is_absolute() or relative.name != filename or ".." in relative.parts:
        raise ValueError(f"unsafe font manifest path: {filename}")
    return input_dir / relative


def pack_fonts(input_dir: Path, output: Path) -> bytes:
    manifest_path = input_dir / "manifest.json"
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    if manifest.get("schema_version") != 1 or not isinstance(manifest.get("glyphs"), list):
        raise ValueError("font manifest has an unsupported schema")
    if int(manifest.get("record_count", -1)) != len(manifest["glyphs"]):
        raise ValueError("font manifest record count does not match its glyph list")

    glyphs: list[FontGlyph] = []
    for record_index, record in enumerate(manifest["glyphs"]):
        codepoint = int(record["codepoint"])
        if codepoint != 0x30 + record_index:
            raise ValueError("font manifest glyphs are not in codepoint order")
        width = int(record["width"])
        height = int(record["height"])
        metadata = bytes.fromhex(record["metadata"])
        if len(metadata) != 2:
            raise ValueError("font metadata must contain exactly two bytes")
        pixels = read_pgm(
            safe_manifest_file(input_dir, record["file"]), width, height
        )
        glyphs.append(
            FontGlyph(
                codepoint=codepoint,
                width=width,
                height=height,
                metadata=metadata,
                pixels=pixels,
                encoded=b"",
            )
        )

    packed = encode_font_table(glyphs, int(manifest["padding_size"]))
    expected_size = int(manifest["font_storage_end"], 0) - int(
        manifest["font_start"], 0
    )
    if len(packed) != expected_size:
        raise ValueError(
            f"packed font table is {len(packed)} bytes; expected {expected_size}"
        )
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(packed)
    return packed


def verify_fonts(profile: str, rom_argument: Path | None) -> tuple[int, int]:
    _, normalized, _, layout, glyphs, padding_size = load_profile_fonts(
        profile, rom_argument
    )
    rebuilt = encode_font_table(glyphs, padding_size)
    original = normalized[layout["font_start"] : layout["font_storage_end"]]
    if rebuilt != original:
        raise ValueError(f"{profile} font table did not rebuild byte-identically")
    return len(glyphs), len(rebuilt)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    subparsers = parser.add_subparsers(dest="command", required=True)

    extract_parser = subparsers.add_parser("extract")
    extract_parser.add_argument("--profile", choices=("us", "debug", "ects"), default="us")
    extract_parser.add_argument("--rom", type=Path)
    extract_parser.add_argument("--output", type=Path)
    extract_parser.add_argument("--force", action="store_true")

    pack_parser = subparsers.add_parser("pack")
    pack_parser.add_argument("--input", type=Path, required=True)
    pack_parser.add_argument("--output", type=Path, required=True)

    verify_parser = subparsers.add_parser("verify")
    verify_parser.add_argument("--profile", choices=("us", "debug", "ects"), default="us")
    verify_parser.add_argument("--rom", type=Path)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        if args.command == "extract":
            output = args.output or (ROOT / "build" / "fonts" / args.profile)
            if not output.is_absolute():
                output = ROOT / output
            manifest = extract_fonts(args.profile, args.rom, output, args.force)
            print(
                f"Extracted {manifest['record_count']} {args.profile} font glyphs to "
                f"{display_path(output)}"
            )
        elif args.command == "pack":
            input_dir = args.input if args.input.is_absolute() else ROOT / args.input
            output = args.output if args.output.is_absolute() else ROOT / args.output
            packed = pack_fonts(input_dir, output)
            print(f"Packed {len(packed)} font bytes to {display_path(output)}")
        else:
            count, size = verify_fonts(args.profile, args.rom)
            print(f"Verified {args.profile} fonts: {count} glyphs, {size} bytes, byte-identical")
    except (KeyError, OSError, TypeError, ValueError, json.JSONDecodeError) as error:
        print(f"error: {error}")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
