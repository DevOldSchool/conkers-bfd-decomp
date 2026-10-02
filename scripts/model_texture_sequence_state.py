"""The bounded texture-frame state transition in the US ROM's 1511A494.

Callers must authenticate rows with model_object_texture_animation.animation_table.
This module describes one invocation, without choosing a runtime state or clock.
"""
from __future__ import annotations


UPDATER_ADDRESS = 0x1511A494
UPDATER_SIZE = 616
UPDATER_SHA1 = 'c896da27caa019639fe040e1d5bf9034f2663673'


def _integer(value, low, high, name):
    if type(value) is not int or not low <= value <= high:
        raise ValueError(f'{name} must be an integer in {low}..{high}')
    return value


def step(row, packed_state):
    """Advance one authenticated row using the native packed state word.

    The native high halfword is a signed increment, not merely a direction bit.
    The low halfword is an unsigned counter. Unsupported native out-of-array
    reads and counter values that cannot be packed independently are rejected.
    No generic modulo or repeated reflection is substituted for the ROM code.
    """
    if not isinstance(row, dict):
        raise ValueError('texture sequence row must be a mapping')
    frames = row.get('frames')
    if not isinstance(frames, (list, tuple)) or not 1 <= len(frames) <= 255:
        raise ValueError('texture sequence must contain 1..255 frame words')
    for flat in frames:
        _integer(flat, 0, 0xFFFFFFFF, 'frame flat index')
    period = _integer(row.get('frame_period'), 1, 255, 'frame period')
    ping_pong = row.get('ping_pong')
    if type(ping_pong) is not bool:
        raise ValueError('ping_pong must be a boolean')
    _integer(packed_state, 0, 0xFFFFFFFF, 'packed state')

    increment = packed_state >> 16
    if increment & 0x8000:
        increment -= 0x10000
    if increment == 0:
        increment = 1
    counter = (packed_state & 0xFFFF) + increment
    span = len(frames) * period
    if ping_pong:
        if counter < 0:
            counter, increment = period, 1
        elif counter >= span:
            counter, increment = (len(frames) - 1) * period, -1
    elif counter >= span:
        counter -= span
        increment = 1

    # The native signed DIV truncates toward zero. For the admitted nonnegative
    # counter domain this is integer division; negative or overflowing counters
    # would also corrupt the independent halfword fields in the final OR store.
    if not 0 <= counter <= 0xFFFF:
        raise ValueError('native texture counter is outside the supported packed range')
    index = counter // period
    if not 0 <= index < len(frames):
        raise ValueError('native texture frame index is outside the ROM frame array')
    return {'packed_state': ((increment & 0xFFFF) << 16) | counter,
            'counter': counter, 'increment': increment,
            'frame_index': index, 'flat_index': frames[index]}


def description():
    """Machine-readable semantics; source authentication belongs to the caller."""
    return {
        'updater': f'func_{UPDATER_ADDRESS:08X}',
        'consumer_bytes': UPDATER_SIZE, 'consumer_sha1': UPDATER_SHA1,
        'source_validation': 'Require a row from the ROM-guarded animation_table before applying this helper.',
        'input': {'packed_state': 'u32; high16 signed increment, low16 unsigned counter',
                  'frame_count': 'u8, 1..255', 'frame_period': 'u8, 1..255'},
        'order': ['Read signed increment; substitute +1 when it is zero.',
                  'Add the increment to the unsigned low-halfword counter.',
                  'Apply the selected boundary rule once.',
                  'Divide the counter by period, then select the frame.',
                  'Store (increment << 16) | counter as a 32-bit word.'],
        'ping_pong': {'below_zero': {'counter': 'period', 'increment': 1},
                      'at_or_above_count_times_period': {
                          'counter': '(count - 1) * period', 'increment': -1}},
        'loop': {'at_or_above_count_times_period': {
                    'counter': 'counter - count * period', 'increment': 1},
                 'subtractions': 1, 'negative_counter_correction': False},
        'limits': 'Reject resulting counters outside 0..65535 and frame indices outside the supplied array. No modulo or repeated reflection.',
        'scope': ('One native texture-selection helper invocation. No FPS, elapsed time, '
                  'starting state or gameplay reachability is inferred. Wrapper UV/vertex '
                  'updates and conditional dispatcher timing are outside this controller.'),
    }
