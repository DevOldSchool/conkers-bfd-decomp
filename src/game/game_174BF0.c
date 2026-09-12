#include "types.h"

/*
 * Reviewed source unit: src/game/game_174BF0.c
 * Boundary evidence: docs/evidence/game_raw_effect_dispatch_engine.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15147740
 * - func_1514795C
 * - func_151479E0
 * - func_15147A30
 * - func_15147A80
 * - func_15147C4C
 * - func_15147D1C
 * - func_15147D64
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147740.s")
void func_151478D0(s32 arg0) {
    func_151D5E30(arg0 + 0x84, arg0);
}
void func_1514795C(s32 arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);

void func_151478F4(s32 arg0) {
    func_151478D0(arg0);
    func_1514795C(arg0);
    func_15169804(arg0);
}
void func_15147928(s32 arg0) {
    func_151478D0(arg0);
    func_1514795C(arg0);
    func_15169824(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_1514795C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_151479E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147A30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147A80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147C4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147D1C.s")
void func_15169260(void *, s32, s32, s32);
extern u8 D_800A5760;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15147D64 CURRENT (260) */
void func_15147D64(s32 arg0, s32 arg1) {
    func_15169260(&D_800A5760, 2, arg0, (u8) arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15147D64 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_174BF0/func_15147D64.s")
