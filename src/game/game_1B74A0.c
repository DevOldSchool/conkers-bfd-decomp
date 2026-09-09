#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B74A0.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15189FF0
 * - func_1518A094
 * - func_1518A214
 * - func_1518A2E8
 * - func_1518A324
 * - func_1518A360
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B74A0/func_15189FF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B74A0/func_1518A094.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B74A0/func_1518A214.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B74A0/func_1518A2E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B74A0/func_1518A324.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518A360 CURRENT (205) */
void func_1518A360(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x170);
    if ((arg2 & 0xFF) == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_a2 = *(s32 *)((u8 *)temp_v0 + 0x18);
        if (temp_v1 == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 0x18) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 0x1D) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 0x18) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 0x1D) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518A360 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B74A0/func_1518A360.s")
