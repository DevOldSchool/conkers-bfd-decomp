#!/usr/bin/env python3
"""Survey, extract, verify, and prepare previews of US model geometry."""

from __future__ import annotations

import argparse
import hashlib
import json
import math
import shutil
import struct
from dataclasses import dataclass, replace
from pathlib import Path
from typing import Any

try:
    from scripts.rzip_archive import (
        decode_rzip_chunk,
        normalize_rom,
        parse_asset_banks,
        parse_asset_entries,
        parse_game_archive,
    )
    from scripts.rzip_extract import (
        ROOT,
        display_path,
        load_layout,
        manifest_source,
        prepare_output,
    )
except ModuleNotFoundError:
    from rzip_archive import (  # type: ignore[no-redef]
        decode_rzip_chunk,
        normalize_rom,
        parse_asset_banks,
        parse_asset_entries,
        parse_game_archive,
    )
    from rzip_extract import (  # type: ignore[no-redef]
        ROOT,
        display_path,
        load_layout,
        manifest_source,
        prepare_output,
    )


BANK_INDICES = (0x01, 0x03, 0x04, 0x09)
DEFAULT_BANK_INDEX = 0x04
# Bank-02 entry 0, pair 6 is a compact runtime pose for the highest-detail
# Conker model. Keep the numeric identity explicit until animation IDs are named.
CHARACTER_PREVIEW_POSE_PAIRS = {0: 6}
PREVIEW_TEXTURE_FAMILIES = (
    "us",
    "us-1056-proven",
    "us-ci8-proven",
    "us-rgba16-proven",
    "us-native-proven",
    "us-tiled-views",
)
GLTF_REPEAT = 10497
GLTF_CLAMP_TO_EDGE = 33071
GLTF_MIRRORED_REPEAT = 33648
RUNTIME_RENDER_STATE_TABLE_BASES = tuple(
    range(0x80082FC0, 0x80083EC0 + 1, 0x180)
)
RUNTIME_RENDER_STATE_OFFSETS = tuple(range(0, 0x180, 0x10))
COLOR_AB_MUX = {
    0: "COMBINED",
    1: "TEXEL0",
    2: "TEXEL1",
    3: "PRIMITIVE",
    4: "SHADE",
    5: "ENVIRONMENT",
    6: "ONE",
    7: "NOISE",
    15: "ZERO",
}
COLOR_C_MUX = {
    0: "COMBINED",
    1: "TEXEL0",
    2: "TEXEL1",
    3: "PRIMITIVE",
    4: "SHADE",
    5: "ENVIRONMENT",
    6: "CENTER_OR_SCALE",
    7: "COMBINED_ALPHA",
    8: "TEXEL0_ALPHA",
    9: "TEXEL1_ALPHA",
    10: "PRIMITIVE_ALPHA",
    11: "SHADE_ALPHA",
    12: "ENVIRONMENT_ALPHA",
    13: "LOD_FRACTION",
    14: "PRIM_LOD_FRAC",
    15: "K5",
    31: "ZERO",
}
COLOR_D_MUX = {
    0: "COMBINED",
    1: "TEXEL0",
    2: "TEXEL1",
    3: "PRIMITIVE",
    4: "SHADE",
    5: "ENVIRONMENT",
    6: "ONE",
    7: "ZERO",
}
ALPHA_ABD_MUX = {
    0: "COMBINED",
    1: "TEXEL0",
    2: "TEXEL1",
    3: "PRIMITIVE",
    4: "SHADE",
    5: "ENVIRONMENT",
    6: "ONE",
    7: "ZERO",
}
ALPHA_C_MUX = {
    0: "LOD_FRACTION",
    1: "TEXEL0",
    2: "TEXEL1",
    3: "PRIMITIVE",
    4: "SHADE",
    5: "ENVIRONMENT",
    6: "PRIM_LOD_FRAC",
    7: "ZERO",
}


@dataclass(frozen=True)
class ModelSegment:
    index: int
    offset: int
    size: int
    final_flag: bool
    data: bytes


@dataclass(frozen=True)
class ModelBundle:
    index: int
    type_flags: int
    compressed: bool
    data: bytes
    segments: tuple[ModelSegment, ...]


@dataclass(frozen=True)
class ModelVertex:
    x: int
    y: int
    z: int
    flag: int
    s: int
    t: int
    color: tuple[int, int, int, int]


@dataclass(frozen=True)
class ModelRegion:
    offset: int
    size: int


@dataclass(frozen=True)
class VertexColorAnimationDescriptor:
    color_data_offset: int
    vertex_index_offset: int
    vertex_count: int
    max_vertex_index: int


@dataclass(frozen=True)
class ModelTextureReference:
    image_command: int
    encoded_argument: int
    flat_index: int
    mode: int


@dataclass(frozen=True)
class ModelTextureBinding:
    image_command: int
    flat_index: int | None = None
    mode: int | None = None
    segment: int | None = None
    offset: int | None = None
    external: bool = False
    load_command: tuple[int, int] | None = None


@dataclass(frozen=True)
class ModelMaterialRun:
    first_face: int
    face_count: int
    texture_enabled: bool
    pixel: ModelTextureBinding | None
    palette: ModelTextureBinding | None
    render_tile: tuple[int, int] | None
    tile_bounds: tuple[int, int] | None
    texture_scale: tuple[int, int] | None
    combine_mode: tuple[int, int] | None
    other_mode: tuple[int, int] | None
    runtime_render_state_offset: int | None
    texture_coordinates_proven: bool = True
    matrix_index: int | None = None


@dataclass(frozen=True)
class ModelGeometry:
    vertices: tuple[ModelVertex, ...]
    faces: tuple[tuple[int, int, int], ...]
    display_list_offset: int
    display_list_size: int
    vertex_load_count: int
    segment_8_display_list_offsets: tuple[int, ...]
    secondary_region: ModelRegion | None
    tertiary_region: ModelRegion | None
    vertex_color_animation_offset: int | None
    vertex_color_animation_table_size: int
    vertex_color_animation_descriptors: tuple[
        VertexColorAnimationDescriptor, ...
    ]
    texture_references: tuple[ModelTextureReference, ...]
    runtime_segment_texture_addresses: tuple[tuple[int, int], ...]
    material_runs: tuple[ModelMaterialRun, ...]
    header_words: tuple[int, ...]


@dataclass(frozen=True)
class PreviewTexture:
    family: str
    source: Path
    flat_index: int
    format: int
    size: int
    width: int
    height: int
    sha1: str


PLACEMENT_RECORD_SIZE = 0x44
PLACEMENT_BANKS = (0x0B, 0x0C)


def nested_asset_payload(data: bytes, index: int) -> bytes:
    """Return one exact child from an in-memory indexed asset table."""

    if len(data) < 8:
        raise ValueError("nested asset table is shorter than one descriptor")
    table_size = struct.unpack_from(">I", data, 0)[0]
    if not table_size or table_size % 8 or table_size > len(data):
        raise ValueError("nested asset table has an invalid descriptor span")
    if index < 0 or index >= table_size // 8:
        raise ValueError(f"nested asset index {index} is outside the table")
    start, size_flags = struct.unpack_from(">II", data, index * 8)
    size = size_flags & 0x00FFFFFF
    if start < table_size or start + size > len(data):
        raise ValueError(f"nested asset index {index} has an invalid range")
    return data[start : start + size]


def parse_placement_records(
    data: bytes, *, allow_alignment_padding: bool
) -> tuple[tuple[bytes, ...], bytes]:
    """Split the runtime-proven 0x44-byte placement records without naming fields."""

    record_count, remainder = divmod(len(data), PLACEMENT_RECORD_SIZE)
    padding = data[record_count * PLACEMENT_RECORD_SIZE :]
    if remainder and (
        not allow_alignment_padding or remainder >= 16 or any(padding)
    ):
        raise ValueError("placement payload has invalid trailing bytes")
    return (
        tuple(
            data[offset : offset + PLACEMENT_RECORD_SIZE]
            for offset in range(0, record_count * PLACEMENT_RECORD_SIZE, PLACEMENT_RECORD_SIZE)
        ),
        padding,
    )


def placement_record_manifest(record: bytes, index: int) -> dict[str, Any]:
    if len(record) != PLACEMENT_RECORD_SIZE:
        raise ValueError("placement record is not 0x44 bytes")
    scale = struct.unpack_from(">3f", record, 0x20)
    if not all(math.isfinite(value) for value in scale):
        raise ValueError("placement record contains a non-finite scale vector")
    dispatch_kind = struct.unpack_from(">I", record, 0x0C)[0]
    model_or_dispatch_index = struct.unpack_from(">I", record, 0x10)[0]
    return {
        "index": index,
        "sha1": hashlib.sha1(record).hexdigest(),
        "position_s16_00": list(struct.unpack_from(">3h", record, 0x00)),
        "rotation_degrees_s16_06": list(struct.unpack_from(">3h", record, 0x06)),
        "dispatch_kind": dispatch_kind,
        "model_index": model_or_dispatch_index if dispatch_kind == 0 else None,
        "dispatch_index": model_or_dispatch_index if dispatch_kind != 0 else None,
        "word_14": f"0x{struct.unpack_from('>I', record, 0x14)[0]:08X}",
        "word_18": f"0x{struct.unpack_from('>I', record, 0x18)[0]:08X}",
        "word_1c": f"0x{struct.unpack_from('>I', record, 0x1C)[0]:08X}",
        "scale_f32_20": list(scale),
        "bytes_2c_37": record[0x2C:0x38].hex(),
        "word_38": f"0x{struct.unpack_from('>I', record, 0x38)[0]:08X}",
        "bytes_3c_3f": record[0x3C:0x40].hex(),
        "halfwords_40": list(struct.unpack_from(">2H", record, 0x40)),
        "raw_hex": record.hex(),
    }


def placement_transform_matrix(record: dict[str, Any]) -> list[float]:
    """Reproduce the static object transform built by func_1511490C.

    Conker stores row-vector matrices. The glTF array below is the transpose of
    that matrix, expressed in glTF's column-vector convention. Runtime order is
    scale followed by the rotation composed as Y, Z, X; the initial dynamic
    vertical displacement is zero, so the record position is used verbatim.
    """

    x_degrees, y_degrees, z_degrees = record["rotation_degrees_s16_06"]
    x, y, z = (math.radians(value) for value in (x_degrees, y_degrees, z_degrees))
    sx, sy, sz = record["scale_f32_20"]
    tx, ty, tz = record["position_s16_00"]
    cx, cy, cz = math.cos(x), math.cos(y), math.cos(z)
    sin_x, sin_y, sin_z = math.sin(x), math.sin(y), math.sin(z)

    # This is the transpose of M(x, 0, z) * M(0, y, 0), the exact row-vector
    # composition performed by func_151148A8.
    rotation = (
        (
            cz * cy,
            -cx * sin_z * cy + sin_x * sin_y,
            sin_x * sin_z * cy + cx * sin_y,
        ),
        (sin_z, cx * cz, -sin_x * cz),
        (
            -cz * sin_y,
            cx * sin_z * sin_y + sin_x * cy,
            -sin_x * sin_z * sin_y + cx * cy,
        ),
    )
    scale = (sx, sy, sz)
    rows = [
        [rotation[row][column] * scale[column] for column in range(3)]
        + [float((tx, ty, tz)[row])]
        for row in range(3)
    ]
    rows.append([0.0, 0.0, 0.0, 1.0])
    return [rows[row][column] for column in range(4) for row in range(4)]


def parse_model_bundle(data: bytes) -> tuple[ModelSegment, ...]:
    """Parse the exact descriptor layout shared by every decoded US bank-04 file."""

    if len(data) < 0x20:
        raise ValueError("bank-04 bundle is shorter than its minimum descriptor table")
    header_size = struct.unpack_from(">I", data, 0)[0]
    if header_size < 0x20 or header_size % 8 or header_size > len(data):
        raise ValueError("bank-04 bundle has an invalid descriptor-table size")

    segments = []
    expected_offset = header_size
    descriptor_count = header_size // 8
    for index in range(descriptor_count):
        offset, size_flags = struct.unpack_from(">II", data, index * 8)
        if size_flags & 0x70000000:
            raise ValueError(
                f"bank-04 segment {index} uses unsupported descriptor flags"
            )
        size = size_flags & 0x0FFFFFFF
        final_flag = bool(size_flags & 0x80000000)
        if offset != expected_offset or offset % 8 or size % 8:
            raise ValueError(
                f"bank-04 segment {index} is not an aligned contiguous range"
            )
        end = offset + size
        if end > len(data):
            raise ValueError(f"bank-04 segment {index} extends beyond its bundle")
        if final_flag != (index == descriptor_count - 1):
            raise ValueError("bank-04 final flag is not confined to the last segment")
        segments.append(
            ModelSegment(
                index=index,
                offset=offset,
                size=size,
                final_flag=final_flag,
                data=data[offset:end],
            )
        )
        expected_offset = end
    if expected_offset != len(data):
        raise ValueError("bank-04 segments do not consume the decoded bundle")
    return tuple(segments)


def encode_model_bundle(segments: tuple[ModelSegment, ...]) -> bytes:
    if len(segments) < 4:
        raise ValueError("bank-04 bundle requires at least four segments")
    header_size = len(segments) * 8
    offset = header_size
    descriptors = bytearray()
    payload = bytearray()
    for index, segment in enumerate(segments):
        if segment.index != index or segment.size != len(segment.data):
            raise ValueError("bank-04 segment metadata does not match its payload")
        if segment.size % 8 or segment.final_flag != (index == len(segments) - 1):
            raise ValueError("bank-04 segment alignment or final flag is invalid")
        descriptors.extend(
            struct.pack(
                ">II",
                offset,
                segment.size | (0x80000000 if segment.final_flag else 0),
            )
        )
        payload.extend(segment.data)
        offset += segment.size
    return bytes(descriptors + payload)


def packed_four_triangle_indices(command: int, argument: int) -> tuple[int, ...]:
    """Decode the 12 five-bit cache indices used by Conker opcodes 0x10-0x1f."""

    return (
        (argument >> 25) & 0x1F,
        (argument >> 20) & 0x1F,
        (argument >> 15) & 0x1F,
        (argument >> 10) & 0x1F,
        (argument >> 5) & 0x1F,
        argument & 0x1F,
        (command >> 10) & 0x1F,
        (command >> 5) & 0x1F,
        command & 0x1F,
        (command >> 23) & 0x1F,
        (command >> 18) & 0x1F,
        ((argument >> 30) & 0x3) | (((command >> 15) & 0x7) << 2),
    )


def parse_model_region(
    data: bytes, offset: int, size: int, name: str
) -> ModelRegion | None:
    if not offset:
        if size:
            raise ValueError(f"model {name} region has a size without an offset")
        return None
    if not size or offset < 0x28 or offset + size > len(data):
        raise ValueError(f"model {name} region is outside its segment")
    return ModelRegion(offset=offset, size=size)


def parse_vertex_color_animation(
    data: bytes, table_offset: int, table_size: int, vertex_count: int
) -> tuple[VertexColorAnimationDescriptor, ...]:
    """Decode the sentinel-terminated descriptors consumed by func_151739B0."""

    if not table_offset:
        if table_size:
            raise ValueError("vertex-color animation has a size without a table")
        return ()
    if (
        table_offset < 0x28
        or table_offset % 4
        or table_size < 12
        or table_size % 12
        or table_offset + table_size > len(data)
    ):
        raise ValueError("vertex-color animation table has an invalid range")

    descriptors = []
    offset = table_offset
    table_end = table_offset + table_size
    while offset < table_end:
        color_offset, index_offset, count = struct.unpack_from(">III", data, offset)
        if not color_offset:
            if offset + 12 != table_end:
                raise ValueError("vertex-color animation terminator is not last")
            break
        if (
            not count
            or color_offset + count * 3 > len(data)
            or index_offset + count * 2 > len(data)
        ):
            raise ValueError("vertex-color animation descriptor is outside its model")
        indices = struct.unpack_from(f">{count}H", data, index_offset)
        if max(indices) >= vertex_count:
            raise ValueError("vertex-color animation references an invalid vertex")
        descriptors.append(
            VertexColorAnimationDescriptor(
                color_data_offset=color_offset,
                vertex_index_offset=index_offset,
                vertex_count=count,
                max_vertex_index=max(indices),
            )
        )
        offset += 12
    else:
        raise ValueError("vertex-color animation table is not terminated")
    return tuple(descriptors)


