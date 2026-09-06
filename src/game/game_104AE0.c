#include "types.h"

/*
 * Reviewed source unit: src/game/game_104AE0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D765C
 * - func_150D7790
 * - func_150D7928
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE9E4;
extern u16 D_800D9910;

void func_150D7630(s32 arg0) {
    if (arg0 == 0) {
        D_800D9910 += D_800BE9E4 << 6;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_104AE0/func_150D765C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_104AE0/func_150D7790.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_104AE0/func_150D7928.s")
