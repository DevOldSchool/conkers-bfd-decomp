#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D3AB0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A6600
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D3AB0/func_151A6600.s")
void func_1000FD38(void *, void *, s32, void *);
extern u8 D_1000EF40;

void func_151A6AB8(void *arg0) {
    void *temp_a0;

    *(s8 *)(*(u8 **)((u8 *)arg0 + 0x110) + 0x14) = 1;
    func_1000FD38(&D_1000EF40, *(void **)((u8 *)arg0 + 0x110), 0, arg0);
    temp_a0 = *(void **)((u8 *)arg0 + 0x120);
    if (temp_a0 != 0) {
        func_1516972C(temp_a0);
    }
}
