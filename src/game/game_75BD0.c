#include "types.h"

/*
 * Reviewed source unit: src/game/game_75BD0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_small_multi_function_units.md
 */

f32 func_15048A70(f32 arg0, f32 arg1);

f32 func_15048720(f32 arg0, f32 arg1, f32 arg2) {
    f32 result = func_15048A70(arg1, arg2);
    f32 product = result * arg0;

    return arg1 + product;
}
void func_15048758(f32 *arg0) {
    while (*arg0 < 0.0f) {
        *arg0 += 360.0f;
    }
    while (*arg0 >= 360.0f) {
        *arg0 -= 360.0f;
    }
}
