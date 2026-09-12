#include "types.h"

/*
 * Reviewed source unit: src/game/game_803A0.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15052EF0
 * - func_15052F9C
 * - func_1505327C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_803A0/func_15052EF0.s")
extern u8 D_800CC2D0[];

void func_15052F58(s32 arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = D_800CC2D0 + (arg0 * 0x32C);
    temp_v0[0x13C] = 0;
    *(s32 *)(temp_v0 + 0x218) = 0;
    temp_v0[0x232] = arg1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_803A0/func_15052F9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_803A0/func_1505327C.s")
