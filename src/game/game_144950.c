#include "types.h"

/*
 * Reviewed source unit: src/game/game_144950.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151174A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_151172D8(void *arg0, f32 arg1);            /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151174A0 CURRENT (185) */
void func_151174A0(void *arg0) {
    *(f32 *)((u8 *)arg0 + 8) = func_151172D8(*(f32 *)((u8 *)arg0 + 8));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151174A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_144950/func_151174A0.s")
void func_151174C8(u8 *arg0) {
    *(f32 *)(arg0 + 4) = func_151172D8(arg0, *(f32 *)(arg0 + 4));
}
