#include "types.h"

/*
 * Reviewed source unit: src/game/game_1114C0.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E4010
 * - func_150E4174
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1114C0/func_150E4010.s")
void func_151C3B0C(void *, f32, f32, f32, f32, s32, s32, s32);
extern f32 D_800A1054;

void func_150E411C(void *arg0) {
    func_151C3B0C(arg0, 0.35200003f, 0.70100003f, 0.56600004f, D_800A1054, 0xFF, 0xFF, 0xFF);
}
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E4174 CURRENT (35) */
s32 func_150E4174(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + (*(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + (*(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E4174 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1114C0/func_150E4174.s")
