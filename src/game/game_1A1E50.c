#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A1E50.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151749A0
 * - func_151749F8
 * - func_15174AA4
 * - func_15174B48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE9E4;
extern u8 D_800DD405;
extern u8 D_800DD406;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151749A0 CURRENT (480) */
void func_151749A0(s32 arg0, s32 arg1) {
    u8 temp_t1;
    u8 temp_t8;

    temp_t8 = D_800DD406 + D_800BE9E4;
    D_800DD406 = temp_t8;
    if (arg0 < (temp_t8 & 0xFF)) {
        temp_t1 = D_800DD405 + 1;
        D_800DD405 = temp_t1;
        if ((temp_t1 & 0xFF) >= arg1) {
            D_800DD405 = 0;
        }
        D_800DD406 = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151749A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A1E50/func_151749A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A1E50/func_151749F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A1E50/func_15174AA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A1E50/func_15174B48.s")
