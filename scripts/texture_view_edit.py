"""Import full-color view edits using the original per-tile palette indices."""

from __future__ import annotations

import hashlib
import struct
import zlib
from pathlib import Path
from typing import Any

try:
    from scripts import texture_assets as t
except ModuleNotFoundError:
    import texture_assets as t


def decode_view_png(data: bytes) -> bytes:
    """Read non-interlaced 8-bit RGB/RGBA, including all five PNG filters."""
    if not data.startswith(t.PNG_SIGNATURE):
        raise ValueError("view file is not a PNG")
    chunks: dict[bytes, list[bytes]] = {}
    offset = len(t.PNG_SIGNATURE)
    while offset < len(data):
        if offset + 12 > len(data):
            raise ValueError("view PNG chunk is truncated")
        size = struct.unpack_from(">I", data, offset)[0]
        kind = data[offset + 4:offset + 8]
        end = offset + size + 12
        if end > len(data):
            raise ValueError("view PNG chunk payload is truncated")
        payload = data[offset + 8:end - 4]
        crc = struct.unpack_from(">I", data, end - 4)[0]
        if zlib.crc32(kind + payload) & 0xFFFFFFFF != crc:
            raise ValueError("view PNG chunk CRC is invalid")
        if not chunks and kind != b"IHDR":
            raise ValueError("view PNG must begin with IHDR")
        if kind not in (b"IHDR", b"IDAT", b"IEND", b"PLTE") and not kind[0] & 32:
            raise ValueError("view PNG contains an unsupported critical chunk")
        chunks.setdefault(kind, []).append(payload)
        offset = end
        if kind == b"IEND":
            break
    if offset != len(data) or chunks.get(b"IEND") != [b""]:
        raise ValueError("view PNG must end with IEND")
    headers = chunks.get(b"IHDR", [])
    if len(headers) != 1 or len(headers[0]) != 13:
        raise ValueError("view PNG must contain one valid IHDR")
    width, height, depth, color, compression, filtering, interlace = struct.unpack(
        ">IIBBBBB", headers[0]
    )
    if (width, height, depth) != (t.TILED_VIEW_WIDTH, t.TILED_VIEW_HEIGHT, 8) or color not in (2, 6):
        raise ValueError("view PNG must be 360x360 RGB or RGBA at eight bits")
    if compression or filtering or interlace or b"tRNS" in chunks:
        raise ValueError("view PNG uses unsupported encoding; export non-interlaced RGBA")
    channels = 4 if color == 6 else 3
    expected = height * (width * channels + 1)
    stream = zlib.decompressobj()
    try:
        raw = stream.decompress(b"".join(chunks.get(b"IDAT", [])), expected + 1)
    except zlib.error as error:
        raise ValueError("view PNG has invalid compressed pixels") from error
    if len(raw) != expected or not stream.eof or stream.unused_data:
        raise ValueError("view PNG has invalid decompressed size or stream")
    pixels = t.unfilter_rows(raw, width, height, width * channels, channels)
    if channels == 3:
        pixels = b"".join(pixels[i:i + 3] + b"\xff" for i in range(0, len(pixels), 3))
    return pixels


def apply_view_edits(
    input_dir: Path, manifest: dict[str, Any], originals: dict[int, bytes]
) -> dict[int, bytes]:
    """Validate every input before returning new payloads; never modify sources."""
    records = {int(record["flat_index"]): record for record in manifest["tiles"]}
    for index, payload in originals.items():
        if hashlib.sha1(payload).hexdigest() != records[index].get("decoded_sha1"):
            raise ValueError(
                f"tile {index} was edited: --views requires original indexed tiles; "
                "pack tile edits without --views or use a fresh extraction for view edits"
            )
    views = manifest.get("views")
    if not isinstance(views, list) or not views or manifest.get("view_count") != len(views):
        raise ValueError("view manifest count is missing or invalid")
    result = {index: bytearray(payload) for index, payload in originals.items()}
    proposals: dict[tuple[int, int], int] = {}
    seen: set[tuple[int, int]] = set()
    for view in views:
        identity = (int(view["group_index"]), int(view["view_index"]))
        if identity in seen:
            raise ValueError("duplicate view in manifest")
        seen.add(identity)
        base = int(view["first_flat_index"])
        start = base - t.TILED_STREAM_PHASE
        if (
            view.get("continuous_stream_phase") != t.TILED_STREAM_PHASE
            or view.get("source_flat_index_start") != start
            or view.get("source_flat_index_end") != start + t.TILED_ENTRIES_PER_VIEW - 1
            or view.get("flat_index_order") != "column-major"
        ):
            raise ValueError("view assembly metadata is stale; re-extract tiled-views")
        pixels = decode_view_png(t.safe_manifest_file(input_dir, view["file"]).read_bytes())
        for position in range(t.TILED_ENTRIES_PER_VIEW):
            index = start + position
            if index not in originals:
                raise ValueError(f"view references missing tile {index}")
            record, payload = records[index], originals[index]
            if (record["storage_width"], record["storage_height"]) != (64, 32) or record["format"] not in ("ci4", "ci8"):
                raise ValueError(f"view tile {index} has unsupported dimensions or format")
            depth = 4 if record["format"] == "ci4" else 8
            pixel_size = 64 * 32 * depth // 8
            palette = payload[pixel_size:]
            colors = {}
            for slot, (word,) in enumerate(struct.iter_unpack(">H", palette)):
                rgba = bytes((t.expand_5bit(word >> 11), t.expand_5bit((word >> 6) & 31),
                              t.expand_5bit((word >> 1) & 31), 255 if word & 1 else 0))
                colors.setdefault(rgba, slot)
            source_rgba = t.indexed_payload_rgba(payload, depth, record["row_layout"])
            column, row = divmod(position, t.TILED_ROWS)
            for y in range(t.TILED_VISIBLE_HEIGHT):
                for x in range(t.TILED_VISIBLE_WIDTH):
                    source = (y * 64 + x) * 4
                    destination = ((row * 30 + y) * 360 + column * 60 + x) * 4
                    rgba = pixels[destination:destination + 4]
                    if rgba == source_rgba[source:source + 4]:
                        continue  # Retain the original index even for duplicate palette colors.
                    if rgba not in colors:
                        raise ValueError(
                            f"{view['file']}: pixel ({column * 60 + x}, {row * 30 + y}) "
                            f"is outside tile {index}'s palette; use that tile's existing colors"
                        )
                    slot = colors[rgba]
                    key = (index, y * 64 + x)
                    if key in proposals and proposals[key] != slot:
                        raise ValueError(f"conflicting view edits for shared tile {index}")
                    proposals[key] = slot
                    stored_y = 31 - y
                    byte_x = x * depth // 8
                    if record["row_layout"] == t.ROW_LAYOUT_TMEM and stored_y & 1:
                        byte_x ^= 4
                    address = stored_y * (64 * depth // 8) + byte_x
                    if depth == 8:
                        result[index][address] = slot
                    else:
                        shift = 4 if x % 2 == 0 else 0
                        result[index][address] = (result[index][address] & ~(15 << shift)) | (slot << shift)
    return {index: bytes(payload) for index, payload in result.items()}
