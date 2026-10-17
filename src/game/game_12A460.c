#include "types.h"

/*
 * Reviewed source unit: src/game/game_12A460.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FCFD4
 * - func_150FD514
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150FCFB0(s32 arg0) {
    func_15103828();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12A460/func_150FCFD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12A460/func_150FD514.s")
void func_150FDB0C(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;

    temp_v0 = arg0 + 0x110;
    if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)temp_v0) {
            u8 *dst = temp_v0;

            *(s32 *)dst = *(s32 *)arg1;
            *(u8 *)(dst + 4) = *(u8 *)(arg1 + 8);
        }
    } else if (arg2 == 0) {
        s32 temp_v1 = *(s32 *)arg1;

        if ((temp_v1 == *(s32 *)temp_v0) || (temp_v0[4] == arg1[4])) {
            *(s32 *)temp_v0 = 0;
        }
    }
}
