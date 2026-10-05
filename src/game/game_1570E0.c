#include "types.h"

/*
 * Reviewed source unit: src/game/game_1570E0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15129C30
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct { u16 buttons; s8 x, y; } Game1570E0Input;
typedef struct {
    u8 pad00[0x23D]; u8 index;
    u8 pad23E[0x66]; f32 targetX, targetY, targetZ;
    u8 pad2B0[0xC]; f32 lookX, lookY, lookZ;
    u8 pad2C8[0x30]; f32 x, y, z;
    u8 pad304[0x40]; f32 value344;
    u8 pad348[0x18]; f32 ground;
    u8 pad364[6]; u16 pressed;
    Game1570E0Input *input;
    u8 pad370[0xC]; f32 yaw, yawCopy;
    u8 pad384[4]; f32 pitch;
    u8 pad38C[4]; f32 value390, savedYaw, pitchRadians, yawRadians, yawRadiansCopy;
    u8 pad3A4[0x248]; f32 roll; s32 flags;
    u8 pad5F4[0x4C]; s32 result640, result644, result648;
} Game1570E0Camera;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

f32 func_15047C00(f32);
f32 func_15047D60(f32);
void func_1510E7A4(s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32);

extern f32 D_80089560[];
extern f32 D_80089570[];
extern f32 D_80089580[];
extern f32 D_800A3620;
extern f32 D_800A3624;
extern f32 D_800A3628;
extern f32 D_800A362C;
extern f32 D_800A3630;
extern f32 D_800A3634;
extern f32 D_800A3638;
extern f32 D_800A363C;
extern f32 D_800A3640;
extern f32 D_800A3644;
extern f32 D_800A3648;
extern f32 D_800A364C;
extern s32 D_800BEA08;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15129C30 CURRENT (9177) */
void func_15129C30(Game1570E0Camera *arg0) {
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp68;
    f32 sp60;
    f32 *var_a0;
    f32 *var_a2;
    f32 *var_v0;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fa1_3;
    f32 temp_ft4;
    f32 temp_ft4_2;
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
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_ft2;
    f32 var_ft4;
    f32 var_ft4_2;
    f32 var_fv0;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_v1;
    Game1570E0Input *temp_t6;
    Game1570E0Input *temp_v1;

    sp7C = 0.0f;
    temp_t6 = arg0->input;
    temp_a3 = arg0->index;
    temp_a2 = temp_t6->buttons;
    if (arg0->pressed & 0x400) {
        temp_v0 = arg0->flags;
        if (temp_v0 & 0x80000000) {
            arg0->flags = (s32) (temp_v0 & 0x7FFFFFFF);
        } else {
            arg0->flags = (s32) (temp_v0 | 0x80000000);
        }
    }
    if (!(arg0->flags & 0x80000000)) {
        temp_v1 = arg0->input;
        temp_v0_2 = temp_v1->x;
        if ((temp_v0_2 < -4) || (temp_v0_2 >= 5)) {
            var_fv1 = (f32) temp_v0_2;
        } else {
            var_fv1 = 0.0f;
        }
        temp_v0_3 = temp_v1->y;
        var_v1 = temp_a3 * 4;
        if ((temp_v0_3 < -4) || (temp_v0_3 >= 5)) {
            var_fa0 = (f32) temp_v0_3;
        } else {
            var_fa0 = 0.0f;
        }
        temp_fv0 = var_fv1 / 80.0f;
        if (temp_fv0 > 0.0f) {
            arg0->yaw = (f32) (arg0->yaw - (temp_fv0 * temp_fv0 * (f32) D_800BEA08));
        } else {
            arg0->yaw = (f32) (arg0->yaw + (temp_fv0 * temp_fv0 * (f32) D_800BEA08));
        }
        arg0->yawRadians = (f32) (arg0->yaw * D_800A3620);
        temp_fv0_2 = (var_fa0 / 80.0f) * 7.0f;
        if (temp_fv0_2 > 0.0f) {
            var_fv1_2 = (f32) D_800BEA08;
            var_ft2 = temp_fv0_2 * temp_fv0_2 * var_fv1_2;
        } else {
            var_fv1_2 = (f32) D_800BEA08;
            var_ft2 = -temp_fv0_2 * temp_fv0_2 * var_fv1_2;
        }
        sp80 = var_ft2;
        if (temp_a2 & 4) {
            var_a2 = (f32 *) ((u8 *) D_80089560 + var_v1);
            var_fa0_2 = D_800A3624;
            *var_a2 += var_fa0_2;
            arg0->y = (f32) (arg0->y - (*var_a2 * var_fv1_2));
        } else if (temp_a2 & 8) {
            var_v1 = temp_a3 * 4;
            var_a2 = (f32 *) ((u8 *) D_80089560 + var_v1);
            var_fa0_2 = D_800A3628;
            *var_a2 += var_fa0_2;
            arg0->y = (f32) (arg0->y + (*var_a2 * var_fv1_2));
        } else {
            var_v1 = temp_a3 * 4;
            var_a2 = (f32 *) ((u8 *) D_80089560 + var_v1);
            *var_a2 = 0.0f;
            var_fa0_2 = D_800A362C;
        }
        if (temp_a2 & 0x8000) {
            var_a0 = (f32 *) ((u8 *) D_80089580 + var_v1);
            *var_a0 += D_800A3630;
            arg0->pitch = (f32) (arg0->pitch - (*var_a0 * (f32) D_800BEA08));
        } else if (temp_a2 & 0x4000) {
            var_a0 = (f32 *) ((u8 *) D_80089580 + var_v1);
            *var_a0 += D_800A3634;
            arg0->pitch = (f32) (arg0->pitch + (*var_a0 * (f32) D_800BEA08));
        } else {
            var_a0 = (f32 *) ((u8 *) D_80089580 + var_v1);
            *var_a0 = 0.0f;
        }
        temp_fv0_3 = arg0->pitch;
        if (temp_fv0_3 < -89.5f) {
            arg0->pitch = -89.5f;
        } else {
            if (temp_fv0_3 > 89.5f) {
                var_ft4 = 89.5f;
            } else {
                var_ft4 = temp_fv0_3;
            }
            arg0->pitch = var_ft4;
        }
        temp_v0_4 = temp_a2 & 0x2000;
        arg0->pitchRadians = (f32) (arg0->pitch * D_800A3620);
        if (temp_v0_4 != 0) {
            if ((temp_a2 & 2) && (temp_v0_4 != 0)) {
                var_v0 = (f32 *) ((u8 *) D_80089570 + var_v1);
                *var_v0 += var_fa0_2;
                arg0->roll = (f32) (arg0->roll - (*var_v0 * D_800A3638));
            } else if ((temp_a2 & 1) && (temp_v0_4 != 0)) {
                var_v0 = (f32 *) ((u8 *) D_80089570 + var_v1);
                *var_v0 += var_fa0_2;
                arg0->roll = (f32) (arg0->roll + (*var_v0 * D_800A363C));
            } else {
                var_v0 = (f32 *) ((u8 *) D_80089570 + var_v1);
                *var_v0 = 0.0f;
            }
            goto block_49;
        }
        if (temp_a2 & 2) {
            var_v0 = (f32 *) ((u8 *) D_80089570 + var_v1);
            *var_v0 += D_800A3640;
            var_fv0 = *var_v0;
            sp7C = 0.0f - var_fv0;
        } else if (temp_a2 & 1) {
            var_v0 = (f32 *) ((u8 *) D_80089570 + var_v1);
            *var_v0 += D_800A3644;
            var_fv0 = *var_v0;
            sp7C = 0.0f + var_fv0;
        } else {
            var_v0 = (f32 *) ((u8 *) D_80089570 + var_v1);
            *var_v0 = 0.0f;
block_49:
            var_fv0 = *var_v0;
        }
        if (var_fv0 > 100.0f) {
            *var_v0 = 100.0f;
        } else {
            *var_v0 = var_fv0;
        }
        temp_fv0_4 = *var_a0;
        if (temp_fv0_4 > 8.0f) {
            *var_a0 = 8.0f;
        } else {
            *var_a0 = temp_fv0_4;
        }
        temp_fv0_5 = *var_a2;
        if (temp_fv0_5 > 40.0f) {
            *var_a2 = 40.0f;
        } else {
            *var_a2 = temp_fv0_5;
        }
        temp_fv0_6 = arg0->roll;
        if (temp_fv0_6 < -45.0f) {
            arg0->roll = -45.0f;
        } else {
            if (temp_fv0_6 > 45.0f) {
                var_ft4_2 = 45.0f;
            } else {
                var_ft4_2 = temp_fv0_6;
            }
            arg0->roll = var_ft4_2;
        }
        temp_fa1 = -func_15047D60(arg0->yawRadians);
        sp8C = temp_fa1;
        temp_fv1 = -func_15047C00(arg0->yawRadians);
        arg0->x = (f32) (arg0->x + (temp_fa1 * sp80));
        arg0->z = (f32) (arg0->z + (temp_fv1 * sp80));
        arg0->x = (f32) (arg0->x + (-temp_fv1 * sp7C));
        arg0->value344 = 0.0f;
        temp_fa1_2 = temp_fa1 * 600.0f;
        arg0->z = (f32) (arg0->z + (temp_fa1 * sp7C));
        temp_fa0 = temp_fv1 * 600.0f;
        sp84 = temp_fa0;
        sp8C = temp_fa1_2;
        temp_ft4 = sqrtf((temp_fa1_2 * temp_fa1_2) + (temp_fa0 * temp_fa0));
        sp60 = temp_ft4;
        sp88 = func_15047D60(arg0->pitchRadians) * temp_ft4;
        temp_fa1_3 = func_15047C00(arg0->pitchRadians) * temp_fa1_2;
        sp8C = temp_fa1_3;
        temp_fv1_2 = arg0->x + temp_fa1_3;
        temp_ft5 = func_15047C00(arg0->pitchRadians) * temp_fa0;
        arg0->targetX = temp_fv1_2;
        arg0->lookX = temp_fv1_2;
        temp_ft4_2 = arg0->z + temp_ft5;
        arg0->value390 = 0.0f;
        arg0->targetX = (f32) arg0->lookX;
        temp_fa0_2 = arg0->y + sp88;
        arg0->lookZ = temp_ft4_2;
        arg0->targetZ = temp_ft4_2;
        arg0->lookY = temp_fa0_2;
        arg0->targetY = temp_fa0_2;
        arg0->targetZ = (f32) arg0->lookZ;
        arg0->targetY = (f32) arg0->lookY;
    } else {
        arg0->savedYaw = (f32) arg0->yaw;
    }
    arg0->yawCopy = arg0->yaw;
    temp_fv1_3 = arg0->yaw * D_800A3648;
    arg0->yawRadians = temp_fv1_3;
    arg0->yawRadiansCopy = temp_fv1_3;
    temp_fv0_7 = arg0->y;
    func_1510E7A4((s32) &arg0->result644, (s32) &arg0->result648, (s32) &sp68, (s32) &arg0->ground, (s32) &arg0->result640, 0, arg0->x, temp_fv0_7, arg0->z, temp_fv0_7, 0U, 0, D_800A364C, temp_fv0_7);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15129C30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1570E0/func_15129C30.s")
void func_151E6C1C(u8 arg0, void *arg1);

void func_1512A360(void *arg0) {
    func_151E6C1C(*(u8 *)((u8 *)arg0 + 0x23D), arg0);
}
