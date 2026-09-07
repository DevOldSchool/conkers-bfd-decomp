#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BBFC0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518EB10
 * - func_1518EF54
 * - func_1518F058
 * - func_1518F108
 * - func_1518F15C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1BBFC0/func_1518EB10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BBFC0/func_1518EF54.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518F058 CURRENT (975) */
s32 func_1518F058(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x150);
    *(f32 *)((u8 *)arg0 + 0x140) = (f32) (*(f32 *)((u8 *)arg0 + 0x140) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x148) = (f32) (*(f32 *)((u8 *)arg0 + 0x148) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x144) = (f32) (*(f32 *)((u8 *)arg0 + 0x144) + (*(f32 *)((u8 *)arg0 + 0x14C) * D_800BE9A4));
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x140) * D_800BE9A4;
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x144) * D_800BE9A4;
    temp_ft4 = *(f32 *)((u8 *)arg0 + 0x148) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)arg0 + 0x34) + temp_fa0);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + temp_fa1);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + temp_ft4);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x40) + temp_fa0);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) + temp_fa1);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)arg0 + 0x48) + temp_ft4);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518F058 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BBFC0/func_1518F058.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518F108 CURRENT (10) */
s32 func_1518F108(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x30);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x154);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    if (temp_v0 < *(s16 *)((u8 *)arg0 + 0x158)) {
        *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (temp_v0 * *(s16 *)((u8 *)arg0 + 0x15A));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518F108 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BBFC0/func_1518F108.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518F15C CURRENT (20) */
s32 func_1518F15C(void *arg0) {
    f32 temp_fv0;
    s16 temp_v0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x30);
    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0 - (temp_fv0 * *(f32 *)((u8 *)arg0 + 0x154)));
    if (temp_v0 < *(s16 *)((u8 *)arg0 + 0x158)) {
        *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (temp_v0 * *(s16 *)((u8 *)arg0 + 0x15A));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518F15C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BBFC0/func_1518F15C.s")
