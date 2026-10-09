"""Resolve texture consumers using runtime IDs, retaining physical storage names."""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

try:
    from scripts import (texture_assets as t, texture_ci8, texture_rgba16,
                         texture_native, hud_assets as h, hud_additional_artwork as artwork,
                         texture_model_catalog)
except ModuleNotFoundError:
    import texture_assets as t
    import texture_ci8
    import texture_rgba16
    import texture_native
    import hud_assets as h
    import hud_additional_artwork as artwork
    import texture_model_catalog


def runtime_context(path: Path, rom: bytes):
    """The size table includes empty slots; a stream ordinal is not a resource ID."""
    _, layout = h.resolve_rom('us', path)
    if hashlib.sha1(rom).hexdigest() not in layout['normalized_sha1']:
        raise ValueError('texture catalog reference ROM changed')
    game = h.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    family = h.parse_hud_assets(game.code, game.data,
                               layout['game_vram'], layout['game_data_vram'])
    size_bytes = h.data_slice(game.data, layout['game_data_vram'],
                             h.RUNTIME_FLAT_SIZE_TABLE,
                             h.RUNTIME_FLAT_SIZE_TABLE + h.RUNTIME_FLAT_ASSET_COUNT * 2)
    sizes = struct.unpack(f'>{h.RUNTIME_FLAT_ASSET_COUNT}H', size_bytes)
    if [i for i, size in enumerate(sizes) if not size] != h.RUNTIME_FLAT_IDENTITY['empty_runtime_slots']:
        raise ValueError('US runtime flat asset empty slots changed')
    entries = tuple(h.iter_indexed_flat_rzip_entries(
        rom[layout['flat_assets_start']:layout['flat_assets_end']], sizes))
    return layout, entries, family


def load_extended(root: Path, rom: bytes, *, excluded_indices=()) -> dict[int, tuple[t.TextureAsset, dict]]:
    """Only full-payload, reviewed contracts qualify; duplicate consumers count once."""
    path = root / 'roms/baserom.us.z64'
    digest = hashlib.sha1(rom).hexdigest()
    layout, entries, hud = runtime_context(path, rom)
    by_id = {entry.index: entry for entry in entries}
    ordinals = {entry.index: i for i, entry in enumerate(entries)}
    result = {}

    def add(resource, family, fmt, width, height, row, origin='bottom-left'):
        entry = by_id[resource]
        index = ordinals[resource]
        texture = t.TextureAsset(index, layout['flat_assets_start'] + entry.start,
                                 layout['flat_assets_start'] + entry.end, entry.data)
        contract = {'identity': 'runtime-resource', 'runtime_resource_id': resource,
                    'family': family, 'format': fmt, 'width': width,
                    'height': height, 'row_layout': row, 'source_origin': origin}
        # Multiple consumers can view the same full payload in different shapes.
        # The first reviewed contract wins; the physical range is credited once.
        result.setdefault(index, (texture, contract))

    for family, module, fmt in (
            ('ci8-proven', texture_ci8, 'ci8'),
            ('rgba16-proven', texture_rgba16, 'rgba16'),
            ('native-proven', texture_native, None)):
        manifest, payloads = module.survey('us', path, flat_entries=entries)
        if manifest['normalized_sha1'] != digest:
            raise ValueError('texture catalog reference ROM changed')
        for record in manifest['textures']:
            resource = record['flat_index']
            entry = by_id[resource]
            if (payloads[resource] != entry.data
                    or int(record['rom_start'], 16) != layout['flat_assets_start'] + entry.start
                    or int(record['rom_end'], 16) != layout['flat_assets_start'] + entry.end):
                raise ValueError(f'conflicting texture payload contracts: {resource}')
            add(resource, family, fmt or record['format'], record['width'],
                record['height'], record['row_layout'])

    survey = t.survey_rectangular_textures('us', path, flat_entries=entries)
    if survey['normalized_sha1'] != digest:
        raise ValueError('texture catalog reference ROM changed')
    for record in survey['proven_textures']:
        resource = record['flat_index']
        add(resource, '1056-proven', 'ci4', record['width'], record['height'],
            t.row_layout_for_flat_index(resource))

    tiled_ids = set(range(t.TILED_OVERRIDE_FIRST_INDEX,
                         t.TILED_OVERRIDE_FIRST_INDEX + t.TILED_OVERRIDE_ENTRY_COUNT))
    for group in survey['runtime_tiled_ci4_contract']['groups']:
        for view in group['views']:
            tiled_ids.update(range(view['first_flat_index'], view['last_flat_index'] + 1))
    # Use actual runtime ranges, never the old preview-only neighboring streams.
    formats = {1056: ('ci4', 64, 32), 2560: ('ci8', 64, 32)}
    for resource in sorted(tiled_ids):
        try:
            fmt, width, height = formats[len(by_id[resource].data)]
        except KeyError as error:
            raise ValueError(f'unsupported proven tiled texture storage: {resource}') from error
        add(resource, 'tiled-views', fmt, width, height,
            t.row_layout_for_flat_index(resource))

    dimensions = h.resource_preview_dimensions(hud.sprites)
    for resource in h.reachable_flat_indices(hud.sprites):
        width, height = dimensions[resource]
        payload = by_id[resource].data
        preview = h.resource_preview_image(resource, payload, width, height)
        if (preview is None or preview.bytes_used != len(payload)
                or preview.texture_format not in ('rgba32', 'ia4', 'ia8', 'ia16', 'i4', 'i8')):
            raise ValueError(f'HUD resource lacks a full native texture contract: {resource}')
        add(resource, 'hud-selector', preview.texture_format, preview.width,
            preview.height, preview.row_layout, 'top-left')

    for _, _, resources, width, height, fmt in artwork.ARTWORK:
        for resource in resources:
            if texture_native.packed_row_size(fmt, width) * height != len(by_id[resource].data):
                raise ValueError(f'HUD artwork size differs from reviewed contract: {resource}')
            add(resource, 'hud-additional-artwork', fmt, width, height,
                t.ROW_LAYOUT_TMEM, 'top-left')
    occupied = set(result) | set(excluded_indices)
    excluded_ids = {entry.index for index, entry in enumerate(entries) if index in occupied}
    for resource, contract in texture_model_catalog.load(root, rom, entries, excluded_ids).items():
        if resource in excluded_ids:
            raise ValueError('model catalog returned an already classified texture')
        add(resource, contract['family'], contract['format'], contract['width'],
            contract['height'], contract['row_layout'], contract['source_origin'])
        result[ordinals[resource]][1]['consumer'] = contract['consumer']
        if 'levels' in contract:
            result[ordinals[resource]][1].update(levels=contract['levels'],
                                                palette_size=contract['palette_size'])
            for key in ('zero_alignment', 'pixel_tlut_overlap_bytes', 'clamped_npot_dimensions', 'mixed_detail'):
                if key in contract:
                    result[ordinals[resource]][1][key] = contract[key]
    return result
