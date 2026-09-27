#include "types.h"

/*
 * Reviewed source unit: src/game/game_BC430.c
 * Boundary evidence: docs/evidence/game_remaining_single_function_units_up_to_256_bytes.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1508EF80
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_15047C00(f32 arg0);
f32 func_15047D60(f32 arg0);

extern f32 D_8009DC80;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508EF80 CURRENT (552) */
void func_1508EF80(f32 *arg0, f32 *arg1, f32 arg2, f32 *arg3) {
    f32 xDelta;
    f32 zDelta;
    f32 angle;
    f32 cosine;
    f32 xResult;
    f32 zResult;

    xDelta = arg0[0] - arg1[0];
    angle = arg2 * D_8009DC80;
    zDelta = arg0[2] - arg1[2];

    cosine = func_15047C00(angle);
    xResult = arg1[0] + ((func_15047D60(angle) * zDelta) + (cosine * xDelta));

    cosine = func_15047D60(angle);
    zResult = arg1[2] + ((func_15047C00(angle) * zDelta) + (-cosine * xDelta));
    arg3[0] = xResult;
    arg3[2] = zResult;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508EF80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC430/func_1508EF80.s")
