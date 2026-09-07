#!/usr/bin/env python3
"""Survey, extract, verify, and prepare previews of US model geometry."""

from __future__ import annotations

import argparse
import hashlib
import json
import math
import shutil
import struct
from colorsys import hsv_to_rgb
from dataclasses import dataclass, replace
from pathlib import Path
from statistics import median
from typing import Any

try:
    from scripts.rzip_archive import (
        decode_rzip_chunk,
        iter_flat_rzip_entries,
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
    from scripts.texture_assets import (
        encode_ci8_png,
        encode_indexed_png,
        encode_rgba_png,
    )
except ModuleNotFoundError:
    from rzip_archive import (  # type: ignore[no-redef]
        decode_rzip_chunk,
        iter_flat_rzip_entries,
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
    from texture_assets import (  # type: ignore[no-redef]
        encode_ci8_png,
        encode_indexed_png,
        encode_rgba_png,
    )


BANK_INDICES = (0x01, 0x03, 0x04, 0x09)
DEFAULT_BANK_INDEX = 0x04
# Runtime-proven poses are retained as references, but the glTF's default node
# transforms remain the neutral bind hierarchy. Every decoded pose is exposed
# as a separate Action so importing the model does not silently deform it.
CHARACTER_REFERENCE_POSE_PAIRS: dict[int, int] = {0: 25}
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
VALIDATION_ATLAS_VIEW_SIZE = 128
VALIDATION_ATLAS_VIEWS = ("front", "side", "top")
CHARACTER_CUSTOM_MOVEMEM_COMMAND = 0xDC38000E
CHARACTER_RUNTIME_COLOR_STATE = {
    "status": "runtime-dynamic-not-baked",
    "renderer": "func_1502CCFC",
    "color_resolver": "func_1502CC34",
    "color_updater": "func_1510CB10",
    "color_initializer": "func_150006E0",
    "primitive_rgb_storage": "D_800D9B68",
    "environment_rgb_storage": "D_800D9B78",
    "rgb_stride": 3,
    "primitive_command": "0xFA00F200",
    "environment_command": "0xFB000000",
    "alpha_source": "runtime-caller-parameter",
    "effect_override": "func_1502EC34",
}
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
    render_tiles: tuple[tuple[int, int, int], ...]
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
    face_normal_bytes: tuple[
        tuple[
            tuple[int, int, int] | None,
            tuple[int, int, int] | None,
            tuple[int, int, int] | None,
        ],
        ...,
    ]
    header_words: tuple[int, ...]
    face_command_offsets: tuple[int, ...] = ()
    face_command_opcodes: tuple[int, ...] = ()
    face_cache_indices: tuple[tuple[int, int, int], ...] = ()
    custom_normal_command_count: int = 0


@dataclass(frozen=True)
class PreviewTexture:
    family: str
    source: Path | None
    flat_index: int
    format: int
    size: int
    width: int
    height: int
    sha1: str
    png_data: bytes | None = None
    pixel_byte_offset: int | None = None
    palette_byte_offset: int | None = None


@dataclass(frozen=True)
class CharacterAnimationChannel:
    base_value: int
    bit_width: int
    scale_base_value: int | None = None
    scale_bit_width: int | None = None


@dataclass(frozen=True)
class CharacterAnimationLayout:
    joint_count: int
    flags: int
    root_bit_widths: tuple[int, int, int]
    joint_translation_mask: tuple[bool, ...]
    rotation_channels: tuple[CharacterAnimationChannel, ...]
    descriptor_bytes_consumed: int
    descriptor_padding_size: int
    descriptor_runtime_zero_fill_size: int
    frame_bit_size: int
    decoded_frame_byte_size: int
    frame_byte_size: int
    frame_trailing_size: int


@dataclass(frozen=True)
class CharacterAnimationFrame:
    root_translation: tuple[int, int, int]
    joint_translation_deltas: tuple[tuple[int, int, int] | None, ...]
    encoded_rotations: tuple[tuple[int, int, int], ...]
    rotations: tuple[tuple[float, float, float, float], ...]
    scale_channels: tuple[int | None, ...]
    trailing_data: bytes


@dataclass(frozen=True)
class CharacterAnimationClip:
    pair_index: int
    frames: tuple[CharacterAnimationFrame, ...]
    frame_byte_size: int
    bitstream_padding_size: int
    descriptor_runtime_zero_fill_size: int
    companion_trailing_size: int = 0
    companion_trailing_sha1: str | None = None
    duration_ticks: int | None = None
    keyframe_step: int = 1
    duration_status: str = "descriptor-duration-and-keyframe-spacing"
    logical_animation_indices: tuple[int, ...] = ()


ANIMATION_RUNTIME_FPS = 30.0
CHARACTER_ANIMATION_ROUTE_BANK = 0x0F
CHARACTER_ANIMATION_ROUTE_SENTINEL = 0x03E7
CHARACTER_ANIMATION_GROUP_COUNTS_ADDRESS = 0x80098888
CHARACTER_ANIMATION_GROUP_POINTERS_ADDRESS = 0x80084410
CHARACTER_ANIMATION_DURATION_TABLE_ADDRESS = 0x800993F8
CHARACTER_ANIMATION_SPECIAL_DURATION_ADDRESS = 0x8009953C


def character_animation_preview_times(
    clip: CharacterAnimationClip,
) -> tuple[float, ...]:
    """Map stored source frames onto the runtime's 30 Hz animation clock."""

    ticks = [index * clip.keyframe_step for index in range(len(clip.frames))]
    if clip.duration_ticks is not None and ticks:
        ticks[-1] = min(ticks[-1], clip.duration_ticks - 1)
    return tuple(tick / ANIMATION_RUNTIME_FPS for tick in ticks)


def character_global_bind_pivots(
    character_joints: tuple[dict[str, Any], ...],
) -> dict[int, tuple[float, float, float]]:
    """Accumulate the runtime's parent-relative joint translations."""

    joint_by_matrix = {
        joint["matrix_index"]: joint for joint in character_joints
    }
    pivots: dict[int, tuple[float, float, float]] = {}
    visiting = set()

    def resolve(matrix_index: int) -> tuple[float, float, float]:
        if matrix_index in pivots:
            return pivots[matrix_index]
        if matrix_index in visiting:
            raise ValueError("character joint hierarchy contains a parent cycle")
        try:
            joint = joint_by_matrix[matrix_index]
        except KeyError as error:
            raise ValueError(
                f"character joint hierarchy references absent joint {matrix_index}"
            ) from error
        visiting.add(matrix_index)
        local = tuple(float(value) for value in joint["bind_pivot_f32"])
        parent = joint["parent_matrix_index"]
        if parent >= 0:
            parent_pivot = resolve(parent)
            pivot = tuple(local[axis] + parent_pivot[axis] for axis in range(3))
        else:
            pivot = local
        visiting.remove(matrix_index)
        pivots[matrix_index] = pivot
        return pivot

    for matrix_index in joint_by_matrix:
        resolve(matrix_index)
    return pivots


def character_local_animation_translation(
    frame: CharacterAnimationFrame,
    joint: dict[str, Any],
    local_bind_translation: list[float],
) -> tuple[float, float, float]:
    """Apply the runtime's masked translation to one local joint matrix."""

    animation_index = joint["animation_index"]
    delta = frame.joint_translation_deltas[animation_index]
    parent = joint["parent_matrix_index"]
    return tuple(
        float(local_bind_translation[axis])
        + (float(delta[axis]) / 16.0 if delta is not None else 0.0)
        + (
            float(frame.root_translation[axis]) / 1024.0
            if parent < 0
            else 0.0
        )
        for axis in range(3)
    )


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
    collision_flags = record[0x32]
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
        "collision_flags_32": f"0x{collision_flags:02X}",
        "collision_included": collision_flags & 0x60 != 0x20,
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
    face_command_offsets = []
    face_command_opcodes = []
    face_cache_indices = []
    vertex_load_count = 0
    segment_8_display_list_offsets = []
    texture_references = []
    runtime_segment_texture_addresses = []
    pending_texture: ModelTextureBinding | None = None
    pixel_texture: ModelTextureBinding | None = None
    palette_texture: ModelTextureBinding | None = None
    texture_enabled = False
    render_tile: tuple[int, int] | None = None
    render_tiles: dict[int, tuple[int, int]] = {}
    tile_bounds: tuple[int, int] | None = None
    texture_scale: tuple[int, int] | None = None
    combine_mode: tuple[int, int] | None = None
    other_mode: tuple[int, int] | None = None
    runtime_render_state_offset: int | None = None
    matrix_index: int | None = None
    material_runs: list[list[Any]] = []
    normal_base: int | None = None
    normal_cache: dict[int, tuple[int, int, int] | None] = {}
    face_normal_bytes: list[
        tuple[
            tuple[int, int, int] | None,
            tuple[int, int, int] | None,
            tuple[int, int, int] | None,
        ]
    ] = []
    custom_normal_command_count = 0

    def append_faces(cache_indices: tuple[int, ...], command_offset: int) -> None:
        first_face = len(faces)
        for index in range(0, len(cache_indices), 3):
            triangle = cache_indices[index : index + 3]
            if any(cache_index not in cache for cache_index in triangle):
                raise ValueError(
                    f"display-list triangle at 0x{command_offset:X} uses an unloaded vertex"
                )
            faces.append(tuple(cache[cache_index] for cache_index in triangle))
            face_cache_indices.append(tuple(triangle))
            face_normal_bytes.append(
                tuple(normal_cache.get(cache_index) for cache_index in triangle)
            )
            face_command_offsets.append(command_offset)
            face_command_opcodes.append(data[command_offset])
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
        active_render_tiles = (
            tuple(
                (tile_index, command, argument)
                for tile_index, (command, argument) in sorted(render_tiles.items())
            )
            if texture_enabled
            else ()
        )
        active_tile_bounds = tile_bounds if texture_enabled else None
        active_texture_scale = texture_scale if texture_enabled else None
        key = (
            texture_enabled,
            active_pixel,
            active_palette,
            active_render_tile,
            active_render_tiles,
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
                    active_render_tiles,
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
                cache_index = cache_start + local_index
                vertex_index = vertex_start + local_index
                cache[cache_index] = vertex_index
                if normal_base is not None:
                    normal_offset = normal_base + cache_index * 2
                    if normal_offset + 2 <= len(data):
                        normal_x, normal_y = struct.unpack_from(">bb", data, normal_offset)
                        normal_z = vertices[vertex_index].flag & 0xFF
                        if normal_z >= 0x80:
                            normal_z -= 0x100
                        normal_cache[cache_index] = (normal_x, normal_y, normal_z)
                    else:
                        normal_cache[cache_index] = None
            vertex_load_count += 1
        elif opcode == 0xDC:
            if command != CHARACTER_CUSTOM_MOVEMEM_COMMAND:
                raise ValueError(
                    f"unsupported MoveMem command at display-list offset 0x{offset:X}"
                )
            if argument > len(data):
                if allow_external_texture:
                    normal_base = None
                    continue
                raise ValueError(
                    f"normal stream at display-list offset 0x{offset:X} is outside its model"
                )
            normal_base = argument
            custom_normal_command_count += 1
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
            render_tiles[0] = (command, argument)
        elif opcode == 0xF5:
            render_tiles[(argument >> 24) & 7] = (command, argument)
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
                render_tiles=run[6],
                tile_bounds=run[7],
                texture_scale=run[8],
                combine_mode=run[9],
                other_mode=run[10],
                runtime_render_state_offset=run[11],
                matrix_index=run[12],
            )
            for run in material_runs
        ),
        face_normal_bytes=(
            tuple(face_normal_bytes) if custom_normal_command_count else ()
        ),
        header_words=header_words,
        face_command_offsets=tuple(face_command_offsets),
        face_command_opcodes=tuple(face_command_opcodes),
        face_cache_indices=tuple(face_cache_indices),
        custom_normal_command_count=custom_normal_command_count,
    )


