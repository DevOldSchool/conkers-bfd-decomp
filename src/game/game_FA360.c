#include "types.h"

/*
 * Reviewed source unit: src/game/game_FA360.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CCEB0
 * - func_150CD17C
 * - func_150CD59C
 * - func_150CD7F8
 * - func_150CDB6C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CCEB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CD17C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CD59C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CD7F8.s")
extern s32 D_80088870;
extern f32 D_800A07A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CDB6C CURRENT (110) */
void func_150CDB6C(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 0x100) && (D_80088870 != 0)) {
        *(f32 *)((u8 *)(D_80088870 + 0x28) + 4) = (f32) ((f32) arg0 * D_800A07A4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CDB6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CDB6C.s")
