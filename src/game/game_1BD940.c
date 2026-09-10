#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BD940.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15190490
 * - func_151904BC
 * - func_15190518
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1BD940/func_15190490.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BD940/func_151904BC.s")
/* Call context: func_1516944C: unique active project prototype */
void func_1516944C(s32, s8 *, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15190518 CURRENT (613) */
void func_15190518(void *arg0) {
    u8 sp1C;
    void *sp18;

    sp18 = arg0;
    sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_1516944C(0x3E, (s8 *) &sp18, 0x2AU, (u8) arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15190518 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BD940/func_15190518.s")
