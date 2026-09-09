#!/usr/bin/env python3
"""Record structured model draw-state evidence from the Mupen debugger."""

from __future__ import annotations

import argparse
import base64
import hashlib
import json
import math
import os
import re
import selectors
import signal
import struct
import subprocess
import sys
import time
from pathlib import Path
from typing import Any


SCHEMA = "conker.model-draw-state-trace/v1"
MODEL_BANKS = (0x01, 0x03, 0x04, 0x09)
CHARACTER_POOL_ADDRESS = 0x800CC2D0
CHARACTER_POOL_RECORD_SIZE = 0x32C
CHARACTER_POOL_RECORD_COUNT = 25
CHARACTER_POOL_SIZE = CHARACTER_POOL_RECORD_SIZE * CHARACTER_POOL_RECORD_COUNT
CHARACTER_PART_TABLE_RECORD_COUNT = 188
CHARACTER_PART_POINTER_TABLE_SIZE = CHARACTER_PART_TABLE_RECORD_COUNT * 4
CHARACTER_PART_COUNT_TABLE_SIZE = CHARACTER_PART_TABLE_RECORD_COUNT * 2
PROMPT = b"(dbg) "
REGISTER_RE = re.compile(
    r"(?:\$)?(?P<name>r0|at|v[01]|a[0-3]|t[0-9]|s[0-7]|sB|k[01]|gp|sp|ra)\s+"
    r"(?P<value>[0-9A-Fa-f]+)"
)
BREAKPOINT_RE = re.compile(r"BPT:\s+0x([0-9A-Fa-f]+)\s+executed")
ADDRESS_EXPR_RE = re.compile(
    r"^(?:0x(?P<fixed>[0-9A-Fa-f]{1,16})|\$(?P<register>[A-Za-z][A-Za-z0-9]*))"
    r"(?P<offset>[+-](?:0x[0-9A-Fa-f]+|[0-9]+))?$"
)
REGISTER_NAMES = {
    "r0",
    "at",
    "v0",
    "v1",
    "a0",
    "a1",
    "a2",
    "a3",
    "t0",
    "t1",
    "t2",
    "t3",
    "t4",
    "t5",
    "t6",
    "t7",
    "t8",
    "t9",
    "k0",
    "k1",
    "s0",
    "s1",
    "s2",
    "s3",
    "s4",
    "s5",
    "s6",
    "s7",
    "sB",
    "gp",
    "sp",
    "ra",
}


class TraceError(RuntimeError):
    pass


def parse_int(value: Any, label: str) -> int:
    if isinstance(value, bool):
        raise TraceError(f"{label} must be an integer")
    if isinstance(value, int):
        return value
    if isinstance(value, str):
        try:
            return int(value, 0)
        except ValueError as error:
            raise TraceError(f"{label} must be an integer") from error
    raise TraceError(f"{label} must be an integer")


def validate_address_expression(expression: str) -> None:
    match = ADDRESS_EXPR_RE.fullmatch(expression)
    if not match:
        raise TraceError(f"unsupported address expression: {expression!r}")
    register = match.group("register")
    if register is not None and register not in REGISTER_NAMES:
        raise TraceError(f"unknown register in address expression: ${register}")


def validate_memory_value_source(
    source: Any,
    label: str,
    probe_max_lengths: dict[str, int],
) -> dict[str, Any]:
    if not isinstance(source, dict) or source.get("source") != "memory":
        raise TraceError(f"{label} must select a previously captured memory probe")
    source_name = source.get("name")
    if source_name not in probe_max_lengths:
        raise TraceError(f"{label} uses unavailable memory probe {source_name!r}")
    size = parse_int(source.get("size", 4), f"{label}.size")
    if size not in {1, 2, 4, 8}:
        raise TraceError(f"{label}.size must be 1, 2, 4, or 8")
    endian = source.get("endian", "big")
    if endian not in {"big", "little"}:
        raise TraceError(f"{label}.endian must be big or little")
    offset = parse_int(source.get("offset", 0), f"{label}.offset")
    if offset < 0 or offset + size > probe_max_lengths[source_name]:
        raise TraceError(f"{label} reads outside memory probe {source_name}")
    if "shift" in source and parse_int(source["shift"], f"{label}.shift") < 0:
        raise TraceError(f"{label}.shift cannot be negative")
    if "mask" in source:
        parse_int(source["mask"], f"{label}.mask")
    return source


def validate_spec(spec: dict[str, Any]) -> dict[str, Any]:
    if spec.get("schema_version") != 1:
        raise TraceError("trace spec schema_version must be 1")
    name = spec.get("name")
    if not isinstance(name, str) or not name.strip():
        raise TraceError("trace spec name must be a non-empty string")
    breakpoints = spec.get("breakpoints")
    if not isinstance(breakpoints, list) or not breakpoints:
        raise TraceError("trace spec must contain at least one breakpoint")
    seen_names: set[str] = set()
    for index, breakpoint in enumerate(breakpoints):
        if not isinstance(breakpoint, dict):
            raise TraceError(f"breakpoints[{index}] must be an object")
        breakpoint_name = breakpoint.get("name")
        if not isinstance(breakpoint_name, str) or not breakpoint_name:
            raise TraceError(f"breakpoints[{index}].name must be non-empty")
        if breakpoint_name in seen_names:
            raise TraceError(f"duplicate breakpoint name: {breakpoint_name}")
        seen_names.add(breakpoint_name)
        address = parse_int(breakpoint.get("address"), f"{breakpoint_name}.address")
        if not 0 <= address <= 0xFFFFFFFF:
            raise TraceError(f"{breakpoint_name}.address is outside guest address space")
        flags = parse_int(breakpoint.get("flags", 8), f"{breakpoint_name}.flags")
        if flags <= 0 or flags & ~0xE:
            raise TraceError(f"{breakpoint_name}.flags must use debugger READ/WRITE/EXEC bits")
        if not isinstance(breakpoint.get("stop_after_capture", False), bool):
            raise TraceError(f"{breakpoint_name}.stop_after_capture must be boolean")
        stop_after_capture_count = breakpoint.get("stop_after_capture_count")
        if stop_after_capture_count is not None:
            stop_after_capture_count = parse_int(
                stop_after_capture_count,
                f"{breakpoint_name}.stop_after_capture_count",
            )
            if not 1 <= stop_after_capture_count <= 100000:
                raise TraceError(
                    f"{breakpoint_name}.stop_after_capture_count must be between 1 and 100000"
                )
            if breakpoint.get("stop_after_capture", False):
                raise TraceError(
                    f"{breakpoint_name} cannot combine stop_after_capture with "
                    "stop_after_capture_count"
                )
        probes = breakpoint.get("memory", [])
        if not isinstance(probes, list):
            raise TraceError(f"{breakpoint_name}.memory must be an array")
        probe_names: set[str] = set()
        probe_max_lengths: dict[str, int] = {}
        for probe_index, probe in enumerate(probes):
            if not isinstance(probe, dict):
                raise TraceError(f"{breakpoint_name}.memory[{probe_index}] must be an object")
            probe_name = probe.get("name")
            if not isinstance(probe_name, str) or not re.fullmatch(r"[A-Za-z0-9_-]+", probe_name):
                raise TraceError(f"{breakpoint_name}.memory[{probe_index}].name is invalid")
            if probe_name in probe_names:
                raise TraceError(f"duplicate memory probe name: {probe_name}")
            expression = probe.get("address")
            if isinstance(expression, str):
                validate_address_expression(expression)
            else:
                validate_memory_value_source(
                    expression,
                    f"{probe_name}.address",
                    probe_max_lengths,
                )
                address_map = expression.get("map", "direct")
                if address_map not in {"direct", "physical", "kseg0", "kseg1"}:
                    raise TraceError(f"{probe_name}.address.map is invalid")
                if "add" in expression:
                    parse_int(expression["add"], f"{probe_name}.address.add")
            length_source = probe.get("length")
            if isinstance(length_source, dict):
                validate_memory_value_source(
                    length_source,
                    f"{probe_name}.length",
                    probe_max_lengths,
                )
                max_length = parse_int(
                    length_source.get("max", 0x10000),
                    f"{probe_name}.length.max",
                )
                if not 1 <= max_length <= 0x10000:
                    raise TraceError(
                        f"{probe_name}.length.max must be between 1 and 65536"
                    )
            else:
                max_length = parse_int(length_source, f"{probe_name}.length")
                if not 1 <= max_length <= 0x10000:
                    raise TraceError(f"{probe_name}.length must be between 1 and 65536")
            probe_names.add(probe_name)
            probe_max_lengths[probe_name] = max_length
        fields = breakpoint.get("fields", {})
        if not isinstance(fields, dict):
            raise TraceError(f"{breakpoint_name}.fields must be an object")
        conditions = breakpoint.get("when", [])
        if not isinstance(conditions, list):
            raise TraceError(f"{breakpoint_name}.when must be an array")
        sources: list[tuple[str, dict[str, Any]]] = list(fields.items())
        for condition_index, condition in enumerate(conditions):
            if not isinstance(condition, dict) or "equals" not in condition:
                raise TraceError(f"{breakpoint_name}.when[{condition_index}] must contain equals")
            sources.append((f"{breakpoint_name}.when[{condition_index}]", condition))
        for destination, source in sources:
            if not isinstance(destination, str) or not re.fullmatch(
                r"(?:segments|texture|rdp|colours|joint_matrices|model)(?:\.[A-Za-z0-9_-]+)+",
                destination,
            ) and not destination.startswith(f"{breakpoint_name}.when["):
                raise TraceError(f"unsupported state field path: {destination!r}")
            if not isinstance(source, dict) or source.get("source") not in {"register", "memory"}:
                raise TraceError(f"{destination} must select a register or memory source")
            source_name = source.get("name")
            if source["source"] == "register":
                if source_name not in REGISTER_NAMES:
                    raise TraceError(f"{destination} uses unknown register {source_name!r}")
            elif source_name not in probe_names:
                raise TraceError(f"{destination} uses unknown memory probe {source_name!r}")
            if "shift" in source and parse_int(source["shift"], f"{destination}.shift") < 0:
                raise TraceError(f"{destination}.shift cannot be negative")
            if "mask" in source:
                parse_int(source["mask"], f"{destination}.mask")
            if "equals" in source:
                parse_int(source["equals"], f"{destination}.equals")
            if source["source"] == "memory":
                size = parse_int(source.get("size", 4), f"{destination}.size")
                if size not in {1, 2, 4, 8}:
                    raise TraceError(f"{destination}.size must be 1, 2, 4, or 8")
                endian = source.get("endian", "big")
                if endian not in {"big", "little"}:
                    raise TraceError(f"{destination}.endian must be big or little")
                offset = parse_int(source.get("offset", 0), f"{destination}.offset")
                probe = next(item for item in probes if item["name"] == source_name)
                probe_length = probe["length"]
                probe_max_length = (
                    parse_int(probe_length.get("max", 0x10000), "probe.length.max")
                    if isinstance(probe_length, dict)
                    else parse_int(probe_length, "probe.length")
                )
                if offset < 0 or offset + size > probe_max_length:
                    raise TraceError(f"{destination} reads outside memory probe {source_name}")
        decoder = breakpoint.get("decoder")
        if decoder is not None:
            if not isinstance(decoder, dict) or decoder.get("format") not in {
                "f3dex2-cbfd",
                "cbfd-character-pool",
                "cbfd-character-draw-range",
            }:
                raise TraceError(f"{breakpoint_name}.decoder format is unsupported")
            decoder_format = decoder["format"]
            decoder_memory = decoder.get("memory")
            if decoder_format == "cbfd-character-draw-range":
                if not isinstance(decoder_memory, str) or not re.fullmatch(
                    r"[A-Za-z0-9_-]+", decoder_memory
                ):
                    raise TraceError(
                        f"{breakpoint_name}.decoder memory name is invalid"
                    )
                if decoder_memory in probe_names:
                    raise TraceError(
                        f"{breakpoint_name}.decoder dynamic memory name conflicts with a probe"
                    )
                entry_breakpoint = decoder.get("entry_breakpoint")
                if not isinstance(entry_breakpoint, str) or not entry_breakpoint:
                    raise TraceError(
                        f"{breakpoint_name}.decoder entry_breakpoint is required"
                    )
                max_bytes = parse_int(
                    decoder.get("max_bytes", 0x10000),
                    f"{breakpoint_name}.decoder.max_bytes",
                )
                if not 8 <= max_bytes <= 0x10000 or max_bytes % 8:
                    raise TraceError(
                        f"{breakpoint_name}.decoder.max_bytes must be an 8-byte multiple up to 65536"
                    )
            elif decoder_memory not in probe_names:
                raise TraceError(f"{breakpoint_name}.decoder uses an unknown memory probe")
            if decoder.get("format") == "cbfd-character-pool":
                source_name = decoder["memory"]
                if probe_max_lengths[source_name] != CHARACTER_POOL_SIZE:
                    raise TraceError(
                        f"{breakpoint_name}.decoder requires a {CHARACTER_POOL_SIZE}-byte "
                        "character-pool probe"
                    )
                capture_part_tables = decoder.get(
                    "capture_character_part_tables", False
                )
                if not isinstance(capture_part_tables, bool):
                    raise TraceError(
                        f"{breakpoint_name}.decoder.capture_character_part_tables "
                        "must be boolean"
                    )
                if capture_part_tables:
                    for option, expected_size in (
                        ("part_pointer_table", CHARACTER_PART_POINTER_TABLE_SIZE),
                        ("part_count_table", CHARACTER_PART_COUNT_TABLE_SIZE),
                        (
                            "extra_part_pointer_table",
                            CHARACTER_PART_POINTER_TABLE_SIZE,
                        ),
                    ):
                        probe_name = decoder.get(option)
                        if probe_name not in probe_max_lengths:
                            raise TraceError(
                                f"{breakpoint_name}.decoder.{option} uses an unknown "
                                "memory probe"
                            )
                        if probe_max_lengths[probe_name] != expected_size:
                            raise TraceError(
                                f"{breakpoint_name}.decoder.{option} requires an "
                                f"exactly {expected_size}-byte probe"
                            )
                continue
            walk = decoder.get("walk_nested", False)
            if not isinstance(walk, bool):
                raise TraceError(f"{breakpoint_name}.decoder.walk_nested must be boolean")
            max_nested_lists = parse_int(
                decoder.get("max_nested_lists", 64),
                f"{breakpoint_name}.decoder.max_nested_lists",
            )
            max_nested_bytes = parse_int(
                decoder.get("max_nested_bytes", 0x10000),
                f"{breakpoint_name}.decoder.max_nested_bytes",
            )
            if not 1 <= max_nested_lists <= 1024:
                raise TraceError(
                    f"{breakpoint_name}.decoder.max_nested_lists must be between 1 and 1024"
                )
            if not 8 <= max_nested_bytes <= 0x10000 or max_nested_bytes % 8:
                raise TraceError(
                    f"{breakpoint_name}.decoder.max_nested_bytes must be an 8-byte multiple up to 65536"
                )
            capture_matrices = decoder.get("capture_matrices", False)
            if not isinstance(capture_matrices, bool):
                raise TraceError(
                    f"{breakpoint_name}.decoder.capture_matrices must be boolean"
                )
            matrix_format = decoder.get("matrix_format", "n64-mtx")
            if matrix_format not in {"n64-mtx", "cbfd-character-f32"}:
                raise TraceError(
                    f"{breakpoint_name}.decoder.matrix_format must be "
                    "n64-mtx or cbfd-character-f32"
                )
            max_matrices = parse_int(
                decoder.get("max_matrices", 128),
                f"{breakpoint_name}.decoder.max_matrices",
            )
            if not 1 <= max_matrices <= 1024:
                raise TraceError(
                    f"{breakpoint_name}.decoder.max_matrices must be between 1 and 1024"
                )
            capture_lights = decoder.get("capture_lights", False)
            if not isinstance(decoder.get("capture_vertices", False), bool):
                raise TraceError(f"{breakpoint_name}.decoder.capture_vertices must be boolean")
            if not 1 <= parse_int(decoder.get("max_vertex_blocks", 512), "max_vertex_blocks") <= 4096:
                raise TraceError("max_vertex_blocks must be between 1 and 4096")
            if not isinstance(capture_lights, bool):
                raise TraceError(
                    f"{breakpoint_name}.decoder.capture_lights must be boolean"
                )
            max_lights = parse_int(
                decoder.get("max_lights", 128),
                f"{breakpoint_name}.decoder.max_lights",
            )
            if not 1 <= max_lights <= 1024:
                raise TraceError(
                    f"{breakpoint_name}.decoder.max_lights must be between 1 and 1024"
                )
            capture_normals = decoder.get("capture_normals", False)
            if not isinstance(capture_normals, bool):
                raise TraceError(
                    f"{breakpoint_name}.decoder.capture_normals must be boolean"
                )
            max_normal_streams = parse_int(
                decoder.get("max_normal_streams", 128),
                f"{breakpoint_name}.decoder.max_normal_streams",
            )
            if not 1 <= max_normal_streams <= 1024:
                raise TraceError(
                    f"{breakpoint_name}.decoder.max_normal_streams must be between 1 and 1024"
                )
    max_events = parse_int(spec.get("max_events", 1), "max_events")
    max_breakpoint_hits = parse_int(
        spec.get("max_breakpoint_hits", max_events * 1000), "max_breakpoint_hits"
    )
    timeout = parse_int(spec.get("timeout_seconds", 120), "timeout_seconds")
    if not 1 <= max_events <= 100000:
        raise TraceError("max_events must be between 1 and 100000")
    if not 1 <= timeout <= 3600:
        raise TraceError("timeout_seconds must be between 1 and 3600")
    if not max_events <= max_breakpoint_hits <= 1000000:
        raise TraceError("max_breakpoint_hits must cover max_events and cannot exceed 1000000")
    if not isinstance(spec.get("model_correlation", False), bool):
        raise TraceError("model_correlation must be boolean")
    if not isinstance(spec.get("model_inventory_digest", False), bool):
        raise TraceError("model_inventory_digest must be boolean")
    return spec


