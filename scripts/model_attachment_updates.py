"""ROM-proven attachment texture and SetTileSize inspection updates."""
from __future__ import annotations

import hashlib
import struct
from dataclasses import replace

try:
    from scripts.model_attachment_texture_bindings import CONSUMERS as SHARED_CONSUMERS
    from scripts.model_object_texture_animation import checked
except ModuleNotFoundError:
    from model_attachment_texture_bindings import CONSUMERS as SHARED_CONSUMERS
    from model_object_texture_animation import checked

CONSUMERS = SHARED_CONSUMERS + (
    (0x150D83D8, 440, '73966a1646839351ecf831823d1709127b61db0b'),
    (0x1510D0EC, 648, '47b67aab9ed8a4eb1706ced5424981ff21373aba'),
)
DATA_SPANS = (
    (0x80086FEC, '8009d21001000000'),
    (0x8009D210, '50091301000000020000000000004101'),
    (0x8008420C, '150d83d8'),
    (0x80096FE0, '15031c00'),
    (0x80090304, '00001c23'),
    (0x800A0B14, '3c23d70a'),
)
MODEL_SHA1 = 'd9667ef7783f87f1dbfd616d278539a7f7664fcb'


def initial_tile_word(scale):
    """The reviewed counter-zero arm sets accumulator 50, then writes F2."""
    f32 = lambda value: struct.unpack('>f', struct.pack('>f', value))[0]
    value = f32(f32(f32(50) * scale) * f32(120))
    origin = int(f32(value + f32(2)))  # MIPS trunc.w.s, not host rounding.
    return 0xF2002000 | (origin & 0xFFF)


def material_context(code, code_base, data, data_base):
    for address, size, expected in CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError('attachment UV update consumer changed')
    for address, expected in DATA_SPANS:
        raw = bytes.fromhex(expected)
        if checked(data, data_base, address, len(raw)) != raw:
            raise ValueError('attachment UV update action or data changed')
    scale = struct.unpack('>f', checked(data, data_base, 0x800A0B14, 4))[0]
    word = initial_tile_word(scale)
    if word != 0xF200203E:
        raise ValueError('attachment initial tile origin changed')
    selector = {'descriptor_0x38': 0, 'next_descriptor_0x3C': 50,
                'parent_0x84': 0, 'excluded_parent_0x84': 397,
                'descriptor_0x17': -1, 'descriptor_0x1A': 0,
                'renderer_fifth_argument': 0}
    scope = ('Initial texture and tile-origin preset; stored vertices and joints. '
             'Parent ownership, later updates, animation, visibility, lighting and native appearance unresolved.')
    state = {
        'kind': 'direct-pixel-segments', 'action': 102,
        'action_header_address': '0x80086FEC', 'action_record_address': '0x8009D210',
        'action_record_sha1': hashlib.sha1(bytes.fromhex(DATA_SPANS[1][1])).hexdigest(),
        'update_function': 'func_150D83D8', 'update_dispatch_address': '0x8008420C',
        'table_address': '0x80090304', 'selector': selector,
        'bindings': {'6': {'pixel_segment': 6, 'flats': [7203], 'selected_index': 0,
                           'selected_flat': 7203, 'image_layout': [8, 64, 0, 3], 'payload_bytes': 2048}},
        'preview_policy': 'Explicit initial attachment texture and UV preset; not a sampled or proven reachable gameplay state',
        'scope': scope,
    }
    update = {'source_model_sha1': MODEL_SHA1, 'updater': 'func_150D83D8',
              'selector': selector, 'command_offset': 0x340,
              'source_command': [0xF2002002, 0x0001E0FE],
              'preview_command': [word, 0x0001E0FE], 'affected_material_runs': [0],
              'texture_dimensions': [8, 64],
              'dimension_evidence': 'unclamped masks 3/6 and complete 2048-byte RGBA32 LoadBlock',
              'scope': scope}
    return {'consumers': [{'function': f'func_{a:08X}', 'size': n, 'sha1': h} for a, n, h in CONSUMERS],
            'models': [{'bank': 9, 'entry': 80, 'segment': 0, 'renderer': 'func_150311C4',
                        'texture_binding': state, 'geometry_update': update, 'scope': scope}],
            'capture_inputs': []}


def preview_geometry(data, geometry, context, runtime_materials=None):
    """Apply the paired UV update only when its ROM texture preset is used."""
    update = (context or {}).get('geometry_update')
    if update is None:
        return geometry, None
    # A captured material carries its own image/coordinate state. Do not
    # combine that state with this ROM-only inspection preset.
    if 0 in (runtime_materials or {}):
        return geometry, None
    if ((context['bank'], context['entry'], context['segment']) != (9, 80, 0)
            or update['source_model_sha1'] != MODEL_SHA1
            or hashlib.sha1(data).hexdigest() != MODEL_SHA1):
        raise ValueError('attachment UV update model differs from ROM')
    # The loaded pointer table's first primary list starts at 0x320. Locate
    # the first F2 as the native updater does; the pinned source proves bounds.
    offset = next((o for o in range(0x320, len(data) - 7, 8) if data[o] == 0xF2), None)
    if (offset != update['command_offset'] or offset != 0x340
            or list(struct.unpack_from('>II', data, offset)) != update['source_command']
            or update['source_command'] != [0xF2002002, 0x0001E0FE]
            or update['preview_command'] != [0xF200203E, 0x0001E0FE]
            or update['affected_material_runs'] != [0] or update['texture_dimensions'] != [8, 64]):
        raise ValueError('attachment UV update display-list command changed')
    if len(geometry.material_runs) != 2:
        raise ValueError('attachment UV update material spans changed')
    run = geometry.material_runs[0]
    if (run.first_face != 0 or run.face_count != 16 or run.tile_bounds != tuple(update['source_command'])
            or run.render_tile != (0xF5180400, 0x00018030)
            or run.pixel is None or run.pixel.image_command != 0xFD180000
            or (run.pixel.segment, run.pixel.offset, run.pixel.flat_index) != (6, 0, None)
            or run.pixel.load_command != (0xF3000000, 0x071FF000)
            or run.palette is not None or run.texture_dimensions is not None):
        raise ValueError('attachment UV update lacks its complete mask texture')
    # Preserve image dimensions when scrolling SetTileSize's origin. The
    # full repeating 8x64 image is proven by masks, load and pixel size above.
    adjusted = replace(run, tile_bounds=tuple(update['preview_command']), texture_dimensions=(8, 64))
    return replace(geometry, material_runs=(adjusted, geometry.material_runs[1])), update
