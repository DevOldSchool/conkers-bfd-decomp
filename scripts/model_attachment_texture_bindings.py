"""Reviewed US action-record attachment texture presets, derived from the ROM."""
from __future__ import annotations

import hashlib
import struct

try:
    from scripts.model_object_texture_animation import checked
except ModuleNotFoundError:
    from model_object_texture_animation import checked

# Whole functions guard the reviewed argument/field flow, including constructor
# initialization, update dispatch and the ordinary renderer's final segment binds.
CONSUMERS = (
    (0x15083568, 356, '419012702249e321c26fc2badb49949b0aafa0fc'),
    (0x15030AF4, 608, 'f506f08cf457bc3d9bb7a751c0c1381e2ddd39a9'),
    (0x1502FFD8, 384, 'd03a13f16beb1aacae4a2c964a393164e8a477c4'),
    (0x1502FE10, 456, '8637778facf0ce5e9a4cd03316b390e02fdf84e2'),
    (0x15031A50, 452, '433d396431907cf2bdef8fc872dbcd46dd31d274'),
    (0x15030468, 1676, '52db878e843d5fb82917548b53bc82259a72f2d3'),
    (0x15030E08, 396, 'b1673819535984e56f9c71ae7c0568ca7f64dea4'),
    (0x150311C4, 1896, 'e276f4d4cce00c18939e50ff942094540aae5f1e'),
    (0x150D82BC, 284, '8a08adfcc3dec022262fa26d155464260156102e'),
    (0x15031E2C, 80, '2fd7cd5fea4298bc218c5e2612686bce6e3f9896'),
    (0x150F56B0, 932, '4ef46b71a2d55a38b2188433d3366133f0f9255a'),
)
# Only these headers/records are reviewed, not a guessed extent for the entire
# action table. Kind 2 uses the separate proof below.
ACTIONS = (
    (9, 0x8009CE90, '13150101000000000000000000000000'),
    (21, 0x8009CF30, '1909020100000000000d019f000e0000'),
    (76, 0x8009D120, '31090401000000000000000000004101'),
)
# These action records use self-contained flat textures. The initializer's
# pinned 95..129 default arm is a no-op and updater zero is never dispatched.
DIRECT_ACTIONS = (
    (48, 0x8009D8C0, '790c0001000000000000000000000000'),
    (167, 0x8009D8F0, '80020001000000000000000000000000'),
)
UPDATERS = {1: 0x150D82BC, 2: 0x15031E2C, 4: 0x150F56B0}
# Model, selected ROM table span, and its exact contents. Updater 49's other
# animation branches are not advertised as proven variants.
TEXTURES = {
    19: (0x800902B0, (1352,)),
    25: (0x800902BC, (2644, 2645, 2646)),
    49: (0x8009028C, (3256,)),
}

ANIMATED_CONSUMERS = (
    (0x150337E4, 84, '215e1823593dbd426d6e8814a3e7928ab4bd6568'),
    (0x1503F62C, 396, 'b678946246dbc937322777d197d874c3dbd0839b'),
    (0x1503F5B8, 116, '9c1459ec3091739935c855401477cde06d507404'),
    (0x15035D6C, 636, '2175df0c3739180be2804e0a8b9aaac99c0ef866'),
    (0x1510D0EC, 648, '47b67aab9ed8a4eb1706ced5424981ff21373aba'),
)

INDEXED_ANIMATED_CONSUMERS = (
    (0x15031FC8, 4592, '704af990a303a59dc929a5359c5bbaf435b44fa8'),
    (0x150859AC, 272, '052c8a8b5e3be9c51932ac759fcd5a9ae38e3d56'),
)
# Exact action records and indirect branch targets used by the two presets.
# 141's initializer reads progress slot (0, 6); this is not an RNG call.
INDEXED_ANIMATED_DATA = (
    (0x8008721C, '8009d06001000000'),
    (0x8009D060, '8d090502000007010000000000004101'),
    (0x80086EEC, '8009d14001000000'),
    (0x8009D140, '930e0502000010000000000000000000'),
    (0x800841D4, '15031fc8'),
    (0x80096F6C, '15031ba8'),
    (0x80097240, '15032578'),
    (0x800970E8, '150320b4'),
    (0x8009716C, '15032150'),
    (0x8009D9B8, '15085a9c'),
    (0x80090228, '00001c0d00001c0e'),
    (0x800902D0, '00000ecf00000ed0'),
)


