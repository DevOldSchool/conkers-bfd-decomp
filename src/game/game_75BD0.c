#include "types.h"

/*
 * Reviewed source unit: src/game/game_75BD0.c
 * Boundary evidence: docs/evidence/game_small_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15048758
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_15048A70(f32 arg0, f32 arg1);

f32 func_15048720(f32 arg0, f32 arg1, f32 arg2) {
    f32 result = func_15048A70(arg1, arg2);
    f32 product = result * arg0;

    return arg1 + product;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_75BD0/func_15048758.s")
