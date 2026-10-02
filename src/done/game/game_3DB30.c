#include "types.h"

/*
 * Reviewed source unit: src/game/game_3DB30.c
 * Boundary evidence: docs/evidence/game_small_units_3D6F0_3FC30.md
 */

extern void (*D_800E0940)(void);
void func_150EA904(void);

void func_15010680(void) {
    D_800E0940 = func_150EA904;
}
