#include "types.h"

/*
 * Reviewed source unit: src/game/game_1AC2F0.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1517EE40
 * - func_1517EF00
 * - func_1517EFDC
 * - func_1517F08C
 * - func_1517F3A0
 * - func_1517F488
 * - func_1517F4D8
 * - func_1517F564
 * - func_1517F720
 * - func_1517F75C
 * - func_1517F7B4
 * - func_1517F814
 * - func_1517F9F4
 * - func_1517FB9C
 * - func_15180580
 * - func_151814FC
 * - func_15181D00
 * - func_15181D70
 * - func_15181DC8
 * - func_15181E18
 * - func_15181EE0
 * - func_15182670
 * - func_15182768
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517EE40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517EF00.s")
s32 func_1517EF00();                                /* extern */

s32 func_1517EFAC(void) {
    if (func_1517EF00() == 0xFF) {
        return 1;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517EFDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F08C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F3A0.s")
extern s32 D_800DDDB0[];
extern s32 D_800DDE28[];
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F488.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F4D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F564.s")
extern s8 D_800DDD88;
extern s8 D_800DDD89;
extern s8 D_800DDD8A;
extern s8 D_800DDD8B;
extern s8 D_800DDD8C;
extern s16 D_800DDE08;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517F720 CURRENT (1210) */
void func_1517F720(s8 arg0, s16 arg1, s8 arg2, s8 arg3, s32 arg4) {
    D_800DDE08 = arg1;
    D_800DDD88 = arg2;
    D_800DDD89 = 0;
    D_800DDD8A = arg0;
    D_800DDD8B = arg3;
    D_800DDD8C = (s8) arg4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517F720 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F720.s")
extern s32 D_80082FA0;
extern s32 D_800BE9E4;
extern u16 D_800DDE10;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517F75C CURRENT (1515) */
void func_1517F75C(void) {
    u16 *var_a0;
    u16 temp_v1;

    var_a0 = &D_800DDE10;
    if (D_80082FA0 >= 0) {
        do {
            temp_v1 = *var_a0;
            if (D_800BE9E4 < (s32) temp_v1) {
                *var_a0 = temp_v1 - D_800BE9E4;
            } else {
                *var_a0 = 0;
            }
            var_a0 += 2;
        } while ((u32) &(&D_800DDE10)[D_80082FA0] >= (u32) var_a0);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181D00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181D70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181DC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181E18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181EE0.s")
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
s32 func_1517F08C(u8, u8, u8, s32, s32);            /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15182768 CURRENT (264) */
s32 func_15182768(s32 arg0, u8 *arg1, s16 arg2) {
    s32 var_a0;
    u8 *temp_v0;

    var_a0 = arg0;
    temp_v0 = (void *)(arg1 + 0x28);
    if (arg2 == *(u8 *)((u8 *)arg1 + 0x2C)) {
        var_a0 = func_1517F08C(*(u8 *)((u8 *)temp_v0 + 3), *(u8 *)((u8 *)arg1 + 0x28), *(u8 *)((u8 *)temp_v0 + 1), (s32) *(u8 *)((u8 *)temp_v0 + 2), (s32) *(u8 *)((u8 *)temp_v0 + 4));
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15182768 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15182768.s")
