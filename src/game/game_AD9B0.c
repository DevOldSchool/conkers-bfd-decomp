#include "types.h"

/*
 * Reviewed source unit: src/game/game_AD9B0.c
 * Boundary evidence: docs/evidence/game_raw_periodic_actor_resource_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15080500
 * - func_15080620
 * - func_150806A8
 * - func_15080784
 * - func_15080828
 * - func_15080BE8
 * - func_15080C64
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_AD9B0/func_15080500.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AD9B0/func_15080620.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AD9B0/func_150806A8.s")
void func_15080718(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg2 = 1 << (arg0 & 7);
    *arg1 = arg0 >> 3;
}
extern u8 D_800BE580[];

s32 func_15080738(s32 arg0) {
    s32 sp1C;
    s32 sp18;

    func_15080718(arg0, &sp1C, &sp18);
    if (D_800BE580[sp1C] & sp18) {
        return 1;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_AD9B0/func_15080784.s")
void func_15080784(void);

void func_150807F4(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == 0x20) {
        func_15080784();
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_AD9B0/func_15080828.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AD9B0/func_15080BE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AD9B0/func_15080C64.s")
extern u8 D_800D1941;

s32 func_15080CF4(void) {
    if (D_800D1941 == 0) {
        return 1;
    }
    return 0;
}
