#include "types.h"

/*
 * Reviewed source unit: src/game/game_3E5A0.c
 * Boundary evidence: docs/evidence/game_small_units_3D6F0_3FC30.md
 */

void func_15195AA8(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_80090318;
extern s32 D_8009031C;
extern s32 D_800B0E00;

void func_150110F0(void) {
    func_15195AA8(D_800B0E00, D_80090318, 0, -1, 0, 0, 0, 8);
    func_15195AA8(D_800B0E00, D_8009031C, 0, -1, 0, 0, 8, 0);
}
