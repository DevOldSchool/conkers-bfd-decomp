#include "types.h"

/*
 * Reviewed source unit: src/game/game_EEB70.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C16C0
 * - func_150C1978
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_EEB70/func_150C16C0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C1978 CURRENT (480) */
s32 func_150C1978(void *arg0) {
    s32 temp_t6;
    s32 var_v1;
    void *temp_v0;

    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 8;
    var_v1 = temp_t6;
    if (temp_t6 >= 0x100) {
        var_v1 = 0xFF;
    }
    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    *(s8 *)((u8 *)temp_v0 + 0x1B) = var_v1;
    if ((var_v1 & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C1978 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EEB70/func_150C1978.s")
