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
 * - func_1517A958
 * - func_1517A9A8
 * - func_1517AA20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_15179FE0.s")
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517A958 CURRENT (115) */
s32 func_1517A958(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a0;

    var_a0 = arg0;
    D_800DD450 = -1;
    if ((arg1 == 0xC) || (arg1 == 0x59)) {
        var_a0 = func_1517A394(var_a0);
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517A958 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517A958.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7490/func_1517AA20.s")
void func_1510B7B4(s32 arg0, s32 arg1);

void func_1517AB7C(s32 arg0, s32 arg1, s16 arg2) {
    func_1510B7B4(arg0, arg2);
}