def parse_model_geometry(
    data: bytes, *, allow_external_texture: bool = False
) -> ModelGeometry:
    """Decode the proven vertex and triangle portions of one bank-04 model."""

    if len(data) < 0x30:
        raise ValueError("model candidate is shorter than its header and display list")
    header_words = struct.unpack_from(">10I", data, 0)
    display_offset, display_size = header_words[:2]
    if (
        display_offset < 0x28
        or (display_offset - 0x28) % 16
        or display_size == 0
        or display_size % 8
        or display_offset + display_size > len(data)
    ):
        raise ValueError("model candidate has invalid vertex/display-list boundaries")
    if data[display_offset + display_size - 8] != 0xDF:
        raise ValueError("model candidate lacks its final DF display-list command")
    if header_words[6] or header_words[7]:
        raise ValueError("model reserved header words are not zero")

    secondary_region = parse_model_region(
        data, header_words[2], header_words[3], "secondary"
    )
    tertiary_region = parse_model_region(
        data, header_words[4], header_words[5], "tertiary"
    )
    for region in (secondary_region, tertiary_region):
        if region is not None and region.offset < display_offset + display_size:
            raise ValueError("model auxiliary region overlaps its primary display list")
    if (
        secondary_region is not None
        and tertiary_region is not None
        and secondary_region.offset + secondary_region.size > tertiary_region.offset
    ):
        raise ValueError("model secondary and tertiary regions overlap")

    vertices = []
    for offset in range(0x28, display_offset, 16):
        x, y, z, flag, s, t = struct.unpack_from(">hhhHhh", data, offset)
        vertices.append(
            ModelVertex(
                x=x,
                y=y,
                z=z,
                flag=flag,
                s=s,
                t=t,
                color=tuple(data[offset + 12 : offset + 16]),
            )
        )

    cache: dict[int, int] = {}
    faces = []
    vertex_load_count = 0
    segment_8_display_list_offsets = []
    texture_references = []
    runtime_segment_texture_addresses = []
    pending_texture: ModelTextureBinding | None = None
    pixel_texture: ModelTextureBinding | None = None
    palette_texture: ModelTextureBinding | None = None
    texture_enabled = False
    render_tile: tuple[int, int] | None = None
    tile_bounds: tuple[int, int] | None = None
    texture_scale: tuple[int, int] | None = None
    combine_mode: tuple[int, int] | None = None
    other_mode: tuple[int, int] | None = None
    runtime_render_state_offset: int | None = None
    matrix_index: int | None = None
    material_runs: list[list[Any]] = []

    def append_faces(cache_indices: tuple[int, ...], command_offset: int) -> None:
        first_face = len(faces)
        for index in range(0, len(cache_indices), 3):
            triangle = cache_indices[index : index + 3]
            if any(cache_index not in cache for cache_index in triangle):
                raise ValueError(
                    f"display-list triangle at 0x{command_offset:X} uses an unloaded vertex"
                )
            faces.append(tuple(cache[cache_index] for cache_index in triangle))
        face_count = len(faces) - first_face
        nonlocal pixel_texture
        if texture_enabled and pixel_texture is None:
            if not allow_external_texture:
                raise ValueError(
                    f"textured triangles at 0x{command_offset:X} have no loaded image"
                )
            pixel_texture = ModelTextureBinding(image_command=0, external=True)
        active_pixel = pixel_texture if texture_enabled else None
        render_format = (
            (render_tile[0] >> 21) & 7 if render_tile is not None else None
        )
        render_size = (
            (render_tile[0] >> 19) & 3 if render_tile is not None else None
        )
        uses_character_tlut_load = (
            active_pixel is not None
            and active_pixel.image_command == 0xFD100000
            and render_format == 0
            and render_size in (0, 1)
            and palette_texture is not None
            and palette_texture.flat_index == active_pixel.flat_index
            and palette_texture.mode == 2 - render_size
        )
        active_palette = (
            palette_texture
            if active_pixel is not None
            and (
                active_pixel.image_command == 0xFD500000
                or uses_character_tlut_load
            )
            else None
        )
        active_render_tile = render_tile if texture_enabled else None
        active_tile_bounds = tile_bounds if texture_enabled else None
        active_texture_scale = texture_scale if texture_enabled else None
        key = (
            texture_enabled,
            active_pixel,
            active_palette,
            active_render_tile,
            active_tile_bounds,
            active_texture_scale,
            combine_mode,
            other_mode,
            runtime_render_state_offset,
            matrix_index,
        )
        if material_runs and tuple(material_runs[-1][2:]) == key:
            material_runs[-1][1] += face_count
        else:
            material_runs.append(
                [
                    first_face,
                    face_count,
                    texture_enabled,
                    active_pixel,
                    active_palette,
                    active_render_tile,
                    active_tile_bounds,
                    active_texture_scale,
                    combine_mode,
                    other_mode,
                    runtime_render_state_offset,
                    matrix_index,
                ]
            )

    for offset in range(display_offset, display_offset + display_size, 8):
        command, argument = struct.unpack_from(">II", data, offset)
        opcode = command >> 24
        if opcode == 0x01:
            count = (command >> 12) & 0xFF
            cache_end = (command >> 1) & 0x7F
            cache_start = cache_end - count
            vertex_byte_offset = argument & 0xFFFFFF
            vertex_start = vertex_byte_offset // 16
            if (
                argument >> 24 != 0x01
                or count == 0
                or cache_start < 0
                or cache_end > 32
                or vertex_byte_offset % 16
                or vertex_start + count > len(vertices)
            ):
                raise ValueError(f"invalid vertex load at display-list offset 0x{offset:X}")
            for local_index in range(count):
                cache[cache_start + local_index] = vertex_start + local_index
            vertex_load_count += 1
        elif opcode == 0x05:
            append_faces(
                tuple(value // 2 for value in command.to_bytes(4, "big")[1:4]),
                offset,
            )
        elif opcode == 0x06:
            encoded = command.to_bytes(4, "big")[1:4] + argument.to_bytes(4, "big")[1:4]
            append_faces(tuple(value // 2 for value in encoded), offset)
        elif 0x10 <= opcode <= 0x1F:
            append_faces(packed_four_triangle_indices(command, argument), offset)
        elif opcode == 0xDE:
            if command != 0xDE000000 or argument >> 24 != 0x08 or argument & 7:
                raise ValueError(
                    f"unsupported display-list branch at offset 0x{offset:X}"
                )
            segment_8_display_list_offsets.append(argument & 0xFFFFFF)
            runtime_render_state_offset = argument & 0xFFFFFF
            other_mode = None
        elif opcode == 0xDA:
            if command != 0xDA380003 or argument >> 24 != 0x03 or argument & 0x3F:
                raise ValueError(f"unsupported matrix command at offset 0x{offset:X}")
            matrix_index = (argument & 0xFFFFFF) // 0x40
        elif opcode == 0xFD:
            if argument >> 24 == 0:
                flat_index = argument & 0x3FFFFF
                if flat_index >= 0x1E52:
                    raise ValueError("model texture reference exceeds the flat archive")
                texture_references.append(
                    ModelTextureReference(
                        image_command=command,
                        encoded_argument=argument,
                        flat_index=flat_index,
                        mode=argument >> 22,
                    )
                )
                pending_texture = ModelTextureBinding(
                    image_command=command,
                    flat_index=flat_index,
                    mode=argument >> 22,
                )
            else:
                if argument >> 28:
                    raise ValueError("model texture reference has an invalid segment")
                runtime_segment_texture_addresses.append(
                    (argument >> 24, argument & 0xFFFFFF)
                )
                pending_texture = ModelTextureBinding(
                    image_command=command,
                    segment=argument >> 24,
                    offset=argument & 0xFFFFFF,
                )
        elif opcode == 0xF3:
            pixel_texture = (
                replace(pending_texture, load_command=(command, argument))
                if pending_texture is not None
                else None
            )
        elif opcode == 0xF0:
            palette_texture = (
                replace(pending_texture, load_command=(command, argument))
                if pending_texture is not None
                else None
            )
        elif opcode == 0xF5 and (argument >> 24) & 7 == 0:
            render_tile = (command, argument)
        elif opcode == 0xF2 and (argument >> 24) & 7 == 0:
            tile_bounds = (command, argument)
        elif opcode == 0xD7:
            texture_enabled = bool(command & 2)
            texture_scale = (command, argument)
        elif opcode == 0xFC:
            combine_mode = (command, argument)
        elif opcode == 0xEF:
            other_mode = (command, argument)
            runtime_render_state_offset = None

    if not faces and not allow_external_texture:
        raise ValueError("model candidate display list contains no triangles")
    if sum(run[1] for run in material_runs) != len(faces):
        raise ValueError("model material runs do not cover every primary face")
    if not header_words[9] & 0x80000000:
        raise ValueError("model header flag bit 31 is not set")
    vertex_color_animation_table_size = header_words[9] & 0x7FFFFFFF
    vertex_color_animation_descriptors = parse_vertex_color_animation(
        data, header_words[8], vertex_color_animation_table_size, len(vertices)
    )
    return ModelGeometry(
        vertices=tuple(vertices),
        faces=tuple(faces),
        display_list_offset=display_offset,
        display_list_size=display_size,
        vertex_load_count=vertex_load_count,
        segment_8_display_list_offsets=tuple(segment_8_display_list_offsets),
        secondary_region=secondary_region,
        tertiary_region=tertiary_region,
        vertex_color_animation_offset=header_words[8] or None,
        vertex_color_animation_table_size=vertex_color_animation_table_size,
        vertex_color_animation_descriptors=vertex_color_animation_descriptors,
        texture_references=tuple(texture_references),
        runtime_segment_texture_addresses=tuple(
            runtime_segment_texture_addresses
        ),
        material_runs=tuple(
            ModelMaterialRun(
                first_face=run[0],
                face_count=run[1],
                texture_enabled=run[2],
                pixel=run[3],
                palette=run[4],
                render_tile=run[5],
                tile_bounds=run[6],
                texture_scale=run[7],
                combine_mode=run[8],
                other_mode=run[9],
                runtime_render_state_offset=run[10],
                matrix_index=run[11],
            )
            for run in material_runs
        ),
        header_words=header_words,
    )


def parse_character_model_geometry(
    data: bytes,
) -> tuple[ModelGeometry, dict[str, Any]]:
    """Decode the bank-01 character-model container used by func_1503CF20.

    Its display lists address vertices relative to the 0x38-byte native header,
    while the direct-model parser addresses its vertex array from zero. A
    temporary, lossless command view rebases only opcode-01 vertex addresses;
    every native region and pointer remains recorded against the original data.
    """

    if len(data) < 0x40:
        raise ValueError("bank-01 character model is shorter than its header")
    header_words = struct.unpack_from(">14I", data, 0)
    pairs = tuple(
        (header_words[index], header_words[index + 1])
        for index in range(0, 14, 2)
    )
    for pair_index, (offset, size_flags) in enumerate(pairs):
        size = size_flags & (0x7FFFFFFF if pair_index == 6 else 0xFFFFFFFF)
        if bool(offset) != bool(size):
            if pair_index != 6 or offset or size:
                raise ValueError(
                    f"bank-01 header pair {pair_index} has only one range component"
                )
        if offset and (offset < 0x38 or offset + size > len(data)):
            raise ValueError(f"bank-01 header pair {pair_index} is outside its model")

    vertex_end = header_words[0] or header_words[2]
    if vertex_end < 0x38 or (vertex_end - 0x38) % 16:
        raise ValueError("bank-01 character vertex region has invalid boundaries")
    vertex_data = data[0x38:vertex_end]

    display_list_pointers: list[int] = []
    pointer_tables = []
    for name, offset_index, size_index in (
        ("primary", 2, 3),
        ("secondary", 10, 11),
    ):
        offset, size = header_words[offset_index], header_words[size_index]
        if not offset:
            pointer_tables.append(
                {"name": name, "offset": None, "size": 0, "pointers": []}
            )
            continue
        if size % 4:
            raise ValueError(f"bank-01 {name} display-list table is not word-sized")
        pointers = list(struct.unpack_from(f">{size // 4}I", data, offset))
        display_list_pointers.extend(pointers)
        pointer_tables.append(
            {
                "name": name,
                "offset": f"0x{offset:X}",
                "size": size,
                "pointers": [f"0x{pointer:X}" for pointer in pointers],
            }
        )
    if not display_list_pointers:
        raise ValueError("bank-01 character model has no display-list pointers")
    display_offset = min(display_list_pointers)
    later_offsets = [
        offset
        for offset, _ in pairs
        if offset and offset > display_offset
    ]
    display_end = min(later_offsets, default=len(data))
    if (
        display_offset % 4
        or display_end <= display_offset
        or (display_end - display_offset) % 8
        or any(
            pointer < display_offset
            or pointer >= display_end
            or (pointer - display_offset) % 8
            for pointer in display_list_pointers
        )
    ):
        raise ValueError("bank-01 character display-list region is invalid")

    display_data = bytearray(data[display_offset:display_end])
    end_count = 0
    last_end_offset = 0
    for relative_offset in range(0, len(display_data), 8):
        command, argument = struct.unpack_from(">II", display_data, relative_offset)
        opcode = command >> 24
        if opcode == 0x01:
            vertex_byte_offset = argument & 0xFFFFFF
            if argument >> 24 != 0x01 or vertex_byte_offset < 0x38:
                raise ValueError("bank-01 vertex command has an invalid segment address")
            rebased = vertex_byte_offset - 0x38
            if rebased % 16:
                raise ValueError("bank-01 vertex command is not vertex-aligned")
            struct.pack_into(">I", display_data, relative_offset + 4, 0x01000000 | rebased)
        elif opcode == 0xDF:
            if command != 0xDF000000 or argument:
                raise ValueError("bank-01 character model has a malformed EndDL")
            end_count += 1
            last_end_offset = relative_offset + 8
    if end_count != len(display_list_pointers):
        raise ValueError(
            "bank-01 display-list pointer and EndDL counts do not agree"
        )
    display_padding_size = len(display_data) - last_end_offset
    if display_padding_size < 0 or any(display_data[last_end_offset:]):
        raise ValueError("bank-01 display-list region has nonzero trailing data")
    del display_data[last_end_offset:]

    synthetic_display_offset = 0x28 + len(vertex_data)
    synthetic = (
        struct.pack(
            ">10I",
            synthetic_display_offset,
            len(display_data),
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0x80000000,
        )
        + vertex_data
        + display_data
    )
    geometry = parse_model_geometry(synthetic, allow_external_texture=True)
    character_material_runs = []
    for run in geometry.material_runs:
        try:
            texture_coordinate_state(run)
        except ValueError:
            run = replace(run, texture_coordinates_proven=False)
        character_material_runs.append(run)
    geometry = ModelGeometry(
        vertices=geometry.vertices,
        faces=geometry.faces,
        display_list_offset=display_offset,
        display_list_size=len(display_data),
        vertex_load_count=geometry.vertex_load_count,
        segment_8_display_list_offsets=geometry.segment_8_display_list_offsets,
        secondary_region=None,
        tertiary_region=None,
        vertex_color_animation_offset=None,
        vertex_color_animation_table_size=0,
        vertex_color_animation_descriptors=(),
        texture_references=geometry.texture_references,
        runtime_segment_texture_addresses=geometry.runtime_segment_texture_addresses,
        material_runs=tuple(character_material_runs),
        header_words=header_words,
    )
    section_names = (
        "vertex_boundary_table",
        "primary_display_list_pointer_table",
        "joint_table",
        "texture_descriptor_table",
        "unresolved_character_auxiliary_data",
        "secondary_display_list_pointer_table",
        "unresolved_character_tail_data",
    )
    sections = []
    for index, ((offset, size_flags), name) in enumerate(zip(pairs, section_names)):
        size = size_flags & (0x7FFFFFFF if index == 6 else 0xFFFFFFFF)
        sections.append(
            {
                "index": index,
                "name": name,
                "offset": f"0x{offset:X}" if offset else None,
                "size": size,
                "flags": (
                    f"0x{size_flags & 0x80000000:08X}" if index == 6 else None
                ),
                "sha1": (
                    hashlib.sha1(data[offset : offset + size]).hexdigest()
                    if offset and size
                    else None
                ),
                "file": (
                    f"character-regions/{{entry:04d}}-{index:02d}-{name}.bin"
                    if offset and size
                    else None
                ),
            }
        )
    joint_offset, joint_size = header_words[4], header_words[5]
    if joint_size % 16:
        raise ValueError("bank-01 joint table is not 16-byte-record aligned")
    joints = []
    matrix_indices = set()
    animation_indices = set()
    for index in range(joint_size // 16):
        offset = joint_offset + index * 16
        parent, matrix_index, animation_index, flags = struct.unpack_from(
            ">bBBB", data, offset
        )
        translation = struct.unpack_from(">3f", data, offset + 4)
        if parent < -1 or not all(math.isfinite(value) for value in translation):
            raise ValueError("bank-01 joint table contains an invalid record")
        matrix_indices.add(matrix_index)
        animation_indices.add(animation_index)
        joints.append(
            {
                "record_index": index,
                "parent_matrix_index": parent,
                "matrix_index": matrix_index,
                "animation_index": animation_index,
                "flags": flags,
                "local_translation_f32": list(translation),
            }
        )
    expected_joint_indices = set(range(len(joints)))
    if matrix_indices != expected_joint_indices or animation_indices != expected_joint_indices:
        raise ValueError("bank-01 joint table does not cover every runtime matrix slot")
    if any(
        joint["parent_matrix_index"] >= 0
        and joint["parent_matrix_index"] not in matrix_indices
        for joint in joints
    ):
        raise ValueError("bank-01 joint table references an absent parent matrix")
    used_matrix_indices = {
        run.matrix_index for run in geometry.material_runs if run.matrix_index is not None
    }
    if used_matrix_indices.difference(matrix_indices):
        raise ValueError("bank-01 display list references an absent joint matrix")

    texture_descriptor_offset, texture_descriptor_size = (
        header_words[6],
        header_words[7],
    )
    if texture_descriptor_size % 12:
        raise ValueError(
            "bank-01 texture descriptor table is not 12-byte-record aligned"
        )
    texture_descriptors = []
    for index in range(texture_descriptor_size // 12):
        offset = texture_descriptor_offset + index * 12
        initial_pointer_slot, flat_index, width, height = struct.unpack_from(
            ">IIHH", data, offset
        )
        if initial_pointer_slot != flat_index:
            raise ValueError(
                "bank-01 texture descriptor pointer slot does not contain its flat index"
            )
        if flat_index == 0:
            if initial_pointer_slot or width or height:
                raise ValueError("bank-01 null texture descriptor is malformed")
        elif flat_index >= 0x1E52:
            raise ValueError("bank-01 texture descriptor flat index is out of range")
        elif not width or not height:
            raise ValueError("bank-01 texture descriptor has an empty dimension")
        texture_descriptors.append(
            {
                "record_index": index,
                "runtime_pointer_slot_initial_value": initial_pointer_slot,
                "flat_index": flat_index,
                "width": width,
                "height": height,
            }
        )
    descriptor_flat_indices = {
        descriptor["flat_index"]
        for descriptor in texture_descriptors
        if descriptor["flat_index"]
    }
    referenced_flat_indices = {
        reference.flat_index
        for reference in geometry.texture_references
        if reference.flat_index is not None
    }
    if referenced_flat_indices.difference(descriptor_flat_indices):
        raise ValueError(
            "bank-01 display list references a flat texture absent from its descriptor table"
        )

    return geometry, {
        "header_size": 0x38,
        "header_words": [f"0x{word:08X}" for word in header_words],
        "vertex_offset": "0x38",
        "vertex_size": len(vertex_data),
        "vertex_count": len(vertex_data) // 16,
        "display_list_offset": f"0x{display_offset:X}",
        "display_list_size": len(display_data),
        "display_list_padding_size": display_padding_size,
        "display_list_count": len(display_list_pointers),
        "display_list_pointer_tables": pointer_tables,
        "joint_count": header_words[5] // 16,
        "joints": joints,
        "display_list_matrix_indices": sorted(used_matrix_indices),
        "texture_descriptor_count": len(texture_descriptors),
        "texture_descriptors": texture_descriptors,
        "sections": sections,
        "structural_status": (
            "runtime-proven-container-rigged-geometry-and-texture-descriptors"
        ),
        "rig_semantic_status": (
            "runtime-proven-hierarchy-and-rigid-matrix-assignments-"
            "unresolved-character-auxiliary-data-not-attributed-to-skinning"
        ),
        "runtime_evidence": {
            "pose_function": "func_150A81D0",
            "triangle_count_function": "func_1503D984",
            "runtime_triangle_count": len(geometry.faces),
            "joint_record_size": 16,
            "parent_matrix_index_offset": 0,
            "matrix_index_offset": 1,
            "animation_index_offset": 2,
            "local_translation_offset": 4,
            "matrix_stride": "0x40",
            "display_list_matrix_command": "DA380003 segment-3 offset / 0x40",
            "texture_descriptor_loader": "func_1503DC3C",
            "texture_resolver": "func_1510D0EC",
            "texture_descriptor_record_size": 12,
            "texture_pointer_slot_offset": 0,
            "texture_flat_index_offset": 4,
            "texture_width_offset": 8,
            "texture_height_offset": 10,
        },
    }


def parse_geometry_for_bank(data: bytes, bank_index: int) -> ModelGeometry:
    if bank_index == 0x01:
        return parse_character_model_geometry(data)[0]
    return parse_model_geometry(data)


def material_name(run: ModelMaterialRun) -> str:
    if not run.texture_enabled:
        name = "untextured"
    else:
        if run.pixel is None:
            raise ValueError("textured material run has no pixel binding")
        if run.pixel.external:
            name = "external_runtime_texture"
        elif run.pixel.flat_index is not None:
            name = (
                f"flat_{run.pixel.flat_index:04d}_mode_{run.pixel.mode}_"
                f"cmd_{run.pixel.image_command:08x}"
            )
        else:
            name = (
                f"segment_{run.pixel.segment:02d}_{run.pixel.offset:06x}_"
                f"cmd_{run.pixel.image_command:08x}"
            )
        if run.palette is not None:
            if run.palette.flat_index is not None:
                name += (
                    f"_palette_{run.palette.flat_index:04d}_mode_{run.palette.mode}"
                )
            else:
                name += (
                    f"_palette_segment_{run.palette.segment:02d}_"
                    f"{run.palette.offset:06x}"
                )
        coordinate_state = (
            texture_coordinate_state(run)
            if run.texture_coordinates_proven
            else None
        )
        if coordinate_state is not None:
            name += (
                f"_fmt_{coordinate_state['format']}_siz_{coordinate_state['size']}_"
                f"tile_{coordinate_state['width']}x{coordinate_state['height']}"
            )
    if run.combine_mode is not None:
        name += f"_combine_{run.combine_mode[0]:08x}_{run.combine_mode[1]:08x}"
    if run.other_mode is not None:
        name += f"_other_{run.other_mode[0]:08x}_{run.other_mode[1]:08x}"
    elif run.runtime_render_state_offset is not None:
        name += f"_runtime_other_{run.runtime_render_state_offset:04x}"
    return name


def texture_binding_record(binding: ModelTextureBinding | None) -> dict | None:
    if binding is None:
        return None
    record = {"image_command": f"0x{binding.image_command:08X}"}
    if binding.external:
        record.update(source="external-runtime-state")
    elif binding.flat_index is not None:
        record.update(
            source="flat-archive",
            flat_index=binding.flat_index,
            mode=binding.mode,
        )
    else:
        record.update(
            source="runtime-segment",
            segment=binding.segment,
            offset=f"0x{binding.offset:X}",
        )
    record["load_command"] = command_pair_record(binding.load_command)
    return record


def command_pair_record(pair: tuple[int, int] | None) -> list[str] | None:
    if pair is None:
        return None
    return [f"0x{word:08X}" for word in pair]


def decode_combine_mode(pair: tuple[int, int] | None) -> dict[str, Any] | None:
    """Decode the standard RDP two-cycle (A - B) * C + D selectors."""

    if pair is None:
        return None
    command, argument = pair
    if command >> 24 != 0xFC:
        raise ValueError("combine-mode command does not use opcode 0xFC")
    selectors = (
        (
            (command >> 20) & 0xF,
            (argument >> 28) & 0xF,
            (command >> 15) & 0x1F,
            (argument >> 15) & 0x7,
            (command >> 12) & 0x7,
            (argument >> 12) & 0x7,
            (command >> 9) & 0x7,
            (argument >> 9) & 0x7,
        ),
        (
            (command >> 5) & 0xF,
            (argument >> 24) & 0xF,
            command & 0x1F,
            (argument >> 6) & 0x7,
            (argument >> 21) & 0x7,
            (argument >> 3) & 0x7,
            (argument >> 18) & 0x7,
            argument & 0x7,
        ),
    )
    cycles = []
    requirements = set()
    for values in selectors:
        try:
            color = [
                COLOR_AB_MUX[values[0]],
                COLOR_AB_MUX[values[1]],
                COLOR_C_MUX[values[2]],
                COLOR_D_MUX[values[3]],
            ]
            alpha = [
                ALPHA_ABD_MUX[values[4]],
                ALPHA_ABD_MUX[values[5]],
                ALPHA_C_MUX[values[6]],
                ALPHA_ABD_MUX[values[7]],
            ]
        except KeyError as error:
            raise ValueError(f"combine mode contains unknown mux value {error.args[0]}") from error
        requirements.update(color)
        requirements.update(alpha)
        cycles.append({"color": color, "alpha": alpha})
    return {
        "formula": "(A - B) * C + D",
        "cycles": cycles,
        "inputs": sorted(requirements.difference({"COMBINED", "ZERO", "ONE"})),
    }


def texture_coordinate_state(run: ModelMaterialRun) -> dict | None:
    if not run.texture_enabled:
        return None
    if run.render_tile is None or run.texture_scale is None:
        raise ValueError("textured material run lacks tile or scale state")
    tile_command, tile_argument = run.render_tile
    mask_t = (tile_argument >> 14) & 0xF
    shift_t = (tile_argument >> 10) & 0xF
    mask_s = (tile_argument >> 4) & 0xF
    shift_s = tile_argument & 0xF
    if run.tile_bounds is not None:
        upper, lower = run.tile_bounds
        uls, ult = (upper >> 12) & 0xFFF, upper & 0xFFF
        lrs, lrt = (lower >> 12) & 0xFFF, lower & 0xFFF
        if lrs < uls or lrt < ult or (lrs - uls) % 4 or (lrt - ult) % 4:
            raise ValueError("material run has invalid render-tile bounds")
        width = (lrs - uls) // 4 + 1
        height = (lrt - ult) // 4 + 1
        dimension_evidence = "tile-bounds"
    elif mask_s and mask_t:
        uls = ult = 0
        width, height = 1 << mask_s, 1 << mask_t
        dimension_evidence = "tile-masks"
    else:
        raise ValueError("textured material run has no bounded texture dimensions")
    _, scale_argument = run.texture_scale
    format_id = (tile_command >> 21) & 7
    size_id = (tile_command >> 19) & 3
    format_evidence = "render-tile"
    if (
        run.pixel is not None
        and run.pixel.image_command == 0xFD100000
        and format_id == 0
        and size_id in (0, 1)
        and run.palette is not None
        and run.palette.flat_index == run.pixel.flat_index
        and run.palette.mode == 2 - size_id
    ):
        # Character display lists load their indexed bytes through an RGBA16
        # transfer image, then select an otherwise-invalid 4/8-bit RGBA render
        # tile and a same-index mode-two/mode-one TLUT. The palette load proves
        # the effective render format is CI4/CI8.
        format_id = 2
        format_evidence = "character-same-index-tlut-load"
    return {
        "width": width,
        "height": height,
        "uls": uls,
        "ult": ult,
        "scale_s": (scale_argument >> 16) / 65536.0,
        "scale_t": (scale_argument & 0xFFFF) / 65536.0,
        "shift_s": shift_s,
        "shift_t": shift_t,
        "mask_s": mask_s,
        "mask_t": mask_t,
        "format": format_id,
        "size": size_id,
        "format_evidence": format_evidence,
        "dimension_evidence": dimension_evidence,
    }


def shifted_texture_coordinate(value: float, shift: int) -> float:
    if shift <= 10:
        return value / (1 << shift)
    return value * (1 << (16 - shift))


def texture_coordinates(vertex: ModelVertex, run: ModelMaterialRun) -> tuple[float, float]:
    state = texture_coordinate_state(run)
    if state is None:
        raise ValueError("untextured material run has no texture coordinates")
    s = shifted_texture_coordinate(
        vertex.s / 32.0 * state["scale_s"], state["shift_s"]
    )
    t = shifted_texture_coordinate(
        vertex.t / 32.0 * state["scale_t"], state["shift_t"]
    )
    u = (s - state["uls"] / 4.0) / state["width"]
    v = 1.0 - (t - state["ult"] / 4.0) / state["height"]
    return u, v


def texture_address_mode(run: ModelMaterialRun) -> dict[str, Any] | None:
    """Translate the render tile's N64 S/T addressing into glTF sampler state."""

    if run.render_tile is None:
        return None
    _, argument = run.render_tile
    modes = {"s": (argument >> 8) & 3, "t": (argument >> 18) & 3}

    def gltf_wrap(mode: int) -> int:
        if mode & 2:
            return GLTF_CLAMP_TO_EDGE
        if mode & 1:
            return GLTF_MIRRORED_REPEAT
        return GLTF_REPEAT

    def name(mode: int) -> str:
        return ("mirror-" if mode & 1 else "") + (
            "clamp" if mode & 2 else "repeat"
        )

    return {
        "n64": {axis: name(mode) for axis, mode in modes.items()},
        "n64_bits": modes,
        "gltf": {
            "wrapS": gltf_wrap(modes["s"]),
            "wrapT": gltf_wrap(modes["t"]),
        },
    }


def texture_coordinate_count(geometry: ModelGeometry) -> int:
    count = 0
    for run in geometry.material_runs:
        if not run.texture_enabled or not run.texture_coordinates_proven:
            continue
        count += len(
            {
                vertex_index
                for face in geometry.faces[
                    run.first_face : run.first_face + run.face_count
                ]
                for vertex_index in face
            }
        )
    return count


def encode_obj(
    bundle_index: int,
    segment_index: int,
    geometry: ModelGeometry,
    bank_index: int = DEFAULT_BANK_INDEX,
) -> bytes:
    lines = [
        f"# Conker US model bundle {bundle_index:04d} model {segment_index:02d}",
        "# Native signed coordinates; material names encode runtime texture state.",
        f"mtllib {bundle_index:04d}-{segment_index:02d}.mtl",
        f"o bank{bank_index:02x}_{bundle_index:04d}_{segment_index:02d}",
    ]
    lines.extend(
        f"v {vertex.x} {vertex.y} {vertex.z}"
        for vertex in geometry.vertices
    )
    texture_coordinate_indices = {}
    next_texture_coordinate_index = 1
    for run_index, run in enumerate(geometry.material_runs):
        if not run.texture_enabled or not run.texture_coordinates_proven:
            continue
        seen_vertices = set()
        for face in geometry.faces[
            run.first_face : run.first_face + run.face_count
        ]:
            for vertex_index in face:
                if vertex_index in seen_vertices:
                    continue
                seen_vertices.add(vertex_index)
                u, v = texture_coordinates(geometry.vertices[vertex_index], run)
                lines.append(f"vt {u:.9g} {v:.9g}")
                texture_coordinate_indices[(run_index, vertex_index)] = (
                    next_texture_coordinate_index
                )
                next_texture_coordinate_index += 1
    for index, run in enumerate(geometry.material_runs):
        lines.append(f"g material_run_{index:04d}")
        lines.append(f"usemtl {material_name(run)}")
        for face in geometry.faces[
            run.first_face : run.first_face + run.face_count
        ]:
            if run.texture_enabled and run.texture_coordinates_proven:
                lines.append(
                    "f "
                    + " ".join(
                        f"{vertex_index + 1}/"
                        f"{texture_coordinate_indices[(index, vertex_index)]}"
                        for vertex_index in face
                    )
                )
            else:
                lines.append(
                    f"f {face[0] + 1} {face[1] + 1} {face[2] + 1}"
                )
    return ("\n".join(lines) + "\n").encode("ascii")


def encode_mtl(
    bundle_index: int,
    segment_index: int,
    geometry: ModelGeometry,
    texture_files: dict[str, str] | None = None,
    bank_index: int = DEFAULT_BANK_INDEX,
) -> bytes:
    lines = [
        f"# Conker US model bundle {bundle_index:04d} model {segment_index:02d}",
        "# Stable runtime bindings only; semantic material names remain unresolved.",
    ]
    seen = set()
    for run in geometry.material_runs:
        name = material_name(run)
        if name in seen:
            continue
        seen.add(name)
        lines.extend(("", f"newmtl {name}", "Kd 1.0 1.0 1.0"))
        if texture_files is not None and name in texture_files:
            lines.append(f"map_Kd {texture_files[name]}")
    return ("\n".join(lines) + "\n").encode("ascii")


def encode_gltf(
    bundle_index: int,
    segment_index: int,
    geometry: ModelGeometry,
    texture_files: dict[str, str] | None = None,
    bank_index: int = DEFAULT_BANK_INDEX,
    character_joints: tuple[dict[str, Any], ...] | None = None,
    character_rotations: tuple[tuple[float, float, float, float], ...] | None = None,
    character_pose_source: str | None = None,
) -> tuple[bytes, bytes]:
    binary = bytearray()
    buffer_views = []
    accessors = []

    def append_accessor(
        data: bytes,
        component_type: int,
        value_type: str,
        count: int,
        target: int | None,
        minimum: list[float | int] | None = None,
        maximum: list[float | int] | None = None,
        normalized: bool = False,
    ) -> int:
        while len(binary) % 4:
            binary.append(0)
        offset = len(binary)
        binary.extend(data)
        buffer_view = len(buffer_views)
        buffer_view_record = {
            "buffer": 0,
            "byteOffset": offset,
            "byteLength": len(data),
        }
        if target is not None:
            buffer_view_record["target"] = target
        buffer_views.append(buffer_view_record)
        accessor = {
            "bufferView": buffer_view,
            "componentType": component_type,
            "count": count,
            "type": value_type,
        }
        if minimum is not None:
            accessor["min"] = minimum
        if maximum is not None:
            accessor["max"] = maximum
        if normalized:
            accessor["normalized"] = True
        accessors.append(accessor)
        return len(accessors) - 1

    images = []
    image_indices: dict[str, int] = {}
    samplers = []
    sampler_indices: dict[tuple[int, int], int] = {}
    textures = []
    texture_indices: dict[tuple[str, int, int], int] = {}
    materials = []
    primitives = []
    for run_index, run in enumerate(geometry.material_runs):
        source_vertex_indices = []
        local_vertex_indices = {}
        local_faces = []
        for face in geometry.faces[
            run.first_face : run.first_face + run.face_count
        ]:
            local_face = []
            for source_index in face:
                if source_index not in local_vertex_indices:
                    local_vertex_indices[source_index] = len(source_vertex_indices)
                    source_vertex_indices.append(source_index)
                local_face.append(local_vertex_indices[source_index])
            local_faces.append(tuple(local_face))
        vertices = [geometry.vertices[index] for index in source_vertex_indices]
        position_accessor = append_accessor(
            b"".join(
                struct.pack("<3f", vertex.x, vertex.y, vertex.z)
                for vertex in vertices
            ),
            5126,
            "VEC3",
            len(vertices),
            34962,
            [
                float(min(getattr(vertex, axis) for vertex in vertices))
                for axis in ("x", "y", "z")
            ],
            [
                float(max(getattr(vertex, axis) for vertex in vertices))
                for axis in ("x", "y", "z")
            ],
        )
        color_accessor = append_accessor(
            b"".join(bytes(vertex.color) for vertex in vertices),
            5121,
            "VEC4",
            len(vertices),
            34962,
            normalized=True,
        )
        attributes = {"POSITION": position_accessor, "COLOR_0": color_accessor}
        if character_joints:
            joint_index = run.matrix_index if run.matrix_index is not None else 0
            attributes["JOINTS_0"] = append_accessor(
                b"".join(
                    struct.pack("<4H", joint_index, 0, 0, 0) for _ in vertices
                ),
                5123,
                "VEC4",
                len(vertices),
                34962,
            )
            attributes["WEIGHTS_0"] = append_accessor(
                b"".join(struct.pack("<4f", 1.0, 0.0, 0.0, 0.0) for _ in vertices),
                5126,
                "VEC4",
                len(vertices),
                34962,
            )
        if run.texture_enabled and run.texture_coordinates_proven:
            texcoord_accessor = append_accessor(
                b"".join(
                    struct.pack("<2f", *texture_coordinates(vertex, run))
                    for vertex in vertices
                ),
                5126,
                "VEC2",
                len(vertices),
                34962,
            )
            attributes["TEXCOORD_0"] = texcoord_accessor
        local_indices = [index for face in local_faces for index in face]
        index_accessor = append_accessor(
            b"".join(struct.pack("<H", index) for index in local_indices),
            5123,
            "SCALAR",
            len(local_indices),
            34963,
            [min(local_indices)],
            [max(local_indices)],
        )
        name = material_name(run)
        material = {
            "name": name,
            "doubleSided": True,
            "pbrMetallicRoughness": {
                "baseColorFactor": [1.0, 1.0, 1.0, 1.0],
                "metallicFactor": 0.0,
                "roughnessFactor": 1.0,
            },
            "extras": {
                "materialRun": run_index,
                "firstFace": run.first_face,
                "faceCount": run.face_count,
                "combineMode": command_pair_record(run.combine_mode),
                "combineFormula": decode_combine_mode(run.combine_mode),
                "otherMode": command_pair_record(run.other_mode),
                "runtimeRenderStateOffset": (
                    f"0x{run.runtime_render_state_offset:X}"
                    if run.runtime_render_state_offset is not None
                    else None
                ),
                "textureAddressMode": texture_address_mode(run),
            },
        }
        texture_file = texture_files.get(name) if texture_files is not None else None
        if texture_file is not None:
            address_mode = texture_address_mode(run)
            if address_mode is None:
                raise ValueError("linked texture material lacks render-tile state")
            wrap_s = address_mode["gltf"]["wrapS"]
            wrap_t = address_mode["gltf"]["wrapT"]
            texture_key = (texture_file, wrap_s, wrap_t)
            texture_index = texture_indices.get(texture_key)
            if texture_index is None:
                image_index = image_indices.get(texture_file)
                if image_index is None:
                    image_index = len(images)
                    images.append({"uri": texture_file})
                    image_indices[texture_file] = image_index
                sampler_key = (wrap_s, wrap_t)
                sampler_index = sampler_indices.get(sampler_key)
                if sampler_index is None:
                    sampler_index = len(samplers)
                    samplers.append(
                        {
                            "magFilter": 9729,
                            "minFilter": 9987,
                            "wrapS": wrap_s,
                            "wrapT": wrap_t,
                        }
                    )
                    sampler_indices[sampler_key] = sampler_index
                texture_index = len(textures)
                textures.append({"sampler": sampler_index, "source": image_index})
                texture_indices[texture_key] = texture_index
            material["pbrMetallicRoughness"]["baseColorTexture"] = {
                "index": texture_index
            }
            material["alphaMode"] = "MASK"
            material["alphaCutoff"] = 0.5
        material_index = len(materials)
        materials.append(material)
        primitive = {
                "attributes": attributes,
                "indices": index_accessor,
                "material": material_index,
                "mode": 4,
                "extras": {"matrixIndex": run.matrix_index},
            }
        primitives.append(primitive)
    stem = f"{bundle_index:04d}-{segment_index:02d}"
    if not character_joints:
        nodes = [{"mesh": 0, "name": f"bank{bank_index:02x}_{stem}"}]
        meshes = [
            {"name": f"bank{bank_index:02x}_{stem}", "primitives": primitives}
        ]
        scene_nodes = [0]
        skins = None
    else:
        meshes = [
            {"name": f"bank{bank_index:02x}_{stem}", "primitives": primitives}
        ]
        ordered_joints = sorted(character_joints, key=lambda joint: joint["matrix_index"])
        nodes = []
        node_by_matrix = {}
        for joint in ordered_joints:
            matrix_index = joint["matrix_index"]
            node_by_matrix[matrix_index] = len(nodes)
            node: dict[str, Any] = {
                "name": f"joint_{matrix_index:02d}",
                "translation": joint["local_translation_f32"],
                "extras": {
                    "recordIndex": joint["record_index"],
                    "matrixIndex": matrix_index,
                    "animationIndex": joint["animation_index"],
                    "parentMatrixIndex": joint["parent_matrix_index"],
                    "runtimeFlags": joint["flags"],
                },
            }
            if character_rotations is not None:
                node["rotation"] = list(
                    character_rotations[joint["animation_index"]]
                )
            nodes.append(node)
        scene_nodes = []
        for joint in ordered_joints:
            node_index = node_by_matrix[joint["matrix_index"]]
            parent = joint["parent_matrix_index"]
            if parent < 0:
                scene_nodes.append(node_index)
            else:
                nodes[node_by_matrix[parent]].setdefault("children", []).append(node_index)
        mesh_node_index = len(nodes)
        scene_nodes.append(mesh_node_index)
        nodes.append(
            {
                "name": f"bank{bank_index:02x}_{stem}_skinned_mesh",
                "mesh": 0,
                "skin": 0,
            }
        )
        skins = [
            {
                "name": f"bank{bank_index:02x}_{stem}_rig",
                "joints": [
                    node_by_matrix[joint["matrix_index"]] for joint in ordered_joints
                ],
                "skeleton": scene_nodes[0],
                "extras": {
                    "inverseBindMatrices": "identity-by-omission-native-bone-local-vertices"
                },
            }
        ]
    document = {
        "asset": {"version": "2.0", "generator": "conker model-assets"},
        "scene": 0,
        "scenes": [{"nodes": scene_nodes}],
        "nodes": nodes,
        "meshes": meshes,
        "materials": materials,
        "buffers": [{"uri": f"{stem}.bin", "byteLength": len(binary)}],
        "bufferViews": buffer_views,
        "accessors": accessors,
    }
    if skins is not None:
        document["skins"] = skins
        document["extras"] = {
            "characterJointHierarchy": "runtime-proven-func_150A81D0",
            "skinningStatus": "rigid-display-matrix-assignment-proven",
            "characterAuxiliaryData": (
                "preserved-unresolved-not-attributed-to-skinning"
            ),
            "previewPose": character_pose_source
            or "translation-hierarchy-animation-rotations-unresolved",
            "coordinateConversion": "none-native-axes",
        }
    if images:
        document["samplers"] = samplers
        document["images"] = images
        document["textures"] = textures
    return (
        (json.dumps(document, indent=2) + "\n").encode("utf-8"),
        bytes(binary),
    )


def encode_placement_scene_gltf(
    scene_index: int,
    placements: list[dict[str, Any]],
    model_gltfs: dict[int, tuple[dict[str, Any], bytes]],
) -> tuple[bytes, bytes]:
    """Combine direct bank-03 model glTFs into one bank-12 placement scene."""

    binary = bytearray()
    buffer_views: list[dict[str, Any]] = []
    accessors: list[dict[str, Any]] = []
    images: list[dict[str, Any]] = []
    samplers: list[dict[str, Any]] = []
    textures: list[dict[str, Any]] = []
    materials: list[dict[str, Any]] = []
    meshes: list[dict[str, Any]] = []
    mesh_indices: dict[int, int] = {}

    for model_index in dict.fromkeys(record["model_index"] for record in placements):
        if model_index is None or model_index not in model_gltfs:
            raise ValueError(
                f"scene {scene_index} references absent bank-03 model {model_index}"
            )
        source, source_binary = model_gltfs[model_index]
        while len(binary) % 4:
            binary.append(0)
        binary_offset = len(binary)
        binary.extend(source_binary)

        buffer_view_base = len(buffer_views)
        for source_view in source["bufferViews"]:
            view = dict(source_view)
            view["buffer"] = 0
            view["byteOffset"] = view.get("byteOffset", 0) + binary_offset
            buffer_views.append(view)

        accessor_base = len(accessors)
        for source_accessor in source["accessors"]:
            accessor = dict(source_accessor)
            accessor["bufferView"] += buffer_view_base
            accessors.append(accessor)

        image_base = len(images)
        images.extend(dict(source_image) for source_image in source.get("images", []))
        sampler_base = len(samplers)
        samplers.extend(
            dict(source_sampler) for source_sampler in source.get("samplers", [])
        )
        texture_base = len(textures)
        for source_texture in source.get("textures", []):
            texture = dict(source_texture)
            texture["source"] += image_base
            texture["sampler"] += sampler_base
            textures.append(texture)

        material_base = len(materials)
        for source_material in source["materials"]:
            material = json.loads(json.dumps(source_material))
            base_color_texture = material["pbrMetallicRoughness"].get(
                "baseColorTexture"
            )
            if base_color_texture is not None:
                base_color_texture["index"] += texture_base
            materials.append(material)

        source_mesh = json.loads(json.dumps(source["meshes"][0]))
        for primitive in source_mesh["primitives"]:
            primitive["indices"] += accessor_base
            primitive["material"] += material_base
            primitive["attributes"] = {
                name: accessor_index + accessor_base
                for name, accessor_index in primitive["attributes"].items()
            }
        mesh_indices[model_index] = len(meshes)
        meshes.append(source_mesh)

    nodes = [
        {
            "mesh": mesh_indices[record["model_index"]],
            "name": (
                f"scene_{scene_index:02d}_object_{record['index']:03d}_"
                f"model_{record['model_index']:04d}"
            ),
            "matrix": placement_transform_matrix(record),
            "extras": {
                "placementRecord": record["index"],
                "modelIndex": record["model_index"],
                "recordSha1": record["sha1"],
            },
        }
        for record in placements
    ]
    stem = f"scene-{scene_index:02d}"
    document: dict[str, Any] = {
        "asset": {
            "version": "2.0",
            "generator": "conker model-assets bank-12 scene assembler",
        },
        "scene": 0,
        "scenes": [
            {
                "name": f"bank12_scene_{scene_index:02d}",
                "nodes": list(range(len(nodes))),
            }
        ],
        "nodes": nodes,
        "meshes": meshes,
        "materials": materials,
        "buffers": [{"uri": f"{stem}.bin", "byteLength": len(binary)}],
        "bufferViews": buffer_views,
        "accessors": accessors,
        "extras": {
            "placementBank": 12,
            "placementSceneIndex": scene_index,
            "transformRuntime": "func_1511490C",
            "rotationOrder": "YZX",
            "coordinateConversion": "none-native-axes",
        },
    }
    if images:
        document["samplers"] = samplers
        document["images"] = images
        document["textures"] = textures
    return (json.dumps(document, indent=2) + "\n").encode("utf-8"), bytes(binary)


def _validated_preview_source(family_root: Path, relative_file: str) -> Path:
    relative = Path(relative_file)
    if relative.is_absolute() or ".." in relative.parts:
        raise ValueError("texture manifest contains an unsafe preview path")
    source = (family_root / relative).resolve()
    if not source.is_relative_to(family_root.resolve()) or not source.is_file():
        raise ValueError(f"preview texture does not exist: {source}")
    return source


def load_preview_texture_catalog(
    texture_root: Path, normalized_sha1: str
) -> dict[tuple[int, int, int], tuple[PreviewTexture, ...]]:
    catalog: dict[tuple[int, int, int], list[PreviewTexture]] = {}
    fixed_formats = {
        "us": (2, 0),
        "us-1056-proven": (2, 0),
        "us-ci8-proven": (2, 1),
        "us-rgba16-proven": (0, 2),
    }
    native_formats = {
        "rgba32": (0, 3),
        "ia8": (3, 1),
        "ia16": (3, 2),
        "i4": (4, 0),
        "i8": (4, 1),
    }
    for family in PREVIEW_TEXTURE_FAMILIES:
        family_root = texture_root / family
        manifest_path = family_root / "manifest.json"
        if not manifest_path.is_file():
            raise ValueError(
                f"missing {display_path(manifest_path)}; extract every proven "
                "texture family before preparing model previews"
            )
        manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
        if manifest.get("profile") != "us":
            raise ValueError(f"{family} texture manifest is not for US")
        if manifest.get("normalized_sha1") != normalized_sha1:
            raise ValueError(f"{family} texture manifest is from a different ROM")
        records = manifest.get("tiles" if family == "us-tiled-views" else "textures")
        if not isinstance(records, list):
            raise ValueError(f"{family} texture manifest lacks texture records")
        for record in records:
            if family in fixed_formats:
                format_id, size_id = fixed_formats[family]
            elif family == "us-native-proven":
                try:
                    format_id, size_id = native_formats[record["format"]]
                except KeyError as error:
                    raise ValueError(
                        f"unsupported native preview format: {record.get('format')}"
                    ) from error
            else:
                format_id, size_id = (
                    (2, 0) if record["format"] == "ci4" else (2, 1)
                )
            width = record.get("storage_width", record.get("width", manifest.get("width")))
            height = record.get(
                "storage_height", record.get("height", manifest.get("height"))
            )
            if not isinstance(width, int) or not isinstance(height, int):
                raise ValueError(f"{family} texture record lacks dimensions")
            source = _validated_preview_source(family_root, record["file"])
            texture = PreviewTexture(
                family=family,
                source=source,
                flat_index=record["flat_index"],
                format=format_id,
                size=size_id,
                width=width,
                height=height,
                sha1=hashlib.sha1(source.read_bytes()).hexdigest(),
            )
            catalog.setdefault(
                (texture.flat_index, texture.format, texture.size), []
            ).append(texture)
    return {
        key: tuple(
            sorted(
                textures,
                key=lambda texture: (
                    PREVIEW_TEXTURE_FAMILIES.index(texture.family),
                    texture.width,
                    texture.height,
                    str(texture.source),
                ),
            )
        )
        for key, textures in catalog.items()
    }


def choose_preview_texture(
    run: ModelMaterialRun,
    catalog: dict[tuple[int, int, int], tuple[PreviewTexture, ...]],
) -> tuple[PreviewTexture | None, str]:
    if not run.texture_enabled:
        return None, "untextured"
    if run.pixel is None:
        raise ValueError("textured material run has no pixel binding")
    if run.pixel.external:
        return None, "external-runtime-texture"
    if not run.texture_coordinates_proven:
        return None, "unresolved-texture-coordinate-state"
    if run.pixel.flat_index is None:
        return None, "runtime-segment"
    state = texture_coordinate_state(run)
    if state is None:
        raise ValueError("textured material run has no coordinate state")
    if state["format_evidence"] == "character-same-index-tlut-load":
        return None, "character-indexed-material-runtime-unresolved"
    if state["format"] == 2:
        if (
            run.palette is None
            or run.palette.flat_index != run.pixel.flat_index
        ):
            return None, "unresolved-ci-palette"
        if state["size"] == 1:
            return None, "mode-one-ci8-palette-runtime-unresolved"
    candidates = catalog.get(
        (run.pixel.flat_index, state["format"], state["size"]), ()
    )
    if not candidates:
        return None, "no-proven-texture"
    material_candidates = tuple(
        texture for texture in candidates if texture.family != "us-native-proven"
    )
    if not material_candidates:
        return None, "native-material-combiner-unresolved"
    candidates = material_candidates
    exact = tuple(
        texture
        for texture in candidates
        if texture.width == state["width"] and texture.height == state["height"]
    )
    pool = exact or candidates
    return min(
        pool,
        key=lambda texture: (
            PREVIEW_TEXTURE_FAMILIES.index(texture.family),
            abs(texture.width - state["width"])
            + abs(texture.height - state["height"]),
            str(texture.source),
        ),
    ), "proven-texture"


def preview_texture_filename(texture: PreviewTexture) -> str:
    return (
        f"{texture.family}-{texture.flat_index:04d}-"
        f"{texture.width}x{texture.height}-{texture.sha1[:12]}.png"
    )


def verify_preview_output(output: Path, manifest: dict[str, Any]) -> None:
    instructions_path = output / manifest["instructions_file"]
    if not instructions_path.is_file():
        raise ValueError("preview instructions are missing")
    texture_files = {
        texture["file"]: texture["png_sha1"] for texture in manifest["textures"]
    }
    for relative_file, expected_sha1 in texture_files.items():
        path = output / relative_file
        if (
            not path.is_file()
            or hashlib.sha1(path.read_bytes()).hexdigest() != expected_sha1
        ):
            raise ValueError(f"preview texture failed verification: {relative_file}")
    for model in manifest["models"]:
        obj_path = output / model["object_file"]
        mtl_path = output / model["material_file"]
        gltf_path = output / model["gltf_file"]
        binary_path = output / model["gltf_binary_file"]
        if not all(
            path.is_file() for path in (obj_path, mtl_path, gltf_path, binary_path)
        ):
            raise ValueError("preview model is missing an exported file")
        obj_lines = obj_path.read_text(encoding="ascii").splitlines()
        vertex_count = sum(line.startswith("v ") for line in obj_lines)
        texture_coordinate_total = sum(line.startswith("vt ") for line in obj_lines)
        face_lines = [line for line in obj_lines if line.startswith("f ")]
        if vertex_count != model["vertex_count"]:
            raise ValueError(f"preview OBJ vertex count mismatch: {obj_path.name}")
        if texture_coordinate_total != model["texture_coordinate_count"]:
            raise ValueError(f"preview OBJ UV count mismatch: {obj_path.name}")
        if len(face_lines) != model["face_count"]:
            raise ValueError(f"preview OBJ face count mismatch: {obj_path.name}")
        for face_line in face_lines:
            fields = face_line.split()[1:]
            if len(fields) != 3:
                raise ValueError(f"preview OBJ has a non-triangle face: {obj_path.name}")
            for field in fields:
                indices = field.split("/")
                if not 1 <= int(indices[0]) <= vertex_count:
                    raise ValueError(f"preview OBJ has an invalid vertex: {obj_path.name}")
                if (
                    len(indices) > 1
                    and not 1 <= int(indices[1]) <= texture_coordinate_total
                ):
                    raise ValueError(f"preview OBJ has an invalid UV: {obj_path.name}")
        expected_mtl = f"mtllib {mtl_path.name}"
        if expected_mtl not in obj_lines:
            raise ValueError(f"preview OBJ does not reference its MTL: {obj_path.name}")
        mtl_lines = mtl_path.read_text(encoding="ascii").splitlines()
        material_names = {
            line.removeprefix("newmtl ")
            for line in mtl_lines
            if line.startswith("newmtl ")
        }
        used_materials = {
            line.removeprefix("usemtl ")
            for line in obj_lines
            if line.startswith("usemtl ")
        }
        if not used_materials.issubset(material_names):
            raise ValueError(f"preview OBJ uses an undefined material: {obj_path.name}")
        for line in mtl_lines:
            if not line.startswith("map_Kd "):
                continue
            mapped = (mtl_path.parent / line.removeprefix("map_Kd ")).resolve()
            if not mapped.is_relative_to(output.resolve()) or not mapped.is_file():
                raise ValueError(f"preview MTL has a missing texture: {mtl_path.name}")
        gltf = json.loads(gltf_path.read_text(encoding="utf-8"))
        if gltf.get("asset", {}).get("version") != "2.0":
            raise ValueError(f"preview glTF has an invalid version: {gltf_path.name}")
        if gltf["buffers"][0]["byteLength"] != binary_path.stat().st_size:
            raise ValueError(f"preview glTF buffer size mismatch: {gltf_path.name}")
        primitives = [
            primitive
            for mesh in gltf["meshes"]
            for primitive in mesh["primitives"]
        ]
        if len(primitives) != len(model["material_runs"]):
            raise ValueError(f"preview glTF material-run mismatch: {gltf_path.name}")
        if any("COLOR_0" not in primitive["attributes"] for primitive in primitives):
            raise ValueError(f"preview glTF omits vertex colors: {gltf_path.name}")
        if model.get("joint_count", 0):
            if len(gltf.get("skins", [])) != 1:
                raise ValueError(f"preview glTF omits its character skin: {gltf_path.name}")
            skin = gltf["skins"][0]
            if len(skin["joints"]) != model["joint_count"]:
                raise ValueError(f"preview glTF joint count mismatch: {gltf_path.name}")
            if any(
                "JOINTS_0" not in primitive["attributes"]
                or "WEIGHTS_0" not in primitive["attributes"]
                for primitive in primitives
            ):
                raise ValueError(f"preview glTF omits rigid skin weights: {gltf_path.name}")
            if any(not 0 <= node < len(gltf["nodes"]) for node in skin["joints"]):
                raise ValueError(f"preview glTF has an invalid joint node: {gltf_path.name}")
        for accessor in gltf["accessors"]:
            if not 0 <= accessor["bufferView"] < len(gltf["bufferViews"]):
                raise ValueError(f"preview glTF has an invalid accessor: {gltf_path.name}")
        for view in gltf["bufferViews"]:
            if view.get("byteOffset", 0) + view["byteLength"] > binary_path.stat().st_size:
                raise ValueError(f"preview glTF view exceeds its buffer: {gltf_path.name}")
        for image in gltf.get("images", []):
            mapped = (gltf_path.parent / image["uri"]).resolve()
            if not mapped.is_relative_to(output.resolve()) or not mapped.is_file():
                raise ValueError(f"preview glTF has a missing texture: {gltf_path.name}")
    for scene in manifest.get("assembled_scenes", []):
        gltf_path = output / scene["gltf_file"]
        binary_path = output / scene["gltf_binary_file"]
        if not gltf_path.is_file() or not binary_path.is_file():
            raise ValueError("assembled scene is missing an exported file")
        gltf = json.loads(gltf_path.read_text(encoding="utf-8"))
        if gltf.get("asset", {}).get("version") != "2.0":
            raise ValueError(f"assembled glTF has an invalid version: {gltf_path.name}")
        if gltf["buffers"][0]["byteLength"] != binary_path.stat().st_size:
            raise ValueError(f"assembled glTF buffer size mismatch: {gltf_path.name}")
        if len(gltf["nodes"]) != scene["placement_record_count"]:
            raise ValueError(f"assembled glTF placement mismatch: {gltf_path.name}")
        if len(gltf["meshes"]) != scene["unique_model_count"]:
            raise ValueError(f"assembled glTF model mismatch: {gltf_path.name}")
        if any(len(node.get("matrix", [])) != 16 for node in gltf["nodes"]):
            raise ValueError(f"assembled glTF transform mismatch: {gltf_path.name}")
        if any(not 0 <= node["mesh"] < len(gltf["meshes"]) for node in gltf["nodes"]):
            raise ValueError(f"assembled glTF mesh reference mismatch: {gltf_path.name}")
        for image in gltf.get("images", []):
            mapped = (gltf_path.parent / image["uri"]).resolve()
            if not mapped.is_relative_to(output.resolve()) or not mapped.is_file():
                raise ValueError(f"assembled glTF has a missing texture: {gltf_path.name}")


def resolve_rom(profile: str, rom_argument: Path | None) -> tuple[Path, dict[str, Any]]:
    layout = load_layout(profile)
    default_rom = layout.get("default_rom")
    rom_path = rom_argument or (ROOT / default_rom if default_rom else None)
    if rom_path is None:
        raise ValueError(f"--rom is required for the {profile} profile")
    if not rom_path.is_absolute():
        rom_path = ROOT / rom_path
    if not rom_path.is_file():
        raise ValueError(f"ROM does not exist: {display_path(rom_path)}")
    return rom_path, layout


def parse_runtime_render_state_tables(
    game_data: bytes, data_vram: int
) -> tuple[dict[str, Any], ...]:
    """Decode the fixed 24-entry OtherMode display lists selected as segment 8."""

    tables = []
    for base_address in RUNTIME_RENDER_STATE_TABLE_BASES:
        entries = []
        for entry_index in range(24):
            display_list_offset = entry_index * 0x10
            offset = base_address - data_vram + display_list_offset
            if offset < 0 or offset + 0x10 > len(game_data):
                raise ValueError(
                    f"runtime render-state table 0x{base_address:X} is outside game data"
                )
            command, argument, end_command, end_argument = struct.unpack_from(
                ">4I", game_data, offset
            )
            if command >> 24 != 0xEF or end_command != 0xDF000000 or end_argument:
                raise ValueError(
                    f"runtime render-state entry 0x{base_address:X}+"
                    f"0x{display_list_offset:X} is not OtherMode plus EndDL"
                )
            entries.append(
                {
                    "offset": f"0x{display_list_offset:X}",
                    "other_mode": [f"0x{command:08X}", f"0x{argument:08X}"],
                }
            )
        tables.append(
            {
                "base_address": f"0x{base_address:X}",
                "entry_count": len(entries),
                "entries": entries,
            }
        )
    return tuple(tables)


def load_model_bundles(
    profile: str, rom_argument: Path | None, bank_index: int = DEFAULT_BANK_INDEX
) -> tuple[Path, str, str, list[ModelBundle], tuple[dict[str, Any], ...]]:
    if profile != "us":
        raise ValueError("model extraction is currently proven only for US")
    if bank_index not in BANK_INDICES:
        raise ValueError(f"unsupported model bank {bank_index:02X}")
    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(f"US normalized ROM SHA-1 mismatch: got {digest}")

    banks = parse_asset_banks(normalized, layout["asset_table"])
    try:
        bank = next(candidate for candidate in banks if candidate.index == bank_index)
    except StopIteration as error:
        raise ValueError(f"US indexed asset bank {bank_index:02X} is absent") from error
    if bank.flags:
        raise ValueError(
            f"US indexed asset bank {bank_index:02X} is not an ordinary indexed bank"
        )

    bundles = []
    for entry in parse_asset_entries(normalized, bank):
        raw = normalized[entry.start : entry.end]
        data = decode_rzip_chunk(raw).data if entry.compressed else raw
        if bank_index == 0x04:
            segments = parse_model_bundle(data)
        else:
            # Banks 01 and 03 consist entirely of character/direct model
            # payloads. Bank 09 is a mixed runtime display-list bank, but entries
            # 426--431 use the same self-contained 40-byte geometry header.
            try:
                parse_geometry_for_bank(data, bank_index)
            except ValueError as error:
                if bank_index == 0x09:
                    continue
                raise ValueError(
                    f"bank-{bank_index:02X} entry {entry.index}: {error}"
                ) from error
            segments = (
                ModelSegment(
                    index=0,
                    offset=0,
                    size=len(data),
                    final_flag=True,
                    data=data,
                ),
            )
        bundles.append(
            ModelBundle(
                index=entry.index,
                type_flags=entry.type_flags,
                compressed=entry.compressed,
                data=data,
                segments=segments,
            )
        )
    if not bundles:
        raise ValueError(f"US indexed asset bank {bank_index:02X} contains no models")
    if layout.get("game_format") != "rzip":
        raise ValueError("US runtime render-state evidence requires the RZIP game archive")
    game = parse_game_archive(normalized[layout["game_start"] : layout["game_end"]])
    render_state_tables = parse_runtime_render_state_tables(
        game.data, int(layout["game_data_vram"])
    )
    return rom_path, source_order, digest, bundles, render_state_tables


def load_object_placement_manifest(
    profile: str,
    rom_argument: Path | None,
    *,
    include_files: bool,
) -> tuple[dict[str, Any], dict[tuple[int, int], bytes]]:
    """Decode the two 0x44-byte runtime record sources used by func_150039E0."""

    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(f"US normalized ROM SHA-1 mismatch: got {digest}")
    banks = {bank.index: bank for bank in parse_asset_banks(normalized, layout["asset_table"])}
    if any(index not in banks or banks[index].flags for index in (*PLACEMENT_BANKS, 0x03)):
        raise ValueError("US object placement or model bank is absent")

    available_model_indices = set()
    for entry in parse_asset_entries(normalized, banks[0x03]):
        raw = normalized[entry.start : entry.end]
        data = decode_rzip_chunk(raw).data if entry.compressed else raw
        parse_model_geometry(data)
        available_model_indices.add(entry.index)

    payloads: dict[tuple[int, int], bytes] = {}
    scene_records = []
    referenced_model_indices = set()
    for bank_index in PLACEMENT_BANKS:
        for entry in parse_asset_entries(normalized, banks[bank_index]):
            raw = normalized[entry.start : entry.end]
            decoded = decode_rzip_chunk(raw).data if entry.compressed else raw
            if bank_index == 0x0B:
                payload = decoded
                path = [0x0B, entry.index]
                allow_alignment_padding = True
            else:
                payload = nested_asset_payload(decoded, 2)
                path = [0x0C, entry.index, 2]
                allow_alignment_padding = False
            records, padding = parse_placement_records(
                payload, allow_alignment_padding=allow_alignment_padding
            )
            parsed_records = [
                placement_record_manifest(record, index)
                for index, record in enumerate(records)
            ]
            dispatch_kinds = {record["dispatch_kind"] for record in parsed_records}
            if bank_index == 0x0B and (not dispatch_kinds or 0 in dispatch_kinds):
                raise ValueError("bank-11 placement records lack their nonzero dispatch kind")
            if bank_index == 0x0C and dispatch_kinds.difference({0}):
                raise ValueError("bank-12 child-2 placement records have an unexpected dispatch kind")
            model_indices = {
                record["model_index"]
                for record in parsed_records
                if record["model_index"] is not None
            }
            missing = model_indices.difference(available_model_indices)
            if missing:
                raise ValueError(
                    "bank-12 placement records reference absent bank-03 models: "
                    + ", ".join(str(index) for index in sorted(missing))
                )
            referenced_model_indices.update(model_indices)
            payloads[(bank_index, entry.index)] = payload
            scene_records.append(
                {
                    "bank_index": bank_index,
                    "scene_index": entry.index,
                    "runtime_path": path,
                    "decoded_container_size": len(decoded),
                    "payload_size": len(payload),
                    "record_count": len(records),
                    "alignment_padding_size": len(padding),
                    "payload_sha1": hashlib.sha1(payload).hexdigest(),
                    "file": (
                        f"placements/bank-{bank_index:02x}/scene-{entry.index:02d}.bin"
                        if include_files
                        else None
                    ),
                    "records": parsed_records,
                }
            )
    return (
        {
            "schema_version": 1,
            "family": "object-placement-records",
            "profile": profile,
            "source_rom": manifest_source(rom_path),
            "source_byte_order": source_order,
            "normalized_sha1": digest,
            "record_size": PLACEMENT_RECORD_SIZE,
            "scene_table_count": len(scene_records),
            "record_count": sum(scene["record_count"] for scene in scene_records),
            "bank_11_record_count": sum(
                scene["record_count"]
                for scene in scene_records
                if scene["bank_index"] == 0x0B
            ),
            "bank_12_record_count": sum(
                scene["record_count"]
                for scene in scene_records
                if scene["bank_index"] == 0x0C
            ),
            "referenced_bank_03_model_count": len(referenced_model_indices),
            "referenced_bank_03_model_indices": sorted(referenced_model_indices),
            "unreferenced_bank_03_model_indices": sorted(
                available_model_indices.difference(referenced_model_indices)
            ),
            "structural_status": "proven",
            "transform_semantics_status": "runtime-proven-static-transform",
            "runtime_evidence": {
                "record_loader_function": "func_150039E0",
                "record_loader_assembly": "asm/nonmatchings/game_30E90/func_150039E0.s",
                "record_size": "0x44",
                "bank_11_path": [0x0B, "scene-index"],
                "bank_12_path": [0x0C, "scene-index", 2],
                "position_offset": "0x00",
                "rotation_degrees_offset": "0x06",
                "bank_12_model_index_offset": "0x10",
                "scale_offset": "0x20",
                "transform_function": "func_1511490C",
                "orientation_function": "func_151148A8",
                "euler_matrix_function": "func_150A8050",
                "degrees_to_radians_constant": "D_8009F6C0 = pi / 180",
                "matrix_multiply_function": "func_150A7A48",
                "scale_matrix_function": "func_150A7CB0",
                "rotation_order": "YZX",
                "matrix_convention": "row-vector-runtime-transposed-for-gltf",
                "coordinate_conversion": "none-native-axes",
            },
            "scenes": scene_records,
        },
        payloads,
    )


class CharacterAnimationBitReader:
    def __init__(self, data: bytes):
        self.data = data
        self.bit_offset = 0

    def read(self, width: int) -> int:
        if width < 0 or self.bit_offset + width > len(self.data) * 8:
            raise ValueError("character animation bitstream is truncated")
        value = 0
        for _ in range(width):
            value = (value << 1) | (
                (self.data[self.bit_offset // 8] >> (7 - self.bit_offset % 8)) & 1
            )
            self.bit_offset += 1
        return value


def character_rotation_quaternion(
    encoded_angles: tuple[int, int, int],
) -> tuple[float, float, float, float]:
    """Convert Conker's three stored quaternion half-angles to glTF XYZW."""

    angles = [
        struct.unpack(">h", struct.pack(">H", value & 0xFFFF))[0]
        * (2.0 * math.pi / 65536.0)
        for value in encoded_angles
    ]
    sx, sy, sz = (math.sin(value) for value in angles)
    cx, cy, cz = (math.cos(value) for value in angles)
    quaternion = (
        sx * cy * cz - cx * sy * sz,
        cx * sy * cz + sx * cy * sz,
        cx * cy * sz - sx * sy * cz,
        cx * cy * cz + sx * sy * sz,
    )
    length = math.sqrt(sum(value * value for value in quaternion))
    return tuple(value / length for value in quaternion)


def decode_character_animation_first_pose(
    descriptor: bytes, bitstream: bytes
) -> tuple[tuple[float, float, float, float], ...]:
    """Decode the first pose using the bit layout consumed by func_150A8A18."""

    if len(descriptor) < 10 or descriptor[1] < 2:
        raise ValueError("character animation descriptor is too short")
    reader = CharacterAnimationBitReader(bitstream)
    for width in (descriptor[6] >> 4, descriptor[6] & 0xF, descriptor[7] & 0xF):
        reader.read(width)
    value_count = (descriptor[1] - 1) * 3
    offset = 10
    values = []
    for _ in range(value_count):
        if offset + 2 > len(descriptor):
            raise ValueError("character animation rotation table is truncated")
        word = struct.unpack_from(">H", descriptor, offset)[0]
        offset += 2
        width = word & 0xF
        value = ((word & 0xFFF0) + (reader.read(width) << 5)) & 0xFFFF
        if value & 0x10:
            if offset + 2 > len(descriptor):
                raise ValueError("character animation alternate rotation is truncated")
            alternate = struct.unpack_from(">H", descriptor, offset)[0]
            offset += 2
            reader.read(alternate & 0xF)
        values.append(value)
    return tuple(
        character_rotation_quaternion(tuple(values[index : index + 3]))
        for index in range(0, len(values), 3)
    )


def load_character_animation_manifest(
    profile: str,
    rom_argument: Path | None,
    *,
    include_files: bool,
) -> tuple[dict[str, Any], dict[str, bytes]]:
    """Preserve the bank-02 data loaded alongside bank-01 character models."""

    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(f"US normalized ROM SHA-1 mismatch: got {digest}")
    banks = {bank.index: bank for bank in parse_asset_banks(normalized, layout["asset_table"])}
    bank = banks.get(0x02)
    if bank is None or bank.flags:
        raise ValueError("US character animation bank 02 is absent")

    files: dict[str, bytes] = {}
    records = []
    clip_pair_count = segment_count = 0
    for entry in parse_asset_entries(normalized, bank):
        raw = normalized[entry.start : entry.end]
        data = decode_rzip_chunk(raw).data if entry.compressed else raw
        entry_file = f"animations/bank-02/entries/{entry.index:04d}.bin"
        if include_files:
            files[entry_file] = data
        record: dict[str, Any] = {
            "bank_entry": entry.index,
            "type_flags": entry.type_flags,
            "compressed": entry.compressed,
            "decoded_size": len(data),
            "decoded_sha1": hashlib.sha1(data).hexdigest(),
            "file": entry_file if include_files else None,
        }
        try:
            segments = parse_model_bundle(data)
        except ValueError:
            record.update(
                format="direct-companion-payload",
                structural_status="exact-bytes-preserved-format-unresolved",
            )
        else:
            if len(segments) % 2:
                raise ValueError(
                    f"bank-02 entry {entry.index} has an odd animation segment count"
                )
            if encode_model_bundle(segments) != data:
                raise ValueError(
                    f"bank-02 entry {entry.index} did not round-trip byte-identically"
                )
            segment_count += len(segments)
            clip_pair_count += len(segments) // 2
            segment_records = []
            for segment in segments:
                segment_file = (
                    f"animations/bank-02/segments/{entry.index:04d}-"
                    f"{segment.index:04d}.bin"
                )
                if include_files:
                    files[segment_file] = segment.data
                segment_records.append(
                    {
                        "index": segment.index,
                        "role": "pair-even" if segment.index % 2 == 0 else "pair-odd",
                        "offset": f"0x{segment.offset:X}",
                        "size": segment.size,
                        "final_flag": segment.final_flag,
                        "sha1": hashlib.sha1(segment.data).hexdigest(),
                        "file": segment_file if include_files else None,
                    }
                )
            record.update(
                format="paired-animation-segment-table",
                structural_status="proven-even-paired-segments",
                segment_count=len(segments),
                clip_pair_count=len(segments) // 2,
                segments=segment_records,
            )
        records.append(record)
    indexed_records = [
        record
        for record in records
        if record["format"] == "paired-animation-segment-table"
    ]
    return (
        {
            "schema_version": 1,
            "family": "indexed-bank-02-character-animation-companions",
            "profile": profile,
            "source_rom": manifest_source(rom_path),
            "source_byte_order": source_order,
            "normalized_sha1": digest,
            "bank_index": 2,
            "entry_count": len(records),
            "indexed_animation_entry_count": len(indexed_records),
            "direct_companion_entry_count": len(records) - len(indexed_records),
            "animation_segment_count": segment_count,
            "clip_pair_count": clip_pair_count,
            "decoded_size": sum(record["decoded_size"] for record in records),
            "structural_status": "byte-identical-even-segment-pairs-proven",
            "semantic_status": "pair-role-and-channel-bitstream-decode-unresolved",
            "runtime_evidence": {
                "loader": "func_1503D774",
                "loader_assembly": "asm/nonmatchings/game_6A3D0/func_1503D774.s",
                "bank_path": [2, "character-model-index"],
                "caller": "func_1503CF20",
                "index_limit": 187,
            },
            "entries": records,
        },
        files,
    )


def make_manifest(
    rom_path: Path,
    source_order: str,
    digest: str,
    bundles: list[ModelBundle],
    render_state_tables: tuple[dict[str, Any], ...],
    include_files: bool,
    bank_index: int = DEFAULT_BANK_INDEX,
) -> dict[str, Any]:
    records = []
    for bundle in bundles:
        segments = []
        for segment in bundle.segments:
            filename = f"bundles/{bundle.index:04d}/segment-{segment.index:02d}.bin"
            record = {
                "index": segment.index,
                "offset": f"0x{segment.offset:X}",
                "size": segment.size,
                "final_flag": segment.final_flag,
                "sha1": hashlib.sha1(segment.data).hexdigest(),
                "file": filename if include_files else None,
                "model_status": "empty" if not segment.data else "geometry-proven",
            }
            if segment.data:
                geometry = parse_geometry_for_bank(segment.data, bank_index)
                geometry_record = {
                    "vertex_count": len(geometry.vertices),
                    "face_count": len(geometry.faces),
                    "texture_coordinate_count": texture_coordinate_count(geometry),
                    "display_list_offset": f"0x{geometry.display_list_offset:X}",
                    "display_list_size": geometry.display_list_size,
                    "vertex_load_count": geometry.vertex_load_count,
                    "segment_8_display_list_count": len(
                        geometry.segment_8_display_list_offsets
                    ),
                    "segment_8_display_list_offsets": [
                        f"0x{offset:X}"
                        for offset in geometry.segment_8_display_list_offsets
                    ],
                    "header_words": [f"0x{word:08X}" for word in geometry.header_words],
                    "header_flags": (
                        f"0x{geometry.header_words[-1]:08X}"
                    ),
                    "file": (
                        f"geometry/{bundle.index:04d}-{segment.index:02d}.obj"
                        if include_files
                        else None
                    ),
                }
                if bank_index == 0x01:
                    _, character_layout = parse_character_model_geometry(segment.data)
                    for section in character_layout["sections"]:
                        if section["file"] is not None:
                            section["file"] = section["file"].format(entry=bundle.index)
                    geometry_record["character_layout"] = character_layout
                for name, region in (
                    ("secondary_region", geometry.secondary_region),
                    ("tertiary_region", geometry.tertiary_region),
                ):
                    if region is None:
                        geometry_record[name] = None
                        continue
                    region_filename = (
                        f"regions/{bundle.index:04d}-{segment.index:02d}-"
                        f"{name.removesuffix('_region')}.bin"
                    )
                    region_data = segment.data[
                        region.offset : region.offset + region.size
                    ]
                    geometry_record[name] = {
                        "offset": f"0x{region.offset:X}",
                        "size": region.size,
                        "sha1": hashlib.sha1(region_data).hexdigest(),
                        "file": region_filename if include_files else None,
                        "semantic_status": "unresolved",
                    }
                descriptors = geometry.vertex_color_animation_descriptors
                geometry_record["vertex_color_animation"] = (
                    {
                        "table_offset": (
                            f"0x{geometry.vertex_color_animation_offset:X}"
                        ),
                        "table_size": geometry.vertex_color_animation_table_size,
                        "descriptor_count": len(descriptors),
                        "vertex_reference_count": sum(
                            descriptor.vertex_count for descriptor in descriptors
                        ),
                        "descriptors": [
                            {
                                "color_data_offset": (
                                    f"0x{descriptor.color_data_offset:X}"
                                ),
                                "vertex_index_offset": (
                                    f"0x{descriptor.vertex_index_offset:X}"
                                ),
                                "vertex_count": descriptor.vertex_count,
                                "max_vertex_index": descriptor.max_vertex_index,
                            }
                            for descriptor in descriptors
                        ],
                    }
                    if geometry.vertex_color_animation_offset is not None
                    else None
                )
                texture_reference_counts: dict[tuple[int, int, int], int] = {}
                for reference in geometry.texture_references:
                    key = (
                        reference.image_command,
                        reference.flat_index,
                        reference.mode,
                    )
                    texture_reference_counts[key] = (
                        texture_reference_counts.get(key, 0) + 1
                    )
                geometry_record["flat_texture_references"] = {
                    "reference_count": len(geometry.texture_references),
                    "unique_flat_index_count": len(
                        {
                            reference.flat_index
                            for reference in geometry.texture_references
                        }
                    ),
                    "references": [
                        {
                            "image_command": f"0x{image_command:08X}",
                            "flat_index": flat_index,
                            "mode": mode,
                            "occurrence_count": count,
                        }
                        for (image_command, flat_index, mode), count in sorted(
                            texture_reference_counts.items()
                        )
                    ],
                }
                runtime_segment_counts: dict[tuple[int, int], int] = {}
                for address in geometry.runtime_segment_texture_addresses:
                    runtime_segment_counts[address] = (
                        runtime_segment_counts.get(address, 0) + 1
                    )
                geometry_record["runtime_segment_texture_references"] = {
                    "reference_count": len(
                        geometry.runtime_segment_texture_addresses
                    ),
                    "addresses": [
                        {
                            "segment": segment_id,
                            "offset": f"0x{offset:X}",
                            "occurrence_count": count,
                        }
                        for (segment_id, offset), count in sorted(
                            runtime_segment_counts.items()
                        )
                    ],
                }
                geometry_record["material_run_count"] = len(
                    geometry.material_runs
                )
                geometry_record["material_runs"] = [
                    {
                        "index": index,
                        "name": material_name(run),
                        "first_face": run.first_face,
                        "face_count": run.face_count,
                        "texture_enabled": run.texture_enabled,
                        "pixel": texture_binding_record(run.pixel),
                        "palette": texture_binding_record(run.palette),
                        "render_tile": (
                            [f"0x{word:08X}" for word in run.render_tile]
                            if run.render_tile is not None
                            else None
                        ),
                        "tile_bounds": (
                            [f"0x{word:08X}" for word in run.tile_bounds]
                            if run.tile_bounds is not None
                            else None
                        ),
                        "texture_scale": (
                            [f"0x{word:08X}" for word in run.texture_scale]
                            if run.texture_scale is not None
                            else None
                        ),
                        "combine_mode": command_pair_record(run.combine_mode),
                        "combine_formula": decode_combine_mode(run.combine_mode),
                        "other_mode": command_pair_record(run.other_mode),
                        "runtime_render_state_offset": (
                            f"0x{run.runtime_render_state_offset:X}"
                            if run.runtime_render_state_offset is not None
                            else None
                        ),
                        "matrix_index": run.matrix_index,
                        "texture_coordinates": (
                            texture_coordinate_state(run)
                            if run.texture_coordinates_proven
                            else None
                        ),
                        "texture_coordinate_status": (
                            "proven"
                            if run.texture_coordinates_proven
                            else "runtime-state-unresolved"
                        ),
                    }
                    for index, run in enumerate(geometry.material_runs)
                ]
                geometry_record["material_file"] = (
                    f"geometry/{bundle.index:04d}-{segment.index:02d}.mtl"
                    if include_files
                    else None
                )
                if (
                    bank_index == 0x04
                    and segment.index == 0
                    and geometry.tertiary_region is not None
                ):
                    region = geometry.tertiary_region
                    if region.size < 8 or region.size % 4:
                        raise ValueError(
                            "primary model tertiary region has an invalid runtime table size"
                        )
                    header_word_0, header_word_1 = struct.unpack_from(
                        ">II", segment.data, region.offset
                    )
                    if header_word_1 != 5:
                        raise ValueError(
                            "primary model tertiary region lacks its runtime table header"
                        )
                    geometry_record["tertiary_region"]["runtime_lookup"] = {
                        "header_words": [
                            f"0x{header_word_0:08X}",
                            f"0x{header_word_1:08X}",
                        ],
                        "entry_count": (region.size - 8) // 4,
                        "entry_size": 4,
                        "data_offset": f"0x{region.offset + 8:X}",
                        "semantic_status": "surface-metadata-proven",
                    }
                elif (
                    bank_index == 0x03
                    and geometry.tertiary_region is not None
                    and geometry.tertiary_region.size == len(geometry.faces) * 4
                ):
                    geometry_record["tertiary_region"]["record_shape"] = {
                        "entry_count": len(geometry.faces),
                        "entry_size": 4,
                        "structural_status": "one-record-per-primary-face",
                        "semantic_status": "unresolved",
                    }
                record["geometry"] = geometry_record
            segments.append(record)
        records.append(
            {
                "bank_entry": bundle.index,
                "type_flags": bundle.type_flags,
                "compressed": bundle.compressed,
                "decoded_size": len(bundle.data),
                "decoded_sha1": hashlib.sha1(bundle.data).hexdigest(),
                "descriptor_count": len(bundle.segments),
                "segments": segments,
            }
        )
    observed_render_state_offsets = {
        int(offset, 16)
        for record in records
        for segment in record["segments"]
        for offset in segment.get("geometry", {}).get(
            "segment_8_display_list_offsets", []
        )
    }
    unsupported_render_state_offsets = observed_render_state_offsets.difference(
        RUNTIME_RENDER_STATE_OFFSETS
    )
    if unsupported_render_state_offsets:
        raise ValueError(
            "model display lists reference unvalidated runtime render-state offsets: "
            + ", ".join(
                f"0x{offset:X}" for offset in sorted(unsupported_render_state_offsets)
            )
        )
    return {
        "schema_version": 1,
        "family": {
            0x01: "indexed-bank-01-rigged-character-model-geometry",
            0x03: "indexed-bank-03-object-model-geometry",
            0x04: "indexed-bank-04-segmented-model-geometry",
            0x09: "indexed-bank-09-direct-model-subset",
        }[bank_index],
        "profile": "us",
        "source_rom": manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": digest,
        "bank_index": bank_index,
        "structural_status": "proven",
        "semantic_status": (
            "primary-geometry-hierarchy-rigid-matrix-assignments-and-texture-"
            "descriptors-proven-character-auxiliary-material-and-animation-"
            "semantics-unresolved"
            if bank_index == 0x01
            else "primary-geometry-material-uv-and-vertex-color-animation-proven-"
            "runtime-segment-8-render-state-family-proven-selection-unresolved"
        ),
        "character_texture_descriptor_count": sum(
            segment.get("geometry", {})
            .get("character_layout", {})
            .get("texture_descriptor_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "runtime_render_state_tables": list(render_state_tables),
        "runtime_render_state_table_count": len(render_state_tables),
        "runtime_render_state_entry_count": sum(
            table["entry_count"] for table in render_state_tables
        ),
        "runtime_render_state_offsets_used": [
            f"0x{offset:X}" for offset in sorted(observed_render_state_offsets)
        ],
        "runtime_evidence": {
            "loader": (
                {
                    "function": "func_1503CF20",
                    "assembly": "asm/nonmatchings/game_6A3D0/func_1503CF20.s",
                    "bank_path": [1, "character-model-index"],
                    "model_limit": 187,
                    "payload_shape": "rigged-character-model",
                    "header_size": "0x38",
                    "triangle_counter": "func_1503D984",
                    "texture_descriptor_loader": "func_1503DC3C",
                    "texture_resolver": "func_1510D0EC",
                }
                if bank_index == 0x01
                else
                {
                    "function": "func_150031EC",
                    "assembly": "asm/nonmatchings/game_305D0/func_150031EC.s",
                    "bank_path": [4, "level-index"],
                    "bundle_limit": 69,
                    "payload_shape": "segmented-level-bundle",
                }
                if bank_index == 0x04
                else {
                    "function": "func_150039E0",
                    "assembly": "asm/nonmatchings/game_30E90/func_150039E0.s",
                    "bank_path": [3, "object-model-index"],
                    "index_source": "placement-record-plus-0x10",
                    "payload_shape": "direct-model",
                }
                if bank_index == 0x03
                else {
                    "functions": ["func_1502FE10", "func_1518C900"],
                    "assembly": [
                        "asm/nonmatchings/game_5D2C0/func_1502FE10.s",
                        "asm/nonmatchings/game_1B9DB0/func_1518C900.s",
                    ],
                    "bank_path": [9, "runtime-index"],
                    "payload_shape": "display-list-pointer-table",
                    "selected_subset": "direct-model-header-compatible",
                }
            ),
            "outer_relocator": {
                "function": "func_1502B4A8",
                "assembly": "asm/nonmatchings/game_57FA0/func_1502B4A8.s",
                "size_mask": "0x0FFFFFFF",
                "final_flag": "0x80000000",
            },
            "display_list_relocator": {
                "function": "func_150049A4",
                "assembly": "asm/nonmatchings/game_30E90/func_150049A4.s",
                "opcode_load": "signed-byte",
                "segment_8_de_relocation": "unreachable-positive-0xDE-compare",
            },
            "segment_8_setup_examples": [
                {
                    "function": "func_15035D6C",
                    "assembly": "asm/nonmatchings/game_623D0/func_15035D6C.s",
                    "command": "0xDB060020",
                },
                {
                    "function": "func_151137D4",
                    "assembly": "asm/nonmatchings/game_13F9D0/func_151137D4.s",
                    "command": "0xDB060020",
                },
            ],
            "segment_8_render_state": {
                "game_data_vram": "0x80082B20",
                "first_table": "0x80082FC0",
                "last_table": "0x80083EC0",
                "table_stride": "0x180",
                "entry_stride": "0x10",
                "entry_shape": "EF OtherMode command followed by DF EndDL",
                "selection_status": "renderer-runtime-dependent",
                "geometry_effect": "none",
            },
            "packed_triangle_decoder": {
                "function": "func_1510BF60",
                "assembly": "asm/nonmatchings/game_139410/func_1510BF60.s",
            },
            "vertex_color_animation": {
                "relocator": {
                    "function": "func_15003120",
                    "assembly": "asm/nonmatchings/game_305D0/func_15003120.s",
                    "descriptor_size": 12,
                    "terminator": "zero-color-data-pointer",
                },
                "consumer": {
                    "function": "func_151739B0",
                    "assembly": "asm/nonmatchings/game_1A0E60/func_151739B0.s",
                    "color_stride": 3,
                    "vertex_index_stride": 2,
                },
            },
            "primary_model_tertiary_lookup": {
                "function": "func_150039BC",
                "assembly": "asm/nonmatchings/game_305D0/func_150039BC.s",
                "header_size": 8,
                "entry_size": 4,
                "semantic_status": "surface-metadata-proven",
            },
            "secondary_region_pointer_array": {
                "loader": "func_150031EC",
                "storage": "D_800B0E20",
                "slot_count": 4,
                "consumer_status": (
                    "no-static-reference-beyond-loader-in-current-us-assembly"
                ),
                "semantic_status": "unresolved",
            },
            "flat_texture_resolver": {
                "function": "func_1510CE60",
                "assembly": "asm/nonmatchings/game_139FC0/func_1510CE60.s",
                "opcode": "0xFD",
                "asset_loader": "func_1510D0EC",
                "flat_index_mask": "0x003FFFFF",
                "mode_shift": 22,
            },
            "material_state": {
                "texture_toggle_opcode": "0xD7",
                "texture_enable_bit": 1,
                "pixel_load_opcode": "0xF3",
                "palette_load_opcode": "0xF0",
                "grouping": "contiguous-primary-face-runs",
                "render_tile_opcode": "0xF5",
                "render_tile_bounds_opcode": "0xF2",
                "texture_coordinate_scale_opcode": "0xD7",
                "combine_mode_opcode": "0xFC",
                "direct_other_mode_opcode": "0xEF",
                "vertex_coordinate_fractional_bits": 5,
                "obj_v_axis": "one-minus-normalized-t",
            },
        },
        "bundle_count": len(records),
        "segment_count": sum(len(record["segments"]) for record in records),
        "model_count": sum(
            segment["model_status"] == "geometry-proven"
            for record in records
            for segment in record["segments"]
        ),
        "drawable_model_count": sum(
            segment.get("geometry", {}).get("face_count", 0) > 0
            for record in records
            for segment in record["segments"]
        ),
        "empty_geometry_model_count": sum(
            segment.get("geometry", {}).get("face_count") == 0
            for record in records
            for segment in record["segments"]
            if "geometry" in segment
        ),
        "empty_segment_count": sum(
            segment["model_status"] == "empty"
            for record in records
            for segment in record["segments"]
        ),
        "vertex_count": sum(
            segment.get("geometry", {}).get("vertex_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "face_count": sum(
            segment.get("geometry", {}).get("face_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "texture_coordinate_count": sum(
            segment.get("geometry", {}).get("texture_coordinate_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "runtime_segment_8_display_list_count": sum(
            segment.get("geometry", {}).get("segment_8_display_list_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "secondary_region_count": sum(
            segment.get("geometry", {}).get("secondary_region") is not None
            for record in records
            for segment in record["segments"]
        ),
        "tertiary_region_count": sum(
            segment.get("geometry", {}).get("tertiary_region") is not None
            for record in records
            for segment in record["segments"]
        ),
        "primary_surface_metadata_table_count": sum(
            "runtime_lookup"
            in (segment.get("geometry", {}).get("tertiary_region") or {})
            for record in records
            for segment in record["segments"]
        ),
        "per_face_metadata_region_count": sum(
            "record_shape"
            in (segment.get("geometry", {}).get("tertiary_region") or {})
            for record in records
            for segment in record["segments"]
        ),
        "vertex_color_animation_model_count": sum(
            segment.get("geometry", {}).get("vertex_color_animation") is not None
            for record in records
            for segment in record["segments"]
        ),
        "vertex_color_animation_descriptor_count": sum(
            segment["geometry"]["vertex_color_animation"]["descriptor_count"]
            for record in records
            for segment in record["segments"]
            if segment.get("geometry", {}).get("vertex_color_animation") is not None
        ),
        "vertex_color_animation_vertex_reference_count": sum(
            segment["geometry"]["vertex_color_animation"]["vertex_reference_count"]
            for record in records
            for segment in record["segments"]
            if segment.get("geometry", {}).get("vertex_color_animation") is not None
        ),
        "flat_texture_reference_count": sum(
            segment.get("geometry", {})
            .get("flat_texture_references", {})
            .get("reference_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "unique_flat_texture_index_count": len(
            {
                reference["flat_index"]
                for record in records
                for segment in record["segments"]
                for reference in segment.get("geometry", {})
                .get("flat_texture_references", {})
                .get("references", [])
            }
        ),
        "runtime_segment_texture_reference_count": sum(
            segment.get("geometry", {})
            .get("runtime_segment_texture_references", {})
            .get("reference_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "material_run_count": sum(
            segment.get("geometry", {}).get("material_run_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "combine_mode_count": len(
            {
                tuple(run["combine_mode"])
                for record in records
                for segment in record["segments"]
                for run in segment.get("geometry", {}).get("material_runs", [])
                if run["combine_mode"] is not None
            }
        ),
        "direct_other_mode_count": len(
            {
                tuple(run["other_mode"])
                for record in records
                for segment in record["segments"]
                for run in segment.get("geometry", {}).get("material_runs", [])
                if run["other_mode"] is not None
            }
        ),
        "runtime_render_state_material_run_count": sum(
            run["runtime_render_state_offset"] is not None
            for record in records
            for segment in record["segments"]
            for run in segment.get("geometry", {}).get("material_runs", [])
        ),
        "flat_texture_face_count": sum(
            run["face_count"]
            for record in records
            for segment in record["segments"]
            for run in segment.get("geometry", {}).get("material_runs", [])
            if run["pixel"] is not None
            and run["pixel"]["source"] == "flat-archive"
        ),
        "runtime_segment_texture_face_count": sum(
            run["face_count"]
            for record in records
            for segment in record["segments"]
            for run in segment.get("geometry", {}).get("material_runs", [])
            if run["pixel"] is not None
            and run["pixel"]["source"] == "runtime-segment"
        ),
        "external_runtime_texture_face_count": sum(
            run["face_count"]
            for record in records
            for segment in record["segments"]
            for run in segment.get("geometry", {}).get("material_runs", [])
            if run["pixel"] is not None
            and run["pixel"]["source"] == "external-runtime-state"
        ),
        "untextured_face_count": sum(
            run["face_count"]
            for record in records
            for segment in record["segments"]
            for run in segment.get("geometry", {}).get("material_runs", [])
            if not run["texture_enabled"]
        ),
        "decoded_size": sum(record["decoded_size"] for record in records),
        "bundles": records,
    }


def extract_models(
    profile: str,
    rom_argument: Path | None,
    output: Path,
    force: bool,
    bank_index: int = DEFAULT_BANK_INDEX,
) -> dict[str, Any]:
    rom_path, source_order, digest, bundles, render_state_tables = load_model_bundles(
        profile, rom_argument, bank_index
    )
    prepare_output(output, force)
    for bundle in bundles:
        for segment in bundle.segments:
            path = output / f"bundles/{bundle.index:04d}/segment-{segment.index:02d}.bin"
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(segment.data)
            if segment.data:
                geometry = parse_geometry_for_bank(segment.data, bank_index)
                obj_path = output / f"geometry/{bundle.index:04d}-{segment.index:02d}.obj"
                obj_path.parent.mkdir(parents=True, exist_ok=True)
                obj_path.write_bytes(
                    encode_obj(bundle.index, segment.index, geometry, bank_index)
                )
                mtl_path = output / f"geometry/{bundle.index:04d}-{segment.index:02d}.mtl"
                mtl_path.write_bytes(
                    encode_mtl(
                        bundle.index,
                        segment.index,
                        geometry,
                        bank_index=bank_index,
                    )
                )
                if bank_index == 0x01:
                    _, character_layout = parse_character_model_geometry(segment.data)
                    for section in character_layout["sections"]:
                        if section["offset"] is None or section["size"] == 0:
                            continue
                        offset = int(section["offset"], 16)
                        region_path = output / section["file"].format(entry=bundle.index)
                        region_path.parent.mkdir(parents=True, exist_ok=True)
                        region_path.write_bytes(
                            segment.data[offset : offset + section["size"]]
                        )
                for name, region in (
                    ("secondary", geometry.secondary_region),
                    ("tertiary", geometry.tertiary_region),
                ):
                    if region is None:
                        continue
                    region_path = (
                        output
                        / f"regions/{bundle.index:04d}-{segment.index:02d}-{name}.bin"
                    )
                    region_path.parent.mkdir(parents=True, exist_ok=True)
                    region_path.write_bytes(
                        segment.data[region.offset : region.offset + region.size]
                    )
    manifest = make_manifest(
        rom_path,
        source_order,
        digest,
        bundles,
        render_state_tables,
        True,
        bank_index,
    )
    if bank_index == 0x03:
        placements, placement_payloads = load_object_placement_manifest(
            profile, rom_argument, include_files=True
        )
        for (placement_bank, scene_index), payload in placement_payloads.items():
            placement_path = (
                output
                / f"placements/bank-{placement_bank:02x}/scene-{scene_index:02d}.bin"
            )
            placement_path.parent.mkdir(parents=True, exist_ok=True)
            placement_path.write_bytes(payload)
        manifest["object_placements"] = placements
    elif bank_index == 0x01:
        animations, animation_files = load_character_animation_manifest(
            profile, rom_argument, include_files=True
        )
        for relative_file, data in animation_files.items():
            path = output / relative_file
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)
        manifest["character_animations"] = animations
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    return manifest


def extract_model_preview(
    profile: str,
    rom_argument: Path | None,
    texture_root: Path,
    output: Path,
    force: bool,
    bank_index: int = DEFAULT_BANK_INDEX,
) -> dict[str, Any]:
    rom_path, source_order, digest, bundles, render_state_tables = load_model_bundles(
        profile, rom_argument, bank_index
    )
    catalog = load_preview_texture_catalog(texture_root, digest)
    prepare_output(output, force)
    copied_textures: dict[PreviewTexture, str] = {}
    model_records = []
    model_gltfs: dict[int, tuple[dict[str, Any], bytes]] = {}
    character_animation_manifest = None
    character_animation_files: dict[str, bytes] = {}
    if bank_index == 0x01:
        character_animation_manifest, character_animation_files = (
            load_character_animation_manifest(
                profile, rom_argument, include_files=True
            )
        )
    reason_counts: dict[str, int] = {}
    reason_face_counts: dict[str, int] = {}
    linked_run_count = linked_face_count = 0
    for bundle in bundles:
        for segment in bundle.segments:
            if not segment.data:
                continue
            character_joints = None
            character_rotations = None
            character_pose_source = None
            if bank_index == 0x01:
                geometry, character_layout = parse_character_model_geometry(
                    segment.data
                )
                character_joints = tuple(character_layout["joints"])
                pose_pair = CHARACTER_PREVIEW_POSE_PAIRS.get(bundle.index)
                if pose_pair is not None:
                    descriptor_name = (
                        f"animations/bank-02/segments/{bundle.index:04d}-"
                        f"{pose_pair * 2:04d}.bin"
                    )
                    bitstream_name = (
                        f"animations/bank-02/segments/{bundle.index:04d}-"
                        f"{pose_pair * 2 + 1:04d}.bin"
                    )
                    if (
                        descriptor_name not in character_animation_files
                        or bitstream_name not in character_animation_files
                    ):
                        raise ValueError(
                            f"bank-01 entry {bundle.index} preview pose pair is absent"
                        )
                    character_rotations = decode_character_animation_first_pose(
                        character_animation_files[descriptor_name],
                        character_animation_files[bitstream_name],
                    )
                    if len(character_rotations) != len(character_joints):
                        raise ValueError(
                            f"bank-01 entry {bundle.index} preview pose joint count changed"
                        )
                    character_pose_source = (
                        f"bank-02-entry-{bundle.index:04d}-pair-{pose_pair:04d}-first-pose"
                    )
            else:
                geometry = parse_geometry_for_bank(segment.data, bank_index)
            texture_files: dict[str, str] = {}
            run_records = []
            for run_index, run in enumerate(geometry.material_runs):
                texture, status = choose_preview_texture(run, catalog)
                reason_counts[status] = reason_counts.get(status, 0) + 1
                reason_face_counts[status] = (
                    reason_face_counts.get(status, 0) + run.face_count
                )
                record = {
                    "material_run": run_index,
                    "material": material_name(run),
                    "face_count": run.face_count,
                    "matrix_index": run.matrix_index,
                    "status": status,
                    "combine_mode": command_pair_record(run.combine_mode),
                    "combine_formula": decode_combine_mode(run.combine_mode),
                    "other_mode": command_pair_record(run.other_mode),
                    "runtime_render_state_offset": (
                        f"0x{run.runtime_render_state_offset:X}"
                        if run.runtime_render_state_offset is not None
                        else None
                    ),
                    "texture": None,
                }
                if texture is not None:
                    linked_run_count += 1
                    linked_face_count += run.face_count
                    filename = copied_textures.get(texture)
                    if filename is None:
                        filename = preview_texture_filename(texture)
                        destination = output / "textures" / filename
                        destination.parent.mkdir(parents=True, exist_ok=True)
                        shutil.copyfile(texture.source, destination)
                        copied_textures[texture] = filename
                    material = material_name(run)
                    relative_texture = f"../textures/{filename}"
                    previous = texture_files.setdefault(material, relative_texture)
                    if previous != relative_texture:
                        raise ValueError(
                            f"material {material} resolves to multiple preview textures"
                        )
                    record["texture"] = {
                        "flat_index": texture.flat_index,
                        "format": texture.format,
                        "size": texture.size,
                        "width": texture.width,
                        "height": texture.height,
                        "source_family": texture.family,
                        "file": f"textures/{filename}",
                        "png_sha1": texture.sha1,
                    }
                run_records.append(record)
            stem = f"{bundle.index:04d}-{segment.index:02d}"
            geometry_dir = output / "geometry"
            geometry_dir.mkdir(parents=True, exist_ok=True)
            (geometry_dir / f"{stem}.obj").write_bytes(
                encode_obj(bundle.index, segment.index, geometry, bank_index)
            )
            (geometry_dir / f"{stem}.mtl").write_bytes(
                encode_mtl(
                    bundle.index,
                    segment.index,
                    geometry,
                    texture_files,
                    bank_index,
                )
            )
            gltf_data, gltf_binary = encode_gltf(
                bundle.index,
                segment.index,
                geometry,
                texture_files,
                bank_index,
                character_joints,
                character_rotations,
                character_pose_source,
            )
            (geometry_dir / f"{stem}.gltf").write_bytes(gltf_data)
            (geometry_dir / f"{stem}.bin").write_bytes(gltf_binary)
            if bank_index == 0x03:
                model_gltfs[bundle.index] = (json.loads(gltf_data), gltf_binary)
            model_records.append(
                {
                    "bank_entry": bundle.index,
                    "segment": segment.index,
                    "object_file": f"geometry/{stem}.obj",
                    "material_file": f"geometry/{stem}.mtl",
                    "gltf_file": f"geometry/{stem}.gltf",
                    "gltf_binary_file": f"geometry/{stem}.bin",
                    "vertex_count": len(geometry.vertices),
                    "face_count": len(geometry.faces),
                    "texture_coordinate_count": texture_coordinate_count(geometry),
                    "material_runs": run_records,
                    "joint_count": len(character_joints or ()),
                    "preview_pose": (
                        character_pose_source
                        or "translation-hierarchy-animation-rotations-unresolved"
                    )
                    if bank_index == 0x01 else None,
                }
            )
    assembled_scenes = []
    if bank_index == 0x03:
        placements, _ = load_object_placement_manifest(
            profile, rom_argument, include_files=False
        )
        for scene in placements["scenes"]:
            if scene["bank_index"] != 0x0C or not scene["records"]:
                continue
            scene_index = scene["scene_index"]
            scene_gltf, scene_binary = encode_placement_scene_gltf(
                scene_index, scene["records"], model_gltfs
            )
            scene_dir = output / "scenes"
            scene_dir.mkdir(parents=True, exist_ok=True)
            stem = f"scene-{scene_index:02d}"
            (scene_dir / f"{stem}.gltf").write_bytes(scene_gltf)
            (scene_dir / f"{stem}.bin").write_bytes(scene_binary)
            assembled_scenes.append(
                {
                    "scene_index": scene_index,
                    "placement_record_count": scene["record_count"],
                    "unique_model_count": len(
                        {record["model_index"] for record in scene["records"]}
                    ),
                    "gltf_file": f"scenes/{stem}.gltf",
                    "gltf_binary_file": f"scenes/{stem}.bin",
                    "transform_status": "runtime-proven-static-transform",
                }
            )

    manifest = {
        "schema_version": 1,
        "family": f"indexed-bank-{bank_index:02x}-model-preview",
        "profile": "us",
        "source_rom": manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": digest,
        "bank_index": bank_index,
        "source_texture_root": display_path(texture_root),
        "runtime_render_state_tables": list(render_state_tables),
        "runtime_render_state_table_count": len(render_state_tables),
        "instructions_file": "README.txt",
        "model_count": len(model_records),
        "drawable_model_count": sum(model["face_count"] > 0 for model in model_records),
        "rigged_model_count": sum(model["joint_count"] > 0 for model in model_records),
        "joint_count": sum(model["joint_count"] for model in model_records),
        "texture_coordinate_count": sum(
            model["texture_coordinate_count"] for model in model_records
        ),
        "material_run_count": sum(reason_counts.values()),
        "linked_material_run_count": linked_run_count,
        "linked_face_count": linked_face_count,
        "copied_texture_count": len(copied_textures),
        "status_run_counts": dict(sorted(reason_counts.items())),
        "status_face_counts": dict(sorted(reason_face_counts.items())),
        "ci8_palette_runtime_evidence": (
            {
                "initial_model_slots": {
                    "function": "func_150031EC",
                    "call": "0x150033F4",
                    "fifth_argument": 0,
                },
                "object_model_instances": {
                    "function": "func_150039E0",
                    "call": "0x150041F0",
                    "fifth_argument": 0,
                },
                "parser": "func_1510CE60",
                "effect": (
                    "mode-one palette pointers remain at the decoded payload base; "
                    "they do not select payload_end_minus_0x200"
                ),
            }
            if bank_index in (0x01, 0x03, 0x04)
            else {
                "loaders": ["func_1502FE10", "func_1518C900"],
                "parser": "func_1510CE60",
                "fifth_argument": "runtime-supplied",
                "effect": "mode-one palette selection remains runtime-dependent",
            }
        ),
        "limitations": [
            "runtime-segment textures are scene-dependent and are not linked",
            "flat textures without a proven compatible extractor remain unlinked",
            "character same-index TLUT loads prove effective CI4/CI8 sampling, but "
            "their runtime palette/image composition is not yet a standalone PNG "
            "contract and remains unlinked",
            (
                f"bank-{bank_index:02X} model paths load mode-one CI8 palettes with a "
                "null fifth parser argument, so the reversible trailing-palette PNGs "
                "are not linked"
                if bank_index in (0x01, 0x03, 0x04)
                else "bank-09 mode-one CI8 palettes depend on a runtime-supplied fifth "
                "parser argument and remain unlinked"
            ),
            "native-proven PNGs prove reversible pixel storage, not the RDP combiner "
            "and primitive/environment colors needed for a faithful material; they "
            "remain unlinked",
            "OBJ/MTL cannot preserve the vertex-color multiply used by the common "
            "RDP combine mode; use the glTF preview for material inspection",
            "surface metadata and secondary runtime regions remain raw sidecar evidence",
            (
                "bank-01 entry 0000 applies the first pose from exact bank-02 pair 0006; "
                "the remaining compressed animation timelines are preserved but not decoded"
                if bank_index == 0x01
                else "character animation is outside this model family"
            ),
        ],
        "textures": [
            {
                "flat_index": texture.flat_index,
                "format": texture.format,
                "size": texture.size,
                "width": texture.width,
                "height": texture.height,
                "source_family": texture.family,
                "file": f"textures/{filename}",
                "png_sha1": texture.sha1,
            }
            for texture, filename in sorted(
                copied_textures.items(), key=lambda item: item[1]
            )
        ],
        "models": model_records,
    }
    if bank_index == 0x01:
        character_animations = character_animation_manifest
        if character_animations is None:
            raise ValueError("bank-01 character animation manifest is absent")
        manifest["character_animations"] = {
            key: value
            for key, value in character_animations.items()
            if key != "entries"
        }
    if bank_index == 0x03:
        manifest["assembled_scene_count"] = len(assembled_scenes)
        manifest["assembled_scene_placement_count"] = sum(
            scene["placement_record_count"] for scene in assembled_scenes
        )
        manifest["assembled_scenes"] = assembled_scenes
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    (output / "README.txt").write_text(
        f"Conker bank-{bank_index:02X} model previews\n"
        "\n"
        "Recommended viewer: Blender. Use File > Import > glTF 2.0, choose one "
        ".gltf file from geometry/, then switch the viewport to Material "
        "Preview. glTF preserves the N64 vertex colors and multiplies them by "
        "the linked texture, matching the model's common RDP combine mode. Keep "
        "the imported per-material sampler settings: repeat, mirrored repeat, and "
        "clamp modes come directly from each N64 render tile. OBJ/MTL files remain "
        "useful as geometry interchange, but MTL cannot represent that vertex-color "
        "combiner.\n"
        "\n"
        + {
            0x01: (
                "Start with geometry/0000-00.gltf. Its runtime-proven joint hierarchy "
                "imports as a glTF skin. The file applies the first pose from bank-02 "
                "entry 0000 pair 0006 so Conker's tail and limbs assemble; expand the "
                "armature in Blender's Outliner. "
            ),
            0x03: "Start with geometry/0051-00.gltf before loading larger object models. ",
            0x04: (
                "Start with geometry/0002-04.gltf (40 faces, fully linked) before loading "
                "larger level models. "
            ),
            0x09: "Start with geometry/0426-00.gltf before loading larger models. ",
        }[bank_index]
        + (
            "The scenes/ directory contains the 48 nonempty bank-12 direct-model "
            "placement tables assembled with their runtime-proven position, YZX "
            "Euler rotation, and scale transforms. Start with scenes/scene-00.gltf. "
            if bank_index == 0x03
            else ""
        )
        + "Unlinked materials intentionally retain vertex "
        "color only. The native-proven PNGs are reversible storage views, but are "
        "not linked until their RDP combiner and primitive/environment colors are "
        "represented. See manifest.json for per-run status and known runtime "
        "limits. "
        + (
            "Bank-01 glTF files preserve the runtime hierarchy and rigid display-matrix "
            "assignments. Entry 0000 includes one exact decoded runtime pose; remaining "
            "animation timelines remain unresolved. Unconsumed character auxiliary "
            "regions are preserved without assigning unsupported skinning semantics.\n"
            if bank_index == 0x01
            else (
                "Bank-03 scene previews cover direct bank-12 object placements only; "
                "bank-11 dispatch records, dynamic animation, and level geometry are "
                "separate runtime layers.\n"
                if bank_index == 0x03
                else "These are individual native-coordinate model components.\n"
            )
        ),
        encoding="utf-8",
    )
    verify_preview_output(output, manifest)
    return manifest


def verify_models(
    profile: str, rom_argument: Path | None, bank_index: int = DEFAULT_BANK_INDEX
) -> tuple[int, ...]:
    _, _, _, bundles, _ = load_model_bundles(profile, rom_argument, bank_index)
    if bank_index == 0x03:
        placements, payloads = load_object_placement_manifest(
            profile, rom_argument, include_files=False
        )
        if sum(len(payload) for payload in payloads.values()) <= 0:
            raise ValueError("object placement payloads are unexpectedly empty")
        if placements["record_count"] != 1238:
            raise ValueError("US object placement record count changed")
    elif bank_index == 0x01:
        animations, _ = load_character_animation_manifest(
            profile, rom_argument, include_files=False
        )
        if (
            animations["entry_count"] != 145
            or animations["indexed_animation_entry_count"] != 123
            or animations["clip_pair_count"] != 2660
            or animations["decoded_size"] != 4051200
        ):
            raise ValueError("US bank-02 character animation inventory changed")
    model_count = vertex_count = face_count = segment_8_display_list_count = 0
    flat_texture_reference_count = runtime_segment_texture_reference_count = 0
    material_run_count = 0
    flat_texture_face_count = runtime_segment_texture_face_count = 0
    external_runtime_texture_face_count = 0
    untextured_face_count = 0
    texture_coordinate_total = 0
    flat_texture_indices = set()
    for bundle in bundles:
        rebuilt = (
            encode_model_bundle(bundle.segments)
            if bank_index == 0x04
            else bundle.segments[0].data
        )
        if rebuilt != bundle.data:
            raise ValueError(
                f"bank-{bank_index:02X} entry {bundle.index} did not round-trip"
            )
        for segment in bundle.segments:
            if not segment.data:
                continue
            geometry = parse_geometry_for_bank(segment.data, bank_index)
            model_count += 1
            vertex_count += len(geometry.vertices)
            face_count += len(geometry.faces)
            texture_coordinate_total += texture_coordinate_count(geometry)
            segment_8_display_list_count += len(
                geometry.segment_8_display_list_offsets
            )
            flat_texture_reference_count += len(geometry.texture_references)
            flat_texture_indices.update(
                reference.flat_index for reference in geometry.texture_references
            )
            runtime_segment_texture_reference_count += len(
                geometry.runtime_segment_texture_addresses
            )
            material_run_count += len(geometry.material_runs)
            for run in geometry.material_runs:
                if not run.texture_enabled:
                    untextured_face_count += run.face_count
                elif run.pixel is not None and run.pixel.external:
                    external_runtime_texture_face_count += run.face_count
                elif run.pixel is not None and run.pixel.flat_index is not None:
                    flat_texture_face_count += run.face_count
                else:
                    runtime_segment_texture_face_count += run.face_count
    return (
        len(bundles),
        sum(len(bundle.segments) for bundle in bundles),
        model_count,
        vertex_count,
        face_count,
        texture_coordinate_total,
        segment_8_display_list_count,
        flat_texture_reference_count,
        len(flat_texture_indices),
        runtime_segment_texture_reference_count,
        material_run_count,
        flat_texture_face_count,
        runtime_segment_texture_face_count,
        external_runtime_texture_face_count,
        untextured_face_count,
        sum(len(bundle.data) for bundle in bundles),
    )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("survey", "extract", "preview", "verify"))
    parser.add_argument("--profile", choices=("us",), default="us")
    parser.add_argument(
        "--bank",
        choices=("01", "03", "04", "09"),
        default="04",
        help="indexed model bank to process (default: 04 level geometry)",
    )
    parser.add_argument("--rom", type=Path)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--textures", type=Path)
    parser.add_argument("--force", action="store_true")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    bank_index = int(args.bank, 16)
    try:
        if args.action == "survey":
            rom_path, source_order, digest, bundles, render_state_tables = load_model_bundles(
                args.profile, args.rom, bank_index
            )
            manifest = make_manifest(
                rom_path,
                source_order,
                digest,
                bundles,
                render_state_tables,
                False,
                bank_index,
            )
            if bank_index == 0x03:
                placements, _ = load_object_placement_manifest(
                    args.profile, args.rom, include_files=False
                )
                manifest["object_placements"] = placements
            elif bank_index == 0x01:
                animations, _ = load_character_animation_manifest(
                    args.profile, args.rom, include_files=False
                )
                manifest["character_animations"] = animations
            print(json.dumps(manifest, indent=2))
        elif args.action == "extract":
            output = args.output or ROOT / f"build/assets/models/us-bank-{bank_index:02x}"
            if not output.is_absolute():
                output = ROOT / output
            manifest = extract_models(
                args.profile, args.rom, output, args.force, bank_index
            )
            print(
                f"Extracted {manifest['model_count']} US bank-{bank_index:02X} models from "
                f"{manifest['bundle_count']} bundles: {manifest['vertex_count']} vertices, "
                f"{manifest['face_count']} primary faces, "
                f"{manifest['texture_coordinate_count']} UV coordinates, "
                f"{manifest['runtime_segment_8_display_list_count']} runtime segment-8 display lists"
            )
            print(
                f"Auxiliary regions: {manifest['secondary_region_count']} secondary, "
                f"{manifest['tertiary_region_count']} tertiary; "
                f"{manifest['vertex_color_animation_descriptor_count']} vertex-color "
                f"animation descriptors with "
                f"{manifest['vertex_color_animation_vertex_reference_count']} references"
            )
            print(
                f"Texture bindings: {manifest['flat_texture_reference_count']} flat "
                f"references to {manifest['unique_flat_texture_index_count']} indices; "
                f"{manifest['runtime_segment_texture_reference_count']} runtime-segment "
                f"references"
            )
            print(
                f"Material runs: {manifest['material_run_count']} covering "
                f"{manifest['flat_texture_face_count']} flat-textured, "
                f"{manifest['runtime_segment_texture_face_count']} "
                f"runtime-segment, {manifest['external_runtime_texture_face_count']} "
                f"external-runtime, and {manifest['untextured_face_count']} "
                f"untextured faces"
            )
            print(f"Manifest: {display_path(output / 'manifest.json')}")
            if bank_index == 0x03:
                placements = manifest["object_placements"]
                print(
                    f"Object placement records: {placements['record_count']} across "
                    f"{placements['scene_table_count']} scene tables; "
                    f"{placements['referenced_bank_03_model_count']} bank-03 models referenced"
                )
            elif bank_index == 0x01:
                animations = manifest["character_animations"]
                print(
                    f"Character animation companions: {animations['entry_count']} bank-02 "
                    f"entries, {animations['clip_pair_count']} even/odd segment pairs, "
                    f"{animations['decoded_size']} decoded bytes"
                )
                print(
                    "Character texture descriptors: "
                    f"{manifest['character_texture_descriptor_count']} runtime records"
                )
        elif args.action == "preview":
            output = (
                args.output
                or ROOT / f"build/assets/models/us-bank-{bank_index:02x}-preview"
            )
            texture_root = args.textures or ROOT / "build/assets/textures"
            if not output.is_absolute():
                output = ROOT / output
            if not texture_root.is_absolute():
                texture_root = ROOT / texture_root
            manifest = extract_model_preview(
                args.profile,
                args.rom,
                texture_root,
                output,
                args.force,
                bank_index,
            )
            print(
                f"Prepared and verified {manifest['model_count']} model previews with "
                f"{manifest['texture_coordinate_count']} UV coordinates"
            )
            if bank_index == 0x01:
                print(
                    f"Rigged previews: {manifest['rigged_model_count']} models, "
                    f"{manifest['joint_count']} runtime joints; bank-02 animation "
                    "companions are preserved in the preview manifest"
                )
            print(
                f"Linked {manifest['linked_material_run_count']} material runs and "
                f"{manifest['linked_face_count']} faces to "
                f"{manifest['copied_texture_count']} proven texture PNGs"
            )
            print(f"Preview manifest: {display_path(output / 'manifest.json')}")
        else:
            (
                bundle_count,
                segment_count,
                model_count,
                vertex_count,
                face_count,
                texture_coordinate_total,
                segment_8_display_list_count,
                flat_texture_reference_count,
                unique_flat_texture_index_count,
                runtime_segment_texture_reference_count,
                material_run_count,
                flat_texture_face_count,
                runtime_segment_texture_face_count,
                external_runtime_texture_face_count,
                untextured_face_count,
                decoded_size,
            ) = verify_models(args.profile, args.rom, bank_index)
            print(
                f"Verified US bank-{bank_index:02X} models: {bundle_count} bundles, "
                f"{segment_count} segments, {model_count} models, "
                f"{vertex_count} vertices, {face_count} primary faces, "
                f"{texture_coordinate_total} UV coordinates, "
                f"{segment_8_display_list_count} runtime segment-8 display lists, "
                f"{flat_texture_reference_count} flat texture references to "
                f"{unique_flat_texture_index_count} indices, "
                f"{runtime_segment_texture_reference_count} runtime-segment textures, "
                f"{material_run_count} material runs covering "
                f"{flat_texture_face_count} flat-textured, "
                f"{runtime_segment_texture_face_count} runtime-segment, "
                f"{external_runtime_texture_face_count} external-runtime, and "
                f"{untextured_face_count} untextured faces, "
                f"{decoded_size} bytes, byte-identical"
            )
    except (KeyError, OSError, TypeError, ValueError, json.JSONDecodeError) as error:
        print(f"error: {error}")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
