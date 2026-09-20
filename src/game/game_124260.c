#include "types.h"

/*
 * Reviewed source unit: src/game/game_124260.c
 * Boundary evidence: docs/evidence/game_raw_secondary_stream_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F6DE4
 * - func_150F706C
 * - func_150F7310
 * - func_150F739C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150F739C(s32 arg0);
void func_1516972C(void *arg0);
void func_15149368(s32 arg0);

void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_150F6DB0(void *arg0) {
    struct {
        void *sp18;
        volatile u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151494E0((s32 *)&sp, 0x3E, (s32)arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_124260/func_150F6DE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_124260/func_150F706C.s")
void func_15149514(s32, u8, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F7310 CURRENT (260) */
void func_150F7310(void *arg0, void *arg1, u8 arg2) {
    u8 *temp_a2;

    temp_a2 = (u8 *)arg0 + 0x28;
    if (arg2 == 0x3E) {
        if ((*(s32 *)temp_a2 == *(s32 *)arg1) || (*(u8 *)((u8 *)temp_a2 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    } else {
        func_15149514((s32) arg1, arg2, (s32) temp_a2, (s32) ((u8 *)temp_a2 + 4), (s32) arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F7310 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_124260/func_150F7310.s")
/* Call context: func_1514EDF0: unique active project prototype */
void func_1514EDF0(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F739C CURRENT (1184) */
void func_150F739C(s32 arg0) {
    s32 temp_t8;
    s32 var_s0;
    void *temp_a0;

    var_s0 = 0;
    do {
        temp_a0 = *(void **)((u8 *)(arg0 + 0x28 + (var_s0 * 4)) + 8);
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
        }
        temp_t8 = (var_s0 + 1) & 0xFF;
        var_s0 = temp_t8;
    } while (temp_t8 < 2);
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0x28));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F739C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_124260/func_150F739C.s")
void func_150F740C(s32 arg0) {
    func_150F739C(arg0);
    func_1514933C(arg0);
}
void func_150F7438(s32 arg0) {
    func_150F739C(arg0);
    func_15149368(arg0);
}
