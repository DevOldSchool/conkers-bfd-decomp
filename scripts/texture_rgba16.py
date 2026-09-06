"""Conservative direct-display-list RGBA16 texture contracts for the US ROM."""

from __future__ import annotations

import hashlib
import json
import struct
import zlib
from collections import Counter, defaultdict
from pathlib import Path

try:
    from scripts import texture_assets as t
except ModuleNotFoundError:
    import texture_assets as t


FAMILY = t.RGBA16_FAMILY
FAMILY_NAME = t.RGBA16_FAMILY_NAME
TEXTURE_IMAGE = 0xFD100000
RGBA_FORMAT = 0
BITS_16 = 2


def convert_row_layout(
    pixels: bytes, row_layout: str, width: int, height: int
) -> bytes:
    if row_layout not in t.ROW_LAYOUTS:
        raise ValueError(f"unsupported RGBA16 row layout: {row_layout}")
    if len(pixels) != width * height * 2:
        raise ValueError("RGBA16 pixel data has an invalid size")
    if row_layout == t.ROW_LAYOUT_LINEAR:
        return pixels
    row_size = width * 2
    converted = bytearray(pixels)
    for row_index in range(1, height, 2):
        row_start = row_index * row_size
        source = pixels[row_start : row_start + row_size]
        converted[row_start : row_start + row_size] = bytes(
            source[column ^ 4] for column in range(row_size)
        )
    return bytes(converted)


def flip_vertical(pixels: bytes, width: int, height: int, pixel_size: int) -> bytes:
    row_size = width * pixel_size
    if len(pixels) != row_size * height:
        raise ValueError("texture pixel data has an invalid size")
    return b"".join(
        pixels[offset : offset + row_size]
        for offset in range(row_size * (height - 1), -1, -row_size)
    )


def encode_png(
    payload: bytes, row_layout: str, width: int, height: int
) -> bytes:
    pixels = flip_vertical(
        convert_row_layout(payload, row_layout, width, height), width, height, 2
    )
    words = struct.unpack(f">{width * height}H", pixels)
    rgba = b"".join(
        bytes(
            (
                t.expand_5bit((value >> 11) & 0x1F),
                t.expand_5bit((value >> 6) & 0x1F),
                t.expand_5bit((value >> 1) & 0x1F),
                255 if value & 1 else 0,
            )
        )
        for value in words
    )
    return t.encode_rgba_png(width, height, rgba)


def decode_png(
    data: bytes, row_layout: str, width: int, height: int
) -> bytes:
    if not data.startswith(t.PNG_SIGNATURE):
        raise ValueError("texture file is not a PNG")
    chunks: dict[bytes, list[bytes]] = {}
    offset = len(t.PNG_SIGNATURE)
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
    if (png_width, png_height, depth, color_type) != (width, height, 8, 6):
        raise ValueError(f"texture PNG must be {width}x{height} RGBA at eight bits")
    if compression or filtering or interlace:
        raise ValueError("texture PNG uses unsupported encoding options")
    try:
        filtered = zlib.decompress(b"".join(chunks[b"IDAT"]))
    except (KeyError, zlib.error) as error:
        raise ValueError("PNG IDAT data is missing or invalid") from error
    rgba = t.unfilter_rows(
        filtered,
        width,
        height,
        bytes_per_row=width * 4,
        bytes_per_pixel=4,
    )
    words = []
    for pixel in range(0, len(rgba), 4):
        red, green, blue, alpha = rgba[pixel : pixel + 4]
        if alpha not in (0, 255):
            raise ValueError("PNG alpha is not representable as RGBA5551")
        words.append(
            (t.reduce_5bit(red) << 11)
            | (t.reduce_5bit(green) << 6)
            | (t.reduce_5bit(blue) << 1)
            | (1 if alpha else 0)
        )
    payload = struct.pack(f">{len(words)}H", *words)
    return convert_row_layout(
        flip_vertical(payload, width, height, 2), row_layout, width, height
    )


def scan_contracts(data: bytes, source: str, sizes: dict[int, int]) -> list[dict]:
    records = []
    for offset in range(0, len(data) - 7, 8):
        command, index = t.command_words(data, offset)
        if command != TEXTURE_IMAGE or index not in sizes:
            continue
        tile = bounds = loaded = dxt = None
        for cursor in range(offset + 8, min(len(data) - 7, offset + 0x100), 8):
            following, argument = t.command_words(data, cursor)
            opcode = following >> 24
            if opcode in (t.BRANCH_DISPLAY_LIST, t.END_DISPLAY_LIST, 0xFD):
                break
            if opcode == 0xF3 and loaded is None:
                loaded = (((argument >> 12) & 0xFFF) + 1) * 2
                dxt = argument & 0xFFF
            if t.is_render_tile(following, argument) and tile is None:
                tile = following
            if opcode == 0xF2 and (argument >> 24) & 7 == 0 and bounds is None:
                bounds = (following, argument)
        record = {
            "flat_index": index,
            "source": source,
            "offset": f"0x{offset:X}",
            "tile_command": f"0x{tile:08X}" if tile is not None else None,
            "loaded_bytes": loaded,
            "load_dxt": dxt,
        }
        reason = None
        if tile is None or bounds is None or loaded is None:
            reason = "incomplete-local-contract"
        elif t.tile_format_and_size(tile) != (RGBA_FORMAT, BITS_16):
            reason = "not-rgba16-render-tile"
        else:
            upper, lower = bounds
            uls, ult = (upper >> 12) & 0xFFF, upper & 0xFFF
            lrs, lrt = (lower >> 12) & 0xFFF, lower & 0xFFF
            if lrs < uls or lrt < ult or (lrs - uls) % 4 or (lrt - ult) % 4:
                reason = "noncanonical-tile-bounds-or-stride"
            else:
                width = (lrs - uls) // 4 + 1
                height = (lrt - ult) // 4 + 1
                record.update(
                    width=width,
                    height=height,
                    tile_bounds=[f"0x{upper:08X}", f"0x{lower:08X}"],
                )
                line_words = (tile >> 9) & 0x1FF
                if width != line_words * 4 or tile & 0x1FF:
                    reason = "noncanonical-tile-bounds-or-stride"
                elif loaded != width * height * 2:
                    reason = "partial-or-mismatched-load"
                elif dxt != 0:
                    reason = "unsupported-load-row-conversion"
                elif sizes[index] != loaded:
                    reason = "payload-size-disagrees-with-consumer"
        record["status"] = reason or "proven"
        records.append(record)
    return records


