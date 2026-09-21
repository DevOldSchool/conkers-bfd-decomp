#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B4A90.c
 * Boundary evidence: docs/evidence/game_raw_clipping_resource_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151875E0
 * - func_15187978
 * - func_15187A98
 * - func_15187D6C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B4A90/func_151875E0.s")
void func_10004074(s32);
void func_1516972C(u8 *);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15187978 CURRENT (1907) */
void func_15187978(s32 arg0) {
    f32 temp_fv0;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 var_a0;
    s16 var_v1;
    s32 var_a2;
    s32 var_a1;
    s32 temp_v0_3;
    s32 var_v0;

    var_a2 = arg0;
    temp_v0 = *(s16 *)(var_a2 + 0xA8);
    if (temp_v0 < 0) {
        func_10004074(*(s32 *)(var_a2 + 0xA4));
        func_1516972C((u8 *)var_a2);
        return;
    }
    *(s16 *)(var_a2 + 0xA8) = temp_v0 + D_800BE9E4;
    temp_v0_2 = *(s16 *)(var_a2 + 0xA8);
    if (*(s16 *)(var_a2 + 0xAA) < temp_v0_2) {
        *(s16 *)(var_a2 + 0xA8) = -0xA;
        return;
    }
    var_a1 = 0;
    if (temp_v0_2 >= 0) {
        do {
            temp_v0_3 = *(s32 *)(var_a2 + 0xA4) + var_a1;
            temp_v1 = *(s16 *)(temp_v0_3 + 0x94);
            if (temp_v1 < *(s16 *)(temp_v0_3 + 0x96)) {
                *(s16 *)(temp_v0_3 + 0x94) = temp_v1 + D_800BE9E4;
                var_v0 = *(s32 *)(var_a2 + 0xA4) + var_a1;
                var_a0 = *(s16 *)(var_v0 + 0x96);
                var_v1 = *(s16 *)(var_v0 + 0x94);
                if (var_a0 < var_v1) {
                    *(s16 *)(var_v0 + 0x94) = var_a0;
                    var_v0 = *(s32 *)(var_a2 + 0xA4) + var_a1;
                    var_v1 = *(s16 *)(var_v0 + 0x94);
                    var_a0 = *(s16 *)(var_v0 + 0x96);
                }
                temp_fv0 = *(f32 *)(var_v0 + 0x8C);
                *(f32 *)(var_v0 + 0x90) +=
                    temp_fv0 - (((temp_fv0 / 3.0f) * (f32)var_v1) /
                                (f32)var_a0);
            }
            var_a1 += 0xA0;
        } while (var_a1 != 0x780);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15187978 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B4A90/func_15187978.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B4A90/func_15187A98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B4A90/func_15187D6C.s")
