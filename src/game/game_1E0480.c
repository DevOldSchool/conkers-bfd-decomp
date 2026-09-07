#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E0480.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B3014
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1E0480Inner {
    u8 pad0[0x44];
    s32 field_44;
} Game1E0480Inner;

typedef struct Game1E0480Object {
    u8 pad0[0x4C];
    Game1E0480Inner *inner;
} Game1E0480Object;

void func_151B2FD0(Game1E0480Object *arg0) {
    Game1E0480Inner *inner = arg0->inner;

    if (inner != 0) {
        inner->field_44 = 0;
    }
}
void func_151B2FE8(Game1E0480Object *arg0) {
    func_151B2FD0(arg0);
    func_1514933C(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E0480/func_151B3014.s")
