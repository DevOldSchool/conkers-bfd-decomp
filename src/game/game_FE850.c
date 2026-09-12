#include "types.h"

/*
 * Reviewed source unit: src/game/game_FE850.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D13A0
 * - func_150D149C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_FE850/func_150D13A0.s")
/* Call context: func_151149AC: unique active project prototype */
s32 func_151149AC(u8);
extern u8 D_800CC2D0;

void func_150D1410(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_151149AC(0xF9U);
    if (temp_v0 != 0) {
        if (((arg0 - (s32)&D_800CC2D0) / 0x32C) == 0) {
            *(s8 *)((u8 *)temp_v0 + 0x6E) = 1;
            return;
        }
        *(s8 *)((u8 *)temp_v0 + 0x6E) = 0;
    }
}

void func_150D146C(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_151149AC(0xF9U);
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 0x6E) = 1;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_FE850/func_150D149C.s")
