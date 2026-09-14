#include "types.h"

/*
 * Reviewed source unit: src/game/game_F21D0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C4D20
 * - func_150C4E9C
 * - func_150C522C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_F21D0/func_150C4D20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F21D0/func_150C4E9C.s")
void func_1516972C(s32);
extern s32 D_800D98D0;
extern s32 D_800D98E0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C522C CURRENT (20) */
void func_150C522C(void) {
    s32 *var_s0;
    s32 *var_s1;
    s32 temp_a0;

    var_s1 = &D_800D98E0;
    var_s0 = &D_800D98D0;
    do {
        temp_a0 = *var_s0;
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
        }
        var_s0++;
        var_s0[-1] = 0;
    } while (var_s0 != var_s1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C522C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F21D0/func_150C522C.s")
