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
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D080/func_150DFCA8.s")
extern f32 D_800A0FB0;

void func_150DFDA4(void *arg0) {
    void *temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x1D4) + 0x40;
    *(f32 *)((u8 *)temp_v0 + 0x30) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)temp_v0 + 0x34) = (f32) D_800A0FB0;
    *(f32 *)((u8 *)temp_v0 + 0x38) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
