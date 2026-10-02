#include "types.h"

/*
 * Reviewed source unit: src/game/game_3DB60.c
 * Boundary evidence: docs/evidence/game_small_units_3D6F0_3FC30.md
 */

extern void (*D_800E0930)(void);
void func_150EB430(void);

void func_150106B0(void) {
    D_800E0930 = func_150EB430;
}
