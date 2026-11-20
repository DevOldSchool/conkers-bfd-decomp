#include "types.h"

/*
 * Reviewed source unit: src/game/game_76C90.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 */

f32 func_150497E0(f32 *arg0, s32 arg1, f32 arg2) {
    f32 a;
    f32 c;
    f32 b;
    f32 result;

    a = ((((-0.5f * arg0[arg1]) + (1.5f * arg0[arg1 + 1])) + (-1.5f * arg0[arg1 + 2])) + (arg0[arg1 + 3] * 0.5f));
    b = (((arg0[arg1] + (-2.5f * arg0[arg1 + 1])) + (2.0f * arg0[arg1 + 2])) + (arg0[arg1 + 3] * -0.5f));
    c = ((-0.5f * arg0[arg1]) + (arg0[arg1 + 2] * 0.5f));
    result = (((((a * arg2) + b) * arg2) + c) * arg2);
    result += arg0[arg1 + 1];
    return result;
}
f32 func_150498A4(f32 *arg0, s32 arg1, f32 arg2, f32 *arg3) {
    f32 result;
    f32 c;
    f32 b;
    f32 a;

    a = ((((-0.5f * arg0[arg1]) + (1.5f * arg0[arg1 + 1])) + (-1.5f * arg0[arg1 + 2])) + (arg0[arg1 + 3] * 0.5f));
    b = (((arg0[arg1] + (-2.5f * arg0[arg1 + 1])) + (2.0f * arg0[arg1 + 2])) + (arg0[arg1 + 3] * -0.5f));
    c = ((-0.5f * arg0[arg1]) + (arg0[arg1 + 2] * 0.5f));
    result = arg0[arg1 + 1];
    *arg3 = ((((a * 3.0f) * arg2) + (2.0f * b)) * arg2) + c;
    result = (((((a * arg2) + b) * arg2) + c) * arg2) + result;
    return result;
}
