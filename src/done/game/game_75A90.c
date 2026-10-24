#include "types.h"

/*
 * Reviewed source unit: src/game/game_75A90.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_compact_multi_function_units.md
 */

extern u16 D_80085EC0[];
extern u16 D_80085F3C[];
extern u16 D_80085FBC[];

s32 func_150485E0(s32 arg0) {
    s32 var_a1;
    s32 var_v1;
    u16 *var_a2;
    s32 temp_a3;
    u16 *temp_t0;
    u16 temp_t1;

    var_v1 = 7;
    if (arg0 >= 0x7FE0) {
        var_a1 = 3;
        var_a2 = D_80085FBC;
        arg0 -= 0x7FE0;
    } else {
        var_v1 = 0x1FF;
        if (arg0 >= 0x7800) {
            var_v1 = 0x1F;
            var_a1 = 5;
            var_a2 = D_80085F3C;
            arg0 -= 0x7800;
        } else {
            temp_a3 = 9;
            var_a1 = temp_a3;
            var_a2 = D_80085EC0;
        }
    }
    temp_t0 = (u16 *)((u8 *)var_a2 + ((arg0 >> var_a1) * 2));
    temp_a3 = temp_t0[0];
    temp_t1 = temp_t0[1];
    return temp_a3 - (((s32)(temp_a3 - temp_t1) * (arg0 & var_v1)) >> var_a1);
}
u32 func_15048664(s16 arg0) {
    register s32 result;

    result = arg0 >= 0 ? arg0 : -arg0;
    result = func_150485E0(result);
    if (arg0 < 0) {
        result = 0xFFFF - result;
    }
    return result & 0xFFFF;
}
s32 func_150486B8(s16 arg0) {
    register s32 result;

    result = arg0 >= 0 ? arg0 : -arg0;
    result = func_150485E0(result);
    result = arg0 >= 0 ? 0x7FFF - result : result - 0x8000;
    return (s16)result;
}
