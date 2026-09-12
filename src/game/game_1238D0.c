#include "types.h"

/*
 * Reviewed source unit: src/game/game_1238D0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F6484
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150F6400(s32 arg0);
void func_1513CA6C(s32 arg0);
void func_1513CAA0(s32 arg0);

void func_150F6420(s32 arg0) {
    func_150F6400(arg0);
    func_1513CA6C(arg0);
}
void func_150F644C(s32 arg0) {
    func_150F6400(arg0);
    func_1513CAA0(arg0);
}
void func_150F6478(s32 arg0) {

}
/* Call context: func_150F6478: unique active project prototype */
/* Call context: func_151411A4: unique active project prototype */
void func_151411A4(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F6484 CURRENT (500) */
void func_150F6484(s32 arg0) {
    func_150F6478(arg0);
    func_151411A4();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F6484 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1238D0/func_150F6484.s")
