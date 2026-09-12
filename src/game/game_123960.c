#include "types.h"

/*
 * Reviewed source unit: src/game/game_123960.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F64DC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150F64B0(s32 arg0) {
    func_150F6478(arg0);
    func_151411C4(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_123960/func_150F64DC.s")
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150F6850(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
