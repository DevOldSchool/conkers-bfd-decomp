#include "types.h"

/*
 * Reviewed source unit: src/game/game_D4C20.c
 * Boundary evidence: docs/evidence/game_remaining_units_up_to_64_bytes.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A7770
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A7770 CURRENT (700) */
void func_150A7770(s8 *arg0, s32 arg1, s32 arg2) {
loop:
    *arg0 = arg1;
    arg2--;
    arg0++;
    if (arg2 != 0) {
        goto loop;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A7770 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4C20/func_150A7770.s")
