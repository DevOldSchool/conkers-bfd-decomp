#include "types.h"

/*
 * Reviewed source unit: src/game/game_3DB60.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_small_units_3D6F0_3FC30.md
 */

struct Game1188E0Vector;
extern void (*D_800E0930)(struct Game1188E0Vector *, struct Game1188E0Vector *, void *);
void func_150EB430(struct Game1188E0Vector *, struct Game1188E0Vector *, void *);

void func_150106B0(void) {
    D_800E0930 = func_150EB430;
}
