#include "types.h"

/*
 * Reviewed source unit: src/game/game_476D0.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1501A220
 * - func_1501A39C
 * - func_1501A490
 * - func_1501A680
 * - func_1501A6CC
 * - func_1501A764
 * - func_1501A8C0
 * - func_1501AE94
 * - func_1501B0A0
 * - func_1501B22C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A220.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A39C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A490.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A680.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A6CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A764.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A8C0.s")
extern s32 D_800BE620;
extern s32 D_800BE624;
extern s32 D_800BE628;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501AE94 CURRENT (1670) */
s32 func_1501AE94(s32 arg0) {
    void *temp_v0;

    temp_v0 = D_800BE628 + (arg0 * 0x180);
    if ((*(f32 *)((u8 *)temp_v0 + 0x2C) < 2.0f) || (((f32) D_800BE620 - 2.0f) < *(f32 *)((u8 *)temp_v0 + 0x30))) {
        return 0;
    }
    if ((*(f32 *)((u8 *)temp_v0 + 0x24) < 0.0f) || ((f32) D_800BE624 < *(f32 *)((u8 *)temp_v0 + 0x28))) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501AE94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501AE94.s")
void func_1501AF44(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fa0_3;
    f32 var_fa0_4;

    temp_fv0 = *arg0;
    if (temp_fv0 < 2.0f) {
        *arg0 = 2.0f;
    } else {
        temp_fv1 = (f32) D_800BE620 - 2.0f;
        if (temp_fv1 < temp_fv0) {
            var_fa0 = temp_fv1;
        } else {
            var_fa0 = temp_fv0;
        }
        *arg0 = var_fa0;
    }
    temp_fv0_2 = *arg2;
    if (temp_fv0_2 < 2.0f) {
        *arg2 = 2.0f;
    } else {
        temp_fv1_2 = (f32) D_800BE620 - 2.0f;
        if (temp_fv1_2 < temp_fv0_2) {
            var_fa0_2 = temp_fv1_2;
        } else {
            var_fa0_2 = temp_fv0_2;
        }
        *arg2 = var_fa0_2;
    }
    temp_fv0_3 = *arg1;
    if (temp_fv0_3 < 0.0f) {
        *arg1 = 0.0f;
    } else {
        temp_fv1_3 = (f32) D_800BE624;
        if (temp_fv1_3 < temp_fv0_3) {
            var_fa0_3 = temp_fv1_3;
        } else {
            var_fa0_3 = temp_fv0_3;
        }
        *arg1 = var_fa0_3;
    }
    temp_fv0_4 = *arg3;
    if (temp_fv0_4 < 0.0f) {
        *arg3 = 0.0f;
        return;
    }
    temp_fv1_4 = (f32) D_800BE624;
    if (temp_fv1_4 < temp_fv0_4) {
        var_fa0_4 = temp_fv1_4;
    } else {
        var_fa0_4 = temp_fv0_4;
    }
    *arg3 = var_fa0_4;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501B0A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501B22C.s")
