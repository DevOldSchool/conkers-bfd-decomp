"""ROM character position targets consumed by func_1517AD00, indexed bank 13."""

from __future__ import annotations

import hashlib
import struct
from typing import Any

try:
    from scripts.rzip_archive import decode_rzip_chunk, parse_asset_banks, parse_asset_entries, parse_game_archive
except ModuleNotFoundError:
    from rzip_archive import decode_rzip_chunk, parse_asset_banks, parse_asset_entries, parse_game_archive


def verify_consumers(code: bytes, base: int, data: bytes, data_base: int) -> list[dict]:
    for address, size, expected in (
        (0x1517AD00, 2048, "a16226b408961566109c7c0088fd15ae34c76f1c"),
        (0x1503CF20, 1096, "2335fa3855313510f1f46512cfa704ab301814d1"),
        (0x150849A0, 44, "62d89a7ec36b39096dfd2c98896619b96b71866a"),
        (0x1502BD84, 352, "61e704387f12db65b320176ca0ba031df34ee228"),
    ):
        offset = address - base
        if offset < 0 or hashlib.sha1(code[offset:offset + size]).hexdigest() != expected:
            raise ValueError(f"ROM morph consumer changed at 0x{address:08X}")
    offset = 0x800A7230 - data_base
    table = data[offset:offset + 16] if offset >= 0 else b""
    if table != bytes.fromhex("00100151000C000C3A07006D00190018"):
        raise ValueError("ROM morph selector/count table changed")
    return [{"bank_entry": index, "character_entry": character, "shape_count": count,
             "part_vertex_counts": [first, second, third]}
            for index, (character, count, first, second, third)
            in enumerate(struct.iter_unpack(">BB3H", table))]


def children(data: bytes, count: int, *, compressed: bool) -> list[bytes]:
    """Walk a complete native pair table; reject overlaps and nonzero padding."""
    cursor = count * 8
    if count <= 0 or len(data) < cursor:
        raise ValueError("morph table is truncated")
    result = []
    for index in range(count):
        offset, flags = struct.unpack_from(">II", data, index * 8)
        size = flags & 0x0FFFFFFF
        expected_flags = (0x10000000 if compressed else 0) | (0x80000000 if index == count - 1 else 0)
        if flags & 0xF0000000 != expected_flags or not size:
            raise ValueError("morph table flags or child size changed")
        if offset < cursor or offset % 8 or offset + size > len(data) or offset - cursor >= 8:
            raise ValueError("morph child has invalid boundaries")
        if any(data[cursor:offset]):
            raise ValueError("morph child has unknown nonzero padding")
        raw = data[offset:offset + size]
        result.append(decode_rzip_chunk(raw).data if compressed else raw)
        cursor = offset + size
    if len(data) - cursor >= 8 or any(data[cursor:]):
        raise ValueError("morph table has an unknown tail")
    return result


def encode_part(part: dict) -> bytes:
    positions = part["positions"]
    if len(positions) != part["vertex_count"] or any(len(position) != 3 for position in positions):
        raise ValueError("morph part vertex count changed")
    payload = b"".join(struct.pack(">3h", *position) for position in positions)
    padding = part["padding_size"]
    if not 0 <= padding < 16 or (len(payload) + padding) % 16:
        raise ValueError("morph part padding is invalid")
    return payload + bytes(padding)


