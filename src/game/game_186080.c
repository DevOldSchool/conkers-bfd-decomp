#include "types.h"

/*
 * Reviewed source unit: src/game/game_186080.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15158BD0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_186080/func_15158BD0.s")
/* Call context: func_1514EDF0: unique active project prototype */
/* Call context: func_15169804: unique active project prototype */
void func_1514EDF0(s32, s32);
void func_15169804(s32);

void func_15158CD4(void *arg0) {
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0x18));
    func_15169804((s32) arg0);
}
