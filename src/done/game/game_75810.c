#include "types.h"

/*
 * Reviewed source unit: src/game/game_75810.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 * Semantic evidence: docs/evidence/trig_angle_helper_semantics.md
 */

/* Keep address symbols for linking and registered match evidence. */
#define trig_acos_radians_clamped_lut func_15048360
#define trig_asin_radians_clamped_lut func_15048408

u32 func_15048664(s16);                             /* extern */
extern f32 D_80098DD0;
extern f32 D_80098DD4;

f32 trig_acos_radians_clamped_lut(f32 arg0) {
    s16 var_a0;

    if (arg0 >= 1.0f) {
        var_a0 = 0x7FFF;
    } else if (arg0 <= -1.0f) {
        var_a0 = -0x7FFF;
    } else {
        var_a0 = (s16) (s32) (arg0 * D_80098DD0);
    }
    return (f32) func_15048664(var_a0) * D_80098DD4;
}
s32 func_150486B8(s16);                             /* extern */
extern f32 D_80098DD8;
extern f32 D_80098DDC;

f32 trig_asin_radians_clamped_lut(f32 arg0) {
    s16 var_a0;

    if (arg0 >= 1.0f) {
        var_a0 = 0x7FFF;
    } else if (arg0 <= -1.0f) {
        var_a0 = -0x7FFF;
    } else {
        var_a0 = (s16) (s32) (arg0 * D_80098DD8);
    }
    return (f32) func_150486B8(var_a0) * D_80098DDC;
}
