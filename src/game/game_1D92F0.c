#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D92F0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151ABE40
 * - func_151AC078
 * - func_151AC3CC
 * - func_151AC408
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151ABE40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AC078.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AC3CC CURRENT (130) */
s32 func_151AC3CC(void *arg0) {
    s32 temp_t6;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 8;
    {
        s32 var_v1 = temp_t6;
    if (temp_t6 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < (s32) *(u8 *)((u8 *)temp_v0 + 0x1B)) {
        *(u8 *)((u8 *)temp_v0 + 0x1B) = (u8) var_v1;
    }
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AC3CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AC3CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AC408.s")
