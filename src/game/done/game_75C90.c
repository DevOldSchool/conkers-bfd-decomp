#include "types.h"

/*
 * Reviewed source unit: src/game/game_75C90.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 */

f32 fabsf(f32 arg0);
#pragma intrinsic(fabsf)

extern u16 D_80098E00[];

f32 func_150487E0(f32 arg0, f32 value) {
    f32 result;

    value = (D_80098E00[(s32)(fabsf(arg0) * 255.99998f)] * 1.5707964f) / 65536.0f;
    if (arg0 < 0.0f) {
        result = -value;
    } else {
        result = value;
    }
    return result;
}

f32 func_15048864(f32 arg0, f32 arg1) {
    f32 var_fv1;

    arg1 = (f32)((s32)D_80098E00[(s32)(fabsf(arg0) * 255.99998f)] >> 10);
    if (arg0 < 0.0f) {
        var_fv1 = 255.0f - arg1;
    } else {
        var_fv1 = arg1;
    }
    return var_fv1;
}

f32 func_150488C8(f32 arg0) {
    f32 scaled;
    f32 fraction;
    f32 lower;
    f32 upper;
    s32 index;

    scaled = fabsf(arg0) * 255.99998f;
    index = (s32)scaled;
    fraction = scaled - (f32)index;
    lower = D_80098E00[index];
    if (index < 0xFF) {
        upper = D_80098E00[index + 1];
    } else {
        upper = 65535.0f;
    }

    lower = (((upper - lower) * fraction) + lower) * 1.5707964f / 65536.0f;
    if (arg0 < 0.0f) {
        return -lower;
    }
    return lower;
}
