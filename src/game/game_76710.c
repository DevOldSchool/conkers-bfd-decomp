#include "types.h"

/*
 * Reviewed source unit: src/game/game_76710.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15049260
 * - func_150492CC
 * - func_15049350
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_76710/func_15049260.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_76710/func_150492CC.s")
extern f32 D_800CC210;
extern f32 D_800CC214;
extern f32 D_800CC218;
extern f32 D_800CC21C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15049350 CURRENT (2556) */
void func_15049350(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 sp4;
    f32 sp0;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)&arg0 - *(f32 *)&arg3;
    sp0 = *(f32 *)&arg0;
    temp_fv1 = *(f32 *)&arg1 - *(f32 *)&arg4;
    sp4 = *(f32 *)&arg1;
    temp_fa0 = *(f32 *)&arg2 - *(f32 *)&arg5;
    temp_fa1 = *(f32 *)&arg0 - *(f32 *)&arg6;
    temp_ft4 = *(f32 *)&arg1 - *(f32 *)&arg7;
    temp_ft5 = *(f32 *)&arg2 - *(f32 *)&arg8;
    temp_ft1 = (temp_fv1 * temp_ft5) - (temp_fa0 * temp_ft4);
    D_800CC210 = temp_ft1;
    sp10 = temp_ft1;
    spC = (-temp_fv0 * temp_ft5) + (temp_fa0 * temp_fa1);
    D_800CC214 = spC;
    sp8 = (temp_fv0 * temp_ft4) - (temp_fv1 * temp_fa1);
    D_800CC218 = sp8;
    D_800CC21C = (*(f32 *)&arg2 * sp8) + ((temp_ft1 * sp0) + (spC * sp4));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15049350 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_76710/func_15049350.s")
