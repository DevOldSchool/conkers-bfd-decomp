"""ROM-proven digit selectors for bank-09's four-digit timer model."""
from __future__ import annotations

import hashlib
import struct

try:
    from scripts.model_object_texture_animation import checked
except ModuleNotFoundError:
    from model_object_texture_animation import checked


CONSUMERS = (
    (0x15093878, 68, 'c56384d3d2abd16a21d08fd633b729741368243f'),
    (0x150938BC, 668, '408ac2cab82dc86156ae7babdaa7190a63162942'),
    (0x1518C900, 260, '38d05a33437a0f688bda1b2cf2ac6299b9aede8e'),
    (0x15168E54, 180, 'cbc1245a3f5d3846756b7c360d39675df6521c34'),
    (0x15168E34, 32, 'edfbe5742959d43dfa06d389f8a448dd015aa75f'),
    (0x1510D0EC, 648, '47b67aab9ed8a4eb1706ced5424981ff21373aba'),
    (0x150A7D00, 160, '3d54de78c27073ce272064b1221db73d683a2611'),
)
GUARDS = (
    (0x15093880, 0x0D463240), (0x15093884, 0x240400BA),
    (0x1509388C, 0xAC222448), (0x1518C934, 0x24180009),
    (0x150938D8, 0x2416001E), (0x150938DC, 0x2417003C),
    (0x15093900, 0x3C140000), (0x15093904, 0x24100004),
    (0x15093910, 0x269411AD), (0x15093968, 0x2413000A),
    (0x150939A4, 0x0D44343B), (0x150939C4, 0x3C01DB06),
    (0x150939CC, 0xAC690000), (0x150939D4, 0xAC620004),
    (0x150939D8, 0x24010003), (0x15093A7C, 0x2610FFFF),
    (0x15093A80, 0x1600FFBA), (0x15093AD8, 0x0D429F40),
    (0x15093B0C, 0x3C0DDE00), (0x15093B18, 0x8DCE2448),
    (0x15093B24, 0xAC8E0004),
)


def digit_selectors(ticks):
    """Mirror the pinned renderer for a nonnegative signed 32-bit timer value.

    The loop writes seconds units/tens, then minutes units/tens. Higher minute
    digits are discarded by the four-place display, as in the native loop.
    """
    if type(ticks) is not int or not 0 <= ticks <= 0x7FFFFFFF:
        raise ValueError('timer preset must be a nonnegative signed 32-bit tick count')
    seconds = ticks // 30
    minutes = seconds // 60
    return {1: minutes // 10 % 10, 2: minutes % 10,
            3: seconds % 60 // 10, 4: seconds % 10}


def material_context(code, code_base, *, preview_ticks=0):
    for address, size, expected in CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError(f'timer consumer changed: 0x{address:08X}')
    for address, expected in GUARDS:
        if checked(code, code_base, address, 4) != struct.pack('>I', expected):
            raise ValueError('timer selector or submission instruction changed')
    selectors = digit_selectors(preview_ticks)
    flats = list(range(4525, 4535))
    scope = ('Stored geometry and UVs with a selected ROM timer value; visibility, '
             'projection, lighting, gameplay time and native appearance remain unresolved.')
    state = {
        'kind': 'direct-pixel-segments',
        'initializer': 'func_15093878', 'loader': 'func_1518C900',
        'renderer': 'func_150938BC', 'texture_loader': 'func_1510D0EC',
        'model_pointer': '0x800D2448', 'timer_address': '0x800D2450',
        'preview_state': {'ticks': preview_ticks, 'ticks_per_second': 30,
                          'display': f'{selectors[1]}{selectors[2]}:{selectors[3]}{selectors[4]}'},
        'bindings': {str(segment): {
            'pixel_segment': segment, 'flats': flats.copy(),
            'selected_index': digit, 'selected_flat': flats[digit],
            'image_layout': [16, 32, 3, 0], 'payload_bytes': 256,
        } for segment, digit in selectors.items()},
        'selector_formula': '4525 + decimal digit; segments 1..4 are MMSS left to right',
        'preview_policy': 'Explicit timer inspection preset; not an initial or sampled gameplay state',
        'scope': scope,
    }
    return {'consumers': [{'function': f'func_{a:08X}', 'size': n, 'sha1': h}
                          for a, n, h in CONSUMERS],
            'models': [{'bank': 9, 'entry': 186, 'segment': 0,
                        'renderer': 'func_150938BC', 'texture_binding': state,
                        'scope': scope}], 'capture_inputs': []}
