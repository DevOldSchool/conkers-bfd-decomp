#include "types.h"

/*
 * Reviewed source unit: src/game/game_76E50.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150499A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150499A0 CURRENT (3906) */
void func_150499A0(void *arg0, void *arg1) {
    f32 (*input)[4];
    f32 (*output)[4];
    f32 a, b, c, d, e, f, g, h, i;
    f32 reciprocal;

    input = arg0;
    output = arg1;
    a = input[0][0];
    e = input[1][1];
    i = input[2][2];
    b = input[0][1];
    f = input[1][2];
    g = input[2][0];
    c = input[0][2];
    d = input[1][0];
    h = input[2][1];

    reciprocal = 1.0f / (((((((a * e) * i) + ((b * f) * g)) +
                             ((c * d) * h)) - ((c * e) * g)) -
                           ((b * d) * i)) - ((a * f) * h));

    output[0][0] = ((e * i) - (h * f)) * reciprocal;
    output[1][0] = ((input[1][2] * input[2][0]) -
                     (input[2][2] * input[1][0])) * reciprocal;
    output[2][0] = ((input[1][0] * input[2][1]) -
                     (input[2][0] * input[1][1])) * reciprocal;
    output[0][1] = ((input[0][2] * input[2][1]) -
                     (input[2][2] * input[0][1])) * reciprocal;
    output[1][1] = ((input[0][0] * input[2][2]) -
                     (input[2][0] * input[0][2])) * reciprocal;
    output[2][1] = ((input[0][1] * input[2][0]) -
                     (input[2][1] * input[0][0])) * reciprocal;
    output[0][2] = ((input[0][1] * input[1][2]) -
                     (input[1][1] * input[0][2])) * reciprocal;
    output[1][2] = ((input[0][2] * input[1][0]) -
                     (input[1][2] * input[0][0])) * reciprocal;
    output[2][2] = ((input[0][0] * input[1][1]) -
                     (input[1][0] * input[0][1])) * reciprocal;

    output[3][0] = -((output[2][0] * input[3][2]) +
                     ((input[3][0] * output[0][0]) +
                      (input[3][1] * output[1][0])));
    output[3][1] = -((output[2][1] * input[3][2]) +
                     ((input[3][0] * output[0][1]) +
                      (input[3][1] * output[1][1])));
    output[3][3] = 1.0f;
    output[0][3] = 0.0f;
    output[1][3] = 0.0f;
    output[2][3] = 0.0f;
    output[3][2] = -((output[2][2] * input[3][2]) +
                     ((input[3][0] * output[0][2]) +
                      (input[3][1] * output[1][2])));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150499A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_76E50/func_150499A0.s")
