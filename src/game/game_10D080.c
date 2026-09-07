#include "types.h"

/*
 * Reviewed source unit: src/game/game_10D080.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DFBD0
 * - func_150DFCA8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_10D080/func_150DFBD0.s")
extern f32 D_800A0FA0;
extern f32 D_800A0FA4;
extern f32 D_800A0FA8;
extern f32 D_800A0FAC;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DFCA8 CURRENT (190) */
void func_150DFCA8(void *arg0) {
    f32 temp_fa0;
    f32 var_fv0;

    *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + (*(f32 *)((u8 *)arg0 + 0x64) * (f32) D_800BE9E4));
    temp_fa0 = *(f32 *)((u8 *)arg0 + 4);
    if (temp_fa0 < 11.0f) {
        var_fv0 = D_800A0FA0;
        *(f32 *)((u8 *)arg0 + 0x7C) = var_fv0;
    } else if (temp_fa0 > 55.0f) {
        var_fv0 = -D_800A0FA4;
        *(f32 *)((u8 *)arg0 + 0x7C) = var_fv0;
    } else {
        var_fv0 = *(f32 *)((u8 *)arg0 + 0x7C);
    }
    if (*(f32 *)((u8 *)arg0 + 0x64) < var_fv0) {
        *(f32 *)((u8 *)arg0 + 0x64) = (f32) (*(f32 *)((u8 *)arg0 + 0x64) + D_800A0FA8);
        if (var_fv0 < *(f32 *)((u8 *)arg0 + 0x64)) {
            *(f32 *)((u8 *)arg0 + 0x64) = var_fv0;
        }
    } else if (var_fv0 < *(f32 *)((u8 *)arg0 + 0x64)) {
        *(f32 *)((u8 *)arg0 + 0x64) = (f32) (*(f32 *)((u8 *)arg0 + 0x64) - D_800A0FAC);
        if (*(f32 *)((u8 *)arg0 + 0x64) < var_fv0) {
            *(f32 *)((u8 *)arg0 + 0x64) = var_fv0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DFCA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D080/func_150DFCA8.s")
extern f32 D_800A0FB0;

void func_150DFDA4(void *arg0) {
    void *temp_v0;

    temp_v0 = (void *)(*(s32 *)((u8 *)arg0 + 0x1D4) + 0x40);
    *(f32 *)((u8 *)temp_v0 + 0x30) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)temp_v0 + 0x34) = (f32) D_800A0FB0;
    *(f32 *)((u8 *)temp_v0 + 0x38) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
