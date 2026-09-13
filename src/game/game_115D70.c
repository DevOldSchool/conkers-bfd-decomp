#include "types.h"

/*
 * Reviewed source unit: src/game/game_115D70.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E8930
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game115D70State {
    u8 pad0[0x28];
    f32 timer_28;
} Game115D70State;

f32 func_150ADA68(void);
void func_150E8930(Game115D70State *);
extern f32 D_800A1378;
extern f32 D_800BE9A4;

void func_150E88C0(Game115D70State *arg0) {
    arg0->timer_28 -= D_800BE9A4;
    if (arg0->timer_28 < 0.0f) {
        arg0->timer_28 = (func_150ADA68() * D_800A1378) + 201.0f;
        func_150E8930(arg0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_115D70/func_150E8930.s")
