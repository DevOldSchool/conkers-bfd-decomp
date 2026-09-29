#include "types.h"

/*
 * Reviewed source unit: src/game/game_126ED0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 */

typedef struct Game126ED0State {
    u8 pad0[0x84];
    volatile u32 flags;
    u8 pad88[0x108];
    f32 field190;
} Game126ED0State;

s32 func_1509BE40(s32, ...);

void func_150F9A20(Game126ED0State *arg0) {
    if (func_1509BE40(1, 0x4025, 6, 0x2000) != 0) {
        *(u32 *)((u8 *)arg0 + 0x84) |= 0x80;
        arg0->flags = *(u32 *)((u8 *)arg0 + 0x84) & ~8;
        arg0->field190 = 85.0f;
        return;
    }
    *(u32 *)((u8 *)arg0 + 0x84) &= ~0x80;
    arg0->flags = *(u32 *)((u8 *)arg0 + 0x84) | 8;
    arg0->field190 = 0.0f;
}
