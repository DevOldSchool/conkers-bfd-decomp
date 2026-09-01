#include "types.h"

/*
 * Reviewed source unit: src/game/game_3FC30.c
 * Boundary evidence: docs/evidence/game_small_units_3D6F0_3FC30.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15012780
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800DD410;
extern volatile s8 D_800DD418;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15012780 */
void func_15012780(void) {
    volatile s32 *current;

    D_800DD418 = 0;
    current = &D_800DD410;
loop:
    current++;
    current[-1] = 0;
    if (current != (volatile s32 *)&D_800DD418) {
        goto loop;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15012780 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3FC30/func_15012780.s")
