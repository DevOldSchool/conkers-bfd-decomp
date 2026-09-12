#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FC0C0.c
 * Boundary evidence: docs/evidence/game_raw_direct_helper_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151CEC10
 * - func_151CEC54
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CEC10 CURRENT (20) */
s32 func_151CEC10(void *arg0, void *arg1, void *arg2) {
    s32 var_v0;

    var_v0 = 1;
    if (arg2 != 0) {
        *(s32 *)((u8 *)arg0 + 0) = *(s32 *)((u8 *)arg2 + 0x40);
        *(s32 *)((u8 *)arg0 + 4) = *(s32 *)((u8 *)arg2 + 0x44);
        *(s32 *)((u8 *)arg0 + 8) = *(s32 *)((u8 *)arg2 + 0x48);
    } else {
        *(f32 *)((u8 *)arg0 + 0) = *(f32 *)((u8 *)arg1 + 0x14);
        *(f32 *)((u8 *)arg0 + 4) = *(f32 *)((u8 *)arg1 + 0x18);
        *(f32 *)((u8 *)arg0 + 8) = *(f32 *)((u8 *)arg1 + 0x1C);
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CEC10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC0C0/func_151CEC10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC0C0/func_151CEC54.s")
