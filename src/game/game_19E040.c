#include "types.h"

/*
 * Reviewed source unit: src/game/game_19E040.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15170B90
 * - func_15170EC4
 * - func_15170F4C
 * - func_15171200
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_19E040/func_15170B90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19E040/func_15170EC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19E040/func_15170F4C.s")
void func_150C3D5C(void);
void func_15060F28(u8 *, s32);

void func_151711C4(u8 *arg0) {
    if (arg0[4] == 0x33) {
        func_150C3D5C();
    }
    func_15060F28(arg0, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_19E040/func_15171200.s")
