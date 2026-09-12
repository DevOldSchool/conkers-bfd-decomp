#include "types.h"

/*
 * Reviewed source unit: src/game/game_128790.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FB324
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_150FB240(void *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4);

s32 func_150FB2E0(void *arg0) {
    func_150FB240((u8 *) arg0 + 0x2E, *(s16 *)((u8 *) arg0 + 0x22), *(s16 *)((u8 *) arg0 + 0x70), *(s16 *)((u8 *) arg0 + 0x26), *(s16 *)((u8 *) arg0 + 0x28));
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_128790/func_150FB324.s")
