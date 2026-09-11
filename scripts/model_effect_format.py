"""ROM effect meshes loaded from bank 09 by func_15183ACC and its wrappers."""

from __future__ import annotations

import hashlib
import struct
from dataclasses import dataclass, replace
from typing import Any, Callable


@dataclass(frozen=True)
class EffectModelSource:
    entry: int
    geometry_entry: int
    geometry_data: bytes
    material_entry: int
    material_data: bytes
    effect_type: int
    draw_setup_commands: tuple[tuple[int, int], ...] = ()


def is_effect_model(data: bytes) -> bool:
    """Recognize the four-pair terminator, independent of mesh opcodes."""
    return len(data) >= 32 and int.from_bytes(data[28:32], "big") >> 28 == 8


def effect_header(data: bytes) -> tuple[int, ...]:
    if not is_effect_model(data):
        raise ValueError("effect model lacks its four-pair header terminator")
    words = struct.unpack_from(">8I", data)
    if any(word & 0xF0000000 for word in words[:7]):
        raise ValueError("effect model has unsupported header flags")
    cursor = 32
    for pair in range(4):
        offset, size = words[pair * 2:pair * 2 + 2]
        size &= 0x0FFFFFFF
        alignment = 16 if pair < 2 else 8
        if bool(offset) != bool(size) or size % alignment:
            raise ValueError("effect model section extent is invalid")
        if not size:
            continue
        if offset < cursor or offset % 8 or offset + size > len(data):
            raise ValueError("effect model sections overlap or exceed their container")
        if any(data[cursor:offset]):
            raise ValueError("effect model has unknown nonzero section padding")
        cursor = offset + size
        if pair >= 2 and data[cursor - 8:cursor] != struct.pack(">II", 0xDF000000, 0):
            raise ValueError("effect model display list is unterminated")
        if pair >= 2 and any(data[pos] == 0xDF for pos in range(offset, cursor - 8, 8)):
            raise ValueError("effect model display list has an early terminator")
    if not words[1] or words[3] not in (0, words[1]):
        raise ValueError("effect model vertex buffers have incompatible extents")
    if any(data[cursor:]):
        raise ValueError("effect model has an unknown nonzero tail")
    return words


def verify_effect_consumers(code: bytes, code_base: int, data: bytes, data_base: int) -> tuple[int, ...]:
    """Pin native loading, shared lists, and the first-match material selector."""
    for start, size, sha1 in (
        (0x15183ACC, 216, "e5677352eb28fc3bcfe515e76af54de1c2c359c8"),
        (0x151838B0, 196, "a197453b5b61aec56dd06d1bc8fce8a8072b0b1b"),
        (0x15183974, 124, "9ed8b4c73b3669570d493a1d214a1b856d2bbb8e"),
        (0x151839F0, 220, "5558849e2c49a64f0e6478c0864dc7a88a7b09d5"),
        (0x15183BA4, 132, "6a7b200404f3cc9066be01be07c96cc127cb3cf9"),
        (0x15183290, 1568, "b7fe43d5b242d531aac06e54940d04541d5fa771"),
        (0x151770C8, 404, "1f2269e413d43602be88c373961441c76fbe4f65"),
        (0x151674F8, 1392, "1a4cc2434666765a39feb16096d26a83d4b8fcc3"),
        (0x15176DF0, 728, "89f939ac18b989879310621580740aac10fabdaa"),
        (0x15142FBC, 136, "e271c17f3ef050f70c77607be39588cf00d0c810"),
    ):
        offset = start - code_base
        if offset < 0 or hashlib.sha1(code[offset:offset + size]).hexdigest() != sha1:
            raise ValueError(f"ROM effect-model consumer changed at 0x{start:08X}")
    offset = 0x800A72D0 - data_base
    types = tuple(data[offset:offset + 11]) if offset >= 0 else ()
    if types != (10, 10, 21, 22, 23, 24, 20, 19, 68, 69, 19):
        raise ValueError("ROM effect-model material selector table changed")
    for effect_type in set(types):
        offset = 0x8008B4A8 + effect_type * 52 + 8 - data_base
        expected = (0x151770C8 if effect_type == 19 else 0x15176DF0, 0, 0, 0x15183BA4)
        if offset < 0 or data[offset:offset + 16] != struct.pack(">4I", *expected):
            raise ValueError("ROM effect-model render dispatch table changed")
    return types


def resolve_effect_sources(entries: dict[int, bytes], types: tuple[int, ...]) -> dict[int, EffectModelSource]:
    if types != (10, 10, 21, 22, 23, 24, 20, 19, 68, 69, 19):
        raise ValueError("effect source resolution requires the verified eleven-entry table")
    sources = {}
    for index, effect_type in enumerate(types):
        entry = index + 173
        # The native wrappers copy record+0x0C to the adjacent record+0x20.
        geometry_entry = {174: 173, 182: 181}.get(entry, entry)
        material_entry = types.index(effect_type) + 173
        try:
            own, geometry, material = (entries[e] for e in (entry, geometry_entry, material_entry))
        except KeyError as error:
            raise ValueError("effect model is missing a ROM dependency") from error
        own_header, geometry_header, material_header = map(effect_header, (own, geometry, material))
        if not geometry_header[7] & 0x0FFFFFFF or not material_header[5]:
            raise ValueError("effect model dependency has no required display list")
        if geometry_entry != entry and (own_header[7] & 0x0FFFFFFF or own_header[1] != geometry_header[1]):
            raise ValueError("effect model shared geometry contract changed")
        # Dispatcher clears lighting after the material callback. The general
        # renderer then calls func_15142FBC(0x82CA0, 0x504A50), which emits EF
        # with the low high-word nibble ORed with 15. Entry 183 uses the special
        # renderer branch instead, so its inherited OtherMode stays unknown.
        setup = ((0xD9FDFFFF, 0),)
        if entry != 183:
            setup += ((0xEF082CAF, 0x00504A50),)
        sources[entry] = EffectModelSource(entry, geometry_entry, geometry, material_entry,
                                         material, effect_type, setup)
    return sources