def parse_registers(output: str) -> dict[str, int]:
    registers: dict[str, int] = {}
    clean = re.sub(r"\x1b\[[0-9;]*m", "", output)
    for match in REGISTER_RE.finditer(clean):
        registers[match.group("name")] = int(match.group("value"), 16) & 0xFFFFFFFFFFFFFFFF
    if len(registers) != 32:
        raise TraceError(f"debugger returned {len(registers)} registers instead of 32")
    return registers


def resolve_address(expression: str, registers: dict[str, int]) -> int:
    match = ADDRESS_EXPR_RE.fullmatch(expression)
    if match is None:
        raise TraceError(f"unsupported address expression: {expression!r}")
    if match.group("fixed") is not None:
        value = int(match.group("fixed"), 16)
    else:
        register = match.group("register")
        if register not in registers:
            raise TraceError(f"register ${register} was not captured")
        value = registers[register]
    offset = match.group("offset")
    if offset:
        sign = -1 if offset[0] == "-" else 1
        value += sign * int(offset[1:], 0)
    return value & 0xFFFFFFFF


def resolve_probe_address(
    source: str | dict[str, Any],
    registers: dict[str, int],
    memory: dict[str, bytes],
) -> int:
    if isinstance(source, str):
        return resolve_address(source, registers)
    value = extract_value(source, registers, memory)
    address_map = source.get("map", "direct")
    if address_map == "physical":
        value &= 0x1FFFFFFF
    elif address_map == "kseg0":
        value = (value & 0x1FFFFFFF) | 0x80000000
    elif address_map == "kseg1":
        value = (value & 0x1FFFFFFF) | 0xA0000000
    value += parse_int(source.get("add", 0), "probe address add")
    return value & 0xFFFFFFFF


def resolve_probe_length(
    source: int | str | dict[str, Any],
    registers: dict[str, int],
    memory: dict[str, bytes],
) -> int:
    if not isinstance(source, dict):
        return parse_int(source, "probe length")
    length = extract_value(source, registers, memory)
    max_length = parse_int(source.get("max", 0x10000), "probe length max")
    if not 1 <= length <= max_length:
        raise TraceError(f"resolved probe length {length} is outside 1..{max_length}")
    return length


def extract_value(source: dict[str, Any], registers: dict[str, int], memory: dict[str, bytes]) -> int:
    if source["source"] == "register":
        value = registers[source["name"]]
    else:
        data = memory[source["name"]]
        offset = parse_int(source.get("offset", 0), "field offset")
        size = parse_int(source.get("size", 4), "field size")
        value = int.from_bytes(data[offset : offset + size], source.get("endian", "big"))
    value >>= parse_int(source.get("shift", 0), "field shift")
    if "mask" in source:
        value &= parse_int(source["mask"], "field mask")
    return value


def set_path(root: dict[str, Any], path: str, value: Any) -> None:
    parts = path.split(".")
    current: dict[str, Any] = root
    for part in parts[:-1]:
        child = current.get(part)
        if not isinstance(child, dict):
            child = {}
            current[part] = child
        current = child
    current[parts[-1]] = value


def default_state() -> dict[str, Any]:
    return {
        "segments": {},
        "texture": {
            "flat_id": None,
            "mode": None,
            "resolved_source_address": None,
            "resolved_pixel_address": None,
            "resolved_tlut_address": None,
        },
        "rdp": {
            "tiles": [],
            "tmem": [],
            "combine_mode": None,
            "convert_mode": None,
            "other_mode": None,
            "geometry_mode": 0,
        },
        "colours": {
            "primitive": None,
            "environment": None,
            "alpha": None,
        },
        "model": {},
        "joint_matrices": [],
        "rsp_lights": [],
        "rsp_normal_streams": [],
        "rdp_texture_images": [],
    }


def decode_cbfd_character_pool(data: bytes) -> dict[str, Any]:
    """Decode the 25 live 0x32C-byte character records rooted at D_800CC2D0."""

    if len(data) != CHARACTER_POOL_SIZE:
        raise TraceError(
            f"CBFD character pool must be exactly {CHARACTER_POOL_SIZE} bytes"
        )
    active_records: list[dict[str, Any]] = []
    for slot in range(CHARACTER_POOL_RECORD_COUNT):
        offset = slot * CHARACTER_POOL_RECORD_SIZE
        record = data[offset : offset + CHARACTER_POOL_RECORD_SIZE]
        owner_address = int.from_bytes(record[0:4], "big")
        if owner_address == 0:
            continue
        active_records.append(
            {
                "slot": slot,
                "record_offset": offset,
                "record_address": CHARACTER_POOL_ADDRESS + offset,
                "owner_address": owner_address,
                "entry": record[4],
                "flags": record[0xAC],
                "animation_state_address": int.from_bytes(record[0x144:0x148], "big"),
            }
        )
    return {
        "character_pool_address": CHARACTER_POOL_ADDRESS,
        "record_size": CHARACTER_POOL_RECORD_SIZE,
        "record_count": CHARACTER_POOL_RECORD_COUNT,
        "active_record_count": len(active_records),
        "active_entries": sorted({record["entry"] for record in active_records}),
        "active_records": active_records,
    }


def decode_cbfd_character_part_table_headers(
    pointer_data: bytes,
    count_data: bytes,
    extra_pointer_data: bytes,
) -> list[dict[str, Any]]:
    """Decode the renderer's 188 model-indexed part-table headers."""

    if len(pointer_data) != CHARACTER_PART_POINTER_TABLE_SIZE:
        raise TraceError("CBFD character part pointer table has the wrong size")
    if len(count_data) != CHARACTER_PART_COUNT_TABLE_SIZE:
        raise TraceError("CBFD character part count table has the wrong size")
    if len(extra_pointer_data) != CHARACTER_PART_POINTER_TABLE_SIZE:
        raise TraceError("CBFD character extra-part pointer table has the wrong size")
    pointers = struct.unpack(f">{CHARACTER_PART_TABLE_RECORD_COUNT}I", pointer_data)
    counts = struct.unpack(f">{CHARACTER_PART_TABLE_RECORD_COUNT}H", count_data)
    extra_pointers = struct.unpack(
        f">{CHARACTER_PART_TABLE_RECORD_COUNT}I", extra_pointer_data
    )
    return [
        {
            "model_index": index,
            "part_count": counts[index],
            "part_pointer_table_address": pointers[index] or None,
            "extra_part_pointer_table_address": extra_pointers[index] or None,
        }
        for index in range(CHARACTER_PART_TABLE_RECORD_COUNT)
        if counts[index] or pointers[index] or extra_pointers[index]
    ]


def state_hash(state: dict[str, Any]) -> str:
    encoded = json.dumps(state, sort_keys=True, separators=(",", ":")).encode("utf-8")
    return hashlib.sha256(encoded).hexdigest()


def rgba(value: int) -> list[int]:
    return [(value >> shift) & 0xFF for shift in (24, 16, 8, 0)]


def signed_16(value: int) -> int:
    return value - 0x10000 if value & 0x8000 else value


def update_cbfd_coord_mod(values: list[float | None], command: int, argument: int) -> None:
    """Replay F3DEX2CBFD_CoordMod's six effective MoveWord writes."""

    if command & 8:
        return
    index = (command >> 1) & 3
    position = command & 0x30
    high = (argument >> 16) & 0xFFFF
    low = argument & 0xFFFF
    if position == 0:
        values[index] = float(signed_16(high))
        values[index + 1] = float(signed_16(low))
    elif position == 0x10:
        values[4 + index] = high / 65536.0
        values[5 + index] = low / 65536.0
        base_a = values[index]
        base_b = values[index + 1]
        values[12 + index] = None if base_a is None else base_a + high / 65536.0
        values[13 + index] = None if base_b is None else base_b + low / 65536.0
    elif position == 0x20:
        values[8 + index] = float(signed_16(high))
        values[9 + index] = float(signed_16(low))


def triangle_count(opcode: int) -> int:
    if opcode == 0x05:
        return 1
    if opcode == 0x06:
        return 2
    if 0x10 <= opcode <= 0x1F:
        return 4
    return 0


def triangle_cache_indices(command: int, argument: int) -> list[list[int]]:
    """Decode the cache slots consumed by supported CBFD triangle commands."""

    opcode = command >> 24
    if opcode in (0x05, 0x06):
        words = [command] if opcode == 0x05 else [command, argument]
        return [[(word >> shift) & 0x7F for shift in (17, 9, 1)] for word in words]
    if 0x10 <= opcode <= 0x1F:
        return [
            [(command >> 23) & 31, (command >> 18) & 31,
             ((command >> 15) & 7) * 4 + (argument >> 30)],
            [(command >> shift) & 31 for shift in (10, 5, 0)],
            [(argument >> shift) & 31 for shift in (25, 20, 15)],
            [(argument >> shift) & 31 for shift in (10, 5, 0)],
        ]
    return []


def resolve_runtime_matrix_address(
    address: int,
    segments: dict[str, int] | None = None,
) -> int | None:
    if 0x80000000 <= address <= 0xBFFFFFFF:
        return address
    if address >> 24 == 0:
        return address | 0x80000000
    segment = address >> 24
    segment_base = (segments or {}).get(str(segment))
    if segment_base is not None:
        resolved = (segment_base + (address & 0xFFFFFF)) & 0xFFFFFFFF
        if resolved < 0x20000000:
            resolved |= 0x80000000
        return resolved
    return None


