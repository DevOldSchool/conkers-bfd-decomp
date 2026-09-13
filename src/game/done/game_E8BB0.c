#include "types.h"

/*
 * Reviewed source unit: src/game/game_E8BB0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 */

typedef struct GameE8BB0State {
    u8 pad0[0x84];
    s32 flags;
} GameE8BB0State;

s32 func_1509BE40(s32, ...);

void func_150BB700(GameE8BB0State *arg0) {
    if (func_1509BE40(1, 0x4047, 6, 0x2000) != 0) {
        arg0->flags |= 0x1000;
    } else {
        arg0->flags &= ~0x1000;
    }
}
