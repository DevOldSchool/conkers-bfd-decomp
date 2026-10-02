#include "types.h"

/*
 * Reviewed source unit: src/game/game_10ECB0.c
 * Boundary evidence: docs/evidence/game_remaining_single_function_units_up_to_256_bytes.md
 */

typedef struct Game10ECB0State {
    u8 pad0[0x84];
    s32 flags;
} Game10ECB0State;

s32 func_1509BE40(s32, ...);

void func_150E1800(Game10ECB0State *arg0) {
    if (func_1509BE40(1, 0x403E, 6, 0x2000) != 0) {
        arg0->flags |= 0x20;
    } else {
        arg0->flags &= ~0x20;
    }
}
