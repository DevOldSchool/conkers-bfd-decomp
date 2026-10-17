#include "types.h"

/*
 * Reviewed source unit: src/game/game_36280.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_units_up_to_64_bytes.md
 */

extern s32 D_800DD460;
extern s32 D_800DD468;

void func_15008DD0(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        (&D_800DD460)[i] = 0;
    }
}
