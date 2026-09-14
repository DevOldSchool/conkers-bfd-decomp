#include "types.h"

/*
 * Reviewed source unit: src/game/game_119960.c
 * Boundary evidence: docs/evidence/game_remaining_single_function_units_up_to_256_bytes.md
 */

typedef struct Game119960State {
    u8 pad0[0x84];
    u32 flags_84;
} Game119960State;

s32 func_1509BE40(s32, ...);

void func_150EC4B0(Game119960State *arg0) {
    if (func_1509BE40(1, 0x4023, 6, 0x2000) != 0) {
        arg0->flags_84 |= 0x1010;
    } else {
        arg0->flags_84 &= ~0x1010;
    }
    arg0->flags_84 &= ~8;
}
