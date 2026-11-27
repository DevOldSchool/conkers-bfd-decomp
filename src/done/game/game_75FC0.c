#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_75FC0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 */

void func_1503E5F8(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150A7A48(void *, void *, void *);
void func_150A7BC0(void *);
void func_150A8050(void *, f32, f32, f32);

void func_15048B10(u8 *arg0, void *arg1) {
    struct {
        u8 sp34[0x40];
        u8 sp74[0x40];
        u8 spB4[0x40];
        u8 spF4[0x40];
        u8 sp134[0x40];
        u8 sp174[0x40];
        f32 sp1B4;
        f32 sp1B8;
        f32 sp1BC;
        f32 sp1C0;
        f32 sp1C4;
        f32 sp1C8;
        f32 sp1CC;
        f32 sp1D0;
        f32 sp1D4;
    } locals;

    func_1503E5F8(arg0, (s32)&locals.sp1D4, (s32)&locals.sp1D0,
                  (s32)&locals.sp1CC, (s32)&locals.sp1BC,
                  (s32)&locals.sp1B8, (s32)&locals.sp1B4,
                  (s32)&locals.sp1C8, (s32)&locals.sp1C4,
                  (s32)&locals.sp1C0);
    func_150A7BC0(locals.spB4);
    *(f32 *)(locals.spB4 + 0x30) = -locals.sp1D4;
    *(f32 *)(locals.spB4 + 0x34) = -locals.sp1D0;
    *(f32 *)(locals.spB4 + 0x38) = -locals.sp1CC;
    func_150A8050(locals.sp174, -locals.sp1BC, 0.0f, 0.0f);
    func_150A8050(locals.sp134, 0.0f, -locals.sp1B8, 0.0f);
    func_150A8050(locals.spF4, 0.0f, 0.0f, -locals.sp1B4);
    func_150A7A48(locals.spB4, locals.spF4, locals.sp74);
    func_150A7A48(locals.sp74, locals.sp134, locals.sp34);
    func_150A7A48(locals.sp34, locals.sp174, arg1);
}
extern f32 D_80099020[6];
extern f32 D_80099038[5];
extern f32 D_8009904C[4];
extern f32 D_8009905C[4];
extern f32 D_80085FD0;
extern f32 D_80085FD4;
extern f32 D_80085FD8;
extern f32 D_80085FDC;
extern f32 D_80085FE0;
extern f32 D_80085FE4;
extern f32 D_80085FE8;
f32 fabsf(f32);
f32 sqrtf(f32);
#pragma intrinsic(fabsf)
#pragma intrinsic(sqrtf)

f32 func_15048C30(f32 arg0) {
    s32 word;
    s32 exponent;
    f32 square;
    f32 reduced;
    f32 numerator;
    f32 denominator;
    f32 root;
    f32 correction;

    word = *(s32 *)&arg0;
    exponent = (word >> 23) & 0xFF;
    if (exponent < 126) {
        if (exponent >= 99) {
            square = arg0 * arg0;
            numerator = ((((D_80099020[5] * square + D_80099020[4]) * square + D_80099020[3]) * square + D_80099020[2]) * square + D_80099020[1]);
            denominator = ((((square + D_80099038[3]) * square + D_80099038[2]) * square + D_80099038[1]) * square + D_80099038[0]);
            return ((square * numerator) * arg0) / denominator + arg0;
        }
        return arg0;
    }
    if (exponent < 127) {
        square = fabsf(arg0);
        if (square < D_80085FE8) {
            square = arg0 * arg0;
            reduced = (square + square) - D_80085FD0;
            square = reduced * reduced;
            numerator = ((((D_80099020[5] * square + D_80099020[4]) * square + D_80099020[3]) * square + D_80099020[2]) * square + D_80099020[1]);
            denominator = ((((square + D_80099038[3]) * square + D_80099038[2]) * square + D_80099038[1]) * square + D_80099038[0]);
            correction = ((square * numerator) * reduced) / denominator + reduced;
            if (word > 0) {
                return 0.5f * correction + D_80085FD8;
            }
            return D_80085FE0 - 0.5f * correction;
        }
        reduced = (D_80085FD0 - square) * 0.5f;
        root = sqrtf(reduced);
        numerator = ((D_8009904C[3] * reduced + D_8009904C[2]) * reduced + D_8009904C[1]);
        denominator = ((reduced + D_8009905C[2]) * reduced + D_8009905C[1]) * reduced + D_8009905C[0];
        correction = ((reduced * numerator) * root) / denominator + root;
        if (word > 0) {
            return D_80085FDC - (correction + correction);
        }
        return (correction + correction) + D_80085FE4;
    }
    if (arg0 != arg0) {
        return 0.0f;
    }
    if (arg0 == D_80085FD0) {
        return D_80085FDC;
    }
    if (arg0 == D_80085FD4) {
        return D_80085FE4;
    }
    return 0.0f;
}
void func_15048F20(void *arg0, void *arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) (*(f32 *)((u8 *)arg1 + 0) + *(f32 *)((u8 *)arg0 + 0));
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg1 + 4) + *(f32 *)((u8 *)arg0 + 4));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg1 + 8) + *(f32 *)((u8 *)arg0 + 8));
}
void func_15048F58(void *arg0, void *arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) - *(f32 *)((u8 *)arg1 + 0));
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) - *(f32 *)((u8 *)arg1 + 4));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) - *(f32 *)((u8 *)arg1 + 8));
}
void func_15048F90(void *arg0, void *arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) (*(f32 *)((u8 *)arg1 + 0) - *(f32 *)((u8 *)arg0 + 0));
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg1 + 4) - *(f32 *)((u8 *)arg0 + 4));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg1 + 8) - *(f32 *)((u8 *)arg0 + 8));
}
extern f32 D_80099070;
extern f32 D_80099074;


