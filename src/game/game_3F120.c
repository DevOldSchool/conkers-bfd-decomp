#include "types.h"

/*
 * Reviewed source unit: src/game/game_3F120.c
 * Boundary evidence: docs/evidence/game_small_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15011CC0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15103800(void);
extern s32 D_800D9AA0[3];

void func_15011C70(void) {
    D_800D9AA0[0] = 0;
    D_800D9AA0[1] = 0;
    D_800D9AA0[2] = 0;
    func_15103800();
}
void func_15011CA0(void) {
    func_15103800();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_3F120/func_15011CC0.s")
