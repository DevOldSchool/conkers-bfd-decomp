#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E6260.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B8DB0
 * - func_151B9214
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E6260/func_151B8DB0.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800AA564;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B9214 CURRENT (2686) */
s32 func_151B9214(u8 *arg0) {
    void *sp18;
    f32 temp_fa0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    u8 *temp_v0;

    *(f32 *)((u8 *)arg0 + 0x178) = (f32) (*(f32 *)((u8 *)arg0 + 0x178) + (*(f32 *)((u8 *)arg0 + 0x17C) * D_800BE9A4));
    {
        f32 temp_fv0 = func_15144B68(*(f32 *)((u8 *)arg0 + 0x178));
    temp_v0 = (void *)(arg0 + 0x170);
    *(f32 *)((u8 *)temp_v0 + 8) = temp_fv0;
    sp18 = temp_v0;
    temp_fv1 = *(f32 *)((u8 *)temp_v0 + 4);
    temp_fa0 = *(f32 *)((u8 *)temp_v0 + 0x18);
    *(f32 *)((u8 *)arg0 + 0x170) = (f32) (func_15047D60(temp_fv0) * temp_fv1);
    if (temp_fa0 > 0.0f) {
        *(f32 *)((u8 *)temp_v0 + 0x18) = (f32) (temp_fa0 - D_800BE9A4);
        *(f32 *)((u8 *)temp_v0 + 0xC) = (f32) (*(f32 *)((u8 *)temp_v0 + 0xC) + (*(f32 *)((u8 *)temp_v0 + 0x20) * D_800BE9A4));
        *(f32 *)((u8 *)temp_v0 + 4) = (f32) (temp_fv1 + (*(f32 *)((u8 *)temp_v0 + 0x1C) * D_800BE9A4));
    } else {
        temp_fv0_2 = *(f32 *)((u8 *)temp_v0 + 0xC);
        *(f32 *)((u8 *)temp_v0 + 0xC) = (f32) (temp_fv0_2 + ((*(f32 *)((u8 *)temp_v0 + 0x14) - temp_fv0_2) * D_800AA564));
        *(f32 *)((u8 *)temp_v0 + 4) = (f32) (temp_fv1 + ((*(f32 *)((u8 *)temp_v0 + 0x10) - temp_fv1) * D_800AA564));
    }
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B9214 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E6260/func_151B9214.s")
