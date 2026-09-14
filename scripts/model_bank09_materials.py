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
    (0x1513A6E0, 1240, '9d9cb54a938ddfbf76f6fbcb1c00fa5697256a8b'),
    (0x15143134, 392, 'aff90add2efa478694dcdd5359f96038e7f1c6f8'),
    (0x15143794, 160, 'a7634c23792fe2bbba7646b52180f28d8a7c3551'),
    (0x150A7960, 160, '74bbe33c7a4fb06b7b640eb86c0fb601b77a8c0d'),
    (0x15142314, 196, '40947fc56427337b13d6b6d8047d967753641b66'),
    (0x151423D8, 108, '954d4825ed97aad8aa6d35d203a8d2ba96cf11ae'),
    (0x150ADA20, 72, 'd66a837e2d79841fd1b885390b95e5e2dc50bd45'),
    (0x150ADA68, 100, '4367530c675204e4481b489e437de0d5ae563248'),
    (0x1503F404, 172, 'd607cc0af029e9b1959bb71c4cccfc9e43fb6675'),
    (0x15134070, 252, 'a7cf677b63f76ad45de83f60c5db0e8d02fdc8e3'),
    (0x15138424, 1412, '05212f5aec7598460aa3b2565e7ca5d6be67d655'),
    (0x15138BC0, 192, '2de828578f48d3750b085246735863131af7b027'),
    (0x1513B0F8, 1256, 'afe190baeaf57391ceb066ce6b92c734073f1ad8'),
    (0x15136C3C, 788, '585f34d7cf570b402f1f7f7bf4d1fa1c7f713846'),
    (0x1513A24C, 576, '1859f5c6b74be313881963173a0c69a803bdaed7'),
    (0x1515080C, 1296, '8a76782a5c5b96ff73e269d77038908f01dfc5db'),
    (0x150F1D10, 992, '77c321a9f44d4758a8f5b249b431ada52469e419'),
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


# Two complementary mask loops in one pinned constructor. The full function
# establishes index 0..3, bit 1 << index and a mask selected with RNG % 6.
# Guards identify the address, stride/load, mask polarity, store and submission;
# whole-function pins cover intervening lifetimes and bounded vector helpers.
LOOP_MASK = (0x800A4278, 6, 'e9a9be10f39f99e9842f3e0f6b20e38dd69b50d8')
LOOP_SETUPS = (
    dict(call=0x1513A89C, frame=0x144, flags=(0x1513A780, 0x1513A784, 0x1513A7EC),
         address=0x800A4280, sha1='2500c94c8e5b569e4ec666db87d4e8eded11a013',
         store=0x1513A8A0, mask_set=True,
         guards=((0x1513A83C, 0x3C12800A), (0x1513A848, 0x26524280),
                 (0x1513A868, 0x92D80000), (0x1513A86C, 0x00104080),
                 (0x1513A874, 0x0303C824), (0x1513A878, 0x1320000F),
                 (0x1513A87C, 0x02484821), (0x1513A880, 0x8D2A0000),
                 (0x1513A860, 0x27B30144), (0x1513A88C, 0x02602025),
                 (0x1513A89C, 0x0D44CA93), (0x1513A8A0, 0xA7AA019A),
                 (0x1513A8C8, 0x29610004), (0x1513A8D0, 0x1420FFE5))),
    dict(call=0x1513AB48, frame=0xA4, flags=(0x1513A974, 0x1513A984, 0x1513AA34),
         address=0x800A4290, sha1='d7494ec63fa885c74203a90d19fc5959d480d5af',
         store=0x1513AA70, mask_set=False,
         guards=((0x1513A990, 0x3C14800A), (0x1513A994, 0x26944290),
                 (0x1513AA4C, 0x92CE0000), (0x1513AA50, 0x0010C080),
                 (0x1513AA58, 0x01C27824), (0x1513AA5C, 0x15E0003C),
                 (0x1513AA60, 0x0298C821), (0x1513AA64, 0x8F280000),
                 (0x1513AB30, 0x27A400A4), (0x1513AB48, 0x0D44C993),
                 (0x1513AA70, 0xA7A800FA), (0x1513AB60, 0x2B210004),
                 (0x1513AB68, 0x1420FFB8))),
)

