#include "types.h"

/*
 * Reviewed source unit: src/game/game_DC360.c
 * Boundary evidence: docs/evidence/game_raw_selected_particle_resource_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AEEB0
 * - func_150AF1C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_DC360/func_150AEEB0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AF1C0 CURRENT (440) */
s32 func_150AF1C0(void *arg0) {
    s16 temp_v1;
    u8 *temp_v0;
    s32 temp_t6;
    s32 var_v1;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x98);
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
    temp_t6 = temp_v1 << 5;
    var_v1 = temp_t6;
    if (temp_t6 >= 0x100) {
        var_v1 = -1;
    }
    *(s8 *)(temp_v0 + 0x1B) = var_v1;
    if ((var_v1 & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AF1C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DC360/func_150AF1C0.s")
