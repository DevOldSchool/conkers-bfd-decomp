#include "types.h"

/*
 * Reviewed source unit: src/game/game_F8590.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CB1F4
 * - func_150CBE88
 * - func_150CBF5C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15143134(f32 *, f32 *, s32);
s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);
extern f32 D_800A05E0;
extern f32 D_800A05EC;

s32 func_150CB0E0(f32 *arg0, void *arg1, s32 arg2, u8 arg3) {
    f32 position[3];
    f32 *var_a0;
    s32 var_a2;

    if ((arg3 != 1) && (arg3 != 2)) {
        return 0;
    }
    if (arg3 == 1) {
        var_a0 = &D_800A05EC;
    } else {
        var_a0 = &D_800A05E0;
    }
    if (arg3 == 1) {
        var_a2 = *(s32 *)((u8 *)arg1 + 0x1D4) + 0xA00;
    } else {
        var_a2 = *(s32 *)((u8 *)arg1 + 0x1D4) + 0xBC0;
    }
    func_15143134(var_a0, arg0, var_a2);
    if (arg2 == 0) {
        return 1;
    }
    position[0] = arg0[0];
    position[1] = arg0[1] + 100.0f;
    position[2] = arg0[2];
    func_1504715C((void *)arg2, arg1);
    return func_15046C80(position, 0, arg0[1] - 500.0f, (void *)arg2);
}
s32 func_150CB1E0(s32 arg0, s32 arg1) {
    return 0xB;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CB1F4.s")
s32 func_150CB7CC(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x28)) {
            *(u8 *)((u8 *)arg0 + 0x28) = (u8) temp_v1;
        }
    }
    return 1;
}
void func_15143794(s16, s16, f32, void *);
u32 func_150ADA20(void);
f32 func_150ADA68(void);

typedef struct GameF8590EffectPacket {
    f32 field0;
    f32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    s32 field50;
    s16 field54;
    s16 field56;
    s8 field58;
    u8 pad59[0x3];
    s32 field5C;
    u8 field60;
    s8 field61;
    s8 field62;
    s8 field63;
    s8 field64;
    s8 field65;
    s8 field66;
    s8 field67;
    s8 field68;
    u8 pad69[0x1];
    s8 field6A;
    u8 pad6B[0x1];
    s32 field6C;
    s8 field70;
    u8 pad71[0x1];
    s16 field72;
    s16 field74;
    u8 unknown76[0xA];
} GameF8590EffectPacket;

void *func_15132A4C(void *, s32, s32, s32, u8, s32);
extern f32 D_800A0604, D_800A0608, D_800A060C, D_800A0610;
extern f32 D_800A0618, D_800A061C, D_800A0614, D_800A0620;

s32 func_150CB800(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    GameF8590EffectPacket packet;
    f32 fraction;
    u32 random;

    packet.field28 = arg2;
    packet.field2C = arg3;
    packet.field30 = arg4;
    packet.field24 = packet.field20 = packet.field1C = 1.0f;
    packet.field50 = 0x29E8;
    packet.field18 = packet.field14 = packet.field10 = 0.0f;
    packet.field44 = 0.0f;
    packet.field0 = 1.0f;
    packet.field56 = 0x20;
    packet.field4 = D_800A0604;
    random = func_150ADA20();
    fraction = func_150ADA68();
    func_15143794(((s16 *)&arg8)[1], (s16)((random % 36U) - 0x37),
                 ((fraction * 200.0f) + 200.0f) * D_800A0608, &packet.field34);
    packet.field40 = ((func_150ADA68() * 300.0f) + -149.0f) * D_800A060C;
    packet.field48 = ((func_150ADA68() * 300.0f) + -149.0f) * D_800A0610;
    packet.field54 = (func_150ADA20() % 33U) + 0x20;
    packet.field4C = ((func_150ADA68() * D_800A0614) + D_800A0618) * D_800A061C;
    fraction = ((func_150ADA68() * 300.0f) + 101.0f) * D_800A0620;
    packet.field58 = 0;
    packet.field5C = 0;
    packet.field8 = fraction;
    packet.fieldC = fraction;
    packet.field60 = (func_150ADA20() % 101U) + 0x9B;
    packet.field61 = 2;
    packet.field62 = 0;
    packet.field63 = 0;
    packet.field64 = 0;
    packet.field65 = 0;
    packet.field66 = 0;
    packet.field67 = 0;
    packet.field68 = 0;
    packet.field6A = 2;
    packet.field6C = 0;
    packet.field70 = 0;
    packet.field72 = 0x20;
    packet.field74 = 7;
    func_15132A4C(&packet, 3, 0xFF, 0, ((u8 *)&arg14)[3], 0);
    return 1;
}
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

s32 func_150CBA30(void *arg0) {
    f32 temp_fv0;
    s16 temp_v0;
    s32 temp_v1;

    *(s16 *)((u8 *)arg0 + 0x128) = (s16) (*(s16 *)((u8 *)arg0 + 0x128) - D_800BE9E4);
    if (*(s16 *)((u8 *)arg0 + 0x128) > 0) {
        temp_fv0 = *(f32 *)((u8 *)arg0 + 0x12C) * D_800BE9A4;
        *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + temp_fv0);
        *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + temp_fv0);
    }
    if (*(s32 *)((u8 *)arg0 + 0x58) & 1) {
        temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
        if (temp_v0 < 0x20) {
            temp_v1 = temp_v0 * 8;
            if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
                *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
            }
        }
    }
    return 1;
}
typedef struct GameF8590Particle {
    s32 flags, field4;
    s16 kind, duration;
    s32 fieldC, field10;
    u8 color0[4], color1[4];
    u8 field1C, field1D;
    s16 field1E, field20, field22;
    f32 field24, size0, size1;
    f32 position[3];
    u8 pad3C[0xC];
    f32 direction[3];
    f32 field54;
    s32 flags58;
    u8 pad5C[4];
    u8 field60, field61, field62;
    s8 field63;
    u8 pad64[0xC];
} GameF8590Particle;

void *func_10022EC0(void *, const void *, u32);
void *func_15130374(s32, u8, s32, u8, s32);
extern f32 D_800A0624, D_800A0628, D_800A062C, D_800A0630;

s32 func_150CBABC(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    void *temp_v0;
    GameF8590Particle packet;
    f32 size;
    f32 sp2C;
    f32 fraction;
    u32 sp24;

    packet.field1D = 0x29;
    packet.kind = 0xE03;
    packet.flags = 0x200005;
    packet.field4 = 0;
    packet.duration = (func_150ADA20() % 41U) + 0x28;
    packet.fieldC = 0;
    packet.field10 = 0;
    packet.color1[0] = 0xB0;
    packet.color1[1] = 0xA0;
    packet.color1[2] = 0x2A;
    packet.color0[0] = 0x40;
    packet.color0[1] = 0xB;
    packet.color0[2] = 0x6A;
    packet.color0[3] = 0xFF;
    packet.color1[3] = (func_150ADA20() % 157U) + 0x64;
    packet.field1C = 0xFF;
    packet.field60 = 3;
    packet.field61 = 3;
    size = (func_150ADA68() * D_800A0624) + 300.0f;
    packet.position[0] = arg2;
    packet.position[1] = arg3;
    packet.position[2] = arg4;
    packet.size0 = size;
    packet.size1 = size;
    sp24 = func_150ADA20();
    fraction = func_150ADA68();
    func_15143794(((s16 *)&arg8)[1], (s16) ((sp24 % 26U) - 0x19), ((fraction * 500.0f) + 1000.0f) * D_800A0628, &packet.direction);
    packet.flags58 = 0xE05;
    packet.field54 = 0.0f;
    if (func_150ADA20() & 1) {
        packet.flags58 |= 0x40;
    }
    if (func_150ADA20() & 1) {
        packet.flags58 |= 0x80;
    }
    packet.field62 = 7;
    packet.field63 = -1;
    packet.field1E = 0x19;
    packet.field20 = 0xA;
    packet.field22 = 0x3C;
    packet.field24 = D_800A062C;
    sp2C = D_800A0630;
    temp_v0 = func_15130374((s32) &packet, 1U, 4, ((u8 *)&arg14)[3], 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0xA8, &sp2C, 4U);
    }
    return 1;
}
s32 func_150CBCE0(void *arg0, s32 arg1) {
    f32 *factor;
    s32 remaining;

    factor = (f32 *)((u8 *)arg0 + 0xA8);
    remaining = D_800BE9E4;
    while (remaining != 0) {
        *(f32 *)((u8 *)arg0 + 0x58) *= *factor;
        *(f32 *)((u8 *)arg0 + 0x60) *= *factor;
        remaining--;
    }
    return 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CBE88 CURRENT (120) */
s32 func_150CBE88(void *arg0) {
    f32 rate;
    f32 temp_fa0;
    f32 temp_fv1;

    *(f32 *)((u8 *)arg0 + 0x38) += *(f32 *)((u8 *)arg0 + 0x44) * D_800BE9A4;
    rate = D_800BE9A4;
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x48);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x5C);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + ((temp_fv1 * rate) + (temp_fa0 * rate * rate * 0.5f)));
    *(f32 *)((u8 *)arg0 + 0x40) += *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (temp_fv1 + (temp_fa0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x20) += *(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x24) += *(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x28) += *(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CBE88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CBE88.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CBF5C CURRENT (220) */
void func_150CBF5C(void *arg0) {
    s32 temp_t6;
    s32 temp_t7;
    s16 temp_t8;

    temp_t6 = *(s32 *)((u8 *)arg0 + 0x58);
    temp_t7 = temp_t6 | 1;
    temp_t8 = 0x20;
    *(s16 *)((u8 *)arg0 + 0x1C) = temp_t8;
    *(s32 *)((u8 *)arg0 + 0x58) = temp_t7;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CBF5C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CBF5C.s")
