#include "types.h"

/*
 * Reviewed source unit: src/game/game_1F1F60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C4B0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151C4AB0(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x110);
    if (arg2 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == *(s32 *)((u8 *)temp_v0 + 0x90)) {
            *(s32 *)((u8 *)temp_v0 + 0x90) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 0x94) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)((u8 *)temp_v0 + 0x90)) {
            *(s32 *)((u8 *)temp_v0 + 0x90) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 0x94) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F1F60/func_151C4B0C.s")
