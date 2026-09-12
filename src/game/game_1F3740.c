#include "types.h"

/*
 * Reviewed source unit: src/game/game_1F3740.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 */

s32 func_151C6290(void *arg0, s32 arg1, s32 arg2) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if ((temp_v0 == 0x5A) || (temp_v0 == 0x74) || (temp_v0 == 0x7A)) {
        return 0;
    }
    return 1;
}
