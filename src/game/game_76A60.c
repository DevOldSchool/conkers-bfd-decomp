#include "types.h"

/*
 * Reviewed source unit: src/game/game_76A60.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150495B0
 * - func_15049688
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150495B0 CURRENT (1681) */
void func_150495B0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 sp4;
    f32 temp_ft2;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 var_fv0;
    f32 var_fv1;

    temp_fv0 = arg1 - *arg0;
    if (temp_fv0 < 0.0f) {
        var_fv1 = -1.0f;
    } else {
        var_fv1 = 1.0f;
    }
    temp_ft5 = *arg2;
    *arg2 = temp_ft5 + (((temp_fv0 * arg3) - temp_ft5) * arg4 * arg5);
    temp_ft2 = (*arg2 * arg5) + *arg0;
    sp4 = temp_ft2;
    if (arg1 < temp_ft2) {
        var_fv0 = -1.0f;
    } else {
        var_fv0 = 1.0f;
    }
    if (var_fv0 == var_fv1) {
        *arg0 = sp4;
        return;
    }
    *arg0 = arg1;
    *arg2 = 0.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150495B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_76A60/func_150495B0.s")
f32 func_15048A70(f32, f32);
void func_15048758(f32 *);
f32 fabsf(f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15049688 CURRENT (6912) */
void func_15049688(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 sp1C;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_ft4;
    f32 var_fv0;
    s32 var_t6;

    temp_fv0 = func_15048A70(*arg0, arg1);
    temp_fv0_2 = fabsf(temp_fv0);
    if (temp_fv0 < 0.0f) {
        var_ft4 = -1.0f;
    } else {
        var_ft4 = 1.0f;
    }
    temp_fa0 = *arg2;
    var_t6 = 0;
    *arg2 = temp_fa0 + (((temp_fv0 * arg3) - temp_fa0) * arg4 * arg5);
    if (temp_fv0_2 < 10.0f) {
        var_t6 = 1;
    }
    if (var_t6 != 0) {
        sp1C = var_ft4;
        if (func_15048A70((*arg2 * arg5) + *arg0, arg1) < 0.0f) {
            var_fv0 = -1.0f;
        } else {
            var_fv0 = 1.0f;
        }
        if (var_fv0 == var_ft4) {
            goto block_10;
        }
        *arg0 = arg1;
        *arg2 = 0.0f;
    } else {
block_10:
        *arg0 += *arg2 * arg5;
    }
    func_15048758(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15049688 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_76A60/func_15049688.s")
