"""Direct full-payload RGBA32, IA, and intensity texture contracts."""

from __future__ import annotations

import hashlib
import json
import struct
from collections import Counter, defaultdict
from pathlib import Path

try:
    from scripts import texture_assets as t
except ModuleNotFoundError:
    import texture_assets as t


FAMILY = t.NATIVE_FAMILY
FAMILY_NAME = t.NATIVE_FAMILY_NAME

FORMATS = {
    (0, 3): "rgba32",
    (3, 1): "ia8",
    (3, 2): "ia16",
    (4, 0): "i4",
    (4, 1): "i8",
}
IMAGE_COMMANDS = {
    0xFD180000: (0, 3),
    0xFD700000: (3, 2),
    0xFD900000: (4, 2),
}


def packed_row_size(texture_format: str, width: int) -> int:
    if texture_format == "i4":
        if width % 2:
            raise ValueError("I4 texture width must be even")
        return width // 2
    if texture_format in ("ia8", "i8"):
        return width
    if texture_format == "ia16":
        return width * 2
    if texture_format == "rgba32":
        return width * 4
    raise ValueError(f"unsupported native texture format: {texture_format}")


def convert_row_layout(
    payload: bytes, row_layout: str, texture_format: str, width: int, height: int
) -> bytes:
    if row_layout not in t.ROW_LAYOUTS:
        raise ValueError(f"unsupported texture row layout: {row_layout}")
    row_size = packed_row_size(texture_format, width)
    if len(payload) != row_size * height:
        raise ValueError(f"{texture_format} pixel data has an invalid size")
    if row_layout == t.ROW_LAYOUT_LINEAR:
        return payload
    # RGBA32 occupies paired 64-bit words in TMEM, so odd rows exchange the
    # eight-byte halves of each 16-byte group.  The narrower formats exchange
    # the four-byte halves of each eight-byte group instead.
    swap_mask = 8 if texture_format == "rgba32" else 4
    if row_size % (swap_mask * 2):
        raise ValueError(
            f"{texture_format} row size is not aligned for TMEM word swapping"
        )
    converted = bytearray(payload)
    for row_index in range(1, height, 2):
        row_start = row_index * row_size
        source = payload[row_start : row_start + row_size]
        converted[row_start : row_start + row_size] = bytes(
            source[column ^ swap_mask] for column in range(row_size)
        )
    return bytes(converted)


def flip_vertical(
    payload: bytes, texture_format: str, width: int, height: int
) -> bytes:
    row_size = packed_row_size(texture_format, width)
    if len(payload) != row_size * height:
        raise ValueError(f"{texture_format} pixel data has an invalid size")
    return b"".join(
        payload[offset : offset + row_size]
        for offset in range(row_size * (height - 1), -1, -row_size)
    )


def payload_to_rgba(payload: bytes, texture_format: str) -> bytes:
    if texture_format == "rgba32":
        return payload
    if texture_format == "ia16":
        return b"".join(
            bytes((payload[offset],) * 3 + (payload[offset + 1],))
            for offset in range(0, len(payload), 2)
        )
    if texture_format == "ia8":
        return b"".join(
            bytes(((value >> 4) * 17,) * 3 + ((value & 0xF) * 17,))
            for value in payload
        )
    if texture_format == "i8":
        return b"".join(bytes((value,) * 4) for value in payload)
    if texture_format == "i4":
        values = [nibble for value in payload for nibble in (value >> 4, value & 0xF)]
        return b"".join(bytes((value * 17,) * 4) for value in values)
    raise ValueError(f"unsupported native texture format: {texture_format}")


