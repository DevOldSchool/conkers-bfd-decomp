#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FBED0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151CEA20
 * - func_151CEAAC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CEA20 CURRENT (575) */
s32 func_151CEA20(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x40);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x44);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (temp_fv1 + (temp_fa0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + ((temp_fv1 + (0.5f * temp_fa0 * D_800BE9A4)) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)arg0 + 0x50) + (*(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4));
    if (*(f32 *)((u8 *)arg0 + 0x50) > 1.0f) {
        *(f32 *)((u8 *)arg0 + 0x50) = 1.0f;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CEA20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FBED0/func_151CEA20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FBED0/func_151CEAAC.s")
