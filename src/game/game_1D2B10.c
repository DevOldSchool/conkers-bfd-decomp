#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D2B10.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A5660
 * - func_151A5CAC
 * - func_151A5CEC
 * - func_151A5D2C
 * - func_151A5D58
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A5660.s")
/* Call context: func_1514933C: unique active project prototype */
void func_1514933C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A5CAC CURRENT (435) */
void func_151A5CAC(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 0x6C) != 0) {
        func_151A5D2C((s32) *(u16 *)((u8 *)arg0 + 0x6C), (u16) arg0);
    }
    func_1514933C((s32) arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A5CAC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A5CAC.s")
extern void func_151A5D2C(s32 arg0, u16 arg1);
extern void func_15149368(void *arg0, void *arg1);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A5CEC CURRENT (545) */
void func_151A5CEC(void *arg0) {
    void *temp_a1;
    u16 temp_v0;

    temp_a1 = arg0;
    temp_v0 = *(u16 *)((u8 *)temp_a1 + 0x6C);
    if (temp_v0 != 0) {
        func_151A5D2C(temp_v0, (u16) temp_a1);
    }
    func_15149368(temp_a1, temp_a1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A5CEC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A5CEC.s")
/* Call context: func_100111C8: unique active project prototype */
void func_100111C8(s32, u16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A5D2C CURRENT (419) */
void func_151A5D2C(s32 arg0, u16 arg1) {
    func_100111C8(arg0 & 0xFFFF, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A5D2C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A5D2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A5D58.s")
