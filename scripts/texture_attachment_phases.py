"""Finite ROM attachment frame witnesses; no gameplay activation claim."""
from __future__ import annotations

import copy
import hashlib
import math
import struct

try:
    from scripts import hud_assets as h, model_attachment_texture_bindings as attachments
except ModuleNotFoundError:
    import hud_assets as h
    import model_attachment_texture_bindings as attachments


MODELS = {19: 'bdf11181cd8cf26d16a5ab1ec8cf615fb47e4437',
          49: 'aedeb22c5efa1e267f024a961ff146f56e58e935'}
DATA = ((0x80090274, '00000cb200000cb300000cb400000cb500000cb600000cb700000cb800000cb900000cba'),
        (0x800902B4, '00000547'),
        (0x800A1B40, '3e2aaaab'),
        (0x800A0B10, '3d70f0f1'))
# Avoid conversion boundaries. Each frame is an explicit conditional witness,
# not evidence that the parent animation actually reaches it in gameplay.
WITNESSES = ((52, 0), (49, 1), (46, 2), (43, 3), (40, 4), (37, 5), (61, 7), (64, 8))


def f32(value):
    return struct.unpack('>f', struct.pack('>f', value))[0]


def phase_index(frame):
    """The three reviewed arms of 150F56B0, with single-precision steps."""
    if not math.isfinite(frame):
        raise ValueError('unreviewed attachment frame')
    frame = f32(frame)
    if 36 <= frame <= 51:
        return math.trunc(f32(6 * f32(1 - f32(f32(frame - 36) * 0.0625))))
    if 51 < frame <= 54:
        return 0
    if 60 < frame <= 65:
        scale = struct.unpack('>f', bytes.fromhex('3e2aaaab'))[0]
        return 7 + math.trunc(f32(2 * f32(f32(frame - 60) * scale)))
    raise ValueError('unreviewed attachment frame')


def verified_choices(code, code_base, data, data_base):
    shared = attachments.material_context(code, code_base, data, data_base)
    for address, expected in DATA:
        raw = bytes.fromhex(expected)
        if h.data_slice(data, data_base, address, address + len(raw)) != raw:
            raise ValueError('attachment phase table or constant changed')
    original = {r['entry']: r['texture_binding'] for r in shared['models']
                if r['entry'] in MODELS}
    result = {19: [], 49: []}
    for entry, frame, index in [(19, 23, 0)] + [(49, f, i) for f, i in WITNESSES]:
        if entry == 49 and phase_index(frame) != index:
            raise ValueError('attachment frame witness no longer selects its image')
        address, size = (0x800902B4, 4) if entry == 19 else (0x80090274, 36)
        raw = h.data_slice(data, data_base, address, address + size)
        resource = struct.unpack(f'>{size // 4}I', raw)[index]
        state = copy.deepcopy(original[entry])
        state['table_address'] = f'0x{address:08X}'
        state['table_sha1'] = hashlib.sha1(raw).hexdigest()
        selector = state['selector']
        selector.pop('excluded_parent_0x84')
        selector.update(parent_0x84=13 if entry == 19 else 174,
                        parent_animation_frame=frame, table_index=index)
        state['bindings']['6'].update(flats=[resource], selected_index=0)
        state['preview_policy'] = 'Explicit ROM animation frame witness; not sampled gameplay'
        state['scope'] = ('Complete source storage conditional on this parent animation and frame; '
                          'activation, pose, visibility, lighting and native appearance unresolved.')
        proof = {'native_consumers': shared['consumers'], 'binding': state,
                 'data_guards': [{'address': f'0x{a:08X}', 'bytes': b} for a, b in DATA]}
        if entry == 19:
            # At frame 23, trunc(70 * ((frame-23) * C) + 2) == 2.
            # The first F2 word is therefore unchanged, as is its second word.
            proof['uv_update'] = {'frame': 23, 'first_f2_offset': 1024,
                                  'before_after': 'f2002002000fe07e',
                                  'selected_uls': 2, 'geometry_changed': False}
        result[entry].append((state, proof))
    return result


def check_model(entry, raw):
    if hashlib.sha1(raw).hexdigest() != MODELS[entry]:
        raise ValueError('attachment phase model changed')
    if entry == 19 and raw[1024:1032] != bytes.fromhex('f2002002000fe07e'):
        raise ValueError('attachment frame 23 no longer preserves texture coordinates')


def load(root, rom):
    _, layout = h.resolve_rom('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() not in layout['normalized_sha1']:
        raise ValueError('attachment phase reference ROM changed')
    game = h.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    return verified_choices(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
