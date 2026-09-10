#include "types.h"

/*
 * Reviewed source unit: src/game/game_79F10.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_beta_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1504CA60
 * - func_1504CB98
 * - func_150511E8
 * - func_15051558
 * - func_1505210C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_79F10/func_1504CA60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_79F10/func_1504CB98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_79F10/func_150511E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_79F10/func_15051558.s")
/* Call context: func_150484A0: unique active project prototype */
f32 func_150484A0(f32, f32);
f32 func_150AD780(f32);                             /* extern */
f32 func_150AD78C(f32);                             /* extern */
extern f32 D_80099330;
extern f32 D_80099334;
extern f32 D_80099338;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505210C CURRENT (3769) */
f32 func_1505210C(void *arg0, f32 arg1, f32 arg2, f32 *arg3, f32 arg4) {
    f32 sp34;
    f32 sp2C;
    f32 temp_fa0;
    f32 temp_fs0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fs0;
    f32 var_fs1;

    temp_fs0 = -arg2;
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x40) * D_80099330;
    sp2C = temp_fa0;
    sp34 = func_150AD780(temp_fa0);
    temp_fv0 = func_150AD78C(temp_fa0);
    var_fs1 = func_150484A0((arg1 * sp34) + (temp_fs0 * temp_fv0), 1.0f) * D_80099334;
    temp_fv1 = func_150484A0((-arg1 * temp_fv0) + (temp_fs0 * sp34), 1.0f) * D_80099338;
    var_fs0 = temp_fv1;
    if (var_fs1 >= 180.0f) {
        var_fs1 -= 360.0f;
    }
    if (temp_fv1 >= 180.0f) {
        var_fs0 = temp_fv1 - 360.0f;
    }
    temp_fv0_2 = -arg4;
    if (arg4 < var_fs1) {
        var_fs1 = arg4;
    }
    if (var_fs1 < temp_fv0_2) {
        var_fs1 = temp_fv0_2;
    }
    if (arg4 < var_fs0) {
        var_fs0 = arg4;
    }
    if (var_fs0 < temp_fv0_2) {
        var_fs0 = temp_fv0_2;
    }
    *arg3 = var_fs0;
    return var_fs1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505210C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_79F10/func_1505210C.s")
