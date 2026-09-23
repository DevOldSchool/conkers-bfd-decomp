#include "types.h"

/*
 * Reviewed source unit: src/game/game_768F0.c
 * Boundary evidence: docs/evidence/game_medium_single_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15049440
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15049440 CURRENT (1059) */
s32 func_15049440(f32 *matrix, f32 x, f32 y, f32 z, f32 x_extent, f32 y_extent, f32 near_bound, f32 far_bound, f32 x_bound, f32 y_bound) {
    f32 depth;
    f32 projected_x;
    f32 projected_y;

    depth = -(matrix[14] + ((matrix[2] * x) + (matrix[6] * y) + (matrix[10] * z)));
    if (depth < near_bound) {
        return 0;
    }
    if (far_bound < depth) {
        return 0;
    }
    projected_x = matrix[12] + ((matrix[0] * x) + (matrix[4] * y) + (matrix[8] * z));
    if (x_bound < (projected_x - x_extent)) {
        return 0;
    }
    if ((projected_x + x_extent) < -x_bound) {
        return 0;
    }
    projected_y = matrix[13] + ((matrix[1] * x) + (matrix[5] * y) + (matrix[9] * z));
    if (y_bound < (projected_y - y_extent)) {
        return 0;
    }
    if ((projected_y + y_extent) < -y_bound) {
        return 0;
    }
    return (s32)depth;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15049440 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_768F0/func_15049440.s")
