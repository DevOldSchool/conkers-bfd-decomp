"""Complete texture storage and selector contracts, independent of preview policy."""
from __future__ import annotations

import hashlib
import struct
from dataclasses import replace

try:
    from scripts import model_assets as models
except ModuleNotFoundError:
    import model_assets as models


FORMATS = {(2, 0): 'ci4', (2, 1): 'ci8', (0, 2): 'rgba16', (0, 3): 'rgba32',
           (3, 0): 'ia4', (3, 1): 'ia8', (3, 2): 'ia16', (4, 0): 'i4', (4, 1): 'i8'}


def layered_contract(run, payload: bytes, *, storage_extensions: bool = False) -> dict | None:
    """Require explicit contiguous TMEM levels covering the entire pixel load."""
    state = models.texture_coordinate_state(run)
    if not state or run.pixel is None:
        return None
    fmt = FORMATS.get((state['format'], state['size']))
    pixel = run.pixel
    if (fmt is None or pixel.mode != 0 or pixel.external
            or pixel.image_command not in (0xFD100000, 0xFD180000, 0xFD500000,
                                           0xFD700000, 0xFD900000)
            or pixel.load_command is None or pixel.load_command[0] != 0xF3000000
            or pixel.load_command[1] & 0xfff):
        return None
    transfer = (pixel.image_command >> 19) & 3
    loaded = (((pixel.load_command[1] >> 12) & 0xfff) + 1) * (1, 1, 2, 4)[transfer]
    matches = [(i, tile) for i, (binding, tile) in enumerate(run.texture_loads)
               if binding == pixel]
    if not matches:
        return None
    load_index, load = matches[-1]
    # Render tiles are frequently changed after LoadBlock. Only its captured
    # load-time descriptor establishes the destination and transfer size.
    if (load is None or load[0] & 511 or ((load[0] >> 19) & 3) != transfer
            or any(binding is None for binding, _ in run.texture_loads[load_index + 1:])):
        return None
    palette_size = 0
    if fmt in ('ci4', 'ci8'):
        palette_size = 32 if fmt == 'ci4' else 512
        palette = run.palette
        if (palette is None or palette.flat_index != pixel.flat_index
                or palette.mode != (2 if fmt == 'ci4' else 1)
                or palette.image_command != 0xFD100000 or palette.load_command is None
                or palette.load_command[0] != 0xF0000000
                or (((palette.load_command[1] >> 14) & 1023) + 1) * 2 != palette_size):
            return None
        loads = [tile for binding, tile in run.texture_loads if binding == palette]
        if (not loads or loads[-1] is None or loads[-1][0] & 511 != 256
                or (run.render_tile[1] >> 20) & 15):
            return None
    pixel_end = len(payload) - palette_size
    alignment = pixel_end - loaded
    boundary = 128 if fmt == 'rgba32' else 64
    if alignment and (not storage_extensions or not 0 < alignment < boundary
                      or pixel_end != (loaded + boundary - 1) // boundary * boundary
                      or any(payload[loaded:pixel_end])):
        return None
    overlap = max(0, loaded - 2048) if palette_size else 0
    if loaded > 4096 or (overlap and not storage_extensions):
        return None
    if overlap and not any(binding == run.palette for binding, _ in run.texture_loads[load_index + 1:]):
        # Retain the authored transfer sequence, including the later TLUT
        # overwrite. This is complete source storage, not a full rendered view.
        return None
    tiles = {index: (cmd, arg) for index, cmd, arg in run.render_tiles}
    base, last = (run.texture_scale[0] >> 8) & 7, (run.texture_scale[0] >> 11) & 7
    if base != 0 or last >= 6 or tiles.get(base) != run.render_tile:
        return None
    factor = 2 if fmt == 'rgba32' else 1
    bits = (4, 8, 16, 32)[state['size']]
    levels, cursor, clamped_npot = [], 0, False
    for level in range(last + 1):
        tile = tiles.get(base + level)
        if tile is None:
            return None
        cmd, arg = tile
        width, height = max(1, state['width'] >> level), max(1, state['height'] >> level)
        stride, start = ((cmd >> 9) & 511) * 8 * factor, (cmd & 511) * 8 * factor
        if (cmd >> 19) & 31 != (run.render_tile[0] >> 19) & 31:
            return None
        if last:
            if (arg & 15, (arg >> 10) & 15) != (level, level):
                return None
            for dimension, mask, clamp in ((width, (arg >> 4) & 15, arg & 0x200),
                                           (height, (arg >> 14) & 15, arg & 0x80000)):
                if 1 << mask != dimension:
                    if (not storage_extensions or not clamp
                            or 1 << mask != 1 << (dimension - 1).bit_length()):
                        return None
                    clamped_npot = True
        if (not stride or stride * 8 < bits * width or start != cursor
                or start + stride * height > loaded):
            return None
        levels.append({'level': level, 'offset': start, 'width': stride * 8 // bits,
                       'height': height, 'visible_width': width, 'visible_height': height,
                       'bytes': stride * height})
        cursor = start + stride * height
    if cursor != loaded:
        return None
    contract = {'format': fmt, 'width': levels[0]['width'], 'height': levels[0]['height'],
                'row_layout': 'tmem-odd-row-32bit-swap', 'source_origin': 'bottom-left',
                'levels': levels, 'palette_size': palette_size}
    if alignment:
        contract['zero_alignment'] = {'offset': loaded, 'size': alignment, 'alignment': boundary}
    if overlap:
        contract['pixel_tlut_overlap_bytes'] = overlap
    if clamped_npot:
        contract['clamped_npot_dimensions'] = True
    return contract


