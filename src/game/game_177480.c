#include "types.h"

/*
 * Reviewed source unit: src/game/game_177480.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15149FD0
 * - func_1514A19C
 * - func_1514A380
 * - func_1514A498
 * - func_1514A4EC
 * - func_1514A594
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_15149FD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A19C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A380.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514A498 CURRENT (10) */
s32 func_1514A498(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x30);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x144);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    if (temp_v0 < *(s16 *)((u8 *)arg0 + 0x156)) {
        *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (temp_v0 * *(s16 *)((u8 *)arg0 + 0x158));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514A498 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A498.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514A4EC CURRENT (2540) */
s32 func_1514A4EC(void *arg0) {
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x140);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) *(f32 *)((u8 *)arg0 + 0x34);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) *(f32 *)((u8 *)arg0 + 0x38);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) *(f32 *)((u8 *)arg0 + 0x3C);
    *(f32 *)((u8 *)arg0 + 0x130) = (f32) (*(f32 *)((u8 *)arg0 + 0x130) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x138) = (f32) (*(f32 *)((u8 *)arg0 + 0x138) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x134) = (f32) (*(f32 *)((u8 *)arg0 + 0x134) + (*(f32 *)((u8 *)arg0 + 0x13C) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)arg0 + 0x34) + (*(f32 *)((u8 *)arg0 + 0x130) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + (*(f32 *)((u8 *)arg0 + 0x134) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + (*(f32 *)((u8 *)arg0 + 0x138) * D_800BE9A4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514A4EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A4EC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514A594 CURRENT (1295) */
s32 func_1514A594(void *arg0) {
    f32 sp4;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft1;
    f32 temp_fv1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x140);
    *(f32 *)((u8 *)arg0 + 0x130) = (f32) (*(f32 *)((u8 *)arg0 + 0x130) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x134) = (f32) (*(f32 *)((u8 *)arg0 + 0x134) + (*(f32 *)((u8 *)arg0 + 0x13C) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x138) = (f32) (*(f32 *)((u8 *)arg0 + 0x138) * temp_fv0);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x130) * D_800BE9A4;
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x134) * D_800BE9A4;
    temp_ft4 = *(f32 *)((u8 *)arg0 + 0x138) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)arg0 + 0x34) + temp_fa0);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + temp_fa1);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + temp_ft4);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x40) + temp_fa0);
    temp_ft1 = *(f32 *)((u8 *)arg0 + 0x54);
    temp_ft5 = *(f32 *)((u8 *)arg0 + 0x34);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) + temp_fa1);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)arg0 + 0x48) + temp_ft4);
    sp4 = temp_ft1;
    temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x38);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x3C);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (temp_ft5 + ((*(f32 *)((u8 *)arg0 + 0x40) - temp_ft5) * sp4));
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (temp_fv0_2 + ((*(f32 *)((u8 *)arg0 + 0x44) - temp_fv0_2) * temp_ft1));
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (temp_fv1 + ((*(f32 *)((u8 *)arg0 + 0x48) - temp_fv1) * sp4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514A594 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A594.s")
