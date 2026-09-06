#include "types.h"

/*
 * Reviewed source unit: src/game/game_10EF60.c
 * Boundary evidence: docs/evidence/game_raw_path_owner_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E1AB0
 * - func_150E1D14
 * - func_150E28DC
 * - func_150E2DB4
 * - func_150E2EA4
 * - func_150E2FC0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E1AB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E1D14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E28DC.s")
s32 func_150E2DA4(s32 arg0, s32 arg1) {
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E2DB4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E2EA4.s")
void func_150E2F90(s32 arg0, s32 arg1, s16 arg2) {
    func_150E2DA4(arg0, (s32) arg2);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E2FC0 CURRENT (205) */
void func_150E2FC0(void *arg0, void *arg1, s32 arg2) {
    s32 temp_v0;
    s32 temp_v1;

    if ((arg2 & 0xFF) == 0x2D) {
        temp_v0 = *(s32 *)((u8 *)arg1 + 0);
        temp_v1 = *(s32 *)((u8 *)arg0 + 0xDC);
        if (temp_v0 == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0xDC) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)arg0 + 0xDA) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0xDC) = temp_v0;
            *(u8 *)((u8 *)arg0 + 0xDA) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E2FC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E2FC0.s")
