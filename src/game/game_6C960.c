#include "types.h"

/*
 * Reviewed source unit: src/game/game_6C960.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503F4B0
 * - func_1503F5B8
 * - func_1503F62C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_6C960/func_1503F4B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6C960/func_1503F5B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6C960/func_1503F62C.s")
extern void func_10004074(s32 arg0);
extern void func_100043B4();

void func_1503F7B8(void *arg0) {
    func_100043B4(*(s32 *)((u8 *)arg0 + 0x3E8), 4);
    func_100043B4(*(s32 *)((u8 *)arg0 + 0x3EC), 4);
    func_10004074((s32) arg0);
}
