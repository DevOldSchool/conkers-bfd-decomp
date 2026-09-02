#include "types.h"

/*
 * Reviewed source unit: src/game/game_3F820.c
 * Boundary evidence: docs/evidence/game_next_compact_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15012370
 * - func_150124A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1518AADC(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_80088750;

#pragma GLOBAL_ASM("asm/nonmatchings/game_3F820/func_15012370.s")
void func_15012470(void) {
    D_80088750 = func_1518AADC(4, 0x12C, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_3F820/func_150124A0.s")
