#include "types.h"

/*
 * Reviewed source unit: src/game/game_3FC30.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_small_units_3D6F0_3FC30.md
 */

extern s32 D_800DD410;
extern volatile s8 D_800DD418;

void func_15012780(void) {
    s32 i;

    *(s8 *)&D_800DD418 = 0;
    for (i = 0; i < 2; i++) {
        (&D_800DD410)[i] = 0;
    }
}
