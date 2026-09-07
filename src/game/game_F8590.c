#include "types.h"

/*
 * Reviewed source unit: src/game/game_F8590.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CB0E0
 * - func_150CB1F4
 * - func_150CB800
 * - func_150CBABC
 * - func_150CBCE0
 * - func_150CBE88
 * - func_150CBF5C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CB0E0.s")
s32 func_150CB1E0(s32 arg0, s32 arg1) {
    return 0xB;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CB1F4.s")
s32 func_150CB7CC(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x28)) {
            *(u8 *)((u8 *)arg0 + 0x28) = (u8) temp_v1;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CB800.s")
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

s32 func_150CBA30(void *arg0) {
    f32 temp_fv0;
    s16 temp_v0;
    s32 temp_v1;

    *(s16 *)((u8 *)arg0 + 0x128) = (s16) (*(s16 *)((u8 *)arg0 + 0x128) - D_800BE9E4);
    if (*(s16 *)((u8 *)arg0 + 0x128) > 0) {
        temp_fv0 = *(f32 *)((u8 *)arg0 + 0x12C) * D_800BE9A4;
        *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + temp_fv0);
        *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + temp_fv0);
    }
    if (*(s32 *)((u8 *)arg0 + 0x58) & 1) {
        temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
        if (temp_v0 < 0x20) {
            temp_v1 = temp_v0 * 8;
            if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
                *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
            }
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CBABC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CBCE0 CURRENT (13905) */
s32 func_150CBCE0(void *arg0, s32 arg1) {
    f32 var_ft5;
    f32 var_ft5_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 var_v1;
    s32 var_v1_2;

    var_v1 = D_800BE9E4;
    if (var_v1 != 0) {
        temp_a2 = -(var_v1 & 3);
        temp_a1 = var_v1 + temp_a2;
        if (temp_a2 != 0) {
            var_v1 -= 1;
            var_ft5 = *(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8);
            if (temp_a1 != var_v1) {
                do {
                    *(f32 *)((u8 *)arg0 + 0x58) = var_ft5;
                    var_v1 -= 1;
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    var_ft5 = *(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8);
                } while (temp_a1 != var_v1);
            }
            *(f32 *)((u8 *)arg0 + 0x58) = var_ft5;
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
            if (var_v1 != 0) {
                goto block_5;
            }
        } else {
block_5:
            var_v1_2 = var_v1 - 4;
            var_ft5_2 = *(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8);
            if (var_v1_2 != 0) {
                do {
                    *(f32 *)((u8 *)arg0 + 0x58) = var_ft5_2;
                    var_v1_2 -= 4;
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
                    *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
                    var_ft5_2 = *(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8);
                } while (var_v1_2 != 0);
            }
            *(f32 *)((u8 *)arg0 + 0x58) = var_ft5_2;
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)arg0 + 0xA8));
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)arg0 + 0xA8));
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CBCE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CBCE0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CBE88 CURRENT (325) */
s32 func_150CBE88(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x5C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x48);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + (*(f32 *)((u8 *)arg0 + 0x44) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + ((temp_fv1 * D_800BE9A4) + (D_800BE9A4 * temp_fa0 * D_800BE9A4 * 0.5f)));
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x40) + (*(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (temp_fv1 + (temp_fa0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) + (*(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) + (*(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) + (*(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CBE88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CBE88.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CBF5C CURRENT (30) */
void func_150CBF5C(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x1C) = 0x20;
    *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CBF5C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F8590/func_150CBF5C.s")
