#include "types.h"

/*
 * Reviewed source unit: src/game/game_12A460.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FDB0C CURRENT (580) */
void func_150FDB0C(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_t6;
    s32 temp_v1;
    u8 *temp_v0;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x2D) {
        temp_v0 = (void *)(arg0 + 0x110);
        temp_a2 = *(s32 *)((u8 *)arg0 + 0x110);
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == temp_a2) {
            *(s32 *)((u8 *)arg0 + 0x110) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a2) {
            *(s32 *)((u8 *)arg0 + 0x110) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    } else if ((temp_t6 == 0) && ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x110)) || (*(u8 *)((u8 *)(arg0 + 0x110) + 4) == (u8) *(s32 *)((u8 *)arg1 + 4)))) {
        *(s32 *)((u8 *)arg0 + 0x110) = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FDB0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12A460/func_150FDB0C.s")
