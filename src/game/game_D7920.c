#include "types.h"

/*
 * Reviewed source unit: src/game/game_D7920.c
 * Boundary evidence: docs/evidence/game_reconciled_text_data_tail_aa470.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AA470
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AA470 CURRENT (3940) */
s32 func_150AA470(void) {
    f32 x0;
    f32 x1;
    f32 x2;
    f32 y0;
    f32 y1;
    f32 y2;
    s32 result = 0;

    if (y0 > x0) {
        result = 1;
    }
    if (y0 < -x0) {
        result |= 2;
    }
    if (y1 > x1) {
        result |= 4;
    }
    if (y1 < -x1) {
        result |= 8;
    }
    if (y2 > x2) {
        result |= 0x10;
    }
    if (y2 < -x2) {
        result |= 0x20;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AA470 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D7920/func_150AA470.s")
