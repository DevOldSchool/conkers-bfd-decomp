#include "types.h"

/*
 * Reviewed source unit: src/game/game_122A40.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F5590
 * - func_150F55C8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_122A40/func_150F5590.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F55C8 CURRENT (395) */
void func_150F55C8(void *arg0) {
    s16 temp_t2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_t1;
    s32 temp_v0;
    s32 temp_v1;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x1C);
    temp_a2 = *(s32 *)((u8 *)arg0 + 0x18);
    temp_t2 = *(s16 *)((u8 *)arg0 + 0x24);
    temp_v0 = temp_v1 & 0xFFFF;
    temp_a1 = temp_a2 >> 0x10;
    temp_t1 = temp_v0 - temp_a1;
    if (temp_t1 < temp_t2) {
        *(s8 *)((u8 *)arg0 + 0x45) = (s8) ((s32) ((temp_v0 - temp_t2) * 0xFF) / temp_a1);
        return;
    }
    if ((temp_t1 - (temp_a2 & 0xFFFF)) < temp_t2) {
        *(s8 *)((u8 *)arg0 + 0x45) = 0xFF;
        return;
    }
    *(s8 *)((u8 *)arg0 + 0x45) = (s8) ((s32) (temp_t2 * 0xFF) / (s32) (temp_v1 >> 0x10));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F55C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_122A40/func_150F55C8.s")
void func_150F568C(s32 arg0) {
    func_15179008(0);
}
