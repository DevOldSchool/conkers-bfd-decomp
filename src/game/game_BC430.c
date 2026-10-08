#include "types.h"

/*
 * Reviewed source unit: src/game/game_BC430.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_single_function_units_up_to_256_bytes.md
 */

f32 func_15047C00(f32 arg0);
f32 func_15047D60(f32 arg0);

extern f32 D_8009DC80;

void func_1508EF80(f32 *arg0, f32 *arg1, f32 arg2, f32 *arg3) {
    f32 sp3C;
    f32 sp38;
    f32 pad0;
    f32 pad1;
    f32 pad2;
    f32 sp28;
    f32 sp24;
    f32 temp_f20;
    f32 temp_f8;
    f32 outz;

    sp3C = arg0[0] - arg1[0];
    sp38 = arg0[2] - arg1[2];
    temp_f20 = arg2 * D_8009DC80;
    sp24 = func_15047C00(temp_f20);
    sp28 = arg1[0] + ((func_15047D60(temp_f20) * sp38) + (sp24 * sp3C));
    sp24 = func_15047D60(temp_f20);
    temp_f8 = func_15047C00(temp_f20) * sp38;
    outz = temp_f8;
    outz += (-sp24 * sp3C);
    outz += arg1[2];
    arg3[0] = sp28;
    arg3[2] = outz;
}
