#include "types.h"

/*
 * Reviewed source unit: src/game/game_205C90.c
 * Boundary evidence: docs/evidence/game_raw_slot_view_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D87E0
 * - func_151D8868
 * - func_151D8A24
 * - func_151D8B24
 * - func_151D8C00
 * - func_151D8D5C
 * - func_151D8DB4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D87E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8868.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8A24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8B24.s")
void func_151D8B24(s32 arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);

void func_151D8B88(s32 arg0) {
    func_151D8B24(arg0);
    func_15169804(arg0);
}
void func_151D8BB4(s32 arg0) {
    func_151D8B24(arg0);
    func_15169824(arg0);
}
void func_151D8BE0(s32 arg0) {
    func_151D8C00(arg0, arg0 + 0x18);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8C00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8D5C.s")
void func_15169260(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_800AB300;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D8DB4 CURRENT (400) */
void func_151D8DB4(s32 arg0, s32 arg1) {
    func_15169260(&D_800AB300, 1, arg0, arg1 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D8DB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8DB4.s")
void func_151D8DB4(s32 arg0, s32 arg1);
extern s8 D_800E0A00;

void func_151D8DE8(void) {
    D_800E0A00 = 1;
    func_151D8DB4(0, 0x58);
}
