#include "types.h"

/*
 * Reviewed source unit: src/game/game_122B60.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F56B0
 * - func_150F5A54
 * - func_150F5C08
 * - func_150F5C98
 * - func_150F6178
 * - func_150F631C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150F631C(s32 arg0);
void func_1514933C(s32 arg0);
void func_15149368(s32 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F56B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F5A54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F5C08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F5C98.s")
extern void func_15149514(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150F6138(s32 arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F6178.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F631C.s")
void func_150F6368(s32 arg0) {
    func_150F631C(arg0);
    func_1514933C(arg0);
}
void func_150F6394(s32 arg0) {
    func_150F631C(arg0);
    func_15149368(arg0);
}
