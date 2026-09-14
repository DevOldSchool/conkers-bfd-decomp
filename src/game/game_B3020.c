#include "types.h"

/*
 * Reviewed source unit: src/game/game_B3020.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_beta_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15085BE8
 * - func_15085DA8
 * - func_15085DF8
 * - func_15086098
 * - func_15086364
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s16 width;
    s16 height;
    u8 data[1];
} GameB3020Image;

GameB3020Image *func_1502B5C8(s32, s32, s32, void *);
void func_15085BE8(void);
extern s16 D_80087290;
extern s16 D_80087294;
extern u8 *D_800D2350;

void func_15085B70(void *arg0) {
    GameB3020Image *image;

    image = func_1502B5C8(0, 2, 0x19, arg0);
    if (image == 0) {
        D_80087290 = 0;
        D_80087294 = 0;
        D_800D2350 = 0;
    } else {
        D_80087290 = image->width;
        D_80087294 = image->height;
        D_800D2350 = image->data;
    }
    func_15085BE8();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15085BE8.s")
extern f32 D_800D2360;
extern u8 D_800D237C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15085DA8 CURRENT (540) */
u8 func_15085DA8(f32 arg0) {
    f32 *var_v0;
    f32 temp_ft1;
    s32 var_v1;

    var_v1 = 0;
    if (D_800D2360 <= arg0) {
        var_v0 = &D_800D2360;
        do {
            temp_ft1 = var_v0[1];
            var_v1 += 1;
            var_v0 += 1;
        } while (temp_ft1 <= arg0);
    }
    return D_800D237C[var_v1];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15085DA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15085DA8.s")
f32 func_15086D94(f32, f32, f32, f32, f32);         /* extern */
extern s16 D_80087290;
extern u8 D_8008729C;
extern f32 D_8009D9CC;
extern s32 D_800D2354;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15085DF8 CURRENT (2373) */
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
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_s3 = 0;
    var_fs1 = D_8009D9CC;
    if (arg3 == 0) {
        var_s3 = 1;
    }
    if (D_8008729C != 0xFF) {
        temp_v0 = (void *)((D_8008729C * 0x10) + D_800D2350);
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
            temp_v0_2 = (void *)((var_s0 * 0x10) + D_800D2350);
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
