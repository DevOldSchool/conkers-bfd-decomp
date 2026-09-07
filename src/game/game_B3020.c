#include "types.h"

/*
 * Reviewed source unit: src/game/game_B3020.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_beta_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15085B70
 * - func_15085BE8
 * - func_15085DA8
 * - func_15085DF8
 * - func_15086098
 * - func_15086364
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15085B70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15085BE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15085DA8.s")
f32 func_15086D94(f32, f32, f32, f32, f32);         /* extern */
extern s16 D_80087290;
extern u8 D_8008729C;
extern f32 D_8009D9CC;
extern s32 D_800D2350;
extern s32 D_800D2354;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15085DF8 CURRENT (2862) */
s32 func_15085DF8(f32 arg0, f32 arg1, f32 arg2, s8 arg3, s8 arg4) {
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 temp_fs0;
    f32 temp_ft4;
    f32 temp_ft4_2;
    f32 temp_ft5;
    f32 temp_ft5_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fs1;
    s32 var_s0;
    s32 var_s3;
    s32 var_s5;
    void *temp_v0;
    void *temp_v0_2;

    var_s3 = 0;
    var_fs1 = D_8009D9CC;
    if (arg3 == 0) {
        var_s3 = 1;
    }
    if (D_8008729C != 0xFF) {
        temp_v0 = (D_8008729C * 0x10) + D_800D2350;
        temp_fv1 = (f32) *(s16 *)((u8 *)temp_v0 + 0) - arg0;
        temp_ft4 = (f32) *(s16 *)((u8 *)temp_v0 + 2) - arg1;
        temp_ft5 = (f32) *(s16 *)((u8 *)temp_v0 + 4) - arg2;
        if ((var_s3 == 0) || ((var_s3 != 0) && (sp70 = temp_fv1, sp6C = temp_ft4, sp68 = temp_ft5, (func_15086D94(arg0, arg1, arg2, temp_fv1, temp_ft5) < 0.0f)))) {
            var_fs1 = (temp_fv1 * temp_fv1) + (temp_ft4 * temp_ft4) + (temp_ft5 * temp_ft5) + 10.0f;
        }
        D_8008729C = 0xFF;
    }
    var_s5 = 0xFF;
    var_s0 = 0;
    if (D_80087290 > 0) {
        do {
            temp_v0_2 = (var_s0 * 0x10) + D_800D2350;
            if (((arg4 == *(u8 *)((u8 *)temp_v0_2 + 6)) || (arg4 == -1)) && ((arg3 == *(u8 *)((u8 *)temp_v0_2 + 0xE)) || (arg3 == -1))) {
                temp_fv1_2 = (f32) *(s16 *)((u8 *)temp_v0_2 + 0) - arg0;
                temp_ft4_2 = (f32) *(s16 *)((u8 *)temp_v0_2 + 2) - arg1;
                temp_ft5_2 = (f32) *(s16 *)((u8 *)temp_v0_2 + 4) - arg2;
                temp_fs0 = (temp_fv1_2 * temp_fv1_2) + (temp_ft4_2 * temp_ft4_2) + (temp_ft5_2 * temp_ft5_2);
                if ((temp_fs0 < var_fs1) && ((var_s3 == 0) || ((var_s3 != 0) && (func_15086D94(arg0, arg1, arg2, temp_fv1_2, temp_ft5_2) < 0.0f)))) {
                    var_fs1 = temp_fs0;
                    var_s5 = var_s0;
                }
            }
            var_s0 += 1;
        } while (var_s0 < D_80087290);
    }
    D_800D2354 = (s32) sqrtf(var_fs1);
    return var_s5;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15085DF8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15085DF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15086098.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15086364.s")
