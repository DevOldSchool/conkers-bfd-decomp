#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DFE00.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B2950
 * - func_151B2974
 * - func_151B2F04
 * - func_151B2FA0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DFE00/func_151B2950.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DFE00/func_151B2974.s")
void func_151B2EC4(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B2F04 CURRENT (780) */
void func_151B2F04(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x28);
    if ((arg2 & 0xFF) == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_a2 = *(s32 *)((u8 *)arg0 + 0x28);
        if (temp_v1 == temp_a2) {
            *(s32 *)((u8 *)arg0 + 0x28) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
        } else if (*(s32 *)((u8 *)arg1 + 4) == temp_a2) {
            *(s32 *)((u8 *)arg0 + 0x28) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
        temp_a2_2 = *(s32 *)((u8 *)temp_v0 + 8);
        if (*(s32 *)((u8 *)arg1 + 0) == temp_a2_2) {
            *(s32 *)((u8 *)temp_v0 + 8) = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 0xC) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a2_2) {
            *(s32 *)((u8 *)temp_v0 + 8) = *(s32 *)((u8 *)arg1 + 0);
            *(u8 *)((u8 *)temp_v0 + 0xC) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B2F04 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DFE00/func_151B2F04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DFE00/func_151B2FA0.s")
