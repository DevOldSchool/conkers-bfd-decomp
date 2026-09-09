#include "types.h"

/*
 * Reviewed source unit: src/game/game_142A70.c
 * Boundary evidence: docs/evidence/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151155C0
 * - func_1511575C
 * - func_15115E0C
 * - func_15115EDC
 * - func_15115F68
 * - func_15116058
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151155C0 CURRENT (11445) */
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

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x3C);
    temp_t2 = *(s16 *)((u8 *)arg0 + 0x12);
    temp_a1 = ((temp_v1 >> 0x18) & 0xFF) + 1;
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
    temp_lo = (s32) ((s16) temp_v1 - var_v1) / (s32) ((temp_v1 >> 0x10) & 0xFF);
    var_t4 = *(s32 *)((u8 *)arg0 + 0x80);
    if (var_t4 == 0) {
        temp_v0 = temp_t2 - temp_lo;
        if (var_v1 == temp_t2) {
            if (var_a3 != 0) {
                *(s32 *)((u8 *)arg0 + 0x80) = temp_a1;
                var_t4 = temp_a1;
            }
        } else {
            if (var_v1 < (s16) temp_v1) {
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
        if (*(s32 *)((u8 *)arg0 + 0x7C) < (s16) temp_v1) {
            if (temp_v0_2 < (s16) temp_v1) {
                goto block_21;
            }
        } else if ((s16) temp_v1 < temp_v0_2) {
block_21:
            var_t0 = 1;
        }
        var_t4 = temp_t9;
        if (var_t0 != 0) {
            *(s16 *)((u8 *)arg0 + 0x12) = temp_v0_2;
            *(s32 *)((u8 *)arg0 + 0x80) = temp_a1;
            var_t4 = temp_a1;
        } else {
            *(s16 *)((u8 *)arg0 + 0x12) = (s16) temp_v1;
            *(s32 *)((u8 *)arg0 + 0x80) = temp_t9;
        }
    }
    if (var_t4 < 0) {
        *(s32 *)((u8 *)arg0 + 0x80) = (s32) (var_t4 + 1);
    }
    *(s16 *)((u8 *)arg0 + 0x5C) = (s16) (*(s16 *)((u8 *)arg0 + 0x12) * 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151155C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142A70/func_151155C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_142A70/func_1511575C.s")
f32 func_150AD780(f32);                             /* extern */
f32 func_150AD78C(f32, void *);                     /* extern */
extern f32 D_800A2FA0;
extern f32 D_800A2FA4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15115E0C CURRENT (10) */
void func_15115E0C(void *arg0, void *arg1) {
    f32 sp1C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;

    sp1C = func_150AD780(*(f32 *)((u8 *)arg0 + 4) * D_800A2FA0);
    temp_fv0 = func_150AD78C(*(f32 *)((u8 *)arg0 + 4) * D_800A2FA4, arg0);
    temp_fa0 = *(f32 *)((u8 *)arg1 + 0x14) - (f32) *(s16 *)((u8 *)arg0 + 0x10);
    temp_fa1 = *(f32 *)((u8 *)arg1 + 0x1C) - (f32) *(s16 *)((u8 *)arg0 + 0x14);
    if ((*(u8 *)((u8 *)arg0 + 0x4F) & 4) == 4) {
        *(f32 *)((u8 *)arg0 + 0x7C) = (f32) (*(f32 *)((u8 *)arg0 + 0x7C) + ((temp_fv0 * temp_fa0) + (sp1C * temp_fa1)));
        *(f32 *)((u8 *)arg0 + 0x80) = (f32) (*(f32 *)((u8 *)arg0 + 0x80) - ((temp_fv0 * temp_fa1) + (sp1C * temp_fa0)));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15115E0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142A70/func_15115E0C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15115EDC CURRENT (1482) */
void func_15115EDC(void *arg0, void *arg1) {
    f32 sp1C;
    f32 sp18;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x7C);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x80);
    sp1C = temp_fa0;
    sp18 = temp_fa1;
    func_15115E0C(arg0, arg1);
    if (*(u16 *)((u8 *)arg1 + 0x84) == 0x4B) {
        temp_fv0 = *(f32 *)((u8 *)arg0 + 0x7C);
        temp_fv1 = *(f32 *)((u8 *)arg0 + 0x80);
        *(f32 *)((u8 *)arg0 + 0x7C) = (f32) (temp_fv0 + ((temp_fv0 - temp_fa0) * 4.0f));
        *(f32 *)((u8 *)arg0 + 0x80) = (f32) (temp_fv1 + ((temp_fv1 - temp_fa1) * 4.0f));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15115EDC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142A70/func_15115EDC.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15115F68 CURRENT (3210) */
void func_15115F68(void *arg0) {
    f32 temp_fv0;
    f32 var_fv1;
    s32 temp_a1;
    s32 temp_v1;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x3C);
    temp_a1 = temp_v1 >> 0x10;
    if ((s8) temp_v1 != 0) {
        *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) + ((*(f32 *)((u8 *)arg0 + 0x7C) / (f32) (s8) temp_v1) + (f32) (s8) temp_a1));
    } else {
        *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) + (f32) ((s8) D_800BE9E4 * temp_a1));
    }
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0);
    var_fv1 = (f32) (s8) (temp_v1 >> 8);
    if (var_fv1 < temp_fv0) {
        goto block_6;
    }
    var_fv1 = (f32) (s8) (temp_v1 >> 0x18);
    if (temp_fv0 < var_fv1) {
block_6:
        *(f32 *)((u8 *)arg0 + 0) = var_fv1;
    }
    *(f32 *)((u8 *)arg0 + 0x80) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x7C) = 0.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15115F68 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_142A70/func_15115F68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_142A70/func_15116058.s")
