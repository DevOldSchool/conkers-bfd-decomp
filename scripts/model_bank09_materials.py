"""Texture-state evidence for reviewed bank-09 object constructors.

The ROM lookup table alone is insufficient: the renderer permits a callback
which can replace segment 8. Only the initial, callback-disabled paths below
are admitted. Complete function pins cover the reviewed control/data flow;
field records also decode and check the actual literal/store instructions.
"""
from __future__ import annotations

import hashlib
import struct


CONSUMERS = (
    (0x150B2EB4, 724, '0e124ee088467533e58d78a87edf2c8694142825'),
    (0x1513264C, 1024, 'b022e07fc63bd600c1da1ce8de6da11a8a352733'),
    (0x151336A8, 184, '2432f6c82170d429bdbad3f281b65ca8e0663945'),
    (0x15132A4C, 60, '3fb32dda30af3d1ea495657ab1b6cdf0ed798074'),
    (0x15132B80, 604, 'd0b8f621187945c259efddd0f31cdc77bb6eba9a'),
    (0x151674F8, 1392, '1a4cc2434666765a39feb16096d26a83d4b8fcc3'),
    (0x15167A68, 112, '0825b0b974ca67a92c0a6e7d8665230b02e2b181'),
    (0x15168A4C, 80, '41a70fd6b122eeb005b9c01d21f215c154765b9d'),
    (0x15142C10, 224, 'b25e68a995048ced62f806da32c7b18f3ada8b12'),
    (0x15142B7C, 148, '8273f4c6055c4104f8695287d16bfdd4541af20f'),
    (0x151462C8, 496, '6dcfdd4d04697403fe2e944a1f79edaf5bea4bc4'),
    (0x1515E544, 836, '0e519a645021b9188d667049b16a555b1b75933d'),
    (0x1515D914, 2404, 'a0ca1f285c354276fa25543fe54a68ef023f1813'),
    (0x150BB498, 616, '53f2e0bf57530eaf7707464cac976337d894e8af'),
    (0x151A6F00, 1260, 'c5a5b8632d569450924197f482040ac0fde74d1c'),
    (0x15109C20, 692, '6decb0be5b3a3f4d230e72e82e18dbbe0aefd1be'),
    (0x1518B6B0, 992, 'c5f569c368c612c17e3ca1edf58452b4fbf008df'),
    (0x150E5558, 696, '3e8b76f1225f2ee238d13d2e901424264a8d7501'),
    (0x15010A60, 1360, '4dd66da12b20985c586e17b952c2eb48682cc317'),
    (0x150F892C, 3572, '45bfb40913cad9a333602766f0801a302454b196'),
    (0x150DECC0, 1652, 'cfc33dabedf0ab5515a0932a2a13155c82aaf037'),
    (0x150BB760, 1020, 'a00a28e9525665ba83885ef89dba2a3995bb1c29'),
    (0x151BA518, 2860, '412f01d8d7f17216270904488fce83aeecedeb79'),
    (0x151B8DB0, 1124, '342d2bae9d339096b6c3bcfc26b4f295fc0f5e5e'),
    (0x15151D6C, 1060, '7d2db4bd09a40af2e1851a2715967513cf3ab4e2'),
    (0x15152190, 912, 'ad00c680b1584fcef202f0e6fc6690a6bb3dc5f6'),
    (0x151BB61C, 1152, '24f395be1718c9a889cf618b9caf18b022f628cb'),
    (0x151BBA9C, 1096, 'f2ff72cdfa4045152fa5912c4ccd0e324d6ecfa8'),
)
MODEL_TABLE = 0x800A3880
MODEL_COUNT = 233
MODEL_TABLE_SHA1 = '4e7fe3ec765c742dd70576aaba0c9bc005487d53'

