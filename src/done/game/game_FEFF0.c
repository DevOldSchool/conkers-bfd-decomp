#include "types.h"

/*
 * Reviewed source unit: src/game/game_FEFF0.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 */

typedef struct GameFEFF0State {
    u8 pad0[0x84];
    s32 flags;
} GameFEFF0State;

s32 func_1509BE40(s32, ...);

void func_151467A4(f32 *, f32, f32 *, f32, f32, f32, f32, f32 *);
void func_1515D4D4(s32, u8, u8, s32);
extern f32 D_800A08E0;
extern u8 D_800DCD20[];

void func_150D1B40(void *arg0) {
    f32 *sp28;

    sp28 = (f32 *)((u8 *)arg0 + 0x28);
    func_151467A4((f32 *)((u8 *)arg0 + 0x30), 10.0f,
                  (f32 *)((u8 *)arg0 + 0x2C), 86.0f,
                  170.0f, 255.0f, D_800A08E0, sp28);
    func_1515D4D4((s32) *sp28, D_800DCD20[1], D_800DCD20[2], 0);
}

void func_150D1BD0(GameFEFF0State *arg0) {
    if (func_1509BE40(1, 0x402C, 6, 0x2000) != 0) {
        arg0->flags |= 0x10;
    } else {
        arg0->flags &= ~0x10;
    }
}
