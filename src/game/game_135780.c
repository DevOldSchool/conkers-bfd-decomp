#include "types.h"

/*
 * Reviewed source unit: src/game/game_135780.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151082D0
 * - func_15108658
 * - func_151087FC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_135780/func_151082D0.s")
f32 func_150ADA68();                                /* extern */
extern f32 D_800A2460;
extern f32 D_800A2464;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108658 CURRENT (1991) */
s32 func_15108658(u8 *arg0, s32 arg1) {
    void *sp18;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    u8 *var_v0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0xA8);
    var_v0 = (void *)(arg0 + 0xA8);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0xAC) - temp_fv0;
    if ((temp_fv0 < *(f32 *)((u8 *)arg0 + 0xB4)) || (temp_fv1 < *(f32 *)((u8 *)var_v0 + 0xC))) {
        *(s32 *)((u8 *)arg0 + 0x1C) = 0;
        var_v0 = (void *)(arg0 + 0xA8);
    } else {
        temp_fv0_2 = *(f32 *)((u8 *)var_v0 + 8);
        if ((*(f32 *)((u8 *)arg0 + 0xA8) < temp_fv0_2) || (temp_fv1 < temp_fv0_2)) {
            *(s32 *)((u8 *)arg0 + 0x1C) = 0x10000;
        } else {
            *(s32 *)((u8 *)arg0 + 0x1C) = 0x20000;
        }
    }
    temp_fv0_3 = *(f32 *)((u8 *)var_v0 + 0x10);
    if (temp_fv0_3 != 0.0f) {
        if ((temp_fv0_3 < D_800A2460) || ((11.0f - temp_fv0_3) < D_800A2460)) {
            *(s32 *)((u8 *)arg0 + 0x1C) = 0;
            *(s8 *)((u8 *)arg0 + 0x74) = -1;
        } else {
            *(s8 *)((u8 *)arg0 + 0x74) = 3;
        }
        *(f32 *)((u8 *)var_v0 + 0x10) = (f32) (*(f32 *)((u8 *)var_v0 + 0x10) - D_800BE9A4);
        if (*(f32 *)((u8 *)var_v0 + 0x10) < 0.0f) {
            *(f32 *)((u8 *)var_v0 + 0x10) = 0.0f;
            *(s8 *)((u8 *)arg0 + 0x74) = -1;
        }
        goto block_19;
    }
    *(f32 *)((u8 *)var_v0 + 0) = (f32) (*(f32 *)((u8 *)var_v0 + 0) - D_800BE9A4);
    if (*(f32 *)((u8 *)var_v0 + 0) < 0.0f) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x1C) == 0x20000) {
        sp18 = var_v0;
        if (func_150ADA68() < D_800A2464) {
            *(f32 *)((u8 *)var_v0 + 0x10) = 11.0f;
        }
    }
block_19:
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108658 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135780/func_15108658.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151087FC CURRENT (759) */
void func_151087FC(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_t6;
    void *temp_v0;
    void *temp_v0_2;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x2B) {
        temp_v0 = arg0 + 0x28;
        *(u8 *)((u8 *)temp_v0 + 8) = (u8) (*(u8 *)((u8 *)temp_v0 + 8) | 1);
        return;
    }
    temp_v0_2 = arg0 + 0x28;
    if (temp_t6 == 0x2C) {
        *(u8 *)((u8 *)temp_v0_2 + 8) = (u8) (*(u8 *)((u8 *)temp_v0_2 + 8) & 0xFFFE);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151087FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135780/func_151087FC.s")
