#include "types.h"

/*
 * Reviewed source unit: src/game/game_75FC0.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15048C30
 * - func_15048F20
 * - func_15048FC8
 * - func_150490A8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1503E5F8(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_75FC0/func_15048C30.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15048F20 CURRENT (30) */
void func_15048F20(void *arg0, void *arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) + *(f32 *)((u8 *)arg1 + 0));
    *(f32 *)((u8 *)arg2 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + *(f32 *)((u8 *)arg1 + 4));
    *(f32 *)((u8 *)arg2 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + *(f32 *)((u8 *)arg1 + 8));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15048F20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_75FC0/func_15048F20.s")
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
f32 func_15048C30(f32, f32);                        /* extern */
extern f32 D_80099070;
extern f32 D_80099074;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15048FC8 CURRENT (3363) */
f32 func_15048FC8(void *arg0) {
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fa0_2;

    temp_fa1 = *(f32 *)((u8 *)arg0 + 0);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 8);
    temp_ft4 = sqrtf((temp_fa1 * temp_fa1) + (temp_fv1 * temp_fv1));
    if (temp_ft4 == 0.0f) {
        return 0.0f;
    }
    temp_fv0 = func_15048C30(-temp_fa1 / temp_ft4, temp_fa1);
    if (*(f32 *)((u8 *)arg0 + 8) > 0.0f) {
        var_fa0_2 = 270.0f - (temp_fv0 * D_80099070);
    } else {
        var_fa0_2 = (temp_fv0 * D_80099074) + 90.0f;
    }
    var_fa0 = var_fa0_2 - 90.0f;
    if (var_fa0 < 0.0f) {
        var_fa0 += 360.0f;
    }
    return var_fa0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15048FC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_75FC0/func_15048FC8.s")
f32 func_15048864(f32, f32);                        /* extern */

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150490A8 CURRENT (35) */
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
    temp_ft3 = (s32) func_15048864(temp_fa1 / temp_fa0, temp_fa1);
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
#endif /* CONKER_DEFERRED_CANDIDATE func_150490A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_75FC0/func_150490A8.s")
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