# Function, submission call, stack template, flags (literal, store), and model
# selector (literal, store) pairs. Multiple selectors are reviewed alternatives,
# not a claim that all alternatives are submitted in one invocation.
SETUPS = (
    (0x150B2EB4, 0x150B316C, 0x24, (0x150B2F0C, 0x150B2F14), ((0x150B30F0, 0x150B310C),)),
    (0x150BB498, 0x150BB6D8, 0x2C, (0x150BB4F0, 0x150BB4F8), ((0x150BB660, 0x150BB678),)),
    (0x151A6F00, 0x151A72F8, 0xE8, (0x151A6F70, 0x151A6F80), ((0x151A6F9C, 0x151A6FA0),)),
    (0x15109C20, 0x15109EBC, 0x20, (0x15109DD8, 0x15109DDC),
     ((0x15109E14, 0x15109E1C), (0x15109E20, 0x15109E24))),
    (0x1518B6B0, 0x1518B970, 0xCC, (0x1518B720, 0x1518B744), ((0x1518B71C, 0x1518B734),)),
    (0x150E5558, 0x150E57F8, 0x34, (0x150E56CC, 0x150E56D8), ((0x150E56A8, 0x150E56AC),)),
    (0x15010A60, 0x15010E3C, 0x154, (0x15010B04, 0x15010B40), ((0x15010B0C, 0x15010B48),)),
    (0x150F892C, 0x150F904C, 0x158, (0x150F8D80, 0x150F8E30), ((0x150F8D88, 0x150F8E34),)),
    (0x150DECC0, 0x150DEFDC, 0x104, (0x150DED68, 0x150DEE00),
     ((0x150DEFAC, 0x150DEFB4), (0x150DEFB8, 0x150DEFBC))),
    (0x150BB760, 0x150BBB40, 0x7C, (0x150BB82C, 0x150BB84C), ((0x150BB824, 0x150BB848),)),
    # This constructor reuses one template across five submissions. Only
    # +0x56 changes between them; +0x50 remains the initial 0x39E9. Some
    # submissions sit in bounded random-choice loops; visibility is not proven.
    (0x151BA518, 0x151BA980, 0xDC, (0x151BA77C, 0x151BA7A0), ((0x151BA850, 0x151BA85C),)),
    (0x151BA518, 0x151BAAE0, 0xDC, (0x151BA77C, 0x151BA7A0), ((0x151BA9D0, 0x151BA9DC),)),
    (0x151BA518, 0x151BAC60, 0xDC, (0x151BA77C, 0x151BA7A0), ((0x151BAAE8, 0x151BAAEC),)),
    (0x151BA518, 0x151BAE1C, 0xDC, (0x151BA77C, 0x151BA7A0), ((0x151BAC78, 0x151BAC80),)),
    (0x151BA518, 0x151BAFE4, 0xDC, (0x151BA77C, 0x151BA7A0), ((0x151BAE30, 0x151BAE34),)),
    # Three flags PCs describe a reviewed conditional literal, OR, and store.
    (0x151B8DB0, 0x151B8F7C, 0x140, (0x151B8EF0, 0x151B8F0C, 0x151B8F28),
     ((0x151B8E90, 0x151B8EA8),)),
)

# Helper: submission, template frame, flags expression, selector store. Each
# helper selects a word from its a1 array with RNG % a3, then stores its low
# halfword at template +0x56. The caller pins cover the copy to the a1 buffer.
ARRAY_HELPERS = {
    0x15151D6C: (0x15152144, 0xB0, (0x15151E98, 0x15151EC0), 0x15152084),
    0x15152190: (0x151524D0, 0x70, (0x151521FC, 0x15152210, 0x15152228), 0x15152488),
}
# Caller, call, helper, a3 literal, ROM array address pair, array count/hash,
# and the instruction establishing a1's stack copy. These are initial ROM
# array values; later mutations of source data are outside this contract.
ARRAY_SETUPS = (
    (0x151BB61C, 0x151BBA7C, 0x15151D6C, 0x151BB9D4,
     (0x151BB930, 0x151BB934), 0x800AA718, 9, '7ff9cb28ca0cf99ba0f5959133159dcf140501c9',
     0x151BB91C, 0xE0),
    (0x151BBA9C, 0x151BBECC, 0x15152190, 0x151BBE08,
     (0x151BBDB8, 0x151BBDBC), 0x8008FBA0, 3, 'd88080eac98a7119b89ad930cb043e3c2fa96ac5',
     0x151BBDB0, 0x40),
)


def _slice(raw: bytes, base: int, address: int, size: int) -> bytes:
    offset = address - base
    if offset < 0 or offset + size > len(raw):
        raise ValueError('bank-09 object evidence exceeds ROM region')
    return raw[offset:offset + size]


def literal_store(code: bytes, base: int, pair: tuple[int, int], offset: int, size: int) -> dict:
    literal, store = (struct.unpack('>I', _slice(code, base, pc, 4))[0] for pc in pair)
    # addiu rt, zero, nonnegative immediate; sw/sh rt, frame-offset(sp).
    if literal >> 26 != 9 or literal >> 21 & 31 or literal & 0x8000:
        raise ValueError('bank-09 constructor field is not a reviewed positive literal')
    if (store >> 26 != {2: 41, 4: 43}[size] or store >> 21 & 31 != 29
            or store >> 16 & 31 != literal >> 16 & 31 or store & 0xFFFF != offset):
        raise ValueError('bank-09 constructor field store differs')
    return {'literal_pc': f'0x{pair[0]:08X}', 'store_pc': f'0x{pair[1]:08X}',
            'stack_offset': offset, 'value': literal & 0xFFFF}


