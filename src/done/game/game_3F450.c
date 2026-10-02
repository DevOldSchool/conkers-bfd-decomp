#include "types.h"

/*
 * Reviewed source unit: src/game/game_3F450.c
 * Boundary evidence: docs/evidence/game_small_units_3D6F0_3FC30.md
 */

void func_10022EC0(void *, f32 *, s32);
void *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_15011FA0(s32 arg0) {
    f32 sp34[3];
    void *temp_v0;

    sp34[0] = 50.0f;
    sp34[1] = 50.0f;
    sp34[2] = 0.0f;
    temp_v0 = func_15149130(0x12C, -1, 0x48, -1, 0, 0, 0xC, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, sp34, 0xC);
    }
}
