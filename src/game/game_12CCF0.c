#include "types.h"

/*
 * Reviewed source unit: src/game/game_12CCF0.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FF840
 * - func_150FFB6C
 * - func_150FFBDC
 * - func_150FFC3C
 * - func_150FFCC8
 * - func_150FFD84
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FF840.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FFB6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FFBDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FFC3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FFCC8.s")
void func_15081E0C(void *, s32, s32);

void func_150FFD2C(s32 arg0, void *arg1, s32 arg2) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg1 + 4);
    if (((temp_v0 == 0x9F) || (temp_v0 == 0xA0)) && !(*(s32 *)((u8 *)arg1 + 0x94) & 0x80)) {
        func_15081E0C(arg1, 4, 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FFD84.s")
