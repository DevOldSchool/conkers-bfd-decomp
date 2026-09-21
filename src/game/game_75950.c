#include "types.h"

/*
 * Reviewed source unit: src/game/game_75950.c
 * Boundary evidence: docs/evidence/game_medium_single_function_units.md
 */

f32 func_10026530(f32);
f32 func_15048360(f32);
extern f32 D_80098DE0;
extern f32 D_80098DE4;
extern f32 D_80098DE8;
extern f32 D_80098DEC;
extern f32 D_80098DF0;
extern f32 D_80098DF4;
extern f32 D_80098DF8;

f32 func_150484A0(f32 arg0, f32 arg1) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fv1;

    if (arg0 == 0.0f) {
        if (arg1 >= 0.0f) {
            var_fv1 = 0.0f;
        } else {
            var_fv1 = D_80098DE0;
        }
    } else if (arg1 == 0.0f) {
        if (arg0 > 0.0f) {
            var_fv1 = D_80098DE4;
        } else {
            var_fv1 = D_80098DE8;
        }
    } else {
        temp_fv0 = func_10026530((arg0 * arg0) + (arg1 * arg1));
        if (arg1 < arg0) {
            temp_fv0_2 = func_15048360(arg1 / temp_fv0);
            var_fv1 = temp_fv0_2;
            if (arg0 < 0.0f) {
                var_fv1 = D_80098DEC - temp_fv0_2;
            }
        } else {
            temp_fa0 = D_80098DF0 - func_15048360(arg0 / temp_fv0);
            var_fv1 = temp_fa0;
            if (arg1 < 0.0f) {
                var_fv1 = D_80098DF4 - temp_fa0;
            }
            if (var_fv1 < 0.0f) {
                var_fv1 += D_80098DF8;
            }
        }
    }
    return var_fv1;
}
