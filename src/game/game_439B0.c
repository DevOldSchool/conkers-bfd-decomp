#include "types.h"

/*
 * Reviewed source unit: src/game/game_439B0.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15016500
 * - func_15016588
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_439B0/func_15016500.s")

void func_100226F0(void *arg0, s32 arg1);
s32 func_1502B020(s32 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4);

extern u8 D_800BE580[8];
extern u8 D_800BEAAB;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15016588 CURRENT (431) */
void func_15016588(void) {
    s32 sp44;
    s32 sp40;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    func_100226F0(D_800BE580, 8);
    var_s1 = -1;
    var_s0 = 0;
    var_s2 = sp44;

    do {
        if (!(var_s0 & 7)) {
            var_s2 = 1;
            var_s1++;
        } else {
            var_s2 *= 2;
        }

        func_1502B020(&sp40, 3, 0x1A, D_800BEAAB, var_s0);
        var_s0++;
        if (sp40 != 0) {
            D_800BE580[var_s1] |= var_s2;
        }
    } while (var_s0 != 0x43);

    sp44 = var_s2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15016588 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_439B0/func_15016588.s")
