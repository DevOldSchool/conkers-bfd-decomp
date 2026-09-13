#include "types.h"

/*
 * Reviewed source unit: src/game/game_FEFF0.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D1B40
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameFEFF0State {
    u8 pad0[0x84];
    s32 flags;
} GameFEFF0State;

s32 func_1509BE40(s32, ...);

#pragma GLOBAL_ASM("asm/nonmatchings/game_FEFF0/func_150D1B40.s")

void func_150D1BD0(GameFEFF0State *arg0) {
    if (func_1509BE40(1, 0x402C, 6, 0x2000) != 0) {
        arg0->flags |= 0x10;
    } else {
        arg0->flags &= ~0x10;
    }
}