def parse_targets(data: bytes, model_data: bytes, geometry: Any, selector: dict) -> dict:
    counts = selector["part_vertex_counts"]
    offset, size = geometry.header_words[:2]
    if size != len(counts) * 4 or not offset or offset + size > len(model_data):
        raise ValueError("morph model vertex-boundary table changed")
    starts = struct.unpack_from(f">{len(counts)}I", model_data, offset)
    previous_end = 0
    for start, count in zip(starts, counts):
        if count <= 0 or start < previous_end or start + count > len(geometry.vertices):
            raise ValueError("morph part exceeds or overlaps the model vertex buffer")
        previous_end = start + count
    parts = [children(part, selector["shape_count"], compressed=True)
             for part in children(data, len(counts), compressed=False)]
    targets = []
    for shape in range(selector["shape_count"]):
        records = []
        for part_index, (start, count, values) in enumerate(zip(starts, counts, parts)):
            payload = values[shape]
            extent = count * 6
            if len(payload) < extent or len(payload) % 16 or len(payload) - extent >= 16 or any(payload[extent:]):
                raise ValueError("morph position payload has invalid extent or padding")
            positions = [list(position) for position in struct.iter_unpack(">3h", payload[:extent])]
            record = {"part": part_index, "first_vertex": start, "vertex_count": count,
                      "positions": positions, "padding_size": len(payload) - extent,
                      "decoded_size": len(payload), "sha1": hashlib.sha1(payload).hexdigest()}
            if encode_part(record) != payload:
                raise ValueError("morph positions failed decoded-byte reconstruction")
            if shape == 0 and positions != [[v.x, v.y, v.z] for v in geometry.vertices[start:start + count]]:
                raise ValueError("morph shape zero does not match its ROM model vertex ranges")
            records.append(record)
        targets.append({"shape_index": shape, "name": f"rom-shape-{shape:02d}", "parts": records})
    return {**selector, "model_sha1": hashlib.sha1(model_data).hexdigest(),
            "source_sha1": hashlib.sha1(data).hexdigest(), "source_size": len(data),
            "vertex_boundary_table_offset": offset, "vertex_starts": list(starts),
            "basis_status": "shape-zero-equals-ROM-model-positions", "targets": targets}


def load_manifest(rom: bytes, layout: dict, models: dict[int, tuple[bytes, Any]]) -> dict:
    game = parse_game_archive(rom[layout["game_start"]:layout["game_end"]])
    selectors = verify_consumers(game.code, int(layout["game_vram"]),
                                 game.data, int(layout["game_data_vram"]))
    bank = next((bank for bank in parse_asset_banks(rom, layout["asset_table"]) if bank.index == 0x13), None)
    if bank is None or bank.flags:
        raise ValueError("ROM morph bank is absent or changed")
    entries = parse_asset_entries(rom, bank)
    if [entry.index for entry in entries] != [record["bank_entry"] for record in selectors]:
        raise ValueError("ROM morph bank entry inventory changed")
    records = []
    for entry, selector in zip(entries, selectors):
        if entry.compressed:
            raise ValueError("ROM morph bank outer compression changed")
        model_data, geometry = models[selector["character_entry"]]
        records.append(parse_targets(rom[entry.start:entry.end], model_data, geometry, selector))
    leaves = [part for record in records for target in record["targets"] for part in target["parts"]]
    return {"schema_version": 1, "family": "ROM-character-position-morphs", "bank_index": 0x13,
            "normalized_sha1": hashlib.sha1(rom).hexdigest(), "model_count": len(records),
            "shape_count": sum(record["shape_count"] for record in records), "part_payload_count": len(leaves),
            "decoded_size": sum(part["decoded_size"] for part in leaves), "models": records,
            "runtime_evidence": {"loader_interpolator": "func_1517AD00", "model_loader": "func_1503CF20",
                                 "model_selector": "func_150849A0", "caller": "func_1502BD84",
                                 "selector_table": "0x800A7230"},
            "scope": "Stored XYZ endpoints. Runtime chooses shape IDs and transition duration; no timeline or expression names inferred. Native intermediate positions truncate to s16; glTF interpolation remains floating point. UV, colour, normal and joint fields are not modified by this consumer."}


def target_deltas(record: dict, geometry: Any) -> list[dict[int, tuple[int, int, int]]]:
    result = []
    for target in record["targets"]:
        values = {}
        for part in target["parts"]:
            start = part["first_vertex"]
            for index, position in enumerate(part["positions"], start):
                if index in values or not 0 <= index < len(geometry.vertices):
                    raise ValueError("morph target vertex index is invalid")
                vertex = geometry.vertices[index]
                values[index] = tuple(a - b for a, b in zip(position, (vertex.x, vertex.y, vertex.z)))
        result.append(values)
    return result
