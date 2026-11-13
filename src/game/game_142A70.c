#include "types.h"

/*
 * Reviewed source unit: src/game/game_142A70.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511575C
 * - func_15115F68
 * - func_15116058
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151155C0(void *arg0) {
    s32 divisor;
    s32 count;
    s32 target;
    s32 enabled;
    s32 crossed;
    s32 start;
    s32 step;
    s16 next;

    divisor = (u8)(*(s32 *)((u8 *)arg0 + 0x3C) >> 16);
    count = (u8)(*(s32 *)((u8 *)arg0 + 0x3C) >> 24) + 1;
    target = (s16)*(s32 *)((u8 *)arg0 + 0x3C);
    enabled = 0;
    crossed = 0;
    start = *(s16 *)((u8 *)arg0 + 0x12);
    if ((*(u8 *)((u8 *)arg0 + 0x4F) & 4) == 4) {
        enabled = 1;
    }
    if (*(s32 *)((u8 *)arg0 + 0x7C) == 0) {
        *(s32 *)((u8 *)arg0 + 0x7C) = *(s16 *)((u8 *)arg0 + 0x12);
    }
    step = (target - *(s32 *)((u8 *)arg0 + 0x7C)) / divisor;
    if (*(s32 *)((u8 *)arg0 + 0x80) == 0) {
        if (*(s32 *)((u8 *)arg0 + 0x7C) == *(s16 *)((u8 *)arg0 + 0x12)) {
            if (enabled) {
                *(s32 *)((u8 *)arg0 + 0x80) = count;
            }
        } else {
            next = *(s16 *)((u8 *)arg0 + 0x12) - step;
            if (*(s32 *)((u8 *)arg0 + 0x7C) < target) {
                if (*(s32 *)((u8 *)arg0 + 0x7C) < next) {
                    crossed = 1;
                }
            } else if (next < *(s32 *)((u8 *)arg0 + 0x7C)) {
                crossed = 1;
            }
            if (crossed) {
                *(s16 *)((u8 *)arg0 + 0x12) = next;
            } else {
                *(s16 *)((u8 *)arg0 + 0x12) = *(s32 *)((u8 *)arg0 + 0x7C);
                *(s32 *)((u8 *)arg0 + 0x80) = -count;
            }
        }
    }
    if (*(s32 *)((u8 *)arg0 + 0x80) > 0) {
        next = *(s16 *)((u8 *)arg0 + 0x12) + step;
        if (*(s32 *)((u8 *)arg0 + 0x7C) < target) {
            if (next < target) {
                crossed = 1;
            }
        } else if (target < next) {
            crossed = 1;
        }
        if (crossed) {
            *(s16 *)((u8 *)arg0 + 0x12) = next;
            *(s32 *)((u8 *)arg0 + 0x80) = count;
        } else {
            *(s16 *)((u8 *)arg0 + 0x12) = target;
            *(s32 *)((u8 *)arg0 + 0x80) = *(s32 *)((u8 *)arg0 + 0x80) - 1;
        }
    }
    if (*(s32 *)((u8 *)arg0 + 0x80) < 0) {
        *(s32 *)((u8 *)arg0 + 0x80) = *(s32 *)((u8 *)arg0 + 0x80) + 1;
    }
    *(s16 *)((u8 *)arg0 + 0x5C) = *(s16 *)((u8 *)arg0 + 0x12) - start;
}
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15116058 CURRENT (1165) */
void func_15116058(void *arg0) {
    u8 *base;
    s32 delta;
    s32 index;
    s32 offset;
    s16 low;

    base = arg0;
    delta = *(s32 *)(base + 0x3C);
    index = 0;
    low = (s16)delta;
    delta = (s16)(delta >> 16);
    if (*(u16 *)(base + 0x16) > 0) {
        offset = 0;
        do {
            index++;
            *(s16 *)(*(u8 **)(base + D_800BE9C0 * 4 + 0x20) + offset + 8) =
                *(s16 *)(*(u8 **)(base + (D_800BE9C0 == 0) * 4 + 0x20) + offset + 8) + delta;
            *(s16 *)(*(u8 **)(base + D_800BE9C0 * 4 + 0x20) + offset + 0xA) =
                *(s16 *)(*(u8 **)(base + (D_800BE9C0 == 0) * 4 + 0x20) + offset + 0xA) + low;
            offset += 0x10;
        } while (index < *(u16 *)(base + 0x16));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15116058 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142A70/func_15116058.s")
