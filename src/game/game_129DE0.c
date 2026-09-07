#include "types.h"

/*
 * Reviewed source unit: src/game/game_129DE0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FC974
 * - func_150FC9A4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150FC930(void *arg0, s32 arg1, s32 arg2) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if ((temp_v0 == 0x12) || (temp_v0 == 0x23) || (temp_v0 == 0x73) || (temp_v0 == 0x8A)) {
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_129DE0/func_150FC974.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_129DE0/func_150FC9A4.s")
