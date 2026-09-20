#include "types.h"

/*
 * Reviewed source unit: src/game/game_119370.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EBEC0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_119370/func_150EBEC0.s")
s32 func_150EC3D4(void *arg0, void *arg1) {
    s32 temp_v0;

    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0) == 0) {
        return 0;
    }
    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if (temp_v0 == 0xFF) {
        return 0;
    }
    if ((temp_v0 == 0) || (temp_v0 == 1) || (temp_v0 == 2) || (temp_v0 == 3) ||
        (temp_v0 == 4) || (temp_v0 == 0x28) || (temp_v0 == 0x77)) {
        return 1;
    }
    return 0;
}
void func_151C3B0C(void *, f32, f32, f32, f32, s32, s32, s32);

void func_150EC45C(void *arg0) {
    func_151C3B0C(arg0, 1.0f, 1.0f, 1.0f, 0.0f, 0xFF, 0xFF, 0xFF);
}
