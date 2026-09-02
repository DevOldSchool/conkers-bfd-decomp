#include "types.h"

/*
 * Reviewed source unit: src/game/game_77A90.c
 * Boundary evidence: docs/evidence/game_remaining_units_up_to_64_bytes.md
 */

f32 func_15047C00(f32 arg0);
f32 func_15047D60(f32 arg0);

f32 func_1504A5E0(f32 arg0) {
    f32 result;

    result = func_15047D60(arg0);
    return result / func_15047C00(arg0);
}