def geometry_clusters(data: bytes) -> list[dict[str, Any]]:
    """Return address-normalized vertex-load plus triangle command clusters."""

    clusters: list[dict[str, Any]] = []
    vertex_command: tuple[int, int, int] | None = None
    active: dict[str, Any] | None = None
    face_index = 0

    def finish() -> None:
        nonlocal active
        if active is None:
            return
        encoded = json.dumps(active["commands"], separators=(",", ":")).encode("ascii")
        active["signature"] = hashlib.sha256(encoded).hexdigest()
        clusters.append(active)
        active = None

    for command_index, (command, argument) in enumerate(struct.iter_unpack(">II", data)):
        opcode = command >> 24
        if opcode == 0x01:
            finish()
            vertex_command = (command_index * 8, command, 0)
            continue
        count = triangle_count(opcode)
        if not count:
            finish()
            # State commands and returning from a called display list do not
            # invalidate the RSP vertex cache. Triangles can resume without VTX.
            continue
        if active is None:
            if vertex_command is None:
                face_index += count
                continue
            active = {
                "command_offset": vertex_command[0],
                "triangle_command_offset": command_index * 8,
                "commands": [[vertex_command[1], vertex_command[2]]],
                "first_face": face_index,
                "triangle_count": 0,
            }
        active["commands"].append([command, argument])
        active["triangle_end_offset"] = (command_index + 1) * 8
        active["triangle_count"] += count
        face_index += count
    finish()
    return clusters


def public_geometry_cluster(cluster: dict[str, Any]) -> dict[str, Any]:
    return {
        "command_offset": cluster["command_offset"],
        "triangle_command_offset": cluster["triangle_command_offset"],
        "triangle_end_offset": cluster["triangle_end_offset"],
        "command_count": len(cluster["commands"]),
        "first_face": cluster["first_face"],
        "triangle_count": cluster["triangle_count"],
        "signature": cluster["signature"],
    }


def load_model_cluster_index() -> list[dict[str, Any]]:
    index: list[dict[str, Any]] = []
    for bank in MODEL_BANKS:
        root = Path(f"build/assets/models/us-bank-{bank:02x}")
        manifest_path = root / "manifest.json"
        if not manifest_path.is_file():
            raise TraceError(
                f"model correlation requires {manifest_path}; extract bank {bank:02x} first"
            )
        manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
        for bundle in manifest.get("bundles", []):
            entry = parse_int(bundle.get("bank_entry"), "bundle.bank_entry")
            for segment in bundle.get("segments", []):
                geometry = segment.get("geometry")
                if not isinstance(geometry, dict):
                    continue
                segment_index = parse_int(segment.get("index"), "segment.index")
                payload_path = root / "bundles" / f"{entry:04d}" / f"segment-{segment_index:02d}.bin"
                if not payload_path.is_file():
                    raise TraceError(f"model correlation requires {payload_path}")
                payload = payload_path.read_bytes()
                display_offset = parse_int(
                    geometry.get("display_list_offset"),
                    "geometry.display_list_offset",
                )
                display_size = parse_int(
                    geometry.get("display_list_size"),
                    "geometry.display_list_size",
                )
                if display_offset < 0 or display_size <= 0 or display_offset + display_size > len(payload):
                    raise TraceError(f"invalid display-list bounds in {payload_path}")
                material_runs = geometry.get("material_runs", [])
                for cluster_index, cluster in enumerate(
                    geometry_clusters(payload[display_offset : display_offset + display_size])
                ):
                    cluster_end = cluster["first_face"] + cluster["triangle_count"]
                    material_run = next(
                        (
                            run
                            for run in material_runs
                            if parse_int(run.get("first_face"), "material_run.first_face")
                            <= cluster["first_face"]
                            and cluster_end
                            <= parse_int(run.get("first_face"), "material_run.first_face")
                            + parse_int(run.get("face_count"), "material_run.face_count")
                        ),
                        None,
                    )
                    if material_run is None:
                        raise TraceError(
                            f"geometry cluster {cluster_index} is outside material runs in {manifest_path}"
                        )
                    index.append(
                        {
                            "bank": bank,
                            "entry": entry,
                            "segment": segment_index,
                            "model_sha1": segment.get("sha1"),
                            "static_cluster_index": cluster_index,
                            "static_first_face": cluster["first_face"],
                            "commands": cluster["commands"],
                            "triangle_count": cluster["triangle_count"],
                            "material_run": {
                                key: material_run.get(key)
                                for key in (
                                    "index",
                                    "first_face",
                                    "face_count",
                                    "pixel",
                                    "palette",
                                    "runtime_render_state_offset",
                                    "matrix_index",
                                )
                            },
                        }
                    )
    return index


def load_model_inventory_digest() -> str:
    digests = set()
    for bank in MODEL_BANKS:
        path = Path(f"build/assets/models/us-bank-{bank:02x}/manifest.json")
        if not path.is_file():
            raise TraceError(f"model correlation requires {path}")
        manifest = json.loads(path.read_text(encoding="utf-8"))
        digest = manifest.get("normalized_sha1")
        if not isinstance(digest, str):
            raise TraceError(f"model manifest has no ROM digest: {path}")
        digests.add(digest)
    if len(digests) != 1:
        raise TraceError("model correlation manifests belong to different ROMs")
    return digests.pop()


def correlate_model_clusters(
    runtime_clusters: list[dict[str, Any]],
    model_cluster_index: list[dict[str, Any]],
) -> list[dict[str, Any]]:
    correlations: list[dict[str, Any]] = []
    for runtime_index, cluster in enumerate(runtime_clusters):
        commands = cluster["commands"]
        candidates = []
        for candidate in model_cluster_index:
            static_commands = candidate["commands"]
            if len(commands) > len(static_commands) or commands != static_commands[: len(commands)]:
                continue
            candidates.append(
                {
                    **{key: candidate[key] for key in (
                        "bank", "entry", "segment", "model_sha1",
                        "static_cluster_index", "static_first_face", "material_run",
                    )},
                    # A matched prefix proves only the captured triangles.
                    "triangle_count": cluster["triangle_count"],
                }
            )
        unique_models = {candidate["model_sha1"] for candidate in candidates}
        if not candidates:
            status = "unmatched"
        elif len(candidates) == 1:
            status = "unique"
        elif len(unique_models) == 1:
            status = "equivalent-aliases"
        else:
            status = "ambiguous"
        correlations.append(
            {
                "runtime_cluster_index": runtime_index,
                **public_geometry_cluster(cluster),
                "status": status,
                "candidate_count": len(candidates),
                "unique_model_count": len(unique_models),
                "candidates": candidates,
            }
        )
    return correlations


def runtime_texture_address(draw_run: dict[str, Any], role: str) -> int | None:
    image = draw_run["state"]["texture"].get(f"{role}_image")
    return image.get("address") if isinstance(image, dict) else None


def correlate_material_runs(
    draw_runs: list[dict[str, Any]],
    model_correlations: list[dict[str, Any]],
) -> list[dict[str, Any]]:
    """Attach proven static material identities and flat IDs to runtime draws."""

    results: list[dict[str, Any]] = []
    for correlation in model_correlations:
        start = correlation.get("triangle_command_offset", correlation["command_offset"] + 8)
        end = correlation.get(
            "triangle_end_offset",
            correlation["command_offset"] + correlation["command_count"] * 8,
        )
        draw_run_indices = [
            index
            for index, draw_run in enumerate(draw_runs)
            if start <= draw_run["command_offset"] < end
        ]
        if not draw_run_indices:
            continue
        candidates = [
            {
                "bank": candidate["bank"],
                "entry": candidate["entry"],
                "segment": candidate["segment"],
                "model_sha1": candidate.get("model_sha1"),
                "material_run": candidate["material_run"],
            }
            for candidate in correlation["candidates"]
        ]
        unique_materials = {
            json.dumps(candidate["material_run"], sort_keys=True, separators=(",", ":"))
            for candidate in candidates
        }
        if len(candidates) == 1:
            status = "unique"
            resolved = candidates[0]
            common_material = candidates[0]["material_run"]
        elif candidates and len(unique_materials) == 1:
            status = "equivalent-material-aliases"
            resolved = None
            common_material = candidates[0]["material_run"]
        elif candidates:
            status = "ambiguous"
            resolved = None
            common_material = None
        else:
            status = "unmatched"
            resolved = None
            common_material = None
        first_draw = draw_runs[draw_run_indices[0]]
        result: dict[str, Any] = {
            "runtime_cluster_index": correlation["runtime_cluster_index"],
            "draw_run_indices": draw_run_indices,
            "status": status,
            "candidates": candidates,
            "runtime_texture": {
                "pixel_address": runtime_texture_address(first_draw, "pixel"),
                "tlut_address": runtime_texture_address(first_draw, "palette"),
            },
            "resolved": resolved,
            "common_material": common_material,
        }
        if common_material is not None:
            result["texture_join"] = {
                "pixel": {
                    "runtime_address": result["runtime_texture"]["pixel_address"],
                    "static": common_material.get("pixel"),
                },
                "palette": {
                    "runtime_address": result["runtime_texture"]["tlut_address"],
                    "static": common_material.get("palette"),
                },
            }
            matrix_state = first_draw["state"].get("matrix")
            runtime_matrix_slot = (
                matrix_state.get("matrix_slot")
                if isinstance(matrix_state, dict)
                else None
            )
            static_matrix_slot = common_material.get("matrix_index")
            result["matrix_slot"] = {
                "runtime": runtime_matrix_slot,
                "static": static_matrix_slot,
                "matches": (
                    runtime_matrix_slot == static_matrix_slot
                    if runtime_matrix_slot is not None and static_matrix_slot is not None
                    else None
                ),
            }
        result_index = len(results)
        results.append(result)
        for draw_run_index in draw_run_indices:
            draw_runs[draw_run_index]["runtime_cluster_index"] = correlation[
                "runtime_cluster_index"
            ]
            draw_runs[draw_run_index]["material_correlation_index"] = result_index
    return results


