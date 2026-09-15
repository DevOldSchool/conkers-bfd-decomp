#include "types.h"

/*
 * Reviewed source unit: src/game/game_142560.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151150BC
 * - func_1511515C
 * - func_151151FC
 * - func_151152A8
 * - func_15115368
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151150B0(s32 arg0) {

}
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151150BC CURRENT (110) */
void func_151150BC(void *arg0) {
    f32 temp_fv0;

    *(f32 *)((u8 *)arg0 + 0x68) = (f32) ((f32) (((s32) *(s32 *)((u8 *)arg0 + 0x3C) >> 0x10) * D_800BE9E4) * 0.00390625f);
    *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + *(f32 *)((u8 *)arg0 + 0x68));
    temp_fv0 = *(f32 *)((u8 *)arg0 + 8);
    if (temp_fv0 < 0.0f) {
        *(f32 *)((u8 *)arg0 + 8) = (f32) (temp_fv0 + 360.0f);
        return;
    }
    if (temp_fv0 >= 360.0f) {
        *(f32 *)((u8 *)arg0 + 8) = (f32) (temp_fv0 - 360.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151150BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151150BC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511515C CURRENT (10) */
void func_1511515C(void *arg0) {
    f32 temp_fv0;

    *(f32 *)((u8 *)arg0 + 0x64) = (f32) ((f32) (((s32) *(s32 *)((u8 *)arg0 + 0x3C) >> 0x10) * D_800BE9E4) * 0.00390625f);
    *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + *(f32 *)((u8 *)arg0 + 0x64));
    temp_fv0 = *(f32 *)((u8 *)arg0 + 4);
    if (temp_fv0 < 0.0f) {
        *(f32 *)((u8 *)arg0 + 4) = (f32) (temp_fv0 + 360.0f);
        return;
    }
    if (temp_fv0 >= 360.0f) {
        *(f32 *)((u8 *)arg0 + 4) = (f32) (temp_fv0 - 360.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511515C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_1511515C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151151FC CURRENT (10) */
void func_151151FC(void *arg0) {
    f32 temp_fv0;

    *(f32 *)((u8 *)arg0 + 0x60) = (f32) ((f32) (((s32) *(s32 *)((u8 *)arg0 + 0x3C) >> 0x10) * D_800BE9E4) * 0.00390625f);
    *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) + *(f32 *)((u8 *)arg0 + 0x60));
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0);
    if (temp_fv0 < 0.0f) {
        *(f32 *)((u8 *)arg0 + 0) = (f32) (temp_fv0 + 360.0f);
        return;
    }
    if (temp_fv0 >= 360.0f) {
        *(f32 *)((u8 *)arg0 + 0) = (f32) (temp_fv0 - 360.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151151FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151151FC.s")
void func_1511529C(s32 arg0) {

}
extern f32 D_800A2F8C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151152A8 CURRENT (130) */
void func_151152A8(void *arg0) {
    s16 temp_v1;
    s32 temp_a1;
    s32 var_v0;

    var_v0 = *(s32 *)((u8 *)arg0 + 0x7C);
    if (var_v0 == 0) {
        var_v0 = (s32) *(s16 *)((u8 *)arg0 + 0x12);
        *(s32 *)((u8 *)arg0 + 0x7C) = var_v0;
    }
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x12);
    if (*(u8 *)((u8 *)arg0 + 0x4F) & 4) {
        temp_a1 = *(s32 *)((u8 *)arg0 + 0x3C);
        if ((var_v0 - temp_v1) < (s16) temp_a1) {
            *(s16 *)((u8 *)arg0 + 0x12) = (s16) (temp_v1 - ((s16) (temp_a1 >> 0x10) * D_800BE9E4));
        }
    } else {
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) (s32) ((f32) temp_v1 + ((f32) (var_v0 - temp_v1) * D_800A2F8C * (f32) D_800BE9E4));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151152A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_151152A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_142560/func_15115368.s")
