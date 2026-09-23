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
void func_10010154(s32, void *, s32, s32, s32);
u8 *func_1506C460(f32, f32, f32, f32, s32, s32, f32, f32, s32, s32, s32);
s32 func_1508855C(s32);
void func_150885EC(s32, s32);
s32 func_1508868C(u8 *);
extern u8 D_800C3E78;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D7790 CURRENT (98) */
void func_150D7790(u8 *arg0, s32 arg1) {
    u8 *existing;
    u8 *created;
    s32 type;
    s32 old_id;
    s32 new_id;
    s32 variant;

    variant = 0;
    existing = *(u8 **)(arg0 + 0x31C);
    if (existing != 0 && *(s8 *)(existing + 0x1AE) <= 0) {
        return;
    }
    switch (arg1) {
    case 0x30:
    case 0x31:
        if (existing != 0) {
            *(s16 *)(existing + 0x12C) = 0x78;
            existing = *(u8 **)(arg0 + 0x31C);
            *(s8 *)(existing + 0x1AE) -= 1;
            func_10010154(0x628, arg0, 0x7FFF, 0x1F4, 0x3E8);
        }
        return;
    case 0x33:
        variant = 1;
    case 0x32:
        break;
    default:
        return;
    }
    type = (variant * 0x1E) + 0x1E;
    created = func_1506C460(*(f32 *)(arg0 + 0x40), 310.0f, 0.0f, 0.0f,
                             type, 0xD, 0.0f, 1.0f, 0, 1, variant == 0);
    if (created != 0) {
        *(s8 *)(created + 0x124) = D_800C3E78 + 1;
    }
    if (created != 0 && type != 0x1E) {
        *(s8 *)(created + 0x221) = -1;
        old_id = func_1508855C((s32)arg0);
        if (old_id != -1) {
            new_id = func_1508868C(created);
            if (new_id != -1) {
                func_150885EC(old_id, new_id);
            }
        }
    }
    existing = *(u8 **)(arg0 + 0x31C);
    if (existing != 0) {
        *(s8 *)(existing + 0x1AE) -= 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D7790 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_104AE0/func_150D7790.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_104AE0/func_150D7928.s")
