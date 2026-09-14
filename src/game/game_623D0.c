#include "types.h"

/*
 * Reviewed source unit: src/game/game_623D0.c
 * Boundary evidence: docs/evidence/game_raw_record_glyph_emitter_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15034F30
 * - func_150356C8
 * - func_15035714
 * - func_15035808
 * - func_15035D6C
 * - func_15035FE8
 * - func_15036148
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s8 D_800C3F00;

void func_15034F20(void) {
    D_800C3F00 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15034F30.s")
extern u8 D_800C3F08[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150356C8 CURRENT (30) */
void *func_150356C8(void) {
    s32 temp_t6;
    u8 temp_v1;

    temp_v1 = D_800C3F00;
    if (temp_v1 == 0xF) {
        return 0;
    }
    temp_t6 = temp_v1 + 1;
    D_800C3F00 = temp_t6;
    return ((temp_t6 & 0xFF) * 0xC) - 0xC + D_800C3F08;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150356C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_150356C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15035714.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15035808.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15035D6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15035FE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_623D0/func_15036148.s")
