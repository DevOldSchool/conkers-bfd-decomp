#include "types.h"

/*
 * Reviewed source unit: src/game/game_1ED080.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BFBFC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151BFBD0(s32 arg0) {
    func_151BFB2C(arg0);
    func_15149368(arg0);
}
extern void func_1516972C(s32 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BFBFC CURRENT (295) */
void func_151BFBFC(s32 arg0, s32 arg1, s32 arg2) {
    arg2 = arg2 & 0xFF;
    if (arg2 == 0x57) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BFBFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED080/func_151BFBFC.s")