def rgba_to_payload(rgba: bytes, texture_format: str) -> bytes:
    if texture_format == "rgba32":
        return rgba
    values = []
    for offset in range(0, len(rgba), 4):
        red, green, blue, alpha = rgba[offset : offset + 4]
        if red != green or green != blue:
            raise ValueError(f"{texture_format} PNG must use grayscale RGB values")
        if texture_format == "ia16":
            values.extend((red, alpha))
        elif texture_format == "ia8":
            if red % 17 or alpha % 17:
                raise ValueError("IA8 PNG channels must be multiples of 17")
            values.append(((red // 17) << 4) | (alpha // 17))
        elif texture_format == "i8":
            if alpha != red:
                raise ValueError("I8 PNG alpha must equal its intensity")
            values.append(red)
        elif texture_format == "i4":
            if alpha != red or red % 17:
                raise ValueError("I4 PNG channels must contain one shared four-bit value")
            values.append(red // 17)
        else:
            raise ValueError(f"unsupported native texture format: {texture_format}")
    if texture_format == "i4":
        return bytes((values[index] << 4) | values[index + 1] for index in range(0, len(values), 2))
    return bytes(values)


def encode_png(
    payload: bytes,
    texture_format: str,
    row_layout: str,
    width: int,
    height: int,
) -> bytes:
    linear = flip_vertical(
        convert_row_layout(payload, row_layout, texture_format, width, height),
        texture_format,
        width,
        height,
    )
    return t.encode_rgba_png(width, height, payload_to_rgba(linear, texture_format))


def decode_png(
    data: bytes,
    texture_format: str,
    row_layout: str,
    width: int,
    height: int,
) -> bytes:
    rgba = t.decode_rgba_png_pixels(data, width, height)
    linear = rgba_to_payload(rgba, texture_format)
    return convert_row_layout(
        flip_vertical(linear, texture_format, width, height),
        row_layout,
        texture_format,
        width,
        height,
    )


def scan_contracts(data: bytes, source: str, sizes: dict[int, int]) -> list[dict]:
    records = []
    for offset in range(0, len(data) - 7, 8):
        image_command, index = t.command_words(data, offset)
        image_state = IMAGE_COMMANDS.get(image_command)
        if image_state is None or index not in sizes:
            continue
        tile = bounds = loaded_count = dxt = None
        for cursor in range(offset + 8, min(len(data) - 7, offset + 0x100), 8):
            command, argument = t.command_words(data, cursor)
            opcode = command >> 24
            if opcode in (t.BRANCH_DISPLAY_LIST, t.END_DISPLAY_LIST, 0xFD):
                break
            if opcode == 0xF3 and loaded_count is None:
                loaded_count = ((argument >> 12) & 0xFFF) + 1
                dxt = argument & 0xFFF
            if t.is_render_tile(command, argument) and tile is None:
                tile = command
            if opcode == 0xF2 and (argument >> 24) & 7 == 0 and bounds is None:
                bounds = (command, argument)
        record = {
            "flat_index": index,
            "source": source,
            "offset": f"0x{offset:X}",
            "image_command": f"0x{image_command:08X}",
            "tile_command": f"0x{tile:08X}" if tile is not None else None,
            "load_dxt": dxt,
        }
        reason = None
        tile_state = t.tile_format_and_size(tile) if tile is not None else None
        texture_format = FORMATS.get(tile_state)
        if tile is None or bounds is None or loaded_count is None:
            reason = "incomplete-local-contract"
        elif texture_format is None or image_state[0] != tile_state[0]:
            reason = "unsupported-native-render-tile"
        else:
            upper, lower = bounds
            uls, ult = (upper >> 12) & 0xFFF, upper & 0xFFF
            lrs, lrt = (lower >> 12) & 0xFFF, lower & 0xFFF
            if lrs < uls or lrt < ult or (lrs - uls) % 4 or (lrt - ult) % 4:
                reason = "noncanonical-tile-bounds-or-stride"
            else:
                width = (lrs - uls) // 4 + 1
                height = (lrt - ult) // 4 + 1
                row_size = packed_row_size(texture_format, width)
                line_bytes = width * 2 if texture_format == "rgba32" else row_size
                loaded_bytes = loaded_count * (4 if image_state[1] == 3 else 2)
                record.update(
                    format=texture_format,
                    width=width,
                    height=height,
                    loaded_bytes=loaded_bytes,
                    tile_bounds=[f"0x{upper:08X}", f"0x{lower:08X}"],
                )
                if line_bytes != ((tile >> 9) & 0x1FF) * 8 or tile & 0x1FF:
                    reason = "noncanonical-tile-bounds-or-stride"
                elif loaded_bytes != row_size * height:
                    reason = "partial-or-mismatched-load"
                elif dxt != 0:
                    reason = "unsupported-load-row-conversion"
                elif sizes[index] != loaded_bytes:
                    reason = "payload-size-disagrees-with-consumer"
        record["status"] = reason or "proven"
        records.append(record)
    return records


def consistent_contracts(references: list[dict]) -> list[dict]:
    proven = [record for record in references if record["status"] == "proven"]
    contracts = {
        (record["format"], record["width"], record["height"])
        for record in proven
    }
    if len(contracts) != 1 or any(
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
        texture_format = proven[0]["format"]
        width, height = proven[0]["width"], proven[0]["height"]
        entry = entries[index]
        textures.append(
            {
                "flat_index": index,
                "format": texture_format,
                "width": width,
                "height": height,
                "rom_start": f"0x{start + entry.start:X}",
                "rom_end": f"0x{start + entry.end:X}",
                "decoded_size": len(entry.data),
                "decoded_sha1": hashlib.sha1(entry.data).hexdigest(),
                "row_layout": t.ROW_LAYOUT_TMEM,
                "row_layout_evidence": "zero-dxt-tmem-ready-load",
                "preview_status": "runtime-appearance-not-verified",
                "references": proven,
                "file": f"{index:04d}.{texture_format}.png",
            }
        )
    manifest = {
        "schema_version": 8,
        "family": FAMILY,
        "profile": profile,
        "source_rom": t.manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": digest,
        "source_origin": t.SOURCE_ORIGIN,
        "png_origin": t.PNG_ORIGIN,
        "texture_count": len(textures),
        "textures": textures,
        "format_counts": dict(Counter(record["format"] for record in textures)),
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
            "Direct local native-color render dimensions, matching stride, full "
            "zero-DXT load, and exact full-payload storage contracts"
        ),
        "visual_validation": {
            "status": "incomplete",
            "note": (
                "The display-list contract proves each native pixel format and "
                "reversible storage; semantic names and finished-art appearance "
                "remain unclaimed."
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
        png = encode_png(
            payload,
            record["format"],
            record["row_layout"],
            record["width"],
            record["height"],
        )
        if decode_png(
            png,
            record["format"],
            record["row_layout"],
            record["width"],
            record["height"],
        ) != payload:
            raise ValueError(f"native texture {record['flat_index']} did not round-trip")
        (output / record["file"]).write_bytes(png)
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    return manifest


def verify(profile: str, rom_argument: Path | None) -> tuple[int, int]:
    manifest, payloads = survey(profile, rom_argument)
    size = 0
    for record in manifest["textures"]:
        payload = payloads[record["flat_index"]]
        rebuilt = decode_png(
            encode_png(
                payload,
                record["format"],
                record["row_layout"],
                record["width"],
                record["height"],
            ),
            record["format"],
            record["row_layout"],
            record["width"],
            record["height"],
        )
        if rebuilt != payload:
            raise ValueError(f"native texture {record['flat_index']} did not round-trip")
        size += len(payload)
    return manifest["texture_count"], size