def conditional_or_store(code: bytes, base: int, pcs: tuple[int, int, int], offset: int) -> dict:
    """Decode both outcomes of the pinned beqz/literal/zero flags expression.

    Whole-function pins remain responsible for intervening register lifetime
    and template aliasing. This is deliberately not a general branch evaluator.
    """
    branch_pc, or_pc, store_pc = pcs
    branch, delay, jump, literal, zero = struct.unpack('>5I', _slice(code, base, branch_pc, 20))
    register = literal >> 16 & 31
    if (branch >> 26 != 4 or not (branch >> 21 & 31) or branch >> 16 & 31 or branch & 0xFFFF != 3
            or delay >> 26 not in (43, 57) or delay >> 21 & 31 != 29
            or abs((delay & 0xFFFF) - offset) < 4
            or jump != 0x10000002
            or literal >> 26 not in (9, 15) or literal >> 21 & 31 or not register
            or (literal >> 26 == 9 and literal & 0x8000)
            or zero != (register << 11) | 0x25):
        raise ValueError('bank-09 conditional flags branch differs')
    merge, store = (struct.unpack('>I', _slice(code, base, pc, 4))[0] for pc in (or_pc, store_pc))
    if (or_pc < branch_pc + 20 or store_pc <= or_pc
            or merge >> 26 != 13 or merge >> 21 & 31 != register
            or not (merge >> 16 & 31)
            or store >> 26 != 43 or store >> 21 & 31 != 29
            or store >> 16 & 31 != merge >> 16 & 31 or store & 0xFFFF != offset):
        raise ValueError('bank-09 conditional flags merge/store differs')
    literal_value = (literal & 0xFFFF) << (16 if literal >> 26 == 15 else 0)
    values = sorted({merge & 0xFFFF, literal_value | (merge & 0xFFFF)})
    return {'branch_pc': f'0x{branch_pc:08X}', 'or_pc': f'0x{or_pc:08X}',
            'store_pc': f'0x{store_pc:08X}', 'stack_offset': offset, 'values': values}


def array_selectors(code: bytes, code_base: int, data: bytes, data_base: int, setup: tuple) -> dict:
    caller, call, helper, count_pc, address_pcs, address, count, expected, a1_pc, frame = setup
    word = struct.unpack('>I', _slice(code, code_base, call, 4))[0]
    if word != (3 << 26) | ((helper >> 2) & 0x3FFFFFF) or helper not in ARRAY_HELPERS:
        raise ValueError('bank-09 array helper call differs')
    upper, lower = (struct.unpack('>I', _slice(code, code_base, pc, 4))[0] for pc in address_pcs)
    register = upper >> 16 & 31
    immediate = lower & 0xFFFF
    actual_address = ((upper & 0xFFFF) << 16) + (immediate if immediate < 0x8000 else immediate - 0x10000)
    if (upper >> 26 != 15 or upper >> 21 & 31 or not register
            or lower >> 26 != 9 or lower >> 21 & 31 != register or lower >> 16 & 31 != register
            or actual_address != address):
        raise ValueError('bank-09 array address differs')
    for pc, expected_word in ((count_pc, 0x24070000 | count), (a1_pc, 0x27A50000 | frame)):
        if struct.unpack('>I', _slice(code, code_base, pc, 4))[0] != expected_word:
            raise ValueError('bank-09 array count or stack copy differs')
    raw = _slice(data, data_base, address, count * 4)
    if not count or hashlib.sha1(raw).hexdigest() != expected:
        raise ValueError('bank-09 selector array changed')
    return {'caller': f'func_{caller:08X}', 'call_pc': f'0x{call:08X}',
            'address': f'0x{address:08X}', 'count': count, 'sha1': expected,
            'a1_stack_offset': frame, 'selectors': list(struct.unpack(f'>{count}I', raw))}