def indexed_animated_action_bindings(code, code_base, data, data_base):
    """Two explicit updater-5 presets with ROM-proven inline CI palettes.

    Shared constructor and kind-2 loader/renderer checks belong to
    material_context. These presets establish texture selection, not gameplay
    ownership or reachability of the selected parent/animation state.
    """
    for address, size, expected in INDEXED_ANIMATED_CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError('indexed animated attachment consumer changed')
    for address, expected in INDEXED_ANIMATED_DATA:
        raw = bytes.fromhex(expected)
        if checked(data, data_base, address, len(raw)) != raw:
            raise ValueError('indexed animated attachment action or branch data changed')
    contexts = []
    for entry, action, address, table_address, flats, selector in (
        (141, 172, 0x8009D060, 0x80090228, [7181, 7182],
         {'descriptor_0x17': 7, 'parent_0x04': 0,
          'progress_0x800D2148': 0, 'initializer_branch': 'progress value < 100',
          'selector_formula': 'progress slot (0, 6) < 100 selects table[0], otherwise table[1]'}),
        (147, 70, 0x8009D140, 0x800902D0, [3791, 3792],
         {'descriptor_0x17': 16, 'parent_0x04': 90, 'parent_0x2E8': 0,
          'initializer_branch': 'no-op for this model',
          'selector_formula': 'parent +0x2E8 == 0 selects table[0], otherwise table[1]'}),
    ):
        selector.update(descriptor_0x1A=0, descriptor_0x48='non-null attachment animation',
                        parent_0x84=0, parent_0x2D0=0, renderer_fifth_argument=0)
        raw = checked(data, data_base, address, 16)
        table = checked(data, data_base, table_address, 8)
        state = {
            'kind': 'attachment-payload', 'action': action,
            'action_header_address': f'0x{0x80086CC4 + (action - 1) * 8:08X}',
            'action_record_address': f'0x{address:08X}', 'action_record_index': 0,
            'action_record_sha1': hashlib.sha1(raw).hexdigest(),
            'update_function': 'func_15031FC8', 'update_dispatch_address': '0x800841D4',
            'animated_loader': 'func_1503F62C', 'animated_renderer': 'func_15035D6C',
            'table_address': f'0x{table_address:08X}',
            'table_sha1': hashlib.sha1(table).hexdigest(), 'selector': selector,
            'bindings': {'6': {'pixel_segment': 6, 'palette_segment': 6,
                               'flats': flats, 'selected_index': 0}},
            'preview_policy': 'Explicit ROM attachment texture preset; not a sampled or proven reachable gameplay state',
            'scope': 'Stored geometry and UVs; parent ownership, animation, pose, visibility, lighting and native appearance unresolved.',
        }
        contexts.append({'bank': 9, 'entry': entry, 'segment': 0,
                         'renderer': 'func_150311C4', 'texture_binding': state,
                         'scope': state['scope']})
    return contexts


def animated_action_binding(code, code_base, data, data_base):
    """Action 26's kind-2 attachment after updater 15 selects its first image.

    The shared constructor/update/render pins are checked by material_context.
    Animation controls matrices; the additional renderer changes segments 3/8
    and preserves the segment-6 pixel binding set by the ordinary renderer.
    """
    for address, size, expected in ANIMATED_CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError('animated attachment consumer changed')
    header_address = 0x80086CC4 + 25 * 8
    address = 0x8009D2F0
    raw = checked(data, data_base, address, 16)
    if (checked(data, data_base, header_address, 8) != struct.pack('>IB3x', address, 1)
            or raw != bytes.fromhex('99120f02000016000000000000000000')
            or checked(data, data_base, 0x800841FC, 4) != struct.pack('>I', 0x150337E4)):
        raise ValueError('animated attachment action or updater changed')
    table = checked(data, data_base, 0x800902FC, 8)
    flats = list(struct.unpack('>2I', table))
    if flats != [1545, 1546]:
        raise ValueError('animated attachment image table changed')
    scope = ('Stored geometry and UVs; attachment animation, pose, visibility, '
             'lighting and native appearance remain unresolved.')
    state = {
        'kind': 'direct-pixel-segments', 'action': 26,
        'action_header_address': f'0x{header_address:08X}',
        'action_record_address': f'0x{address:08X}',
        'action_record_sha1': hashlib.sha1(raw).hexdigest(),
        'update_function': 'func_150337E4', 'update_dispatch_address': '0x800841FC',
        'animated_loader': 'func_1503F62C', 'animated_renderer': 'func_15035D6C',
        'table_address': '0x800902FC', 'table_sha1': hashlib.sha1(table).hexdigest(),
        'preview_state': {'descriptor_0x17': 22, 'descriptor_0x38': 0,
                          'descriptor_0x3C': 0, 'descriptor_0x1A': 0,
                          'update_delta': 1},
        'selector_formula': 'Toggle descriptor +0x3C after accumulator +0x38 reaches 16; use table[+0x3C]',
        'bindings': {'6': {'pixel_segment': 6, 'flats': flats, 'selected_index': 0,
                           'selected_flat': flats[0], 'image_layout': [32, 32, 0, 3],
                           'payload_bytes': 4096}},
        'preview_policy': 'Explicit first-frame attachment inspection preset; not a sampled gameplay state',
        'scope': scope,
    }
    return {'bank': 9, 'entry': 153, 'segment': 0, 'renderer': 'func_150311C4',
            'texture_binding': state, 'scope': scope}