def parse_effect_model(data: bytes, decode_geometry: Callable[..., Any],
                       source: EffectModelSource | None = None) -> tuple[Any, dict[str, Any]]:
    words = effect_header(data)
    geometry_data = source.geometry_data if source else data
    material_data = source.material_data if source else data
    geometry_words, material_words = map(effect_header, (geometry_data, material_data))
    draw_offset, draw_flags = geometry_words[6:8]
    draw_size = draw_flags & 0x0FFFFFFF
    if not draw_size:
        raise ValueError("effect model requires a proven shared ROM triangle list")
    material_offset, material_size = material_words[4:6]
    # These are consecutive native calls. EndDL returns to the caller without
    # clearing RDP state; the virtual stream preserves exactly that ordering.
    setup = b"".join(struct.pack(">II", *pair) for pair in source.draw_setup_commands) if source else b""
    display = (material_data[material_offset:material_offset + material_size] + setup
               + geometry_data[draw_offset:draw_offset + draw_size])
    virtual_start = 40 + words[1]
    virtual = (struct.pack(">10I", virtual_start, len(display), 0, 0, 0, 0, 0, 0, 0, 0x80000000)
               + data[words[0]:words[0] + words[1]] + display)
    geometry = decode_geometry(virtual, allow_external_texture=True)
    first_draw = virtual_start + material_size + len(setup)
    if any(offset < first_draw for offset in geometry.face_command_offsets):
        raise ValueError("effect material list unexpectedly contains geometry")
    geometry = replace(geometry, display_list_offset=draw_offset, display_list_size=draw_size,
                       face_command_offsets=tuple(offset - first_draw + draw_offset
                                                  for offset in geometry.face_command_offsets),
                       header_words=words)
    buffers = []
    for offset, size in ((words[0], words[1]), (words[2], words[3])):
        buffers.append([list(vertex) for vertex in struct.iter_unpack(">hhhHhh4B", data[offset:offset + size])])
    sections = [{"name": name, "offset": words[pair * 2], "size": words[pair * 2 + 1] & 0x0FFFFFFF}
                for pair, name in ((2, "material"), (3, "geometry"))]
    for section in sections:
        raw = data[section["offset"]:section["offset"] + section["size"]]
        section["sha1"] = hashlib.sha1(raw).hexdigest()
        section["file"] = f"regions/{{entry:04d}}-00-effect-{section['name']}.bin" if raw else None
    return geometry, {
        "family": "bank-09-four-pair-effect-model", "header_size": 32, "decoded_size": len(data),
        "vertex_buffers": buffers, "vertex_offsets": [words[0], words[2]],
        "vertex_buffers_identical": buffers[0] == buffers[1] if buffers[1] else None,
        "preview_vertex_buffer": 0, "sections": sections,
        "geometry_source_entry": source.geometry_entry if source else None,
        "geometry_source_sha1": hashlib.sha1(geometry_data).hexdigest(),
        "material_source_entry": source.material_entry if source else None,
        "material_source_sha1": hashlib.sha1(material_data).hexdigest(),
        "effect_type": source.effect_type if source else None,
        "draw_setup_commands": [list(pair) for pair in source.draw_setup_commands] if source else [],
        "runtime_evidence": {"loader": "func_15183ACC", "material_selector": "func_15183BA4",
                             "shared_geometry_loaders": ["func_151838B0", "func_15183974"],
                             "dispatcher": "func_151674F8", "other_mode_setter": "func_15142FBC",
                             "renderers": ["func_15176DF0", "func_151770C8"]},
        "appearance_status": "ROM vertex buffer and proven renderer defaults; runtime deformation, environment colour and native raster parity unresolved",
    }


def encode_effect_model(geometry: Any, layout: dict[str, Any], regions: dict[str, bytes]) -> bytes:
    result = bytearray(layout["decoded_size"])
    struct.pack_into(">8I", result, 0, *geometry.header_words)
    decoded = [[v.x, v.y, v.z, v.flag, v.s, v.t, *v.color] for v in geometry.vertices]
    if decoded != layout["vertex_buffers"][0]:
        raise ValueError("effect reconstruction disagrees with decoded primary vertices")
    for offset, vertices in zip(layout["vertex_offsets"], layout["vertex_buffers"]):
        raw = b"".join(struct.pack(">hhhHhh4B", *vertex) for vertex in vertices)
        result[offset:offset + len(raw)] = raw
    for section in layout["sections"]:
        raw = regions[section["name"]]
        if len(raw) != section["size"] or hashlib.sha1(raw).hexdigest() != section["sha1"]:
            raise ValueError("effect reconstruction section identity changed")
        result[section["offset"]:section["offset"] + len(raw)] = raw
    return bytes(result)