def parse_character_face_normal_bytes(
    data: bytes,
    display_offset: int,
    display_size: int,
    vertices: tuple[ModelVertex, ...],
    expected_faces: tuple[tuple[int, int, int], ...],
) -> tuple[
    tuple[
        tuple[int, int, int] | None,
        tuple[int, int, int] | None,
        tuple[int, int, int] | None,
    ],
    ...,
]:
    """Replay CBFD's separate signed-X/Y normal stream per vertex-cache slot."""

    normal_base: int | None = None
    vertex_cache: dict[int, int] = {}
    normal_cache: dict[int, tuple[int, int, int] | None] = {}
    faces = []
    face_normals = []

    for offset in range(display_offset, display_offset + display_size, 8):
        command, argument = struct.unpack_from(">II", data, offset)
        opcode = command >> 24
        if command == CHARACTER_CUSTOM_MOVEMEM_COMMAND:
            normal_base = argument
            continue
        if opcode == 0x01:
            if normal_base is None:
                raise ValueError("bank-01 vertex load precedes its normal-base command")
            count = (command >> 12) & 0xFF
            cache_end = (command >> 1) & 0x7F
            cache_start = cache_end - count
            vertex_start = ((argument & 0xFFFFFF) - 0x38) // 16
            for local_index in range(count):
                cache_index = cache_start + local_index
                vertex_index = vertex_start + local_index
                vertex_cache[cache_index] = vertex_index
                normal_offset = normal_base + cache_index * 2
                if normal_offset + 2 <= len(data):
                    normal_x, normal_y = struct.unpack_from(">bb", data, normal_offset)
                    normal_z = vertices[vertex_index].flag & 0xFF
                    if normal_z >= 0x80:
                        normal_z -= 0x100
                    normal_cache[cache_index] = (normal_x, normal_y, normal_z)
                else:
                    normal_cache[cache_index] = None
            continue

        cache_indices: tuple[int, ...] | None = None
        if opcode == 0x05:
            cache_indices = tuple(
                value // 2 for value in command.to_bytes(4, "big")[1:4]
            )
        elif opcode == 0x06:
            encoded = command.to_bytes(4, "big")[1:4] + argument.to_bytes(
                4, "big"
            )[1:4]
            cache_indices = tuple(value // 2 for value in encoded)
        elif 0x10 <= opcode <= 0x1F:
            cache_indices = packed_four_triangle_indices(command, argument)
        if cache_indices is None:
            continue
        for first in range(0, len(cache_indices), 3):
            triangle = cache_indices[first : first + 3]
            try:
                faces.append(tuple(vertex_cache[index] for index in triangle))
                face_normals.append(tuple(normal_cache[index] for index in triangle))
            except KeyError as error:
                raise ValueError(
                    "bank-01 normal stream references an unloaded vertex-cache slot"
                ) from error

    if tuple(faces) != expected_faces:
        raise ValueError("bank-01 normal replay does not match decoded triangle order")
    return tuple(face_normals)


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
    custom_movemem_commands = []
    auxiliary_offset, auxiliary_size = header_words[8], header_words[9]
    auxiliary_end = auxiliary_offset + auxiliary_size
    procedural_joint_offset = header_words[12]
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
        elif opcode == 0xDC:
            if command != CHARACTER_CUSTOM_MOVEMEM_COMMAND:
                raise ValueError("bank-01 character model has an unsupported MoveMem command")
            if (
                not auxiliary_offset
                or argument < auxiliary_offset
                or argument > auxiliary_end
                or (argument - auxiliary_offset) % 32
            ):
                raise ValueError(
                    "bank-01 custom MoveMem command does not reference its auxiliary region"
                )
            source_location = "auxiliary-region"
            if argument == auxiliary_end:
                if argument != procedural_joint_offset:
                    raise ValueError(
                        "bank-01 custom MoveMem command reaches an unproven auxiliary boundary"
                    )
                source_location = "procedural-tail-boundary"
            custom_movemem_commands.append(
                {
                    "display_list_offset": f"0x{display_offset + relative_offset:X}",
                    "command": f"0x{command:08X}",
                    "source_offset": f"0x{argument:X}",
                    "relative_to_auxiliary": argument - auxiliary_offset,
                    "source_location": source_location,
                }
            )
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
    face_normal_bytes = parse_character_face_normal_bytes(
        data,
        display_offset,
        len(display_data),
        geometry.vertices,
        geometry.faces,
    )
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
        face_normal_bytes=face_normal_bytes,
        header_words=header_words,
        face_command_offsets=tuple(
            offset - synthetic_display_offset + display_offset
            for offset in geometry.face_command_offsets
        ),
        face_command_opcodes=geometry.face_command_opcodes,
        face_cache_indices=geometry.face_cache_indices,
        custom_normal_command_count=len(custom_movemem_commands),
    )
    section_names = (
        "vertex_boundary_table",
        "primary_display_list_pointer_table",
        "joint_table",
        "texture_descriptor_table",
        "custom_movemem_auxiliary_data",
        "secondary_display_list_pointer_table",
        "procedural_animation_joint_index_table",
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
                "bind_pivot_f32": list(translation),
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

    procedural_joint_size = header_words[13] & 0x7FFFFFFF
    if procedural_joint_size not in (0, 2):
        raise ValueError(
            "bank-01 procedural animation joint table is not an optional pair"
        )
    procedural_joint_indices = (
        list(data[procedural_joint_offset : procedural_joint_offset + 2])
        if procedural_joint_size
        else []
    )
    if any(index != 0xFF and index >= len(joints) for index in procedural_joint_indices):
        raise ValueError(
            "bank-01 procedural animation joint table references an absent joint"
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
        "custom_movemem_command_count": len(custom_movemem_commands),
        "custom_movemem_commands": custom_movemem_commands,
        "custom_movemem_semantic_status": (
            "emulator-validated-signed-xy-normal-stream-with-signed-vertex-flag-z"
        ),
        "face_normal_corner_count": len(face_normal_bytes) * 3,
        "source_normal_corner_count": sum(
            normal is not None and normal != (0, 0, 0)
            for face in face_normal_bytes
            for normal in face
        ),
        "zero_source_normal_corner_count": sum(
            normal == (0, 0, 0)
            for face in face_normal_bytes
            for normal in face
        ),
        "unavailable_source_normal_corner_count": sum(
            normal is None
            for face in face_normal_bytes
            for normal in face
        ),
        "gltf_normal_status": (
            "normalized-source-normal-with-geometric-fallback-for-zero-or-"
            "unavailable-preview-corners"
        ),
        "procedural_animation_joint_indices": [
            None if index == 0xFF else index for index in procedural_joint_indices
        ],
        "procedural_animation_joint_index_count": len(procedural_joint_indices),
        "sections": sections,
        "structural_status": (
            "runtime-proven-container-rigged-geometry-and-texture-descriptors"
        ),
        "rig_semantic_status": (
            "runtime-proven-hierarchy-and-rigid-matrix-assignments-"
            "custom-normal-stream-emulator-validated"
        ),
        "runtime_evidence": {
            "pose_function": "func_150A81D0",
            "triangle_count_function": "func_1503D984",
            "runtime_triangle_count": len(geometry.faces),
            "joint_record_size": 16,
            "parent_matrix_index_offset": 0,
            "matrix_index_offset": 1,
            "animation_index_offset": 2,
            "bind_pivot_offset": 4,
            "bind_pivot_semantics": (
                "parent-relative-translation-accumulated-to-model-space-pivot"
            ),
            "matrix_stride": "0x40",
            "display_list_matrix_command": "DA380003 segment-3 offset / 0x40",
            "texture_descriptor_loader": "func_1503DC3C",
            "texture_resolver": "func_1510D0EC",
            "texture_descriptor_record_size": 12,
            "texture_pointer_slot_offset": 0,
            "texture_flat_index_offset": 4,
            "texture_width_offset": 8,
            "texture_height_offset": 10,
            "custom_movemem_command": f"0x{CHARACTER_CUSTOM_MOVEMEM_COMMAND:08X}",
            "custom_movemem_relocator": "func_1503D438",
            "custom_movemem_scanner": "func_1503D368",
            "custom_movemem_pair_index": 4,
            "custom_movemem_pointer_alignment": 32,
            "custom_movemem_semantics": (
                "signed-s8-x-y-normal-components-indexed-by-vertex-cache-slot"
            ),
            "custom_vertex_normal_z": "signed-low-byte-of-vertex-flag",
            "custom_vertex_normal_emulator_reference": (
                "GLideN64/src/uCodes/F3DEX2CBFD.cpp-and-src/gSP.cpp"
            ),
            "character_material_colors": CHARACTER_RUNTIME_COLOR_STATE,
            "procedural_joint_lookup": "func_1503DA3C",
            "procedural_joint_caller": "func_15033FE0",
            "procedural_joint_override_builder": "func_15034860",
            "procedural_joint_table_pair_index": 6,
            "procedural_joint_sentinel": "0xFF",
        },
    }


def parse_geometry_for_bank(data: bytes, bank_index: int) -> ModelGeometry:
    if bank_index == 0x01:
        return parse_character_model_geometry(data)[0]
    return parse_model_geometry(data)


def validation_color(index: int) -> tuple[int, int, int, int]:
    """Return a stable, high-contrast unlit colour for one rigid/material run."""

    hue = (index * 0.6180339887498949) % 1.0
    red, green, blue = hsv_to_rgb(hue, 0.68, 0.95)
    return (round(red * 255), round(green * 255), round(blue * 255), 255)


def validation_face_records(
    geometry: ModelGeometry,
    character_joints: tuple[dict[str, Any], ...] | None = None,
    matrix_rows_by_index: dict[int, list[list[float]]] | None = None,
) -> list[dict[str, Any]]:
    """Expand faces into bind-space positions and validation colour groups."""

    joint_by_matrix = {
        joint["matrix_index"]: joint for joint in character_joints or ()
    }
    global_bind_pivots = (
        character_global_bind_pivots(character_joints)
        if character_joints
        else {}
    )
    records = []
    for run_index, run in enumerate(geometry.material_runs):
        matrix_index = run.matrix_index if run.matrix_index is not None else 0
        pivot = (0.0, 0.0, 0.0)
        if character_joints:
            joint = joint_by_matrix.get(matrix_index)
            if joint is None:
                pivot = (math.nan, math.nan, math.nan)
            else:
                pivot = global_bind_pivots[matrix_index]
        group_index = matrix_index if character_joints else run_index
        for face_offset, face in enumerate(
            geometry.faces[run.first_face : run.first_face + run.face_count]
        ):
            if matrix_rows_by_index is None:
                positions = tuple(
                    (
                        float(geometry.vertices[index].x) + pivot[0],
                        float(geometry.vertices[index].y) + pivot[1],
                        float(geometry.vertices[index].z) + pivot[2],
                    )
                    for index in face
                )
            else:
                rows = matrix_rows_by_index.get(matrix_index)
                if rows is None:
                    positions = ((math.nan, math.nan, math.nan),) * 3
                else:
                    positions = tuple(
                        tuple(
                            float(geometry.vertices[index].x) * rows[0][axis]
                            + float(geometry.vertices[index].y) * rows[1][axis]
                            + float(geometry.vertices[index].z) * rows[2][axis]
                            + rows[3][axis]
                            for axis in range(3)
                        )
                        for index in face
                    )
            records.append(
                {
                    "face_index": run.first_face + face_offset,
                    "run_index": run_index,
                    "matrix_index": matrix_index if character_joints else None,
                    "source_indices": face,
                    "component_keys": positions,
                    "positions": positions,
                    "color": validation_color(group_index),
                }
            )
    if len(records) != len(geometry.faces):
        raise ValueError("validation faces do not cover the decoded geometry")
    return records


def _triangle_cross(
    positions: tuple[
        tuple[float, float, float],
        tuple[float, float, float],
        tuple[float, float, float],
    ],
) -> tuple[float, float, float]:
    left, middle, right = positions
    first = tuple(middle[axis] - left[axis] for axis in range(3))
    second = tuple(right[axis] - left[axis] for axis in range(3))
    return (
        first[1] * second[2] - first[2] * second[1],
        first[2] * second[0] - first[0] * second[2],
        first[0] * second[1] - first[1] * second[0],
    )


def omit_zero_area_preview_faces(
    geometry: ModelGeometry,
) -> tuple[ModelGeometry, tuple[int, ...], tuple[int, ...]]:
    """Remove source-authentic no-op triangles from interchange previews only."""

    retained_faces = []
    retained_normals = []
    retained_offsets = []
    retained_opcodes = []
    retained_cache_indices = []
    omitted_faces = []
    omitted_by_run = []
    preview_runs = []
    has_face_cache_indices = len(geometry.face_cache_indices) == len(geometry.faces)
    for run in geometry.material_runs:
        first_face = len(retained_faces)
        omitted_count = 0
        for face_index in range(run.first_face, run.first_face + run.face_count):
            face = geometry.faces[face_index]
            positions = tuple(
                (
                    float(geometry.vertices[index].x),
                    float(geometry.vertices[index].y),
                    float(geometry.vertices[index].z),
                )
                for index in face
            )
            cross = _triangle_cross(positions)
            if sum(value * value for value in cross) == 0.0:
                omitted_faces.append(face_index)
                omitted_count += 1
                continue
            retained_faces.append(face)
            if geometry.face_normal_bytes:
                retained_normals.append(geometry.face_normal_bytes[face_index])
            if geometry.face_command_offsets:
                retained_offsets.append(geometry.face_command_offsets[face_index])
            if geometry.face_command_opcodes:
                retained_opcodes.append(geometry.face_command_opcodes[face_index])
            if has_face_cache_indices:
                retained_cache_indices.append(geometry.face_cache_indices[face_index])
        omitted_by_run.append(omitted_count)
        preview_runs.append(
            replace(
                run,
                first_face=first_face,
                face_count=len(retained_faces) - first_face,
            )
        )
    return (
        replace(
            geometry,
            faces=tuple(retained_faces),
            material_runs=tuple(preview_runs),
            face_normal_bytes=tuple(retained_normals),
            face_command_offsets=tuple(retained_offsets),
            face_command_opcodes=tuple(retained_opcodes),
            face_cache_indices=tuple(retained_cache_indices),
        ),
        tuple(omitted_faces),
        tuple(omitted_by_run),
    )


def zero_area_face_record(
    geometry: ModelGeometry, face_index: int
) -> dict[str, Any]:
    """Describe one source face that cannot cover a raster sample."""

    face = geometry.faces[face_index]
    positions = tuple(
        (
            float(geometry.vertices[index].x),
            float(geometry.vertices[index].y),
            float(geometry.vertices[index].z),
        )
        for index in face
    )
    if len(set(face)) < 3:
        kind = "repeated-vertex-index"
    elif len(set(positions)) < 3:
        kind = "duplicate-position"
    else:
        kind = "collinear-positions"
    return {
        "face_index": face_index,
        "source_indices": list(face),
        "kind": kind,
        "display_list_offset": (
            f"0x{geometry.face_command_offsets[face_index]:X}"
            if geometry.face_command_offsets
            else None
        ),
        "triangle_opcode": (
            f"0x{geometry.face_command_opcodes[face_index]:02X}"
            if geometry.face_command_opcodes
            else None
        ),
    }


def validate_model_geometry(
    geometry: ModelGeometry,
    character_joints: tuple[dict[str, Any], ...] | None = None,
) -> dict[str, Any]:
    """Return conservative structural findings without inferring model semantics."""

    faces = validation_face_records(geometry, character_joints)
    invalid_joint_assignments = []
    invalid_joint_hierarchy = []
    if character_joints:
        matrix_indices = [joint["matrix_index"] for joint in character_joints]
        matrix_set = set(matrix_indices)
        if len(matrix_indices) != len(matrix_set):
            invalid_joint_hierarchy.append("duplicate-matrix-index")
        for joint in character_joints:
            parent = joint["parent_matrix_index"]
            if parent >= 0 and parent not in matrix_set:
                invalid_joint_hierarchy.append(
                    f"joint-{joint['matrix_index']}-missing-parent-{parent}"
                )
            seen = set()
            cursor = joint
            while cursor["parent_matrix_index"] >= 0:
                matrix_index = cursor["matrix_index"]
                if matrix_index in seen:
                    invalid_joint_hierarchy.append(
                        f"joint-{joint['matrix_index']}-parent-cycle"
                    )
                    break
                seen.add(matrix_index)
                parent = cursor["parent_matrix_index"]
                if parent not in matrix_set:
                    break
                cursor = next(
                    candidate
                    for candidate in character_joints
                    if candidate["matrix_index"] == parent
                )
        invalid_joint_assignments = sorted(
            {
                face["matrix_index"]
                for face in faces
                if face["matrix_index"] not in matrix_set
            }
        )

    positions = [position for face in faces for position in face["positions"]]
    if not positions:
        positions = [
            (float(vertex.x), float(vertex.y), float(vertex.z))
            for vertex in geometry.vertices
        ]
    finite_positions = [
        position
        for position in positions
        if all(math.isfinite(value) for value in position)
    ]
    finite_bounds = len(finite_positions) == len(positions)
    if finite_positions:
        bounds_min = [min(position[axis] for position in finite_positions) for axis in range(3)]
        bounds_max = [max(position[axis] for position in finite_positions) for axis in range(3)]
    else:
        bounds_min = bounds_max = [0.0, 0.0, 0.0]
    bounds_extent = [bounds_max[axis] - bounds_min[axis] for axis in range(3)]
    bounds_diagonal = math.sqrt(sum(value * value for value in bounds_extent))

    zero_area_faces = []
    zero_area_kinds: dict[str, int] = {}
    zero_area_opcodes: dict[str, int] = {}
    inverted_source_normal_faces = []
    duplicate_faces = []
    seen_triangles: dict[tuple[tuple[float, float, float], ...], int] = {}
    for face in faces:
        cross = _triangle_cross(face["positions"])
        cross_length = math.sqrt(sum(value * value for value in cross))
        if not math.isfinite(cross_length) or cross_length == 0.0:
            zero_area_faces.append(face["face_index"])
            source_record = zero_area_face_record(geometry, face["face_index"])
            kind = source_record["kind"]
            zero_area_kinds[kind] = zero_area_kinds.get(kind, 0) + 1
            opcode = source_record["triangle_opcode"]
            if opcode is not None:
                zero_area_opcodes[opcode] = zero_area_opcodes.get(opcode, 0) + 1
        triangle_key = tuple(sorted(face["positions"]))
        if triangle_key in seen_triangles:
            duplicate_faces.append(face["face_index"])
        else:
            seen_triangles[triangle_key] = face["face_index"]
        if geometry.face_normal_bytes and cross_length:
            raw_normals = geometry.face_normal_bytes[face["face_index"]]
            usable = [
                normal
                for normal in raw_normals
                if normal is not None and normal != (0, 0, 0)
            ]
            if usable:
                average = tuple(
                    sum(normal[axis] for normal in usable) / len(usable)
                    for axis in range(3)
                )
                dot = sum(cross[axis] * average[axis] for axis in range(3))
                if dot < 0.0:
                    inverted_source_normal_faces.append(face["face_index"])

    parent: dict[tuple[float, float, float], tuple[float, float, float]] = {}

    def find(key: tuple[float, float, float]) -> tuple[float, float, float]:
        parent.setdefault(key, key)
        while parent[key] != key:
            parent[key] = parent[parent[key]]
            key = parent[key]
        return key

    def union(
        left: tuple[float, float, float], right: tuple[float, float, float]
    ) -> None:
        left_root, right_root = find(left), find(right)
        if left_root != right_root:
            parent[right_root] = left_root

    for face in faces:
        keys = face["component_keys"]
        union(keys[0], keys[1])
        union(keys[1], keys[2])
    component_face_counts: dict[tuple[float, float, float], int] = {}
    for face in faces:
        root = find(face["component_keys"][0])
        component_face_counts[root] = component_face_counts.get(root, 0) + 1
    component_sizes = sorted(component_face_counts.values(), reverse=True)

    rejection_reasons = []
    if not finite_bounds:
        rejection_reasons.append("non-finite-bounds")
    if invalid_joint_assignments or invalid_joint_hierarchy:
        rejection_reasons.append("invalid-joint-assignment-or-hierarchy")
    review_reasons = []
    if len(component_sizes) > 1:
        review_reasons.append("disconnected-components")
    if duplicate_faces:
        review_reasons.append("coincident-triangles")
    if zero_area_faces:
        review_reasons.append("source-zero-area-triangles-filtered-from-previews")
    if inverted_source_normal_faces:
        review_reasons.append("source-normal-winding-disagreement")
    status = "rejected" if rejection_reasons else "review" if review_reasons else "accepted"
    return {
        "status": status,
        "rejection_reasons": rejection_reasons,
        "review_reasons": review_reasons,
        "bounds": {
            "min": bounds_min,
            "max": bounds_max,
            "extent": bounds_extent,
            "diagonal": bounds_diagonal,
            "finite": finite_bounds,
        },
        "connected_component_count": len(component_sizes),
        "component_face_counts": component_sizes,
        "small_component_count": sum(size <= 2 for size in component_sizes),
        "zero_area_face_count": len(zero_area_faces),
        "zero_area_faces": zero_area_faces,
        "zero_area_kind_counts": dict(sorted(zero_area_kinds.items())),
        "zero_area_opcode_counts": dict(sorted(zero_area_opcodes.items())),
        "duplicate_face_count": len(duplicate_faces),
        "duplicate_faces": duplicate_faces,
        "inverted_source_normal_face_count": len(inverted_source_normal_faces),
        "inverted_source_normal_faces": inverted_source_normal_faces,
        "invalid_joint_assignments": invalid_joint_assignments,
        "invalid_joint_hierarchy": sorted(set(invalid_joint_hierarchy)),
    }


def render_validation_strip(
    geometry: ModelGeometry,
    character_joints: tuple[dict[str, Any], ...] | None = None,
    view_size: int = VALIDATION_ATLAS_VIEW_SIZE,
    matrix_rows_by_index: dict[int, list[list[float]]] | None = None,
) -> bytes:
    """Software-render three deterministic, unlit orthographic model views."""

    faces = validation_face_records(
        geometry, character_joints, matrix_rows_by_index
    )
    width = view_size * len(VALIDATION_ATLAS_VIEWS)
    pixels = bytearray((34, 37, 43, 255) * (width * view_size))
    projections = {
        "front": ((0, 2), 1),
        "side": ((1, 2), 0),
        "top": ((0, 1), 2),
    }
    for view_index, view in enumerate(VALIDATION_ATLAS_VIEWS):
        axes, depth_axis = projections[view]
        projected_faces = [
            tuple((position[axes[0]], -position[axes[1]], position[depth_axis]) for position in face["positions"])
            for face in faces
        ]
        all_points = [point for face in projected_faces for point in face]
        if not all_points or not all(
            math.isfinite(value) for point in all_points for value in point
        ):
            continue
        minimum = [min(point[axis] for point in all_points) for axis in range(2)]
        maximum = [max(point[axis] for point in all_points) for axis in range(2)]
        span = [maximum[axis] - minimum[axis] for axis in range(2)]
        scale = (view_size - 10) / max(max(span), 1.0)
        center = [(minimum[axis] + maximum[axis]) * 0.5 for axis in range(2)]
        depth = [-math.inf] * (view_size * view_size)
        for face, projected in zip(faces, projected_faces):
            points = tuple(
                (
                    (point[0] - center[0]) * scale + (view_size - 1) * 0.5,
                    (point[1] - center[1]) * scale + (view_size - 1) * 0.5,
                    point[2],
                )
                for point in projected
            )
            area = (
                (points[1][0] - points[0][0]) * (points[2][1] - points[0][1])
                - (points[1][1] - points[0][1]) * (points[2][0] - points[0][0])
            )
            if area == 0.0:
                continue
            min_x = max(0, math.floor(min(point[0] for point in points)))
            max_x = min(view_size - 1, math.ceil(max(point[0] for point in points)))
            min_y = max(0, math.floor(min(point[1] for point in points)))
            max_y = min(view_size - 1, math.ceil(max(point[1] for point in points)))
            for y in range(min_y, max_y + 1):
                for x in range(min_x, max_x + 1):
                    sample_x, sample_y = x + 0.5, y + 0.5
                    weights = (
                        ((points[1][0] - sample_x) * (points[2][1] - sample_y) - (points[1][1] - sample_y) * (points[2][0] - sample_x)) / area,
                        ((points[2][0] - sample_x) * (points[0][1] - sample_y) - (points[2][1] - sample_y) * (points[0][0] - sample_x)) / area,
                    )
                    third = 1.0 - weights[0] - weights[1]
                    if min(weights[0], weights[1], third) < -1e-9:
                        continue
                    sample_depth = sum(
                        weight * point[2]
                        for weight, point in zip((weights[0], weights[1], third), points)
                    )
                    local_offset = y * view_size + x
                    if sample_depth < depth[local_offset]:
                        continue
                    depth[local_offset] = sample_depth
                    pixel_offset = (
                        y * width + view_index * view_size + x
                    ) * 4
                    pixels[pixel_offset : pixel_offset + 4] = bytes(face["color"])
        if view_index:
            separator_x = view_index * view_size
            for y in range(view_size):
                pixel_offset = (y * width + separator_x) * 4
                pixels[pixel_offset : pixel_offset + 4] = bytes((80, 84, 94, 255))
    return encode_rgba_png(width, view_size, bytes(pixels))


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


def decode_other_mode(pair: tuple[int, int] | None) -> dict[str, Any] | None:
    """Decode the RDP fields that materially affect an interchange preview."""

    if pair is None:
        return None
    command, argument = pair
    if command >> 24 != 0xEF:
        raise ValueError("other-mode command does not use opcode 0xEF")
    mode_high = command & 0x00FFFFFF
    cycle_type = (mode_high >> 20) & 3
    texture_lod = (mode_high >> 16) & 1
    texture_filter = (mode_high >> 12) & 3
    texture_lut = (mode_high >> 14) & 3
    alpha_compare = argument & 3
    z_mode = (argument >> 10) & 3
    force_blend = bool(argument & 0x4000)
    coverage_times_alpha = bool(argument & 0x1000)
    if force_blend or z_mode == 2:
        alpha_mode = "BLEND"
    elif alpha_compare or coverage_times_alpha:
        alpha_mode = "MASK"
    else:
        alpha_mode = "OPAQUE"
    return {
        "mode_high": f"0x{mode_high:06X}",
        "mode_low": f"0x{argument:08X}",
        "cycle_type": ("one-cycle", "two-cycle", "copy", "fill")[cycle_type],
        "texture_lod": ("tile", "lod")[texture_lod],
        "texture_filter": {
            0: "point",
            2: "bilinear",
            3: "average",
        }.get(texture_filter, f"reserved-{texture_filter}"),
        "texture_lut": {
            0: "none",
            2: "rgba16",
            3: "ia16",
        }.get(texture_lut, f"reserved-{texture_lut}"),
        "alpha_compare": {
            0: "none",
            1: "threshold",
            3: "dither",
        }.get(alpha_compare, f"reserved-{alpha_compare}"),
        "z_mode": ("opaque", "interpenetrating", "translucent", "decal")[
            z_mode
        ],
        "force_blend": force_blend,
        "coverage_times_alpha": coverage_times_alpha,
        "gltf_alpha_mode": alpha_mode,
        "gltf_alpha_status": (
            "approximate-rdp-coverage-and-blender-state-retained-in-extras"
            if alpha_mode != "OPAQUE"
            else "direct-opaque"
        ),
        "gltf_sampler": {
            "magFilter": 9728 if texture_filter == 0 else 9729,
            "minFilter": 9984 if texture_filter == 0 else 9987,
        },
    }


def translate_runtime_material_state(state: dict[str, Any]) -> dict[str, Any]:
    """Classify the captured RDP state against glTF's base-colour product."""

    combine_pair = tuple(state["combine_mode"]) if state.get("combine_mode") else None
    other_pair = tuple(state["other_mode"]) if state.get("other_mode") else None
    combine = decode_combine_mode(combine_pair)
    other = decode_other_mode(other_pair)
    if combine is None:
        return {
            "status": "unsupported-missing-combine-mode",
            "baseColorFactor": None,
            "alphaMode": other["gltf_alpha_mode"] if other else None,
            "sampler": other["gltf_sampler"] if other else None,
        }
    cycle_index = 1 if other and other["cycle_type"] == "two-cycle" else 0
    cycle = combine["cycles"][cycle_index]
    primitive = (state.get("colours", {}).get("primitive") or {}).get("rgba")
    environment = (state.get("colours", {}).get("environment") or {}).get("rgba")
    color = cycle["color"]
    alpha = cycle["alpha"]
    color_product = color == ["TEXEL0", "ZERO", "SHADE", "ZERO"]
    if (
        color == ["TEXEL0", "ENVIRONMENT", "SHADE", "PRIMITIVE"]
        and primitive is not None
        and environment is not None
        and primitive[:3] == [0, 0, 0]
        and environment[:3] == [0, 0, 0]
    ):
        color_product = True
    alpha_product = alpha == ["TEXEL0", "ZERO", "SHADE", "ZERO"]
    needs_mipmap = "TEXEL1" in combine["inputs"] or "LOD_FRACTION" in combine[
        "inputs"
    ]
    lighting_enabled = bool(state.get("lighting_enabled"))
    light_state = state.get("lights")
    captured_lights = bool(
        isinstance(light_state, dict)
        and any(
            isinstance(slot, dict) and isinstance(slot.get("decoded"), dict)
            for slot in light_state.get("slots", [])
        )
    )
    if needs_mipmap:
        status = "unsupported-explicit-rdp-mipmap"
    elif color_product and alpha_product and lighting_enabled:
        status = (
            "requires-runtime-lighting-replay"
            if captured_lights
            else "requires-runtime-lighting"
        )
    elif color_product and alpha_product:
        status = "exact-texture-times-vertex-color"
    elif color_product:
        status = "rgb-only-alpha-combiner-unsupported"
    else:
        status = "unsupported-rdp-combiner"
    return {
        "status": status,
        "baseColorFactor": [1.0, 1.0, 1.0, 1.0] if color_product else None,
        "alphaMode": other["gltf_alpha_mode"] if other else None,
        "sampler": other["gltf_sampler"] if other else None,
        "lightingEnabled": lighting_enabled,
        "runtimeLightsCaptured": captured_lights,
        "combineCycle": cycle_index + 1,
        "combineFormula": combine,
        "otherMode": other,
    }


def runtime_lighting_context(
    draw: dict[str, Any], matrices: list[dict[str, Any]]
) -> dict[str, Any] | None:
    """Retain the active model-view input needed by CBFD directional lights."""

    matrix_index = draw.get("captured_matrix_index")
    if not isinstance(matrix_index, int) or not 0 <= matrix_index < len(matrices):
        return None
    matrix = matrices[matrix_index]
    if draw.get("matrix_sha256") != matrix.get("sha256"):
        raise ValueError("runtime draw matrix hash changed")
    rows = matrix.get("rows")
    if (
        not isinstance(rows, list)
        or len(rows) != 4
        or any(not isinstance(row, list) or len(row) != 4 for row in rows)
    ):
        raise ValueError("runtime draw matrix is not a 4x4 matrix")
    context = {
        "matrix_sha256": matrix["sha256"],
        "matrix_layout": matrix.get("layout"),
        "model_view_rows": rows,
        "matrix_translation": matrix.get("translation"),
        "normal_stream": None,
    }
    normal_base = draw.get("state", {}).get("normal_base")
    if isinstance(normal_base, dict) and isinstance(
        normal_base.get("normal_xy_s8"), list
    ):
        context["normal_stream"] = {
            "sha256": normal_base.get("sha256"),
            "layout": normal_base.get("layout"),
            "normal_xy_s8": normal_base["normal_xy_s8"],
        }
    context["lighting_context_hash"] = hashlib.sha256(
        json.dumps(context, sort_keys=True, separators=(",", ":")).encode("utf-8")
    ).hexdigest()
    return context


def replay_cbfd_vertex_lighting(
    vertex: ModelVertex,
    normal: tuple[int, int, int] | None,
    state: dict[str, Any],
    context: dict[str, Any] | None,
) -> tuple[float, float, float, float] | None:
    """Replay GLideN64's F3DEX2CBFD per-vertex lighting calculation.

    ``None`` means that a required captured input is absent. The result remains
    floating point because the RSP/RDP interpolates lit colours before the
    framebuffer quantizes them.
    """

    if not state.get("lighting_enabled"):
        return tuple(component / 255.0 for component in vertex.color)
    lights = state.get("lights")
    if not isinstance(lights, dict):
        return None
    num_lights = lights.get("num_lights")
    if not isinstance(num_lights, int) or not 1 <= num_lights < 12:
        return None
    slots = {
        slot.get("light_slot"): slot.get("decoded")
        for slot in lights.get("slots", [])
        if isinstance(slot, dict)
        and isinstance(slot.get("light_slot"), int)
        and isinstance(slot.get("decoded"), dict)
    }
    required_slots = set(range(max(0, num_lights - 1))) | {num_lights}
    if lights.get("advanced_lighting"):
        required_slots.add(num_lights - 1)
    if any(slot not in slots for slot in required_slots):
        return None

    # CBFD deliberately leaves vertices with a negative signed flag unlit.
    if vertex.flag & 0x8000:
        return tuple(component / 255.0 for component in vertex.color)

    modifiers = lights.get("coordinate_modifiers")
    if (
        not isinstance(modifiers, list)
        or len(modifiers) < 15
        or any(modifiers[index] is None for index in (8, 9, 10, 12, 13, 14))
    ):
        return None
    vertex_position = [
        (coordinate + float(modifiers[8 + axis]))
        * float(modifiers[12 + axis])
        for axis, coordinate in enumerate((vertex.x, vertex.y, vertex.z))
    ]

    ambient = slots[num_lights]
    colour = [component / 255.0 for component in ambient["colour"]]
    normal_vector: tuple[float, float, float] | None = None

    def source_normal() -> tuple[float, float, float] | None:
        if normal is None:
            return None
        # GLideN64's FIXED2FLOATCOLOR7 is exactly 1/127, and CBFD does not
        # normalize the source normal before taking light dot products.
        return tuple(component / 127.0 for component in normal)

    def transformed_direction(slot: dict[str, Any]) -> tuple[float, float, float] | None:
        if context is None:
            return None
        rows = context.get("model_view_rows")
        direction = slot.get("direction_normalized")
        if not isinstance(rows, list) or not isinstance(direction, list):
            return None
        result = tuple(
            sum(float(rows[axis][component]) * float(direction[component]) for component in range(3))
            for axis in range(3)
        )
        length = math.sqrt(sum(component * component for component in result))
        return tuple(component / length for component in result) if length else result

    advanced = bool(lights.get("advanced_lighting"))
    if advanced:
        normal_vector = source_normal()
        direction = transformed_direction(slots[num_lights - 1])
        if normal_vector is None or direction is None:
            return None
        intensity = min(1.0, sum(a * b for a, b in zip(normal_vector, direction)))
        if intensity > 0.0:
            for channel, component in enumerate(slots[num_lights - 1]["colour"]):
                colour[channel] += component / 255.0 * intensity

    point_directional = advanced and bool(
        int(state.get("geometry_mode") or 0) & 0x00400000
    )
    if point_directional and normal_vector is None:
        normal_vector = source_normal()
        if normal_vector is None:
            return None
    for light_index in range(num_lights - 2, -1, -1):
        light = slots[light_index]
        position = light.get("position_s16")
        if not isinstance(position, list) or len(position) < 3:
            return None
        delta = [
            vertex_position[axis] - float(position[axis]) for axis in range(3)
        ]
        length = 2.0 * sum(component * component for component in delta) / 65536.0
        attenuation = float(light.get("attenuation", 0.0))
        intensity = 1.0 if length == 0.0 and attenuation > 0.0 else min(
            1.0, attenuation / length if length else 0.0
        )
        if point_directional:
            direction = transformed_direction(light)
            if direction is None:
                return None
            intensity *= min(
                1.0,
                sum(a * b for a, b in zip(normal_vector or (), direction)),
            )
        if intensity > 0.0:
            for channel, component in enumerate(light["colour"]):
                colour[channel] += component / 255.0 * intensity

    colour = [min(1.0, component) for component in colour]
    return (
        vertex.color[0] / 255.0 * colour[0],
        vertex.color[1] / 255.0 * colour[1],
        vertex.color[2] / 255.0 * colour[2],
        vertex.color[3] / 255.0,
    )


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
    character_animation_clips: tuple[CharacterAnimationClip, ...] = (),
    output_stem: str | None = None,
    runtime_materials: dict[int, dict[str, Any]] | None = None,
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
    sampler_indices: dict[tuple[int, int, int, int], int] = {}
    textures = []
    texture_indices: dict[tuple[str, int, int, int, int], int] = {}
    materials = []
    primitives = []
    character_joint_by_matrix = {
        joint["matrix_index"]: joint for joint in character_joints or ()
    }
    character_global_pivots = (
        character_global_bind_pivots(character_joints)
        if character_joints
        else {}
    )

    def normalized(values: tuple[int | float, int | float, int | float]):
        length = math.sqrt(sum(float(value) ** 2 for value in values))
        if length == 0.0:
            return None
        return tuple(float(value) / length for value in values)

    def geometric_face_normal(face: tuple[int, int, int]):
        left, middle, right = (geometry.vertices[index] for index in face)
        first = (
            middle.x - left.x,
            middle.y - left.y,
            middle.z - left.z,
        )
        second = (
            right.x - left.x,
            right.y - left.y,
            right.z - left.z,
        )
        result = normalized(
            (
                first[1] * second[2] - first[2] * second[1],
                first[2] * second[0] - first[0] * second[2],
                first[0] * second[1] - first[1] * second[0],
            )
        )
        return result or (0.0, 0.0, 1.0)

    for run_index, run in enumerate(geometry.material_runs):
        if run.face_count == 0:
            continue
        runtime_material = (
            runtime_materials.get(run_index) if runtime_materials is not None else None
        )
        replay_choice = runtime_lighting_replay_choice(runtime_material)
        replay_normal_base = (
            replay_choice[1].get("normal_stream")
            if replay_choice is not None
            else None
        )
        replay_normal_xy = (
            replay_normal_base.get("normal_xy_s8")
            if isinstance(replay_normal_base, dict)
            else None
        )
        source_vertex_indices = []
        source_normals = []
        source_normal_bytes: list[tuple[int, int, int] | None] = []
        local_vertex_indices = {}
        local_faces = []
        for face_offset, face in enumerate(
            geometry.faces[run.first_face : run.first_face + run.face_count]
        ):
            face_index = run.first_face + face_offset
            raw_normals = (
                geometry.face_normal_bytes[face_index]
                if geometry.face_normal_bytes
                else None
            )
            has_normal_evidence = bool(raw_normals) or isinstance(
                replay_normal_xy, list
            )
            fallback_normal = (
                geometric_face_normal(face) if has_normal_evidence else None
            )
            local_face = []
            for corner, source_index in enumerate(face):
                raw_normal = raw_normals[corner] if raw_normals else None
                if (
                    raw_normal is None
                    and isinstance(replay_normal_xy, list)
                    and geometry.face_cache_indices
                ):
                    cache_index = geometry.face_cache_indices[face_index][corner]
                    if cache_index < len(replay_normal_xy):
                        z = geometry.vertices[source_index].flag & 0xFF
                        raw_normal = (
                            int(replay_normal_xy[cache_index][0]),
                            int(replay_normal_xy[cache_index][1]),
                            z - 0x100 if z >= 0x80 else z,
                )
                decoded_source_normal = normalized(raw_normal) if raw_normal else None
                source_normal = decoded_source_normal
                if has_normal_evidence and decoded_source_normal is None:
                    source_normal = fallback_normal
                vertex_key = (
                    (
                        source_index,
                        raw_normal
                        if decoded_source_normal is not None
                        else ("fallback", face_index),
                    )
                    if has_normal_evidence
                    else source_index
                )
                if vertex_key not in local_vertex_indices:
                    local_vertex_indices[vertex_key] = len(source_vertex_indices)
                    source_vertex_indices.append(source_index)
                    source_normal_bytes.append(raw_normal)
                    if source_normal is not None:
                        source_normals.append(source_normal)
                local_face.append(local_vertex_indices[vertex_key])
            local_faces.append(tuple(local_face))
        vertices = [geometry.vertices[index] for index in source_vertex_indices]
        if character_joints:
            joint_index = run.matrix_index if run.matrix_index is not None else 0
            try:
                bind_pivot = character_global_pivots[joint_index]
            except KeyError as error:
                raise ValueError(
                    f"character material run references absent joint {joint_index}"
                ) from error
            positions = [
                (
                    float(vertex.x) + float(bind_pivot[0]),
                    float(vertex.y) + float(bind_pivot[1]),
                    float(vertex.z) + float(bind_pivot[2]),
                )
                for vertex in vertices
            ]
        else:
            positions = [
                (float(vertex.x), float(vertex.y), float(vertex.z))
                for vertex in vertices
            ]
        position_accessor = append_accessor(
            b"".join(
                struct.pack("<3f", *position) for position in positions
            ),
            5126,
            "VEC3",
            len(vertices),
            34962,
            [
                min(position[axis] for position in positions)
                for axis in range(3)
            ],
            [
                max(position[axis] for position in positions)
                for axis in range(3)
            ],
        )
        replayed_colors = (
            [
                replay_cbfd_vertex_lighting(
                    vertex,
                    source_normal_bytes[index],
                    replay_choice[0]["state"],
                    replay_choice[1],
                )
                for index, vertex in enumerate(vertices)
            ]
            if replay_choice is not None
            else []
        )
        lighting_replayed = bool(replayed_colors) and all(
            color is not None for color in replayed_colors
        )
        if lighting_replayed:
            color_accessor = append_accessor(
                b"".join(
                    struct.pack("<4f", *color)
                    for color in replayed_colors
                    if color is not None
                ),
                5126,
                "VEC4",
                len(vertices),
                34962,
            )
        else:
            color_accessor = append_accessor(
                b"".join(bytes(vertex.color) for vertex in vertices),
                5121,
                "VEC4",
                len(vertices),
                34962,
                normalized=True,
            )
        attributes = {"POSITION": position_accessor, "COLOR_0": color_accessor}
        if source_normals:
            if len(source_normals) != len(vertices):
                raise ValueError("character normal count does not match glTF vertices")
            attributes["NORMAL"] = append_accessor(
                b"".join(
                    struct.pack("<3f", *normal) for normal in source_normals
                ),
                5126,
                "VEC3",
                len(source_normals),
                34962,
            )
        if character_joints:
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
        runtime_consensus = runtime_material_consensus(runtime_material)
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
        if character_joints:
            material["extras"]["characterColorState"] = (
                CHARACTER_RUNTIME_COLOR_STATE
            )
        if runtime_material is not None:
            material["extras"]["runtimeMaterial"] = {
                "modelSha1": runtime_material["model_sha1"],
                "sourceFirstFace": runtime_material["source_first_face"],
                "sourceFaceCount": runtime_material["source_face_count"],
                "variantCount": runtime_material["variant_count"],
                "observationCount": runtime_material["observation_count"],
                "consensus": runtime_consensus,
                "variants": [
                    {
                        key: value
                        for key, value in variant.items()
                        if key != "evidence"
                    }
                    for variant in runtime_material["variants"]
                ],
            }
            material["extras"]["runtimeMaterial"]["lightingReplay"] = {
                "status": (
                    "gliden64-equivalent-observed-draw"
                    if lighting_replayed
                    else "not-baked-ambiguous-or-incomplete"
                ),
                "contextHash": (
                    replay_choice[1]["lighting_context_hash"]
                    if replay_choice is not None
                    else None
                ),
            }
            if runtime_consensus and runtime_consensus["baseColorFactor"] is not None:
                material["pbrMetallicRoughness"]["baseColorFactor"] = (
                    runtime_consensus["baseColorFactor"]
                )
        texture_file = texture_files.get(name) if texture_files is not None else None
        if texture_file is not None:
            address_mode = texture_address_mode(run)
            if address_mode is None:
                raise ValueError("linked texture material lacks render-tile state")
            wrap_s = address_mode["gltf"]["wrapS"]
            wrap_t = address_mode["gltf"]["wrapT"]
            sampler_state = (
                runtime_consensus["sampler"]
                if runtime_consensus and runtime_consensus["sampler"] is not None
                else {"magFilter": 9729, "minFilter": 9987}
            )
            mag_filter = sampler_state["magFilter"]
            min_filter = sampler_state["minFilter"]
            texture_key = (
                texture_file,
                wrap_s,
                wrap_t,
                mag_filter,
                min_filter,
            )
            texture_index = texture_indices.get(texture_key)
            if texture_index is None:
                image_index = image_indices.get(texture_file)
                if image_index is None:
                    image_index = len(images)
                    images.append({"uri": texture_file})
                    image_indices[texture_file] = image_index
                sampler_key = (wrap_s, wrap_t, mag_filter, min_filter)
                sampler_index = sampler_indices.get(sampler_key)
                if sampler_index is None:
                    sampler_index = len(samplers)
                    samplers.append(
                        {
                            "magFilter": mag_filter,
                            "minFilter": min_filter,
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
        if runtime_consensus and runtime_consensus["alphaMode"] is not None:
            material["alphaMode"] = runtime_consensus["alphaMode"]
            if material["alphaMode"] == "MASK":
                material["alphaCutoff"] = 0.5
            else:
                material.pop("alphaCutoff", None)
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
    stem = output_stem or f"{bundle_index:04d}-{segment_index:02d}"
    animations = []
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
        joint_by_matrix = {
            joint["matrix_index"]: joint for joint in ordered_joints
        }
        local_bind_translations = {}
        for joint in ordered_joints:
            matrix_index = joint["matrix_index"]
            local_bind_translations[matrix_index] = [
                float(value) for value in joint["bind_pivot_f32"]
            ]
        nodes = []
        node_by_matrix = {}
        for joint in ordered_joints:
            matrix_index = joint["matrix_index"]
            node_by_matrix[matrix_index] = len(nodes)
            node: dict[str, Any] = {
                "name": f"joint_{matrix_index:02d}",
                "translation": local_bind_translations[matrix_index],
                "extras": {
                    "recordIndex": joint["record_index"],
                    "matrixIndex": matrix_index,
                    "animationIndex": joint["animation_index"],
                    "parentMatrixIndex": joint["parent_matrix_index"],
                    "bindPivot": joint["bind_pivot_f32"],
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
        inverse_bind_accessor = append_accessor(
            b"".join(
                struct.pack(
                    "<16f",
                    1.0,
                    0.0,
                    0.0,
                    0.0,
                    0.0,
                    1.0,
                    0.0,
                    0.0,
                    0.0,
                    0.0,
                    1.0,
                    0.0,
                    -character_global_pivots[joint["matrix_index"]][0],
                    -character_global_pivots[joint["matrix_index"]][1],
                    -character_global_pivots[joint["matrix_index"]][2],
                    1.0,
                )
                for joint in ordered_joints
            ),
            5126,
            "MAT4",
            len(ordered_joints),
            None,
        )
        skins = [
            {
                "name": f"bank{bank_index:02x}_{stem}_rig",
                "joints": [
                    node_by_matrix[joint["matrix_index"]] for joint in ordered_joints
                ],
                "skeleton": scene_nodes[0],
                "inverseBindMatrices": inverse_bind_accessor,
                "extras": {
                    "bindSemantics": (
                        "parent-relative-translations-with-accumulated-global-pivots"
                    )
                },
            }
        ]
        for clip in character_animation_clips:
            if not clip.frames:
                continue
            times = list(character_animation_preview_times(clip))
            time_accessor = append_accessor(
                b"".join(struct.pack("<f", value) for value in times),
                5126,
                "SCALAR",
                len(times),
                None,
                [times[0]],
                [times[-1]],
            )
            samplers_for_clip = []
            channels_for_clip = []
            for joint in ordered_joints:
                animation_index = joint["animation_index"]
                node_index = node_by_matrix[joint["matrix_index"]]
                rotations = []
                previous = None
                for frame in clip.frames:
                    rotation = frame.rotations[animation_index]
                    if previous is not None and sum(
                        left * right for left, right in zip(previous, rotation)
                    ) < 0.0:
                        rotation = tuple(-value for value in rotation)
                    rotations.append(rotation)
                    previous = rotation
                rotation_accessor = append_accessor(
                    b"".join(struct.pack("<4f", *value) for value in rotations),
                    5126,
                    "VEC4",
                    len(rotations),
                    None,
                )
                rotation_sampler = len(samplers_for_clip)
                samplers_for_clip.append(
                    {
                        "input": time_accessor,
                        "output": rotation_accessor,
                        "interpolation": "LINEAR",
                    }
                )
                channels_for_clip.append(
                    {
                        "sampler": rotation_sampler,
                        "target": {"node": node_index, "path": "rotation"},
                    }
                )

                scale_indices = range(animation_index * 3, animation_index * 3 + 3)
                has_scale_channel = any(
                    clip.frames[0].scale_channels[index] is not None
                    for index in scale_indices
                )
                if has_scale_channel:
                    scales = [
                        tuple(
                            1.0
                            if frame.scale_channels[index] in (None, 0)
                            else float(frame.scale_channels[index]) / 16384.0
                            for index in scale_indices
                        )
                        for frame in clip.frames
                    ]
                    scale_accessor = append_accessor(
                        b"".join(struct.pack("<3f", *value) for value in scales),
                        5126,
                        "VEC3",
                        len(scales),
                        None,
                    )
                    scale_sampler = len(samplers_for_clip)
                    samplers_for_clip.append(
                        {
                            "input": time_accessor,
                            "output": scale_accessor,
                            "interpolation": "LINEAR",
                        }
                    )
                    channels_for_clip.append(
                        {
                            "sampler": scale_sampler,
                            "target": {"node": node_index, "path": "scale"},
                        }
                    )

                deltas = [
                    frame.joint_translation_deltas[animation_index]
                    for frame in clip.frames
                ]
                has_joint_translation = deltas[0] is not None
                if any((delta is not None) != has_joint_translation for delta in deltas):
                    raise ValueError("character translation mask changes by frame")
                parent = joint["parent_matrix_index"]
                is_root = parent < 0
                has_root_translation = is_root and any(
                    any(value != 0 for value in frame.root_translation)
                    for frame in clip.frames
                )
                if (
                    not has_joint_translation
                    and not has_root_translation
                ):
                    continue
                base = local_bind_translations[joint["matrix_index"]]
                translations = [
                    character_local_animation_translation(
                        frame,
                        joint,
                        base,
                    )
                    for frame in clip.frames
                ]
                translation_accessor = append_accessor(
                    b"".join(
                        struct.pack("<3f", *value) for value in translations
                    ),
                    5126,
                    "VEC3",
                    len(translations),
                    None,
                )
                translation_sampler = len(samplers_for_clip)
                samplers_for_clip.append(
                    {
                        "input": time_accessor,
                        "output": translation_accessor,
                        "interpolation": "LINEAR",
                    }
                )
                channels_for_clip.append(
                    {
                        "sampler": translation_sampler,
                        "target": {"node": node_index, "path": "translation"},
                    }
                )
            animations.append(
                {
                    "name": (
                        f"bank02_entry_{bundle_index:04d}_"
                        f"pair_{clip.pair_index:04d}"
                        + (
                            f"_anim_{clip.logical_animation_indices[0]:04d}"
                            if clip.logical_animation_indices
                            else ""
                        )
                    ),
                    "samplers": samplers_for_clip,
                    "channels": channels_for_clip,
                    "extras": {
                        "sourceBank": 2,
                        "sourceEntry": bundle_index,
                        "sourcePair": clip.pair_index,
                        "logicalAnimationIndices": list(
                            clip.logical_animation_indices
                        ),
                        "sourceFrameCount": len(clip.frames),
                        "sourceFrameStride": clip.frame_byte_size,
                        "sourceBitstreamPadding": clip.bitstream_padding_size,
                        "descriptorRuntimeZeroFill": (
                            clip.descriptor_runtime_zero_fill_size
                        ),
                        "sourceCompanionTrailingSize": (
                            clip.companion_trailing_size
                        ),
                        "sourceCompanionTrailingSha1": (
                            clip.companion_trailing_sha1
                        ),
                        "sourceDurationTicks": clip.duration_ticks,
                        "sourceKeyframeStep": clip.keyframe_step,
                        "sourceDurationStatus": clip.duration_status,
                        "runtimeFramesPerSecond": ANIMATION_RUNTIME_FPS,
                        "timingStatus": "runtime-animation-clock-proven-30-hz",
                        "rootTranslationStatus": (
                            "applied-to-root-node-runtime-scale-one-over-1024"
                        ),
                        "maskedJointTranslationStatus": (
                            "local-joint-translation-deltas-at-one-over-16"
                        ),
                        "scaleChannelStatus": (
                            "runtime-proven-per-axis-zero-means-unit-otherwise-"
                            "unsigned-value-over-16384"
                        ),
                    },
                }
            )
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
            "bindPivotStatus": (
                "runtime-proven-parent-relative-translations-with-accumulated-"
                "global-pivots-and-explicit-"
                "inverse-bind-matrices"
            ),
            "characterVertexSpace": (
                "joint-local-source-positions-baked-through-accumulated-global-pivots"
            ),
            "characterAuxiliaryData": (
                "emulator-validated-signed-xy-normal-stream-vertex-flag-signed-z"
            ),
            "characterNormalStatus": (
                "normalized-source-with-geometric-fallback-for-zero-or-"
                "unavailable-preview-corners"
            ),
            "characterColorState": CHARACTER_RUNTIME_COLOR_STATE,
            "previewPose": character_pose_source
            or "neutral-bind-pose-no-semantic-action-selected",
            "coordinateConversion": "none-native-axes",
            "animationStatus": (
                "runtime-proven-rotation-root-and-masked-joint-translation-channels"
                if animations
                else "no-compatible-nonempty-bank-02-clips"
            ),
        }
    if animations:
        document["animations"] = animations
    if images:
        document["samplers"] = samplers
        document["images"] = images
        document["textures"] = textures
    return (
        (json.dumps(document, indent=2) + "\n").encode("utf-8"),
        bytes(binary),
    )


def bank_04_collision_surface_words(
    segment: ModelSegment, geometry: ModelGeometry
) -> tuple[int, ...]:
    """Decode the one-per-face surface words consumed after func_150039BC."""

    region = geometry.tertiary_region
    if segment.index != 0 or region is None:
        raise ValueError("bank-04 collision metadata requires primary segment zero")
    if region.size != 8 + len(geometry.faces) * 4:
        raise ValueError("bank-04 collision metadata does not cover every face")
    _, header_word_1 = struct.unpack_from(">II", segment.data, region.offset)
    if header_word_1 != 5:
        raise ValueError("bank-04 collision metadata has an unknown table header")
    return struct.unpack_from(
        f">{len(geometry.faces)}I", segment.data, region.offset + 8
    )


def encode_collision_triangle_offsets(geometry: ModelGeometry) -> bytes:
    """Encode runtime triangle-pointer records as relocatable model byte offsets."""

    return b"".join(
        struct.pack(">III", *(0x28 + vertex_index * 16 for vertex_index in face))
        for face in geometry.faces
    )


def collision_surface_color(surface_word: int) -> tuple[float, float, float, float]:
    """Return a stable high-contrast preview colour for one exact surface word."""

    mixed = (surface_word * 0x9E3779B1) & 0xFFFFFFFF
    hue = mixed / 0x100000000
    red, green, blue = hsv_to_rgb(hue, 0.72, 0.95)
    return (red, green, blue, 1.0)


def encode_collision_gltf(
    bundle_index: int,
    geometry: ModelGeometry,
    surface_words: tuple[int, ...] | None,
    segment_index: int = 0,
    bank_index: int = 0x04,
) -> tuple[bytes, bytes, tuple[int, ...]]:
    """Export one bank-04 collision mesh, grouped by surface word when present."""

    if surface_words is not None and len(surface_words) != len(geometry.faces):
        raise ValueError("collision surface count does not match decoded faces")
    binary = bytearray()
    buffer_views = []
    accessors = []
    face_surface_words: tuple[int | None, ...] = (
        surface_words
        if surface_words is not None
        else tuple(None for _ in geometry.faces)
    )
    faces_by_surface: dict[
        int | None, list[tuple[int, tuple[int, int, int]]]
    ] = {}
    omitted_faces = []
    for face_index, (face, surface_word) in enumerate(
        zip(geometry.faces, face_surface_words)
    ):
        positions_for_face = tuple(
            (
                float(geometry.vertices[index].x),
                float(geometry.vertices[index].y),
                float(geometry.vertices[index].z),
            )
            for index in face
        )
        cross = _triangle_cross(positions_for_face)
        if sum(value * value for value in cross) == 0.0:
            omitted_faces.append(face_index)
            continue
        faces_by_surface.setdefault(surface_word, []).append((face_index, face))

    materials = []
    primitives = []
    for surface_word, face_records in sorted(
        faces_by_surface.items(), key=lambda item: -1 if item[0] is None else item[0]
    ):
        expanded_positions = [
            (
                float(geometry.vertices[index].x),
                float(geometry.vertices[index].y),
                float(geometry.vertices[index].z),
            )
            for _, face in face_records
            for index in face
        ]
        while len(binary) % 4:
            binary.append(0)
        position_byte_offset = len(binary)
        position_data = b"".join(
            struct.pack("<3f", *position) for position in expanded_positions
        )
        binary.extend(position_data)
        position_buffer_view_index = len(buffer_views)
        buffer_views.append(
            {
                "buffer": 0,
                "byteOffset": position_byte_offset,
                "byteLength": len(position_data),
                "target": 34962,
            }
        )
        position_accessor_index = len(accessors)
        accessors.append(
            {
                "bufferView": position_buffer_view_index,
                "componentType": 5126,
                "count": len(expanded_positions),
                "type": "VEC3",
                "min": [
                    min(position[axis] for position in expanded_positions)
                    for axis in range(3)
                ],
                "max": [
                    max(position[axis] for position in expanded_positions)
                    for axis in range(3)
                ],
            }
        )
        while len(binary) % 4:
            binary.append(0)
        byte_offset = len(binary)
        indices = list(range(len(expanded_positions)))
        index_data = b"".join(struct.pack("<I", index) for index in indices)
        binary.extend(index_data)
        buffer_view_index = len(buffer_views)
        buffer_views.append(
            {
                "buffer": 0,
                "byteOffset": byte_offset,
                "byteLength": len(index_data),
                "target": 34963,
            }
        )
        accessor_index = len(accessors)
        accessors.append(
            {
                "bufferView": buffer_view_index,
                "componentType": 5125,
                "count": len(indices),
                "type": "SCALAR",
                "min": [min(indices)],
                "max": [max(indices)],
            }
        )
        material_index = len(materials)
        materials.append(
            {
                "name": (
                    f"surface_0x{surface_word:08X}"
                    if surface_word is not None
                    else "surface_unclassified"
                ),
                "doubleSided": True,
                "pbrMetallicRoughness": {
                    "baseColorFactor": list(
                        collision_surface_color(surface_word)
                        if surface_word is not None
                        else (0.65, 0.72, 0.8, 1.0)
                    ),
                    "metallicFactor": 0.0,
                    "roughnessFactor": 1.0,
                },
                "extensions": {"KHR_materials_unlit": {}},
                "extras": (
                    {
                        "surfaceWord": f"0x{surface_word:08X}",
                        "semanticStatus": "exact-value-meaning-unresolved",
                    }
                    if surface_word is not None
                    else {"surfaceWordStatus": "no-associated-primary-table"}
                ),
            }
        )
        primitives.append(
            {
                "attributes": {"POSITION": position_accessor_index},
                "indices": accessor_index,
                "material": material_index,
                "mode": 4,
                "extras": {
                    **(
                        {"surfaceWord": f"0x{surface_word:08X}"}
                        if surface_word is not None
                        else {"surfaceWordStatus": "no-associated-primary-table"}
                    ),
                    "sourceFaceIndices": [index for index, _ in face_records],
                },
            }
        )

    stem = f"{bundle_index:04d}-{segment_index:02d}-collision"
    document = {
        "asset": {"version": "2.0", "generator": "conker model-assets collision"},
        "extensionsUsed": ["KHR_materials_unlit"],
        "scene": 0,
        "scenes": [{"nodes": [0]}],
        "nodes": [{"mesh": 0, "name": f"bank{bank_index:02x}_{stem}"}],
        "meshes": [
            {"name": f"bank{bank_index:02x}_{stem}", "primitives": primitives}
        ],
        "materials": materials,
        "buffers": [{"uri": f"{stem}.bin", "byteLength": len(binary)}],
        "bufferViews": buffer_views,
        "accessors": accessors,
        "extras": {
            "sourceBank": bank_index,
            "sourceEntry": bundle_index,
            "sourceSegment": segment_index,
            "triangleRecordShape": "three-runtime-pointers-encoded-separately-as-model-relative-offsets",
            "surfaceRecordShape": (
                "one-big-endian-u32-per-source-face"
                if surface_words is not None
                else None
            ),
            "surfaceSemanticStatus": (
                "exact-values-preserved-meanings-unresolved"
                if surface_words is not None
                else "no-associated-primary-table"
            ),
            "zeroAreaPreviewPolicy": "retained-in-records-omitted-from-gltf",
            "duplicateFacePreviewPolicy": (
                "expanded-to-unique-preview-vertices-so-importers-preserve-every-face"
            ),
        },
    }
    return (
        (json.dumps(document, indent=2) + "\n").encode("utf-8"),
        bytes(binary),
        tuple(omitted_faces),
    )


def encode_placement_scene_gltf(
    scene_index: int,
    placements: list[dict[str, Any]],
    model_gltfs: dict[int, tuple[dict[str, Any], bytes]],
    *,
    placement_bank: int = 0x0C,
    model_bank: int = 0x03,
    model_index_field: str = "model_index",
) -> tuple[bytes, bytes]:
    """Combine one proven placement table with its referenced model glTFs."""

    binary = bytearray()
    buffer_views: list[dict[str, Any]] = []
    accessors: list[dict[str, Any]] = []
    images: list[dict[str, Any]] = []
    samplers: list[dict[str, Any]] = []
    textures: list[dict[str, Any]] = []
    materials: list[dict[str, Any]] = []
    meshes: list[dict[str, Any]] = []
    mesh_indices: dict[int, int] = {}
    extensions_used = set()

    for model_index in dict.fromkeys(
        record[model_index_field] for record in placements
    ):
        if model_index is None or model_index not in model_gltfs:
            raise ValueError(
                f"bank-{placement_bank:02X} scene {scene_index} references absent "
                f"bank-{model_bank:02X} model {model_index}"
            )
        source, source_binary = model_gltfs[model_index]
        extensions_used.update(source.get("extensionsUsed", []))
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
            "mesh": mesh_indices[record[model_index_field]],
            "name": (
                f"scene_{scene_index:02d}_object_{record['index']:03d}_"
                f"model_{record[model_index_field]:04d}"
            ),
            "matrix": placement_transform_matrix(record),
            "extras": {
                "placementRecord": record["index"],
                "modelIndex": record[model_index_field],
                "dispatchKind": record.get("dispatch_kind"),
                "recordSha1": record["sha1"],
            },
        }
        for record in placements
    ]
    stem = f"scene-{scene_index:02d}"
    document: dict[str, Any] = {
        "asset": {
            "version": "2.0",
            "generator": (
                f"conker model-assets bank-{placement_bank:02X} scene assembler"
            ),
        },
        "scene": 0,
        "scenes": [
            {
                "name": f"bank{placement_bank:02x}_scene_{scene_index:02d}",
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
            "placementBank": placement_bank,
            "modelBank": model_bank,
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
    if extensions_used:
        document["extensionsUsed"] = sorted(extensions_used)
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


def load_flat_asset_payloads(
    profile: str, rom_argument: Path | None, normalized_sha1: str
) -> dict[int, bytes]:
    """Load the exact decoded flat payloads referenced by character display lists."""

    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, _ = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest != normalized_sha1 or digest not in layout["normalized_sha1"]:
        raise ValueError("character texture payloads are from a different ROM")
    start, end = layout["flat_assets_start"], layout["flat_assets_end"]
    return {
        entry.index: entry.data
        for entry in iter_flat_rzip_entries(normalized[start:end])
    }


def character_runtime_preview_texture(
    run: ModelMaterialRun, payload: bytes
) -> tuple[PreviewTexture | None, str]:
    """Compose the CI image and TLUT bytes selected by ``func_1510CE60``.

    Character display lists load a flat payload into TMEM through an RGBA16
    transfer tile, then reinterpret the selected TMEM span as CI4/CI8. The
    render-time callers pass the parser's non-null rewrite table. At
    ``func_1510CE60+0x16C`` that path places every nonzero-mode reference at
    payload end minus 0x200; mode one loads all 256 CI8 entries while mode two
    loads the first 16 entries there as a CI4 TLUT. This function mirrors that
    pointer selection without claiming that the resulting PNG is a reversible
    representation of the flat asset.
    """

    state = texture_coordinate_state(run)
    if (
        state is None
        or state["format_evidence"] != "character-same-index-tlut-load"
        or run.pixel is None
        or run.palette is None
        or run.render_tile is None
        or run.pixel.flat_index is None
    ):
        raise ValueError("material run is not a character same-index TLUT load")
    if run.pixel.load_command is None or run.palette.load_command is None:
        return None, "character-indexed-load-command-unresolved"

    pixel_load_command, pixel_load_argument = run.pixel.load_command
    palette_load_command, palette_load_argument = run.palette.load_command
    if pixel_load_command >> 24 != 0xF3 or palette_load_command >> 24 != 0xF0:
        return None, "character-indexed-load-command-unresolved"
    palette_entries = ((palette_load_argument >> 14) & 0x3FF) + 1
    expected_palette_entries = 16 if state["size"] == 0 else 256
    if palette_entries != expected_palette_entries:
        return None, "character-indexed-tlut-size-unresolved"

    transfer_size = (run.pixel.image_command >> 19) & 3
    transfer_bytes_per_texel = (1, 1, 2, 4)[transfer_size]
    transfer_size_bytes = (
        ((pixel_load_argument >> 12) & 0xFFF) + 1
    ) * transfer_bytes_per_texel
    render_tile_command, _ = run.render_tile
    tmem_word_offset = render_tile_command & 0x1FF
    pixel_byte_offset = tmem_word_offset * 8
    row_size = state["width"]
    if state["size"] == 0:
        row_size = (row_size + 1) // 2
    elif state["size"] != 1:
        return None, "character-indexed-format-unresolved"
    line_words = (render_tile_command >> 9) & 0x1FF
    row_stride = line_words * 8 if line_words else row_size
    if row_stride < row_size:
        return None, "character-indexed-row-stride-unresolved"
    pixel_storage_size = (state["height"] - 1) * row_stride + row_size
    if pixel_byte_offset + pixel_storage_size > transfer_size_bytes:
        return None, "character-indexed-tmem-span-unresolved"
    if pixel_byte_offset + pixel_storage_size > len(payload):
        return None, "character-indexed-payload-span-unresolved"

    palette_size = 0x20 if state["size"] == 0 else 0x200
    palette_byte_offset = len(payload) - 0x200
    if palette_byte_offset < 0:
        return None, "character-indexed-palette-pointer-unresolved"
    if pixel_byte_offset + pixel_storage_size > palette_byte_offset:
        # Some character payloads are smaller than the render tile's nominal
        # full-resolution CI image plus its trailing TLUT. Those layouts can
        # contain mip levels or another runtime-selected packing scheme. Do not
        # reinterpret any part of the proven palette as ordinary image indices.
        return None, "character-indexed-pixel-palette-overlap-unresolved"

    rows = []
    for row_index in range(state["height"]):
        row_start = pixel_byte_offset + row_index * row_stride
        row = payload[row_start : row_start + row_stride]
        if row_index & 1:
            row = bytes(row[index ^ 4] for index in range(row_stride))
        rows.append(row[:row_size])
    linear_pixels = b"".join(rows)

    palette = payload[palette_byte_offset : palette_byte_offset + palette_size]
    if not any(value & 1 for (value,) in struct.iter_unpack(">H", palette)):
        # A zero-alpha TLUT can still contribute through Conker's two-cycle
        # primitive/environment combiner, but glTF's texture-times-vertex-color
        # material would make the surface disappear. Leave it unbound until the
        # runtime color tables are represented by the preview exporter.
        return None, "character-indexed-combiner-preview-unresolved"

    if state["size"] == 0:
        if run.palette.mode != 2:
            return None, "character-indexed-palette-pointer-unresolved"
        png_data = encode_indexed_png(
            linear_pixels + palette,
            "linear",
            state["width"],
            state["height"],
        )
    else:
        if run.palette.mode != 1:
            return None, "character-indexed-palette-pointer-unresolved"
        png_data = encode_ci8_png(
            linear_pixels + palette,
            "linear",
            state["width"],
            state["height"],
        )
    return (
        PreviewTexture(
            family="us-character-runtime-composed",
            source=None,
            flat_index=run.pixel.flat_index,
            format=state["format"],
            size=state["size"],
            width=state["width"],
            height=state["height"],
            sha1=hashlib.sha1(png_data).hexdigest(),
            png_data=png_data,
            pixel_byte_offset=pixel_byte_offset,
            palette_byte_offset=palette_byte_offset,
        ),
        "runtime-composed-character-texture",
    )


def direct_runtime_ci8_preview_texture(
    run: ModelMaterialRun, payload: bytes
) -> tuple[PreviewTexture | None, str]:
    """Compose a direct CI8 image for a proven non-null parser consumer.

    The ordinary model display lists load the CI8 indices through an RGBA16
    transfer image and select the same flat asset again with mode one for the
    256-entry TLUT. When the fifth argument to ``func_1510CE60`` is non-null,
    that second pointer is rebased to ``payload_end - 0x200``. Bank 09's
    loaders prove this path. Banks 03 and 04 use a null fifth argument and are
    deliberately rejected by ``choose_preview_texture`` before reaching here.
    """

    state = texture_coordinate_state(run)
    if (
        state is None
        or state["format"] != 2
        or state["size"] != 1
        or run.pixel is None
        or run.palette is None
        or run.render_tile is None
        or run.pixel.flat_index is None
        or run.pixel.flat_index != run.palette.flat_index
        or run.pixel.image_command != 0xFD500000
        or run.pixel.mode != 0
        or run.palette.image_command != 0xFD100000
        or run.palette.mode != 1
    ):
        raise ValueError("material run is not a direct same-index CI8 load")
    if run.pixel.load_command is None or run.palette.load_command is None:
        return None, "direct-ci8-load-command-unresolved"

    pixel_load_command, pixel_load_argument = run.pixel.load_command
    palette_load_command, palette_load_argument = run.palette.load_command
    if pixel_load_command >> 24 != 0xF3 or palette_load_command >> 24 != 0xF0:
        return None, "direct-ci8-load-command-unresolved"
    if ((palette_load_argument >> 14) & 0x3FF) + 1 != 256:
        return None, "direct-ci8-tlut-size-unresolved"

    transfer_size = (run.pixel.image_command >> 19) & 3
    transfer_bytes_per_texel = (1, 1, 2, 4)[transfer_size]
    transfer_size_bytes = (
        ((pixel_load_argument >> 12) & 0xFFF) + 1
    ) * transfer_bytes_per_texel
    render_tile_command, _ = run.render_tile
    if render_tile_command & 0x1FF:
        return None, "direct-ci8-tmem-offset-unresolved"
    row_size = state["width"]
    line_words = (render_tile_command >> 9) & 0x1FF
    row_stride = line_words * 8 if line_words else row_size
    if row_stride < row_size:
        return None, "direct-ci8-row-stride-unresolved"
    pixel_storage_size = (state["height"] - 1) * row_stride + row_size
    if pixel_storage_size > transfer_size_bytes:
        return None, "direct-ci8-tmem-span-unresolved"
    if pixel_storage_size > len(payload):
        return None, "direct-ci8-payload-span-unresolved"

    palette_byte_offset = len(payload) - 0x200
    if palette_byte_offset < pixel_storage_size:
        return None, "direct-ci8-pixel-palette-overlap-unresolved"

    rows = []
    for row_index in range(state["height"]):
        row_start = row_index * row_stride
        row = payload[row_start : row_start + row_stride]
        if row_index & 1:
            row = bytes(row[index ^ 4] for index in range(row_stride))
        rows.append(row[:row_size])
    linear_pixels = b"".join(rows)
    palette = payload[palette_byte_offset:]
    png_data = encode_ci8_png(
        linear_pixels + palette,
        "linear",
        state["width"],
        state["height"],
    )
    return (
        PreviewTexture(
            family="us-direct-runtime-composed",
            source=None,
            flat_index=run.pixel.flat_index,
            format=state["format"],
            size=state["size"],
            width=state["width"],
            height=state["height"],
            sha1=hashlib.sha1(png_data).hexdigest(),
            png_data=png_data,
            pixel_byte_offset=0,
            palette_byte_offset=palette_byte_offset,
        ),
        "runtime-composed-direct-ci8-texture",
    )


def choose_preview_texture(
    run: ModelMaterialRun,
    catalog: dict[tuple[int, int, int], tuple[PreviewTexture, ...]],
    flat_payloads: dict[int, bytes] | None = None,
    *,
    mode_one_ci8_palette_policy: str | None = None,
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
        combine = decode_combine_mode(run.combine_mode)
        if combine is not None:
            texture_inputs = {
                name for name in combine["inputs"] if name in ("TEXEL0", "TEXEL1")
            }
            if texture_inputs == {"TEXEL0", "TEXEL1"}:
                if not any(tile_index == 1 for tile_index, _, _ in run.render_tiles):
                    return None, "character-indexed-mipmap-state-unresolved"
                # The complete tile ladder is now preserved, but glTF cannot
                # represent the RDP's TEXEL0/TEXEL1 LOD interpolation together
                # with its dynamic primitive/environment colour formula. A
                # base-level diffuse binding makes several valid mask textures
                # look like corrupt colour images, so keep these runs unbound.
                return None, "character-indexed-mipmap-combiner-unresolved"
            elif texture_inputs != {"TEXEL0"}:
                # Colour-only runs depend on dynamic primitive/environment
                # state and must not be assigned the nearest texture.
                return None, "native-material-combiner-unresolved"
        if flat_payloads is None:
            return None, "character-indexed-material-runtime-unresolved"
        payload = flat_payloads.get(run.pixel.flat_index)
        if payload is None:
            return None, "character-indexed-flat-payload-missing"
        return character_runtime_preview_texture(run, payload)
    if state["format"] == 2:
        if (
            run.palette is None
            or run.palette.flat_index != run.pixel.flat_index
        ):
            return None, "unresolved-ci-palette"
        if state["size"] == 1:
            if run.palette.mode != 1:
                return None, "unresolved-ci-palette"
            if mode_one_ci8_palette_policy == "payload-base":
                return None, "mode-one-ci8-palette-overlaps-pixels"
            if mode_one_ci8_palette_policy == "payload-end-minus-0x200":
                if flat_payloads is None:
                    return None, "direct-ci8-flat-payload-missing"
                payload = flat_payloads.get(run.pixel.flat_index)
                if payload is None:
                    return None, "direct-ci8-flat-payload-missing"
                return direct_runtime_ci8_preview_texture(run, payload)
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
    if manifest["bank_index"] == 1 and (
        manifest["animation_clip_count"] != 2621
        or manifest["animation_frame_count"] != 57732
        or manifest["incompatible_animation_clip_count"] != 0
    ):
        raise ValueError("bank-01 preview animation inventory changed")
    for relative_file, expected_sha1 in texture_files.items():
        path = output / relative_file
        if (
            not path.is_file()
            or hashlib.sha1(path.read_bytes()).hexdigest() != expected_sha1
        ):
            raise ValueError(f"preview texture failed verification: {relative_file}")
    for model in manifest["models"]:
        if (
            model["source_face_count"]
            != model["face_count"] + model["omitted_zero_area_face_count"]
        ):
            raise ValueError("preview source and exported face counts do not agree")
        if model["omitted_zero_area_face_count"] != len(
            model["omitted_zero_area_faces"]
        ):
            raise ValueError("preview omitted-face count does not match its records")
        if sum(
            run["source_face_count"] for run in model["material_runs"]
        ) != model["source_face_count"]:
            raise ValueError("preview material runs do not cover every source face")
        if sum(run["face_count"] for run in model["material_runs"]) != model[
            "face_count"
        ]:
            raise ValueError("preview material runs do not cover every exported face")
        if sum(
            run["omitted_zero_area_face_count"]
            for run in model["material_runs"]
        ) != model["omitted_zero_area_face_count"]:
            raise ValueError("preview material-run omitted counts do not agree")
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
        if len(primitives) != sum(
            run["face_count"] > 0 for run in model["material_runs"]
        ):
            raise ValueError(f"preview glTF material-run mismatch: {gltf_path.name}")
        expected_runtime_materials = sum(
            run["face_count"] > 0 and run["runtime_material"] is not None
            for run in model["material_runs"]
        )
        actual_runtime_materials = sum(
            "runtimeMaterial" in material.get("extras", {})
            for material in gltf.get("materials", [])
        )
        if actual_runtime_materials != expected_runtime_materials:
            raise ValueError(
                f"preview glTF runtime material count mismatch: {gltf_path.name}"
            )
        replay_by_run = {
            material.get("extras", {}).get("materialRun"): material.get(
                "extras", {}
            )
            .get("runtimeMaterial", {})
            .get("lightingReplay")
            for material in gltf.get("materials", [])
        }
        if any(
            run.get("runtime_lighting_replay") != replay_by_run.get(run_index)
            for run_index, run in enumerate(model["material_runs"])
            if run.get("runtime_lighting_replay") is not None
        ):
            raise ValueError(
                f"preview glTF lighting replay status mismatch: {gltf_path.name}"
            )
        if any(
            material.get("alphaMode", "OPAQUE") not in ("OPAQUE", "MASK", "BLEND")
            for material in gltf.get("materials", [])
        ):
            raise ValueError(f"preview glTF has an invalid alpha mode: {gltf_path.name}")
        if any("COLOR_0" not in primitive["attributes"] for primitive in primitives):
            raise ValueError(f"preview glTF omits vertex colors: {gltf_path.name}")
        if model.get("joint_count", 0):
            if len(gltf.get("skins", [])) != 1:
                raise ValueError(f"preview glTF omits its character skin: {gltf_path.name}")
            skin = gltf["skins"][0]
            if len(skin["joints"]) != model["joint_count"]:
                raise ValueError(f"preview glTF joint count mismatch: {gltf_path.name}")
            inverse_bind_index = skin.get("inverseBindMatrices")
            if not isinstance(inverse_bind_index, int) or not (
                0 <= inverse_bind_index < len(gltf["accessors"])
            ):
                raise ValueError(
                    f"preview glTF omits inverse bind matrices: {gltf_path.name}"
                )
            inverse_bind_accessor = gltf["accessors"][inverse_bind_index]
            if (
                inverse_bind_accessor["type"] != "MAT4"
                or inverse_bind_accessor["componentType"] != 5126
                or inverse_bind_accessor["count"] != model["joint_count"]
            ):
                raise ValueError(
                    f"preview glTF has invalid inverse bind matrices: {gltf_path.name}"
                )
            if any(
                "JOINTS_0" not in primitive["attributes"]
                or "WEIGHTS_0" not in primitive["attributes"]
                for primitive in primitives
            ):
                raise ValueError(f"preview glTF omits rigid skin weights: {gltf_path.name}")
            if any("NORMAL" not in primitive["attributes"] for primitive in primitives):
                raise ValueError(f"preview glTF omits character normals: {gltf_path.name}")
            if any(not 0 <= node < len(gltf["nodes"]) for node in skin["joints"]):
                raise ValueError(f"preview glTF has an invalid joint node: {gltf_path.name}")
            animations = gltf.get("animations", [])
            if len(animations) != model["animation_clip_count"]:
                raise ValueError(
                    f"preview glTF animation count mismatch: {gltf_path.name}"
                )
            for animation in animations:
                for channel in animation["channels"]:
                    if not 0 <= channel["sampler"] < len(animation["samplers"]):
                        raise ValueError(
                            f"preview glTF has an invalid animation sampler: {gltf_path.name}"
                        )
                    if not 0 <= channel["target"]["node"] < len(gltf["nodes"]):
                        raise ValueError(
                            f"preview glTF has an invalid animation node: {gltf_path.name}"
                        )
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
        if model.get("bind_gltf_file") is not None:
            bind_gltf_path = output / model["bind_gltf_file"]
            bind_binary_path = output / model["bind_gltf_binary_file"]
            if not bind_gltf_path.is_file() or not bind_binary_path.is_file():
                raise ValueError("character bind preview is missing an exported file")
            bind_gltf = json.loads(bind_gltf_path.read_text(encoding="utf-8"))
            if bind_gltf.get("animations"):
                raise ValueError(
                    f"character bind preview contains animations: {bind_gltf_path.name}"
                )
            if bind_gltf["buffers"][0]["byteLength"] != bind_binary_path.stat().st_size:
                raise ValueError(
                    f"character bind preview buffer mismatch: {bind_gltf_path.name}"
                )
            if len(bind_gltf.get("skins", [])) != 1 or len(
                bind_gltf["skins"][0]["joints"]
            ) != model["joint_count"]:
                raise ValueError(
                    f"character bind preview skin mismatch: {bind_gltf_path.name}"
                )
    if manifest.get("runtime_lighting_replay_run_count") != sum(
        run.get("runtime_lighting_replay", {}).get("status")
        == "gliden64-equivalent-observed-draw"
        for model in manifest["models"]
        for run in model["material_runs"]
    ):
        raise ValueError("preview runtime lighting replay count changed")
    if manifest.get("assembled_scene_count", 0) != len(
        manifest.get("assembled_scenes", [])
    ):
        raise ValueError("preview assembled scene count changed")
    if manifest.get("assembled_scene_placement_count", 0) != sum(
        scene["placement_record_count"]
        for scene in manifest.get("assembled_scenes", [])
    ):
        raise ValueError("preview assembled placement count changed")
    if manifest.get("unresolved_placement_scene_count", 0) != len(
        manifest.get("unresolved_placement_scenes", [])
    ):
        raise ValueError("preview unresolved placement scene count changed")
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
    if any(
        index not in banks or banks[index].flags
        for index in (*PLACEMENT_BANKS, 0x03, 0x04)
    ):
        raise ValueError("US object placement or model bank is absent")

    available_model_indices = set()
    for entry in parse_asset_entries(normalized, banks[0x03]):
        raw = normalized[entry.start : entry.end]
        data = decode_rzip_chunk(raw).data if entry.compressed else raw
        parse_model_geometry(data)
        available_model_indices.add(entry.index)

    available_segment_indices: dict[int, set[int]] = {}
    for entry in parse_asset_entries(normalized, banks[0x04]):
        raw = normalized[entry.start : entry.end]
        data = decode_rzip_chunk(raw).data if entry.compressed else raw
        segments = parse_model_bundle(data)
        available_segment_indices[entry.index] = {
            segment.index for segment in segments if segment.data
        }

    payloads: dict[tuple[int, int], bytes] = {}
    scene_records = []
    referenced_model_indices = set()
    referenced_segment_indices = set()
    resolved_segment_indices = set()
    unresolved_dispatch_references = []
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
            if bank_index == 0x0B:
                for record in parsed_records:
                    dispatch_index = record["dispatch_index"]
                    model_reference = (entry.index, dispatch_index)
                    referenced_segment_indices.add(model_reference)
                    record["model_source"] = [0x04, entry.index, dispatch_index]
                    if dispatch_index in available_segment_indices.get(entry.index, set()):
                        resolved_segment_indices.add(model_reference)
                        record["model_resolution_status"] = "resolved-bank-04-segment"
                    else:
                        record["model_resolution_status"] = (
                            "unavailable-bank-04-scene-or-segment"
                        )
                        unresolved_dispatch_references.append(
                            {
                                "scene_index": entry.index,
                                "placement_record": record["index"],
                                "dispatch_kind": record["dispatch_kind"],
                                "dispatch_index": dispatch_index,
                                "model_source": record["model_source"],
                            }
                        )
            else:
                for record in parsed_records:
                    record["model_source"] = [0x03, record["model_index"]]
                    record["model_resolution_status"] = "resolved-bank-03-model"
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
            "collision_included_record_count": sum(
                record["collision_included"]
                for scene in scene_records
                for record in scene["records"]
            ),
            "collision_excluded_record_count": sum(
                not record["collision_included"]
                for scene in scene_records
                for record in scene["records"]
            ),
            "referenced_bank_03_model_count": len(referenced_model_indices),
            "referenced_bank_03_model_indices": sorted(referenced_model_indices),
            "unreferenced_bank_03_model_indices": sorted(
                available_model_indices.difference(referenced_model_indices)
            ),
            "referenced_bank_04_segment_count": len(referenced_segment_indices),
            "resolved_bank_04_segment_count": len(resolved_segment_indices),
            "resolved_bank_11_record_count": sum(
                record["model_resolution_status"] == "resolved-bank-04-segment"
                for scene in scene_records
                if scene["bank_index"] == 0x0B
                for record in scene["records"]
            ),
            "unresolved_bank_11_record_count": len(unresolved_dispatch_references),
            "unresolved_bank_11_dispatch_references": unresolved_dispatch_references,
            "structural_status": "proven",
            "transform_semantics_status": "runtime-proven-static-transform",
            "runtime_evidence": {
                "record_loader_function": "func_150039E0",
                "record_loader_assembly": "asm/nonmatchings/game_30E90/func_150039E0.s",
                "record_size": "0x44",
                "bank_11_path": [0x0B, "scene-index"],
                "bank_12_path": [0x0C, "scene-index", 2],
                "bank_11_model_table_loader": "func_150031EC",
                "bank_11_model_table": "D_800B0E50",
                "bank_11_model_source": [0x04, "scene-index", "dispatch-index"],
                "bank_11_dispatch_kind_offset": "0x0C",
                "bank_11_dispatch_index_offset": "0x10",
                "position_offset": "0x00",
                "rotation_degrees_offset": "0x06",
                "bank_12_model_index_offset": "0x10",
                "collision_flags_source_offset": "0x32",
                "collision_flags_runtime_offset": "0x4F",
                "collision_exclusion_mask": "(flags & 0x60) == 0x20",
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


def parse_character_animation_descriptor(
    descriptor: bytes,
    *,
    runtime_zero_fill_limit: int = 0,
) -> CharacterAnimationLayout:
    """Parse the per-clip layout consumed by ``func_150A8A18``.

    The descriptor supplies fixed bases and bit widths. Each adjacent odd
    segment is consequently a sequence of fixed-stride frames, not one opaque
    animation bitstream. Optional joint translations are selected by a
    big-endian mask before the packed root and rotation channels.
    """

    if len(descriptor) < 10 or descriptor[1] < 2:
        raise ValueError("character animation descriptor is too short")
    if runtime_zero_fill_limit < 0:
        raise ValueError("character animation runtime zero-fill limit is invalid")
    runtime_descriptor = descriptor + bytes(runtime_zero_fill_limit)

    def descriptor_word(word_offset: int, label: str) -> int:
        if word_offset + 2 > len(runtime_descriptor):
            raise ValueError(f"character animation {label} is truncated")
        return struct.unpack_from(">H", runtime_descriptor, word_offset)[0]

    joint_count = descriptor[1] - 1
    flags = descriptor[7] & 0xF0
    offset = 10
    if flags & 0x40:
        offset += 2
    if flags & 0x20:
        offset += 2
    if offset > len(descriptor):
        raise ValueError("character animation optional header is truncated")

    translation_mask = [False] * joint_count
    if flags & 0x80:
        mask_size = ((joint_count + 15) // 16) * 2
        if offset + mask_size > len(runtime_descriptor):
            raise ValueError("character animation translation mask is truncated")
        mask = int.from_bytes(
            runtime_descriptor[offset : offset + mask_size].ljust(8, b"\0"), "big"
        )
        translation_mask = [
            bool(mask & (1 << (63 - index))) for index in range(joint_count)
        ]
        offset += mask_size

    channels = []
    packed_bit_size = sum(
        (descriptor[6] >> 4, descriptor[6] & 0xF, descriptor[7] & 0xF)
    )
    for _ in range(joint_count * 3):
        word = descriptor_word(offset, "rotation table")
        offset += 2
        scale_base = scale_width = None
        if word & 0x10:
            scale = descriptor_word(offset, "scale table")
            offset += 2
            scale_base = scale & 0xFFF0
            scale_width = scale & 0xF
            packed_bit_size += scale_width
        channels.append(
            CharacterAnimationChannel(
                # Bit 4 marks the following scale descriptor. Runtime angle
                # lookup shifts the value right by five, so it is not angle data.
                base_value=word & 0xFFE0,
                bit_width=word & 0xF,
                scale_base_value=scale_base,
                scale_bit_width=scale_width,
            )
        )
        packed_bit_size += word & 0xF

    zero_fill_size = max(0, offset - len(descriptor))
    padding = descriptor[offset:] if offset <= len(descriptor) else b""
    if len(padding) > 7 or any(padding):
        raise ValueError("character animation descriptor has unresolved trailing data")
    translation_bytes = sum(translation_mask) * 6
    decoded_frame_byte_size = translation_bytes + (packed_bit_size + 7) // 8
    frame_byte_size = descriptor[5]
    if frame_byte_size < decoded_frame_byte_size:
        raise ValueError(
            "character animation declared frame stride is smaller than its channels"
        )
    return CharacterAnimationLayout(
        joint_count=joint_count,
        flags=flags,
        root_bit_widths=(
            descriptor[6] >> 4,
            descriptor[6] & 0xF,
            descriptor[7] & 0xF,
        ),
        joint_translation_mask=tuple(translation_mask),
        rotation_channels=tuple(channels),
        descriptor_bytes_consumed=offset,
        descriptor_padding_size=len(padding),
        descriptor_runtime_zero_fill_size=zero_fill_size,
        frame_bit_size=translation_bytes * 8 + packed_bit_size,
        decoded_frame_byte_size=decoded_frame_byte_size,
        frame_byte_size=frame_byte_size,
        frame_trailing_size=frame_byte_size - decoded_frame_byte_size,
    )


def decode_character_animation_frame(
    descriptor: bytes,
    frame_data: bytes,
    *,
    runtime_zero_fill_limit: int = 0,
) -> CharacterAnimationFrame:
    """Decode one discrete bank-02 pose without runtime interpolation."""

    layout = parse_character_animation_descriptor(
        descriptor, runtime_zero_fill_limit=runtime_zero_fill_limit
    )
    if len(frame_data) != layout.frame_byte_size:
        raise ValueError("character animation frame has an invalid size")
    offset = 0
    translations: list[tuple[int, int, int] | None] = []
    for present in layout.joint_translation_mask:
        if not present:
            translations.append(None)
            continue
        translations.append(struct.unpack_from(">3h", frame_data, offset))
        offset += 6

    packed_end = offset + (layout.frame_bit_size - offset * 8 + 7) // 8
    reader = CharacterAnimationBitReader(frame_data[offset:packed_end])
    root_translation = tuple(
        struct.unpack(">b", descriptor[index : index + 1])[0] * 0x1000
        + (reader.read(width) << 5)
        for index, width in zip((0, 2, 4), layout.root_bit_widths)
    )
    encoded_values = []
    scale_values: list[int | None] = []
    for channel in layout.rotation_channels:
        encoded_values.append(
            (channel.base_value + (reader.read(channel.bit_width) << 5)) & 0xFFFF
        )
        if channel.scale_bit_width is None:
            scale_values.append(None)
        else:
            assert channel.scale_base_value is not None
            scale_values.append(
                (
                    channel.scale_base_value
                    + (reader.read(channel.scale_bit_width) << 5)
                )
                & 0xFFFF
            )
    encoded_rotations = tuple(
        tuple(encoded_values[index : index + 3])
        for index in range(0, len(encoded_values), 3)
    )
    return CharacterAnimationFrame(
        root_translation=root_translation,
        joint_translation_deltas=tuple(translations),
        encoded_rotations=encoded_rotations,
        rotations=tuple(
            character_rotation_quaternion(rotation)
            for rotation in encoded_rotations
        ),
        scale_channels=tuple(scale_values),
        trailing_data=frame_data[layout.decoded_frame_byte_size :],
    )


def decode_character_animation_timeline(
    descriptor: bytes,
    bitstream: bytes,
    *,
    runtime_zero_fill_limit: int = 0,
) -> tuple[CharacterAnimationFrame, ...]:
    """Decode the runtime-selected frames and reject non-padding companion data."""

    layout = parse_character_animation_descriptor(
        descriptor, runtime_zero_fill_limit=runtime_zero_fill_limit
    )
    frame_count, trailing_data, _ = character_animation_frame_span(
        descriptor, layout, bitstream
    )
    if len(trailing_data) > 7 or any(trailing_data):
        raise ValueError("character animation bitstream has unresolved trailing data")
    return tuple(
        decode_character_animation_frame(
            descriptor,
            bitstream[
                index * layout.frame_byte_size:
                (index + 1) * layout.frame_byte_size
            ],
            runtime_zero_fill_limit=runtime_zero_fill_limit,
        )
        for index in range(frame_count)
    )


def character_animation_frame_span(
    descriptor: bytes,
    layout: CharacterAnimationLayout,
    bitstream: bytes,
    *,
    runtime_duration: int | None = None,
    runtime_duration_status: str | None = None,
) -> tuple[int, bytes, str]:
    """Return the source-frame count selected by ``func_1502D824``.

    Descriptor byte 3 is the duration and byte 8 plus one is the interval
    between stored source frames. A duration of 0xFF is replaced at runtime.
    Callers that resolve the character-specific replacement pass it here;
    otherwise the clip remains conservatively segment-bounded.
    """

    if layout.frame_byte_size == 0:
        if bitstream:
            raise ValueError("zero-stride character animation has payload data")
        return 0, b"", "empty-zero-stride"
    duration = descriptor[3]
    keyframe_step = descriptor[8] + 1
    if duration == 0xFF:
        if runtime_duration is None:
            frame_count, trailing_size = divmod(
                len(bitstream), layout.frame_byte_size
            )
            trailing_data = bitstream[-trailing_size:] if trailing_size else b""
            if len(trailing_data) > 7 or any(trailing_data):
                raise ValueError(
                    "runtime-duration character animation has unresolved trailing data"
                )
            return (
                frame_count,
                trailing_data,
                "runtime-duration-override-segment-bounded",
            )
        if runtime_duration <= 0:
            raise ValueError("runtime character animation duration is not positive")
        duration = runtime_duration
    if duration == 0:
        raise ValueError("nonempty character animation has zero duration")
    frame_count = (duration - 1 + keyframe_step - 1) // keyframe_step + 1
    frame_data_size = frame_count * layout.frame_byte_size
    if frame_data_size > len(bitstream):
        raise ValueError("character animation bitstream is truncated")
    return (
        frame_count,
        bitstream[frame_data_size:],
        runtime_duration_status or "descriptor-duration-and-keyframe-spacing",
    )


def parse_character_animation_route_table(data: bytes) -> tuple[dict[str, int], ...]:
    """Decode the eight-byte records consumed by ``func_1505E650``.

    The first halfword selects an even bank-02 segment, the second indexes the
    runtime metadata table used by ``func_1505E0C4``, and the final word is an
    optional in-entry offset relocated by ``func_1503D484``.
    """

    if len(data) < 0x18:
        raise ValueError("character animation route table is truncated")
    records = []
    for offset in range(0x10, len(data), 8):
        segment_index, runtime_table_index, auxiliary_offset = struct.unpack_from(
            ">HHI", data, offset
        )
        if segment_index == CHARACTER_ANIMATION_ROUTE_SENTINEL:
            if runtime_table_index or auxiliary_offset:
                raise ValueError("character animation route sentinel has payload data")
            return tuple(records)
        if segment_index & 1:
            raise ValueError("character animation route selects an odd descriptor segment")
        if (
            auxiliary_offset
            and not auxiliary_offset & 0x0F000000
            and auxiliary_offset >= len(data)
        ):
            raise ValueError("character animation route auxiliary offset is out of range")
        records.append(
            {
                "logical_animation_index": len(records),
                "descriptor_segment_index": segment_index,
                "pair_index": segment_index // 2,
                "runtime_table_index": runtime_table_index,
                "auxiliary_offset": auxiliary_offset,
            }
        )
    raise ValueError("character animation route table lacks its sentinel")


def character_animation_group_routes(
    game_data: bytes, game_data_vram: int
) -> tuple[tuple[dict[str, Any], ...], dict[int, int]]:
    """Recover the five representative groups selected by ``func_1503D5F0``."""

    def data_offset(address: int, size: int) -> int:
        offset = address - game_data_vram
        if offset < 0 or offset + size > len(game_data):
            raise ValueError(f"runtime data address 0x{address:X} is outside game data")
        return offset

    count_offset = data_offset(CHARACTER_ANIMATION_GROUP_COUNTS_ADDRESS, 5)
    pointer_offset = data_offset(CHARACTER_ANIMATION_GROUP_POINTERS_ADDRESS, 20)
    counts = game_data[count_offset : count_offset + 5]
    pointers = struct.unpack_from(">5I", game_data, pointer_offset)
    groups = []
    representative_by_character: dict[int, int] = {}
    for group_index, (count, pointer) in enumerate(zip(counts, pointers)):
        members_offset = data_offset(pointer, count)
        members = tuple(game_data[members_offset : members_offset + count])
        if not members:
            raise ValueError("character animation route group is empty")
        representative = members[0]
        for member in members:
            existing = representative_by_character.get(member)
            if existing is not None and existing != representative:
                raise ValueError("character belongs to conflicting animation route groups")
            representative_by_character[member] = representative
        groups.append(
            {
                "group_index": group_index,
                "representative_bank_entry": representative,
                "character_bank_entries": list(members),
            }
        )
    return tuple(groups), representative_by_character


def resolve_character_animation_runtime_duration(
    bank_entry: int,
    logical_animation_indices: tuple[int, ...],
    game_data: bytes,
    game_data_vram: int,
) -> tuple[int, str]:
    """Apply the character-specific 0xFF duration paths in ``func_1505E0C4``."""

    if bank_entry == 0x92:
        if not logical_animation_indices:
            raise ValueError("character 0x92 runtime duration lacks a logical route")
        durations = set()
        for logical_index in logical_animation_indices:
            offset = (
                CHARACTER_ANIMATION_DURATION_TABLE_ADDRESS
                - game_data_vram
                + logical_index * 2
            )
            if offset < 0 or offset + 2 > len(game_data):
                raise ValueError("character animation duration table is truncated")
            durations.add(struct.unpack_from(">H", game_data, offset)[0])
        if len(durations) != 1:
            raise ValueError("logical routes disagree on runtime animation duration")
        return durations.pop(), "runtime-character-0x92-duration-table"
    if bank_entry in (0xB7, 0xB8, 0xB9):
        offset = CHARACTER_ANIMATION_SPECIAL_DURATION_ADDRESS - game_data_vram
        if offset < 0 or offset + 4 > len(game_data):
            raise ValueError("special character animation duration is outside game data")
        duration = struct.unpack_from(">f", game_data, offset)[0]
        if not duration.is_integer() or duration <= 0:
            raise ValueError("special character animation duration is not integral")
        return int(duration), "runtime-character-0xB7-0xB9-duration-constant"
    return 0xFF, "runtime-default-u8-duration"


def character_rotation_quaternion(
    encoded_angles: tuple[int, int, int],
) -> tuple[float, float, float, float]:
    """Convert Conker's three stored Euler angles to the runtime glTF rotation."""

    angles = [
        struct.unpack(">h", struct.pack(">H", value & 0xFFE0))[0]
        * (math.pi / 65536.0)
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
    descriptor: bytes,
    bitstream: bytes,
    *,
    runtime_zero_fill_limit: int = 0,
) -> tuple[tuple[float, float, float, float], ...]:
    """Decode the first pose using the bit layout consumed by func_150A8A18."""

    layout = parse_character_animation_descriptor(
        descriptor, runtime_zero_fill_limit=runtime_zero_fill_limit
    )
    if len(bitstream) < layout.frame_byte_size:
        raise ValueError("character animation bitstream is truncated")
    return decode_character_animation_frame(
        descriptor,
        bitstream[: layout.frame_byte_size],
        runtime_zero_fill_limit=runtime_zero_fill_limit,
    ).rotations


def parse_runtime_character_animation_descriptor(
    descriptor: bytes,
) -> CharacterAnimationLayout:
    """Reproduce the zeroed descriptor destination used by ``func_1505E0C4``."""

    return parse_character_animation_descriptor(
        descriptor, runtime_zero_fill_limit=15
    )


def load_character_animation_manifest(
    profile: str,
    rom_argument: Path | None,
    *,
    include_files: bool,
) -> tuple[dict[str, Any], dict[str, bytes]]:
    """Preserve the bank-02 data loaded alongside bank-01 character models."""

    rom_path, rom_layout = resolve_rom(profile, rom_argument)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in rom_layout["normalized_sha1"]:
        raise ValueError(f"US normalized ROM SHA-1 mismatch: got {digest}")
    banks = {
        bank.index: bank
        for bank in parse_asset_banks(normalized, rom_layout["asset_table"])
    }
    bank = banks.get(0x02)
    if bank is None or bank.flags:
        raise ValueError("US character animation bank 02 is absent")
    route_bank = banks.get(CHARACTER_ANIMATION_ROUTE_BANK)
    if route_bank is None or route_bank.flags:
        raise ValueError("US character animation route bank 15 is absent")

    route_payloads = {}
    for route_entry in parse_asset_entries(normalized, route_bank):
        raw = normalized[route_entry.start : route_entry.end]
        route_payloads[route_entry.index] = (
            decode_rzip_chunk(raw).data if route_entry.compressed else raw
        )
    if rom_layout.get("game_format") != "rzip":
        raise ValueError("US character animation evidence requires the RZIP game archive")
    game = parse_game_archive(
        normalized[rom_layout["game_start"] : rom_layout["game_end"]]
    )
    game_data_vram = int(rom_layout["game_data_vram"])
    route_groups, route_representative_by_character = character_animation_group_routes(
        game.data, game_data_vram
    )

    files: dict[str, bytes] = {}
    records = []
    clip_pair_count = segment_count = 0
    decoded_clip_count = empty_clip_count = unresolved_clip_count = 0
    decoded_frame_count = 0
    runtime_zero_filled_descriptor_count = extended_stride_clip_count = 0
    companion_trailing_clip_count = companion_trailing_byte_count = 0
    runtime_duration_override_clip_count = 0
    resolved_runtime_duration_override_clip_count = 0
    bitstream_alignment_padding_clip_count = 0
    bitstream_alignment_padding_byte_count = 0
    scale_channel_count = scale_channel_clip_count = 0
    logical_animation_route_count = 0
    mapped_logical_animation_route_count = 0
    for entry in parse_asset_entries(normalized, bank):
        raw = normalized[entry.start : entry.end]
        data = decode_rzip_chunk(raw).data if entry.compressed else raw
        entry_file = f"animations/bank-02/entries/{entry.index:04d}.bin"
        if include_files:
            files[entry_file] = data
        route_bank_entry = route_representative_by_character.get(
            entry.index, entry.index
        )
        route_payload = route_payloads.get(route_bank_entry)
        if route_payload is None:
            raise ValueError(
                f"bank-02 entry {entry.index} lacks runtime animation routes"
            )
        route_records = parse_character_animation_route_table(route_payload)
        logical_animation_route_count += len(route_records)
        logical_indices_by_pair: dict[int, list[int]] = {}
        for route in route_records:
            logical_indices_by_pair.setdefault(route["pair_index"], []).append(
                route["logical_animation_index"]
            )
        record: dict[str, Any] = {
            "bank_entry": entry.index,
            "type_flags": entry.type_flags,
            "compressed": entry.compressed,
            "decoded_size": len(data),
            "decoded_sha1": hashlib.sha1(data).hexdigest(),
            "file": entry_file if include_files else None,
            "animation_route_bank": CHARACTER_ANIMATION_ROUTE_BANK,
            "animation_route_bank_entry": route_bank_entry,
            "logical_animation_route_count": len(route_records),
            "logical_animation_routes": [
                {
                    **route,
                    "auxiliary_offset": f"0x{route['auxiliary_offset']:X}",
                }
                for route in route_records
            ],
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
            invalid_routes = [
                route
                for route in route_records
                if route["descriptor_segment_index"] >= len(segments)
            ]
            if invalid_routes:
                raise ValueError(
                    f"bank-02 entry {entry.index} has out-of-range animation routes"
                )
            mapped_logical_animation_route_count += len(route_records)
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
            clip_records = []
            for pair_index in range(len(segments) // 2):
                descriptor = segments[pair_index * 2].data
                bitstream = segments[pair_index * 2 + 1].data
                logical_animation_indices = tuple(
                    logical_indices_by_pair.get(pair_index, ())
                )
                clip_record: dict[str, Any] = {
                    "pair_index": pair_index,
                    "descriptor_segment_index": pair_index * 2,
                    "bitstream_segment_index": pair_index * 2 + 1,
                    "logical_animation_indices": list(logical_animation_indices),
                }
                if not bitstream:
                    layout = parse_runtime_character_animation_descriptor(descriptor)
                    empty_clip_count += 1
                    clip_scale_channel_count = sum(
                        channel.scale_bit_width is not None
                        for channel in layout.rotation_channels
                    )
                    scale_channel_count += clip_scale_channel_count
                    scale_channel_clip_count += bool(clip_scale_channel_count)
                    clip_record.update(
                        timeline_status="empty-bitstream-preserved",
                        joint_count=layout.joint_count,
                        flags=f"0x{layout.flags:02X}",
                        root_bit_widths=list(layout.root_bit_widths),
                        translated_joint_count=sum(layout.joint_translation_mask),
                        rotation_channel_count=len(layout.rotation_channels),
                        scale_channel_count=clip_scale_channel_count,
                        descriptor_bytes_consumed=(
                            layout.descriptor_bytes_consumed
                        ),
                        descriptor_padding_size=layout.descriptor_padding_size,
                        descriptor_runtime_zero_fill_size=(
                            layout.descriptor_runtime_zero_fill_size
                        ),
                        frame_bit_size=layout.frame_bit_size,
                        decoded_frame_byte_size=layout.decoded_frame_byte_size,
                        frame_byte_size=layout.frame_byte_size,
                        frame_trailing_size=layout.frame_trailing_size,
                        frame_count=0,
                        bitstream_padding_size=0,
                    )
                else:
                    try:
                        layout = parse_runtime_character_animation_descriptor(
                            descriptor
                        )
                        runtime_duration = runtime_duration_status = None
                        if descriptor[3] == 0xFF:
                            (
                                runtime_duration,
                                runtime_duration_status,
                            ) = resolve_character_animation_runtime_duration(
                                entry.index,
                                logical_animation_indices,
                                game.data,
                                game_data_vram,
                            )
                        (
                            frame_count,
                            trailing_data,
                            duration_status,
                        ) = character_animation_frame_span(
                            descriptor,
                            layout,
                            bitstream,
                            runtime_duration=runtime_duration,
                            runtime_duration_status=runtime_duration_status,
                        )
                        is_alignment_padding = (
                            len(trailing_data) <= 7 and not any(trailing_data)
                        )
                    except ValueError as error:
                        unresolved_clip_count += 1
                        clip_record.update(
                            timeline_status="unresolved-frame-layout",
                            error=str(error),
                        )
                    else:
                        decoded_clip_count += 1
                        decoded_frame_count += frame_count
                        runtime_zero_filled_descriptor_count += bool(
                            layout.descriptor_runtime_zero_fill_size
                        )
                        extended_stride_clip_count += bool(
                            layout.frame_trailing_size
                        )
                        companion_trailing_size = (
                            0 if is_alignment_padding else len(trailing_data)
                        )
                        bitstream_padding_size = (
                            len(trailing_data) if is_alignment_padding else 0
                        )
                        bitstream_alignment_padding_clip_count += bool(
                            bitstream_padding_size
                        )
                        bitstream_alignment_padding_byte_count += (
                            bitstream_padding_size
                        )
                        companion_trailing_clip_count += bool(
                            companion_trailing_size
                        )
                        companion_trailing_byte_count += companion_trailing_size
                        runtime_duration_override_clip_count += (
                            descriptor[3] == 0xFF
                        )
                        resolved_runtime_duration_override_clip_count += (
                            descriptor[3] == 0xFF
                            and duration_status
                            != "runtime-duration-override-segment-bounded"
                        )
                        clip_scale_channel_count = sum(
                            channel.scale_bit_width is not None
                            for channel in layout.rotation_channels
                        )
                        scale_channel_count += clip_scale_channel_count
                        scale_channel_clip_count += bool(clip_scale_channel_count)
                        clip_record.update(
                            timeline_status="runtime-frame-layout-proven",
                            joint_count=layout.joint_count,
                            flags=f"0x{layout.flags:02X}",
                            root_bit_widths=list(layout.root_bit_widths),
                            translated_joint_count=sum(
                                layout.joint_translation_mask
                            ),
                            rotation_channel_count=len(layout.rotation_channels),
                            scale_channel_count=clip_scale_channel_count,
                            descriptor_bytes_consumed=(
                                layout.descriptor_bytes_consumed
                            ),
                            descriptor_padding_size=layout.descriptor_padding_size,
                            descriptor_runtime_zero_fill_size=(
                                layout.descriptor_runtime_zero_fill_size
                            ),
                            frame_bit_size=layout.frame_bit_size,
                            decoded_frame_byte_size=(
                                layout.decoded_frame_byte_size
                            ),
                            frame_byte_size=layout.frame_byte_size,
                            frame_trailing_size=layout.frame_trailing_size,
                            frame_count=frame_count,
                            duration_descriptor_value=descriptor[3],
                            duration_ticks=(
                                descriptor[3]
                                if descriptor[3] != 0xFF
                                else runtime_duration
                            ),
                            keyframe_step=descriptor[8] + 1,
                            duration_status=duration_status,
                            bitstream_padding_size=bitstream_padding_size,
                            companion_trailing_size=companion_trailing_size,
                            companion_trailing_sha1=(
                                hashlib.sha1(trailing_data).hexdigest()
                                if companion_trailing_size
                                else None
                            ),
                        )
                clip_records.append(clip_record)
            record.update(
                format="paired-animation-segment-table",
                structural_status="proven-even-paired-segments",
                segment_count=len(segments),
                clip_pair_count=len(segments) // 2,
                segments=segment_records,
                clips=clip_records,
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
            "logical_animation_route_count": logical_animation_route_count,
            "mapped_logical_animation_route_count": (
                mapped_logical_animation_route_count
            ),
            "direct_companion_logical_animation_route_count": (
                logical_animation_route_count - mapped_logical_animation_route_count
            ),
            "decoded_timeline_clip_count": decoded_clip_count,
            "empty_timeline_clip_count": empty_clip_count,
            "unresolved_timeline_clip_count": unresolved_clip_count,
            "decoded_frame_count": decoded_frame_count,
            "runtime_zero_filled_descriptor_count": (
                runtime_zero_filled_descriptor_count
            ),
            "extended_stride_clip_count": extended_stride_clip_count,
            "companion_trailing_clip_count": companion_trailing_clip_count,
            "companion_trailing_byte_count": companion_trailing_byte_count,
            "runtime_duration_override_clip_count": (
                runtime_duration_override_clip_count
            ),
            "resolved_runtime_duration_override_clip_count": (
                resolved_runtime_duration_override_clip_count
            ),
            "unresolved_runtime_duration_override_clip_count": (
                runtime_duration_override_clip_count
                - resolved_runtime_duration_override_clip_count
            ),
            "scale_channel_count": scale_channel_count,
            "scale_channel_clip_count": scale_channel_clip_count,
            "bitstream_alignment_padding_clip_count": (
                bitstream_alignment_padding_clip_count
            ),
            "bitstream_alignment_padding_byte_count": (
                bitstream_alignment_padding_byte_count
            ),
            "decoded_size": sum(record["decoded_size"] for record in records),
            "structural_status": "byte-identical-even-segment-pairs-proven",
            "semantic_status": (
                "all-nonempty-source-frame-channel-route-and-duration-layouts-"
                "decoded-runtime-playback-rate-unresolved"
            ),
            "animation_route_groups": list(route_groups),
            "runtime_evidence": {
                "loader": "func_1503D774",
                "loader_assembly": "asm/nonmatchings/game_6A3D0/func_1503D774.s",
                "bank_path": [2, "character-model-index"],
                "caller": "func_1503CF20",
                "index_limit": 187,
                "frame_decoder": "func_150A8A18",
                "quaternion_consumer": "func_150A8918",
                "frame_copy_and_stride_consumer": "func_1502D824",
                "descriptor_loader": "func_1505E0C4",
                "frame_stride_descriptor_offset": 5,
                "duration_descriptor_offset": 3,
                "keyframe_spacing_descriptor_offset": 8,
                "route_loader": "func_1503D660",
                "route_group_selector": "func_1503D5F0",
                "route_bank_path": [CHARACTER_ANIMATION_ROUTE_BANK, "group-index"],
                "route_consumer": "func_1505E650",
                "duration_override_consumer": "func_1505E0C4",
                "duration_table_address": (
                    f"0x{CHARACTER_ANIMATION_DURATION_TABLE_ADDRESS:08X}"
                ),
                "special_duration_address": (
                    f"0x{CHARACTER_ANIMATION_SPECIAL_DURATION_ADDRESS:08X}"
                ),
            },
            "entries": records,
        },
        files,
    )


def character_animation_clips_for_model(
    bank_entry: int,
    required_animation_channel_count: int,
    animation_manifest: dict[str, Any],
    animation_files: dict[str, bytes],
) -> tuple[tuple[CharacterAnimationClip, ...], int]:
    """Decode clips that supply every animation slot referenced by one bank-01 rig."""

    entry = next(
        (
            candidate
            for candidate in animation_manifest["entries"]
            if candidate["bank_entry"] == bank_entry and "clips" in candidate
        ),
        None,
    )
    if entry is None:
        return (), 0
    clips = []
    incompatible_count = 0
    for record in entry["clips"]:
        if record["timeline_status"] != "runtime-frame-layout-proven":
            continue
        if record["joint_count"] < required_animation_channel_count:
            incompatible_count += 1
            continue
        descriptor_name = (
            f"animations/bank-02/segments/{bank_entry:04d}-"
            f"{record['descriptor_segment_index']:04d}.bin"
        )
        bitstream_name = (
            f"animations/bank-02/segments/{bank_entry:04d}-"
            f"{record['bitstream_segment_index']:04d}.bin"
        )
        descriptor = animation_files[descriptor_name]
        bitstream = animation_files[bitstream_name]
        frames = tuple(
            decode_character_animation_frame(
                descriptor,
                bitstream[
                    index * record["frame_byte_size"]:
                    (index + 1) * record["frame_byte_size"]
                ],
                runtime_zero_fill_limit=15,
            )
            for index in range(record["frame_count"])
        )
        if len(frames) != record["frame_count"]:
            raise ValueError("bank-02 decoded animation frame count changed")
        clips.append(
            CharacterAnimationClip(
                pair_index=record["pair_index"],
                frames=frames,
                frame_byte_size=record["frame_byte_size"],
                bitstream_padding_size=record["bitstream_padding_size"],
                descriptor_runtime_zero_fill_size=(
                    record["descriptor_runtime_zero_fill_size"]
                ),
                companion_trailing_size=record.get("companion_trailing_size", 0),
                companion_trailing_sha1=record.get("companion_trailing_sha1"),
                duration_ticks=record.get("duration_ticks"),
                keyframe_step=record.get("keyframe_step", descriptor[8] + 1),
                duration_status=record.get(
                    "duration_status",
                    "descriptor-duration-and-keyframe-spacing",
                ),
                logical_animation_indices=tuple(
                    record.get("logical_animation_indices", ())
                ),
            )
        )
    return tuple(clips), incompatible_count


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
                    "face_normal_corner_count": (
                        len(geometry.face_normal_bytes) * 3
                    ),
                    "source_normal_corner_count": sum(
                        normal is not None and normal != (0, 0, 0)
                        for face in geometry.face_normal_bytes
                        for normal in face
                    ),
                    "zero_source_normal_corner_count": sum(
                        normal == (0, 0, 0)
                        for face in geometry.face_normal_bytes
                        for normal in face
                    ),
                    "unavailable_source_normal_corner_count": sum(
                        normal is None
                        for face in geometry.face_normal_bytes
                        for normal in face
                    ),
                    "custom_normal_command_count": (
                        geometry.custom_normal_command_count
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
                        "render_tiles": [
                            {
                                "tile": tile_index,
                                "command": [
                                    f"0x{command:08X}",
                                    f"0x{argument:08X}",
                                ],
                                "tmem_byte_offset": (command & 0x1FF) * 8,
                            }
                            for tile_index, command, argument in run.render_tiles
                        ],
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
            "descriptors-proven-custom-movemem-auxiliary-consumer-and-animation-"
            "structure-proven-normal-encoding-emulator-validated-material-color-"
            "and-lighting-state-runtime-dependent"
            if bank_index == 0x01
            else (
                "primary-geometry-material-uv-vertex-color-animation-and-custom-"
                "normal-stream-proven-runtime-segment-8-render-state-family-proven-"
                "selection-unresolved"
                if bank_index in (0x03, 0x04)
                else "primary-geometry-material-and-uv-proven-runtime-material-"
                "selection-unresolved"
            )
        ),
        "face_normal_model_count": sum(
            bool(segment.get("geometry", {}).get("face_normal_corner_count"))
            for record in records
            for segment in record["segments"]
        ),
        "custom_normal_command_count_all_models": sum(
            segment.get("geometry", {}).get("custom_normal_command_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "face_normal_corner_count": sum(
            segment.get("geometry", {}).get("face_normal_corner_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "source_normal_corner_count": sum(
            segment.get("geometry", {}).get("source_normal_corner_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "zero_source_normal_corner_count": sum(
            segment.get("geometry", {}).get("zero_source_normal_corner_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "unavailable_source_normal_corner_count": sum(
            segment.get("geometry", {}).get(
                "unavailable_source_normal_corner_count", 0
            )
            for record in records
            for segment in record["segments"]
        ),
        "character_texture_descriptor_count": sum(
            segment.get("geometry", {})
            .get("character_layout", {})
            .get("texture_descriptor_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "custom_movemem_auxiliary_model_count": sum(
            bool(
                segment.get("geometry", {})
                .get("character_layout", {})
                .get("custom_movemem_command_count", 0)
            )
            for record in records
            for segment in record["segments"]
        ),
        "custom_movemem_command_count": sum(
            segment.get("geometry", {})
            .get("character_layout", {})
            .get("custom_movemem_command_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "custom_movemem_auxiliary_decoded_size": sum(
            next(
                (
                    section["size"]
                    for section in segment.get("geometry", {})
                    .get("character_layout", {})
                    .get("sections", [])
                    if section["index"] == 4
                ),
                0,
            )
            for record in records
            for segment in record["segments"]
        ),
        "character_face_normal_corner_count": sum(
            segment.get("geometry", {})
            .get("character_layout", {})
            .get("face_normal_corner_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "character_source_normal_corner_count": sum(
            segment.get("geometry", {})
            .get("character_layout", {})
            .get("source_normal_corner_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "character_zero_source_normal_corner_count": sum(
            segment.get("geometry", {})
            .get("character_layout", {})
            .get("zero_source_normal_corner_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "character_unavailable_source_normal_corner_count": sum(
            segment.get("geometry", {})
            .get("character_layout", {})
            .get("unavailable_source_normal_corner_count", 0)
            for record in records
            for segment in record["segments"]
        ),
        "procedural_animation_joint_table_count": sum(
            bool(
                segment.get("geometry", {})
                .get("character_layout", {})
                .get("procedural_animation_joint_index_count", 0)
            )
            for record in records
            for segment in record["segments"]
        ),
        "procedural_animation_joint_index_count": sum(
            segment.get("geometry", {})
            .get("character_layout", {})
            .get("procedural_animation_joint_index_count", 0)
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
                    "custom_movemem_scanner": "func_1503D368",
                    "custom_movemem_relocator": "func_1503D438",
                    "custom_movemem_command": "0xDC38000E",
                    "custom_movemem_semantics": (
                        "signed-s8-x-y-normal-components-indexed-by-vertex-cache-slot"
                    ),
                    "custom_vertex_normal_z": "signed-low-byte-of-vertex-flag",
                    "custom_vertex_normal_emulator_reference": (
                        "GLideN64/src/uCodes/F3DEX2CBFD.cpp-and-src/gSP.cpp"
                    ),
                    "material_color_state": CHARACTER_RUNTIME_COLOR_STATE,
                    "secondary_display_list_consumer": "func_1502CCFC",
                    "procedural_joint_lookup": "func_1503DA3C",
                    "procedural_joint_caller": "func_15033FE0",
                    "procedural_joint_override_builder": "func_15034860",
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


def verify_collision_output(output: Path, manifest: dict[str, Any]) -> None:
    """Verify the generated collision views and their exact source records."""

    records = manifest["models"]
    if manifest["model_count"] != len(records):
        raise ValueError("collision model count does not match its records")
    if manifest["triangle_record_count"] != sum(
        record["triangle_record_count"] for record in records
    ):
        raise ValueError("collision triangle total does not match its records")
    if manifest["surface_record_count"] != sum(
        record["surface_record_count"] for record in records
    ):
        raise ValueError("collision surface total does not match its records")
    if manifest["preview_face_count"] != sum(
        record["preview_face_count"] for record in records
    ):
        raise ValueError("collision preview face total does not match its records")
    surface_words = {
        word for record in records for word in record["surface_words"]
    }
    if manifest["unique_surface_word_count"] != len(surface_words):
        raise ValueError("collision surface-word total does not match its records")
    placement_scenes = manifest["placement_scenes"]
    if manifest["placement_collision_scene_count"] != len(placement_scenes):
        raise ValueError("placement collision scene count changed")
    if manifest["placement_collision_resolved_record_count"] != sum(
        scene["placement_count"] for scene in placement_scenes
    ):
        raise ValueError("placement collision record total changed")
    if manifest["placement_collision_source_face_count"] != sum(
        scene["source_face_count"] for scene in placement_scenes
    ):
        raise ValueError("placement collision source-face total changed")
    if manifest["placement_collision_preview_face_count"] != sum(
        scene["preview_face_count"] for scene in placement_scenes
    ):
        raise ValueError("placement collision preview-face total changed")

    for record in records:
        triangle_path = output / record["triangle_records_file"]
        gltf_path = output / record["gltf_file"]
        binary_path = output / record["binary_file"]
        triangle_data = triangle_path.read_bytes()
        gltf_data = gltf_path.read_bytes()
        binary_data = binary_path.read_bytes()
        for data, key in (
            (triangle_data, "triangle_records_sha1"),
            (gltf_data, "gltf_sha1"),
            (binary_data, "binary_sha1"),
        ):
            if hashlib.sha1(data).hexdigest() != record[key]:
                raise ValueError(
                    f"collision output hash changed for bank-04 entry "
                    f"{record['bank_entry']}"
                )
        if len(triangle_data) != record["triangle_record_count"] * 12:
            raise ValueError("collision triangle records have the wrong size")
        if record["surface_records_file"] is not None:
            surface_data = (output / record["surface_records_file"]).read_bytes()
            if hashlib.sha1(surface_data).hexdigest() != record[
                "surface_records_sha1"
            ]:
                raise ValueError("collision surface output hash changed")
            if len(surface_data) != record["surface_record_count"] * 4:
                raise ValueError("collision surface records have the wrong size")
        elif record["surface_record_count"] or record["surface_records_sha1"]:
            raise ValueError("collision record has inconsistent absent surface data")
        document = json.loads(gltf_data)
        if document["buffers"] != [
            {
                "uri": Path(record["binary_file"]).name,
                "byteLength": len(binary_data),
            }
        ]:
            raise ValueError("collision glTF buffer declaration changed")
        primitives = document["meshes"][0]["primitives"]
        if len(primitives) != record["preview_surface_word_count"]:
            raise ValueError("collision glTF surface grouping changed")
        if sum(
            len(primitive["extras"]["sourceFaceIndices"])
            for primitive in primitives
        ) != record["preview_face_count"]:
            raise ValueError("collision glTF face provenance changed")

    for scene in placement_scenes:
        gltf_data = (output / scene["gltf_file"]).read_bytes()
        binary_data = (output / scene["binary_file"]).read_bytes()
        if hashlib.sha1(gltf_data).hexdigest() != scene["gltf_sha1"]:
            raise ValueError("placement collision glTF hash changed")
        if hashlib.sha1(binary_data).hexdigest() != scene["binary_sha1"]:
            raise ValueError("placement collision binary hash changed")
        document = json.loads(gltf_data)
        if document["buffers"][0]["byteLength"] != len(binary_data):
            raise ValueError("placement collision glTF buffer size changed")
        if len(document["nodes"]) != scene["placement_count"]:
            raise ValueError("placement collision glTF node count changed")

    written = json.loads((output / "manifest.json").read_text(encoding="utf-8"))
    if written != manifest:
        raise ValueError("collision manifest did not round-trip through JSON")


def extract_bank_04_collision(
    profile: str,
    rom_argument: Path | None,
    output: Path,
    force: bool,
) -> dict[str, Any]:
    """Export bank-04 collision triangles and exact per-face surface words."""

    rom_path, source_order, digest, bundles, _ = load_model_bundles(
        profile, rom_argument, 0x04
    )
    prepare_output(output, force)
    records = []
    for bundle in bundles:
        if not bundle.segments or not bundle.segments[0].data:
            continue
        segment = bundle.segments[0]
        geometry = parse_model_geometry(segment.data)
        if geometry.tertiary_region is None:
            continue
        surface_words = bank_04_collision_surface_words(segment, geometry)
        triangle_data = encode_collision_triangle_offsets(geometry)
        region = geometry.tertiary_region
        surface_data = segment.data[
            region.offset + 8 : region.offset + region.size
        ]
        if surface_data != b"".join(
            struct.pack(">I", word) for word in surface_words
        ):
            raise ValueError("collision surface words did not preserve source bytes")
        gltf_data, binary_data, omitted_faces = encode_collision_gltf(
            bundle.index, geometry, surface_words
        )
        stem = f"{bundle.index:04d}-00"
        triangle_file = f"records/{stem}-triangles.bin"
        surface_file = f"records/{stem}-surfaces.bin"
        gltf_file = f"geometry/{stem}-collision.gltf"
        binary_file = f"geometry/{stem}-collision.bin"
        for relative_path, data in (
            (triangle_file, triangle_data),
            (surface_file, surface_data),
            (gltf_file, gltf_data),
            (binary_file, binary_data),
        ):
            path = output / relative_path
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)
        omitted_set = set(omitted_faces)
        preview_surface_words = {
            surface_words[index]
            for index in range(len(surface_words))
            if index not in omitted_set
        }
        records.append(
            {
                "bank_entry": bundle.index,
                "collision_layer": "primary-terrain",
                "source_segment": 0,
                "source_model_sha1": hashlib.sha1(segment.data).hexdigest(),
                "vertex_count": len(geometry.vertices),
                "source_face_count": len(geometry.faces),
                "triangle_record_count": len(geometry.faces),
                "triangle_record_shape": (
                    "three-big-endian-u32-model-relative-vertex-byte-offsets"
                ),
                "triangle_records_file": triangle_file,
                "triangle_records_sha1": hashlib.sha1(triangle_data).hexdigest(),
                "surface_record_count": len(surface_words),
                "surface_record_shape": "one-big-endian-u32-per-source-face",
                "surface_records_file": surface_file,
                "surface_records_sha1": hashlib.sha1(surface_data).hexdigest(),
                "surface_words": [
                    f"0x{word:08X}" for word in sorted(set(surface_words))
                ],
                "unique_surface_word_count": len(set(surface_words)),
                "preview_face_count": len(geometry.faces) - len(omitted_faces),
                "preview_surface_word_count": len(preview_surface_words),
                "zero_area_source_face_indices": list(omitted_faces),
                "gltf_file": gltf_file,
                "gltf_sha1": hashlib.sha1(gltf_data).hexdigest(),
                "binary_file": binary_file,
                "binary_sha1": hashlib.sha1(binary_data).hexdigest(),
            }
        )

        if len(bundle.segments) <= 3 or not bundle.segments[3].data:
            continue
        secondary_segment = bundle.segments[3]
        secondary_geometry = parse_model_geometry(secondary_segment.data)
        secondary_triangles = encode_collision_triangle_offsets(
            secondary_geometry
        )
        secondary_gltf, secondary_binary, secondary_omitted = (
            encode_collision_gltf(
                bundle.index,
                secondary_geometry,
                None,
                segment_index=3,
            )
        )
        secondary_stem = f"{bundle.index:04d}-03"
        secondary_triangle_file = (
            f"records/{secondary_stem}-triangles.bin"
        )
        secondary_gltf_file = (
            f"geometry/{secondary_stem}-collision.gltf"
        )
        secondary_binary_file = (
            f"geometry/{secondary_stem}-collision.bin"
        )
        for relative_path, data in (
            (secondary_triangle_file, secondary_triangles),
            (secondary_gltf_file, secondary_gltf),
            (secondary_binary_file, secondary_binary),
        ):
            path = output / relative_path
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)
        records.append(
            {
                "bank_entry": bundle.index,
                "collision_layer": "secondary-terrain",
                "source_segment": 3,
                "source_model_sha1": hashlib.sha1(
                    secondary_segment.data
                ).hexdigest(),
                "vertex_count": len(secondary_geometry.vertices),
                "source_face_count": len(secondary_geometry.faces),
                "triangle_record_count": len(secondary_geometry.faces),
                "triangle_record_shape": (
                    "three-big-endian-u32-model-relative-vertex-byte-offsets"
                ),
                "triangle_records_file": secondary_triangle_file,
                "triangle_records_sha1": hashlib.sha1(
                    secondary_triangles
                ).hexdigest(),
                "surface_record_count": 0,
                "surface_record_shape": None,
                "surface_records_file": None,
                "surface_records_sha1": None,
                "surface_words": [],
                "unique_surface_word_count": 0,
                "preview_face_count": len(secondary_geometry.faces)
                - len(secondary_omitted),
                "preview_surface_word_count": (
                    1 if len(secondary_geometry.faces) > len(secondary_omitted) else 0
                ),
                "zero_area_source_face_indices": list(secondary_omitted),
                "gltf_file": secondary_gltf_file,
                "gltf_sha1": hashlib.sha1(secondary_gltf).hexdigest(),
                "binary_file": secondary_binary_file,
                "binary_sha1": hashlib.sha1(secondary_binary).hexdigest(),
            }
        )

    placement_manifest, _ = load_object_placement_manifest(
        profile, rom_argument, include_files=False
    )
    _, _, bank_03_digest, bank_03_bundles, _ = load_model_bundles(
        profile, rom_argument, 0x03
    )
    if bank_03_digest != digest:
        raise ValueError("placement collision models came from a different ROM")
    bundles_by_bank = {
        0x03: {bundle.index: bundle for bundle in bank_03_bundles},
        0x04: {bundle.index: bundle for bundle in bundles},
    }
    collision_sources: dict[
        tuple[int, int, int], tuple[dict[str, Any], bytes, int, int]
    ] = {}

    def collision_source(
        bank_index: int, entry_index: int, segment_index: int
    ) -> tuple[dict[str, Any], bytes, int, int]:
        key = (bank_index, entry_index, segment_index)
        if key not in collision_sources:
            bundle = bundles_by_bank[bank_index][entry_index]
            segment = bundle.segments[segment_index]
            geometry = parse_model_geometry(segment.data)
            gltf_data, binary_data, omitted_faces = encode_collision_gltf(
                entry_index,
                geometry,
                None,
                segment_index=segment_index,
                bank_index=bank_index,
            )
            collision_sources[key] = (
                json.loads(gltf_data),
                binary_data,
                len(geometry.faces),
                len(geometry.faces) - len(omitted_faces),
            )
        return collision_sources[key]

    placement_scenes = []
    unresolved_placement_scenes = []
    for scene in placement_manifest["scenes"]:
        included = [
            record for record in scene["records"] if record["collision_included"]
        ]
        resolved = [
            record
            for record in included
            if record["model_resolution_status"]
            in ("resolved-bank-03-model", "resolved-bank-04-segment")
        ]
        unresolved = [record for record in included if record not in resolved]
        if unresolved:
            unresolved_placement_scenes.append(
                {
                    "placement_bank": scene["bank_index"],
                    "scene_index": scene["scene_index"],
                    "unresolved_record_indices": [
                        record["index"] for record in unresolved
                    ],
                }
            )
        if not resolved:
            continue
        placement_bank = scene["bank_index"]
        model_bank = 0x03 if placement_bank == 0x0C else 0x04
        model_index_field = (
            "model_index" if placement_bank == 0x0C else "dispatch_index"
        )
        model_gltfs = {}
        source_face_count = preview_face_count = 0
        for record in resolved:
            model_index = record[model_index_field]
            source_segment = 0 if model_bank == 0x03 else model_index
            source = collision_source(
                model_bank,
                record["model_source"][1],
                source_segment,
            )
            model_gltfs[model_index] = (source[0], source[1])
            source_face_count += source[2]
            preview_face_count += source[3]
        scene_gltf, scene_binary = encode_placement_scene_gltf(
            scene["scene_index"],
            resolved,
            model_gltfs,
            placement_bank=placement_bank,
            model_bank=model_bank,
            model_index_field=model_index_field,
        )
        scene_document = json.loads(scene_gltf)
        scene_document["extras"].update(
            {
                "purpose": "runtime-placement-collision-array-preview",
                "collisionFilter": "source-byte-0x32-mask-0x60-not-equal-0x20",
                "sourceFaceCount": source_face_count,
                "previewFaceCount": preview_face_count,
            }
        )
        scene_gltf = (json.dumps(scene_document, indent=2) + "\n").encode("utf-8")
        stem = f"bank-{placement_bank:02x}/scene-{scene['scene_index']:02d}"
        gltf_file = f"scenes/{stem}.gltf"
        binary_file = f"scenes/{stem}.bin"
        for relative_path, data in (
            (gltf_file, scene_gltf),
            (binary_file, scene_binary),
        ):
            path = output / relative_path
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)
        placement_scenes.append(
            {
                "placement_bank": placement_bank,
                "model_bank": model_bank,
                "scene_index": scene["scene_index"],
                "placement_count": len(resolved),
                "source_face_count": source_face_count,
                "preview_face_count": preview_face_count,
                "gltf_file": gltf_file,
                "gltf_sha1": hashlib.sha1(scene_gltf).hexdigest(),
                "binary_file": binary_file,
                "binary_sha1": hashlib.sha1(scene_binary).hexdigest(),
            }
        )

    manifest = {
        "schema_version": 1,
        "family": "bank-04-collision-and-surface-records",
        "profile": profile,
        "source_rom": manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": digest,
        "model_count": len(records),
        "primary_terrain_model_count": sum(
            record["collision_layer"] == "primary-terrain" for record in records
        ),
        "secondary_terrain_model_count": sum(
            record["collision_layer"] == "secondary-terrain" for record in records
        ),
        "triangle_record_count": sum(
            record["triangle_record_count"] for record in records
        ),
        "surface_record_count": sum(
            record["surface_record_count"] for record in records
        ),
        "preview_face_count": sum(
            record["preview_face_count"] for record in records
        ),
        "zero_area_source_face_count": sum(
            len(record["zero_area_source_face_indices"]) for record in records
        ),
        "unique_surface_word_count": len(
            {word for record in records for word in record["surface_words"]}
        ),
        "placement_collision_source_record_count": placement_manifest[
            "record_count"
        ],
        "placement_collision_included_record_count": sum(
            record["collision_included"]
            for scene in placement_manifest["scenes"]
            for record in scene["records"]
        ),
        "placement_collision_excluded_record_count": sum(
            not record["collision_included"]
            for scene in placement_manifest["scenes"]
            for record in scene["records"]
        ),
        "placement_collision_resolved_record_count": sum(
            scene["placement_count"] for scene in placement_scenes
        ),
        "placement_collision_scene_count": len(placement_scenes),
        "placement_collision_source_face_count": sum(
            scene["source_face_count"] for scene in placement_scenes
        ),
        "placement_collision_preview_face_count": sum(
            scene["preview_face_count"] for scene in placement_scenes
        ),
        "unresolved_placement_collision_scene_count": len(
            unresolved_placement_scenes
        ),
        "unresolved_placement_collision_scenes": unresolved_placement_scenes,
        "runtime_evidence": {
            "triangle_count_and_allocation": "func_15002754",
            "display_list_triangle_record_builder": "func_15001460",
            "collision_source_dispatch": "func_15003668",
            "surface_table_pointer_setup": "func_150039BC",
            "triangle_runtime_record": (
                "three relocated vertex pointers; exported record uses model-relative "
                "vertex byte offsets so it is portable"
            ),
            "surface_source_record": (
                "exact four-byte ROM word following the eight-byte primary table header"
            ),
            "secondary_terrain_surface_status": (
                "no corresponding per-face table is installed by func_150031EC"
            ),
            "placement_collision_filter": (
                "func_15003668 includes runtime object +0x4F when flags & 0x60 "
                "is not 0x20; func_150039E0 copies source record byte 0x32 there"
            ),
        },
        "surface_semantic_status": "exact-values-preserved-meanings-unresolved",
        "models": records,
        "placement_scenes": placement_scenes,
    }
    if (
        manifest["primary_terrain_model_count"] != 58
        or manifest["secondary_terrain_model_count"] != 38
        or manifest["triangle_record_count"] != 98479
        or manifest["surface_record_count"] != 97071
        or manifest["unique_surface_word_count"] != 176
        or manifest["preview_face_count"] != 98291
        or manifest["zero_area_source_face_count"] != 188
        or manifest["placement_collision_source_record_count"] != 1238
        or manifest["placement_collision_included_record_count"] != 1066
        or manifest["placement_collision_excluded_record_count"] != 172
        or manifest["placement_collision_resolved_record_count"] != 1055
        or manifest["placement_collision_scene_count"] != 98
        or manifest["placement_collision_source_face_count"] != 42901
        or manifest["placement_collision_preview_face_count"] != 42885
        or manifest["unresolved_placement_collision_scene_count"] != 2
    ):
        raise ValueError("US bank-04 collision inventory changed")
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    (output / "README.txt").write_text(
        "Conker bank-04 collision previews and surface records\n\n"
        "Import a file from geometry/ into Blender with File > Import > glTF 2.0, "
        "then switch to Material Preview. Primary-terrain colours identify distinct "
        "exact 32-bit surface words; they are deliberately diagnostic and are not "
        "game materials. Secondary-terrain meshes are blue-grey because the runtime "
        "does not install an associated per-face surface table for that layer.\n\n"
        "records/*-surfaces.bin contains the byte-identical ROM surface words after "
        "the eight-byte table header. records/*-triangles.bin contains a portable "
        "equivalent of the runtime 12-byte triangle-pointer records: three big-endian "
        "model-relative vertex byte offsets per face. At runtime those offsets become "
        "relocated pointers and separate bounds arrays are generated.\n\n"
        "The scenes/ directory contains transformed placement-collision previews. "
        "They apply the runtime-proven source byte 0x32 exclusion mask and preserve "
        "the position, YZX rotation, and scale transforms. Scenes 17 and 62 retain "
        "eleven included records without previews because their bank-04 bundles are "
        "absent.\n",
        encoding="utf-8",
    )
    verify_collision_output(output, manifest)
    return manifest


def runtime_material_inventory(
    profile: str, rom_argument: Path | None
) -> tuple[str, dict[tuple[int, int, int, int], dict[str, Any]]]:
    """Build the current ROM-backed identity set accepted by runtime traces."""

    digest = None
    inventory: dict[tuple[int, int, int, int], dict[str, Any]] = {}
    for bank_index in BANK_INDICES:
        _, _, bank_digest, bundles, _ = load_model_bundles(
            profile, rom_argument, bank_index
        )
        if digest is None:
            digest = bank_digest
        elif digest != bank_digest:
            raise ValueError("runtime material banks were loaded from different ROMs")
        for bundle in bundles:
            for segment in bundle.segments:
                if not segment.data:
                    continue
                geometry = parse_geometry_for_bank(segment.data, bank_index)
                model_sha1 = hashlib.sha1(segment.data).hexdigest()
                for run_index, run in enumerate(geometry.material_runs):
                    inventory[(bank_index, bundle.index, segment.index, run_index)] = {
                        "model_sha1": model_sha1,
                        "first_face": run.first_face,
                        "face_count": run.face_count,
                        "matrix_index": run.matrix_index,
                    }
    if digest is None:
        raise ValueError("runtime material inventory is empty")
    return digest, inventory


def verify_runtime_material_output(output: Path, manifest: dict[str, Any]) -> None:
    materials = manifest["materials"]
    if manifest["material_record_count"] != len(materials):
        raise ValueError("runtime material record count changed")
    if manifest["variant_count"] != sum(
        len(record["variants"]) for record in materials
    ):
        raise ValueError("runtime material variant count changed")
    if manifest["material_assignment_observation_count"] != sum(
        variant["observation_count"]
        for record in materials
        for variant in record["variants"]
    ):
        raise ValueError("runtime material observation count changed")
    keys = [
        (
            record["bank"],
            record["entry"],
            record["segment"],
            record["material_run"],
        )
        for record in materials
    ]
    if len(keys) != len(set(keys)):
        raise ValueError("runtime material identities are not unique")
    for record in materials:
        if record["variant_count"] != len(record["variants"]):
            raise ValueError("runtime material per-record variant count changed")
        for variant in record["variants"]:
            digest = hashlib.sha256(
                json.dumps(
                    variant["state"], sort_keys=True, separators=(",", ":")
                ).encode("utf-8")
            ).hexdigest()
            if digest != variant["material_state_hash"]:
                raise ValueError("runtime material state hash changed")
            if translate_runtime_material_state(variant["state"]) != variant[
                "gltf_translation"
            ]:
                raise ValueError("runtime material glTF translation changed")
            contexts = variant.get("lighting_contexts", [])
            if variant.get("lighting_context_count") != len(contexts):
                raise ValueError("runtime lighting context count changed")
            for context in contexts:
                hashed = {
                    key: context[key]
                    for key in (
                        "matrix_sha256",
                        "matrix_layout",
                        "model_view_rows",
                        "matrix_translation",
                        "normal_stream",
                    )
                }
                digest = hashlib.sha256(
                    json.dumps(
                        hashed, sort_keys=True, separators=(",", ":")
                    ).encode("utf-8")
                ).hexdigest()
                if digest != context.get("lighting_context_hash"):
                    raise ValueError("runtime lighting context hash changed")
    if manifest.get("lighting_context_count") != sum(
        variant.get("lighting_context_count", 0)
        for record in materials
        for variant in record["variants"]
    ):
        raise ValueError("runtime lighting context total changed")
    source_traces = manifest.get("source_traces", [])
    for field in (
        "nested_display_list_call_count",
        "resolved_address_display_list_call_count",
        "decoder_unresolved_display_list_call_count",
        "segment_8_display_list_call_count",
        "resolved_segment_8_display_list_call_count",
    ):
        if manifest.get(field) != sum(
            int(trace.get(field, 0)) for trace in source_traces
        ):
            raise ValueError(f"runtime material {field} total changed")
    segment_8_addresses = sorted(
        {
            address
            for trace in source_traces
            for address in trace.get(
                "resolved_segment_8_display_list_addresses", []
            )
        }
    )
    if (
        manifest.get("resolved_segment_8_display_list_addresses")
        != segment_8_addresses
        or manifest.get("resolved_segment_8_display_list_count")
        != len(segment_8_addresses)
    ):
        raise ValueError("runtime material segment-8 address inventory changed")
    written = json.loads((output / "manifest.json").read_text(encoding="utf-8"))
    if written != manifest:
        raise ValueError("runtime material manifest did not round-trip through JSON")


def extract_runtime_materials(
    profile: str,
    rom_argument: Path | None,
    trace_paths: tuple[Path, ...],
    output: Path,
    force: bool,
) -> dict[str, Any]:
    """Aggregate correlated draw states into reusable static material variants."""

    if not trace_paths:
        raise ValueError("at least one --trace JSONL file is required")
    digest, inventory = runtime_material_inventory(profile, rom_argument)
    prepare_output(output, force)
    records: dict[tuple[int, int, int, int], dict[str, Any]] = {}
    trace_records = []
    correlation_count = 0
    correlated_draw_observation_count = 0
    assignment_observation_count = 0
    nested_display_list_call_count = 0
    resolved_display_list_call_count = 0
    unresolved_display_list_call_count = 0
    segment_8_display_list_call_count = 0
    resolved_segment_8_display_list_call_count = 0
    resolved_segment_8_display_list_addresses: set[int] = set()
    for source_path in trace_paths:
        path = source_path if source_path.is_absolute() else ROOT / source_path
        data = path.read_bytes()
        lines = [json.loads(line) for line in data.splitlines() if line.strip()]
        if not lines or lines[0].get("record_type") != "session":
            raise ValueError(f"runtime material trace has no session record: {path}")
        if any(line.get("schema") != "conker.model-draw-state-trace/v1" for line in lines):
            raise ValueError(f"runtime material trace schema changed: {path}")
        trace_digest = lines[0].get("normalized_sha1")
        if trace_digest is not None and trace_digest != digest:
            raise ValueError(f"runtime material trace belongs to a different ROM: {path}")
        events = [line for line in lines if line.get("record_type") == "draw_state"]
        trace_nested_calls = [
            call
            for event in events
            for call in event.get("state", {})
            .get("rdp", {})
            .get("nested_display_lists", [])
        ]
        trace_unresolved_calls = sum(
            len(
                event.get("state", {})
                .get("rdp", {})
                .get("unresolved_display_list_targets", [])
            )
            for event in events
        )
        trace_segment_8_calls = [
            call
            for call in trace_nested_calls
            if int(call.get("address", 0)) >> 24 == 8
        ]
        trace_resolved_segment_8_addresses = {
            int(call["resolved_address"])
            for call in trace_segment_8_calls
            if call.get("resolved_address") is not None
        }
        trace_resolved_calls = sum(
            call.get("resolved_address") is not None for call in trace_nested_calls
        )
        trace_resolved_segment_8_calls = sum(
            call.get("resolved_address") is not None
            for call in trace_segment_8_calls
        )
        nested_display_list_call_count += len(trace_nested_calls)
        resolved_display_list_call_count += trace_resolved_calls
        unresolved_display_list_call_count += trace_unresolved_calls
        segment_8_display_list_call_count += len(trace_segment_8_calls)
        resolved_segment_8_display_list_call_count += (
            trace_resolved_segment_8_calls
        )
        resolved_segment_8_display_list_addresses.update(
            trace_resolved_segment_8_addresses
        )
        trace_records.append(
            {
                "file": display_path(path),
                "sha256": hashlib.sha256(data).hexdigest(),
                "spec_name": lines[0].get("spec_name"),
                "normalized_sha1": trace_digest,
                "tool_revisions": lines[0].get("tool_revisions"),
                "event_count": len(events),
                "nested_display_list_call_count": len(trace_nested_calls),
                "resolved_address_display_list_call_count": trace_resolved_calls,
                "decoder_unresolved_display_list_call_count": trace_unresolved_calls,
                "segment_8_display_list_call_count": len(trace_segment_8_calls),
                "resolved_segment_8_display_list_call_count": (
                    trace_resolved_segment_8_calls
                ),
                "resolved_segment_8_display_list_addresses": [
                    f"0x{address:08X}"
                    for address in sorted(trace_resolved_segment_8_addresses)
                ],
            }
        )
        for event_index, event in enumerate(events):
            event_state = event.get("state", {})
            rdp = event_state.get("rdp", {})
            matrices = event_state.get("joint_matrices", [])
            draw_runs = rdp.get("draw_runs", [])
            for correlation_index, correlation in enumerate(
                rdp.get("material_run_correlations", [])
            ):
                if correlation.get("status") not in (
                    "unique",
                    "equivalent-material-aliases",
                ):
                    continue
                draw_indices = correlation.get("draw_run_indices", [])
                correlation_count += 1
                correlated_draw_observation_count += len(draw_indices)
                candidate_keys = set()
                for candidate in correlation.get("candidates", []):
                    material = candidate.get("material_run") or {}
                    key = (
                        int(candidate["bank"]),
                        int(candidate["entry"]),
                        int(candidate["segment"]),
                        int(material["index"]),
                    )
                    current = inventory.get(key)
                    if current is None:
                        raise ValueError(f"runtime material identity is absent: {key}")
                    candidate_sha1 = candidate.get("model_sha1")
                    if candidate_sha1 is not None and candidate_sha1 != current[
                        "model_sha1"
                    ]:
                        raise ValueError(f"runtime material model hash changed: {key}")
                    if any(
                        material.get(field) != current[field]
                        for field in ("first_face", "face_count", "matrix_index")
                    ):
                        raise ValueError(f"runtime material run boundary changed: {key}")
                    candidate_keys.add(key)
                for draw_index in draw_indices:
                    if not 0 <= int(draw_index) < len(draw_runs):
                        raise ValueError("runtime material draw index is out of range")
                    draw = draw_runs[int(draw_index)]
                    source_state = draw.get("state", {})
                    material_state = {
                        "texture": source_state.get("texture"),
                        "tiles": source_state.get("tiles"),
                        "combine_mode": source_state.get("combine_mode"),
                        "other_mode": source_state.get("other_mode"),
                        "colours": source_state.get("colours"),
                        "geometry_mode": source_state.get("geometry_mode"),
                        "lighting_enabled": source_state.get("lighting_enabled"),
                        "lights": source_state.get("lights"),
                    }
                    material_hash = hashlib.sha256(
                        json.dumps(
                            material_state, sort_keys=True, separators=(",", ":")
                        ).encode("utf-8")
                    ).hexdigest()
                    translation = translate_runtime_material_state(material_state)
                    lighting_context = (
                        runtime_lighting_context(draw, matrices)
                        if material_state.get("lighting_enabled")
                        else None
                    )
                    for key in candidate_keys:
                        assignment_observation_count += 1
                        current = inventory[key]
                        record = records.setdefault(
                            key,
                            {
                                "bank": key[0],
                                "entry": key[1],
                                "segment": key[2],
                                "material_run": key[3],
                                "model_sha1": current["model_sha1"],
                                "source_first_face": current["first_face"],
                                "source_face_count": current["face_count"],
                                "matrix_index": current["matrix_index"],
                                "variants": {},
                            },
                        )
                        variant = record["variants"].setdefault(
                            material_hash,
                            {
                                "material_state_hash": material_hash,
                                "observation_count": 0,
                                "state": material_state,
                                "gltf_translation": translation,
                                "lighting_contexts": {},
                                "evidence": [],
                            },
                        )
                        variant["observation_count"] += 1
                        if lighting_context is not None:
                            context_hash = lighting_context["lighting_context_hash"]
                            context = variant["lighting_contexts"].setdefault(
                                context_hash,
                                {
                                    **lighting_context,
                                    "observation_count": 0,
                                },
                            )
                            context["observation_count"] += 1
                        evidence = {
                            "trace": display_path(path),
                            "event_index": event_index,
                            "hit_index": event.get("hit_index"),
                            "event_render_state_hash": event.get("render_state_hash"),
                            "material_correlation_index": correlation_index,
                            "draw_run_index": int(draw_index),
                            "source_material_state_hash": draw.get(
                                "material_state_hash"
                            ),
                        }
                        if evidence not in variant["evidence"]:
                            variant["evidence"].append(evidence)
    material_records = []
    status_counts: dict[str, int] = {}
    for key in sorted(records):
        record = records[key]
        variants = [record["variants"][name] for name in sorted(record["variants"])]
        for variant in variants:
            variant["lighting_contexts"] = [
                variant["lighting_contexts"][name]
                for name in sorted(variant["lighting_contexts"])
            ]
            variant["lighting_context_count"] = len(
                variant["lighting_contexts"]
            )
            status = variant["gltf_translation"]["status"]
            status_counts[status] = status_counts.get(status, 0) + 1
        record["variants"] = variants
        record["variant_count"] = len(variants)
        record["observation_count"] = sum(
            variant["observation_count"] for variant in variants
        )
        material_records.append(record)
    manifest = {
        "schema_version": 1,
        "family": "runtime-correlated-model-materials",
        "profile": profile,
        "normalized_sha1": digest,
        "source_traces": trace_records,
        "trace_file_count": len(trace_records),
        "nested_display_list_call_count": nested_display_list_call_count,
        "resolved_address_display_list_call_count": (
            resolved_display_list_call_count
        ),
        "decoder_unresolved_display_list_call_count": (
            unresolved_display_list_call_count
        ),
        "segment_8_display_list_call_count": segment_8_display_list_call_count,
        "resolved_segment_8_display_list_call_count": (
            resolved_segment_8_display_list_call_count
        ),
        "resolved_segment_8_display_list_count": len(
            resolved_segment_8_display_list_addresses
        ),
        "resolved_segment_8_display_list_addresses": [
            f"0x{address:08X}"
            for address in sorted(resolved_segment_8_display_list_addresses)
        ],
        "correlation_count": correlation_count,
        "correlated_draw_observation_count": correlated_draw_observation_count,
        "material_assignment_observation_count": assignment_observation_count,
        "material_record_count": len(material_records),
        "variant_count": sum(record["variant_count"] for record in material_records),
        "lighting_context_count": sum(
            variant["lighting_context_count"]
            for record in material_records
            for variant in record["variants"]
        ),
        "gltf_translation_status_counts": dict(sorted(status_counts.items())),
        "limitations": [
            "runtime correlations cover only models visible in the supplied traces",
            "equivalent model payload aliases retain every candidate identity",
            "RDP coverage and blender state are approximated by glTF alpha modes",
            "explicit TEXEL0/TEXEL1 LOD blending remains metadata-only",
            "captured CBFD lights and model-view matrices are retained per material variant for deterministic vertex-lighting replay",
        ],
        "materials": material_records,
    }
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    verify_runtime_material_output(output, manifest)
    return manifest


def load_runtime_material_catalog(
    path: Path | None, expected_digest: str
) -> dict[tuple[int, int, int, int], dict[str, Any]]:
    if path is None:
        return {}
    source = path if path.is_absolute() else ROOT / path
    manifest = json.loads(source.read_text(encoding="utf-8"))
    if (
        manifest.get("schema_version") != 1
        or manifest.get("family") != "runtime-correlated-model-materials"
    ):
        raise ValueError("runtime material manifest has an unsupported schema")
    if manifest.get("normalized_sha1") != expected_digest:
        raise ValueError("runtime material manifest belongs to a different ROM")
    catalog = {}
    for record in manifest.get("materials", []):
        key = tuple(
            int(record[field])
            for field in ("bank", "entry", "segment", "material_run")
        )
        if key in catalog:
            raise ValueError(f"duplicate runtime material record: {key}")
        catalog[key] = record
    if len(catalog) != manifest.get("material_record_count"):
        raise ValueError("runtime material manifest count changed")
    return catalog


def runtime_material_consensus(record: dict[str, Any] | None) -> dict[str, Any] | None:
    if record is None:
        return None
    variants = record.get("variants", [])
    if not variants:
        return None
    translations = [variant["gltf_translation"] for variant in variants]

    def unanimous(field: str) -> Any:
        values = [translation.get(field) for translation in translations]
        encoded = {
            json.dumps(value, sort_keys=True, separators=(",", ":"))
            for value in values
        }
        return values[0] if len(encoded) == 1 else None

    statuses = sorted({translation["status"] for translation in translations})
    exact = all(status == "exact-texture-times-vertex-color" for status in statuses)
    return {
        "variantCount": len(variants),
        "observationCount": record.get("observation_count"),
        "statuses": statuses,
        "alphaMode": unanimous("alphaMode"),
        "sampler": unanimous("sampler"),
        "baseColorFactor": unanimous("baseColorFactor") if exact else None,
        "exact": exact,
    }


def runtime_lighting_replay_choice(
    record: dict[str, Any] | None,
) -> tuple[dict[str, Any], dict[str, Any]] | None:
    """Choose only an unambiguous captured lighting state and matrix."""

    if record is None or len(record.get("variants", [])) != 1:
        return None
    variant = record["variants"][0]
    if variant.get("gltf_translation", {}).get("status") != (
        "requires-runtime-lighting-replay"
    ):
        return None
    contexts = variant.get("lighting_contexts", [])
    if len(contexts) != 1:
        return None
    return variant, contexts[0]


def extract_model_preview(
    profile: str,
    rom_argument: Path | None,
    texture_root: Path,
    output: Path,
    force: bool,
    bank_index: int = DEFAULT_BANK_INDEX,
    runtime_material_path: Path | None = None,
) -> dict[str, Any]:
    rom_path, source_order, digest, bundles, render_state_tables = load_model_bundles(
        profile, rom_argument, bank_index
    )
    catalog = load_preview_texture_catalog(texture_root, digest)
    runtime_material_catalog = load_runtime_material_catalog(
        runtime_material_path, digest
    )
    flat_payloads = (
        load_flat_asset_payloads(profile, rom_argument, digest)
        if bank_index in (0x01, 0x09)
        else None
    )
    prepare_output(output, force)
    copied_textures: dict[PreviewTexture, str] = {}
    model_records = []
    model_gltfs: dict[int, tuple[dict[str, Any], bytes]] = {}
    segmented_model_gltfs: dict[
        tuple[int, int], tuple[dict[str, Any], bytes]
    ] = {}
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
            character_reference_pose_source = None
            character_animation_clips: tuple[CharacterAnimationClip, ...] = ()
            incompatible_animation_clip_count = 0
            if bank_index == 0x01:
                geometry, character_layout = parse_character_model_geometry(
                    segment.data
                )
                character_joints = tuple(character_layout["joints"])
                if character_animation_manifest is None:
                    raise ValueError("bank-01 character animation manifest is absent")
                (
                    character_animation_clips,
                    incompatible_animation_clip_count,
                ) = character_animation_clips_for_model(
                    bundle.index,
                    max(
                        joint["animation_index"] for joint in character_joints
                    )
                    + 1,
                    character_animation_manifest,
                    character_animation_files,
                )
                pose_pair = CHARACTER_REFERENCE_POSE_PAIRS.get(bundle.index)
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
                    reference_rotations = decode_character_animation_first_pose(
                        character_animation_files[descriptor_name],
                        character_animation_files[bitstream_name],
                    )
                    if len(reference_rotations) != len(character_joints):
                        raise ValueError(
                            f"bank-01 entry {bundle.index} reference pose joint count changed"
                        )
                    character_reference_pose_source = (
                        f"bank-02-entry-{bundle.index:04d}-pair-{pose_pair:04d}-first-pose"
                    )
                    character_animation_clips = tuple(
                        sorted(
                            character_animation_clips,
                            key=lambda clip: clip.pair_index != pose_pair,
                        )
                    )
            else:
                geometry = parse_geometry_for_bank(segment.data, bank_index)
            source_geometry = geometry
            geometry, omitted_zero_area_faces, omitted_zero_area_by_run = (
                omit_zero_area_preview_faces(source_geometry)
            )
            texture_files: dict[str, str] = {}
            model_runtime_materials: dict[int, dict[str, Any]] = {}
            run_records = []
            mode_one_ci8_palette_policy = (
                "payload-base"
                if bank_index in (0x03, 0x04)
                else "payload-end-minus-0x200"
                if bank_index == 0x09
                else None
            )
            for run_index, run in enumerate(geometry.material_runs):
                runtime_material = runtime_material_catalog.get(
                    (bank_index, bundle.index, segment.index, run_index)
                )
                if runtime_material is not None:
                    model_sha1 = hashlib.sha1(segment.data).hexdigest()
                    if runtime_material.get("model_sha1") != model_sha1:
                        raise ValueError(
                            "runtime material record model hash does not match preview"
                        )
                    model_runtime_materials[run_index] = runtime_material
                texture, status = choose_preview_texture(
                    run,
                    catalog,
                    flat_payloads,
                    mode_one_ci8_palette_policy=mode_one_ci8_palette_policy,
                )
                reason_counts[status] = reason_counts.get(status, 0) + 1
                reason_face_counts[status] = (
                    reason_face_counts.get(status, 0) + run.face_count
                )
                record = {
                    "material_run": run_index,
                    "material": material_name(run),
                    "source_face_count": source_geometry.material_runs[
                        run_index
                    ].face_count,
                    "face_count": run.face_count,
                    "omitted_zero_area_face_count": omitted_zero_area_by_run[
                        run_index
                    ],
                    "matrix_index": run.matrix_index,
                    "status": status,
                    "runtime_material": (
                        runtime_material_consensus(runtime_material)
                        if runtime_material is not None
                        else None
                    ),
                    "combine_mode": command_pair_record(run.combine_mode),
                    "combine_formula": decode_combine_mode(run.combine_mode),
                    "render_tiles": [
                        {
                            "tile": tile_index,
                            "command": [
                                f"0x{command:08X}",
                                f"0x{argument:08X}",
                            ],
                            "tmem_byte_offset": (command & 0x1FF) * 8,
                        }
                        for tile_index, command, argument in run.render_tiles
                    ],
                    "other_mode": command_pair_record(run.other_mode),
                    "runtime_render_state_offset": (
                        f"0x{run.runtime_render_state_offset:X}"
                        if run.runtime_render_state_offset is not None
                        else None
                    ),
                    "texture": None,
                }
                if texture is not None and run.face_count:
                    linked_run_count += 1
                    linked_face_count += run.face_count
                    filename = copied_textures.get(texture)
                    if filename is None:
                        filename = preview_texture_filename(texture)
                        destination = output / "textures" / filename
                        destination.parent.mkdir(parents=True, exist_ok=True)
                        if texture.png_data is not None:
                            destination.write_bytes(texture.png_data)
                        else:
                            if texture.source is None:
                                raise ValueError("preview texture has no PNG source")
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
                        "pixel_byte_offset": texture.pixel_byte_offset,
                        "palette_byte_offset": texture.palette_byte_offset,
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
                character_animation_clips,
                runtime_materials=model_runtime_materials,
            )
            gltf_document = json.loads(gltf_data)
            for material in gltf_document.get("materials", []):
                extras = material.get("extras", {})
                run_index = extras.get("materialRun")
                replay = extras.get("runtimeMaterial", {}).get("lightingReplay")
                if isinstance(run_index, int) and replay is not None:
                    run_records[run_index]["runtime_lighting_replay"] = replay
            (geometry_dir / f"{stem}.gltf").write_bytes(gltf_data)
            (geometry_dir / f"{stem}.bin").write_bytes(gltf_binary)
            bind_gltf_file = bind_binary_file = None
            if bank_index == 0x01:
                bind_stem = f"{stem}-bind"
                bind_gltf_data, bind_binary = encode_gltf(
                    bundle.index,
                    segment.index,
                    geometry,
                    texture_files,
                    bank_index,
                    character_joints,
                    None,
                    None,
                    (),
                    bind_stem,
                    model_runtime_materials,
                )
                (geometry_dir / f"{bind_stem}.gltf").write_bytes(bind_gltf_data)
                (geometry_dir / f"{bind_stem}.bin").write_bytes(bind_binary)
                bind_gltf_file = f"geometry/{bind_stem}.gltf"
                bind_binary_file = f"geometry/{bind_stem}.bin"
            if bank_index == 0x03:
                model_gltfs[bundle.index] = (json.loads(gltf_data), gltf_binary)
            elif bank_index == 0x04:
                segmented_model_gltfs[(bundle.index, segment.index)] = (
                    json.loads(gltf_data),
                    gltf_binary,
                )
            model_records.append(
                {
                    "bank_entry": bundle.index,
                    "segment": segment.index,
                    "object_file": f"geometry/{stem}.obj",
                    "material_file": f"geometry/{stem}.mtl",
                    "gltf_file": f"geometry/{stem}.gltf",
                    "gltf_binary_file": f"geometry/{stem}.bin",
                    "bind_gltf_file": bind_gltf_file,
                    "bind_gltf_binary_file": bind_binary_file,
                    "vertex_count": len(geometry.vertices),
                    "source_face_count": len(source_geometry.faces),
                    "face_count": len(geometry.faces),
                    "omitted_zero_area_face_count": len(omitted_zero_area_faces),
                    "omitted_zero_area_faces": [
                        zero_area_face_record(source_geometry, face_index)
                        for face_index in omitted_zero_area_faces
                    ],
                    "texture_coordinate_count": texture_coordinate_count(geometry),
                    "material_runs": run_records,
                    "joint_count": len(character_joints or ()),
                    "normal_corner_count": len(geometry.face_normal_bytes) * 3,
                    "source_face_normal_corner_count": len(
                        source_geometry.face_normal_bytes
                    )
                    * 3,
                    "source_normal_corner_count": sum(
                        normal is not None and normal != (0, 0, 0)
                        for face in source_geometry.face_normal_bytes
                        for normal in face
                    ),
                    "geometric_fallback_normal_corner_count": sum(
                        normal is None or normal == (0, 0, 0)
                        for face in geometry.face_normal_bytes
                        for normal in face
                    ),
                    "animation_clip_count": len(character_animation_clips),
                    "animation_frame_count": sum(
                        len(clip.frames) for clip in character_animation_clips
                    ),
                    "incompatible_animation_clip_count": (
                        incompatible_animation_clip_count
                    ),
                    "preview_pose": (
                        character_pose_source
                        or "neutral-translation-hierarchy-no-semantic-action-selected"
                    )
                    if bank_index == 0x01 else None,
                    "runtime_reference_pose": (
                        character_reference_pose_source
                        if bank_index == 0x01
                        else None
                    ),
                }
            )
    assembled_scenes = []
    unresolved_placement_scenes = []
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
    elif bank_index == 0x04:
        placements, _ = load_object_placement_manifest(
            profile, rom_argument, include_files=False
        )
        for scene in placements["scenes"]:
            if scene["bank_index"] != 0x0B or not scene["records"]:
                continue
            scene_index = scene["scene_index"]
            unresolved = [
                record
                for record in scene["records"]
                if record["model_resolution_status"] != "resolved-bank-04-segment"
            ]
            if unresolved:
                unresolved_placement_scenes.append(
                    {
                        "scene_index": scene_index,
                        "placement_record_count": scene["record_count"],
                        "unresolved_record_count": len(unresolved),
                        "unresolved_dispatch_indices": sorted(
                            {record["dispatch_index"] for record in unresolved}
                        ),
                        "status": "not-assembled-missing-bank-04-bundle",
                    }
                )
                continue
            scene_models = {
                dispatch_index: segmented_model_gltfs[(scene_index, dispatch_index)]
                for dispatch_index in {
                    record["dispatch_index"] for record in scene["records"]
                }
            }
            scene_gltf, scene_binary = encode_placement_scene_gltf(
                scene_index,
                scene["records"],
                scene_models,
                placement_bank=0x0B,
                model_bank=0x04,
                model_index_field="dispatch_index",
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
                    "unique_model_count": len(scene_models),
                    "gltf_file": f"scenes/{stem}.gltf",
                    "gltf_binary_file": f"scenes/{stem}.bin",
                    "transform_status": "runtime-proven-static-transform",
                    "model_source": [0x04, scene_index, "dispatch-index"],
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
        "runtime_material_manifest": (
            display_path(
                runtime_material_path
                if runtime_material_path is not None
                and runtime_material_path.is_absolute()
                else ROOT / runtime_material_path
            )
            if runtime_material_path is not None
            else None
        ),
        "runtime_material_record_count": sum(
            run["runtime_material"] is not None
            for model in model_records
            for run in model["material_runs"]
        ),
        "runtime_lighting_replay_run_count": sum(
            run.get("runtime_lighting_replay", {}).get("status")
            == "gliden64-equivalent-observed-draw"
            for model in model_records
            for run in model["material_runs"]
        ),
        "instructions_file": "README.txt",
        "model_count": len(model_records),
        "source_face_count": sum(
            model["source_face_count"] for model in model_records
        ),
        "face_count": sum(model["face_count"] for model in model_records),
        "omitted_zero_area_face_count": sum(
            model["omitted_zero_area_face_count"] for model in model_records
        ),
        "drawable_model_count": sum(model["face_count"] > 0 for model in model_records),
        "rigged_model_count": sum(model["joint_count"] > 0 for model in model_records),
        "joint_count": sum(model["joint_count"] for model in model_records),
        "normal_corner_count": sum(
            model["normal_corner_count"] for model in model_records
        ),
        "source_face_normal_corner_count": sum(
            model["source_face_normal_corner_count"] for model in model_records
        ),
        "source_normal_corner_count": sum(
            model["source_normal_corner_count"] for model in model_records
        ),
        "geometric_fallback_normal_corner_count": sum(
            model["geometric_fallback_normal_corner_count"]
            for model in model_records
        ),
        "animation_clip_count": sum(
            model["animation_clip_count"] for model in model_records
        ),
        "animation_frame_count": sum(
            model["animation_frame_count"] for model in model_records
        ),
        "incompatible_animation_clip_count": sum(
            model["incompatible_animation_clip_count"] for model in model_records
        ),
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
                "render_loaders": [
                    {
                        "function": "func_1518C900",
                        "parser": "func_1510CE60",
                        "fifth_argument": "non-null-rewrite-table",
                    },
                    {
                        "function": "func_15183ACC",
                        "parser": "func_1510CE60",
                        "fifth_argument": "non-null-rewrite-table",
                    },
                ],
                "mode_one_effect": "256-entry-palette-starts-at-payload-end-minus-0x200",
                "mode_two_effect": "16-entry-palette-starts-at-payload-end-minus-0x200",
            }
            if bank_index == 0x01
            else
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
            if bank_index == 0x03
            else {
                "initial_model_slots": {
                    "function": "func_150031EC",
                    "call": "0x150033F4",
                    "segment_indices": [0, 1, 2, 3],
                    "fifth_argument": 0,
                    "effect": "mode-one palette remains at payload base",
                },
                "object_model_instances": {
                    "function": "func_150039E0",
                    "model_table": "D_800B0E50",
                    "call": "0x150041F0",
                    "fifth_argument": 0,
                    "effect": (
                        "new placement instances select any bundle model by index and "
                        "leave mode-one palettes at payload base"
                    ),
                },
                "parser": "func_1510CE60",
            }
            if bank_index == 0x04
            else {
                "loaders": ["func_1502FE10", "func_1518C900"],
                "parser": "func_1510CE60",
                "fifth_argument": "non-null-rewrite-table",
                "effect": (
                    "mode-one palette starts at payload end minus 0x200; direct CI8 "
                    "previews are composed from the loaded pixel span and that TLUT"
                ),
            }
        ),
        "runtime_segment_texture_evidence": (
            {
                "draw_function": "func_150911F4",
                "resolver": "func_1510D0EC",
                "state": "D_800D24C8",
                "slots": [
                    {"segment": 6, "state_u16_offset": "0xB0"},
                    {"segment": 7, "state_u16_offset": "0xB2"},
                    {"segment": 10, "state_u16_offset": "0xB4"},
                    {"segment": 11, "state_u16_offset": "0xB6"},
                ],
                "status": "character-state-selected-not-model-static",
            }
            if bank_index == 0x01
            else None
        ),
        "animation_clock": (
            {
                "ticks_per_second": ANIMATION_RUNTIME_FPS,
                "animation_updater": "func_1507BDB0",
                "animation_delta": "D_800BE9A4",
                "scheduler_retrace_delta": "D_800BE9E4",
                "scheduler_writer": "func_80004F00",
                "runtime_trace": {
                    "breakpoint": "func_1502D824",
                    "animation_delta": 1.0,
                    "video_retrace_delta": 2,
                },
                "status": "runtime-proven-ntsc-30-hz",
            }
            if bank_index == 0x01
            else None
        ),
        "limitations": [
            (
                "character texture segments 6, 7, 10, and 11 are selected from "
                "four runtime character-state texture IDs and are not linked"
                if bank_index == 0x01
                else "runtime-segment textures are scene-dependent and are not linked"
            ),
            "flat textures without a proven compatible extractor remain unlinked",
            (
                "bank-01 single-TEXEL0 same-index CI4/CI8 loads are linked only when "
                "their nominal pixel span and trailing runtime TLUT do not overlap; "
                "packed or mipmapped layouts remain unlinked"
                if bank_index == 0x01
                else "character same-index TLUT loads prove effective CI4/CI8 "
                "sampling, but their runtime palette/image composition is not yet a "
                "standalone PNG contract and remains unlinked"
            ),
            (
                "bank-01 render loaders pass a non-null rewrite table, placing both "
                "CI8 and CI4 TLUT references at payload end minus 0x200; TEXEL0/TEXEL1 "
                "mipmapped runs preserve their complete render-tile ladders but remain "
                "unlinked until their LOD blend and dynamic colours can be reproduced"
                if bank_index == 0x01
                else "bank-03's model loader passes a null fifth parser argument, so "
                "mode-one CI8 palette pointers remain at payload base, overlap the "
                "pixel indices, and are not linked to trailing-palette PNGs"
                if bank_index == 0x03
                else "bank-04's initial slots and indexed placement instances pass the "
                "same null fifth parser argument, so mode-one CI8 palette pointers "
                "remain at payload base and are not linked to trailing-palette PNGs"
                if bank_index == 0x04
                else "bank-09 loaders pass a non-null rewrite table, so mode-one CI8 "
                "palettes are composed from payload end minus 0x200"
            ),
            "native-proven PNGs prove reversible pixel storage, not the RDP combiner "
            "and primitive/environment colors needed for a faithful material; they "
            "remain unlinked",
            "OBJ/MTL cannot preserve the vertex-color multiply used by the common "
            "RDP combine mode; use the glTF preview for material inspection",
            "surface metadata and secondary runtime regions remain raw sidecar evidence",
            "source-authentic zero-area display-list triangles remain counted and indexed "
            "in the manifest but are omitted from OBJ/glTF preview geometry",
            (
                "bank-01 glTFs include compatible bank-02 rotation, scale, and masked "
                "joint-translation channels with descriptor-relative keyframe spacing "
                "on the runtime-proven 30 Hz animation clock"
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
                "pixel_byte_offset": texture.pixel_byte_offset,
                "palette_byte_offset": texture.palette_byte_offset,
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
    elif bank_index == 0x04:
        manifest["assembled_scene_count"] = len(assembled_scenes)
        manifest["assembled_scene_placement_count"] = sum(
            scene["placement_record_count"] for scene in assembled_scenes
        )
        manifest["assembled_scenes"] = assembled_scenes
        manifest["unresolved_placement_scene_count"] = len(
            unresolved_placement_scenes
        )
        manifest["unresolved_placement_scenes"] = unresolved_placement_scenes
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
                "Start with geometry/0000-00-bind.gltf. It contains the assembled neutral "
                "Conker hierarchy without animation data, so Blender cannot silently select "
                "an arbitrary imported Action while geometry is being inspected. Source "
                "vertices are joint-local in the ROM. The joint-table translations are "
                "parent-relative, so the exporter accumulates their model-space pivots "
                "before baking vertices and inverse-bind transforms. Use "
                "geometry/0000-00.gltf for the animated version, then expand the armature in "
                "Blender's Outliner. Compatible bank-02 clips import as named Actions; the first "
                "logical game animation ID routed to a pair appears as anim_NNNN in the "
                "Action name, and every routed ID is retained in the Action extras. Choose "
                "one in the Dope Sheet's Action Editor and press Space to preview it. Clear "
                "the active Action with its X button to return to the neutral bind hierarchy. "
                "Action time accessors use the runtime-proven 30 Hz animation clock. "
                "A pinned Mupen trace separately proves bank-02 entry 0000 pair 0025 frame 0 "
                "as a live Conker pose; it remains an Action and a manifest reference rather "
                "than changing the default nodes. "
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
            else "The scenes/ directory contains the 52 bank-11 dispatched-placement "
            "tables whose model source resolves completely through the matching bank-04 "
            "bundle. They assemble 716 records with the same runtime-proven position, "
            "YZX Euler rotation, and scale transforms. Scenes 17 and 62 retain 11 raw "
            "records but are not assembled because their matching bank-04 bundles are "
            "absent. Start with scenes/scene-00.gltf. "
            if bank_index == 0x04
            else ""
        )
        + "Unlinked materials intentionally retain vertex "
        "color only. The native-proven PNGs are reversible storage views, but are "
        "not linked until their RDP combiner and primitive/environment colors are "
        "represented. "
        + (
            "Character facial textures in runtime segments 6, 7, 10, and 11 are "
            "selected from live character state and therefore remain unlinked. "
            if bank_index == 0x01
            else ""
        )
        + "See manifest.json for per-run status and known runtime limits. "
        + (
            f"This preview embeds {manifest['runtime_material_record_count']} "
            "ROM-validated runtime material records. Unanimous sampler and alpha "
            "state is translated to glTF. Unambiguous supported lit runs use "
            "GLideN64-equivalent floating-point vertex colours; unsupported or "
            "ambiguous combiner, lighting, and mip state remains in material extras. "
            if runtime_material_catalog
            else ""
        )
        + "Zero-area triangles emitted by the source display lists are recorded by source "
        "face index but omitted from OBJ/glTF previews because they rasterize no surface. "
        + (
            "Bank-01 glTF files preserve the runtime hierarchy and rigid display-matrix "
            "assignments. They replay Conker's separate signed X/Y normal stream with "
            "signed vertex-flag Z, normalize valid source normals for glTF, and record "
            "the small geometric fallback set. They export every compatible bank-02 "
            "rotation, scale, and "
            "masked joint-translation timeline, plus root motion at its runtime 1/1024 scale, "
            "using descriptor-relative keyframe spacing on the runtime-proven 30 Hz "
            "animation clock. Bank-15 route tables attach logical game animation IDs to "
            "those Actions, and all five character-state duration overrides are resolved. "
            "Runtime material/lighting state remains unresolved.\n"
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


def verify_validation_atlas_output(output: Path, manifest: dict[str, Any]) -> None:
    if manifest["model_count"] != len(manifest["models"]):
        raise ValueError("validation atlas model count does not match its records")
    if sum(manifest["status_counts"].values()) != manifest["model_count"]:
        raise ValueError("validation atlas status counts do not cover every model")
    for required in ("index.html", "manifest.json"):
        if not (output / required).is_file():
            raise ValueError(f"validation atlas is missing {required}")
    for record in manifest["models"]:
        path = output / record["image_file"]
        data = path.read_bytes()
        if hashlib.sha1(data).hexdigest() != record["image_sha1"]:
            raise ValueError(f"validation atlas image hash changed: {record['image_file']}")
        if not data.startswith(b"\x89PNG\r\n\x1a\n"):
            raise ValueError(f"validation atlas image is not PNG: {record['image_file']}")
        width, height = struct.unpack_from(">II", data, 16)
        if (width, height) != (
            VALIDATION_ATLAS_VIEW_SIZE * len(VALIDATION_ATLAS_VIEWS),
            VALIDATION_ATLAS_VIEW_SIZE,
        ):
            raise ValueError(f"validation atlas image dimensions changed: {record['image_file']}")


def extract_validation_atlas(
    profile: str,
    rom_argument: Path | None,
    output: Path,
    force: bool,
    bank_indices: tuple[int, ...] = BANK_INDICES,
) -> dict[str, Any]:
    """Validate and render every requested model without texture or light state."""

    prepare_output(output, force)
    pending = []
    source_rom = source_order = digest = None
    bank_diagonals: dict[int, list[float]] = {}
    for bank_index in bank_indices:
        (
            bank_rom,
            bank_source_order,
            bank_digest,
            bundles,
            _,
        ) = load_model_bundles(profile, rom_argument, bank_index)
        if source_rom is None:
            source_rom = bank_rom
            source_order = bank_source_order
            digest = bank_digest
        elif (bank_rom, bank_source_order, bank_digest) != (
            source_rom,
            source_order,
            digest,
        ):
            raise ValueError("model banks were loaded from different ROM sources")
        bank_diagonals[bank_index] = []
        for bundle in bundles:
            for segment in bundle.segments:
                if not segment.data:
                    continue
                character_joints = None
                if bank_index == 0x01:
                    geometry, layout = parse_character_model_geometry(segment.data)
                    character_joints = tuple(layout["joints"])
                else:
                    geometry = parse_model_geometry(segment.data)
                validation = validate_model_geometry(geometry, character_joints)
                bank_diagonals[bank_index].append(validation["bounds"]["diagonal"])
                pending.append(
                    {
                        "bank_index": bank_index,
                        "bank_entry": bundle.index,
                        "segment": segment.index,
                        "geometry": geometry,
                        "character_joints": character_joints,
                        "validation": validation,
                    }
                )

    bank_medians = {
        bank_index: median(diagonals) if diagonals else 0.0
        for bank_index, diagonals in bank_diagonals.items()
    }
    records = []
    for item in pending:
        bank_index = item["bank_index"]
        geometry = item.pop("geometry")
        character_joints = item.pop("character_joints")
        validation = item.pop("validation")
        median_diagonal = bank_medians[bank_index]
        ratio = (
            validation["bounds"]["diagonal"] / median_diagonal
            if median_diagonal
            else 0.0
        )
        bounds_outlier = ratio > 32.0
        if bounds_outlier:
            validation["review_reasons"].append("extreme-bank-relative-bounds")
        if not geometry.faces:
            validation["review_reasons"].append("no-drawable-faces")
        if validation["status"] != "rejected":
            validation["status"] = (
                "review" if validation["review_reasons"] else "accepted"
            )
        image_data = render_validation_strip(geometry, character_joints)
        stem = f"{item['bank_entry']:04d}-{item['segment']:02d}"
        relative_image = f"images/bank-{bank_index:02x}/{stem}.png"
        image_path = output / relative_image
        image_path.parent.mkdir(parents=True, exist_ok=True)
        image_path.write_bytes(image_data)
        records.append(
            {
                **item,
                "vertex_count": len(geometry.vertices),
                "face_count": len(geometry.faces),
                "material_run_count": len(geometry.material_runs),
                "joint_count": len(character_joints or ()),
                "color_group": "rigid-joint" if character_joints else "material-run",
                "bounds_outlier": bounds_outlier,
                "bounds_diagonal_to_bank_median": ratio,
                **validation,
                "image_file": relative_image,
                "image_sha1": hashlib.sha1(image_data).hexdigest(),
            }
        )

    status_counts = {
        status: sum(record["status"] == status for record in records)
        for status in ("accepted", "review", "rejected")
    }
    zero_area_kind_counts: dict[str, int] = {}
    zero_area_opcode_counts: dict[str, int] = {}
    for record in records:
        for kind, count in record["zero_area_kind_counts"].items():
            zero_area_kind_counts[kind] = zero_area_kind_counts.get(kind, 0) + count
        for opcode, count in record["zero_area_opcode_counts"].items():
            zero_area_opcode_counts[opcode] = (
                zero_area_opcode_counts.get(opcode, 0) + count
            )
    manifest = {
        "schema_version": 1,
        "family": "cross-bank-model-validation-atlas",
        "profile": profile,
        "source_rom": manifest_source(source_rom),
        "source_byte_order": source_order,
        "normalized_sha1": digest,
        "bank_indices": list(bank_indices),
        "views": list(VALIDATION_ATLAS_VIEWS),
        "view_size": VALIDATION_ATLAS_VIEW_SIZE,
        "rendering": "software-orthographic-unlit-flat-color-with-depth-buffer",
        "model_count": len(records),
        "drawable_model_count": sum(record["face_count"] > 0 for record in records),
        "status_counts": status_counts,
        "bank_median_bounds_diagonal": {
            f"{bank_index:02x}": value
            for bank_index, value in bank_medians.items()
        },
        "bounds_outlier_ratio_threshold": 32.0,
        "zero_area_face_count": sum(record["zero_area_face_count"] for record in records),
        "zero_area_kind_counts": dict(sorted(zero_area_kind_counts.items())),
        "zero_area_opcode_counts": dict(sorted(zero_area_opcode_counts.items())),
        "duplicate_face_count": sum(record["duplicate_face_count"] for record in records),
        "inverted_source_normal_face_count": sum(
            record["inverted_source_normal_face_count"] for record in records
        ),
        "acceptance_policy": {
            "rejected": [
                "non-finite-bounds",
                "invalid-joint-assignment-or-hierarchy",
            ],
            "review": [
                "disconnected-components",
                "coincident-triangles",
                "source-zero-area-triangles-filtered-from-previews",
                "source-normal-winding-disagreement",
                "extreme-bank-relative-bounds",
                "no-drawable-faces",
            ],
            "preview_filter": (
                "source zero-area triangles are retained in the decoded inventory "
                "and manifest provenance but omitted from OBJ/glTF previews"
            ),
        },
        "models": records,
    }
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    cards = "\n".join(
        f'<article class="{record["status"]}"><a href="{record["image_file"]}">'
        f'<img loading="lazy" src="{record["image_file"]}" '
        f'alt="bank {record["bank_index"]:02X} entry {record["bank_entry"]:04d} '
        f'segment {record["segment"]:02d}: front, side, top"></a>'
        f'<h2>{record["bank_index"]:02X}:{record["bank_entry"]:04d}-'
        f'{record["segment"]:02d} · {record["status"]}</h2>'
        f'<p>{record["face_count"]} faces · {record["connected_component_count"]} '
        f'components · {record["color_group"]}</p>'
        f'<p>{", ".join(record["rejection_reasons"] + record["review_reasons"]) or "no findings"}</p>'
        "</article>"
        for record in records
    )
    (output / "index.html").write_text(
        "<!doctype html><html><head><meta charset=\"utf-8\"><title>Conker model "
        "validation atlas</title><style>body{background:#15171b;color:#eee;font:14px "
        "system-ui;margin:20px}header{position:sticky;top:0;background:#15171beF;padding:8px;"
        "z-index:1}.grid{display:grid;grid-template-columns:repeat(auto-fill,minmax(400px,1fr));"
        "gap:12px}article{background:#22262d;border-left:5px solid #44b678;padding:8px}"
        "article.review{border-color:#e2ad3b}article.rejected{border-color:#dd5b5b}img{width:100%;"
        "image-rendering:auto;background:#22252b}h2{font-size:15px;margin:6px 0}p{margin:3px 0;"
        "color:#bbc0c8}</style></head><body><header><h1>Conker model validation atlas</h1>"
        f'<p>Views: front · side · top. Unlit colours identify rigid joints in bank 01 and '
        f'material runs elsewhere. {status_counts["accepted"]} accepted, '
        f'{status_counts["review"]} review, {status_counts["rejected"]} rejected.</p>'
        "</header><main class=\"grid\">" + cards + "</main></body></html>\n",
        encoding="utf-8",
    )
    verify_validation_atlas_output(output, manifest)
    return manifest


def verify_models(
    profile: str, rom_argument: Path | None, bank_index: int = DEFAULT_BANK_INDEX
) -> tuple[int, ...]:
    _, _, _, bundles, _ = load_model_bundles(profile, rom_argument, bank_index)
    if bank_index in (0x03, 0x04):
        placements, payloads = load_object_placement_manifest(
            profile, rom_argument, include_files=False
        )
        if sum(len(payload) for payload in payloads.values()) <= 0:
            raise ValueError("object placement payloads are unexpectedly empty")
        if placements["record_count"] != 1238:
            raise ValueError("US object placement record count changed")
        if bank_index == 0x04 and (
            placements["resolved_bank_11_record_count"] != 716
            or placements["unresolved_bank_11_record_count"] != 11
            or placements["resolved_bank_04_segment_count"] != 570
        ):
            raise ValueError("US bank-11 dispatched placement resolution changed")
    elif bank_index == 0x01:
        animations, _ = load_character_animation_manifest(
            profile, rom_argument, include_files=False
        )
        if (
            animations["entry_count"] != 145
            or animations["indexed_animation_entry_count"] != 123
            or animations["clip_pair_count"] != 2660
            or animations["logical_animation_route_count"] != 3021
            or animations["mapped_logical_animation_route_count"] != 2982
            or animations["direct_companion_logical_animation_route_count"] != 39
            or animations["decoded_timeline_clip_count"] != 2621
            or animations["empty_timeline_clip_count"] != 39
            or animations["unresolved_timeline_clip_count"] != 0
            or animations["decoded_frame_count"] != 57732
            or animations["runtime_zero_filled_descriptor_count"] != 1
            or animations["extended_stride_clip_count"] != 2
            or animations["companion_trailing_clip_count"] != 3
            or animations["companion_trailing_byte_count"] != 1845
            or animations["runtime_duration_override_clip_count"] != 5
            or animations["resolved_runtime_duration_override_clip_count"] != 5
            or animations["unresolved_runtime_duration_override_clip_count"] != 0
            or animations["scale_channel_count"] != 3616
            or animations["scale_channel_clip_count"] != 689
            or animations["bitstream_alignment_padding_clip_count"] != 1796
            or animations["bitstream_alignment_padding_byte_count"] != 7177
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
    collision_model_count = collision_record_count = 0
    collision_surface_words = set()
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
            if (
                bank_index == 0x04
                and segment.index == 0
                and geometry.tertiary_region is not None
            ):
                surface_words = bank_04_collision_surface_words(segment, geometry)
                collision_model_count += 1
                collision_record_count += len(surface_words)
                collision_surface_words.update(surface_words)
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
    if bank_index == 0x04 and (
        collision_model_count != 58
        or collision_record_count != 97071
        or len(collision_surface_words) != 176
    ):
        raise ValueError("US bank-04 collision inventory changed")
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
    parser.add_argument(
        "action",
        choices=(
            "survey",
            "extract",
            "preview",
            "atlas",
            "materials",
            "collision",
            "verify",
        ),
    )
    parser.add_argument("--profile", choices=("us",), default="us")
    parser.add_argument(
        "--bank",
        choices=("01", "03", "04", "09"),
        help=(
            "indexed model bank to process (default: 04, or all four proven "
            "banks for atlas)"
        ),
    )
    parser.add_argument("--rom", type=Path)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--textures", type=Path)
    parser.add_argument(
        "--runtime-materials",
        type=Path,
        help="runtime-correlated material manifest to embed in preview glTF files",
    )
    parser.add_argument(
        "--trace",
        type=Path,
        action="append",
        help="runtime draw-state JSONL input (repeatable for materials)",
    )
    parser.add_argument("--force", action="store_true")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    bank_index = int(args.bank or "04", 16)
    try:
        if args.action == "materials":
            output = args.output or ROOT / "build/assets/models/us-runtime-materials"
            if not output.is_absolute():
                output = ROOT / output
            manifest = extract_runtime_materials(
                args.profile,
                args.rom,
                tuple(args.trace or ()),
                output,
                args.force,
            )
            print(
                f"Prepared {manifest['material_record_count']} runtime-correlated "
                f"materials with {manifest['variant_count']} variants from "
                f"{manifest['correlated_draw_observation_count']} draw observations"
            )
            print(f"Manifest: {display_path(output / 'manifest.json')}")
        elif args.action == "survey":
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
                args.runtime_materials,
            )
            print(
                f"Prepared and verified {manifest['model_count']} model previews with "
                f"{manifest['texture_coordinate_count']} UV coordinates"
            )
            if bank_index == 0x01:
                print(
                    f"Rigged previews: {manifest['rigged_model_count']} models, "
                    f"{manifest['joint_count']} runtime joints, "
                    f"{manifest['animation_clip_count']} compatible bank-02 clips, "
                    f"{manifest['animation_frame_count']} exported source frames"
                )
            print(
                f"Linked {manifest['linked_material_run_count']} material runs and "
                f"{manifest['linked_face_count']} faces to "
                f"{manifest['copied_texture_count']} proven texture PNGs"
            )
            print(f"Preview manifest: {display_path(output / 'manifest.json')}")
        elif args.action == "atlas":
            output = args.output or ROOT / "build/assets/models/us-validation-atlas"
            if not output.is_absolute():
                output = ROOT / output
            bank_indices = (bank_index,) if args.bank else BANK_INDICES
            manifest = extract_validation_atlas(
                args.profile,
                args.rom,
                output,
                args.force,
                bank_indices,
            )
            print(
                f"Prepared and verified {manifest['model_count']} model validation "
                f"strips across {len(manifest['bank_indices'])} banks: "
                f"{manifest['status_counts']['accepted']} accepted, "
                f"{manifest['status_counts']['review']} review, "
                f"{manifest['status_counts']['rejected']} rejected"
            )
            print(
                f"Geometry findings: {manifest['zero_area_face_count']} zero-area, "
                f"{manifest['duplicate_face_count']} duplicate, "
                f"{manifest['inverted_source_normal_face_count']} source-normal/winding "
                "disagreements"
            )
            print(f"Atlas: {display_path(output / 'index.html')}")
            print(f"Manifest: {display_path(output / 'manifest.json')}")
        elif args.action == "collision":
            if bank_index != 0x04:
                raise ValueError("collision export is proven only for bank 04")
            output = args.output or ROOT / "build/assets/models/us-bank-04-collision"
            if not output.is_absolute():
                output = ROOT / output
            manifest = extract_bank_04_collision(
                args.profile, args.rom, output, args.force
            )
            print(
                f"Prepared and verified {manifest['model_count']} bank-04 static "
                f"terrain collision meshes "
                f"({manifest['primary_terrain_model_count']} primary, "
                f"{manifest['secondary_terrain_model_count']} secondary): "
                f"{manifest['triangle_record_count']} portable triangle "
                f"records, {manifest['surface_record_count']} exact surface records, "
                f"{manifest['unique_surface_word_count']} unique surface words"
            )
            unresolved_placements = (
                manifest["placement_collision_included_record_count"]
                - manifest["placement_collision_resolved_record_count"]
            )
            print(
                f"Assembled {manifest['placement_collision_resolved_record_count']} "
                f"runtime-included placement collisions across "
                f"{manifest['placement_collision_scene_count']} scenes; "
                f"{manifest['placement_collision_excluded_record_count']} source "
                f"records are excluded by flags and "
                f"{unresolved_placements} "
                "included records lack their bank-04 scene bundle"
            )
            print(f"Manifest: {display_path(output / 'manifest.json')}")
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
