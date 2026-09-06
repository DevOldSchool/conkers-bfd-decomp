#include "types.h"

/*
 * Reviewed source unit: src/game/game_F8590.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CB0E0
 * - func_150CB1F4
 * - func_150CB800
 * - func_150CBA30
 * - func_150CBABC
 * - func_150CBCE0
 * - func_150CBE88
 * - func_150CBF5C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CB0E0.s")
s32 func_150CB1E0(s32 arg0, s32 arg1) {
    return 0xB;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CB1F4.s")
s32 func_150CB7CC(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x28)) {
            *(u8 *)((u8 *)arg0 + 0x28) = (u8) temp_v1;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CB800.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CBA30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CBABC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CBCE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CBE88.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CBF5C CURRENT (30) */
void func_150CBF5C(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x1C) = 0x20;
    *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CBF5C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CBF5C.s")
