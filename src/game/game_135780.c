#include "types.h"

/*
 * Reviewed source unit: src/game/game_135780.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151082D0
 * - func_15108658
 * - func_151087FC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_135780/func_151082D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_135780/func_15108658.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151087FC CURRENT (759) */
void func_151087FC(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_t6;
    void *temp_v0;
    void *temp_v0_2;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x2B) {
        temp_v0 = arg0 + 0x28;
        *(u8 *)((u8 *)temp_v0 + 8) = (u8) (*(u8 *)((u8 *)temp_v0 + 8) | 1);
        return;
    }
    temp_v0_2 = arg0 + 0x28;
    if (temp_t6 == 0x2C) {
        *(u8 *)((u8 *)temp_v0_2 + 8) = (u8) (*(u8 *)((u8 *)temp_v0_2 + 8) & 0xFFFE);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151087FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135780/func_151087FC.s")
