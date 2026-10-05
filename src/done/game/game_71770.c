#include "types.h"

/*
 * Reviewed source unit: src/game/game_71770.c
 * Boundary evidence: docs/evidence/game_remaining_single_function_units_up_to_256_bytes.md
 * Semantic evidence: docs/evidence/vector_transform_helper_semantics.md
 */

/* Keep address symbols for linking and registered match evidence. */
#define matrixf_add_basis_translation func_150442C0

void matrixf_add_basis_translation(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3) {
    arg0[3][0] += (arg1 * arg0[0][0]) + (arg2 * arg0[1][0]) + (arg3 * arg0[2][0]);
    arg0[3][1] += (arg1 * arg0[0][1]) + (arg2 * arg0[1][1]) + (arg3 * arg0[2][1]);
    arg0[3][2] += (arg1 * arg0[0][2]) + (arg2 * arg0[1][2]) + (arg3 * arg0[2][2]);
}