# The same selection protocol with two entries and three mask alternatives.
# Keep the old records unchanged so existing export evidence is stable.
LOOP_SETUPS += (
    dict(function=0x1513B0F8, call=0x1513B2C4, frame=0x144,
         flags=(0x1513B1AC, 0x1513B1B0, 0x1513B218),
         address=0x800A4328, count=2, sha1='4b3184d589c4910e2cde7a150be53b80af1f9cd4',
         mask=(0x800A4324, 3, '0c7a623fd2bbc05b06423be359e4021d36e721ad'),
         store=0x1513B2C8, mask_set=True,
         guards=((0x1513B268, 0x3C12800A), (0x1513B274, 0x26524328),
                 (0x1513B2A8, 0x8D2A0000), (0x1513B2C4, 0x0D44CA93),
                 (0x1513B2C8, 0xA7AA019A), (0x1513B2F0, 0x29610002))),
    dict(function=0x1513B0F8, call=0x1513B564, frame=0xA4,
         flags=(0x1513B388, 0x1513B398, 0x1513B450),
         address=0x800A4330, count=2, sha1='e6668de31308cba3dc45196a61b1475bbe353493',
         mask=(0x800A4324, 3, '0c7a623fd2bbc05b06423be359e4021d36e721ad'),
         store=0x1513B48C, mask_set=False,
         guards=((0x1513B3A4, 0x3C14800A), (0x1513B3A8, 0x26944330),
                 (0x1513B480, 0x8F190000), (0x1513B564, 0x0D44C993),
                 (0x1513B48C, 0xA7B900FA), (0x1513B57C, 0x2B010002))),
)

DESCRIPTOR_TABLE = (0x800A3FD8, 20, 16, '0e8101c4aae51031a32f923f252098a9eba039c6')
DESCRIPTOR_SWITCHES = (
    (0x800A4350, 129, 'e70e56298b7ac4cea69efdb3a55781e491b92ca4'),
    (0x800A4554, 23, '1acee8d60bd0ac6743dc44648251864bd85b1ba1'),
)

