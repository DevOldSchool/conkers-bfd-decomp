#include "types.h"

/*
 * Reviewed source unit: src/game/game_DC360.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_selected_particle_resource_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AEEB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_DC360/func_150AEEB0.s")
s32 func_150AF1C0(void *arg0) {
    u8 *temp_v0;
    s32 var_v1;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x98);
    var_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
    var_v1 *= 32;
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    *(s8 *)(temp_v0 + 0x1B) = var_v1;
    if ((var_v1 & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
