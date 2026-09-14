#include "types.h"

/*
 * Reviewed source unit: src/game/game_75C90.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150487E0
 * - func_15048864
 * - func_150488C8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 fabsf(f32 arg0);
#pragma intrinsic(fabsf)

extern u16 D_80098E00[];
extern f32 D_80099000;
extern f32 D_80099004;
extern f32 D_80099008;
extern f32 D_8009900C;
extern f32 D_80099010;
extern f32 D_80099014;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150487E0 CURRENT (1000) */
f32 func_150487E0(f32 arg0) {
    f32 var_ft4;
    f32 temp_fa1;
    f32 var_fv1;
    u16 temp_t9;
    volatile u16 *table;

    table = D_80098E00;
    temp_t9 = *(u16 *)((u8 *)table + ((s32)(fabsf(arg0) * D_80099000) * 2));
    var_ft4 = (f32)temp_t9;
    if ((s32)temp_t9 < 0) {
        var_ft4 += 4294967296.0f;
    }
    temp_fa1 = (var_ft4 * D_80099004) / 65536.0f;
    if (arg0 < 0.0f) {
        var_fv1 = -temp_fa1;
    } else {
        var_fv1 = temp_fa1;
    }
    return var_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150487E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_75C90/func_150487E0.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15048864 CURRENT (30) */
f32 func_15048864(f32 arg0) {
    f32 temp_fa1;
    f32 var_fv1;

    temp_fa1 = (f32)((s32)D_80098E00[(s32)(fabsf(arg0) * D_80099008)] >> 10);
    if (arg0 < 0.0f) {
        var_fv1 = 255.0f - temp_fa1;
    } else {
        var_fv1 = temp_fa1;
    }
    return var_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15048864 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_75C90/func_15048864.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150488C8 CURRENT (15) */
f32 func_150488C8(f32 arg0) {
    f32 scaled;
    f32 fraction;
    f32 lower;
    f32 upper;
    f32 result;
    s32 index;

    scaled = fabsf(arg0) * D_8009900C;
    index = (s32)scaled;
    fraction = scaled - (f32)index;
    lower = D_80098E00[index];
    if (index < 0xFF) {
        upper = D_80098E00[index + 1];
    } else {
        upper = D_80099010;
    }

    result = (((upper - lower) * fraction) + lower) * D_80099014 / 65536.0f;
    if (arg0 < 0.0f) {
        return -result;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150488C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_75C90/func_150488C8.s")
