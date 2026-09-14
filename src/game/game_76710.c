#include "types.h"

/*
 * Reviewed source unit: src/game/game_76710.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150492CC
 * - func_15049350
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game76710CallArgs {
    s32 words[9];
} Game76710CallArgs;

s32 func_150AAD98(Game76710CallArgs);

s32 func_15049260(Game76710CallArgs arg0) {
    return func_150AAD98(arg0);
}
extern f32 D_80099080;
extern f32 D_800CC220;
extern f32 D_800CC224;
extern f32 D_800CC228;
extern f32 D_800CC22C;
extern f32 D_800CC230;
extern f32 D_800CC234;
extern f32 D_800CC238;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150492CC CURRENT (1170) */
void func_150492CC(f32 arg0, f32 arg1, f32 arg2) {
    f32 var_fa0;

    var_fa0 = arg0;
    D_800CC220 = var_fa0;
    D_800CC224 = arg1;
    D_800CC228 = arg2;
    D_800CC22C = var_fa0 / 2.0f;
    D_800CC230 = arg1 / 2.0f;
    D_800CC234 = arg2 / 2.0f;
    if (var_fa0 == 0.0f) {
        var_fa0 = D_80099080;
    }
    D_800CC238 = arg1 / var_fa0;
    *(f32 *)((u8 *)&D_800CC238 + 4) = arg2 / var_fa0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150492CC */
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
