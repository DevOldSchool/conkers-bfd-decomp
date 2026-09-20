#include "types.h"

/*
 * Reviewed source unit: src/game/game_19EAB0.c
 * Boundary evidence: docs/evidence/game_raw_direct_helper_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15171600
 * - func_151717FC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_19EAB0/func_15171600.s")
void func_151700D8(f32, f32, f32 *, f32, f32, s32, f32, s32, s32,
                   s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151717FC CURRENT (2244) */
void func_151717FC(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   f32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   f32 arg10, u8 arg11, s32 arg12) {
    f32 sp50[12];
    f32 sp3C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fa1 = (f32)*(s16 *)((u8 *)arg0 + 0x10) + arg3;
    temp_fa0 = (f32)*(s16 *)((u8 *)arg0 + 0x12) + arg4;
    temp_ft4 = (f32)*(s16 *)((u8 *)arg0 + 0x14) + arg5;
    sp50[1] = temp_fa0;
    sp50[4] = temp_fa0;
    temp_ft5 = arg1 + temp_fa1;
    sp50[7] = temp_fa0;
    sp50[0] = temp_ft5;
    sp50[9] = temp_ft5;
    temp_fv1 = temp_fa1 - arg1;
    sp3C = temp_ft4 - arg2;
    temp_fv0 = arg2 + temp_ft4;
    sp50[3] = temp_fv1;
    sp50[6] = temp_fv1;
    sp50[2] = temp_fv0;
    sp50[5] = temp_fv0;
    sp50[10] = temp_fa0;
    sp50[8] = sp3C;
    sp50[11] = sp3C;
    func_151700D8(temp_fa0, temp_fa1, sp50, temp_fa1, temp_ft4,
                  arg7, arg10, arg6, arg8, arg9, arg11, arg12);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151717FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19EAB0/func_151717FC.s")
