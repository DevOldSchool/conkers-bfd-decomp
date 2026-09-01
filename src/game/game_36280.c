#include "types.h"

/*
 * Reviewed source unit: src/game/game_36280.c
 * Boundary evidence: docs/evidence/game_remaining_units_up_to_64_bytes.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15008DD0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800DD460;
extern s32 D_800DD468;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15008DD0 */
void func_15008DD0(void) {
    s32 *end = &D_800DD468;
    s32 *current = &D_800DD460;

loop:
    current++;
    current[-1] = 0;
    if (current != end) {
        goto loop;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15008DD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36280/func_15008DD0.s")
