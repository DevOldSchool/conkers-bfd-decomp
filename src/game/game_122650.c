#include "types.h"

/*
 * Reviewed source unit: src/game/game_122650.c
 * Boundary evidence: docs/evidence/game_small_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F51E8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_80088B40;

void func_150F51A0(s32 arg0, s32 arg1) {
    D_80088B40 = 1;
}
s32 func_150F51BC(void) {
    if (D_80088B40 != 0) {
        D_80088B40 = 0;
        return 1;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_122650/func_150F51E8.s")
