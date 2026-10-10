#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1A7490.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_quad_actor_effect_groups.md
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

typedef struct Game1A7490Motion {
    u8 kind;
    u8 pad1[0x8F];
    s16 pos90;
    s16 pos92;
    s16 pos94;
    s16 pos96;
    s16 pos98;
    s16 pos9A;
    s8 inc9C;
    s8 inc9D;
    s8 inc9E;
    u8 field9F;
    s16 speedA0;
    s16 speedA2;
    s16 speedA4;
    u16 timerA6;
    f32 fieldA8;
    u16 stateAC;
    u16 divisorAE;
    s16 posB0;
    u8 phaseB2;
    u8 fadeB3;
} Game1A7490Motion;

u32 func_150ADA20(void);
extern f32 D_800A7220;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15179FE0 CURRENT (2175) */
void func_15179FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10) {
    Game1A7490Motion *effect;
    u32 range;
    s32 half;

    effect = func_15167A68(arg10, 0, 0xB8, 1, 0xFF, 1);
    if (effect != 0) {
        effect->pos90 = arg1;
        effect->pos92 = arg2;
        effect->pos94 = arg3;
        effect->speedA2 = (s8)arg4;
        effect->speedA0 = (func_150ADA20() % (u8)arg7) - ((s32)(u8)arg7 >> 1);
        half = (s32)(u8)arg7 >> 1;
        range = (u8)arg7;
        effect->speedA4 = (func_150ADA20() % range) - half;
        if ((u16)arg6 == 5) {
            effect->pos90 += effect->speedA0 * 4;
            effect->pos92 -= effect->speedA2 * 4;
            effect->pos94 += effect->speedA4 * 4;
        }
        effect->pos96 = 0;
        effect->pos98 = 0;
        effect->pos9A = 0;
        effect->inc9C = (func_150ADA20() % (u8)arg8) - ((s32)(u8)arg8 >> 1);
        half = (s32)(u8)arg8 >> 1;
        range = (u8)arg8;
        effect->inc9D = (func_150ADA20() % range) - half;
        effect->inc9E = (func_150ADA20() % range) - half;
        effect->fieldA8 = (f32)(s32)((func_150ADA20() & 0x7FU) + 0x8C) * D_800A7220;
        effect->timerA6 = arg5;
        effect->field9F = arg0;
        effect->stateAC = arg6;
        effect->phaseB2 = 0;
        effect->fadeB3 = 0xFF;
        effect->divisorAE = (u8)arg9;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15179FE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_15179FE0.s")


extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517A1EC CURRENT (1975) */
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
    fade = (s32)((u32)timer - (u32)D_800BE9E4);
    if (fade < 0) {
        fade = 0;
        fadedAlpha = (s32)((u32)arg0->fadeB3 - ((u32)D_800BE9E4 << 2));
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
s32 func_1510AEE0(f32 *, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *);
s32 func_1517A9A8(s32, s32);
void func_15043D90(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void *func_15142FBC(void *, s32, s32, u8 *);
extern u8 D_800D9C10[];
extern f32 D_800D35E0[2];
extern f32 D_800D9B20;
extern f32 D_800D9B1C;
extern u8 D_800BE9C0;
extern s16 D_800DD450;
extern s32 D_800D2C9C;
extern u8 D_8008CDF0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517A3A0 CURRENT (4278) */
s32 func_1517A3A0(s32 arg0, Game1A7490Motion *effect, s32 view) {
    u8 flag;
    f32 scale;
    s32 mode;
    u32 *command;

    if (effect->kind != 0xC && effect->kind != 0x59 &&
        func_1510AEE0((f32 *)(D_800D9C10 + ((s16)view * 0x40)),
                       (f32)effect->pos90, (f32)effect->pos92, (f32)effect->pos94,
                       D_800D9B20, D_800D9B1C, D_800D35E0[0], D_800D35E0[1],
                       0, 0) != 0) {
        if (effect->kind == 8 && (effect->phaseB2 & (1 << (s16)view))) {
            effect->phaseB2 |= 0x10 << (s16)view;
        }
        return arg0;
    }
    if (effect->kind != 9) {
        effect->phaseB2 |= 1 << (s16)view;
    }
    arg0 = func_1517A9A8(arg0, effect->field9F);
    scale = effect->fieldA8;
    func_15043D90((s32)((u8 *)effect + (D_800BE9C0 << 6) + 0x10),
                   (f32)effect->pos96, (f32)effect->pos98, (f32)effect->pos9A,
                   scale, scale, scale,
                   (f32)effect->pos90, (f32)effect->pos92, (f32)effect->pos94);
    command = (u32 *)arg0;
    command[0] = 0xDA380003;
    arg0 += 8;
    command[1] = (u32)((u8 *)effect + (D_800BE9C0 << 6) + 0x10);
    if (effect->fadeB3 != D_800DD450) {
        command = (u32 *)arg0;
        command[0] = 0xE7000000;
        arg0 += 8;
        command[1] = 0;
        command = (u32 *)arg0;
        command[0] = 0xFA000000;
        arg0 += 8;
        command[1] = effect->fadeB3;
        D_800DD450 = effect->fadeB3;
    }
    flag = 0;
    if (effect->kind == 8 || effect->kind == 9) {
        mode = 0x5049D8;
    } else {
        mode = 0x504240;
    }
    command = func_15142FBC((void *)arg0, D_800D2C9C | 0x82CA0, mode, &flag);
    command[0] = 0xDE000000;
    command[1] = (u32)D_8008CDF0;
    return (s32)(command + 2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517A3A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A3A0.s")
void func_1510E82C(s32, s32, s32, s32, s32, s32,
                   f32, f32, f32, f32, u16, s32);
extern f32 D_800A7224;
extern f32 D_800A7228;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517A644 CURRENT (560) */
void func_1517A644(f32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4) {
    s32 divisor;
    Game1A7490Motion *effect;
    f32 height;
    s32 newHeight;
    s32 random;
    s32 half;

    divisor = (s32)arg0;
    if (divisor != 0) {
        effect = func_15167A68(9, 0, 0xB8, 1, 0xFF, 1);
        if (effect != 0) {
            func_1510E82C(0, 0, (s32)&height, 0, 0, 0,
                          (f32)arg2, (f32)arg3, (f32)(s16)arg4, (f32)arg3, 0, 0);
            newHeight = (s32)(height + 3.0f);
            effect->posB0 = newHeight;
            effect->pos92 = newHeight;
            effect->pos90 = arg2;
            effect->pos94 = (s16)arg4;
            effect->pos96 = 0x5A;
            effect->pos98 = func_150ADA20() % 360U;
            effect->pos9A = 0;
            effect->speedA0 = 0;
            effect->speedA4 = 0;
            effect->field9F = arg1;
            random = (func_150ADA20() % 80U) + 100;
            effect->fieldA8 = (f32)random * D_800A7224;
            effect->speedA2 = (s32)(arg0 * D_800A7228);
            random = func_150ADA20() % (u32)divisor;
            half = (s32)(arg0 * 0.5f);
            effect->inc9C = random - half;
            effect->inc9D = (func_150ADA20() % (u32)divisor) - half;
            effect->inc9E = (func_150ADA20() % (u32)divisor) - half;
            effect->timerA6 = 0;
            effect->fadeB3 = 0xFF;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517A644 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A644.s")
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
