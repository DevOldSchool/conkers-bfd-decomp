#include "types.h"

/*
 * Reviewed source unit: src/game/game_1F3780.c
 * Boundary evidence: docs/evidence/game_raw_model_anchor_owner_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C62D0
 * - func_151C69CC
 * - func_151C6A28
 * - func_151C6D70
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C62D0.s")
void func_151C69CC();

void func_151C6974(s32 arg0, s32 arg1, s32 arg2) {
    func_151C69CC(arg0, arg2, 0, arg2);
}
void func_151C69A0(s32 arg0, s32 arg1, s32 arg2) {
    func_151C69CC(arg0, arg2, 1, arg2);
}
void func_15143134(f32 *, f32 *, s32);
extern s32 D_800AAB00[];
extern f32 D_800AAB08[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C69CC CURRENT (380) */
void func_151C69CC(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a3;

    temp_a3 = arg2 & 0xFF;
    func_15143134((f32 *)((u8 *)D_800AAB08 + (temp_a3 * 0xC)), (f32 *)arg1,
                   D_800AAB00[temp_a3] + *(s32 *)((u8 *)arg0 + 0x1D4));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C69CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C69CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C6A28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C6D70.s")
