#include "types.h"

/*
 * Reviewed source unit: src/game/game_1765E0.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15149130
 * - func_151491F4
 * - func_15149264
 * - func_15149394
 * - func_151493E4
 * - func_15149434
 * - func_15149490
 * - func_151494E0
 * - func_15149514
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_15149130.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_151491F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_15149264.s")
void func_15149318(s32 arg0) {
    func_151D5E30(arg0 + 0x14, arg0);
}
void func_15169804(s32);

void func_1514933C(s32 arg0) {
    func_15149318(arg0);
    func_15169804(arg0);
}
void func_15149318(s32 arg0);
void func_15169824(s32 arg0);

void func_15149368(s32 arg0) {
    func_15149318(arg0);
    func_15169824(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_15149394.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_151493E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_15149434.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_15149490.s")
void func_15169260(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_800A5770;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151494E0 CURRENT (400) */
void func_151494E0(s32 arg0, s32 arg1) {
    func_15169260(&D_800A5770, 2, arg0, arg1 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151494E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_151494E0.s")
void func_15169850(s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15149514 CURRENT (173) */
void func_15149514(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg1 = arg1 & 0xFF;
    func_15169850(arg0, arg1, arg2, arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15149514 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1765E0/func_15149514.s")