def action_bindings(data, data_base):
    contexts = []
    for action, address, expected in ACTIONS:
        header_address = 0x80086CC4 + (action - 1) * 8
        header = checked(data, data_base, header_address, 8)
        if header != struct.pack('>IB3x', address, 1):
            raise ValueError('attachment action header changed')
        raw = checked(data, data_base, address, 16)
        if raw != bytes.fromhex(expected) or raw[3] != 1:
            raise ValueError('attachment action record changed')
        entry, updater = raw[0], raw[2]
        dispatch_address = 0x800841C0 + updater * 4
        if checked(data, data_base, dispatch_address, 4) != struct.pack('>I', UPDATERS[updater]):
            raise ValueError('attachment update dispatch changed')
        table_address, expected_flats = TEXTURES[entry]
        table = checked(data, data_base, table_address, len(expected_flats) * 4)
        flats = struct.unpack(f'>{len(expected_flats)}I', table)
        if flats != expected_flats:
            raise ValueError('attachment texture table changed')
        selector = {'descriptor_0x17': -1, 'descriptor_0x1A': 0,
                    'initializer': 'no-op for this model', 'renderer_fifth_argument': 0}
        if entry == 25:
            selector.update(descriptor_0x38=0, next_descriptor_0x38=1,
                            frame_indices=[0, 1, 2, 2, 1, 0])
            policy = 'First stored ROM texture frame; not a sampled gameplay time'
        else:
            selector.update(parent_0x2D0='non-null animation pointer', parent_0x84=0,
                            excluded_parent_0x84=13 if entry == 19 else 174)
            if entry == 49:
                selector['table_index'] = 6
            policy = 'Explicit ROM updater inspection preset; not a sampled gameplay state'
        state = {'kind': 'attachment-payload', 'action': action,
                 'action_header_address': f'0x{header_address:08X}',
                 'action_record_address': f'0x{address:08X}', 'action_record_index': 0,
                 'action_record_sha1': hashlib.sha1(raw).hexdigest(),
                 'update_function': f'func_{UPDATERS[updater]:08X}',
                 'update_dispatch_address': f'0x{dispatch_address:08X}',
                 'table_address': f'0x{table_address:08X}',
                 'table_sha1': hashlib.sha1(table).hexdigest(), 'selector': selector,
                 'bindings': {'6': {'pixel_segment': 6, 'palette_segment': 6,
                                    'flats': list(flats), 'selected_index': 0}},
                 'preview_policy': policy,
                 'scope': 'Stored geometry and UVs; later state changes, attachment pose, visibility, lighting and native appearance unresolved.'}
        contexts.append({'bank': 9, 'entry': entry, 'segment': 0,
                         'renderer': 'func_150311C4', 'texture_binding': state,
                         'scope': state['scope']})
    return contexts


def material_context(code, code_base, data, data_base):
    consumers = []
    for address, size, expected in CONSUMERS:
        if hashlib.sha1(checked(code, code_base, address, size)).hexdigest() != expected:
            raise ValueError(f'attachment texture consumer changed: 0x{address:08X}')
        consumers.append({'function': f'func_{address:08X}', 'size': size, 'sha1': expected})
    contexts = action_bindings(data, data_base)
    for action, address, expected in DIRECT_ACTIONS:
        header_address = 0x80086CC4 + (action - 1) * 8
        if checked(data, data_base, header_address, 8) != struct.pack('>IB3x', address, 1):
            raise ValueError('attachment direct action header changed')
        raw = checked(data, data_base, address, 16)
        if (raw != bytes.fromhex(expected) or raw[2:4] != b'\x00\x01'
                or not 95 <= raw[0] < 130 or checked(data, data_base, 0x800841C0, 4) != bytes(4)):
            raise ValueError('attachment direct action or no-op initializer changed')
        contexts.append({'bank': 9, 'entry': raw[0], 'segment': 0,
            'renderer': 'func_150311C4', 'segment_8_bases': ['0x80082FC0', '0x80083140'],
            'action': action, 'action_header_address': f'0x{header_address:08X}',
            'action_record_address': f'0x{address:08X}',
            'action_record_sha1': hashlib.sha1(raw).hexdigest(),
            'initializer': 'func_15031A50 default no-op arm', 'updater': None,
            'scope': 'Stored flat-textured attachment geometry; pose, visibility, lighting and native appearance unresolved.'})
    contexts.append(animated_action_binding(code, code_base, data, data_base))
    contexts.extend(indexed_animated_action_bindings(code, code_base, data, data_base))
    consumers.extend({'function': f'func_{a:08X}', 'size': n, 'sha1': h}
                     for a, n, h in ANIMATED_CONSUMERS + INDEXED_ANIMATED_CONSUMERS)
    return {'consumers': consumers, 'models': contexts, 'capture_inputs': []}