def decode_f3dex2_cbfd(
    data: bytes,
    model_cluster_index: list[dict[str, Any]] | None = None,
) -> dict[str, Any]:
    """Decode exact state transitions present in one submitted CBFD command buffer."""

    if not data or len(data) % 8:
        raise TraceError("F3DEX2 CBFD command buffer must be a non-empty multiple of 8 bytes")
    segments: dict[str, int] = {}
    tiles: dict[int, dict[str, int]] = {}
    tile_bounds: dict[int, list[int]] = {}
    tmem: list[dict[str, Any]] = []
    nested_display_lists: list[dict[str, int]] = []
    matrix_commands: list[dict[str, int]] = []
    light_commands: list[dict[str, int | None]] = []
    normal_commands: list[dict[str, int | None]] = []
    draw_runs: list[dict[str, Any]] = []
    vertex_loads: list[dict[str, Any]] = []
    vertex_cache: dict[int, int] = {}
    model_view_stack: list[list[dict[str, Any]] | None] = [None]
    projection_chain: list[dict[str, Any]] | None = None
    color_image: dict[str, Any] | None = None
    opcode_counts: dict[str, int] = {}
    texture_enabled = False
    texture_scale: list[int] | None = None
    pending_image: dict[str, Any] | None = None
    pixel_image: dict[str, Any] | None = None
    palette_image: dict[str, Any] | None = None
    combine_mode: list[int] | None = None
    convert_mode: list[int] | None = None
    other_mode: list[int] | None = None
    primitive: dict[str, Any] | None = None
    environment: dict[str, Any] | None = None
    matrix: dict[str, int] | None = None
    geometry_mode = 0
    geometry_mode_known_bits = 0
    num_lights: int | None = None
    num_lights_raw: int | None = None
    light_slots: dict[int, dict[str, int | None]] = {}
    normal_base: dict[str, int | None] | None = None
    coord_mod: list[float | None] = [None] * 16
    advanced_lighting = False
    end_count = 0

    def vertex_state() -> dict[str, Any]:
        return {
            "matrix": matrix,
            "model_view_chain": model_view_stack[-1],
            "projection_chain": projection_chain,
            "geometry_mode": geometry_mode,
            "lighting_enabled": bool(geometry_mode & 0x00020000),
            "lighting_enabled_known": bool(geometry_mode_known_bits & 0x00020000),
            "lights": {
                "num_lights": num_lights,
                "num_lights_raw": num_lights_raw,
                "advanced_lighting": advanced_lighting,
                "coordinate_modifiers": list(coord_mod),
                "slots": [dict(light_slots[i]) for i in sorted(light_slots)],
            },
            "normal_base": dict(normal_base) if normal_base is not None else None,
        }

    for command_index, (command, argument) in enumerate(struct.iter_unpack(">II", data)):
        opcode = command >> 24
        opcode_key = f"0x{opcode:02X}"
        opcode_counts[opcode_key] = opcode_counts.get(opcode_key, 0) + 1
        command_offset = command_index * 8
        if opcode == 0xDB:
            move_word_index = (command >> 16) & 0xFF
            if move_word_index == 0x06:
                segment = (command & 0xFFFF) // 4
                if segment < 16:
                    segments[str(segment)] = argument
            elif move_word_index == 0x02:
                num_lights_raw = argument
                num_lights = argument // 48 if argument % 48 == 0 else None
            elif move_word_index == 0x10:
                update_cbfd_coord_mod(coord_mod, command, argument)
        elif opcode == 0xDE:
            nested_display_lists.append(
                {
                    "command_offset": command_offset,
                    "command": command,
                    "address": argument,
                    "resolved_address": resolve_runtime_matrix_address(
                        argument, segments
                    ),
                }
            )
        elif opcode == 0xDA:
            encoded_segment = argument >> 24
            segmented = (
                argument < 0x80000000
                and encoded_segment != 0
                and str(encoded_segment) in segments
            )
            segment_offset = argument & 0xFFFFFF if segmented else None
            segment_base_address = (
                segments[str(encoded_segment)] if segmented else None
            )
            segment_relative_matrix_slot = (
                segment_offset // 0x40
                if segment_offset is not None and segment_offset % 0x40 == 0
                else None
            )
            matrix_command = {
                "command_offset": command_offset,
                "command": command,
                "address": argument,
                "resolved_address": resolve_runtime_matrix_address(argument, segments),
                "segment": encoded_segment if segmented else None,
                "segment_offset": segment_offset,
                "segment_base_address": segment_base_address,
                "segment_relative_matrix_slot": segment_relative_matrix_slot,
                # Compatibility alias. This is relative to the segment base in
                # force when the command executes, not necessarily to a whole
                # character matrix palette: segment 3 may be rebound to an
                # interior palette address between display-list calls.
                "matrix_slot": segment_relative_matrix_slot,
            }
            matrix_commands.append(matrix_command)
            # F3DEX2 flips the encoded PUSH bit before interpreting the flags.
            parameters = (command & 0xFF) ^ 1
            if parameters & ~7 or (command & 0xFFFFFF00) != 0xDA380000:
                model_view_stack = [None]
                projection_chain = None
                matrix = None
            elif parameters & 4:
                projection_chain = (
                    [matrix_command] if parameters & 2
                    else projection_chain + [matrix_command]
                    if projection_chain is not None else None
                )
            else:
                if parameters & 1:
                    model_view_stack.append(model_view_stack[-1])
                previous = model_view_stack[-1]
                model_view_stack[-1] = (
                    [matrix_command] if parameters & 2
                    else previous + [matrix_command] if previous is not None else None
                )
                matrix = matrix_command
        elif opcode == 0xD8:
            count = argument // 64
            if command == 0xD8380002 and argument % 64 == 0 and 0 < count < len(model_view_stack):
                del model_view_stack[-count:]
                chain = model_view_stack[-1]
                matrix = chain[-1] if chain else None
            else:
                model_view_stack = [None]
                matrix = None
        elif opcode == 0x01:
            count = (command >> 12) & 0xFF
            first = ((command >> 1) & 0x7F) - count
            if count and 0 <= first < first + count <= 128:
                load_index = len(vertex_loads)
                vertex_loads.append({
                    "command_offset": command_offset,
                    "command": command,
                    "address": argument,
                    "resolved_address": resolve_runtime_matrix_address(argument, segments),
                    "first_cache_index": first,
                    "vertex_count": count,
                    "state": vertex_state(),
                })
                for slot in range(first, first + count):
                    vertex_cache[slot] = load_index
            else:
                vertex_cache.clear()
        elif opcode == 0x02:
            # A cached vertex modification is not a fresh source vertex load.
            vertex_cache.pop((command & 0xFFFF) // 2, None)
        elif opcode == 0xDC and (command & 0xFF) == 0x0A:
            cbfd_offset = (command >> 5) & 0x3FFF
            cbfd_index = cbfd_offset // 48 if cbfd_offset % 48 == 0 else None
            encoded_segment = argument >> 24
            segmented = (
                argument < 0x80000000
                and encoded_segment != 0
                and str(encoded_segment) in segments
            )
            light = {
                "command_offset": command_offset,
                "command": command,
                "address": argument,
                "resolved_address": resolve_runtime_matrix_address(argument, segments),
                "cbfd_offset": cbfd_offset,
                "cbfd_index": cbfd_index,
                "light_slot": (
                    cbfd_index - 2
                    if cbfd_index is not None and cbfd_index >= 2
                    else None
                ),
                "segment": encoded_segment if segmented else None,
                "segment_offset": argument & 0xFFFFFF if segmented else None,
            }
            light_commands.append(light)
            if light["light_slot"] is not None:
                light_slots[int(light["light_slot"])] = light
        elif opcode == 0xDC and (command & 0xFF) == 0x0E:
            encoded_segment = argument >> 24
            segmented = (
                argument < 0x80000000
                and encoded_segment != 0
                and str(encoded_segment) in segments
            )
            normal_base = {
                "command_offset": command_offset,
                "command": command,
                "address": argument,
                "resolved_address": resolve_runtime_matrix_address(
                    argument, segments
                ),
                "segment": encoded_segment if segmented else None,
                "segment_offset": argument & 0xFFFFFF if segmented else None,
            }
            normal_commands.append(normal_base)
        elif opcode == 0xD9:
            geometry_mode = (
                geometry_mode & (command & 0x00FFFFFF)
            ) | argument
            geometry_mode_known_bits = (
                (geometry_mode_known_bits & command) | (~command & 0x00FFFFFF) | argument
            )
        elif opcode == 0xD7:
            texture_enabled = bool(command & 2)
            texture_scale = [command, argument]
        elif opcode == 0xFD:
            pending_image = {
                "command": command,
                "address": argument,
                "resolved_address": resolve_runtime_matrix_address(
                    argument, segments
                ),
            }
        elif opcode == 0xFF:
            color_image = {
                "command_offset": command_offset,
                "command": command,
                "address": argument,
                "resolved_address": resolve_runtime_matrix_address(argument, segments),
                "format": (command >> 21) & 7,
                "size": (command >> 19) & 3,
                "width": (command & 0xFFF) + 1,
            }
        elif opcode == 0xF5:
            tile_index = (argument >> 24) & 7
            tiles[tile_index] = {
                "index": tile_index,
                "command": command,
                "argument": argument,
                "tmem_word": (command >> 9) & 0x1FF,
            }
        elif opcode == 0xF2:
            tile_bounds[(argument >> 24) & 7] = [command, argument]
        elif opcode == 0xF3:
            pixel_image = runtime_texture_image_record(
                pending_image, command, argument, "pixels"
            )
            tmem.append(
                {
                    "command_offset": command_offset,
                    "role": "pixels",
                    "image": pixel_image,
                    "load_command": [command, argument],
                }
            )
        elif opcode == 0xF0:
            palette_image = runtime_texture_image_record(
                pending_image, command, argument, "tlut"
            )
            tmem.append(
                {
                    "command_offset": command_offset,
                    "role": "tlut",
                    "image": palette_image,
                    "load_command": [command, argument],
                }
            )
        elif opcode == 0xFC:
            combine_mode = [command, argument]
        elif opcode == 0xEC:
            convert_mode = [command, argument]
        elif opcode == 0xEF:
            other_mode = [command, argument]
        elif opcode == 0xFA:
            primitive = {"command": command, "rgba": rgba(argument)}
        elif opcode == 0xFB:
            environment = {"command": command, "rgba": rgba(argument)}
        elif opcode == 0xDD:
            advanced_lighting = True
        elif opcode == 0xDF:
            end_count += 1

        command_triangle_count = triangle_count(opcode)
        if command_triangle_count:
            material_state = {
                "color_image": color_image,
                "segments": dict(segments),
                "texture": {
                    "enabled": texture_enabled,
                    "scale": texture_scale,
                    "pixel_image": pixel_image,
                    "palette_image": palette_image,
                },
                "tiles": [tiles[index] for index in sorted(tiles)],
                "tile_bounds": {str(index): bounds for index, bounds in tile_bounds.items()},
                "combine_mode": combine_mode,
                "convert_mode": convert_mode,
                "other_mode": other_mode,
                "geometry_mode": geometry_mode,
                "lighting_enabled": bool(geometry_mode & 0x00020000),
                "lights": {
                    "num_lights": num_lights,
                    "num_lights_raw": num_lights_raw,
                    "advanced_lighting": advanced_lighting,
                    "coordinate_modifiers": list(coord_mod),
                    "slots": [
                        dict(light_slots[index]) for index in sorted(light_slots)
                    ],
                },
                "normal_base": dict(normal_base) if normal_base is not None else None,
                "colours": {
                    "primitive": primitive,
                    "environment": environment,
                    "alpha": primitive["rgba"][3] if primitive is not None else None,
                },
                "matrix": matrix,
            }
            draw_runs.append(
                {
                    "command_offset": command_offset,
                    "opcode": opcode,
                    "triangle_count": command_triangle_count,
                    "material_state_hash": state_hash(material_state),
                    "state": material_state,
                    "vertex_cache_indices": triangle_cache_indices(command, argument),
                    "vertex_load_indices": [
                        [vertex_cache.get(slot) for slot in face]
                        for face in triangle_cache_indices(command, argument)
                    ],
                }
            )

    runtime_clusters = geometry_clusters(data)
    rdp = {
        "command_count": len(data) // 8,
        "opcode_counts": opcode_counts,
        "end_count": end_count,
        "nested_display_lists": nested_display_lists,
        "matrix_commands": matrix_commands,
        "vertex_loads": vertex_loads,
        "light_commands": light_commands,
        "normal_commands": normal_commands,
        "color_image": color_image,
        "geometry_clusters": [
            public_geometry_cluster(cluster) for cluster in runtime_clusters
        ],
        "tiles": [tiles[index] for index in sorted(tiles)],
        "tmem": tmem,
        "combine_mode": combine_mode,
        "convert_mode": convert_mode,
        "other_mode": other_mode,
        "geometry_mode": geometry_mode,
        "lighting_enabled": bool(geometry_mode & 0x00020000),
        "lights": {
            "num_lights": num_lights,
            "num_lights_raw": num_lights_raw,
            "advanced_lighting": advanced_lighting,
            "coordinate_modifiers": coord_mod,
            "slots": [light_slots[index] for index in sorted(light_slots)],
        },
        "normal_base": normal_base,
        "draw_runs": draw_runs,
    }
    if model_cluster_index is not None:
        rdp["model_correlations"] = correlate_model_clusters(
            runtime_clusters,
            model_cluster_index,
        )
        rdp["material_run_correlations"] = correlate_material_runs(
            draw_runs,
            rdp["model_correlations"],
        )
    return {
        "segments": segments,
        "texture": {
            "resolved_pixel_address": (
                pixel_image["resolved_address"] if pixel_image is not None else None
            ),
            "resolved_tlut_address": (
                palette_image["resolved_address"] if palette_image is not None else None
            ),
        },
        "rdp": rdp,
        "colours": {
            "primitive": primitive,
            "environment": environment,
            "alpha": primitive["rgba"][3] if primitive is not None else None,
        },
    }


def runtime_texture_image_record(
    pending_image: dict[str, Any] | None,
    load_command: int,
    load_argument: int,
    role: str,
) -> dict[str, Any] | None:
    """Describe the exact RDRAM span consumed by an RDP texture load."""

    if pending_image is None:
        return None
    image = dict(pending_image)
    image_size = (int(image["command"]) >> 19) & 3
    bits_per_texel = (4, 8, 16, 32)[image_size]
    opcode = load_command >> 24
    if opcode == 0xF3:
        texel_count = ((load_argument >> 12) & 0xFFF) + 1
        byte_length = (texel_count * bits_per_texel + 7) // 8
    elif opcode == 0xF0:
        texel_count = ((load_argument >> 14) & 0x3FF) + 1
        byte_length = texel_count * 2
    else:
        raise TraceError(f"unsupported runtime texture load opcode 0x{opcode:02X}")
    image.update(
        {
            "role": role,
            "image_size": image_size,
            "bits_per_texel": bits_per_texel,
            "texel_count": texel_count,
            "byte_length": byte_length,
        }
    )
    return image


def decode_rsp_matrix(data: bytes) -> dict[str, Any]:
    """Decode the 64-byte split signed-16.16 N64 Mtx consumed by the RSP."""

    if len(data) != 64:
        raise TraceError("RSP matrix must contain exactly 64 bytes")
    values = []
    for index in range(16):
        integer = struct.unpack_from(">h", data, index * 2)[0]
        fraction = struct.unpack_from(">H", data, 0x20 + index * 2)[0]
        values.append(integer + fraction / 65536.0)
    rows = [values[offset : offset + 4] for offset in range(0, 16, 4)]
    return {
        "layout": "n64-mtx-row-major-4x4-s16.16-split",
        "rows": rows,
        "translation": rows[3][:3],
    }


def decode_cbfd_character_matrix(data: bytes) -> dict[str, Any]:
    """Decode the float matrix array addressed through character segment 3."""

    if len(data) != 64:
        raise TraceError("CBFD character matrix must contain exactly 64 bytes")
    values = struct.unpack(">16f", data)
    relevant = [values[row * 4 + column] for row in range(4) for column in range(3)]
    rotation = [values[row * 4 + column] for row in range(3) for column in range(3)]
    valid = (
        all(math.isfinite(value) for value in relevant)
        and max(abs(value) for value in rotation) <= 64.0
        and max(abs(value) for value in relevant[9:12]) <= 10000000.0
    )
    if not valid:
        return {
            "layout": "cbfd-character-row-major-f32",
            "status": "invalid-or-uninitialized-at-capture",
            "rows": None,
            "translation": None,
        }
    rows = [
        [
            float(values[row * 4 + 0]),
            float(values[row * 4 + 1]),
            float(values[row * 4 + 2]),
            0.0 if row < 3 else 1.0,
        ]
        for row in range(4)
    ]
    return {
        "layout": "cbfd-character-row-major-f32",
        "status": "decoded-affine-components",
        "rows": rows,
        "translation": rows[3][:3],
        "ignored_column_status": "canonicalized-to-zero-zero-zero-one",
    }


def capture_runtime_matrices(
    debugger: "MupenDebugger",
    matrix_commands: list[dict[str, int]],
    max_matrices: int,
    matrix_format: str,
    timeout: int,
) -> tuple[list[dict[str, Any]], list[dict[str, Any]], list[int]]:
    """Capture unique model-view and projection matrices referenced by the task."""

    addresses: list[int] = []
    references_by_address: dict[int, list[dict[str, int | None]]] = {}
    unresolved: list[int] = []
    for matrix_command in matrix_commands:
        encoded_address = matrix_command["address"]
        address = matrix_command["resolved_address"]
        if address is None:
            if encoded_address not in unresolved:
                unresolved.append(encoded_address)
            continue
        if address not in addresses:
            addresses.append(address)
        reference = {
            key: matrix_command[key]
            for key in (
                "address",
                "segment",
                "segment_offset",
                "segment_base_address",
                "segment_relative_matrix_slot",
                "matrix_slot",
                "command",
            )
        }
        references = references_by_address.setdefault(address, [])
        if reference not in references:
            references.append(reference)
    if len(addresses) > max_matrices:
        raise TraceError(
            f"graphics task references {len(addresses)} direct matrices, limit is {max_matrices}"
        )

    matrices: list[dict[str, Any]] = []
    evidence: list[dict[str, Any]] = []
    for index, address in enumerate(addresses):
        output = debugger.command(f"mem /64b 0x{address:08X}", timeout)
        data = parse_memory_bytes(output, 64)
        digest = hashlib.sha256(data).hexdigest()
        name = f"runtime-matrix-{index:04d}"
        references = references_by_address[address]
        projection = any(int(ref["command"]) & 4 for ref in references)
        if projection and matrix_format == "cbfd-character-f32" and any(
            not (int(ref["command"]) & 4) for ref in references
        ):
            raise TraceError("one captured address has conflicting matrix layouts")
        decoder = (
            decode_cbfd_character_matrix
            if matrix_format == "cbfd-character-f32" and not projection
            else decode_rsp_matrix
        )
        matrices.append(
            {
                "address": address,
                "sha256": digest,
                "references": references,
                **decoder(data),
            }
        )
        evidence.append(
            {
                "name": name,
                "address_expression": {"matrix_command": f"0x{address:08X}"},
                "resolved_address": f"0x{address:08X}",
                "length": 64,
                "sha256": digest,
                "data_base64": base64.b64encode(data).decode("ascii"),
            }
        )
    return matrices, evidence, unresolved


def capture_runtime_vertices(
    debugger: "MupenDebugger", loads: list[dict[str, Any]], max_blocks: int, timeout: int
) -> list[dict[str, Any]]:
    """Retain source bytes actually read by VTX, including CPU-updated colours."""

    spans: dict[int, int] = {}
    for load in loads:
        address = load.get("resolved_address")
        if address is None:
            continue
        size = int(load["vertex_count"]) * 16
        if (not 16 <= size <= 2048 or not 0x80000000 <= address < 0xC0000000
                or (address & 0x1FFFFFFF) + size > 0x800000):
            raise TraceError("runtime vertex span is outside RDRAM")
        spans[address] = max(spans.get(address, 0), size)
    if len(spans) > max_blocks:
        raise TraceError(f"graphics task references {len(spans)} vertex blocks, limit is {max_blocks}")
    evidence = []
    for address, size in sorted(spans.items()):
        data = parse_memory_bytes(debugger.command(f"mem /{size}b 0x{address:08X}", timeout), size)
        evidence.append({
            "name": f"runtime-vertex-block-{len(evidence):04d}",
            "resolved_address": f"0x{address:08X}",
            "address_expression": {"vertex_load": f"0x{address:08X}"},
            "length": size,
            "sha256": hashlib.sha256(data).hexdigest(),
            "data_base64": base64.b64encode(data).decode("ascii"),
        })
    return evidence


def attach_runtime_matrices(
    decoded: dict[str, Any],
    matrices: list[dict[str, Any]],
) -> None:
    matrix_by_address = {
        matrix["address"]: (index, matrix)
        for index, matrix in enumerate(matrices)
    }
    def multiply(left: list, right: list) -> list:
        return [[sum(left[i][k] * right[k][j] for k in range(4))
                 for j in range(4)] for i in range(4)]

    def resolve_chain(chain: list | None) -> tuple[list | None, list[str]]:
        if not chain:
            return None, []
        rows = None
        hashes = []
        for reference in chain:
            captured = matrix_by_address.get(reference.get("resolved_address"))
            if captured is None:
                return None, hashes
            value = captured[1]
            current = value.get("rows")
            if (
                value.get("status") == "invalid-or-uninitialized-at-capture"
                or not isinstance(current, list) or len(current) != 4
                or any(not isinstance(row, list) or len(row) != 4 for row in current)
                or any(not math.isfinite(float(v)) for row in current for v in row)
            ):
                return None, hashes
            hashes.append(value["sha256"])
            # GLideN64 MultMatrix2 pre-multiplies in this row-vector layout.
            rows = current if rows is None else multiply(current, rows)
        if any(not math.isfinite(v) for row in rows for v in row):
            return None, hashes
        return rows, hashes

    for load in decoded["rdp"].get("vertex_loads", []):
        model_view, model_hashes = resolve_chain(load["state"].get("model_view_chain"))
        projection, projection_hashes = resolve_chain(load["state"].get("projection_chain"))
        combined = (
            multiply(model_view, projection)
            if model_view is not None and projection is not None else None
        )
        load["processing_matrices"] = {
            "model_view_rows": model_view,
            "projection_rows": projection,
            "combined_rows": combined,
            "model_view_sha256": model_hashes,
            "projection_sha256": projection_hashes,
        }

    for draw_run in [*decoded["rdp"]["draw_runs"], *decoded["rdp"].get("vertex_loads", [])]:
        matrix_state = draw_run["state"].get("matrix")
        if (
            matrix_state is None
            or matrix_state["resolved_address"] not in matrix_by_address
        ):
            continue
        index, matrix = matrix_by_address[matrix_state["resolved_address"]]
        draw_run["captured_matrix_index"] = index
        draw_run["matrix_sha256"] = matrix["sha256"]
        draw_run["matrix_translation"] = matrix["translation"]
        draw_run["pose_state_hash"] = state_hash(matrix)


def decode_cbfd_light(data: bytes) -> dict[str, Any]:
    """Decode the 48-byte source record consumed by GLideN64's CBFD handler."""

    if len(data) != 48:
        raise TraceError("CBFD light record must contain exactly 48 bytes")
    direction = list(struct.unpack_from(">3b", data, 8))
    direction_length = sum(component * component for component in direction) ** 0.5
    return {
        "layout": "f3dex2-cbfd-light-48",
        "colour": list(data[0:3]),
        "colour_copy": list(data[4:7]),
        "direction_s8": direction,
        "direction_normalized": (
            [component / direction_length for component in direction]
            if direction_length
            else [0.0, 0.0, 0.0]
        ),
        "attenuation": data[12] / 16.0,
        "position_s16": list(struct.unpack_from(">4h", data, 32)),
    }


def capture_runtime_lights(
    debugger: "MupenDebugger",
    light_commands: list[dict[str, int | None]],
    max_lights: int,
    timeout: int,
) -> tuple[list[dict[str, Any]], list[dict[str, Any]], list[int]]:
    """Capture unique 48-byte CBFD light records referenced by the task."""

    addresses: list[int] = []
    references_by_address: dict[int, list[dict[str, int | None]]] = {}
    unresolved: list[int] = []
    for light_command in light_commands:
        if light_command["light_slot"] is None:
            continue
        encoded_address = int(light_command["address"])
        resolved = light_command["resolved_address"]
        if resolved is None:
            if encoded_address not in unresolved:
                unresolved.append(encoded_address)
            continue
        address = int(resolved)
        if address not in addresses:
            addresses.append(address)
        reference = {
            key: light_command[key]
            for key in ("address", "segment", "segment_offset", "light_slot")
        }
        if reference not in references_by_address.setdefault(address, []):
            references_by_address[address].append(reference)
    if len(addresses) > max_lights:
        raise TraceError(
            f"graphics task references {len(addresses)} CBFD lights, limit is {max_lights}"
        )

    lights: list[dict[str, Any]] = []
    evidence: list[dict[str, Any]] = []
    for index, address in enumerate(addresses):
        output = debugger.command(f"mem /48b 0x{address:08X}", timeout)
        data = parse_memory_bytes(output, 48)
        digest = hashlib.sha256(data).hexdigest()
        name = f"runtime-light-{index:04d}"
        lights.append(
            {
                "address": address,
                "sha256": digest,
                "references": references_by_address[address],
                **decode_cbfd_light(data),
            }
        )
        evidence.append(
            {
                "name": name,
                "address_expression": {"light_command": f"0x{address:08X}"},
                "resolved_address": f"0x{address:08X}",
                "length": 48,
                "sha256": digest,
                "data_base64": base64.b64encode(data).decode("ascii"),
            }
        )
    return lights, evidence, unresolved


def attach_runtime_lights(
    decoded: dict[str, Any],
    lights: list[dict[str, Any]],
) -> None:
    light_by_address = {
        light["address"]: (index, light) for index, light in enumerate(lights)
    }
    for draw_run in [*decoded["rdp"]["draw_runs"], *decoded["rdp"].get("vertex_loads", [])]:
        run_state = draw_run["state"]
        for slot in run_state["lights"]["slots"]:
            captured = light_by_address.get(slot["resolved_address"])
            if captured is None:
                continue
            index, light = captured
            slot["captured_light_index"] = index
            slot["sha256"] = light["sha256"]
            slot["decoded"] = {
                key: light[key]
                for key in (
                    "colour",
                    "colour_copy",
                    "direction_s8",
                    "direction_normalized",
                    "attenuation",
                    "position_s16",
                )
            }
        draw_run["material_state_hash"] = state_hash(run_state)


def capture_runtime_normal_streams(
    debugger: "MupenDebugger",
    normal_commands: list[dict[str, int | None]],
    max_normal_streams: int,
    timeout: int,
) -> tuple[list[dict[str, Any]], list[dict[str, Any]], list[int]]:
    """Capture the 32 two-byte XY normal slots addressed by CBFD vertex loads."""

    addresses: list[int] = []
    references_by_address: dict[int, list[dict[str, int | None]]] = {}
    unresolved: list[int] = []
    for normal_command in normal_commands:
        encoded_address = int(normal_command["address"])
        resolved = normal_command["resolved_address"]
        if resolved is None:
            if encoded_address not in unresolved:
                unresolved.append(encoded_address)
            continue
        address = int(resolved)
        if address not in addresses:
            addresses.append(address)
        reference = {
            key: normal_command[key]
            for key in ("address", "segment", "segment_offset")
        }
        if reference not in references_by_address.setdefault(address, []):
            references_by_address[address].append(reference)
    if len(addresses) > max_normal_streams:
        raise TraceError(
            f"graphics task references {len(addresses)} CBFD normal streams, "
            f"limit is {max_normal_streams}"
        )

    streams: list[dict[str, Any]] = []
    evidence: list[dict[str, Any]] = []
    for index, address in enumerate(addresses):
        output = debugger.command(f"mem /64b 0x{address:08X}", timeout)
        data = parse_memory_bytes(output, 64)
        digest = hashlib.sha256(data).hexdigest()
        name = f"runtime-normal-stream-{index:04d}"
        streams.append(
            {
                "address": address,
                "sha256": digest,
                "layout": "f3dex2-cbfd-normal-xy-s8-32",
                "normal_xy_s8": [list(pair) for pair in struct.iter_unpack(">bb", data)],
                "references": references_by_address[address],
            }
        )
        evidence.append(
            {
                "name": name,
                "address_expression": {"normal_command": f"0x{address:08X}"},
                "resolved_address": f"0x{address:08X}",
                "length": 64,
                "sha256": digest,
                "data_base64": base64.b64encode(data).decode("ascii"),
            }
        )
    return streams, evidence, unresolved


def attach_runtime_normal_streams(
    decoded: dict[str, Any], streams: list[dict[str, Any]]
) -> None:
    stream_by_address = {
        stream["address"]: (index, stream) for index, stream in enumerate(streams)
    }
    for draw_run in [*decoded["rdp"]["draw_runs"], *decoded["rdp"].get("vertex_loads", [])]:
        run_state = draw_run["state"]
        normal_base = run_state.get("normal_base")
        if not isinstance(normal_base, dict):
            continue
        captured = stream_by_address.get(normal_base.get("resolved_address"))
        if captured is None:
            continue
        index, stream = captured
        normal_base["captured_normal_stream_index"] = index
        normal_base["sha256"] = stream["sha256"]
        normal_base["layout"] = stream["layout"]
        normal_base["normal_xy_s8"] = stream["normal_xy_s8"]
        draw_run["material_state_hash"] = state_hash(run_state)


def capture_runtime_texture_images(
    debugger: "MupenDebugger",
    tmem_commands: list[dict[str, Any]],
    max_images: int,
    max_bytes: int,
    timeout: int,
) -> tuple[list[dict[str, Any]], list[dict[str, Any]], list[int]]:
    """Capture unique RDRAM pixel and TLUT spans loaded by one graphics task."""

    unique: list[tuple[int, int]] = []
    references: dict[tuple[int, int], list[dict[str, Any]]] = {}
    unresolved: list[int] = []
    for tmem in tmem_commands:
        image = tmem.get("image")
        if not isinstance(image, dict):
            continue
        encoded_address = int(image["address"])
        resolved_address = image.get("resolved_address")
        byte_length = int(image.get("byte_length", 0))
        if resolved_address is None or byte_length <= 0 or byte_length > max_bytes:
            if encoded_address not in unresolved:
                unresolved.append(encoded_address)
            continue
        key = (int(resolved_address), byte_length)
        if key not in unique:
            unique.append(key)
        reference = {
            "command_offset": tmem["command_offset"],
            "role": tmem["role"],
            "encoded_address": encoded_address,
            "byte_length": byte_length,
        }
        if reference not in references.setdefault(key, []):
            references[key].append(reference)
    if len(unique) > max_images:
        raise TraceError(
            f"graphics task references {len(unique)} runtime texture images, "
            f"limit is {max_images}"
        )

    images: list[dict[str, Any]] = []
    evidence: list[dict[str, Any]] = []
    for index, (address, byte_length) in enumerate(unique):
        data = bytearray()
        while len(data) < byte_length:
            length = min(0x400, byte_length - len(data))
            chunk_address = address + len(data)
            output = debugger.command(
                f"mem /{length}b 0x{chunk_address:08X}", timeout
            )
            data.extend(parse_memory_bytes(output, length))
        payload = bytes(data)
        digest = hashlib.sha256(payload).hexdigest()
        name = f"runtime-texture-image-{index:04d}"
        record = {
            "address": address,
            "byte_length": byte_length,
            "sha256": digest,
            "references": references[(address, byte_length)],
        }
        images.append(record)
        evidence.append(
            {
                "name": name,
                "address_expression": {
                    "runtime_texture_image": f"0x{address:08X}"
                },
                "resolved_address": f"0x{address:08X}",
                "length": byte_length,
                "sha256": digest,
                "data_base64": base64.b64encode(payload).decode("ascii"),
            }
        )
    return images, evidence, unresolved


def attach_runtime_texture_images(
    decoded: dict[str, Any], images: list[dict[str, Any]]
) -> None:
    """Attach content hashes to texture state without duplicating raw payloads."""

    image_by_key = {
        (image["address"], image["byte_length"]): (index, image)
        for index, image in enumerate(images)
    }
    for tmem in decoded["rdp"]["tmem"]:
        image_state = tmem.get("image")
        if not isinstance(image_state, dict):
            continue
        key = (image_state.get("resolved_address"), image_state.get("byte_length"))
        captured = image_by_key.get(key)
        if captured is None:
            continue
        index, image = captured
        image_state["captured_texture_image_index"] = index
        image_state["sha256"] = image["sha256"]
    for draw_run in decoded["rdp"]["draw_runs"]:
        draw_run["material_state_hash"] = state_hash(draw_run["state"])


def merge_state(destination: dict[str, Any], observed: dict[str, Any]) -> None:
    for key, value in observed.items():
        if isinstance(value, dict) and isinstance(destination.get(key), dict):
            merge_state(destination[key], value)
        else:
            destination[key] = value


def update_segments_and_targets(
    data: bytes,
    segments: dict[int, int],
) -> list[int]:
    targets: list[int] = []
    for command, argument in struct.iter_unpack(">II", data):
        opcode = command >> 24
        if opcode == 0xDB and (command >> 16) & 0xFF == 0x06:
            segment = (command & 0xFFFF) // 4
            if segment < 16:
                segments[segment] = argument
        elif opcode == 0xDE:
            segment = argument >> 24
            if argument >= 0x80000000:
                address = argument
            elif segment in segments:
                address = (segments[segment] + (argument & 0xFFFFFF)) & 0xFFFFFFFF
                if address < 0x20000000:
                    address |= 0x80000000
            else:
                continue
            targets.append(address)
    return targets


def resolve_display_list_address(argument: int, segments: dict[int, int]) -> int | None:
    if argument >= 0x80000000:
        return argument
    segment = argument >> 24
    if segment not in segments:
        return None
    address = (segments[segment] + (argument & 0xFFFFFF)) & 0xFFFFFFFF
    if address < 0x20000000:
        address |= 0x80000000
    return address


def flatten_display_lists(
    root_data: bytes,
    nested_data: dict[int, bytes],
    *,
    root_address: int = 0,
    origins: list[list[int]] | None = None,
) -> tuple[bytes, list[int]]:
    """Inline captured G_DL calls in execution order for effective-state decoding."""

    segments: dict[int, int] = {}
    unresolved: list[int] = []

    def walk(data: bytes, address: int, active: set[int], parents: list[int]) -> bytes:
        flattened = bytearray()
        for index, (command, argument) in enumerate(struct.iter_unpack(">II", data)):
            opcode = command >> 24
            flattened.extend(struct.pack(">II", command, argument))
            command_address = address + index * 8
            if origins is not None:
                origins.append([*parents, command_address])
            if opcode == 0xDB and (command >> 16) & 0xFF == 0x06:
                segment = (command & 0xFFFF) // 4
                if segment < 16:
                    segments[segment] = argument
            elif opcode == 0xDE:
                target = resolve_display_list_address(argument, segments)
                if target is None or target not in nested_data or target in active:
                    unresolved.append(argument)
                else:
                    flattened.extend(walk(nested_data[target], target, active | {target},
                                          [*parents, command_address]))
                if command & 0x00010000:
                    break
            elif opcode == 0xDF:
                break
        return bytes(flattened)

    return walk(root_data, root_address, {root_address}, []), unresolved


def captured_task_type(event: dict[str, Any]) -> int | None:
    """Read OSTask.type from verified task bytes; renderer subranges have none."""

    probes = [probe for probe in event.get("evidence", {}).get("memory", [])
              if probe.get("name") == "task"]
    if not probes:
        return None
    if len(probes) != 1:
        raise TraceError("captured task header is ambiguous")
    probe = probes[0]
    data = base64.b64decode(probe["data_base64"], validate=True)
    if (len(data) != 64 or probe.get("length") != 64
            or hashlib.sha256(data).hexdigest() != probe.get("sha256")):
        raise TraceError("captured task header identity changed")
    return int.from_bytes(data[:4], "big")


def read_display_list(
    debugger: MupenDebugger,
    address: int,
    max_bytes: int,
    timeout: int,
) -> tuple[bytes, bool]:
    data = bytearray()
    chunk_size = min(0x400, max_bytes)
    while len(data) < max_bytes:
        length = min(chunk_size, max_bytes - len(data))
        output = debugger.command(f"mem /{length}b 0x{address + len(data):08X}", timeout)
        data.extend(parse_memory_bytes(output, length))
        for offset in range(0, len(data), 8):
            if data[offset] == 0xDF:
                return bytes(data[: offset + 8]), True
    return bytes(data), False


def capture_nested_display_lists(
    debugger: MupenDebugger,
    root_data: bytes,
    max_lists: int,
    max_bytes: int,
    timeout: int,
) -> tuple[list[dict[str, Any]], list[dict[str, Any]]]:
    """Capture reachable display lists in RSP execution order.

    Segment bases are mutable display-list state.  A breadth-first scan loses
    the base selected by an earlier called list, which in turn leaves later
    segment-8 calls unresolved even though their runtime address is known.
    Replay calls here in command order, while caching each distinct payload so
    repeated calls can still be walked under their current segment state.
    """

    segments: dict[int, int] = {}
    captured: list[dict[str, Any]] = []
    captured_by_address: dict[int, bytes] = {}
    evidence: list[dict[str, Any]] = []

    def load(address: int) -> bytes | None:
        if address in captured_by_address:
            return captured_by_address[address]
        if len(captured) >= max_lists:
            return None
        data, terminated = read_display_list(debugger, address, max_bytes, timeout)
        captured_by_address[address] = data
        sha256 = hashlib.sha256(data).hexdigest()
        name = f"nested-display-list-{len(captured):04d}"
        captured.append(
            {
                "name": name,
                "address": address,
                "data": data,
                "terminated": terminated,
            }
        )
        evidence.append(
            {
                "name": name,
                "address_expression": {"display_list_target": f"0x{address:08X}"},
                "resolved_address": f"0x{address:08X}",
                "length": len(data),
                "sha256": sha256,
                "data_base64": base64.b64encode(data).decode("ascii"),
                "terminated_by_enddl": terminated,
            }
        )
        return data

    def walk(data: bytes, active: set[int]) -> None:
        for command, argument in struct.iter_unpack(">II", data):
            opcode = command >> 24
            if opcode == 0xDB and (command >> 16) & 0xFF == 0x06:
                segment = (command & 0xFFFF) // 4
                if segment < 16:
                    segments[segment] = argument
            elif opcode == 0xDE:
                address = resolve_display_list_address(argument, segments)
                if address is not None and address not in active:
                    nested = load(address)
                    if nested is not None:
                        walk(nested, active | {address})
                if command & 0x00010000:
                    break
            elif opcode == 0xDF:
                break

    walk(root_data, set())
    return captured, evidence


def summarize_nested_display_lists(
    captured: list[dict[str, Any]],
    model_cluster_index: list[dict[str, Any]] | None,
) -> list[dict[str, Any]]:
    summaries = []
    for record in captured:
        decoded = decode_f3dex2_cbfd(record["data"], model_cluster_index)
        summaries.append(
            {
                "address": record["address"],
                "length": len(record["data"]),
                "sha256": hashlib.sha256(record["data"]).hexdigest(),
                "terminated_by_enddl": record["terminated"],
                "segments": decoded["segments"],
                "texture": decoded["texture"],
                "rdp": decoded["rdp"],
                "colours": decoded["colours"],
            }
        )
    return summaries


def replay_face_culling(
    data: bytes, origins: list[list[int]] | None = None
) -> dict[int, dict[str, int | None]]:
    """Replay culling knowledge across a checked, optionally flattened stream."""

    if len(data) % 8 or (origins is not None and len(origins) != len(data) // 8):
        raise TraceError("culling replay command/origin span is invalid")
    if any(data[offset] in (0x03, 0x04) for offset in range(0, len(data), 8)):
        # Flattening expands unconditional calls only. A conditional return or
        # branch can bypass geometry-mode writes, including in a caller after
        # a callee returns. Do not infer execution from linear captured bytes.
        return {offset: {"mode": None, "known_bits": 0}
                for offset in range(0, len(data), 8) if triangle_count(data[offset])}
    value = known = 0
    states = {}
    for index, (command, argument) in enumerate(struct.iter_unpack(">II", data)):
        opcode = command >> 24
        if opcode == 0xD9:
            preserve = command & 0xFFFFFF
            value = (value & preserve) | argument
            known = (known & preserve) | (~preserve & 0xFFFFFF) | argument
        elif opcode == 0xDE:
            # A following descendant origin proves that this call was expanded
            # from captured bytes. An unresolved callee may change either bit.
            resolved = (origins is not None and index + 1 < len(origins)
                        and len(origins[index + 1]) > len(origins[index])
                        and origins[index + 1][:len(origins[index])] == origins[index])
            if not resolved:
                known = 0
        if triangle_count(opcode):
            states[index * 8] = {
                "mode": value & 0x600 if known & 0x600 == 0x600 else None,
                "known_bits": known & 0x600,
            }
    return states


def refresh_trace_model_correlations(
    event: dict[str, Any], model_cluster_index: list[dict[str, Any]]
) -> bool:
    """Refresh derived correlations from hash-checked captured command bytes.

    Keep recorded RDP state, matrix/texture captures, and the source JSONL
    untouched. Add replayed tile bounds and vertex-processing inputs separately
    from the recorded state. This permits corrected decoding without a new run.
    """

    if captured_task_type(event) not in (None, 1):
        return False
    rdp = event.get("state", {}).get("rdp", {})
    if "model_correlations" not in rdp:
        return False
    probes = event.get("evidence", {}).get("memory", [])

    def payload(probe: dict[str, Any]) -> bytes:
        data = base64.b64decode(probe["data_base64"], validate=True)
        if len(data) != probe["length"] or hashlib.sha256(data).hexdigest() != probe["sha256"]:
            raise TraceError("captured display-list payload identity changed")
        return data

    roots = [probe for probe in probes if probe.get("name") in {
        "character-command-buffer", "command-buffer"
    }]
    if len(roots) != 1:
        raise TraceError("correlation refresh requires one captured command buffer")
    root_data = payload(roots[0])
    nested_data = {
        parse_int(probe["resolved_address"], "resolved_address"): payload(probe)
        for probe in probes
        if probe.get("name", "").startswith("nested-display-list-")
    }

    def refresh(target: dict[str, Any], data: bytes, origins: list[list[int]] | None = None) -> None:
        clusters = geometry_clusters(data)
        target["geometry_clusters"] = [public_geometry_cluster(c) for c in clusters]
        target["model_correlations"] = correlate_model_clusters(clusters, model_cluster_index)
        if "draw_runs" in target:
            replayed = decode_f3dex2_cbfd(data)
            attach_runtime_matrices(replayed, replay_matrices)
            attach_runtime_lights(replayed, replay_lights)
            attach_runtime_normal_streams(replayed, replay_normals)
            replayed_draws = replayed["rdp"]["draw_runs"]
            replayed_vertex_loads = replayed["rdp"]["vertex_loads"]
            replayed_culling = replay_face_culling(data, origins)
            if [(draw["command_offset"], draw["triangle_count"]) for draw in replayed_draws] != [
                (draw["command_offset"], draw["triangle_count"]) for draw in target["draw_runs"]
            ]:
                raise TraceError("captured triangle command identity changed during replay")
            for draw, replayed in zip(target["draw_runs"], replayed_draws):
                draw["replayed_tile_bounds"] = replayed["state"]["tile_bounds"]
                draw["replayed_face_culling"] = replayed_culling[draw["command_offset"]]
                draw["replayed_vertex_load_indices"] = replayed["vertex_load_indices"]
                draw["replayed_vertex_cache_indices"] = replayed["vertex_cache_indices"]
            target["replayed_vertex_loads"] = replayed_vertex_loads
            target["material_run_correlations"] = correlate_material_runs(
                target["draw_runs"], target["model_correlations"]
            )

    # Rebuild derived vertex inputs from captured bytes. Do not silently trust
    # decoded rows/light values in an older trace, or invent uncaptured inputs.
    replay_matrices: list[dict[str, Any]] = []
    replay_lights: list[dict[str, Any]] = []
    replay_normals: list[dict[str, Any]] = []
    for prefix, state_key, output in (
        ("runtime-matrix-", "joint_matrices", replay_matrices),
        ("runtime-light-", "rsp_lights", replay_lights),
        ("runtime-normal-stream-", "rsp_normal_streams", replay_normals),
    ):
        records = {record["address"]: record for record in event.get("state", {}).get(state_key, [])}
        for probe in probes:
            if not probe.get("name", "").startswith(prefix):
                continue
            data = payload(probe)
            address = parse_int(probe["resolved_address"], "resolved_address")
            record = records.get(address)
            if record is None or record.get("sha256") != probe["sha256"]:
                raise TraceError("captured vertex-processing input identity changed")
            if state_key == "joint_matrices":
                layout = record.get("layout")
                if layout == "cbfd-character-row-major-f32":
                    decoded_input = decode_cbfd_character_matrix(data)
                elif layout == "n64-mtx-row-major-4x4-s16.16-split":
                    decoded_input = decode_rsp_matrix(data)
                else:
                    raise TraceError("captured vertex-processing matrix layout is unknown")
            elif state_key == "rsp_lights":
                decoded_input = decode_cbfd_light(data)
            else:
                if len(data) != 64:
                    raise TraceError("captured CBFD normal stream size changed")
                decoded_input = {
                    "layout": "f3dex2-cbfd-normal-xy-s8-32",
                    "normal_xy_s8": [list(pair) for pair in struct.iter_unpack(">bb", data)],
                }
            output.append({"address": address, "sha256": probe["sha256"], **decoded_input})

    effective_data = root_data
    command_origins: list[list[int]] = []
    root_address = (parse_int(roots[0]["resolved_address"], "resolved_address")
                    if "resolved_address" in roots[0] else None)
    if "submitted_buffer" in rdp:
        effective_data, unresolved = flatten_display_lists(
            root_data, nested_data, root_address=root_address or 0,
            origins=command_origins if root_address is not None else None,
        )
        if unresolved != rdp.get("unresolved_display_list_targets", []):
            raise TraceError("captured display-list traversal changed during refresh")
        refresh(rdp["submitted_buffer"], root_data)
    if len(effective_data) // 8 != rdp.get("effective_command_count", rdp["command_count"]):
        raise TraceError("captured effective command count changed during refresh")
    refresh(rdp, effective_data, command_origins or None)
    if root_address is not None:
        rdp["replayed_command_origins"] = command_origins or [
            [root_address + offset] for offset in range(0, len(effective_data), 8)
        ]
    for record in rdp.get("walked_display_lists", []):
        data = nested_data.get(int(record["address"]))
        if data is None or hashlib.sha256(data).hexdigest() != record["sha256"]:
            raise TraceError("walked display list is absent from captured evidence")
        refresh(record["rdp"], data)
    return True


class MupenDebugger:
    def __init__(
        self, command: list[str], session_timeout: int | None = None
    ) -> None:
        master, slave = os.openpty()
        self.master = master
        self.selector = selectors.DefaultSelector()
        self.selector.register(master, selectors.EVENT_READ)
        self.process = subprocess.Popen(
            command,
            stdin=slave,
            stdout=slave,
            stderr=slave,
            close_fds=True,
            start_new_session=True,
        )
        os.close(slave)
        self.buffer = b""
        self.session_deadline = (
            time.monotonic() + session_timeout
            if session_timeout is not None
            else None
        )

    def wait_deadline(self, timeout: int) -> float:
        deadline = time.monotonic() + timeout
        if self.session_deadline is not None:
            deadline = min(deadline, self.session_deadline)
        return deadline

    def _read(self, timeout: float) -> bytes:
        events = self.selector.select(timeout)
        if not events:
            return b""
        try:
            return os.read(self.master, 65536)
        except OSError:
            return b""

    def wait_for_prompt(self, timeout: int) -> str:
        deadline = self.wait_deadline(timeout)
        while PROMPT not in self.buffer:
            if self.process.poll() is not None:
                raise TraceError(f"Mupen exited with status {self.process.returncode}")
            remaining = deadline - time.monotonic()
            if remaining <= 0:
                raise TraceError("timed out waiting for the Mupen debugger prompt")
            self.buffer += self._read(min(remaining, 1.0))
        output, self.buffer = self.buffer.split(PROMPT, 1)
        return output.decode("utf-8", errors="replace")

    def wait_for_breakpoint(self, timeout: int) -> tuple[int, str]:
        deadline = self.wait_deadline(timeout)
        transcript = bytearray(self.buffer)
        self.buffer = b""
        while True:
            decoded = transcript.decode("utf-8", errors="replace")
            matches = list(BREAKPOINT_RE.finditer(decoded))
            if matches and re.search(r"PC at 0x[0-9A-Fa-f]+\.", decoded[matches[-1].end() :]):
                # The 2.6 debugger sometimes emits its next prompt just after
                # the PC line and sometimes waits until the next command. Drain
                # only already-ready bytes so a late prompt cannot satisfy the
                # following command before that command's output arrives.
                while True:
                    ready = self._read(0.05)
                    if not ready:
                        break
                    transcript.extend(ready)
                self.buffer = b""
                return int(matches[-1].group(1), 16), transcript.decode(
                    "utf-8", errors="replace"
                )
            if self.process.poll() is not None:
                raise TraceError(f"Mupen exited before a breakpoint (status {self.process.returncode})")
            remaining = deadline - time.monotonic()
            if remaining <= 0:
                raise TraceError("timed out waiting for a runtime breakpoint")
            transcript.extend(self._read(min(remaining, 1.0)))
            if len(transcript) > 16 * 1024 * 1024:
                del transcript[: len(transcript) - 8 * 1024 * 1024]

    def send(self, command: str) -> None:
        os.write(self.master, command.encode("ascii") + b"\n")

    def resume(self) -> None:
        # Mupen 2.6.0 can emit a second debugger prompt just after the prompt
        # consumed by `regs` or `mem`. If `run` is sent into that transition it
        # is occasionally lost, which makes replay skips nondeterministic.
        # Drain only already-arriving prompt bytes before resuming execution.
        deadline = time.monotonic() + 0.25
        while time.monotonic() < deadline:
            ready = self._read(0.05)
            if not ready:
                break
        self.buffer = b""
        self.send("run")

    def command(self, command: str, timeout: int) -> str:
        self.send(command)
        return self.wait_for_prompt(timeout)

    def close(self) -> None:
        if self.process.poll() is None:
            try:
                self.send("quit")
                self.process.wait(timeout=5)
            except (OSError, subprocess.TimeoutExpired):
                os.killpg(self.process.pid, signal.SIGTERM)
                try:
                    self.process.wait(timeout=5)
                except subprocess.TimeoutExpired:
                    os.killpg(self.process.pid, signal.SIGKILL)
                    self.process.wait()
        self.selector.close()
        os.close(self.master)


def capture_memory(
    debugger: MupenDebugger,
    probes: list[dict[str, Any]],
    registers: dict[str, int],
    timeout: int,
    initial_memory: dict[str, bytes] | None = None,
) -> tuple[dict[str, bytes], list[dict[str, Any]]]:
    captured: dict[str, bytes] = dict(initial_memory or {})
    evidence: list[dict[str, Any]] = []
    for probe in probes:
        address = resolve_probe_address(probe["address"], registers, captured)
        length = resolve_probe_length(probe["length"], registers, captured)
        output = debugger.command(f"mem /{length}b 0x{address:08X}", timeout)
        data = parse_memory_bytes(output, length)
        captured[probe["name"]] = data
        evidence.append(
            {
                "name": probe["name"],
                "address_expression": probe["address"],
                "resolved_address": f"0x{address:08X}",
                "length": length,
                "sha256": hashlib.sha256(data).hexdigest(),
                "data_base64": base64.b64encode(data).decode("ascii"),
            }
        )
    return captured, evidence


def parse_memory_bytes(output: str, expected_length: int) -> bytes:
    clean = re.sub(r"\x1b\[[0-9;]*m", "", output)
    lines = clean.replace("\r", "").splitlines()
    data_lines = [line for line in lines if not line.strip().startswith("mem ")]
    values = re.findall(r"(?<![0-9A-Fa-f])[0-9A-Fa-f]{2}(?![0-9A-Fa-f])", " ".join(data_lines))
    if len(values) != expected_length:
        raise TraceError(
            f"debugger memory command returned {len(values)} bytes, expected {expected_length}"
        )
    return bytes(int(value, 16) for value in values)


def load_tool_revisions() -> dict[str, str]:
    lock_path = Path("toolchain/tools.lock.json")
    if not lock_path.is_file():
        return {}
    lock = json.loads(lock_path.read_text(encoding="utf-8"))
    return {
        name: value["revision"]
        for name, value in lock.get("tools", {}).items()
        if (name.startswith("mupen64plus-") or name == "angrylion-rdp-plus")
        and isinstance(value, dict) and "revision" in value
    }


def output_path(value: str) -> Path:
    root = Path.cwd().resolve()
    build_root = (root / "build").resolve()
    path = Path(value)
    if not path.is_absolute():
        path = root / path
    path = path.resolve()
    if not path.is_relative_to(build_root):
        raise TraceError("trace output must be under build/")
    return path


def identity_from(spec: dict[str, Any], args: argparse.Namespace) -> dict[str, int | None]:
    target = spec.get("target", {})
    if not isinstance(target, dict):
        raise TraceError("trace spec target must be an object")
    identity: dict[str, int | None] = {}
    for name in ("bank", "entry", "segment", "material_run"):
        override = getattr(args, name)
        value = override if override is not None else target.get(name)
        identity[name] = None if value is None else parse_int(value, f"target.{name}")
        if identity[name] is not None and identity[name] < 0:
            raise TraceError(f"target.{name} cannot be negative")
    return identity


def runtime_command(args: argparse.Namespace) -> list[str]:
    """Select a reproducible backend without changing the default trace mode."""

    if args.software_renderer and any(
        argument.split("=", 1)[0] in {"--gfx", "--rsp", "--emumode"}
        for argument in args.mupen_args
    ):
        raise TraceError("--software-renderer cannot be combined with CPU/GFX/RSP overrides")
    command = [
        "/usr/local/bin/conker-mupen64plus",
        "--noosd",
        "--nospeedlimit",
        "--debug",
        "--emumode",
        "1",
        "--gfx",
        "mupen64plus-video-angrylion-plus" if args.software_renderer else "dummy",
        "--audio",
        "dummy",
        "--input",
        "dummy",
        "--rsp",
        "mupen64plus-rsp-cxd4-sse2" if args.software_renderer else "mupen64plus-rsp-hle",
    ]
    if args.software_renderer:
        command = ["xvfb-run", "--auto-servernum", "--server-args=-screen 0 640x480x24 -nolisten tcp",
                   "env", "LIBGL_ALWAYS_SOFTWARE=1", *command]
    if args.savestate:
        command.extend(["--savestate", args.savestate])
    command.extend(args.mupen_args)
    command.append("roms/baserom.us.z64")

    return command


def record(args: argparse.Namespace) -> int:
    spec = validate_spec(json.loads(Path(args.spec).read_text(encoding="utf-8")))
    destination = output_path(args.output)
    if destination.exists() and not (args.force or args.append):
        raise TraceError(f"trace output already exists: {destination}; use --force or --append")
    destination.parent.mkdir(parents=True, exist_ok=True)
    identity = identity_from(spec, args)
    max_events = args.max_events or parse_int(spec.get("max_events", 1), "max_events")
    max_breakpoint_hits = parse_int(
        spec.get("max_breakpoint_hits", max_events * 1000), "max_breakpoint_hits"
    )
    timeout = args.timeout or parse_int(spec.get("timeout_seconds", 120), "timeout_seconds")
    session_timeout = args.session_timeout
    model_cluster_index = load_model_cluster_index() if spec.get("model_correlation") else None
    model_inventory_digest = (
        load_model_inventory_digest()
        if model_cluster_index is not None or spec.get("model_inventory_digest")
        else None
    )
    if not 1 <= max_events <= 100000:
        raise TraceError("--max-events must be between 1 and 100000")
    if max_breakpoint_hits < max_events:
        raise TraceError("max_breakpoint_hits must be at least --max-events")
    if not 1 <= timeout <= 3600:
        raise TraceError("--timeout must be between 1 and 3600 seconds")
    if session_timeout is not None and not 1 <= session_timeout <= 86400:
        raise TraceError("--session-timeout must be between 1 and 86400 seconds")

    command = runtime_command(args)

    mode = "a" if args.append else "w"
    debugger = MupenDebugger(command, session_timeout)
    captured_count = 0
    breakpoint_hits = 0
    breakpoint_capture_counts: dict[str, int] = {}
    pending_character_draws: list[dict[str, Any]] = []
    try:
        debugger.wait_for_prompt(timeout)
        breakpoints_by_address: dict[int, dict[str, Any]] = {}
        for breakpoint in spec["breakpoints"]:
            address = parse_int(breakpoint["address"], f"{breakpoint['name']}.address")
            flags = parse_int(breakpoint.get("flags", 8), f"{breakpoint['name']}.flags")
            debugger.command(f"bp add 0x{address:08X} 1 {flags}", timeout)
            breakpoints_by_address[address] = breakpoint

        with destination.open(mode, encoding="utf-8") as stream:
            if not args.append:
                header = {
                    "schema": SCHEMA,
                    "record_type": "session",
                    "profile": "us",
                    "spec_name": spec["name"],
                    "identity": identity,
                    "tool_revisions": load_tool_revisions(),
                    "emulation": {
                        "default_cpu": "interpreter",
                        "default_graphics": "angrylion-rdp-plus" if args.software_renderer else "dummy",
                        "default_rsp": "cxd4" if args.software_renderer else "hle",
                        "requested_backend": "software" if args.software_renderer else "headless",
                        "additional_arguments": args.mupen_args,
                    },
                    "normalized_sha1": model_inventory_digest,
                    "session_timeout_seconds": session_timeout,
                }
                stream.write(json.dumps(header, sort_keys=True) + "\n")
                stream.flush()
            debugger.send("run")
            while captured_count < max_events:
                guest_pc, _ = debugger.wait_for_breakpoint(timeout)
                breakpoint = breakpoints_by_address.get(guest_pc)
                if breakpoint is None:
                    # Mupen 2.6 may report the instruction after an execution
                    # breakpoint even though its BPT line names the configured
                    # instruction. Preserve the reported PC but associate that
                    # single-instruction stop with its reviewed hook.
                    breakpoint = breakpoints_by_address.get((guest_pc - 4) & 0xFFFFFFFF)
                if breakpoint is None:
                    raise TraceError(f"unexpected breakpoint at 0x{guest_pc:08X}")
                registers = parse_registers(debugger.command("regs", timeout))
                probes = breakpoint.get("memory", [])
                breakpoint_hits += 1
                if breakpoint_hits > max_breakpoint_hits:
                    raise TraceError(
                        f"stopped after {max_breakpoint_hits} breakpoint hits without enough qualifying events"
                    )
                register_conditions = [
                    condition
                    for condition in breakpoint.get("when", [])
                    if condition["source"] == "register"
                ]
                if not all(
                    extract_value(condition, registers, {})
                    == parse_int(condition["equals"], "condition.equals")
                    for condition in register_conditions
                ):
                    debugger.resume()
                    continue
                condition_probe_names = {
                    condition["name"]
                    for condition in breakpoint.get("when", [])
                    if condition["source"] == "memory"
                }
                condition_probes = [
                    probe for probe in probes if probe["name"] in condition_probe_names
                ]
                memory, memory_evidence = capture_memory(
                    debugger,
                    condition_probes,
                    registers,
                    timeout,
                )
                if not all(
                    extract_value(condition, registers, memory)
                    == parse_int(condition["equals"], "condition.equals")
                    for condition in breakpoint.get("when", [])
                ):
                    debugger.resume()
                    continue
                remaining_probes = [
                    probe for probe in probes if probe["name"] not in condition_probe_names
                ]
                remaining_memory, remaining_evidence = capture_memory(
                    debugger,
                    remaining_probes,
                    registers,
                    timeout,
                    memory,
                )
                memory = remaining_memory
                memory_evidence.extend(remaining_evidence)
                decoder = breakpoint.get("decoder")
                draw_context_for_event: dict[str, Any] | None = None
                if decoder is not None and decoder.get("format") == (
                    "cbfd-character-draw-range"
                ):
                    stack_pointer = registers["sp"] & 0xFFFFFFFF
                    matching_contexts = [
                        index
                        for index, context in enumerate(pending_character_draws)
                        if context["entry_breakpoint"]
                        == decoder["entry_breakpoint"]
                        and context["return_stack_pointer"] == stack_pointer
                    ]
                    if not matching_contexts:
                        raise TraceError(
                            f"{breakpoint['name']} has no matching character draw entry"
                        )
                    draw_context = pending_character_draws.pop(matching_contexts[-1])
                    start = draw_context["command_buffer_start"]
                    end = registers["v0"] & 0xFFFFFFFF
                    max_bytes = parse_int(
                        decoder.get("max_bytes", 0x10000),
                        f"{breakpoint['name']}.decoder.max_bytes",
                    )
                    length = end - start
                    if length < 8 or length > max_bytes or length % 8:
                        raise TraceError(
                            f"{breakpoint['name']} emitted invalid command range "
                            f"0x{start:08X}:0x{end:08X}"
                        )
                    memory_name = decoder["memory"]
                    output = debugger.command(
                        f"mem /{length}b 0x{start:08X}", timeout
                    )
                    command_data = parse_memory_bytes(output, length)
                    memory[memory_name] = command_data
                    memory_evidence.append(
                        {
                            "name": memory_name,
                            "address_expression": {
                                "source": "prior-breakpoint",
                                "name": decoder["entry_breakpoint"],
                                "field": "model.command_buffer_start",
                            },
                            "resolved_address": f"0x{start:08X}",
                            "length": length,
                            "sha256": hashlib.sha256(command_data).hexdigest(),
                            "data_base64": base64.b64encode(command_data).decode(
                                "ascii"
                            ),
                        }
                    )
                    draw_context_for_event = {
                        **draw_context["model"],
                        "command_buffer_start": start,
                        "command_buffer_end": end,
                        "command_byte_count": length,
                    }
                    decoder = {**decoder, "format": "f3dex2-cbfd"}
                nested_display_lists: list[dict[str, Any]] = []
                if decoder is not None and decoder.get("walk_nested"):
                    nested_display_lists, nested_evidence = capture_nested_display_lists(
                        debugger,
                        memory[decoder["memory"]],
                        parse_int(decoder.get("max_nested_lists", 64), "max_nested_lists"),
                        parse_int(decoder.get("max_nested_bytes", 0x10000), "max_nested_bytes"),
                        timeout,
                    )
                    memory_evidence.extend(nested_evidence)
                state = default_state()
                for destination_path, source in breakpoint.get("fields", {}).items():
                    set_path(state, destination_path, extract_value(source, registers, memory))
                if draw_context_for_event is not None:
                    state["model"].update(draw_context_for_event)
                if decoder is not None and decoder["format"] == "f3dex2-cbfd":
                    effective_data = memory[decoder["memory"]]
                    root_decoded = decode_f3dex2_cbfd(
                        effective_data,
                        model_cluster_index,
                    )
                    if nested_display_lists:
                        flattened, unresolved = flatten_display_lists(
                            memory[decoder["memory"]],
                            {
                                record["address"]: record["data"]
                                for record in nested_display_lists
                            },
                        )
                        decoded = decode_f3dex2_cbfd(flattened, model_cluster_index)
                        effective_data = flattened
                        decoded["rdp"]["submitted_buffer"] = {
                            key: root_decoded["rdp"][key]
                            for key in (
                                "command_count",
                                "opcode_counts",
                                "end_count",
                                "nested_display_lists",
                                "geometry_clusters",
                                "model_correlations",
                            )
                            if key in root_decoded["rdp"]
                        }
                        decoded["rdp"]["effective_command_count"] = len(flattened) // 8
                        decoded["rdp"]["unresolved_display_list_targets"] = unresolved
                        decoded["rdp"]["walked_display_lists"] = summarize_nested_display_lists(
                            nested_display_lists,
                            model_cluster_index,
                        )
                    else:
                        decoded = root_decoded
                    merge_state(state, decoded)
                    if decoder.get("capture_matrices"):
                        matrices, matrix_evidence, unresolved_matrices = capture_runtime_matrices(
                            debugger,
                            decoded["rdp"]["matrix_commands"],
                            parse_int(
                                decoder.get("max_matrices", 128),
                                "max_matrices",
                            ),
                            decoder.get("matrix_format", "n64-mtx"),
                            timeout,
                        )
                        attach_runtime_matrices(decoded, matrices)
                        state["joint_matrices"] = matrices
                        state["rdp"]["unresolved_matrix_addresses"] = [
                            f"0x{address:08X}" for address in unresolved_matrices
                        ]
                        memory_evidence.extend(matrix_evidence)
                    if decoder.get("capture_lights"):
                        lights, light_evidence, unresolved_lights = capture_runtime_lights(
                            debugger,
                            decoded["rdp"]["light_commands"],
                            parse_int(decoder.get("max_lights", 128), "max_lights"),
                            timeout,
                        )
                        attach_runtime_lights(decoded, lights)
                        state["rsp_lights"] = lights
                        state["rdp"]["unresolved_light_addresses"] = [
                            f"0x{address:08X}" for address in unresolved_lights
                        ]
                        memory_evidence.extend(light_evidence)
                    if decoder.get("capture_vertices"):
                        memory_evidence.extend(capture_runtime_vertices(
                            debugger, decoded["rdp"]["vertex_loads"],
                            parse_int(decoder.get("max_vertex_blocks", 512), "max_vertex_blocks"),
                            timeout,
                        ))
                    if decoder.get("capture_normals"):
                        (
                            normal_streams,
                            normal_evidence,
                            unresolved_normals,
                        ) = capture_runtime_normal_streams(
                            debugger,
                            decoded["rdp"]["normal_commands"],
                            parse_int(
                                decoder.get("max_normal_streams", 128),
                                "max_normal_streams",
                            ),
                            timeout,
                        )
                        attach_runtime_normal_streams(decoded, normal_streams)
                        state["rsp_normal_streams"] = normal_streams
                        state["rdp"]["unresolved_normal_addresses"] = [
                            f"0x{address:08X}" for address in unresolved_normals
                        ]
                        memory_evidence.extend(normal_evidence)
                    if decoder.get("capture_textures"):
                        (
                            texture_images,
                            texture_evidence,
                            unresolved_textures,
                        ) = capture_runtime_texture_images(
                            debugger,
                            decoded["rdp"]["tmem"],
                            parse_int(
                                decoder.get("max_texture_images", 512),
                                "max_texture_images",
                            ),
                            parse_int(
                                decoder.get("max_texture_bytes", 0x4000),
                                "max_texture_bytes",
                            ),
                            timeout,
                        )
                        attach_runtime_texture_images(decoded, texture_images)
                        state["rdp_texture_images"] = texture_images
                        state["rdp"]["unresolved_texture_addresses"] = [
                            f"0x{address:08X}" for address in unresolved_textures
                        ]
                        memory_evidence.extend(texture_evidence)
                elif decoder is not None:
                    character_model = decode_cbfd_character_pool(
                        memory[decoder["memory"]]
                    )
                    if decoder.get("capture_character_part_tables"):
                        character_model["part_tables"] = (
                            decode_cbfd_character_part_table_headers(
                                memory[decoder["part_pointer_table"]],
                                memory[decoder["part_count_table"]],
                                memory[decoder["extra_part_pointer_table"]],
                            )
                        )
                    merge_state(state, {"model": character_model})
                dynamic_entry_breakpoints = {
                    candidate["decoder"]["entry_breakpoint"]
                    for candidate in spec["breakpoints"]
                    if isinstance(candidate.get("decoder"), dict)
                    and candidate["decoder"].get("format")
                    == "cbfd-character-draw-range"
                }
                if breakpoint["name"] in dynamic_entry_breakpoints:
                    stack_pointer = registers["sp"] & 0xFFFFFFFF
                    pending_character_draws.append(
                        {
                            "entry_breakpoint": breakpoint["name"],
                            "return_stack_pointer": (stack_pointer - 0x150)
                            & 0xFFFFFFFF,
                            "command_buffer_start": int(
                                state["model"]["command_buffer_start"]
                            )
                            & 0xFFFFFFFF,
                            "model": {
                                key: value
                                for key, value in state["model"].items()
                                if key != "active_records"
                            },
                        }
                    )
                event = {
                    "schema": SCHEMA,
                    "record_type": "draw_state",
                    "identity": identity,
                    "breakpoint": breakpoint["name"],
                    "hook_address": f"0x{parse_int(breakpoint['address'], 'breakpoint.address'):08X}",
                    "guest_pc": f"0x{guest_pc:08X}",
                    "hit_index": captured_count,
                    "breakpoint_hit_index": breakpoint_hits - 1,
                    "render_state_hash": state_hash(state),
                    "state": state,
                    "evidence": {
                        "registers": {name: f"0x{value:016X}" for name, value in registers.items()},
                        "memory": memory_evidence,
                    },
                }
                stream.write(json.dumps(event, sort_keys=True) + "\n")
                stream.flush()
                captured_count += 1
                breakpoint_capture_counts[breakpoint["name"]] = (
                    breakpoint_capture_counts.get(breakpoint["name"], 0) + 1
                )
                if breakpoint.get("stop_after_capture"):
                    break
                stop_after_capture_count = breakpoint.get("stop_after_capture_count")
                if (
                    stop_after_capture_count is not None
                    and breakpoint_capture_counts[breakpoint["name"]]
                    >= parse_int(
                        stop_after_capture_count,
                        f"{breakpoint['name']}.stop_after_capture_count",
                    )
                ):
                    break
                if captured_count < max_events:
                    debugger.resume()
    finally:
        debugger.close()
    print(f"Recorded {captured_count} draw-state event(s) in {destination.relative_to(Path.cwd())}.")
    return 0


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    subparsers = parser.add_subparsers(dest="command", required=True)
    record_parser = subparsers.add_parser("record", help="record debugger breakpoints as JSONL")
    record_parser.add_argument("--spec", required=True, help="versioned JSON trace specification")
    record_parser.add_argument("--output", required=True, help="JSONL path under build/")
    record_parser.add_argument("--bank", type=int)
    record_parser.add_argument("--entry", type=int)
    record_parser.add_argument("--segment", type=int)
    record_parser.add_argument("--material-run", dest="material_run", type=int)
    record_parser.add_argument("--max-events", type=int)
    record_parser.add_argument("--timeout", type=int, help="seconds to wait for each debugger stop")
    record_parser.add_argument(
        "--session-timeout",
        type=int,
        help="maximum wall-clock seconds for the complete trace session",
    )
    record_parser.add_argument("--savestate", help="optional savestate path under the mounted workspace")
    record_parser.add_argument(
        "--software-renderer", action="store_true",
        help="execute ROM RSP microcode and RDP rasterization with CXD4/Angrylion under Xvfb",
    )
    output_mode = record_parser.add_mutually_exclusive_group()
    output_mode.add_argument("--force", action="store_true")
    output_mode.add_argument("--append", action="store_true")
    record_parser.add_argument("mupen_args", nargs=argparse.REMAINDER)
    record_parser.set_defaults(handler=record)
    return parser


def main(argv: list[str] | None = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)
    if args.mupen_args and args.mupen_args[0] == "--":
        args.mupen_args = args.mupen_args[1:]
    try:
        return args.handler(args)
    except (OSError, json.JSONDecodeError, TraceError) as error:
        parser.error(str(error))
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
