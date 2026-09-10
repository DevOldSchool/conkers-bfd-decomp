#include "types.h"

/*
 * Reviewed source unit: src/game/game_6E770.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150412C0
 * - func_150413FC
 * - func_15041480
 * - func_15041508
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_150412C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_150413FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_15041480.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15041508 CURRENT (2290) */
void *func_15041508(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v1;
    u8 *temp_a0;


    *(s32 *)((u8 *)arg0 + 4) = (s32) ((((arg1 * 4) & 0xFFF) << 0xC) | ((arg2 * 4) & 0xFFF));
    *(s32 *)((u8 *)arg0 + 0) = (s32) (((((arg1 + 8) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((arg2 + 0xC) * 4) & 0xFFF));
    {
    u8 *temp_a0_2;
    temp_a0_2 = (void *)(arg0 + 8);
    *(s32 *)((u8 *)arg0 + 8) = 0xE1000000;
    temp_a0 = (void *)(temp_a0_2 + 8);
    temp_v1 = arg3 % 8;
    *(s32 *)((u8 *)temp_a0_2 + 4) = (s32) ((((temp_v1 * 8) << 5) << 0x10) | ((((s32) (arg3 - temp_v1) / 8) * 0x180) & 0xFFFF));
    *(s32 *)((u8 *)temp_a0_2 + 8) = 0xF1000000;
    }
    *(s32 *)((u8 *)temp_a0 + 4) = 0x04000400;
    return temp_a0 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15041508 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_15041508.s")
