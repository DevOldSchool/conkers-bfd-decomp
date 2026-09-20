#include "types.h"

/*
 * Reviewed source unit: src/game/game_FD110.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CFC60
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_800A0878;
extern f32 D_800A087C;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CFC60 CURRENT (2425) */
s32 func_150CFC60(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 *state;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x74);
    *(f32 *)((u8 *)arg0 + 0x10) += *(f32 *)((u8 *)arg0 + 0x70) * D_800BE9A4;
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x78);
    *(f32 *)((u8 *)arg0 + 0x14) +=
        temp_fv1 * D_800BE9A4 +
        0.5f * temp_fa0 * D_800BE9A4 * D_800BE9A4;
    state = (u8 *)arg0 + 0x70;
    *(f32 *)(state + 4) = temp_fv1 + temp_fa0 * D_800BE9A4;
    if (*(f32 *)((u8 *)arg0 + 0x7C) < *(f32 *)((u8 *)arg0 + 0x14)) {
        *(f32 *)((u8 *)arg0 + 0x14) = *(f32 *)(state + 0xC);
        temp_fv0 = __builtin_fabsf(*(f32 *)(state + 4));
        *(f32 *)state *= D_800A0878;
        *(f32 *)(state + 4) = temp_fv0 * D_800A087C;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CFC60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD110/func_150CFC60.s")
