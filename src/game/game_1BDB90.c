#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BDB90.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151906E0
 * - func_1519072C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151906E0 CURRENT (205) */
void func_151906E0(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x90);
    if ((arg2 & 0xFF) == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_a2 = *(s32 *)((u8 *)temp_v0 + 8);
        if (temp_v1 == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 8) = (s32) *(s32 *)((u8 *)arg1 + 4);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 8) = temp_v1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151906E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDB90/func_151906E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDB90/func_1519072C.s")