def bound_contract(run, preview, payload: bytes) -> dict | None:
    """Relocate only pointers authenticated by the ROM selector preview resolver."""
    if (preview is None or run.pixel is None or run.pixel.segment not in (6, 7, 10, 11)
            or run.pixel.offset != 0 or preview.flat_index is None):
        return None
    resource = preview.flat_index
    pixel = replace(run.pixel, flat_index=resource, mode=0, segment=None, offset=None)
    palette = run.palette
    if palette is not None:
        size = {(2, 0): 32, (2, 1): 512}.get((preview.format, preview.size))
        if (size is None or palette.segment != run.pixel.segment
                or palette.offset != len(payload) - size):
            return None
        palette = replace(palette, flat_index=resource, mode=2 if size == 32 else 1,
                          segment=None, offset=None)
    mapped = replace(run, pixel=pixel, palette=palette, texture_loads=tuple(
        (pixel if ref == run.pixel else palette if ref == run.palette else ref, tile)
        for ref, tile in run.texture_loads))
    return layered_contract(mapped, payload, storage_extensions=True)


def authored_contract(data: bytes, geometry, run, payload: bytes) -> tuple[dict, dict] | None:
    """Prove a complete storage tile authored after the current texture load.

    These draws retain tile 1 and may sample earlier TMEM contents. A fresh,
    explicitly bounded tile 0 describes the stored image, not the final draw.
    Accept only the exact native command sequence, never an inherited tile.
    """
    pixel, palette = run.pixel, run.palette
    if (pixel is None or palette is None or pixel.flat_index is None
            or pixel.mode != 0 or palette.mode != 1 or pixel.flat_index != palette.flat_index
            or pixel.image_command != 0xFD100000 or palette.image_command != 0xFD100000
            or run.texture_scale is None or run.texture_scale[0] != 0xD7000902
            or pixel.load_command is None or palette.load_command is None
            or not 0 <= run.first_face < len(geometry.face_command_offsets)):
        return None
    begin, end = geometry.display_list_offset, geometry.face_command_offsets[run.first_face]
    if begin < 0 or end > len(data) or end <= begin or (end - begin) % 8:
        return None
    words = list(struct.iter_unpack('>II', data[begin:end]))
    starts = [i for i, pair in enumerate(words) if pair == (pixel.image_command, pixel.flat_index)]
    if not starts:
        return None
    start = starts[-1]
    commands = words[start:]
    prefix = [(0xFD100000, pixel.flat_index), (0xE6000000, 0), pixel.load_command,
              (0xE7000000, 0), (0xE6000000, 0),
              (0xFD100000, 0x400000 | pixel.flat_index), palette.load_command, (0xE7000000, 0)]
    if (len(commands) not in (10, 11) or commands[:8] != prefix
            or (len(commands) == 11 and commands[10] != (0xD9FFFFFF, 0x400))):
        return None
    tile, bounds = commands[8:10]
    if (tile[0] >> 24 != 0xF5 or bounds[0] >> 24 != 0xF2
            or tile[1] >> 24 != 0 or bounds[1] >> 24 != 0
            or (0, *tile) not in run.render_tiles):
        return None
    storage_run = replace(run, render_tile=tile, tile_bounds=bounds, texture_dimensions=None,
                          texture_scale=(0xD7000002, run.texture_scale[1]))
    contract = layered_contract(storage_run, payload)
    if contract is None or contract['format'] != 'ci8':
        return None
    offset = begin + start * 8
    return contract, {'scope': 'authored-source-storage-not-composed-render',
                      'storage_tile': 0, 'draw_tile': 1,
                      'draw_texture_scale': list(run.texture_scale),
                      'command_start': offset, 'command_end': end,
                      'command_sha256': hashlib.sha256(data[offset:end]).hexdigest(),
                      'commands': [list(pair) for pair in commands]}


