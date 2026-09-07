#include "types.h"

/*
 * Reviewed source unit: src/game/game_1EBFD0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BEB20
 * - func_151BECB8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1EBFD0/func_151BEB20.s")
s32 func_151BEC94(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 *arg4) {
    *arg4 = 1;
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EBFD0/func_151BECB8.s")
s32 func_151BEE94(void *arg0) {
    if (*(u8 *)((u8 *)arg0 + 0x127) == 0xFF) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0) == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 4) == 0xFF) {
        return 0;
    }
    return 1;
}