f32 func_15048FC8(f32 *arg0) {
    f32 z;
    f32 length;
    f32 angle;
    z = arg0[2];
    length = sqrtf((arg0[0] * arg0[0]) + (z * z));
    if (length == 0.0f) {
        return 0.0f;
    }
    angle = (-arg0[0]) / length;
    angle = func_15048C30(angle);
    if (arg0[2] > 0.0f) {
        angle = 270.0f - (angle * D_80099070);
    } else {
        angle = (angle * D_80099074) + 90.0f;
    }
    angle -= 90.0f;
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}

f32 func_15048864(f32, f32);                        /* extern */

s32 func_150490A8(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;
    s32 temp_ft3;
    s32 var_v1;

    temp_fa1 = *(f32 *)((u8 *)arg0 + 0);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 8);
    temp_fa0 = sqrtf((temp_fa1 * temp_fa1) + (temp_fv1 * temp_fv1));
    if (temp_fa0 == 0.0f) {
        return 0;
    }
    temp_fa0 = temp_fa1 / temp_fa0;
    temp_ft3 = (s32) func_15048864(temp_fa0, temp_fa1);
    var_v1 = temp_ft3;
    if (*(f32 *)((u8 *)arg0 + 8) > 0.0f) {
        if (temp_ft3 < 0x40) {
            var_v1 = 0x80 - temp_ft3;
        } else {
            var_v1 = 0x180 - temp_ft3;
        }
    }
    return var_v1;
}
void func_15049148(void *arg0, f32 arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
}
f32 func_150AD930();                                /* extern */

void func_1504917C(void *arg0, void *arg1) {
    f32 temp_fv0;
    f32 var_fv1;

    temp_fv0 = func_150AD930();
    var_fv1 = temp_fv0;
    if (temp_fv0 != 0.0f) {
        var_fv1 = 1.0f / temp_fv0;
    }
    *(f32 *)((u8 *)arg1 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * var_fv1);
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * var_fv1);
    *(f32 *)((u8 *)arg1 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * var_fv1);
}
void func_150491EC(void *arg0, void *arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) (*(f32 *)((u8 *)arg1 + 0) - *(f32 *)((u8 *)arg0 + 0));
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg1 + 4) - *(f32 *)((u8 *)arg0 + 4));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg1 + 8) - *(f32 *)((u8 *)arg0 + 8));
    func_1504917C(arg2, arg2);
}
