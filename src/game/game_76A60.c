#include "types.h"

/*
 * Reviewed source unit: src/game/game_76A60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 */

void func_150495B0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 value;
    f32 direction;
    f32 change;
    f32 sign;
    f32 next;

    value = arg1 - *arg0;
    if (value < 0.0f) {
        direction = -1.0f;
    } else {
        direction = 1.0f;
    }
    value *= arg3;
    change = value - *arg2;
    change *= arg4;
    *arg2 += change * arg5;
    next = *arg0 + (*arg2 * arg5);
    if (arg1 < next) {
        sign = -1.0f;
    } else {
        sign = 1.0f;
    }
    if (sign == direction) {
        *arg0 = next;
    } else {
        *arg0 = arg1;
        *arg2 = 0;
    }
}
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
