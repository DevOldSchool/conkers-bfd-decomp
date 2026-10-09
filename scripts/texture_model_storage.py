"""Complete texture storage and selector contracts, independent of preview policy."""
from __future__ import annotations

import hashlib

try:
    from scripts import model_assets as models
except ModuleNotFoundError:
    import model_assets as models


FORMATS = {(2, 0): 'ci4', (2, 1): 'ci8', (0, 2): 'rgba16', (0, 3): 'rgba32',
           (3, 0): 'ia4', (3, 1): 'ia8', (3, 2): 'ia16', (4, 0): 'i4', (4, 1): 'i8'}


def layered_contract(run, payload: bytes) -> dict | None:
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
    if loaded != pixel_end or loaded > (2048 if palette_size else 4096):
        return None
    tiles = {index: (cmd, arg) for index, cmd, arg in run.render_tiles}
    base, last = (run.texture_scale[0] >> 8) & 7, (run.texture_scale[0] >> 11) & 7
    if base != 0 or last >= 6 or tiles.get(base) != run.render_tile:
        return None
    factor = 2 if fmt == 'rgba32' else 1
    bits = (4, 8, 16, 32)[state['size']]
    levels, cursor = [], 0
    for level in range(last + 1):
        tile = tiles.get(base + level)
        if tile is None:
            return None
        cmd, arg = tile
        width, height = max(1, state['width'] >> level), max(1, state['height'] >> level)
        stride, start = ((cmd >> 9) & 511) * 8 * factor, (cmd & 511) * 8 * factor
        if (cmd >> 19) & 31 != (run.render_tile[0] >> 19) & 31:
            return None
        if last and ((1 << ((arg >> 4) & 15), 1 << ((arg >> 14) & 15)) != (width, height)
                     or (arg & 15, (arg >> 10) & 15) != (level, level)):
            return None
        if (not stride or stride * 8 < bits * width or start != cursor
                or start + stride * height > pixel_end):
            return None
        levels.append({'level': level, 'offset': start, 'width': stride * 8 // bits,
                       'height': height, 'visible_width': width, 'visible_height': height,
                       'bytes': stride * height})
        cursor = start + stride * height
    if cursor != pixel_end:
        return None
    return {'format': fmt, 'width': levels[0]['width'], 'height': levels[0]['height'],
            'row_layout': 'tmem-odd-row-32bit-swap', 'source_origin': 'bottom-left',
            'levels': levels, 'palette_size': palette_size}


def expression_selectors(initial: dict, preset: dict, consumers: dict) -> dict | None:
    """Selector writes are unconditional after morph writes when action is zero.

    This describes stored textures, not a rendered morph or animation state.
    Keep the shared gallery's stricter expression-preview policy unchanged.
    """
    if preset['animation_selector'] or preset['reserved_byte']:
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
    return {**initial, 'preset': f'ROM-expression-{preset["index"]}-selector-only',
            'descriptor_indices': indices, 'expression_texture_selection': {
                'stored_preset': preset, 'consumer_sha1': consumers,
                'selection_policy': 'texture-storage-only-no-morph-preview-claim'}}


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