def consistent_contracts(references: list[dict]) -> list[dict]:
    proven = [record for record in references if record["status"] == "proven"]
    dimensions = {(record["width"], record["height"]) for record in proven}
    if len(dimensions) != 1 or any(
        record["status"] not in ("proven", "incomplete-local-contract")
        for record in references
    ):
        return []
    return proven


def survey(profile: str, rom_argument: Path | None):
    rom_path, layout = t.resolve_rom(profile, rom_argument)
    rom, source_order = t.normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(f"US normalized ROM SHA-1 mismatch: got {digest}")
    start, end = layout["flat_assets_start"], layout["flat_assets_end"]
    entries = list(t.iter_flat_rzip_entries(rom[start:end]))
    sizes = {entry.index: len(entry.data) for entry in entries}
    references = []
    for bank in t.parse_asset_banks(rom, layout["asset_table"]):
        if bank.flags:
            continue
        for entry in t.parse_asset_entries(rom, bank):
            raw = rom[entry.start : entry.end]
            decoded = t.decode_rzip_chunk(raw).data if entry.compressed else raw
            references.extend(
                scan_contracts(
                    decoded, f"bank-{bank.index:02X}/{entry.index:04d}", sizes
                )
            )
    grouped = defaultdict(list)
    for reference in references:
        grouped[reference["flat_index"]].append(reference)
    textures = []
    for index, candidates in sorted(grouped.items()):
        proven = consistent_contracts(candidates)
        if not proven:
            continue
        width, height = proven[0]["width"], proven[0]["height"]
        entry = entries[index]
        textures.append(
            {
                "flat_index": index,
                "width": width,
                "height": height,
                "rom_start": f"0x{start + entry.start:X}",
                "rom_end": f"0x{start + entry.end:X}",
                "decoded_size": len(entry.data),
                "decoded_sha1": hashlib.sha1(entry.data).hexdigest(),
                "pixel_encoding": "rgba5551-big-endian",
                "row_layout": t.ROW_LAYOUT_TMEM,
                "row_layout_evidence": "zero-dxt-tmem-ready-load",
                "preview_status": "runtime-appearance-not-verified",
                "references": proven,
                "file": f"{index:04d}.rgba16.png",
            }
        )
    manifest = {
        "schema_version": 7,
        "family": FAMILY,
        "profile": profile,
        "source_rom": t.manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": digest,
        "source_origin": t.SOURCE_ORIGIN,
        "png_origin": t.PNG_ORIGIN,
        "texture_count": len(textures),
        "textures": textures,
        "reference_count": len(references),
        "referenced_texture_count": len(grouped),
        "excluded_texture_count": len(grouped) - len(textures),
        "excluded_flat_indices": sorted(
            set(grouped) - {record["flat_index"] for record in textures}
        ),
        "reference_status_counts": dict(
            Counter(record["status"] for record in references)
        ),
        "survey_references": references,
        "classification": (
            "Direct local RGBA16 render dimensions, full zero-DXT load, "
            "and exact full-payload storage contracts"
        ),
        "visual_validation": {
            "status": "incomplete",
            "note": (
                "The display-list contract proves direct RGBA16 consumption and "
                "reversible storage. It does not assign semantic names or certify "
                "that every standalone PNG resembles finished artwork."
            ),
        },
    }
    return manifest, {entry.index: entry.data for entry in entries}


def extract(
    profile: str, rom_argument: Path | None, output: Path, force: bool
) -> dict:
    manifest, payloads = survey(profile, rom_argument)
    t.prepare_output(output, force)
    for record in manifest["textures"]:
        payload = payloads[record["flat_index"]]
        width, height = record["width"], record["height"]
        png = encode_png(payload, record["row_layout"], width, height)
        if decode_png(png, record["row_layout"], width, height) != payload:
            raise ValueError(f"RGBA16 texture {record['flat_index']} did not round-trip")
        (output / record["file"]).write_bytes(png)
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    return manifest


def verify(profile: str, rom_argument: Path | None) -> tuple[int, int]:
    manifest, payloads = survey(profile, rom_argument)
    size = 0
    for record in manifest["textures"]:
        payload = payloads[record["flat_index"]]
        width, height = record["width"], record["height"]
        rebuilt = decode_png(
            encode_png(payload, record["row_layout"], width, height),
            record["row_layout"],
            width,
            height,
        )
        if rebuilt != payload:
            raise ValueError(f"RGBA16 texture {record['flat_index']} did not round-trip")
        size += len(payload)
    return manifest["texture_count"], size
