#include "types.h"

/*
 * Reviewed source unit: src/game/game_DAE10.c
 * Boundary evidence: docs/evidence/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AD960
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AD960 CURRENT (2130) */
s32 func_150AD960(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;

    var_a2 = arg2 - arg0;
    var_a3 = arg3 - arg1;
    if (var_a2 < 0) {
        var_a2 = -var_a2;
    }
    if (var_a3 < 0) {
        var_a3 = -var_a3;
    }
    if (var_a3 < var_a2) {
        var_t0 = var_a3 >> 1;
    } else {
        var_t0 = var_a2 >> 1;
    }
    return (var_a2 + var_a3) - var_t0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AD960 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAE10/func_150AD960.s")
