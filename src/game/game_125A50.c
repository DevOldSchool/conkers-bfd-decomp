#include "types.h"

/*
 * Reviewed source unit: src/game/game_125A50.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F85A0
 * - func_150F887C
 * - func_150F892C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_125A50/func_150F85A0.s")
void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_150F884C(s32 arg0, s32 arg1) {
    s32 sp18[2];

    sp18[0] = arg1;
    func_151494E0(&sp18[0], 0x3F, arg1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_125A50/func_150F887C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_125A50/func_150F892C.s")
