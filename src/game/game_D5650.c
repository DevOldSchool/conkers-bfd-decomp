#include "types.h"

/*
 * Reviewed source unit: src/game/game_D5650.c
 * Boundary evidence: docs/evidence/game_raw_handwritten_entry_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A81A0
 * - func_150A81D0
 * - func_150A94DC
 * - func_150A9984
 * - func_150A9B0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s64 **D_80088544;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A81A0 CURRENT (3370) */
void func_150A81A0(s64 *arg0, s64 *arg1) {
    s64 *temp_a3;
    s64 *var_a0;
    s64 *var_a1;

    var_a0 = arg0;
    var_a1 = arg1;
    temp_a3 = (void *)(var_a1 + 0x40);
    do {
        *var_a0 = *var_a1;
        var_a0 += 8;
        var_a1 += 8;
    } while (var_a1 != temp_a3);
    *D_80088544 = var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A81A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A81A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A81D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A94DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A9984.s")
f32 func_150AD780(f32);
f32 func_150AD78C(f32);
extern f32 D_8009F6D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A9B0C CURRENT (9318) */
void func_150A9B0C(f32 *arg0, f32 arg1, f32 arg2, f32 arg3,
                   f32 arg4, f32 arg5, f32 arg6) {
    f32 sin_x;
    f32 cos_x;
    f32 neg_cos_x;
    f32 sin_y;
    f32 cos_y;
    f32 neg_cos_y;
    f32 sin_z;
    f32 cos_z;
    f32 neg_cos_z;
    f32 temp_1;
    f32 temp_2;
    f32 temp_3;
    f32 temp_4;

    arg1 *= D_8009F6D0;
    sin_x = func_150AD780(arg1);
    cos_x = func_150AD78C(arg1);
    neg_cos_x = -cos_x;
    arg2 *= D_8009F6D0;
    sin_y = func_150AD780(arg2);
    cos_y = func_150AD78C(arg2);
    neg_cos_y = -cos_y;
    arg3 *= D_8009F6D0;
    sin_z = func_150AD780(arg3);
    cos_z = func_150AD78C(arg3);
    neg_cos_z = -cos_z;

    temp_1 = sin_x * sin_z;
    temp_2 = neg_cos_x * sin_z;
    temp_3 = sin_x * neg_cos_z;
    temp_4 = neg_cos_x * neg_cos_z;
    arg0[0] = (cos_z * sin_y) * arg4;
    arg0[1] = cos_z * arg4;
    arg0[2] = (cos_z * neg_cos_y) * arg4;
    arg0[4] = ((temp_3 * sin_y) + (cos_x * cos_y)) * arg5;
    arg0[5] = temp_1 * arg5;
    arg0[6] = ((temp_3 * neg_cos_y) + (cos_x * sin_y)) * arg5;
    arg0[8] = ((temp_4 * sin_y) + (sin_x * cos_y)) * arg6;
    arg0[9] = temp_2 * arg6;
    arg0[10] = ((temp_4 * neg_cos_y) + (sin_x * sin_y)) * arg6;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A9B0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A9B0C.s")
