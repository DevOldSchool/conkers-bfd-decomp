#include "types.h"

/*
 * Reviewed source unit: src/game/game_3D6F0.c
 * Boundary evidence: docs/evidence/game_small_units_3D6F0_3FC30.md
 */

void func_15195AA8(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800902E4;
extern s32 D_800B0E00;
extern s32 D_800B0E04;

void func_15010240(void) {
    func_15195AA8(D_800B0E00, D_800902E4, 0, -1, 0, 0, 0, 4);
    func_15195AA8(D_800B0E04, D_800902E4, 0, -1, 0, 1, 0, 4);
}
