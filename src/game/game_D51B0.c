#include "types.h"

/*
 * Reviewed source unit: src/game/game_D51B0.c
 * Boundary evidence: docs/evidence/game_remaining_single_function_units_up_to_256_bytes.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A7D00
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A7D00 CURRENT (6430) */
void func_150A7D00(volatile s64 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 temp_fv0;
    s32 temp_fv0_2;
    s32 temp_fv0_3;

    arg0[0] = 0;
    arg0[1] = 0;
    temp_fv0 = (s32)(arg1 * 65536.0f);
    arg0[2] = 0;
    arg0[3] = 0;
    arg0[4] = 0;
    arg0[5] = 0;
    temp_fv0_2 = (s32)(arg2 * 65536.0f);
    arg0[6] = 0;
    arg0[7] = 0;
    ((volatile s16 *)arg0)[0] = 1;
    ((volatile s16 *)arg0)[5] = 1;
    temp_fv0_3 = (s32)(arg3 * 65536.0f);
    ((volatile s16 *)arg0)[10] = 1;
    ((volatile s16 *)arg0)[15] = 1;
    ((volatile s16 *)arg0)[12] = (s16)((u32)temp_fv0 >> 16);
    ((volatile s16 *)arg0)[13] = (s16)((u32)temp_fv0_2 >> 16);
    ((volatile s16 *)arg0)[14] = (s16)((u32)temp_fv0_3 >> 16);
    ((volatile s16 *)arg0)[28] = (s16)temp_fv0;
    ((volatile s16 *)arg0)[29] = (s16)temp_fv0_2;
    ((volatile s16 *)arg0)[30] = (s16)temp_fv0_3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A7D00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D51B0/func_150A7D00.s")
