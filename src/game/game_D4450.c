#include "types.h"

/*
 * Reviewed source unit: src/game/game_D4450.c
 * Boundary evidence: docs/evidence/game_raw_handwritten_entry_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A6FA0
 * - func_150A70C0
 * - func_150A71C8
 * - func_150A7360
 * - func_150A751C
 * - func_150A76F0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_D4450/func_150A6FA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4450/func_150A70C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4450/func_150A71C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4450/func_150A7360.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4450/func_150A751C.s")
/* Semantic candidate only; the raw entry consumes live registers and tail-jumps. */
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A76F0 CURRENT (3410) */
f32 func_150A76F0(u32 index, u32 lower_bound, u32 *table, u32 upper_bound) {
    index &= 0xFF;
    if (index < 0x41) {
        return *(f32 *)&table[lower_bound - index];
    }
    if (index < 0x81) {
        return -*(f32 *)&table[index - 0x80];
    }
    if (index < 0xC1) {
        return -*(f32 *)&table[upper_bound - index];
    }
    return *(f32 *)&table[index];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A76F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4450/func_150A76F0.s")
