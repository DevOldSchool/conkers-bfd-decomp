#include "types.h"

/*
 * Reviewed source unit: src/game/game_12A460.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FCFD4
 * - func_150FD514
 * - func_150FDB0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150FCFB0(s32 arg0) {
    func_15103828();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12A460/func_150FCFD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12A460/func_150FD514.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FDB0C CURRENT (30) */
void func_150FDB0C(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    s32 temp_v1;

    temp_v0 = arg0 + 0x110;
    if (arg2 == 0x2D) {
        s32 temp_a2;

        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_a2 = *(s32 *)temp_v0;
        if (temp_v1 == temp_a2) {
            *(s32 *)temp_v0 = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a2) {
            *(s32 *)temp_v0 = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    } else if (arg2 == 0) {
        temp_v1 = *(s32 *)arg1;
        if ((temp_v1 == *(s32 *)temp_v0) || (temp_v0[4] == arg1[4])) {
            *(s32 *)temp_v0 = 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FDB0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12A460/func_150FDB0C.s")
