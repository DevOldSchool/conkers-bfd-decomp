#include "types.h"

/*
 * Reviewed source unit: src/game/game_138390.c
 * Boundary evidence: docs/evidence/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510AEE0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510AEE0 CURRENT (7674) */
s32 func_1510AEE0(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   f32 arg5, f32 arg6, f32 arg7, f32 *arg8, f32 *arg9) {
    f32 sp0;
    f32 horizontal;
    f32 depth;

    depth = -(arg0[14] + ((arg0[2] * arg1) + (arg0[6] * arg2) +
                            (arg0[10] * arg3)));
    if (depth < arg4) {
        return 1;
    }
    if (arg5 < depth) {
        return 1;
    }
    horizontal = __builtin_fabsf(arg0[12] + ((arg0[0] * arg1) + (arg0[4] * arg2) +
                                   (arg0[8] * arg3))) * arg6;
    if (depth < horizontal) {
        return 1;
    }
    sp0 = __builtin_fabsf(arg0[13] + ((arg0[1] * arg1) + (arg0[5] * arg2) +
                            (arg0[9] * arg3))) * arg7;
    if (depth < sp0) {
        return 1;
    }
    if (arg8 != 0) {
        *arg8 = 1.0f - (horizontal / depth);
    }
    if (arg9 != 0) {
        *arg9 = 1.0f - (sp0 / depth);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510AEE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_138390/func_1510AEE0.s")
