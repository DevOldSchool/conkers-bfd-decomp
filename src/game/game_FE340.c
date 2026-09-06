#include "types.h"

/*
 * Reviewed source unit: src/game/game_FE340.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D0E90
 * - func_150D10E4
 * - func_150D1204
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_FE340/func_150D0E90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FE340/func_150D10E4.s")
f32 func_150ADA68();                                /* extern */
extern f32 D_800A0894;

s32 func_150D11B4(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x74) = (f32) (((func_150ADA68() * 150.0f) + 350.0f) * D_800A0894);
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_FE340/func_150D1204.s")
