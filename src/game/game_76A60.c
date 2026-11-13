#include "types.h"

/*
 * Reviewed source unit: src/game/game_76A60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150495B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150495B0 CURRENT (791) */
void func_150495B0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 proposed;
    f32 next;
    f32 velocity;
    f32 value;
    f32 direction;
    f32 change;

    value = arg1 - *arg0;
    if (value < 0.0f) {
        direction = -1.0f;
    } else {
        direction = 1.0f;
    }
    value *= arg3;
    velocity = *arg2;
    change = value - velocity;
    change *= arg4;
    *arg2 += change * arg5;
    next = (*arg2 * arg5) + *arg0;
    proposed = next;
    if (arg1 < next) {
        value = -1.0f;
    } else {
        value = 1.0f;
    }
    if (value == direction) {
        *arg0 = proposed;
    } else {
        *arg0 = arg1;
        *arg2 = 0.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150495B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_76A60/func_150495B0.s")
f32 func_15048A70(f32, f32);
void func_15048758(f32 *);
f32 fabsf(f32);

#pragma intrinsic(fabsf)
void func_15049688(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 value;
    f32 dist;
    f32 direction;
    f32 change;
    s32 close;

    value = func_15048A70(*arg0, arg1);
    dist = fabsf(value);
    close = dist < 10.0f;
    if (value < 0.0f) {
        direction = -1.0f;
    } else {
        direction = 1.0f;
    }
    value *= arg3;
    change = value - *arg2;
    change *= arg4;
    *arg2 += change * arg5;
    if (!close || (((func_15048A70(*arg0 + (*arg2 * arg5), arg1) < 0.0f) ? -1.0f : 1.0f) == direction)) {
        *arg0 += *arg2 * arg5;
    } else {
        *arg0 = arg1;
        *arg2 = 0;
    }
    func_15048758(arg0);
}
