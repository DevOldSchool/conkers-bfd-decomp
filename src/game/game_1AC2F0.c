#include "types.h"

/*
 * Reviewed source unit: src/game/game_1AC2F0.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1517EF00
 * - func_1517F08C
 * - func_1517F488
 * - func_1517F564
 * - func_1517F75C
 * - func_1517F7B4
 * - func_1517F814
 * - func_1517F9F4
 * - func_1517FB9C
 * - func_15180580
 * - func_151814FC
 * - func_15181DC8
 * - func_15181EE0
 * - func_15182670
 * - func_15182768
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1AC2F0Color {
    u8 red;
    u8 green;
    u8 blue;
} Game1AC2F0Color;

extern Game1AC2F0Color D_800DDDA0[];
extern u8 D_800DDDC0[];
extern s8 D_800DDDAC[];
extern s32 D_800DDE28[];
extern s32 D_800DDDB0[];
void func_1517EE40(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 arg4, s32 arg5) {
    Game1AC2F0Color *temp_a0;
    s8 *temp_v0;

    temp_v0 = &D_800DDDAC[arg5];
    if ((arg4 != *temp_v0) || (D_800DDDB0[arg5] < D_800DDE28[arg5]) || (D_800DDDC0[arg5] != 0)) {
        temp_a0 = &D_800DDDA0[arg5];
        temp_a0->green = (u8)arg1;
        temp_a0->blue = (u8)arg2;
        temp_a0->red = (u8)arg0;
        D_800DDE28[arg5] = arg3;
        D_800DDDB0[arg5] = 0;
        *temp_v0 = arg4;
        D_800DDDC0[arg5] = 0;
    }
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517EF00 CURRENT (495) */
s32 func_1517EF00(s32 arg0) {
    s32 temp_a1;
    u8 temp_v0;
    s32 var_v1;

    temp_v0 = D_800DDDC0[arg0];
    if (temp_v0 != 0) {
        var_v1 = temp_v0;
    } else {
        temp_a1 = D_800DDE28[arg0];
        if (temp_a1 != 0) {
            var_v1 = (D_800DDDB0[arg0] * 0xFF) / temp_a1;
            if (var_v1 >= 0x100) {
                var_v1 = 0xFF;
            }
        } else {
            var_v1 = 0xFF;
        }
        if (D_800DDDAC[arg0] == 0) {
            var_v1 = 0xFF - var_v1;
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517EF00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517EF00.s")

s32 func_1517EF00(s32);

s32 func_1517EFAC(s32 arg0) {
    if (func_1517EF00(arg0) == 0xFF) {
        return 1;
    }
    return 0;
}
extern s32 D_80082FA0;
extern f32 D_800DDDC8[];

s32 func_1517EFDC(void) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;

    temp_v0 = D_80082FA0;
    var_s1 = -1;
    var_s0 = 0;
    if (temp_v0 >= 0) {
        do {
            if ((func_1517EF00(var_s0) > 0) || (D_800DDDC8[var_s0] > 0.0f)) {
                var_s1 += 1;
            }
            var_s0 += 1;
        } while ((temp_v0 = D_80082FA0) >= var_s0);
    }
    if (var_s1 == temp_v0) {
        return 1;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F08C.s")

s32 func_1517F08C(s32, s32, s32, s32, s32, s32);

s32 func_1517F3A0(s32 arg0, s32 arg1) {
    s32 intensity;
    Game1AC2F0Color *color;

    intensity = func_1517EF00(arg1);
    if (intensity == 0) {
        return arg0;
    }
    color = &D_800DDDA0[arg1];
    return func_1517F08C(arg0, intensity, color->red, color->green,
                          color->blue, arg1);
}
extern s32 D_800BE9E4;

s32 func_1517F40C(s32 arg0) {
    if (D_800DDDB0[arg0] >= D_800DDE28[arg0]) {
        return 1;
    }
    return 0;
}
void func_1517F448(s32 arg0) {
    if (D_800DDDB0[arg0] != D_800DDE28[arg0]) {
        D_800DDDB0[arg0] += D_800BE9E4;
    }
}
extern s8 D_800DDD90;
extern s8 D_800DDD9C;
extern u16 D_800DDE10;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517F488 CURRENT (115) */
void func_1517F488(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s8 *temp_v0;
    s32 temp_t9;

    temp_v0 = &(&D_800DDD90)[arg5 * 3];
    temp_t9 = arg5;
    temp_v0[0] = arg0;
    temp_v0[1] = arg1;
    temp_v0[2] = arg2;
    (&D_800DDD9C)[temp_t9] = arg3;
    (&D_800DDE10)[temp_t9] = arg4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517F488 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F488.s")
s32 func_1517F4D8(s32 arg0, s32 arg1) {
    s32 temp_a1;
    u8 *temp_v0;
    u8 *entry = (u8 *)&D_800DDD9C + arg1;

    if (*(u16 *)((u8 *)&D_800DDE10 + (arg1 * 2)) == 0) {
        return arg0;
    }
    temp_a1 = *entry;
    if (temp_a1 == 0) {
        return arg0;
    }
    temp_v0 = (u8 *)&D_800DDD90 + (arg1 * 3);
    return func_1517F08C(arg0, (s32)temp_a1, temp_v0[0], temp_v0[1], temp_v0[2], arg1);
}
extern s8 D_800DDD88;
extern s8 D_800DDD89;
extern s8 D_800DDD8A;
extern s8 D_800DDD8B;
extern s8 D_800DDD8C;
extern s16 D_800DDE08;
extern u8 D_8008D010[][6];
f32 func_15048A40(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517F564 CURRENT (3177) */
s32 func_1517F564(s32 arg0) {
    f32 fraction;
    f32 scale;
    f32 red;
    f32 green;
    f32 blue;
    s32 intensity;
    u8 *colors;
    u8 red0;
    u8 green0;
    u8 blue0;

    if ((u16)D_800DDE08 == 0) {
        return arg0;
    }
    if ((u8)D_800DDD8B == 0) {
        return arg0;
    }
    intensity = (u8)D_800DDD8B;
    if ((u8)D_800DDD8C != 0) {
        scale = (func_15048A40((u8)D_800DDD89, intensity) + 1.0f) * 0.5f;
        intensity = (s32)((f32)(u8)D_800DDD8B * scale);
        fraction = 0.0f;
    }
    colors = D_8008D010[(u8)D_800DDD8A];
    red0 = colors[0];
    red = (f32)red0 + (f32)(colors[3] - red0) * fraction;
    green0 = colors[1];
    green = (f32)green0 + (f32)(colors[4] - green0) * fraction;
    blue0 = colors[2];
    blue = (f32)blue0 + (f32)(colors[5] - blue0) * fraction;
    return func_1517F08C(arg0, intensity, (s32)red, (s32)green, (s32)blue, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517F564 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F564.s")

void func_1517F720(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    D_800DDE08 = arg1;
    D_800DDD88 = arg2;
    D_800DDD89 = 0;
    D_800DDD8A = arg0;
    D_800DDD8B = arg3;
    D_800DDD8C = (s8) arg4;
}
extern s32 D_80082FA0;
extern s32 D_800BE9E4;
extern u16 D_800DDE10;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517F75C CURRENT (775) */
void func_1517F75C(void) {
    u16 *var_a0;
    u16 *end;
    u16 temp_v1;
    s32 max_index;
    s32 decrement;

    var_a0 = &D_800DDE10;
    max_index = D_80082FA0;
    if (max_index >= 0) {
        end = &D_800DDE10 + max_index;
        decrement = D_800BE9E4;
        do {
            temp_v1 = *var_a0;
            if (decrement < (s32) temp_v1) {
                *var_a0 = temp_v1 - decrement;
            } else {
                *var_a0 = 0;
            }
            var_a0++;
        } while ((u32) end >= (u32) var_a0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517F75C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F75C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517F7B4 CURRENT (30) */
void func_1517F7B4(void) {
    if ((u16) D_800DDE08 != 0) {
        if (D_800BE9E4 < (s32) (u16) D_800DDE08) {
            D_800DDE08 = (u16) D_800DDE08 - D_800BE9E4;
        } else {
            D_800DDE08 = 0;
        }
        D_800DDD89 = (u8) D_800DDD89 + ((u8) D_800DDD88 * D_800BE9E4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517F7B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F7B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F814.s")
extern s32 D_800BE628;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517F9F4 CURRENT (1645) */
void *func_1517F9F4(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_ft1;
    s32 temp_ft1_2;
    s32 temp_ft3;
    s32 temp_ft5;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a1;
    s32 var_a3;
    s32 var_t3;
    s32 var_t3_2;
    s32 var_t3_3;
    s32 var_t3_4;
    s32 var_v1;
    u8 *temp_a0;
    u8 *temp_v1;

    var_a1 = arg1;
    {
        s32 var_a2 = arg2;
    var_a3 = arg3;
    var_v1 = arg4;
    if (var_a3 < var_a1) {
        temp_v0 = var_a1;
        var_a1 = var_a3;
        var_a3 = temp_v0;
    }
    if (var_v1 < var_a2) {
        temp_v0_2 = var_a2;
        var_a2 = var_v1;
        var_v1 = temp_v0_2;
    }
    temp_a0 = (void *)(D_800BE628 + (arg5 * 0x180));
    temp_ft1 = (s32) *(f32 *)((u8 *)temp_a0 + 0x2C);
    temp_ft3 = (s32) *(f32 *)((u8 *)temp_a0 + 0x24);
    temp_ft1_2 = (s32) *(f32 *)((u8 *)temp_a0 + 0x28);
    temp_ft5 = (s32) *(f32 *)((u8 *)temp_a0 + 0x30);
    if ((var_a2 >= temp_ft1_2) || (temp_ft3 >= var_v1) || (var_a1 >= temp_ft5) || (temp_ft1 >= var_a3)) {
        return arg0;
    }
    if (var_a1 < temp_ft1) {
        var_a0 = temp_ft1;
    } else {
        var_t3 = var_a1;
        if (temp_ft5 < var_a1) {
            var_t3 = temp_ft5;
        }
        var_a0 = var_t3;
    }
    if (var_a2 < temp_ft3) {
        var_a0_2 = temp_ft3;
    } else {
        var_t3_2 = var_a2;
        if (temp_ft1_2 < var_a2) {
            var_t3_2 = temp_ft1_2;
        }
        var_a0_2 = var_t3_2;
    }
    if (var_a3 < temp_ft1) {
        var_a0_3 = temp_ft1;
    } else {
        var_t3_3 = var_a3;
        if (temp_ft5 < var_a3) {
            var_t3_3 = temp_ft5;
        }
        var_a0_3 = var_t3_3;
    }
    if (var_v1 < temp_ft3) {
        var_a0_4 = temp_ft3;
    } else {
        var_t3_4 = var_v1;
        if (temp_ft1_2 < var_v1) {
            var_t3_4 = temp_ft1_2;
        }
        var_a0_4 = var_t3_4;
    }
    temp_v1 = arg0;
    arg0 = (void *)(temp_v1 + 8);
    *(s32 *)((u8 *)temp_v1 + 4) = (s32) (((var_a0 & 0x3FF) << 0xE) | ((var_a0_2 & 0x3FF) * 4));
    *(s32 *)((u8 *)temp_v1 + 0) = (s32) (((var_a0_3 & 0x3FF) << 0xE) | 0xF6000000 | ((var_a0_4 & 0x3FF) * 4));
    return arg0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517F9F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F9F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517FB9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15180580.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_151814FC.s")
extern f32 D_800DDDC8[];

s32 func_15181CC8(s32 arg0) {
    if (D_800DDDC8[arg0] == 0.0f) {
        return 1;
    }
    return 0;
}
typedef struct Game1AC2F0Vector {
    f32 field_0;
    f32 field_4;
} Game1AC2F0Vector;

extern f32 D_800A72AC;
extern f32 D_800DDDD8[];
extern u8 D_800DDDE8[];
extern s8 D_800DDE1C[];

void func_15181D00(s32 arg0, s32 arg1) {
    Game1AC2F0Vector *vector;

    if (arg1 == 0) {
        D_800DDDC8[arg0] = 0.0f;
    } else {
        D_800DDDD8[arg0] = 0.0f;
        vector = (Game1AC2F0Vector *)(D_800DDDE8 + (arg0 * 8));
        D_800DDDC8[arg0] = D_800A72AC;
        vector->field_0 = 0.0f;
        vector->field_4 = 0.0f;
    }
    D_800DDE1C[arg0] = arg1;
}
extern f32 D_800A72B0;
extern f32 D_800DDDD8[];
extern f32 D_800DDDC8[];
extern u8 D_800DDDE8[];
extern s8 D_800DDE20[];

void func_15181D70(s32 arg0) {
    void *temp_v1;

    D_800DDDD8[arg0] = D_800A72B0;
    D_800DDDC8[arg0] = 0.0f;
    temp_v1 = D_800DDDE8 + (arg0 * 8);
    *(f32 *)temp_v1 = 0.0f;
    *(f32 *)((u8 *)temp_v1 + 4) = 0.0f;
    D_800DDE20[arg0] = 1;
}
extern f32 D_800DDDD8[];
extern u8 D_800DDDE8[];
extern s8 D_800DDE20[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15181DC8 CURRENT (105) */
void func_15181DC8(s32 arg0) {
    f32 temp_ft0;

    temp_ft0 = 0.0f;
    D_800DDDD8[arg0] = temp_ft0;
    D_800DDDC8[arg0] = 0.0f;
    D_800DDDE8[arg0].field_0 = 0.0f;
    D_800DDDE8[arg0].field_4 = 0.0f;
    D_800DDE20[arg0] = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15181DC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181DC8.s")
extern f32 D_800A72B4;
extern u8 D_800BE616;
extern s8 D_800DDE3C;

void func_15181E18(s32 arg0) {
    Game1AC2F0Color *temp_v0;
    void *temp_v0_2;

    if (D_800BE616 != 0) {
        temp_v0 = &D_800DDDA0[arg0];
        temp_v0->red = 0;
        temp_v0->green = 0;
        temp_v0->blue = 0;
        D_800DDE28[arg0] = 0x19;
        D_800DDDB0[arg0] = 0;
        D_800DDDAC[arg0] = 0;
        D_800DDDC0[arg0] = 0;
        return;
    }
    *(&D_800DDE3C + arg0) = 1;
    D_800DDDC8[arg0] = 1.0f;
    temp_v0_2 = (arg0 * 8) + D_800DDDE8;
    *(f32 *)((u8 *)temp_v0_2 + 0) = 0.0f;
    *(f32 *)((u8 *)temp_v0_2 + 4) = 0.0f;
    D_800DDDD8[arg0] = D_800A72B4;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181EE0.s")
void *func_10022EC0(void *, const void *, u32);
void *func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15182670 CURRENT (3035) */
void func_15182670(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4,
                   u8 arg5, u8 arg6, s32 arg7) {
    struct {
        u8 value0;
        u8 value1;
        u8 value2;
        u8 value3;
        u8 value4;
        u8 pad;
        s16 quotient;
        s32 trailing;
    } payload;
    void *result;

    if (arg4 > 0) {
        payload.value0 = arg0;
        payload.quotient = (s16)((s32)arg3 / arg4);
        payload.value3 = arg3;
        payload.value1 = arg1;
        payload.value2 = arg2;
        payload.value4 = arg5;
        result = func_15149130(arg4, -1, 0x39, 3, 1, 0, 8, arg6, arg7);
        if (result != 0) {
            func_10022EC0((u8 *)result + 0x28, &payload, 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15182670 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15182670.s")
typedef struct Game1AC2F0Object {
    u8 pad0[0xE];
    s16 field_E;
    u8 pad10[0x1B];
    s8 field_2B;
    u8 pad2C[2];
    s16 field_2E;
} Game1AC2F0Object;

void func_15182748(Game1AC2F0Object *arg0) {
    arg0->field_2B = arg0->field_2E * arg0->field_E;
}
s32 func_1517F08C(s32, s32, s32, s32, s32, s32);  /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15182768 CURRENT (100) */
s32 func_15182768(s32 arg0, u8 *arg1, s16 arg2) {
    u8 *temp_v0;

    temp_v0 = (void *)(arg1 + 0x28);
    if (arg2 == *(u8 *)((u8 *)arg1 + 0x2C)) {
        arg0 = func_1517F08C(arg0, *(u8 *)((u8 *)temp_v0 + 3),
                                *(u8 *)temp_v0,
                                *(u8 *)((u8 *)temp_v0 + 1),
                                (s32)*(u8 *)((u8 *)temp_v0 + 2),
                                (s32)*(u8 *)((u8 *)temp_v0 + 4));
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15182768 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15182768.s")
