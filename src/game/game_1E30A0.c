#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E30A0.c
 * Boundary evidence: docs/evidence/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B5BF0
 * - func_151B5E94
 * - func_151B5FCC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E30A0/func_151B5BF0.s")
void func_151B5E8C(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E30A0/func_151B5E94.s")
/* Call context: func_100111C8: unique active project prototype */
void func_100111C8(s32, u16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B5FCC CURRENT (125) */
void func_151B5FCC(void *arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x88);
    if (temp_v0 != 0) {
        func_100111C8(temp_v0 & 0xFFFF, (u16) arg0);
        *(s32 *)((u8 *)arg0 + 0x88) = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B5FCC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E30A0/func_151B5FCC.s")
