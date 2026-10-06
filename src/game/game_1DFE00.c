#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DFE00.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B2974
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151B2950(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x178);
    if (temp_v0 != 0) {
        *(s32 *)(temp_v0 + (*(u8 *)(arg0 + 0x17C) * 4) + 0x38) = 0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DFE00/func_151B2974.s")
void func_151B2EC4(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
void func_151B2F04(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_a2;
    s32 temp_v1;
    s32 replacement;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x28);
    if (arg2 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_a2 = *(s32 *)temp_v0;
        if (temp_v1 == temp_a2) {
            *(s32 *)temp_v0 = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
        } else if ((replacement = *(s32 *)((u8 *)arg1 + 4)) == temp_a2) {
            *(s32 *)temp_v0 = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
        replacement = *(s32 *)(arg1 + 4);
        temp_v1 = *(s32 *)arg1;
        temp_a2 = *(s32 *)((u8 *)temp_v0 + 8);
        if (temp_v1 == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 8) = replacement;
            *(u8 *)((u8 *)temp_v0 + 0xC) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (replacement == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 8) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 0xC) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
void func_151B47D8(s32 arg0, s32 arg1, s32 arg2, u8 arg3);

void func_151B2FA0(s32 arg0, s32 arg1, u8 arg2) {
    func_151B47D8(arg0, arg0 + 0x150, arg1, arg2);
}
