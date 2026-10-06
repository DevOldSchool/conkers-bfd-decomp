#include "types.h"

/*
 * Reviewed source unit: src/game/game_778B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

f32 func_1504A2B0(f32, f32);
f32 func_1504A620(f32);

f32 func_1504A400(f32 arg0, f32 arg1) {
    f32 base;
    f32 result;

    if ((arg0 != 0.0f) && (arg1 == 0.0f)) {
        return 1.0f;
    }
    if (arg0 == 0.0f) {
        return 0.0f;
    }
    if (((arg0 == 0.0f) && (arg1 == 0.0f)) ||
        ((arg0 < 0.0f) && (arg1 != (f32) (s32) arg1))) {
        return 0.0f;
    }
    if (arg1 != (f32) (s32) arg1) {
        arg0 = func_1504A2B0(func_1504A620(arg0) * arg1, arg1);
    } else if (arg1 > 0.0f) {
        base = arg0;
        arg1--;
        while (arg1--) {
            arg0 *= base;
        }
    } else {
        result = 1.0f;
        while (arg1++) {
            result /= arg0;
        }
        arg0 = result;
    }
    return arg0;
}
