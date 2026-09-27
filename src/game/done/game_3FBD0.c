#include "types.h"

/*
 * Reviewed source unit: src/game/game_3FBD0.c
 * Boundary evidence: docs/evidence/game_small_units_3D6F0_3FC30.md
 */

extern s32 D_800BE9F0;

s32 func_15012720(void) {
    switch (D_800BE9F0) {
        case 0:
        case 0x2C:
        case 0x37:
            return 2;
        case 0x28:
            return 6;
        default:
            return 5;
    }
}
