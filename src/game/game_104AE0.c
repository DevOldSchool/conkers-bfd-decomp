#include "types.h"

/*
 * Reviewed source unit: src/game/game_104AE0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D765C
 * - func_150D7790
 * - func_150D7928
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE9E4;
extern u16 D_800D9910;

void func_150D7630(s32 arg0) {
    if (arg0 == 0) {
        D_800D9910 += D_800BE9E4 << 6;
    }
}
s32 func_1510D0EC(s32, s32 *, s32, s32);
extern s32 *D_80088900[2];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D765C CURRENT (2970) */
s32 *func_150D765C(s32 *arg0) {
    struct {
        s32 *sp4C[2];
        u8 pad54[0xC];
        s32 sp60;
    } locals;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 *var_s3;

    var_s3 = arg0;
    var_s2 = 0;
    locals.sp4C[0] = D_80088900[0];
    var_s0 = 8;
    locals.sp4C[1] = D_80088900[1];
    var_s1 = (s32)D_800D9910 >> 8;
    do {
        if (var_s0 >= 0x18) {
            var_s2 = 1;
        }
        temp_v0 = func_1510D0EC(locals.sp4C[var_s2][var_s1 % 5],
                                &locals.sp60, 3, 0);
        var_s3[0] = (var_s0 & 0xFFFF) | 0xDB060000;
        var_s3[1] = temp_v0;
        var_s3 += 2;
        var_s0 += 4;
        var_s1 += 0xD;
    } while (var_s0 != 0x20);
    return var_s3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D765C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_104AE0/func_150D765C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_104AE0/func_150D7790.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_104AE0/func_150D7928.s")
