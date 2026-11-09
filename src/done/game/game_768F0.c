#include "types.h"

/*
 * Reviewed source unit: src/game/game_768F0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_medium_single_function_units.md
 */

s32 func_15049440(f32 *matrix, f32 x, f32 y, f32 z, f32 x_extent, f32 y_extent, f32 near_bound, f32 far_bound, f32 x_bound, f32 y_bound) {
    f32 depth;
    f32 projected_x;
    f32 projected_y;

    depth = -((matrix[2] * x) + (matrix[6] * y) + (matrix[10] * z) + matrix[14]);
    if (depth < near_bound) {
        return 0;
    }
    if (far_bound < depth) {
        return 0;
    }
    projected_x = (matrix[0] * x) + (matrix[4] * y) + (matrix[8] * z) + matrix[12];
    if (x_bound < (projected_x - x_extent)) {
        return 0;
    }
    if ((projected_x + x_extent) < -x_bound) {
        return 0;
    }
    projected_y = (matrix[1] * x) + (matrix[5] * y) + (matrix[9] * z) + matrix[13];
    if (y_bound < (projected_y - y_extent)) {
        return 0;
    }
    if ((projected_y + y_extent) < -y_bound) {
        return 0;
    }
    return (s32)depth;
}