# Actor-type selector arrays used by 15136C3C -> 1513A24C -> 1515080C.
# Type index 1 enables callback 1 and is deliberately excluded. All other
# indices pass -1, whose signed byte is copied to object +0x79 and tested by
# the renderer before its optional callback. These are initial ROM arrays.
FRAGMENT_TABLES = (
    (0x80089A20, 80, 'fc31239198497a530d95521b430bea024ce7a081'),
    (0x800A3F14, 80, '03eb3d6d44ad2b1f1075be7cf65ed6e800c878d2'),
    (0x800A3C6C, 680, 'e1d0e2b9ac6c6818d798a994f0e8bb32c61de8e2'),
    (0x800A18C0, 12, '9b86e97e5a7793f59e956182524b84cee02860e3'),
)
FRAGMENT_GUARDS = (
    (0x15132C3C, 0x82020079), (0x15132C40, 0x2401FFFF),
    (0x15132C48, 0x10410008), (0x1515097C, 0x83AE0143),
    (0x151509C8, 0xA3AE0109), (0x15150BE4, 0x8FA80124),
    (0x15150BE8, 0x00108880), (0x15150BEC, 0x01114821),
    (0x15150BF0, 0x8D2A0000), (0x15150BFC, 0xA7AA00F6),
    (0x15150C54, 0x27A400A0), (0x15150CB0, 0x0D44C993),
    (0x1513A300, 0x2403FFFF), (0x1513A324, 0x10410021),
    (0x1513A3CC, 0x24030001), (0x1513A454, 0xAFA30020),
    (0x1513A468, 0x0D454203), (0x15136D34, 0x8CA59A20),
    (0x15136D38, 0xAFA30014), (0x15136D50, 0x0D44E893),
    (0x15136D00, 0x8CE73F14), (0x150F1F78, 0x3C05800A),
    (0x150F1F84, 0x2409FFFF), (0x150F1FB0, 0xAFA90020),
    (0x150F1FBC, 0x24A518C0), (0x150F1FE8, 0x24070003),
    (0x150F1FF0, 0x0D454203),
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


def word_literal_store(code: bytes, base: int, pcs: tuple[int, int, int], offset: int) -> dict:
    """Decode a pinned LUI/ORI/SW field while retaining every high flag bit."""
    upper, lower, store = (struct.unpack('>I', _slice(code, base, pc, 4))[0] for pc in pcs)
    register = upper >> 16 & 31
    if (not register or upper >> 26 != 15 or upper >> 21 & 31
            or lower >> 26 != 13 or lower >> 21 & 31 != register
            or lower >> 16 & 31 != register or store >> 26 != 43
            or store >> 21 & 31 != 29 or store >> 16 & 31 != register
            or store & 0xFFFF != offset):
        raise ValueError('bank-09 word literal/store differs')
    return {'literal_pc': f'0x{pcs[0]:08X}', 'or_pc': f'0x{pcs[1]:08X}',
            'store_pc': f'0x{pcs[2]:08X}', 'stack_offset': offset,
            'value': ((upper & 0xFFFF) << 16) | (lower & 0xFFFF)}


def loop_array_contexts(code: bytes, code_base: int, data: bytes, data_base: int,
                        setup: dict, lookup: tuple[int, ...]) -> dict:
    for pc, expected in setup['guards']:
        if struct.unpack('>I', _slice(code, code_base, pc, 4))[0] != expected:
            raise ValueError('bank-09 mask loop instruction differs')
    flags = word_literal_store(code, code_base, setup['flags'], setup['frame'] + 0x50)
    if flags['value'] & 0x10000:
        raise ValueError('bank-09 mask loop permits a texture callback')
    count = setup.get('count', 4)
    raw = _slice(data, data_base, setup['address'], count * 4)
    if hashlib.sha1(raw).hexdigest() != setup['sha1']:
        raise ValueError('bank-09 mask loop selector array changed')
    mask_address, mask_count, mask_hash = setup.get('mask', LOOP_MASK)
    masks = _slice(data, data_base, mask_address, mask_count)
    if hashlib.sha1(masks).hexdigest() != mask_hash:
        raise ValueError('bank-09 loop selection masks changed')
    selectors = struct.unpack(f'>{count}I', raw)
    contexts = {}
    for index, selector in enumerate(selectors):
        if selector >= len(lookup):
            raise ValueError('bank-09 loop model selector exceeds lookup table')
        rows = [row for row, mask in enumerate(masks)
                if bool(mask & (1 << index)) == setup['mask_set']]
        if not rows:
            continue
        contexts.setdefault(lookup[selector], []).append({
            'function': f"func_{setup.get('function', 0x1513A6E0):08X}", 'call_pc': f"0x{setup['call']:08X}",
            'template_stack_offset': setup['frame'], 'initial_flags': flags,
            'model_selector': {'value': selector, 'array_index': index,
                               'store_pc': f"0x{setup['store']:08X}"},
            'selector_array': {'address': f"0x{setup['address']:08X}", 'count': count,
                               'sha1': setup['sha1'], 'selectors': list(selectors)},
            'selection_mask': {'address': f'0x{mask_address:08X}', 'count': mask_count,
                               'sha1': mask_hash, 'values': list(masks), 'bit': 1 << index,
                               'submit_when': 'set' if setup['mask_set'] else 'clear',
                               'enabled_rows': rows, 'row_selection': f'RNG % {mask_count}'},
            'model_table_address': f'0x{MODEL_TABLE + selector * 4:08X}',
            'texture_callback': 'disabled by initial flags bit 16'})
    return contexts


def descriptor_contexts(code, code_base, data, data_base, lookup):
    """Read every constructor descriptor reached by the pinned type switch.

    func_15138BC0 rejects the switch's sentinel 99 and forwards the index to
    func_15138424. That constructor reads record +0xC, stores it at template
    +0x56 and submits with flags 0x39E9. No per-model whitelist is involved.
    Whole consumer pins cover control flow and the vector helper write spans.
    """
    indices = set()
    for address, count, expected in DESCRIPTOR_SWITCHES:
        raw = _slice(data, data_base, address, count * 4)
        if hashlib.sha1(raw).hexdigest() != expected:
            raise ValueError('bank-09 descriptor type switch changed')
        for destination in set(struct.unpack(f'>{count}I', raw)):
            if destination == 0x15134160:  # The pinned sentinel return.
                continue
            ret, value = struct.unpack('>2I', _slice(code, code_base, destination, 8))
            if ret != 0x03E00008 or not (value & 0xFFFF0000 == 0x24020000 or value == 0x00001025):
                raise ValueError('bank-09 descriptor switch return differs')
            indices.add(value & 0xFFFF if value != 0x00001025 else 0)
    address, count, stride, expected = DESCRIPTOR_TABLE
    raw = _slice(data, data_base, address, count * stride)
    if hashlib.sha1(raw).hexdigest() != expected or indices != set(range(count)):
        raise ValueError('bank-09 constructor descriptor table changed')
    flags = literal_store(code, code_base, (0x151384F4, 0x15138510), 0x118, 4)
    if flags['value'] & 0x10000:
        raise ValueError('bank-09 descriptor constructor permits a texture callback')
    contexts = {}
    for index in sorted(indices):
        selector = struct.unpack_from('>H', raw, index * stride + 12)[0]
        if selector >= len(lookup):
            raise ValueError('bank-09 descriptor selector exceeds model table')
        contexts.setdefault(lookup[selector], []).append({
            'function': 'func_15138424', 'call_pc': '0x15138728',
            'template_stack_offset': 0xC8, 'initial_flags': flags,
            'model_selector': {'value': selector, 'store_pc': '0x15138548'},
            'constructor_descriptor': {'address': f'0x{address + index * stride:08X}',
                'index': index, 'table_address': f'0x{address:08X}', 'count': count,
                'stride': stride, 'sha1': expected, 'field_offset': 12,
                'index_consumer': 'func_15134070', 'caller': 'func_15138BC0'},
            'model_table_address': f'0x{MODEL_TABLE + selector * 4:08X}',
            'texture_callback': 'disabled by initial flags bit 16'})
    return contexts


def fragment_array_contexts(code, code_base, data, data_base, lookup):
    """Recover ROM arrays whose helper passes the renderer's -1 sentinel.

    Whole-function pins in material_context cover selection without replacement,
    template lifetimes and both flag branches. Vector outputs end before the
    flags/selector/callback fields; post-allocation copies begin at object
    +0x170. The signed callback byte is never changed after initialization.
    """
    for pc, expected in FRAGMENT_GUARDS:
        if struct.unpack('>I', _slice(code, code_base, pc, 4))[0] != expected:
            raise ValueError('bank-09 fragment callback protocol changed')
    spans = []
    for address, size, expected in FRAGMENT_TABLES:
        raw = _slice(data, data_base, address, size)
        if hashlib.sha1(raw).hexdigest() != expected:
            raise ValueError('bank-09 fragment selector table changed')
        spans.append(raw)
    if len(spans[0]) != 80 or len(spans[1]) != 80:
        raise ValueError('bank-09 fragment type table extent differs')
    pointers = struct.unpack('>20I', spans[0])
    counts = struct.unpack('>20I', spans[1])
    arrays = []
    for type_index, (address, count) in enumerate(zip(pointers, counts)):
        if type_index == 1:
            continue  # 1513A3CC changes the callback from -1 to 1.
        offset = address - FRAGMENT_TABLES[2][0]
        if count <= 2 or offset < 0 or offset % 4 or offset + count * 4 > len(spans[2]):
            raise ValueError('bank-09 fragment selector array exceeds pinned span')
        raw = spans[2][offset:offset + count * 4]
        arrays.append((raw, {'caller': 'func_15136C3C', 'call_pc': '0x15136D50',
            'wrapper': 'func_1513A24C', 'wrapper_call_pc': '0x1513A468',
            'type_index': type_index, 'type_consumer': 'func_15134070',
            'address': f'0x{address:08X}', 'count': count,
            'count_variants': [count - 2, count],
            'pointer_table_address': f'0x{FRAGMENT_TABLES[0][0]:08X}',
            'count_table_address': f'0x{FRAGMENT_TABLES[1][0]:08X}',
            'callback_argument_store': '0x1513A454'}))
    arrays.append((spans[3], {'caller': 'func_150F1D10', 'call_pc': '0x150F1FF0',
        'address': f'0x{FRAGMENT_TABLES[3][0]:08X}', 'count': 3,
        'count_variants': [3], 'callback_argument_store': '0x150F1FB0'}))
    contexts = {}
    for raw, selection in arrays:
        selection = {**selection, 'sha1': hashlib.sha1(raw).hexdigest(),
                     'selectors': list(struct.unpack(f'>{len(raw) // 4}I', raw)),
                     'policy': 'Initial ROM array; conditional selection without replacement'}
        for index, selector in enumerate(selection['selectors']):
            if selector >= len(lookup):
                raise ValueError('bank-09 fragment selector exceeds model lookup')
            proof = {'function': 'func_1515080C', 'call_pc': '0x15150CB0',
                'template_stack_offset': 0xA0, 'selector_array': selection,
                'model_selector': {'value': selector, 'array_index': index,
                                   'store_pc': '0x15150BFC'},
                'model_table_address': f'0x{MODEL_TABLE + selector * 4:08X}',
                'callback_index': {'value': -1, 'argument_stack_offset': 0x20,
                    'load_pc': '0x1515097C', 'store_pc': '0x151509C8',
                    'template_offset': 0x69, 'object_offset': 0x79,
                    'renderer_test_pc': '0x15132C48'},
                'texture_callback': 'disabled by signed callback index -1'}
            contexts.setdefault(lookup[selector], []).append(proof)
    return contexts


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
    for setup in LOOP_SETUPS:
        for entry, proofs in loop_array_contexts(code, code_base, data, data_base, setup, lookup).items():
            contexts.setdefault(entry, proofs)
    for entry, proofs in descriptor_contexts(code, code_base, data, data_base, lookup).items():
        contexts.setdefault(entry, proofs)
    for entry, proofs in fragment_array_contexts(code, code_base, data, data_base, lookup).items():
        contexts.setdefault(entry, proofs)
    return {'consumers': consumers,
            'model_lookup_table': {'address': f'0x{MODEL_TABLE:08X}', 'count': MODEL_COUNT, 'sha1': MODEL_TABLE_SHA1},
            'models': [{'bank': 9, 'entry': entry, 'segment': 0, 'constructors': proofs,
                        'renderer': 'func_15132B80', 'segment_8_bases': ['0x80083740', '0x800838C0'],
                        'scope': 'Reviewed initial object draw with texture callback disabled. Later flag changes, visibility, colours, transforms and native raster parity unresolved.'}
                       for entry, proofs in sorted(contexts.items())],
            'capture_inputs': []}
