#include "types.h"

/*
 * Reviewed source unit: src/game/game_3FBD0.c
 * Boundary evidence: docs/evidence/game_small_units_3D6F0_3FC30.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15012720
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15012720 CURRENT (630) */
s32 func_15012720(void) {
    if (D_800BE9F0 == 0) {
        goto return_two;
    }
    if (D_800BE9F0 == 0x28) {
        return 6;
    }
    if (D_800BE9F0 == 0x2C) {
        goto return_two;
    }
    if (D_800BE9F0 != 0x37) {
        return 5;
    }

return_two:
    return 2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15012720 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3FBD0/func_15012720.s")
