#include "types.h"

/*
 * Reviewed source unit: src/game/game_79F10.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_call_connected_beta_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1504CB98
 * - func_150511E8
 * - func_15051558
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15058EA4(void *, f32, f32, f32, f32, f32, f32);
u32 func_150ADA20(void);

void func_1504CA60(u8 *arg0) {
    f32 horizontal;
    f32 vertical;

    horizontal = 18.0f;
    vertical = *(f32 *)(arg0 + 0x180) + 20.0f;
    *(f32 *)(arg0 + 0x1CC) = *(f32 *)(arg0 + 0x18);
    if (*(f32 *)(arg0 + 0x28) > 30.0f) {
        horizontal = 80.0f;
    }
    if (arg0[0x81] != 0) {
        horizontal = 80.0f;
        vertical -= 30.0f;
        if ((*(f32 *)(arg0 + 0x28) < 5.0f) && (*(f32 *)(arg0 + 0x20) < 0.0f)) {
            arg0[0x81] = 0;
            *(f32 *)(arg0 + 0x20) = 45.0f;
        }
    } else if (*(f32 *)(arg0 + 0x28) < 20.0f) {
        if (!(func_150ADA20() & 0x3F)) {
            *(f32 *)(arg0 + 0x20) = 25.0f;
        }
    }
    func_15058EA4(arg0, vertical, 3.8f, vertical, -3.5f, 80.0f,
                  -horizontal);
    arg0[0x80] = 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_79F10/func_1504CB98.s")
typedef struct {
    u8 pad00[4];
    u8 kind;
    u8 pad05[0x23];
    f32 height;
    u8 pad2C[0x10];
    f32 speed;
    u8 pad40[0x49];
    u8 state;
    u8 pad8A[0x2E];
    f32 pitch;
    u8 padBC[8];
    f32 roll;
    u8 padC8[0x30];
    u32 flags;
    u8 padFC[0x68];
    f32 tiltX;
    f32 tiltZ;
    u8 pad16C[0x1C];
    void *surface;
    f32 position[3];
    u8 pad198[0x8E];
    u8 tiltScale;
} Game79F10Actor;

void func_1510F820(void *, void *, f32 *, f32 *, f32 *, f32 *, f32 *);
f32 func_1505210C(void *, f32, f32, f32 *, f32);
void func_1505A250(f32, f32, f32, f32 *, f32 *);
f32 fabsf(f32);
f32 sqrtf(f32);
#pragma intrinsic(fabsf, sqrtf)
extern f32 D_800992D8, D_800992DC, D_800992E0;
extern f32 D_800992E4, D_800992E8, D_800992EC;
extern f32 D_800992F0, D_800992F4, D_800992F8, D_800992FC, D_80099300;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150511E8 CURRENT (4619) */
void func_150511E8(Game79F10Actor *arg0) {
    f32 x;
    f32 z;
    f32 normalX;
    f32 normalZ;
    f32 length;
    f32 result;
    f32 gain;
    f32 damping;
    f32 scale;
    f32 rise;
    f32 absoluteX;
    f32 pitch;
    f32 *position;
    u32 flag;

    position = arg0->position;
    if (arg0->height <= 0.0f) {
        gain = D_800992D8;
        damping = D_800992DC;
        scale = 35.0f;
        flag = arg0->kind;
        rise = D_800992E0;
        if (flag == 0x28 || flag == 0x77) {
            gain = D_800992E4;
            damping = D_800992E8;
            scale = 7.0f;
            rise = D_800992EC;
        }
        func_1510F820(arg0->surface, position, &normalX, &normalZ,
                      &length, &x, &z);
        if (arg0->flags & 0x100000) {
            func_1510F820(arg0->surface, position, &normalX, &normalZ,
                          &length, &x, &z);
            result = func_1505210C(arg0, x, z, &pitch, 50.0f);
            pitch *= gain;
            arg0->pitch = arg0->pitch + (pitch - arg0->pitch) * damping;
            arg0->roll = arg0->roll + (result * gain - arg0->roll) * damping;
        }
        if (arg0->flags & 0x80000) {
            flag = arg0->tiltScale;
            if (flag != 0) {
                scale = (f32)flag;
            }
            absoluteX = fabsf(x);
            if (absoluteX < D_800992F0 && fabsf(z) < D_800992F0) {
                x = 0.0f;
                length = D_800992F4;
                z = 0.0f;
            } else {
                flag = 0;
                gain = fabsf(z);
                if (absoluteX > 1.0f) {
                    flag = 1;
                    if (x < 0.0f) x = -1.0f;
                    else x = 1.0f;
                }
                if (gain > 1.0f) {
                    flag = 1;
                    if (z < 0.0f) z = -1.0f;
                    else z = 1.0f;
                }
                if (flag && arg0->kind == 0x77) {
                    result = arg0->speed;
                    if (result > 15.0f) arg0->speed = result * D_800992F8;
                    if (arg0->state < 8) arg0->state = 6;
                }
                length = sqrtf(x * x + z * z) * rise + D_800992FC;
                x *= scale;
                z *= scale;
            }
            goto apply;
        }
    } else {
        x = 0.0f;
        length = D_80099300;
        z = 0.0f;
apply:
        func_1505A250(-x, -z, length, &arg0->tiltX, &arg0->tiltZ);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150511E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_79F10/func_150511E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_79F10/func_15051558.s")
/* Call context: func_150484A0: unique active project prototype */
f32 func_150484A0(f32, f32);
f32 func_150AD780(f32);                             /* extern */
f32 func_150AD78C(f32);                             /* extern */
extern f32 D_80099330;
extern f32 D_80099334;
extern f32 D_80099338;

f32 func_1505210C(void *arg0, f32 arg1, f32 arg2, f32 *arg3, f32 arg4) {
    f32 sp34;
    f32 sp2C;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 rotated_x;

    arg2 = -arg2;
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x40) * D_80099330;
    sp2C = temp_fa0;
    sp34 = func_150AD780(temp_fa0);
    temp_fv0 = func_150AD78C(temp_fa0);
    rotated_x = (arg1 * sp34) + (arg2 * temp_fv0);
    arg2 = (-arg1 * temp_fv0) + (arg2 * sp34);
    arg1 = func_150484A0(rotated_x, 1.0f) * D_80099334;
    temp_fv1 = func_150484A0(arg2, 1.0f) * D_80099338;
    arg2 = temp_fv1;
    if (arg1 >= 180.0f) {
        arg1 -= 360.0f;
    }
    if (temp_fv1 >= 180.0f) {
        arg2 = temp_fv1 - 360.0f;
    }
    temp_fv0_2 = -arg4;
    if (arg4 < arg1) {
        arg1 = arg4;
    }
    if (arg1 < temp_fv0_2) {
        arg1 = temp_fv0_2;
    }
    if (arg4 < arg2) {
        arg2 = arg4;
    }
    if (arg2 < temp_fv0_2) {
        arg2 = temp_fv0_2;
    }
    *arg3 = arg2;
    return arg1;
}
