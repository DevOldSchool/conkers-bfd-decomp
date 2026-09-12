"""Reviewed US scene texture selectors; deterministic inspection states."""
from __future__ import annotations

import hashlib
import struct

CONSUMERS = (
    (0x150031EC, 712, 'ed48d58ffb38dab90c140a0d547dbdae13f3225a'),
    (0x1510B9D0, 1424, '0798a739b422132025c7dc9162df8e604ef74b54'),
    (0x150C8600, 304, '7585760801c2b8790eeb5c9fc435464cd4df0ac3'),
    (0x15100464, 412, 'e7e6ed36b46da330c2acb00680ee165b302643a4'),
    (0x150DFBD0, 216, '2e78a0f9427ae847f3d5b6d6027f970b1988e044'),
    (0x150D765C, 308, '905c5386623f60a44cc7176d098b904678afd917'),
    (0x1500FE30, 364, '57f8573f00d8abf897791aa17b6ba9b7a63cde6e'),
    (0x150DF8C0, 96, '864ced8b7340cf8ac1d97af58cb302c0ba923779'),
    (0x150DF920, 688, '8a67ffea41741e286d084ca94fd9f3a20a99daed'),
    (0x151749A0, 88, 'd350e4d4f79a0ffd6ea52f6bbc910c3be69063f4'),
    (0x15100340, 292, '9921edc177db233cbc99a42e761990ba9b0500ba'),
    (0x1510F800, 32, 'e60ff68750b9704132b657981b121501e0de60fd'),
    (0x150A49F4, 256, '471d41da99ec832b971383c5b8dc40724a39b6db'),
    (0x1515D914, 2404, 'a0ca1f285c354276fa25543fe54a68ef023f1813'),
    (0x1515E278, 452, '9aede05e0c808ac36f5e87a4e57eedbff3a1dc14'),
    (0x1515E43C, 264, '10f5a925aaef37de09823e0b6075d24ebd3db534'),
    (0x1515EB84, 244, 'a626452bb72fb6e1e0ee13cb22c40e53ab26f4ce'),
    (0x1515EC78, 764, '1605c00be3c252ce639ea2c95a9cd9f3ae21880d'),
)
DATA = {
    0x800A2C2C: (140, '5479fadf0d63d5d069923ba245c0c877ad92dba5'),
    0x80088810: (8, '5d097d2018ebacdadad73baaa03810e0539506f1'),
    0x80088900: (8, '5d097d2018ebacdadad73baaa03810e0539506f1'),
    0x80090230: (20, '67381cb10fc7bacae1b465e85dce2cc32c3304f2'),
    0x80090244: (20, '9aa679e7c4858ffaaf5e1c51db6f125a681e930c'),
    0x80090324: (52, '1633f6e3a7c1a212943b1ee7eca9a748186f1417'),
}


def checked(raw, base, address, size):
    offset = address - base
    if offset < 0 or offset + size > len(raw):
        raise ValueError('scene texture evidence exceeds ROM region')
    return raw[offset:offset + size]


def scene_contexts(code, code_base, data, data_base):
    for address, size, expected in CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError('scene texture consumer changed')
    for address, (size, expected) in DATA.items():
        if hashlib.sha1(checked(data, data_base, address, size)).hexdigest() != expected:
            raise ValueError('scene texture table changed')
    words = lambda address, count: list(struct.unpack(
        f'>{count}I', checked(data, data_base, address, count * 4)))
    return decoded_contexts(words)


def decoded_contexts(words):
    """Mirror reviewed selector formulas after verifying the complete consumers.

    These explicit inspection inputs do not claim a current or initial frame.
    Table alternatives are retained even when one state is selected for glTF.
    """
    result = []
    expected_dispatch = {19: 0x1510BB6C, 20: 0x1510BB4C,
                         26: 0x1510BB5C, 51: 0x1510BB8C}
    for scene, target in expected_dispatch.items():
        if words(0x800A2C2C + (scene - 19) * 4, 1) != [target]:
            raise ValueError('scene texture dispatch changed')
        bindings = {}
        def bind(segment, address, count, selected, formula):
            frames = words(address, count)
            if not 0 <= selected < len(frames):
                raise ValueError('scene texture preview selector exceeds table')
            bindings[str(segment)] = {'pixel_segment': segment,
                'frame_array': f'0x{address:08X}', 'frames': frames,
                'selected_index': selected, 'selected_flat': frames[selected],
                'selector_formula': formula}
        if scene == 19:
            # Inactive branch selects +0x20; active branch selects +0x24 + phase*4.
            for segment in range(2, 5):
                bind(segment, 0x80090344, 5, 0, 'inactive: 0; active: 1 + phase (0..3)')
            helper = 0x150DFBD0
            state = {'active_slots': [False, False, False], 'phase': 0}
        elif scene == 20:
            pointers = words(0x80088810, 2)
            for segment in range(1, 11):
                bank = (segment - 1) // 5  # func_1500FE30 initializes each group.
                bind(segment, pointers[bank], 5, 0, 'clamp(s16 phase >> 8, 0, 4)')
            helper = 0x150C8600
            state = {'type_by_segment': [0] * 5 + [1] * 5, 'phase': [0] * 10}
        elif scene == 26:
            bind(2, 0x80090324, 3, 0, '(u8 phase >> 2) % 3')
            bind(3, 0x80090324, 3, 1, '((u8 phase >> 2) + 1) % 3')
            for segment in range(4, 9):
                bind(segment, 0x80090330, 2, 0, 'u8 switch (0 or 1)')
            helper = 0x15100464
            state = {'phase': 0, 'switches': [0] * 5}
        else:
            pointers = words(0x80088900, 2)
            for segment in range(2, 8):
                bank = int(segment >= 6)
                selected = (13 * (segment - 2)) % 5
                bind(segment, pointers[bank], 5, selected,
                     '((u16 phase >> 8) + 13 * (segment - 2)) % 5')
            helper = 0x150D765C
            state = {'phase': 0}
        proof = {'helper': f'func_{helper:08X}', 'dispatch_target': f'0x{target:08X}',
                 'preview_state': state, 'bindings': bindings,
                 'preview_policy': 'Explicit ROM selector inspection state; not a sampled or initial gameplay frame.'}
        result.append({'bank': 4, 'entry': scene, 'segment': 0,
            'renderer': 'func_1510B9D0', 'scene_texture_state': proof,
            'scope': 'Conditional primary terrain draw with scene binding branch enabled; gameplay state, visibility, lighting and raster parity unresolved.'})
    return result
