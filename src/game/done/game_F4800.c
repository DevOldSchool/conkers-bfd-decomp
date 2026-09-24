#include "types.h"

/*
 * Reviewed source unit: src/game/game_F4800.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 */

typedef struct GameF4800State {
    u8 pad0[0x84];
    u32 flags;
} GameF4800State;

s32 func_1509BE40(s32, ...);

void func_150C7350(GameF4800State *arg0) {
    arg0->flags |= 0x80004000;
    if (func_1509BE40(3, 0x2000, 0xAC, 0x4002, 0x4003, 0x4004) != 0) {
        arg0->flags |= 0x400000;
    } else {
        arg0->flags &= 0xFFBFFFFF;
    }
}
