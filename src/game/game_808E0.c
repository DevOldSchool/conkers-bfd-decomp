#include "types.h"

/*
 * Reviewed source unit: src/game/game_808E0.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15053430
 * - func_150535F4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_808E0/func_15053430.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_808E0/func_150535F4.s")
/* Call context: func_1506160C: unique active project prototype */
void func_1506160C(u8 *, s32, s32, s32, u8);

void func_15053694(u8 *arg0) {
    *(s32 *)(arg0 + 0) = 8;
    *(s16 *)(arg0 + 0xE4) = 0;
    *(s16 *)(arg0 + 0xE6) = 0;
    func_1506160C(arg0, 6, 0, 0, 0U);
}
