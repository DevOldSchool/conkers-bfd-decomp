#include "types.h"

/*
 * Reviewed source unit: src/game/game_35E80.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_units_up_to_64_bytes.md
 */

extern u8 D_800DD2A0[4];

void func_150089D0(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_800DD2A0[i] = 0xFF;
    }
}
