#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A7490.c
 * Boundary evidence: docs/evidence/game_raw_quad_actor_effect_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15179FE0
 * - func_1517A1EC
 * - func_1517A3A0
 * - func_1517A644
 * - func_1517A84C
 * - func_1517A9A8
 * - func_1517AA20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_15179FE0.s")
typedef struct Game1A7490Motion {
    u8 pad0[0x90];
    s16 pos90;
    s16 pos92;
    s16 pos94;
    s16 pos96;
    s16 pos98;
    s16 pos9A;
    s8 inc9C;
    s8 inc9D;
    s8 inc9E;
    u8 pad9F;
    s16 speedA0;
    s16 speedA2;
    s16 speedA4;
    u16 timerA6;
    u8 padA8[4];
    u16 stateAC;
    u16 divisorAE;
    u8 padB0[2];
    u8 phaseB2;
    u8 fadeB3;
} Game1A7490Motion;

u32 func_150ADA20(void);
void func_1516972C(u8 *);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517A1EC CURRENT (3405) */
void func_1517A1EC(Game1A7490Motion *arg0) {
    s16 oldA2;
    s16 velocity;
    u16 timer;
    u32 random;
    s32 signA;
    s32 signB;
    s32 fade;
    s32 fadedAlpha;
    u8 phase;

    oldA2 = arg0->speedA2;
    arg0->pos90 += arg0->speedA0;
    arg0->pos92 -= oldA2;
    arg0->pos94 += arg0->speedA4;
    arg0->pos96 += arg0->inc9C;
    arg0->pos98 += arg0->inc9D;
    arg0->pos9A += arg0->inc9E;
    if (arg0->stateAC == 5) {
        arg0->speedA2 = oldA2 + 1;
    }
    timer = arg0->timerA6;
    if (timer < arg0->stateAC) {
        random = func_150ADA20() % arg0->divisorAE;
        velocity = arg0->speedA0;
        signA = 1;
        if (velocity < 0) {
            signA = -1;
        }
        arg0->speedA0 = velocity + (-signA * random);
        random = func_150ADA20() % arg0->divisorAE;
        velocity = arg0->speedA4;
        signB = 1;
        if (velocity < 0) {
            signB = -1;
        }
        arg0->speedA4 = velocity + (-signB * random);
        timer = arg0->timerA6;
    }
    fade = timer - D_800BE9E4;
    if (fade < 0) {
        fade = 0;
        fadedAlpha = arg0->fadeB3 - D_800BE9E4 * 4;
        if (fadedAlpha < 0) {
            fadedAlpha = 0;
        }
        arg0->fadeB3 = fadedAlpha;
    }
    arg0->timerA6 = fade;
    if (arg0->fadeB3 == 0 ||
        ((phase = arg0->phaseB2) != 0 && (phase & 0xF) == (phase >> 4))) {
        func_1516972C((u8 *)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517A1EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A1EC.s")
s32 func_1517A394(s32 arg0) {
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A3A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A644.s")
void func_1516972C(u8 *);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517A84C CURRENT (200) */
void func_1517A84C(u8 *arg0) {
    s16 temp_v0_2;
    s16 temp_v1;
    s32 temp_v0_3;
    u16 temp_v0;

    temp_v0 = *(u16 *)(arg0 + 0xA6);
    if (temp_v0 == 0) {
        *(s16 *)(arg0 + 0x90) += *(s16 *)(arg0 + 0xA0);
        temp_v0_2 = *(s16 *)(arg0 + 0xA2);
        *(s16 *)(arg0 + 0x92) += temp_v0_2;
        *(s16 *)(arg0 + 0x94) += *(s16 *)(arg0 + 0xA4);
        if (temp_v0_2 > 0) {
            *(s16 *)(arg0 + 0xA2) = temp_v0_2 - 1;
            if (*(s16 *)(arg0 + 0xA2) <= 0) {
                *(s16 *)(arg0 + 0xA2) = -3;
            }
        }
        temp_v1 = *(s16 *)(arg0 + 0xB0);
        if ((*(s16 *)(arg0 + 0x92) - temp_v1) <= 0) {
            *(s16 *)(arg0 + 0x96) = 0x5A;
            *(s16 *)(arg0 + 0x9A) = 0;
            *(u16 *)(arg0 + 0xA6) = 0x3C;
            *(s16 *)(arg0 + 0x92) = temp_v1;
            return;
        }
        *(s16 *)(arg0 + 0x96) += *(s8 *)(arg0 + 0x9C);
        *(s16 *)(arg0 + 0x98) += *(s8 *)(arg0 + 0x9D);
        *(s16 *)(arg0 + 0x9A) += *(s8 *)(arg0 + 0x9E);
        return;
    }
    temp_v0_3 = temp_v0 - D_800BE9E4;
    if (temp_v0_3 > 0) {
        *(u16 *)(arg0 + 0xA6) = temp_v0_3;
        *(s8 *)(arg0 + 0xB3) = (temp_v0_3 << 8) / 60;
        return;
    }
    func_1516972C(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517A84C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A84C.s")
extern s16 D_800DD450;

s32 func_1517A958(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800DD450 = -1;
    if ((arg1 == 0xC) || (arg1 == 0x59)) {
        arg0 = func_1517A394(arg0);
    }
    return arg0;
}
typedef struct {
    u32 data;
    u8 field_4;
    u8 pad5;
    u16 field_6;
    u16 field_8;
    u8 field_A;
    u8 field_B;
} Game1A7490Input;

typedef struct {
    u8 pad0[0x10];
    void *output;
} Game1A7490Owner;

s32 func_15094F70(s32, Game1A7490Input *, s32, Game1A7490Owner *, s32, s32, s32, s32, s32);
extern Game1A7490Input D_80090614;
extern s32 D_800DD1B0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517A9A8 CURRENT (440) */
s32 func_1517A9A8(s32 arg0, s32 arg1) {
    Game1A7490Owner owner;

    if (arg1 != D_800DD1B0) {
        arg0 = func_15094F70(arg0, &D_80090614, arg1 << 8, &owner, 0, 0, 0, 2, 3);
        D_800DD1B0 = arg1;
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517A9A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A9A8.s")
u32 func_150ADA20(void);
void func_1517A644(f32, s32, s16, s16, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517AA20 CURRENT (2053) */
void func_1517AA20(f32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    f32 var_ft0;
    s32 temp_s0;
    s32 temp_s2;
    s32 var_s1;
    s32 divisor;
    u32 temp_t9;
    f32 half;

    if (!(arg0 < 12.0f)) {
        divisor = (s32)(arg0 * 8.0f);
        half = arg0 * 0.5f;
        var_s1 = 0;
        if (arg4 > 0) {
            do {
                temp_s0 = func_150ADA20() & 0x3F;
                temp_s2 = (func_150ADA20() & 0x3F) - 0x20;
                temp_t9 = (u32)(func_150ADA20() % (u32)divisor) >> 4;
                var_ft0 = (f32)temp_t9;
                temp_s0 -= 0x20;
                func_1517A644(var_ft0 + half, func_150ADA20() & 1,
                              (s16)(arg1 + temp_s0), (s16)arg2,
                              arg3 + temp_s2);
                var_s1 += 1;
            } while (var_s1 != arg4);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517AA20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517AA20.s")
void func_1510B7B4(s32 arg0, s32 arg1);

void func_1517AB7C(s32 arg0, s32 arg1, s16 arg2) {
    func_1510B7B4(arg0, arg2);
}
