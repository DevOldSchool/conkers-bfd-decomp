#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A0E60.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151739B0
 * - func_15173C90
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0E60/func_151739B0.s")
void func_151739B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15173C60(s32 arg0, s32 arg1) {
    func_151739B0(0, 0, arg0, arg1, 0);
}
/* Call context: func_151149AC: unique active project prototype */
/* Call context: func_151739B0: unique active project prototype */
s32 func_151149AC(u8);
extern s32 D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15173C90 CURRENT (645) */
void func_15173C90(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = func_151149AC(arg2 & 0xFF);
    if (temp_v0 != 0) {
        func_151739B0(*(u16 *)((u8 *)temp_v0 + 0x54) & 0xFFFF7FFF, 1, arg0, arg1, (s32) (temp_v0 - D_800DBEF4) / 160);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15173C90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0E60/func_15173C90.s")
