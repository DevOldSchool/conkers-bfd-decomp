#include "types.h"

/*
 * Reviewed source unit: src/game/game_1C0B10.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15193660
 * - func_151937F4
 * - func_151938FC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C0B10/func_15193660.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C0B10/func_151937F4.s")
extern f32 D_800A81E8;

s32 func_151938E4(u8 *arg0) {
    *(f32 *)(arg0 + 0x74) = D_800A81E8;
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C0B10/func_151938FC.s")