def material_context(code: bytes, code_base: int, data: bytes, data_base: int) -> dict:
    consumers = []
    for address, size, expected in CONSUMERS:
        actual = hashlib.sha1(_slice(code, code_base, address, size)).hexdigest()
        if actual != expected:
            raise ValueError(f'bank-09 object consumer changed: 0x{address:08X}')
        consumers.append({'function': f'func_{address:08X}', 'size': size, 'sha1': actual})
    raw = _slice(data, data_base, MODEL_TABLE, MODEL_COUNT * 4)
    if hashlib.sha1(raw).hexdigest() != MODEL_TABLE_SHA1:
        raise ValueError('bank-09 object model lookup table changed')
    lookup = struct.unpack(f'>{MODEL_COUNT}I', raw)
    for kind in (25, 72):
        # Both constructor allocation kinds use this draw function. No
        # pre-list or pre-render callback can supply a different segment 8.
        dispatch = _slice(data, data_base, 0x8008B4A8 + kind * 52 + 8, 16)
        if dispatch != struct.pack('>4I', 0x15132B80, 0x15132A88, 0, 0):
            raise ValueError('bank-09 object draw dispatch changed')
    contexts = {}
    for function, call, frame, flags_pair, selector_pairs in SETUPS:
        word = struct.unpack('>I', _slice(code, code_base, call, 4))[0]
        target = ((call + 4) & 0xF0000000) | ((word & 0x3FFFFFF) << 2)
        if word >> 26 != 3 or target not in (0x1513264C, 0x15132A4C):
            raise ValueError('bank-09 object constructor submission changed')
        flags = (literal_store(code, code_base, flags_pair, frame + 0x50, 4)
                 if len(flags_pair) == 2 else conditional_or_store(code, code_base, flags_pair, frame + 0x50))
        if any(value & 0x10000 for value in flags.get('values', [flags.get('value', 0)])):
            raise ValueError('bank-09 object constructor permits a texture callback')
        for selector_pair in selector_pairs:
            selector = literal_store(code, code_base, selector_pair, frame + 0x56, 2)
            if selector['value'] >= len(lookup):
                raise ValueError('bank-09 constructor model selector exceeds lookup table')
            entry = lookup[selector['value']]
            proof = {'function': f'func_{function:08X}', 'call_pc': f'0x{call:08X}',
                     'template_stack_offset': frame, 'initial_flags': flags,
                     'model_selector': selector,
                     'model_table_address': f'0x{MODEL_TABLE + selector["value"] * 4:08X}',
                     'texture_callback': 'disabled by initial flags bit 16'}
            contexts.setdefault(entry, []).append(proof)
    for setup in ARRAY_SETUPS:
        helper = setup[2]
        selection = array_selectors(code, code_base, data, data_base, setup)
        call, frame, flags_pcs, selector_store = ARRAY_HELPERS[helper]
        call_word = struct.unpack('>I', _slice(code, code_base, call, 4))[0]
        store_word = struct.unpack('>I', _slice(code, code_base, selector_store, 4))[0]
        if (call_word != (3 << 26) | ((0x15132A4C >> 2) & 0x3FFFFFF)
                or store_word >> 26 != 41 or store_word >> 21 & 31 != 29
                or store_word & 0xFFFF != frame + 0x56):
            raise ValueError('bank-09 array submission or selector store differs')
        flags = (literal_store(code, code_base, flags_pcs, frame + 0x50, 4)
                 if len(flags_pcs) == 2 else conditional_or_store(code, code_base, flags_pcs, frame + 0x50))
        if any(value & 0x10000 for value in flags.get('values', [flags.get('value', 0)])):
            raise ValueError('bank-09 array helper permits a texture callback')
        for index, selector in enumerate(selection['selectors']):
            if selector >= len(lookup):
                raise ValueError('bank-09 array model selector exceeds lookup table')
            entry = lookup[selector]
            # Preserve the existing sufficient proof for models already covered
            # by a direct constructor, including duplicate array selections.
            if entry in contexts:
                continue
            contexts[entry] = [{'function': f'func_{helper:08X}', 'call_pc': f'0x{call:08X}',
                                'template_stack_offset': frame, 'initial_flags': flags,
                                'model_selector': {'value': selector, 'array_index': index,
                                                   'store_pc': f'0x{selector_store:08X}'},
                                'selector_array': selection,
                                'model_table_address': f'0x{MODEL_TABLE + selector * 4:08X}',
                                'texture_callback': 'disabled by initial flags bit 16'}]
    return {'consumers': consumers,
            'model_lookup_table': {'address': f'0x{MODEL_TABLE:08X}', 'count': MODEL_COUNT, 'sha1': MODEL_TABLE_SHA1},
            'models': [{'bank': 9, 'entry': entry, 'segment': 0, 'constructors': proofs,
                        'renderer': 'func_15132B80', 'segment_8_bases': ['0x80083740', '0x800838C0'],
                        'scope': 'Reviewed initial object draw with texture callback disabled. Later flag changes, visibility, colours, transforms and native raster parity unresolved.'}
                       for entry, proofs in sorted(contexts.items())],
            'capture_inputs': []}
