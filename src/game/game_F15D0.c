#include "types.h"

/*
 * Reviewed source unit: src/game/game_F15D0.c
 * Boundary evidence: docs/evidence/game_raw_owner_chain_resource_emitters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C4120
 * - func_150C44A4
 * - func_150C4B60
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150C4AD8(void *arg0);
void func_1516972C(void *arg0);
void func_15149368(s32 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/game_F15D0/func_150C4120.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F15D0/func_150C44A4.s")
void func_150C4AD8(void *arg0) {
    volatile void **field_34 = (volatile void **)((u8 *)arg0 + 0x34);

    if (*field_34 != 0) {
        func_1516972C((void *)*field_34);
    }
}
void func_150C4B08(s32 arg0) {
    func_150C4AD8((void *)arg0);
    func_1514933C(arg0);
}
void func_150C4B34(s32 arg0) {
    func_150C4AD8((void *)arg0);
    func_15149368(arg0);
}
/* Call context: func_15149514: unique active project prototype */
void func_15149514(s32, u8, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C4B60 CURRENT (415) */
void func_150C4B60(u8 *volatile arg0, volatile s32 arg1, volatile u8 arg2) {
    u8 *temp_a2;
    u8 *owner;
    s32 selector;

    selector = arg2;
    temp_a2 = arg0;
    if (selector == 0x55) {
        temp_a2 += 0x28;
        temp_a2[0x16] &= 0xFFFD;
        return;
    }
    owner = arg0;
    if (selector == 0x56) {
        temp_a2 = arg0 + 0x28;
        temp_a2[0x16] |= 2;
        return;
    }
    temp_a2 = owner + 0x28;
    func_15149514(arg1, arg2, (s32)temp_a2, (s32)(temp_a2 + 4), (s32)owner);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C4B60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F15D0/func_150C4B60.s")
