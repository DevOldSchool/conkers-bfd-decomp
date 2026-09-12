#include "types.h"

/*
 * Reviewed source unit: src/game/game_EDE60.c
 * Boundary evidence: docs/evidence/game_raw_owner_chain_resource_emitters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C0A48
 * - func_150C0AC0
 * - func_150C0C38
 * - func_150C1198
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150C0A48(s32 arg0);
void func_15169824(s32 arg0);

extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150C09B0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x20, arg0 + 0x24, arg0);
}
void func_150C09F0(s32 arg0) {
    func_150C0A48(arg0);
    func_15169804(arg0);
}
void func_150C0A1C(s32 arg0) {
    func_150C0A48(arg0);
    func_15169824(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EDE60/func_150C0A48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EDE60/func_150C0AC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EDE60/func_150C0C38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EDE60/func_150C1198.s")
