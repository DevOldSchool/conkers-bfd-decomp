#include "types.h"

/*
 * Reviewed source unit: src/game/game_D0960.c
 * Boundary evidence: docs/evidence/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A3504
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150A3504();                                /* extern */

s32 func_150A34B0(void *arg0) {
    s32 var_v0;

    if (*(u8 *)((u8 *)arg0 + 0x14) == 1) {
        return 0;
    }
    var_v0 = 0;
    if (!(*(u8 *)((u8 *)arg0 + 0x15) & 3)) {
        return func_150A3504();
    }
    return var_v0;
}
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
/* Call context: func_150AD780: unique active project prototype */
/* Call context: func_150AD78C: unique active project prototype */
f32 func_150AD780(f32);
f32 func_150AD78C(f32);

extern f32 D_8009F674;
extern f32 D_8009F678;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A3504 CURRENT (16606) */
s32 func_150A3504(void *arg0, void *arg1, void *arg2, void *arg3) {
    f32 spA4;
    f32 spA0;
    f32 points[6];
    f32 sp84;
    f32 sp7C;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 *var_v0;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_fa0_4;
    f32 temp_fa1;
    f32 temp_ft0;
    f32 temp_ft2;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv0_5;
    f32 temp_fv0_6;
    f32 temp_fv0_7;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft4;
    f32 var_ft4_2;
    f32 var_ft4_3;
    f32 var_ft5;
    f32 var_fv0;
    s16 temp_v0;

    var_v0 = points;
    var_fa1 = (*(f32 *)((u8 *)arg1 + 0)) - (f32) (*(s16 *)((u8 *)arg0 + 0));
    var_ft4 = (*(f32 *)((u8 *)arg1 + 4)) - (f32) (*(s16 *)((u8 *)arg0 + 2));
    var_fa0 = (*(f32 *)((u8 *)arg1 + 8)) - (f32) (*(s16 *)((u8 *)arg0 + 4));
    do {
        temp_fv0 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_fv1 = (*(f32 *)((u8 *)arg0 + 0x2C));
        (*(f32 *)((u8 *)var_v0 + 0)) = (var_fa1 * temp_fv0) - (var_fa0 * temp_fv1);
        temp_fv0_2 = (*(f32 *)((u8 *)arg0 + 0x28));
        temp_fv1_2 = (*(f32 *)((u8 *)arg0 + 0x24));
        var_fa0 = (var_fa0 * temp_fv0) + (var_fa1 * temp_fv1);
        (*(f32 *)((u8 *)var_v0 + 8)) = (f32) ((var_fa0 * temp_fv0_2) - (var_ft4 * temp_fv1_2));
        (*(f32 *)((u8 *)var_v0 + 4)) = (f32) ((var_ft4 * temp_fv0_2) + (var_fa0 * temp_fv1_2));
        if (var_v0 == points) {
            var_fa1 = (*(f32 *)((u8 *)arg2 + 0)) - (f32) (*(s16 *)((u8 *)arg0 + 0));
            var_ft4 = (*(f32 *)((u8 *)arg2 + 4)) - (f32) (*(s16 *)((u8 *)arg0 + 2));
            var_fa0 = (*(f32 *)((u8 *)arg2 + 8)) - (f32) (*(s16 *)((u8 *)arg0 + 4));
        }
        var_v0 += 3;
    } while (var_v0 != points + 6);
    sp58 = points[0];
    temp_fv0_3 = points[4] - points[1];
    sp64 = points[3] - points[0];
    sp5C = points[1];
    sp68 = temp_fv0_3;
    sp60 = points[2];
    sp6C = points[5] - points[2];
    if (temp_fv0_3 != 0.0f) {
        temp_fv0_4 = 1.0f / sp68;
        temp_fv1_3 = -points[1] * temp_fv0_4;
        spA4 = temp_fv1_3;
        var_ft4_2 = ((f32) (*(s16 *)((u8 *)arg0 + 8)) - points[1]) * temp_fv0_4;
        if (var_ft4_2 < spA4) {
            spA4 = var_ft4_2;
            var_ft4_2 = temp_fv1_3;
        }
        if ((var_ft4_2 < 0.0f) || (spA4 > 1.0f)) {
            return 0;
        }
        if (spA4 < 0.0f) {
            spA4 = 0.0f;
        }
        if (var_ft4_2 > 1.0f) {
            var_ft4_2 = 1.0f;
        }
        goto block_18;
    }
    if ((points[1] < 0.0f) || ((f32) (*(s16 *)((u8 *)arg0 + 8)) < points[1])) {
        return 0;
    }
    var_ft4_2 = 1.0f;
    spA4 = 0.0f;
    spA0 = 1.0f;
block_18:
    temp_fa1 = (sp6C * sp6C) + (sp64 * sp64);
    if (temp_fa1 == 0.0f) {
        return 0;
    }
    sp20 = 2.0f * ((points[2] * sp6C) + (sp64 * points[0]));
    temp_v0 = (*(s16 *)((u8 *)arg0 + 6));
    spA0 = var_ft4_2;
    temp_ft5 = (sp20 * sp20) - ((((points[2] * points[2]) + (points[0] * points[0])) - (f32) (temp_v0 * temp_v0)) * (4.0f * temp_fa1));
    sp54 = temp_ft5;
    if (temp_ft5 < 0.0f) {
        return 0;
    }
    temp_fv0_5 = sqrtf(sp54);
    temp_fa0 = 0.5f / temp_fa1;
    temp_fv1_4 = -sp20;
    temp_ft2 = (temp_fv1_4 + temp_fv0_5) * temp_fa0;
    temp_ft0 = (temp_fv1_4 - temp_fv0_5) * temp_fa0;
    sp1C = temp_ft2;
    var_ft4_3 = temp_ft2;
    sp18 = temp_ft0;
    var_ft5 = temp_ft0;
    if (temp_ft0 < temp_ft2) {
        var_ft4_3 = temp_ft0;
        var_ft5 = temp_ft2;
    }
    if ((var_ft5 < 0.0f) || (var_ft4_3 > 1.0f)) {
        return 0;
    }
    if (var_ft4_3 < 0.0f) {
        var_ft4_3 = 0.0f;
    }
    if (var_ft5 > 1.0f) {
        var_ft5 = 1.0f;
    }
    if ((var_ft5 < spA4) || (spA0 < var_ft4_3)) {
        return 0;
    }
    if (var_ft4_3 < spA4) {
        var_fv0 = spA4;
    } else {
        var_fv0 = var_ft4_3;
    }
    sp28 = (sp64 * var_fv0) + sp58;
    sp2C = (sp68 * var_fv0) + sp5C;
    sp30 = (sp6C * var_fv0) + sp60;
    temp_fa0_2 = -((*(f32 *)((u8 *)arg0 + 0xC)) * D_8009F674);
    sp7C = temp_fa0_2;
    sp84 = func_150AD78C(temp_fa0_2);
    temp_fv0_6 = func_150AD780(temp_fa0_2);
    (*(f32 *)((u8 *)arg3 + 8)) = (f32) ((sp30 * temp_fv0_6) - (sp2C * sp84));
    (*(f32 *)((u8 *)arg3 + 4)) = (f32) ((sp2C * temp_fv0_6) + (sp30 * sp84));
    temp_fa0_3 = -((*(f32 *)((u8 *)arg0 + 0x10)) * D_8009F678);
    sp7C = temp_fa0_3;
    sp84 = func_150AD78C(temp_fa0_3);
    temp_fv0_7 = func_150AD780(temp_fa0_3);
    temp_fa0_4 = (*(f32 *)((u8 *)arg3 + 8));
    (*(f32 *)((u8 *)arg3 + 0)) = (f32) ((sp28 * temp_fv0_7) - (temp_fa0_4 * sp84));
    (*(f32 *)((u8 *)arg3 + 8)) = (f32) ((temp_fa0_4 * temp_fv0_7) + (sp28 * sp84));
    (*(f32 *)((u8 *)arg3 + 0)) = (f32) ((*(f32 *)((u8 *)arg3 + 0)) + (f32) (*(s16 *)((u8 *)arg0 + 0)));
    (*(f32 *)((u8 *)arg3 + 4)) = (f32) ((*(f32 *)((u8 *)arg3 + 4)) + (f32) (*(s16 *)((u8 *)arg0 + 2)));
    (*(f32 *)((u8 *)arg3 + 8)) = (f32) ((*(f32 *)((u8 *)arg3 + 8)) + (f32) (*(s16 *)((u8 *)arg0 + 4)));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A3504 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D0960/func_150A3504.s")
