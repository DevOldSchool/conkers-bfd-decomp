#include "types.h"

/*
 * Reviewed source unit: src/game/game_131620.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15104170
 * - func_151041E4
 * - func_1510448C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_131620/func_15104170.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131620/func_151041E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131620/func_1510448C.s")
extern void *D_800CC5EC;

u8 func_151044F4(void) {
    if (D_800CC5EC != 0) {
        return *(u8 *)((u8 *)D_800CC5EC + 0x7D);
    }
    return 0U;
}
