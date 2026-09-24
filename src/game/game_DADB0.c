#include "types.h"

/*
 * Reviewed source unit: src/game/game_DADB0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AD900
 * - func_150AD930
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AD900 CURRENT (660) */
f32 func_150AD900(void *arg0, void *arg1) {
    f32 *a = arg0;
    f32 *b = arg1;

    return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AD900 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DADB0/func_150AD900.s")
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AD930 CURRENT (320) */
f32 func_150AD930(void *arg0) {
    f32 temp_ft0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 4);
    temp_ft0 = *(f32 *)((u8 *)arg0 + 8);
    return sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1) + (temp_ft0 * temp_ft0));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AD930 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DADB0/func_150AD930.s")
