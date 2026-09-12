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
#pragma GLOBAL_ASM("asm/nonmatchings/game_124260/func_150F7310.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_124260/func_150F739C.s")
void func_150F740C(s32 arg0) {
    func_150F739C(arg0);
    func_1514933C(arg0);
}
void func_150F7438(s32 arg0) {
    func_150F739C(arg0);
    func_15149368(arg0);
}
