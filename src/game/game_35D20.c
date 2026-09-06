#include "types.h"

/*
 * Reviewed source unit: src/game/game_35D20.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15008930
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800DCE50[2][104];

void func_15008870(s32 arg0) {
    s32 start = 0;
    s32 end = 104;
    s32 row;
    s32 column;

    if (arg0 == 1) {
        end = 101;
    } else if (arg0 == 2) {
        start = 101;
    }

    for (row = 0; row < 2; row++) {
        for (column = start; column < end; column++) {
            D_800DCE50[row][column] = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_35D20/func_15008930.s")
