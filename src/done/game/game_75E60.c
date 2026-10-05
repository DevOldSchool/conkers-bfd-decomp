#include "types.h"

/*
 * Reviewed source unit: src/game/game_75E60.c
 * Boundary evidence: docs/evidence/game_final_compact_units.md
 * Semantic evidence: docs/evidence/trig_angle_helper_semantics.md
 */

/* Keep address symbols for linking and registered match evidence. */
#define trig_cos_turn256_lut func_150489B0
#define trig_sin_turn256_lut func_15048A40
#define angle_delta_degrees_f32_single_wrap func_15048A70
#define angle_delta_degrees_s32_single_wrap func_15048AD0

f32 trig_cos_turn256_lut(u8 arg0);
extern f32 D_8009A220[];

f32 trig_cos_turn256_lut(u8 arg0) {
    f32 value;
    s32 index;

    index = arg0;
    if (arg0 >= 0x41) {
        if (index >= 0x81) {
            if (index >= 0xC1) {
                value = D_8009A220[0x100 - index];
            } else {
                value = -D_8009A220[index - 0x80];
            }
        } else {
            value = -D_8009A220[0x80 - index];
        }
    } else {
        value = D_8009A220[arg0];
    }
    return value;
}
f32 trig_sin_turn256_lut(u8 arg0) {
    return trig_cos_turn256_lut(arg0 - 0x40);
}
f32 angle_delta_degrees_f32_single_wrap(f32 arg0, f32 arg1) {
    f32 temp_fv0 = arg0 - arg1;
    if (temp_fv0 > 180.0f) {
        arg0 -= 360.0f;
    } else if (temp_fv0 <= -180.0f) {
        arg1 -= 360.0f;
    }
    return arg1 - arg0;
}

s32 angle_delta_degrees_s32_single_wrap(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = arg0 - arg1;
    if (temp_v0 >= 0xB5) {
        arg0 -= 0x168;
    } else if (temp_v0 < -0xB3) {
        arg1 -= 0x168;
    }
    return arg1 - arg0;
}
