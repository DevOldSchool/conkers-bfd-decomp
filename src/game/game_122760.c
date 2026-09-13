#include "types.h"

/*
 * Reviewed source unit: src/game/game_122760.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F52B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game122760State {
    u8 pad0[0x84];
    s32 flags;
} Game122760State;

s32 func_1509BE40(s32, ...);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F52B0 CURRENT (100) */
void func_150F52B0(Game122760State *arg0) {
    if (func_1509BE40(1, 0x401C, 6, 0x9000) != 0) {
        arg0->flags |= 0x80000000;
    } else {
        arg0->flags &= 0x7FFFFFFF;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F52B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_122760/func_150F52B0.s")

void func_150F5310(s32 arg0) {
    func_151827D0();
}
