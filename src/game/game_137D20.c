#include "types.h"

/*
 * Reviewed source unit: src/game/game_137D20.c
 * Boundary evidence: docs/evidence/game_raw_callback_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510A870
 * - func_1510A8CC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510A870 CURRENT (10) */
void func_1510A870(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_a2;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x28);
    if (arg2 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_a2 = *(s32 *)temp_v0;
        if (temp_v1 == temp_a2) {
            *(s32 *)temp_v0 = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (temp_a2 == *(s32 *)((u8 *)arg1 + 4)) {
            *(s32 *)temp_v0 = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510A870 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_137D20/func_1510A870.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510A8CC CURRENT (110) */
void func_1510A8CC(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_a2;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x28);
    if (arg2 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_a2 = *(s32 *)temp_v0;
        if (temp_v1 == temp_a2) {
            *(s32 *)temp_v0 = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (temp_a2 == *(s32 *)((u8 *)arg1 + 4)) {
            *(s32 *)temp_v0 = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510A8CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_137D20/func_1510A8CC.s")
