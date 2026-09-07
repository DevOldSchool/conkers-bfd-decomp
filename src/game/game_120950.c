#include "types.h"

/*
 * Reviewed source unit: src/game/game_120950.c
 * Boundary evidence: docs/evidence/game_raw_direct_helper_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F34F4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_800A1980;
extern f32 D_800A1984;

f32 func_150F34A0(s32 arg0, f32 arg1) {
    f32 var_fv1;

    if (arg1 < -5.0f) {
        var_fv1 = (arg1 * D_800A1980) + D_800A1984;
    } else {
        var_fv1 = 0.75f;
    }
    return var_fv1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_120950/func_150F34F4.s")
