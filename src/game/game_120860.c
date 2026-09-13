#include "types.h"

/*
 * Reviewed source unit: src/game/game_120860.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F33B0
 * - func_150F33F8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F33B0 CURRENT (25) */
void func_150F33B0(void *arg0) {
    if (*(f32 *)((u8 *)D_800DBFF0 + 0x300) < -2000.0f) {
        *(u8 *)((u8 *)arg0 + 0x4F) = (u8) (*(u8 *)((u8 *)arg0 + 0x4F) & 0xFFFE);
        return;
    }
    *(u8 *)((u8 *)arg0 + 0x4F) = (u8) (*(u8 *)((u8 *)arg0 + 0x4F) | 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F33B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_120860/func_150F33B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_120860/func_150F33F8.s")
