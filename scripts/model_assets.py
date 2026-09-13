#!/usr/bin/env python3
"""Survey, extract, verify, and prepare previews of US model geometry."""

from __future__ import annotations

import argparse
import sys
from collections import Counter
import base64
import copy
import hashlib
import json
import math
import re
import shutil
import struct
from colorsys import hsv_to_rgb
from dataclasses import dataclass, replace
from pathlib import Path
from statistics import median
from typing import Any

try:
    from scripts import model_character_defaults, model_morphs, model_emission_points, model_character_parts, model_object_materials, model_bank09_materials
    from scripts.model_effect_format import (
        EffectModelSource, is_effect_model, parse_effect_model, encode_effect_model,
        verify_effect_consumers, resolve_effect_sources,
    )
    from scripts.model_attachment_format import (
        is_attachment_model, parse_attachment_model, encode_attachment_model,
    )
    from scripts.rzip_archive import (
        decode_rzip_chunk,
        iter_flat_rzip_entries,
        iter_indexed_flat_rzip_entries,
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
    from scripts.texture_native import encode_png as encode_native_texture_png
    from scripts.texture_native import packed_row_size, payload_to_rgba as native_payload_to_rgba
    from scripts.texture_rgba16 import encode_png as encode_rgba16_texture_png
    from scripts.mupen_trace import (
        CHARACTER_POOL_ADDRESS,
        CHARACTER_POOL_RECORD_COUNT,
        CHARACTER_POOL_RECORD_SIZE,
        CHARACTER_PART_COUNT_TABLE_SIZE,
        CHARACTER_PART_POINTER_TABLE_SIZE,
        decode_cbfd_character_part_table_headers,
        decode_f3dex2_cbfd,
        decode_rsp_matrix,
        flatten_display_lists,
        captured_task_type,
        geometry_clusters,
        load_model_cluster_index,
        refresh_trace_model_correlations,
    )
except ModuleNotFoundError:
    import model_character_defaults
    import model_morphs
    import model_emission_points
    import model_character_parts
    import model_object_materials
    import model_bank09_materials
    from model_effect_format import (
        EffectModelSource, is_effect_model, parse_effect_model, encode_effect_model,
        verify_effect_consumers, resolve_effect_sources,
    )
    from model_attachment_format import (  # type: ignore[no-redef]
        is_attachment_model, parse_attachment_model, encode_attachment_model,
    )
    from rzip_archive import (  # type: ignore[no-redef]
        decode_rzip_chunk,
        iter_flat_rzip_entries,
        iter_indexed_flat_rzip_entries,
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
    from texture_native import encode_png as encode_native_texture_png
    from texture_native import packed_row_size, payload_to_rgba as native_payload_to_rgba
    from texture_rgba16 import encode_png as encode_rgba16_texture_png
    from mupen_trace import (  # type: ignore[no-redef]
        CHARACTER_POOL_ADDRESS,
        CHARACTER_POOL_RECORD_COUNT,
        CHARACTER_POOL_RECORD_SIZE,
        CHARACTER_PART_COUNT_TABLE_SIZE,
        CHARACTER_PART_POINTER_TABLE_SIZE,
        decode_cbfd_character_part_table_headers,
        decode_f3dex2_cbfd,
        decode_rsp_matrix,
        flatten_display_lists,
        captured_task_type,
        geometry_clusters,
        load_model_cluster_index,
        refresh_trace_model_correlations,
    )


BANK_INDICES = (0x01, 0x03, 0x04, 0x09)
DEFAULT_BANK_INDEX = 0x04
RUNTIME_FLAT_ASSET_COUNT = 0x1E52
RUNTIME_FLAT_SIZE_TABLE = 0x80091D20
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
CHARACTER_RUNTIME_MATRIX_STATE = {
    "status": "runtime-conversion-chain-proven",
    "renderer": "func_1502CCFC",
    "segment": 3,
    "renderer_layout": "cbfd-character-row-major-f32",
    "finalizer": "func_1502E474",
    "in_place_converter": "func_150A9984",
    "submitted_layout": "n64-split-signed-16.16-mtx",
    "palette_identity": "renderer-root-plus-absolute-address-delta",
    "segment_relative_slot_status": "not-palette-global-after-interior-rebase",
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
    effect_source: EffectModelSource | None = None


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
    texture_enabled: bool | None
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
    texture_dimensions: tuple[int, int] | None = None
    # Values and known-bit masks for partial E2/E3 writes without a full EF.
    other_mode_partial: tuple[int, int, int, int] | None = None
    # Detail LOD selects a tile after G_TEXTURE's declared base. Preserve its
    # own SetTileSize state, rather than inferring an origin from another tile.
    detail_tile_bounds: tuple[tuple[int, int, int], ...] = ()
    preview_coordinate_state: tuple[tuple[int, int], tuple[int, int], tuple[int, int]] | None = None
    # Load-time tile state, scoped to one callable display list. Later SetTile
    # commands do not change the destination of an earlier TMEM transfer.
    texture_loads: tuple[tuple[ModelTextureBinding | None, tuple[int, int] | None], ...] = ()


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
    # RSP transforms a vertex when VTX loads it, not when a triangle draws it.
    # A cache can retain corners loaded under several different joint matrices.
    face_matrix_indices: tuple[
        tuple[int | None, int | None, int | None], ...
    ] = ()
    custom_normal_command_count: int = 0
    # Interchange normals transformed with a baked pose, separate from the
    # signed source bytes consumed by CBFD lighting.
    face_preview_normals: tuple[
        tuple[tuple[float, float, float] | None, ...], ...
    ] = ()
    # Original face within this run's source model, through merges/filtering.
    face_source_indices: tuple[int, ...] = ()
    # F3DEX2 cull bits at each triangle. None means at least one bit is
    # inherited or was invalidated by an unresolved display-list call.
    face_cull_modes: tuple[int | None, ...] = ()


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
    preview_coordinate_state: tuple[tuple[int, int], tuple[int, int], tuple[int, int]] | None = None
    # Contributing LoadBlocks: flat ID, payload SHA-1, TMEM byte offset, count.
    tmem_source_loads: tuple[tuple[int, str, int, int], ...] = ()
    tmem_load_sizes: tuple[int, ...] = ()


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
    data: bytes,
    *,
    allow_external_texture: bool = False,
    independent_display_lists: bool = False,
    model_relative_vertices: bool = False,
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
    matrix_cache: dict[int, int | None] = {}
    faces = []
    face_command_offsets = []
    face_command_opcodes = []
    face_cache_indices = []
    face_matrix_indices = []
    face_cull_modes = []
    geometry_mode = geometry_mode_known_bits = 0
    vertex_load_count = 0
    segment_8_display_list_offsets = []
    texture_references = []
    runtime_segment_texture_addresses = []
    pending_texture: ModelTextureBinding | None = None
    texture_loads = []
    pixel_texture: ModelTextureBinding | None = None
    palette_texture: ModelTextureBinding | None = None
    texture_enabled = None if independent_display_lists else False
    render_tiles: dict[int, tuple[int, int]] = {}
    render_tile_bounds: dict[int, tuple[int, int]] = {}
    texture_scale: tuple[int, int] | None = None
    combine_mode: tuple[int, int] | None = None
    other_mode: tuple[int, int] | None = None
    other_mode_partial: tuple[int, int, int, int] | None = None
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
            face_matrix_indices.append(tuple(matrix_cache[index] for index in triangle))
            face_normal_bytes.append(
                tuple(normal_cache.get(cache_index) for cache_index in triangle)
            )
            face_command_offsets.append(command_offset)
            face_command_opcodes.append(data[command_offset])
            face_cull_modes.append(
                geometry_mode & 0x600
                if geometry_mode_known_bits & 0x600 == 0x600 else None
            )
        face_count = len(faces) - first_face
        nonlocal pixel_texture
        if texture_enabled and pixel_texture is None:
            if not allow_external_texture:
                raise ValueError(
                    f"textured triangles at 0x{command_offset:X} have no loaded image"
                )
            pixel_texture = ModelTextureBinding(image_command=0, external=True)
        active_pixel = pixel_texture if texture_enabled else None
        # G_TEXTURE selects the base tile independently of SetTile order. In
        # particular, character facial lists select tile 4 after defining a
        # different-sized tile 0 and its mip chain in the same callable list.
        tile_index = (texture_scale[0] >> 8) & 7 if texture_scale else 0
        render_tile = render_tiles.get(tile_index)
        tile_bounds = render_tile_bounds.get(tile_index)
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
                or (
                    active_pixel.segment is not None
                    and palette_texture is not None
                    and palette_texture.segment == active_pixel.segment
                )
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
        detail_bounds = (tuple((i, c, a) for i, (c, a) in sorted(render_tile_bounds.items()))
                         if texture_enabled and other_mode is not None
                         and ((other_mode[0] >> 17) & 3) == 2 else ())
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
            other_mode_partial,
            detail_bounds,
            tuple(texture_loads),
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
                    other_mode_partial,
                    detail_bounds,
                    tuple(texture_loads),
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
            # Bank-09's direct loader passes the model base to func_15168E54.
            # func_15168E34 adds it only to unsegmented addresses; these include
            # the 0x28-byte native header. Segment-1 addresses are unchanged.
            relative_address = model_relative_vertices and argument >> 24 == 0
            if relative_address:
                vertex_byte_offset -= 0x28
            vertex_start = vertex_byte_offset // 16
            if (
                (argument >> 24 != 0x01 and not relative_address)
                or vertex_byte_offset < 0
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
                matrix_cache[cache_index] = matrix_index
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
            # The validated segment-8 slots contain only OtherMode + EndDL.
            # An unrecognised slot cannot prove that earlier TMEM survives.
            if runtime_render_state_offset not in RUNTIME_RENDER_STATE_OFFSETS:
                texture_loads.append((None, None))
            other_mode = None
            other_mode_partial = None
            geometry_mode_known_bits = 0
        elif opcode == 0xD9:
            preserve = command & 0xFFFFFF
            geometry_mode = (geometry_mode & preserve) | argument
            geometry_mode_known_bits = (
                (geometry_mode_known_bits & preserve) | (~preserve & 0xFFFFFF) | argument
            )
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
            texture_loads.append((pixel_texture, render_tiles.get((argument >> 24) & 7)))
        elif opcode == 0xF0:
            palette_texture = (
                replace(pending_texture, load_command=(command, argument))
                if pending_texture is not None
                else None
            )
            texture_loads.append((palette_texture, render_tiles.get((argument >> 24) & 7)))
        elif opcode == 0xF4:
            # LoadTile has different row/stride semantics from this replay.
            texture_loads.append((None, None))
        elif opcode == 0xF5:
            render_tiles[(argument >> 24) & 7] = (command, argument)
        elif opcode == 0xF2:
            render_tile_bounds[(argument >> 24) & 7] = (command, argument)
        elif opcode == 0xD7:
            texture_enabled = bool(command & 2)
            texture_scale = (command, argument)
        elif opcode == 0xFC:
            combine_mode = (command, argument)
        elif opcode == 0xEF:
            other_mode = (command, argument)
            other_mode_partial = None
            runtime_render_state_offset = None
        elif opcode in (0xE2, 0xE3):
            other_mode, other_mode_partial = apply_other_mode_write(
                other_mode, other_mode_partial, command, argument)
            # A later partial write is no longer the unchanged segment-8 state.
            runtime_render_state_offset = None
        elif opcode == 0xDF and independent_display_lists:
            # Character pointer-table entries are separately callable. The
            # renderer selects their order; physical adjacency in the model
            # does not prove inherited RDP state for the next entry.
            cache.clear()
            matrix_cache.clear()
            normal_cache.clear()
            normal_base = None
            matrix_index = None
            pending_texture = pixel_texture = palette_texture = None
            texture_loads = []
            texture_scale = None
            render_tiles = {}
            render_tile_bounds = {}
            texture_enabled = None
            combine_mode = other_mode = None
            other_mode_partial = None
            runtime_render_state_offset = None
            geometry_mode = geometry_mode_known_bits = 0

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
    decoded_material_runs = tuple(
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
            other_mode_partial=run[13],
            detail_tile_bounds=run[14],
            texture_loads=run[15],
        )
        for run in material_runs
    )
    proven_material_runs = []
    for run in decoded_material_runs:
        try:
            texture_coordinate_state(run)
        except ValueError:
            run = replace(run, texture_coordinates_proven=False)
        proven_material_runs.append(run)
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
        material_runs=tuple(proven_material_runs),
        face_normal_bytes=(
            tuple(face_normal_bytes) if custom_normal_command_count else ()
        ),
        header_words=header_words,
        face_command_offsets=tuple(face_command_offsets),
        face_command_opcodes=tuple(face_command_opcodes),
        face_cache_indices=tuple(face_cache_indices),
        face_matrix_indices=tuple(face_matrix_indices),
        face_cull_modes=tuple(face_cull_modes),
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
    geometry = parse_model_geometry(
        synthetic, allow_external_texture=True, independent_display_lists=True
    )
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
        face_matrix_indices=geometry.face_matrix_indices,
        face_cull_modes=geometry.face_cull_modes,
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
    used_matrix_indices.update(
        matrix for face in geometry.face_matrix_indices for matrix in face
        if matrix is not None
    )
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
    if bank_index == 0x09 and is_attachment_model(data):
        return parse_attachment_model(data, parse_model_geometry)[0]
    if bank_index == 0x09 and is_effect_model(data):
        return parse_effect_model(data, parse_model_geometry)[0]
    return parse_model_geometry(data, model_relative_vertices=bank_index == 0x09)


def parse_segment_geometry(segment: ModelSegment, bank_index: int) -> ModelGeometry:
    if segment.effect_source is not None:
        if bank_index != 9:
            raise ValueError("effect source belongs to bank 09")
        return parse_effect_model(segment.data, parse_model_geometry, segment.effect_source)[0]
    return parse_geometry_for_bank(segment.data, bank_index)


def verify_direct_model_consumers(code: bytes, base: int) -> None:
    """Pin the US bank-09 loader and conditional pointer relocation contract."""
    for start, size, sha1 in (
        (0x1518C900, 260, '38d05a33437a0f688bda1b2cf2ac6299b9aede8e'),
        (0x15168E54, 180, 'cbc1245a3f5d3846756b7c360d39675df6521c34'),
        (0x15168E34, 32, 'edfbe5742959d43dfa06d389f8a448dd015aa75f'),
    ):
        offset = start - base
        if offset < 0 or hashlib.sha1(code[offset:offset + size]).hexdigest() != sha1:
            raise ValueError(f'ROM direct-model consumer changed at 0x{start:08X}')


def rebuild_direct_model(data: bytes, geometry: ModelGeometry) -> bytes:
    """Re-encode decoded header/vertices; preserve native lists and opaque data."""
    vertices = b''.join(struct.pack('>hhhHhh4B', v.x, v.y, v.z, v.flag, v.s, v.t, *v.color)
                        for v in geometry.vertices)
    if len(vertices) != geometry.display_list_offset - 0x28 or len(geometry.header_words) != 10:
        raise ValueError('direct model reconstruction extent changed')
    return (struct.pack('>10I', *geometry.header_words) + vertices
            + data[geometry.display_list_offset:])


def validation_color(index: int) -> tuple[int, int, int, int]:
    """Return a stable, high-contrast unlit colour for one rigid/material run."""

    hue = (index * 0.6180339887498949) % 1.0
    red, green, blue = hsv_to_rgb(hue, 0.68, 0.95)
    return (round(red * 255), round(green * 255), round(blue * 255), 255)


def face_vertex_matrix_indices(
    geometry: ModelGeometry, run: ModelMaterialRun, face_index: int
) -> tuple[int, int, int]:
    """Return each corner's matrix at its most recent vertex-cache load."""

    if not geometry.face_matrix_indices:
        # Compatibility for synthetic test geometry and already baked positions.
        return (run.matrix_index if run.matrix_index is not None else 0,) * 3
    if len(geometry.face_matrix_indices) != len(geometry.faces):
        raise ValueError("vertex-load matrix records do not cover every face")
    return tuple(
        matrix if matrix is not None else 0
        for matrix in geometry.face_matrix_indices[face_index]
    )


def geometry_vertex_matrix_indices(geometry: ModelGeometry) -> set[int]:
    return {
        matrix
        for run in geometry.material_runs
        for face_index in range(run.first_face, run.first_face + run.face_count)
        for matrix in face_vertex_matrix_indices(geometry, run, face_index)
    }


def vertex_matrix_mismatch_face_count(geometry: ModelGeometry) -> int:
    return sum(
        any(
            matrix != (run.matrix_index or 0)
            for matrix in face_vertex_matrix_indices(geometry, run, face_index)
        )
        for run in geometry.material_runs
        for face_index in range(run.first_face, run.first_face + run.face_count)
    )


def validation_face_records(
    geometry: ModelGeometry,
    character_joints: tuple[dict[str, Any], ...] | None = None,
    matrix_rows_by_index: dict[int, list[list[float]]] | None = None,
) -> list[dict[str, Any]]:
    """Expand faces into bind-space positions and validation colour groups."""

    global_bind_pivots = (
        character_global_bind_pivots(character_joints)
        if character_joints
        else {}
    )
    records = []
    for run_index, run in enumerate(geometry.material_runs):
        matrix_index = run.matrix_index if run.matrix_index is not None else 0
        group_index = matrix_index if character_joints else run_index
        for face_offset, face in enumerate(
            geometry.faces[run.first_face : run.first_face + run.face_count]
        ):
            vertex_matrices = face_vertex_matrix_indices(
                geometry, run, run.first_face + face_offset
            )
            positions = []
            for index, vertex_matrix in zip(face, vertex_matrices):
                vertex = geometry.vertices[index]
                if matrix_rows_by_index is None:
                    pivot = (
                        global_bind_pivots.get(
                            vertex_matrix, (math.nan, math.nan, math.nan)
                        ) if character_joints else (0.0, 0.0, 0.0)
                    )
                    position = (
                        float(vertex.x) + pivot[0],
                        float(vertex.y) + pivot[1],
                        float(vertex.z) + pivot[2],
                    )
                else:
                    rows = matrix_rows_by_index.get(vertex_matrix)
                    position = tuple(
                        float(vertex.x) * rows[0][axis]
                        + float(vertex.y) * rows[1][axis]
                        + float(vertex.z) * rows[2][axis]
                        + rows[3][axis]
                        for axis in range(3)
                    ) if rows is not None else (math.nan, math.nan, math.nan)
                positions.append(position)
            positions = tuple(positions)
            records.append(
                {
                    "face_index": run.first_face + face_offset,
                    "run_index": run_index,
                    "matrix_index": matrix_index if character_joints else None,
                    "vertex_matrix_indices": vertex_matrices if character_joints else (),
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
    retained_source_indices = []
    retained_normals = []
    retained_preview_normals = []
    retained_offsets = []
    retained_opcodes = []
    retained_cache_indices = []
    retained_matrix_indices = []
    retained_cull_modes = []
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
            # Equal local positions can separate under different joint matrices.
            # Only reject these faces after bind/pose transforms are evaluated.
            one_matrix = len(set(
                face_vertex_matrix_indices(geometry, run, face_index)
            )) == 1
            if sum(value * value for value in cross) == 0.0 and one_matrix:
                omitted_faces.append(face_index)
                omitted_count += 1
                continue
            retained_faces.append(face)
            retained_source_indices.append(
                geometry.face_source_indices[face_index] if geometry.face_source_indices else face_index
            )
            if geometry.face_normal_bytes:
                retained_normals.append(geometry.face_normal_bytes[face_index])
            if geometry.face_preview_normals:
                retained_preview_normals.append(geometry.face_preview_normals[face_index])
            if geometry.face_command_offsets:
                retained_offsets.append(geometry.face_command_offsets[face_index])
            if geometry.face_command_opcodes:
                retained_opcodes.append(geometry.face_command_opcodes[face_index])
            if has_face_cache_indices:
                retained_cache_indices.append(geometry.face_cache_indices[face_index])
            if geometry.face_matrix_indices:
                retained_matrix_indices.append(geometry.face_matrix_indices[face_index])
            if geometry.face_cull_modes:
                retained_cull_modes.append(geometry.face_cull_modes[face_index])
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
            face_source_indices=tuple(retained_source_indices),
            faces=tuple(retained_faces),
            material_runs=tuple(preview_runs),
            face_normal_bytes=tuple(retained_normals),
            face_preview_normals=tuple(retained_preview_normals),
            face_command_offsets=tuple(retained_offsets),
            face_command_opcodes=tuple(retained_opcodes),
            face_cache_indices=tuple(retained_cache_indices),
            face_matrix_indices=tuple(retained_matrix_indices),
            face_cull_modes=tuple(retained_cull_modes),
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
                matrix
                for face in faces
                for matrix in face["vertex_matrix_indices"]
                if matrix not in matrix_set
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
    if run.texture_enabled is None:
        name = "runtime_texture_state_unknown"
    elif not run.texture_enabled:
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
    if run.other_mode_partial is not None:
        name += "_partial_" + "_".join(f"{word:08x}" for word in run.other_mode_partial)
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


def decode_convert_mode(pair: tuple[int, int] | None) -> dict[str, Any] | None:
    """Decode the six signed nine-bit coefficients written by SetConvert."""

    if pair is None:
        return None
    command, argument = pair
    if command >> 24 != 0xEC:
        raise ValueError("convert-mode command does not use opcode 0xEC")
    values = [
        (command >> 13) & 0x1FF,
        (command >> 4) & 0x1FF,
        ((command & 0xF) << 5) | ((argument >> 27) & 0x1F),
        (argument >> 18) & 0x1FF,
        (argument >> 9) & 0x1FF,
        argument & 0x1FF,
    ]
    return {
        "coefficients": [value - 0x200 if value & 0x100 else value for value in values],
        "raw": command_pair_record(pair),
    }


def apply_other_mode_write(
    pair: tuple[int, int] | None, partial: tuple[int, int, int, int] | None,
    command: int, argument: int,
) -> tuple[tuple[int, int] | None, tuple[int, int, int, int] | None]:
    """Apply F3DEX2's reversed shift encoding without inventing inherited bits."""
    opcode = command >> 24
    length = (command & 0xFF) + 1
    shift = 32 - ((command >> 8) & 0xFF) - length
    if opcode not in (0xE2, 0xE3) or command & 0x00FF0000 or not 0 <= shift < 32 or length > 32:
        raise ValueError("invalid partial other-mode write")
    mask = ((1 << length) - 1) << shift
    if argument & ~mask or (opcode == 0xE3 and mask & 0xFF000000):
        raise ValueError("partial other-mode write exceeds its declared bits")
    values = list((pair[0] & 0xFFFFFF, pair[1], 0xFFFFFF, 0xFFFFFFFF)
                  if pair is not None else partial or (0, 0, 0, 0))
    word = 0 if opcode == 0xE3 else 1
    values[word] = (values[word] & ~mask) | argument
    values[word + 2] |= mask
    if values[2:] == [0xFFFFFF, 0xFFFFFFFF]:
        return (0xEF000000 | values[0], values[1]), None
    return None, tuple(values)


def known_other_mode_bits(run: ModelMaterialRun, word: int, mask: int) -> int | None:
    if word not in (0, 1):
        raise ValueError("other-mode word must be high or low")
    if run.other_mode is not None:
        return run.other_mode[word] & mask
    if run.other_mode_partial is not None and run.other_mode_partial[word + 2] & mask == mask:
        return run.other_mode_partial[word] & mask
    return None


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
    texture_detail = (mode_high >> 17) & 3
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
        "texture_detail": {
            0: "clamp",
            1: "sharpen",
            2: "detail",
        }.get(texture_detail, f"reserved-{texture_detail}"),
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
    convert_pair = tuple(state["convert_mode"]) if state.get("convert_mode") else None
    other_pair = tuple(state["other_mode"]) if state.get("other_mode") else None
    combine = decode_combine_mode(combine_pair)
    convert = decode_convert_mode(convert_pair)
    other = decode_other_mode(other_pair)
    if combine is None:
        return {
            "status": "unsupported-missing-combine-mode",
            "baseColorFactor": None,
            "alphaMode": other["gltf_alpha_mode"] if other else None,
            "sampler": other["gltf_sampler"] if other else None,
            "convertMode": convert,
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
    # A common CBFD two-cycle material first places TEXEL0 in COMBINED, then
    # evaluates (SHADE - ENVIRONMENT) * COMBINED + PRIMITIVE.  With the exact
    # captured zero RGB colours this reduces to TEXEL0 * SHADE.  Its alpha path
    # likewise carries TEXEL0 * SHADE through COMBINED and multiplies it by an
    # opaque environment alpha.  Recognize the complete two-cycle expression;
    # inspecting only cycle two makes this family look unsupported.
    two_cycle_texture_product = bool(
        other
        and other["cycle_type"] == "two-cycle"
        and combine["cycles"][0]["color"]
        == ["ZERO", "ZERO", "ZERO", "TEXEL0"]
        and combine["cycles"][0]["alpha"]
        == ["TEXEL0", "ZERO", "SHADE", "ZERO"]
        and color == ["SHADE", "ENVIRONMENT", "COMBINED", "PRIMITIVE"]
        and alpha == ["COMBINED", "ZERO", "ENVIRONMENT", "ZERO"]
        and primitive is not None
        and environment is not None
        and primitive[:3] == [0, 0, 0]
        and environment[:3] == [0, 0, 0]
    )
    if two_cycle_texture_product:
        color_product = True
        alpha_product = True
    first_cycle = combine["cycles"][0]
    first_color_product = first_cycle["color"] == [
        "TEXEL0",
        "ZERO",
        "SHADE",
        "ZERO",
    ] or bool(
        first_cycle["color"]
        == ["TEXEL0", "ENVIRONMENT", "SHADE", "PRIMITIVE"]
        and primitive is not None
        and environment is not None
        and primitive[:3] == [0, 0, 0]
        and environment[:3] == [0, 0, 0]
    )
    two_cycle_combined_product = bool(
        other
        and other["cycle_type"] == "two-cycle"
        and first_color_product
        and first_cycle["alpha"]
        == ["TEXEL0", "ZERO", "SHADE", "ZERO"]
        and color == ["ZERO", "ZERO", "ZERO", "COMBINED"]
        and alpha == ["COMBINED", "ZERO", "ENVIRONMENT", "ZERO"]
        and environment is not None
    )
    if two_cycle_combined_product:
        color_product = True
        alpha_product = True
    two_cycle_rgb_vertex_alpha_texture = bool(
        other
        and other["cycle_type"] == "two-cycle"
        and first_cycle["color"]
        == ["TEXEL0", "ZERO", "SHADE", "ZERO"]
        and first_cycle["alpha"]
        == ["ZERO", "ZERO", "ZERO", "TEXEL0"]
        and color == ["ZERO", "ZERO", "ZERO", "COMBINED"]
        and alpha == ["COMBINED", "ZERO", "ENVIRONMENT", "ZERO"]
        and environment is not None
    )
    # Several one-cycle character materials use vertex lighting only for RGB,
    # while alpha comes directly from TEXEL0 (optionally scaled by ENV alpha).
    # glTF can represent that exactly by forcing the vertex alpha component to
    # one and carrying the RDP alpha scale in baseColorFactor.
    separate_texture_alpha_product = bool(
        color_product
        and (
            alpha == ["ZERO", "ZERO", "ZERO", "TEXEL0"]
            or (
                alpha == ["TEXEL0", "ZERO", "ENVIRONMENT", "ZERO"]
                and environment is not None
            )
        )
    )
    convert_coefficients = convert["coefficients"] if convert is not None else None
    k5_vertex_product = bool(
        other
        and other["cycle_type"] == "two-cycle"
        and combine["cycles"][0]["color"]
        == ["ZERO", "ZERO", "ZERO", "ZERO"]
        and combine["cycles"][0]["alpha"]
        == ["ZERO", "ZERO", "ZERO", "SHADE"]
        and color == ["SHADE", "ENVIRONMENT", "K5", "PRIMITIVE"]
        and alpha == ["COMBINED", "ZERO", "ENVIRONMENT", "ZERO"]
        and primitive is not None
        and environment is not None
        and primitive[:3] == [0, 0, 0]
        and environment[:3] == [0, 0, 0]
        and environment[3] == 255
        and convert_coefficients is not None
        and 0 <= convert_coefficients[5] <= 255
    )
    primitive_texture_alpha_product = bool(
        color == ["ZERO", "ZERO", "ZERO", "PRIMITIVE"]
        and alpha == ["TEXEL0", "ZERO", "PRIMITIVE", "ZERO"]
        and primitive is not None
        and primitive[:3] == [0, 0, 0]
    )
    environment_texture_alpha_product = bool(
        color == ["ENVIRONMENT", "ZERO", "SHADE", "ZERO"]
        and alpha == ["TEXEL0", "ZERO", "ENVIRONMENT", "ZERO"]
        and environment is not None
        and environment[:3] == [0, 0, 0]
    )
    texture_only_product = bool(
        color == ["TEXEL0", "ZERO", "ENVIRONMENT", "ZERO"]
        and alpha == ["ENVIRONMENT", "ZERO", "TEXEL0", "ZERO"]
        and environment == [255, 255, 255, 255]
    )
    shade_alpha_product = bool(
        color == ["ZERO", "ZERO", "ZERO", "SHADE"]
        and (
            alpha == ["ZERO", "ZERO", "ZERO", "SHADE"]
            or (
                alpha == ["SHADE", "ZERO", "ENVIRONMENT", "ZERO"]
                and environment is not None
            )
        )
    )
    shade_primitive_alpha_product = bool(
        color == ["SHADE", "ENVIRONMENT", "PRIMITIVE_ALPHA", "PRIMITIVE"]
        and alpha == ["ZERO", "ZERO", "ZERO", "SHADE"]
        and primitive is not None
        and environment is not None
        and primitive[:3] == [0, 0, 0]
        and primitive[3] == 255
        and environment[:3] == [0, 0, 0]
    )
    vertex_color_product = shade_alpha_product or shade_primitive_alpha_product
    constant_texture_alpha_product = (
        primitive_texture_alpha_product or environment_texture_alpha_product
    )
    gltf_product = (
        color_product and alpha_product
        or k5_vertex_product
        or constant_texture_alpha_product
        or texture_only_product
        or vertex_color_product
        or two_cycle_rgb_vertex_alpha_texture
        or separate_texture_alpha_product
    )
    base_color_factor = (
        [1.0, 1.0, 1.0, environment[3] / 255.0]
        if (
            (two_cycle_texture_product or two_cycle_combined_product)
            and environment is not None
        )
        else [1.0, 1.0, 1.0, environment[3] / 255.0]
        if two_cycle_rgb_vertex_alpha_texture and environment is not None
        else [1.0, 1.0, 1.0, environment[3] / 255.0]
        if separate_texture_alpha_product
        and alpha == ["TEXEL0", "ZERO", "ENVIRONMENT", "ZERO"]
        and environment is not None
        else [component / 255.0 for component in primitive]
        if primitive_texture_alpha_product and primitive is not None
        else [component / 255.0 for component in environment]
        if environment_texture_alpha_product and environment is not None
        else [1.0, 1.0, 1.0, environment[3] / 255.0]
        if shade_alpha_product
        and alpha == ["SHADE", "ZERO", "ENVIRONMENT", "ZERO"]
        and environment is not None
        else [convert_coefficients[5] / 256.0] * 3 + [1.0]
        if k5_vertex_product and convert_coefficients is not None
        else [1.0, 1.0, 1.0, 1.0]
        if color_product or texture_only_product or vertex_color_product
        else None
    )
    needs_mipmap = "LOD_FRACTION" in combine["inputs"] or bool(
        "TEXEL1" in combine["inputs"]
        and other
        and other["texture_lod"] == "lod"
    )
    needs_multiple_textures = "TEXEL1" in combine["inputs"] and not needs_mipmap
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
    elif needs_multiple_textures:
        status = "unsupported-rdp-multitexture"
    elif constant_texture_alpha_product:
        status = "exact-runtime-color-times-texture-alpha"
    elif texture_only_product:
        status = "exact-texture-without-vertex-color"
    elif gltf_product and lighting_enabled:
        status = (
            "requires-runtime-lighting-replay"
            if captured_lights
            else "requires-runtime-lighting"
        )
    elif gltf_product:
        status = (
            "exact-vertex-color-times-factor"
            if k5_vertex_product or vertex_color_product
            else "exact-texture-times-vertex-color"
        )
    elif color_product:
        status = "rgb-only-alpha-combiner-unsupported"
    else:
        status = "unsupported-rdp-combiner"
    return {
        "status": status,
        "baseColorFactor": base_color_factor,
        "alphaMode": other["gltf_alpha_mode"] if other else None,
        "sampler": other["gltf_sampler"] if other else None,
        "lightingEnabled": lighting_enabled,
        "runtimeLightsCaptured": captured_lights,
        "usesTexture": (
            color_product
            or constant_texture_alpha_product
            or texture_only_product
            or two_cycle_rgb_vertex_alpha_texture
        ),
        "usesVertexColor": (
            not (constant_texture_alpha_product or texture_only_product)
            if gltf_product
            else None
        ),
        "vertexAlphaMode": (
            "one"
            if two_cycle_rgb_vertex_alpha_texture or separate_texture_alpha_product
            else "source"
            if gltf_product
            else None
        ),
        "combineCycle": cycle_index + 1,
        "combineFormula": combine,
        "convertMode": convert,
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
    if matrix.get("status") == "invalid-or-uninitialized-at-capture":
        return None
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


def runtime_segment_8_resolution(
    run: ModelMaterialRun | None,
    draw_state: dict[str, Any],
    nested_calls: list[dict[str, Any]],
    payloads_by_address: dict[int, dict[str, Any]],
) -> dict[str, Any] | None:
    """Resolve one static segment-8 state reference through captured runtime state."""

    if run is None:
        return None
    offset = run.runtime_render_state_offset
    if offset is None:
        return None
    segmented_address = 0x08000000 | int(offset)
    segments = draw_state.get("segments", {})
    base = segments.get("8", segments.get(8))
    result: dict[str, Any] = {
        "segment": 8,
        "offset": f"0x{int(offset):X}",
        "segmented_address": f"0x{segmented_address:08X}",
        "segment_base": f"0x{int(base):08X}" if isinstance(base, int) else None,
        "resolved_address": None,
        "payload_sha256": None,
        "payload_length": None,
        "other_mode": None,
        "matches_effective_other_mode": None,
    }
    if not isinstance(base, int):
        result["status"] = "segment-base-unavailable"
        return result
    resolved_address = (base + int(offset)) & 0xFFFFFFFF
    result["resolved_address"] = f"0x{resolved_address:08X}"
    matches = [
        call
        for call in nested_calls
        if int(call.get("address", -1)) == segmented_address
        and int(call.get("resolved_address", -1)) == resolved_address
    ]
    if not matches:
        result["status"] = "segment-base-only-no-matching-call"
        return result
    payload = payloads_by_address.get(resolved_address)
    if payload is None:
        result["status"] = "resolved-call-without-payload"
        return result
    encoded = payload.get("data_base64")
    if not isinstance(encoded, str):
        raise ValueError("runtime segment-8 payload has no encoded bytes")
    data = base64.b64decode(encoded)
    if len(data) % 8 or hashlib.sha256(data).hexdigest() != payload.get("sha256"):
        raise ValueError("runtime segment-8 payload identity changed")
    commands = list(struct.iter_unpack(">II", data))
    result["payload_sha256"] = payload["sha256"]
    result["payload_length"] = len(data)
    if commands and commands[0][0] >> 24 == 0xEF:
        other_mode = [commands[0][0], commands[0][1]]
        result["other_mode"] = other_mode
        result["matches_effective_other_mode"] = (
            draw_state.get("other_mode") == other_mode
        )
    result["status"] = (
        "exact-runtime-list-effective-state"
        if result["matches_effective_other_mode"] is True
        else "exact-runtime-list-state-later-overridden"
    )
    return result


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
    # CBFD deliberately leaves vertices with a negative signed flag unlit.
    if vertex.flag & 0x8000:
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

    modifiers = lights.get("coordinate_modifiers")
    if (
        not isinstance(modifiers, list)
        or len(modifiers) < 15
        or any(modifiers[index] is None for index in (8, 9, 10, 12, 13, 14))
    ):
        return None
    rows = context.get("combined_rows") if isinstance(context, dict) else None
    if (not isinstance(rows, list) or len(rows) != 4
            or any(not isinstance(row, list) or len(row) != 4 for row in rows)
            or any(not math.isfinite(float(v)) for row in rows for v in row)):
        return None
    # gSPProcessVertex transforms XYZ before CBFD point-light attenuation.
    # Perspective division happens later and must not be applied here.
    transformed_position = [
        sum(float(value) * float(rows[row][axis])
            for row, value in enumerate((vertex.x, vertex.y, vertex.z, 1)))
        for axis in range(3)
    ]
    vertex_position = [
        (coordinate + float(modifiers[8 + axis]))
        * float(modifiers[12 + axis])
        for axis, coordinate in enumerate(transformed_position)
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


def captured_vertex_sources(event: dict[str, Any]) -> list[tuple[int, bytes, str]]:
    """Read hash-checked memory spans covering the event's actual VTX inputs."""

    probes = event.get("evidence", {}).get("memory", [])
    tasks = [probe for probe in probes if probe.get("name") == "task"]
    roots = [probe for probe in probes if probe.get("name") == "command-buffer"]
    # CBFD resets its basic/advanced lighting mode at the task boundary.
    # A renderer-return subrange cannot establish that inherited initial state.
    if len(tasks) != 1 or len(roots) != 1:
        return []
    task, root = tasks[0], roots[0]
    task_bytes = base64.b64decode(task["data_base64"], validate=True)
    if len(task_bytes) != 64 or hashlib.sha256(task_bytes).hexdigest() != task.get("sha256"):
        raise ValueError("captured graphics task bytes changed")
    if (int.from_bytes(task_bytes[:4], "big") != 1
            or (int.from_bytes(task_bytes[48:52], "big") & 0x1FFFFFFF)
            != (int(root["resolved_address"], 0) & 0x1FFFFFFF)
            or int.from_bytes(task_bytes[52:56], "big") != root["length"]):
        return []
    loads = event.get("state", {}).get("rdp", {}).get("replayed_vertex_loads", [])
    spans = [(load["resolved_address"], 16 * load["vertex_count"])
             for load in loads if isinstance(load.get("resolved_address"), int)]
    result = []
    for probe in probes:
        address = probe.get("resolved_address")
        if not isinstance(address, str):
            continue
        base = int(address, 0)
        size = probe.get("length", 0)
        if not any(base <= start and start + length <= base + size for start, length in spans):
            continue
        data = base64.b64decode(probe["data_base64"], validate=True)
        if len(data) != size or hashlib.sha256(data).hexdigest() != probe.get("sha256"):
            raise ValueError("captured vertex bytes changed")
        result.append((base, data, probe["sha256"]))
    return result


def captured_draw_vertices(
    draw: dict[str, Any], loads: list[dict[str, Any]],
    sources: list[tuple[int, bytes, str]], geometry: ModelGeometry, first_face: int,
) -> list[list[tuple[ModelVertex, dict[str, Any], int, list[str]]]] | None:
    """Match captured VTX bytes to source corners, independently of lighting."""

    indices = draw.get("replayed_vertex_load_indices", [])
    cache_indices = draw.get("replayed_vertex_cache_indices", [])
    if len(indices) != draw.get("triangle_count") or len(cache_indices) != len(indices):
        return None
    # The archive's stable face ordering for TRI4 differs from GLideN64's
    # emitted triangle ordering. Join the three cache slots, not array position.
    ordered = []
    for face_index in range(first_face, first_face + len(indices)):
        if not 0 <= face_index < len(geometry.face_cache_indices):
            return None
        matches = [(face_loads, slots) for face_loads, slots in zip(indices, cache_indices)
                   if tuple(slots) == geometry.face_cache_indices[face_index]]
        if not matches or len({tuple(face_loads) for face_loads, _ in matches}) != 1:
            return None
        ordered.append(matches[0])
    faces = []
    for face_offset, (face_loads, slots) in enumerate(ordered):
        face_index = first_face + face_offset
        if not 0 <= face_index < len(geometry.faces) or len(face_loads) != 3 or len(slots) != 3:
            return None
        if geometry.face_cache_indices and tuple(slots) != geometry.face_cache_indices[face_index]:
            return None
        corners = []
        for source_index, load_index, slot in zip(geometry.faces[face_index], face_loads, slots):
            if not isinstance(load_index, int) or not 0 <= load_index < len(loads):
                return None
            load = loads[load_index]
            local_index = slot - load["first_cache_index"]
            address = load.get("resolved_address")
            if not isinstance(address, int) or not 0 <= local_index < load["vertex_count"]:
                return None
            address += 16 * local_index
            matches = [(data[address-base:address-base+16], digest)
                       for base, data, digest in sources if base <= address and address+16 <= base+len(data)]
            if not matches or len({data for data, _ in matches}) != 1:
                return None
            raw = matches[0][0]
            x, y, z, flag, s, t, r, g, b, a = struct.unpack(">hhhHhh4B", raw)
            source_vertex = geometry.vertices[source_index]
            if (x, y, z) != (source_vertex.x, source_vertex.y, source_vertex.z):
                return None
            vertex = ModelVertex(x, y, z, flag, s, t, (r, g, b, a))
            corners.append((vertex, load, slot, [digest for _, digest in matches]))
        faces.append(corners)
    return faces


def replay_draw_vertex_colours(
    draw: dict[str, Any], loads: list[dict[str, Any]],
    sources: list[tuple[int, bytes, str]], geometry: ModelGeometry, first_face: int,
) -> dict[str, Any] | None:
    """Replay captured VTX colours only after proving the exact source corners."""

    faces = captured_draw_vertices(draw, loads, sources, geometry, first_face)
    if faces is None:
        return None
    colours = []
    input_hashes = set()
    for face in faces:
        face_colours = []
        for vertex, load, slot, digests in face:
            state = load["state"]
            context = load.get("processing_matrices", {})
            if not state.get("lighting_enabled_known") or context.get("combined_rows") is None:
                return None
            normal_xy = (state.get("normal_base") or {}).get("normal_xy_s8", [])
            flag = vertex.flag
            normal = (*normal_xy[slot], (flag & 255) - (256 if flag & 128 else 0)) if slot < len(normal_xy) else None
            colour = replay_cbfd_vertex_lighting(vertex, normal, state, context)
            if colour is None or any(not math.isfinite(v) or not 0 <= v <= 1 for v in colour):
                return None
            face_colours.append(list(colour))
            input_hashes.update(digests)
            input_hashes.add(hashlib.sha256(json.dumps(
                {"state": state, "processing_matrices": context}, sort_keys=True,
                separators=(",", ":"),
            ).encode()).hexdigest())
        colours.append(face_colours)
    result = {"status": "captured-cbfd-vertex-load-colours", "source_first_face": first_face,
              "face_colours": colours, "input_sha256": sorted(input_hashes)}
    result["sha256"] = hashlib.sha256(json.dumps(result, sort_keys=True, separators=(",", ":")).encode()).hexdigest()
    return result


def validate_vertex_lighting_sample(sample: dict[str, Any], first: int, count: int) -> None:
    payload = {key: value for key, value in sample.items() if key != "sha256"}
    if hashlib.sha256(json.dumps(payload, sort_keys=True, separators=(",", ":")).encode()).hexdigest() != sample.get("sha256"):
        raise ValueError("runtime vertex lighting sample hash changed")
    colours = sample.get("face_colours")
    hashes = sample.get("input_sha256")
    if (sample.get("status") != "captured-cbfd-vertex-load-colours"
            or sample.get("source_first_face") != first
            or not isinstance(colours, list) or len(colours) != count
            or any(not isinstance(face, list) or len(face) != 3 for face in colours)
            or any(not isinstance(colour, list) or len(colour) != 4
                   or any(not isinstance(v, (int, float)) or not math.isfinite(v) or not 0 <= v <= 1 for v in colour)
                   for face in colours for colour in face)
            or not isinstance(hashes, list) or not hashes
            or any(not isinstance(digest, str) or re.fullmatch(r"[0-9a-f]{64}", digest) is None for digest in hashes)):
        raise ValueError("runtime vertex lighting sample shape changed")


def runtime_vertex_colour_map(record: dict[str, Any] | None) -> dict[int, tuple]:
    """Require matching colour evidence from every observation of each face."""

    if record is None or len(record.get("variants", [])) != 1:
        return {}
    colours: dict[int, tuple | None] = {}
    for evidence in record["variants"][0].get("evidence", []):
        first, count = evidence.get("source_first_face"), evidence.get("source_face_count")
        if not isinstance(first, int) or not isinstance(count, int):
            return {}
        if not record["source_first_face"] <= first < first + count <= record["source_first_face"] + record["source_face_count"]:
            raise ValueError("runtime vertex lighting observation exceeds source material")
        sample = evidence.get("vertex_lighting")
        if isinstance(sample, dict):
            validate_vertex_lighting_sample(sample, first, count)
        values = sample.get("face_colours", []) if isinstance(sample, dict) else []
        for offset in range(count):
            value = tuple(tuple(c) for c in values[offset]) if len(values) == count else None
            index = first + offset
            if index not in colours:
                colours[index] = value
            elif colours[index] != value:
                colours[index] = None
    return {index: value for index, value in colours.items() if value is not None}


def runtime_face_culling_map(record: dict[str, Any] | None) -> dict[int, int | None]:
    """Require consistent checked draw evidence for each observed source face."""

    if record is None:
        return {}
    observations: dict[int, set[int | None]] = {}
    for variant in record.get("variants", []):
        for evidence in variant.get("evidence", []):
            if evidence.get("material_correlation_status") == "equivalent-material-aliases":
                # Shared triangle/material patterns do not identify which
                # source list supplied its inherited geometry state.
                return {}
            state = evidence.get("face_culling")
            first, count = evidence.get("source_first_face"), evidence.get("source_face_count")
            if not isinstance(state, dict) or not isinstance(first, int) or not isinstance(count, int):
                # Legacy or unbounded observations cannot establish a face's
                # complete set of captured states. Retain its static evidence.
                return {}
            if not record["source_first_face"] <= first < first + count <= record["source_first_face"] + record["source_face_count"]:
                raise ValueError("runtime culling observation exceeds source material")
            mode, known = state.get("mode"), state.get("known_bits")
            if (not isinstance(known, int) or known & ~0x600
                    or (known == 0x600 and mode not in (0, 0x200, 0x400, 0x600))
                    or (known != 0x600 and mode is not None)):
                raise ValueError("runtime culling observation has invalid known bits")
            for index in range(first, first + count):
                observations.setdefault(index, set()).add(mode)
    return {index: next(iter(values)) if len(values) == 1 else None
            for index, values in observations.items()}


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
    if run.texture_dimensions is not None:
        width, height = run.texture_dimensions
        uls = (run.tile_bounds[0] >> 12) & 0xFFF if run.tile_bounds else 0
        ult = run.tile_bounds[0] & 0xFFF if run.tile_bounds else 0
        dimension_evidence = "runtime-load-block-tile-masks"
    elif run.tile_bounds is not None:
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
    if run.texture_dimensions is None:
        mask_dimensions = direct_ci4_mask_dimensions(run)
        if mask_dimensions is not None:
            # Unclamped tiles wrap at their mask period, even when SetTileSize
            # describes smaller bounds. Use the same complete image extent
            # for decoding and UV normalization; retain the tile's origin.
            width, height = mask_dimensions
            dimension_evidence = "direct-load-block-tile-masks"
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


def direct_ci4_mask_dimensions(run: ModelMaterialRun) -> tuple[int, int] | None:
    """Prove a complete repeating CI4 image from its masks and LoadBlock."""

    if run.render_tile is None or run.pixel is None or run.palette is None:
        return None
    command, argument = run.render_tile
    mask_s, mask_t = (argument >> 4) & 15, (argument >> 14) & 15
    other = decode_other_mode(run.other_mode)
    if (
        (command >> 21) & 7 != 2 or (command >> 19) & 3 != 0
        or command & 0x1FF
        or argument & ((2 << 8) | (2 << 18))
        or not mask_s or not mask_t
        or run.pixel.image_command != 0xFD500000 or run.pixel.mode != 0
        or run.palette.image_command != 0xFD100000 or run.palette.mode != 2
        or run.pixel.flat_index is None
        or run.pixel.flat_index != run.palette.flat_index
        or run.pixel.load_command is None
        or other is None or other["texture_lut"] != "rgba16"
    ):
        return None
    load_command, load_argument = run.pixel.load_command
    if load_command != 0xF3000000 or load_argument & 0xFFF:
        return None
    tiles = {index: value for index, value, _ in run.render_tiles}
    load_tile = tiles.get((load_argument >> 24) & 7)
    if load_tile is None or load_tile & 0x1FF:
        return None
    width, height = 1 << mask_s, 1 << mask_t
    stride = ((command >> 9) & 0x1FF) * 8
    loaded_bytes = (((load_argument >> 12) & 0xFFF) + 1) * 2
    # Nonzero masks give even dimensions. The final odd row's word swap
    # requires its entire stride to be loaded, not just the visible pixels.
    if stride < width // 2 or height * stride > min(loaded_bytes, 2048):
        return None
    return width, height


def shifted_texture_coordinate(value: float, shift: int) -> float:
    if shift <= 10:
        return value / (1 << shift)
    return value * (1 << (16 - shift))


def texture_coordinates(vertex: ModelVertex, run: ModelMaterialRun) -> tuple[float, float]:
    if run.preview_coordinate_state is not None:
        tile, bounds, dimensions = run.preview_coordinate_state
        run = replace(run, render_tile=tile, tile_bounds=bounds, texture_dimensions=dimensions,
                      preview_coordinate_state=None)
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
    _, argument = (run.preview_coordinate_state[0]
                   if run.preview_coordinate_state is not None else run.render_tile)
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


def face_culling_spans(
    geometry: ModelGeometry, run: ModelMaterialRun,
    runtime_modes: dict[int, int | None] | None = None,
) -> list[tuple[int, int, int | None]]:
    """Partition a source material without changing its identity or face order."""

    if geometry.face_cull_modes and len(geometry.face_cull_modes) != len(geometry.faces):
        raise ValueError("culling state does not cover every source face")
    spans = []
    start = run.first_face
    end = start + run.face_count
    for index in range(start, end):
        mode = geometry.face_cull_modes[index] if geometry.face_cull_modes else None
        if runtime_modes is not None and index in runtime_modes:
            mode = runtime_modes[index]
        if spans and spans[-1][2] == mode:
            first, count, _ = spans[-1]
            spans[-1] = (first, count + 1, mode)
        else:
            spans.append((index, 1, mode))
    return spans


def encode_gltf(
    bundle_index: int,
    segment_index: int,
    geometry: ModelGeometry,
    texture_files: dict[str | int, str] | None = None,
    bank_index: int = DEFAULT_BANK_INDEX,
    character_joints: tuple[dict[str, Any], ...] | None = None,
    character_rotations: tuple[tuple[float, float, float, float], ...] | None = None,
    character_pose_source: str | None = None,
    character_animation_clips: tuple[CharacterAnimationClip, ...] = (),
    output_stem: str | None = None,
    runtime_materials: dict[int, dict[str, Any]] | None = None,
    character_morphs: dict[str, Any] | None = None,
    character_draw_pass: dict[str, Any] | None = None,
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
    if character_morphs is not None and (bank_index != 1 or bundle_index != character_morphs["character_entry"]):
        raise ValueError("morph targets belong to a different character model")
    morph_deltas = model_morphs.target_deltas(character_morphs, geometry) if character_morphs else []
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

    def geometric_face_normal(face: tuple[int, int, int], matrices: tuple[int, int, int]):
        positions = []
        for index, matrix in zip(face, matrices):
            vertex = geometry.vertices[index]
            pivot = character_global_pivots.get(matrix, (0.0, 0.0, 0.0))
            positions.append((vertex.x + pivot[0], vertex.y + pivot[1], vertex.z + pivot[2]))
        result = normalized(_triangle_cross(tuple(positions)))
        return result or (0.0, 0.0, 1.0)

    for run_index, run in enumerate(geometry.material_runs):
        if run.face_count == 0:
            continue
        runtime_material = (
            runtime_materials.get(run_index) if runtime_materials is not None else None
        )
        runtime_consensus = runtime_material_consensus(runtime_material)
        face_colours = runtime_vertex_colour_map(runtime_material)
        source_faces = [geometry.face_source_indices[i] if geometry.face_source_indices else i
                        for i in range(run.first_face, run.first_face + run.face_count)]
        captured_culling = runtime_face_culling_map(runtime_material)
        runtime_culling = {}
        conflicting_culling_faces = set()
        for offset, source_face in enumerate(source_faces):
            if source_face not in captured_culling:
                continue
            face = run.first_face + offset
            source_mode = geometry.face_cull_modes[face] if geometry.face_cull_modes else None
            captured_mode = captured_culling[source_face]
            if source_mode is not None and captured_mode != source_mode:
                # Command-pattern correlations alone do not prove a runtime
                # rewrite of an explicit ROM geometry-mode command.
                conflicting_culling_faces.add(face)
            else:
                runtime_culling[face] = captured_mode
        has_replayed_colours = all(index in face_colours for index in source_faces)
        force_vertex_alpha_one = is_character_trilinear_base(run) or bool(
            is_direct_ia4_trilinear_base(run)
            and decode_combine_mode(run.combine_mode)["cycles"][1]["alpha"]
            == ["ZERO", "ZERO", "ZERO", "COMBINED"]
        ) or bool(
            runtime_consensus
            and runtime_consensus["baseColorFactor"] is not None
            and runtime_consensus["vertexAlphaMode"] == "one"
            and (
                has_replayed_colours
                or not any(
                    status.startswith("requires-runtime-lighting")
                    for status in runtime_consensus["statuses"]
                )
            )
        )
        source_vertex_indices = []
        source_matrix_indices = []
        source_normals = []
        source_replayed_colours = []
        local_vertex_indices = {}
        local_faces = []
        for face_offset, face in enumerate(
            geometry.faces[run.first_face : run.first_face + run.face_count]
        ):
            face_index = run.first_face + face_offset
            vertex_matrices = face_vertex_matrix_indices(geometry, run, face_index)
            raw_normals = (
                geometry.face_normal_bytes[face_index]
                if geometry.face_normal_bytes
                else None
            )
            preview_normals = (
                geometry.face_preview_normals[face_index]
                if geometry.face_preview_normals else None
            )
            has_normal_evidence = bool(raw_normals or preview_normals)
            fallback_normal = (
                geometric_face_normal(face, vertex_matrices) if has_normal_evidence else None
            )
            local_face = []
            for corner, source_index in enumerate(face):
                raw_normal = raw_normals[corner] if raw_normals else None
                decoded_source_normal = normalized(raw_normal) if raw_normal else None
                source_normal = (
                    normalized(preview_normals[corner])
                    if preview_normals and preview_normals[corner] is not None
                    else None if preview_normals else decoded_source_normal
                )
                normal_defined = source_normal is not None
                if has_normal_evidence and source_normal is None:
                    source_normal = fallback_normal
                vertex_key = (
                    (
                        source_index,
                        (source_normal if preview_normals else raw_normal)
                        if normal_defined
                        else ("fallback", face_index),
                    )
                    if has_normal_evidence
                    else source_index
                )
                if character_joints:
                    vertex_key = (vertex_key, vertex_matrices[corner])
                replay_colour = face_colours[source_faces[face_offset]][corner] if has_replayed_colours else None
                if replay_colour is not None:
                    vertex_key = (vertex_key, replay_colour)
                if vertex_key not in local_vertex_indices:
                    local_vertex_indices[vertex_key] = len(source_vertex_indices)
                    source_vertex_indices.append(source_index)
                    source_matrix_indices.append(vertex_matrices[corner])
                    source_replayed_colours.append(replay_colour)
                    if source_normal is not None:
                        source_normals.append(source_normal)
                local_face.append(local_vertex_indices[vertex_key])
            local_faces.append(tuple(local_face))
        vertices = [geometry.vertices[index] for index in source_vertex_indices]
        if character_joints:
            try:
                bind_pivots = [
                    character_global_pivots[index] for index in source_matrix_indices
                ]
            except KeyError as error:
                raise ValueError(
                    f"character vertex load references absent joint {error.args[0]}"
                ) from error
            positions = [
                (
                    float(vertex.x) + float(bind_pivot[0]),
                    float(vertex.y) + float(bind_pivot[1]),
                    float(vertex.z) + float(bind_pivot[2]),
                )
                for vertex, bind_pivot in zip(vertices, bind_pivots)
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
        replayed_colors = source_replayed_colours if has_replayed_colours else []
        if force_vertex_alpha_one:
            replayed_colors = [
                (*color[:3], 1.0) if color is not None else None
                for color in replayed_colors
            ]
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
                b"".join(
                    bytes((*vertex.color[:3], 255))
                    if force_vertex_alpha_one
                    else bytes(vertex.color)
                    for vertex in vertices
                ),
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
                    struct.pack("<4H", joint_index, 0, 0, 0)
                    for joint_index in source_matrix_indices
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
        if (
            runtime_consensus
            and runtime_consensus["exact"]
            and runtime_consensus["usesVertexColor"] is False
        ):
            attributes.pop("COLOR_0", None)
        if (runtime_material is None and is_direct_rgba32_texture_mipmap_base(run)
                and texture_files is not None and name in texture_files):
            # The explicit second cycle has no SHADE input in either channel.
            # Preserve source colours without applying an unused SHADE multiplier.
            attributes["_SOURCE_COLOR_0"] = attributes.pop("COLOR_0")
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
                **({"otherModePartial": list(run.other_mode_partial)} if run.other_mode_partial is not None else {}),
                "runtimeRenderStateOffset": (
                    f"0x{run.runtime_render_state_offset:X}"
                    if run.runtime_render_state_offset is not None
                    else None
                ),
                "textureAddressMode": texture_address_mode(run),
                **({"romDetailTexturePreview": detail_texture_preview_record(run)}
                   if run.preview_coordinate_state is not None else {}),
                "vertexLoadMatrixIndices": sorted(set(source_matrix_indices)),
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
                    "captured-cbfd-vertex-load-colours"
                    if lighting_replayed
                    else "not-baked-ambiguous-or-incomplete"
                ),
                "sourceFaceCount": run.face_count if lighting_replayed else 0,
            }
            if runtime_consensus and runtime_consensus["baseColorFactor"] is not None:
                material["pbrMetallicRoughness"]["baseColorFactor"] = (
                    runtime_consensus["baseColorFactor"]
                )
        texture_file = (
            texture_files.get(run_index, texture_files.get(name))
            if texture_files is not None
            else None
        )
        if runtime_consensus and runtime_consensus["referencesTexels"] is False:
            texture_file = None
        if texture_file is not None:
            static_material = None
            if runtime_material is None and run.other_mode is not None:
                # Filtering and blend state belong to the draw, independently
                # of the texture's storage format. Keep colour/lighting limits
                # explicit while preserving these known ROM fields.
                static_material = translate_runtime_material_state({
                    "combine_mode": run.combine_mode, "other_mode": run.other_mode,
                })
                material["extras"]["staticMaterialPreview"] = {
                    "source": "ROM-display-list",
                    "colourStatus": static_material["status"],
                    "nativeRasterParity": "unverified",
                }
            address_mode = texture_address_mode(run)
            if address_mode is None:
                raise ValueError("linked texture material lacks render-tile state")
            wrap_s = address_mode["gltf"]["wrapS"]
            wrap_t = address_mode["gltf"]["wrapT"]
            sampler_state = (
                runtime_consensus["sampler"]
                if runtime_consensus and runtime_consensus["sampler"] is not None
                else static_material["sampler"]
                if static_material and static_material["sampler"] is not None
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
            if is_character_trilinear_base(run):
                material["extras"]["textureLodPreview"] = {
                    "source": "stored-highest-resolution-TEXEL0",
                    "combiner": "G_CC_TRILERP-at-zero-LOD-fraction",
                    "minification": "glTF-consumer-generated-mipmaps",
                    "nativeDistanceDependentLodParity": "unverified",
                    "vertexAlpha": "ignored-by-proven-combiner",
                }
            elif is_character_rgb_trilinear_base(run):
                material["extras"]["textureLodPreview"] = {
                    "source": "stored-highest-resolution-TEXEL0",
                    "combiner": "RGB-trilerp-at-zero-LOD-fraction; alpha=TEXEL0*SHADE*ENVIRONMENT",
                    "minification": "glTF-consumer-generated-mipmaps",
                    "nativeDistanceDependentLodParity": "unverified",
                    "vertexAlpha": "preserved-for-texture-times-shade-alpha",
                }
            material["alphaMode"] = (
                static_material["alphaMode"]
                if static_material and static_material["alphaMode"] is not None
                else "MASK"
            )
            if material["alphaMode"] == "MASK":
                material["alphaCutoff"] = 0.5
        if runtime_consensus and runtime_consensus["alphaMode"] is not None:
            material["alphaMode"] = runtime_consensus["alphaMode"]
            if material["alphaMode"] == "MASK":
                material["alphaCutoff"] = 0.5
            else:
                material.pop("alphaCutoff", None)
        if lighting_replayed:
            material["extensions"] = {"KHR_materials_unlit": {}}
        culling_spans = face_culling_spans(geometry, run, runtime_culling)
        morph_accessors = []
        for deltas in morph_deltas:
            positions = [deltas.get(index, (0, 0, 0)) for index in source_vertex_indices]
            morph_accessors.append({"POSITION": append_accessor(
                b"".join(struct.pack("<3f", *position) for position in positions),
                5126, "VEC3", len(positions), 34962,
                [min(position[axis] for position in positions) for axis in range(3)],
                [max(position[axis] for position in positions) for axis in range(3)],
            )})
        for span_index, (first, count, cull_mode) in enumerate(culling_spans):
            span_material = copy.deepcopy(material)
            span_material["doubleSided"] = cull_mode != 0x400
            span_material["extras"]["faceCulling"] = {
                "source": "ROM-display-list-analysis",
                "mode": {None: "inherited-unresolved", 0: "disabled", 0x400: "back",
                         0x200: "front-unresolved", 0x600: "both-unresolved"}[cull_mode],
                "sourceBits": f"0x{cull_mode:03X}" if cull_mode is not None else None,
            }
            observed_culling_faces = sum(index in runtime_culling for index in range(first, first + count))
            if observed_culling_faces:
                span_material["extras"]["faceCulling"].update(
                    source=("captured-command-replay" if observed_culling_faces == count
                            else "ROM-and-captured-command-analysis"),
                    runtimeObservedFaceCount=observed_culling_faces,
                )
            conflict_count = sum(index in conflicting_culling_faces for index in range(first, first + count))
            if conflict_count:
                span_material["extras"]["faceCulling"]["runtimeConflictFaceCount"] = conflict_count
            span_material["extras"]["firstFace"] = first
            span_material["extras"]["faceCount"] = count
            span_indices = index_accessor
            if len(culling_spans) > 1:
                span_material["name"] += f"_cull_span_{span_index}"
                indices = [index for face in local_faces[first - run.first_face:first - run.first_face + count]
                           for index in face]
                span_indices = append_accessor(
                    b"".join(struct.pack("<H", index) for index in indices),
                    5123, "SCALAR", len(indices), 34963, [min(indices)], [max(indices)],
                )
            material_index = len(materials)
            materials.append(span_material)
            primitive = {
                "attributes": attributes,
                "indices": span_indices,
                "material": material_index,
                "mode": 4,
                "extras": {"matrixIndex": run.matrix_index, "firstFace": first, "faceCount": count},
            }
            if morph_accessors:
                primitive["targets"] = morph_accessors
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
    if not primitives:
        # glTF forbids empty mesh/material arrays. Preserve the source record
        # and its hierarchy as nodes, without inventing drawable geometry.
        document.pop("meshes")
        document.pop("materials")
        for node in nodes:
            node.pop("mesh", None)
            node.pop("skin", None)
        if not binary:
            for field in ("buffers", "bufferViews", "accessors"):
                document.pop(field)
    if skins is not None:
        document["skins"] = skins
        document["extras"] = {
            "characterJointHierarchy": "runtime-proven-func_150A81D0",
            "skinningStatus": "rigid-vertex-load-matrix-assignment-proven",
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
            "characterMatrixState": CHARACTER_RUNTIME_MATRIX_STATE,
            "previewPose": character_pose_source
            or "neutral-bind-pose-no-semantic-action-selected",
            "coordinateConversion": "none-native-axes",
            "animationStatus": (
                "runtime-proven-rotation-root-and-masked-joint-translation-channels"
                if animations
                else "no-compatible-nonempty-bank-02-clips"
            ),
        }
        if bank_index == 0x09:
            extras = document["extras"]
            extras.pop("characterColorState")
            extras.pop("characterMatrixState")
            extras["attachmentColorState"] = {
                "renderer": "func_150311C4", "status": "runtime-capture-required",
            }
            extras["attachmentMatrixState"] = {
                "renderer": "func_150311C4", "selector": "func_15031070",
                "pose_builder": "func_150A81D0", "converter": "func_150A9984",
                "segment": 3, "parent_transform": "runtime-capture-required",
            }
            extras["animationStatus"] = "attachment-animation-not-recovered"
    if animations:
        document["animations"] = animations
    if character_morphs is not None:
        for mesh in meshes:
            mesh["weights"] = [0.0] * len(morph_deltas)
            mesh["extras"] = {"targetNames": [target["name"] for target in character_morphs["targets"]]}
        document.setdefault("extras", {})["romMorphTargets"] = {
            "bank": 0x13, "entry": character_morphs["bank_entry"],
            "sourceSha1": character_morphs["source_sha1"],
            "modelSha1": character_morphs["model_sha1"],
            "shapeCount": len(morph_deltas), "vertexStarts": character_morphs["vertex_starts"],
            "partVertexCounts": character_morphs["part_vertex_counts"],
            "basisStatus": character_morphs["basis_status"],
            "interpolation": "stored-endpoints; runtime shape selection and timing not inferred",
            "nativeQuantization": "runtime truncates intermediate XYZ to s16; glTF uses floating point",
        }
    if character_draw_pass is not None:
        if bank_index != 1:
            raise ValueError('character draw-pass selection belongs to bank 01')
        document.setdefault('extras', {})['romCharacterDrawPass'] = character_draw_pass
    if geometry.face_preview_normals:
        document.setdefault("extras", {})["characterNormalStatus"] = (
            "source-normal-inverse-transpose-per-vertex-load-matrix-with-geometric-fallback"
        )
    if any("KHR_materials_unlit" in material.get("extensions", {}) for material in materials):
        document["extensionsUsed"] = ["KHR_materials_unlit"]
    if not primitives:
        document.setdefault("extras", {}).update(
            geometryStatus="empty-drawable-geometry", drawableFaceCount=0)
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
    texture_root: Path, normalized_sha1: str,
    runtime_flat_indices: tuple[int, ...] | None = None,
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
                flat_index=(
                    runtime_flat_indices[record["flat_index"]]
                    if runtime_flat_indices is not None
                    else record["flat_index"]
                ),
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
    """Load flat payloads by the runtime loader's IDs, including empty slots."""

    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, _ = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest != normalized_sha1 or digest not in layout["normalized_sha1"]:
        raise ValueError("character texture payloads are from a different ROM")
    start, end = layout["flat_assets_start"], layout["flat_assets_end"]
    if profile != "us":
        raise ValueError("runtime flat asset size table is only proven for US")
    game = parse_game_archive(normalized[layout["game_start"] : layout["game_end"]])
    # func_1510D374 sums D_80091D20[0:asset_id]; func_1510D0EC
    # returns the empty-asset sentinel for a zero table entry. These two US
    # slots have no deflate stream and must not renumber every later texture.
    compressed_sizes = struct.unpack_from(
        f">{RUNTIME_FLAT_ASSET_COUNT}H",
        game.data, RUNTIME_FLAT_SIZE_TABLE - layout["game_data_vram"]
    )
    return {
        entry.index: entry.data
        for entry in iter_indexed_flat_rzip_entries(normalized[start:end], compressed_sizes)
    }


def flat_asset_identity(payloads: dict[int, bytes] | None) -> dict[str, Any] | None:
    if payloads is None:
        return None
    return {
        "model_reference_ids": "runtime-compressed-size-table",
        "size_table_address": f"0x{RUNTIME_FLAT_SIZE_TABLE:08X}",
        "runtime_slot_count": RUNTIME_FLAT_ASSET_COUNT,
        "physical_stream_count": len(payloads),
        "empty_runtime_slots": sorted(set(range(RUNTIME_FLAT_ASSET_COUNT)) - payloads.keys()),
        "source_texture_manifest_ids": "physical-stream-ordinal-remapped-through-size-table",
    }


def character_runtime_preview_texture(
    run: ModelMaterialRun, payload: bytes
) -> tuple[PreviewTexture | None, str]:
    """Compose the CI image and TLUT bytes selected by ``func_1510CE60``.

    Character display lists load a flat payload into TMEM through an RGBA16
    transfer tile, then reinterpret the selected TMEM span as CI4/CI8. The
    loader tests mode bit 0 at ``0x1510CFBC`` and mode bit 1 at
    ``0x1510CFE8``: mode one selects payload end minus 0x200, while mode two
    selects payload end minus 0x20. The fifth argument only controls the
    reference bookkeeping table. This function mirrors that
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
    palette_byte_offset = len(payload) - palette_size
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


def replay_lower_tmem(run, payloads, *, rgba32=False):
    """Replay supported transfers into lower TMEM, retaining byte ownership.

    RGBA32 writes RG halfwords here and BA halfwords into upper TMEM. The
    latter invalidates the remembered TLUT and cannot extend the CI8 path.
    """
    memory, owners, loads = bytearray(2048), [None] * 2048, []
    sizes = []
    last_pixel = last_palette = None
    for binding, tile in run.texture_loads:
        if binding is None or binding.load_command is None or tile is None:
            owners, last_pixel, last_palette = [None] * 2048, None, None
            continue
        command, argument = binding.load_command
        if (command == 0xF0000000 and argument & 0xFFFFFF == 0x3FC000
                and tile[0] in (0xF5000100, 0xF5600100)
                and tile[1] == argument & 0x07000000):
            # A complete TLUT occupies upper TMEM; it leaves CI indices alone.
            last_palette = binding
            continue
        payload = payloads.get(binding.flat_index)
        size = 3 if rgba32 and binding.image_command == 0xFD180000 else 2
        count = (((argument >> 12) & 4095) + 1) * (1 << (size - 1))
        span = count // 2 if size == 3 else count
        destination = (tile[0] & 511) * 8
        if (command != 0xF3000000 or argument & 0xFFF
                or binding.image_command != (0xFD180000 if size == 3 else 0xFD100000) or binding.mode != 0
                or binding.external or binding.segment is not None
                or tile[0] & ~511 != (0xF5180000 if size == 3 else 0xF5100000) or tile[1] != argument & 0x07000000
                or count % 8 or payload is None or count > len(payload)
                or destination + span > 2048):
            owners, last_pixel, last_palette = [None] * 2048, None, None
            continue
        index = len(loads)
        loads.append((binding.flat_index, hashlib.sha1(payload).hexdigest(), destination, count))
        sizes.append(16 if size == 2 else 32)
        data = (b''.join(payload[i:i + 2] for i in range(0, count, 4))
                if size == 3 else payload[:count])
        memory[destination:destination + span] = data
        owners[destination:destination + span] = [index] * span
        if size == 3:
            last_palette = None
        last_pixel = binding
    return memory, owners, loads, sizes, last_pixel, last_palette


def character_tmem_preview_texture(run, payloads):
    """Replay bounded RGBA16 transfers for an inherited CI8 render tile.

    DXT-zero LoadBlock overwrites its destination range, retaining other TMEM
    bytes. Every sampled index must have a ROM owner in this callable list.
    Unsupported transfers invalidate memory; they never supply guessed bytes.
    """
    unresolved = (None, 'character-indexed-tmem-span-unresolved')
    state = texture_coordinate_state(run)
    combine = decode_combine_mode(run.combine_mode)
    if (not state or state['format_evidence'] != 'character-same-index-tlut-load'
            or state['size'] != 1 or not run.texture_loads or not combine
            or {name for name in combine['inputs'] if name in ('TEXEL0', 'TEXEL1')} != {'TEXEL0'}
            or run.pixel is None or run.palette is None):
        return unresolved
    stride = ((run.render_tile[0] >> 9) & 511) * 8
    start = (run.render_tile[0] & 511) * 8
    width, height = state['width'], state['height']
    if stride < width or not stride or start + stride * height > 2048:
        return unresolved
    memory, owners, loads, _, last_pixel, last_palette = replay_lower_tmem(run, payloads)
    if (last_pixel != run.pixel or last_palette != run.palette
            or run.palette.flat_index != run.pixel.flat_index or run.palette.mode != 1
            or run.palette.image_command != 0xFD100000 or run.palette.external
            or run.palette.segment is not None):
        return unresolved
    payload = payloads.get(run.palette.flat_index, b'')
    if len(payload) < 512:
        return unresolved
    palette = payload[-512:]
    if not any(value & 1 for (value,) in struct.iter_unpack('>H', palette)):
        return unresolved
    addresses = [start + y * stride + (x ^ 4 if y & 1 else x)
                 for y in range(height) for x in range(width)]
    if any(owners[address] is None for address in addresses):
        return unresolved
    contributing = sorted({owners[address] for address in addresses})
    if len(contributing) < 2:
        return unresolved
    pixels = bytes(memory[address] for address in addresses)
    png = encode_ci8_png(pixels + palette, 'linear', width, height)
    return PreviewTexture(
        'us-character-tmem-composed', None, run.pixel.flat_index, 2, 1,
        width, height, hashlib.sha1(png).hexdigest(), png,
        palette_byte_offset=len(payload) - 512,
        tmem_source_loads=tuple(loads[index] for index in contributing),
    ), 'runtime-composed-character-tmem-texture'


def rgba8_tmem_preview_texture(run, payloads):
    """Fetch an RGBA8 tile without TLUT after a proven RGBA32 LoadBlock.

    RDP RGBA8 and I8 reads have the same four-channel byte expansion. The
    latest load contributes RG bytes, with earlier ROM loads supplying the
    untouched tail. Retain the authored tile and its own UV addressing.
    """
    unresolved = (None, 'no-proven-texture')
    state, other = texture_coordinate_state(run), decode_other_mode(run.other_mode)
    if (not run.texture_enabled or not run.texture_coordinates_proven
            or not state or (state['format'], state['size']) != (0, 1)
            or run.pixel is None or run.pixel.image_command != 0xFD180000
            or run.palette is not None or not run.texture_loads
            or run.other_mode_partial is not None or other is None
            or (other['texture_lut'], other['texture_lod'], other['texture_detail'], other['cycle_type'])
            != ('none', 'tile', 'clamp', 'two-cycle')
            or run.combine_mode != (0xFCFF9880, 0xF514FEFF)):
        return unresolved
    stride, start = ((run.render_tile[0] >> 9) & 511) * 8, (run.render_tile[0] & 511) * 8
    width, height = state['width'], state['height']
    if stride < width or not stride or start + stride * height > 2048:
        return unresolved
    memory, owners, loads, sizes, last_pixel, _ = replay_lower_tmem(run, payloads, rgba32=True)
    if last_pixel != run.pixel:
        return unresolved
    addresses = [start + y * stride + (x ^ 4 if y & 1 else x)
                 for y in range(height) for x in range(width)]
    if any(owners[address] is None for address in addresses):
        return unresolved
    contributing = sorted({owners[address] for address in addresses})
    if not contributing or sizes[contributing[-1]] != 32:
        return unresolved
    pixels = bytes(channel for address in addresses for channel in [memory[address]] * 4)
    # PNG rows have the same vertical flip as other ROM texture exports.
    pixels = b''.join(pixels[y * width * 4:(y + 1) * width * 4] for y in reversed(range(height)))
    png = encode_rgba_png(width, height, pixels)
    return PreviewTexture(
        'us-rgba8-tmem-composed', None, run.pixel.flat_index, 0, 1,
        width, height, hashlib.sha1(png).hexdigest(), png,
        tmem_source_loads=tuple(loads[i] for i in contributing),
        tmem_load_sizes=tuple(sizes[i] for i in contributing),
    ), 'runtime-composed-rgba8-tmem-texture'


def direct_runtime_indexed_preview_texture(
    run: ModelMaterialRun, payload: bytes
) -> tuple[PreviewTexture | None, str]:
    """Compose a direct CI4/CI8 tile from a packed LoadBlock image and TLUT.

    The command-derived image can occupy a prefix of a payload containing
    multiple mip levels. The shared loader selects the trailing 32-byte CI4
    or 512-byte CI8 palette independently of the reference bookkeeping table.
    This exports the selected base image, not native distance-dependent LOD.
    """

    state = texture_coordinate_state(run)
    if (
        state is None
        or state["format"] != 2
        or state["size"] not in (0, 1)
        or run.pixel is None
        or run.palette is None
        or run.render_tile is None
        or run.pixel.flat_index is None
        or run.pixel.flat_index != run.palette.flat_index
        or run.pixel.image_command != 0xFD500000
        or run.pixel.mode != 0
        or run.palette.image_command != 0xFD100000
        or run.palette.mode != (2 if state["size"] == 0 else 1)
    ):
        raise ValueError("material run is not a direct same-index indexed load")
    label = "direct-ci4" if state["size"] == 0 else "direct-ci8"
    if run.pixel.load_command is None or run.palette.load_command is None:
        return None, f"{label}-load-command-unresolved"

    pixel_load_command, pixel_load_argument = run.pixel.load_command
    palette_load_command, palette_load_argument = run.palette.load_command
    if pixel_load_command >> 24 != 0xF3 or palette_load_command >> 24 != 0xF0:
        return None, f"{label}-load-command-unresolved"
    palette_entries = 16 if state["size"] == 0 else 256
    if ((palette_load_argument >> 14) & 0x3FF) + 1 != palette_entries:
        return None, f"{label}-tlut-size-unresolved"

    if state["size"] == 0:
        if pixel_load_command & 0xFFFFFF or pixel_load_argument & 0xFFF:
            return None, f"{label}-load-row-conversion-unresolved"
        tiles = {index: (command, argument) for index, command, argument in run.render_tiles}
        pixel_tile = tiles.get((pixel_load_argument >> 24) & 7)
        palette_tile = tiles.get((palette_load_argument >> 24) & 7)
        if pixel_tile is None or pixel_tile[0] & 0x1FF:
            return None, f"{label}-load-tmem-origin-unresolved"
        # A 16-entry upload at TMEM word 0x100 populates palette bank zero.
        # Other palette destinations/banks require their own address mapping.
        if (palette_tile is None or palette_tile[0] & 0x1FF != 0x100
                or (run.render_tile[1] >> 20) & 0xF):
            return None, f"{label}-tlut-bank-unresolved"
        other = decode_other_mode(run.other_mode)
        if other is None or other["texture_lut"] != "rgba16":
            return None, f"{label}-lookup-mode-unresolved"

    transfer_size = (run.pixel.image_command >> 19) & 3
    transfer_bytes_per_texel = (1, 1, 2, 4)[transfer_size]
    transfer_size_bytes = (
        ((pixel_load_argument >> 12) & 0xFFF) + 1
    ) * transfer_bytes_per_texel
    render_tile_command, _ = run.render_tile
    if render_tile_command & 0x1FF:
        return None, f"{label}-tmem-offset-unresolved"
    row_size = (state["width"] + 1) // 2 if state["size"] == 0 else state["width"]
    line_words = (render_tile_command >> 9) & 0x1FF
    row_stride = line_words * 8 if line_words else row_size
    if row_stride < row_size:
        return None, f"{label}-row-stride-unresolved"
    if state["size"] == 0 and state["height"] > 1 and (not line_words or row_stride % 8):
        return None, f"{label}-row-stride-unresolved"
    pixel_storage_size = (state["height"] - 1) * row_stride + row_size
    if state["size"] == 0:
        if state["height"] % 2 == 0:
            # The odd-row swap reads a complete eight-byte-aligned row.
            pixel_storage_size = state["height"] * row_stride
        if pixel_storage_size > 2048:
            return None, f"{label}-tmem-span-unresolved"
    if pixel_storage_size > transfer_size_bytes:
        return None, f"{label}-tmem-span-unresolved"
    if pixel_storage_size > len(payload):
        return None, f"{label}-payload-span-unresolved"

    palette_byte_offset = len(payload) - palette_entries * 2
    if palette_byte_offset < pixel_storage_size:
        return None, f"{label}-pixel-palette-overlap-unresolved"

    rows = []
    for row_index in range(state["height"]):
        row_start = row_index * row_stride
        row = payload[row_start : row_start + row_stride]
        if row_index & 1:
            row = bytes(row[index ^ 4] for index in range(row_stride))
        rows.append(row[:row_size])
    linear_pixels = b"".join(rows)
    palette = payload[palette_byte_offset:]
    if state["size"] == 0 and state["width"] & 1:
        # An odd visible width still occupies a whole final CI4 byte per row.
        # Expand only visible texels through the exact RGBA5551 palette. This
        # avoids changing the reversible even-width CI4 PNG storage contract;
        # row padding and the unused low nibble remain in the source payload.
        colors = [palette[index:index + 2] for index in range(0, 32, 2)]
        rgba16 = b"".join(colors[(row[x // 2] >> (0 if x & 1 else 4)) & 15]
                          for row in rows for x in range(state["width"]))
        png_data = encode_rgba16_texture_png(
            rgba16, "linear", state["width"], state["height"])
    else:
        png_data = (encode_indexed_png if state["size"] == 0 else encode_ci8_png)(
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
        f"runtime-composed-{label}-texture",
    )


def is_character_trilinear_base(run: ModelMaterialRun) -> bool:
    """Recognize G_CC_TRILERP followed by the ordinary character colour stage.

    At LOD fraction zero the first cycle is exactly TEXEL0, for both RGB and
    alpha. The stored highest-resolution image is therefore a valid diffuse
    preview; this does not emulate distance-dependent N64 mip selection.
    """

    combine = decode_combine_mode(run.combine_mode)
    return bool(combine and combine["cycles"] == [
        {"color": ["TEXEL1", "TEXEL0", "LOD_FRACTION", "TEXEL0"],
         "alpha": ["TEXEL1", "TEXEL0", "LOD_FRACTION", "TEXEL0"]},
        {"color": ["SHADE", "ENVIRONMENT", "COMBINED", "PRIMITIVE"],
         "alpha": ["COMBINED", "ZERO", "ENVIRONMENT", "ZERO"]},
    ])


def is_direct_ia4_trilinear_base(run: ModelMaterialRun) -> bool:
    """Recognize explicit IA4 trilerp with shade or texture-only draw alpha."""
    if not run.texture_enabled or run.render_tile is None or run.texture_scale is None:
        return False
    state, other = texture_coordinate_state(run), decode_other_mode(run.other_mode)
    combine = decode_combine_mode(run.combine_mode)
    return bool(state and (state["format"], state["size"]) == (3, 0)
        and other and run.other_mode_partial is None
        and (other["texture_lut"], other["texture_lod"], other["texture_detail"], other["cycle_type"])
        == ("none", "lod", "clamp", "two-cycle")
        and combine and combine["cycles"][0] == {
            "color": ["TEXEL1", "TEXEL0", "LOD_FRACTION", "TEXEL0"],
            "alpha": ["TEXEL1", "TEXEL0", "LOD_FRACTION", "TEXEL0"]}
        and combine["cycles"][1]["color"] == ["COMBINED", "ENVIRONMENT", "SHADE", "PRIMITIVE"]
        and combine["cycles"][1]["alpha"] in (
            ["COMBINED", "ZERO", "SHADE", "ZERO"],
            ["ZERO", "ZERO", "ZERO", "COMBINED"]))


def is_direct_ia8_shade_mipmap_base(run: ModelMaterialRun) -> bool:
    if not run.texture_enabled or run.render_tile is None or run.texture_scale is None:
        return False
    state, other = texture_coordinate_state(run), decode_other_mode(run.other_mode)
    combine = decode_combine_mode(run.combine_mode)
    return bool(state and (state["format"], state["size"]) == (3, 1)
        and other and run.other_mode_partial is None
        and (other["texture_lut"], other["texture_lod"], other["texture_detail"], other["cycle_type"])
        == ("none", "lod", "clamp", "two-cycle")
        and combine and combine["cycles"] == [
            {"color": ["TEXEL1", "TEXEL0", "LOD_FRACTION", "TEXEL0"],
             "alpha": ["TEXEL1", "TEXEL0", "LOD_FRACTION", "TEXEL0"]},
            {"color": ["COMBINED", "ZERO", "SHADE", "ZERO"],
             "alpha": ["COMBINED", "ZERO", "SHADE", "ZERO"]},
        ])


def intensity_shade_mipmap_alpha(run: ModelMaterialRun) -> str | None:
    """Classify the two ordinary intensity trilerp alpha formulas at LOD zero.

    RGB is COMBINED * SHADE. One form uses texture alpha; the other bypasses
    it entirely. The environment factor belongs to the draw, not the image.
    """
    combine = decode_combine_mode(run.combine_mode)
    if not combine or combine['cycles'][0] != {
        'color': ['TEXEL1', 'TEXEL0', 'LOD_FRACTION', 'TEXEL0'],
        'alpha': ['TEXEL1', 'TEXEL0', 'LOD_FRACTION', 'TEXEL0'],
    } or combine['cycles'][1]['color'] != ['COMBINED', 'ZERO', 'SHADE', 'ZERO']:
        return None
    return {
        ('SHADE', 'ZERO', 'ENVIRONMENT', 'ZERO'): 'shade',
        ('COMBINED', 'ZERO', 'ENVIRONMENT', 'ZERO'): 'texture',
    }.get(tuple(combine['cycles'][1]['alpha']))


def is_character_rgb_trilinear_base(run: ModelMaterialRun) -> bool:
    """The RGB-only trilerp variant retains vertex alpha in both cycles."""
    combine = decode_combine_mode(run.combine_mode)
    return bool(combine and combine['cycles'] == [
        {'color': ['TEXEL1', 'TEXEL0', 'LOD_FRACTION', 'TEXEL0'],
         'alpha': ['TEXEL0', 'ZERO', 'SHADE', 'ZERO']},
        {'color': ['SHADE', 'ENVIRONMENT', 'COMBINED', 'PRIMITIVE'],
         'alpha': ['COMBINED', 'ZERO', 'ENVIRONMENT', 'ZERO']},
    ])


def character_rgb_mipmap_preview_texture(run, payload):
    """Validate the full indexed mip chain before selecting its RGB base."""
    state = texture_coordinate_state(run)
    other = decode_other_mode(run.other_mode)
    if (not is_character_rgb_trilinear_base(run) or state is None
            or state['format_evidence'] != 'character-same-index-tlut-load'):
        return None, 'character-rgb-mipmap-combiner-unresolved'
    if (other is None or run.other_mode_partial is not None
            or (other['texture_lut'], other['texture_lod'], other['texture_detail'], other['cycle_type'])
            != ('rgba16', 'lod', 'clamp', 'two-cycle')):
        return None, 'character-rgb-mipmap-other-mode-unresolved'
    pixel, palette = run.pixel, run.palette
    if (pixel is None or palette is None or pixel.mode != 0
            or pixel.image_command != 0xFD100000 or palette.image_command != 0xFD100000
            or pixel.flat_index is None or pixel.flat_index != palette.flat_index
            or pixel.load_command is None or palette.load_command is None
            or pixel.load_command[0] != 0xF3000000 or pixel.load_command[1] & 0xFFF
            or palette.load_command[0] != 0xF0000000 or run.texture_scale is None):
        return None, 'character-rgb-mipmap-load-unresolved'
    tiles = {i: (c, a) for i, c, a in run.render_tiles}
    load_tile = tiles.get((pixel.load_command[1] >> 24) & 7)
    tlut_tile = tiles.get((palette.load_command[1] >> 24) & 7)
    base = (run.texture_scale[0] >> 8) & 7
    count = (run.texture_scale[0] >> 11) & 7
    if (load_tile is None or load_tile[0] != 0xF5100000
            or tlut_tile is None or tlut_tile[0] & 0x1FF != 0x100
            or base != 0 or not count or base + count >= 6):
        return None, 'character-rgb-mipmap-tiles-unresolved'
    loaded = (((pixel.load_command[1] >> 12) & 0xFFF) + 1) * 2
    palette_size = 32 if state['size'] == 0 else 512
    if loaded > min(2048, len(payload) - palette_size):
        return None, 'character-rgb-mipmap-payload-span-unresolved'
    previous_end = 0
    for level in range(count + 1):
        tile = tiles.get(base + level)
        if tile is None:
            return None, 'character-rgb-mipmap-tiles-unresolved'
        c, a = tile
        width, height = max(1, state['width'] >> level), max(1, state['height'] >> level)
        stride, start = ((c >> 9) & 0x1FF) * 8, (c & 0x1FF) * 8
        row_bytes = (width * (4 << state['size']) + 7) // 8
        if ((c >> 21) & 7 != (run.render_tile[0] >> 21) & 7
                or (c >> 19) & 3 != state['size']
                or (1 << ((a >> 4) & 15), 1 << ((a >> 14) & 15)) != (width, height)
                or (a & 15, (a >> 10) & 15) != (level, level)
                or stride < row_bytes or start < previous_end
                or start + stride * height > min(loaded, 2048, len(payload) - palette_size)):
            return None, 'character-rgb-mipmap-layout-unresolved'
        previous_end = start + stride * height
    texture, status = character_runtime_preview_texture(run, payload)
    return texture, 'runtime-composed-character-rgb-trilinear-base' if texture else status


def zero_alpha_texture_is_invisible(run: ModelMaterialRun) -> bool:
    """Prove that an all-zero texture alpha cannot contribute visible colour.

    The second-cycle blender must be IN*A_IN + MEM*(1-A_IN), with no
    coverage-alpha replacement or depth write. Bit layouts are defined by
    GBL_c2 and the render-mode flags in libultra's PR/gbi.h.
    """
    combine, other = decode_combine_mode(run.combine_mode), decode_other_mode(run.other_mode)
    if (combine is None or other is None or run.other_mode_partial is not None
            or other['cycle_type'] != 'two-cycle'
            or [cycle['alpha'] for cycle in combine['cycles']] != [
                ['TEXEL0', 'ZERO', 'SHADE', 'ZERO'],
                ['COMBINED', 'ZERO', 'ENVIRONMENT', 'ZERO']]):
        return False
    low = run.other_mode[1]
    return (low & 0x33330000 == 0x00100000  # GBL_c2(IN, A_IN, MEM, 1MA)
            and low & 0x4040 == 0x4040      # FORCE_BL and IM_RD
            and low & 0x3023 == 0)          # No coverage replacement, Z_UPD or alpha compare.


RGBA32_TEXTURE_MIP_CYCLES = [
    {"color": ["TEXEL1", "TEXEL0", "LOD_FRACTION", "TEXEL0"],
     "alpha": ["TEXEL1", "TEXEL0", "LOD_FRACTION", "TEXEL0"]},
    {"color": ["ZERO", "ZERO", "ZERO", "COMBINED"],
     "alpha": ["COMBINED", "ZERO", "ENVIRONMENT", "ZERO"]},
]


def is_direct_rgba32_texture_mipmap_base(run: ModelMaterialRun) -> bool:
    if (not run.texture_enabled or run.render_tile is None or run.texture_scale is None
            or (run.render_tile[0] >> 19) & 31 != 3):
        return False
    state, other = texture_coordinate_state(run), decode_other_mode(run.other_mode)
    combine = decode_combine_mode(run.combine_mode)
    return bool(run.texture_enabled and state and (state["format"], state["size"]) == (0, 3)
        and other and run.other_mode_partial is None
        and (other["texture_lut"], other["texture_lod"], other["texture_detail"], other["cycle_type"])
        == ("none", "lod", "clamp", "two-cycle")
        and combine and combine["cycles"] == RGBA32_TEXTURE_MIP_CYCLES)


def direct_rgba32_mipmap_preview_texture(run: ModelMaterialRun, payload: bytes):
    label = "direct-rgba32-mipmap"
    if not is_direct_rgba32_texture_mipmap_base(run):
        return None, label + "-mode-unresolved"
    state, pixel = texture_coordinate_state(run), run.pixel
    if (pixel is None or pixel.image_command != 0xFD180000 or pixel.mode != 0
            or pixel.flat_index is None or pixel.load_command is None
            or pixel.load_command[0] != 0xF3000000 or pixel.load_command[1] & 0xFFF
            or run.texture_scale is None):
        return None, label + "-load-unresolved"
    tiles = {i: (c, a) for i, c, a in run.render_tiles}
    base, last = (run.texture_scale[0] >> 8) & 7, (run.texture_scale[0] >> 11) & 7
    load_tile = tiles.get((pixel.load_command[1] >> 24) & 7)
    loaded = (((pixel.load_command[1] >> 12) & 0xFFF) + 1) * 4
    if (load_tile is None or load_tile[0] != 0xF5180000 or base != 0
            or tiles.get(base) != run.render_tile or not 0 < last < 6
            or loaded > min(4096, len(payload))):
        return None, label + "-tiles-or-payload-unresolved"
    previous_end = 0
    for level in range(last + 1):
        tile = tiles.get(level)
        if tile is None:
            return None, label + "-layout-unresolved"
        command, argument = tile
        width, height = max(1, state["width"] >> level), max(1, state["height"] >> level)
        stride, start = ((command >> 9) & 511) * 8, (command & 511) * 8
        # RGBA32 has two bytes per texel in each TMEM bank. Source offsets
        # and row spans cover both banks; lower levels cannot overlap either.
        if ((command >> 19) & 31 != 3
                or (1 << ((argument >> 4) & 15), 1 << ((argument >> 14) & 15)) != (width, height)
                or (argument & 15, (argument >> 10) & 15) != (level, level)
                or stride < width * 2 or start < previous_end
                or (level == 0 and (start != 0 or stride != width * 2 or width % 4))
                or (start + stride * height) * 2 > loaded):
            return None, label + "-layout-unresolved"
        previous_end = start + stride * height
    width, height = state["width"], state["height"]
    png = encode_native_texture_png(payload[:width * height * 4], "rgba32",
                                    "tmem-odd-row-32bit-swap", width, height)
    return PreviewTexture(family="us-direct-rgba32-mipmap-base", source=None,
        flat_index=pixel.flat_index, format=0, size=3, width=width, height=height,
        sha1=hashlib.sha1(png).hexdigest(), png_data=png, pixel_byte_offset=0), label + "-base"


def direct_rgba32_preview_texture(
    run: ModelMaterialRun, payload: bytes
) -> tuple[PreviewTexture | None, str]:
    """Decode a ROM-backed RGBA32 base image from a proven LoadBlock prefix."""

    state = texture_coordinate_state(run)
    if (state is None or (state["format"], state["size"]) != (0, 3)
            or run.pixel is None or run.pixel.image_command != 0xFD180000
            or run.pixel.mode != 0 or run.pixel.flat_index is None):
        raise ValueError("material run is not a direct RGBA32 load")
    if known_other_mode_bits(run, 0, 3 << 14) != 0:
        return None, "direct-rgba32-lookup-mode-unresolved"
    if is_direct_rgba32_texture_mipmap_base(run):
        return direct_rgba32_mipmap_preview_texture(run, payload)
    combine = decode_combine_mode(run.combine_mode)
    inputs = set(combine["inputs"]) & {"TEXEL0", "TEXEL1"} if combine else set()
    if inputs != {"TEXEL0"} and not (
        is_character_trilinear_base(run)
        and any(index == 1 for index, _, _ in run.render_tiles)
    ):
        return None, "direct-rgba32-combiner-inputs-unresolved"
    load = run.pixel.load_command
    if load is None or load[0] != 0xF3000000 or load[1] & 0xFFF:
        return None, "direct-rgba32-load-row-conversion-unresolved"
    tiles = {index: command for index, command, _ in run.render_tiles}
    load_tile = tiles.get((load[1] >> 24) & 7)
    if load_tile is None or load_tile & 0x1FF:
        return None, "direct-rgba32-load-tmem-origin-unresolved"
    width, height = state["width"], state["height"]
    command, _ = run.render_tile
    if command & 0x1FF or width % 4 or ((command >> 9) & 0x1FF) * 8 != width * 2:
        return None, "direct-rgba32-row-stride-unresolved"
    size_bytes = width * height * 4
    loaded_bytes = (((load[1] >> 12) & 0xFFF) + 1) * 4
    if not size_bytes <= loaded_bytes <= 4096:
        return None, "direct-rgba32-tmem-span-unresolved"
    if loaded_bytes > len(payload):
        return None, "direct-rgba32-payload-span-unresolved"
    # RGBA32 pairs the two TMEM banks. Its line field counts two bytes per
    # texel; the ROM's zero-DXT layout swaps eight-byte halves on odd rows.
    # Following mip levels/padding are preserved in the source, not the PNG.
    png_data = encode_native_texture_png(payload[:size_bytes], "rgba32",
        "tmem-odd-row-32bit-swap", width, height)
    return PreviewTexture(family="us-direct-runtime-composed", source=None,
        flat_index=run.pixel.flat_index, format=0, size=3, width=width, height=height,
        sha1=hashlib.sha1(png_data).hexdigest(), png_data=png_data,
        pixel_byte_offset=0), "runtime-composed-direct-rgba32-texture"


def direct_rgba16_mipmap_preview_texture(
    run: ModelMaterialRun, payload: bytes
) -> tuple[PreviewTexture | None, str]:
    """Validate a direct RGBA16 mip chain and export its LOD-zero base."""
    label = "direct-rgba16-mipmap"
    state, other = texture_coordinate_state(run), decode_other_mode(run.other_mode)
    combine = decode_combine_mode(run.combine_mode)
    cycles = combine["cycles"] if combine else []
    if (state is None or (state["format"], state["size"]) != (0, 2)
            or len(cycles) != 2 or cycles[0] !=
                {"color": ["TEXEL1", "TEXEL0", "LOD_FRACTION", "TEXEL0"],
                 "alpha": ["TEXEL1", "TEXEL0", "LOD_FRACTION", "TEXEL0"]}
            or cycles[1] not in (
                {"color": ["COMBINED", "ENVIRONMENT", "SHADE", "PRIMITIVE"],
                 "alpha": ["COMBINED", "ZERO", "SHADE", "ZERO"]},
                {"color": ["COMBINED", "ZERO", "SHADE", "ZERO"],
                 "alpha": ["COMBINED", "ZERO", "SHADE", "ZERO"]})):
        return None, f"{label}-combiner-unresolved"
    if (other is None or run.other_mode_partial is not None
            or (other["texture_lut"], other["texture_lod"], other["texture_detail"], other["cycle_type"])
            != ("none", "lod", "clamp", "two-cycle")):
        return None, f"{label}-other-mode-unresolved"
    pixel = run.pixel
    if (pixel is None or pixel.image_command != 0xFD100000 or pixel.mode != 0
            or pixel.flat_index is None or pixel.load_command is None
            or pixel.load_command[0] != 0xF3000000 or pixel.load_command[1] & 0xFFF
            or run.texture_scale is None):
        return None, f"{label}-load-unresolved"
    tiles = {i: (c, a) for i, c, a in run.render_tiles}
    base, last = (run.texture_scale[0] >> 8) & 7, (run.texture_scale[0] >> 11) & 7
    load_tile = tiles.get((pixel.load_command[1] >> 24) & 7)
    if (load_tile is None or load_tile[0] != 0xF5100000 or base != 0
            or tiles.get(base) != run.render_tile or not 0 < last < 6):
        return None, f"{label}-tiles-unresolved"
    loaded = (((pixel.load_command[1] >> 12) & 0xFFF) + 1) * 2
    if loaded > min(4096, len(payload)):
        return None, f"{label}-payload-span-unresolved"
    previous_end = 0
    for level in range(last + 1):
        tile = tiles.get(level)
        if tile is None:
            return None, f"{label}-tiles-unresolved"
        command, argument = tile
        width, height = max(1, state["width"] >> level), max(1, state["height"] >> level)
        stride, start = ((command >> 9) & 0x1FF) * 8, (command & 0x1FF) * 8
        if ((command >> 19) & 31 != 2
                or (1 << ((argument >> 4) & 15), 1 << ((argument >> 14) & 15)) != (width, height)
                or (argument & 15, (argument >> 10) & 15) != (level, level)
                or stride < width * 2 or start < previous_end
                or (level == 0 and (start != 0 or stride != width * 2))
                or start + stride * height > loaded):
            return None, f"{label}-layout-unresolved"
        previous_end = start + stride * height
    width, height = state["width"], state["height"]
    png = encode_rgba16_texture_png(
        payload[:width * height * 2], "tmem-odd-row-32bit-swap", width, height)
    return PreviewTexture(family="us-direct-runtime-composed", source=None,
        flat_index=pixel.flat_index, format=0, size=2, width=width, height=height,
        sha1=hashlib.sha1(png).hexdigest(), png_data=png, pixel_byte_offset=0), \
        "runtime-composed-direct-rgba16-trilinear-base"


def direct_rgba16_preview_texture(
    run: ModelMaterialRun, payload: bytes
) -> tuple[PreviewTexture | None, str]:
    """Recover a complete RGBA5551 image using the draw's native flat index."""
    state = texture_coordinate_state(run)
    if (state is None or (state["format"], state["size"]) != (0, 2)
            or run.pixel is None or run.pixel.image_command != 0xFD100000
            or run.pixel.mode != 0 or run.pixel.flat_index is None):
        return None, "direct-rgba16-source-unresolved"
    if known_other_mode_bits(run, 0, 3 << 14) != 0:
        return None, "direct-rgba16-lookup-mode-unresolved"
    combine = decode_combine_mode(run.combine_mode)
    if combine and {"TEXEL0", "TEXEL1"}.issubset(combine["inputs"]):
        return direct_rgba16_mipmap_preview_texture(run, payload)
    if not combine or set(combine["inputs"]) & {"TEXEL0", "TEXEL1"} != {"TEXEL0"}:
        return None, "direct-rgba16-combiner-inputs-unresolved"
    load = run.pixel.load_command
    if load is None or load[0] != 0xF3000000 or load[1] & 0xFFF:
        return None, "direct-rgba16-load-row-conversion-unresolved"
    tiles = {index: command for index, command, _ in run.render_tiles}
    if tiles.get((load[1] >> 24) & 7) != 0xF5100000:
        return None, "direct-rgba16-load-tile-unresolved"
    width, height = state["width"], state["height"]
    command, _ = run.render_tile
    if command & 0x1FF or width % 4 or ((command >> 9) & 0x1FF) * 8 != width * 2:
        return None, "direct-rgba16-row-stride-unresolved"
    size_bytes = width * height * 2
    loaded_bytes = (((load[1] >> 12) & 0xFFF) + 1) * 2
    if not size_bytes == loaded_bytes == len(payload) or size_bytes > 4096:
        return None, "direct-rgba16-full-payload-unresolved"
    png_data = encode_rgba16_texture_png(payload, "tmem-odd-row-32bit-swap", width, height)
    return PreviewTexture(family="us-direct-runtime-composed", source=None,
        flat_index=run.pixel.flat_index, format=0, size=2, width=width, height=height,
        sha1=hashlib.sha1(png_data).hexdigest(), png_data=png_data,
        pixel_byte_offset=0), "runtime-composed-direct-rgba16-texture"


def direct_intensity_preview_texture(
    run: ModelMaterialRun, payload: bytes
) -> tuple[PreviewTexture | None, str]:
    """Decode a selected IA/I base image with explicit load and sampling state.

    Conker transfers these payloads as 16-bit texels with zero DXT. Narrow
    render tiles reinterpret the pre-swapped rows. Following mip/padding bytes
    stay in the source; this helper exports only the complete selected image.
    """

    state = texture_coordinate_state(run)
    formats = {(3, 0): "ia4", (3, 1): "ia8", (3, 2): "ia16", (4, 0): "i4", (4, 1): "i8"}
    name = formats.get((state["format"], state["size"])) if state else None
    if name is None:
        raise ValueError("material run is not a supported intensity render tile")
    label = f"direct-{name}"
    image_command = {3: 0xFD700000, 4: 0xFD900000}[state["format"]]
    if (run.pixel is None or run.pixel.mode != 0 or run.pixel.flat_index is None
            or run.pixel.image_command != image_command):
        return None, f"{label}-source-unresolved"
    other = decode_other_mode(run.other_mode)
    if other is None or other["texture_lut"] != "none":
        return None, f"{label}-lookup-mode-unresolved"
    if (is_character_trilinear_base(run) or is_direct_ia4_trilinear_base(run)
            or is_direct_ia8_shade_mipmap_base(run) or intensity_shade_mipmap_alpha(run)):
        # Explicit OtherMode draws need the same complete mip-chain checks
        # as segment-8 consensus draws. Export only the proven LOD-zero base.
        texture, status = character_intensity_mipmap_preview_texture(run, payload)
        if texture is not None:
            return texture, status
    combine = decode_combine_mode(run.combine_mode)
    inputs = set(combine["inputs"]) & {"TEXEL0", "TEXEL1"} if combine else set()
    if inputs != {"TEXEL0"}:
        return None, f"{label}-combiner-inputs-unresolved"
    if other["cycle_type"] not in ("one-cycle", "two-cycle"):
        return None, f"{label}-cycle-mode-unresolved"
    # IA stores separate alpha, while I repeats intensity into alpha. Binding
    # either to a transparent glTF material requires its actual alpha formula.
    texture_alpha_product = (
        other["cycle_type"] == "one-cycle"
        and all(cycle["alpha"] == ["TEXEL0", "ZERO", "SHADE", "ZERO"]
                for cycle in combine["cycles"])
    ) or (
        other["cycle_type"] == "two-cycle"
        and combine["cycles"][0]["alpha"] == ["TEXEL0", "ZERO", "SHADE", "ZERO"]
        and combine["cycles"][1]["alpha"] == ["COMBINED", "ZERO", "ENVIRONMENT", "ZERO"]
    )
    # The second form retains texture alpha through COMBINED, then scales it
    # by environment alpha. Export its IA/I alpha unchanged; the unknown
    # runtime environment factor remains outside the static preview.
    shade_alpha = (name in ("i4", "i8") and run.other_mode_partial is None
                   and other["gltf_alpha_mode"] != "OPAQUE"
                   and other["cycle_type"] == "one-cycle"
                   and other["texture_lod"] == "tile"
                   and all(cycle["alpha"] == ["ZERO", "ZERO", "ZERO", "SHADE"]
                           for cycle in combine["cycles"]))
    shade_alpha = shade_alpha or (name == 'i8' and run.other_mode_partial is None
        and other['cycle_type'] == 'two-cycle' and other['texture_lod'] == 'tile'
        and combine['cycles'] == [
            {'color': ['TEXEL0', 'ZERO', 'SHADE', 'ZERO'],
             'alpha': ['ZERO', 'ZERO', 'ZERO', 'SHADE']},
            {'color': ['ZERO', 'ZERO', 'ZERO', 'COMBINED'],
             'alpha': ['COMBINED', 'ZERO', 'ENVIRONMENT', 'ZERO']},
        ])
    if other["gltf_alpha_mode"] != "OPAQUE" and not (texture_alpha_product or shade_alpha):
        return None, f"{label}-alpha-expression-unresolved"
    load = run.pixel.load_command
    if load is None or load[0] != 0xF3000000 or load[1] & 0xFFF:
        return None, f"{label}-load-row-conversion-unresolved"
    tiles = {index: command for index, command, _ in run.render_tiles}
    load_tile = tiles.get((load[1] >> 24) & 7)
    if load_tile is None or load_tile & 0x1FF:
        return None, f"{label}-load-tmem-origin-unresolved"
    # Character lists also use the ordinary RGBA16 transfer tile for IA/I
    # bytes. Both are 16-bit LoadBlock transfers; the selected render tile
    # supplies the final format. Zero DXT and TMEM origin are required above.
    # Admit that path only for a supported alpha expression. An explicit
    # one-cycle shade-only draw receives an opaque RGB intensity texture;
    # inherited character modes remain covered by their separate decoder.
    load_format = (load_tile >> 19) & 31
    if load_format != (image_command >> 19) & 31 and not (
        load_format == 2 and (texture_alpha_product or shade_alpha)
    ):
        return None, f"{label}-load-format-unresolved"
    width, height = state["width"], state["height"]
    if name in ("i4", "ia4") and width % 2:
        return None, f"{label}-row-stride-unresolved"
    row_bytes = packed_row_size(name, width)
    command, _ = run.render_tile
    row_stride = ((command >> 9) & 0x1FF) * 8
    if command & 0x1FF or row_stride < row_bytes:
        return None, f"{label}-row-stride-unresolved"
    # SetTileSize can expose fewer texels than a complete TMEM row. The
    # line field still advances by whole eight-byte words. Swap each stored
    # row before cropping its visible columns, including on the final row.
    size_bytes = row_stride * height
    loaded_bytes = (((load[1] >> 12) & 0xFFF) + 1) * 2
    if not size_bytes <= loaded_bytes <= 4096:
        return None, f"{label}-tmem-span-unresolved"
    if loaded_bytes > len(payload):
        return None, f"{label}-payload-span-unresolved"
    rows = []
    for y in range(height):
        row = payload[y * row_stride:(y + 1) * row_stride]
        rows.append(bytes(row[x ^ (4 if y & 1 else 0)] for x in range(row_bytes)))
    if shade_alpha:
        # The draw takes alpha solely from SHADE, so intensity is colour only.
        # Preserve the independent vertex alpha without multiplying it by I.
        intensities = ([(v >> shift & 15) * 17 for row in reversed(rows) for v in row
                        for shift in (4, 0)] if name == "i4"
                       else [v for row in reversed(rows) for v in row])
        png_data = encode_rgba_png(width, height,
            b"".join(bytes((v, v, v, 255)) for v in intensities))
        label += "-shade-alpha"
    else:
        png_data = encode_native_texture_png(b"".join(rows), name, "linear", width, height)
    return PreviewTexture(
        family="us-direct-runtime-composed", source=None,
        flat_index=run.pixel.flat_index, format=state["format"], size=state["size"],
        width=width, height=height, sha1=hashlib.sha1(png_data).hexdigest(),
        png_data=png_data, pixel_byte_offset=0,
    ), f"runtime-composed-{label}-texture"


def choose_preview_texture(
    run: ModelMaterialRun,
    catalog: dict[tuple[int, int, int], tuple[PreviewTexture, ...]],
    flat_payloads: dict[int, bytes] | None = None,
) -> tuple[PreviewTexture | None, str]:
    if run.texture_enabled is None:
        return None, "runtime-texture-enable-state-unresolved"
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
    if ((state['format'], state['size']) == (0, 1)
            and run.pixel.image_command == 0xFD180000):
        return rgba8_tmem_preview_texture(run, flat_payloads or {})
    if ((state["format"], state["size"]) == (3, 0)
            and run.pixel.image_command == 0xFD500000
            and run.other_mode is not None
            and decode_other_mode(run.other_mode)["texture_detail"] == "detail"):
        payload = (flat_payloads or {}).get(run.pixel.flat_index)
        if payload is None:
            return None, "direct-detail-indexed-flat-payload-missing"
        return direct_detail_indexed_preview_texture(run, payload)
    if state["format_evidence"] == "character-same-index-tlut-load":
        combine = decode_combine_mode(run.combine_mode)
        if combine is not None:
            texture_inputs = {
                name for name in combine["inputs"] if name in ("TEXEL0", "TEXEL1")
            }
            if texture_inputs == {"TEXEL0", "TEXEL1"}:
                if not any(tile_index == 1 for tile_index, _, _ in run.render_tiles):
                    return None, "character-indexed-mipmap-state-unresolved"
                if not (is_character_trilinear_base(run) or is_character_rgb_trilinear_base(run)):
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
        if is_character_rgb_trilinear_base(run):
            return character_rgb_mipmap_preview_texture(run, payload)
        texture, status = character_runtime_preview_texture(run, payload)
        if texture is None and status == 'character-indexed-tmem-span-unresolved':
            texture, status = character_tmem_preview_texture(run, flat_payloads)
        if texture is not None and is_character_trilinear_base(run):
            status = "runtime-composed-character-trilinear-base"
        return texture, status
    if state["format"] == 2:
        if (
            run.palette is None
            or run.palette.flat_index != run.pixel.flat_index
        ):
            return None, "unresolved-ci-palette"
        if state["size"] == 1:
            if run.palette.mode != 1:
                return None, "unresolved-ci-palette"
            if flat_payloads is None:
                return None, "direct-ci8-flat-payload-missing"
            payload = flat_payloads.get(run.pixel.flat_index)
            if payload is None:
                return None, "direct-ci8-flat-payload-missing"
            return direct_runtime_indexed_preview_texture(run, payload)
    if (state["format"] == 2 and state["size"] == 0 and run.palette is not None
            and run.palette.mode == 2 and run.pixel.image_command == 0xFD500000
            and flat_payloads is not None):
        payload = flat_payloads.get(run.pixel.flat_index)
        if payload is None:
            return None, "direct-ci4-flat-payload-missing"
        # A reversible standalone PNG does not resolve a particular draw's
        # unknown lookup state or incompatible image geometry.
        return direct_runtime_indexed_preview_texture(run, payload)
    if ((state["format"], state["size"]) == (0, 3)
            and run.pixel.image_command == 0xFD180000 and flat_payloads is not None):
        payload = flat_payloads.get(run.pixel.flat_index)
        if payload is None:
            return None, "direct-rgba32-flat-payload-missing"
        return direct_rgba32_preview_texture(run, payload)
    if ((state["format"], state["size"]) in ((3, 1), (3, 2), (4, 0), (4, 1))
            or ((state["format"], state["size"]) == (3, 0)
                and run.pixel.image_command == 0xFD700000)):
        payload = flat_payloads.get(run.pixel.flat_index) if flat_payloads is not None else None
        if payload is None:
            return None, "direct-intensity-flat-payload-missing"
        return direct_intensity_preview_texture(run, payload)
    candidates = catalog.get(
        (run.pixel.flat_index, state["format"], state["size"]), ()
    )
    if not candidates:
        if (state["format"], state["size"]) == (0, 2) and flat_payloads is not None:
            payload = flat_payloads.get(run.pixel.flat_index)
            if payload is not None:
                return direct_rgba16_preview_texture(run, payload)
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


def detail_texture_preview_record(run: ModelMaterialRun) -> dict:
    tile, bounds, dimensions = run.preview_coordinate_state
    return {
        "source": "ROM-display-list-and-flat-payload",
        "scope": "detail-mode non-magnified first mip at LOD fraction zero",
        "declared_base_tile": (run.texture_scale[0] >> 8) & 7,
        "preview_tile": ((run.texture_scale[0] >> 8) & 7) + 1,
        "preview_render_tile": list(tile), "preview_tile_bounds": list(bounds),
        "preview_dimensions": list(dimensions),
        "source_tile_bounds": [list(row) for row in run.detail_tile_bounds],
        "native_distance_blending": "unverified",
    }


def direct_detail_indexed_preview_texture(run: ModelMaterialRun, payload: bytes):
    """Export the first ordinary mip of a fully bounded ROM detail texture.

    In RDP detail mode, non-magnified LOD zero selects base+1/base+2.
    At zero LOD fraction the proven lerp selects base+1, including that tile's
    own UV shift and origin. Keep the declared detail tile as source state.
    """
    def reject(reason):
        return None, "direct-detail-indexed-" + reason + "-unresolved"
    other, combine = decode_other_mode(run.other_mode), decode_combine_mode(run.combine_mode)
    expected = [
        {"color": ["TEXEL1", "TEXEL0", "LOD_FRACTION", "TEXEL0"],
         "alpha": ["TEXEL1", "TEXEL0", "LOD_FRACTION", "TEXEL0"]},
        {"color": ["COMBINED", "ENVIRONMENT", "SHADE", "PRIMITIVE"],
         "alpha": ["COMBINED", "ZERO", "SHADE", "ZERO"]},
    ]
    if (not run.texture_enabled or not run.texture_coordinates_proven
            or run.texture_scale is None or run.other_mode_partial is not None
            or other is None or combine is None or combine["cycles"][0] != expected[0]
            or combine["cycles"][1] not in (expected[1], {
                "color": ["COMBINED", "ZERO", "SHADE", "ZERO"],
                "alpha": ["COMBINED", "ZERO", "SHADE", "ZERO"],
            })
            or (other["texture_lut"], other["texture_lod"], other["texture_detail"], other["cycle_type"])
            != ("rgba16", "lod", "detail", "two-cycle")):
        return reject("mode")
    pixel, palette = run.pixel, run.palette
    if (pixel is None or palette is None or pixel.flat_index is None
            or pixel.flat_index != palette.flat_index or pixel.mode != 0
            or pixel.image_command != 0xFD500000 or palette.image_command != 0xFD100000
            or palette.mode not in (1, 2) or pixel.load_command is None
            or palette.load_command is None):
        return reject("binding")
    pc, pa = pixel.load_command
    tc, ta = palette.load_command
    entries = 256 if palette.mode == 1 else 16
    tiles = {i: (c, a) for i, c, a in run.render_tiles}
    bounds = {i: (c, a) for i, c, a in run.detail_tile_bounds}
    load, tlut = tiles.get((pa >> 24) & 7), tiles.get((ta >> 24) & 7)
    if (pc != 0xF3000000 or pa & 0xFFF or tc != 0xF0000000
            or ((ta >> 14) & 0x3FF) + 1 != entries or load is None
            or load[0] != 0xF5500000 or tlut is None or tlut[0] != 0xF5600100):
        return reject("load")
    declared = (run.texture_scale[0] >> 8) & 7
    maximum = (run.texture_scale[0] >> 11) & 7
    first = declared + 1
    loaded = (((pa >> 12) & 0xFFF) + 1) * 2
    palette_start = len(payload) - entries * 2
    if (not maximum or first + maximum >= 6 or palette_start < 0
            or loaded > min(len(payload), 4096) or tiles.get(declared) != run.render_tile
            or declared not in bounds or bounds.get(declared) != run.tile_bounds):
        return reject("span")
    detail, base = tiles.get(declared), tiles.get(first)
    if detail is None or base is None or first not in bounds:
        return reject("tiles")
    base_run = replace(run, render_tile=base, tile_bounds=bounds[first], texture_dimensions=None)
    try:
        state = texture_coordinate_state(base_run)
    except ValueError:
        return reject("coordinates")
    size = state["size"]
    if state["format"] != 2 or size != 2 - palette.mode or (size == 0 and state["width"] & 1):
        return reject("format")
    previous_end = 0
    for level in range(maximum + 1):
        tile, bound = tiles.get(first + level), bounds.get(first + level)
        if tile is None or bound is None:
            return reject("tiles")
        c, a = tile
        w, h = max(1, state["width"] >> level), max(1, state["height"] >> level)
        stride, start = ((c >> 9) & 0x1FF) * 8, (c & 0x1FF) * 8
        if (((c >> 21) & 7, (c >> 19) & 3) != (2, size)
                or (1 << ((a >> 4) & 15), 1 << ((a >> 14) & 15)) != (w, h)
                or (a & 15, (a >> 10) & 15) != (level, level)
                or a & ((3 << 8) | (3 << 18) | (15 << 20))
                or stride < (w * (4 << size) + 7) // 8 or start < previous_end
                or start + stride * h > min(loaded, palette_start, 2048)):
            return reject("mip-layout")
        try:
            level_state = texture_coordinate_state(replace(base_run, render_tile=tile, tile_bounds=bound))
        except ValueError:
            return reject("coordinates")
        # Some authored chains add a half-texel (two quarter units) at
        # every level. Scale the integer origin while retaining that bias.
        origins = (state["uls"], state["ult"])
        biases = tuple(origin & 3 for origin in origins)
        if ((level_state["width"], level_state["height"]) != (w, h)
                or any(bias not in (0, 2) for bias in biases)
                or (level_state["uls"], level_state["ult"]) != tuple(
                    ((origin - bias) >> level) + bias for origin, bias in zip(origins, biases))):
            return reject("coordinates")
        previous_end = start + stride * h
    c, a = detail
    detail_state = texture_coordinate_state(run)
    dw, dh = detail_state["width"], detail_state["height"]
    stride, start = ((c >> 9) & 0x1FF) * 8, (c & 0x1FF) * 8
    if (((c >> 21) & 7, (c >> 19) & 3) != (3, 0)
            or dw & 1 or (a & 15, (a >> 10) & 15) != (15, 15)
            or (1 << ((a >> 4) & 15), 1 << ((a >> 14) & 15)) != (dw, dh)
            or a & ((3 << 8) | (3 << 18) | (15 << 20)) or stride < dw // 2
            or start < previous_end or start + stride * dh > min(loaded, palette_start, 2048)):
        return reject("detail-layout")
    width, height = state["width"], state["height"]
    row_bytes = (width * (4 << size) + 7) // 8
    stride, start = ((base[0] >> 9) & 0x1FF) * 8, (base[0] & 0x1FF) * 8
    rows = [bytes(payload[start + y * stride + (x ^ (4 if y & 1 else 0))]
                  for x in range(row_bytes)) for y in range(height)]
    encoder = encode_ci8_png if size else encode_indexed_png
    png = encoder(b"".join(rows) + payload[palette_start:], "linear", width, height)
    coordinates = (base, bounds[first], (width, height))
    return PreviewTexture("us-direct-detail-indexed-base", None, pixel.flat_index, 2, size,
                          width, height, hashlib.sha1(png).hexdigest(), png, start,
                          palette_start, coordinates), "direct-detail-indexed-base"


def preview_texture_filename(texture: PreviewTexture) -> str:
    return (
        f"{texture.family}-{texture.flat_index:04d}-"
        f"{texture.width}x{texture.height}-{texture.sha1[:12]}.png"
    )


def verify_gltf_material_spans(gltf: dict[str, Any], runs: list[dict[str, Any]]) -> None:
    """Require ordered, complete source-run coverage after culling partitions."""

    boundaries = []
    total = 0
    for run in runs:
        boundaries.append((total, total + run["face_count"]))
        total += run["face_count"]
    cursor = 0
    used_materials = set()
    for mesh in gltf.get("meshes", []):
        for primitive in mesh["primitives"]:
            material_index = primitive["material"]
            used_materials.add(material_index)
            material = gltf["materials"][material_index]
            extras = material["extras"]
            run_index = extras.get("materialRun")
            first, count = extras.get("firstFace"), extras.get("faceCount")
            if (not isinstance(run_index, int) or not 0 <= run_index < len(runs)
                    or first != cursor or not isinstance(count, int) or count <= 0
                    or not boundaries[run_index][0] <= first < first + count <= boundaries[run_index][1]
                    or gltf["accessors"][primitive["indices"]]["count"] != count * 3):
                raise ValueError("preview glTF material spans do not partition source runs")
            if ("runtimeMaterial" in extras) != (runs[run_index]["runtime_material"] is not None):
                raise ValueError("preview glTF runtime material span changed")
            culling = extras.get("faceCulling", {})
            if culling and material["doubleSided"] != (culling["mode"] != "back"):
                raise ValueError("preview glTF material culling flag disagrees with source state")
            cursor += count
    if cursor != total or used_materials != set(range(len(gltf.get("materials", [])))):
        raise ValueError("preview glTF material spans leave missing or unused source data")


def verify_gltf_vertex_colors(gltf: dict[str, Any], runs: list[dict[str, Any]]) -> None:
    """Retain source colours; allow only the proven RGBA32 texture-only draw."""

    for mesh in gltf.get("meshes", []):
        for primitive in mesh["primitives"]:
            attributes = primitive["attributes"]
            if "COLOR_0" in attributes:
                continue
            material = gltf["materials"][primitive["material"]]
            extras = material.get("extras", {})
            run = runs[extras["materialRun"]]
            texture = run.get("texture") or {}
            combine = decode_combine_mode(tuple(int(x, 16) for x in run["combine_mode"])) if run.get("combine_mode") else None
            other = decode_other_mode(tuple(int(x, 16) for x in run["other_mode"])) if run.get("other_mode") else None
            source = attributes.get("_SOURCE_COLOR_0")
            if (run.get("status") != "direct-rgba32-mipmap-base"
                    or run.get("runtime_material") is not None
                    or run.get("other_mode_partial") is not None
                    or not combine or combine["cycles"] != RGBA32_TEXTURE_MIP_CYCLES
                    or not other or tuple(other[k] for k in ("texture_lut", "texture_lod", "texture_detail", "cycle_type"))
                    != ("none", "lod", "clamp", "two-cycle")
                    or extras.get("combineMode") != run["combine_mode"]
                    or extras.get("otherMode") != run["other_mode"]
                    or texture.get("source_family") != "us-direct-rgba32-mipmap-base"
                    or (texture.get("format"), texture.get("size")) != (0, 3)
                    or not isinstance(source, int) or not 0 <= source < len(gltf["accessors"])
                    or "TEXCOORD_0" not in attributes):
                raise ValueError("preview glTF omits required vertex colors")
            accessor = gltf["accessors"][source]
            if (accessor.get("type"), accessor.get("componentType"), accessor.get("normalized"), accessor.get("count")) != (
                    "VEC4", 5121, True, gltf["accessors"][attributes["POSITION"]]["count"]):
                raise ValueError("preview glTF source colors are invalid")
            binding = material.get("pbrMetallicRoughness", {}).get("baseColorTexture")
            if not binding or gltf["images"][gltf["textures"][binding["index"]]["source"]].get("uri") != "../" + texture["file"]:
                raise ValueError("preview glTF texture-only color binding changed")


def verify_preview_output(output: Path, manifest: dict[str, Any]) -> None:
    instructions_path = output / manifest["instructions_file"]
    if not instructions_path.is_file():
        raise ValueError("preview instructions are missing")
    texture_files = {
        texture["file"]: texture["png_sha1"] for texture in manifest["textures"]
    }
    runtime_mip_files = set()
    runtime_multitexture_files = set()
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
        if (gltf.get("buffers", [{}])[0].get("byteLength", 0)
                != binary_path.stat().st_size):
            raise ValueError(f"preview glTF buffer size mismatch: {gltf_path.name}")
        primitives = [
            primitive
            for mesh in gltf.get("meshes", [])
            for primitive in mesh["primitives"]
        ]
        verify_gltf_material_spans(gltf, model["material_runs"])
        for material in gltf.get("materials", []):
            runtime_material = material.get("extras", {}).get("runtimeMaterial", {})
            for variant in runtime_material.get("variants", []):
                captured = variant.get("captured_texture")
                if not isinstance(captured, dict):
                    continue
                texture1_image = captured.get("texture1_image")
                for level in runtime_captured_auxiliary_textures(captured):
                    preview_file = level.get("preview_file")
                    if not isinstance(preview_file, str):
                        raise ValueError("preview glTF omits a captured mip path")
                    mapped = (gltf_path.parent / preview_file).resolve()
                    if (
                        not mapped.is_relative_to(output.resolve())
                        or not mapped.is_file()
                        or hashlib.sha1(mapped.read_bytes()).hexdigest()
                        != level["png_sha1"]
                    ):
                        raise ValueError("preview glTF captured mip failed verification")
                    if level is texture1_image:
                        runtime_multitexture_files.add(mapped.name)
                    else:
                        runtime_mip_files.add(mapped.name)
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
        verify_gltf_vertex_colors(gltf, model["material_runs"])
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
        for accessor in gltf.get("accessors", []):
            if not 0 <= accessor["bufferView"] < len(gltf["bufferViews"]):
                raise ValueError(f"preview glTF has an invalid accessor: {gltf_path.name}")
        for view in gltf.get("bufferViews", []):
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
        == "captured-cbfd-vertex-load-colours"
        for model in manifest["models"]
        for run in model["material_runs"]
    ):
        raise ValueError("preview runtime lighting replay count changed")
    if manifest.get("copied_runtime_mip_texture_count") != len(runtime_mip_files):
        raise ValueError("preview runtime mip texture count changed")
    if manifest.get("copied_runtime_multitexture_count") != len(
        runtime_multitexture_files
    ):
        raise ValueError("preview runtime secondary texture count changed")
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

    entries = parse_asset_entries(normalized, bank)
    payloads = {}
    for entry in entries:
        raw = normalized[entry.start:entry.end]
        payloads[entry.index] = decode_rzip_chunk(raw).data if entry.compressed else raw
    if layout.get("game_format") != "rzip":
        raise ValueError("US runtime render-state evidence requires the RZIP game archive")
    game = parse_game_archive(normalized[layout["game_start"]:layout["game_end"]])
    effect_sources = {}
    if bank_index == 0x09:
        verify_direct_model_consumers(game.code, int(layout['game_vram']))
        types = verify_effect_consumers(game.code, int(layout['game_vram']),
                                        game.data, int(layout['game_data_vram']))
        effect_sources = resolve_effect_sources(payloads, types)
    bundles = []
    for entry in entries:
        data = payloads[entry.index]
        effect_source = effect_sources.get(entry.index)
        if bank_index == 9 and is_effect_model(data) and effect_source is None:
            raise ValueError(f"bank-09 entry {entry.index} lacks a verified effect consumer")
        if bank_index == 0x04:
            segments = parse_model_bundle(data)
        else:
            # Bank 09 has attachment, effect, and direct models. Remaining
            # point-record assets are not silently promoted to meshes.
            try:
                if effect_source is not None:
                    parse_effect_model(data, parse_model_geometry, effect_source)
                else:
                    parse_geometry_for_bank(data, bank_index)
            except ValueError as error:
                if bank_index == 0x09 and not (is_attachment_model(data) or is_effect_model(data)):
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
                    effect_source=effect_source,
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
    render_state_tables = parse_runtime_render_state_tables(
        game.data, int(layout["game_data_vram"])
    )
    return rom_path, source_order, digest, bundles, render_state_tables


def load_character_morph_manifest(profile: str, rom_argument: Path | None,
                                  bundles: list[ModelBundle] | None = None) -> dict:
    rom_path, layout = resolve_rom(profile, rom_argument)
    rom, _ = normalize_rom(rom_path.read_bytes())
    if profile != "us" or hashlib.sha1(rom).hexdigest() not in layout["normalized_sha1"]:
        raise ValueError("character morphs require the checksum-validated US ROM")
    if bundles is None:
        _, _, _, bundles, _ = load_model_bundles(profile, rom_argument, 1)
    models = {bundle.index: (bundle.data, parse_character_model_geometry(bundle.data)[0])
              for bundle in bundles if bundle.index in (0, 58)}
    return model_morphs.load_manifest(rom, layout, models)


def load_emission_point_manifest(profile: str, rom_argument: Path | None) -> dict:
    rom_path, layout = resolve_rom(profile, rom_argument)
    rom, _ = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    if profile != 'us' or digest not in layout['normalized_sha1']:
        raise ValueError('emission points require the checksum-validated US ROM')
    game = parse_game_archive(rom[layout['game_start']:layout['game_end']])
    bank = next(bank for bank in parse_asset_banks(rom, layout['asset_table']) if bank.index == 9)
    if bank.flags:
        raise ValueError('emission-point bank has unsupported flags')
    payloads = {}
    for entry in parse_asset_entries(rom, bank):
        if entry.index in model_emission_points.ENTRIES:
            raw = rom[entry.start:entry.end]
            payloads[entry.index] = decode_rzip_chunk(raw).data if entry.compressed else raw
    return model_emission_points.make_manifest(payloads, game.code, layout['game_vram'],
                                               game.data, layout['game_data_vram'], digest)


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
                geometry = parse_segment_geometry(segment, bank_index)
                geometry_record = {
                    "vertex_count": len(geometry.vertices),
                    "face_count": len(geometry.faces),
                    "texture_coordinate_count": texture_coordinate_count(geometry),
                    "display_list_offset": f"0x{geometry.display_list_offset:X}",
                    "display_list_size": geometry.display_list_size,
                    "vertex_load_count": geometry.vertex_load_count,
                    "vertex_load_matrix_corner_count": sum(
                        matrix is not None
                        for face in geometry.face_matrix_indices for matrix in face
                    ),
                    "faces_differing_from_draw_matrix": vertex_matrix_mismatch_face_count(geometry),
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
                elif bank_index == 0x09 and is_attachment_model(segment.data):
                    _, attachment_layout = parse_attachment_model(segment.data, parse_model_geometry)
                    for section in attachment_layout["sections"]:
                        if section["file"] is not None:
                            section["file"] = section["file"].format(entry=bundle.index) if include_files else None
                    geometry_record["attachment_layout"] = attachment_layout
                elif segment.effect_source is not None:
                    _, effect_layout = parse_effect_model(segment.data, parse_model_geometry, segment.effect_source)
                    for section in effect_layout["sections"]:
                        if section["file"] is not None:
                            section["file"] = section["file"].format(entry=bundle.index) if include_files else None
                    geometry_record["effect_layout"] = effect_layout
                elif bank_index == 0x09:
                    geometry_record['vertex_addressing'] = {
                        'unsegmented': 'model-relative-including-0x28-header',
                        'segment_01': 'vertex-array-relative',
                        'loader': 'func_1518C900', 'relocator': 'func_15168E34',
                        'relocation_dispatch': 'func_15168E54',
                    }
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
                        **({"other_mode_partial": list(run.other_mode_partial)} if run.other_mode_partial is not None else {}),
                        "runtime_render_state_offset": (
                            f"0x{run.runtime_render_state_offset:X}"
                            if run.runtime_render_state_offset is not None
                            else None
                        ),
                        "matrix_index": run.matrix_index,
                        "vertex_load_matrix_indices": sorted({
                            matrix
                            for face_index in range(run.first_face, run.first_face + run.face_count)
                            for matrix in face_vertex_matrix_indices(geometry, run, face_index)
                        }),
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
            0x09: "indexed-bank-09-attachment-and-direct-model-geometry",
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
                else "attachment-and-direct-geometry-proven-available-uv-and-normal-"
                "state-preserved-parent-transform-animation-and-inherited-material-state-runtime-dependent"
            )
        ),
        "attachment_model_count": sum(
            "attachment_layout" in segment.get("geometry", {})
            for record in records for segment in record["segments"]
        ),
        "effect_model_count": sum(
            "effect_layout" in segment.get("geometry", {})
            for record in records for segment in record["segments"]
        ),
        "jointed_attachment_model_count": sum(
            bool(segment.get("geometry", {}).get("attachment_layout", {}).get("joints"))
            for record in records for segment in record["segments"]
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
                    "runtime_matrix_state": CHARACTER_RUNTIME_MATRIX_STATE,
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
                    "selected_subset": "three-pair-attachment-four-pair-effect-and-direct-models",
                    "attachment_renderer": "func_150311C4",
                    "attachment_pose_builder": "func_150A81D0",
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
            if run["texture_enabled"] is None or (
                run["pixel"] is not None
                and run["pixel"]["source"] == "external-runtime-state"
            )
        ),
        "untextured_face_count": sum(
            run["face_count"]
            for record in records
            for segment in record["segments"]
            for run in segment.get("geometry", {}).get("material_runs", [])
            if run["texture_enabled"] is False
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
                geometry = parse_segment_geometry(segment, bank_index)
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
                elif bank_index == 0x09 and is_attachment_model(segment.data):
                    _, attachment_layout = parse_attachment_model(segment.data, parse_model_geometry)
                    for section in attachment_layout["sections"]:
                        if not section["size"]:
                            continue
                        region_path = output / section["file"].format(entry=bundle.index)
                        region_path.parent.mkdir(parents=True, exist_ok=True)
                        offset = section["offset"]
                        region_path.write_bytes(segment.data[offset:offset + section["size"]])
                if segment.effect_source is not None:
                    _, effect_layout = parse_effect_model(segment.data, parse_model_geometry, segment.effect_source)
                    for section in effect_layout["sections"]:
                        if section["size"]:
                            region_path = output / section["file"].format(entry=bundle.index)
                            region_path.parent.mkdir(parents=True, exist_ok=True)
                            offset = section["offset"]
                            region_path.write_bytes(segment.data[offset:offset + section["size"]])
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
        morphs = load_character_morph_manifest(profile, rom_argument, bundles)
        (output / "character-morphs.json").write_text(json.dumps(morphs, indent=2) + "\n")
        manifest["character_morphs"] = {key: value for key, value in morphs.items() if key != "models"}
        manifest["character_morphs"]["file"] = "character-morphs.json"
        expressions = load_character_expression_manifest(profile, rom_argument, digest)
        (output / 'character-expressions.json').write_text(json.dumps(expressions, indent=2) + '\n')
        manifest['character_expressions'] = {key: value for key, value in expressions.items() if key != 'models'}
        manifest['character_expressions']['file'] = 'character-expressions.json'
    elif bank_index == 0x09:
        points = load_emission_point_manifest(profile, rom_argument)
        (output / "emission-points.json").write_text(json.dumps(points, indent=2) + "\n")
        manifest["emission_points"] = {key: value for key, value in points.items() if key != "records"}
        manifest["emission_points"]["file"] = "emission-points.json"
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
                geometry = parse_segment_geometry(segment, bank_index)
                model_sha1 = hashlib.sha1(segment.data).hexdigest()
                for run_index, run in enumerate(geometry.material_runs):
                    inventory[(bank_index, bundle.index, segment.index, run_index)] = {
                        "model_sha1": model_sha1,
                        "first_face": run.first_face,
                        "face_count": run.face_count,
                        "matrix_index": run.matrix_index,
                        "_run": run,
                        "_geometry": geometry,
                    }
    if digest is None:
        raise ValueError("runtime material inventory is empty")
    return digest, inventory


def runtime_captured_preview_texture(
    run: ModelMaterialRun | None,
    material_state: dict[str, Any] | None,
    payloads: dict[int, bytes],
) -> dict[str, Any] | None:
    """Compose a PNG using the task's actual tile format and palette mode."""

    if run is None or not isinstance(material_state, dict) or run.render_tile is None:
        return None
    texture = material_state.get("texture")
    if not isinstance(texture, dict) or texture.get("enabled") is False:
        return None
    pixel_image = texture.get("pixel_image")
    palette_image = texture.get("palette_image")
    if not isinstance(pixel_image, dict):
        return None
    pixel_index = pixel_image.get("captured_texture_image_index")
    palette_index = (
        palette_image.get("captured_texture_image_index")
        if isinstance(palette_image, dict) else None
    )
    if not isinstance(pixel_index, int):
        return None
    pixel_data = payloads.get(pixel_index)
    palette_data = payloads.get(palette_index)
    if pixel_data is None:
        return None
    try:
        state = texture_coordinate_state(run)
    except ValueError:
        return None
    if state is None or state["size"] not in (0, 1, 2, 3):
        return None
    render_tile_command, render_tile_argument = run.render_tile
    other = decode_other_mode(material_state.get("other_mode"))
    if other is None:
        # A retained palette load alone does not prove that lookup is enabled.
        return None
    runtime_tiles = {
        int(tile["index"]): tile
        for tile in material_state.get("tiles", []) or []
        if isinstance(tile, dict) and isinstance(tile.get("index"), int)
    }
    texture_scale = texture.get("scale")
    base_tile = (
        (texture_scale[0] >> 8) & 7
        if isinstance(texture_scale, list) and len(texture_scale) == 2 else 0
    )
    runtime_base = runtime_tiles.get(base_tile)
    if runtime_base is not None:
        runtime_command, runtime_argument = runtime_base["command"], runtime_base["argument"]
        # Exported UVs still use the stored geometry's coordinate contract.
        # Different sizes or addressing require a separate runtime UV replay.
        coordinate_mask = 0xFFFFF
        if (
            ((runtime_command >> 19) & 3) != state["size"]
            or (runtime_argument & coordinate_mask) != (render_tile_argument & coordinate_mask)
            or (isinstance(texture_scale, list) and texture_scale[1] != run.texture_scale[1])
        ):
            return None
        render_tile_command, render_tile_argument = runtime_command, runtime_argument
    bounds = material_state.get("tile_bounds", {}).get(str(base_tile))
    coordinate_run = replace(
        run,
        render_tile=(render_tile_command, render_tile_argument),
        tile_bounds=tuple(bounds) if bounds is not None else run.tile_bounds,
    )
    if bounds is not None and run.pixel is not None and run.pixel.load_command is not None:
        mask_s = (render_tile_argument >> 4) & 0xF
        mask_t = (render_tile_argument >> 14) & 0xF
        clamps = render_tile_argument & ((2 << 8) | (2 << 18))
        mask_row_bytes = ((1 << mask_s) * (4 << state["size"]) + 7) // 8
        mask_row_stride = ((render_tile_command >> 9) & 0x1FF) * 8 or mask_row_bytes
        mask_end = ((render_tile_command & 0x1FF) * 8
                    + ((1 << mask_t) - 1) * mask_row_stride + mask_row_bytes)
        # For an unclamped LoadBlock tile, masks define the repeating image;
        # SetTileSize's origin can scroll fractionally or wrap through 0xFFF.
        # Admit only a complete mask image fitting the lower 2 KiB of TMEM.
        if (
            state["size"] in (0, 1, 2)
            and run.pixel.load_command[0] >> 24 == 0xF3 and not clamps
            and mask_s and mask_t
            and (1 << (mask_s + mask_t)) * (4 << state["size"]) <= 2048 * 8
            and mask_end <= 2048
        ):
            coordinate_run = replace(coordinate_run, texture_dimensions=(1 << mask_s, 1 << mask_t))
    try:
        state = texture_coordinate_state(coordinate_run)
    except ValueError:
        return None
    width, height = state["width"], state["height"]
    if state["size"] == 0 and width & 1:
        # The reversible CI4 PNG contract does not yet preserve row-end nibbles.
        return None

    def effective_format(tile_command: int) -> str | None:
        size = (tile_command >> 19) & 3
        format_id = (tile_command >> 21) & 7
        if size == 3 and format_id == 0 and other["texture_lut"] == "none":
            return "rgba32"
        if size == 2 and format_id == 3 and other["texture_lut"] == "none":
            return "ia16"
        if size not in (0, 1):
            return None
        if other["texture_lut"] == "rgba16" and format_id in (0, 2, 3, 4):
            return "ci4" if size == 0 else "ci8"
        if other["texture_lut"] != "none":
            return None
        # GLideN64's G_TT_NONE table reads RGBA4/8 as intensity, and IA8
        # directly. Do not feed those bytes through an unrelated retained TLUT.
        if format_id in (0, 4) or (format_id == 2 and size == 1):
            return "i4" if size == 0 else "i8"
        if format_id == 3 and size == 1:
            return "ia8"
        if format_id == 3 and size == 0:
            return "ia4"
        return None

    format_name = effective_format(render_tile_command)
    if format_name is None or (format_name.startswith("ci") and palette_data is None):
        return None
    static_tiles = {
        tile_index: (command, argument)
        for tile_index, command, argument in run.render_tiles
    }
    load_tmem = 0
    if run.pixel is not None and run.pixel.load_command is not None:
        load_tile_index = (run.pixel.load_command[1] >> 24) & 0x7
        load_tile = static_tiles.get(load_tile_index)
        if load_tile is not None:
            load_tmem = load_tile[0] & 0x1FF

    def encode_level(
        level: int,
        tile_command: int,
        tile_argument: int,
        level_width: int,
        level_height: int,
        source_byte_offset: int,
        level_size: int,
    ) -> dict[str, Any] | None:
        if level_size == 3:
            # Match texture_native's complete RGBA32 LoadBlock contract. A
            # zero DXT stream is already arranged for paired TMEM banks: line
            # stride counts two bytes per texel; odd rows swap 8-byte halves.
            # Partial loads and nonzero TMEM origins need separate replay.
            load = run.pixel.load_command if run.pixel is not None else None
            size_bytes = level_width * level_height * 4
            if (level != 0 or source_byte_offset or load_tmem or tile_command & 0x1FF
                    or effective_format(tile_command) != "rgba32"
                    or pixel_image.get("command") != 0xFD180000
                    or load is None or load[0] >> 24 != 0xF3 or load[1] & 0xFFF
                    or (((load[1] >> 12) & 0xFFF) + 1) * 4 != size_bytes
                    or len(pixel_data) != size_bytes or size_bytes > 4096
                    or ((tile_command >> 9) & 0x1FF) * 8 != level_width * 2
                    or level_width % 4):
                return None
            png_data = encode_native_texture_png(
                pixel_data, "rgba32", "tmem-odd-row-32bit-swap", level_width, level_height
            )
            digest = hashlib.sha1(png_data).hexdigest()
            return {"level": level, "format": "rgba32", "width": level_width,
                    "height": level_height, "tmem_byte_offset": 0, "source_byte_offset": 0,
                    "png_sha1": digest,
                    "file": f"textures/runtime-rgba32-{level_width}x{level_height}-{digest[:12]}.png",
                    "png_data": png_data}
        if level_size == 0 and level_width & 1:
            return None
        if level_size == 2 or effective_format(tile_command) == "ia4":
            load = run.pixel.load_command if run.pixel is not None else None
            if (effective_format(tile_command) not in ("ia4", "ia16") or level != 0
                    or source_byte_offset or load_tmem or tile_command & 0x1FF
                    or pixel_image.get("command") != 0xFD700000
                    or load is None or load[0] != 0xF3000000 or load[1] & 0xFFF
                    or len(pixel_data) > 4096
                    or (((load[1] >> 12) & 0xFFF) + 1) * 2 != len(pixel_data)):
                return None
        row_size = ((level_width + 1) // 2 if level_size == 0
                    else level_width * 2 if level_size == 2 else level_width)
        row_stride = ((tile_command >> 9) & 0x1FF) * 8 or row_size
        if row_stride < row_size or source_byte_offset < 0:
            return None
        if level_height > 1 and row_stride % 8:
            return None
        pixel_size = (
            source_byte_offset + (level_height - 1) * row_stride + row_size
        )
        if pixel_size > len(pixel_data):
            return None
        rows = []
        for row_index in range(level_height):
            row_start = source_byte_offset + row_index * row_stride
            row = pixel_data[row_start : row_start + row_stride]
            if row_index & 1:
                if len(row) != row_stride:
                    return None
                row = bytes(row[index ^ 4] for index in range(row_stride))
            rows.append(row[:row_size])
        pixels = b"".join(rows)
        level_format_name = effective_format(tile_command)
        if level_format_name is None:
            return None
        if level_format_name in ("i4", "i8", "ia4", "ia8", "ia16"):
            png_data = encode_native_texture_png(
                pixels, level_format_name, "linear", level_width, level_height
            )
        elif level_size == 0:
            palette_bank = (tile_argument >> 20) & 0xF
            palette_start = palette_bank * 0x20
            palette = palette_data[palette_start : palette_start + 0x20]
            if len(palette) != 0x20:
                return None
            png_data = encode_indexed_png(
                pixels + palette, "linear", level_width, level_height
            )
        else:
            palette = palette_data[:0x200]
            if len(palette) != 0x200:
                return None
            png_data = encode_ci8_png(
                pixels + palette, "linear", level_width, level_height
            )
        digest = hashlib.sha1(png_data).hexdigest()
        return {
            "level": level,
            "format": level_format_name,
            "width": level_width,
            "height": level_height,
            "tmem_byte_offset": (tile_command & 0x1FF) * 8,
            "source_byte_offset": source_byte_offset,
            "png_sha1": digest,
            "file": (
                f"textures/runtime-{level_format_name}-{level_width}x{level_height}-"
                f"{digest[:12]}.png"
            ),
            "png_data": png_data,
        }

    base_source_offset = ((render_tile_command & 0x1FF) - load_tmem) * 8
    base = encode_level(
        0,
        render_tile_command,
        render_tile_argument,
        width,
        height,
        base_source_offset,
        state["size"],
    )
    if base is None:
        return None
    result = {
        "status": (
            "runtime-captured-indexed-texture" if format_name.startswith("ci")
            else "runtime-captured-native-texture"
        ),
        "format": format_name,
        "width": width,
        "height": height,
        "pixel_sha256": pixel_image.get("sha256"),
        "palette_sha256": (
            palette_image.get("sha256") if format_name.startswith("ci") else None
        ),
        "texture_lut": other["texture_lut"],
        "png_sha1": base["png_sha1"],
        "file": base["file"],
        "png_data": base["png_data"],
        "tmem_byte_offset": base["tmem_byte_offset"],
        "source_byte_offset": base["source_byte_offset"],
        "coordinate_state": {
            "render_tile": list(coordinate_run.render_tile),
            "tile_bounds": list(coordinate_run.tile_bounds) if coordinate_run.tile_bounds else None,
            "texture_scale": list(coordinate_run.texture_scale),
            "texture_dimensions": list(coordinate_run.texture_dimensions) if coordinate_run.texture_dimensions else None,
            "bounds_evidence": "captured-command-replay" if bounds is not None else "source-display-list",
        },
        "mip_levels": [],
        "texture1_mip_levels": [],
        "texture1_image": None,
    }
    if (
        isinstance(texture_scale, list)
        and len(texture_scale) == 2
        and all(isinstance(value, int) for value in texture_scale)
    ):
        max_level = (texture_scale[0] >> 11) & 0x7
        base_tile = (texture_scale[0] >> 8) & 0x7
        combine_pair = material_state.get("combine_mode")
        combine = (
            decode_combine_mode(tuple(combine_pair))
            if isinstance(combine_pair, list) and len(combine_pair) == 2
            else None
        )
        runtime_base = runtime_tiles.get(base_tile)
        if runtime_base is not None:
            for level in range(1, max_level + 1):
                tile = runtime_tiles.get(base_tile + level)
                if tile is None:
                    break
                command = int(tile["command"])
                if ((command >> 19) & 0x3) != state["size"]:
                    break
                mip = encode_level(
                    level,
                    command,
                    int(tile["argument"]),
                    max(1, width >> level),
                    max(1, height >> level),
                    ((command & 0x1FF) - load_tmem) * 8,
                    state["size"],
                )
                if mip is None:
                    break
                result["mip_levels"].append(mip)
            if (
                not result["mip_levels"]
                and max_level
                and other is not None
                and other["texture_detail"] == "detail"
            ):
                detail_base_tile = runtime_tiles.get(base_tile + 1)
                if detail_base_tile is not None:
                    detail_command = int(detail_base_tile["command"])
                    detail_size = (detail_command >> 19) & 0x3
                    detail_argument = int(detail_base_tile["argument"])
                    mask_s = (detail_argument >> 4) & 0xF
                    mask_t = (detail_argument >> 14) & 0xF
                    if detail_size in (0, 1) and mask_s and mask_t:
                        detail_width, detail_height = 1 << mask_s, 1 << mask_t
                        for level in range(max_level + 1):
                            tile = runtime_tiles.get(base_tile + 1 + level)
                            if tile is None:
                                break
                            command = int(tile["command"])
                            if ((command >> 19) & 0x3) != detail_size:
                                break
                            mip = encode_level(
                                level,
                                command,
                                int(tile["argument"]),
                                max(1, detail_width >> level),
                                max(1, detail_height >> level),
                                ((command & 0x1FF) - load_tmem) * 8,
                                detail_size,
                            )
                            if mip is None:
                                break
                            result["texture1_mip_levels"].append(mip)
            if (
                max_level == 0
                and combine is not None
                and "TEXEL1" in combine["inputs"]
                and other is not None
                and other["texture_lod"] == "tile"
            ):
                texture1_tile = runtime_tiles.get(base_tile + 1)
                if texture1_tile is not None:
                    command = int(texture1_tile["command"])
                    texture1_size = (command >> 19) & 0x3
                    argument = int(texture1_tile["argument"])
                    mask_s = (argument >> 4) & 0xF
                    mask_t = (argument >> 14) & 0xF
                    if texture1_size in (0, 1) and mask_s and mask_t:
                        texture1 = encode_level(
                            0,
                            command,
                            argument,
                            1 << mask_s,
                            1 << mask_t,
                            ((command & 0x1FF) - load_tmem) * 8,
                            texture1_size,
                        )
                        if texture1 is not None:
                            texture1["role"] = "TEXEL1"
                            result["texture1_image"] = texture1
    result["mip_level_count"] = 1 + len(result["mip_levels"])
    result["texture1_mip_level_count"] = len(result["texture1_mip_levels"])
    return result


def runtime_captured_mip_levels(captured: dict[str, Any]) -> list[dict[str, Any]]:
    return [
        *captured.get("mip_levels", []),
        *captured.get("texture1_mip_levels", []),
    ]


def runtime_captured_auxiliary_textures(
    captured: dict[str, Any]
) -> list[dict[str, Any]]:
    texture1 = captured.get("texture1_image")
    return [
        *runtime_captured_mip_levels(captured),
        *([texture1] if isinstance(texture1, dict) else []),
    ]


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
            captured_texture = variant.get("captured_texture")
            if captured_texture is not None:
                primary_levels = [
                    captured_texture,
                    *captured_texture.get("mip_levels", []),
                ]
                texture1_levels = captured_texture.get("texture1_mip_levels", [])
                texture1_image = captured_texture.get("texture1_image")
                if captured_texture.get("mip_level_count") != len(primary_levels):
                    raise ValueError("runtime captured mip level count changed")
                if captured_texture.get("texture1_mip_level_count") != len(
                    texture1_levels
                ):
                    raise ValueError("runtime captured TEXEL1 mip count changed")
                for level_index, level in enumerate(primary_levels):
                    if level_index and level.get("level") != level_index:
                        raise ValueError("runtime captured mip level order changed")
                for level_index, level in enumerate(texture1_levels):
                    if level.get("level") != level_index:
                        raise ValueError("runtime captured TEXEL1 mip order changed")
                for level in [
                    *primary_levels,
                    *texture1_levels,
                    *([texture1_image] if isinstance(texture1_image, dict) else []),
                ]:
                    relative = Path(level["file"])
                    texture_path = (output / relative).resolve()
                    if (
                        relative.is_absolute()
                        or ".." in relative.parts
                        or not texture_path.is_relative_to(output.resolve())
                        or not texture_path.is_file()
                    ):
                        raise ValueError("runtime captured texture path is invalid")
                    if hashlib.sha1(texture_path.read_bytes()).hexdigest() != level[
                        "png_sha1"
                    ]:
                        raise ValueError("runtime captured texture PNG hash changed")
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
            for evidence in variant.get("evidence", []):
                sample = evidence.get("vertex_lighting")
                if isinstance(sample, dict):
                    first, count = evidence.get("source_first_face"), evidence.get("source_face_count")
                    if (not isinstance(first, int) or not isinstance(count, int)
                            or not record["source_first_face"] <= first < first + count <= record["source_first_face"] + record["source_face_count"]):
                        raise ValueError("runtime vertex lighting sample exceeds source material")
                    validate_vertex_lighting_sample(sample, first, count)
    if manifest.get("lighting_context_count") != sum(
        variant.get("lighting_context_count", 0)
        for record in materials
        for variant in record["variants"]
    ):
        raise ValueError("runtime lighting context total changed")
    convert_modes = [
        tuple(variant["state"]["convert_mode"])
        for record in materials
        for variant in record["variants"]
        if variant["state"].get("convert_mode") is not None
    ]
    if (
        manifest.get("convert_mode_variant_count") != len(convert_modes)
        or manifest.get("missing_convert_mode_variant_count")
        != manifest["variant_count"] - len(convert_modes)
        or manifest.get("convert_mode_count") != len(set(convert_modes))
    ):
        raise ValueError("runtime material convert-mode inventory changed")
    mip_levels = [
        level
        for record in materials
        for variant in record["variants"]
        for level in runtime_captured_mip_levels(
            variant.get("captured_texture") or {}
        )
    ]
    if (
        manifest.get("captured_mip_variant_count")
        != sum(
            bool(runtime_captured_mip_levels(variant.get("captured_texture") or {}))
            for record in materials
            for variant in record["variants"]
        )
        or manifest.get("captured_mip_level_count") != len(mip_levels)
        or manifest.get("captured_mip_png_count")
        != len({level["file"] for level in mip_levels})
    ):
        raise ValueError("runtime captured mip inventory changed")
    multitextures = [
        captured["texture1_image"]
        for record in materials
        for variant in record["variants"]
        if isinstance((captured := variant.get("captured_texture")), dict)
        and isinstance(captured.get("texture1_image"), dict)
    ]
    if (
        manifest.get("captured_multitexture_variant_count")
        != len(multitextures)
        or manifest.get("captured_multitexture_png_count")
        != len({texture["file"] for texture in multitextures})
    ):
        raise ValueError("runtime captured secondary texture inventory changed")
    appearances = manifest.get("appearances", [])
    if manifest.get("appearance_count") != len(appearances):
        raise ValueError("runtime material appearance count changed")
    appearance_ids = [appearance["id"] for appearance in appearances]
    if len(appearance_ids) != len(set(appearance_ids)):
        raise ValueError("runtime material appearance identities are not unique")
    if manifest["material_assignment_observation_count"] != sum(
        appearance["material_assignment_observation_count"]
        for appearance in appearances
    ):
        raise ValueError("runtime material appearance observation count changed")
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
    segment_8_resolutions = [
        resolution
        for record in materials
        for variant in record["variants"]
        for evidence in variant.get("evidence", [])
        if isinstance(
            (resolution := evidence.get("runtime_segment_8_resolution")), dict
        )
    ]
    segment_8_status_counts: dict[str, int] = {}
    for resolution in segment_8_resolutions:
        status = resolution.get("status")
        if not isinstance(status, str):
            raise ValueError("runtime segment-8 resolution status changed")
        segment_8_status_counts[status] = segment_8_status_counts.get(status, 0) + 1
    if (
        manifest.get("runtime_segment_8_material_assignment_observation_count")
        != len(segment_8_resolutions)
        or manifest.get("runtime_segment_8_resolution_status_counts")
        != dict(sorted(segment_8_status_counts.items()))
    ):
        raise ValueError("runtime material segment-8 resolution inventory changed")
    payload_hashes = sorted(
        {
            resolution["payload_sha256"]
            for resolution in segment_8_resolutions
            if isinstance(resolution.get("payload_sha256"), str)
        }
    )
    effective_payload_hashes = sorted(
        {
            resolution["payload_sha256"]
            for resolution in segment_8_resolutions
            if resolution.get("status")
            == "exact-runtime-list-effective-state"
            and isinstance(resolution.get("payload_sha256"), str)
        }
    )
    if (
        manifest.get("runtime_segment_8_payload_count") != len(payload_hashes)
        or manifest.get("runtime_segment_8_payload_sha256") != payload_hashes
        or manifest.get("runtime_segment_8_effective_payload_count")
        != len(effective_payload_hashes)
        or manifest.get("runtime_segment_8_effective_payload_sha256")
        != effective_payload_hashes
    ):
        raise ValueError("runtime material segment-8 payload inventory changed")
    written = json.loads((output / "manifest.json").read_text(encoding="utf-8"))
    if written != manifest:
        raise ValueError("runtime material manifest did not round-trip through JSON")


def backfill_runtime_convert_modes(event: dict[str, Any]) -> None:
    """Replay retained command evidence to upgrade traces made before EC capture."""

    draw_runs = event.get("state", {}).get("rdp", {}).get("draw_runs", [])
    if not draw_runs or all(
        "convert_mode" in run.get("state", {}) for run in draw_runs
    ):
        return
    root_data = None
    nested_data: dict[int, bytes] = {}
    for item in event.get("evidence", {}).get("memory", []):
        name = item.get("name", "")
        encoded = item.get("data_base64")
        if not isinstance(encoded, str):
            continue
        if name == "command-buffer":
            root_data = base64.b64decode(encoded)
        elif name.startswith("nested-display-list-"):
            resolved = item.get("resolved_address")
            if isinstance(resolved, str):
                nested_data[int(resolved, 16)] = base64.b64decode(encoded)
    # Synthetic tests and older minimal traces may not retain the raw task.
    if root_data is None:
        return
    flattened, unresolved = flatten_display_lists(root_data, nested_data)
    if unresolved:
        raise ValueError("runtime trace convert-state replay has unresolved display lists")
    replayed = decode_f3dex2_cbfd(flattened)["rdp"]["draw_runs"]
    if len(replayed) != len(draw_runs):
        raise ValueError("runtime trace convert-state replay draw count changed")
    for original, refreshed in zip(draw_runs, replayed):
        identity = ("command_offset", "opcode", "triangle_count")
        if any(original.get(key) != refreshed.get(key) for key in identity):
            raise ValueError("runtime trace convert-state replay draw identity changed")
        original.setdefault("state", {})["convert_mode"] = refreshed["state"].get(
            "convert_mode"
        )


def load_character_activity_trace(
    path: Path,
    expected_digest: str,
    valid_entries: set[int],
) -> dict[str, Any]:
    """Validate one character-pool snapshot trace and return stable evidence."""

    data = path.read_bytes()
    lines = [json.loads(line) for line in data.splitlines() if line.strip()]
    if not lines or lines[0].get("record_type") != "session":
        raise ValueError(f"character activity trace has no session record: {path}")
    if lines[0].get("spec_name") != "character-model-activity":
        raise ValueError(f"character activity trace uses the wrong spec: {path}")
    if any(line.get("schema") != "conker.model-draw-state-trace/v1" for line in lines):
        raise ValueError(f"character activity trace schema changed: {path}")
    trace_digest = lines[0].get("normalized_sha1")
    if trace_digest is not None and trace_digest != expected_digest:
        raise ValueError(f"character activity trace belongs to a different ROM: {path}")
    events = [line for line in lines if line.get("record_type") == "draw_state"]
    if not events:
        raise ValueError(f"character activity trace has no snapshot event: {path}")
    snapshots = []
    for event_index, event in enumerate(events):
        pool = event.get("state", {}).get("model", {})
        records = pool.get("active_records")
        if (
            pool.get("character_pool_address") != CHARACTER_POOL_ADDRESS
            or pool.get("record_size") != CHARACTER_POOL_RECORD_SIZE
            or pool.get("record_count") != CHARACTER_POOL_RECORD_COUNT
            or not isinstance(records, list)
            or pool.get("active_record_count") != len(records)
        ):
            raise ValueError(f"character activity pool contract changed: {path}")
        seen_slots = set()
        entries = []
        for record in records:
            slot = int(record["slot"])
            entry = int(record["entry"])
            offset = slot * CHARACTER_POOL_RECORD_SIZE
            if (
                not 0 <= slot < CHARACTER_POOL_RECORD_COUNT
                or slot in seen_slots
                or int(record["record_offset"]) != offset
                or int(record["record_address"]) != CHARACTER_POOL_ADDRESS + offset
                or int(record["owner_address"]) == 0
            ):
                raise ValueError(f"character activity record identity changed: {path}")
            if entry not in valid_entries:
                raise ValueError(
                    f"character activity references absent bank-01 entry {entry}: {path}"
                )
            seen_slots.add(slot)
            entries.append(entry)
        if sorted(set(entries)) != pool.get("active_entries"):
            raise ValueError(f"character activity entry summary changed: {path}")
        snapshots.append(
            {
                "event_index": event_index,
                "hit_index": event.get("hit_index"),
                "render_state_hash": event.get("render_state_hash"),
                "active_record_count": len(records),
                "active_entries": sorted(set(entries)),
                "active_records": records,
            }
        )
    return {
        "file": display_path(path),
        "sha256": hashlib.sha256(data).hexdigest(),
        "normalized_sha1": trace_digest,
        "tool_revisions": lines[0].get("tool_revisions"),
        "snapshot_count": len(snapshots),
        "snapshots": snapshots,
    }


def load_character_part_table_trace(
    path: Path,
    expected_digest: str,
) -> dict[str, Any]:
    """Validate one graphics-boundary snapshot of the renderer part headers."""

    data = path.read_bytes()
    lines = [json.loads(line) for line in data.splitlines() if line.strip()]
    if not lines or lines[0].get("record_type") != "session":
        raise ValueError(f"character part-table trace has no session record: {path}")
    if lines[0].get("spec_name") != "character-model-part-tables":
        raise ValueError(f"character part-table trace uses the wrong spec: {path}")
    if any(line.get("schema") != "conker.model-draw-state-trace/v1" for line in lines):
        raise ValueError(f"character part-table trace schema changed: {path}")
    trace_digest = lines[0].get("normalized_sha1")
    if trace_digest is not None and trace_digest != expected_digest:
        raise ValueError(f"character part-table trace belongs to a different ROM: {path}")
    events = [line for line in lines if line.get("record_type") == "draw_state"]
    if len(events) != 1 or events[0].get("breakpoint") != (
        "character-part-tables-at-graphics-submit"
    ):
        raise ValueError(f"character part-table trace event changed: {path}")
    event = events[0]
    probes = {
        probe["name"]: probe
        for probe in event.get("evidence", {}).get("memory", [])
    }
    table_inputs = []
    for name, address, length in (
        ("character-part-pointer-table", 0x800C4488, CHARACTER_PART_POINTER_TABLE_SIZE),
        ("character-part-count-table", 0x800C4778, CHARACTER_PART_COUNT_TABLE_SIZE),
        (
            "character-extra-part-pointer-table",
            0x800C48F0,
            CHARACTER_PART_POINTER_TABLE_SIZE,
        ),
    ):
        probe = probes.get(name)
        if (
            probe is None
            or int(probe["resolved_address"], 0) != address
            or int(probe["length"]) != length
        ):
            raise ValueError(f"character part-table probe changed: {path}")
        payload = base64.b64decode(probe["data_base64"], validate=True)
        if len(payload) != length or hashlib.sha256(payload).hexdigest() != probe["sha256"]:
            raise ValueError(f"character part-table payload changed: {path}")
        table_inputs.append(payload)
    decoded_tables = decode_cbfd_character_part_table_headers(*table_inputs)
    if decoded_tables != event.get("state", {}).get("model", {}).get("part_tables"):
        raise ValueError(f"character part-table decode changed: {path}")
    return {
        "file": display_path(path),
        "sha256": hashlib.sha256(data).hexdigest(),
        "normalized_sha1": trace_digest,
        "tool_revisions": lines[0].get("tool_revisions"),
        "table_record_count": len(decoded_tables),
        "part_tables": decoded_tables,
    }


def character_display_list_topology(
    bundles: list[ModelBundle],
) -> dict[tuple[int, str, int], dict[str, Any]]:
    """Map renderer part-table slots to exact ROM display-list clusters."""

    topology: dict[tuple[int, str, int], dict[str, Any]] = {}
    table_names = {"primary": "normal", "secondary": "extra"}
    for bundle in bundles:
        if len(bundle.segments) != 1 or bundle.segments[0].index != 0:
            raise ValueError("bank-01 character bundle topology changed")
        segment = bundle.segments[0]
        geometry, layout = parse_character_model_geometry(segment.data)
        display = segment.data[
            geometry.display_list_offset :
            geometry.display_list_offset + geometry.display_list_size
        ]
        clusters = geometry_clusters(display)
        assigned_clusters: set[int] = set()
        for table in layout["display_list_pointer_tables"]:
            renderer_table = table_names[table["name"]]
            for part_index, encoded_pointer in enumerate(table["pointers"]):
                pointer = int(encoded_pointer, 0)
                relative_start = pointer - geometry.display_list_offset
                relative_end = None
                for offset in range(relative_start, len(display), 8):
                    command, argument = struct.unpack_from(">II", display, offset)
                    if command == 0xDF000000 and argument == 0:
                        relative_end = offset + 8
                        break
                if relative_end is None:
                    raise ValueError(
                        f"bank-01 entry {bundle.index} part list has no EndDL"
                    )
                cluster_indices = {
                    index
                    for index, cluster in enumerate(clusters)
                    if relative_start <= int(cluster["command_offset"]) < relative_end
                }
                overlap = assigned_clusters.intersection(cluster_indices)
                if overlap:
                    raise ValueError(
                        f"bank-01 entry {bundle.index} part lists overlap clusters"
                    )
                assigned_clusters.update(cluster_indices)
                topology[(bundle.index, renderer_table, part_index)] = {
                    "static_pointer_offset": pointer,
                    "static_cluster_indices": cluster_indices,
                }
        if assigned_clusters != set(range(len(clusters))):
            raise ValueError(
                f"bank-01 entry {bundle.index} part lists do not cover all clusters"
            )
    return topology


def character_palette_matrix_slot(root_address: int, matrix_address: int) -> int | None:
    """Resolve a palette-global slot from absolute character matrix addresses.

    F3DEX2CBFD may rebind segment 3 to an interior palette address, so a
    display-list command's segment-relative offset is not a stable palette
    index. The renderer-provided root address and captured absolute matrix
    address are.
    """

    delta = (int(matrix_address) - int(root_address)) & 0xFFFFFFFF
    if delta > 0xFFFFFF or delta % 0x40:
        return None
    return delta // 0x40


def character_render_pass(caller_return_address: int | None, draw_mode: int) -> dict[str, Any]:
    """Classify the proven US render-to-texture call without guessing by model ID."""

    if caller_return_address == 0x15185154:
        if draw_mode != 3:
            raise ValueError("US render-to-texture callsite no longer passes draw mode 3")
        # func_15184FA4 emits FF48003F to *D_800DF088 before this call,
        # then samples that buffer as I8. Its geometry is not a body overlay.
        return {
            "kind": "render-to-texture",
            "evidence": "us-caller-0x15184FA4-call-0x1518514C",
            "caller_return_address": "0x15185154",
            "draw_mode": 3,
            "color_image_command": "0xFF48003F",
            "color_buffer_pointer_address": "0x800DF088",
            "width": 64,
            "storage_bits_per_pixel": 8,
            "subsequent_sample_format": "i8",
        }
    return {"kind": "caller-managed-target", "evidence": "not-classified-as-render-to-texture"}


def submitted_character_cluster_map(returned: dict, submitted: dict, scoped_draws: list) -> dict | None:
    """Join complete ordered clusters inside an already byte-verified call range."""
    indices = list(dict.fromkeys(draw.get('runtime_cluster_index') for draw in scoped_draws))
    source = returned.get('model_correlations', [])
    if None in indices or not source or len(indices) != len(source):
        return None
    target = {row['runtime_cluster_index']: row for row in submitted.get('model_correlations', [])}
    if len(target) != len(submitted.get('model_correlations', [])):
        return None
    mapping = {}
    for old, index in zip(source, indices):
        new = target.get(index)
        count = sum(draw['triangle_count'] for draw in scoped_draws if draw['runtime_cluster_index'] == index)
        if (new is None or old.get('signature') is None or new.get('signature') != old['signature']
                or old['triangle_count'] != count or new['triangle_count'] != count
                or str(old['runtime_cluster_index']) in mapping):
            return None
        # This mapping is also embedded in the JSON activity manifest.
        mapping[str(old['runtime_cluster_index'])] = index
    return mapping


def link_character_graphics_submission(
    events: list[dict[str, Any]], draw_call: dict[str, Any]
) -> dict[str, Any] | None:
    """Prove a renderer range executes once in the next captured graphics task."""

    return_index = int(draw_call["return_event_index"])
    following = [(index, event) for index, event in enumerate(events)
                 if index > return_index and captured_task_type(event) == 1]
    if not following:
        return None
    submit_index, submitted = following[0]
    returned = events[return_index]
    start, end = draw_call["command_buffer_start"], draw_call["command_buffer_end"]
    roots = [probe for probe in returned.get("evidence", {}).get("memory", [])
             if probe.get("name") == "character-command-buffer" and "data_base64" in probe]
    if len(roots) != 1:
        return None

    def payload(probe):
        raw = base64.b64decode(probe["data_base64"], validate=True)
        if len(raw) != probe["length"] or hashlib.sha256(raw).hexdigest() != probe["sha256"]:
            raise ValueError("character submission memory identity changed")
        return raw

    raw = payload(roots[0])
    if len(raw) != end - start or int(roots[0]["resolved_address"], 0) != start:
        raise ValueError("character submission range identity changed")
    probes = submitted.get("evidence", {}).get("memory", [])
    tasks = [probe for probe in probes if probe.get("name") == "task"]
    submitted_roots = [probe for probe in probes if probe.get("name") == "command-buffer"]
    if len(tasks) != 1 or len(submitted_roots) != 1:
        return None
    task = payload(tasks[0])
    task_root = submitted_roots[0]
    if ((int.from_bytes(task[48:52], "big") & 0x1FFFFFFF)
            != (int(task_root["resolved_address"], 0) & 0x1FFFFFFF)
            or int.from_bytes(task[52:56], "big") != task_root["length"]):
        return None
    command_probes = [probe for probe in probes if probe.get("name") == "command-buffer"
                      or probe.get("name", "").startswith("nested-display-list-")]
    if not any(
        int(probe["resolved_address"], 0) <= start
        and end <= int(probe["resolved_address"], 0) + probe["length"]
        and payload(probe)[start-int(probe["resolved_address"], 0):end-int(probe["resolved_address"], 0)] == raw
        for probe in command_probes
    ):
        return None
    rdp = submitted.get("state", {}).get("rdp", {})
    origins = rdp.get("replayed_command_origins", [])
    counts: dict[int, int] = {}
    for path in origins:
        counts[path[-1]] = counts.get(path[-1], 0) + 1
    if any(counts.get(address) != 1 for address in range(start, end, 8)):
        return None
    scoped_draws = [draw for draw in rdp.get("draw_runs", [])
                    if any(start <= address < end
                           for address in origins[draw["command_offset"] // 8])]
    return_rdp = returned.get("state", {}).get("rdp", {})
    if sum(draw["triangle_count"] for draw in scoped_draws) != sum(
        draw["triangle_count"] for draw in return_rdp.get("draw_runs", [])
    ):
        return None
    # Geometry-bearing lists must retain their bytes. Inherited material lists
    # may be visible only from the enclosing task, so they are not guessed here.
    submitted_lists = {int(probe["resolved_address"], 0): payload(probe)
                       for probe in command_probes}
    for record in return_rdp.get("walked_display_lists", []):
        if record.get("rdp", {}).get("model_correlations"):
            data = submitted_lists.get(record["address"])
            if data is None or hashlib.sha256(data).hexdigest() != record["sha256"]:
                return None
    matrix_probes = {int(probe["resolved_address"], 0): probe for probe in probes
                     if probe.get("name", "").startswith("runtime-matrix-")}
    matrices = []
    changed_slots = []
    for matrix in draw_call.get("runtime_matrices", []):
        probe = matrix_probes.get(matrix["address"])
        if probe is None:
            return None
        decoded = decode_rsp_matrix(payload(probe))
        rows = decoded["rows"]
        if any(rows[row][3] != float(row == 3) for row in range(4)):
            return None
        if any(abs(rows[row][column] - matrix["rows"][row][column]) > 1 / 65536
               for row in range(4) for column in range(3)):
            changed_slots.append(matrix["matrix_slot"])
        matrices.append({**matrix, **decoded, "sha256": probe["sha256"],
                         "status": "decoded-affine-components"})
    if not matrices:
        return None
    return {"status": "captured-range-executed-once-in-next-graphics-task",
            "event_index": submit_index, "command_buffer_start": start,
            "command_buffer_end": end, "command_sha256": roots[0]["sha256"],
            "triangle_count": sum(draw["triangle_count"] for draw in scoped_draws),
            "matrices_changed_after_return": sorted(changed_slots),
            "cluster_correspondence": submitted_character_cluster_map(return_rdp, rdp, scoped_draws),
            "runtime_matrices": matrices}


def load_character_draw_trace(
    path: Path,
    expected_digest: str,
    valid_entries: set[int],
    display_list_topology: dict[
        tuple[int, str, int], dict[str, Any]
    ] | None = None,
    model_cluster_index: list[dict[str, Any]] | None = None,
) -> dict[str, Any]:
    """Validate paired character-renderer entry/return events from one state."""

    data = path.read_bytes()
    lines = [json.loads(line) for line in data.splitlines() if line.strip()]
    if not lines or lines[0].get("record_type") != "session":
        raise ValueError(f"character draw trace has no session record: {path}")
    if lines[0].get("spec_name") != "character-model-draw-ranges":
        raise ValueError(f"character draw trace uses the wrong spec: {path}")
    if any(line.get("schema") != "conker.model-draw-state-trace/v1" for line in lines):
        raise ValueError(f"character draw trace schema changed: {path}")
    trace_digest = lines[0].get("normalized_sha1")
    if trace_digest is not None and trace_digest != expected_digest:
        raise ValueError(f"character draw trace belongs to a different ROM: {path}")

    pending: list[dict[str, Any]] = []
    draw_calls = []
    boundary_count = 0
    task_type_counts: dict[int | None, int] = {}
    events = [line for line in lines if line.get("record_type") == "draw_state"]
    for event_index, event in enumerate(events):
        if model_cluster_index is not None:
            refresh_trace_model_correlations(event, model_cluster_index)
        breakpoint = event.get("breakpoint")
        model = event.get("state", {}).get("model", {})
        registers = event.get("evidence", {}).get("registers", {})
        try:
            stack_pointer = int(registers["sp"], 0) & 0xFFFFFFFF
        except (KeyError, TypeError, ValueError) as error:
            raise ValueError(f"character draw stack evidence changed: {path}") from error
        if breakpoint == "character-model-draw-enter":
            slot = int(model["draw_character_slot"])
            records = model.get("active_records", [])
            selected = [record for record in records if int(record["slot"]) == slot]
            if len(selected) != 1:
                raise ValueError(f"character draw slot is not active: {path}")
            entry = int(selected[0]["entry"])
            if entry not in valid_entries:
                raise ValueError(
                    f"character draw references absent bank-01 entry {entry}: {path}"
                )
            start = int(model["command_buffer_start"]) & 0xFFFFFFFF
            if start & 7:
                raise ValueError(f"character draw start is not aligned: {path}")
            caller_return_address = (
                int(registers["ra"], 0) & 0xFFFFFFFF if "ra" in registers else None
            )
            pending.append(
                {
                    "event_index": event_index,
                    "hit_index": event.get("hit_index"),
                    "slot": slot,
                    "entry": entry,
                    "task_submission_index": boundary_count,
                    "command_buffer_start": start,
                    "return_stack_pointer": (stack_pointer - 0x150) & 0xFFFFFFFF,
                    "root_matrix_address": int(model["root_matrix_address"])
                    & 0xFFFFFFFF,
                    "part_selections": [],
                    "caller_return_address": (
                        f"0x{caller_return_address:08X}" if caller_return_address is not None else None
                    ),
                    "render_pass": character_render_pass(
                        caller_return_address, int(model["draw_argument_6"])
                    ),
                    "arguments": [
                        int(model[f"draw_argument_{index}"])
                        for index in range(4, 8)
                    ],
                }
            )
        elif breakpoint in {
            "character-normal-part-selected",
            "character-extra-part-selected",
        }:
            matches = [
                index
                for index, record in enumerate(pending)
                if record["return_stack_pointer"] == stack_pointer
            ]
            if not matches:
                raise ValueError(
                    f"character part selection has no matching draw entry: {path}"
                )
            record = pending[matches[-1]]
            character_record_address = int(model["character_record_address"]) & 0xFFFFFFFF
            expected_record_address = (
                CHARACTER_POOL_ADDRESS
                + int(record["slot"]) * CHARACTER_POOL_RECORD_SIZE
            )
            if character_record_address != expected_record_address:
                raise ValueError(
                    f"character part selection record address changed: {path}"
                )
            record["part_selections"].append(
                {
                    "event_index": event_index,
                    "hit_index": event.get("hit_index"),
                    "table": (
                        "normal"
                        if breakpoint == "character-normal-part-selected"
                        else "extra"
                    ),
                    "display_model_index": int(model["display_model_index"]),
                    "secondary_model_index": int(model["secondary_model_index"]),
                    "draw_mode": int(model["draw_mode"]),
                    "part_index": int(model["part_index"]),
                    "part_table_slot_address": int(
                        model["part_table_slot_address"]
                    )
                    & 0xFFFFFFFF,
                    "selected_display_list": int(model["selected_display_list"])
                    & 0xFFFFFFFF,
                }
            )
        elif breakpoint == "character-model-draw-return":
            matches = [
                index
                for index, record in enumerate(pending)
                if record["return_stack_pointer"] == stack_pointer
            ]
            if not matches:
                raise ValueError(f"character draw return has no matching entry: {path}")
            record = pending.pop(matches[-1])
            end = int(model["command_buffer_end"]) & 0xFFFFFFFF
            if end < record["command_buffer_start"] or end & 7:
                raise ValueError(f"character draw command range changed: {path}")
            record.pop("return_stack_pointer")
            record.update(
                {
                    "return_event_index": event_index,
                    "return_hit_index": event.get("hit_index"),
                    "command_buffer_end": end,
                    "command_byte_count": end - record["command_buffer_start"],
                }
            )
            command_probe = next(
                (
                    probe
                    for probe in event.get("evidence", {}).get("memory", [])
                    if probe.get("name") == "character-command-buffer"
                ),
                None,
            )
            if command_probe is not None:
                if (
                    int(command_probe["resolved_address"], 0)
                    != record["command_buffer_start"]
                    or int(command_probe["length"]) != record["command_byte_count"]
                ):
                    raise ValueError(
                        f"character draw command evidence changed: {path}"
                    )
                rdp = event.get("state", {}).get("rdp", {})
                correlations = rdp.get("model_correlations", [])
                material_correlations = rdp.get(
                    "material_run_correlations", []
                )
                model_sequence = resolve_character_model_sequence(correlations)
                walked_lists_by_address = {
                    int(item["address"]): item
                    for item in rdp.get("walked_display_lists", [])
                }
                for selection in record["part_selections"]:
                    selected_list = walked_lists_by_address.get(
                        selection["selected_display_list"]
                    )
                    if selected_list is None:
                        raise ValueError(
                            "character selected part list was not captured: "
                            f"{path}"
                        )
                    selected_correlations = selected_list.get("rdp", {}).get(
                        "model_correlations", []
                    )
                    selection["display_list_sha256"] = selected_list["sha256"]
                    selection["display_list_byte_count"] = int(
                        selected_list["length"]
                    )
                    selection["model_correlation_count"] = len(
                        selected_correlations
                    )
                    selection["_model_correlations"] = selected_correlations
                    topology = (
                        display_list_topology.get(
                            (
                                int(selection["display_model_index"]),
                                selection["table"],
                                int(selection["part_index"]),
                            )
                        )
                        if display_list_topology is not None
                        else None
                    )
                    if display_list_topology is not None and topology is None:
                        raise ValueError(
                            "character selected part is absent from the ROM pointer "
                            f"table: {path}"
                        )
                    if topology is not None:
                        static_pointer = int(topology["static_pointer_offset"])
                        selection["static_display_list_offset"] = static_pointer
                        selection["model_runtime_base"] = (
                            int(selection["selected_display_list"]) - static_pointer
                        ) & 0xFFFFFFFF
                    selection_resolution = resolve_character_model_sequence(
                        selected_correlations,
                        expected_bank_entry=(
                            0x01,
                            int(selection["display_model_index"]),
                        ),
                        expected_static_cluster_indices=(
                            set(topology["static_cluster_indices"])
                            if topology is not None
                            else None
                        ),
                    )
                    if (
                        topology is not None
                        and selection_resolution.get("status") == "resolved"
                    ):
                        selection_resolution["resolution_basis"] = (
                            "renderer-model-header-pointer-table"
                        )
                    selection["model_sequence_resolution"] = selection_resolution
                runtime_bases: dict[int, set[int]] = {}
                for selection in record["part_selections"]:
                    runtime_base = selection.get("model_runtime_base")
                    if runtime_base is not None:
                        runtime_bases.setdefault(
                            int(selection["display_model_index"]), set()
                        ).add(int(runtime_base))
                if any(len(bases) != 1 for bases in runtime_bases.values()):
                    raise ValueError(
                        f"character selected parts disagree on model base: {path}"
                    )
                resolve_character_part_selection_sequence(record["part_selections"])
                part_sequence = resolve_character_call_from_part_selections(
                    record["part_selections"]
                )
                if (
                    model_sequence.get("status") != "resolved"
                    and part_sequence is not None
                ):
                    model_sequence = part_sequence
                runtime_matrices_by_slot: dict[int, dict[str, Any]] = {}
                for matrix in event.get("state", {}).get("joint_matrices", []):
                    references = matrix.get("references", [])
                    if not any(reference.get("segment") == 3 for reference in references):
                        continue
                    matrix_slot = character_palette_matrix_slot(
                        record["root_matrix_address"], matrix["address"]
                    )
                    if matrix_slot is None:
                        raise ValueError(
                            "character runtime matrix address changed: "
                            f"{path}"
                        )
                    candidate = {
                        "matrix_slot": matrix_slot,
                        "address": int(matrix["address"]),
                        "sha256": matrix["sha256"],
                        "layout": matrix.get("layout"),
                        "status": matrix.get("status"),
                        "rows": matrix.get("rows"),
                        "translation": matrix.get("translation"),
                    }
                    previous = runtime_matrices_by_slot.get(matrix_slot)
                    if previous is not None and previous != candidate:
                        raise ValueError(
                            "character runtime matrix slot has conflicting "
                            f"captures: {path}"
                        )
                    runtime_matrices_by_slot[matrix_slot] = candidate
                record.update(
                    {
                        "command_sha256": command_probe["sha256"],
                        "decoded_command_count": int(
                            rdp.get("effective_command_count", 0)
                        ),
                        "nested_display_list_call_count": len(
                            rdp.get("nested_display_lists", [])
                        ),
                        "model_correlation_count": len(correlations),
                        "model_correlations": correlations,
                        "model_sequence_resolution": model_sequence,
                        "material_run_correlation_count": len(
                            material_correlations
                        ),
                        "material_run_correlations": material_correlations,
                        "part_selection_count": len(record["part_selections"]),
                        "runtime_matrix_count": len(
                            event.get("state", {}).get("joint_matrices", [])
                        ),
                        "runtime_matrices": [
                            runtime_matrices_by_slot[slot]
                            for slot in sorted(runtime_matrices_by_slot)
                        ],
                    }
                )
            draw_calls.append(record)
        elif breakpoint == "character-draws-at-graphics-submit":
            task_type = captured_task_type(event)
            task_type_counts[task_type] = task_type_counts.get(task_type, 0) + 1
            # Preserve the historical RSP-boundary index used by stored poses.
            # Older specs also captured audio; this is not proof of a draw's
            # inclusion in a submitted graphics command buffer.
            boundary_count += 1
        else:
            raise ValueError(f"character draw trace breakpoint changed: {path}")
    if pending:
        raise ValueError(f"character draw trace has unterminated calls: {path}")
    if boundary_count < 1 or not events or events[-1].get("breakpoint") != (
        "character-draws-at-graphics-submit"
    ):
        raise ValueError(f"character draw trace has no terminal graphics boundary: {path}")
    for draw_call in draw_calls:
        submission = link_character_graphics_submission(events, draw_call)
        if submission is not None:
            draw_call["renderer_return_matrices"] = draw_call["runtime_matrices"]
            draw_call["runtime_matrices"] = submission.pop("runtime_matrices")
            draw_call["submitted_graphics"] = submission
    return {
        "file": display_path(path),
        "sha256": hashlib.sha256(data).hexdigest(),
        "normalized_sha1": trace_digest,
        "tool_revisions": lines[0].get("tool_revisions"),
        "event_count": len(events),
        "task_submission_count": boundary_count,
        "graphics_task_submission_count": task_type_counts.get(1, 0),
        "non_graphics_task_submission_count": sum(
            count for kind, count in task_type_counts.items() if kind not in (None, 1)
        ),
        "untyped_task_submission_count": task_type_counts.get(None, 0),
        "draw_call_count": len(draw_calls),
        "submitted_graphics_draw_call_count": sum("submitted_graphics" in call for call in draw_calls),
        "draw_calls": draw_calls,
    }


def resolve_character_model_sequence(
    correlations: list[dict[str, Any]],
    expected_bank_entry: tuple[int, int] | None = None,
    expected_static_cluster_indices: set[int] | None = None,
) -> dict[str, Any]:
    """Resolve one renderer call by its shared model and static cluster order."""

    if not correlations:
        return {"status": "no-model-correlations", "resolved_clusters": []}

    def candidate_allowed(candidate: dict[str, Any]) -> bool:
        return bool(
            (
                expected_bank_entry is None
                or (
                    int(candidate["bank"]),
                    int(candidate["entry"]),
                )
                == expected_bank_entry
            )
            and (
                expected_static_cluster_indices is None
                or int(candidate["static_cluster_index"])
                in expected_static_cluster_indices
            )
        )

    identity_sets = [
        {
            (
                int(candidate["bank"]),
                int(candidate["entry"]),
                int(candidate["segment"]),
                candidate["model_sha1"],
            )
            for candidate in correlation.get("candidates", [])
            if candidate_allowed(candidate)
        }
        for correlation in correlations
    ]
    common_identities = set.intersection(*identity_sets)
    if len(common_identities) != 1:
        return {
            "status": "no-unique-common-model",
            "common_model_count": len(common_identities),
            "resolved_clusters": [],
        }
    identity = next(iter(common_identities))
    layers = []
    for correlation in correlations:
        candidates_by_cluster = {
            int(candidate["static_cluster_index"]): candidate
            for candidate in correlation.get("candidates", [])
            if (
                int(candidate["bank"]),
                int(candidate["entry"]),
                int(candidate["segment"]),
                candidate["model_sha1"],
            )
            == identity
            and candidate_allowed(candidate)
        }
        if not candidates_by_cluster:
            return {
                "status": "common-model-missing-cluster",
                "common_model_count": 1,
                "resolved_clusters": [],
            }
        layers.append(
            [candidates_by_cluster[index] for index in sorted(candidates_by_cluster)]
        )

    paths = [
        (candidate, 1, [candidate])
        for candidate in layers[0]
    ]
    for layer in layers[1:]:
        next_paths = []
        for candidate in layer:
            compatible = [
                (count, path)
                for previous, count, path in paths
                if count
                and int(previous["static_cluster_index"])
                < int(candidate["static_cluster_index"])
            ]
            count = min(2, sum(item[0] for item in compatible))
            path = compatible[0][1] + [candidate] if compatible else []
            next_paths.append((candidate, count, path))
        paths = next_paths
    path_count = min(2, sum(count for _, count, _ in paths))
    if path_count != 1:
        return {
            "status": "ambiguous-static-cluster-order",
            "common_model_count": 1,
            "candidate_path_count": path_count,
            "source_model": {
                "bank": identity[0],
                "entry": identity[1],
                "segment": identity[2],
                "model_sha1": identity[3],
            },
            "resolved_clusters": [],
        }
    selected = next(path for _, count, path in paths if count == 1)
    return {
        "status": "resolved",
        "common_model_count": 1,
        "candidate_path_count": 1,
        "source_model": {
            "bank": identity[0],
            "entry": identity[1],
            "segment": identity[2],
            "model_sha1": identity[3],
        },
        "resolved_cluster_count": len(selected),
        "resolved_face_count": sum(
            int(candidate["triangle_count"]) for candidate in selected
        ),
        "resolved_clusters": [
            {
                "static_cluster_index": int(candidate["static_cluster_index"]),
                "first_face": int(candidate["static_first_face"]),
                "face_count": int(candidate["triangle_count"]),
                "material_run": int(candidate["material_run"]["index"]),
                "matrix_index": candidate["material_run"].get("matrix_index"),
            }
            for candidate in selected
        ],
    }


def resolve_character_part_selection_sequence(
    selections: list[dict[str, Any]],
) -> None:
    """Use renderer part order to resolve aliases spanning sibling part lists."""

    display_model_indices = {
        int(selection["display_model_index"]) for selection in selections
    }
    all_correlations = [
        correlation
        for selection in selections
        for correlation in selection.get("_model_correlations", [])
    ]
    if len(display_model_indices) == 1 and all_correlations:
        display_model_index = next(iter(display_model_indices))
        combined = resolve_character_model_sequence(
            all_correlations,
            expected_bank_entry=(0x01, display_model_index),
        )
        if combined.get("status") == "resolved":
            offset = 0
            for selection in selections:
                count = int(selection["model_correlation_count"])
                clusters = combined["resolved_clusters"][offset : offset + count]
                offset += count
                ordered_resolution = {
                    "status": "resolved",
                    "resolution_basis": "renderer-model-index-and-part-order",
                    "common_model_count": 1,
                    "candidate_path_count": 1,
                    "source_model": combined["source_model"],
                    "resolved_cluster_count": len(clusters),
                    "resolved_face_count": sum(
                        int(cluster["face_count"]) for cluster in clusters
                    ),
                    "resolved_clusters": clusters,
                }
                previous = selection.get("model_sequence_resolution", {})
                if previous.get("status") == "resolved":
                    if previous.get("resolved_clusters") != clusters:
                        raise ValueError(
                            "renderer part-list and sibling-order resolutions disagree"
                        )
                else:
                    selection["model_sequence_resolution"] = ordered_resolution
            if offset != len(combined["resolved_clusters"]):
                raise ValueError("renderer part cluster partition changed")
    for selection in selections:
        selection.pop("_model_correlations", None)


def resolve_character_call_from_part_selections(
    selections: list[dict[str, Any]],
) -> dict[str, Any] | None:
    """Combine exact renderer-selected ROM part lists into one model sequence."""

    if not selections:
        return None
    sequences = [
        selection.get("model_sequence_resolution", {}) for selection in selections
    ]
    if any(sequence.get("status") != "resolved" for sequence in sequences):
        return None
    if any(
        not isinstance(sequence.get("source_model"), dict) for sequence in sequences
    ):
        return None
    source_models = {
        (
            int(sequence["source_model"]["bank"]),
            int(sequence["source_model"]["entry"]),
            int(sequence["source_model"]["segment"]),
            sequence["source_model"]["model_sha1"],
        )
        for sequence in sequences
    }
    if len(source_models) != 1:
        return None
    clusters = [
        cluster
        for sequence in sequences
        for cluster in sequence.get("resolved_clusters", [])
    ]
    if len(clusters) != sum(
        int(selection.get("model_correlation_count", 0)) for selection in selections
    ):
        return None
    cluster_indices = [int(cluster["static_cluster_index"]) for cluster in clusters]
    if any(
        previous >= current
        for previous, current in zip(cluster_indices, cluster_indices[1:])
    ):
        return None
    source = next(iter(source_models))
    return {
        "status": "resolved",
        "resolution_basis": "renderer-model-header-pointer-table",
        "common_model_count": 1,
        "candidate_path_count": 1,
        "source_model": {
            "bank": source[0],
            "entry": source[1],
            "segment": source[2],
            "model_sha1": source[3],
        },
        "resolved_cluster_count": len(clusters),
        "resolved_face_count": sum(
            int(cluster["face_count"]) for cluster in clusters
        ),
        "resolved_clusters": clusters,
    }


def extract_character_activity(
    profile: str,
    rom_argument: Path | None,
    trace_paths: tuple[Path, ...],
    runtime_material_path: Path | None,
    output: Path,
    force: bool,
    draw_trace_paths: tuple[Path, ...] = (),
    part_table_trace_paths: tuple[Path, ...] = (),
) -> dict[str, Any]:
    """Aggregate active bank-01 entries across reproducible savestate snapshots."""

    if not trace_paths:
        raise ValueError("at least one --trace JSONL file is required")
    _, _, digest, bundles, _ = load_model_bundles(profile, rom_argument, 0x01)
    valid_entries = {bundle.index for bundle in bundles}
    material_catalog = (
        load_runtime_material_catalog(runtime_material_path, digest)
        if runtime_material_path is not None
        else {}
    )
    material_entries = {key[1] for key in material_catalog if key[0] == 0x01}
    source_traces = []
    entry_states: dict[int, set[str]] = {}
    entry_observations: dict[int, int] = {}
    active_record_observation_count = 0
    for source_path in trace_paths:
        path = source_path if source_path.is_absolute() else ROOT / source_path
        trace = load_character_activity_trace(path, digest, valid_entries)
        state_name = path.stem
        source_traces.append({"state": state_name, **trace})
        for snapshot in trace["snapshots"]:
            active_record_observation_count += snapshot["active_record_count"]
            for record in snapshot["active_records"]:
                entry = int(record["entry"])
                entry_states.setdefault(entry, set()).add(state_name)
                entry_observations[entry] = entry_observations.get(entry, 0) + 1
    source_part_table_traces = []
    renderer_part_table_records: dict[int, dict[str, Any]] = {}
    for source_path in part_table_trace_paths:
        path = source_path if source_path.is_absolute() else ROOT / source_path
        trace = load_character_part_table_trace(path, digest)
        state_name = path.stem
        source_part_table_traces.append({"state": state_name, **trace})
        for table in trace["part_tables"]:
            model_index = int(table["model_index"])
            record = renderer_part_table_records.setdefault(
                model_index,
                {
                    "model_index": model_index,
                    "states": set(),
                    "part_counts": set(),
                    "part_pointer_table_addresses": set(),
                    "extra_part_pointer_table_addresses": set(),
                },
            )
            record["states"].add(state_name)
            record["part_counts"].add(int(table["part_count"]))
            if table["part_pointer_table_address"] is not None:
                record["part_pointer_table_addresses"].add(
                    int(table["part_pointer_table_address"])
                )
            if table["extra_part_pointer_table_address"] is not None:
                record["extra_part_pointer_table_addresses"].add(
                    int(table["extra_part_pointer_table_address"])
                )
    source_draw_traces = []
    drawn_entry_states: dict[int, set[str]] = {}
    drawn_entry_observations: dict[int, int] = {}
    composition_records: dict[tuple[str, int], dict[str, Any]] = {}
    composition_instance_records: dict[
        tuple[str, int, int, int, int, str], dict[str, Any]
    ] = {}
    display_list_topology = character_display_list_topology(bundles)

    def new_composition_record(render_pass: dict[str, Any]) -> dict[str, Any]:
        return {
            "render_pass": render_pass,
            "call_count": 0,
            "command_hashes": set(),
            "command_byte_counts": set(),
            "runtime_matrix_counts": set(),
            "status_counts": {},
            "parts": {},
            "model_sequence_status_counts": {},
            "sequence_source_models": set(),
            "resolved_clusters": {},
            "runtime_matrix_observations": {},
            "renderer_part_selections": {},
        }

    def add_runtime_matrices(
        composition: dict[str, Any], draw_call: dict[str, Any]
    ) -> None:
        for matrix in draw_call.get("runtime_matrices", []):
            slot = int(matrix["matrix_slot"])
            observations = composition["runtime_matrix_observations"].setdefault(
                slot, {}
            )
            key = (
                matrix.get("status"),
                matrix["sha256"],
            )
            observation = observations.setdefault(
                key,
                {
                    **matrix,
                    "observation_count": 0,
                },
            )
            observation["observation_count"] += 1

    def add_composition_correlation(
        composition: dict[str, Any], correlation: dict[str, Any]
    ) -> None:
        status = correlation.get("status", "unknown")
        composition["status_counts"][status] = (
            composition["status_counts"].get(status, 0) + 1
        )
        resolved = correlation.get("resolved")
        if not isinstance(resolved, dict):
            return
        material_run = resolved.get("material_run") or {}
        key = (
            int(resolved["bank"]),
            int(resolved["entry"]),
            int(resolved["segment"]),
            int(material_run["index"]),
        )
        part = composition["parts"].setdefault(
            key,
            {
                "bank": key[0],
                "entry": key[1],
                "segment": key[2],
                "material_run": key[3],
                "first_face": int(material_run["first_face"]),
                "face_count": int(material_run["face_count"]),
                "model_sha1": resolved["model_sha1"],
                "observation_count": 0,
                "runtime_matrix_slots": set(),
            },
        )
        part["observation_count"] += 1
        matrix_slot = correlation.get("matrix_slot", {}).get("runtime")
        if isinstance(matrix_slot, int):
            part["runtime_matrix_slots"].add(matrix_slot)

    def add_renderer_part_selections(
        composition: dict[str, Any], draw_call: dict[str, Any]
    ) -> None:
        for selection in draw_call.get("part_selections", []):
            sequence = selection.get("model_sequence_resolution", {})
            source_model = sequence.get("source_model")
            resolved_clusters = tuple(
                int(cluster["static_cluster_index"])
                for cluster in sequence.get("resolved_clusters", [])
            )
            source_identity = (
                (
                    int(source_model["bank"]),
                    int(source_model["entry"]),
                    int(source_model["segment"]),
                    source_model["model_sha1"],
                )
                if isinstance(source_model, dict)
                else None
            )
            key = (
                selection["table"],
                int(selection["display_model_index"]),
                int(selection["part_index"]),
                source_identity,
                resolved_clusters,
            )
            record = composition["renderer_part_selections"].setdefault(
                key,
                {
                    "table": selection["table"],
                    "display_model_index": int(selection["display_model_index"]),
                    "part_index": int(selection["part_index"]),
                    "source_model": source_model,
                    "resolved_clusters": list(
                        sequence.get("resolved_clusters", [])
                    ),
                    "model_sequence_status": sequence.get("status", "absent"),
                    "observation_count": 0,
                    "draw_modes": set(),
                    "secondary_model_indices": set(),
                    "display_list_addresses": set(),
                    "display_list_sha256s": set(),
                    "display_list_byte_counts": set(),
                    "static_display_list_offsets": set(),
                    "model_runtime_bases": set(),
                },
            )
            record["observation_count"] += 1
            record["draw_modes"].add(int(selection["draw_mode"]))
            record["secondary_model_indices"].add(
                int(selection["secondary_model_index"])
            )
            record["display_list_addresses"].add(
                int(selection["selected_display_list"])
            )
            record["display_list_sha256s"].add(
                selection["display_list_sha256"]
            )
            record["display_list_byte_counts"].add(
                int(selection["display_list_byte_count"])
            )
            if selection.get("static_display_list_offset") is not None:
                record["static_display_list_offsets"].add(
                    int(selection["static_display_list_offset"])
                )
            if selection.get("model_runtime_base") is not None:
                record["model_runtime_bases"].add(
                    int(selection["model_runtime_base"])
                )

    model_cluster_index = load_model_cluster_index() if draw_trace_paths else None
    for draw_trace_index, source_path in enumerate(draw_trace_paths):
        path = source_path if source_path.is_absolute() else ROOT / source_path
        trace = load_character_draw_trace(
            path,
            digest,
            valid_entries,
            display_list_topology,
            model_cluster_index,
        )
        state_name = path.stem
        source_draw_traces.append(
            {"trace_index": draw_trace_index, "state": state_name, **trace}
        )
        for draw_call in trace["draw_calls"]:
            entry = int(draw_call["entry"])
            render_pass = draw_call["render_pass"]
            pass_kind = render_pass["kind"]
            drawn_entry_states.setdefault(entry, set()).add(state_name)
            drawn_entry_observations[entry] = (
                drawn_entry_observations.get(entry, 0) + 1
            )
            composition = composition_records.setdefault(
                (pass_kind, entry), new_composition_record(render_pass)
            )
            instance_key = (
                state_name,
                int(draw_call["task_submission_index"]),
                int(draw_call["slot"]),
                entry,
                int(draw_call["root_matrix_address"]),
                pass_kind,
            )
            instance = composition_instance_records.setdefault(
                instance_key, new_composition_record(render_pass)
            )
            for target in (composition, instance):
                target["call_count"] += 1
                if draw_call.get("command_sha256") is not None:
                    target["command_hashes"].add(draw_call["command_sha256"])
                target["command_byte_counts"].add(
                    int(draw_call["command_byte_count"])
                )
                if draw_call.get("runtime_matrix_count") is not None:
                    target["runtime_matrix_counts"].add(
                        int(draw_call["runtime_matrix_count"])
                    )
                sequence = draw_call.get("model_sequence_resolution", {})
                sequence_status = sequence.get("status", "absent")
                target["model_sequence_status_counts"][sequence_status] = (
                    target["model_sequence_status_counts"].get(
                        sequence_status, 0
                    )
                    + 1
                )
                source_model = sequence.get("source_model")
                if isinstance(source_model, dict):
                    source_key = (
                        int(source_model["bank"]),
                        int(source_model["entry"]),
                        int(source_model["segment"]),
                        source_model["model_sha1"],
                    )
                    target["sequence_source_models"].add(source_key)
                    for cluster in sequence.get("resolved_clusters", []):
                        cluster_key = (
                            source_key[0],
                            source_key[1],
                            source_key[2],
                            int(cluster["static_cluster_index"]),
                        )
                        resolved_cluster = target["resolved_clusters"].setdefault(
                            cluster_key,
                            {
                                "bank": source_key[0],
                                "entry": source_key[1],
                                "segment": source_key[2],
                                "model_sha1": source_key[3],
                                **cluster,
                                "observation_count": 0,
                                "runtime_appearance_observations": set(),
                            },
                        )
                        resolved_cluster["observation_count"] += 1
                        resolved_cluster["runtime_appearance_observations"].add(
                            (
                                draw_trace_index,
                                trace["sha256"],
                                trace["file"],
                                int(draw_call["return_event_index"]),
                                draw_call.get("submitted_graphics", {}).get("event_index", -1),
                                int(draw_call["command_buffer_start"]),
                                int(draw_call["command_buffer_end"]),
                            )
                        )
            add_runtime_matrices(instance, draw_call)
            for target in (composition, instance):
                add_renderer_part_selections(target, draw_call)
            for correlation in draw_call.get("material_run_correlations", []):
                add_composition_correlation(composition, correlation)
                add_composition_correlation(instance, correlation)
    active_entries = sorted(entry_states)
    coverage = [
        {
            "entry": entry,
            "state_count": len(entry_states[entry]),
            "states": sorted(entry_states[entry]),
            "active_record_observation_count": entry_observations[entry],
            "runtime_material_covered": entry in material_entries,
            "draw_call_count": drawn_entry_observations.get(entry, 0),
            "draw_states": sorted(drawn_entry_states.get(entry, set())),
        }
        for entry in active_entries
    ]
    def composition_summary(
        composition: dict[str, Any], include_runtime_matrices: bool = False
    ) -> dict[str, Any]:
        parts = []
        for key in sorted(composition["parts"]):
            part = composition["parts"][key]
            parts.append(
                {
                    **{
                        field: value
                        for field, value in part.items()
                        if field != "runtime_matrix_slots"
                    },
                    "runtime_matrix_slots": sorted(part["runtime_matrix_slots"]),
                }
            )
        renderer_part_selections = []
        for key in sorted(
            composition["renderer_part_selections"], key=lambda value: repr(value)
        ):
            selection = composition["renderer_part_selections"][key]
            renderer_part_selections.append(
                {
                    **{
                        field: value
                        for field, value in selection.items()
                        if field
                        not in {
                            "draw_modes",
                            "secondary_model_indices",
                            "display_list_addresses",
                            "display_list_sha256s",
                            "display_list_byte_counts",
                            "static_display_list_offsets",
                            "model_runtime_bases",
                        }
                    },
                    "draw_modes": sorted(selection["draw_modes"]),
                    "secondary_model_indices": sorted(
                        selection["secondary_model_indices"]
                    ),
                    "display_list_addresses": [
                        f"0x{address:08X}"
                        for address in sorted(selection["display_list_addresses"])
                    ],
                    "display_list_sha256s": sorted(
                        selection["display_list_sha256s"]
                    ),
                    "display_list_byte_counts": sorted(
                        selection["display_list_byte_counts"]
                    ),
                    "static_display_list_offsets": [
                        f"0x{offset:X}"
                        for offset in sorted(selection["static_display_list_offsets"])
                    ],
                    "model_runtime_bases": [
                        f"0x{address:08X}"
                        for address in sorted(selection["model_runtime_bases"])
                    ],
                }
            )
        resolved_clusters = []
        for key in sorted(composition["resolved_clusters"]):
            cluster = composition["resolved_clusters"][key]
            appearances = [
                {
                    "draw_trace_index": appearance[0],
                    "draw_trace_sha256": appearance[1],
                    "draw_trace": appearance[2],
                    "event_index": appearance[3],
                    **({"submitted_graphics": {
                        "event_index": appearance[4],
                        "command_buffer_start": appearance[5],
                        "command_buffer_end": appearance[6],
                    }} if appearance[4] >= 0 else {}),
                }
                for appearance in sorted(
                    cluster["runtime_appearance_observations"]
                )
            ]
            resolved_clusters.append(
                {
                    **{
                        field: value
                        for field, value in cluster.items()
                        if field != "runtime_appearance_observations"
                    },
                    "runtime_appearance_count": len(appearances),
                    "runtime_appearances": appearances,
                }
            )
        summary = {
            "render_pass": composition["render_pass"],
            "call_count": composition["call_count"],
            "command_variant_count": len(composition["command_hashes"]),
            "command_hashes": sorted(composition["command_hashes"]),
            "command_byte_counts": sorted(composition["command_byte_counts"]),
            "runtime_matrix_counts": sorted(
                composition["runtime_matrix_counts"]
            ),
            "material_correlation_status_counts": dict(
                sorted(composition["status_counts"].items())
            ),
            "model_sequence_status_counts": dict(
                sorted(composition["model_sequence_status_counts"].items())
            ),
            "resolved_correlation_count": sum(
                count
                for status, count in composition["status_counts"].items()
                if status in ("unique", "equivalent-material-aliases")
            ),
            "unresolved_correlation_count": sum(
                count
                for status, count in composition["status_counts"].items()
                if status not in ("unique", "equivalent-material-aliases")
            ),
            "resolved_part_count": len(parts),
            "resolved_face_count": sum(part["face_count"] for part in parts),
            "resolved_source_entries": sorted({part["entry"] for part in parts}),
            "resolved_parts": parts,
            "sequence_source_models": [
                {
                    "bank": source[0],
                    "entry": source[1],
                    "segment": source[2],
                    "model_sha1": source[3],
                }
                for source in sorted(composition["sequence_source_models"])
            ],
            "resolved_cluster_count": len(resolved_clusters),
            "resolved_cluster_face_count": sum(
                cluster["face_count"] for cluster in resolved_clusters
            ),
            "resolved_clusters": resolved_clusters,
            "renderer_part_selection_variant_count": len(
                renderer_part_selections
            ),
            "renderer_part_selection_observation_count": sum(
                selection["observation_count"]
                for selection in renderer_part_selections
            ),
            "renderer_part_selections": renderer_part_selections,
        }
        if include_runtime_matrices:
            runtime_matrices = []
            for slot in sorted(composition["runtime_matrix_observations"]):
                observations = list(
                    composition["runtime_matrix_observations"][slot].values()
                )
                decoded = [
                    item
                    for item in observations
                    if item.get("status") == "decoded-affine-components"
                    and item.get("rows") is not None
                ]
                if len(observations) == 1 and len(decoded) == 1:
                    runtime_matrices.append(decoded[0])
                else:
                    runtime_matrices.append(
                        {
                            "matrix_slot": slot,
                            "status": "conflicting-or-invalid-observations",
                            "observation_variant_count": len(observations),
                            "observations": observations,
                        }
                    )
            summary["runtime_matrices"] = runtime_matrices
        return summary

    all_compositions = [
        {"entry": key[1], **composition_summary(composition_records[key])}
        for key in sorted(composition_records)
    ]
    all_composition_instances = [
        {
            "state": key[0],
            "task_submission_index": key[1],
            "slot": key[2],
            "entry": key[3],
            "root_matrix_address": f"0x{key[4]:08X}",
            **composition_summary(
                composition_instance_records[key], include_runtime_matrices=True
            ),
        }
        for key in sorted(composition_instance_records)
    ]
    character_compositions = [c for c in all_compositions if c["render_pass"]["kind"] != "render-to-texture"]
    render_texture_compositions = [c for c in all_compositions if c["render_pass"]["kind"] == "render-to-texture"]
    character_composition_instances = [c for c in all_composition_instances if c["render_pass"]["kind"] != "render-to-texture"]
    render_texture_composition_instances = [c for c in all_composition_instances if c["render_pass"]["kind"] == "render-to-texture"]
    material_path = (
        runtime_material_path
        if runtime_material_path is None or runtime_material_path.is_absolute()
        else ROOT / runtime_material_path
    )
    renderer_part_selections = [
        selection
        for trace in source_draw_traces
        for draw_call in trace["draw_calls"]
        for selection in draw_call.get("part_selections", [])
    ]
    renderer_part_tables = [
        {
            "model_index": model_index,
            "state_count": len(record["states"]),
            "states": sorted(record["states"]),
            "part_counts": sorted(record["part_counts"]),
            "part_pointer_table_addresses": [
                f"0x{address:08X}"
                for address in sorted(record["part_pointer_table_addresses"])
            ],
            "extra_part_pointer_table_addresses": [
                f"0x{address:08X}"
                for address in sorted(
                    record["extra_part_pointer_table_addresses"]
                )
            ],
        }
        for model_index, record in sorted(renderer_part_table_records.items())
    ]
    renderer_part_table_indices = set(renderer_part_table_records)
    manifest = {
        "schema_version": 1,
        "family": "runtime-character-model-activity",
        "profile": profile,
        "normalized_sha1": digest,
        "bank_index": 1,
        "source_traces": source_traces,
        "trace_file_count": len(source_traces),
        "source_draw_traces": source_draw_traces,
        "draw_trace_file_count": len(source_draw_traces),
        "source_part_table_traces": source_part_table_traces,
        "part_table_trace_file_count": len(source_part_table_traces),
        "renderer_part_table_model_count": len(renderer_part_tables),
        "renderer_part_table_model_indices": sorted(renderer_part_table_indices),
        "renderer_part_table_bank_entry_count": len(
            renderer_part_table_indices & valid_entries
        ),
        "renderer_part_table_bank_entries": sorted(
            renderer_part_table_indices & valid_entries
        ),
        "renderer_part_table_special_indices": sorted(
            renderer_part_table_indices - valid_entries
        ),
        "bank_entries_without_renderer_part_table_count": len(
            valid_entries - renderer_part_table_indices
        ),
        "bank_entries_without_renderer_part_tables": sorted(
            valid_entries - renderer_part_table_indices
        ),
        "renderer_part_tables": renderer_part_tables,
        "character_draw_task_submission_count": sum(
            trace["task_submission_count"] for trace in source_draw_traces
        ),
        "character_draw_graphics_task_submission_count": sum(
            trace["graphics_task_submission_count"] for trace in source_draw_traces
        ),
        "character_draw_non_graphics_task_submission_count": sum(
            trace["non_graphics_task_submission_count"] for trace in source_draw_traces
        ),
        "character_draw_untyped_task_submission_count": sum(
            trace["untyped_task_submission_count"] for trace in source_draw_traces
        ),
        "character_draw_call_count": sum(drawn_entry_observations.values()),
        "submitted_graphics_draw_call_count": sum(
            trace["submitted_graphics_draw_call_count"] for trace in source_draw_traces
        ),
        "renderer_part_selection_count": len(renderer_part_selections),
        "resolved_renderer_part_selection_count": sum(
            selection.get("model_sequence_resolution", {}).get("status")
            == "resolved"
            for selection in renderer_part_selections
        ),
        "renderer_display_model_indices": sorted(
            {
                int(selection["display_model_index"])
                for selection in renderer_part_selections
            }
        ),
        "drawn_entry_count": len(drawn_entry_states),
        "drawn_entries": sorted(drawn_entry_states),
        "drawn_runtime_material_covered_entry_count": len(
            set(drawn_entry_states) & material_entries
        ),
        "drawn_runtime_material_covered_entries": sorted(
            set(drawn_entry_states) & material_entries
        ),
        "character_composition_count": len(character_compositions),
        "character_compositions": character_compositions,
        "character_composition_instance_count": len(
            character_composition_instances
        ),
        "character_composition_instances": character_composition_instances,
        "render_texture_composition_count": len(render_texture_compositions),
        "render_texture_compositions": render_texture_compositions,
        "render_texture_composition_instance_count": len(render_texture_composition_instances),
        "render_texture_composition_instances": render_texture_composition_instances,
        "render_texture_draw_call_count": sum(c["call_count"] for c in render_texture_compositions),
        "snapshot_count": sum(trace["snapshot_count"] for trace in source_traces),
        "active_record_observation_count": active_record_observation_count,
        "active_entry_count": len(active_entries),
        "active_entries": active_entries,
        "runtime_material_manifest": (
            display_path(material_path) if material_path is not None else None
        ),
        "runtime_material_covered_entry_count": len(
            set(active_entries) & material_entries
        ),
        "runtime_material_covered_entries": sorted(
            set(active_entries) & material_entries
        ),
        "active_without_runtime_material_count": len(
            set(active_entries) - material_entries
        ),
        "active_without_runtime_material_entries": sorted(
            set(active_entries) - material_entries
        ),
        "unobserved_bank_entry_count": len(valid_entries - set(active_entries)),
        "unobserved_bank_entries": sorted(valid_entries - set(active_entries)),
        "coverage": coverage,
        "limitations": [
            "an active character record proves model selection but not visibility or a submitted draw",
            "a character draw range proves renderer emission before the captured task boundary but not final raster visibility",
            "a boundary-only draw trace may resume from a savestate whose command buffer was already built and is not negative evidence",
            "runtime materials remain assigned only by display-list and material-run correlation",
            "save-state snapshots do not prove characters or variants absent from the supplied states",
        ],
    }
    prepare_output(output, force)
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    if json.loads((output / "manifest.json").read_text(encoding="utf-8")) != manifest:
        raise ValueError("character activity manifest did not round-trip through JSON")
    return manifest


def merge_character_composition_geometry(
    source_models: dict[tuple[int, int, int, str], ModelGeometry],
    clusters: list[dict[str, Any]],
) -> ModelGeometry:
    """Assemble the exact ROM face clusters reached by a traced character call."""

    vertices: list[ModelVertex] = []
    faces: list[tuple[int, int, int]] = []
    material_runs: list[ModelMaterialRun] = []
    face_normal_bytes = []
    face_command_offsets = []
    face_command_opcodes = []
    face_cache_indices = []
    face_matrix_indices = []
    face_source_indices = []
    face_cull_modes = []
    vertex_bases: dict[tuple[int, int, int, str], int] = {}
    for cluster in sorted(
        clusters,
        key=lambda item: (
            int(item["bank"]),
            int(item["entry"]),
            int(item["segment"]),
            int(item["static_cluster_index"]),
        ),
    ):
        source_key = (
            int(cluster["bank"]),
            int(cluster["entry"]),
            int(cluster["segment"]),
            cluster["model_sha1"],
        )
        geometry = source_models[source_key]
        if source_key not in vertex_bases:
            vertex_bases[source_key] = len(vertices)
            vertices.extend(geometry.vertices)
        vertex_base = vertex_bases[source_key]
        first_face = int(cluster["first_face"])
        face_count = int(cluster["face_count"])
        end_face = first_face + face_count
        run_index = int(cluster["material_run"])
        run = geometry.material_runs[run_index]
        if (
            first_face < run.first_face
            or end_face > run.first_face + run.face_count
            or end_face > len(geometry.faces)
        ):
            raise ValueError("resolved character cluster exceeds its material run")
        output_first_face = len(faces)
        faces.extend(
            tuple(vertex_base + vertex for vertex in face)
            for face in geometry.faces[first_face:end_face]
        )
        material_runs.append(
            replace(run, first_face=output_first_face, face_count=face_count)
        )
        face_normal_bytes.extend(geometry.face_normal_bytes[first_face:end_face])
        face_source_indices.extend(range(first_face, end_face))
        face_command_offsets.extend(geometry.face_command_offsets[first_face:end_face])
        face_command_opcodes.extend(geometry.face_command_opcodes[first_face:end_face])
        face_cache_indices.extend(geometry.face_cache_indices[first_face:end_face])
        face_cull_modes.extend(
            geometry.face_cull_modes[first_face:end_face]
            if geometry.face_cull_modes else (None,) * face_count
        )
        face_matrix_indices.extend(
            face_vertex_matrix_indices(geometry, run, face_index)
            for face_index in range(first_face, end_face)
        )
    return ModelGeometry(
        vertices=tuple(vertices),
        faces=tuple(faces),
        display_list_offset=0,
        display_list_size=0,
        vertex_load_count=0,
        segment_8_display_list_offsets=(),
        secondary_region=None,
        tertiary_region=None,
        vertex_color_animation_offset=None,
        vertex_color_animation_table_size=0,
        vertex_color_animation_descriptors=(),
        texture_references=(),
        runtime_segment_texture_addresses=(),
        material_runs=tuple(material_runs),
        face_normal_bytes=tuple(face_normal_bytes),
        header_words=(),
        face_command_offsets=tuple(face_command_offsets),
        face_command_opcodes=tuple(face_command_opcodes),
        face_cache_indices=tuple(face_cache_indices),
        face_matrix_indices=tuple(face_matrix_indices),
        custom_normal_command_count=0,
        face_source_indices=tuple(face_source_indices),
        face_cull_modes=tuple(face_cull_modes),
    )


def transform_preview_normal(
    normal: tuple[int, int, int] | None, rows: list[list[float]]
) -> tuple[float, float, float] | None:
    """Transform a surface normal by the row-vector matrix's inverse transpose."""

    if normal is None or not any(normal):
        return None
    a, b, c = [row[:3] for row in rows[:3]]

    def cross(u, v):
        return (u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0])

    cofactors = (cross(b, c), cross(c, a), cross(a, b))
    determinant = sum(x * y for x, y in zip(a, cofactors[0]))
    if determinant == 0 or not math.isfinite(determinant):
        return None
    transformed = tuple(
        sum(normal[row] * cofactors[row][axis] for row in range(3)) / determinant
        for axis in range(3)
    )
    length = math.sqrt(sum(value * value for value in transformed))
    if length == 0 or not math.isfinite(length):
        return None
    return tuple(value / length for value in transformed)


def bake_character_runtime_pose(
    geometry: ModelGeometry,
    matrix_rows_by_index: dict[int, list[list[float]]],
    root_translation: list[float],
) -> ModelGeometry:
    """Bake one captured character matrix palette into preview geometry."""

    if len(root_translation) != 3 or not all(
        math.isfinite(float(value)) for value in root_translation
    ):
        raise ValueError("character runtime root translation is invalid")
    vertices: list[ModelVertex] = []
    faces: list[tuple[int, int, int]] = []
    material_runs = []
    preview_normals = []
    normal_cache = {}
    for matrix_index in geometry_vertex_matrix_indices(geometry):
        rows = matrix_rows_by_index.get(matrix_index)
        if rows is None:
            raise ValueError(f"character runtime matrix {matrix_index} is absent")
        if (
            len(rows) != 4
            or any(len(row) != 4 for row in rows)
            or not all(
                math.isfinite(float(value)) for row in rows for value in row
            )
        ):
            raise ValueError(f"character runtime matrix {matrix_index} is invalid")
    for run in geometry.material_runs:
        output_first_face = len(faces)
        run_vertex_indices: dict[tuple[int, int], int] = {}
        for face_offset, face in enumerate(geometry.faces[
            run.first_face : run.first_face + run.face_count
        ]):
            vertex_matrices = face_vertex_matrix_indices(
                geometry, run, run.first_face + face_offset
            )
            if geometry.face_normal_bytes:
                transformed_normals = []
                for normal, matrix_index in zip(
                    geometry.face_normal_bytes[run.first_face + face_offset], vertex_matrices
                ):
                    key = (normal, matrix_index)
                    if key not in normal_cache:
                        normal_cache[key] = transform_preview_normal(
                            normal, matrix_rows_by_index[matrix_index]
                        )
                    transformed_normals.append(normal_cache[key])
                preview_normals.append(tuple(transformed_normals))
            output_face = []
            for source_index, matrix_index in zip(face, vertex_matrices):
                rows = matrix_rows_by_index[matrix_index]
                key = (source_index, matrix_index)
                output_index = run_vertex_indices.get(key)
                if output_index is None:
                    vertex = geometry.vertices[source_index]
                    position = (float(vertex.x), float(vertex.y), float(vertex.z))
                    transformed = tuple(
                        sum(position[row] * float(rows[row][axis]) for row in range(3))
                        + float(rows[3][axis])
                        - float(root_translation[axis])
                        for axis in range(3)
                    )
                    output_index = len(vertices)
                    vertices.append(
                        replace(
                            vertex,
                            x=transformed[0],
                            y=transformed[1],
                            z=transformed[2],
                        )
                    )
                    run_vertex_indices[key] = output_index
                output_face.append(output_index)
            faces.append(tuple(output_face))
        material_runs.append(
            replace(
                run,
                first_face=output_first_face,
                face_count=len(faces) - output_first_face,
            )
        )
    return replace(
        geometry,
        vertices=tuple(vertices),
        faces=tuple(faces),
        material_runs=tuple(material_runs),
        # Transformed normals are for interchange shading. Keep them distinct
        # from CBFD's source normal bytes and unquantized until glTF encoding.
        face_normal_bytes=(),
        face_preview_normals=tuple(preview_normals),
        face_matrix_indices=(),
        custom_normal_command_count=0,
    )


def load_runtime_material_appearance_lookup(
    path: Path | None,
    expected_digest: str,
) -> dict[tuple[str, int], tuple[int, int]]:
    """Index exact runtime appearances by source trace content and event."""

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
    traces = {
        int(trace["trace_index"]): trace
        for trace in manifest.get("source_traces", [])
    }
    lookup: dict[tuple[str, int], tuple[int, int]] = {}
    for appearance in manifest.get("appearances", []):
        trace_index = int(appearance["trace_index"])
        event_index = int(appearance["event_index"])
        trace = traces.get(trace_index)
        if trace is None:
            raise ValueError("runtime appearance references an absent source trace")
        key = (trace["sha256"], event_index)
        candidate = (trace_index, event_index)
        previous = lookup.get(key)
        if previous is None or candidate < previous:
            lookup[key] = candidate
    return lookup


def extract_character_composition_previews(
    profile: str,
    rom_argument: Path | None,
    activity_manifest_path: Path,
    output: Path,
    force: bool,
    texture_root: Path | None = None,
    runtime_material_path: Path | None = None,
    task_runtime_material_path: Path | None = None,
    attachment_trace_paths: tuple[Path, ...] = (),
) -> dict[str, Any]:
    """Export neutral and captured-pose trace-resolved character previews."""

    _, _, digest, bundles, _ = load_model_bundles(profile, rom_argument, 0x01)
    path = (
        activity_manifest_path
        if activity_manifest_path.is_absolute()
        else ROOT / activity_manifest_path
    )
    activity = json.loads(path.read_text(encoding="utf-8"))
    if (
        activity.get("family") != "runtime-character-model-activity"
        or activity.get("normalized_sha1") != digest
    ):
        raise ValueError("character composition manifest identity changed")
    bundle_by_entry = {bundle.index: bundle for bundle in bundles}
    flat_payloads = (
        load_flat_asset_payloads(profile, rom_argument, digest)
        if texture_root is not None
        else None
    )
    preview_texture_catalog = (
        load_preview_texture_catalog(texture_root, digest, tuple(flat_payloads))
        if texture_root is not None and flat_payloads is not None
        else {}
    )
    runtime_material_catalog = load_runtime_material_catalog(
        runtime_material_path, digest
    )
    task_material_path = task_runtime_material_path or runtime_material_path
    runtime_appearance_lookup = load_runtime_material_appearance_lookup(
        task_material_path, digest
    )
    runtime_appearance_catalogs: dict[
        tuple[tuple[int, int], tuple[int, int] | None],
        dict[tuple[int, int, int, int], dict[str, Any]]
    ] = {}
    prepare_output(output, force)
    geometry_dir = output / "geometry"
    geometry_dir.mkdir(parents=True, exist_ok=True)
    posed_dir = output / "posed"
    posed_dir.mkdir(parents=True, exist_ok=True)
    copied_textures: dict[PreviewTexture, str] = {}
    texture_status_counts: dict[str, int] = {}
    source_model_cache: dict[tuple[int, int, int, str], ModelGeometry] = {}

    def source_models_for(composition: dict[str, Any]):
        source_models = {}
        for source in composition.get("sequence_source_models", []):
            source_key = (
                int(source["bank"]),
                int(source["entry"]),
                int(source["segment"]),
                source["model_sha1"],
            )
            if source_key[0] != 1 or source_key[2] != 0:
                raise ValueError(
                    "character composition references a non-character model"
                )
            if source_key not in source_model_cache:
                bundle = bundle_by_entry[source_key[1]]
                segment = bundle.segments[0]
                if hashlib.sha1(segment.data).hexdigest() != source_key[3]:
                    raise ValueError("character composition source hash changed")
                geometry, _ = parse_character_model_geometry(segment.data)
                source_model_cache[source_key] = geometry
            source_models[source_key] = source_model_cache[source_key]
        return source_models

    def material_maps_for(
        geometry: ModelGeometry,
        clusters: list[dict[str, Any]],
        task_local: bool = False,
    ) -> tuple[
        dict[int, str],
        dict[str, str],
        dict[int, dict[str, Any]],
        int,
        int,
    ]:
        ordered_clusters = sorted(
            clusters,
            key=lambda item: (
                int(item["bank"]),
                int(item["entry"]),
                int(item["segment"]),
                int(item["static_cluster_index"]),
            ),
        )
        if len(ordered_clusters) != len(geometry.material_runs):
            raise ValueError("character composition material identity changed")
        gltf_texture_files = {}
        mtl_texture_files = {}
        runtime_materials = {}
        linked_face_count = 0
        task_local_runtime_material_run_count = 0
        conflicting_mtl_materials: set[str] = set()
        for run_index, (run, cluster) in enumerate(
            zip(geometry.material_runs, ordered_clusters)
        ):
            source_key = (
                int(cluster["bank"]),
                int(cluster["entry"]),
                int(cluster["segment"]),
                int(cluster["material_run"]),
            )
            runtime_material = None
            if task_local:
                appearances = cluster.get("runtime_appearances", [])
                if len(appearances) == 1:
                    appearance = appearances[0]
                    submission = appearance.get("submitted_graphics")
                    command_range = ((int(submission["command_buffer_start"]),
                                      int(submission["command_buffer_end"]))
                                     if submission is not None else None)
                    selector = runtime_appearance_lookup.get(
                        (
                            appearance["draw_trace_sha256"],
                            int(submission["event_index"] if submission else appearance["event_index"]),
                        )
                    )
                    if selector is not None:
                        cache_key = (selector, command_range)
                        catalog = runtime_appearance_catalogs.get(cache_key)
                        if catalog is None:
                            catalog = load_runtime_material_catalog(
                                task_material_path, digest, selector, command_range=command_range
                            )
                            runtime_appearance_catalogs[cache_key] = catalog
                        runtime_material = catalog.get(source_key)
                        if runtime_material is not None:
                            task_local_runtime_material_run_count += 1
            else:
                runtime_material = runtime_material_catalog.get(source_key)
            if runtime_material is not None:
                runtime_materials[run_index] = runtime_material
                copy_runtime_captured_auxiliary_textures(runtime_material, output)
            texture = runtime_captured_texture_choice(runtime_material)
            if texture is not None:
                captured_status = runtime_material["variants"][0]["captured_texture"]["status"]
                status = (
                    f"task-local-{captured_status}"
                    if task_local
                    else captured_status
                )
            elif texture_root is not None:
                texture, status = choose_preview_texture(
                    run,
                    preview_texture_catalog,
                    flat_payloads,
                )
            else:
                texture, status = None, "texture-catalog-not-requested"
            if runtime_material_references_texels(runtime_material) is False:
                texture, status = None, "runtime-combiner-does-not-use-texture"
            if texture is not None and (
                not run.texture_enabled or not run.texture_coordinates_proven
            ):
                texture, status = None, "runtime-texture-observed-coordinate-state-unresolved"
            texture_status_counts[status] = texture_status_counts.get(status, 0) + 1
            if texture is None or not run.face_count:
                continue
            filename = copied_textures.get(texture)
            if filename is None:
                filename = preview_texture_filename(texture)
                destination = output / "textures" / filename
                destination.parent.mkdir(parents=True, exist_ok=True)
                if texture.png_data is not None:
                    destination.write_bytes(texture.png_data)
                else:
                    if texture.source is None:
                        raise ValueError("composition texture has no PNG source")
                    shutil.copyfile(texture.source, destination)
                copied_textures[texture] = filename
            relative_texture = f"../textures/{filename}"
            gltf_texture_files[run_index] = relative_texture
            material = material_name(run)
            previous = mtl_texture_files.get(material)
            if material in conflicting_mtl_materials:
                pass
            elif previous is None:
                mtl_texture_files[material] = relative_texture
            elif previous != relative_texture:
                mtl_texture_files.pop(material, None)
                conflicting_mtl_materials.add(material)
            linked_face_count += run.face_count
        return (
            gltf_texture_files,
            mtl_texture_files,
            runtime_materials,
            linked_face_count,
            task_local_runtime_material_run_count,
        )

    records = []
    for composition in (
        activity.get("character_compositions", [])
        + activity.get("render_texture_compositions", [])
    ):
        render_pass = composition.get("render_pass", {"kind": "caller-managed-target"})
        offscreen = render_pass["kind"] == "render-to-texture"
        clusters = composition.get("resolved_clusters", [])
        if not clusters:
            continue
        entry = int(composition["entry"])
        source_models = source_models_for(composition)
        geometry = merge_character_composition_geometry(source_models, clusters)
        source_face_count = len(geometry.faces)
        geometry, omitted_faces, _ = omit_zero_area_preview_faces(geometry)
        (
            gltf_texture_files,
            mtl_texture_files,
            runtime_materials,
            linked_face_count,
            _,
        ) = material_maps_for(geometry, clusters)
        geometry = apply_runtime_texture_coordinates(geometry, runtime_materials)
        base_bundle = bundle_by_entry[entry]
        _, base_layout = parse_character_model_geometry(base_bundle.segments[0].data)
        joints = tuple(base_layout["joints"])
        if not geometry_vertex_matrix_indices(geometry).issubset(
            {joint["matrix_index"] for joint in joints}
        ):
            raise ValueError("character composition exceeds its live joint hierarchy")
        stem = f"{entry:04d}-00"
        if offscreen:
            stem = f"render-texture-{stem}"
        gltf_stem = f"{stem}-composed"
        obj_data = encode_obj(entry, 0, geometry, 0x01)
        mtl_data = encode_mtl(
            entry,
            0,
            geometry,
            texture_files=mtl_texture_files,
            bank_index=0x01,
        )
        gltf_data, binary = encode_gltf(
            entry,
            0,
            geometry,
            bank_index=0x01,
            character_joints=joints,
            character_pose_source="trace-resolved-composition-neutral-bind-pose",
            output_stem=gltf_stem,
            texture_files=gltf_texture_files,
            runtime_materials=runtime_materials,
        )
        gltf = json.loads(gltf_data)
        gltf.setdefault("extras", {})["renderPass"] = render_pass
        gltf_data = (json.dumps(gltf, indent=2) + "\n").encode("utf-8")
        (geometry_dir / f"{stem}.obj").write_bytes(obj_data)
        (geometry_dir / f"{stem}.mtl").write_bytes(mtl_data)
        (geometry_dir / f"{gltf_stem}.gltf").write_bytes(gltf_data)
        (geometry_dir / f"{gltf_stem}.bin").write_bytes(binary)
        gltf = json.loads(gltf_data)
        if gltf["buffers"][0]["byteLength"] != len(binary):
            raise ValueError("character composition glTF buffer size changed")
        records.append(
            {
                "entry": entry,
                "render_pass": render_pass,
                "source_models": composition["sequence_source_models"],
                "source_cluster_count": len(clusters),
                "source_face_count": source_face_count,
                "face_count": len(geometry.faces),
                "omitted_zero_area_face_count": len(omitted_faces),
                "joint_count": len(joints),
                "linked_texture_run_count": len(gltf_texture_files),
                "linked_texture_face_count": linked_face_count,
                "model_sequence_status_counts": composition[
                    "model_sequence_status_counts"
                ],
                "object_file": f"geometry/{stem}.obj",
                "material_file": f"geometry/{stem}.mtl",
                "gltf_file": f"geometry/{gltf_stem}.gltf",
                "gltf_binary_file": f"geometry/{gltf_stem}.bin",
            }
        )
    posed_records = []
    skipped_pose_records = []
    for instance in (
        activity.get("character_composition_instances", [])
        + activity.get("render_texture_composition_instances", [])
    ):
        render_pass = instance.get("render_pass", {"kind": "caller-managed-target"})
        offscreen = render_pass["kind"] == "render-to-texture"
        clusters = instance.get("resolved_clusters", [])
        unresolved_calls = sum(
            count
            for status, count in instance.get(
                "model_sequence_status_counts", {}
            ).items()
            if status != "resolved"
        )
        if not clusters or unresolved_calls:
            skipped_pose_records.append(
                {
                    "render_pass": render_pass,
                    "state": instance["state"],
                    "task_submission_index": instance["task_submission_index"],
                    "slot": instance["slot"],
                    "entry": instance["entry"],
                    "reason": (
                        "no-resolved-clusters"
                        if not clusters
                        else "renderer-call-sequence-not-fully-resolved"
                    ),
                }
            )
            continue
        matrices = {
            int(matrix["matrix_slot"]): matrix
            for matrix in instance.get("runtime_matrices", [])
            if matrix.get("status") == "decoded-affine-components"
            and matrix.get("rows") is not None
        }
        entry = int(instance["entry"])
        source_models = source_models_for(instance)
        geometry = merge_character_composition_geometry(source_models, clusters)
        required_slots = sorted(geometry_vertex_matrix_indices(geometry))
        missing_slots = [slot for slot in required_slots if slot not in matrices]
        if missing_slots:
            skipped_pose_records.append(
                {
                    "render_pass": render_pass,
                    "state": instance["state"],
                    "task_submission_index": instance["task_submission_index"],
                    "slot": instance["slot"],
                    "entry": instance["entry"],
                    "reason": "missing-or-conflicting-runtime-matrices",
                    "required_matrix_slots": required_slots,
                    "missing_matrix_slots": missing_slots,
                }
            )
            continue
        source_face_count = len(geometry.faces)
        geometry, omitted_faces, _ = omit_zero_area_preview_faces(geometry)
        (
            gltf_texture_files,
            _,
            runtime_materials,
            linked_face_count,
            task_local_runtime_material_run_count,
        ) = material_maps_for(geometry, clusters, task_local=True)
        geometry = apply_runtime_texture_coordinates(geometry, runtime_materials)
        geometry = bake_character_runtime_pose(
            geometry,
            {slot: matrices[slot]["rows"] for slot in required_slots},
            matrices[0 if 0 in matrices else required_slots[0]]["translation"],
        )
        geometry, runtime_omitted_faces, _ = omit_zero_area_preview_faces(geometry)
        origin_matrix_slot = 0 if 0 in matrices else required_slots[0]
        state = instance["state"]
        task_index = int(instance["task_submission_index"])
        slot = int(instance["slot"])
        stem = f"{state}-task-{task_index:03d}-slot-{slot:02d}-entry-{entry:04d}"
        if offscreen:
            stem = f"render-texture-{stem}"
        gltf_data, binary = encode_gltf(
            entry,
            0,
            geometry,
            bank_index=0x01,
            character_pose_source="captured-runtime-matrix-palette-centered-on-slot-0",
            output_stem=stem,
            texture_files=gltf_texture_files,
            runtime_materials=runtime_materials,
        )
        gltf = json.loads(gltf_data)
        gltf.setdefault("extras", {})["renderPass"] = render_pass
        gltf_data = (json.dumps(gltf, indent=2) + "\n").encode("utf-8")
        (posed_dir / f"{stem}.gltf").write_bytes(gltf_data)
        (posed_dir / f"{stem}.bin").write_bytes(binary)
        gltf = json.loads(gltf_data)
        if gltf["buffers"][0]["byteLength"] != len(binary):
            raise ValueError("posed character composition glTF buffer size changed")
        posed_records.append(
            {
                "state": state,
                "render_pass": render_pass,
                "task_submission_index": task_index,
                "slot": slot,
                "entry": entry,
                "root_matrix_address": instance["root_matrix_address"],
                "transformed_normal_corner_count": sum(
                    normal is not None for face in geometry.face_preview_normals for normal in face
                ),
                "geometric_normal_fallback_corner_count": sum(
                    normal is None for face in geometry.face_preview_normals for normal in face
                ),
                "source_models": instance["sequence_source_models"],
                "source_cluster_count": len(clusters),
                "source_face_count": source_face_count,
                "face_count": len(geometry.faces),
                "omitted_zero_area_face_count": (
                    len(omitted_faces) + len(runtime_omitted_faces)
                ),
                "source_zero_area_face_count": len(omitted_faces),
                "runtime_pose_zero_area_face_count": len(runtime_omitted_faces),
                "required_matrix_slots": required_slots,
                "origin_matrix_slot": origin_matrix_slot,
                "linked_texture_run_count": len(gltf_texture_files),
                "linked_texture_face_count": linked_face_count,
                "task_local_runtime_material_run_count": (
                    task_local_runtime_material_run_count
                ),
                "gltf_file": f"posed/{stem}.gltf",
                "gltf_binary_file": f"posed/{stem}.bin",
            }
        )
    offscreen_records = [r for r in records if r["render_pass"]["kind"] == "render-to-texture"]
    offscreen_posed_records = [r for r in posed_records if r["render_pass"]["kind"] == "render-to-texture"]
    records = [r for r in records if r["render_pass"]["kind"] != "render-to-texture"]
    posed_records = [r for r in posed_records if r["render_pass"]["kind"] != "render-to-texture"]
    try:
        from scripts.model_attachment_runtime import attach_composition_previews
    except ModuleNotFoundError:
        from model_attachment_runtime import attach_composition_previews
    attachment_report = attach_composition_previews(
        profile, rom_argument, digest, attachment_trace_paths, activity, posed_records,
        output, task_material_path, copied_textures,
    )
    manifest = {
        "schema_version": 1,
        "family": "runtime-character-model-composition-preview",
        **attachment_report,
        "render_texture_model_count": len(offscreen_records),
        "render_texture_models": offscreen_records,
        "render_texture_posed_model_count": len(offscreen_posed_records),
        "render_texture_posed_models": offscreen_posed_records,
        "render_texture_source_face_count": sum(r["source_face_count"] for r in offscreen_records),
        "profile": profile,
        "normalized_sha1": digest,
        "flat_asset_identity": flat_asset_identity(flat_payloads),
        "source_activity_manifest": display_path(path),
        "aggregate_runtime_material_manifest": (
            display_path(
                runtime_material_path
                if runtime_material_path.is_absolute()
                else ROOT / runtime_material_path
            )
            if runtime_material_path is not None
            else None
        ),
        "task_runtime_material_manifest": (
            display_path(
                task_material_path
                if task_material_path.is_absolute()
                else ROOT / task_material_path
            )
            if task_material_path is not None
            else None
        ),
        "model_count": len(records),
        "source_cluster_count": sum(
            record["source_cluster_count"] for record in records
        ),
        "source_face_count": sum(record["source_face_count"] for record in records),
        "face_count": sum(record["face_count"] for record in records),
        "models": records,
        "posed_model_count": len(posed_records),
        "posed_models": posed_records,
        "skipped_pose_count": len(skipped_pose_records),
        "skipped_poses": skipped_pose_records,
        "copied_texture_count": len(copied_textures),
        "texture_status_counts": dict(sorted(texture_status_counts.items())),
        "neutral_linked_texture_run_count": sum(
            record["linked_texture_run_count"] for record in records
        ),
        "neutral_linked_texture_face_count": sum(
            record["linked_texture_face_count"] for record in records
        ),
        "posed_linked_texture_run_count": sum(
            record["linked_texture_run_count"] for record in posed_records
        ),
        "posed_linked_texture_face_count": sum(
            record["linked_texture_face_count"] for record in posed_records
        ),
        "posed_task_local_runtime_material_run_count": sum(
            record["task_local_runtime_material_run_count"]
            for record in posed_records
        ),
        "runtime_matrix_state": CHARACTER_RUNTIME_MATRIX_STATE,
        "vertex_transform_assignment": "matrix-at-each-cached-vertex-load",
        "display_list_material_scope": "independently-callable-pointer-table-entry",
        "limitations": [
            "only exact source-model and monotonic static-cluster resolutions are exported",
            "aggregate previews use the live entry's neutral bind hierarchy",
            "posed previews require a fully resolved task-local call sequence and every referenced runtime matrix",
            "posed previews are centered on matrix slot 0 when captured, otherwise the lowest required slot, while retaining runtime orientation and scale",
            "posed vertex positions follow the proven row-vector float-palette to split-fixed RSP conversion chain; normals and exact N64 raster output remain diagnostic",
            "posed preview materials use the proven submitted graphics range when available, otherwise the exact renderer-return event; absent body correlations fall back to proven static textures",
            "attachments require matching parent identity, submitted commands and matrices; unobserved attachments are not inferred from a character name or neutral bone pose",
            "attachment captures preserve runtime UV, colour and normal attributes, but changed source XYZ requires additional deformation evidence",
            "separately callable lists do not inherit static material state from their stored neighbors; missing texture or coordinate state leaves diagnostic plain surfaces",
            "unobserved character entries require additional runtime states",
        ],
    }
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    return manifest


def load_character_activity_manifest(
    path: Path | None,
    expected_digest: str,
) -> tuple[dict[str, Any] | None, dict[str, set[int]]]:
    """Load per-state active bank-01 entries for conservative correlation."""

    if path is None:
        return None, {}
    source = path if path.is_absolute() else ROOT / path
    data = source.read_bytes()
    manifest = json.loads(data)
    if (
        manifest.get("schema_version") != 1
        or manifest.get("family") != "runtime-character-model-activity"
    ):
        raise ValueError("character activity manifest has an unsupported schema")
    if manifest.get("normalized_sha1") != expected_digest:
        raise ValueError("character activity manifest belongs to a different ROM")
    state_entries: dict[str, set[int]] = {}
    for trace in manifest.get("source_traces", []):
        state = trace.get("state")
        snapshots = trace.get("snapshots")
        if not isinstance(state, str) or not state or not isinstance(snapshots, list):
            raise ValueError("character activity manifest trace identity changed")
        entries = state_entries.setdefault(state, set())
        for snapshot in snapshots:
            active_entries = snapshot.get("active_entries")
            if not isinstance(active_entries, list) or any(
                not isinstance(entry, int) or entry < 0 for entry in active_entries
            ):
                raise ValueError("character activity manifest entries changed")
            entries.update(active_entries)
    if set(manifest.get("active_entries", [])) != {
        entry for entries in state_entries.values() for entry in entries
    }:
        raise ValueError("character activity manifest summary changed")
    return (
        {
            "file": display_path(source),
            "sha256": hashlib.sha256(data).hexdigest(),
            "state_count": len(state_entries),
            "active_entry_count": len(
                {entry for entries in state_entries.values() for entry in entries}
            ),
        },
        state_entries,
    )


def runtime_material_candidate_key(
    candidate: dict[str, Any],
    inventory: dict[tuple[int, int, int, int], dict[str, Any]],
) -> tuple[int, int, int, int]:
    """Validate one static material candidate and return its stable identity."""

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
    if candidate_sha1 is not None and candidate_sha1 != current["model_sha1"]:
        raise ValueError(f"runtime material model hash changed: {key}")
    if any(
        material.get(field) != current[field]
        for field in ("first_face", "face_count", "matrix_index")
    ):
        raise ValueError(f"runtime material run boundary changed: {key}")
    return key


def refine_character_material_candidates(
    candidates: list[dict[str, Any]],
    draw: dict[str, Any],
    active_entries: set[int] | None,
    inventory: dict[tuple[int, int, int, int], dict[str, Any]],
) -> set[tuple[int, int, int, int]]:
    """Resolve one ambiguous draw only with active-entry and matrix evidence."""

    if active_entries is None:
        return set()
    validated = [
        (candidate, runtime_material_candidate_key(candidate, inventory))
        for candidate in candidates
    ]
    active_bank_1 = [
        (candidate, key)
        for candidate, key in validated
        if key[0] == 1 and key[1] in active_entries
    ]
    if not active_bank_1:
        return set()
    matrix = draw.get("state", {}).get("matrix") or {}
    matrix_slot = matrix.get("matrix_slot")
    if matrix_slot is None:
        # The character pool cannot disprove object/level candidates. Without an
        # exact matrix slot, active-entry evidence is sufficient only when every
        # original candidate is already a character-bank candidate.
        if any(key[0] != 1 for _, key in validated):
            return set()
        filtered = active_bank_1
    else:
        filtered = [
            (candidate, key)
            for candidate, key in active_bank_1
            if candidate.get("material_run", {}).get("matrix_index")
            == int(matrix_slot)
        ]
    keys = {key for _, key in filtered}
    return keys if len(keys) == 1 else set()


def refine_captured_material_candidate(
    correlation: dict[str, Any], geometry_correlation: dict[str, Any],
    draws: list[dict[str, Any]], loads: list[dict[str, Any]],
    sources: list[tuple[int, bytes, str]],
    inventory: dict[tuple[int, int, int, int], dict[str, Any]],
) -> tuple[tuple[int, int, int, int], int] | None:
    """Resolve an ambiguous command cluster only with one exact vertex match."""

    if not sources or not correlation.get("draw_run_indices"):
        return None
    matches = set()
    for candidate in geometry_correlation.get("candidates", []):
        key = runtime_material_candidate_key(candidate, inventory)
        geometry = inventory[key].get("_geometry")
        first = candidate.get("static_first_face")
        if geometry is None or not isinstance(first, int):
            continue
        offset = 0
        for draw_index in correlation["draw_run_indices"]:
            draw = draws[int(draw_index)]
            if captured_draw_vertices(draw, loads, sources, geometry, first + offset) is None:
                break
            offset += int(draw["triangle_count"])
        else:
            matches.add((key, first))
    # Identical geometry in several models or source spans remains ambiguous.
    return next(iter(matches)) if len(matches) == 1 else None


def selected_part_material_candidates(
    trace: dict[str, Any],
    inventory: dict[tuple[int, int, int, int], dict[str, Any]],
) -> dict[int, dict[int, dict[str, Any]]]:
    """Join validated part sequences to returns and byte-verified submissions."""

    result = {}
    for call in trace.get("draw_calls", []):
        sequence = resolve_character_call_from_part_selections(call.get("part_selections", []))
        if sequence is None:
            continue
        correlations = call.get("model_correlations", [])
        clusters = sequence["resolved_clusters"]
        if len(correlations) != len(clusters):
            raise ValueError("selected part sequence does not cover the renderer command range")
        selected = {}
        for correlation, cluster in zip(correlations, clusters):
            matches = [candidate for candidate in correlation.get("candidates", [])
                       if all(candidate.get(key) == value for key, value in sequence["source_model"].items())
                       and candidate.get("static_cluster_index") == cluster["static_cluster_index"]
                       and candidate.get("static_first_face") == cluster["first_face"]
                       and candidate.get("triangle_count") == cluster["face_count"]
                       and (candidate.get("material_run") or {}).get("index") == cluster["material_run"]]
            if len(matches) != 1:
                raise ValueError("selected part cluster has no exact renderer correlation")
            candidate = matches[0]
            runtime_material_candidate_key(candidate, inventory)
            index = correlation["runtime_cluster_index"]
            if index in selected:
                raise ValueError("selected part runtime cluster identity is duplicated")
            selected[index] = {"candidate": candidate, "evidence": {
                "command_sha256": call["command_sha256"],
                "return_event_index": call["return_event_index"],
                "static_cluster_index": cluster["static_cluster_index"],
                "part_selection_event_indices": [part["event_index"] for part in call["part_selections"]],
            }}
        if call["return_event_index"] in result:
            raise ValueError("selected part renderer return identity is duplicated")
        result[call["return_event_index"]] = selected
        submission = call.get('submitted_graphics', {})
        mapping = submission.get('cluster_correspondence')
        if mapping is None:
            continue
        normalized_mapping = {int(index): value for index, value in mapping.items()}
        if len(normalized_mapping) != len(mapping):
            raise ValueError('selected part submission cluster mapping repeats an index')
        mapping = normalized_mapping
        if (submission.get('status') != 'captured-range-executed-once-in-next-graphics-task'
                or set(mapping) != set(selected) or len(set(mapping.values())) != len(mapping)):
            raise ValueError('selected part submission cluster mapping is incomplete or duplicated')
        submitted = result.setdefault(submission['event_index'], {})
        for old_index, new_index in mapping.items():
            if new_index in submitted:
                raise ValueError('selected part submitted cluster identity is duplicated')
            record = selected[old_index]
            submitted[new_index] = {'candidate': record['candidate'], 'evidence': {
                **record['evidence'], 'submitted_event_index': submission['event_index'],
                'submitted_command_buffer_start': submission['command_buffer_start'],
                'submitted_command_buffer_end': submission['command_buffer_end'],
                'submission_status': submission['status'],
            }}
    return result


def extract_runtime_materials(
    profile: str,
    rom_argument: Path | None,
    trace_paths: tuple[Path, ...],
    output: Path,
    force: bool,
    activity_manifest_path: Path | None = None,
) -> dict[str, Any]:
    """Aggregate correlated draw states into reusable static material variants."""

    if not trace_paths:
        raise ValueError("at least one --trace JSONL file is required")
    digest, inventory = runtime_material_inventory(profile, rom_argument)
    activity_source, activity_by_state = load_character_activity_manifest(
        activity_manifest_path, digest
    )
    if output.exists():
        if not force:
            raise ValueError(
                f"output already exists: {display_path(output)}; "
                "pass --force to replace it"
            )
        if not output.is_dir():
            raise ValueError(
                f"refusing to replace non-directory output: {display_path(output)}"
            )
    records: dict[tuple[int, int, int, int], dict[str, Any]] = {}
    trace_records = []
    correlation_count = 0
    correlated_draw_observation_count = 0
    assignment_observation_count = 0
    activity_refined_correlation_count = 0
    activity_refined_draw_observation_count = 0
    activity_refined_assignment_observation_count = 0
    vertex_refined_correlation_count = 0
    vertex_refined_draw_observation_count = 0
    vertex_unproven_assignment_count = 0
    selected_part_correlation_count = 0
    selected_part_draw_observation_count = 0
    character_topology = None
    nested_display_list_call_count = 0
    resolved_display_list_call_count = 0
    unresolved_display_list_call_count = 0
    segment_8_display_list_call_count = 0
    resolved_segment_8_display_list_call_count = 0
    resolved_segment_8_display_list_addresses: set[int] = set()
    runtime_segment_8_resolution_status_counts: dict[str, int] = {}
    runtime_segment_8_payload_hashes: set[str] = set()
    runtime_segment_8_effective_payload_hashes: set[str] = set()
    appearance_records: dict[tuple[int, int], dict[str, Any]] = {}
    captured_texture_pngs: dict[str, bytes] = {}
    model_cluster_index = None
    refreshed_correlation_event_count = 0
    for trace_index, source_path in enumerate(trace_paths):
        path = source_path if source_path.is_absolute() else ROOT / source_path
        active_entries = activity_by_state.get(path.stem)
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
        graphics_events = [event for event in events if captured_task_type(event) in (None, 1)]
        for event in graphics_events:
            if any(probe.get("name") in {"character-command-buffer", "command-buffer"}
                   for probe in event.get("evidence", {}).get("memory", [])):
                if model_cluster_index is None:
                    model_cluster_index = load_model_cluster_index()
                refreshed_correlation_event_count += refresh_trace_model_correlations(
                    event, model_cluster_index
                )
        part_candidates = {}
        if lines[0].get("spec_name") == "character-model-draw-ranges":
            if character_topology is None:
                _, _, character_digest, character_bundles, _ = load_model_bundles(profile, rom_argument, 1)
                if character_digest != digest:
                    raise ValueError("selected part topology belongs to a different ROM")
                character_topology = character_display_list_topology(character_bundles)
            validated_trace = load_character_draw_trace(
                path, digest, {key[1] for key in inventory if key[0] == 1},
                character_topology, model_cluster_index,
            )
            part_candidates = selected_part_material_candidates(validated_trace, inventory)
        trace_nested_calls = [
            call
            for event in graphics_events
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
            for event in graphics_events
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
                "trace_index": trace_index,
                "file": display_path(path),
                "sha256": hashlib.sha256(data).hexdigest(),
                "spec_name": lines[0].get("spec_name"),
                "normalized_sha1": trace_digest,
                "tool_revisions": lines[0].get("tool_revisions"),
                "event_count": len(events),
                "ignored_non_graphics_task_count": len(events) - len(graphics_events),
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
            if captured_task_type(event) not in (None, 1):
                continue
            backfill_runtime_convert_modes(event)
            event_state = event.get("state", {})
            rdp = event_state.get("rdp", {})
            matrices = event_state.get("joint_matrices", [])
            draw_runs = rdp.get("draw_runs", [])
            vertex_sources = captured_vertex_sources(event)
            vertex_loads = rdp.get("replayed_vertex_loads", [])
            geometry_correlations = {
                item["runtime_cluster_index"]: item
                for item in rdp.get("model_correlations", [])
            }
            nested_payloads_by_address = {
                int(item["resolved_address"], 0): item
                for item in event.get("evidence", {}).get("memory", [])
                if item.get("name", "").startswith("nested-display-list-")
                and isinstance(item.get("resolved_address"), str)
            }
            texture_payloads = {
                int(item["name"].rsplit("-", 1)[1]): base64.b64decode(
                    item["data_base64"]
                )
                for item in event.get("evidence", {}).get("memory", [])
                if item.get("name", "").startswith("runtime-texture-image-")
            }
            for correlation_index, correlation in enumerate(
                rdp.get("material_run_correlations", [])
            ):
                correlation_status = correlation.get("status")
                if correlation_status not in (
                    "unique",
                    "equivalent-material-aliases",
                    "ambiguous",
                ):
                    continue
                draw_indices = correlation.get("draw_run_indices", [])
                selected_part = part_candidates.get(event_index, {}).get(correlation.get("runtime_cluster_index"))
                part_candidate = selected_part["candidate"] if selected_part is not None else None
                if part_candidate is not None:
                    geometry_correlation = geometry_correlations.get(correlation.get("runtime_cluster_index"), {})
                    if part_candidate not in geometry_correlation.get("candidates", []):
                        raise ValueError("selected part geometry changed during material replay")
                    part_key = runtime_material_candidate_key(part_candidate, inventory)
                    if part_key not in {runtime_material_candidate_key(c, inventory) for c in correlation.get("candidates", [])}:
                        raise ValueError("selected part material is absent from its draw correlation")
                    selected_part_correlation_count += 1
                vertex_candidate = (
                    refine_captured_material_candidate(
                        correlation,
                        geometry_correlations.get(correlation.get("runtime_cluster_index"), {}),
                        draw_runs, vertex_loads, vertex_sources, inventory,
                    )
                    if correlation_status == "ambiguous" and part_candidate is None else None
                )
                vertex_refined_correlation_count += vertex_candidate is not None
                accepted_draw_count = 0
                for draw_position, draw_index in enumerate(draw_indices):
                    if not 0 <= int(draw_index) < len(draw_runs):
                        raise ValueError("runtime material draw index is out of range")
                    draw = draw_runs[int(draw_index)]
                    if part_candidate is not None:
                        candidate_keys = {part_key}
                        evidence_status = "renderer-selected-part-sequence"
                    elif correlation_status in (
                        "unique",
                        "equivalent-material-aliases",
                    ):
                        candidate_keys = {
                            runtime_material_candidate_key(candidate, inventory)
                            for candidate in correlation.get("candidates", [])
                        }
                        evidence_status = correlation_status
                    elif vertex_candidate is not None:
                        candidate_keys = {vertex_candidate[0]}
                        evidence_status = "captured-vertex-bytes-and-command-cluster"
                        vertex_refined_draw_observation_count += 1
                    else:
                        candidate_keys = refine_character_material_candidates(
                            correlation.get("candidates", []),
                            draw,
                            active_entries,
                            inventory,
                        )
                        if not candidate_keys:
                            continue
                        evidence_status = "runtime-active-character-matrix"
                        activity_refined_draw_observation_count += 1
                        activity_refined_assignment_observation_count += len(
                            candidate_keys
                        )
                    verified_first_faces = {}
                    if vertex_sources:
                        # A unique triangle pattern can still be coincidental.
                        # Captured coordinates must support each assignment,
                        # including unique and equivalent command candidates.
                        draw_face_offset = sum(int(draw_runs[int(i)]["triangle_count"])
                                               for i in draw_indices[:draw_position])
                        for key in candidate_keys:
                            first_faces = {
                                int(candidate["static_first_face"]) + draw_face_offset
                                for candidate in geometry_correlations.get(
                                    correlation.get("runtime_cluster_index"), {}
                                ).get("candidates", [])
                                if "static_first_face" in candidate
                                and runtime_material_candidate_key(candidate, inventory) == key
                            }
                            if part_candidate is not None:
                                first_faces = {part_candidate["static_first_face"] + draw_face_offset}
                            elif vertex_candidate is not None:
                                first_faces = {vertex_candidate[1] + draw_face_offset}
                            geometry = inventory[key].get("_geometry")
                            matching = [first for first in first_faces if geometry is not None
                                        and captured_draw_vertices(draw, vertex_loads, vertex_sources,
                                                                   geometry, first) is not None]
                            if len(matching) == 1:
                                verified_first_faces[key] = matching[0]
                            else:
                                vertex_unproven_assignment_count += 1
                        candidate_keys = set(verified_first_faces)
                        if not candidate_keys:
                            continue
                        evidence_status = "captured-vertex-bytes-and-command-cluster"
                    accepted_draw_count += 1
                    if part_candidate is not None:
                        selected_part_draw_observation_count += 1
                    source_state = dict(draw.get("state", {}))
                    if "replayed_tile_bounds" in draw:
                        source_state["tile_bounds"] = draw["replayed_tile_bounds"]
                    texture_state = copy.deepcopy(source_state.get("texture"))
                    if isinstance(texture_state, dict):
                        for image_name in ("pixel_image", "palette_image"):
                            image = texture_state.get(image_name)
                            if isinstance(image, dict):
                                image.pop("captured_texture_image_index", None)
                    material_state = {
                        "texture": texture_state,
                        "tiles": source_state.get("tiles"),
                        "tile_bounds": source_state.get("tile_bounds", {}),
                        "combine_mode": source_state.get("combine_mode"),
                        "convert_mode": source_state.get("convert_mode"),
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
                        captured_texture = runtime_captured_preview_texture(
                            current.get("_run"),
                            source_state,
                            texture_payloads,
                        )
                        if captured_texture is not None:
                            for level in [
                                captured_texture,
                                *runtime_captured_auxiliary_textures(
                                    captured_texture
                                ),
                            ]:
                                captured_texture_pngs.setdefault(
                                    level["file"], level.pop("png_data")
                                )
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
                                "captured_texture": captured_texture,
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
                            "trace_index": trace_index,
                            "event_index": event_index,
                            "hit_index": event.get("hit_index"),
                            "event_render_state_hash": event.get("render_state_hash"),
                            "material_correlation_index": correlation_index,
                            "material_correlation_status": evidence_status,
                            "draw_run_index": int(draw_index),
                            "source_material_state_hash": draw.get(
                                "material_state_hash"
                            ),
                            "lighting_context_hash": (
                                lighting_context["lighting_context_hash"]
                                if lighting_context is not None
                                else None
                            ),
                        }
                        origins = rdp.get("replayed_command_origins", [])
                        command_index = int(draw.get("command_offset", -8)) // 8
                        if 0 <= command_index < len(origins):
                            evidence["command_path"] = origins[command_index]
                        if "replayed_face_culling" in draw:
                            evidence["face_culling"] = draw["replayed_face_culling"]
                        if selected_part is not None:
                            evidence["renderer_part_sequence"] = selected_part["evidence"]
                        source_faces = {
                            int(candidate["static_first_face"]) + sum(
                                int(draw_runs[int(i)]["triangle_count"])
                                for i in draw_indices[:draw_position]
                            )
                            for candidate in geometry_correlations.get(
                                correlation.get("runtime_cluster_index"), {}
                            ).get("candidates", [])
                            if "static_first_face" in candidate
                            and runtime_material_candidate_key(candidate, inventory) == key
                        }
                        if vertex_candidate is not None:
                            source_faces = {vertex_candidate[1] + sum(
                                int(draw_runs[int(i)]["triangle_count"])
                                for i in draw_indices[:draw_position]
                            )}
                        if part_candidate is not None:
                            source_faces = {part_candidate["static_first_face"] + sum(
                                int(draw_runs[int(i)]["triangle_count"])
                                for i in draw_indices[:draw_position]
                            )}
                        if key in verified_first_faces:
                            source_faces = {verified_first_faces[key]}
                        if len(source_faces) == 1:
                            first_face = next(iter(source_faces))
                            count = int(draw["triangle_count"])
                            if not current["first_face"] <= first_face < first_face + count <= current["first_face"] + current["face_count"]:
                                raise ValueError("runtime draw exceeds its source material face range")
                            evidence["source_first_face"] = first_face
                            evidence["source_face_count"] = count
                            if vertex_sources and "_geometry" in current:
                                sample = replay_draw_vertex_colours(
                                    draw, vertex_loads, vertex_sources, current["_geometry"], first_face
                                )
                                if sample is not None:
                                    evidence["vertex_lighting"] = sample
                        segment_8_resolution = runtime_segment_8_resolution(
                            current.get("_run"),
                            source_state,
                            rdp.get("nested_display_lists", []),
                            nested_payloads_by_address,
                        )
                        if segment_8_resolution is not None:
                            evidence["runtime_segment_8_resolution"] = (
                                segment_8_resolution
                            )
                            resolution_status = segment_8_resolution["status"]
                            runtime_segment_8_resolution_status_counts[
                                resolution_status
                            ] = (
                                runtime_segment_8_resolution_status_counts.get(
                                    resolution_status, 0
                                )
                                + 1
                            )
                            payload_hash = segment_8_resolution.get(
                                "payload_sha256"
                            )
                            if isinstance(payload_hash, str):
                                runtime_segment_8_payload_hashes.add(payload_hash)
                                if resolution_status == (
                                    "exact-runtime-list-effective-state"
                                ):
                                    runtime_segment_8_effective_payload_hashes.add(
                                        payload_hash
                                    )
                        if evidence not in variant["evidence"]:
                            variant["evidence"].append(evidence)
                        appearance = appearance_records.setdefault(
                            (trace_index, event_index),
                            {
                                "id": f"trace-{trace_index:03d}-event-{event_index:03d}",
                                "trace_index": trace_index,
                                "trace": display_path(path),
                                "event_index": event_index,
                                "hit_index": event.get("hit_index"),
                                "event_render_state_hash": event.get(
                                    "render_state_hash"
                                ),
                                "material_assignment_observation_count": 0,
                                "material_keys": set(),
                                "variant_keys": set(),
                                "bank_entries": {},
                            },
                        )
                        appearance["material_assignment_observation_count"] += 1
                        appearance["material_keys"].add(key)
                        appearance["variant_keys"].add((*key, material_hash))
                        appearance["bank_entries"].setdefault(key[0], set()).add(
                            key[1]
                        )
                if accepted_draw_count:
                    correlation_count += 1
                    correlated_draw_observation_count += accepted_draw_count
                    if correlation_status == "ambiguous" and vertex_candidate is None:
                        activity_refined_correlation_count += 1
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
    appearances = []
    for key in sorted(appearance_records):
        appearance = appearance_records[key]
        appearances.append(
            {
                **{
                    field: value
                    for field, value in appearance.items()
                    if field not in ("material_keys", "variant_keys", "bank_entries")
                },
                "material_record_count": len(appearance["material_keys"]),
                "variant_count": len(appearance["variant_keys"]),
                "bank_entries": [
                    {
                        "bank": bank,
                        "entries": sorted(entries),
                    }
                    for bank, entries in sorted(appearance["bank_entries"].items())
                ],
            }
        )
    manifest = {
        "schema_version": 1,
        "family": "runtime-correlated-model-materials",
        "profile": profile,
        "normalized_sha1": digest,
        "source_traces": trace_records,
        "trace_file_count": len(trace_records),
        "refreshed_correlation_event_count": refreshed_correlation_event_count,
        "correlation_basis": "hash-checked-captured-commands-current-vertex-cache-clusters",
        "appearances": appearances,
        "appearance_count": len(appearances),
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
        "runtime_segment_8_material_assignment_observation_count": sum(
            runtime_segment_8_resolution_status_counts.values()
        ),
        "runtime_segment_8_resolution_status_counts": dict(
            sorted(runtime_segment_8_resolution_status_counts.items())
        ),
        "runtime_segment_8_payload_count": len(
            runtime_segment_8_payload_hashes
        ),
        "runtime_segment_8_payload_sha256": sorted(
            runtime_segment_8_payload_hashes
        ),
        "runtime_segment_8_effective_payload_count": len(
            runtime_segment_8_effective_payload_hashes
        ),
        "runtime_segment_8_effective_payload_sha256": sorted(
            runtime_segment_8_effective_payload_hashes
        ),
        "correlation_count": correlation_count,
        "correlated_draw_observation_count": correlated_draw_observation_count,
        "material_assignment_observation_count": assignment_observation_count,
        "character_activity_manifest": activity_source,
        "vertex_refined_correlation_count": vertex_refined_correlation_count,
        "vertex_refined_draw_observation_count": vertex_refined_draw_observation_count,
        "vertex_unproven_assignment_count": vertex_unproven_assignment_count,
        "activity_refined_correlation_count": activity_refined_correlation_count,
        "activity_refined_draw_observation_count": (
            activity_refined_draw_observation_count
        ),
        "activity_refined_assignment_observation_count": (
            activity_refined_assignment_observation_count
        ),
        "material_record_count": len(material_records),
        "variant_count": sum(record["variant_count"] for record in material_records),
        "lighting_context_count": sum(
            variant["lighting_context_count"]
            for record in material_records
            for variant in record["variants"]
        ),
        "convert_mode_variant_count": sum(
            variant["state"].get("convert_mode") is not None
            for record in material_records
            for variant in record["variants"]
        ),
        "missing_convert_mode_variant_count": sum(
            variant["state"].get("convert_mode") is None
            for record in material_records
            for variant in record["variants"]
        ),
        "convert_mode_count": len(
            {
                tuple(variant["state"]["convert_mode"])
                for record in material_records
                for variant in record["variants"]
                if variant["state"].get("convert_mode") is not None
            }
        ),
        "captured_mip_variant_count": sum(
            bool(runtime_captured_mip_levels(variant.get("captured_texture") or {}))
            for record in material_records
            for variant in record["variants"]
        ),
        "captured_mip_level_count": sum(
            len(runtime_captured_mip_levels(variant.get("captured_texture") or {}))
            for record in material_records
            for variant in record["variants"]
        ),
        "captured_mip_png_count": len(
            {
                level["file"]
                for record in material_records
                for variant in record["variants"]
                for level in runtime_captured_mip_levels(
                    variant.get("captured_texture") or {}
                )
            }
        ),
        "captured_multitexture_variant_count": sum(
            isinstance(
                (variant.get("captured_texture") or {}).get("texture1_image"),
                dict,
            )
            for record in material_records
            for variant in record["variants"]
        ),
        "captured_multitexture_png_count": len(
            {
                texture1["file"]
                for record in material_records
                for variant in record["variants"]
                if isinstance(
                    (texture1 := (variant.get("captured_texture") or {}).get(
                        "texture1_image"
                    )),
                    dict,
                )
            }
        ),
        "gltf_translation_status_counts": dict(sorted(status_counts.items())),
        "limitations": [
            "runtime correlations cover only models visible in the supplied traces",
            "character-pool refinement promotes only a unique active bank-01 material identity with compatible matrix evidence",
            "equivalent model payload aliases retain every candidate identity",
            "RDP coverage and blender state are approximated by glTF alpha modes",
            "explicit TEXEL0/TEXEL1 LOD blending remains metadata-only",
            "draws before a task-local SetConvert retain an unresolved inherited conversion state",
            "captured CBFD lights and model-view matrices are retained per material variant for deterministic vertex-lighting replay",
        ],
        "materials": material_records,
    }
    if selected_part_correlation_count:
        manifest["renderer_part_sequence_correlation_count"] = selected_part_correlation_count
        manifest["renderer_part_sequence_draw_observation_count"] = selected_part_draw_observation_count
    prepare_output(output, force)
    for relative, data in sorted(captured_texture_pngs.items()):
        destination = output / relative
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes(data)
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    verify_runtime_material_output(output, manifest)
    return manifest


def load_runtime_material_catalog(
    path: Path | None,
    expected_digest: str,
    appearance: tuple[int, int] | None = None,
    *,
    command_range: tuple[int, int] | None = None,
    draw_indices: set[int] | None = None,
) -> dict[tuple[int, int, int, int], dict[str, Any]]:
    if path is None:
        return {}
    if draw_indices is not None and (appearance is None or not draw_indices
                                     or any(not isinstance(i, int) or i < 0 for i in draw_indices)):
        raise ValueError("runtime draw selection requires an appearance and nonnegative indices")
    if command_range is not None and (appearance is None or len(command_range) != 2
                                     or not command_range[0] < command_range[1]
                                     or any(address & 7 for address in command_range)):
        raise ValueError("runtime command range requires an appearance and aligned bounds")
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
        if appearance is None:
            record = copy.deepcopy(record)
            record["_source_root"] = source.parent
            catalog[key] = record
            continue
        selected = copy.deepcopy(record)
        selected_variants = []
        for variant in selected.get("variants", []):
            evidence = [
                item
                for item in variant.get("evidence", [])
                if (
                    int(item.get("trace_index", -1)),
                    int(item.get("event_index", -1)),
                )
                == appearance
                and (draw_indices is None or item.get("draw_run_index") in draw_indices)
                and (command_range is None or any(
                    command_range[0] <= address < command_range[1]
                    for address in item.get("command_path", [])
                ))
            ]
            if not evidence:
                continue
            context_hashes = {
                item.get("lighting_context_hash")
                for item in evidence
                if item.get("lighting_context_hash") is not None
            }
            context_observations = {
                context_hash: sum(
                    item.get("lighting_context_hash") == context_hash
                    for item in evidence
                )
                for context_hash in context_hashes
            }
            variant["evidence"] = evidence
            variant["observation_count"] = len(evidence)
            variant["lighting_contexts"] = [
                {
                    **context,
                    "observation_count": context_observations[
                        context["lighting_context_hash"]
                    ],
                }
                for context in variant.get("lighting_contexts", [])
                if context.get("lighting_context_hash") in context_hashes
            ]
            variant["lighting_context_count"] = len(variant["lighting_contexts"])
            selected_variants.append(variant)
        if selected_variants:
            selected["variants"] = selected_variants
            selected["variant_count"] = len(selected_variants)
            selected["observation_count"] = sum(
                variant["observation_count"] for variant in selected_variants
            )
            selected["_source_root"] = source.parent
            catalog[key] = selected
    if len(catalog) != manifest.get("material_record_count"):
        if appearance is None:
            raise ValueError("runtime material manifest count changed")
        available = {
            (int(item["trace_index"]), int(item["event_index"]))
            for item in manifest.get("appearances", [])
        }
        if appearance not in available:
            raise ValueError(
                "runtime material appearance is absent: "
                f"{appearance[0]}:{appearance[1]}"
            )
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
    exact_statuses = {
        "exact-texture-times-vertex-color",
        "exact-vertex-color-times-factor",
        "exact-runtime-color-times-texture-alpha",
        "exact-texture-without-vertex-color",
    }
    base_color_factor = unanimous("baseColorFactor")
    exact = (
        all(status in exact_statuses for status in statuses)
        and base_color_factor is not None
    )
    return {
        "variantCount": len(variants),
        "observationCount": record.get("observation_count"),
        "statuses": statuses,
        "alphaMode": unanimous("alphaMode"),
        "sampler": unanimous("sampler"),
        "baseColorFactor": base_color_factor,
        "usesVertexColor": unanimous("usesVertexColor"),
        "referencesTexels": runtime_material_references_texels(record),
        "vertexAlphaMode": unanimous("vertexAlphaMode"),
        "exact": exact,
    }


def runtime_material_references_texels(record: dict[str, Any] | None) -> bool | None:
    """Prove texture absence independently of unresolved lighting or constants.

    Inspect both cycles conservatively. A reference in an inactive or algebraically
    cancelled term keeps the texture eligible; missing state never proves absence.
    A loaded image alone does not mean the combiner samples it.
    """

    variants = record.get("variants", []) if record is not None else []
    if not variants:
        return None
    referenced = False
    for variant in variants:
        state = variant.get("state", {})
        other = decode_other_mode(state.get("other_mode"))
        if other is None or other["cycle_type"] == "fill":
            return None
        if other["cycle_type"] == "copy":
            referenced = True
            continue
        pair = state.get("combine_mode")
        if not isinstance(pair, (list, tuple)) or len(pair) != 2:
            return None
        formula = decode_combine_mode(tuple(pair))
        if formula is None:
            return None
        referenced |= bool({"TEXEL0", "TEXEL1"}.intersection(formula["inputs"]))
    return referenced


def runtime_captured_texture_choice(
    record: dict[str, Any] | None,
) -> PreviewTexture | None:
    """Return one task-local captured texture only when selection is unambiguous."""

    if (record is None or len(record.get("variants", [])) != 1
            or runtime_material_references_texels(record) is False):
        return None
    captured = record["variants"][0].get("captured_texture")
    source_root = record.get("_source_root")
    if not isinstance(captured, dict) or not isinstance(source_root, Path):
        return None
    source = _validated_preview_source(source_root, captured["file"])
    if hashlib.sha1(source.read_bytes()).hexdigest() != captured["png_sha1"]:
        raise ValueError("runtime captured texture PNG hash changed")
    format_id, size_id = {
        "ci4": (2, 0), "ci8": (2, 1), "i4": (4, 0),
        "i8": (4, 1), "ia4": (3, 0), "ia8": (3, 1), "ia16": (3, 2), "rgba32": (0, 3),
    }[captured["format"]]
    return PreviewTexture(
        family="us-runtime-captured",
        source=source,
        flat_index=0,
        format=format_id,
        size=size_id,
        width=int(captured["width"]),
        height=int(captured["height"]),
        sha1=captured["png_sha1"],
    )


def apply_runtime_texture_coordinates(
    geometry: ModelGeometry, runtime_materials: dict[int, dict[str, Any]]
) -> ModelGeometry:
    """Keep captured image dimensions, tile origins and exported UVs together."""

    runs = list(geometry.material_runs)
    for index, record in runtime_materials.items():
        variants = record.get("variants", [])
        if len(variants) != 1:
            continue
        captured = variants[0].get("captured_texture") or {}
        coordinates = captured.get("coordinate_state")
        if coordinates is None:
            continue
        run = replace(
            runs[index],
            render_tile=tuple(coordinates["render_tile"]),
            tile_bounds=tuple(coordinates["tile_bounds"]) if coordinates["tile_bounds"] else None,
            texture_scale=tuple(coordinates["texture_scale"]),
            texture_dimensions=tuple(coordinates["texture_dimensions"]) if coordinates.get("texture_dimensions") else None,
        )
        state = texture_coordinate_state(run)
        if state is None or (state["width"], state["height"]) != (
            captured["width"], captured["height"]
        ):
            raise ValueError("captured texture dimensions disagree with its coordinate state")
        runs[index] = run
    return replace(geometry, material_runs=tuple(runs))


def copy_runtime_captured_auxiliary_textures(
    record: dict[str, Any], output: Path
) -> tuple[set[str], set[str]]:
    """Copy secondary captured textures beside a self-contained preview."""

    source_root = record.get("_source_root")
    if not isinstance(source_root, Path):
        return set(), set()
    copied_mips = set()
    copied_multitextures = set()
    for variant in record.get("variants", []):
        captured = variant.get("captured_texture")
        if not isinstance(captured, dict):
            continue
        texture1_image = captured.get("texture1_image")
        for level in runtime_captured_auxiliary_textures(captured):
            source = _validated_preview_source(source_root, level["file"])
            data = source.read_bytes()
            if hashlib.sha1(data).hexdigest() != level["png_sha1"]:
                raise ValueError("runtime captured mip PNG hash changed")
            filename = source.name
            destination = output / "textures" / filename
            destination.parent.mkdir(parents=True, exist_ok=True)
            if destination.exists() and destination.read_bytes() != data:
                raise ValueError("runtime captured mip filename collision")
            destination.write_bytes(data)
            level["preview_file"] = f"../textures/{filename}"
            if level is texture1_image:
                copied_multitextures.add(filename)
            else:
                copied_mips.add(filename)
    return copied_mips, copied_multitextures


def character_intensity_shade_alpha_preview_texture(run, payload):
    """Recover I8 colour when the complete combiner excludes texture alpha."""
    state = texture_coordinate_state(run)
    combine = decode_combine_mode(run.combine_mode)
    other = decode_other_mode(run.other_mode)
    formula = [
        {'color': ['ZERO', 'ZERO', 'ZERO', 'TEXEL0'],
         'alpha': ['ZERO', 'ZERO', 'ZERO', 'SHADE']},
        {'color': ['SHADE', 'ENVIRONMENT', 'COMBINED', 'PRIMITIVE'],
         'alpha': ['COMBINED', 'ZERO', 'ENVIRONMENT', 'ZERO']},
    ]
    shade_modulate = [
        {'color': ['TEXEL0', 'ZERO', 'SHADE', 'ZERO'],
         'alpha': ['ZERO', 'ZERO', 'ZERO', 'SHADE']},
        {'color': ['ZERO', 'ZERO', 'ZERO', 'COMBINED'],
         'alpha': ['COMBINED', 'ZERO', 'ENVIRONMENT', 'ZERO']},
    ]
    if (state is None or (state['format'], state['size']) != (4, 1)
            or combine is None or combine['cycles'] not in (formula, shade_modulate)):
        return None, 'character-intensity-shade-alpha-combiner-unresolved'
    if (other is None or other['texture_lut'] != 'none' or other['cycle_type'] != 'two-cycle'
            or other['texture_lod'] != 'tile' or run.texture_scale is None
            or (run.texture_scale[0] >> 11) & 7):
        return None, 'character-intensity-shade-alpha-other-mode-unresolved'
    pixel = run.pixel
    if (pixel is None or pixel.flat_index is None or pixel.mode != 0
            or pixel.image_command != 0xFD900000 or pixel.load_command is None
            or pixel.load_command[0] != 0xF3000000 or pixel.load_command[1] & 0xFFF):
        return None, 'character-intensity-shade-alpha-load-unresolved'
    tiles = {i: c for i, c, _ in run.render_tiles}
    if tiles.get((pixel.load_command[1] >> 24) & 7) != 0xF5100000:
        return None, 'character-intensity-shade-alpha-load-tile-unresolved'
    stride = ((run.render_tile[0] >> 9) & 0x1FF) * 8
    start = (run.render_tile[0] & 0x1FF) * 8
    loaded = (((pixel.load_command[1] >> 12) & 0xFFF) + 1) * 2
    if (stride < state['width'] or start + stride * state['height'] > loaded
            or loaded > min(len(payload), 4096)):
        return None, 'character-intensity-shade-alpha-span-unresolved'
    rows = []
    for y in range(state['height']):
        row = payload[start + y * stride:start + (y + 1) * stride]
        rows.append(bytes(row[x ^ (4 if y & 1 else 0)] for x in range(state['width'])))
    # Source I8 intensity is not the alpha input of this draw. A preview RGB
    # texture therefore carries alpha one; vertex/environment alpha is separate.
    rgba = b''.join(bytes((v, v, v, 255)) for row in reversed(rows) for v in row)
    png = encode_rgba_png(state['width'], state['height'], rgba)
    return PreviewTexture('us-character-intensity-shade-alpha', None, pixel.flat_index,
                          4, 1, state['width'], state['height'], hashlib.sha1(png).hexdigest(),
                          png, start), 'character-intensity-shade-alpha-i8'


def character_intensity_mipmap_preview_texture(run, payload):
    """Decode a supported IA/I mip base after validating every declared level."""
    state = texture_coordinate_state(run)
    formats = {(3, 0): 'ia4', (3, 1): 'ia8', (3, 2): 'ia16', (4, 0): 'i4', (4, 1): 'i8'}
    name = formats.get((state['format'], state['size'])) if state else None
    direct_mip = is_direct_ia4_trilinear_base(run) or is_direct_ia8_shade_mipmap_base(run)
    shade_mip_alpha = intensity_shade_mipmap_alpha(run)
    if name is None or not (is_character_trilinear_base(run) or direct_mip or shade_mip_alpha):
        return None, 'character-intensity-mipmap-combiner-unresolved'
    other = decode_other_mode(run.other_mode)
    if (other is None or run.other_mode_partial is not None
            or other['texture_lut'] != 'none' or other['texture_lod'] != 'lod'
            or other['texture_detail'] != 'clamp' or other['cycle_type'] != 'two-cycle'):
        return None, 'character-intensity-mipmap-other-mode-unresolved'
    pixel = run.pixel
    if (pixel is None or pixel.flat_index is None or pixel.mode != 0
            or pixel.image_command != {3: 0xFD700000, 4: 0xFD900000}[state['format']]
            or pixel.load_command is None or pixel.load_command[0] != 0xF3000000
            or pixel.load_command[1] & 0xFFF or run.texture_scale is None):
        return None, 'character-intensity-mipmap-load-unresolved'
    tiles = {i: (c, a) for i, c, a in run.render_tiles}
    load = tiles.get((pixel.load_command[1] >> 24) & 7)
    # SetTextureImage and the LoadBlock tile both transfer sixteen-bit units.
    # The latter uses the game's RGBA16 transfer tile; render tiles supply IA/I.
    allowed_load_tiles = (0xF5100000, 0xF5700000) if direct_mip else (0xF5100000,)
    if shade_mip_alpha:
        allowed_load_tiles = (0xF5100000, {3: 0xF5700000, 4: 0xF5900000}[state['format']])
    if load is None or load[0] not in allowed_load_tiles:
        return None, 'character-intensity-mipmap-load-tile-unresolved'
    base_tile = (run.texture_scale[0] >> 8) & 7
    if (direct_mip or shade_mip_alpha) and tiles.get(base_tile) != run.render_tile:
        return None, 'direct-' + name + '-mipmap-base-tile-unresolved'
    maximum = (run.texture_scale[0] >> 11) & 7
    loaded = (((pixel.load_command[1] >> 12) & 0xFFF) + 1) * 2
    if not maximum or base_tile + maximum >= 6 or loaded > min(len(payload), 4096):
        return None, 'character-intensity-mipmap-span-unresolved'
    previous_end = 0
    first_stride = first_start = None
    for level in range(maximum + 1):
        tile = tiles.get(base_tile + level)
        if tile is None:
            return None, 'character-intensity-mipmap-tiles-unresolved'
        command, argument = tile
        width, height = max(1, state['width'] >> level), max(1, state['height'] >> level)
        if state['size'] == 0 and width % 2:
            return None, 'character-intensity-mipmap-width-unresolved'
        stride = ((command >> 9) & 0x1FF) * 8
        start = (command & 0x1FF) * 8
        if (((command >> 21) & 7, (command >> 19) & 3) != (state['format'], state['size'])
                or (1 << ((argument >> 4) & 15), 1 << ((argument >> 14) & 15)) != (width, height)
                or (argument & 15, (argument >> 10) & 15) != (level, level)
                or stride < packed_row_size(name, width) or start < previous_end
                or start + stride * height > loaded):
            return None, 'character-intensity-mipmap-layout-unresolved'
        if level == 0:
            first_stride, first_start = stride, start
        previous_end = start + stride * height
    row_bytes = packed_row_size(name, state['width'])
    rows = []
    for y in range(state['height']):
        start = first_start + y * first_stride
        row = payload[start:start + first_stride]
        rows.append(bytes(row[x ^ (4 if y & 1 else 0)] for x in range(row_bytes)))
    png = encode_native_texture_png(b''.join(rows), name, 'linear', state['width'], state['height'])
    if shade_mip_alpha == 'shade':
        # N64 intensity/IA alpha is not used by this combiner. Keep its RGB,
        # while allowing vertex alpha to remain independent in the material.
        rgba = bytearray(native_payload_to_rgba(b''.join(reversed(rows)), name))
        rgba[3::4] = bytes([255]) * (state['width'] * state['height'])
        png = encode_rgba_png(state['width'], state['height'], bytes(rgba))
    family = 'us-direct-' + name + '-mipmap-base' if direct_mip else 'us-character-intensity-mipmap-base'
    status = 'direct-' + name + '-mipmap-base' if direct_mip else 'character-intensity-mipmap-base-' + name
    if shade_mip_alpha == 'shade':
        family += '-shade-alpha'
        status += '-shade-alpha'
    return PreviewTexture(family, None, pixel.flat_index,
                          state['format'], state['size'], state['width'], state['height'],
                          hashlib.sha1(png).hexdigest(), png, first_start), status


def rom_render_state_preview_texture(run, catalog, payloads, tables):
    """Resolve a texture only when every ROM segment-8 variant agrees.

    The effective render pass remains unknown. No selected OtherMode is
    propagated into geometry or glTF blending from this texture-only proof.
    """
    if run.other_mode is not None or run.other_mode_partial is not None or run.runtime_render_state_offset is None:
        return None, 'rom-state-consensus-unavailable', None
    if tuple(int(table['base_address'], 0) for table in tables) != RUNTIME_RENDER_STATE_TABLE_BASES:
        raise ValueError('ROM render-state consensus requires every verified table')
    modes = []
    for table in tables:
        entries = [entry for entry in table['entries']
                   if int(entry['offset'], 0) == run.runtime_render_state_offset]
        if len(entries) != 1:
            raise ValueError('ROM render-state consensus has an absent or repeated offset')
        mode = tuple(int(word, 0) for word in entries[0]['other_mode'])
        decode_other_mode(mode)
        modes.append(mode)
    choices = []
    for mode in modes:
        candidate_run = replace(run, other_mode=mode, runtime_render_state_offset=None)
        texture, status = choose_preview_texture(candidate_run, catalog, payloads)
        if texture is None and run.pixel is not None and run.pixel.flat_index in payloads:
            texture, status = character_intensity_shade_alpha_preview_texture(candidate_run, payloads[run.pixel.flat_index])
        if texture is None and run.pixel is not None and run.pixel.flat_index in payloads:
            texture, status = character_intensity_mipmap_preview_texture(candidate_run, payloads[run.pixel.flat_index])
        choices.append((texture, status))
    texture, status = choices[0]
    if texture is None or any(candidate != texture or reason != status for candidate, reason in choices):
        return None, 'rom-state-consensus-texture-unresolved', None
    evidence = {'segment_8_offset': run.runtime_render_state_offset,
                'tables': [{'base_address': table['base_address'], 'other_mode': list(mode)}
                           for table, mode in zip(tables, modes)],
                'texture_png_sha1': texture.sha1, 'texture_status': status,
                'scope': 'Texture agrees for every ROM segment-8 table. Effective render pass, blending and colours remain unresolved.'}
    if status == 'character-intensity-shade-alpha-i8':
        evidence['texture_alpha'] = 'one; combiner alpha is SHADE times ENVIRONMENT and never samples texture alpha'
    return replace(texture, family='us-rom-state-consensus'), 'rom-state-consensus-' + status, evidence


def load_object_material_context(profile: str, rom_argument: Path | None, digest: str, bank_index: int = 3) -> dict:
    rom_path, layout = resolve_rom(profile, rom_argument)
    rom, _ = normalize_rom(rom_path.read_bytes())
    if profile != 'us' or hashlib.sha1(rom).hexdigest() != digest or digest not in layout['normalized_sha1']:
        raise ValueError('object materials require the same validated US ROM')
    game = parse_game_archive(rom[layout['game_start']:layout['game_end']])
    if bank_index == 9:
        try:
            from scripts import model_attachment_texture_bindings as attachments
            from scripts import model_callback_texture_bindings as callbacks
            from scripts import model_timer_texture_bindings as timer
            from scripts import model_attachment_updates as attachment_updates
        except ModuleNotFoundError:
            import model_attachment_texture_bindings as attachments
            import model_callback_texture_bindings as callbacks
            import model_timer_texture_bindings as timer
            import model_attachment_updates as attachment_updates
        context = model_bank09_materials.material_context(
            game.code, layout['game_vram'], game.data, layout['game_data_vram'])
        attachment_context = attachments.material_context(
            game.code, layout['game_vram'], game.data, layout['game_data_vram'])
        identities = {(r['bank'], r['entry'], r['segment']) for r in context['models']}
        if any((r['bank'], r['entry'], r['segment']) in identities for r in attachment_context['models']):
            raise ValueError('attachment and ordinary object material contexts overlap')
        context['models'].extend(attachment_context['models'])
        context['attachment_consumers'] = attachment_context['consumers']
        callback_context = callbacks.material_context(
            game.code, layout['game_vram'], game.data, layout['game_data_vram'])
        identities.update((r['bank'], r['entry'], r['segment']) for r in attachment_context['models'])
        if any((r['bank'], r['entry'], r['segment']) in identities for r in callback_context['models']):
            raise ValueError('callback and ordinary object material contexts overlap')
        context['models'].extend(callback_context['models'])
        context['callback_consumers'] = callback_context['consumers']
        timer_context = timer.material_context(game.code, layout['game_vram'])
        identities.update((r['bank'], r['entry'], r['segment']) for r in callback_context['models'])
        if any((r['bank'], r['entry'], r['segment']) in identities for r in timer_context['models']):
            raise ValueError('timer and other object material contexts overlap')
        context['models'].extend(timer_context['models'])
        context['timer_consumers'] = timer_context['consumers']
        update_context = attachment_updates.material_context(
            game.code, layout['game_vram'], game.data, layout['game_data_vram'])
        identities.update((r['bank'], r['entry'], r['segment']) for r in timer_context['models'])
        if any((r['bank'], r['entry'], r['segment']) in identities for r in update_context['models']):
            raise ValueError('attachment update and other object material contexts overlap')
        context['models'].extend(update_context['models'])
        context['attachment_update_consumers'] = update_context['consumers']
        return {'normalized_sha1': digest, **context}
    if bank_index not in (3, 4):
        raise ValueError('object materials require bank 03, 04 or 09')
    try:
        from scripts import model_object_texture_animation as animation
    except ModuleNotFoundError:
        import model_object_texture_animation as animation
    consumers = model_object_materials.verify_consumers(game.code, layout['game_vram'], game.data)
    placements, _ = load_object_placement_manifest(profile, rom_argument, include_files=False)
    if placements['normalized_sha1'] != digest:
        raise ValueError('object placement ROM changed while reading material context')
    contexts = model_object_materials.placement_contexts(placements, game.data, layout['game_data_vram'])
    if bank_index == 4:
        rows = animation.animation_table(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
        animations = animation.placement_animations(placements, rows)
        try:
            from scripts import model_object_texture_bindings as object_bindings
        except ModuleNotFoundError:
            import model_object_texture_bindings as object_bindings
        pair = object_bindings.binding_table(
            game.code, layout['game_vram'], game.data, layout['game_data_vram'])
        bindings = object_bindings.placement_bindings(placements, pair)
        for context in contexts:
            key = (context['bank'], context['entry'], context['segment'])
            if key in animations:
                context['texture_animation'] = animations[key]
            if key in bindings:
                context['texture_binding'] = bindings[key]
        try:
            from scripts import model_scene_texture_bindings as scene_textures
        except ModuleNotFoundError:
            import model_scene_texture_bindings as scene_textures
        contexts.extend(scene_textures.scene_contexts(
            game.code, layout['game_vram'], game.data, layout['game_data_vram']))
    return {'normalized_sha1': digest, 'consumers': consumers,
            'segment_override_call_sites': [f'0x{address:08X}' for address in model_object_materials.OVERRIDE_CALLS],
            'segment_override_destinations': [4, 5, 6, 7],
            'models': contexts,
            'capture_inputs': []}


def apply_rom_attachment_preview_update(data, geometry, context, runtime_materials=None):
    if not (context or {}).get('geometry_update'):
        return geometry, None
    try:
        from scripts import model_attachment_updates
    except ModuleNotFoundError:
        import model_attachment_updates
    return model_attachment_updates.preview_geometry(data, geometry, context, runtime_materials)


def rom_object_animation_preview_texture(run, catalog, payloads, tables, context):
    animation = (context or {}).get('texture_animation')
    pixel, palette = run.pixel, run.palette
    if (not animation or not run.texture_enabled or not run.texture_coordinates_proven
            or pixel is None or pixel.segment != 4 or pixel.offset != 0
            or pixel.flat_index is not None or pixel.external
            or (palette is not None and (palette.segment != 5 or palette.offset != 0
                or palette.flat_index is not None or palette.external))):
        return None, 'rom-object-animation-binding-unresolved', None
    textures, frames = [], []
    for flat in animation['frames']:
        mapped = replace(run,
            pixel=replace(pixel, flat_index=flat, mode=0, segment=None, offset=None),
            palette=replace(palette, flat_index=flat, mode=2, segment=None, offset=None) if palette else None)
        texture, status = choose_preview_texture(mapped, catalog, payloads)
        state_evidence = None
        if texture is None and ('lookup-mode-unresolved' in status or status == 'no-proven-texture'):
            texture, status, state_evidence = rom_object_preview_texture(mapped, catalog, payloads, tables, context)
        if texture is None or (palette is not None and texture.palette_byte_offset != len(payloads[flat]) - 32):
            return None, 'rom-object-animation-frame-unresolved', None
        textures.append(texture)
        frames.append({'flat_index': flat, 'png_sha1': texture.sha1, 'texture_status': status,
                       'render_state_consensus': state_evidence})
    if not textures or animation['preview_frame'] != 0:
        return None, 'rom-object-animation-frame-unresolved', None
    first = textures[0]
    if any((t.width, t.height, t.format, t.size) != (first.width, first.height, first.format, first.size)
           for t in textures):
        return None, 'rom-object-animation-layout-unresolved', None
    evidence = {'binding': animation, 'frames': frames,
                'scope': 'First stored ROM texture frame; frame timing, current phase, lighting and native appearance remain unverified.'}
    return replace(first, family='us-rom-object-animation'), 'rom-object-animation-frame', evidence


def rom_attachment_binding_preview_texture(run, catalog, payloads, state):
    """Resolve an attachment's inline CI palette at a proven payload offset."""
    pixel, palette = run.pixel, run.palette
    if (not run.texture_enabled or not run.texture_coordinates_proven
            or pixel is None or pixel.external or pixel.flat_index is not None
            or pixel.segment != 6 or pixel.offset != 0
            or palette is None or palette.external or palette.flat_index is not None
            or palette.segment != pixel.segment or not isinstance(palette.offset, int)):
        return None, 'rom-attachment-binding-unresolved', None
    binding = state['bindings'].get(str(pixel.segment))
    if (not binding or binding['pixel_segment'] != pixel.segment
            or binding['palette_segment'] != palette.segment):
        return None, 'rom-attachment-binding-unresolved', None
    decoded, textures = [], []
    for flat in binding['flats']:
        payload = payloads.get(flat)
        if payload is None:
            return None, 'rom-attachment-payload-unresolved', None
        tail_size = len(payload) - palette.offset
        if tail_size not in (32, 512) or palette.offset <= 0:
            return None, 'rom-attachment-palette-unresolved', None
        mapped = replace(run,
            pixel=replace(pixel, flat_index=flat, mode=0, segment=None, offset=None),
            palette=replace(palette, flat_index=flat, mode=2 if tail_size == 32 else 1,
                            segment=None, offset=None))
        texture, status = choose_preview_texture(mapped, catalog, payloads)
        # No inherited render-state guess: CI format, TLUT load extent and
        # TMEM span must be proven by the attachment's own commands.
        if (texture is None or (texture.format, texture.size) != (2, 0 if tail_size == 32 else 1)
                or texture.palette_byte_offset != palette.offset):
            return None, 'rom-attachment-texture-unresolved', None
        textures.append(texture)
        decoded.append({'flat_index': flat, 'png_sha1': texture.sha1, 'texture_status': status})
    if not textures or binding['selected_index'] != 0:
        return None, 'rom-attachment-selector-unresolved', None
    first = textures[0]
    if any((t.width, t.height, t.format, t.size) != (first.width, first.height, first.format, first.size)
           for t in textures):
        return None, 'rom-attachment-layout-unresolved', None
    evidence = {'binding': state, 'pixel_segment': pixel.segment, 'decoded_variants': decoded,
                'scope': state['preview_policy'] + '; ' + state['scope']}
    return replace(first, family='us-rom-attachment-binding'), 'rom-attachment-binding-texture', evidence


def rom_direct_binding_preview_texture(run, catalog, payloads, state):
    """Decode proven direct pixel segments using only the model's own draw state."""
    pixel = run.pixel
    if (not run.texture_enabled or not run.texture_coordinates_proven
            or pixel is None or pixel.external or pixel.flat_index is not None
            or pixel.offset != 0 or run.palette is not None):
        return None, 'rom-direct-binding-unresolved', None
    binding = state['bindings'].get(str(pixel.segment))
    if not binding or binding['pixel_segment'] != pixel.segment:
        return None, 'rom-direct-binding-unresolved', None
    textures, decoded = [], []
    for flat in binding['flats']:
        payload = payloads.get(flat)
        if payload is None or len(payload) != binding['payload_bytes']:
            return None, 'rom-direct-binding-payload-unresolved', None
        mapped = replace(run, pixel=replace(pixel, flat_index=flat, mode=0,
                                           segment=None, offset=None))
        texture, status = choose_preview_texture(mapped, catalog, payloads)
        # Do not apply ordinary-object segment-8 consensus to a direct renderer.
        if texture is None or [texture.width, texture.height, texture.format, texture.size] != binding['image_layout']:
            return None, 'rom-direct-binding-texture-unresolved', None
        textures.append(texture)
        decoded.append({'flat_index': flat, 'png_sha1': texture.sha1, 'texture_status': status})
    selected = binding['selected_index']
    if (not textures or type(selected) is not int or not 0 <= selected < len(textures)
            or binding['flats'][selected] != binding['selected_flat']):
        return None, 'rom-direct-binding-selector-unresolved', None
    evidence = {'binding': state, 'pixel_segment': pixel.segment, 'decoded_variants': decoded,
                'scope': state['preview_policy'] + '; ' + state['scope']}
    return replace(textures[selected], family='us-rom-direct-binding'), 'rom-direct-binding-texture', evidence


def rom_object_binding_preview_texture(run, catalog, payloads, tables, context):
    state = (context or {}).get('texture_binding')
    if state and state.get('kind') == 'attachment-payload':
        return rom_attachment_binding_preview_texture(run, catalog, payloads, state)
    if state and state.get('kind') == 'direct-pixel-segments':
        return rom_direct_binding_preview_texture(run, catalog, payloads, state)
    pixel, palette = run.pixel, run.palette
    if (not state or not run.texture_enabled or not run.texture_coordinates_proven
            or pixel is None or pixel.external or pixel.flat_index is not None or pixel.offset != 0
            or palette is None or palette.external or palette.flat_index is not None or palette.offset != 0):
        return None, 'rom-object-binding-unresolved', None
    binding = state['bindings'].get(str(pixel.segment))
    if (not binding or binding['pixel_segment'] != pixel.segment
            or binding['palette_segment'] != palette.segment or state['palette_tail_bytes'] != 512):
        return None, 'rom-object-binding-unresolved', None
    decoded, textures = [], []
    for flat in binding['flats']:
        mapped = replace(run,
            pixel=replace(pixel, flat_index=flat, mode=0, segment=None, offset=None),
            palette=replace(palette, flat_index=flat, mode=1, segment=None, offset=None))
        texture, status = choose_preview_texture(mapped, catalog, payloads)
        consensus = None
        if texture is None and ('lookup-mode-unresolved' in status or status == 'no-proven-texture'):
            texture, status, consensus = rom_object_preview_texture(mapped, catalog, payloads, tables, context)
        if (texture is None or (texture.format, texture.size) != (2, 1)
                or texture.palette_byte_offset != len(payloads[flat]) - 512):
            return None, 'rom-object-binding-texture-unresolved', None
        textures.append(texture)
        decoded.append({'flat_index': flat, 'png_sha1': texture.sha1, 'texture_status': status,
                        'render_state_consensus': consensus})
    selected = binding['selected_index']
    if not textures or selected != 0:
        return None, 'rom-object-binding-selector-unresolved', None
    first = textures[selected]
    if any((t.width, t.height, t.format, t.size) != (first.width, first.height, first.format, first.size)
           for t in textures):
        return None, 'rom-object-binding-layout-unresolved', None
    evidence = {'binding': state, 'pixel_segment': pixel.segment, 'decoded_variants': decoded,
                'scope': state['preview_policy'] + '; ' + state['scope']}
    return replace(first, family='us-rom-object-binding'), 'rom-object-binding-texture', evidence


def rom_scene_preview_texture(run, catalog, payloads, context):
    state = (context or {}).get('scene_texture_state')
    pixel = run.pixel
    if (not state or not run.texture_enabled or not run.texture_coordinates_proven
            or pixel is None or pixel.external or pixel.flat_index is not None
            or pixel.offset != 0 or run.palette is not None):
        return None, 'rom-scene-binding-unresolved', None
    binding = state['bindings'].get(str(pixel.segment))
    if not binding or binding['pixel_segment'] != pixel.segment:
        return None, 'rom-scene-binding-unresolved', None
    frames, textures = [], []
    for flat in binding['frames']:
        mapped = replace(run, pixel=replace(pixel, flat_index=flat, mode=0,
                                           segment=None, offset=None))
        texture, status = choose_preview_texture(mapped, catalog, payloads)
        if texture is None:
            return None, 'rom-scene-frame-unresolved', None
        textures.append(texture)
        frames.append({'flat_index': flat, 'png_sha1': texture.sha1, 'texture_status': status})
    selected = binding['selected_index']
    if (not textures or not isinstance(selected, int) or not 0 <= selected < len(textures)
            or binding['frames'][selected] != binding['selected_flat']):
        return None, 'rom-scene-selector-unresolved', None
    texture = textures[selected]
    if any((t.width, t.height, t.format, t.size) !=
           (texture.width, texture.height, texture.format, texture.size) for t in textures):
        return None, 'rom-scene-layout-unresolved', None
    evidence = {'scene': context['entry'], 'renderer': context['renderer'],
                'state': state, 'decoded_frames': frames, 'scope': context['scope']}
    return replace(texture, family='us-rom-scene-state'), 'rom-scene-texture-state', evidence


def rom_object_preview_texture(run, catalog, payloads, tables, context):
    if (context is None or 'scene_texture_state' in context
            or context.get('texture_binding', {}).get('kind') in ('attachment-payload', 'direct-pixel-segments')):
        return None, 'rom-object-renderer-unresolved', None
    texture, status, evidence = rom_render_state_preview_texture(run, catalog, payloads, tables)
    if evidence is not None:
        evidence['object_renderer_context'] = {
            key: context[key] for key in ('bank', 'entry', 'segment', 'renderer', 'segment_8_bases', 'scope')}
    return texture, status, evidence


def add_rom_texture_state_evidence(encoded: bytes, run_records: list[dict]) -> bytes:
    if not any(record.get('rom_texture_state_consensus') or record.get('rom_object_texture_animation') or record.get('rom_scene_texture_state') or record.get('rom_object_texture_binding') or (record.get('texture') or {}).get('tmem_source_loads') for record in run_records):
        return encoded
    document = json.loads(encoded)
    for material in document.get('materials', []):
        extras = material.get('extras', {})
        index = extras.get('materialRun')
        if isinstance(index, int) and (run_records[index].get('texture') or {}).get('tmem_source_loads'):
            extras['romTextureMemory'] = {
                'source_loads': run_records[index]['texture']['tmem_source_loads'],
                'scope': ('ROM LoadBlocks within one callable list; selected RGBA8 tile without TLUT. Native appearance unverified.'
                          if run_records[index]['texture'].get('tmem_fetch') else
                          'ROM LoadBlocks within one callable list; selected tile and latest TLUT retained. Native appearance unverified.'),
                **({'fetch': run_records[index]['texture']['tmem_fetch']}
                   if run_records[index]['texture'].get('tmem_fetch') else {}),
            }
        if isinstance(index, int) and run_records[index].get('rom_texture_state_consensus'):
            extras['romTextureStateConsensus'] = run_records[index]['rom_texture_state_consensus']
        if isinstance(index, int) and run_records[index].get('rom_object_texture_animation'):
            extras['romObjectTextureAnimation'] = run_records[index]['rom_object_texture_animation']
        if isinstance(index, int) and run_records[index].get('rom_object_texture_binding'):
            extras['romObjectTextureBinding'] = run_records[index]['rom_object_texture_binding']
        if isinstance(index, int) and run_records[index].get('rom_scene_texture_state'):
            extras['romSceneTextureState'] = run_records[index]['rom_scene_texture_state']
    return (json.dumps(document, indent=2) + '\n').encode()


def load_character_defaults(profile: str, rom_argument: Path | None, digest: str, *, include_expressions: bool = False) -> dict:
    """Resolve ordinary character defaults using only validated ROM bytes."""
    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, _ = normalize_rom(rom_path.read_bytes())
    if hashlib.sha1(normalized).hexdigest() != digest or digest not in layout['normalized_sha1']:
        raise ValueError('character defaults require the same validated ROM')
    game = parse_game_archive(normalized[layout['game_start']:layout['game_end']])
    consumers = model_character_defaults.verify_consumers(game.code, layout['game_vram'])
    draw_tables = model_character_parts.verify_consumers(game.code, layout['game_vram'])
    expression_consumers = model_character_defaults.verify_expression_consumers(game.code, layout['game_vram']) if include_expressions else None
    expression_programs = model_character_defaults.parse_expression_animation_programs(game.data, layout['game_data_vram']) if include_expressions else None
    expression_texture_consumers = model_character_defaults.expression_texture_consumers(
        game.code, layout['game_vram'])
    bank = next(bank for bank in parse_asset_banks(normalized, layout['asset_table']) if bank.index == 0x11)
    if bank.flags:
        raise ValueError('character-default bank has unsupported flags')
    entries = {}
    for entry in parse_asset_entries(normalized, bank):
        raw = normalized[entry.start:entry.end]
        data = decode_rzip_chunk(raw).data if entry.compressed else raw
        entries[entry.index] = {
            **model_character_defaults.parse_defaults(data),
            'rom_start': f'0x{entry.start:X}', 'rom_end': f'0x{entry.end:X}',
            'compressed': entry.compressed,
        }
        if include_expressions or entry.index in model_character_defaults.EXPRESSION_PREVIEW_PRESETS:
            entries[entry.index]['expression_presets'] = model_character_defaults.parse_expression_presets(data)
        if include_expressions:
            for preset in entries[entry.index]['expression_presets']:
                selector = preset['animation_selector']
                if selector and (entry.index != 0 or selector > len(expression_programs)):
                    raise ValueError('expression references an unsupported native action selector')
                preset['native_action'] = expression_programs[selector - 1]['native_action'] if selector else None
    return {'bank_index': 0x11, 'consumer_words': consumers, 'entries': entries,
            'draw_table_selection': draw_tables,
            'instance_texture_presets': model_character_defaults.instance_texture_presets(game.code, layout['game_vram']),
            'renderer_texture_presets': model_character_defaults.renderer_texture_presets(game.code, layout['game_vram']),
            'expression_preview_presets': {
                entry: {'index': index, 'consumer_sha1': expression_texture_consumers}
                for entry, index in model_character_defaults.EXPRESSION_PREVIEW_PRESETS.items()},
            **({'expression_consumers': expression_consumers, 'expression_animation_programs': expression_programs} if include_expressions else {}),
            'capture_inputs': [], 'normalized_sha1': digest}


def load_character_expression_manifest(profile: str, rom_argument: Path | None, digest: str) -> dict:
    source = load_character_defaults(profile, rom_argument, digest, include_expressions=True)
    records = [{'character_entry': entry, 'bundle_sha1': record['sha1'],
                'default_header_sha1': record['header_sha1'],
                'source_offset': record['expression_offset'], 'decoded_size': record['expression_size'],
                'presets': record['expression_presets']}
               for entry, record in source['entries'].items() if record['expression_presets']]
    return {'schema_version': 1, 'family': 'ROM-character-expression-presets',
            'normalized_sha1': digest, 'bank_index': 0x11,
            'source_bundle_count': len(source['entries']), 'model_count': len(records),
            'preset_count': sum(len(record['presets']) for record in records),
            'decoded_size': sum(record['decoded_size'] for record in records),
            'consumer_sha1': source['expression_consumers'], 'models': records,
            'animation_programs': source['expression_animation_programs'],
            'scope': 'Native ten-byte expression presets. Morph duration may be overridden by the caller; zero texture overrides select the initializer defaults. Nonzero animation selectors resolve to native action programs, not direct clip indices. Expression names, triggers and complete playback timelines remain unresolved.',
            'capture_inputs': []}


def rom_default_preview_texture(run, defaults, descriptors, payloads, render_state_tables):
    """Decode a ROM-selected face image with its explicit load and format."""
    evidence = {'preset': defaults['preset'], 'default_header_sha1': defaults['header_sha1']}
    if defaults.get('instance_texture_selection'):
        evidence['instance_texture_selection'] = defaults['instance_texture_selection']
    if defaults.get('expression_texture_selection'):
        evidence['expression_texture_selection'] = defaults['expression_texture_selection']
    if defaults.get('renderer_texture_selection'):
        evidence['renderer_texture_selection'] = defaults['renderer_texture_selection']

    def unresolved(reason):
        return None, 'rom-default-' + reason, evidence

    combine = decode_combine_mode(run.combine_mode)
    if combine is None:
        return unresolved('combiner-unresolved')
    texels = set(combine['inputs']).intersection(('TEXEL0', 'TEXEL1'))
    if not texels:
        return unresolved('combiner-does-not-use-texture')
    trilinear = is_character_trilinear_base(run)
    if texels != {'TEXEL0'} and not trilinear:
        return unresolved('multitexture-unresolved')
    if not run.texture_enabled or not run.texture_coordinates_proven:
        return unresolved('coordinate-state-unresolved')
    pixel, palette = run.pixel, run.palette
    state = texture_coordinate_state(run)
    direct_format = {(3, 1): 'ia8', (0, 3): 'rgba32'}.get(
        (state['format'], state['size'])) if state else None
    if direct_format:
        if pixel is None or palette is not None or pixel.offset != 0:
            return unresolved('direct-binding-unresolved')
        descriptor = model_character_defaults.select_descriptor(defaults, descriptors, pixel.segment)
        if descriptor is None:
            return unresolved('descriptor-unresolved')
        evidence.update(segment=pixel.segment, descriptor=descriptor)
        if (descriptor['width'], descriptor['height']) != (state['width'], state['height']):
            return unresolved('descriptor-dimensions-differ')
        other = decode_other_mode(run.other_mode)
        if (other is None or run.other_mode_partial is not None
                or other['texture_lut'] != 'none'
                or other['cycle_type'] not in ('one-cycle', 'two-cycle')):
            return unresolved('direct-other-mode-unresolved')
        if trilinear:
            return unresolved('direct-multitexture-unresolved')
        alpha = [cycle['alpha'] for cycle in combine['cycles']]
        product = (alpha[0] == ['TEXEL0', 'ZERO', 'SHADE', 'ZERO']
                   and (other['cycle_type'] == 'one-cycle'
                        or alpha[1] == ['COMBINED', 'ZERO', 'ENVIRONMENT', 'ZERO']))
        if other['gltf_alpha_mode'] != 'OPAQUE' and not product:
            return unresolved('direct-alpha-expression-unresolved')
        if pixel.image_command != {'ia8': 0xFD700000, 'rgba32': 0xFD180000}[direct_format]:
            return unresolved('direct-load-format-unresolved')
        payload = payloads.get(descriptor['flat_index'])
        if payload is None:
            return unresolved('payload-missing')
        # Reuse the direct-format transfer decoder after resolving the native
        # segmented selector. The original binding stays in the model record.
        selected = replace(run, pixel=replace(pixel, mode=0, flat_index=descriptor['flat_index']))
        decoder = direct_intensity_preview_texture if direct_format == 'ia8' else direct_rgba32_preview_texture
        texture, status = decoder(selected, payload)
        if texture is None:
            return unresolved(status)
        evidence.update(flat_payload_sha1=hashlib.sha1(payload).hexdigest(),
                        render_dimensions=[state['width'], state['height']],
                        dimension_evidence=state['dimension_evidence'],
                        source_format=direct_format, pixel_byte_offset=0,
                        palette_byte_offset=None, lookup_evidence='explicit-other-mode',
                        decoder_status=status, png_sha1=texture.sha1)
        return replace(texture, family='us-rom-default-direct'), 'rom-default-direct-' + direct_format, evidence
    if pixel is None or palette is None or pixel.segment != palette.segment:
        return unresolved('palette-binding-unresolved')
    descriptor = model_character_defaults.select_descriptor(defaults, descriptors, pixel.segment)
    if descriptor is None:
        return unresolved('descriptor-unresolved')
    evidence.update(segment=pixel.segment, descriptor=descriptor)
    if state is None or (state['format'], state['size']) not in ((0, 0), (0, 1), (2, 0), (2, 1)):
        return unresolved('format-unresolved')
    if ((descriptor['width'], descriptor['height']) != (state['width'], state['height'])
            and state['dimension_evidence'] != 'tile-bounds'):
        return unresolved('descriptor-dimensions-differ')
    # Renderer variants differ in blending. Only infer their unanimous TLUT
    # setting; do not select a runtime pass or bake its colours into the model.
    modes = []
    if run.other_mode is not None:
        modes = [run.other_mode]
    elif run.runtime_render_state_offset is not None:
        for table in render_state_tables:
            matches = [e for e in table['entries'] if int(e['offset'], 0) == run.runtime_render_state_offset]
            if len(matches) != 1:
                return unresolved('lookup-state-unresolved')
            modes.append(tuple(int(word, 0) for word in matches[0]['other_mode']))
    if not modes or any(decode_other_mode(mode)['texture_lut'] != 'rgba16' for mode in modes):
        return unresolved('lookup-state-unresolved')
    if (pixel.image_command != 0xFD100000 or palette.image_command != 0xFD100000
            or pixel.load_command is None or palette.load_command is None
            or pixel.offset is None or palette.offset is None):
        return unresolved('load-command-unresolved')
    pc, pa = pixel.load_command
    tc, ta = palette.load_command
    entries = 16 if state['size'] == 0 else 256
    if pc != 0xF3000000 or pa & 0xFFF or tc != 0xF0000000 or ((ta >> 14) & 0x3FF) + 1 != entries:
        return unresolved('load-layout-unresolved')
    tiles = {i: (c, a) for i, c, a in run.render_tiles}
    load_tile = tiles.get((pa >> 24) & 7)
    tlut_tile = tiles.get((ta >> 24) & 7)
    if load_tile is None or tlut_tile is None or (tlut_tile[0] & 0x1FF) != 0x100:
        return unresolved('load-tile-unresolved')
    if trilinear:
        if any(decode_other_mode(mode)['texture_lod'] != 'lod'
               or decode_other_mode(mode)['texture_detail'] != 'clamp'
               or decode_other_mode(mode)['cycle_type'] != 'two-cycle' for mode in modes):
            return unresolved('mipmap-other-mode-unresolved')
        base_tile = (run.texture_scale[0] >> 8) & 7
        max_level = (run.texture_scale[0] >> 11) & 7
        if not max_level or base_tile + max_level >= 6:
            return unresolved('mipmap-tiles-unresolved')
        # Require the complete ROM mip chain, including its TMEM extents and
        # halving masks/shifts. The glTF diffuse image represents LOD zero;
        # distance-dependent native interpolation remains outside this preview.
        levels = []
        loaded = (((pa >> 12) & 0xFFF) + 1) * 2
        previous_end = 0
        for level in range(max_level + 1):
            tile = tiles.get(base_tile + level)
            if tile is None:
                return unresolved('mipmap-tiles-unresolved')
            c, a = tile
            width, height = max(1, state['width'] >> level), max(1, state['height'] >> level)
            stride = ((c >> 9) & 0x1FF) * 8
            start = ((c & 0x1FF) - (load_tile[0] & 0x1FF)) * 8
            row_bytes = (width * (4 if state['size'] == 0 else 8) + 7) // 8
            if (((c >> 19) & 3) != state['size'] or ((c >> 21) & 7) != state['format']
                    or (1 << ((a >> 4) & 15), 1 << ((a >> 14) & 15)) != (width, height)
                    or (a & 15, (a >> 10) & 15) != (level, level)
                    or stride < row_bytes or start < previous_end
                    or start + stride * height > min(loaded, 2048)):
                return unresolved('mipmap-layout-unresolved')
            levels.append({'level': level, 'width': width, 'height': height,
                           'pixel_byte_offset': pixel.offset + start, 'row_stride': stride})
            previous_end = start + stride * height
        evidence.update(preview_scope='trilinear-base-at-LOD-fraction-zero', mip_levels=levels)
    if state['size'] == 0 and (run.render_tile[1] >> 20) & 15:
        return unresolved('palette-bank-unresolved')
    payload = payloads.get(descriptor['flat_index'])
    if payload is None:
        return unresolved('payload-missing')
    row_bytes = state['width'] if state['size'] == 1 else (state['width'] + 1) // 2
    stride = ((run.render_tile[0] >> 9) & 0x1FF) * 8
    relative = ((run.render_tile[0] & 0x1FF) - (load_tile[0] & 0x1FF)) * 8
    loaded = (((pa >> 12) & 0xFFF) + 1) * 2
    extent = stride * state['height']
    # CI lookup reads indices from the lower 2 KiB of TMEM, wrapping the
    # address before applying the odd-row word swap. A complete CI8 image
    # can cross that boundary even though the later TLUT occupies upper TMEM.
    # Admit only a zero-origin, non-mip RGBA16 transfer fully backed by ROM.
    wrapped_ci8 = (extent > 2048 and state['size'] == 1 and not trilinear
                   and run.other_mode_partial is None and relative == 0
                   and load_tile[0] == 0xF5100000
                   and not (run.render_tile[0] & 0x1FF)
                   and extent <= loaded <= 4096)
    if (stride < row_bytes or stride % 8 or relative < 0
            or (relative + extent > min(loaded, 2048) and not wrapped_ci8)):
        return unresolved('tmem-span-unresolved')
    start, palette_start = pixel.offset + relative, palette.offset
    if (start < 0 or start + extent > len(payload) or palette_start < start + extent
            or palette_start + entries * 2 > len(payload)):
        return unresolved('payload-span-unresolved')
    if trilinear and (pixel.offset + previous_end > palette_start or pixel.offset < 0):
        return unresolved('mipmap-payload-span-unresolved')
    rows = []
    for y in range(state['height']):
        if wrapped_ci8:
            rows.append(bytes(payload[start + (((y * stride + x) & 0x7FF) ^ (4 if y & 1 else 0))]
                              for x in range(row_bytes)))
        else:
            row = payload[start + y * stride:start + (y + 1) * stride]
            rows.append(bytes(row[x ^ 4 if y & 1 else x] for x in range(row_bytes)))
    if wrapped_ci8:
        evidence['tmem_addressing'] = {
            'index_address_mask': '0x7FF', 'load_tmem_byte_offset': 0,
            'loaded_bytes': loaded, 'logical_image_span': extent,
            'row_stride': stride, 'odd_row_xor': 4,
            'scope': 'CI8 index reads wrap in lower TMEM; the explicit TLUT supplies palette colours.',
        }
    indices = b''.join(rows)
    colors = payload[palette_start:palette_start + entries * 2]
    if not any(value & 1 for (value,) in struct.iter_unpack('>H', colors)):
        if not zero_alpha_texture_is_invisible(run):
            return unresolved('transparent-combiner-unresolved')
        evidence['zero_alpha_preview'] = {
            'source': 'unchanged-ROM-palette-alpha',
            'combiner_alpha': 'TEXEL0 * SHADE * ENVIRONMENT',
            'blender_cycle_2': 'IN * A_IN + MEM * (1 - A_IN)',
            'coverage_alpha_replacement': False, 'depth_write': False,
            'scope': 'zero visible colour contribution; geometry retained',
        }
    encoder = encode_ci8_png if state['size'] == 1 else encode_indexed_png
    png = encoder(indices + colors, 'linear', state['width'], state['height'])
    evidence.update(flat_payload_sha1=hashlib.sha1(payload).hexdigest(),
                    render_dimensions=[state['width'], state['height']],
                    dimension_evidence=state['dimension_evidence'],
                    pixel_byte_offset=start, palette_byte_offset=palette_start,
                    pixel_sha256=hashlib.sha256(indices).hexdigest(),
                    palette_sha256=hashlib.sha256(colors).hexdigest(),
                    lookup_evidence='explicit-other-mode' if run.other_mode else 'all-ROM-segment-8-variants',
                    lookup_variant_count=len(modes))
    texture = PreviewTexture('us-rom-default', None, descriptor['flat_index'], 2, state['size'],
                             state['width'], state['height'], hashlib.sha1(png).hexdigest(), png,
                             start, palette_start)
    return texture, 'rom-default-indexed-trilinear-base' if trilinear else 'rom-default-indexed', evidence


def extract_model_preview(
    profile: str,
    rom_argument: Path | None,
    texture_root: Path,
    output: Path,
    force: bool,
    bank_index: int = DEFAULT_BANK_INDEX,
    runtime_material_path: Path | None = None,
    runtime_appearance: tuple[int, int] | None = None,
    rom_defaults: bool = False,
) -> dict[str, Any]:
    if rom_defaults and (bank_index != 0x01 or runtime_material_path is not None or runtime_appearance is not None):
        raise ValueError('--rom-defaults requires bank 01 and excludes runtime material inputs')
    if runtime_appearance is not None and runtime_material_path is None:
        raise ValueError("--runtime-appearance requires --runtime-materials")
    rom_path, source_order, digest, bundles, render_state_tables = load_model_bundles(
        profile, rom_argument, bank_index
    )
    flat_payloads = load_flat_asset_payloads(profile, rom_argument, digest)
    default_manifest = load_character_defaults(profile, rom_argument, digest) if rom_defaults else None
    object_material_context = load_object_material_context(profile, rom_argument, digest, bank_index) if bank_index in (3, 4, 9) else None
    object_contexts = {(record['bank'], record['entry'], record['segment']): record
                       for record in object_material_context['models']} if object_material_context else {}
    morph_manifest = load_character_morph_manifest(profile, rom_argument, bundles) if rom_defaults else None
    morph_models = {record["character_entry"]: record for record in morph_manifest["models"]} if morph_manifest else {}
    catalog = load_preview_texture_catalog(texture_root, digest, tuple(flat_payloads))
    runtime_material_catalog = load_runtime_material_catalog(
        runtime_material_path, digest, runtime_appearance
    )
    prepare_output(output, force)
    copied_textures: dict[PreviewTexture, str] = {}
    copied_runtime_mip_textures: set[str] = set()
    copied_runtime_multitextures: set[str] = set()
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
            character_draw_pass = None
            character_animation_clips: tuple[CharacterAnimationClip, ...] = ()
            incompatible_animation_clip_count = 0
            if bank_index == 0x01:
                geometry, character_layout = parse_character_model_geometry(
                    segment.data
                )
                character_joints = tuple(character_layout["joints"])
                if rom_defaults:
                    geometry, character_draw_pass = model_character_parts.primary_preview(
                        segment.data, geometry, character_layout)
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
            elif bank_index == 0x09 and is_attachment_model(segment.data):
                geometry, attachment_layout = parse_attachment_model(segment.data, parse_model_geometry)
                character_joints = tuple(attachment_layout["joints"]) or None
                character_pose_source = "neutral-attachment-joint-hierarchy-parent-transform-unobserved"
            else:
                geometry = parse_segment_geometry(segment, bank_index)
            source_geometry = geometry
            update_runtime_materials = {i: runtime_material_catalog[(bank_index, bundle.index, segment.index, i)]
                for i in range(len(geometry.material_runs))
                if (bank_index, bundle.index, segment.index, i) in runtime_material_catalog}
            geometry, attachment_update = apply_rom_attachment_preview_update(
                segment.data, geometry, object_contexts.get((bank_index, bundle.index, segment.index)),
                update_runtime_materials)
            geometry, omitted_zero_area_faces, omitted_zero_area_by_run = (
                omit_zero_area_preview_faces(geometry)
            )
            texture_files: dict[str, str] = {}
            gltf_texture_files: dict[str | int, str] = {}
            model_runtime_materials: dict[int, dict[str, Any]] = {}
            detail_preview_coordinates = {}
            run_records = []
            for run_index, run in enumerate(geometry.material_runs):
                default_evidence = None
                state_consensus_evidence = None
                runtime_material = runtime_material_catalog.get(
                    (bank_index, bundle.index, segment.index, run_index)
                )
                if runtime_material is not None:
                    model_sha1 = hashlib.sha1(segment.data).hexdigest()
                    if runtime_material.get("model_sha1") != model_sha1:
                        raise ValueError(
                            "runtime material record model hash does not match preview"
                        )
                    copied_mips, copied_multitextures = (
                        copy_runtime_captured_auxiliary_textures(
                            runtime_material, output
                        )
                    )
                    copied_runtime_mip_textures.update(copied_mips)
                    copied_runtime_multitextures.update(copied_multitextures)
                    model_runtime_materials[run_index] = runtime_material
                texture = runtime_captured_texture_choice(runtime_material)
                if texture is not None:
                    status = runtime_material["variants"][0]["captured_texture"]["status"]
                else:
                    texture, status = choose_preview_texture(
                        run,
                        catalog,
                        flat_payloads,
                    )
                if rom_defaults and texture is None and ('lookup-mode-unresolved' in status or status == 'no-proven-texture'):
                    candidate, candidate_status, evidence = rom_render_state_preview_texture(
                        run, catalog, flat_payloads, render_state_tables)
                    if candidate is not None:
                        texture, status, state_consensus_evidence = candidate, candidate_status, evidence
                if runtime_material is None and texture is None and ('lookup-mode-unresolved' in status or status == 'no-proven-texture'):
                    candidate, candidate_status, evidence = rom_object_preview_texture(
                        run, catalog, flat_payloads, render_state_tables,
                        object_contexts.get((bank_index, bundle.index, segment.index)))
                    if candidate is not None:
                        texture, status, state_consensus_evidence = candidate, candidate_status, evidence
                animation_evidence = None
                if runtime_material is None and texture is None and status == 'runtime-segment':
                    texture, animation_status, animation_evidence = rom_object_animation_preview_texture(
                        run, catalog, flat_payloads, render_state_tables,
                        object_contexts.get((bank_index, bundle.index, segment.index)))
                    if texture is not None:
                        status = animation_status
                binding_evidence = None
                if runtime_material is None and texture is None and status == 'runtime-segment':
                    texture, binding_status, binding_evidence = rom_object_binding_preview_texture(
                        run, catalog, flat_payloads, render_state_tables,
                        object_contexts.get((bank_index, bundle.index, segment.index)))
                    if texture is not None:
                        status = binding_status
                scene_evidence = None
                if runtime_material is None and texture is None and status == 'runtime-segment':
                    texture, scene_status, scene_evidence = rom_scene_preview_texture(
                        run, catalog, flat_payloads,
                        object_contexts.get((bank_index, bundle.index, segment.index)))
                    if texture is not None:
                        status = scene_status
                if runtime_material_references_texels(runtime_material) is False:
                    texture, status = None, "runtime-combiner-does-not-use-texture"
                if default_manifest is not None and run.pixel is not None and run.pixel.segment in (6, 7, 10, 11):
                    defaults = model_character_defaults.preview_defaults(default_manifest, bundle.index)
                    if defaults is None:
                        texture, status = None, 'rom-default-header-missing'
                    else:
                        texture, status, default_evidence = rom_default_preview_texture(
                            run, defaults, character_layout['texture_descriptors'], flat_payloads, render_state_tables)
                if texture is not None and (
                    not run.texture_enabled or not run.texture_coordinates_proven
                ):
                    texture, status = None, "runtime-texture-observed-coordinate-state-unresolved"
                if character_draw_pass is not None and not source_geometry.material_runs[run_index].face_count:
                    texture, status = None, 'excluded-secondary-draw-pass'
                    default_evidence = None
                    state_consensus_evidence = None
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
                    "rom_default_texture": default_evidence,
                    **({"rom_object_texture_animation": animation_evidence} if animation_evidence else {}),
                    **({"rom_object_texture_binding": binding_evidence} if binding_evidence else {}),
                    **({"rom_scene_texture_state": scene_evidence} if scene_evidence else {}),
                    **({"rom_texture_state_consensus": state_consensus_evidence} if state_consensus_evidence else {}),
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
                    **({"other_mode_partial": list(run.other_mode_partial)} if run.other_mode_partial is not None else {}),
                    "runtime_render_state_offset": (
                        f"0x{run.runtime_render_state_offset:X}"
                        if run.runtime_render_state_offset is not None
                        else None
                    ),
                    "texture": None,
                }
                if texture is not None and run.face_count:
                    if texture.preview_coordinate_state is not None:
                        detail_preview_coordinates[run_index] = texture.preview_coordinate_state
                        record["rom_detail_texture_preview"] = detail_texture_preview_record(
                            replace(run, preview_coordinate_state=texture.preview_coordinate_state))
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
                    texture_key: str | int = (
                        run_index
                        if texture.family == "us-runtime-captured"
                        else material
                    )
                    previous = gltf_texture_files.setdefault(
                        texture_key, relative_texture
                    )
                    if previous != relative_texture:
                        raise ValueError(
                            f"material {material} resolves to multiple preview textures"
                        )
                    if isinstance(texture_key, str):
                        texture_files[material] = relative_texture
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
                        **({'tmem_source_loads': [
                            {'flat_index': flat, 'payload_sha1': digest,
                             'tmem_byte_offset': start, 'loaded_bytes': count,
                             **({'transfer_bits': texture.tmem_load_sizes[i],
                                 'lower_tmem_bytes': count // 2 if texture.tmem_load_sizes[i] == 32 else count}
                                if texture.tmem_load_sizes else {})}
                            for i, (flat, digest, start, count) in enumerate(texture.tmem_source_loads)
                        ]} if texture.tmem_source_loads else {}),
                        **({'tmem_fetch': 'RGBA8 without TLUT: R=G=B=A=byte; RGBA32 loads split RG/BA banks'}
                           if texture.family == 'us-rgba8-tmem-composed' else {}),
                    }
                run_records.append(record)
            geometry = apply_runtime_texture_coordinates(geometry, model_runtime_materials)
            if detail_preview_coordinates:
                geometry = replace(geometry, material_runs=tuple(
                    replace(run, preview_coordinate_state=detail_preview_coordinates[i])
                    if i in detail_preview_coordinates else run
                    for i, run in enumerate(geometry.material_runs)))
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
                gltf_texture_files,
                bank_index,
                character_joints,
                character_rotations,
                character_pose_source,
                character_animation_clips,
                runtime_materials=model_runtime_materials,
                character_morphs=morph_models.get(bundle.index),
                character_draw_pass=character_draw_pass,
            )
            gltf_document = json.loads(gltf_data)
            if attachment_update is not None:
                gltf_document.setdefault("extras", {})["romAttachmentUpdate"] = attachment_update
                gltf_data = (json.dumps(gltf_document, indent=2) + "\n").encode()
            if segment.effect_source is not None:
                _, effect_layout = parse_effect_model(segment.data, parse_model_geometry, segment.effect_source)
                gltf_document.setdefault("extras", {})["romEffectModel"] = {
                    key: effect_layout[key] for key in (
                        "family", "geometry_source_entry", "geometry_source_sha1",
                        "material_source_entry", "material_source_sha1", "effect_type",
                        "preview_vertex_buffer", "vertex_buffers_identical", "appearance_status",
                        "draw_setup_commands",
                    )
                }
                gltf_data = (json.dumps(gltf_document, indent=2) + "\n").encode()
            for material in gltf_document.get("materials", []):
                extras = material.get("extras", {})
                run_index = extras.get("materialRun")
                replay = extras.get("runtimeMaterial", {}).get("lightingReplay")
                if isinstance(run_index, int) and replay is not None:
                    run_records[run_index]["runtime_lighting_replay"] = replay
            gltf_data = add_rom_texture_state_evidence(gltf_data, run_records)
            (geometry_dir / f"{stem}.gltf").write_bytes(gltf_data)
            (geometry_dir / f"{stem}.bin").write_bytes(gltf_binary)
            bind_gltf_file = bind_binary_file = None
            if bank_index == 0x01:
                bind_stem = f"{stem}-bind"
                bind_gltf_data, bind_binary = encode_gltf(
                    bundle.index,
                    segment.index,
                    geometry,
                    gltf_texture_files,
                    bank_index,
                    character_joints,
                    None,
                    None,
                    (),
                    bind_stem,
                    model_runtime_materials,
                    morph_models.get(bundle.index),
                    character_draw_pass,
                )
                bind_gltf_data = add_rom_texture_state_evidence(bind_gltf_data, run_records)
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
                    **({"morph_target_count": morph_models[bundle.index]["shape_count"]}
                       if bundle.index in morph_models else {}),
                    **({'character_draw_pass': character_draw_pass} if character_draw_pass is not None else {}),
                    **({'rom_attachment_update': attachment_update} if attachment_update is not None else {}),
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
                    if character_pose_source is not None or bank_index == 0x01 else None,
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
        "flat_asset_identity": flat_asset_identity(flat_payloads),
        "bank_index": bank_index,
        "source_texture_root": display_path(texture_root),
        "rom_character_defaults": default_manifest,
        **({'rom_object_material_context': object_material_context} if object_material_context else {}),
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
        "runtime_material_appearance": (
            {
                "trace_index": runtime_appearance[0],
                "event_index": runtime_appearance[1],
            }
            if runtime_appearance is not None
            else None
        ),
        "runtime_material_record_count": sum(
            run["runtime_material"] is not None
            for model in model_records
            for run in model["material_runs"]
        ),
        "runtime_lighting_replay_run_count": sum(
            run.get("runtime_lighting_replay", {}).get("status")
            == "captured-cbfd-vertex-load-colours"
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
        "copied_runtime_mip_texture_count": len(copied_runtime_mip_textures),
        "copied_runtime_multitexture_count": len(copied_runtime_multitextures),
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
                "mode_two_effect": "16-entry-palette-starts-at-payload-end-minus-0x20",
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
                    "mode-one palettes select payload end minus 0x200; "
                    "mode-two palettes select payload end minus 0x20"
                ),
            }
            if bank_index == 0x03
            else {
                "initial_model_slots": {
                    "function": "func_150031EC",
                    "call": "0x150033F4",
                    "segment_indices": [0, 1, 2, 3],
                    "fifth_argument": 0,
                    "effect": "mode-one palette selects payload end minus 0x200",
                },
                "object_model_instances": {
                    "function": "func_150039E0",
                    "model_table": "D_800B0E50",
                    "call": "0x150041F0",
                    "fifth_argument": 0,
                    "effect": (
                        "new placement instances select any bundle model by index and "
                        "select mode-one palettes at payload end minus 0x200"
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
                "draw_function": "func_1502F01C",
                "resolver": "func_1510D0EC",
                "descriptor_table": "D_800C5338",
                "default_header_table": "D_800D1C90",
                "default_bank": "0x11",
                "status": "ROM-default-preset" if rom_defaults else "runtime-selection",
                "special_renderer": "func_150911F4 separately selects flat IDs from D_800D24C8",
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
                "character texture segments 6, 7, 10, and 11 use a ROM default preset "
                "when --rom-defaults is selected; runtime expressions, blink changes, "
                "part visibility and native colour/combiner parity are not reproduced"
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
                "the loader places CI8 TLUTs at payload end minus 0x200 and CI4 "
                "TLUTs at payload end minus 0x20; TEXEL0/TEXEL1 "
                "mipmapped runs preserve their complete render-tile ladders but remain "
                "unlinked until their LOD blend and dynamic colours can be reproduced"
                if bank_index == 0x01
                else "bank-03 mode-one CI8 palettes use the trailing 0x200 bytes; "
                "the fifth parser argument only controls reference bookkeeping"
                if bank_index == 0x03
                else "bank-04 initial slots and placement instances use the shared "
                "mode-one trailing 0x200-byte palette contract; source image spans "
                "still require complete display-list load evidence"
                if bank_index == 0x04
                else "bank-09 mode-one CI8 palettes use payload end minus 0x200, "
                "independently of the parser's reference bookkeeping table"
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
        if morph_manifest is not None:
            manifest["character_morphs"] = {key: value for key, value in morph_manifest.items() if key != "models"}
            (output / "character-morphs.json").write_text(json.dumps(morph_manifest, indent=2) + "\n")
            manifest["character_morphs"]["file"] = "character-morphs.json"
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
            0x09: "Start with geometry/0258-00.gltf for a directly ROM-backed object. ",
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
            (
                "This corpus uses ROM default facial selectors for segments 6, 7, 10, "
                "and 11, with zero blink selectors and no expression override. Pixel "
                "and TLUT offsets come from ROM display lists; no captures are inputs. "
                if rom_defaults else
                "Character facial segments 6, 7, 10, and 11 depend on character state. "
                "Use --rom-defaults for their ROM default preset, or an appearance-specific "
                "runtime manifest for captured pixel and TLUT spans. "
            )
            if bank_index == 0x01
            else ""
        )
        + "See manifest.json for per-run status and known runtime limits. "
        + (
            f"This preview embeds {manifest['runtime_material_record_count']} "
            "ROM-validated runtime material records. Unanimous sampler and alpha "
            "state is translated to glTF. Unambiguous lit runs use GLideN64-equivalent "
            "floating-point vertex colours. Every observed non-mipmap combiner is "
            "classified; explicit mip and second-texture images are copied beside the "
            "preview and referenced from material extras, while standard glTF displays "
            "only the base texture. Ambiguous lighting remains unbaked. "
            + (
                "Those records are filtered to runtime appearance "
                f"{runtime_appearance[0]}:{runtime_appearance[1]}; unobserved runs "
                "do not inherit another task's state. "
                if runtime_appearance is not None
                else "The embedded aggregate catalogs multiple observed appearances; "
                "it does not claim that every variant occurred simultaneously. "
            )
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
            "Dynamic appearances outside the selected ROM preset or captured state remain "
            "unresolved.\n"
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
                elif bank_index == 0x09 and is_attachment_model(segment.data):
                    geometry, layout = parse_attachment_model(segment.data, parse_model_geometry)
                    character_joints = tuple(layout["joints"]) or None
                else:
                    geometry = parse_segment_geometry(segment, bank_index)
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
    _, _, digest, bundles, _ = load_model_bundles(profile, rom_argument, bank_index)
    if bank_index == 0x09:
        points = load_emission_point_manifest(profile, rom_argument)
        if (points['asset_count'], points['point_count'], points['decoded_size']) != (20, 1963, 31408):
            raise ValueError('US bank-09 emission-point inventory changed')
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
        morphs = load_character_morph_manifest(profile, rom_argument, bundles)
        if (morphs["model_count"], morphs["shape_count"], morphs["part_payload_count"], morphs["decoded_size"]) != (2, 23, 69, 41792):
            raise ValueError("US bank-13 character morph inventory changed")
        expressions = load_character_expression_manifest(profile, rom_argument, digest)
        if (expressions['source_bundle_count'], expressions['model_count'], expressions['preset_count'], expressions['decoded_size']) != (186, 22, 258, 2580):
            raise ValueError('US bank-11 character expression inventory changed')
        programs = expressions['animation_programs']
        if (len(programs), sum(p['record_count'] for p in programs), sum(p['decoded_size'] for p in programs)) != (5, 6, 96):
            raise ValueError('US expression action-program inventory changed')
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
        if bank_index == 0x09 and is_attachment_model(bundle.data):
            geometry, attachment_layout = parse_attachment_model(bundle.data, parse_model_geometry)
            regions = {section["name"]: bundle.data[section["offset"]:section["offset"] + section["size"]]
                       for section in attachment_layout["sections"]}
            rebuilt = encode_attachment_model(geometry, attachment_layout, regions)
        elif bank_index == 0x09 and bundle.segments[0].effect_source is not None:
            geometry, effect_layout = parse_effect_model(bundle.data, parse_model_geometry, bundle.segments[0].effect_source)
            regions = {section["name"]: bundle.data[section["offset"]:section["offset"] + section["size"]]
                       for section in effect_layout["sections"]}
            rebuilt = encode_effect_model(geometry, effect_layout, regions)
        elif bank_index == 0x09:
            rebuilt = rebuild_direct_model(bundle.data, parse_geometry_for_bank(bundle.data, bank_index))
        if rebuilt != bundle.data:
            raise ValueError(
                f"bank-{bank_index:02X} entry {bundle.index} did not round-trip"
            )
        for segment in bundle.segments:
            if not segment.data:
                continue
            geometry = parse_segment_geometry(segment, bank_index)
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
                if run.texture_enabled is None:
                    external_runtime_texture_face_count += run.face_count
                elif not run.texture_enabled:
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


def parse_runtime_appearance(value: str) -> tuple[int, int]:
    fields = value.split(":")
    if len(fields) != 2:
        raise argparse.ArgumentTypeError(
            "runtime appearance must be TRACE_INDEX:EVENT_INDEX"
        )
    try:
        trace_index, event_index = (int(field, 10) for field in fields)
    except ValueError as error:
        raise argparse.ArgumentTypeError(
            "runtime appearance indices must be decimal integers"
        ) from error
    if trace_index < 0 or event_index < 0:
        raise argparse.ArgumentTypeError(
            "runtime appearance indices must be non-negative"
        )
    return trace_index, event_index


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "action",
        choices=(
            "batch",
            "survey",
            "extract",
            "preview",
            "atlas",
            "activity",
            "compose",
            "materials",
            "collision",
            "coverage",
            "scene-consumers",
            "scene-assemblies",
            "constructors",
            "verify",
            "validate",
            "inspect",
            "submitted",
            "discover-submitted",
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
        "--rom-defaults", action="store_true",
        help="bank-01 preview with ROM default facial selectors, without capture inputs",
    )
    parser.add_argument(
        "--model-root", type=Path, help="existing model outputs for coverage"
    )
    parser.add_argument(
        "--blender-validation", type=Path,
        help="per-file Blender validation report for coverage",
    )
    parser.add_argument(
        "--scene-manifest", type=Path,
        help="additional proven scene consumers for coverage",
    )
    parser.add_argument(
        "--runtime-materials",
        type=Path,
        help="runtime-correlated material manifest to embed in preview glTF files",
    )
    parser.add_argument(
        "--task-runtime-materials",
        type=Path,
        help=(
            "renderer-return material manifest used for exact per-cluster "
            "character composition appearances"
        ),
    )
    parser.add_argument(
        "--activity-manifest",
        type=Path,
        help=(
            "character activity manifest used to conservatively refine ambiguous "
            "bank-01 material correlations"
        ),
    )
    parser.add_argument(
        "--runtime-appearance",
        type=parse_runtime_appearance,
        help=(
            "limit a preview material manifest to one captured graphics task, "
            "formatted TRACE_INDEX:EVENT_INDEX"
        ),
    )
    parser.add_argument(
        "--trace",
        type=Path,
        action="append",
        help="runtime draw-state JSONL input (repeatable for materials)",
    )
    parser.add_argument(
        "--draw-trace",
        type=Path,
        action="append",
        help="character renderer entry/return JSONL input (repeatable for activity)",
    )
    parser.add_argument(
        "--attachment-trace", type=Path, action="append",
        help="attachment renderer selected-part/return JSONL input (repeatable for compose)",
    )
    parser.add_argument(
        "--part-table-trace",
        type=Path,
        action="append",
        help="character renderer part-table JSONL input (repeatable for activity)",
    )
    parser.add_argument("--force", action="store_true")
    parser.add_argument("--validation-config", type=Path,
                        help="batch validation corpus and regression render cases")
    parser.add_argument("--inspection-config", type=Path,
                        help="named model selection for self-contained Blender inspection files")
    parser.add_argument("--blender", type=Path, help="Blender executable for batch validation")
    parser.add_argument("--skip-blender", action="store_true",
                        help="leave Blender evidence incomplete in batch validation")
    parser.add_argument("--skip-renders", action="store_true",
                        help="leave visual regression evidence incomplete in batch validation")
    args = parser.parse_args()
    if args.rom_defaults and args.action != 'preview':
        parser.error('--rom-defaults applies only to preview')
    return args


def main() -> int:
    if len(sys.argv) > 1 and sys.argv[1] == "batch":
        try:
            from scripts.model_batch import main as batch_main
        except ModuleNotFoundError:
            from model_batch import main as batch_main
        return batch_main(sys.argv[2:])
    args = parse_args()
    bank_index = int(args.bank or "04", 16)
    try:
        if args.action == "constructors":
            try:
                from scripts.model_constructor_analysis import report
            except ModuleNotFoundError:
                from model_constructor_analysis import report
            result = report(sys.modules[__name__], args.profile, args.rom, int(args.bank or '09', 16))
            output = args.output or ROOT / f"build/assets/models/reference/constructors-bank{result['bank']:02}.json"
            output.parent.mkdir(parents=True, exist_ok=True)
            output.write_text(json.dumps(result, indent=2) + '\n')
            print(f"Constructor diagnosis: {result['counts']}; report: {display_path(output)}")
            return 0
        elif args.action == "discover-submitted":
            try:
                from scripts.model_submitted_pose import discover_cases
            except ModuleNotFoundError:
                from model_submitted_pose import discover_cases
            if len(args.trace or []) != 1 or args.runtime_materials is None:
                raise ValueError("discover-submitted requires one --trace and --runtime-materials")
            result = discover_cases(args.trace[0].resolve(), args.runtime_materials.resolve(),
                                    (args.model_root or ROOT / "build/assets/models").resolve())
            output = (args.output or ROOT / "build/assets/models/submitted-discovery.json").resolve()
            output.parent.mkdir(parents=True, exist_ok=True)
            output.write_text(json.dumps(result, indent=2) + "\n")
            counts = Counter(row['status'] for row in result['candidates'])
            print(f"Submitted candidates: {dict(counts)}; report: {display_path(output)}")
            return 0
        elif args.action == "submitted":
            try:
                from scripts.model_submitted_pose import export_cases
            except ModuleNotFoundError:
                from model_submitted_pose import export_cases
            manifest = export_cases((args.validation_config or ROOT / "config/model-validation.json").resolve())
            output = (args.output or ROOT / "build/assets/models/us-submitted-poses/manifest.json").resolve()
            output.parent.mkdir(parents=True, exist_ok=True)
            output.write_text(json.dumps(manifest, indent=2) + "\n")
            print(f"Exported {len(manifest['models'])} verified submitted poses: {display_path(output)}")
            return 0
        elif args.action == "inspect":
            try:
                from scripts.model_inspection import publish_inspection
            except ModuleNotFoundError:
                from model_inspection import publish_inspection
            output = (args.output or ROOT / "build/assets/models/inspect").resolve()
            manifest = publish_inspection(
                (args.inspection_config or ROOT / "config/model-inspection.json").resolve(), output)
            print(f"Prepared {len(manifest['models'])} self-contained inspection models: {display_path(output)}")
            if manifest.get('review_models'):
                print(f"Extracted review tab: {len(manifest['review_models'])} additional ROM records")
            return 0
        elif args.action == "validate":
            try:
                from scripts.model_validation import validate_batch
            except ModuleNotFoundError:
                from model_validation import validate_batch
            output = (args.output or ROOT / "build/assets/models/validation").resolve()
            report = validate_batch(
                (args.validation_config or ROOT / "config/model-validation.json").resolve(), output,
                blender=args.blender, skip_blender=args.skip_blender, skip_renders=args.skip_renders)
            print(f"Validation: {report['status']}; report: {display_path(output / 'report.json')}")
            print(f"Review: {display_path(output / 'review.html')}")
            return 1 if report["status"] == "failed" else 0
        elif args.action == "scene-assemblies":
            try:
                from scripts.model_scene_assemblies import export_assemblies
            except ModuleNotFoundError:
                from model_scene_assemblies import export_assemblies
            output = (args.output or ROOT / "build/assets/models/rom-scene-assemblies").resolve()
            manifest = export_assemblies(ROOT / "config/model-scene-assemblies.json",
                (args.model_root or ROOT / "build/assets/models/rom-only").resolve(), output,
                args.profile, args.rom)
            print(f"Exported {len(manifest['models'])} static ROM scene assemblies: {display_path(output)}")
            return 0
        elif args.action == "scene-consumers":
            try:
                from scripts.model_scene_consumers import extract_scene_consumers
            except ModuleNotFoundError:
                from model_scene_consumers import extract_scene_consumers
            output = (
                args.output or ROOT / "build/assets/models/us-scene-consumers.json"
            ).resolve()
            manifest = extract_scene_consumers(args.profile, args.rom, output)
            print(
                f"Resolved {manifest['initial_slot_model_count']} initial scene slots and "
                f"{manifest['resolved_placement_count']} placements to "
                f"{manifest['model_association_count']} models"
            )
            print(f"Manifest: {display_path(output)}")
        elif args.action == "coverage":
            try:
                from scripts.model_coverage import extract_coverage
            except ModuleNotFoundError:
                from model_coverage import extract_coverage
            root = (args.model_root or ROOT / "build/assets/models").resolve()
            output = (args.output or root / "us-coverage.json").resolve()
            manifest = extract_coverage(
                args.profile,
                args.rom,
                root,
                (args.textures or ROOT / "build/assets/textures").resolve(),
                output,
                tuple(
                    path.resolve()
                    for path in (args.runtime_materials, args.task_runtime_materials)
                    if path
                ),
                args.activity_manifest.resolve() if args.activity_manifest else None,
                (args.blender_validation or root / "blender-validation.json").resolve(),
                args.scene_manifest.resolve() if args.scene_manifest else None,
            )
            summary = manifest["summary"]
            print(
                f"Audited {summary['model_count']} models, "
                f"{summary['material_run_count']} material runs, "
                f"{summary['source_face_count']} source faces"
            )
            print(f"Coverage: {display_path(output)}")
        elif args.action == "activity":
            output = args.output or ROOT / "build/assets/models/us-character-activity"
            if not output.is_absolute():
                output = ROOT / output
            manifest = extract_character_activity(
                args.profile,
                args.rom,
                tuple(args.trace or ()),
                args.runtime_materials,
                output,
                args.force,
                tuple(args.draw_trace or ()),
                tuple(args.part_table_trace or ()),
            )
            print(
                f"Recorded {manifest['active_entry_count']} active bank-01 entries "
                f"across {manifest['snapshot_count']} character-pool snapshots; "
                f"{manifest['active_without_runtime_material_count']} active entries "
                "still lack runtime-correlated materials"
            )
            print(f"Manifest: {display_path(output / 'manifest.json')}")
        elif args.action == "compose":
            if args.activity_manifest is None:
                raise ValueError("compose requires --activity-manifest")
            output = (
                args.output
                or ROOT / "build/assets/models/us-character-compositions"
            )
            if not output.is_absolute():
                output = ROOT / output
            texture_root = args.textures or ROOT / "build/assets/textures"
            if not texture_root.is_absolute():
                texture_root = ROOT / texture_root
            manifest = extract_character_composition_previews(
                args.profile,
                args.rom,
                args.activity_manifest,
                output,
                args.force,
                texture_root,
                args.runtime_materials,
                args.task_runtime_materials,
                tuple(args.attachment_trace or ()),
            )
            print(
                f"Prepared {manifest['model_count']} trace-resolved character "
                f"composition previews from {manifest['source_cluster_count']} "
                f"exact static clusters and {manifest['face_count']} drawable faces"
            )
            print(
                f"Linked {manifest['neutral_linked_texture_run_count']} neutral and "
                f"{manifest['posed_linked_texture_run_count']} posed material runs to "
                f"{manifest['copied_texture_count']} proven texture PNGs"
            )
            print(f"Manifest: {display_path(output / 'manifest.json')}")
        elif args.action == "materials":
            output = args.output or ROOT / "build/assets/models/us-runtime-materials"
            if not output.is_absolute():
                output = ROOT / output
            manifest = extract_runtime_materials(
                args.profile,
                args.rom,
                tuple(args.trace or ()),
                output,
                args.force,
                args.activity_manifest,
            )
            print(
                f"Prepared {manifest['material_record_count']} runtime-correlated "
                f"materials with {manifest['variant_count']} variants from "
                f"{manifest['correlated_draw_observation_count']} draw observations "
                f"across {manifest['appearance_count']} captured appearances"
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
                args.runtime_appearance,
                args.rom_defaults,
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
            if args.runtime_appearance is not None:
                print(
                    "Runtime material appearance: "
                    f"{args.runtime_appearance[0]}:{args.runtime_appearance[1]} "
                    f"({manifest['runtime_material_record_count']} assigned runs)"
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
