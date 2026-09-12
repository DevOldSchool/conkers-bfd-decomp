#include "types.h"

/*
 * Reviewed source unit: src/game/game_F4B20.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C7670
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_F4B20/func_150C7670.s")
void func_10022EC0(void *arg0, void *arg1, s32 arg2);
extern u8 D_80089470;

s32 func_150C773C(void *arg0, s32 arg1) {
    func_10022EC0(arg0, &D_80089470, 0x40);
    return 1;
}
