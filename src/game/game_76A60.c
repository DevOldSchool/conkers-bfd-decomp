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
#pragma GLOBAL_ASM("asm/nonmatchings/game_76A60/func_15049688.s")
