#include "types.h"

/*
 * Reviewed source unit: src/game/game_108AE0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DB630
 * - func_150DB714
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DB630 CURRENT (4585) */
s32 func_150DB630(void *arg0) {
    f32 temp_fv0;

    if (**(f32 **)((u8 *)arg0 + 0x120) > 255.0f) {
        *(s8 *)((u8 *)arg0 + 0x5C) = 0xFF;
        return 1;
    }
    temp_fv0 = **(f32 **)((u8 *)arg0 + 0x120);
    if (temp_fv0 < 0.0f) {
        *(s8 *)((u8 *)arg0 + 0x5C) = 0;
        return 1;
    }
    *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (u32) temp_fv0;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DB630 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_108AE0/func_150DB630.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_108AE0/func_150DB714.s")
