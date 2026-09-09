"""ROM-native bank-09 pointer-table models consumed by func_1502FE10."""

from __future__ import annotations

import hashlib
import math
import struct
from dataclasses import replace
from typing import Any, Callable


def is_attachment_model(data: bytes) -> bool:
    """Recognize the third pair's terminator, not a geometry opcode signature."""
    return len(data) >= 24 and int.from_bytes(data[20:24], "big") >> 28 == 8


def parse_attachment_model(
    data: bytes, decode_geometry: Callable[..., Any]
) -> tuple[Any, dict[str, Any]]:
    """Decode the native container through a temporary direct-geometry view.

    func_1502FE10 exposes vertices at +0x18 and the three declared regions:
    part pointers, optional 16-byte joints, and CBFD XY normals. Only normal
    addresses are rebased in the temporary view. Native offsets and bytes are
    retained for reconstruction and runtime correlation.
    """
    if not is_attachment_model(data):
        raise ValueError("attachment model lacks its three-pair header terminator")
    words = struct.unpack_from(">6I", data)
    table, table_size, joint_offset, joint_size, normals, normal_flags = words
    normal_size = normal_flags & 0x0FFFFFFF
    if any(word & 0xF0000000 for word in words[:5]):
        raise ValueError("attachment model has unsupported header flags")
    if table < 24 or (table - 24) % 16 or not table_size or table_size % 4:
        raise ValueError("attachment vertex or part-table extent is invalid")
    for offset, size in ((table, table_size), (joint_offset, joint_size),
                         (normals, normal_size)):
        if bool(offset) != bool(size) or (offset and (offset < table or offset + size > len(data))):
            raise ValueError("attachment header range is outside its container")
    if table_size // 4 > 255 or joint_size % 16:
        raise ValueError("attachment part count or joint alignment is invalid")
    pointers = list(struct.unpack_from(f">{table_size // 4}I", data, table))
    display_start = min(pointers)
    display_end = normals or len(data)
    if (display_start & 7 or display_end <= display_start
            or (display_end - display_start) % 8
            or any(p < display_start or p >= display_end or p & 7 for p in pointers)
            or pointers != sorted(set(pointers))):
        raise ValueError("attachment part-list boundaries are invalid")
    ranges = sorted([(0, table + table_size), (display_start, display_end)]
                    + ([(joint_offset, joint_offset + joint_size)] if joint_offset else [])
                    + ([(normals, normals + normal_size)] if normals else []))
    cursor = 0
    for start, end in ranges:
        if start < cursor or any(data[cursor:start]):
            raise ValueError("attachment regions overlap or contain unknown nonzero gaps")
        cursor = end
    if any(data[cursor:]):
        raise ValueError("attachment has an unknown nonzero tail")
    next_start = display_start
    for pointer in pointers:
        if pointer != next_start:
            raise ValueError("attachment has a gap between part lists")
        for offset in range(pointer, display_end, 8):
            if struct.unpack_from(">II", data, offset) == (0xDF000000, 0):
                next_start = offset + 8
                break
        else:
            raise ValueError("attachment part list is unterminated")
    if any(data[next_start:display_end]):
        raise ValueError("attachment display-list padding is nonzero")
    display = bytearray(data[display_start:next_start])
    virtual_start = 40 + table - 24
    virtual_normals = virtual_start + len(display)
    for offset in range(0, len(display), 8):
        command, argument = struct.unpack_from(">II", display, offset)
        if command >> 24 == 0xDC:
            if (command != 0xDC38000E or not normals or argument < normals
                    or argument + 64 > normals + normal_size or (argument - normals) % 32):
                raise ValueError("attachment normal command is outside its declared region")
            struct.pack_into(">I", display, offset + 4, virtual_normals + argument - normals)
    virtual = (struct.pack(">10I", virtual_start, len(display),
                           virtual_normals if normal_size else 0, normal_size,
                           0, 0, 0, 0, 0, 0x80000000)
               + data[24:table] + display + data[normals:normals + normal_size])
    geometry = decode_geometry(virtual, allow_external_texture=True,
                               independent_display_lists=True)
    geometry = replace(
        geometry, display_list_offset=display_start, display_list_size=len(display),
        face_command_offsets=tuple(offset - virtual_start + display_start
                                   for offset in geometry.face_command_offsets),
        header_words=words, secondary_region=None,
    )
    joints = []
    for index in range(joint_size // 16):
        parent, matrix, animation, flags, *translation = struct.unpack_from(
            ">bBBB3f", data, joint_offset + index * 16
        )
        if parent < -1 or not all(math.isfinite(value) for value in translation):
            raise ValueError("attachment joint has an invalid parent or translation")
        joints.append({"record_index": index, "parent_matrix_index": parent,
                       "matrix_index": matrix, "animation_index": animation,
                       "flags": flags, "bind_pivot_f32": translation})
    expected = set(range(len(joints)))
    if ({joint["matrix_index"] for joint in joints} != expected
            or {joint["animation_index"] for joint in joints} != expected):
        raise ValueError("attachment joints do not cover each matrix/animation slot")
    parents = {joint["matrix_index"]: joint["parent_matrix_index"] for joint in joints}
    for slot in parents:
        seen = set()
        while slot >= 0:
            if slot in seen or slot not in parents:
                raise ValueError("attachment joint parent is absent or cyclic")
            seen.add(slot)
            slot = parents[slot]
    used = {slot for face in geometry.face_matrix_indices for slot in face}
    if used.difference(expected if joints else {0}):
        raise ValueError("attachment display list references an absent matrix")
    sections = []
    for name, offset, size in (
        ("display_lists", display_start, len(display)),
        ("normals", normals, normal_size),
    ):
        sections.append({"name": name, "offset": offset, "size": size,
                         "sha1": hashlib.sha1(data[offset:offset + size]).hexdigest(),
                         "file": f"regions/{{entry:04d}}-00-attachment-{name}.bin" if size else None})
    return geometry, {
        "family": "bank-09-three-pair-attachment-model", "header_size": 24,
        "decoded_size": len(data), "vertex_offset": 24, "vertex_size": table - 24,
        "pointer_table_offset": table, "pointer_table_size": table_size,
        "display_list_pointers": pointers, "display_list_count": len(pointers),
        "display_list_padding_size": display_end - next_start,
        "joint_offset": joint_offset, "joint_size": joint_size, "joints": joints,
        "normal_offset": normals, "normal_size": normal_size, "sections": sections,
        "runtime_evidence": {"loader": "func_1502FE10", "vertex_copy": "func_1502FFD8",
                             "renderer": "func_150311C4", "joint_wrapper": "func_1503F4B0",
                             "pose_builder": "func_150A81D0"},
        "pose_status": "neutral-joint-hierarchy; parent attachment transform requires runtime evidence",
    }


def encode_attachment_model(geometry: Any, layout: dict[str, Any], regions: dict[str, bytes]) -> bytes:
    """Rebuild native bytes from decoded vertices, pointers, joints and regions."""
    result = bytearray(layout["decoded_size"])
    struct.pack_into(">6I", result, 0, *geometry.header_words)
    vertex_data = b"".join(struct.pack(">hhhHhh4B", vertex.x, vertex.y, vertex.z,
                                     vertex.flag, vertex.s, vertex.t, *vertex.color)
                           for vertex in geometry.vertices)
    if len(vertex_data) != layout["vertex_size"]:
        raise ValueError("attachment reconstruction vertex extent changed")
    result[24:24 + len(vertex_data)] = vertex_data
    pointers = layout["display_list_pointers"]
    struct.pack_into(f">{len(pointers)}I", result, layout["pointer_table_offset"], *pointers)
    for joint in layout["joints"]:
        struct.pack_into(">bBBB3f", result, layout["joint_offset"] + joint["record_index"] * 16,
                         joint["parent_matrix_index"], joint["matrix_index"], joint["animation_index"],
                         joint["flags"], *joint["bind_pivot_f32"])
    for section in layout["sections"]:
        raw = regions[section["name"]]
        if len(raw) != section["size"] or hashlib.sha1(raw).hexdigest() != section["sha1"]:
            raise ValueError("attachment reconstruction region identity changed")
        result[section["offset"]:section["offset"] + len(raw)] = raw
    return bytes(result)
