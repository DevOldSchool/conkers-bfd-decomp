#include "types.h"

/*
 * Reviewed source unit: src/game/game_76C90.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150497E0
 * - func_150498A4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150497E0 CURRENT (2133) */
f32 func_150497E0(s32 arg0, s32 arg1, f32 arg2) {
    f32 coefficients[3];
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 *temp_v0;

    temp_v0 = (u8 *)arg0;
    temp_v0 += arg1 * 4;
    temp_fa0 = *(f32 *)((u8 *)temp_v0 + 0);
    temp_fa1 = -0.5f * temp_fa0;
    temp_ft4 = *(f32 *)((u8 *)temp_v0 + 4);
    temp_fv0 = *(f32 *)((u8 *)temp_v0 + 8);
    temp_fv1 = *(f32 *)((u8 *)temp_v0 + 0xC);
    coefficients[0] = (temp_fv1 * 0.5f) + (temp_fa1 + (1.5f * temp_ft4) + (-1.5f * temp_fv0));
    coefficients[1] = (temp_fv1 * -0.5f) + (temp_fa0 + (-2.5f * temp_ft4) + (2.0f * temp_fv0));
    coefficients[2] = (temp_fv0 * 0.5f) + temp_fa1;
    return (((((coefficients[0] * arg2) + coefficients[1]) * arg2) + coefficients[2]) * arg2) + temp_ft4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150497E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_76C90/func_150497E0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150498A4 CURRENT (1744) */
f32 func_150498A4(s32 arg0, s32 arg1, f32 arg2, f32 *arg3) {
    f32 coefficients[3];
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 *temp_v0;

    temp_v0 = (f32 *)arg0 + arg1;
    temp_fa0 = *(f32 *)((u8 *)temp_v0 + 0);
    temp_fa1 = -0.5f * temp_fa0;
    temp_ft4 = *(f32 *)((u8 *)temp_v0 + 4);
    temp_fv0 = *(f32 *)((u8 *)temp_v0 + 8);
    temp_fv1 = *(f32 *)((u8 *)temp_v0 + 0xC);
    coefficients[0] = (temp_fv1 * 0.5f) + (temp_fa1 + (1.5f * temp_ft4) + (-1.5f * temp_fv0));
    coefficients[1] = (temp_fv1 * -0.5f) + (temp_fa0 + (-2.5f * temp_ft4) + (2.0f * temp_fv0));
    coefficients[2] = (temp_fv0 * 0.5f) + temp_fa1;
    temp_fa0 = coefficients[0];
    temp_ft5 = coefficients[1];
    temp_fa1 = coefficients[2];
    *arg3 = (((temp_fa0 * 3.0f * arg2) + (2.0f * temp_ft5)) * arg2) + temp_fa1;
    temp_fv1 = (((((temp_fa0 * arg2) + temp_ft5) * arg2) + temp_fa1) * arg2) + temp_ft4;
    return temp_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150498A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_76C90/func_150498A4.s")