def detail_contract(run, preview, payload: bytes) -> dict | None:
    """Retain all indexed mip storage and the native IA4 detail plane.

    The preview must come from direct_detail_indexed_preview_texture, including
    ROM render-state resolution where needed. It proves formats, bounds, loads,
    and mip/detail semantics; here we additionally require complete storage.
    """
    if (preview is None or preview.family != 'us-direct-detail-indexed-base'
            or run.pixel is None or preview.flat_index != run.pixel.flat_index
            or run.palette is None):
        return None
    tiles = {i: (cmd, arg) for i, cmd, arg in run.render_tiles}
    bounds = {i: (cmd, arg) for i, cmd, arg in run.detail_tile_bounds}
    first = ((run.texture_scale[0] >> 8) & 7) + 1
    maximum = (run.texture_scale[0] >> 11) & 7
    palette_size = 32 if preview.size == 0 else 512
    pixel_end = len(payload) - palette_size
    levels, cursor = [], 0
    for level, index in enumerate([*range(first, first + maximum + 1), first - 1]):
        tile, bound = tiles.get(index), bounds.get(index)
        if tile is None or bound is None:
            return None
        state = models.texture_coordinate_state(replace(
            run, render_tile=tile, tile_bounds=bound, texture_dimensions=None))
        fmt = FORMATS.get((state['format'], state['size']))
        role = 'detail' if index == first - 1 else 'mip'
        if fmt != ('ia4' if role == 'detail' else ('ci4' if preview.size == 0 else 'ci8')):
            return None
        stride, start = ((tile[0] >> 9) & 511) * 8, (tile[0] & 511) * 8
        bits = 8 if fmt == 'ci8' else 4
        size = stride * state['height']
        if not stride or start != cursor or start + size > pixel_end:
            return None
        levels.append({'level': level, 'tile': index, 'role': role, 'format': fmt,
                       'offset': start, 'width': stride * 8 // bits, 'height': state['height'],
                       'visible_width': state['width'], 'visible_height': state['height'], 'bytes': size})
        cursor += size
    gap = pixel_end - cursor
    if gap and (not 0 < gap < 64 or pixel_end != (cursor + 63) // 64 * 64
                or any(payload[cursor:pixel_end])):
        return None
    contract = {'format': levels[0]['format'], 'width': levels[0]['width'],
                'height': levels[0]['height'], 'row_layout': 'tmem-odd-row-32bit-swap',
                'source_origin': 'bottom-left', 'levels': levels, 'palette_size': palette_size,
                'mixed_detail': True}
    if gap:
        contract['zero_alignment'] = {'offset': cursor, 'size': gap, 'alignment': 64}
    return contract


