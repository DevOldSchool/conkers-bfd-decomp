#include "types.h"

/*
 * Reviewed source unit: src/game/game_D5650.c
 * Boundary evidence: docs/evidence/game_raw_handwritten_entry_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A81A0
 * - func_150A81D0
 * - func_150A94DC
 * - func_150A9984
 * - func_150A9B0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s64 **D_80088544;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A81A0 CURRENT (3370) */
void func_150A81A0(s64 *arg0, s64 *arg1) {
    s64 *temp_a3;
    s64 *var_a0;
    s64 *var_a1;

    var_a0 = arg0;
    var_a1 = arg1;
    temp_a3 = (void *)(var_a1 + 0x40);
    do {
        *var_a0 = *var_a1;
        var_a0 += 8;
        var_a1 += 8;
    } while (var_a1 != temp_a3);
    *D_80088544 = var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A81A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A81A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A81D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A94DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A9984.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5650/func_150A9B0C.s")
