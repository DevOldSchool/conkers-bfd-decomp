#include "types.h"

/*
 * Reviewed source unit: src/game/game_1F1F60.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C4AB0
 * - func_151C4B0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C4AB0 CURRENT (215) */
void func_151C4AB0(s32 arg0, void *arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_v1;
    void *temp_v0;

    temp_v0 = arg0 + 0x110;
    if ((arg2 & 0xFF) == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_a2 = *(s32 *)((u8 *)temp_v0 + 0x90);
        if (temp_v1 == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 0x90) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 0x94) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 0x90) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 0x94) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C4AB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F1F60/func_151C4AB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F1F60/func_151C4B0C.s")
