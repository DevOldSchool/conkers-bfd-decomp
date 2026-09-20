#include "types.h"

/*
 * Reviewed source unit: src/game/game_11CC60.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EF7B0
 * - func_150EF860
 * - func_150EF910
 * - func_150EFA4C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_1516972C(void *arg0);
extern void func_1513CA6C(void *arg0);
extern void func_1516979C(void *arg0);
extern void func_1513CAA0(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EF7B0 CURRENT (717) */
void func_150EF7B0(void *arg0) {
    void **var_s1;
    s32 var_s0;

    var_s0 = 0;
    var_s1 = (void **)((u8 *)arg0 + 0x110);
    do {
        if (var_s1[7] != 0) {
            func_1516972C(var_s1[7]);
        }
        var_s0 += 4;
        var_s1 = (void **)((u8 *)var_s1 + 4);
    } while (var_s0 != 8);
    if (var_s1[1] != 0) {
        func_1516972C(var_s1[1]);
    }
    if (var_s1[2] != 0) {
        func_1516972C(var_s1[2]);
    }
    if (var_s1[3] != 0) {
        func_1516972C(var_s1[3]);
    }
    func_1513CA6C(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EF7B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11CC60/func_150EF7B0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EF860 CURRENT (717) */
void func_150EF860(void *arg0) {
    void **var_s1;
    s32 var_s0;

    var_s0 = 0;
    var_s1 = (void **)((u8 *)arg0 + 0x110);
    do {
        if (var_s1[7] != 0) {
            func_1516979C(var_s1[7]);
        }
        var_s0 += 4;
        var_s1 = (void **)((u8 *)var_s1 + 4);
    } while (var_s0 != 8);
    if (var_s1[1] != 0) {
        func_1516979C(var_s1[1]);
    }
    if (var_s1[2] != 0) {
        func_1516979C(var_s1[2]);
    }
    if (var_s1[3] != 0) {
        func_1516979C(var_s1[3]);
    }
    func_1513CAA0(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EF860 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11CC60/func_150EF860.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11CC60/func_150EF910.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11CC60/func_150EFA4C.s")