def expression_selectors(initial: dict, preset: dict, consumers: dict,
                         *, action_program: dict | None = None) -> dict | None:
    """Selector writes follow morph writes and the optional constructor action.

    This describes stored textures, not a rendered morph or animation state.
    Keep the shared gallery's stricter expression-preview policy unchanged.
    """
    if preset['reserved_byte']:
        return None
    if preset['animation_selector']:
        if (action_program is None or action_program['selector'] != preset['animation_selector']
                or action_program['native_action'] != preset.get('native_action')
                or not action_program['operations']
                or len(action_program['operations']) != action_program['record_count']
                or any(op['dispatch_kind'] not in (1, 2)
                       or op['operation'] != 'attachment-constructor' or op['bank'] != 9
                       for op in action_program['operations'])):
            return None
    selectors, codes = preset['blink_selector_bytes'], preset['actor_blink_codes']
    overrides = preset['texture_descriptor_overrides']
    if (len(selectors) != 2 or len(overrides) != 2
            or any(not isinstance(v, int) or not 0 <= v <= 245 for v in selectors)
            or codes != [v + 10 for v in selectors]
            or any(not isinstance(v, int) or not 0 <= v <= 255 for v in overrides)):
        return None
    indices = {**initial['descriptor_indices'], '6': selectors[0], '7': selectors[1]}
    for segment, override in zip(('10', '11'), overrides):
        if override:
            indices[segment] = override
    selection = {
                'stored_preset': preset, 'consumer_sha1': consumers,
                'selection_policy': 'texture-storage-only-no-morph-preview-claim'}
    if action_program is not None:
        selection['action_program'] = action_program
        selection['selection_policy'] = 'texture-storage-after-constructor-no-runtime-activation-claim'
    return {**initial, 'preset': f'ROM-expression-{preset["index"]}-selector-only',
            'descriptor_indices': indices, 'expression_texture_selection': selection}


def action_selector_choices(manifest: dict, entry: int) -> list[tuple[str, dict]]:
    """Use only Conker's separately verified attachment-only action programs.

    The native caller ignores the action's return value and writes these
    selectors afterwards. No parent-modification dispatch or rendered
    attachment state is admitted by the constructor evidence module.
    """
    if entry != 0 or entry not in manifest['entries']:
        return []
    constructors = manifest['expression_constructors']
    if constructors['family'] != 'ROM-expression-attachment-constructors':
        raise ValueError('expression action lacks verified constructor evidence')
    programs = {p['selector']: p for p in constructors['programs']}
    initial, choices = manifest['entries'][entry], []
    for preset in initial['expression_presets']:
        if not preset['animation_selector']:
            continue
        program = programs.get(preset['animation_selector'])
        selected = expression_selectors(initial, preset, constructors['consumer_sha1'],
                                        action_program=program)
        if selected is not None:
            choices.append((f'action-expression-{preset["index"]}', selected))
    return choices


def selector_choices(manifest: dict, entry: int, rom: bytes) -> list[tuple[str, dict]]:
    initial = manifest['entries'].get(entry)
    if initial is None:
        return []
    raw = rom[int(initial['rom_start'], 16):int(initial['rom_end'], 16)]
    raw = models.decode_rzip_chunk(raw).data if initial['compressed'] else raw
    if hashlib.sha1(raw).hexdigest() != initial['sha1']:
        raise ValueError('character selector source changed')
    header = raw[16:80]
    choices = [('initializer', initial)]
    for phase in (1, 2):
        choices.append((f'blink-{phase}', {
            **initial, 'preset': f'ROM-blink-table-{phase}', 'descriptor_indices': {
                **initial['descriptor_indices'], '6': header[8 + phase], '7': header[11 + phase]}}))
    preset = manifest.get('instance_texture_presets', {}).get(entry)
    if preset:
        for variant in range(len(preset['descriptor_indices'])):
            changed = {**manifest, 'instance_texture_presets': {
                **manifest['instance_texture_presets'], entry: {**preset, 'selected_variant': variant}}}
            choices.append((f'instance-{variant}', models.model_character_defaults.preview_defaults(changed, entry)))
    for preset in initial['expression_presets']:
        default = expression_selectors(initial, preset, manifest['expression_consumers'])
        if default is not None:
            choices.append((f'expression-{preset["index"]}', default))
    return choices
