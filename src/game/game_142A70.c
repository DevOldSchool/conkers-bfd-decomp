#include "types.h"

/*
 * Reviewed source unit: src/game/game_142A70.c
 * Boundary evidence: docs/evidence/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151155C0
 * - func_1511575C
 * - func_15115F68
 * - func_15116058
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151155C0 CURRENT (12790) */
void func_151155C0(void *arg0) {
    s16 temp_t2;
    s16 temp_v0;
    s16 temp_v0_2;
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_t9;
    s32 temp_v1;
    s32 var_a3;
    s32 var_t0;
    s32 var_t4;
    s32 var_v1;
    u8 divisor;
    s16 target;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x3C);
    temp_t2 = *(s16 *)((u8 *)arg0 + 0x12);
    divisor = temp_v1 >> 0x10;
    temp_a1 = temp_v1 >> 0x18;
    target = temp_v1;
    divisor = (u8)divisor;
    temp_a1 = (u8)temp_a1 + 1;
    target = (s16)target;
    var_a3 = 0;
    var_t0 = 0;
    if ((*(u8 *)((u8 *)arg0 + 0x4F) & 4) == 4) {
        var_a3 = 1;
    }
    var_v1 = *(s32 *)((u8 *)arg0 + 0x7C);
    if (var_v1 == 0) {
        *(s32 *)((u8 *)arg0 + 0x7C) = (s32) temp_t2;
        var_v1 = (s32) temp_t2;
    }
    temp_lo = (s32) (target - var_v1) / divisor;
    var_t4 = *(s32 *)((u8 *)arg0 + 0x80);
    if (var_t4 == 0) {
        temp_v0 = temp_t2 - temp_lo;
        if (var_v1 == temp_t2) {
            if (var_a3 != 0) {
                *(s32 *)((u8 *)arg0 + 0x80) = temp_a1;
                var_t4 = temp_a1;
            }
        } else {
            if (var_v1 < target) {
                if (var_v1 < temp_v0) {
                    goto block_12;
                }
            } else if (temp_v0 < var_v1) {
block_12:
                var_t0 = 1;
            }
            var_t4 = -temp_a1;
            if (var_t0 != 0) {
                *(s16 *)((u8 *)arg0 + 0x12) = temp_v0;
                var_t4 = *(s32 *)((u8 *)arg0 + 0x80);
            } else {
                *(s16 *)((u8 *)arg0 + 0x12) = (s16) var_v1;
                *(s32 *)((u8 *)arg0 + 0x80) = var_t4;
            }
        }
    }
    if (var_t4 > 0) {
        temp_t9 = var_t4 - 1;
        temp_v0_2 = *(s16 *)((u8 *)arg0 + 0x12) + temp_lo;
        if (*(s32 *)((u8 *)arg0 + 0x7C) < target) {
            if (temp_v0_2 < target) {
                goto block_21;
            }
        } else if (target < temp_v0_2) {
block_21:
            var_t0 = 1;
        }
        var_t4 = temp_t9;
        if (var_t0 != 0) {
            *(s16 *)((u8 *)arg0 + 0x12) = temp_v0_2;
            *(s32 *)((u8 *)arg0 + 0x80) = temp_a1;
            var_t4 = temp_a1;
        } else {
            *(s16 *)((u8 *)arg0 + 0x12) = target;
            *(s32 *)((u8 *)arg0 + 0x80) = temp_t9;
        }
    }
    if (var_t4 < 0) {
        *(s32 *)((u8 *)arg0 + 0x80) = (s32) (var_t4 + 1);
    }
    *(s16 *)((u8 *)arg0 + 0x5C) = (s16) (*(s16 *)((u8 *)arg0 + 0x12) - temp_t2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151155C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142A70/func_151155C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_142A70/func_1511575C.s")
f32 func_150AD780(f32);                             /* extern */
f32 func_150AD78C(f32);                             /* extern */
extern f32 D_800A2FA0;
extern f32 D_800A2FA4;

void func_15115E0C(void *arg0, void *arg1) {
    f32 sp1C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;

    sp1C = func_150AD780(*(f32 *)((u8 *)arg0 + 4) * D_800A2FA0);
    temp_fv0 = func_150AD78C(*(f32 *)((u8 *)arg0 + 4) * D_800A2FA4);
    temp_fa0 = *(f32 *)((u8 *)arg1 + 0x14) - (f32) *(s16 *)((u8 *)arg0 + 0x10);
    temp_fa1 = *(f32 *)((u8 *)arg1 + 0x1C) - (f32) *(s16 *)((u8 *)arg0 + 0x14);
    if ((*(u8 *)((u8 *)arg0 + 0x4F) & 4) == 4) {
        *(f32 *)((u8 *)arg0 + 0x7C) = (f32) (*(f32 *)((u8 *)arg0 + 0x7C) + ((temp_fv0 * temp_fa0) + (sp1C * temp_fa1)));
        *(f32 *)((u8 *)arg0 + 0x80) = (f32) (*(f32 *)((u8 *)arg0 + 0x80) - ((temp_fv0 * temp_fa1) + (sp1C * temp_fa0)));
    }
}
void func_15115EDC(void *arg0, void *arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x7C);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x80);
    func_15115E0C(arg0, arg1);
    if (*(u16 *)((u8 *)arg1 + 0x84) == 0x4B) {
        temp_fv0 = *(f32 *)((u8 *)arg0 + 0x7C);
        temp_fv1 = *(f32 *)((u8 *)arg0 + 0x80);
        temp_fa0 = (temp_fv0 - temp_fa0) * 4.0f;
        temp_fa1 = (temp_fv1 - temp_fa1) * 4.0f;
        *(f32 *)((u8 *)arg0 + 0x7C) = temp_fv0 + temp_fa0;
        *(f32 *)((u8 *)arg0 + 0x80) = temp_fv1 + temp_fa1;
    }
}
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15115F68 CURRENT (1730) */
void func_15115F68(void *arg0) {
    f32 temp_fv0;
    f32 var_fv1;
    s32 divisor;
    s32 packed;
    s32 increment;
    s32 upper;
    s32 lower;

    packed = *(s32 *)((u8 *)arg0 + 0x3C);
    divisor = packed;
    increment = packed >> 16;
    upper = packed >> 8;
    lower = packed >> 24;
    divisor = (s8)divisor;
    increment = (s8)increment;
    upper = (s8)upper;
    lower = (s8)lower;
    if ((s8)packed != 0) {
        *(f32 *)arg0 += *(f32 *)((u8 *)arg0 + 0x7C) / (f32)divisor + (f32)increment;
    } else {
        *(f32 *)arg0 += (f32)(increment * D_800BE9E4);
    }
    temp_fv0 = *(f32 *)arg0;
    var_fv1 = (f32)upper;
    if (var_fv1 < temp_fv0) {
        *(f32 *)arg0 = var_fv1;
    } else {
        var_fv1 = (f32)lower;
        if (temp_fv0 < var_fv1) {
            *(f32 *)arg0 = var_fv1;
        }
    }
    *(f32 *)((u8 *)arg0 + 0x80) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x7C) = 0.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15115F68 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142A70/func_15115F68.s")
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15116058 CURRENT (3835) */
void func_15116058(void *arg0) {
    u8 *base;
    s32 delta;
    s32 offset;
    u16 count;
    u16 index;

    base = (u8 *)arg0;
    delta = *(s32 *)(base + 0x3C);
    count = *(u16 *)(base + 0x16);
    index = 0;
    offset = 0;
    while (index < count) {
        s32 *destination;
        s32 *source;

        destination = *(s32 **)(base + ((D_800BE9C0 & 0xFF) * 4) + 0x20);
        source = *(s32 **)(base + (((D_800BE9C0 == 0) & 0xFF) * 4) + 0x20);
        *(s16 *)((u8 *)destination + offset + 8) += (s16)(delta >> 16);
        *(s16 *)((u8 *)source + offset + 0xA) += (s16)delta;
        index += 1;
        offset += 0x10;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15116058 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142A70/func_15116058.s")
