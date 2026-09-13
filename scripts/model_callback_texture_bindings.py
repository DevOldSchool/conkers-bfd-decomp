"""ROM-selected image/palette bindings for two reviewed object callbacks.

The callbacks preserve segment 8. Only the pinned constructor payloads below
establish the other segment IDs; arbitrary callback-enabled objects remain out
of scope. Presets retain the correlated alternatives chosen by each caller.
"""
from __future__ import annotations

import hashlib
import struct

try:
    from scripts import model_bank09_materials as objects
    from scripts.model_object_texture_animation import checked
except ModuleNotFoundError:
    import model_bank09_materials as objects
    from model_object_texture_animation import checked


SHARED_FUNCTIONS = {
    0x1513264C, 0x15132A4C, 0x151336A8, 0x15132B80, 0x151674F8,
    0x15167A68, 0x15168A4C, 0x15142C10, 0x15142B7C, 0x151462C8,
    0x15134070, 0x15136C3C, 0x1513A24C, 0x1515080C,
}
CONSUMERS = tuple(row for row in objects.CONSUMERS if row[0] in SHARED_FUNCTIONS) + (
    (0x15133EB8, 52, 'c655c3665caec744165d1bdeaec95743aed8bf85'),
    (0x15133EEC, 236, '022514849c4aa339cf0d13c9b00324f7681f7140'),
    (0x15133FD8, 140, '01bc7aca2283491b4eac92ebae76782d5d5db49f'),
    (0x151C9198, 828, 'fe08ed5e4446c23d3653383f50a01377dea2209a'),
    (0x15133760, 96, '41f6e77a029a6217c95b9cc7d21e84833f64fcd2'),
    (0x15142838, 220, '8f1da2caa28c2f387682b57bc8fb76a6c63e7e28'),
    (0x150A7790, 464, 'b8f2a7c3eb85814d9bfbdf6c445a0c03ec739fec'),
    (0x150A8050, 336, '9d826a49f8529b88a58d6e5c9455f61c87f6244c'),
    (0x1510D0EC, 648, '47b67aab9ed8a4eb1706ced5424981ff21373aba'),
)
DATA_SPANS = (
    (0x800899A8, 8, '1a890ac72b54bcd209cca13651f9d96be0e42c80'),
    (0x80089A24, 4, 'cf61b7af2e16d51365d089c2416991e88c3ea62d'),
    (0x800A3F18, 4, 'a338270cfeb804d9e6ae99711a9e029f0ecbc02c'),
    (0x800A3C94, 32, '7bab4ae7ed23635a1d53e6606d4191bfa3f4fa94'),
    (0x800A4258, 8, '768988bdeaee703d6cbb4dc5a36a368709d4ea57'),
    (0x8009116C, 48, 'f0ac1cfc1ca43cbcaf86a35ae2749aa220dd2966'),
    (0x800911B4, 96, 'ce4baf7e3c51c8cabf0f8740135888075cbd3c97'),
    (0x80090A3C, 16, '946cd983987b8d389c8ab96eae7bd0d1d168a791'),
    (0x80090A54, 32, '41c02cea2bff0f137bf68aa0824e955cc46f79fd'),
    (objects.MODEL_TABLE, objects.MODEL_COUNT * 4, objects.MODEL_TABLE_SHA1),
)
# Literal, store and copy guards supplement whole-function checks. Template
# +0x69 becomes object +0x79 through the constructor's 0x7c-byte copy.
GUARDS = (
    (0x1513A3CC, 0x24030001), (0x1513A3F8, 0xA3AF0066),
    (0x1513A3FC, 0xAFA80068), (0x1513A400, 0xA7B80064),
    (0x1513A454, 0xAFA30020), (0x151509C8, 0xA3AE0109),
    (0x15150CD0, 0x0C008BB0), (0x15150CD4, 0x8FA60134),
    (0x151328C4, 0x0C008BB0), (0x151328C8, 0x2406007C),
    (0x151C9374, 0xA3AF00C1), (0x151C9378, 0xA3AE0040),
    (0x151C937C, 0xA3B90046), (0x151C9380, 0xA3A8004E),
    (0x151C93BC, 0x240E0037), (0x151C93C0, 0xA7AE00AE),
    (0x151C93DC, 0x0D44CA93), (0x151C941C, 0x0C008BB0),
    (0x151C9420, 0x24840170), (0x151C9428, 0x24090038),
    (0x151C942C, 0xA7A900AE), (0x151C9474, 0x0D44CA93),
    (0x151C94B4, 0x0C008BB0), (0x151C94B8, 0x24840170),
)
SIGHT_SELECTORS = (
    (55, ((0x151C9390, 0x151C93A4), (0x151C9394, 0x151C93A8))),
    (56, ((0x151C9438, 0x151C944C), (0x151C943C, 0x151C9450))),
)


def verify_spans(raw, base, spans):
    for address, size, expected in spans:
        if hashlib.sha1(checked(raw, base, address, size)).hexdigest() != expected:
            raise ValueError(f'object callback evidence changed: 0x{address:08X}')


