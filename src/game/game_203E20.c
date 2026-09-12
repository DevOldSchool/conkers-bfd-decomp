#include "types.h"

/*
 * Reviewed source unit: src/game/game_203E20.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D69B4
 * - func_151D6BFC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_150D6730(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_800BE9F0;

void func_151D6970(s32 arg0, s32 arg1) {
    if ((D_800BE9F0 == 0x32) || (D_800BE9F0 == 0x33)) {
        func_150D6730(arg0, 0xFF, 1);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_203E20/func_151D69B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_203E20/func_151D6BFC.s")
