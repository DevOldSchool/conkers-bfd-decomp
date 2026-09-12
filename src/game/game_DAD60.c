#include "types.h"

/*
 * Reviewed source unit: src/game/game_DAD60.c
 * Boundary evidence: docs/evidence/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AD8B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AD8B0 CURRENT (765) */
void func_150AD8B0(void *arg0, void *arg1, void *arg2) {
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft2;
    f32 temp_ft3;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 4);
    temp_ft0 = *(f32 *)((u8 *)arg1 + 0);
    temp_ft1 = *(f32 *)((u8 *)arg1 + 4);
    temp_ft2 = *(f32 *)((u8 *)arg1 + 8);
    temp_ft3 = *(f32 *)((u8 *)arg0 + 8);
    *(f32 *)((u8 *)arg2 + 8) = (temp_fv0 * temp_ft1) - (temp_fv1 * temp_ft0);
    *(f32 *)((u8 *)arg2 + 0) = (temp_fv1 * temp_ft2) - (temp_ft3 * temp_ft1);
    *(f32 *)((u8 *)arg2 + 4) = (temp_ft3 * temp_ft0) - (temp_fv0 * temp_ft2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AD8B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAD60/func_150AD8B0.s")