def texture_descriptor(data, base, selector):
    address = 0x80090B60 + selector * 12
    if not any(start <= address and address + 12 <= start + size
               for start, size, _ in DATA_SPANS if start in (0x8009116C, 0x800911B4)):
        raise ValueError('callback texture descriptor outside reviewed spans')
    raw = checked(data, base, address, 12)
    pointer, count, flags, width, height, fmt, size = struct.unpack('>IBBHHBB', raw)
    if (count, flags, fmt, size) != (1, 0, 2, 1) or width != 32 or height not in (32, 64):
        raise ValueError('callback texture descriptor layout changed')
    if pointer & 3 or not any(start <= pointer and pointer + 4 <= start + span
                              for start, span, _ in DATA_SPANS
                              if start in (0x80090A3C, 0x80090A54)):
        raise ValueError('callback flat pointer outside reviewed spans')
    flat_raw = checked(data, base, pointer, 4)
    flat = struct.unpack('>I', flat_raw)[0]
    return {'selector': selector, 'address': f'0x{address:08X}',
            'sha1': hashlib.sha1(raw).hexdigest(), 'flat_pointer': f'0x{pointer:08X}',
            'flat_word_sha1': hashlib.sha1(flat_raw).hexdigest(), 'flat_index': flat,
            'width': width, 'height': height, 'palette_tail_bytes': 512}


def material_context(code, code_base, data, data_base):
    verify_spans(code, code_base, CONSUMERS)
    verify_spans(data, data_base, DATA_SPANS)
    for pc, expected in GUARDS:
        if checked(code, code_base, pc, 4) != struct.pack('>I', expected):
            raise ValueError('callback constructor instruction changed')
    lookup = struct.unpack(f'>{objects.MODEL_COUNT}I',
                           checked(data, data_base, objects.MODEL_TABLE, objects.MODEL_COUNT * 4))
    dispatch = struct.unpack('>2I', checked(data, data_base, 0x800899A8, 8))
    if dispatch != (0x15133EB8, 0x15133FD8):
        raise ValueError('object callback dispatch changed')
    contexts = []

    def context(selector, callback, proof, bindings, variants):
        if not 0 <= selector < len(lookup):
            raise ValueError('callback model selector exceeds lookup')
        scope = ('Stored geometry and UVs with an explicit ROM selector preset; '
                 'later updates, visibility, assembly, colours, lighting and native appearance unresolved.')
        state = {'kind': 'object-callback-pairs', 'callback_index': callback,
                 'callback': f'func_{dispatch[callback - 1]:08X}',
                 'dispatch_address': f'0x{0x800899A4 + callback * 4:08X}',
                 'binding_helper': 'func_15133EEC', 'constructor': proof,
                 'selector_variants': variants, 'selected_variant': 0,
                 'palette_tail_bytes': 512, 'bindings': bindings,
                 'preview_policy': 'Explicit ROM constructor selector preset; not a sampled gameplay state',
                 'scope': scope}
        contexts.append({'bank': 9, 'entry': lookup[selector], 'segment': 0,
                         'renderer': 'func_15132B80', 'segment_8_bases': ['0x80083740', '0x800838C0'],
                         'texture_binding': state, 'scope': scope})

    # Type 1 is deliberately excluded by the callback-disabled extractor.
    # Here its twelve-byte payload is followed through helper -> object +0x170.
    pointer, = struct.unpack('>I', checked(data, data_base, 0x80089A24, 4))
    count, = struct.unpack('>I', checked(data, data_base, 0x800A3F18, 4))
    if (pointer, count) != (0x800A3C94, 8):
        raise ValueError('callback type-one model array changed')
    selectors = struct.unpack('>8I', checked(data, data_base, pointer, count * 4))
    textures = struct.unpack('>4H', checked(data, data_base, 0x800A4258, 8))
    descriptors = [texture_descriptor(data, data_base, s) for s in textures]
    for selector in sorted(set(selectors) & {145, 146}):
        context(selector, 1,
                {'caller': 'func_15136C3C', 'type_index': 1, 'helper': 'func_1513A24C',
                 'allocation_helper': 'func_1515080C', 'model_array': f'0x{pointer:08X}',
                 'model_selector': selector, 'model_count_variants': [6, 8],
                 'texture_array': '0x800A4258', 'payload_size': 12,
                 'payload_texture_offset': 4, 'payload_segment_offset': 6,
                 'selector_field': 'parent +0x128 unsigned byte clamped to 3'},
                {'6': {'pixel_segment': 6, 'palette_segment': 7,
                       'flats': [d['flat_index'] for d in descriptors], 'selected_index': 0,
                       'texture_descriptors': descriptors}},
                [{'parent_0x128_clamped': i} for i in range(4)])

    # Two records at +0x174/+0x17c are consumed in array order. Each branch
    # supplies a correlated pair; segment 8 is never a target of either record.
    for selector, segment_pcs in SIGHT_SELECTORS:
        bindings = {}
        for segment, pcs in zip((4, 6), segment_pcs):
            descriptors = []
            for pc in pcs:
                word, = struct.unpack('>I', checked(code, code_base, pc, 4))
                if word >> 26 != 9 or (word >> 21) & 31:
                    raise ValueError('callback texture selector is not a literal')
                descriptors.append(texture_descriptor(data, data_base, word & 0xFFFF))
            bindings[str(segment)] = {'pixel_segment': segment, 'palette_segment': segment + 1,
                                     'flats': [d['flat_index'] for d in descriptors],
                                     'selected_index': 0, 'texture_descriptors': descriptors}
        context(selector, 2,
                {'caller': 'func_151C9198', 'model_selector': selector,
                 'constructor': 'func_15132A4C', 'template_stack_offset': 0x58,
                 'payload_stack_offset': 0x40, 'payload_size': 20, 'record_count': 2,
                 'selector_field': 'caller argument at entry sp+0x14, low byte'},
                bindings, [{'caller_arg_0x14_nonzero': True}, {'caller_arg_0x14_nonzero': False}])
    return {'consumers': [{'function': f'func_{a:08X}', 'size': n, 'sha1': h}
                          for a, n, h in CONSUMERS], 'models': contexts, 'capture_inputs': []}
