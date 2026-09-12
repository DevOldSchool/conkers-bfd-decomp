#include "types.h"

/*
 * Reviewed source unit: src/game/game_204310.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D6E60
 * - func_151D7000
 * - func_151D710C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_204310/func_151D6E60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_204310/func_151D7000.s")
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_151D70CC(void *arg0, s32 arg1, u8 arg2) {
    s32 temp_a2;

    temp_a2 = *(s32 *)((u8 *)arg0 + 0x48);
    func_15169850(arg1, (s32) arg2, temp_a2, temp_a2 + 4, (s32) arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_204310/func_151D710C.s")
